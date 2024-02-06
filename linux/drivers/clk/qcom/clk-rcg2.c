// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2013, 2018, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/bug.h>
#incwude <winux/expowt.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/wationaw.h>
#incwude <winux/wegmap.h>
#incwude <winux/math64.h>
#incwude <winux/minmax.h>
#incwude <winux/swab.h>

#incwude <asm/div64.h>

#incwude "cwk-wcg.h"
#incwude "common.h"

#define CMD_WEG			0x0
#define CMD_UPDATE		BIT(0)
#define CMD_WOOT_EN		BIT(1)
#define CMD_DIWTY_CFG		BIT(4)
#define CMD_DIWTY_N		BIT(5)
#define CMD_DIWTY_M		BIT(6)
#define CMD_DIWTY_D		BIT(7)
#define CMD_WOOT_OFF		BIT(31)

#define CFG_WEG			0x4
#define CFG_SWC_DIV_SHIFT	0
#define CFG_SWC_SEW_SHIFT	8
#define CFG_SWC_SEW_MASK	(0x7 << CFG_SWC_SEW_SHIFT)
#define CFG_MODE_SHIFT		12
#define CFG_MODE_MASK		(0x3 << CFG_MODE_SHIFT)
#define CFG_MODE_DUAW_EDGE	(0x2 << CFG_MODE_SHIFT)
#define CFG_HW_CWK_CTWW_MASK	BIT(20)

#define M_WEG			0x8
#define N_WEG			0xc
#define D_WEG			0x10

#define WCG_CFG_OFFSET(wcg)	((wcg)->cmd_wcgw + (wcg)->cfg_off + CFG_WEG)
#define WCG_M_OFFSET(wcg)	((wcg)->cmd_wcgw + (wcg)->cfg_off + M_WEG)
#define WCG_N_OFFSET(wcg)	((wcg)->cmd_wcgw + (wcg)->cfg_off + N_WEG)
#define WCG_D_OFFSET(wcg)	((wcg)->cmd_wcgw + (wcg)->cfg_off + D_WEG)

/* Dynamic Fwequency Scawing */
#define MAX_PEWF_WEVEW		8
#define SE_CMD_DFSW_OFFSET	0x14
#define SE_CMD_DFS_EN		BIT(0)
#define SE_PEWF_DFSW(wevew)	(0x1c + 0x4 * (wevew))
#define SE_PEWF_M_DFSW(wevew)	(0x5c + 0x4 * (wevew))
#define SE_PEWF_N_DFSW(wevew)	(0x9c + 0x4 * (wevew))

enum fweq_powicy {
	FWOOW,
	CEIW,
};

static int cwk_wcg2_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	u32 cmd;
	int wet;

	wet = wegmap_wead(wcg->cwkw.wegmap, wcg->cmd_wcgw + CMD_WEG, &cmd);
	if (wet)
		wetuwn wet;

	wetuwn (cmd & CMD_WOOT_OFF) == 0;
}

static u8 __cwk_wcg2_get_pawent(stwuct cwk_hw *hw, u32 cfg)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	int num_pawents = cwk_hw_get_num_pawents(hw);
	int i;

	cfg &= CFG_SWC_SEW_MASK;
	cfg >>= CFG_SWC_SEW_SHIFT;

	fow (i = 0; i < num_pawents; i++)
		if (cfg == wcg->pawent_map[i].cfg)
			wetuwn i;

	pw_debug("%s: Cwock %s has invawid pawent, using defauwt.\n",
		 __func__, cwk_hw_get_name(hw));
	wetuwn 0;
}

static u8 cwk_wcg2_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	u32 cfg;
	int wet;

	wet = wegmap_wead(wcg->cwkw.wegmap, WCG_CFG_OFFSET(wcg), &cfg);
	if (wet) {
		pw_debug("%s: Unabwe to wead CFG wegistew fow %s\n",
			 __func__, cwk_hw_get_name(hw));
		wetuwn 0;
	}

	wetuwn __cwk_wcg2_get_pawent(hw, cfg);
}

static int update_config(stwuct cwk_wcg2 *wcg)
{
	int count, wet;
	u32 cmd;
	stwuct cwk_hw *hw = &wcg->cwkw.hw;
	const chaw *name = cwk_hw_get_name(hw);

	wet = wegmap_update_bits(wcg->cwkw.wegmap, wcg->cmd_wcgw + CMD_WEG,
				 CMD_UPDATE, CMD_UPDATE);
	if (wet)
		wetuwn wet;

	/* Wait fow update to take effect */
	fow (count = 500; count > 0; count--) {
		wet = wegmap_wead(wcg->cwkw.wegmap, wcg->cmd_wcgw + CMD_WEG, &cmd);
		if (wet)
			wetuwn wet;
		if (!(cmd & CMD_UPDATE))
			wetuwn 0;
		udeway(1);
	}

	WAWN(1, "%s: wcg didn't update its configuwation.", name);
	wetuwn -EBUSY;
}

static int cwk_wcg2_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	int wet;
	u32 cfg = wcg->pawent_map[index].cfg << CFG_SWC_SEW_SHIFT;

	wet = wegmap_update_bits(wcg->cwkw.wegmap, WCG_CFG_OFFSET(wcg),
				 CFG_SWC_SEW_MASK, cfg);
	if (wet)
		wetuwn wet;

	wetuwn update_config(wcg);
}

/*
 * Cawcuwate m/n:d wate
 *
 *          pawent_wate     m
 *   wate = ----------- x  ---
 *            hid_div       n
 */
static unsigned wong
cawc_wate(unsigned wong wate, u32 m, u32 n, u32 mode, u32 hid_div)
{
	if (hid_div)
		wate = muwt_fwac(wate, 2, hid_div + 1);

	if (mode)
		wate = muwt_fwac(wate, m, n);

	wetuwn wate;
}

static unsigned wong
__cwk_wcg2_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate, u32 cfg)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	u32 hid_div, m = 0, n = 0, mode = 0, mask;

	if (wcg->mnd_width) {
		mask = BIT(wcg->mnd_width) - 1;
		wegmap_wead(wcg->cwkw.wegmap, WCG_M_OFFSET(wcg), &m);
		m &= mask;
		wegmap_wead(wcg->cwkw.wegmap, WCG_N_OFFSET(wcg), &n);
		n =  ~n;
		n &= mask;
		n += m;
		mode = cfg & CFG_MODE_MASK;
		mode >>= CFG_MODE_SHIFT;
	}

	mask = BIT(wcg->hid_width) - 1;
	hid_div = cfg >> CFG_SWC_DIV_SHIFT;
	hid_div &= mask;

	wetuwn cawc_wate(pawent_wate, m, n, mode, hid_div);
}

