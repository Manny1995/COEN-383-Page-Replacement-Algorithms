#ifndef FREELIST_CPP
#define FREELIST_CPP

#include "FreeList.h"

#define FREE_LIST_SIZE 100

// ---------------------------------------------

FreeList::FreeList() {
    
    this->head = NULL;
    this->tail = head;
    
    for (int i = 0 ; i < FREE_LIST_SIZE ; ++i) {
        
        Page* newPage = new Page();
        
        if (head == NULL) {
            head = newPage;
            tail = head;
        } else {
            tail->next = newPage;
            tail = tail->next;
        }
        
    }
    
    tail->next = NULL;
    
}


Page* FreeList::getFreePage() {
    
    Page* currentPage = this->head;
    
    while (currentPage != NULL) {
        if (currentPage->processID < 0) {
            return currentPage;
        }
        currentPage = currentPage->next;
    }
    
    return NULL;
    
}

bool FreeList::hasEnoughFreePages() {
    
    return numberOfFreePages() >= 4;
    
}

int FreeList::numberOfFreePages() {
    
    Page* currentPage = this->head;
    int numberOfFreePages = 0;
    
    while (currentPage != NULL) {
        if (currentPage->processID < 0) {
            ++numberOfFreePages;
        }
        currentPage = currentPage->next;
    }
    
    return numberOfFreePages;
    
}


#endif
