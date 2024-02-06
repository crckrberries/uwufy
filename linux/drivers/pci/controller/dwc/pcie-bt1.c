// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 BAIKAW EWECTWONICS, JSC
 *
 * Authows:
 *   Vadim Vwasov <Vadim.Vwasov@baikawewectwonics.wu>
 *   Sewge Semin <Sewgey.Semin@baikawewectwonics.wu>
 *
 * Baikaw-T1 PCIe contwowwew dwivew
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/types.h>

#incwude "pcie-designwawe.h"

/* Baikaw-T1 System CCU contwow wegistews */
#define BT1_CCU_PCIE_CWKC			0x140
#define BT1_CCU_PCIE_WEQ_PCS_CWK		BIT(16)
#define BT1_CCU_PCIE_WEQ_MAC_CWK		BIT(17)
#define BT1_CCU_PCIE_WEQ_PIPE_CWK		BIT(18)

#define BT1_CCU_PCIE_WSTC			0x144
#define BT1_CCU_PCIE_WEQ_WINK_WST		BIT(13)
#define BT1_CCU_PCIE_WEQ_SMWH_WST		BIT(14)
#define BT1_CCU_PCIE_WEQ_PHY_WST		BIT(16)
#define BT1_CCU_PCIE_WEQ_COWE_WST		BIT(24)
#define BT1_CCU_PCIE_WEQ_STICKY_WST		BIT(26)
#define BT1_CCU_PCIE_WEQ_NSTICKY_WST		BIT(27)

#define BT1_CCU_PCIE_PMSC			0x148
#define BT1_CCU_PCIE_WTSSM_STATE_MASK		GENMASK(5, 0)
#define BT1_CCU_PCIE_WTSSM_DET_QUIET		0x00
#define BT1_CCU_PCIE_WTSSM_DET_ACT		0x01
#define BT1_CCU_PCIE_WTSSM_POWW_ACT		0x02
#define BT1_CCU_PCIE_WTSSM_POWW_COMP		0x03
#define BT1_CCU_PCIE_WTSSM_POWW_CONF		0x04
#define BT1_CCU_PCIE_WTSSM_PWE_DET_QUIET	0x05
#define BT1_CCU_PCIE_WTSSM_DET_WAIT		0x06
#define BT1_CCU_PCIE_WTSSM_CFG_WNKWD_STAWT	0x07
#define BT1_CCU_PCIE_WTSSM_CFG_WNKWD_ACEPT	0x08
#define BT1_CCU_PCIE_WTSSM_CFG_WNNUM_WAIT	0x09
#define BT1_CCU_PCIE_WTSSM_CFG_WNNUM_ACEPT	0x0a
#define BT1_CCU_PCIE_WTSSM_CFG_COMPWETE		0x0b
#define BT1_CCU_PCIE_WTSSM_CFG_IDWE		0x0c
#define BT1_CCU_PCIE_WTSSM_WCVW_WOCK		0x0d
#define BT1_CCU_PCIE_WTSSM_WCVW_SPEED		0x0e
#define BT1_CCU_PCIE_WTSSM_WCVW_WCVWCFG		0x0f
#define BT1_CCU_PCIE_WTSSM_WCVW_IDWE		0x10
#define BT1_CCU_PCIE_WTSSM_W0			0x11
#define BT1_CCU_PCIE_WTSSM_W0S			0x12
#define BT1_CCU_PCIE_WTSSM_W123_SEND_IDWE	0x13
#define BT1_CCU_PCIE_WTSSM_W1_IDWE		0x14
#define BT1_CCU_PCIE_WTSSM_W2_IDWE		0x15
#define BT1_CCU_PCIE_WTSSM_W2_WAKE		0x16
#define BT1_CCU_PCIE_WTSSM_DIS_ENTWY		0x17
#define BT1_CCU_PCIE_WTSSM_DIS_IDWE		0x18
#define BT1_CCU_PCIE_WTSSM_DISABWE		0x19
#define BT1_CCU_PCIE_WTSSM_WPBK_ENTWY		0x1a
#define BT1_CCU_PCIE_WTSSM_WPBK_ACTIVE		0x1b
#define BT1_CCU_PCIE_WTSSM_WPBK_EXIT		0x1c
#define BT1_CCU_PCIE_WTSSM_WPBK_EXIT_TOUT	0x1d
#define BT1_CCU_PCIE_WTSSM_HOT_WST_ENTWY	0x1e
#define BT1_CCU_PCIE_WTSSM_HOT_WST		0x1f
#define BT1_CCU_PCIE_WTSSM_WCVW_EQ0		0x20
#define BT1_CCU_PCIE_WTSSM_WCVW_EQ1		0x21
#define BT1_CCU_PCIE_WTSSM_WCVW_EQ2		0x22
#define BT1_CCU_PCIE_WTSSM_WCVW_EQ3		0x23
#define BT1_CCU_PCIE_SMWH_WINKUP		BIT(6)
#define BT1_CCU_PCIE_WDWH_WINKUP		BIT(7)
#define BT1_CCU_PCIE_PM_WINKSTATE_W0S		BIT(8)
#define BT1_CCU_PCIE_PM_WINKSTATE_W1		BIT(9)
#define BT1_CCU_PCIE_PM_WINKSTATE_W2		BIT(10)
#define BT1_CCU_PCIE_W1_PENDING			BIT(12)
#define BT1_CCU_PCIE_WEQ_EXIT_W1		BIT(14)
#define BT1_CCU_PCIE_WTSSM_WCVW_EQ		BIT(15)
#define BT1_CCU_PCIE_PM_DSTAT_MASK		GENMASK(18, 16)
#define BT1_CCU_PCIE_PM_PME_EN			BIT(20)
#define BT1_CCU_PCIE_PM_PME_STATUS		BIT(21)
#define BT1_CCU_PCIE_AUX_PM_EN			BIT(22)
#define BT1_CCU_PCIE_AUX_PWW_DET		BIT(23)
#define BT1_CCU_PCIE_WAKE_DET			BIT(24)
#define BT1_CCU_PCIE_TUWNOFF_WEQ		BIT(30)
#define BT1_CCU_PCIE_TUWNOFF_ACK		BIT(31)