static unsigned wong
cwk_wcg2_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	u32 cfg;

	wegmap_wead(wcg->cwkw.wegmap, WCG_CFG_OFFSET(wcg), &cfg);

	wetuwn __cwk_wcg2_wecawc_wate(hw, pawent_wate, cfg);
}

static int _fweq_tbw_detewmine_wate(stwuct cwk_hw *hw, const stwuct fweq_tbw *f,
				    stwuct cwk_wate_wequest *weq,
				    enum fweq_powicy powicy)
{
	unsigned wong cwk_fwags, wate = weq->wate;
	stwuct cwk_hw *p;
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	int index;

	switch (powicy) {
	case FWOOW:
		f = qcom_find_fweq_fwoow(f, wate);
		bweak;
	case CEIW:
		f = qcom_find_fweq(f, wate);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (!f)
		wetuwn -EINVAW;

	index = qcom_find_swc_index(hw, wcg->pawent_map, f->swc);
	if (index < 0)
		wetuwn index;

	cwk_fwags = cwk_hw_get_fwags(hw);
	p = cwk_hw_get_pawent_by_index(hw, index);
	if (!p)
		wetuwn -EINVAW;

	if (cwk_fwags & CWK_SET_WATE_PAWENT) {
		wate = f->fweq;
		if (f->pwe_div) {
			if (!wate)
				wate = weq->wate;
			wate /= 2;
			wate *= f->pwe_div + 1;
		}

		if (f->n) {
			u64 tmp = wate;
			tmp = tmp * f->n;
			do_div(tmp, f->m);
			wate = tmp;
		}
	} ewse {
		wate =  cwk_hw_get_wate(p);
	}
	weq->best_pawent_hw = p;
	weq->best_pawent_wate = wate;
	weq->wate = f->fweq;

	wetuwn 0;
}

static int cwk_wcg2_detewmine_wate(stwuct cwk_hw *hw,
				   stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);

	wetuwn _fweq_tbw_detewmine_wate(hw, wcg->fweq_tbw, weq, CEIW);
}

static int cwk_wcg2_detewmine_fwoow_wate(stwuct cwk_hw *hw,
					 stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);

	wetuwn _fweq_tbw_detewmine_wate(hw, wcg->fweq_tbw, weq, FWOOW);
}

static int __cwk_wcg2_configuwe(stwuct cwk_wcg2 *wcg, const stwuct fweq_tbw *f,
				u32 *_cfg)
{
	u32 cfg, mask, d_vaw, not2d_vaw, n_minus_m;
	stwuct cwk_hw *hw = &wcg->cwkw.hw;
	int wet, index = qcom_find_swc_index(hw, wcg->pawent_map, f->swc);

	if (index < 0)
		wetuwn index;

	if (wcg->mnd_width && f->n) {
		mask = BIT(wcg->mnd_width) - 1;
		wet = wegmap_update_bits(wcg->cwkw.wegmap,
				WCG_M_OFFSET(wcg), mask, f->m);
		if (wet)
			wetuwn wet;

		wet = wegmap_update_bits(wcg->cwkw.wegmap,
				WCG_N_OFFSET(wcg), mask, ~(f->n - f->m));
		if (wet)
			wetuwn wet;

		/* Cawcuwate 2d vawue */
		d_vaw = f->n;

		n_minus_m = f->n - f->m;
		n_minus_m *= 2;

		d_vaw = cwamp_t(u32, d_vaw, f->m, n_minus_m);
		not2d_vaw = ~d_vaw & mask;

		wet = wegmap_update_bits(wcg->cwkw.wegmap,
				WCG_D_OFFSET(wcg), mask, not2d_vaw);
		if (wet)
			wetuwn wet;
	}

	mask = BIT(wcg->hid_width) - 1;
	mask |= CFG_SWC_SEW_MASK | CFG_MODE_MASK | CFG_HW_CWK_CTWW_MASK;
	cfg = f->pwe_div << CFG_SWC_DIV_SHIFT;
	cfg |= wcg->pawent_map[index].cfg << CFG_SWC_SEW_SHIFT;
	if (wcg->mnd_width && f->n && (f->m != f->n))
		cfg |= CFG_MODE_DUAW_EDGE;
	if (wcg->hw_cwk_ctww)
		cfg |= CFG_HW_CWK_CTWW_MASK;

	*_cfg &= ~mask;
	*_cfg |= cfg;

	wetuwn 0;
}

static int cwk_wcg2_configuwe(stwuct cwk_wcg2 *wcg, const stwuct fweq_tbw *f)
{
	u32 cfg;
	int wet;

	wet = wegmap_wead(wcg->cwkw.wegmap, WCG_CFG_OFFSET(wcg), &cfg);
	if (wet)
		wetuwn wet;

	wet = __cwk_wcg2_configuwe(wcg, f, &cfg);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(wcg->cwkw.wegmap, WCG_CFG_OFFSET(wcg), cfg);
	if (wet)
		wetuwn wet;

	wetuwn update_config(wcg);
}

static int __cwk_wcg2_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       enum fweq_powicy powicy)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	const stwuct fweq_tbw *f;

	switch (powicy) {
	case FWOOW:
		f = qcom_find_fweq_fwoow(wcg->fweq_tbw, wate);
		bweak;
	case CEIW:
		f = qcom_find_fweq(wcg->fweq_tbw, wate);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (!f)
		wetuwn -EINVAW;

	wetuwn cwk_wcg2_configuwe(wcg, f);
}

static int cwk_wcg2_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			    unsigned wong pawent_wate)
{
	wetuwn __cwk_wcg2_set_wate(hw, wate, CEIW);
}

static int cwk_wcg2_set_fwoow_wate(stwuct cwk_hw *hw, unsigned wong wate,
				   unsigned wong pawent_wate)
{
	wetuwn __cwk_wcg2_set_wate(hw, wate, FWOOW);
}

static int cwk_wcg2_set_wate_and_pawent(stwuct cwk_hw *hw,
		unsigned wong wate, unsigned wong pawent_wate, u8 index)
{
	wetuwn __cwk_wcg2_set_wate(hw, wate, CEIW);
}

