#ifndef PAGELIST_CPP
#define PAGELIST_CPP

#include "PageList.h"

PageList::PageList() {
	this->head = NULL;
	this->tail = head;
}


// I know that this is inefficient, but it beats keeping it in track and updating it as a variable :)
// - Dat O(n) runtime tho! :D
int PageList::getSize() {

	Page *cur = this->head;
	int res = 0;

	while (cur != NULL) {
		cur = cur->next;
		res++;
	}
	return res;
}


void PageList::appendPage(Page *newPage) {

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

Page *PageList::getPageAtIndex(int index) {
    if (index > this->getSize()) {
        return NULL;
    }
    
    Page *cur = this->head;
    for (int i = 0; i < index; i++) {
        
        if (cur == NULL) {
            cerr << "ERROR, NULL PAGE" << endl;
            return NULL;
        }
        
        cur=cur->next;
    }
    
    return cur;
    
}

// Shifts the page to the back
// Should call this when using something like an MFU or LRU algorithm
void PageList::shiftPageToBack(int pagePos) {
    
    Page *page = this->getPageAtIndex(pagePos);

	if (page == NULL) {
		cerr << "NULL page, so cannot shift to back" << endl;
		return;
	}

	if (page == this->head) {
		this->head = NULL;
		this->tail = this->head;
	}
	else {
		Page *cur = this->head;
		while (cur != NULL) {
			if (cur->next == page) {
				cur->next = page->next;
				break;
			}
		}

		if (page == this->tail) {
			this->tail = cur;
		}
	}

	delete page;
}


Page *PageList::findPage(string identifier) {
    
    Page* currentPage = this->head;
    
    while (currentPage != NULL) {
        
        if (currentPage->identifier == identifier) {
            return currentPage;
        }
    }
    
    return NULL;  
}


bool PageList::hasFreePages() {
	return this->getSize() >= 4;
}

// By default gets the first 4 free pages
Page *PageList::getFreePages() {

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

Page *PageList::deleteHead() {
    
    Page *res = this->head;
    if (res == NULL) {
        cerr << "NO HEAD TO DELETE" << endl;
    }
    else {
        res->next = NULL;
        this->head = res->next;
    }
    return res;
}


#endif
