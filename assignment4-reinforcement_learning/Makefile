GCC = g++
CFLAGS = -O0 -Wall
LIBS =  -ggdb
SOURCES = driver.c Vector.c pole.c cart.c cell.c
HEADERS = Vector.h pole.h cart.h cell.h
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = pole_balance

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(GCC) $(CFLAGS) $(OBJECTS) $(HEADERS) -o $@

.c.o:
	$(GCC) $(CFLAGS) -c $< -o $@ $(LIBS)

clean :
	rm *.o *~ pole_balance