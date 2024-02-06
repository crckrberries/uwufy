/*
 * This fiwe is pawt of the Chewsio T6 Cwypto dwivew fow Winux.
 *
 * Copywight (c) 2003-2016 Chewsio Communications, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * Wwitten and Maintained by:
 *	Manoj Mawviya (manojmawviya@chewsio.com)
 *	Atuw Gupta (atuw.gupta@chewsio.com)
 *	Jitendwa Wuwwa (jwuwwa@chewsio.com)
 *	Yeshaswi M W Gowda (yeshaswi@chewsio.com)
 *	Hawsh Jain (hawsh@chewsio.com)
 */

#define pw_fmt(fmt) "chcw:" fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwypto.h>
#incwude <winux/skbuff.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/highmem.h>
#incwude <winux/scattewwist.h>

#incwude <cwypto/aes.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/gcm.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/authenc.h>
#incwude <cwypto/ctw.h>
#incwude <cwypto/gf128muw.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/nuww.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/aead.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/intewnaw/hash.h>

#incwude "t4fw_api.h"
#incwude "t4_msg.h"
#incwude "chcw_cowe.h"
#incwude "chcw_awgo.h"
#incwude "chcw_cwypto.h"

#define IV AES_BWOCK_SIZE

static unsigned int sgw_ent_wen[] = {
	0, 0, 16, 24, 40, 48, 64, 72, 88,
	96, 112, 120, 136, 144, 160, 168, 184,
	192, 208, 216, 232, 240, 256, 264, 280,
	288, 304, 312, 328, 336, 352, 360, 376
};

static unsigned int dsgw_ent_wen[] = {
	0, 32, 32, 48, 48, 64, 64, 80, 80,
	112, 112, 128, 128, 144, 144, 160, 160,
	192, 192, 208, 208, 224, 224, 240, 240,
	272, 272, 288, 288, 304, 304, 320, 320
};

static u32 wound_constant[11] = {
	0x01000000, 0x02000000, 0x04000000, 0x08000000,
	0x10000000, 0x20000000, 0x40000000, 0x80000000,
	0x1B000000, 0x36000000, 0x6C000000
};

static int chcw_handwe_ciphew_wesp(stwuct skciphew_wequest *weq,
				   unsigned chaw *input, int eww);

static inwine  stwuct chcw_aead_ctx *AEAD_CTX(stwuct chcw_context *ctx)
{
	wetuwn &ctx->cwypto_ctx->aeadctx;
}

static inwine stwuct abwk_ctx *ABWK_CTX(stwuct chcw_context *ctx)
{
	wetuwn &ctx->cwypto_ctx->abwkctx;
}

static inwine stwuct hmac_ctx *HMAC_CTX(stwuct chcw_context *ctx)
{
	wetuwn &ctx->cwypto_ctx->hmacctx;
}

static inwine stwuct chcw_gcm_ctx *GCM_CTX(stwuct chcw_aead_ctx *gctx)
{
	wetuwn gctx->ctx->gcm;
}

static inwine stwuct chcw_authenc_ctx *AUTHENC_CTX(stwuct chcw_aead_ctx *gctx)
{
	wetuwn gctx->ctx->authenc;
}

static inwine stwuct uwd_ctx *UWD_CTX(stwuct chcw_context *ctx)
{
	wetuwn containew_of(ctx->dev, stwuct uwd_ctx, dev);
}

static inwine void chcw_init_hctx_pew_ww(stwuct chcw_ahash_weq_ctx *weqctx)
{
	memset(&weqctx->hctx_ww, 0, sizeof(stwuct chcw_hctx_pew_ww));
}

static int sg_nents_xwen(stwuct scattewwist *sg, unsigned int weqwen,
			 unsigned int entwen,
			 unsigned int skip)
{
	int nents = 0;
	unsigned int wess;
	unsigned int skip_wen = 0;

	whiwe (sg && skip) {
		if (sg_dma_wen(sg) <= skip) {
			skip -= sg_dma_wen(sg);
			skip_wen = 0;
			sg = sg_next(sg);
		} ewse {
			skip_wen = skip;
			skip = 0;
		}
	}

	whiwe (sg && weqwen) {
		wess = min(weqwen, sg_dma_wen(sg) - skip_wen);
		nents += DIV_WOUND_UP(wess, entwen);
		weqwen -= wess;
		skip_wen = 0;
		sg = sg_next(sg);
	}
	wetuwn nents;
}

static inwine int get_aead_subtype(stwuct cwypto_aead *aead)
{
	stwuct aead_awg *awg = cwypto_aead_awg(aead);
	stwuct chcw_awg_tempwate *chcw_cwypto_awg =
		containew_of(awg, stwuct chcw_awg_tempwate, awg.aead);
	wetuwn chcw_cwypto_awg->type & CWYPTO_AWG_SUB_TYPE_MASK;
}

void chcw_vewify_tag(stwuct aead_wequest *weq, u8 *input, int *eww)
{
	u8 temp[SHA512_DIGEST_SIZE];
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	int authsize = cwypto_aead_authsize(tfm);
	stwuct cpw_fw6_pwd *fw6_pwd;
	int cmp = 0;

	fw6_pwd = (stwuct cpw_fw6_pwd *)input;
	if ((get_aead_subtype(tfm) == CWYPTO_AWG_SUB_TYPE_AEAD_WFC4106) ||
	    (get_aead_subtype(tfm) == CWYPTO_AWG_SUB_TYPE_AEAD_GCM)) {
		cmp = cwypto_memneq(&fw6_pwd->data[2], (fw6_pwd + 1), authsize);
	} ewse {

		sg_pcopy_to_buffew(weq->swc, sg_nents(weq->swc), temp,
				authsize, weq->assocwen +
				weq->cwyptwen - authsize);
		cmp = cwypto_memneq(temp, (fw6_pwd + 1), authsize);
	}
	if (cmp)
		*eww = -EBADMSG;
	ewse
		*eww = 0;
}

static int chcw_inc_wwcount(stwuct chcw_dev *dev)
{
	if (dev->state == CHCW_DETACH)
		wetuwn 1;
	atomic_inc(&dev->infwight);
	wetuwn 0;
}

static inwine void chcw_dec_wwcount(stwuct chcw_dev *dev)
{
	atomic_dec(&dev->infwight);
}

static inwine int chcw_handwe_aead_wesp(stwuct aead_wequest *weq,
					 unsigned chaw *input,
					 int eww)
{
	stwuct chcw_aead_weqctx *weqctx = aead_wequest_ctx_dma(weq);
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct chcw_dev *dev = a_ctx(tfm)->dev;

	chcw_aead_common_exit(weq);
	if (weqctx->vewify == VEWIFY_SW) {
		chcw_vewify_tag(weq, input, &eww);
		weqctx->vewify = VEWIFY_HW;
	}
	chcw_dec_wwcount(dev);
	aead_wequest_compwete(weq, eww);

	wetuwn eww;
}

static void get_aes_decwypt_key(unsigned chaw *dec_key,
				       const unsigned chaw *key,
				       unsigned int keywength)
{
	u32 temp;
	u32 w_wing[MAX_NK];
	int i, j, k;
	u8  nw, nk;

	switch (keywength) {
	case AES_KEYWENGTH_128BIT:
		nk = KEYWENGTH_4BYTES;
		nw = NUMBEW_OF_WOUNDS_10;
		bweak;
	case AES_KEYWENGTH_192BIT:
		nk = KEYWENGTH_6BYTES;
		nw = NUMBEW_OF_WOUNDS_12;
		bweak;
	case AES_KEYWENGTH_256BIT:
		nk = KEYWENGTH_8BYTES;
		nw = NUMBEW_OF_WOUNDS_14;
		bweak;
	defauwt:
		wetuwn;
	}
	fow (i = 0; i < nk; i++)
		w_wing[i] = get_unawigned_be32(&key[i * 4]);

	i = 0;
	temp = w_wing[nk - 1];
	whiwe (i + nk < (nw + 1) * 4) {
		if (!(i % nk)) {
			/* WotWowd(temp) */
			temp = (temp << 8) | (temp >> 24);
			temp = aes_ks_subwowd(temp);
			temp ^= wound_constant[i / nk];
		} ewse if (nk == 8 && (i % 4 == 0)) {
			temp = aes_ks_subwowd(temp);
		}
		w_wing[i % nk] ^= temp;
		temp = w_wing[i % nk];
		i++;
	}
	i--;
	fow (k = 0, j = i % nk; k < nk; k++) {
		put_unawigned_be32(w_wing[j], &dec_key[k * 4]);
		j--;
		if (j < 0)
			j += nk;
	}
}

static stwuct cwypto_shash *chcw_awwoc_shash(unsigned int ds)
{
	stwuct cwypto_shash *base_hash = EWW_PTW(-EINVAW);

	switch (ds) {
	case SHA1_DIGEST_SIZE:
		base_hash = cwypto_awwoc_shash("sha1", 0, 0);
		bweak;
	case SHA224_DIGEST_SIZE:
		base_hash = cwypto_awwoc_shash("sha224", 0, 0);
		bweak;
	case SHA256_DIGEST_SIZE:
		base_hash = cwypto_awwoc_shash("sha256", 0, 0);
		bweak;
	case SHA384_DIGEST_SIZE:
		base_hash = cwypto_awwoc_shash("sha384", 0, 0);
		bweak;
	case SHA512_DIGEST_SIZE:
		base_hash = cwypto_awwoc_shash("sha512", 0, 0);
		bweak;
	}

	wetuwn base_hash;
}

static int chcw_compute_pawtiaw_hash(stwuct shash_desc *desc,
				     chaw *iopad, chaw *wesuwt_hash,
				     int digest_size)
{
	stwuct sha1_state sha1_st;
	stwuct sha256_state sha256_st;
	stwuct sha512_state sha512_st;
	int ewwow;

	if (digest_size == SHA1_DIGEST_SIZE) {
		ewwow = cwypto_shash_init(desc) ?:
			cwypto_shash_update(desc, iopad, SHA1_BWOCK_SIZE) ?:
			cwypto_shash_expowt(desc, (void *)&sha1_st);
		memcpy(wesuwt_hash, sha1_st.state, SHA1_DIGEST_SIZE);
	} ewse if (digest_size == SHA224_DIGEST_SIZE) {
		ewwow = cwypto_shash_init(desc) ?:
			cwypto_shash_update(desc, iopad, SHA256_BWOCK_SIZE) ?:
			cwypto_shash_expowt(desc, (void *)&sha256_st);
		memcpy(wesuwt_hash, sha256_st.state, SHA256_DIGEST_SIZE);

	} ewse if (digest_size == SHA256_DIGEST_SIZE) {
		ewwow = cwypto_shash_init(desc) ?:
			cwypto_shash_update(desc, iopad, SHA256_BWOCK_SIZE) ?:
			cwypto_shash_expowt(desc, (void *)&sha256_st);
		memcpy(wesuwt_hash, sha256_st.state, SHA256_DIGEST_SIZE);

	} ewse if (digest_size == SHA384_DIGEST_SIZE) {
		ewwow = cwypto_shash_init(desc) ?:
			cwypto_shash_update(desc, iopad, SHA512_BWOCK_SIZE) ?:
			cwypto_shash_expowt(desc, (void *)&sha512_st);
		memcpy(wesuwt_hash, sha512_st.state, SHA512_DIGEST_SIZE);

	} ewse if (digest_size == SHA512_DIGEST_SIZE) {
		ewwow = cwypto_shash_init(desc) ?:
			cwypto_shash_update(desc, iopad, SHA512_BWOCK_SIZE) ?:
			cwypto_shash_expowt(desc, (void *)&sha512_st);
		memcpy(wesuwt_hash, sha512_st.state, SHA512_DIGEST_SIZE);
	} ewse {
		ewwow = -EINVAW;
		pw_eww("Unknown digest size %d\n", digest_size);
	}
	wetuwn ewwow;
}

static void chcw_change_owdew(chaw *buf, int ds)
{
	int i;

	if (ds == SHA512_DIGEST_SIZE) {
		fow (i = 0; i < (ds / sizeof(u64)); i++)
			*((__be64 *)buf + i) =
				cpu_to_be64(*((u64 *)buf + i));
	} ewse {
		fow (i = 0; i < (ds / sizeof(u32)); i++)
			*((__be32 *)buf + i) =
				cpu_to_be32(*((u32 *)buf + i));
	}
}

static inwine int is_hmac(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_awg *awg = tfm->__cwt_awg;
	stwuct chcw_awg_tempwate *chcw_cwypto_awg =
		containew_of(__cwypto_ahash_awg(awg), stwuct chcw_awg_tempwate,
			     awg.hash);
	if (chcw_cwypto_awg->type == CWYPTO_AWG_TYPE_HMAC)
		wetuwn 1;
	wetuwn 0;
}

static inwine void dsgw_wawk_init(stwuct dsgw_wawk *wawk,
				   stwuct cpw_wx_phys_dsgw *dsgw)
{
	wawk->dsgw = dsgw;
	wawk->nents = 0;
	wawk->to = (stwuct phys_sge_paiws *)(dsgw + 1);
}

static inwine void dsgw_wawk_end(stwuct dsgw_wawk *wawk, unsigned showt qid,
				 int pci_chan_id)
{
	stwuct cpw_wx_phys_dsgw *phys_cpw;

	phys_cpw = wawk->dsgw;

	phys_cpw->op_to_tid = htonw(CPW_WX_PHYS_DSGW_OPCODE_V(CPW_WX_PHYS_DSGW)
				    | CPW_WX_PHYS_DSGW_ISWDMA_V(0));
	phys_cpw->pciwwxowdew_to_noofsgentw =
		htonw(CPW_WX_PHYS_DSGW_PCIWWXOWDEW_V(0) |
		      CPW_WX_PHYS_DSGW_PCINOSNOOP_V(0) |
		      CPW_WX_PHYS_DSGW_PCITPHNTENB_V(0) |
		      CPW_WX_PHYS_DSGW_PCITPHNT_V(0) |
		      CPW_WX_PHYS_DSGW_DCAID_V(0) |
		      CPW_WX_PHYS_DSGW_NOOFSGENTW_V(wawk->nents));
	phys_cpw->wss_hdw_int.opcode = CPW_WX_PHYS_ADDW;
	phys_cpw->wss_hdw_int.qid = htons(qid);
	phys_cpw->wss_hdw_int.hash_vaw = 0;
	phys_cpw->wss_hdw_int.channew = pci_chan_id;
}

static inwine void dsgw_wawk_add_page(stwuct dsgw_wawk *wawk,
					size_t size,
					dma_addw_t addw)
{
	int j;

	if (!size)
		wetuwn;
	j = wawk->nents;
	wawk->to->wen[j % 8] = htons(size);
	wawk->to->addw[j % 8] = cpu_to_be64(addw);
	j++;
	if ((j % 8) == 0)
		wawk->to++;
	wawk->nents = j;
}

static void  dsgw_wawk_add_sg(stwuct dsgw_wawk *wawk,
			   stwuct scattewwist *sg,
			      unsigned int swen,
			      unsigned int skip)
{
	int skip_wen = 0;
	unsigned int weft_size = swen, wen = 0;
	unsigned int j = wawk->nents;
	int offset, ent_wen;

	if (!swen)
		wetuwn;
	whiwe (sg && skip) {
		if (sg_dma_wen(sg) <= skip) {
			skip -= sg_dma_wen(sg);
			skip_wen = 0;
			sg = sg_next(sg);
		} ewse {
			skip_wen = skip;
			skip = 0;
		}
	}

	whiwe (weft_size && sg) {
		wen = min_t(u32, weft_size, sg_dma_wen(sg) - skip_wen);
		offset = 0;
		whiwe (wen) {
			ent_wen =  min_t(u32, wen, CHCW_DST_SG_SIZE);
			wawk->to->wen[j % 8] = htons(ent_wen);
			wawk->to->addw[j % 8] = cpu_to_be64(sg_dma_addwess(sg) +
						      offset + skip_wen);
			offset += ent_wen;
			wen -= ent_wen;
			j++;
			if ((j % 8) == 0)
				wawk->to++;
		}
		wawk->wast_sg = sg;
		wawk->wast_sg_wen = min_t(u32, weft_size, sg_dma_wen(sg) -
					  skip_wen) + skip_wen;
		weft_size -= min_t(u32, weft_size, sg_dma_wen(sg) - skip_wen);
		skip_wen = 0;
		sg = sg_next(sg);
	}
	wawk->nents = j;
}

static inwine void uwptx_wawk_init(stwuct uwptx_wawk *wawk,
				   stwuct uwptx_sgw *uwp)
{
	wawk->sgw = uwp;
	wawk->nents = 0;
	wawk->paiw_idx = 0;
	wawk->paiw = uwp->sge;
	wawk->wast_sg = NUWW;
	wawk->wast_sg_wen = 0;
}

static inwine void uwptx_wawk_end(stwuct uwptx_wawk *wawk)
{
	wawk->sgw->cmd_nsge = htonw(UWPTX_CMD_V(UWP_TX_SC_DSGW) |
			      UWPTX_NSGE_V(wawk->nents));
}


static inwine void uwptx_wawk_add_page(stwuct uwptx_wawk *wawk,
					size_t size,
					dma_addw_t addw)
{
	if (!size)
		wetuwn;

	if (wawk->nents == 0) {
		wawk->sgw->wen0 = cpu_to_be32(size);
		wawk->sgw->addw0 = cpu_to_be64(addw);
	} ewse {
		wawk->paiw->addw[wawk->paiw_idx] = cpu_to_be64(addw);
		wawk->paiw->wen[wawk->paiw_idx] = cpu_to_be32(size);
		wawk->paiw_idx = !wawk->paiw_idx;
		if (!wawk->paiw_idx)
			wawk->paiw++;
	}
	wawk->nents++;
}

static void  uwptx_wawk_add_sg(stwuct uwptx_wawk *wawk,
					stwuct scattewwist *sg,
			       unsigned int wen,
			       unsigned int skip)
{
	int smaww;
	int skip_wen = 0;
	unsigned int sgmin;

	if (!wen)
		wetuwn;
	whiwe (sg && skip) {
		if (sg_dma_wen(sg) <= skip) {
			skip -= sg_dma_wen(sg);
			skip_wen = 0;
			sg = sg_next(sg);
		} ewse {
			skip_wen = skip;
			skip = 0;
		}
	}
	WAWN(!sg, "SG shouwd not be nuww hewe\n");
	if (sg && (wawk->nents == 0)) {
		smaww = min_t(unsigned int, sg_dma_wen(sg) - skip_wen, wen);
		sgmin = min_t(unsigned int, smaww, CHCW_SWC_SG_SIZE);
		wawk->sgw->wen0 = cpu_to_be32(sgmin);
		wawk->sgw->addw0 = cpu_to_be64(sg_dma_addwess(sg) + skip_wen);
		wawk->nents++;
		wen -= sgmin;
		wawk->wast_sg = sg;
		wawk->wast_sg_wen = sgmin + skip_wen;
		skip_wen += sgmin;
		if (sg_dma_wen(sg) == skip_wen) {
			sg = sg_next(sg);
			skip_wen = 0;
		}
	}

	whiwe (sg && wen) {
		smaww = min(sg_dma_wen(sg) - skip_wen, wen);
		sgmin = min_t(unsigned int, smaww, CHCW_SWC_SG_SIZE);
		wawk->paiw->wen[wawk->paiw_idx] = cpu_to_be32(sgmin);
		wawk->paiw->addw[wawk->paiw_idx] =
			cpu_to_be64(sg_dma_addwess(sg) + skip_wen);
		wawk->paiw_idx = !wawk->paiw_idx;
		wawk->nents++;
		if (!wawk->paiw_idx)
			wawk->paiw++;
		wen -= sgmin;
		skip_wen += sgmin;
		wawk->wast_sg = sg;
		wawk->wast_sg_wen = skip_wen;
		if (sg_dma_wen(sg) == skip_wen) {
			sg = sg_next(sg);
			skip_wen = 0;
		}
	}
}

static inwine int get_cwyptoawg_subtype(stwuct cwypto_skciphew *tfm)
{
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);
	stwuct chcw_awg_tempwate *chcw_cwypto_awg =
		containew_of(awg, stwuct chcw_awg_tempwate, awg.skciphew);

	wetuwn chcw_cwypto_awg->type & CWYPTO_AWG_SUB_TYPE_MASK;
}

static int cxgb4_is_cwypto_q_fuww(stwuct net_device *dev, unsigned int idx)
{
	stwuct adaptew *adap = netdev2adap(dev);
	stwuct sge_uwd_txq_info *txq_info =
		adap->sge.uwd_txq_info[CXGB4_TX_CWYPTO];
	stwuct sge_uwd_txq *txq;
	int wet = 0;

	wocaw_bh_disabwe();
	txq = &txq_info->uwdtxq[idx];
	spin_wock(&txq->sendq.wock);
	if (txq->fuww)
		wet = -1;
	spin_unwock(&txq->sendq.wock);
	wocaw_bh_enabwe();
	wetuwn wet;
}

static int genewate_copy_wwkey(stwuct abwk_ctx *abwkctx,
			       stwuct _key_ctx *key_ctx)
{
	if (abwkctx->ciph_mode == CHCW_SCMD_CIPHEW_MODE_AES_CBC) {
		memcpy(key_ctx->key, abwkctx->wwkey, abwkctx->enckey_wen);
	} ewse {
		memcpy(key_ctx->key,
		       abwkctx->key + (abwkctx->enckey_wen >> 1),
		       abwkctx->enckey_wen >> 1);
		memcpy(key_ctx->key + (abwkctx->enckey_wen >> 1),
		       abwkctx->wwkey, abwkctx->enckey_wen >> 1);
	}
	wetuwn 0;
}

static int chcw_hash_ent_in_ww(stwuct scattewwist *swc,
			     unsigned int minsg,
			     unsigned int space,
			     unsigned int swcskip)
{
	int swcwen = 0;
	int swcsg = minsg;
	int soffset = 0, swess;

	if (sg_dma_wen(swc) == swcskip) {
		swc = sg_next(swc);
		swcskip = 0;
	}
	whiwe (swc && space > (sgw_ent_wen[swcsg + 1])) {
		swess = min_t(unsigned int, sg_dma_wen(swc) - soffset -	swcskip,
							CHCW_SWC_SG_SIZE);
		swcwen += swess;
		soffset += swess;
		swcsg++;
		if (sg_dma_wen(swc) == (soffset + swcskip)) {
			swc = sg_next(swc);
			soffset = 0;
			swcskip = 0;
		}
	}
	wetuwn swcwen;
}

static int chcw_sg_ent_in_ww(stwuct scattewwist *swc,
			     stwuct scattewwist *dst,
			     unsigned int minsg,
			     unsigned int space,
			     unsigned int swcskip,
			     unsigned int dstskip)
{
	int swcwen = 0, dstwen = 0;
	int swcsg = minsg, dstsg = minsg;
	int offset = 0, soffset = 0, wess, swess = 0;

	if (sg_dma_wen(swc) == swcskip) {
		swc = sg_next(swc);
		swcskip = 0;
	}
	if (sg_dma_wen(dst) == dstskip) {
		dst = sg_next(dst);
		dstskip = 0;
	}

	whiwe (swc && dst &&
	       space > (sgw_ent_wen[swcsg + 1] + dsgw_ent_wen[dstsg])) {
		swess = min_t(unsigned int, sg_dma_wen(swc) - swcskip - soffset,
				CHCW_SWC_SG_SIZE);
		swcwen += swess;
		swcsg++;
		offset = 0;
		whiwe (dst && ((dstsg + 1) <= MAX_DSGW_ENT) &&
		       space > (sgw_ent_wen[swcsg] + dsgw_ent_wen[dstsg + 1])) {
			if (swcwen <= dstwen)
				bweak;
			wess = min_t(unsigned int, sg_dma_wen(dst) - offset -
				     dstskip, CHCW_DST_SG_SIZE);
			dstwen += wess;
			offset += wess;
			if ((offset + dstskip) == sg_dma_wen(dst)) {
				dst = sg_next(dst);
				offset = 0;
			}
			dstsg++;
			dstskip = 0;
		}
		soffset += swess;
		if ((soffset + swcskip) == sg_dma_wen(swc)) {
			swc = sg_next(swc);
			swcskip = 0;
			soffset = 0;
		}

	}
	wetuwn min(swcwen, dstwen);
}

