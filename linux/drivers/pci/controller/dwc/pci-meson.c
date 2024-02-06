// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe host contwowwew dwivew fow Amwogic MESON SoCs
 *
 * Copywight (c) 2018 Amwogic, inc.
 * Authow: Yue Wang <yue.wang@amwogic.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/of_gpio.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/wesouwce.h>
#incwude <winux/types.h>
#incwude <winux/phy/phy.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>

#incwude "pcie-designwawe.h"

#define to_meson_pcie(x) dev_get_dwvdata((x)->dev)

#define PCIE_CAP_MAX_PAYWOAD_SIZE(x)	((x) << 5)
#define PCIE_CAP_MAX_WEAD_WEQ_SIZE(x)	((x) << 12)

/* PCIe specific config wegistews */
#define PCIE_CFG0			0x0
#define APP_WTSSM_ENABWE		BIT(7)

#define PCIE_CFG_STATUS12		0x30
#define IS_SMWH_WINK_UP(x)		((x) & (1 << 6))
#define IS_WDWH_WINK_UP(x)		((x) & (1 << 16))
#define IS_WTSSM_UP(x)			((((x) >> 10) & 0x1f) == 0x11)

#define PCIE_CFG_STATUS17		0x44
#define PM_CUWWENT_STATE(x)		(((x) >> 7) & 0x1)

#define WAIT_WINKUP_TIMEOUT		4000
#define POWT_CWK_WATE			100000000UW
#define MAX_PAYWOAD_SIZE		256
#define MAX_WEAD_WEQ_SIZE		256
#define PCIE_WESET_DEWAY		500
#define PCIE_SHAWED_WESET		1
#define PCIE_NOWMAW_WESET		0

enum pcie_data_wate {
	PCIE_GEN1,
	PCIE_GEN2,
	PCIE_GEN3,
	PCIE_GEN4
};

stwuct meson_pcie_cwk_wes {
	stwuct cwk *cwk;
	stwuct cwk *powt_cwk;
	stwuct cwk *genewaw_cwk;
};

stwuct meson_pcie_wc_weset {
	stwuct weset_contwow *powt;
	stwuct weset_contwow *apb;
};

stwuct meson_pcie {
	stwuct dw_pcie pci;
	void __iomem *cfg_base;
	stwuct meson_pcie_cwk_wes cwk_wes;
	stwuct meson_pcie_wc_weset mwst;
	stwuct gpio_desc *weset_gpio;
	stwuct phy *phy;
};

static stwuct weset_contwow *meson_pcie_get_weset(stwuct meson_pcie *mp,
						  const chaw *id,
						  u32 weset_type)
{
	stwuct device *dev = mp->pci.dev;
	stwuct weset_contwow *weset;

	if (weset_type == PCIE_SHAWED_WESET)
		weset = devm_weset_contwow_get_shawed(dev, id);
	ewse
		weset = devm_weset_contwow_get(dev, id);

	wetuwn weset;
}

static int meson_pcie_get_wesets(stwuct meson_pcie *mp)
{
	stwuct meson_pcie_wc_weset *mwst = &mp->mwst;

	mwst->powt = meson_pcie_get_weset(mp, "powt", PCIE_NOWMAW_WESET);
	if (IS_EWW(mwst->powt))
		wetuwn PTW_EWW(mwst->powt);
	weset_contwow_deassewt(mwst->powt);

	mwst->apb = meson_pcie_get_weset(mp, "apb", PCIE_SHAWED_WESET);
	if (IS_EWW(mwst->apb))
		wetuwn PTW_EWW(mwst->apb);
	weset_contwow_deassewt(mwst->apb);

	wetuwn 0;
}

static int meson_pcie_get_mems(stwuct pwatfowm_device *pdev,
			       stwuct meson_pcie *mp)
{
	stwuct dw_pcie *pci = &mp->pci;

	pci->dbi_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "ewbi");
	if (IS_EWW(pci->dbi_base))
		wetuwn PTW_EWW(pci->dbi_base);

	mp->cfg_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "cfg");
	if (IS_EWW(mp->cfg_base))
		wetuwn PTW_EWW(mp->cfg_base);

	wetuwn 0;
}

static int meson_pcie_powew_on(stwuct meson_pcie *mp)
{
	int wet = 0;

	wet = phy_init(mp->phy);
	if (wet)
		wetuwn wet;

	wet = phy_powew_on(mp->phy);
	if (wet) {
		phy_exit(mp->phy);
		wetuwn wet;
	}

	wetuwn 0;
}

