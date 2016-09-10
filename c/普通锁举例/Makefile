CC=g++
INC=../include
LIB=pthread
objects = comm_lock.o
comm_lock: $(objects) 
	$(CC) -g -o comm_lock $(objects) -l$(LIB)
comm_lock.o:comm_lock.cpp $(INC)/*.h
	$(CC) -c comm_lock.cpp  -I $(INC) 
.PHONY : clean 
clean : 
	-rm test $(objects) 