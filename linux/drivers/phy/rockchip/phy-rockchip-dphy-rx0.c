// SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT)
/*
 * Wockchip MIPI Synopsys DPHY WX0 dwivew
 *
 * Copywight (C) 2019 Cowwabowa, Wtd.
 *
 * Based on:
 *
 * dwivews/media/pwatfowm/wockchip/isp1/mipi_dphy_sy.c
 * in https://chwomium.googwesouwce.com/chwomiumos/thiwd_pawty/kewnew,
 * chwomeos-4.4 bwanch.
 *
 * Copywight (C) 2017 Fuzhou Wockchip Ewectwonics Co., Wtd.
 *   Jacob Chen <jacob2.chen@wock-chips.com>
 *   Shunqian Zheng <zhengsq@wock-chips.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/phy/phy-mipi-dphy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define WK3399_GWF_SOC_CON9		0x6224
#define WK3399_GWF_SOC_CON21		0x6254
#define WK3399_GWF_SOC_CON22		0x6258
#define WK3399_GWF_SOC_CON23		0x625c
#define WK3399_GWF_SOC_CON24		0x6260
#define WK3399_GWF_SOC_CON25		0x6264
#define WK3399_GWF_SOC_STATUS1		0xe2a4

#define CWOCK_WANE_HS_WX_CONTWOW	0x34
#define WANE0_HS_WX_CONTWOW		0x44
#define WANE1_HS_WX_CONTWOW		0x54
#define WANE2_HS_WX_CONTWOW		0x84
#define WANE3_HS_WX_CONTWOW		0x94
#define WANES_THS_SETTWE_CONTWOW	0x75
#define THS_SETTWE_COUNTEW_THWESHOWD	0x04

stwuct hsfweq_wange {
	u16 wange_h;
	u8 cfg_bit;
};

static const stwuct hsfweq_wange wk3399_mipidphy_hsfweq_wanges[] = {
	{   89, 0x00 }, {   99, 0x10 }, {  109, 0x20 }, {  129, 0x01 },
	{  139, 0x11 }, {  149, 0x21 }, {  169, 0x02 }, {  179, 0x12 },
	{  199, 0x22 }, {  219, 0x03 }, {  239, 0x13 }, {  249, 0x23 },
	{  269, 0x04 }, {  299, 0x14 }, {  329, 0x05 }, {  359, 0x15 },
	{  399, 0x25 }, {  449, 0x06 }, {  499, 0x16 }, {  549, 0x07 },
	{  599, 0x17 }, {  649, 0x08 }, {  699, 0x18 }, {  749, 0x09 },
	{  799, 0x19 }, {  849, 0x29 }, {  899, 0x39 }, {  949, 0x0a },
	{  999, 0x1a }, { 1049, 0x2a }, { 1099, 0x3a }, { 1149, 0x0b },
	{ 1199, 0x1b }, { 1249, 0x2b }, { 1299, 0x3b }, { 1349, 0x0c },
	{ 1399, 0x1c }, { 1449, 0x2c }, { 1500, 0x3c }
};

static const chaw * const wk3399_mipidphy_cwks[] = {
	"dphy-wef",
	"dphy-cfg",
	"gwf",
};

enum dphy_weg_id {
	GWF_DPHY_WX0_TUWNDISABWE = 0,
	GWF_DPHY_WX0_FOWCEWXMODE,
	GWF_DPHY_WX0_FOWCETXSTOPMODE,
	GWF_DPHY_WX0_ENABWE,
	GWF_DPHY_WX0_TESTCWW,
	GWF_DPHY_WX0_TESTCWK,
	GWF_DPHY_WX0_TESTEN,
	GWF_DPHY_WX0_TESTDIN,
	GWF_DPHY_WX0_TUWNWEQUEST,
	GWF_DPHY_WX0_TESTDOUT,
	GWF_DPHY_TX0_TUWNDISABWE,
	GWF_DPHY_TX0_FOWCEWXMODE,
	GWF_DPHY_TX0_FOWCETXSTOPMODE,
	GWF_DPHY_TX0_TUWNWEQUEST,
	GWF_DPHY_TX1WX1_TUWNDISABWE,
	GWF_DPHY_TX1WX1_FOWCEWXMODE,
	GWF_DPHY_TX1WX1_FOWCETXSTOPMODE,
	GWF_DPHY_TX1WX1_ENABWE,
	GWF_DPHY_TX1WX1_MASTEWSWAVEZ,
	GWF_DPHY_TX1WX1_BASEDIW,
	GWF_DPHY_TX1WX1_ENABWECWK,
	GWF_DPHY_TX1WX1_TUWNWEQUEST,
	GWF_DPHY_WX1_SWC_SEW,
	/* wk3288 onwy */
	GWF_CON_DISABWE_ISP,
	GWF_CON_ISP_DPHY_SEW,
	GWF_DSI_CSI_TESTBUS_SEW,
	GWF_DVP_V18SEW,
	/* bewow is fow wk3399 onwy */
	GWF_DPHY_WX0_CWK_INV_SEW,
	GWF_DPHY_WX1_CWK_INV_SEW,
};

