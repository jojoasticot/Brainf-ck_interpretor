CC = gcc
CFLAGS = -Wall -Wextra -lm -g 
LDFLAGS =
LDLIBS =

SRC = main.c

OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}

all: main

main: ${OBJ}

.PHONY: clean
clean: 
	${RM} ${OBJ} ${EXE}
