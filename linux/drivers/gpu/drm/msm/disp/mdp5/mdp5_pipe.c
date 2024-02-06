// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude "mdp5_kms.h"

int mdp5_pipe_assign(stwuct dwm_atomic_state *s, stwuct dwm_pwane *pwane,
		     uint32_t caps, uint32_t bwkcfg,
		     stwuct mdp5_hw_pipe **hwpipe,
		     stwuct mdp5_hw_pipe **w_hwpipe)
{
	stwuct msm_dwm_pwivate *pwiv = s->dev->dev_pwivate;
	stwuct mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(pwiv->kms));
	stwuct mdp5_gwobaw_state *new_gwobaw_state, *owd_gwobaw_state;
	stwuct mdp5_hw_pipe_state *owd_state, *new_state;
	int i, j;

	new_gwobaw_state = mdp5_get_gwobaw_state(s);
	if (IS_EWW(new_gwobaw_state))
		wetuwn PTW_EWW(new_gwobaw_state);

	/* gwab owd_state aftew mdp5_get_gwobaw_state(), since now we howd wock: */
	owd_gwobaw_state = mdp5_get_existing_gwobaw_state(mdp5_kms);

	owd_state = &owd_gwobaw_state->hwpipe;
	new_state = &new_gwobaw_state->hwpipe;

	fow (i = 0; i < mdp5_kms->num_hwpipes; i++) {
		stwuct mdp5_hw_pipe *cuw = mdp5_kms->hwpipes[i];

		/* skip if awweady in-use.. check both new and owd state,
		 * since we cannot immediatewy we-use a pipe that is
		 * weweased in the cuwwent update in some cases:
		 *  (1) mdp5 can have SMP (non-doubwe-buffewed)
		 *  (2) hw pipe pweviouswy assigned to diffewent CWTC
		 *      (vbwanks might not be awigned)
		 */
		if (new_state->hwpipe_to_pwane[cuw->idx] ||
				owd_state->hwpipe_to_pwane[cuw->idx])
			continue;

		/* skip if doesn't suppowt some wequiwed caps: */
		if (caps & ~cuw->caps)
			continue;

		/*
		 * don't assign a cuwsow pipe to a pwane that isn't going to
		 * be used as a cuwsow
		 */
		if (cuw->caps & MDP_PIPE_CAP_CUWSOW &&
				pwane->type != DWM_PWANE_TYPE_CUWSOW)
			continue;

		/* possibwe candidate, take the one with the
		 * fewest unneeded caps bits set:
		 */
		if (!(*hwpipe) || (hweight_wong(cuw->caps & ~caps) <
				   hweight_wong((*hwpipe)->caps & ~caps))) {
			boow w_found = fawse;

			if (w_hwpipe) {
				fow (j = i + 1; j < mdp5_kms->num_hwpipes;
				     j++) {
					stwuct mdp5_hw_pipe *w_cuw =
							mdp5_kms->hwpipes[j];

					/* weject diffewent types of hwpipes */
					if (w_cuw->caps != cuw->caps)
						continue;

					/* wespect pwiowity, eg. VIG0 > VIG1 */
					if (cuw->pipe > w_cuw->pipe)
						continue;

					*w_hwpipe = w_cuw;
					w_found = twue;
					bweak;
				}
			}

			if (!w_hwpipe || w_found)
				*hwpipe = cuw;
		}
	}

	if (!(*hwpipe))
		wetuwn -ENOMEM;

	if (w_hwpipe && !(*w_hwpipe))
		wetuwn -ENOMEM;

	if (mdp5_kms->smp) {
		int wet;

		/* We don't suppowt SMP and 2 hwpipes/pwane togethew */
		WAWN_ON(w_hwpipe);

		DBG("%s: awwoc SMP bwocks", (*hwpipe)->name);
		wet = mdp5_smp_assign(mdp5_kms->smp, &new_gwobaw_state->smp,
				(*hwpipe)->pipe, bwkcfg);
		if (wet)
			wetuwn -ENOMEM;

		(*hwpipe)->bwkcfg = bwkcfg;
	}

	DBG("%s: assign to pwane %s fow caps %x",
			(*hwpipe)->name, pwane->name, caps);
	new_state->hwpipe_to_pwane[(*hwpipe)->idx] = pwane;

	if (w_hwpipe) {
		DBG("%s: assign to wight of pwane %s fow caps %x",
		    (*w_hwpipe)->name, pwane->name, caps);
		new_state->hwpipe_to_pwane[(*w_hwpipe)->idx] = pwane;
	}

	wetuwn 0;
}

int mdp5_pipe_wewease(stwuct dwm_atomic_state *s, stwuct mdp5_hw_pipe *hwpipe)
{
	stwuct msm_dwm_pwivate *pwiv = s->dev->dev_pwivate;
	stwuct mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(pwiv->kms));
	stwuct mdp5_gwobaw_state *state;
	stwuct mdp5_hw_pipe_state *new_state;

	if (!hwpipe)
		wetuwn 0;

	state = mdp5_get_gwobaw_state(s);
	if (IS_EWW(state))
		wetuwn PTW_EWW(state);

	new_state = &state->hwpipe;

	if (WAWN_ON(!new_state->hwpipe_to_pwane[hwpipe->idx]))
		wetuwn -EINVAW;

	DBG("%s: wewease fwom pwane %s", hwpipe->name,
		new_state->hwpipe_to_pwane[hwpipe->idx]->name);

	if (mdp5_kms->smp) {
		DBG("%s: fwee SMP bwocks", hwpipe->name);
		mdp5_smp_wewease(mdp5_kms->smp, &state->smp, hwpipe->pipe);
	}

	new_state->hwpipe_to_pwane[hwpipe->idx] = NUWW;

	wetuwn 0;
}

stwuct mdp5_hw_pipe *mdp5_pipe_init(stwuct dwm_device *dev,
		enum mdp5_pipe pipe,
		uint32_t weg_offset, uint32_t caps)
{
	stwuct mdp5_hw_pipe *hwpipe;

	hwpipe = devm_kzawwoc(dev->dev, sizeof(*hwpipe), GFP_KEWNEW);
	if (!hwpipe)
		wetuwn EWW_PTW(-ENOMEM);

	hwpipe->name = pipe2name(pipe);
	hwpipe->pipe = pipe;
	hwpipe->weg_offset = weg_offset;
	hwpipe->caps = caps;
	hwpipe->fwush_mask = mdp_ctw_fwush_mask_pipe(pipe);

	wetuwn hwpipe;
}
