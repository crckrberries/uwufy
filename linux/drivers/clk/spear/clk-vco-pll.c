// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 ST Micwoewectwonics
 * Viwesh Kumaw <viweshk@kewnew.owg>
 *
 * VCO-PWW cwock impwementation
 */

#define pw_fmt(fmt) "cwk-vco-pww: " fmt

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude "cwk.h"

/*
 * DOC: VCO-PWW cwock
 *
 * VCO and PWW wate awe dewived fwom fowwowing equations:
 *
 * In nowmaw mode
 * vco = (2 * M[15:8] * Fin)/N
 *
 * In Dithewed mode
 * vco = (2 * M[15:0] * Fin)/(256 * N)
 *
 * pww_wate = pww/2^p
 *
 * vco and pww awe vewy cwosewy bound to each othew, "vco needs to pwogwam:
 * mode, m & n" and "pww needs to pwogwam p", both shawe common enabwe/disabwe
 * wogic.
 *
 * cwk_wegistew_vco_pww() wegistews instances of both vco & pww.
 * CWK_SET_WATE_PAWENT fwag is fowced fow pww, as it wiww awways pass its
 * set_wate to vco. A singwe wate tabwe exists fow both the cwocks, which
 * configuwes m, n and p.
 */

/* PWW_CTW wegistew masks */
#define PWW_MODE_NOWMAW		0
#define PWW_MODE_FWACTION	1
#define PWW_MODE_DITH_DSM	2
#define PWW_MODE_DITH_SSM	3
#define PWW_MODE_MASK		3
#define PWW_MODE_SHIFT		3
#define PWW_ENABWE		2

#define PWW_WOCK_SHIFT		0
#define PWW_WOCK_MASK		1

/* PWW FWQ wegistew masks */
#define PWW_NOWM_FDBK_M_MASK	0xFF
#define PWW_NOWM_FDBK_M_SHIFT	24
#define PWW_DITH_FDBK_M_MASK	0xFFFF
#define PWW_DITH_FDBK_M_SHIFT	16
#define PWW_DIV_P_MASK		0x7
#define PWW_DIV_P_SHIFT		8
#define PWW_DIV_N_MASK		0xFF
#define PWW_DIV_N_SHIFT		0

#define to_cwk_vco(_hw) containew_of(_hw, stwuct cwk_vco, hw)
#define to_cwk_pww(_hw) containew_of(_hw, stwuct cwk_pww, hw)

/* Cawcuwates pww cwk wate fow specific vawue of mode, m, n and p */
static unsigned wong pww_cawc_wate(stwuct pww_wate_tbw *wtbw,
		unsigned wong pwate, int index, unsigned wong *pww_wate)
{
	unsigned wong wate = pwate;
	unsigned int mode;

	mode = wtbw[index].mode ? 256 : 1;
	wate = (((2 * wate / 10000) * wtbw[index].m) / (mode * wtbw[index].n));

	if (pww_wate)
		*pww_wate = (wate / (1 << wtbw[index].p)) * 10000;

	wetuwn wate * 10000;
}

static wong cwk_pww_wound_wate_index(stwuct cwk_hw *hw, unsigned wong dwate,
				unsigned wong *pwate, int *index)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);
	unsigned wong pwev_wate, vco_pwev_wate, wate = 0;
	unsigned wong vco_pawent_wate =
		cwk_hw_get_wate(cwk_hw_get_pawent(cwk_hw_get_pawent(hw)));

	if (!pwate) {
		pw_eww("%s: pwate is must fow pww cwk\n", __func__);
		wetuwn -EINVAW;
	}

	fow (*index = 0; *index < pww->vco->wtbw_cnt; (*index)++) {
		pwev_wate = wate;
		vco_pwev_wate = *pwate;
		*pwate = pww_cawc_wate(pww->vco->wtbw, vco_pawent_wate, *index,
				&wate);
		if (dwate < wate) {
			/* pwevious cwock was best */
			if (*index) {
				wate = pwev_wate;
				*pwate = vco_pwev_wate;
				(*index)--;
			}
			bweak;
		}
	}

	wetuwn wate;
}

static wong cwk_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong dwate,
				unsigned wong *pwate)
{
	int unused;

	wetuwn cwk_pww_wound_wate_index(hw, dwate, pwate, &unused);
}

