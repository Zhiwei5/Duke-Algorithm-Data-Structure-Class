CFLAGS =  -std=gnu99 -pedantic -Wall
Test : test.o
	gcc -o Test test.o
%.o : %.c
	gcc $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o *.c~ *.h~s
