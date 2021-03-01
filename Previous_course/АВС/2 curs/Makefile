computer: main.o libcomputer.a libterm.a libchars.a libkey.a libcpu.a
	gcc -o computer main.o -L. -lcomputer -lterm -lchars -lkey -lcpu
	rm *.a *.o

main.o: main.c
	gcc -c main.c 

libcomputer.a: My_Simple_Computer.o
	ar cr libcomputer.a My_Simple_Computer.o

libterm.a: My_Term.o
	ar cr libterm.a My_Term.o

libchars.a: My_Big_Chars.o
	ar cr libchars.a My_Big_Chars.o

libkey.a: My_Read_Key.o
	ar cr libkey.a My_Read_Key.o

libcpu.a: cpu.o
	ar cr libcpu.a cpu.o

My_Simple_Computer.o: My_Simple_Computer.c 
	gcc -c My_Simple_Computer.c 

My_Term.o: My_Term.c
	gcc -c My_Term.c

My_Big_Chars.o: My_Big_Chars.c
	gcc -c My_Big_Chars.c

My_Read_Key.o: My_Read_Key.c
	gcc -c My_Read_Key.c

cpu.o: cpu.c
	gcc -c cpu.c

clean:
	rm computer

run:
	./computer