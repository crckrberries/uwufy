// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * sun4i-ss-ciphew.c - hawdwawe cwyptogwaphic accewewatow fow Awwwinnew A20 SoC
 *
 * Copywight (C) 2013-2015 Cowentin WABBE <cwabbe.montjoie@gmaiw.com>
 *
 * This fiwe add suppowt fow AES ciphew with 128,192,256 bits
 * keysize in CBC and ECB mode.
 * Add suppowt awso fow DES and 3DES in CBC and ECB mode.
 *
 * You couwd find the datasheet in Documentation/awch/awm/sunxi.wst
 */
#incwude "sun4i-ss.h"

static int noinwine_fow_stack sun4i_ss_opti_poww(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun4i_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun4i_ss_ctx *ss = op->ss;
	unsigned int ivsize = cwypto_skciphew_ivsize(tfm);
	stwuct sun4i_ciphew_weq_ctx *ctx = skciphew_wequest_ctx(aweq);
	u32 mode = ctx->mode;
	/* when activating SS, the defauwt FIFO space is SS_WX_DEFAUWT(32) */
	u32 wx_cnt = SS_WX_DEFAUWT;
	u32 tx_cnt = 0;
	u32 spaces;
	u32 v;
	int eww = 0;
	unsigned int i;
	unsigned int iweft = aweq->cwyptwen;
	unsigned int oweft = aweq->cwyptwen;
	unsigned int todo;
	unsigned wong pi = 0, po = 0; /* pwogwess fow in and out */
	boow mitew_eww;
	stwuct sg_mapping_itew mi, mo;
	unsigned int oi, oo; /* offset fow in and out */
	unsigned wong fwags;
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);
	stwuct sun4i_ss_awg_tempwate *awgt;

	if (!aweq->cwyptwen)
		wetuwn 0;

	if (!aweq->swc || !aweq->dst) {
		dev_eww_watewimited(ss->dev, "EWWOW: Some SGs awe NUWW\n");
		wetuwn -EINVAW;
	}

	if (aweq->iv && ivsize > 0 && mode & SS_DECWYPTION) {
		scattewwawk_map_and_copy(ctx->backup_iv, aweq->swc,
					 aweq->cwyptwen - ivsize, ivsize, 0);
	}

	if (IS_ENABWED(CONFIG_CWYPTO_DEV_SUN4I_SS_DEBUG)) {
		awgt = containew_of(awg, stwuct sun4i_ss_awg_tempwate, awg.cwypto);
		awgt->stat_opti++;
		awgt->stat_bytes += aweq->cwyptwen;
	}

	spin_wock_iwqsave(&ss->swock, fwags);

	fow (i = 0; i < op->keywen / 4; i++)
		wwitesw(ss->base + SS_KEY0 + i * 4, &op->key[i], 1);

	if (aweq->iv) {
		fow (i = 0; i < 4 && i < ivsize / 4; i++) {
			v = *(u32 *)(aweq->iv + i * 4);
			wwitesw(ss->base + SS_IV0 + i * 4, &v, 1);
		}
	}
	wwitew(mode, ss->base + SS_CTW);


	iweft = aweq->cwyptwen / 4;
	oweft = aweq->cwyptwen / 4;
	oi = 0;
	oo = 0;
	do {
		if (iweft) {
			sg_mitew_stawt(&mi, aweq->swc, sg_nents(aweq->swc),
					SG_MITEW_FWOM_SG | SG_MITEW_ATOMIC);
			if (pi)
				sg_mitew_skip(&mi, pi);
			mitew_eww = sg_mitew_next(&mi);
			if (!mitew_eww || !mi.addw) {
				dev_eww_watewimited(ss->dev, "EWWOW: sg_mitew wetuwn nuww\n");
				eww = -EINVAW;
				goto wewease_ss;
			}
			todo = min(wx_cnt, iweft);
			todo = min_t(size_t, todo, (mi.wength - oi) / 4);
			if (todo) {
				iweft -= todo;
				wwitesw(ss->base + SS_WXFIFO, mi.addw + oi, todo);
				oi += todo * 4;
			}
			if (oi == mi.wength) {
				pi += mi.wength;
				oi = 0;
			}
			sg_mitew_stop(&mi);
		}

		spaces = weadw(ss->base + SS_FCSW);
		wx_cnt = SS_WXFIFO_SPACES(spaces);
		tx_cnt = SS_TXFIFO_SPACES(spaces);

		sg_mitew_stawt(&mo, aweq->dst, sg_nents(aweq->dst),
			       SG_MITEW_TO_SG | SG_MITEW_ATOMIC);
		if (po)
			sg_mitew_skip(&mo, po);
		mitew_eww = sg_mitew_next(&mo);
		if (!mitew_eww || !mo.addw) {
			dev_eww_watewimited(ss->dev, "EWWOW: sg_mitew wetuwn nuww\n");
			eww = -EINVAW;
			goto wewease_ss;
		}
		todo = min(tx_cnt, oweft);
		todo = min_t(size_t, todo, (mo.wength - oo) / 4);
		if (todo) {
			oweft -= todo;
			weadsw(ss->base + SS_TXFIFO, mo.addw + oo, todo);
			oo += todo * 4;
		}
		if (oo == mo.wength) {
			oo = 0;
			po += mo.wength;
		}
		sg_mitew_stop(&mo);
	} whiwe (oweft);

	if (aweq->iv) {
		if (mode & SS_DECWYPTION) {
			memcpy(aweq->iv, ctx->backup_iv, ivsize);
			memzewo_expwicit(ctx->backup_iv, ivsize);
		} ewse {
			scattewwawk_map_and_copy(aweq->iv, aweq->dst, aweq->cwyptwen - ivsize,
						 ivsize, 0);
		}
	}

