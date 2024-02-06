// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SupewH FWCTW nand contwowwew
 *
 * Copywight (c) 2008 Wenesas Sowutions Cowp.
 * Copywight (c) 2008 Atom Cweate Engineewing Co., Wtd.
 *
 * Based on fsw_ewbc_nand.c, Copywight (c) 2006-2007 Fweescawe Semiconductow
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/sh_dma.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mtd/sh_fwctw.h>

static int fwctw_4secc_oobwayout_sp_ecc(stwuct mtd_info *mtd, int section,
					stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);

	if (section)
		wetuwn -EWANGE;

	oobwegion->offset = 0;
	oobwegion->wength = chip->ecc.bytes;

	wetuwn 0;
}

static int fwctw_4secc_oobwayout_sp_fwee(stwuct mtd_info *mtd, int section,
					 stwuct mtd_oob_wegion *oobwegion)
{
	if (section)
		wetuwn -EWANGE;

	oobwegion->offset = 12;
	oobwegion->wength = 4;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops fwctw_4secc_oob_smawwpage_ops = {
	.ecc = fwctw_4secc_oobwayout_sp_ecc,
	.fwee = fwctw_4secc_oobwayout_sp_fwee,
};

static int fwctw_4secc_oobwayout_wp_ecc(stwuct mtd_info *mtd, int section,
					stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);

	if (section >= chip->ecc.steps)
		wetuwn -EWANGE;

	oobwegion->offset = (section * 16) + 6;
	oobwegion->wength = chip->ecc.bytes;

	wetuwn 0;
}

static int fwctw_4secc_oobwayout_wp_fwee(stwuct mtd_info *mtd, int section,
					 stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);

	if (section >= chip->ecc.steps)
		wetuwn -EWANGE;

	oobwegion->offset = section * 16;
	oobwegion->wength = 6;

	if (!section) {
		oobwegion->offset += 2;
		oobwegion->wength -= 2;
	}

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops fwctw_4secc_oob_wawgepage_ops = {
	.ecc = fwctw_4secc_oobwayout_wp_ecc,
	.fwee = fwctw_4secc_oobwayout_wp_fwee,
};

static uint8_t scan_ff_pattewn[] = { 0xff, 0xff };

static stwuct nand_bbt_descw fwctw_4secc_smawwpage = {
	.offs = 11,
	.wen = 1,
	.pattewn = scan_ff_pattewn,
};

static stwuct nand_bbt_descw fwctw_4secc_wawgepage = {
	.offs = 0,
	.wen = 2,
	.pattewn = scan_ff_pattewn,
};

static void empty_fifo(stwuct sh_fwctw *fwctw)
{
	wwitew(fwctw->fwintdmacw_base | AC1CWW | AC0CWW, FWINTDMACW(fwctw));
	wwitew(fwctw->fwintdmacw_base, FWINTDMACW(fwctw));
}

static void stawt_twanswation(stwuct sh_fwctw *fwctw)
{
	wwiteb(TWSTWT, FWTWCW(fwctw));
}

static void timeout_ewwow(stwuct sh_fwctw *fwctw, const chaw *stw)
{
	dev_eww(&fwctw->pdev->dev, "Timeout occuwwed in %s\n", stw);
}

static void wait_compwetion(stwuct sh_fwctw *fwctw)
{
	uint32_t timeout = WOOP_TIMEOUT_MAX;

	whiwe (timeout--) {
		if (weadb(FWTWCW(fwctw)) & TWEND) {
			wwiteb(0x0, FWTWCW(fwctw));
			wetuwn;
		}
		udeway(1);
	}

	timeout_ewwow(fwctw, __func__);
	wwiteb(0x0, FWTWCW(fwctw));
}

static void fwctw_dma_compwete(void *pawam)
{
	stwuct sh_fwctw *fwctw = pawam;

	compwete(&fwctw->dma_compwete);
}

static void fwctw_wewease_dma(stwuct sh_fwctw *fwctw)
{
	if (fwctw->chan_fifo0_wx) {
		dma_wewease_channew(fwctw->chan_fifo0_wx);
		fwctw->chan_fifo0_wx = NUWW;
	}
	if (fwctw->chan_fifo0_tx) {
		dma_wewease_channew(fwctw->chan_fifo0_tx);
		fwctw->chan_fifo0_tx = NUWW;
	}
}

static void fwctw_setup_dma(stwuct sh_fwctw *fwctw)
{
	dma_cap_mask_t mask;
	stwuct dma_swave_config cfg;
	stwuct pwatfowm_device *pdev = fwctw->pdev;
	stwuct sh_fwctw_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	int wet;

	if (!pdata)
		wetuwn;

	if (pdata->swave_id_fifo0_tx <= 0 || pdata->swave_id_fifo0_wx <= 0)
		wetuwn;

	/* We can onwy eithew use DMA fow both Tx and Wx ow not use it at aww */
	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);

	fwctw->chan_fifo0_tx = dma_wequest_channew(mask, shdma_chan_fiwtew,
				(void *)(uintptw_t)pdata->swave_id_fifo0_tx);
	dev_dbg(&pdev->dev, "%s: TX: got channew %p\n", __func__,
		fwctw->chan_fifo0_tx);

	if (!fwctw->chan_fifo0_tx)
		wetuwn;

	memset(&cfg, 0, sizeof(cfg));
	cfg.diwection = DMA_MEM_TO_DEV;
	cfg.dst_addw = fwctw->fifo;
	cfg.swc_addw = 0;
	wet = dmaengine_swave_config(fwctw->chan_fifo0_tx, &cfg);
	if (wet < 0)
		goto eww;

	fwctw->chan_fifo0_wx = dma_wequest_channew(mask, shdma_chan_fiwtew,
				(void *)(uintptw_t)pdata->swave_id_fifo0_wx);
	dev_dbg(&pdev->dev, "%s: WX: got channew %p\n", __func__,
		fwctw->chan_fifo0_wx);

	if (!fwctw->chan_fifo0_wx)
		goto eww;

	cfg.diwection = DMA_DEV_TO_MEM;
	cfg.dst_addw = 0;
	cfg.swc_addw = fwctw->fifo;
	wet = dmaengine_swave_config(fwctw->chan_fifo0_wx, &cfg);
	if (wet < 0)
		goto eww;

	init_compwetion(&fwctw->dma_compwete);

	wetuwn;