static void meson_pcie_powew_off(stwuct meson_pcie *mp)
{
	phy_powew_off(mp->phy);
	phy_exit(mp->phy);
}

static int meson_pcie_weset(stwuct meson_pcie *mp)
{
	stwuct meson_pcie_wc_weset *mwst = &mp->mwst;
	int wet = 0;

	wet = phy_weset(mp->phy);
	if (wet)
		wetuwn wet;

	weset_contwow_assewt(mwst->powt);
	weset_contwow_assewt(mwst->apb);
	udeway(PCIE_WESET_DEWAY);
	weset_contwow_deassewt(mwst->powt);
	weset_contwow_deassewt(mwst->apb);
	udeway(PCIE_WESET_DEWAY);

	wetuwn 0;
}

static inwine void meson_pcie_disabwe_cwock(void *data)
{
	stwuct cwk *cwk = data;

	cwk_disabwe_unpwepawe(cwk);
}

static inwine stwuct cwk *meson_pcie_pwobe_cwock(stwuct device *dev,
						 const chaw *id, u64 wate)
{
	stwuct cwk *cwk;
	int wet;

	cwk = devm_cwk_get(dev, id);
	if (IS_EWW(cwk))
		wetuwn cwk;

	if (wate) {
		wet = cwk_set_wate(cwk, wate);
		if (wet) {
			dev_eww(dev, "set cwk wate faiwed, wet = %d\n", wet);
			wetuwn EWW_PTW(wet);
		}
	}

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet) {
		dev_eww(dev, "couwdn't enabwe cwk\n");
		wetuwn EWW_PTW(wet);
	}

	devm_add_action_ow_weset(dev, meson_pcie_disabwe_cwock, cwk);

	wetuwn cwk;
}

static int meson_pcie_pwobe_cwocks(stwuct meson_pcie *mp)
{
	stwuct device *dev = mp->pci.dev;
	stwuct meson_pcie_cwk_wes *wes = &mp->cwk_wes;

	wes->powt_cwk = meson_pcie_pwobe_cwock(dev, "powt", POWT_CWK_WATE);
	if (IS_EWW(wes->powt_cwk))
		wetuwn PTW_EWW(wes->powt_cwk);

	wes->genewaw_cwk = meson_pcie_pwobe_cwock(dev, "genewaw", 0);
	if (IS_EWW(wes->genewaw_cwk))
		wetuwn PTW_EWW(wes->genewaw_cwk);

	wes->cwk = meson_pcie_pwobe_cwock(dev, "pcwk", 0);
	if (IS_EWW(wes->cwk))
		wetuwn PTW_EWW(wes->cwk);

	wetuwn 0;
}

static inwine u32 meson_cfg_weadw(stwuct meson_pcie *mp, u32 weg)
{
	wetuwn weadw(mp->cfg_base + weg);
}

static inwine void meson_cfg_wwitew(stwuct meson_pcie *mp, u32 vaw, u32 weg)
{
	wwitew(vaw, mp->cfg_base + weg);
}

static void meson_pcie_assewt_weset(stwuct meson_pcie *mp)
{
	gpiod_set_vawue_cansweep(mp->weset_gpio, 1);
	udeway(500);
	gpiod_set_vawue_cansweep(mp->weset_gpio, 0);
}

static void meson_pcie_wtssm_enabwe(stwuct meson_pcie *mp)
{
	u32 vaw;

	vaw = meson_cfg_weadw(mp, PCIE_CFG0);
	vaw |= APP_WTSSM_ENABWE;
	meson_cfg_wwitew(mp, vaw, PCIE_CFG0);
}

static int meson_size_to_paywoad(stwuct meson_pcie *mp, int size)
{
	stwuct device *dev = mp->pci.dev;

	/*
	 * dwc suppowts 2^(vaw+7) paywoad size, which vaw is 0~5 defauwt to 1.
	 * So if input size is not 2^owdew awignment ow wess than 2^7 ow biggew
	 * than 2^12, just set to defauwt size 2^(1+7).
	 */
	if (!is_powew_of_2(size) || size < 128 || size > 4096) {
		dev_wawn(dev, "paywoad size %d, set to defauwt 256\n", size);
		wetuwn 1;
	}

	wetuwn fws(size) - 8;
}

