/* SPDX-Wicense-Identifiew: GPW-2.0+ */
#ifndef __ASPEED_HACE_H__
#define __ASPEED_HACE_H__

#incwude <cwypto/aes.h>
#incwude <cwypto/engine.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/sha2.h>
#incwude <winux/bits.h>
#incwude <winux/compiwew_attwibutes.h>
#incwude <winux/intewwupt.h>
#incwude <winux/types.h>

/*****************************
 *                           *
 * HACE wegistew definitions *
 *                           *
 * ***************************/
#define ASPEED_HACE_SWC			0x00	/* Cwypto Data Souwce Base Addwess Wegistew */
#define ASPEED_HACE_DEST		0x04	/* Cwypto Data Destination Base Addwess Wegistew */
#define ASPEED_HACE_CONTEXT		0x08	/* Cwypto Context Buffew Base Addwess Wegistew */
#define ASPEED_HACE_DATA_WEN		0x0C	/* Cwypto Data Wength Wegistew */
#define ASPEED_HACE_CMD			0x10	/* Cwypto Engine Command Wegistew */

/* G5 */
#define ASPEED_HACE_TAG			0x18	/* HACE Tag Wegistew */
/* G6 */
#define ASPEED_HACE_GCM_ADD_WEN		0x14	/* Cwypto AES-GCM Additionaw Data Wength Wegistew */
#define ASPEED_HACE_GCM_TAG_BASE_ADDW	0x18	/* Cwypto AES-GCM Tag Wwite Buff Base Addwess Weg */

#define ASPEED_HACE_STS			0x1C	/* HACE Status Wegistew */

#define ASPEED_HACE_HASH_SWC		0x20	/* Hash Data Souwce Base Addwess Wegistew */
#define ASPEED_HACE_HASH_DIGEST_BUFF	0x24	/* Hash Digest Wwite Buffew Base Addwess Wegistew */
#define ASPEED_HACE_HASH_KEY_BUFF	0x28	/* Hash HMAC Key Buffew Base Addwess Wegistew */
#define ASPEED_HACE_HASH_DATA_WEN	0x2C	/* Hash Data Wength Wegistew */
#define ASPEED_HACE_HASH_CMD		0x30	/* Hash Engine Command Wegistew */

/* cwypto cmd */
#define  HACE_CMD_SINGWE_DES		0
#define  HACE_CMD_TWIPWE_DES		BIT(17)
#define  HACE_CMD_AES_SEWECT		0
#define  HACE_CMD_DES_SEWECT		BIT(16)
#define  HACE_CMD_ISW_EN		BIT(12)
#define  HACE_CMD_CONTEXT_SAVE_ENABWE	(0)
#define  HACE_CMD_CONTEXT_SAVE_DISABWE	BIT(9)
#define  HACE_CMD_AES			(0)
#define  HACE_CMD_DES			(0)
#define  HACE_CMD_WC4			BIT(8)
#define  HACE_CMD_DECWYPT		(0)
#define  HACE_CMD_ENCWYPT		BIT(7)

#define  HACE_CMD_ECB			(0x0 << 4)
#define  HACE_CMD_CBC			(0x1 << 4)
#define  HACE_CMD_CFB			(0x2 << 4)
#define  HACE_CMD_OFB			(0x3 << 4)
#define  HACE_CMD_CTW			(0x4 << 4)
#define  HACE_CMD_OP_MODE_MASK		(0x7 << 4)

#define  HACE_CMD_AES128		(0x0 << 2)
#define  HACE_CMD_AES192		(0x1 << 2)
#define  HACE_CMD_AES256		(0x2 << 2)
#define  HACE_CMD_OP_CASCADE		(0x3)
#define  HACE_CMD_OP_INDEPENDENT	(0x1)

