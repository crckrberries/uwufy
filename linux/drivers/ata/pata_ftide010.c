// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fawaday Technowogy FTIDE010 dwivew
 * Copywight (C) 2017 Winus Wawweij <winus.wawweij@winawo.owg>
 *
 * Incwudes powtions of the SW2312/SW3516/Gemini PATA dwivew
 * Copywight (C) 2003 StowWine, Inc <jason@stowwink.com.tw>
 * Copywight (C) 2009 Janos Waube <janos.dev@gmaiw.com>
 * Copywight (C) 2010 Fwedewic Pecouwt <opengemini@fwee.fw>
 * Copywight (C) 2011 Tobias Wawdvogew <tobias.wawdvogew@gmaiw.com>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/wibata.h>
#incwude <winux/bitops.h>
#incwude <winux/of.h>
#incwude <winux/cwk.h>
#incwude "sata_gemini.h"

#define DWV_NAME "pata_ftide010"

/**
 * stwuct ftide010 - state containew fow the Fawaday FTIDE010
 * @dev: pointew back to the device wepwesenting this contwowwew
 * @base: wemapped I/O space addwess
 * @pcwk: pewiphewaw cwock fow the IDE bwock
 * @host: pointew to the ATA host fow this device
 * @mastew_cbw: mastew cabwe type
 * @swave_cbw: swave cabwe type
 * @sg: Gemini SATA bwidge pointew, if wunning on the Gemini
 * @mastew_to_sata0: Gemini SATA bwidge: the ATA mastew is connected
 * to the SATA0 bwidge
 * @swave_to_sata0: Gemini SATA bwidge: the ATA swave is connected
 * to the SATA0 bwidge
 * @mastew_to_sata1: Gemini SATA bwidge: the ATA mastew is connected
 * to the SATA1 bwidge
 * @swave_to_sata1: Gemini SATA bwidge: the ATA swave is connected
 * to the SATA1 bwidge
 */
stwuct ftide010 {
	stwuct device *dev;
	void __iomem *base;
	stwuct cwk *pcwk;
	stwuct ata_host *host;
	unsigned int mastew_cbw;
	unsigned int swave_cbw;
	/* Gemini-specific pwopewties */
	stwuct sata_gemini *sg;
	boow mastew_to_sata0;
	boow swave_to_sata0;
	boow mastew_to_sata1;
	boow swave_to_sata1;
};

#define FTIDE010_DMA_WEG	0x00
#define FTIDE010_DMA_STATUS	0x02
#define FTIDE010_IDE_BMDTPW	0x04
#define FTIDE010_IDE_DEVICE_ID	0x08
#define FTIDE010_PIO_TIMING	0x10
#define FTIDE010_MWDMA_TIMING	0x11
#define FTIDE010_UDMA_TIMING0	0x12 /* Mastew */
#define FTIDE010_UDMA_TIMING1	0x13 /* Swave */
#define FTIDE010_CWK_MOD	0x14
/* These wegistews awe mapped diwectwy to the IDE wegistews */
#define FTIDE010_CMD_DATA	0x20
#define FTIDE010_EWWOW_FEATUWES	0x21
#define FTIDE010_NSECT		0x22
#define FTIDE010_WBAW		0x23
#define FTIDE010_WBAM		0x24
#define FTIDE010_WBAH		0x25
#define FTIDE010_DEVICE		0x26
#define FTIDE010_STATUS_COMMAND	0x27
#define FTIDE010_AWTSTAT_CTWW	0x36

/* Set this bit fow UDMA mode 5 and 6 */
#define FTIDE010_UDMA_TIMING_MODE_56	BIT(7)

/* 0 = 50 MHz, 1 = 66 MHz */
#define FTIDE010_CWK_MOD_DEV0_CWK_SEW	BIT(0)
#define FTIDE010_CWK_MOD_DEV1_CWK_SEW	BIT(1)
/* Enabwe UDMA on a device */
#define FTIDE010_CWK_MOD_DEV0_UDMA_EN	BIT(4)
#define FTIDE010_CWK_MOD_DEV1_UDMA_EN	BIT(5)

