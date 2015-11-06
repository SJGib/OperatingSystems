CC = clang
CFLAGS = -Wall -Wextra -std=c99 -pthread
LFLAGS = 
LIBS = -lm
SOURCES = sudoku_validator.c sudoku_solver.c
OBJECTS = $(subst .c,.o,$(SOURCES))
EXE = sudoku_validator.exe sudoku_solver.exe
.PHONY: clean help

%.exe : %.o
	$(CC) $(CFLAGS) $< $(LIBS) -o $@ 

%.o : %.c
	$(CC) $(CFLAGS) -c $< 

all : $(EXE)

clean:
	rm -f $(OBJECTS) $(EXE) *~

help:
	@echo "Valid targets:"
	@echo "  clean:  removes .o and .exe files"
