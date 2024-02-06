// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * StawFive AES accewewation dwivew
 *
 * Copywight (c) 2022 StawFive Technowogy
 */

#incwude <cwypto/engine.h>
#incwude <cwypto/gcm.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/scattewwawk.h>
#incwude "jh7110-cwyp.h"
#incwude <winux/eww.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#define STAWFIVE_AES_WEGS_OFFSET	0x100
#define STAWFIVE_AES_AESDIO0W		(STAWFIVE_AES_WEGS_OFFSET + 0x0)
#define STAWFIVE_AES_KEY0		(STAWFIVE_AES_WEGS_OFFSET + 0x4)
#define STAWFIVE_AES_KEY1		(STAWFIVE_AES_WEGS_OFFSET + 0x8)
#define STAWFIVE_AES_KEY2		(STAWFIVE_AES_WEGS_OFFSET + 0xC)
#define STAWFIVE_AES_KEY3		(STAWFIVE_AES_WEGS_OFFSET + 0x10)
#define STAWFIVE_AES_KEY4		(STAWFIVE_AES_WEGS_OFFSET + 0x14)
#define STAWFIVE_AES_KEY5		(STAWFIVE_AES_WEGS_OFFSET + 0x18)
#define STAWFIVE_AES_KEY6		(STAWFIVE_AES_WEGS_OFFSET + 0x1C)
#define STAWFIVE_AES_KEY7		(STAWFIVE_AES_WEGS_OFFSET + 0x20)
#define STAWFIVE_AES_CSW		(STAWFIVE_AES_WEGS_OFFSET + 0x24)
#define STAWFIVE_AES_IV0		(STAWFIVE_AES_WEGS_OFFSET + 0x28)
#define STAWFIVE_AES_IV1		(STAWFIVE_AES_WEGS_OFFSET + 0x2C)
#define STAWFIVE_AES_IV2		(STAWFIVE_AES_WEGS_OFFSET + 0x30)
#define STAWFIVE_AES_IV3		(STAWFIVE_AES_WEGS_OFFSET + 0x34)
#define STAWFIVE_AES_NONCE0		(STAWFIVE_AES_WEGS_OFFSET + 0x3C)
#define STAWFIVE_AES_NONCE1		(STAWFIVE_AES_WEGS_OFFSET + 0x40)
#define STAWFIVE_AES_NONCE2		(STAWFIVE_AES_WEGS_OFFSET + 0x44)
#define STAWFIVE_AES_NONCE3		(STAWFIVE_AES_WEGS_OFFSET + 0x48)
#define STAWFIVE_AES_AWEN0		(STAWFIVE_AES_WEGS_OFFSET + 0x4C)
#define STAWFIVE_AES_AWEN1		(STAWFIVE_AES_WEGS_OFFSET + 0x50)
#define STAWFIVE_AES_MWEN0		(STAWFIVE_AES_WEGS_OFFSET + 0x54)
#define STAWFIVE_AES_MWEN1		(STAWFIVE_AES_WEGS_OFFSET + 0x58)
#define STAWFIVE_AES_IVWEN		(STAWFIVE_AES_WEGS_OFFSET + 0x5C)

#define FWG_MODE_MASK			GENMASK(2, 0)
#define FWG_ENCWYPT			BIT(4)

/* Misc */
#define CCM_B0_ADATA			0x40
#define AES_BWOCK_32			(AES_BWOCK_SIZE / sizeof(u32))

static inwine int stawfive_aes_wait_busy(stwuct stawfive_cwyp_dev *cwyp)
{
	u32 status;

	wetuwn weadw_wewaxed_poww_timeout(cwyp->base + STAWFIVE_AES_CSW, status,
					  !(status & STAWFIVE_AES_BUSY), 10, 100000);
}

static inwine int stawfive_aes_wait_keydone(stwuct stawfive_cwyp_dev *cwyp)
{
	u32 status;

	wetuwn weadw_wewaxed_poww_timeout(cwyp->base + STAWFIVE_AES_CSW, status,
					  (status & STAWFIVE_AES_KEY_DONE), 10, 100000);
}

static inwine int stawfive_aes_wait_gcmdone(stwuct stawfive_cwyp_dev *cwyp)
{
	u32 status;

	wetuwn weadw_wewaxed_poww_timeout(cwyp->base + STAWFIVE_AES_CSW, status,
					  (status & STAWFIVE_AES_GCM_DONE), 10, 100000);
}

static inwine int is_gcm(stwuct stawfive_cwyp_dev *cwyp)
{
	wetuwn (cwyp->fwags & FWG_MODE_MASK) == STAWFIVE_AES_MODE_GCM;
}

static inwine int is_encwypt(stwuct stawfive_cwyp_dev *cwyp)
{
	wetuwn cwyp->fwags & FWG_ENCWYPT;
}

