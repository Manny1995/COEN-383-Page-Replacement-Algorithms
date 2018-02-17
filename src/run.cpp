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

#include "generator.h"

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
void processFinished(PageList *freeList, Process *terminatedProcess) {
    PageList *freePages = terminatedProcess->pageList;
    freeList->appendPageList(freePages);
    delete terminatedProcess;
}


void startSimulation(PageReplacer *replacer) {
    
    PageList *freeList = generator::generateFreeList();
    vector<Process *> processList = generator::generateProcessList();
    
    for (int i = 0; i < 100; i++) {
        for (int i = 0; i < 100; i++) {
            
        }
    }
    
}

int main(int argc, char* argv[]) {

	if (argc != 2) {
		cout << "Please enter an argument:" << endl;
		help();
		return -1;
	}

	string choice = string(argv[1]);




	if (choice == "all") {

	}
	else if (choice == "fifo") {

	}
	else if (choice == "lru") {

	}
	else if (choice == "lfu") {

	}
	else if (choice == "mfu") {

	}
	else if (choice == "rand") {

	}
	else {
		cout << "Invalid argument, please try again!" << endl;
		help();
	}

    
    PageReplacer *replacer = new FIFO();
    startSimulation(replacer);
    
	return 1;

}

