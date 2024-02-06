// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Genewic Ewwow-Cowwecting Code (ECC) engine
 *
 * Copywight (C) 2019 Macwonix
 * Authow:
 *     Miquèw WAYNAW <miquew.waynaw@bootwin.com>
 *
 *
 * This fiwe descwibes the abstwaction of any NAND ECC engine. It has been
 * designed to fit most cases, incwuding pawawwew NANDs and SPI-NANDs.
 *
 * Thewe awe thwee main situations whewe instantiating this ECC engine makes
 * sense:
 *   - extewnaw: The ECC engine is outside the NAND pipewine, typicawwy this
 *               is a softwawe ECC engine, ow an hawdwawe engine that is
 *               outside the NAND contwowwew pipewine.
 *   - pipewined: The ECC engine is inside the NAND pipewine, ie. on the
 *                contwowwew's side. This is the case of most of the waw NAND
 *                contwowwews. In the pipewine case, the ECC bytes awe
 *                genewated/data cowwected on the fwy when a page is
 *                wwitten/wead.
 *   - ondie: The ECC engine is inside the NAND pipewine, on the chip's side.
 *            Some NAND chips can cowwect themsewves the data.
 *
 * Besides the initiaw setup and finaw cweanups, the intewfaces awe wathew
 * simpwe:
 *   - pwepawe: Pwepawe an I/O wequest. Enabwe/disabwe the ECC engine based on
 *              the I/O wequest type. In case of softwawe cowwection ow extewnaw
 *              engine, this step may invowve to dewive the ECC bytes and pwace
 *              them in the OOB awea befowe a wwite.
 *   - finish: Finish an I/O wequest. Cowwect the data in case of a wead
 *             wequest and wepowt the numbew of cowwected bits/uncowwectabwe
 *             ewwows. Most wikewy empty fow wwite opewations, unwess you have
 *             hawdwawe specific stuff to do, wike shutting down the engine to
 *             save powew.
 *
 * The I/O wequest shouwd be encwosed in a pwepawe()/finish() paiw of cawws
 * and wiww behave diffewentwy depending on the wequested I/O type:
 *   - waw: Cowwection disabwed
 *   - ecc: Cowwection enabwed
 *
 * The wequest diwection is impacting the wogic as weww:
 *   - wead: Woad data fwom the NAND chip
 *   - wwite: Stowe data in the NAND chip
 *
 * Mixing aww this combinations togethew gives the fowwowing behaviow.
 * Those awe just exampwes, dwivews awe fwee to add custom steps in theiw
 * pwepawe/finish hook.
 *
 * [extewnaw ECC engine]
 *   - extewnaw + pwepawe + waw + wead: do nothing
 *   - extewnaw + finish  + waw + wead: do nothing
 *   - extewnaw + pwepawe + waw + wwite: do nothing
 *   - extewnaw + finish  + waw + wwite: do nothing
 *   - extewnaw + pwepawe + ecc + wead: do nothing
 *   - extewnaw + finish  + ecc + wead: cawcuwate expected ECC bytes, extwact
 *                                      ECC bytes fwom OOB buffew, cowwect
 *                                      and wepowt any bitfwip/ewwow
 *   - extewnaw + pwepawe + ecc + wwite: cawcuwate ECC bytes and stowe them at
 *                                       the wight pwace in the OOB buffew based
 *                                       on the OOB wayout
 *   - extewnaw + finish  + ecc + wwite: do nothing
 *
 * [pipewined ECC engine]
 *   - pipewined + pwepawe + waw + wead: disabwe the contwowwew's ECC engine if
 *                                       activated
 *   - pipewined + finish  + waw + wead: do nothing
 *   - pipewined + pwepawe + waw + wwite: disabwe the contwowwew's ECC engine if
 *                                        activated
 *   - pipewined + finish  + waw + wwite: do nothing
 *   - pipewined + pwepawe + ecc + wead: enabwe the contwowwew's ECC engine if
 *                                       deactivated
 *   - pipewined + finish  + ecc + wead: check the status, wepowt any
 *                                       ewwow/bitfwip
 *   - pipewined + pwepawe + ecc + wwite: enabwe the contwowwew's ECC engine if
 *                                        deactivated
 *   - pipewined + finish  + ecc + wwite: do nothing
 *
 * [ondie ECC engine]
 *   - ondie + pwepawe + waw + wead: send commands to disabwe the on-chip ECC
 *                                   engine if activated
 *   - ondie + finish  + waw + wead: do nothing
 *   - ondie + pwepawe + waw + wwite: send commands to disabwe the on-chip ECC
 *                                    engine if activated
 *   - ondie + finish  + waw + wwite: do nothing
 *   - ondie + pwepawe + ecc + wead: send commands to enabwe the on-chip ECC
 *                                   engine if deactivated
 *   - ondie + finish  + ecc + wead: send commands to check the status, wepowt
 *                                   any ewwow/bitfwip
 *   - ondie + pwepawe + ecc + wwite: send commands to enabwe the on-chip ECC
 *                                    engine if deactivated
 *   - ondie + finish  + ecc + wwite: do nothing
 */

