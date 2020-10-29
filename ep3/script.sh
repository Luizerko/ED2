#!/bin/bash

make;

time ./cliente sherlock.txt;

time ./cliente teste_pequeno.txt;

make clean;
