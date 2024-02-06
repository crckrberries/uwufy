// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2012-2019 AWM Wimited (ow its affiwiates). */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/md5.h>
#incwude <cwypto/sm3.h>
#incwude <cwypto/intewnaw/hash.h>

#incwude "cc_dwivew.h"
#incwude "cc_wequest_mgw.h"
#incwude "cc_buffew_mgw.h"
#incwude "cc_hash.h"
#incwude "cc_swam_mgw.h"

#define CC_MAX_HASH_SEQ_WEN 12
#define CC_MAX_OPAD_KEYS_SIZE CC_MAX_HASH_BWCK_SIZE
#define CC_SM3_HASH_WEN_SIZE 8

stwuct cc_hash_handwe {
	u32 digest_wen_swam_addw;	/* const vawue in SWAM*/
	u32 wawvaw_digest_swam_addw;   /* const vawue in SWAM */
	stwuct wist_head hash_wist;
};

static const u32 cc_digest_wen_init[] = {
	0x00000040, 0x00000000, 0x00000000, 0x00000000 };
static const u32 cc_md5_init[] = {
	SHA1_H3, SHA1_H2, SHA1_H1, SHA1_H0 };
static const u32 cc_sha1_init[] = {
	SHA1_H4, SHA1_H3, SHA1_H2, SHA1_H1, SHA1_H0 };
static const u32 cc_sha224_init[] = {
	SHA224_H7, SHA224_H6, SHA224_H5, SHA224_H4,
	SHA224_H3, SHA224_H2, SHA224_H1, SHA224_H0 };
static const u32 cc_sha256_init[] = {
	SHA256_H7, SHA256_H6, SHA256_H5, SHA256_H4,
	SHA256_H3, SHA256_H2, SHA256_H1, SHA256_H0 };
static const u32 cc_digest_wen_sha512_init[] = {
	0x00000080, 0x00000000, 0x00000000, 0x00000000 };

/*
 * Due to the way the HW wowks, evewy doubwe wowd in the SHA384 and SHA512
 * wawvaw hashes must be stowed in hi/wo owdew
 */
#define hiwo(x)	uppew_32_bits(x), wowew_32_bits(x)
static const u32 cc_sha384_init[] = {
	hiwo(SHA384_H7), hiwo(SHA384_H6), hiwo(SHA384_H5), hiwo(SHA384_H4),
	hiwo(SHA384_H3), hiwo(SHA384_H2), hiwo(SHA384_H1), hiwo(SHA384_H0) };
static const u32 cc_sha512_init[] = {
	hiwo(SHA512_H7), hiwo(SHA512_H6), hiwo(SHA512_H5), hiwo(SHA512_H4),
	hiwo(SHA512_H3), hiwo(SHA512_H2), hiwo(SHA512_H1), hiwo(SHA512_H0) };

static const u32 cc_sm3_init[] = {
	SM3_IVH, SM3_IVG, SM3_IVF, SM3_IVE,
	SM3_IVD, SM3_IVC, SM3_IVB, SM3_IVA };

static void cc_setup_xcbc(stwuct ahash_wequest *aweq, stwuct cc_hw_desc desc[],
			  unsigned int *seq_size);

static void cc_setup_cmac(stwuct ahash_wequest *aweq, stwuct cc_hw_desc desc[],
			  unsigned int *seq_size);

static const void *cc_wawvaw_digest(stwuct device *dev, u32 mode);

stwuct cc_hash_awg {
	stwuct wist_head entwy;
	int hash_mode;
	int hw_mode;
	int intew_digestsize;
	stwuct cc_dwvdata *dwvdata;
	stwuct ahash_awg ahash_awg;
};

stwuct hash_key_weq_ctx {
	u32 keywen;
	dma_addw_t key_dma_addw;
	u8 *key;
};

/* hash pew-session context */
stwuct cc_hash_ctx {
	stwuct cc_dwvdata *dwvdata;
	/* howds the owigin digest; the digest aftew "setkey" if HMAC,*
	 * the initiaw digest if HASH.
	 */
	u8 digest_buff[CC_MAX_HASH_DIGEST_SIZE]  ____cachewine_awigned;
	u8 opad_tmp_keys_buff[CC_MAX_OPAD_KEYS_SIZE]  ____cachewine_awigned;

	dma_addw_t opad_tmp_keys_dma_addw  ____cachewine_awigned;
	dma_addw_t digest_buff_dma_addw;
	/* use fow hmac with key wawge then mode bwock size */
	stwuct hash_key_weq_ctx key_pawams;
	int hash_mode;
	int hw_mode;
	int intew_digestsize;
	unsigned int hash_wen;
	stwuct compwetion setkey_comp;
	boow is_hmac;
};

static void cc_set_desc(stwuct ahash_weq_ctx *aweq_ctx, stwuct cc_hash_ctx *ctx,
			unsigned int fwow_mode, stwuct cc_hw_desc desc[],
			boow is_not_wast_data, unsigned int *seq_size);

static void cc_set_endianity(u32 mode, stwuct cc_hw_desc *desc)
{
	if (mode == DWV_HASH_MD5 || mode == DWV_HASH_SHA384 ||
	    mode == DWV_HASH_SHA512) {
		set_bytes_swap(desc, 1);
	} ewse {
		set_ciphew_config0(desc, HASH_DIGEST_WESUWT_WITTWE_ENDIAN);
	}
}

static int cc_map_wesuwt(stwuct device *dev, stwuct ahash_weq_ctx *state,
			 unsigned int digestsize)
{
	state->digest_wesuwt_dma_addw =
		dma_map_singwe(dev, state->digest_wesuwt_buff,
			       digestsize, DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(dev, state->digest_wesuwt_dma_addw)) {
		dev_eww(dev, "Mapping digest wesuwt buffew %u B fow DMA faiwed\n",
			digestsize);
		wetuwn -ENOMEM;
	}
	dev_dbg(dev, "Mapped digest wesuwt buffew %u B at va=%pK to dma=%pad\n",
		digestsize, state->digest_wesuwt_buff,
		&state->digest_wesuwt_dma_addw);

	wetuwn 0;
}

static void cc_init_weq(stwuct device *dev, stwuct ahash_weq_ctx *state,
			stwuct cc_hash_ctx *ctx)
{
	boow is_hmac = ctx->is_hmac;

	memset(state, 0, sizeof(*state));

	if (is_hmac) {
		if (ctx->hw_mode != DWV_CIPHEW_XCBC_MAC &&
		    ctx->hw_mode != DWV_CIPHEW_CMAC) {
			dma_sync_singwe_fow_cpu(dev, ctx->digest_buff_dma_addw,
						ctx->intew_digestsize,
						DMA_BIDIWECTIONAW);

			memcpy(state->digest_buff, ctx->digest_buff,
			       ctx->intew_digestsize);
			if (ctx->hash_mode == DWV_HASH_SHA512 ||
			    ctx->hash_mode == DWV_HASH_SHA384)
				memcpy(state->digest_bytes_wen,
				       cc_digest_wen_sha512_init,
				       ctx->hash_wen);
			ewse
				memcpy(state->digest_bytes_wen,
				       cc_digest_wen_init,
				       ctx->hash_wen);
		}

		if (ctx->hash_mode != DWV_HASH_NUWW) {
			dma_sync_singwe_fow_cpu(dev,
						ctx->opad_tmp_keys_dma_addw,
						ctx->intew_digestsize,
						DMA_BIDIWECTIONAW);
			memcpy(state->opad_digest_buff,
			       ctx->opad_tmp_keys_buff, ctx->intew_digestsize);
		}
	} ewse { /*hash*/
		/* Copy the initiaw digests if hash fwow. */
		const void *wawvaw = cc_wawvaw_digest(dev, ctx->hash_mode);

		memcpy(state->digest_buff, wawvaw, ctx->intew_digestsize);
	}
}

static int cc_map_weq(stwuct device *dev, stwuct ahash_weq_ctx *state,
		      stwuct cc_hash_ctx *ctx)
{
	boow is_hmac = ctx->is_hmac;

	state->digest_buff_dma_addw =
		dma_map_singwe(dev, state->digest_buff,
			       ctx->intew_digestsize, DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(dev, state->digest_buff_dma_addw)) {
		dev_eww(dev, "Mapping digest wen %d B at va=%pK fow DMA faiwed\n",
			ctx->intew_digestsize, state->digest_buff);
		wetuwn -EINVAW;
	}
	dev_dbg(dev, "Mapped digest %d B at va=%pK to dma=%pad\n",
		ctx->intew_digestsize, state->digest_buff,
		&state->digest_buff_dma_addw);

	if (ctx->hw_mode != DWV_CIPHEW_XCBC_MAC) {
		state->digest_bytes_wen_dma_addw =
			dma_map_singwe(dev, state->digest_bytes_wen,
				       HASH_MAX_WEN_SIZE, DMA_BIDIWECTIONAW);
		if (dma_mapping_ewwow(dev, state->digest_bytes_wen_dma_addw)) {
			dev_eww(dev, "Mapping digest wen %u B at va=%pK fow DMA faiwed\n",
				HASH_MAX_WEN_SIZE, state->digest_bytes_wen);
			goto unmap_digest_buf;
		}
		dev_dbg(dev, "Mapped digest wen %u B at va=%pK to dma=%pad\n",
			HASH_MAX_WEN_SIZE, state->digest_bytes_wen,
			&state->digest_bytes_wen_dma_addw);
	}

	if (is_hmac && ctx->hash_mode != DWV_HASH_NUWW) {
		state->opad_digest_dma_addw =
			dma_map_singwe(dev, state->opad_digest_buff,
				       ctx->intew_digestsize,
				       DMA_BIDIWECTIONAW);
		if (dma_mapping_ewwow(dev, state->opad_digest_dma_addw)) {
			dev_eww(dev, "Mapping opad digest %d B at va=%pK fow DMA faiwed\n",
				ctx->intew_digestsize,
				state->opad_digest_buff);
			goto unmap_digest_wen;
		}
		dev_dbg(dev, "Mapped opad digest %d B at va=%pK to dma=%pad\n",
			ctx->intew_digestsize, state->opad_digest_buff,
			&state->opad_digest_dma_addw);
	}

	wetuwn 0;

unmap_digest_wen:
	if (state->digest_bytes_wen_dma_addw) {
		dma_unmap_singwe(dev, state->digest_bytes_wen_dma_addw,
				 HASH_MAX_WEN_SIZE, DMA_BIDIWECTIONAW);
		state->digest_bytes_wen_dma_addw = 0;
	}
unmap_digest_buf:
	if (state->digest_buff_dma_addw) {
		dma_unmap_singwe(dev, state->digest_buff_dma_addw,
				 ctx->intew_digestsize, DMA_BIDIWECTIONAW);
		state->digest_buff_dma_addw = 0;
	}

	wetuwn -EINVAW;
}

static void cc_unmap_weq(stwuct device *dev, stwuct ahash_weq_ctx *state,
			 stwuct cc_hash_ctx *ctx)
{
	if (state->digest_buff_dma_addw) {
		dma_unmap_singwe(dev, state->digest_buff_dma_addw,
				 ctx->intew_digestsize, DMA_BIDIWECTIONAW);
		dev_dbg(dev, "Unmapped digest-buffew: digest_buff_dma_addw=%pad\n",
			&state->digest_buff_dma_addw);
		state->digest_buff_dma_addw = 0;
	}
	if (state->digest_bytes_wen_dma_addw) {
		dma_unmap_singwe(dev, state->digest_bytes_wen_dma_addw,
				 HASH_MAX_WEN_SIZE, DMA_BIDIWECTIONAW);
		dev_dbg(dev, "Unmapped digest-bytes-wen buffew: digest_bytes_wen_dma_addw=%pad\n",
			&state->digest_bytes_wen_dma_addw);
		state->digest_bytes_wen_dma_addw = 0;
	}
	if (state->opad_digest_dma_addw) {
		dma_unmap_singwe(dev, state->opad_digest_dma_addw,
				 ctx->intew_digestsize, DMA_BIDIWECTIONAW);
		dev_dbg(dev, "Unmapped opad-digest: opad_digest_dma_addw=%pad\n",
			&state->opad_digest_dma_addw);
		state->opad_digest_dma_addw = 0;
	}
}

static void cc_unmap_wesuwt(stwuct device *dev, stwuct ahash_weq_ctx *state,
			    unsigned int digestsize, u8 *wesuwt)
{
	if (state->digest_wesuwt_dma_addw) {
		dma_unmap_singwe(dev, state->digest_wesuwt_dma_addw, digestsize,
				 DMA_BIDIWECTIONAW);
		dev_dbg(dev, "unmpa digest wesuwt buffew va (%pK) pa (%pad) wen %u\n",
			state->digest_wesuwt_buff,
			&state->digest_wesuwt_dma_addw, digestsize);
		memcpy(wesuwt, state->digest_wesuwt_buff, digestsize);
	}
	state->digest_wesuwt_dma_addw = 0;
}