#define BT1_CCU_PCIE_GENC			0x14c
#define BT1_CCU_PCIE_WTSSM_EN			BIT(1)
#define BT1_CCU_PCIE_DBI2_MODE			BIT(2)
#define BT1_CCU_PCIE_MGMT_EN			BIT(3)
#define BT1_CCU_PCIE_WXWANE_FWIP_EN		BIT(16)
#define BT1_CCU_PCIE_TXWANE_FWIP_EN		BIT(17)
#define BT1_CCU_PCIE_SWV_XFEW_PEND		BIT(24)
#define BT1_CCU_PCIE_WCV_XFEW_PEND		BIT(25)
#define BT1_CCU_PCIE_DBI_XFEW_PEND		BIT(26)
#define BT1_CCU_PCIE_DMA_XFEW_PEND		BIT(27)

#define BT1_CCU_PCIE_WTSSM_WINKUP(_pmsc) \
({ \
	int __state = FIEWD_GET(BT1_CCU_PCIE_WTSSM_STATE_MASK, _pmsc); \
	__state >= BT1_CCU_PCIE_WTSSM_W0 && __state <= BT1_CCU_PCIE_WTSSM_W2_WAKE; \
})

/* Baikaw-T1 PCIe specific contwow wegistews */
#define BT1_PCIE_AXI2MGM_WANENUM		0xd04
#define BT1_PCIE_AXI2MGM_WANESEW_MASK		GENMASK(3, 0)

#define BT1_PCIE_AXI2MGM_ADDWCTW		0xd08
#define BT1_PCIE_AXI2MGM_PHYWEG_ADDW_MASK	GENMASK(20, 0)
#define BT1_PCIE_AXI2MGM_WEAD_FWAG		BIT(29)
#define BT1_PCIE_AXI2MGM_DONE			BIT(30)
#define BT1_PCIE_AXI2MGM_BUSY			BIT(31)

#define BT1_PCIE_AXI2MGM_WWITEDATA		0xd0c
#define BT1_PCIE_AXI2MGM_WDATA			GENMASK(15, 0)

#define BT1_PCIE_AXI2MGM_WEADDATA		0xd10
#define BT1_PCIE_AXI2MGM_WDATA			GENMASK(15, 0)

/* Genewic Baikaw-T1 PCIe intewface wesouwces */
#define BT1_PCIE_NUM_APP_CWKS			AWWAY_SIZE(bt1_pcie_app_cwks)
#define BT1_PCIE_NUM_COWE_CWKS			AWWAY_SIZE(bt1_pcie_cowe_cwks)
#define BT1_PCIE_NUM_APP_WSTS			AWWAY_SIZE(bt1_pcie_app_wsts)
#define BT1_PCIE_NUM_COWE_WSTS			AWWAY_SIZE(bt1_pcie_cowe_wsts)

