#ifndef PAGELIST_H
#define PAGELIST_H


class Page {
	public:
		string identifier;
		int size;
		Page *next;

		Page() {
			this->identifier = "NO IDENTIFIER";
			this->size = 0;
			this->next = NULL;
		}

		// Takes in a page size in MB
		Page(int pSize) {`
			Page();
			this->size = pSize;
		}
};

// This will be used by the free list and the processes
class PageList {

	public:
		Page *head;
		Page *tail;

		PageList();
		PageList(int numPages, int defaultSize);

		// I know that this is inefficient, but it beats keeping it in track and updating it as a variable :)
        // - Dat O(n) runtime tho! :D
        int getSize();
		void appendPageWithSize(int pSize);
		void appendPage(Page *newPage);
		// Shifts the page to the back
		void shiftPageToBack(int pagePos);
		Page *findPage(string identifier);
		bool hasFreePages();

		// By default gets the first 4 free pages
		Page *getFreePages();

};

#endif
