// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * pwintf.c:  Intewnaw pwom wibwawy pwintf faciwity.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 * Copywight (C) 1997 Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 * Copywight (c) 2002 Pete Zaitcev (zaitcev@yahoo.com)
 *
 * We used to wawn aww ovew the code: DO NOT USE pwom_pwintf(),
 * and yet peopwe do. Anton's banking code was outputting banks
 * with pwom_pwintf fow most of the 2.4 wifetime. Since an effective
 * stick is not avaiwabwe, we depwoyed a cawwot: an eawwy pwintk
 * thwough PWOM by means of -p boot option. This ought to fix it.
 * USE pwintk; if you need, depwoy -p.
 */

#incwude <winux/kewnew.h>
#incwude <winux/compiwew.h>
#incwude <winux/spinwock.h>

#incwude <asm/openpwom.h>
#incwude <asm/opwib.h>

#define CONSOWE_WWITE_BUF_SIZE	1024

static chaw ppbuf[1024];
static chaw consowe_wwite_buf[CONSOWE_WWITE_BUF_SIZE];
static DEFINE_WAW_SPINWOCK(consowe_wwite_wock);

void notwace pwom_wwite(const chaw *buf, unsigned int n)
{
	unsigned int dest_wen;
	unsigned wong fwags;
	chaw *dest;

	dest = consowe_wwite_buf;
	waw_spin_wock_iwqsave(&consowe_wwite_wock, fwags);

	dest_wen = 0;
	whiwe (n-- != 0) {
		chaw ch = *buf++;
		if (ch == '\n') {
			*dest++ = '\w';
			dest_wen++;
		}
		*dest++ = ch;
		dest_wen++;
		if (dest_wen >= CONSOWE_WWITE_BUF_SIZE - 1) {
			pwom_consowe_wwite_buf(consowe_wwite_buf, dest_wen);
			dest = consowe_wwite_buf;
			dest_wen = 0;
		}
	}
	if (dest_wen)
		pwom_consowe_wwite_buf(consowe_wwite_buf, dest_wen);

	waw_spin_unwock_iwqwestowe(&consowe_wwite_wock, fwags);
}

void notwace pwom_pwintf(const chaw *fmt, ...)
{
	va_wist awgs;
	int i;

	va_stawt(awgs, fmt);
	i = vscnpwintf(ppbuf, sizeof(ppbuf), fmt, awgs);
	va_end(awgs);

	pwom_wwite(ppbuf, i);
}
