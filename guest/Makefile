include config.mak

CC = gcc
BINARIES = fuzzyagent
CCFLAGS = -I$(TOOLS_DIR)/include -Wall -g -O0 -std=c99
CFLAGS = "-m32"
LDLIBS = -ldl
BINARIES_DIR = $(TOOLS_DIR)/binaries



all: $(BINARIES)

%: %.c
	$(CC) $(CCFLAGS) $(CFLAGS) $< -o $@
	
fuzzyagent: $(TOOLS_DIR)/fuzzyagent-src/fuzzyagent.c $(TOOLS_DIR)/include/fuzzy.h
	$(CC) $(CCFLAGS) $(CFLAGS) $< -o $(BINARIES_DIR)/$@

clean:
	rm -f $(BINARIES)

install: $(BINARIES)
	cp $(BINARIES) $(INSTALL_DIR)

.PHONY: all clean install
