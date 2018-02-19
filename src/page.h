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
    int processID;
    Page *next;
    
    void assignProcessOwner(Process* newOwner, int newID, int timestamp);
    void removeProcessOwner();
    
    /* Algorithm Specific Info */
    // used by LRU
    int lastTimeReferenced;         // time in ms
    
    // used by LFU/MFU
    int timesReferenced;            // count of times referenced
    
    Page();
    Page(int i);
    
    
};

#endif
