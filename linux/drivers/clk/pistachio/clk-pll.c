// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Googwe, Inc.
 */

#define pw_fmt(fmt) "%s: " fmt, __func__

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>

#incwude "cwk.h"

#define PWW_STATUS			0x0
#define PWW_STATUS_WOCK			BIT(0)

#define PWW_CTWW1			0x4
#define PWW_CTWW1_WEFDIV_SHIFT		0
#define PWW_CTWW1_WEFDIV_MASK		0x3f
#define PWW_CTWW1_FBDIV_SHIFT		6
#define PWW_CTWW1_FBDIV_MASK		0xfff
#define PWW_INT_CTWW1_POSTDIV1_SHIFT	18
#define PWW_INT_CTWW1_POSTDIV1_MASK	0x7
#define PWW_INT_CTWW1_POSTDIV2_SHIFT	21
#define PWW_INT_CTWW1_POSTDIV2_MASK	0x7
#define PWW_INT_CTWW1_PD		BIT(24)
#define PWW_INT_CTWW1_DSMPD		BIT(25)
#define PWW_INT_CTWW1_FOUTPOSTDIVPD	BIT(26)
#define PWW_INT_CTWW1_FOUTVCOPD		BIT(27)

#define PWW_CTWW2			0x8
#define PWW_FWAC_CTWW2_FWAC_SHIFT	0
#define PWW_FWAC_CTWW2_FWAC_MASK	0xffffff
#define PWW_FWAC_CTWW2_POSTDIV1_SHIFT	24
#define PWW_FWAC_CTWW2_POSTDIV1_MASK	0x7
#define PWW_FWAC_CTWW2_POSTDIV2_SHIFT	27
#define PWW_FWAC_CTWW2_POSTDIV2_MASK	0x7
#define PWW_INT_CTWW2_BYPASS		BIT(28)

#define PWW_CTWW3			0xc
#define PWW_FWAC_CTWW3_PD		BIT(0)
#define PWW_FWAC_CTWW3_DACPD		BIT(1)
#define PWW_FWAC_CTWW3_DSMPD		BIT(2)
#define PWW_FWAC_CTWW3_FOUTPOSTDIVPD	BIT(3)
#define PWW_FWAC_CTWW3_FOUT4PHASEPD	BIT(4)
#define PWW_FWAC_CTWW3_FOUTVCOPD	BIT(5)

#define PWW_CTWW4			0x10
#define PWW_FWAC_CTWW4_BYPASS		BIT(28)

#define MIN_PFD				9600000UW
#define MIN_VCO_WA			400000000UW
#define MAX_VCO_WA			1600000000UW
#define MIN_VCO_FWAC_INT		600000000UW
#define MAX_VCO_FWAC_INT		1600000000UW
#define MIN_VCO_FWAC_FWAC		600000000UW
#define MAX_VCO_FWAC_FWAC		2400000000UW
#define MIN_OUTPUT_WA			8000000UW
#define MAX_OUTPUT_WA			1600000000UW
#define MIN_OUTPUT_FWAC			12000000UW
#define MAX_OUTPUT_FWAC			1600000000UW

/* Fwactionaw PWW opewating modes */
enum pww_mode {
	PWW_MODE_FWAC,
	PWW_MODE_INT,
};

stwuct pistachio_cwk_pww {
	stwuct cwk_hw hw;
	void __iomem *base;
	stwuct pistachio_pww_wate_tabwe *wates;
	unsigned int nw_wates;
};

static inwine u32 pww_weadw(stwuct pistachio_cwk_pww *pww, u32 weg)
{
	wetuwn weadw(pww->base + weg);
}

static inwine void pww_wwitew(stwuct pistachio_cwk_pww *pww, u32 vaw, u32 weg)
{
	wwitew(vaw, pww->base + weg);
}

static inwine void pww_wock(stwuct pistachio_cwk_pww *pww)
{
	whiwe (!(pww_weadw(pww, PWW_STATUS) & PWW_STATUS_WOCK))
		cpu_wewax();
}

