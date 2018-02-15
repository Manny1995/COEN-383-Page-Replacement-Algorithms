// Immanuel Amirtharaj and Carlos Rivera
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
		cout << "random	- highest priority first non-preemptive" << endl;
}

int main(int argc, char* argv[]) {

	if (argc != 2) {
		cout << "Please enter an argument:" << endl;
		help();
		return -1;
	}

	string choice = string(argv[1]);



	PageList *freeList = Generator::


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
	else if (choice == "random") {

	}
	else {
		cout << "Invalid argument, please try again!" << endl;
		help();
	}

	return 1;

}