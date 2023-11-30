include config.mk

INCLUDE = -Iinclude
RM  = rm -f
SRCDIR = src
OBJDIR = obj
SRC = main.c screen.c input.c player.c sleep.c
OBJ = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

DEFLDFLAGS = $(shell if echo "" | cc -E -dM -xc - | grep __FreeBSD__ > /dev/null 2>&1; then echo "-lpthread"; fi)

all: $(OUT)

obj:
	mkdir obj

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDE)

$(OUT): obj $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS) $(DEFLDFLAGS)

clean:
	$(RM) $(OUT) $(OBJDIR)/*

.PHONY: default clean
