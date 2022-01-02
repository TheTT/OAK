#ifndef __MATRIX__
#define __MATRIX__

#include"ioPFL.hpp"

#include<string.h>

int P;
namespace Matrix_Static{
  const int Matrix_Limit=105;
}
class iMatrix{
 private:
 public:
  int n,m;
  long long a[Matrix_Static::Matrix_Limit][Matrix_Static::Matrix_Limit];
  iMatrix():n(0),m(0){}
  inline long long *operator[](int i){
    return a[i];
  }
  iMatrix &operator()(int n,int m){
    this->n=n;
    this->m=m;
    return *this;
  }
  iMatrix operator*(const iMatrix &b){
    static iMatrix c;
    if(m!=b.n){
      terr << "a.m != b.n\n";
      return c(0,0);
    }
    c.n=n;
    c.m=b.m;
    for(int i=1;i<=c.n;i++)
      for(int j=1;j<=c.m;j++){
        c[i][j]=0;
        for(int k=1;k<=m;k++)
          c[i][j]=(a[i][k]*b.a[k][j]+c[i][j])%P;
      }
    return c;
  }
  long long M(int x,int y){  // 代数余子式
    if(n!=m){
      terr << "m != n\n";
      return 0;
    }
    static iMatrix t;
    t.n=t.m=n-1;
    for(int i=1,p=1;i<n;p++,i++){
      if(p==x)
        p++;
      for(int j=1,q=1;j<n;q++,j++){
        if(q==y)
          q++;
        t[i][j]=a[p][q];
      }
    }
    if((x&1)^(y&1))
      return P-t.det();
    return t.det();
  }
  long long det(){
    if(n!=m){
      terr << "m != n\n";
      return 0;
    }
    static long long *it[Matrix_Static::Matrix_Limit],t[Matrix_Static::Matrix_Limit][Matrix_Static::Matrix_Limit];
    long long res=1,tmp,*edx;
    bool fl=0;
    memcpy(t,a,sizeof(t));
    for(int i=1;i<=n;i++)
      it[i]=t[i];
    for(int i=1,k;i<=n;i++){
      k=i;
      for(int j=i;j<=n;j++)
        if(it[j][i]){
          k=j;
          break;
        }
      if(it[k][i]==0)
        return 0;
      for(int j=k+1;j<=n;j++)
        if(it[j][i]&&it[j][i]<it[k][i])
          k=j;
      if(i!=k){
        edx=it[k];
        it[k]=it[i];
        it[i]=edx;
        fl^=1;
      }
      for(int j=i+1;j<=n;j++){
        if(it[j][i]>it[i][i]){
          edx=it[j];
          it[j]=it[i];
          it[i]=edx;
          fl^=1;
        }
        while(it[j][i]){
          tmp=it[i][i]/it[j][i];
          for(k=i;k<=n;k++)
            it[i][k]=(it[i][k]+(P-tmp)*it[j][k])%P;
          edx=it[j];
          it[j]=it[i];
          it[i]=edx;
          fl^=1;
        }
      }
      res=res*it[i][i]%P;
    }
    if(fl)
      return (P-res)%P;
    return (P+res)%P;
  }
  void Gauss(){  // TODO
    
  }
};
Input &operator>>(Input &in,iMatrix &m){
  for(int i=1;i<=m.n;i++)
    for(int j=1;j<=m.m;j++)
      in >> m[i][j];
  return in;
}
Output &operator<<(Output &out,iMatrix &m){
  for(int i=1;i<=m.n;i++){
    for(int j=1;j<=m.m;j++)
      out << (m[i][j]+P)%P << ' ';
    out << '\n';
  }
  return out;
}

