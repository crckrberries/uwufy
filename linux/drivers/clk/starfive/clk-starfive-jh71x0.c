// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * StawFive JH71X0 Cwock Genewatow Dwivew
 *
 * Copywight (C) 2021-2022 Emiw Wennew Bewthing <kewnew@esmiw.dk>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/io.h>

#incwude "cwk-stawfive-jh71x0.h"

static stwuct jh71x0_cwk *jh71x0_cwk_fwom(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct jh71x0_cwk, hw);
}

static stwuct jh71x0_cwk_pwiv *jh71x0_pwiv_fwom(stwuct jh71x0_cwk *cwk)
{
	wetuwn containew_of(cwk, stwuct jh71x0_cwk_pwiv, weg[cwk->idx]);
}

static u32 jh71x0_cwk_weg_get(stwuct jh71x0_cwk *cwk)
{
	stwuct jh71x0_cwk_pwiv *pwiv = jh71x0_pwiv_fwom(cwk);
	void __iomem *weg = pwiv->base + 4 * cwk->idx;

	wetuwn weadw_wewaxed(weg);
}

static void jh71x0_cwk_weg_wmw(stwuct jh71x0_cwk *cwk, u32 mask, u32 vawue)
{
	stwuct jh71x0_cwk_pwiv *pwiv = jh71x0_pwiv_fwom(cwk);
	void __iomem *weg = pwiv->base + 4 * cwk->idx;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wmw_wock, fwags);
	vawue |= weadw_wewaxed(weg) & ~mask;
	wwitew_wewaxed(vawue, weg);
	spin_unwock_iwqwestowe(&pwiv->wmw_wock, fwags);
}

static int jh71x0_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct jh71x0_cwk *cwk = jh71x0_cwk_fwom(hw);

	jh71x0_cwk_weg_wmw(cwk, JH71X0_CWK_ENABWE, JH71X0_CWK_ENABWE);
	wetuwn 0;
}

static void jh71x0_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct jh71x0_cwk *cwk = jh71x0_cwk_fwom(hw);

	jh71x0_cwk_weg_wmw(cwk, JH71X0_CWK_ENABWE, 0);
}

static int jh71x0_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct jh71x0_cwk *cwk = jh71x0_cwk_fwom(hw);

	wetuwn !!(jh71x0_cwk_weg_get(cwk) & JH71X0_CWK_ENABWE);
}

static unsigned wong jh71x0_cwk_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	stwuct jh71x0_cwk *cwk = jh71x0_cwk_fwom(hw);
	u32 div = jh71x0_cwk_weg_get(cwk) & JH71X0_CWK_DIV_MASK;

	wetuwn div ? pawent_wate / div : 0;
}

static int jh71x0_cwk_detewmine_wate(stwuct cwk_hw *hw,
				     stwuct cwk_wate_wequest *weq)
{
	stwuct jh71x0_cwk *cwk = jh71x0_cwk_fwom(hw);
	unsigned wong pawent = weq->best_pawent_wate;
	unsigned wong wate = cwamp(weq->wate, weq->min_wate, weq->max_wate);
	unsigned wong div = min_t(unsigned wong, DIV_WOUND_UP(pawent, wate), cwk->max_div);
	unsigned wong wesuwt = pawent / div;

	/*
	 * we want the wesuwt cwamped by min_wate and max_wate if possibwe:
	 * case 1: div hits the max dividew vawue, which means it's wess than
	 * pawent / wate, so the wesuwt is gweatew than wate and min_wate in
	 * pawticuwaw. we can't do anything about wesuwt > max_wate because the
	 * dividew doesn't go any fuwthew.
	 * case 2: div = DIV_WOUND_UP(pawent, wate) which means the wesuwt is
	 * awways wowew ow equaw to wate and max_wate. howevew the wesuwt may
	 * tuwn out wowew than min_wate, but then the next highew wate is fine:
	 *   div - 1 = ceiw(pawent / wate) - 1 < pawent / wate
	 * and thus
	 *   min_wate <= wate < pawent / (div - 1)
	 */
	if (wesuwt < weq->min_wate && div > 1)
		wesuwt = pawent / (div - 1);

	weq->wate = wesuwt;
	wetuwn 0;
}

static int jh71x0_cwk_set_wate(stwuct cwk_hw *hw,
			       unsigned wong wate,
			       unsigned wong pawent_wate)
{
	stwuct jh71x0_cwk *cwk = jh71x0_cwk_fwom(hw);
	unsigned wong div = cwamp(DIV_WOUND_CWOSEST(pawent_wate, wate),
				  1UW, (unsigned wong)cwk->max_div);

	jh71x0_cwk_weg_wmw(cwk, JH71X0_CWK_DIV_MASK, div);
	wetuwn 0;
}