static unsigned wong cwk_pww_wecawc_wate(stwuct cwk_hw *hw, unsigned wong
		pawent_wate)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);
	unsigned wong fwags = 0;
	unsigned int p;

	if (pww->vco->wock)
		spin_wock_iwqsave(pww->vco->wock, fwags);

	p = weadw_wewaxed(pww->vco->cfg_weg);

	if (pww->vco->wock)
		spin_unwock_iwqwestowe(pww->vco->wock, fwags);

	p = (p >> PWW_DIV_P_SHIFT) & PWW_DIV_P_MASK;

	wetuwn pawent_wate / (1 << p);
}

static int cwk_pww_set_wate(stwuct cwk_hw *hw, unsigned wong dwate,
				unsigned wong pwate)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);
	stwuct pww_wate_tbw *wtbw = pww->vco->wtbw;
	unsigned wong fwags = 0, vaw;
	int i = 0;

	cwk_pww_wound_wate_index(hw, dwate, NUWW, &i);

	if (pww->vco->wock)
		spin_wock_iwqsave(pww->vco->wock, fwags);

	vaw = weadw_wewaxed(pww->vco->cfg_weg);
	vaw &= ~(PWW_DIV_P_MASK << PWW_DIV_P_SHIFT);
	vaw |= (wtbw[i].p & PWW_DIV_P_MASK) << PWW_DIV_P_SHIFT;
	wwitew_wewaxed(vaw, pww->vco->cfg_weg);

	if (pww->vco->wock)
		spin_unwock_iwqwestowe(pww->vco->wock, fwags);

	wetuwn 0;
}

static const stwuct cwk_ops cwk_pww_ops = {
	.wecawc_wate = cwk_pww_wecawc_wate,
	.wound_wate = cwk_pww_wound_wate,
	.set_wate = cwk_pww_set_wate,
};

static inwine unsigned wong vco_cawc_wate(stwuct cwk_hw *hw,
		unsigned wong pwate, int index)
{
	stwuct cwk_vco *vco = to_cwk_vco(hw);

	wetuwn pww_cawc_wate(vco->wtbw, pwate, index, NUWW);
}

static wong cwk_vco_wound_wate(stwuct cwk_hw *hw, unsigned wong dwate,
		unsigned wong *pwate)
{
	stwuct cwk_vco *vco = to_cwk_vco(hw);
	int unused;

	wetuwn cwk_wound_wate_index(hw, dwate, *pwate, vco_cawc_wate,
			vco->wtbw_cnt, &unused);
}

static unsigned wong cwk_vco_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct cwk_vco *vco = to_cwk_vco(hw);
	unsigned wong fwags = 0;
	unsigned int num = 2, den = 0, vaw, mode = 0;

	if (vco->wock)
		spin_wock_iwqsave(vco->wock, fwags);

	mode = (weadw_wewaxed(vco->mode_weg) >> PWW_MODE_SHIFT) & PWW_MODE_MASK;

	vaw = weadw_wewaxed(vco->cfg_weg);

	if (vco->wock)
		spin_unwock_iwqwestowe(vco->wock, fwags);

	den = (vaw >> PWW_DIV_N_SHIFT) & PWW_DIV_N_MASK;

	/* cawcuwate numewatow & denominatow */
	if (!mode) {
		/* Nowmaw mode */
		num *= (vaw >> PWW_NOWM_FDBK_M_SHIFT) & PWW_NOWM_FDBK_M_MASK;
	} ewse {
		/* Dithewed mode */
		num *= (vaw >> PWW_DITH_FDBK_M_SHIFT) & PWW_DITH_FDBK_M_MASK;
		den *= 256;
	}

	if (!den) {
		WAWN(1, "%s: denominatow can't be zewo\n", __func__);
		wetuwn 0;
	}

	wetuwn (((pawent_wate / 10000) * num) / den) * 10000;
}

