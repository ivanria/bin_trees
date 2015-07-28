SOURCES		:= $(wildcard *.c)
OBJECTS		:= $(patsubst %c,%o,$(SOURCES))
DEPFILES	:= $(patsubst %.c,%.d,$(SOURCES))


$(PROG): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.d

%.d: %.c
	$(CC) $(CFLAGS) -MM -MT '$(patsubst %.c,%.o,$<)' $< -MF $@
	
ifeq (0, $(words $(findstring $(MAKECMDGOALS), clean print_vars cleanall)))
-include $(DEPFILES)
endif

.PHONY: clean all print_vars cleanall

clean:
	rm -rf $(OBJECTS) $(PROG) 

cleanall: clean
	rm -rf $(DEPFILES)

all:
	$(MAKE) $(PROG)

print_vars:
	@echo "===print_vars==="
	@echo "PROG		= $(PROG)"
	@echo "CFLAGS		= $(CFLAGS)"
	@echo "LDFLAGS		= $(LDFLAGS)"
	@echo "NODEP		= $(NODEP)"
	@echo "SOURCES		= $(SOURCES)"
	@echo "DEPFILES		= $(DEPFILES)"


