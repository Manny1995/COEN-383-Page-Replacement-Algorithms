#ifndef FREELIST_H
#define FREELIST_H

#include <iostream>
#include <string>

#include "Process.h"

#include "Page.h"

using namespace std;

class Page;

// class Process;

/*
class Page {
    
public:
    
    string identifier;
    int pageID;
    int refCount;
    int processID;
    Page *next;

    Page() {
        this->identifier = "NO ID";
        this->pageID = -1;
        this->refCount = 0;
        this->processID = -1;
        this->next = NULL;
    }
    
    void assignProcessOwner(Process* newOwner, int newID) {
        this->pageID = newID;
        this->refCount++;
        this->processID = newOwner->pnum;
    }

    // Takes in a page size in MB
    Page(string identifier) {
        Page();
        this->identifier = identifier;
    }
    
};
*/

class FreeList {
    
public:
    
    Page* head;
    Page* tail;
    
    // utility functions
    Page* getFreePage();
    bool hasEnoughFreePages();
    int numberOfFreePages();
    
    void print();
    
    // constructor
    FreeList();
    
};







// This will be used by the free list and the processes
/*
class PageList {

public:
    Page *head;
    Page *tail;

    PageList();

    // I know that this is inefficient, but it beats keeping it in track and updating it as a variable :)
    // - Dat O(n) runtime tho! :D
    int getSize();
    
    void appendPageWithSize(int pSize);
    void appendPage(Page *newPage);
    
    
    // Shifts the page to the back
    // NEEDED FOR LRU
    void shiftPageToBack(int pagePos);

    // Need this for random choice, and for sending to back
    Page* getPageAtIndex(int index);
    
    // Deletes the head of the page
    // NEEDED TO EVICT FOR LRU AND FIFO
    Page* deleteHead();
    
    // Deletes the tail of the page
    // NEEDED TO EVICT FOR MRU
    Page* deleteTail();
    
    Page *getPageAtPosition(int pos);
    bool hasFreePages();

    // By default gets the first 4 free pages
    Page *getFreePages();
    
    
    Page *findPage(string identifier);
    
    void appendPageList(PageList *pList);


};
 */

#endif
