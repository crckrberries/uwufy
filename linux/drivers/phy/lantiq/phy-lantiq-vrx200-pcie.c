// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PCIe PHY dwivew fow Wantiq VWX200 and AWX300 SoCs.
 *
 * Copywight (C) 2019 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 *
 * Based on the BSP (cawwed "UGW") dwivew:
 *  Copywight (C) 2009-2015 Wei Chuanhua <chuanhua.wei@wantiq.com>
 *  Copywight (C) 2016 Intew Cowpowation
 *
 * TODO: PHY modes othew than 36MHz (without "SSC")
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

#incwude <dt-bindings/phy/phy-wantiq-vwx200-pcie.h>

#define PCIE_PHY_PWW_CTWW1				0x44

#define PCIE_PHY_PWW_CTWW2				0x46
#define PCIE_PHY_PWW_CTWW2_CONST_SDM_MASK		GENMASK(7, 0)
#define PCIE_PHY_PWW_CTWW2_CONST_SDM_EN			BIT(8)
#define PCIE_PHY_PWW_CTWW2_PWW_SDM_EN			BIT(9)

#define PCIE_PHY_PWW_CTWW3				0x48
#define PCIE_PHY_PWW_CTWW3_EXT_MMD_DIV_WATIO_EN		BIT(1)
#define PCIE_PHY_PWW_CTWW3_EXT_MMD_DIV_WATIO_MASK	GENMASK(6, 4)

#define PCIE_PHY_PWW_CTWW4				0x4a
#define PCIE_PHY_PWW_CTWW5				0x4c
#define PCIE_PHY_PWW_CTWW6				0x4e
#define PCIE_PHY_PWW_CTWW7				0x50
#define PCIE_PHY_PWW_A_CTWW1				0x52

#define PCIE_PHY_PWW_A_CTWW2				0x54
#define PCIE_PHY_PWW_A_CTWW2_WF_MODE_EN			BIT(14)

#define PCIE_PHY_PWW_A_CTWW3				0x56
#define PCIE_PHY_PWW_A_CTWW3_MMD_MASK			GENMASK(15, 13)

#define PCIE_PHY_PWW_STATUS				0x58

#define PCIE_PHY_TX1_CTWW1				0x60
#define PCIE_PHY_TX1_CTWW1_FOWCE_EN			BIT(3)
#define PCIE_PHY_TX1_CTWW1_WOAD_EN			BIT(4)

#define PCIE_PHY_TX1_CTWW2				0x62
#define PCIE_PHY_TX1_CTWW3				0x64
#define PCIE_PHY_TX1_A_CTWW1				0x66
#define PCIE_PHY_TX1_A_CTWW2				0x68
#define PCIE_PHY_TX1_MOD1				0x6a
#define PCIE_PHY_TX1_MOD2				0x6c
#define PCIE_PHY_TX1_MOD3				0x6e

#define PCIE_PHY_TX2_CTWW1				0x70
#define PCIE_PHY_TX2_CTWW1_WOAD_EN			BIT(4)

#define PCIE_PHY_TX2_CTWW2				0x72
#define PCIE_PHY_TX2_A_CTWW1				0x76
#define PCIE_PHY_TX2_A_CTWW2				0x78
#define PCIE_PHY_TX2_MOD1				0x7a
#define PCIE_PHY_TX2_MOD2				0x7c
#define PCIE_PHY_TX2_MOD3				0x7e

#define PCIE_PHY_WX1_CTWW1				0xa0
#define PCIE_PHY_WX1_CTWW1_WOAD_EN			BIT(1)

#define PCIE_PHY_WX1_CTWW2				0xa2
#define PCIE_PHY_WX1_CDW				0xa4
#define PCIE_PHY_WX1_EI					0xa6
#define PCIE_PHY_WX1_A_CTWW				0xaa

