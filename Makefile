OUTPUT = carserver

CC = gcc
LIBS = -lzmq -lpthread

OBJS = can.o server.o carserver.o

%.o: src/%.c
	$(CC) -c -o $@ $<

$(OUTPUT): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

clean:
	-rm *.o carserver

.PHONY: clean
