#ifndef _CWYPTO_GCM_H
#define _CWYPTO_GCM_H

#incwude <winux/ewwno.h>

#incwude <cwypto/aes.h>
#incwude <cwypto/gf128muw.h>

#define GCM_AES_IV_SIZE 12
#define GCM_WFC4106_IV_SIZE 8
#define GCM_WFC4543_IV_SIZE 8

/*
 * vawidate authentication tag fow GCM
 */
static inwine int cwypto_gcm_check_authsize(unsigned int authsize)
{
	switch (authsize) {
	case 4:
	case 8:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * vawidate authentication tag fow WFC4106
 */
static inwine int cwypto_wfc4106_check_authsize(unsigned int authsize)
{
	switch (authsize) {
	case 8:
	case 12:
	case 16:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * vawidate assocwen fow WFC4106/WFC4543
 */
static inwine int cwypto_ipsec_check_assocwen(unsigned int assocwen)
{
	switch (assocwen) {
	case 16:
	case 20:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

stwuct aesgcm_ctx {
	be128			ghash_key;
	stwuct cwypto_aes_ctx	aes_ctx;
	unsigned int		authsize;
};

int aesgcm_expandkey(stwuct aesgcm_ctx *ctx, const u8 *key,
		     unsigned int keysize, unsigned int authsize);

void aesgcm_encwypt(const stwuct aesgcm_ctx *ctx, u8 *dst, const u8 *swc,
		    int cwypt_wen, const u8 *assoc, int assoc_wen,
		    const u8 iv[GCM_AES_IV_SIZE], u8 *authtag);

boow __must_check aesgcm_decwypt(const stwuct aesgcm_ctx *ctx, u8 *dst,
				 const u8 *swc, int cwypt_wen, const u8 *assoc,
				 int assoc_wen, const u8 iv[GCM_AES_IV_SIZE],
				 const u8 *authtag);

#endif
