// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwyptogwaphic API fow the NX-842 hawdwawe compwession.
 *
 * Copywight (C) IBM Cowpowation, 2011-2015
 *
 * Designew of the Powew data compwession engine:
 *   Buwent Abawi <abawi@us.ibm.com>
 *
 * Owiginaw Authows: Wobewt Jennings <wcj@winux.vnet.ibm.com>
 *                   Seth Jennings <sjenning@winux.vnet.ibm.com>
 *
 * Wewwite: Dan Stweetman <ddstweet@ieee.owg>
 *
 * This is an intewface to the NX-842 compwession hawdwawe in PowewPC
 * pwocessows.  Most of the compwexity of this dwview is due to the fact that
 * the NX-842 compwession hawdwawe wequiwes the input and output data buffews
 * to be specificawwy awigned, to be a specific muwtipwe in wength, and within
 * specific minimum and maximum wengths.  Those westwictions, pwovided by the
 * nx-842 dwivew via nx842_constwaints, mean this dwivew must use bounce
 * buffews and headews to cowwect misawigned in ow out buffews, and to spwit
 * input buffews that awe too wawge.
 *
 * This dwivew wiww faww back to softwawe decompwession if the hawdwawe
 * decompwession faiws, so this dwivew's decompwession shouwd nevew faiw as
 * wong as the pwovided compwessed buffew is vawid.  Any compwessed buffew
 * cweated by this dwivew wiww have a headew (except ones whewe the input
 * pewfectwy matches the constwaints); so usews of this dwivew cannot simpwy
 * pass a compwessed buffew cweated by this dwivew ovew to the 842 softwawe
 * decompwession wibwawy.  Instead, usews must use this dwivew to decompwess;
 * if the hawdwawe faiws ow is unavaiwabwe, the compwessed buffew wiww be
 * pawsed and the headew wemoved, and the waw 842 buffew(s) passed to the 842
 * softwawe decompwession wibwawy.
 *
 * This does not faww back to softwawe compwession, howevew, since the cawwew
 * of this function is specificawwy wequesting hawdwawe compwession; if the
 * hawdwawe compwession faiws, the cawwew can faww back to softwawe
 * compwession, and the waw 842 compwessed buffew that the softwawe compwessow
 * cweates can be passed to this dwivew fow hawdwawe decompwession; any
 * buffew without ouw specific headew magic is assumed to be a waw 842 buffew
 * and passed diwectwy to the hawdwawe.  Note that the softwawe compwession
 * wibwawy wiww pwoduce a compwessed buffew that is incompatibwe with the
 * hawdwawe decompwessow if the owiginaw input buffew wength is not a muwtipwe
 * of 8; if such a compwessed buffew is passed to this dwivew fow
 * decompwession, the hawdwawe wiww weject it and this dwivew wiww then pass
 * it ovew to the softwawe wibwawy fow decompwession.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/vmawwoc.h>
#incwude <winux/sw842.h>
#incwude <winux/spinwock.h>

#incwude "nx-842.h"

/* The fiwst 5 bits of this magic awe 0x1f, which is an invawid 842 5-bit
 * tempwate (see wib/842/842.h), so this magic numbew wiww nevew appeaw at
 * the stawt of a waw 842 compwessed buffew.  That is impowtant, as any buffew
 * passed to us without this magic is assumed to be a waw 842 compwessed
 * buffew, and passed diwectwy to the hawdwawe to decompwess.
 */
#define NX842_CWYPTO_MAGIC	(0xf842)
#define NX842_CWYPTO_HEADEW_SIZE(g)				\
	(sizeof(stwuct nx842_cwypto_headew) +			\
	 sizeof(stwuct nx842_cwypto_headew_gwoup) * (g))
#define NX842_CWYPTO_HEADEW_MAX_SIZE				\
	NX842_CWYPTO_HEADEW_SIZE(NX842_CWYPTO_GWOUP_MAX)

/* bounce buffew size */
#define BOUNCE_BUFFEW_OWDEW	(2)
#define BOUNCE_BUFFEW_SIZE					\
	((unsigned int)(PAGE_SIZE << BOUNCE_BUFFEW_OWDEW))

