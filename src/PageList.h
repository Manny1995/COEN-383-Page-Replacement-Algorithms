#ifndef PAGELIST_H
#define PAGELIST_H

#include <iostream>
#include <string>

using namespace std;

class Page {
	public:
		string identifier;
		Page *next;
        int refCount;

		Page() {
			this->identifier = "NO IDENTIFIER";
			this->next = NULL;
            this->refCount = 0;
		}

		// Takes in a page size in MB
		Page(string identifier) {
			Page();
            this->identifier = identifier;
		}
};

// This will be used by the free list and the processes
class PageList {

	public:
		Page *head;
		Page *tail;

		PageList();

		// I know that this is inefficient, but it beats keeping it in track and updating it as a variable :)
        // - Dat O(n) runtime tho! :D
        int getSize();
		void appendPageWithSize(int pSize);
		void appendPage(Page *newPage);
    
    
		// Shifts the page to the back
        // NEEDED FOR LRU
        void shiftPageToBack(int pagePos);

        // Need this for random choice, and for sending to back
        Page* getPageAtIndex(int index);
    
        // Deletes the head of the page
        // NEEDED TO EVICT FOR LRU AND FIFO
        Page* deleteHead();
    
        // Deletes the tail of the page
        // NEEDED TO EVICT FOR MRU
        Page* deleteTail();
    
		Page *getPageAtPosition(int pos);
		bool hasFreePages();

		// By default gets the first 4 free pages
		Page *getFreePages();
    
    
        Page *findPage(string identifier);


};

#endif
