#ifndef __TALGO__
#define __TALGO__

// TTL库
#include"ioPFL.hpp"
#include"Graph.hpp"
#include"Heap.hpp"
#include"RBTree.hpp"
#include"Treap.hpp"

// STL库
#include<map>
#include<string>
#include<cstring>
#include<iostream>

// 高级调试功能
#define proDEBUG
//#define Linux
#ifdef proDEBUG
//#define WALL
#endif
#ifdef proDEBUG
 #ifndef Linux
  #include<windows.h>
 #endif
  std::map<std::string,int> PRINT_TAG_helper_map;
 #ifndef Linux
  void PRINT_TAG(std::string s,int k=-1){
    if(k!=-1)
      PRINT_TAG_helper_map[s]=k;
    else PRINT_TAG_helper_map[s]++;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(10<<4));
    std::cerr << s << " TAG " << PRINT_TAG_helper_map[s] << '.';
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    std::cerr << '\n';
  }
  #define SetLog() (SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(FOREGROUND_GREEN|FOREGROUND_INTENSITY)),terr << "Hit Line " << __LINE__ << " in " << __FUNCTION__ << ".\n",SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7))
  #define Assert(code) (SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY|BACKGROUND_RED)),terr << "At Line " << __LINE__ << " in Function[" << __FUNCTION__ << "] ,\nError code: " << (code) << ".\n",SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7),terr << "Press any key to exit . . .\n\n",system("pause > nul"));exit(0)
 #else
  void PRINT_TAG(std::string s,int k=-1){
    if(k!=-1)
      PRINT_TAG_helper_map[s]=k;
    else PRINT_TAG_helper_map[s]++;
    std::cerr << s << " TAG " << PRINT_TAG_helper_map[s] << ".\n";
  }
  #define SetLog(code) (terr << "Hit Line " << __LINE__ << " in " << __FUNCTION__ << " \n")
  #define Assert(code) (terr << "At Line " << __LINE__ << " in " << __FUNCTION__ << "\nError code: " << (code) << " \n",*((char *)0)=1)
 #endif
#else
  #define SetLog(code) (terr << "Hit Line " << __LINE__ << " in " << __FUNCTION__ << " \n")
  #define Assert(code) (terr << "At Line " << __LINE__ << " in " << __FUNCTION__ << "\nError code: " << (code) << " \n",*((char *)0)=1)
#endif

// 简化声明
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef std::pair<int,int> pii;
//typedef IOmem<short *> shortArr;
//typedef IOmem<unsigned short *> ushortArr;
//typedef IOmem<int *> intArr;
//typedef IOmem<unsigned int *> uintArr;
//typedef IOmem<long long *> llArr;
//typedef IOmem<unsigned long long *> ullArr;

// 自定义量及类
int inf,uinf;
ll llinf,ullinf;
namespace INIT{
  class Init{
   public:
    Init(){
      memset(&inf,0x3f,sizeof(inf));
      memset(&uinf,0xc0,sizeof(uinf));
      memset(&llinf,0x3f,sizeof(llinf));
      memset(&ullinf,0xc0,sizeof(ullinf));
    }
  }init;
}
ull power(ull a,ull k,ull p){
  ull res=1;
  for(;k>0;k>>=1,a=(ull(a))*a%p)
    if(k&1)
      res=(ull(res))*a%p;
  return res;
}
/*
class complex{
 private:
  double Reality,Imagine;
 public:
  inline double R(){
    return Reality;
  }
  inline double I(){
    return Imagine;
  }
};
*/

#endif
