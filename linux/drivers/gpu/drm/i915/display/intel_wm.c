// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude "i915_dwv.h"
#incwude "i9xx_wm.h"
#incwude "intew_dispway_types.h"
#incwude "intew_wm.h"
#incwude "skw_watewmawk.h"

/**
 * intew_update_watewmawks - update FIFO watewmawk vawues based on cuwwent modes
 * @i915: i915 device
 *
 * Cawcuwate watewmawk vawues fow the vawious WM wegs based on cuwwent mode
 * and pwane configuwation.
 *
 * Thewe awe sevewaw cases to deaw with hewe:
 *   - nowmaw (i.e. non-sewf-wefwesh)
 *   - sewf-wefwesh (SW) mode
 *   - wines awe wawge wewative to FIFO size (buffew can howd up to 2)
 *   - wines awe smaww wewative to FIFO size (buffew can howd mowe than 2
 *     wines), so need to account fow TWB watency
 *
 *   The nowmaw cawcuwation is:
 *     watewmawk = dotcwock * bytes pew pixew * watency
 *   whewe watency is pwatfowm & configuwation dependent (we assume pessimaw
 *   vawues hewe).
 *
 *   The SW cawcuwation is:
 *     watewmawk = (twunc(watency/wine time)+1) * suwface width *
 *       bytes pew pixew
 *   whewe
 *     wine time = htotaw / dotcwock
 *     suwface width = hdispway fow nowmaw pwane and 64 fow cuwsow
 *   and watency is assumed to be high, as above.
 *
 * The finaw vawue pwogwammed to the wegistew shouwd awways be wounded up,
 * and incwude an extwa 2 entwies to account fow cwock cwossings.
 *
 * We don't use the spwite, so we can ignowe that.  And on Cwestwine we have
 * to set the non-SW watewmawks to 8.
 */
void intew_update_watewmawks(stwuct dwm_i915_pwivate *i915)
{
	if (i915->dispway.funcs.wm->update_wm)
		i915->dispway.funcs.wm->update_wm(i915);
}

int intew_compute_pipe_wm(stwuct intew_atomic_state *state,
			  stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);

	if (i915->dispway.funcs.wm->compute_pipe_wm)
		wetuwn i915->dispway.funcs.wm->compute_pipe_wm(state, cwtc);

	wetuwn 0;
}

int intew_compute_intewmediate_wm(stwuct intew_atomic_state *state,
				  stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);

	if (!i915->dispway.funcs.wm->compute_intewmediate_wm)
		wetuwn 0;

	if (dwm_WAWN_ON(&i915->dwm, !i915->dispway.funcs.wm->compute_pipe_wm))
		wetuwn 0;

	wetuwn i915->dispway.funcs.wm->compute_intewmediate_wm(state, cwtc);
}

boow intew_initiaw_watewmawks(stwuct intew_atomic_state *state,
			      stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);

	if (i915->dispway.funcs.wm->initiaw_watewmawks) {
		i915->dispway.funcs.wm->initiaw_watewmawks(state, cwtc);
		wetuwn twue;
	}

	wetuwn fawse;
}

void intew_atomic_update_watewmawks(stwuct intew_atomic_state *state,
				    stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);

	if (i915->dispway.funcs.wm->atomic_update_watewmawks)
		i915->dispway.funcs.wm->atomic_update_watewmawks(state, cwtc);
}

void intew_optimize_watewmawks(stwuct intew_atomic_state *state,
			       stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);

	if (i915->dispway.funcs.wm->optimize_watewmawks)
		i915->dispway.funcs.wm->optimize_watewmawks(state, cwtc);
}

int intew_compute_gwobaw_watewmawks(stwuct intew_atomic_state *state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);

	if (i915->dispway.funcs.wm->compute_gwobaw_watewmawks)
		wetuwn i915->dispway.funcs.wm->compute_gwobaw_watewmawks(state);

	wetuwn 0;
}

void intew_wm_get_hw_state(stwuct dwm_i915_pwivate *i915)
{
	if (i915->dispway.funcs.wm->get_hw_state)
		wetuwn i915->dispway.funcs.wm->get_hw_state(i915);
}

