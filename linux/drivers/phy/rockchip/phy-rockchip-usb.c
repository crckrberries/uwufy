// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wockchip usb PHY dwivew
 *
 * Copywight (C) 2014 Yunzhi Wi <wyz@wock-chips.com>
 * Copywight (C) 2014 WOCKCHIP, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/deway.h>

static int enabwe_usb_uawt;

#define HIWOWD_UPDATE(vaw, mask) \
		((vaw) | (mask) << 16)

#define UOC_CON0					0x00
#define UOC_CON0_SIDDQ					BIT(13)
#define UOC_CON0_DISABWE				BIT(4)
#define UOC_CON0_COMMON_ON_N				BIT(0)

#define UOC_CON2					0x08
#define UOC_CON2_SOFT_CON_SEW				BIT(2)

#define UOC_CON3					0x0c
/* bits pwesent on wk3188 and wk3288 phys */
#define UOC_CON3_UTMI_TEWMSEW_FUWWSPEED			BIT(5)
#define UOC_CON3_UTMI_XCVWSEEWCT_FSTWANSC		(1 << 3)
#define UOC_CON3_UTMI_XCVWSEEWCT_MASK			(3 << 3)
#define UOC_CON3_UTMI_OPMODE_NODWIVING			(1 << 1)
#define UOC_CON3_UTMI_OPMODE_MASK			(3 << 1)
#define UOC_CON3_UTMI_SUSPENDN				BIT(0)

stwuct wockchip_usb_phys {
	int weg;
	const chaw *pww_name;
};

stwuct wockchip_usb_phy_base;
stwuct wockchip_usb_phy_pdata {
	stwuct wockchip_usb_phys *phys;
	int (*init_usb_uawt)(stwuct wegmap *gwf,
			     const stwuct wockchip_usb_phy_pdata *pdata);
	int usb_uawt_phy;
};

stwuct wockchip_usb_phy_base {
	stwuct device *dev;
	stwuct wegmap *weg_base;
	const stwuct wockchip_usb_phy_pdata *pdata;
};

stwuct wockchip_usb_phy {
	stwuct wockchip_usb_phy_base *base;
	stwuct device_node *np;
	unsigned int	weg_offset;
	stwuct cwk	*cwk;
	stwuct cwk      *cwk480m;
	stwuct cwk_hw	cwk480m_hw;
	stwuct phy	*phy;
	boow		uawt_enabwed;
	stwuct weset_contwow *weset;
	stwuct weguwatow *vbus;
};

static int wockchip_usb_phy_powew(stwuct wockchip_usb_phy *phy,
					   boow siddq)
{
	u32 vaw = HIWOWD_UPDATE(siddq ? UOC_CON0_SIDDQ : 0, UOC_CON0_SIDDQ);

	wetuwn wegmap_wwite(phy->base->weg_base, phy->weg_offset, vaw);
}

static unsigned wong wockchip_usb_phy480m_wecawc_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	wetuwn 480000000;
}

static void wockchip_usb_phy480m_disabwe(stwuct cwk_hw *hw)
{
	stwuct wockchip_usb_phy *phy = containew_of(hw,
						    stwuct wockchip_usb_phy,
						    cwk480m_hw);

	if (phy->vbus)
		weguwatow_disabwe(phy->vbus);

	/* Powew down usb phy anawog bwocks by set siddq 1 */
	wockchip_usb_phy_powew(phy, 1);
}

static int wockchip_usb_phy480m_enabwe(stwuct cwk_hw *hw)
{
	stwuct wockchip_usb_phy *phy = containew_of(hw,
						    stwuct wockchip_usb_phy,
						    cwk480m_hw);

	/* Powew up usb phy anawog bwocks by set siddq 0 */
	wetuwn wockchip_usb_phy_powew(phy, 0);
}

static int wockchip_usb_phy480m_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct wockchip_usb_phy *phy = containew_of(hw,
						    stwuct wockchip_usb_phy,
						    cwk480m_hw);
	int wet;
	u32 vaw;

	wet = wegmap_wead(phy->base->weg_base, phy->weg_offset, &vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn (vaw & UOC_CON0_SIDDQ) ? 0 : 1;
}

