CC = gcc
CFLAGS = -O2 -g -Wall -Werror -fsanitize=address
CXXFLAGS = -O2 -g -Wall -Werror -fsanitize=address -fno-omit-frame-pointer

KP_SRC = $(wildcard kp/*.hpp)

benchfizz: benchfizz.cpp
	g++ -O2 benchfizz.cpp -isystem /usr/local/include/benchmark -L/usr/local/lib/libbenchmark.a -lbenchmark -lpthread  -fno-omit-frame-pointer  -o benchfizz

kpcases.o: kpcases.cpp
	g++ -g kpcases.cpp -O2 -o kpcases.o -c

benchk.o: benchk.cpp $(KP_SRC)
	g++ -g benchk.cpp -O1 -o benchk.o -c

benchk: benchk.o kpcases.o
	g++ -g -O1 benchk.o kpcases.o -isystem /usr/local/include/benchmark -L/usr/local/lib/libbenchmark.a -lbenchmark -lpthread  -fno-omit-frame-pointer  -o benchk

testk.o: testk.cpp $(KP_SRC)
	g++ testk.cpp -O2 -o testk.o -c

testk: kpcases.o testk.o
	g++ -O2 testk.o kpcases.o -o testk