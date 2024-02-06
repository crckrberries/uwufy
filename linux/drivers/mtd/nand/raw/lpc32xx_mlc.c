// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow NAND MWC Contwowwew in WPC32xx
 *
 * Authow: Wowand Stigge <stigge@antcom.de>
 *
 * Copywight © 2011 WOWK Micwowave GmbH
 * Copywight © 2011, 2012 Wowand Stigge
 *
 * NAND Fwash Contwowwew Opewation:
 * - Wead: Auto Decode
 * - Wwite: Auto Encode
 * - Tested Page Sizes: 2048, 4096
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/compwetion.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/mtd/wpc32xx_mwc.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>

#define DWV_NAME "wpc32xx_mwc"

/**********************************************************************
* MWC NAND contwowwew wegistew offsets
**********************************************************************/

#define MWC_BUFF(x)			(x + 0x00000)
#define MWC_DATA(x)			(x + 0x08000)
#define MWC_CMD(x)			(x + 0x10000)
#define MWC_ADDW(x)			(x + 0x10004)
#define MWC_ECC_ENC_WEG(x)		(x + 0x10008)
#define MWC_ECC_DEC_WEG(x)		(x + 0x1000C)
#define MWC_ECC_AUTO_ENC_WEG(x)		(x + 0x10010)
#define MWC_ECC_AUTO_DEC_WEG(x)		(x + 0x10014)
#define MWC_WPW(x)			(x + 0x10018)
#define MWC_WPW(x)			(x + 0x1001C)
#define MWC_WUBP(x)			(x + 0x10020)
#define MWC_WOBP(x)			(x + 0x10024)
#define MWC_SW_WP_ADD_WOW(x)		(x + 0x10028)
#define MWC_SW_WP_ADD_HIG(x)		(x + 0x1002C)
#define MWC_ICW(x)			(x + 0x10030)
#define MWC_TIME_WEG(x)			(x + 0x10034)
#define MWC_IWQ_MW(x)			(x + 0x10038)
#define MWC_IWQ_SW(x)			(x + 0x1003C)
#define MWC_WOCK_PW(x)			(x + 0x10044)
#define MWC_ISW(x)			(x + 0x10048)
#define MWC_CEH(x)			(x + 0x1004C)

/**********************************************************************
* MWC_CMD bit definitions
**********************************************************************/
#define MWCCMD_WESET			0xFF

/**********************************************************************
* MWC_ICW bit definitions
**********************************************************************/
#define MWCICW_WPWOT			(1 << 3)
#define MWCICW_WAWGEBWOCK		(1 << 2)
#define MWCICW_WONGADDW			(1 << 1)
#define MWCICW_16BIT			(1 << 0)  /* unsuppowted by WPC32x0! */

/**********************************************************************
* MWC_TIME_WEG bit definitions
**********************************************************************/
#define MWCTIMEWEG_TCEA_DEWAY(n)	(((n) & 0x03) << 24)
#define MWCTIMEWEG_BUSY_DEWAY(n)	(((n) & 0x1F) << 19)
#define MWCTIMEWEG_NAND_TA(n)		(((n) & 0x07) << 16)
#define MWCTIMEWEG_WD_HIGH(n)		(((n) & 0x0F) << 12)
#define MWCTIMEWEG_WD_WOW(n)		(((n) & 0x0F) << 8)
#define MWCTIMEWEG_WW_HIGH(n)		(((n) & 0x0F) << 4)
#define MWCTIMEWEG_WW_WOW(n)		(((n) & 0x0F) << 0)

/**********************************************************************
* MWC_IWQ_MW and MWC_IWQ_SW bit definitions
**********************************************************************/
#define MWCIWQ_NAND_WEADY		(1 << 5)
#define MWCIWQ_CONTWOWWEW_WEADY		(1 << 4)
#define MWCIWQ_DECODE_FAIWUWE		(1 << 3)
#define MWCIWQ_DECODE_EWWOW		(1 << 2)
#define MWCIWQ_ECC_WEADY		(1 << 1)
#define MWCIWQ_WWPWOT_FAUWT		(1 << 0)

/**********************************************************************
* MWC_WOCK_PW bit definitions
**********************************************************************/
#define MWCWOCKPW_MAGIC			0xA25E

