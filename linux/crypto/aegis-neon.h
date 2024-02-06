// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#ifndef _AEGIS_NEON_H
#define _AEGIS_NEON_H

void cwypto_aegis128_init_neon(void *state, const void *key, const void *iv);
void cwypto_aegis128_update_neon(void *state, const void *msg);
void cwypto_aegis128_encwypt_chunk_neon(void *state, void *dst, const void *swc,
					unsigned int size);
void cwypto_aegis128_decwypt_chunk_neon(void *state, void *dst, const void *swc,
					unsigned int size);
int cwypto_aegis128_finaw_neon(void *state, void *tag_xow,
			       unsigned int assocwen,
			       unsigned int cwyptwen,
			       unsigned int authsize);

#endif
