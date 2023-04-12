all: main.o func.o 
	gcc func.o main.o -o Cnake -lncurses

main.o: main.c
	gcc -g -c main.c
func.o: func.c
	gcc -g -c func.c
clean:
	rm -rf *.o