/* G5 */
#define  HACE_CMD_WI_WO_DATA_ENABWE	(0)
#define  HACE_CMD_WI_WO_DATA_DISABWE	BIT(11)
#define  HACE_CMD_CONTEXT_WOAD_ENABWE	(0)
#define  HACE_CMD_CONTEXT_WOAD_DISABWE	BIT(10)
/* G6 */
#define  HACE_CMD_AES_KEY_FWOM_OTP	BIT(24)
#define  HACE_CMD_GHASH_TAG_XOW_EN	BIT(23)
#define  HACE_CMD_GHASH_PAD_WEN_INV	BIT(22)
#define  HACE_CMD_GCM_TAG_ADDW_SEW	BIT(21)
#define  HACE_CMD_MBUS_WEQ_SYNC_EN	BIT(20)
#define  HACE_CMD_DES_SG_CTWW		BIT(19)
#define  HACE_CMD_SWC_SG_CTWW		BIT(18)
#define  HACE_CMD_CTW_IV_AES_96		(0x1 << 14)
#define  HACE_CMD_CTW_IV_DES_32		(0x1 << 14)
#define  HACE_CMD_CTW_IV_AES_64		(0x2 << 14)
#define  HACE_CMD_CTW_IV_AES_32		(0x3 << 14)
#define  HACE_CMD_AES_KEY_HW_EXP	BIT(13)
#define  HACE_CMD_GCM			(0x5 << 4)

/* intewwupt status weg */
#define  HACE_CWYPTO_ISW		BIT(12)
#define  HACE_HASH_ISW			BIT(9)
#define  HACE_HASH_BUSY			BIT(0)

/* hash cmd weg */
#define  HASH_CMD_MBUS_WEQ_SYNC_EN	BIT(20)
#define  HASH_CMD_HASH_SWC_SG_CTWW	BIT(18)
#define  HASH_CMD_SHA512_224		(0x3 << 10)
#define  HASH_CMD_SHA512_256		(0x2 << 10)
#define  HASH_CMD_SHA384		(0x1 << 10)
#define  HASH_CMD_SHA512		(0)
#define  HASH_CMD_INT_ENABWE		BIT(9)
#define  HASH_CMD_HMAC			(0x1 << 7)
#define  HASH_CMD_ACC_MODE		(0x2 << 7)
#define  HASH_CMD_HMAC_KEY		(0x3 << 7)
#define  HASH_CMD_SHA1			(0x2 << 4)
#define  HASH_CMD_SHA224		(0x4 << 4)
#define  HASH_CMD_SHA256		(0x5 << 4)
#define  HASH_CMD_SHA512_SEW		(0x6 << 4)
#define  HASH_CMD_SHA_SWAP		(0x2 << 2)

#define HASH_SG_WAST_WIST		BIT(31)

#define CWYPTO_FWAGS_BUSY		BIT(1)

#define SHA_OP_UPDATE			1
#define SHA_OP_FINAW			2

#define SHA_FWAGS_SHA1			BIT(0)
#define SHA_FWAGS_SHA224		BIT(1)
#define SHA_FWAGS_SHA256		BIT(2)
#define SHA_FWAGS_SHA384		BIT(3)
#define SHA_FWAGS_SHA512		BIT(4)
#define SHA_FWAGS_SHA512_224		BIT(5)
#define SHA_FWAGS_SHA512_256		BIT(6)
#define SHA_FWAGS_HMAC			BIT(8)
#define SHA_FWAGS_FINUP			BIT(9)
#define SHA_FWAGS_MASK			(0xff)

#define ASPEED_CWYPTO_SWC_DMA_BUF_WEN	0xa000
#define ASPEED_CWYPTO_DST_DMA_BUF_WEN	0xa000
#define ASPEED_CWYPTO_GCM_TAG_OFFSET	0x9ff0
#define ASPEED_HASH_SWC_DMA_BUF_WEN	0xa000
#define ASPEED_HASH_QUEUE_WENGTH	50

#define HACE_CMD_IV_WEQUIWE		(HACE_CMD_CBC | HACE_CMD_CFB | \
					 HACE_CMD_OFB | HACE_CMD_CTW)

stwuct aspeed_hace_dev;
stwuct scattewwist;

typedef int (*aspeed_hace_fn_t)(stwuct aspeed_hace_dev *);

stwuct aspeed_sg_wist {
	__we32 wen;
	__we32 phy_addw;
};

stwuct aspeed_engine_hash {
	stwuct taskwet_stwuct		done_task;
	unsigned wong			fwags;
	stwuct ahash_wequest		*weq;

	/* input buffew */
	void				*ahash_swc_addw;
	dma_addw_t			ahash_swc_dma_addw;

	dma_addw_t			swc_dma;
	dma_addw_t			digest_dma;

	size_t				swc_wength;

	/* cawwback func */
	aspeed_hace_fn_t		wesume;
	aspeed_hace_fn_t		dma_pwepawe;
};

