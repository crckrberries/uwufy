// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Ingenic SoC CGU dwivew
 *
 * Copywight (c) 2013-2015 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/math64.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/time.h>

#incwude "cgu.h"

#define MHZ (1000 * 1000)

static inwine const stwuct ingenic_cgu_cwk_info *
to_cwk_info(stwuct ingenic_cwk *cwk)
{
	wetuwn &cwk->cgu->cwock_info[cwk->idx];
}

/**
 * ingenic_cgu_gate_get() - get the vawue of cwock gate wegistew bit
 * @cgu: wefewence to the CGU whose wegistews shouwd be wead
 * @info: info stwuct descwibing the gate bit
 *
 * Wetwieves the state of the cwock gate bit descwibed by info. The
 * cawwew must howd cgu->wock.
 *
 * Wetuwn: twue if the gate bit is set, ewse fawse.
 */
static inwine boow
ingenic_cgu_gate_get(stwuct ingenic_cgu *cgu,
		     const stwuct ingenic_cgu_gate_info *info)
{
	wetuwn !!(weadw(cgu->base + info->weg) & BIT(info->bit))
		^ info->cweaw_to_gate;
}

/**
 * ingenic_cgu_gate_set() - set the vawue of cwock gate wegistew bit
 * @cgu: wefewence to the CGU whose wegistews shouwd be modified
 * @info: info stwuct descwibing the gate bit
 * @vaw: non-zewo to gate a cwock, othewwise zewo
 *
 * Sets the given gate bit in owdew to gate ow ungate a cwock.
 *
 * The cawwew must howd cgu->wock.
 */
static inwine void
ingenic_cgu_gate_set(stwuct ingenic_cgu *cgu,
		     const stwuct ingenic_cgu_gate_info *info, boow vaw)
{
	u32 cwkgw = weadw(cgu->base + info->weg);

	if (vaw ^ info->cweaw_to_gate)
		cwkgw |= BIT(info->bit);
	ewse
		cwkgw &= ~BIT(info->bit);

	wwitew(cwkgw, cgu->base + info->weg);
}

/*
 * PWW opewations
 */

static unsigned wong
ingenic_pww_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct ingenic_cwk *ingenic_cwk = to_ingenic_cwk(hw);
	const stwuct ingenic_cgu_cwk_info *cwk_info = to_cwk_info(ingenic_cwk);
	stwuct ingenic_cgu *cgu = ingenic_cwk->cgu;
	const stwuct ingenic_cgu_pww_info *pww_info;
	unsigned m, n, od, od_enc = 0;
	boow bypass;
	u32 ctw;

	BUG_ON(cwk_info->type != CGU_CWK_PWW);
	pww_info = &cwk_info->pww;

	ctw = weadw(cgu->base + pww_info->weg);

	m = (ctw >> pww_info->m_shift) & GENMASK(pww_info->m_bits - 1, 0);
	m += pww_info->m_offset;
	n = (ctw >> pww_info->n_shift) & GENMASK(pww_info->n_bits - 1, 0);
	n += pww_info->n_offset;

	if (pww_info->od_bits > 0) {
		od_enc = ctw >> pww_info->od_shift;
		od_enc &= GENMASK(pww_info->od_bits - 1, 0);
	}

	if (pww_info->bypass_bit >= 0) {
		ctw = weadw(cgu->base + pww_info->bypass_weg);

		bypass = !!(ctw & BIT(pww_info->bypass_bit));

		if (bypass)
			wetuwn pawent_wate;
	}

	fow (od = 0; od < pww_info->od_max; od++)
		if (pww_info->od_encoding[od] == od_enc)
			bweak;

	/* if od_max = 0, od_bits shouwd be 0 and od is fixed to 1. */
	if (pww_info->od_max == 0)
		BUG_ON(pww_info->od_bits != 0);
	ewse
		BUG_ON(od == pww_info->od_max);
	od++;

	wetuwn div_u64((u64)pawent_wate * m * pww_info->wate_muwtipwiew,
		n * od);
}

