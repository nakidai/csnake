include include/config.mk

INCLUDE = -Iinclude
RM  = rm -f
SRCDIR = src
OBJDIR = obj
SRC = main.c screen.c input.c player.c sleep.c platform/getch.c platform/game.c
OBJ = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

# Link pthread on FreeBSD
DEFLDFLAGS += $(shell if echo "" | cc -E -dM -xc - | grep __FreeBSD__ > /dev/null 2>&1; then echo "-lpthread"; fi)
# Use ucrt on MinGW
DEFLDFLAGS += $(shell if echo "" | cc -E -dM -xc - | grep __MINGW32__ > /dev/null 2>&1; then echo "-lucrt"; fi)
DEFCFLAGS  += $(shell if echo "" | cc -E -dM -xc - | grep __MINGW32__ > /dev/null 2>&1; then echo "-D_UCRT"; fi)

all: $(OUT)

$(OBJDIR)/platform:
	mkdir -p $(OBJDIR)/platform

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -std=c11 -o $@ $< $(CFLAGS) $(DEFCFLAGS) $(INCLUDE)

$(OUT): $(OBJDIR)/platform $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS) $(DEFLDFLAGS)

clean:
	$(RM) $(OUT) $(OBJDIR)/*.o $(OBJDIR)/platform/*.o

.PHONY: default clean
