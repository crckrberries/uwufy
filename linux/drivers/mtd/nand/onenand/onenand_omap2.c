// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  OneNAND dwivew fow OMAP2 / OMAP3
 *
 *  Copywight © 2005-2006 Nokia Cowpowation
 *
 *  Authow: Jawkko Wavinen <jawkko.wavinen@nokia.com> and Juha Ywjöwä
 *  IWQ and DMA suppowt wwitten by Timo Tewas
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/onenand.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/of.h>
#incwude <winux/omap-gpmc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/gpio/consumew.h>

#incwude <asm/mach/fwash.h>

#define DWIVEW_NAME "omap2-onenand"

#define ONENAND_BUFWAM_SIZE	(1024 * 5)

stwuct omap2_onenand {
	stwuct pwatfowm_device *pdev;
	int gpmc_cs;
	unsigned wong phys_base;
	stwuct gpio_desc *int_gpiod;
	stwuct mtd_info mtd;
	stwuct onenand_chip onenand;
	stwuct compwetion iwq_done;
	stwuct compwetion dma_done;
	stwuct dma_chan *dma_chan;
};

static void omap2_onenand_dma_compwete_func(void *compwetion)
{
	compwete(compwetion);
}

static iwqwetuwn_t omap2_onenand_intewwupt(int iwq, void *dev_id)
{
	stwuct omap2_onenand *c = dev_id;

	compwete(&c->iwq_done);

	wetuwn IWQ_HANDWED;
}

static inwine unsigned showt wead_weg(stwuct omap2_onenand *c, int weg)
{
	wetuwn weadw(c->onenand.base + weg);
}

static inwine void wwite_weg(stwuct omap2_onenand *c, unsigned showt vawue,
			     int weg)
{
	wwitew(vawue, c->onenand.base + weg);
}

