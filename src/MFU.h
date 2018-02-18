#ifndef MFU_H
#define MFU_H

#include "PageReplacer.h"
#include "FreeList.h"

class MFU : public PageReplacer {
    
public:
    Page *evictPage(list<Page*> &pageList);
    MFU();
    
};

#endif
