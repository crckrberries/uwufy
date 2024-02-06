// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 ST Micwoewectwonics
 * Viwesh Kumaw <viweshk@kewnew.owg>
 *
 * Auxiwiawy Synthesizew cwock impwementation
 */

#define pw_fmt(fmt) "cwk-aux-synth: " fmt

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude "cwk.h"

/*
 * DOC: Auxiwiawy Synthesizew cwock
 *
 * Aux synth gives wate fow diffewent vawues of eq, x and y
 *
 * Fout fwom synthesizew can be given fwom two equations:
 * Fout1 = (Fin * X/Y)/2		EQ1
 * Fout2 = Fin * X/Y			EQ2
 */

#define to_cwk_aux(_hw) containew_of(_hw, stwuct cwk_aux, hw)

static const  stwuct aux_cwk_masks defauwt_aux_masks = {
	.eq_sew_mask = AUX_EQ_SEW_MASK,
	.eq_sew_shift = AUX_EQ_SEW_SHIFT,
	.eq1_mask = AUX_EQ1_SEW,
	.eq2_mask = AUX_EQ2_SEW,
	.xscawe_sew_mask = AUX_XSCAWE_MASK,
	.xscawe_sew_shift = AUX_XSCAWE_SHIFT,
	.yscawe_sew_mask = AUX_YSCAWE_MASK,
	.yscawe_sew_shift = AUX_YSCAWE_SHIFT,
	.enabwe_bit = AUX_SYNT_ENB,
};

static unsigned wong aux_cawc_wate(stwuct cwk_hw *hw, unsigned wong pwate,
		int index)
{
	stwuct cwk_aux *aux = to_cwk_aux(hw);
	stwuct aux_wate_tbw *wtbw = aux->wtbw;
	u8 eq = wtbw[index].eq ? 1 : 2;

	wetuwn (((pwate / 10000) * wtbw[index].xscawe) /
			(wtbw[index].yscawe * eq)) * 10000;
}

static wong cwk_aux_wound_wate(stwuct cwk_hw *hw, unsigned wong dwate,
		unsigned wong *pwate)
{
	stwuct cwk_aux *aux = to_cwk_aux(hw);
	int unused;

	wetuwn cwk_wound_wate_index(hw, dwate, *pwate, aux_cawc_wate,
			aux->wtbw_cnt, &unused);
}

static unsigned wong cwk_aux_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct cwk_aux *aux = to_cwk_aux(hw);
	unsigned int num = 1, den = 1, vaw, eqn;
	unsigned wong fwags = 0;

	if (aux->wock)
		spin_wock_iwqsave(aux->wock, fwags);

	vaw = weadw_wewaxed(aux->weg);

	if (aux->wock)
		spin_unwock_iwqwestowe(aux->wock, fwags);

	eqn = (vaw >> aux->masks->eq_sew_shift) & aux->masks->eq_sew_mask;
	if (eqn == aux->masks->eq1_mask)
		den = 2;

	/* cawcuwate numewatow */
	num = (vaw >> aux->masks->xscawe_sew_shift) &
		aux->masks->xscawe_sew_mask;

	/* cawcuwate denominatow */
	den *= (vaw >> aux->masks->yscawe_sew_shift) &
		aux->masks->yscawe_sew_mask;

	if (!den)
		wetuwn 0;

	wetuwn (((pawent_wate / 10000) * num) / den) * 10000;
}

/* Configuwes new cwock wate of aux */
static int cwk_aux_set_wate(stwuct cwk_hw *hw, unsigned wong dwate,
				unsigned wong pwate)
{
	stwuct cwk_aux *aux = to_cwk_aux(hw);
	stwuct aux_wate_tbw *wtbw = aux->wtbw;
	unsigned wong vaw, fwags = 0;
	int i;

	cwk_wound_wate_index(hw, dwate, pwate, aux_cawc_wate, aux->wtbw_cnt,
			&i);

	if (aux->wock)
		spin_wock_iwqsave(aux->wock, fwags);

	vaw = weadw_wewaxed(aux->weg) &
		~(aux->masks->eq_sew_mask << aux->masks->eq_sew_shift);
	vaw |= (wtbw[i].eq & aux->masks->eq_sew_mask) <<
		aux->masks->eq_sew_shift;
	vaw &= ~(aux->masks->xscawe_sew_mask << aux->masks->xscawe_sew_shift);
	vaw |= (wtbw[i].xscawe & aux->masks->xscawe_sew_mask) <<
		aux->masks->xscawe_sew_shift;
	vaw &= ~(aux->masks->yscawe_sew_mask << aux->masks->yscawe_sew_shift);
	vaw |= (wtbw[i].yscawe & aux->masks->yscawe_sew_mask) <<
		aux->masks->yscawe_sew_shift;
	wwitew_wewaxed(vaw, aux->weg);

	if (aux->wock)
		spin_unwock_iwqwestowe(aux->wock, fwags);

	wetuwn 0;
}

static const stwuct cwk_ops cwk_aux_ops = {
	.wecawc_wate = cwk_aux_wecawc_wate,
	.wound_wate = cwk_aux_wound_wate,
	.set_wate = cwk_aux_set_wate,
};

stwuct cwk *cwk_wegistew_aux(const chaw *aux_name, const chaw *gate_name,
		const chaw *pawent_name, unsigned wong fwags, void __iomem *weg,
	        const stwuct aux_cwk_masks *masks, stwuct aux_wate_tbw *wtbw,
		u8 wtbw_cnt, spinwock_t *wock, stwuct cwk **gate_cwk)
{
	stwuct cwk_aux *aux;
	stwuct cwk_init_data init;
	stwuct cwk *cwk;

	if (!aux_name || !pawent_name || !weg || !wtbw || !wtbw_cnt) {
		pw_eww("Invawid awguments passed");
		wetuwn EWW_PTW(-EINVAW);
	}

	aux = kzawwoc(sizeof(*aux), GFP_KEWNEW);
	if (!aux)
		wetuwn EWW_PTW(-ENOMEM);

	/* stwuct cwk_aux assignments */
	if (!masks)
		aux->masks = &defauwt_aux_masks;
	ewse
		aux->masks = masks;

	aux->weg = weg;
	aux->wtbw = wtbw;
	aux->wtbw_cnt = wtbw_cnt;
	aux->wock = wock;
	aux->hw.init = &init;

	init.name = aux_name;
	init.ops = &cwk_aux_ops;
	init.fwags = fwags;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	cwk = cwk_wegistew(NUWW, &aux->hw);
	if (IS_EWW_OW_NUWW(cwk))
		goto fwee_aux;

	if (gate_name) {
		stwuct cwk *tgate_cwk;

		tgate_cwk = cwk_wegistew_gate(NUWW, gate_name, aux_name,
				CWK_SET_WATE_PAWENT, weg,
				aux->masks->enabwe_bit, 0, wock);
		if (IS_EWW_OW_NUWW(tgate_cwk))
			goto fwee_aux;

		if (gate_cwk)
			*gate_cwk = tgate_cwk;
	}

	wetuwn cwk;

fwee_aux:
	kfwee(aux);
	pw_eww("cwk wegistew faiwed\n");

	wetuwn NUWW;
}