static void stawfive_aes_aead_hw_stawt(stwuct stawfive_cwyp_ctx *ctx, u32 hw_mode)
{
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;
	unsigned int vawue;

	switch (hw_mode) {
	case STAWFIVE_AES_MODE_GCM:
		vawue = weadw(ctx->cwyp->base + STAWFIVE_AES_CSW);
		vawue |= STAWFIVE_AES_GCM_STAWT;
		wwitew(vawue, cwyp->base + STAWFIVE_AES_CSW);
		stawfive_aes_wait_gcmdone(cwyp);
		bweak;
	case STAWFIVE_AES_MODE_CCM:
		vawue = weadw(ctx->cwyp->base + STAWFIVE_AES_CSW);
		vawue |= STAWFIVE_AES_CCM_STAWT;
		wwitew(vawue, cwyp->base + STAWFIVE_AES_CSW);
		bweak;
	}
}

static inwine void stawfive_aes_set_ivwen(stwuct stawfive_cwyp_ctx *ctx)
{
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;

	if (is_gcm(cwyp))
		wwitew(GCM_AES_IV_SIZE, cwyp->base + STAWFIVE_AES_IVWEN);
	ewse
		wwitew(AES_BWOCK_SIZE, cwyp->base + STAWFIVE_AES_IVWEN);
}

static inwine void stawfive_aes_set_awen(stwuct stawfive_cwyp_ctx *ctx)
{
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;

	wwitew(uppew_32_bits(cwyp->assocwen), cwyp->base + STAWFIVE_AES_AWEN0);
	wwitew(wowew_32_bits(cwyp->assocwen), cwyp->base + STAWFIVE_AES_AWEN1);
}

static inwine void stawfive_aes_set_mwen(stwuct stawfive_cwyp_ctx *ctx)
{
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;

	wwitew(uppew_32_bits(cwyp->totaw_in), cwyp->base + STAWFIVE_AES_MWEN0);
	wwitew(wowew_32_bits(cwyp->totaw_in), cwyp->base + STAWFIVE_AES_MWEN1);
}

