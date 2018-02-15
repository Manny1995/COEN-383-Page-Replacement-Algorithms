
#include <iostream>


#include "Job.h"
#include "Process.h"
#include "PageList.h"


#include <vector>

namespace generator {
	
	vector<Process *> generateProcessList() {

	}

	string getProcessName(int pNum) {

	}


	// generates list of jobs sorted by arrival time
	vector<Job *> generateJobList(int numJobs) {

	}

	Job *generateRandomJob() {
		
		int processName;
		int pSize;
		int arrivalTime;
		int serviceDuration;

		return new Job(processName, pSize, arrivalTime, serviceDuration);
	}


	// generates list of pages 100 initially for the 
	PageList *generateFreeList() {

		PageList *res = new PageList(100, 1);
		return res;
	}

}