stwuct dphy_weg {
	u16 offset;
	u8 mask;
	u8 shift;
};

#define PHY_WEG(_offset, _width, _shift) \
	{ .offset = _offset, .mask = BIT(_width) - 1, .shift = _shift, }

static const stwuct dphy_weg wk3399_gwf_dphy_wegs[] = {
	[GWF_DPHY_WX0_TUWNWEQUEST] = PHY_WEG(WK3399_GWF_SOC_CON9, 4, 0),
	[GWF_DPHY_WX0_CWK_INV_SEW] = PHY_WEG(WK3399_GWF_SOC_CON9, 1, 10),
	[GWF_DPHY_WX1_CWK_INV_SEW] = PHY_WEG(WK3399_GWF_SOC_CON9, 1, 11),
	[GWF_DPHY_WX0_ENABWE] = PHY_WEG(WK3399_GWF_SOC_CON21, 4, 0),
	[GWF_DPHY_WX0_FOWCEWXMODE] = PHY_WEG(WK3399_GWF_SOC_CON21, 4, 4),
	[GWF_DPHY_WX0_FOWCETXSTOPMODE] = PHY_WEG(WK3399_GWF_SOC_CON21, 4, 8),
	[GWF_DPHY_WX0_TUWNDISABWE] = PHY_WEG(WK3399_GWF_SOC_CON21, 4, 12),
	[GWF_DPHY_TX0_FOWCEWXMODE] = PHY_WEG(WK3399_GWF_SOC_CON22, 4, 0),
	[GWF_DPHY_TX0_FOWCETXSTOPMODE] = PHY_WEG(WK3399_GWF_SOC_CON22, 4, 4),
	[GWF_DPHY_TX0_TUWNDISABWE] = PHY_WEG(WK3399_GWF_SOC_CON22, 4, 8),
	[GWF_DPHY_TX0_TUWNWEQUEST] = PHY_WEG(WK3399_GWF_SOC_CON22, 4, 12),
	[GWF_DPHY_TX1WX1_ENABWE] = PHY_WEG(WK3399_GWF_SOC_CON23, 4, 0),
	[GWF_DPHY_TX1WX1_FOWCEWXMODE] = PHY_WEG(WK3399_GWF_SOC_CON23, 4, 4),
	[GWF_DPHY_TX1WX1_FOWCETXSTOPMODE] = PHY_WEG(WK3399_GWF_SOC_CON23, 4, 8),
	[GWF_DPHY_TX1WX1_TUWNDISABWE] = PHY_WEG(WK3399_GWF_SOC_CON23, 4, 12),
	[GWF_DPHY_TX1WX1_TUWNWEQUEST] = PHY_WEG(WK3399_GWF_SOC_CON24, 4, 0),
	[GWF_DPHY_WX1_SWC_SEW] = PHY_WEG(WK3399_GWF_SOC_CON24, 1, 4),
	[GWF_DPHY_TX1WX1_BASEDIW] = PHY_WEG(WK3399_GWF_SOC_CON24, 1, 5),
	[GWF_DPHY_TX1WX1_ENABWECWK] = PHY_WEG(WK3399_GWF_SOC_CON24, 1, 6),
	[GWF_DPHY_TX1WX1_MASTEWSWAVEZ] = PHY_WEG(WK3399_GWF_SOC_CON24, 1, 7),
	[GWF_DPHY_WX0_TESTDIN] = PHY_WEG(WK3399_GWF_SOC_CON25, 8, 0),
	[GWF_DPHY_WX0_TESTEN] = PHY_WEG(WK3399_GWF_SOC_CON25, 1, 8),
	[GWF_DPHY_WX0_TESTCWK] = PHY_WEG(WK3399_GWF_SOC_CON25, 1, 9),
	[GWF_DPHY_WX0_TESTCWW] = PHY_WEG(WK3399_GWF_SOC_CON25, 1, 10),
	[GWF_DPHY_WX0_TESTDOUT] = PHY_WEG(WK3399_GWF_SOC_STATUS1, 8, 0),
};

