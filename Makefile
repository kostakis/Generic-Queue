all: queue.o
	gcc -Wall -Wextra -o test.out main.c queue.o

queue.o:
	gcc -Wall -Wextra -c queue.c -o queue.o

clean:
	rm test.out
	rm queue.o