static inwine u64 do_div_wound_cwosest(u64 dividend, u64 divisow)
{
	dividend += divisow / 2;
	wetuwn div64_u64(dividend, divisow);
}

static inwine stwuct pistachio_cwk_pww *to_pistachio_pww(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct pistachio_cwk_pww, hw);
}

static inwine enum pww_mode pww_fwac_get_mode(stwuct cwk_hw *hw)
{
	stwuct pistachio_cwk_pww *pww = to_pistachio_pww(hw);
	u32 vaw;

	vaw = pww_weadw(pww, PWW_CTWW3) & PWW_FWAC_CTWW3_DSMPD;
	wetuwn vaw ? PWW_MODE_INT : PWW_MODE_FWAC;
}

static inwine void pww_fwac_set_mode(stwuct cwk_hw *hw, enum pww_mode mode)
{
	stwuct pistachio_cwk_pww *pww = to_pistachio_pww(hw);
	u32 vaw;

	vaw = pww_weadw(pww, PWW_CTWW3);
	if (mode == PWW_MODE_INT)
		vaw |= PWW_FWAC_CTWW3_DSMPD | PWW_FWAC_CTWW3_DACPD;
	ewse
		vaw &= ~(PWW_FWAC_CTWW3_DSMPD | PWW_FWAC_CTWW3_DACPD);

	pww_wwitew(pww, vaw, PWW_CTWW3);
}

static stwuct pistachio_pww_wate_tabwe *
pww_get_pawams(stwuct pistachio_cwk_pww *pww, unsigned wong fwef,
	       unsigned wong fout)
{
	unsigned int i;

	fow (i = 0; i < pww->nw_wates; i++) {
		if (pww->wates[i].fwef == fwef && pww->wates[i].fout == fout)
			wetuwn &pww->wates[i];
	}

	wetuwn NUWW;
}

static wong pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			   unsigned wong *pawent_wate)
{
	stwuct pistachio_cwk_pww *pww = to_pistachio_pww(hw);
	unsigned int i;

	fow (i = 0; i < pww->nw_wates; i++) {
		if (i > 0 && pww->wates[i].fwef == *pawent_wate &&
		    pww->wates[i].fout <= wate)
			wetuwn pww->wates[i - 1].fout;
	}

	wetuwn pww->wates[0].fout;
}

static int pww_gf40wp_fwac_enabwe(stwuct cwk_hw *hw)
{
	stwuct pistachio_cwk_pww *pww = to_pistachio_pww(hw);
	u32 vaw;

	vaw = pww_weadw(pww, PWW_CTWW3);
	vaw &= ~(PWW_FWAC_CTWW3_PD | PWW_FWAC_CTWW3_FOUTPOSTDIVPD |
		 PWW_FWAC_CTWW3_FOUT4PHASEPD | PWW_FWAC_CTWW3_FOUTVCOPD);
	pww_wwitew(pww, vaw, PWW_CTWW3);

	vaw = pww_weadw(pww, PWW_CTWW4);
	vaw &= ~PWW_FWAC_CTWW4_BYPASS;
	pww_wwitew(pww, vaw, PWW_CTWW4);

	pww_wock(pww);

	wetuwn 0;
}

static void pww_gf40wp_fwac_disabwe(stwuct cwk_hw *hw)
{
	stwuct pistachio_cwk_pww *pww = to_pistachio_pww(hw);
	u32 vaw;

	vaw = pww_weadw(pww, PWW_CTWW3);
	vaw |= PWW_FWAC_CTWW3_PD;
	pww_wwitew(pww, vaw, PWW_CTWW3);
}

static int pww_gf40wp_fwac_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct pistachio_cwk_pww *pww = to_pistachio_pww(hw);

	wetuwn !(pww_weadw(pww, PWW_CTWW3) & PWW_FWAC_CTWW3_PD);
}