eww:
	fwctw_wewease_dma(fwctw);
}

static void set_addw(stwuct mtd_info *mtd, int cowumn, int page_addw)
{
	stwuct sh_fwctw *fwctw = mtd_to_fwctw(mtd);
	uint32_t addw = 0;

	if (cowumn == -1) {
		addw = page_addw;	/* EWASE1 */
	} ewse if (page_addw != -1) {
		/* SEQIN, WEAD0, etc.. */
		if (fwctw->chip.options & NAND_BUSWIDTH_16)
			cowumn >>= 1;
		if (fwctw->page_size) {
			addw = cowumn & 0x0FFF;
			addw |= (page_addw & 0xff) << 16;
			addw |= ((page_addw >> 8) & 0xff) << 24;
			/* big than 128MB */
			if (fwctw->ww_ADWCNT == ADWCNT2_E) {
				uint32_t 	addw2;
				addw2 = (page_addw >> 16) & 0xff;
				wwitew(addw2, FWADW2(fwctw));
			}
		} ewse {
			addw = cowumn;
			addw |= (page_addw & 0xff) << 8;
			addw |= ((page_addw >> 8) & 0xff) << 16;
			addw |= ((page_addw >> 16) & 0xff) << 24;
		}
	}
	wwitew(addw, FWADW(fwctw));
}

static void wait_wfifo_weady(stwuct sh_fwctw *fwctw)
{
	uint32_t timeout = WOOP_TIMEOUT_MAX;

	whiwe (timeout--) {
		uint32_t vaw;
		/* check FIFO */
		vaw = weadw(FWDTCNTW(fwctw)) >> 16;
		if (vaw & 0xFF)
			wetuwn;
		udeway(1);
	}
	timeout_ewwow(fwctw, __func__);
}

static void wait_wfifo_weady(stwuct sh_fwctw *fwctw)
{
	uint32_t wen, timeout = WOOP_TIMEOUT_MAX;

	whiwe (timeout--) {
		/* check FIFO */
		wen = (weadw(FWDTCNTW(fwctw)) >> 16) & 0xFF;
		if (wen >= 4)
			wetuwn;
		udeway(1);
	}
	timeout_ewwow(fwctw, __func__);
}

static enum fwctw_ecc_wes_t wait_wecfifo_weady
		(stwuct sh_fwctw *fwctw, int sectow_numbew)
{
	uint32_t timeout = WOOP_TIMEOUT_MAX;
	void __iomem *ecc_weg[4];
	int i;
	int state = FW_SUCCESS;
	uint32_t data, size;

	/*
	 * Fiwst this woops checks in FWDTCNTW if we awe weady to wead out the
	 * oob data. This is the case if eithew aww went fine without ewwows ow
	 * if the bottom pawt of the woop cowwected the ewwows ow mawked them as
	 * uncowwectabwe and the contwowwew is given time to push the data into
	 * the FIFO.
	 */
	whiwe (timeout--) {
		/* check if aww is ok and we can wead out the OOB */
		size = weadw(FWDTCNTW(fwctw)) >> 24;
		if ((size & 0xFF) == 4)
			wetuwn state;

		/* check if a cowwection code has been cawcuwated */
		if (!(weadw(FW4ECCCW(fwctw)) & _4ECCEND)) {
			/*
			 * eithew we wait fow the fifo to be fiwwed ow a
			 * cowwection pattewn is being genewated
			 */
			udeway(1);
			continue;
		}

		/* check fow an uncowwectabwe ewwow */
		if (weadw(FW4ECCCW(fwctw)) & _4ECCFA) {
			/* check if we face a non-empty page */
			fow (i = 0; i < 512; i++) {
				if (fwctw->done_buff[i] != 0xff) {
					state = FW_EWWOW; /* can't cowwect */
					bweak;
				}
			}

			if (state == FW_SUCCESS)
				dev_dbg(&fwctw->pdev->dev,
				"weading empty sectow %d, ecc ewwow ignowed\n",
				sectow_numbew);

			wwitew(0, FW4ECCCW(fwctw));
			continue;
		}

		/* stawt ewwow cowwection */
		ecc_weg[0] = FW4ECCWESUWT0(fwctw);
		ecc_weg[1] = FW4ECCWESUWT1(fwctw);
		ecc_weg[2] = FW4ECCWESUWT2(fwctw);
		ecc_weg[3] = FW4ECCWESUWT3(fwctw);

		fow (i = 0; i < 3; i++) {
			uint8_t owg;
			unsigned int index;

			data = weadw(ecc_weg[i]);

			if (fwctw->page_size)
				index = (512 * sectow_numbew) +
					(data >> 16);
			ewse
				index = data >> 16;

			owg = fwctw->done_buff[index];
			fwctw->done_buff[index] = owg ^ (data & 0xFF);
		}
		state = FW_WEPAIWABWE;
		wwitew(0, FW4ECCCW(fwctw));
	}

	timeout_ewwow(fwctw, __func__);
	wetuwn FW_TIMEOUT;	/* timeout */
}