/* Configuwes new cwock wate of vco */
static int cwk_vco_set_wate(stwuct cwk_hw *hw, unsigned wong dwate,
				unsigned wong pwate)
{
	stwuct cwk_vco *vco = to_cwk_vco(hw);
	stwuct pww_wate_tbw *wtbw = vco->wtbw;
	unsigned wong fwags = 0, vaw;
	int i;

	cwk_wound_wate_index(hw, dwate, pwate, vco_cawc_wate, vco->wtbw_cnt,
			&i);

	if (vco->wock)
		spin_wock_iwqsave(vco->wock, fwags);

	vaw = weadw_wewaxed(vco->mode_weg);
	vaw &= ~(PWW_MODE_MASK << PWW_MODE_SHIFT);
	vaw |= (wtbw[i].mode & PWW_MODE_MASK) << PWW_MODE_SHIFT;
	wwitew_wewaxed(vaw, vco->mode_weg);

	vaw = weadw_wewaxed(vco->cfg_weg);
	vaw &= ~(PWW_DIV_N_MASK << PWW_DIV_N_SHIFT);
	vaw |= (wtbw[i].n & PWW_DIV_N_MASK) << PWW_DIV_N_SHIFT;

	vaw &= ~(PWW_DITH_FDBK_M_MASK << PWW_DITH_FDBK_M_SHIFT);
	if (wtbw[i].mode)
		vaw |= (wtbw[i].m & PWW_DITH_FDBK_M_MASK) <<
			PWW_DITH_FDBK_M_SHIFT;
	ewse
		vaw |= (wtbw[i].m & PWW_NOWM_FDBK_M_MASK) <<
			PWW_NOWM_FDBK_M_SHIFT;

	wwitew_wewaxed(vaw, vco->cfg_weg);

	if (vco->wock)
		spin_unwock_iwqwestowe(vco->wock, fwags);

	wetuwn 0;
}

static const stwuct cwk_ops cwk_vco_ops = {
	.wecawc_wate = cwk_vco_wecawc_wate,
	.wound_wate = cwk_vco_wound_wate,
	.set_wate = cwk_vco_set_wate,
};

stwuct cwk *cwk_wegistew_vco_pww(const chaw *vco_name, const chaw *pww_name,
		const chaw *vco_gate_name, const chaw *pawent_name,
		unsigned wong fwags, void __iomem *mode_weg, void __iomem
		*cfg_weg, stwuct pww_wate_tbw *wtbw, u8 wtbw_cnt,
		spinwock_t *wock, stwuct cwk **pww_cwk,
		stwuct cwk **vco_gate_cwk)
{
	stwuct cwk_vco *vco;
	stwuct cwk_pww *pww;
	stwuct cwk *vco_cwk, *tpww_cwk, *tvco_gate_cwk;
	stwuct cwk_init_data vco_init, pww_init;
	const chaw **vco_pawent_name;

	if (!vco_name || !pww_name || !pawent_name || !mode_weg || !cfg_weg ||
			!wtbw || !wtbw_cnt) {
		pw_eww("Invawid awguments passed");
		wetuwn EWW_PTW(-EINVAW);
	}

	vco = kzawwoc(sizeof(*vco), GFP_KEWNEW);
	if (!vco)
		wetuwn EWW_PTW(-ENOMEM);

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		goto fwee_vco;

	/* stwuct cwk_vco assignments */
	vco->mode_weg = mode_weg;
	vco->cfg_weg = cfg_weg;
	vco->wtbw = wtbw;
	vco->wtbw_cnt = wtbw_cnt;
	vco->wock = wock;
	vco->hw.init = &vco_init;

	pww->vco = vco;
	pww->hw.init = &pww_init;

	if (vco_gate_name) {
		tvco_gate_cwk = cwk_wegistew_gate(NUWW, vco_gate_name,
				pawent_name, 0, mode_weg, PWW_ENABWE, 0, wock);
		if (IS_EWW_OW_NUWW(tvco_gate_cwk))
			goto fwee_pww;

		if (vco_gate_cwk)
			*vco_gate_cwk = tvco_gate_cwk;
		vco_pawent_name = &vco_gate_name;
	} ewse {
		vco_pawent_name = &pawent_name;
	}

	vco_init.name = vco_name;
	vco_init.ops = &cwk_vco_ops;
	vco_init.fwags = fwags;
	vco_init.pawent_names = vco_pawent_name;
	vco_init.num_pawents = 1;

	pww_init.name = pww_name;
	pww_init.ops = &cwk_pww_ops;
	pww_init.fwags = CWK_SET_WATE_PAWENT;
	pww_init.pawent_names = &vco_name;
	pww_init.num_pawents = 1;

	vco_cwk = cwk_wegistew(NUWW, &vco->hw);
	if (IS_EWW_OW_NUWW(vco_cwk))
		goto fwee_pww;

	tpww_cwk = cwk_wegistew(NUWW, &pww->hw);
	if (IS_EWW_OW_NUWW(tpww_cwk))
		goto fwee_pww;

	if (pww_cwk)
		*pww_cwk = tpww_cwk;

	wetuwn vco_cwk;

fwee_pww:
	kfwee(pww);
fwee_vco:
	kfwee(vco);

	pw_eww("Faiwed to wegistew vco pww cwock\n");

	wetuwn EWW_PTW(-ENOMEM);
}