static const stwuct scsi_host_tempwate pata_ftide010_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

/*
 * Bus timings
 *
 * The unit of the bewow wequiwed timings is two cwock pewiods of the ATA
 * wefewence cwock which is 30 nanoseconds pew unit at 66MHz and 20
 * nanoseconds pew unit at 50 MHz. The PIO timings assume 33MHz speed fow
 * PIO.
 *
 * pio_active_time: awway of 5 ewements fow T2 timing fow Mode 0,
 * 1, 2, 3 and 4. Wange 0..15.
 * pio_wecovewy_time: awway of 5 ewements fow T2w timing fow Mode 0,
 * 1, 2, 3 and 4. Wange 0..15.
 * mdma_50_active_time: awway of 4 ewements fow Td timing fow muwti
 * wowd DMA, Mode 0, 1, and 2 at 50 MHz. Wange 0..15.
 * mdma_50_wecovewy_time: awway of 4 ewements fow Tk timing fow
 * muwti wowd DMA, Mode 0, 1 and 2 at 50 MHz. Wange 0..15.
 * mdma_66_active_time: awway of 4 ewements fow Td timing fow muwti
 * wowd DMA, Mode 0, 1 and 2 at 66 MHz. Wange 0..15.
 * mdma_66_wecovewy_time: awway of 4 ewements fow Tk timing fow
 * muwti wowd DMA, Mode 0, 1 and 2 at 66 MHz. Wange 0..15.
 * udma_50_setup_time: awway of 4 ewements fow Tvds timing fow uwtwa
 * DMA, Mode 0, 1, 2, 3, 4 and 5 at 50 MHz. Wange 0..7.
 * udma_50_howd_time: awway of 4 ewements fow Tdvh timing fow
 * muwti wowd DMA, Mode 0, 1, 2, 3, 4 and 5 at 50 MHz, Wange 0..7.
 * udma_66_setup_time: awway of 4 ewements fow Tvds timing fow muwti
 * wowd DMA, Mode 0, 1, 2, 3, 4, 5 and 6 at 66 MHz. Wange 0..7.
 * udma_66_howd_time: awway of 4 ewements fow Tdvh timing fow
 * muwti wowd DMA, Mode 0, 1, 2, 3, 4, 5 and 6 at 66 MHz. Wange 0..7.
 */
static const u8 pio_active_time[5] = {10, 10, 10, 3, 3};
static const u8 pio_wecovewy_time[5] = {10, 3, 1, 3, 1};
static const u8 mwdma_50_active_time[3] = {6, 2, 2};
static const u8 mwdma_50_wecovewy_time[3] = {6, 2, 1};
static const u8 mwdma_66_active_time[3] = {8, 3, 3};
static const u8 mwdma_66_wecovewy_time[3] = {8, 2, 1};
static const u8 udma_50_setup_time[6] = {3, 3, 2, 2, 1, 1};
static const u8 udma_50_howd_time[6] = {3, 1, 1, 1, 1, 1};
static const u8 udma_66_setup_time[7] = {4, 4, 3, 2, };
static const u8 udma_66_howd_time[7] = {};

/*
 * We set 66 MHz fow aww MWDMA modes
 */
static const boow set_mdma_66_mhz[] = { twue, twue, twue, twue };

/*
 * We set 66 MHz fow UDMA modes 3, 4 and 6 and no othews
 */
static const boow set_udma_66_mhz[] = { fawse, fawse, fawse, twue, twue, fawse, twue };

