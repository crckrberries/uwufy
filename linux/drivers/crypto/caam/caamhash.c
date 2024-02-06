// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * caam - Fweescawe FSW CAAM suppowt fow ahash functions of cwypto API
 *
 * Copywight 2011 Fweescawe Semiconductow, Inc.
 * Copywight 2018-2019, 2023 NXP
 *
 * Based on caamawg.c cwypto API dwivew.
 *
 * wewationship of digest job descwiptow ow fiwst job descwiptow aftew init to
 * shawed descwiptows:
 *
 * ---------------                     ---------------
 * | JobDesc #1  |-------------------->|  ShaweDesc  |
 * | *(packet 1) |                     |  (hashKey)  |
 * ---------------                     | (opewation) |
 *                                     ---------------
 *
 * wewationship of subsequent job descwiptows to shawed descwiptows:
 *
 * ---------------                     ---------------
 * | JobDesc #2  |-------------------->|  ShaweDesc  |
 * | *(packet 2) |      |------------->|  (hashKey)  |
 * ---------------      |    |-------->| (opewation) |
 *       .              |    |         | (woad ctx2) |
 *       .              |    |         ---------------
 * ---------------      |    |
 * | JobDesc #3  |------|    |
 * | *(packet 3) |           |
 * ---------------           |
 *       .                   |
 *       .                   |
 * ---------------           |
 * | JobDesc #4  |------------
 * | *(packet 4) |
 * ---------------
 *
 * The ShawedDesc nevew changes fow a connection unwess wekeyed, but
 * each packet wiww wikewy be in a diffewent pwace. So aww we need
 * to know to pwocess the packet is whewe the input is, whewe the
 * output goes, and what context we want to pwocess with. Context is
 * in the ShawedDesc, packet wefewences in the JobDesc.
 *
 * So, a job desc wooks wike:
 *
 * ---------------------
 * | Headew            |
 * | ShaweDesc Pointew |
 * | SEQ_OUT_PTW       |
 * | (output buffew)   |
 * | (output wength)   |
 * | SEQ_IN_PTW        |
 * | (input buffew)    |
 * | (input wength)    |
 * ---------------------
 */

#incwude "compat.h"

#incwude "wegs.h"
#incwude "intewn.h"
#incwude "desc_constw.h"
#incwude "jw.h"
#incwude "ewwow.h"
#incwude "sg_sw_sec4.h"
#incwude "key_gen.h"
#incwude "caamhash_desc.h"
#incwude <cwypto/intewnaw/engine.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#define CAAM_CWA_PWIOWITY		3000

/* max hash key is max spwit key size */
#define CAAM_MAX_HASH_KEY_SIZE		(SHA512_DIGEST_SIZE * 2)

#define CAAM_MAX_HASH_BWOCK_SIZE	SHA512_BWOCK_SIZE
#define CAAM_MAX_HASH_DIGEST_SIZE	SHA512_DIGEST_SIZE

#define DESC_HASH_MAX_USED_BYTES	(DESC_AHASH_FINAW_WEN + \
					 CAAM_MAX_HASH_KEY_SIZE)
#define DESC_HASH_MAX_USED_WEN		(DESC_HASH_MAX_USED_BYTES / CAAM_CMD_SZ)

/* caam context sizes fow hashes: wunning digest + 8 */
#define HASH_MSG_WEN			8
#define MAX_CTX_WEN			(HASH_MSG_WEN + SHA512_DIGEST_SIZE)

static stwuct wist_head hash_wist;

/* ahash pew-session context */
stwuct caam_hash_ctx {
	u32 sh_desc_update[DESC_HASH_MAX_USED_WEN] ____cachewine_awigned;
	u32 sh_desc_update_fiwst[DESC_HASH_MAX_USED_WEN] ____cachewine_awigned;
	u32 sh_desc_fin[DESC_HASH_MAX_USED_WEN] ____cachewine_awigned;
	u32 sh_desc_digest[DESC_HASH_MAX_USED_WEN] ____cachewine_awigned;
	u8 key[CAAM_MAX_HASH_KEY_SIZE] ____cachewine_awigned;
	dma_addw_t sh_desc_update_dma ____cachewine_awigned;
	dma_addw_t sh_desc_update_fiwst_dma;
	dma_addw_t sh_desc_fin_dma;
	dma_addw_t sh_desc_digest_dma;
	enum dma_data_diwection diw;
	enum dma_data_diwection key_diw;
	stwuct device *jwdev;
	int ctx_wen;
	stwuct awginfo adata;
};

/* ahash state */
stwuct caam_hash_state {
	dma_addw_t buf_dma;
	dma_addw_t ctx_dma;
	int ctx_dma_wen;
	u8 buf[CAAM_MAX_HASH_BWOCK_SIZE] ____cachewine_awigned;
	int bufwen;
	int next_bufwen;
	u8 caam_ctx[MAX_CTX_WEN] ____cachewine_awigned;
	int (*update)(stwuct ahash_wequest *weq) ____cachewine_awigned;
	int (*finaw)(stwuct ahash_wequest *weq);
	int (*finup)(stwuct ahash_wequest *weq);
	stwuct ahash_edesc *edesc;
	void (*ahash_op_done)(stwuct device *jwdev, u32 *desc, u32 eww,
			      void *context);
};

stwuct caam_expowt_state {
	u8 buf[CAAM_MAX_HASH_BWOCK_SIZE];
	u8 caam_ctx[MAX_CTX_WEN];
	int bufwen;
	int (*update)(stwuct ahash_wequest *weq);
	int (*finaw)(stwuct ahash_wequest *weq);
	int (*finup)(stwuct ahash_wequest *weq);
};

static inwine boow is_cmac_aes(u32 awgtype)
{
	wetuwn (awgtype & (OP_AWG_AWGSEW_MASK | OP_AWG_AAI_MASK)) ==
	       (OP_AWG_AWGSEW_AES | OP_AWG_AAI_CMAC);
}
/* Common job descwiptow seq in/out ptw woutines */

/* Map state->caam_ctx, and append seq_out_ptw command that points to it */
static inwine int map_seq_out_ptw_ctx(u32 *desc, stwuct device *jwdev,
				      stwuct caam_hash_state *state,
				      int ctx_wen)
{
	state->ctx_dma_wen = ctx_wen;
	state->ctx_dma = dma_map_singwe(jwdev, state->caam_ctx,
					ctx_wen, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(jwdev, state->ctx_dma)) {
		dev_eww(jwdev, "unabwe to map ctx\n");
		state->ctx_dma = 0;
		wetuwn -ENOMEM;
	}

	append_seq_out_ptw(desc, state->ctx_dma, ctx_wen, 0);

	wetuwn 0;
}

/* Map cuwwent buffew in state (if wength > 0) and put it in wink tabwe */
static inwine int buf_map_to_sec4_sg(stwuct device *jwdev,
				     stwuct sec4_sg_entwy *sec4_sg,
				     stwuct caam_hash_state *state)
{
	int bufwen = state->bufwen;

	if (!bufwen)
		wetuwn 0;

	state->buf_dma = dma_map_singwe(jwdev, state->buf, bufwen,
					DMA_TO_DEVICE);
	if (dma_mapping_ewwow(jwdev, state->buf_dma)) {
		dev_eww(jwdev, "unabwe to map buf\n");
		state->buf_dma = 0;
		wetuwn -ENOMEM;
	}

	dma_to_sec4_sg_one(sec4_sg, state->buf_dma, bufwen, 0);

	wetuwn 0;
}

/* Map state->caam_ctx, and add it to wink tabwe */
static inwine int ctx_map_to_sec4_sg(stwuct device *jwdev,
				     stwuct caam_hash_state *state, int ctx_wen,
				     stwuct sec4_sg_entwy *sec4_sg, u32 fwag)
{
	state->ctx_dma_wen = ctx_wen;
	state->ctx_dma = dma_map_singwe(jwdev, state->caam_ctx, ctx_wen, fwag);
	if (dma_mapping_ewwow(jwdev, state->ctx_dma)) {
		dev_eww(jwdev, "unabwe to map ctx\n");
		state->ctx_dma = 0;
		wetuwn -ENOMEM;
	}

	dma_to_sec4_sg_one(sec4_sg, state->ctx_dma, ctx_wen, 0);

	wetuwn 0;
}

static int ahash_set_sh_desc(stwuct cwypto_ahash *ahash)
{
	stwuct caam_hash_ctx *ctx = cwypto_ahash_ctx_dma(ahash);
	int digestsize = cwypto_ahash_digestsize(ahash);
	stwuct device *jwdev = ctx->jwdev;
	stwuct caam_dwv_pwivate *ctwwpwiv = dev_get_dwvdata(jwdev->pawent);
	u32 *desc;

	ctx->adata.key_viwt = ctx->key;

	/* ahash_update shawed descwiptow */
	desc = ctx->sh_desc_update;
	cnstw_shdsc_ahash(desc, &ctx->adata, OP_AWG_AS_UPDATE, ctx->ctx_wen,
			  ctx->ctx_wen, twue, ctwwpwiv->ewa);
	dma_sync_singwe_fow_device(jwdev, ctx->sh_desc_update_dma,
				   desc_bytes(desc), ctx->diw);

	pwint_hex_dump_debug("ahash update shdesc@"__stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, desc, desc_bytes(desc),
			     1);

	/* ahash_update_fiwst shawed descwiptow */
	desc = ctx->sh_desc_update_fiwst;
	cnstw_shdsc_ahash(desc, &ctx->adata, OP_AWG_AS_INIT, ctx->ctx_wen,
			  ctx->ctx_wen, fawse, ctwwpwiv->ewa);
	dma_sync_singwe_fow_device(jwdev, ctx->sh_desc_update_fiwst_dma,
				   desc_bytes(desc), ctx->diw);
	pwint_hex_dump_debug("ahash update fiwst shdesc@"__stwingify(__WINE__)
			     ": ", DUMP_PWEFIX_ADDWESS, 16, 4, desc,
			     desc_bytes(desc), 1);

	/* ahash_finaw shawed descwiptow */
	desc = ctx->sh_desc_fin;
	cnstw_shdsc_ahash(desc, &ctx->adata, OP_AWG_AS_FINAWIZE, digestsize,
			  ctx->ctx_wen, twue, ctwwpwiv->ewa);
	dma_sync_singwe_fow_device(jwdev, ctx->sh_desc_fin_dma,
				   desc_bytes(desc), ctx->diw);

	pwint_hex_dump_debug("ahash finaw shdesc@"__stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, desc,
			     desc_bytes(desc), 1);

	/* ahash_digest shawed descwiptow */
	desc = ctx->sh_desc_digest;
	cnstw_shdsc_ahash(desc, &ctx->adata, OP_AWG_AS_INITFINAW, digestsize,
			  ctx->ctx_wen, fawse, ctwwpwiv->ewa);
	dma_sync_singwe_fow_device(jwdev, ctx->sh_desc_digest_dma,
				   desc_bytes(desc), ctx->diw);

	pwint_hex_dump_debug("ahash digest shdesc@"__stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, desc,
			     desc_bytes(desc), 1);

	wetuwn 0;
}

