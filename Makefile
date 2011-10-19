PROGNAME = os_meas
CC = g++
#LIBS = -pthread 
LIBS = 
INCLUDES = -I.
#LDFLAGS = -Llibs/
LDFLAGS = 

OBJECTS = main.o \
          utils.o \
	  benchmarks.o \
          
CFLAGS = -Wall -O0 -finline-functions

all: $(PROGNAME)

$(PROGNAME): $(OBJECTS)
	$(CC) -o $(PROGNAME) $(OBJECTS) $(LIBS) $(INCLUDES) $(LDFLAGS)

$(OBJECTS): Makefile

.c.o: 
	$(CC) -c $(CFLAGS) $(INCLUDES) -o $@ $< 

clean:
	rm *.o $(PROGNAME)