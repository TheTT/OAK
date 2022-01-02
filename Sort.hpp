namespace Sort_Static{
  template<typename _Tp>
  inline bool cmp(const _Tp &a,const _Tp &b){
    return a<b;
  }
}
template<typename _Tp>
void quick_sort(_Tp a[],int l,int r,bool cmp(const _Tp &,const _Tp &)=Sort_Static::cmp){
  static _Tp tmp,x;
  x=a[((r^l)<<2)%(r-l+1)+l];
  int i=l,j=r;
  do{
    while(cmp(a[i],x))
      i++;
    while(cmp(x,a[j]))
      j--;
    if(i<=j){
      tmp=a[i];
      a[i]=a[j];
      a[j]=tmp;
      i++;
      j--;
    }
  }while(i<=j);
  if(l<j)
    quick_sort(a,l,j,cmp);
  if(i<r)
    quick_sort(a,i,r,cmp);
}
template<typename _Tp>
void sort(_Tp a[],int l,int r,bool cmp(const _Tp &,const _Tp &)=Sort_Static::cmp){
  static _Tp tmp,x;
  if(r-l<=10){
    for(int i=l;i<r;i++)
      for(int j=i+1;j<=r;j++)
        if(cmp(a[j],a[i])){
          tmp=a[i];
          a[i]=a[j];
          a[j]=tmp;
        }
    return;
  }
  x=a[((r^l)<<2)%(r-l+1)+l];
  int i=l,j=r;
  do{
    while(cmp(a[i],x))
      i++;
    while(cmp(x,a[j]))
      j--;
    if(i<=j){
      tmp=a[i];
      a[i]=a[j];
      a[j]=tmp;
      i++;
      j--;
    }
  }while(i<=j);
  if(l<j)
    sort(a,l,j,cmp);
  if(i<r)
    sort(a,i,r,cmp);
}