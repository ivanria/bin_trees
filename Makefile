export PROG	:= bin_trees
SRC_DIR		:= ./src
export CC	:= gcc
export CFLAGS	:= -Werror -Wall -Wextra -DDEBUG

all:
	$(MAKE) -C $(SRC_DIR) all

.PHONY: clean print_vars cleanall

clean:
	$(MAKE) -C $(SRC_DIR) clean

cleanall:
	$(MAKE) -C $(SRC_DIR) cleanall

print_vars:
	@echo "===print_vars==="
	@echo "PROG		= $(PROG)"
	@echo "SRC_DIR		= $(SRC_DIR)"
	@echo "CFLAGS		= $(CFLAGS)"
	@echo "LDFLAGS		= $(LDFLAGS)"
	$(MAKE) -C $(SRC_DIR) print_vars

