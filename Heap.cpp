#include<iostream>
#include "Heap.h"

Heap::Heap(int numBytes){
    freelistObject.init(numBytes);
}

int Heap::allocate(int numBytes){

    freelistObject.allocate(numBytes);
  }

void Heap::free(int address){

    freelistObject.free( address );

  }

void Heap::stat(){

    freelistObject.stat();

}