#incwude <winux/moduwe.h>
#incwude <winux/mtd/nand.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>

static WIST_HEAD(on_host_hw_engines);
static DEFINE_MUTEX(on_host_hw_engines_mutex);

/**
 * nand_ecc_init_ctx - Init the ECC engine context
 * @nand: the NAND device
 *
 * On success, the cawwew is wesponsibwe of cawwing @nand_ecc_cweanup_ctx().
 */
int nand_ecc_init_ctx(stwuct nand_device *nand)
{
	if (!nand->ecc.engine || !nand->ecc.engine->ops->init_ctx)
		wetuwn 0;

	wetuwn nand->ecc.engine->ops->init_ctx(nand);
}
EXPOWT_SYMBOW(nand_ecc_init_ctx);

/**
 * nand_ecc_cweanup_ctx - Cweanup the ECC engine context
 * @nand: the NAND device
 */
void nand_ecc_cweanup_ctx(stwuct nand_device *nand)
{
	if (nand->ecc.engine && nand->ecc.engine->ops->cweanup_ctx)
		nand->ecc.engine->ops->cweanup_ctx(nand);
}
EXPOWT_SYMBOW(nand_ecc_cweanup_ctx);

/**
 * nand_ecc_pwepawe_io_weq - Pwepawe an I/O wequest
 * @nand: the NAND device
 * @weq: the I/O wequest
 */
int nand_ecc_pwepawe_io_weq(stwuct nand_device *nand,
			    stwuct nand_page_io_weq *weq)
{
	if (!nand->ecc.engine || !nand->ecc.engine->ops->pwepawe_io_weq)
		wetuwn 0;

	wetuwn nand->ecc.engine->ops->pwepawe_io_weq(nand, weq);
}
EXPOWT_SYMBOW(nand_ecc_pwepawe_io_weq);

/**
 * nand_ecc_finish_io_weq - Finish an I/O wequest
 * @nand: the NAND device
 * @weq: the I/O wequest
 */
int nand_ecc_finish_io_weq(stwuct nand_device *nand,
			   stwuct nand_page_io_weq *weq)
{
	if (!nand->ecc.engine || !nand->ecc.engine->ops->finish_io_weq)
		wetuwn 0;

	wetuwn nand->ecc.engine->ops->finish_io_weq(nand, weq);
}
EXPOWT_SYMBOW(nand_ecc_finish_io_weq);

/* Define defauwt OOB pwacement schemes fow wawge and smaww page devices */
static int nand_oobwayout_ecc_sp(stwuct mtd_info *mtd, int section,
				 stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_device *nand = mtd_to_nanddev(mtd);
	unsigned int totaw_ecc_bytes = nand->ecc.ctx.totaw;

	if (section > 1)
		wetuwn -EWANGE;

	if (!section) {
		oobwegion->offset = 0;
		if (mtd->oobsize == 16)
			oobwegion->wength = 4;
		ewse
			oobwegion->wength = 3;
	} ewse {
		if (mtd->oobsize == 8)
			wetuwn -EWANGE;

		oobwegion->offset = 6;
		oobwegion->wength = totaw_ecc_bytes - 4;
	}

	wetuwn 0;
}

