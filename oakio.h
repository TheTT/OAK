// Copyright (c) TheToror
#ifndef OAKIO_H
#define OAKIO_H

#include<stdio.h>

static const int IBUFsize(1<<20),OBUFsize(1<<18);
template<class _Tp>
class IOmem{
 private:
 public:
  _Tp S,T;
  char space[5],ender[5];
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
  void SetFile(FILE *F_ptr);
  void SetFile(const char *F_path);
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
  void SetFile(FILE *F_ptr);
  void SetFile(const char *F_path);
  InputBinary &operator>>(char &c);
  InputBinary &operator>>(unsigned char &c);
  InputBinary &operator>>(short &x);
  InputBinary &operator>>(unsigned short &x);
  InputBinary &operator>>(int &x);
  InputBinary &operator>>(unsigned int &x);
  InputBinary &operator>>(long long &x);
  InputBinary &operator>>(unsigned long long &x);
  InputBinary &operator>>(char *s);
};
class Output{
 private:
  char *BUF,*S,*T;
  FILE *OFile;
  bool err;
 public:
  int Flush();
  Output(int ERR);
  ~Output();
  void SetFile(FILE *F_ptr);
  void SetFile(const char *F_path);
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
  void SetFile(FILE *F_ptr);
  void SetFile(const char *F_path);
  OutputBinary &operator<<(const char &c);
  OutputBinary &operator<<(const unsigned char &c);
  OutputBinary &operator<<(const short &Tx);
  OutputBinary &operator<<(const unsigned short &Tx);
  OutputBinary &operator<<(const int &Tx);
  OutputBinary &operator<<(const unsigned int &Tx);
  OutputBinary &operator<<(const long long &Tx);
  OutputBinary &operator<<(const unsigned long long &Tx);
  OutputBinary &operator<<(const char *s);
};

extern Input tin;
extern InputBinary tinb;
extern Output tout,terr;
extern OutputBinary toutb;
#endif
