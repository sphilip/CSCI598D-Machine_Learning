CC = g++
CFLAGS = -Wall
PROG = pole_balancing

SRCS = g_rl.cpp pole.c Vector.c cart.c
HDRS = pole.h Vector.h cart.h
LIBS = -lglut -lGL -lGLU -ggdb

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(HDRS) $(LIBS)

clean:
	rm -f $(PROG) *~
