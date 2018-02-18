
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
}
#endif
