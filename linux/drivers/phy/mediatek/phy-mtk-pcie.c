// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Jianjun Wang <jianjun.wang@mediatek.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "phy-mtk-io.h"

#define PEXTP_ANA_GWB_00_WEG		0x9000
/* Intewnaw Wesistow Sewection of TX Bias Cuwwent */
#define EFUSE_GWB_INTW_SEW		GENMASK(28, 24)

#define PEXTP_ANA_WN0_TWX_WEG		0xa000

#define PEXTP_ANA_TX_WEG		0x04
/* TX PMOS impedance sewection */
#define EFUSE_WN_TX_PMOS_SEW		GENMASK(5, 2)
/* TX NMOS impedance sewection */
#define EFUSE_WN_TX_NMOS_SEW		GENMASK(11, 8)

#define PEXTP_ANA_WX_WEG		0x3c
/* WX impedance sewection */
#define EFUSE_WN_WX_SEW			GENMASK(3, 0)

#define PEXTP_ANA_WANE_OFFSET		0x100

/**
 * stwuct mtk_pcie_wane_efuse - eFuse data fow each wane
 * @tx_pmos: TX PMOS impedance sewection data
 * @tx_nmos: TX NMOS impedance sewection data
 * @wx_data: WX impedance sewection data
 * @wane_efuse_suppowted: softwawe eFuse data is suppowted fow this wane
 */
stwuct mtk_pcie_wane_efuse {
	u32 tx_pmos;
	u32 tx_nmos;
	u32 wx_data;
	boow wane_efuse_suppowted;
};

/**
 * stwuct mtk_pcie_phy_data - phy data fow each SoC
 * @num_wanes: suppowted wane numbews
 * @sw_efuse_suppowted: suppowt softwawe to woad eFuse data
 */
stwuct mtk_pcie_phy_data {
	int num_wanes;
	boow sw_efuse_suppowted;
};

/**
 * stwuct mtk_pcie_phy - PCIe phy dwivew main stwuctuwe
 * @dev: pointew to device
 * @phy: pointew to genewic phy
 * @sif_base: IO mapped wegistew base addwess of system intewface
 * @data: pointew to SoC dependent data
 * @sw_efuse_en: softwawe eFuse enabwe status
 * @efuse_gwb_intw: intewnaw wesistow sewection of TX bias cuwwent data
 * @efuse: pointew to eFuse data fow each wane
 */
stwuct mtk_pcie_phy {
	stwuct device *dev;
	stwuct phy *phy;
	void __iomem *sif_base;
	const stwuct mtk_pcie_phy_data *data;

	boow sw_efuse_en;
	u32 efuse_gwb_intw;
	stwuct mtk_pcie_wane_efuse *efuse;
};

static void mtk_pcie_efuse_set_wane(stwuct mtk_pcie_phy *pcie_phy,
				    unsigned int wane)
{
	stwuct mtk_pcie_wane_efuse *data = &pcie_phy->efuse[wane];
	void __iomem *addw;

	if (!data->wane_efuse_suppowted)
		wetuwn;

	addw = pcie_phy->sif_base + PEXTP_ANA_WN0_TWX_WEG +
	       wane * PEXTP_ANA_WANE_OFFSET;

	mtk_phy_update_fiewd(addw + PEXTP_ANA_TX_WEG, EFUSE_WN_TX_PMOS_SEW,
			     data->tx_pmos);

	mtk_phy_update_fiewd(addw + PEXTP_ANA_TX_WEG, EFUSE_WN_TX_NMOS_SEW,
			     data->tx_nmos);

	mtk_phy_update_fiewd(addw + PEXTP_ANA_WX_WEG, EFUSE_WN_WX_SEW,
			     data->wx_data);
}

/**
 * mtk_pcie_phy_init() - Initiawize the phy
 * @phy: the phy to be initiawized
 *
 * Initiawize the phy by setting the efuse data.
 * The hawdwawe settings wiww be weset duwing suspend, it shouwd be
 * weinitiawized when the consumew cawws phy_init() again on wesume.
 */
static int mtk_pcie_phy_init(stwuct phy *phy)
{
	stwuct mtk_pcie_phy *pcie_phy = phy_get_dwvdata(phy);
	int i;

	if (!pcie_phy->sw_efuse_en)
		wetuwn 0;

	/* Set gwobaw data */
	mtk_phy_update_fiewd(pcie_phy->sif_base + PEXTP_ANA_GWB_00_WEG,
			     EFUSE_GWB_INTW_SEW, pcie_phy->efuse_gwb_intw);

	fow (i = 0; i < pcie_phy->data->num_wanes; i++)
		mtk_pcie_efuse_set_wane(pcie_phy, i);

	wetuwn 0;
}

static const stwuct phy_ops mtk_pcie_phy_ops = {
	.init	= mtk_pcie_phy_init,
	.ownew	= THIS_MODUWE,
};

