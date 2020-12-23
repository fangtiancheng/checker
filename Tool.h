#ifndef TOOL_H
#define TOOL_H
namespace zxh{
const double inf=0x3f3f3f3f;

const int node_data_size=10005;

const int node_id_range=3000;
const int node_size_range=3000;
const int edge_size_range=10000;
const int edge_value_range=9999;

enum WORKING_STATE{UNKNOWN,RANDOM_MODE=1,APPEND_MODE,SINGALBLOCK_MODE,MULTIBLOCK_MODE};

enum SEG_ALGORITHM{BruteForce_MODE=1,LouvainSA_MODE,Greedy_MODE,GreedyMKL_MODE};

const int max_edge_size=30005;
const int max_node_size=5005;

struct edge
{
    int to,next;
    double w;
};

struct v_edge
{
    int to,next;
    double w;
    int ty;
};

struct val
{
    int x,y;
    double w;
    val(int xx=0,int yy=0,double ww=0)
    {
        x=xx;y=yy;w=ww;
    }
    bool operator<(val x)const
    {
        return w<x.w;
    }
};
}// end namespace zxh
#endif
