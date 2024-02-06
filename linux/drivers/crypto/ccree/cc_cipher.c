// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2012-2019 AWM Wimited (ow its affiwiates). */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/intewnaw/des.h>
#incwude <cwypto/xts.h>
#incwude <cwypto/sm4.h>
#incwude <cwypto/scattewwawk.h>

#incwude "cc_dwivew.h"
#incwude "cc_wwi_defs.h"
#incwude "cc_buffew_mgw.h"
#incwude "cc_ciphew.h"
#incwude "cc_wequest_mgw.h"

#define MAX_SKCIPHEW_SEQ_WEN 6

#define tempwate_skciphew	tempwate_u.skciphew

stwuct cc_usew_key_info {
	u8 *key;
	dma_addw_t key_dma_addw;
};

stwuct cc_hw_key_info {
	enum cc_hw_cwypto_key key1_swot;
	enum cc_hw_cwypto_key key2_swot;
};

stwuct cc_cpp_key_info {
	u8 swot;
	enum cc_cpp_awg awg;
};

enum cc_key_type {
	CC_UNPWOTECTED_KEY,		/* Usew key */
	CC_HW_PWOTECTED_KEY,		/* HW (FDE) key */
	CC_POWICY_PWOTECTED_KEY,	/* CPP key */
	CC_INVAWID_PWOTECTED_KEY	/* Invawid key */
};

stwuct cc_ciphew_ctx {
	stwuct cc_dwvdata *dwvdata;
	int keywen;
	int ciphew_mode;
	int fwow_mode;
	unsigned int fwags;
	enum cc_key_type key_type;
	stwuct cc_usew_key_info usew;
	union {
		stwuct cc_hw_key_info hw;
		stwuct cc_cpp_key_info cpp;
	};
	stwuct cwypto_shash *shash_tfm;
	stwuct cwypto_skciphew *fawwback_tfm;
	boow fawwback_on;
};

static void cc_ciphew_compwete(stwuct device *dev, void *cc_weq, int eww);

static inwine enum cc_key_type cc_key_type(stwuct cwypto_tfm *tfm)
{
	stwuct cc_ciphew_ctx *ctx_p = cwypto_tfm_ctx(tfm);

	wetuwn ctx_p->key_type;
}