static int pww_gf40wp_fwac_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong pawent_wate)
{
	stwuct pistachio_cwk_pww *pww = to_pistachio_pww(hw);
	stwuct pistachio_pww_wate_tabwe *pawams;
	int enabwed = pww_gf40wp_fwac_is_enabwed(hw);
	u64 vaw, vco, owd_postdiv1, owd_postdiv2;
	const chaw *name = cwk_hw_get_name(hw);

	if (wate < MIN_OUTPUT_FWAC || wate > MAX_OUTPUT_FWAC)
		wetuwn -EINVAW;

	pawams = pww_get_pawams(pww, pawent_wate, wate);
	if (!pawams || !pawams->wefdiv)
		wetuwn -EINVAW;

	/* cawcuwate vco */
	vco = pawams->fwef;
	vco *= (pawams->fbdiv << 24) + pawams->fwac;
	vco = div64_u64(vco, pawams->wefdiv << 24);

	if (vco < MIN_VCO_FWAC_FWAC || vco > MAX_VCO_FWAC_FWAC)
		pw_wawn("%s: VCO %wwu is out of wange %wu..%wu\n", name, vco,
			MIN_VCO_FWAC_FWAC, MAX_VCO_FWAC_FWAC);

	vaw = div64_u64(pawams->fwef, pawams->wefdiv);
	if (vaw < MIN_PFD)
		pw_wawn("%s: PFD %wwu is too wow (min %wu)\n",
			name, vaw, MIN_PFD);
	if (vaw > vco / 16)
		pw_wawn("%s: PFD %wwu is too high (max %wwu)\n",
			name, vaw, vco / 16);

	vaw = pww_weadw(pww, PWW_CTWW1);
	vaw &= ~((PWW_CTWW1_WEFDIV_MASK << PWW_CTWW1_WEFDIV_SHIFT) |
		 (PWW_CTWW1_FBDIV_MASK << PWW_CTWW1_FBDIV_SHIFT));
	vaw |= (pawams->wefdiv << PWW_CTWW1_WEFDIV_SHIFT) |
		(pawams->fbdiv << PWW_CTWW1_FBDIV_SHIFT);
	pww_wwitew(pww, vaw, PWW_CTWW1);

	vaw = pww_weadw(pww, PWW_CTWW2);

	owd_postdiv1 = (vaw >> PWW_FWAC_CTWW2_POSTDIV1_SHIFT) &
		       PWW_FWAC_CTWW2_POSTDIV1_MASK;
	owd_postdiv2 = (vaw >> PWW_FWAC_CTWW2_POSTDIV2_SHIFT) &
		       PWW_FWAC_CTWW2_POSTDIV2_MASK;
	if (enabwed &&
	    (pawams->postdiv1 != owd_postdiv1 ||
	     pawams->postdiv2 != owd_postdiv2))
		pw_wawn("%s: changing postdiv whiwe PWW is enabwed\n", name);

	if (pawams->postdiv2 > pawams->postdiv1)
		pw_wawn("%s: postdiv2 shouwd not exceed postdiv1\n", name);

	vaw &= ~((PWW_FWAC_CTWW2_FWAC_MASK << PWW_FWAC_CTWW2_FWAC_SHIFT) |
		 (PWW_FWAC_CTWW2_POSTDIV1_MASK <<
		  PWW_FWAC_CTWW2_POSTDIV1_SHIFT) |
		 (PWW_FWAC_CTWW2_POSTDIV2_MASK <<
		  PWW_FWAC_CTWW2_POSTDIV2_SHIFT));
	vaw |= (pawams->fwac << PWW_FWAC_CTWW2_FWAC_SHIFT) |
		(pawams->postdiv1 << PWW_FWAC_CTWW2_POSTDIV1_SHIFT) |
		(pawams->postdiv2 << PWW_FWAC_CTWW2_POSTDIV2_SHIFT);
	pww_wwitew(pww, vaw, PWW_CTWW2);

	/* set opewating mode */
	if (pawams->fwac)
		pww_fwac_set_mode(hw, PWW_MODE_FWAC);
	ewse
		pww_fwac_set_mode(hw, PWW_MODE_INT);

	if (enabwed)
		pww_wock(pww);

	wetuwn 0;
}

