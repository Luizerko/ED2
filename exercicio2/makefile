all: sl

sl: skip_list.o
	gcc -o sl skip_list.o

skip_list.o: skip_list.c
	gcc skip_list.c -c

clean:
	rm -rf *.o sl
