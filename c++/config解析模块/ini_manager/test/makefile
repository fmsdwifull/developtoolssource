XX       = gcc
CFLAGS   = -Wall -ggdb 
LIBS     = 
TARGET   = ./ini_test
INCLUDES = -I../src/
SOURCES  = $(wildcard *.c) $(wildcard ../src/*.c)
OBJS     = $(patsubst %.c,%.o,$(SOURCES)) 
		
all: $(TARGET)    
$(TARGET) : $(OBJS)	
	$(XX) $(OBJS) -o $(TARGET) $(LIBS)  	
	rm -rf $(OBJS) 
				
%.o: %.c  	
	$(XX) $(CFLAGS) $(INCLUDES) -c $< -o $@    
clean:  	
	rm -rf *.o $(TARGET)               
rebuild: clean all
c: clean 
r: rebuild
