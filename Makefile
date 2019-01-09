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

# DEBUGGER
DEBUGGER	= lldb

# FORMATTER
FORMATTER	= clang-format
FORMAT_FLAGS	= -i -style=file

OBJS	= y.tab.o main.o base.o
DEFS	= defs.h
REXP	= rexp.lex
LEXC	= lex.yy.c
SYNS	= syns.yac
YACC	= y.tab.c
SRC	= src.txt
TMP	= tmp.txt
ZIP_FILE	= $(TARGET).zip

debug: CCFLAGS+=$(CC_DEBUG_FLAGS)
debug: clean all
	$(DEBUGGER) $(TARGET)

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
	-rm -f $(TARGET) $(OBJS) $(LEXC) $(YACC) $(TMP) $(ZIP_FILE) *\~

src: all
	./$(TARGET) < $(SRC) > $(TMP)
	cat $(TMP)

format: clean
	$(FORMATTER) $(FORMAT_FLAGS) *.c

zip: clean
	zip  $(ZIP_FILE) *.h *.c $(REXP) $(SYNS)