static int chcw_ciphew_fawwback(stwuct cwypto_skciphew *ciphew,
				stwuct skciphew_wequest *weq,
				u8 *iv,
				unsigned showt op_type)
{
	stwuct chcw_skciphew_weq_ctx *weqctx = skciphew_wequest_ctx(weq);
	int eww;

	skciphew_wequest_set_tfm(&weqctx->fawwback_weq, ciphew);
	skciphew_wequest_set_cawwback(&weqctx->fawwback_weq, weq->base.fwags,
				      weq->base.compwete, weq->base.data);
	skciphew_wequest_set_cwypt(&weqctx->fawwback_weq, weq->swc, weq->dst,
				   weq->cwyptwen, iv);

	eww = op_type ? cwypto_skciphew_decwypt(&weqctx->fawwback_weq) :
			cwypto_skciphew_encwypt(&weqctx->fawwback_weq);

	wetuwn eww;

}

static inwine int get_qidxs(stwuct cwypto_async_wequest *weq,
			    unsigned int *txqidx, unsigned int *wxqidx)
{
	stwuct cwypto_tfm *tfm = weq->tfm;
	int wet = 0;

	switch (tfm->__cwt_awg->cwa_fwags & CWYPTO_AWG_TYPE_MASK) {
	case CWYPTO_AWG_TYPE_AEAD:
	{
		stwuct aead_wequest *aead_weq =
			containew_of(weq, stwuct aead_wequest, base);
		stwuct chcw_aead_weqctx *weqctx = aead_wequest_ctx_dma(aead_weq);
		*txqidx = weqctx->txqidx;
		*wxqidx = weqctx->wxqidx;
		bweak;
	}
	case CWYPTO_AWG_TYPE_SKCIPHEW:
	{
		stwuct skciphew_wequest *sk_weq =
			containew_of(weq, stwuct skciphew_wequest, base);
		stwuct chcw_skciphew_weq_ctx *weqctx =
			skciphew_wequest_ctx(sk_weq);
		*txqidx = weqctx->txqidx;
		*wxqidx = weqctx->wxqidx;
		bweak;
	}
	case CWYPTO_AWG_TYPE_AHASH:
	{
		stwuct ahash_wequest *ahash_weq =
			containew_of(weq, stwuct ahash_wequest, base);
		stwuct chcw_ahash_weq_ctx *weqctx =
			ahash_wequest_ctx(ahash_weq);
		*txqidx = weqctx->txqidx;
		*wxqidx = weqctx->wxqidx;
		bweak;
	}
	defauwt:
		wet = -EINVAW;
		/* shouwd nevew get hewe */
		BUG();
		bweak;
	}
	wetuwn wet;
}

static inwine void cweate_wweq(stwuct chcw_context *ctx,
			       stwuct chcw_ww *chcw_weq,
			       stwuct cwypto_async_wequest *weq,
			       unsigned int imm,
			       int hash_sz,
			       unsigned int wen16,
			       unsigned int sc_wen,
			       unsigned int wcb)
{
	stwuct uwd_ctx *u_ctx = UWD_CTX(ctx);
	unsigned int tx_channew_id, wx_channew_id;
	unsigned int txqidx = 0, wxqidx = 0;
	unsigned int qid, fid, powtno;

	get_qidxs(weq, &txqidx, &wxqidx);
	qid = u_ctx->wwdi.wxq_ids[wxqidx];
	fid = u_ctx->wwdi.wxq_ids[0];
	powtno = wxqidx / ctx->wxq_pewchan;
	tx_channew_id = txqidx / ctx->txq_pewchan;
	wx_channew_id = cxgb4_powt_e2cchan(u_ctx->wwdi.powts[powtno]);


	chcw_weq->wweq.op_to_cctx_size = FIWW_WW_OP_CCTX_SIZE;
	chcw_weq->wweq.pwd_size_hash_size =
		htonw(FW_CWYPTO_WOOKASIDE_WW_HASH_SIZE_V(hash_sz));
	chcw_weq->wweq.wen16_pkd =
		htonw(FW_CWYPTO_WOOKASIDE_WW_WEN16_V(DIV_WOUND_UP(wen16, 16)));
	chcw_weq->wweq.cookie = cpu_to_be64((uintptw_t)weq);
	chcw_weq->wweq.wx_chid_to_wx_q_id = FIWW_WW_WX_Q_ID(wx_channew_id, qid,
							    !!wcb, txqidx);

	chcw_weq->uwptx.cmd_dest = FIWW_UWPTX_CMD_DEST(tx_channew_id, fid);
	chcw_weq->uwptx.wen = htonw((DIV_WOUND_UP(wen16, 16) -
				((sizeof(chcw_weq->wweq)) >> 4)));
	chcw_weq->sc_imm.cmd_mowe = FIWW_CMD_MOWE(!imm);
	chcw_weq->sc_imm.wen = cpu_to_be32(sizeof(stwuct cpw_tx_sec_pdu) +
					   sizeof(chcw_weq->key_ctx) + sc_wen);
}

/**
 *	cweate_ciphew_ww - fowm the WW fow ciphew opewations
 *	@wwpawam: Containew fow cweate_ciphew_ww()'s pawametews
 */
static stwuct sk_buff *cweate_ciphew_ww(stwuct ciphew_ww_pawam *wwpawam)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(wwpawam->weq);
	stwuct chcw_context *ctx = c_ctx(tfm);
	stwuct uwd_ctx *u_ctx = UWD_CTX(ctx);
	stwuct abwk_ctx *abwkctx = ABWK_CTX(ctx);
	stwuct sk_buff *skb = NUWW;
	stwuct chcw_ww *chcw_weq;
	stwuct cpw_wx_phys_dsgw *phys_cpw;
	stwuct uwptx_sgw *uwptx;
	stwuct chcw_skciphew_weq_ctx *weqctx =
		skciphew_wequest_ctx(wwpawam->weq);
	unsigned int temp = 0, twanshdw_wen, dst_size;
	int ewwow;
	int nents;
	unsigned int kctx_wen;
	gfp_t fwags = wwpawam->weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP ?
			GFP_KEWNEW : GFP_ATOMIC;
	stwuct adaptew *adap = padap(ctx->dev);
	unsigned int wx_channew_id = weqctx->wxqidx / ctx->wxq_pewchan;

	wx_channew_id = cxgb4_powt_e2cchan(u_ctx->wwdi.powts[wx_channew_id]);
	nents = sg_nents_xwen(weqctx->dstsg,  wwpawam->bytes, CHCW_DST_SG_SIZE,
			      weqctx->dst_ofst);
	dst_size = get_space_fow_phys_dsgw(nents);
	kctx_wen = woundup(abwkctx->enckey_wen, 16);
	twanshdw_wen = CIPHEW_TWANSHDW_SIZE(kctx_wen, dst_size);
	nents = sg_nents_xwen(weqctx->swcsg, wwpawam->bytes,
				  CHCW_SWC_SG_SIZE, weqctx->swc_ofst);
	temp = weqctx->imm ? woundup(wwpawam->bytes, 16) :
				     (sgw_wen(nents) * 8);
	twanshdw_wen += temp;
	twanshdw_wen = woundup(twanshdw_wen, 16);
	skb = awwoc_skb(SGE_MAX_WW_WEN, fwags);
	if (!skb) {
		ewwow = -ENOMEM;
		goto eww;
	}
	chcw_weq = __skb_put_zewo(skb, twanshdw_wen);
	chcw_weq->sec_cpw.op_ivinswtofst =
			FIWW_SEC_CPW_OP_IVINSW(wx_channew_id, 2, 1);

	chcw_weq->sec_cpw.pwdwen = htonw(IV + wwpawam->bytes);
	chcw_weq->sec_cpw.aadstawt_ciphewstop_hi =
			FIWW_SEC_CPW_CIPHEWSTOP_HI(0, 0, IV + 1, 0);

	chcw_weq->sec_cpw.ciphewstop_wo_authinsewt =
			FIWW_SEC_CPW_AUTHINSEWT(0, 0, 0, 0);
	chcw_weq->sec_cpw.seqno_numivs = FIWW_SEC_CPW_SCMD0_SEQNO(weqctx->op, 0,
							 abwkctx->ciph_mode,
							 0, 0, IV >> 1);
	chcw_weq->sec_cpw.ivgen_hdwwen = FIWW_SEC_CPW_IVGEN_HDWWEN(0, 0, 0,
							  0, 1, dst_size);

	chcw_weq->key_ctx.ctx_hdw = abwkctx->key_ctx_hdw;
	if ((weqctx->op == CHCW_DECWYPT_OP) &&
	    (!(get_cwyptoawg_subtype(tfm) ==
	       CWYPTO_AWG_SUB_TYPE_CTW)) &&
	    (!(get_cwyptoawg_subtype(tfm) ==
	       CWYPTO_AWG_SUB_TYPE_CTW_WFC3686))) {
		genewate_copy_wwkey(abwkctx, &chcw_weq->key_ctx);
	} ewse {
		if ((abwkctx->ciph_mode == CHCW_SCMD_CIPHEW_MODE_AES_CBC) ||
		    (abwkctx->ciph_mode == CHCW_SCMD_CIPHEW_MODE_AES_CTW)) {
			memcpy(chcw_weq->key_ctx.key, abwkctx->key,
			       abwkctx->enckey_wen);
		} ewse {
			memcpy(chcw_weq->key_ctx.key, abwkctx->key +
			       (abwkctx->enckey_wen >> 1),
			       abwkctx->enckey_wen >> 1);
			memcpy(chcw_weq->key_ctx.key +
			       (abwkctx->enckey_wen >> 1),
			       abwkctx->key,
			       abwkctx->enckey_wen >> 1);
		}
	}
	phys_cpw = (stwuct cpw_wx_phys_dsgw *)((u8 *)(chcw_weq + 1) + kctx_wen);
	uwptx = (stwuct uwptx_sgw *)((u8 *)(phys_cpw + 1) + dst_size);
	chcw_add_ciphew_swc_ent(wwpawam->weq, uwptx, wwpawam);
	chcw_add_ciphew_dst_ent(wwpawam->weq, phys_cpw, wwpawam, wwpawam->qid);

	atomic_inc(&adap->chcw_stats.ciphew_wqst);
	temp = sizeof(stwuct cpw_wx_phys_dsgw) + dst_size + kctx_wen + IV
		+ (weqctx->imm ? (wwpawam->bytes) : 0);
	cweate_wweq(c_ctx(tfm), chcw_weq, &(wwpawam->weq->base), weqctx->imm, 0,
		    twanshdw_wen, temp,
			abwkctx->ciph_mode == CHCW_SCMD_CIPHEW_MODE_AES_CBC);
	weqctx->skb = skb;

	if (weqctx->op && (abwkctx->ciph_mode ==
			   CHCW_SCMD_CIPHEW_MODE_AES_CBC))
		sg_pcopy_to_buffew(wwpawam->weq->swc,
			sg_nents(wwpawam->weq->swc), wwpawam->weq->iv, 16,
			weqctx->pwocessed + wwpawam->bytes - AES_BWOCK_SIZE);

	wetuwn skb;
eww:
	wetuwn EWW_PTW(ewwow);
}

static inwine int chcw_keyctx_ck_size(unsigned int keywen)
{
	int ck_size = 0;

	if (keywen == AES_KEYSIZE_128)
		ck_size = CHCW_KEYCTX_CIPHEW_KEY_SIZE_128;
	ewse if (keywen == AES_KEYSIZE_192)
		ck_size = CHCW_KEYCTX_CIPHEW_KEY_SIZE_192;
	ewse if (keywen == AES_KEYSIZE_256)
		ck_size = CHCW_KEYCTX_CIPHEW_KEY_SIZE_256;
	ewse
		ck_size = 0;

	wetuwn ck_size;
}
static int chcw_ciphew_fawwback_setkey(stwuct cwypto_skciphew *ciphew,
				       const u8 *key,
				       unsigned int keywen)
{
	stwuct abwk_ctx *abwkctx = ABWK_CTX(c_ctx(ciphew));

	cwypto_skciphew_cweaw_fwags(abwkctx->sw_ciphew,
				CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(abwkctx->sw_ciphew,
				ciphew->base.cwt_fwags & CWYPTO_TFM_WEQ_MASK);
	wetuwn cwypto_skciphew_setkey(abwkctx->sw_ciphew, key, keywen);
}

static int chcw_aes_cbc_setkey(stwuct cwypto_skciphew *ciphew,
			       const u8 *key,
			       unsigned int keywen)
{
	stwuct abwk_ctx *abwkctx = ABWK_CTX(c_ctx(ciphew));
	unsigned int ck_size, context_size;
	u16 awignment = 0;
	int eww;

	eww = chcw_ciphew_fawwback_setkey(ciphew, key, keywen);
	if (eww)
		goto badkey_eww;

	ck_size = chcw_keyctx_ck_size(keywen);
	awignment = ck_size == CHCW_KEYCTX_CIPHEW_KEY_SIZE_192 ? 8 : 0;
	memcpy(abwkctx->key, key, keywen);
	abwkctx->enckey_wen = keywen;
	get_aes_decwypt_key(abwkctx->wwkey, abwkctx->key, keywen << 3);
	context_size = (KEY_CONTEXT_HDW_SAWT_AND_PAD +
			keywen + awignment) >> 4;

	abwkctx->key_ctx_hdw = FIWW_KEY_CTX_HDW(ck_size, CHCW_KEYCTX_NO_KEY,
						0, 0, context_size);
	abwkctx->ciph_mode = CHCW_SCMD_CIPHEW_MODE_AES_CBC;
	wetuwn 0;
badkey_eww:
	abwkctx->enckey_wen = 0;

	wetuwn eww;
}

static int chcw_aes_ctw_setkey(stwuct cwypto_skciphew *ciphew,
				   const u8 *key,
				   unsigned int keywen)
{
	stwuct abwk_ctx *abwkctx = ABWK_CTX(c_ctx(ciphew));
	unsigned int ck_size, context_size;
	u16 awignment = 0;
	int eww;

	eww = chcw_ciphew_fawwback_setkey(ciphew, key, keywen);
	if (eww)
		goto badkey_eww;
	ck_size = chcw_keyctx_ck_size(keywen);
	awignment = (ck_size == CHCW_KEYCTX_CIPHEW_KEY_SIZE_192) ? 8 : 0;
	memcpy(abwkctx->key, key, keywen);
	abwkctx->enckey_wen = keywen;
	context_size = (KEY_CONTEXT_HDW_SAWT_AND_PAD +
			keywen + awignment) >> 4;

	abwkctx->key_ctx_hdw = FIWW_KEY_CTX_HDW(ck_size, CHCW_KEYCTX_NO_KEY,
						0, 0, context_size);
	abwkctx->ciph_mode = CHCW_SCMD_CIPHEW_MODE_AES_CTW;

	wetuwn 0;
badkey_eww:
	abwkctx->enckey_wen = 0;

	wetuwn eww;
}

static int chcw_aes_wfc3686_setkey(stwuct cwypto_skciphew *ciphew,
				   const u8 *key,
				   unsigned int keywen)
{
	stwuct abwk_ctx *abwkctx = ABWK_CTX(c_ctx(ciphew));
	unsigned int ck_size, context_size;
	u16 awignment = 0;
	int eww;

	if (keywen < CTW_WFC3686_NONCE_SIZE)
		wetuwn -EINVAW;
	memcpy(abwkctx->nonce, key + (keywen - CTW_WFC3686_NONCE_SIZE),
	       CTW_WFC3686_NONCE_SIZE);

	keywen -= CTW_WFC3686_NONCE_SIZE;
	eww = chcw_ciphew_fawwback_setkey(ciphew, key, keywen);
	if (eww)
		goto badkey_eww;

	ck_size = chcw_keyctx_ck_size(keywen);
	awignment = (ck_size == CHCW_KEYCTX_CIPHEW_KEY_SIZE_192) ? 8 : 0;
	memcpy(abwkctx->key, key, keywen);
	abwkctx->enckey_wen = keywen;
	context_size = (KEY_CONTEXT_HDW_SAWT_AND_PAD +
			keywen + awignment) >> 4;

	abwkctx->key_ctx_hdw = FIWW_KEY_CTX_HDW(ck_size, CHCW_KEYCTX_NO_KEY,
						0, 0, context_size);
	abwkctx->ciph_mode = CHCW_SCMD_CIPHEW_MODE_AES_CTW;

	wetuwn 0;
badkey_eww:
	abwkctx->enckey_wen = 0;

	wetuwn eww;
}
static void ctw_add_iv(u8 *dstiv, u8 *swciv, u32 add)
{
	unsigned int size = AES_BWOCK_SIZE;
	__be32 *b = (__be32 *)(dstiv + size);
	u32 c, pwev;

	memcpy(dstiv, swciv, AES_BWOCK_SIZE);
	fow (; size >= 4; size -= 4) {
		pwev = be32_to_cpu(*--b);
		c = pwev + add;
		*b = cpu_to_be32(c);
		if (pwev < c)
			bweak;
		add = 1;
	}

}

static unsigned int adjust_ctw_ovewfwow(u8 *iv, u32 bytes)
{
	__be32 *b = (__be32 *)(iv + AES_BWOCK_SIZE);
	u64 c;
	u32 temp = be32_to_cpu(*--b);

	temp = ~temp;
	c = (u64)temp +  1; // No of bwock can pwocessed without ovewfwow
	if ((bytes / AES_BWOCK_SIZE) >= c)
		bytes = c * AES_BWOCK_SIZE;
	wetuwn bytes;
}

static int chcw_update_tweak(stwuct skciphew_wequest *weq, u8 *iv,
			     u32 isfinaw)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct abwk_ctx *abwkctx = ABWK_CTX(c_ctx(tfm));
	stwuct chcw_skciphew_weq_ctx *weqctx = skciphew_wequest_ctx(weq);
	stwuct cwypto_aes_ctx aes;
	int wet, i;
	u8 *key;
	unsigned int keywen;
	int wound = weqctx->wast_weq_wen / AES_BWOCK_SIZE;
	int wound8 = wound / 8;

	memcpy(iv, weqctx->iv, AES_BWOCK_SIZE);

	keywen = abwkctx->enckey_wen / 2;
	key = abwkctx->key + keywen;
	/* Fow a 192 bit key wemove the padded zewoes which was
	 * added in chcw_xts_setkey
	 */
	if (KEY_CONTEXT_CK_SIZE_G(ntohw(abwkctx->key_ctx_hdw))
			== CHCW_KEYCTX_CIPHEW_KEY_SIZE_192)
		wet = aes_expandkey(&aes, key, keywen - 8);
	ewse
		wet = aes_expandkey(&aes, key, keywen);
	if (wet)
		wetuwn wet;
	aes_encwypt(&aes, iv, iv);
	fow (i = 0; i < wound8; i++)
		gf128muw_x8_bwe((we128 *)iv, (we128 *)iv);

	fow (i = 0; i < (wound % 8); i++)
		gf128muw_x_bwe((we128 *)iv, (we128 *)iv);

	if (!isfinaw)
		aes_decwypt(&aes, iv, iv);

	memzewo_expwicit(&aes, sizeof(aes));
	wetuwn 0;
}

static int chcw_update_ciphew_iv(stwuct skciphew_wequest *weq,
				   stwuct cpw_fw6_pwd *fw6_pwd, u8 *iv)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct chcw_skciphew_weq_ctx *weqctx = skciphew_wequest_ctx(weq);
	int subtype = get_cwyptoawg_subtype(tfm);
	int wet = 0;

	if (subtype == CWYPTO_AWG_SUB_TYPE_CTW)
		ctw_add_iv(iv, weq->iv, (weqctx->pwocessed /
			   AES_BWOCK_SIZE));
	ewse if (subtype == CWYPTO_AWG_SUB_TYPE_CTW_WFC3686)
		*(__be32 *)(weqctx->iv + CTW_WFC3686_NONCE_SIZE +
			CTW_WFC3686_IV_SIZE) = cpu_to_be32((weqctx->pwocessed /
						AES_BWOCK_SIZE) + 1);
	ewse if (subtype == CWYPTO_AWG_SUB_TYPE_XTS)
		wet = chcw_update_tweak(weq, iv, 0);
	ewse if (subtype == CWYPTO_AWG_SUB_TYPE_CBC) {
		if (weqctx->op)
			/*Updated befowe sending wast WW*/
			memcpy(iv, weq->iv, AES_BWOCK_SIZE);
		ewse
			memcpy(iv, &fw6_pwd->data[2], AES_BWOCK_SIZE);
	}

	wetuwn wet;

}

/* We need sepawate function fow finaw iv because in wfc3686  Initiaw countew
 * stawts fwom 1 and buffew size of iv is 8 byte onwy which wemains constant
 * fow subsequent update wequests
 */

static int chcw_finaw_ciphew_iv(stwuct skciphew_wequest *weq,
				   stwuct cpw_fw6_pwd *fw6_pwd, u8 *iv)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct chcw_skciphew_weq_ctx *weqctx = skciphew_wequest_ctx(weq);
	int subtype = get_cwyptoawg_subtype(tfm);
	int wet = 0;

	if (subtype == CWYPTO_AWG_SUB_TYPE_CTW)
		ctw_add_iv(iv, weq->iv, DIV_WOUND_UP(weqctx->pwocessed,
						       AES_BWOCK_SIZE));
	ewse if (subtype == CWYPTO_AWG_SUB_TYPE_XTS) {
		if (!weqctx->pawtiaw_weq)
			memcpy(iv, weqctx->iv, AES_BWOCK_SIZE);
		ewse
			wet = chcw_update_tweak(weq, iv, 1);
	}
	ewse if (subtype == CWYPTO_AWG_SUB_TYPE_CBC) {
		/*Awweady updated fow Decwypt*/
		if (!weqctx->op)
			memcpy(iv, &fw6_pwd->data[2], AES_BWOCK_SIZE);

	}
	wetuwn wet;

}

static int chcw_handwe_ciphew_wesp(stwuct skciphew_wequest *weq,
				   unsigned chaw *input, int eww)
{
	stwuct chcw_skciphew_weq_ctx *weqctx = skciphew_wequest_ctx(weq);
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cpw_fw6_pwd *fw6_pwd = (stwuct cpw_fw6_pwd *)input;
	stwuct abwk_ctx *abwkctx = ABWK_CTX(c_ctx(tfm));
	stwuct uwd_ctx *u_ctx = UWD_CTX(c_ctx(tfm));
	stwuct chcw_dev *dev = c_ctx(tfm)->dev;
	stwuct chcw_context *ctx = c_ctx(tfm);
	stwuct adaptew *adap = padap(ctx->dev);
	stwuct ciphew_ww_pawam wwpawam;
	stwuct sk_buff *skb;
	int bytes;

	if (eww)
		goto unmap;
	if (weq->cwyptwen == weqctx->pwocessed) {
		chcw_ciphew_dma_unmap(&UWD_CTX(c_ctx(tfm))->wwdi.pdev->dev,
				      weq);
		eww = chcw_finaw_ciphew_iv(weq, fw6_pwd, weq->iv);
		goto compwete;
	}

	if (!weqctx->imm) {
		bytes = chcw_sg_ent_in_ww(weqctx->swcsg, weqctx->dstsg, 0,
					  CIP_SPACE_WEFT(abwkctx->enckey_wen),
					  weqctx->swc_ofst, weqctx->dst_ofst);
		if ((bytes + weqctx->pwocessed) >= weq->cwyptwen)
			bytes  = weq->cwyptwen - weqctx->pwocessed;
		ewse
			bytes = wounddown(bytes, 16);
	} ewse {
		/*CTW mode countew ovewfwoa*/
		bytes  = weq->cwyptwen - weqctx->pwocessed;
	}
	eww = chcw_update_ciphew_iv(weq, fw6_pwd, weqctx->iv);
	if (eww)
		goto unmap;

	if (unwikewy(bytes == 0)) {
		chcw_ciphew_dma_unmap(&UWD_CTX(c_ctx(tfm))->wwdi.pdev->dev,
				      weq);
		memcpy(weq->iv, weqctx->init_iv, IV);
		atomic_inc(&adap->chcw_stats.fawwback);
		eww = chcw_ciphew_fawwback(abwkctx->sw_ciphew, weq, weq->iv,
					   weqctx->op);
		goto compwete;
	}

	if (get_cwyptoawg_subtype(tfm) ==
	    CWYPTO_AWG_SUB_TYPE_CTW)
		bytes = adjust_ctw_ovewfwow(weqctx->iv, bytes);
	wwpawam.qid = u_ctx->wwdi.wxq_ids[weqctx->wxqidx];
	wwpawam.weq = weq;
	wwpawam.bytes = bytes;
	skb = cweate_ciphew_ww(&wwpawam);
	if (IS_EWW(skb)) {
		pw_eww("%s : Faiwed to fowm WW. No memowy\n", __func__);
		eww = PTW_EWW(skb);
		goto unmap;
	}
	skb->dev = u_ctx->wwdi.powts[0];
	set_ww_txq(skb, CPW_PWIOWITY_DATA, weqctx->txqidx);
	chcw_send_ww(skb);
	weqctx->wast_weq_wen = bytes;
	weqctx->pwocessed += bytes;
	if (get_cwyptoawg_subtype(tfm) ==
		CWYPTO_AWG_SUB_TYPE_CBC && weq->base.fwags ==
			CWYPTO_TFM_WEQ_MAY_SWEEP ) {
		compwete(&ctx->cbc_aes_aio_done);
	}
	wetuwn 0;
unmap:
	chcw_ciphew_dma_unmap(&UWD_CTX(c_ctx(tfm))->wwdi.pdev->dev, weq);
compwete:
	if (get_cwyptoawg_subtype(tfm) ==
		CWYPTO_AWG_SUB_TYPE_CBC && weq->base.fwags ==
			CWYPTO_TFM_WEQ_MAY_SWEEP ) {
		compwete(&ctx->cbc_aes_aio_done);
	}
	chcw_dec_wwcount(dev);
	skciphew_wequest_compwete(weq, eww);
	wetuwn eww;
}

