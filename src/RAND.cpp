#ifndef RAND_CPP
#define RAND_CPP

#include "RAND.h"

RAND::RAND() {
    replacerID = "RAND";
}

Page* RAND::evictPage(list<Page*> &pageList) {
    
    
    int displacement = rand() % pageList.size();
    list<Page*>::iterator iter = pageList.begin();
    
    advance(iter,displacement);
    Page* randPage = *iter;
    
    // check if usage is correct
    pageList.erase(iter);

    return randPage;
    
}

#endif
