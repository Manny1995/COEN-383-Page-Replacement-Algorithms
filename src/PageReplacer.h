
#ifndef PAGEREPLACER_H
#define PAGEREPLACER_H

#include <list>

#include "page.h"
#include "PageList.h"

// gets called by the process class
class PageReplacer {

public:
    string replacerID;
    
    // Takes in a page list and returns the evicted page
    // virtual Page* evictPage(PageList *pageList);
    virtual Page* evictPage(list<Page*> pageList);
    PageReplacer();

};


#endif
