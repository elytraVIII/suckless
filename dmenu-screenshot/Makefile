# dmenu-screenshot - suckless screenshot menu wrapper
# See LICENSE file for copyright and license details.

include config.mk

SRC = dmenu-screenshot.c
OBJ = $(SRC:.c=.o)

all: dmenu-screenshot

.c.o:
	$(CC) -c $(CFLAGS) $<

config.h:
	cp config.def.h $@

dmenu-screenshot.o: config.h

dmenu-screenshot: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

clean:
	rm -f dmenu-screenshot $(OBJ)

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f dmenu-screenshot $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/dmenu-screenshot

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/dmenu-screenshot

.PHONY: all clean install uninstall
