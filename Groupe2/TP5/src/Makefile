CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS =

SRC = \
	evaluation.c \
	lexer.c \
	parseur.c \
	variables.c \
	repl.c

OBJ = $(SRC:.c=.o)

TARGET = interpreteur

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean