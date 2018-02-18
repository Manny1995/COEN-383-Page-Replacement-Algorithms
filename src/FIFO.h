
#ifndef FIFO_H
#define FIFO_H

#include "PageReplacer.h"
#include "FreeList.h"

class FIFO : public PageReplacer {

public:
    Page *evictPage(list<Page*> &pageList);
    FIFO();
    
};

#endif