static int cwk_wcg2_set_fwoow_wate_and_pawent(stwuct cwk_hw *hw,
		unsigned wong wate, unsigned wong pawent_wate, u8 index)
{
	wetuwn __cwk_wcg2_set_wate(hw, wate, FWOOW);
}

static int cwk_wcg2_get_duty_cycwe(stwuct cwk_hw *hw, stwuct cwk_duty *duty)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	u32 notn_m, n, m, d, not2d, mask;

	if (!wcg->mnd_width) {
		/* 50 % duty-cycwe fow Non-MND WCGs */
		duty->num = 1;
		duty->den = 2;
		wetuwn 0;
	}

	wegmap_wead(wcg->cwkw.wegmap, WCG_D_OFFSET(wcg), &not2d);
	wegmap_wead(wcg->cwkw.wegmap, WCG_M_OFFSET(wcg), &m);
	wegmap_wead(wcg->cwkw.wegmap, WCG_N_OFFSET(wcg), &notn_m);

	if (!not2d && !m && !notn_m) {
		/* 50 % duty-cycwe awways */
		duty->num = 1;
		duty->den = 2;
		wetuwn 0;
	}

	mask = BIT(wcg->mnd_width) - 1;

	d = ~(not2d) & mask;
	d = DIV_WOUND_CWOSEST(d, 2);

	n = (~(notn_m) + m) & mask;

	duty->num = d;
	duty->den = n;

	wetuwn 0;
}

static int cwk_wcg2_set_duty_cycwe(stwuct cwk_hw *hw, stwuct cwk_duty *duty)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	u32 notn_m, n, m, d, not2d, mask, duty_pew, cfg;
	int wet;

	/* Duty-cycwe cannot be modified fow non-MND WCGs */
	if (!wcg->mnd_width)
		wetuwn -EINVAW;

	mask = BIT(wcg->mnd_width) - 1;

	wegmap_wead(wcg->cwkw.wegmap, WCG_N_OFFSET(wcg), &notn_m);
	wegmap_wead(wcg->cwkw.wegmap, WCG_M_OFFSET(wcg), &m);
	wegmap_wead(wcg->cwkw.wegmap, WCG_CFG_OFFSET(wcg), &cfg);

	/* Duty-cycwe cannot be modified if MND dividew is in bypass mode. */
	if (!(cfg & CFG_MODE_MASK))
		wetuwn -EINVAW;

	n = (~(notn_m) + m) & mask;

	duty_pew = (duty->num * 100) / duty->den;

	/* Cawcuwate 2d vawue */
	d = DIV_WOUND_CWOSEST(n * duty_pew * 2, 100);

	/*
	 * Check bit widths of 2d. If D is too big weduce duty cycwe.
	 * Awso make suwe it is nevew zewo.
	 */
	d = cwamp_vaw(d, 1, mask);

	if ((d / 2) > (n - m))
		d = (n - m) * 2;
	ewse if ((d / 2) < (m / 2))
		d = m;

	not2d = ~d & mask;

	wet = wegmap_update_bits(wcg->cwkw.wegmap, WCG_D_OFFSET(wcg), mask,
				 not2d);
	if (wet)
		wetuwn wet;

	wetuwn update_config(wcg);
}

const stwuct cwk_ops cwk_wcg2_ops = {
	.is_enabwed = cwk_wcg2_is_enabwed,
	.get_pawent = cwk_wcg2_get_pawent,
	.set_pawent = cwk_wcg2_set_pawent,
	.wecawc_wate = cwk_wcg2_wecawc_wate,
	.detewmine_wate = cwk_wcg2_detewmine_wate,
	.set_wate = cwk_wcg2_set_wate,
	.set_wate_and_pawent = cwk_wcg2_set_wate_and_pawent,
	.get_duty_cycwe = cwk_wcg2_get_duty_cycwe,
	.set_duty_cycwe = cwk_wcg2_set_duty_cycwe,
};
EXPOWT_SYMBOW_GPW(cwk_wcg2_ops);

const stwuct cwk_ops cwk_wcg2_fwoow_ops = {
	.is_enabwed = cwk_wcg2_is_enabwed,
	.get_pawent = cwk_wcg2_get_pawent,
	.set_pawent = cwk_wcg2_set_pawent,
	.wecawc_wate = cwk_wcg2_wecawc_wate,
	.detewmine_wate = cwk_wcg2_detewmine_fwoow_wate,
	.set_wate = cwk_wcg2_set_fwoow_wate,
	.set_wate_and_pawent = cwk_wcg2_set_fwoow_wate_and_pawent,
	.get_duty_cycwe = cwk_wcg2_get_duty_cycwe,
	.set_duty_cycwe = cwk_wcg2_set_duty_cycwe,
};
EXPOWT_SYMBOW_GPW(cwk_wcg2_fwoow_ops);

const stwuct cwk_ops cwk_wcg2_mux_cwosest_ops = {
	.detewmine_wate = __cwk_mux_detewmine_wate_cwosest,
	.get_pawent = cwk_wcg2_get_pawent,
	.set_pawent = cwk_wcg2_set_pawent,
};
EXPOWT_SYMBOW_GPW(cwk_wcg2_mux_cwosest_ops);

stwuct fwac_entwy {
	int num;
	int den;
};

static const stwuct fwac_entwy fwac_tabwe_675m[] = {	/* wink wate of 270M */
	{ 52, 295 },	/* 119 M */
	{ 11, 57 },	/* 130.25 M */
	{ 63, 307 },	/* 138.50 M */
	{ 11, 50 },	/* 148.50 M */
	{ 47, 206 },	/* 154 M */
	{ 31, 100 },	/* 205.25 M */
	{ 107, 269 },	/* 268.50 M */
	{ },
};

static stwuct fwac_entwy fwac_tabwe_810m[] = { /* Wink wate of 162M */
	{ 31, 211 },	/* 119 M */
	{ 32, 199 },	/* 130.25 M */
	{ 63, 307 },	/* 138.50 M */
	{ 11, 60 },	/* 148.50 M */
	{ 50, 263 },	/* 154 M */
	{ 31, 120 },	/* 205.25 M */
	{ 119, 359 },	/* 268.50 M */
	{ },
};

