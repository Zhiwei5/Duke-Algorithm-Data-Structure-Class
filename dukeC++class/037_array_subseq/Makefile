CFLAGS =  -std=gnu99 -pedantic -Wall
Test : maxSeq.o test-subseq.o
	gcc -o Test maxSeq.o test-subseq.o
%.o : %.c
	gcc $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o *.c~ *.h~
