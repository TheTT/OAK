// Copyright (c) TheToror
#ifndef __IOPFL__
#define __IOPFL__

#include<stdio.h>

const int IBUFsize(1<<20),OBUFsize(1<<18);
template<class _Tp>
class IOmem{
 private:
 public:
  _Tp S,T;
  char space[5],ender[5];
  IOmem():S(NULL),T(NULL){}
  IOmem(_Tp s,_Tp t):S(s),T(t){
    space[0]=' ';
    space[1]='\0';
    ender[0]='\n';
    ender[1]='\0';
  }
  IOmem(_Tp s,_Tp t,const char *Space,const char *Ender):S(s),T(t){
    static int len;
    len=0;
    while(Space[len]!='\0')
      len++;
    for(int i=0;i<=len;i++)
      space[i]=Space[i];
    len=0;
    while(Ender[len]!='\0')
      len++;
    for(int i=0;i<=len;i++)
      ender[i]=Ender[i];
  }
};
class Input{
 private:
  char BUF[IBUFsize],*S,*T;
  FILE *IFile;
 public:
  Input(){
    S=T=BUF;
    IFile=stdin;
  }
  ~Input(){
    fclose(IFile);
  }
  void SetFile(FILE *F_ptr){
    S=T=BUF;
    fclose(IFile);
    IFile=F_ptr;
  }
  void SetFile(const char *F_path){
    S=T=BUF;
    fclose(IFile);
    fopen_s(&IFile,F_path,"r");
  }
  Input &operator>>(char &c){
    return (c=((S==T)&&(S=BUF,T=S+fread(BUF,sizeof(char),IBUFsize,IFile)),(S==T)?EOF:*(S++)),*this);
  }
  Input &operator>>(short &x){
    static bool w;
    static char c;
    w=0;
    c='\0';
    x=0;
    while(*this >> c,w=((w&&c>='0'&&c<='9')||c=='-'),c<'0'||c>'9')
      if(c==EOF)
        return (w&&(x=-x),*this);
    while(x=x*10+(c-'0'),*this >> c,c>='0'&&c<='9')
      if(c==EOF)
        return (w&&(x=-x),*this);
    w&&(x=-x);
    return *this;
  }
  Input &operator>>(unsigned short &x){
    static char c;
    c='\0';
    x=0;
    while(*this >> c,c<'0'||c>'9')
      if(c==EOF)
        return *this;
    while(x=x*10+(c-'0'),*this >> c,c>='0'&&c<='9')
      if(c==EOF)
        return *this;
    return *this;
  }
  Input &operator>>(int &x){
    static bool w;
    static char c;
    w=0;
    c='\0';
    x=0;
    while(*this >> c,w=((w&&c>='0'&&c<='9')||c=='-'),c<'0'||c>'9')
      if(c==EOF)
        return (w&&(x=-x),*this);
    while(x=x*10+(c-'0'),*this >> c,c>='0'&&c<='9')
      if(c==EOF)
        return (w&&(x=-x),*this);
    w&&(x=-x);
    return *this;
  }
  Input &operator>>(unsigned int &x){
    static char c;
    c='\0';
    x=0;
    while(*this >> c,c<'0'||c>'9')
      if(c==EOF)
        return *this;
    while(x=x*10+(c-'0'),*this >> c,c>='0'&&c<='9')
      if(c==EOF)
        return *this;
    return *this;
  }
  Input &operator>>(long long &x){
    static bool w;
    static char c;
    w=0;
    c='\0';
    x=0;
    while(*this >> c,w=((w&&c>='0'&&c<='9')||c=='-'),c<'0'||c>'9')
      if(c==EOF)
        return (w&&(x=-x),*this);
    while(x=x*10+(c-'0'),*this >> c,c>='0'&&c<='9')
      if(c==EOF)
        return (w&&(x=-x),*this);
    w&&(x=-x);
    return *this;
  }
  Input &operator>>(unsigned long long &x){
    static char c;
    c='\0';
    x=0;
    while(*this >> c,c<'0'||c>'9')
      if(c==EOF)
        return *this;
    while(x=x*10+(c-'0'),*this >> c,c>='0'&&c<='9')
      if(c==EOF)
        return *this;
    return *this;
  }
  Input &operator>>(float &x){
    static bool w,j;
    static char c;
    static float k;
    w=j=0;
    c='\0';
    k=1.0;
    x=0.0;
    while(*this >> c,w=((w&&(c>='0'&&c<='9'||c=='.'))||c=='-'),j=((j&&c>='0'&&c<='9')||c=='.'),c<'0'||c>'9')
      if(c==EOF)
        return *this;
    if(!j)
      while(x=x*10+(c-'0'),*this >> c,c>='0'&&c<='9')
        if(c==EOF)
          return (w&&(x=-x),*this);
    if(j||c=='.'){
      if(c=='.')
        *this >> c;
      while(k=k*0.1,x+=k*(c-'0'),*this >> c,c>='0'&&c<='9')
        if(c==EOF)
          return (w&&(x=-x),*this);
    }
    w&&(x=-x);
    return *this;
  }
  Input &operator>>(double &x){
    static bool w,j;
    static char c;
    static double k;
    w=j=0;
    c='\0';
    k=1.0;
    x=0.0;
    while(*this >> c,w=((w&&(c>='0'&&c<='9'||c=='.'))||c=='-'),j=((j&&c>='0'&&c<='9')||c=='.'),c<'0'||c>'9')
      if(c==EOF)
        return *this;
    if(!j)
      while(x=x*10+(c-'0'),*this >> c,c>='0'&&c<='9')
        if(c==EOF)
          return (w&&(x=-x),*this);
    if(j||c=='.'){
      if(c=='.')
        *this >> c;
      while(k=k*0.1L,x+=k*(c-'0'),*this >> c,c>='0'&&c<='9')
        if(c==EOF)
          return (w&&(x=-x),*this);
    }
    w&&(x=-x);
    return *this;
  }
  Input &operator>>(long double &x){
    static bool w,j;
    static char c;
    static long double k;
    w=j=0;
    c='\0';
    k=1.0;
    x=0.0;
    while(*this >> c,w=((w&&(c>='0'&&c<='9'||c=='.'))||c=='-'),j=((j&&c>='0'&&c<='9')||c=='.'),c<'0'||c>'9')
      if(c==EOF)
        return *this;
    if(!j)
      while(x=x*10+(c-'0'),*this >> c,c>='0'&&c<='9')
        if(c==EOF)
          return (w&&(x=-x),*this);
    if(j||c=='.'){
      if(c=='.')
        *this >> c;
      while(k=k*0.1L,x+=k*(c-'0'),*this >> c,c>='0'&&c<='9')
        if(c==EOF)
          return (w&&(x=-x),*this);
    }
    w&&(x=-x);
    return *this;
  }
  Input &operator>>(char *s){
    static char c,*st;
    c='\0';
    st=s;
    st[0]='\0';
    if(c==EOF)
      return *this;
    while(*this >> c,c=='\0'||c==' '||c=='\n'||c=='\r')
      if(c==EOF)
        return *this;
    while(*st=c,*(++st)='\0',*this >> c,c!=EOF&&c!='\0'&&c!=' '&&c!='\n'&&c!='\r');
    return *this;
  }
  template<typename _Tp>
  Input &operator>>(const IOmem<_Tp> &a){
    for(_Tp i=a.S;i!=a.T;++i)
      *this >> *i;
    return *this;
  }
}tin;
class Output{
 private:
  char BUF[OBUFsize],*S,*T;
  FILE *OFile;
  bool err;
 public:
  int Flush(){
    if(!err){
      fwrite(BUF,sizeof(char),S-BUF,OFile);
      S=BUF;
    }
    return 0;
  }
  Output(int ERR){
    S=BUF;
    T=BUF+OBUFsize;
    if(this->err=ERR)
      OFile=stderr;
    else OFile=stdout;
  }
  ~Output(){
    Flush();
    fclose(OFile);
  }
  void SetFile(FILE *F_ptr){
    Flush();
    fclose(OFile);
    OFile=F_ptr;
  }
  void SetFile(const char *F_path){
    Flush();
    fclose(OFile);
    fopen_s(&OFile,F_path,"w");
  }
  Output &operator<<(const char &c){
    return err?(fwrite(&c,sizeof(char),1,OFile),*this):((S==T)?Flush():0,*S++=c,*this);
  }
  Output &operator<<(const short &Tx){
    static char Sta[6];
    static int Top;
    static unsigned short x;
    Top=0;
    if(Tx<0){
      x=-Tx;
      *this << '-';
    }
    else x=Tx;
    do{
      Sta[Top++]=(x%10^0x30);
    }while(x/=10);
    while(Top--)
      *this << Sta[Top];
    return *this;
  }
  Output &operator<<(const unsigned short &Tx){
    static char Sta[6];
    static int Top;
    static unsigned short x;
    Top=0;
    x=Tx;
    do{
      Sta[Top++]=(x%10^0x30);
    }while(x/=10);
    while(Top--)
      *this << Sta[Top];
    return *this;
  }
  Output &operator<<(const int &Tx){
    static char Sta[12];
    static int Top;
    static unsigned int x;
    Top=0;
    if(Tx<0){
      x=-Tx;
      *this << '-';
    }
    else x=Tx;
    do{
      Sta[Top++]=(x%10^0x30);
    }while(x/=10);
    while(Top--)
      *this << Sta[Top];
    return *this;
  }
  Output &operator<<(const unsigned int &Tx){
    static char Sta[12];
    static int Top;
    static unsigned int x;
    Top=0;
    x=Tx;
    do{
      Sta[Top++]=(x%10^0x30);
    }while(x/=10);
    while(Top--)
      *this << Sta[Top];
    return *this;
  }
  Output &operator<<(const long long &Tx){
    static char Sta[20];
    static int Top;
    static unsigned long long x;
    Top=0;
    if(Tx<0){
      x=-Tx;
      *this << '-';
    }
    else x=Tx;
    do{
      Sta[Top++]=(x%10^0x30);
    }while(x/=10);
    while(Top--)
      *this << Sta[Top];
    return *this;
  }
  Output &operator<<(const unsigned long long &Tx){
    static char Sta[20];
    static int Top;
    static unsigned long long x;
    Top=0;
    x=Tx;
    do{
      Sta[Top++]=(x%10^0x30);
    }while(x/=10);
    while(Top--)
      *this << Sta[Top];
    return *this;
  }
  Output &operator<<(const float &Tx){
    static char Sta[12];
    static int Top;
    static unsigned int x;
    static float f,eps=1e-3;
    Top=0;
    if(Tx<0){
      x=-Tx;
      f=-Tx-x;
      *this << '-';
    }
    else{
      x=Tx;
      f=Tx-x;
    }
    if(f>1-eps){
      f=0.0;
      ++x;
    }
    do{
      Sta[Top++]=(x%10^0x30);
    }while(x/=10);
    while(Top--)
      *this << Sta[Top];
    if(f<1-eps&&f>=eps){
      *this << '.';
      for(int i=1;i<=6&&f<1-eps&&f>=eps;i++){
        f=f*10.0;
        *this << char(int(f+eps)^'0');
        f-=int(f);
      }
    }
    return *this;
  }
  Output &operator<<(const double &Tx){
    static char Sta[20];
    static int Top;
    static unsigned int x;
    static double f,eps=1e-7;
    Top=0;
    if(Tx<0){
      x=-Tx;
      f=-Tx-x;
      *this << '-';
    }
    else{
      x=Tx;
      f=Tx-x;
    }
    if(f>1-eps){
      f=0.0;
      ++x;
    }
    do{
      Sta[Top++]=(x%10^0x30);
    }while(x/=10);
    while(Top--)
      *this << Sta[Top];
    if(f<1-eps&&f>=eps){
      *this << '.';
      for(int i=1;i<=15&&f<1-eps&&f>=eps;i++){
        f=f*10.0;
        *this << char(int(f+eps)^'0');
        f-=int(f);
      }
    }
    return *this;
  }
  Output &operator<<(const long double &Tx){
    static char Sta[20];
    static int Top;
    static unsigned int x;
    static long double f,eps=1e-9;
    Top=0;
    if(Tx<0){
      x=-Tx;
      f=-Tx-x;
      *this << '-';
    }
    else{
      x=Tx;
      f=Tx-x;
    }
    if(f>1-eps){
      f=0.0;
      ++x;
    }
    do{
      Sta[Top++]=(x%10^0x30);
    }while(x/=10);
    while(Top--)
      *this << Sta[Top];
    if(f<1-eps&&f>=eps){
      *this << '.';
      for(int i=1;i<=18&&f<1-eps&&f>=eps;i++){
        f=f*10.0;
        *this << char(int(f+eps)^'0');
        f-=int(f);
      }
    }
    return *this;
  }
  Output &operator<<(const char *s){
    static char *t;
    t=(char *)((long long)(s));
    while(*t!='\0')
      *this << *t++;
    return *this;
  }
  template<typename _Tp>
  Output &operator<<(const IOmem<_Tp> &a){
    if(a.S==a.T)
      return *this;
    *this << *a.S;
    _Tp i=a.S;
    for(++i;i!=a.T;++i)
      *this << a.space << *i;
    *this << a.ender;
    return *this;
  }
}tout(0),terr(1);
#endif