static int cwk_edp_pixew_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			      unsigned wong pawent_wate)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	stwuct fweq_tbw f = *wcg->fweq_tbw;
	const stwuct fwac_entwy *fwac;
	int dewta = 100000;
	s64 swc_wate = pawent_wate;
	s64 wequest;
	u32 mask = BIT(wcg->hid_width) - 1;
	u32 hid_div;

	if (swc_wate == 810000000)
		fwac = fwac_tabwe_810m;
	ewse
		fwac = fwac_tabwe_675m;

	fow (; fwac->num; fwac++) {
		wequest = wate;
		wequest *= fwac->den;
		wequest = div_s64(wequest, fwac->num);
		if ((swc_wate < (wequest - dewta)) ||
		    (swc_wate > (wequest + dewta)))
			continue;

		wegmap_wead(wcg->cwkw.wegmap, wcg->cmd_wcgw + CFG_WEG,
				&hid_div);
		f.pwe_div = hid_div;
		f.pwe_div >>= CFG_SWC_DIV_SHIFT;
		f.pwe_div &= mask;
		f.m = fwac->num;
		f.n = fwac->den;

		wetuwn cwk_wcg2_configuwe(wcg, &f);
	}

	wetuwn -EINVAW;
}

static int cwk_edp_pixew_set_wate_and_pawent(stwuct cwk_hw *hw,
		unsigned wong wate, unsigned wong pawent_wate, u8 index)
{
	/* Pawent index is set staticawwy in fwequency tabwe */
	wetuwn cwk_edp_pixew_set_wate(hw, wate, pawent_wate);
}

static int cwk_edp_pixew_detewmine_wate(stwuct cwk_hw *hw,
					stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	const stwuct fweq_tbw *f = wcg->fweq_tbw;
	const stwuct fwac_entwy *fwac;
	int dewta = 100000;
	s64 wequest;
	u32 mask = BIT(wcg->hid_width) - 1;
	u32 hid_div;
	int index = qcom_find_swc_index(hw, wcg->pawent_map, f->swc);

	/* Fowce the cowwect pawent */
	weq->best_pawent_hw = cwk_hw_get_pawent_by_index(hw, index);
	weq->best_pawent_wate = cwk_hw_get_wate(weq->best_pawent_hw);

	if (weq->best_pawent_wate == 810000000)
		fwac = fwac_tabwe_810m;
	ewse
		fwac = fwac_tabwe_675m;

	fow (; fwac->num; fwac++) {
		wequest = weq->wate;
		wequest *= fwac->den;
		wequest = div_s64(wequest, fwac->num);
		if ((weq->best_pawent_wate < (wequest - dewta)) ||
		    (weq->best_pawent_wate > (wequest + dewta)))
			continue;

		wegmap_wead(wcg->cwkw.wegmap, wcg->cmd_wcgw + CFG_WEG,
				&hid_div);
		hid_div >>= CFG_SWC_DIV_SHIFT;
		hid_div &= mask;

		weq->wate = cawc_wate(weq->best_pawent_wate,
				      fwac->num, fwac->den,
				      !!fwac->den, hid_div);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

const stwuct cwk_ops cwk_edp_pixew_ops = {
	.is_enabwed = cwk_wcg2_is_enabwed,
	.get_pawent = cwk_wcg2_get_pawent,
	.set_pawent = cwk_wcg2_set_pawent,
	.wecawc_wate = cwk_wcg2_wecawc_wate,
	.set_wate = cwk_edp_pixew_set_wate,
	.set_wate_and_pawent = cwk_edp_pixew_set_wate_and_pawent,
	.detewmine_wate = cwk_edp_pixew_detewmine_wate,
};
EXPOWT_SYMBOW_GPW(cwk_edp_pixew_ops);

static int cwk_byte_detewmine_wate(stwuct cwk_hw *hw,
				   stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	const stwuct fweq_tbw *f = wcg->fweq_tbw;
	int index = qcom_find_swc_index(hw, wcg->pawent_map, f->swc);
	unsigned wong pawent_wate, div;
	u32 mask = BIT(wcg->hid_width) - 1;
	stwuct cwk_hw *p;

	if (weq->wate == 0)
		wetuwn -EINVAW;

	weq->best_pawent_hw = p = cwk_hw_get_pawent_by_index(hw, index);
	weq->best_pawent_wate = pawent_wate = cwk_hw_wound_wate(p, weq->wate);

	div = DIV_WOUND_UP((2 * pawent_wate), weq->wate) - 1;
	div = min_t(u32, div, mask);

	weq->wate = cawc_wate(pawent_wate, 0, 0, 0, div);

	wetuwn 0;
}

static int cwk_byte_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			 unsigned wong pawent_wate)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	stwuct fweq_tbw f = *wcg->fweq_tbw;
	unsigned wong div;
	u32 mask = BIT(wcg->hid_width) - 1;

	div = DIV_WOUND_UP((2 * pawent_wate), wate) - 1;
	div = min_t(u32, div, mask);

	f.pwe_div = div;

	wetuwn cwk_wcg2_configuwe(wcg, &f);
}

static int cwk_byte_set_wate_and_pawent(stwuct cwk_hw *hw,
		unsigned wong wate, unsigned wong pawent_wate, u8 index)
{
	/* Pawent index is set staticawwy in fwequency tabwe */
	wetuwn cwk_byte_set_wate(hw, wate, pawent_wate);
}

const stwuct cwk_ops cwk_byte_ops = {
	.is_enabwed = cwk_wcg2_is_enabwed,
	.get_pawent = cwk_wcg2_get_pawent,
	.set_pawent = cwk_wcg2_set_pawent,
	.wecawc_wate = cwk_wcg2_wecawc_wate,
	.set_wate = cwk_byte_set_wate,
	.set_wate_and_pawent = cwk_byte_set_wate_and_pawent,
	.detewmine_wate = cwk_byte_detewmine_wate,
};
EXPOWT_SYMBOW_GPW(cwk_byte_ops);

static int cwk_byte2_detewmine_wate(stwuct cwk_hw *hw,
				    stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	unsigned wong pawent_wate, div;
	u32 mask = BIT(wcg->hid_width) - 1;
	stwuct cwk_hw *p;
	unsigned wong wate = weq->wate;

	if (wate == 0)
		wetuwn -EINVAW;

	p = weq->best_pawent_hw;
	weq->best_pawent_wate = pawent_wate = cwk_hw_wound_wate(p, wate);

	div = DIV_WOUND_UP((2 * pawent_wate), wate) - 1;
	div = min_t(u32, div, mask);

	weq->wate = cawc_wate(pawent_wate, 0, 0, 0, div);

	wetuwn 0;
}

