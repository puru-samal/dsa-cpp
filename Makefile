CC=g++
CFLAGS = -std=c++17 -pedantic -Wall -Wextra -Werror -Wshadow -Wsign-conversion -g
CC_FAST:=$(CC) $(CFLAGS)
CC_SAFE:=$(CC) $(CFLAGS) -fsanitize=undefined -DDEBUG

sort-tests:
	$(CC_SAFE) -Isort.hpp tests/sort-tests.cpp -o tests/sort-tests
	./tests/sort-tests

	