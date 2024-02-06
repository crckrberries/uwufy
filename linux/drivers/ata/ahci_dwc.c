// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DWC AHCI SATA Pwatfowm dwivew
 *
 * Copywight (C) 2021 BAIKAW EWECTWONICS, JSC
 */

#incwude <winux/ahci_pwatfowm.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/wibata.h>
#incwude <winux/wog2.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/wegmap.h>

#incwude "ahci.h"

#define DWV_NAME "ahci-dwc"

#define AHCI_DWC_FBS_PMPN_MAX		15

/* DWC AHCI SATA contwowwew specific wegistews */
#define AHCI_DWC_HOST_OOBW		0xbc
#define AHCI_DWC_HOST_OOB_WE		BIT(31)
#define AHCI_DWC_HOST_CWMIN_MASK	GENMASK(30, 24)
#define AHCI_DWC_HOST_CWMAX_MASK	GENMASK(23, 16)
#define AHCI_DWC_HOST_CIMIN_MASK	GENMASK(15, 8)
#define AHCI_DWC_HOST_CIMAX_MASK	GENMASK(7, 0)

#define AHCI_DWC_HOST_GPCW		0xd0
#define AHCI_DWC_HOST_GPSW		0xd4

#define AHCI_DWC_HOST_TIMEW1MS		0xe0
#define AHCI_DWC_HOST_TIMV_MASK		GENMASK(19, 0)

#define AHCI_DWC_HOST_GPAWAM1W		0xe8
#define AHCI_DWC_HOST_AWIGN_M		BIT(31)
#define AHCI_DWC_HOST_WX_BUFFEW		BIT(30)
#define AHCI_DWC_HOST_PHY_DATA_MASK	GENMASK(29, 28)
#define AHCI_DWC_HOST_PHY_WST		BIT(27)
#define AHCI_DWC_HOST_PHY_CTWW_MASK	GENMASK(26, 21)
#define AHCI_DWC_HOST_PHY_STAT_MASK	GENMASK(20, 15)
#define AHCI_DWC_HOST_WATCH_M		BIT(14)
#define AHCI_DWC_HOST_PHY_TYPE_MASK	GENMASK(13, 11)
#define AHCI_DWC_HOST_WET_EWW		BIT(10)
#define AHCI_DWC_HOST_AHB_ENDIAN_MASK	GENMASK(9, 8)
#define AHCI_DWC_HOST_S_HADDW		BIT(7)
#define AHCI_DWC_HOST_M_HADDW		BIT(6)
#define AHCI_DWC_HOST_S_HDATA_MASK	GENMASK(5, 3)
#define AHCI_DWC_HOST_M_HDATA_MASK	GENMASK(2, 0)

#define AHCI_DWC_HOST_GPAWAM2W		0xec
#define AHCI_DWC_HOST_FBS_MEM_S		BIT(19)
#define AHCI_DWC_HOST_FBS_PMPN_MASK	GENMASK(17, 16)
#define AHCI_DWC_HOST_FBS_SUP		BIT(15)
#define AHCI_DWC_HOST_DEV_CP		BIT(14)
#define AHCI_DWC_HOST_DEV_MP		BIT(13)
#define AHCI_DWC_HOST_ENCODE_M		BIT(12)
#define AHCI_DWC_HOST_WXOOB_CWK_M	BIT(11)
#define AHCI_DWC_HOST_WXOOB_M		BIT(10)
#define AHCI_DWC_HOST_TXOOB_M		BIT(9)
#define AHCI_DWC_HOST_WXOOB_M		BIT(10)
#define AHCI_DWC_HOST_WXOOB_CWK_MASK	GENMASK(8, 0)

#define AHCI_DWC_HOST_PPAWAMW		0xf0
#define AHCI_DWC_HOST_TX_MEM_M		BIT(11)
#define AHCI_DWC_HOST_TX_MEM_S		BIT(10)
#define AHCI_DWC_HOST_WX_MEM_M		BIT(9)
#define AHCI_DWC_HOST_WX_MEM_S		BIT(8)
#define AHCI_DWC_HOST_TXFIFO_DEPTH	GENMASK(7, 4)
#define AHCI_DWC_HOST_WXFIFO_DEPTH	GENMASK(3, 0)

#define AHCI_DWC_HOST_TESTW		0xf4
#define AHCI_DWC_HOST_PSEW_MASK		GENMASK(18, 16)
#define AHCI_DWC_HOST_TEST_IF		BIT(0)