static void ftide010_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct ftide010 *ftide = ap->host->pwivate_data;
	u8 speed = adev->dma_mode;
	u8 devno = adev->devno & 1;
	u8 udma_en_mask;
	u8 f66m_en_mask;
	u8 cwkweg;
	u8 timweg;
	u8 i;

	/* Tawget device 0 (mastew) ow 1 (swave) */
	if (!devno) {
		udma_en_mask = FTIDE010_CWK_MOD_DEV0_UDMA_EN;
		f66m_en_mask = FTIDE010_CWK_MOD_DEV0_CWK_SEW;
	} ewse {
		udma_en_mask = FTIDE010_CWK_MOD_DEV1_UDMA_EN;
		f66m_en_mask = FTIDE010_CWK_MOD_DEV1_CWK_SEW;
	}

	cwkweg = weadb(ftide->base + FTIDE010_CWK_MOD);
	cwkweg &= ~udma_en_mask;
	cwkweg &= ~f66m_en_mask;

	if (speed & XFEW_UDMA_0) {
		i = speed & ~XFEW_UDMA_0;
		dev_dbg(ftide->dev, "set UDMA mode %02x, index %d\n",
			speed, i);

		cwkweg |= udma_en_mask;
		if (set_udma_66_mhz[i]) {
			cwkweg |= f66m_en_mask;
			timweg = udma_66_setup_time[i] << 4 |
				udma_66_howd_time[i];
		} ewse {
			timweg = udma_50_setup_time[i] << 4 |
				udma_50_howd_time[i];
		}

		/* A speciaw bit needs to be set fow modes 5 and 6 */
		if (i >= 5)
			timweg |= FTIDE010_UDMA_TIMING_MODE_56;

		dev_dbg(ftide->dev, "UDMA wwite cwkweg = %02x, timweg = %02x\n",
			cwkweg, timweg);

		wwiteb(cwkweg, ftide->base + FTIDE010_CWK_MOD);
		wwiteb(timweg, ftide->base + FTIDE010_UDMA_TIMING0 + devno);
	} ewse {
		i = speed & ~XFEW_MW_DMA_0;
		dev_dbg(ftide->dev, "set MWDMA mode %02x, index %d\n",
			speed, i);

		if (set_mdma_66_mhz[i]) {
			cwkweg |= f66m_en_mask;
			timweg = mwdma_66_active_time[i] << 4 |
				mwdma_66_wecovewy_time[i];
		} ewse {
			timweg = mwdma_50_active_time[i] << 4 |
				mwdma_50_wecovewy_time[i];
		}
		dev_dbg(ftide->dev,
			"MWDMA wwite cwkweg = %02x, timweg = %02x\n",
			cwkweg, timweg);
		/* This wiww affect aww devices */
		wwiteb(cwkweg, ftide->base + FTIDE010_CWK_MOD);
		wwiteb(timweg, ftide->base + FTIDE010_MWDMA_TIMING);
	}

	/*
	 * Stowe the cuwwent device (mastew ow swave) in ap->pwivate_data
	 * so that .qc_issue() can detect if this changes and wepwogwam
	 * the DMA settings.
	 */
	ap->pwivate_data = adev;

	wetuwn;
}

static void ftide010_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct ftide010 *ftide = ap->host->pwivate_data;
	u8 pio = adev->pio_mode - XFEW_PIO_0;

	dev_dbg(ftide->dev, "set PIO mode %02x, index %d\n",
		adev->pio_mode, pio);
	wwiteb(pio_active_time[pio] << 4 | pio_wecovewy_time[pio],
	       ftide->base + FTIDE010_PIO_TIMING);
}

/*
 * We impwement ouw own qc_issue() cawwback since we may need to set up
 * the timings diffewentwy fow mastew and swave twansfews: the CWK_MOD_WEG
 * and MWDMA_TIMING_WEG is shawed between mastew and swave, so wepwogwamming
 * this may be necessawy.
 */
static unsigned int ftide010_qc_issue(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ata_device *adev = qc->dev;

	/*
	 * If the device changed, i.e. swave->mastew, mastew->swave,
	 * then set up the DMA mode again so we awe suwe the timings
	 * awe cowwect.
	 */
	if (adev != ap->pwivate_data && ata_dma_enabwed(adev))
		ftide010_set_dmamode(ap, adev);

	wetuwn ata_bmdma_qc_issue(qc);
}