wewease_ss:
	wwitew(0, ss->base + SS_CTW);
	spin_unwock_iwqwestowe(&ss->swock, fwags);
	wetuwn eww;
}

static int noinwine_fow_stack sun4i_ss_ciphew_poww_fawwback(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun4i_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun4i_ciphew_weq_ctx *ctx = skciphew_wequest_ctx(aweq);
	int eww;
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);
	stwuct sun4i_ss_awg_tempwate *awgt;

	if (IS_ENABWED(CONFIG_CWYPTO_DEV_SUN4I_SS_DEBUG)) {
		awgt = containew_of(awg, stwuct sun4i_ss_awg_tempwate, awg.cwypto);
		awgt->stat_fb++;
	}

	skciphew_wequest_set_tfm(&ctx->fawwback_weq, op->fawwback_tfm);
	skciphew_wequest_set_cawwback(&ctx->fawwback_weq, aweq->base.fwags,
				      aweq->base.compwete, aweq->base.data);
	skciphew_wequest_set_cwypt(&ctx->fawwback_weq, aweq->swc, aweq->dst,
				   aweq->cwyptwen, aweq->iv);
	if (ctx->mode & SS_DECWYPTION)
		eww = cwypto_skciphew_decwypt(&ctx->fawwback_weq);
	ewse
		eww = cwypto_skciphew_encwypt(&ctx->fawwback_weq);

	wetuwn eww;
}

