#ifndef MFU_H
#define MFU_H

#include "PageReplacer.h"
#include "PageList.h"

class MFU : public PageReplacer {
    
public:
    Page *evictPage(list<Page*> &pageList);
    MFU();
    
};

#endif
