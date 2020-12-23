#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H

#include "Tool.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <time.h>

namespace zxh{
using namespace std;

class Graph_Generator
{
private:
    char addr[1005];
    int to[max_node_size],mp[max_node_size],sz[max_node_size],sum[max_node_size];
    int fa[max_node_size<<1];

    double rand_double()
    {
        int x,y;
        x=rand()%edge_value_range;
        y=rand()%100;
        return x+0.01*y;
    }

    int find(int x)
    {
        int t=fa[x];
        if(x==fa[x])
            return fa[x];
        fa[x]=find(t);
        return fa[x];
    }

    void join(int x,int y)
    {
        int fx=find(x),fy=find(y);
        if(fx!=fy)
            fa[fx]=fy;
    }

    void multiblock_generate(int n,int m,int nodecou)
    {
        ofstream outfile(addr,ios::out);
        if(!outfile.good()){
            throw ftc::Error(__LINE__,"open file error");
        }
        int i,x,y;
        double w;
        memset(fa,0,sizeof(fa));
        memset(sz,0,sizeof(sz));
        memset(sum,0,sizeof(sum));
        for(i=1;i<=n;i++)
        {
            fa[i]=i;
            outfile<<'<'<<i<<">\n";
        }
        int nodesz=n/nodecou;
        for(i=1;i<=nodecou/2;i++)
        {
            do
            {
                x=(rand()%nodesz)+2;
                y=nodesz*2-x; 
            }while(!(x>0&&y>0));
            sz[i*2-1]=x; sz[i*2]=y;
        }
        for(i=1;i<nodecou;i++)
        {
            sum[i]=sum[i-1]+sz[i];
            //outfile<<"O: "<<sz[i]<<' '<<sum[i]<<endl;
        }
        sum[nodecou]=n;
        if(sz[nodecou]==0)
            sz[nodecou]=n-sum[nodecou-1];
        //outfile<<"O: "<<sz[nodecou]<<' '<<sum[nodecou]<<endl;
        for(int nz=1;nz<=nodecou;nz++)
            for(i=1;i<sz[nz];i++)
            {
                do
                {
                    x=rand()%sz[nz]+sum[nz-1]+1;
                    y=rand()%sz[nz]+sum[nz-1]+1;
                }while(find(x)==find(y));
                w=rand_double();
                join(x,y);
                outfile<<'<'<<x<<' '<<y<<' '<<w<<">\n";
            }
        for(i=1;i<=m-n+nodecou;i++)
        {
            do
            {
                x=rand()%n+1;
                y=rand()%n+1;
            }while(find(x)!=find(y)||x==y); 
            w=rand_double();
            outfile<<'<'<<x<<' '<<y<<' '<<w<<">\n";

        }
        outfile.close();
    }

    void block_generate(int n,int m)
    {
        ofstream outfile(addr,ios::out);
        if(!outfile.good()){
            throw ftc::Error(__LINE__,"open file error");
        }
        int i,x,y;
        double w;
        memset(fa,0,sizeof(fa));
        for(i=1;i<=n;i++)
        {
            fa[i]=i;
            outfile<<'<'<<i<<">\n";
        }
        for(i=1;i<n;i++)
        {
            do
            {
                x=rand()%n+1;
                y=rand()%n+1;
            }while(find(x)==find(y));
            w=rand_double();
            join(x,y);
            outfile<<'<'<<x<<' '<<y<<' '<<w<<">\n";
        }
        for(i=1;i<=m-n+1;i++)
        {
            do
            {
                x=rand()%n+1;
                y=rand()%n+1;
            }while(x==y);
            w=rand_double();
            outfile<<'<'<<x<<' '<<y<<' '<<w<<">\n";
        }
        outfile.close();
    }
    void normal_generate(int n,int m)
    {
        int i,x,y;
        double w;
        ofstream outfile(addr,ios::out);
        if(!outfile.good()){
            throw ftc::Error(__LINE__,"open file error");
        }
        memset(to,0,sizeof(to));
        memset(mp,0,sizeof(mp));
        for(i=1;i<=n;i++)
        {
            do
            {
                to[i]=rand()%node_id_range+1;
            }while(mp[to[i]]);
            mp[to[i]]=1;
            outfile<<'<'<<to[i]<<">\n";
        }
        for(i=1;i<=m;i++)
        {
            x=to[rand()%n+1];
            y=to[rand()%n+1];
            w=rand_double();
            outfile<<'<'<<x<<' '<<y<<' '<<w<<">\n";
        }
        outfile.close();
    }
    void append_generate(int m)
    {
        ofstream outfile(addr,ios::app);
        int i,x,y;
        double w;
        for(i=1;i<=m;i++)
        {
            x=rand()%node_id_range+1;
            y=rand()%node_id_range+1;
            w=rand_double();
            outfile<<'<'<<x<<' '<<y<<' '<<w<<">\n";
        }
        outfile.close();
    }
public:
    Graph_Generator() {}
    void generate(zxh::WORKING_STATE mode, const char* filename, int n, int m,int nodecou)
    {
        srand((unsigned)time(NULL));
        // int mode,n,m,nodecou;
        // printf("Input the address of the output:");
        // scanf("%s",addr);
        strcpy(addr, filename);
        // printf("Choose the mode(1: RANDOM_MODE,2: APPEND_MODE,3: SINGALBLOCK_MODE,4: MULTIBLOCK_MODE):");
        // scanf("%d",&mode);
        switch(mode)
        {
            case RANDOM_MODE:
                // scanf("%d %d",&n,&m);
                normal_generate(n,m);break;
            case APPEND_MODE:
                // scanf("%d",&m);
                append_generate(m);break;
            case SINGALBLOCK_MODE:
                // scanf("%d %d",&n,&m);
                block_generate(n,m);break;
            case MULTIBLOCK_MODE:
                // scanf("%d %d %d",&n,&m,&nodecou);
                multiblock_generate(n,m,nodecou);break;
        default:
            throw ftc::Error(__LINE__,"mode error");
        }
    }
};
}// end namespace zxh
#endif
