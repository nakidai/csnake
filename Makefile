include config.mk

INCLUDE = -Iinclude
RM  = rm -f
SRCDIR = src
OBJDIR = obj
SRC = main.c screen.c input.c player.c sleep.c platform/getch.c
OBJ = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

DEFLDFLAGS = $(shell if echo "" | cc -E -dM -xc - | grep __FreeBSD__ > /dev/null 2>&1; then echo "-lpthread"; fi)

all: $(OUT)

obj:
	mkdir obj

platform: obj
	mkdir obj/platform

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDE)

$(OUT): obj platform $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS) $(DEFLDFLAGS)

clean:
	$(RM) -r $(OUT) $(OBJDIR)/*

.PHONY: default clean
