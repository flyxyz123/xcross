CC = gcc
CFLAGS = -g -Wall -lX11
PREFIX = /usr/local

xcross: xcross.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f xcross

install:
	cp -f xcross ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/xcross

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/xcross

.PHONY: clean install uninstall
