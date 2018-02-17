#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>


#include "Process.h"
#include "PageList.h"


#include <vector>
#include <sstream>

#define FREELIST_SIZE 100

namespace generator {
	
	vector<Process *> generateProcessList() {
        vector<Process *> processList;
        
        
        return processList;
	}

	string getProcessName(int pNum) {
        stringstream ss;
        ss << "Proc-" << pNum;
        return ss.str();
	}
    
    string getPageName(int pNum) {
        stringstream ss;
        ss << "Page-" << pNum;
        return ss.str();
    }


	Process *generateRandomProcess(int pNum) {
		
        int sizeArr [] = {5, 11, 17, 31};
        
        int pSize = sizeArr[rand() % 4];
        
        // NOT SURE ABOUT THIS, ASSUMING BECAUSE WE RUN FOR A MINUTE?
        int arrivalTime = rand() % 60;
        
        int serviceDuration = rand() % 5;
        
        string pName = getProcessName(pNum);
        
        return new Process(pName, pSize, arrivalTime, serviceDuration);
	}


	// generates list of pages 100 initially for the 
	PageList *generateFreeList() {

        PageList *res = new PageList();
        for (int i = 0; i < FREELIST_SIZE; i++) {
            Page *newPage = new Page(getPageName(i));
            res->appendPage(newPage);
        }
        
		return res;
	}

}

#endif
