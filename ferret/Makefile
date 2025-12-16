# This will point to the root of the FERRET project
SRCDIR = src
DSTDIR = bin
TMPDIR = tmp

LIBS = -ldl -lpthread
INCLUDES=

CC = gcc
CFLAGS = -g $(INCLUDES) -Wall -rdynamic

PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
INSTALL ?= install

.SUFFIXES: .c .cpp

.PHONY: all clean depend install uninstall
all: $(DSTDIR)/ferret

$(DSTDIR):
	mkdir -p $(DSTDIR)

$(TMPDIR):
	mkdir -p $(TMPDIR)

$(TMPDIR)/%.o: $(SRCDIR)/%.c | $(TMPDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TMPDIR)/main.o: $(SRCDIR)/main.cpp | $(TMPDIR)
	$(CC) $(CFLAGS) -c $< -o $@

main_sources := $(wildcard $(SRCDIR)/*.c)
SRC = $(main_sources)
OBJ = $(addprefix $(TMPDIR)/, $(notdir $(addsuffix .o, $(basename $(SRC))))) $(TMPDIR)/main.o

$(DSTDIR)/ferret: $(DSTDIR) $(TMPDIR) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) -lm $(LIBS) -lstdc++ -rdynamic

install: $(DSTDIR)/ferret
	$(INSTALL) -d "$(DESTDIR)$(BINDIR)"
	$(INSTALL) -m 0755 "$(DSTDIR)/ferret" "$(DESTDIR)$(BINDIR)/ferret"

uninstall:
	rm -f "$(DESTDIR)$(BINDIR)/ferret"

depend:
	makedepend $(CFLAGS) -Y $(SRC)

clean:
	rm -rf $(OBJ) $(DSTDIR) $(TMPDIR)
