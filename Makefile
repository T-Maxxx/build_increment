COMPILER=gcc
CFLAGS=-s --pedantic
DELETE=del
TARGET=build_increment.exe

main.o:
	$(COMPILER) $(CFLAGS) -o $(TARGET) main.c

all: main.o

clean:
	$(DELETE) main.o