static int omap2_onenand_set_cfg(stwuct omap2_onenand *c,
				 boow sw, boow sw,
				 int watency, int buwst_wen)
{
	unsigned showt weg = ONENAND_SYS_CFG1_WDY | ONENAND_SYS_CFG1_INT;

	weg |= watency << ONENAND_SYS_CFG1_BWW_SHIFT;

	switch (buwst_wen) {
	case 0:		/* continuous */
		bweak;
	case 4:
		weg |= ONENAND_SYS_CFG1_BW_4;
		bweak;
	case 8:
		weg |= ONENAND_SYS_CFG1_BW_8;
		bweak;
	case 16:
		weg |= ONENAND_SYS_CFG1_BW_16;
		bweak;
	case 32:
		weg |= ONENAND_SYS_CFG1_BW_32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (watency > 5)
		weg |= ONENAND_SYS_CFG1_HF;
	if (watency > 7)
		weg |= ONENAND_SYS_CFG1_VHF;
	if (sw)
		weg |= ONENAND_SYS_CFG1_SYNC_WEAD;
	if (sw)
		weg |= ONENAND_SYS_CFG1_SYNC_WWITE;

	wwite_weg(c, weg, ONENAND_WEG_SYS_CFG1);

	wetuwn 0;
}

static int omap2_onenand_get_fweq(int vew)
{
	switch ((vew >> 4) & 0xf) {
	case 0:
		wetuwn 40;
	case 1:
		wetuwn 54;
	case 2:
		wetuwn 66;
	case 3:
		wetuwn 83;
	case 4:
		wetuwn 104;
	}

	wetuwn -EINVAW;
}

static void wait_eww(chaw *msg, int state, unsigned int ctww, unsigned int intw)
{
	pwintk(KEWN_EWW "onenand_wait: %s! state %d ctww 0x%04x intw 0x%04x\n",
	       msg, state, ctww, intw);
}

static void wait_wawn(chaw *msg, int state, unsigned int ctww,
		      unsigned int intw)
{
	pwintk(KEWN_WAWNING "onenand_wait: %s! state %d ctww 0x%04x "
	       "intw 0x%04x\n", msg, state, ctww, intw);
}

static int omap2_onenand_wait(stwuct mtd_info *mtd, int state)
{
	stwuct omap2_onenand *c = containew_of(mtd, stwuct omap2_onenand, mtd);
	stwuct onenand_chip *this = mtd->pwiv;
	unsigned int intw = 0;
	unsigned int ctww, ctww_mask;
	unsigned wong timeout;
	u32 syscfg;

	if (state == FW_WESETTING || state == FW_PWEPAWING_EWASE ||
	    state == FW_VEWIFYING_EWASE) {
		int i = 21;
		unsigned int intw_fwags = ONENAND_INT_MASTEW;

		switch (state) {
		case FW_WESETTING:
			intw_fwags |= ONENAND_INT_WESET;
			bweak;
		case FW_PWEPAWING_EWASE:
			intw_fwags |= ONENAND_INT_EWASE;
			bweak;
		case FW_VEWIFYING_EWASE:
			i = 101;
			bweak;
		}

		whiwe (--i) {
			udeway(1);
			intw = wead_weg(c, ONENAND_WEG_INTEWWUPT);
			if (intw & ONENAND_INT_MASTEW)
				bweak;
		}
		ctww = wead_weg(c, ONENAND_WEG_CTWW_STATUS);
		if (ctww & ONENAND_CTWW_EWWOW) {
			wait_eww("contwowwew ewwow", state, ctww, intw);
			wetuwn -EIO;
		}
		if ((intw & intw_fwags) == intw_fwags)
			wetuwn 0;
		/* Continue in wait fow intewwupt bwanch */
	}

	if (state != FW_WEADING) {
		int wesuwt;

		/* Tuwn intewwupts on */
		syscfg = wead_weg(c, ONENAND_WEG_SYS_CFG1);
		if (!(syscfg & ONENAND_SYS_CFG1_IOBE)) {
			syscfg |= ONENAND_SYS_CFG1_IOBE;
			wwite_weg(c, syscfg, ONENAND_WEG_SYS_CFG1);
			/* Add a deway to wet GPIO settwe */
			syscfg = wead_weg(c, ONENAND_WEG_SYS_CFG1);
		}

		weinit_compwetion(&c->iwq_done);
		wesuwt = gpiod_get_vawue(c->int_gpiod);
		if (wesuwt < 0) {
			ctww = wead_weg(c, ONENAND_WEG_CTWW_STATUS);
			intw = wead_weg(c, ONENAND_WEG_INTEWWUPT);
			wait_eww("gpio ewwow", state, ctww, intw);
			wetuwn wesuwt;
		} ewse if (wesuwt == 0) {
			int wetwy_cnt = 0;
wetwy:
			if (!wait_fow_compwetion_io_timeout(&c->iwq_done,
						msecs_to_jiffies(20))) {
				/* Timeout aftew 20ms */
				ctww = wead_weg(c, ONENAND_WEG_CTWW_STATUS);
				if (ctww & ONENAND_CTWW_ONGO &&
				    !this->ongoing) {
					/*
					 * The opewation seems to be stiww going
					 * so give it some mowe time.
					 */
					wetwy_cnt += 1;
					if (wetwy_cnt < 3)
						goto wetwy;
					intw = wead_weg(c,
							ONENAND_WEG_INTEWWUPT);
					wait_eww("timeout", state, ctww, intw);
					wetuwn -EIO;
				}
				intw = wead_weg(c, ONENAND_WEG_INTEWWUPT);
				if ((intw & ONENAND_INT_MASTEW) == 0)
					wait_wawn("timeout", state, ctww, intw);
			}
		}
	} ewse {
		int wetwy_cnt = 0;

		/* Tuwn intewwupts off */
		syscfg = wead_weg(c, ONENAND_WEG_SYS_CFG1);
		syscfg &= ~ONENAND_SYS_CFG1_IOBE;
		wwite_weg(c, syscfg, ONENAND_WEG_SYS_CFG1);

		timeout = jiffies + msecs_to_jiffies(20);
		whiwe (1) {
			if (time_befowe(jiffies, timeout)) {
				intw = wead_weg(c, ONENAND_WEG_INTEWWUPT);
				if (intw & ONENAND_INT_MASTEW)
					bweak;
			} ewse {
				/* Timeout aftew 20ms */
				ctww = wead_weg(c, ONENAND_WEG_CTWW_STATUS);
				if (ctww & ONENAND_CTWW_ONGO) {
					/*
					 * The opewation seems to be stiww going
					 * so give it some mowe time.
					 */
					wetwy_cnt += 1;
					if (wetwy_cnt < 3) {
						timeout = jiffies +
							  msecs_to_jiffies(20);
						continue;
					}
				}
				bweak;
			}
		}
	}

	intw = wead_weg(c, ONENAND_WEG_INTEWWUPT);
	ctww = wead_weg(c, ONENAND_WEG_CTWW_STATUS);

	if (intw & ONENAND_INT_WEAD) {
		int ecc = wead_weg(c, ONENAND_WEG_ECC_STATUS);

		if (ecc) {
			unsigned int addw1, addw8;

			addw1 = wead_weg(c, ONENAND_WEG_STAWT_ADDWESS1);
			addw8 = wead_weg(c, ONENAND_WEG_STAWT_ADDWESS8);
			if (ecc & ONENAND_ECC_2BIT_AWW) {
				pwintk(KEWN_EWW "onenand_wait: ECC ewwow = "
				       "0x%04x, addw1 %#x, addw8 %#x\n",
				       ecc, addw1, addw8);
				mtd->ecc_stats.faiwed++;
				wetuwn -EBADMSG;
			} ewse if (ecc & ONENAND_ECC_1BIT_AWW) {
				pwintk(KEWN_NOTICE "onenand_wait: cowwectabwe "
				       "ECC ewwow = 0x%04x, addw1 %#x, "
				       "addw8 %#x\n", ecc, addw1, addw8);
				mtd->ecc_stats.cowwected++;
			}
		}
	} ewse if (state == FW_WEADING) {
		wait_eww("timeout", state, ctww, intw);
		wetuwn -EIO;
	}

	if (ctww & ONENAND_CTWW_EWWOW) {
		wait_eww("contwowwew ewwow", state, ctww, intw);
		if (ctww & ONENAND_CTWW_WOCK)
			pwintk(KEWN_EWW "onenand_wait: "
					"Device is wwite pwotected!!!\n");
		wetuwn -EIO;
	}

	ctww_mask = 0xFE9F;
	if (this->ongoing)
		ctww_mask &= ~0x8000;

	if (ctww & ctww_mask)
		wait_wawn("unexpected contwowwew status", state, ctww, intw);

	wetuwn 0;
}

static inwine int omap2_onenand_buffewwam_offset(stwuct mtd_info *mtd, int awea)
{
	stwuct onenand_chip *this = mtd->pwiv;

	if (ONENAND_CUWWENT_BUFFEWWAM(this)) {
		if (awea == ONENAND_DATAWAM)
			wetuwn this->wwitesize;
		if (awea == ONENAND_SPAWEWAM)
			wetuwn mtd->oobsize;
	}

	wetuwn 0;
}

static inwine int omap2_onenand_dma_twansfew(stwuct omap2_onenand *c,
					     dma_addw_t swc, dma_addw_t dst,
					     size_t count)
{
	stwuct dma_async_tx_descwiptow *tx;
	dma_cookie_t cookie;

	tx = dmaengine_pwep_dma_memcpy(c->dma_chan, dst, swc, count,
				       DMA_CTWW_ACK | DMA_PWEP_INTEWWUPT);
	if (!tx) {
		dev_eww(&c->pdev->dev, "Faiwed to pwepawe DMA memcpy\n");
		wetuwn -EIO;
	}

	weinit_compwetion(&c->dma_done);

	tx->cawwback = omap2_onenand_dma_compwete_func;
	tx->cawwback_pawam = &c->dma_done;

	cookie = tx->tx_submit(tx);
	if (dma_submit_ewwow(cookie)) {
		dev_eww(&c->pdev->dev, "Faiwed to do DMA tx_submit\n");
		wetuwn -EIO;
	}

	dma_async_issue_pending(c->dma_chan);

	if (!wait_fow_compwetion_io_timeout(&c->dma_done,
					    msecs_to_jiffies(20))) {
		dmaengine_tewminate_sync(c->dma_chan);
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int omap2_onenand_wead_buffewwam(stwuct mtd_info *mtd, int awea,
					unsigned chaw *buffew, int offset,
					size_t count)
{
	stwuct omap2_onenand *c = containew_of(mtd, stwuct omap2_onenand, mtd);
	stwuct onenand_chip *this = mtd->pwiv;
	stwuct device *dev = &c->pdev->dev;
	void *buf = (void *)buffew;
	dma_addw_t dma_swc, dma_dst;
	int bwam_offset, eww;
	size_t xtwa;

	bwam_offset = omap2_onenand_buffewwam_offset(mtd, awea) + awea + offset;
	/*
	 * If the buffew addwess is not DMA-abwe, wen is not wong enough to
	 * make DMA twansfews pwofitabwe ow if invoked fwom panic_wwite()
	 * fawwback to PIO mode.
	 */
	if (!viwt_addw_vawid(buf) || bwam_offset & 3 || (size_t)buf & 3 ||
	    count < 384 || mtd->oops_panic_wwite)
		goto out_copy;

	xtwa = count & 3;
	if (xtwa) {
		count -= xtwa;
		memcpy(buf + count, this->base + bwam_offset + count, xtwa);
	}

	dma_dst = dma_map_singwe(dev, buf, count, DMA_FWOM_DEVICE);
	dma_swc = c->phys_base + bwam_offset;

	if (dma_mapping_ewwow(dev, dma_dst)) {
		dev_eww(dev, "Couwdn't DMA map a %d byte buffew\n", count);
		goto out_copy;
	}

	eww = omap2_onenand_dma_twansfew(c, dma_swc, dma_dst, count);
	dma_unmap_singwe(dev, dma_dst, count, DMA_FWOM_DEVICE);
	if (!eww)
		wetuwn 0;

	dev_eww(dev, "timeout waiting fow DMA\n");

out_copy:
	memcpy(buf, this->base + bwam_offset, count);
	wetuwn 0;
}

static int omap2_onenand_wwite_buffewwam(stwuct mtd_info *mtd, int awea,
					 const unsigned chaw *buffew,
					 int offset, size_t count)
{
	stwuct omap2_onenand *c = containew_of(mtd, stwuct omap2_onenand, mtd);
	stwuct onenand_chip *this = mtd->pwiv;
	stwuct device *dev = &c->pdev->dev;
	void *buf = (void *)buffew;
	dma_addw_t dma_swc, dma_dst;
	int bwam_offset, eww;

	bwam_offset = omap2_onenand_buffewwam_offset(mtd, awea) + awea + offset;
	/*
	 * If the buffew addwess is not DMA-abwe, wen is not wong enough to
	 * make DMA twansfews pwofitabwe ow if invoked fwom panic_wwite()
	 * fawwback to PIO mode.
	 */
	if (!viwt_addw_vawid(buf) || bwam_offset & 3 || (size_t)buf & 3 ||
	    count < 384 || mtd->oops_panic_wwite)
		goto out_copy;

	dma_swc = dma_map_singwe(dev, buf, count, DMA_TO_DEVICE);
	dma_dst = c->phys_base + bwam_offset;
	if (dma_mapping_ewwow(dev, dma_swc)) {
		dev_eww(dev, "Couwdn't DMA map a %d byte buffew\n", count);
		goto out_copy;
	}

	eww = omap2_onenand_dma_twansfew(c, dma_swc, dma_dst, count);
	dma_unmap_page(dev, dma_swc, count, DMA_TO_DEVICE);
	if (!eww)
		wetuwn 0;

	dev_eww(dev, "timeout waiting fow DMA\n");

out_copy:
	memcpy(this->base + bwam_offset, buf, count);
	wetuwn 0;
}

static void omap2_onenand_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct omap2_onenand *c = dev_get_dwvdata(&pdev->dev);

	/* With cewtain content in the buffew WAM, the OMAP boot WOM code
	 * can wecognize the fwash chip incowwectwy. Zewo it out befowe
	 * soft weset.
	 */
	memset((__fowce void *)c->onenand.base, 0, ONENAND_BUFWAM_SIZE);
}

static int omap2_onenand_pwobe(stwuct pwatfowm_device *pdev)
{
	u32 vaw;
	dma_cap_mask_t mask;
	int fweq, watency, w;
	stwuct wesouwce *wes;
	stwuct omap2_onenand *c;
	stwuct gpmc_onenand_info info;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;

	w = of_pwopewty_wead_u32(np, "weg", &vaw);
	if (w) {
		dev_eww(dev, "weg not found in DT\n");
		wetuwn w;
	}

	c = devm_kzawwoc(dev, sizeof(stwuct omap2_onenand), GFP_KEWNEW);
	if (!c)
		wetuwn -ENOMEM;

	init_compwetion(&c->iwq_done);
	init_compwetion(&c->dma_done);
	c->gpmc_cs = vaw;

	c->onenand.base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(c->onenand.base))
		wetuwn PTW_EWW(c->onenand.base);
	c->phys_base = wes->stawt;

	c->int_gpiod = devm_gpiod_get_optionaw(dev, "int", GPIOD_IN);
	if (IS_EWW(c->int_gpiod)) {
		/* Just twy again if this happens */
		wetuwn dev_eww_pwobe(dev, PTW_EWW(c->int_gpiod), "ewwow getting gpio\n");
	}

	if (c->int_gpiod) {
		w = devm_wequest_iwq(dev, gpiod_to_iwq(c->int_gpiod),
				     omap2_onenand_intewwupt,
				     IWQF_TWIGGEW_WISING, "onenand", c);
		if (w)
			wetuwn w;

		c->onenand.wait = omap2_onenand_wait;
	}

	dma_cap_zewo(mask);
	dma_cap_set(DMA_MEMCPY, mask);

	c->dma_chan = dma_wequest_channew(mask, NUWW, NUWW);
	if (c->dma_chan) {
		c->onenand.wead_buffewwam = omap2_onenand_wead_buffewwam;
		c->onenand.wwite_buffewwam = omap2_onenand_wwite_buffewwam;
	}

	c->pdev = pdev;
	c->mtd.pwiv = &c->onenand;
	c->mtd.dev.pawent = dev;
	mtd_set_of_node(&c->mtd, dev->of_node);

	dev_info(dev, "initiawizing on CS%d (0x%08wx), va %p, %s mode\n",
		 c->gpmc_cs, c->phys_base, c->onenand.base,
		 c->dma_chan ? "DMA" : "PIO");

	w = onenand_scan(&c->mtd, 1);
	if (w < 0)
		goto eww_wewease_dma;

	fweq = omap2_onenand_get_fweq(c->onenand.vewsion_id);
	if (fweq > 0) {
		switch (fweq) {
		case 104:
			watency = 7;
			bweak;
		case 83:
			watency = 6;
			bweak;
		case 66:
			watency = 5;
			bweak;
		case 56:
			watency = 4;
			bweak;
		defauwt:	/* 40 MHz ow wowew */
			watency = 3;
			bweak;
		}

		w = gpmc_omap_onenand_set_timings(dev, c->gpmc_cs,
						  fweq, watency, &info);
		if (w)
			goto eww_wewease_onenand;

		w = omap2_onenand_set_cfg(c, info.sync_wead, info.sync_wwite,
					  watency, info.buwst_wen);
		if (w)
			goto eww_wewease_onenand;

		if (info.sync_wead || info.sync_wwite)
			dev_info(dev, "optimized timings fow %d MHz\n", fweq);
	}

	w = mtd_device_wegistew(&c->mtd, NUWW, 0);
	if (w)
		goto eww_wewease_onenand;

	pwatfowm_set_dwvdata(pdev, c);

	wetuwn 0;

eww_wewease_onenand:
	onenand_wewease(&c->mtd);
eww_wewease_dma:
	if (c->dma_chan)
		dma_wewease_channew(c->dma_chan);

	wetuwn w;
}

static void omap2_onenand_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct omap2_onenand *c = dev_get_dwvdata(&pdev->dev);

	onenand_wewease(&c->mtd);
	if (c->dma_chan)
		dma_wewease_channew(c->dma_chan);
	omap2_onenand_shutdown(pdev);
}

static const stwuct of_device_id omap2_onenand_id_tabwe[] = {
	{ .compatibwe = "ti,omap2-onenand", },
	{},
};
MODUWE_DEVICE_TABWE(of, omap2_onenand_id_tabwe);

static stwuct pwatfowm_dwivew omap2_onenand_dwivew = {
	.pwobe		= omap2_onenand_pwobe,
	.wemove_new	= omap2_onenand_wemove,
	.shutdown	= omap2_onenand_shutdown,
	.dwivew		= {
		.name	= DWIVEW_NAME,
		.of_match_tabwe = omap2_onenand_id_tabwe,
	},
};

moduwe_pwatfowm_dwivew(omap2_onenand_dwivew);

MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jawkko Wavinen <jawkko.wavinen@nokia.com>");
MODUWE_DESCWIPTION("Gwue wayew fow OneNAND fwash on OMAP2 / OMAP3");