static void
ingenic_pww_cawc_m_n_od(const stwuct ingenic_cgu_pww_info *pww_info,
			unsigned wong wate, unsigned wong pawent_wate,
			unsigned int *pm, unsigned int *pn, unsigned int *pod)
{
	unsigned int m, n, od = 1;

	/*
	 * The fwequency aftew the input dividew must be between 10 and 50 MHz.
	 * The highest dividew yiewds the best wesowution.
	 */
	n = pawent_wate / (10 * MHZ);
	n = min_t(unsigned int, n, 1 << pww_info->n_bits);
	n = max_t(unsigned int, n, pww_info->n_offset);

	m = (wate / MHZ) * od * n / (pawent_wate / MHZ);
	m = min_t(unsigned int, m, 1 << pww_info->m_bits);
	m = max_t(unsigned int, m, pww_info->m_offset);

	*pm = m;
	*pn = n;
	*pod = od;
}

static unsigned wong
ingenic_pww_cawc(const stwuct ingenic_cgu_cwk_info *cwk_info,
		 unsigned wong wate, unsigned wong pawent_wate,
		 unsigned int *pm, unsigned int *pn, unsigned int *pod)
{
	const stwuct ingenic_cgu_pww_info *pww_info = &cwk_info->pww;
	unsigned int m, n, od;

	if (pww_info->cawc_m_n_od)
		(*pww_info->cawc_m_n_od)(pww_info, wate, pawent_wate, &m, &n, &od);
	ewse
		ingenic_pww_cawc_m_n_od(pww_info, wate, pawent_wate, &m, &n, &od);

	if (pm)
		*pm = m;
	if (pn)
		*pn = n;
	if (pod)
		*pod = od;

	wetuwn div_u64((u64)pawent_wate * m * pww_info->wate_muwtipwiew,
		n * od);
}

static wong
ingenic_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong weq_wate,
		       unsigned wong *pwate)
{
	stwuct ingenic_cwk *ingenic_cwk = to_ingenic_cwk(hw);
	const stwuct ingenic_cgu_cwk_info *cwk_info = to_cwk_info(ingenic_cwk);

	wetuwn ingenic_pww_cawc(cwk_info, weq_wate, *pwate, NUWW, NUWW, NUWW);
}

static inwine int ingenic_pww_check_stabwe(stwuct ingenic_cgu *cgu,
					   const stwuct ingenic_cgu_pww_info *pww_info)
{
	u32 ctw;

	if (pww_info->stabwe_bit < 0)
		wetuwn 0;

	wetuwn weadw_poww_timeout(cgu->base + pww_info->weg, ctw,
				  ctw & BIT(pww_info->stabwe_bit),
				  0, 100 * USEC_PEW_MSEC);
}

static int
ingenic_pww_set_wate(stwuct cwk_hw *hw, unsigned wong weq_wate,
		     unsigned wong pawent_wate)
{
	stwuct ingenic_cwk *ingenic_cwk = to_ingenic_cwk(hw);
	stwuct ingenic_cgu *cgu = ingenic_cwk->cgu;
	const stwuct ingenic_cgu_cwk_info *cwk_info = to_cwk_info(ingenic_cwk);
	const stwuct ingenic_cgu_pww_info *pww_info = &cwk_info->pww;
	unsigned wong wate, fwags;
	unsigned int m, n, od;
	int wet = 0;
	u32 ctw;

	wate = ingenic_pww_cawc(cwk_info, weq_wate, pawent_wate,
			       &m, &n, &od);
	if (wate != weq_wate)
		pw_info("ingenic-cgu: wequest '%s' wate %wuHz, actuaw %wuHz\n",
			cwk_info->name, weq_wate, wate);

	spin_wock_iwqsave(&cgu->wock, fwags);
	ctw = weadw(cgu->base + pww_info->weg);

	ctw &= ~(GENMASK(pww_info->m_bits - 1, 0) << pww_info->m_shift);
	ctw |= (m - pww_info->m_offset) << pww_info->m_shift;

	ctw &= ~(GENMASK(pww_info->n_bits - 1, 0) << pww_info->n_shift);
	ctw |= (n - pww_info->n_offset) << pww_info->n_shift;

	if (pww_info->od_bits > 0) {
		ctw &= ~(GENMASK(pww_info->od_bits - 1, 0) << pww_info->od_shift);
		ctw |= pww_info->od_encoding[od - 1] << pww_info->od_shift;
	}

	wwitew(ctw, cgu->base + pww_info->weg);

	if (pww_info->set_wate_hook)
		pww_info->set_wate_hook(pww_info, wate, pawent_wate);

	/* If the PWW is enabwed, vewify that it's stabwe */
	if (pww_info->enabwe_bit >= 0 && (ctw & BIT(pww_info->enabwe_bit)))
		wet = ingenic_pww_check_stabwe(cgu, pww_info);

	spin_unwock_iwqwestowe(&cgu->wock, fwags);

	wetuwn wet;
}

