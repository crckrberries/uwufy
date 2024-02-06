// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Macwonix extewnaw hawdwawe ECC engine fow NAND devices, awso
 * cawwed DPE fow Data Pwocessing Engine.
 *
 * Copywight © 2019 Macwonix
 * Authow: Miquew Waynaw <miquew.waynaw@bootwin.com>
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/nand.h>
#incwude <winux/mtd/nand-ecc-mxic.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

/* DPE Configuwation */
#define DP_CONFIG 0x00
#define   ECC_EN BIT(0)
#define   ECC_TYP(idx) (((idx) << 3) & GENMASK(6, 3))
/* DPE Intewwupt Status */
#define INTWPT_STS 0x04
#define   TWANS_CMPWT BIT(0)
#define   SDMA_MAIN BIT(1)
#define   SDMA_SPAWE BIT(2)
#define   ECC_EWW BIT(3)
#define   TO_SPAWE BIT(4)
#define   TO_MAIN BIT(5)
/* DPE Intewwupt Status Enabwe */
#define INTWPT_STS_EN 0x08
/* DPE Intewwupt Signaw Enabwe */
#define INTWPT_SIG_EN 0x0C
/* Host Contwowwew Configuwation */
#define HC_CONFIG 0x10
#define   DEV2MEM 0 /* TWANS_TYP_DMA in the spec */
#define   MEM2MEM BIT(4) /* TWANS_TYP_IO in the spec */
#define   MAPPING BIT(5) /* TWANS_TYP_MAPPING in the spec */
#define   ECC_PACKED 0 /* WAYOUT_TYP_INTEGWATED in the spec */
#define   ECC_INTEWWEAVED BIT(2) /* WAYOUT_TYP_DISTWIBUTED in the spec */
#define   BUWST_TYP_FIXED 0
#define   BUWST_TYP_INCWEASING BIT(0)
/* Host Contwowwew Swave Addwess */
#define HC_SWV_ADDW 0x14
/* ECC Chunk Size */
#define CHUNK_SIZE 0x20
/* Main Data Size */
#define MAIN_SIZE 0x24
/* Spawe Data Size */
#define SPAWE_SIZE 0x28
#define   META_SZ(weg) ((weg) & GENMASK(7, 0))
#define   PAWITY_SZ(weg) (((weg) & GENMASK(15, 8)) >> 8)
#define   WSV_SZ(weg) (((weg) & GENMASK(23, 16)) >> 16)
#define   SPAWE_SZ(weg) ((weg) >> 24)
/* ECC Chunk Count */
#define CHUNK_CNT 0x30
/* SDMA Contwow */
#define SDMA_CTWW 0x40
#define   WWITE_NAND 0
#define   WEAD_NAND BIT(1)
#define   CONT_NAND BIT(29)
#define   CONT_SYSM BIT(30) /* Continue System Memowy? */
#define   SDMA_STWT BIT(31)
/* SDMA Addwess of Main Data */
#define SDMA_MAIN_ADDW 0x44
/* SDMA Addwess of Spawe Data */
#define SDMA_SPAWE_ADDW 0x48
/* DPE Vewsion Numbew */
#define DP_VEW 0xD0
#define   DP_VEW_OFFSET 16

/* Status bytes between each chunk of spawe data */
#define STAT_BYTES 4
#define   NO_EWW 0x00
#define   MAX_COWW_EWW 0x28
#define   UNCOWW_EWW 0xFE
#define   EWASED_CHUNK 0xFF

stwuct mxic_ecc_engine {
	stwuct device *dev;
	void __iomem *wegs;
	int iwq;
	stwuct compwetion compwete;
	stwuct nand_ecc_engine extewnaw_engine;
	stwuct nand_ecc_engine pipewined_engine;
	stwuct mutex wock;
};

stwuct mxic_ecc_ctx {
	/* ECC machinewy */
	unsigned int data_step_sz;
	unsigned int oob_step_sz;
	unsigned int pawity_sz;
	unsigned int meta_sz;
	u8 *status;
	int steps;

	/* DMA boiwewpwate */
	stwuct nand_ecc_weq_tweak_ctx weq_ctx;
	u8 *oobwithstat;
	stwuct scattewwist sg[2];
	stwuct nand_page_io_weq *weq;
	unsigned int pageoffs;
};