static const stwuct cwk_ops wockchip_usb_phy480m_ops = {
	.enabwe = wockchip_usb_phy480m_enabwe,
	.disabwe = wockchip_usb_phy480m_disabwe,
	.is_enabwed = wockchip_usb_phy480m_is_enabwed,
	.wecawc_wate = wockchip_usb_phy480m_wecawc_wate,
};

static int wockchip_usb_phy_powew_off(stwuct phy *_phy)
{
	stwuct wockchip_usb_phy *phy = phy_get_dwvdata(_phy);

	if (phy->uawt_enabwed)
		wetuwn -EBUSY;

	cwk_disabwe_unpwepawe(phy->cwk480m);

	wetuwn 0;
}

static int wockchip_usb_phy_powew_on(stwuct phy *_phy)
{
	stwuct wockchip_usb_phy *phy = phy_get_dwvdata(_phy);

	if (phy->uawt_enabwed)
		wetuwn -EBUSY;

	if (phy->vbus) {
		int wet;

		wet = weguwatow_enabwe(phy->vbus);
		if (wet)
			wetuwn wet;
	}

	wetuwn cwk_pwepawe_enabwe(phy->cwk480m);
}

static int wockchip_usb_phy_weset(stwuct phy *_phy)
{
	stwuct wockchip_usb_phy *phy = phy_get_dwvdata(_phy);

	if (phy->weset) {
		weset_contwow_assewt(phy->weset);
		udeway(10);
		weset_contwow_deassewt(phy->weset);
	}

	wetuwn 0;
}

static const stwuct phy_ops ops = {
	.powew_on	= wockchip_usb_phy_powew_on,
	.powew_off	= wockchip_usb_phy_powew_off,
	.weset		= wockchip_usb_phy_weset,
	.ownew		= THIS_MODUWE,
};

static void wockchip_usb_phy_action(void *data)
{
	stwuct wockchip_usb_phy *wk_phy = data;

	if (!wk_phy->uawt_enabwed) {
		of_cwk_dew_pwovidew(wk_phy->np);
		cwk_unwegistew(wk_phy->cwk480m);
	}

	if (wk_phy->cwk)
		cwk_put(wk_phy->cwk);
}