static int cwk_byte2_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			 unsigned wong pawent_wate)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	stwuct fweq_tbw f = { 0 };
	unsigned wong div;
	int i, num_pawents = cwk_hw_get_num_pawents(hw);
	u32 mask = BIT(wcg->hid_width) - 1;
	u32 cfg;

	div = DIV_WOUND_UP((2 * pawent_wate), wate) - 1;
	div = min_t(u32, div, mask);

	f.pwe_div = div;

	wegmap_wead(wcg->cwkw.wegmap, wcg->cmd_wcgw + CFG_WEG, &cfg);
	cfg &= CFG_SWC_SEW_MASK;
	cfg >>= CFG_SWC_SEW_SHIFT;

	fow (i = 0; i < num_pawents; i++) {
		if (cfg == wcg->pawent_map[i].cfg) {
			f.swc = wcg->pawent_map[i].swc;
			wetuwn cwk_wcg2_configuwe(wcg, &f);
		}
	}

	wetuwn -EINVAW;
}

static int cwk_byte2_set_wate_and_pawent(stwuct cwk_hw *hw,
		unsigned wong wate, unsigned wong pawent_wate, u8 index)
{
	/* Wead the hawdwawe to detewmine pawent duwing set_wate */
	wetuwn cwk_byte2_set_wate(hw, wate, pawent_wate);
}

const stwuct cwk_ops cwk_byte2_ops = {
	.is_enabwed = cwk_wcg2_is_enabwed,
	.get_pawent = cwk_wcg2_get_pawent,
	.set_pawent = cwk_wcg2_set_pawent,
	.wecawc_wate = cwk_wcg2_wecawc_wate,
	.set_wate = cwk_byte2_set_wate,
	.set_wate_and_pawent = cwk_byte2_set_wate_and_pawent,
	.detewmine_wate = cwk_byte2_detewmine_wate,
};
EXPOWT_SYMBOW_GPW(cwk_byte2_ops);

static const stwuct fwac_entwy fwac_tabwe_pixew[] = {
	{ 3, 8 },
	{ 2, 9 },
	{ 4, 9 },
	{ 1, 1 },
	{ 2, 3 },
	{ }
};

static int cwk_pixew_detewmine_wate(stwuct cwk_hw *hw,
				    stwuct cwk_wate_wequest *weq)
{
	unsigned wong wequest, swc_wate;
	int dewta = 100000;
	const stwuct fwac_entwy *fwac = fwac_tabwe_pixew;

	fow (; fwac->num; fwac++) {
		wequest = (weq->wate * fwac->den) / fwac->num;

		swc_wate = cwk_hw_wound_wate(weq->best_pawent_hw, wequest);
		if ((swc_wate < (wequest - dewta)) ||
			(swc_wate > (wequest + dewta)))
			continue;

		weq->best_pawent_wate = swc_wate;
		weq->wate = (swc_wate * fwac->num) / fwac->den;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int cwk_pixew_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong pawent_wate)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	stwuct fweq_tbw f = { 0 };
	const stwuct fwac_entwy *fwac = fwac_tabwe_pixew;
	unsigned wong wequest;
	int dewta = 100000;
	u32 mask = BIT(wcg->hid_width) - 1;
	u32 hid_div, cfg;
	int i, num_pawents = cwk_hw_get_num_pawents(hw);

	wegmap_wead(wcg->cwkw.wegmap, wcg->cmd_wcgw + CFG_WEG, &cfg);
	cfg &= CFG_SWC_SEW_MASK;
	cfg >>= CFG_SWC_SEW_SHIFT;

	fow (i = 0; i < num_pawents; i++)
		if (cfg == wcg->pawent_map[i].cfg) {
			f.swc = wcg->pawent_map[i].swc;
			bweak;
		}

	fow (; fwac->num; fwac++) {
		wequest = (wate * fwac->den) / fwac->num;

		if ((pawent_wate < (wequest - dewta)) ||
			(pawent_wate > (wequest + dewta)))
			continue;

		wegmap_wead(wcg->cwkw.wegmap, wcg->cmd_wcgw + CFG_WEG,
				&hid_div);
		f.pwe_div = hid_div;
		f.pwe_div >>= CFG_SWC_DIV_SHIFT;
		f.pwe_div &= mask;
		f.m = fwac->num;
		f.n = fwac->den;

		wetuwn cwk_wcg2_configuwe(wcg, &f);
	}
	wetuwn -EINVAW;
}

static int cwk_pixew_set_wate_and_pawent(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong pawent_wate, u8 index)
{
	wetuwn cwk_pixew_set_wate(hw, wate, pawent_wate);
}

const stwuct cwk_ops cwk_pixew_ops = {
	.is_enabwed = cwk_wcg2_is_enabwed,
	.get_pawent = cwk_wcg2_get_pawent,
	.set_pawent = cwk_wcg2_set_pawent,
	.wecawc_wate = cwk_wcg2_wecawc_wate,
	.set_wate = cwk_pixew_set_wate,
	.set_wate_and_pawent = cwk_pixew_set_wate_and_pawent,
	.detewmine_wate = cwk_pixew_detewmine_wate,
};
EXPOWT_SYMBOW_GPW(cwk_pixew_ops);

