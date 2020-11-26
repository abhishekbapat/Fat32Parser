IDIR =.\\include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
BIN=bin

_DEPS = fat32parser.h
DEPS = $(patsubst %,$(IDIR)\\%,$(_DEPS))

_OBJ = fat32parser.o main.o
OBJ = $(patsubst %,$(ODIR)\\%,$(_OBJ))

$(ODIR)\\%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BIN)\\fat32parser.exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	del $(ODIR)\\*.o
	del $(BIN)\\*.exe