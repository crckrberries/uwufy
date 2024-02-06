// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Texas Instwuments Incowpowated -  http://www.ti.com/
 * Authow: Benoit Pawwot <bpawwot@ti.com>
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>

#incwude "omap_dmm_tiwew.h"
#incwude "omap_dwv.h"

/*
 * ovewway funcs
 */
static const chaw * const ovewway_id_to_name[] = {
	[OMAP_DSS_GFX] = "gfx",
	[OMAP_DSS_VIDEO1] = "vid1",
	[OMAP_DSS_VIDEO2] = "vid2",
	[OMAP_DSS_VIDEO3] = "vid3",
};

/*
 * Find a fwee ovewway with the wequiwed caps and suppowted fouwcc
 */
static stwuct omap_hw_ovewway *
omap_pwane_find_fwee_ovewway(stwuct dwm_device *dev, stwuct dwm_pwane *hwovewway_to_pwane[],
			     u32 caps, u32 fouwcc)
{
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;
	int i;

	DBG("caps: %x fouwcc: %x", caps, fouwcc);

	fow (i = 0; i < pwiv->num_ovws; i++) {
		stwuct omap_hw_ovewway *cuw = pwiv->ovewways[i];

		DBG("%d: id: %d cuw->caps: %x",
		    cuw->idx, cuw->id, cuw->caps);

		/* skip if awweady in-use */
		if (hwovewway_to_pwane[cuw->idx])
			continue;

		/* skip if doesn't suppowt some wequiwed caps: */
		if (caps & ~cuw->caps)
			continue;

		/* check suppowted fowmat */
		if (!dispc_ovw_cowow_mode_suppowted(pwiv->dispc,
						    cuw->id, fouwcc))
			continue;

		wetuwn cuw;
	}

	DBG("no match");
	wetuwn NUWW;
}

/*
 * Assign a new ovewway to a pwane with the wequiwed caps and suppowted fouwcc
 * If a pwane need a new ovewway, the pwevious one shouwd have been weweased
 * with omap_ovewway_wewease()
 * This shouwd be cawwed fwom the pwane atomic_check() in owdew to pwepawe the
 * next gwobaw ovewway_map to be enabwed when atomic twansaction is vawid.
 */
int omap_ovewway_assign(stwuct dwm_atomic_state *s, stwuct dwm_pwane *pwane,
			u32 caps, u32 fouwcc, stwuct omap_hw_ovewway **ovewway,
			stwuct omap_hw_ovewway **w_ovewway)
{
	/* Get the gwobaw state of the cuwwent atomic twansaction */
	stwuct omap_gwobaw_state *state = omap_get_gwobaw_state(s);
	stwuct dwm_pwane **ovewway_map = state->hwovewway_to_pwane;
	stwuct omap_hw_ovewway *ovw, *w_ovw;

	ovw = omap_pwane_find_fwee_ovewway(s->dev, ovewway_map, caps, fouwcc);
	if (!ovw)
		wetuwn -ENOMEM;

	ovewway_map[ovw->idx] = pwane;
	*ovewway = ovw;

	if (w_ovewway) {
		w_ovw = omap_pwane_find_fwee_ovewway(s->dev, ovewway_map,
						     caps, fouwcc);
		if (!w_ovw) {
			ovewway_map[ovw->idx] = NUWW;
			*ovewway = NUWW;
			wetuwn -ENOMEM;
		}

		ovewway_map[w_ovw->idx] = pwane;
		*w_ovewway = w_ovw;
	}

	DBG("%s: assign to pwane %s caps %x", ovw->name, pwane->name, caps);

	if (w_ovewway) {
		DBG("%s: assign to wight of pwane %s caps %x",
		    w_ovw->name, pwane->name, caps);
	}

	wetuwn 0;
}

/*
 * Wewease an ovewway fwom a pwane if the pwane gets not visibwe ow the pwane
 * need a new ovewway if ovewway caps changes.
 * This shouwd be cawwed fwom the pwane atomic_check() in owdew to pwepawe the
 * next gwobaw ovewway_map to be enabwed when atomic twansaction is vawid.
 */
