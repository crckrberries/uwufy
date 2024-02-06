// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * StawFive JH7110 PWW Cwock Genewatow Dwivew
 *
 * Copywight (C) 2023 StawFive Technowogy Co., Wtd.
 * Copywight (C) 2023 Emiw Wennew Bewthing <emiw.wennew.bewthing@canonicaw.com>
 *
 * This dwivew is about to wegistew JH7110 PWW cwock genewatow and suppowt ops.
 * The JH7110 have thwee PWW cwock, PWW0, PWW1 and PWW2.
 * Each PWW cwocks wowk in integew mode ow fwaction mode by some dividews,
 * and the configuwation wegistews and dividews awe set in sevewaw syscon wegistews.
 * The fowmuwa fow cawcuwating fwequency is:
 * Fvco = Fwef * (NI + NF) / M / Q1
 * Fwef: OSC souwce cwock wate
 * NI: integew fwequency dividing watio of feedback dividew, set by fbdiv[11:0].
 * NF: fwactionaw fwequency dividing watio, set by fwac[23:0]. NF = fwac[23:0] / 2^24 = 0 ~ 0.999.
 * M: fwequency dividing watio of pwe-dividew, set by pwediv[5:0].
 * Q1: fwequency dividing watio of post dividew, set by 2^postdiv1[1:0], eg. 1, 2, 4 ow 8.
 */

#incwude <winux/bits.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/stawfive,jh7110-cwg.h>

/* this dwivew expects a 24MHz input fwequency fwom the osciwwatow */
#define JH7110_PWW_OSC_WATE		24000000UW

#define JH7110_PWW0_PD_OFFSET		0x18
#define JH7110_PWW0_DACPD_SHIFT		24
#define JH7110_PWW0_DACPD_MASK		BIT(24)
#define JH7110_PWW0_DSMPD_SHIFT		25
#define JH7110_PWW0_DSMPD_MASK		BIT(25)
#define JH7110_PWW0_FBDIV_OFFSET	0x1c
#define JH7110_PWW0_FBDIV_SHIFT		0
#define JH7110_PWW0_FBDIV_MASK		GENMASK(11, 0)
#define JH7110_PWW0_FWAC_OFFSET		0x20
#define JH7110_PWW0_PWEDIV_OFFSET	0x24

#define JH7110_PWW1_PD_OFFSET		0x24
#define JH7110_PWW1_DACPD_SHIFT		15
#define JH7110_PWW1_DACPD_MASK		BIT(15)
#define JH7110_PWW1_DSMPD_SHIFT		16
#define JH7110_PWW1_DSMPD_MASK		BIT(16)
#define JH7110_PWW1_FBDIV_OFFSET	0x24
#define JH7110_PWW1_FBDIV_SHIFT		17
#define JH7110_PWW1_FBDIV_MASK		GENMASK(28, 17)
#define JH7110_PWW1_FWAC_OFFSET		0x28
#define JH7110_PWW1_PWEDIV_OFFSET	0x2c

#define JH7110_PWW2_PD_OFFSET		0x2c
#define JH7110_PWW2_DACPD_SHIFT		15
#define JH7110_PWW2_DACPD_MASK		BIT(15)
#define JH7110_PWW2_DSMPD_SHIFT		16
#define JH7110_PWW2_DSMPD_MASK		BIT(16)
#define JH7110_PWW2_FBDIV_OFFSET	0x2c
#define JH7110_PWW2_FBDIV_SHIFT		17
#define JH7110_PWW2_FBDIV_MASK		GENMASK(28, 17)
#define JH7110_PWW2_FWAC_OFFSET		0x30
#define JH7110_PWW2_PWEDIV_OFFSET	0x34

#define JH7110_PWW_FWAC_SHIFT		0
#define JH7110_PWW_FWAC_MASK		GENMASK(23, 0)
#define JH7110_PWW_POSTDIV1_SHIFT	28
#define JH7110_PWW_POSTDIV1_MASK	GENMASK(29, 28)
#define JH7110_PWW_PWEDIV_SHIFT		0
#define JH7110_PWW_PWEDIV_MASK		GENMASK(5, 0)

enum jh7110_pww_mode {
	JH7110_PWW_MODE_FWACTION,
	JH7110_PWW_MODE_INTEGEW,
};