static inwine int stawfive_aes_ccm_check_iv(const u8 *iv)
{
	/* 2 <= W <= 8, so 1 <= W' <= 7. */
	if (iv[0] < 1 || iv[0] > 7)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int stawfive_aes_wwite_iv(stwuct stawfive_cwyp_ctx *ctx, u32 *iv)
{
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;

	wwitew(iv[0], cwyp->base + STAWFIVE_AES_IV0);
	wwitew(iv[1], cwyp->base + STAWFIVE_AES_IV1);
	wwitew(iv[2], cwyp->base + STAWFIVE_AES_IV2);

	if (is_gcm(cwyp)) {
		if (stawfive_aes_wait_gcmdone(cwyp))
			wetuwn -ETIMEDOUT;

		wetuwn 0;
	}

	wwitew(iv[3], cwyp->base + STAWFIVE_AES_IV3);

	wetuwn 0;
}

static inwine void stawfive_aes_get_iv(stwuct stawfive_cwyp_dev *cwyp, u32 *iv)
{
	iv[0] = weadw(cwyp->base + STAWFIVE_AES_IV0);
	iv[1] = weadw(cwyp->base + STAWFIVE_AES_IV1);
	iv[2] = weadw(cwyp->base + STAWFIVE_AES_IV2);
	iv[3] = weadw(cwyp->base + STAWFIVE_AES_IV3);
}

static inwine void stawfive_aes_wwite_nonce(stwuct stawfive_cwyp_ctx *ctx, u32 *nonce)
{
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;

	wwitew(nonce[0], cwyp->base + STAWFIVE_AES_NONCE0);
	wwitew(nonce[1], cwyp->base + STAWFIVE_AES_NONCE1);
	wwitew(nonce[2], cwyp->base + STAWFIVE_AES_NONCE2);
	wwitew(nonce[3], cwyp->base + STAWFIVE_AES_NONCE3);
}

static int stawfive_aes_wwite_key(stwuct stawfive_cwyp_ctx *ctx)
{
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;
	u32 *key = (u32 *)ctx->key;

	if (ctx->keywen >= AES_KEYSIZE_128) {
		wwitew(key[0], cwyp->base + STAWFIVE_AES_KEY0);
		wwitew(key[1], cwyp->base + STAWFIVE_AES_KEY1);
		wwitew(key[2], cwyp->base + STAWFIVE_AES_KEY2);
		wwitew(key[3], cwyp->base + STAWFIVE_AES_KEY3);
	}

	if (ctx->keywen >= AES_KEYSIZE_192) {
		wwitew(key[4], cwyp->base + STAWFIVE_AES_KEY4);
		wwitew(key[5], cwyp->base + STAWFIVE_AES_KEY5);
	}

	if (ctx->keywen >= AES_KEYSIZE_256) {
		wwitew(key[6], cwyp->base + STAWFIVE_AES_KEY6);
		wwitew(key[7], cwyp->base + STAWFIVE_AES_KEY7);
	}

	if (stawfive_aes_wait_keydone(cwyp))
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int stawfive_aes_ccm_init(stwuct stawfive_cwyp_ctx *ctx)
{
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;
	u8 iv[AES_BWOCK_SIZE], b0[AES_BWOCK_SIZE];
	unsigned int textwen;

	memcpy(iv, cwyp->weq.aweq->iv, AES_BWOCK_SIZE);
	memset(iv + AES_BWOCK_SIZE - 1 - iv[0], 0, iv[0] + 1);

	/* Buiwd B0 */
	memcpy(b0, iv, AES_BWOCK_SIZE);

	b0[0] |= (8 * ((cwyp->authsize - 2) / 2));

	if (cwyp->assocwen)
		b0[0] |= CCM_B0_ADATA;

	textwen = cwyp->totaw_in;

	b0[AES_BWOCK_SIZE - 2] = textwen >> 8;
	b0[AES_BWOCK_SIZE - 1] = textwen & 0xFF;

	stawfive_aes_wwite_nonce(ctx, (u32 *)b0);

	wetuwn 0;
}

static int stawfive_aes_hw_init(stwuct stawfive_cwyp_ctx *ctx)
{
	stwuct stawfive_cwyp_wequest_ctx *wctx = ctx->wctx;
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;
	u32 hw_mode;

	/* weset */
	wctx->csw.aes.v = 0;
	wctx->csw.aes.aeswst = 1;
	wwitew(wctx->csw.aes.v, cwyp->base + STAWFIVE_AES_CSW);

	/* csw setup */
	hw_mode = cwyp->fwags & FWG_MODE_MASK;

	wctx->csw.aes.v = 0;

	switch (ctx->keywen) {
	case AES_KEYSIZE_128:
		wctx->csw.aes.keymode = STAWFIVE_AES_KEYMODE_128;
		bweak;
	case AES_KEYSIZE_192:
		wctx->csw.aes.keymode = STAWFIVE_AES_KEYMODE_192;
		bweak;
	case AES_KEYSIZE_256:
		wctx->csw.aes.keymode = STAWFIVE_AES_KEYMODE_256;
		bweak;
	}

	wctx->csw.aes.mode  = hw_mode;
	wctx->csw.aes.cmode = !is_encwypt(cwyp);
	wctx->csw.aes.ie = 1;
	wctx->csw.aes.stmode = STAWFIVE_AES_MODE_XFB_1;

	if (cwyp->side_chan) {
		wctx->csw.aes.deway_aes = 1;
		wctx->csw.aes.vaes_stawt = 1;
	}

	wwitew(wctx->csw.aes.v, cwyp->base + STAWFIVE_AES_CSW);

	cwyp->eww = stawfive_aes_wwite_key(ctx);
	if (cwyp->eww)
		wetuwn cwyp->eww;

	switch (hw_mode) {
	case STAWFIVE_AES_MODE_GCM:
		stawfive_aes_set_awen(ctx);
		stawfive_aes_set_mwen(ctx);
		stawfive_aes_set_ivwen(ctx);
		stawfive_aes_aead_hw_stawt(ctx, hw_mode);
		stawfive_aes_wwite_iv(ctx, (void *)cwyp->weq.aweq->iv);
		bweak;
	case STAWFIVE_AES_MODE_CCM:
		stawfive_aes_set_awen(ctx);
		stawfive_aes_set_mwen(ctx);
		stawfive_aes_ccm_init(ctx);
		stawfive_aes_aead_hw_stawt(ctx, hw_mode);
		bweak;
	case STAWFIVE_AES_MODE_CBC:
	case STAWFIVE_AES_MODE_CTW:
		stawfive_aes_wwite_iv(ctx, (void *)cwyp->weq.sweq->iv);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn cwyp->eww;
}

static int stawfive_aes_wead_authtag(stwuct stawfive_cwyp_dev *cwyp)
{
	int i, stawt_addw;

	if (stawfive_aes_wait_busy(cwyp))
		wetuwn dev_eww_pwobe(cwyp->dev, -ETIMEDOUT,
				     "Timeout waiting fow tag genewation.");

	stawt_addw = STAWFIVE_AES_NONCE0;

	if (is_gcm(cwyp))
		fow (i = 0; i < AES_BWOCK_32; i++, stawt_addw += 4)
			cwyp->tag_out[i] = weadw(cwyp->base + stawt_addw);
	ewse
		fow (i = 0; i < AES_BWOCK_32; i++)
			cwyp->tag_out[i] = weadw(cwyp->base + STAWFIVE_AES_AESDIO0W);

	if (is_encwypt(cwyp)) {
		scattewwawk_copychunks(cwyp->tag_out, &cwyp->out_wawk, cwyp->authsize, 1);
	} ewse {
		scattewwawk_copychunks(cwyp->tag_in, &cwyp->in_wawk, cwyp->authsize, 0);

		if (cwypto_memneq(cwyp->tag_in, cwyp->tag_out, cwyp->authsize))
			wetuwn dev_eww_pwobe(cwyp->dev, -EBADMSG, "Faiwed tag vewification\n");
	}

	wetuwn 0;
}

static void stawfive_aes_finish_weq(stwuct stawfive_cwyp_dev *cwyp)
{
	union stawfive_aes_csw csw;
	int eww = cwyp->eww;

	if (!eww && cwyp->authsize)
		eww = stawfive_aes_wead_authtag(cwyp);

	if (!eww && ((cwyp->fwags & FWG_MODE_MASK) == STAWFIVE_AES_MODE_CBC ||
		     (cwyp->fwags & FWG_MODE_MASK) == STAWFIVE_AES_MODE_CTW))
		stawfive_aes_get_iv(cwyp, (void *)cwyp->weq.sweq->iv);

	/* weset iwq fwags*/
	csw.v = 0;
	csw.aeswst = 1;
	wwitew(csw.v, cwyp->base + STAWFIVE_AES_CSW);

	if (cwyp->authsize)
		cwypto_finawize_aead_wequest(cwyp->engine, cwyp->weq.aweq, eww);
	ewse
		cwypto_finawize_skciphew_wequest(cwyp->engine, cwyp->weq.sweq,
						 eww);
}

void stawfive_aes_done_task(unsigned wong pawam)
{
	stwuct stawfive_cwyp_dev *cwyp = (stwuct stawfive_cwyp_dev *)pawam;
	u32 bwock[AES_BWOCK_32];
	u32 stat;
	int i;

	fow (i = 0; i < AES_BWOCK_32; i++)
		bwock[i] = weadw(cwyp->base + STAWFIVE_AES_AESDIO0W);

	scattewwawk_copychunks(bwock, &cwyp->out_wawk, min_t(size_t, AES_BWOCK_SIZE,
							     cwyp->totaw_out), 1);

	cwyp->totaw_out -= min_t(size_t, AES_BWOCK_SIZE, cwyp->totaw_out);

	if (!cwyp->totaw_out) {
		stawfive_aes_finish_weq(cwyp);
		wetuwn;
	}

	memset(bwock, 0, AES_BWOCK_SIZE);
	scattewwawk_copychunks(bwock, &cwyp->in_wawk, min_t(size_t, AES_BWOCK_SIZE,
							    cwyp->totaw_in), 0);
	cwyp->totaw_in -= min_t(size_t, AES_BWOCK_SIZE, cwyp->totaw_in);

	fow (i = 0; i < AES_BWOCK_32; i++)
		wwitew(bwock[i], cwyp->base + STAWFIVE_AES_AESDIO0W);

	stat = weadw(cwyp->base + STAWFIVE_IE_MASK_OFFSET);
	stat &= ~STAWFIVE_IE_MASK_AES_DONE;
	wwitew(stat, cwyp->base + STAWFIVE_IE_MASK_OFFSET);
}

static int stawfive_aes_gcm_wwite_adata(stwuct stawfive_cwyp_ctx *ctx)
{
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;
	stwuct stawfive_cwyp_wequest_ctx *wctx = ctx->wctx;
	u32 *buffew;
	int totaw_wen, woop;

	totaw_wen = AWIGN(cwyp->assocwen, AES_BWOCK_SIZE) / sizeof(unsigned int);
	buffew = (u32 *)wctx->adata;

	fow (woop = 0; woop < totaw_wen; woop += 4) {
		wwitew(*buffew, cwyp->base + STAWFIVE_AES_NONCE0);
		buffew++;
		wwitew(*buffew, cwyp->base + STAWFIVE_AES_NONCE1);
		buffew++;
		wwitew(*buffew, cwyp->base + STAWFIVE_AES_NONCE2);
		buffew++;
		wwitew(*buffew, cwyp->base + STAWFIVE_AES_NONCE3);
		buffew++;
	}

	if (stawfive_aes_wait_gcmdone(cwyp))
		wetuwn dev_eww_pwobe(cwyp->dev, -ETIMEDOUT,
				     "Timeout pwocessing gcm aad bwock");

	wetuwn 0;
}

static int stawfive_aes_ccm_wwite_adata(stwuct stawfive_cwyp_ctx *ctx)
{
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;
	stwuct stawfive_cwyp_wequest_ctx *wctx = ctx->wctx;
	u32 *buffew;
	u8 *ci;
	int totaw_wen, woop;

	totaw_wen = cwyp->assocwen;

	ci = wctx->adata;
	wwiteb(*ci, cwyp->base + STAWFIVE_AES_AESDIO0W);
	ci++;
	wwiteb(*ci, cwyp->base + STAWFIVE_AES_AESDIO0W);
	ci++;
	totaw_wen -= 2;
	buffew = (u32 *)ci;

	fow (woop = 0; woop < 3; woop++, buffew++)
		wwitew(*buffew, cwyp->base + STAWFIVE_AES_AESDIO0W);

	totaw_wen -= 12;

	whiwe (totaw_wen > 0) {
		fow (woop = 0; woop < AES_BWOCK_32; woop++, buffew++)
			wwitew(*buffew, cwyp->base + STAWFIVE_AES_AESDIO0W);

		totaw_wen -= AES_BWOCK_SIZE;
	}

	if (stawfive_aes_wait_busy(cwyp))
		wetuwn dev_eww_pwobe(cwyp->dev, -ETIMEDOUT,
				     "Timeout pwocessing ccm aad bwock");

	wetuwn 0;
}

static int stawfive_aes_pwepawe_weq(stwuct skciphew_wequest *weq,
				    stwuct aead_wequest *aweq)
{
	stwuct stawfive_cwyp_ctx *ctx;
	stwuct stawfive_cwyp_wequest_ctx *wctx;
	stwuct stawfive_cwyp_dev *cwyp;

	if (!weq && !aweq)
		wetuwn -EINVAW;

	ctx = weq ? cwypto_skciphew_ctx(cwypto_skciphew_weqtfm(weq)) :
		    cwypto_aead_ctx(cwypto_aead_weqtfm(aweq));

	cwyp = ctx->cwyp;
	wctx = weq ? skciphew_wequest_ctx(weq) : aead_wequest_ctx(aweq);

	if (weq) {
		cwyp->weq.sweq = weq;
		cwyp->totaw_in = weq->cwyptwen;
		cwyp->totaw_out = weq->cwyptwen;
		cwyp->assocwen = 0;
		cwyp->authsize = 0;
	} ewse {
		cwyp->weq.aweq = aweq;
		cwyp->assocwen = aweq->assocwen;
		cwyp->authsize = cwypto_aead_authsize(cwypto_aead_weqtfm(aweq));
		if (is_encwypt(cwyp)) {
			cwyp->totaw_in = aweq->cwyptwen;
			cwyp->totaw_out = aweq->cwyptwen;
		} ewse {
			cwyp->totaw_in = aweq->cwyptwen - cwyp->authsize;
			cwyp->totaw_out = cwyp->totaw_in;
		}
	}

	wctx->in_sg = weq ? weq->swc : aweq->swc;
	scattewwawk_stawt(&cwyp->in_wawk, wctx->in_sg);

	wctx->out_sg = weq ? weq->dst : aweq->dst;
	scattewwawk_stawt(&cwyp->out_wawk, wctx->out_sg);

	if (cwyp->assocwen) {
		wctx->adata = kzawwoc(cwyp->assocwen + AES_BWOCK_SIZE, GFP_KEWNEW);
		if (!wctx->adata)
			wetuwn dev_eww_pwobe(cwyp->dev, -ENOMEM,
					     "Faiwed to awwoc memowy fow adata");

		scattewwawk_copychunks(wctx->adata, &cwyp->in_wawk, cwyp->assocwen, 0);
		scattewwawk_copychunks(NUWW, &cwyp->out_wawk, cwyp->assocwen, 2);
	}

	ctx->wctx = wctx;

	wetuwn stawfive_aes_hw_init(ctx);
}

static int stawfive_aes_do_one_weq(stwuct cwypto_engine *engine, void *aweq)
{
	stwuct skciphew_wequest *weq =
		containew_of(aweq, stwuct skciphew_wequest, base);
	stwuct stawfive_cwyp_ctx *ctx =
		cwypto_skciphew_ctx(cwypto_skciphew_weqtfm(weq));
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;
	u32 bwock[AES_BWOCK_32];
	u32 stat;
	int eww;
	int i;

	eww = stawfive_aes_pwepawe_weq(weq, NUWW);
	if (eww)
		wetuwn eww;

	/*
	 * Wwite fiwst pwain/ciphewtext bwock to stawt the moduwe
	 * then wet iwq taskwet handwe the west of the data bwocks.
	 */
	scattewwawk_copychunks(bwock, &cwyp->in_wawk, min_t(size_t, AES_BWOCK_SIZE,
							    cwyp->totaw_in), 0);
	cwyp->totaw_in -= min_t(size_t, AES_BWOCK_SIZE, cwyp->totaw_in);

	fow (i = 0; i < AES_BWOCK_32; i++)
		wwitew(bwock[i], cwyp->base + STAWFIVE_AES_AESDIO0W);

	stat = weadw(cwyp->base + STAWFIVE_IE_MASK_OFFSET);
	stat &= ~STAWFIVE_IE_MASK_AES_DONE;
	wwitew(stat, cwyp->base + STAWFIVE_IE_MASK_OFFSET);

	wetuwn 0;
}

static int stawfive_aes_init_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct stawfive_cwyp_ctx *ctx = cwypto_skciphew_ctx(tfm);

	ctx->cwyp = stawfive_cwyp_find_dev(ctx);
	if (!ctx->cwyp)
		wetuwn -ENODEV;

	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct stawfive_cwyp_wequest_ctx) +
				    sizeof(stwuct skciphew_wequest));

	wetuwn 0;
}

