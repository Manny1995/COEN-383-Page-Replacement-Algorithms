// Immanuel Amirtharaj and Carlos Rivera
// JobList.h

#ifndef JOBLIST_H
#define JOBLIST_H

#include <iostream>
#include <string> 

using namespace std;

class Job {

	public:
		Job *next;
		string processName;
		int pageSize;
		int arrivalTime;
		int serviceDuration;
		void Job(string pName, int pPageSize, int jArrivalTime, int jServiceDuration);
	
};


// Whelp, we need a linked list for jobs :/
class JobList{

	public:
		Job *head;
		Job *tail;

		JobList(vector<Job *>);
		void appendJob(Job *);
		void finishJob();


};

#endif