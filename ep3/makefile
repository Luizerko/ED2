CFLAGS = -g -Wall -Wno-unused-result
CLINKS = -lm

all: cliente

cliente: cliente.o ABB.o ARN.o tries.o hash_linear.o hash_encadeamento.o node_ABB.h node_ARN.h node_trie.h node_hash_linear.h node_hash_encadeamento.h
	gcc -o cliente cliente.o ABB.o ARN.o tries.o hash_linear.o hash_encadeamento.o $(CLINKS)

cliente.o: cliente.c node_ABB.h node_ARN.h node_trie.h node_hash_linear.h node_hash_encadeamento.h
	gcc $(CFLAGS) cliente.c -c

ABB.o: ABB.c node_ABB.h
	gcc $(CFLAGS) ABB.c -c

ARN.o: ARN.c node_ARN.h
	gcc $(CFLAGS) ARN.c -c

tries.o: tries.c node_trie.h
	gcc $(CFLAGS) tries.c -c

hash_linear.o: hash_linear.c node_hash_linear.h
	gcc $(CFLAGS) hash_linear.c -c

hash_encadeamento.o: hash_encadeamento.c node_hash_encadeamento.h
	gcc $(CFLAGS) hash_encadeamento.c -c

clean:
	rm -rf *.o cliente