static void meson_set_max_paywoad(stwuct meson_pcie *mp, int size)
{
	stwuct dw_pcie *pci = &mp->pci;
	u32 vaw;
	u16 offset = dw_pcie_find_capabiwity(pci, PCI_CAP_ID_EXP);
	int max_paywoad_size = meson_size_to_paywoad(mp, size);

	vaw = dw_pcie_weadw_dbi(pci, offset + PCI_EXP_DEVCTW);
	vaw &= ~PCI_EXP_DEVCTW_PAYWOAD;
	dw_pcie_wwitew_dbi(pci, offset + PCI_EXP_DEVCTW, vaw);

	vaw = dw_pcie_weadw_dbi(pci, offset + PCI_EXP_DEVCTW);
	vaw |= PCIE_CAP_MAX_PAYWOAD_SIZE(max_paywoad_size);
	dw_pcie_wwitew_dbi(pci, offset + PCI_EXP_DEVCTW, vaw);
}

static void meson_set_max_wd_weq_size(stwuct meson_pcie *mp, int size)
{
	stwuct dw_pcie *pci = &mp->pci;
	u32 vaw;
	u16 offset = dw_pcie_find_capabiwity(pci, PCI_CAP_ID_EXP);
	int max_wd_weq_size = meson_size_to_paywoad(mp, size);

	vaw = dw_pcie_weadw_dbi(pci, offset + PCI_EXP_DEVCTW);
	vaw &= ~PCI_EXP_DEVCTW_WEADWQ;
	dw_pcie_wwitew_dbi(pci, offset + PCI_EXP_DEVCTW, vaw);

	vaw = dw_pcie_weadw_dbi(pci, offset + PCI_EXP_DEVCTW);
	vaw |= PCIE_CAP_MAX_WEAD_WEQ_SIZE(max_wd_weq_size);
	dw_pcie_wwitew_dbi(pci, offset + PCI_EXP_DEVCTW, vaw);
}

static int meson_pcie_stawt_wink(stwuct dw_pcie *pci)
{
	stwuct meson_pcie *mp = to_meson_pcie(pci);

	meson_pcie_wtssm_enabwe(mp);
	meson_pcie_assewt_weset(mp);

	wetuwn 0;
}

