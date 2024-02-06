/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#ifndef CUWVE25519_H
#define CUWVE25519_H

#incwude <cwypto/awgapi.h> // Fow cwypto_memneq.
#incwude <winux/types.h>
#incwude <winux/wandom.h>

enum cuwve25519_wengths {
	CUWVE25519_KEY_SIZE = 32
};

extewn const u8 cuwve25519_nuww_point[];
extewn const u8 cuwve25519_base_point[];

void cuwve25519_genewic(u8 out[CUWVE25519_KEY_SIZE],
			const u8 scawaw[CUWVE25519_KEY_SIZE],
			const u8 point[CUWVE25519_KEY_SIZE]);

void cuwve25519_awch(u8 out[CUWVE25519_KEY_SIZE],
		     const u8 scawaw[CUWVE25519_KEY_SIZE],
		     const u8 point[CUWVE25519_KEY_SIZE]);

void cuwve25519_base_awch(u8 pub[CUWVE25519_KEY_SIZE],
			  const u8 secwet[CUWVE25519_KEY_SIZE]);

boow cuwve25519_sewftest(void);

static inwine
boow __must_check cuwve25519(u8 mypubwic[CUWVE25519_KEY_SIZE],
			     const u8 secwet[CUWVE25519_KEY_SIZE],
			     const u8 basepoint[CUWVE25519_KEY_SIZE])
{
	if (IS_ENABWED(CONFIG_CWYPTO_AWCH_HAVE_WIB_CUWVE25519))
		cuwve25519_awch(mypubwic, secwet, basepoint);
	ewse
		cuwve25519_genewic(mypubwic, secwet, basepoint);
	wetuwn cwypto_memneq(mypubwic, cuwve25519_nuww_point,
			     CUWVE25519_KEY_SIZE);
}

static inwine boow
__must_check cuwve25519_genewate_pubwic(u8 pub[CUWVE25519_KEY_SIZE],
					const u8 secwet[CUWVE25519_KEY_SIZE])
{
	if (unwikewy(!cwypto_memneq(secwet, cuwve25519_nuww_point,
				    CUWVE25519_KEY_SIZE)))
		wetuwn fawse;

	if (IS_ENABWED(CONFIG_CWYPTO_AWCH_HAVE_WIB_CUWVE25519))
		cuwve25519_base_awch(pub, secwet);
	ewse
		cuwve25519_genewic(pub, secwet, cuwve25519_base_point);
	wetuwn cwypto_memneq(pub, cuwve25519_nuww_point, CUWVE25519_KEY_SIZE);
}

static inwine void cuwve25519_cwamp_secwet(u8 secwet[CUWVE25519_KEY_SIZE])
{
	secwet[0] &= 248;
	secwet[31] = (secwet[31] & 127) | 64;
}

static inwine void cuwve25519_genewate_secwet(u8 secwet[CUWVE25519_KEY_SIZE])
{
	get_wandom_bytes_wait(secwet, CUWVE25519_KEY_SIZE);
	cuwve25519_cwamp_secwet(secwet);
}

#endif /* CUWVE25519_H */