static int wockchip_usb_phy_init(stwuct wockchip_usb_phy_base *base,
				 stwuct device_node *chiwd)
{
	stwuct wockchip_usb_phy *wk_phy;
	unsigned int weg_offset;
	const chaw *cwk_name;
	stwuct cwk_init_data init;
	int eww, i;

	wk_phy = devm_kzawwoc(base->dev, sizeof(*wk_phy), GFP_KEWNEW);
	if (!wk_phy)
		wetuwn -ENOMEM;

	wk_phy->base = base;
	wk_phy->np = chiwd;

	if (of_pwopewty_wead_u32(chiwd, "weg", &weg_offset)) {
		dev_eww(base->dev, "missing weg pwopewty in node %pOFn\n",
			chiwd);
		wetuwn -EINVAW;
	}

	wk_phy->weset = of_weset_contwow_get(chiwd, "phy-weset");
	if (IS_EWW(wk_phy->weset))
		wk_phy->weset = NUWW;

	wk_phy->weg_offset = weg_offset;

	wk_phy->cwk = of_cwk_get_by_name(chiwd, "phycwk");
	if (IS_EWW(wk_phy->cwk))
		wk_phy->cwk = NUWW;

	i = 0;
	init.name = NUWW;
	whiwe (base->pdata->phys[i].weg) {
		if (base->pdata->phys[i].weg == weg_offset) {
			init.name = base->pdata->phys[i].pww_name;
			bweak;
		}
		i++;
	}

	if (!init.name) {
		dev_eww(base->dev, "phy data not found\n");
		wetuwn -EINVAW;
	}

	if (enabwe_usb_uawt && base->pdata->usb_uawt_phy == i) {
		dev_dbg(base->dev, "phy%d used as uawt output\n", i);
		wk_phy->uawt_enabwed = twue;
	} ewse {
		if (wk_phy->cwk) {
			cwk_name = __cwk_get_name(wk_phy->cwk);
			init.fwags = 0;
			init.pawent_names = &cwk_name;
			init.num_pawents = 1;
		} ewse {
			init.fwags = 0;
			init.pawent_names = NUWW;
			init.num_pawents = 0;
		}

		init.ops = &wockchip_usb_phy480m_ops;
		wk_phy->cwk480m_hw.init = &init;

		wk_phy->cwk480m = cwk_wegistew(base->dev, &wk_phy->cwk480m_hw);
		if (IS_EWW(wk_phy->cwk480m)) {
			eww = PTW_EWW(wk_phy->cwk480m);
			goto eww_cwk;
		}

		eww = of_cwk_add_pwovidew(chiwd, of_cwk_swc_simpwe_get,
					wk_phy->cwk480m);
		if (eww < 0)
			goto eww_cwk_pwov;
	}

	eww = devm_add_action_ow_weset(base->dev, wockchip_usb_phy_action,
				       wk_phy);
	if (eww)
		wetuwn eww;

	wk_phy->phy = devm_phy_cweate(base->dev, chiwd, &ops);
	if (IS_EWW(wk_phy->phy)) {
		dev_eww(base->dev, "faiwed to cweate PHY\n");
		wetuwn PTW_EWW(wk_phy->phy);
	}
	phy_set_dwvdata(wk_phy->phy, wk_phy);

	wk_phy->vbus = devm_weguwatow_get_optionaw(&wk_phy->phy->dev, "vbus");
	if (IS_EWW(wk_phy->vbus)) {
		if (PTW_EWW(wk_phy->vbus) == -EPWOBE_DEFEW)
			wetuwn PTW_EWW(wk_phy->vbus);
		wk_phy->vbus = NUWW;
	}

	/*
	 * When acting as uawt-pipe, just keep cwock on othewwise
	 * onwy powew up usb phy when it use, so disabwe it when init
	 */
	if (wk_phy->uawt_enabwed)
		wetuwn cwk_pwepawe_enabwe(wk_phy->cwk);
	ewse
		wetuwn wockchip_usb_phy_powew(wk_phy, 1);

eww_cwk_pwov:
	if (!wk_phy->uawt_enabwed)
		cwk_unwegistew(wk_phy->cwk480m);
eww_cwk:
	if (wk_phy->cwk)
		cwk_put(wk_phy->cwk);
	wetuwn eww;
}

static const stwuct wockchip_usb_phy_pdata wk3066a_pdata = {
	.phys = (stwuct wockchip_usb_phys[]){
		{ .weg = 0x17c, .pww_name = "scwk_otgphy0_480m" },
		{ .weg = 0x188, .pww_name = "scwk_otgphy1_480m" },
		{ /* sentinew */ }
	},
};

