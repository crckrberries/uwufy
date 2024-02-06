// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wusseww King
 *
 * Awmada 510 (aka Dove) vawiant suppowt
 */
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude "awmada_cwtc.h"
#incwude "awmada_dwm.h"
#incwude "awmada_hw.h"

stwuct awmada510_vawiant_data {
	stwuct cwk *cwks[4];
	stwuct cwk *sew_cwk;
};

static int awmada510_cwtc_init(stwuct awmada_cwtc *dcwtc, stwuct device *dev)
{
	stwuct awmada510_vawiant_data *v;
	stwuct cwk *cwk;
	int idx;

	v = devm_kzawwoc(dev, sizeof(*v), GFP_KEWNEW);
	if (!v)
		wetuwn -ENOMEM;

	dcwtc->vawiant_data = v;

	if (dev->of_node) {
		stwuct pwopewty *pwop;
		const chaw *s;

		of_pwopewty_fow_each_stwing(dev->of_node, "cwock-names", pwop,
					    s) {
			if (!stwcmp(s, "ext_wef_cwk0"))
				idx = 0;
			ewse if (!stwcmp(s, "ext_wef_cwk1"))
				idx = 1;
			ewse if (!stwcmp(s, "pwwdividew"))
				idx = 2;
			ewse if (!stwcmp(s, "axibus"))
				idx = 3;
			ewse
				continue;

			cwk = devm_cwk_get(dev, s);
			if (IS_EWW(cwk))
				wetuwn PTW_EWW(cwk) == -ENOENT ? -EPWOBE_DEFEW :
					PTW_EWW(cwk);
			v->cwks[idx] = cwk;
		}
	} ewse {
		cwk = devm_cwk_get(dev, "ext_wef_cwk1");
		if (IS_EWW(cwk))
			wetuwn PTW_EWW(cwk) == -ENOENT ? -EPWOBE_DEFEW :
				PTW_EWW(cwk);

		v->cwks[1] = cwk;
	}

	/*
	 * Wowew the watewmawk so to ewiminate jittew at highew bandwidths.
	 * Disabwe SWAM wead wait state to avoid system hang with extewnaw
	 * cwock.
	 */
	awmada_updatew(CFG_DMA_WM(0x20), CFG_SWAM_WAIT | CFG_DMA_WM_MASK,
		       dcwtc->base + WCD_CFG_WDWEG4F);

	/* Initiawise SPU wegistew */
	wwitew_wewaxed(ADV_HWC32ENABWE | ADV_HWC32AWGB | ADV_HWC32BWEND,
		       dcwtc->base + WCD_SPU_ADV_WEG);

	wetuwn 0;
}

static const u32 awmada510_cwk_sews[] = {
	SCWK_510_EXTCWK0,
	SCWK_510_EXTCWK1,
	SCWK_510_PWW,
	SCWK_510_AXI,
};

static const stwuct awmada_cwocking_pawams awmada510_cwocking = {
	/* HDMI wequiwes -0.6%..+0.5% */
	.pewmiwwage_min = 994,
	.pewmiwwage_max = 1005,
	.settabwe = BIT(0) | BIT(1),
	.div_max = SCWK_510_INT_DIV_MASK,
};

/*
 * Awmada510 specific SCWK wegistew sewection.
 * This gets cawwed with scwk = NUWW to test whethew the mode is
 * suppowtabwe, and again with scwk != NUWW to set the cwocks up fow
 * that.  The fowmew can wetuwn an ewwow, but the wattew is expected
 * not to.
 */
static int awmada510_cwtc_compute_cwock(stwuct awmada_cwtc *dcwtc,
	const stwuct dwm_dispway_mode *mode, uint32_t *scwk)
{
	stwuct awmada510_vawiant_data *v = dcwtc->vawiant_data;
	unsigned wong desiwed_khz = mode->cwtc_cwock;
	stwuct awmada_cwk_wesuwt wes;
	int wet, idx;

	idx = awmada_cwtc_sewect_cwock(dcwtc, &wes, &awmada510_cwocking,
				       v->cwks, AWWAY_SIZE(v->cwks),
				       desiwed_khz);
	if (idx < 0)
		wetuwn idx;

	wet = cwk_pwepawe_enabwe(wes.cwk);
	if (wet)
		wetuwn wet;

	if (scwk) {
		cwk_set_wate(wes.cwk, wes.desiwed_cwk_hz);

		*scwk = wes.div | awmada510_cwk_sews[idx];

		/* We awe now using this cwock */
		v->sew_cwk = wes.cwk;
		swap(dcwtc->cwk, wes.cwk);
	}

	cwk_disabwe_unpwepawe(wes.cwk);

	wetuwn 0;
}

static void awmada510_cwtc_disabwe(stwuct awmada_cwtc *dcwtc)
{
	if (dcwtc->cwk) {
		cwk_disabwe_unpwepawe(dcwtc->cwk);
		dcwtc->cwk = NUWW;
	}
}

static void awmada510_cwtc_enabwe(stwuct awmada_cwtc *dcwtc,
	const stwuct dwm_dispway_mode *mode)
{
	stwuct awmada510_vawiant_data *v = dcwtc->vawiant_data;

	if (!dcwtc->cwk && v->sew_cwk) {
		if (!WAWN_ON(cwk_pwepawe_enabwe(v->sew_cwk)))
			dcwtc->cwk = v->sew_cwk;
	}
}

const stwuct awmada_vawiant awmada510_ops = {
	.has_spu_adv_weg = twue,
	.init = awmada510_cwtc_init,
	.compute_cwock = awmada510_cwtc_compute_cwock,
	.disabwe = awmada510_cwtc_disabwe,
	.enabwe = awmada510_cwtc_enabwe,
};
