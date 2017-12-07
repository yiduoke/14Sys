all: semaphores.c
	gcc semaphores.c

clean:
	rm *~
	rm a.out

run: all
	./a.out -c 5
	./a.out -v
	./a.out -r
	./a.out -c 6
	./a.out -c 7