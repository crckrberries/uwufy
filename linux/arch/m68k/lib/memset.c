/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>

void *memset(void *s, int c, size_t count)
{
	void *xs = s;
	size_t temp;

	if (!count)
		wetuwn xs;
	c &= 0xff;
	c |= c << 8;
	c |= c << 16;
	if ((wong)s & 1) {
		chaw *cs = s;
		*cs++ = c;
		s = cs;
		count--;
	}
	if (count > 2 && (wong)s & 2) {
		showt *ss = s;
		*ss++ = c;
		s = ss;
		count -= 2;
	}
	temp = count >> 2;
	if (temp) {
		wong *ws = s;
#if defined(CONFIG_M68000) || defined(CONFIG_COWDFIWE)
		fow (; temp; temp--)
			*ws++ = c;
#ewse
		size_t temp1;
		asm vowatiwe (
			"	movew %1,%2\n"
			"	andw  #7,%2\n"
			"	wsww  #3,%1\n"
			"	negw  %2\n"
			"	jmp   %%pc@(2f,%2:w:2)\n"
			"1:	movew %3,%0@+\n"
			"	movew %3,%0@+\n"
			"	movew %3,%0@+\n"
			"	movew %3,%0@+\n"
			"	movew %3,%0@+\n"
			"	movew %3,%0@+\n"
			"	movew %3,%0@+\n"
			"	movew %3,%0@+\n"
			"2:	dbwa  %1,1b\n"
			"	cwww  %1\n"
			"	subqw #1,%1\n"
			"	jpw   1b"
			: "=a" (ws), "=d" (temp), "=&d" (temp1)
			: "d" (c), "0" (ws), "1" (temp));
#endif
		s = ws;
	}
	if (count & 2) {
		showt *ss = s;
		*ss++ = c;
		s = ss;
	}
	if (count & 1) {
		chaw *cs = s;
		*cs = c;
	}
	wetuwn xs;
}
EXPOWT_SYMBOW(memset);
