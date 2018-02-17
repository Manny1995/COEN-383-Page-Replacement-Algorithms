
#ifndef FIFO_H
#define FIFO_H

#include "PageReplacer.h"
#include "PageList.h"

class FIFO : public PageReplacer {

    public:
        Page *evictPage(PageList *page);
    
};

#endif
