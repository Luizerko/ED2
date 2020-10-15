CFLAGS = -g -Wall -ansi -pedantic -Wno-unused-result

all: ep2

ep2: ep2.o fila_CPU.o fila_ei.o fila_prioridade.o fila.h processo.h
	gcc -o ep2 ep2.o fila_CPU.o fila_ei.o fila_prioridade.o

ep2.o: ep2.c processo.h
	gcc $(CFLAGS) ep2.c -c

fila_CPU.o: fila_CPU.c processo.h
	gcc $(CFLAGS) fila_CPU.c -c

fila_ei.o: fila_ei.c fila.h processo.h
	gcc $(CFLAGS) fila_ei.c -c

fila_prioridade.o: fila_prioridade.c processo.h
	gcc $(CFLAGS) fila_prioridade.c -c

clean:
	rm -rf *.o ep2
