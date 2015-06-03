CFLAGS += -Wall -g

ifneq (,$(findstring -DDEBUG, $(CFLAGS)))
	LDFLAGS += -Wl,--no-as-needed,-lefence
endif

.PHONY: clean print_vars

clean:
	rm -f test *.o

print_vars:
	@echo "===print_vars==="
	@echo "CFLAGS = $(CFLAGS)"
	@echo
	@echo "LDFLAGS = $(LDFLAGS)"