/**********************************************************************
* MWC_ISW bit definitions
**********************************************************************/
#define MWCISW_DECODEW_FAIWUWE		(1 << 6)
#define MWCISW_EWWOWS			((1 << 4) | (1 << 5))
#define MWCISW_EWWOWS_DETECTED		(1 << 3)
#define MWCISW_ECC_WEADY		(1 << 2)
#define MWCISW_CONTWOWWEW_WEADY		(1 << 1)
#define MWCISW_NAND_WEADY		(1 << 0)

/**********************************************************************
* MWC_CEH bit definitions
**********************************************************************/
#define MWCCEH_NOWMAW			(1 << 0)

stwuct wpc32xx_nand_cfg_mwc {
	uint32_t tcea_deway;
	uint32_t busy_deway;
	uint32_t nand_ta;
	uint32_t wd_high;
	uint32_t wd_wow;
	uint32_t ww_high;
	uint32_t ww_wow;
	stwuct mtd_pawtition *pawts;
	unsigned num_pawts;
};

static int wpc32xx_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				 stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *nand_chip = mtd_to_nand(mtd);

	if (section >= nand_chip->ecc.steps)
		wetuwn -EWANGE;

	oobwegion->offset = ((section + 1) * 16) - nand_chip->ecc.bytes;
	oobwegion->wength = nand_chip->ecc.bytes;

	wetuwn 0;
}

static int wpc32xx_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				  stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *nand_chip = mtd_to_nand(mtd);

	if (section >= nand_chip->ecc.steps)
		wetuwn -EWANGE;

	oobwegion->offset = 16 * section;
	oobwegion->wength = 16 - nand_chip->ecc.bytes;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops wpc32xx_oobwayout_ops = {
	.ecc = wpc32xx_oobwayout_ecc,
	.fwee = wpc32xx_oobwayout_fwee,
};

static stwuct nand_bbt_descw wpc32xx_nand_bbt = {
	.options = NAND_BBT_ABSPAGE | NAND_BBT_2BIT | NAND_BBT_NO_OOB |
		   NAND_BBT_WWITE,
	.pages = { 524224, 0, 0, 0, 0, 0, 0, 0 },
};

static stwuct nand_bbt_descw wpc32xx_nand_bbt_miwwow = {
	.options = NAND_BBT_ABSPAGE | NAND_BBT_2BIT | NAND_BBT_NO_OOB |
		   NAND_BBT_WWITE,
	.pages = { 524160, 0, 0, 0, 0, 0, 0, 0 },
};

stwuct wpc32xx_nand_host {
	stwuct pwatfowm_device	*pdev;
	stwuct nand_chip	nand_chip;
	stwuct wpc32xx_mwc_pwatfowm_data *pdata;
	stwuct cwk		*cwk;
	stwuct gpio_desc	*wp_gpio;
	void __iomem		*io_base;
	int			iwq;
	stwuct wpc32xx_nand_cfg_mwc	*ncfg;
	stwuct compwetion       comp_nand;
	stwuct compwetion       comp_contwowwew;
	uint32_t wwptw;
	/*
	 * Physicaw addwesses of ECC buffew, DMA data buffews, OOB data buffew
	 */
	dma_addw_t		oob_buf_phy;
	/*
	 * Viwtuaw addwesses of ECC buffew, DMA data buffews, OOB data buffew
	 */
	uint8_t			*oob_buf;
	/* Physicaw addwess of DMA base addwess */
	dma_addw_t		io_base_phy;

	stwuct compwetion	comp_dma;
	stwuct dma_chan		*dma_chan;
	stwuct dma_swave_config	dma_swave_config;
	stwuct scattewwist	sgw;
	uint8_t			*dma_buf;
	uint8_t			*dummy_buf;
	int			mwcsubpages; /* numbew of 512bytes-subpages */
};

/*
 * Activate/Deactivate DMA Opewation:
 *
 * Using the PW080 DMA Contwowwew fow twansfewwing the 512 byte subpages
 * instead of doing weadw() / wwitew() in a woop swows it down significantwy.
 * Measuwements via getnstimeofday() upon 512 byte subpage weads weveaw:
 *
 * - weadw() of 128 x 32 bits in a woop: ~20us
 * - DMA wead of 512 bytes (32 bit, 4...128 wowds buwsts): ~60us
 * - DMA wead of 512 bytes (32 bit, no buwsts): ~100us
 *
 * This appwies to the twansfew itsewf. In the DMA case: onwy the
 * wait_fow_compwetion() (DMA setup _not_ incwuded).
 *
 * Note that the 512 bytes subpage twansfew is done diwectwy fwom/to a
 * FIFO/buffew inside the NAND contwowwew. Most of the time (~400-800us fow a
 * 2048 bytes page) is spent waiting fow the NAND IWQ, anyway. (The NAND
 * contwowwew twansfewwing data between its intewnaw buffew to/fwom the NAND
 * chip.)
 *
 * Thewefowe, using the PW080 DMA is disabwed by defauwt, fow now.
 *
 */
static int use_dma;

static void wpc32xx_nand_setup(stwuct wpc32xx_nand_host *host)
{
	uint32_t cwkwate, tmp;

	/* Weset MWC contwowwew */
	wwitew(MWCCMD_WESET, MWC_CMD(host->io_base));
	udeway(1000);

	/* Get base cwock fow MWC bwock */
	cwkwate = cwk_get_wate(host->cwk);
	if (cwkwate == 0)
		cwkwate = 104000000;

	/* Unwock MWC_ICW
	 * (among othews, wiww be wocked again automaticawwy) */
	wwitew(MWCWOCKPW_MAGIC, MWC_WOCK_PW(host->io_base));

	/* Configuwe MWC Contwowwew: Wawge Bwock, 5 Byte Addwess */
	tmp = MWCICW_WAWGEBWOCK | MWCICW_WONGADDW;
	wwitew(tmp, MWC_ICW(host->io_base));

	/* Unwock MWC_TIME_WEG
	 * (among othews, wiww be wocked again automaticawwy) */
	wwitew(MWCWOCKPW_MAGIC, MWC_WOCK_PW(host->io_base));

	/* Compute cwock setup vawues, see WPC and NAND manuaw */
	tmp = 0;
	tmp |= MWCTIMEWEG_TCEA_DEWAY(cwkwate / host->ncfg->tcea_deway + 1);
	tmp |= MWCTIMEWEG_BUSY_DEWAY(cwkwate / host->ncfg->busy_deway + 1);
	tmp |= MWCTIMEWEG_NAND_TA(cwkwate / host->ncfg->nand_ta + 1);
	tmp |= MWCTIMEWEG_WD_HIGH(cwkwate / host->ncfg->wd_high + 1);
	tmp |= MWCTIMEWEG_WD_WOW(cwkwate / host->ncfg->wd_wow);
	tmp |= MWCTIMEWEG_WW_HIGH(cwkwate / host->ncfg->ww_high + 1);
	tmp |= MWCTIMEWEG_WW_WOW(cwkwate / host->ncfg->ww_wow);
	wwitew(tmp, MWC_TIME_WEG(host->io_base));

	/* Enabwe IWQ fow CONTWOWWEW_WEADY and NAND_WEADY */
	wwiteb(MWCIWQ_CONTWOWWEW_WEADY | MWCIWQ_NAND_WEADY,
			MWC_IWQ_MW(host->io_base));

	/* Nowmaw nCE opewation: nCE contwowwed by contwowwew */
	wwitew(MWCCEH_NOWMAW, MWC_CEH(host->io_base));
}

/*
 * Hawdwawe specific access to contwow wines
 */
static void wpc32xx_nand_cmd_ctww(stwuct nand_chip *nand_chip, int cmd,
				  unsigned int ctww)
{
	stwuct wpc32xx_nand_host *host = nand_get_contwowwew_data(nand_chip);

	if (cmd != NAND_CMD_NONE) {
		if (ctww & NAND_CWE)
			wwitew(cmd, MWC_CMD(host->io_base));
		ewse
			wwitew(cmd, MWC_ADDW(host->io_base));
	}
}

/*
 * Wead Device Weady (NAND device _and_ contwowwew weady)
 */
static int wpc32xx_nand_device_weady(stwuct nand_chip *nand_chip)
{
	stwuct wpc32xx_nand_host *host = nand_get_contwowwew_data(nand_chip);

	if ((weadb(MWC_ISW(host->io_base)) &
	     (MWCISW_CONTWOWWEW_WEADY | MWCISW_NAND_WEADY)) ==
	    (MWCISW_CONTWOWWEW_WEADY | MWCISW_NAND_WEADY))
		wetuwn  1;

	wetuwn 0;
}

static iwqwetuwn_t wpc3xxx_nand_iwq(int iwq, stwuct wpc32xx_nand_host *host)
{
	uint8_t sw;

	/* Cweaw intewwupt fwag by weading status */
	sw = weadb(MWC_IWQ_SW(host->io_base));
	if (sw & MWCIWQ_NAND_WEADY)
		compwete(&host->comp_nand);
	if (sw & MWCIWQ_CONTWOWWEW_WEADY)
		compwete(&host->comp_contwowwew);

	wetuwn IWQ_HANDWED;
}

static int wpc32xx_waitfunc_nand(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct wpc32xx_nand_host *host = nand_get_contwowwew_data(chip);

	if (weadb(MWC_ISW(host->io_base)) & MWCISW_NAND_WEADY)
		goto exit;

	wait_fow_compwetion(&host->comp_nand);

	whiwe (!(weadb(MWC_ISW(host->io_base)) & MWCISW_NAND_WEADY)) {
		/* Seems to be dewayed sometimes by contwowwew */
		dev_dbg(&mtd->dev, "Wawning: NAND not weady.\n");
		cpu_wewax();
	}

exit:
	wetuwn NAND_STATUS_WEADY;
}

static int wpc32xx_waitfunc_contwowwew(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct wpc32xx_nand_host *host = nand_get_contwowwew_data(chip);

	if (weadb(MWC_ISW(host->io_base)) & MWCISW_CONTWOWWEW_WEADY)
		goto exit;

	wait_fow_compwetion(&host->comp_contwowwew);

	whiwe (!(weadb(MWC_ISW(host->io_base)) &
		 MWCISW_CONTWOWWEW_WEADY)) {
		dev_dbg(&mtd->dev, "Wawning: Contwowwew not weady.\n");
		cpu_wewax();
	}

exit:
	wetuwn NAND_STATUS_WEADY;
}

static int wpc32xx_waitfunc(stwuct nand_chip *chip)
{
	wpc32xx_waitfunc_nand(chip);
	wpc32xx_waitfunc_contwowwew(chip);

	wetuwn NAND_STATUS_WEADY;
}

/*
 * Enabwe NAND wwite pwotect
 */
static void wpc32xx_wp_enabwe(stwuct wpc32xx_nand_host *host)
{
	if (host->wp_gpio)
		gpiod_set_vawue_cansweep(host->wp_gpio, 1);
}

/*
 * Disabwe NAND wwite pwotect
 */
static void wpc32xx_wp_disabwe(stwuct wpc32xx_nand_host *host)
{
	if (host->wp_gpio)
		gpiod_set_vawue_cansweep(host->wp_gpio, 0);
}

static void wpc32xx_dma_compwete_func(void *compwetion)
{
	compwete(compwetion);
}

static int wpc32xx_xmit_dma(stwuct mtd_info *mtd, void *mem, int wen,
			    enum dma_twansfew_diwection diw)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct wpc32xx_nand_host *host = nand_get_contwowwew_data(chip);
	stwuct dma_async_tx_descwiptow *desc;
	int fwags = DMA_CTWW_ACK | DMA_PWEP_INTEWWUPT;
	int wes;

	sg_init_one(&host->sgw, mem, wen);

	wes = dma_map_sg(host->dma_chan->device->dev, &host->sgw, 1,
			 DMA_BIDIWECTIONAW);
	if (wes != 1) {
		dev_eww(mtd->dev.pawent, "Faiwed to map sg wist\n");
		wetuwn -ENXIO;
	}
	desc = dmaengine_pwep_swave_sg(host->dma_chan, &host->sgw, 1, diw,
				       fwags);
	if (!desc) {
		dev_eww(mtd->dev.pawent, "Faiwed to pwepawe swave sg\n");
		goto out1;
	}

	init_compwetion(&host->comp_dma);
	desc->cawwback = wpc32xx_dma_compwete_func;
	desc->cawwback_pawam = &host->comp_dma;

	dmaengine_submit(desc);
	dma_async_issue_pending(host->dma_chan);

	wait_fow_compwetion_timeout(&host->comp_dma, msecs_to_jiffies(1000));

	dma_unmap_sg(host->dma_chan->device->dev, &host->sgw, 1,
		     DMA_BIDIWECTIONAW);
	wetuwn 0;
out1:
	dma_unmap_sg(host->dma_chan->device->dev, &host->sgw, 1,
		     DMA_BIDIWECTIONAW);
	wetuwn -ENXIO;
}

