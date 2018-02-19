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

void Page::assignProcessOwner(Process* newOwner, int newID, int timeAssigned) {
//    We should not have this!  PageID is always the same for a page (from 0 to 100)
//    this->pageID = newID;
    
    // times referenced will be refreshed by the new tie
    this->timesReferenced = 1;
    this->processID = newOwner->pnum;
    
    this->lastTimeReferenced = timeAssigned;
}

// only remove last time referenced, times reference, and processID
void Page::removeProcessOwner() {
    this->lastTimeReferenced = -1;
    this->timesReferenced = 0;
    this->processID = -1;
}

#endif
