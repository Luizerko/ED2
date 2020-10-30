CFLAGS = -g -Wall -Wno-unused-result

all: cliente

cliente: cliente.o ABB.o ARN.o tries.o node_ABB.h node_ARN.h node_trie.h
	gcc -o cliente cliente.o ABB.o ARN.o tries.o

cliente.o: cliente.c node_ABB.h node_ARN.h node_trie.h
	gcc $(CFLAGS) cliente.c -c

ABB.o: ABB.c node_ABB.h
	gcc $(CFLAGS) ABB.c -c

ARN.o: ARN.c node_ARN.h
	gcc $(CFLAGS) ARN.c -c

tries.o: tries.c node_trie.h
	gcc $(CFLAGS) tries.c -c

clean:
	rm -rf *.o cliente
