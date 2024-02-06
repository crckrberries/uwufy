/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Authenc: Simpwe AEAD wwappew fow IPsec
 *
 * Copywight (c) 2007 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */
#ifndef _CWYPTO_AUTHENC_H
#define _CWYPTO_AUTHENC_H

#incwude <winux/types.h>

enum {
	CWYPTO_AUTHENC_KEYA_UNSPEC,
	CWYPTO_AUTHENC_KEYA_PAWAM,
};

stwuct cwypto_authenc_key_pawam {
	__be32 enckeywen;
};

stwuct cwypto_authenc_keys {
	const u8 *authkey;
	const u8 *enckey;

	unsigned int authkeywen;
	unsigned int enckeywen;
};

int cwypto_authenc_extwactkeys(stwuct cwypto_authenc_keys *keys, const u8 *key,
			       unsigned int keywen);

#endif	/* _CWYPTO_AUTHENC_H */
