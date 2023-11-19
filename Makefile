# Компилятор
CC = g++

# Флаги компиляции
CFLAGS = -Wall -Wextra -std=c++17

# Имя исполняемого файла
EXEC = server

# Библиотеки для связывания
LDLIBS = -lcrypto++

# Исходные файлы
SRCS = main.cpp worker.cpp Calculator.cpp ErrorHandling.cpp

# Объектные файлы
OBJS = $(SRCS:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
