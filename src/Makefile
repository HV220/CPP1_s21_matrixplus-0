# all, clean, test, s21_matrix_oop.a
g = g++
flags = -Wall -Wextra -Werror
LINUX = -lrt -lpthread -lm -lsubunit
LIBS = -lcheck
LFLAGS = -fprofile-arcs -ftest-coverage
OS = $(shell uname -s)

all: build

build: s21_matrix_oop.cpp
	$(g) $(flags) s21_matrix_oop.cpp -o s21_matrix_oop.out
# test:
# s21_matrix_oop.a: 
clean:
	rm *.out
