CFLAGS := -O2 -c #-Wall -Werror
LDFLAGS := -lresolv

SRCPATH := ./src
BUILDPATH := ./build

SOURCES := connection.c main.c
OBJECTS := $(addprefix $(BUILDPATH)/,$(SOURCES:%.c=%.o))
SOURCES := $(addprefix $(SRCPATH)/,$(SOURCES))

OUTFILE := demise

PREFIX := /usr
BINDIR := /bin
INSPATH := $(DESTDIR)$(PREFIX)$(BINDIR)

.PHONY : all install uninstall clean

all : $(OUTFILE)

$(OUTFILE) : $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^
	strip $@

$(BUILDPATH)/%.o : $(SRCPATH)/%.c
	$(CC) $(CFLAGS) -o $@ $^

install : $(OUTFILE)
	install -Dm755 "$^" "$(INSPATH)/$^"

uninstall :
	rm "$(INSPATH)/$(OUTFILE)"

clean :
	rm $(BUILDPATH)/*
	rm $(OUTFILE)
