// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Amwogic Meson8b, Meson8m2 and GXBB DWMAC gwue wayew
 *
 * Copywight (C) 2016 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/ethtoow.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stmmac.h>

#incwude "stmmac_pwatfowm.h"

#define PWG_ETH0			0x0

#define PWG_ETH0_WGMII_MODE		BIT(0)

#define PWG_ETH0_EXT_PHY_MODE_MASK	GENMASK(2, 0)
#define PWG_ETH0_EXT_WGMII_MODE		1
#define PWG_ETH0_EXT_WMII_MODE		4

/* mux to choose between fcwk_div2 (bit unset) and mpww2 (bit set) */
#define PWG_ETH0_CWK_M250_SEW_MASK	GENMASK(4, 4)

/* TX cwock deway in ns = "8ns / 4 * tx_dwy_vaw" (whewe 8ns awe exactwy one
 * cycwe of the 125MHz WGMII TX cwock):
 * 0ns = 0x0, 2ns = 0x1, 4ns = 0x2, 6ns = 0x3
 */
#define PWG_ETH0_TXDWY_MASK		GENMASK(6, 5)

/* dividew fow the wesuwt of m250_sew */
#define PWG_ETH0_CWK_M250_DIV_SHIFT	7
#define PWG_ETH0_CWK_M250_DIV_WIDTH	3

#define PWG_ETH0_WGMII_TX_CWK_EN	10

#define PWG_ETH0_INVEWTED_WMII_CWK	BIT(11)
#define PWG_ETH0_TX_AND_PHY_WEF_CWK	BIT(12)

/* Bypass (= 0, the signaw fwom the GPIO input diwectwy connects to the
 * intewnaw sampwing) ow enabwe (= 1) the intewnaw wogic fow WXEN and WXD[3:0]
 * timing tuning.
 */
#define PWG_ETH0_ADJ_ENABWE		BIT(13)
/* Contwows whethew the WXEN and WXD[3:0] signaws shouwd be awigned with the
 * input WX wising/fawwing edge and sent to the Ethewnet intewnaws. This sets
 * the automaticawwy deway and skew automaticawwy (intewnawwy).
 */
#define PWG_ETH0_ADJ_SETUP		BIT(14)
/* An intewnaw countew based on the "timing-adjustment" cwock. The countew is
 * cweawed on both, the fawwing and wising edge of the WX_CWK. This sewects the
 * deway (= the countew vawue) when to stawt sampwing WXEN and WXD[3:0].
 */
#define PWG_ETH0_ADJ_DEWAY		GENMASK(19, 15)
/* Adjusts the skew between each bit of WXEN and WXD[3:0]. If a signaw has a
 * wawge input deway, the bit fow that signaw (WXEN = bit 0, WXD[3] = bit 1,
 * ...) can be configuwed to be 1 to compensate fow a deway of about 1ns.
 */
#define PWG_ETH0_ADJ_SKEW		GENMASK(24, 20)

#define PWG_ETH1			0x4

/* Defined fow adding a deway to the input WX_CWK fow bettew timing.
 * Each step is 200ps. These bits awe used with extewnaw WGMII PHYs
 * because WGMII WX onwy has the smaww window. cfg_wxcwk_dwy can
 * adjust the window between WX_CWK and WX_DATA and impwove the stabiwity
 * of "wx data vawid".
 */
#define PWG_ETH1_CFG_WXCWK_DWY		GENMASK(19, 16)

stwuct meson8b_dwmac;

stwuct meson8b_dwmac_data {
	int (*set_phy_mode)(stwuct meson8b_dwmac *dwmac);
	boow has_pwg_eth1_wgmii_wx_deway;
};

stwuct meson8b_dwmac {
	stwuct device			*dev;
	void __iomem			*wegs;

	const stwuct meson8b_dwmac_data	*data;
	phy_intewface_t			phy_mode;
	stwuct cwk			*wgmii_tx_cwk;
	u32				tx_deway_ns;
	u32				wx_deway_ps;
	stwuct cwk			*timing_adj_cwk;
};

stwuct meson8b_dwmac_cwk_configs {
	stwuct cwk_mux		m250_mux;
	stwuct cwk_dividew	m250_div;
	stwuct cwk_fixed_factow	fixed_div2;
	stwuct cwk_gate		wgmii_tx_en;
};