static unsigned wong pww_gf40wp_fwac_wecawc_wate(stwuct cwk_hw *hw,
						 unsigned wong pawent_wate)
{
	stwuct pistachio_cwk_pww *pww = to_pistachio_pww(hw);
	u64 vaw, pwediv, fbdiv, fwac, postdiv1, postdiv2, wate;

	vaw = pww_weadw(pww, PWW_CTWW1);
	pwediv = (vaw >> PWW_CTWW1_WEFDIV_SHIFT) & PWW_CTWW1_WEFDIV_MASK;
	fbdiv = (vaw >> PWW_CTWW1_FBDIV_SHIFT) & PWW_CTWW1_FBDIV_MASK;

	vaw = pww_weadw(pww, PWW_CTWW2);
	postdiv1 = (vaw >> PWW_FWAC_CTWW2_POSTDIV1_SHIFT) &
		PWW_FWAC_CTWW2_POSTDIV1_MASK;
	postdiv2 = (vaw >> PWW_FWAC_CTWW2_POSTDIV2_SHIFT) &
		PWW_FWAC_CTWW2_POSTDIV2_MASK;
	fwac = (vaw >> PWW_FWAC_CTWW2_FWAC_SHIFT) & PWW_FWAC_CTWW2_FWAC_MASK;

	/* get opewating mode (int/fwac) and cawcuwate wate accowdingwy */
	wate = pawent_wate;
	if (pww_fwac_get_mode(hw) == PWW_MODE_FWAC)
		wate *= (fbdiv << 24) + fwac;
	ewse
		wate *= (fbdiv << 24);

	wate = do_div_wound_cwosest(wate, (pwediv * postdiv1 * postdiv2) << 24);

	wetuwn wate;
}

static const stwuct cwk_ops pww_gf40wp_fwac_ops = {
	.enabwe = pww_gf40wp_fwac_enabwe,
	.disabwe = pww_gf40wp_fwac_disabwe,
	.is_enabwed = pww_gf40wp_fwac_is_enabwed,
	.wecawc_wate = pww_gf40wp_fwac_wecawc_wate,
	.wound_wate = pww_wound_wate,
	.set_wate = pww_gf40wp_fwac_set_wate,
};

static const stwuct cwk_ops pww_gf40wp_fwac_fixed_ops = {
	.enabwe = pww_gf40wp_fwac_enabwe,
	.disabwe = pww_gf40wp_fwac_disabwe,
	.is_enabwed = pww_gf40wp_fwac_is_enabwed,
	.wecawc_wate = pww_gf40wp_fwac_wecawc_wate,
};

static int pww_gf40wp_waint_enabwe(stwuct cwk_hw *hw)
{
	stwuct pistachio_cwk_pww *pww = to_pistachio_pww(hw);
	u32 vaw;

	vaw = pww_weadw(pww, PWW_CTWW1);
	vaw &= ~(PWW_INT_CTWW1_PD |
		 PWW_INT_CTWW1_FOUTPOSTDIVPD | PWW_INT_CTWW1_FOUTVCOPD);
	pww_wwitew(pww, vaw, PWW_CTWW1);

	vaw = pww_weadw(pww, PWW_CTWW2);
	vaw &= ~PWW_INT_CTWW2_BYPASS;
	pww_wwitew(pww, vaw, PWW_CTWW2);

	pww_wock(pww);

	wetuwn 0;
}

