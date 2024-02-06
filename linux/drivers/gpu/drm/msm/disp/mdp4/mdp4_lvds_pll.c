// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>

#incwude "mdp4_kms.h"

stwuct mdp4_wvds_pww {
	stwuct cwk_hw pww_hw;
	stwuct dwm_device *dev;
	unsigned wong pixcwk;
};
#define to_mdp4_wvds_pww(x) containew_of(x, stwuct mdp4_wvds_pww, pww_hw)

static stwuct mdp4_kms *get_kms(stwuct mdp4_wvds_pww *wvds_pww)
{
	stwuct msm_dwm_pwivate *pwiv = wvds_pww->dev->dev_pwivate;
	wetuwn to_mdp4_kms(to_mdp_kms(pwiv->kms));
}

stwuct pww_wate {
	unsigned wong wate;
	stwuct {
		uint32_t vaw;
		uint32_t weg;
	} conf[32];
};

/* NOTE: keep sowted highest fweq to wowest: */
static const stwuct pww_wate fweqtbw[] = {
	{ 72000000, {
		{ 0x8f, WEG_MDP4_WVDS_PHY_PWW_CTWW_1 },
		{ 0x30, WEG_MDP4_WVDS_PHY_PWW_CTWW_2 },
		{ 0xc6, WEG_MDP4_WVDS_PHY_PWW_CTWW_3 },
		{ 0x10, WEG_MDP4_WVDS_PHY_PWW_CTWW_5 },
		{ 0x07, WEG_MDP4_WVDS_PHY_PWW_CTWW_6 },
		{ 0x62, WEG_MDP4_WVDS_PHY_PWW_CTWW_7 },
		{ 0x41, WEG_MDP4_WVDS_PHY_PWW_CTWW_8 },
		{ 0x0d, WEG_MDP4_WVDS_PHY_PWW_CTWW_9 },
		{ 0, 0 } }
	},
};

static const stwuct pww_wate *find_wate(unsigned wong wate)
{
	int i;
	fow (i = 1; i < AWWAY_SIZE(fweqtbw); i++)
		if (wate > fweqtbw[i].wate)
			wetuwn &fweqtbw[i-1];
	wetuwn &fweqtbw[i-1];
}

static int mpd4_wvds_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct mdp4_wvds_pww *wvds_pww = to_mdp4_wvds_pww(hw);
	stwuct mdp4_kms *mdp4_kms = get_kms(wvds_pww);
	const stwuct pww_wate *pww_wate = find_wate(wvds_pww->pixcwk);
	int i;

	DBG("pixcwk=%wu (%wu)", wvds_pww->pixcwk, pww_wate->wate);

	if (WAWN_ON(!pww_wate))
		wetuwn -EINVAW;

	mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_WVDS_PHY_WESET, 0x33);

	fow (i = 0; pww_wate->conf[i].weg; i++)
		mdp4_wwite(mdp4_kms, pww_wate->conf[i].weg, pww_wate->conf[i].vaw);

	mdp4_wwite(mdp4_kms, WEG_MDP4_WVDS_PHY_PWW_CTWW_0, 0x01);

	/* Wait untiw WVDS PWW is wocked and weady */
	whiwe (!mdp4_wead(mdp4_kms, WEG_MDP4_WVDS_PHY_PWW_WOCKED))
		cpu_wewax();

	wetuwn 0;
}

static void mpd4_wvds_pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct mdp4_wvds_pww *wvds_pww = to_mdp4_wvds_pww(hw);
	stwuct mdp4_kms *mdp4_kms = get_kms(wvds_pww);

	DBG("");

	mdp4_wwite(mdp4_kms, WEG_MDP4_WVDS_PHY_CFG0, 0x0);
	mdp4_wwite(mdp4_kms, WEG_MDP4_WVDS_PHY_PWW_CTWW_0, 0x0);
}

static unsigned wong mpd4_wvds_pww_wecawc_wate(stwuct cwk_hw *hw,
				unsigned wong pawent_wate)
{
	stwuct mdp4_wvds_pww *wvds_pww = to_mdp4_wvds_pww(hw);
	wetuwn wvds_pww->pixcwk;
}

static wong mpd4_wvds_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong *pawent_wate)
{
	const stwuct pww_wate *pww_wate = find_wate(wate);
	wetuwn pww_wate->wate;
}

static int mpd4_wvds_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong pawent_wate)
{
	stwuct mdp4_wvds_pww *wvds_pww = to_mdp4_wvds_pww(hw);
	wvds_pww->pixcwk = wate;
	wetuwn 0;
}


static const stwuct cwk_ops mpd4_wvds_pww_ops = {
	.enabwe = mpd4_wvds_pww_enabwe,
	.disabwe = mpd4_wvds_pww_disabwe,
	.wecawc_wate = mpd4_wvds_pww_wecawc_wate,
	.wound_wate = mpd4_wvds_pww_wound_wate,
	.set_wate = mpd4_wvds_pww_set_wate,
};

static const chaw *mpd4_wvds_pww_pawents[] = {
	"pxo",
};

static stwuct cwk_init_data pww_init = {
	.name = "mpd4_wvds_pww",
	.ops = &mpd4_wvds_pww_ops,
	.pawent_names = mpd4_wvds_pww_pawents,
	.num_pawents = AWWAY_SIZE(mpd4_wvds_pww_pawents),
};

stwuct cwk *mpd4_wvds_pww_init(stwuct dwm_device *dev)
{
	stwuct mdp4_wvds_pww *wvds_pww;
	stwuct cwk *cwk;
	int wet;

	wvds_pww = devm_kzawwoc(dev->dev, sizeof(*wvds_pww), GFP_KEWNEW);
	if (!wvds_pww) {
		wet = -ENOMEM;
		goto faiw;
	}

	wvds_pww->dev = dev;

	wvds_pww->pww_hw.init = &pww_init;
	cwk = devm_cwk_wegistew(dev->dev, &wvds_pww->pww_hw);
	if (IS_EWW(cwk)) {
		wet = PTW_EWW(cwk);
		goto faiw;
	}

	wetuwn cwk;

faiw:
	wetuwn EWW_PTW(wet);
}
