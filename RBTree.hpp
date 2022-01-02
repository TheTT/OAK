// Copyright (c) TheToror
#ifndef __RBTREE__
#define __RBTREE__

#include<stack>

namespace RBTree_Static{
  const int Array_Limit=100005;
}
template<class _Tp>
struct RBND{
  _Tp v;
  int sz,cnt;
  bool col;
  int fa,ch[2];
  RBND(){}
  RBND(_Tp v):v(v){
    sz=cnt=1;
    col=1;
    fa=ch[0]=ch[1]=0;
  }
};
template<class _Tp>
class RBT{
  private:
    RBND<_Tp> t[RBTree_Static::Array_Limit<<2];
    std::stack<int> recybin;
    int root,nodetop;
    void update(int);
    bool WhCh(int);
    int newnode(_Tp);
    void rotate(int,bool);
    void DRC(int);
    void DBC(int);
  public:
    RBT<_Tp>(){}
    void Insert(_Tp);
    void Delete(_Tp);
    int Rank(_Tp);
    _Tp kth(int);
    _Tp Successor(_Tp);
    _Tp Precursor(_Tp);
};

template<class _Tp>
void RBT<_Tp>::update(int o){
  t[o].sz=t[t[o].ch[0]].sz+t[t[o].ch[1]].sz+t[o].cnt;
}
template<class _Tp>
bool RBT<_Tp>::WhCh(int o){
  return t[t[o].fa].ch[1]==o;
}
template<class _Tp>
int RBT<_Tp>::newnode(_Tp v){
  int o;
  if(recybin.size()){
    o=recybin.top();
    recybin.pop();
  }
  else o=++nodetop;
  t[o]=RBND<_Tp>(v);
  return o;
}
template<class _Tp>
void RBT<_Tp>::rotate(int o,bool c){
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
void RBT<_Tp>::DRC(int o){
  while(t[t[o].fa].col){  // DRC-3
    int f=t[o].fa,gf=t[f].fa;
    bool wh=!WhCh(f);
    int ul=t[gf].ch[wh];
    if(t[ul].col){  // DRC 1/2
      t[f].col=t[ul].col=0;
      t[gf].col=1;
      o=gf;
    }
    else if(t[root].col)  // DRC-4
      t[root].col=0;
    else{
      if(o==t[f].ch[wh])  // DRC-2a
        rotate(o=f,!wh);
      else{  // DRC-2b
        t[gf].col=1;
        t[f].col=0;
        rotate(gf,wh);
      }
    }
  }
}
template<class _Tp>
void RBT<_Tp>::DBC(int o){
  while(o!=root&&!t[o].col){
    bool wh=!WhCh(o);
    int f=t[o].fa,ul=t[f].ch[wh];
    if(t[ul].col){
      t[ul].col=0;
      t[f].col=1;
      rotate(f,!wh);
      ul=t[f].ch[wh];
    }
    else{
      if(!t[t[ul].ch[0]].col&&!t[t[ul].ch[1]].col){
        t[ul].col=1;
        o=f;
      }
      else{
        if(!t[t[ul].ch[wh]].col){
          t[t[ul].ch[!wh]].col=0;
          t[ul].col=1;
          rotate(ul,wh);
          ul=t[f].ch[wh];
        }
        t[ul].col=t[f].col;
        t[t[ul].ch[wh]].col=t[f].col=0;
        rotate(f,!wh);
        break;
      }
    }
  }
  t[o].col=0;
}
template<class _Tp>
void RBT<_Tp>::Insert(_Tp v){
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
  DRC(o);
}
template<class _Tp>
void RBT<_Tp>::Delete(_Tp v){
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
  if(!t[d].col)
    DBC(g);
  recybin.push(d);
}
template<class _Tp>
int RBT<_Tp>::Rank(_Tp v){
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
_Tp RBT<_Tp>::kth(int k){
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
_Tp RBT<_Tp>::Successor(_Tp v){
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
_Tp RBT<_Tp>::Precursor(_Tp v){
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