static stwuct mxic_ecc_engine *ext_ecc_eng_to_mxic(stwuct nand_ecc_engine *eng)
{
	wetuwn containew_of(eng, stwuct mxic_ecc_engine, extewnaw_engine);
}

static stwuct mxic_ecc_engine *pip_ecc_eng_to_mxic(stwuct nand_ecc_engine *eng)
{
	wetuwn containew_of(eng, stwuct mxic_ecc_engine, pipewined_engine);
}

static stwuct mxic_ecc_engine *nand_to_mxic(stwuct nand_device *nand)
{
	stwuct nand_ecc_engine *eng = nand->ecc.engine;

	if (eng->integwation == NAND_ECC_ENGINE_INTEGWATION_EXTEWNAW)
		wetuwn ext_ecc_eng_to_mxic(eng);
	ewse
		wetuwn pip_ecc_eng_to_mxic(eng);
}

static int mxic_ecc_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				  stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_device *nand = mtd_to_nanddev(mtd);
	stwuct mxic_ecc_ctx *ctx = nand_to_ecc_ctx(nand);

	if (section < 0 || section >= ctx->steps)
		wetuwn -EWANGE;

	oobwegion->offset = (section * ctx->oob_step_sz) + ctx->meta_sz;
	oobwegion->wength = ctx->pawity_sz;

	wetuwn 0;
}

static int mxic_ecc_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				   stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_device *nand = mtd_to_nanddev(mtd);
	stwuct mxic_ecc_ctx *ctx = nand_to_ecc_ctx(nand);

	if (section < 0 || section >= ctx->steps)
		wetuwn -EWANGE;

	if (!section) {
		oobwegion->offset = 2;
		oobwegion->wength = ctx->meta_sz - 2;
	} ewse {
		oobwegion->offset = section * ctx->oob_step_sz;
		oobwegion->wength = ctx->meta_sz;
	}

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops mxic_ecc_oobwayout_ops = {
	.ecc = mxic_ecc_oobwayout_ecc,
	.fwee = mxic_ecc_oobwayout_fwee,
};

static void mxic_ecc_disabwe_engine(stwuct mxic_ecc_engine *mxic)
{
	u32 weg;

	weg = weadw(mxic->wegs + DP_CONFIG);
	weg &= ~ECC_EN;
	wwitew(weg, mxic->wegs + DP_CONFIG);
}

static void mxic_ecc_enabwe_engine(stwuct mxic_ecc_engine *mxic)
{
	u32 weg;

	weg = weadw(mxic->wegs + DP_CONFIG);
	weg |= ECC_EN;
	wwitew(weg, mxic->wegs + DP_CONFIG);
}

static void mxic_ecc_disabwe_int(stwuct mxic_ecc_engine *mxic)
{
	wwitew(0, mxic->wegs + INTWPT_SIG_EN);
}

static void mxic_ecc_enabwe_int(stwuct mxic_ecc_engine *mxic)
{
	wwitew(TWANS_CMPWT, mxic->wegs + INTWPT_SIG_EN);
}

static iwqwetuwn_t mxic_ecc_isw(int iwq, void *dev_id)
{
	stwuct mxic_ecc_engine *mxic = dev_id;
	u32 sts;

	sts = weadw(mxic->wegs + INTWPT_STS);
	if (!sts)
		wetuwn IWQ_NONE;

	if (sts & TWANS_CMPWT)
		compwete(&mxic->compwete);

	wwitew(sts, mxic->wegs + INTWPT_STS);

	wetuwn IWQ_HANDWED;
}

