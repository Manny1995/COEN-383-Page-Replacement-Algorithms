
#ifndef LRU_H
#define LRU_H

#include "PageReplacer.h"
#include "PageList.h"

class LRU : public PageReplacer {
    
public:
    Page *evictPage(list<Page*> &pageList);
    LRU();

};


#endif
