CC 	:= gcc

CURR 	:= $(shell pwd)
INCDIR	:= $(CURR)/include
OBJDIR	:= $(CURR)/obj
BINDIR 	:= $(CURR)/bin
SRCDIR	:= $(CURR)/src

BIN	:= $(BINDIR)/fat32parser
INCLUDE	:= $(wildcard $(INCDIR)/*.h)
SRC	:= $(wildcard $(SRCDIR)/*.c)

_OBJ	:= main.o fat32parser.o
OBJ	:= $(patsubst %,$(OBJDIR)/%,$(_OBJ))

all: MKDIR $(BIN)

MKDIR:
	mkdir obj
	mkdir bin

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< -I$(INCDIR)

$(BIN): $(OBJ)
	$(CC) -o $@ $^

.PHONY: clean

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)
