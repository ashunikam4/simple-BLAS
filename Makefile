CC=gcc
CFLAGS=-c -Wall

all: app

app: main.o subs.o matinv.o plotter.o dsc.o brs.o dda.o
	$(CC) main.o subs.o matinv.o plotter.o dsc.o brs.o dda.o -o app -lm

# main
main.o: main.c
	$(CC) $(CFLAGS) main.c

# solver files
subs.o: solver/subs.c
	$(CC) $(CFLAGS) solver/subs.c

matinv.o: solver/matinv.c
	$(CC) $(CFLAGS) solver/matinv.c

# plotter files
plotter.o: plotting/plotter.c
	$(CC) $(CFLAGS) plotting/plotter.c 

dsc.o: plotting/drawing/dsc.c
	$(CC) $(CFLAGS) plotting/drawing/dsc.c

dda.o: plotting/drawing/dda.c
	$(CC) $(CFLAGS) plotting/drawing/dda.c

brs.o: plotting/drawing/brs.c
	$(CC) $(CFLAGS) plotting/drawing/brs.c

clean:
	rm *.o app