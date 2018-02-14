#ifndef JOB_H
#define JOB_H

#include <string>
#include <iostream>

using namespace std;


class Job {

	public:
		string processName;
		int pageSize;
		int arrivalTime;
		int serviceDuration;

		void Job(string pName, pPageSize, jArrivalTime, jServiceDuration) {
			this->processName = pName;
			this->pageSize = pPageSize;
			this->arrivalTime = jArrivalTime;
			this->serviceDuration = jServiceDuration;
		}
	
};



#endif