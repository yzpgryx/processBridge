CROSS_COMPILE ?=

CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar
RM = rm

CFLAGS += -Wall -I./src

SRCS = ./src/process_bridge.c \
	   ./src/msg_queue.c

OBJS = $(SRCS:.c=.o)

all : shared static test

shared : $(OBJS)
	$(CC) $(CFLAGS) -shared -o libpb.so $(OBJS) -lpthread

static : $(OBJS)
	$(AR) -r libpb.a $(OBJS)

test : shared
	$(CC) $(CFLAGS) -o test_client ./test/test_client.c -L. -lpb
	$(CC) $(CFLAGS) -o test_server ./test/test_server.c -L. -lpb

clean :
	$(RM) -rf src/*.o test/*.o
	$(RM) -rf libpb.*
	$(RM) -rf test_client test_server
	$(RM) -rf test/*.o
