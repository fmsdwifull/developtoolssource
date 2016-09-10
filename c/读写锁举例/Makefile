CC=g++
INC=../include
LIB=pthread
objects = rw_pthread_lock.o 
rw_pthread_lock: $(objects) 
	$(CC) -g -o rw_pthread_lock $(objects) -l$(LIB)
rw_pthread_lock.o:rw_pthread_lock.cpp $(INC)/*.h
	$(CC) -c rw_pthread_lock.cpp  -I $(INC) 
.PHONY : clean 
clean : 
	-rm rw_pthread_lock $(objects) 