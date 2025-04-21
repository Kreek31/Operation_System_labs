all : prog1 prog2

prog1 : program_first.o libLib1.so
	gcc -o prog1 program_first.o -L. -lLib1  -Wl,-rpath,.

program_first.o : program_first.c
	gcc -c program_first.c 

libLib1.so : lib_first.o
	gcc -shared -o libLib1.so lib_first.o 

lib_first.o : lib_first.c
	gcc -c -fPIC lib_first.c 


prog2 : program_second.o libLib2.so
	gcc -o prog2 program_second.o -L. -lLib2  -Wl,-rpath,.

program_second.o : program_second.c
	gcc -c program_second.c 

libLib2.so : lib_second.o
	gcc -shared -o libLib2.so lib_second.o 

lib_second.o : lib_second.c
	gcc -c -fPIC lib_second.c 

clean:
	rm -rf *.o *.so prog1 prog2
