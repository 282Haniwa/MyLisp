TARGET	= MyLisp

# LINK (*.o)
LD	= cc
LDFLAGS	= -W

# COMPILE (*.c)
CC	= cc
CC_DEBUG_FLAGS	= -W -O0 -g
CC_RELEASE_FLAGS	= -W -O2

# GENERATOR (*.lex and *.yac)
LEX	= flex
YAC	= yacc

OBJS	= y.tab.o main.o base.o
DEFS	= defs.h
REXP	= rexp.lex
LEXC	= lex.yy.c
SYNS	= syns.yac
YACC	= y.tab.c
SRC	= src.txt
TMP	= tmp.txt

debug: CCFLAGS+=$(CC_DEBUG_FLAGS)
debug: clean all
	lldb $(TARGET)

all: CCFLAGS+=$(CC_RELEASE_FLAGS)
all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(OBJS): $(DEFS)

$(LEXC): $(REXP) $(DEFS)
	$(LEX) $(REXP)

$(YACC): $(SYNS) $(LEXC) $(DEFS)
	$(YAC) $(SYNS)

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	-rm -f $(TARGET) $(OBJS) $(LEXC) $(YACC) $(TMP) *\~

src: all
	./$(TARGET) < $(SRC) > $(TMP)
	cat $(TMP)
