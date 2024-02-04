// Copyright (c) TheToror
#ifndef OAKIO_H
#define OAKIO_H

#include<stdio.h>

static const int IBUFsize(1<<20),OBUFsize(1<<18);
template<class _Tp>
class IOmem{
 private:
  _Tp S,T;
  char space[5],ender[5];
 public:
  IOmem();
  IOmem(_Tp s,_Tp t);
  IOmem(_Tp s,_Tp t,const char *Space,const char *Ender);
};
class Input{
 private:
  char *BUF,*S,*T;
  FILE *IFile;
 public:
  Input();
  ~Input();
  void SetFile(FILE *F_ptr,bool flag=1);
  void SetFile(const char *F_path,bool flag=1);
  Input &operator>>(char &c);
  Input &operator>>(unsigned char &c);
  Input &operator>>(short &x);
  Input &operator>>(unsigned short &x);
  Input &operator>>(int &x);
  Input &operator>>(unsigned int &x);
  Input &operator>>(long long &x);
  Input &operator>>(unsigned long long &x);
  Input &operator>>(float &x);
  Input &operator>>(double &x);
  Input &operator>>(long double &x);
  Input &operator>>(char *s);
  template<typename _Tp>
  Input &operator>>(const IOmem<_Tp> &a);
};
class InputBinary{
 private:
  Input *in;
 public:
  InputBinary();
  void SetFile(FILE *F_ptr,bool flag=1);
  void SetFile(const char *F_path,bool flag=1);
  InputBinary &operator>>(char &c);
  InputBinary &operator>>(unsigned char &c);
  InputBinary &operator>>(char *s);
  template<typename _Tp>
  InputBinary &operator>>(const _Tp &Tx);
};
class Output{
 private:
  char *BUF,*S,*T;
  bool err;
 public:
  FILE *OFile;
  int Flush();
  Output(int ERR);
  ~Output();
  void SetFile(FILE *F_ptr,bool flag=1);
  void SetFile(const char *F_path,bool flag=1);
  Output &operator<<(const char &c);
  Output &operator<<(const unsigned char &c);
  Output &operator<<(const short &Tx);
  Output &operator<<(const unsigned short &Tx);
  Output &operator<<(const int &Tx);
  Output &operator<<(const unsigned int &Tx);
  Output &operator<<(const long long &Tx);
  Output &operator<<(const unsigned long long &Tx);
  Output &operator<<(const float &Tx);
  Output &operator<<(const double &Tx);
  Output &operator<<(const long double &Tx);
  Output &operator<<(const char *s);
  template<typename _Tp>
  Output &operator<<(const IOmem<_Tp> &a);
};
class OutputBinary{
 private:
  Output *out;
 public:
  OutputBinary();
  void SetFile(FILE *F_ptr,bool flag=1);
  void SetFile(const char *F_path,bool flag=1);
  OutputBinary &operator<<(const char &c);
  OutputBinary &operator<<(const unsigned char &c);
  OutputBinary &operator<<(const char *s);
  template<typename _Tp>
  OutputBinary &operator<<(const _Tp &Tx);
};

extern Input tin;
extern InputBinary tinb;
extern Output tout,terr;
extern OutputBinary toutb;
#endif
