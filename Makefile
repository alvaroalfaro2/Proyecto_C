CC=gcc
CFLAGS=`pkg-config --cflags gtk+-3.0`
LFLAGS=`pkg-config --libs gtk+-3.0`
SRC=./Proyecto_C.c
EXE=exe

all:
	gcc $(CFLAGS) $(SRC) -o $(EXE) $(LFLAGS)
run:
	./exe
clean:
	rm exe
