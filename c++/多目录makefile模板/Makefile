TARGET=xxx
CC=g++
INC=include
objects = test/test.o src/sharememory.o 
sharmem : $(objects) 
	$(CC) -g -o ${TARGET}$(objects) 
	mv xxx test
test/test.o:test/test.cpp $(INC)/*.h
	$(CC) -c test/test.cpp  -I include
	mv test.o test
src/sharememory.o:src/sharememory.cpp  $(INC)/*.h
	$(CC) -c src/sharememory.cpp  -I include
	mv sharememory.o  src
.PHONY : clean 
clean : 
	-rm ${TARGET} $(objects) 