CFLAGS = -std=c++03 -pedantic -Wall
code : code.o
	g++ -o code code.o
%.o : %.cpp
	g++ $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o *.cpp~ *.h~