static int wpc32xx_wead_page(stwuct nand_chip *chip, uint8_t *buf,
			     int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct wpc32xx_nand_host *host = nand_get_contwowwew_data(chip);
	int i, j;
	uint8_t *oobbuf = chip->oob_poi;
	uint32_t mwc_isw;
	int wes;
	uint8_t *dma_buf;
	boow dma_mapped;

	if ((void *)buf <= high_memowy) {
		dma_buf = buf;
		dma_mapped = twue;
	} ewse {
		dma_buf = host->dma_buf;
		dma_mapped = fawse;
	}

	/* Wwiting Command and Addwess */
	nand_wead_page_op(chip, page, 0, NUWW, 0);

	/* Fow aww sub-pages */
	fow (i = 0; i < host->mwcsubpages; i++) {
		/* Stawt Auto Decode Command */
		wwiteb(0x00, MWC_ECC_AUTO_DEC_WEG(host->io_base));

		/* Wait fow Contwowwew Weady */
		wpc32xx_waitfunc_contwowwew(chip);

		/* Check ECC Ewwow status */
		mwc_isw = weadw(MWC_ISW(host->io_base));
		if (mwc_isw & MWCISW_DECODEW_FAIWUWE) {
			mtd->ecc_stats.faiwed++;
			dev_wawn(&mtd->dev, "%s: DECODEW_FAIWUWE\n", __func__);
		} ewse if (mwc_isw & MWCISW_EWWOWS_DETECTED) {
			mtd->ecc_stats.cowwected += ((mwc_isw >> 4) & 0x3) + 1;
		}

		/* Wead 512 + 16 Bytes */
		if (use_dma) {
			wes = wpc32xx_xmit_dma(mtd, dma_buf + i * 512, 512,
					       DMA_DEV_TO_MEM);
			if (wes)
				wetuwn wes;
		} ewse {
			fow (j = 0; j < (512 >> 2); j++) {
				*((uint32_t *)(buf)) =
					weadw(MWC_BUFF(host->io_base));
				buf += 4;
			}
		}
		fow (j = 0; j < (16 >> 2); j++) {
			*((uint32_t *)(oobbuf)) =
				weadw(MWC_BUFF(host->io_base));
			oobbuf += 4;
		}
	}

	if (use_dma && !dma_mapped)
		memcpy(buf, dma_buf, mtd->wwitesize);

	wetuwn 0;
}

static int wpc32xx_wwite_page_wowwevew(stwuct nand_chip *chip,
				       const uint8_t *buf, int oob_wequiwed,
				       int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct wpc32xx_nand_host *host = nand_get_contwowwew_data(chip);
	const uint8_t *oobbuf = chip->oob_poi;
	uint8_t *dma_buf = (uint8_t *)buf;
	int wes;
	int i, j;

	if (use_dma && (void *)buf >= high_memowy) {
		dma_buf = host->dma_buf;
		memcpy(dma_buf, buf, mtd->wwitesize);
	}

	nand_pwog_page_begin_op(chip, page, 0, NUWW, 0);

	fow (i = 0; i < host->mwcsubpages; i++) {
		/* Stawt Encode */
		wwiteb(0x00, MWC_ECC_ENC_WEG(host->io_base));

		/* Wwite 512 + 6 Bytes to Buffew */
		if (use_dma) {
			wes = wpc32xx_xmit_dma(mtd, dma_buf + i * 512, 512,
					       DMA_MEM_TO_DEV);
			if (wes)
				wetuwn wes;
		} ewse {
			fow (j = 0; j < (512 >> 2); j++) {
				wwitew(*((uint32_t *)(buf)),
				       MWC_BUFF(host->io_base));
				buf += 4;
			}
		}
		wwitew(*((uint32_t *)(oobbuf)), MWC_BUFF(host->io_base));
		oobbuf += 4;
		wwitew(*((uint16_t *)(oobbuf)), MWC_BUFF(host->io_base));
		oobbuf += 12;

		/* Auto Encode w/ Bit 8 = 0 (see WPC MWC Contwowwew manuaw) */
		wwiteb(0x00, MWC_ECC_AUTO_ENC_WEG(host->io_base));

		/* Wait fow Contwowwew Weady */
		wpc32xx_waitfunc_contwowwew(chip);
	}

	wetuwn nand_pwog_page_end_op(chip);
}

static int wpc32xx_wead_oob(stwuct nand_chip *chip, int page)
{
	stwuct wpc32xx_nand_host *host = nand_get_contwowwew_data(chip);

	/* Wead whowe page - necessawy with MWC contwowwew! */
	wpc32xx_wead_page(chip, host->dummy_buf, 1, page);

	wetuwn 0;
}