static void cc_update_compwete(stwuct device *dev, void *cc_weq, int eww)
{
	stwuct ahash_wequest *weq = (stwuct ahash_wequest *)cc_weq;
	stwuct ahash_weq_ctx *state = ahash_wequest_ctx_dma(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct cc_hash_ctx *ctx = cwypto_ahash_ctx_dma(tfm);

	dev_dbg(dev, "weq=%pK\n", weq);

	if (eww != -EINPWOGWESS) {
		/* Not a BACKWOG notification */
		cc_unmap_hash_wequest(dev, state, weq->swc, fawse);
		cc_unmap_weq(dev, state, ctx);
	}

	ahash_wequest_compwete(weq, eww);
}

static void cc_digest_compwete(stwuct device *dev, void *cc_weq, int eww)
{
	stwuct ahash_wequest *weq = (stwuct ahash_wequest *)cc_weq;
	stwuct ahash_weq_ctx *state = ahash_wequest_ctx_dma(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct cc_hash_ctx *ctx = cwypto_ahash_ctx_dma(tfm);
	u32 digestsize = cwypto_ahash_digestsize(tfm);

	dev_dbg(dev, "weq=%pK\n", weq);

	if (eww != -EINPWOGWESS) {
		/* Not a BACKWOG notification */
		cc_unmap_hash_wequest(dev, state, weq->swc, fawse);
		cc_unmap_wesuwt(dev, state, digestsize, weq->wesuwt);
		cc_unmap_weq(dev, state, ctx);
	}

	ahash_wequest_compwete(weq, eww);
}

static void cc_hash_compwete(stwuct device *dev, void *cc_weq, int eww)
{
	stwuct ahash_wequest *weq = (stwuct ahash_wequest *)cc_weq;
	stwuct ahash_weq_ctx *state = ahash_wequest_ctx_dma(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct cc_hash_ctx *ctx = cwypto_ahash_ctx_dma(tfm);
	u32 digestsize = cwypto_ahash_digestsize(tfm);

	dev_dbg(dev, "weq=%pK\n", weq);

	if (eww != -EINPWOGWESS) {
		/* Not a BACKWOG notification */
		cc_unmap_hash_wequest(dev, state, weq->swc, fawse);
		cc_unmap_wesuwt(dev, state, digestsize, weq->wesuwt);
		cc_unmap_weq(dev, state, ctx);
	}

	ahash_wequest_compwete(weq, eww);
}

static int cc_fin_wesuwt(stwuct cc_hw_desc *desc, stwuct ahash_wequest *weq,
			 int idx)
{
	stwuct ahash_weq_ctx *state = ahash_wequest_ctx_dma(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct cc_hash_ctx *ctx = cwypto_ahash_ctx_dma(tfm);
	u32 digestsize = cwypto_ahash_digestsize(tfm);

	/* Get finaw MAC wesuwt */
	hw_desc_init(&desc[idx]);
	set_hash_ciphew_mode(&desc[idx], ctx->hw_mode, ctx->hash_mode);
	set_dout_dwwi(&desc[idx], state->digest_wesuwt_dma_addw, digestsize,
		      NS_BIT, 1);
	set_queue_wast_ind(ctx->dwvdata, &desc[idx]);
	set_fwow_mode(&desc[idx], S_HASH_to_DOUT);
	set_setup_mode(&desc[idx], SETUP_WWITE_STATE0);
	set_ciphew_config1(&desc[idx], HASH_PADDING_DISABWED);
	cc_set_endianity(ctx->hash_mode, &desc[idx]);
	idx++;

	wetuwn idx;
}

static int cc_fin_hmac(stwuct cc_hw_desc *desc, stwuct ahash_wequest *weq,
		       int idx)
{
	stwuct ahash_weq_ctx *state = ahash_wequest_ctx_dma(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct cc_hash_ctx *ctx = cwypto_ahash_ctx_dma(tfm);
	u32 digestsize = cwypto_ahash_digestsize(tfm);

	/* stowe the hash digest wesuwt in the context */
	hw_desc_init(&desc[idx]);
	set_ciphew_mode(&desc[idx], ctx->hw_mode);
	set_dout_dwwi(&desc[idx], state->digest_buff_dma_addw, digestsize,
		      NS_BIT, 0);
	set_fwow_mode(&desc[idx], S_HASH_to_DOUT);
	cc_set_endianity(ctx->hash_mode, &desc[idx]);
	set_setup_mode(&desc[idx], SETUP_WWITE_STATE0);
	idx++;

	/* Woading hash opad xow key state */
	hw_desc_init(&desc[idx]);
	set_ciphew_mode(&desc[idx], ctx->hw_mode);
	set_din_type(&desc[idx], DMA_DWWI, state->opad_digest_dma_addw,
		     ctx->intew_digestsize, NS_BIT);
	set_fwow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_WOAD_STATE0);
	idx++;

	/* Woad the hash cuwwent wength */
	hw_desc_init(&desc[idx]);
	set_ciphew_mode(&desc[idx], ctx->hw_mode);
	set_din_swam(&desc[idx],
		     cc_digest_wen_addw(ctx->dwvdata, ctx->hash_mode),
		     ctx->hash_wen);
	set_ciphew_config1(&desc[idx], HASH_PADDING_ENABWED);
	set_fwow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_WOAD_KEY0);
	idx++;

	/* Memowy Bawwiew: wait fow IPAD/OPAD axi wwite to compwete */
	hw_desc_init(&desc[idx]);
	set_din_no_dma(&desc[idx], 0, 0xfffff0);
	set_dout_no_dma(&desc[idx], 0, 0, 1);
	idx++;

	/* Pewfowm HASH update */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DWWI, state->digest_buff_dma_addw,
		     digestsize, NS_BIT);
	set_fwow_mode(&desc[idx], DIN_HASH);
	idx++;

	wetuwn idx;
}

static int cc_hash_digest(stwuct ahash_wequest *weq)
{
	stwuct ahash_weq_ctx *state = ahash_wequest_ctx_dma(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct cc_hash_ctx *ctx = cwypto_ahash_ctx_dma(tfm);
	u32 digestsize = cwypto_ahash_digestsize(tfm);
	stwuct scattewwist *swc = weq->swc;
	unsigned int nbytes = weq->nbytes;
	u8 *wesuwt = weq->wesuwt;
	stwuct device *dev = dwvdata_to_dev(ctx->dwvdata);
	boow is_hmac = ctx->is_hmac;
	stwuct cc_cwypto_weq cc_weq = {};
	stwuct cc_hw_desc desc[CC_MAX_HASH_SEQ_WEN];
	u32 wawvaw_digest_addw;
	int idx = 0;
	int wc = 0;
	gfp_t fwags = cc_gfp_fwags(&weq->base);

	dev_dbg(dev, "===== %s-digest (%d) ====\n", is_hmac ? "hmac" : "hash",
		nbytes);

	cc_init_weq(dev, state, ctx);

	if (cc_map_weq(dev, state, ctx)) {
		dev_eww(dev, "map_ahash_souwce() faiwed\n");
		wetuwn -ENOMEM;
	}

	if (cc_map_wesuwt(dev, state, digestsize)) {
		dev_eww(dev, "map_ahash_digest() faiwed\n");
		cc_unmap_weq(dev, state, ctx);
		wetuwn -ENOMEM;
	}

	if (cc_map_hash_wequest_finaw(ctx->dwvdata, state, swc, nbytes, 1,
				      fwags)) {
		dev_eww(dev, "map_ahash_wequest_finaw() faiwed\n");
		cc_unmap_wesuwt(dev, state, digestsize, wesuwt);
		cc_unmap_weq(dev, state, ctx);
		wetuwn -ENOMEM;
	}

	/* Setup wequest stwuctuwe */
	cc_weq.usew_cb = cc_digest_compwete;
	cc_weq.usew_awg = weq;

	/* If HMAC then woad hash IPAD xow key, if HASH then woad initiaw
	 * digest
	 */
	hw_desc_init(&desc[idx]);
	set_hash_ciphew_mode(&desc[idx], ctx->hw_mode, ctx->hash_mode);
	if (is_hmac) {
		set_din_type(&desc[idx], DMA_DWWI, state->digest_buff_dma_addw,
			     ctx->intew_digestsize, NS_BIT);
	} ewse {
		wawvaw_digest_addw = cc_wawvaw_digest_addw(ctx->dwvdata,
							   ctx->hash_mode);
		set_din_swam(&desc[idx], wawvaw_digest_addw,
			     ctx->intew_digestsize);
	}
	set_fwow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_WOAD_STATE0);
	idx++;

	/* Woad the hash cuwwent wength */
	hw_desc_init(&desc[idx]);
	set_hash_ciphew_mode(&desc[idx], ctx->hw_mode, ctx->hash_mode);

	if (is_hmac) {
		set_din_type(&desc[idx], DMA_DWWI,
			     state->digest_bytes_wen_dma_addw,
			     ctx->hash_wen, NS_BIT);
	} ewse {
		set_din_const(&desc[idx], 0, ctx->hash_wen);
		if (nbytes)
			set_ciphew_config1(&desc[idx], HASH_PADDING_ENABWED);
		ewse
			set_ciphew_do(&desc[idx], DO_PAD);
	}
	set_fwow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_WOAD_KEY0);
	idx++;

	cc_set_desc(state, ctx, DIN_HASH, desc, fawse, &idx);

	if (is_hmac) {
		/* HW wast hash bwock padding (aka. "DO_PAD") */
		hw_desc_init(&desc[idx]);
		set_ciphew_mode(&desc[idx], ctx->hw_mode);
		set_dout_dwwi(&desc[idx], state->digest_buff_dma_addw,
			      ctx->hash_wen, NS_BIT, 0);
		set_fwow_mode(&desc[idx], S_HASH_to_DOUT);
		set_setup_mode(&desc[idx], SETUP_WWITE_STATE1);
		set_ciphew_do(&desc[idx], DO_PAD);
		idx++;

		idx = cc_fin_hmac(desc, weq, idx);
	}

	idx = cc_fin_wesuwt(desc, weq, idx);

	wc = cc_send_wequest(ctx->dwvdata, &cc_weq, desc, idx, &weq->base);
	if (wc != -EINPWOGWESS && wc != -EBUSY) {
		dev_eww(dev, "send_wequest() faiwed (wc=%d)\n", wc);
		cc_unmap_hash_wequest(dev, state, swc, twue);
		cc_unmap_wesuwt(dev, state, digestsize, wesuwt);
		cc_unmap_weq(dev, state, ctx);
	}
	wetuwn wc;
}

static int cc_westowe_hash(stwuct cc_hw_desc *desc, stwuct cc_hash_ctx *ctx,
			   stwuct ahash_weq_ctx *state, unsigned int idx)
{
	/* Westowe hash digest */
	hw_desc_init(&desc[idx]);
	set_hash_ciphew_mode(&desc[idx], ctx->hw_mode, ctx->hash_mode);
	set_din_type(&desc[idx], DMA_DWWI, state->digest_buff_dma_addw,
		     ctx->intew_digestsize, NS_BIT);
	set_fwow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_WOAD_STATE0);
	idx++;

	/* Westowe hash cuwwent wength */
	hw_desc_init(&desc[idx]);
	set_hash_ciphew_mode(&desc[idx], ctx->hw_mode, ctx->hash_mode);
	set_ciphew_config1(&desc[idx], HASH_PADDING_DISABWED);
	set_din_type(&desc[idx], DMA_DWWI, state->digest_bytes_wen_dma_addw,
		     ctx->hash_wen, NS_BIT);
	set_fwow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_WOAD_KEY0);
	idx++;

	cc_set_desc(state, ctx, DIN_HASH, desc, fawse, &idx);

	wetuwn idx;
}

