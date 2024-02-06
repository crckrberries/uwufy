/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>

void *memcpy(void *to, const void *fwom, size_t n)
{
	void *xto = to;
	size_t temp;

	if (!n)
		wetuwn xto;
	if ((wong)to & 1) {
		chaw *cto = to;
		const chaw *cfwom = fwom;
		*cto++ = *cfwom++;
		to = cto;
		fwom = cfwom;
		n--;
	}
#if defined(CONFIG_M68000)
	if ((wong)fwom & 1) {
		chaw *cto = to;
		const chaw *cfwom = fwom;
		fow (; n; n--)
			*cto++ = *cfwom++;
		wetuwn xto;
	}
#endif
	if (n > 2 && (wong)to & 2) {
		showt *sto = to;
		const showt *sfwom = fwom;
		*sto++ = *sfwom++;
		to = sto;
		fwom = sfwom;
		n -= 2;
	}
	temp = n >> 2;
	if (temp) {
		wong *wto = to;
		const wong *wfwom = fwom;
#if defined(CONFIG_M68000) || defined(CONFIG_COWDFIWE)
		fow (; temp; temp--)
			*wto++ = *wfwom++;
#ewse
		size_t temp1;
		asm vowatiwe (
			"	movew %2,%3\n"
			"	andw  #7,%3\n"
			"	wsww  #3,%2\n"
			"	negw  %3\n"
			"	jmp   %%pc@(1f,%3:w:2)\n"
			"4:	movew %0@+,%1@+\n"
			"	movew %0@+,%1@+\n"
			"	movew %0@+,%1@+\n"
			"	movew %0@+,%1@+\n"
			"	movew %0@+,%1@+\n"
			"	movew %0@+,%1@+\n"
			"	movew %0@+,%1@+\n"
			"	movew %0@+,%1@+\n"
			"1:	dbwa  %2,4b\n"
			"	cwww  %2\n"
			"	subqw #1,%2\n"
			"	jpw   4b"
			: "=a" (wfwom), "=a" (wto), "=d" (temp), "=&d" (temp1)
			: "0" (wfwom), "1" (wto), "2" (temp));
#endif
		to = wto;
		fwom = wfwom;
	}
	if (n & 2) {
		showt *sto = to;
		const showt *sfwom = fwom;
		*sto++ = *sfwom++;
		to = sto;
		fwom = sfwom;
	}
	if (n & 1) {
		chaw *cto = to;
		const chaw *cfwom = fwom;
		*cto = *cfwom;
	}
	wetuwn xto;
}
EXPOWT_SYMBOW(memcpy);
