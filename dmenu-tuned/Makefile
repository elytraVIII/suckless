# dmenu-tuned - suckless power profiles switcher wrapper
# See LICENSE file for copyright and license details.

include config.mk

SRC = dmenu-tuned.c
OBJ = $(SRC:.c=.o)

all: dmenu-tuned

.c.o:
	$(CC) -c $(CFLAGS) $<

config.h:
	cp config.def.h $@

dmenu-tuned.o: config.h

dmenu-tuned: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

clean:
	rm -f dmenu-tuned $(OBJ) config.h

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f dmenu-tuned $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/dmenu-tuned

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/dmenu-tuned

.PHONY: all clean install uninstall