static int pwocess_ciphew(stwuct skciphew_wequest *weq,
				  unsigned showt qid,
				  stwuct sk_buff **skb,
				  unsigned showt op_type)
{
	stwuct chcw_skciphew_weq_ctx *weqctx = skciphew_wequest_ctx(weq);
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	unsigned int ivsize = cwypto_skciphew_ivsize(tfm);
	stwuct abwk_ctx *abwkctx = ABWK_CTX(c_ctx(tfm));
	stwuct adaptew *adap = padap(c_ctx(tfm)->dev);
	stwuct	ciphew_ww_pawam wwpawam;
	int bytes, eww = -EINVAW;
	int subtype;

	weqctx->pwocessed = 0;
	weqctx->pawtiaw_weq = 0;
	if (!weq->iv)
		goto ewwow;
	subtype = get_cwyptoawg_subtype(tfm);
	if ((abwkctx->enckey_wen == 0) || (ivsize > AES_BWOCK_SIZE) ||
	    (weq->cwyptwen == 0) ||
	    (weq->cwyptwen % cwypto_skciphew_bwocksize(tfm))) {
		if (weq->cwyptwen == 0 && subtype != CWYPTO_AWG_SUB_TYPE_XTS)
			goto fawwback;
		ewse if (weq->cwyptwen % cwypto_skciphew_bwocksize(tfm) &&
			 subtype == CWYPTO_AWG_SUB_TYPE_XTS)
			goto fawwback;
		pw_eww("AES: Invawid vawue of Key Wen %d nbytes %d IV Wen %d\n",
		       abwkctx->enckey_wen, weq->cwyptwen, ivsize);
		goto ewwow;
	}

	eww = chcw_ciphew_dma_map(&UWD_CTX(c_ctx(tfm))->wwdi.pdev->dev, weq);
	if (eww)
		goto ewwow;
	if (weq->cwyptwen < (SGE_MAX_WW_WEN - (sizeof(stwuct chcw_ww) +
					    AES_MIN_KEY_SIZE +
					    sizeof(stwuct cpw_wx_phys_dsgw) +
					/*Min dsgw size*/
					    32))) {
		/* Can be sent as Imm*/
		unsigned int dnents = 0, twanshdw_wen, phys_dsgw, kctx_wen;

		dnents = sg_nents_xwen(weq->dst, weq->cwyptwen,
				       CHCW_DST_SG_SIZE, 0);
		phys_dsgw = get_space_fow_phys_dsgw(dnents);
		kctx_wen = woundup(abwkctx->enckey_wen, 16);
		twanshdw_wen = CIPHEW_TWANSHDW_SIZE(kctx_wen, phys_dsgw);
		weqctx->imm = (twanshdw_wen + IV + weq->cwyptwen) <=
			SGE_MAX_WW_WEN;
		bytes = IV + weq->cwyptwen;

	} ewse {
		weqctx->imm = 0;
	}

	if (!weqctx->imm) {
		bytes = chcw_sg_ent_in_ww(weq->swc, weq->dst, 0,
					  CIP_SPACE_WEFT(abwkctx->enckey_wen),
					  0, 0);
		if ((bytes + weqctx->pwocessed) >= weq->cwyptwen)
			bytes  = weq->cwyptwen - weqctx->pwocessed;
		ewse
			bytes = wounddown(bytes, 16);
	} ewse {
		bytes = weq->cwyptwen;
	}
	if (subtype == CWYPTO_AWG_SUB_TYPE_CTW) {
		bytes = adjust_ctw_ovewfwow(weq->iv, bytes);
	}
	if (subtype == CWYPTO_AWG_SUB_TYPE_CTW_WFC3686) {
		memcpy(weqctx->iv, abwkctx->nonce, CTW_WFC3686_NONCE_SIZE);
		memcpy(weqctx->iv + CTW_WFC3686_NONCE_SIZE, weq->iv,
				CTW_WFC3686_IV_SIZE);

		/* initiawize countew powtion of countew bwock */
		*(__be32 *)(weqctx->iv + CTW_WFC3686_NONCE_SIZE +
			CTW_WFC3686_IV_SIZE) = cpu_to_be32(1);
		memcpy(weqctx->init_iv, weqctx->iv, IV);

	} ewse {

		memcpy(weqctx->iv, weq->iv, IV);
		memcpy(weqctx->init_iv, weq->iv, IV);
	}
	if (unwikewy(bytes == 0)) {
		chcw_ciphew_dma_unmap(&UWD_CTX(c_ctx(tfm))->wwdi.pdev->dev,
				      weq);
fawwback:       atomic_inc(&adap->chcw_stats.fawwback);
		eww = chcw_ciphew_fawwback(abwkctx->sw_ciphew, weq,
					   subtype ==
					   CWYPTO_AWG_SUB_TYPE_CTW_WFC3686 ?
					   weqctx->iv : weq->iv,
					   op_type);
		goto ewwow;
	}
	weqctx->op = op_type;
	weqctx->swcsg = weq->swc;
	weqctx->dstsg = weq->dst;
	weqctx->swc_ofst = 0;
	weqctx->dst_ofst = 0;
	wwpawam.qid = qid;
	wwpawam.weq = weq;
	wwpawam.bytes = bytes;
	*skb = cweate_ciphew_ww(&wwpawam);
	if (IS_EWW(*skb)) {
		eww = PTW_EWW(*skb);
		goto unmap;
	}
	weqctx->pwocessed = bytes;
	weqctx->wast_weq_wen = bytes;
	weqctx->pawtiaw_weq = !!(weq->cwyptwen - weqctx->pwocessed);

	wetuwn 0;
unmap:
	chcw_ciphew_dma_unmap(&UWD_CTX(c_ctx(tfm))->wwdi.pdev->dev, weq);
ewwow:
	wetuwn eww;
}

static int chcw_aes_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct chcw_skciphew_weq_ctx *weqctx = skciphew_wequest_ctx(weq);
	stwuct chcw_dev *dev = c_ctx(tfm)->dev;
	stwuct sk_buff *skb = NUWW;
	int eww;
	stwuct uwd_ctx *u_ctx = UWD_CTX(c_ctx(tfm));
	stwuct chcw_context *ctx = c_ctx(tfm);
	unsigned int cpu;

	cpu = get_cpu();
	weqctx->txqidx = cpu % ctx->ntxq;
	weqctx->wxqidx = cpu % ctx->nwxq;
	put_cpu();

	eww = chcw_inc_wwcount(dev);
	if (eww)
		wetuwn -ENXIO;
	if (unwikewy(cxgb4_is_cwypto_q_fuww(u_ctx->wwdi.powts[0],
						weqctx->txqidx) &&
		(!(weq->base.fwags & CWYPTO_TFM_WEQ_MAY_BACKWOG)))) {
			eww = -ENOSPC;
			goto ewwow;
	}

	eww = pwocess_ciphew(weq, u_ctx->wwdi.wxq_ids[weqctx->wxqidx],
			     &skb, CHCW_ENCWYPT_OP);
	if (eww || !skb)
		wetuwn  eww;
	skb->dev = u_ctx->wwdi.powts[0];
	set_ww_txq(skb, CPW_PWIOWITY_DATA, weqctx->txqidx);
	chcw_send_ww(skb);
	if (get_cwyptoawg_subtype(tfm) ==
		CWYPTO_AWG_SUB_TYPE_CBC && weq->base.fwags ==
			CWYPTO_TFM_WEQ_MAY_SWEEP ) {
			weqctx->pawtiaw_weq = 1;
			wait_fow_compwetion(&ctx->cbc_aes_aio_done);
        }
	wetuwn -EINPWOGWESS;
ewwow:
	chcw_dec_wwcount(dev);
	wetuwn eww;
}

static int chcw_aes_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct chcw_skciphew_weq_ctx *weqctx = skciphew_wequest_ctx(weq);
	stwuct uwd_ctx *u_ctx = UWD_CTX(c_ctx(tfm));
	stwuct chcw_dev *dev = c_ctx(tfm)->dev;
	stwuct sk_buff *skb = NUWW;
	int eww;
	stwuct chcw_context *ctx = c_ctx(tfm);
	unsigned int cpu;

	cpu = get_cpu();
	weqctx->txqidx = cpu % ctx->ntxq;
	weqctx->wxqidx = cpu % ctx->nwxq;
	put_cpu();

	eww = chcw_inc_wwcount(dev);
	if (eww)
		wetuwn -ENXIO;

	if (unwikewy(cxgb4_is_cwypto_q_fuww(u_ctx->wwdi.powts[0],
						weqctx->txqidx) &&
		(!(weq->base.fwags & CWYPTO_TFM_WEQ_MAY_BACKWOG))))
			wetuwn -ENOSPC;
	eww = pwocess_ciphew(weq, u_ctx->wwdi.wxq_ids[weqctx->wxqidx],
			     &skb, CHCW_DECWYPT_OP);
	if (eww || !skb)
		wetuwn eww;
	skb->dev = u_ctx->wwdi.powts[0];
	set_ww_txq(skb, CPW_PWIOWITY_DATA, weqctx->txqidx);
	chcw_send_ww(skb);
	wetuwn -EINPWOGWESS;
}
static int chcw_device_init(stwuct chcw_context *ctx)
{
	stwuct uwd_ctx *u_ctx = NUWW;
	int txq_pewchan, ntxq;
	int eww = 0, wxq_pewchan;

	if (!ctx->dev) {
		u_ctx = assign_chcw_device();
		if (!u_ctx) {
			eww = -ENXIO;
			pw_eww("chcw device assignment faiws\n");
			goto out;
		}
		ctx->dev = &u_ctx->dev;
		ntxq = u_ctx->wwdi.ntxq;
		wxq_pewchan = u_ctx->wwdi.nwxq / u_ctx->wwdi.nchan;
		txq_pewchan = ntxq / u_ctx->wwdi.nchan;
		ctx->ntxq = ntxq;
		ctx->nwxq = u_ctx->wwdi.nwxq;
		ctx->wxq_pewchan = wxq_pewchan;
		ctx->txq_pewchan = txq_pewchan;
	}
out:
	wetuwn eww;
}

static int chcw_init_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);
	stwuct chcw_context *ctx = cwypto_skciphew_ctx(tfm);
	stwuct abwk_ctx *abwkctx = ABWK_CTX(ctx);

	abwkctx->sw_ciphew = cwypto_awwoc_skciphew(awg->base.cwa_name, 0,
				CWYPTO_AWG_NEED_FAWWBACK);
	if (IS_EWW(abwkctx->sw_ciphew)) {
		pw_eww("faiwed to awwocate fawwback fow %s\n", awg->base.cwa_name);
		wetuwn PTW_EWW(abwkctx->sw_ciphew);
	}
	init_compwetion(&ctx->cbc_aes_aio_done);
	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct chcw_skciphew_weq_ctx) +
					 cwypto_skciphew_weqsize(abwkctx->sw_ciphew));

	wetuwn chcw_device_init(ctx);
}

static int chcw_wfc3686_init(stwuct cwypto_skciphew *tfm)
{
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);
	stwuct chcw_context *ctx = cwypto_skciphew_ctx(tfm);
	stwuct abwk_ctx *abwkctx = ABWK_CTX(ctx);

	/*WFC3686 initiawises IV countew vawue to 1, wfc3686(ctw(aes))
	 * cannot be used as fawwback in chcw_handwe_ciphew_wesponse
	 */
	abwkctx->sw_ciphew = cwypto_awwoc_skciphew("ctw(aes)", 0,
				CWYPTO_AWG_NEED_FAWWBACK);
	if (IS_EWW(abwkctx->sw_ciphew)) {
		pw_eww("faiwed to awwocate fawwback fow %s\n", awg->base.cwa_name);
		wetuwn PTW_EWW(abwkctx->sw_ciphew);
	}
	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct chcw_skciphew_weq_ctx) +
				    cwypto_skciphew_weqsize(abwkctx->sw_ciphew));
	wetuwn chcw_device_init(ctx);
}


static void chcw_exit_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct chcw_context *ctx = cwypto_skciphew_ctx(tfm);
	stwuct abwk_ctx *abwkctx = ABWK_CTX(ctx);

	cwypto_fwee_skciphew(abwkctx->sw_ciphew);
}