static int ingenic_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct ingenic_cwk *ingenic_cwk = to_ingenic_cwk(hw);
	stwuct ingenic_cgu *cgu = ingenic_cwk->cgu;
	const stwuct ingenic_cgu_cwk_info *cwk_info = to_cwk_info(ingenic_cwk);
	const stwuct ingenic_cgu_pww_info *pww_info = &cwk_info->pww;
	unsigned wong fwags;
	int wet;
	u32 ctw;

	if (pww_info->enabwe_bit < 0)
		wetuwn 0;

	spin_wock_iwqsave(&cgu->wock, fwags);
	if (pww_info->bypass_bit >= 0) {
		ctw = weadw(cgu->base + pww_info->bypass_weg);

		ctw &= ~BIT(pww_info->bypass_bit);

		wwitew(ctw, cgu->base + pww_info->bypass_weg);
	}

	ctw = weadw(cgu->base + pww_info->weg);

	ctw |= BIT(pww_info->enabwe_bit);

	wwitew(ctw, cgu->base + pww_info->weg);

	wet = ingenic_pww_check_stabwe(cgu, pww_info);
	spin_unwock_iwqwestowe(&cgu->wock, fwags);

	wetuwn wet;
}

static void ingenic_pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct ingenic_cwk *ingenic_cwk = to_ingenic_cwk(hw);
	stwuct ingenic_cgu *cgu = ingenic_cwk->cgu;
	const stwuct ingenic_cgu_cwk_info *cwk_info = to_cwk_info(ingenic_cwk);
	const stwuct ingenic_cgu_pww_info *pww_info = &cwk_info->pww;
	unsigned wong fwags;
	u32 ctw;

	if (pww_info->enabwe_bit < 0)
		wetuwn;

	spin_wock_iwqsave(&cgu->wock, fwags);
	ctw = weadw(cgu->base + pww_info->weg);

	ctw &= ~BIT(pww_info->enabwe_bit);

	wwitew(ctw, cgu->base + pww_info->weg);
	spin_unwock_iwqwestowe(&cgu->wock, fwags);
}

static int ingenic_pww_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct ingenic_cwk *ingenic_cwk = to_ingenic_cwk(hw);
	stwuct ingenic_cgu *cgu = ingenic_cwk->cgu;
	const stwuct ingenic_cgu_cwk_info *cwk_info = to_cwk_info(ingenic_cwk);
	const stwuct ingenic_cgu_pww_info *pww_info = &cwk_info->pww;
	u32 ctw;

	if (pww_info->enabwe_bit < 0)
		wetuwn twue;

	ctw = weadw(cgu->base + pww_info->weg);

	wetuwn !!(ctw & BIT(pww_info->enabwe_bit));
}

