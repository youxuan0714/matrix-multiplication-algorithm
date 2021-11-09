all: 1 2 3 4 5

1: Main1.c
	gcc -o 1 Main1.c
2: Main2.c
	gcc -o 2 Main2.c
3: Main3.c
	gcc -o 3 Main3.c
4: Main4.c
	gcc -o 4 Main4.c
5: Main5.c
	gcc -o 5 Main5.c

run:
	./1
	./2
	./3
	./4
	./5

clean:
	rm -rf 1 2 3 4 5
