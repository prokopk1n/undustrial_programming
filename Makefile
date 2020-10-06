lab2: main.o function.o
	gcc -o lab2 main.o function.o
main.o: main.c
	gcc -c -o main.o main.c 
function.o: function.c
	gcc -c -o function.o function.c 
