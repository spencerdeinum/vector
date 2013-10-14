COMPILER=clang
OPTIONS = -std=c99 -Weverything -Werror -pedantic

default: run

build/vector.o:
	$(COMPILER) $(OPTIONS) -c src/vector.c -o build/vector.o

build/test.o:
	$(COMPILER) $(OPTIONS) -c src/test.c -o build/test.o

test: build/vector.o build/test.o
	$(COMPILER) $(OPTIONS) -o bin/test build/vector.o build/test.o

clean:
	$(RM) build/* bin/*

run: test
	./bin/test

valgrind: test
	valgrind --suppressions=src/valgrind.supp ./bin/test

gdb: test
	gdb ./bin/test
