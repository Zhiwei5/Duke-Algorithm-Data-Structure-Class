CFLAGS =  -std=gnu99 -pedantic -Wall -Werror
all: Step1 Step2 Step3
Step1 : step1.o
	gcc -o Step1 step1.o
Step2 : step2.o
	gcc -o Step2 step2.o
Step3 : step3.o
	gcc -o Step3 step3.o 
%.o : %.c
	gcc $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o *.c~ *.h~