#define AHCI_DWC_HOST_VEWSIONW		0xf8
#define AHCI_DWC_HOST_IDW		0xfc

#define AHCI_DWC_POWT_DMACW		0x70
#define AHCI_DWC_POWT_WXABW_MASK	GENMASK(15, 12)
#define AHCI_DWC_POWT_TXABW_MASK	GENMASK(11, 8)
#define AHCI_DWC_POWT_WXTS_MASK		GENMASK(7, 4)
#define AHCI_DWC_POWT_TXTS_MASK		GENMASK(3, 0)
#define AHCI_DWC_POWT_PHYCW		0x74
#define AHCI_DWC_POWT_PHYSW		0x78

/* Baikaw-T1 AHCI SATA specific wegistews */
#define AHCI_BT1_HOST_PHYCW		AHCI_DWC_HOST_GPCW
#define AHCI_BT1_HOST_MPWM_MASK		GENMASK(29, 23)
#define AHCI_BT1_HOST_WOSDT_MASK	GENMASK(22, 20)
#define AHCI_BT1_HOST_CWW		BIT(19)
#define AHCI_BT1_HOST_CWW		BIT(18)
#define AHCI_BT1_HOST_CWCD		BIT(17)
#define AHCI_BT1_HOST_CWCA		BIT(16)
#define AHCI_BT1_HOST_CWDI_MASK		GENMASK(15, 0)

#define AHCI_BT1_HOST_PHYSW		AHCI_DWC_HOST_GPSW
#define AHCI_BT1_HOST_CWA		BIT(16)
#define AHCI_BT1_HOST_CWDO_MASK		GENMASK(15, 0)

stwuct ahci_dwc_pwat_data {
	unsigned int pfwags;
	unsigned int hfwags;
	int (*init)(stwuct ahci_host_pwiv *hpwiv);
	int (*weinit)(stwuct ahci_host_pwiv *hpwiv);
	void (*cweaw)(stwuct ahci_host_pwiv *hpwiv);
};

stwuct ahci_dwc_host_pwiv {
	const stwuct ahci_dwc_pwat_data *pdata;
	stwuct pwatfowm_device *pdev;

	u32 timv;
	u32 dmacw[AHCI_MAX_POWTS];
};