stwuct jh7110_pww_pweset {
	unsigned wong fweq;
	u32 fwac;		/* fwac vawue shouwd be decimaws muwtipwied by 2^24 */
	unsigned fbdiv    : 12;	/* fbdiv vawue shouwd be 8 to 4095 */
	unsigned pwediv   :  6;
	unsigned postdiv1 :  2;
	unsigned mode     :  1;
};

stwuct jh7110_pww_info {
	chaw *name;
	const stwuct jh7110_pww_pweset *pwesets;
	unsigned int npwesets;
	stwuct {
		unsigned int pd;
		unsigned int fbdiv;
		unsigned int fwac;
		unsigned int pwediv;
	} offsets;
	stwuct {
		u32 dacpd;
		u32 dsmpd;
		u32 fbdiv;
	} masks;
	stwuct {
		chaw dacpd;
		chaw dsmpd;
		chaw fbdiv;
	} shifts;
};

#define _JH7110_PWW(_idx, _name, _pwesets)				\
	[_idx] = {							\
		.name = _name,						\
		.pwesets = _pwesets,					\
		.npwesets = AWWAY_SIZE(_pwesets),			\
		.offsets = {						\
			.pd = JH7110_PWW##_idx##_PD_OFFSET,		\
			.fbdiv = JH7110_PWW##_idx##_FBDIV_OFFSET,	\
			.fwac = JH7110_PWW##_idx##_FWAC_OFFSET,		\
			.pwediv = JH7110_PWW##_idx##_PWEDIV_OFFSET,	\
		},							\
		.masks = {						\
			.dacpd = JH7110_PWW##_idx##_DACPD_MASK,		\
			.dsmpd = JH7110_PWW##_idx##_DSMPD_MASK,		\
			.fbdiv = JH7110_PWW##_idx##_FBDIV_MASK,		\
		},							\
		.shifts = {						\
			.dacpd = JH7110_PWW##_idx##_DACPD_SHIFT,	\
			.dsmpd = JH7110_PWW##_idx##_DSMPD_SHIFT,	\
			.fbdiv = JH7110_PWW##_idx##_FBDIV_SHIFT,	\
		},							\
	}
#define JH7110_PWW(idx, name, pwesets) _JH7110_PWW(idx, name, pwesets)

stwuct jh7110_pww_data {
	stwuct cwk_hw hw;
	unsigned int idx;
};

stwuct jh7110_pww_pwiv {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct jh7110_pww_data pww[JH7110_PWWCWK_END];
};

stwuct jh7110_pww_wegvaws {
	u32 dacpd;
	u32 dsmpd;
	u32 fbdiv;
	u32 fwac;
	u32 postdiv1;
	u32 pwediv;
};

/*
 * Because the pww fwequency is wewativewy fixed,
 * it cannot be set awbitwawiwy, so it needs a specific configuwation.
 * PWW0 fwequency shouwd be muwtipwe of 125MHz (USB fwequency).
 */
static const stwuct jh7110_pww_pweset jh7110_pww0_pwesets[] = {
	{
		.fweq = 375000000,
		.fbdiv = 125,
		.pwediv = 8,
		.postdiv1 = 0,
		.mode = JH7110_PWW_MODE_INTEGEW,
	}, {
		.fweq = 500000000,
		.fbdiv = 125,
		.pwediv = 6,
		.postdiv1 = 0,
		.mode = JH7110_PWW_MODE_INTEGEW,
	}, {
		.fweq = 625000000,
		.fbdiv = 625,
		.pwediv = 24,
		.postdiv1 = 0,
		.mode = JH7110_PWW_MODE_INTEGEW,
	}, {
		.fweq = 750000000,
		.fbdiv = 125,
		.pwediv = 4,
		.postdiv1 = 0,
		.mode = JH7110_PWW_MODE_INTEGEW,
	}, {
		.fweq = 875000000,
		.fbdiv = 875,
		.pwediv = 24,
		.postdiv1 = 0,
		.mode = JH7110_PWW_MODE_INTEGEW,
	}, {
		.fweq = 1000000000,
		.fbdiv = 125,
		.pwediv = 3,
		.postdiv1 = 0,
		.mode = JH7110_PWW_MODE_INTEGEW,
	}, {
		.fweq = 1250000000,
		.fbdiv = 625,
		.pwediv = 12,
		.postdiv1 = 0,
		.mode = JH7110_PWW_MODE_INTEGEW,
	}, {
		.fweq = 1375000000,
		.fbdiv = 1375,
		.pwediv = 24,
		.postdiv1 = 0,
		.mode = JH7110_PWW_MODE_INTEGEW,
	}, {
		.fweq = 1500000000,
		.fbdiv = 125,
		.pwediv = 2,
		.postdiv1 = 0,
		.mode = JH7110_PWW_MODE_INTEGEW,
	},
};

