// Immanuel Amirtharaj, Carlos Rivera, Maxen Chung, Tasmine Hackson, Isaac Jorgenson
// run.cpp
// The main driver for this

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>



// Include page replacement Algorithms
#include "PageReplacer.h"

// Include generation
#include "generator.h"

// Include Pagelist and Page Classes
#include "FreeList.h"
#include "Page.h"


#include "printer.h"


#define NUM_EXPERIMENTS 5

#define STARTING_PAGE_ID 0

extern bool printAverage;
extern bool printProcesses;
extern bool printReferences;

bool printAverage;
bool printProcesses;
bool printReferences;

using namespace std;

void help() {
    cout << "Algorithms" << endl;
    cout << "all 	- run all 6 algorithms" << endl;
    cout << "fifo 	- first come first serve" << endl;
    cout << "lru 	- shortest job first" << endl;
    cout << "lfu 	- shortest time remaining" << endl;
    cout << "mfu	- round robin" << endl;
    cout << "rand	- highest priority first non-preemptive" << endl << endl;
    cout << "Flags" << endl;
    cout << "-all   - print all stats" << endl;
    cout << "-avg   - print only avg hits/misses" << endl;
    cout << "-proc  - print only processes marks (starting/ending processes)" << endl;
    cout << "-ref   - print only reference marks (hit/miss encountered)" << endl;
}

int totalMisses = 0;
int totalHits = 0;
int totalSwaps = 0;

// modifies the list for current processes
vector<Process *> removeFinishedProcesses(vector<Process*> &runningProcesses, int currentTime) {
    
    vector<Process *>finishedProcesses;
    
    vector<Process*>::iterator iter;
    int calculatedEndTime;
    
    for (int i = 0; i < runningProcesses.size(); i++) {
        
        calculatedEndTime = runningProcesses[i]->arrivalTime + runningProcesses[i]->serviceDuration;
        
        if (calculatedEndTime <= currentTime) {
            runningProcesses[i]->freePages();
           // cout << runningProcesses[i]->pid << " ended" << endl;
            finishedProcesses.push_back(runningProcesses[i]);
            runningProcesses.erase(runningProcesses.begin()+i);
        }
        
    }
 
    return finishedProcesses;
}

// given a time, get all processes that have arrived by that point
// IMPORTANT: removes processes that are ready from processList
vector<Process*> getReadyProcesses(int currentTime, vector<Process*> &processList) {
    
    vector<Process*> readyProcesses;
    vector<Process*>::iterator iter;
    Process* currentProcess;
    
    // We were getting seg faults when deleteing something at an iterator, so instead lets just create a new vector
    // to hold the remaining processes and assign processList to it
    vector<Process *> newProcessList;
    for (iter = processList.begin(); iter != processList.end(); ++iter) {
        
        currentProcess = *iter;
        
        if (currentProcess->arrivalTime <= currentTime) {
            readyProcesses.push_back(currentProcess);
        }
        else {
            newProcessList.push_back(currentProcess);
        }
        
    }
    
    processList = newProcessList;
    return readyProcesses;
}

// given some number of processes that should be started, give all processes a page
// from the free list given that for each process there are at least four free pages
// in the free list
vector<Process*> startReadyProcesses(vector<Process*> readyProcesses, FreeList* freeList, int currentTime) {
    
    // start ready processes
    
    vector<Process*> runningProcesses;
    vector<Process*>::iterator iter;
    Process* currentProcess;
    
    for (iter = readyProcesses.begin(); iter != readyProcesses.end(); ++iter) {
        
        currentProcess = *iter;
        
        if (!freeList->hasEnoughFreePages()) {
            break;
        }
        
        Page* freePage = freeList->getFreePage();
        freePage->assignProcessOwner(currentProcess, STARTING_PAGE_ID, currentTime);
        totalMisses++;
        
        currentProcess->pages.push_back(freePage);
        currentProcess->startTime = currentTime;
        
        // print process report
        
        runningProcesses.push_back(currentProcess);
        
    }
    
    return runningProcesses;
}

// remove processes that are already running from the total processes queued up
vector<Process*> updateRemainingProcesses(vector<Process*> totalProcesses, vector<Process*> runningProcesses) {
    
    vector<Process*>::iterator iter;
    vector<Process*>::iterator foundPosition;
    
    for (iter = runningProcesses.begin(); iter != runningProcesses.end(); ++iter) {
        
        foundPosition = find(totalProcesses.begin(), totalProcesses.end(), *iter);
        
        if (foundPosition != totalProcesses.end()) {
            totalProcesses.erase(foundPosition);
        }
        
    }
    
    return totalProcesses;
    
}