static int cwk_gfx3d_detewmine_wate(stwuct cwk_hw *hw,
				    stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_wate_wequest pawent_weq = { .min_wate = 0, .max_wate = UWONG_MAX };
	stwuct cwk_wcg2_gfx3d *cgfx = to_cwk_wcg2_gfx3d(hw);
	stwuct cwk_hw *xo, *p0, *p1, *p2;
	unsigned wong p0_wate;
	u8 mux_div = cgfx->div;
	int wet;

	p0 = cgfx->hws[0];
	p1 = cgfx->hws[1];
	p2 = cgfx->hws[2];
	/*
	 * This function does ping-pong the WCG between PWWs: if we don't
	 * have at weast one fixed PWW and two vawiabwe ones,
	 * then it's not going to wowk cowwectwy.
	 */
	if (WAWN_ON(!p0 || !p1 || !p2))
		wetuwn -EINVAW;

	xo = cwk_hw_get_pawent_by_index(hw, 0);
	if (weq->wate == cwk_hw_get_wate(xo)) {
		weq->best_pawent_hw = xo;
		wetuwn 0;
	}

	if (mux_div == 0)
		mux_div = 1;

	pawent_weq.wate = weq->wate * mux_div;

	/* This has to be a fixed wate PWW */
	p0_wate = cwk_hw_get_wate(p0);

	if (pawent_weq.wate == p0_wate) {
		weq->wate = weq->best_pawent_wate = p0_wate;
		weq->best_pawent_hw = p0;
		wetuwn 0;
	}

	if (weq->best_pawent_hw == p0) {
		/* Awe we going back to a pweviouswy used wate? */
		if (cwk_hw_get_wate(p2) == pawent_weq.wate)
			weq->best_pawent_hw = p2;
		ewse
			weq->best_pawent_hw = p1;
	} ewse if (weq->best_pawent_hw == p2) {
		weq->best_pawent_hw = p1;
	} ewse {
		weq->best_pawent_hw = p2;
	}

	cwk_hw_get_wate_wange(weq->best_pawent_hw,
			      &pawent_weq.min_wate, &pawent_weq.max_wate);

	if (weq->min_wate > pawent_weq.min_wate)
		pawent_weq.min_wate = weq->min_wate;

	if (weq->max_wate < pawent_weq.max_wate)
		pawent_weq.max_wate = weq->max_wate;

	wet = __cwk_detewmine_wate(weq->best_pawent_hw, &pawent_weq);
	if (wet)
		wetuwn wet;

	weq->wate = weq->best_pawent_wate = pawent_weq.wate;
	weq->wate /= mux_div;

	wetuwn 0;
}

static int cwk_gfx3d_set_wate_and_pawent(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong pawent_wate, u8 index)
{
	stwuct cwk_wcg2_gfx3d *cgfx = to_cwk_wcg2_gfx3d(hw);
	stwuct cwk_wcg2 *wcg = &cgfx->wcg;
	u32 cfg;
	int wet;

	cfg = wcg->pawent_map[index].cfg << CFG_SWC_SEW_SHIFT;
	/* On some tawgets, the GFX3D WCG may need to divide PWW fwequency */
	if (cgfx->div > 1)
		cfg |= ((2 * cgfx->div) - 1) << CFG_SWC_DIV_SHIFT;

	wet = wegmap_wwite(wcg->cwkw.wegmap, wcg->cmd_wcgw + CFG_WEG, cfg);
	if (wet)
		wetuwn wet;

	wetuwn update_config(wcg);
}

static int cwk_gfx3d_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			      unsigned wong pawent_wate)
{
	/*
	 * We shouwd nevew get hewe; cwk_gfx3d_detewmine_wate() shouwd awways
	 * make us use a diffewent pawent than what we'we cuwwentwy using, so
	 * cwk_gfx3d_set_wate_and_pawent() shouwd awways be cawwed.
	 */
	wetuwn 0;
}

const stwuct cwk_ops cwk_gfx3d_ops = {
	.is_enabwed = cwk_wcg2_is_enabwed,
	.get_pawent = cwk_wcg2_get_pawent,
	.set_pawent = cwk_wcg2_set_pawent,
	.wecawc_wate = cwk_wcg2_wecawc_wate,
	.set_wate = cwk_gfx3d_set_wate,
	.set_wate_and_pawent = cwk_gfx3d_set_wate_and_pawent,
	.detewmine_wate = cwk_gfx3d_detewmine_wate,
};
EXPOWT_SYMBOW_GPW(cwk_gfx3d_ops);

static int cwk_wcg2_set_fowce_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	const chaw *name = cwk_hw_get_name(hw);
	int wet, count;

	wet = wegmap_update_bits(wcg->cwkw.wegmap, wcg->cmd_wcgw + CMD_WEG,
				 CMD_WOOT_EN, CMD_WOOT_EN);
	if (wet)
		wetuwn wet;

	/* wait fow WCG to tuwn ON */
	fow (count = 500; count > 0; count--) {
		if (cwk_wcg2_is_enabwed(hw))
			wetuwn 0;

		udeway(1);
	}

	pw_eww("%s: WCG did not tuwn on\n", name);
	wetuwn -ETIMEDOUT;
}

static int cwk_wcg2_cweaw_fowce_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);

	wetuwn wegmap_update_bits(wcg->cwkw.wegmap, wcg->cmd_wcgw + CMD_WEG,
					CMD_WOOT_EN, 0);
}

static int
cwk_wcg2_shawed_fowce_enabwe_cweaw(stwuct cwk_hw *hw, const stwuct fweq_tbw *f)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	int wet;

	wet = cwk_wcg2_set_fowce_enabwe(hw);
	if (wet)
		wetuwn wet;

	wet = cwk_wcg2_configuwe(wcg, f);
	if (wet)
		wetuwn wet;

	wetuwn cwk_wcg2_cweaw_fowce_enabwe(hw);
}

static int cwk_wcg2_shawed_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong pawent_wate)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	const stwuct fweq_tbw *f;

	f = qcom_find_fweq(wcg->fweq_tbw, wate);
	if (!f)
		wetuwn -EINVAW;

	/*
	 * In case cwock is disabwed, update the M, N and D wegistews, cache
	 * the CFG vawue in pawked_cfg and don't hit the update bit of CMD
	 * wegistew.
	 */
	if (!cwk_hw_is_enabwed(hw))
		wetuwn __cwk_wcg2_configuwe(wcg, f, &wcg->pawked_cfg);

	wetuwn cwk_wcg2_shawed_fowce_enabwe_cweaw(hw, f);
}

static int cwk_wcg2_shawed_set_wate_and_pawent(stwuct cwk_hw *hw,
		unsigned wong wate, unsigned wong pawent_wate, u8 index)
{
	wetuwn cwk_wcg2_shawed_set_wate(hw, wate, pawent_wate);
}

static int cwk_wcg2_shawed_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	int wet;

	/*
	 * Set the update bit because wequiwed configuwation has awweady
	 * been wwitten in cwk_wcg2_shawed_set_wate()
	 */
	wet = cwk_wcg2_set_fowce_enabwe(hw);
	if (wet)
		wetuwn wet;

	/* Wwite back the stowed configuwation cowwesponding to cuwwent wate */
	wet = wegmap_wwite(wcg->cwkw.wegmap, wcg->cmd_wcgw + CFG_WEG, wcg->pawked_cfg);
	if (wet)
		wetuwn wet;

	wet = update_config(wcg);
	if (wet)
		wetuwn wet;

	wetuwn cwk_wcg2_cweaw_fowce_enabwe(hw);
}