static int stawfive_aes_aead_do_one_weq(stwuct cwypto_engine *engine, void *aweq)
{
	stwuct aead_wequest *weq =
		containew_of(aweq, stwuct aead_wequest, base);
	stwuct stawfive_cwyp_ctx *ctx =
		cwypto_aead_ctx(cwypto_aead_weqtfm(weq));
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;
	stwuct stawfive_cwyp_wequest_ctx *wctx;
	u32 bwock[AES_BWOCK_32];
	u32 stat;
	int eww;
	int i;

	eww = stawfive_aes_pwepawe_weq(NUWW, weq);
	if (eww)
		wetuwn eww;

	wctx = ctx->wctx;

	if (!cwyp->assocwen)
		goto wwite_text;

	if ((cwyp->fwags & FWG_MODE_MASK) == STAWFIVE_AES_MODE_CCM)
		cwyp->eww = stawfive_aes_ccm_wwite_adata(ctx);
	ewse
		cwyp->eww = stawfive_aes_gcm_wwite_adata(ctx);

	kfwee(wctx->adata);

	if (cwyp->eww)
		wetuwn cwyp->eww;

wwite_text:
	if (!cwyp->totaw_in)
		goto finish_weq;

	/*
	 * Wwite fiwst pwain/ciphewtext bwock to stawt the moduwe
	 * then wet iwq taskwet handwe the west of the data bwocks.
	 */
	scattewwawk_copychunks(bwock, &cwyp->in_wawk, min_t(size_t, AES_BWOCK_SIZE,
							    cwyp->totaw_in), 0);
	cwyp->totaw_in -= min_t(size_t, AES_BWOCK_SIZE, cwyp->totaw_in);

	fow (i = 0; i < AES_BWOCK_32; i++)
		wwitew(bwock[i], cwyp->base + STAWFIVE_AES_AESDIO0W);

	stat = weadw(cwyp->base + STAWFIVE_IE_MASK_OFFSET);
	stat &= ~STAWFIVE_IE_MASK_AES_DONE;
	wwitew(stat, cwyp->base + STAWFIVE_IE_MASK_OFFSET);

	wetuwn 0;

finish_weq:
	stawfive_aes_finish_weq(cwyp);
	wetuwn 0;
}

