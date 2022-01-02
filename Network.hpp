// TODO
#include"ioPFL.hpp"
#include<queue>
#include<cstring>
#include<algorithm>
class Network{
 private:
  bool EK_bfs(int S,int T,int *pre,int *neck){
    static queue<int> q;
    static bool vis[NodeLimit];
    q=queue<int>();
    memset(vis,0,sizeof(vis));
    q.push(S);
    vis[S]=1;
    neck[S]=inf;
    int u;
    while(!q.empty()){
      u=q.front();
      q.pop();
      for(int e=head[u],v;e;e=Next[e]){
        if(len[e]==0||vis[v=edge[e]])
          continue;
        vis[v]=1;
        neck[v]=min(neck[u],len[e]);
        pre[v]=e;
        q.push(v);
        if(v==T)
          return 1;
      }
    }
    return 0;
  }
  void EK_update(int S,int T,int *pre,int *neck,int &ans){
    int u=T,v;
    while(u!=S){
      v=pre[u];
      len[v]-=neck[T];
      len[v^1]+=neck[T];
      u=edge[v^1];
    }
    ans+=neck[T];
  }
  bool Dinic_bfs(int S,int T,int *dep,int *cur){
    static queue<int> q;
    static bool vis[NodeLimit];
    memset(dep,0x3f,sizeof(dep));
    q=queue<int>();
    memset(vis,0,sizeof(vis));
    q.push(S);
    dep[S]=0;
    vis[S]=1;
    cur[S]=head[S];
    int u;
    while(!q.empty()){
      u=q.front();
      q.pop();
      for(int e=head[u],v;e;e=Next[e]){
        v=edge[e];
        if(len[e]>0&&!vis[v]){
          q.push(v);
          vis[v]=1;
          cur[v]=head[v];
          dep[v]=dep[u]+1;
        }
      }
    }
    return vis[T];
  }
  int Dinic_dfs(int u,int T,int neck,int *dep,int *cur){
    if(u==T)
      return neck;
    int uflow=0;
    for(int e=cur[u],v,vflow;e&&neck;e=Next[e]){
      cur[u]=e;
      v=edge[e];
      if(len[e]>0&&(dep[v]==dep[u]+1)){
        vflow=Dinic_dfs(v,T,min(neck,len[e]),dep,cur);
        if(vflow==0)
          dep[v]=inf;
        len[e]-=vflow;
        len[e^1]+=vflow;
        uflow+=vflow;
        neck-=vflow;
      }
    }
    return uflow;
  }
 public:
  int n,m;
  int edgenum,head[NodeLimit],edge[EdgeLimit],Next[EdgeLimit],len[EdgeLimit];
  Network():edgenum(1),n(0),m(0){}
  void addedge(int u,int v,int w){
    if(edgenum>=Edgelimit)
      Assert(1);
    edge[++edgenum]=v;
    Next[edgenum]=head[u];
    len[edgenum]=w;
    head[u]=edgenum;
  }
  Network &operator()(const int &n,const int &m){
    this->n=n;
    this->m=m;
    return *this;
  }
  int EK(int S,int T){
    static int pre[NodeLimit],neck[NodeLimit],ans;
    ans=0;
    while(EK_bfs(S,T,pre,neck))
      EK_update(S,T,pre,neck,ans);
    return ans;
  }
  int Dinic(int S,int T){
    static int dep[NodeLimit],cur[NodeLimit];
    static int ans,d;
    ans=0;
    while(Dinic_bfs(S,T,dep,cur))
      while(d=Dinic_dfs(S,T,inf,dep,cur))
        ans+=d;
    return ans;
  }
};
Input &operator>>(Input &in,Network &G){
  for(int i=1,u,v,w;i<=G.m;i++){
    in >> u >> v >> w;
    G.addedge(u,v,w);
    G.addedge(v,u,0);
  }
  return in;
}
Output &operator<<(Output &out,const Network &G){
  for(int u=1;u<=G.n;u++)
    for(int e=G.head[u];e;e=G.Next[e])
      out << u << ' ' << G.edge[e] << ' ' << G.len[e] << '\n';
  return out;
}