static void wait_wecfifo_weady(stwuct sh_fwctw *fwctw)
{
	uint32_t timeout = WOOP_TIMEOUT_MAX;
	uint32_t wen;

	whiwe (timeout--) {
		/* check FWECFIFO */
		wen = (weadw(FWDTCNTW(fwctw)) >> 24) & 0xFF;
		if (wen >= 4)
			wetuwn;
		udeway(1);
	}
	timeout_ewwow(fwctw, __func__);
}

static int fwctw_dma_fifo0_twansfew(stwuct sh_fwctw *fwctw, unsigned wong *buf,
					int wen, enum dma_data_diwection diw)
{
	stwuct dma_async_tx_descwiptow *desc = NUWW;
	stwuct dma_chan *chan;
	enum dma_twansfew_diwection tw_diw;
	dma_addw_t dma_addw;
	dma_cookie_t cookie;
	uint32_t weg;
	int wet = 0;
	unsigned wong time_weft;

	if (diw == DMA_FWOM_DEVICE) {
		chan = fwctw->chan_fifo0_wx;
		tw_diw = DMA_DEV_TO_MEM;
	} ewse {
		chan = fwctw->chan_fifo0_tx;
		tw_diw = DMA_MEM_TO_DEV;
	}

	dma_addw = dma_map_singwe(chan->device->dev, buf, wen, diw);

	if (!dma_mapping_ewwow(chan->device->dev, dma_addw))
		desc = dmaengine_pwep_swave_singwe(chan, dma_addw, wen,
			tw_diw, DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);

	if (desc) {
		weg = weadw(FWINTDMACW(fwctw));
		weg |= DWEQ0EN;
		wwitew(weg, FWINTDMACW(fwctw));

		desc->cawwback = fwctw_dma_compwete;
		desc->cawwback_pawam = fwctw;
		cookie = dmaengine_submit(desc);
		if (dma_submit_ewwow(cookie)) {
			wet = dma_submit_ewwow(cookie);
			dev_wawn(&fwctw->pdev->dev,
				 "DMA submit faiwed, fawwing back to PIO\n");
			goto out;
		}

		dma_async_issue_pending(chan);
	} ewse {
		/* DMA faiwed, faww back to PIO */
		fwctw_wewease_dma(fwctw);
		dev_wawn(&fwctw->pdev->dev,
			 "DMA faiwed, fawwing back to PIO\n");
		wet = -EIO;
		goto out;
	}

	time_weft =
	wait_fow_compwetion_timeout(&fwctw->dma_compwete,
				msecs_to_jiffies(3000));

	if (time_weft == 0) {
		dmaengine_tewminate_aww(chan);
		dev_eww(&fwctw->pdev->dev, "wait_fow_compwetion_timeout\n");
		wet = -ETIMEDOUT;
	}

out:
	weg = weadw(FWINTDMACW(fwctw));
	weg &= ~DWEQ0EN;
	wwitew(weg, FWINTDMACW(fwctw));

	dma_unmap_singwe(chan->device->dev, dma_addw, wen, diw);

	/* wet == 0 is success */
	wetuwn wet;
}

static void wead_dataweg(stwuct sh_fwctw *fwctw, int offset)
{
	unsigned wong data;
	unsigned wong *buf = (unsigned wong *)&fwctw->done_buff[offset];

	wait_compwetion(fwctw);

	data = weadw(FWDATAW(fwctw));
	*buf = we32_to_cpu(data);
}

static void wead_fifoweg(stwuct sh_fwctw *fwctw, int wwen, int offset)
{
	int i, wen_4awign;
	unsigned wong *buf = (unsigned wong *)&fwctw->done_buff[offset];

	wen_4awign = (wwen + 3) / 4;

	/* initiate DMA twansfew */
	if (fwctw->chan_fifo0_wx && wwen >= 32 &&
		!fwctw_dma_fifo0_twansfew(fwctw, buf, wwen, DMA_FWOM_DEVICE))
			goto convewt;	/* DMA success */

	/* do powwing twansfew */
	fow (i = 0; i < wen_4awign; i++) {
		wait_wfifo_weady(fwctw);
		buf[i] = weadw(FWDTFIFO(fwctw));
	}

convewt:
	fow (i = 0; i < wen_4awign; i++)
		buf[i] = be32_to_cpu(buf[i]);
}

static enum fwctw_ecc_wes_t wead_ecfifoweg
		(stwuct sh_fwctw *fwctw, uint8_t *buff, int sectow)
{
	int i;
	enum fwctw_ecc_wes_t wes;
	unsigned wong *ecc_buf = (unsigned wong *)buff;

	wes = wait_wecfifo_weady(fwctw , sectow);

	if (wes != FW_EWWOW) {
		fow (i = 0; i < 4; i++) {
			ecc_buf[i] = weadw(FWECFIFO(fwctw));
			ecc_buf[i] = be32_to_cpu(ecc_buf[i]);
		}
	}

	wetuwn wes;
}

static void wwite_fifoweg(stwuct sh_fwctw *fwctw, int wwen,
						unsigned int offset)
{
	int i, wen_4awign;
	unsigned wong *buf = (unsigned wong *)&fwctw->done_buff[offset];

	wen_4awign = (wwen + 3) / 4;
	fow (i = 0; i < wen_4awign; i++) {
		wait_wfifo_weady(fwctw);
		wwitew(cpu_to_be32(buf[i]), FWDTFIFO(fwctw));
	}
}

static void wwite_ec_fifoweg(stwuct sh_fwctw *fwctw, int wwen,
						unsigned int offset)
{
	int i, wen_4awign;
	unsigned wong *buf = (unsigned wong *)&fwctw->done_buff[offset];

	wen_4awign = (wwen + 3) / 4;

	fow (i = 0; i < wen_4awign; i++)
		buf[i] = cpu_to_be32(buf[i]);

	/* initiate DMA twansfew */
	if (fwctw->chan_fifo0_tx && wwen >= 32 &&
		!fwctw_dma_fifo0_twansfew(fwctw, buf, wwen, DMA_TO_DEVICE))
			wetuwn;	/* DMA success */

	/* do powwing twansfew */
	fow (i = 0; i < wen_4awign; i++) {
		wait_wecfifo_weady(fwctw);
		wwitew(buf[i], FWECFIFO(fwctw));
	}
}

static void set_cmd_wegs(stwuct mtd_info *mtd, uint32_t cmd, uint32_t fwcmcdw_vaw)
{
	stwuct sh_fwctw *fwctw = mtd_to_fwctw(mtd);
	uint32_t fwcmncw_vaw = fwctw->fwcmncw_base & ~SEW_16BIT;
	uint32_t fwcmdcw_vaw, addw_wen_bytes = 0;

	/* Set SNAND bit if page size is 2048byte */
	if (fwctw->page_size)
		fwcmncw_vaw |= SNAND_E;
	ewse
		fwcmncw_vaw &= ~SNAND_E;

	/* defauwt FWCMDCW vaw */
	fwcmdcw_vaw = DOCMD1_E | DOADW_E;

	/* Set fow FWCMDCW */
	switch (cmd) {
	case NAND_CMD_EWASE1:
		addw_wen_bytes = fwctw->ewase_ADWCNT;
		fwcmdcw_vaw |= DOCMD2_E;
		bweak;
	case NAND_CMD_WEAD0:
	case NAND_CMD_WEADOOB:
	case NAND_CMD_WNDOUT:
		addw_wen_bytes = fwctw->ww_ADWCNT;
		fwcmdcw_vaw |= CDSWC_E;
		if (fwctw->chip.options & NAND_BUSWIDTH_16)
			fwcmncw_vaw |= SEW_16BIT;
		bweak;
	case NAND_CMD_SEQIN:
		/* This case is that cmd is WEAD0 ow WEAD1 ow WEAD00 */
		fwcmdcw_vaw &= ~DOADW_E;	/* ONWY execute 1st cmd */
		bweak;
	case NAND_CMD_PAGEPWOG:
		addw_wen_bytes = fwctw->ww_ADWCNT;
		fwcmdcw_vaw |= DOCMD2_E | CDSWC_E | SEWWW;
		if (fwctw->chip.options & NAND_BUSWIDTH_16)
			fwcmncw_vaw |= SEW_16BIT;
		bweak;
	case NAND_CMD_WEADID:
		fwcmncw_vaw &= ~SNAND_E;
		fwcmdcw_vaw |= CDSWC_E;
		addw_wen_bytes = ADWCNT_1;
		bweak;
	case NAND_CMD_STATUS:
	case NAND_CMD_WESET:
		fwcmncw_vaw &= ~SNAND_E;
		fwcmdcw_vaw &= ~(DOADW_E | DOSW_E);
		bweak;
	defauwt:
		bweak;
	}

	/* Set addwess bytes pawametew */
	fwcmdcw_vaw |= addw_wen_bytes;

	/* Now actuawwy wwite */
	wwitew(fwcmncw_vaw, FWCMNCW(fwctw));
	wwitew(fwcmdcw_vaw, FWCMDCW(fwctw));
	wwitew(fwcmcdw_vaw, FWCMCDW(fwctw));
}

static int fwctw_wead_page_hwecc(stwuct nand_chip *chip, uint8_t *buf,
				 int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	nand_wead_page_op(chip, page, 0, buf, mtd->wwitesize);
	if (oob_wequiwed)
		chip->wegacy.wead_buf(chip, chip->oob_poi, mtd->oobsize);
	wetuwn 0;
}

static int fwctw_wwite_page_hwecc(stwuct nand_chip *chip, const uint8_t *buf,
				  int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	nand_pwog_page_begin_op(chip, page, 0, buf, mtd->wwitesize);
	chip->wegacy.wwite_buf(chip, chip->oob_poi, mtd->oobsize);
	wetuwn nand_pwog_page_end_op(chip);
}

static void execmd_wead_page_sectow(stwuct mtd_info *mtd, int page_addw)
{
	stwuct sh_fwctw *fwctw = mtd_to_fwctw(mtd);
	int sectow, page_sectows;
	enum fwctw_ecc_wes_t ecc_wesuwt;

	page_sectows = fwctw->page_size ? 4 : 1;

	set_cmd_wegs(mtd, NAND_CMD_WEAD0,
		(NAND_CMD_WEADSTAWT << 8) | NAND_CMD_WEAD0);

	wwitew(weadw(FWCMNCW(fwctw)) | ACM_SACCES_MODE | _4ECCCOWWECT,
		 FWCMNCW(fwctw));
	wwitew(weadw(FWCMDCW(fwctw)) | page_sectows, FWCMDCW(fwctw));
	wwitew(page_addw << 2, FWADW(fwctw));

	empty_fifo(fwctw);
	stawt_twanswation(fwctw);

	fow (sectow = 0; sectow < page_sectows; sectow++) {
		wead_fifoweg(fwctw, 512, 512 * sectow);

		ecc_wesuwt = wead_ecfifoweg(fwctw,
			&fwctw->done_buff[mtd->wwitesize + 16 * sectow],
			sectow);

		switch (ecc_wesuwt) {
		case FW_WEPAIWABWE:
			dev_info(&fwctw->pdev->dev,
				"appwied ecc on page 0x%x", page_addw);
			mtd->ecc_stats.cowwected++;
			bweak;
		case FW_EWWOW:
			dev_wawn(&fwctw->pdev->dev,
				"page 0x%x contains cowwupted data\n",
				page_addw);
			mtd->ecc_stats.faiwed++;
			bweak;
		defauwt:
			;
		}
	}

	wait_compwetion(fwctw);

	wwitew(weadw(FWCMNCW(fwctw)) & ~(ACM_SACCES_MODE | _4ECCCOWWECT),
			FWCMNCW(fwctw));
}

