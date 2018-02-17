#ifndef PROCESS_H
#define PROCESS_H


#include "PageList.h"

class Process {
	public:
		string pid;
		int pageSize;
		int serviceDuration;
        int arrivalTime;
    
        PageList *pageList;
    
        Process(string pName, int pPageSize, int jArrivalTime, int jServiceDuration);
};

#endif
