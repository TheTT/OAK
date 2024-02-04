// Copyright (c) TheToror
#include"oakio.h"

template<class _Tp>
IOmem<_Tp>::IOmem(){
  S=NULL;
  T=NULL;
}
template<class _Tp>
IOmem<_Tp>::IOmem(_Tp s,_Tp t){
  S=s;
  T=t;
  space[0]=' ';
  space[1]='\0';
  ender[0]='\n';
  ender[1]='\0';
}
template<class _Tp>
IOmem<_Tp>::IOmem(_Tp s,_Tp t,const char *Space,const char *Ender){
  S=s;
  T=t;
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

Input::Input(){
  BUF=new char[IBUFsize];
  S=T=BUF;
  IFile=stdin;
}
Input::~Input(){
  fclose(IFile);
  delete[] BUF;
}
void Input::SetFile(FILE *F_ptr,bool flag){
  S=T=BUF;
  if(flag)
    fclose(IFile);
  IFile=F_ptr;
}
void Input::SetFile(const char *F_path,bool flag){
  S=T=BUF;
  if(flag)
    fclose(IFile);
  IFile=fopen(F_path,"r");
  if(!IFile)
    IFile=NULL;
}
Input &Input::operator>>(char &c){
  if(S==T){
    S=BUF;
    T=S+fread(BUF,sizeof(char),IBUFsize,IFile);
  }
  if(S==T)
    c=EOF;
  else c=*(S++);
  return *this;
}
Input &Input::operator>>(unsigned char &c){
  if(S==T){
    S=BUF;
    T=S+fread(BUF,sizeof(char),IBUFsize,IFile);
  }
  if(S==T)
    c=(unsigned char)EOF;
  else c=(unsigned char)*(S++);
  return *this;
}
Input &Input::operator>>(short &x){
  static bool w;
  static char c;
  w=0;
  c='\0';
  x=0;
  while(*this >> c,w=((w&&c>='0'&&c<='9')||c=='-'),c<'0'||c>'9')
    if(c==EOF){
      if(w)
        x=(short)-x;
      return *this;
    }
  while(x=(short)(x*10+(c-'0')),*this >> c,c>='0'&&c<='9')
    if(c==EOF){
      if(w)
        x=(short)-x;
      return *this;
    }
  if(w)
    x=(short)-x;
  return *this;
}
Input &Input::operator>>(unsigned short &x){
  static char c;
  c='\0';
  x=0;
  while(*this >> c,c<'0'||c>'9')
    if(c==EOF)
      return *this;
  while(x=(unsigned short)(x*10+(c-'0')),*this >> c,c>='0'&&c<='9')
    if(c==EOF)
      return *this;
  return *this;
}
Input &Input::operator>>(int &x){
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
Input &Input::operator>>(unsigned int &x){
  static char c;
  c='\0';
  x=0;
  while(*this >> c,c<'0'||c>'9')
    if(c==EOF)
      return *this;
  while(x=x*10U+(unsigned int)(c-'0'),*this >> c,c>='0'&&c<='9')
    if(c==EOF)
      return *this;
  return *this;
}
Input &Input::operator>>(long long &x){
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
Input &Input::operator>>(unsigned long long &x){
  static char c;
  c='\0';
  x=0;
  while(*this >> c,c<'0'||c>'9')
    if(c==EOF)
      return *this;
  while(x=x*10ULL+(unsigned long long)(c-'0'),*this >> c,c>='0'&&c<='9')
    if(c==EOF)
      return *this;
  return *this;
}
Input &Input::operator>>(float &x){
  static bool w,j;
  static char c;
  static float k;
  w=j=0;
  c='\0';
  k=1.0;
  x=0.0;
  while(*this >> c,w=((w&&((c>='0'&&c<='9')||c=='.'))||c=='-'),j=((j&&c>='0'&&c<='9')||c=='.'),c<'0'||c>'9')
    if(c==EOF)
      return *this;
  if(!j)
    while(x=x*10.F+(float)(c-'0'),*this >> c,c>='0'&&c<='9')
      if(c==EOF){
        if(w)
          x=-x;
        return *this;
      }
  if(j||c=='.'){
    if(c=='.')
      *this >> c;
    while(k=k*0.1F,x+=k*(float)(c-'0'),*this >> c,c>='0'&&c<='9')
      if(c==EOF){
        if(w)
          x=-x;
        return *this;
      }
  }
  if(w)
    x=-x;
  return *this;
}
Input &Input::operator>>(double &x){
  static bool w,j;
  static char c;
  static double k;
  w=j=0;
  c='\0';
  k=1.0;
  x=0.0;
  while(*this >> c,w=((w&&((c>='0'&&c<='9')||c=='.'))||c=='-'),j=((j&&c>='0'&&c<='9')||c=='.'),c<'0'||c>'9')
    if(c==EOF)
      return *this;
  if(!j)
    while(x=x*10+(c-'0'),*this >> c,c>='0'&&c<='9')
      if(c==EOF){
        if(w)
          x=-x;
        return *this;
      }
  if(j||c=='.'){
    if(c=='.')
      *this >> c;
    while(k=k*0.1,x+=k*(c-'0'),*this >> c,c>='0'&&c<='9')
      if(c==EOF){
        if(w)
          x=-x;
        return *this;
      }
  }
  if(w)
    x=-x;
  return *this;
}
Input &Input::operator>>(long double &x){
  static bool w,j;
  static char c;
  static long double k;
  w=j=0;
  c='\0';
  k=1.0;
  x=0.0;
  while(*this >> c,w=((w&&((c>='0'&&c<='9')||c=='.'))||c=='-'),j=((j&&c>='0'&&c<='9')||c=='.'),c<'0'||c>'9')
    if(c==EOF)
      return *this;
  if(!j)
    while(x=x*10+(c-'0'),*this >> c,c>='0'&&c<='9')
      if(c==EOF){
        if(w)
          x=-x;
        return *this;
      }
  if(j||c=='.'){
    if(c=='.')
      *this >> c;
    while(k=k*0.1L,x+=k*(c-'0'),*this >> c,c>='0'&&c<='9')
      if(c==EOF){
        if(w)
          x=-x;
        return *this;
      }
  }
  if(w)
    x=-x;
  return *this;
}
Input &Input::operator>>(char *s){
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
Input &Input::operator>>(const IOmem<_Tp> &a){
    for(_Tp i=a.S;i!=a.T;++i)
      *this >> *i;
    return *this;
  }

InputBinary::InputBinary(){
  in=&tin;
}
void InputBinary::SetFile(FILE *F_ptr,bool flag){
  in->SetFile(F_ptr,flag);
}
void InputBinary::SetFile(const char *F_path,bool flag){
  FILE *tmp=fopen(F_path,"rb");
  in->SetFile(tmp,flag);
}
InputBinary &InputBinary::operator>>(char &c){
  (*in) >> c;
  return *this;
}
InputBinary &InputBinary::operator>>(unsigned char &c){
  (*in) >> c;
  return *this;
}
InputBinary &InputBinary::operator>>(char *s){
  static char c,*st;
  c='\0';
  st=s;
  st[0]='\0';
  if(c==EOF)
    return *this;
  while(*in >> c,c=='\0')
    if(c==EOF)
      return *this;
  while(*st=c,*(++st)='\0',*in >> c,c!=EOF&&c!='\0');
  return *this;
}
template<typename _Tp>
InputBinary &InputBinary::operator>>(const _Tp &Tx){
  unsigned char *it=(unsigned char *)&Tx;
  for(int i=0;i<sizeof(_Tp);i++,it++)
    (*in) >> *it;
  return *this;
}
template InputBinary &InputBinary::operator>> <short>(const short &Tx);
template InputBinary &InputBinary::operator>> <unsigned short>(const unsigned short &Tx);
template InputBinary &InputBinary::operator>> <int>(const int &Tx);
template InputBinary &InputBinary::operator>> <unsigned int>(const unsigned int &Tx);
template InputBinary &InputBinary::operator>> <long long>(const long long &Tx);
template InputBinary &InputBinary::operator>> <unsigned long long>(const unsigned long long &Tx);
template InputBinary &InputBinary::operator>> <float>(const float &Tx);
template InputBinary &InputBinary::operator>> <double>(const double &Tx);
template InputBinary &InputBinary::operator>> <long double>(const long double &Tx);

int Output::Flush(){
  if(!err){
    fwrite(BUF,sizeof(char),(unsigned long)(S-BUF),OFile);
    S=BUF;
  }
  return 0;
}
Output::Output(int ERR){
  if(ERR)
    BUF=new char[8];
  else BUF=new char[OBUFsize];
  S=BUF;
  T=BUF+OBUFsize;
  this->err=ERR;
  if(this->err)
    OFile=stderr;
  else OFile=stdout;
}
Output::~Output(){
  Flush();
  fclose(OFile);
  delete[] BUF;
}
void Output::SetFile(FILE *F_ptr,bool flag){
  Flush();
  if(flag)
    fclose(OFile);
  OFile=F_ptr;
}
void Output::SetFile(const char *F_path,bool flag){
  Flush();
  if(flag)
    fclose(OFile);
  OFile=fopen(F_path,"w");
  if(!OFile)
    OFile=NULL;
}
Output &Output::operator<<(const char &c){
  return err?(fwrite(&c,sizeof(char),1,OFile),*this):((S==T)?Flush():0,*S++=c,*this);
}
Output &Output::operator<<(const unsigned char &c){
  if(err)
    fwrite(&c,sizeof(char),1,OFile);
  else{
    if(S==T)Flush();
    *S++=(char)c;
  }
  return *this;
}
Output &Output::operator<<(const short &Tx){
  static char Sta[6];
  static int Top;
  static unsigned short x;
  Top=0;
  if(Tx<0){
    x=(unsigned short)-Tx;
    *this << '-';
  }
  else x=(unsigned short)Tx;
  do{
    Sta[Top++]=(char)(x%10^0x30);
  }while(x/=10);
  while(Top--)
    *this << Sta[Top];
  return *this;
}
Output &Output::operator<<(const unsigned short &Tx){
  static char Sta[6];
  static int Top;
  static unsigned short x;
  Top=0;
  x=Tx;
  do{
    Sta[Top++]=(char)(x%10^0x30);
  }while(x/=10);
  while(Top--)
    *this << Sta[Top];
  return *this;
}
Output &Output::operator<<(const int &Tx){
  static char Sta[12];
  static int Top;
  static unsigned int x;
  Top=0;
  if(Tx<0){
    x=(unsigned int)-Tx;
    *this << '-';
  }
  else x=(unsigned int)Tx;
  do{
    Sta[Top++]=(char)(x%10^0x30);
  }while(x/=10);
  while(Top--)
    *this << Sta[Top];
  return *this;
}
Output &Output::operator<<(const unsigned int &Tx){
  static char Sta[12];
  static int Top;
  static unsigned int x;
  Top=0;
  x=Tx;
  do{
    Sta[Top++]=(char)(x%10^0x30);
  }while(x/=10);
  while(Top--)
    *this << Sta[Top];
  return *this;
}
Output &Output::operator<<(const long long &Tx){
  static char Sta[20];
  static int Top;
  static unsigned long long x;
  Top=0;
  if(Tx<0){
    x=(unsigned long long)-Tx;
    *this << '-';
  }
  else x=(unsigned long long)Tx;
  do{
    Sta[Top++]=(char)(x%10^0x30);
  }while(x/=10);
  while(Top--)
    *this << Sta[Top];
  return *this;
}
Output &Output::operator<<(const unsigned long long &Tx){
  static char Sta[20];
  static int Top;
  static unsigned long long x;
  Top=0;
  x=Tx;
  do{
    Sta[Top++]=(char)(x%10^0x30);
  }while(x/=10);
  while(Top--)
    *this << Sta[Top];
  return *this;
}
Output &Output::operator<<(const float &Tx){
  static char Sta[12];
  static int Top;
  static unsigned int x;
  static float f;
  static const float eps=1.192092896e-07F;
  Top=0;
  if(Tx<0){
    x=(unsigned int)-Tx;
    f=(float)(-Tx-(float)x);
    *this << '-';
  }
  else{
    x=(unsigned int)Tx;
    f=(float)(Tx-(float)x);
  }
  if(f>1-eps){
    f=0.0;
    ++x;
  }
  do{
    Sta[Top++]=(char)(x%10^0x30);
  }while(x/=10);
  while(Top--)
    *this << Sta[Top];
  if(f<1-eps&&f>=eps){
    *this << '.';
    for(int i=1;i<=6&&f<1-eps&&f>=eps;i++){
      f=f*10.0F;
      *this << char(int(f+eps)^'0');
      f-=(float)((int)f);
    }
  }
  return *this;
}
Output &Output::operator<<(const double &Tx){
  static char Sta[20];
  static int Top;
  static unsigned int x;
  static double f;
  static const double eps=2.2204460492503131e-016;
  Top=0;
  if(Tx<0){
    x=(unsigned int)-Tx;
    f=-Tx-(double)x;
    *this << '-';
  }
  else{
    x=(unsigned int)Tx;
    f=Tx-x;
  }
  if(f>1-eps){
    f=0.0;
    ++x;
  }
  do{
    Sta[Top++]=(char)(x%10^0x30);
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
Output &Output::operator<<(const long double &Tx){
  static char Sta[20];
  static int Top;
  static unsigned long long x;
  static long double f;
  static const long double eps=2.2204460492503131e-016;
  Top=0;
  if(Tx<0){
    x=(unsigned long long)-Tx;
    f=-Tx-x;
    *this << '-';
  }
  else{
    x=(unsigned long long)Tx;
    f=Tx-x;
  }
  if(f>1-eps){
    f=0.0;
    ++x;
  }
  do{
    Sta[Top++]=(char)(x%10^0x30);
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
Output &Output::operator<<(const char *s){
  static char *t;
  t=(char *)(s);
  while(*t!='\0')
    *this << *t++;
  return *this;
}
template<typename _Tp>
Output &Output::operator<<(const IOmem<_Tp> &a){
  if(a.S==a.T)
    return *this;
  *this << *a.S;
  _Tp i=a.S;
  for(++i;i!=a.T;++i)
    *this << a.space << *i;
  *this << a.ender;
  return *this;
}

OutputBinary::OutputBinary(){
  out=&tout;
}
void OutputBinary::SetFile(FILE *F_ptr,bool flag){
  out->SetFile(F_ptr,flag);
}
void OutputBinary::SetFile(const char *F_path,bool flag){
  FILE *tmp=fopen(F_path,"wb");
  out->SetFile(tmp,flag);
}
OutputBinary &OutputBinary::operator<<(const char &c){
  (*out) << c;
  return *this;
}
OutputBinary &OutputBinary::operator<<(const unsigned char &c){
  (*out) << c;
  return *this;
}
OutputBinary &OutputBinary::operator<<(const char *s){
  (*out) << s << '\0';
  return *this;
}
template<typename _Tp>
OutputBinary &OutputBinary::operator<<(const _Tp &Tx){
  unsigned char *it=(unsigned char *)&Tx;
  for(int i=0;i<sizeof(_Tp);i++,it++)
    (*out) << *it;
  return *this;
}
template OutputBinary &OutputBinary::operator<< <short>(const short &Tx);
template OutputBinary &OutputBinary::operator<< <unsigned short>(const unsigned short &Tx);
template OutputBinary &OutputBinary::operator<< <int>(const int &Tx);
template OutputBinary &OutputBinary::operator<< <unsigned int>(const unsigned int &Tx);
template OutputBinary &OutputBinary::operator<< <long long>(const long long &Tx);
template OutputBinary &OutputBinary::operator<< <unsigned long long>(const unsigned long long &Tx);
template OutputBinary &OutputBinary::operator<< <float>(const float &Tx);
template OutputBinary &OutputBinary::operator<< <double>(const double &Tx);
template OutputBinary &OutputBinary::operator<< <long double>(const long double &Tx);

Input tin;
InputBinary tinb;
Output tout(0),terr(1);
OutputBinary toutb;