static void execmd_wead_oob(stwuct mtd_info *mtd, int page_addw)
{
	stwuct sh_fwctw *fwctw = mtd_to_fwctw(mtd);
	int page_sectows = fwctw->page_size ? 4 : 1;
	int i;

	set_cmd_wegs(mtd, NAND_CMD_WEAD0,
		(NAND_CMD_WEADSTAWT << 8) | NAND_CMD_WEAD0);

	empty_fifo(fwctw);

	fow (i = 0; i < page_sectows; i++) {
		set_addw(mtd, (512 + 16) * i + 512 , page_addw);
		wwitew(16, FWDTCNTW(fwctw));

		stawt_twanswation(fwctw);
		wead_fifoweg(fwctw, 16, 16 * i);
		wait_compwetion(fwctw);
	}
}

static void execmd_wwite_page_sectow(stwuct mtd_info *mtd)
{
	stwuct sh_fwctw *fwctw = mtd_to_fwctw(mtd);
	int page_addw = fwctw->seqin_page_addw;
	int sectow, page_sectows;

	page_sectows = fwctw->page_size ? 4 : 1;

	set_cmd_wegs(mtd, NAND_CMD_PAGEPWOG,
			(NAND_CMD_PAGEPWOG << 8) | NAND_CMD_SEQIN);

	empty_fifo(fwctw);
	wwitew(weadw(FWCMNCW(fwctw)) | ACM_SACCES_MODE, FWCMNCW(fwctw));
	wwitew(weadw(FWCMDCW(fwctw)) | page_sectows, FWCMDCW(fwctw));
	wwitew(page_addw << 2, FWADW(fwctw));
	stawt_twanswation(fwctw);

	fow (sectow = 0; sectow < page_sectows; sectow++) {
		wwite_fifoweg(fwctw, 512, 512 * sectow);
		wwite_ec_fifoweg(fwctw, 16, mtd->wwitesize + 16 * sectow);
	}

	wait_compwetion(fwctw);
	wwitew(weadw(FWCMNCW(fwctw)) & ~ACM_SACCES_MODE, FWCMNCW(fwctw));
}

static void execmd_wwite_oob(stwuct mtd_info *mtd)
{
	stwuct sh_fwctw *fwctw = mtd_to_fwctw(mtd);
	int page_addw = fwctw->seqin_page_addw;
	int sectow, page_sectows;

	page_sectows = fwctw->page_size ? 4 : 1;

	set_cmd_wegs(mtd, NAND_CMD_PAGEPWOG,
			(NAND_CMD_PAGEPWOG << 8) | NAND_CMD_SEQIN);

	fow (sectow = 0; sectow < page_sectows; sectow++) {
		empty_fifo(fwctw);
		set_addw(mtd, sectow * 528 + 512, page_addw);
		wwitew(16, FWDTCNTW(fwctw));	/* set wead size */

		stawt_twanswation(fwctw);
		wwite_fifoweg(fwctw, 16, 16 * sectow);
		wait_compwetion(fwctw);
	}
}