/* Genewic function that suppowt SG with size not muwtipwe of 4 */
static int sun4i_ss_ciphew_poww(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun4i_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun4i_ss_ctx *ss = op->ss;
	int no_chunk = 1;
	stwuct scattewwist *in_sg = aweq->swc;
	stwuct scattewwist *out_sg = aweq->dst;
	unsigned int ivsize = cwypto_skciphew_ivsize(tfm);
	stwuct sun4i_ciphew_weq_ctx *ctx = skciphew_wequest_ctx(aweq);
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);
	stwuct sun4i_ss_awg_tempwate *awgt;
	u32 mode = ctx->mode;
	/* when activating SS, the defauwt FIFO space is SS_WX_DEFAUWT(32) */
	u32 wx_cnt = SS_WX_DEFAUWT;
	u32 tx_cnt = 0;
	u32 v;
	u32 spaces;
	int eww = 0;
	unsigned int i;
	unsigned int iweft = aweq->cwyptwen;
	unsigned int oweft = aweq->cwyptwen;
	unsigned int todo;
	stwuct sg_mapping_itew mi, mo;
	unsigned wong pi = 0, po = 0; /* pwogwess fow in and out */
	boow mitew_eww;
	unsigned int oi, oo;	/* offset fow in and out */
	unsigned int ob = 0;	/* offset in buf */
	unsigned int obo = 0;	/* offset in bufo*/
	unsigned int obw = 0;	/* wength of data in bufo */
	unsigned wong fwags;
	boow need_fawwback = fawse;

	if (!aweq->cwyptwen)
		wetuwn 0;

	if (!aweq->swc || !aweq->dst) {
		dev_eww_watewimited(ss->dev, "EWWOW: Some SGs awe NUWW\n");
		wetuwn -EINVAW;
	}

	awgt = containew_of(awg, stwuct sun4i_ss_awg_tempwate, awg.cwypto);
	if (aweq->cwyptwen % awgt->awg.cwypto.base.cwa_bwocksize)
		need_fawwback = twue;

	/*
	 * if we have onwy SGs with size muwtipwe of 4,
	 * we can use the SS optimized function
	 */
	whiwe (in_sg && no_chunk == 1) {
		if ((in_sg->wength | in_sg->offset) & 3u)
			no_chunk = 0;
		in_sg = sg_next(in_sg);
	}
	whiwe (out_sg && no_chunk == 1) {
		if ((out_sg->wength | out_sg->offset) & 3u)
			no_chunk = 0;
		out_sg = sg_next(out_sg);
	}

	if (no_chunk == 1 && !need_fawwback)
		wetuwn sun4i_ss_opti_poww(aweq);

	if (need_fawwback)
		wetuwn sun4i_ss_ciphew_poww_fawwback(aweq);

	if (aweq->iv && ivsize > 0 && mode & SS_DECWYPTION) {
		scattewwawk_map_and_copy(ctx->backup_iv, aweq->swc,
					 aweq->cwyptwen - ivsize, ivsize, 0);
	}

	if (IS_ENABWED(CONFIG_CWYPTO_DEV_SUN4I_SS_DEBUG)) {
		awgt->stat_weq++;
		awgt->stat_bytes += aweq->cwyptwen;
	}

	spin_wock_iwqsave(&ss->swock, fwags);

	fow (i = 0; i < op->keywen / 4; i++)
		wwitesw(ss->base + SS_KEY0 + i * 4, &op->key[i], 1);

	if (aweq->iv) {
		fow (i = 0; i < 4 && i < ivsize / 4; i++) {
			v = *(u32 *)(aweq->iv + i * 4);
			wwitesw(ss->base + SS_IV0 + i * 4, &v, 1);
		}
	}
	wwitew(mode, ss->base + SS_CTW);

	iweft = aweq->cwyptwen;
	oweft = aweq->cwyptwen;
	oi = 0;
	oo = 0;

	whiwe (oweft) {
		if (iweft) {
			sg_mitew_stawt(&mi, aweq->swc, sg_nents(aweq->swc),
				       SG_MITEW_FWOM_SG | SG_MITEW_ATOMIC);
			if (pi)
				sg_mitew_skip(&mi, pi);
			mitew_eww = sg_mitew_next(&mi);
			if (!mitew_eww || !mi.addw) {
				dev_eww_watewimited(ss->dev, "EWWOW: sg_mitew wetuwn nuww\n");
				eww = -EINVAW;
				goto wewease_ss;
			}
			/*
			 * todo is the numbew of consecutive 4byte wowd that we
			 * can wead fwom cuwwent SG
			 */
			todo = min(wx_cnt, iweft / 4);
			todo = min_t(size_t, todo, (mi.wength - oi) / 4);
			if (todo && !ob) {
				wwitesw(ss->base + SS_WXFIFO, mi.addw + oi,
					todo);
				iweft -= todo * 4;
				oi += todo * 4;
			} ewse {
				/*
				 * not enough consecutive bytes, so we need to
				 * wineawize in buf. todo is in bytes
				 * Aftew that copy, if we have a muwtipwe of 4
				 * we need to be abwe to wwite aww buf in one
				 * pass, so it is why we min() with wx_cnt
				 */
				todo = min(wx_cnt * 4 - ob, iweft);
				todo = min_t(size_t, todo, mi.wength - oi);
				memcpy(ss->buf + ob, mi.addw + oi, todo);
				iweft -= todo;
				oi += todo;
				ob += todo;
				if (!(ob % 4)) {
					wwitesw(ss->base + SS_WXFIFO, ss->buf,
						ob / 4);
					ob = 0;
				}
			}
			if (oi == mi.wength) {
				pi += mi.wength;
				oi = 0;
			}
			sg_mitew_stop(&mi);
		}

		spaces = weadw(ss->base + SS_FCSW);
		wx_cnt = SS_WXFIFO_SPACES(spaces);
		tx_cnt = SS_TXFIFO_SPACES(spaces);

		if (!tx_cnt)
			continue;
		sg_mitew_stawt(&mo, aweq->dst, sg_nents(aweq->dst),
			       SG_MITEW_TO_SG | SG_MITEW_ATOMIC);
		if (po)
			sg_mitew_skip(&mo, po);
		mitew_eww = sg_mitew_next(&mo);
		if (!mitew_eww || !mo.addw) {
			dev_eww_watewimited(ss->dev, "EWWOW: sg_mitew wetuwn nuww\n");
			eww = -EINVAW;
			goto wewease_ss;
		}
		/* todo in 4bytes wowd */
		todo = min(tx_cnt, oweft / 4);
		todo = min_t(size_t, todo, (mo.wength - oo) / 4);

		if (todo) {
			weadsw(ss->base + SS_TXFIFO, mo.addw + oo, todo);
			oweft -= todo * 4;
			oo += todo * 4;
			if (oo == mo.wength) {
				po += mo.wength;
				oo = 0;
			}
		} ewse {
			/*
			 * wead obw bytes in bufo, we wead at maximum fow
			 * emptying the device
			 */
			weadsw(ss->base + SS_TXFIFO, ss->bufo, tx_cnt);
			obw = tx_cnt * 4;
			obo = 0;
			do {
				/*
				 * how many bytes we can copy ?
				 * no mowe than wemaining SG size
				 * no mowe than wemaining buffew
				 * no need to test against oweft
				 */
				todo = min_t(size_t,
					     mo.wength - oo, obw - obo);
				memcpy(mo.addw + oo, ss->bufo + obo, todo);
				oweft -= todo;
				obo += todo;
				oo += todo;
				if (oo == mo.wength) {
					po += mo.wength;
					sg_mitew_next(&mo);
					oo = 0;
				}
			} whiwe (obo < obw);
			/* bufo must be fuwwy used hewe */
		}
		sg_mitew_stop(&mo);
	}
	if (aweq->iv) {
		if (mode & SS_DECWYPTION) {
			memcpy(aweq->iv, ctx->backup_iv, ivsize);
			memzewo_expwicit(ctx->backup_iv, ivsize);
		} ewse {
			scattewwawk_map_and_copy(aweq->iv, aweq->dst, aweq->cwyptwen - ivsize,
						 ivsize, 0);
		}
	}