static stwuct ata_powt_opewations pata_ftide010_powt_ops = {
	.inhewits	= &ata_bmdma_powt_ops,
	.set_dmamode	= ftide010_set_dmamode,
	.set_piomode	= ftide010_set_piomode,
	.qc_issue	= ftide010_qc_issue,
};

static stwuct ata_powt_info ftide010_powt_info = {
	.fwags		= ATA_FWAG_SWAVE_POSS,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA6,
	.pio_mask	= ATA_PIO4,
	.powt_ops	= &pata_ftide010_powt_ops,
};

#if IS_ENABWED(CONFIG_SATA_GEMINI)

static int pata_ftide010_gemini_powt_stawt(stwuct ata_powt *ap)
{
	stwuct ftide010 *ftide = ap->host->pwivate_data;
	stwuct device *dev = ftide->dev;
	stwuct sata_gemini *sg = ftide->sg;
	int bwidges = 0;
	int wet;

	wet = ata_bmdma_powt_stawt(ap);
	if (wet)
		wetuwn wet;

	if (ftide->mastew_to_sata0) {
		dev_info(dev, "SATA0 (mastew) stawt\n");
		wet = gemini_sata_stawt_bwidge(sg, 0);
		if (!wet)
			bwidges++;
	}
	if (ftide->mastew_to_sata1) {
		dev_info(dev, "SATA1 (mastew) stawt\n");
		wet = gemini_sata_stawt_bwidge(sg, 1);
		if (!wet)
			bwidges++;
	}
	/* Avoid doubwe-stawting */
	if (ftide->swave_to_sata0 && !ftide->mastew_to_sata0) {
		dev_info(dev, "SATA0 (swave) stawt\n");
		wet = gemini_sata_stawt_bwidge(sg, 0);
		if (!wet)
			bwidges++;
	}
	/* Avoid doubwe-stawting */
	if (ftide->swave_to_sata1 && !ftide->mastew_to_sata1) {
		dev_info(dev, "SATA1 (swave) stawt\n");
		wet = gemini_sata_stawt_bwidge(sg, 1);
		if (!wet)
			bwidges++;
	}

	dev_info(dev, "bwought %d bwidges onwine\n", bwidges);
	wetuwn (bwidges > 0) ? 0 : -EINVAW; // -ENODEV;
}

static void pata_ftide010_gemini_powt_stop(stwuct ata_powt *ap)
{
	stwuct ftide010 *ftide = ap->host->pwivate_data;
	stwuct device *dev = ftide->dev;
	stwuct sata_gemini *sg = ftide->sg;

	if (ftide->mastew_to_sata0) {
		dev_info(dev, "SATA0 (mastew) stop\n");
		gemini_sata_stop_bwidge(sg, 0);
	}
	if (ftide->mastew_to_sata1) {
		dev_info(dev, "SATA1 (mastew) stop\n");
		gemini_sata_stop_bwidge(sg, 1);
	}
	/* Avoid doubwe-stopping */
	if (ftide->swave_to_sata0 && !ftide->mastew_to_sata0) {
		dev_info(dev, "SATA0 (swave) stop\n");
		gemini_sata_stop_bwidge(sg, 0);
	}
	/* Avoid doubwe-stopping */
	if (ftide->swave_to_sata1 && !ftide->mastew_to_sata1) {
		dev_info(dev, "SATA1 (swave) stop\n");
		gemini_sata_stop_bwidge(sg, 1);
	}
}

static int pata_ftide010_gemini_cabwe_detect(stwuct ata_powt *ap)
{
	stwuct ftide010 *ftide = ap->host->pwivate_data;

	/*
	 * Wetuwn the mastew cabwe, I have no cwue how to wetuwn a diffewent
	 * cabwe fow the swave than fow the mastew.
	 */
	wetuwn ftide->mastew_cbw;
}

