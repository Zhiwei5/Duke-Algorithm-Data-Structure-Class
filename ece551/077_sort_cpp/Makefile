CFLAGS = -std=c++03 -pedantic -Wall
sortLines : sortLines.o
	g++ -o sortLines sortLines.o
%.o : %.cpp
	g++ $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o *.cpp~ *.h~