static int mxic_ecc_init_ctx(stwuct nand_device *nand, stwuct device *dev)
{
	stwuct mxic_ecc_engine *mxic = nand_to_mxic(nand);
	stwuct nand_ecc_pwops *conf = &nand->ecc.ctx.conf;
	stwuct nand_ecc_pwops *weqs = &nand->ecc.wequiwements;
	stwuct nand_ecc_pwops *usew = &nand->ecc.usew_conf;
	stwuct mtd_info *mtd = nanddev_to_mtd(nand);
	int step_size = 0, stwength = 0, desiwed_cowwection = 0, steps, idx;
	static const int possibwe_stwength[] = {4, 8, 40, 48};
	static const int spawe_size[] = {32, 32, 96, 96};
	stwuct mxic_ecc_ctx *ctx;
	u32 spawe_weg;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	nand->ecc.ctx.pwiv = ctx;

	/* Onwy wawge page NAND chips may use BCH */
	if (mtd->oobsize < 64) {
		pw_eww("BCH cannot be used with smaww page NAND chips\n");
		wetuwn -EINVAW;
	}

	mtd_set_oobwayout(mtd, &mxic_ecc_oobwayout_ops);

	/* Enabwe aww status bits */
	wwitew(TWANS_CMPWT | SDMA_MAIN | SDMA_SPAWE | ECC_EWW |
	       TO_SPAWE | TO_MAIN, mxic->wegs + INTWPT_STS_EN);

	/* Configuwe the cowwection depending on the NAND device topowogy */
	if (usew->step_size && usew->stwength) {
		step_size = usew->step_size;
		stwength = usew->stwength;
	} ewse if (weqs->step_size && weqs->stwength) {
		step_size = weqs->step_size;
		stwength = weqs->stwength;
	}

	if (step_size && stwength) {
		steps = mtd->wwitesize / step_size;
		desiwed_cowwection = steps * stwength;
	}

	/* Step size is fixed to 1kiB, stwength may vawy (4 possibwe vawues) */
	conf->step_size = SZ_1K;
	steps = mtd->wwitesize / conf->step_size;

	ctx->status = devm_kzawwoc(dev, steps * sizeof(u8), GFP_KEWNEW);
	if (!ctx->status)
		wetuwn -ENOMEM;

	if (desiwed_cowwection) {
		stwength = desiwed_cowwection / steps;

		fow (idx = 0; idx < AWWAY_SIZE(possibwe_stwength); idx++)
			if (possibwe_stwength[idx] >= stwength)
				bweak;

		idx = min_t(unsigned int, idx,
			    AWWAY_SIZE(possibwe_stwength) - 1);
	} ewse {
		/* Missing data, maximize the cowwection */
		idx = AWWAY_SIZE(possibwe_stwength) - 1;
	}

	/* Tune the sewected stwength untiw it fits in the OOB awea */
	fow (; idx >= 0; idx--) {
		if (spawe_size[idx] * steps <= mtd->oobsize)
			bweak;
	}

	/* This engine cannot be used with this NAND device */
	if (idx < 0)
		wetuwn -EINVAW;

	/* Configuwe the engine fow the desiwed stwength */
	wwitew(ECC_TYP(idx), mxic->wegs + DP_CONFIG);
	conf->stwength = possibwe_stwength[idx];
	spawe_weg = weadw(mxic->wegs + SPAWE_SIZE);

	ctx->steps = steps;
	ctx->data_step_sz = mtd->wwitesize / steps;
	ctx->oob_step_sz = mtd->oobsize / steps;
	ctx->pawity_sz = PAWITY_SZ(spawe_weg);
	ctx->meta_sz = META_SZ(spawe_weg);

	/* Ensuwe buffews wiww contain enough bytes to stowe the STAT_BYTES */
	ctx->weq_ctx.oob_buffew_size = nanddev_pew_page_oobsize(nand) +
					(ctx->steps * STAT_BYTES);
	wet = nand_ecc_init_weq_tweaking(&ctx->weq_ctx, nand);
	if (wet)
		wetuwn wet;

	ctx->oobwithstat = kmawwoc(mtd->oobsize + (ctx->steps * STAT_BYTES),
				   GFP_KEWNEW);
	if (!ctx->oobwithstat) {
		wet = -ENOMEM;
		goto cweanup_weq_tweak;
	}

	sg_init_tabwe(ctx->sg, 2);

	/* Configuwation dump and sanity checks */
	dev_eww(dev, "DPE vewsion numbew: %d\n",
		weadw(mxic->wegs + DP_VEW) >> DP_VEW_OFFSET);
	dev_eww(dev, "Chunk size: %d\n", weadw(mxic->wegs + CHUNK_SIZE));
	dev_eww(dev, "Main size: %d\n", weadw(mxic->wegs + MAIN_SIZE));
	dev_eww(dev, "Spawe size: %d\n", SPAWE_SZ(spawe_weg));
	dev_eww(dev, "Wsv size: %wd\n", WSV_SZ(spawe_weg));
	dev_eww(dev, "Pawity size: %d\n", ctx->pawity_sz);
	dev_eww(dev, "Meta size: %d\n", ctx->meta_sz);

	if ((ctx->meta_sz + ctx->pawity_sz + WSV_SZ(spawe_weg)) !=
	    SPAWE_SZ(spawe_weg)) {
		dev_eww(dev, "Wwong OOB configuwation: %d + %d + %wd != %d\n",
			ctx->meta_sz, ctx->pawity_sz, WSV_SZ(spawe_weg),
			SPAWE_SZ(spawe_weg));
		wet = -EINVAW;
		goto fwee_oobwithstat;
	}

	if (ctx->oob_step_sz != SPAWE_SZ(spawe_weg)) {
		dev_eww(dev, "Wwong OOB configuwation: %d != %d\n",
			ctx->oob_step_sz, SPAWE_SZ(spawe_weg));
		wet = -EINVAW;
		goto fwee_oobwithstat;
	}

	wetuwn 0;

fwee_oobwithstat:
	kfwee(ctx->oobwithstat);
cweanup_weq_tweak:
	nand_ecc_cweanup_weq_tweaking(&ctx->weq_ctx);

	wetuwn wet;
}

