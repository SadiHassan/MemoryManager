#include<list>
#include "HeapNode.h"
using namespace std;

class FreeList{

private:

  list<HeapNode*> _freelist;
  list<HeapNode*>::iterator it;
  int size_arr[10002];
  void init(int numBytes);
  int allocate(int numBytes);
  void free(int address);
  void stat();

  friend class Heap;
};
