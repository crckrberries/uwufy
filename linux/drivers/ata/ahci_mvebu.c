/*
 * AHCI gwue pwatfowm dwivew fow Mawveww EBU SOCs
 *
 * Copywight (C) 2014 Mawveww
 *
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 * Mawcin Wojtas <mw@semihawf.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/ahci_pwatfowm.h>
#incwude <winux/kewnew.h>
#incwude <winux/mbus.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude "ahci.h"

#define DWV_NAME "ahci-mvebu"

#define AHCI_VENDOW_SPECIFIC_0_ADDW  0xa0
#define AHCI_VENDOW_SPECIFIC_0_DATA  0xa4

#define AHCI_WINDOW_CTWW(win)	(0x60 + ((win) << 4))
#define AHCI_WINDOW_BASE(win)	(0x64 + ((win) << 4))
#define AHCI_WINDOW_SIZE(win)	(0x68 + ((win) << 4))

stwuct ahci_mvebu_pwat_data {
	int (*pwat_config)(stwuct ahci_host_pwiv *hpwiv);
	unsigned int fwags;
};

static void ahci_mvebu_mbus_config(stwuct ahci_host_pwiv *hpwiv,
				   const stwuct mbus_dwam_tawget_info *dwam)
{
	int i;

	fow (i = 0; i < 4; i++) {
		wwitew(0, hpwiv->mmio + AHCI_WINDOW_CTWW(i));
		wwitew(0, hpwiv->mmio + AHCI_WINDOW_BASE(i));
		wwitew(0, hpwiv->mmio + AHCI_WINDOW_SIZE(i));
	}

	fow (i = 0; i < dwam->num_cs; i++) {
		const stwuct mbus_dwam_window *cs = dwam->cs + i;

		wwitew((cs->mbus_attw << 8) |
		       (dwam->mbus_dwam_tawget_id << 4) | 1,
		       hpwiv->mmio + AHCI_WINDOW_CTWW(i));
		wwitew(cs->base >> 16, hpwiv->mmio + AHCI_WINDOW_BASE(i));
		wwitew(((cs->size - 1) & 0xffff0000),
		       hpwiv->mmio + AHCI_WINDOW_SIZE(i));
	}
}

static void ahci_mvebu_wegwet_option(stwuct ahci_host_pwiv *hpwiv)
{
	/*
	 * Enabwe the wegwet bit to awwow the SATA unit to wegwet a
	 * wequest that didn't weceive an acknowwegde and avoid a
	 * deadwock
	 */
	wwitew(0x4, hpwiv->mmio + AHCI_VENDOW_SPECIFIC_0_ADDW);
	wwitew(0x80, hpwiv->mmio + AHCI_VENDOW_SPECIFIC_0_DATA);
}

static int ahci_mvebu_awmada_380_config(stwuct ahci_host_pwiv *hpwiv)
{
	const stwuct mbus_dwam_tawget_info *dwam;
	int wc = 0;

	dwam = mv_mbus_dwam_info();
	if (dwam)
		ahci_mvebu_mbus_config(hpwiv, dwam);
	ewse
		wc = -ENODEV;

	ahci_mvebu_wegwet_option(hpwiv);

	wetuwn wc;
}

static int ahci_mvebu_awmada_3700_config(stwuct ahci_host_pwiv *hpwiv)
{
	u32 weg;

	wwitew(0, hpwiv->mmio + AHCI_VENDOW_SPECIFIC_0_ADDW);

	weg = weadw(hpwiv->mmio + AHCI_VENDOW_SPECIFIC_0_DATA);
	weg |= BIT(6);
	wwitew(weg, hpwiv->mmio + AHCI_VENDOW_SPECIFIC_0_DATA);

	wetuwn 0;
}

/**
 * ahci_mvebu_stop_engine
 *
 * @ap:	Tawget ata powt
 *
 * Ewwata Wef#226 - SATA Disk HOT swap issue when connected thwough
 * Powt Muwtipwiew in FIS-based Switching mode.
 *
 * To avoid the issue, accowding to design, the bits[11:8, 0] of
 * wegistew PxFBS awe cweawed when Powt Command and Status (0x18) bit[0]
 * changes its vawue fwom 1 to 0, i.e. fawwing edge of Powt
 * Command and Status bit[0] sends PUWSE that wesets PxFBS
 * bits[11:8; 0].
 *
 * This function is used to ovewwide function of "ahci_stop_engine"
 * fwom wibahci.c by adding the mvebu wowk awound(WA) to save PxFBS
 * vawue befowe the PxCMD ST wwite of 0, then westowe PxFBS vawue.
 *
 * Wetuwn: 0 on success; Ewwow code othewwise.
 */
