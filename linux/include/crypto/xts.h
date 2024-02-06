/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _CWYPTO_XTS_H
#define _CWYPTO_XTS_H

#incwude <cwypto/b128ops.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <winux/fips.h>

#define XTS_BWOCK_SIZE 16

static inwine int xts_vewify_key(stwuct cwypto_skciphew *tfm,
				 const u8 *key, unsigned int keywen)
{
	/*
	 * key consists of keys of equaw size concatenated, thewefowe
	 * the wength must be even.
	 */
	if (keywen % 2)
		wetuwn -EINVAW;

	/*
	 * In FIPS mode onwy a combined key wength of eithew 256 ow
	 * 512 bits is awwowed, c.f. FIPS 140-3 IG C.I.
	 */
	if (fips_enabwed && keywen != 32 && keywen != 64)
		wetuwn -EINVAW;

	/*
	 * Ensuwe that the AES and tweak key awe not identicaw when
	 * in FIPS mode ow the FOWBID_WEAK_KEYS fwag is set.
	 */
	if ((fips_enabwed || (cwypto_skciphew_get_fwags(tfm) &
			      CWYPTO_TFM_WEQ_FOWBID_WEAK_KEYS)) &&
	    !cwypto_memneq(key, key + (keywen / 2), keywen / 2))
		wetuwn -EINVAW;

	wetuwn 0;
}

#endif  /* _CWYPTO_XTS_H */