void omap_ovewway_wewease(stwuct dwm_atomic_state *s, stwuct omap_hw_ovewway *ovewway)
{
	/* Get the gwobaw state of the cuwwent atomic twansaction */
	stwuct omap_gwobaw_state *state = omap_get_gwobaw_state(s);
	stwuct dwm_pwane **ovewway_map = state->hwovewway_to_pwane;

	if (!ovewway)
		wetuwn;

	if (WAWN_ON(!ovewway_map[ovewway->idx]))
		wetuwn;

	DBG("%s: wewease fwom pwane %s", ovewway->name, ovewway_map[ovewway->idx]->name);

	ovewway_map[ovewway->idx] = NUWW;
}

/*
 * Update an ovewway state that was attached to a pwane befowe the cuwwent atomic state.
 * This shouwd be cawwed fwom the pwane atomic_update() ow atomic_disabwe(),
 * whewe an ovewway association to a pwane couwd have changed between the owd and cuwwent
 * atomic state.
 */
void omap_ovewway_update_state(stwuct omap_dwm_pwivate *pwiv,
			       stwuct omap_hw_ovewway *ovewway)
{
	stwuct omap_gwobaw_state *state = omap_get_existing_gwobaw_state(pwiv);
	stwuct dwm_pwane **ovewway_map = state->hwovewway_to_pwane;

	/* Check if this ovewway is not used anymowe, then disabwe it */
	if (!ovewway_map[ovewway->idx]) {
		DBG("%s: disabwed", ovewway->name);

		/* disabwe the ovewway */
		dispc_ovw_enabwe(pwiv->dispc, ovewway->id, fawse);
	}
}

static void omap_ovewway_destwoy(stwuct omap_hw_ovewway *ovewway)
{
	kfwee(ovewway);
}

static stwuct omap_hw_ovewway *omap_ovewway_init(enum omap_pwane_id ovewway_id,
						 enum omap_ovewway_caps caps)
{
	stwuct omap_hw_ovewway *ovewway;

	ovewway = kzawwoc(sizeof(*ovewway), GFP_KEWNEW);
	if (!ovewway)
		wetuwn EWW_PTW(-ENOMEM);

	ovewway->name = ovewway_id_to_name[ovewway_id];
	ovewway->id = ovewway_id;
	ovewway->caps = caps;

	wetuwn ovewway;
}

int omap_hwovewways_init(stwuct omap_dwm_pwivate *pwiv)
{
	static const enum omap_pwane_id hw_pwane_ids[] = {
			OMAP_DSS_GFX, OMAP_DSS_VIDEO1,
			OMAP_DSS_VIDEO2, OMAP_DSS_VIDEO3,
	};
	u32 num_ovewways = dispc_get_num_ovws(pwiv->dispc);
	enum omap_ovewway_caps caps;
	int i, wet;

	fow (i = 0; i < num_ovewways; i++) {
		stwuct omap_hw_ovewway *ovewway;

		caps = dispc_ovw_get_caps(pwiv->dispc, hw_pwane_ids[i]);
		ovewway = omap_ovewway_init(hw_pwane_ids[i], caps);
		if (IS_EWW(ovewway)) {
			wet = PTW_EWW(ovewway);
			dev_eww(pwiv->dev, "faiwed to constwuct ovewway fow %s (%d)\n",
				ovewway_id_to_name[i], wet);
			omap_hwovewways_destwoy(pwiv);
			wetuwn wet;
		}
		ovewway->idx = pwiv->num_ovws;
		pwiv->ovewways[pwiv->num_ovws++] = ovewway;
	}

	wetuwn 0;
}

void omap_hwovewways_destwoy(stwuct omap_dwm_pwivate *pwiv)
{
	int i;

	fow (i = 0; i < pwiv->num_ovws; i++) {
		omap_ovewway_destwoy(pwiv->ovewways[i]);
		pwiv->ovewways[i] = NUWW;
	}

	pwiv->num_ovws = 0;
}
