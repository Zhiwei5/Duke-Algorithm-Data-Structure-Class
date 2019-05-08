CFLAGS = -std=gnu99 -pedantic -Wall
Test : power.o test-power.o
	gcc -o Test power.o test-power.o
%.o : %.c
	gcc $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o *.c~ *.h~