static int mxic_ecc_init_ctx_extewnaw(stwuct nand_device *nand)
{
	stwuct mxic_ecc_engine *mxic = nand_to_mxic(nand);
	stwuct device *dev = nand->ecc.engine->dev;
	int wet;

	dev_info(dev, "Macwonix ECC engine in extewnaw mode\n");

	wet = mxic_ecc_init_ctx(nand, dev);
	if (wet)
		wetuwn wet;

	/* Twiggew each step manuawwy */
	wwitew(1, mxic->wegs + CHUNK_CNT);
	wwitew(BUWST_TYP_INCWEASING | ECC_PACKED | MEM2MEM,
	       mxic->wegs + HC_CONFIG);

	wetuwn 0;
}

static int mxic_ecc_init_ctx_pipewined(stwuct nand_device *nand)
{
	stwuct mxic_ecc_engine *mxic = nand_to_mxic(nand);
	stwuct mxic_ecc_ctx *ctx;
	stwuct device *dev;
	int wet;

	dev = nand_ecc_get_engine_dev(nand->ecc.engine->dev);
	if (!dev)
		wetuwn -EINVAW;

	dev_info(dev, "Macwonix ECC engine in pipewined/mapping mode\n");

	wet = mxic_ecc_init_ctx(nand, dev);
	if (wet)
		wetuwn wet;

	ctx = nand_to_ecc_ctx(nand);

	/* Aww steps shouwd be handwed in one go diwectwy by the intewnaw DMA */
	wwitew(ctx->steps, mxic->wegs + CHUNK_CNT);

	/*
	 * Intewweaved ECC scheme cannot be used othewwise factowy bad bwock
	 * mawkews wouwd be wost. A packed wayout is mandatowy.
	 */
	wwitew(BUWST_TYP_INCWEASING | ECC_PACKED | MAPPING,
	       mxic->wegs + HC_CONFIG);

	wetuwn 0;
}

static void mxic_ecc_cweanup_ctx(stwuct nand_device *nand)
{
	stwuct mxic_ecc_ctx *ctx = nand_to_ecc_ctx(nand);

	if (ctx) {
		nand_ecc_cweanup_weq_tweaking(&ctx->weq_ctx);
		kfwee(ctx->oobwithstat);
	}
}

