// Copyright (c) TheToror
#ifndef __HEAP__
#define __HEAP__

namespace Heap_Static{
  const int Array_Limit=1000006;
  template<class _Tp>
  class less{
  public:
    inline bool operator()(const _Tp &a,const _Tp &b){
      return a<b;
    }
  };
  template<class _Tp>
  class greater{
  public:
    inline bool operator()(const _Tp &a,const _Tp &b){
      return b<a;
    }
  };
  template<typename _Tp>
  inline void swap(_Tp &a,_Tp &b){
    _Tp c;
    c=a;
    a=b;
    b=c;
  }
}
template<class _Tp,class _Cmp=Heap_Static::less<_Tp> >
class Heap{
 #define F ((k)>>1)
 #define L ((k)<<1)
 #define R (((k)<<1)|1)
 private:
  int n,vt;
  int id[Heap_Static::Array_Limit];
  _Tp v[Heap_Static::Array_Limit];
  _Cmp cmp;
 public:
  Heap():n(0){}
  inline unsigned int size(){
    return n;
  }
  inline void clear(){
    n=vt=0;
  }
  template<typename _TpIt>
  void build(_TpIt S,_TpIt T){
    clear();
    for(_TpIt it=S;it!=T;++it,++n)
      v[id[n]=n]=*it;
    vt=n;
    for(int k=n;k>1;--k)
      if(cmp(v[id[F]],v[id[k]]))
        Heap_Static::swap(id[k],id[F]);
  }
  void push(_Tp x){
    v[id[++n]=++vt]=x;
    static int k;
    for(k=n;k>1&&cmp(v[id[F]],v[id[k]]);k=F)
      Heap_Static::swap(id[k],id[F]);
  }
  inline _Tp top(){
    return v[id[1]];
  }
  void pop(){
    Heap_Static::swap(id[1],id[n--]);
    if(n==0){
      clear();
      return;
    }
    static int k;
    for(k=1;R<=n;){
      if(cmp(v[id[k]],v[id[L]])){
        if(cmp(v[id[L]],v[id[R]])){
          Heap_Static::swap(id[k],id[R]);
          k=R;
        }
        else{
          Heap_Static::swap(id[k],id[L]);
          k=L;
        }
      }
      else if(cmp(v[id[k]],v[id[R]])){
        Heap_Static::swap(id[k],id[R]);
        k=R;
      }
      else break;
    }
    if(L==n&&cmp(v[id[k]],v[id[L]]))
      Heap_Static::swap(id[k],id[L]);
  }
  inline const _Tp &operator[](int u){
    return v[id[u]];
  }
 #undef L
 #undef R
 #undef F
};

#endif
