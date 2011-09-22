GCC = g++
CFLAGS = -O0 -Wall
LIBS =  -ggdb -L/usr/X11R6/lib -lGLU -lGL -lglut 
SOURCES = g_rl.cpp
HEADERS = 
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = pole_balance

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(GCC) $(CFLAGS) $(OBJECTS) $(HEADERS) -o $@
        

.cpp.o:
	$(GCC) $(CFLAGS) -c $< -o $@ $(LIBS)

clean :
	rm *.o *~ pole_balance