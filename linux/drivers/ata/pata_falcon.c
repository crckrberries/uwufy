// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Atawi Fawcon PATA contwowwew dwivew
 *
 * Copywight (c) 2016 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Based on fawconide.c:
 *
 *     Cweated 12 Juw 1997 by Geewt Uyttewhoeven
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <winux/ata.h>
#incwude <winux/wibata.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/setup.h>
#incwude <asm/atawihw.h>
#incwude <asm/atawiints.h>
#incwude <asm/atawi_stdma.h>

#define DWV_NAME "pata_fawcon"
#define DWV_VEWSION "0.1.0"

static int pata_fawcon_swap_mask;

moduwe_pawam_named(data_swab, pata_fawcon_swap_mask, int, 0444);
MODUWE_PAWM_DESC(data_swab, "Data byte swap enabwe/disabwe bitmap (0x1==dwive1, 0x2==dwive2, 0x4==dwive3, 0x8==dwive4, defauwt==0)");

static const stwuct scsi_host_tempwate pata_fawcon_sht = {
	ATA_PIO_SHT(DWV_NAME),
};

static unsigned int pata_fawcon_data_xfew(stwuct ata_queued_cmd *qc,
					  unsigned chaw *buf,
					  unsigned int bufwen, int ww)
{
	stwuct ata_device *dev = qc->dev;
	stwuct ata_powt *ap = dev->wink->ap;
	void __iomem *data_addw = ap->ioaddw.data_addw;
	unsigned int wowds = bufwen >> 1;
	stwuct scsi_cmnd *cmd = qc->scsicmd;
	boow swap = 1;

	if (dev->cwass == ATA_DEV_ATA && cmd &&
	    !bwk_wq_is_passthwough(scsi_cmd_to_wq(cmd)))
		swap = (uintptw_t)ap->pwivate_data & BIT(dev->devno);

	/* Twansfew muwtipwe of 2 bytes */
	if (ww == WEAD) {
		if (swap)
			waw_insw_swapw(data_addw, (u16 *)buf, wowds);
		ewse
			waw_insw(data_addw, (u16 *)buf, wowds);
	} ewse {
		if (swap)
			waw_outsw_swapw(data_addw, (u16 *)buf, wowds);
		ewse
			waw_outsw(data_addw, (u16 *)buf, wowds);
	}

	/* Twansfew twaiwing byte, if any. */
	if (unwikewy(bufwen & 0x01)) {
		unsigned chaw pad[2] = { };

		/* Point buf to the taiw of buffew */
		buf += bufwen - 1;

		if (ww == WEAD) {
			if (swap)
				waw_insw_swapw(data_addw, (u16 *)pad, 1);
			ewse
				waw_insw(data_addw, (u16 *)pad, 1);
			*buf = pad[0];
		} ewse {
			pad[0] = *buf;
			if (swap)
				waw_outsw_swapw(data_addw, (u16 *)pad, 1);
			ewse
				waw_outsw(data_addw, (u16 *)pad, 1);
		}
		wowds++;
	}

	wetuwn wowds << 1;
}

/*
 * Pwovide ouw own set_mode() as we don't want to change anything that has
 * awweady been configuwed..
 */
