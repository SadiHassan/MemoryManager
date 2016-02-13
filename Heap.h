#include "FreeList.h"

class Heap{

public:
  Heap(int numBytes);
  void init(int numBytes);
  int allocate(int numBytes);
  void free(int address);
  void stat();

private:

  FreeList freelistObject;
};

