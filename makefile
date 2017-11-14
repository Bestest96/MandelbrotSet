CC=gcc
CFLAGS=-m64

ASM=nasm
AFLAGS=-f elf64

LFLAGS=-L/usr/lib -lallegro -lallegro_color

all: mandelbrot

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

mandelbrot.o: mandelbrot.s
	$(ASM) $(AFLAGS) mandelbrot.s
	
draw.o:	draw.c
	$(CC) $(CFLAGS) -c draw.c

mandelbrot: main.o mandelbrot.o draw.o draw.h
	$(CC) $(CFLAGS) main.o mandelbrot.o draw.o -o mandelbrot $(LFLAGS)

clean:
	rm *.o
	rm mandelbrot

PHONY: clean
