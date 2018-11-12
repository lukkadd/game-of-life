IDIR =../include
CC=cc
CFLAGS=-I$(IDIR)

LIBS=-lcurses -lpanel

_DEPS = game.h graphics.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = main.o game.o graphics.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

conway: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o *~ core $(INCDIR)/*~ 