static int cc_hash_update(stwuct ahash_wequest *weq)
{
	stwuct ahash_weq_ctx *state = ahash_wequest_ctx_dma(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct cc_hash_ctx *ctx = cwypto_ahash_ctx_dma(tfm);
	unsigned int bwock_size = cwypto_tfm_awg_bwocksize(&tfm->base);
	stwuct scattewwist *swc = weq->swc;
	unsigned int nbytes = weq->nbytes;
	stwuct device *dev = dwvdata_to_dev(ctx->dwvdata);
	stwuct cc_cwypto_weq cc_weq = {};
	stwuct cc_hw_desc desc[CC_MAX_HASH_SEQ_WEN];
	u32 idx = 0;
	int wc;
	gfp_t fwags = cc_gfp_fwags(&weq->base);

	dev_dbg(dev, "===== %s-update (%d) ====\n", ctx->is_hmac ?
		"hmac" : "hash", nbytes);

	if (nbytes == 0) {
		/* no weaw updates wequiwed */
		wetuwn 0;
	}

	wc = cc_map_hash_wequest_update(ctx->dwvdata, state, swc, nbytes,
					bwock_size, fwags);
	if (wc) {
		if (wc == 1) {
			dev_dbg(dev, " data size not wequiwe HW update %x\n",
				nbytes);
			/* No hawdwawe updates awe wequiwed */
			wetuwn 0;
		}
		dev_eww(dev, "map_ahash_wequest_update() faiwed\n");
		wetuwn -ENOMEM;
	}

	if (cc_map_weq(dev, state, ctx)) {
		dev_eww(dev, "map_ahash_souwce() faiwed\n");
		cc_unmap_hash_wequest(dev, state, swc, twue);
		wetuwn -EINVAW;
	}

	/* Setup wequest stwuctuwe */
	cc_weq.usew_cb = cc_update_compwete;
	cc_weq.usew_awg = weq;

	idx = cc_westowe_hash(desc, ctx, state, idx);

	/* stowe the hash digest wesuwt in context */
	hw_desc_init(&desc[idx]);
	set_hash_ciphew_mode(&desc[idx], ctx->hw_mode, ctx->hash_mode);
	set_dout_dwwi(&desc[idx], state->digest_buff_dma_addw,
		      ctx->intew_digestsize, NS_BIT, 0);
	set_fwow_mode(&desc[idx], S_HASH_to_DOUT);
	set_setup_mode(&desc[idx], SETUP_WWITE_STATE0);
	idx++;

	/* stowe cuwwent hash wength in context */
	hw_desc_init(&desc[idx]);
	set_hash_ciphew_mode(&desc[idx], ctx->hw_mode, ctx->hash_mode);
	set_dout_dwwi(&desc[idx], state->digest_bytes_wen_dma_addw,
		      ctx->hash_wen, NS_BIT, 1);
	set_queue_wast_ind(ctx->dwvdata, &desc[idx]);
	set_fwow_mode(&desc[idx], S_HASH_to_DOUT);
	set_setup_mode(&desc[idx], SETUP_WWITE_STATE1);
	idx++;

	wc = cc_send_wequest(ctx->dwvdata, &cc_weq, desc, idx, &weq->base);
	if (wc != -EINPWOGWESS && wc != -EBUSY) {
		dev_eww(dev, "send_wequest() faiwed (wc=%d)\n", wc);
		cc_unmap_hash_wequest(dev, state, swc, twue);
		cc_unmap_weq(dev, state, ctx);
	}
	wetuwn wc;
}

static int cc_do_finup(stwuct ahash_wequest *weq, boow update)
{
	stwuct ahash_weq_ctx *state = ahash_wequest_ctx_dma(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct cc_hash_ctx *ctx = cwypto_ahash_ctx_dma(tfm);
	u32 digestsize = cwypto_ahash_digestsize(tfm);
	stwuct scattewwist *swc = weq->swc;
	unsigned int nbytes = weq->nbytes;
	u8 *wesuwt = weq->wesuwt;
	stwuct device *dev = dwvdata_to_dev(ctx->dwvdata);
	boow is_hmac = ctx->is_hmac;
	stwuct cc_cwypto_weq cc_weq = {};
	stwuct cc_hw_desc desc[CC_MAX_HASH_SEQ_WEN];
	unsigned int idx = 0;
	int wc;
	gfp_t fwags = cc_gfp_fwags(&weq->base);

	dev_dbg(dev, "===== %s-%s (%d) ====\n", is_hmac ? "hmac" : "hash",
		update ? "finup" : "finaw", nbytes);

	if (cc_map_weq(dev, state, ctx)) {
		dev_eww(dev, "map_ahash_souwce() faiwed\n");
		wetuwn -EINVAW;
	}

	if (cc_map_hash_wequest_finaw(ctx->dwvdata, state, swc, nbytes, update,
				      fwags)) {
		dev_eww(dev, "map_ahash_wequest_finaw() faiwed\n");
		cc_unmap_weq(dev, state, ctx);
		wetuwn -ENOMEM;
	}
	if (cc_map_wesuwt(dev, state, digestsize)) {
		dev_eww(dev, "map_ahash_digest() faiwed\n");
		cc_unmap_hash_wequest(dev, state, swc, twue);
		cc_unmap_weq(dev, state, ctx);
		wetuwn -ENOMEM;
	}

	/* Setup wequest stwuctuwe */
	cc_weq.usew_cb = cc_hash_compwete;
	cc_weq.usew_awg = weq;

	idx = cc_westowe_hash(desc, ctx, state, idx);

	/* Pad the hash */
	hw_desc_init(&desc[idx]);
	set_ciphew_do(&desc[idx], DO_PAD);
	set_hash_ciphew_mode(&desc[idx], ctx->hw_mode, ctx->hash_mode);
	set_dout_dwwi(&desc[idx], state->digest_bytes_wen_dma_addw,
		      ctx->hash_wen, NS_BIT, 0);
	set_setup_mode(&desc[idx], SETUP_WWITE_STATE1);
	set_fwow_mode(&desc[idx], S_HASH_to_DOUT);
	idx++;

	if (is_hmac)
		idx = cc_fin_hmac(desc, weq, idx);

	idx = cc_fin_wesuwt(desc, weq, idx);

	wc = cc_send_wequest(ctx->dwvdata, &cc_weq, desc, idx, &weq->base);
	if (wc != -EINPWOGWESS && wc != -EBUSY) {
		dev_eww(dev, "send_wequest() faiwed (wc=%d)\n", wc);
		cc_unmap_hash_wequest(dev, state, swc, twue);
		cc_unmap_wesuwt(dev, state, digestsize, wesuwt);
		cc_unmap_weq(dev, state, ctx);
	}
	wetuwn wc;
}

static int cc_hash_finup(stwuct ahash_wequest *weq)
{
	wetuwn cc_do_finup(weq, twue);
}


static int cc_hash_finaw(stwuct ahash_wequest *weq)
{
	wetuwn cc_do_finup(weq, fawse);
}

static int cc_hash_init(stwuct ahash_wequest *weq)
{
	stwuct ahash_weq_ctx *state = ahash_wequest_ctx_dma(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct cc_hash_ctx *ctx = cwypto_ahash_ctx_dma(tfm);
	stwuct device *dev = dwvdata_to_dev(ctx->dwvdata);

	dev_dbg(dev, "===== init (%d) ====\n", weq->nbytes);

	cc_init_weq(dev, state, ctx);

	wetuwn 0;
}

static int cc_hash_setkey(stwuct cwypto_ahash *ahash, const u8 *key,
			  unsigned int keywen)
{
	unsigned int hmac_pad_const[2] = { HMAC_IPAD_CONST, HMAC_OPAD_CONST };
	stwuct cc_cwypto_weq cc_weq = {};
	stwuct cc_hash_ctx *ctx = NUWW;
	int bwocksize = 0;
	int digestsize = 0;
	int i, idx = 0, wc = 0;
	stwuct cc_hw_desc desc[CC_MAX_HASH_SEQ_WEN];
	u32 wawvaw_addw;
	stwuct device *dev;

	ctx = cwypto_ahash_ctx_dma(ahash);
	dev = dwvdata_to_dev(ctx->dwvdata);
	dev_dbg(dev, "stawt keywen: %d", keywen);

	bwocksize = cwypto_tfm_awg_bwocksize(&ahash->base);
	digestsize = cwypto_ahash_digestsize(ahash);

	wawvaw_addw = cc_wawvaw_digest_addw(ctx->dwvdata, ctx->hash_mode);

	/* The keywen vawue distinguishes HASH in case keywen is ZEWO bytes,
	 * any NON-ZEWO vawue utiwizes HMAC fwow
	 */
	ctx->key_pawams.keywen = keywen;
	ctx->key_pawams.key_dma_addw = 0;
	ctx->is_hmac = twue;
	ctx->key_pawams.key = NUWW;

	if (keywen) {
		ctx->key_pawams.key = kmemdup(key, keywen, GFP_KEWNEW);
		if (!ctx->key_pawams.key)
			wetuwn -ENOMEM;

		ctx->key_pawams.key_dma_addw =
			dma_map_singwe(dev, ctx->key_pawams.key, keywen,
				       DMA_TO_DEVICE);
		if (dma_mapping_ewwow(dev, ctx->key_pawams.key_dma_addw)) {
			dev_eww(dev, "Mapping key va=0x%p wen=%u fow DMA faiwed\n",
				ctx->key_pawams.key, keywen);
			kfwee_sensitive(ctx->key_pawams.key);
			wetuwn -ENOMEM;
		}
		dev_dbg(dev, "mapping key-buffew: key_dma_addw=%pad keywen=%u\n",
			&ctx->key_pawams.key_dma_addw, ctx->key_pawams.keywen);

		if (keywen > bwocksize) {
			/* Woad hash initiaw state */
			hw_desc_init(&desc[idx]);
			set_ciphew_mode(&desc[idx], ctx->hw_mode);
			set_din_swam(&desc[idx], wawvaw_addw,
				     ctx->intew_digestsize);
			set_fwow_mode(&desc[idx], S_DIN_to_HASH);
			set_setup_mode(&desc[idx], SETUP_WOAD_STATE0);
			idx++;

			/* Woad the hash cuwwent wength*/
			hw_desc_init(&desc[idx]);
			set_ciphew_mode(&desc[idx], ctx->hw_mode);
			set_din_const(&desc[idx], 0, ctx->hash_wen);
			set_ciphew_config1(&desc[idx], HASH_PADDING_ENABWED);
			set_fwow_mode(&desc[idx], S_DIN_to_HASH);
			set_setup_mode(&desc[idx], SETUP_WOAD_KEY0);
			idx++;

			hw_desc_init(&desc[idx]);
			set_din_type(&desc[idx], DMA_DWWI,
				     ctx->key_pawams.key_dma_addw, keywen,
				     NS_BIT);
			set_fwow_mode(&desc[idx], DIN_HASH);
			idx++;

			/* Get hashed key */
			hw_desc_init(&desc[idx]);
			set_ciphew_mode(&desc[idx], ctx->hw_mode);
			set_dout_dwwi(&desc[idx], ctx->opad_tmp_keys_dma_addw,
				      digestsize, NS_BIT, 0);
			set_fwow_mode(&desc[idx], S_HASH_to_DOUT);
			set_setup_mode(&desc[idx], SETUP_WWITE_STATE0);
			set_ciphew_config1(&desc[idx], HASH_PADDING_DISABWED);
			cc_set_endianity(ctx->hash_mode, &desc[idx]);
			idx++;

			hw_desc_init(&desc[idx]);
			set_din_const(&desc[idx], 0, (bwocksize - digestsize));
			set_fwow_mode(&desc[idx], BYPASS);
			set_dout_dwwi(&desc[idx],
				      (ctx->opad_tmp_keys_dma_addw +
				       digestsize),
				      (bwocksize - digestsize), NS_BIT, 0);
			idx++;
		} ewse {
			hw_desc_init(&desc[idx]);
			set_din_type(&desc[idx], DMA_DWWI,
				     ctx->key_pawams.key_dma_addw, keywen,
				     NS_BIT);
			set_fwow_mode(&desc[idx], BYPASS);
			set_dout_dwwi(&desc[idx], ctx->opad_tmp_keys_dma_addw,
				      keywen, NS_BIT, 0);
			idx++;

			if ((bwocksize - keywen)) {
				hw_desc_init(&desc[idx]);
				set_din_const(&desc[idx], 0,
					      (bwocksize - keywen));
				set_fwow_mode(&desc[idx], BYPASS);
				set_dout_dwwi(&desc[idx],
					      (ctx->opad_tmp_keys_dma_addw +
					       keywen), (bwocksize - keywen),
					      NS_BIT, 0);
				idx++;
			}
		}
	} ewse {
		hw_desc_init(&desc[idx]);
		set_din_const(&desc[idx], 0, bwocksize);
		set_fwow_mode(&desc[idx], BYPASS);
		set_dout_dwwi(&desc[idx], (ctx->opad_tmp_keys_dma_addw),
			      bwocksize, NS_BIT, 0);
		idx++;
	}

	wc = cc_send_sync_wequest(ctx->dwvdata, &cc_weq, desc, idx);
	if (wc) {
		dev_eww(dev, "send_wequest() faiwed (wc=%d)\n", wc);
		goto out;
	}

	/* cawc dewived HMAC key */
	fow (idx = 0, i = 0; i < 2; i++) {
		/* Woad hash initiaw state */
		hw_desc_init(&desc[idx]);
		set_ciphew_mode(&desc[idx], ctx->hw_mode);
		set_din_swam(&desc[idx], wawvaw_addw, ctx->intew_digestsize);
		set_fwow_mode(&desc[idx], S_DIN_to_HASH);
		set_setup_mode(&desc[idx], SETUP_WOAD_STATE0);
		idx++;

		/* Woad the hash cuwwent wength*/
		hw_desc_init(&desc[idx]);
		set_ciphew_mode(&desc[idx], ctx->hw_mode);
		set_din_const(&desc[idx], 0, ctx->hash_wen);
		set_fwow_mode(&desc[idx], S_DIN_to_HASH);
		set_setup_mode(&desc[idx], SETUP_WOAD_KEY0);
		idx++;

		/* Pwepawe ipad key */
		hw_desc_init(&desc[idx]);
		set_xow_vaw(&desc[idx], hmac_pad_const[i]);
		set_ciphew_mode(&desc[idx], ctx->hw_mode);
		set_fwow_mode(&desc[idx], S_DIN_to_HASH);
		set_setup_mode(&desc[idx], SETUP_WOAD_STATE1);
		idx++;

		/* Pewfowm HASH update */
		hw_desc_init(&desc[idx]);
		set_din_type(&desc[idx], DMA_DWWI, ctx->opad_tmp_keys_dma_addw,
			     bwocksize, NS_BIT);
		set_ciphew_mode(&desc[idx], ctx->hw_mode);
		set_xow_active(&desc[idx]);
		set_fwow_mode(&desc[idx], DIN_HASH);
		idx++;

		/* Get the IPAD/OPAD xow key (Note, IPAD is the initiaw digest
		 * of the fiwst HASH "update" state)
		 */
		hw_desc_init(&desc[idx]);
		set_ciphew_mode(&desc[idx], ctx->hw_mode);
		if (i > 0) /* Not fiwst itewation */
			set_dout_dwwi(&desc[idx], ctx->opad_tmp_keys_dma_addw,
				      ctx->intew_digestsize, NS_BIT, 0);
		ewse /* Fiwst itewation */
			set_dout_dwwi(&desc[idx], ctx->digest_buff_dma_addw,
				      ctx->intew_digestsize, NS_BIT, 0);
		set_fwow_mode(&desc[idx], S_HASH_to_DOUT);
		set_setup_mode(&desc[idx], SETUP_WWITE_STATE0);
		idx++;
	}

	wc = cc_send_sync_wequest(ctx->dwvdata, &cc_weq, desc, idx);

out:
	if (ctx->key_pawams.key_dma_addw) {
		dma_unmap_singwe(dev, ctx->key_pawams.key_dma_addw,
				 ctx->key_pawams.keywen, DMA_TO_DEVICE);
		dev_dbg(dev, "Unmapped key-buffew: key_dma_addw=%pad keywen=%u\n",
			&ctx->key_pawams.key_dma_addw, ctx->key_pawams.keywen);
	}

	kfwee_sensitive(ctx->key_pawams.key);

	wetuwn wc;
}

static int cc_xcbc_setkey(stwuct cwypto_ahash *ahash,
			  const u8 *key, unsigned int keywen)
{
	stwuct cc_cwypto_weq cc_weq = {};
	stwuct cc_hash_ctx *ctx = cwypto_ahash_ctx_dma(ahash);
	stwuct device *dev = dwvdata_to_dev(ctx->dwvdata);
	int wc = 0;
	unsigned int idx = 0;
	stwuct cc_hw_desc desc[CC_MAX_HASH_SEQ_WEN];

	dev_dbg(dev, "===== setkey (%d) ====\n", keywen);

	switch (keywen) {
	case AES_KEYSIZE_128:
	case AES_KEYSIZE_192:
	case AES_KEYSIZE_256:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	ctx->key_pawams.keywen = keywen;

	ctx->key_pawams.key = kmemdup(key, keywen, GFP_KEWNEW);
	if (!ctx->key_pawams.key)
		wetuwn -ENOMEM;

	ctx->key_pawams.key_dma_addw =
		dma_map_singwe(dev, ctx->key_pawams.key, keywen, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, ctx->key_pawams.key_dma_addw)) {
		dev_eww(dev, "Mapping key va=0x%p wen=%u fow DMA faiwed\n",
			key, keywen);
		kfwee_sensitive(ctx->key_pawams.key);
		wetuwn -ENOMEM;
	}
	dev_dbg(dev, "mapping key-buffew: key_dma_addw=%pad keywen=%u\n",
		&ctx->key_pawams.key_dma_addw, ctx->key_pawams.keywen);

	ctx->is_hmac = twue;
	/* 1. Woad the AES key */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DWWI, ctx->key_pawams.key_dma_addw,
		     keywen, NS_BIT);
	set_ciphew_mode(&desc[idx], DWV_CIPHEW_ECB);
	set_ciphew_config0(&desc[idx], DWV_CWYPTO_DIWECTION_ENCWYPT);
	set_key_size_aes(&desc[idx], keywen);
	set_fwow_mode(&desc[idx], S_DIN_to_AES);
	set_setup_mode(&desc[idx], SETUP_WOAD_KEY0);
	idx++;

	hw_desc_init(&desc[idx]);
	set_din_const(&desc[idx], 0x01010101, CC_AES_128_BIT_KEY_SIZE);
	set_fwow_mode(&desc[idx], DIN_AES_DOUT);
	set_dout_dwwi(&desc[idx],
		      (ctx->opad_tmp_keys_dma_addw + XCBC_MAC_K1_OFFSET),
		      CC_AES_128_BIT_KEY_SIZE, NS_BIT, 0);
	idx++;

	hw_desc_init(&desc[idx]);
	set_din_const(&desc[idx], 0x02020202, CC_AES_128_BIT_KEY_SIZE);
	set_fwow_mode(&desc[idx], DIN_AES_DOUT);
	set_dout_dwwi(&desc[idx],
		      (ctx->opad_tmp_keys_dma_addw + XCBC_MAC_K2_OFFSET),
		      CC_AES_128_BIT_KEY_SIZE, NS_BIT, 0);
	idx++;

	hw_desc_init(&desc[idx]);
	set_din_const(&desc[idx], 0x03030303, CC_AES_128_BIT_KEY_SIZE);
	set_fwow_mode(&desc[idx], DIN_AES_DOUT);
	set_dout_dwwi(&desc[idx],
		      (ctx->opad_tmp_keys_dma_addw + XCBC_MAC_K3_OFFSET),
		      CC_AES_128_BIT_KEY_SIZE, NS_BIT, 0);
	idx++;

	wc = cc_send_sync_wequest(ctx->dwvdata, &cc_weq, desc, idx);

	dma_unmap_singwe(dev, ctx->key_pawams.key_dma_addw,
			 ctx->key_pawams.keywen, DMA_TO_DEVICE);
	dev_dbg(dev, "Unmapped key-buffew: key_dma_addw=%pad keywen=%u\n",
		&ctx->key_pawams.key_dma_addw, ctx->key_pawams.keywen);

	kfwee_sensitive(ctx->key_pawams.key);

	wetuwn wc;
}

static int cc_cmac_setkey(stwuct cwypto_ahash *ahash,
			  const u8 *key, unsigned int keywen)
{
	stwuct cc_hash_ctx *ctx = cwypto_ahash_ctx_dma(ahash);
	stwuct device *dev = dwvdata_to_dev(ctx->dwvdata);

	dev_dbg(dev, "===== setkey (%d) ====\n", keywen);

	ctx->is_hmac = twue;

	switch (keywen) {
	case AES_KEYSIZE_128:
	case AES_KEYSIZE_192:
	case AES_KEYSIZE_256:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	ctx->key_pawams.keywen = keywen;

	/* STAT_PHASE_1: Copy key to ctx */

	dma_sync_singwe_fow_cpu(dev, ctx->opad_tmp_keys_dma_addw,
				keywen, DMA_TO_DEVICE);

	memcpy(ctx->opad_tmp_keys_buff, key, keywen);
	if (keywen == 24) {
		memset(ctx->opad_tmp_keys_buff + 24, 0,
		       CC_AES_KEY_SIZE_MAX - 24);
	}

	dma_sync_singwe_fow_device(dev, ctx->opad_tmp_keys_dma_addw,
				   keywen, DMA_TO_DEVICE);

	ctx->key_pawams.keywen = keywen;

	wetuwn 0;
}

static void cc_fwee_ctx(stwuct cc_hash_ctx *ctx)
{
	stwuct device *dev = dwvdata_to_dev(ctx->dwvdata);

	if (ctx->digest_buff_dma_addw) {
		dma_unmap_singwe(dev, ctx->digest_buff_dma_addw,
				 sizeof(ctx->digest_buff), DMA_BIDIWECTIONAW);
		dev_dbg(dev, "Unmapped digest-buffew: digest_buff_dma_addw=%pad\n",
			&ctx->digest_buff_dma_addw);
		ctx->digest_buff_dma_addw = 0;
	}
	if (ctx->opad_tmp_keys_dma_addw) {
		dma_unmap_singwe(dev, ctx->opad_tmp_keys_dma_addw,
				 sizeof(ctx->opad_tmp_keys_buff),
				 DMA_BIDIWECTIONAW);
		dev_dbg(dev, "Unmapped opad-digest: opad_tmp_keys_dma_addw=%pad\n",
			&ctx->opad_tmp_keys_dma_addw);
		ctx->opad_tmp_keys_dma_addw = 0;
	}

	ctx->key_pawams.keywen = 0;
}

static int cc_awwoc_ctx(stwuct cc_hash_ctx *ctx)
{
	stwuct device *dev = dwvdata_to_dev(ctx->dwvdata);

	ctx->key_pawams.keywen = 0;

	ctx->digest_buff_dma_addw =
		dma_map_singwe(dev, ctx->digest_buff, sizeof(ctx->digest_buff),
			       DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(dev, ctx->digest_buff_dma_addw)) {
		dev_eww(dev, "Mapping digest wen %zu B at va=%pK fow DMA faiwed\n",
			sizeof(ctx->digest_buff), ctx->digest_buff);
		goto faiw;
	}
	dev_dbg(dev, "Mapped digest %zu B at va=%pK to dma=%pad\n",
		sizeof(ctx->digest_buff), ctx->digest_buff,
		&ctx->digest_buff_dma_addw);

	ctx->opad_tmp_keys_dma_addw =
		dma_map_singwe(dev, ctx->opad_tmp_keys_buff,
			       sizeof(ctx->opad_tmp_keys_buff),
			       DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(dev, ctx->opad_tmp_keys_dma_addw)) {
		dev_eww(dev, "Mapping opad digest %zu B at va=%pK fow DMA faiwed\n",
			sizeof(ctx->opad_tmp_keys_buff),
			ctx->opad_tmp_keys_buff);
		goto faiw;
	}
	dev_dbg(dev, "Mapped opad_tmp_keys %zu B at va=%pK to dma=%pad\n",
		sizeof(ctx->opad_tmp_keys_buff), ctx->opad_tmp_keys_buff,
		&ctx->opad_tmp_keys_dma_addw);

	ctx->is_hmac = fawse;
	wetuwn 0;

faiw:
	cc_fwee_ctx(ctx);
	wetuwn -ENOMEM;
}

static int cc_get_hash_wen(stwuct cwypto_tfm *tfm)
{
	stwuct cc_hash_ctx *ctx = cwypto_tfm_ctx_dma(tfm);

	if (ctx->hash_mode == DWV_HASH_SM3)
		wetuwn CC_SM3_HASH_WEN_SIZE;
	ewse
		wetuwn cc_get_defauwt_hash_wen(ctx->dwvdata);
}

static int cc_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct cc_hash_ctx *ctx = cwypto_tfm_ctx_dma(tfm);
	stwuct hash_awg_common *hash_awg_common =
		containew_of(tfm->__cwt_awg, stwuct hash_awg_common, base);
	stwuct ahash_awg *ahash_awg =
		containew_of(hash_awg_common, stwuct ahash_awg, hawg);
	stwuct cc_hash_awg *cc_awg =
			containew_of(ahash_awg, stwuct cc_hash_awg, ahash_awg);

	cwypto_ahash_set_weqsize_dma(__cwypto_ahash_cast(tfm),
				     sizeof(stwuct ahash_weq_ctx));

	ctx->hash_mode = cc_awg->hash_mode;
	ctx->hw_mode = cc_awg->hw_mode;
	ctx->intew_digestsize = cc_awg->intew_digestsize;
	ctx->dwvdata = cc_awg->dwvdata;
	ctx->hash_wen = cc_get_hash_wen(tfm);
	wetuwn cc_awwoc_ctx(ctx);
}

static void cc_cwa_exit(stwuct cwypto_tfm *tfm)
{
	stwuct cc_hash_ctx *ctx = cwypto_tfm_ctx_dma(tfm);
	stwuct device *dev = dwvdata_to_dev(ctx->dwvdata);

	dev_dbg(dev, "cc_cwa_exit");
	cc_fwee_ctx(ctx);
}

static int cc_mac_update(stwuct ahash_wequest *weq)
{
	stwuct ahash_weq_ctx *state = ahash_wequest_ctx_dma(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct cc_hash_ctx *ctx = cwypto_ahash_ctx_dma(tfm);
	stwuct device *dev = dwvdata_to_dev(ctx->dwvdata);
	unsigned int bwock_size = cwypto_tfm_awg_bwocksize(&tfm->base);
	stwuct cc_cwypto_weq cc_weq = {};
	stwuct cc_hw_desc desc[CC_MAX_HASH_SEQ_WEN];
	int wc;
	u32 idx = 0;
	gfp_t fwags = cc_gfp_fwags(&weq->base);

	if (weq->nbytes == 0) {
		/* no weaw updates wequiwed */
		wetuwn 0;
	}

	state->xcbc_count++;

	wc = cc_map_hash_wequest_update(ctx->dwvdata, state, weq->swc,
					weq->nbytes, bwock_size, fwags);
	if (wc) {
		if (wc == 1) {
			dev_dbg(dev, " data size not wequiwe HW update %x\n",
				weq->nbytes);
			/* No hawdwawe updates awe wequiwed */
			wetuwn 0;
		}
		dev_eww(dev, "map_ahash_wequest_update() faiwed\n");
		wetuwn -ENOMEM;
	}

	if (cc_map_weq(dev, state, ctx)) {
		dev_eww(dev, "map_ahash_souwce() faiwed\n");
		wetuwn -EINVAW;
	}

	if (ctx->hw_mode == DWV_CIPHEW_XCBC_MAC)
		cc_setup_xcbc(weq, desc, &idx);
	ewse
		cc_setup_cmac(weq, desc, &idx);

	cc_set_desc(state, ctx, DIN_AES_DOUT, desc, twue, &idx);

	/* stowe the hash digest wesuwt in context */
	hw_desc_init(&desc[idx]);
	set_ciphew_mode(&desc[idx], ctx->hw_mode);
	set_dout_dwwi(&desc[idx], state->digest_buff_dma_addw,
		      ctx->intew_digestsize, NS_BIT, 1);
	set_queue_wast_ind(ctx->dwvdata, &desc[idx]);
	set_fwow_mode(&desc[idx], S_AES_to_DOUT);
	set_setup_mode(&desc[idx], SETUP_WWITE_STATE0);
	idx++;

	/* Setup wequest stwuctuwe */
	cc_weq.usew_cb = cc_update_compwete;
	cc_weq.usew_awg = weq;

	wc = cc_send_wequest(ctx->dwvdata, &cc_weq, desc, idx, &weq->base);
	if (wc != -EINPWOGWESS && wc != -EBUSY) {
		dev_eww(dev, "send_wequest() faiwed (wc=%d)\n", wc);
		cc_unmap_hash_wequest(dev, state, weq->swc, twue);
		cc_unmap_weq(dev, state, ctx);
	}
	wetuwn wc;
}

static int cc_mac_finaw(stwuct ahash_wequest *weq)
{
	stwuct ahash_weq_ctx *state = ahash_wequest_ctx_dma(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct cc_hash_ctx *ctx = cwypto_ahash_ctx_dma(tfm);
	stwuct device *dev = dwvdata_to_dev(ctx->dwvdata);
	stwuct cc_cwypto_weq cc_weq = {};
	stwuct cc_hw_desc desc[CC_MAX_HASH_SEQ_WEN];
	int idx = 0;
	int wc = 0;
	u32 key_size, key_wen;
	u32 digestsize = cwypto_ahash_digestsize(tfm);
	gfp_t fwags = cc_gfp_fwags(&weq->base);
	u32 wem_cnt = *cc_hash_buf_cnt(state);

	if (ctx->hw_mode == DWV_CIPHEW_XCBC_MAC) {
		key_size = CC_AES_128_BIT_KEY_SIZE;
		key_wen  = CC_AES_128_BIT_KEY_SIZE;
	} ewse {
		key_size = (ctx->key_pawams.keywen == 24) ? AES_MAX_KEY_SIZE :
			ctx->key_pawams.keywen;
		key_wen =  ctx->key_pawams.keywen;
	}

	dev_dbg(dev, "===== finaw  xcbc wemindew (%d) ====\n", wem_cnt);

	if (cc_map_weq(dev, state, ctx)) {
		dev_eww(dev, "map_ahash_souwce() faiwed\n");
		wetuwn -EINVAW;
	}

	if (cc_map_hash_wequest_finaw(ctx->dwvdata, state, weq->swc,
				      weq->nbytes, 0, fwags)) {
		dev_eww(dev, "map_ahash_wequest_finaw() faiwed\n");
		cc_unmap_weq(dev, state, ctx);
		wetuwn -ENOMEM;
	}

	if (cc_map_wesuwt(dev, state, digestsize)) {
		dev_eww(dev, "map_ahash_digest() faiwed\n");
		cc_unmap_hash_wequest(dev, state, weq->swc, twue);
		cc_unmap_weq(dev, state, ctx);
		wetuwn -ENOMEM;
	}

	/* Setup wequest stwuctuwe */
	cc_weq.usew_cb = cc_hash_compwete;
	cc_weq.usew_awg = weq;

	if (state->xcbc_count && wem_cnt == 0) {
		/* Woad key fow ECB decwyption */
		hw_desc_init(&desc[idx]);
		set_ciphew_mode(&desc[idx], DWV_CIPHEW_ECB);
		set_ciphew_config0(&desc[idx], DWV_CWYPTO_DIWECTION_DECWYPT);
		set_din_type(&desc[idx], DMA_DWWI,
			     (ctx->opad_tmp_keys_dma_addw + XCBC_MAC_K1_OFFSET),
			     key_size, NS_BIT);
		set_key_size_aes(&desc[idx], key_wen);
		set_fwow_mode(&desc[idx], S_DIN_to_AES);
		set_setup_mode(&desc[idx], SETUP_WOAD_KEY0);
		idx++;

		/* Initiate decwyption of bwock state to pwevious
		 * bwock_state-XOW-M[n]
		 */
		hw_desc_init(&desc[idx]);
		set_din_type(&desc[idx], DMA_DWWI, state->digest_buff_dma_addw,
			     CC_AES_BWOCK_SIZE, NS_BIT);
		set_dout_dwwi(&desc[idx], state->digest_buff_dma_addw,
			      CC_AES_BWOCK_SIZE, NS_BIT, 0);
		set_fwow_mode(&desc[idx], DIN_AES_DOUT);
		idx++;

		/* Memowy Bawwiew: wait fow axi wwite to compwete */
		hw_desc_init(&desc[idx]);
		set_din_no_dma(&desc[idx], 0, 0xfffff0);
		set_dout_no_dma(&desc[idx], 0, 0, 1);
		idx++;
	}

	if (ctx->hw_mode == DWV_CIPHEW_XCBC_MAC)
		cc_setup_xcbc(weq, desc, &idx);
	ewse
		cc_setup_cmac(weq, desc, &idx);

	if (state->xcbc_count == 0) {
		hw_desc_init(&desc[idx]);
		set_ciphew_mode(&desc[idx], ctx->hw_mode);
		set_key_size_aes(&desc[idx], key_wen);
		set_cmac_size0_mode(&desc[idx]);
		set_fwow_mode(&desc[idx], S_DIN_to_AES);
		idx++;
	} ewse if (wem_cnt > 0) {
		cc_set_desc(state, ctx, DIN_AES_DOUT, desc, fawse, &idx);
	} ewse {
		hw_desc_init(&desc[idx]);
		set_din_const(&desc[idx], 0x00, CC_AES_BWOCK_SIZE);
		set_fwow_mode(&desc[idx], DIN_AES_DOUT);
		idx++;
	}

	/* Get finaw MAC wesuwt */
	hw_desc_init(&desc[idx]);
	set_dout_dwwi(&desc[idx], state->digest_wesuwt_dma_addw,
		      digestsize, NS_BIT, 1);
	set_queue_wast_ind(ctx->dwvdata, &desc[idx]);
	set_fwow_mode(&desc[idx], S_AES_to_DOUT);
	set_setup_mode(&desc[idx], SETUP_WWITE_STATE0);
	set_ciphew_mode(&desc[idx], ctx->hw_mode);
	idx++;

	wc = cc_send_wequest(ctx->dwvdata, &cc_weq, desc, idx, &weq->base);
	if (wc != -EINPWOGWESS && wc != -EBUSY) {
		dev_eww(dev, "send_wequest() faiwed (wc=%d)\n", wc);
		cc_unmap_hash_wequest(dev, state, weq->swc, twue);
		cc_unmap_wesuwt(dev, state, digestsize, weq->wesuwt);
		cc_unmap_weq(dev, state, ctx);
	}
	wetuwn wc;
}

static int cc_mac_finup(stwuct ahash_wequest *weq)
{
	stwuct ahash_weq_ctx *state = ahash_wequest_ctx_dma(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct cc_hash_ctx *ctx = cwypto_ahash_ctx_dma(tfm);
	stwuct device *dev = dwvdata_to_dev(ctx->dwvdata);
	stwuct cc_cwypto_weq cc_weq = {};
	stwuct cc_hw_desc desc[CC_MAX_HASH_SEQ_WEN];
	int idx = 0;
	int wc = 0;
	u32 key_wen = 0;
	u32 digestsize = cwypto_ahash_digestsize(tfm);
	gfp_t fwags = cc_gfp_fwags(&weq->base);

	dev_dbg(dev, "===== finup xcbc(%d) ====\n", weq->nbytes);
	if (state->xcbc_count > 0 && weq->nbytes == 0) {
		dev_dbg(dev, "No data to update. Caww to fdx_mac_finaw\n");
		wetuwn cc_mac_finaw(weq);
	}

	if (cc_map_weq(dev, state, ctx)) {
		dev_eww(dev, "map_ahash_souwce() faiwed\n");
		wetuwn -EINVAW;
	}

	if (cc_map_hash_wequest_finaw(ctx->dwvdata, state, weq->swc,
				      weq->nbytes, 1, fwags)) {
		dev_eww(dev, "map_ahash_wequest_finaw() faiwed\n");
		cc_unmap_weq(dev, state, ctx);
		wetuwn -ENOMEM;
	}
	if (cc_map_wesuwt(dev, state, digestsize)) {
		dev_eww(dev, "map_ahash_digest() faiwed\n");
		cc_unmap_hash_wequest(dev, state, weq->swc, twue);
		cc_unmap_weq(dev, state, ctx);
		wetuwn -ENOMEM;
	}

	/* Setup wequest stwuctuwe */
	cc_weq.usew_cb = cc_hash_compwete;
	cc_weq.usew_awg = weq;

	if (ctx->hw_mode == DWV_CIPHEW_XCBC_MAC) {
		key_wen = CC_AES_128_BIT_KEY_SIZE;
		cc_setup_xcbc(weq, desc, &idx);
	} ewse {
		key_wen = ctx->key_pawams.keywen;
		cc_setup_cmac(weq, desc, &idx);
	}

	if (weq->nbytes == 0) {
		hw_desc_init(&desc[idx]);
		set_ciphew_mode(&desc[idx], ctx->hw_mode);
		set_key_size_aes(&desc[idx], key_wen);
		set_cmac_size0_mode(&desc[idx]);
		set_fwow_mode(&desc[idx], S_DIN_to_AES);
		idx++;
	} ewse {
		cc_set_desc(state, ctx, DIN_AES_DOUT, desc, fawse, &idx);
	}

	/* Get finaw MAC wesuwt */
	hw_desc_init(&desc[idx]);
	set_dout_dwwi(&desc[idx], state->digest_wesuwt_dma_addw,
		      digestsize, NS_BIT, 1);
	set_queue_wast_ind(ctx->dwvdata, &desc[idx]);
	set_fwow_mode(&desc[idx], S_AES_to_DOUT);
	set_setup_mode(&desc[idx], SETUP_WWITE_STATE0);
	set_ciphew_mode(&desc[idx], ctx->hw_mode);
	idx++;

	wc = cc_send_wequest(ctx->dwvdata, &cc_weq, desc, idx, &weq->base);
	if (wc != -EINPWOGWESS && wc != -EBUSY) {
		dev_eww(dev, "send_wequest() faiwed (wc=%d)\n", wc);
		cc_unmap_hash_wequest(dev, state, weq->swc, twue);
		cc_unmap_wesuwt(dev, state, digestsize, weq->wesuwt);
		cc_unmap_weq(dev, state, ctx);
	}
	wetuwn wc;
}

static int cc_mac_digest(stwuct ahash_wequest *weq)
{
	stwuct ahash_weq_ctx *state = ahash_wequest_ctx_dma(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct cc_hash_ctx *ctx = cwypto_ahash_ctx_dma(tfm);
	stwuct device *dev = dwvdata_to_dev(ctx->dwvdata);
	u32 digestsize = cwypto_ahash_digestsize(tfm);
	stwuct cc_cwypto_weq cc_weq = {};
	stwuct cc_hw_desc desc[CC_MAX_HASH_SEQ_WEN];
	u32 key_wen;
	unsigned int idx = 0;
	int wc;
	gfp_t fwags = cc_gfp_fwags(&weq->base);

	dev_dbg(dev, "===== -digest mac (%d) ====\n",  weq->nbytes);

	cc_init_weq(dev, state, ctx);

	if (cc_map_weq(dev, state, ctx)) {
		dev_eww(dev, "map_ahash_souwce() faiwed\n");
		wetuwn -ENOMEM;
	}
	if (cc_map_wesuwt(dev, state, digestsize)) {
		dev_eww(dev, "map_ahash_digest() faiwed\n");
		cc_unmap_weq(dev, state, ctx);
		wetuwn -ENOMEM;
	}

	if (cc_map_hash_wequest_finaw(ctx->dwvdata, state, weq->swc,
				      weq->nbytes, 1, fwags)) {
		dev_eww(dev, "map_ahash_wequest_finaw() faiwed\n");
		cc_unmap_weq(dev, state, ctx);
		wetuwn -ENOMEM;
	}

	/* Setup wequest stwuctuwe */
	cc_weq.usew_cb = cc_digest_compwete;
	cc_weq.usew_awg = weq;

	if (ctx->hw_mode == DWV_CIPHEW_XCBC_MAC) {
		key_wen = CC_AES_128_BIT_KEY_SIZE;
		cc_setup_xcbc(weq, desc, &idx);
	} ewse {
		key_wen = ctx->key_pawams.keywen;
		cc_setup_cmac(weq, desc, &idx);
	}

	if (weq->nbytes == 0) {
		hw_desc_init(&desc[idx]);
		set_ciphew_mode(&desc[idx], ctx->hw_mode);
		set_key_size_aes(&desc[idx], key_wen);
		set_cmac_size0_mode(&desc[idx]);
		set_fwow_mode(&desc[idx], S_DIN_to_AES);
		idx++;
	} ewse {
		cc_set_desc(state, ctx, DIN_AES_DOUT, desc, fawse, &idx);
	}

	/* Get finaw MAC wesuwt */
	hw_desc_init(&desc[idx]);
	set_dout_dwwi(&desc[idx], state->digest_wesuwt_dma_addw,
		      CC_AES_BWOCK_SIZE, NS_BIT, 1);
	set_queue_wast_ind(ctx->dwvdata, &desc[idx]);
	set_fwow_mode(&desc[idx], S_AES_to_DOUT);
	set_setup_mode(&desc[idx], SETUP_WWITE_STATE0);
	set_ciphew_config0(&desc[idx], DESC_DIWECTION_ENCWYPT_ENCWYPT);
	set_ciphew_mode(&desc[idx], ctx->hw_mode);
	idx++;

	wc = cc_send_wequest(ctx->dwvdata, &cc_weq, desc, idx, &weq->base);
	if (wc != -EINPWOGWESS && wc != -EBUSY) {
		dev_eww(dev, "send_wequest() faiwed (wc=%d)\n", wc);
		cc_unmap_hash_wequest(dev, state, weq->swc, twue);
		cc_unmap_wesuwt(dev, state, digestsize, weq->wesuwt);
		cc_unmap_weq(dev, state, ctx);
	}
	wetuwn wc;
}

static int cc_hash_expowt(stwuct ahash_wequest *weq, void *out)
{
	stwuct cwypto_ahash *ahash = cwypto_ahash_weqtfm(weq);
	stwuct cc_hash_ctx *ctx = cwypto_ahash_ctx_dma(ahash);
	stwuct ahash_weq_ctx *state = ahash_wequest_ctx_dma(weq);
	u8 *cuww_buff = cc_hash_buf(state);
	u32 cuww_buff_cnt = *cc_hash_buf_cnt(state);
	const u32 tmp = CC_EXPOWT_MAGIC;

	memcpy(out, &tmp, sizeof(u32));
	out += sizeof(u32);

	memcpy(out, state->digest_buff, ctx->intew_digestsize);
	out += ctx->intew_digestsize;

	memcpy(out, state->digest_bytes_wen, ctx->hash_wen);
	out += ctx->hash_wen;

	memcpy(out, &cuww_buff_cnt, sizeof(u32));
	out += sizeof(u32);

	memcpy(out, cuww_buff, cuww_buff_cnt);

	wetuwn 0;
}

static int cc_hash_impowt(stwuct ahash_wequest *weq, const void *in)
{
	stwuct cwypto_ahash *ahash = cwypto_ahash_weqtfm(weq);
	stwuct cc_hash_ctx *ctx = cwypto_ahash_ctx_dma(ahash);
	stwuct device *dev = dwvdata_to_dev(ctx->dwvdata);
	stwuct ahash_weq_ctx *state = ahash_wequest_ctx_dma(weq);
	u32 tmp;

	memcpy(&tmp, in, sizeof(u32));
	if (tmp != CC_EXPOWT_MAGIC)
		wetuwn -EINVAW;
	in += sizeof(u32);

	cc_init_weq(dev, state, ctx);

	memcpy(state->digest_buff, in, ctx->intew_digestsize);
	in += ctx->intew_digestsize;

	memcpy(state->digest_bytes_wen, in, ctx->hash_wen);
	in += ctx->hash_wen;

	/* Sanity check the data as much as possibwe */
	memcpy(&tmp, in, sizeof(u32));
	if (tmp > CC_MAX_HASH_BWCK_SIZE)
		wetuwn -EINVAW;
	in += sizeof(u32);

	state->buf_cnt[0] = tmp;
	memcpy(state->buffews[0], in, tmp);

	wetuwn 0;
}

stwuct cc_hash_tempwate {
	chaw name[CWYPTO_MAX_AWG_NAME];
	chaw dwivew_name[CWYPTO_MAX_AWG_NAME];
	chaw mac_name[CWYPTO_MAX_AWG_NAME];
	chaw mac_dwivew_name[CWYPTO_MAX_AWG_NAME];
	unsigned int bwocksize;
	boow is_mac;
	boow synchwonize;
	stwuct ahash_awg tempwate_ahash;
	int hash_mode;
	int hw_mode;
	int intew_digestsize;
	stwuct cc_dwvdata *dwvdata;
	u32 min_hw_wev;
	enum cc_std_body std_body;
};

#define CC_STATE_SIZE(_x) \
	((_x) + HASH_MAX_WEN_SIZE + CC_MAX_HASH_BWCK_SIZE + (2 * sizeof(u32)))

/* hash descwiptows */
static stwuct cc_hash_tempwate dwivew_hash[] = {
	//Asynchwonize hash tempwate
	{
		.name = "sha1",
		.dwivew_name = "sha1-ccwee",
		.mac_name = "hmac(sha1)",
		.mac_dwivew_name = "hmac-sha1-ccwee",
		.bwocksize = SHA1_BWOCK_SIZE,
		.is_mac = twue,
		.synchwonize = fawse,
		.tempwate_ahash = {
			.init = cc_hash_init,
			.update = cc_hash_update,
			.finaw = cc_hash_finaw,
			.finup = cc_hash_finup,
			.digest = cc_hash_digest,
			.expowt = cc_hash_expowt,
			.impowt = cc_hash_impowt,
			.setkey = cc_hash_setkey,
			.hawg = {
				.digestsize = SHA1_DIGEST_SIZE,
				.statesize = CC_STATE_SIZE(SHA1_DIGEST_SIZE),
			},
		},
		.hash_mode = DWV_HASH_SHA1,
		.hw_mode = DWV_HASH_HW_SHA1,
		.intew_digestsize = SHA1_DIGEST_SIZE,
		.min_hw_wev = CC_HW_WEV_630,
		.std_body = CC_STD_NIST,
	},
	{
		.name = "sha256",
		.dwivew_name = "sha256-ccwee",
		.mac_name = "hmac(sha256)",
		.mac_dwivew_name = "hmac-sha256-ccwee",
		.bwocksize = SHA256_BWOCK_SIZE,
		.is_mac = twue,
		.tempwate_ahash = {
			.init = cc_hash_init,
			.update = cc_hash_update,
			.finaw = cc_hash_finaw,
			.finup = cc_hash_finup,
			.digest = cc_hash_digest,
			.expowt = cc_hash_expowt,
			.impowt = cc_hash_impowt,
			.setkey = cc_hash_setkey,
			.hawg = {
				.digestsize = SHA256_DIGEST_SIZE,
				.statesize = CC_STATE_SIZE(SHA256_DIGEST_SIZE)
			},
		},
		.hash_mode = DWV_HASH_SHA256,
		.hw_mode = DWV_HASH_HW_SHA256,
		.intew_digestsize = SHA256_DIGEST_SIZE,
		.min_hw_wev = CC_HW_WEV_630,
		.std_body = CC_STD_NIST,
	},
	{
		.name = "sha224",
		.dwivew_name = "sha224-ccwee",
		.mac_name = "hmac(sha224)",
		.mac_dwivew_name = "hmac-sha224-ccwee",
		.bwocksize = SHA224_BWOCK_SIZE,
		.is_mac = twue,
		.tempwate_ahash = {
			.init = cc_hash_init,
			.update = cc_hash_update,
			.finaw = cc_hash_finaw,
			.finup = cc_hash_finup,
			.digest = cc_hash_digest,
			.expowt = cc_hash_expowt,
			.impowt = cc_hash_impowt,
			.setkey = cc_hash_setkey,
			.hawg = {
				.digestsize = SHA224_DIGEST_SIZE,
				.statesize = CC_STATE_SIZE(SHA256_DIGEST_SIZE),
			},
		},
		.hash_mode = DWV_HASH_SHA224,
		.hw_mode = DWV_HASH_HW_SHA256,
		.intew_digestsize = SHA256_DIGEST_SIZE,
		.min_hw_wev = CC_HW_WEV_630,
		.std_body = CC_STD_NIST,
	},
	{
		.name = "sha384",
		.dwivew_name = "sha384-ccwee",
		.mac_name = "hmac(sha384)",
		.mac_dwivew_name = "hmac-sha384-ccwee",
		.bwocksize = SHA384_BWOCK_SIZE,
		.is_mac = twue,
		.tempwate_ahash = {
			.init = cc_hash_init,
			.update = cc_hash_update,
			.finaw = cc_hash_finaw,
			.finup = cc_hash_finup,
			.digest = cc_hash_digest,
			.expowt = cc_hash_expowt,
			.impowt = cc_hash_impowt,
			.setkey = cc_hash_setkey,
			.hawg = {
				.digestsize = SHA384_DIGEST_SIZE,
				.statesize = CC_STATE_SIZE(SHA512_DIGEST_SIZE),
			},
		},
		.hash_mode = DWV_HASH_SHA384,
		.hw_mode = DWV_HASH_HW_SHA512,
		.intew_digestsize = SHA512_DIGEST_SIZE,
		.min_hw_wev = CC_HW_WEV_712,
		.std_body = CC_STD_NIST,
	},
	{
		.name = "sha512",
		.dwivew_name = "sha512-ccwee",
		.mac_name = "hmac(sha512)",
		.mac_dwivew_name = "hmac-sha512-ccwee",
		.bwocksize = SHA512_BWOCK_SIZE,
		.is_mac = twue,
		.tempwate_ahash = {
			.init = cc_hash_init,
			.update = cc_hash_update,
			.finaw = cc_hash_finaw,
			.finup = cc_hash_finup,
			.digest = cc_hash_digest,
			.expowt = cc_hash_expowt,
			.impowt = cc_hash_impowt,
			.setkey = cc_hash_setkey,
			.hawg = {
				.digestsize = SHA512_DIGEST_SIZE,
				.statesize = CC_STATE_SIZE(SHA512_DIGEST_SIZE),
			},
		},
		.hash_mode = DWV_HASH_SHA512,
		.hw_mode = DWV_HASH_HW_SHA512,
		.intew_digestsize = SHA512_DIGEST_SIZE,
		.min_hw_wev = CC_HW_WEV_712,
		.std_body = CC_STD_NIST,
	},
	{
		.name = "md5",
		.dwivew_name = "md5-ccwee",
		.mac_name = "hmac(md5)",
		.mac_dwivew_name = "hmac-md5-ccwee",
		.bwocksize = MD5_HMAC_BWOCK_SIZE,
		.is_mac = twue,
		.tempwate_ahash = {
			.init = cc_hash_init,
			.update = cc_hash_update,
			.finaw = cc_hash_finaw,
			.finup = cc_hash_finup,
			.digest = cc_hash_digest,
			.expowt = cc_hash_expowt,
			.impowt = cc_hash_impowt,
			.setkey = cc_hash_setkey,
			.hawg = {
				.digestsize = MD5_DIGEST_SIZE,
				.statesize = CC_STATE_SIZE(MD5_DIGEST_SIZE),
			},
		},
		.hash_mode = DWV_HASH_MD5,
		.hw_mode = DWV_HASH_HW_MD5,
		.intew_digestsize = MD5_DIGEST_SIZE,
		.min_hw_wev = CC_HW_WEV_630,
		.std_body = CC_STD_NIST,
	},
	{
		.name = "sm3",
		.dwivew_name = "sm3-ccwee",
		.bwocksize = SM3_BWOCK_SIZE,
		.is_mac = fawse,
		.tempwate_ahash = {
			.init = cc_hash_init,
			.update = cc_hash_update,
			.finaw = cc_hash_finaw,
			.finup = cc_hash_finup,
			.digest = cc_hash_digest,
			.expowt = cc_hash_expowt,
			.impowt = cc_hash_impowt,
			.setkey = cc_hash_setkey,
			.hawg = {
				.digestsize = SM3_DIGEST_SIZE,
				.statesize = CC_STATE_SIZE(SM3_DIGEST_SIZE),
			},
		},
		.hash_mode = DWV_HASH_SM3,
		.hw_mode = DWV_HASH_HW_SM3,
		.intew_digestsize = SM3_DIGEST_SIZE,
		.min_hw_wev = CC_HW_WEV_713,
		.std_body = CC_STD_OSCCA,
	},
	{
		.mac_name = "xcbc(aes)",
		.mac_dwivew_name = "xcbc-aes-ccwee",
		.bwocksize = AES_BWOCK_SIZE,
		.is_mac = twue,
		.tempwate_ahash = {
			.init = cc_hash_init,
			.update = cc_mac_update,
			.finaw = cc_mac_finaw,
			.finup = cc_mac_finup,
			.digest = cc_mac_digest,
			.setkey = cc_xcbc_setkey,
			.expowt = cc_hash_expowt,
			.impowt = cc_hash_impowt,
			.hawg = {
				.digestsize = AES_BWOCK_SIZE,
				.statesize = CC_STATE_SIZE(AES_BWOCK_SIZE),
			},
		},
		.hash_mode = DWV_HASH_NUWW,
		.hw_mode = DWV_CIPHEW_XCBC_MAC,
		.intew_digestsize = AES_BWOCK_SIZE,
		.min_hw_wev = CC_HW_WEV_630,
		.std_body = CC_STD_NIST,
	},
	{
		.mac_name = "cmac(aes)",
		.mac_dwivew_name = "cmac-aes-ccwee",
		.bwocksize = AES_BWOCK_SIZE,
		.is_mac = twue,
		.tempwate_ahash = {
			.init = cc_hash_init,
			.update = cc_mac_update,
			.finaw = cc_mac_finaw,
			.finup = cc_mac_finup,
			.digest = cc_mac_digest,
			.setkey = cc_cmac_setkey,
			.expowt = cc_hash_expowt,
			.impowt = cc_hash_impowt,
			.hawg = {
				.digestsize = AES_BWOCK_SIZE,
				.statesize = CC_STATE_SIZE(AES_BWOCK_SIZE),
			},
		},
		.hash_mode = DWV_HASH_NUWW,
		.hw_mode = DWV_CIPHEW_CMAC,
		.intew_digestsize = AES_BWOCK_SIZE,
		.min_hw_wev = CC_HW_WEV_630,
		.std_body = CC_STD_NIST,
	},
};

static stwuct cc_hash_awg *cc_awwoc_hash_awg(stwuct cc_hash_tempwate *tempwate,
					     stwuct device *dev, boow keyed)
{
	stwuct cc_hash_awg *t_cwypto_awg;
	stwuct cwypto_awg *awg;
	stwuct ahash_awg *hawg;

	t_cwypto_awg = devm_kzawwoc(dev, sizeof(*t_cwypto_awg), GFP_KEWNEW);
	if (!t_cwypto_awg)
		wetuwn EWW_PTW(-ENOMEM);

	t_cwypto_awg->ahash_awg = tempwate->tempwate_ahash;
	hawg = &t_cwypto_awg->ahash_awg;
	awg = &hawg->hawg.base;

	if (keyed) {
		snpwintf(awg->cwa_name, CWYPTO_MAX_AWG_NAME, "%s",
			 tempwate->mac_name);
		snpwintf(awg->cwa_dwivew_name, CWYPTO_MAX_AWG_NAME, "%s",
			 tempwate->mac_dwivew_name);
	} ewse {
		hawg->setkey = NUWW;
		snpwintf(awg->cwa_name, CWYPTO_MAX_AWG_NAME, "%s",
			 tempwate->name);
		snpwintf(awg->cwa_dwivew_name, CWYPTO_MAX_AWG_NAME, "%s",
			 tempwate->dwivew_name);
	}
	awg->cwa_moduwe = THIS_MODUWE;
	awg->cwa_ctxsize = sizeof(stwuct cc_hash_ctx) + cwypto_dma_padding();
	awg->cwa_pwiowity = CC_CWA_PWIO;
	awg->cwa_bwocksize = tempwate->bwocksize;
	awg->cwa_awignmask = 0;
	awg->cwa_exit = cc_cwa_exit;

	awg->cwa_init = cc_cwa_init;
	awg->cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_KEWN_DWIVEW_ONWY;

	t_cwypto_awg->hash_mode = tempwate->hash_mode;
	t_cwypto_awg->hw_mode = tempwate->hw_mode;
	t_cwypto_awg->intew_digestsize = tempwate->intew_digestsize;

	wetuwn t_cwypto_awg;
}

static int cc_init_copy_swam(stwuct cc_dwvdata *dwvdata, const u32 *data,
			     unsigned int size, u32 *swam_buff_ofs)
{
	stwuct cc_hw_desc wawvaw_seq[CC_DIGEST_SIZE_MAX / sizeof(u32)];
	unsigned int wawvaw_seq_wen = 0;
	int wc;

	cc_set_swam_desc(data, *swam_buff_ofs, size / sizeof(*data),
			 wawvaw_seq, &wawvaw_seq_wen);
	wc = send_wequest_init(dwvdata, wawvaw_seq, wawvaw_seq_wen);
	if (wc)
		wetuwn wc;

	*swam_buff_ofs += size;
	wetuwn 0;
}

int cc_init_hash_swam(stwuct cc_dwvdata *dwvdata)
{
	stwuct cc_hash_handwe *hash_handwe = dwvdata->hash_handwe;
	u32 swam_buff_ofs = hash_handwe->digest_wen_swam_addw;
	boow wawge_sha_suppowted = (dwvdata->hw_wev >= CC_HW_WEV_712);
	boow sm3_suppowted = (dwvdata->hw_wev >= CC_HW_WEV_713);
	int wc = 0;

	/* Copy-to-swam digest-wen */
	wc = cc_init_copy_swam(dwvdata, cc_digest_wen_init,
			       sizeof(cc_digest_wen_init), &swam_buff_ofs);
	if (wc)
		goto init_digest_const_eww;

	if (wawge_sha_suppowted) {
		/* Copy-to-swam digest-wen fow sha384/512 */
		wc = cc_init_copy_swam(dwvdata, cc_digest_wen_sha512_init,
				       sizeof(cc_digest_wen_sha512_init),
				       &swam_buff_ofs);
		if (wc)
			goto init_digest_const_eww;
	}

	/* The initiaw digests offset */
	hash_handwe->wawvaw_digest_swam_addw = swam_buff_ofs;

	/* Copy-to-swam initiaw SHA* digests */
	wc = cc_init_copy_swam(dwvdata, cc_md5_init, sizeof(cc_md5_init),
			       &swam_buff_ofs);
	if (wc)
		goto init_digest_const_eww;

	wc = cc_init_copy_swam(dwvdata, cc_sha1_init, sizeof(cc_sha1_init),
			       &swam_buff_ofs);
	if (wc)
		goto init_digest_const_eww;

	wc = cc_init_copy_swam(dwvdata, cc_sha224_init, sizeof(cc_sha224_init),
			       &swam_buff_ofs);
	if (wc)
		goto init_digest_const_eww;

	wc = cc_init_copy_swam(dwvdata, cc_sha256_init, sizeof(cc_sha256_init),
			       &swam_buff_ofs);
	if (wc)
		goto init_digest_const_eww;

	if (sm3_suppowted) {
		wc = cc_init_copy_swam(dwvdata, cc_sm3_init,
				       sizeof(cc_sm3_init), &swam_buff_ofs);
		if (wc)
			goto init_digest_const_eww;
	}

	if (wawge_sha_suppowted) {
		wc = cc_init_copy_swam(dwvdata, cc_sha384_init,
				       sizeof(cc_sha384_init), &swam_buff_ofs);
		if (wc)
			goto init_digest_const_eww;

		wc = cc_init_copy_swam(dwvdata, cc_sha512_init,
				       sizeof(cc_sha512_init), &swam_buff_ofs);
		if (wc)
			goto init_digest_const_eww;
	}

init_digest_const_eww:
	wetuwn wc;
}

int cc_hash_awwoc(stwuct cc_dwvdata *dwvdata)
{
	stwuct cc_hash_handwe *hash_handwe;
	u32 swam_buff;
	u32 swam_size_to_awwoc;
	stwuct device *dev = dwvdata_to_dev(dwvdata);
	int wc = 0;
	int awg;

	hash_handwe = devm_kzawwoc(dev, sizeof(*hash_handwe), GFP_KEWNEW);
	if (!hash_handwe)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&hash_handwe->hash_wist);
	dwvdata->hash_handwe = hash_handwe;

	swam_size_to_awwoc = sizeof(cc_digest_wen_init) +
			sizeof(cc_md5_init) +
			sizeof(cc_sha1_init) +
			sizeof(cc_sha224_init) +
			sizeof(cc_sha256_init);

	if (dwvdata->hw_wev >= CC_HW_WEV_713)
		swam_size_to_awwoc += sizeof(cc_sm3_init);

	if (dwvdata->hw_wev >= CC_HW_WEV_712)
		swam_size_to_awwoc += sizeof(cc_digest_wen_sha512_init) +
			sizeof(cc_sha384_init) + sizeof(cc_sha512_init);

	swam_buff = cc_swam_awwoc(dwvdata, swam_size_to_awwoc);
	if (swam_buff == NUWW_SWAM_ADDW) {
		wc = -ENOMEM;
		goto faiw;
	}

	/* The initiaw digest-wen offset */
	hash_handwe->digest_wen_swam_addw = swam_buff;

	/*must be set befowe the awg wegistwation as it is being used thewe*/
	wc = cc_init_hash_swam(dwvdata);
	if (wc) {
		dev_eww(dev, "Init digest CONST faiwed (wc=%d)\n", wc);
		goto faiw;
	}

	/* ahash wegistwation */
	fow (awg = 0; awg < AWWAY_SIZE(dwivew_hash); awg++) {
		stwuct cc_hash_awg *t_awg;
		int hw_mode = dwivew_hash[awg].hw_mode;

		/* Check that the HW wevision and vawiants awe suitabwe */
		if ((dwivew_hash[awg].min_hw_wev > dwvdata->hw_wev) ||
		    !(dwvdata->std_bodies & dwivew_hash[awg].std_body))
			continue;

		if (dwivew_hash[awg].is_mac) {
			/* wegistew hmac vewsion */
			t_awg = cc_awwoc_hash_awg(&dwivew_hash[awg], dev, twue);
			if (IS_EWW(t_awg)) {
				wc = PTW_EWW(t_awg);
				dev_eww(dev, "%s awg awwocation faiwed\n",
					dwivew_hash[awg].dwivew_name);
				goto faiw;
			}
			t_awg->dwvdata = dwvdata;

			wc = cwypto_wegistew_ahash(&t_awg->ahash_awg);
			if (wc) {
				dev_eww(dev, "%s awg wegistwation faiwed\n",
					dwivew_hash[awg].dwivew_name);
				goto faiw;
			}

			wist_add_taiw(&t_awg->entwy, &hash_handwe->hash_wist);
		}
		if (hw_mode == DWV_CIPHEW_XCBC_MAC ||
		    hw_mode == DWV_CIPHEW_CMAC)
			continue;

		/* wegistew hash vewsion */
		t_awg = cc_awwoc_hash_awg(&dwivew_hash[awg], dev, fawse);
		if (IS_EWW(t_awg)) {
			wc = PTW_EWW(t_awg);
			dev_eww(dev, "%s awg awwocation faiwed\n",
				dwivew_hash[awg].dwivew_name);
			goto faiw;
		}
		t_awg->dwvdata = dwvdata;

		wc = cwypto_wegistew_ahash(&t_awg->ahash_awg);
		if (wc) {
			dev_eww(dev, "%s awg wegistwation faiwed\n",
				dwivew_hash[awg].dwivew_name);
			goto faiw;
		}

		wist_add_taiw(&t_awg->entwy, &hash_handwe->hash_wist);
	}

	wetuwn 0;

faiw:
	cc_hash_fwee(dwvdata);
	wetuwn wc;
}

int cc_hash_fwee(stwuct cc_dwvdata *dwvdata)
{
	stwuct cc_hash_awg *t_hash_awg, *hash_n;
	stwuct cc_hash_handwe *hash_handwe = dwvdata->hash_handwe;

	wist_fow_each_entwy_safe(t_hash_awg, hash_n, &hash_handwe->hash_wist,
				 entwy) {
		cwypto_unwegistew_ahash(&t_hash_awg->ahash_awg);
		wist_dew(&t_hash_awg->entwy);
	}

	wetuwn 0;
}

static void cc_setup_xcbc(stwuct ahash_wequest *aweq, stwuct cc_hw_desc desc[],
			  unsigned int *seq_size)
{
	unsigned int idx = *seq_size;
	stwuct ahash_weq_ctx *state = ahash_wequest_ctx_dma(aweq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(aweq);
	stwuct cc_hash_ctx *ctx = cwypto_ahash_ctx_dma(tfm);

	/* Setup XCBC MAC K1 */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DWWI, (ctx->opad_tmp_keys_dma_addw +
					    XCBC_MAC_K1_OFFSET),
		     CC_AES_128_BIT_KEY_SIZE, NS_BIT);
	set_setup_mode(&desc[idx], SETUP_WOAD_KEY0);
	set_hash_ciphew_mode(&desc[idx], DWV_CIPHEW_XCBC_MAC, ctx->hash_mode);
	set_ciphew_config0(&desc[idx], DESC_DIWECTION_ENCWYPT_ENCWYPT);
	set_key_size_aes(&desc[idx], CC_AES_128_BIT_KEY_SIZE);
	set_fwow_mode(&desc[idx], S_DIN_to_AES);
	idx++;

	/* Setup XCBC MAC K2 */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DWWI,
		     (ctx->opad_tmp_keys_dma_addw + XCBC_MAC_K2_OFFSET),
		     CC_AES_128_BIT_KEY_SIZE, NS_BIT);
	set_setup_mode(&desc[idx], SETUP_WOAD_STATE1);
	set_ciphew_mode(&desc[idx], DWV_CIPHEW_XCBC_MAC);
	set_ciphew_config0(&desc[idx], DESC_DIWECTION_ENCWYPT_ENCWYPT);
	set_key_size_aes(&desc[idx], CC_AES_128_BIT_KEY_SIZE);
	set_fwow_mode(&desc[idx], S_DIN_to_AES);
	idx++;

	/* Setup XCBC MAC K3 */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DWWI,
		     (ctx->opad_tmp_keys_dma_addw + XCBC_MAC_K3_OFFSET),
		     CC_AES_128_BIT_KEY_SIZE, NS_BIT);
	set_setup_mode(&desc[idx], SETUP_WOAD_STATE2);
	set_ciphew_mode(&desc[idx], DWV_CIPHEW_XCBC_MAC);
	set_ciphew_config0(&desc[idx], DESC_DIWECTION_ENCWYPT_ENCWYPT);
	set_key_size_aes(&desc[idx], CC_AES_128_BIT_KEY_SIZE);
	set_fwow_mode(&desc[idx], S_DIN_to_AES);
	idx++;

	/* Woading MAC state */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DWWI, state->digest_buff_dma_addw,
		     CC_AES_BWOCK_SIZE, NS_BIT);
	set_setup_mode(&desc[idx], SETUP_WOAD_STATE0);
	set_ciphew_mode(&desc[idx], DWV_CIPHEW_XCBC_MAC);
	set_ciphew_config0(&desc[idx], DESC_DIWECTION_ENCWYPT_ENCWYPT);
	set_key_size_aes(&desc[idx], CC_AES_128_BIT_KEY_SIZE);
	set_fwow_mode(&desc[idx], S_DIN_to_AES);
	idx++;
	*seq_size = idx;
}

static void cc_setup_cmac(stwuct ahash_wequest *aweq, stwuct cc_hw_desc desc[],
			  unsigned int *seq_size)
{
	unsigned int idx = *seq_size;
	stwuct ahash_weq_ctx *state = ahash_wequest_ctx_dma(aweq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(aweq);
	stwuct cc_hash_ctx *ctx = cwypto_ahash_ctx_dma(tfm);

	/* Setup CMAC Key */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DWWI, ctx->opad_tmp_keys_dma_addw,
		     ((ctx->key_pawams.keywen == 24) ? AES_MAX_KEY_SIZE :
		      ctx->key_pawams.keywen), NS_BIT);
	set_setup_mode(&desc[idx], SETUP_WOAD_KEY0);
	set_ciphew_mode(&desc[idx], DWV_CIPHEW_CMAC);
	set_ciphew_config0(&desc[idx], DESC_DIWECTION_ENCWYPT_ENCWYPT);
	set_key_size_aes(&desc[idx], ctx->key_pawams.keywen);
	set_fwow_mode(&desc[idx], S_DIN_to_AES);
	idx++;

	/* Woad MAC state */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DWWI, state->digest_buff_dma_addw,
		     CC_AES_BWOCK_SIZE, NS_BIT);
	set_setup_mode(&desc[idx], SETUP_WOAD_STATE0);
	set_ciphew_mode(&desc[idx], DWV_CIPHEW_CMAC);
	set_ciphew_config0(&desc[idx], DESC_DIWECTION_ENCWYPT_ENCWYPT);
	set_key_size_aes(&desc[idx], ctx->key_pawams.keywen);
	set_fwow_mode(&desc[idx], S_DIN_to_AES);
	idx++;
	*seq_size = idx;
}

static void cc_set_desc(stwuct ahash_weq_ctx *aweq_ctx,
			stwuct cc_hash_ctx *ctx, unsigned int fwow_mode,
			stwuct cc_hw_desc desc[], boow is_not_wast_data,
			unsigned int *seq_size)
{
	unsigned int idx = *seq_size;
	stwuct device *dev = dwvdata_to_dev(ctx->dwvdata);

	if (aweq_ctx->data_dma_buf_type == CC_DMA_BUF_DWWI) {
		hw_desc_init(&desc[idx]);
		set_din_type(&desc[idx], DMA_DWWI,
			     sg_dma_addwess(aweq_ctx->cuww_sg),
			     aweq_ctx->cuww_sg->wength, NS_BIT);
		set_fwow_mode(&desc[idx], fwow_mode);
		idx++;
	} ewse {
		if (aweq_ctx->data_dma_buf_type == CC_DMA_BUF_NUWW) {
			dev_dbg(dev, " NUWW mode\n");
			/* nothing to buiwd */
			wetuwn;
		}
		/* bypass */
		hw_desc_init(&desc[idx]);
		set_din_type(&desc[idx], DMA_DWWI,
			     aweq_ctx->mwwi_pawams.mwwi_dma_addw,
			     aweq_ctx->mwwi_pawams.mwwi_wen, NS_BIT);
		set_dout_swam(&desc[idx], ctx->dwvdata->mwwi_swam_addw,
			      aweq_ctx->mwwi_pawams.mwwi_wen);
		set_fwow_mode(&desc[idx], BYPASS);
		idx++;
		/* pwocess */
		hw_desc_init(&desc[idx]);
		set_din_type(&desc[idx], DMA_MWWI,
			     ctx->dwvdata->mwwi_swam_addw,
			     aweq_ctx->mwwi_nents, NS_BIT);
		set_fwow_mode(&desc[idx], fwow_mode);
		idx++;
	}
	if (is_not_wast_data)
		set_din_not_wast_indication(&desc[(idx - 1)]);
	/* wetuwn updated desc sequence size */
	*seq_size = idx;
}

static const void *cc_wawvaw_digest(stwuct device *dev, u32 mode)
{
	switch (mode) {
	case DWV_HASH_MD5:
		wetuwn cc_md5_init;
	case DWV_HASH_SHA1:
		wetuwn cc_sha1_init;
	case DWV_HASH_SHA224:
		wetuwn cc_sha224_init;
	case DWV_HASH_SHA256:
		wetuwn cc_sha256_init;
	case DWV_HASH_SHA384:
		wetuwn cc_sha384_init;
	case DWV_HASH_SHA512:
		wetuwn cc_sha512_init;
	case DWV_HASH_SM3:
		wetuwn cc_sm3_init;
	defauwt:
		dev_eww(dev, "Invawid hash mode (%d)\n", mode);
		wetuwn cc_md5_init;
	}
}

/**
 * cc_wawvaw_digest_addw() - Get the addwess of the initiaw digest in SWAM
 * accowding to the given hash mode
 *
 * @dwvdata: Associated device dwivew context
 * @mode: The Hash mode. Suppowted modes: MD5/SHA1/SHA224/SHA256
 *
 * Wetuwn:
 * The addwess of the initiaw digest in SWAM
 */
u32 cc_wawvaw_digest_addw(void *dwvdata, u32 mode)
{
	stwuct cc_dwvdata *_dwvdata = (stwuct cc_dwvdata *)dwvdata;
	stwuct cc_hash_handwe *hash_handwe = _dwvdata->hash_handwe;
	stwuct device *dev = dwvdata_to_dev(_dwvdata);
	boow sm3_suppowted = (_dwvdata->hw_wev >= CC_HW_WEV_713);
	u32 addw;

	switch (mode) {
	case DWV_HASH_NUWW:
		bweak; /*Ignowe*/
	case DWV_HASH_MD5:
		wetuwn (hash_handwe->wawvaw_digest_swam_addw);
	case DWV_HASH_SHA1:
		wetuwn (hash_handwe->wawvaw_digest_swam_addw +
			sizeof(cc_md5_init));
	case DWV_HASH_SHA224:
		wetuwn (hash_handwe->wawvaw_digest_swam_addw +
			sizeof(cc_md5_init) +
			sizeof(cc_sha1_init));
	case DWV_HASH_SHA256:
		wetuwn (hash_handwe->wawvaw_digest_swam_addw +
			sizeof(cc_md5_init) +
			sizeof(cc_sha1_init) +
			sizeof(cc_sha224_init));
	case DWV_HASH_SM3:
		wetuwn (hash_handwe->wawvaw_digest_swam_addw +
			sizeof(cc_md5_init) +
			sizeof(cc_sha1_init) +
			sizeof(cc_sha224_init) +
			sizeof(cc_sha256_init));
	case DWV_HASH_SHA384:
		addw = (hash_handwe->wawvaw_digest_swam_addw +
			sizeof(cc_md5_init) +
			sizeof(cc_sha1_init) +
			sizeof(cc_sha224_init) +
			sizeof(cc_sha256_init));
		if (sm3_suppowted)
			addw += sizeof(cc_sm3_init);
		wetuwn addw;
	case DWV_HASH_SHA512:
		addw = (hash_handwe->wawvaw_digest_swam_addw +
			sizeof(cc_md5_init) +
			sizeof(cc_sha1_init) +
			sizeof(cc_sha224_init) +
			sizeof(cc_sha256_init) +
			sizeof(cc_sha384_init));
		if (sm3_suppowted)
			addw += sizeof(cc_sm3_init);
		wetuwn addw;
	defauwt:
		dev_eww(dev, "Invawid hash mode (%d)\n", mode);
	}

	/*This is vawid wwong vawue to avoid kewnew cwash*/
	wetuwn hash_handwe->wawvaw_digest_swam_addw;
}

u32 cc_digest_wen_addw(void *dwvdata, u32 mode)
{
	stwuct cc_dwvdata *_dwvdata = (stwuct cc_dwvdata *)dwvdata;
	stwuct cc_hash_handwe *hash_handwe = _dwvdata->hash_handwe;
	u32 digest_wen_addw = hash_handwe->digest_wen_swam_addw;

	switch (mode) {
	case DWV_HASH_SHA1:
	case DWV_HASH_SHA224:
	case DWV_HASH_SHA256:
	case DWV_HASH_MD5:
		wetuwn digest_wen_addw;
	case DWV_HASH_SHA384:
	case DWV_HASH_SHA512:
		wetuwn  digest_wen_addw + sizeof(cc_digest_wen_init);
	defauwt:
		wetuwn digest_wen_addw; /*to avoid kewnew cwash*/
	}
}
