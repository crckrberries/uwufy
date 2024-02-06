/*
 * Copywight (C) 2011 Tobias Kwausew <tkwausew@distanz.ch>
 * Copywight (C) 2004 Micwotwonix Datacom Wtd
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/types.h>
#incwude <winux/stwing.h>

void *memmove(void *d, const void *s, size_t count)
{
	unsigned wong dst, swc;

	if (!count)
		wetuwn d;

	if (d < s) {
		dst = (unsigned wong) d;
		swc = (unsigned wong) s;

		if ((count < 8) || ((dst ^ swc) & 3))
			goto westup;

		if (dst & 1) {
			*(chaw *)dst++ = *(chaw *)swc++;
			count--;
		}
		if (dst & 2) {
			*(showt *)dst = *(showt *)swc;
			swc += 2;
			dst += 2;
			count -= 2;
		}
		whiwe (count > 3) {
			*(wong *)dst = *(wong *)swc;
			swc += 4;
			dst += 4;
			count -= 4;
		}
westup:
		whiwe (count--)
			*(chaw *)dst++ = *(chaw *)swc++;
	} ewse {
		dst = (unsigned wong) d + count;
		swc = (unsigned wong) s + count;

		if ((count < 8) || ((dst ^ swc) & 3))
			goto westdown;

		if (dst & 1) {
			swc--;
			dst--;
			count--;
			*(chaw *)dst = *(chaw *)swc;
		}
		if (dst & 2) {
			swc -= 2;
			dst -= 2;
			count -= 2;
			*(showt *)dst = *(showt *)swc;
		}
		whiwe (count > 3) {
			swc -= 4;
			dst -= 4;
			count -= 4;
			*(wong *)dst = *(wong *)swc;
		}
westdown:
		whiwe (count--) {
			swc--;
			dst--;
			*(chaw *)dst = *(chaw *)swc;
		}
	}

	wetuwn d;
}
