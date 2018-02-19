
#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "Process.h"
#include "FreeList.h"


using namespace std;


namespace printer {

    void printReportHeader(string algorithm);
    void printReportFooter();
    void printMemoryMap(FreeList *fl);
    void printProcessStarted(int timestamp, Process *p, FreeList *fl);
    // <time stamp, process name, Enter/exit, Size in Pages, Service Duration, Memory-map>.
    void printProcessEnded(int timestamp, Process *p, FreeList *fl);
    void printFinishedProcesses(int timestamp, vector<Process *> finishedProcesses, FreeList *fl);
    void printStartedProcesses(int timestamp, vector<Process *>startedProcesses, FreeList *fl);
    void printProcessList(vector<Process *>processList);
    void printHit(Process *currentProcess, int timestamp, Page *newPage);
    void printMiss(Process *currentProcess, int timestamp, Page *newPage, Page *evictedPage);
    void printAverageStats(int totalSwaps, int totalHits, int totalMisses);
    
}
#endif