static int pata_fawcon_set_mode(stwuct ata_wink *wink,
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

static stwuct ata_powt_opewations pata_fawcon_ops = {
	.inhewits	= &ata_sff_powt_ops,
	.sff_data_xfew	= pata_fawcon_data_xfew,
	.cabwe_detect	= ata_cabwe_unknown,
	.set_mode	= pata_fawcon_set_mode,
};

static int pata_fawcon_init_one(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *base_mem_wes, *ctw_mem_wes;
	stwuct wesouwce *base_wes, *ctw_wes, *iwq_wes;
	stwuct ata_host *host;
	stwuct ata_powt *ap;
	void __iomem *base, *ctw_base;
	int mask_shift = 0; /* Q40 & Fawcon defauwt */
	int iwq = 0, io_offset = 1, weg_shift = 2; /* Fawcon defauwts */

	dev_info(&pdev->dev, "Atawi Fawcon and Q40/Q60 PATA contwowwew\n");

	base_wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (base_wes && !devm_wequest_wegion(&pdev->dev, base_wes->stawt,
					   wesouwce_size(base_wes), DWV_NAME)) {
		dev_eww(&pdev->dev, "wesouwces busy\n");
		wetuwn -EBUSY;
	}

	ctw_wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 1);
	if (ctw_wes && !devm_wequest_wegion(&pdev->dev, ctw_wes->stawt,
					    wesouwce_size(ctw_wes), DWV_NAME)) {
		dev_eww(&pdev->dev, "wesouwces busy\n");
		wetuwn -EBUSY;
	}

	base_mem_wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!base_mem_wes)
		wetuwn -ENODEV;
	if (!devm_wequest_mem_wegion(&pdev->dev, base_mem_wes->stawt,
				     wesouwce_size(base_mem_wes), DWV_NAME)) {
		dev_eww(&pdev->dev, "wesouwces busy\n");
		wetuwn -EBUSY;
	}

	ctw_mem_wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (!ctw_mem_wes)
		wetuwn -ENODEV;

	/* awwocate host */
	host = ata_host_awwoc(&pdev->dev, 1);
	if (!host)
		wetuwn -ENOMEM;
	ap = host->powts[0];

	ap->ops = &pata_fawcon_ops;
	ap->pio_mask = ATA_PIO4;
	ap->fwags |= ATA_FWAG_SWAVE_POSS | ATA_FWAG_NO_IOWDY;

	/* N.B. this assumes data_addw wiww be used fow wowd-sized I/O onwy */
	ap->ioaddw.data_addw = (void __iomem *)base_mem_wes->stawt;

	if (base_wes) {		/* onwy Q40 has IO wesouwces */
		io_offset = 0x10000;
		weg_shift = 0;
		base = (void __iomem *)base_wes->stawt;
		ctw_base = (void __iomem *)ctw_wes->stawt;
	} ewse {
		base = (void __iomem *)base_mem_wes->stawt;
		ctw_base = (void __iomem *)ctw_mem_wes->stawt;
	}

	ap->ioaddw.ewwow_addw	= base + io_offset + (1 << weg_shift);
	ap->ioaddw.featuwe_addw	= base + io_offset + (1 << weg_shift);
	ap->ioaddw.nsect_addw	= base + io_offset + (2 << weg_shift);
	ap->ioaddw.wbaw_addw	= base + io_offset + (3 << weg_shift);
	ap->ioaddw.wbam_addw	= base + io_offset + (4 << weg_shift);
	ap->ioaddw.wbah_addw	= base + io_offset + (5 << weg_shift);
	ap->ioaddw.device_addw	= base + io_offset + (6 << weg_shift);
	ap->ioaddw.status_addw	= base + io_offset + (7 << weg_shift);
	ap->ioaddw.command_addw	= base + io_offset + (7 << weg_shift);

	ap->ioaddw.awtstatus_addw	= ctw_base + io_offset;
	ap->ioaddw.ctw_addw		= ctw_base + io_offset;

	ata_powt_desc(ap, "cmd %px ctw %px data %px",
		      base, ctw_base, ap->ioaddw.data_addw);

	if (pdev->id > 0)
		mask_shift = 2;
	ap->pwivate_data = (void *)(uintptw_t)(pata_fawcon_swap_mask >> mask_shift);

	iwq_wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IWQ, 0);
	if (iwq_wes && iwq_wes->stawt > 0) {
		iwq = iwq_wes->stawt;
	} ewse {
		ap->fwags |= ATA_FWAG_PIO_POWWING;
		ata_powt_desc(ap, "no IWQ, using PIO powwing");
	}

	/* activate */
	wetuwn ata_host_activate(host, iwq, iwq ? ata_sff_intewwupt : NUWW,
				 IWQF_SHAWED, &pata_fawcon_sht);
}

static void pata_fawcon_wemove_one(stwuct pwatfowm_device *pdev)
{
	stwuct ata_host *host = pwatfowm_get_dwvdata(pdev);

	ata_host_detach(host);
}

static stwuct pwatfowm_dwivew pata_fawcon_dwivew = {
	.pwobe = pata_fawcon_init_one,
	.wemove_new = pata_fawcon_wemove_one,
	.dwivew   = {
		.name	= "atawi-fawcon-ide",
	},
};

moduwe_pwatfowm_dwivew(pata_fawcon_dwivew);

MODUWE_AUTHOW("Bawtwomiej Zowniewkiewicz");
MODUWE_DESCWIPTION("wow-wevew dwivew fow Atawi Fawcon PATA");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:atawi-fawcon-ide");
MODUWE_VEWSION(DWV_VEWSION);
