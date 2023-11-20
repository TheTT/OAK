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
void Input::SetFile(FILE *F_ptr){
  S=T=BUF;
  fclose(IFile);
  IFile=F_ptr;
}
void Input::SetFile(const char *F_path){
  S=T=BUF;
  fclose(IFile);
  fopen_s(&IFile,F_path,"r");
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
    c=EOF;
  else c=*(S++);
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
  while(x=x*10+(c-'0'),*this >> c,c>='0'&&c<='9')
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
  while(x=x*10+(c-'0'),*this >> c,c>='0'&&c<='9')
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
  w&&(x=-x);
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
void InputBinary::SetFile(FILE *F_ptr){
  in->SetFile(F_ptr);
}
void InputBinary::SetFile(const char *F_path){
  in->SetFile(F_path);
}
InputBinary &InputBinary::operator>>(char &c){
  (*in) >> c;
  return *this;
}
InputBinary &InputBinary::operator>>(unsigned char &c){
  (*in) >> c;
  return *this;
}
InputBinary &InputBinary::operator>>(short &x){
  static unsigned char a,b;
  (*in) >> a >> b;
  x=(short)((unsigned short)a|((unsigned short)b<<8));
  return *this;
}
InputBinary &InputBinary::operator>>(unsigned short &x){
  static unsigned char a,b;
  (*in) >> a >> b;
  x=(unsigned short)((unsigned short)a|((unsigned short)b<<8));
  return *this;
}
InputBinary &InputBinary::operator>>(int &x){
  static unsigned char a,b,c,d;
  (*in) >> a >> b >> c >> d;
  x=(int)((unsigned int)a|((unsigned int)b<<8)|((unsigned int)c<<16)|((unsigned int)d<<24));
  return *this;
}
InputBinary &InputBinary::operator>>(unsigned int &x){
  static unsigned char a,b,c,d;
  (*in) >> a >> b >> c >> d;
  x=((unsigned int)a|((unsigned int)b<<8)|((unsigned int)c<<16)|((unsigned int)d<<24));
  return *this;
}
InputBinary &InputBinary::operator>>(long long &x){
  static unsigned char a,b,c,d,e,f,g,h;
  (*in) >> a >> b >> c >> d >> e >> f >> g >> h;
  x=(long long)((unsigned long long)a|((unsigned long long)b<<8)|((unsigned long long)c<<16)|((unsigned long long)d<<24)|((unsigned long long)e<<32)|((unsigned long long)f<<40)|((unsigned long long)g<<48)|((unsigned long long)h<<56));
  return *this;
}
InputBinary &InputBinary::operator>>(unsigned long long &x){
  static unsigned char a,b,c,d,e,f,g,h;
  (*in) >> a >> b >> c >> d >> e >> f >> g >> h;
  x=((unsigned long long)a|((unsigned long long)b<<8)|((unsigned long long)c<<16)|((unsigned long long)d<<24)|((unsigned long long)e<<32)|((unsigned long long)f<<40)|((unsigned long long)g<<48)|((unsigned long long)h<<56));
  return *this;
}
InputBinary &InputBinary::operator>>(char *s){
    (*in) >> s;
    return *this;
  }

int Output::Flush(){
  if(!err){
    fwrite(BUF,sizeof(char),S-BUF,OFile);
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
void Output::SetFile(FILE *F_ptr){
  Flush();
  fclose(OFile);
  OFile=F_ptr;
}
void Output::SetFile(const char *F_path){
  Flush();
  fclose(OFile);
  fopen_s(&OFile,F_path,"w");
}
Output &Output::operator<<(const char &c){
  return err?(fwrite(&c,sizeof(char),1,OFile),*this):((S==T)?Flush():0,*S++=c,*this);
}
Output &Output::operator<<(const unsigned char &c){
  return err?(fwrite(&c,sizeof(char),1,OFile),*this):((S==T)?Flush():0,*S++=c,*this);
}
Output &Output::operator<<(const short &Tx){
  static char Sta[6];
  static int Top;
  static unsigned short x;
  Top=0;
  if(Tx<0){
    x=(short)-Tx;
    *this << '-';
  }
  else x=Tx;
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
    x=-Tx;
    *this << '-';
  }
  else x=Tx;
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
    x=-Tx;
    *this << '-';
  }
  else x=Tx;
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
  static float f,eps=1.192092896e-07F;
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
  static double f,eps=2.2204460492503131e-016;
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
  static long double f,eps=2.2204460492503131e-016;
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
  t=(char *)((long long)(s));
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
void OutputBinary::SetFile(FILE *F_ptr){
  out->SetFile(F_ptr);
}
void OutputBinary::SetFile(const char *F_path){
  out->SetFile(F_path);
}
OutputBinary &OutputBinary::operator<<(const char &c){
  (*out) << c;
  return *this;
}
OutputBinary &OutputBinary::operator<<(const unsigned char &c){
  (*out) << c;
  return *this;
}
OutputBinary &OutputBinary::operator<<(const short &Tx){
  (*out) << (unsigned char)(Tx&0xFF) << (unsigned char)((Tx>>8)&0xFF);
  return *this;
}
OutputBinary &OutputBinary::operator<<(const unsigned short &Tx){
  (*out) << (unsigned char)(Tx&0xFF) << (unsigned char)((Tx>>8)&0xFF);
  return *this;
}
OutputBinary &OutputBinary::operator<<(const int &Tx){
  (*out) << (unsigned char)(Tx&0xFF) << (unsigned char)((Tx>>8)&0xFF) << (unsigned char)((Tx>>16)&0xFF) << (unsigned char)((Tx>>24)&0xFF);
  return *this;
}
OutputBinary &OutputBinary::operator<<(const unsigned int &Tx){
  (*out) << (unsigned char)(Tx&0xFF) << (unsigned char)((Tx>>8)&0xFF) << (unsigned char)((Tx>>16)&0xFF) << (unsigned char)((Tx>>24)&0xFF);
  return *this;
}
OutputBinary &OutputBinary::operator<<(const long long &Tx){
  (*out) << (unsigned char)(Tx&0xFF) << (unsigned char)((Tx>>8)&0xFF) << (unsigned char)((Tx>>16)&0xFF) << (unsigned char)((Tx>>24)&0xFF) << (unsigned char)((Tx>>32)&0xFF) << (unsigned char)((Tx>>40)&0xFF) << (unsigned char)((Tx>>48)&0xFF) << (unsigned char)((Tx>>56)&0xFF);
  return *this;
}
OutputBinary &OutputBinary::operator<<(const unsigned long long &Tx){
  (*out) << (unsigned char)(Tx&0xFF) << (unsigned char)((Tx>>8)&0xFF) << (unsigned char)((Tx>>16)&0xFF) << (unsigned char)((Tx>>24)&0xFF) << (unsigned char)((Tx>>32)&0xFF) << (unsigned char)((Tx>>40)&0xFF) << (unsigned char)((Tx>>48)&0xFF) << (unsigned char)((Tx>>56)&0xFF);
  return *this;
}
OutputBinary &OutputBinary::operator<<(const char *s){
  (*out) << s;
  return *this;
}

Input tin;
InputBinary tinb;
Output tout(0),terr(1);
OutputBinary toutb;