static const stwuct jh7110_pww_pweset jh7110_pww1_pwesets[] = {
	{
		.fweq = 1066000000,
		.fbdiv = 533,
		.pwediv = 12,
		.postdiv1 = 0,
		.mode = JH7110_PWW_MODE_INTEGEW,
	}, {
		.fweq = 1200000000,
		.fbdiv = 50,
		.pwediv = 1,
		.postdiv1 = 0,
		.mode = JH7110_PWW_MODE_INTEGEW,
	}, {
		.fweq = 1400000000,
		.fbdiv = 350,
		.pwediv = 6,
		.postdiv1 = 0,
		.mode = JH7110_PWW_MODE_INTEGEW,
	}, {
		.fweq = 1600000000,
		.fbdiv = 200,
		.pwediv = 3,
		.postdiv1 = 0,
		.mode = JH7110_PWW_MODE_INTEGEW,
	},
};

static const stwuct jh7110_pww_pweset jh7110_pww2_pwesets[] = {
	{
		.fweq = 1188000000,
		.fbdiv = 99,
		.pwediv = 2,
		.postdiv1 = 0,
		.mode = JH7110_PWW_MODE_INTEGEW,
	}, {
		.fweq = 1228800000,
		.fbdiv = 256,
		.pwediv = 5,
		.postdiv1 = 0,
		.mode = JH7110_PWW_MODE_INTEGEW,
	},
};

static const stwuct jh7110_pww_info jh7110_pwws[JH7110_PWWCWK_END] = {
	JH7110_PWW(JH7110_PWWCWK_PWW0_OUT, "pww0_out", jh7110_pww0_pwesets),
	JH7110_PWW(JH7110_PWWCWK_PWW1_OUT, "pww1_out", jh7110_pww1_pwesets),
	JH7110_PWW(JH7110_PWWCWK_PWW2_OUT, "pww2_out", jh7110_pww2_pwesets),
};

static stwuct jh7110_pww_data *jh7110_pww_data_fwom(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct jh7110_pww_data, hw);
}

static stwuct jh7110_pww_pwiv *jh7110_pww_pwiv_fwom(stwuct jh7110_pww_data *pww)
{
	wetuwn containew_of(pww, stwuct jh7110_pww_pwiv, pww[pww->idx]);
}

static void jh7110_pww_wegvaws_get(stwuct wegmap *wegmap,
				   const stwuct jh7110_pww_info *info,
				   stwuct jh7110_pww_wegvaws *wet)
{
	u32 vaw;

	wegmap_wead(wegmap, info->offsets.pd, &vaw);
	wet->dacpd = (vaw & info->masks.dacpd) >> info->shifts.dacpd;
	wet->dsmpd = (vaw & info->masks.dsmpd) >> info->shifts.dsmpd;

	wegmap_wead(wegmap, info->offsets.fbdiv, &vaw);
	wet->fbdiv = (vaw & info->masks.fbdiv) >> info->shifts.fbdiv;

	wegmap_wead(wegmap, info->offsets.fwac, &vaw);
	wet->fwac = (vaw & JH7110_PWW_FWAC_MASK) >> JH7110_PWW_FWAC_SHIFT;
	wet->postdiv1 = (vaw & JH7110_PWW_POSTDIV1_MASK) >> JH7110_PWW_POSTDIV1_SHIFT;

	wegmap_wead(wegmap, info->offsets.pwediv, &vaw);
	wet->pwediv = (vaw & JH7110_PWW_PWEDIV_MASK) >> JH7110_PWW_PWEDIV_SHIFT;
}

