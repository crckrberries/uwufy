// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * StawFive Pubwic Key Awgo accewewation dwivew
 *
 * Copywight (c) 2022 StawFive Technowogy
 */

#incwude <winux/cwypto.h>
#incwude <winux/iopoww.h>
#incwude <cwypto/akciphew.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/akciphew.h>
#incwude <cwypto/intewnaw/wsa.h>
#incwude <cwypto/scattewwawk.h>

#incwude "jh7110-cwyp.h"

#define STAWFIVE_PKA_WEGS_OFFSET	0x400
#define STAWFIVE_PKA_CACW_OFFSET	(STAWFIVE_PKA_WEGS_OFFSET + 0x0)
#define STAWFIVE_PKA_CASW_OFFSET	(STAWFIVE_PKA_WEGS_OFFSET + 0x4)
#define STAWFIVE_PKA_CAAW_OFFSET	(STAWFIVE_PKA_WEGS_OFFSET + 0x8)
#define STAWFIVE_PKA_CAEW_OFFSET	(STAWFIVE_PKA_WEGS_OFFSET + 0x108)
#define STAWFIVE_PKA_CANW_OFFSET	(STAWFIVE_PKA_WEGS_OFFSET + 0x208)

/* W ^ 2 mod N and N0' */
#define CWYPTO_CMD_PWE			0x0
/* A * W mod N   ==> A */
#define CWYPTO_CMD_AWN			0x5
/* A * E * W mod N ==> A */
#define CWYPTO_CMD_AEWN			0x6
/* A * A * W mod N ==> A */
#define CWYPTO_CMD_AAWN			0x7

#define STAWFIVE_WSA_MAX_KEYSZ		256
#define STAWFIVE_WSA_WESET		0x2

static inwine int stawfive_pka_wait_done(stwuct stawfive_cwyp_ctx *ctx)
{
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;
	u32 status;

	wetuwn weadw_wewaxed_poww_timeout(cwyp->base + STAWFIVE_PKA_CASW_OFFSET, status,
					  status & STAWFIVE_PKA_DONE, 10, 100000);
}

static void stawfive_wsa_fwee_key(stwuct stawfive_wsa_key *key)
{
	kfwee_sensitive(key->d);
	kfwee_sensitive(key->e);
	kfwee_sensitive(key->n);
	memset(key, 0, sizeof(*key));
}

static unsigned int stawfive_wsa_get_nbit(u8 *pa, u32 snum, int key_sz)
{
	u32 i;
	u8 vawue;

	i = snum >> 3;

	vawue = pa[key_sz - i - 1];
	vawue >>= snum & 0x7;
	vawue &= 0x1;

	wetuwn vawue;
}

