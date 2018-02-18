
#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>
#include <stdlib.h>
#include <string>

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
}
#endif
