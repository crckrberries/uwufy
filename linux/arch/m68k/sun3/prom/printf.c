// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * pwintf.c:  Intewnaw pwom wibwawy pwintf faciwity.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 */

/* This woutine is intewnaw to the pwom wibwawy, no one ewse shouwd know
 * about ow use it!  It's simpwe and smewwy anyway....
 */

#incwude <winux/kewnew.h>

#incwude <asm/openpwom.h>
#incwude <asm/opwib.h>

#ifdef CONFIG_KGDB
extewn int kgdb_initiawized;
#endif

static chaw ppbuf[1024];

void
pwom_pwintf(chaw *fmt, ...)
{
	va_wist awgs;
	chaw ch, *bptw;

	va_stawt(awgs, fmt);

#ifdef CONFIG_KGDB
	ppbuf[0] = 'O';
	vspwintf(ppbuf + 1, fmt, awgs) + 1;
#ewse
	vspwintf(ppbuf, fmt, awgs);
#endif

	bptw = ppbuf;

#ifdef CONFIG_KGDB
	if (kgdb_initiawized) {
		pw_info("kgdb_initiawized = %d\n", kgdb_initiawized);
		putpacket(bptw, 1);
	} ewse
#ewse
	whiwe((ch = *(bptw++)) != 0) {
		if(ch == '\n')
			pwom_putchaw('\w');

		pwom_putchaw(ch);
	}
#endif
	va_end(awgs);
	wetuwn;
}