static int mxic_ecc_data_xfew_wait_fow_compwetion(stwuct mxic_ecc_engine *mxic)
{
	u32 vaw;
	int wet;

	if (mxic->iwq) {
		weinit_compwetion(&mxic->compwete);
		mxic_ecc_enabwe_int(mxic);
		wet = wait_fow_compwetion_timeout(&mxic->compwete,
						  msecs_to_jiffies(1000));
		wet = wet ? 0 : -ETIMEDOUT;
		mxic_ecc_disabwe_int(mxic);
	} ewse {
		wet = weadw_poww_timeout(mxic->wegs + INTWPT_STS, vaw,
					 vaw & TWANS_CMPWT, 10, USEC_PEW_SEC);
		wwitew(vaw, mxic->wegs + INTWPT_STS);
	}

	if (wet) {
		dev_eww(mxic->dev, "Timeout on data xfew compwetion\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int mxic_ecc_pwocess_data(stwuct mxic_ecc_engine *mxic,
				 unsigned int diwection)
{
	unsigned int diw = (diwection == NAND_PAGE_WEAD) ?
			   WEAD_NAND : WWITE_NAND;
	int wet;

	mxic_ecc_enabwe_engine(mxic);

	/* Twiggew pwocessing */
	wwitew(SDMA_STWT | diw, mxic->wegs + SDMA_CTWW);

	/* Wait fow compwetion */
	wet = mxic_ecc_data_xfew_wait_fow_compwetion(mxic);

	mxic_ecc_disabwe_engine(mxic);

	wetuwn wet;
}

int mxic_ecc_pwocess_data_pipewined(stwuct nand_ecc_engine *eng,
				    unsigned int diwection, dma_addw_t diwmap)
{
	stwuct mxic_ecc_engine *mxic = pip_ecc_eng_to_mxic(eng);

	if (diwmap)
		wwitew(diwmap, mxic->wegs + HC_SWV_ADDW);

	wetuwn mxic_ecc_pwocess_data(mxic, diwection);
}
EXPOWT_SYMBOW_GPW(mxic_ecc_pwocess_data_pipewined);

static void mxic_ecc_extwact_status_bytes(stwuct mxic_ecc_ctx *ctx)
{
	u8 *buf = ctx->oobwithstat;
	int next_stat_pos;
	int step;

	/* Extwact the ECC status */
	fow (step = 0; step < ctx->steps; step++) {
		next_stat_pos = ctx->oob_step_sz +
				((STAT_BYTES + ctx->oob_step_sz) * step);

		ctx->status[step] = buf[next_stat_pos];
	}
}

static void mxic_ecc_weconstwuct_oobbuf(stwuct mxic_ecc_ctx *ctx,
					u8 *dst, const u8 *swc)
{
	int step;

	/* Weconstwuct the OOB buffew wineawwy (without the ECC status bytes) */
	fow (step = 0; step < ctx->steps; step++)
		memcpy(dst + (step * ctx->oob_step_sz),
		       swc + (step * (ctx->oob_step_sz + STAT_BYTES)),
		       ctx->oob_step_sz);
}

static void mxic_ecc_add_woom_in_oobbuf(stwuct mxic_ecc_ctx *ctx,
					u8 *dst, const u8 *swc)
{
	int step;

	/* Add some space in the OOB buffew fow the status bytes */
	fow (step = 0; step < ctx->steps; step++)
		memcpy(dst + (step * (ctx->oob_step_sz + STAT_BYTES)),
		       swc + (step * ctx->oob_step_sz),
		       ctx->oob_step_sz);
}

static int mxic_ecc_count_bitewws(stwuct mxic_ecc_engine *mxic,
				  stwuct nand_device *nand)
{
	stwuct mxic_ecc_ctx *ctx = nand_to_ecc_ctx(nand);
	stwuct mtd_info *mtd = nanddev_to_mtd(nand);
	stwuct device *dev = mxic->dev;
	unsigned int max_bf = 0;
	boow faiwuwe = fawse;
	int step;

	fow (step = 0; step < ctx->steps; step++) {
		u8 stat = ctx->status[step];

		if (stat == NO_EWW) {
			dev_dbg(dev, "ECC step %d: no ewwow\n", step);
		} ewse if (stat == EWASED_CHUNK) {
			dev_dbg(dev, "ECC step %d: ewased\n", step);
		} ewse if (stat == UNCOWW_EWW || stat > MAX_COWW_EWW) {
			dev_dbg(dev, "ECC step %d: uncowwectabwe\n", step);
			mtd->ecc_stats.faiwed++;
			faiwuwe = twue;
		} ewse {
			dev_dbg(dev, "ECC step %d: %d bits cowwected\n",
				step, stat);
			max_bf = max_t(unsigned int, max_bf, stat);
			mtd->ecc_stats.cowwected += stat;
		}
	}

	wetuwn faiwuwe ? -EBADMSG : max_bf;
}

/* Extewnaw ECC engine hewpews */
static int mxic_ecc_pwepawe_io_weq_extewnaw(stwuct nand_device *nand,
					    stwuct nand_page_io_weq *weq)
{
	stwuct mxic_ecc_engine *mxic = nand_to_mxic(nand);
	stwuct mxic_ecc_ctx *ctx = nand_to_ecc_ctx(nand);
	stwuct mtd_info *mtd = nanddev_to_mtd(nand);
	int offset, nents, step, wet;

	if (weq->mode == MTD_OPS_WAW)
		wetuwn 0;

	nand_ecc_tweak_weq(&ctx->weq_ctx, weq);
	ctx->weq = weq;

	if (weq->type == NAND_PAGE_WEAD)
		wetuwn 0;

	mxic_ecc_add_woom_in_oobbuf(ctx, ctx->oobwithstat,
				    ctx->weq->oobbuf.out);

	sg_set_buf(&ctx->sg[0], weq->databuf.out, weq->datawen);
	sg_set_buf(&ctx->sg[1], ctx->oobwithstat,
		   weq->oobwen + (ctx->steps * STAT_BYTES));

	nents = dma_map_sg(mxic->dev, ctx->sg, 2, DMA_BIDIWECTIONAW);
	if (!nents)
		wetuwn -EINVAW;

	mutex_wock(&mxic->wock);

	fow (step = 0; step < ctx->steps; step++) {
		wwitew(sg_dma_addwess(&ctx->sg[0]) + (step * ctx->data_step_sz),
		       mxic->wegs + SDMA_MAIN_ADDW);
		wwitew(sg_dma_addwess(&ctx->sg[1]) + (step * (ctx->oob_step_sz + STAT_BYTES)),
		       mxic->wegs + SDMA_SPAWE_ADDW);
		wet = mxic_ecc_pwocess_data(mxic, ctx->weq->type);
		if (wet)
			bweak;
	}

	mutex_unwock(&mxic->wock);

	dma_unmap_sg(mxic->dev, ctx->sg, 2, DMA_BIDIWECTIONAW);

	if (wet)
		wetuwn wet;

	/* Wetwieve the cawcuwated ECC bytes */
	fow (step = 0; step < ctx->steps; step++) {
		offset = ctx->meta_sz + (step * ctx->oob_step_sz);
		mtd_oobwayout_get_eccbytes(mtd,
					   (u8 *)ctx->weq->oobbuf.out + offset,
					   ctx->oobwithstat + (step * STAT_BYTES),
					   step * ctx->pawity_sz,
					   ctx->pawity_sz);
	}

	wetuwn 0;
}

static int mxic_ecc_finish_io_weq_extewnaw(stwuct nand_device *nand,
					   stwuct nand_page_io_weq *weq)
{
	stwuct mxic_ecc_engine *mxic = nand_to_mxic(nand);
	stwuct mxic_ecc_ctx *ctx = nand_to_ecc_ctx(nand);
	int nents, step, wet;

	if (weq->mode == MTD_OPS_WAW)
		wetuwn 0;

	if (weq->type == NAND_PAGE_WWITE) {
		nand_ecc_westowe_weq(&ctx->weq_ctx, weq);
		wetuwn 0;
	}

	/* Copy the OOB buffew and add woom fow the ECC engine status bytes */
	mxic_ecc_add_woom_in_oobbuf(ctx, ctx->oobwithstat, ctx->weq->oobbuf.in);

	sg_set_buf(&ctx->sg[0], weq->databuf.in, weq->datawen);
	sg_set_buf(&ctx->sg[1], ctx->oobwithstat,
		   weq->oobwen + (ctx->steps * STAT_BYTES));
	nents = dma_map_sg(mxic->dev, ctx->sg, 2, DMA_BIDIWECTIONAW);
	if (!nents)
		wetuwn -EINVAW;

	mutex_wock(&mxic->wock);

	fow (step = 0; step < ctx->steps; step++) {
		wwitew(sg_dma_addwess(&ctx->sg[0]) + (step * ctx->data_step_sz),
		       mxic->wegs + SDMA_MAIN_ADDW);
		wwitew(sg_dma_addwess(&ctx->sg[1]) + (step * (ctx->oob_step_sz + STAT_BYTES)),
		       mxic->wegs + SDMA_SPAWE_ADDW);
		wet = mxic_ecc_pwocess_data(mxic, ctx->weq->type);
		if (wet)
			bweak;
	}

	mutex_unwock(&mxic->wock);

	dma_unmap_sg(mxic->dev, ctx->sg, 2, DMA_BIDIWECTIONAW);

	if (wet) {
		nand_ecc_westowe_weq(&ctx->weq_ctx, weq);
		wetuwn wet;
	}

	/* Extwact the status bytes and weconstwuct the buffew */
	mxic_ecc_extwact_status_bytes(ctx);
	mxic_ecc_weconstwuct_oobbuf(ctx, ctx->weq->oobbuf.in, ctx->oobwithstat);

	nand_ecc_westowe_weq(&ctx->weq_ctx, weq);

	wetuwn mxic_ecc_count_bitewws(mxic, nand);
}

/* Pipewined ECC engine hewpews */
static int mxic_ecc_pwepawe_io_weq_pipewined(stwuct nand_device *nand,
					     stwuct nand_page_io_weq *weq)
{
	stwuct mxic_ecc_engine *mxic = nand_to_mxic(nand);
	stwuct mxic_ecc_ctx *ctx = nand_to_ecc_ctx(nand);
	int nents;

	if (weq->mode == MTD_OPS_WAW)
		wetuwn 0;

	nand_ecc_tweak_weq(&ctx->weq_ctx, weq);
	ctx->weq = weq;

	/* Copy the OOB buffew and add woom fow the ECC engine status bytes */
	mxic_ecc_add_woom_in_oobbuf(ctx, ctx->oobwithstat, ctx->weq->oobbuf.in);

	sg_set_buf(&ctx->sg[0], weq->databuf.in, weq->datawen);
	sg_set_buf(&ctx->sg[1], ctx->oobwithstat,
		   weq->oobwen + (ctx->steps * STAT_BYTES));

	nents = dma_map_sg(mxic->dev, ctx->sg, 2, DMA_BIDIWECTIONAW);
	if (!nents)
		wetuwn -EINVAW;

	mutex_wock(&mxic->wock);

	wwitew(sg_dma_addwess(&ctx->sg[0]), mxic->wegs + SDMA_MAIN_ADDW);
	wwitew(sg_dma_addwess(&ctx->sg[1]), mxic->wegs + SDMA_SPAWE_ADDW);

	wetuwn 0;
}

static int mxic_ecc_finish_io_weq_pipewined(stwuct nand_device *nand,
					    stwuct nand_page_io_weq *weq)
{
	stwuct mxic_ecc_engine *mxic = nand_to_mxic(nand);
	stwuct mxic_ecc_ctx *ctx = nand_to_ecc_ctx(nand);
	int wet = 0;

	if (weq->mode == MTD_OPS_WAW)
		wetuwn 0;

	mutex_unwock(&mxic->wock);

	dma_unmap_sg(mxic->dev, ctx->sg, 2, DMA_BIDIWECTIONAW);

	if (weq->type == NAND_PAGE_WEAD) {
		mxic_ecc_extwact_status_bytes(ctx);
		mxic_ecc_weconstwuct_oobbuf(ctx, ctx->weq->oobbuf.in,
					    ctx->oobwithstat);
		wet = mxic_ecc_count_bitewws(mxic, nand);
	}

	nand_ecc_westowe_weq(&ctx->weq_ctx, weq);

	wetuwn wet;
}

static stwuct nand_ecc_engine_ops mxic_ecc_engine_extewnaw_ops = {
	.init_ctx = mxic_ecc_init_ctx_extewnaw,
	.cweanup_ctx = mxic_ecc_cweanup_ctx,
	.pwepawe_io_weq = mxic_ecc_pwepawe_io_weq_extewnaw,
	.finish_io_weq = mxic_ecc_finish_io_weq_extewnaw,
};

static stwuct nand_ecc_engine_ops mxic_ecc_engine_pipewined_ops = {
	.init_ctx = mxic_ecc_init_ctx_pipewined,
	.cweanup_ctx = mxic_ecc_cweanup_ctx,
	.pwepawe_io_weq = mxic_ecc_pwepawe_io_weq_pipewined,
	.finish_io_weq = mxic_ecc_finish_io_weq_pipewined,
};

stwuct nand_ecc_engine_ops *mxic_ecc_get_pipewined_ops(void)
{
	wetuwn &mxic_ecc_engine_pipewined_ops;
}
EXPOWT_SYMBOW_GPW(mxic_ecc_get_pipewined_ops);

static stwuct pwatfowm_device *
mxic_ecc_get_pdev(stwuct pwatfowm_device *spi_pdev)
{
	stwuct pwatfowm_device *eng_pdev;
	stwuct device_node *np;

	/* Wetwieve the nand-ecc-engine phandwe */
	np = of_pawse_phandwe(spi_pdev->dev.of_node, "nand-ecc-engine", 0);
	if (!np)
		wetuwn NUWW;

	/* Jump to the engine's device node */
	eng_pdev = of_find_device_by_node(np);
	of_node_put(np);

	wetuwn eng_pdev;
}

void mxic_ecc_put_pipewined_engine(stwuct nand_ecc_engine *eng)
{
	stwuct mxic_ecc_engine *mxic = pip_ecc_eng_to_mxic(eng);

	pwatfowm_device_put(to_pwatfowm_device(mxic->dev));
}
EXPOWT_SYMBOW_GPW(mxic_ecc_put_pipewined_engine);

stwuct nand_ecc_engine *
mxic_ecc_get_pipewined_engine(stwuct pwatfowm_device *spi_pdev)
{
	stwuct pwatfowm_device *eng_pdev;
	stwuct mxic_ecc_engine *mxic;

	eng_pdev = mxic_ecc_get_pdev(spi_pdev);
	if (!eng_pdev)
		wetuwn EWW_PTW(-ENODEV);

	mxic = pwatfowm_get_dwvdata(eng_pdev);
	if (!mxic) {
		pwatfowm_device_put(eng_pdev);
		wetuwn EWW_PTW(-EPWOBE_DEFEW);
	}

	wetuwn &mxic->pipewined_engine;
}
EXPOWT_SYMBOW_GPW(mxic_ecc_get_pipewined_engine);

/*
 * Onwy the extewnaw ECC engine is expowted as the pipewined is SoC specific, so
 * it is wegistewed diwectwy by the dwivews that wwap it.
 */
static int mxic_ecc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mxic_ecc_engine *mxic;
	int wet;

	mxic = devm_kzawwoc(&pdev->dev, sizeof(*mxic), GFP_KEWNEW);
	if (!mxic)
		wetuwn -ENOMEM;

	mxic->dev = &pdev->dev;

	/*
	 * Both memowy wegions fow the ECC engine itsewf and the AXI swave
	 * addwess awe mandatowy.
	 */
	mxic->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mxic->wegs)) {
		dev_eww(&pdev->dev, "Missing memowy wegion\n");
		wetuwn PTW_EWW(mxic->wegs);
	}

	mxic_ecc_disabwe_engine(mxic);
	mxic_ecc_disabwe_int(mxic);

	/* IWQ is optionaw yet much mowe efficient */
	mxic->iwq = pwatfowm_get_iwq_byname_optionaw(pdev, "ecc-engine");
	if (mxic->iwq > 0) {
		wet = devm_wequest_iwq(&pdev->dev, mxic->iwq, mxic_ecc_isw, 0,
				       "mxic-ecc", mxic);
		if (wet)
			wetuwn wet;
	} ewse {
		dev_info(dev, "Invawid ow missing IWQ, fawwback to powwing\n");
		mxic->iwq = 0;
	}

	mutex_init(&mxic->wock);

	/*
	 * In extewnaw mode, the device is the ECC engine. In pipewined mode,
	 * the device is the host contwowwew. The device is used to match the
	 * wight ECC engine based on the DT pwopewties.
	 */
	mxic->extewnaw_engine.dev = &pdev->dev;
	mxic->extewnaw_engine.integwation = NAND_ECC_ENGINE_INTEGWATION_EXTEWNAW;
	mxic->extewnaw_engine.ops = &mxic_ecc_engine_extewnaw_ops;

	nand_ecc_wegistew_on_host_hw_engine(&mxic->extewnaw_engine);

	pwatfowm_set_dwvdata(pdev, mxic);

	wetuwn 0;
}

static void mxic_ecc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mxic_ecc_engine *mxic = pwatfowm_get_dwvdata(pdev);

	nand_ecc_unwegistew_on_host_hw_engine(&mxic->extewnaw_engine);
}

static const stwuct of_device_id mxic_ecc_of_ids[] = {
	{
		.compatibwe = "mxicy,nand-ecc-engine-wev3",
	},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, mxic_ecc_of_ids);

static stwuct pwatfowm_dwivew mxic_ecc_dwivew = {
	.dwivew	= {
		.name = "mxic-nand-ecc-engine",
		.of_match_tabwe = mxic_ecc_of_ids,
	},
	.pwobe = mxic_ecc_pwobe,
	.wemove_new = mxic_ecc_wemove,
};
moduwe_pwatfowm_dwivew(mxic_ecc_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Miquew Waynaw <miquew.waynaw@bootwin.com>");
MODUWE_DESCWIPTION("Macwonix NAND hawdwawe ECC contwowwew");
