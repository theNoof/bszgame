# settings
CC = cc
OUTPATH ?= bin/bszgame

raylib ?= ./external/rl
uv ?= ./external/libuv-1.53.0
CFLAGS ?= -Wall -Wextra -O3 -ggdb -I./external/raylib/src
LDFLAGS ?= -L./bin -l:libraylib.a -lm -lX11

# things from external/ are not included in dependencies because they are assumed to be available.
# if they are changed, rebuild with `-B`.
raylib ?= external/rl

raylib-CFLAGS = -I$(raylib)/src
raylib-LDFLAGS = -L$(raylib)/src -l:libraylib.a -lm -lX11

CFLAGS ?= -Wall -Wextra -O3 -ggdb $(raylib-CFLAGS) $(uv-CFLAGS)
LDFLAGS ?= $(raylib-LDFLAGS) $(uv-LDFLAGS)

$(OUTPATH): src/main.c src/gui.h bin/gui.o bin/net.o | bin
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

.PHONY: run
run: $(OUTPATH)
	$(OUTPATH)

bin/gui.o: src/gui.c src/gui.h | bin
	$(CC) $(CFLAGS) -c $< -o $@


bin:
	mkdir -p $@
