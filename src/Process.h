#ifndef PROCESS_H
#define PROCESS_H

#include <list>

#include "FreeList.h"
#include "PageReplacer.h"
#include "Page.h"

using namespace std;

//class Page;
//class PageList;
class PageReplacer;

class Process {
    
public:
    
    string pid;
    int pnum;
    int size;               // 5, 11, 17, or 31 pages
    int serviceDuration;
    int arrivalTime;
    int startTime;          // default to -1 to indicate hasn't started yet
    
    int currentPage;
    
    list<Page*> pages;
    
    Process(string pName, int pNum, int pPageSize, int jArrivalTime, int jServiceDuration);
    
    int getNextPageIndex();
    bool referencePage(PageReplacer* replacer, Page *newPage, int timestamp, Page *evictedPage);
    void freePages();
    
};

#endif