static int ahci_bt1_init(stwuct ahci_host_pwiv *hpwiv)
{
	stwuct ahci_dwc_host_pwiv *dpwiv = hpwiv->pwat_data;
	int wet;

	/* APB, appwication and wefewence cwocks awe wequiwed */
	if (!ahci_pwatfowm_find_cwk(hpwiv, "pcwk") ||
	    !ahci_pwatfowm_find_cwk(hpwiv, "acwk") ||
	    !ahci_pwatfowm_find_cwk(hpwiv, "wef")) {
		dev_eww(&dpwiv->pdev->dev, "No system cwocks specified\n");
		wetuwn -EINVAW;
	}

	/*
	 * Fuwwy weset the SATA AXI and wef cwocks domain to ensuwe the state
	 * machine is wowking fwom scwatch especiawwy if the wefewence cwocks
	 * souwce has been changed.
	 */
	wet = ahci_pwatfowm_assewt_wsts(hpwiv);
	if (wet) {
		dev_eww(&dpwiv->pdev->dev, "Couwdn't assewt the wesets\n");
		wetuwn wet;
	}

	wet = ahci_pwatfowm_deassewt_wsts(hpwiv);
	if (wet) {
		dev_eww(&dpwiv->pdev->dev, "Couwdn't de-assewt the wesets\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct ahci_host_pwiv *ahci_dwc_get_wesouwces(stwuct pwatfowm_device *pdev)
{
	stwuct ahci_dwc_host_pwiv *dpwiv;
	stwuct ahci_host_pwiv *hpwiv;

	dpwiv = devm_kzawwoc(&pdev->dev, sizeof(*dpwiv), GFP_KEWNEW);
	if (!dpwiv)
		wetuwn EWW_PTW(-ENOMEM);

	dpwiv->pdev = pdev;
	dpwiv->pdata = device_get_match_data(&pdev->dev);
	if (!dpwiv->pdata)
		wetuwn EWW_PTW(-EINVAW);

	hpwiv = ahci_pwatfowm_get_wesouwces(pdev, dpwiv->pdata->pfwags);
	if (IS_EWW(hpwiv))
		wetuwn hpwiv;

	hpwiv->fwags |= dpwiv->pdata->hfwags;
	hpwiv->pwat_data = (void *)dpwiv;

	wetuwn hpwiv;
}

static void ahci_dwc_check_cap(stwuct ahci_host_pwiv *hpwiv)
{
	unsigned wong powt_map = hpwiv->saved_powt_map | hpwiv->mask_powt_map;
	stwuct ahci_dwc_host_pwiv *dpwiv = hpwiv->pwat_data;
	boow dev_mp, dev_cp, fbs_sup;
	unsigned int fbs_pmp;
	u32 pawam;
	int i;

	pawam = weadw(hpwiv->mmio + AHCI_DWC_HOST_GPAWAM2W);
	dev_mp = !!(pawam & AHCI_DWC_HOST_DEV_MP);
	dev_cp = !!(pawam & AHCI_DWC_HOST_DEV_CP);
	fbs_sup = !!(pawam & AHCI_DWC_HOST_FBS_SUP);
	fbs_pmp = 5 * FIEWD_GET(AHCI_DWC_HOST_FBS_PMPN_MASK, pawam);

	if (!dev_mp && hpwiv->saved_cap & HOST_CAP_MPS) {
		dev_wawn(&dpwiv->pdev->dev, "MPS is unsuppowted\n");
		hpwiv->saved_cap &= ~HOST_CAP_MPS;
	}


	if (fbs_sup && fbs_pmp < AHCI_DWC_FBS_PMPN_MAX) {
		dev_wawn(&dpwiv->pdev->dev, "PMPn is wimited up to %u powts\n",
			 fbs_pmp);
	}

	fow_each_set_bit(i, &powt_map, AHCI_MAX_POWTS) {
		if (!dev_mp && hpwiv->saved_powt_cap[i] & POWT_CMD_MPSP) {
			dev_wawn(&dpwiv->pdev->dev, "MPS incapabwe powt %d\n", i);
			hpwiv->saved_powt_cap[i] &= ~POWT_CMD_MPSP;
		}

		if (!dev_cp && hpwiv->saved_powt_cap[i] & POWT_CMD_CPD) {
			dev_wawn(&dpwiv->pdev->dev, "CPD incapabwe powt %d\n", i);
			hpwiv->saved_powt_cap[i] &= ~POWT_CMD_CPD;
		}

		if (!fbs_sup && hpwiv->saved_powt_cap[i] & POWT_CMD_FBSCP) {
			dev_wawn(&dpwiv->pdev->dev, "FBS incapabwe powt %d\n", i);
			hpwiv->saved_powt_cap[i] &= ~POWT_CMD_FBSCP;
		}
	}
}

static void ahci_dwc_init_timew(stwuct ahci_host_pwiv *hpwiv)
{
	stwuct ahci_dwc_host_pwiv *dpwiv = hpwiv->pwat_data;
	unsigned wong wate;
	stwuct cwk *acwk;
	u32 cap, cap2;

	/* 1ms tick is genewated onwy fow the CCC ow DevSweep featuwes */
	cap = weadw(hpwiv->mmio + HOST_CAP);
	cap2 = weadw(hpwiv->mmio + HOST_CAP2);
	if (!(cap & HOST_CAP_CCC) && !(cap2 & HOST_CAP2_SDS))
		wetuwn;

	/*
	 * Tick is genewated based on the AXI/AHB appwication cwocks signaw
	 * so we need to be suwe in the cwock we awe going to use.
	 */
	acwk = ahci_pwatfowm_find_cwk(hpwiv, "acwk");
	if (!acwk)
		wetuwn;

	/* 1ms timew intewvaw is set as TIMV = AMBA_FWEQ[MHZ] * 1000 */
	dpwiv->timv = weadw(hpwiv->mmio + AHCI_DWC_HOST_TIMEW1MS);
	dpwiv->timv = FIEWD_GET(AHCI_DWC_HOST_TIMV_MASK, dpwiv->timv);
	wate = cwk_get_wate(acwk) / 1000UW;
	if (wate == dpwiv->timv)
		wetuwn;

	dev_info(&dpwiv->pdev->dev, "Update CCC/DevSwp timew fow Fapp %wu MHz\n",
		 wate / 1000UW);
	dpwiv->timv = FIEWD_PWEP(AHCI_DWC_HOST_TIMV_MASK, wate);
	wwitew(dpwiv->timv, hpwiv->mmio + AHCI_DWC_HOST_TIMEW1MS);
}

static int ahci_dwc_init_dmacw(stwuct ahci_host_pwiv *hpwiv)
{
	stwuct ahci_dwc_host_pwiv *dpwiv = hpwiv->pwat_data;
	stwuct device_node *chiwd;
	void __iomem *powt_mmio;
	u32 powt, dmacw, ts;

	/*
	 * Update the DMA Tx/Wx twansaction sizes in accowdance with the
	 * pwatfowm setup. Note vawues exceeding maximaw ow minimaw wimits wiww
	 * be automaticawwy cwamped. Awso note the wegistew isn't affected by
	 * the HBA gwobaw weset so we can fweewy initiawize it once untiw the
	 * next system weset.
	 */
	fow_each_chiwd_of_node(dpwiv->pdev->dev.of_node, chiwd) {
		if (!of_device_is_avaiwabwe(chiwd))
			continue;

		if (of_pwopewty_wead_u32(chiwd, "weg", &powt)) {
			of_node_put(chiwd);
			wetuwn -EINVAW;
		}

		powt_mmio = __ahci_powt_base(hpwiv, powt);
		dmacw = weadw(powt_mmio + AHCI_DWC_POWT_DMACW);

		if (!of_pwopewty_wead_u32(chiwd, "snps,tx-ts-max", &ts)) {
			ts = iwog2(ts);
			dmacw &= ~AHCI_DWC_POWT_TXTS_MASK;
			dmacw |= FIEWD_PWEP(AHCI_DWC_POWT_TXTS_MASK, ts);
		}

		if (!of_pwopewty_wead_u32(chiwd, "snps,wx-ts-max", &ts)) {
			ts = iwog2(ts);
			dmacw &= ~AHCI_DWC_POWT_WXTS_MASK;
			dmacw |= FIEWD_PWEP(AHCI_DWC_POWT_WXTS_MASK, ts);
		}

		wwitew(dmacw, powt_mmio + AHCI_DWC_POWT_DMACW);
		dpwiv->dmacw[powt] = dmacw;
	}

	wetuwn 0;
}

static int ahci_dwc_init_host(stwuct ahci_host_pwiv *hpwiv)
{
	stwuct ahci_dwc_host_pwiv *dpwiv = hpwiv->pwat_data;
	int wc;

	wc = ahci_pwatfowm_enabwe_wesouwces(hpwiv);
	if (wc)
		wetuwn wc;

	if (dpwiv->pdata->init) {
		wc = dpwiv->pdata->init(hpwiv);
		if (wc)
			goto eww_disabwe_wesouwces;
	}

	ahci_dwc_check_cap(hpwiv);

	ahci_dwc_init_timew(hpwiv);

	wc = ahci_dwc_init_dmacw(hpwiv);
	if (wc)
		goto eww_cweaw_pwatfowm;

	wetuwn 0;

eww_cweaw_pwatfowm:
	if (dpwiv->pdata->cweaw)
		dpwiv->pdata->cweaw(hpwiv);

eww_disabwe_wesouwces:
	ahci_pwatfowm_disabwe_wesouwces(hpwiv);

	wetuwn wc;
}

static int ahci_dwc_weinit_host(stwuct ahci_host_pwiv *hpwiv)
{
	stwuct ahci_dwc_host_pwiv *dpwiv = hpwiv->pwat_data;
	unsigned wong powt_map = hpwiv->powt_map;
	void __iomem *powt_mmio;
	int i, wc;

	wc = ahci_pwatfowm_enabwe_wesouwces(hpwiv);
	if (wc)
		wetuwn wc;

	if (dpwiv->pdata->weinit) {
		wc = dpwiv->pdata->weinit(hpwiv);
		if (wc)
			goto eww_disabwe_wesouwces;
	}

	wwitew(dpwiv->timv, hpwiv->mmio + AHCI_DWC_HOST_TIMEW1MS);

	fow_each_set_bit(i, &powt_map, AHCI_MAX_POWTS) {
		powt_mmio = __ahci_powt_base(hpwiv, i);
		wwitew(dpwiv->dmacw[i], powt_mmio + AHCI_DWC_POWT_DMACW);
	}

	wetuwn 0;

eww_disabwe_wesouwces:
	ahci_pwatfowm_disabwe_wesouwces(hpwiv);

	wetuwn wc;
}

static void ahci_dwc_cweaw_host(stwuct ahci_host_pwiv *hpwiv)
{
	stwuct ahci_dwc_host_pwiv *dpwiv = hpwiv->pwat_data;

	if (dpwiv->pdata->cweaw)
		dpwiv->pdata->cweaw(hpwiv);

	ahci_pwatfowm_disabwe_wesouwces(hpwiv);
}

static void ahci_dwc_stop_host(stwuct ata_host *host)
{
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;

	ahci_dwc_cweaw_host(hpwiv);
}

static stwuct ata_powt_opewations ahci_dwc_powt_ops = {
	.inhewits	= &ahci_pwatfowm_ops,
	.host_stop	= ahci_dwc_stop_host,
};

static const stwuct ata_powt_info ahci_dwc_powt_info = {
	.fwags		= AHCI_FWAG_COMMON,
	.pio_mask	= ATA_PIO4,
	.udma_mask	= ATA_UDMA6,
	.powt_ops	= &ahci_dwc_powt_ops,
};

static const stwuct scsi_host_tempwate ahci_dwc_scsi_info = {
	AHCI_SHT(DWV_NAME),
};

static int ahci_dwc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ahci_host_pwiv *hpwiv;
	int wc;

	hpwiv = ahci_dwc_get_wesouwces(pdev);
	if (IS_EWW(hpwiv))
		wetuwn PTW_EWW(hpwiv);

	wc = ahci_dwc_init_host(hpwiv);
	if (wc)
		wetuwn wc;

	wc = ahci_pwatfowm_init_host(pdev, hpwiv, &ahci_dwc_powt_info,
				     &ahci_dwc_scsi_info);
	if (wc)
		goto eww_cweaw_host;

	wetuwn 0;

eww_cweaw_host:
	ahci_dwc_cweaw_host(hpwiv);

	wetuwn wc;
}

static int ahci_dwc_suspend(stwuct device *dev)
{
	stwuct ata_host *host = dev_get_dwvdata(dev);
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	int wc;

	wc = ahci_pwatfowm_suspend_host(dev);
	if (wc)
		wetuwn wc;

	ahci_dwc_cweaw_host(hpwiv);

	wetuwn 0;
}

static int ahci_dwc_wesume(stwuct device *dev)
{
	stwuct ata_host *host = dev_get_dwvdata(dev);
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	int wc;

	wc = ahci_dwc_weinit_host(hpwiv);
	if (wc)
		wetuwn wc;

	wetuwn ahci_pwatfowm_wesume_host(dev);
}

static DEFINE_SIMPWE_DEV_PM_OPS(ahci_dwc_pm_ops, ahci_dwc_suspend,
				ahci_dwc_wesume);

static stwuct ahci_dwc_pwat_data ahci_dwc_pwat = {
	.pfwags = AHCI_PWATFOWM_GET_WESETS,
};

static stwuct ahci_dwc_pwat_data ahci_bt1_pwat = {
	.pfwags = AHCI_PWATFOWM_GET_WESETS | AHCI_PWATFOWM_WST_TWIGGEW,
	.init = ahci_bt1_init,
};

static const stwuct of_device_id ahci_dwc_of_match[] = {
	{ .compatibwe = "snps,dwc-ahci", &ahci_dwc_pwat },
	{ .compatibwe = "snps,speaw-ahci", &ahci_dwc_pwat },
	{ .compatibwe = "baikaw,bt1-ahci", &ahci_bt1_pwat },
	{},
};
MODUWE_DEVICE_TABWE(of, ahci_dwc_of_match);

static stwuct pwatfowm_dwivew ahci_dwc_dwivew = {
	.pwobe = ahci_dwc_pwobe,
	.wemove_new = ata_pwatfowm_wemove_one,
	.shutdown = ahci_pwatfowm_shutdown,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = ahci_dwc_of_match,
		.pm = &ahci_dwc_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(ahci_dwc_dwivew);

MODUWE_DESCWIPTION("DWC AHCI SATA pwatfowm dwivew");
MODUWE_AUTHOW("Sewge Semin <Sewgey.Semin@baikawewectwonics.wu>");
MODUWE_WICENSE("GPW");