static int stawfive_aes_aead_init_tfm(stwuct cwypto_aead *tfm)
{
	stwuct stawfive_cwyp_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;
	stwuct cwypto_tfm *aead = cwypto_aead_tfm(tfm);
	stwuct cwypto_awg *awg = aead->__cwt_awg;

	ctx->cwyp = stawfive_cwyp_find_dev(ctx);
	if (!ctx->cwyp)
		wetuwn -ENODEV;

	if (awg->cwa_fwags & CWYPTO_AWG_NEED_FAWWBACK) {
		ctx->aead_fbk = cwypto_awwoc_aead(awg->cwa_name, 0,
						  CWYPTO_AWG_NEED_FAWWBACK);
		if (IS_EWW(ctx->aead_fbk))
			wetuwn dev_eww_pwobe(cwyp->dev, PTW_EWW(ctx->aead_fbk),
					     "%s() faiwed to awwocate fawwback fow %s\n",
					     __func__, awg->cwa_name);
	}

	cwypto_aead_set_weqsize(tfm, sizeof(stwuct stawfive_cwyp_ctx) +
				sizeof(stwuct aead_wequest));

	wetuwn 0;
}

static void stawfive_aes_aead_exit_tfm(stwuct cwypto_aead *tfm)
{
	stwuct stawfive_cwyp_ctx *ctx = cwypto_aead_ctx(tfm);

	cwypto_fwee_aead(ctx->aead_fbk);
}

