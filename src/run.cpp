// Immanuel Amirtharaj, Carlos Rivera, Maxen Chung, Tasmine Hackson, Isaac Jorgenson
// run.cpp
// The main driver for this

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>



// Include page replacement Algorithms
#include "PageReplacer.h"
#include "FIFO.h"
#include "LRU.h"
#include "LFU.h"
#include "MFU.h"
#include "RAND.h"

// Include generation
#include "generator.h"

// Include Pagelist and Page Classes
#include "FreeList.h"
#include "Page.h"


#include "printer.h"


#define STARTING_PAGE_ID 0

using namespace std;


void help() {
		cout << "all 	- run all 6 algorithms" << endl;
		cout << "fifo 	- first come first serve" << endl;
		cout << "lru 	- shortest job first" << endl;
		cout << "lfu 	- shortest time remaining" << endl;
		cout << "mfu	- round robin" << endl;
		cout << "rand	- highest priority first non-preemptive" << endl;
}

// add the terminated process' free pages back to the free list
/*
void processFinished(PageList *freeList, Process *terminatedProcess) {
    PageList *freePages = terminatedProcess->pageList;
    freeList->appendPageList(freePages);
    delete terminatedProcess;
}
 */
int totalMisses = 0;
int totalHits = 0;

// modifies the list for current processes
vector<Process *> removeFinishedProcesses(vector<Process*> &runningProcesses, int currentTime) {
    
    vector<Process *>finishedProcesses;
    
    vector<Process*>::iterator iter;
    Process* currentProcess;
    int calculatedEndTime;
    
    for (int i = 0; i < runningProcesses.size(); i++) {
        
        calculatedEndTime = runningProcesses[i]->arrivalTime + runningProcesses[i]->serviceDuration;
        
        if (calculatedEndTime <= currentTime) {
            runningProcesses[i]->freePages();
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
    
    for (iter = processList.begin(); iter != processList.end(); ++iter) {
        
        currentProcess = *iter;
        
        if (currentProcess->arrivalTime <= currentTime) {
            readyProcesses.push_back(currentProcess);
            processList.erase(iter);
        }
        
    }
    
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
        freePage->assignProcessOwner(currentProcess, STARTING_PAGE_ID);
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


void referencePages(vector<Process*> runningProcesses, PageReplacer* replacer, FreeList *freeList) {
    
    vector<Process*>::iterator iter;
    Process* currentProcess;
    bool hit;
    
    for (iter = runningProcesses.begin(); iter != runningProcesses.end(); ++iter) {
        
        currentProcess = *iter;
        
        int nextPage = currentProcess->getNextPageIndex();
        Page *newPage = freeList->getPageWithId(nextPage);
        hit = currentProcess->referencePage(replacer, newPage);
        
        if (hit) {
            totalHits++;
        } else {
            totalMisses++;
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
    int i = 0;
    for (auto p : processList) {
        cerr << "arrival time: " << p->arrivalTime << endl;
        i++;
    }
}

void runSimulation(PageReplacer *replacer) {
    
    FreeList* freeList = new FreeList();
    vector<Process *> processList = generator::generateProcessList();

    checkFreeList(freeList);
    checkProcessList(processList);
    
    vector<Process *> runningProcesses;
    
    // loop to run for one minute, measured in milliseconds
    for (int milliseconds = 0 ; milliseconds < 60000 ; ++milliseconds) {
        cout << "time: " << milliseconds << endl;
        if (!runningProcesses.empty()) {
            // processes are running right now
            // need to check their service duration
            vector<Process*> finishedProcesses = removeFinishedProcesses(runningProcesses, milliseconds);
            printer::printFinishedProcesses(milliseconds, finishedProcesses, freeList);
        }
        
        // Get new processes and start them
        vector<Process*> readyProcesses = getReadyProcesses(milliseconds, processList);
        vector<Process*> initializedProcesses = startReadyProcesses(readyProcesses, freeList, milliseconds);
        
        // Add the new running processes to the running process list
        
        
        for (auto p : initializedProcesses) {
            
            runningProcesses.push_back(p);
        }
        
        
        /*
        vector<Process*>::iterator iter;
        for (iter = initializedProcesses.begin(); iter != initializedProcesses.end(); ++iter) {
            
            Process* currentProcess = *iter;
            
            if (find(runningProcesses.begin(), runningProcesses.end(), currentProcess) == runningProcesses.end()) {
                runningProcesses.push_back(currentProcess);
                // initializedProcesses.erase(iter);
                // print single process getting added
            }
            
        }
        
        if (!initializedProcesses.empty()) {
            
            vector<Process*>::iterator iter;
            for (iter = initializedProcesses.begin(); iter != initializedProcesses.end(); ++iter) {
                
                Process* currentProcess = *iter;
                
                if (find(processList.begin(), processList.end(), currentProcess) == processList.end()) {
                    processList.push_back(currentProcess);
                }
                
            }
            
            initializedProcesses.clear();
            
        }
         */
        
        printer::printStartedProcesses(milliseconds, runningProcesses, freeList);

         
        // deletes the processes from the process list
        processList = updateRemainingProcesses(processList, runningProcesses);
        
        // if 100 milliseconds have passed each process should reference a
        // new page in it's address space
        if ((milliseconds % 100 == 0) && (milliseconds != 0)) {
            
            // replacer needs to be passed so that the process knows which page to evict
            referencePages(runningProcesses, replacer, freeList);
            
        }
        
    }
    
}

int main(int argc, char* argv[]) {
    
    srand(time(NULL));

//    if (argc != 2) {
//        cout << "Please enter an argument:" << endl;
//        help();
//        return -1;
//    }
//
//    string choice = string(argv[1]);
    
    string choice = "fifo";
    
    list<PageReplacer*> replacementAlgorithms;

	if (choice == "all") {
        replacementAlgorithms.push_back(new FIFO());
        replacementAlgorithms.push_back(new LRU());
        replacementAlgorithms.push_back(new LFU());
        replacementAlgorithms.push_back(new MFU());
        replacementAlgorithms.push_back(new RAND());
	}
	else if (choice == "fifo") {
        replacementAlgorithms.push_back(new FIFO());
	}
	else if (choice == "lru") {
        replacementAlgorithms.push_back(new LRU());
	}
	else if (choice == "lfu") {
        replacementAlgorithms.push_back(new LFU());
	}
	else if (choice == "mfu") {
        replacementAlgorithms.push_back(new MFU());
	}
	else if (choice == "rand") {
        replacementAlgorithms.push_back(new RAND());
	}
	else {
		cout << "Invalid argument, please try again!" << endl;
		help();
	}
    
    list<PageReplacer*>::iterator iter;
    
    for (iter = replacementAlgorithms.begin(); iter != replacementAlgorithms.end(); ++iter) {
        
        printer::printReportHeader((*iter)->replacerID);
        runSimulation(*iter);
        // clearGlobals();
        printer::printReportFooter();
    }
    
	return 0;

}

