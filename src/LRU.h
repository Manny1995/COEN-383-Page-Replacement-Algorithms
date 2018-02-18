
#ifndef LRU_H
#define LRU_H

#include "PageReplacer.h"
#include "FreeList.h"

class LRU : public PageReplacer {
    
public:
    Page *evictPage(list<Page*> &pageList);
    LRU();

};


#endif