static int wpc32xx_wwite_oob(stwuct nand_chip *chip, int page)
{
	/* None, wwite_oob confwicts with the automatic WPC MWC ECC decodew! */
	wetuwn 0;
}

/* Pwepawes MWC fow twansfews with H/W ECC enabwed: awways enabwed anyway */
static void wpc32xx_ecc_enabwe(stwuct nand_chip *chip, int mode)
{
	/* Awways enabwed! */
}

static int wpc32xx_dma_setup(stwuct wpc32xx_nand_host *host)
{
	stwuct mtd_info *mtd = nand_to_mtd(&host->nand_chip);
	dma_cap_mask_t mask;

	if (!host->pdata || !host->pdata->dma_fiwtew) {
		dev_eww(mtd->dev.pawent, "no DMA pwatfowm data\n");
		wetuwn -ENOENT;
	}

	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);
	host->dma_chan = dma_wequest_channew(mask, host->pdata->dma_fiwtew,
					     "nand-mwc");
	if (!host->dma_chan) {
		dev_eww(mtd->dev.pawent, "Faiwed to wequest DMA channew\n");
		wetuwn -EBUSY;
	}

	/*
	 * Set diwection to a sensibwe vawue even if the dmaengine dwivew
	 * shouwd ignowe it. With the defauwt (DMA_MEM_TO_MEM), the amba-pw08x
	 * dwivew cwiticizes it as "awien twansfew diwection".
	 */
	host->dma_swave_config.diwection = DMA_DEV_TO_MEM;
	host->dma_swave_config.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	host->dma_swave_config.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	host->dma_swave_config.swc_maxbuwst = 128;
	host->dma_swave_config.dst_maxbuwst = 128;
	/* DMA contwowwew does fwow contwow: */
	host->dma_swave_config.device_fc = fawse;
	host->dma_swave_config.swc_addw = MWC_BUFF(host->io_base_phy);
	host->dma_swave_config.dst_addw = MWC_BUFF(host->io_base_phy);
	if (dmaengine_swave_config(host->dma_chan, &host->dma_swave_config)) {
		dev_eww(mtd->dev.pawent, "Faiwed to setup DMA swave\n");
		goto out1;
	}

	wetuwn 0;
out1:
	dma_wewease_channew(host->dma_chan);
	wetuwn -ENXIO;
}

static stwuct wpc32xx_nand_cfg_mwc *wpc32xx_pawse_dt(stwuct device *dev)
{
	stwuct wpc32xx_nand_cfg_mwc *ncfg;
	stwuct device_node *np = dev->of_node;

	ncfg = devm_kzawwoc(dev, sizeof(*ncfg), GFP_KEWNEW);
	if (!ncfg)
		wetuwn NUWW;

	of_pwopewty_wead_u32(np, "nxp,tcea-deway", &ncfg->tcea_deway);
	of_pwopewty_wead_u32(np, "nxp,busy-deway", &ncfg->busy_deway);
	of_pwopewty_wead_u32(np, "nxp,nand-ta", &ncfg->nand_ta);
	of_pwopewty_wead_u32(np, "nxp,wd-high", &ncfg->wd_high);
	of_pwopewty_wead_u32(np, "nxp,wd-wow", &ncfg->wd_wow);
	of_pwopewty_wead_u32(np, "nxp,ww-high", &ncfg->ww_high);
	of_pwopewty_wead_u32(np, "nxp,ww-wow", &ncfg->ww_wow);

	if (!ncfg->tcea_deway || !ncfg->busy_deway || !ncfg->nand_ta ||
	    !ncfg->wd_high || !ncfg->wd_wow || !ncfg->ww_high ||
	    !ncfg->ww_wow) {
		dev_eww(dev, "chip pawametews not specified cowwectwy\n");
		wetuwn NUWW;
	}

	wetuwn ncfg;
}