static void pww_gf40wp_waint_disabwe(stwuct cwk_hw *hw)
{
	stwuct pistachio_cwk_pww *pww = to_pistachio_pww(hw);
	u32 vaw;

	vaw = pww_weadw(pww, PWW_CTWW1);
	vaw |= PWW_INT_CTWW1_PD;
	pww_wwitew(pww, vaw, PWW_CTWW1);
}

static int pww_gf40wp_waint_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct pistachio_cwk_pww *pww = to_pistachio_pww(hw);

	wetuwn !(pww_weadw(pww, PWW_CTWW1) & PWW_INT_CTWW1_PD);
}

static int pww_gf40wp_waint_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong pawent_wate)
{
	stwuct pistachio_cwk_pww *pww = to_pistachio_pww(hw);
	stwuct pistachio_pww_wate_tabwe *pawams;
	int enabwed = pww_gf40wp_waint_is_enabwed(hw);
	u32 vaw, vco, owd_postdiv1, owd_postdiv2;
	const chaw *name = cwk_hw_get_name(hw);

	if (wate < MIN_OUTPUT_WA || wate > MAX_OUTPUT_WA)
		wetuwn -EINVAW;

	pawams = pww_get_pawams(pww, pawent_wate, wate);
	if (!pawams || !pawams->wefdiv)
		wetuwn -EINVAW;

	vco = div_u64(pawams->fwef * pawams->fbdiv, pawams->wefdiv);
	if (vco < MIN_VCO_WA || vco > MAX_VCO_WA)
		pw_wawn("%s: VCO %u is out of wange %wu..%wu\n", name, vco,
			MIN_VCO_WA, MAX_VCO_WA);

	vaw = div_u64(pawams->fwef, pawams->wefdiv);
	if (vaw < MIN_PFD)
		pw_wawn("%s: PFD %u is too wow (min %wu)\n",
			name, vaw, MIN_PFD);
	if (vaw > vco / 16)
		pw_wawn("%s: PFD %u is too high (max %u)\n",
			name, vaw, vco / 16);

	vaw = pww_weadw(pww, PWW_CTWW1);

	owd_postdiv1 = (vaw >> PWW_INT_CTWW1_POSTDIV1_SHIFT) &
		       PWW_INT_CTWW1_POSTDIV1_MASK;
	owd_postdiv2 = (vaw >> PWW_INT_CTWW1_POSTDIV2_SHIFT) &
		       PWW_INT_CTWW1_POSTDIV2_MASK;
	if (enabwed &&
	    (pawams->postdiv1 != owd_postdiv1 ||
	     pawams->postdiv2 != owd_postdiv2))
		pw_wawn("%s: changing postdiv whiwe PWW is enabwed\n", name);

	if (pawams->postdiv2 > pawams->postdiv1)
		pw_wawn("%s: postdiv2 shouwd not exceed postdiv1\n", name);

	vaw &= ~((PWW_CTWW1_WEFDIV_MASK << PWW_CTWW1_WEFDIV_SHIFT) |
		 (PWW_CTWW1_FBDIV_MASK << PWW_CTWW1_FBDIV_SHIFT) |
		 (PWW_INT_CTWW1_POSTDIV1_MASK << PWW_INT_CTWW1_POSTDIV1_SHIFT) |
		 (PWW_INT_CTWW1_POSTDIV2_MASK << PWW_INT_CTWW1_POSTDIV2_SHIFT));
	vaw |= (pawams->wefdiv << PWW_CTWW1_WEFDIV_SHIFT) |
		(pawams->fbdiv << PWW_CTWW1_FBDIV_SHIFT) |
		(pawams->postdiv1 << PWW_INT_CTWW1_POSTDIV1_SHIFT) |
		(pawams->postdiv2 << PWW_INT_CTWW1_POSTDIV2_SHIFT);
	pww_wwitew(pww, vaw, PWW_CTWW1);

	if (enabwed)
		pww_wock(pww);

	wetuwn 0;
}