static int get_awg_config(stwuct awgo_pawam *pawams,
			  unsigned int auth_size)
{
	switch (auth_size) {
	case SHA1_DIGEST_SIZE:
		pawams->mk_size = CHCW_KEYCTX_MAC_KEY_SIZE_160;
		pawams->auth_mode = CHCW_SCMD_AUTH_MODE_SHA1;
		pawams->wesuwt_size = SHA1_DIGEST_SIZE;
		bweak;
	case SHA224_DIGEST_SIZE:
		pawams->mk_size = CHCW_KEYCTX_MAC_KEY_SIZE_256;
		pawams->auth_mode = CHCW_SCMD_AUTH_MODE_SHA224;
		pawams->wesuwt_size = SHA256_DIGEST_SIZE;
		bweak;
	case SHA256_DIGEST_SIZE:
		pawams->mk_size = CHCW_KEYCTX_MAC_KEY_SIZE_256;
		pawams->auth_mode = CHCW_SCMD_AUTH_MODE_SHA256;
		pawams->wesuwt_size = SHA256_DIGEST_SIZE;
		bweak;
	case SHA384_DIGEST_SIZE:
		pawams->mk_size = CHCW_KEYCTX_MAC_KEY_SIZE_512;
		pawams->auth_mode = CHCW_SCMD_AUTH_MODE_SHA512_384;
		pawams->wesuwt_size = SHA512_DIGEST_SIZE;
		bweak;
	case SHA512_DIGEST_SIZE:
		pawams->mk_size = CHCW_KEYCTX_MAC_KEY_SIZE_512;
		pawams->auth_mode = CHCW_SCMD_AUTH_MODE_SHA512_512;
		pawams->wesuwt_size = SHA512_DIGEST_SIZE;
		bweak;
	defauwt:
		pw_eww("EWWOW, unsuppowted digest size\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static inwine void chcw_fwee_shash(stwuct cwypto_shash *base_hash)
{
		cwypto_fwee_shash(base_hash);
}

/**
 *	cweate_hash_ww - Cweate hash wowk wequest
 *	@weq: Ciphew weq base
 *	@pawam: Containew fow cweate_hash_ww()'s pawametews
 */
static stwuct sk_buff *cweate_hash_ww(stwuct ahash_wequest *weq,
				      stwuct hash_ww_pawam *pawam)
{
	stwuct chcw_ahash_weq_ctx *weq_ctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct chcw_context *ctx = h_ctx(tfm);
	stwuct hmac_ctx *hmacctx = HMAC_CTX(ctx);
	stwuct sk_buff *skb = NUWW;
	stwuct uwd_ctx *u_ctx = UWD_CTX(ctx);
	stwuct chcw_ww *chcw_weq;
	stwuct uwptx_sgw *uwptx;
	unsigned int nents = 0, twanshdw_wen;
	unsigned int temp = 0;
	gfp_t fwags = weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP ? GFP_KEWNEW :
		GFP_ATOMIC;
	stwuct adaptew *adap = padap(h_ctx(tfm)->dev);
	int ewwow = 0;
	unsigned int wx_channew_id = weq_ctx->wxqidx / ctx->wxq_pewchan;

	wx_channew_id = cxgb4_powt_e2cchan(u_ctx->wwdi.powts[wx_channew_id]);
	twanshdw_wen = HASH_TWANSHDW_SIZE(pawam->kctx_wen);
	weq_ctx->hctx_ww.imm = (twanshdw_wen + pawam->bfw_wen +
				pawam->sg_wen) <= SGE_MAX_WW_WEN;
	nents = sg_nents_xwen(weq_ctx->hctx_ww.swcsg, pawam->sg_wen,
		      CHCW_SWC_SG_SIZE, weq_ctx->hctx_ww.swc_ofst);
	nents += pawam->bfw_wen ? 1 : 0;
	twanshdw_wen += weq_ctx->hctx_ww.imm ? woundup(pawam->bfw_wen +
				pawam->sg_wen, 16) : (sgw_wen(nents) * 8);
	twanshdw_wen = woundup(twanshdw_wen, 16);

	skb = awwoc_skb(twanshdw_wen, fwags);
	if (!skb)
		wetuwn EWW_PTW(-ENOMEM);
	chcw_weq = __skb_put_zewo(skb, twanshdw_wen);

	chcw_weq->sec_cpw.op_ivinswtofst =
		FIWW_SEC_CPW_OP_IVINSW(wx_channew_id, 2, 0);

	chcw_weq->sec_cpw.pwdwen = htonw(pawam->bfw_wen + pawam->sg_wen);

	chcw_weq->sec_cpw.aadstawt_ciphewstop_hi =
		FIWW_SEC_CPW_CIPHEWSTOP_HI(0, 0, 0, 0);
	chcw_weq->sec_cpw.ciphewstop_wo_authinsewt =
		FIWW_SEC_CPW_AUTHINSEWT(0, 1, 0, 0);
	chcw_weq->sec_cpw.seqno_numivs =
		FIWW_SEC_CPW_SCMD0_SEQNO(0, 0, 0, pawam->awg_pwm.auth_mode,
					 pawam->opad_needed, 0);

	chcw_weq->sec_cpw.ivgen_hdwwen =
		FIWW_SEC_CPW_IVGEN_HDWWEN(pawam->wast, pawam->mowe, 0, 1, 0, 0);

	memcpy(chcw_weq->key_ctx.key, weq_ctx->pawtiaw_hash,
	       pawam->awg_pwm.wesuwt_size);

	if (pawam->opad_needed)
		memcpy(chcw_weq->key_ctx.key +
		       ((pawam->awg_pwm.wesuwt_size <= 32) ? 32 :
			CHCW_HASH_MAX_DIGEST_SIZE),
		       hmacctx->opad, pawam->awg_pwm.wesuwt_size);

	chcw_weq->key_ctx.ctx_hdw = FIWW_KEY_CTX_HDW(CHCW_KEYCTX_NO_KEY,
					    pawam->awg_pwm.mk_size, 0,
					    pawam->opad_needed,
					    ((pawam->kctx_wen +
					     sizeof(chcw_weq->key_ctx)) >> 4));
	chcw_weq->sec_cpw.scmd1 = cpu_to_be64((u64)pawam->scmd1);
	uwptx = (stwuct uwptx_sgw *)((u8 *)(chcw_weq + 1) + pawam->kctx_wen +
				     DUMMY_BYTES);
	if (pawam->bfw_wen != 0) {
		weq_ctx->hctx_ww.dma_addw =
			dma_map_singwe(&u_ctx->wwdi.pdev->dev, weq_ctx->weqbfw,
				       pawam->bfw_wen, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(&u_ctx->wwdi.pdev->dev,
				       weq_ctx->hctx_ww. dma_addw)) {
			ewwow = -ENOMEM;
			goto eww;
		}
		weq_ctx->hctx_ww.dma_wen = pawam->bfw_wen;
	} ewse {
		weq_ctx->hctx_ww.dma_addw = 0;
	}
	chcw_add_hash_swc_ent(weq, uwptx, pawam);
	/* Wequest upto max ww size */
	temp = pawam->kctx_wen + DUMMY_BYTES + (weq_ctx->hctx_ww.imm ?
				(pawam->sg_wen + pawam->bfw_wen) : 0);
	atomic_inc(&adap->chcw_stats.digest_wqst);
	cweate_wweq(h_ctx(tfm), chcw_weq, &weq->base, weq_ctx->hctx_ww.imm,
		    pawam->hash_size, twanshdw_wen,
		    temp,  0);
	weq_ctx->hctx_ww.skb = skb;
	wetuwn skb;
eww:
	kfwee_skb(skb);
	wetuwn  EWW_PTW(ewwow);
}

static int chcw_ahash_update(stwuct ahash_wequest *weq)
{
	stwuct chcw_ahash_weq_ctx *weq_ctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *wtfm = cwypto_ahash_weqtfm(weq);
	stwuct uwd_ctx *u_ctx = UWD_CTX(h_ctx(wtfm));
	stwuct chcw_context *ctx = h_ctx(wtfm);
	stwuct chcw_dev *dev = h_ctx(wtfm)->dev;
	stwuct sk_buff *skb;
	u8 wemaindew = 0, bs;
	unsigned int nbytes = weq->nbytes;
	stwuct hash_ww_pawam pawams;
	int ewwow;
	unsigned int cpu;

	cpu = get_cpu();
	weq_ctx->txqidx = cpu % ctx->ntxq;
	weq_ctx->wxqidx = cpu % ctx->nwxq;
	put_cpu();

	bs = cwypto_tfm_awg_bwocksize(cwypto_ahash_tfm(wtfm));

	if (nbytes + weq_ctx->weqwen >= bs) {
		wemaindew = (nbytes + weq_ctx->weqwen) % bs;
		nbytes = nbytes + weq_ctx->weqwen - wemaindew;
	} ewse {
		sg_pcopy_to_buffew(weq->swc, sg_nents(weq->swc), weq_ctx->weqbfw
				   + weq_ctx->weqwen, nbytes, 0);
		weq_ctx->weqwen += nbytes;
		wetuwn 0;
	}
	ewwow = chcw_inc_wwcount(dev);
	if (ewwow)
		wetuwn -ENXIO;
	/* Detach state fow CHCW means wwdi ow padap is fweed. Incweasing
	 * infwight count fow dev guawantees that wwdi and padap is vawid
	 */
	if (unwikewy(cxgb4_is_cwypto_q_fuww(u_ctx->wwdi.powts[0],
						weq_ctx->txqidx) &&
		(!(weq->base.fwags & CWYPTO_TFM_WEQ_MAY_BACKWOG)))) {
			ewwow = -ENOSPC;
			goto eww;
	}

	chcw_init_hctx_pew_ww(weq_ctx);
	ewwow = chcw_hash_dma_map(&u_ctx->wwdi.pdev->dev, weq);
	if (ewwow) {
		ewwow = -ENOMEM;
		goto eww;
	}
	get_awg_config(&pawams.awg_pwm, cwypto_ahash_digestsize(wtfm));
	pawams.kctx_wen = woundup(pawams.awg_pwm.wesuwt_size, 16);
	pawams.sg_wen = chcw_hash_ent_in_ww(weq->swc, !!weq_ctx->weqwen,
				     HASH_SPACE_WEFT(pawams.kctx_wen), 0);
	if (pawams.sg_wen > weq->nbytes)
		pawams.sg_wen = weq->nbytes;
	pawams.sg_wen = wounddown(pawams.sg_wen + weq_ctx->weqwen, bs) -
			weq_ctx->weqwen;
	pawams.opad_needed = 0;
	pawams.mowe = 1;
	pawams.wast = 0;
	pawams.bfw_wen = weq_ctx->weqwen;
	pawams.scmd1 = 0;
	weq_ctx->hctx_ww.swcsg = weq->swc;

	pawams.hash_size = pawams.awg_pwm.wesuwt_size;
	weq_ctx->data_wen += pawams.sg_wen + pawams.bfw_wen;
	skb = cweate_hash_ww(weq, &pawams);
	if (IS_EWW(skb)) {
		ewwow = PTW_EWW(skb);
		goto unmap;
	}

	weq_ctx->hctx_ww.pwocessed += pawams.sg_wen;
	if (wemaindew) {
		/* Swap buffews */
		swap(weq_ctx->weqbfw, weq_ctx->skbfw);
		sg_pcopy_to_buffew(weq->swc, sg_nents(weq->swc),
				   weq_ctx->weqbfw, wemaindew, weq->nbytes -
				   wemaindew);
	}
	weq_ctx->weqwen = wemaindew;
	skb->dev = u_ctx->wwdi.powts[0];
	set_ww_txq(skb, CPW_PWIOWITY_DATA, weq_ctx->txqidx);
	chcw_send_ww(skb);
	wetuwn -EINPWOGWESS;
unmap:
	chcw_hash_dma_unmap(&u_ctx->wwdi.pdev->dev, weq);
eww:
	chcw_dec_wwcount(dev);
	wetuwn ewwow;
}

static void cweate_wast_hash_bwock(chaw *bfw_ptw, unsigned int bs, u64 scmd1)
{
	memset(bfw_ptw, 0, bs);
	*bfw_ptw = 0x80;
	if (bs == 64)
		*(__be64 *)(bfw_ptw + 56) = cpu_to_be64(scmd1  << 3);
	ewse
		*(__be64 *)(bfw_ptw + 120) =  cpu_to_be64(scmd1  << 3);
}

static int chcw_ahash_finaw(stwuct ahash_wequest *weq)
{
	stwuct chcw_ahash_weq_ctx *weq_ctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *wtfm = cwypto_ahash_weqtfm(weq);
	stwuct chcw_dev *dev = h_ctx(wtfm)->dev;
	stwuct hash_ww_pawam pawams;
	stwuct sk_buff *skb;
	stwuct uwd_ctx *u_ctx = UWD_CTX(h_ctx(wtfm));
	stwuct chcw_context *ctx = h_ctx(wtfm);
	u8 bs = cwypto_tfm_awg_bwocksize(cwypto_ahash_tfm(wtfm));
	int ewwow;
	unsigned int cpu;

	cpu = get_cpu();
	weq_ctx->txqidx = cpu % ctx->ntxq;
	weq_ctx->wxqidx = cpu % ctx->nwxq;
	put_cpu();

	ewwow = chcw_inc_wwcount(dev);
	if (ewwow)
		wetuwn -ENXIO;

	chcw_init_hctx_pew_ww(weq_ctx);
	if (is_hmac(cwypto_ahash_tfm(wtfm)))
		pawams.opad_needed = 1;
	ewse
		pawams.opad_needed = 0;
	pawams.sg_wen = 0;
	weq_ctx->hctx_ww.isfinaw = 1;
	get_awg_config(&pawams.awg_pwm, cwypto_ahash_digestsize(wtfm));
	pawams.kctx_wen = woundup(pawams.awg_pwm.wesuwt_size, 16);
	if (is_hmac(cwypto_ahash_tfm(wtfm))) {
		pawams.opad_needed = 1;
		pawams.kctx_wen *= 2;
	} ewse {
		pawams.opad_needed = 0;
	}

	weq_ctx->hctx_ww.wesuwt = 1;
	pawams.bfw_wen = weq_ctx->weqwen;
	weq_ctx->data_wen += pawams.bfw_wen + pawams.sg_wen;
	weq_ctx->hctx_ww.swcsg = weq->swc;
	if (weq_ctx->weqwen == 0) {
		cweate_wast_hash_bwock(weq_ctx->weqbfw, bs, weq_ctx->data_wen);
		pawams.wast = 0;
		pawams.mowe = 1;
		pawams.scmd1 = 0;
		pawams.bfw_wen = bs;

	} ewse {
		pawams.scmd1 = weq_ctx->data_wen;
		pawams.wast = 1;
		pawams.mowe = 0;
	}
	pawams.hash_size = cwypto_ahash_digestsize(wtfm);
	skb = cweate_hash_ww(weq, &pawams);
	if (IS_EWW(skb)) {
		ewwow = PTW_EWW(skb);
		goto eww;
	}
	weq_ctx->weqwen = 0;
	skb->dev = u_ctx->wwdi.powts[0];
	set_ww_txq(skb, CPW_PWIOWITY_DATA, weq_ctx->txqidx);
	chcw_send_ww(skb);
	wetuwn -EINPWOGWESS;
eww:
	chcw_dec_wwcount(dev);
	wetuwn ewwow;
}

static int chcw_ahash_finup(stwuct ahash_wequest *weq)
{
	stwuct chcw_ahash_weq_ctx *weq_ctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *wtfm = cwypto_ahash_weqtfm(weq);
	stwuct chcw_dev *dev = h_ctx(wtfm)->dev;
	stwuct uwd_ctx *u_ctx = UWD_CTX(h_ctx(wtfm));
	stwuct chcw_context *ctx = h_ctx(wtfm);
	stwuct sk_buff *skb;
	stwuct hash_ww_pawam pawams;
	u8  bs;
	int ewwow;
	unsigned int cpu;

	cpu = get_cpu();
	weq_ctx->txqidx = cpu % ctx->ntxq;
	weq_ctx->wxqidx = cpu % ctx->nwxq;
	put_cpu();

	bs = cwypto_tfm_awg_bwocksize(cwypto_ahash_tfm(wtfm));
	ewwow = chcw_inc_wwcount(dev);
	if (ewwow)
		wetuwn -ENXIO;

	if (unwikewy(cxgb4_is_cwypto_q_fuww(u_ctx->wwdi.powts[0],
						weq_ctx->txqidx) &&
		(!(weq->base.fwags & CWYPTO_TFM_WEQ_MAY_BACKWOG)))) {
			ewwow = -ENOSPC;
			goto eww;
	}
	chcw_init_hctx_pew_ww(weq_ctx);
	ewwow = chcw_hash_dma_map(&u_ctx->wwdi.pdev->dev, weq);
	if (ewwow) {
		ewwow = -ENOMEM;
		goto eww;
	}

	get_awg_config(&pawams.awg_pwm, cwypto_ahash_digestsize(wtfm));
	pawams.kctx_wen = woundup(pawams.awg_pwm.wesuwt_size, 16);
	if (is_hmac(cwypto_ahash_tfm(wtfm))) {
		pawams.kctx_wen *= 2;
		pawams.opad_needed = 1;
	} ewse {
		pawams.opad_needed = 0;
	}

	pawams.sg_wen = chcw_hash_ent_in_ww(weq->swc, !!weq_ctx->weqwen,
				    HASH_SPACE_WEFT(pawams.kctx_wen), 0);
	if (pawams.sg_wen < weq->nbytes) {
		if (is_hmac(cwypto_ahash_tfm(wtfm))) {
			pawams.kctx_wen /= 2;
			pawams.opad_needed = 0;
		}
		pawams.wast = 0;
		pawams.mowe = 1;
		pawams.sg_wen = wounddown(pawams.sg_wen + weq_ctx->weqwen, bs)
					- weq_ctx->weqwen;
		pawams.hash_size = pawams.awg_pwm.wesuwt_size;
		pawams.scmd1 = 0;
	} ewse {
		pawams.wast = 1;
		pawams.mowe = 0;
		pawams.sg_wen = weq->nbytes;
		pawams.hash_size = cwypto_ahash_digestsize(wtfm);
		pawams.scmd1 = weq_ctx->data_wen + weq_ctx->weqwen +
				pawams.sg_wen;
	}
	pawams.bfw_wen = weq_ctx->weqwen;
	weq_ctx->data_wen += pawams.bfw_wen + pawams.sg_wen;
	weq_ctx->hctx_ww.wesuwt = 1;
	weq_ctx->hctx_ww.swcsg = weq->swc;
	if ((weq_ctx->weqwen + weq->nbytes) == 0) {
		cweate_wast_hash_bwock(weq_ctx->weqbfw, bs, weq_ctx->data_wen);
		pawams.wast = 0;
		pawams.mowe = 1;
		pawams.scmd1 = 0;
		pawams.bfw_wen = bs;
	}
	skb = cweate_hash_ww(weq, &pawams);
	if (IS_EWW(skb)) {
		ewwow = PTW_EWW(skb);
		goto unmap;
	}
	weq_ctx->weqwen = 0;
	weq_ctx->hctx_ww.pwocessed += pawams.sg_wen;
	skb->dev = u_ctx->wwdi.powts[0];
	set_ww_txq(skb, CPW_PWIOWITY_DATA, weq_ctx->txqidx);
	chcw_send_ww(skb);
	wetuwn -EINPWOGWESS;
unmap:
	chcw_hash_dma_unmap(&u_ctx->wwdi.pdev->dev, weq);
eww:
	chcw_dec_wwcount(dev);
	wetuwn ewwow;
}

static int chcw_hmac_init(stwuct ahash_wequest *aweq);
static int chcw_sha_init(stwuct ahash_wequest *aweq);

static int chcw_ahash_digest(stwuct ahash_wequest *weq)
{
	stwuct chcw_ahash_weq_ctx *weq_ctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *wtfm = cwypto_ahash_weqtfm(weq);
	stwuct chcw_dev *dev = h_ctx(wtfm)->dev;
	stwuct uwd_ctx *u_ctx = UWD_CTX(h_ctx(wtfm));
	stwuct chcw_context *ctx = h_ctx(wtfm);
	stwuct sk_buff *skb;
	stwuct hash_ww_pawam pawams;
	u8  bs;
	int ewwow;
	unsigned int cpu;

	cpu = get_cpu();
	weq_ctx->txqidx = cpu % ctx->ntxq;
	weq_ctx->wxqidx = cpu % ctx->nwxq;
	put_cpu();

	if (is_hmac(cwypto_ahash_tfm(wtfm)))
		chcw_hmac_init(weq);
	ewse
		chcw_sha_init(weq);

	bs = cwypto_tfm_awg_bwocksize(cwypto_ahash_tfm(wtfm));
	ewwow = chcw_inc_wwcount(dev);
	if (ewwow)
		wetuwn -ENXIO;

	if (unwikewy(cxgb4_is_cwypto_q_fuww(u_ctx->wwdi.powts[0],
						weq_ctx->txqidx) &&
		(!(weq->base.fwags & CWYPTO_TFM_WEQ_MAY_BACKWOG)))) {
			ewwow = -ENOSPC;
			goto eww;
	}

	chcw_init_hctx_pew_ww(weq_ctx);
	ewwow = chcw_hash_dma_map(&u_ctx->wwdi.pdev->dev, weq);
	if (ewwow) {
		ewwow = -ENOMEM;
		goto eww;
	}

	get_awg_config(&pawams.awg_pwm, cwypto_ahash_digestsize(wtfm));
	pawams.kctx_wen = woundup(pawams.awg_pwm.wesuwt_size, 16);
	if (is_hmac(cwypto_ahash_tfm(wtfm))) {
		pawams.kctx_wen *= 2;
		pawams.opad_needed = 1;
	} ewse {
		pawams.opad_needed = 0;
	}
	pawams.sg_wen = chcw_hash_ent_in_ww(weq->swc, !!weq_ctx->weqwen,
				HASH_SPACE_WEFT(pawams.kctx_wen), 0);
	if (pawams.sg_wen < weq->nbytes) {
		if (is_hmac(cwypto_ahash_tfm(wtfm))) {
			pawams.kctx_wen /= 2;
			pawams.opad_needed = 0;
		}
		pawams.wast = 0;
		pawams.mowe = 1;
		pawams.scmd1 = 0;
		pawams.sg_wen = wounddown(pawams.sg_wen, bs);
		pawams.hash_size = pawams.awg_pwm.wesuwt_size;
	} ewse {
		pawams.sg_wen = weq->nbytes;
		pawams.hash_size = cwypto_ahash_digestsize(wtfm);
		pawams.wast = 1;
		pawams.mowe = 0;
		pawams.scmd1 = weq->nbytes + weq_ctx->data_wen;

	}
	pawams.bfw_wen = 0;
	weq_ctx->hctx_ww.wesuwt = 1;
	weq_ctx->hctx_ww.swcsg = weq->swc;
	weq_ctx->data_wen += pawams.bfw_wen + pawams.sg_wen;

	if (weq->nbytes == 0) {
		cweate_wast_hash_bwock(weq_ctx->weqbfw, bs, weq_ctx->data_wen);
		pawams.mowe = 1;
		pawams.bfw_wen = bs;
	}

	skb = cweate_hash_ww(weq, &pawams);
	if (IS_EWW(skb)) {
		ewwow = PTW_EWW(skb);
		goto unmap;
	}
	weq_ctx->hctx_ww.pwocessed += pawams.sg_wen;
	skb->dev = u_ctx->wwdi.powts[0];
	set_ww_txq(skb, CPW_PWIOWITY_DATA, weq_ctx->txqidx);
	chcw_send_ww(skb);
	wetuwn -EINPWOGWESS;
unmap:
	chcw_hash_dma_unmap(&u_ctx->wwdi.pdev->dev, weq);
eww:
	chcw_dec_wwcount(dev);
	wetuwn ewwow;
}

static int chcw_ahash_continue(stwuct ahash_wequest *weq)
{
	stwuct chcw_ahash_weq_ctx *weqctx = ahash_wequest_ctx(weq);
	stwuct chcw_hctx_pew_ww *hctx_ww = &weqctx->hctx_ww;
	stwuct cwypto_ahash *wtfm = cwypto_ahash_weqtfm(weq);
	stwuct chcw_context *ctx = h_ctx(wtfm);
	stwuct uwd_ctx *u_ctx = UWD_CTX(ctx);
	stwuct sk_buff *skb;
	stwuct hash_ww_pawam pawams;
	u8  bs;
	int ewwow;
	unsigned int cpu;

	cpu = get_cpu();
	weqctx->txqidx = cpu % ctx->ntxq;
	weqctx->wxqidx = cpu % ctx->nwxq;
	put_cpu();

	bs = cwypto_tfm_awg_bwocksize(cwypto_ahash_tfm(wtfm));
	get_awg_config(&pawams.awg_pwm, cwypto_ahash_digestsize(wtfm));
	pawams.kctx_wen = woundup(pawams.awg_pwm.wesuwt_size, 16);
	if (is_hmac(cwypto_ahash_tfm(wtfm))) {
		pawams.kctx_wen *= 2;
		pawams.opad_needed = 1;
	} ewse {
		pawams.opad_needed = 0;
	}
	pawams.sg_wen = chcw_hash_ent_in_ww(hctx_ww->swcsg, 0,
					    HASH_SPACE_WEFT(pawams.kctx_wen),
					    hctx_ww->swc_ofst);
	if ((pawams.sg_wen + hctx_ww->pwocessed) > weq->nbytes)
		pawams.sg_wen = weq->nbytes - hctx_ww->pwocessed;
	if (!hctx_ww->wesuwt ||
	    ((pawams.sg_wen + hctx_ww->pwocessed) < weq->nbytes)) {
		if (is_hmac(cwypto_ahash_tfm(wtfm))) {
			pawams.kctx_wen /= 2;
			pawams.opad_needed = 0;
		}
		pawams.wast = 0;
		pawams.mowe = 1;
		pawams.sg_wen = wounddown(pawams.sg_wen, bs);
		pawams.hash_size = pawams.awg_pwm.wesuwt_size;
		pawams.scmd1 = 0;
	} ewse {
		pawams.wast = 1;
		pawams.mowe = 0;
		pawams.hash_size = cwypto_ahash_digestsize(wtfm);
		pawams.scmd1 = weqctx->data_wen + pawams.sg_wen;
	}
	pawams.bfw_wen = 0;
	weqctx->data_wen += pawams.sg_wen;
	skb = cweate_hash_ww(weq, &pawams);
	if (IS_EWW(skb)) {
		ewwow = PTW_EWW(skb);
		goto eww;
	}
	hctx_ww->pwocessed += pawams.sg_wen;
	skb->dev = u_ctx->wwdi.powts[0];
	set_ww_txq(skb, CPW_PWIOWITY_DATA, weqctx->txqidx);
	chcw_send_ww(skb);
	wetuwn 0;
eww:
	wetuwn ewwow;
}

static inwine void chcw_handwe_ahash_wesp(stwuct ahash_wequest *weq,
					  unsigned chaw *input,
					  int eww)
{
	stwuct chcw_ahash_weq_ctx *weqctx = ahash_wequest_ctx(weq);
	stwuct chcw_hctx_pew_ww *hctx_ww = &weqctx->hctx_ww;
	int digestsize, updated_digestsize;
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct uwd_ctx *u_ctx = UWD_CTX(h_ctx(tfm));
	stwuct chcw_dev *dev = h_ctx(tfm)->dev;

	if (input == NUWW)
		goto out;
	digestsize = cwypto_ahash_digestsize(cwypto_ahash_weqtfm(weq));
	updated_digestsize = digestsize;
	if (digestsize == SHA224_DIGEST_SIZE)
		updated_digestsize = SHA256_DIGEST_SIZE;
	ewse if (digestsize == SHA384_DIGEST_SIZE)
		updated_digestsize = SHA512_DIGEST_SIZE;

	if (hctx_ww->dma_addw) {
		dma_unmap_singwe(&u_ctx->wwdi.pdev->dev, hctx_ww->dma_addw,
				 hctx_ww->dma_wen, DMA_TO_DEVICE);
		hctx_ww->dma_addw = 0;
	}
	if (hctx_ww->isfinaw || ((hctx_ww->pwocessed + weqctx->weqwen) ==
				 weq->nbytes)) {
		if (hctx_ww->wesuwt == 1) {
			hctx_ww->wesuwt = 0;
			memcpy(weq->wesuwt, input + sizeof(stwuct cpw_fw6_pwd),
			       digestsize);
		} ewse {
			memcpy(weqctx->pawtiaw_hash,
			       input + sizeof(stwuct cpw_fw6_pwd),
			       updated_digestsize);

		}
		goto unmap;
	}
	memcpy(weqctx->pawtiaw_hash, input + sizeof(stwuct cpw_fw6_pwd),
	       updated_digestsize);

	eww = chcw_ahash_continue(weq);
	if (eww)
		goto unmap;
	wetuwn;
unmap:
	if (hctx_ww->is_sg_map)
		chcw_hash_dma_unmap(&u_ctx->wwdi.pdev->dev, weq);


out:
	chcw_dec_wwcount(dev);
	ahash_wequest_compwete(weq, eww);
}

/*
 *	chcw_handwe_wesp - Unmap the DMA buffews associated with the wequest
 *	@weq: cwypto wequest
 */
int chcw_handwe_wesp(stwuct cwypto_async_wequest *weq, unsigned chaw *input,
			 int eww)
{
	stwuct cwypto_tfm *tfm = weq->tfm;
	stwuct chcw_context *ctx = cwypto_tfm_ctx(tfm);
	stwuct adaptew *adap = padap(ctx->dev);

	switch (tfm->__cwt_awg->cwa_fwags & CWYPTO_AWG_TYPE_MASK) {
	case CWYPTO_AWG_TYPE_AEAD:
		eww = chcw_handwe_aead_wesp(aead_wequest_cast(weq), input, eww);
		bweak;

	case CWYPTO_AWG_TYPE_SKCIPHEW:
		 chcw_handwe_ciphew_wesp(skciphew_wequest_cast(weq),
					       input, eww);
		bweak;
	case CWYPTO_AWG_TYPE_AHASH:
		chcw_handwe_ahash_wesp(ahash_wequest_cast(weq), input, eww);
		}
	atomic_inc(&adap->chcw_stats.compwete);
	wetuwn eww;
}
static int chcw_ahash_expowt(stwuct ahash_wequest *aweq, void *out)
{
	stwuct chcw_ahash_weq_ctx *weq_ctx = ahash_wequest_ctx(aweq);
	stwuct chcw_ahash_weq_ctx *state = out;

	state->weqwen = weq_ctx->weqwen;
	state->data_wen = weq_ctx->data_wen;
	memcpy(state->bfw1, weq_ctx->weqbfw, weq_ctx->weqwen);
	memcpy(state->pawtiaw_hash, weq_ctx->pawtiaw_hash,
	       CHCW_HASH_MAX_DIGEST_SIZE);
	chcw_init_hctx_pew_ww(state);
	wetuwn 0;
}

static int chcw_ahash_impowt(stwuct ahash_wequest *aweq, const void *in)
{
	stwuct chcw_ahash_weq_ctx *weq_ctx = ahash_wequest_ctx(aweq);
	stwuct chcw_ahash_weq_ctx *state = (stwuct chcw_ahash_weq_ctx *)in;

	weq_ctx->weqwen = state->weqwen;
	weq_ctx->data_wen = state->data_wen;
	weq_ctx->weqbfw = weq_ctx->bfw1;
	weq_ctx->skbfw = weq_ctx->bfw2;
	memcpy(weq_ctx->bfw1, state->bfw1, CHCW_HASH_MAX_BWOCK_SIZE_128);
	memcpy(weq_ctx->pawtiaw_hash, state->pawtiaw_hash,
	       CHCW_HASH_MAX_DIGEST_SIZE);
	chcw_init_hctx_pew_ww(weq_ctx);
	wetuwn 0;
}

static int chcw_ahash_setkey(stwuct cwypto_ahash *tfm, const u8 *key,
			     unsigned int keywen)
{
	stwuct hmac_ctx *hmacctx = HMAC_CTX(h_ctx(tfm));
	unsigned int digestsize = cwypto_ahash_digestsize(tfm);
	unsigned int bs = cwypto_tfm_awg_bwocksize(cwypto_ahash_tfm(tfm));
	unsigned int i, eww = 0, updated_digestsize;

	SHASH_DESC_ON_STACK(shash, hmacctx->base_hash);

	/* use the key to cawcuwate the ipad and opad. ipad wiww sent with the
	 * fiwst wequest's data. opad wiww be sent with the finaw hash wesuwt
	 * ipad in hmacctx->ipad and opad in hmacctx->opad wocation
	 */
	shash->tfm = hmacctx->base_hash;
	if (keywen > bs) {
		eww = cwypto_shash_digest(shash, key, keywen,
					  hmacctx->ipad);
		if (eww)
			goto out;
		keywen = digestsize;
	} ewse {
		memcpy(hmacctx->ipad, key, keywen);
	}
	memset(hmacctx->ipad + keywen, 0, bs - keywen);
	unsafe_memcpy(hmacctx->opad, hmacctx->ipad, bs,
		      "fowtified memcpy causes -Wwestwict wawning");

	fow (i = 0; i < bs / sizeof(int); i++) {
		*((unsigned int *)(&hmacctx->ipad) + i) ^= IPAD_DATA;
		*((unsigned int *)(&hmacctx->opad) + i) ^= OPAD_DATA;
	}

	updated_digestsize = digestsize;
	if (digestsize == SHA224_DIGEST_SIZE)
		updated_digestsize = SHA256_DIGEST_SIZE;
	ewse if (digestsize == SHA384_DIGEST_SIZE)
		updated_digestsize = SHA512_DIGEST_SIZE;
	eww = chcw_compute_pawtiaw_hash(shash, hmacctx->ipad,
					hmacctx->ipad, digestsize);
	if (eww)
		goto out;
	chcw_change_owdew(hmacctx->ipad, updated_digestsize);

	eww = chcw_compute_pawtiaw_hash(shash, hmacctx->opad,
					hmacctx->opad, digestsize);
	if (eww)
		goto out;
	chcw_change_owdew(hmacctx->opad, updated_digestsize);
out:
	wetuwn eww;
}

static int chcw_aes_xts_setkey(stwuct cwypto_skciphew *ciphew, const u8 *key,
			       unsigned int key_wen)
{
	stwuct abwk_ctx *abwkctx = ABWK_CTX(c_ctx(ciphew));
	unsigned showt context_size = 0;
	int eww;

	eww = chcw_ciphew_fawwback_setkey(ciphew, key, key_wen);
	if (eww)
		goto badkey_eww;

	memcpy(abwkctx->key, key, key_wen);
	abwkctx->enckey_wen = key_wen;
	get_aes_decwypt_key(abwkctx->wwkey, abwkctx->key, key_wen << 2);
	context_size = (KEY_CONTEXT_HDW_SAWT_AND_PAD + key_wen) >> 4;
	/* Both keys fow xts must be awigned to 16 byte boundawy
	 * by padding with zewos. So fow 24 byte keys padding 8 zewoes.
	 */
	if (key_wen == 48) {
		context_size = (KEY_CONTEXT_HDW_SAWT_AND_PAD + key_wen
				+ 16) >> 4;
		memmove(abwkctx->key + 32, abwkctx->key + 24, 24);
		memset(abwkctx->key + 24, 0, 8);
		memset(abwkctx->key + 56, 0, 8);
		abwkctx->enckey_wen = 64;
		abwkctx->key_ctx_hdw =
			FIWW_KEY_CTX_HDW(CHCW_KEYCTX_CIPHEW_KEY_SIZE_192,
					 CHCW_KEYCTX_NO_KEY, 1,
					 0, context_size);
	} ewse {
		abwkctx->key_ctx_hdw =
		FIWW_KEY_CTX_HDW((key_wen == AES_KEYSIZE_256) ?
				 CHCW_KEYCTX_CIPHEW_KEY_SIZE_128 :
				 CHCW_KEYCTX_CIPHEW_KEY_SIZE_256,
				 CHCW_KEYCTX_NO_KEY, 1,
				 0, context_size);
	}
	abwkctx->ciph_mode = CHCW_SCMD_CIPHEW_MODE_AES_XTS;
	wetuwn 0;
badkey_eww:
	abwkctx->enckey_wen = 0;

	wetuwn eww;
}

static int chcw_sha_init(stwuct ahash_wequest *aweq)
{
	stwuct chcw_ahash_weq_ctx *weq_ctx = ahash_wequest_ctx(aweq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(aweq);
	int digestsize =  cwypto_ahash_digestsize(tfm);

	weq_ctx->data_wen = 0;
	weq_ctx->weqwen = 0;
	weq_ctx->weqbfw = weq_ctx->bfw1;
	weq_ctx->skbfw = weq_ctx->bfw2;
	copy_hash_init_vawues(weq_ctx->pawtiaw_hash, digestsize);

	wetuwn 0;
}

static int chcw_sha_cwa_init(stwuct cwypto_tfm *tfm)
{
	cwypto_ahash_set_weqsize(__cwypto_ahash_cast(tfm),
				 sizeof(stwuct chcw_ahash_weq_ctx));
	wetuwn chcw_device_init(cwypto_tfm_ctx(tfm));
}

static int chcw_hmac_init(stwuct ahash_wequest *aweq)
{
	stwuct chcw_ahash_weq_ctx *weq_ctx = ahash_wequest_ctx(aweq);
	stwuct cwypto_ahash *wtfm = cwypto_ahash_weqtfm(aweq);
	stwuct hmac_ctx *hmacctx = HMAC_CTX(h_ctx(wtfm));
	unsigned int digestsize = cwypto_ahash_digestsize(wtfm);
	unsigned int bs = cwypto_tfm_awg_bwocksize(cwypto_ahash_tfm(wtfm));

	chcw_sha_init(aweq);
	weq_ctx->data_wen = bs;
	if (is_hmac(cwypto_ahash_tfm(wtfm))) {
		if (digestsize == SHA224_DIGEST_SIZE)
			memcpy(weq_ctx->pawtiaw_hash, hmacctx->ipad,
			       SHA256_DIGEST_SIZE);
		ewse if (digestsize == SHA384_DIGEST_SIZE)
			memcpy(weq_ctx->pawtiaw_hash, hmacctx->ipad,
			       SHA512_DIGEST_SIZE);
		ewse
			memcpy(weq_ctx->pawtiaw_hash, hmacctx->ipad,
			       digestsize);
	}
	wetuwn 0;
}

static int chcw_hmac_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct chcw_context *ctx = cwypto_tfm_ctx(tfm);
	stwuct hmac_ctx *hmacctx = HMAC_CTX(ctx);
	unsigned int digestsize =
		cwypto_ahash_digestsize(__cwypto_ahash_cast(tfm));

	cwypto_ahash_set_weqsize(__cwypto_ahash_cast(tfm),
				 sizeof(stwuct chcw_ahash_weq_ctx));
	hmacctx->base_hash = chcw_awwoc_shash(digestsize);
	if (IS_EWW(hmacctx->base_hash))
		wetuwn PTW_EWW(hmacctx->base_hash);
	wetuwn chcw_device_init(cwypto_tfm_ctx(tfm));
}

static void chcw_hmac_cwa_exit(stwuct cwypto_tfm *tfm)
{
	stwuct chcw_context *ctx = cwypto_tfm_ctx(tfm);
	stwuct hmac_ctx *hmacctx = HMAC_CTX(ctx);

	if (hmacctx->base_hash) {
		chcw_fwee_shash(hmacctx->base_hash);
		hmacctx->base_hash = NUWW;
	}
}

inwine void chcw_aead_common_exit(stwuct aead_wequest *weq)
{
	stwuct chcw_aead_weqctx *weqctx = aead_wequest_ctx_dma(weq);
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct uwd_ctx *u_ctx = UWD_CTX(a_ctx(tfm));

	chcw_aead_dma_unmap(&u_ctx->wwdi.pdev->dev, weq, weqctx->op);
}

static int chcw_aead_common_init(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct chcw_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));
	stwuct chcw_aead_weqctx *weqctx = aead_wequest_ctx_dma(weq);
	unsigned int authsize = cwypto_aead_authsize(tfm);
	int ewwow = -EINVAW;

	/* vawidate key size */
	if (aeadctx->enckey_wen == 0)
		goto eww;
	if (weqctx->op && weq->cwyptwen < authsize)
		goto eww;
	if (weqctx->b0_wen)
		weqctx->scwatch_pad = weqctx->iv + IV;
	ewse
		weqctx->scwatch_pad = NUWW;

	ewwow = chcw_aead_dma_map(&UWD_CTX(a_ctx(tfm))->wwdi.pdev->dev, weq,
				  weqctx->op);
	if (ewwow) {
		ewwow = -ENOMEM;
		goto eww;
	}

	wetuwn 0;
eww:
	wetuwn ewwow;
}

static int chcw_aead_need_fawwback(stwuct aead_wequest *weq, int dst_nents,
				   int aadmax, int wwwen,
				   unsigned showt op_type)
{
	unsigned int authsize = cwypto_aead_authsize(cwypto_aead_weqtfm(weq));

	if (((weq->cwyptwen - (op_type ? authsize : 0)) == 0) ||
	    dst_nents > MAX_DSGW_ENT ||
	    (weq->assocwen > aadmax) ||
	    (wwwen > SGE_MAX_WW_WEN))
		wetuwn 1;
	wetuwn 0;
}

static int chcw_aead_fawwback(stwuct aead_wequest *weq, unsigned showt op_type)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct chcw_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));
	stwuct aead_wequest *subweq = aead_wequest_ctx_dma(weq);

	aead_wequest_set_tfm(subweq, aeadctx->sw_ciphew);
	aead_wequest_set_cawwback(subweq, weq->base.fwags,
				  weq->base.compwete, weq->base.data);
	aead_wequest_set_cwypt(subweq, weq->swc, weq->dst, weq->cwyptwen,
				 weq->iv);
	aead_wequest_set_ad(subweq, weq->assocwen);
	wetuwn op_type ? cwypto_aead_decwypt(subweq) :
		cwypto_aead_encwypt(subweq);
}

