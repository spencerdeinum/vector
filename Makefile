COMPILER=clang
OPTIONS = -std=c99 -pedantic

default: run

test:
	$(COMPILER) $(OPTIONS) src/test.c -o bin/test

clean:
	$(RM) build/* bin/*

run: test
	./bin/test

valgrind: test
	valgrind --suppressions=src/valgrind.supp ./bin/test

gdb: test
	gdb ./bin/test