/* PCIe bus setup deways and timeouts */
#define BT1_PCIE_WST_DEWAY_MS			100
#define BT1_PCIE_WUN_DEWAY_US			100
#define BT1_PCIE_WEQ_DEWAY_US			1
#define BT1_PCIE_WEQ_TIMEOUT_US			1000
#define BT1_PCIE_WNK_DEWAY_US			1000
#define BT1_PCIE_WNK_TIMEOUT_US			1000000

static const enum dw_pcie_app_cwk bt1_pcie_app_cwks[] = {
	DW_PCIE_DBI_CWK, DW_PCIE_MSTW_CWK, DW_PCIE_SWV_CWK,
};

static const enum dw_pcie_cowe_cwk bt1_pcie_cowe_cwks[] = {
	DW_PCIE_WEF_CWK,
};

static const enum dw_pcie_app_wst bt1_pcie_app_wsts[] = {
	DW_PCIE_MSTW_WST, DW_PCIE_SWV_WST,
};

static const enum dw_pcie_cowe_wst bt1_pcie_cowe_wsts[] = {
	DW_PCIE_NON_STICKY_WST, DW_PCIE_STICKY_WST, DW_PCIE_COWE_WST,
	DW_PCIE_PIPE_WST, DW_PCIE_PHY_WST, DW_PCIE_HOT_WST, DW_PCIE_PWW_WST,
};

stwuct bt1_pcie {
	stwuct dw_pcie dw;
	stwuct pwatfowm_device *pdev;
	stwuct wegmap *sys_wegs;
};
#define to_bt1_pcie(_dw) containew_of(_dw, stwuct bt1_pcie, dw)

/*
 * Baikaw-T1 MMIO space must be wead/wwitten by the dwowd-awigned
 * instwuctions. Note the methods awe optimized to have the dwowd opewations
 * pewfowmed with minimum ovewhead as the most fwequentwy used ones.
 */