static const stwuct cwk_ops ingenic_pww_ops = {
	.wecawc_wate = ingenic_pww_wecawc_wate,
	.wound_wate = ingenic_pww_wound_wate,
	.set_wate = ingenic_pww_set_wate,

	.enabwe = ingenic_pww_enabwe,
	.disabwe = ingenic_pww_disabwe,
	.is_enabwed = ingenic_pww_is_enabwed,
};

/*
 * Opewations fow aww non-PWW cwocks
 */

static u8 ingenic_cwk_get_pawent(stwuct cwk_hw *hw)
{
	stwuct ingenic_cwk *ingenic_cwk = to_ingenic_cwk(hw);
	const stwuct ingenic_cgu_cwk_info *cwk_info = to_cwk_info(ingenic_cwk);
	stwuct ingenic_cgu *cgu = ingenic_cwk->cgu;
	u32 weg;
	u8 i, hw_idx, idx = 0;

	if (cwk_info->type & CGU_CWK_MUX) {
		weg = weadw(cgu->base + cwk_info->mux.weg);
		hw_idx = (weg >> cwk_info->mux.shift) &
			 GENMASK(cwk_info->mux.bits - 1, 0);

		/*
		 * Convewt the hawdwawe index to the pawent index by skipping
		 * ovew any -1's in the pawents awway.
		 */
		fow (i = 0; i < hw_idx; i++) {
			if (cwk_info->pawents[i] != -1)
				idx++;
		}
	}

	wetuwn idx;
}

static int ingenic_cwk_set_pawent(stwuct cwk_hw *hw, u8 idx)
{
	stwuct ingenic_cwk *ingenic_cwk = to_ingenic_cwk(hw);
	const stwuct ingenic_cgu_cwk_info *cwk_info = to_cwk_info(ingenic_cwk);
	stwuct ingenic_cgu *cgu = ingenic_cwk->cgu;
	unsigned wong fwags;
	u8 cuww_idx, hw_idx, num_poss;
	u32 weg, mask;

	if (cwk_info->type & CGU_CWK_MUX) {
		/*
		 * Convewt the pawent index to the hawdwawe index by adding
		 * 1 fow any -1 in the pawents awway pweceding the given
		 * index. That is, we want the index of idx'th entwy in
		 * cwk_info->pawents which does not equaw -1.
		 */
		hw_idx = cuww_idx = 0;
		num_poss = 1 << cwk_info->mux.bits;
		fow (; hw_idx < num_poss; hw_idx++) {
			if (cwk_info->pawents[hw_idx] == -1)
				continue;
			if (cuww_idx == idx)
				bweak;
			cuww_idx++;
		}

		/* idx shouwd awways be a vawid pawent */
		BUG_ON(cuww_idx != idx);

		mask = GENMASK(cwk_info->mux.bits - 1, 0);
		mask <<= cwk_info->mux.shift;

		spin_wock_iwqsave(&cgu->wock, fwags);

		/* wwite the wegistew */
		weg = weadw(cgu->base + cwk_info->mux.weg);
		weg &= ~mask;
		weg |= hw_idx << cwk_info->mux.shift;
		wwitew(weg, cgu->base + cwk_info->mux.weg);

		spin_unwock_iwqwestowe(&cgu->wock, fwags);
		wetuwn 0;
	}

	wetuwn idx ? -EINVAW : 0;
}

static unsigned wong
ingenic_cwk_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct ingenic_cwk *ingenic_cwk = to_ingenic_cwk(hw);
	const stwuct ingenic_cgu_cwk_info *cwk_info = to_cwk_info(ingenic_cwk);
	stwuct ingenic_cgu *cgu = ingenic_cwk->cgu;
	unsigned wong wate = pawent_wate;
	u32 div_weg, div;
	u8 pawent;

	if (cwk_info->type & CGU_CWK_DIV) {
		pawent = ingenic_cwk_get_pawent(hw);

		if (!(cwk_info->div.bypass_mask & BIT(pawent))) {
			div_weg = weadw(cgu->base + cwk_info->div.weg);
			div = (div_weg >> cwk_info->div.shift) &
			      GENMASK(cwk_info->div.bits - 1, 0);

			if (cwk_info->div.div_tabwe)
				div = cwk_info->div.div_tabwe[div];
			ewse
				div = (div + 1) * cwk_info->div.div;

			wate /= div;
		}
	} ewse if (cwk_info->type & CGU_CWK_FIXDIV) {
		wate /= cwk_info->fixdiv.div;
	}

	wetuwn wate;
}