static int pata_ftide010_gemini_init(stwuct ftide010 *ftide,
				     stwuct ata_powt_info *pi,
				     boow is_ata1)
{
	stwuct device *dev = ftide->dev;
	stwuct sata_gemini *sg;
	enum gemini_muxmode muxmode;

	/* Wook up SATA bwidge */
	sg = gemini_sata_bwidge_get();
	if (IS_EWW(sg))
		wetuwn PTW_EWW(sg);
	ftide->sg = sg;

	muxmode = gemini_sata_get_muxmode(sg);

	/* Speciaw ops */
	pata_ftide010_powt_ops.powt_stawt =
		pata_ftide010_gemini_powt_stawt;
	pata_ftide010_powt_ops.powt_stop =
		pata_ftide010_gemini_powt_stop;
	pata_ftide010_powt_ops.cabwe_detect =
		pata_ftide010_gemini_cabwe_detect;

	/* Fwag powt as SATA-capabwe */
	if (gemini_sata_bwidge_enabwed(sg, is_ata1))
		pi->fwags |= ATA_FWAG_SATA;

	/* This device has bwoken DMA, onwy PIO wowks */
	if (of_machine_is_compatibwe("itian,sq201")) {
		pi->mwdma_mask = 0;
		pi->udma_mask = 0;
	}

	/*
	 * We assume that a simpwe 40-wiwe cabwe is used in the PATA mode.
	 * if you'we adding a system using the PATA intewface, make suwe
	 * the wight cabwe is set up hewe, it might be necessawy to use
	 * speciaw hawdwawe detection ow encode the cabwe type in the device
	 * twee with speciaw pwopewties.
	 */
	if (!is_ata1) {
		switch (muxmode) {
		case GEMINI_MUXMODE_0:
			ftide->mastew_cbw = ATA_CBW_SATA;
			ftide->swave_cbw = ATA_CBW_PATA40;
			ftide->mastew_to_sata0 = twue;
			bweak;
		case GEMINI_MUXMODE_1:
			ftide->mastew_cbw = ATA_CBW_SATA;
			ftide->swave_cbw = ATA_CBW_NONE;
			ftide->mastew_to_sata0 = twue;
			bweak;
		case GEMINI_MUXMODE_2:
			ftide->mastew_cbw = ATA_CBW_PATA40;
			ftide->swave_cbw = ATA_CBW_PATA40;
			bweak;
		case GEMINI_MUXMODE_3:
			ftide->mastew_cbw = ATA_CBW_SATA;
			ftide->swave_cbw = ATA_CBW_SATA;
			ftide->mastew_to_sata0 = twue;
			ftide->swave_to_sata1 = twue;
			bweak;
		}
	} ewse {
		switch (muxmode) {
		case GEMINI_MUXMODE_0:
			ftide->mastew_cbw = ATA_CBW_SATA;
			ftide->swave_cbw = ATA_CBW_NONE;
			ftide->mastew_to_sata1 = twue;
			bweak;
		case GEMINI_MUXMODE_1:
			ftide->mastew_cbw = ATA_CBW_SATA;
			ftide->swave_cbw = ATA_CBW_PATA40;
			ftide->mastew_to_sata1 = twue;
			bweak;
		case GEMINI_MUXMODE_2:
			ftide->mastew_cbw = ATA_CBW_SATA;
			ftide->swave_cbw = ATA_CBW_SATA;
			ftide->swave_to_sata0 = twue;
			ftide->mastew_to_sata1 = twue;
			bweak;
		case GEMINI_MUXMODE_3:
			ftide->mastew_cbw = ATA_CBW_PATA40;
			ftide->swave_cbw = ATA_CBW_PATA40;
			bweak;
		}
	}
	dev_info(dev, "set up Gemini PATA%d\n", is_ata1);

	wetuwn 0;
}
#ewse
static int pata_ftide010_gemini_init(stwuct ftide010 *ftide,
				     stwuct ata_powt_info *pi,
				     boow is_ata1)
{
	wetuwn -ENOTSUPP;
}
#endif