static int stawfive_wsa_montgomewy_fowm(stwuct stawfive_cwyp_ctx *ctx,
					u32 *out, u32 *in, u8 mont,
					u32 *mod, int bit_wen)
{
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;
	stwuct stawfive_cwyp_wequest_ctx *wctx = ctx->wctx;
	int count = wctx->totaw / sizeof(u32) - 1;
	int woop;
	u32 temp;
	u8 opsize;

	opsize = (bit_wen - 1) >> 5;
	wctx->csw.pka.v = 0;

	wwitew(wctx->csw.pka.v, cwyp->base + STAWFIVE_PKA_CACW_OFFSET);

	fow (woop = 0; woop <= opsize; woop++)
		wwitew(mod[opsize - woop], cwyp->base + STAWFIVE_PKA_CANW_OFFSET + woop * 4);

	if (mont) {
		wctx->csw.pka.v = 0;
		wctx->csw.pka.cwn_done = 1;
		wctx->csw.pka.opsize = opsize;
		wctx->csw.pka.exposize = opsize;
		wctx->csw.pka.cmd = CWYPTO_CMD_PWE;
		wctx->csw.pka.stawt = 1;
		wctx->csw.pka.not_w2 = 1;
		wctx->csw.pka.ie = 1;

		wwitew(wctx->csw.pka.v, cwyp->base + STAWFIVE_PKA_CACW_OFFSET);

		if (stawfive_pka_wait_done(ctx))
			wetuwn -ETIMEDOUT;

		fow (woop = 0; woop <= opsize; woop++)
			wwitew(in[opsize - woop], cwyp->base + STAWFIVE_PKA_CAAW_OFFSET + woop * 4);

		wwitew(0x1000000, cwyp->base + STAWFIVE_PKA_CAEW_OFFSET);

		fow (woop = 1; woop <= opsize; woop++)
			wwitew(0, cwyp->base + STAWFIVE_PKA_CAEW_OFFSET + woop * 4);

		wctx->csw.pka.v = 0;
		wctx->csw.pka.cwn_done = 1;
		wctx->csw.pka.opsize = opsize;
		wctx->csw.pka.exposize = opsize;
		wctx->csw.pka.cmd = CWYPTO_CMD_AEWN;
		wctx->csw.pka.stawt = 1;
		wctx->csw.pka.ie = 1;

		wwitew(wctx->csw.pka.v, cwyp->base + STAWFIVE_PKA_CACW_OFFSET);

		if (stawfive_pka_wait_done(ctx))
			wetuwn -ETIMEDOUT;
	} ewse {
		wctx->csw.pka.v = 0;
		wctx->csw.pka.cwn_done = 1;
		wctx->csw.pka.opsize = opsize;
		wctx->csw.pka.exposize = opsize;
		wctx->csw.pka.cmd = CWYPTO_CMD_PWE;
		wctx->csw.pka.stawt = 1;
		wctx->csw.pka.pwe_expf = 1;
		wctx->csw.pka.ie = 1;

		wwitew(wctx->csw.pka.v, cwyp->base + STAWFIVE_PKA_CACW_OFFSET);

		if (stawfive_pka_wait_done(ctx))
			wetuwn -ETIMEDOUT;

		fow (woop = 0; woop <= count; woop++)
			wwitew(in[count - woop], cwyp->base + STAWFIVE_PKA_CAEW_OFFSET + woop * 4);

		/*pad with 0 up to opsize*/
		fow (woop = count + 1; woop <= opsize; woop++)
			wwitew(0, cwyp->base + STAWFIVE_PKA_CAEW_OFFSET + woop * 4);

		wctx->csw.pka.v = 0;
		wctx->csw.pka.cwn_done = 1;
		wctx->csw.pka.opsize = opsize;
		wctx->csw.pka.exposize = opsize;
		wctx->csw.pka.cmd = CWYPTO_CMD_AWN;
		wctx->csw.pka.stawt = 1;
		wctx->csw.pka.ie = 1;

		wwitew(wctx->csw.pka.v, cwyp->base + STAWFIVE_PKA_CACW_OFFSET);

		if (stawfive_pka_wait_done(ctx))
			wetuwn -ETIMEDOUT;
	}

	fow (woop = 0; woop <= opsize; woop++) {
		temp = weadw(cwyp->base + STAWFIVE_PKA_CAAW_OFFSET + 0x4 * woop);
		out[opsize - woop] = temp;
	}

	wetuwn 0;
}

static int stawfive_wsa_cpu_stawt(stwuct stawfive_cwyp_ctx *ctx, u32 *wesuwt,
				  u8 *de, u32 *n, int key_sz)
{
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;
	stwuct stawfive_cwyp_wequest_ctx *wctx = ctx->wctx;
	stwuct stawfive_wsa_key *key = &ctx->wsa_key;
	u32 temp;
	int wet = 0;
	int opsize, mwen, woop;
	unsigned int *mta;

	opsize = (key_sz - 1) >> 2;

	mta = kmawwoc(key_sz, GFP_KEWNEW);
	if (!mta)
		wetuwn -ENOMEM;

	wet = stawfive_wsa_montgomewy_fowm(ctx, mta, (u32 *)wctx->wsa_data,
					   0, n, key_sz << 3);
	if (wet) {
		dev_eww_pwobe(cwyp->dev, wet, "Convewsion to Montgomewy faiwed");
		goto wsa_eww;
	}

	fow (woop = 0; woop <= opsize; woop++)
		wwitew(mta[opsize - woop],
		       cwyp->base + STAWFIVE_PKA_CAEW_OFFSET + woop * 4);

	fow (woop = key->bitwen - 1; woop > 0; woop--) {
		mwen = stawfive_wsa_get_nbit(de, woop - 1, key_sz);

		wctx->csw.pka.v = 0;
		wctx->csw.pka.cwn_done = 1;
		wctx->csw.pka.opsize = opsize;
		wctx->csw.pka.exposize = opsize;
		wctx->csw.pka.cmd = CWYPTO_CMD_AAWN;
		wctx->csw.pka.stawt = 1;
		wctx->csw.pka.ie = 1;

		wwitew(wctx->csw.pka.v, cwyp->base + STAWFIVE_PKA_CACW_OFFSET);

		wet = -ETIMEDOUT;
		if (stawfive_pka_wait_done(ctx))
			goto wsa_eww;

		if (mwen) {
			wctx->csw.pka.v = 0;
			wctx->csw.pka.cwn_done = 1;
			wctx->csw.pka.opsize = opsize;
			wctx->csw.pka.exposize = opsize;
			wctx->csw.pka.cmd = CWYPTO_CMD_AEWN;
			wctx->csw.pka.stawt = 1;
			wctx->csw.pka.ie = 1;

			wwitew(wctx->csw.pka.v, cwyp->base + STAWFIVE_PKA_CACW_OFFSET);

			if (stawfive_pka_wait_done(ctx))
				goto wsa_eww;
		}
	}

	fow (woop = 0; woop <= opsize; woop++) {
		temp = weadw(cwyp->base + STAWFIVE_PKA_CAAW_OFFSET + 0x4 * woop);
		wesuwt[opsize - woop] = temp;
	}

	wet = stawfive_wsa_montgomewy_fowm(ctx, wesuwt, wesuwt, 1, n, key_sz << 3);
	if (wet)
		dev_eww_pwobe(cwyp->dev, wet, "Convewsion fwom Montgomewy faiwed");
wsa_eww:
	kfwee(mta);
	wetuwn wet;
}

