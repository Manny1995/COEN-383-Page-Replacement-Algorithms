makeall: fifo lru lfu mfu rand

CC		= gcc
CFLAGS	= -o $@
EXT		= 
LIB		=

COMMON_COMPILE_FILES	:= run.cpp
COMMON_COMPILE_FILES	+= Job.cpp

COMMON_DEPEND_FILES		:= 


fifo:	FIFO.h FIFO.cpp
	$(CC) $(CFLAGS) $(COMMON_COMPILE_FILES) FIFO.cpp


lru:	LRU.h LRU.cpp
	$(CC) $(CFLAGS) $(COMMON_COMPILE_FILES) LRU.cpp


lfu:	LFU.h LFU.cpp
	$(CC) $(CFLAGS) $(COMMON_COMPILE_FILES) LFU.cpp


mfu:	MFU.h MFU.cpp
	$(CC) $(CFLAGS) $(COMMON_COMPILE_FILES) MFU.cpp


rand:	RAND.h RAND.cpp
	$(CC) $(CFLAGS) $(COMMON_COMPILE_FILES) RAND.cpp


clean:
	rm fifo lru lfu mfu rand

