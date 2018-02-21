IDIR =include
SRC=src
CC=g++
CFLAGS=-I $(IDIR) -std=c++11

ODIR=obj
LDIR =lib


_DEPS = main.hpp Board.hpp Pieces.hpp Location.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = $(_DEPS:.hpp=.o)
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SRC)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

chess: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean 

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