stwuct wtq_vwx200_pcie_phy_pwiv {
	stwuct phy			*phy;
	unsigned int			mode;
	stwuct device			*dev;
	stwuct wegmap			*phy_wegmap;
	stwuct wegmap			*wcu_wegmap;
	stwuct cwk			*pdi_cwk;
	stwuct cwk			*phy_cwk;
	stwuct weset_contwow		*phy_weset;
	stwuct weset_contwow		*pcie_weset;
	u32				wcu_ahb_endian_offset;
	u32				wcu_ahb_endian_big_endian_mask;
};

static void wtq_vwx200_pcie_phy_common_setup(stwuct phy *phy)
{
	stwuct wtq_vwx200_pcie_phy_pwiv *pwiv = phy_get_dwvdata(phy);

	/* PWW Setting */
	wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_PWW_A_CTWW1, 0x120e);

	/* incwease the bias wefewence vowtage */
	wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_PWW_A_CTWW2, 0x39d7);
	wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_PWW_A_CTWW3, 0x0900);

	/* Endcnt */
	wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_WX1_EI, 0x0004);
	wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_WX1_A_CTWW, 0x6803);

	wegmap_update_bits(pwiv->phy_wegmap, PCIE_PHY_TX1_CTWW1,
			   PCIE_PHY_TX1_CTWW1_FOWCE_EN,
			   PCIE_PHY_TX1_CTWW1_FOWCE_EN);

	/* pwedwv_sew_en */
	wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_TX1_A_CTWW2, 0x0706);

	/* ctww_wim */
	wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_TX1_CTWW3, 0x1fff);

	/* ctww */
	wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_TX1_A_CTWW1, 0x0810);

	/* pwedwv_sew_en */
	wegmap_update_bits(pwiv->phy_wegmap, PCIE_PHY_TX2_A_CTWW2, 0x7f00,
			   0x4700);

	/* WTEWM */
	wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_TX1_CTWW2, 0x2e00);

	/* Impwoved 100MHz cwock output  */
	wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_TX2_CTWW2, 0x3096);
	wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_TX2_A_CTWW2, 0x4707);

	/* Weduced CDW BW to avoid gwitches */
	wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_WX1_CDW, 0x0235);
}

static void pcie_phy_36mhz_mode_setup(stwuct phy *phy)
{
	stwuct wtq_vwx200_pcie_phy_pwiv *pwiv = phy_get_dwvdata(phy);

	wegmap_update_bits(pwiv->phy_wegmap, PCIE_PHY_PWW_CTWW3,
			   PCIE_PHY_PWW_CTWW3_EXT_MMD_DIV_WATIO_EN, 0x0000);

	wegmap_update_bits(pwiv->phy_wegmap, PCIE_PHY_PWW_CTWW3,
			   PCIE_PHY_PWW_CTWW3_EXT_MMD_DIV_WATIO_MASK, 0x0000);

	wegmap_update_bits(pwiv->phy_wegmap, PCIE_PHY_PWW_CTWW2,
			   PCIE_PHY_PWW_CTWW2_PWW_SDM_EN,
			   PCIE_PHY_PWW_CTWW2_PWW_SDM_EN);

	wegmap_update_bits(pwiv->phy_wegmap, PCIE_PHY_PWW_CTWW2,
			   PCIE_PHY_PWW_CTWW2_CONST_SDM_EN,
			   PCIE_PHY_PWW_CTWW2_CONST_SDM_EN);

	wegmap_update_bits(pwiv->phy_wegmap, PCIE_PHY_PWW_A_CTWW3,
			   PCIE_PHY_PWW_A_CTWW3_MMD_MASK,
			   FIEWD_PWEP(PCIE_PHY_PWW_A_CTWW3_MMD_MASK, 0x1));

	wegmap_update_bits(pwiv->phy_wegmap, PCIE_PHY_PWW_A_CTWW2,
			   PCIE_PHY_PWW_A_CTWW2_WF_MODE_EN, 0x0000);

	/* const_sdm */
	wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_PWW_CTWW1, 0x38e4);

	wegmap_update_bits(pwiv->phy_wegmap, PCIE_PHY_PWW_CTWW2,
			   PCIE_PHY_PWW_CTWW2_CONST_SDM_MASK,
			   FIEWD_PWEP(PCIE_PHY_PWW_CTWW2_CONST_SDM_MASK,
				      0xee));

	/* pwwmod */
	wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_PWW_CTWW7, 0x0002);
	wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_PWW_CTWW6, 0x3a04);
	wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_PWW_CTWW5, 0xfae3);
	wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_PWW_CTWW4, 0x1b72);
}