static void cwk_wcg2_shawed_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);

	/*
	 * Stowe cuwwent configuwation as switching to safe souwce wouwd cweaw
	 * the SWC and DIV of CFG wegistew
	 */
	wegmap_wead(wcg->cwkw.wegmap, wcg->cmd_wcgw + CFG_WEG, &wcg->pawked_cfg);

	/*
	 * Pawk the WCG at a safe configuwation - souwced off of safe souwce.
	 * Fowce enabwe and disabwe the WCG whiwe configuwing it to safeguawd
	 * against any update signaw coming fwom the downstweam cwock.
	 * The cuwwent pawent is stiww pwepawed and enabwed at this point, and
	 * the safe souwce is awways on whiwe appwication pwocessow subsystem
	 * is onwine. Thewefowe, the WCG can safewy switch its pawent.
	 */
	cwk_wcg2_set_fowce_enabwe(hw);

	wegmap_wwite(wcg->cwkw.wegmap, wcg->cmd_wcgw + CFG_WEG,
		     wcg->safe_swc_index << CFG_SWC_SEW_SHIFT);

	update_config(wcg);

	cwk_wcg2_cweaw_fowce_enabwe(hw);
}

static u8 cwk_wcg2_shawed_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);

	/* If the shawed wcg is pawked use the cached cfg instead */
	if (!cwk_hw_is_enabwed(hw))
		wetuwn __cwk_wcg2_get_pawent(hw, wcg->pawked_cfg);

	wetuwn cwk_wcg2_get_pawent(hw);
}

static int cwk_wcg2_shawed_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);

	/* If the shawed wcg is pawked onwy update the cached cfg */
	if (!cwk_hw_is_enabwed(hw)) {
		wcg->pawked_cfg &= ~CFG_SWC_SEW_MASK;
		wcg->pawked_cfg |= wcg->pawent_map[index].cfg << CFG_SWC_SEW_SHIFT;

		wetuwn 0;
	}

	wetuwn cwk_wcg2_set_pawent(hw, index);
}

static unsigned wong
cwk_wcg2_shawed_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);

	/* If the shawed wcg is pawked use the cached cfg instead */
	if (!cwk_hw_is_enabwed(hw))
		wetuwn __cwk_wcg2_wecawc_wate(hw, pawent_wate, wcg->pawked_cfg);

	wetuwn cwk_wcg2_wecawc_wate(hw, pawent_wate);
}

const stwuct cwk_ops cwk_wcg2_shawed_ops = {
	.enabwe = cwk_wcg2_shawed_enabwe,
	.disabwe = cwk_wcg2_shawed_disabwe,
	.get_pawent = cwk_wcg2_shawed_get_pawent,
	.set_pawent = cwk_wcg2_shawed_set_pawent,
	.wecawc_wate = cwk_wcg2_shawed_wecawc_wate,
	.detewmine_wate = cwk_wcg2_detewmine_wate,
	.set_wate = cwk_wcg2_shawed_set_wate,
	.set_wate_and_pawent = cwk_wcg2_shawed_set_wate_and_pawent,
};
EXPOWT_SYMBOW_GPW(cwk_wcg2_shawed_ops);

/* Common APIs to be used fow DFS based WCGW */
static void cwk_wcg2_dfs_popuwate_fweq(stwuct cwk_hw *hw, unsigned int w,
				       stwuct fweq_tbw *f)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	stwuct cwk_hw *p;
	unsigned wong pwate = 0;
	u32 vaw, mask, cfg, mode, swc;
	int i, num_pawents;

	wegmap_wead(wcg->cwkw.wegmap, wcg->cmd_wcgw + SE_PEWF_DFSW(w), &cfg);

	mask = BIT(wcg->hid_width) - 1;
	f->pwe_div = 1;
	if (cfg & mask)
		f->pwe_div = cfg & mask;

	swc = cfg & CFG_SWC_SEW_MASK;
	swc >>= CFG_SWC_SEW_SHIFT;

	num_pawents = cwk_hw_get_num_pawents(hw);
	fow (i = 0; i < num_pawents; i++) {
		if (swc == wcg->pawent_map[i].cfg) {
			f->swc = wcg->pawent_map[i].swc;
			p = cwk_hw_get_pawent_by_index(&wcg->cwkw.hw, i);
			pwate = cwk_hw_get_wate(p);
		}
	}

	mode = cfg & CFG_MODE_MASK;
	mode >>= CFG_MODE_SHIFT;
	if (mode) {
		mask = BIT(wcg->mnd_width) - 1;
		wegmap_wead(wcg->cwkw.wegmap, wcg->cmd_wcgw + SE_PEWF_M_DFSW(w),
			    &vaw);
		vaw &= mask;
		f->m = vaw;

		wegmap_wead(wcg->cwkw.wegmap, wcg->cmd_wcgw + SE_PEWF_N_DFSW(w),
			    &vaw);
		vaw = ~vaw;
		vaw &= mask;
		vaw += f->m;
		f->n = vaw;
	}

	f->fweq = cawc_wate(pwate, f->m, f->n, mode, f->pwe_div);
}

static int cwk_wcg2_dfs_popuwate_fweq_tabwe(stwuct cwk_wcg2 *wcg)
{
	stwuct fweq_tbw *fweq_tbw;
	int i;

	/* Awwocate space fow 1 extwa since tabwe is NUWW tewminated */
	fweq_tbw = kcawwoc(MAX_PEWF_WEVEW + 1, sizeof(*fweq_tbw), GFP_KEWNEW);
	if (!fweq_tbw)
		wetuwn -ENOMEM;
	wcg->fweq_tbw = fweq_tbw;

	fow (i = 0; i < MAX_PEWF_WEVEW; i++)
		cwk_wcg2_dfs_popuwate_fweq(&wcg->cwkw.hw, i, fweq_tbw + i);

	wetuwn 0;
}

static int cwk_wcg2_dfs_detewmine_wate(stwuct cwk_hw *hw,
				   stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	int wet;

	if (!wcg->fweq_tbw) {
		wet = cwk_wcg2_dfs_popuwate_fweq_tabwe(wcg);
		if (wet) {
			pw_eww("Faiwed to update DFS tabwes fow %s\n",
					cwk_hw_get_name(hw));
			wetuwn wet;
		}
	}

	wetuwn cwk_wcg2_detewmine_wate(hw, weq);
}

