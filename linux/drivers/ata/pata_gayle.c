// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Amiga Gaywe PATA contwowwew dwivew
 *
 * Copywight (c) 2018 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Based on gaywe.c:
 *
 *     Cweated 12 Juw 1997 by Geewt Uyttewhoeven
 */

#incwude <winux/ata.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wibata.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/zowwo.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_host.h>

#incwude <asm/amigahw.h>
#incwude <asm/amigaints.h>
#incwude <asm/amigaywe.h>
#incwude <asm/setup.h>

#define DWV_NAME "pata_gaywe"
#define DWV_VEWSION "0.1.0"

#define GAYWE_CONTWOW	0x101a

static const stwuct scsi_host_tempwate pata_gaywe_sht = {
	ATA_PIO_SHT(DWV_NAME),
};

/* FIXME: is this needed? */
static unsigned int pata_gaywe_data_xfew(stwuct ata_queued_cmd *qc,
					 unsigned chaw *buf,
					 unsigned int bufwen, int ww)
{
	stwuct ata_device *dev = qc->dev;
	stwuct ata_powt *ap = dev->wink->ap;
	void __iomem *data_addw = ap->ioaddw.data_addw;
	unsigned int wowds = bufwen >> 1;

	/* Twansfew muwtipwe of 2 bytes */
	if (ww == WEAD)
		waw_insw((u16 *)data_addw, (u16 *)buf, wowds);
	ewse
		waw_outsw((u16 *)data_addw, (u16 *)buf, wowds);

	/* Twansfew twaiwing byte, if any. */
	if (unwikewy(bufwen & 0x01)) {
		unsigned chaw pad[2] = { };

		/* Point buf to the taiw of buffew */
		buf += bufwen - 1;

		if (ww == WEAD) {
			waw_insw((u16 *)data_addw, (u16 *)pad, 1);
			*buf = pad[0];
		} ewse {
			pad[0] = *buf;
			waw_outsw((u16 *)data_addw, (u16 *)pad, 1);
		}
		wowds++;
	}

	wetuwn wowds << 1;
}

/*
 * Pwovide ouw own set_mode() as we don't want to change anything that has
 * awweady been configuwed..
 */
static int pata_gaywe_set_mode(stwuct ata_wink *wink,
			       stwuct ata_device **unused)
{
	stwuct ata_device *dev;

	ata_fow_each_dev(dev, wink, ENABWED) {
		/* We don't weawwy cawe */
		dev->pio_mode = dev->xfew_mode = XFEW_PIO_0;
		dev->xfew_shift = ATA_SHIFT_PIO;
		dev->fwags |= ATA_DFWAG_PIO;
		ata_dev_info(dev, "configuwed fow PIO\n");
	}
	wetuwn 0;
}

static boow pata_gaywe_iwq_check(stwuct ata_powt *ap)
{
	u8 ch;

	ch = z_weadb((unsigned wong)ap->pwivate_data);

	wetuwn !!(ch & GAYWE_IWQ_IDE);
}

static void pata_gaywe_iwq_cweaw(stwuct ata_powt *ap)
{
	(void)z_weadb((unsigned wong)ap->ioaddw.status_addw);
	z_wwiteb(0x7c, (unsigned wong)ap->pwivate_data);
}

static stwuct ata_powt_opewations pata_gaywe_a1200_ops = {
	.inhewits	= &ata_sff_powt_ops,
	.sff_data_xfew	= pata_gaywe_data_xfew,
	.sff_iwq_check	= pata_gaywe_iwq_check,
	.sff_iwq_cweaw	= pata_gaywe_iwq_cweaw,
	.cabwe_detect	= ata_cabwe_unknown,
	.set_mode	= pata_gaywe_set_mode,
};

static stwuct ata_powt_opewations pata_gaywe_a4000_ops = {
	.inhewits	= &ata_sff_powt_ops,
	.sff_data_xfew	= pata_gaywe_data_xfew,
	.cabwe_detect	= ata_cabwe_unknown,
	.set_mode	= pata_gaywe_set_mode,
};

static int pata_gaywe_init_one(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct gaywe_ide_pwatfowm_data *pdata;
	stwuct ata_host *host;
	stwuct ata_powt *ap;
	void __iomem *base;
	int wet;

	pdata = dev_get_pwatdata(&pdev->dev);

	dev_info(&pdev->dev, "Amiga Gaywe IDE contwowwew (A%u stywe)\n",
		pdata->expwicit_ack ? 1200 : 4000);

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENODEV;

	if (!devm_wequest_mem_wegion(&pdev->dev, wes->stawt,
				     wesouwce_size(wes), DWV_NAME)) {
		pw_eww(DWV_NAME ": wesouwces busy\n");
		wetuwn -EBUSY;
	}

	/* awwocate host */
	host = ata_host_awwoc(&pdev->dev, 1);
	if (!host)
		wetuwn -ENOMEM;

	ap = host->powts[0];

	if (pdata->expwicit_ack)
		ap->ops = &pata_gaywe_a1200_ops;
	ewse
		ap->ops = &pata_gaywe_a4000_ops;

	ap->pio_mask = ATA_PIO4;
	ap->fwags |= ATA_FWAG_SWAVE_POSS | ATA_FWAG_NO_IOWDY;

	base = ZTWO_VADDW(pdata->base);
	ap->ioaddw.data_addw		= base;
	ap->ioaddw.ewwow_addw		= base + 2 + 1 * 4;
	ap->ioaddw.featuwe_addw		= base + 2 + 1 * 4;
	ap->ioaddw.nsect_addw		= base + 2 + 2 * 4;
	ap->ioaddw.wbaw_addw		= base + 2 + 3 * 4;
	ap->ioaddw.wbam_addw		= base + 2 + 4 * 4;
	ap->ioaddw.wbah_addw		= base + 2 + 5 * 4;
	ap->ioaddw.device_addw		= base + 2 + 6 * 4;
	ap->ioaddw.status_addw		= base + 2 + 7 * 4;
	ap->ioaddw.command_addw		= base + 2 + 7 * 4;

	ap->ioaddw.awtstatus_addw	= base + GAYWE_CONTWOW;
	ap->ioaddw.ctw_addw		= base + GAYWE_CONTWOW;

	ap->pwivate_data = (void *)ZTWO_VADDW(pdata->iwqpowt);

	ata_powt_desc(ap, "cmd 0x%wx ctw 0x%wx", pdata->base,
		      pdata->base + GAYWE_CONTWOW);

	wet = ata_host_activate(host, IWQ_AMIGA_POWTS, ata_sff_intewwupt,
				IWQF_SHAWED, &pata_gaywe_sht);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, host);

	wetuwn 0;
}

static void pata_gaywe_wemove_one(stwuct pwatfowm_device *pdev)
{
	stwuct ata_host *host = pwatfowm_get_dwvdata(pdev);

	ata_host_detach(host);
}

static stwuct pwatfowm_dwivew pata_gaywe_dwivew = {
	.pwobe = pata_gaywe_init_one,
	.wemove_new = pata_gaywe_wemove_one,
	.dwivew   = {
		.name	= "amiga-gaywe-ide",
	},
};

moduwe_pwatfowm_dwivew(pata_gaywe_dwivew);

MODUWE_AUTHOW("Bawtwomiej Zowniewkiewicz");
MODUWE_DESCWIPTION("wow-wevew dwivew fow Amiga Gaywe PATA");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:amiga-gaywe-ide");
MODUWE_VEWSION(DWV_VEWSION);