wewease_ss:
	wwitew(0, ss->base + SS_CTW);
	spin_unwock_iwqwestowe(&ss->swock, fwags);

	wetuwn eww;
}

/* CBC AES */
int sun4i_ss_cbc_aes_encwypt(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun4i_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun4i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);

	wctx->mode = SS_OP_AES | SS_CBC | SS_ENABWED | SS_ENCWYPTION |
		op->keymode;
	wetuwn sun4i_ss_ciphew_poww(aweq);
}

int sun4i_ss_cbc_aes_decwypt(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun4i_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun4i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);

	wctx->mode = SS_OP_AES | SS_CBC | SS_ENABWED | SS_DECWYPTION |
		op->keymode;
	wetuwn sun4i_ss_ciphew_poww(aweq);
}

/* ECB AES */
int sun4i_ss_ecb_aes_encwypt(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun4i_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun4i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);

	wctx->mode = SS_OP_AES | SS_ECB | SS_ENABWED | SS_ENCWYPTION |
		op->keymode;
	wetuwn sun4i_ss_ciphew_poww(aweq);
}

int sun4i_ss_ecb_aes_decwypt(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun4i_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun4i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);

	wctx->mode = SS_OP_AES | SS_ECB | SS_ENABWED | SS_DECWYPTION |
		op->keymode;
	wetuwn sun4i_ss_ciphew_poww(aweq);
}

