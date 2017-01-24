CFLAGS += -std=c99 -Wall -O2

SRC := numstat.c measure.c parse_num_list.c

BIN := numstat
VER ?= $(shell git describe --tags --always --dirty)

ODIR := obj
OBJ := $(patsubst %.c, $(ODIR)/%.o, $(SRC)) $(ODIR)/version.o

all: $(BIN)

clean:
	$(RM) -rf $(BIN) obj/*

$(BIN): $(OBJ)
	@echo LINK $(BIN)
	@$(CC) -O $@ $^

$(ODIR):
	@mkdir -p $@

$(ODIR)/version.o:
	@echo 'const char *VERSION="$(VER)";' | $(CC) -xc -c -o $@ -

$(ODIR)/%.o : %.c
	@echo CC $<
	@$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: all clean
.PHONY: $(ODIR)/version.o

vpath %.c src
vpath %.h src
