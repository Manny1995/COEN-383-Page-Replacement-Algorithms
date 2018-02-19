#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>


#include "Process.h"
#include "FreeList.h"


#include <vector>
#include <sstream>
#include <algorithm>

#define FREELIST_SIZE 100
#define PROCESS_COUNT 150

using namespace std;

namespace generator {
	
	string getProcessName(int pNum) {
        stringstream ss;
        ss << "Proc-" << pNum;
        return ss.str();
	}
    

	Process *generateRandomProcess(int pNum) {
		
        int sizeArr [] = {5, 11, 17, 31};
        
        int pSize = sizeArr[rand() % 4];
        
        // NOT SURE ABOUT THIS, ASSUMING BECAUSE WE RUN FOR A MINUTE?
        // int arrivalTime = rand() % 60;
        int arrivalTime = rand() % 60000;    // units in ms
        
        int serviceDuration = ((rand() % 5) + 1) * 1000;
        
        string pName = getProcessName(pNum);
        
        return new Process(pName, pNum, pSize, arrivalTime, serviceDuration);
	}

    bool processComp(Process *p, Process *q) {
        if (p == NULL || q == NULL) {
            cerr << "SORTING NULL PROCESS THIS SHOULD NOT BE HAPPENING" << endl;
            return false;
        }
        
        return p->arrivalTime < q->arrivalTime;
    }
    
    // Generates a process list and sorts it by arrival time
    vector<Process *> generateProcessList() {
        
        vector<Process *> processList;
        
        for (int pageIndex = 0 ; pageIndex < PROCESS_COUNT ; ++pageIndex) {
            Process* newProcess = generator::generateRandomProcess(pageIndex);
            processList.push_back(newProcess);
        }
        
        sort(processList.begin(), processList.end(), processComp);
                
        return processList;
        
    }


}

#endif