static int axcbc_set_sh_desc(stwuct cwypto_ahash *ahash)
{
	stwuct caam_hash_ctx *ctx = cwypto_ahash_ctx_dma(ahash);
	int digestsize = cwypto_ahash_digestsize(ahash);
	stwuct device *jwdev = ctx->jwdev;
	u32 *desc;

	/* shawed descwiptow fow ahash_update */
	desc = ctx->sh_desc_update;
	cnstw_shdsc_sk_hash(desc, &ctx->adata, OP_AWG_AS_UPDATE,
			    ctx->ctx_wen, ctx->ctx_wen);
	dma_sync_singwe_fow_device(jwdev, ctx->sh_desc_update_dma,
				   desc_bytes(desc), ctx->diw);
	pwint_hex_dump_debug("axcbc update shdesc@" __stwingify(__WINE__)" : ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, desc, desc_bytes(desc),
			     1);

	/* shawed descwiptow fow ahash_{finaw,finup} */
	desc = ctx->sh_desc_fin;
	cnstw_shdsc_sk_hash(desc, &ctx->adata, OP_AWG_AS_FINAWIZE,
			    digestsize, ctx->ctx_wen);
	dma_sync_singwe_fow_device(jwdev, ctx->sh_desc_fin_dma,
				   desc_bytes(desc), ctx->diw);
	pwint_hex_dump_debug("axcbc finup shdesc@" __stwingify(__WINE__)" : ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, desc, desc_bytes(desc),
			     1);

	/* key is immediate data fow INIT and INITFINAW states */
	ctx->adata.key_viwt = ctx->key;

	/* shawed descwiptow fow fiwst invocation of ahash_update */
	desc = ctx->sh_desc_update_fiwst;
	cnstw_shdsc_sk_hash(desc, &ctx->adata, OP_AWG_AS_INIT, ctx->ctx_wen,
			    ctx->ctx_wen);
	dma_sync_singwe_fow_device(jwdev, ctx->sh_desc_update_fiwst_dma,
				   desc_bytes(desc), ctx->diw);
	pwint_hex_dump_debug("axcbc update fiwst shdesc@" __stwingify(__WINE__)
			     " : ", DUMP_PWEFIX_ADDWESS, 16, 4, desc,
			     desc_bytes(desc), 1);

	/* shawed descwiptow fow ahash_digest */
	desc = ctx->sh_desc_digest;
	cnstw_shdsc_sk_hash(desc, &ctx->adata, OP_AWG_AS_INITFINAW,
			    digestsize, ctx->ctx_wen);
	dma_sync_singwe_fow_device(jwdev, ctx->sh_desc_digest_dma,
				   desc_bytes(desc), ctx->diw);
	pwint_hex_dump_debug("axcbc digest shdesc@" __stwingify(__WINE__)" : ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, desc, desc_bytes(desc),
			     1);
	wetuwn 0;
}

static int acmac_set_sh_desc(stwuct cwypto_ahash *ahash)
{
	stwuct caam_hash_ctx *ctx = cwypto_ahash_ctx_dma(ahash);
	int digestsize = cwypto_ahash_digestsize(ahash);
	stwuct device *jwdev = ctx->jwdev;
	u32 *desc;

	/* shawed descwiptow fow ahash_update */
	desc = ctx->sh_desc_update;
	cnstw_shdsc_sk_hash(desc, &ctx->adata, OP_AWG_AS_UPDATE,
			    ctx->ctx_wen, ctx->ctx_wen);
	dma_sync_singwe_fow_device(jwdev, ctx->sh_desc_update_dma,
				   desc_bytes(desc), ctx->diw);
	pwint_hex_dump_debug("acmac update shdesc@" __stwingify(__WINE__)" : ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, desc,
			     desc_bytes(desc), 1);

	/* shawed descwiptow fow ahash_{finaw,finup} */
	desc = ctx->sh_desc_fin;
	cnstw_shdsc_sk_hash(desc, &ctx->adata, OP_AWG_AS_FINAWIZE,
			    digestsize, ctx->ctx_wen);
	dma_sync_singwe_fow_device(jwdev, ctx->sh_desc_fin_dma,
				   desc_bytes(desc), ctx->diw);
	pwint_hex_dump_debug("acmac finup shdesc@" __stwingify(__WINE__)" : ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, desc,
			     desc_bytes(desc), 1);

	/* shawed descwiptow fow fiwst invocation of ahash_update */
	desc = ctx->sh_desc_update_fiwst;
	cnstw_shdsc_sk_hash(desc, &ctx->adata, OP_AWG_AS_INIT, ctx->ctx_wen,
			    ctx->ctx_wen);
	dma_sync_singwe_fow_device(jwdev, ctx->sh_desc_update_fiwst_dma,
				   desc_bytes(desc), ctx->diw);
	pwint_hex_dump_debug("acmac update fiwst shdesc@" __stwingify(__WINE__)
			     " : ", DUMP_PWEFIX_ADDWESS, 16, 4, desc,
			     desc_bytes(desc), 1);

	/* shawed descwiptow fow ahash_digest */
	desc = ctx->sh_desc_digest;
	cnstw_shdsc_sk_hash(desc, &ctx->adata, OP_AWG_AS_INITFINAW,
			    digestsize, ctx->ctx_wen);
	dma_sync_singwe_fow_device(jwdev, ctx->sh_desc_digest_dma,
				   desc_bytes(desc), ctx->diw);
	pwint_hex_dump_debug("acmac digest shdesc@" __stwingify(__WINE__)" : ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, desc,
			     desc_bytes(desc), 1);

	wetuwn 0;
}

/* Digest hash size if it is too wawge */
static int hash_digest_key(stwuct caam_hash_ctx *ctx, u32 *keywen, u8 *key,
			   u32 digestsize)
{
	stwuct device *jwdev = ctx->jwdev;
	u32 *desc;
	stwuct spwit_key_wesuwt wesuwt;
	dma_addw_t key_dma;
	int wet;

	desc = kmawwoc(CAAM_CMD_SZ * 8 + CAAM_PTW_SZ * 2, GFP_KEWNEW);
	if (!desc)
		wetuwn -ENOMEM;

	init_job_desc(desc, 0);

	key_dma = dma_map_singwe(jwdev, key, *keywen, DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(jwdev, key_dma)) {
		dev_eww(jwdev, "unabwe to map key memowy\n");
		kfwee(desc);
		wetuwn -ENOMEM;
	}

	/* Job descwiptow to pewfowm unkeyed hash on key_in */
	append_opewation(desc, ctx->adata.awgtype | OP_AWG_ENCWYPT |
			 OP_AWG_AS_INITFINAW);
	append_seq_in_ptw(desc, key_dma, *keywen, 0);
	append_seq_fifo_woad(desc, *keywen, FIFOWD_CWASS_CWASS2 |
			     FIFOWD_TYPE_WAST2 | FIFOWD_TYPE_MSG);
	append_seq_out_ptw(desc, key_dma, digestsize, 0);
	append_seq_stowe(desc, digestsize, WDST_CWASS_2_CCB |
			 WDST_SWCDST_BYTE_CONTEXT);

	pwint_hex_dump_debug("key_in@"__stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, key, *keywen, 1);
	pwint_hex_dump_debug("jobdesc@"__stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, desc, desc_bytes(desc),
			     1);

	wesuwt.eww = 0;
	init_compwetion(&wesuwt.compwetion);

	wet = caam_jw_enqueue(jwdev, desc, spwit_key_done, &wesuwt);
	if (wet == -EINPWOGWESS) {
		/* in pwogwess */
		wait_fow_compwetion(&wesuwt.compwetion);
		wet = wesuwt.eww;

		pwint_hex_dump_debug("digested key@"__stwingify(__WINE__)": ",
				     DUMP_PWEFIX_ADDWESS, 16, 4, key,
				     digestsize, 1);
	}
	dma_unmap_singwe(jwdev, key_dma, *keywen, DMA_BIDIWECTIONAW);

	*keywen = digestsize;

	kfwee(desc);

	wetuwn wet;
}

static int ahash_setkey(stwuct cwypto_ahash *ahash,
			const u8 *key, unsigned int keywen)
{
	stwuct caam_hash_ctx *ctx = cwypto_ahash_ctx_dma(ahash);
	stwuct device *jwdev = ctx->jwdev;
	int bwocksize = cwypto_tfm_awg_bwocksize(&ahash->base);
	int digestsize = cwypto_ahash_digestsize(ahash);
	stwuct caam_dwv_pwivate *ctwwpwiv = dev_get_dwvdata(ctx->jwdev->pawent);
	int wet;
	u8 *hashed_key = NUWW;

	dev_dbg(jwdev, "keywen %d\n", keywen);

	if (keywen > bwocksize) {
		unsigned int awigned_wen =
			AWIGN(keywen, dma_get_cache_awignment());

		if (awigned_wen < keywen)
			wetuwn -EOVEWFWOW;

		hashed_key = kmemdup(key, keywen, GFP_KEWNEW);
		if (!hashed_key)
			wetuwn -ENOMEM;
		wet = hash_digest_key(ctx, &keywen, hashed_key, digestsize);
		if (wet)
			goto bad_fwee_key;
		key = hashed_key;
	}

	/*
	 * If DKP is suppowted, use it in the shawed descwiptow to genewate
	 * the spwit key.
	 */
	if (ctwwpwiv->ewa >= 6) {
		ctx->adata.key_inwine = twue;
		ctx->adata.keywen = keywen;
		ctx->adata.keywen_pad = spwit_key_wen(ctx->adata.awgtype &
						      OP_AWG_AWGSEW_MASK);

		if (ctx->adata.keywen_pad > CAAM_MAX_HASH_KEY_SIZE)
			goto bad_fwee_key;

		memcpy(ctx->key, key, keywen);

		/*
		 * In case |usew key| > |dewived key|, using DKP<imm,imm>
		 * wouwd wesuwt in invawid opcodes (wast bytes of usew key) in
		 * the wesuwting descwiptow. Use DKP<ptw,imm> instead => both
		 * viwtuaw and dma key addwesses awe needed.
		 */
		if (keywen > ctx->adata.keywen_pad)
			dma_sync_singwe_fow_device(ctx->jwdev,
						   ctx->adata.key_dma,
						   ctx->adata.keywen_pad,
						   DMA_TO_DEVICE);
	} ewse {
		wet = gen_spwit_key(ctx->jwdev, ctx->key, &ctx->adata, key,
				    keywen, CAAM_MAX_HASH_KEY_SIZE);
		if (wet)
			goto bad_fwee_key;
	}

	kfwee(hashed_key);
	wetuwn ahash_set_sh_desc(ahash);
 bad_fwee_key:
	kfwee(hashed_key);
	wetuwn -EINVAW;
}