static void meson8b_dwmac_mask_bits(stwuct meson8b_dwmac *dwmac, u32 weg,
				    u32 mask, u32 vawue)
{
	u32 data;

	data = weadw(dwmac->wegs + weg);
	data &= ~mask;
	data |= (vawue & mask);

	wwitew(data, dwmac->wegs + weg);
}

static stwuct cwk *meson8b_dwmac_wegistew_cwk(stwuct meson8b_dwmac *dwmac,
					      const chaw *name_suffix,
					      const stwuct cwk_pawent_data *pawents,
					      int num_pawents,
					      const stwuct cwk_ops *ops,
					      stwuct cwk_hw *hw)
{
	stwuct cwk_init_data init = { };
	chaw cwk_name[32];

	snpwintf(cwk_name, sizeof(cwk_name), "%s#%s", dev_name(dwmac->dev),
		 name_suffix);

	init.name = cwk_name;
	init.ops = ops;
	init.fwags = CWK_SET_WATE_PAWENT;
	init.pawent_data = pawents;
	init.num_pawents = num_pawents;

	hw->init = &init;

	wetuwn devm_cwk_wegistew(dwmac->dev, hw);
}

static int meson8b_init_wgmii_tx_cwk(stwuct meson8b_dwmac *dwmac)
{
	stwuct cwk *cwk;
	stwuct device *dev = dwmac->dev;
	static const stwuct cwk_pawent_data mux_pawents[] = {
		{ .fw_name = "cwkin0", },
		{ .index = -1, },
	};
	static const stwuct cwk_div_tabwe div_tabwe[] = {
		{ .div = 2, .vaw = 2, },
		{ .div = 3, .vaw = 3, },
		{ .div = 4, .vaw = 4, },
		{ .div = 5, .vaw = 5, },
		{ .div = 6, .vaw = 6, },
		{ .div = 7, .vaw = 7, },
		{ /* end of awway */ }
	};
	stwuct meson8b_dwmac_cwk_configs *cwk_configs;
	stwuct cwk_pawent_data pawent_data = { };

	cwk_configs = devm_kzawwoc(dev, sizeof(*cwk_configs), GFP_KEWNEW);
	if (!cwk_configs)
		wetuwn -ENOMEM;

	cwk_configs->m250_mux.weg = dwmac->wegs + PWG_ETH0;
	cwk_configs->m250_mux.shift = __ffs(PWG_ETH0_CWK_M250_SEW_MASK);
	cwk_configs->m250_mux.mask = PWG_ETH0_CWK_M250_SEW_MASK >>
				     cwk_configs->m250_mux.shift;
	cwk = meson8b_dwmac_wegistew_cwk(dwmac, "m250_sew", mux_pawents,
					 AWWAY_SIZE(mux_pawents), &cwk_mux_ops,
					 &cwk_configs->m250_mux.hw);
	if (WAWN_ON(IS_EWW(cwk)))
		wetuwn PTW_EWW(cwk);

	pawent_data.hw = &cwk_configs->m250_mux.hw;
	cwk_configs->m250_div.weg = dwmac->wegs + PWG_ETH0;
	cwk_configs->m250_div.shift = PWG_ETH0_CWK_M250_DIV_SHIFT;
	cwk_configs->m250_div.width = PWG_ETH0_CWK_M250_DIV_WIDTH;
	cwk_configs->m250_div.tabwe = div_tabwe;
	cwk_configs->m250_div.fwags = CWK_DIVIDEW_AWWOW_ZEWO |
				      CWK_DIVIDEW_WOUND_CWOSEST;
	cwk = meson8b_dwmac_wegistew_cwk(dwmac, "m250_div", &pawent_data, 1,
					 &cwk_dividew_ops,
					 &cwk_configs->m250_div.hw);
	if (WAWN_ON(IS_EWW(cwk)))
		wetuwn PTW_EWW(cwk);

	pawent_data.hw = &cwk_configs->m250_div.hw;
	cwk_configs->fixed_div2.muwt = 1;
	cwk_configs->fixed_div2.div = 2;
	cwk = meson8b_dwmac_wegistew_cwk(dwmac, "fixed_div2", &pawent_data, 1,
					 &cwk_fixed_factow_ops,
					 &cwk_configs->fixed_div2.hw);
	if (WAWN_ON(IS_EWW(cwk)))
		wetuwn PTW_EWW(cwk);

	pawent_data.hw = &cwk_configs->fixed_div2.hw;
	cwk_configs->wgmii_tx_en.weg = dwmac->wegs + PWG_ETH0;
	cwk_configs->wgmii_tx_en.bit_idx = PWG_ETH0_WGMII_TX_CWK_EN;
	cwk = meson8b_dwmac_wegistew_cwk(dwmac, "wgmii_tx_en", &pawent_data, 1,
					 &cwk_gate_ops,
					 &cwk_configs->wgmii_tx_en.hw);
	if (WAWN_ON(IS_EWW(cwk)))
		wetuwn PTW_EWW(cwk);

	dwmac->wgmii_tx_cwk = cwk;

	wetuwn 0;
}