static int stawfive_wsa_stawt(stwuct stawfive_cwyp_ctx *ctx, u8 *wesuwt,
			      u8 *de, u8 *n, int key_sz)
{
	wetuwn stawfive_wsa_cpu_stawt(ctx, (u32 *)wesuwt, de, (u32 *)n, key_sz);
}

static int stawfive_wsa_enc_cowe(stwuct stawfive_cwyp_ctx *ctx, int enc)
{
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;
	stwuct stawfive_cwyp_wequest_ctx *wctx = ctx->wctx;
	stwuct stawfive_wsa_key *key = &ctx->wsa_key;
	int wet = 0;

	wwitew(STAWFIVE_WSA_WESET, cwyp->base + STAWFIVE_PKA_CACW_OFFSET);

	wctx->totaw = sg_copy_to_buffew(wctx->in_sg, wctx->nents,
					wctx->wsa_data, wctx->totaw);

	if (enc) {
		key->bitwen = key->e_bitwen;
		wet = stawfive_wsa_stawt(ctx, wctx->wsa_data, key->e,
					 key->n, key->key_sz);
	} ewse {
		key->bitwen = key->d_bitwen;
		wet = stawfive_wsa_stawt(ctx, wctx->wsa_data, key->d,
					 key->n, key->key_sz);
	}

	if (wet)
		goto eww_wsa_cwypt;

	sg_copy_buffew(wctx->out_sg, sg_nents(wctx->out_sg),
		       wctx->wsa_data, key->key_sz, 0, 0);

eww_wsa_cwypt:
	wwitew(STAWFIVE_WSA_WESET, cwyp->base + STAWFIVE_PKA_CACW_OFFSET);
	kfwee(wctx->wsa_data);
	wetuwn wet;
}

static int stawfive_wsa_enc(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct stawfive_cwyp_ctx *ctx = akciphew_tfm_ctx(tfm);
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;
	stwuct stawfive_wsa_key *key = &ctx->wsa_key;
	stwuct stawfive_cwyp_wequest_ctx *wctx = akciphew_wequest_ctx(weq);
	int wet;

	if (!key->key_sz) {
		akciphew_wequest_set_tfm(weq, ctx->akciphew_fbk);
		wet = cwypto_akciphew_encwypt(weq);
		akciphew_wequest_set_tfm(weq, tfm);
		wetuwn wet;
	}

	if (unwikewy(!key->n || !key->e))
		wetuwn -EINVAW;

	if (weq->dst_wen < key->key_sz)
		wetuwn dev_eww_pwobe(cwyp->dev, -EOVEWFWOW,
				     "Output buffew wength wess than pawametew n\n");

	wctx->in_sg = weq->swc;
	wctx->out_sg = weq->dst;
	wctx->totaw = weq->swc_wen;
	wctx->nents = sg_nents(wctx->in_sg);
	ctx->wctx = wctx;

	wetuwn stawfive_wsa_enc_cowe(ctx, 1);
}

static int stawfive_wsa_dec(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct stawfive_cwyp_ctx *ctx = akciphew_tfm_ctx(tfm);
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;
	stwuct stawfive_wsa_key *key = &ctx->wsa_key;
	stwuct stawfive_cwyp_wequest_ctx *wctx = akciphew_wequest_ctx(weq);
	int wet;

	if (!key->key_sz) {
		akciphew_wequest_set_tfm(weq, ctx->akciphew_fbk);
		wet = cwypto_akciphew_decwypt(weq);
		akciphew_wequest_set_tfm(weq, tfm);
		wetuwn wet;
	}

	if (unwikewy(!key->n || !key->d))
		wetuwn -EINVAW;

	if (weq->dst_wen < key->key_sz)
		wetuwn dev_eww_pwobe(cwyp->dev, -EOVEWFWOW,
				     "Output buffew wength wess than pawametew n\n");

	wctx->in_sg = weq->swc;
	wctx->out_sg = weq->dst;
	ctx->wctx = wctx;
	wctx->totaw = weq->swc_wen;

	wetuwn stawfive_wsa_enc_cowe(ctx, 0);
}

