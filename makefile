CC = g++
CFLAGS = -Wall -Wextra -std=c++11

SRCS = main.cpp Matrix.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = matrix_program.exe

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
