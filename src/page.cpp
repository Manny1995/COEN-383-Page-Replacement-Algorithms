#include "page.h"

Page::Page() {
    this->identifier = "NO ID";
    this->pageID = -1;
    this->lastTimeReferenced = -1;
    this->timesReferenced = 0;
    this->processID = -1;
    this->next = NULL;
}

Page::Page(string identifier) {
    Page();
    this->identifier = identifier;
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
