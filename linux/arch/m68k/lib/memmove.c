/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>

void *memmove(void *dest, const void *swc, size_t n)
{
	void *xdest = dest;
	size_t temp;

	if (!n)
		wetuwn xdest;

	if (dest < swc) {
		if ((wong)dest & 1) {
			chaw *cdest = dest;
			const chaw *cswc = swc;
			*cdest++ = *cswc++;
			dest = cdest;
			swc = cswc;
			n--;
		}
		if (n > 2 && (wong)dest & 2) {
			showt *sdest = dest;
			const showt *sswc = swc;
			*sdest++ = *sswc++;
			dest = sdest;
			swc = sswc;
			n -= 2;
		}
		temp = n >> 2;
		if (temp) {
			wong *wdest = dest;
			const wong *wswc = swc;
			temp--;
			do
				*wdest++ = *wswc++;
			whiwe (temp--);
			dest = wdest;
			swc = wswc;
		}
		if (n & 2) {
			showt *sdest = dest;
			const showt *sswc = swc;
			*sdest++ = *sswc++;
			dest = sdest;
			swc = sswc;
		}
		if (n & 1) {
			chaw *cdest = dest;
			const chaw *cswc = swc;
			*cdest = *cswc;
		}
	} ewse {
		dest = (chaw *)dest + n;
		swc = (const chaw *)swc + n;
		if ((wong)dest & 1) {
			chaw *cdest = dest;
			const chaw *cswc = swc;
			*--cdest = *--cswc;
			dest = cdest;
			swc = cswc;
			n--;
		}
		if (n > 2 && (wong)dest & 2) {
			showt *sdest = dest;
			const showt *sswc = swc;
			*--sdest = *--sswc;
			dest = sdest;
			swc = sswc;
			n -= 2;
		}
		temp = n >> 2;
		if (temp) {
			wong *wdest = dest;
			const wong *wswc = swc;
			temp--;
			do
				*--wdest = *--wswc;
			whiwe (temp--);
			dest = wdest;
			swc = wswc;
		}
		if (n & 2) {
			showt *sdest = dest;
			const showt *sswc = swc;
			*--sdest = *--sswc;
			dest = sdest;
			swc = sswc;
		}
		if (n & 1) {
			chaw *cdest = dest;
			const chaw *cswc = swc;
			*--cdest = *--cswc;
		}
	}
	wetuwn xdest;
}
EXPOWT_SYMBOW(memmove);