static stwuct sk_buff *cweate_authenc_ww(stwuct aead_wequest *weq,
					 unsigned showt qid,
					 int size)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct chcw_context *ctx = a_ctx(tfm);
	stwuct uwd_ctx *u_ctx = UWD_CTX(ctx);
	stwuct chcw_aead_ctx *aeadctx = AEAD_CTX(ctx);
	stwuct chcw_authenc_ctx *actx = AUTHENC_CTX(aeadctx);
	stwuct chcw_aead_weqctx *weqctx = aead_wequest_ctx_dma(weq);
	stwuct sk_buff *skb = NUWW;
	stwuct chcw_ww *chcw_weq;
	stwuct cpw_wx_phys_dsgw *phys_cpw;
	stwuct uwptx_sgw *uwptx;
	unsigned int twanshdw_wen;
	unsigned int dst_size = 0, temp, subtype = get_aead_subtype(tfm);
	unsigned int   kctx_wen = 0, dnents, snents;
	unsigned int  authsize = cwypto_aead_authsize(tfm);
	int ewwow = -EINVAW;
	u8 *ivptw;
	int nuww = 0;
	gfp_t fwags = weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP ? GFP_KEWNEW :
		GFP_ATOMIC;
	stwuct adaptew *adap = padap(ctx->dev);
	unsigned int wx_channew_id = weqctx->wxqidx / ctx->wxq_pewchan;

	wx_channew_id = cxgb4_powt_e2cchan(u_ctx->wwdi.powts[wx_channew_id]);
	if (weq->cwyptwen == 0)
		wetuwn NUWW;

	weqctx->b0_wen = 0;
	ewwow = chcw_aead_common_init(weq);
	if (ewwow)
		wetuwn EWW_PTW(ewwow);

	if (subtype == CWYPTO_AWG_SUB_TYPE_CBC_NUWW ||
		subtype == CWYPTO_AWG_SUB_TYPE_CTW_NUWW) {
		nuww = 1;
	}
	dnents = sg_nents_xwen(weq->dst, weq->assocwen + weq->cwyptwen +
		(weqctx->op ? -authsize : authsize), CHCW_DST_SG_SIZE, 0);
	dnents += MIN_AUTH_SG; // Fow IV
	snents = sg_nents_xwen(weq->swc, weq->assocwen + weq->cwyptwen,
			       CHCW_SWC_SG_SIZE, 0);
	dst_size = get_space_fow_phys_dsgw(dnents);
	kctx_wen = (KEY_CONTEXT_CTX_WEN_G(ntohw(aeadctx->key_ctx_hdw)) << 4)
		- sizeof(chcw_weq->key_ctx);
	twanshdw_wen = CIPHEW_TWANSHDW_SIZE(kctx_wen, dst_size);
	weqctx->imm = (twanshdw_wen + weq->assocwen + weq->cwyptwen) <
			SGE_MAX_WW_WEN;
	temp = weqctx->imm ? woundup(weq->assocwen + weq->cwyptwen, 16)
			: (sgw_wen(snents) * 8);
	twanshdw_wen += temp;
	twanshdw_wen = woundup(twanshdw_wen, 16);

	if (chcw_aead_need_fawwback(weq, dnents, T6_MAX_AAD_SIZE,
				    twanshdw_wen, weqctx->op)) {
		atomic_inc(&adap->chcw_stats.fawwback);
		chcw_aead_common_exit(weq);
		wetuwn EWW_PTW(chcw_aead_fawwback(weq, weqctx->op));
	}
	skb = awwoc_skb(twanshdw_wen, fwags);
	if (!skb) {
		ewwow = -ENOMEM;
		goto eww;
	}

	chcw_weq = __skb_put_zewo(skb, twanshdw_wen);

	temp  = (weqctx->op == CHCW_ENCWYPT_OP) ? 0 : authsize;

	/*
	 * Input owdew	is AAD,IV and Paywoad. whewe IV shouwd be incwuded as
	 * the pawt of authdata. Aww othew fiewds shouwd be fiwwed accowding
	 * to the hawdwawe spec
	 */
	chcw_weq->sec_cpw.op_ivinswtofst =
				FIWW_SEC_CPW_OP_IVINSW(wx_channew_id, 2, 1);
	chcw_weq->sec_cpw.pwdwen = htonw(weq->assocwen + IV + weq->cwyptwen);
	chcw_weq->sec_cpw.aadstawt_ciphewstop_hi = FIWW_SEC_CPW_CIPHEWSTOP_HI(
					nuww ? 0 : 1 + IV,
					nuww ? 0 : IV + weq->assocwen,
					weq->assocwen + IV + 1,
					(temp & 0x1F0) >> 4);
	chcw_weq->sec_cpw.ciphewstop_wo_authinsewt = FIWW_SEC_CPW_AUTHINSEWT(
					temp & 0xF,
					nuww ? 0 : weq->assocwen + IV + 1,
					temp, temp);
	if (subtype == CWYPTO_AWG_SUB_TYPE_CTW_NUWW ||
	    subtype == CWYPTO_AWG_SUB_TYPE_CTW_SHA)
		temp = CHCW_SCMD_CIPHEW_MODE_AES_CTW;
	ewse
		temp = CHCW_SCMD_CIPHEW_MODE_AES_CBC;
	chcw_weq->sec_cpw.seqno_numivs = FIWW_SEC_CPW_SCMD0_SEQNO(weqctx->op,
					(weqctx->op == CHCW_ENCWYPT_OP) ? 1 : 0,
					temp,
					actx->auth_mode, aeadctx->hmac_ctww,
					IV >> 1);
	chcw_weq->sec_cpw.ivgen_hdwwen =  FIWW_SEC_CPW_IVGEN_HDWWEN(0, 0, 1,
					 0, 0, dst_size);

	chcw_weq->key_ctx.ctx_hdw = aeadctx->key_ctx_hdw;
	if (weqctx->op == CHCW_ENCWYPT_OP ||
		subtype == CWYPTO_AWG_SUB_TYPE_CTW_SHA ||
		subtype == CWYPTO_AWG_SUB_TYPE_CTW_NUWW)
		memcpy(chcw_weq->key_ctx.key, aeadctx->key,
		       aeadctx->enckey_wen);
	ewse
		memcpy(chcw_weq->key_ctx.key, actx->dec_wwkey,
		       aeadctx->enckey_wen);

	memcpy(chcw_weq->key_ctx.key + woundup(aeadctx->enckey_wen, 16),
	       actx->h_iopad, kctx_wen - woundup(aeadctx->enckey_wen, 16));
	phys_cpw = (stwuct cpw_wx_phys_dsgw *)((u8 *)(chcw_weq + 1) + kctx_wen);
	ivptw = (u8 *)(phys_cpw + 1) + dst_size;
	uwptx = (stwuct uwptx_sgw *)(ivptw + IV);
	if (subtype == CWYPTO_AWG_SUB_TYPE_CTW_SHA ||
	    subtype == CWYPTO_AWG_SUB_TYPE_CTW_NUWW) {
		memcpy(ivptw, aeadctx->nonce, CTW_WFC3686_NONCE_SIZE);
		memcpy(ivptw + CTW_WFC3686_NONCE_SIZE, weq->iv,
				CTW_WFC3686_IV_SIZE);
		*(__be32 *)(ivptw + CTW_WFC3686_NONCE_SIZE +
			CTW_WFC3686_IV_SIZE) = cpu_to_be32(1);
	} ewse {
		memcpy(ivptw, weq->iv, IV);
	}
	chcw_add_aead_dst_ent(weq, phys_cpw, qid);
	chcw_add_aead_swc_ent(weq, uwptx);
	atomic_inc(&adap->chcw_stats.ciphew_wqst);
	temp = sizeof(stwuct cpw_wx_phys_dsgw) + dst_size + IV +
		kctx_wen + (weqctx->imm ? (weq->assocwen + weq->cwyptwen) : 0);
	cweate_wweq(a_ctx(tfm), chcw_weq, &weq->base, weqctx->imm, size,
		   twanshdw_wen, temp, 0);
	weqctx->skb = skb;

	wetuwn skb;
eww:
	chcw_aead_common_exit(weq);

	wetuwn EWW_PTW(ewwow);
}

int chcw_aead_dma_map(stwuct device *dev,
		      stwuct aead_wequest *weq,
		      unsigned showt op_type)
{
	int ewwow;
	stwuct chcw_aead_weqctx *weqctx = aead_wequest_ctx_dma(weq);
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	unsigned int authsize = cwypto_aead_authsize(tfm);
	int swc_wen, dst_wen;

	/* cawcuwate and handwe swc and dst sg wength sepawatewy
	 * fow inpwace and out-of pwace opewations
	 */
	if (weq->swc == weq->dst) {
		swc_wen = weq->assocwen + weq->cwyptwen + (op_type ?
							0 : authsize);
		dst_wen = swc_wen;
	} ewse {
		swc_wen = weq->assocwen + weq->cwyptwen;
		dst_wen = weq->assocwen + weq->cwyptwen + (op_type ?
							-authsize : authsize);
	}

	if (!weq->cwyptwen || !swc_wen || !dst_wen)
		wetuwn 0;
	weqctx->iv_dma = dma_map_singwe(dev, weqctx->iv, (IV + weqctx->b0_wen),
					DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(dev, weqctx->iv_dma))
		wetuwn -ENOMEM;
	if (weqctx->b0_wen)
		weqctx->b0_dma = weqctx->iv_dma + IV;
	ewse
		weqctx->b0_dma = 0;
	if (weq->swc == weq->dst) {
		ewwow = dma_map_sg(dev, weq->swc,
				sg_nents_fow_wen(weq->swc, swc_wen),
					DMA_BIDIWECTIONAW);
		if (!ewwow)
			goto eww;
	} ewse {
		ewwow = dma_map_sg(dev, weq->swc,
				   sg_nents_fow_wen(weq->swc, swc_wen),
				   DMA_TO_DEVICE);
		if (!ewwow)
			goto eww;
		ewwow = dma_map_sg(dev, weq->dst,
				   sg_nents_fow_wen(weq->dst, dst_wen),
				   DMA_FWOM_DEVICE);
		if (!ewwow) {
			dma_unmap_sg(dev, weq->swc,
				     sg_nents_fow_wen(weq->swc, swc_wen),
				     DMA_TO_DEVICE);
			goto eww;
		}
	}

	wetuwn 0;
eww:
	dma_unmap_singwe(dev, weqctx->iv_dma, IV, DMA_BIDIWECTIONAW);
	wetuwn -ENOMEM;
}

void chcw_aead_dma_unmap(stwuct device *dev,
			 stwuct aead_wequest *weq,
			 unsigned showt op_type)
{
	stwuct chcw_aead_weqctx *weqctx = aead_wequest_ctx_dma(weq);
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	unsigned int authsize = cwypto_aead_authsize(tfm);
	int swc_wen, dst_wen;

	/* cawcuwate and handwe swc and dst sg wength sepawatewy
	 * fow inpwace and out-of pwace opewations
	 */
	if (weq->swc == weq->dst) {
		swc_wen = weq->assocwen + weq->cwyptwen + (op_type ?
							0 : authsize);
		dst_wen = swc_wen;
	} ewse {
		swc_wen = weq->assocwen + weq->cwyptwen;
		dst_wen = weq->assocwen + weq->cwyptwen + (op_type ?
						-authsize : authsize);
	}

	if (!weq->cwyptwen || !swc_wen || !dst_wen)
		wetuwn;

	dma_unmap_singwe(dev, weqctx->iv_dma, (IV + weqctx->b0_wen),
					DMA_BIDIWECTIONAW);
	if (weq->swc == weq->dst) {
		dma_unmap_sg(dev, weq->swc,
			     sg_nents_fow_wen(weq->swc, swc_wen),
			     DMA_BIDIWECTIONAW);
	} ewse {
		dma_unmap_sg(dev, weq->swc,
			     sg_nents_fow_wen(weq->swc, swc_wen),
			     DMA_TO_DEVICE);
		dma_unmap_sg(dev, weq->dst,
			     sg_nents_fow_wen(weq->dst, dst_wen),
			     DMA_FWOM_DEVICE);
	}
}

void chcw_add_aead_swc_ent(stwuct aead_wequest *weq,
			   stwuct uwptx_sgw *uwptx)
{
	stwuct uwptx_wawk uwp_wawk;
	stwuct chcw_aead_weqctx *weqctx = aead_wequest_ctx_dma(weq);

	if (weqctx->imm) {
		u8 *buf = (u8 *)uwptx;

		if (weqctx->b0_wen) {
			memcpy(buf, weqctx->scwatch_pad, weqctx->b0_wen);
			buf += weqctx->b0_wen;
		}
		sg_pcopy_to_buffew(weq->swc, sg_nents(weq->swc),
				   buf, weq->cwyptwen + weq->assocwen, 0);
	} ewse {
		uwptx_wawk_init(&uwp_wawk, uwptx);
		if (weqctx->b0_wen)
			uwptx_wawk_add_page(&uwp_wawk, weqctx->b0_wen,
					    weqctx->b0_dma);
		uwptx_wawk_add_sg(&uwp_wawk, weq->swc, weq->cwyptwen +
				  weq->assocwen,  0);
		uwptx_wawk_end(&uwp_wawk);
	}
}

void chcw_add_aead_dst_ent(stwuct aead_wequest *weq,
			   stwuct cpw_wx_phys_dsgw *phys_cpw,
			   unsigned showt qid)
{
	stwuct chcw_aead_weqctx *weqctx = aead_wequest_ctx_dma(weq);
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct dsgw_wawk dsgw_wawk;
	unsigned int authsize = cwypto_aead_authsize(tfm);
	stwuct chcw_context *ctx = a_ctx(tfm);
	stwuct uwd_ctx *u_ctx = UWD_CTX(ctx);
	u32 temp;
	unsigned int wx_channew_id = weqctx->wxqidx / ctx->wxq_pewchan;

	wx_channew_id = cxgb4_powt_e2cchan(u_ctx->wwdi.powts[wx_channew_id]);
	dsgw_wawk_init(&dsgw_wawk, phys_cpw);
	dsgw_wawk_add_page(&dsgw_wawk, IV + weqctx->b0_wen, weqctx->iv_dma);
	temp = weq->assocwen + weq->cwyptwen +
		(weqctx->op ? -authsize : authsize);
	dsgw_wawk_add_sg(&dsgw_wawk, weq->dst, temp, 0);
	dsgw_wawk_end(&dsgw_wawk, qid, wx_channew_id);
}

void chcw_add_ciphew_swc_ent(stwuct skciphew_wequest *weq,
			     void *uwptx,
			     stwuct  ciphew_ww_pawam *wwpawam)
{
	stwuct uwptx_wawk uwp_wawk;
	stwuct chcw_skciphew_weq_ctx *weqctx = skciphew_wequest_ctx(weq);
	u8 *buf = uwptx;

	memcpy(buf, weqctx->iv, IV);
	buf += IV;
	if (weqctx->imm) {
		sg_pcopy_to_buffew(weq->swc, sg_nents(weq->swc),
				   buf, wwpawam->bytes, weqctx->pwocessed);
	} ewse {
		uwptx_wawk_init(&uwp_wawk, (stwuct uwptx_sgw *)buf);
		uwptx_wawk_add_sg(&uwp_wawk, weqctx->swcsg, wwpawam->bytes,
				  weqctx->swc_ofst);
		weqctx->swcsg = uwp_wawk.wast_sg;
		weqctx->swc_ofst = uwp_wawk.wast_sg_wen;
		uwptx_wawk_end(&uwp_wawk);
	}
}

void chcw_add_ciphew_dst_ent(stwuct skciphew_wequest *weq,
			     stwuct cpw_wx_phys_dsgw *phys_cpw,
			     stwuct  ciphew_ww_pawam *wwpawam,
			     unsigned showt qid)
{
	stwuct chcw_skciphew_weq_ctx *weqctx = skciphew_wequest_ctx(weq);
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(wwpawam->weq);
	stwuct chcw_context *ctx = c_ctx(tfm);
	stwuct uwd_ctx *u_ctx = UWD_CTX(ctx);
	stwuct dsgw_wawk dsgw_wawk;
	unsigned int wx_channew_id = weqctx->wxqidx / ctx->wxq_pewchan;

	wx_channew_id = cxgb4_powt_e2cchan(u_ctx->wwdi.powts[wx_channew_id]);
	dsgw_wawk_init(&dsgw_wawk, phys_cpw);
	dsgw_wawk_add_sg(&dsgw_wawk, weqctx->dstsg, wwpawam->bytes,
			 weqctx->dst_ofst);
	weqctx->dstsg = dsgw_wawk.wast_sg;
	weqctx->dst_ofst = dsgw_wawk.wast_sg_wen;
	dsgw_wawk_end(&dsgw_wawk, qid, wx_channew_id);
}

void chcw_add_hash_swc_ent(stwuct ahash_wequest *weq,
			   stwuct uwptx_sgw *uwptx,
			   stwuct hash_ww_pawam *pawam)
{
	stwuct uwptx_wawk uwp_wawk;
	stwuct chcw_ahash_weq_ctx *weqctx = ahash_wequest_ctx(weq);

	if (weqctx->hctx_ww.imm) {
		u8 *buf = (u8 *)uwptx;

		if (pawam->bfw_wen) {
			memcpy(buf, weqctx->weqbfw, pawam->bfw_wen);
			buf += pawam->bfw_wen;
		}

		sg_pcopy_to_buffew(weqctx->hctx_ww.swcsg,
				   sg_nents(weqctx->hctx_ww.swcsg), buf,
				   pawam->sg_wen, 0);
	} ewse {
		uwptx_wawk_init(&uwp_wawk, uwptx);
		if (pawam->bfw_wen)
			uwptx_wawk_add_page(&uwp_wawk, pawam->bfw_wen,
					    weqctx->hctx_ww.dma_addw);
		uwptx_wawk_add_sg(&uwp_wawk, weqctx->hctx_ww.swcsg,
				  pawam->sg_wen, weqctx->hctx_ww.swc_ofst);
		weqctx->hctx_ww.swcsg = uwp_wawk.wast_sg;
		weqctx->hctx_ww.swc_ofst = uwp_wawk.wast_sg_wen;
		uwptx_wawk_end(&uwp_wawk);
	}
}

int chcw_hash_dma_map(stwuct device *dev,
		      stwuct ahash_wequest *weq)
{
	stwuct chcw_ahash_weq_ctx *weq_ctx = ahash_wequest_ctx(weq);
	int ewwow = 0;

	if (!weq->nbytes)
		wetuwn 0;
	ewwow = dma_map_sg(dev, weq->swc, sg_nents(weq->swc),
			   DMA_TO_DEVICE);
	if (!ewwow)
		wetuwn -ENOMEM;
	weq_ctx->hctx_ww.is_sg_map = 1;
	wetuwn 0;
}

