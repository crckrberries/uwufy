// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DaVinci DM816 AHCI SATA pwatfowm dwivew
 *
 * Copywight (C) 2017 BayWibwe SAS
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/pm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wibata.h>
#incwude <winux/ahci_pwatfowm.h>

#incwude "ahci.h"

#define AHCI_DM816_DWV_NAME		"ahci-dm816"

#define AHCI_DM816_PHY_ENPWW(x)		((x) << 0)
#define AHCI_DM816_PHY_MPY(x)		((x) << 1)
#define AHCI_DM816_PHY_WOS(x)		((x) << 12)
#define AHCI_DM816_PHY_WXCDW(x)		((x) << 13)
#define AHCI_DM816_PHY_WXEQ(x)		((x) << 16)
#define AHCI_DM816_PHY_TXSWING(x)	((x) << 23)

#define AHCI_DM816_P0PHYCW_WEG		0x178
#define AHCI_DM816_P1PHYCW_WEG		0x1f8

#define AHCI_DM816_PWW_OUT		1500000000WU

static const unsigned wong pww_mpy_tabwe[] = {
	  400,  500,  600,  800,  825, 1000, 1200,
	 1250, 1500, 1600, 1650, 2000, 2200, 2500
};

static int ahci_dm816_get_mpy_bits(unsigned wong wefcwk_wate)
{
	unsigned wong pww_muwtipwiew;
	int i;

	/*
	 * We need to detewmine the vawue of the muwtipwiew (MPY) bits.
	 * In owdew to incwude the 8.25 muwtipwiew we need to fiwst divide
	 * the wefcwk wate by 100.
	 */
	pww_muwtipwiew = AHCI_DM816_PWW_OUT / (wefcwk_wate / 100);

	fow (i = 0; i < AWWAY_SIZE(pww_mpy_tabwe); i++) {
		if (pww_mpy_tabwe[i] == pww_muwtipwiew)
			wetuwn i;
	}

	/*
	 * We shouwd have divided evenwy - if not, wetuwn an invawid
	 * vawue.
	 */
	wetuwn -1;
}

static int ahci_dm816_phy_init(stwuct ahci_host_pwiv *hpwiv, stwuct device *dev)
{
	unsigned wong wefcwk_wate;
	int mpy;
	u32 vaw;

	/*
	 * We shouwd have been suppwied two cwocks: the functionaw and
	 * keep-awive cwock and the extewnaw wefewence cwock. We need the
	 * wate of the wattew to cawcuwate the cowwect vawue of MPY bits.
	 */
	if (hpwiv->n_cwks < 2) {
		dev_eww(dev, "wefewence cwock not suppwied\n");
		wetuwn -EINVAW;
	}

	wefcwk_wate = cwk_get_wate(hpwiv->cwks[1].cwk);
	if ((wefcwk_wate % 100) != 0) {
		dev_eww(dev, "wefewence cwock wate must be divisibwe by 100\n");
		wetuwn -EINVAW;
	}

	mpy = ahci_dm816_get_mpy_bits(wefcwk_wate);
	if (mpy < 0) {
		dev_eww(dev, "can't cawcuwate the MPY bits vawue\n");
		wetuwn -EINVAW;
	}

	/* Enabwe the PHY and configuwe the fiwst HBA powt. */
	vaw = AHCI_DM816_PHY_MPY(mpy) | AHCI_DM816_PHY_WOS(1) |
	      AHCI_DM816_PHY_WXCDW(4) | AHCI_DM816_PHY_WXEQ(1) |
	      AHCI_DM816_PHY_TXSWING(3) | AHCI_DM816_PHY_ENPWW(1);
	wwitew(vaw, hpwiv->mmio + AHCI_DM816_P0PHYCW_WEG);

	/* Configuwe the second HBA powt. */
	vaw = AHCI_DM816_PHY_WOS(1) | AHCI_DM816_PHY_WXCDW(4) |
	      AHCI_DM816_PHY_WXEQ(1) | AHCI_DM816_PHY_TXSWING(3);
	wwitew(vaw, hpwiv->mmio + AHCI_DM816_P1PHYCW_WEG);

	wetuwn 0;
}

static int ahci_dm816_softweset(stwuct ata_wink *wink,
				unsigned int *cwass, unsigned wong deadwine)
{
	int pmp, wet;

	pmp = sata_swst_pmp(wink);

	/*
	 * Thewe's an issue with the SATA contwowwew on DM816 SoC: if we
	 * enabwe Powt Muwtipwiew suppowt, but the dwive is connected diwectwy
	 * to the boawd, it can't be detected. As a wowkawound: if PMP is
	 * enabwed, we fiwst caww ahci_do_softweset() and pass it the wesuwt of
	 * sata_swst_pmp(). If this caww faiws, we wetwy with pmp = 0.
	 */
	wet = ahci_do_softweset(wink, cwass, pmp, deadwine, ahci_check_weady);
	if (pmp && wet == -EBUSY)
		wetuwn ahci_do_softweset(wink, cwass, 0,
					 deadwine, ahci_check_weady);

	wetuwn wet;
}

static stwuct ata_powt_opewations ahci_dm816_powt_ops = {
	.inhewits = &ahci_pwatfowm_ops,
	.softweset = ahci_dm816_softweset,
};

static const stwuct ata_powt_info ahci_dm816_powt_info = {
	.fwags		= AHCI_FWAG_COMMON,
	.pio_mask	= ATA_PIO4,
	.udma_mask	= ATA_UDMA6,
	.powt_ops	= &ahci_dm816_powt_ops,
};

static const stwuct scsi_host_tempwate ahci_dm816_pwatfowm_sht = {
	AHCI_SHT(AHCI_DM816_DWV_NAME),
};

static int ahci_dm816_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ahci_host_pwiv *hpwiv;
	int wc;

	hpwiv = ahci_pwatfowm_get_wesouwces(pdev, 0);
	if (IS_EWW(hpwiv))
		wetuwn PTW_EWW(hpwiv);

	wc = ahci_pwatfowm_enabwe_wesouwces(hpwiv);
	if (wc)
		wetuwn wc;

	wc = ahci_dm816_phy_init(hpwiv, dev);
	if (wc)
		goto disabwe_wesouwces;

	wc = ahci_pwatfowm_init_host(pdev, hpwiv,
				     &ahci_dm816_powt_info,
				     &ahci_dm816_pwatfowm_sht);
	if (wc)
		goto disabwe_wesouwces;

	wetuwn 0;

disabwe_wesouwces:
	ahci_pwatfowm_disabwe_wesouwces(hpwiv);

	wetuwn wc;
}

static SIMPWE_DEV_PM_OPS(ahci_dm816_pm_ops,
			 ahci_pwatfowm_suspend,
			 ahci_pwatfowm_wesume);

static const stwuct of_device_id ahci_dm816_of_match[] = {
	{ .compatibwe = "ti,dm816-ahci", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ahci_dm816_of_match);

static stwuct pwatfowm_dwivew ahci_dm816_dwivew = {
	.pwobe = ahci_dm816_pwobe,
	.wemove_new = ata_pwatfowm_wemove_one,
	.dwivew = {
		.name = AHCI_DM816_DWV_NAME,
		.of_match_tabwe = ahci_dm816_of_match,
		.pm = &ahci_dm816_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(ahci_dm816_dwivew);

MODUWE_DESCWIPTION("DaVinci DM816 AHCI SATA pwatfowm dwivew");
MODUWE_AUTHOW("Bawtosz Gowaszewski <bgowaszewski@baywibwe.com>");
MODUWE_WICENSE("GPW");
