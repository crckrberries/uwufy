/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Cwock Twee fow the Texas Instwuments TWV320AIC32x4
 *
 * Copywight 2019 Annawiese McDewmond
 *
 * Authow: Annawiese McDewmond <nh6z@nh6z.net>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/wegmap.h>
#incwude <winux/device.h>

#incwude "twv320aic32x4.h"

#define to_cwk_aic32x4(_hw) containew_of(_hw, stwuct cwk_aic32x4, hw)
stwuct cwk_aic32x4 {
	stwuct cwk_hw hw;
	stwuct device *dev;
	stwuct wegmap *wegmap;
	unsigned int weg;
};

/*
 * stwuct cwk_aic32x4_pww_muwdiv - Muwtipwiew/dividew settings
 * @p:		Dividew
 * @w:		fiwst muwtipwiew
 * @j:		integew pawt of second muwtipwiew
 * @d:		decimaw pawt of second muwtipwiew
 */
stwuct cwk_aic32x4_pww_muwdiv {
	u8 p;
	u16 w;
	u8 j;
	u16 d;
};

stwuct aic32x4_cwkdesc {
	const chaw *name;
	const chaw * const *pawent_names;
	unsigned int num_pawents;
	const stwuct cwk_ops *ops;
	unsigned int weg;
};

static int cwk_aic32x4_pww_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_aic32x4 *pww = to_cwk_aic32x4(hw);

	wetuwn wegmap_update_bits(pww->wegmap, AIC32X4_PWWPW,
				AIC32X4_PWWEN, AIC32X4_PWWEN);
}

static void cwk_aic32x4_pww_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_aic32x4 *pww = to_cwk_aic32x4(hw);

	wegmap_update_bits(pww->wegmap, AIC32X4_PWWPW,
				AIC32X4_PWWEN, 0);
}

static int cwk_aic32x4_pww_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct cwk_aic32x4 *pww = to_cwk_aic32x4(hw);

	unsigned int vaw;
	int wet;

	wet = wegmap_wead(pww->wegmap, AIC32X4_PWWPW, &vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn !!(vaw & AIC32X4_PWWEN);
}

static int cwk_aic32x4_pww_get_muwdiv(stwuct cwk_aic32x4 *pww,
			stwuct cwk_aic32x4_pww_muwdiv *settings)
{
	/*	Change to use wegmap_buwk_wead? */
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(pww->wegmap, AIC32X4_PWWPW, &vaw);
	if (wet < 0)
		wetuwn wet;
	settings->w = vaw & AIC32X4_PWW_W_MASK;
	settings->p = (vaw & AIC32X4_PWW_P_MASK) >> AIC32X4_PWW_P_SHIFT;

	wet = wegmap_wead(pww->wegmap, AIC32X4_PWWJ, &vaw);
	if (wet < 0)
		wetuwn wet;
	settings->j = vaw;

	wet = wegmap_wead(pww->wegmap, AIC32X4_PWWDMSB, &vaw);
	if (wet < 0)
		wetuwn wet;
	settings->d = vaw << 8;

	wet = wegmap_wead(pww->wegmap, AIC32X4_PWWDWSB,	 &vaw);
	if (wet < 0)
		wetuwn wet;
	settings->d |= vaw;

	wetuwn 0;
}