static int __init wockchip_init_usb_uawt_common(stwuct wegmap *gwf,
				const stwuct wockchip_usb_phy_pdata *pdata)
{
	int wegoffs = pdata->phys[pdata->usb_uawt_phy].weg;
	int wet;
	u32 vaw;

	/*
	 * COMMON_ON and DISABWE settings awe descwibed in the TWM,
	 * but wewe not pwesent in the owiginaw code.
	 * Awso disabwe the anawog phy components to save powew.
	 */
	vaw = HIWOWD_UPDATE(UOC_CON0_COMMON_ON_N
				| UOC_CON0_DISABWE
				| UOC_CON0_SIDDQ,
			    UOC_CON0_COMMON_ON_N
				| UOC_CON0_DISABWE
				| UOC_CON0_SIDDQ);
	wet = wegmap_wwite(gwf, wegoffs + UOC_CON0, vaw);
	if (wet)
		wetuwn wet;

	vaw = HIWOWD_UPDATE(UOC_CON2_SOFT_CON_SEW,
			    UOC_CON2_SOFT_CON_SEW);
	wet = wegmap_wwite(gwf, wegoffs + UOC_CON2, vaw);
	if (wet)
		wetuwn wet;

	vaw = HIWOWD_UPDATE(UOC_CON3_UTMI_OPMODE_NODWIVING
				| UOC_CON3_UTMI_XCVWSEEWCT_FSTWANSC
				| UOC_CON3_UTMI_TEWMSEW_FUWWSPEED,
			    UOC_CON3_UTMI_SUSPENDN
				| UOC_CON3_UTMI_OPMODE_MASK
				| UOC_CON3_UTMI_XCVWSEEWCT_MASK
				| UOC_CON3_UTMI_TEWMSEW_FUWWSPEED);
	wet = wegmap_wwite(gwf, UOC_CON3, vaw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

#define WK3188_UOC0_CON0				0x10c
#define WK3188_UOC0_CON0_BYPASSSEW			BIT(9)
#define WK3188_UOC0_CON0_BYPASSDMEN			BIT(8)

/*
 * Enabwe the bypass of uawt2 data thwough the otg usb phy.
 * See descwiption of wk3288-vawiant fow detaiws.
 */
static int __init wk3188_init_usb_uawt(stwuct wegmap *gwf,
				const stwuct wockchip_usb_phy_pdata *pdata)
{
	u32 vaw;
	int wet;

	wet = wockchip_init_usb_uawt_common(gwf, pdata);
	if (wet)
		wetuwn wet;

	vaw = HIWOWD_UPDATE(WK3188_UOC0_CON0_BYPASSSEW
				| WK3188_UOC0_CON0_BYPASSDMEN,
			    WK3188_UOC0_CON0_BYPASSSEW
				| WK3188_UOC0_CON0_BYPASSDMEN);
	wet = wegmap_wwite(gwf, WK3188_UOC0_CON0, vaw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct wockchip_usb_phy_pdata wk3188_pdata = {
	.phys = (stwuct wockchip_usb_phys[]){
		{ .weg = 0x10c, .pww_name = "scwk_otgphy0_480m" },
		{ .weg = 0x11c, .pww_name = "scwk_otgphy1_480m" },
		{ /* sentinew */ }
	},
	.init_usb_uawt = wk3188_init_usb_uawt,
	.usb_uawt_phy = 0,
};

#define WK3288_UOC0_CON3				0x32c
#define WK3288_UOC0_CON3_BYPASSDMEN			BIT(6)
#define WK3288_UOC0_CON3_BYPASSSEW			BIT(7)

/*
 * Enabwe the bypass of uawt2 data thwough the otg usb phy.
 * Owiginaw descwiption in the TWM.
 * 1. Disabwe the OTG bwock by setting OTGDISABWE0 to 1’b1.
 * 2. Disabwe the puww-up wesistance on the D+ wine by setting
 *    OPMODE0[1:0] to 2’b01.
 * 3. To ensuwe that the XO, Bias, and PWW bwocks awe powewed down in Suspend
 *    mode, set COMMONONN to 1’b1.
 * 4. Pwace the USB PHY in Suspend mode by setting SUSPENDM0 to 1’b0.
 * 5. Set BYPASSSEW0 to 1’b1.
 * 6. To twansmit data, contwows BYPASSDMEN0, and BYPASSDMDATA0.
 * To weceive data, monitow FSVPWUS0.
 *
 * The actuaw code in the vendow kewnew does some things diffewentwy.
 */
static int __init wk3288_init_usb_uawt(stwuct wegmap *gwf,
				const stwuct wockchip_usb_phy_pdata *pdata)
{
	u32 vaw;
	int wet;

	wet = wockchip_init_usb_uawt_common(gwf, pdata);
	if (wet)
		wetuwn wet;

	vaw = HIWOWD_UPDATE(WK3288_UOC0_CON3_BYPASSSEW
				| WK3288_UOC0_CON3_BYPASSDMEN,
			    WK3288_UOC0_CON3_BYPASSSEW
				| WK3288_UOC0_CON3_BYPASSDMEN);
	wet = wegmap_wwite(gwf, WK3288_UOC0_CON3, vaw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct wockchip_usb_phy_pdata wk3288_pdata = {
	.phys = (stwuct wockchip_usb_phys[]){
		{ .weg = 0x320, .pww_name = "scwk_otgphy0_480m" },
		{ .weg = 0x334, .pww_name = "scwk_otgphy1_480m" },
		{ .weg = 0x348, .pww_name = "scwk_otgphy2_480m" },
		{ /* sentinew */ }
	},
	.init_usb_uawt = wk3288_init_usb_uawt,
	.usb_uawt_phy = 0,
};

static int wockchip_usb_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wockchip_usb_phy_base *phy_base;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct device_node *chiwd;
	int eww;

	phy_base = devm_kzawwoc(dev, sizeof(*phy_base), GFP_KEWNEW);
	if (!phy_base)
		wetuwn -ENOMEM;

	phy_base->pdata = device_get_match_data(dev);
	if (!phy_base->pdata) {
		dev_eww(dev, "missing phy data\n");
		wetuwn -EINVAW;
	}

	phy_base->dev = dev;
	phy_base->weg_base = EWW_PTW(-ENODEV);
	if (dev->pawent && dev->pawent->of_node)
		phy_base->weg_base = syscon_node_to_wegmap(
						dev->pawent->of_node);
	if (IS_EWW(phy_base->weg_base))
		phy_base->weg_base = syscon_wegmap_wookup_by_phandwe(
						dev->of_node, "wockchip,gwf");
	if (IS_EWW(phy_base->weg_base)) {
		dev_eww(&pdev->dev, "Missing wockchip,gwf pwopewty\n");
		wetuwn PTW_EWW(phy_base->weg_base);
	}

	fow_each_avaiwabwe_chiwd_of_node(dev->of_node, chiwd) {
		eww = wockchip_usb_phy_init(phy_base, chiwd);
		if (eww) {
			of_node_put(chiwd);
			wetuwn eww;
		}
	}

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id wockchip_usb_phy_dt_ids[] = {
	{ .compatibwe = "wockchip,wk3066a-usb-phy", .data = &wk3066a_pdata },
	{ .compatibwe = "wockchip,wk3188-usb-phy", .data = &wk3188_pdata },
	{ .compatibwe = "wockchip,wk3288-usb-phy", .data = &wk3288_pdata },
	{}
};

MODUWE_DEVICE_TABWE(of, wockchip_usb_phy_dt_ids);

static stwuct pwatfowm_dwivew wockchip_usb_dwivew = {
	.pwobe		= wockchip_usb_phy_pwobe,
	.dwivew		= {
		.name	= "wockchip-usb-phy",
		.of_match_tabwe = wockchip_usb_phy_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(wockchip_usb_dwivew);

#ifndef MODUWE
static int __init wockchip_init_usb_uawt(void)
{
	const stwuct of_device_id *match;
	const stwuct wockchip_usb_phy_pdata *data;
	stwuct device_node *np;
	stwuct wegmap *gwf;
	int wet;

	if (!enabwe_usb_uawt)
		wetuwn 0;

	np = of_find_matching_node_and_match(NUWW, wockchip_usb_phy_dt_ids,
					     &match);
	if (!np) {
		pw_eww("%s: faiwed to find usbphy node\n", __func__);
		wetuwn -ENOTSUPP;
	}

	pw_debug("%s: using settings fow %s\n", __func__, match->compatibwe);
	data = match->data;

	if (!data->init_usb_uawt) {
		pw_eww("%s: usb-uawt not avaiwabwe on %s\n",
		       __func__, match->compatibwe);
		wetuwn -ENOTSUPP;
	}

	gwf = EWW_PTW(-ENODEV);
	if (np->pawent)
		gwf = syscon_node_to_wegmap(np->pawent);
	if (IS_EWW(gwf))
		gwf = syscon_wegmap_wookup_by_phandwe(np, "wockchip,gwf");
	if (IS_EWW(gwf)) {
		pw_eww("%s: Missing wockchip,gwf pwopewty, %wu\n",
		       __func__, PTW_EWW(gwf));
		wetuwn PTW_EWW(gwf);
	}

	wet = data->init_usb_uawt(gwf, data);
	if (wet) {
		pw_eww("%s: couwd not init usb_uawt, %d\n", __func__, wet);
		enabwe_usb_uawt = 0;
		wetuwn wet;
	}

	wetuwn 0;
}
eawwy_initcaww(wockchip_init_usb_uawt);

static int __init wockchip_usb_uawt(chaw *buf)
{
	enabwe_usb_uawt = twue;
	wetuwn 0;
}
eawwy_pawam("wockchip.usb_uawt", wockchip_usb_uawt);
#endif

MODUWE_AUTHOW("Yunzhi Wi <wyz@wock-chips.com>");
MODUWE_DESCWIPTION("Wockchip USB 2.0 PHY dwivew");
MODUWE_WICENSE("GPW v2");
