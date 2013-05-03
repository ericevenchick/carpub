OUTPUT = carpub

CC = gcc
CFLAGS = -g
LIBS = -lzmq -lpthread

OBJS = can.o carpub.o carpub_server.o canstore.o canstore_parser.o

%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUTPUT): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	-rm *.o $(OUTPUT)

.PHONY: clean
