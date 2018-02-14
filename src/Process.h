#ifndef PROCESS_H
#define PROCESS_H


#include "PageList.h"

class Process {
	public:
		string identifier;
		int pageSize;
		int serviceDuration;
		
		PageList *pageList;
		PageReplacer *replacer;


		// randomize 70%
		bool shouldAccessCache() {

		}

		void accessMemory() {

			bool accessCache = this->shouldAccessCache();

			if (accessCache) {
				this->replacer()
			}
			else {

			}
		}

}

#endif