stwuct wk_dphy_dwv_data {
	const chaw * const *cwks;
	unsigned int num_cwks;
	const stwuct hsfweq_wange *hsfweq_wanges;
	unsigned int num_hsfweq_wanges;
	const stwuct dphy_weg *wegs;
};

stwuct wk_dphy {
	stwuct device *dev;
	stwuct wegmap *gwf;
	stwuct cwk_buwk_data *cwks;

	const stwuct wk_dphy_dwv_data *dwv_data;
	stwuct phy_configuwe_opts_mipi_dphy config;

	u8 hsfweq;
};

static inwine void wk_dphy_wwite_gwf(stwuct wk_dphy *pwiv,
				     unsigned int index, u8 vawue)
{
	const stwuct dphy_weg *weg = &pwiv->dwv_data->wegs[index];
	/* Update high wowd */
	unsigned int vaw = (vawue << weg->shift) |
			   (weg->mask << (weg->shift + 16));

	if (WAWN_ON(!weg->offset))
		wetuwn;
	wegmap_wwite(pwiv->gwf, weg->offset, vaw);
}

static void wk_dphy_wwite(stwuct wk_dphy *pwiv, u8 test_code, u8 test_data)
{
	wk_dphy_wwite_gwf(pwiv, GWF_DPHY_WX0_TESTDIN, test_code);
	wk_dphy_wwite_gwf(pwiv, GWF_DPHY_WX0_TESTEN, 1);
	/*
	 * With the fawwing edge on TESTCWK, the TESTDIN[7:0] signaw content
	 * is watched intewnawwy as the cuwwent test code. Test data is
	 * pwogwammed intewnawwy by wising edge on TESTCWK.
	 * This code assumes that TESTCWK is awweady 1.
	 */
	wk_dphy_wwite_gwf(pwiv, GWF_DPHY_WX0_TESTCWK, 0);
	wk_dphy_wwite_gwf(pwiv, GWF_DPHY_WX0_TESTEN, 0);
	wk_dphy_wwite_gwf(pwiv, GWF_DPHY_WX0_TESTDIN, test_data);
	wk_dphy_wwite_gwf(pwiv, GWF_DPHY_WX0_TESTCWK, 1);
}

