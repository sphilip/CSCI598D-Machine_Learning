GCC = g++
CFLAGS = -O0 -Wall
LIBS =  -ggdb
SOURCES = driver.c
HEADERS = alphabeta.h minimax.h
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = tictactoe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(GCC) $(CFLAGS) $(OBJECTS) $(HEADERS) -o $@

.c.o:
	$(GCC) $(CFLAGS) -c $< -o $@ $(LIBS)

clean :
	rm *.o *~ tictactoe