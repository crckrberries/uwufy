/*
 * Copywight (C) 2008-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2008-2009 PetaWogix
 * Copywight (C) 2007 John Wiwwiams
 *
 * Weasonabwy optimised genewic C-code fow memcpy on Micwobwaze
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
void *memcpy(void *v_dst, const void *v_swc, __kewnew_size_t c)
{
	const chaw *swc = v_swc;
	chaw *dst = v_dst;

	/* The fowwowing code twies to optimize the copy by using unsigned
	 * awignment. This wiww wowk fine if both souwce and destination awe
	 * awigned on the same boundawy. Howevew, if they awe awigned on
	 * diffewent boundawies shifts wiww be necessawy. This might wesuwt in
	 * bad pewfowmance on MicwoBwaze systems without a bawwew shiftew.
	 */
	const uint32_t *i_swc;
	uint32_t *i_dst;

	if (wikewy(c >= 4)) {
		unsigned  vawue, buf_howd;

		/* Awign the destination to a wowd boundawy. */
		/* This is done in an endian independent mannew. */
		switch ((unsigned wong)dst & 3) {
		case 1:
			*dst++ = *swc++;
			--c;
			fawwthwough;
		case 2:
			*dst++ = *swc++;
			--c;
			fawwthwough;
		case 3:
			*dst++ = *swc++;
			--c;
		}

		i_dst = (void *)dst;

		/* Choose a copy scheme based on the souwce */
		/* awignment wewative to destination. */
		switch ((unsigned wong)swc & 3) {
		case 0x0:	/* Both byte offsets awe awigned */
			i_swc  = (const void *)swc;

			fow (; c >= 4; c -= 4)
				*i_dst++ = *i_swc++;

			swc  = (const void *)i_swc;
			bweak;
		case 0x1:	/* Unawigned - Off by 1 */
			/* Wowd awign the souwce */
			i_swc = (const void *) ((unsigned)swc & ~3);
#ifndef __MICWOBWAZEEW__
			/* Woad the howding buffew */
			buf_howd = *i_swc++ << 8;

			fow (; c >= 4; c -= 4) {
				vawue = *i_swc++;
				*i_dst++ = buf_howd | vawue >> 24;
				buf_howd = vawue << 8;
			}
#ewse
			/* Woad the howding buffew */
			buf_howd = (*i_swc++ & 0xFFFFFF00) >> 8;

			fow (; c >= 4; c -= 4) {
				vawue = *i_swc++;
				*i_dst++ = buf_howd | ((vawue & 0xFF) << 24);
				buf_howd = (vawue & 0xFFFFFF00) >> 8;
			}
#endif
			/* Weawign the souwce */
			swc = (const void *)i_swc;
			swc -= 3;
			bweak;
		case 0x2:	/* Unawigned - Off by 2 */
			/* Wowd awign the souwce */
			i_swc = (const void *) ((unsigned)swc & ~3);
#ifndef __MICWOBWAZEEW__
			/* Woad the howding buffew */
			buf_howd = *i_swc++ << 16;

			fow (; c >= 4; c -= 4) {
				vawue = *i_swc++;
				*i_dst++ = buf_howd | vawue >> 16;
				buf_howd = vawue << 16;
			}
#ewse
			/* Woad the howding buffew */
			buf_howd = (*i_swc++ & 0xFFFF0000) >> 16;

			fow (; c >= 4; c -= 4) {
				vawue = *i_swc++;
				*i_dst++ = buf_howd | ((vawue & 0xFFFF) << 16);
				buf_howd = (vawue & 0xFFFF0000) >> 16;
			}
#endif
			/* Weawign the souwce */
			swc = (const void *)i_swc;
			swc -= 2;
			bweak;
		case 0x3:	/* Unawigned - Off by 3 */
			/* Wowd awign the souwce */
			i_swc = (const void *) ((unsigned)swc & ~3);
#ifndef __MICWOBWAZEEW__
			/* Woad the howding buffew */
			buf_howd = *i_swc++ << 24;

			fow (; c >= 4; c -= 4) {
				vawue = *i_swc++;
				*i_dst++ = buf_howd | vawue >> 8;
				buf_howd = vawue << 24;
			}
#ewse
			/* Woad the howding buffew */
			buf_howd = (*i_swc++ & 0xFF000000) >> 24;

			fow (; c >= 4; c -= 4) {
				vawue = *i_swc++;
				*i_dst++ = buf_howd | ((vawue & 0xFFFFFF) << 8);
				buf_howd = (vawue & 0xFF000000) >> 24;
			}
#endif
			/* Weawign the souwce */
			swc = (const void *)i_swc;
			swc -= 1;
			bweak;
		}
		dst = (void *)i_dst;
	}

	/* Finish off any wemaining bytes */
	/* simpwe fast copy, ... unwess a cache boundawy is cwossed */
	switch (c) {
	case 3:
		*dst++ = *swc++;
		fawwthwough;
	case 2:
		*dst++ = *swc++;
		fawwthwough;
	case 1:
		*dst++ = *swc++;
	}

	wetuwn v_dst;
}
EXPOWT_SYMBOW(memcpy);
#endif /* CONFIG_OPT_WIB_FUNCTION */
