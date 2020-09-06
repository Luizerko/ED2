CFLAGS = -g -Wall -ansi -pedantic -Wno-unused-result

all: main

main: main.o fila_CPU.o fila_espera.o fila_impressora.o processo.h
	gcc -o main main.o fila_CPU.o fila_espera.o fila_impressora.o

main.o: main.c processo.h
	gcc $(CFLAGS) main.c -c

fila_CPU.o: fila_CPU.c processo.h
	gcc $(CFLAGS) fila_CPU.c -c

fila_espera.o: fila_espera.c processo.h
	gcc $(CFLAGS) fila_espera.c -c

fila_impressora.o: fila_impressora.c processo.h
	gcc $(CFLAGS) fila_impressora.c -c

clean:
	rm -rf *.o *~ main
