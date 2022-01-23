all: queue.o
	gcc -Wall -o test.out main.c queue.o

queue.o:
	gcc -Wall -c queue.c -o queue.o

clean:
	rm test.out
	rm queue.o