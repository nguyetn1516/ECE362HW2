all: twist main.o DynamicStack.o

twist: main.o DynamicStack.o
	gcc -std=c99 -Wall -o twist main.o DynamicStack.o
main.o: main.c
	gcc -std=c99 -Wall -c main.c DynamicStack.c
DynamicStack.o: DynamicStack.c
	gcc -Wall -std=c99 -c DynamicStack.c
clean:
	rm twist DynamicStack.o