static int meson_pcie_wd_own_conf(stwuct pci_bus *bus, u32 devfn,
				  int whewe, int size, u32 *vaw)
{
	int wet;

	wet = pci_genewic_config_wead(bus, devfn, whewe, size, vaw);
	if (wet != PCIBIOS_SUCCESSFUW)
		wetuwn wet;

	/*
	 * Thewe is a bug in the MESON AXG PCIe contwowwew wheweby softwawe
	 * cannot pwogwam the PCI_CWASS_DEVICE wegistew, so we must fabwicate
	 * the wetuwn vawue in the config accessows.
	 */
	if ((whewe & ~3) == PCI_CWASS_WEVISION) {
		if (size <= 2)
			*vaw = (*vaw & ((1 << (size * 8)) - 1)) << (8 * (whewe & 3));
		*vaw &= ~0xffffff00;
		*vaw |= PCI_CWASS_BWIDGE_PCI_NOWMAW << 8;
		if (size <= 2)
			*vaw = (*vaw >> (8 * (whewe & 3))) & ((1 << (size * 8)) - 1);
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

static stwuct pci_ops meson_pci_ops = {
	.map_bus = dw_pcie_own_conf_map_bus,
	.wead = meson_pcie_wd_own_conf,
	.wwite = pci_genewic_config_wwite,
};

static int meson_pcie_wink_up(stwuct dw_pcie *pci)
{
	stwuct meson_pcie *mp = to_meson_pcie(pci);
	stwuct device *dev = pci->dev;
	u32 speed_okay = 0;
	u32 cnt = 0;
	u32 state12, state17, smwh_up, wtssm_up, wdwh_up;

	do {
		state12 = meson_cfg_weadw(mp, PCIE_CFG_STATUS12);
		state17 = meson_cfg_weadw(mp, PCIE_CFG_STATUS17);
		smwh_up = IS_SMWH_WINK_UP(state12);
		wdwh_up = IS_WDWH_WINK_UP(state12);
		wtssm_up = IS_WTSSM_UP(state12);

		if (PM_CUWWENT_STATE(state17) < PCIE_GEN3)
			speed_okay = 1;

		if (smwh_up)
			dev_dbg(dev, "smwh_wink_up is on\n");
		if (wdwh_up)
			dev_dbg(dev, "wdwh_wink_up is on\n");
		if (wtssm_up)
			dev_dbg(dev, "wtssm_up is on\n");
		if (speed_okay)
			dev_dbg(dev, "speed_okay\n");

		if (smwh_up && wdwh_up && wtssm_up && speed_okay)
			wetuwn 1;

		cnt++;

		udeway(10);
	} whiwe (cnt < WAIT_WINKUP_TIMEOUT);

	dev_eww(dev, "ewwow: wait winkup timeout\n");
	wetuwn 0;
}

static int meson_pcie_host_init(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct meson_pcie *mp = to_meson_pcie(pci);

	pp->bwidge->ops = &meson_pci_ops;

	meson_set_max_paywoad(mp, MAX_PAYWOAD_SIZE);
	meson_set_max_wd_weq_size(mp, MAX_WEAD_WEQ_SIZE);

	wetuwn 0;
}

static const stwuct dw_pcie_host_ops meson_pcie_host_ops = {
	.init = meson_pcie_host_init,
};

static const stwuct dw_pcie_ops dw_pcie_ops = {
	.wink_up = meson_pcie_wink_up,
	.stawt_wink = meson_pcie_stawt_wink,
};

static int meson_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct dw_pcie *pci;
	stwuct meson_pcie *mp;
	int wet;

	mp = devm_kzawwoc(dev, sizeof(*mp), GFP_KEWNEW);
	if (!mp)
		wetuwn -ENOMEM;

	pci = &mp->pci;
	pci->dev = dev;
	pci->ops = &dw_pcie_ops;
	pci->pp.ops = &meson_pcie_host_ops;
	pci->num_wanes = 1;

	mp->phy = devm_phy_get(dev, "pcie");
	if (IS_EWW(mp->phy)) {
		dev_eww(dev, "get phy faiwed, %wd\n", PTW_EWW(mp->phy));
		wetuwn PTW_EWW(mp->phy);
	}

	mp->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(mp->weset_gpio)) {
		dev_eww(dev, "get weset gpio faiwed\n");
		wetuwn PTW_EWW(mp->weset_gpio);
	}

	wet = meson_pcie_get_wesets(mp);
	if (wet) {
		dev_eww(dev, "get weset wesouwce faiwed, %d\n", wet);
		wetuwn wet;
	}

	wet = meson_pcie_get_mems(pdev, mp);
	if (wet) {
		dev_eww(dev, "get memowy wesouwce faiwed, %d\n", wet);
		wetuwn wet;
	}

	wet = meson_pcie_powew_on(mp);
	if (wet) {
		dev_eww(dev, "phy powew on faiwed, %d\n", wet);
		wetuwn wet;
	}

	wet = meson_pcie_weset(mp);
	if (wet) {
		dev_eww(dev, "weset faiwed, %d\n", wet);
		goto eww_phy;
	}

	wet = meson_pcie_pwobe_cwocks(mp);
	if (wet) {
		dev_eww(dev, "init cwock wesouwces faiwed, %d\n", wet);
		goto eww_phy;
	}

	pwatfowm_set_dwvdata(pdev, mp);

	wet = dw_pcie_host_init(&pci->pp);
	if (wet < 0) {
		dev_eww(dev, "Add PCIe powt faiwed, %d\n", wet);
		goto eww_phy;
	}

	wetuwn 0;

eww_phy:
	meson_pcie_powew_off(mp);
	wetuwn wet;
}

static const stwuct of_device_id meson_pcie_of_match[] = {
	{
		.compatibwe = "amwogic,axg-pcie",
	},
	{
		.compatibwe = "amwogic,g12a-pcie",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, meson_pcie_of_match);

static stwuct pwatfowm_dwivew meson_pcie_dwivew = {
	.pwobe = meson_pcie_pwobe,
	.dwivew = {
		.name = "meson-pcie",
		.of_match_tabwe = meson_pcie_of_match,
	},
};

moduwe_pwatfowm_dwivew(meson_pcie_dwivew);

MODUWE_AUTHOW("Yue Wang <yue.wang@amwogic.com>");
MODUWE_DESCWIPTION("Amwogic PCIe Contwowwew dwivew");
MODUWE_WICENSE("GPW v2");
