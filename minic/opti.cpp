#include "opti.h"
#include <gvc.h>
#include <iostream>
#include <vector>
#include "IRCode.h"
using namespace std;

extern InterCode itcode;

int func_num = 0;
int block_num = 0;
int instNo = 0;
bool first = false;
Agnode_t *ag[10][500];
unordered_map<string, string> block_map;
string cur_block;

// 创建GV的上下文
GVC_t *gv_opti = gvContext();
// 创建一个图形
Agraph_t *g_opti = agopen((char *)"ast", Agdirected, nullptr);

/*|| stmt->getOp() == "lt" || stmt->getOp() == "le"
        || stmt->getOp() == "gt" || stmt->getOp() == "ge" || stmt->getOp() == "eq" || stmt->getOp() == "ne"*/

void opti()
{
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
            first = true;
            instNo = 0;
            nodeLabel = "";
            cur_block = (char *)(to_string(func_num) + " " + stmt->getDst()).c_str();
        }

        if (stmt->getOp() == "bc") {
            for (auto val : stmt->getSrc()) {
                //if (block_map.find(cur_block))
                block_map.insert({ cur_block, to_string(func_num) + " " + val });
            }
        }
        if (stmt->getOp() == "br") {
            block_map.insert({ cur_block, to_string(func_num) + " " + stmt->getDst() });
        }

        nodeLabel += to_string(instNo) + " " + itcode.ircode[cnt] + "\\l";
        cnt++;
        instNo++;
    }
    agsafeset(ag[func_num][block_num], (char *)"label", (char *)nodeLabel.c_str(), (char *)"");
    agsafeset(ag[func_num][block_num], (char *)"shape", (char *)"Mrecord", (char *)"");

    for (auto &kv : block_map) {
        Agnode_t *src = agfindnode(g_opti, (char *)kv.first.c_str());
        Agnode_t *tg = agfindnode(g_opti, (char *)kv.second.c_str());
        agedge(g_opti, src, tg, "", 1);
    }
}



void opti_show(const std::string filePath)
{
    agsafeset(g_opti, (char *)"dpi", (char *)"600", (char *)"");

    opti();

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