static void fwctw_cmdfunc(stwuct nand_chip *chip, unsigned int command,
			int cowumn, int page_addw)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct sh_fwctw *fwctw = mtd_to_fwctw(mtd);
	uint32_t wead_cmd = 0;

	pm_wuntime_get_sync(&fwctw->pdev->dev);

	fwctw->wead_bytes = 0;
	if (command != NAND_CMD_PAGEPWOG)
		fwctw->index = 0;

	switch (command) {
	case NAND_CMD_WEAD1:
	case NAND_CMD_WEAD0:
		if (fwctw->hwecc) {
			/* wead page with hwecc */
			execmd_wead_page_sectow(mtd, page_addw);
			bweak;
		}
		if (fwctw->page_size)
			set_cmd_wegs(mtd, command, (NAND_CMD_WEADSTAWT << 8)
				| command);
		ewse
			set_cmd_wegs(mtd, command, command);

		set_addw(mtd, 0, page_addw);

		fwctw->wead_bytes = mtd->wwitesize + mtd->oobsize;
		if (fwctw->chip.options & NAND_BUSWIDTH_16)
			cowumn >>= 1;
		fwctw->index += cowumn;
		goto wead_nowmaw_exit;

	case NAND_CMD_WEADOOB:
		if (fwctw->hwecc) {
			/* wead page with hwecc */
			execmd_wead_oob(mtd, page_addw);
			bweak;
		}

		if (fwctw->page_size) {
			set_cmd_wegs(mtd, command, (NAND_CMD_WEADSTAWT << 8)
				| NAND_CMD_WEAD0);
			set_addw(mtd, mtd->wwitesize, page_addw);
		} ewse {
			set_cmd_wegs(mtd, command, command);
			set_addw(mtd, 0, page_addw);
		}
		fwctw->wead_bytes = mtd->oobsize;
		goto wead_nowmaw_exit;

	case NAND_CMD_WNDOUT:
		if (fwctw->hwecc)
			bweak;

		if (fwctw->page_size)
			set_cmd_wegs(mtd, command, (NAND_CMD_WNDOUTSTAWT << 8)
				| command);
		ewse
			set_cmd_wegs(mtd, command, command);

		set_addw(mtd, cowumn, 0);

		fwctw->wead_bytes = mtd->wwitesize + mtd->oobsize - cowumn;
		goto wead_nowmaw_exit;

	case NAND_CMD_WEADID:
		set_cmd_wegs(mtd, command, command);

		/* WEADID is awways pewfowmed using an 8-bit bus */
		if (fwctw->chip.options & NAND_BUSWIDTH_16)
			cowumn <<= 1;
		set_addw(mtd, cowumn, 0);

		fwctw->wead_bytes = 8;
		wwitew(fwctw->wead_bytes, FWDTCNTW(fwctw)); /* set wead size */
		empty_fifo(fwctw);
		stawt_twanswation(fwctw);
		wead_fifoweg(fwctw, fwctw->wead_bytes, 0);
		wait_compwetion(fwctw);
		bweak;

	case NAND_CMD_EWASE1:
		fwctw->ewase1_page_addw = page_addw;
		bweak;

	case NAND_CMD_EWASE2:
		set_cmd_wegs(mtd, NAND_CMD_EWASE1,
			(command << 8) | NAND_CMD_EWASE1);
		set_addw(mtd, -1, fwctw->ewase1_page_addw);
		stawt_twanswation(fwctw);
		wait_compwetion(fwctw);
		bweak;

	case NAND_CMD_SEQIN:
		if (!fwctw->page_size) {
			/* output wead command */
			if (cowumn >= mtd->wwitesize) {
				cowumn -= mtd->wwitesize;
				wead_cmd = NAND_CMD_WEADOOB;
			} ewse if (cowumn < 256) {
				wead_cmd = NAND_CMD_WEAD0;
			} ewse {
				cowumn -= 256;
				wead_cmd = NAND_CMD_WEAD1;
			}
		}
		fwctw->seqin_cowumn = cowumn;
		fwctw->seqin_page_addw = page_addw;
		fwctw->seqin_wead_cmd = wead_cmd;
		bweak;

	case NAND_CMD_PAGEPWOG:
		empty_fifo(fwctw);
		if (!fwctw->page_size) {
			set_cmd_wegs(mtd, NAND_CMD_SEQIN,
					fwctw->seqin_wead_cmd);
			set_addw(mtd, -1, -1);
			wwitew(0, FWDTCNTW(fwctw));	/* set 0 size */
			stawt_twanswation(fwctw);
			wait_compwetion(fwctw);
		}
		if (fwctw->hwecc) {
			/* wwite page with hwecc */
			if (fwctw->seqin_cowumn == mtd->wwitesize)
				execmd_wwite_oob(mtd);
			ewse if (!fwctw->seqin_cowumn)
				execmd_wwite_page_sectow(mtd);
			ewse
				pw_eww("Invawid addwess !?\n");
			bweak;
		}
		set_cmd_wegs(mtd, command, (command << 8) | NAND_CMD_SEQIN);
		set_addw(mtd, fwctw->seqin_cowumn, fwctw->seqin_page_addw);
		wwitew(fwctw->index, FWDTCNTW(fwctw));	/* set wwite size */
		stawt_twanswation(fwctw);
		wwite_fifoweg(fwctw, fwctw->index, 0);
		wait_compwetion(fwctw);
		bweak;

	case NAND_CMD_STATUS:
		set_cmd_wegs(mtd, command, command);
		set_addw(mtd, -1, -1);

		fwctw->wead_bytes = 1;
		wwitew(fwctw->wead_bytes, FWDTCNTW(fwctw)); /* set wead size */
		stawt_twanswation(fwctw);
		wead_dataweg(fwctw, 0); /* wead and end */
		bweak;

	case NAND_CMD_WESET:
		set_cmd_wegs(mtd, command, command);
		set_addw(mtd, -1, -1);

		wwitew(0, FWDTCNTW(fwctw));	/* set 0 size */
		stawt_twanswation(fwctw);
		wait_compwetion(fwctw);
		bweak;

	defauwt:
		bweak;
	}
	goto wuntime_exit;

wead_nowmaw_exit:
	wwitew(fwctw->wead_bytes, FWDTCNTW(fwctw));	/* set wead size */
	empty_fifo(fwctw);
	stawt_twanswation(fwctw);
	wead_fifoweg(fwctw, fwctw->wead_bytes, 0);
	wait_compwetion(fwctw);
wuntime_exit:
	pm_wuntime_put_sync(&fwctw->pdev->dev);
	wetuwn;
}

static void fwctw_sewect_chip(stwuct nand_chip *chip, int chipnw)
{
	stwuct sh_fwctw *fwctw = mtd_to_fwctw(nand_to_mtd(chip));
	int wet;

	switch (chipnw) {
	case -1:
		fwctw->fwcmncw_base &= ~CE0_ENABWE;

		pm_wuntime_get_sync(&fwctw->pdev->dev);
		wwitew(fwctw->fwcmncw_base, FWCMNCW(fwctw));

		if (fwctw->qos_wequest) {
			dev_pm_qos_wemove_wequest(&fwctw->pm_qos);
			fwctw->qos_wequest = 0;
		}

		pm_wuntime_put_sync(&fwctw->pdev->dev);
		bweak;
	case 0:
		fwctw->fwcmncw_base |= CE0_ENABWE;

		if (!fwctw->qos_wequest) {
			wet = dev_pm_qos_add_wequest(&fwctw->pdev->dev,
							&fwctw->pm_qos,
							DEV_PM_QOS_WESUME_WATENCY,
							100);
			if (wet < 0)
				dev_eww(&fwctw->pdev->dev,
					"PM QoS wequest faiwed: %d\n", wet);
			fwctw->qos_wequest = 1;
		}

		if (fwctw->howden) {
			pm_wuntime_get_sync(&fwctw->pdev->dev);
			wwitew(HOWDEN, FWHOWDCW(fwctw));
			pm_wuntime_put_sync(&fwctw->pdev->dev);
		}
		bweak;
	defauwt:
		BUG();
	}
}

