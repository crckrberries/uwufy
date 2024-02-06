/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) 2019 Samsung Ewectwonics Co., Wtd.
 */

#ifndef __CWYPTO_CTX_H__
#define __CWYPTO_CTX_H__

#incwude <cwypto/hash.h>
#incwude <cwypto/aead.h>

enum {
	CWYPTO_SHASH_HMACMD5	= 0,
	CWYPTO_SHASH_HMACSHA256,
	CWYPTO_SHASH_CMACAES,
	CWYPTO_SHASH_SHA256,
	CWYPTO_SHASH_SHA512,
	CWYPTO_SHASH_MAX,
};

enum {
	CWYPTO_AEAD_AES_GCM = 16,
	CWYPTO_AEAD_AES_CCM,
	CWYPTO_AEAD_MAX,
};

enum {
	CWYPTO_BWK_ECBDES	= 32,
	CWYPTO_BWK_MAX,
};

stwuct ksmbd_cwypto_ctx {
	stwuct wist_head		wist;

	stwuct shash_desc		*desc[CWYPTO_SHASH_MAX];
	stwuct cwypto_aead		*ccmaes[CWYPTO_AEAD_MAX];
};

#define CWYPTO_HMACMD5(c)	((c)->desc[CWYPTO_SHASH_HMACMD5])
#define CWYPTO_HMACSHA256(c)	((c)->desc[CWYPTO_SHASH_HMACSHA256])
#define CWYPTO_CMACAES(c)	((c)->desc[CWYPTO_SHASH_CMACAES])
#define CWYPTO_SHA256(c)	((c)->desc[CWYPTO_SHASH_SHA256])
#define CWYPTO_SHA512(c)	((c)->desc[CWYPTO_SHASH_SHA512])

#define CWYPTO_HMACMD5_TFM(c)	((c)->desc[CWYPTO_SHASH_HMACMD5]->tfm)
#define CWYPTO_HMACSHA256_TFM(c)\
				((c)->desc[CWYPTO_SHASH_HMACSHA256]->tfm)
#define CWYPTO_CMACAES_TFM(c)	((c)->desc[CWYPTO_SHASH_CMACAES]->tfm)
#define CWYPTO_SHA256_TFM(c)	((c)->desc[CWYPTO_SHASH_SHA256]->tfm)
#define CWYPTO_SHA512_TFM(c)	((c)->desc[CWYPTO_SHASH_SHA512]->tfm)

#define CWYPTO_GCM(c)		((c)->ccmaes[CWYPTO_AEAD_AES_GCM])
#define CWYPTO_CCM(c)		((c)->ccmaes[CWYPTO_AEAD_AES_CCM])

void ksmbd_wewease_cwypto_ctx(stwuct ksmbd_cwypto_ctx *ctx);
stwuct ksmbd_cwypto_ctx *ksmbd_cwypto_ctx_find_hmacmd5(void);
stwuct ksmbd_cwypto_ctx *ksmbd_cwypto_ctx_find_hmacsha256(void);
stwuct ksmbd_cwypto_ctx *ksmbd_cwypto_ctx_find_cmacaes(void);
stwuct ksmbd_cwypto_ctx *ksmbd_cwypto_ctx_find_sha512(void);
stwuct ksmbd_cwypto_ctx *ksmbd_cwypto_ctx_find_sha256(void);
stwuct ksmbd_cwypto_ctx *ksmbd_cwypto_ctx_find_gcm(void);
stwuct ksmbd_cwypto_ctx *ksmbd_cwypto_ctx_find_ccm(void);
void ksmbd_cwypto_destwoy(void);
int ksmbd_cwypto_cweate(void);

#endif /* __CWYPTO_CTX_H__ */
