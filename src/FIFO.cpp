#ifndef FIFO_CPP
#define FIFO_CPP

#include "FIFO.h"

FIFO::FIFO() {
    replacerID = "FIFO";
}

Page* FIFO::evictPage(list<Page*> &pageList) {
    
    Page* firstPage = *(pageList.begin());
    pageList.pop_front();
    return firstPage;
    
}



#endif
