
#ifndef PRINTER_CPP
#define PRINTER_CPP

#include "printer.h"
#include <sstream>

void printer::printReportHeader(string algorithm) {
    
    cout << "====================================================================" << endl;
    cout << algorithm << endl;
    cout << endl;
    
}

void printer::printReportFooter() {
    
    cout << "====================================================================" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    
}

void printer::printMemoryMap(FreeList *fl) {
    Page *cur = fl->head;
    cout << "PRINTING MEMORY MAP" << endl;
    while (cur != NULL) {
        
        if (cur->processID > -1) {
            cout << "[" << cur->processID << "]";
        }
        else {
            cout << ".";
        }
        
        cur = cur->next;
    }
    cout << "\n" << endl;
}

void printer::printProcessStarted(int timestamp, Process *p, FreeList *fl) {
    
    cout << "Process name is " << p->pid << ", its size in pages is " << p->size << " and service duration is " << p->serviceDuration << " ms." << endl;
}

// <time stamp, process name, Enter/exit, Size in Pages, Service Duration, Memory-map>.
void printer::printProcessEnded(int timestamp, Process *p, FreeList *fl) {
    cout << "Process name was " << p->pid << ", its size in pages was " << p->size << " and service duration was " << p->serviceDuration << endl;
}

void printer::printFinishedProcesses(int timestamp, vector<Process *> finishedProcesses, FreeList *fl) {
    
    if (finishedProcesses.size() == 0) {
        return;
    }
    
    cout << "Batch of processes which have ended at " << timestamp << endl;
    cout << "-----------------------------------" << endl;
    for (int i = 0; i < finishedProcesses.size(); i++) {
        Process *p = finishedProcesses[i];
        printProcessEnded(timestamp, p, fl);
    }
    printMemoryMap(fl);
    cout << "-----------------------------------" << endl;

}

void printer::printStartedProcesses(int timestamp, vector<Process *>startedProcesses, FreeList *fl) {
    
    if (startedProcesses.size() == 0) {
        return;
    }
    
    cout << "Batch of processes which have started at " << timestamp << endl;
    cout << "-----------------------------------" << endl;
    for (int i = 0; i < startedProcesses.size(); i++) {
        Process *p = startedProcesses[i];
        printProcessEnded(timestamp, p, fl);
    }
    printMemoryMap(fl);
    cout << "-----------------------------------" << endl;
}

void printer::printProcessList(vector<Process *>processList) {
    cout << "|  pid     |   size        |  arriv    |   dur     |" << endl;
    cout << "-------------------------------------------" << endl;
    
    for (int i = 0; i < processList.size(); i++) {
        Process *cur = processList[i];
        cout << "|   " << cur->pnum << "        |   " << cur->size << "     |   " << cur->arrivalTime << "      |   " << cur->serviceDuration << "      |" << endl;
        
    }
    cout << "-------------------------------------------" << endl;

}

void printer::printHit(Process *currentProcess, int timestamp, Page *newPage) {
    stringstream ss;
    ss << timestamp << ":   " << currentProcess->pnum << " HIT Page[" << newPage->pageID << "]";
    cout << ss.str() << endl;
}

void printer::printMiss(Process *currentProcess, int timestamp, Page *newPage, Page *evictedPage) {
    stringstream ss;
    ss << timestamp << ":   " << currentProcess->pnum << " MISS Page[" << newPage->pageID << "]";
    
    if (evictedPage != NULL) {
        ss << " and evicted Page[" << evictedPage->pageID << "]";
    }
    
    cout << ss.str() << endl;
}

void printer::printAverageStats(int totalSwaps, int totalHits, int totalMisses) {
    cout << "AVERAGES STATS OF 5 RUNS" << endl;
    cout << "------------------------" << endl;
    cout << "Average swaps  = " << totalSwaps / 5 << endl;
    cout << "Average hits = " << totalHits / 5 << endl;
    cout << "Average misses = " << totalMisses / 5 << endl;
}


#endif