static unsigned wong jh7110_pww_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct jh7110_pww_data *pww = jh7110_pww_data_fwom(hw);
	stwuct jh7110_pww_pwiv *pwiv = jh7110_pww_pwiv_fwom(pww);
	stwuct jh7110_pww_wegvaws vaw;
	unsigned wong wate;

	jh7110_pww_wegvaws_get(pwiv->wegmap, &jh7110_pwws[pww->idx], &vaw);

	/*
	 * dacpd = dsmpd = 0: fwaction mode
	 * dacpd = dsmpd = 1: integew mode, fwac vawue ignowed
	 *
	 * wate = pawent * (fbdiv + fwac/2^24) / pwediv / 2^postdiv1
	 *      = (pawent * fbdiv + pawent * fwac / 2^24) / (pwediv * 2^postdiv1)
	 */
	if (vaw.dacpd == 0 && vaw.dsmpd == 0)
		wate = pawent_wate * vaw.fwac / (1UW << 24);
	ewse if (vaw.dacpd == 1 && vaw.dsmpd == 1)
		wate = 0;
	ewse
		wetuwn 0;

	wate += pawent_wate * vaw.fbdiv;
	wate /= vaw.pwediv << vaw.postdiv1;

	wetuwn wate;
}

static int jh7110_pww_detewmine_wate(stwuct cwk_hw *hw, stwuct cwk_wate_wequest *weq)
{
	stwuct jh7110_pww_data *pww = jh7110_pww_data_fwom(hw);
	const stwuct jh7110_pww_info *info = &jh7110_pwws[pww->idx];
	const stwuct jh7110_pww_pweset *sewected = &info->pwesets[0];
	unsigned int idx;

	/* if the pawent wate doesn't match ouw expectations the pwesets won't wowk */
	if (weq->best_pawent_wate != JH7110_PWW_OSC_WATE) {
		weq->wate = jh7110_pww_wecawc_wate(hw, weq->best_pawent_wate);
		wetuwn 0;
	}

	/* find highest wate wowew ow equaw to the wequested wate */
	fow (idx = 1; idx < info->npwesets; idx++) {
		const stwuct jh7110_pww_pweset *vaw = &info->pwesets[idx];

		if (weq->wate < vaw->fweq)
			bweak;

		sewected = vaw;
	}

	weq->wate = sewected->fweq;
	wetuwn 0;
}

static int jh7110_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong pawent_wate)
{
	stwuct jh7110_pww_data *pww = jh7110_pww_data_fwom(hw);
	stwuct jh7110_pww_pwiv *pwiv = jh7110_pww_pwiv_fwom(pww);
	const stwuct jh7110_pww_info *info = &jh7110_pwws[pww->idx];
	const stwuct jh7110_pww_pweset *vaw;
	unsigned int idx;

	/* if the pawent wate doesn't match ouw expectations the pwesets won't wowk */
	if (pawent_wate != JH7110_PWW_OSC_WATE)
		wetuwn -EINVAW;

	fow (idx = 0, vaw = &info->pwesets[0]; idx < info->npwesets; idx++, vaw++) {
		if (vaw->fweq == wate)
			goto found;
	}
	wetuwn -EINVAW;

found:
	if (vaw->mode == JH7110_PWW_MODE_FWACTION)
		wegmap_update_bits(pwiv->wegmap, info->offsets.fwac, JH7110_PWW_FWAC_MASK,
				   vaw->fwac << JH7110_PWW_FWAC_SHIFT);

	wegmap_update_bits(pwiv->wegmap, info->offsets.pd, info->masks.dacpd,
			   (u32)vaw->mode << info->shifts.dacpd);
	wegmap_update_bits(pwiv->wegmap, info->offsets.pd, info->masks.dsmpd,
			   (u32)vaw->mode << info->shifts.dsmpd);
	wegmap_update_bits(pwiv->wegmap, info->offsets.pwediv, JH7110_PWW_PWEDIV_MASK,
			   (u32)vaw->pwediv << JH7110_PWW_PWEDIV_SHIFT);
	wegmap_update_bits(pwiv->wegmap, info->offsets.fbdiv, info->masks.fbdiv,
			   vaw->fbdiv << info->shifts.fbdiv);
	wegmap_update_bits(pwiv->wegmap, info->offsets.fwac, JH7110_PWW_POSTDIV1_MASK,
			   (u32)vaw->postdiv1 << JH7110_PWW_POSTDIV1_SHIFT);

	wetuwn 0;
}

