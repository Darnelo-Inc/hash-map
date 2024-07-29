main: main.c hash-map.c
	cc -Wall -o main main.c hash-map.c

clean:
	rm -f main