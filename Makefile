CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
SRCS = s21_parser.c s21_affine_transform.c
OBJS = $(SRCS:.c=.o)

TARGET = viwer

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test:
	$(CC) $(CFLAGS) -lcheck -lm -lpthread tests.c $(SRCS) -o test
	./test

gcov_report:
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage  $(SRCS) tests.c -pthread -lcheck -pthread -lm -o test
	./test
	lcov -t "test_html" -o unit_test.info -c -d . --rc lcov_branch_coverage=1
	genhtml -o test_html unit_test.info
	open test_html/index.html

clean:
	rm -rf *.gc* *.o test unit_test.info test_html/ test