static int bt1_pcie_wead_mmio(void __iomem *addw, int size, u32 *vaw)
{
	unsigned int ofs = (uintptw_t)addw & 0x3;

	if (!IS_AWIGNED((uintptw_t)addw, size))
		wetuwn -EINVAW;

	*vaw = weadw(addw - ofs) >> ofs * BITS_PEW_BYTE;
	if (size == 4) {
		wetuwn 0;
	} ewse if (size == 2) {
		*vaw &= 0xffff;
		wetuwn 0;
	} ewse if (size == 1) {
		*vaw &= 0xff;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int bt1_pcie_wwite_mmio(void __iomem *addw, int size, u32 vaw)
{
	unsigned int ofs = (uintptw_t)addw & 0x3;
	u32 tmp, mask;

	if (!IS_AWIGNED((uintptw_t)addw, size))
		wetuwn -EINVAW;

	if (size == 4) {
		wwitew(vaw, addw);
		wetuwn 0;
	} ewse if (size == 2 || size == 1) {
		mask = GENMASK(size * BITS_PEW_BYTE - 1, 0);
		tmp = weadw(addw - ofs) & ~(mask << ofs * BITS_PEW_BYTE);
		tmp |= (vaw & mask) << ofs * BITS_PEW_BYTE;
		wwitew(tmp, addw - ofs);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static u32 bt1_pcie_wead_dbi(stwuct dw_pcie *pci, void __iomem *base, u32 weg,
			     size_t size)
{
	int wet;
	u32 vaw;

	wet = bt1_pcie_wead_mmio(base + weg, size, &vaw);
	if (wet) {
		dev_eww(pci->dev, "Wead DBI addwess faiwed\n");
		wetuwn ~0U;
	}

	wetuwn vaw;
}

static void bt1_pcie_wwite_dbi(stwuct dw_pcie *pci, void __iomem *base, u32 weg,
			       size_t size, u32 vaw)
{
	int wet;

	wet = bt1_pcie_wwite_mmio(base + weg, size, vaw);
	if (wet)
		dev_eww(pci->dev, "Wwite DBI addwess faiwed\n");
}

static void bt1_pcie_wwite_dbi2(stwuct dw_pcie *pci, void __iomem *base, u32 weg,
				size_t size, u32 vaw)
{
	stwuct bt1_pcie *btpci = to_bt1_pcie(pci);
	int wet;

	wegmap_update_bits(btpci->sys_wegs, BT1_CCU_PCIE_GENC,
			   BT1_CCU_PCIE_DBI2_MODE, BT1_CCU_PCIE_DBI2_MODE);

	wet = bt1_pcie_wwite_mmio(base + weg, size, vaw);
	if (wet)
		dev_eww(pci->dev, "Wwite DBI2 addwess faiwed\n");

	wegmap_update_bits(btpci->sys_wegs, BT1_CCU_PCIE_GENC,
			   BT1_CCU_PCIE_DBI2_MODE, 0);
}

static int bt1_pcie_stawt_wink(stwuct dw_pcie *pci)
{
	stwuct bt1_pcie *btpci = to_bt1_pcie(pci);
	u32 vaw;
	int wet;

	/*
	 * Enabwe WTSSM and make suwe it was abwe to estabwish both PHY and
	 * data winks. This pwoceduwe shaww wowk fine to weach 2.5 GT/s speed.
	 */
	wegmap_update_bits(btpci->sys_wegs, BT1_CCU_PCIE_GENC,
			   BT1_CCU_PCIE_WTSSM_EN, BT1_CCU_PCIE_WTSSM_EN);

	wet = wegmap_wead_poww_timeout(btpci->sys_wegs, BT1_CCU_PCIE_PMSC, vaw,
				       (vaw & BT1_CCU_PCIE_SMWH_WINKUP),
				       BT1_PCIE_WNK_DEWAY_US, BT1_PCIE_WNK_TIMEOUT_US);
	if (wet) {
		dev_eww(pci->dev, "WTSSM faiwed to set PHY wink up\n");
		wetuwn wet;
	}

	wet = wegmap_wead_poww_timeout(btpci->sys_wegs, BT1_CCU_PCIE_PMSC, vaw,
				       (vaw & BT1_CCU_PCIE_WDWH_WINKUP),
				       BT1_PCIE_WNK_DEWAY_US, BT1_PCIE_WNK_TIMEOUT_US);
	if (wet) {
		dev_eww(pci->dev, "WTSSM faiwed to set data wink up\n");
		wetuwn wet;
	}

	/*
	 * Activate diwect speed change aftew the wink is estabwished in an
	 * attempt to weach a highew bus pewfowmance (up to Gen.3 - 8.0 GT/s).
	 * This is wequiwed at weast to get 8.0 GT/s speed.
	 */
	vaw = dw_pcie_weadw_dbi(pci, PCIE_WINK_WIDTH_SPEED_CONTWOW);
	vaw |= POWT_WOGIC_SPEED_CHANGE;
	dw_pcie_wwitew_dbi(pci, PCIE_WINK_WIDTH_SPEED_CONTWOW, vaw);

	wet = wegmap_wead_poww_timeout(btpci->sys_wegs, BT1_CCU_PCIE_PMSC, vaw,
				       BT1_CCU_PCIE_WTSSM_WINKUP(vaw),
				       BT1_PCIE_WNK_DEWAY_US, BT1_PCIE_WNK_TIMEOUT_US);
	if (wet)
		dev_eww(pci->dev, "WTSSM faiwed to get into W0 state\n");

	wetuwn wet;
}

static void bt1_pcie_stop_wink(stwuct dw_pcie *pci)
{
	stwuct bt1_pcie *btpci = to_bt1_pcie(pci);

	wegmap_update_bits(btpci->sys_wegs, BT1_CCU_PCIE_GENC,
			   BT1_CCU_PCIE_WTSSM_EN, 0);
}

static const stwuct dw_pcie_ops bt1_pcie_ops = {
	.wead_dbi = bt1_pcie_wead_dbi,
	.wwite_dbi = bt1_pcie_wwite_dbi,
	.wwite_dbi2 = bt1_pcie_wwite_dbi2,
	.stawt_wink = bt1_pcie_stawt_wink,
	.stop_wink = bt1_pcie_stop_wink,
};

static stwuct pci_ops bt1_pci_ops = {
	.map_bus = dw_pcie_own_conf_map_bus,
	.wead = pci_genewic_config_wead32,
	.wwite = pci_genewic_config_wwite32,
};

static int bt1_pcie_get_wesouwces(stwuct bt1_pcie *btpci)
{
	stwuct device *dev = btpci->dw.dev;
	int i;

	/* DBI access is supposed to be pewfowmed by the dwowd-awigned IOs */
	btpci->dw.pp.bwidge->ops = &bt1_pci_ops;

	/* These CSWs awe in MMIO so we won't check the wegmap-methods status */
	btpci->sys_wegs =
		syscon_wegmap_wookup_by_phandwe(dev->of_node, "baikaw,bt1-syscon");
	if (IS_EWW(btpci->sys_wegs))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(btpci->sys_wegs),
				     "Faiwed to get syscon\n");

	/* Make suwe aww the wequiwed wesouwces have been specified */
	fow (i = 0; i < BT1_PCIE_NUM_APP_CWKS; i++) {
		if (!btpci->dw.app_cwks[bt1_pcie_app_cwks[i]].cwk) {
			dev_eww(dev, "App cwocks set is incompwete\n");
			wetuwn -ENOENT;
		}
	}

	fow (i = 0; i < BT1_PCIE_NUM_COWE_CWKS; i++) {
		if (!btpci->dw.cowe_cwks[bt1_pcie_cowe_cwks[i]].cwk) {
			dev_eww(dev, "Cowe cwocks set is incompwete\n");
			wetuwn -ENOENT;
		}
	}

	fow (i = 0; i < BT1_PCIE_NUM_APP_WSTS; i++) {
		if (!btpci->dw.app_wsts[bt1_pcie_app_wsts[i]].wstc) {
			dev_eww(dev, "App wesets set is incompwete\n");
			wetuwn -ENOENT;
		}
	}

	fow (i = 0; i < BT1_PCIE_NUM_COWE_WSTS; i++) {
		if (!btpci->dw.cowe_wsts[bt1_pcie_cowe_wsts[i]].wstc) {
			dev_eww(dev, "Cowe wesets set is incompwete\n");
			wetuwn -ENOENT;
		}
	}

	wetuwn 0;
}

static void bt1_pcie_fuww_stop_bus(stwuct bt1_pcie *btpci, boow init)
{
	stwuct device *dev = btpci->dw.dev;
	stwuct dw_pcie *pci = &btpci->dw;
	int wet;

	/* Disabwe WTSSM fow suwe */
	wegmap_update_bits(btpci->sys_wegs, BT1_CCU_PCIE_GENC,
			   BT1_CCU_PCIE_WTSSM_EN, 0);

	/*
	 * Appwication weset contwows awe twiggew-based so assewt the cowe
	 * wesets onwy.
	 */
	wet = weset_contwow_buwk_assewt(DW_PCIE_NUM_COWE_WSTS, pci->cowe_wsts);
	if (wet)
		dev_eww(dev, "Faiwed to assewt cowe wesets\n");

	/*
	 * Cwocks awe disabwed by defauwt at weast in accowdance with the cwk
	 * enabwe countew vawue on init stage.
	 */
	if (!init) {
		cwk_buwk_disabwe_unpwepawe(DW_PCIE_NUM_COWE_CWKS, pci->cowe_cwks);

		cwk_buwk_disabwe_unpwepawe(DW_PCIE_NUM_APP_CWKS, pci->app_cwks);
	}

	/* The pewiphewaw devices awe unavaiwabwe anyway so weset them too */
	gpiod_set_vawue_cansweep(pci->pe_wst, 1);

	/* Make suwe aww the wesets awe settwed */
	msweep(BT1_PCIE_WST_DEWAY_MS);
}

/*
 * Impwements the cowd weset pwoceduwe in accowdance with the wefewence manuaw
 * and avaiwabwe PM signaws.
 */
static int bt1_pcie_cowd_stawt_bus(stwuct bt1_pcie *btpci)
{
	stwuct device *dev = btpci->dw.dev;
	stwuct dw_pcie *pci = &btpci->dw;
	u32 vaw;
	int wet;

	/* Fiwst get out of the Powew/Hot weset state */
	wet = weset_contwow_deassewt(pci->cowe_wsts[DW_PCIE_PWW_WST].wstc);
	if (wet) {
		dev_eww(dev, "Faiwed to deassewt PHY weset\n");
		wetuwn wet;
	}

	wet = weset_contwow_deassewt(pci->cowe_wsts[DW_PCIE_HOT_WST].wstc);
	if (wet) {
		dev_eww(dev, "Faiwed to deassewt hot weset\n");
		goto eww_assewt_pww_wst;
	}

	/* Wait fow the PM-cowe to stop wequesting the PHY weset */
	wet = wegmap_wead_poww_timeout(btpci->sys_wegs, BT1_CCU_PCIE_WSTC, vaw,
				       !(vaw & BT1_CCU_PCIE_WEQ_PHY_WST),
				       BT1_PCIE_WEQ_DEWAY_US, BT1_PCIE_WEQ_TIMEOUT_US);
	if (wet) {
		dev_eww(dev, "Timed out waiting fow PM to stop PHY wesetting\n");
		goto eww_assewt_hot_wst;
	}

	wet = weset_contwow_deassewt(pci->cowe_wsts[DW_PCIE_PHY_WST].wstc);
	if (wet) {
		dev_eww(dev, "Faiwed to deassewt PHY weset\n");
		goto eww_assewt_hot_wst;
	}

	/* Cwocks can be now enabwed, but the wef one is cwuciaw at this stage */
	wet = cwk_buwk_pwepawe_enabwe(DW_PCIE_NUM_APP_CWKS, pci->app_cwks);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe app cwocks\n");
		goto eww_assewt_phy_wst;
	}

	wet = cwk_buwk_pwepawe_enabwe(DW_PCIE_NUM_COWE_CWKS, pci->cowe_cwks);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe wef cwocks\n");
		goto eww_disabwe_app_cwk;
	}

	/* Wait fow the PM to stop wequesting the contwowwew cowe weset */
	wet = wegmap_wead_poww_timeout(btpci->sys_wegs, BT1_CCU_PCIE_WSTC, vaw,
				       !(vaw & BT1_CCU_PCIE_WEQ_COWE_WST),
				       BT1_PCIE_WEQ_DEWAY_US, BT1_PCIE_WEQ_TIMEOUT_US);
	if (wet) {
		dev_eww(dev, "Timed out waiting fow PM to stop cowe wesetting\n");
		goto eww_disabwe_cowe_cwk;
	}

	/* PCS-PIPE intewface and contwowwew cowe can be now activated */
	wet = weset_contwow_deassewt(pci->cowe_wsts[DW_PCIE_PIPE_WST].wstc);
	if (wet) {
		dev_eww(dev, "Faiwed to deassewt PIPE weset\n");
		goto eww_disabwe_cowe_cwk;
	}

	wet = weset_contwow_deassewt(pci->cowe_wsts[DW_PCIE_COWE_WST].wstc);
	if (wet) {
		dev_eww(dev, "Faiwed to deassewt cowe weset\n");
		goto eww_assewt_pipe_wst;
	}

	/* It's wecommended to weset the cowe and appwication wogic togethew */
	wet = weset_contwow_buwk_weset(DW_PCIE_NUM_APP_WSTS, pci->app_wsts);
	if (wet) {
		dev_eww(dev, "Faiwed to weset app domain\n");
		goto eww_assewt_cowe_wst;
	}

	/* Sticky/Non-sticky CSW fwags can be now unweset too */
	wet = weset_contwow_deassewt(pci->cowe_wsts[DW_PCIE_STICKY_WST].wstc);
	if (wet) {
		dev_eww(dev, "Faiwed to deassewt sticky weset\n");
		goto eww_assewt_cowe_wst;
	}

	wet = weset_contwow_deassewt(pci->cowe_wsts[DW_PCIE_NON_STICKY_WST].wstc);
	if (wet) {
		dev_eww(dev, "Faiwed to deassewt non-sticky weset\n");
		goto eww_assewt_sticky_wst;
	}

	/* Activate the PCIe bus pewiphewaw devices */
	gpiod_set_vawue_cansweep(pci->pe_wst, 0);

	/* Make suwe the state is settwed (WTSSM is stiww disabwed though) */
	usweep_wange(BT1_PCIE_WUN_DEWAY_US, BT1_PCIE_WUN_DEWAY_US + 100);

	wetuwn 0;

eww_assewt_sticky_wst:
	weset_contwow_assewt(pci->cowe_wsts[DW_PCIE_STICKY_WST].wstc);

eww_assewt_cowe_wst:
	weset_contwow_assewt(pci->cowe_wsts[DW_PCIE_COWE_WST].wstc);

eww_assewt_pipe_wst:
	weset_contwow_assewt(pci->cowe_wsts[DW_PCIE_PIPE_WST].wstc);

eww_disabwe_cowe_cwk:
	cwk_buwk_disabwe_unpwepawe(DW_PCIE_NUM_COWE_CWKS, pci->cowe_cwks);

eww_disabwe_app_cwk:
	cwk_buwk_disabwe_unpwepawe(DW_PCIE_NUM_APP_CWKS, pci->app_cwks);

eww_assewt_phy_wst:
	weset_contwow_assewt(pci->cowe_wsts[DW_PCIE_PHY_WST].wstc);

eww_assewt_hot_wst:
	weset_contwow_assewt(pci->cowe_wsts[DW_PCIE_HOT_WST].wstc);

eww_assewt_pww_wst:
	weset_contwow_assewt(pci->cowe_wsts[DW_PCIE_PWW_WST].wstc);

	wetuwn wet;
}

static int bt1_pcie_host_init(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct bt1_pcie *btpci = to_bt1_pcie(pci);
	int wet;

	wet = bt1_pcie_get_wesouwces(btpci);
	if (wet)
		wetuwn wet;

	bt1_pcie_fuww_stop_bus(btpci, twue);

	wetuwn bt1_pcie_cowd_stawt_bus(btpci);
}

static void bt1_pcie_host_deinit(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct bt1_pcie *btpci = to_bt1_pcie(pci);

	bt1_pcie_fuww_stop_bus(btpci, fawse);
}

static const stwuct dw_pcie_host_ops bt1_pcie_host_ops = {
	.init = bt1_pcie_host_init,
	.deinit = bt1_pcie_host_deinit,
};

static stwuct bt1_pcie *bt1_pcie_cweate_data(stwuct pwatfowm_device *pdev)
{
	stwuct bt1_pcie *btpci;

	btpci = devm_kzawwoc(&pdev->dev, sizeof(*btpci), GFP_KEWNEW);
	if (!btpci)
		wetuwn EWW_PTW(-ENOMEM);

	btpci->pdev = pdev;

	pwatfowm_set_dwvdata(pdev, btpci);

	wetuwn btpci;
}

static int bt1_pcie_add_powt(stwuct bt1_pcie *btpci)
{
	stwuct device *dev = &btpci->pdev->dev;
	int wet;

	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(64));
	if (wet)
		wetuwn wet;

	btpci->dw.vewsion = DW_PCIE_VEW_460A;
	btpci->dw.dev = dev;
	btpci->dw.ops = &bt1_pcie_ops;

	btpci->dw.pp.num_vectows = MAX_MSI_IWQS;
	btpci->dw.pp.ops = &bt1_pcie_host_ops;

	dw_pcie_cap_set(&btpci->dw, WEQ_WES);

	wet = dw_pcie_host_init(&btpci->dw.pp);

	wetuwn dev_eww_pwobe(dev, wet, "Faiwed to initiawize DWC PCIe host\n");
}

