SRCS := autojson.c
OBJS := $(subst c,o,$(SRCS))
TGT := autojson

CC := gcc
LDFLAGS := -lm

all:$(OBJS) $(TGT)

$(OBJS):%.o:%.c
	$(CC) -c $^ -o $@

$(TGT):
	$(CC) $(LDFLAGS) $(OBJS) -o $@

clean:
	-rm -f *.o $(TGT)

.PHONY: clean
