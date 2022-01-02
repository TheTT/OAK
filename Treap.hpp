// Copyright (c) TheToror
#ifndef __TREAP__
#define __TREAP__

#include<ctime>
#include<stack>
#include<cstdlib>

namespace Treap_Static{
  const int Array_Limit=100005;
}
int n;
template<class _Tp>
struct TepND{
  _Tp v;
  int sz,cnt,key;
  int fa,ch[2];
  TepND(){}
  TepND(_Tp v):v(v){
    sz=cnt=1;
    key=rand()+100;
    fa=ch[0]=ch[1]=0;
  }
};
template<class _Tp>
class Treap{
  private:
    TepND<_Tp> t[Treap_Static::Array_Limit<<2];
    std::stack<int> recybin;
    int root,nodetop;
    void update(int);
    bool WhCh(int);
    int newnode(_Tp);
    void rotate(int,bool);
    void FIX(int);
  public:
    Treap<_Tp>(){}
    void Insert(_Tp);
    void Delete(_Tp);
    int Rank(_Tp);
    _Tp kth(int);
    _Tp Successor(_Tp);
    _Tp Precursor(_Tp);
};

template<class _Tp>
void Treap<_Tp>::update(int o){
  t[o].sz=t[t[o].ch[0]].sz+t[t[o].ch[1]].sz+t[o].cnt;
}
template<class _Tp>
bool Treap<_Tp>::WhCh(int o){
  return t[t[o].fa].ch[1]==o;
}
template<class _Tp>
int Treap<_Tp>::newnode(_Tp v){
  int o;
  if(recybin.size()){
    o=recybin.top();
    recybin.pop();
  }
  else o=++nodetop;
  t[o]=TepND<_Tp>(v);
  return o;
}
template<class _Tp>
void Treap<_Tp>::rotate(int o,bool c){
  int s1=t[o].ch[!c];
  t[o].ch[!c]=t[s1].ch[c];
  if(t[s1].ch[c])
    t[t[s1].ch[c]].fa=o;
  t[s1].fa=t[o].fa;
  if(!t[o].fa)
    root=s1;
  else t[t[o].fa].ch[WhCh(o)]=s1;
  t[s1].ch[c]=o;
  t[o].fa=s1;
  update(o);
  update(s1);
}
template<class _Tp>
void Treap<_Tp>::FIX(int o){
  while(t[o].fa&&t[o].key>t[o].fa)
    rotate(t[o].fa,!WhCh(o));
  while((t[o].ch[0]&&t[t[o].ch[0]].key>t[o].key)||(t[o].ch[1]&&t[t[o].ch[1]].key>t[o].key))
    if(t[t[o].ch[0]].key>t[t[o].ch[1]].key)
      rotate(o,1);
    else rotate(o,0);
}
template<class _Tp>
void Treap<_Tp>::Insert(_Tp v){
  int o=root,f=0;
  while(o){
    t[o].sz++,f=o;
    if(v==t[o].v){
      t[o].cnt++;
      return;
    }
    o=t[o].ch[v>t[o].v];
  }
  o=newnode(v);
  if(f)
    t[f].ch[v>t[f].v]=o;
  else root=o;
  t[o].fa=f;
  FIX(o);
}
template<class _Tp>
void Treap<_Tp>::Delete(_Tp v){
  int o=root;
  while(o&&t[o].v!=v){
    o=t[o].ch[t[o].v<v];
  }
  if(!o)
    return;
  if(t[o].cnt>1){
    t[o].cnt--;
    for(int i=o;i;i=t[i].fa)
      t[i].sz--;
    return;
  }
  int d=o,g=0;
  if(t[o].ch[0]&&t[o].ch[1]){
    d=t[o].ch[1];
    while(t[d].ch[0])
      d=t[d].ch[0];
  }
  g=t[d].ch[!t[d].ch[0]];
  t[g].fa=t[d].fa;
  if(!t[d].fa)
    root=g;
  else t[t[d].fa].ch[WhCh(d)]=g;
  if(o!=d){
    t[o].v=t[d].v;
    t[o].cnt=t[d].cnt;
  }
  for(int i=t[d].fa;i;i=t[i].fa)
    t[i].sz--;
  for(int i=t[d].fa;i&&t[d].cnt>1&&i!=o;i=t[i].fa){
    t[i].sz-=t[d].cnt;
    t[i].sz++;
  }
  FIX(g);
  recybin.push(d);
}
template<class _Tp>
int Treap<_Tp>::Rank(_Tp v){
  Insert(v);
  int tmp=0,sum=0;
  int o=root;
  for(;o;){
    tmp=t[t[o].ch[0]].sz;
    if(v==t[o].v)
      break;
    else{
      if(v<t[o].v)
        o=t[o].ch[0];
      else{
        sum+=tmp+t[o].cnt,
        o=t[o].ch[1];
      }
    }
  }
  Delete(v);
  return sum+tmp+1;
}
template<class _Tp>
_Tp Treap<_Tp>::kth(int k){
  int tmp;
  int o=root;
  for(;o;){
    tmp=t[t[o].ch[0]].sz;
    if(tmp+1<=k&&k<=tmp+t[o].cnt)
      break;
    else{
      if(k<=tmp)
        o=t[o].ch[0];
      else{
        k-=tmp+t[o].cnt;
        o=t[o].ch[1];
      }
    }
  }
  return t[o].v;
}
template<class _Tp>
_Tp Treap<_Tp>::Successor(_Tp v){
  _Tp res;
  int o=root;
  for(;o;){
    if(t[o].v>v){
      res=t[o].v,
      o=t[o].ch[0];
    }
    else o=t[o].ch[1];
  }
  return res;
}
template<class _Tp>
_Tp Treap<_Tp>::Precursor(_Tp v){
  _Tp res;
  int o=root;
  for(;o;){
    if(t[o].v<v){
      res=t[o].v;
      o=t[o].ch[1];
    }
    else o=t[o].ch[0];
  }
  return res;
}

#endif