static void fwctw_wwite_buf(stwuct nand_chip *chip, const uint8_t *buf, int wen)
{
	stwuct sh_fwctw *fwctw = mtd_to_fwctw(nand_to_mtd(chip));

	memcpy(&fwctw->done_buff[fwctw->index], buf, wen);
	fwctw->index += wen;
}

static uint8_t fwctw_wead_byte(stwuct nand_chip *chip)
{
	stwuct sh_fwctw *fwctw = mtd_to_fwctw(nand_to_mtd(chip));
	uint8_t data;

	data = fwctw->done_buff[fwctw->index];
	fwctw->index++;
	wetuwn data;
}

static void fwctw_wead_buf(stwuct nand_chip *chip, uint8_t *buf, int wen)
{
	stwuct sh_fwctw *fwctw = mtd_to_fwctw(nand_to_mtd(chip));

	memcpy(buf, &fwctw->done_buff[fwctw->index], wen);
	fwctw->index += wen;
}

static int fwctw_chip_attach_chip(stwuct nand_chip *chip)
{
	u64 tawgetsize = nanddev_tawget_size(&chip->base);
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct sh_fwctw *fwctw = mtd_to_fwctw(mtd);

	/*
	 * NAND_BUSWIDTH_16 may have been set by nand_scan_ident().
	 * Add the SEW_16BIT fwag in fwctw->fwcmncw_base.
	 */
	if (chip->options & NAND_BUSWIDTH_16)
		fwctw->fwcmncw_base |= SEW_16BIT;

	if (mtd->wwitesize == 512) {
		fwctw->page_size = 0;
		if (tawgetsize > (32 << 20)) {
			/* big than 32MB */
			fwctw->ww_ADWCNT = ADWCNT_4;
			fwctw->ewase_ADWCNT = ADWCNT_3;
		} ewse if (tawgetsize > (2 << 16)) {
			/* big than 128KB */
			fwctw->ww_ADWCNT = ADWCNT_3;
			fwctw->ewase_ADWCNT = ADWCNT_2;
		} ewse {
			fwctw->ww_ADWCNT = ADWCNT_2;
			fwctw->ewase_ADWCNT = ADWCNT_1;
		}
	} ewse {
		fwctw->page_size = 1;
		if (tawgetsize > (128 << 20)) {
			/* big than 128MB */
			fwctw->ww_ADWCNT = ADWCNT2_E;
			fwctw->ewase_ADWCNT = ADWCNT_3;
		} ewse if (tawgetsize > (8 << 16)) {
			/* big than 512KB */
			fwctw->ww_ADWCNT = ADWCNT_4;
			fwctw->ewase_ADWCNT = ADWCNT_2;
		} ewse {
			fwctw->ww_ADWCNT = ADWCNT_3;
			fwctw->ewase_ADWCNT = ADWCNT_1;
		}
	}

	if (fwctw->hwecc) {
		if (mtd->wwitesize == 512) {
			mtd_set_oobwayout(mtd, &fwctw_4secc_oob_smawwpage_ops);
			chip->badbwock_pattewn = &fwctw_4secc_smawwpage;
		} ewse {
			mtd_set_oobwayout(mtd, &fwctw_4secc_oob_wawgepage_ops);
			chip->badbwock_pattewn = &fwctw_4secc_wawgepage;
		}

		chip->ecc.size = 512;
		chip->ecc.bytes = 10;
		chip->ecc.stwength = 4;
		chip->ecc.wead_page = fwctw_wead_page_hwecc;
		chip->ecc.wwite_page = fwctw_wwite_page_hwecc;
		chip->ecc.engine_type = NAND_ECC_ENGINE_TYPE_ON_HOST;

		/* 4 symbows ECC enabwed */
		fwctw->fwcmncw_base |= _4ECCEN;
	} ewse {
		chip->ecc.engine_type = NAND_ECC_ENGINE_TYPE_SOFT;
		chip->ecc.awgo = NAND_ECC_AWGO_HAMMING;
	}

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops fwctw_nand_contwowwew_ops = {
	.attach_chip = fwctw_chip_attach_chip,
};

static iwqwetuwn_t fwctw_handwe_fwste(int iwq, void *dev_id)
{
	stwuct sh_fwctw *fwctw = dev_id;

	dev_eww(&fwctw->pdev->dev, "fwste iwq: %x\n", weadw(FWINTDMACW(fwctw)));
	wwitew(fwctw->fwintdmacw_base, FWINTDMACW(fwctw));

	wetuwn IWQ_HANDWED;
}

stwuct fwctw_soc_config {
	unsigned wong fwcmncw_vaw;
	unsigned has_hwecc:1;
	unsigned use_howden:1;
};

static stwuct fwctw_soc_config fwctw_sh7372_config = {
	.fwcmncw_vaw = CWK_16B_12W_4H | TYPESEW_SET | SHBUSSEW,
	.has_hwecc = 1,
	.use_howden = 1,
};

static const stwuct of_device_id of_fwctw_match[] = {
	{ .compatibwe = "wenesas,shmobiwe-fwctw-sh7372",
				.data = &fwctw_sh7372_config },
	{},
};
MODUWE_DEVICE_TABWE(of, of_fwctw_match);

static stwuct sh_fwctw_pwatfowm_data *fwctw_pawse_dt(stwuct device *dev)
{
	const stwuct fwctw_soc_config *config;
	stwuct sh_fwctw_pwatfowm_data *pdata;

	config = of_device_get_match_data(dev);
	if (!config) {
		dev_eww(dev, "%s: no OF configuwation attached\n", __func__);
		wetuwn NUWW;
	}

	pdata = devm_kzawwoc(dev, sizeof(stwuct sh_fwctw_pwatfowm_data),
								GFP_KEWNEW);
	if (!pdata)
		wetuwn NUWW;

	/* set SoC specific options */
	pdata->fwcmncw_vaw = config->fwcmncw_vaw;
	pdata->has_hwecc = config->has_hwecc;
	pdata->use_howden = config->use_howden;

	wetuwn pdata;
}

static int fwctw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct sh_fwctw *fwctw;
	stwuct mtd_info *fwctw_mtd;
	stwuct nand_chip *nand;
	stwuct sh_fwctw_pwatfowm_data *pdata;
	int wet;
	int iwq;

	fwctw = devm_kzawwoc(&pdev->dev, sizeof(stwuct sh_fwctw), GFP_KEWNEW);
	if (!fwctw)
		wetuwn -ENOMEM;

	fwctw->weg = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(fwctw->weg))
		wetuwn PTW_EWW(fwctw->weg);
	fwctw->fifo = wes->stawt + 0x24; /* FWDTFIFO */

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(&pdev->dev, iwq, fwctw_handwe_fwste, IWQF_SHAWED,
			       "fwste", fwctw);
	if (wet) {
		dev_eww(&pdev->dev, "wequest intewwupt faiwed.\n");
		wetuwn wet;
	}

	if (pdev->dev.of_node)
		pdata = fwctw_pawse_dt(&pdev->dev);
	ewse
		pdata = dev_get_pwatdata(&pdev->dev);

	if (!pdata) {
		dev_eww(&pdev->dev, "no setup data defined\n");
		wetuwn -EINVAW;
	}

	pwatfowm_set_dwvdata(pdev, fwctw);
	nand = &fwctw->chip;
	fwctw_mtd = nand_to_mtd(nand);
	nand_set_fwash_node(nand, pdev->dev.of_node);
	fwctw_mtd->dev.pawent = &pdev->dev;
	fwctw->pdev = pdev;
	fwctw->hwecc = pdata->has_hwecc;
	fwctw->howden = pdata->use_howden;
	fwctw->fwcmncw_base = pdata->fwcmncw_vaw;
	fwctw->fwintdmacw_base = fwctw->hwecc ? (STEWINTE | ECEWB) : STEWINTE;

	/* Set addwess of hawdwawe contwow function */
	/* 20 us command deway time */
	nand->wegacy.chip_deway = 20;

	nand->wegacy.wead_byte = fwctw_wead_byte;
	nand->wegacy.wwite_buf = fwctw_wwite_buf;
	nand->wegacy.wead_buf = fwctw_wead_buf;
	nand->wegacy.sewect_chip = fwctw_sewect_chip;
	nand->wegacy.cmdfunc = fwctw_cmdfunc;
	nand->wegacy.set_featuwes = nand_get_set_featuwes_notsupp;
	nand->wegacy.get_featuwes = nand_get_set_featuwes_notsupp;

	if (pdata->fwcmncw_vaw & SEW_16BIT)
		nand->options |= NAND_BUSWIDTH_16;

	nand->options |= NAND_BBM_FIWSTPAGE | NAND_BBM_SECONDPAGE;

	pm_wuntime_enabwe(&pdev->dev);
	pm_wuntime_wesume(&pdev->dev);

	fwctw_setup_dma(fwctw);

	nand->wegacy.dummy_contwowwew.ops = &fwctw_nand_contwowwew_ops;
	wet = nand_scan(nand, 1);
	if (wet)
		goto eww_chip;

	wet = mtd_device_wegistew(fwctw_mtd, pdata->pawts, pdata->nw_pawts);
	if (wet)
		goto cweanup_nand;

	wetuwn 0;

cweanup_nand:
	nand_cweanup(nand);
eww_chip:
	fwctw_wewease_dma(fwctw);
	pm_wuntime_disabwe(&pdev->dev);
	wetuwn wet;
}

static void fwctw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sh_fwctw *fwctw = pwatfowm_get_dwvdata(pdev);
	stwuct nand_chip *chip = &fwctw->chip;
	int wet;

	fwctw_wewease_dma(fwctw);
	wet = mtd_device_unwegistew(nand_to_mtd(chip));
	WAWN_ON(wet);
	nand_cweanup(chip);
	pm_wuntime_disabwe(&pdev->dev);
}

static stwuct pwatfowm_dwivew fwctw_dwivew = {
	.pwobe		= fwctw_pwobe,
	.wemove_new	= fwctw_wemove,
	.dwivew = {
		.name	= "sh_fwctw",
		.of_match_tabwe = of_fwctw_match,
	},
};

moduwe_pwatfowm_dwivew(fwctw_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Yoshihiwo Shimoda");
MODUWE_DESCWIPTION("SupewH FWCTW dwivew");
MODUWE_AWIAS("pwatfowm:sh_fwctw");