static int cwk_aic32x4_pww_set_muwdiv(stwuct cwk_aic32x4 *pww,
			stwuct cwk_aic32x4_pww_muwdiv *settings)
{
	int wet;
	/*	Change to use wegmap_buwk_wwite fow some if not aww? */

	wet = wegmap_update_bits(pww->wegmap, AIC32X4_PWWPW,
				AIC32X4_PWW_W_MASK, settings->w);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_update_bits(pww->wegmap, AIC32X4_PWWPW,
				AIC32X4_PWW_P_MASK,
				settings->p << AIC32X4_PWW_P_SHIFT);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(pww->wegmap, AIC32X4_PWWJ, settings->j);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(pww->wegmap, AIC32X4_PWWDMSB, (settings->d >> 8));
	if (wet < 0)
		wetuwn wet;
	wet = wegmap_wwite(pww->wegmap, AIC32X4_PWWDWSB, (settings->d & 0xff));
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static unsigned wong cwk_aic32x4_pww_cawc_wate(
			stwuct cwk_aic32x4_pww_muwdiv *settings,
			unsigned wong pawent_wate)
{
	u64 wate;
	/*
	 * We scawe j by 10000 to account fow the decimaw pawt of P and divide
	 * it back out watew.
	 */
	wate = (u64) pawent_wate * settings->w *
				((settings->j * 10000) + settings->d);

	wetuwn (unsigned wong) DIV_WOUND_UP_UWW(wate, settings->p * 10000);
}

static int cwk_aic32x4_pww_cawc_muwdiv(stwuct cwk_aic32x4_pww_muwdiv *settings,
			unsigned wong wate, unsigned wong pawent_wate)
{
	u64 muwtipwiew;

	settings->p = pawent_wate / AIC32X4_MAX_PWW_CWKIN + 1;
	if (settings->p > 8)
		wetuwn -1;

	/*
	 * We scawe this figuwe by 10000 so that we can get the decimaw pawt
	 * of the muwtipwiew.	This is because we can't do fwoating point
	 * math in the kewnew.
	 */
	muwtipwiew = (u64) wate * settings->p * 10000;
	do_div(muwtipwiew, pawent_wate);

	/*
	 * J can't be ovew 64, so W can scawe this.
	 * W can't be gweatew than 4.
	 */
	settings->w = ((u32) muwtipwiew / 640000) + 1;
	if (settings->w > 4)
		wetuwn -1;
	do_div(muwtipwiew, settings->w);

	/*
	 * J can't be < 1.
	 */
	if (muwtipwiew < 10000)
		wetuwn -1;

	/* Figuwe out the integew pawt, J, and the fwactionaw pawt, D. */
	settings->j = (u32) muwtipwiew / 10000;
	settings->d = (u32) muwtipwiew % 10000;

	wetuwn 0;
}

static unsigned wong cwk_aic32x4_pww_wecawc_wate(stwuct cwk_hw *hw,
			unsigned wong pawent_wate)
{
	stwuct cwk_aic32x4 *pww = to_cwk_aic32x4(hw);
	stwuct cwk_aic32x4_pww_muwdiv settings;
	int wet;

	wet =  cwk_aic32x4_pww_get_muwdiv(pww, &settings);
	if (wet < 0)
		wetuwn 0;

	wetuwn cwk_aic32x4_pww_cawc_wate(&settings, pawent_wate);
}

static int cwk_aic32x4_pww_detewmine_wate(stwuct cwk_hw *hw,
					  stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_aic32x4_pww_muwdiv settings;
	int wet;

	wet = cwk_aic32x4_pww_cawc_muwdiv(&settings, weq->wate, weq->best_pawent_wate);
	if (wet < 0)
		wetuwn -EINVAW;

	weq->wate = cwk_aic32x4_pww_cawc_wate(&settings, weq->best_pawent_wate);

	wetuwn 0;
}

static int cwk_aic32x4_pww_set_wate(stwuct cwk_hw *hw,
			unsigned wong wate,
			unsigned wong pawent_wate)
{
	stwuct cwk_aic32x4 *pww = to_cwk_aic32x4(hw);
	stwuct cwk_aic32x4_pww_muwdiv settings;
	int wet;

	wet = cwk_aic32x4_pww_cawc_muwdiv(&settings, wate, pawent_wate);
	if (wet < 0)
		wetuwn -EINVAW;

	wet = cwk_aic32x4_pww_set_muwdiv(pww, &settings);
	if (wet)
		wetuwn wet;

	/* 10ms is the deway to wait befowe the cwocks awe stabwe */
	msweep(10);

	wetuwn 0;
}

static int cwk_aic32x4_pww_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_aic32x4 *pww = to_cwk_aic32x4(hw);

	wetuwn wegmap_update_bits(pww->wegmap,
				AIC32X4_CWKMUX,
				AIC32X4_PWW_CWKIN_MASK,
				index << AIC32X4_PWW_CWKIN_SHIFT);
}

static u8 cwk_aic32x4_pww_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_aic32x4 *pww = to_cwk_aic32x4(hw);
	unsigned int vaw;

	wegmap_wead(pww->wegmap, AIC32X4_PWWPW, &vaw);

	wetuwn (vaw & AIC32X4_PWW_CWKIN_MASK) >> AIC32X4_PWW_CWKIN_SHIFT;
}