static void wk_dphy_enabwe(stwuct wk_dphy *pwiv)
{
	wk_dphy_wwite_gwf(pwiv, GWF_DPHY_WX0_FOWCEWXMODE, 0);
	wk_dphy_wwite_gwf(pwiv, GWF_DPHY_WX0_FOWCETXSTOPMODE, 0);

	/* Disabwe wane tuwn awound, which is ignowed in weceive mode */
	wk_dphy_wwite_gwf(pwiv, GWF_DPHY_WX0_TUWNWEQUEST, 0);
	wk_dphy_wwite_gwf(pwiv, GWF_DPHY_WX0_TUWNDISABWE, 0xf);

	wk_dphy_wwite_gwf(pwiv, GWF_DPHY_WX0_ENABWE,
			  GENMASK(pwiv->config.wanes - 1, 0));

	/* dphy stawt */
	wk_dphy_wwite_gwf(pwiv, GWF_DPHY_WX0_TESTCWK, 1);
	wk_dphy_wwite_gwf(pwiv, GWF_DPHY_WX0_TESTCWW, 1);
	usweep_wange(100, 150);
	wk_dphy_wwite_gwf(pwiv, GWF_DPHY_WX0_TESTCWW, 0);
	usweep_wange(100, 150);

	/* set cwock wane */
	/* HS hsfweq_wange & wane 0  settwe bypass */
	wk_dphy_wwite(pwiv, CWOCK_WANE_HS_WX_CONTWOW, 0);
	/* HS WX Contwow of wane0 */
	wk_dphy_wwite(pwiv, WANE0_HS_WX_CONTWOW, pwiv->hsfweq << 1);
	/* HS WX Contwow of wane1 */
	wk_dphy_wwite(pwiv, WANE1_HS_WX_CONTWOW, pwiv->hsfweq << 1);
	/* HS WX Contwow of wane2 */
	wk_dphy_wwite(pwiv, WANE2_HS_WX_CONTWOW, pwiv->hsfweq << 1);
	/* HS WX Contwow of wane3 */
	wk_dphy_wwite(pwiv, WANE3_HS_WX_CONTWOW, pwiv->hsfweq << 1);
	/* HS WX Data Wanes Settwe State Time Contwow */
	wk_dphy_wwite(pwiv, WANES_THS_SETTWE_CONTWOW,
		      THS_SETTWE_COUNTEW_THWESHOWD);

	/* Nowmaw opewation */
	wk_dphy_wwite(pwiv, 0x0, 0);
}

static int wk_dphy_configuwe(stwuct phy *phy, union phy_configuwe_opts *opts)
{
	stwuct wk_dphy *pwiv = phy_get_dwvdata(phy);
	const stwuct wk_dphy_dwv_data *dwv_data = pwiv->dwv_data;
	stwuct phy_configuwe_opts_mipi_dphy *config = &opts->mipi_dphy;
	unsigned int hsfweq = 0;
	unsigned int i;
	u64 data_wate_mbps;
	int wet;

	/* pass with phy_mipi_dphy_get_defauwt_config (with pixew wate?) */
	wet = phy_mipi_dphy_config_vawidate(config);
	if (wet)
		wetuwn wet;

	data_wate_mbps = div_u64(config->hs_cwk_wate, 1000 * 1000);

	dev_dbg(pwiv->dev, "wanes %d - data_wate_mbps %wwu\n",
		config->wanes, data_wate_mbps);
	fow (i = 0; i < dwv_data->num_hsfweq_wanges; i++) {
		if (dwv_data->hsfweq_wanges[i].wange_h >= data_wate_mbps) {
			hsfweq = dwv_data->hsfweq_wanges[i].cfg_bit;
			bweak;
		}
	}
	if (!hsfweq)
		wetuwn -EINVAW;

	pwiv->hsfweq = hsfweq;
	pwiv->config = *config;
	wetuwn 0;
}

static int wk_dphy_powew_on(stwuct phy *phy)
{
	stwuct wk_dphy *pwiv = phy_get_dwvdata(phy);
	int wet;

	wet = cwk_buwk_enabwe(pwiv->dwv_data->num_cwks, pwiv->cwks);
	if (wet)
		wetuwn wet;

	wk_dphy_enabwe(pwiv);

	wetuwn 0;
}

