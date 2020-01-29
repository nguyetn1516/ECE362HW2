all: twist twist.o DynamicStack.o

twist: twist.o DynamicStack.o
	gcc -std=c99 -Wall -o twist twist.o DynamicStack.o
twist.o: twist.c
	gcc -std=c99 -Wall -c twist.c DynamicStack.c
DynamicStack.o: DynamicStack.c
	gcc -Wall -std=c99 -c DynamicStack.c
clean:
	rm twist twist.o DynamicStack.o