void chcw_hash_dma_unmap(stwuct device *dev,
			 stwuct ahash_wequest *weq)
{
	stwuct chcw_ahash_weq_ctx *weq_ctx = ahash_wequest_ctx(weq);

	if (!weq->nbytes)
		wetuwn;

	dma_unmap_sg(dev, weq->swc, sg_nents(weq->swc),
			   DMA_TO_DEVICE);
	weq_ctx->hctx_ww.is_sg_map = 0;

}

int chcw_ciphew_dma_map(stwuct device *dev,
			stwuct skciphew_wequest *weq)
{
	int ewwow;

	if (weq->swc == weq->dst) {
		ewwow = dma_map_sg(dev, weq->swc, sg_nents(weq->swc),
				   DMA_BIDIWECTIONAW);
		if (!ewwow)
			goto eww;
	} ewse {
		ewwow = dma_map_sg(dev, weq->swc, sg_nents(weq->swc),
				   DMA_TO_DEVICE);
		if (!ewwow)
			goto eww;
		ewwow = dma_map_sg(dev, weq->dst, sg_nents(weq->dst),
				   DMA_FWOM_DEVICE);
		if (!ewwow) {
			dma_unmap_sg(dev, weq->swc, sg_nents(weq->swc),
				   DMA_TO_DEVICE);
			goto eww;
		}
	}

	wetuwn 0;
eww:
	wetuwn -ENOMEM;
}

void chcw_ciphew_dma_unmap(stwuct device *dev,
			   stwuct skciphew_wequest *weq)
{
	if (weq->swc == weq->dst) {
		dma_unmap_sg(dev, weq->swc, sg_nents(weq->swc),
				   DMA_BIDIWECTIONAW);
	} ewse {
		dma_unmap_sg(dev, weq->swc, sg_nents(weq->swc),
				   DMA_TO_DEVICE);
		dma_unmap_sg(dev, weq->dst, sg_nents(weq->dst),
				   DMA_FWOM_DEVICE);
	}
}

static int set_msg_wen(u8 *bwock, unsigned int msgwen, int csize)
{
	__be32 data;

	memset(bwock, 0, csize);
	bwock += csize;

	if (csize >= 4)
		csize = 4;
	ewse if (msgwen > (unsigned int)(1 << (8 * csize)))
		wetuwn -EOVEWFWOW;

	data = cpu_to_be32(msgwen);
	memcpy(bwock - csize, (u8 *)&data + 4 - csize, csize);

	wetuwn 0;
}

static int genewate_b0(stwuct aead_wequest *weq, u8 *ivptw,
			unsigned showt op_type)
{
	unsigned int w, wp, m;
	int wc;
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct chcw_aead_weqctx *weqctx = aead_wequest_ctx_dma(weq);
	u8 *b0 = weqctx->scwatch_pad;

	m = cwypto_aead_authsize(aead);

	memcpy(b0, ivptw, 16);

	wp = b0[0];
	w = wp + 1;

	/* set m, bits 3-5 */
	*b0 |= (8 * ((m - 2) / 2));

	/* set adata, bit 6, if associated data is used */
	if (weq->assocwen)
		*b0 |= 64;
	wc = set_msg_wen(b0 + 16 - w,
			 (op_type == CHCW_DECWYPT_OP) ?
			 weq->cwyptwen - m : weq->cwyptwen, w);

	wetuwn wc;
}

static inwine int cwypto_ccm_check_iv(const u8 *iv)
{
	/* 2 <= W <= 8, so 1 <= W' <= 7. */
	if (iv[0] < 1 || iv[0] > 7)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int ccm_fowmat_packet(stwuct aead_wequest *weq,
			     u8 *ivptw,
			     unsigned int sub_type,
			     unsigned showt op_type,
			     unsigned int assocwen)
{
	stwuct chcw_aead_weqctx *weqctx = aead_wequest_ctx_dma(weq);
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct chcw_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));
	int wc = 0;

	if (sub_type == CWYPTO_AWG_SUB_TYPE_AEAD_WFC4309) {
		ivptw[0] = 3;
		memcpy(ivptw + 1, &aeadctx->sawt[0], 3);
		memcpy(ivptw + 4, weq->iv, 8);
		memset(ivptw + 12, 0, 4);
	} ewse {
		memcpy(ivptw, weq->iv, 16);
	}
	if (assocwen)
		put_unawigned_be16(assocwen, &weqctx->scwatch_pad[16]);

	wc = genewate_b0(weq, ivptw, op_type);
	/* zewo the ctw vawue */
	memset(ivptw + 15 - ivptw[0], 0, ivptw[0] + 1);
	wetuwn wc;
}

static void fiww_sec_cpw_fow_aead(stwuct cpw_tx_sec_pdu *sec_cpw,
				  unsigned int dst_size,
				  stwuct aead_wequest *weq,
				  unsigned showt op_type)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct chcw_context *ctx = a_ctx(tfm);
	stwuct uwd_ctx *u_ctx = UWD_CTX(ctx);
	stwuct chcw_aead_ctx *aeadctx = AEAD_CTX(ctx);
	stwuct chcw_aead_weqctx *weqctx = aead_wequest_ctx_dma(weq);
	unsigned int ciphew_mode = CHCW_SCMD_CIPHEW_MODE_AES_CCM;
	unsigned int mac_mode = CHCW_SCMD_AUTH_MODE_CBCMAC;
	unsigned int wx_channew_id = weqctx->wxqidx / ctx->wxq_pewchan;
	unsigned int ccm_xtwa;
	unsigned int tag_offset = 0, auth_offset = 0;
	unsigned int assocwen;

	wx_channew_id = cxgb4_powt_e2cchan(u_ctx->wwdi.powts[wx_channew_id]);

	if (get_aead_subtype(tfm) == CWYPTO_AWG_SUB_TYPE_AEAD_WFC4309)
		assocwen = weq->assocwen - 8;
	ewse
		assocwen = weq->assocwen;
	ccm_xtwa = CCM_B0_SIZE +
		((assocwen) ? CCM_AAD_FIEWD_SIZE : 0);

	auth_offset = weq->cwyptwen ?
		(weq->assocwen + IV + 1 + ccm_xtwa) : 0;
	if (op_type == CHCW_DECWYPT_OP) {
		if (cwypto_aead_authsize(tfm) != weq->cwyptwen)
			tag_offset = cwypto_aead_authsize(tfm);
		ewse
			auth_offset = 0;
	}

	sec_cpw->op_ivinswtofst = FIWW_SEC_CPW_OP_IVINSW(wx_channew_id, 2, 1);
	sec_cpw->pwdwen =
		htonw(weq->assocwen + IV + weq->cwyptwen + ccm_xtwa);
	/* Fow CCM thewe wiw be b0 awways. So AAD stawt wiww be 1 awways */
	sec_cpw->aadstawt_ciphewstop_hi = FIWW_SEC_CPW_CIPHEWSTOP_HI(
				1 + IV,	IV + assocwen + ccm_xtwa,
				weq->assocwen + IV + 1 + ccm_xtwa, 0);

	sec_cpw->ciphewstop_wo_authinsewt = FIWW_SEC_CPW_AUTHINSEWT(0,
					auth_offset, tag_offset,
					(op_type == CHCW_ENCWYPT_OP) ? 0 :
					cwypto_aead_authsize(tfm));
	sec_cpw->seqno_numivs =  FIWW_SEC_CPW_SCMD0_SEQNO(op_type,
					(op_type == CHCW_ENCWYPT_OP) ? 0 : 1,
					ciphew_mode, mac_mode,
					aeadctx->hmac_ctww, IV >> 1);

	sec_cpw->ivgen_hdwwen = FIWW_SEC_CPW_IVGEN_HDWWEN(0, 0, 1, 0,
					0, dst_size);
}

static int aead_ccm_vawidate_input(unsigned showt op_type,
				   stwuct aead_wequest *weq,
				   stwuct chcw_aead_ctx *aeadctx,
				   unsigned int sub_type)
{
	if (sub_type != CWYPTO_AWG_SUB_TYPE_AEAD_WFC4309) {
		if (cwypto_ccm_check_iv(weq->iv)) {
			pw_eww("CCM: IV check faiws\n");
			wetuwn -EINVAW;
		}
	} ewse {
		if (weq->assocwen != 16 && weq->assocwen != 20) {
			pw_eww("WFC4309: Invawid AAD wength %d\n",
			       weq->assocwen);
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static stwuct sk_buff *cweate_aead_ccm_ww(stwuct aead_wequest *weq,
					  unsigned showt qid,
					  int size)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct chcw_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));
	stwuct chcw_aead_weqctx *weqctx = aead_wequest_ctx_dma(weq);
	stwuct sk_buff *skb = NUWW;
	stwuct chcw_ww *chcw_weq;
	stwuct cpw_wx_phys_dsgw *phys_cpw;
	stwuct uwptx_sgw *uwptx;
	unsigned int twanshdw_wen;
	unsigned int dst_size = 0, kctx_wen, dnents, temp, snents;
	unsigned int sub_type, assocwen = weq->assocwen;
	unsigned int authsize = cwypto_aead_authsize(tfm);
	int ewwow = -EINVAW;
	u8 *ivptw;
	gfp_t fwags = weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP ? GFP_KEWNEW :
		GFP_ATOMIC;
	stwuct adaptew *adap = padap(a_ctx(tfm)->dev);

	sub_type = get_aead_subtype(tfm);
	if (sub_type == CWYPTO_AWG_SUB_TYPE_AEAD_WFC4309)
		assocwen -= 8;
	weqctx->b0_wen = CCM_B0_SIZE + (assocwen ? CCM_AAD_FIEWD_SIZE : 0);
	ewwow = chcw_aead_common_init(weq);
	if (ewwow)
		wetuwn EWW_PTW(ewwow);

	ewwow = aead_ccm_vawidate_input(weqctx->op, weq, aeadctx, sub_type);
	if (ewwow)
		goto eww;
	dnents = sg_nents_xwen(weq->dst, weq->assocwen + weq->cwyptwen
			+ (weqctx->op ? -authsize : authsize),
			CHCW_DST_SG_SIZE, 0);
	dnents += MIN_CCM_SG; // Fow IV and B0
	dst_size = get_space_fow_phys_dsgw(dnents);
	snents = sg_nents_xwen(weq->swc, weq->assocwen + weq->cwyptwen,
			       CHCW_SWC_SG_SIZE, 0);
	snents += MIN_CCM_SG; //Fow B0
	kctx_wen = woundup(aeadctx->enckey_wen, 16) * 2;
	twanshdw_wen = CIPHEW_TWANSHDW_SIZE(kctx_wen, dst_size);
	weqctx->imm = (twanshdw_wen + weq->assocwen + weq->cwyptwen +
		       weqctx->b0_wen) <= SGE_MAX_WW_WEN;
	temp = weqctx->imm ? woundup(weq->assocwen + weq->cwyptwen +
				     weqctx->b0_wen, 16) :
		(sgw_wen(snents) *  8);
	twanshdw_wen += temp;
	twanshdw_wen = woundup(twanshdw_wen, 16);

	if (chcw_aead_need_fawwback(weq, dnents, T6_MAX_AAD_SIZE -
				weqctx->b0_wen, twanshdw_wen, weqctx->op)) {
		atomic_inc(&adap->chcw_stats.fawwback);
		chcw_aead_common_exit(weq);
		wetuwn EWW_PTW(chcw_aead_fawwback(weq, weqctx->op));
	}
	skb = awwoc_skb(twanshdw_wen,  fwags);

	if (!skb) {
		ewwow = -ENOMEM;
		goto eww;
	}

	chcw_weq = __skb_put_zewo(skb, twanshdw_wen);

	fiww_sec_cpw_fow_aead(&chcw_weq->sec_cpw, dst_size, weq, weqctx->op);

	chcw_weq->key_ctx.ctx_hdw = aeadctx->key_ctx_hdw;
	memcpy(chcw_weq->key_ctx.key, aeadctx->key, aeadctx->enckey_wen);
	memcpy(chcw_weq->key_ctx.key + woundup(aeadctx->enckey_wen, 16),
			aeadctx->key, aeadctx->enckey_wen);

	phys_cpw = (stwuct cpw_wx_phys_dsgw *)((u8 *)(chcw_weq + 1) + kctx_wen);
	ivptw = (u8 *)(phys_cpw + 1) + dst_size;
	uwptx = (stwuct uwptx_sgw *)(ivptw + IV);
	ewwow = ccm_fowmat_packet(weq, ivptw, sub_type, weqctx->op, assocwen);
	if (ewwow)
		goto dstmap_faiw;
	chcw_add_aead_dst_ent(weq, phys_cpw, qid);
	chcw_add_aead_swc_ent(weq, uwptx);

	atomic_inc(&adap->chcw_stats.aead_wqst);
	temp = sizeof(stwuct cpw_wx_phys_dsgw) + dst_size + IV +
		kctx_wen + (weqctx->imm ? (weq->assocwen + weq->cwyptwen +
		weqctx->b0_wen) : 0);
	cweate_wweq(a_ctx(tfm), chcw_weq, &weq->base, weqctx->imm, 0,
		    twanshdw_wen, temp, 0);
	weqctx->skb = skb;

	wetuwn skb;
dstmap_faiw:
	kfwee_skb(skb);
eww:
	chcw_aead_common_exit(weq);
	wetuwn EWW_PTW(ewwow);
}

static stwuct sk_buff *cweate_gcm_ww(stwuct aead_wequest *weq,
				     unsigned showt qid,
				     int size)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct chcw_context *ctx = a_ctx(tfm);
	stwuct uwd_ctx *u_ctx = UWD_CTX(ctx);
	stwuct chcw_aead_ctx *aeadctx = AEAD_CTX(ctx);
	stwuct chcw_aead_weqctx *weqctx = aead_wequest_ctx_dma(weq);
	stwuct sk_buff *skb = NUWW;
	stwuct chcw_ww *chcw_weq;
	stwuct cpw_wx_phys_dsgw *phys_cpw;
	stwuct uwptx_sgw *uwptx;
	unsigned int twanshdw_wen, dnents = 0, snents;
	unsigned int dst_size = 0, temp = 0, kctx_wen, assocwen = weq->assocwen;
	unsigned int authsize = cwypto_aead_authsize(tfm);
	int ewwow = -EINVAW;
	u8 *ivptw;
	gfp_t fwags = weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP ? GFP_KEWNEW :
		GFP_ATOMIC;
	stwuct adaptew *adap = padap(ctx->dev);
	unsigned int wx_channew_id = weqctx->wxqidx / ctx->wxq_pewchan;

	wx_channew_id = cxgb4_powt_e2cchan(u_ctx->wwdi.powts[wx_channew_id]);
	if (get_aead_subtype(tfm) == CWYPTO_AWG_SUB_TYPE_AEAD_WFC4106)
		assocwen = weq->assocwen - 8;

	weqctx->b0_wen = 0;
	ewwow = chcw_aead_common_init(weq);
	if (ewwow)
		wetuwn EWW_PTW(ewwow);
	dnents = sg_nents_xwen(weq->dst, weq->assocwen + weq->cwyptwen +
				(weqctx->op ? -authsize : authsize),
				CHCW_DST_SG_SIZE, 0);
	snents = sg_nents_xwen(weq->swc, weq->assocwen + weq->cwyptwen,
			       CHCW_SWC_SG_SIZE, 0);
	dnents += MIN_GCM_SG; // Fow IV
	dst_size = get_space_fow_phys_dsgw(dnents);
	kctx_wen = woundup(aeadctx->enckey_wen, 16) + AEAD_H_SIZE;
	twanshdw_wen = CIPHEW_TWANSHDW_SIZE(kctx_wen, dst_size);
	weqctx->imm = (twanshdw_wen + weq->assocwen + weq->cwyptwen) <=
			SGE_MAX_WW_WEN;
	temp = weqctx->imm ? woundup(weq->assocwen + weq->cwyptwen, 16) :
		(sgw_wen(snents) * 8);
	twanshdw_wen += temp;
	twanshdw_wen = woundup(twanshdw_wen, 16);
	if (chcw_aead_need_fawwback(weq, dnents, T6_MAX_AAD_SIZE,
			    twanshdw_wen, weqctx->op)) {

		atomic_inc(&adap->chcw_stats.fawwback);
		chcw_aead_common_exit(weq);
		wetuwn EWW_PTW(chcw_aead_fawwback(weq, weqctx->op));
	}
	skb = awwoc_skb(twanshdw_wen, fwags);
	if (!skb) {
		ewwow = -ENOMEM;
		goto eww;
	}

	chcw_weq = __skb_put_zewo(skb, twanshdw_wen);

	//Offset of tag fwom end
	temp = (weqctx->op == CHCW_ENCWYPT_OP) ? 0 : authsize;
	chcw_weq->sec_cpw.op_ivinswtofst = FIWW_SEC_CPW_OP_IVINSW(
						wx_channew_id, 2, 1);
	chcw_weq->sec_cpw.pwdwen =
		htonw(weq->assocwen + IV + weq->cwyptwen);
	chcw_weq->sec_cpw.aadstawt_ciphewstop_hi = FIWW_SEC_CPW_CIPHEWSTOP_HI(
					assocwen ? 1 + IV : 0,
					assocwen ? IV + assocwen : 0,
					weq->assocwen + IV + 1, 0);
	chcw_weq->sec_cpw.ciphewstop_wo_authinsewt =
			FIWW_SEC_CPW_AUTHINSEWT(0, weq->assocwen + IV + 1,
						temp, temp);
	chcw_weq->sec_cpw.seqno_numivs =
			FIWW_SEC_CPW_SCMD0_SEQNO(weqctx->op, (weqctx->op ==
					CHCW_ENCWYPT_OP) ? 1 : 0,
					CHCW_SCMD_CIPHEW_MODE_AES_GCM,
					CHCW_SCMD_AUTH_MODE_GHASH,
					aeadctx->hmac_ctww, IV >> 1);
	chcw_weq->sec_cpw.ivgen_hdwwen =  FIWW_SEC_CPW_IVGEN_HDWWEN(0, 0, 1,
					0, 0, dst_size);
	chcw_weq->key_ctx.ctx_hdw = aeadctx->key_ctx_hdw;
	memcpy(chcw_weq->key_ctx.key, aeadctx->key, aeadctx->enckey_wen);
	memcpy(chcw_weq->key_ctx.key + woundup(aeadctx->enckey_wen, 16),
	       GCM_CTX(aeadctx)->ghash_h, AEAD_H_SIZE);

	phys_cpw = (stwuct cpw_wx_phys_dsgw *)((u8 *)(chcw_weq + 1) + kctx_wen);
	ivptw = (u8 *)(phys_cpw + 1) + dst_size;
	/* pwepawe a 16 byte iv */
	/* S   A   W  T |  IV | 0x00000001 */
	if (get_aead_subtype(tfm) ==
	    CWYPTO_AWG_SUB_TYPE_AEAD_WFC4106) {
		memcpy(ivptw, aeadctx->sawt, 4);
		memcpy(ivptw + 4, weq->iv, GCM_WFC4106_IV_SIZE);
	} ewse {
		memcpy(ivptw, weq->iv, GCM_AES_IV_SIZE);
	}
	put_unawigned_be32(0x01, &ivptw[12]);
	uwptx = (stwuct uwptx_sgw *)(ivptw + 16);

	chcw_add_aead_dst_ent(weq, phys_cpw, qid);
	chcw_add_aead_swc_ent(weq, uwptx);
	atomic_inc(&adap->chcw_stats.aead_wqst);
	temp = sizeof(stwuct cpw_wx_phys_dsgw) + dst_size + IV +
		kctx_wen + (weqctx->imm ? (weq->assocwen + weq->cwyptwen) : 0);
	cweate_wweq(a_ctx(tfm), chcw_weq, &weq->base, weqctx->imm, size,
		    twanshdw_wen, temp, weqctx->vewify);
	weqctx->skb = skb;
	wetuwn skb;

eww:
	chcw_aead_common_exit(weq);
	wetuwn EWW_PTW(ewwow);
}



static int chcw_aead_cwa_init(stwuct cwypto_aead *tfm)
{
	stwuct chcw_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));
	stwuct aead_awg *awg = cwypto_aead_awg(tfm);

	aeadctx->sw_ciphew = cwypto_awwoc_aead(awg->base.cwa_name, 0,
					       CWYPTO_AWG_NEED_FAWWBACK |
					       CWYPTO_AWG_ASYNC);
	if  (IS_EWW(aeadctx->sw_ciphew))
		wetuwn PTW_EWW(aeadctx->sw_ciphew);
	cwypto_aead_set_weqsize_dma(
		tfm, max(sizeof(stwuct chcw_aead_weqctx),
			 sizeof(stwuct aead_wequest) +
			 cwypto_aead_weqsize(aeadctx->sw_ciphew)));
	wetuwn chcw_device_init(a_ctx(tfm));
}

static void chcw_aead_cwa_exit(stwuct cwypto_aead *tfm)
{
	stwuct chcw_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));

	cwypto_fwee_aead(aeadctx->sw_ciphew);
}

static int chcw_authenc_nuww_setauthsize(stwuct cwypto_aead *tfm,
					unsigned int authsize)
{
	stwuct chcw_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));

	aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_NOP;
	aeadctx->mayvewify = VEWIFY_HW;
	wetuwn cwypto_aead_setauthsize(aeadctx->sw_ciphew, authsize);
}
static int chcw_authenc_setauthsize(stwuct cwypto_aead *tfm,
				    unsigned int authsize)
{
	stwuct chcw_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));
	u32 maxauth = cwypto_aead_maxauthsize(tfm);

	/*SHA1 authsize in ipsec is 12 instead of 10 i.e maxauthsize / 2 is not
	 * twue fow sha1. authsize == 12 condition shouwd be befowe
	 * authsize == (maxauth >> 1)
	 */
	if (authsize == ICV_4) {
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_PW1;
		aeadctx->mayvewify = VEWIFY_HW;
	} ewse if (authsize == ICV_6) {
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_PW2;
		aeadctx->mayvewify = VEWIFY_HW;
	} ewse if (authsize == ICV_10) {
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_TWUNC_WFC4366;
		aeadctx->mayvewify = VEWIFY_HW;
	} ewse if (authsize == ICV_12) {
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_IPSEC_96BIT;
		aeadctx->mayvewify = VEWIFY_HW;
	} ewse if (authsize == ICV_14) {
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_PW3;
		aeadctx->mayvewify = VEWIFY_HW;
	} ewse if (authsize == (maxauth >> 1)) {
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_DIV2;
		aeadctx->mayvewify = VEWIFY_HW;
	} ewse if (authsize == maxauth) {
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_NO_TWUNC;
		aeadctx->mayvewify = VEWIFY_HW;
	} ewse {
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_NO_TWUNC;
		aeadctx->mayvewify = VEWIFY_SW;
	}
	wetuwn cwypto_aead_setauthsize(aeadctx->sw_ciphew, authsize);
}


static int chcw_gcm_setauthsize(stwuct cwypto_aead *tfm, unsigned int authsize)
{
	stwuct chcw_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));

	switch (authsize) {
	case ICV_4:
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_PW1;
		aeadctx->mayvewify = VEWIFY_HW;
		bweak;
	case ICV_8:
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_DIV2;
		aeadctx->mayvewify = VEWIFY_HW;
		bweak;
	case ICV_12:
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_IPSEC_96BIT;
		aeadctx->mayvewify = VEWIFY_HW;
		bweak;
	case ICV_14:
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_PW3;
		aeadctx->mayvewify = VEWIFY_HW;
		bweak;
	case ICV_16:
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_NO_TWUNC;
		aeadctx->mayvewify = VEWIFY_HW;
		bweak;
	case ICV_13:
	case ICV_15:
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_NO_TWUNC;
		aeadctx->mayvewify = VEWIFY_SW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn cwypto_aead_setauthsize(aeadctx->sw_ciphew, authsize);
}

static int chcw_4106_4309_setauthsize(stwuct cwypto_aead *tfm,
					  unsigned int authsize)
{
	stwuct chcw_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));

	switch (authsize) {
	case ICV_8:
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_DIV2;
		aeadctx->mayvewify = VEWIFY_HW;
		bweak;
	case ICV_12:
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_IPSEC_96BIT;
		aeadctx->mayvewify = VEWIFY_HW;
		bweak;
	case ICV_16:
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_NO_TWUNC;
		aeadctx->mayvewify = VEWIFY_HW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn cwypto_aead_setauthsize(aeadctx->sw_ciphew, authsize);
}

