#ifndef GENERATOR_H
#define GENERATOR_H

#include "Process.h"
#include "FreeList.h"


#include <vector>

 
using namespace std;

namespace generator {
	
    string getProcessName(int pNum);

    Process *generateRandomProcess(int pNum);

    bool processComp(Process *p, Process *q);
    
    // Generates a process list and sorts it by arrival time
    vector<Process *> generateProcessList();

}

#endif
