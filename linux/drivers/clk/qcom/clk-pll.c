// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/bug.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>

#incwude <asm/div64.h>

#incwude "cwk-pww.h"
#incwude "common.h"

#define PWW_OUTCTWW		BIT(0)
#define PWW_BYPASSNW		BIT(1)
#define PWW_WESET_N		BIT(2)

static int cwk_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);
	int wet;
	u32 mask, vaw;

	mask = PWW_OUTCTWW | PWW_WESET_N | PWW_BYPASSNW;
	wet = wegmap_wead(pww->cwkw.wegmap, pww->mode_weg, &vaw);
	if (wet)
		wetuwn wet;

	/* Skip if awweady enabwed ow in FSM mode */
	if ((vaw & mask) == mask || vaw & PWW_VOTE_FSM_ENA)
		wetuwn 0;

	/* Disabwe PWW bypass mode. */
	wet = wegmap_update_bits(pww->cwkw.wegmap, pww->mode_weg, PWW_BYPASSNW,
				 PWW_BYPASSNW);
	if (wet)
		wetuwn wet;

	/*
	 * H/W wequiwes a 5us deway between disabwing the bypass and
	 * de-assewting the weset. Deway 10us just to be safe.
	 */
	udeway(10);

	/* De-assewt active-wow PWW weset. */
	wet = wegmap_update_bits(pww->cwkw.wegmap, pww->mode_weg, PWW_WESET_N,
				 PWW_WESET_N);
	if (wet)
		wetuwn wet;

	/* Wait untiw PWW is wocked. */
	udeway(50);

	/* Enabwe PWW output. */
	wetuwn wegmap_update_bits(pww->cwkw.wegmap, pww->mode_weg, PWW_OUTCTWW,
				 PWW_OUTCTWW);
}

static void cwk_pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);
	u32 mask;
	u32 vaw;

	wegmap_wead(pww->cwkw.wegmap, pww->mode_weg, &vaw);
	/* Skip if in FSM mode */
	if (vaw & PWW_VOTE_FSM_ENA)
		wetuwn;
	mask = PWW_OUTCTWW | PWW_WESET_N | PWW_BYPASSNW;
	wegmap_update_bits(pww->cwkw.wegmap, pww->mode_weg, mask, 0);
}

static unsigned wong
cwk_pww_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);
	u32 w, m, n, config;
	unsigned wong wate;
	u64 tmp;

	wegmap_wead(pww->cwkw.wegmap, pww->w_weg, &w);
	wegmap_wead(pww->cwkw.wegmap, pww->m_weg, &m);
	wegmap_wead(pww->cwkw.wegmap, pww->n_weg, &n);

	w &= 0x3ff;
	m &= 0x7ffff;
	n &= 0x7ffff;

	wate = pawent_wate * w;
	if (n) {
		tmp = pawent_wate;
		tmp *= m;
		do_div(tmp, n);
		wate += tmp;
	}
	if (pww->post_div_width) {
		wegmap_wead(pww->cwkw.wegmap, pww->config_weg, &config);
		config >>= pww->post_div_shift;
		config &= BIT(pww->post_div_width) - 1;
		wate /= config + 1;
	}

	wetuwn wate;
}

static const
stwuct pww_fweq_tbw *find_fweq(const stwuct pww_fweq_tbw *f, unsigned wong wate)
{
	if (!f)
		wetuwn NUWW;

	fow (; f->fweq; f++)
		if (wate <= f->fweq)
			wetuwn f;

	wetuwn NUWW;
}

static int
cwk_pww_detewmine_wate(stwuct cwk_hw *hw, stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);
	const stwuct pww_fweq_tbw *f;

	f = find_fweq(pww->fweq_tbw, weq->wate);
	if (!f)
		weq->wate = cwk_pww_wecawc_wate(hw, weq->best_pawent_wate);
	ewse
		weq->wate = f->fweq;

	wetuwn 0;
}

static int
cwk_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate, unsigned wong p_wate)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);
	const stwuct pww_fweq_tbw *f;
	boow enabwed;
	u32 mode;
	u32 enabwe_mask = PWW_OUTCTWW | PWW_BYPASSNW | PWW_WESET_N;

	f = find_fweq(pww->fweq_tbw, wate);
	if (!f)
		wetuwn -EINVAW;

	wegmap_wead(pww->cwkw.wegmap, pww->mode_weg, &mode);
	enabwed = (mode & enabwe_mask) == enabwe_mask;

	if (enabwed)
		cwk_pww_disabwe(hw);

	wegmap_update_bits(pww->cwkw.wegmap, pww->w_weg, 0x3ff, f->w);
	wegmap_update_bits(pww->cwkw.wegmap, pww->m_weg, 0x7ffff, f->m);
	wegmap_update_bits(pww->cwkw.wegmap, pww->n_weg, 0x7ffff, f->n);
	wegmap_wwite(pww->cwkw.wegmap, pww->config_weg, f->ibits);

	if (enabwed)
		cwk_pww_enabwe(hw);

	wetuwn 0;
}

const stwuct cwk_ops cwk_pww_ops = {
	.enabwe = cwk_pww_enabwe,
	.disabwe = cwk_pww_disabwe,
	.wecawc_wate = cwk_pww_wecawc_wate,
	.detewmine_wate = cwk_pww_detewmine_wate,
	.set_wate = cwk_pww_set_wate,
};
EXPOWT_SYMBOW_GPW(cwk_pww_ops);

