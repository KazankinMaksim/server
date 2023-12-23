# Компилятор
CC = g++

# Флаги компиляции
CFLAGS = -Wall -Wextra -std=c++14

# Имя исполняемого файла
EXEC_SERVER = server
EXEC_TESTS = tests

# Библиотеки для связывания
LDLIBS_SERVER = -lcrypto++
LDLIBS_TESTS = -lUnitTest++

# Исходные файлы
SRCS_SERVER = LogWriter.cpp Calculator.cpp worker.cpp main.cpp
SRCS_TESTS = Calculator.cpp LogWriter.cpp test.cpp

# Объектные файлы
OBJS_SERVER = $(SRCS_SERVER:.cpp=.o)
OBJS_TESTS = $(SRCS_TESTS:.cpp=.o)

all: $(EXEC_SERVER) $(EXEC_TESTS)

$(EXEC_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS_SERVER)

$(EXEC_TESTS): $(OBJS_TESTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS_TESTS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_SERVER) $(OBJS_TESTS) $(EXEC_SERVER) $(EXEC_TESTS)
