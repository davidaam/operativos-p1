main: main.o misc.o map.o
	gcc -g main.o misc.o map.o -o main
misc.o:	misc.h misc.c
	gcc -c misc.c
map.o: map.h misc.h
	gcc -c map.c
clean:
	rm main
	rm *.o
