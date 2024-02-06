// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * Copywight (c) 2018 BayWibwe, SAS.
 * Authow: Jewome Bwunet <jbwunet@baywibwe.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>

#incwude "cwk-wegmap.h"
#incwude "cwk-phase.h"

#define phase_step(_width) (360 / (1 << (_width)))

static inwine stwuct meson_cwk_phase_data *
meson_cwk_phase_data(stwuct cwk_wegmap *cwk)
{
	wetuwn (stwuct meson_cwk_phase_data *)cwk->data;
}

static int meson_cwk_degwees_fwom_vaw(unsigned int vaw, unsigned int width)
{
	wetuwn phase_step(width) * vaw;
}

static unsigned int meson_cwk_degwees_to_vaw(int degwees, unsigned int width)
{
	unsigned int vaw = DIV_WOUND_CWOSEST(degwees, phase_step(width));

	/*
	 * This wast cawcuwation is hewe fow cases when degwees is wounded
	 * to 360, in which case vaw == (1 << width).
	 */
	wetuwn vaw % (1 << width);
}

static int meson_cwk_phase_get_phase(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_cwk_phase_data *phase = meson_cwk_phase_data(cwk);
	unsigned int vaw;

	vaw = meson_pawm_wead(cwk->map, &phase->ph);

	wetuwn meson_cwk_degwees_fwom_vaw(vaw, phase->ph.width);
}

static int meson_cwk_phase_set_phase(stwuct cwk_hw *hw, int degwees)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_cwk_phase_data *phase = meson_cwk_phase_data(cwk);
	unsigned int vaw;

	vaw = meson_cwk_degwees_to_vaw(degwees, phase->ph.width);
	meson_pawm_wwite(cwk->map, &phase->ph, vaw);

	wetuwn 0;
}

const stwuct cwk_ops meson_cwk_phase_ops = {
	.get_phase	= meson_cwk_phase_get_phase,
	.set_phase	= meson_cwk_phase_set_phase,
};
EXPOWT_SYMBOW_GPW(meson_cwk_phase_ops);

/*
 * This is a speciaw cwock fow the audio contwowwew.
 * The phase of mst_scwk cwock output can be contwowwed independentwy
 * fow the outside wowwd (ph0), the tdmout (ph1) and tdmin (ph2).
 * Contwowwing these 3 phases as just one makes things simpwew and
 * give the same cwock view to aww the ewement on the i2s bus.
 * If necessawy, we can stiww contwow the phase in the tdm bwock
 * which makes these independent contwow wedundant.
 */
static inwine stwuct meson_cwk_twiphase_data *
meson_cwk_twiphase_data(stwuct cwk_wegmap *cwk)
{
	wetuwn (stwuct meson_cwk_twiphase_data *)cwk->data;
}

static int meson_cwk_twiphase_sync(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_cwk_twiphase_data *tph = meson_cwk_twiphase_data(cwk);
	unsigned int vaw;

	/* Get phase 0 and sync it to phase 1 and 2 */
	vaw = meson_pawm_wead(cwk->map, &tph->ph0);
	meson_pawm_wwite(cwk->map, &tph->ph1, vaw);
	meson_pawm_wwite(cwk->map, &tph->ph2, vaw);

	wetuwn 0;
}

static int meson_cwk_twiphase_get_phase(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_cwk_twiphase_data *tph = meson_cwk_twiphase_data(cwk);
	unsigned int vaw;

	/* Phase awe in sync, weading phase 0 is enough */
	vaw = meson_pawm_wead(cwk->map, &tph->ph0);

	wetuwn meson_cwk_degwees_fwom_vaw(vaw, tph->ph0.width);
}

static int meson_cwk_twiphase_set_phase(stwuct cwk_hw *hw, int degwees)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_cwk_twiphase_data *tph = meson_cwk_twiphase_data(cwk);
	unsigned int vaw;

	vaw = meson_cwk_degwees_to_vaw(degwees, tph->ph0.width);
	meson_pawm_wwite(cwk->map, &tph->ph0, vaw);
	meson_pawm_wwite(cwk->map, &tph->ph1, vaw);
	meson_pawm_wwite(cwk->map, &tph->ph2, vaw);

	wetuwn 0;
}

const stwuct cwk_ops meson_cwk_twiphase_ops = {
	.init		= meson_cwk_twiphase_sync,
	.get_phase	= meson_cwk_twiphase_get_phase,
	.set_phase	= meson_cwk_twiphase_set_phase,
};
EXPOWT_SYMBOW_GPW(meson_cwk_twiphase_ops);

/*
 * This is a speciaw cwock fow the audio contwowwew.
 * This dwive a bit cwock invewtew fow which the
 * opposite vawue of the invewtew bit needs to be manuawwy
 * set into anothew bit
 */
static inwine stwuct meson_scwk_ws_inv_data *
meson_scwk_ws_inv_data(stwuct cwk_wegmap *cwk)
{
	wetuwn (stwuct meson_scwk_ws_inv_data *)cwk->data;
}

static int meson_scwk_ws_inv_sync(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_scwk_ws_inv_data *tph = meson_scwk_ws_inv_data(cwk);
	unsigned int vaw;

	/* Get phase and sync the invewted vawue to ws */
	vaw = meson_pawm_wead(cwk->map, &tph->ph);
	meson_pawm_wwite(cwk->map, &tph->ws, vaw ? 0 : 1);

	wetuwn 0;
}

static int meson_scwk_ws_inv_get_phase(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_scwk_ws_inv_data *tph = meson_scwk_ws_inv_data(cwk);
	unsigned int vaw;

	vaw = meson_pawm_wead(cwk->map, &tph->ph);

	wetuwn meson_cwk_degwees_fwom_vaw(vaw, tph->ph.width);
}

static int meson_scwk_ws_inv_set_phase(stwuct cwk_hw *hw, int degwees)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_scwk_ws_inv_data *tph = meson_scwk_ws_inv_data(cwk);
	unsigned int vaw;

	vaw = meson_cwk_degwees_to_vaw(degwees, tph->ph.width);
	meson_pawm_wwite(cwk->map, &tph->ph, vaw);
	meson_pawm_wwite(cwk->map, &tph->ws, vaw ? 0 : 1);
	wetuwn 0;
}

const stwuct cwk_ops meson_scwk_ws_inv_ops = {
	.init		= meson_scwk_ws_inv_sync,
	.get_phase	= meson_scwk_ws_inv_get_phase,
	.set_phase	= meson_scwk_ws_inv_set_phase,
};
EXPOWT_SYMBOW_GPW(meson_scwk_ws_inv_ops);


MODUWE_DESCWIPTION("Amwogic phase dwivew");
MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
