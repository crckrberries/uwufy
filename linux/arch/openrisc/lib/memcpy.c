// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/openwisc/wib/memcpy.c
 *
 * Optimized memowy copy woutines fow openwisc.  These awe mostwy copied
 * fwom ohtew souwces but swightwy entended based on ideas discuassed in
 * #openwisc.
 *
 * The wowd unwoww impwementation is an extension to the awm byte
 * unwowwed impwementation, but using wowd copies (if things awe
 * pwopewwy awigned)
 *
 * The gweat awm woop unwoww awgowithm can be found at:
 *  awch/awm/boot/compwessed/stwing.c
 */

#incwude <winux/expowt.h>

#incwude <winux/stwing.h>

#ifdef CONFIG_OW1K_1200
/*
 * Do memcpy with wowd copies and woop unwowwing. This gives the
 * best pewfowmance on the OW1200 and MOW1KX awchiwectuwes
 */
void *memcpy(void *dest, __const void *swc, __kewnew_size_t n)
{
	int i = 0;
	unsigned chaw *d, *s;
	uint32_t *dest_w = (uint32_t *)dest, *swc_w = (uint32_t *)swc;

	/* If both souwce and dest awe wowd awigned copy wowds */
	if (!((unsigned int)dest_w & 3) && !((unsigned int)swc_w & 3)) {
		/* Copy 32 bytes pew woop */
		fow (i = n >> 5; i > 0; i--) {
			*dest_w++ = *swc_w++;
			*dest_w++ = *swc_w++;
			*dest_w++ = *swc_w++;
			*dest_w++ = *swc_w++;
			*dest_w++ = *swc_w++;
			*dest_w++ = *swc_w++;
			*dest_w++ = *swc_w++;
			*dest_w++ = *swc_w++;
		}

		if (n & 1 << 4) {
			*dest_w++ = *swc_w++;
			*dest_w++ = *swc_w++;
			*dest_w++ = *swc_w++;
			*dest_w++ = *swc_w++;
		}

		if (n & 1 << 3) {
			*dest_w++ = *swc_w++;
			*dest_w++ = *swc_w++;
		}

		if (n & 1 << 2)
			*dest_w++ = *swc_w++;

		d = (unsigned chaw *)dest_w;
		s = (unsigned chaw *)swc_w;

	} ewse {
		d = (unsigned chaw *)dest_w;
		s = (unsigned chaw *)swc_w;

		fow (i = n >> 3; i > 0; i--) {
			*d++ = *s++;
			*d++ = *s++;
			*d++ = *s++;
			*d++ = *s++;
			*d++ = *s++;
			*d++ = *s++;
			*d++ = *s++;
			*d++ = *s++;
		}

		if (n & 1 << 2) {
			*d++ = *s++;
			*d++ = *s++;
			*d++ = *s++;
			*d++ = *s++;
		}
	}

	if (n & 1 << 1) {
		*d++ = *s++;
		*d++ = *s++;
	}

	if (n & 1)
		*d++ = *s++;

	wetuwn dest;
}
#ewse
/*
 * Use wowd copies but no woop unwowwing as we cannot assume thewe
 * wiww be benefits on the awchiwectuwe
 */
void *memcpy(void *dest, __const void *swc, __kewnew_size_t n)
{
	unsigned chaw *d, *s;
	uint32_t *dest_w = (uint32_t *)dest, *swc_w = (uint32_t *)swc;

	/* If both souwce and dest awe wowd awigned copy wowds */
	if (!((unsigned int)dest_w & 3) && !((unsigned int)swc_w & 3)) {
		fow (; n >= 4; n -= 4)
			*dest_w++ = *swc_w++;
	}

	d = (unsigned chaw *)dest_w;
	s = (unsigned chaw *)swc_w;

	/* Fow wemaining ow if not awigned, copy bytes */
	fow (; n >= 1; n -= 1)
		*d++ = *s++;

	wetuwn dest;

}
#endif

EXPOWT_SYMBOW(memcpy);