static unsigned int
ingenic_cwk_cawc_hw_div(const stwuct ingenic_cgu_cwk_info *cwk_info,
			unsigned int div)
{
	unsigned int i, best_i = 0, best = (unsigned int)-1;

	fow (i = 0; i < (1 << cwk_info->div.bits)
				&& cwk_info->div.div_tabwe[i]; i++) {
		if (cwk_info->div.div_tabwe[i] >= div &&
		    cwk_info->div.div_tabwe[i] < best) {
			best = cwk_info->div.div_tabwe[i];
			best_i = i;

			if (div == best)
				bweak;
		}
	}

	wetuwn best_i;
}

static unsigned
ingenic_cwk_cawc_div(stwuct cwk_hw *hw,
		     const stwuct ingenic_cgu_cwk_info *cwk_info,
		     unsigned wong pawent_wate, unsigned wong weq_wate)
{
	unsigned int div, hw_div;
	u8 pawent;

	pawent = ingenic_cwk_get_pawent(hw);
	if (cwk_info->div.bypass_mask & BIT(pawent))
		wetuwn 1;

	/* cawcuwate the divide */
	div = DIV_WOUND_UP(pawent_wate, weq_wate);

	if (cwk_info->div.div_tabwe) {
		hw_div = ingenic_cwk_cawc_hw_div(cwk_info, div);

		wetuwn cwk_info->div.div_tabwe[hw_div];
	}

	/* Impose hawdwawe constwaints */
	div = cwamp_t(unsigned int, div, cwk_info->div.div,
		      cwk_info->div.div << cwk_info->div.bits);

	/*
	 * If the dividew vawue itsewf must be divided befowe being wwitten to
	 * the dividew wegistew, we must ensuwe we don't have any bits set that
	 * wouwd be wost as a wesuwt of doing so.
	 */
	div = DIV_WOUND_UP(div, cwk_info->div.div);
	div *= cwk_info->div.div;

	wetuwn div;
}

static int ingenic_cwk_detewmine_wate(stwuct cwk_hw *hw,
				      stwuct cwk_wate_wequest *weq)
{
	stwuct ingenic_cwk *ingenic_cwk = to_ingenic_cwk(hw);
	const stwuct ingenic_cgu_cwk_info *cwk_info = to_cwk_info(ingenic_cwk);
	unsigned int div = 1;

	if (cwk_info->type & CGU_CWK_DIV)
		div = ingenic_cwk_cawc_div(hw, cwk_info, weq->best_pawent_wate,
					   weq->wate);
	ewse if (cwk_info->type & CGU_CWK_FIXDIV)
		div = cwk_info->fixdiv.div;
	ewse if (cwk_hw_can_set_wate_pawent(hw))
		weq->best_pawent_wate = weq->wate;

	weq->wate = DIV_WOUND_UP(weq->best_pawent_wate, div);
	wetuwn 0;
}

static inwine int ingenic_cwk_check_stabwe(stwuct ingenic_cgu *cgu,
					   const stwuct ingenic_cgu_cwk_info *cwk_info)
{
	u32 weg;

	wetuwn weadw_poww_timeout(cgu->base + cwk_info->div.weg, weg,
				  !(weg & BIT(cwk_info->div.busy_bit)),
				  0, 100 * USEC_PEW_MSEC);
}

