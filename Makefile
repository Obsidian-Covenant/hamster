# This will point to the root of the FERRET project
SRCDIR = ./src
DSTDIR = ./bin
TMPDIR = ./tmp

LIBS = -ldl -lpthread
INCLUDES = -I. -I$(SRCDIR) -I$(SRCDIR)/include

CC = gcc
CFLAGS = -g $(INCLUDES) -Wall

PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
INSTALL ?= install

.SUFFIXES: .c .cpp

.PHONY: all clean depend install uninstall
all: $(DSTDIR)/hamster

$(DSTDIR):
	mkdir -p $(DSTDIR)

$(TMPDIR):
	mkdir -p $(TMPDIR)

$(TMPDIR)/%.o: $(SRCDIR)/%.c | $(TMPDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TMPDIR)/%.o: $(SRCDIR)/%.cpp | $(TMPDIR)
	$(CC) $(CFLAGS) -c $< -o $@

c_sources := $(wildcard $(SRCDIR)/*.c)
cpp_sources := $(wildcard $(SRCDIR)/*.cpp)

SRC = $(c_sources) $(cpp_sources)

OBJ = $(addprefix $(TMPDIR)/, $(notdir $(addsuffix .o, $(basename $(SRC)))))

$(DSTDIR)/hamster: $(DSTDIR) $(TMPDIR) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) -lm $(LIBS) -lstdc++

install: $(DSTDIR)/hamster
	$(INSTALL) -d "$(DESTDIR)$(BINDIR)"
	$(INSTALL) -m 0755 "$(DSTDIR)/hamster" "$(DESTDIR)$(BINDIR)/hamster"

uninstall:
	rm -f "$(DESTDIR)$(BINDIR)/hamster"

depend:
	makedepend $(CFLAGS) -Y $(SRC)

clean:
	rm -rf $(OBJ) $(TMPDIR) $(DSTDIR)
