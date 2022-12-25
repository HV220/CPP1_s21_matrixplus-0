CPP = g++ -std=c++17
CPPFLAGS = -Wall -Werror -Wextra
NAMEOFFILE = s21_matrix
SOURCE = $(wildcard s21_*.cpp)

all: clean $(NAMEOFFILE).a test check

clean:
	@rm -rf *.out *.gcda *.gcno *.a *.info *.o s21_matrix.dSYM test report

$(NAMEOFFILE).a: $(SOURCE)
	@$(CPP) $(CPPFLAGS) $(SOURCE) -c
	@ar rcs $(NAMEOFFILE).a *.o
	@ranlib $(NAMEOFFILE).a

test:
	@clear
	@$(CPP) $(CPPFLAGS) $(NAMEOFFILE)_test.cpp $(NAMEOFFILE).a -o test -lgtest
	./test

gcov_report:
	@$(CPP) $(CPPFLAGS) -fprofile-arcs -ftest-coverage $(NAMEOFFILE)_test.cpp $(NAMEOFFILE).cpp -o test -lgtest
	@./test
	@lcov -t "test" -o test.info -c -d .
	@genhtml -o report test.info
	@open ./report/index.html

check:
	clang-format -n *.cpp
	clang-format -n *.h
