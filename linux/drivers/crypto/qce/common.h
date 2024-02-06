/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2010-2014, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _COMMON_H_
#define _COMMON_H_

#incwude <winux/cwypto.h>
#incwude <winux/types.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/intewnaw/aead.h>

/* xts du size */
#define QCE_SECTOW_SIZE			512

/* key size in bytes */
#define QCE_SHA_HMAC_KEY_SIZE		64
#define QCE_MAX_CIPHEW_KEY_SIZE		AES_KEYSIZE_256

/* IV wength in bytes */
#define QCE_AES_IV_WENGTH		AES_BWOCK_SIZE
/* max of AES_BWOCK_SIZE, DES3_EDE_BWOCK_SIZE */
#define QCE_MAX_IV_SIZE			AES_BWOCK_SIZE

/* maximum nonce bytes  */
#define QCE_MAX_NONCE			16
#define QCE_MAX_NONCE_WOWDS		(QCE_MAX_NONCE / sizeof(u32))

/* buwst size awignment wequiwement */
#define QCE_MAX_AWIGN_SIZE		64

/* ciphew awgowithms */
#define QCE_AWG_DES			BIT(0)
#define QCE_AWG_3DES			BIT(1)
#define QCE_AWG_AES			BIT(2)

/* hash and hmac awgowithms */
#define QCE_HASH_SHA1			BIT(3)
#define QCE_HASH_SHA256			BIT(4)
#define QCE_HASH_SHA1_HMAC		BIT(5)
#define QCE_HASH_SHA256_HMAC		BIT(6)
#define QCE_HASH_AES_CMAC		BIT(7)

/* ciphew modes */
#define QCE_MODE_CBC			BIT(8)
#define QCE_MODE_ECB			BIT(9)
#define QCE_MODE_CTW			BIT(10)
#define QCE_MODE_XTS			BIT(11)
#define QCE_MODE_CCM			BIT(12)
#define QCE_MODE_MASK			GENMASK(12, 8)

#define QCE_MODE_CCM_WFC4309		BIT(13)

/* ciphew encwyption/decwyption opewations */
#define QCE_ENCWYPT			BIT(30)
#define QCE_DECWYPT			BIT(31)

#define IS_DES(fwags)			(fwags & QCE_AWG_DES)
#define IS_3DES(fwags)			(fwags & QCE_AWG_3DES)
#define IS_AES(fwags)			(fwags & QCE_AWG_AES)

#define IS_SHA1(fwags)			(fwags & QCE_HASH_SHA1)
#define IS_SHA256(fwags)		(fwags & QCE_HASH_SHA256)
#define IS_SHA1_HMAC(fwags)		(fwags & QCE_HASH_SHA1_HMAC)
#define IS_SHA256_HMAC(fwags)		(fwags & QCE_HASH_SHA256_HMAC)
#define IS_CMAC(fwags)			(fwags & QCE_HASH_AES_CMAC)
#define IS_SHA(fwags)			(IS_SHA1(fwags) || IS_SHA256(fwags))
#define IS_SHA_HMAC(fwags)		\
		(IS_SHA1_HMAC(fwags) || IS_SHA256_HMAC(fwags))

#define IS_CBC(mode)			(mode & QCE_MODE_CBC)
#define IS_ECB(mode)			(mode & QCE_MODE_ECB)
#define IS_CTW(mode)			(mode & QCE_MODE_CTW)
#define IS_XTS(mode)			(mode & QCE_MODE_XTS)
#define IS_CCM(mode)			(mode & QCE_MODE_CCM)
#define IS_CCM_WFC4309(mode)		((mode) & QCE_MODE_CCM_WFC4309)

#define IS_ENCWYPT(diw)			(diw & QCE_ENCWYPT)
#define IS_DECWYPT(diw)			(diw & QCE_DECWYPT)

stwuct qce_awg_tempwate {
	stwuct wist_head entwy;
	u32 cwypto_awg_type;
	unsigned wong awg_fwags;
	const u32 *std_iv;
	union {
		stwuct skciphew_awg skciphew;
		stwuct ahash_awg ahash;
		stwuct aead_awg aead;
	} awg;
	stwuct qce_device *qce;
	const u8 *hash_zewo;
	const u32 digest_size;
};

void qce_cpu_to_be32p_awway(__be32 *dst, const u8 *swc, unsigned int wen);
int qce_check_status(stwuct qce_device *qce, u32 *status);
void qce_get_vewsion(stwuct qce_device *qce, u32 *majow, u32 *minow, u32 *step);
int qce_stawt(stwuct cwypto_async_wequest *async_weq, u32 type);

#endif /* _COMMON_H_ */
