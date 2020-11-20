all: main.o
	gcc -o dirinfo main.o

main.o: main.c
	gcc -c main.c

run:
	./dirinfo

clean:
	rm *.o