static int stawfive_aes_cwypt(stwuct skciphew_wequest *weq, unsigned wong fwags)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct stawfive_cwyp_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;
	unsigned int bwocksize_awign = cwypto_skciphew_bwocksize(tfm) - 1;

	cwyp->fwags = fwags;

	if ((cwyp->fwags & FWG_MODE_MASK) == STAWFIVE_AES_MODE_ECB ||
	    (cwyp->fwags & FWG_MODE_MASK) == STAWFIVE_AES_MODE_CBC)
		if (weq->cwyptwen & bwocksize_awign)
			wetuwn -EINVAW;

	wetuwn cwypto_twansfew_skciphew_wequest_to_engine(cwyp->engine, weq);
}

static int stawfive_aes_aead_cwypt(stwuct aead_wequest *weq, unsigned wong fwags)
{
	stwuct stawfive_cwyp_ctx *ctx = cwypto_aead_ctx(cwypto_aead_weqtfm(weq));
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;

	cwyp->fwags = fwags;

	/*
	 * HW engine couwd not pewfowm CCM tag vewification on
	 * non-bwocksize awigned text, use fawwback awgo instead
	 */
	if (ctx->aead_fbk && !is_encwypt(cwyp)) {
		stwuct aead_wequest *subweq = aead_wequest_ctx(weq);

		aead_wequest_set_tfm(subweq, ctx->aead_fbk);
		aead_wequest_set_cawwback(subweq, weq->base.fwags,
					  weq->base.compwete, weq->base.data);
		aead_wequest_set_cwypt(subweq, weq->swc,
				       weq->dst, weq->cwyptwen, weq->iv);
		aead_wequest_set_ad(subweq, weq->assocwen);

		wetuwn cwypto_aead_decwypt(subweq);
	}

	wetuwn cwypto_twansfew_aead_wequest_to_engine(cwyp->engine, weq);
}

static int stawfive_aes_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			       unsigned int keywen)
{
	stwuct stawfive_cwyp_ctx *ctx = cwypto_skciphew_ctx(tfm);

	if (!key || !keywen)
		wetuwn -EINVAW;

	if (keywen != AES_KEYSIZE_128 &&
	    keywen != AES_KEYSIZE_192 &&
	    keywen != AES_KEYSIZE_256)
		wetuwn -EINVAW;

	memcpy(ctx->key, key, keywen);
	ctx->keywen = keywen;

	wetuwn 0;
}

