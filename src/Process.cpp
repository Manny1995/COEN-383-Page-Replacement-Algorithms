#ifndef PROCESS_CPP
#define PROCESS_CPP

#include "Process.h"

Process::Process(string pName, int pPageSize, int jArrivalTime, int jServiceDuration) {
    this->pid = pName;
    this->pageSize = pPageSize;
    this->arrivalTime = jArrivalTime;
    this->serviceDuration = jServiceDuration;
}



#endif
