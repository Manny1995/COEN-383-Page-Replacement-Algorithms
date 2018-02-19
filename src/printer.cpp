
#ifndef PRINTER_CPP
#define PRINTER_CPP

#include "printer.h"
#include <sstream>

extern bool printAverage;
extern bool printProcesses;
extern bool printReferences;

void printer::printReportHeader(string algorithm) {
    cout << "=====================================================";
    cout << "====================================================" << endl;
    cout << "\t\t\t\t\t\t" << algorithm << endl << endl;
}

void printer::printReportFooter() {
    cout << "=====================================================";
    cout << "====================================================" << endl;
    cout << endl << endl << endl << endl;
}

void printer::printMemoryMap(FreeList *fl) {
    Page *cur = fl->head;
    cout << endl;
    cout << "MEMORY MAP" << endl;
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
    
    cout << "Process name is " << p->pid << ", its size is ";
    cout << p->size << " MB, and service duration is " << p->serviceDuration << " ms." << endl;
}

// <time stamp, process name, Enter/exit, Size in Pages, Service Duration, Memory-map>.
void printer::printProcessEnded(int timestamp, Process *p, FreeList *fl) {
    cout << "Process name was " << p->pid << ", its size was ";
    cout << p->size << " MB, and service duration was " << p->serviceDuration << " ms." << endl;
}

void printer::printFinishedProcesses(int timestamp, vector<Process *> finishedProcesses, FreeList *fl) {
    
    if (!printProcesses) {
        return;
    }
    
    if (finishedProcesses.size() == 0) {
        return;
    }
    
    cout << endl;
    cout << "Processes ended at time " << timestamp << " (ms)" << endl;
    cout << "-----------------------------------------------------";
    cout << "----------------------------------------------------" << endl;
    for (int i = 0; i < finishedProcesses.size(); i++) {
        Process *p = finishedProcesses[i];
        printProcessEnded(timestamp, p, fl);
    }
    printMemoryMap(fl);
    cout << "-----------------------------------------------------";
    cout << "----------------------------------------------------" << endl;
    cout << endl;
}

void printer::printStartedProcesses(int timestamp, vector<Process *>startedProcesses, FreeList *fl) {
    
    if (!printProcesses) {
        return;
    }
    
    if (startedProcesses.size() == 0) {
        return;
    }
    
    cout << endl;
    cout << "Processes started at time " << timestamp << " (ms)" << endl;
    cout << "-----------------------------------------------------";
    cout << "----------------------------------------------------" << endl;
    for (int i = 0; i < startedProcesses.size(); i++) {
        Process *p = startedProcesses[i];
        printProcessStarted(timestamp, p, fl);
    }
    printMemoryMap(fl);
    cout << "-----------------------------------------------------";
    cout << "----------------------------------------------------" << endl;
    cout << endl;
}

void printer::printProcessList(vector<Process *>processList) {
    cout << "\t\t\t\t\t\tPROCESS LIST" << endl;
    cout << "-----------------------------------------------------";
    cout << "----------------------------------------------------" << endl;
    cout << "|\tProcess ID\t|\tSize (MB)\t|\tArrival Time (ms)\t|\tDuration (ms)\t|" << endl;
    cout << "-----------------------------------------------------";
    cout << "----------------------------------------------------" << endl;
    for (int i = 0; i < processList.size(); i++) {
        Process *cur = processList[i];
        cout << "|\t" << cur->pnum << "\t\t|\t" << cur->size << "\t\t|\t";
        cout << cur->arrivalTime << "\t\t\t|\t" << cur->serviceDuration << "\t\t|" << endl;
        
    }
    cout << "-----------------------------------------------------";
    cout << "----------------------------------------------------" << endl;
}

void printer::printHit(Process *currentProcess, int timestamp, Page *newPage) {
    
    if (!printReferences) {
        return;
    }
    
    stringstream ss;
    ss << timestamp << ":\tProc-" << currentProcess->pnum << "  \tHIT\tPage[" << newPage->pageID << "]";
    cout << ss.str() << endl;
    
}

void printer::printMiss(Process *currentProcess, int timestamp, Page *newPage, Page *evictedPage) {
    
    if (!printReferences) {
        return;
    }
    
    stringstream ss;
    ss << timestamp << ":\tProc-" << currentProcess->pnum << "  \tMISS\tPage[" << newPage->pageID << "]";
    
    if (evictedPage != NULL) {
        ss << " and evicted Page[" << evictedPage->pageID << "]";
    }
    
    cout << ss.str() << endl;
}

void printer::printAverageStats(int totalSwaps, int totalHits, int totalMisses) {
    
    if (!printAverage) {
        return;
    }
    
    cout << endl;
    cout << "AVERAGES STATS OF 5 RUNS" << endl;
    cout << "------------------------" << endl;
    cout << "Average swaps\t= " << totalSwaps / 5 << endl;
    cout << "Average hits\t= " << totalHits / 5 << endl;
    cout << "Average misses\t= " << totalMisses / 5 << endl << endl;
}


#endif
