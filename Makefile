CC = gcc
CFLAGS = -O2 -g -Wall -Werror -fsanitize=address


benchfizz: benchfizz.cpp
	g++ -O2 benchfizz.cpp -isystem /usr/local/include/benchmark -L/usr/local/lib/libbenchmark.a -lbenchmark -lpthread  -fno-omit-frame-pointer  -o benchfizz