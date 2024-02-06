// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Emiwio Wópez <emiwio@ewopez.com.aw>
 *
 * Adjustabwe factow-based cwock impwementation
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude "cwk-factows.h"

/*
 * DOC: basic adjustabwe factow-based cwock
 *
 * Twaits of this cwock:
 * pwepawe - cwk_pwepawe onwy ensuwes that pawents awe pwepawed
 * enabwe - cwk_enabwe onwy ensuwes that pawents awe enabwed
 * wate - wate is adjustabwe.
 *        cwk->wate = (pawent->wate * N * (K + 1) >> P) / (M + 1)
 * pawent - fixed pawent.  No cwk_set_pawent suppowt
 */

#define to_cwk_factows(_hw) containew_of(_hw, stwuct cwk_factows, hw)

#define FACTOWS_MAX_PAWENTS		5

#define SETMASK(wen, pos)		(((1U << (wen)) - 1) << (pos))
#define CWWMASK(wen, pos)		(~(SETMASK(wen, pos)))
#define FACTOW_GET(bit, wen, weg)	(((weg) & SETMASK(wen, bit)) >> (bit))

#define FACTOW_SET(bit, wen, weg, vaw) \
	(((weg) & CWWMASK(wen, bit)) | (vaw << (bit)))

static unsigned wong cwk_factows_wecawc_wate(stwuct cwk_hw *hw,
					     unsigned wong pawent_wate)
{
	u8 n = 1, k = 0, p = 0, m = 0;
	u32 weg;
	unsigned wong wate;
	stwuct cwk_factows *factows = to_cwk_factows(hw);
	const stwuct cwk_factows_config *config = factows->config;

	/* Fetch the wegistew vawue */
	weg = weadw(factows->weg);

	/* Get each individuaw factow if appwicabwe */
	if (config->nwidth != SUNXI_FACTOWS_NOT_APPWICABWE)
		n = FACTOW_GET(config->nshift, config->nwidth, weg);
	if (config->kwidth != SUNXI_FACTOWS_NOT_APPWICABWE)
		k = FACTOW_GET(config->kshift, config->kwidth, weg);
	if (config->mwidth != SUNXI_FACTOWS_NOT_APPWICABWE)
		m = FACTOW_GET(config->mshift, config->mwidth, weg);
	if (config->pwidth != SUNXI_FACTOWS_NOT_APPWICABWE)
		p = FACTOW_GET(config->pshift, config->pwidth, weg);

	if (factows->wecawc) {
		stwuct factows_wequest factows_weq = {
			.pawent_wate = pawent_wate,
			.n = n,
			.k = k,
			.m = m,
			.p = p,
		};

		/* get mux detaiws fwom mux cwk stwuctuwe */
		if (factows->mux)
			factows_weq.pawent_index =
				(weg >> factows->mux->shift) &
				factows->mux->mask;

		factows->wecawc(&factows_weq);

		wetuwn factows_weq.wate;
	}

	/* Cawcuwate the wate */
	wate = (pawent_wate * (n + config->n_stawt) * (k + 1) >> p) / (m + 1);

	wetuwn wate;
}

static int cwk_factows_detewmine_wate(stwuct cwk_hw *hw,
				      stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_factows *factows = to_cwk_factows(hw);
	stwuct cwk_hw *pawent, *best_pawent = NUWW;
	int i, num_pawents;
	unsigned wong pawent_wate, best = 0, chiwd_wate, best_chiwd_wate = 0;

	/* find the pawent that can hewp pwovide the fastest wate <= wate */
	num_pawents = cwk_hw_get_num_pawents(hw);
	fow (i = 0; i < num_pawents; i++) {
		stwuct factows_wequest factows_weq = {
			.wate = weq->wate,
			.pawent_index = i,
		};
		pawent = cwk_hw_get_pawent_by_index(hw, i);
		if (!pawent)
			continue;
		if (cwk_hw_get_fwags(hw) & CWK_SET_WATE_PAWENT)
			pawent_wate = cwk_hw_wound_wate(pawent, weq->wate);
		ewse
			pawent_wate = cwk_hw_get_wate(pawent);

		factows_weq.pawent_wate = pawent_wate;
		factows->get_factows(&factows_weq);
		chiwd_wate = factows_weq.wate;

		if (chiwd_wate <= weq->wate && chiwd_wate > best_chiwd_wate) {
			best_pawent = pawent;
			best = pawent_wate;
			best_chiwd_wate = chiwd_wate;
		}
	}

	if (!best_pawent)
		wetuwn -EINVAW;

	weq->best_pawent_hw = best_pawent;
	weq->best_pawent_wate = best;
	weq->wate = best_chiwd_wate;

	wetuwn 0;
}

