##############################
#compile:
#CFLAGS="-DDEBUG" make
#for debugging version or just
#make
##############################
CFLAGS := -DDEBUG
CFLAGS += -Wall -g

ifneq (,$(findstring -DDEBUG, $(CFLAGS)))
	LDFLAGS += -Wl,--no-as-needed,-lefence
endif

all: test

test.o: test.c tree.h 

test: test.o

.PHONY: clean print_vars

clean:
	rm -f test *.o

print_vars:
	@echo "===print_vars==="
	@echo "CFLAGS = $(CFLAGS)"
	@echo
	@echo "LDFLAGS = $(LDFLAGS)"



