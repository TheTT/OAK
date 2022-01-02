#ifndef __MATRIX_TREE__
#define __MATRIX_TREE__

#include"Matrix.hpp"

Matrix &operator<<(Matrix &a,const Graph &G){
  a.n=a.m=G.n;
  for(int u=1;u<=a.n;u++)
    for(int e=G.head[u],v;e;e=G.Next[e]){
      v=G.edge[e];
      a[v][v]=(a[v][v]+G.len[e]+P)%P;
      a[u][v]=(a[u][v]-G.len[e]+P)%P;
    }
  return a;
}
Matrix &operator<<(Matrix &a,const uGraph &G){
  a.n=a.m=G.n;
  for(int u=1;u<=a.n;u++)
    for(int e=G.head[u],v;e;e=G.Next[e]){
      v=G.edge[e];
      a[v][v]++;
      a[u][v]--;
    }
  return a;
}

#endif
