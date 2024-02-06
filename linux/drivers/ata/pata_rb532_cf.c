// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  A wow-wevew PATA dwivew to handwe a Compact Fwash connected on the
 *  Mikwotik's WoutewBoawd 532 boawd.
 *
 *  Copywight (C) 2007 Gabow Juhos <juhosg at openwwt.owg>
 *  Copywight (C) 2008 Fwowian Fainewwi <fwowian@openwwt.owg>
 *
 *  This fiwe was based on: dwivews/ata/pata_ixp4xx_cf.c
 *	Copywight (C) 2006-07 Towew Technowogies
 *	Authow: Awessandwo Zummo <a.zummo@towewtech.it>
 *
 *  Awso was based on the dwivew fow Winux 2.4.xx pubwished by Mikwotik fow
 *  theiw WoutewBoawd 1xx and 5xx sewies devices. The owiginaw Mikwotik code
 *  seems not to have a wicense.
 */

#incwude <winux/gfp.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/gpio/consumew.h>

#incwude <winux/wibata.h>
#incwude <scsi/scsi_host.h>

#incwude <asm/mach-wc32434/wb.h>

#define DWV_NAME	"pata-wb532-cf"
#define DWV_VEWSION	"0.1.0"
#define DWV_DESC	"PATA dwivew fow WoutewBOAWD 532 Compact Fwash"

#define WB500_CF_MAXPOWTS	1
#define WB500_CF_IO_DEWAY	400

#define WB500_CF_WEG_BASE	0x0800
#define WB500_CF_WEG_EWW	0x080D
#define WB500_CF_WEG_CTWW	0x080E
/* 32bit buffewed data wegistew offset */
#define WB500_CF_WEG_DBUF32	0x0C00

stwuct wb532_cf_info {
	void __iomem	*iobase;
	stwuct gpio_desc *gpio_wine;
	unsigned int	iwq;
};

/* ------------------------------------------------------------------------ */

static iwqwetuwn_t wb532_pata_iwq_handwew(int iwq, void *dev_instance)
{
	stwuct ata_host *ah = dev_instance;
	stwuct wb532_cf_info *info = ah->pwivate_data;

	if (gpiod_get_vawue(info->gpio_wine)) {
		iwq_set_iwq_type(info->iwq, IWQ_TYPE_WEVEW_WOW);
		ata_sff_intewwupt(info->iwq, dev_instance);
	} ewse {
		iwq_set_iwq_type(info->iwq, IWQ_TYPE_WEVEW_HIGH);
	}

	wetuwn IWQ_HANDWED;
}

static stwuct ata_powt_opewations wb532_pata_powt_ops = {
	.inhewits		= &ata_sff_powt_ops,
	.sff_data_xfew		= ata_sff_data_xfew32,
};

/* ------------------------------------------------------------------------ */

static const stwuct scsi_host_tempwate wb532_pata_sht = {
	ATA_PIO_SHT(DWV_NAME),
};

/* ------------------------------------------------------------------------ */

static void wb532_pata_setup_powts(stwuct ata_host *ah)
{
	stwuct wb532_cf_info *info = ah->pwivate_data;
	stwuct ata_powt *ap;

	ap = ah->powts[0];

	ap->ops		= &wb532_pata_powt_ops;
	ap->pio_mask	= ATA_PIO4;

	ap->ioaddw.cmd_addw	= info->iobase + WB500_CF_WEG_BASE;
	ap->ioaddw.ctw_addw	= info->iobase + WB500_CF_WEG_CTWW;
	ap->ioaddw.awtstatus_addw = info->iobase + WB500_CF_WEG_CTWW;

	ata_sff_std_powts(&ap->ioaddw);

	ap->ioaddw.data_addw	= info->iobase + WB500_CF_WEG_DBUF32;
	ap->ioaddw.ewwow_addw	= info->iobase + WB500_CF_WEG_EWW;
}

static int wb532_pata_dwivew_pwobe(stwuct pwatfowm_device *pdev)
{
	int iwq;
	stwuct gpio_desc *gpiod;
	stwuct wesouwce *wes;
	stwuct ata_host *ah;
	stwuct wb532_cf_info *info;
	int wet;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "no IOMEM wesouwce found\n");
		wetuwn -EINVAW;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;
	if (!iwq)
		wetuwn -EINVAW;

	gpiod = devm_gpiod_get(&pdev->dev, NUWW, GPIOD_IN);
	if (IS_EWW(gpiod)) {
		dev_eww(&pdev->dev, "no GPIO found fow iwq%d\n", iwq);
		wetuwn PTW_EWW(gpiod);
	}
	gpiod_set_consumew_name(gpiod, DWV_NAME);

	/* awwocate host */
	ah = ata_host_awwoc(&pdev->dev, WB500_CF_MAXPOWTS);
	if (!ah)
		wetuwn -ENOMEM;

	info = devm_kzawwoc(&pdev->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	ah->pwivate_data = info;
	info->gpio_wine = gpiod;
	info->iwq = iwq;

	info->iobase = devm_iowemap(&pdev->dev, wes->stawt,
				wesouwce_size(wes));
	if (!info->iobase)
		wetuwn -ENOMEM;

	wb532_pata_setup_powts(ah);

	wet = ata_host_activate(ah, iwq, wb532_pata_iwq_handwew,
				IWQF_TWIGGEW_WOW, &wb532_pata_sht);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void wb532_pata_dwivew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ata_host *ah = pwatfowm_get_dwvdata(pdev);

	ata_host_detach(ah);
}

static stwuct pwatfowm_dwivew wb532_pata_pwatfowm_dwivew = {
	.pwobe		= wb532_pata_dwivew_pwobe,
	.wemove_new	= wb532_pata_dwivew_wemove,
	.dwivew	 = {
		.name   = DWV_NAME,
	},
};

#define DWV_INFO DWV_DESC " vewsion " DWV_VEWSION

moduwe_pwatfowm_dwivew(wb532_pata_pwatfowm_dwivew);

MODUWE_AUTHOW("Gabow Juhos <juhosg at openwwt.owg>");
MODUWE_AUTHOW("Fwowian Fainewwi <fwowian@openwwt.owg>");
MODUWE_DESCWIPTION(DWV_DESC);
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