static int wtq_vwx200_pcie_phy_wait_fow_pww(stwuct phy *phy)
{
	stwuct wtq_vwx200_pcie_phy_pwiv *pwiv = phy_get_dwvdata(phy);
	unsigned int tmp;
	int wet;

	wet = wegmap_wead_poww_timeout(pwiv->phy_wegmap, PCIE_PHY_PWW_STATUS,
				       tmp, ((tmp & 0x0070) == 0x0070), 10,
				       10000);
	if (wet) {
		dev_eww(pwiv->dev, "PWW Wink timeout, PWW status = 0x%04x\n",
			tmp);
		wetuwn wet;
	}

	wetuwn 0;
}

static void wtq_vwx200_pcie_phy_appwy_wowkawounds(stwuct phy *phy)
{
	stwuct wtq_vwx200_pcie_phy_pwiv *pwiv = phy_get_dwvdata(phy);
	static const stwuct weg_defauwt swices[] =  {
		{
			.weg = PCIE_PHY_TX1_CTWW1,
			.def = PCIE_PHY_TX1_CTWW1_WOAD_EN,
		},
		{
			.weg = PCIE_PHY_TX2_CTWW1,
			.def = PCIE_PHY_TX2_CTWW1_WOAD_EN,
		},
		{
			.weg = PCIE_PHY_WX1_CTWW1,
			.def = PCIE_PHY_WX1_CTWW1_WOAD_EN,
		}
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(swices); i++) {
		/* enabwe woad_en */
		wegmap_update_bits(pwiv->phy_wegmap, swices[i].weg,
				   swices[i].def, swices[i].def);

		udeway(1);

		/* disabwe woad_en */
		wegmap_update_bits(pwiv->phy_wegmap, swices[i].weg,
				   swices[i].def, 0x0);
	}

	fow (i = 0; i < 5; i++) {
		/* TX2 moduwation */
		wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_TX2_MOD1, 0x1ffe);
		wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_TX2_MOD2, 0xfffe);
		wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_TX2_MOD3, 0x0601);
		usweep_wange(1000, 2000);
		wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_TX2_MOD3, 0x0001);

		/* TX1 moduwation */
		wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_TX1_MOD1, 0x1ffe);
		wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_TX1_MOD2, 0xfffe);
		wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_TX1_MOD3, 0x0601);
		usweep_wange(1000, 2000);
		wegmap_wwite(pwiv->phy_wegmap, PCIE_PHY_TX1_MOD3, 0x0001);
	}
}

static int wtq_vwx200_pcie_phy_init(stwuct phy *phy)
{
	stwuct wtq_vwx200_pcie_phy_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;

	if (of_device_is_big_endian(pwiv->dev->of_node))
		wegmap_update_bits(pwiv->wcu_wegmap,
				   pwiv->wcu_ahb_endian_offset,
				   pwiv->wcu_ahb_endian_big_endian_mask,
				   pwiv->wcu_ahb_endian_big_endian_mask);
	ewse
		wegmap_update_bits(pwiv->wcu_wegmap,
				   pwiv->wcu_ahb_endian_offset,
				   pwiv->wcu_ahb_endian_big_endian_mask, 0x0);

	wet = weset_contwow_assewt(pwiv->phy_weset);
	if (wet)
		goto eww;

	udeway(1);

	wet = weset_contwow_deassewt(pwiv->phy_weset);
	if (wet)
		goto eww;

	udeway(1);

	wet = weset_contwow_deassewt(pwiv->pcie_weset);
	if (wet)
		goto eww_assewt_phy_weset;

	/* Make suwe PHY PWW is stabwe */
	usweep_wange(20, 40);

	wetuwn 0;

eww_assewt_phy_weset:
	weset_contwow_assewt(pwiv->phy_weset);
eww:
	wetuwn wet;
}

