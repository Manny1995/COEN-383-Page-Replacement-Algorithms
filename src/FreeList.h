#ifndef FREELIST_H
#define FREELIST_H

#include <iostream>
#include <string>

#include "Process.h"

#include "Page.h"

using namespace std;

class Page;

class FreeList {
    
public:
    
    Page* head;
    Page* tail;
    
    // utility functions
    Page* getFreePage();
    bool hasEnoughFreePages();
    int numberOfFreePages();
    
    
    Page* getPageWithId(int id);
    
    void print();
    
    // constructor
    FreeList();
    
};


#endif
