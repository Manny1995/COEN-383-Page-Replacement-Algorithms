
#ifndef PAGEREPLACER_CPP
#define PAGEREPLACER_CPP

#include "PageReplacer.h"

PageReplacer::PageReplacer() {
    replacerID = "No ID";
}

Page* PageReplacer::evictPage(list<Page*> &pageList){
    
    Page *res = NULL;
    
    if (replacerID == FIFO_IDENTIFIER) {
        res = evictFIFO(pageList);
    }
    else if (replacerID == LRU_IDENTIFIER) {
        res = evictLRU(pageList);
    }
    else if (replacerID == LFU_IDENTIFIER) {
        res = evictLFU(pageList);
    }
    else if (replacerID == RAND_IDENTIFIER) {
        res = evictRAND(pageList);
    }
    else if (replacerID == MFU_IDENTIFIER) {
        res = evictMFU(pageList);
    }
    
    return res;
    
    
}

Page *PageReplacer::evictFIFO(list<Page *> &pageList) {
    Page* firstPage = *(pageList.begin());
    pageList.pop_front();
    return firstPage;
}

Page *PageReplacer::evictLRU(list<Page *> &pageList) {
    list<Page*>::iterator iter;
    list<Page*>::iterator targetPagePosition;
    Page* currentPage;
    Page* lruPage = NULL;
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

Page *PageReplacer::evictLFU(list<Page *> &pageList) {
    list<Page*>::iterator iter;
    list<Page*>::iterator targetPagePosition;
    Page* currentPage;
    Page* lfuPage = NULL;
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

Page *PageReplacer::evictRAND(list<Page *> &pageList) {
    int displacement = rand() % pageList.size();
    list<Page*>::iterator iter = pageList.begin();
    
    advance(iter,displacement);
    Page* randPage = *iter;
    
    // check if usage is correct
    pageList.erase(iter);
    
    return randPage;
}
Page *PageReplacer::evictMFU(list<Page *> &pageList) {
    list<Page*>::iterator iter;
    list<Page*>::iterator targetPagePosition;
    Page* currentPage;
    Page* mfuPage = NULL;
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

PageReplacer::PageReplacer(string s) {
    replacerID = s;
}


#endif
