matrix: main.o matrix.o
	gcc -o matrix main.o matrix.o
	rm *.o

main.o: main.c
	gcc -c main.c

matrix.o: matrix.c
	gcc -c matrix.c
	
run:
	./matrix

clean:
	rm matrix