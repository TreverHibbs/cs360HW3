INCLUDE=../readable/include/
READABLEDIR=../readable/
CFILES=../readable/readable.c ./test_main.c
CFLAGS=-Wall -pedantic -std=c99 -g -o test_main
OFLAGS=-c -Wall -pedantic -std=c99 -g

test_main.out: readable.o test_main.c $(INCLUDE)readable.h
	gcc $(CFLAGS) $(CFILES) -I$(INCLUDE)

readable.o: $(READABLEDIR)readable.c $(INCLUDE)readable.h
	gcc $(OFLAGS) $(READABLEDIR)readable.c -I$(INCLUDE)

clean: 
	rm -f readable.o test_main.out
	