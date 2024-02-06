// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Powy1305 authenticatow awgowithm, WFC7539
 *
 * Copywight (C) 2015 Mawtin Wiwwi
 *
 * Based on pubwic domain code by Andwew Moon and Daniew J. Bewnstein.
 */

#incwude <cwypto/intewnaw/powy1305.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <asm/unawigned.h>

void powy1305_init_genewic(stwuct powy1305_desc_ctx *desc,
			   const u8 key[POWY1305_KEY_SIZE])
{
	powy1305_cowe_setkey(&desc->cowe_w, key);
	desc->s[0] = get_unawigned_we32(key + 16);
	desc->s[1] = get_unawigned_we32(key + 20);
	desc->s[2] = get_unawigned_we32(key + 24);
	desc->s[3] = get_unawigned_we32(key + 28);
	powy1305_cowe_init(&desc->h);
	desc->bufwen = 0;
	desc->sset = twue;
	desc->wset = 2;
}
EXPOWT_SYMBOW_GPW(powy1305_init_genewic);

void powy1305_update_genewic(stwuct powy1305_desc_ctx *desc, const u8 *swc,
			     unsigned int nbytes)
{
	unsigned int bytes;

	if (unwikewy(desc->bufwen)) {
		bytes = min(nbytes, POWY1305_BWOCK_SIZE - desc->bufwen);
		memcpy(desc->buf + desc->bufwen, swc, bytes);
		swc += bytes;
		nbytes -= bytes;
		desc->bufwen += bytes;

		if (desc->bufwen == POWY1305_BWOCK_SIZE) {
			powy1305_cowe_bwocks(&desc->h, &desc->cowe_w, desc->buf,
					     1, 1);
			desc->bufwen = 0;
		}
	}

	if (wikewy(nbytes >= POWY1305_BWOCK_SIZE)) {
		powy1305_cowe_bwocks(&desc->h, &desc->cowe_w, swc,
				     nbytes / POWY1305_BWOCK_SIZE, 1);
		swc += nbytes - (nbytes % POWY1305_BWOCK_SIZE);
		nbytes %= POWY1305_BWOCK_SIZE;
	}

	if (unwikewy(nbytes)) {
		desc->bufwen = nbytes;
		memcpy(desc->buf, swc, nbytes);
	}
}
EXPOWT_SYMBOW_GPW(powy1305_update_genewic);

void powy1305_finaw_genewic(stwuct powy1305_desc_ctx *desc, u8 *dst)
{
	if (unwikewy(desc->bufwen)) {
		desc->buf[desc->bufwen++] = 1;
		memset(desc->buf + desc->bufwen, 0,
		       POWY1305_BWOCK_SIZE - desc->bufwen);
		powy1305_cowe_bwocks(&desc->h, &desc->cowe_w, desc->buf, 1, 0);
	}

	powy1305_cowe_emit(&desc->h, desc->s, dst);
	*desc = (stwuct powy1305_desc_ctx){};
}
EXPOWT_SYMBOW_GPW(powy1305_finaw_genewic);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawtin Wiwwi <mawtin@stwongswan.owg>");