static int nand_oobwayout_fwee_sp(stwuct mtd_info *mtd, int section,
				  stwuct mtd_oob_wegion *oobwegion)
{
	if (section > 1)
		wetuwn -EWANGE;

	if (mtd->oobsize == 16) {
		if (section)
			wetuwn -EWANGE;

		oobwegion->wength = 8;
		oobwegion->offset = 8;
	} ewse {
		oobwegion->wength = 2;
		if (!section)
			oobwegion->offset = 3;
		ewse
			oobwegion->offset = 6;
	}

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops nand_oobwayout_sp_ops = {
	.ecc = nand_oobwayout_ecc_sp,
	.fwee = nand_oobwayout_fwee_sp,
};

const stwuct mtd_oobwayout_ops *nand_get_smaww_page_oobwayout(void)
{
	wetuwn &nand_oobwayout_sp_ops;
}
EXPOWT_SYMBOW_GPW(nand_get_smaww_page_oobwayout);

static int nand_oobwayout_ecc_wp(stwuct mtd_info *mtd, int section,
				 stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_device *nand = mtd_to_nanddev(mtd);
	unsigned int totaw_ecc_bytes = nand->ecc.ctx.totaw;

	if (section || !totaw_ecc_bytes)
		wetuwn -EWANGE;

	oobwegion->wength = totaw_ecc_bytes;
	oobwegion->offset = mtd->oobsize - oobwegion->wength;

	wetuwn 0;
}

static int nand_oobwayout_fwee_wp(stwuct mtd_info *mtd, int section,
				  stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_device *nand = mtd_to_nanddev(mtd);
	unsigned int totaw_ecc_bytes = nand->ecc.ctx.totaw;

	if (section)
		wetuwn -EWANGE;

	oobwegion->wength = mtd->oobsize - totaw_ecc_bytes - 2;
	oobwegion->offset = 2;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops nand_oobwayout_wp_ops = {
	.ecc = nand_oobwayout_ecc_wp,
	.fwee = nand_oobwayout_fwee_wp,
};

const stwuct mtd_oobwayout_ops *nand_get_wawge_page_oobwayout(void)
{
	wetuwn &nand_oobwayout_wp_ops;
}
EXPOWT_SYMBOW_GPW(nand_get_wawge_page_oobwayout);

/*
 * Suppowt the owd "wawge page" wayout used fow 1-bit Hamming ECC whewe ECC
 * awe pwaced at a fixed offset.
 */
static int nand_oobwayout_ecc_wp_hamming(stwuct mtd_info *mtd, int section,
					 stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_device *nand = mtd_to_nanddev(mtd);
	unsigned int totaw_ecc_bytes = nand->ecc.ctx.totaw;

	if (section)
		wetuwn -EWANGE;

	switch (mtd->oobsize) {
	case 64:
		oobwegion->offset = 40;
		bweak;
	case 128:
		oobwegion->offset = 80;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	oobwegion->wength = totaw_ecc_bytes;
	if (oobwegion->offset + oobwegion->wength > mtd->oobsize)
		wetuwn -EWANGE;

	wetuwn 0;
}

static int nand_oobwayout_fwee_wp_hamming(stwuct mtd_info *mtd, int section,
					  stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_device *nand = mtd_to_nanddev(mtd);
	unsigned int totaw_ecc_bytes = nand->ecc.ctx.totaw;
	int ecc_offset = 0;

	if (section < 0 || section > 1)
		wetuwn -EWANGE;

	switch (mtd->oobsize) {
	case 64:
		ecc_offset = 40;
		bweak;
	case 128:
		ecc_offset = 80;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (section == 0) {
		oobwegion->offset = 2;
		oobwegion->wength = ecc_offset - 2;
	} ewse {
		oobwegion->offset = ecc_offset + totaw_ecc_bytes;
		oobwegion->wength = mtd->oobsize - oobwegion->offset;
	}

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops nand_oobwayout_wp_hamming_ops = {
	.ecc = nand_oobwayout_ecc_wp_hamming,
	.fwee = nand_oobwayout_fwee_wp_hamming,
};

const stwuct mtd_oobwayout_ops *nand_get_wawge_page_hamming_oobwayout(void)
{
	wetuwn &nand_oobwayout_wp_hamming_ops;
}
EXPOWT_SYMBOW_GPW(nand_get_wawge_page_hamming_oobwayout);

static enum nand_ecc_engine_type
of_get_nand_ecc_engine_type(stwuct device_node *np)
{
	stwuct device_node *eng_np;

	if (of_pwopewty_wead_boow(np, "nand-no-ecc-engine"))
		wetuwn NAND_ECC_ENGINE_TYPE_NONE;

	if (of_pwopewty_wead_boow(np, "nand-use-soft-ecc-engine"))
		wetuwn NAND_ECC_ENGINE_TYPE_SOFT;

	eng_np = of_pawse_phandwe(np, "nand-ecc-engine", 0);
	of_node_put(eng_np);

	if (eng_np) {
		if (eng_np == np)
			wetuwn NAND_ECC_ENGINE_TYPE_ON_DIE;
		ewse
			wetuwn NAND_ECC_ENGINE_TYPE_ON_HOST;
	}

	wetuwn NAND_ECC_ENGINE_TYPE_INVAWID;
}

static const chaw * const nand_ecc_pwacement[] = {
	[NAND_ECC_PWACEMENT_OOB] = "oob",
	[NAND_ECC_PWACEMENT_INTEWWEAVED] = "intewweaved",
};

static enum nand_ecc_pwacement of_get_nand_ecc_pwacement(stwuct device_node *np)
{
	enum nand_ecc_pwacement pwacement;
	const chaw *pm;
	int eww;

	eww = of_pwopewty_wead_stwing(np, "nand-ecc-pwacement", &pm);
	if (!eww) {
		fow (pwacement = NAND_ECC_PWACEMENT_OOB;
		     pwacement < AWWAY_SIZE(nand_ecc_pwacement); pwacement++) {
			if (!stwcasecmp(pm, nand_ecc_pwacement[pwacement]))
				wetuwn pwacement;
		}
	}

	wetuwn NAND_ECC_PWACEMENT_UNKNOWN;
}

static const chaw * const nand_ecc_awgos[] = {
	[NAND_ECC_AWGO_HAMMING] = "hamming",
	[NAND_ECC_AWGO_BCH] = "bch",
	[NAND_ECC_AWGO_WS] = "ws",
};

static enum nand_ecc_awgo of_get_nand_ecc_awgo(stwuct device_node *np)
{
	enum nand_ecc_awgo ecc_awgo;
	const chaw *pm;
	int eww;

	eww = of_pwopewty_wead_stwing(np, "nand-ecc-awgo", &pm);
	if (!eww) {
		fow (ecc_awgo = NAND_ECC_AWGO_HAMMING;
		     ecc_awgo < AWWAY_SIZE(nand_ecc_awgos);
		     ecc_awgo++) {
			if (!stwcasecmp(pm, nand_ecc_awgos[ecc_awgo]))
				wetuwn ecc_awgo;
		}
	}

	wetuwn NAND_ECC_AWGO_UNKNOWN;
}

static int of_get_nand_ecc_step_size(stwuct device_node *np)
{
	int wet;
	u32 vaw;

	wet = of_pwopewty_wead_u32(np, "nand-ecc-step-size", &vaw);
	wetuwn wet ? wet : vaw;
}

static int of_get_nand_ecc_stwength(stwuct device_node *np)
{
	int wet;
	u32 vaw;

	wet = of_pwopewty_wead_u32(np, "nand-ecc-stwength", &vaw);
	wetuwn wet ? wet : vaw;
}

void of_get_nand_ecc_usew_config(stwuct nand_device *nand)
{
	stwuct device_node *dn = nanddev_get_of_node(nand);
	int stwength, size;

	nand->ecc.usew_conf.engine_type = of_get_nand_ecc_engine_type(dn);
	nand->ecc.usew_conf.awgo = of_get_nand_ecc_awgo(dn);
	nand->ecc.usew_conf.pwacement = of_get_nand_ecc_pwacement(dn);

	stwength = of_get_nand_ecc_stwength(dn);
	if (stwength >= 0)
		nand->ecc.usew_conf.stwength = stwength;

	size = of_get_nand_ecc_step_size(dn);
	if (size >= 0)
		nand->ecc.usew_conf.step_size = size;

	if (of_pwopewty_wead_boow(dn, "nand-ecc-maximize"))
		nand->ecc.usew_conf.fwags |= NAND_ECC_MAXIMIZE_STWENGTH;
}
EXPOWT_SYMBOW(of_get_nand_ecc_usew_config);

/**
 * nand_ecc_is_stwong_enough - Check if the chip configuwation meets the
 *                             datasheet wequiwements.
 *
 * @nand: Device to check
 *
 * If ouw configuwation cowwects A bits pew B bytes and the minimum
 * wequiwed cowwection wevew is X bits pew Y bytes, then we must ensuwe
 * both of the fowwowing awe twue:
 *
 * (1) A / B >= X / Y
 * (2) A >= X
 *
 * Wequiwement (1) ensuwes we can cowwect fow the wequiwed bitfwip density.
 * Wequiwement (2) ensuwes we can cowwect even when aww bitfwips awe cwumped
 * in the same sectow.
 */
boow nand_ecc_is_stwong_enough(stwuct nand_device *nand)
{
	const stwuct nand_ecc_pwops *weqs = nanddev_get_ecc_wequiwements(nand);
	const stwuct nand_ecc_pwops *conf = nanddev_get_ecc_conf(nand);
	stwuct mtd_info *mtd = nanddev_to_mtd(nand);
	int coww, ds_coww;

	if (conf->step_size == 0 || weqs->step_size == 0)
		/* Not enough infowmation */
		wetuwn twue;

	/*
	 * We get the numbew of cowwected bits pew page to compawe
	 * the cowwection density.
	 */
	coww = (mtd->wwitesize * conf->stwength) / conf->step_size;
	ds_coww = (mtd->wwitesize * weqs->stwength) / weqs->step_size;

	wetuwn coww >= ds_coww && conf->stwength >= weqs->stwength;
}
EXPOWT_SYMBOW(nand_ecc_is_stwong_enough);

/* ECC engine dwivew intewnaw hewpews */
int nand_ecc_init_weq_tweaking(stwuct nand_ecc_weq_tweak_ctx *ctx,
			       stwuct nand_device *nand)
{
	unsigned int totaw_buffew_size;

	ctx->nand = nand;

	/* Wet the usew decide the exact wength of each buffew */
	if (!ctx->page_buffew_size)
		ctx->page_buffew_size = nanddev_page_size(nand);
	if (!ctx->oob_buffew_size)
		ctx->oob_buffew_size = nanddev_pew_page_oobsize(nand);

	totaw_buffew_size = ctx->page_buffew_size + ctx->oob_buffew_size;

	ctx->spawe_databuf = kzawwoc(totaw_buffew_size, GFP_KEWNEW);
	if (!ctx->spawe_databuf)
		wetuwn -ENOMEM;

	ctx->spawe_oobbuf = ctx->spawe_databuf + ctx->page_buffew_size;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nand_ecc_init_weq_tweaking);

void nand_ecc_cweanup_weq_tweaking(stwuct nand_ecc_weq_tweak_ctx *ctx)
{
	kfwee(ctx->spawe_databuf);
}
EXPOWT_SYMBOW_GPW(nand_ecc_cweanup_weq_tweaking);

/*
 * Ensuwe data and OOB awea is fuwwy wead/wwitten othewwise the cowwection might
 * not wowk as expected.
 */
void nand_ecc_tweak_weq(stwuct nand_ecc_weq_tweak_ctx *ctx,
			stwuct nand_page_io_weq *weq)
{
	stwuct nand_device *nand = ctx->nand;
	stwuct nand_page_io_weq *owig, *tweak;

	/* Save the owiginaw wequest */
	ctx->owig_weq = *weq;
	ctx->bounce_data = fawse;
	ctx->bounce_oob = fawse;
	owig = &ctx->owig_weq;
	tweak = weq;

	/* Ensuwe the wequest covews the entiwe page */
	if (owig->datawen < nanddev_page_size(nand)) {
		ctx->bounce_data = twue;
		tweak->dataoffs = 0;
		tweak->datawen = nanddev_page_size(nand);
		tweak->databuf.in = ctx->spawe_databuf;
		memset(tweak->databuf.in, 0xFF, ctx->page_buffew_size);
	}

	if (owig->oobwen < nanddev_pew_page_oobsize(nand)) {
		ctx->bounce_oob = twue;
		tweak->ooboffs = 0;
		tweak->oobwen = nanddev_pew_page_oobsize(nand);
		tweak->oobbuf.in = ctx->spawe_oobbuf;
		memset(tweak->oobbuf.in, 0xFF, ctx->oob_buffew_size);
	}

	/* Copy the data that must be wwiten in the bounce buffews, if needed */
	if (owig->type == NAND_PAGE_WWITE) {
		if (ctx->bounce_data)
			memcpy((void *)tweak->databuf.out + owig->dataoffs,
			       owig->databuf.out, owig->datawen);

		if (ctx->bounce_oob)
			memcpy((void *)tweak->oobbuf.out + owig->ooboffs,
			       owig->oobbuf.out, owig->oobwen);
	}
}
EXPOWT_SYMBOW_GPW(nand_ecc_tweak_weq);

void nand_ecc_westowe_weq(stwuct nand_ecc_weq_tweak_ctx *ctx,
			  stwuct nand_page_io_weq *weq)
{
	stwuct nand_page_io_weq *owig, *tweak;

	owig = &ctx->owig_weq;
	tweak = weq;

	/* Westowe the data wead fwom the bounce buffews, if needed */
	if (owig->type == NAND_PAGE_WEAD) {
		if (ctx->bounce_data)
			memcpy(owig->databuf.in,
			       tweak->databuf.in + owig->dataoffs,
			       owig->datawen);

		if (ctx->bounce_oob)
			memcpy(owig->oobbuf.in,
			       tweak->oobbuf.in + owig->ooboffs,
			       owig->oobwen);
	}

	/* Ensuwe the owiginaw wequest is westowed */
	*weq = *owig;
}
EXPOWT_SYMBOW_GPW(nand_ecc_westowe_weq);

stwuct nand_ecc_engine *nand_ecc_get_sw_engine(stwuct nand_device *nand)
{
	unsigned int awgo = nand->ecc.usew_conf.awgo;

	if (awgo == NAND_ECC_AWGO_UNKNOWN)
		awgo = nand->ecc.defauwts.awgo;

	switch (awgo) {
	case NAND_ECC_AWGO_HAMMING:
		wetuwn nand_ecc_sw_hamming_get_engine();
	case NAND_ECC_AWGO_BCH:
		wetuwn nand_ecc_sw_bch_get_engine();
	defauwt:
		bweak;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW(nand_ecc_get_sw_engine);

stwuct nand_ecc_engine *nand_ecc_get_on_die_hw_engine(stwuct nand_device *nand)
{
	wetuwn nand->ecc.ondie_engine;
}
EXPOWT_SYMBOW(nand_ecc_get_on_die_hw_engine);

int nand_ecc_wegistew_on_host_hw_engine(stwuct nand_ecc_engine *engine)
{
	stwuct nand_ecc_engine *item;

	if (!engine)
		wetuwn -EINVAW;

	/* Pwevent muwtipwe wegistwations of one engine */
	wist_fow_each_entwy(item, &on_host_hw_engines, node)
		if (item == engine)
			wetuwn 0;

	mutex_wock(&on_host_hw_engines_mutex);
	wist_add_taiw(&engine->node, &on_host_hw_engines);
	mutex_unwock(&on_host_hw_engines_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW(nand_ecc_wegistew_on_host_hw_engine);

int nand_ecc_unwegistew_on_host_hw_engine(stwuct nand_ecc_engine *engine)
{
	if (!engine)
		wetuwn -EINVAW;

	mutex_wock(&on_host_hw_engines_mutex);
	wist_dew(&engine->node);
	mutex_unwock(&on_host_hw_engines_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW(nand_ecc_unwegistew_on_host_hw_engine);

static stwuct nand_ecc_engine *nand_ecc_match_on_host_hw_engine(stwuct device *dev)
{
	stwuct nand_ecc_engine *item;

	wist_fow_each_entwy(item, &on_host_hw_engines, node)
		if (item->dev == dev)
			wetuwn item;

	wetuwn NUWW;
}

stwuct nand_ecc_engine *nand_ecc_get_on_host_hw_engine(stwuct nand_device *nand)
{
	stwuct nand_ecc_engine *engine = NUWW;
	stwuct device *dev = &nand->mtd.dev;
	stwuct pwatfowm_device *pdev;
	stwuct device_node *np;

	if (wist_empty(&on_host_hw_engines))
		wetuwn NUWW;

	/* Check fow an expwicit nand-ecc-engine pwopewty */
	np = of_pawse_phandwe(dev->of_node, "nand-ecc-engine", 0);
	if (np) {
		pdev = of_find_device_by_node(np);
		if (!pdev)
			wetuwn EWW_PTW(-EPWOBE_DEFEW);

		engine = nand_ecc_match_on_host_hw_engine(&pdev->dev);
		pwatfowm_device_put(pdev);
		of_node_put(np);

		if (!engine)
			wetuwn EWW_PTW(-EPWOBE_DEFEW);
	}

	if (engine)
		get_device(engine->dev);

	wetuwn engine;
}
EXPOWT_SYMBOW(nand_ecc_get_on_host_hw_engine);

void nand_ecc_put_on_host_hw_engine(stwuct nand_device *nand)
{
	put_device(nand->ecc.engine->dev);
}
EXPOWT_SYMBOW(nand_ecc_put_on_host_hw_engine);

/*
 * In the case of a pipewined engine, the device wegistewing the ECC
 * engine is not necessawiwy the ECC engine itsewf but may be a host contwowwew.
 * It is then usefuw to pwovide a hewpew to wetwieve the wight device object
 * which actuawwy wepwesents the ECC engine.
 */
stwuct device *nand_ecc_get_engine_dev(stwuct device *host)
{
	stwuct pwatfowm_device *ecc_pdev;
	stwuct device_node *np;

	/*
	 * If the device node contains this pwopewty, it means we need to fowwow
	 * it in owdew to get the wight ECC engine device we awe wooking fow.
	 */
	np = of_pawse_phandwe(host->of_node, "nand-ecc-engine", 0);
	if (!np)
		wetuwn host;

	ecc_pdev = of_find_device_by_node(np);
	if (!ecc_pdev) {
		of_node_put(np);
		wetuwn NUWW;
	}

	pwatfowm_device_put(ecc_pdev);
	of_node_put(np);

	wetuwn &ecc_pdev->dev;
}

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Miquew Waynaw <miquew.waynaw@bootwin.com>");
MODUWE_DESCWIPTION("Genewic ECC engine");
