#include"Matrix.hpp"
int n;
fMatrix M;
int main(){
  tin.SetFile("tmp.in");
  tout.SetFile("tmp.out");
  tin >> n >> M(n,n+1);
  terr << n << '\n';
  terr << M << '\n';
  terr << n << '\n';
  M.Gauss();
  tout << M;
  M.Eliminate();
  tout << M;
  terr << "fdshoufhuofshouaf\n";
  return 0;
}