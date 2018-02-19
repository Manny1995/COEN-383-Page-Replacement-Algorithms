#ifndef PROCESS_CPP
#define PROCESS_CPP

#include "Process.h"

#define LOCALITY_THRESHOLD 7

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
    
    // change this to 6 before debugging
    if (choice <=7) {
        int neighborArray[] = {-1, 0, 1};
        int neighborChoice = rand() % LOCALITY_THRESHOLD;
        newPage = this->currentPage+=neighborArray[neighborChoice];
        
        // TODO - Make sure that we take a page that is not referenced by another one
        
        if (newPage < 0) {
            newPage = 0;
        }
    }
    else {
        newPage = rand() % 100;

    }
    
    if (newPage >= 100) {
        newPage = 99;
    }
    
    return newPage;
}

bool Process::referencePage(PageReplacer* replacer, Page *newPage, int timestamp, Page* &evictedPage) {
    
    evictedPage = NULL;
    
    this->currentPage = newPage->pageID;
    
    list<Page *>::iterator iter;

    for (iter = pages.begin(); iter != pages.end(); ++iter) {
        Page *page = *iter;
        if (page->pageID == this->currentPage) {
            page->timesReferenced++;
            page->lastTimeReferenced = 0;
            page->timesReferenced = timestamp;
            // todo, add a time
            return true;
        }
    }
    
    if (pages.size() == size) {
     //   int temp = pages.size();
        evictedPage = replacer->evictPage(pages);
      //  int temp2 = pages.size();
        
      //  cerr << temp << "   " << temp2 << endl;
        
        
    }
    
    newPage->timesReferenced = 1;
    newPage->processID = this->pnum;
    this->pages.push_back(newPage);
    return false;
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