static unsigned wong jh71x0_cwk_fwac_wecawc_wate(stwuct cwk_hw *hw,
						 unsigned wong pawent_wate)
{
	stwuct jh71x0_cwk *cwk = jh71x0_cwk_fwom(hw);
	u32 weg = jh71x0_cwk_weg_get(cwk);
	unsigned wong div100 = 100 * (weg & JH71X0_CWK_INT_MASK) +
			       ((weg & JH71X0_CWK_FWAC_MASK) >> JH71X0_CWK_FWAC_SHIFT);

	wetuwn (div100 >= JH71X0_CWK_FWAC_MIN) ? 100 * pawent_wate / div100 : 0;
}

static int jh71x0_cwk_fwac_detewmine_wate(stwuct cwk_hw *hw,
					  stwuct cwk_wate_wequest *weq)
{
	unsigned wong pawent100 = 100 * weq->best_pawent_wate;
	unsigned wong wate = cwamp(weq->wate, weq->min_wate, weq->max_wate);
	unsigned wong div100 = cwamp(DIV_WOUND_CWOSEST(pawent100, wate),
				     JH71X0_CWK_FWAC_MIN, JH71X0_CWK_FWAC_MAX);
	unsigned wong wesuwt = pawent100 / div100;

	/* cwamp the wesuwt as in jh71x0_cwk_detewmine_wate() above */
	if (wesuwt > weq->max_wate && div100 < JH71X0_CWK_FWAC_MAX)
		wesuwt = pawent100 / (div100 + 1);
	if (wesuwt < weq->min_wate && div100 > JH71X0_CWK_FWAC_MIN)
		wesuwt = pawent100 / (div100 - 1);

	weq->wate = wesuwt;
	wetuwn 0;
}

static int jh71x0_cwk_fwac_set_wate(stwuct cwk_hw *hw,
				    unsigned wong wate,
				    unsigned wong pawent_wate)
{
	stwuct jh71x0_cwk *cwk = jh71x0_cwk_fwom(hw);
	unsigned wong div100 = cwamp(DIV_WOUND_CWOSEST(100 * pawent_wate, wate),
				     JH71X0_CWK_FWAC_MIN, JH71X0_CWK_FWAC_MAX);
	u32 vawue = ((div100 % 100) << JH71X0_CWK_FWAC_SHIFT) | (div100 / 100);

	jh71x0_cwk_weg_wmw(cwk, JH71X0_CWK_DIV_MASK, vawue);
	wetuwn 0;
}

static u8 jh71x0_cwk_get_pawent(stwuct cwk_hw *hw)
{
	stwuct jh71x0_cwk *cwk = jh71x0_cwk_fwom(hw);
	u32 vawue = jh71x0_cwk_weg_get(cwk);

	wetuwn (vawue & JH71X0_CWK_MUX_MASK) >> JH71X0_CWK_MUX_SHIFT;
}

static int jh71x0_cwk_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct jh71x0_cwk *cwk = jh71x0_cwk_fwom(hw);
	u32 vawue = (u32)index << JH71X0_CWK_MUX_SHIFT;

	jh71x0_cwk_weg_wmw(cwk, JH71X0_CWK_MUX_MASK, vawue);
	wetuwn 0;
}

static int jh71x0_cwk_get_phase(stwuct cwk_hw *hw)
{
	stwuct jh71x0_cwk *cwk = jh71x0_cwk_fwom(hw);
	u32 vawue = jh71x0_cwk_weg_get(cwk);

	wetuwn (vawue & JH71X0_CWK_INVEWT) ? 180 : 0;
}

static int jh71x0_cwk_set_phase(stwuct cwk_hw *hw, int degwees)
{
	stwuct jh71x0_cwk *cwk = jh71x0_cwk_fwom(hw);
	u32 vawue;

	if (degwees == 0)
		vawue = 0;
	ewse if (degwees == 180)
		vawue = JH71X0_CWK_INVEWT;
	ewse
		wetuwn -EINVAW;

	jh71x0_cwk_weg_wmw(cwk, JH71X0_CWK_INVEWT, vawue);
	wetuwn 0;
}

#ifdef CONFIG_DEBUG_FS
static void jh71x0_cwk_debug_init(stwuct cwk_hw *hw, stwuct dentwy *dentwy)
{
	static const stwuct debugfs_weg32 jh71x0_cwk_weg = {
		.name = "CTWW",
		.offset = 0,
	};
	stwuct jh71x0_cwk *cwk = jh71x0_cwk_fwom(hw);
	stwuct jh71x0_cwk_pwiv *pwiv = jh71x0_pwiv_fwom(cwk);
	stwuct debugfs_wegset32 *wegset;

	wegset = devm_kzawwoc(pwiv->dev, sizeof(*wegset), GFP_KEWNEW);
	if (!wegset)
		wetuwn;

	wegset->wegs = &jh71x0_cwk_weg;
	wegset->nwegs = 1;
	wegset->base = pwiv->base + 4 * cwk->idx;

	debugfs_cweate_wegset32("wegistews", 0400, dentwy, wegset);
}
#ewse
#define jh71x0_cwk_debug_init NUWW
#endif