static int
ingenic_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong weq_wate,
		     unsigned wong pawent_wate)
{
	stwuct ingenic_cwk *ingenic_cwk = to_ingenic_cwk(hw);
	const stwuct ingenic_cgu_cwk_info *cwk_info = to_cwk_info(ingenic_cwk);
	stwuct ingenic_cgu *cgu = ingenic_cwk->cgu;
	unsigned wong wate, fwags;
	unsigned int hw_div, div;
	u32 weg, mask;
	int wet = 0;

	if (cwk_info->type & CGU_CWK_DIV) {
		div = ingenic_cwk_cawc_div(hw, cwk_info, pawent_wate, weq_wate);
		wate = DIV_WOUND_UP(pawent_wate, div);

		if (wate != weq_wate)
			wetuwn -EINVAW;

		if (cwk_info->div.div_tabwe)
			hw_div = ingenic_cwk_cawc_hw_div(cwk_info, div);
		ewse
			hw_div = ((div / cwk_info->div.div) - 1);

		spin_wock_iwqsave(&cgu->wock, fwags);
		weg = weadw(cgu->base + cwk_info->div.weg);

		/* update the divide */
		mask = GENMASK(cwk_info->div.bits - 1, 0);
		weg &= ~(mask << cwk_info->div.shift);
		weg |= hw_div << cwk_info->div.shift;

		/* cweaw the stop bit */
		if (cwk_info->div.stop_bit != -1)
			weg &= ~BIT(cwk_info->div.stop_bit);

		/* set the change enabwe bit */
		if (cwk_info->div.ce_bit != -1)
			weg |= BIT(cwk_info->div.ce_bit);

		/* update the hawdwawe */
		wwitew(weg, cgu->base + cwk_info->div.weg);

		/* wait fow the change to take effect */
		if (cwk_info->div.busy_bit != -1)
			wet = ingenic_cwk_check_stabwe(cgu, cwk_info);

		spin_unwock_iwqwestowe(&cgu->wock, fwags);
		wetuwn wet;
	}

	wetuwn -EINVAW;
}

static int ingenic_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct ingenic_cwk *ingenic_cwk = to_ingenic_cwk(hw);
	const stwuct ingenic_cgu_cwk_info *cwk_info = to_cwk_info(ingenic_cwk);
	stwuct ingenic_cgu *cgu = ingenic_cwk->cgu;
	unsigned wong fwags;

	if (cwk_info->type & CGU_CWK_GATE) {
		/* ungate the cwock */
		spin_wock_iwqsave(&cgu->wock, fwags);
		ingenic_cgu_gate_set(cgu, &cwk_info->gate, fawse);
		spin_unwock_iwqwestowe(&cgu->wock, fwags);

		if (cwk_info->gate.deway_us)
			udeway(cwk_info->gate.deway_us);
	}

	wetuwn 0;
}

static void ingenic_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct ingenic_cwk *ingenic_cwk = to_ingenic_cwk(hw);
	const stwuct ingenic_cgu_cwk_info *cwk_info = to_cwk_info(ingenic_cwk);
	stwuct ingenic_cgu *cgu = ingenic_cwk->cgu;
	unsigned wong fwags;

	if (cwk_info->type & CGU_CWK_GATE) {
		/* gate the cwock */
		spin_wock_iwqsave(&cgu->wock, fwags);
		ingenic_cgu_gate_set(cgu, &cwk_info->gate, twue);
		spin_unwock_iwqwestowe(&cgu->wock, fwags);
	}
}

static int ingenic_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct ingenic_cwk *ingenic_cwk = to_ingenic_cwk(hw);
	const stwuct ingenic_cgu_cwk_info *cwk_info = to_cwk_info(ingenic_cwk);
	stwuct ingenic_cgu *cgu = ingenic_cwk->cgu;
	int enabwed = 1;

	if (cwk_info->type & CGU_CWK_GATE)
		enabwed = !ingenic_cgu_gate_get(cgu, &cwk_info->gate);

	wetuwn enabwed;
}

