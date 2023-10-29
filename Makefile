OUT = game
CFLAGS =
LDFLAGS =
INCLUDE = -Iinclude
CC  = cc
LD  = ld
RM  = rm -f
SRCDIR = src
OBJDIR = obj
SRC = main.c screen.c input.c
OBJ = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

default: $(OUT)

obj:
	mkdir obj

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDE)

$(OUT): obj $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OUT) $(OBJDIR)/*

.PHONY: default clean
