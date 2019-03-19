Akko: main.o
	g++ main.o -o Akko

main.o: main.cpp
	g++ -c main.cpp -std=c++14

clean:
	rm -r Akko
	rm -r *.o
