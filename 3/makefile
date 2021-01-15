DEPS= main.o funkcje.o

gra: $(DEPS)
	gcc $(DEPS) -o $@ -Wall -pedantic -lm

%.o:%.c
	gcc -c $^ -o $@

clean:
	rm -f gra
	rm -f *.o

test: gra
	./gra

test-memory: gra
	valgrind ./gra
