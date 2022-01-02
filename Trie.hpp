#include<cstring>
class Trie{
 public:
  int data[100005],head[100005],nodenum;
  int Next[200005],edge[200005],id[200005],edgenum;
  int nptr;
  Trie(){
    nodenum=edgenum=0;
    memset(data,0,sizeof(data));
    memset(head,0,sizeof(head));
    memset(Next,0,sizeof(Next));
    memset(edge,-1,sizeof(edge));
    memset(id,-1,sizeof(id));
  }
  void add(int n,int a[],int d){
    int p=0,flag;
    for(int i=1;i<=n;i++){
      flag=0;
      for(int e=head[p];e;e=Next[e])
        if(id[e]==a[i]/*-abandon*/){
          flag=1;
          p=edge[e];
          break;
        }
      if(!flag){
        edge[++edgenum]=++nodenum;
        Next[edgenum]=head[p];
        id[edgenum]=a[i];
        head[p]=edgenum;
        data[p=nodenum]=0;
      }
    }
    data[p]=d;
  }
  void step(int a){
    if(nptr==-1)
      return;
    for(int e=head[nptr];e;e=Next[e])
      if(id[e]==a/*-abandon*/){
        nptr=edge[e];
        return;
      }
    nptr=-1;
  }
  void reset(){
    nptr=0;
  }
  int get(){
    return (nptr==-1)?0:data[nptr];
  }
};