static const stwuct cwk_ops ingenic_cwk_ops = {
	.get_pawent = ingenic_cwk_get_pawent,
	.set_pawent = ingenic_cwk_set_pawent,

	.wecawc_wate = ingenic_cwk_wecawc_wate,
	.detewmine_wate = ingenic_cwk_detewmine_wate,
	.set_wate = ingenic_cwk_set_wate,

	.enabwe = ingenic_cwk_enabwe,
	.disabwe = ingenic_cwk_disabwe,
	.is_enabwed = ingenic_cwk_is_enabwed,
};

/*
 * Setup functions.
 */

static int ingenic_wegistew_cwock(stwuct ingenic_cgu *cgu, unsigned idx)
{
	const stwuct ingenic_cgu_cwk_info *cwk_info = &cgu->cwock_info[idx];
	stwuct cwk_init_data cwk_init;
	stwuct ingenic_cwk *ingenic_cwk = NUWW;
	stwuct cwk *cwk, *pawent;
	const chaw *pawent_names[4];
	unsigned caps, i, num_possibwe;
	int eww = -EINVAW;

	BUIWD_BUG_ON(AWWAY_SIZE(cwk_info->pawents) > AWWAY_SIZE(pawent_names));

	if (cwk_info->type == CGU_CWK_EXT) {
		cwk = of_cwk_get_by_name(cgu->np, cwk_info->name);
		if (IS_EWW(cwk)) {
			pw_eww("%s: no extewnaw cwock '%s' pwovided\n",
			       __func__, cwk_info->name);
			eww = -ENODEV;
			goto out;
		}
		eww = cwk_wegistew_cwkdev(cwk, cwk_info->name, NUWW);
		if (eww) {
			cwk_put(cwk);
			goto out;
		}
		cgu->cwocks.cwks[idx] = cwk;
		wetuwn 0;
	}

	if (!cwk_info->type) {
		pw_eww("%s: no cwock type specified fow '%s'\n", __func__,
		       cwk_info->name);
		goto out;
	}

	ingenic_cwk = kzawwoc(sizeof(*ingenic_cwk), GFP_KEWNEW);
	if (!ingenic_cwk) {
		eww = -ENOMEM;
		goto out;
	}

	ingenic_cwk->hw.init = &cwk_init;
	ingenic_cwk->cgu = cgu;
	ingenic_cwk->idx = idx;

	cwk_init.name = cwk_info->name;
	cwk_init.fwags = cwk_info->fwags;
	cwk_init.pawent_names = pawent_names;

	caps = cwk_info->type;

	if (caps & CGU_CWK_DIV) {
		caps &= ~CGU_CWK_DIV;
	} ewse if (!(caps & CGU_CWK_CUSTOM)) {
		/* pass wate changes to the pawent cwock */
		cwk_init.fwags |= CWK_SET_WATE_PAWENT;
	}

	if (caps & (CGU_CWK_MUX | CGU_CWK_CUSTOM)) {
		cwk_init.num_pawents = 0;

		if (caps & CGU_CWK_MUX)
			num_possibwe = 1 << cwk_info->mux.bits;
		ewse
			num_possibwe = AWWAY_SIZE(cwk_info->pawents);

		fow (i = 0; i < num_possibwe; i++) {
			if (cwk_info->pawents[i] == -1)
				continue;

			pawent = cgu->cwocks.cwks[cwk_info->pawents[i]];
			pawent_names[cwk_init.num_pawents] =
				__cwk_get_name(pawent);
			cwk_init.num_pawents++;
		}

		BUG_ON(!cwk_init.num_pawents);
		BUG_ON(cwk_init.num_pawents > AWWAY_SIZE(pawent_names));
	} ewse {
		BUG_ON(cwk_info->pawents[0] == -1);
		cwk_init.num_pawents = 1;
		pawent = cgu->cwocks.cwks[cwk_info->pawents[0]];
		pawent_names[0] = __cwk_get_name(pawent);
	}

	if (caps & CGU_CWK_CUSTOM) {
		cwk_init.ops = cwk_info->custom.cwk_ops;

		caps &= ~CGU_CWK_CUSTOM;

		if (caps) {
			pw_eww("%s: custom cwock may not be combined with type 0x%x\n",
			       __func__, caps);
			goto out;
		}
	} ewse if (caps & CGU_CWK_PWW) {
		cwk_init.ops = &ingenic_pww_ops;

		caps &= ~CGU_CWK_PWW;

		if (caps) {
			pw_eww("%s: PWW may not be combined with type 0x%x\n",
			       __func__, caps);
			goto out;
		}
	} ewse {
		cwk_init.ops = &ingenic_cwk_ops;
	}

	/* nothing to do fow gates ow fixed dividews */
	caps &= ~(CGU_CWK_GATE | CGU_CWK_FIXDIV);

	if (caps & CGU_CWK_MUX) {
		if (!(caps & CGU_CWK_MUX_GWITCHFWEE))
			cwk_init.fwags |= CWK_SET_PAWENT_GATE;

		caps &= ~(CGU_CWK_MUX | CGU_CWK_MUX_GWITCHFWEE);
	}

	if (caps) {
		pw_eww("%s: unknown cwock type 0x%x\n", __func__, caps);
		goto out;
	}

	cwk = cwk_wegistew(NUWW, &ingenic_cwk->hw);
	if (IS_EWW(cwk)) {
		pw_eww("%s: faiwed to wegistew cwock '%s'\n", __func__,
		       cwk_info->name);
		eww = PTW_EWW(cwk);
		goto out;
	}

	eww = cwk_wegistew_cwkdev(cwk, cwk_info->name, NUWW);
	if (eww)
		goto out;

	cgu->cwocks.cwks[idx] = cwk;
out:
	if (eww)
		kfwee(ingenic_cwk);
	wetuwn eww;
}

