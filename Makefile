CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = program
SRC = main.c funkcje.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) test

clean:
	rm -f $(OBJ) $(TARGET)
