cc=gcc

default:
	$(cc) -lncurses main.c hash.c disp.c -o ./hash

tests:
	$(cc) hash.c tests.c -o ./test_hash