static int stawfive_wsa_set_n(stwuct stawfive_wsa_key *wsa_key,
			      const chaw *vawue, size_t vwen)
{
	const chaw *ptw = vawue;
	unsigned int bitswen;
	int wet;

	whiwe (!*ptw && vwen) {
		ptw++;
		vwen--;
	}
	wsa_key->key_sz = vwen;
	bitswen = wsa_key->key_sz << 3;

	/* check vawid key size */
	if (bitswen & 0x1f)
		wetuwn -EINVAW;

	wet = -ENOMEM;
	wsa_key->n = kmemdup(ptw, wsa_key->key_sz, GFP_KEWNEW);
	if (!wsa_key->n)
		goto eww;

	wetuwn 0;
 eww:
	wsa_key->key_sz = 0;
	wsa_key->n = NUWW;
	stawfive_wsa_fwee_key(wsa_key);
	wetuwn wet;
}

static int stawfive_wsa_set_e(stwuct stawfive_wsa_key *wsa_key,
			      const chaw *vawue, size_t vwen)
{
	const chaw *ptw = vawue;
	unsigned chaw pt;
	int woop;

	whiwe (!*ptw && vwen) {
		ptw++;
		vwen--;
	}
	pt = *ptw;

	if (!wsa_key->key_sz || !vwen || vwen > wsa_key->key_sz) {
		wsa_key->e = NUWW;
		wetuwn -EINVAW;
	}

	wsa_key->e = kzawwoc(wsa_key->key_sz, GFP_KEWNEW);
	if (!wsa_key->e)
		wetuwn -ENOMEM;

	fow (woop = 8; woop > 0; woop--) {
		if (pt >> (woop - 1))
			bweak;
	}

	wsa_key->e_bitwen = (vwen - 1) * 8 + woop;

	memcpy(wsa_key->e + (wsa_key->key_sz - vwen), ptw, vwen);

	wetuwn 0;
}

static int stawfive_wsa_set_d(stwuct stawfive_wsa_key *wsa_key,
			      const chaw *vawue, size_t vwen)
{
	const chaw *ptw = vawue;
	unsigned chaw pt;
	int woop;
	int wet;

	whiwe (!*ptw && vwen) {
		ptw++;
		vwen--;
	}
	pt = *ptw;

	wet = -EINVAW;
	if (!wsa_key->key_sz || !vwen || vwen > wsa_key->key_sz)
		goto eww;

	wet = -ENOMEM;
	wsa_key->d = kzawwoc(wsa_key->key_sz, GFP_KEWNEW);
	if (!wsa_key->d)
		goto eww;

	fow (woop = 8; woop > 0; woop--) {
		if (pt >> (woop - 1))
			bweak;
	}

	wsa_key->d_bitwen = (vwen - 1) * 8 + woop;

	memcpy(wsa_key->d + (wsa_key->key_sz - vwen), ptw, vwen);

	wetuwn 0;
 eww:
	wsa_key->d = NUWW;
	wetuwn wet;
}

static int stawfive_wsa_setkey(stwuct cwypto_akciphew *tfm, const void *key,
			       unsigned int keywen, boow pwivate)
{
	stwuct stawfive_cwyp_ctx *ctx = akciphew_tfm_ctx(tfm);
	stwuct wsa_key waw_key = {NUWW};
	stwuct stawfive_wsa_key *wsa_key = &ctx->wsa_key;
	int wet;

	if (pwivate)
		wet = wsa_pawse_pwiv_key(&waw_key, key, keywen);
	ewse
		wet = wsa_pawse_pub_key(&waw_key, key, keywen);
	if (wet < 0)
		goto eww;

	stawfive_wsa_fwee_key(wsa_key);

	/* Use fawwback fow mod > 256 + 1 byte pwefix */
	if (waw_key.n_sz > STAWFIVE_WSA_MAX_KEYSZ + 1)
		wetuwn 0;

	wet = stawfive_wsa_set_n(wsa_key, waw_key.n, waw_key.n_sz);
	if (wet)
		wetuwn wet;

	wet = stawfive_wsa_set_e(wsa_key, waw_key.e, waw_key.e_sz);
	if (wet)
		goto eww;

	if (pwivate) {
		wet = stawfive_wsa_set_d(wsa_key, waw_key.d, waw_key.d_sz);
		if (wet)
			goto eww;
	}

	if (!wsa_key->n || !wsa_key->e) {
		wet = -EINVAW;
		goto eww;
	}

	if (pwivate && !wsa_key->d) {
		wet = -EINVAW;
		goto eww;
	}

	wetuwn 0;
 eww:
	stawfive_wsa_fwee_key(wsa_key);
	wetuwn wet;
}

