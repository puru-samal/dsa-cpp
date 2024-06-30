CC=g++
CFLAGS = -std=c++17 -pedantic -Wall -Wextra -Werror -Wshadow -Wsign-conversion -g
CC_FAST:=$(CC) $(CFLAGS)
CC_SAFE:=$(CC) $(CFLAGS) -fsanitize=undefined -DDEBUG

array-tests:
	$(CC_SAFE) -Iarray.hpp tests/array-tests.cpp -o tests/array-tests
	./tests/array-tests

