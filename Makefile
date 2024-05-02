CC=g++
CFLAGS=-Wall -Wextra -Werror -std=c++17 -c
LIBS=

SRC_DIR=./
OBJS_DIR=./build/
SOURCES=$(wildcard $(SRC_DIR)*.cc)
OBJS=$(patsubst $(SRC_DIR)%.cc, $(OBJS_DIR)%.o, $(SOURCES))

TARGET=s21_matrix_oop.a

TESTS_SRC_DIR=./tests/
TESTS_OBJS_DIR=./build/
TESTS_SOURCES=$(wildcard $(TESTS_SRC_DIR)*.cc)
TESTS_OBJS=$(patsubst $(TESTS_SRC_DIR)%.cc, $(TESTS_OBJS_DIR)%.o, $(TESTS_SOURCES))

TESTS_TARGET=$(TESTS_OBJS_DIR)s21_matrix_oop_tests.out

DEV_LIBS=-lgtest -lpthread

all: $(TARGET)

$(TARGET): $(OBJS)
	@printf "[BUILD] \e[92mLinking objects\e[0m\n"
	@ar rcs $@ $(OBJS) $(LIBS)
	@printf "[BUILD] \e[95mBuilt target $@\e[0m\n"

$(OBJS_DIR)%.o: $(SRC_DIR)%.cc
	@printf "[BUILD] \e[32mBuilding $< -> $@\e[0m\n"
	@$(CC) $(CFLAGS) $<  -o $@

$(TESTS_TARGET): $(TARGET) $(TESTS_OBJS)
	@printf "[BUILD] \e[92mLinking objects\e[0m\n"
	@$(CC) -o $@ $(TESTS_OBJS) $(TARGET) $(DEV_LIBS)
	@printf "[BUILD] \e[95mBuilt target $@\e[0m\n"


$(TESTS_OBJS_DIR)%.o: $(TESTS_SRC_DIR)%.cc
	@printf "[BUILD] \e[32mBuilding $< -> $@\e[0m\n"
	@$(CC) $(CFLAGS) $< $(GCOV_FLAG) -o $@


test: $(TESTS_TARGET)
	@./$(TESTS_TARGET)

clean: clean_target clean_tests clean_gcov clean_log
	clear
	@printf "[CLEAN] \e[33mCleaned\e[0m\n"

rebuild: clean all

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./$(TESTS_TARGET)

format:
	@clang-format -i $(SOURCES) $(TESTS_SOURCES) s21_matrix_oop.h

check-format:
	@clang-format -n $(SOURCES) $(TESTS_SOURCES) s21_matrix_oop.h

clean_target:
	@rm -rf $(OBJS) $(TARGET)
	@rm -rf main

clean_tests:
	@rm -rf $(TESTS_OBJS) $(TESTS_TARGET)

clean_gcov:
	@rm -rf tests.info *.gcda *.gcno build/*.gcda build/*.gcno build/report/

clean_log:
	@rm -f tests/*.log
