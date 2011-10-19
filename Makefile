PROGNAME = os_meas
CC = gcc
#LIBS = -pthread 
LIBS = 
INCLUDES = -I.
#LDFLAGS = -Llibs/
LDFLAGS = 

OBJECTS = main.o \
          utils.o \
          
CFLAGS = -Wall -pedantic 

all: $(PROGNAME)

$(PROGNAME): $(OBJECTS)
	$(CC) -o $(PROGNAME) $(OBJECTS) $(LIBS) $(INCLUDES) $(LDFLAGS)

$(OBJECTS): Makefile

.c.o: 
	$(CC) -c $(CFLAGS) $(INCLUDES) -o $@ $< 

clean:
	rm *.o $(PROGNAME)