class fMatrix{
 private:
 public:
  int n,m;
  double a[Matrix_Static::Matrix_Limit][Matrix_Static::Matrix_Limit];
  fMatrix():n(0),m(0){}
  inline double *operator[](int i){
    return a[i];
  }
  fMatrix &operator()(int n,int m){
    this->n=n;
    this->m=m;
    return *this;
  }
  fMatrix operator*(const fMatrix &b){
    fMatrix c;
    if(m!=b.n){
      terr << "a.m != b.n\n";
      return c(0,0);
    }
    c.n=n;
    c.m=b.m;
    for(int i=1;i<=c.n;i++)
      for(int j=1;j<=c.m;j++){
        c[i][j]=0;
        for(int k=1;k<=m;k++)
          c[i][j]=a[i][k]*b.a[k][j]+c[i][j];
      }
    return c;
  }
  double M(int x,int y){  // 代数余子式
    if(n!=m){
      terr << "m != n\n";
      return 0;
    }
    static fMatrix t;
    t.n=t.m=n-1;
    for(int i=1,p=1;i<n;p++,i++){
      if(p==x)
        p++;
      for(int j=1,q=1;j<n;q++,j++){
        if(q==y)
          q++;
        t[i][j]=a[p][q];
      }
    }
    if((x&1)^(y&1))
      return -t.det();
    return t.det();
  }
  double det(){
    if(n!=m){
      terr << "m != n\n";
      return 0;
    }
    static double *it[Matrix_Static::Matrix_Limit],t[Matrix_Static::Matrix_Limit][Matrix_Static::Matrix_Limit];
    double res=1,tmp,*edx;
    bool fl=0;
    memcpy(t,a,sizeof(t));
    for(int i=1;i<=n;i++)
      it[i]=t[i];
    for(int i=1,k;i<=n;i++){
      k=i;
      for(int j=i;j<=n;j++)
        if(it[j][i]){
          k=j;
          break;
        }
      if(it[k][i]==0)
        return 0;
      for(int j=k+1;j<=n;j++)
        if(it[j][i]&&it[j][i]<it[k][i])
          k=j;
      if(i!=k){
        edx=it[k];
        it[k]=it[i];
        it[i]=edx;
        fl^=1;
      }
      for(int j=i+1;j<=n;j++){
        if(it[j][i]>it[i][i]){
          edx=it[j];
          it[j]=it[i];
          it[i]=edx;
          fl^=1;
        }
        while(it[j][i]){
          tmp=it[i][i]/it[j][i];
          for(k=i;k<=n;k++)
            it[i][k]=it[i][k]-tmp*it[j][k];
          edx=it[j];
          it[j]=it[i];
          it[i]=edx;
          fl^=1;
        }
      }
      res=res*it[i][i];
    }
    if(fl)
      return -res;
    return res;
  }
  void Gauss(){  // FIXME
    double *tmp,*t[Matrix_Static::Matrix_Limit],d;
    for(int i=1;i<=n;i++)
      t[i]=a[i];
    for(int i=1,k;i<n;i++){
      k=-1;
      for(int j=1;j<=n;j++)
        if(t[j][j]!=0){
          k=j;
          break;
        }
      if(k==-1){
        terr << "Fail to Gauss\n";
        return;
      }
      tmp=t[i];
      t[i]=t[k];
      t[k]=tmp;
      for(int j=i+1;j<=n;j++)
        if(t[j][i]!=0){
          d=t[j][i]/t[i][i];
          for(k=1;k<=m;k++){
            t[j][k]-=a[i][k]*d;
            if(-1e-7<t[j][k]&&t[j][k]<1e-7)
              t[j][k]=0;
          }
        }
    }
  }
  void Eliminate(){
    for(int i=n;i>=1;i--){
      if(a[i][i]==0){
        terr << "No Solution\n";
        return;
      }
      for(int j=n+1;j<=m;j++)
        a[i][j]/=a[i][i];
      a[i][i]=1;
      for(int j=1;j<=i-1;j++){
        for(int k=n+1;k<=m;k++)
          a[j][k]-=a[i][k]*a[j][i];
        a[j][i]=0;
      }
    }
  }
};
Input &operator>>(Input &in,fMatrix &m){
  for(int i=1;i<=m.n;i++)
    for(int j=1;j<=m.m;j++)
      in >> m[i][j];
  return in;
}
Output &operator<<(Output &out,fMatrix &m){
  for(int i=1;i<=m.n;i++){
    for(int j=1;j<=m.m;j++)
      out << m[i][j] << ' ';
    out << '\n';
  }
  return out;
}

#endif
