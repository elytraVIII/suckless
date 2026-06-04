# dmenu-screenshot version
VERSION = 0.1

# paths
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

# flags
CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=200809L -DVERSION=\"$(VERSION)\"
CFLAGS   = -std=c99 -pedantic -Wall -Os $(CPPFLAGS)
LDFLAGS  = -lX11 -lXinerama

# compiler and linker
CC = cc
