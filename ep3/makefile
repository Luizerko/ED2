CFLAGS = -g -Wall -Wno-unused-result

all: cliente

cliente: cliente.o ABB.o ARN.o node_ABB.h node_ARN.h
	gcc -o cliente cliente.o ABB.o ARN.o

cliente.o: cliente.c node_ABB.h node_ARN.h
	gcc $(CFLAGS) cliente.c -c

ABB.o: ABB.c node_ABB.h
	gcc $(CFLAGS) ABB.c -c

ARN.o: ARN.c node_ARN.h
	gcc $(CFLAGS) ARN.c -c

clean:
	rm -rf *.o cliente
