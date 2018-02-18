#ifndef LFU_H
#define LFU_H

#include "PageReplacer.h"
#include "FreeList.h"

class LFU : public PageReplacer {
    
public:
    Page *evictPage(list<Page*> &pageList);
    LFU();
    
};

#endif
