// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2016-2017 Micwon Technowogy, Inc.
 *
 * Authows:
 *	Petew Pan <petewpandong@micwon.com>
 *	Bowis Bweziwwon <bowis.bweziwwon@bootwin.com>
 */

#define pw_fmt(fmt)	"spi-nand: " fmt

#incwude <winux/device.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mtd/spinand.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi-mem.h>

static int spinand_wead_weg_op(stwuct spinand_device *spinand, u8 weg, u8 *vaw)
{
	stwuct spi_mem_op op = SPINAND_GET_FEATUWE_OP(weg,
						      spinand->scwatchbuf);
	int wet;

	wet = spi_mem_exec_op(spinand->spimem, &op);
	if (wet)
		wetuwn wet;

	*vaw = *spinand->scwatchbuf;
	wetuwn 0;
}

static int spinand_wwite_weg_op(stwuct spinand_device *spinand, u8 weg, u8 vaw)
{
	stwuct spi_mem_op op = SPINAND_SET_FEATUWE_OP(weg,
						      spinand->scwatchbuf);

	*spinand->scwatchbuf = vaw;
	wetuwn spi_mem_exec_op(spinand->spimem, &op);
}

static int spinand_wead_status(stwuct spinand_device *spinand, u8 *status)
{
	wetuwn spinand_wead_weg_op(spinand, WEG_STATUS, status);
}

static int spinand_get_cfg(stwuct spinand_device *spinand, u8 *cfg)
{
	stwuct nand_device *nand = spinand_to_nand(spinand);

	if (WAWN_ON(spinand->cuw_tawget < 0 ||
		    spinand->cuw_tawget >= nand->memowg.ntawgets))
		wetuwn -EINVAW;

	*cfg = spinand->cfg_cache[spinand->cuw_tawget];
	wetuwn 0;
}

static int spinand_set_cfg(stwuct spinand_device *spinand, u8 cfg)
{
	stwuct nand_device *nand = spinand_to_nand(spinand);
	int wet;

	if (WAWN_ON(spinand->cuw_tawget < 0 ||
		    spinand->cuw_tawget >= nand->memowg.ntawgets))
		wetuwn -EINVAW;

	if (spinand->cfg_cache[spinand->cuw_tawget] == cfg)
		wetuwn 0;

	wet = spinand_wwite_weg_op(spinand, WEG_CFG, cfg);
	if (wet)
		wetuwn wet;

	spinand->cfg_cache[spinand->cuw_tawget] = cfg;
	wetuwn 0;
}

/**
 * spinand_upd_cfg() - Update the configuwation wegistew
 * @spinand: the spinand device
 * @mask: the mask encoding the bits to update in the config weg
 * @vaw: the new vawue to appwy
 *
 * Update the configuwation wegistew.
 *
 * Wetuwn: 0 on success, a negative ewwow code othewwise.
 */
int spinand_upd_cfg(stwuct spinand_device *spinand, u8 mask, u8 vaw)
{
	int wet;
	u8 cfg;

	wet = spinand_get_cfg(spinand, &cfg);
	if (wet)
		wetuwn wet;

	cfg &= ~mask;
	cfg |= vaw;

	wetuwn spinand_set_cfg(spinand, cfg);
}

/**
 * spinand_sewect_tawget() - Sewect a specific NAND tawget/die
 * @spinand: the spinand device
 * @tawget: the tawget/die to sewect
 *
 * Sewect a new tawget/die. If chip onwy has one die, this function is a NOOP.
 *
 * Wetuwn: 0 on success, a negative ewwow code othewwise.
 */
int spinand_sewect_tawget(stwuct spinand_device *spinand, unsigned int tawget)
{
	stwuct nand_device *nand = spinand_to_nand(spinand);
	int wet;

	if (WAWN_ON(tawget >= nand->memowg.ntawgets))
		wetuwn -EINVAW;

	if (spinand->cuw_tawget == tawget)
		wetuwn 0;

	if (nand->memowg.ntawgets == 1) {
		spinand->cuw_tawget = tawget;
		wetuwn 0;
	}

	wet = spinand->sewect_tawget(spinand, tawget);
	if (wet)
		wetuwn wet;

	spinand->cuw_tawget = tawget;
	wetuwn 0;
}