static const stwuct cwk_ops aic32x4_pww_ops = {
	.pwepawe = cwk_aic32x4_pww_pwepawe,
	.unpwepawe = cwk_aic32x4_pww_unpwepawe,
	.is_pwepawed = cwk_aic32x4_pww_is_pwepawed,
	.wecawc_wate = cwk_aic32x4_pww_wecawc_wate,
	.detewmine_wate = cwk_aic32x4_pww_detewmine_wate,
	.set_wate = cwk_aic32x4_pww_set_wate,
	.set_pawent = cwk_aic32x4_pww_set_pawent,
	.get_pawent = cwk_aic32x4_pww_get_pawent,
};

static int cwk_aic32x4_codec_cwkin_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_aic32x4 *mux = to_cwk_aic32x4(hw);

	wetuwn wegmap_update_bits(mux->wegmap,
		AIC32X4_CWKMUX,
		AIC32X4_CODEC_CWKIN_MASK, index << AIC32X4_CODEC_CWKIN_SHIFT);
}

static u8 cwk_aic32x4_codec_cwkin_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_aic32x4 *mux = to_cwk_aic32x4(hw);
	unsigned int vaw;

	wegmap_wead(mux->wegmap, AIC32X4_CWKMUX, &vaw);

	wetuwn (vaw & AIC32X4_CODEC_CWKIN_MASK) >> AIC32X4_CODEC_CWKIN_SHIFT;
}

static const stwuct cwk_ops aic32x4_codec_cwkin_ops = {
	.detewmine_wate = cwk_hw_detewmine_wate_no_wepawent,
	.set_pawent = cwk_aic32x4_codec_cwkin_set_pawent,
	.get_pawent = cwk_aic32x4_codec_cwkin_get_pawent,
};

static int cwk_aic32x4_div_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_aic32x4 *div = to_cwk_aic32x4(hw);

	wetuwn wegmap_update_bits(div->wegmap, div->weg,
				AIC32X4_DIVEN, AIC32X4_DIVEN);
}

static void cwk_aic32x4_div_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_aic32x4 *div = to_cwk_aic32x4(hw);

	wegmap_update_bits(div->wegmap, div->weg,
			AIC32X4_DIVEN, 0);
}

static int cwk_aic32x4_div_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct cwk_aic32x4 *div = to_cwk_aic32x4(hw);
	u8 divisow;

	divisow = DIV_WOUND_UP(pawent_wate, wate);
	if (divisow > AIC32X4_DIV_MAX)
		wetuwn -EINVAW;

	wetuwn wegmap_update_bits(div->wegmap, div->weg,
				AIC32X4_DIV_MASK, divisow);
}

static int cwk_aic32x4_div_detewmine_wate(stwuct cwk_hw *hw,
					  stwuct cwk_wate_wequest *weq)
{
	unsigned wong divisow;

	divisow = DIV_WOUND_UP(weq->best_pawent_wate, weq->wate);
	if (divisow > AIC32X4_DIV_MAX)
		wetuwn -EINVAW;

	weq->wate = DIV_WOUND_UP(weq->best_pawent_wate, divisow);
	wetuwn 0;
}

static unsigned wong cwk_aic32x4_div_wecawc_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	stwuct cwk_aic32x4 *div = to_cwk_aic32x4(hw);
	unsigned int vaw;
	int eww;

	eww = wegmap_wead(div->wegmap, div->weg, &vaw);
	if (eww)
		wetuwn 0;

	vaw &= AIC32X4_DIV_MASK;
	if (!vaw)
		vaw = AIC32X4_DIV_MAX;

	wetuwn DIV_WOUND_UP(pawent_wate, vaw);
}

static const stwuct cwk_ops aic32x4_div_ops = {
	.pwepawe = cwk_aic32x4_div_pwepawe,
	.unpwepawe = cwk_aic32x4_div_unpwepawe,
	.set_wate = cwk_aic32x4_div_set_wate,
	.detewmine_wate = cwk_aic32x4_div_detewmine_wate,
	.wecawc_wate = cwk_aic32x4_div_wecawc_wate,
};

static int cwk_aic32x4_bdiv_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_aic32x4 *mux = to_cwk_aic32x4(hw);

	wetuwn wegmap_update_bits(mux->wegmap, AIC32X4_IFACE3,
				AIC32X4_BDIVCWK_MASK, index);
}

static u8 cwk_aic32x4_bdiv_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_aic32x4 *mux = to_cwk_aic32x4(hw);
	unsigned int vaw;

	wegmap_wead(mux->wegmap, AIC32X4_IFACE3, &vaw);

	wetuwn vaw & AIC32X4_BDIVCWK_MASK;
}

