
#ifndef PRINTER_CPP
#define PRINTER_CPP

#include "printer.h"

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
    cout << "TIMESTAMP - " << timestamp << endl;
    cout << "PROCESS STARTED " << endl;
    cout << "Process name is " << p->pid << ", its size in pages is " << p->size << " and service duration is " << p->serviceDuration << " ms." << endl;
    printMemoryMap(fl);
}

// <time stamp, process name, Enter/exit, Size in Pages, Service Duration, Memory-map>.
void printer::printProcessEnded(int timestamp, Process *p, FreeList *fl) {
    cout << "TIMESTAMP - " << timestamp << endl;
    cout << "PROCESS COMPLETED " << endl;
    cout << "Process name was " << p->pid << ", its size in pages was " << p->size << " and service duration was " << p->serviceDuration << endl;
    printMemoryMap(fl);
    
}

void printer::printFinishedProcesses(int timestamp, vector<Process *> finishedProcesses, FreeList *fl) {
    for (auto p : finishedProcesses) {
        printProcessEnded(timestamp, p, fl);
    }
}

void printer::printStartedProcesses(int timestamp, vector<Process *>startedProcesses, FreeList *fl) {
    for (auto p : startedProcesses) {
        printProcessStarted(timestamp, p, fl);
    }
}


#endif
