EXENAME = /mnt/hgfs/linux-win/DxPro/inotify_mod/inotify
CC = gcc
CFLAGS =
INCLUDE = 
LIBS = -lpthread
#DEP_LIBS = ./liba/libyuv.a ./liba/libjpeg.a ./liba/libg711.a ./liba/libimage.a
#HEADER =
OBJS = inotify.o commudpwrite.o 
all: $(EXENAME)
.c.o:
	$(CC) -c $(CFLAGS) $(INCLUDE) $<

$(EXENAME): $(OBJS)
	$(CC) -o $(EXENAME) $(OBJS) $(LIBS) $(DEP_LIBS)

clean:
	rm -f *.o a.out $(EXENAME) core *~
