CFLAGS := -O2 -c #-Wall -Werror
LDFLAGS := -lglut -lGL -lGLU -lm

SRCPATH := ./src
BUILDPATH := ./build

SOURCES :=
OBJECTS := $(addprefix $(BUILDPATH)/,$(SOURCES:%.c=%.o))
SOURCES := $(addprefix $(SRCPATH)/,$(SOURCES))

OUTFILE := minCeraft

PREFIX := /usr
BINDIR := /bin
INSPATH := $(DESTDIR)$(PREFIX)$(BINDIR)

.PHONY : all
all : $(OUTFILE)

$(OUTFILE) : $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^
	strip $@


$(BUILDPATH)/%.o : $(SRCPATH)/%.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY : install
install : $(OUTFILE)
	install -Dm755 "$(OUTFILE)" "$(INSPATH)/$(OUTFILE)"

.PHONY : uninstall
uninstall :
	rm "$(INSPATH)/$(OUTFILE)"

.PHONY : clean
clean :
	rm $(BUILDPATH)/*
	rm $(OUTFILE)