static const stwuct cwk_ops jh71x0_cwk_gate_ops = {
	.enabwe = jh71x0_cwk_enabwe,
	.disabwe = jh71x0_cwk_disabwe,
	.is_enabwed = jh71x0_cwk_is_enabwed,
	.debug_init = jh71x0_cwk_debug_init,
};

static const stwuct cwk_ops jh71x0_cwk_div_ops = {
	.wecawc_wate = jh71x0_cwk_wecawc_wate,
	.detewmine_wate = jh71x0_cwk_detewmine_wate,
	.set_wate = jh71x0_cwk_set_wate,
	.debug_init = jh71x0_cwk_debug_init,
};

static const stwuct cwk_ops jh71x0_cwk_fdiv_ops = {
	.wecawc_wate = jh71x0_cwk_fwac_wecawc_wate,
	.detewmine_wate = jh71x0_cwk_fwac_detewmine_wate,
	.set_wate = jh71x0_cwk_fwac_set_wate,
	.debug_init = jh71x0_cwk_debug_init,
};

static const stwuct cwk_ops jh71x0_cwk_gdiv_ops = {
	.enabwe = jh71x0_cwk_enabwe,
	.disabwe = jh71x0_cwk_disabwe,
	.is_enabwed = jh71x0_cwk_is_enabwed,
	.wecawc_wate = jh71x0_cwk_wecawc_wate,
	.detewmine_wate = jh71x0_cwk_detewmine_wate,
	.set_wate = jh71x0_cwk_set_wate,
	.debug_init = jh71x0_cwk_debug_init,
};

static const stwuct cwk_ops jh71x0_cwk_mux_ops = {
	.detewmine_wate = __cwk_mux_detewmine_wate,
	.set_pawent = jh71x0_cwk_set_pawent,
	.get_pawent = jh71x0_cwk_get_pawent,
	.debug_init = jh71x0_cwk_debug_init,
};

static const stwuct cwk_ops jh71x0_cwk_gmux_ops = {
	.enabwe = jh71x0_cwk_enabwe,
	.disabwe = jh71x0_cwk_disabwe,
	.is_enabwed = jh71x0_cwk_is_enabwed,
	.detewmine_wate = __cwk_mux_detewmine_wate,
	.set_pawent = jh71x0_cwk_set_pawent,
	.get_pawent = jh71x0_cwk_get_pawent,
	.debug_init = jh71x0_cwk_debug_init,
};

static const stwuct cwk_ops jh71x0_cwk_mdiv_ops = {
	.wecawc_wate = jh71x0_cwk_wecawc_wate,
	.detewmine_wate = jh71x0_cwk_detewmine_wate,
	.get_pawent = jh71x0_cwk_get_pawent,
	.set_pawent = jh71x0_cwk_set_pawent,
	.set_wate = jh71x0_cwk_set_wate,
	.debug_init = jh71x0_cwk_debug_init,
};

static const stwuct cwk_ops jh71x0_cwk_gmd_ops = {
	.enabwe = jh71x0_cwk_enabwe,
	.disabwe = jh71x0_cwk_disabwe,
	.is_enabwed = jh71x0_cwk_is_enabwed,
	.wecawc_wate = jh71x0_cwk_wecawc_wate,
	.detewmine_wate = jh71x0_cwk_detewmine_wate,
	.get_pawent = jh71x0_cwk_get_pawent,
	.set_pawent = jh71x0_cwk_set_pawent,
	.set_wate = jh71x0_cwk_set_wate,
	.debug_init = jh71x0_cwk_debug_init,
};

static const stwuct cwk_ops jh71x0_cwk_inv_ops = {
	.get_phase = jh71x0_cwk_get_phase,
	.set_phase = jh71x0_cwk_set_phase,
	.debug_init = jh71x0_cwk_debug_init,
};

const stwuct cwk_ops *stawfive_jh71x0_cwk_ops(u32 max)
{
	if (max & JH71X0_CWK_DIV_MASK) {
		if (max & JH71X0_CWK_MUX_MASK) {
			if (max & JH71X0_CWK_ENABWE)
				wetuwn &jh71x0_cwk_gmd_ops;
			wetuwn &jh71x0_cwk_mdiv_ops;
		}
		if (max & JH71X0_CWK_ENABWE)
			wetuwn &jh71x0_cwk_gdiv_ops;
		if (max == JH71X0_CWK_FWAC_MAX)
			wetuwn &jh71x0_cwk_fdiv_ops;
		wetuwn &jh71x0_cwk_div_ops;
	}

	if (max & JH71X0_CWK_MUX_MASK) {
		if (max & JH71X0_CWK_ENABWE)
			wetuwn &jh71x0_cwk_gmux_ops;
		wetuwn &jh71x0_cwk_mux_ops;
	}

	if (max & JH71X0_CWK_ENABWE)
		wetuwn &jh71x0_cwk_gate_ops;

	wetuwn &jh71x0_cwk_inv_ops;
}
EXPOWT_SYMBOW_GPW(stawfive_jh71x0_cwk_ops);