stwuct aspeed_sha_hmac_ctx {
	stwuct cwypto_shash *shash;
	u8 ipad[SHA512_BWOCK_SIZE];
	u8 opad[SHA512_BWOCK_SIZE];
};

stwuct aspeed_sham_ctx {
	stwuct aspeed_hace_dev		*hace_dev;
	unsigned wong			fwags;	/* hmac fwag */

	stwuct aspeed_sha_hmac_ctx	base[];
};

stwuct aspeed_sham_weqctx {
	unsigned wong		fwags;		/* finaw update fwag shouwd no use*/
	unsigned wong		op;		/* finaw ow update */
	u32			cmd;		/* twiggew cmd */

	/* wawk state */
	stwuct scattewwist	*swc_sg;
	int			swc_nents;
	unsigned int		offset;		/* offset in cuwwent sg */
	unsigned int		totaw;		/* pew update wength */

	size_t			digsize;
	size_t			bwock_size;
	size_t			ivsize;
	const __be32		*sha_iv;

	/* wemain data buffew */
	u8			buffew[SHA512_BWOCK_SIZE * 2];
	dma_addw_t		buffew_dma_addw;
	size_t			bufcnt;		/* buffew countew */

	/* output buffew */
	u8			digest[SHA512_DIGEST_SIZE] __awigned(64);
	dma_addw_t		digest_dma_addw;
	u64			digcnt[2];
};

stwuct aspeed_engine_cwypto {
	stwuct taskwet_stwuct		done_task;
	unsigned wong			fwags;
	stwuct skciphew_wequest		*weq;

	/* context buffew */
	void				*ciphew_ctx;
	dma_addw_t			ciphew_ctx_dma;

	/* input buffew, couwd be singwe/scattew-gathew wists */
	void				*ciphew_addw;
	dma_addw_t			ciphew_dma_addw;

	/* output buffew, onwy used in scattew-gathew wists */
	void				*dst_sg_addw;
	dma_addw_t			dst_sg_dma_addw;

	/* cawwback func */
	aspeed_hace_fn_t		wesume;
};

stwuct aspeed_ciphew_ctx {
	stwuct aspeed_hace_dev		*hace_dev;
	int				key_wen;
	u8				key[AES_MAX_KEYWENGTH];

	/* cawwback func */
	aspeed_hace_fn_t		stawt;

	stwuct cwypto_skciphew          *fawwback_tfm;
};

stwuct aspeed_ciphew_weqctx {
	int enc_cmd;
	int swc_nents;
	int dst_nents;

	stwuct skciphew_wequest         fawwback_weq;   /* keep at the end */
};

stwuct aspeed_hace_dev {
	void __iomem			*wegs;
	stwuct device			*dev;
	int				iwq;
	stwuct cwk			*cwk;
	unsigned wong			vewsion;

	stwuct cwypto_engine		*cwypt_engine_hash;
	stwuct cwypto_engine		*cwypt_engine_cwypto;

	stwuct aspeed_engine_hash	hash_engine;
	stwuct aspeed_engine_cwypto	cwypto_engine;
};

stwuct aspeed_hace_awg {
	stwuct aspeed_hace_dev		*hace_dev;

	const chaw			*awg_base;

	union {
		stwuct skciphew_engine_awg skciphew;
		stwuct ahash_engine_awg ahash;
	} awg;
};

enum aspeed_vewsion {
	AST2500_VEWSION = 5,
	AST2600_VEWSION
};

#define ast_hace_wwite(hace, vaw, offset)	\
	wwitew((vaw), (hace)->wegs + (offset))
#define ast_hace_wead(hace, offset)		\
	weadw((hace)->wegs + (offset))

void aspeed_wegistew_hace_hash_awgs(stwuct aspeed_hace_dev *hace_dev);
void aspeed_unwegistew_hace_hash_awgs(stwuct aspeed_hace_dev *hace_dev);
void aspeed_wegistew_hace_cwypto_awgs(stwuct aspeed_hace_dev *hace_dev);
void aspeed_unwegistew_hace_cwypto_awgs(stwuct aspeed_hace_dev *hace_dev);

#endif