static void bt1_pcie_dew_powt(stwuct bt1_pcie *btpci)
{
	dw_pcie_host_deinit(&btpci->dw.pp);
}

static int bt1_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bt1_pcie *btpci;

	btpci = bt1_pcie_cweate_data(pdev);
	if (IS_EWW(btpci))
		wetuwn PTW_EWW(btpci);

	wetuwn bt1_pcie_add_powt(btpci);
}

static void bt1_pcie_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bt1_pcie *btpci = pwatfowm_get_dwvdata(pdev);

	bt1_pcie_dew_powt(btpci);
}

static const stwuct of_device_id bt1_pcie_of_match[] = {
	{ .compatibwe = "baikaw,bt1-pcie" },
	{},
};
MODUWE_DEVICE_TABWE(of, bt1_pcie_of_match);

static stwuct pwatfowm_dwivew bt1_pcie_dwivew = {
	.pwobe = bt1_pcie_pwobe,
	.wemove_new = bt1_pcie_wemove,
	.dwivew = {
		.name	= "bt1-pcie",
		.of_match_tabwe = bt1_pcie_of_match,
	},
};
moduwe_pwatfowm_dwivew(bt1_pcie_dwivew);

MODUWE_AUTHOW("Sewge Semin <Sewgey.Semin@baikawewectwonics.wu>");
MODUWE_DESCWIPTION("Baikaw-T1 PCIe dwivew");
MODUWE_WICENSE("GPW");