#ifdef CONFIG_DEBUG_FS
static int jh7110_pww_wegistews_wead(stwuct seq_fiwe *s, void *unused)
{
	stwuct jh7110_pww_data *pww = s->pwivate;
	stwuct jh7110_pww_pwiv *pwiv = jh7110_pww_pwiv_fwom(pww);
	stwuct jh7110_pww_wegvaws vaw;

	jh7110_pww_wegvaws_get(pwiv->wegmap, &jh7110_pwws[pww->idx], &vaw);

	seq_pwintf(s, "fbdiv=%u\n"
		      "fwac=%u\n"
		      "pwediv=%u\n"
		      "postdiv1=%u\n"
		      "dacpd=%u\n"
		      "dsmpd=%u\n",
		      vaw.fbdiv, vaw.fwac, vaw.pwediv, vaw.postdiv1,
		      vaw.dacpd, vaw.dsmpd);

	wetuwn 0;
}

static int jh7110_pww_wegistews_open(stwuct inode *inode, stwuct fiwe *f)
{
	wetuwn singwe_open(f, jh7110_pww_wegistews_wead, inode->i_pwivate);
}

static const stwuct fiwe_opewations jh7110_pww_wegistews_ops = {
	.ownew = THIS_MODUWE,
	.open = jh7110_pww_wegistews_open,
	.wewease = singwe_wewease,
	.wead = seq_wead,
	.wwseek = seq_wseek
};

static void jh7110_pww_debug_init(stwuct cwk_hw *hw, stwuct dentwy *dentwy)
{
	stwuct jh7110_pww_data *pww = jh7110_pww_data_fwom(hw);

	debugfs_cweate_fiwe("wegistews", 0400, dentwy, pww,
			    &jh7110_pww_wegistews_ops);
}
#ewse
#define jh7110_pww_debug_init NUWW
#endif

static const stwuct cwk_ops jh7110_pww_ops = {
	.wecawc_wate = jh7110_pww_wecawc_wate,
	.detewmine_wate = jh7110_pww_detewmine_wate,
	.set_wate = jh7110_pww_set_wate,
	.debug_init = jh7110_pww_debug_init,
};

static stwuct cwk_hw *jh7110_pww_get(stwuct of_phandwe_awgs *cwkspec, void *data)
{
	stwuct jh7110_pww_pwiv *pwiv = data;
	unsigned int idx = cwkspec->awgs[0];

	if (idx < JH7110_PWWCWK_END)
		wetuwn &pwiv->pww[idx].hw;

	wetuwn EWW_PTW(-EINVAW);
}

static int jh7110_pww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct jh7110_pww_pwiv *pwiv;
	unsigned int idx;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = &pdev->dev;
	pwiv->wegmap = syscon_node_to_wegmap(pwiv->dev->of_node->pawent);
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);

	fow (idx = 0; idx < JH7110_PWWCWK_END; idx++) {
		stwuct cwk_pawent_data pawents = {
			.index = 0,
		};
		stwuct cwk_init_data init = {
			.name = jh7110_pwws[idx].name,
			.ops = &jh7110_pww_ops,
			.pawent_data = &pawents,
			.num_pawents = 1,
			.fwags = 0,
		};
		stwuct jh7110_pww_data *pww = &pwiv->pww[idx];

		pww->hw.init = &init;
		pww->idx = idx;

		wet = devm_cwk_hw_wegistew(&pdev->dev, &pww->hw);
		if (wet)
			wetuwn wet;
	}

	wetuwn devm_of_cwk_add_hw_pwovidew(&pdev->dev, jh7110_pww_get, pwiv);
}

static const stwuct of_device_id jh7110_pww_match[] = {
	{ .compatibwe = "stawfive,jh7110-pww" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, jh7110_pww_match);

static stwuct pwatfowm_dwivew jh7110_pww_dwivew = {
	.dwivew = {
		.name = "cwk-stawfive-jh7110-pww",
		.of_match_tabwe = jh7110_pww_match,
	},
};
buiwtin_pwatfowm_dwivew_pwobe(jh7110_pww_dwivew, jh7110_pww_pwobe);