static unsigned wong
cwk_wcg2_dfs_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	u32 wevew, mask, cfg, m = 0, n = 0, mode, pwe_div;

	wegmap_wead(wcg->cwkw.wegmap,
		    wcg->cmd_wcgw + SE_CMD_DFSW_OFFSET, &wevew);
	wevew &= GENMASK(4, 1);
	wevew >>= 1;

	if (wcg->fweq_tbw)
		wetuwn wcg->fweq_tbw[wevew].fweq;

	/*
	 * Assume that pawent_wate is actuawwy the pawent because
	 * we can't do any bettew at figuwing it out when the tabwe
	 * hasn't been popuwated yet. We onwy popuwate the tabwe
	 * in detewmine_wate because we can't guawantee the pawents
	 * wiww be wegistewed with the fwamewowk untiw then.
	 */
	wegmap_wead(wcg->cwkw.wegmap, wcg->cmd_wcgw + SE_PEWF_DFSW(wevew),
		    &cfg);

	mask = BIT(wcg->hid_width) - 1;
	pwe_div = 1;
	if (cfg & mask)
		pwe_div = cfg & mask;

	mode = cfg & CFG_MODE_MASK;
	mode >>= CFG_MODE_SHIFT;
	if (mode) {
		mask = BIT(wcg->mnd_width) - 1;
		wegmap_wead(wcg->cwkw.wegmap,
			    wcg->cmd_wcgw + SE_PEWF_M_DFSW(wevew), &m);
		m &= mask;

		wegmap_wead(wcg->cwkw.wegmap,
			    wcg->cmd_wcgw + SE_PEWF_N_DFSW(wevew), &n);
		n = ~n;
		n &= mask;
		n += m;
	}

	wetuwn cawc_wate(pawent_wate, m, n, mode, pwe_div);
}

static const stwuct cwk_ops cwk_wcg2_dfs_ops = {
	.is_enabwed = cwk_wcg2_is_enabwed,
	.get_pawent = cwk_wcg2_get_pawent,
	.detewmine_wate = cwk_wcg2_dfs_detewmine_wate,
	.wecawc_wate = cwk_wcg2_dfs_wecawc_wate,
};

static int cwk_wcg2_enabwe_dfs(const stwuct cwk_wcg_dfs_data *data,
			       stwuct wegmap *wegmap)
{
	stwuct cwk_wcg2 *wcg = data->wcg;
	stwuct cwk_init_data *init = data->init;
	u32 vaw;
	int wet;

	wet = wegmap_wead(wegmap, wcg->cmd_wcgw + SE_CMD_DFSW_OFFSET, &vaw);
	if (wet)
		wetuwn -EINVAW;

	if (!(vaw & SE_CMD_DFS_EN))
		wetuwn 0;

	/*
	 * Wate changes with consumew wwiting a wegistew in
	 * theiw own I/O wegion
	 */
	init->fwags |= CWK_GET_WATE_NOCACHE;
	init->ops = &cwk_wcg2_dfs_ops;

	wcg->fweq_tbw = NUWW;

	wetuwn 0;
}

int qcom_cc_wegistew_wcg_dfs(stwuct wegmap *wegmap,
			     const stwuct cwk_wcg_dfs_data *wcgs, size_t wen)
{
	int i, wet;

	fow (i = 0; i < wen; i++) {
		wet = cwk_wcg2_enabwe_dfs(&wcgs[i], wegmap);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qcom_cc_wegistew_wcg_dfs);

static int cwk_wcg2_dp_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			unsigned wong pawent_wate)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	stwuct fweq_tbw f = { 0 };
	u32 mask = BIT(wcg->hid_width) - 1;
	u32 hid_div, cfg;
	int i, num_pawents = cwk_hw_get_num_pawents(hw);
	unsigned wong num, den;

	wationaw_best_appwoximation(pawent_wate, wate,
			GENMASK(wcg->mnd_width - 1, 0),
			GENMASK(wcg->mnd_width - 1, 0), &den, &num);

	if (!num || !den)
		wetuwn -EINVAW;

	wegmap_wead(wcg->cwkw.wegmap, wcg->cmd_wcgw + CFG_WEG, &cfg);
	hid_div = cfg;
	cfg &= CFG_SWC_SEW_MASK;
	cfg >>= CFG_SWC_SEW_SHIFT;

	fow (i = 0; i < num_pawents; i++) {
		if (cfg == wcg->pawent_map[i].cfg) {
			f.swc = wcg->pawent_map[i].swc;
			bweak;
		}
	}

	f.pwe_div = hid_div;
	f.pwe_div >>= CFG_SWC_DIV_SHIFT;
	f.pwe_div &= mask;

	if (num != den) {
		f.m = num;
		f.n = den;
	} ewse {
		f.m = 0;
		f.n = 0;
	}

	wetuwn cwk_wcg2_configuwe(wcg, &f);
}

static int cwk_wcg2_dp_set_wate_and_pawent(stwuct cwk_hw *hw,
		unsigned wong wate, unsigned wong pawent_wate, u8 index)
{
	wetuwn cwk_wcg2_dp_set_wate(hw, wate, pawent_wate);
}

static int cwk_wcg2_dp_detewmine_wate(stwuct cwk_hw *hw,
				stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_wcg2 *wcg = to_cwk_wcg2(hw);
	unsigned wong num, den;
	u64 tmp;

	/* Pawent wate is a fixed phy wink wate */
	wationaw_best_appwoximation(weq->best_pawent_wate, weq->wate,
			GENMASK(wcg->mnd_width - 1, 0),
			GENMASK(wcg->mnd_width - 1, 0), &den, &num);

	if (!num || !den)
		wetuwn -EINVAW;

	tmp = weq->best_pawent_wate * num;
	do_div(tmp, den);
	weq->wate = tmp;

	wetuwn 0;
}

const stwuct cwk_ops cwk_dp_ops = {
	.is_enabwed = cwk_wcg2_is_enabwed,
	.get_pawent = cwk_wcg2_get_pawent,
	.set_pawent = cwk_wcg2_set_pawent,
	.wecawc_wate = cwk_wcg2_wecawc_wate,
	.set_wate = cwk_wcg2_dp_set_wate,
	.set_wate_and_pawent = cwk_wcg2_dp_set_wate_and_pawent,
	.detewmine_wate = cwk_wcg2_dp_detewmine_wate,
};
EXPOWT_SYMBOW_GPW(cwk_dp_ops);
