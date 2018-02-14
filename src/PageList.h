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
		Page(int pSize) {
			Page();
			this->size = pSize;
		}

};

// This will be used by the free list and the processes
class PageList {

	public:
		Page *head;
		Page *tail;

		PageList() {
			this->head = NULL;
			this->tail = head;
		}

		PageList(int numPages, int defaultSize) {

			for (int i = 0; i < numPages; i++) {
				this->appendPageWithSize(defaultSize);
			}
		}


		// I know that this is inefficient, but it beats keeping it in track and updating it as a variable :)
        // - Dat O(n) runtime tho! :D
        int getSize() {

			Page *cur = this->head;
			int res = 0;

			while (cur != NULL) {
				cur = cur->next;
				res++;
			}
			return res;
		}

		void appendPageWithSize(int pSize) {
			Page *newPage = Page(pSize);
			this->appendPage(newPage);
		}

		void appendPage(Page *newPage) {

			if (newPage == NULL) {
				cerr << "New Page is NULL" << endl;
				return;
			}

			if (head == NULL) {
				this->head = newPage;
				this->tail = this->head;
			}
			else {
				this->tail->next = newPage;
				this->tail = this->tail->next;
				this->tail->next = NULL;
			}
		}

		// Shifts the page to the back
		void shiftPageToBack(int pagePos) {
			
		}
		

		Page *findPage() {

		}

		bool hasFreePages() {
			return this->getSize() >= 4;
		}

		// By default gets the first 4 free pages
		Page *getFreePages() {

			if (this->getSize() < 4) {
				cerr << "No Free Pages!" << endl;
				return NULL;
			}

			Page *res = this->head;
			Page *tRes = res;
			for (int i = 0; i < 3; i++) {
				tRes = tRes->next;
			}

			// Got to shift the head
			this->head = tRes->next;
			tRes->next = NULL;

			return res;
		}

};

#endif