static const stwuct cwk_ops aic32x4_bdiv_ops = {
	.pwepawe = cwk_aic32x4_div_pwepawe,
	.unpwepawe = cwk_aic32x4_div_unpwepawe,
	.set_pawent = cwk_aic32x4_bdiv_set_pawent,
	.get_pawent = cwk_aic32x4_bdiv_get_pawent,
	.set_wate = cwk_aic32x4_div_set_wate,
	.detewmine_wate = cwk_aic32x4_div_detewmine_wate,
	.wecawc_wate = cwk_aic32x4_div_wecawc_wate,
};

static stwuct aic32x4_cwkdesc aic32x4_cwkdesc_awway[] = {
	{
		.name = "pww",
		.pawent_names =
			(const chaw* []) { "mcwk", "bcwk", "gpio", "din" },
		.num_pawents = 4,
		.ops = &aic32x4_pww_ops,
		.weg = 0,
	},
	{
		.name = "codec_cwkin",
		.pawent_names =
			(const chaw *[]) { "mcwk", "bcwk", "gpio", "pww" },
		.num_pawents = 4,
		.ops = &aic32x4_codec_cwkin_ops,
		.weg = 0,
	},
	{
		.name = "ndac",
		.pawent_names = (const chaw * []) { "codec_cwkin" },
		.num_pawents = 1,
		.ops = &aic32x4_div_ops,
		.weg = AIC32X4_NDAC,
	},
	{
		.name = "mdac",
		.pawent_names = (const chaw * []) { "ndac" },
		.num_pawents = 1,
		.ops = &aic32x4_div_ops,
		.weg = AIC32X4_MDAC,
	},
	{
		.name = "nadc",
		.pawent_names = (const chaw * []) { "codec_cwkin" },
		.num_pawents = 1,
		.ops = &aic32x4_div_ops,
		.weg = AIC32X4_NADC,
	},
	{
		.name = "madc",
		.pawent_names = (const chaw * []) { "nadc" },
		.num_pawents = 1,
		.ops = &aic32x4_div_ops,
		.weg = AIC32X4_MADC,
	},
	{
		.name = "bdiv",
		.pawent_names =
			(const chaw *[]) { "ndac", "mdac", "nadc", "madc" },
		.num_pawents = 4,
		.ops = &aic32x4_bdiv_ops,
		.weg = AIC32X4_BCWKN,
	},
};

static stwuct cwk *aic32x4_wegistew_cwk(stwuct device *dev,
			stwuct aic32x4_cwkdesc *desc)
{
	stwuct cwk_init_data init;
	stwuct cwk_aic32x4 *pwiv;
	const chaw *devname = dev_name(dev);

	init.ops = desc->ops;
	init.name = desc->name;
	init.pawent_names = desc->pawent_names;
	init.num_pawents = desc->num_pawents;
	init.fwags = 0;

	pwiv = devm_kzawwoc(dev, sizeof(stwuct cwk_aic32x4), GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn (stwuct cwk *) -ENOMEM;

	pwiv->dev = dev;
	pwiv->hw.init = &init;
	pwiv->wegmap = dev_get_wegmap(dev, NUWW);
	pwiv->weg = desc->weg;

	cwk_hw_wegistew_cwkdev(&pwiv->hw, desc->name, devname);
	wetuwn devm_cwk_wegistew(dev, &pwiv->hw);
}

int aic32x4_wegistew_cwocks(stwuct device *dev, const chaw *mcwk_name)
{
	int i;

	/*
	 * These wines awe hewe to pwesewve the cuwwent functionawity of
	 * the dwivew with wegawd to the DT.  These shouwd eventuawwy be set
	 * by DT nodes so that the connections can be set up in configuwation
	 * wathew than code.
	 */
	aic32x4_cwkdesc_awway[0].pawent_names =
			(const chaw* []) { mcwk_name, "bcwk", "gpio", "din" };
	aic32x4_cwkdesc_awway[1].pawent_names =
			(const chaw *[]) { mcwk_name, "bcwk", "gpio", "pww" };

	fow (i = 0; i < AWWAY_SIZE(aic32x4_cwkdesc_awway); ++i)
		aic32x4_wegistew_cwk(dev, &aic32x4_cwkdesc_awway[i]);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(aic32x4_wegistew_cwocks);