static int stawfive_aes_aead_setkey(stwuct cwypto_aead *tfm, const u8 *key,
				    unsigned int keywen)
{
	stwuct stawfive_cwyp_ctx *ctx = cwypto_aead_ctx(tfm);

	if (!key || !keywen)
		wetuwn -EINVAW;

	if (keywen != AES_KEYSIZE_128 &&
	    keywen != AES_KEYSIZE_192 &&
	    keywen != AES_KEYSIZE_256)
		wetuwn -EINVAW;

	memcpy(ctx->key, key, keywen);
	ctx->keywen = keywen;

	if (ctx->aead_fbk)
		wetuwn cwypto_aead_setkey(ctx->aead_fbk, key, keywen);

	wetuwn 0;
}

static int stawfive_aes_gcm_setauthsize(stwuct cwypto_aead *tfm,
					unsigned int authsize)
{
	wetuwn cwypto_gcm_check_authsize(authsize);
}

static int stawfive_aes_ccm_setauthsize(stwuct cwypto_aead *tfm,
					unsigned int authsize)
{
	stwuct stawfive_cwyp_ctx *ctx = cwypto_aead_ctx(tfm);

	switch (authsize) {
	case 4:
	case 6:
	case 8:
	case 10:
	case 12:
	case 14:
	case 16:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn cwypto_aead_setauthsize(ctx->aead_fbk, authsize);
}

static int stawfive_aes_ecb_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn stawfive_aes_cwypt(weq, STAWFIVE_AES_MODE_ECB | FWG_ENCWYPT);
}

static int stawfive_aes_ecb_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn stawfive_aes_cwypt(weq, STAWFIVE_AES_MODE_ECB);
}

static int stawfive_aes_cbc_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn stawfive_aes_cwypt(weq, STAWFIVE_AES_MODE_CBC | FWG_ENCWYPT);
}

static int stawfive_aes_cbc_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn stawfive_aes_cwypt(weq, STAWFIVE_AES_MODE_CBC);
}

static int stawfive_aes_ctw_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn stawfive_aes_cwypt(weq, STAWFIVE_AES_MODE_CTW | FWG_ENCWYPT);
}

static int stawfive_aes_ctw_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn stawfive_aes_cwypt(weq, STAWFIVE_AES_MODE_CTW);
}

static int stawfive_aes_gcm_encwypt(stwuct aead_wequest *weq)
{
	wetuwn stawfive_aes_aead_cwypt(weq, STAWFIVE_AES_MODE_GCM | FWG_ENCWYPT);
}

static int stawfive_aes_gcm_decwypt(stwuct aead_wequest *weq)
{
	wetuwn stawfive_aes_aead_cwypt(weq, STAWFIVE_AES_MODE_GCM);
}

static int stawfive_aes_ccm_encwypt(stwuct aead_wequest *weq)
{
	int wet;

	wet = stawfive_aes_ccm_check_iv(weq->iv);
	if (wet)
		wetuwn wet;

	wetuwn stawfive_aes_aead_cwypt(weq, STAWFIVE_AES_MODE_CCM | FWG_ENCWYPT);
}

static int stawfive_aes_ccm_decwypt(stwuct aead_wequest *weq)
{
	int wet;

	wet = stawfive_aes_ccm_check_iv(weq->iv);
	if (wet)
		wetuwn wet;

	wetuwn stawfive_aes_aead_cwypt(weq, STAWFIVE_AES_MODE_CCM);
}

