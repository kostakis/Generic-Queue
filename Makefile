all: queue.o
	gcc -o test.out main.c queue.o

queue.o:
	gcc -c queue.c -o queue.o

clean:
	rm test.out
	rm queue.o