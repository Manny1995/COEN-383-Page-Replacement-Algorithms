
#ifndef PAGEREPLACER_H
#define PAGEREPLACER_H

#include <list>

#include "Page.h"
#include "FreeList.h"


#define FIFO_IDENTIFIER "fifo"
#define LRU_IDENTIFIER "lru"
#define LFU_IDENTIFIER "lfu"
#define RAND_IDENTIFIER "rand"
#define MFU_IDENTIFIER "mfu"


// gets called by the process class
class PageReplacer {

public:
    string replacerID;
    
    // Takes in a page list and returns the evicted page
    // virtual Page* evictPage(PageList *pageList);
    Page* evictPage(list<Page*> &pageList);
    Page *evictFIFO(list<Page *> &pageList);
    Page *evictLRU(list<Page *> &pageList);
    Page *evictLFU(list<Page *> &pageList);
    Page *evictRAND(list<Page *> &pageList);
    Page *evictMFU(list<Page *> &pageList);
    PageReplacer();
    PageReplacer(string s);
};



#endif
