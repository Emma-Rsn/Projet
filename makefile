CC=gcc
FLAGS=-Wall -g
EXE = TLN
LFLAGS   = -Wall -I. -lm
CFLAGS   = -std=c99 -Wall -I.
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf



#Macros des repertoires
SRCDIR   = src
LIBSDIR = libs
OBJDIR   = obj
BINDIR   = bin
SAVEDIR    = save

#creer les repertoires obj et bin si il n'existe pas deja
.PHONY: DIRS
DIRS	 = $(OBJDIR) $(BINDIR) $(SAVEDIR)


$(BINDIR):
	mkdir -p $(BINDIR)
$(OBJDIR):
	mkdir -p $(OBJDIR)
$(SAVEDIR):
	mkdir -p $(SAVEDIR)
	touch save/settings.txt
	chmod a+w save/settings.txt
	cp map.txt save
	
#recupere les fichiers .c et .h du repertoires sources dans 2 variables
SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(LIBSDIR)/*.h)

#creer une liste de tout les .o apartir des .c du repertoire sources
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(DIRS) $(BINDIR)/$(EXE)
	

$(BINDIR)/$(EXE): $(OBJECTS)
	@$(CC) $(FLAGS) $(OBJECTS) $(LFLAGS) -o $@ $(LDFLAGS)

	
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	@$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@
	
clean:
	@rm -f -R $(BINDIR)
	@rm -f -R $(OBJDIR)
	@rm -f -R $(SAVEDIR)