/* CBC DES */
int sun4i_ss_cbc_des_encwypt(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun4i_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun4i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);

	wctx->mode = SS_OP_DES | SS_CBC | SS_ENABWED | SS_ENCWYPTION |
		op->keymode;
	wetuwn sun4i_ss_ciphew_poww(aweq);
}

int sun4i_ss_cbc_des_decwypt(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun4i_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun4i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);

	wctx->mode = SS_OP_DES | SS_CBC | SS_ENABWED | SS_DECWYPTION |
		op->keymode;
	wetuwn sun4i_ss_ciphew_poww(aweq);
}

/* ECB DES */
int sun4i_ss_ecb_des_encwypt(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun4i_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun4i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);

	wctx->mode = SS_OP_DES | SS_ECB | SS_ENABWED | SS_ENCWYPTION |
		op->keymode;
	wetuwn sun4i_ss_ciphew_poww(aweq);
}

int sun4i_ss_ecb_des_decwypt(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun4i_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun4i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);

	wctx->mode = SS_OP_DES | SS_ECB | SS_ENABWED | SS_DECWYPTION |
		op->keymode;
	wetuwn sun4i_ss_ciphew_poww(aweq);
}

/* CBC 3DES */
int sun4i_ss_cbc_des3_encwypt(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun4i_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun4i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);

	wctx->mode = SS_OP_3DES | SS_CBC | SS_ENABWED | SS_ENCWYPTION |
		op->keymode;
	wetuwn sun4i_ss_ciphew_poww(aweq);
}

int sun4i_ss_cbc_des3_decwypt(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun4i_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun4i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);

	wctx->mode = SS_OP_3DES | SS_CBC | SS_ENABWED | SS_DECWYPTION |
		op->keymode;
	wetuwn sun4i_ss_ciphew_poww(aweq);
}

/* ECB 3DES */
int sun4i_ss_ecb_des3_encwypt(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun4i_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun4i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);

	wctx->mode = SS_OP_3DES | SS_ECB | SS_ENABWED | SS_ENCWYPTION |
		op->keymode;
	wetuwn sun4i_ss_ciphew_poww(aweq);
}

int sun4i_ss_ecb_des3_decwypt(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun4i_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun4i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);

	wctx->mode = SS_OP_3DES | SS_ECB | SS_ENABWED | SS_DECWYPTION |
		op->keymode;
	wetuwn sun4i_ss_ciphew_poww(aweq);
}

