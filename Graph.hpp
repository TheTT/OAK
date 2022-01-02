// Copyright (c) TheToror
#ifndef __GRAPH__
#define __GRAPH__

#include"ioPFL.hpp"

#include<queue>
#include<cstring>
#include<algorithm>

typedef std::priority_queue<std::pair<int,int> ,std::vector<std::pair<int,int> >,std::greater<std::pair<int,int> > > gprqpii;

namespace Graph_Static{
  const int NodeLimit=3003,EdgeLimit=55555,Edgelimit=EdgeLimit/100*100;
 // Dijkstra
  bool Dijkstra_locked[NodeLimit];
  gprqpii Dijkstra_q;
 // SPFA
  int SPFA_cnt[NodeLimit];
  bool SPFA_locked[NodeLimit];
  std::deque<int> SPFA_q;
 // Johnson
  int Johnson_dist[NodeLimit][NodeLimit];
  int Johnson_h[NodeLimit];
}
class Graph{
 private:
 public:
  int n,m;
  bool Directed;
  int edgenum,head[Graph_Static::NodeLimit],edge[Graph_Static::EdgeLimit],Next[Graph_Static::EdgeLimit],len[Graph_Static::EdgeLimit];
  Graph():edgenum(0),n(0),m(0),Directed(1){}
  void Dijkstra(int *dist,int S){
    memset(dist,0x3f,sizeof(int)*Graph_Static::NodeLimit);
    memset(Graph_Static::Dijkstra_locked,0,sizeof(Graph_Static::Dijkstra_locked));
    Graph_Static::Dijkstra_q=gprqpii();
    Graph_Static::Dijkstra_q.push(std::make_pair(dist[S]=0,S));
    int u;
    while(Graph_Static::Dijkstra_q.size()){
      u=Graph_Static::Dijkstra_q.top().second;
      Graph_Static::Dijkstra_q.pop();
      if(Graph_Static::Dijkstra_locked[u])
        continue;
      Graph_Static::Dijkstra_locked[u]=1;
      for(int e=head[u],v;e;e=Next[e]){
        v=edge[e];
        if((!Graph_Static::Dijkstra_locked[v])&&dist[u]+len[e]<dist[v])
          Graph_Static::Dijkstra_q.push(std::make_pair(dist[v]=dist[u]+len[e],v));
      }
    }
  }
  bool SPFA(int *dist,int S){
    memset(dist,0x3f,sizeof(int)*Graph_Static::NodeLimit);
    memset(Graph_Static::SPFA_locked,0,sizeof(Graph_Static::SPFA_locked));
    memset(Graph_Static::SPFA_cnt,0,sizeof(Graph_Static::SPFA_cnt));
    dist[S]=0;
    Graph_Static::SPFA_locked[S]=1;
    Graph_Static::SPFA_cnt[S]++;
    Graph_Static::SPFA_q.push_back(S);
    int u,t;
    while(Graph_Static::SPFA_q.size()){
      u=Graph_Static::SPFA_q.front();
      Graph_Static::SPFA_q.pop_front();
      for(int e=head[u],v;e;e=Next[e]){
        v=edge[e];
        if(dist[v]>dist[u]+len[e]){
          dist[v]=dist[u]+len[e];
          if(!Graph_Static::SPFA_locked[v]){
            if((++Graph_Static::SPFA_cnt[v])>n){
              memset(dist,0xc0,sizeof(dist));
              return 0;
            }
            Graph_Static::SPFA_locked[v]=1;
            if(Graph_Static::SPFA_q.size()&&dist[v]<dist[Graph_Static::SPFA_q.front()]+30000){
              t=Graph_Static::SPFA_q.front();
              Graph_Static::SPFA_q.pop_front();
              Graph_Static::SPFA_q.push_back(t);
              Graph_Static::SPFA_q.push_front(v);
            }
            else if(Graph_Static::SPFA_q.size()&&dist[v]<dist[Graph_Static::SPFA_q.front()])
              Graph_Static::SPFA_q.push_front(v);
            else Graph_Static::SPFA_q.push_back(v);
          }
        }
      }
      Graph_Static::SPFA_locked[u]=0;
    }
    return 1;
  }
  bool Johnson(){
    memset(Graph_Static::Johnson_dist,0x3f,sizeof(int)*Graph_Static::NodeLimit*Graph_Static::NodeLimit);
    for(int i=1;i<=n;i++)
      addedge(0,i,0);
    if(!SPFA(Graph_Static::Johnson_h,0)){
      for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
          Graph_Static::Johnson_dist[i][j]=int(0xc0c0c0c0c0c0c0c0LL);
      return 0;
    }
    for(int u=1;u<=n;u++)
      for(int e=head[u];e;e=Next[e])
        len[e]+=Graph_Static::Johnson_h[u]-Graph_Static::Johnson_h[edge[e]];
    for(int i=1;i<=n;i++){
      Dijkstra(Graph_Static::Johnson_dist[i],i);
      for(int j=1;j<=n;j++)
        Graph_Static::Johnson_dist[i][j]-=Graph_Static::Johnson_h[i]-Graph_Static::Johnson_h[j];
    }
    return 1;
  }
  void addedge(int u,int v,int w){
    if(edgenum>=Graph_Static::Edgelimit){
      terr << "Too many edges.\n";
      exit(0);
    }
    edge[++edgenum]=v;
    Next[edgenum]=head[u];
    len[edgenum]=w;
    head[u]=edgenum;
  }
  Graph &operator()(const int &n,const int &m,const int &d=1){
    this->n=n;
    this->m=m;
    Directed=d;
    return *this;
  }
};
Input &operator>>(Input &in,Graph &G){
  for(int i=1,u,v,w;i<=G.m;i++){
    in >> u >> v >> w;
    G.addedge(u,v,w);
    if(!G.Directed)
      G.addedge(v,u,w);
  }
  return in;
}
Output &operator<<(Output &out,const Graph &G){
  for(int u=1;u<=G.n;u++)
    for(int e=G.head[u];e;e=G.Next[e])
      if(u<=G.edge[e]||!G.Directed)
        out << u << ' ' << G.edge[e] << ' ' << G.len[e] << '\n';
  return out;
}

namespace uGraph_Static{
  const int NodeLimit=3003,EdgeLimit=55555,Edgelimit=EdgeLimit/100*100;
}
class uGraph{
 private:
 public:
  int n,m;
  bool Directed;
  int edgenum,head[uGraph_Static::NodeLimit],edge[uGraph_Static::EdgeLimit],Next[uGraph_Static::EdgeLimit];
  uGraph():edgenum(0),n(0),m(0),Directed(1){}
  void addedge(int u,int v){
    if(edgenum>=uGraph_Static::Edgelimit)
      exit(0);
    edge[++edgenum]=v;
    Next[edgenum]=head[u];
    head[u]=edgenum;
  }
  uGraph &operator()(const int &n,const int &m,const int &d=1){
    this->n=n;
    this->m=m;
    Directed=d;
    return *this;
  }
};
Input &operator>>(Input &in,uGraph &G){
  for(int i=1,u,v,w;i<=G.m;i++){
    in >> u >> v;
    G.addedge(u,v);
    if(!G.Directed)
      G.addedge(v,u);
  }
  return in;
}
Output &operator<<(Output &out,const uGraph &G){
  for(int u=1;u<=G.n;u++)
    for(int e=G.head[u];e;e=G.Next[e])
      if(u<=G.edge[e]||!G.Directed)
        out << u << ' ' << G.edge[e] << '\n';
  return out;
}

#endif
