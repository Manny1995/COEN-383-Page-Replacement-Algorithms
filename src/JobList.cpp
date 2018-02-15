// Immanuel Amirtharaj and Carlos Rivera

#ifndef JOBLIST_CPP
#define JOBLIST_CPP

#include "JobList.h"

#include <iostream>
#include <string> 

using namespace std;

void Job::Job(string pName, int pPageSize, int jArrivalTime, int jServiceDuration) {
	this->processName = pName;
	this->pageSize = pPageSize;
	this->arrivalTime = jArrivalTime;
	this->serviceDuration = jServiceDuration;
}


// JobList Methods

JobList::JobList() {
	this->head = NULL;
	this->tail = NULL;
} 

void JobList::appendJob(Job *newJob) {
	if (newJob == NULL) {
		cerr << "Trying to append a null job" << endl;
		return;
	}

	newJob->next = NULL;

	if (this->head == NULL) {
		this->head = newJob;
		this->tail = newJob;
	}
	else {
		this->tail->next = newJob;
		this->tail = newJob;
	}
}

// deletes the head
void JobList::finishJob() {

	if (this->head == NULL) {
		cout << "Job List empty" << endl;
		return;
	}

	Job *temp = this->head;
	this->head = this->head->next;

	if (this->tail == temp) {
		this->head = NULL;
		this->tail = NULL;
	}

	delete temp;
}


#endif