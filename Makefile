all: main

main: main.c hash-map.c
	cc -o main main.c hash-map.c
	./main
clean:
	rm -f main