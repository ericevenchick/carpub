OUTPUT = carserver

CC = gcc
CFLAGS = -g
LIBS = -lzmq -lpthread

OBJS = can.o carpub.o carserver.o canstore.o

%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUTPUT): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	-rm *.o carserver

.PHONY: clean
