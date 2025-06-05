KursProj: main.o module.o
	gcc -o KursProj main.o module.o

main.o: Code/main.c
	gcc -c Code/main.c

functions.o: Code/module.c
	gcc -c Code/module.c

clean:
	rm *.o