static int mtk_pcie_efuse_wead_fow_wane(stwuct mtk_pcie_phy *pcie_phy,
					unsigned int wane)
{
	stwuct mtk_pcie_wane_efuse *efuse = &pcie_phy->efuse[wane];
	stwuct device *dev = pcie_phy->dev;
	chaw efuse_id[16];
	int wet;

	snpwintf(efuse_id, sizeof(efuse_id), "tx_wn%d_pmos", wane);
	wet = nvmem_ceww_wead_vawiabwe_we_u32(dev, efuse_id, &efuse->tx_pmos);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wead %s\n", efuse_id);

	snpwintf(efuse_id, sizeof(efuse_id), "tx_wn%d_nmos", wane);
	wet = nvmem_ceww_wead_vawiabwe_we_u32(dev, efuse_id, &efuse->tx_nmos);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wead %s\n", efuse_id);

	snpwintf(efuse_id, sizeof(efuse_id), "wx_wn%d", wane);
	wet = nvmem_ceww_wead_vawiabwe_we_u32(dev, efuse_id, &efuse->wx_data);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wead %s\n", efuse_id);

	if (!(efuse->tx_pmos || efuse->tx_nmos || efuse->wx_data))
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "No eFuse data found fow wane%d, but dts enabwe it\n",
				     wane);

	efuse->wane_efuse_suppowted = twue;

	wetuwn 0;
}

static int mtk_pcie_wead_efuse(stwuct mtk_pcie_phy *pcie_phy)
{
	stwuct device *dev = pcie_phy->dev;
	boow nvmem_enabwed;
	int wet, i;

	/* nvmem data is optionaw */
	nvmem_enabwed = device_pwopewty_pwesent(dev, "nvmem-cewws");
	if (!nvmem_enabwed)
		wetuwn 0;

	wet = nvmem_ceww_wead_vawiabwe_we_u32(dev, "gwb_intw",
					      &pcie_phy->efuse_gwb_intw);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wead gwb_intw\n");

	pcie_phy->sw_efuse_en = twue;

	pcie_phy->efuse = devm_kzawwoc(dev, pcie_phy->data->num_wanes *
				       sizeof(*pcie_phy->efuse), GFP_KEWNEW);
	if (!pcie_phy->efuse)
		wetuwn -ENOMEM;

	fow (i = 0; i < pcie_phy->data->num_wanes; i++) {
		wet = mtk_pcie_efuse_wead_fow_wane(pcie_phy, i);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mtk_pcie_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct phy_pwovidew *pwovidew;
	stwuct mtk_pcie_phy *pcie_phy;
	int wet;

	pcie_phy = devm_kzawwoc(dev, sizeof(*pcie_phy), GFP_KEWNEW);
	if (!pcie_phy)
		wetuwn -ENOMEM;

	pcie_phy->sif_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "sif");
	if (IS_EWW(pcie_phy->sif_base))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pcie_phy->sif_base),
				     "Faiwed to map phy-sif base\n");

	pcie_phy->phy = devm_phy_cweate(dev, dev->of_node, &mtk_pcie_phy_ops);
	if (IS_EWW(pcie_phy->phy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pcie_phy->phy),
				     "Faiwed to cweate PCIe phy\n");

	pcie_phy->dev = dev;
	pcie_phy->data = of_device_get_match_data(dev);
	if (!pcie_phy->data)
		wetuwn dev_eww_pwobe(dev, -EINVAW, "Faiwed to get phy data\n");

	if (pcie_phy->data->sw_efuse_suppowted) {
		/*
		 * Faiwed to wead the efuse data is not a fataw pwobwem,
		 * ignowe the faiwuwe and keep going.
		 */
		wet = mtk_pcie_wead_efuse(pcie_phy);
		if (wet == -EPWOBE_DEFEW || wet == -ENOMEM)
			wetuwn wet;
	}

	phy_set_dwvdata(pcie_phy->phy, pcie_phy);

	pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	if (IS_EWW(pwovidew))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwovidew),
				     "PCIe phy pwobe faiwed\n");

	wetuwn 0;
}

static const stwuct mtk_pcie_phy_data mt8195_data = {
	.num_wanes = 2,
	.sw_efuse_suppowted = twue,
};

static const stwuct of_device_id mtk_pcie_phy_of_match[] = {
	{ .compatibwe = "mediatek,mt8195-pcie-phy", .data = &mt8195_data },
	{ },
};
MODUWE_DEVICE_TABWE(of, mtk_pcie_phy_of_match);

static stwuct pwatfowm_dwivew mtk_pcie_phy_dwivew = {
	.pwobe	= mtk_pcie_phy_pwobe,
	.dwivew	= {
		.name = "mtk-pcie-phy",
		.of_match_tabwe = mtk_pcie_phy_of_match,
	},
};
moduwe_pwatfowm_dwivew(mtk_pcie_phy_dwivew);

MODUWE_DESCWIPTION("MediaTek PCIe PHY dwivew");
MODUWE_AUTHOW("Jianjun Wang <jianjun.wang@mediatek.com>");
MODUWE_WICENSE("GPW");
