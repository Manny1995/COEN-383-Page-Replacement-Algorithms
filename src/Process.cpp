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
}

bool Process::referencePage(PageReplacer* replacer) {
    
    if (pages.size() == size) {
        replacer->evictPage(pages);
        return false;
    } else {
        return true;
    }
    
}


#endif
