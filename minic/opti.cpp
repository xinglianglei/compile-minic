#include "opti.h"
#include <gvc.h>
#include <iostream>
#include<algorithm>
#include <vector>
#include "IRCode.h"
using namespace std;

extern InterCode itcode;

int func_num = 0;//函数个数
int block_num = 0;//每个函数块名
int instNo = 0;//每个块语句数
int loop_num = 0;
bool first = false;
vector<string> states;
Agnode_t *ag[10][500];
int func_bNum[10];
unordered_map<string, vector<string>> block_map;
string cur_block;
bool skip = false;

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
                states.push_back(cur);
            } else {
                bool flag = false;
                for (auto &block : block_map.find(cur)->second) {
                    if (find(states.begin(), states.end(), block) == states.end()) {
                        flag = true;
                        break;
                    }
                }
                if (flag == false) {
                    Agnode_t *node = agfindnode(g_opti, (char *)cur.c_str());
                    agdelnode(g_opti, node);
                    states.push_back(cur);
                }
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
            skip = false;//到下一个entry处，即下一个块儿处，停止跳过
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
            skip = false;//到下一个label处，即下一个块儿处，停止跳过
        }
        if (skip) {
            cnt++;
            continue;
        }
        if (stmt->getOp() == "bc") {
            for (auto val : stmt->getSrc()) {
                auto iter = block_map.find(to_string(func_num) + " " + val);
                if (iter != block_map.end()) {
                    iter->second.push_back(cur_block);
                } else {
                    std::vector<string> myVector;
                    myVector.push_back(cur_block);
                    block_map.insert({ to_string(func_num) + " " + val,myVector });
                }
            }
            skip = true;
        }
        if (stmt->getOp() == "br") {
            auto iter = block_map.find(to_string(func_num) + " " + stmt->getDst());
            if (iter != block_map.end()) {
                iter->second.push_back(cur_block);
            } else {
                std::vector<string> myVector;
                myVector.push_back(cur_block);
                block_map.insert({ to_string(func_num) + " " + stmt->getDst(),myVector });
            }
            skip = true;
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
            agedge(g_opti, tg, src, "", 1);
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