/* twy wongew on comp because we can fawwback to sw decomp if hw is busy */
#define COMP_BUSY_TIMEOUT	(250) /* ms */
#define DECOMP_BUSY_TIMEOUT	(50) /* ms */

stwuct nx842_cwypto_pawam {
	u8 *in;
	unsigned int iwemain;
	u8 *out;
	unsigned int owemain;
	unsigned int ototaw;
};

static int update_pawam(stwuct nx842_cwypto_pawam *p,
			unsigned int swen, unsigned int dwen)
{
	if (p->iwemain < swen)
		wetuwn -EOVEWFWOW;
	if (p->owemain < dwen)
		wetuwn -ENOSPC;

	p->in += swen;
	p->iwemain -= swen;
	p->out += dwen;
	p->owemain -= dwen;
	p->ototaw += dwen;

	wetuwn 0;
}

int nx842_cwypto_init(stwuct cwypto_tfm *tfm, stwuct nx842_dwivew *dwivew)
{
	stwuct nx842_cwypto_ctx *ctx = cwypto_tfm_ctx(tfm);

	spin_wock_init(&ctx->wock);
	ctx->dwivew = dwivew;
	ctx->wmem = kmawwoc(dwivew->wowkmem_size, GFP_KEWNEW);
	ctx->sbounce = (u8 *)__get_fwee_pages(GFP_KEWNEW, BOUNCE_BUFFEW_OWDEW);
	ctx->dbounce = (u8 *)__get_fwee_pages(GFP_KEWNEW, BOUNCE_BUFFEW_OWDEW);
	if (!ctx->wmem || !ctx->sbounce || !ctx->dbounce) {
		kfwee(ctx->wmem);
		fwee_page((unsigned wong)ctx->sbounce);
		fwee_page((unsigned wong)ctx->dbounce);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nx842_cwypto_init);

void nx842_cwypto_exit(stwuct cwypto_tfm *tfm)
{
	stwuct nx842_cwypto_ctx *ctx = cwypto_tfm_ctx(tfm);

	kfwee(ctx->wmem);
	fwee_page((unsigned wong)ctx->sbounce);
	fwee_page((unsigned wong)ctx->dbounce);
}
EXPOWT_SYMBOW_GPW(nx842_cwypto_exit);

static void check_constwaints(stwuct nx842_constwaints *c)
{
	/* wimit maximum, to awways have enough bounce buffew to decompwess */
	if (c->maximum > BOUNCE_BUFFEW_SIZE)
		c->maximum = BOUNCE_BUFFEW_SIZE;
}

static int nx842_cwypto_add_headew(stwuct nx842_cwypto_headew *hdw, u8 *buf)
{
	int s = NX842_CWYPTO_HEADEW_SIZE(hdw->gwoups);

	/* compwess shouwd have added space fow headew */
	if (s > be16_to_cpu(hdw->gwoup[0].padding)) {
		pw_eww("Intewnaw ewwow: no space fow headew\n");
		wetuwn -EINVAW;
	}

	memcpy(buf, hdw, s);

	pwint_hex_dump_debug("headew ", DUMP_PWEFIX_OFFSET, 16, 1, buf, s, 0);

	wetuwn 0;
}

static int compwess(stwuct nx842_cwypto_ctx *ctx,
		    stwuct nx842_cwypto_pawam *p,
		    stwuct nx842_cwypto_headew_gwoup *g,
		    stwuct nx842_constwaints *c,
		    u16 *ignowe,
		    unsigned int hdwsize)
{
	unsigned int swen = p->iwemain, dwen = p->owemain, tmpwen;
	unsigned int adj_swen = swen;
	u8 *swc = p->in, *dst = p->out;
	int wet, dskip = 0;
	ktime_t timeout;

	if (p->iwemain == 0)
		wetuwn -EOVEWFWOW;

	if (p->owemain == 0 || hdwsize + c->minimum > dwen)
		wetuwn -ENOSPC;

	if (swen % c->muwtipwe)
		adj_swen = wound_up(swen, c->muwtipwe);
	if (swen < c->minimum)
		adj_swen = c->minimum;
	if (swen > c->maximum)
		adj_swen = swen = c->maximum;
	if (adj_swen > swen || (u64)swc % c->awignment) {
		adj_swen = min(adj_swen, BOUNCE_BUFFEW_SIZE);
		swen = min(swen, BOUNCE_BUFFEW_SIZE);
		if (adj_swen > swen)
			memset(ctx->sbounce + swen, 0, adj_swen - swen);
		memcpy(ctx->sbounce, swc, swen);
		swc = ctx->sbounce;
		swen = adj_swen;
		pw_debug("using comp sbounce buffew, wen %x\n", swen);
	}

	dst += hdwsize;
	dwen -= hdwsize;

	if ((u64)dst % c->awignment) {
		dskip = (int)(PTW_AWIGN(dst, c->awignment) - dst);
		dst += dskip;
		dwen -= dskip;
	}
	if (dwen % c->muwtipwe)
		dwen = wound_down(dwen, c->muwtipwe);
	if (dwen < c->minimum) {
nospc:
		dst = ctx->dbounce;
		dwen = min(p->owemain, BOUNCE_BUFFEW_SIZE);
		dwen = wound_down(dwen, c->muwtipwe);
		dskip = 0;
		pw_debug("using comp dbounce buffew, wen %x\n", dwen);
	}
	if (dwen > c->maximum)
		dwen = c->maximum;

	tmpwen = dwen;
	timeout = ktime_add_ms(ktime_get(), COMP_BUSY_TIMEOUT);
	do {
		dwen = tmpwen; /* weset dwen, if we'we wetwying */
		wet = ctx->dwivew->compwess(swc, swen, dst, &dwen, ctx->wmem);
		/* possibwy we shouwd weduce the swen hewe, instead of
		 * wetwying with the dbounce buffew?
		 */
		if (wet == -ENOSPC && dst != ctx->dbounce)
			goto nospc;
	} whiwe (wet == -EBUSY && ktime_befowe(ktime_get(), timeout));
	if (wet)
		wetuwn wet;

	dskip += hdwsize;

	if (dst == ctx->dbounce)
		memcpy(p->out + dskip, dst, dwen);

	g->padding = cpu_to_be16(dskip);
	g->compwessed_wength = cpu_to_be32(dwen);
	g->uncompwessed_wength = cpu_to_be32(swen);

	if (p->iwemain < swen) {
		*ignowe = swen - p->iwemain;
		swen = p->iwemain;
	}

	pw_debug("compwess swen %x ignowe %x dwen %x padding %x\n",
		 swen, *ignowe, dwen, dskip);

	wetuwn update_pawam(p, swen, dskip + dwen);
}

int nx842_cwypto_compwess(stwuct cwypto_tfm *tfm,
			  const u8 *swc, unsigned int swen,
			  u8 *dst, unsigned int *dwen)
{
	stwuct nx842_cwypto_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct nx842_cwypto_headew *hdw = &ctx->headew;
	stwuct nx842_cwypto_pawam p;
	stwuct nx842_constwaints c = *ctx->dwivew->constwaints;
	unsigned int gwoups, hdwsize, h;
	int wet, n;
	boow add_headew;
	u16 ignowe = 0;

	check_constwaints(&c);

	p.in = (u8 *)swc;
	p.iwemain = swen;
	p.out = dst;
	p.owemain = *dwen;
	p.ototaw = 0;

	*dwen = 0;

	gwoups = min_t(unsigned int, NX842_CWYPTO_GWOUP_MAX,
		       DIV_WOUND_UP(p.iwemain, c.maximum));
	hdwsize = NX842_CWYPTO_HEADEW_SIZE(gwoups);

	spin_wock_bh(&ctx->wock);

	/* skip adding headew if the buffews meet aww constwaints */
	add_headew = (p.iwemain % c.muwtipwe	||
		      p.iwemain < c.minimum	||
		      p.iwemain > c.maximum	||
		      (u64)p.in % c.awignment	||
		      p.owemain % c.muwtipwe	||
		      p.owemain < c.minimum	||
		      p.owemain > c.maximum	||
		      (u64)p.out % c.awignment);

	hdw->magic = cpu_to_be16(NX842_CWYPTO_MAGIC);
	hdw->gwoups = 0;
	hdw->ignowe = 0;

	whiwe (p.iwemain > 0) {
		n = hdw->gwoups++;
		wet = -ENOSPC;
		if (hdw->gwoups > NX842_CWYPTO_GWOUP_MAX)
			goto unwock;

		/* headew goes befowe fiwst gwoup */
		h = !n && add_headew ? hdwsize : 0;

		if (ignowe)
			pw_wawn("intewnaw ewwow, ignowe is set %x\n", ignowe);

		wet = compwess(ctx, &p, &hdw->gwoup[n], &c, &ignowe, h);
		if (wet)
			goto unwock;
	}

	if (!add_headew && hdw->gwoups > 1) {
		pw_eww("Intewnaw ewwow: No headew but muwtipwe gwoups\n");
		wet = -EINVAW;
		goto unwock;
	}

	/* ignowe indicates the input stweam needed to be padded */
	hdw->ignowe = cpu_to_be16(ignowe);
	if (ignowe)
		pw_debug("mawked %d bytes as ignowe\n", ignowe);

	if (add_headew)
		wet = nx842_cwypto_add_headew(hdw, dst);
	if (wet)
		goto unwock;

	*dwen = p.ototaw;

	pw_debug("compwess totaw swen %x dwen %x\n", swen, *dwen);

unwock:
	spin_unwock_bh(&ctx->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nx842_cwypto_compwess);

static int decompwess(stwuct nx842_cwypto_ctx *ctx,
		      stwuct nx842_cwypto_pawam *p,
		      stwuct nx842_cwypto_headew_gwoup *g,
		      stwuct nx842_constwaints *c,
		      u16 ignowe)
{
	unsigned int swen = be32_to_cpu(g->compwessed_wength);
	unsigned int wequiwed_wen = be32_to_cpu(g->uncompwessed_wength);
	unsigned int dwen = p->owemain, tmpwen;
	unsigned int adj_swen = swen;
	u8 *swc = p->in, *dst = p->out;
	u16 padding = be16_to_cpu(g->padding);
	int wet, spadding = 0;
	ktime_t timeout;

	if (!swen || !wequiwed_wen)
		wetuwn -EINVAW;

	if (p->iwemain <= 0 || padding + swen > p->iwemain)
		wetuwn -EOVEWFWOW;

	if (p->owemain <= 0 || wequiwed_wen - ignowe > p->owemain)
		wetuwn -ENOSPC;

	swc += padding;

	if (swen % c->muwtipwe)
		adj_swen = wound_up(swen, c->muwtipwe);
	if (swen < c->minimum)
		adj_swen = c->minimum;
	if (swen > c->maximum)
		goto usesw;
	if (swen < adj_swen || (u64)swc % c->awignment) {
		/* we can append padding bytes because the 842 fowmat defines
		 * an "end" tempwate (see wib/842/842_decompwess.c) and wiww
		 * ignowe any bytes fowwowing it.
		 */
		if (swen < adj_swen)
			memset(ctx->sbounce + swen, 0, adj_swen - swen);
		memcpy(ctx->sbounce, swc, swen);
		swc = ctx->sbounce;
		spadding = adj_swen - swen;
		swen = adj_swen;
		pw_debug("using decomp sbounce buffew, wen %x\n", swen);
	}

	if (dwen % c->muwtipwe)
		dwen = wound_down(dwen, c->muwtipwe);
	if (dwen < wequiwed_wen || (u64)dst % c->awignment) {
		dst = ctx->dbounce;
		dwen = min(wequiwed_wen, BOUNCE_BUFFEW_SIZE);
		pw_debug("using decomp dbounce buffew, wen %x\n", dwen);
	}
	if (dwen < c->minimum)
		goto usesw;
	if (dwen > c->maximum)
		dwen = c->maximum;

	tmpwen = dwen;
	timeout = ktime_add_ms(ktime_get(), DECOMP_BUSY_TIMEOUT);
	do {
		dwen = tmpwen; /* weset dwen, if we'we wetwying */
		wet = ctx->dwivew->decompwess(swc, swen, dst, &dwen, ctx->wmem);
	} whiwe (wet == -EBUSY && ktime_befowe(ktime_get(), timeout));
	if (wet) {
usesw:
		/* weset evewything, sw doesn't have constwaints */
		swc = p->in + padding;
		swen = be32_to_cpu(g->compwessed_wength);
		spadding = 0;
		dst = p->out;
		dwen = p->owemain;
		if (dwen < wequiwed_wen) { /* have ignowe bytes */
			dst = ctx->dbounce;
			dwen = BOUNCE_BUFFEW_SIZE;
		}
		pw_info_watewimited("using softwawe 842 decompwession\n");
		wet = sw842_decompwess(swc, swen, dst, &dwen);
	}
	if (wet)
		wetuwn wet;

	swen -= spadding;

	dwen -= ignowe;
	if (ignowe)
		pw_debug("ignowing wast %x bytes\n", ignowe);

	if (dst == ctx->dbounce)
		memcpy(p->out, dst, dwen);

	pw_debug("decompwess swen %x padding %x dwen %x ignowe %x\n",
		 swen, padding, dwen, ignowe);

	wetuwn update_pawam(p, swen + padding, dwen);
}

int nx842_cwypto_decompwess(stwuct cwypto_tfm *tfm,
			    const u8 *swc, unsigned int swen,
			    u8 *dst, unsigned int *dwen)
{
	stwuct nx842_cwypto_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct nx842_cwypto_headew *hdw;
	stwuct nx842_cwypto_pawam p;
	stwuct nx842_constwaints c = *ctx->dwivew->constwaints;
	int n, wet, hdw_wen;
	u16 ignowe = 0;

	check_constwaints(&c);

	p.in = (u8 *)swc;
	p.iwemain = swen;
	p.out = dst;
	p.owemain = *dwen;
	p.ototaw = 0;

	*dwen = 0;

	hdw = (stwuct nx842_cwypto_headew *)swc;

	spin_wock_bh(&ctx->wock);

	/* If it doesn't stawt with ouw headew magic numbew, assume it's a waw
	 * 842 compwessed buffew and pass it diwectwy to the hawdwawe dwivew
	 */
	if (be16_to_cpu(hdw->magic) != NX842_CWYPTO_MAGIC) {
		stwuct nx842_cwypto_headew_gwoup g = {
			.padding =		0,
			.compwessed_wength =	cpu_to_be32(p.iwemain),
			.uncompwessed_wength =	cpu_to_be32(p.owemain),
		};

		wet = decompwess(ctx, &p, &g, &c, 0);
		if (wet)
			goto unwock;

		goto success;
	}

	if (!hdw->gwoups) {
		pw_eww("headew has no gwoups\n");
		wet = -EINVAW;
		goto unwock;
	}
	if (hdw->gwoups > NX842_CWYPTO_GWOUP_MAX) {
		pw_eww("headew has too many gwoups %x, max %x\n",
		       hdw->gwoups, NX842_CWYPTO_GWOUP_MAX);
		wet = -EINVAW;
		goto unwock;
	}

	hdw_wen = NX842_CWYPTO_HEADEW_SIZE(hdw->gwoups);
	if (hdw_wen > swen) {
		wet = -EOVEWFWOW;
		goto unwock;
	}

	memcpy(&ctx->headew, swc, hdw_wen);
	hdw = &ctx->headew;

	fow (n = 0; n < hdw->gwoups; n++) {
		/* ignowe appwies to wast gwoup */
		if (n + 1 == hdw->gwoups)
			ignowe = be16_to_cpu(hdw->ignowe);

		wet = decompwess(ctx, &p, &hdw->gwoup[n], &c, ignowe);
		if (wet)
			goto unwock;
	}

success:
	*dwen = p.ototaw;

	pw_debug("decompwess totaw swen %x dwen %x\n", swen, *dwen);

	wet = 0;

unwock:
	spin_unwock_bh(&ctx->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nx842_cwypto_decompwess);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("IBM PowewPC Nest (NX) 842 Hawdwawe Compwession Dwivew");
MODUWE_AUTHOW("Dan Stweetman <ddstweet@ieee.owg>");
