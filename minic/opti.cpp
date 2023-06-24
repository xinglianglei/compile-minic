#include "opti.h"
#include <gvc.h>
#include <iostream>
#include <vector>
#include "IRCode.h"
using namespace std;

extern InterCode itcode;

int func_num = 0;//函数个数
int block_num = 0;//每个函数块名
int instNo = 0;//每个块语句数
int loop_num = 0;
bool first = false;
Agnode_t *ag[10][500];
int func_bNum[10];
unordered_map<string, vector<string>> block_map;
string cur_block;

// 创建GV的上下文
GVC_t *gv_opti = gvContext();
// 创建一个图形
Agraph_t *g_opti = agopen((char *)"ast", Agdirected, nullptr);

/*|| stmt->getOp() == "lt" || stmt->getOp() == "le"
        || stmt->getOp() == "gt" || stmt->getOp() == "ge" || stmt->getOp() == "eq" || stmt->getOp() == "ne"*/

void opti()
{
    for (int i = 0; i <= func_num; i++) {
        for (int j = 1;j < func_bNum[i];j++) {
            string cur = to_string(i) + " .L" + to_string(j);
            if (block_map.find(cur) == block_map.end()) {
                Agnode_t *node = agfindnode(g_opti, (char *)cur.c_str());
                agdelnode(g_opti, node);
            }
        }
    }
}

void gen_graph()
{
    //生成结点
    //语句数
    int cnt = 0;
    string nodeLabel = "";
    for (auto &stmt : itcode.getInsts()) {
        if (stmt->getOp() == "entry") {
            if (first) {
                agsafeset(ag[func_num][block_num], (char *)"label", (char *)nodeLabel.c_str(), (char *)"");
                agsafeset(ag[func_num][block_num], (char *)"shape", (char *)"Mrecord", (char *)"");
                func_num++;
            }
            block_num = 0;
            ag[func_num][block_num] = agnode(g_opti, (char *)(to_string(func_num) + " " + stmt->getDst()).c_str(), 1);
            func_bNum[func_num]++;
            first = true;
            instNo = 0;
            nodeLabel = "";
            cur_block = (char *)(to_string(func_num) + " " + stmt->getDst()).c_str();
        }
        if (stmt->getOp() == "label") {
            if (first) {
                agsafeset(ag[func_num][block_num], (char *)"label", (char *)nodeLabel.c_str(), (char *)"");
                agsafeset(ag[func_num][block_num], (char *)"shape", (char *)"Mrecord", (char *)"");
            }
            block_num = atoi(stmt->getDst().substr(2, 100).c_str());
            ag[func_num][block_num] = agnode(g_opti, (char *)(to_string(func_num) + " " + stmt->getDst()).c_str(), 1);
            func_bNum[func_num]++;
            first = true;
            instNo = 0;
            nodeLabel = "";
            cur_block = (char *)(to_string(func_num) + " " + stmt->getDst()).c_str();
        }

        if (stmt->getOp() == "bc") {
            auto iter = block_map.find(cur_block);
            if (iter != block_map.end()) {
                for (auto val : stmt->getSrc()) {
                    iter->second.push_back(to_string(func_num) + " " + val);
                }
            } else {
                std::vector<string> myVector;
                for (auto val : stmt->getSrc()) {
                    myVector.push_back(to_string(func_num) + " " + val);
                }
                block_map.insert({ cur_block,myVector });
            }
        }
        if (stmt->getOp() == "br") {
            auto iter = block_map.find(cur_block);
            if (iter != block_map.end()) {
                iter->second.push_back(to_string(func_num) + " " + stmt->getDst());
            } else {
                std::vector<string> myVector;
                myVector.push_back(to_string(func_num) + " " + stmt->getDst());
                block_map.insert({ cur_block,myVector });
            }
        }

        nodeLabel += to_string(instNo) + " " + itcode.ircode[cnt] + "\\l";
        cnt++;
        instNo++;
    }
    agsafeset(ag[func_num][block_num], (char *)"label", (char *)nodeLabel.c_str(), (char *)"");
    agsafeset(ag[func_num][block_num], (char *)"shape", (char *)"Mrecord", (char *)"");

    //遍历哈希表，连边
    for (auto &kv : block_map) {
        Agnode_t *src = agfindnode(g_opti, (char *)kv.first.c_str());
        for (auto &iter : kv.second) {
            Agnode_t *tg = agfindnode(g_opti, (char *)iter.c_str());
            agedge(g_opti, src, tg, "", 1);
        }
    }
    //优化
    opti();
}



void opti_show(const std::string filePath)
{
    agsafeset(g_opti, (char *)"dpi", (char *)"600", (char *)"");

    gen_graph();

    // 设置图形的布局
    gvLayout(gv_opti, g_opti, "dot");

    string fileExtName;

    string::size_type pos = filePath.find_last_of('.');
    if (pos == string::npos) {
        fileExtName = "png";
    } else {
        fileExtName = filePath.substr(pos + 1);
    }

    // 输出到一个文件中，png格式
    gvRenderFilename(gv_opti, g_opti, fileExtName.c_str(), filePath.c_str());

    // 关闭图形上下文，并清理资源
    gvFreeLayout(gv_opti, g_opti);
    agclose(g_opti);
    gvFreeContext(gv_opti);
}