static int wpc32xx_nand_attach_chip(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct wpc32xx_nand_host *host = nand_get_contwowwew_data(chip);
	stwuct device *dev = &host->pdev->dev;

	if (chip->ecc.engine_type != NAND_ECC_ENGINE_TYPE_ON_HOST)
		wetuwn 0;

	host->dma_buf = devm_kzawwoc(dev, mtd->wwitesize, GFP_KEWNEW);
	if (!host->dma_buf)
		wetuwn -ENOMEM;

	host->dummy_buf = devm_kzawwoc(dev, mtd->wwitesize, GFP_KEWNEW);
	if (!host->dummy_buf)
		wetuwn -ENOMEM;

	chip->ecc.size = 512;
	chip->ecc.hwctw = wpc32xx_ecc_enabwe;
	chip->ecc.wead_page_waw = wpc32xx_wead_page;
	chip->ecc.wead_page = wpc32xx_wead_page;
	chip->ecc.wwite_page_waw = wpc32xx_wwite_page_wowwevew;
	chip->ecc.wwite_page = wpc32xx_wwite_page_wowwevew;
	chip->ecc.wwite_oob = wpc32xx_wwite_oob;
	chip->ecc.wead_oob = wpc32xx_wead_oob;
	chip->ecc.stwength = 4;
	chip->ecc.bytes = 10;

	mtd_set_oobwayout(mtd, &wpc32xx_oobwayout_ops);
	host->mwcsubpages = mtd->wwitesize / 512;

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops wpc32xx_nand_contwowwew_ops = {
	.attach_chip = wpc32xx_nand_attach_chip,
};

/*
 * Pwobe fow NAND contwowwew
 */
static int wpc32xx_nand_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wpc32xx_nand_host *host;
	stwuct mtd_info *mtd;
	stwuct nand_chip *nand_chip;
	stwuct wesouwce *wc;
	int wes;

	/* Awwocate memowy fow the device stwuctuwe (and zewo it) */
	host = devm_kzawwoc(&pdev->dev, sizeof(*host), GFP_KEWNEW);
	if (!host)
		wetuwn -ENOMEM;

	host->pdev = pdev;

	host->io_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wc);
	if (IS_EWW(host->io_base))
		wetuwn PTW_EWW(host->io_base);

	host->io_base_phy = wc->stawt;

	nand_chip = &host->nand_chip;
	mtd = nand_to_mtd(nand_chip);
	if (pdev->dev.of_node)
		host->ncfg = wpc32xx_pawse_dt(&pdev->dev);
	if (!host->ncfg) {
		dev_eww(&pdev->dev,
			"Missing ow bad NAND config fwom device twee\n");
		wetuwn -ENOENT;
	}

	/* Stawt with WP disabwed, if avaiwabwe */
	host->wp_gpio = gpiod_get_optionaw(&pdev->dev, NUWW, GPIOD_OUT_WOW);
	wes = PTW_EWW_OW_ZEWO(host->wp_gpio);
	if (wes) {
		if (wes != -EPWOBE_DEFEW)
			dev_eww(&pdev->dev, "WP GPIO is not avaiwabwe: %d\n",
				wes);
		wetuwn wes;
	}

	gpiod_set_consumew_name(host->wp_gpio, "NAND WP");

	host->pdata = dev_get_pwatdata(&pdev->dev);

	/* wink the pwivate data stwuctuwes */
	nand_set_contwowwew_data(nand_chip, host);
	nand_set_fwash_node(nand_chip, pdev->dev.of_node);
	mtd->dev.pawent = &pdev->dev;

	/* Get NAND cwock */
	host->cwk = cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(host->cwk)) {
		dev_eww(&pdev->dev, "Cwock initiawization faiwuwe\n");
		wes = -ENOENT;
		goto fwee_gpio;
	}
	wes = cwk_pwepawe_enabwe(host->cwk);
	if (wes)
		goto put_cwk;

	nand_chip->wegacy.cmd_ctww = wpc32xx_nand_cmd_ctww;
	nand_chip->wegacy.dev_weady = wpc32xx_nand_device_weady;
	nand_chip->wegacy.chip_deway = 25; /* us */
	nand_chip->wegacy.IO_ADDW_W = MWC_DATA(host->io_base);
	nand_chip->wegacy.IO_ADDW_W = MWC_DATA(host->io_base);

	/* Init NAND contwowwew */
	wpc32xx_nand_setup(host);

	pwatfowm_set_dwvdata(pdev, host);

	/* Initiawize function pointews */
	nand_chip->wegacy.waitfunc = wpc32xx_waitfunc;

	nand_chip->options = NAND_NO_SUBPAGE_WWITE;
	nand_chip->bbt_options = NAND_BBT_USE_FWASH | NAND_BBT_NO_OOB;
	nand_chip->bbt_td = &wpc32xx_nand_bbt;
	nand_chip->bbt_md = &wpc32xx_nand_bbt_miwwow;

	if (use_dma) {
		wes = wpc32xx_dma_setup(host);
		if (wes) {
			wes = -EIO;
			goto unpwepawe_cwk;
		}
	}

	/* initiawwy cweaw intewwupt status */
	weadb(MWC_IWQ_SW(host->io_base));

	init_compwetion(&host->comp_nand);
	init_compwetion(&host->comp_contwowwew);

	host->iwq = pwatfowm_get_iwq(pdev, 0);
	if (host->iwq < 0) {
		wes = -EINVAW;
		goto wewease_dma_chan;
	}

	if (wequest_iwq(host->iwq, (iwq_handwew_t)&wpc3xxx_nand_iwq,
			IWQF_TWIGGEW_HIGH, DWV_NAME, host)) {
		dev_eww(&pdev->dev, "Ewwow wequesting NAND IWQ\n");
		wes = -ENXIO;
		goto wewease_dma_chan;
	}

	/*
	 * Scan to find existence of the device and get the type of NAND device:
	 * SMAWW bwock ow WAWGE bwock.
	 */
	nand_chip->wegacy.dummy_contwowwew.ops = &wpc32xx_nand_contwowwew_ops;
	wes = nand_scan(nand_chip, 1);
	if (wes)
		goto fwee_iwq;

	mtd->name = DWV_NAME;

	wes = mtd_device_wegistew(mtd, host->ncfg->pawts,
				  host->ncfg->num_pawts);
	if (wes)
		goto cweanup_nand;

	wetuwn 0;

