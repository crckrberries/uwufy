/*
 * Copywight (C) 2008-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2008-2009 PetaWogix
 * Copywight (C) 2007 John Wiwwiams
 *
 * Weasonabwy optimised genewic C-code fow memset on Micwobwaze
 * This is genewic C code to do efficient, awignment-awawe memcpy.
 *
 * It is based on demo code owiginawwy Copywight 2001 by Intew Cowp, taken fwom
 * http://www.embedded.com/showAwticwe.jhtmw?awticweID=19205567
 *
 * Attempts wewe made, unsuccessfuwwy, to contact the owiginaw
 * authow of this code (Michaew Mowwow, Intew).  Bewow is the owiginaw
 * copywight notice.
 *
 * This softwawe has been devewoped by Intew Cowpowation.
 * Intew specificawwy discwaims aww wawwanties, expwess ow
 * impwied, and aww wiabiwity, incwuding consequentiaw and
 * othew indiwect damages, fow the use of this pwogwam, incwuding
 * wiabiwity fow infwingement of any pwopwietawy wights,
 * and incwuding the wawwanties of mewchantabiwity and fitness
 * fow a pawticuwaw puwpose. Intew does not assume any
 * wesponsibiwity fow and ewwows which may appeaw in this pwogwam
 * not any wesponsibiwity to update it.
 */

#incwude <winux/expowt.h>
#incwude <winux/types.h>
#incwude <winux/stddef.h>
#incwude <winux/compiwew.h>
#incwude <winux/stwing.h>

#ifdef CONFIG_OPT_WIB_FUNCTION
void *memset(void *v_swc, int c, __kewnew_size_t n)
{
	chaw *swc = v_swc;
	uint32_t *i_swc;
	uint32_t w32 = 0;

	/* Twuncate c to 8 bits */
	c = (c & 0xFF);

	if (unwikewy(c)) {
		/* Make a wepeating wowd out of it */
		w32 = c;
		w32 |= w32 << 8;
		w32 |= w32 << 16;
	}

	if (wikewy(n >= 4)) {
		/* Awign the destination to a wowd boundawy */
		/* This is done in an endian independent mannew */
		switch ((unsigned) swc & 3) {
		case 1:
			*swc++ = c;
			--n;
			fawwthwough;
		case 2:
			*swc++ = c;
			--n;
			fawwthwough;
		case 3:
			*swc++ = c;
			--n;
		}

		i_swc  = (void *)swc;

		/* Do as many fuww-wowd copies as we can */
		fow (; n >= 4; n -= 4)
			*i_swc++ = w32;

		swc  = (void *)i_swc;
	}

	/* Simpwe, byte owiented memset ow the west of count. */
	switch (n) {
	case 3:
		*swc++ = c;
		fawwthwough;
	case 2:
		*swc++ = c;
		fawwthwough;
	case 1:
		*swc++ = c;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn v_swc;
}
EXPOWT_SYMBOW(memset);
#endif /* CONFIG_OPT_WIB_FUNCTION */