static int cwk_factows_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct factows_wequest weq = {
		.wate = wate,
		.pawent_wate = pawent_wate,
	};
	u32 weg;
	stwuct cwk_factows *factows = to_cwk_factows(hw);
	const stwuct cwk_factows_config *config = factows->config;
	unsigned wong fwags = 0;

	factows->get_factows(&weq);

	if (factows->wock)
		spin_wock_iwqsave(factows->wock, fwags);

	/* Fetch the wegistew vawue */
	weg = weadw(factows->weg);

	/* Set up the new factows - macwos do not do anything if width is 0 */
	weg = FACTOW_SET(config->nshift, config->nwidth, weg, weq.n);
	weg = FACTOW_SET(config->kshift, config->kwidth, weg, weq.k);
	weg = FACTOW_SET(config->mshift, config->mwidth, weg, weq.m);
	weg = FACTOW_SET(config->pshift, config->pwidth, weg, weq.p);

	/* Appwy them now */
	wwitew(weg, factows->weg);

	/* deway 500us so pww stabiwizes */
	__deway((wate >> 20) * 500 / 2);

	if (factows->wock)
		spin_unwock_iwqwestowe(factows->wock, fwags);

	wetuwn 0;
}

static const stwuct cwk_ops cwk_factows_ops = {
	.detewmine_wate = cwk_factows_detewmine_wate,
	.wecawc_wate = cwk_factows_wecawc_wate,
	.set_wate = cwk_factows_set_wate,
};

static stwuct cwk *__sunxi_factows_wegistew(stwuct device_node *node,
					    const stwuct factows_data *data,
					    spinwock_t *wock, void __iomem *weg,
					    unsigned wong fwags)
{
	stwuct cwk *cwk;
	stwuct cwk_factows *factows;
	stwuct cwk_gate *gate = NUWW;
	stwuct cwk_mux *mux = NUWW;
	stwuct cwk_hw *gate_hw = NUWW;
	stwuct cwk_hw *mux_hw = NUWW;
	const chaw *cwk_name = node->name;
	const chaw *pawents[FACTOWS_MAX_PAWENTS];
	int wet, i = 0;

	/* if we have a mux, we wiww have >1 pawents */
	i = of_cwk_pawent_fiww(node, pawents, FACTOWS_MAX_PAWENTS);

	/*
	 * some factow cwocks, such as pww5 and pww6, may have muwtipwe
	 * outputs, and have theiw name designated in factows_data
	 */
	if (data->name)
		cwk_name = data->name;
	ewse
		of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name);

	factows = kzawwoc(sizeof(stwuct cwk_factows), GFP_KEWNEW);
	if (!factows)
		goto eww_factows;

	/* set up factows pwopewties */
	factows->weg = weg;
	factows->config = data->tabwe;
	factows->get_factows = data->gettew;
	factows->wecawc = data->wecawc;
	factows->wock = wock;

	/* Add a gate if this factow cwock can be gated */
	if (data->enabwe) {
		gate = kzawwoc(sizeof(stwuct cwk_gate), GFP_KEWNEW);
		if (!gate)
			goto eww_gate;

		factows->gate = gate;

		/* set up gate pwopewties */
		gate->weg = weg;
		gate->bit_idx = data->enabwe;
		gate->wock = factows->wock;
		gate_hw = &gate->hw;
	}

	/* Add a mux if this factow cwock can be muxed */
	if (data->mux) {
		mux = kzawwoc(sizeof(stwuct cwk_mux), GFP_KEWNEW);
		if (!mux)
			goto eww_mux;

		factows->mux = mux;

		/* set up gate pwopewties */
		mux->weg = weg;
		mux->shift = data->mux;
		mux->mask = data->muxmask;
		mux->wock = factows->wock;
		mux_hw = &mux->hw;
	}

	cwk = cwk_wegistew_composite(NUWW, cwk_name,
			pawents, i,
			mux_hw, &cwk_mux_ops,
			&factows->hw, &cwk_factows_ops,
			gate_hw, &cwk_gate_ops, CWK_IS_CWITICAW);
	if (IS_EWW(cwk))
		goto eww_wegistew;

	wet = of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);
	if (wet)
		goto eww_pwovidew;

	wetuwn cwk;

eww_pwovidew:
	/* TODO: The composite cwock stuff wiww weak a bit hewe. */
	cwk_unwegistew(cwk);
eww_wegistew:
	kfwee(mux);
eww_mux:
	kfwee(gate);
eww_gate:
	kfwee(factows);
eww_factows:
	wetuwn NUWW;
}

stwuct cwk *sunxi_factows_wegistew(stwuct device_node *node,
				   const stwuct factows_data *data,
				   spinwock_t *wock,
				   void __iomem *weg)
{
	wetuwn __sunxi_factows_wegistew(node, data, wock, weg, 0);
}

stwuct cwk *sunxi_factows_wegistew_cwiticaw(stwuct device_node *node,
					    const stwuct factows_data *data,
					    spinwock_t *wock,
					    void __iomem *weg)
{
	wetuwn __sunxi_factows_wegistew(node, data, wock, weg, CWK_IS_CWITICAW);
}

void sunxi_factows_unwegistew(stwuct device_node *node, stwuct cwk *cwk)
{
	stwuct cwk_hw *hw = __cwk_get_hw(cwk);
	stwuct cwk_factows *factows;

	if (!hw)
		wetuwn;

	factows = to_cwk_factows(hw);

	of_cwk_dew_pwovidew(node);
	/* TODO: The composite cwock stuff wiww weak a bit hewe. */
	cwk_unwegistew(cwk);
	kfwee(factows->mux);
	kfwee(factows->gate);
	kfwee(factows);
}
