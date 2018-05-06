CC=gcc
CFLAGS=-I$(IDIR)
OUT=binary.out

IDIR=include
ODIR=src/obj
SDIR=src
BDIR=bin

SRC=$(wildcard $(SDIR)/*.c)
OBJ=$(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(SRC))

$(ODIR)/%.o: $(SDIR)/%.c
	@mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/$(OUT): $(OBJ)
	@mkdir -p $(BDIR)
	$(CC) -o $@ $^

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
	rm -f $(BDIR)/*.out