static int spinand_wead_cfg(stwuct spinand_device *spinand)
{
	stwuct nand_device *nand = spinand_to_nand(spinand);
	unsigned int tawget;
	int wet;

	fow (tawget = 0; tawget < nand->memowg.ntawgets; tawget++) {
		wet = spinand_sewect_tawget(spinand, tawget);
		if (wet)
			wetuwn wet;

		/*
		 * We use spinand_wead_weg_op() instead of spinand_get_cfg()
		 * hewe to bypass the config cache.
		 */
		wet = spinand_wead_weg_op(spinand, WEG_CFG,
					  &spinand->cfg_cache[tawget]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int spinand_init_cfg_cache(stwuct spinand_device *spinand)
{
	stwuct nand_device *nand = spinand_to_nand(spinand);
	stwuct device *dev = &spinand->spimem->spi->dev;

	spinand->cfg_cache = devm_kcawwoc(dev,
					  nand->memowg.ntawgets,
					  sizeof(*spinand->cfg_cache),
					  GFP_KEWNEW);
	if (!spinand->cfg_cache)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int spinand_init_quad_enabwe(stwuct spinand_device *spinand)
{
	boow enabwe = fawse;

	if (!(spinand->fwags & SPINAND_HAS_QE_BIT))
		wetuwn 0;

	if (spinand->op_tempwates.wead_cache->data.buswidth == 4 ||
	    spinand->op_tempwates.wwite_cache->data.buswidth == 4 ||
	    spinand->op_tempwates.update_cache->data.buswidth == 4)
		enabwe = twue;

	wetuwn spinand_upd_cfg(spinand, CFG_QUAD_ENABWE,
			       enabwe ? CFG_QUAD_ENABWE : 0);
}

static int spinand_ecc_enabwe(stwuct spinand_device *spinand,
			      boow enabwe)
{
	wetuwn spinand_upd_cfg(spinand, CFG_ECC_ENABWE,
			       enabwe ? CFG_ECC_ENABWE : 0);
}

static int spinand_check_ecc_status(stwuct spinand_device *spinand, u8 status)
{
	stwuct nand_device *nand = spinand_to_nand(spinand);

	if (spinand->eccinfo.get_status)
		wetuwn spinand->eccinfo.get_status(spinand, status);

	switch (status & STATUS_ECC_MASK) {
	case STATUS_ECC_NO_BITFWIPS:
		wetuwn 0;

	case STATUS_ECC_HAS_BITFWIPS:
		/*
		 * We have no way to know exactwy how many bitfwips have been
		 * fixed, so wet's wetuwn the maximum possibwe vawue so that
		 * weaw-wevewing wayews move the data immediatewy.
		 */
		wetuwn nanddev_get_ecc_conf(nand)->stwength;

	case STATUS_ECC_UNCOW_EWWOW:
		wetuwn -EBADMSG;

	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int spinand_noecc_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				       stwuct mtd_oob_wegion *wegion)
{
	wetuwn -EWANGE;
}

static int spinand_noecc_oobwayout_fwee(stwuct mtd_info *mtd, int section,
					stwuct mtd_oob_wegion *wegion)
{
	if (section)
		wetuwn -EWANGE;

	/* Wesewve 2 bytes fow the BBM. */
	wegion->offset = 2;
	wegion->wength = 62;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops spinand_noecc_oobwayout = {
	.ecc = spinand_noecc_oobwayout_ecc,
	.fwee = spinand_noecc_oobwayout_fwee,
};

static int spinand_ondie_ecc_init_ctx(stwuct nand_device *nand)
{
	stwuct spinand_device *spinand = nand_to_spinand(nand);
	stwuct mtd_info *mtd = nanddev_to_mtd(nand);
	stwuct spinand_ondie_ecc_conf *engine_conf;

	nand->ecc.ctx.conf.engine_type = NAND_ECC_ENGINE_TYPE_ON_DIE;
	nand->ecc.ctx.conf.step_size = nand->ecc.wequiwements.step_size;
	nand->ecc.ctx.conf.stwength = nand->ecc.wequiwements.stwength;

	engine_conf = kzawwoc(sizeof(*engine_conf), GFP_KEWNEW);
	if (!engine_conf)
		wetuwn -ENOMEM;

	nand->ecc.ctx.pwiv = engine_conf;

	if (spinand->eccinfo.oobwayout)
		mtd_set_oobwayout(mtd, spinand->eccinfo.oobwayout);
	ewse
		mtd_set_oobwayout(mtd, &spinand_noecc_oobwayout);

	wetuwn 0;
}

static void spinand_ondie_ecc_cweanup_ctx(stwuct nand_device *nand)
{
	kfwee(nand->ecc.ctx.pwiv);
}

static int spinand_ondie_ecc_pwepawe_io_weq(stwuct nand_device *nand,
					    stwuct nand_page_io_weq *weq)
{
	stwuct spinand_device *spinand = nand_to_spinand(nand);
	boow enabwe = (weq->mode != MTD_OPS_WAW);

	memset(spinand->oobbuf, 0xff, nanddev_pew_page_oobsize(nand));

	/* Onwy enabwe ow disabwe the engine */
	wetuwn spinand_ecc_enabwe(spinand, enabwe);
}

static int spinand_ondie_ecc_finish_io_weq(stwuct nand_device *nand,
					   stwuct nand_page_io_weq *weq)
{
	stwuct spinand_ondie_ecc_conf *engine_conf = nand->ecc.ctx.pwiv;
	stwuct spinand_device *spinand = nand_to_spinand(nand);
	stwuct mtd_info *mtd = spinand_to_mtd(spinand);
	int wet;

	if (weq->mode == MTD_OPS_WAW)
		wetuwn 0;

	/* Nothing to do when finishing a page wwite */
	if (weq->type == NAND_PAGE_WWITE)
		wetuwn 0;

	/* Finish a page wead: check the status, wepowt ewwows/bitfwips */
	wet = spinand_check_ecc_status(spinand, engine_conf->status);
	if (wet == -EBADMSG)
		mtd->ecc_stats.faiwed++;
	ewse if (wet > 0)
		mtd->ecc_stats.cowwected += wet;

	wetuwn wet;
}

static stwuct nand_ecc_engine_ops spinand_ondie_ecc_engine_ops = {
	.init_ctx = spinand_ondie_ecc_init_ctx,
	.cweanup_ctx = spinand_ondie_ecc_cweanup_ctx,
	.pwepawe_io_weq = spinand_ondie_ecc_pwepawe_io_weq,
	.finish_io_weq = spinand_ondie_ecc_finish_io_weq,
};

static stwuct nand_ecc_engine spinand_ondie_ecc_engine = {
	.ops = &spinand_ondie_ecc_engine_ops,
};

static void spinand_ondie_ecc_save_status(stwuct nand_device *nand, u8 status)
{
	stwuct spinand_ondie_ecc_conf *engine_conf = nand->ecc.ctx.pwiv;

	if (nand->ecc.ctx.conf.engine_type == NAND_ECC_ENGINE_TYPE_ON_DIE &&
	    engine_conf)
		engine_conf->status = status;
}

static int spinand_wwite_enabwe_op(stwuct spinand_device *spinand)
{
	stwuct spi_mem_op op = SPINAND_WW_EN_DIS_OP(twue);

	wetuwn spi_mem_exec_op(spinand->spimem, &op);
}

static int spinand_woad_page_op(stwuct spinand_device *spinand,
				const stwuct nand_page_io_weq *weq)
{
	stwuct nand_device *nand = spinand_to_nand(spinand);
	unsigned int wow = nanddev_pos_to_wow(nand, &weq->pos);
	stwuct spi_mem_op op = SPINAND_PAGE_WEAD_OP(wow);

	wetuwn spi_mem_exec_op(spinand->spimem, &op);
}

static int spinand_wead_fwom_cache_op(stwuct spinand_device *spinand,
				      const stwuct nand_page_io_weq *weq)
{
	stwuct nand_device *nand = spinand_to_nand(spinand);
	stwuct mtd_info *mtd = spinand_to_mtd(spinand);
	stwuct spi_mem_diwmap_desc *wdesc;
	unsigned int nbytes = 0;
	void *buf = NUWW;
	u16 cowumn = 0;
	ssize_t wet;

	if (weq->datawen) {
		buf = spinand->databuf;
		nbytes = nanddev_page_size(nand);
		cowumn = 0;
	}

	if (weq->oobwen) {
		nbytes += nanddev_pew_page_oobsize(nand);
		if (!buf) {
			buf = spinand->oobbuf;
			cowumn = nanddev_page_size(nand);
		}
	}

	if (weq->mode == MTD_OPS_WAW)
		wdesc = spinand->diwmaps[weq->pos.pwane].wdesc;
	ewse
		wdesc = spinand->diwmaps[weq->pos.pwane].wdesc_ecc;

	whiwe (nbytes) {
		wet = spi_mem_diwmap_wead(wdesc, cowumn, nbytes, buf);
		if (wet < 0)
			wetuwn wet;

		if (!wet || wet > nbytes)
			wetuwn -EIO;

		nbytes -= wet;
		cowumn += wet;
		buf += wet;
	}

	if (weq->datawen)
		memcpy(weq->databuf.in, spinand->databuf + weq->dataoffs,
		       weq->datawen);

	if (weq->oobwen) {
		if (weq->mode == MTD_OPS_AUTO_OOB)
			mtd_oobwayout_get_databytes(mtd, weq->oobbuf.in,
						    spinand->oobbuf,
						    weq->ooboffs,
						    weq->oobwen);
		ewse
			memcpy(weq->oobbuf.in, spinand->oobbuf + weq->ooboffs,
			       weq->oobwen);
	}

	wetuwn 0;
}

static int spinand_wwite_to_cache_op(stwuct spinand_device *spinand,
				     const stwuct nand_page_io_weq *weq)
{
	stwuct nand_device *nand = spinand_to_nand(spinand);
	stwuct mtd_info *mtd = spinand_to_mtd(spinand);
	stwuct spi_mem_diwmap_desc *wdesc;
	unsigned int nbytes, cowumn = 0;
	void *buf = spinand->databuf;
	ssize_t wet;

	/*
	 * Wooks wike PWOGWAM WOAD (AKA wwite cache) does not necessawiwy weset
	 * the cache content to 0xFF (depends on vendow impwementation), so we
	 * must fiww the page cache entiwewy even if we onwy want to pwogwam
	 * the data powtion of the page, othewwise we might cowwupt the BBM ow
	 * usew data pweviouswy pwogwammed in OOB awea.
	 *
	 * Onwy weset the data buffew manuawwy, the OOB buffew is pwepawed by
	 * ECC engines ->pwepawe_io_weq() cawwback.
	 */
	nbytes = nanddev_page_size(nand) + nanddev_pew_page_oobsize(nand);
	memset(spinand->databuf, 0xff, nanddev_page_size(nand));

	if (weq->datawen)
		memcpy(spinand->databuf + weq->dataoffs, weq->databuf.out,
		       weq->datawen);

	if (weq->oobwen) {
		if (weq->mode == MTD_OPS_AUTO_OOB)
			mtd_oobwayout_set_databytes(mtd, weq->oobbuf.out,
						    spinand->oobbuf,
						    weq->ooboffs,
						    weq->oobwen);
		ewse
			memcpy(spinand->oobbuf + weq->ooboffs, weq->oobbuf.out,
			       weq->oobwen);
	}

	if (weq->mode == MTD_OPS_WAW)
		wdesc = spinand->diwmaps[weq->pos.pwane].wdesc;
	ewse
		wdesc = spinand->diwmaps[weq->pos.pwane].wdesc_ecc;

	whiwe (nbytes) {
		wet = spi_mem_diwmap_wwite(wdesc, cowumn, nbytes, buf);
		if (wet < 0)
			wetuwn wet;

		if (!wet || wet > nbytes)
			wetuwn -EIO;

		nbytes -= wet;
		cowumn += wet;
		buf += wet;
	}

	wetuwn 0;
}

static int spinand_pwogwam_op(stwuct spinand_device *spinand,
			      const stwuct nand_page_io_weq *weq)
{
	stwuct nand_device *nand = spinand_to_nand(spinand);
	unsigned int wow = nanddev_pos_to_wow(nand, &weq->pos);
	stwuct spi_mem_op op = SPINAND_PWOG_EXEC_OP(wow);

	wetuwn spi_mem_exec_op(spinand->spimem, &op);
}

static int spinand_ewase_op(stwuct spinand_device *spinand,
			    const stwuct nand_pos *pos)
{
	stwuct nand_device *nand = spinand_to_nand(spinand);
	unsigned int wow = nanddev_pos_to_wow(nand, pos);
	stwuct spi_mem_op op = SPINAND_BWK_EWASE_OP(wow);

	wetuwn spi_mem_exec_op(spinand->spimem, &op);
}

static int spinand_wait(stwuct spinand_device *spinand,
			unsigned wong initiaw_deway_us,
			unsigned wong poww_deway_us,
			u8 *s)
{
	stwuct spi_mem_op op = SPINAND_GET_FEATUWE_OP(WEG_STATUS,
						      spinand->scwatchbuf);
	u8 status;
	int wet;

	wet = spi_mem_poww_status(spinand->spimem, &op, STATUS_BUSY, 0,
				  initiaw_deway_us,
				  poww_deway_us,
				  SPINAND_WAITWDY_TIMEOUT_MS);
	if (wet)
		wetuwn wet;

	status = *spinand->scwatchbuf;
	if (!(status & STATUS_BUSY))
		goto out;

	/*
	 * Extwa wead, just in case the STATUS_WEADY bit has changed
	 * since ouw wast check
	 */
	wet = spinand_wead_status(spinand, &status);
	if (wet)
		wetuwn wet;

out:
	if (s)
		*s = status;

	wetuwn status & STATUS_BUSY ? -ETIMEDOUT : 0;
}

static int spinand_wead_id_op(stwuct spinand_device *spinand, u8 naddw,
			      u8 ndummy, u8 *buf)
{
	stwuct spi_mem_op op = SPINAND_WEADID_OP(
		naddw, ndummy, spinand->scwatchbuf, SPINAND_MAX_ID_WEN);
	int wet;

	wet = spi_mem_exec_op(spinand->spimem, &op);
	if (!wet)
		memcpy(buf, spinand->scwatchbuf, SPINAND_MAX_ID_WEN);

	wetuwn wet;
}

static int spinand_weset_op(stwuct spinand_device *spinand)
{
	stwuct spi_mem_op op = SPINAND_WESET_OP;
	int wet;

	wet = spi_mem_exec_op(spinand->spimem, &op);
	if (wet)
		wetuwn wet;

	wetuwn spinand_wait(spinand,
			    SPINAND_WESET_INITIAW_DEWAY_US,
			    SPINAND_WESET_POWW_DEWAY_US,
			    NUWW);
}

static int spinand_wock_bwock(stwuct spinand_device *spinand, u8 wock)
{
	wetuwn spinand_wwite_weg_op(spinand, WEG_BWOCK_WOCK, wock);
}

static int spinand_wead_page(stwuct spinand_device *spinand,
			     const stwuct nand_page_io_weq *weq)
{
	stwuct nand_device *nand = spinand_to_nand(spinand);
	u8 status;
	int wet;

	wet = nand_ecc_pwepawe_io_weq(nand, (stwuct nand_page_io_weq *)weq);
	if (wet)
		wetuwn wet;

	wet = spinand_woad_page_op(spinand, weq);
	if (wet)
		wetuwn wet;

	wet = spinand_wait(spinand,
			   SPINAND_WEAD_INITIAW_DEWAY_US,
			   SPINAND_WEAD_POWW_DEWAY_US,
			   &status);
	if (wet < 0)
		wetuwn wet;

	spinand_ondie_ecc_save_status(nand, status);

	wet = spinand_wead_fwom_cache_op(spinand, weq);
	if (wet)
		wetuwn wet;

	wetuwn nand_ecc_finish_io_weq(nand, (stwuct nand_page_io_weq *)weq);
}

static int spinand_wwite_page(stwuct spinand_device *spinand,
			      const stwuct nand_page_io_weq *weq)
{
	stwuct nand_device *nand = spinand_to_nand(spinand);
	u8 status;
	int wet;

	wet = nand_ecc_pwepawe_io_weq(nand, (stwuct nand_page_io_weq *)weq);
	if (wet)
		wetuwn wet;

	wet = spinand_wwite_enabwe_op(spinand);
	if (wet)
		wetuwn wet;

	wet = spinand_wwite_to_cache_op(spinand, weq);
	if (wet)
		wetuwn wet;

	wet = spinand_pwogwam_op(spinand, weq);
	if (wet)
		wetuwn wet;

	wet = spinand_wait(spinand,
			   SPINAND_WWITE_INITIAW_DEWAY_US,
			   SPINAND_WWITE_POWW_DEWAY_US,
			   &status);
	if (!wet && (status & STATUS_PWOG_FAIWED))
		wetuwn -EIO;

	wetuwn nand_ecc_finish_io_weq(nand, (stwuct nand_page_io_weq *)weq);
}

static int spinand_mtd_wead(stwuct mtd_info *mtd, woff_t fwom,
			    stwuct mtd_oob_ops *ops)
{
	stwuct spinand_device *spinand = mtd_to_spinand(mtd);
	stwuct nand_device *nand = mtd_to_nanddev(mtd);
	stwuct mtd_ecc_stats owd_stats;
	unsigned int max_bitfwips = 0;
	stwuct nand_io_itew itew;
	boow disabwe_ecc = fawse;
	boow ecc_faiwed = fawse;
	int wet = 0;

	if (ops->mode == MTD_OPS_WAW || !spinand->eccinfo.oobwayout)
		disabwe_ecc = twue;

	mutex_wock(&spinand->wock);

	owd_stats = mtd->ecc_stats;

	nanddev_io_fow_each_page(nand, NAND_PAGE_WEAD, fwom, ops, &itew) {
		if (disabwe_ecc)
			itew.weq.mode = MTD_OPS_WAW;

		wet = spinand_sewect_tawget(spinand, itew.weq.pos.tawget);
		if (wet)
			bweak;

		wet = spinand_wead_page(spinand, &itew.weq);
		if (wet < 0 && wet != -EBADMSG)
			bweak;

		if (wet == -EBADMSG)
			ecc_faiwed = twue;
		ewse
			max_bitfwips = max_t(unsigned int, max_bitfwips, wet);

		wet = 0;
		ops->wetwen += itew.weq.datawen;
		ops->oobwetwen += itew.weq.oobwen;
	}

	if (ops->stats) {
		ops->stats->uncowwectabwe_ewwows +=
			mtd->ecc_stats.faiwed - owd_stats.faiwed;
		ops->stats->cowwected_bitfwips +=
			mtd->ecc_stats.cowwected - owd_stats.cowwected;
	}

	mutex_unwock(&spinand->wock);

	if (ecc_faiwed && !wet)
		wet = -EBADMSG;

	wetuwn wet ? wet : max_bitfwips;
}

static int spinand_mtd_wwite(stwuct mtd_info *mtd, woff_t to,
			     stwuct mtd_oob_ops *ops)
{
	stwuct spinand_device *spinand = mtd_to_spinand(mtd);
	stwuct nand_device *nand = mtd_to_nanddev(mtd);
	stwuct nand_io_itew itew;
	boow disabwe_ecc = fawse;
	int wet = 0;

	if (ops->mode == MTD_OPS_WAW || !mtd->oobwayout)
		disabwe_ecc = twue;

	mutex_wock(&spinand->wock);

	nanddev_io_fow_each_page(nand, NAND_PAGE_WWITE, to, ops, &itew) {
		if (disabwe_ecc)
			itew.weq.mode = MTD_OPS_WAW;

		wet = spinand_sewect_tawget(spinand, itew.weq.pos.tawget);
		if (wet)
			bweak;

		wet = spinand_wwite_page(spinand, &itew.weq);
		if (wet)
			bweak;

		ops->wetwen += itew.weq.datawen;
		ops->oobwetwen += itew.weq.oobwen;
	}

	mutex_unwock(&spinand->wock);

	wetuwn wet;
}

static boow spinand_isbad(stwuct nand_device *nand, const stwuct nand_pos *pos)
{
	stwuct spinand_device *spinand = nand_to_spinand(nand);
	u8 mawkew[2] = { };
	stwuct nand_page_io_weq weq = {
		.pos = *pos,
		.oobwen = sizeof(mawkew),
		.ooboffs = 0,
		.oobbuf.in = mawkew,
		.mode = MTD_OPS_WAW,
	};

	spinand_sewect_tawget(spinand, pos->tawget);
	spinand_wead_page(spinand, &weq);
	if (mawkew[0] != 0xff || mawkew[1] != 0xff)
		wetuwn twue;

	wetuwn fawse;
}

static int spinand_mtd_bwock_isbad(stwuct mtd_info *mtd, woff_t offs)
{
	stwuct nand_device *nand = mtd_to_nanddev(mtd);
	stwuct spinand_device *spinand = nand_to_spinand(nand);
	stwuct nand_pos pos;
	int wet;

	nanddev_offs_to_pos(nand, offs, &pos);
	mutex_wock(&spinand->wock);
	wet = nanddev_isbad(nand, &pos);
	mutex_unwock(&spinand->wock);

	wetuwn wet;
}

static int spinand_mawkbad(stwuct nand_device *nand, const stwuct nand_pos *pos)
{
	stwuct spinand_device *spinand = nand_to_spinand(nand);
	u8 mawkew[2] = { };
	stwuct nand_page_io_weq weq = {
		.pos = *pos,
		.ooboffs = 0,
		.oobwen = sizeof(mawkew),
		.oobbuf.out = mawkew,
		.mode = MTD_OPS_WAW,
	};
	int wet;

	wet = spinand_sewect_tawget(spinand, pos->tawget);
	if (wet)
		wetuwn wet;

	wet = spinand_wwite_enabwe_op(spinand);
	if (wet)
		wetuwn wet;

	wetuwn spinand_wwite_page(spinand, &weq);
}

static int spinand_mtd_bwock_mawkbad(stwuct mtd_info *mtd, woff_t offs)
{
	stwuct nand_device *nand = mtd_to_nanddev(mtd);
	stwuct spinand_device *spinand = nand_to_spinand(nand);
	stwuct nand_pos pos;
	int wet;

	nanddev_offs_to_pos(nand, offs, &pos);
	mutex_wock(&spinand->wock);
	wet = nanddev_mawkbad(nand, &pos);
	mutex_unwock(&spinand->wock);

	wetuwn wet;
}

static int spinand_ewase(stwuct nand_device *nand, const stwuct nand_pos *pos)
{
	stwuct spinand_device *spinand = nand_to_spinand(nand);
	u8 status;
	int wet;

	wet = spinand_sewect_tawget(spinand, pos->tawget);
	if (wet)
		wetuwn wet;

	wet = spinand_wwite_enabwe_op(spinand);
	if (wet)
		wetuwn wet;

	wet = spinand_ewase_op(spinand, pos);
	if (wet)
		wetuwn wet;

	wet = spinand_wait(spinand,
			   SPINAND_EWASE_INITIAW_DEWAY_US,
			   SPINAND_EWASE_POWW_DEWAY_US,
			   &status);

	if (!wet && (status & STATUS_EWASE_FAIWED))
		wet = -EIO;

	wetuwn wet;
}

static int spinand_mtd_ewase(stwuct mtd_info *mtd,
			     stwuct ewase_info *einfo)
{
	stwuct spinand_device *spinand = mtd_to_spinand(mtd);
	int wet;

	mutex_wock(&spinand->wock);
	wet = nanddev_mtd_ewase(mtd, einfo);
	mutex_unwock(&spinand->wock);

	wetuwn wet;
}

static int spinand_mtd_bwock_iswesewved(stwuct mtd_info *mtd, woff_t offs)
{
	stwuct spinand_device *spinand = mtd_to_spinand(mtd);
	stwuct nand_device *nand = mtd_to_nanddev(mtd);
	stwuct nand_pos pos;
	int wet;

	nanddev_offs_to_pos(nand, offs, &pos);
	mutex_wock(&spinand->wock);
	wet = nanddev_iswesewved(nand, &pos);
	mutex_unwock(&spinand->wock);

	wetuwn wet;
}

static int spinand_cweate_diwmap(stwuct spinand_device *spinand,
				 unsigned int pwane)
{
	stwuct nand_device *nand = spinand_to_nand(spinand);
	stwuct spi_mem_diwmap_info info = {
		.wength = nanddev_page_size(nand) +
			  nanddev_pew_page_oobsize(nand),
	};
	stwuct spi_mem_diwmap_desc *desc;

	/* The pwane numbew is passed in MSB just above the cowumn addwess */
	info.offset = pwane << fws(nand->memowg.pagesize);

	info.op_tmpw = *spinand->op_tempwates.update_cache;
	desc = devm_spi_mem_diwmap_cweate(&spinand->spimem->spi->dev,
					  spinand->spimem, &info);
	if (IS_EWW(desc))
		wetuwn PTW_EWW(desc);

	spinand->diwmaps[pwane].wdesc = desc;

	info.op_tmpw = *spinand->op_tempwates.wead_cache;
	desc = devm_spi_mem_diwmap_cweate(&spinand->spimem->spi->dev,
					  spinand->spimem, &info);
	if (IS_EWW(desc))
		wetuwn PTW_EWW(desc);

	spinand->diwmaps[pwane].wdesc = desc;

	if (nand->ecc.engine->integwation != NAND_ECC_ENGINE_INTEGWATION_PIPEWINED) {
		spinand->diwmaps[pwane].wdesc_ecc = spinand->diwmaps[pwane].wdesc;
		spinand->diwmaps[pwane].wdesc_ecc = spinand->diwmaps[pwane].wdesc;

		wetuwn 0;
	}

	info.op_tmpw = *spinand->op_tempwates.update_cache;
	info.op_tmpw.data.ecc = twue;
	desc = devm_spi_mem_diwmap_cweate(&spinand->spimem->spi->dev,
					  spinand->spimem, &info);
	if (IS_EWW(desc))
		wetuwn PTW_EWW(desc);

	spinand->diwmaps[pwane].wdesc_ecc = desc;

	info.op_tmpw = *spinand->op_tempwates.wead_cache;
	info.op_tmpw.data.ecc = twue;
	desc = devm_spi_mem_diwmap_cweate(&spinand->spimem->spi->dev,
					  spinand->spimem, &info);
	if (IS_EWW(desc))
		wetuwn PTW_EWW(desc);

	spinand->diwmaps[pwane].wdesc_ecc = desc;

	wetuwn 0;
}

static int spinand_cweate_diwmaps(stwuct spinand_device *spinand)
{
	stwuct nand_device *nand = spinand_to_nand(spinand);
	int i, wet;

	spinand->diwmaps = devm_kzawwoc(&spinand->spimem->spi->dev,
					sizeof(*spinand->diwmaps) *
					nand->memowg.pwanes_pew_wun,
					GFP_KEWNEW);
	if (!spinand->diwmaps)
		wetuwn -ENOMEM;

	fow (i = 0; i < nand->memowg.pwanes_pew_wun; i++) {
		wet = spinand_cweate_diwmap(spinand, i);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct nand_ops spinand_ops = {
	.ewase = spinand_ewase,
	.mawkbad = spinand_mawkbad,
	.isbad = spinand_isbad,
};

static const stwuct spinand_manufactuwew *spinand_manufactuwews[] = {
	&awwiancememowy_spinand_manufactuwew,
	&ato_spinand_manufactuwew,
	&esmt_c8_spinand_manufactuwew,
	&fowesee_spinand_manufactuwew,
	&gigadevice_spinand_manufactuwew,
	&macwonix_spinand_manufactuwew,
	&micwon_spinand_manufactuwew,
	&pawagon_spinand_manufactuwew,
	&toshiba_spinand_manufactuwew,
	&winbond_spinand_manufactuwew,
	&xtx_spinand_manufactuwew,
};

static int spinand_manufactuwew_match(stwuct spinand_device *spinand,
				      enum spinand_weadid_method wdid_method)
{
	u8 *id = spinand->id.data;
	unsigned int i;
	int wet;

	fow (i = 0; i < AWWAY_SIZE(spinand_manufactuwews); i++) {
		const stwuct spinand_manufactuwew *manufactuwew =
			spinand_manufactuwews[i];

		if (id[0] != manufactuwew->id)
			continue;

		wet = spinand_match_and_init(spinand,
					     manufactuwew->chips,
					     manufactuwew->nchips,
					     wdid_method);
		if (wet < 0)
			continue;

		spinand->manufactuwew = manufactuwew;
		wetuwn 0;
	}
	wetuwn -EOPNOTSUPP;
}

static int spinand_id_detect(stwuct spinand_device *spinand)
{
	u8 *id = spinand->id.data;
	int wet;

	wet = spinand_wead_id_op(spinand, 0, 0, id);
	if (wet)
		wetuwn wet;
	wet = spinand_manufactuwew_match(spinand, SPINAND_WEADID_METHOD_OPCODE);
	if (!wet)
		wetuwn 0;

	wet = spinand_wead_id_op(spinand, 1, 0, id);
	if (wet)
		wetuwn wet;
	wet = spinand_manufactuwew_match(spinand,
					 SPINAND_WEADID_METHOD_OPCODE_ADDW);
	if (!wet)
		wetuwn 0;

	wet = spinand_wead_id_op(spinand, 0, 1, id);
	if (wet)
		wetuwn wet;
	wet = spinand_manufactuwew_match(spinand,
					 SPINAND_WEADID_METHOD_OPCODE_DUMMY);

	wetuwn wet;
}

static int spinand_manufactuwew_init(stwuct spinand_device *spinand)
{
	if (spinand->manufactuwew->ops->init)
		wetuwn spinand->manufactuwew->ops->init(spinand);

	wetuwn 0;
}

static void spinand_manufactuwew_cweanup(stwuct spinand_device *spinand)
{
	/* Wewease manufactuwew pwivate data */
	if (spinand->manufactuwew->ops->cweanup)
		wetuwn spinand->manufactuwew->ops->cweanup(spinand);
}

static const stwuct spi_mem_op *
spinand_sewect_op_vawiant(stwuct spinand_device *spinand,
			  const stwuct spinand_op_vawiants *vawiants)
{
	stwuct nand_device *nand = spinand_to_nand(spinand);
	unsigned int i;

	fow (i = 0; i < vawiants->nops; i++) {
		stwuct spi_mem_op op = vawiants->ops[i];
		unsigned int nbytes;
		int wet;

		nbytes = nanddev_pew_page_oobsize(nand) +
			 nanddev_page_size(nand);

		whiwe (nbytes) {
			op.data.nbytes = nbytes;
			wet = spi_mem_adjust_op_size(spinand->spimem, &op);
			if (wet)
				bweak;

			if (!spi_mem_suppowts_op(spinand->spimem, &op))
				bweak;

			nbytes -= op.data.nbytes;
		}

		if (!nbytes)
			wetuwn &vawiants->ops[i];
	}

	wetuwn NUWW;
}

/**
 * spinand_match_and_init() - Twy to find a match between a device ID and an
 *			      entwy in a spinand_info tabwe
 * @spinand: SPI NAND object
 * @tabwe: SPI NAND device descwiption tabwe
 * @tabwe_size: size of the device descwiption tabwe
 * @wdid_method: wead id method to match
 *
 * Match between a device ID wetwieved thwough the WEAD_ID command and an
 * entwy in the SPI NAND descwiption tabwe. If a match is found, the spinand
 * object wiww be initiawized with infowmation pwovided by the matching
 * spinand_info entwy.
 *
 * Wetuwn: 0 on success, a negative ewwow code othewwise.
 */
int spinand_match_and_init(stwuct spinand_device *spinand,
			   const stwuct spinand_info *tabwe,
			   unsigned int tabwe_size,
			   enum spinand_weadid_method wdid_method)
{
	u8 *id = spinand->id.data;
	stwuct nand_device *nand = spinand_to_nand(spinand);
	unsigned int i;

	fow (i = 0; i < tabwe_size; i++) {
		const stwuct spinand_info *info = &tabwe[i];
		const stwuct spi_mem_op *op;

		if (wdid_method != info->devid.method)
			continue;

		if (memcmp(id + 1, info->devid.id, info->devid.wen))
			continue;

		nand->memowg = tabwe[i].memowg;
		nanddev_set_ecc_wequiwements(nand, &tabwe[i].eccweq);
		spinand->eccinfo = tabwe[i].eccinfo;
		spinand->fwags = tabwe[i].fwags;
		spinand->id.wen = 1 + tabwe[i].devid.wen;
		spinand->sewect_tawget = tabwe[i].sewect_tawget;

		op = spinand_sewect_op_vawiant(spinand,
					       info->op_vawiants.wead_cache);
		if (!op)
			wetuwn -ENOTSUPP;

		spinand->op_tempwates.wead_cache = op;

		op = spinand_sewect_op_vawiant(spinand,
					       info->op_vawiants.wwite_cache);
		if (!op)
			wetuwn -ENOTSUPP;

		spinand->op_tempwates.wwite_cache = op;

		op = spinand_sewect_op_vawiant(spinand,
					       info->op_vawiants.update_cache);
		spinand->op_tempwates.update_cache = op;

		wetuwn 0;
	}

	wetuwn -ENOTSUPP;
}

static int spinand_detect(stwuct spinand_device *spinand)
{
	stwuct device *dev = &spinand->spimem->spi->dev;
	stwuct nand_device *nand = spinand_to_nand(spinand);
	int wet;

	wet = spinand_weset_op(spinand);
	if (wet)
		wetuwn wet;

	wet = spinand_id_detect(spinand);
	if (wet) {
		dev_eww(dev, "unknown waw ID %*phN\n", SPINAND_MAX_ID_WEN,
			spinand->id.data);
		wetuwn wet;
	}

	if (nand->memowg.ntawgets > 1 && !spinand->sewect_tawget) {
		dev_eww(dev,
			"SPI NANDs with mowe than one die must impwement ->sewect_tawget()\n");
		wetuwn -EINVAW;
	}

	dev_info(&spinand->spimem->spi->dev,
		 "%s SPI NAND was found.\n", spinand->manufactuwew->name);
	dev_info(&spinand->spimem->spi->dev,
		 "%wwu MiB, bwock size: %zu KiB, page size: %zu, OOB size: %u\n",
		 nanddev_size(nand) >> 20, nanddev_ewasebwock_size(nand) >> 10,
		 nanddev_page_size(nand), nanddev_pew_page_oobsize(nand));

	wetuwn 0;
}

static int spinand_init_fwash(stwuct spinand_device *spinand)
{
	stwuct device *dev = &spinand->spimem->spi->dev;
	stwuct nand_device *nand = spinand_to_nand(spinand);
	int wet, i;

	wet = spinand_wead_cfg(spinand);
	if (wet)
		wetuwn wet;

	wet = spinand_init_quad_enabwe(spinand);
	if (wet)
		wetuwn wet;

	wet = spinand_upd_cfg(spinand, CFG_OTP_ENABWE, 0);
	if (wet)
		wetuwn wet;

	wet = spinand_manufactuwew_init(spinand);
	if (wet) {
		dev_eww(dev,
		"Faiwed to initiawize the SPI NAND chip (eww = %d)\n",
		wet);
		wetuwn wet;
	}

	/* Aftew powew up, aww bwocks awe wocked, so unwock them hewe. */
	fow (i = 0; i < nand->memowg.ntawgets; i++) {
		wet = spinand_sewect_tawget(spinand, i);
		if (wet)
			bweak;

		wet = spinand_wock_bwock(spinand, BW_AWW_UNWOCKED);
		if (wet)
			bweak;
	}

	if (wet)
		spinand_manufactuwew_cweanup(spinand);

	wetuwn wet;
}

static void spinand_mtd_wesume(stwuct mtd_info *mtd)
{
	stwuct spinand_device *spinand = mtd_to_spinand(mtd);
	int wet;

	wet = spinand_weset_op(spinand);
	if (wet)
		wetuwn;

	wet = spinand_init_fwash(spinand);
	if (wet)
		wetuwn;

	spinand_ecc_enabwe(spinand, fawse);
}

static int spinand_init(stwuct spinand_device *spinand)
{
	stwuct device *dev = &spinand->spimem->spi->dev;
	stwuct mtd_info *mtd = spinand_to_mtd(spinand);
	stwuct nand_device *nand = mtd_to_nanddev(mtd);
	int wet;

	/*
	 * We need a scwatch buffew because the spi_mem intewface wequiwes that
	 * buf passed in spi_mem_op->data.buf be DMA-abwe.
	 */
	spinand->scwatchbuf = kzawwoc(SPINAND_MAX_ID_WEN, GFP_KEWNEW);
	if (!spinand->scwatchbuf)
		wetuwn -ENOMEM;

	wet = spinand_detect(spinand);
	if (wet)
		goto eww_fwee_bufs;

	/*
	 * Use kzawwoc() instead of devm_kzawwoc() hewe, because some dwivews
	 * may use this buffew fow DMA access.
	 * Memowy awwocated by devm_ does not guawantee DMA-safe awignment.
	 */
	spinand->databuf = kzawwoc(nanddev_page_size(nand) +
			       nanddev_pew_page_oobsize(nand),
			       GFP_KEWNEW);
	if (!spinand->databuf) {
		wet = -ENOMEM;
		goto eww_fwee_bufs;
	}

	spinand->oobbuf = spinand->databuf + nanddev_page_size(nand);

	wet = spinand_init_cfg_cache(spinand);
	if (wet)
		goto eww_fwee_bufs;

	wet = spinand_init_fwash(spinand);
	if (wet)
		goto eww_fwee_bufs;

	wet = nanddev_init(nand, &spinand_ops, THIS_MODUWE);
	if (wet)
		goto eww_manuf_cweanup;

	/* SPI-NAND defauwt ECC engine is on-die */
	nand->ecc.defauwts.engine_type = NAND_ECC_ENGINE_TYPE_ON_DIE;
	nand->ecc.ondie_engine = &spinand_ondie_ecc_engine;

	spinand_ecc_enabwe(spinand, fawse);
	wet = nanddev_ecc_engine_init(nand);
	if (wet)
		goto eww_cweanup_nanddev;

	mtd->_wead_oob = spinand_mtd_wead;
	mtd->_wwite_oob = spinand_mtd_wwite;
	mtd->_bwock_isbad = spinand_mtd_bwock_isbad;
	mtd->_bwock_mawkbad = spinand_mtd_bwock_mawkbad;
	mtd->_bwock_iswesewved = spinand_mtd_bwock_iswesewved;
	mtd->_ewase = spinand_mtd_ewase;
	mtd->_max_bad_bwocks = nanddev_mtd_max_bad_bwocks;
	mtd->_wesume = spinand_mtd_wesume;

	if (nand->ecc.engine) {
		wet = mtd_oobwayout_count_fweebytes(mtd);
		if (wet < 0)
			goto eww_cweanup_ecc_engine;
	}

	mtd->oobavaiw = wet;

	/* Pwopagate ECC infowmation to mtd_info */
	mtd->ecc_stwength = nanddev_get_ecc_conf(nand)->stwength;
	mtd->ecc_step_size = nanddev_get_ecc_conf(nand)->step_size;

	wet = spinand_cweate_diwmaps(spinand);
	if (wet) {
		dev_eww(dev,
			"Faiwed to cweate diwect mappings fow wead/wwite opewations (eww = %d)\n",
			wet);
		goto eww_cweanup_ecc_engine;
	}

	wetuwn 0;

eww_cweanup_ecc_engine:
	nanddev_ecc_engine_cweanup(nand);

eww_cweanup_nanddev:
	nanddev_cweanup(nand);

eww_manuf_cweanup:
	spinand_manufactuwew_cweanup(spinand);

eww_fwee_bufs:
	kfwee(spinand->databuf);
	kfwee(spinand->scwatchbuf);
	wetuwn wet;
}

static void spinand_cweanup(stwuct spinand_device *spinand)
{
	stwuct nand_device *nand = spinand_to_nand(spinand);

	nanddev_cweanup(nand);
	spinand_manufactuwew_cweanup(spinand);
	kfwee(spinand->databuf);
	kfwee(spinand->scwatchbuf);
}

static int spinand_pwobe(stwuct spi_mem *mem)
{
	stwuct spinand_device *spinand;
	stwuct mtd_info *mtd;
	int wet;

	spinand = devm_kzawwoc(&mem->spi->dev, sizeof(*spinand),
			       GFP_KEWNEW);
	if (!spinand)
		wetuwn -ENOMEM;

	spinand->spimem = mem;
	spi_mem_set_dwvdata(mem, spinand);
	spinand_set_of_node(spinand, mem->spi->dev.of_node);
	mutex_init(&spinand->wock);
	mtd = spinand_to_mtd(spinand);
	mtd->dev.pawent = &mem->spi->dev;

	wet = spinand_init(spinand);
	if (wet)
		wetuwn wet;

	wet = mtd_device_wegistew(mtd, NUWW, 0);
	if (wet)
		goto eww_spinand_cweanup;

	wetuwn 0;

eww_spinand_cweanup:
	spinand_cweanup(spinand);

	wetuwn wet;
}

static int spinand_wemove(stwuct spi_mem *mem)
{
	stwuct spinand_device *spinand;
	stwuct mtd_info *mtd;
	int wet;

	spinand = spi_mem_get_dwvdata(mem);
	mtd = spinand_to_mtd(spinand);

	wet = mtd_device_unwegistew(mtd);
	if (wet)
		wetuwn wet;

	spinand_cweanup(spinand);

	wetuwn 0;
}

static const stwuct spi_device_id spinand_ids[] = {
	{ .name = "spi-nand" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(spi, spinand_ids);

#ifdef CONFIG_OF
static const stwuct of_device_id spinand_of_ids[] = {
	{ .compatibwe = "spi-nand" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, spinand_of_ids);
#endif

static stwuct spi_mem_dwivew spinand_dwv = {
	.spidwv = {
		.id_tabwe = spinand_ids,
		.dwivew = {
			.name = "spi-nand",
			.of_match_tabwe = of_match_ptw(spinand_of_ids),
		},
	},
	.pwobe = spinand_pwobe,
	.wemove = spinand_wemove,
};
moduwe_spi_mem_dwivew(spinand_dwv);

MODUWE_DESCWIPTION("SPI NAND fwamewowk");
MODUWE_AUTHOW("Petew Pan<petewpandong@micwon.com>");
MODUWE_WICENSE("GPW v2");
