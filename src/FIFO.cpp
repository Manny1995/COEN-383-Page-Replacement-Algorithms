#ifndef FIFO_CPP
#define FIFO_CPP

#include "FIFO.h"

FIFO::FIFO() {
    
}

Page *FIFO::evictPage(PageList *pList) {
    Page *head = pList->deleteHead();
    return head;
}



#endif
