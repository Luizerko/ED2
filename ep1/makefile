CFLAGS = -g -Wall -ansi -pedantic -Wno-unused-result

all: main

main: main.o fila_CPU.o fila_ei.o fila.h processo.h
	gcc -o main main.o fila_CPU.o fila_ei.o

main.o: main.c processo.h
	gcc $(CFLAGS) main.c -c

fila_CPU.o: fila_CPU.c processo.h
	gcc $(CFLAGS) fila_CPU.c -c

fila_ei.o: fila_ei.c fila.h processo.h
	gcc $(CFLAGS) fila_ei.c -c

clean:
	rm -rf *.o main
