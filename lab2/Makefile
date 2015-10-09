CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LFLAGS = 
LIBS = -lm
SOURCES = utility.c myshell.c
OBJECTS = $(subst .c,.o,$(SOURCES))
EXE = myshell.exe
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