void referencePages(vector<Process*> runningProcesses, PageReplacer* replacer, FreeList *freeList, int timestamp) {
    
    vector<Process*>::iterator iter;
    Process* currentProcess;
    bool hit;
    
    for (iter = runningProcesses.begin(); iter != runningProcesses.end(); ++iter) {
        
        currentProcess = *iter;
        
        Page *newPage = NULL;
        int nextPage = currentProcess->getNextPageIndex();
        newPage = freeList->getPageWithId(nextPage);
        
        Page *evictedPage = NULL;
        hit = currentProcess->referencePage(replacer, newPage, timestamp, evictedPage);
        
        if (hit) {
            printer::printHit(currentProcess, timestamp, newPage);
            totalHits++;
        } else {
            printer::printMiss(currentProcess, timestamp, newPage, evictedPage);
            totalMisses++;
        }
        
        if (evictedPage != NULL) {
            totalSwaps++;
        }
    }
}

void checkFreeList(FreeList *freeList) {
    Page *bla = freeList->head;
    int i  = 0;
    while (bla != NULL) {
        i++;
        bla=bla->next;
    }
}

void checkProcessList(vector<Process *> processList) {
    for (int i = 0; i < processList.size(); i++) {
        cerr << "arrival time: " << processList[i]->arrivalTime << endl;
        i++;
    }
}

void runSimulation(PageReplacer *replacer) {
    
    FreeList* freeList = new FreeList();
    vector<Process *> processList = generator::generateProcessList();

//    checkFreeList(freeList);
//    checkProcessList(processList);
    
    printer::printProcessList(processList);
    
    vector<Process *> runningProcesses;
    
    // loop to run for one minute, measured in milliseconds
    for (int milliseconds = 0 ; milliseconds < 60000 ; ++milliseconds) {
       // cout << "time: " << milliseconds << endl;
        if (!runningProcesses.empty()) {
            // processes are running right now
            // need to check their service duration
            vector<Process*> finishedProcesses = removeFinishedProcesses(runningProcesses, milliseconds);
            printer::printFinishedProcesses(milliseconds, finishedProcesses, freeList);
        }
        
        // Get new processes and start them
        vector<Process*> readyProcesses = getReadyProcesses(milliseconds, processList);
       
        // initialization logic for the new processes with the freelist
        vector<Process*> initializedProcesses = startReadyProcesses(readyProcesses, freeList, milliseconds);
        
        // Add the new initialized processes processes to the running process list
        for (int i = 0; i < initializedProcesses.size(); i++) {
            runningProcesses.push_back(initializedProcesses[i]);
        }
        
        // we pass in initialized processes because we need to just show the ones which started
        printer::printStartedProcesses(milliseconds, initializedProcesses, freeList);
        
        // if 100 milliseconds have passed each process should reference a
        // new page in it's address space
        
        
        // Iterate through the list of processes and check if it needs a reference.
        for (int i = 0; i < runningProcesses.size(); i++) {
            Process *cur = runningProcesses[i];
            int time_diff = milliseconds - cur->startTime;
            if (time_diff % 100 == 0) {
                referencePages(runningProcesses, replacer, freeList, milliseconds);
            }
        }
        
    }
    
}

int main(int argc, char* argv[]) {
    
    srand(time(NULL));

    if (argc < 3) {
        cout << "Please enter an argument and flag:" << endl;
        help();
        return -1;
    }

    string choice = string(argv[1]);
    string flag = string(argv[2]);
    
    list<PageReplacer*> replacementAlgorithms;
    
    if (choice == "fifo") {
        replacementAlgorithms.push_back(new PageReplacer(FIFO_IDENTIFIER));
	}
	else if (choice == "lru") {
        replacementAlgorithms.push_back(new PageReplacer(LRU_IDENTIFIER));
	}
	else if (choice == "lfu") {
        replacementAlgorithms.push_back(new PageReplacer(LFU_IDENTIFIER));
	}
	else if (choice == "mfu") {
        replacementAlgorithms.push_back(new PageReplacer(MFU_IDENTIFIER));
	}
	else if (choice == "rand") {
        replacementAlgorithms.push_back(new PageReplacer(RAND_IDENTIFIER));
	}
	else {
		cout << "Invalid algorithm, please try again!" << endl;
		help();
	}
    
    if (flag == "-all") {
        printAverage = true;
        printProcesses = true;
        printReferences = true;
    } else if (flag == "-avg") {
        printAverage = true;
        printProcesses = false;
        printReferences = false;
    } else if (flag == "-proc") {
        printAverage = false;
        printProcesses = true;
        printReferences = false;
    } else if (flag == "-ref") {
        printAverage = false;
        printProcesses = false;
        printReferences = true;
    } else {
        cout << "Invalid flag, please try again!" << endl;
        help();
    }
    
    list<PageReplacer*>::iterator iter;
    cout << endl;
    
    for (iter = replacementAlgorithms.begin(); iter != replacementAlgorithms.end(); ++iter) {
        
        for (int i = 0; i < NUM_EXPERIMENTS; i++) {
            cout << "\t\t\t\t\t\tSIMULATION " << i << endl;
            printer::printReportHeader((*iter)->replacerID);
            runSimulation(*iter);
            printer::printReportFooter();
        }
        
    }
    
    printer::printAverageStats(totalSwaps, totalHits, totalMisses);
	return 0;

}


