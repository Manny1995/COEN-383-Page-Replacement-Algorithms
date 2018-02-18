#ifndef PROCESS_CPP
#define PROCESS_CPP

#include "Process.h"

Process::Process(string pName, int pNum, int pPageSize, int jArrivalTime, int jServiceDuration) {
    this->pid = pName;
    this->pnum = pNum;
    this->size = pPageSize;
    this->arrivalTime = jArrivalTime;
    this->startTime = -1;
    this->serviceDuration = jServiceDuration;
    
    this->currentPage = -1;
}

int Process::getNextPageIndex() {
    int choice = rand() % 10;
    int newPage = -1;
    if (choice <=6) {
        int neighborArray[] = {-1, 0, 1};
        int neighborChoice = rand() % 3;
        newPage = this->currentPage+=neighborArray[neighborChoice];
        
        // TODO - Make sure that we take a page that is not referenced by another one
        
        if (newPage < 0) {
            newPage = 0;
        }
    }
    else {
        newPage = newPage % 100;
    }
    return newPage;
}

bool Process::referencePage(PageReplacer* replacer) {
    
    this->currentPage = this->getNextPageIndex();
    
    for (auto page : this->pages) {
        if (page->pageID == this->currentPage) {
            page->refCount++;
            
            // todo, add a time
            return true;
        }
    }
    
    if (pages.size() == size) {
        replacer->evictPage(pages);
        return false;
    } else {
        return true;
    }
    
}

void Process::freePages() {
    
    list<Page*>::iterator iter;
    Page* currentPage;
    
    for (iter = pages.begin(); iter != pages.end(); ++iter) {
        
        currentPage = *iter;
        currentPage->removeProcessOwner();
        
    }
    
}

#endif