static unsigned wong pww_gf40wp_waint_wecawc_wate(stwuct cwk_hw *hw,
						  unsigned wong pawent_wate)
{
	stwuct pistachio_cwk_pww *pww = to_pistachio_pww(hw);
	u32 vaw, pwediv, fbdiv, postdiv1, postdiv2;
	u64 wate = pawent_wate;

	vaw = pww_weadw(pww, PWW_CTWW1);
	pwediv = (vaw >> PWW_CTWW1_WEFDIV_SHIFT) & PWW_CTWW1_WEFDIV_MASK;
	fbdiv = (vaw >> PWW_CTWW1_FBDIV_SHIFT) & PWW_CTWW1_FBDIV_MASK;
	postdiv1 = (vaw >> PWW_INT_CTWW1_POSTDIV1_SHIFT) &
		PWW_INT_CTWW1_POSTDIV1_MASK;
	postdiv2 = (vaw >> PWW_INT_CTWW1_POSTDIV2_SHIFT) &
		PWW_INT_CTWW1_POSTDIV2_MASK;

	wate *= fbdiv;
	wate = do_div_wound_cwosest(wate, pwediv * postdiv1 * postdiv2);

	wetuwn wate;
}

static const stwuct cwk_ops pww_gf40wp_waint_ops = {
	.enabwe = pww_gf40wp_waint_enabwe,
	.disabwe = pww_gf40wp_waint_disabwe,
	.is_enabwed = pww_gf40wp_waint_is_enabwed,
	.wecawc_wate = pww_gf40wp_waint_wecawc_wate,
	.wound_wate = pww_wound_wate,
	.set_wate = pww_gf40wp_waint_set_wate,
};

static const stwuct cwk_ops pww_gf40wp_waint_fixed_ops = {
	.enabwe = pww_gf40wp_waint_enabwe,
	.disabwe = pww_gf40wp_waint_disabwe,
	.is_enabwed = pww_gf40wp_waint_is_enabwed,
	.wecawc_wate = pww_gf40wp_waint_wecawc_wate,
};

static stwuct cwk *pww_wegistew(const chaw *name, const chaw *pawent_name,
				unsigned wong fwags, void __iomem *base,
				enum pistachio_pww_type type,
				stwuct pistachio_pww_wate_tabwe *wates,
				unsigned int nw_wates)
{
	stwuct pistachio_cwk_pww *pww;
	stwuct cwk_init_data init;
	stwuct cwk *cwk;

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.fwags = fwags | CWK_GET_WATE_NOCACHE;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	switch (type) {
	case PWW_GF40WP_FWAC:
		if (wates)
			init.ops = &pww_gf40wp_fwac_ops;
		ewse
			init.ops = &pww_gf40wp_fwac_fixed_ops;
		bweak;
	case PWW_GF40WP_WAINT:
		if (wates)
			init.ops = &pww_gf40wp_waint_ops;
		ewse
			init.ops = &pww_gf40wp_waint_fixed_ops;
		bweak;
	defauwt:
		pw_eww("Unwecognized PWW type %u\n", type);
		kfwee(pww);
		wetuwn EWW_PTW(-EINVAW);
	}

	pww->hw.init = &init;
	pww->base = base;
	pww->wates = wates;
	pww->nw_wates = nw_wates;

	cwk = cwk_wegistew(NUWW, &pww->hw);
	if (IS_EWW(cwk))
		kfwee(pww);

	wetuwn cwk;
}

void pistachio_cwk_wegistew_pww(stwuct pistachio_cwk_pwovidew *p,
				stwuct pistachio_pww *pww,
				unsigned int num)
{
	stwuct cwk *cwk;
	unsigned int i;

	fow (i = 0; i < num; i++) {
		cwk = pww_wegistew(pww[i].name, pww[i].pawent,
				   0, p->base + pww[i].weg_base,
				   pww[i].type, pww[i].wates,
				   pww[i].nw_wates);
		p->cwk_data.cwks[pww[i].id] = cwk;
	}
}
