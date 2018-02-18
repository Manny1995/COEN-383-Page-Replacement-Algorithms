#ifndef LRU_CPP
#define LRU_CPP

#include "LRU.h"

LRU::LRU() {
    replacerID = "LRU";
}

Page* LRU::evictPage(list<Page*> &pageList) {
    
    list<Page*>::iterator iter;
    list<Page*>::iterator targetPagePosition;
    Page* currentPage;
    Page* lruPage;
    int lruTime = INT_MAX;
    
    for (iter = pageList.begin(); iter != pageList.end(); ++iter) {
        
        currentPage = *iter;
        
        if (currentPage->lastTimeReferenced < lruTime) {
            lruPage = currentPage;
            lruTime = currentPage->lastTimeReferenced;
            targetPagePosition = iter;
        }
        
    }
    
    // check if usage is correct
    pageList.erase(targetPagePosition);
    
    return lruPage;
    
}



#endif
