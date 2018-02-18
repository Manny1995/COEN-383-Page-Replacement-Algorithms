#ifndef RAND_H
#define RAND_H

#include "PageReplacer.h"
#include "FreeList.h"

class RAND : public PageReplacer {
    
public:
    Page *evictPage(list<Page*> &pageList);
    RAND();
    
};


#endif
