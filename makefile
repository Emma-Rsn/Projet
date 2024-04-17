CC=gcc
FLAGS=-Wall -g
EXE = TLN
EXETEST = test
LFLAGS   = -Wall -I. -lm
CFLAGS   = -std=c99 -Wall -I. -lcunit
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer



#Macros des repertoires
SRCDIR   = src
LIBSDIR = libs
OBJDIR   = obj
BINDIR   = bin
SAVEDIR    = save
TESTDIR = test

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
	touch save/save.txt
	chmod a+w save/save.txt
	echo "0" >> save/save.txt
	cp texture.txt save
	cp layout3_1.txt save
	cp layoutbeach.txt save
	
#recupere les fichiers .c et .h du repertoires sources dans 2 variables
SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(LIBSDIR)/*.h)
TESTS := $(wildcard $(TESTDIR)/*.c)

#creer une liste de tout les .o apartir des .c du repertoire sources
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJECTEST  := $(TESTS:$(TESTDIR)/%.c=$(TESTDIR)/%.o)

all: $(DIRS) $(BINDIR)/$(EXE)
	

$(BINDIR)/$(EXE): $(OBJECTS)
	@$(CC) $(FLAGS) $(OBJECTS) $(LFLAGS) -o $@ $(LDFLAGS)

	
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	@$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@

test: $(TESTDIR) $(TESTDIR)/$(EXETEST)

$(TESTDIR)/$(EXETEST): $(OBJECTEST)
	@$(CC) $(FLAGS) $(OBJECTEST) $(LFLAGS) -o $@ $(LDFLAGS)

$(OBJECTEST): $(TESTDIR)/%.o : $(TESTDIR)/%.c
	@$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@

$(BINDIR)/$(EXE): $(OBJECTS)
	@$(CC) $(FLAGS) $(OBJECTS) $(LFLAGS) -o $@ $(LDFLAGS)

	
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	@$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@


clean:
	@rm -f -R $(BINDIR)
	@rm -f -R $(OBJDIR)
	@rm -f -R $(SAVEDIR)

restart:
	@rm -f -R $(BINDIR)
	@rm -f -R $(OBJDIR)








