SRC=$(wildcard *.cpp)
TEST_SRC=$(wildcard tests/*/matrix_*tests.cpp) tests/unit_tests.cpp

PROJECT=matrix_oop.a

OBJ=$(patsubst %.cpp,$(BUILD)/%.o,$(SRC))
TEST_OBJ=$(patsubst tests/%.cpp,$(BUILD)/tests/%.o,$(TEST_SRC))
GCOV_TEST_OBJ=$(patsubst $(BUILD)/%, $(BUILD)/gcov_%, $(OBJ))

BUILD=build

CFLAGS=-Wall -Werror -Wextra -std=c++17
TEST_FLAGS=-lgtest
OS = $(shell uname -s)
ifeq ($(OS), Darwin)
OPEN=open
else
OPEN=xdg-open
endif
GCOV_FLAGS=--coverage
CC=g++

all: $(PROJECT)

$(PROJECT): clang-format $(OBJ)
	mkdir -p $(BUILD)
	ar rc $@ $(OBJ)
	ranlib $@

test: $(PROJECT) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ)  $(PROJECT) -o ./unit_tests $(TEST_FLAGS)
	./unit_tests

gcov_report: $(PROJECT) $(GCOV_TEST_OBJ) $(TEST_OBJ)
	mkdir -p report
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(GCOV_TEST_OBJ) $(TEST_OBJ) -o ./$(BUILD)/gcov_unit_tests $(TEST_FLAGS)
	./$(BUILD)/gcov_unit_tests
	lcov -t "matrix_oop_test" -o ./report/test.info -c -d .
	genhtml -o report ./report/test.info
	$(OPEN) report/index.html

$(BUILD)/%.o: %.cpp
	mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD)/tests/%.o: tests/%.cpp
	echo $(@D)
	mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $< -o $@ $(TEST_FLAGS)

$(BUILD)/gcov_%.o: %.cpp
	$(CC) -c $(CFLAGS) $(GCOV_FLAGS) $< -o ./$@ $(TEST_FLAGS)

clang-format:
	clang-format -i *.cpp *.h ./tests/*.cpp ./tests/*.h ./tests/*/*.cpp

clean:
	rm -rf report/
	rm -rf $(BUILD)
	rm -rf $(PROJECT)
	rm -rf *.o *.a *.gcno *.gcda unit_tests gcov_unit_tests *.info

commit:
	git fetch
	git pull
	git add ..
	git commit -m "update"
