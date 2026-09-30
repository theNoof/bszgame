# settings
CC ?= cc
AR ?= ar
OUTPATH ?= bin/bszgame

CFLAGS ?= -Wall -Wextra -O3 -ggdb -I./external/raylib/src
LDFLAGS ?= -L./bin -l:libraylib.a -lm -lX11

$(OUTPATH): src/main.c src/gui.h bin/gui.o bin/libraylib.a | bin
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

.PHONY: run
run: $(OUTPATH)
	$(OUTPATH)

bin/gui.o: src/gui.c src/gui.h | bin
	$(CC) $(CFLAGS) -c $< -o $@

bin/libraylib.a external/raylib/src/libraylib.a: external/raylib/src/Makefile | bin
	make -C external/raylib/src CC=$(CC) AR=$(AR)
	mv external/raylib/src/libraylib.a $@

bin:
	mkdir -p $@