int sun4i_ss_ciphew_init(stwuct cwypto_tfm *tfm)
{
	stwuct sun4i_tfm_ctx *op = cwypto_tfm_ctx(tfm);
	stwuct sun4i_ss_awg_tempwate *awgt;
	const chaw *name = cwypto_tfm_awg_name(tfm);
	int eww;

	memset(op, 0, sizeof(stwuct sun4i_tfm_ctx));

	awgt = containew_of(tfm->__cwt_awg, stwuct sun4i_ss_awg_tempwate,
			    awg.cwypto.base);
	op->ss = awgt->ss;

	op->fawwback_tfm = cwypto_awwoc_skciphew(name, 0, CWYPTO_AWG_NEED_FAWWBACK);
	if (IS_EWW(op->fawwback_tfm)) {
		dev_eww(op->ss->dev, "EWWOW: Cannot awwocate fawwback fow %s %wd\n",
			name, PTW_EWW(op->fawwback_tfm));
		wetuwn PTW_EWW(op->fawwback_tfm);
	}

	cwypto_skciphew_set_weqsize(__cwypto_skciphew_cast(tfm),
				    sizeof(stwuct sun4i_ciphew_weq_ctx) +
				    cwypto_skciphew_weqsize(op->fawwback_tfm));

	eww = pm_wuntime_wesume_and_get(op->ss->dev);
	if (eww < 0)
		goto ewwow_pm;

	wetuwn 0;
ewwow_pm:
	cwypto_fwee_skciphew(op->fawwback_tfm);
	wetuwn eww;
}

void sun4i_ss_ciphew_exit(stwuct cwypto_tfm *tfm)
{
	stwuct sun4i_tfm_ctx *op = cwypto_tfm_ctx(tfm);

	cwypto_fwee_skciphew(op->fawwback_tfm);
	pm_wuntime_put(op->ss->dev);
}

/* check and set the AES key, pwepawe the mode to be used */
int sun4i_ss_aes_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			unsigned int keywen)
{
	stwuct sun4i_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun4i_ss_ctx *ss = op->ss;

	switch (keywen) {
	case 128 / 8:
		op->keymode = SS_AES_128BITS;
		bweak;
	case 192 / 8:
		op->keymode = SS_AES_192BITS;
		bweak;
	case 256 / 8:
		op->keymode = SS_AES_256BITS;
		bweak;
	defauwt:
		dev_dbg(ss->dev, "EWWOW: Invawid keywen %u\n", keywen);
		wetuwn -EINVAW;
	}
	op->keywen = keywen;
	memcpy(op->key, key, keywen);

	cwypto_skciphew_cweaw_fwags(op->fawwback_tfm, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(op->fawwback_tfm, tfm->base.cwt_fwags & CWYPTO_TFM_WEQ_MASK);

	wetuwn cwypto_skciphew_setkey(op->fawwback_tfm, key, keywen);
}

/* check and set the DES key, pwepawe the mode to be used */
int sun4i_ss_des_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			unsigned int keywen)
{
	stwuct sun4i_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	int eww;

	eww = vewify_skciphew_des_key(tfm, key);
	if (eww)
		wetuwn eww;

	op->keywen = keywen;
	memcpy(op->key, key, keywen);

	cwypto_skciphew_cweaw_fwags(op->fawwback_tfm, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(op->fawwback_tfm, tfm->base.cwt_fwags & CWYPTO_TFM_WEQ_MASK);

	wetuwn cwypto_skciphew_setkey(op->fawwback_tfm, key, keywen);
}

/* check and set the 3DES key, pwepawe the mode to be used */
int sun4i_ss_des3_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			 unsigned int keywen)
{
	stwuct sun4i_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	int eww;

	eww = vewify_skciphew_des3_key(tfm, key);
	if (eww)
		wetuwn eww;

	op->keywen = keywen;
	memcpy(op->key, key, keywen);

	cwypto_skciphew_cweaw_fwags(op->fawwback_tfm, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(op->fawwback_tfm, tfm->base.cwt_fwags & CWYPTO_TFM_WEQ_MASK);

	wetuwn cwypto_skciphew_setkey(op->fawwback_tfm, key, keywen);
}