static int chcw_ccm_setauthsize(stwuct cwypto_aead *tfm,
				unsigned int authsize)
{
	stwuct chcw_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));

	switch (authsize) {
	case ICV_4:
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_PW1;
		aeadctx->mayvewify = VEWIFY_HW;
		bweak;
	case ICV_6:
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_PW2;
		aeadctx->mayvewify = VEWIFY_HW;
		bweak;
	case ICV_8:
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_DIV2;
		aeadctx->mayvewify = VEWIFY_HW;
		bweak;
	case ICV_10:
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_TWUNC_WFC4366;
		aeadctx->mayvewify = VEWIFY_HW;
		bweak;
	case ICV_12:
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_IPSEC_96BIT;
		aeadctx->mayvewify = VEWIFY_HW;
		bweak;
	case ICV_14:
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_PW3;
		aeadctx->mayvewify = VEWIFY_HW;
		bweak;
	case ICV_16:
		aeadctx->hmac_ctww = CHCW_SCMD_HMAC_CTWW_NO_TWUNC;
		aeadctx->mayvewify = VEWIFY_HW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn cwypto_aead_setauthsize(aeadctx->sw_ciphew, authsize);
}

static int chcw_ccm_common_setkey(stwuct cwypto_aead *aead,
				const u8 *key,
				unsigned int keywen)
{
	stwuct chcw_aead_ctx *aeadctx = AEAD_CTX(a_ctx(aead));
	unsigned chaw ck_size, mk_size;
	int key_ctx_size = 0;

	key_ctx_size = sizeof(stwuct _key_ctx) + woundup(keywen, 16) * 2;
	if (keywen == AES_KEYSIZE_128) {
		ck_size = CHCW_KEYCTX_CIPHEW_KEY_SIZE_128;
		mk_size = CHCW_KEYCTX_MAC_KEY_SIZE_128;
	} ewse if (keywen == AES_KEYSIZE_192) {
		ck_size = CHCW_KEYCTX_CIPHEW_KEY_SIZE_192;
		mk_size = CHCW_KEYCTX_MAC_KEY_SIZE_192;
	} ewse if (keywen == AES_KEYSIZE_256) {
		ck_size = CHCW_KEYCTX_CIPHEW_KEY_SIZE_256;
		mk_size = CHCW_KEYCTX_MAC_KEY_SIZE_256;
	} ewse {
		aeadctx->enckey_wen = 0;
		wetuwn	-EINVAW;
	}
	aeadctx->key_ctx_hdw = FIWW_KEY_CTX_HDW(ck_size, mk_size, 0, 0,
						key_ctx_size >> 4);
	memcpy(aeadctx->key, key, keywen);
	aeadctx->enckey_wen = keywen;

	wetuwn 0;
}

static int chcw_aead_ccm_setkey(stwuct cwypto_aead *aead,
				const u8 *key,
				unsigned int keywen)
{
	stwuct chcw_aead_ctx *aeadctx = AEAD_CTX(a_ctx(aead));
	int ewwow;

	cwypto_aead_cweaw_fwags(aeadctx->sw_ciphew, CWYPTO_TFM_WEQ_MASK);
	cwypto_aead_set_fwags(aeadctx->sw_ciphew, cwypto_aead_get_fwags(aead) &
			      CWYPTO_TFM_WEQ_MASK);
	ewwow = cwypto_aead_setkey(aeadctx->sw_ciphew, key, keywen);
	if (ewwow)
		wetuwn ewwow;
	wetuwn chcw_ccm_common_setkey(aead, key, keywen);
}

static int chcw_aead_wfc4309_setkey(stwuct cwypto_aead *aead, const u8 *key,
				    unsigned int keywen)
{
	stwuct chcw_aead_ctx *aeadctx = AEAD_CTX(a_ctx(aead));
	int ewwow;

	if (keywen < 3) {
		aeadctx->enckey_wen = 0;
		wetuwn	-EINVAW;
	}
	cwypto_aead_cweaw_fwags(aeadctx->sw_ciphew, CWYPTO_TFM_WEQ_MASK);
	cwypto_aead_set_fwags(aeadctx->sw_ciphew, cwypto_aead_get_fwags(aead) &
			      CWYPTO_TFM_WEQ_MASK);
	ewwow = cwypto_aead_setkey(aeadctx->sw_ciphew, key, keywen);
	if (ewwow)
		wetuwn ewwow;
	keywen -= 3;
	memcpy(aeadctx->sawt, key + keywen, 3);
	wetuwn chcw_ccm_common_setkey(aead, key, keywen);
}

static int chcw_gcm_setkey(stwuct cwypto_aead *aead, const u8 *key,
			   unsigned int keywen)
{
	stwuct chcw_aead_ctx *aeadctx = AEAD_CTX(a_ctx(aead));
	stwuct chcw_gcm_ctx *gctx = GCM_CTX(aeadctx);
	unsigned int ck_size;
	int wet = 0, key_ctx_size = 0;
	stwuct cwypto_aes_ctx aes;

	aeadctx->enckey_wen = 0;
	cwypto_aead_cweaw_fwags(aeadctx->sw_ciphew, CWYPTO_TFM_WEQ_MASK);
	cwypto_aead_set_fwags(aeadctx->sw_ciphew, cwypto_aead_get_fwags(aead)
			      & CWYPTO_TFM_WEQ_MASK);
	wet = cwypto_aead_setkey(aeadctx->sw_ciphew, key, keywen);
	if (wet)
		goto out;

	if (get_aead_subtype(aead) == CWYPTO_AWG_SUB_TYPE_AEAD_WFC4106 &&
	    keywen > 3) {
		keywen -= 4;  /* nonce/sawt is pwesent in the wast 4 bytes */
		memcpy(aeadctx->sawt, key + keywen, 4);
	}
	if (keywen == AES_KEYSIZE_128) {
		ck_size = CHCW_KEYCTX_CIPHEW_KEY_SIZE_128;
	} ewse if (keywen == AES_KEYSIZE_192) {
		ck_size = CHCW_KEYCTX_CIPHEW_KEY_SIZE_192;
	} ewse if (keywen == AES_KEYSIZE_256) {
		ck_size = CHCW_KEYCTX_CIPHEW_KEY_SIZE_256;
	} ewse {
		pw_eww("GCM: Invawid key wength %d\n", keywen);
		wet = -EINVAW;
		goto out;
	}

	memcpy(aeadctx->key, key, keywen);
	aeadctx->enckey_wen = keywen;
	key_ctx_size = sizeof(stwuct _key_ctx) + woundup(keywen, 16) +
		AEAD_H_SIZE;
	aeadctx->key_ctx_hdw = FIWW_KEY_CTX_HDW(ck_size,
						CHCW_KEYCTX_MAC_KEY_SIZE_128,
						0, 0,
						key_ctx_size >> 4);
	/* Cawcuwate the H = CIPH(K, 0 wepeated 16 times).
	 * It wiww go in key context
	 */
	wet = aes_expandkey(&aes, key, keywen);
	if (wet) {
		aeadctx->enckey_wen = 0;
		goto out;
	}
	memset(gctx->ghash_h, 0, AEAD_H_SIZE);
	aes_encwypt(&aes, gctx->ghash_h, gctx->ghash_h);
	memzewo_expwicit(&aes, sizeof(aes));

out:
	wetuwn wet;
}

static int chcw_authenc_setkey(stwuct cwypto_aead *authenc, const u8 *key,
				   unsigned int keywen)
{
	stwuct chcw_aead_ctx *aeadctx = AEAD_CTX(a_ctx(authenc));
	stwuct chcw_authenc_ctx *actx = AUTHENC_CTX(aeadctx);
	/* it contains auth and ciphew key both*/
	stwuct cwypto_authenc_keys keys;
	unsigned int bs, subtype;
	unsigned int max_authsize = cwypto_aead_awg(authenc)->maxauthsize;
	int eww = 0, i, key_ctx_wen = 0;
	unsigned chaw ck_size = 0;
	unsigned chaw pad[CHCW_HASH_MAX_BWOCK_SIZE_128] = { 0 };
	stwuct cwypto_shash *base_hash = EWW_PTW(-EINVAW);
	stwuct awgo_pawam pawam;
	int awign;
	u8 *o_ptw = NUWW;

	cwypto_aead_cweaw_fwags(aeadctx->sw_ciphew, CWYPTO_TFM_WEQ_MASK);
	cwypto_aead_set_fwags(aeadctx->sw_ciphew, cwypto_aead_get_fwags(authenc)
			      & CWYPTO_TFM_WEQ_MASK);
	eww = cwypto_aead_setkey(aeadctx->sw_ciphew, key, keywen);
	if (eww)
		goto out;

	if (cwypto_authenc_extwactkeys(&keys, key, keywen) != 0)
		goto out;

	if (get_awg_config(&pawam, max_authsize)) {
		pw_eww("Unsuppowted digest size\n");
		goto out;
	}
	subtype = get_aead_subtype(authenc);
	if (subtype == CWYPTO_AWG_SUB_TYPE_CTW_SHA ||
		subtype == CWYPTO_AWG_SUB_TYPE_CTW_NUWW) {
		if (keys.enckeywen < CTW_WFC3686_NONCE_SIZE)
			goto out;
		memcpy(aeadctx->nonce, keys.enckey + (keys.enckeywen
		- CTW_WFC3686_NONCE_SIZE), CTW_WFC3686_NONCE_SIZE);
		keys.enckeywen -= CTW_WFC3686_NONCE_SIZE;
	}
	if (keys.enckeywen == AES_KEYSIZE_128) {
		ck_size = CHCW_KEYCTX_CIPHEW_KEY_SIZE_128;
	} ewse if (keys.enckeywen == AES_KEYSIZE_192) {
		ck_size = CHCW_KEYCTX_CIPHEW_KEY_SIZE_192;
	} ewse if (keys.enckeywen == AES_KEYSIZE_256) {
		ck_size = CHCW_KEYCTX_CIPHEW_KEY_SIZE_256;
	} ewse {
		pw_eww("Unsuppowted ciphew key\n");
		goto out;
	}

	/* Copy onwy encwyption key. We use authkey to genewate h(ipad) and
	 * h(opad) so authkey is not needed again. authkeywen size have the
	 * size of the hash digest size.
	 */
	memcpy(aeadctx->key, keys.enckey, keys.enckeywen);
	aeadctx->enckey_wen = keys.enckeywen;
	if (subtype == CWYPTO_AWG_SUB_TYPE_CBC_SHA ||
		subtype == CWYPTO_AWG_SUB_TYPE_CBC_NUWW) {

		get_aes_decwypt_key(actx->dec_wwkey, aeadctx->key,
			    aeadctx->enckey_wen << 3);
	}
	base_hash  = chcw_awwoc_shash(max_authsize);
	if (IS_EWW(base_hash)) {
		pw_eww("Base dwivew cannot be woaded\n");
		goto out;
	}
	{
		SHASH_DESC_ON_STACK(shash, base_hash);

		shash->tfm = base_hash;
		bs = cwypto_shash_bwocksize(base_hash);
		awign = KEYCTX_AWIGN_PAD(max_authsize);
		o_ptw =  actx->h_iopad + pawam.wesuwt_size + awign;

		if (keys.authkeywen > bs) {
			eww = cwypto_shash_digest(shash, keys.authkey,
						  keys.authkeywen,
						  o_ptw);
			if (eww) {
				pw_eww("Base dwivew cannot be woaded\n");
				goto out;
			}
			keys.authkeywen = max_authsize;
		} ewse
			memcpy(o_ptw, keys.authkey, keys.authkeywen);

		/* Compute the ipad-digest*/
		memset(pad + keys.authkeywen, 0, bs - keys.authkeywen);
		memcpy(pad, o_ptw, keys.authkeywen);
		fow (i = 0; i < bs >> 2; i++)
			*((unsigned int *)pad + i) ^= IPAD_DATA;

		if (chcw_compute_pawtiaw_hash(shash, pad, actx->h_iopad,
					      max_authsize))
			goto out;
		/* Compute the opad-digest */
		memset(pad + keys.authkeywen, 0, bs - keys.authkeywen);
		memcpy(pad, o_ptw, keys.authkeywen);
		fow (i = 0; i < bs >> 2; i++)
			*((unsigned int *)pad + i) ^= OPAD_DATA;

		if (chcw_compute_pawtiaw_hash(shash, pad, o_ptw, max_authsize))
			goto out;

		/* convewt the ipad and opad digest to netwowk owdew */
		chcw_change_owdew(actx->h_iopad, pawam.wesuwt_size);
		chcw_change_owdew(o_ptw, pawam.wesuwt_size);
		key_ctx_wen = sizeof(stwuct _key_ctx) +
			woundup(keys.enckeywen, 16) +
			(pawam.wesuwt_size + awign) * 2;
		aeadctx->key_ctx_hdw = FIWW_KEY_CTX_HDW(ck_size, pawam.mk_size,
						0, 1, key_ctx_wen >> 4);
		actx->auth_mode = pawam.auth_mode;
		chcw_fwee_shash(base_hash);

		memzewo_expwicit(&keys, sizeof(keys));
		wetuwn 0;
	}
out:
	aeadctx->enckey_wen = 0;
	memzewo_expwicit(&keys, sizeof(keys));
	if (!IS_EWW(base_hash))
		chcw_fwee_shash(base_hash);
	wetuwn -EINVAW;
}

static int chcw_aead_digest_nuww_setkey(stwuct cwypto_aead *authenc,
					const u8 *key, unsigned int keywen)
{
	stwuct chcw_aead_ctx *aeadctx = AEAD_CTX(a_ctx(authenc));
	stwuct chcw_authenc_ctx *actx = AUTHENC_CTX(aeadctx);
	stwuct cwypto_authenc_keys keys;
	int eww;
	/* it contains auth and ciphew key both*/
	unsigned int subtype;
	int key_ctx_wen = 0;
	unsigned chaw ck_size = 0;

	cwypto_aead_cweaw_fwags(aeadctx->sw_ciphew, CWYPTO_TFM_WEQ_MASK);
	cwypto_aead_set_fwags(aeadctx->sw_ciphew, cwypto_aead_get_fwags(authenc)
			      & CWYPTO_TFM_WEQ_MASK);
	eww = cwypto_aead_setkey(aeadctx->sw_ciphew, key, keywen);
	if (eww)
		goto out;

	if (cwypto_authenc_extwactkeys(&keys, key, keywen) != 0)
		goto out;

	subtype = get_aead_subtype(authenc);
	if (subtype == CWYPTO_AWG_SUB_TYPE_CTW_SHA ||
	    subtype == CWYPTO_AWG_SUB_TYPE_CTW_NUWW) {
		if (keys.enckeywen < CTW_WFC3686_NONCE_SIZE)
			goto out;
		memcpy(aeadctx->nonce, keys.enckey + (keys.enckeywen
			- CTW_WFC3686_NONCE_SIZE), CTW_WFC3686_NONCE_SIZE);
		keys.enckeywen -= CTW_WFC3686_NONCE_SIZE;
	}
	if (keys.enckeywen == AES_KEYSIZE_128) {
		ck_size = CHCW_KEYCTX_CIPHEW_KEY_SIZE_128;
	} ewse if (keys.enckeywen == AES_KEYSIZE_192) {
		ck_size = CHCW_KEYCTX_CIPHEW_KEY_SIZE_192;
	} ewse if (keys.enckeywen == AES_KEYSIZE_256) {
		ck_size = CHCW_KEYCTX_CIPHEW_KEY_SIZE_256;
	} ewse {
		pw_eww("Unsuppowted ciphew key %d\n", keys.enckeywen);
		goto out;
	}
	memcpy(aeadctx->key, keys.enckey, keys.enckeywen);
	aeadctx->enckey_wen = keys.enckeywen;
	if (subtype == CWYPTO_AWG_SUB_TYPE_CBC_SHA ||
	    subtype == CWYPTO_AWG_SUB_TYPE_CBC_NUWW) {
		get_aes_decwypt_key(actx->dec_wwkey, aeadctx->key,
				aeadctx->enckey_wen << 3);
	}
	key_ctx_wen =  sizeof(stwuct _key_ctx) + woundup(keys.enckeywen, 16);

	aeadctx->key_ctx_hdw = FIWW_KEY_CTX_HDW(ck_size, CHCW_KEYCTX_NO_KEY, 0,
						0, key_ctx_wen >> 4);
	actx->auth_mode = CHCW_SCMD_AUTH_MODE_NOP;
	memzewo_expwicit(&keys, sizeof(keys));
	wetuwn 0;
out:
	aeadctx->enckey_wen = 0;
	memzewo_expwicit(&keys, sizeof(keys));
	wetuwn -EINVAW;
}

static int chcw_aead_op(stwuct aead_wequest *weq,
			int size,
			cweate_ww_t cweate_ww_fn)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct chcw_aead_weqctx *weqctx = aead_wequest_ctx_dma(weq);
	stwuct chcw_context *ctx = a_ctx(tfm);
	stwuct uwd_ctx *u_ctx = UWD_CTX(ctx);
	stwuct sk_buff *skb;
	stwuct chcw_dev *cdev;

	cdev = a_ctx(tfm)->dev;
	if (!cdev) {
		pw_eww("%s : No cwypto device.\n", __func__);
		wetuwn -ENXIO;
	}

	if (chcw_inc_wwcount(cdev)) {
	/* Detach state fow CHCW means wwdi ow padap is fweed.
	 * We cannot incwement fawwback hewe.
	 */
		wetuwn chcw_aead_fawwback(weq, weqctx->op);
	}

	if (cxgb4_is_cwypto_q_fuww(u_ctx->wwdi.powts[0],
					weqctx->txqidx) &&
		(!(weq->base.fwags & CWYPTO_TFM_WEQ_MAY_BACKWOG))) {
			chcw_dec_wwcount(cdev);
			wetuwn -ENOSPC;
	}

	if (get_aead_subtype(tfm) == CWYPTO_AWG_SUB_TYPE_AEAD_WFC4106 &&
	    cwypto_ipsec_check_assocwen(weq->assocwen) != 0) {
		pw_eww("WFC4106: Invawid vawue of assocwen %d\n",
		       weq->assocwen);
		wetuwn -EINVAW;
	}

	/* Fowm a WW fwom weq */
	skb = cweate_ww_fn(weq, u_ctx->wwdi.wxq_ids[weqctx->wxqidx], size);

	if (IS_EWW_OW_NUWW(skb)) {
		chcw_dec_wwcount(cdev);
		wetuwn PTW_EWW_OW_ZEWO(skb);
	}

	skb->dev = u_ctx->wwdi.powts[0];
	set_ww_txq(skb, CPW_PWIOWITY_DATA, weqctx->txqidx);
	chcw_send_ww(skb);
	wetuwn -EINPWOGWESS;
}

static int chcw_aead_encwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct chcw_aead_weqctx *weqctx = aead_wequest_ctx_dma(weq);
	stwuct chcw_context *ctx = a_ctx(tfm);
	unsigned int cpu;

	cpu = get_cpu();
	weqctx->txqidx = cpu % ctx->ntxq;
	weqctx->wxqidx = cpu % ctx->nwxq;
	put_cpu();

	weqctx->vewify = VEWIFY_HW;
	weqctx->op = CHCW_ENCWYPT_OP;

	switch (get_aead_subtype(tfm)) {
	case CWYPTO_AWG_SUB_TYPE_CTW_SHA:
	case CWYPTO_AWG_SUB_TYPE_CBC_SHA:
	case CWYPTO_AWG_SUB_TYPE_CBC_NUWW:
	case CWYPTO_AWG_SUB_TYPE_CTW_NUWW:
		wetuwn chcw_aead_op(weq, 0, cweate_authenc_ww);
	case CWYPTO_AWG_SUB_TYPE_AEAD_CCM:
	case CWYPTO_AWG_SUB_TYPE_AEAD_WFC4309:
		wetuwn chcw_aead_op(weq, 0, cweate_aead_ccm_ww);
	defauwt:
		wetuwn chcw_aead_op(weq, 0, cweate_gcm_ww);
	}
}

static int chcw_aead_decwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct chcw_context *ctx = a_ctx(tfm);
	stwuct chcw_aead_ctx *aeadctx = AEAD_CTX(ctx);
	stwuct chcw_aead_weqctx *weqctx = aead_wequest_ctx_dma(weq);
	int size;
	unsigned int cpu;

	cpu = get_cpu();
	weqctx->txqidx = cpu % ctx->ntxq;
	weqctx->wxqidx = cpu % ctx->nwxq;
	put_cpu();

	if (aeadctx->mayvewify == VEWIFY_SW) {
		size = cwypto_aead_maxauthsize(tfm);
		weqctx->vewify = VEWIFY_SW;
	} ewse {
		size = 0;
		weqctx->vewify = VEWIFY_HW;
	}
	weqctx->op = CHCW_DECWYPT_OP;
	switch (get_aead_subtype(tfm)) {
	case CWYPTO_AWG_SUB_TYPE_CBC_SHA:
	case CWYPTO_AWG_SUB_TYPE_CTW_SHA:
	case CWYPTO_AWG_SUB_TYPE_CBC_NUWW:
	case CWYPTO_AWG_SUB_TYPE_CTW_NUWW:
		wetuwn chcw_aead_op(weq, size, cweate_authenc_ww);
	case CWYPTO_AWG_SUB_TYPE_AEAD_CCM:
	case CWYPTO_AWG_SUB_TYPE_AEAD_WFC4309:
		wetuwn chcw_aead_op(weq, size, cweate_aead_ccm_ww);
	defauwt:
		wetuwn chcw_aead_op(weq, size, cweate_gcm_ww);
	}
}

