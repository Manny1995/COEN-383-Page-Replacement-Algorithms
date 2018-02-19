
#ifndef FIFO_H
#define FIFO_H

#include "PageReplacer.h"
#include "FreeList.h"

class FIFO : public PageReplacer {

public:
    FIFO();
    virtual Page* evictPage(list<Page*> &pageList);

};

//class PageReplacerFactory {
//
//    Page *evictPage(string algo) {
//
//    }
//};

#endif
