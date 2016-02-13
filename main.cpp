#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include "Heap.h"
#include "misc.h"
using namespace std;

int main(){

  freopen("trace1.txt","r",stdin);

  Heap* heap = new Heap(HEAP_SIZE);
  int index, size;
  string firstParameter;


  int total_allocated = 0, res;
  int arr[1001];

  memset(arr,-1,sizeof(arr));

  while(cin>>firstParameter){

    if(firstParameter=="a"){
        cin>>index>>size;
        arr[index] = heap->allocate(size);
    }

    else if(firstParameter=="f"){
        cin>>index;
        if(arr[index]>=0)
        heap->free(arr[index]);
    }
    else break;
  }

  heap->stat();

  return 0;
}