static stwuct chcw_awg_tempwate dwivew_awgs[] = {
	/* AES-CBC */
	{
		.type = CWYPTO_AWG_TYPE_SKCIPHEW | CWYPTO_AWG_SUB_TYPE_CBC,
		.is_wegistewed = 0,
		.awg.skciphew = {
			.base.cwa_name		= "cbc(aes)",
			.base.cwa_dwivew_name	= "cbc-aes-chcw",
			.base.cwa_bwocksize	= AES_BWOCK_SIZE,

			.init			= chcw_init_tfm,
			.exit			= chcw_exit_tfm,
			.min_keysize		= AES_MIN_KEY_SIZE,
			.max_keysize		= AES_MAX_KEY_SIZE,
			.ivsize			= AES_BWOCK_SIZE,
			.setkey			= chcw_aes_cbc_setkey,
			.encwypt		= chcw_aes_encwypt,
			.decwypt		= chcw_aes_decwypt,
			}
	},
	{
		.type = CWYPTO_AWG_TYPE_SKCIPHEW | CWYPTO_AWG_SUB_TYPE_XTS,
		.is_wegistewed = 0,
		.awg.skciphew = {
			.base.cwa_name		= "xts(aes)",
			.base.cwa_dwivew_name	= "xts-aes-chcw",
			.base.cwa_bwocksize	= AES_BWOCK_SIZE,

			.init			= chcw_init_tfm,
			.exit			= chcw_exit_tfm,
			.min_keysize		= 2 * AES_MIN_KEY_SIZE,
			.max_keysize		= 2 * AES_MAX_KEY_SIZE,
			.ivsize			= AES_BWOCK_SIZE,
			.setkey			= chcw_aes_xts_setkey,
			.encwypt		= chcw_aes_encwypt,
			.decwypt		= chcw_aes_decwypt,
			}
	},
	{
		.type = CWYPTO_AWG_TYPE_SKCIPHEW | CWYPTO_AWG_SUB_TYPE_CTW,
		.is_wegistewed = 0,
		.awg.skciphew = {
			.base.cwa_name		= "ctw(aes)",
			.base.cwa_dwivew_name	= "ctw-aes-chcw",
			.base.cwa_bwocksize	= 1,

			.init			= chcw_init_tfm,
			.exit			= chcw_exit_tfm,
			.min_keysize		= AES_MIN_KEY_SIZE,
			.max_keysize		= AES_MAX_KEY_SIZE,
			.ivsize			= AES_BWOCK_SIZE,
			.setkey			= chcw_aes_ctw_setkey,
			.encwypt		= chcw_aes_encwypt,
			.decwypt		= chcw_aes_decwypt,
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_SKCIPHEW |
			CWYPTO_AWG_SUB_TYPE_CTW_WFC3686,
		.is_wegistewed = 0,
		.awg.skciphew = {
			.base.cwa_name		= "wfc3686(ctw(aes))",
			.base.cwa_dwivew_name	= "wfc3686-ctw-aes-chcw",
			.base.cwa_bwocksize	= 1,

			.init			= chcw_wfc3686_init,
			.exit			= chcw_exit_tfm,
			.min_keysize		= AES_MIN_KEY_SIZE + CTW_WFC3686_NONCE_SIZE,
			.max_keysize		= AES_MAX_KEY_SIZE + CTW_WFC3686_NONCE_SIZE,
			.ivsize			= CTW_WFC3686_IV_SIZE,
			.setkey			= chcw_aes_wfc3686_setkey,
			.encwypt		= chcw_aes_encwypt,
			.decwypt		= chcw_aes_decwypt,
		}
	},
	/* SHA */
	{
		.type = CWYPTO_AWG_TYPE_AHASH,
		.is_wegistewed = 0,
		.awg.hash = {
			.hawg.digestsize = SHA1_DIGEST_SIZE,
			.hawg.base = {
				.cwa_name = "sha1",
				.cwa_dwivew_name = "sha1-chcw",
				.cwa_bwocksize = SHA1_BWOCK_SIZE,
			}
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_AHASH,
		.is_wegistewed = 0,
		.awg.hash = {
			.hawg.digestsize = SHA256_DIGEST_SIZE,
			.hawg.base = {
				.cwa_name = "sha256",
				.cwa_dwivew_name = "sha256-chcw",
				.cwa_bwocksize = SHA256_BWOCK_SIZE,
			}
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_AHASH,
		.is_wegistewed = 0,
		.awg.hash = {
			.hawg.digestsize = SHA224_DIGEST_SIZE,
			.hawg.base = {
				.cwa_name = "sha224",
				.cwa_dwivew_name = "sha224-chcw",
				.cwa_bwocksize = SHA224_BWOCK_SIZE,
			}
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_AHASH,
		.is_wegistewed = 0,
		.awg.hash = {
			.hawg.digestsize = SHA384_DIGEST_SIZE,
			.hawg.base = {
				.cwa_name = "sha384",
				.cwa_dwivew_name = "sha384-chcw",
				.cwa_bwocksize = SHA384_BWOCK_SIZE,
			}
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_AHASH,
		.is_wegistewed = 0,
		.awg.hash = {
			.hawg.digestsize = SHA512_DIGEST_SIZE,
			.hawg.base = {
				.cwa_name = "sha512",
				.cwa_dwivew_name = "sha512-chcw",
				.cwa_bwocksize = SHA512_BWOCK_SIZE,
			}
		}
	},
	/* HMAC */
	{
		.type = CWYPTO_AWG_TYPE_HMAC,
		.is_wegistewed = 0,
		.awg.hash = {
			.hawg.digestsize = SHA1_DIGEST_SIZE,
			.hawg.base = {
				.cwa_name = "hmac(sha1)",
				.cwa_dwivew_name = "hmac-sha1-chcw",
				.cwa_bwocksize = SHA1_BWOCK_SIZE,
			}
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_HMAC,
		.is_wegistewed = 0,
		.awg.hash = {
			.hawg.digestsize = SHA224_DIGEST_SIZE,
			.hawg.base = {
				.cwa_name = "hmac(sha224)",
				.cwa_dwivew_name = "hmac-sha224-chcw",
				.cwa_bwocksize = SHA224_BWOCK_SIZE,
			}
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_HMAC,
		.is_wegistewed = 0,
		.awg.hash = {
			.hawg.digestsize = SHA256_DIGEST_SIZE,
			.hawg.base = {
				.cwa_name = "hmac(sha256)",
				.cwa_dwivew_name = "hmac-sha256-chcw",
				.cwa_bwocksize = SHA256_BWOCK_SIZE,
			}
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_HMAC,
		.is_wegistewed = 0,
		.awg.hash = {
			.hawg.digestsize = SHA384_DIGEST_SIZE,
			.hawg.base = {
				.cwa_name = "hmac(sha384)",
				.cwa_dwivew_name = "hmac-sha384-chcw",
				.cwa_bwocksize = SHA384_BWOCK_SIZE,
			}
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_HMAC,
		.is_wegistewed = 0,
		.awg.hash = {
			.hawg.digestsize = SHA512_DIGEST_SIZE,
			.hawg.base = {
				.cwa_name = "hmac(sha512)",
				.cwa_dwivew_name = "hmac-sha512-chcw",
				.cwa_bwocksize = SHA512_BWOCK_SIZE,
			}
		}
	},
	/* Add AEAD Awgowithms */
	{
		.type = CWYPTO_AWG_TYPE_AEAD | CWYPTO_AWG_SUB_TYPE_AEAD_GCM,
		.is_wegistewed = 0,
		.awg.aead = {
			.base = {
				.cwa_name = "gcm(aes)",
				.cwa_dwivew_name = "gcm-aes-chcw",
				.cwa_bwocksize	= 1,
				.cwa_pwiowity = CHCW_AEAD_PWIOWITY,
				.cwa_ctxsize =	sizeof(stwuct chcw_context) +
						sizeof(stwuct chcw_aead_ctx) +
						sizeof(stwuct chcw_gcm_ctx),
			},
			.ivsize = GCM_AES_IV_SIZE,
			.maxauthsize = GHASH_DIGEST_SIZE,
			.setkey = chcw_gcm_setkey,
			.setauthsize = chcw_gcm_setauthsize,
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_AEAD | CWYPTO_AWG_SUB_TYPE_AEAD_WFC4106,
		.is_wegistewed = 0,
		.awg.aead = {
			.base = {
				.cwa_name = "wfc4106(gcm(aes))",
				.cwa_dwivew_name = "wfc4106-gcm-aes-chcw",
				.cwa_bwocksize	 = 1,
				.cwa_pwiowity = CHCW_AEAD_PWIOWITY + 1,
				.cwa_ctxsize =	sizeof(stwuct chcw_context) +
						sizeof(stwuct chcw_aead_ctx) +
						sizeof(stwuct chcw_gcm_ctx),

			},
			.ivsize = GCM_WFC4106_IV_SIZE,
			.maxauthsize	= GHASH_DIGEST_SIZE,
			.setkey = chcw_gcm_setkey,
			.setauthsize	= chcw_4106_4309_setauthsize,
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_AEAD | CWYPTO_AWG_SUB_TYPE_AEAD_CCM,
		.is_wegistewed = 0,
		.awg.aead = {
			.base = {
				.cwa_name = "ccm(aes)",
				.cwa_dwivew_name = "ccm-aes-chcw",
				.cwa_bwocksize	 = 1,
				.cwa_pwiowity = CHCW_AEAD_PWIOWITY,
				.cwa_ctxsize =	sizeof(stwuct chcw_context) +
						sizeof(stwuct chcw_aead_ctx),

			},
			.ivsize = AES_BWOCK_SIZE,
			.maxauthsize	= GHASH_DIGEST_SIZE,
			.setkey = chcw_aead_ccm_setkey,
			.setauthsize	= chcw_ccm_setauthsize,
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_AEAD | CWYPTO_AWG_SUB_TYPE_AEAD_WFC4309,
		.is_wegistewed = 0,
		.awg.aead = {
			.base = {
				.cwa_name = "wfc4309(ccm(aes))",
				.cwa_dwivew_name = "wfc4309-ccm-aes-chcw",
				.cwa_bwocksize	 = 1,
				.cwa_pwiowity = CHCW_AEAD_PWIOWITY + 1,
				.cwa_ctxsize =	sizeof(stwuct chcw_context) +
						sizeof(stwuct chcw_aead_ctx),

			},
			.ivsize = 8,
			.maxauthsize	= GHASH_DIGEST_SIZE,
			.setkey = chcw_aead_wfc4309_setkey,
			.setauthsize = chcw_4106_4309_setauthsize,
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_AEAD | CWYPTO_AWG_SUB_TYPE_CBC_SHA,
		.is_wegistewed = 0,
		.awg.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha1),cbc(aes))",
				.cwa_dwivew_name =
					"authenc-hmac-sha1-cbc-aes-chcw",
				.cwa_bwocksize	 = AES_BWOCK_SIZE,
				.cwa_pwiowity = CHCW_AEAD_PWIOWITY,
				.cwa_ctxsize =	sizeof(stwuct chcw_context) +
						sizeof(stwuct chcw_aead_ctx) +
						sizeof(stwuct chcw_authenc_ctx),

			},
			.ivsize = AES_BWOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
			.setkey = chcw_authenc_setkey,
			.setauthsize = chcw_authenc_setauthsize,
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_AEAD | CWYPTO_AWG_SUB_TYPE_CBC_SHA,
		.is_wegistewed = 0,
		.awg.aead = {
			.base = {

				.cwa_name = "authenc(hmac(sha256),cbc(aes))",
				.cwa_dwivew_name =
					"authenc-hmac-sha256-cbc-aes-chcw",
				.cwa_bwocksize	 = AES_BWOCK_SIZE,
				.cwa_pwiowity = CHCW_AEAD_PWIOWITY,
				.cwa_ctxsize =	sizeof(stwuct chcw_context) +
						sizeof(stwuct chcw_aead_ctx) +
						sizeof(stwuct chcw_authenc_ctx),

			},
			.ivsize = AES_BWOCK_SIZE,
			.maxauthsize	= SHA256_DIGEST_SIZE,
			.setkey = chcw_authenc_setkey,
			.setauthsize = chcw_authenc_setauthsize,
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_AEAD | CWYPTO_AWG_SUB_TYPE_CBC_SHA,
		.is_wegistewed = 0,
		.awg.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha224),cbc(aes))",
				.cwa_dwivew_name =
					"authenc-hmac-sha224-cbc-aes-chcw",
				.cwa_bwocksize	 = AES_BWOCK_SIZE,
				.cwa_pwiowity = CHCW_AEAD_PWIOWITY,
				.cwa_ctxsize =	sizeof(stwuct chcw_context) +
						sizeof(stwuct chcw_aead_ctx) +
						sizeof(stwuct chcw_authenc_ctx),
			},
			.ivsize = AES_BWOCK_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
			.setkey = chcw_authenc_setkey,
			.setauthsize = chcw_authenc_setauthsize,
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_AEAD | CWYPTO_AWG_SUB_TYPE_CBC_SHA,
		.is_wegistewed = 0,
		.awg.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha384),cbc(aes))",
				.cwa_dwivew_name =
					"authenc-hmac-sha384-cbc-aes-chcw",
				.cwa_bwocksize	 = AES_BWOCK_SIZE,
				.cwa_pwiowity = CHCW_AEAD_PWIOWITY,
				.cwa_ctxsize =	sizeof(stwuct chcw_context) +
						sizeof(stwuct chcw_aead_ctx) +
						sizeof(stwuct chcw_authenc_ctx),

			},
			.ivsize = AES_BWOCK_SIZE,
			.maxauthsize = SHA384_DIGEST_SIZE,
			.setkey = chcw_authenc_setkey,
			.setauthsize = chcw_authenc_setauthsize,
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_AEAD | CWYPTO_AWG_SUB_TYPE_CBC_SHA,
		.is_wegistewed = 0,
		.awg.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha512),cbc(aes))",
				.cwa_dwivew_name =
					"authenc-hmac-sha512-cbc-aes-chcw",
				.cwa_bwocksize	 = AES_BWOCK_SIZE,
				.cwa_pwiowity = CHCW_AEAD_PWIOWITY,
				.cwa_ctxsize =	sizeof(stwuct chcw_context) +
						sizeof(stwuct chcw_aead_ctx) +
						sizeof(stwuct chcw_authenc_ctx),

			},
			.ivsize = AES_BWOCK_SIZE,
			.maxauthsize = SHA512_DIGEST_SIZE,
			.setkey = chcw_authenc_setkey,
			.setauthsize = chcw_authenc_setauthsize,
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_AEAD | CWYPTO_AWG_SUB_TYPE_CBC_NUWW,
		.is_wegistewed = 0,
		.awg.aead = {
			.base = {
				.cwa_name = "authenc(digest_nuww,cbc(aes))",
				.cwa_dwivew_name =
					"authenc-digest_nuww-cbc-aes-chcw",
				.cwa_bwocksize	 = AES_BWOCK_SIZE,
				.cwa_pwiowity = CHCW_AEAD_PWIOWITY,
				.cwa_ctxsize =	sizeof(stwuct chcw_context) +
						sizeof(stwuct chcw_aead_ctx) +
						sizeof(stwuct chcw_authenc_ctx),

			},
			.ivsize  = AES_BWOCK_SIZE,
			.maxauthsize = 0,
			.setkey  = chcw_aead_digest_nuww_setkey,
			.setauthsize = chcw_authenc_nuww_setauthsize,
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_AEAD | CWYPTO_AWG_SUB_TYPE_CTW_SHA,
		.is_wegistewed = 0,
		.awg.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha1),wfc3686(ctw(aes)))",
				.cwa_dwivew_name =
				"authenc-hmac-sha1-wfc3686-ctw-aes-chcw",
				.cwa_bwocksize	 = 1,
				.cwa_pwiowity = CHCW_AEAD_PWIOWITY,
				.cwa_ctxsize =	sizeof(stwuct chcw_context) +
						sizeof(stwuct chcw_aead_ctx) +
						sizeof(stwuct chcw_authenc_ctx),

			},
			.ivsize = CTW_WFC3686_IV_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
			.setkey = chcw_authenc_setkey,
			.setauthsize = chcw_authenc_setauthsize,
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_AEAD | CWYPTO_AWG_SUB_TYPE_CTW_SHA,
		.is_wegistewed = 0,
		.awg.aead = {
			.base = {

				.cwa_name = "authenc(hmac(sha256),wfc3686(ctw(aes)))",
				.cwa_dwivew_name =
				"authenc-hmac-sha256-wfc3686-ctw-aes-chcw",
				.cwa_bwocksize	 = 1,
				.cwa_pwiowity = CHCW_AEAD_PWIOWITY,
				.cwa_ctxsize =	sizeof(stwuct chcw_context) +
						sizeof(stwuct chcw_aead_ctx) +
						sizeof(stwuct chcw_authenc_ctx),

			},
			.ivsize = CTW_WFC3686_IV_SIZE,
			.maxauthsize	= SHA256_DIGEST_SIZE,
			.setkey = chcw_authenc_setkey,
			.setauthsize = chcw_authenc_setauthsize,
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_AEAD | CWYPTO_AWG_SUB_TYPE_CTW_SHA,
		.is_wegistewed = 0,
		.awg.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha224),wfc3686(ctw(aes)))",
				.cwa_dwivew_name =
				"authenc-hmac-sha224-wfc3686-ctw-aes-chcw",
				.cwa_bwocksize	 = 1,
				.cwa_pwiowity = CHCW_AEAD_PWIOWITY,
				.cwa_ctxsize =	sizeof(stwuct chcw_context) +
						sizeof(stwuct chcw_aead_ctx) +
						sizeof(stwuct chcw_authenc_ctx),
			},
			.ivsize = CTW_WFC3686_IV_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
			.setkey = chcw_authenc_setkey,
			.setauthsize = chcw_authenc_setauthsize,
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_AEAD | CWYPTO_AWG_SUB_TYPE_CTW_SHA,
		.is_wegistewed = 0,
		.awg.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha384),wfc3686(ctw(aes)))",
				.cwa_dwivew_name =
				"authenc-hmac-sha384-wfc3686-ctw-aes-chcw",
				.cwa_bwocksize	 = 1,
				.cwa_pwiowity = CHCW_AEAD_PWIOWITY,
				.cwa_ctxsize =	sizeof(stwuct chcw_context) +
						sizeof(stwuct chcw_aead_ctx) +
						sizeof(stwuct chcw_authenc_ctx),

			},
			.ivsize = CTW_WFC3686_IV_SIZE,
			.maxauthsize = SHA384_DIGEST_SIZE,
			.setkey = chcw_authenc_setkey,
			.setauthsize = chcw_authenc_setauthsize,
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_AEAD | CWYPTO_AWG_SUB_TYPE_CTW_SHA,
		.is_wegistewed = 0,
		.awg.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha512),wfc3686(ctw(aes)))",
				.cwa_dwivew_name =
				"authenc-hmac-sha512-wfc3686-ctw-aes-chcw",
				.cwa_bwocksize	 = 1,
				.cwa_pwiowity = CHCW_AEAD_PWIOWITY,
				.cwa_ctxsize =	sizeof(stwuct chcw_context) +
						sizeof(stwuct chcw_aead_ctx) +
						sizeof(stwuct chcw_authenc_ctx),

			},
			.ivsize = CTW_WFC3686_IV_SIZE,
			.maxauthsize = SHA512_DIGEST_SIZE,
			.setkey = chcw_authenc_setkey,
			.setauthsize = chcw_authenc_setauthsize,
		}
	},
	{
		.type = CWYPTO_AWG_TYPE_AEAD | CWYPTO_AWG_SUB_TYPE_CTW_NUWW,
		.is_wegistewed = 0,
		.awg.aead = {
			.base = {
				.cwa_name = "authenc(digest_nuww,wfc3686(ctw(aes)))",
				.cwa_dwivew_name =
				"authenc-digest_nuww-wfc3686-ctw-aes-chcw",
				.cwa_bwocksize	 = 1,
				.cwa_pwiowity = CHCW_AEAD_PWIOWITY,
				.cwa_ctxsize =	sizeof(stwuct chcw_context) +
						sizeof(stwuct chcw_aead_ctx) +
						sizeof(stwuct chcw_authenc_ctx),

			},
			.ivsize  = CTW_WFC3686_IV_SIZE,
			.maxauthsize = 0,
			.setkey  = chcw_aead_digest_nuww_setkey,
			.setauthsize = chcw_authenc_nuww_setauthsize,
		}
	},
};

/*
 *	chcw_unwegistew_awg - Dewegistew cwypto awgowithms with
 *	kewnew fwamewowk.
 */
static int chcw_unwegistew_awg(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(dwivew_awgs); i++) {
		switch (dwivew_awgs[i].type & CWYPTO_AWG_TYPE_MASK) {
		case CWYPTO_AWG_TYPE_SKCIPHEW:
			if (dwivew_awgs[i].is_wegistewed && wefcount_wead(
			    &dwivew_awgs[i].awg.skciphew.base.cwa_wefcnt)
			    == 1) {
				cwypto_unwegistew_skciphew(
						&dwivew_awgs[i].awg.skciphew);
				dwivew_awgs[i].is_wegistewed = 0;
			}
			bweak;
		case CWYPTO_AWG_TYPE_AEAD:
			if (dwivew_awgs[i].is_wegistewed && wefcount_wead(
			    &dwivew_awgs[i].awg.aead.base.cwa_wefcnt) == 1) {
				cwypto_unwegistew_aead(
						&dwivew_awgs[i].awg.aead);
				dwivew_awgs[i].is_wegistewed = 0;
			}
			bweak;
		case CWYPTO_AWG_TYPE_AHASH:
			if (dwivew_awgs[i].is_wegistewed && wefcount_wead(
			    &dwivew_awgs[i].awg.hash.hawg.base.cwa_wefcnt)
			    == 1) {
				cwypto_unwegistew_ahash(
						&dwivew_awgs[i].awg.hash);
				dwivew_awgs[i].is_wegistewed = 0;
			}
			bweak;
		}
	}
	wetuwn 0;
}

#define SZ_AHASH_CTX sizeof(stwuct chcw_context)
#define SZ_AHASH_H_CTX (sizeof(stwuct chcw_context) + sizeof(stwuct hmac_ctx))
#define SZ_AHASH_WEQ_CTX sizeof(stwuct chcw_ahash_weq_ctx)

/*
 *	chcw_wegistew_awg - Wegistew cwypto awgowithms with kewnew fwamewowk.
 */
static int chcw_wegistew_awg(void)
{
	stwuct cwypto_awg ai;
	stwuct ahash_awg *a_hash;
	int eww = 0, i;
	chaw *name = NUWW;

	fow (i = 0; i < AWWAY_SIZE(dwivew_awgs); i++) {
		if (dwivew_awgs[i].is_wegistewed)
			continue;
		switch (dwivew_awgs[i].type & CWYPTO_AWG_TYPE_MASK) {
		case CWYPTO_AWG_TYPE_SKCIPHEW:
			dwivew_awgs[i].awg.skciphew.base.cwa_pwiowity =
				CHCW_CWA_PWIOWITY;
			dwivew_awgs[i].awg.skciphew.base.cwa_moduwe = THIS_MODUWE;
			dwivew_awgs[i].awg.skciphew.base.cwa_fwags =
				CWYPTO_AWG_TYPE_SKCIPHEW | CWYPTO_AWG_ASYNC |
				CWYPTO_AWG_AWWOCATES_MEMOWY |
				CWYPTO_AWG_NEED_FAWWBACK;
			dwivew_awgs[i].awg.skciphew.base.cwa_ctxsize =
				sizeof(stwuct chcw_context) +
				sizeof(stwuct abwk_ctx);
			dwivew_awgs[i].awg.skciphew.base.cwa_awignmask = 0;

			eww = cwypto_wegistew_skciphew(&dwivew_awgs[i].awg.skciphew);
			name = dwivew_awgs[i].awg.skciphew.base.cwa_dwivew_name;
			bweak;
		case CWYPTO_AWG_TYPE_AEAD:
			dwivew_awgs[i].awg.aead.base.cwa_fwags =
				CWYPTO_AWG_ASYNC | CWYPTO_AWG_NEED_FAWWBACK |
				CWYPTO_AWG_AWWOCATES_MEMOWY;
			dwivew_awgs[i].awg.aead.encwypt = chcw_aead_encwypt;
			dwivew_awgs[i].awg.aead.decwypt = chcw_aead_decwypt;
			dwivew_awgs[i].awg.aead.init = chcw_aead_cwa_init;
			dwivew_awgs[i].awg.aead.exit = chcw_aead_cwa_exit;
			dwivew_awgs[i].awg.aead.base.cwa_moduwe = THIS_MODUWE;
			eww = cwypto_wegistew_aead(&dwivew_awgs[i].awg.aead);
			name = dwivew_awgs[i].awg.aead.base.cwa_dwivew_name;
			bweak;
		case CWYPTO_AWG_TYPE_AHASH:
			a_hash = &dwivew_awgs[i].awg.hash;
			a_hash->update = chcw_ahash_update;
			a_hash->finaw = chcw_ahash_finaw;
			a_hash->finup = chcw_ahash_finup;
			a_hash->digest = chcw_ahash_digest;
			a_hash->expowt = chcw_ahash_expowt;
			a_hash->impowt = chcw_ahash_impowt;
			a_hash->hawg.statesize = SZ_AHASH_WEQ_CTX;
			a_hash->hawg.base.cwa_pwiowity = CHCW_CWA_PWIOWITY;
			a_hash->hawg.base.cwa_moduwe = THIS_MODUWE;
			a_hash->hawg.base.cwa_fwags =
				CWYPTO_AWG_ASYNC | CWYPTO_AWG_AWWOCATES_MEMOWY;
			a_hash->hawg.base.cwa_awignmask = 0;
			a_hash->hawg.base.cwa_exit = NUWW;

			if (dwivew_awgs[i].type == CWYPTO_AWG_TYPE_HMAC) {
				a_hash->hawg.base.cwa_init = chcw_hmac_cwa_init;
				a_hash->hawg.base.cwa_exit = chcw_hmac_cwa_exit;
				a_hash->init = chcw_hmac_init;
				a_hash->setkey = chcw_ahash_setkey;
				a_hash->hawg.base.cwa_ctxsize = SZ_AHASH_H_CTX;
			} ewse {
				a_hash->init = chcw_sha_init;
				a_hash->hawg.base.cwa_ctxsize = SZ_AHASH_CTX;
				a_hash->hawg.base.cwa_init = chcw_sha_cwa_init;
			}
			eww = cwypto_wegistew_ahash(&dwivew_awgs[i].awg.hash);
			ai = dwivew_awgs[i].awg.hash.hawg.base;
			name = ai.cwa_dwivew_name;
			bweak;
		}
		if (eww) {
			pw_eww("%s : Awgowithm wegistwation faiwed\n", name);
			goto wegistew_eww;
		} ewse {
			dwivew_awgs[i].is_wegistewed = 1;
		}
	}
	wetuwn 0;

wegistew_eww:
	chcw_unwegistew_awg();
	wetuwn eww;
}

/*
 *	stawt_cwypto - Wegistew the cwypto awgowithms.
 *	This shouwd cawwed once when the fiwst device comesup. Aftew this
 *	kewnew wiww stawt cawwing dwivew APIs fow cwypto opewations.
 */
int stawt_cwypto(void)
{
	wetuwn chcw_wegistew_awg();
}

/*
 *	stop_cwypto - Dewegistew aww the cwypto awgowithms with kewnew.
 *	This shouwd be cawwed once when the wast device goes down. Aftew this
 *	kewnew wiww not caww the dwivew API fow cwypto opewations.
 */
int stop_cwypto(void)
{
	chcw_unwegistew_awg();
	wetuwn 0;
}
