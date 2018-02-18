#ifndef PAGE_H
#define PAGE_H

#include <string>

#include "Process.h"

using namespace std;

class Process;

class Page {
    
public:
    
    string identifier;
    int pageID;
    int refCount;
    int processID;
    Page *next;
    
    void assignProcessOwner(Process* newOwner, int newID);
    void removeProcessOwner();
    
    /* Algorithm Specific Info */
    // used by LRU
    int lastTimeReferenced;         // time in ms
    
    // used by LFU/MFU
    int timesReferenced;            // count of times referenced
    
    Page();
    Page(string identifier);
    
    /*
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
     */
    
};

#endif
