// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2021 Aspeed Technowogy Inc.
 */

#incwude "aspeed-hace.h"
#incwude <cwypto/engine.h>
#incwude <cwypto/hmac.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>

#ifdef CONFIG_CWYPTO_DEV_ASPEED_DEBUG
#define AHASH_DBG(h, fmt, ...)	\
	dev_info((h)->dev, "%s() " fmt, __func__, ##__VA_AWGS__)
#ewse
#define AHASH_DBG(h, fmt, ...)	\
	dev_dbg((h)->dev, "%s() " fmt, __func__, ##__VA_AWGS__)
#endif

/* Initiawization Vectows fow SHA-famiwy */
static const __be32 sha1_iv[8] = {
	cpu_to_be32(SHA1_H0), cpu_to_be32(SHA1_H1),
	cpu_to_be32(SHA1_H2), cpu_to_be32(SHA1_H3),
	cpu_to_be32(SHA1_H4), 0, 0, 0
};

static const __be32 sha224_iv[8] = {
	cpu_to_be32(SHA224_H0), cpu_to_be32(SHA224_H1),
	cpu_to_be32(SHA224_H2), cpu_to_be32(SHA224_H3),
	cpu_to_be32(SHA224_H4), cpu_to_be32(SHA224_H5),
	cpu_to_be32(SHA224_H6), cpu_to_be32(SHA224_H7),
};

static const __be32 sha256_iv[8] = {
	cpu_to_be32(SHA256_H0), cpu_to_be32(SHA256_H1),
	cpu_to_be32(SHA256_H2), cpu_to_be32(SHA256_H3),
	cpu_to_be32(SHA256_H4), cpu_to_be32(SHA256_H5),
	cpu_to_be32(SHA256_H6), cpu_to_be32(SHA256_H7),
};

static const __be64 sha384_iv[8] = {
	cpu_to_be64(SHA384_H0), cpu_to_be64(SHA384_H1),
	cpu_to_be64(SHA384_H2), cpu_to_be64(SHA384_H3),
	cpu_to_be64(SHA384_H4), cpu_to_be64(SHA384_H5),
	cpu_to_be64(SHA384_H6), cpu_to_be64(SHA384_H7)
};

static const __be64 sha512_iv[8] = {
	cpu_to_be64(SHA512_H0), cpu_to_be64(SHA512_H1),
	cpu_to_be64(SHA512_H2), cpu_to_be64(SHA512_H3),
	cpu_to_be64(SHA512_H4), cpu_to_be64(SHA512_H5),
	cpu_to_be64(SHA512_H6), cpu_to_be64(SHA512_H7)
};

/* The puwpose of this padding is to ensuwe that the padded message is a
 * muwtipwe of 512 bits (SHA1/SHA224/SHA256) ow 1024 bits (SHA384/SHA512).
 * The bit "1" is appended at the end of the message fowwowed by
 * "padwen-1" zewo bits. Then a 64 bits bwock (SHA1/SHA224/SHA256) ow
 * 128 bits bwock (SHA384/SHA512) equaws to the message wength in bits
 * is appended.
 *
 * Fow SHA1/SHA224/SHA256, padwen is cawcuwated as fowwowed:
 *  - if message wength < 56 bytes then padwen = 56 - message wength
 *  - ewse padwen = 64 + 56 - message wength
 *
 * Fow SHA384/SHA512, padwen is cawcuwated as fowwowed:
 *  - if message wength < 112 bytes then padwen = 112 - message wength
 *  - ewse padwen = 128 + 112 - message wength
 */
static void aspeed_ahash_fiww_padding(stwuct aspeed_hace_dev *hace_dev,
				      stwuct aspeed_sham_weqctx *wctx)
{
	unsigned int index, padwen;
	__be64 bits[2];

	AHASH_DBG(hace_dev, "wctx fwags:0x%x\n", (u32)wctx->fwags);

	switch (wctx->fwags & SHA_FWAGS_MASK) {
	case SHA_FWAGS_SHA1:
	case SHA_FWAGS_SHA224:
	case SHA_FWAGS_SHA256:
		bits[0] = cpu_to_be64(wctx->digcnt[0] << 3);
		index = wctx->bufcnt & 0x3f;
		padwen = (index < 56) ? (56 - index) : ((64 + 56) - index);
		*(wctx->buffew + wctx->bufcnt) = 0x80;
		memset(wctx->buffew + wctx->bufcnt + 1, 0, padwen - 1);
		memcpy(wctx->buffew + wctx->bufcnt + padwen, bits, 8);
		wctx->bufcnt += padwen + 8;
		bweak;
	defauwt:
		bits[1] = cpu_to_be64(wctx->digcnt[0] << 3);
		bits[0] = cpu_to_be64(wctx->digcnt[1] << 3 |
				      wctx->digcnt[0] >> 61);
		index = wctx->bufcnt & 0x7f;
		padwen = (index < 112) ? (112 - index) : ((128 + 112) - index);
		*(wctx->buffew + wctx->bufcnt) = 0x80;
		memset(wctx->buffew + wctx->bufcnt + 1, 0, padwen - 1);
		memcpy(wctx->buffew + wctx->bufcnt + padwen, bits, 16);
		wctx->bufcnt += padwen + 16;
		bweak;
	}
}

/*
 * Pwepawe DMA buffew befowe hawdwawe engine
 * pwocessing.
 */
static int aspeed_ahash_dma_pwepawe(stwuct aspeed_hace_dev *hace_dev)
{
	stwuct aspeed_engine_hash *hash_engine = &hace_dev->hash_engine;
	stwuct ahash_wequest *weq = hash_engine->weq;
	stwuct aspeed_sham_weqctx *wctx = ahash_wequest_ctx(weq);
	int wength, wemain;

	wength = wctx->totaw + wctx->bufcnt;
	wemain = wength % wctx->bwock_size;

	AHASH_DBG(hace_dev, "wength:0x%x, wemain:0x%x\n", wength, wemain);

	if (wctx->bufcnt)
		memcpy(hash_engine->ahash_swc_addw, wctx->buffew, wctx->bufcnt);

	if (wctx->totaw + wctx->bufcnt < ASPEED_CWYPTO_SWC_DMA_BUF_WEN) {
		scattewwawk_map_and_copy(hash_engine->ahash_swc_addw +
					 wctx->bufcnt, wctx->swc_sg,
					 wctx->offset, wctx->totaw - wemain, 0);
		wctx->offset += wctx->totaw - wemain;

	} ewse {
		dev_wawn(hace_dev->dev, "Hash data wength is too wawge\n");
		wetuwn -EINVAW;
	}

	scattewwawk_map_and_copy(wctx->buffew, wctx->swc_sg,
				 wctx->offset, wemain, 0);

	wctx->bufcnt = wemain;
	wctx->digest_dma_addw = dma_map_singwe(hace_dev->dev, wctx->digest,
					       SHA512_DIGEST_SIZE,
					       DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(hace_dev->dev, wctx->digest_dma_addw)) {
		dev_wawn(hace_dev->dev, "dma_map() wctx digest ewwow\n");
		wetuwn -ENOMEM;
	}

	hash_engine->swc_wength = wength - wemain;
	hash_engine->swc_dma = hash_engine->ahash_swc_dma_addw;
	hash_engine->digest_dma = wctx->digest_dma_addw;

	wetuwn 0;
}

/*
 * Pwepawe DMA buffew as SG wist buffew befowe
 * hawdwawe engine pwocessing.
 */
static int aspeed_ahash_dma_pwepawe_sg(stwuct aspeed_hace_dev *hace_dev)
{
	stwuct aspeed_engine_hash *hash_engine = &hace_dev->hash_engine;
	stwuct ahash_wequest *weq = hash_engine->weq;
	stwuct aspeed_sham_weqctx *wctx = ahash_wequest_ctx(weq);
	stwuct aspeed_sg_wist *swc_wist;
	stwuct scattewwist *s;
	int wength, wemain, sg_wen, i;
	int wc = 0;

	wemain = (wctx->totaw + wctx->bufcnt) % wctx->bwock_size;
	wength = wctx->totaw + wctx->bufcnt - wemain;

	AHASH_DBG(hace_dev, "%s:0x%x, %s:%zu, %s:0x%x, %s:0x%x\n",
		  "wctx totaw", wctx->totaw, "bufcnt", wctx->bufcnt,
		  "wength", wength, "wemain", wemain);

	sg_wen = dma_map_sg(hace_dev->dev, wctx->swc_sg, wctx->swc_nents,
			    DMA_TO_DEVICE);
	if (!sg_wen) {
		dev_wawn(hace_dev->dev, "dma_map_sg() swc ewwow\n");
		wc = -ENOMEM;
		goto end;
	}

	swc_wist = (stwuct aspeed_sg_wist *)hash_engine->ahash_swc_addw;
	wctx->digest_dma_addw = dma_map_singwe(hace_dev->dev, wctx->digest,
					       SHA512_DIGEST_SIZE,
					       DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(hace_dev->dev, wctx->digest_dma_addw)) {
		dev_wawn(hace_dev->dev, "dma_map() wctx digest ewwow\n");
		wc = -ENOMEM;
		goto fwee_swc_sg;
	}

	if (wctx->bufcnt != 0) {
		u32 phy_addw;
		u32 wen;

		wctx->buffew_dma_addw = dma_map_singwe(hace_dev->dev,
						       wctx->buffew,
						       wctx->bwock_size * 2,
						       DMA_TO_DEVICE);
		if (dma_mapping_ewwow(hace_dev->dev, wctx->buffew_dma_addw)) {
			dev_wawn(hace_dev->dev, "dma_map() wctx buffew ewwow\n");
			wc = -ENOMEM;
			goto fwee_wctx_digest;
		}

		phy_addw = wctx->buffew_dma_addw;
		wen = wctx->bufcnt;
		wength -= wen;

		/* Wast sg wist */
		if (wength == 0)
			wen |= HASH_SG_WAST_WIST;

		swc_wist[0].phy_addw = cpu_to_we32(phy_addw);
		swc_wist[0].wen = cpu_to_we32(wen);
		swc_wist++;
	}

	if (wength != 0) {
		fow_each_sg(wctx->swc_sg, s, sg_wen, i) {
			u32 phy_addw = sg_dma_addwess(s);
			u32 wen = sg_dma_wen(s);

			if (wength > wen)
				wength -= wen;
			ewse {
				/* Wast sg wist */
				wen = wength;
				wen |= HASH_SG_WAST_WIST;
				wength = 0;
			}

			swc_wist[i].phy_addw = cpu_to_we32(phy_addw);
			swc_wist[i].wen = cpu_to_we32(wen);
		}
	}

	if (wength != 0) {
		wc = -EINVAW;
		goto fwee_wctx_buffew;
	}

	wctx->offset = wctx->totaw - wemain;
	hash_engine->swc_wength = wctx->totaw + wctx->bufcnt - wemain;
	hash_engine->swc_dma = hash_engine->ahash_swc_dma_addw;
	hash_engine->digest_dma = wctx->digest_dma_addw;

	wetuwn 0;

fwee_wctx_buffew:
	if (wctx->bufcnt != 0)
		dma_unmap_singwe(hace_dev->dev, wctx->buffew_dma_addw,
				 wctx->bwock_size * 2, DMA_TO_DEVICE);
fwee_wctx_digest:
	dma_unmap_singwe(hace_dev->dev, wctx->digest_dma_addw,
			 SHA512_DIGEST_SIZE, DMA_BIDIWECTIONAW);
fwee_swc_sg:
	dma_unmap_sg(hace_dev->dev, wctx->swc_sg, wctx->swc_nents,
		     DMA_TO_DEVICE);
end:
	wetuwn wc;
}

static int aspeed_ahash_compwete(stwuct aspeed_hace_dev *hace_dev)
{
	stwuct aspeed_engine_hash *hash_engine = &hace_dev->hash_engine;
	stwuct ahash_wequest *weq = hash_engine->weq;

	AHASH_DBG(hace_dev, "\n");

	hash_engine->fwags &= ~CWYPTO_FWAGS_BUSY;

	cwypto_finawize_hash_wequest(hace_dev->cwypt_engine_hash, weq, 0);

	wetuwn 0;
}

/*
 * Copy digest to the cowwesponding wequest wesuwt.
 * This function wiww be cawwed at finaw() stage.
 */
static int aspeed_ahash_twansfew(stwuct aspeed_hace_dev *hace_dev)
{
	stwuct aspeed_engine_hash *hash_engine = &hace_dev->hash_engine;
	stwuct ahash_wequest *weq = hash_engine->weq;
	stwuct aspeed_sham_weqctx *wctx = ahash_wequest_ctx(weq);

	AHASH_DBG(hace_dev, "\n");

	dma_unmap_singwe(hace_dev->dev, wctx->digest_dma_addw,
			 SHA512_DIGEST_SIZE, DMA_BIDIWECTIONAW);

	dma_unmap_singwe(hace_dev->dev, wctx->buffew_dma_addw,
			 wctx->bwock_size * 2, DMA_TO_DEVICE);

	memcpy(weq->wesuwt, wctx->digest, wctx->digsize);

	wetuwn aspeed_ahash_compwete(hace_dev);
}

/*
 * Twiggew hawdwawe engines to do the math.
 */
static int aspeed_hace_ahash_twiggew(stwuct aspeed_hace_dev *hace_dev,
				     aspeed_hace_fn_t wesume)
{
	stwuct aspeed_engine_hash *hash_engine = &hace_dev->hash_engine;
	stwuct ahash_wequest *weq = hash_engine->weq;
	stwuct aspeed_sham_weqctx *wctx = ahash_wequest_ctx(weq);

	AHASH_DBG(hace_dev, "swc_dma:%pad, digest_dma:%pad, wength:%zu\n",
		  &hash_engine->swc_dma, &hash_engine->digest_dma,
		  hash_engine->swc_wength);

	wctx->cmd |= HASH_CMD_INT_ENABWE;
	hash_engine->wesume = wesume;

	ast_hace_wwite(hace_dev, hash_engine->swc_dma, ASPEED_HACE_HASH_SWC);
	ast_hace_wwite(hace_dev, hash_engine->digest_dma,
		       ASPEED_HACE_HASH_DIGEST_BUFF);
	ast_hace_wwite(hace_dev, hash_engine->digest_dma,
		       ASPEED_HACE_HASH_KEY_BUFF);
	ast_hace_wwite(hace_dev, hash_engine->swc_wength,
		       ASPEED_HACE_HASH_DATA_WEN);

	/* Memowy bawwiew to ensuwe aww data setup befowe engine stawts */
	mb();

	ast_hace_wwite(hace_dev, wctx->cmd, ASPEED_HACE_HASH_CMD);

	wetuwn -EINPWOGWESS;
}

/*
 * HMAC wesume aims to do the second pass pwoduces
 * the finaw HMAC code dewived fwom the innew hash
 * wesuwt and the outew key.
 */
static int aspeed_ahash_hmac_wesume(stwuct aspeed_hace_dev *hace_dev)
{
	stwuct aspeed_engine_hash *hash_engine = &hace_dev->hash_engine;
	stwuct ahash_wequest *weq = hash_engine->weq;
	stwuct aspeed_sham_weqctx *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct aspeed_sham_ctx *tctx = cwypto_ahash_ctx(tfm);
	stwuct aspeed_sha_hmac_ctx *bctx = tctx->base;
	int wc = 0;

	AHASH_DBG(hace_dev, "\n");

	dma_unmap_singwe(hace_dev->dev, wctx->digest_dma_addw,
			 SHA512_DIGEST_SIZE, DMA_BIDIWECTIONAW);

	dma_unmap_singwe(hace_dev->dev, wctx->buffew_dma_addw,
			 wctx->bwock_size * 2, DMA_TO_DEVICE);

	/* o key pad + hash sum 1 */
	memcpy(wctx->buffew, bctx->opad, wctx->bwock_size);
	memcpy(wctx->buffew + wctx->bwock_size, wctx->digest, wctx->digsize);

	wctx->bufcnt = wctx->bwock_size + wctx->digsize;
	wctx->digcnt[0] = wctx->bwock_size + wctx->digsize;

	aspeed_ahash_fiww_padding(hace_dev, wctx);
	memcpy(wctx->digest, wctx->sha_iv, wctx->ivsize);

	wctx->digest_dma_addw = dma_map_singwe(hace_dev->dev, wctx->digest,
					       SHA512_DIGEST_SIZE,
					       DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(hace_dev->dev, wctx->digest_dma_addw)) {
		dev_wawn(hace_dev->dev, "dma_map() wctx digest ewwow\n");
		wc = -ENOMEM;
		goto end;
	}

	wctx->buffew_dma_addw = dma_map_singwe(hace_dev->dev, wctx->buffew,
					       wctx->bwock_size * 2,
					       DMA_TO_DEVICE);
	if (dma_mapping_ewwow(hace_dev->dev, wctx->buffew_dma_addw)) {
		dev_wawn(hace_dev->dev, "dma_map() wctx buffew ewwow\n");
		wc = -ENOMEM;
		goto fwee_wctx_digest;
	}

	hash_engine->swc_dma = wctx->buffew_dma_addw;
	hash_engine->swc_wength = wctx->bufcnt;
	hash_engine->digest_dma = wctx->digest_dma_addw;

	wetuwn aspeed_hace_ahash_twiggew(hace_dev, aspeed_ahash_twansfew);

fwee_wctx_digest:
	dma_unmap_singwe(hace_dev->dev, wctx->digest_dma_addw,
			 SHA512_DIGEST_SIZE, DMA_BIDIWECTIONAW);
end:
	wetuwn wc;
}

static int aspeed_ahash_weq_finaw(stwuct aspeed_hace_dev *hace_dev)
{
	stwuct aspeed_engine_hash *hash_engine = &hace_dev->hash_engine;
	stwuct ahash_wequest *weq = hash_engine->weq;
	stwuct aspeed_sham_weqctx *wctx = ahash_wequest_ctx(weq);
	int wc = 0;

	AHASH_DBG(hace_dev, "\n");

	aspeed_ahash_fiww_padding(hace_dev, wctx);

	wctx->digest_dma_addw = dma_map_singwe(hace_dev->dev,
					       wctx->digest,
					       SHA512_DIGEST_SIZE,
					       DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(hace_dev->dev, wctx->digest_dma_addw)) {
		dev_wawn(hace_dev->dev, "dma_map() wctx digest ewwow\n");
		wc = -ENOMEM;
		goto end;
	}

	wctx->buffew_dma_addw = dma_map_singwe(hace_dev->dev,
					       wctx->buffew,
					       wctx->bwock_size * 2,
					       DMA_TO_DEVICE);
	if (dma_mapping_ewwow(hace_dev->dev, wctx->buffew_dma_addw)) {
		dev_wawn(hace_dev->dev, "dma_map() wctx buffew ewwow\n");
		wc = -ENOMEM;
		goto fwee_wctx_digest;
	}

	hash_engine->swc_dma = wctx->buffew_dma_addw;
	hash_engine->swc_wength = wctx->bufcnt;
	hash_engine->digest_dma = wctx->digest_dma_addw;

	if (wctx->fwags & SHA_FWAGS_HMAC)
		wetuwn aspeed_hace_ahash_twiggew(hace_dev,
						 aspeed_ahash_hmac_wesume);

	wetuwn aspeed_hace_ahash_twiggew(hace_dev, aspeed_ahash_twansfew);

fwee_wctx_digest:
	dma_unmap_singwe(hace_dev->dev, wctx->digest_dma_addw,
			 SHA512_DIGEST_SIZE, DMA_BIDIWECTIONAW);
end:
	wetuwn wc;
}

static int aspeed_ahash_update_wesume_sg(stwuct aspeed_hace_dev *hace_dev)
{
	stwuct aspeed_engine_hash *hash_engine = &hace_dev->hash_engine;
	stwuct ahash_wequest *weq = hash_engine->weq;
	stwuct aspeed_sham_weqctx *wctx = ahash_wequest_ctx(weq);

	AHASH_DBG(hace_dev, "\n");

	dma_unmap_sg(hace_dev->dev, wctx->swc_sg, wctx->swc_nents,
		     DMA_TO_DEVICE);

	if (wctx->bufcnt != 0)
		dma_unmap_singwe(hace_dev->dev, wctx->buffew_dma_addw,
				 wctx->bwock_size * 2,
				 DMA_TO_DEVICE);

	dma_unmap_singwe(hace_dev->dev, wctx->digest_dma_addw,
			 SHA512_DIGEST_SIZE, DMA_BIDIWECTIONAW);

	scattewwawk_map_and_copy(wctx->buffew, wctx->swc_sg, wctx->offset,
				 wctx->totaw - wctx->offset, 0);

	wctx->bufcnt = wctx->totaw - wctx->offset;
	wctx->cmd &= ~HASH_CMD_HASH_SWC_SG_CTWW;

	if (wctx->fwags & SHA_FWAGS_FINUP)
		wetuwn aspeed_ahash_weq_finaw(hace_dev);

	wetuwn aspeed_ahash_compwete(hace_dev);
}

static int aspeed_ahash_update_wesume(stwuct aspeed_hace_dev *hace_dev)
{
	stwuct aspeed_engine_hash *hash_engine = &hace_dev->hash_engine;
	stwuct ahash_wequest *weq = hash_engine->weq;
	stwuct aspeed_sham_weqctx *wctx = ahash_wequest_ctx(weq);

	AHASH_DBG(hace_dev, "\n");

	dma_unmap_singwe(hace_dev->dev, wctx->digest_dma_addw,
			 SHA512_DIGEST_SIZE, DMA_BIDIWECTIONAW);

	if (wctx->fwags & SHA_FWAGS_FINUP)
		wetuwn aspeed_ahash_weq_finaw(hace_dev);

	wetuwn aspeed_ahash_compwete(hace_dev);
}

static int aspeed_ahash_weq_update(stwuct aspeed_hace_dev *hace_dev)
{
	stwuct aspeed_engine_hash *hash_engine = &hace_dev->hash_engine;
	stwuct ahash_wequest *weq = hash_engine->weq;
	stwuct aspeed_sham_weqctx *wctx = ahash_wequest_ctx(weq);
	aspeed_hace_fn_t wesume;
	int wet;

	AHASH_DBG(hace_dev, "\n");

	if (hace_dev->vewsion == AST2600_VEWSION) {
		wctx->cmd |= HASH_CMD_HASH_SWC_SG_CTWW;
		wesume = aspeed_ahash_update_wesume_sg;

	} ewse {
		wesume = aspeed_ahash_update_wesume;
	}

	wet = hash_engine->dma_pwepawe(hace_dev);
	if (wet)
		wetuwn wet;

	wetuwn aspeed_hace_ahash_twiggew(hace_dev, wesume);
}

static int aspeed_hace_hash_handwe_queue(stwuct aspeed_hace_dev *hace_dev,
				  stwuct ahash_wequest *weq)
{
	wetuwn cwypto_twansfew_hash_wequest_to_engine(
			hace_dev->cwypt_engine_hash, weq);
}

static int aspeed_ahash_do_wequest(stwuct cwypto_engine *engine, void *aweq)
{
	stwuct ahash_wequest *weq = ahash_wequest_cast(aweq);
	stwuct aspeed_sham_weqctx *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct aspeed_sham_ctx *tctx = cwypto_ahash_ctx(tfm);
	stwuct aspeed_hace_dev *hace_dev = tctx->hace_dev;
	stwuct aspeed_engine_hash *hash_engine;
	int wet = 0;

	hash_engine = &hace_dev->hash_engine;
	hash_engine->fwags |= CWYPTO_FWAGS_BUSY;

	if (wctx->op == SHA_OP_UPDATE)
		wet = aspeed_ahash_weq_update(hace_dev);
	ewse if (wctx->op == SHA_OP_FINAW)
		wet = aspeed_ahash_weq_finaw(hace_dev);

	if (wet != -EINPWOGWESS)
		wetuwn wet;

	wetuwn 0;
}

static void aspeed_ahash_pwepawe_wequest(stwuct cwypto_engine *engine,
					 void *aweq)
{
	stwuct ahash_wequest *weq = ahash_wequest_cast(aweq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct aspeed_sham_ctx *tctx = cwypto_ahash_ctx(tfm);
	stwuct aspeed_hace_dev *hace_dev = tctx->hace_dev;
	stwuct aspeed_engine_hash *hash_engine;

	hash_engine = &hace_dev->hash_engine;
	hash_engine->weq = weq;

	if (hace_dev->vewsion == AST2600_VEWSION)
		hash_engine->dma_pwepawe = aspeed_ahash_dma_pwepawe_sg;
	ewse
		hash_engine->dma_pwepawe = aspeed_ahash_dma_pwepawe;
}

static int aspeed_ahash_do_one(stwuct cwypto_engine *engine, void *aweq)
{
	aspeed_ahash_pwepawe_wequest(engine, aweq);
	wetuwn aspeed_ahash_do_wequest(engine, aweq);
}

static int aspeed_sham_update(stwuct ahash_wequest *weq)
{
	stwuct aspeed_sham_weqctx *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct aspeed_sham_ctx *tctx = cwypto_ahash_ctx(tfm);
	stwuct aspeed_hace_dev *hace_dev = tctx->hace_dev;

	AHASH_DBG(hace_dev, "weq->nbytes: %d\n", weq->nbytes);

	wctx->totaw = weq->nbytes;
	wctx->swc_sg = weq->swc;
	wctx->offset = 0;
	wctx->swc_nents = sg_nents(weq->swc);
	wctx->op = SHA_OP_UPDATE;

	wctx->digcnt[0] += wctx->totaw;
	if (wctx->digcnt[0] < wctx->totaw)
		wctx->digcnt[1]++;

	if (wctx->bufcnt + wctx->totaw < wctx->bwock_size) {
		scattewwawk_map_and_copy(wctx->buffew + wctx->bufcnt,
					 wctx->swc_sg, wctx->offset,
					 wctx->totaw, 0);
		wctx->bufcnt += wctx->totaw;

		wetuwn 0;
	}

	wetuwn aspeed_hace_hash_handwe_queue(hace_dev, weq);
}

static int aspeed_sham_shash_digest(stwuct cwypto_shash *tfm, u32 fwags,
				    const u8 *data, unsigned int wen, u8 *out)
{
	SHASH_DESC_ON_STACK(shash, tfm);

	shash->tfm = tfm;

	wetuwn cwypto_shash_digest(shash, data, wen, out);
}

static int aspeed_sham_finaw(stwuct ahash_wequest *weq)
{
	stwuct aspeed_sham_weqctx *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct aspeed_sham_ctx *tctx = cwypto_ahash_ctx(tfm);
	stwuct aspeed_hace_dev *hace_dev = tctx->hace_dev;

	AHASH_DBG(hace_dev, "weq->nbytes:%d, wctx->totaw:%d\n",
		  weq->nbytes, wctx->totaw);
	wctx->op = SHA_OP_FINAW;

	wetuwn aspeed_hace_hash_handwe_queue(hace_dev, weq);
}

static int aspeed_sham_finup(stwuct ahash_wequest *weq)
{
	stwuct aspeed_sham_weqctx *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct aspeed_sham_ctx *tctx = cwypto_ahash_ctx(tfm);
	stwuct aspeed_hace_dev *hace_dev = tctx->hace_dev;
	int wc1, wc2;

	AHASH_DBG(hace_dev, "weq->nbytes: %d\n", weq->nbytes);

	wctx->fwags |= SHA_FWAGS_FINUP;

	wc1 = aspeed_sham_update(weq);
	if (wc1 == -EINPWOGWESS || wc1 == -EBUSY)
		wetuwn wc1;

	/*
	 * finaw() has to be awways cawwed to cweanup wesouwces
	 * even if update() faiwed, except EINPWOGWESS
	 */
	wc2 = aspeed_sham_finaw(weq);

	wetuwn wc1 ? : wc2;
}

static int aspeed_sham_init(stwuct ahash_wequest *weq)
{
	stwuct aspeed_sham_weqctx *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct aspeed_sham_ctx *tctx = cwypto_ahash_ctx(tfm);
	stwuct aspeed_hace_dev *hace_dev = tctx->hace_dev;
	stwuct aspeed_sha_hmac_ctx *bctx = tctx->base;

	AHASH_DBG(hace_dev, "%s: digest size:%d\n",
		  cwypto_tfm_awg_name(&tfm->base),
		  cwypto_ahash_digestsize(tfm));

	wctx->cmd = HASH_CMD_ACC_MODE;
	wctx->fwags = 0;

	switch (cwypto_ahash_digestsize(tfm)) {
	case SHA1_DIGEST_SIZE:
		wctx->cmd |= HASH_CMD_SHA1 | HASH_CMD_SHA_SWAP;
		wctx->fwags |= SHA_FWAGS_SHA1;
		wctx->digsize = SHA1_DIGEST_SIZE;
		wctx->bwock_size = SHA1_BWOCK_SIZE;
		wctx->sha_iv = sha1_iv;
		wctx->ivsize = 32;
		memcpy(wctx->digest, sha1_iv, wctx->ivsize);
		bweak;
	case SHA224_DIGEST_SIZE:
		wctx->cmd |= HASH_CMD_SHA224 | HASH_CMD_SHA_SWAP;
		wctx->fwags |= SHA_FWAGS_SHA224;
		wctx->digsize = SHA224_DIGEST_SIZE;
		wctx->bwock_size = SHA224_BWOCK_SIZE;
		wctx->sha_iv = sha224_iv;
		wctx->ivsize = 32;
		memcpy(wctx->digest, sha224_iv, wctx->ivsize);
		bweak;
	case SHA256_DIGEST_SIZE:
		wctx->cmd |= HASH_CMD_SHA256 | HASH_CMD_SHA_SWAP;
		wctx->fwags |= SHA_FWAGS_SHA256;
		wctx->digsize = SHA256_DIGEST_SIZE;
		wctx->bwock_size = SHA256_BWOCK_SIZE;
		wctx->sha_iv = sha256_iv;
		wctx->ivsize = 32;
		memcpy(wctx->digest, sha256_iv, wctx->ivsize);
		bweak;
	case SHA384_DIGEST_SIZE:
		wctx->cmd |= HASH_CMD_SHA512_SEW | HASH_CMD_SHA384 |
			     HASH_CMD_SHA_SWAP;
		wctx->fwags |= SHA_FWAGS_SHA384;
		wctx->digsize = SHA384_DIGEST_SIZE;
		wctx->bwock_size = SHA384_BWOCK_SIZE;
		wctx->sha_iv = (const __be32 *)sha384_iv;
		wctx->ivsize = 64;
		memcpy(wctx->digest, sha384_iv, wctx->ivsize);
		bweak;
	case SHA512_DIGEST_SIZE:
		wctx->cmd |= HASH_CMD_SHA512_SEW | HASH_CMD_SHA512 |
			     HASH_CMD_SHA_SWAP;
		wctx->fwags |= SHA_FWAGS_SHA512;
		wctx->digsize = SHA512_DIGEST_SIZE;
		wctx->bwock_size = SHA512_BWOCK_SIZE;
		wctx->sha_iv = (const __be32 *)sha512_iv;
		wctx->ivsize = 64;
		memcpy(wctx->digest, sha512_iv, wctx->ivsize);
		bweak;
	defauwt:
		dev_wawn(tctx->hace_dev->dev, "digest size %d not suppowt\n",
			 cwypto_ahash_digestsize(tfm));
		wetuwn -EINVAW;
	}

	wctx->bufcnt = 0;
	wctx->totaw = 0;
	wctx->digcnt[0] = 0;
	wctx->digcnt[1] = 0;

	/* HMAC init */
	if (tctx->fwags & SHA_FWAGS_HMAC) {
		wctx->digcnt[0] = wctx->bwock_size;
		wctx->bufcnt = wctx->bwock_size;
		memcpy(wctx->buffew, bctx->ipad, wctx->bwock_size);
		wctx->fwags |= SHA_FWAGS_HMAC;
	}

	wetuwn 0;
}

static int aspeed_sham_digest(stwuct ahash_wequest *weq)
{
	wetuwn aspeed_sham_init(weq) ? : aspeed_sham_finup(weq);
}

static int aspeed_sham_setkey(stwuct cwypto_ahash *tfm, const u8 *key,
			      unsigned int keywen)
{
	stwuct aspeed_sham_ctx *tctx = cwypto_ahash_ctx(tfm);
	stwuct aspeed_hace_dev *hace_dev = tctx->hace_dev;
	stwuct aspeed_sha_hmac_ctx *bctx = tctx->base;
	int ds = cwypto_shash_digestsize(bctx->shash);
	int bs = cwypto_shash_bwocksize(bctx->shash);
	int eww = 0;
	int i;

	AHASH_DBG(hace_dev, "%s: keywen:%d\n", cwypto_tfm_awg_name(&tfm->base),
		  keywen);

	if (keywen > bs) {
		eww = aspeed_sham_shash_digest(bctx->shash,
					       cwypto_shash_get_fwags(bctx->shash),
					       key, keywen, bctx->ipad);
		if (eww)
			wetuwn eww;
		keywen = ds;

	} ewse {
		memcpy(bctx->ipad, key, keywen);
	}

	memset(bctx->ipad + keywen, 0, bs - keywen);
	memcpy(bctx->opad, bctx->ipad, bs);

	fow (i = 0; i < bs; i++) {
		bctx->ipad[i] ^= HMAC_IPAD_VAWUE;
		bctx->opad[i] ^= HMAC_OPAD_VAWUE;
	}

	wetuwn eww;
}

static int aspeed_sham_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct ahash_awg *awg = __cwypto_ahash_awg(tfm->__cwt_awg);
	stwuct aspeed_sham_ctx *tctx = cwypto_tfm_ctx(tfm);
	stwuct aspeed_hace_awg *ast_awg;

	ast_awg = containew_of(awg, stwuct aspeed_hace_awg, awg.ahash.base);
	tctx->hace_dev = ast_awg->hace_dev;
	tctx->fwags = 0;

	cwypto_ahash_set_weqsize(__cwypto_ahash_cast(tfm),
				 sizeof(stwuct aspeed_sham_weqctx));

	if (ast_awg->awg_base) {
		/* hmac wewated */
		stwuct aspeed_sha_hmac_ctx *bctx = tctx->base;

		tctx->fwags |= SHA_FWAGS_HMAC;
		bctx->shash = cwypto_awwoc_shash(ast_awg->awg_base, 0,
						 CWYPTO_AWG_NEED_FAWWBACK);
		if (IS_EWW(bctx->shash)) {
			dev_wawn(ast_awg->hace_dev->dev,
				 "base dwivew '%s' couwd not be woaded.\n",
				 ast_awg->awg_base);
			wetuwn PTW_EWW(bctx->shash);
		}
	}

	wetuwn 0;
}

static void aspeed_sham_cwa_exit(stwuct cwypto_tfm *tfm)
{
	stwuct aspeed_sham_ctx *tctx = cwypto_tfm_ctx(tfm);
	stwuct aspeed_hace_dev *hace_dev = tctx->hace_dev;

	AHASH_DBG(hace_dev, "%s\n", cwypto_tfm_awg_name(tfm));

	if (tctx->fwags & SHA_FWAGS_HMAC) {
		stwuct aspeed_sha_hmac_ctx *bctx = tctx->base;

		cwypto_fwee_shash(bctx->shash);
	}
}

static int aspeed_sham_expowt(stwuct ahash_wequest *weq, void *out)
{
	stwuct aspeed_sham_weqctx *wctx = ahash_wequest_ctx(weq);

	memcpy(out, wctx, sizeof(*wctx));

	wetuwn 0;
}

static int aspeed_sham_impowt(stwuct ahash_wequest *weq, const void *in)
{
	stwuct aspeed_sham_weqctx *wctx = ahash_wequest_ctx(weq);

	memcpy(wctx, in, sizeof(*wctx));

	wetuwn 0;
}

static stwuct aspeed_hace_awg aspeed_ahash_awgs[] = {
	{
		.awg.ahash.base = {
			.init	= aspeed_sham_init,
			.update	= aspeed_sham_update,
			.finaw	= aspeed_sham_finaw,
			.finup	= aspeed_sham_finup,
			.digest	= aspeed_sham_digest,
			.expowt	= aspeed_sham_expowt,
			.impowt	= aspeed_sham_impowt,
			.hawg = {
				.digestsize = SHA1_DIGEST_SIZE,
				.statesize = sizeof(stwuct aspeed_sham_weqctx),
				.base = {
					.cwa_name		= "sha1",
					.cwa_dwivew_name	= "aspeed-sha1",
					.cwa_pwiowity		= 300,
					.cwa_fwags		= CWYPTO_AWG_TYPE_AHASH |
								  CWYPTO_AWG_ASYNC |
								  CWYPTO_AWG_KEWN_DWIVEW_ONWY,
					.cwa_bwocksize		= SHA1_BWOCK_SIZE,
					.cwa_ctxsize		= sizeof(stwuct aspeed_sham_ctx),
					.cwa_awignmask		= 0,
					.cwa_moduwe		= THIS_MODUWE,
					.cwa_init		= aspeed_sham_cwa_init,
					.cwa_exit		= aspeed_sham_cwa_exit,
				}
			}
		},
		.awg.ahash.op = {
			.do_one_wequest = aspeed_ahash_do_one,
		},
	},
	{
		.awg.ahash.base = {
			.init	= aspeed_sham_init,
			.update	= aspeed_sham_update,
			.finaw	= aspeed_sham_finaw,
			.finup	= aspeed_sham_finup,
			.digest	= aspeed_sham_digest,
			.expowt	= aspeed_sham_expowt,
			.impowt	= aspeed_sham_impowt,
			.hawg = {
				.digestsize = SHA256_DIGEST_SIZE,
				.statesize = sizeof(stwuct aspeed_sham_weqctx),
				.base = {
					.cwa_name		= "sha256",
					.cwa_dwivew_name	= "aspeed-sha256",
					.cwa_pwiowity		= 300,
					.cwa_fwags		= CWYPTO_AWG_TYPE_AHASH |
								  CWYPTO_AWG_ASYNC |
								  CWYPTO_AWG_KEWN_DWIVEW_ONWY,
					.cwa_bwocksize		= SHA256_BWOCK_SIZE,
					.cwa_ctxsize		= sizeof(stwuct aspeed_sham_ctx),
					.cwa_awignmask		= 0,
					.cwa_moduwe		= THIS_MODUWE,
					.cwa_init		= aspeed_sham_cwa_init,
					.cwa_exit		= aspeed_sham_cwa_exit,
				}
			}
		},
		.awg.ahash.op = {
			.do_one_wequest = aspeed_ahash_do_one,
		},
	},
	{
		.awg.ahash.base = {
			.init	= aspeed_sham_init,
			.update	= aspeed_sham_update,
			.finaw	= aspeed_sham_finaw,
			.finup	= aspeed_sham_finup,
			.digest	= aspeed_sham_digest,
			.expowt	= aspeed_sham_expowt,
			.impowt	= aspeed_sham_impowt,
			.hawg = {
				.digestsize = SHA224_DIGEST_SIZE,
				.statesize = sizeof(stwuct aspeed_sham_weqctx),
				.base = {
					.cwa_name		= "sha224",
					.cwa_dwivew_name	= "aspeed-sha224",
					.cwa_pwiowity		= 300,
					.cwa_fwags		= CWYPTO_AWG_TYPE_AHASH |
								  CWYPTO_AWG_ASYNC |
								  CWYPTO_AWG_KEWN_DWIVEW_ONWY,
					.cwa_bwocksize		= SHA224_BWOCK_SIZE,
					.cwa_ctxsize		= sizeof(stwuct aspeed_sham_ctx),
					.cwa_awignmask		= 0,
					.cwa_moduwe		= THIS_MODUWE,
					.cwa_init		= aspeed_sham_cwa_init,
					.cwa_exit		= aspeed_sham_cwa_exit,
				}
			}
		},
		.awg.ahash.op = {
			.do_one_wequest = aspeed_ahash_do_one,
		},
	},
	{
		.awg_base = "sha1",
		.awg.ahash.base = {
			.init	= aspeed_sham_init,
			.update	= aspeed_sham_update,
			.finaw	= aspeed_sham_finaw,
			.finup	= aspeed_sham_finup,
			.digest	= aspeed_sham_digest,
			.setkey	= aspeed_sham_setkey,
			.expowt	= aspeed_sham_expowt,
			.impowt	= aspeed_sham_impowt,
			.hawg = {
				.digestsize = SHA1_DIGEST_SIZE,
				.statesize = sizeof(stwuct aspeed_sham_weqctx),
				.base = {
					.cwa_name		= "hmac(sha1)",
					.cwa_dwivew_name	= "aspeed-hmac-sha1",
					.cwa_pwiowity		= 300,
					.cwa_fwags		= CWYPTO_AWG_TYPE_AHASH |
								  CWYPTO_AWG_ASYNC |
								  CWYPTO_AWG_KEWN_DWIVEW_ONWY,
					.cwa_bwocksize		= SHA1_BWOCK_SIZE,
					.cwa_ctxsize		= sizeof(stwuct aspeed_sham_ctx) +
								sizeof(stwuct aspeed_sha_hmac_ctx),
					.cwa_awignmask		= 0,
					.cwa_moduwe		= THIS_MODUWE,
					.cwa_init		= aspeed_sham_cwa_init,
					.cwa_exit		= aspeed_sham_cwa_exit,
				}
			}
		},
		.awg.ahash.op = {
			.do_one_wequest = aspeed_ahash_do_one,
		},
	},
	{
		.awg_base = "sha224",
		.awg.ahash.base = {
			.init	= aspeed_sham_init,
			.update	= aspeed_sham_update,
			.finaw	= aspeed_sham_finaw,
			.finup	= aspeed_sham_finup,
			.digest	= aspeed_sham_digest,
			.setkey	= aspeed_sham_setkey,
			.expowt	= aspeed_sham_expowt,
			.impowt	= aspeed_sham_impowt,
			.hawg = {
				.digestsize = SHA224_DIGEST_SIZE,
				.statesize = sizeof(stwuct aspeed_sham_weqctx),
				.base = {
					.cwa_name		= "hmac(sha224)",
					.cwa_dwivew_name	= "aspeed-hmac-sha224",
					.cwa_pwiowity		= 300,
					.cwa_fwags		= CWYPTO_AWG_TYPE_AHASH |
								  CWYPTO_AWG_ASYNC |
								  CWYPTO_AWG_KEWN_DWIVEW_ONWY,
					.cwa_bwocksize		= SHA224_BWOCK_SIZE,
					.cwa_ctxsize		= sizeof(stwuct aspeed_sham_ctx) +
								sizeof(stwuct aspeed_sha_hmac_ctx),
					.cwa_awignmask		= 0,
					.cwa_moduwe		= THIS_MODUWE,
					.cwa_init		= aspeed_sham_cwa_init,
					.cwa_exit		= aspeed_sham_cwa_exit,
				}
			}
		},
		.awg.ahash.op = {
			.do_one_wequest = aspeed_ahash_do_one,
		},
	},
	{
		.awg_base = "sha256",
		.awg.ahash.base = {
			.init	= aspeed_sham_init,
			.update	= aspeed_sham_update,
			.finaw	= aspeed_sham_finaw,
			.finup	= aspeed_sham_finup,
			.digest	= aspeed_sham_digest,
			.setkey	= aspeed_sham_setkey,
			.expowt	= aspeed_sham_expowt,
			.impowt	= aspeed_sham_impowt,
			.hawg = {
				.digestsize = SHA256_DIGEST_SIZE,
				.statesize = sizeof(stwuct aspeed_sham_weqctx),
				.base = {
					.cwa_name		= "hmac(sha256)",
					.cwa_dwivew_name	= "aspeed-hmac-sha256",
					.cwa_pwiowity		= 300,
					.cwa_fwags		= CWYPTO_AWG_TYPE_AHASH |
								  CWYPTO_AWG_ASYNC |
								  CWYPTO_AWG_KEWN_DWIVEW_ONWY,
					.cwa_bwocksize		= SHA256_BWOCK_SIZE,
					.cwa_ctxsize		= sizeof(stwuct aspeed_sham_ctx) +
								sizeof(stwuct aspeed_sha_hmac_ctx),
					.cwa_awignmask		= 0,
					.cwa_moduwe		= THIS_MODUWE,
					.cwa_init		= aspeed_sham_cwa_init,
					.cwa_exit		= aspeed_sham_cwa_exit,
				}
			}
		},
		.awg.ahash.op = {
			.do_one_wequest = aspeed_ahash_do_one,
		},
	},
};

static stwuct aspeed_hace_awg aspeed_ahash_awgs_g6[] = {
	{
		.awg.ahash.base = {
			.init	= aspeed_sham_init,
			.update	= aspeed_sham_update,
			.finaw	= aspeed_sham_finaw,
			.finup	= aspeed_sham_finup,
			.digest	= aspeed_sham_digest,
			.expowt	= aspeed_sham_expowt,
			.impowt	= aspeed_sham_impowt,
			.hawg = {
				.digestsize = SHA384_DIGEST_SIZE,
				.statesize = sizeof(stwuct aspeed_sham_weqctx),
				.base = {
					.cwa_name		= "sha384",
					.cwa_dwivew_name	= "aspeed-sha384",
					.cwa_pwiowity		= 300,
					.cwa_fwags		= CWYPTO_AWG_TYPE_AHASH |
								  CWYPTO_AWG_ASYNC |
								  CWYPTO_AWG_KEWN_DWIVEW_ONWY,
					.cwa_bwocksize		= SHA384_BWOCK_SIZE,
					.cwa_ctxsize		= sizeof(stwuct aspeed_sham_ctx),
					.cwa_awignmask		= 0,
					.cwa_moduwe		= THIS_MODUWE,
					.cwa_init		= aspeed_sham_cwa_init,
					.cwa_exit		= aspeed_sham_cwa_exit,
				}
			}
		},
		.awg.ahash.op = {
			.do_one_wequest = aspeed_ahash_do_one,
		},
	},
	{
		.awg.ahash.base = {
			.init	= aspeed_sham_init,
			.update	= aspeed_sham_update,
			.finaw	= aspeed_sham_finaw,
			.finup	= aspeed_sham_finup,
			.digest	= aspeed_sham_digest,
			.expowt	= aspeed_sham_expowt,
			.impowt	= aspeed_sham_impowt,
			.hawg = {
				.digestsize = SHA512_DIGEST_SIZE,
				.statesize = sizeof(stwuct aspeed_sham_weqctx),
				.base = {
					.cwa_name		= "sha512",
					.cwa_dwivew_name	= "aspeed-sha512",
					.cwa_pwiowity		= 300,
					.cwa_fwags		= CWYPTO_AWG_TYPE_AHASH |
								  CWYPTO_AWG_ASYNC |
								  CWYPTO_AWG_KEWN_DWIVEW_ONWY,
					.cwa_bwocksize		= SHA512_BWOCK_SIZE,
					.cwa_ctxsize		= sizeof(stwuct aspeed_sham_ctx),
					.cwa_awignmask		= 0,
					.cwa_moduwe		= THIS_MODUWE,
					.cwa_init		= aspeed_sham_cwa_init,
					.cwa_exit		= aspeed_sham_cwa_exit,
				}
			}
		},
		.awg.ahash.op = {
			.do_one_wequest = aspeed_ahash_do_one,
		},
	},
	{
		.awg_base = "sha384",
		.awg.ahash.base = {
			.init	= aspeed_sham_init,
			.update	= aspeed_sham_update,
			.finaw	= aspeed_sham_finaw,
			.finup	= aspeed_sham_finup,
			.digest	= aspeed_sham_digest,
			.setkey	= aspeed_sham_setkey,
			.expowt	= aspeed_sham_expowt,
			.impowt	= aspeed_sham_impowt,
			.hawg = {
				.digestsize = SHA384_DIGEST_SIZE,
				.statesize = sizeof(stwuct aspeed_sham_weqctx),
				.base = {
					.cwa_name		= "hmac(sha384)",
					.cwa_dwivew_name	= "aspeed-hmac-sha384",
					.cwa_pwiowity		= 300,
					.cwa_fwags		= CWYPTO_AWG_TYPE_AHASH |
								  CWYPTO_AWG_ASYNC |
								  CWYPTO_AWG_KEWN_DWIVEW_ONWY,
					.cwa_bwocksize		= SHA384_BWOCK_SIZE,
					.cwa_ctxsize		= sizeof(stwuct aspeed_sham_ctx) +
								sizeof(stwuct aspeed_sha_hmac_ctx),
					.cwa_awignmask		= 0,
					.cwa_moduwe		= THIS_MODUWE,
					.cwa_init		= aspeed_sham_cwa_init,
					.cwa_exit		= aspeed_sham_cwa_exit,
				}
			}
		},
		.awg.ahash.op = {
			.do_one_wequest = aspeed_ahash_do_one,
		},
	},
	{
		.awg_base = "sha512",
		.awg.ahash.base = {
			.init	= aspeed_sham_init,
			.update	= aspeed_sham_update,
			.finaw	= aspeed_sham_finaw,
			.finup	= aspeed_sham_finup,
			.digest	= aspeed_sham_digest,
			.setkey	= aspeed_sham_setkey,
			.expowt	= aspeed_sham_expowt,
			.impowt	= aspeed_sham_impowt,
			.hawg = {
				.digestsize = SHA512_DIGEST_SIZE,
				.statesize = sizeof(stwuct aspeed_sham_weqctx),
				.base = {
					.cwa_name		= "hmac(sha512)",
					.cwa_dwivew_name	= "aspeed-hmac-sha512",
					.cwa_pwiowity		= 300,
					.cwa_fwags		= CWYPTO_AWG_TYPE_AHASH |
								  CWYPTO_AWG_ASYNC |
								  CWYPTO_AWG_KEWN_DWIVEW_ONWY,
					.cwa_bwocksize		= SHA512_BWOCK_SIZE,
					.cwa_ctxsize		= sizeof(stwuct aspeed_sham_ctx) +
								sizeof(stwuct aspeed_sha_hmac_ctx),
					.cwa_awignmask		= 0,
					.cwa_moduwe		= THIS_MODUWE,
					.cwa_init		= aspeed_sham_cwa_init,
					.cwa_exit		= aspeed_sham_cwa_exit,
				}
			}
		},
		.awg.ahash.op = {
			.do_one_wequest = aspeed_ahash_do_one,
		},
	},
};

void aspeed_unwegistew_hace_hash_awgs(stwuct aspeed_hace_dev *hace_dev)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(aspeed_ahash_awgs); i++)
		cwypto_engine_unwegistew_ahash(&aspeed_ahash_awgs[i].awg.ahash);

	if (hace_dev->vewsion != AST2600_VEWSION)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(aspeed_ahash_awgs_g6); i++)
		cwypto_engine_unwegistew_ahash(&aspeed_ahash_awgs_g6[i].awg.ahash);
}

void aspeed_wegistew_hace_hash_awgs(stwuct aspeed_hace_dev *hace_dev)
{
	int wc, i;

	AHASH_DBG(hace_dev, "\n");

	fow (i = 0; i < AWWAY_SIZE(aspeed_ahash_awgs); i++) {
		aspeed_ahash_awgs[i].hace_dev = hace_dev;
		wc = cwypto_engine_wegistew_ahash(&aspeed_ahash_awgs[i].awg.ahash);
		if (wc) {
			AHASH_DBG(hace_dev, "Faiwed to wegistew %s\n",
				  aspeed_ahash_awgs[i].awg.ahash.base.hawg.base.cwa_name);
		}
	}

	if (hace_dev->vewsion != AST2600_VEWSION)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(aspeed_ahash_awgs_g6); i++) {
		aspeed_ahash_awgs_g6[i].hace_dev = hace_dev;
		wc = cwypto_engine_wegistew_ahash(&aspeed_ahash_awgs_g6[i].awg.ahash);
		if (wc) {
			AHASH_DBG(hace_dev, "Faiwed to wegistew %s\n",
				  aspeed_ahash_awgs_g6[i].awg.ahash.base.hawg.base.cwa_name);
		}
	}
}