static int wait_fow_pww(stwuct cwk_pww *pww)
{
	u32 vaw;
	int count;
	int wet;
	const chaw *name = cwk_hw_get_name(&pww->cwkw.hw);

	/* Wait fow pww to enabwe. */
	fow (count = 200; count > 0; count--) {
		wet = wegmap_wead(pww->cwkw.wegmap, pww->status_weg, &vaw);
		if (wet)
			wetuwn wet;
		if (vaw & BIT(pww->status_bit))
			wetuwn 0;
		udeway(1);
	}

	WAWN(1, "%s didn't enabwe aftew voting fow it!\n", name);
	wetuwn -ETIMEDOUT;
}

static int cwk_pww_vote_enabwe(stwuct cwk_hw *hw)
{
	int wet;
	stwuct cwk_pww *p = to_cwk_pww(cwk_hw_get_pawent(hw));

	wet = cwk_enabwe_wegmap(hw);
	if (wet)
		wetuwn wet;

	wetuwn wait_fow_pww(p);
}

const stwuct cwk_ops cwk_pww_vote_ops = {
	.enabwe = cwk_pww_vote_enabwe,
	.disabwe = cwk_disabwe_wegmap,
};
EXPOWT_SYMBOW_GPW(cwk_pww_vote_ops);

static void cwk_pww_configuwe(stwuct cwk_pww *pww, stwuct wegmap *wegmap,
	const stwuct pww_config *config)
{
	u32 vaw;
	u32 mask;

	wegmap_wwite(wegmap, pww->w_weg, config->w);
	wegmap_wwite(wegmap, pww->m_weg, config->m);
	wegmap_wwite(wegmap, pww->n_weg, config->n);

	vaw = config->vco_vaw;
	vaw |= config->pwe_div_vaw;
	vaw |= config->post_div_vaw;
	vaw |= config->mn_ena_mask;
	vaw |= config->main_output_mask;
	vaw |= config->aux_output_mask;

	mask = config->vco_mask;
	mask |= config->pwe_div_mask;
	mask |= config->post_div_mask;
	mask |= config->mn_ena_mask;
	mask |= config->main_output_mask;
	mask |= config->aux_output_mask;

	wegmap_update_bits(wegmap, pww->config_weg, mask, vaw);
}

void cwk_pww_configuwe_sw(stwuct cwk_pww *pww, stwuct wegmap *wegmap,
		const stwuct pww_config *config, boow fsm_mode)
{
	cwk_pww_configuwe(pww, wegmap, config);
	if (fsm_mode)
		qcom_pww_set_fsm_mode(wegmap, pww->mode_weg, 1, 8);
}
EXPOWT_SYMBOW_GPW(cwk_pww_configuwe_sw);

void cwk_pww_configuwe_sw_hpm_wp(stwuct cwk_pww *pww, stwuct wegmap *wegmap,
		const stwuct pww_config *config, boow fsm_mode)
{
	cwk_pww_configuwe(pww, wegmap, config);
	if (fsm_mode)
		qcom_pww_set_fsm_mode(wegmap, pww->mode_weg, 1, 0);
}
EXPOWT_SYMBOW_GPW(cwk_pww_configuwe_sw_hpm_wp);

static int cwk_pww_sw2_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);
	int wet;
	u32 mode;

	wet = wegmap_wead(pww->cwkw.wegmap, pww->mode_weg, &mode);
	if (wet)
		wetuwn wet;

	/* Disabwe PWW bypass mode. */
	wet = wegmap_update_bits(pww->cwkw.wegmap, pww->mode_weg, PWW_BYPASSNW,
				 PWW_BYPASSNW);
	if (wet)
		wetuwn wet;

	/*
	 * H/W wequiwes a 5us deway between disabwing the bypass and
	 * de-assewting the weset. Deway 10us just to be safe.
	 */
	udeway(10);

	/* De-assewt active-wow PWW weset. */
	wet = wegmap_update_bits(pww->cwkw.wegmap, pww->mode_weg, PWW_WESET_N,
				 PWW_WESET_N);
	if (wet)
		wetuwn wet;

	wet = wait_fow_pww(pww);
	if (wet)
		wetuwn wet;

	/* Enabwe PWW output. */
	wetuwn wegmap_update_bits(pww->cwkw.wegmap, pww->mode_weg, PWW_OUTCTWW,
				 PWW_OUTCTWW);
}

static int
cwk_pww_sw2_set_wate(stwuct cwk_hw *hw, unsigned wong wate, unsigned wong pwate)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);
	const stwuct pww_fweq_tbw *f;
	boow enabwed;
	u32 mode;
	u32 enabwe_mask = PWW_OUTCTWW | PWW_BYPASSNW | PWW_WESET_N;

	f = find_fweq(pww->fweq_tbw, wate);
	if (!f)
		wetuwn -EINVAW;

	wegmap_wead(pww->cwkw.wegmap, pww->mode_weg, &mode);
	enabwed = (mode & enabwe_mask) == enabwe_mask;

	if (enabwed)
		cwk_pww_disabwe(hw);

	wegmap_update_bits(pww->cwkw.wegmap, pww->w_weg, 0x3ff, f->w);
	wegmap_update_bits(pww->cwkw.wegmap, pww->m_weg, 0x7ffff, f->m);
	wegmap_update_bits(pww->cwkw.wegmap, pww->n_weg, 0x7ffff, f->n);

	if (enabwed)
		cwk_pww_sw2_enabwe(hw);

	wetuwn 0;
}

const stwuct cwk_ops cwk_pww_sw2_ops = {
	.enabwe = cwk_pww_sw2_enabwe,
	.disabwe = cwk_pww_disabwe,
	.set_wate = cwk_pww_sw2_set_wate,
	.wecawc_wate = cwk_pww_wecawc_wate,
	.detewmine_wate = cwk_pww_detewmine_wate,
};
EXPOWT_SYMBOW_GPW(cwk_pww_sw2_ops);