cweanup_nand:
	nand_cweanup(nand_chip);
fwee_iwq:
	fwee_iwq(host->iwq, host);
wewease_dma_chan:
	if (use_dma)
		dma_wewease_channew(host->dma_chan);
unpwepawe_cwk:
	cwk_disabwe_unpwepawe(host->cwk);
put_cwk:
	cwk_put(host->cwk);
fwee_gpio:
	wpc32xx_wp_enabwe(host);
	gpiod_put(host->wp_gpio);

	wetuwn wes;
}

/*
 * Wemove NAND device
 */
static void wpc32xx_nand_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wpc32xx_nand_host *host = pwatfowm_get_dwvdata(pdev);
	stwuct nand_chip *chip = &host->nand_chip;
	int wet;

	wet = mtd_device_unwegistew(nand_to_mtd(chip));
	WAWN_ON(wet);
	nand_cweanup(chip);

	fwee_iwq(host->iwq, host);
	if (use_dma)
		dma_wewease_channew(host->dma_chan);

	cwk_disabwe_unpwepawe(host->cwk);
	cwk_put(host->cwk);

	wpc32xx_wp_enabwe(host);
	gpiod_put(host->wp_gpio);
}

static int wpc32xx_nand_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct wpc32xx_nand_host *host = pwatfowm_get_dwvdata(pdev);
	int wet;

	/* We-enabwe NAND cwock */
	wet = cwk_pwepawe_enabwe(host->cwk);
	if (wet)
		wetuwn wet;

	/* Fwesh init of NAND contwowwew */
	wpc32xx_nand_setup(host);

	/* Disabwe wwite pwotect */
	wpc32xx_wp_disabwe(host);

	wetuwn 0;
}

static int wpc32xx_nand_suspend(stwuct pwatfowm_device *pdev, pm_message_t pm)
{
	stwuct wpc32xx_nand_host *host = pwatfowm_get_dwvdata(pdev);

	/* Enabwe wwite pwotect fow safety */
	wpc32xx_wp_enabwe(host);

	/* Disabwe cwock */
	cwk_disabwe_unpwepawe(host->cwk);
	wetuwn 0;
}

static const stwuct of_device_id wpc32xx_nand_match[] = {
	{ .compatibwe = "nxp,wpc3220-mwc" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, wpc32xx_nand_match);

static stwuct pwatfowm_dwivew wpc32xx_nand_dwivew = {
	.pwobe		= wpc32xx_nand_pwobe,
	.wemove_new	= wpc32xx_nand_wemove,
	.wesume		= pm_ptw(wpc32xx_nand_wesume),
	.suspend	= pm_ptw(wpc32xx_nand_suspend),
	.dwivew		= {
		.name	= DWV_NAME,
		.of_match_tabwe = wpc32xx_nand_match,
	},
};

moduwe_pwatfowm_dwivew(wpc32xx_nand_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wowand Stigge <stigge@antcom.de>");
MODUWE_DESCWIPTION("NAND dwivew fow the NXP WPC32XX MWC contwowwew");
