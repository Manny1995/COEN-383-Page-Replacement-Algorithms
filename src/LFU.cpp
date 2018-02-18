#ifndef LFU_CPP
#define LFU_CPP

#include "LFU.h"

LFU::LFU() {
    replacerID = "LFU";
}

Page* LFU::evictPage(list<Page*> &pageList) {
    
    list<Page*>::iterator iter;
    list<Page*>::iterator targetPagePosition;
    Page* currentPage;
    Page* lfuPage;
    int lfuCount = INT_MAX;
    
    for (iter = pageList.begin(); iter != pageList.end(); ++iter) {
        
        currentPage = *iter;
        
        if (currentPage->timesReferenced < lfuCount) {
            lfuPage = currentPage;
            lfuCount = currentPage->timesReferenced;
            targetPagePosition = iter;
        }
        
    }
    
    // check if usage is correct
    pageList.erase(targetPagePosition);
    
    return lfuPage;
    
}



#endif
