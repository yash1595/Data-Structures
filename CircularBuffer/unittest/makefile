# _*_ MakeFile _*_

CC = gcc

CFLAGS = -Wall \
	-Werror \
	-DUNIT_TEST \
	-I../utils/include/

LIBS = -lcunit

vpath %.c ../utils/src

SRC :=  testcustom.c

OBJ := $(SRC:.c=.o)

unittest: $(OBJ)
	$(CC) -o unittest $(OBJ) $(CFLAGS) $(LIBS)

clean:
	rm -f *.o *.xml unittest 