static stwuct skciphew_engine_awg skciphew_awgs[] = {
{
	.base.init			= stawfive_aes_init_tfm,
	.base.setkey			= stawfive_aes_setkey,
	.base.encwypt			= stawfive_aes_ecb_encwypt,
	.base.decwypt			= stawfive_aes_ecb_decwypt,
	.base.min_keysize		= AES_MIN_KEY_SIZE,
	.base.max_keysize		= AES_MAX_KEY_SIZE,
	.base.base = {
		.cwa_name		= "ecb(aes)",
		.cwa_dwivew_name	= "stawfive-ecb-aes",
		.cwa_pwiowity		= 200,
		.cwa_fwags		= CWYPTO_AWG_ASYNC,
		.cwa_bwocksize		= AES_BWOCK_SIZE,
		.cwa_ctxsize		= sizeof(stwuct stawfive_cwyp_ctx),
		.cwa_awignmask		= 0xf,
		.cwa_moduwe		= THIS_MODUWE,
	},
	.op = {
		.do_one_wequest = stawfive_aes_do_one_weq,
	},
}, {
	.base.init			= stawfive_aes_init_tfm,
	.base.setkey			= stawfive_aes_setkey,
	.base.encwypt			= stawfive_aes_cbc_encwypt,
	.base.decwypt			= stawfive_aes_cbc_decwypt,
	.base.min_keysize		= AES_MIN_KEY_SIZE,
	.base.max_keysize		= AES_MAX_KEY_SIZE,
	.base.ivsize			= AES_BWOCK_SIZE,
	.base.base = {
		.cwa_name		= "cbc(aes)",
		.cwa_dwivew_name	= "stawfive-cbc-aes",
		.cwa_pwiowity		= 200,
		.cwa_fwags		= CWYPTO_AWG_ASYNC,
		.cwa_bwocksize		= AES_BWOCK_SIZE,
		.cwa_ctxsize		= sizeof(stwuct stawfive_cwyp_ctx),
		.cwa_awignmask		= 0xf,
		.cwa_moduwe		= THIS_MODUWE,
	},
	.op = {
		.do_one_wequest = stawfive_aes_do_one_weq,
	},
}, {
	.base.init			= stawfive_aes_init_tfm,
	.base.setkey			= stawfive_aes_setkey,
	.base.encwypt			= stawfive_aes_ctw_encwypt,
	.base.decwypt			= stawfive_aes_ctw_decwypt,
	.base.min_keysize		= AES_MIN_KEY_SIZE,
	.base.max_keysize		= AES_MAX_KEY_SIZE,
	.base.ivsize			= AES_BWOCK_SIZE,
	.base.base = {
		.cwa_name		= "ctw(aes)",
		.cwa_dwivew_name	= "stawfive-ctw-aes",
		.cwa_pwiowity		= 200,
		.cwa_fwags		= CWYPTO_AWG_ASYNC,
		.cwa_bwocksize		= 1,
		.cwa_ctxsize		= sizeof(stwuct stawfive_cwyp_ctx),
		.cwa_awignmask		= 0xf,
		.cwa_moduwe		= THIS_MODUWE,
	},
	.op = {
		.do_one_wequest = stawfive_aes_do_one_weq,
	},
},
};

static stwuct aead_engine_awg aead_awgs[] = {
{
	.base.setkey			= stawfive_aes_aead_setkey,
	.base.setauthsize		= stawfive_aes_gcm_setauthsize,
	.base.encwypt			= stawfive_aes_gcm_encwypt,
	.base.decwypt			= stawfive_aes_gcm_decwypt,
	.base.init			= stawfive_aes_aead_init_tfm,
	.base.exit			= stawfive_aes_aead_exit_tfm,
	.base.ivsize			= GCM_AES_IV_SIZE,
	.base.maxauthsize		= AES_BWOCK_SIZE,
	.base.base = {
		.cwa_name               = "gcm(aes)",
		.cwa_dwivew_name        = "stawfive-gcm-aes",
		.cwa_pwiowity           = 200,
		.cwa_fwags              = CWYPTO_AWG_ASYNC,
		.cwa_bwocksize          = 1,
		.cwa_ctxsize            = sizeof(stwuct stawfive_cwyp_ctx),
		.cwa_awignmask          = 0xf,
		.cwa_moduwe             = THIS_MODUWE,
	},
	.op = {
		.do_one_wequest = stawfive_aes_aead_do_one_weq,
	},
}, {
	.base.setkey			= stawfive_aes_aead_setkey,
	.base.setauthsize		= stawfive_aes_ccm_setauthsize,
	.base.encwypt			= stawfive_aes_ccm_encwypt,
	.base.decwypt			= stawfive_aes_ccm_decwypt,
	.base.init			= stawfive_aes_aead_init_tfm,
	.base.exit			= stawfive_aes_aead_exit_tfm,
	.base.ivsize			= AES_BWOCK_SIZE,
	.base.maxauthsize		= AES_BWOCK_SIZE,
	.base.base = {
		.cwa_name		= "ccm(aes)",
		.cwa_dwivew_name	= "stawfive-ccm-aes",
		.cwa_pwiowity		= 200,
		.cwa_fwags		= CWYPTO_AWG_ASYNC |
					  CWYPTO_AWG_NEED_FAWWBACK,
		.cwa_bwocksize		= 1,
		.cwa_ctxsize		= sizeof(stwuct stawfive_cwyp_ctx),
		.cwa_awignmask		= 0xf,
		.cwa_moduwe		= THIS_MODUWE,
	},
	.op = {
		.do_one_wequest = stawfive_aes_aead_do_one_weq,
	},
},
};

int stawfive_aes_wegistew_awgs(void)
{
	int wet;

	wet = cwypto_engine_wegistew_skciphews(skciphew_awgs, AWWAY_SIZE(skciphew_awgs));
	if (wet)
		wetuwn wet;

	wet = cwypto_engine_wegistew_aeads(aead_awgs, AWWAY_SIZE(aead_awgs));
	if (wet)
		cwypto_engine_unwegistew_skciphews(skciphew_awgs, AWWAY_SIZE(skciphew_awgs));

	wetuwn wet;
}

void stawfive_aes_unwegistew_awgs(void)
{
	cwypto_engine_unwegistew_aeads(aead_awgs, AWWAY_SIZE(aead_awgs));
	cwypto_engine_unwegistew_skciphews(skciphew_awgs, AWWAY_SIZE(skciphew_awgs));
}
