# settings
CC ?= cc
AR ?= ar
OUTPATH ?= bin/bszgame

CFLAGS ?= -Wall -Wextra -O3 -ggdb -I./external/raylib/src
LDFLAGS ?= -L./bin -l:libraylib.a -lm -lX11

raylib ?= external/rl

$(OUTPATH): src/main.c src/gui.h bin/gui.o bin/libraylib.a | bin
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

.PHONY: run
run: $(OUTPATH)
	$(OUTPATH)

bin/gui.o: src/gui.c src/gui.h | bin
	$(CC) $(CFLAGS) -c $< -o $@

bin/libraylib.a $(raylib)/src/libraylib.a: $(raylib)/src/Makefile | bin
	$(MAKE) -C $(raylib)/src CC=$(CC) AR=$(AR)
	mv $(raylib)/src/libraylib.a $@

bin:
	mkdir -p $@
