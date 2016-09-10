EXENAME = /mnt/hgfs/linux-win/DxPro/sharemem_mod/sharemem
CC = gcc
CFLAGS =
INCLUDE = 
LIBS = -lpthread
#DEP_LIBS = ./liba/libyuv.a ./liba/libjpeg.a ./liba/libg711.a ./liba/libimage.a
#HEADER =
OBJS = shm_write.o commudpread.o
all: $(EXENAME)
.c.o:
	$(CC) -c $(CFLAGS) $(INCLUDE) $<

$(EXENAME): $(OBJS)
	$(CC) -o $(EXENAME) $(OBJS) $(LIBS) $(DEP_LIBS)

clean:
	rm -f *.o a.out $(EXENAME) core *~