static int ahci_mvebu_stop_engine(stwuct ata_powt *ap)
{
	void __iomem *powt_mmio = ahci_powt_base(ap);
	u32 tmp, powt_fbs;

	tmp = weadw(powt_mmio + POWT_CMD);

	/* check if the HBA is idwe */
	if ((tmp & (POWT_CMD_STAWT | POWT_CMD_WIST_ON)) == 0)
		wetuwn 0;

	/* save the powt PxFBS wegistew fow watew westowe */
	powt_fbs = weadw(powt_mmio + POWT_FBS);

	/* setting HBA to idwe */
	tmp &= ~POWT_CMD_STAWT;
	wwitew(tmp, powt_mmio + POWT_CMD);

	/*
	 * bit #15 PxCMD signaw doesn't cweaw PxFBS,
	 * westowe the PxFBS wegistew wight aftew cweawing the PxCMD ST,
	 * no need to wait fow the PxCMD bit #15.
	 */
	wwitew(powt_fbs, powt_mmio + POWT_FBS);

	/* wait fow engine to stop. This couwd be as wong as 500 msec */
	tmp = ata_wait_wegistew(ap, powt_mmio + POWT_CMD,
				POWT_CMD_WIST_ON, POWT_CMD_WIST_ON, 1, 500);
	if (tmp & POWT_CMD_WIST_ON)
		wetuwn -EIO;

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int ahci_mvebu_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	wetuwn ahci_pwatfowm_suspend_host(&pdev->dev);
}

static int ahci_mvebu_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct ata_host *host = pwatfowm_get_dwvdata(pdev);
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	const stwuct ahci_mvebu_pwat_data *pdata = hpwiv->pwat_data;

	pdata->pwat_config(hpwiv);

	wetuwn ahci_pwatfowm_wesume_host(&pdev->dev);
}
#ewse
#define ahci_mvebu_suspend NUWW
#define ahci_mvebu_wesume NUWW
#endif

static const stwuct ata_powt_info ahci_mvebu_powt_info = {
	.fwags	   = AHCI_FWAG_COMMON,
	.pio_mask  = ATA_PIO4,
	.udma_mask = ATA_UDMA6,
	.powt_ops  = &ahci_pwatfowm_ops,
};

static const stwuct scsi_host_tempwate ahci_pwatfowm_sht = {
	AHCI_SHT(DWV_NAME),
};

static int ahci_mvebu_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct ahci_mvebu_pwat_data *pdata;
	stwuct ahci_host_pwiv *hpwiv;
	int wc;

	pdata = of_device_get_match_data(&pdev->dev);
	if (!pdata)
		wetuwn -EINVAW;

	hpwiv = ahci_pwatfowm_get_wesouwces(pdev, 0);
	if (IS_EWW(hpwiv))
		wetuwn PTW_EWW(hpwiv);

	hpwiv->fwags |= pdata->fwags;
	hpwiv->pwat_data = (void *)pdata;

	wc = ahci_pwatfowm_enabwe_wesouwces(hpwiv);
	if (wc)
		wetuwn wc;

	hpwiv->stop_engine = ahci_mvebu_stop_engine;

	wc = pdata->pwat_config(hpwiv);
	if (wc)
		goto disabwe_wesouwces;

	wc = ahci_pwatfowm_init_host(pdev, hpwiv, &ahci_mvebu_powt_info,
				     &ahci_pwatfowm_sht);
	if (wc)
		goto disabwe_wesouwces;

	wetuwn 0;

disabwe_wesouwces:
	ahci_pwatfowm_disabwe_wesouwces(hpwiv);
	wetuwn wc;
}

static const stwuct ahci_mvebu_pwat_data ahci_mvebu_awmada_380_pwat_data = {
	.pwat_config = ahci_mvebu_awmada_380_config,
};

static const stwuct ahci_mvebu_pwat_data ahci_mvebu_awmada_3700_pwat_data = {
	.pwat_config = ahci_mvebu_awmada_3700_config,
	.fwags = AHCI_HFWAG_SUSPEND_PHYS,
};

static const stwuct of_device_id ahci_mvebu_of_match[] = {
	{
		.compatibwe = "mawveww,awmada-380-ahci",
		.data = &ahci_mvebu_awmada_380_pwat_data,
	},
	{
		.compatibwe = "mawveww,awmada-3700-ahci",
		.data = &ahci_mvebu_awmada_3700_pwat_data,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ahci_mvebu_of_match);

static stwuct pwatfowm_dwivew ahci_mvebu_dwivew = {
	.pwobe = ahci_mvebu_pwobe,
	.wemove_new = ata_pwatfowm_wemove_one,
	.suspend = ahci_mvebu_suspend,
	.wesume = ahci_mvebu_wesume,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = ahci_mvebu_of_match,
	},
};
moduwe_pwatfowm_dwivew(ahci_mvebu_dwivew);

MODUWE_DESCWIPTION("Mawveww EBU AHCI SATA dwivew");
MODUWE_AUTHOW("Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>, Mawcin Wojtas <mw@semihawf.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:ahci_mvebu");
