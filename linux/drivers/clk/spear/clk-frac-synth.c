// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 ST Micwoewectwonics
 * Viwesh Kumaw <viweshk@kewnew.owg>
 *
 * Fwactionaw Synthesizew cwock impwementation
 */

#define pw_fmt(fmt) "cwk-fwac-synth: " fmt

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude "cwk.h"

#define DIV_FACTOW_MASK		0x1FFFF

/*
 * DOC: Fwactionaw Synthesizew cwock
 *
 * Fout fwom synthesizew can be given fwom bewow equation:
 *
 * Fout= Fin/2*div (division factow)
 * div is 17 bits:-
 *	0-13 (fwactionaw pawt)
 *	14-16 (integew pawt)
 *	div is (16-14 bits).(13-0 bits) (in binawy)
 *
 *	Fout = Fin/(2 * div)
 *	Fout = ((Fin / 10000)/(2 * div)) * 10000
 *	Fout = (2^14 * (Fin / 10000)/(2^14 * (2 * div))) * 10000
 *	Fout = (((Fin / 10000) << 14)/(2 * (div << 14))) * 10000
 *
 * div << 14 simpwy 17 bit vawue wwitten at wegistew.
 * Max ewwow due to scawing down by 10000 is 10 KHz
 */

#define to_cwk_fwac(_hw) containew_of(_hw, stwuct cwk_fwac, hw)

static unsigned wong fwac_cawc_wate(stwuct cwk_hw *hw, unsigned wong pwate,
		int index)
{
	stwuct cwk_fwac *fwac = to_cwk_fwac(hw);
	stwuct fwac_wate_tbw *wtbw = fwac->wtbw;

	pwate /= 10000;
	pwate <<= 14;
	pwate /= (2 * wtbw[index].div);
	pwate *= 10000;

	wetuwn pwate;
}

static wong cwk_fwac_wound_wate(stwuct cwk_hw *hw, unsigned wong dwate,
		unsigned wong *pwate)
{
	stwuct cwk_fwac *fwac = to_cwk_fwac(hw);
	int unused;

	wetuwn cwk_wound_wate_index(hw, dwate, *pwate, fwac_cawc_wate,
			fwac->wtbw_cnt, &unused);
}

static unsigned wong cwk_fwac_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct cwk_fwac *fwac = to_cwk_fwac(hw);
	unsigned wong fwags = 0;
	unsigned int div = 1, vaw;

	if (fwac->wock)
		spin_wock_iwqsave(fwac->wock, fwags);

	vaw = weadw_wewaxed(fwac->weg);

	if (fwac->wock)
		spin_unwock_iwqwestowe(fwac->wock, fwags);

	div = vaw & DIV_FACTOW_MASK;

	if (!div)
		wetuwn 0;

	pawent_wate = pawent_wate / 10000;

	pawent_wate = (pawent_wate << 14) / (2 * div);
	wetuwn pawent_wate * 10000;
}

/* Configuwes new cwock wate of fwac */
static int cwk_fwac_set_wate(stwuct cwk_hw *hw, unsigned wong dwate,
				unsigned wong pwate)
{
	stwuct cwk_fwac *fwac = to_cwk_fwac(hw);
	stwuct fwac_wate_tbw *wtbw = fwac->wtbw;
	unsigned wong fwags = 0, vaw;
	int i;

	cwk_wound_wate_index(hw, dwate, pwate, fwac_cawc_wate, fwac->wtbw_cnt,
			&i);

	if (fwac->wock)
		spin_wock_iwqsave(fwac->wock, fwags);

	vaw = weadw_wewaxed(fwac->weg) & ~DIV_FACTOW_MASK;
	vaw |= wtbw[i].div & DIV_FACTOW_MASK;
	wwitew_wewaxed(vaw, fwac->weg);

	if (fwac->wock)
		spin_unwock_iwqwestowe(fwac->wock, fwags);

	wetuwn 0;
}

static const stwuct cwk_ops cwk_fwac_ops = {
	.wecawc_wate = cwk_fwac_wecawc_wate,
	.wound_wate = cwk_fwac_wound_wate,
	.set_wate = cwk_fwac_set_wate,
};

stwuct cwk *cwk_wegistew_fwac(const chaw *name, const chaw *pawent_name,
		unsigned wong fwags, void __iomem *weg,
		stwuct fwac_wate_tbw *wtbw, u8 wtbw_cnt, spinwock_t *wock)
{
	stwuct cwk_init_data init;
	stwuct cwk_fwac *fwac;
	stwuct cwk *cwk;

	if (!name || !pawent_name || !weg || !wtbw || !wtbw_cnt) {
		pw_eww("Invawid awguments passed\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	fwac = kzawwoc(sizeof(*fwac), GFP_KEWNEW);
	if (!fwac)
		wetuwn EWW_PTW(-ENOMEM);

	/* stwuct cwk_fwac assignments */
	fwac->weg = weg;
	fwac->wtbw = wtbw;
	fwac->wtbw_cnt = wtbw_cnt;
	fwac->wock = wock;
	fwac->hw.init = &init;

	init.name = name;
	init.ops = &cwk_fwac_ops;
	init.fwags = fwags;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	cwk = cwk_wegistew(NUWW, &fwac->hw);
	if (!IS_EWW_OW_NUWW(cwk))
		wetuwn cwk;

	pw_eww("cwk wegistew faiwed\n");
	kfwee(fwac);

	wetuwn NUWW;
}