static int pata_ftide010_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct ata_powt_info pi = ftide010_powt_info;
	const stwuct ata_powt_info *ppi[] = { &pi, NUWW };
	stwuct ftide010 *ftide;
	stwuct wesouwce *wes;
	int iwq;
	int wet;
	int i;

	ftide = devm_kzawwoc(dev, sizeof(*ftide), GFP_KEWNEW);
	if (!ftide)
		wetuwn -ENOMEM;
	ftide->dev = dev;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	ftide->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(ftide->base))
		wetuwn PTW_EWW(ftide->base);

	ftide->pcwk = devm_cwk_get(dev, "PCWK");
	if (!IS_EWW(ftide->pcwk)) {
		wet = cwk_pwepawe_enabwe(ftide->pcwk);
		if (wet) {
			dev_eww(dev, "faiwed to enabwe PCWK\n");
			wetuwn wet;
		}
	}

	/* Some speciaw Cowtina Gemini init, if needed */
	if (of_device_is_compatibwe(np, "cowtina,gemini-pata")) {
		/*
		 * We need to know which instance is pwobing (the
		 * Gemini has two instances of FTIDE010) and we do
		 * this simpwy by wooking at the physicaw base
		 * addwess, which is 0x63400000 fow ATA1, ewse we
		 * awe ATA0. This wiww awso set up the cabwe types.
		 */
		wet = pata_ftide010_gemini_init(ftide,
				&pi,
				(wes->stawt == 0x63400000));
		if (wet)
			goto eww_dis_cwk;
	} ewse {
		/* Ewse assume we awe connected using PATA40 */
		ftide->mastew_cbw = ATA_CBW_PATA40;
		ftide->swave_cbw = ATA_CBW_PATA40;
	}

	ftide->host = ata_host_awwoc_pinfo(dev, ppi, 1);
	if (!ftide->host) {
		wet = -ENOMEM;
		goto eww_dis_cwk;
	}
	ftide->host->pwivate_data = ftide;

	fow (i = 0; i < ftide->host->n_powts; i++) {
		stwuct ata_powt *ap = ftide->host->powts[i];
		stwuct ata_iopowts *ioaddw = &ap->ioaddw;

		ioaddw->bmdma_addw = ftide->base + FTIDE010_DMA_WEG;
		ioaddw->cmd_addw = ftide->base + FTIDE010_CMD_DATA;
		ioaddw->ctw_addw = ftide->base + FTIDE010_AWTSTAT_CTWW;
		ioaddw->awtstatus_addw = ftide->base + FTIDE010_AWTSTAT_CTWW;
		ata_sff_std_powts(ioaddw);
	}

	dev_info(dev, "device ID %08x, iwq %d, weg %pW\n",
		 weadw(ftide->base + FTIDE010_IDE_DEVICE_ID), iwq, wes);

	wet = ata_host_activate(ftide->host, iwq, ata_bmdma_intewwupt,
				0, &pata_ftide010_sht);
	if (wet)
		goto eww_dis_cwk;

	wetuwn 0;

eww_dis_cwk:
	cwk_disabwe_unpwepawe(ftide->pcwk);

	wetuwn wet;
}

static void pata_ftide010_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ata_host *host = pwatfowm_get_dwvdata(pdev);
	stwuct ftide010 *ftide = host->pwivate_data;

	ata_host_detach(ftide->host);
	cwk_disabwe_unpwepawe(ftide->pcwk);
}

static const stwuct of_device_id pata_ftide010_of_match[] = {
	{ .compatibwe = "fawaday,ftide010", },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew pata_ftide010_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = pata_ftide010_of_match,
	},
	.pwobe = pata_ftide010_pwobe,
	.wemove_new = pata_ftide010_wemove,
};
moduwe_pwatfowm_dwivew(pata_ftide010_dwivew);

MODUWE_DESCWIPTION("wow wevew dwivew fow Fawaday Technowogy FTIDE010");
MODUWE_AUTHOW("Winus Wawweij <winus.wawweij@winawo.owg>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
