#!/bin/bash

make;

#for i in $(seq 1 10); do
#	time ./cliente teste_pequeno.txt;
#done

#for i in $(seq 1 10); do
#	time ./cliente dicionario.txt;
#done

#time ./cliente dictionary.txt;

#for i in $(seq 1 10); do
#	time ./cliente les_miserables.txt;
#done

#for i in $(seq 1 10); do
	time ./cliente bible.txt;
#done

#for i in $(seq 1 10); do
#	time ./cliente sherlock.txt;
#done

#time ./cliente grandao.txt;

#time ./cliente grandao_ordenado.txt;

make clean;
