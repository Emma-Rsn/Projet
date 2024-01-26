CC=gcc
FLAGS=-Wall -g
EXE = TLN
LFLAGS   = -Wall -I. -lm
CFLAGS   = -std=c99 -Wall -I.
LDFLAGS = -lSDL2


#Macros des repertoires
SRCDIR   = src
LIBSDIR = libs
OBJDIR   = obj
BINDIR   = bin

#creer les repertoires obj et bin si il n'existe pas deja
.PHONY: DIRS
DIRS	 = $(OBJDIR) $(BINDIR) 


$(BINDIR):
	mkdir -p $(BINDIR)
$(OBJDIR):
	mkdir -p $(OBJDIR)

	
#recupere les fichiers .c et .h du repertoires sources dans 2 variables
SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(LIBSDIR)/*.h)

#creer une liste de tout les .o apartir des .c du repertoire sources
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(DIRS) $(BINDIR)/$(EXE)

$(BINDIR)/$(EXE): $(OBJECTS)
	@$(CC) $(OBJECTS) $(LFLAGS) -o $@ $(LDFLAGS)

	
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	@$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	@rm -f -R $(BINDIR)
	@rm -f -R $(OBJDIR)