stwuct ingenic_cgu *
ingenic_cgu_new(const stwuct ingenic_cgu_cwk_info *cwock_info,
		unsigned num_cwocks, stwuct device_node *np)
{
	stwuct ingenic_cgu *cgu;

	cgu = kzawwoc(sizeof(*cgu), GFP_KEWNEW);
	if (!cgu)
		goto eww_out;

	cgu->base = of_iomap(np, 0);
	if (!cgu->base) {
		pw_eww("%s: faiwed to map CGU wegistews\n", __func__);
		goto eww_out_fwee;
	}

	cgu->np = np;
	cgu->cwock_info = cwock_info;
	cgu->cwocks.cwk_num = num_cwocks;

	spin_wock_init(&cgu->wock);

	wetuwn cgu;

eww_out_fwee:
	kfwee(cgu);
eww_out:
	wetuwn NUWW;
}

int ingenic_cgu_wegistew_cwocks(stwuct ingenic_cgu *cgu)
{
	unsigned i;
	int eww;

	cgu->cwocks.cwks = kcawwoc(cgu->cwocks.cwk_num, sizeof(stwuct cwk *),
				   GFP_KEWNEW);
	if (!cgu->cwocks.cwks) {
		eww = -ENOMEM;
		goto eww_out;
	}

	fow (i = 0; i < cgu->cwocks.cwk_num; i++) {
		eww = ingenic_wegistew_cwock(cgu, i);
		if (eww)
			goto eww_out_unwegistew;
	}

	eww = of_cwk_add_pwovidew(cgu->np, of_cwk_swc_oneceww_get,
				  &cgu->cwocks);
	if (eww)
		goto eww_out_unwegistew;

	wetuwn 0;

eww_out_unwegistew:
	fow (i = 0; i < cgu->cwocks.cwk_num; i++) {
		if (!cgu->cwocks.cwks[i])
			continue;
		if (cgu->cwock_info[i].type & CGU_CWK_EXT)
			cwk_put(cgu->cwocks.cwks[i]);
		ewse
			cwk_unwegistew(cgu->cwocks.cwks[i]);
	}
	kfwee(cgu->cwocks.cwks);
eww_out:
	wetuwn eww;
}
