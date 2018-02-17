#ifndef FIFO_CPP
#define FIFO_CPP

#include "FIFO.h"

Page *FIFO::evictPage(PageList *pList) {
    Page *head = pList->deleteHead();
    return head;
}



#endif
