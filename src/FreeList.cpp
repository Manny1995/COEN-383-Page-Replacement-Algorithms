#ifndef FREELIST_CPP
#define FREELIST_CPP

#include "FreeList.h"

#define FREE_LIST_SIZE 100

// ---------------------------------------------

FreeList::FreeList() {
    
    this->head = NULL;
    this->tail = head;
    
    for (int i = 0 ; i < FREE_LIST_SIZE ; ++i) {
        
        Page* newPage = new Page(i);

        if (head == NULL) {
            head = newPage;
            tail = head;
        } else {
            tail->next = newPage;
            tail = tail->next;
        }
        tail->next = NULL;
    }
    
    tail->next = NULL;
    
}


Page* FreeList::getFreePage() {
    
    Page* currentPage = this->head;
    
    while (currentPage != NULL) {
        
        // Page not being used by a process
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

Page* FreeList::getPageWithId(int id) {
    Page *cur = this->head;
    while (cur != NULL) {
        if (cur->pageID == id) {
            return cur;
        }
        
        cur=cur->next;
    }
    
    cerr << "id " << id << " is not in the freelist" << endl;
    return NULL;
}


#endif