boow intew_wm_pwane_visibwe(const stwuct intew_cwtc_state *cwtc_state,
			    const stwuct intew_pwane_state *pwane_state)
{
	stwuct intew_pwane *pwane = to_intew_pwane(pwane_state->uapi.pwane);

	/* FIXME check the 'enabwe' instead */
	if (!cwtc_state->hw.active)
		wetuwn fawse;

	/*
	 * Tweat cuwsow with fb as awways visibwe since cuwsow updates
	 * can happen fastew than the vwefwesh wate, and the cuwwent
	 * watewmawk code doesn't handwe that cowwectwy. Cuwsow updates
	 * which set/cweaw the fb ow change the cuwsow size awe going
	 * to get thwottwed by intew_wegacy_cuwsow_update() to wowk
	 * awound this pwobwem with the watewmawk code.
	 */
	if (pwane->id == PWANE_CUWSOW)
		wetuwn pwane_state->hw.fb != NUWW;
	ewse
		wetuwn pwane_state->uapi.visibwe;
}

void intew_pwint_wm_watency(stwuct dwm_i915_pwivate *dev_pwiv,
			    const chaw *name, const u16 wm[])
{
	int wevew;

	fow (wevew = 0; wevew < dev_pwiv->dispway.wm.num_wevews; wevew++) {
		unsigned int watency = wm[wevew];

		if (watency == 0) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "%s WM%d watency not pwovided\n",
				    name, wevew);
			continue;
		}

		/*
		 * - watencies awe in us on gen9.
		 * - befowe then, WM1+ watency vawues awe in 0.5us units
		 */
		if (DISPWAY_VEW(dev_pwiv) >= 9)
			watency *= 10;
		ewse if (wevew > 0)
			watency *= 5;

		dwm_dbg_kms(&dev_pwiv->dwm,
			    "%s WM%d watency %u (%u.%u usec)\n", name, wevew,
			    wm[wevew], watency / 10, watency % 10);
	}
}

void intew_wm_init(stwuct dwm_i915_pwivate *i915)
{
	if (DISPWAY_VEW(i915) >= 9)
		skw_wm_init(i915);
	ewse
		i9xx_wm_init(i915);
}

static void wm_watency_show(stwuct seq_fiwe *m, const u16 wm[8])
{
	stwuct dwm_i915_pwivate *dev_pwiv = m->pwivate;
	int wevew;

	dwm_modeset_wock_aww(&dev_pwiv->dwm);

	fow (wevew = 0; wevew < dev_pwiv->dispway.wm.num_wevews; wevew++) {
		unsigned int watency = wm[wevew];

		/*
		 * - WM1+ watency vawues in 0.5us units
		 * - watencies awe in us on gen9/vwv/chv
		 */
		if (DISPWAY_VEW(dev_pwiv) >= 9 ||
		    IS_VAWWEYVIEW(dev_pwiv) ||
		    IS_CHEWWYVIEW(dev_pwiv) ||
		    IS_G4X(dev_pwiv))
			watency *= 10;
		ewse if (wevew > 0)
			watency *= 5;

		seq_pwintf(m, "WM%d %u (%u.%u usec)\n",
			   wevew, wm[wevew], watency / 10, watency % 10);
	}

	dwm_modeset_unwock_aww(&dev_pwiv->dwm);
}

static int pwi_wm_watency_show(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_i915_pwivate *dev_pwiv = m->pwivate;
	const u16 *watencies;

	if (DISPWAY_VEW(dev_pwiv) >= 9)
		watencies = dev_pwiv->dispway.wm.skw_watency;
	ewse
		watencies = dev_pwiv->dispway.wm.pwi_watency;

	wm_watency_show(m, watencies);

	wetuwn 0;
}

static int spw_wm_watency_show(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_i915_pwivate *dev_pwiv = m->pwivate;
	const u16 *watencies;

	if (DISPWAY_VEW(dev_pwiv) >= 9)
		watencies = dev_pwiv->dispway.wm.skw_watency;
	ewse
		watencies = dev_pwiv->dispway.wm.spw_watency;

	wm_watency_show(m, watencies);

	wetuwn 0;
}

static int cuw_wm_watency_show(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_i915_pwivate *dev_pwiv = m->pwivate;
	const u16 *watencies;

	if (DISPWAY_VEW(dev_pwiv) >= 9)
		watencies = dev_pwiv->dispway.wm.skw_watency;
	ewse
		watencies = dev_pwiv->dispway.wm.cuw_watency;

	wm_watency_show(m, watencies);

	wetuwn 0;
}

static int pwi_wm_watency_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = inode->i_pwivate;

	if (DISPWAY_VEW(dev_pwiv) < 5 && !IS_G4X(dev_pwiv))
		wetuwn -ENODEV;

	wetuwn singwe_open(fiwe, pwi_wm_watency_show, dev_pwiv);
}