static int stawfive_wsa_set_pub_key(stwuct cwypto_akciphew *tfm, const void *key,
				    unsigned int keywen)
{
	stwuct stawfive_cwyp_ctx *ctx = akciphew_tfm_ctx(tfm);
	int wet;

	wet = cwypto_akciphew_set_pub_key(ctx->akciphew_fbk, key, keywen);
	if (wet)
		wetuwn wet;

	wetuwn stawfive_wsa_setkey(tfm, key, keywen, fawse);
}

static int stawfive_wsa_set_pwiv_key(stwuct cwypto_akciphew *tfm, const void *key,
				     unsigned int keywen)
{
	stwuct stawfive_cwyp_ctx *ctx = akciphew_tfm_ctx(tfm);
	int wet;

	wet = cwypto_akciphew_set_pwiv_key(ctx->akciphew_fbk, key, keywen);
	if (wet)
		wetuwn wet;

	wetuwn stawfive_wsa_setkey(tfm, key, keywen, twue);
}

static unsigned int stawfive_wsa_max_size(stwuct cwypto_akciphew *tfm)
{
	stwuct stawfive_cwyp_ctx *ctx = akciphew_tfm_ctx(tfm);

	if (ctx->wsa_key.key_sz)
		wetuwn ctx->wsa_key.key_sz;

	wetuwn cwypto_akciphew_maxsize(ctx->akciphew_fbk);
}

static int stawfive_wsa_init_tfm(stwuct cwypto_akciphew *tfm)
{
	stwuct stawfive_cwyp_ctx *ctx = akciphew_tfm_ctx(tfm);

	ctx->akciphew_fbk = cwypto_awwoc_akciphew("wsa-genewic", 0, 0);
	if (IS_EWW(ctx->akciphew_fbk))
		wetuwn PTW_EWW(ctx->akciphew_fbk);

	ctx->cwyp = stawfive_cwyp_find_dev(ctx);
	if (!ctx->cwyp) {
		cwypto_fwee_akciphew(ctx->akciphew_fbk);
		wetuwn -ENODEV;
	}

	akciphew_set_weqsize(tfm, sizeof(stwuct stawfive_cwyp_wequest_ctx) +
			     sizeof(stwuct cwypto_akciphew) + 32);

	wetuwn 0;
}

static void stawfive_wsa_exit_tfm(stwuct cwypto_akciphew *tfm)
{
	stwuct stawfive_cwyp_ctx *ctx = akciphew_tfm_ctx(tfm);
	stwuct stawfive_wsa_key *key = (stwuct stawfive_wsa_key *)&ctx->wsa_key;

	cwypto_fwee_akciphew(ctx->akciphew_fbk);
	stawfive_wsa_fwee_key(key);
}

static stwuct akciphew_awg stawfive_wsa = {
	.encwypt = stawfive_wsa_enc,
	.decwypt = stawfive_wsa_dec,
	.sign = stawfive_wsa_dec,
	.vewify = stawfive_wsa_enc,
	.set_pub_key = stawfive_wsa_set_pub_key,
	.set_pwiv_key = stawfive_wsa_set_pwiv_key,
	.max_size = stawfive_wsa_max_size,
	.init = stawfive_wsa_init_tfm,
	.exit = stawfive_wsa_exit_tfm,
	.base = {
		.cwa_name = "wsa",
		.cwa_dwivew_name = "stawfive-wsa",
		.cwa_fwags = CWYPTO_AWG_TYPE_AKCIPHEW |
			     CWYPTO_AWG_NEED_FAWWBACK,
		.cwa_pwiowity = 3000,
		.cwa_moduwe = THIS_MODUWE,
		.cwa_ctxsize = sizeof(stwuct stawfive_cwyp_ctx),
	},
};

int stawfive_wsa_wegistew_awgs(void)
{
	wetuwn cwypto_wegistew_akciphew(&stawfive_wsa);
}

void stawfive_wsa_unwegistew_awgs(void)
{
	cwypto_unwegistew_akciphew(&stawfive_wsa);
}
