# PROGNAME = os_meas
CC = g++
#LIBS = -pthread  
LIBS = 
INCLUDES = -I.
#LDFLAGS = -Llibs/
LDFLAGS = 

OBJECTS = utils.o \
	  benchmarks.o \
          
CFLAGS = -Wall -O0 -finline-functions -lpthread

all: main memory pageFault filesys seqFileRead randFileRead

main: main.o $(OBJECTS)
	$(CC) -o $(CFLAGS) $(INCLUDES) $^ -o $@ -lpthread

memory: memory.o $(OBJECTS)
	$(CC) -o $(CFLAGS) $(INCLUDES) $^ -o $@ -lpthread

filesys: filesys.o $(OBJECTS)
	$(CC) -o $(CFLAGS) $(INCLUDES) $^ -o $@ -lpthread

seqFileRead: seqFileRead.o $(OBJECTS)
	$(CC) -o $(CFLAGS) $(INCLUDES) $^ -o $@ -lpthread

randFileRead: randFileRead.o $(OBJECTS)
	$(CC) -o $(CFLAGS) $(INCLUDES) $^ -o $@ -lpthread

pageFault: pageFault.o $(OBJECTS)
	$(CC) -o $(CFLAGS) $(INCLUDES) $^ -o $@ -lpthread

processStartOverhead: processStartOverhead.o $(OBJECTS)
	$(CC) -o $(CFLAGS) $(INCLUDES) $^ -o $@ -lpthread

$(OBJECTS): Makefile

.c.o: 
	$(CC) -c $(CFLAGS) $(INCLUDES) -o $@ $< 

clean:
	rm *.o main memory pageFault filesys seqFileRead randFileRead
