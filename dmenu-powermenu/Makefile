# dmenu-powermenu - suckless power menu wrapper
# See LICENSE file for copyright and license details.

include config.mk

SRC = dmenu-powermenu.c
OBJ = $(SRC:.c=.o)

all: dmenu-powermenu

.c.o:
	$(CC) -c $(CFLAGS) $<

config.h:
	cp config.def.h $@

dmenu-powermenu.o: config.h

dmenu-powermenu: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

clean:
	rm -f dmenu-powermenu $(OBJ)

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f dmenu-powermenu $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/dmenu-powermenu

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/dmenu-powermenu

.PHONY: all clean install uninstall