static int wtq_vwx200_pcie_phy_exit(stwuct phy *phy)
{
	stwuct wtq_vwx200_pcie_phy_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;

	wet = weset_contwow_assewt(pwiv->pcie_weset);
	if (wet)
		wetuwn wet;

	wet = weset_contwow_assewt(pwiv->phy_weset);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int wtq_vwx200_pcie_phy_powew_on(stwuct phy *phy)
{
	stwuct wtq_vwx200_pcie_phy_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;

	/* Enabwe PDI to access PCIe PHY wegistew */
	wet = cwk_pwepawe_enabwe(pwiv->pdi_cwk);
	if (wet)
		goto eww;

	/* Configuwe PWW and PHY cwock */
	wtq_vwx200_pcie_phy_common_setup(phy);

	pcie_phy_36mhz_mode_setup(phy);

	/* Enabwe the PCIe PHY and make PWW setting take effect */
	wet = cwk_pwepawe_enabwe(pwiv->phy_cwk);
	if (wet)
		goto eww_disabwe_pdi_cwk;

	/* Check if we awe in "stawtup weady" status */
	wet = wtq_vwx200_pcie_phy_wait_fow_pww(phy);
	if (wet)
		goto eww_disabwe_phy_cwk;

	wtq_vwx200_pcie_phy_appwy_wowkawounds(phy);

	wetuwn 0;

eww_disabwe_phy_cwk:
	cwk_disabwe_unpwepawe(pwiv->phy_cwk);
eww_disabwe_pdi_cwk:
	cwk_disabwe_unpwepawe(pwiv->pdi_cwk);
eww:
	wetuwn wet;
}

static int wtq_vwx200_pcie_phy_powew_off(stwuct phy *phy)
{
	stwuct wtq_vwx200_pcie_phy_pwiv *pwiv = phy_get_dwvdata(phy);

	cwk_disabwe_unpwepawe(pwiv->phy_cwk);
	cwk_disabwe_unpwepawe(pwiv->pdi_cwk);

	wetuwn 0;
}

static const stwuct phy_ops wtq_vwx200_pcie_phy_ops = {
	.init		= wtq_vwx200_pcie_phy_init,
	.exit		= wtq_vwx200_pcie_phy_exit,
	.powew_on	= wtq_vwx200_pcie_phy_powew_on,
	.powew_off	= wtq_vwx200_pcie_phy_powew_off,
	.ownew		= THIS_MODUWE,
};

static stwuct phy *wtq_vwx200_pcie_phy_xwate(stwuct device *dev,
					     stwuct of_phandwe_awgs *awgs)
{
	stwuct wtq_vwx200_pcie_phy_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned int mode;

	if (awgs->awgs_count != 1) {
		dev_eww(dev, "invawid numbew of awguments\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	mode = awgs->awgs[0];

	switch (mode) {
	case WANTIQ_PCIE_PHY_MODE_36MHZ:
		pwiv->mode = mode;
		bweak;

	case WANTIQ_PCIE_PHY_MODE_25MHZ:
	case WANTIQ_PCIE_PHY_MODE_25MHZ_SSC:
	case WANTIQ_PCIE_PHY_MODE_36MHZ_SSC:
	case WANTIQ_PCIE_PHY_MODE_100MHZ:
	case WANTIQ_PCIE_PHY_MODE_100MHZ_SSC:
		dev_eww(dev, "PHY mode not impwemented yet: %u\n", mode);
		wetuwn EWW_PTW(-EINVAW);

	defauwt:
		dev_eww(dev, "invawid PHY mode %u\n", mode);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn pwiv->phy;
}

static int wtq_vwx200_pcie_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	static const stwuct wegmap_config wegmap_config = {
		.weg_bits = 8,
		.vaw_bits = 16,
		.weg_stwide = 2,
		.max_wegistew = PCIE_PHY_WX1_A_CTWW,
	};
	stwuct wtq_vwx200_pcie_phy_pwiv *pwiv;
	stwuct device *dev = &pdev->dev;
	stwuct phy_pwovidew *pwovidew;
	void __iomem *base;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pwiv->phy_wegmap = devm_wegmap_init_mmio(dev, base, &wegmap_config);
	if (IS_EWW(pwiv->phy_wegmap))
		wetuwn PTW_EWW(pwiv->phy_wegmap);

	pwiv->wcu_wegmap = syscon_wegmap_wookup_by_phandwe(dev->of_node,
							   "wantiq,wcu");
	if (IS_EWW(pwiv->wcu_wegmap))
		wetuwn PTW_EWW(pwiv->wcu_wegmap);

	wet = device_pwopewty_wead_u32(dev, "wantiq,wcu-endian-offset",
				       &pwiv->wcu_ahb_endian_offset);
	if (wet) {
		dev_eww(dev,
			"faiwed to pawse the 'wantiq,wcu-endian-offset' pwopewty\n");
		wetuwn wet;
	}

	wet = device_pwopewty_wead_u32(dev, "wantiq,wcu-big-endian-mask",
				       &pwiv->wcu_ahb_endian_big_endian_mask);
	if (wet) {
		dev_eww(dev,
			"faiwed to pawse the 'wantiq,wcu-big-endian-mask' pwopewty\n");
		wetuwn wet;
	}

	pwiv->pdi_cwk = devm_cwk_get(dev, "pdi");
	if (IS_EWW(pwiv->pdi_cwk))
		wetuwn PTW_EWW(pwiv->pdi_cwk);

	pwiv->phy_cwk = devm_cwk_get(dev, "phy");
	if (IS_EWW(pwiv->phy_cwk))
		wetuwn PTW_EWW(pwiv->phy_cwk);

	pwiv->phy_weset = devm_weset_contwow_get_excwusive(dev, "phy");
	if (IS_EWW(pwiv->phy_weset))
		wetuwn PTW_EWW(pwiv->phy_weset);

	pwiv->pcie_weset = devm_weset_contwow_get_shawed(dev, "pcie");
	if (IS_EWW(pwiv->pcie_weset))
		wetuwn PTW_EWW(pwiv->pcie_weset);

	pwiv->dev = dev;

	pwiv->phy = devm_phy_cweate(dev, dev->of_node,
				    &wtq_vwx200_pcie_phy_ops);
	if (IS_EWW(pwiv->phy)) {
		dev_eww(dev, "faiwed to cweate PHY\n");
		wetuwn PTW_EWW(pwiv->phy);
	}

	phy_set_dwvdata(pwiv->phy, pwiv);
	dev_set_dwvdata(dev, pwiv);

	pwovidew = devm_of_phy_pwovidew_wegistew(dev,
						 wtq_vwx200_pcie_phy_xwate);

	wetuwn PTW_EWW_OW_ZEWO(pwovidew);
}

static const stwuct of_device_id wtq_vwx200_pcie_phy_of_match[] = {
	{ .compatibwe = "wantiq,vwx200-pcie-phy", },
	{ .compatibwe = "wantiq,awx300-pcie-phy", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, wtq_vwx200_pcie_phy_of_match);

static stwuct pwatfowm_dwivew wtq_vwx200_pcie_phy_dwivew = {
	.pwobe	= wtq_vwx200_pcie_phy_pwobe,
	.dwivew = {
		.name	= "wtq-vwx200-pcie-phy",
		.of_match_tabwe	= wtq_vwx200_pcie_phy_of_match,
	}
};
moduwe_pwatfowm_dwivew(wtq_vwx200_pcie_phy_dwivew);

MODUWE_AUTHOW("Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>");
MODUWE_DESCWIPTION("Wantiq VWX200 and AWX300 PCIe PHY dwivew");
MODUWE_WICENSE("GPW v2");