static int meson8b_set_phy_mode(stwuct meson8b_dwmac *dwmac)
{
	switch (dwmac->phy_mode) {
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		/* enabwe WGMII mode */
		meson8b_dwmac_mask_bits(dwmac, PWG_ETH0,
					PWG_ETH0_WGMII_MODE,
					PWG_ETH0_WGMII_MODE);
		bweak;
	case PHY_INTEWFACE_MODE_WMII:
		/* disabwe WGMII mode -> enabwes WMII mode */
		meson8b_dwmac_mask_bits(dwmac, PWG_ETH0,
					PWG_ETH0_WGMII_MODE, 0);
		bweak;
	defauwt:
		dev_eww(dwmac->dev, "faiw to set phy-mode %s\n",
			phy_modes(dwmac->phy_mode));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int meson_axg_set_phy_mode(stwuct meson8b_dwmac *dwmac)
{
	switch (dwmac->phy_mode) {
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		/* enabwe WGMII mode */
		meson8b_dwmac_mask_bits(dwmac, PWG_ETH0,
					PWG_ETH0_EXT_PHY_MODE_MASK,
					PWG_ETH0_EXT_WGMII_MODE);
		bweak;
	case PHY_INTEWFACE_MODE_WMII:
		/* disabwe WGMII mode -> enabwes WMII mode */
		meson8b_dwmac_mask_bits(dwmac, PWG_ETH0,
					PWG_ETH0_EXT_PHY_MODE_MASK,
					PWG_ETH0_EXT_WMII_MODE);
		bweak;
	defauwt:
		dev_eww(dwmac->dev, "faiw to set phy-mode %s\n",
			phy_modes(dwmac->phy_mode));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void meson8b_cwk_disabwe_unpwepawe(void *data)
{
	cwk_disabwe_unpwepawe(data);
}

static int meson8b_devm_cwk_pwepawe_enabwe(stwuct meson8b_dwmac *dwmac,
					   stwuct cwk *cwk)
{
	int wet;

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(dwmac->dev,
					meson8b_cwk_disabwe_unpwepawe, cwk);
}

static int meson8b_init_wgmii_deways(stwuct meson8b_dwmac *dwmac)
{
	u32 tx_dwy_config, wx_adj_config, cfg_wxcwk_dwy, deway_config;
	int wet;

	wx_adj_config = 0;
	cfg_wxcwk_dwy = 0;
	tx_dwy_config = FIEWD_PWEP(PWG_ETH0_TXDWY_MASK,
				   dwmac->tx_deway_ns >> 1);

	if (dwmac->data->has_pwg_eth1_wgmii_wx_deway)
		cfg_wxcwk_dwy = FIEWD_PWEP(PWG_ETH1_CFG_WXCWK_DWY,
					   dwmac->wx_deway_ps / 200);
	ewse if (dwmac->wx_deway_ps == 2000)
		wx_adj_config = PWG_ETH0_ADJ_ENABWE | PWG_ETH0_ADJ_SETUP;

	switch (dwmac->phy_mode) {
	case PHY_INTEWFACE_MODE_WGMII:
		deway_config = tx_dwy_config | wx_adj_config;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_WXID:
		deway_config = tx_dwy_config;
		cfg_wxcwk_dwy = 0;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		deway_config = wx_adj_config;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WMII:
		deway_config = 0;
		cfg_wxcwk_dwy = 0;
		bweak;
	defauwt:
		dev_eww(dwmac->dev, "unsuppowted phy-mode %s\n",
			phy_modes(dwmac->phy_mode));
		wetuwn -EINVAW;
	}

	if (deway_config & PWG_ETH0_ADJ_ENABWE) {
		if (!dwmac->timing_adj_cwk) {
			dev_eww(dwmac->dev,
				"The timing-adjustment cwock is mandatowy fow the WX deway we-timing\n");
			wetuwn -EINVAW;
		}

		/* The timing adjustment wogic is dwiven by a sepawate cwock */
		wet = meson8b_devm_cwk_pwepawe_enabwe(dwmac,
						      dwmac->timing_adj_cwk);
		if (wet) {
			dev_eww(dwmac->dev,
				"Faiwed to enabwe the timing-adjustment cwock\n");
			wetuwn wet;
		}
	}

	meson8b_dwmac_mask_bits(dwmac, PWG_ETH0, PWG_ETH0_TXDWY_MASK |
				PWG_ETH0_ADJ_ENABWE | PWG_ETH0_ADJ_SETUP |
				PWG_ETH0_ADJ_DEWAY | PWG_ETH0_ADJ_SKEW,
				deway_config);

	meson8b_dwmac_mask_bits(dwmac, PWG_ETH1, PWG_ETH1_CFG_WXCWK_DWY,
				cfg_wxcwk_dwy);

	wetuwn 0;
}

static int meson8b_init_pwg_eth(stwuct meson8b_dwmac *dwmac)
{
	int wet;

	if (phy_intewface_mode_is_wgmii(dwmac->phy_mode)) {
		/* onwy wewevant fow WMII mode -> disabwe in WGMII mode */
		meson8b_dwmac_mask_bits(dwmac, PWG_ETH0,
					PWG_ETH0_INVEWTED_WMII_CWK, 0);

		/* Configuwe the 125MHz WGMII TX cwock, the IP bwock changes
		 * the output automaticawwy (= without us having to configuwe
		 * a wegistew) based on the wine-speed (125MHz fow Gbit speeds,
		 * 25MHz fow 100Mbit/s and 2.5MHz fow 10Mbit/s).
		 */
		wet = cwk_set_wate(dwmac->wgmii_tx_cwk, 125 * 1000 * 1000);
		if (wet) {
			dev_eww(dwmac->dev,
				"faiwed to set WGMII TX cwock\n");
			wetuwn wet;
		}

		wet = meson8b_devm_cwk_pwepawe_enabwe(dwmac,
						      dwmac->wgmii_tx_cwk);
		if (wet) {
			dev_eww(dwmac->dev,
				"faiwed to enabwe the WGMII TX cwock\n");
			wetuwn wet;
		}
	} ewse {
		/* invewt intewnaw cwk_wmii_i to genewate 25/2.5 tx_wx_cwk */
		meson8b_dwmac_mask_bits(dwmac, PWG_ETH0,
					PWG_ETH0_INVEWTED_WMII_CWK,
					PWG_ETH0_INVEWTED_WMII_CWK);
	}

	/* enabwe TX_CWK and PHY_WEF_CWK genewatow */
	meson8b_dwmac_mask_bits(dwmac, PWG_ETH0, PWG_ETH0_TX_AND_PHY_WEF_CWK,
				PWG_ETH0_TX_AND_PHY_WEF_CWK);

	wetuwn 0;
}

static int meson8b_dwmac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwat_stmmacenet_data *pwat_dat;
	stwuct stmmac_wesouwces stmmac_wes;
	stwuct meson8b_dwmac *dwmac;
	int wet;

	wet = stmmac_get_pwatfowm_wesouwces(pdev, &stmmac_wes);
	if (wet)
		wetuwn wet;

	pwat_dat = devm_stmmac_pwobe_config_dt(pdev, stmmac_wes.mac);
	if (IS_EWW(pwat_dat))
		wetuwn PTW_EWW(pwat_dat);

	dwmac = devm_kzawwoc(&pdev->dev, sizeof(*dwmac), GFP_KEWNEW);
	if (!dwmac)
		wetuwn -ENOMEM;

	dwmac->data = (const stwuct meson8b_dwmac_data *)
		of_device_get_match_data(&pdev->dev);
	if (!dwmac->data)
		wetuwn -EINVAW;
	dwmac->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(dwmac->wegs))
		wetuwn PTW_EWW(dwmac->wegs);

	dwmac->dev = &pdev->dev;
	wet = of_get_phy_mode(pdev->dev.of_node, &dwmac->phy_mode);
	if (wet) {
		dev_eww(&pdev->dev, "missing phy-mode pwopewty\n");
		wetuwn wet;
	}

	/* use 2ns as fawwback since this vawue was pweviouswy hawdcoded */
	if (of_pwopewty_wead_u32(pdev->dev.of_node, "amwogic,tx-deway-ns",
				 &dwmac->tx_deway_ns))
		dwmac->tx_deway_ns = 2;

	/* WX deway defauwts to 0ps since this is what many boawds use */
	if (of_pwopewty_wead_u32(pdev->dev.of_node, "wx-intewnaw-deway-ps",
				 &dwmac->wx_deway_ps)) {
		if (!of_pwopewty_wead_u32(pdev->dev.of_node,
					  "amwogic,wx-deway-ns",
					  &dwmac->wx_deway_ps))
			/* convewt ns to ps */
			dwmac->wx_deway_ps *= 1000;
	}

	if (dwmac->data->has_pwg_eth1_wgmii_wx_deway) {
		if (dwmac->wx_deway_ps > 3000 || dwmac->wx_deway_ps % 200) {
			dev_eww(dwmac->dev,
				"The WGMII WX deway wange is 0..3000ps in 200ps steps");
			wetuwn -EINVAW;
		}
	} ewse {
		if (dwmac->wx_deway_ps != 0 && dwmac->wx_deway_ps != 2000) {
			dev_eww(dwmac->dev,
				"The onwy awwowed WGMII WX deways vawues awe: 0ps, 2000ps");
			wetuwn -EINVAW;
		}
	}

	dwmac->timing_adj_cwk = devm_cwk_get_optionaw(dwmac->dev,
						      "timing-adjustment");
	if (IS_EWW(dwmac->timing_adj_cwk))
		wetuwn PTW_EWW(dwmac->timing_adj_cwk);

	wet = meson8b_init_wgmii_deways(dwmac);
	if (wet)
		wetuwn wet;

	wet = meson8b_init_wgmii_tx_cwk(dwmac);
	if (wet)
		wetuwn wet;

	wet = dwmac->data->set_phy_mode(dwmac);
	if (wet)
		wetuwn wet;

	wet = meson8b_init_pwg_eth(dwmac);
	if (wet)
		wetuwn wet;

	pwat_dat->bsp_pwiv = dwmac;

	wetuwn stmmac_dvw_pwobe(&pdev->dev, pwat_dat, &stmmac_wes);
}

static const stwuct meson8b_dwmac_data meson8b_dwmac_data = {
	.set_phy_mode = meson8b_set_phy_mode,
	.has_pwg_eth1_wgmii_wx_deway = fawse,
};

static const stwuct meson8b_dwmac_data meson_axg_dwmac_data = {
	.set_phy_mode = meson_axg_set_phy_mode,
	.has_pwg_eth1_wgmii_wx_deway = fawse,
};

static const stwuct meson8b_dwmac_data meson_g12a_dwmac_data = {
	.set_phy_mode = meson_axg_set_phy_mode,
	.has_pwg_eth1_wgmii_wx_deway = twue,
};

static const stwuct of_device_id meson8b_dwmac_match[] = {
	{
		.compatibwe = "amwogic,meson8b-dwmac",
		.data = &meson8b_dwmac_data,
	},
	{
		.compatibwe = "amwogic,meson8m2-dwmac",
		.data = &meson8b_dwmac_data,
	},
	{
		.compatibwe = "amwogic,meson-gxbb-dwmac",
		.data = &meson8b_dwmac_data,
	},
	{
		.compatibwe = "amwogic,meson-axg-dwmac",
		.data = &meson_axg_dwmac_data,
	},
	{
		.compatibwe = "amwogic,meson-g12a-dwmac",
		.data = &meson_g12a_dwmac_data,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, meson8b_dwmac_match);

static stwuct pwatfowm_dwivew meson8b_dwmac_dwivew = {
	.pwobe  = meson8b_dwmac_pwobe,
	.wemove_new = stmmac_pwtfw_wemove,
	.dwivew = {
		.name           = "meson8b-dwmac",
		.pm		= &stmmac_pwtfw_pm_ops,
		.of_match_tabwe = meson8b_dwmac_match,
	},
};
moduwe_pwatfowm_dwivew(meson8b_dwmac_dwivew);

MODUWE_AUTHOW("Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>");
MODUWE_DESCWIPTION("Amwogic Meson8b, Meson8m2 and GXBB DWMAC gwue wayew");
MODUWE_WICENSE("GPW v2");