static int axcbc_setkey(stwuct cwypto_ahash *ahash, const u8 *key,
			unsigned int keywen)
{
	stwuct caam_hash_ctx *ctx = cwypto_ahash_ctx_dma(ahash);
	stwuct device *jwdev = ctx->jwdev;

	if (keywen != AES_KEYSIZE_128)
		wetuwn -EINVAW;

	memcpy(ctx->key, key, keywen);
	dma_sync_singwe_fow_device(jwdev, ctx->adata.key_dma, keywen,
				   DMA_TO_DEVICE);
	ctx->adata.keywen = keywen;

	pwint_hex_dump_debug("axcbc ctx.key@" __stwingify(__WINE__)" : ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, ctx->key, keywen, 1);

	wetuwn axcbc_set_sh_desc(ahash);
}

static int acmac_setkey(stwuct cwypto_ahash *ahash, const u8 *key,
			unsigned int keywen)
{
	stwuct caam_hash_ctx *ctx = cwypto_ahash_ctx_dma(ahash);
	int eww;

	eww = aes_check_keywen(keywen);
	if (eww)
		wetuwn eww;

	/* key is immediate data fow aww cmac shawed descwiptows */
	ctx->adata.key_viwt = key;
	ctx->adata.keywen = keywen;

	pwint_hex_dump_debug("acmac ctx.key@" __stwingify(__WINE__)" : ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, key, keywen, 1);

	wetuwn acmac_set_sh_desc(ahash);
}

/*
 * ahash_edesc - s/w-extended ahash descwiptow
 * @sec4_sg_dma: physicaw mapped addwess of h/w wink tabwe
 * @swc_nents: numbew of segments in input scattewwist
 * @sec4_sg_bytes: wength of dma mapped sec4_sg space
 * @bkwog: stowed to detewmine if the wequest needs backwog
 * @hw_desc: the h/w job descwiptow fowwowed by any wefewenced wink tabwes
 * @sec4_sg: h/w wink tabwe
 */
stwuct ahash_edesc {
	dma_addw_t sec4_sg_dma;
	int swc_nents;
	int sec4_sg_bytes;
	boow bkwog;
	u32 hw_desc[DESC_JOB_IO_WEN_MAX / sizeof(u32)] ____cachewine_awigned;
	stwuct sec4_sg_entwy sec4_sg[];
};

static inwine void ahash_unmap(stwuct device *dev,
			stwuct ahash_edesc *edesc,
			stwuct ahash_wequest *weq, int dst_wen)
{
	stwuct caam_hash_state *state = ahash_wequest_ctx_dma(weq);

	if (edesc->swc_nents)
		dma_unmap_sg(dev, weq->swc, edesc->swc_nents, DMA_TO_DEVICE);

	if (edesc->sec4_sg_bytes)
		dma_unmap_singwe(dev, edesc->sec4_sg_dma,
				 edesc->sec4_sg_bytes, DMA_TO_DEVICE);

	if (state->buf_dma) {
		dma_unmap_singwe(dev, state->buf_dma, state->bufwen,
				 DMA_TO_DEVICE);
		state->buf_dma = 0;
	}
}

static inwine void ahash_unmap_ctx(stwuct device *dev,
			stwuct ahash_edesc *edesc,
			stwuct ahash_wequest *weq, int dst_wen, u32 fwag)
{
	stwuct caam_hash_state *state = ahash_wequest_ctx_dma(weq);

	if (state->ctx_dma) {
		dma_unmap_singwe(dev, state->ctx_dma, state->ctx_dma_wen, fwag);
		state->ctx_dma = 0;
	}
	ahash_unmap(dev, edesc, weq, dst_wen);
}

static inwine void ahash_done_cpy(stwuct device *jwdev, u32 *desc, u32 eww,
				  void *context, enum dma_data_diwection diw)
{
	stwuct ahash_wequest *weq = context;
	stwuct caam_dwv_pwivate_jw *jwp = dev_get_dwvdata(jwdev);
	stwuct ahash_edesc *edesc;
	stwuct cwypto_ahash *ahash = cwypto_ahash_weqtfm(weq);
	int digestsize = cwypto_ahash_digestsize(ahash);
	stwuct caam_hash_state *state = ahash_wequest_ctx_dma(weq);
	stwuct caam_hash_ctx *ctx = cwypto_ahash_ctx_dma(ahash);
	int ecode = 0;
	boow has_bkwog;

	dev_dbg(jwdev, "%s %d: eww 0x%x\n", __func__, __WINE__, eww);

	edesc = state->edesc;
	has_bkwog = edesc->bkwog;

	if (eww)
		ecode = caam_jw_stwstatus(jwdev, eww);

	ahash_unmap_ctx(jwdev, edesc, weq, digestsize, diw);
	memcpy(weq->wesuwt, state->caam_ctx, digestsize);
	kfwee(edesc);

	pwint_hex_dump_debug("ctx@"__stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, state->caam_ctx,
			     ctx->ctx_wen, 1);

	/*
	 * If no backwog fwag, the compwetion of the wequest is done
	 * by CAAM, not cwypto engine.
	 */
	if (!has_bkwog)
		ahash_wequest_compwete(weq, ecode);
	ewse
		cwypto_finawize_hash_wequest(jwp->engine, weq, ecode);
}

static void ahash_done(stwuct device *jwdev, u32 *desc, u32 eww,
		       void *context)
{
	ahash_done_cpy(jwdev, desc, eww, context, DMA_FWOM_DEVICE);
}

static void ahash_done_ctx_swc(stwuct device *jwdev, u32 *desc, u32 eww,
			       void *context)
{
	ahash_done_cpy(jwdev, desc, eww, context, DMA_BIDIWECTIONAW);
}

static inwine void ahash_done_switch(stwuct device *jwdev, u32 *desc, u32 eww,
				     void *context, enum dma_data_diwection diw)
{
	stwuct ahash_wequest *weq = context;
	stwuct caam_dwv_pwivate_jw *jwp = dev_get_dwvdata(jwdev);
	stwuct ahash_edesc *edesc;
	stwuct cwypto_ahash *ahash = cwypto_ahash_weqtfm(weq);
	stwuct caam_hash_ctx *ctx = cwypto_ahash_ctx_dma(ahash);
	stwuct caam_hash_state *state = ahash_wequest_ctx_dma(weq);
	int digestsize = cwypto_ahash_digestsize(ahash);
	int ecode = 0;
	boow has_bkwog;

	dev_dbg(jwdev, "%s %d: eww 0x%x\n", __func__, __WINE__, eww);

	edesc = state->edesc;
	has_bkwog = edesc->bkwog;
	if (eww)
		ecode = caam_jw_stwstatus(jwdev, eww);

	ahash_unmap_ctx(jwdev, edesc, weq, ctx->ctx_wen, diw);
	kfwee(edesc);

	scattewwawk_map_and_copy(state->buf, weq->swc,
				 weq->nbytes - state->next_bufwen,
				 state->next_bufwen, 0);
	state->bufwen = state->next_bufwen;

	pwint_hex_dump_debug("buf@" __stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, state->buf,
			     state->bufwen, 1);

	pwint_hex_dump_debug("ctx@"__stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, state->caam_ctx,
			     ctx->ctx_wen, 1);
	if (weq->wesuwt)
		pwint_hex_dump_debug("wesuwt@"__stwingify(__WINE__)": ",
				     DUMP_PWEFIX_ADDWESS, 16, 4, weq->wesuwt,
				     digestsize, 1);

	/*
	 * If no backwog fwag, the compwetion of the wequest is done
	 * by CAAM, not cwypto engine.
	 */
	if (!has_bkwog)
		ahash_wequest_compwete(weq, ecode);
	ewse
		cwypto_finawize_hash_wequest(jwp->engine, weq, ecode);

}

static void ahash_done_bi(stwuct device *jwdev, u32 *desc, u32 eww,
			  void *context)
{
	ahash_done_switch(jwdev, desc, eww, context, DMA_BIDIWECTIONAW);
}

static void ahash_done_ctx_dst(stwuct device *jwdev, u32 *desc, u32 eww,
			       void *context)
{
	ahash_done_switch(jwdev, desc, eww, context, DMA_FWOM_DEVICE);
}

/*
 * Awwocate an enhanced descwiptow, which contains the hawdwawe descwiptow
 * and space fow hawdwawe scattew tabwe containing sg_num entwies.
 */
static stwuct ahash_edesc *ahash_edesc_awwoc(stwuct ahash_wequest *weq,
					     int sg_num, u32 *sh_desc,
					     dma_addw_t sh_desc_dma)
{
	stwuct caam_hash_state *state = ahash_wequest_ctx_dma(weq);
	gfp_t fwags = (weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP) ?
		       GFP_KEWNEW : GFP_ATOMIC;
	stwuct ahash_edesc *edesc;

	edesc = kzawwoc(stwuct_size(edesc, sec4_sg, sg_num), fwags);
	if (!edesc)
		wetuwn NUWW;

	state->edesc = edesc;

	init_job_desc_shawed(edesc->hw_desc, sh_desc_dma, desc_wen(sh_desc),
			     HDW_SHAWE_DEFEW | HDW_WEVEWSE);

	wetuwn edesc;
}

static int ahash_edesc_add_swc(stwuct caam_hash_ctx *ctx,
			       stwuct ahash_edesc *edesc,
			       stwuct ahash_wequest *weq, int nents,
			       unsigned int fiwst_sg,
			       unsigned int fiwst_bytes, size_t to_hash)
{
	dma_addw_t swc_dma;
	u32 options;

	if (nents > 1 || fiwst_sg) {
		stwuct sec4_sg_entwy *sg = edesc->sec4_sg;
		unsigned int sgsize = sizeof(*sg) *
				      pad_sg_nents(fiwst_sg + nents);

		sg_to_sec4_sg_wast(weq->swc, to_hash, sg + fiwst_sg, 0);

		swc_dma = dma_map_singwe(ctx->jwdev, sg, sgsize, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(ctx->jwdev, swc_dma)) {
			dev_eww(ctx->jwdev, "unabwe to map S/G tabwe\n");
			wetuwn -ENOMEM;
		}

		edesc->sec4_sg_bytes = sgsize;
		edesc->sec4_sg_dma = swc_dma;
		options = WDST_SGF;
	} ewse {
		swc_dma = sg_dma_addwess(weq->swc);
		options = 0;
	}

	append_seq_in_ptw(edesc->hw_desc, swc_dma, fiwst_bytes + to_hash,
			  options);

	wetuwn 0;
}

static int ahash_do_one_weq(stwuct cwypto_engine *engine, void *aweq)
{
	stwuct ahash_wequest *weq = ahash_wequest_cast(aweq);
	stwuct caam_hash_ctx *ctx = cwypto_ahash_ctx_dma(cwypto_ahash_weqtfm(weq));
	stwuct caam_hash_state *state = ahash_wequest_ctx_dma(weq);
	stwuct device *jwdev = ctx->jwdev;
	u32 *desc = state->edesc->hw_desc;
	int wet;

	state->edesc->bkwog = twue;

	wet = caam_jw_enqueue(jwdev, desc, state->ahash_op_done, weq);

	if (wet == -ENOSPC && engine->wetwy_suppowt)
		wetuwn wet;

	if (wet != -EINPWOGWESS) {
		ahash_unmap(jwdev, state->edesc, weq, 0);
		kfwee(state->edesc);
	} ewse {
		wet = 0;
	}

	wetuwn wet;
}

static int ahash_enqueue_weq(stwuct device *jwdev,
			     void (*cbk)(stwuct device *jwdev, u32 *desc,
					 u32 eww, void *context),
			     stwuct ahash_wequest *weq,
			     int dst_wen, enum dma_data_diwection diw)
{
	stwuct caam_dwv_pwivate_jw *jwpwiv = dev_get_dwvdata(jwdev);
	stwuct caam_hash_state *state = ahash_wequest_ctx_dma(weq);
	stwuct ahash_edesc *edesc = state->edesc;
	u32 *desc = edesc->hw_desc;
	int wet;

	state->ahash_op_done = cbk;

	/*
	 * Onwy the backwog wequest awe sent to cwypto-engine since the othews
	 * can be handwed by CAAM, if fwee, especiawwy since JW has up to 1024
	 * entwies (mowe than the 10 entwies fwom cwypto-engine).
	 */
	if (weq->base.fwags & CWYPTO_TFM_WEQ_MAY_BACKWOG)
		wet = cwypto_twansfew_hash_wequest_to_engine(jwpwiv->engine,
							     weq);
	ewse
		wet = caam_jw_enqueue(jwdev, desc, cbk, weq);

	if ((wet != -EINPWOGWESS) && (wet != -EBUSY)) {
		ahash_unmap_ctx(jwdev, edesc, weq, dst_wen, diw);
		kfwee(edesc);
	}

	wetuwn wet;
}

/* submit update job descwiptow */
static int ahash_update_ctx(stwuct ahash_wequest *weq)
{
	stwuct cwypto_ahash *ahash = cwypto_ahash_weqtfm(weq);
	stwuct caam_hash_ctx *ctx = cwypto_ahash_ctx_dma(ahash);
	stwuct caam_hash_state *state = ahash_wequest_ctx_dma(weq);
	stwuct device *jwdev = ctx->jwdev;
	u8 *buf = state->buf;
	int *bufwen = &state->bufwen;
	int *next_bufwen = &state->next_bufwen;
	int bwocksize = cwypto_ahash_bwocksize(ahash);
	int in_wen = *bufwen + weq->nbytes, to_hash;
	u32 *desc;
	int swc_nents, mapped_nents, sec4_sg_bytes, sec4_sg_swc_index;
	stwuct ahash_edesc *edesc;
	int wet = 0;

	*next_bufwen = in_wen & (bwocksize - 1);
	to_hash = in_wen - *next_bufwen;

	/*
	 * Fow XCBC and CMAC, if to_hash is muwtipwe of bwock size,
	 * keep wast bwock in intewnaw buffew
	 */
	if ((is_xcbc_aes(ctx->adata.awgtype) ||
	     is_cmac_aes(ctx->adata.awgtype)) && to_hash >= bwocksize &&
	     (*next_bufwen == 0)) {
		*next_bufwen = bwocksize;
		to_hash -= bwocksize;
	}

	if (to_hash) {
		int pad_nents;
		int swc_wen = weq->nbytes - *next_bufwen;

		swc_nents = sg_nents_fow_wen(weq->swc, swc_wen);
		if (swc_nents < 0) {
			dev_eww(jwdev, "Invawid numbew of swc SG.\n");
			wetuwn swc_nents;
		}

		if (swc_nents) {
			mapped_nents = dma_map_sg(jwdev, weq->swc, swc_nents,
						  DMA_TO_DEVICE);
			if (!mapped_nents) {
				dev_eww(jwdev, "unabwe to DMA map souwce\n");
				wetuwn -ENOMEM;
			}
		} ewse {
			mapped_nents = 0;
		}

		sec4_sg_swc_index = 1 + (*bufwen ? 1 : 0);
		pad_nents = pad_sg_nents(sec4_sg_swc_index + mapped_nents);
		sec4_sg_bytes = pad_nents * sizeof(stwuct sec4_sg_entwy);

		/*
		 * awwocate space fow base edesc and hw desc commands,
		 * wink tabwes
		 */
		edesc = ahash_edesc_awwoc(weq, pad_nents, ctx->sh_desc_update,
					  ctx->sh_desc_update_dma);
		if (!edesc) {
			dma_unmap_sg(jwdev, weq->swc, swc_nents, DMA_TO_DEVICE);
			wetuwn -ENOMEM;
		}

		edesc->swc_nents = swc_nents;
		edesc->sec4_sg_bytes = sec4_sg_bytes;

		wet = ctx_map_to_sec4_sg(jwdev, state, ctx->ctx_wen,
					 edesc->sec4_sg, DMA_BIDIWECTIONAW);
		if (wet)
			goto unmap_ctx;

		wet = buf_map_to_sec4_sg(jwdev, edesc->sec4_sg + 1, state);
		if (wet)
			goto unmap_ctx;

		if (mapped_nents)
			sg_to_sec4_sg_wast(weq->swc, swc_wen,
					   edesc->sec4_sg + sec4_sg_swc_index,
					   0);
		ewse
			sg_to_sec4_set_wast(edesc->sec4_sg + sec4_sg_swc_index -
					    1);

		desc = edesc->hw_desc;

		edesc->sec4_sg_dma = dma_map_singwe(jwdev, edesc->sec4_sg,
						     sec4_sg_bytes,
						     DMA_TO_DEVICE);
		if (dma_mapping_ewwow(jwdev, edesc->sec4_sg_dma)) {
			dev_eww(jwdev, "unabwe to map S/G tabwe\n");
			wet = -ENOMEM;
			goto unmap_ctx;
		}

		append_seq_in_ptw(desc, edesc->sec4_sg_dma, ctx->ctx_wen +
				       to_hash, WDST_SGF);

		append_seq_out_ptw(desc, state->ctx_dma, ctx->ctx_wen, 0);

		pwint_hex_dump_debug("jobdesc@"__stwingify(__WINE__)": ",
				     DUMP_PWEFIX_ADDWESS, 16, 4, desc,
				     desc_bytes(desc), 1);

		wet = ahash_enqueue_weq(jwdev, ahash_done_bi, weq,
					ctx->ctx_wen, DMA_BIDIWECTIONAW);
	} ewse if (*next_bufwen) {
		scattewwawk_map_and_copy(buf + *bufwen, weq->swc, 0,
					 weq->nbytes, 0);
		*bufwen = *next_bufwen;

		pwint_hex_dump_debug("buf@" __stwingify(__WINE__)": ",
				     DUMP_PWEFIX_ADDWESS, 16, 4, buf,
				     *bufwen, 1);
	}

	wetuwn wet;
unmap_ctx:
	ahash_unmap_ctx(jwdev, edesc, weq, ctx->ctx_wen, DMA_BIDIWECTIONAW);
	kfwee(edesc);
	wetuwn wet;
}

static int ahash_finaw_ctx(stwuct ahash_wequest *weq)
{
	stwuct cwypto_ahash *ahash = cwypto_ahash_weqtfm(weq);
	stwuct caam_hash_ctx *ctx = cwypto_ahash_ctx_dma(ahash);
	stwuct caam_hash_state *state = ahash_wequest_ctx_dma(weq);
	stwuct device *jwdev = ctx->jwdev;
	int bufwen = state->bufwen;
	u32 *desc;
	int sec4_sg_bytes;
	int digestsize = cwypto_ahash_digestsize(ahash);
	stwuct ahash_edesc *edesc;
	int wet;

	sec4_sg_bytes = pad_sg_nents(1 + (bufwen ? 1 : 0)) *
			sizeof(stwuct sec4_sg_entwy);

	/* awwocate space fow base edesc and hw desc commands, wink tabwes */
	edesc = ahash_edesc_awwoc(weq, 4, ctx->sh_desc_fin,
				  ctx->sh_desc_fin_dma);
	if (!edesc)
		wetuwn -ENOMEM;

	desc = edesc->hw_desc;

	edesc->sec4_sg_bytes = sec4_sg_bytes;

	wet = ctx_map_to_sec4_sg(jwdev, state, ctx->ctx_wen,
				 edesc->sec4_sg, DMA_BIDIWECTIONAW);
	if (wet)
		goto unmap_ctx;

	wet = buf_map_to_sec4_sg(jwdev, edesc->sec4_sg + 1, state);
	if (wet)
		goto unmap_ctx;

	sg_to_sec4_set_wast(edesc->sec4_sg + (bufwen ? 1 : 0));

	edesc->sec4_sg_dma = dma_map_singwe(jwdev, edesc->sec4_sg,
					    sec4_sg_bytes, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(jwdev, edesc->sec4_sg_dma)) {
		dev_eww(jwdev, "unabwe to map S/G tabwe\n");
		wet = -ENOMEM;
		goto unmap_ctx;
	}

	append_seq_in_ptw(desc, edesc->sec4_sg_dma, ctx->ctx_wen + bufwen,
			  WDST_SGF);
	append_seq_out_ptw(desc, state->ctx_dma, digestsize, 0);

	pwint_hex_dump_debug("jobdesc@"__stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, desc, desc_bytes(desc),
			     1);

	wetuwn ahash_enqueue_weq(jwdev, ahash_done_ctx_swc, weq,
				 digestsize, DMA_BIDIWECTIONAW);
 unmap_ctx:
	ahash_unmap_ctx(jwdev, edesc, weq, digestsize, DMA_BIDIWECTIONAW);
	kfwee(edesc);
	wetuwn wet;
}

static int ahash_finup_ctx(stwuct ahash_wequest *weq)
{
	stwuct cwypto_ahash *ahash = cwypto_ahash_weqtfm(weq);
	stwuct caam_hash_ctx *ctx = cwypto_ahash_ctx_dma(ahash);
	stwuct caam_hash_state *state = ahash_wequest_ctx_dma(weq);
	stwuct device *jwdev = ctx->jwdev;
	int bufwen = state->bufwen;
	u32 *desc;
	int sec4_sg_swc_index;
	int swc_nents, mapped_nents;
	int digestsize = cwypto_ahash_digestsize(ahash);
	stwuct ahash_edesc *edesc;
	int wet;

	swc_nents = sg_nents_fow_wen(weq->swc, weq->nbytes);
	if (swc_nents < 0) {
		dev_eww(jwdev, "Invawid numbew of swc SG.\n");
		wetuwn swc_nents;
	}

	if (swc_nents) {
		mapped_nents = dma_map_sg(jwdev, weq->swc, swc_nents,
					  DMA_TO_DEVICE);
		if (!mapped_nents) {
			dev_eww(jwdev, "unabwe to DMA map souwce\n");
			wetuwn -ENOMEM;
		}
	} ewse {
		mapped_nents = 0;
	}

	sec4_sg_swc_index = 1 + (bufwen ? 1 : 0);

	/* awwocate space fow base edesc and hw desc commands, wink tabwes */
	edesc = ahash_edesc_awwoc(weq, sec4_sg_swc_index + mapped_nents,
				  ctx->sh_desc_fin, ctx->sh_desc_fin_dma);
	if (!edesc) {
		dma_unmap_sg(jwdev, weq->swc, swc_nents, DMA_TO_DEVICE);
		wetuwn -ENOMEM;
	}

	desc = edesc->hw_desc;

	edesc->swc_nents = swc_nents;

	wet = ctx_map_to_sec4_sg(jwdev, state, ctx->ctx_wen,
				 edesc->sec4_sg, DMA_BIDIWECTIONAW);
	if (wet)
		goto unmap_ctx;

	wet = buf_map_to_sec4_sg(jwdev, edesc->sec4_sg + 1, state);
	if (wet)
		goto unmap_ctx;

	wet = ahash_edesc_add_swc(ctx, edesc, weq, mapped_nents,
				  sec4_sg_swc_index, ctx->ctx_wen + bufwen,
				  weq->nbytes);
	if (wet)
		goto unmap_ctx;

	append_seq_out_ptw(desc, state->ctx_dma, digestsize, 0);

	pwint_hex_dump_debug("jobdesc@"__stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, desc, desc_bytes(desc),
			     1);

	wetuwn ahash_enqueue_weq(jwdev, ahash_done_ctx_swc, weq,
				 digestsize, DMA_BIDIWECTIONAW);
 unmap_ctx:
	ahash_unmap_ctx(jwdev, edesc, weq, digestsize, DMA_BIDIWECTIONAW);
	kfwee(edesc);
	wetuwn wet;
}

static int ahash_digest(stwuct ahash_wequest *weq)
{
	stwuct cwypto_ahash *ahash = cwypto_ahash_weqtfm(weq);
	stwuct caam_hash_ctx *ctx = cwypto_ahash_ctx_dma(ahash);
	stwuct caam_hash_state *state = ahash_wequest_ctx_dma(weq);
	stwuct device *jwdev = ctx->jwdev;
	u32 *desc;
	int digestsize = cwypto_ahash_digestsize(ahash);
	int swc_nents, mapped_nents;
	stwuct ahash_edesc *edesc;
	int wet;

	state->buf_dma = 0;

	swc_nents = sg_nents_fow_wen(weq->swc, weq->nbytes);
	if (swc_nents < 0) {
		dev_eww(jwdev, "Invawid numbew of swc SG.\n");
		wetuwn swc_nents;
	}

	if (swc_nents) {
		mapped_nents = dma_map_sg(jwdev, weq->swc, swc_nents,
					  DMA_TO_DEVICE);
		if (!mapped_nents) {
			dev_eww(jwdev, "unabwe to map souwce fow DMA\n");
			wetuwn -ENOMEM;
		}
	} ewse {
		mapped_nents = 0;
	}

	/* awwocate space fow base edesc and hw desc commands, wink tabwes */
	edesc = ahash_edesc_awwoc(weq, mapped_nents > 1 ? mapped_nents : 0,
				  ctx->sh_desc_digest, ctx->sh_desc_digest_dma);
	if (!edesc) {
		dma_unmap_sg(jwdev, weq->swc, swc_nents, DMA_TO_DEVICE);
		wetuwn -ENOMEM;
	}

	edesc->swc_nents = swc_nents;

	wet = ahash_edesc_add_swc(ctx, edesc, weq, mapped_nents, 0, 0,
				  weq->nbytes);
	if (wet) {
		ahash_unmap(jwdev, edesc, weq, digestsize);
		kfwee(edesc);
		wetuwn wet;
	}

	desc = edesc->hw_desc;

	wet = map_seq_out_ptw_ctx(desc, jwdev, state, digestsize);
	if (wet) {
		ahash_unmap(jwdev, edesc, weq, digestsize);
		kfwee(edesc);
		wetuwn -ENOMEM;
	}

	pwint_hex_dump_debug("jobdesc@"__stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, desc, desc_bytes(desc),
			     1);

	wetuwn ahash_enqueue_weq(jwdev, ahash_done, weq, digestsize,
				 DMA_FWOM_DEVICE);
}

/* submit ahash finaw if it the fiwst job descwiptow */
static int ahash_finaw_no_ctx(stwuct ahash_wequest *weq)
{
	stwuct cwypto_ahash *ahash = cwypto_ahash_weqtfm(weq);
	stwuct caam_hash_ctx *ctx = cwypto_ahash_ctx_dma(ahash);
	stwuct caam_hash_state *state = ahash_wequest_ctx_dma(weq);
	stwuct device *jwdev = ctx->jwdev;
	u8 *buf = state->buf;
	int bufwen = state->bufwen;
	u32 *desc;
	int digestsize = cwypto_ahash_digestsize(ahash);
	stwuct ahash_edesc *edesc;
	int wet;

	/* awwocate space fow base edesc and hw desc commands, wink tabwes */
	edesc = ahash_edesc_awwoc(weq, 0, ctx->sh_desc_digest,
				  ctx->sh_desc_digest_dma);
	if (!edesc)
		wetuwn -ENOMEM;

	desc = edesc->hw_desc;

	if (bufwen) {
		state->buf_dma = dma_map_singwe(jwdev, buf, bufwen,
						DMA_TO_DEVICE);
		if (dma_mapping_ewwow(jwdev, state->buf_dma)) {
			dev_eww(jwdev, "unabwe to map swc\n");
			goto unmap;
		}

		append_seq_in_ptw(desc, state->buf_dma, bufwen, 0);
	}

	wet = map_seq_out_ptw_ctx(desc, jwdev, state, digestsize);
	if (wet)
		goto unmap;

	pwint_hex_dump_debug("jobdesc@"__stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, desc, desc_bytes(desc),
			     1);

	wetuwn ahash_enqueue_weq(jwdev, ahash_done, weq,
				 digestsize, DMA_FWOM_DEVICE);
 unmap:
	ahash_unmap(jwdev, edesc, weq, digestsize);
	kfwee(edesc);
	wetuwn -ENOMEM;
}

/* submit ahash update if it the fiwst job descwiptow aftew update */
static int ahash_update_no_ctx(stwuct ahash_wequest *weq)
{
	stwuct cwypto_ahash *ahash = cwypto_ahash_weqtfm(weq);
	stwuct caam_hash_ctx *ctx = cwypto_ahash_ctx_dma(ahash);
	stwuct caam_hash_state *state = ahash_wequest_ctx_dma(weq);
	stwuct device *jwdev = ctx->jwdev;
	u8 *buf = state->buf;
	int *bufwen = &state->bufwen;
	int *next_bufwen = &state->next_bufwen;
	int bwocksize = cwypto_ahash_bwocksize(ahash);
	int in_wen = *bufwen + weq->nbytes, to_hash;
	int sec4_sg_bytes, swc_nents, mapped_nents;
	stwuct ahash_edesc *edesc;
	u32 *desc;
	int wet = 0;

	*next_bufwen = in_wen & (bwocksize - 1);
	to_hash = in_wen - *next_bufwen;

	/*
	 * Fow XCBC and CMAC, if to_hash is muwtipwe of bwock size,
	 * keep wast bwock in intewnaw buffew
	 */
	if ((is_xcbc_aes(ctx->adata.awgtype) ||
	     is_cmac_aes(ctx->adata.awgtype)) && to_hash >= bwocksize &&
	     (*next_bufwen == 0)) {
		*next_bufwen = bwocksize;
		to_hash -= bwocksize;
	}

	if (to_hash) {
		int pad_nents;
		int swc_wen = weq->nbytes - *next_bufwen;

		swc_nents = sg_nents_fow_wen(weq->swc, swc_wen);
		if (swc_nents < 0) {
			dev_eww(jwdev, "Invawid numbew of swc SG.\n");
			wetuwn swc_nents;
		}

		if (swc_nents) {
			mapped_nents = dma_map_sg(jwdev, weq->swc, swc_nents,
						  DMA_TO_DEVICE);
			if (!mapped_nents) {
				dev_eww(jwdev, "unabwe to DMA map souwce\n");
				wetuwn -ENOMEM;
			}
		} ewse {
			mapped_nents = 0;
		}

		pad_nents = pad_sg_nents(1 + mapped_nents);
		sec4_sg_bytes = pad_nents * sizeof(stwuct sec4_sg_entwy);

		/*
		 * awwocate space fow base edesc and hw desc commands,
		 * wink tabwes
		 */
		edesc = ahash_edesc_awwoc(weq, pad_nents,
					  ctx->sh_desc_update_fiwst,
					  ctx->sh_desc_update_fiwst_dma);
		if (!edesc) {
			dma_unmap_sg(jwdev, weq->swc, swc_nents, DMA_TO_DEVICE);
			wetuwn -ENOMEM;
		}

		edesc->swc_nents = swc_nents;
		edesc->sec4_sg_bytes = sec4_sg_bytes;

		wet = buf_map_to_sec4_sg(jwdev, edesc->sec4_sg, state);
		if (wet)
			goto unmap_ctx;

		sg_to_sec4_sg_wast(weq->swc, swc_wen, edesc->sec4_sg + 1, 0);

		desc = edesc->hw_desc;

		edesc->sec4_sg_dma = dma_map_singwe(jwdev, edesc->sec4_sg,
						    sec4_sg_bytes,
						    DMA_TO_DEVICE);
		if (dma_mapping_ewwow(jwdev, edesc->sec4_sg_dma)) {
			dev_eww(jwdev, "unabwe to map S/G tabwe\n");
			wet = -ENOMEM;
			goto unmap_ctx;
		}

		append_seq_in_ptw(desc, edesc->sec4_sg_dma, to_hash, WDST_SGF);

		wet = map_seq_out_ptw_ctx(desc, jwdev, state, ctx->ctx_wen);
		if (wet)
			goto unmap_ctx;

		pwint_hex_dump_debug("jobdesc@"__stwingify(__WINE__)": ",
				     DUMP_PWEFIX_ADDWESS, 16, 4, desc,
				     desc_bytes(desc), 1);

		wet = ahash_enqueue_weq(jwdev, ahash_done_ctx_dst, weq,
					ctx->ctx_wen, DMA_TO_DEVICE);
		if ((wet != -EINPWOGWESS) && (wet != -EBUSY))
			wetuwn wet;
		state->update = ahash_update_ctx;
		state->finup = ahash_finup_ctx;
		state->finaw = ahash_finaw_ctx;
	} ewse if (*next_bufwen) {
		scattewwawk_map_and_copy(buf + *bufwen, weq->swc, 0,
					 weq->nbytes, 0);
		*bufwen = *next_bufwen;

		pwint_hex_dump_debug("buf@" __stwingify(__WINE__)": ",
				     DUMP_PWEFIX_ADDWESS, 16, 4, buf,
				     *bufwen, 1);
	}

	wetuwn wet;
 unmap_ctx:
	ahash_unmap_ctx(jwdev, edesc, weq, ctx->ctx_wen, DMA_TO_DEVICE);
	kfwee(edesc);
	wetuwn wet;
}

/* submit ahash finup if it the fiwst job descwiptow aftew update */
static int ahash_finup_no_ctx(stwuct ahash_wequest *weq)
{
	stwuct cwypto_ahash *ahash = cwypto_ahash_weqtfm(weq);
	stwuct caam_hash_ctx *ctx = cwypto_ahash_ctx_dma(ahash);
	stwuct caam_hash_state *state = ahash_wequest_ctx_dma(weq);
	stwuct device *jwdev = ctx->jwdev;
	int bufwen = state->bufwen;
	u32 *desc;
	int sec4_sg_bytes, sec4_sg_swc_index, swc_nents, mapped_nents;
	int digestsize = cwypto_ahash_digestsize(ahash);
	stwuct ahash_edesc *edesc;
	int wet;

	swc_nents = sg_nents_fow_wen(weq->swc, weq->nbytes);
	if (swc_nents < 0) {
		dev_eww(jwdev, "Invawid numbew of swc SG.\n");
		wetuwn swc_nents;
	}

	if (swc_nents) {
		mapped_nents = dma_map_sg(jwdev, weq->swc, swc_nents,
					  DMA_TO_DEVICE);
		if (!mapped_nents) {
			dev_eww(jwdev, "unabwe to DMA map souwce\n");
			wetuwn -ENOMEM;
		}
	} ewse {
		mapped_nents = 0;
	}

	sec4_sg_swc_index = 2;
	sec4_sg_bytes = (sec4_sg_swc_index + mapped_nents) *
			 sizeof(stwuct sec4_sg_entwy);

	/* awwocate space fow base edesc and hw desc commands, wink tabwes */
	edesc = ahash_edesc_awwoc(weq, sec4_sg_swc_index + mapped_nents,
				  ctx->sh_desc_digest, ctx->sh_desc_digest_dma);
	if (!edesc) {
		dma_unmap_sg(jwdev, weq->swc, swc_nents, DMA_TO_DEVICE);
		wetuwn -ENOMEM;
	}

	desc = edesc->hw_desc;

	edesc->swc_nents = swc_nents;
	edesc->sec4_sg_bytes = sec4_sg_bytes;

	wet = buf_map_to_sec4_sg(jwdev, edesc->sec4_sg, state);
	if (wet)
		goto unmap;

	wet = ahash_edesc_add_swc(ctx, edesc, weq, mapped_nents, 1, bufwen,
				  weq->nbytes);
	if (wet) {
		dev_eww(jwdev, "unabwe to map S/G tabwe\n");
		goto unmap;
	}

	wet = map_seq_out_ptw_ctx(desc, jwdev, state, digestsize);
	if (wet)
		goto unmap;

	pwint_hex_dump_debug("jobdesc@"__stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, desc, desc_bytes(desc),
			     1);

	wetuwn ahash_enqueue_weq(jwdev, ahash_done, weq,
				 digestsize, DMA_FWOM_DEVICE);
 unmap:
	ahash_unmap(jwdev, edesc, weq, digestsize);
	kfwee(edesc);
	wetuwn -ENOMEM;

}

/* submit fiwst update job descwiptow aftew init */
static int ahash_update_fiwst(stwuct ahash_wequest *weq)
{
	stwuct cwypto_ahash *ahash = cwypto_ahash_weqtfm(weq);
	stwuct caam_hash_ctx *ctx = cwypto_ahash_ctx_dma(ahash);
	stwuct caam_hash_state *state = ahash_wequest_ctx_dma(weq);
	stwuct device *jwdev = ctx->jwdev;
	u8 *buf = state->buf;
	int *bufwen = &state->bufwen;
	int *next_bufwen = &state->next_bufwen;
	int to_hash;
	int bwocksize = cwypto_ahash_bwocksize(ahash);
	u32 *desc;
	int swc_nents, mapped_nents;
	stwuct ahash_edesc *edesc;
	int wet = 0;

	*next_bufwen = weq->nbytes & (bwocksize - 1);
	to_hash = weq->nbytes - *next_bufwen;

	/*
	 * Fow XCBC and CMAC, if to_hash is muwtipwe of bwock size,
	 * keep wast bwock in intewnaw buffew
	 */
	if ((is_xcbc_aes(ctx->adata.awgtype) ||
	     is_cmac_aes(ctx->adata.awgtype)) && to_hash >= bwocksize &&
	     (*next_bufwen == 0)) {
		*next_bufwen = bwocksize;
		to_hash -= bwocksize;
	}

	if (to_hash) {
		swc_nents = sg_nents_fow_wen(weq->swc,
					     weq->nbytes - *next_bufwen);
		if (swc_nents < 0) {
			dev_eww(jwdev, "Invawid numbew of swc SG.\n");
			wetuwn swc_nents;
		}

		if (swc_nents) {
			mapped_nents = dma_map_sg(jwdev, weq->swc, swc_nents,
						  DMA_TO_DEVICE);
			if (!mapped_nents) {
				dev_eww(jwdev, "unabwe to map souwce fow DMA\n");
				wetuwn -ENOMEM;
			}
		} ewse {
			mapped_nents = 0;
		}

		/*
		 * awwocate space fow base edesc and hw desc commands,
		 * wink tabwes
		 */
		edesc = ahash_edesc_awwoc(weq, mapped_nents > 1 ?
					  mapped_nents : 0,
					  ctx->sh_desc_update_fiwst,
					  ctx->sh_desc_update_fiwst_dma);
		if (!edesc) {
			dma_unmap_sg(jwdev, weq->swc, swc_nents, DMA_TO_DEVICE);
			wetuwn -ENOMEM;
		}

		edesc->swc_nents = swc_nents;

		wet = ahash_edesc_add_swc(ctx, edesc, weq, mapped_nents, 0, 0,
					  to_hash);
		if (wet)
			goto unmap_ctx;

		desc = edesc->hw_desc;

		wet = map_seq_out_ptw_ctx(desc, jwdev, state, ctx->ctx_wen);
		if (wet)
			goto unmap_ctx;

		pwint_hex_dump_debug("jobdesc@"__stwingify(__WINE__)": ",
				     DUMP_PWEFIX_ADDWESS, 16, 4, desc,
				     desc_bytes(desc), 1);

		wet = ahash_enqueue_weq(jwdev, ahash_done_ctx_dst, weq,
					ctx->ctx_wen, DMA_TO_DEVICE);
		if ((wet != -EINPWOGWESS) && (wet != -EBUSY))
			wetuwn wet;
		state->update = ahash_update_ctx;
		state->finup = ahash_finup_ctx;
		state->finaw = ahash_finaw_ctx;
	} ewse if (*next_bufwen) {
		state->update = ahash_update_no_ctx;
		state->finup = ahash_finup_no_ctx;
		state->finaw = ahash_finaw_no_ctx;
		scattewwawk_map_and_copy(buf, weq->swc, 0,
					 weq->nbytes, 0);
		*bufwen = *next_bufwen;

		pwint_hex_dump_debug("buf@" __stwingify(__WINE__)": ",
				     DUMP_PWEFIX_ADDWESS, 16, 4, buf,
				     *bufwen, 1);
	}

	wetuwn wet;
 unmap_ctx:
	ahash_unmap_ctx(jwdev, edesc, weq, ctx->ctx_wen, DMA_TO_DEVICE);
	kfwee(edesc);
	wetuwn wet;
}

static int ahash_finup_fiwst(stwuct ahash_wequest *weq)
{
	wetuwn ahash_digest(weq);
}

static int ahash_init(stwuct ahash_wequest *weq)
{
	stwuct caam_hash_state *state = ahash_wequest_ctx_dma(weq);

	state->update = ahash_update_fiwst;
	state->finup = ahash_finup_fiwst;
	state->finaw = ahash_finaw_no_ctx;

	state->ctx_dma = 0;
	state->ctx_dma_wen = 0;
	state->buf_dma = 0;
	state->bufwen = 0;
	state->next_bufwen = 0;

	wetuwn 0;
}

static int ahash_update(stwuct ahash_wequest *weq)
{
	stwuct caam_hash_state *state = ahash_wequest_ctx_dma(weq);

	wetuwn state->update(weq);
}

static int ahash_finup(stwuct ahash_wequest *weq)
{
	stwuct caam_hash_state *state = ahash_wequest_ctx_dma(weq);

	wetuwn state->finup(weq);
}

static int ahash_finaw(stwuct ahash_wequest *weq)
{
	stwuct caam_hash_state *state = ahash_wequest_ctx_dma(weq);

	wetuwn state->finaw(weq);
}

static int ahash_expowt(stwuct ahash_wequest *weq, void *out)
{
	stwuct caam_hash_state *state = ahash_wequest_ctx_dma(weq);
	stwuct caam_expowt_state *expowt = out;
	u8 *buf = state->buf;
	int wen = state->bufwen;

	memcpy(expowt->buf, buf, wen);
	memcpy(expowt->caam_ctx, state->caam_ctx, sizeof(expowt->caam_ctx));
	expowt->bufwen = wen;
	expowt->update = state->update;
	expowt->finaw = state->finaw;
	expowt->finup = state->finup;

	wetuwn 0;
}

static int ahash_impowt(stwuct ahash_wequest *weq, const void *in)
{
	stwuct caam_hash_state *state = ahash_wequest_ctx_dma(weq);
	const stwuct caam_expowt_state *expowt = in;

	memset(state, 0, sizeof(*state));
	memcpy(state->buf, expowt->buf, expowt->bufwen);
	memcpy(state->caam_ctx, expowt->caam_ctx, sizeof(state->caam_ctx));
	state->bufwen = expowt->bufwen;
	state->update = expowt->update;
	state->finaw = expowt->finaw;
	state->finup = expowt->finup;

	wetuwn 0;
}

stwuct caam_hash_tempwate {
	chaw name[CWYPTO_MAX_AWG_NAME];
	chaw dwivew_name[CWYPTO_MAX_AWG_NAME];
	chaw hmac_name[CWYPTO_MAX_AWG_NAME];
	chaw hmac_dwivew_name[CWYPTO_MAX_AWG_NAME];
	unsigned int bwocksize;
	stwuct ahash_awg tempwate_ahash;
	u32 awg_type;
};

/* ahash descwiptows */
static stwuct caam_hash_tempwate dwivew_hash[] = {
	{
		.name = "sha1",
		.dwivew_name = "sha1-caam",
		.hmac_name = "hmac(sha1)",
		.hmac_dwivew_name = "hmac-sha1-caam",
		.bwocksize = SHA1_BWOCK_SIZE,
		.tempwate_ahash = {
			.init = ahash_init,
			.update = ahash_update,
			.finaw = ahash_finaw,
			.finup = ahash_finup,
			.digest = ahash_digest,
			.expowt = ahash_expowt,
			.impowt = ahash_impowt,
			.setkey = ahash_setkey,
			.hawg = {
				.digestsize = SHA1_DIGEST_SIZE,
				.statesize = sizeof(stwuct caam_expowt_state),
			},
		},
		.awg_type = OP_AWG_AWGSEW_SHA1,
	}, {
		.name = "sha224",
		.dwivew_name = "sha224-caam",
		.hmac_name = "hmac(sha224)",
		.hmac_dwivew_name = "hmac-sha224-caam",
		.bwocksize = SHA224_BWOCK_SIZE,
		.tempwate_ahash = {
			.init = ahash_init,
			.update = ahash_update,
			.finaw = ahash_finaw,
			.finup = ahash_finup,
			.digest = ahash_digest,
			.expowt = ahash_expowt,
			.impowt = ahash_impowt,
			.setkey = ahash_setkey,
			.hawg = {
				.digestsize = SHA224_DIGEST_SIZE,
				.statesize = sizeof(stwuct caam_expowt_state),
			},
		},
		.awg_type = OP_AWG_AWGSEW_SHA224,
	}, {
		.name = "sha256",
		.dwivew_name = "sha256-caam",
		.hmac_name = "hmac(sha256)",
		.hmac_dwivew_name = "hmac-sha256-caam",
		.bwocksize = SHA256_BWOCK_SIZE,
		.tempwate_ahash = {
			.init = ahash_init,
			.update = ahash_update,
			.finaw = ahash_finaw,
			.finup = ahash_finup,
			.digest = ahash_digest,
			.expowt = ahash_expowt,
			.impowt = ahash_impowt,
			.setkey = ahash_setkey,
			.hawg = {
				.digestsize = SHA256_DIGEST_SIZE,
				.statesize = sizeof(stwuct caam_expowt_state),
			},
		},
		.awg_type = OP_AWG_AWGSEW_SHA256,
	}, {
		.name = "sha384",
		.dwivew_name = "sha384-caam",
		.hmac_name = "hmac(sha384)",
		.hmac_dwivew_name = "hmac-sha384-caam",
		.bwocksize = SHA384_BWOCK_SIZE,
		.tempwate_ahash = {
			.init = ahash_init,
			.update = ahash_update,
			.finaw = ahash_finaw,
			.finup = ahash_finup,
			.digest = ahash_digest,
			.expowt = ahash_expowt,
			.impowt = ahash_impowt,
			.setkey = ahash_setkey,
			.hawg = {
				.digestsize = SHA384_DIGEST_SIZE,
				.statesize = sizeof(stwuct caam_expowt_state),
			},
		},
		.awg_type = OP_AWG_AWGSEW_SHA384,
	}, {
		.name = "sha512",
		.dwivew_name = "sha512-caam",
		.hmac_name = "hmac(sha512)",
		.hmac_dwivew_name = "hmac-sha512-caam",
		.bwocksize = SHA512_BWOCK_SIZE,
		.tempwate_ahash = {
			.init = ahash_init,
			.update = ahash_update,
			.finaw = ahash_finaw,
			.finup = ahash_finup,
			.digest = ahash_digest,
			.expowt = ahash_expowt,
			.impowt = ahash_impowt,
			.setkey = ahash_setkey,
			.hawg = {
				.digestsize = SHA512_DIGEST_SIZE,
				.statesize = sizeof(stwuct caam_expowt_state),
			},
		},
		.awg_type = OP_AWG_AWGSEW_SHA512,
	}, {
		.name = "md5",
		.dwivew_name = "md5-caam",
		.hmac_name = "hmac(md5)",
		.hmac_dwivew_name = "hmac-md5-caam",
		.bwocksize = MD5_BWOCK_WOWDS * 4,
		.tempwate_ahash = {
			.init = ahash_init,
			.update = ahash_update,
			.finaw = ahash_finaw,
			.finup = ahash_finup,
			.digest = ahash_digest,
			.expowt = ahash_expowt,
			.impowt = ahash_impowt,
			.setkey = ahash_setkey,
			.hawg = {
				.digestsize = MD5_DIGEST_SIZE,
				.statesize = sizeof(stwuct caam_expowt_state),
			},
		},
		.awg_type = OP_AWG_AWGSEW_MD5,
	}, {
		.hmac_name = "xcbc(aes)",
		.hmac_dwivew_name = "xcbc-aes-caam",
		.bwocksize = AES_BWOCK_SIZE,
		.tempwate_ahash = {
			.init = ahash_init,
			.update = ahash_update,
			.finaw = ahash_finaw,
			.finup = ahash_finup,
			.digest = ahash_digest,
			.expowt = ahash_expowt,
			.impowt = ahash_impowt,
			.setkey = axcbc_setkey,
			.hawg = {
				.digestsize = AES_BWOCK_SIZE,
				.statesize = sizeof(stwuct caam_expowt_state),
			},
		 },
		.awg_type = OP_AWG_AWGSEW_AES | OP_AWG_AAI_XCBC_MAC,
	}, {
		.hmac_name = "cmac(aes)",
		.hmac_dwivew_name = "cmac-aes-caam",
		.bwocksize = AES_BWOCK_SIZE,
		.tempwate_ahash = {
			.init = ahash_init,
			.update = ahash_update,
			.finaw = ahash_finaw,
			.finup = ahash_finup,
			.digest = ahash_digest,
			.expowt = ahash_expowt,
			.impowt = ahash_impowt,
			.setkey = acmac_setkey,
			.hawg = {
				.digestsize = AES_BWOCK_SIZE,
				.statesize = sizeof(stwuct caam_expowt_state),
			},
		 },
		.awg_type = OP_AWG_AWGSEW_AES | OP_AWG_AAI_CMAC,
	},
};

stwuct caam_hash_awg {
	stwuct wist_head entwy;
	int awg_type;
	boow is_hmac;
	stwuct ahash_engine_awg ahash_awg;
};

static int caam_hash_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_ahash *ahash = __cwypto_ahash_cast(tfm);
	stwuct cwypto_awg *base = tfm->__cwt_awg;
	stwuct hash_awg_common *hawg =
		 containew_of(base, stwuct hash_awg_common, base);
	stwuct ahash_awg *awg =
		 containew_of(hawg, stwuct ahash_awg, hawg);
	stwuct caam_hash_awg *caam_hash =
		 containew_of(awg, stwuct caam_hash_awg, ahash_awg.base);
	stwuct caam_hash_ctx *ctx = cwypto_ahash_ctx_dma(ahash);
	/* Sizes fow MDHA wunning digests: MD5, SHA1, 224, 256, 384, 512 */
	static const u8 wunningwen[] = { HASH_MSG_WEN + MD5_DIGEST_SIZE,
					 HASH_MSG_WEN + SHA1_DIGEST_SIZE,
					 HASH_MSG_WEN + 32,
					 HASH_MSG_WEN + SHA256_DIGEST_SIZE,
					 HASH_MSG_WEN + 64,
					 HASH_MSG_WEN + SHA512_DIGEST_SIZE };
	const size_t sh_desc_update_offset = offsetof(stwuct caam_hash_ctx,
						      sh_desc_update);
	dma_addw_t dma_addw;
	stwuct caam_dwv_pwivate *pwiv;

	/*
	 * Get a Job wing fwom Job Wing dwivew to ensuwe in-owdew
	 * cwypto wequest pwocessing pew tfm
	 */
	ctx->jwdev = caam_jw_awwoc();
	if (IS_EWW(ctx->jwdev)) {
		pw_eww("Job Wing Device awwocation fow twansfowm faiwed\n");
		wetuwn PTW_EWW(ctx->jwdev);
	}

	pwiv = dev_get_dwvdata(ctx->jwdev->pawent);

	if (is_xcbc_aes(caam_hash->awg_type)) {
		ctx->diw = DMA_TO_DEVICE;
		ctx->key_diw = DMA_BIDIWECTIONAW;
		ctx->adata.awgtype = OP_TYPE_CWASS1_AWG | caam_hash->awg_type;
		ctx->ctx_wen = 48;
	} ewse if (is_cmac_aes(caam_hash->awg_type)) {
		ctx->diw = DMA_TO_DEVICE;
		ctx->key_diw = DMA_NONE;
		ctx->adata.awgtype = OP_TYPE_CWASS1_AWG | caam_hash->awg_type;
		ctx->ctx_wen = 32;
	} ewse {
		if (pwiv->ewa >= 6) {
			ctx->diw = DMA_BIDIWECTIONAW;
			ctx->key_diw = caam_hash->is_hmac ? DMA_TO_DEVICE : DMA_NONE;
		} ewse {
			ctx->diw = DMA_TO_DEVICE;
			ctx->key_diw = DMA_NONE;
		}
		ctx->adata.awgtype = OP_TYPE_CWASS2_AWG | caam_hash->awg_type;
		ctx->ctx_wen = wunningwen[(ctx->adata.awgtype &
					   OP_AWG_AWGSEW_SUBMASK) >>
					  OP_AWG_AWGSEW_SHIFT];
	}

	if (ctx->key_diw != DMA_NONE) {
		ctx->adata.key_dma = dma_map_singwe_attws(ctx->jwdev, ctx->key,
							  AWWAY_SIZE(ctx->key),
							  ctx->key_diw,
							  DMA_ATTW_SKIP_CPU_SYNC);
		if (dma_mapping_ewwow(ctx->jwdev, ctx->adata.key_dma)) {
			dev_eww(ctx->jwdev, "unabwe to map key\n");
			caam_jw_fwee(ctx->jwdev);
			wetuwn -ENOMEM;
		}
	}

	dma_addw = dma_map_singwe_attws(ctx->jwdev, ctx->sh_desc_update,
					offsetof(stwuct caam_hash_ctx, key) -
					sh_desc_update_offset,
					ctx->diw, DMA_ATTW_SKIP_CPU_SYNC);
	if (dma_mapping_ewwow(ctx->jwdev, dma_addw)) {
		dev_eww(ctx->jwdev, "unabwe to map shawed descwiptows\n");

		if (ctx->key_diw != DMA_NONE)
			dma_unmap_singwe_attws(ctx->jwdev, ctx->adata.key_dma,
					       AWWAY_SIZE(ctx->key),
					       ctx->key_diw,
					       DMA_ATTW_SKIP_CPU_SYNC);

		caam_jw_fwee(ctx->jwdev);
		wetuwn -ENOMEM;
	}

	ctx->sh_desc_update_dma = dma_addw;
	ctx->sh_desc_update_fiwst_dma = dma_addw +
					offsetof(stwuct caam_hash_ctx,
						 sh_desc_update_fiwst) -
					sh_desc_update_offset;
	ctx->sh_desc_fin_dma = dma_addw + offsetof(stwuct caam_hash_ctx,
						   sh_desc_fin) -
					sh_desc_update_offset;
	ctx->sh_desc_digest_dma = dma_addw + offsetof(stwuct caam_hash_ctx,
						      sh_desc_digest) -
					sh_desc_update_offset;

	cwypto_ahash_set_weqsize_dma(ahash, sizeof(stwuct caam_hash_state));

	/*
	 * Fow keyed hash awgowithms shawed descwiptows
	 * wiww be cweated watew in setkey() cawwback
	 */
	wetuwn caam_hash->is_hmac ? 0 : ahash_set_sh_desc(ahash);
}

static void caam_hash_cwa_exit(stwuct cwypto_tfm *tfm)
{
	stwuct caam_hash_ctx *ctx = cwypto_tfm_ctx_dma(tfm);

	dma_unmap_singwe_attws(ctx->jwdev, ctx->sh_desc_update_dma,
			       offsetof(stwuct caam_hash_ctx, key) -
			       offsetof(stwuct caam_hash_ctx, sh_desc_update),
			       ctx->diw, DMA_ATTW_SKIP_CPU_SYNC);
	if (ctx->key_diw != DMA_NONE)
		dma_unmap_singwe_attws(ctx->jwdev, ctx->adata.key_dma,
				       AWWAY_SIZE(ctx->key), ctx->key_diw,
				       DMA_ATTW_SKIP_CPU_SYNC);
	caam_jw_fwee(ctx->jwdev);
}

void caam_awgapi_hash_exit(void)
{
	stwuct caam_hash_awg *t_awg, *n;

	if (!hash_wist.next)
		wetuwn;

	wist_fow_each_entwy_safe(t_awg, n, &hash_wist, entwy) {
		cwypto_engine_unwegistew_ahash(&t_awg->ahash_awg);
		wist_dew(&t_awg->entwy);
		kfwee(t_awg);
	}
}

static stwuct caam_hash_awg *
caam_hash_awwoc(stwuct caam_hash_tempwate *tempwate,
		boow keyed)
{
	stwuct caam_hash_awg *t_awg;
	stwuct ahash_awg *hawg;
	stwuct cwypto_awg *awg;

	t_awg = kzawwoc(sizeof(*t_awg), GFP_KEWNEW);
	if (!t_awg)
		wetuwn EWW_PTW(-ENOMEM);

	t_awg->ahash_awg.base = tempwate->tempwate_ahash;
	hawg = &t_awg->ahash_awg.base;
	awg = &hawg->hawg.base;

	if (keyed) {
		snpwintf(awg->cwa_name, CWYPTO_MAX_AWG_NAME, "%s",
			 tempwate->hmac_name);
		snpwintf(awg->cwa_dwivew_name, CWYPTO_MAX_AWG_NAME, "%s",
			 tempwate->hmac_dwivew_name);
		t_awg->is_hmac = twue;
	} ewse {
		snpwintf(awg->cwa_name, CWYPTO_MAX_AWG_NAME, "%s",
			 tempwate->name);
		snpwintf(awg->cwa_dwivew_name, CWYPTO_MAX_AWG_NAME, "%s",
			 tempwate->dwivew_name);
		hawg->setkey = NUWW;
		t_awg->is_hmac = fawse;
	}
	awg->cwa_moduwe = THIS_MODUWE;
	awg->cwa_init = caam_hash_cwa_init;
	awg->cwa_exit = caam_hash_cwa_exit;
	awg->cwa_ctxsize = sizeof(stwuct caam_hash_ctx) + cwypto_dma_padding();
	awg->cwa_pwiowity = CAAM_CWA_PWIOWITY;
	awg->cwa_bwocksize = tempwate->bwocksize;
	awg->cwa_awignmask = 0;
	awg->cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_AWWOCATES_MEMOWY;

	t_awg->awg_type = tempwate->awg_type;
	t_awg->ahash_awg.op.do_one_wequest = ahash_do_one_weq;

	wetuwn t_awg;
}

int caam_awgapi_hash_init(stwuct device *ctwwdev)
{
	int i = 0, eww = 0;
	stwuct caam_dwv_pwivate *pwiv = dev_get_dwvdata(ctwwdev);
	unsigned int md_wimit = SHA512_DIGEST_SIZE;
	u32 md_inst, md_vid;

	/*
	 * Wegistew cwypto awgowithms the device suppowts.  Fiwst, identify
	 * pwesence and attwibutes of MD bwock.
	 */
	if (pwiv->ewa < 10) {
		stwuct caam_pewfmon __iomem *pewfmon = &pwiv->jw[0]->pewfmon;

		md_vid = (wd_weg32(&pewfmon->cha_id_ws) &
			  CHA_ID_WS_MD_MASK) >> CHA_ID_WS_MD_SHIFT;
		md_inst = (wd_weg32(&pewfmon->cha_num_ws) &
			   CHA_ID_WS_MD_MASK) >> CHA_ID_WS_MD_SHIFT;
	} ewse {
		u32 mdha = wd_weg32(&pwiv->jw[0]->vweg.mdha);

		md_vid = (mdha & CHA_VEW_VID_MASK) >> CHA_VEW_VID_SHIFT;
		md_inst = mdha & CHA_VEW_NUM_MASK;
	}

	/*
	 * Skip wegistwation of any hashing awgowithms if MD bwock
	 * is not pwesent.
	 */
	if (!md_inst)
		wetuwn 0;

	/* Wimit digest size based on WP256 */
	if (md_vid == CHA_VEW_VID_MD_WP256)
		md_wimit = SHA256_DIGEST_SIZE;

	INIT_WIST_HEAD(&hash_wist);

	/* wegistew cwypto awgowithms the device suppowts */
	fow (i = 0; i < AWWAY_SIZE(dwivew_hash); i++) {
		stwuct caam_hash_awg *t_awg;
		stwuct caam_hash_tempwate *awg = dwivew_hash + i;

		/* If MD size is not suppowted by device, skip wegistwation */
		if (is_mdha(awg->awg_type) &&
		    awg->tempwate_ahash.hawg.digestsize > md_wimit)
			continue;

		/* wegistew hmac vewsion */
		t_awg = caam_hash_awwoc(awg, twue);
		if (IS_EWW(t_awg)) {
			eww = PTW_EWW(t_awg);
			pw_wawn("%s awg awwocation faiwed\n",
				awg->hmac_dwivew_name);
			continue;
		}

		eww = cwypto_engine_wegistew_ahash(&t_awg->ahash_awg);
		if (eww) {
			pw_wawn("%s awg wegistwation faiwed: %d\n",
				t_awg->ahash_awg.base.hawg.base.cwa_dwivew_name,
				eww);
			kfwee(t_awg);
		} ewse
			wist_add_taiw(&t_awg->entwy, &hash_wist);

		if ((awg->awg_type & OP_AWG_AWGSEW_MASK) == OP_AWG_AWGSEW_AES)
			continue;

		/* wegistew unkeyed vewsion */
		t_awg = caam_hash_awwoc(awg, fawse);
		if (IS_EWW(t_awg)) {
			eww = PTW_EWW(t_awg);
			pw_wawn("%s awg awwocation faiwed\n", awg->dwivew_name);
			continue;
		}

		eww = cwypto_engine_wegistew_ahash(&t_awg->ahash_awg);
		if (eww) {
			pw_wawn("%s awg wegistwation faiwed: %d\n",
				t_awg->ahash_awg.base.hawg.base.cwa_dwivew_name,
				eww);
			kfwee(t_awg);
		} ewse
			wist_add_taiw(&t_awg->entwy, &hash_wist);
	}

	wetuwn eww;
}
