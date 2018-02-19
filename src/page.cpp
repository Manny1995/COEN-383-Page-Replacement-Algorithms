#ifndef PAGE_CPP
#define PAGE_CPP

#include "Page.h"
#include <sstream>

Page::Page() {
    this->identifier = "NO ID";
    this->pageID = -1;
    this->lastTimeReferenced = -1;
    this->timesReferenced = 0;
    this->processID = -1;
    this->next = NULL;
}

Page::Page(int i) {
    
    // Page();
    
    this->identifier = "NO ID";
    this->pageID = i;
    this->lastTimeReferenced = -1;
    this->timesReferenced = 0;
    this->processID = -1;
    this->next = NULL;
    
    stringstream ss;
    ss << "PG" << i;
    
    this->identifier = ss.str();
}

void Page::assignProcessOwner(Process* newOwner, int newID) {
    this->pageID = newID;
    this->refCount++;
    this->processID = newOwner->pnum;
}

void Page::removeProcessOwner() {
    this->identifier = "NO ID";
    this->pageID = -1;
    this->lastTimeReferenced = -1;
    this->timesReferenced = 0;
    this->processID = -1;
}

#endif
