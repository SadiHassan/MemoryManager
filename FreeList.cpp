#include<iostream>
#include<cstdio>
#include "FreeList.h"
#include "misc.h"
using namespace std;

void FreeList::init(int numBytes){

    HeapNode* p = new HeapNode(numBytes);
    p->startAddress = 0;
    p->endAddress = numBytes - 1;

    it = _freelist.begin();
    _freelist.insert( it , p );

    cout<<"Initializing...."<<endl;
    for (it = _freelist.begin(); it!=_freelist.end(); it++){
        cout<< (*it)->size <<" "<<(*it)->startAddress<<" "<<(*it)->endAddress<<endl;
    }
}

/*
This function will allocate space for an object. That means, it will make
some space unavailable in the freelist
*/

int FreeList::allocate(int numBytes){

    int temp_start, temp_size;
    bool allocated = false;

    HeapNode* newnode;

    for ( it = _freelist.begin(); it!=_freelist.end(); it++ ){

        if( (*it)->size >= numBytes){

            temp_start = (*it)->startAddress;
            temp_size = (*it)->size;

            if(temp_size - numBytes == 0 ) it = _freelist.erase(it);
            else {
                (*it)->startAddress = temp_start + numBytes ;
                (*it)->size = temp_size - numBytes ;
            }

            allocated = true;
            size_arr[temp_start] = numBytes;

            break;
        }
    }

    if(!allocated) return -1;

    else {
            /*
            cout<<"Printing list after insert..."<<endl;
            for ( it = _freelist.begin(); it!=_freelist.end(); it++ )
                cout<< (*it)->size <<" : "<<(*it)->startAddress<<" "<<(*it)->endAddress<<endl;

            cout<<"Print END..."<<endl;
            */
            return temp_start;
        }



}

void FreeList::free(int address){

    int sizeTobeAdded = size_arr[address];
    HeapNode *temp;
    bool memoryReclaimed = false;
    int temp_start, temp_end, temp_size;

    //Todo: If freeList contains single node!!!!


    if(_freelist.size()==0){ //Free list is empty
        temp = new HeapNode(sizeTobeAdded);
        temp->startAddress = 0;
        temp->endAddress = sizeTobeAdded-1;
        _freelist.insert(it,temp);
        return;
    }

    for ( it = _freelist.begin(); it!=_freelist.end(); it++ ){

        if( address+sizeTobeAdded-1 < (*it)->startAddress ){

            temp = new HeapNode(sizeTobeAdded);
            temp->startAddress = address;
            temp->endAddress = address+sizeTobeAdded-1;
            _freelist.insert(it,temp);
            //cout<<"I am here after insert : "<<sizeTobeAdded<<endl;

            memoryReclaimed = true;

             //Merge with FRONT of originally added node
                temp_start = (*it)->startAddress;
                temp_end =  (*it)->endAddress;
                temp_size =  (*it)->size;

                it--;

                if( (*it)->endAddress + 1 == temp_start ){
                    temp = new HeapNode( (*it)->size + temp_size );
                    temp->startAddress = (*it)->startAddress;
                    temp->endAddress = temp_end;
                    _freelist.insert(it,temp);
                    it = _freelist.erase(it);
                    it = _freelist.erase(it);
                }
                else it++;

              //Merge with PREV of originally added node
              if(_freelist.size()>1){

                it--;

                temp_start = (*it)->startAddress;
                temp_end =  (*it)->endAddress;
                temp_size =  (*it)->size;

                it--;

                if( (*it)->endAddress + 1 == temp_start ){
                    temp = new HeapNode(temp_size+(*it)->size);
                    temp->startAddress = (*it)->startAddress;
                    temp->endAddress = temp_end;
                    _freelist.insert(it,temp);
                    it = _freelist.erase(it);
                    it = _freelist.erase(it);
                }
              }
              //Merge Ends
            break;
        }
    }


    if(!memoryReclaimed){

         if( address+sizeTobeAdded <= HEAP_SIZE ){

            temp = new HeapNode(sizeTobeAdded);
            temp->startAddress = address;
            temp->endAddress = address+sizeTobeAdded-1;

            _freelist.push_back(temp);
            it = _freelist.end();
            memoryReclaimed = true;

            //Merge with previous
            if(_freelist.size()>1){

                it--;

                temp_start = (*it)->startAddress;
                temp_end =  (*it)->endAddress;
                temp_size =  (*it)->size;

                it--;

                if( (*it)->endAddress + 1 == temp_start ){
                    temp = new HeapNode(temp_size+(*it)->size);
                    temp->startAddress = (*it)->startAddress;
                    temp->endAddress = temp_end;
                    _freelist.insert(it,temp);
                    it = _freelist.erase(it);
                    it = _freelist.erase(it);
                }
            }
            //Merge Ends
         }
    }


    /*
    cout<<"Printing list after free..."<<endl;
    for ( it = _freelist.begin(); it!=_freelist.end(); it++ ){
        cout<<"size : "<< (*it)->size <<" "<<(*it)->startAddress<<" "<<(*it)->endAddress<<endl;
    }*/
  }
void FreeList::stat(){

    double totalFreeNode = 0.0;
    double totalFreeSpace = 0.0 ;

    for ( it = _freelist.begin(); it!=_freelist.end(); it++ ){
            totalFreeNode += 1 ;
            //cout<< (*it)->size <<" : "<< (*it)->startAddress <<" "<< (*it)->endAddress<<endl;
            totalFreeSpace = totalFreeSpace + (*it)->size;
    }
    cout<<"Status of Heap Size : "<<HEAP_SIZE<<" Bytes"<<endl;
    cout<<"Total Free Space : "<<totalFreeSpace<<" bytes"<<endl;
    cout<<"Number of Free Nodes in Heap : "<<totalFreeNode<<endl;
    cout<<"Average Size per node : "<<totalFreeSpace/totalFreeNode<<" bytes"<<endl;
    cout<<"Heap Used (%) : "<< ((HEAP_SIZE-totalFreeSpace)/HEAP_SIZE)*100<<endl;

}
