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

all: main processStartOverhead

main: main.o $(OBJECTS)
	$(CC) -o $(INCLUDES) $^ -o $@ -lpthread

processStartOverhead: processStartOverhead.o $(OBJECTS)
	$(CC) -o $(INCLUDES) $^ -o $@ -lpthread

$(OBJECTS): Makefile

.c.o: 
	$(CC) -c $(CFLAGS) $(INCLUDES) -o $@ $< 

clean:
	rm *.o main processStartOverhead