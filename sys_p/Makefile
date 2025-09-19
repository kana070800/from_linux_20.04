CC=gcc
TARGET=main.out

all: $(TARGET)

$(TARGET): main.o
	$(CC) -o main.out main.o

main.o: hellolinux.c
	$(CC) -c -o main.o hellolinux.c

clean:
	rm -f *.o
	rm -f $(TARGET)