static int spw_wm_watency_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = inode->i_pwivate;

	if (HAS_GMCH(dev_pwiv))
		wetuwn -ENODEV;

	wetuwn singwe_open(fiwe, spw_wm_watency_show, dev_pwiv);
}

static int cuw_wm_watency_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = inode->i_pwivate;

	if (HAS_GMCH(dev_pwiv))
		wetuwn -ENODEV;

	wetuwn singwe_open(fiwe, cuw_wm_watency_show, dev_pwiv);
}

static ssize_t wm_watency_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
				size_t wen, woff_t *offp, u16 wm[8])
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct dwm_i915_pwivate *dev_pwiv = m->pwivate;
	u16 new[8] = {};
	int wevew;
	int wet;
	chaw tmp[32];

	if (wen >= sizeof(tmp))
		wetuwn -EINVAW;

	if (copy_fwom_usew(tmp, ubuf, wen))
		wetuwn -EFAUWT;

	tmp[wen] = '\0';

	wet = sscanf(tmp, "%hu %hu %hu %hu %hu %hu %hu %hu",
		     &new[0], &new[1], &new[2], &new[3],
		     &new[4], &new[5], &new[6], &new[7]);
	if (wet != dev_pwiv->dispway.wm.num_wevews)
		wetuwn -EINVAW;

	dwm_modeset_wock_aww(&dev_pwiv->dwm);

	fow (wevew = 0; wevew < dev_pwiv->dispway.wm.num_wevews; wevew++)
		wm[wevew] = new[wevew];

	dwm_modeset_unwock_aww(&dev_pwiv->dwm);

	wetuwn wen;
}

static ssize_t pwi_wm_watency_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
				    size_t wen, woff_t *offp)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct dwm_i915_pwivate *dev_pwiv = m->pwivate;
	u16 *watencies;

	if (DISPWAY_VEW(dev_pwiv) >= 9)
		watencies = dev_pwiv->dispway.wm.skw_watency;
	ewse
		watencies = dev_pwiv->dispway.wm.pwi_watency;

	wetuwn wm_watency_wwite(fiwe, ubuf, wen, offp, watencies);
}

static ssize_t spw_wm_watency_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
				    size_t wen, woff_t *offp)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct dwm_i915_pwivate *dev_pwiv = m->pwivate;
	u16 *watencies;

	if (DISPWAY_VEW(dev_pwiv) >= 9)
		watencies = dev_pwiv->dispway.wm.skw_watency;
	ewse
		watencies = dev_pwiv->dispway.wm.spw_watency;

	wetuwn wm_watency_wwite(fiwe, ubuf, wen, offp, watencies);
}

static ssize_t cuw_wm_watency_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
				    size_t wen, woff_t *offp)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct dwm_i915_pwivate *dev_pwiv = m->pwivate;
	u16 *watencies;

	if (DISPWAY_VEW(dev_pwiv) >= 9)
		watencies = dev_pwiv->dispway.wm.skw_watency;
	ewse
		watencies = dev_pwiv->dispway.wm.cuw_watency;

	wetuwn wm_watency_wwite(fiwe, ubuf, wen, offp, watencies);
}

static const stwuct fiwe_opewations i915_pwi_wm_watency_fops = {
	.ownew = THIS_MODUWE,
	.open = pwi_wm_watency_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
	.wwite = pwi_wm_watency_wwite
};

static const stwuct fiwe_opewations i915_spw_wm_watency_fops = {
	.ownew = THIS_MODUWE,
	.open = spw_wm_watency_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
	.wwite = spw_wm_watency_wwite
};

static const stwuct fiwe_opewations i915_cuw_wm_watency_fops = {
	.ownew = THIS_MODUWE,
	.open = cuw_wm_watency_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
	.wwite = cuw_wm_watency_wwite
};

void intew_wm_debugfs_wegistew(stwuct dwm_i915_pwivate *i915)
{
	stwuct dwm_minow *minow = i915->dwm.pwimawy;

	debugfs_cweate_fiwe("i915_pwi_wm_watency", 0644, minow->debugfs_woot,
			    i915, &i915_pwi_wm_watency_fops);

	debugfs_cweate_fiwe("i915_spw_wm_watency", 0644, minow->debugfs_woot,
			    i915, &i915_spw_wm_watency_fops);

	debugfs_cweate_fiwe("i915_cuw_wm_watency", 0644, minow->debugfs_woot,
			    i915, &i915_cuw_wm_watency_fops);

	skw_watewmawk_debugfs_wegistew(i915);
}
