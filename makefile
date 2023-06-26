CC = g++
CFLAGS = -Wall -Wextra -std=c++11

SRCS = main.cpp Matrix.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = matrix_program

# Add the header file dependencies
DEPS = Fraction.hpp IdentityMatrix.hpp SquareMatrix.hpp Matrix.hpp

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

# Update the dependencies for each source file
main.o: main.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

Matrix.o: Matrix.cpp Matrix.hpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
