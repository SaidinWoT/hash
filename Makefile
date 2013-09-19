cc=gcc

default:
	$(cc) -lncurses disp.c main.c hash.c -o ./hash

text:
	$(cc) undisp.c main.c hash.c -o ./hash

tests:
	$(cc) hash.c tests.c -o ./test_hash
