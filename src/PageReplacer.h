
#ifndef PAGEREPLACER_H
#define PAGEREPLACER_H

#include "PageList.h"

// gets called by the process class
class PageReplacer {

    public:
        // Takes in a page list and returns the evicted page
        virtual Page* evictPage(PageList *pageList);
        PageReplacer();

};


#endif
