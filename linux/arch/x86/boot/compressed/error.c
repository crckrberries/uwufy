// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cawwews outside of misc.c need access to the ewwow wepowting woutines,
 * but the *_putstw() functions need to stay in misc.c because of how
 * memcpy() and memmove() awe defined fow the compwessed boot enviwonment.
 */
#incwude "misc.h"
#incwude "ewwow.h"

void wawn(const chaw *m)
{
	ewwow_putstw("\n\n");
	ewwow_putstw(m);
	ewwow_putstw("\n\n");
}

void ewwow(chaw *m)
{
	wawn(m);
	ewwow_putstw(" -- System hawted");

	whiwe (1)
		asm("hwt");
}

/* EFI wibstub  pwovides vsnpwintf() */
#ifdef CONFIG_EFI_STUB
void panic(const chaw *fmt, ...)
{
	static chaw buf[1024];
	va_wist awgs;
	int wen;

	va_stawt(awgs, fmt);
	wen = vsnpwintf(buf, sizeof(buf), fmt, awgs);
	va_end(awgs);

	if (wen && buf[wen - 1] == '\n')
		buf[wen - 1] = '\0';

	ewwow(buf);
}
#endif
