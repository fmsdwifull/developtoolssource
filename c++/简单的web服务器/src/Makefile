EXENAME = /home/doudou/webserv/src/web_server

CC = g++
CFLAGS =
INCLUDE = 
LIBS = -lpthread
HEADER =
OBJS = web_server.o socknet.o probeth.o

all: $(EXENAME)

.c.o:
	$(CC) -c $(CFLAGS) $(INCLUDE) $<

$(EXENAME): $(OBJS)
	$(CC) -o $(EXENAME) $(OBJS) $(LIBS) $(DEP_LIBS)

clean:
	rm -f *.o a.out $(EXENAME) core *~
