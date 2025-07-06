# List of source files
SRCS = main.c funcoes.c jogo.c
# List of header files
HDRS = funcoes.h jogo.h

# Define the target executable
TARGET = sudoku

# Compilation flags
CFLAGS = -Wall -Wextra

# Build rule for the target executable
$(TARGET): $(SRCS:.c=.o)
	gcc $(CFLAGS) $^ -o $@

# Build rule for source files
%.o: %.c $(HDRS)
	gcc $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f *.o $(TARGET)