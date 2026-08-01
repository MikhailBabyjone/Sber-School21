CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
LDFLAGS = -lm

BUILD_DIR = ../../build
TARGET = $(BUILD_DIR)/Quest_3

OBJS = main_executable_module.o data_io.o data_stat.o data_process.o decision.o

.PHONY: all clean rebuild

all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

main_executable_module.o: main_executable_module.c
	$(CC) $(CFLAGS) -c main_executable_module.c -o main_executable_module.o

data_io.o: ../data_libs/data_io.c
	$(CC) $(CFLAGS) -c ../data_libs/data_io.c -o data_io.o

data_stat.o: ../data_libs/data_stat.c
	$(CC) $(CFLAGS) -c ../data_libs/data_stat.c -o data_stat.o

data_process.o: ../data_module/data_process.c
	$(CC) $(CFLAGS) -c ../data_module/data_process.c -o data_process.o

decision.o: ../yet_another_decision_module/decision.c
	$(CC) $(CFLAGS) -c ../yet_another_decision_module/decision.c -o decision.o

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all