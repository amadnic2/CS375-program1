all: program1 program2 program3

program1: program1.o
	g++ -g -Wall -Werror program1.o -o program1

program1.o: program1.cpp
	g++ -c -g -Wall -Werror ${P1}.cpp -o ${P1}.o

program2: program2.o
	g++ -g -Wall -Werror program2.o -o program2

program2.o: program2.cpp
	g++ -c -g -Wall -Werror program2.cpp -o program2.o

program3: program3.o
	g++ -g -Wall -Werror program3.o -o program3

program3.o: program3.cpp
	g++ -c -g -Wall -Werror program3.cpp -o program3.o


clean:
	rm -rf program1 program2 program3 *.o
