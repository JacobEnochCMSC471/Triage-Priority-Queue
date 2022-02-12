myprog : pqueue.o mytest.o
	g++ mytest.o pqueue.o -o myprog

mytest.o : mytest.cpp pqueue.h
	g++ -Wall -c mytest.cpp

pqueue.o : pqueue.cpp pqueue.h 
	g++ -Wall -c -Wall -c pqueue.cpp

clean :
	rm *.o myprog

val1: 
	valgrind ./myprog

run: 
	./myprog