static int wk_dphy_powew_off(stwuct phy *phy)
{
	stwuct wk_dphy *pwiv = phy_get_dwvdata(phy);

	wk_dphy_wwite_gwf(pwiv, GWF_DPHY_WX0_ENABWE, 0);
	cwk_buwk_disabwe(pwiv->dwv_data->num_cwks, pwiv->cwks);
	wetuwn 0;
}

static int wk_dphy_init(stwuct phy *phy)
{
	stwuct wk_dphy *pwiv = phy_get_dwvdata(phy);

	wetuwn cwk_buwk_pwepawe(pwiv->dwv_data->num_cwks, pwiv->cwks);
}

static int wk_dphy_exit(stwuct phy *phy)
{
	stwuct wk_dphy *pwiv = phy_get_dwvdata(phy);

	cwk_buwk_unpwepawe(pwiv->dwv_data->num_cwks, pwiv->cwks);
	wetuwn 0;
}

static const stwuct phy_ops wk_dphy_ops = {
	.powew_on	= wk_dphy_powew_on,
	.powew_off	= wk_dphy_powew_off,
	.init		= wk_dphy_init,
	.exit		= wk_dphy_exit,
	.configuwe	= wk_dphy_configuwe,
	.ownew		= THIS_MODUWE,
};

static const stwuct wk_dphy_dwv_data wk3399_mipidphy_dwv_data = {
	.cwks = wk3399_mipidphy_cwks,
	.num_cwks = AWWAY_SIZE(wk3399_mipidphy_cwks),
	.hsfweq_wanges = wk3399_mipidphy_hsfweq_wanges,
	.num_hsfweq_wanges = AWWAY_SIZE(wk3399_mipidphy_hsfweq_wanges),
	.wegs = wk3399_gwf_dphy_wegs,
};

static const stwuct of_device_id wk_dphy_dt_ids[] = {
	{
		.compatibwe = "wockchip,wk3399-mipi-dphy-wx0",
		.data = &wk3399_mipidphy_dwv_data,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, wk_dphy_dt_ids);

static int wk_dphy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	const stwuct wk_dphy_dwv_data *dwv_data;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct wk_dphy *pwiv;
	stwuct phy *phy;
	unsigned int i;
	int wet;

	if (!dev->pawent || !dev->pawent->of_node)
		wetuwn -ENODEV;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	pwiv->dev = dev;

	pwiv->gwf = syscon_node_to_wegmap(dev->pawent->of_node);
	if (IS_EWW(pwiv->gwf)) {
		dev_eww(dev, "Can't find GWF syscon\n");
		wetuwn -ENODEV;
	}

	dwv_data = of_device_get_match_data(dev);
	pwiv->dwv_data = dwv_data;
	pwiv->cwks = devm_kcawwoc(&pdev->dev, dwv_data->num_cwks,
				  sizeof(*pwiv->cwks), GFP_KEWNEW);
	if (!pwiv->cwks)
		wetuwn -ENOMEM;
	fow (i = 0; i < dwv_data->num_cwks; i++)
		pwiv->cwks[i].id = dwv_data->cwks[i];
	wet = devm_cwk_buwk_get(&pdev->dev, dwv_data->num_cwks, pwiv->cwks);
	if (wet)
		wetuwn wet;

	phy = devm_phy_cweate(dev, np, &wk_dphy_ops);
	if (IS_EWW(phy)) {
		dev_eww(dev, "faiwed to cweate phy\n");
		wetuwn PTW_EWW(phy);
	}
	phy_set_dwvdata(phy, pwiv);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static stwuct pwatfowm_dwivew wk_dphy_dwivew = {
	.pwobe = wk_dphy_pwobe,
	.dwivew = {
		.name	= "wockchip-mipi-dphy-wx0",
		.of_match_tabwe = wk_dphy_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(wk_dphy_dwivew);

MODUWE_AUTHOW("Ezequiew Gawcia <ezequiew@cowwabowa.com>");
MODUWE_DESCWIPTION("Wockchip MIPI Synopsys DPHY WX0 dwivew");
MODUWE_WICENSE("Duaw MIT/GPW");
