include config.mk

INCLUDE = -Iinclude
RM  = rm -f
SRCDIR = src
OBJDIR = obj
SRC = main.c screen.c input.c player.c platform.c sleep.c
OBJ = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

all: $(OUT)

obj:
	mkdir obj

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDE)

$(OUT): obj $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OUT) $(OBJDIR)/*

.PHONY: default clean
