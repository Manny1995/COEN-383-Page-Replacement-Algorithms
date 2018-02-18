#ifndef MFU_CPP
#define MFU_CPP

#include "MFU.h"

MFU::MFU() {
    replacerID = "MFU";
}

Page* MFU::evictPage(list<Page*> &pageList) {
    
    list<Page*>::iterator iter;
    list<Page*>::iterator targetPagePosition;
    Page* currentPage;
    Page* mfuPage;
    int mfuCount = INT_MIN;
    
    for (iter = pageList.begin(); iter != pageList.end(); ++iter) {
        
        currentPage = *iter;
        
        if (currentPage->timesReferenced > mfuCount) {
            mfuPage = currentPage;
            mfuCount = currentPage->timesReferenced;
            targetPagePosition = iter;
        }
        
    }
    
    // check if usage is correct
    pageList.erase(targetPagePosition);
    
    return mfuPage;
    
}

#endif