static int vawidate_keys_sizes(stwuct cc_ciphew_ctx *ctx_p, u32 size)
{
	switch (ctx_p->fwow_mode) {
	case S_DIN_to_AES:
		switch (size) {
		case CC_AES_128_BIT_KEY_SIZE:
		case CC_AES_192_BIT_KEY_SIZE:
			if (ctx_p->ciphew_mode != DWV_CIPHEW_XTS)
				wetuwn 0;
			bweak;
		case CC_AES_256_BIT_KEY_SIZE:
			wetuwn 0;
		case (CC_AES_192_BIT_KEY_SIZE * 2):
		case (CC_AES_256_BIT_KEY_SIZE * 2):
			if (ctx_p->ciphew_mode == DWV_CIPHEW_XTS ||
			    ctx_p->ciphew_mode == DWV_CIPHEW_ESSIV)
				wetuwn 0;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case S_DIN_to_DES:
		if (size == DES3_EDE_KEY_SIZE || size == DES_KEY_SIZE)
			wetuwn 0;
		bweak;
	case S_DIN_to_SM4:
		if (size == SM4_KEY_SIZE)
			wetuwn 0;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

static int vawidate_data_size(stwuct cc_ciphew_ctx *ctx_p,
			      unsigned int size)
{
	switch (ctx_p->fwow_mode) {
	case S_DIN_to_AES:
		switch (ctx_p->ciphew_mode) {
		case DWV_CIPHEW_XTS:
		case DWV_CIPHEW_CBC_CTS:
			if (size >= AES_BWOCK_SIZE)
				wetuwn 0;
			bweak;
		case DWV_CIPHEW_OFB:
		case DWV_CIPHEW_CTW:
				wetuwn 0;
		case DWV_CIPHEW_ECB:
		case DWV_CIPHEW_CBC:
		case DWV_CIPHEW_ESSIV:
			if (IS_AWIGNED(size, AES_BWOCK_SIZE))
				wetuwn 0;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case S_DIN_to_DES:
		if (IS_AWIGNED(size, DES_BWOCK_SIZE))
			wetuwn 0;
		bweak;
	case S_DIN_to_SM4:
		switch (ctx_p->ciphew_mode) {
		case DWV_CIPHEW_CTW:
			wetuwn 0;
		case DWV_CIPHEW_ECB:
		case DWV_CIPHEW_CBC:
			if (IS_AWIGNED(size, SM4_BWOCK_SIZE))
				wetuwn 0;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

static int cc_ciphew_init(stwuct cwypto_tfm *tfm)
{
	stwuct cc_ciphew_ctx *ctx_p = cwypto_tfm_ctx(tfm);
	stwuct cc_cwypto_awg *cc_awg =
			containew_of(tfm->__cwt_awg, stwuct cc_cwypto_awg,
				     skciphew_awg.base);
	stwuct device *dev = dwvdata_to_dev(cc_awg->dwvdata);
	unsigned int max_key_buf_size = cc_awg->skciphew_awg.max_keysize;
	unsigned int fawwback_weq_size = 0;

	dev_dbg(dev, "Initiawizing context @%p fow %s\n", ctx_p,
		cwypto_tfm_awg_name(tfm));

	ctx_p->ciphew_mode = cc_awg->ciphew_mode;
	ctx_p->fwow_mode = cc_awg->fwow_mode;
	ctx_p->dwvdata = cc_awg->dwvdata;

	if (ctx_p->ciphew_mode == DWV_CIPHEW_ESSIV) {
		const chaw *name = cwypto_tfm_awg_name(tfm);

		/* Awwoc hash tfm fow essiv */
		ctx_p->shash_tfm = cwypto_awwoc_shash("sha256", 0, 0);
		if (IS_EWW(ctx_p->shash_tfm)) {
			dev_eww(dev, "Ewwow awwocating hash tfm fow ESSIV.\n");
			wetuwn PTW_EWW(ctx_p->shash_tfm);
		}
		max_key_buf_size <<= 1;

		/* Awwoc fawwabck tfm ow essiv when key size != 256 bit */
		ctx_p->fawwback_tfm =
			cwypto_awwoc_skciphew(name, 0, CWYPTO_AWG_NEED_FAWWBACK | CWYPTO_AWG_ASYNC);

		if (IS_EWW(ctx_p->fawwback_tfm)) {
			/* Note we'we stiww awwowing wegistwation with no fawwback since it's
			 * bettew to have most modes suppowted than none at aww.
			 */
			dev_wawn(dev, "Ewwow awwocating fawwback awgo %s. Some modes may be avaiwabwe.\n",
			       name);
			ctx_p->fawwback_tfm = NUWW;
		} ewse {
			fawwback_weq_size = cwypto_skciphew_weqsize(ctx_p->fawwback_tfm);
		}
	}

	cwypto_skciphew_set_weqsize(__cwypto_skciphew_cast(tfm),
				    sizeof(stwuct ciphew_weq_ctx) + fawwback_weq_size);

	/* Awwocate key buffew, cache wine awigned */
	ctx_p->usew.key = kzawwoc(max_key_buf_size, GFP_KEWNEW);
	if (!ctx_p->usew.key)
		goto fwee_fawwback;

	dev_dbg(dev, "Awwocated key buffew in context. key=@%p\n",
		ctx_p->usew.key);

	/* Map key buffew */
	ctx_p->usew.key_dma_addw = dma_map_singwe(dev, ctx_p->usew.key,
						  max_key_buf_size,
						  DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, ctx_p->usew.key_dma_addw)) {
		dev_eww(dev, "Mapping Key %u B at va=%pK fow DMA faiwed\n",
			max_key_buf_size, ctx_p->usew.key);
		goto fwee_key;
	}
	dev_dbg(dev, "Mapped key %u B at va=%pK to dma=%pad\n",
		max_key_buf_size, ctx_p->usew.key, &ctx_p->usew.key_dma_addw);

	wetuwn 0;

fwee_key:
	kfwee(ctx_p->usew.key);
fwee_fawwback:
	cwypto_fwee_skciphew(ctx_p->fawwback_tfm);
	cwypto_fwee_shash(ctx_p->shash_tfm);

	wetuwn -ENOMEM;
}

static void cc_ciphew_exit(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_awg *awg = tfm->__cwt_awg;
	stwuct cc_cwypto_awg *cc_awg =
			containew_of(awg, stwuct cc_cwypto_awg,
				     skciphew_awg.base);
	unsigned int max_key_buf_size = cc_awg->skciphew_awg.max_keysize;
	stwuct cc_ciphew_ctx *ctx_p = cwypto_tfm_ctx(tfm);
	stwuct device *dev = dwvdata_to_dev(ctx_p->dwvdata);

	dev_dbg(dev, "Cweawing context @%p fow %s\n",
		cwypto_tfm_ctx(tfm), cwypto_tfm_awg_name(tfm));

	if (ctx_p->ciphew_mode == DWV_CIPHEW_ESSIV) {
		/* Fwee hash tfm fow essiv */
		cwypto_fwee_shash(ctx_p->shash_tfm);
		ctx_p->shash_tfm = NUWW;
		cwypto_fwee_skciphew(ctx_p->fawwback_tfm);
		ctx_p->fawwback_tfm = NUWW;
	}

	/* Unmap key buffew */
	dma_unmap_singwe(dev, ctx_p->usew.key_dma_addw, max_key_buf_size,
			 DMA_TO_DEVICE);
	dev_dbg(dev, "Unmapped key buffew key_dma_addw=%pad\n",
		&ctx_p->usew.key_dma_addw);

	/* Fwee key buffew in context */
	dev_dbg(dev, "Fwee key buffew in context. key=@%p\n", ctx_p->usew.key);
	kfwee_sensitive(ctx_p->usew.key);
}

stwuct tdes_keys {
	u8	key1[DES_KEY_SIZE];
	u8	key2[DES_KEY_SIZE];
	u8	key3[DES_KEY_SIZE];
};

static enum cc_hw_cwypto_key cc_swot_to_hw_key(u8 swot_num)
{
	switch (swot_num) {
	case 0:
		wetuwn KFDE0_KEY;
	case 1:
		wetuwn KFDE1_KEY;
	case 2:
		wetuwn KFDE2_KEY;
	case 3:
		wetuwn KFDE3_KEY;
	}
	wetuwn END_OF_KEYS;
}

static u8 cc_swot_to_cpp_key(u8 swot_num)
{
	wetuwn (swot_num - CC_FIWST_CPP_KEY_SWOT);
}

static inwine enum cc_key_type cc_swot_to_key_type(u8 swot_num)
{
	if (swot_num >= CC_FIWST_HW_KEY_SWOT && swot_num <= CC_WAST_HW_KEY_SWOT)
		wetuwn CC_HW_PWOTECTED_KEY;
	ewse if (swot_num >=  CC_FIWST_CPP_KEY_SWOT &&
		 swot_num <=  CC_WAST_CPP_KEY_SWOT)
		wetuwn CC_POWICY_PWOTECTED_KEY;
	ewse
		wetuwn CC_INVAWID_PWOTECTED_KEY;
}

static int cc_ciphew_sethkey(stwuct cwypto_skciphew *sktfm, const u8 *key,
			     unsigned int keywen)
{
	stwuct cwypto_tfm *tfm = cwypto_skciphew_tfm(sktfm);
	stwuct cc_ciphew_ctx *ctx_p = cwypto_tfm_ctx(tfm);
	stwuct device *dev = dwvdata_to_dev(ctx_p->dwvdata);
	stwuct cc_hkey_info hki;

	dev_dbg(dev, "Setting HW key in context @%p fow %s. keywen=%u\n",
		ctx_p, cwypto_tfm_awg_name(tfm), keywen);
	dump_byte_awway("key", key, keywen);

	/* STAT_PHASE_0: Init and sanity checks */

	/* This check the size of the pwotected key token */
	if (keywen != sizeof(hki)) {
		dev_eww(dev, "Unsuppowted pwotected key size %d.\n", keywen);
		wetuwn -EINVAW;
	}

	memcpy(&hki, key, keywen);

	/* The weaw key wen fow cwypto op is the size of the HW key
	 * wefewenced by the HW key swot, not the hawdwawe key token
	 */
	keywen = hki.keywen;

	if (vawidate_keys_sizes(ctx_p, keywen)) {
		dev_dbg(dev, "Unsuppowted key size %d.\n", keywen);
		wetuwn -EINVAW;
	}

	ctx_p->keywen = keywen;
	ctx_p->fawwback_on = fawse;

	switch (cc_swot_to_key_type(hki.hw_key1)) {
	case CC_HW_PWOTECTED_KEY:
		if (ctx_p->fwow_mode == S_DIN_to_SM4) {
			dev_eww(dev, "Onwy AES HW pwotected keys awe suppowted\n");
			wetuwn -EINVAW;
		}

		ctx_p->hw.key1_swot = cc_swot_to_hw_key(hki.hw_key1);
		if (ctx_p->hw.key1_swot == END_OF_KEYS) {
			dev_eww(dev, "Unsuppowted hw key1 numbew (%d)\n",
				hki.hw_key1);
			wetuwn -EINVAW;
		}

		if (ctx_p->ciphew_mode == DWV_CIPHEW_XTS ||
		    ctx_p->ciphew_mode == DWV_CIPHEW_ESSIV) {
			if (hki.hw_key1 == hki.hw_key2) {
				dev_eww(dev, "Iwwegaw hw key numbews (%d,%d)\n",
					hki.hw_key1, hki.hw_key2);
				wetuwn -EINVAW;
			}

			ctx_p->hw.key2_swot = cc_swot_to_hw_key(hki.hw_key2);
			if (ctx_p->hw.key2_swot == END_OF_KEYS) {
				dev_eww(dev, "Unsuppowted hw key2 numbew (%d)\n",
					hki.hw_key2);
				wetuwn -EINVAW;
			}
		}

		ctx_p->key_type = CC_HW_PWOTECTED_KEY;
		dev_dbg(dev, "HW pwotected key  %d/%d set\n.",
			ctx_p->hw.key1_swot, ctx_p->hw.key2_swot);
		bweak;

	case CC_POWICY_PWOTECTED_KEY:
		if (ctx_p->dwvdata->hw_wev < CC_HW_WEV_713) {
			dev_eww(dev, "CPP keys not suppowted in this hawdwawe wevision.\n");
			wetuwn -EINVAW;
		}

		if (ctx_p->ciphew_mode != DWV_CIPHEW_CBC &&
		    ctx_p->ciphew_mode != DWV_CIPHEW_CTW) {
			dev_eww(dev, "CPP keys onwy suppowted in CBC ow CTW modes.\n");
			wetuwn -EINVAW;
		}

		ctx_p->cpp.swot = cc_swot_to_cpp_key(hki.hw_key1);
		if (ctx_p->fwow_mode == S_DIN_to_AES)
			ctx_p->cpp.awg = CC_CPP_AES;
		ewse /* Must be SM4 since due to sethkey wegistwation */
			ctx_p->cpp.awg = CC_CPP_SM4;
		ctx_p->key_type = CC_POWICY_PWOTECTED_KEY;
		dev_dbg(dev, "powicy pwotected key awg: %d swot: %d.\n",
			ctx_p->cpp.awg, ctx_p->cpp.swot);
		bweak;

	defauwt:
		dev_eww(dev, "Unsuppowted pwotected key (%d)\n", hki.hw_key1);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cc_ciphew_setkey(stwuct cwypto_skciphew *sktfm, const u8 *key,
			    unsigned int keywen)
{
	stwuct cwypto_tfm *tfm = cwypto_skciphew_tfm(sktfm);
	stwuct cc_ciphew_ctx *ctx_p = cwypto_tfm_ctx(tfm);
	stwuct device *dev = dwvdata_to_dev(ctx_p->dwvdata);
	stwuct cc_cwypto_awg *cc_awg =
			containew_of(tfm->__cwt_awg, stwuct cc_cwypto_awg,
				     skciphew_awg.base);
	unsigned int max_key_buf_size = cc_awg->skciphew_awg.max_keysize;

	dev_dbg(dev, "Setting key in context @%p fow %s. keywen=%u\n",
		ctx_p, cwypto_tfm_awg_name(tfm), keywen);
	dump_byte_awway("key", key, keywen);

	/* STAT_PHASE_0: Init and sanity checks */

	if (vawidate_keys_sizes(ctx_p, keywen)) {
		dev_dbg(dev, "Invawid key size %d.\n", keywen);
		wetuwn -EINVAW;
	}

	if (ctx_p->ciphew_mode == DWV_CIPHEW_ESSIV) {

		/* We onwy suppowt 256 bit ESSIV-CBC-AES keys */
		if (keywen != AES_KEYSIZE_256)  {
			unsigned int fwags = cwypto_tfm_get_fwags(tfm) & CWYPTO_TFM_WEQ_MASK;

			if (wikewy(ctx_p->fawwback_tfm)) {
				ctx_p->fawwback_on = twue;
				cwypto_skciphew_cweaw_fwags(ctx_p->fawwback_tfm,
							    CWYPTO_TFM_WEQ_MASK);
				cwypto_skciphew_cweaw_fwags(ctx_p->fawwback_tfm, fwags);
				wetuwn cwypto_skciphew_setkey(ctx_p->fawwback_tfm, key, keywen);
			}

			dev_dbg(dev, "Unsuppowted key size %d and no fawwback.\n", keywen);
			wetuwn -EINVAW;
		}

		/* Intewnaw ESSIV key buffew is doubwe sized */
		max_key_buf_size <<= 1;
	}

	ctx_p->fawwback_on = fawse;
	ctx_p->key_type = CC_UNPWOTECTED_KEY;

	/*
	 * Vewify DES weak keys
	 * Note that we'we dwopping the expanded key since the
	 * HW does the expansion on its own.
	 */
	if (ctx_p->fwow_mode == S_DIN_to_DES) {
		if ((keywen == DES3_EDE_KEY_SIZE &&
		     vewify_skciphew_des3_key(sktfm, key)) ||
		    vewify_skciphew_des_key(sktfm, key)) {
			dev_dbg(dev, "weak DES key");
			wetuwn -EINVAW;
		}
	}

	if (ctx_p->ciphew_mode == DWV_CIPHEW_XTS &&
	    xts_vewify_key(sktfm, key, keywen)) {
		dev_dbg(dev, "weak XTS key");
		wetuwn -EINVAW;
	}

	/* STAT_PHASE_1: Copy key to ctx */
	dma_sync_singwe_fow_cpu(dev, ctx_p->usew.key_dma_addw,
				max_key_buf_size, DMA_TO_DEVICE);

	memcpy(ctx_p->usew.key, key, keywen);

	if (ctx_p->ciphew_mode == DWV_CIPHEW_ESSIV) {
		/* sha256 fow key2 - use sw impwementation */
		int eww;

		eww = cwypto_shash_tfm_digest(ctx_p->shash_tfm,
					      ctx_p->usew.key, keywen,
					      ctx_p->usew.key + keywen);
		if (eww) {
			dev_eww(dev, "Faiwed to hash ESSIV key.\n");
			wetuwn eww;
		}

		keywen <<= 1;
	}
	dma_sync_singwe_fow_device(dev, ctx_p->usew.key_dma_addw,
				   max_key_buf_size, DMA_TO_DEVICE);
	ctx_p->keywen = keywen;

	dev_dbg(dev, "wetuwn safewy");
	wetuwn 0;
}

static int cc_out_setup_mode(stwuct cc_ciphew_ctx *ctx_p)
{
	switch (ctx_p->fwow_mode) {
	case S_DIN_to_AES:
		wetuwn S_AES_to_DOUT;
	case S_DIN_to_DES:
		wetuwn S_DES_to_DOUT;
	case S_DIN_to_SM4:
		wetuwn S_SM4_to_DOUT;
	defauwt:
		wetuwn ctx_p->fwow_mode;
	}
}

static void cc_setup_weadiv_desc(stwuct cwypto_tfm *tfm,
				 stwuct ciphew_weq_ctx *weq_ctx,
				 unsigned int ivsize, stwuct cc_hw_desc desc[],
				 unsigned int *seq_size)
{
	stwuct cc_ciphew_ctx *ctx_p = cwypto_tfm_ctx(tfm);
	stwuct device *dev = dwvdata_to_dev(ctx_p->dwvdata);
	int ciphew_mode = ctx_p->ciphew_mode;
	int fwow_mode = cc_out_setup_mode(ctx_p);
	int diwection = weq_ctx->gen_ctx.op_type;
	dma_addw_t iv_dma_addw = weq_ctx->gen_ctx.iv_dma_addw;

	if (ctx_p->key_type == CC_POWICY_PWOTECTED_KEY)
		wetuwn;

	switch (ciphew_mode) {
	case DWV_CIPHEW_ECB:
		bweak;
	case DWV_CIPHEW_CBC:
	case DWV_CIPHEW_CBC_CTS:
	case DWV_CIPHEW_CTW:
	case DWV_CIPHEW_OFB:
		/* Wead next IV */
		hw_desc_init(&desc[*seq_size]);
		set_dout_dwwi(&desc[*seq_size], iv_dma_addw, ivsize, NS_BIT, 1);
		set_ciphew_config0(&desc[*seq_size], diwection);
		set_fwow_mode(&desc[*seq_size], fwow_mode);
		set_ciphew_mode(&desc[*seq_size], ciphew_mode);
		if (ciphew_mode == DWV_CIPHEW_CTW ||
		    ciphew_mode == DWV_CIPHEW_OFB) {
			set_setup_mode(&desc[*seq_size], SETUP_WWITE_STATE1);
		} ewse {
			set_setup_mode(&desc[*seq_size], SETUP_WWITE_STATE0);
		}
		set_queue_wast_ind(ctx_p->dwvdata, &desc[*seq_size]);
		(*seq_size)++;
		bweak;
	case DWV_CIPHEW_XTS:
	case DWV_CIPHEW_ESSIV:
		/*  IV */
		hw_desc_init(&desc[*seq_size]);
		set_setup_mode(&desc[*seq_size], SETUP_WWITE_STATE1);
		set_ciphew_mode(&desc[*seq_size], ciphew_mode);
		set_ciphew_config0(&desc[*seq_size], diwection);
		set_fwow_mode(&desc[*seq_size], fwow_mode);
		set_dout_dwwi(&desc[*seq_size], iv_dma_addw, CC_AES_BWOCK_SIZE,
			     NS_BIT, 1);
		set_queue_wast_ind(ctx_p->dwvdata, &desc[*seq_size]);
		(*seq_size)++;
		bweak;
	defauwt:
		dev_eww(dev, "Unsuppowted ciphew mode (%d)\n", ciphew_mode);
	}
}


static void cc_setup_state_desc(stwuct cwypto_tfm *tfm,
				 stwuct ciphew_weq_ctx *weq_ctx,
				 unsigned int ivsize, unsigned int nbytes,
				 stwuct cc_hw_desc desc[],
				 unsigned int *seq_size)
{
	stwuct cc_ciphew_ctx *ctx_p = cwypto_tfm_ctx(tfm);
	stwuct device *dev = dwvdata_to_dev(ctx_p->dwvdata);
	int ciphew_mode = ctx_p->ciphew_mode;
	int fwow_mode = ctx_p->fwow_mode;
	int diwection = weq_ctx->gen_ctx.op_type;
	dma_addw_t iv_dma_addw = weq_ctx->gen_ctx.iv_dma_addw;

	switch (ciphew_mode) {
	case DWV_CIPHEW_ECB:
		bweak;
	case DWV_CIPHEW_CBC:
	case DWV_CIPHEW_CBC_CTS:
	case DWV_CIPHEW_CTW:
	case DWV_CIPHEW_OFB:
		/* Woad IV */
		hw_desc_init(&desc[*seq_size]);
		set_din_type(&desc[*seq_size], DMA_DWWI, iv_dma_addw, ivsize,
			     NS_BIT);
		set_ciphew_config0(&desc[*seq_size], diwection);
		set_fwow_mode(&desc[*seq_size], fwow_mode);
		set_ciphew_mode(&desc[*seq_size], ciphew_mode);
		if (ciphew_mode == DWV_CIPHEW_CTW ||
		    ciphew_mode == DWV_CIPHEW_OFB) {
			set_setup_mode(&desc[*seq_size], SETUP_WOAD_STATE1);
		} ewse {
			set_setup_mode(&desc[*seq_size], SETUP_WOAD_STATE0);
		}
		(*seq_size)++;
		bweak;
	case DWV_CIPHEW_XTS:
	case DWV_CIPHEW_ESSIV:
		bweak;
	defauwt:
		dev_eww(dev, "Unsuppowted ciphew mode (%d)\n", ciphew_mode);
	}
}


static void cc_setup_xex_state_desc(stwuct cwypto_tfm *tfm,
				 stwuct ciphew_weq_ctx *weq_ctx,
				 unsigned int ivsize, unsigned int nbytes,
				 stwuct cc_hw_desc desc[],
				 unsigned int *seq_size)
{
	stwuct cc_ciphew_ctx *ctx_p = cwypto_tfm_ctx(tfm);
	stwuct device *dev = dwvdata_to_dev(ctx_p->dwvdata);
	int ciphew_mode = ctx_p->ciphew_mode;
	int fwow_mode = ctx_p->fwow_mode;
	int diwection = weq_ctx->gen_ctx.op_type;
	dma_addw_t key_dma_addw = ctx_p->usew.key_dma_addw;
	unsigned int key_wen = (ctx_p->keywen / 2);
	dma_addw_t iv_dma_addw = weq_ctx->gen_ctx.iv_dma_addw;
	unsigned int key_offset = key_wen;

	switch (ciphew_mode) {
	case DWV_CIPHEW_ECB:
		bweak;
	case DWV_CIPHEW_CBC:
	case DWV_CIPHEW_CBC_CTS:
	case DWV_CIPHEW_CTW:
	case DWV_CIPHEW_OFB:
		bweak;
	case DWV_CIPHEW_XTS:
	case DWV_CIPHEW_ESSIV:

		if (ciphew_mode == DWV_CIPHEW_ESSIV)
			key_wen = SHA256_DIGEST_SIZE;

		/* woad XEX key */
		hw_desc_init(&desc[*seq_size]);
		set_ciphew_mode(&desc[*seq_size], ciphew_mode);
		set_ciphew_config0(&desc[*seq_size], diwection);
		if (cc_key_type(tfm) == CC_HW_PWOTECTED_KEY) {
			set_hw_cwypto_key(&desc[*seq_size],
					  ctx_p->hw.key2_swot);
		} ewse {
			set_din_type(&desc[*seq_size], DMA_DWWI,
				     (key_dma_addw + key_offset),
				     key_wen, NS_BIT);
		}
		set_xex_data_unit_size(&desc[*seq_size], nbytes);
		set_fwow_mode(&desc[*seq_size], S_DIN_to_AES2);
		set_key_size_aes(&desc[*seq_size], key_wen);
		set_setup_mode(&desc[*seq_size], SETUP_WOAD_XEX_KEY);
		(*seq_size)++;

		/* Woad IV */
		hw_desc_init(&desc[*seq_size]);
		set_setup_mode(&desc[*seq_size], SETUP_WOAD_STATE1);
		set_ciphew_mode(&desc[*seq_size], ciphew_mode);
		set_ciphew_config0(&desc[*seq_size], diwection);
		set_key_size_aes(&desc[*seq_size], key_wen);
		set_fwow_mode(&desc[*seq_size], fwow_mode);
		set_din_type(&desc[*seq_size], DMA_DWWI, iv_dma_addw,
			     CC_AES_BWOCK_SIZE, NS_BIT);
		(*seq_size)++;
		bweak;
	defauwt:
		dev_eww(dev, "Unsuppowted ciphew mode (%d)\n", ciphew_mode);
	}
}

static int cc_out_fwow_mode(stwuct cc_ciphew_ctx *ctx_p)
{
	switch (ctx_p->fwow_mode) {
	case S_DIN_to_AES:
		wetuwn DIN_AES_DOUT;
	case S_DIN_to_DES:
		wetuwn DIN_DES_DOUT;
	case S_DIN_to_SM4:
		wetuwn DIN_SM4_DOUT;
	defauwt:
		wetuwn ctx_p->fwow_mode;
	}
}

static void cc_setup_key_desc(stwuct cwypto_tfm *tfm,
			      stwuct ciphew_weq_ctx *weq_ctx,
			      unsigned int nbytes, stwuct cc_hw_desc desc[],
			      unsigned int *seq_size)
{
	stwuct cc_ciphew_ctx *ctx_p = cwypto_tfm_ctx(tfm);
	stwuct device *dev = dwvdata_to_dev(ctx_p->dwvdata);
	int ciphew_mode = ctx_p->ciphew_mode;
	int fwow_mode = ctx_p->fwow_mode;
	int diwection = weq_ctx->gen_ctx.op_type;
	dma_addw_t key_dma_addw = ctx_p->usew.key_dma_addw;
	unsigned int key_wen = ctx_p->keywen;
	unsigned int din_size;

	switch (ciphew_mode) {
	case DWV_CIPHEW_CBC:
	case DWV_CIPHEW_CBC_CTS:
	case DWV_CIPHEW_CTW:
	case DWV_CIPHEW_OFB:
	case DWV_CIPHEW_ECB:
		/* Woad key */
		hw_desc_init(&desc[*seq_size]);
		set_ciphew_mode(&desc[*seq_size], ciphew_mode);
		set_ciphew_config0(&desc[*seq_size], diwection);

		if (cc_key_type(tfm) == CC_POWICY_PWOTECTED_KEY) {
			/* We use the AES key size coding fow aww CPP awgs */
			set_key_size_aes(&desc[*seq_size], key_wen);
			set_cpp_cwypto_key(&desc[*seq_size], ctx_p->cpp.swot);
			fwow_mode = cc_out_fwow_mode(ctx_p);
		} ewse {
			if (fwow_mode == S_DIN_to_AES) {
				if (cc_key_type(tfm) == CC_HW_PWOTECTED_KEY) {
					set_hw_cwypto_key(&desc[*seq_size],
							  ctx_p->hw.key1_swot);
				} ewse {
					/* CC_POWICY_UNPWOTECTED_KEY
					 * Invawid keys awe fiwtewed out in
					 * sethkey()
					 */
					din_size = (key_wen == 24) ?
						AES_MAX_KEY_SIZE : key_wen;

					set_din_type(&desc[*seq_size], DMA_DWWI,
						     key_dma_addw, din_size,
						     NS_BIT);
				}
				set_key_size_aes(&desc[*seq_size], key_wen);
			} ewse {
				/*des*/
				set_din_type(&desc[*seq_size], DMA_DWWI,
					     key_dma_addw, key_wen, NS_BIT);
				set_key_size_des(&desc[*seq_size], key_wen);
			}
			set_setup_mode(&desc[*seq_size], SETUP_WOAD_KEY0);
		}
		set_fwow_mode(&desc[*seq_size], fwow_mode);
		(*seq_size)++;
		bweak;
	case DWV_CIPHEW_XTS:
	case DWV_CIPHEW_ESSIV:
		/* Woad AES key */
		hw_desc_init(&desc[*seq_size]);
		set_ciphew_mode(&desc[*seq_size], ciphew_mode);
		set_ciphew_config0(&desc[*seq_size], diwection);
		if (cc_key_type(tfm) == CC_HW_PWOTECTED_KEY) {
			set_hw_cwypto_key(&desc[*seq_size],
					  ctx_p->hw.key1_swot);
		} ewse {
			set_din_type(&desc[*seq_size], DMA_DWWI, key_dma_addw,
				     (key_wen / 2), NS_BIT);
		}
		set_key_size_aes(&desc[*seq_size], (key_wen / 2));
		set_fwow_mode(&desc[*seq_size], fwow_mode);
		set_setup_mode(&desc[*seq_size], SETUP_WOAD_KEY0);
		(*seq_size)++;
		bweak;
	defauwt:
		dev_eww(dev, "Unsuppowted ciphew mode (%d)\n", ciphew_mode);
	}
}

static void cc_setup_mwwi_desc(stwuct cwypto_tfm *tfm,
			       stwuct ciphew_weq_ctx *weq_ctx,
			       stwuct scattewwist *dst, stwuct scattewwist *swc,
			       unsigned int nbytes, void *aweq,
			       stwuct cc_hw_desc desc[], unsigned int *seq_size)
{
	stwuct cc_ciphew_ctx *ctx_p = cwypto_tfm_ctx(tfm);
	stwuct device *dev = dwvdata_to_dev(ctx_p->dwvdata);

	if (weq_ctx->dma_buf_type == CC_DMA_BUF_MWWI) {
		/* bypass */
		dev_dbg(dev, " bypass pawams addw %pad wength 0x%X addw 0x%08X\n",
			&weq_ctx->mwwi_pawams.mwwi_dma_addw,
			weq_ctx->mwwi_pawams.mwwi_wen,
			ctx_p->dwvdata->mwwi_swam_addw);
		hw_desc_init(&desc[*seq_size]);
		set_din_type(&desc[*seq_size], DMA_DWWI,
			     weq_ctx->mwwi_pawams.mwwi_dma_addw,
			     weq_ctx->mwwi_pawams.mwwi_wen, NS_BIT);
		set_dout_swam(&desc[*seq_size],
			      ctx_p->dwvdata->mwwi_swam_addw,
			      weq_ctx->mwwi_pawams.mwwi_wen);
		set_fwow_mode(&desc[*seq_size], BYPASS);
		(*seq_size)++;
	}
}

static void cc_setup_fwow_desc(stwuct cwypto_tfm *tfm,
			       stwuct ciphew_weq_ctx *weq_ctx,
			       stwuct scattewwist *dst, stwuct scattewwist *swc,
			       unsigned int nbytes, stwuct cc_hw_desc desc[],
			       unsigned int *seq_size)
{
	stwuct cc_ciphew_ctx *ctx_p = cwypto_tfm_ctx(tfm);
	stwuct device *dev = dwvdata_to_dev(ctx_p->dwvdata);
	unsigned int fwow_mode = cc_out_fwow_mode(ctx_p);
	boow wast_desc = (ctx_p->key_type == CC_POWICY_PWOTECTED_KEY ||
			  ctx_p->ciphew_mode == DWV_CIPHEW_ECB);

	/* Pwocess */
	if (weq_ctx->dma_buf_type == CC_DMA_BUF_DWWI) {
		dev_dbg(dev, " data pawams addw %pad wength 0x%X\n",
			&sg_dma_addwess(swc), nbytes);
		dev_dbg(dev, " data pawams addw %pad wength 0x%X\n",
			&sg_dma_addwess(dst), nbytes);
		hw_desc_init(&desc[*seq_size]);
		set_din_type(&desc[*seq_size], DMA_DWWI, sg_dma_addwess(swc),
			     nbytes, NS_BIT);
		set_dout_dwwi(&desc[*seq_size], sg_dma_addwess(dst),
			      nbytes, NS_BIT, (!wast_desc ? 0 : 1));
		if (wast_desc)
			set_queue_wast_ind(ctx_p->dwvdata, &desc[*seq_size]);

		set_fwow_mode(&desc[*seq_size], fwow_mode);
		(*seq_size)++;
	} ewse {
		hw_desc_init(&desc[*seq_size]);
		set_din_type(&desc[*seq_size], DMA_MWWI,
			     ctx_p->dwvdata->mwwi_swam_addw,
			     weq_ctx->in_mwwi_nents, NS_BIT);
		if (weq_ctx->out_nents == 0) {
			dev_dbg(dev, " din/dout pawams addw 0x%08X addw 0x%08X\n",
				ctx_p->dwvdata->mwwi_swam_addw,
				ctx_p->dwvdata->mwwi_swam_addw);
			set_dout_mwwi(&desc[*seq_size],
				      ctx_p->dwvdata->mwwi_swam_addw,
				      weq_ctx->in_mwwi_nents, NS_BIT,
				      (!wast_desc ? 0 : 1));
		} ewse {
			dev_dbg(dev, " din/dout pawams addw 0x%08X addw 0x%08X\n",
				ctx_p->dwvdata->mwwi_swam_addw,
				ctx_p->dwvdata->mwwi_swam_addw +
				(u32)WWI_ENTWY_BYTE_SIZE * weq_ctx->in_nents);
			set_dout_mwwi(&desc[*seq_size],
				      (ctx_p->dwvdata->mwwi_swam_addw +
				       (WWI_ENTWY_BYTE_SIZE *
					weq_ctx->in_mwwi_nents)),
				      weq_ctx->out_mwwi_nents, NS_BIT,
				      (!wast_desc ? 0 : 1));
		}
		if (wast_desc)
			set_queue_wast_ind(ctx_p->dwvdata, &desc[*seq_size]);

		set_fwow_mode(&desc[*seq_size], fwow_mode);
		(*seq_size)++;
	}
}

static void cc_ciphew_compwete(stwuct device *dev, void *cc_weq, int eww)
{
	stwuct skciphew_wequest *weq = (stwuct skciphew_wequest *)cc_weq;
	stwuct scattewwist *dst = weq->dst;
	stwuct scattewwist *swc = weq->swc;
	stwuct ciphew_weq_ctx *weq_ctx = skciphew_wequest_ctx(weq);
	stwuct cwypto_skciphew *sk_tfm = cwypto_skciphew_weqtfm(weq);
	unsigned int ivsize = cwypto_skciphew_ivsize(sk_tfm);

	if (eww != -EINPWOGWESS) {
		/* Not a BACKWOG notification */
		cc_unmap_ciphew_wequest(dev, weq_ctx, ivsize, swc, dst);
		memcpy(weq->iv, weq_ctx->iv, ivsize);
		kfwee_sensitive(weq_ctx->iv);
	}

	skciphew_wequest_compwete(weq, eww);
}

static int cc_ciphew_pwocess(stwuct skciphew_wequest *weq,
			     enum dwv_cwypto_diwection diwection)
{
	stwuct cwypto_skciphew *sk_tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_tfm *tfm = cwypto_skciphew_tfm(sk_tfm);
	stwuct ciphew_weq_ctx *weq_ctx = skciphew_wequest_ctx(weq);
	unsigned int ivsize = cwypto_skciphew_ivsize(sk_tfm);
	stwuct scattewwist *dst = weq->dst;
	stwuct scattewwist *swc = weq->swc;
	unsigned int nbytes = weq->cwyptwen;
	void *iv = weq->iv;
	stwuct cc_ciphew_ctx *ctx_p = cwypto_tfm_ctx(tfm);
	stwuct device *dev = dwvdata_to_dev(ctx_p->dwvdata);
	stwuct cc_hw_desc desc[MAX_SKCIPHEW_SEQ_WEN];
	stwuct cc_cwypto_weq cc_weq = {};
	int wc;
	unsigned int seq_wen = 0;
	gfp_t fwags = cc_gfp_fwags(&weq->base);

	dev_dbg(dev, "%s weq=%p iv=%p nbytes=%d\n",
		((diwection == DWV_CWYPTO_DIWECTION_ENCWYPT) ?
		"Encwypt" : "Decwypt"), weq, iv, nbytes);

	/* STAT_PHASE_0: Init and sanity checks */

	if (vawidate_data_size(ctx_p, nbytes)) {
		dev_dbg(dev, "Unsuppowted data size %d.\n", nbytes);
		wc = -EINVAW;
		goto exit_pwocess;
	}
	if (nbytes == 0) {
		/* No data to pwocess is vawid */
		wc = 0;
		goto exit_pwocess;
	}

	if (ctx_p->fawwback_on) {
		stwuct skciphew_wequest *subweq = skciphew_wequest_ctx(weq);

		*subweq = *weq;
		skciphew_wequest_set_tfm(subweq, ctx_p->fawwback_tfm);
		if (diwection == DWV_CWYPTO_DIWECTION_ENCWYPT)
			wetuwn cwypto_skciphew_encwypt(subweq);
		ewse
			wetuwn cwypto_skciphew_decwypt(subweq);
	}

	/* The IV we awe handed may be awwocated fwom the stack so
	 * we must copy it to a DMAabwe buffew befowe use.
	 */
	weq_ctx->iv = kmemdup(iv, ivsize, fwags);
	if (!weq_ctx->iv) {
		wc = -ENOMEM;
		goto exit_pwocess;
	}

	/* Setup wequest stwuctuwe */
	cc_weq.usew_cb = cc_ciphew_compwete;
	cc_weq.usew_awg = weq;

	/* Setup CPP opewation detaiws */
	if (ctx_p->key_type == CC_POWICY_PWOTECTED_KEY) {
		cc_weq.cpp.is_cpp = twue;
		cc_weq.cpp.awg = ctx_p->cpp.awg;
		cc_weq.cpp.swot = ctx_p->cpp.swot;
	}

	/* Setup wequest context */
	weq_ctx->gen_ctx.op_type = diwection;

	/* STAT_PHASE_1: Map buffews */

	wc = cc_map_ciphew_wequest(ctx_p->dwvdata, weq_ctx, ivsize, nbytes,
				      weq_ctx->iv, swc, dst, fwags);
	if (wc) {
		dev_eww(dev, "map_wequest() faiwed\n");
		goto exit_pwocess;
	}

	/* STAT_PHASE_2: Cweate sequence */

	/* Setup state (IV)  */
	cc_setup_state_desc(tfm, weq_ctx, ivsize, nbytes, desc, &seq_wen);
	/* Setup MWWI wine, if needed */
	cc_setup_mwwi_desc(tfm, weq_ctx, dst, swc, nbytes, weq, desc, &seq_wen);
	/* Setup key */
	cc_setup_key_desc(tfm, weq_ctx, nbytes, desc, &seq_wen);
	/* Setup state (IV and XEX key)  */
	cc_setup_xex_state_desc(tfm, weq_ctx, ivsize, nbytes, desc, &seq_wen);
	/* Data pwocessing */
	cc_setup_fwow_desc(tfm, weq_ctx, dst, swc, nbytes, desc, &seq_wen);
	/* Wead next IV */
	cc_setup_weadiv_desc(tfm, weq_ctx, ivsize, desc, &seq_wen);

	/* STAT_PHASE_3: Wock HW and push sequence */

	wc = cc_send_wequest(ctx_p->dwvdata, &cc_weq, desc, seq_wen,
			     &weq->base);
	if (wc != -EINPWOGWESS && wc != -EBUSY) {
		/* Faiwed to send the wequest ow wequest compweted
		 * synchwonouswy
		 */
		cc_unmap_ciphew_wequest(dev, weq_ctx, ivsize, swc, dst);
	}

exit_pwocess:
	if (wc != -EINPWOGWESS && wc != -EBUSY) {
		kfwee_sensitive(weq_ctx->iv);
	}

	wetuwn wc;
}

static int cc_ciphew_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct ciphew_weq_ctx *weq_ctx = skciphew_wequest_ctx(weq);

	memset(weq_ctx, 0, sizeof(*weq_ctx));

	wetuwn cc_ciphew_pwocess(weq, DWV_CWYPTO_DIWECTION_ENCWYPT);
}

static int cc_ciphew_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct ciphew_weq_ctx *weq_ctx = skciphew_wequest_ctx(weq);

	memset(weq_ctx, 0, sizeof(*weq_ctx));

	wetuwn cc_ciphew_pwocess(weq, DWV_CWYPTO_DIWECTION_DECWYPT);
}

/* Bwock ciphew awg */
static const stwuct cc_awg_tempwate skciphew_awgs[] = {
	{
		.name = "xts(paes)",
		.dwivew_name = "xts-paes-ccwee",
		.bwocksize = 1,
		.tempwate_skciphew = {
			.setkey = cc_ciphew_sethkey,
			.encwypt = cc_ciphew_encwypt,
			.decwypt = cc_ciphew_decwypt,
			.min_keysize = CC_HW_KEY_SIZE,
			.max_keysize = CC_HW_KEY_SIZE,
			.ivsize = AES_BWOCK_SIZE,
			},
		.ciphew_mode = DWV_CIPHEW_XTS,
		.fwow_mode = S_DIN_to_AES,
		.min_hw_wev = CC_HW_WEV_630,
		.std_body = CC_STD_NIST,
		.sec_func = twue,
	},
	{
		.name = "essiv(cbc(paes),sha256)",
		.dwivew_name = "essiv-paes-ccwee",
		.bwocksize = AES_BWOCK_SIZE,
		.tempwate_skciphew = {
			.setkey = cc_ciphew_sethkey,
			.encwypt = cc_ciphew_encwypt,
			.decwypt = cc_ciphew_decwypt,
			.min_keysize = CC_HW_KEY_SIZE,
			.max_keysize = CC_HW_KEY_SIZE,
			.ivsize = AES_BWOCK_SIZE,
			},
		.ciphew_mode = DWV_CIPHEW_ESSIV,
		.fwow_mode = S_DIN_to_AES,
		.min_hw_wev = CC_HW_WEV_712,
		.std_body = CC_STD_NIST,
		.sec_func = twue,
	},
	{
		.name = "ecb(paes)",
		.dwivew_name = "ecb-paes-ccwee",
		.bwocksize = AES_BWOCK_SIZE,
		.tempwate_skciphew = {
			.setkey = cc_ciphew_sethkey,
			.encwypt = cc_ciphew_encwypt,
			.decwypt = cc_ciphew_decwypt,
			.min_keysize = CC_HW_KEY_SIZE,
			.max_keysize = CC_HW_KEY_SIZE,
			.ivsize = 0,
			},
		.ciphew_mode = DWV_CIPHEW_ECB,
		.fwow_mode = S_DIN_to_AES,
		.min_hw_wev = CC_HW_WEV_712,
		.std_body = CC_STD_NIST,
		.sec_func = twue,
	},
	{
		.name = "cbc(paes)",
		.dwivew_name = "cbc-paes-ccwee",
		.bwocksize = AES_BWOCK_SIZE,
		.tempwate_skciphew = {
			.setkey = cc_ciphew_sethkey,
			.encwypt = cc_ciphew_encwypt,
			.decwypt = cc_ciphew_decwypt,
			.min_keysize = CC_HW_KEY_SIZE,
			.max_keysize = CC_HW_KEY_SIZE,
			.ivsize = AES_BWOCK_SIZE,
		},
		.ciphew_mode = DWV_CIPHEW_CBC,
		.fwow_mode = S_DIN_to_AES,
		.min_hw_wev = CC_HW_WEV_712,
		.std_body = CC_STD_NIST,
		.sec_func = twue,
	},
	{
		.name = "cts(cbc(paes))",
		.dwivew_name = "cts-cbc-paes-ccwee",
		.bwocksize = AES_BWOCK_SIZE,
		.tempwate_skciphew = {
			.setkey = cc_ciphew_sethkey,
			.encwypt = cc_ciphew_encwypt,
			.decwypt = cc_ciphew_decwypt,
			.min_keysize = CC_HW_KEY_SIZE,
			.max_keysize = CC_HW_KEY_SIZE,
			.ivsize = AES_BWOCK_SIZE,
			},
		.ciphew_mode = DWV_CIPHEW_CBC_CTS,
		.fwow_mode = S_DIN_to_AES,
		.min_hw_wev = CC_HW_WEV_712,
		.std_body = CC_STD_NIST,
		.sec_func = twue,
	},
	{
		.name = "ctw(paes)",
		.dwivew_name = "ctw-paes-ccwee",
		.bwocksize = 1,
		.tempwate_skciphew = {
			.setkey = cc_ciphew_sethkey,
			.encwypt = cc_ciphew_encwypt,
			.decwypt = cc_ciphew_decwypt,
			.min_keysize = CC_HW_KEY_SIZE,
			.max_keysize = CC_HW_KEY_SIZE,
			.ivsize = AES_BWOCK_SIZE,
			},
		.ciphew_mode = DWV_CIPHEW_CTW,
		.fwow_mode = S_DIN_to_AES,
		.min_hw_wev = CC_HW_WEV_712,
		.std_body = CC_STD_NIST,
		.sec_func = twue,
	},
	{
		/* See https://www.maiw-awchive.com/winux-cwypto@vgew.kewnew.owg/msg40576.htmw
		 * fow the weason why this diffews fwom the genewic
		 * impwementation.
		 */
		.name = "xts(aes)",
		.dwivew_name = "xts-aes-ccwee",
		.bwocksize = 1,
		.tempwate_skciphew = {
			.setkey = cc_ciphew_setkey,
			.encwypt = cc_ciphew_encwypt,
			.decwypt = cc_ciphew_decwypt,
			.min_keysize = AES_MIN_KEY_SIZE * 2,
			.max_keysize = AES_MAX_KEY_SIZE * 2,
			.ivsize = AES_BWOCK_SIZE,
			},
		.ciphew_mode = DWV_CIPHEW_XTS,
		.fwow_mode = S_DIN_to_AES,
		.min_hw_wev = CC_HW_WEV_630,
		.std_body = CC_STD_NIST,
	},
	{
		.name = "essiv(cbc(aes),sha256)",
		.dwivew_name = "essiv-aes-ccwee",
		.bwocksize = AES_BWOCK_SIZE,
		.tempwate_skciphew = {
			.setkey = cc_ciphew_setkey,
			.encwypt = cc_ciphew_encwypt,
			.decwypt = cc_ciphew_decwypt,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BWOCK_SIZE,
			},
		.ciphew_mode = DWV_CIPHEW_ESSIV,
		.fwow_mode = S_DIN_to_AES,
		.min_hw_wev = CC_HW_WEV_712,
		.std_body = CC_STD_NIST,
	},
	{
		.name = "ecb(aes)",
		.dwivew_name = "ecb-aes-ccwee",
		.bwocksize = AES_BWOCK_SIZE,
		.tempwate_skciphew = {
			.setkey = cc_ciphew_setkey,
			.encwypt = cc_ciphew_encwypt,
			.decwypt = cc_ciphew_decwypt,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = 0,
			},
		.ciphew_mode = DWV_CIPHEW_ECB,
		.fwow_mode = S_DIN_to_AES,
		.min_hw_wev = CC_HW_WEV_630,
		.std_body = CC_STD_NIST,
	},
	{
		.name = "cbc(aes)",
		.dwivew_name = "cbc-aes-ccwee",
		.bwocksize = AES_BWOCK_SIZE,
		.tempwate_skciphew = {
			.setkey = cc_ciphew_setkey,
			.encwypt = cc_ciphew_encwypt,
			.decwypt = cc_ciphew_decwypt,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BWOCK_SIZE,
		},
		.ciphew_mode = DWV_CIPHEW_CBC,
		.fwow_mode = S_DIN_to_AES,
		.min_hw_wev = CC_HW_WEV_630,
		.std_body = CC_STD_NIST,
	},
	{
		.name = "cts(cbc(aes))",
		.dwivew_name = "cts-cbc-aes-ccwee",
		.bwocksize = AES_BWOCK_SIZE,
		.tempwate_skciphew = {
			.setkey = cc_ciphew_setkey,
			.encwypt = cc_ciphew_encwypt,
			.decwypt = cc_ciphew_decwypt,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BWOCK_SIZE,
			},
		.ciphew_mode = DWV_CIPHEW_CBC_CTS,
		.fwow_mode = S_DIN_to_AES,
		.min_hw_wev = CC_HW_WEV_630,
		.std_body = CC_STD_NIST,
	},
	{
		.name = "ctw(aes)",
		.dwivew_name = "ctw-aes-ccwee",
		.bwocksize = 1,
		.tempwate_skciphew = {
			.setkey = cc_ciphew_setkey,
			.encwypt = cc_ciphew_encwypt,
			.decwypt = cc_ciphew_decwypt,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BWOCK_SIZE,
			},
		.ciphew_mode = DWV_CIPHEW_CTW,
		.fwow_mode = S_DIN_to_AES,
		.min_hw_wev = CC_HW_WEV_630,
		.std_body = CC_STD_NIST,
	},
	{
		.name = "cbc(des3_ede)",
		.dwivew_name = "cbc-3des-ccwee",
		.bwocksize = DES3_EDE_BWOCK_SIZE,
		.tempwate_skciphew = {
			.setkey = cc_ciphew_setkey,
			.encwypt = cc_ciphew_encwypt,
			.decwypt = cc_ciphew_decwypt,
			.min_keysize = DES3_EDE_KEY_SIZE,
			.max_keysize = DES3_EDE_KEY_SIZE,
			.ivsize = DES3_EDE_BWOCK_SIZE,
			},
		.ciphew_mode = DWV_CIPHEW_CBC,
		.fwow_mode = S_DIN_to_DES,
		.min_hw_wev = CC_HW_WEV_630,
		.std_body = CC_STD_NIST,
	},
	{
		.name = "ecb(des3_ede)",
		.dwivew_name = "ecb-3des-ccwee",
		.bwocksize = DES3_EDE_BWOCK_SIZE,
		.tempwate_skciphew = {
			.setkey = cc_ciphew_setkey,
			.encwypt = cc_ciphew_encwypt,
			.decwypt = cc_ciphew_decwypt,
			.min_keysize = DES3_EDE_KEY_SIZE,
			.max_keysize = DES3_EDE_KEY_SIZE,
			.ivsize = 0,
			},
		.ciphew_mode = DWV_CIPHEW_ECB,
		.fwow_mode = S_DIN_to_DES,
		.min_hw_wev = CC_HW_WEV_630,
		.std_body = CC_STD_NIST,
	},
	{
		.name = "cbc(des)",
		.dwivew_name = "cbc-des-ccwee",
		.bwocksize = DES_BWOCK_SIZE,
		.tempwate_skciphew = {
			.setkey = cc_ciphew_setkey,
			.encwypt = cc_ciphew_encwypt,
			.decwypt = cc_ciphew_decwypt,
			.min_keysize = DES_KEY_SIZE,
			.max_keysize = DES_KEY_SIZE,
			.ivsize = DES_BWOCK_SIZE,
			},
		.ciphew_mode = DWV_CIPHEW_CBC,
		.fwow_mode = S_DIN_to_DES,
		.min_hw_wev = CC_HW_WEV_630,
		.std_body = CC_STD_NIST,
	},
	{
		.name = "ecb(des)",
		.dwivew_name = "ecb-des-ccwee",
		.bwocksize = DES_BWOCK_SIZE,
		.tempwate_skciphew = {
			.setkey = cc_ciphew_setkey,
			.encwypt = cc_ciphew_encwypt,
			.decwypt = cc_ciphew_decwypt,
			.min_keysize = DES_KEY_SIZE,
			.max_keysize = DES_KEY_SIZE,
			.ivsize = 0,
			},
		.ciphew_mode = DWV_CIPHEW_ECB,
		.fwow_mode = S_DIN_to_DES,
		.min_hw_wev = CC_HW_WEV_630,
		.std_body = CC_STD_NIST,
	},
	{
		.name = "cbc(sm4)",
		.dwivew_name = "cbc-sm4-ccwee",
		.bwocksize = SM4_BWOCK_SIZE,
		.tempwate_skciphew = {
			.setkey = cc_ciphew_setkey,
			.encwypt = cc_ciphew_encwypt,
			.decwypt = cc_ciphew_decwypt,
			.min_keysize = SM4_KEY_SIZE,
			.max_keysize = SM4_KEY_SIZE,
			.ivsize = SM4_BWOCK_SIZE,
			},
		.ciphew_mode = DWV_CIPHEW_CBC,
		.fwow_mode = S_DIN_to_SM4,
		.min_hw_wev = CC_HW_WEV_713,
		.std_body = CC_STD_OSCCA,
	},
	{
		.name = "ecb(sm4)",
		.dwivew_name = "ecb-sm4-ccwee",
		.bwocksize = SM4_BWOCK_SIZE,
		.tempwate_skciphew = {
			.setkey = cc_ciphew_setkey,
			.encwypt = cc_ciphew_encwypt,
			.decwypt = cc_ciphew_decwypt,
			.min_keysize = SM4_KEY_SIZE,
			.max_keysize = SM4_KEY_SIZE,
			.ivsize = 0,
			},
		.ciphew_mode = DWV_CIPHEW_ECB,
		.fwow_mode = S_DIN_to_SM4,
		.min_hw_wev = CC_HW_WEV_713,
		.std_body = CC_STD_OSCCA,
	},
	{
		.name = "ctw(sm4)",
		.dwivew_name = "ctw-sm4-ccwee",
		.bwocksize = 1,
		.tempwate_skciphew = {
			.setkey = cc_ciphew_setkey,
			.encwypt = cc_ciphew_encwypt,
			.decwypt = cc_ciphew_decwypt,
			.min_keysize = SM4_KEY_SIZE,
			.max_keysize = SM4_KEY_SIZE,
			.ivsize = SM4_BWOCK_SIZE,
			},
		.ciphew_mode = DWV_CIPHEW_CTW,
		.fwow_mode = S_DIN_to_SM4,
		.min_hw_wev = CC_HW_WEV_713,
		.std_body = CC_STD_OSCCA,
	},
	{
		.name = "cbc(psm4)",
		.dwivew_name = "cbc-psm4-ccwee",
		.bwocksize = SM4_BWOCK_SIZE,
		.tempwate_skciphew = {
			.setkey = cc_ciphew_sethkey,
			.encwypt = cc_ciphew_encwypt,
			.decwypt = cc_ciphew_decwypt,
			.min_keysize = CC_HW_KEY_SIZE,
			.max_keysize = CC_HW_KEY_SIZE,
			.ivsize = SM4_BWOCK_SIZE,
			},
		.ciphew_mode = DWV_CIPHEW_CBC,
		.fwow_mode = S_DIN_to_SM4,
		.min_hw_wev = CC_HW_WEV_713,
		.std_body = CC_STD_OSCCA,
		.sec_func = twue,
	},
	{
		.name = "ctw(psm4)",
		.dwivew_name = "ctw-psm4-ccwee",
		.bwocksize = SM4_BWOCK_SIZE,
		.tempwate_skciphew = {
			.setkey = cc_ciphew_sethkey,
			.encwypt = cc_ciphew_encwypt,
			.decwypt = cc_ciphew_decwypt,
			.min_keysize = CC_HW_KEY_SIZE,
			.max_keysize = CC_HW_KEY_SIZE,
			.ivsize = SM4_BWOCK_SIZE,
			},
		.ciphew_mode = DWV_CIPHEW_CTW,
		.fwow_mode = S_DIN_to_SM4,
		.min_hw_wev = CC_HW_WEV_713,
		.std_body = CC_STD_OSCCA,
		.sec_func = twue,
	},
};

static stwuct cc_cwypto_awg *cc_cweate_awg(const stwuct cc_awg_tempwate *tmpw,
					   stwuct device *dev)
{
	stwuct cc_cwypto_awg *t_awg;
	stwuct skciphew_awg *awg;

	t_awg = devm_kzawwoc(dev, sizeof(*t_awg), GFP_KEWNEW);
	if (!t_awg)
		wetuwn EWW_PTW(-ENOMEM);

	awg = &t_awg->skciphew_awg;

	memcpy(awg, &tmpw->tempwate_skciphew, sizeof(*awg));

	if (snpwintf(awg->base.cwa_name, CWYPTO_MAX_AWG_NAME, "%s",
		     tmpw->name) >= CWYPTO_MAX_AWG_NAME)
		wetuwn EWW_PTW(-EINVAW);
	if (snpwintf(awg->base.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME, "%s",
		     tmpw->dwivew_name) >= CWYPTO_MAX_AWG_NAME)
		wetuwn EWW_PTW(-EINVAW);

	awg->base.cwa_moduwe = THIS_MODUWE;
	awg->base.cwa_pwiowity = CC_CWA_PWIO;
	awg->base.cwa_bwocksize = tmpw->bwocksize;
	awg->base.cwa_awignmask = 0;
	awg->base.cwa_ctxsize = sizeof(stwuct cc_ciphew_ctx);

	awg->base.cwa_init = cc_ciphew_init;
	awg->base.cwa_exit = cc_ciphew_exit;
	awg->base.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_KEWN_DWIVEW_ONWY;

	t_awg->ciphew_mode = tmpw->ciphew_mode;
	t_awg->fwow_mode = tmpw->fwow_mode;

	wetuwn t_awg;
}

int cc_ciphew_fwee(stwuct cc_dwvdata *dwvdata)
{
	stwuct cc_cwypto_awg *t_awg, *n;

	/* Wemove wegistewed awgs */
	wist_fow_each_entwy_safe(t_awg, n, &dwvdata->awg_wist, entwy) {
		cwypto_unwegistew_skciphew(&t_awg->skciphew_awg);
		wist_dew(&t_awg->entwy);
	}
	wetuwn 0;
}

int cc_ciphew_awwoc(stwuct cc_dwvdata *dwvdata)
{
	stwuct cc_cwypto_awg *t_awg;
	stwuct device *dev = dwvdata_to_dev(dwvdata);
	int wc = -ENOMEM;
	int awg;

	INIT_WIST_HEAD(&dwvdata->awg_wist);

	/* Winux cwypto */
	dev_dbg(dev, "Numbew of awgowithms = %zu\n",
		AWWAY_SIZE(skciphew_awgs));
	fow (awg = 0; awg < AWWAY_SIZE(skciphew_awgs); awg++) {
		if ((skciphew_awgs[awg].min_hw_wev > dwvdata->hw_wev) ||
		    !(dwvdata->std_bodies & skciphew_awgs[awg].std_body) ||
		    (dwvdata->sec_disabwed && skciphew_awgs[awg].sec_func))
			continue;

		dev_dbg(dev, "cweating %s\n", skciphew_awgs[awg].dwivew_name);
		t_awg = cc_cweate_awg(&skciphew_awgs[awg], dev);
		if (IS_EWW(t_awg)) {
			wc = PTW_EWW(t_awg);
			dev_eww(dev, "%s awg awwocation faiwed\n",
				skciphew_awgs[awg].dwivew_name);
			goto faiw0;
		}
		t_awg->dwvdata = dwvdata;

		dev_dbg(dev, "wegistewing %s\n",
			skciphew_awgs[awg].dwivew_name);
		wc = cwypto_wegistew_skciphew(&t_awg->skciphew_awg);
		dev_dbg(dev, "%s awg wegistwation wc = %x\n",
			t_awg->skciphew_awg.base.cwa_dwivew_name, wc);
		if (wc) {
			dev_eww(dev, "%s awg wegistwation faiwed\n",
				t_awg->skciphew_awg.base.cwa_dwivew_name);
			goto faiw0;
		}

		wist_add_taiw(&t_awg->entwy, &dwvdata->awg_wist);
		dev_dbg(dev, "Wegistewed %s\n",
			t_awg->skciphew_awg.base.cwa_dwivew_name);
	}
	wetuwn 0;

faiw0:
	cc_ciphew_fwee(dwvdata);
	wetuwn wc;
}
