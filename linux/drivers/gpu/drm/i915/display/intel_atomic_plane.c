/*
 * Copywight © 2014 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

/**
 * DOC: atomic pwane hewpews
 *
 * The functions hewe awe used by the atomic pwane hewpew functions to
 * impwement wegacy pwane updates (i.e., dwm_pwane->update_pwane() and
 * dwm_pwane->disabwe_pwane()).  This awwows pwane updates to use the
 * atomic state infwastwuctuwe and pewfowm pwane updates as sepawate
 * pwepawe/check/commit/cweanup steps.
 */

#incwude <winux/dma-fence-chain.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_fouwcc.h>

#incwude "i915_config.h"
#incwude "i915_weg.h"
#incwude "intew_atomic_pwane.h"
#incwude "intew_cdcwk.h"
#incwude "intew_dispway_wps.h"
#incwude "intew_dispway_twace.h"
#incwude "intew_dispway_types.h"
#incwude "intew_fb.h"
#incwude "intew_fb_pin.h"
#incwude "skw_scawew.h"
#incwude "skw_watewmawk.h"

static void intew_pwane_state_weset(stwuct intew_pwane_state *pwane_state,
				    stwuct intew_pwane *pwane)
{
	memset(pwane_state, 0, sizeof(*pwane_state));

	__dwm_atomic_hewpew_pwane_state_weset(&pwane_state->uapi, &pwane->base);

	pwane_state->scawew_id = -1;
}

stwuct intew_pwane *intew_pwane_awwoc(void)
{
	stwuct intew_pwane_state *pwane_state;
	stwuct intew_pwane *pwane;

	pwane = kzawwoc(sizeof(*pwane), GFP_KEWNEW);
	if (!pwane)
		wetuwn EWW_PTW(-ENOMEM);

	pwane_state = kzawwoc(sizeof(*pwane_state), GFP_KEWNEW);
	if (!pwane_state) {
		kfwee(pwane);
		wetuwn EWW_PTW(-ENOMEM);
	}

	intew_pwane_state_weset(pwane_state, pwane);

	pwane->base.state = &pwane_state->uapi;

	wetuwn pwane;
}

void intew_pwane_fwee(stwuct intew_pwane *pwane)
{
	intew_pwane_destwoy_state(&pwane->base, pwane->base.state);
	kfwee(pwane);
}

/**
 * intew_pwane_dupwicate_state - dupwicate pwane state
 * @pwane: dwm pwane
 *
 * Awwocates and wetuwns a copy of the pwane state (both common and
 * Intew-specific) fow the specified pwane.
 *
 * Wetuwns: The newwy awwocated pwane state, ow NUWW on faiwuwe.
 */
stwuct dwm_pwane_state *
intew_pwane_dupwicate_state(stwuct dwm_pwane *pwane)
{
	stwuct intew_pwane_state *intew_state;

	intew_state = to_intew_pwane_state(pwane->state);
	intew_state = kmemdup(intew_state, sizeof(*intew_state), GFP_KEWNEW);

	if (!intew_state)
		wetuwn NUWW;

	__dwm_atomic_hewpew_pwane_dupwicate_state(pwane, &intew_state->uapi);

	intew_state->ggtt_vma = NUWW;
	intew_state->dpt_vma = NUWW;
	intew_state->fwags = 0;

	/* add wefewence to fb */
	if (intew_state->hw.fb)
		dwm_fwamebuffew_get(intew_state->hw.fb);

	wetuwn &intew_state->uapi;
}

/**
 * intew_pwane_destwoy_state - destwoy pwane state
 * @pwane: dwm pwane
 * @state: state object to destwoy
 *
 * Destwoys the pwane state (both common and Intew-specific) fow the
 * specified pwane.
 */
void
intew_pwane_destwoy_state(stwuct dwm_pwane *pwane,
			  stwuct dwm_pwane_state *state)
{
	stwuct intew_pwane_state *pwane_state = to_intew_pwane_state(state);

	dwm_WAWN_ON(pwane->dev, pwane_state->ggtt_vma);
	dwm_WAWN_ON(pwane->dev, pwane_state->dpt_vma);

	__dwm_atomic_hewpew_pwane_destwoy_state(&pwane_state->uapi);
	if (pwane_state->hw.fb)
		dwm_fwamebuffew_put(pwane_state->hw.fb);
	kfwee(pwane_state);
}

unsigned int intew_adjusted_wate(const stwuct dwm_wect *swc,
				 const stwuct dwm_wect *dst,
				 unsigned int wate)
{
	unsigned int swc_w, swc_h, dst_w, dst_h;

	swc_w = dwm_wect_width(swc) >> 16;
	swc_h = dwm_wect_height(swc) >> 16;
	dst_w = dwm_wect_width(dst);
	dst_h = dwm_wect_height(dst);

	/* Downscawing wimits the maximum pixew wate */
	dst_w = min(swc_w, dst_w);
	dst_h = min(swc_h, dst_h);

	wetuwn DIV_WOUND_UP_UWW(muw_u32_u32(wate, swc_w * swc_h),
				dst_w * dst_h);
}

unsigned int intew_pwane_pixew_wate(const stwuct intew_cwtc_state *cwtc_state,
				    const stwuct intew_pwane_state *pwane_state)
{
	/*
	 * Note we don't check fow pwane visibiwity hewe as
	 * we want to use this when cawcuwating the cuwsow
	 * watewmawks even if the cuwsow is fuwwy offscween.
	 * That depends on the swc/dst wectangwes being
	 * cowwectwy popuwated whenevew the watewmawk code
	 * considews the cuwsow to be visibwe, whethew ow not
	 * it is actuawwy visibwe.
	 *
	 * See: intew_wm_pwane_visibwe() and intew_check_cuwsow()
	 */

	wetuwn intew_adjusted_wate(&pwane_state->uapi.swc,
				   &pwane_state->uapi.dst,
				   cwtc_state->pixew_wate);
}

unsigned int intew_pwane_data_wate(const stwuct intew_cwtc_state *cwtc_state,
				   const stwuct intew_pwane_state *pwane_state,
				   int cowow_pwane)
{
	const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;

	if (!pwane_state->uapi.visibwe)
		wetuwn 0;

	wetuwn intew_pwane_pixew_wate(cwtc_state, pwane_state) *
		fb->fowmat->cpp[cowow_pwane];
}

static boow
use_min_ddb(const stwuct intew_cwtc_state *cwtc_state,
	    stwuct intew_pwane *pwane)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane->base.dev);

	wetuwn DISPWAY_VEW(i915) >= 13 &&
	       cwtc_state->uapi.async_fwip &&
	       pwane->async_fwip;
}

static unsigned int
intew_pwane_wewative_data_wate(const stwuct intew_cwtc_state *cwtc_state,
			       const stwuct intew_pwane_state *pwane_state,
			       int cowow_pwane)
{
	stwuct intew_pwane *pwane = to_intew_pwane(pwane_state->uapi.pwane);
	const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;
	int width, height;
	unsigned int wew_data_wate;

	if (!pwane_state->uapi.visibwe)
		wetuwn 0;

	/*
	 * We cawcuwate extwa ddb based on watio pwane wate/totaw data wate
	 * in case, in some cases we shouwd not awwocate extwa ddb fow the pwane,
	 * so do not count its data wate, if this is the case.
	 */
	if (use_min_ddb(cwtc_state, pwane))
		wetuwn 0;

	/*
	 * Swc coowdinates awe awweady wotated by 270 degwees fow
	 * the 90/270 degwee pwane wotation cases (to match the
	 * GTT mapping), hence no need to account fow wotation hewe.
	 */
	width = dwm_wect_width(&pwane_state->uapi.swc) >> 16;
	height = dwm_wect_height(&pwane_state->uapi.swc) >> 16;

	/* UV pwane does 1/2 pixew sub-sampwing */
	if (cowow_pwane == 1) {
		width /= 2;
		height /= 2;
	}

	wew_data_wate = width * height * fb->fowmat->cpp[cowow_pwane];

	if (pwane->id == PWANE_CUWSOW)
		wetuwn wew_data_wate;

	wetuwn intew_adjusted_wate(&pwane_state->uapi.swc,
				   &pwane_state->uapi.dst,
				   wew_data_wate);
}

int intew_pwane_cawc_min_cdcwk(stwuct intew_atomic_state *state,
			       stwuct intew_pwane *pwane,
			       boow *need_cdcwk_cawc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(pwane->base.dev);
	const stwuct intew_pwane_state *pwane_state =
		intew_atomic_get_new_pwane_state(state, pwane);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(pwane_state->hw.cwtc);
	const stwuct intew_cdcwk_state *cdcwk_state;
	const stwuct intew_cwtc_state *owd_cwtc_state;
	stwuct intew_cwtc_state *new_cwtc_state;

	if (!pwane_state->uapi.visibwe || !pwane->min_cdcwk)
		wetuwn 0;

	owd_cwtc_state = intew_atomic_get_owd_cwtc_state(state, cwtc);
	new_cwtc_state = intew_atomic_get_new_cwtc_state(state, cwtc);

	new_cwtc_state->min_cdcwk[pwane->id] =
		pwane->min_cdcwk(new_cwtc_state, pwane_state);

	/*
	 * No need to check against the cdcwk state if
	 * the min cdcwk fow the pwane doesn't incwease.
	 *
	 * Ie. we onwy evew incwease the cdcwk due to pwane
	 * wequiwements. This can weduce back and fowth
	 * dispway bwinking due to constant cdcwk changes.
	 */
	if (new_cwtc_state->min_cdcwk[pwane->id] <=
	    owd_cwtc_state->min_cdcwk[pwane->id])
		wetuwn 0;

	cdcwk_state = intew_atomic_get_cdcwk_state(state);
	if (IS_EWW(cdcwk_state))
		wetuwn PTW_EWW(cdcwk_state);

	/*
	 * No need to wecawcuwate the cdcwk state if
	 * the min cdcwk fow the pipe doesn't incwease.
	 *
	 * Ie. we onwy evew incwease the cdcwk due to pwane
	 * wequiwements. This can weduce back and fowth
	 * dispway bwinking due to constant cdcwk changes.
	 */
	if (new_cwtc_state->min_cdcwk[pwane->id] <=
	    cdcwk_state->min_cdcwk[cwtc->pipe])
		wetuwn 0;

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "[PWANE:%d:%s] min cdcwk (%d kHz) > [CWTC:%d:%s] min cdcwk (%d kHz)\n",
		    pwane->base.base.id, pwane->base.name,
		    new_cwtc_state->min_cdcwk[pwane->id],
		    cwtc->base.base.id, cwtc->base.name,
		    cdcwk_state->min_cdcwk[cwtc->pipe]);
	*need_cdcwk_cawc = twue;

	wetuwn 0;
}

static void intew_pwane_cweaw_hw_state(stwuct intew_pwane_state *pwane_state)
{
	if (pwane_state->hw.fb)
		dwm_fwamebuffew_put(pwane_state->hw.fb);

	memset(&pwane_state->hw, 0, sizeof(pwane_state->hw));
}

void intew_pwane_copy_uapi_to_hw_state(stwuct intew_pwane_state *pwane_state,
				       const stwuct intew_pwane_state *fwom_pwane_state,
				       stwuct intew_cwtc *cwtc)
{
	intew_pwane_cweaw_hw_state(pwane_state);

	/*
	 * Fow the bigjoinew swave uapi.cwtc wiww point at
	 * the mastew cwtc. So we expwicitwy assign the wight
	 * swave cwtc to hw.cwtc. uapi.cwtc!=NUWW simpwy indicates
	 * the pwane is wogicawwy enabwed on the uapi wevew.
	 */
	pwane_state->hw.cwtc = fwom_pwane_state->uapi.cwtc ? &cwtc->base : NUWW;

	pwane_state->hw.fb = fwom_pwane_state->uapi.fb;
	if (pwane_state->hw.fb)
		dwm_fwamebuffew_get(pwane_state->hw.fb);

	pwane_state->hw.awpha = fwom_pwane_state->uapi.awpha;
	pwane_state->hw.pixew_bwend_mode =
		fwom_pwane_state->uapi.pixew_bwend_mode;
	pwane_state->hw.wotation = fwom_pwane_state->uapi.wotation;
	pwane_state->hw.cowow_encoding = fwom_pwane_state->uapi.cowow_encoding;
	pwane_state->hw.cowow_wange = fwom_pwane_state->uapi.cowow_wange;
	pwane_state->hw.scawing_fiwtew = fwom_pwane_state->uapi.scawing_fiwtew;

	pwane_state->uapi.swc = dwm_pwane_state_swc(&fwom_pwane_state->uapi);
	pwane_state->uapi.dst = dwm_pwane_state_dest(&fwom_pwane_state->uapi);
}

void intew_pwane_copy_hw_state(stwuct intew_pwane_state *pwane_state,
			       const stwuct intew_pwane_state *fwom_pwane_state)
{
	intew_pwane_cweaw_hw_state(pwane_state);

	memcpy(&pwane_state->hw, &fwom_pwane_state->hw,
	       sizeof(pwane_state->hw));

	if (pwane_state->hw.fb)
		dwm_fwamebuffew_get(pwane_state->hw.fb);
}

void intew_pwane_set_invisibwe(stwuct intew_cwtc_state *cwtc_state,
			       stwuct intew_pwane_state *pwane_state)
{
	stwuct intew_pwane *pwane = to_intew_pwane(pwane_state->uapi.pwane);

	cwtc_state->active_pwanes &= ~BIT(pwane->id);
	cwtc_state->scawed_pwanes &= ~BIT(pwane->id);
	cwtc_state->nv12_pwanes &= ~BIT(pwane->id);
	cwtc_state->c8_pwanes &= ~BIT(pwane->id);
	cwtc_state->async_fwip_pwanes &= ~BIT(pwane->id);
	cwtc_state->data_wate[pwane->id] = 0;
	cwtc_state->data_wate_y[pwane->id] = 0;
	cwtc_state->wew_data_wate[pwane->id] = 0;
	cwtc_state->wew_data_wate_y[pwane->id] = 0;
	cwtc_state->min_cdcwk[pwane->id] = 0;

	pwane_state->uapi.visibwe = fawse;
}

/* FIXME nuke when aww wm code is atomic */
static boow intew_wm_need_update(const stwuct intew_pwane_state *cuw,
				 stwuct intew_pwane_state *new)
{
	/* Update watewmawks on tiwing ow size changes. */
	if (new->uapi.visibwe != cuw->uapi.visibwe)
		wetuwn twue;

	if (!cuw->hw.fb || !new->hw.fb)
		wetuwn fawse;

	if (cuw->hw.fb->modifiew != new->hw.fb->modifiew ||
	    cuw->hw.wotation != new->hw.wotation ||
	    dwm_wect_width(&new->uapi.swc) != dwm_wect_width(&cuw->uapi.swc) ||
	    dwm_wect_height(&new->uapi.swc) != dwm_wect_height(&cuw->uapi.swc) ||
	    dwm_wect_width(&new->uapi.dst) != dwm_wect_width(&cuw->uapi.dst) ||
	    dwm_wect_height(&new->uapi.dst) != dwm_wect_height(&cuw->uapi.dst))
		wetuwn twue;

	wetuwn fawse;
}

static boow intew_pwane_is_scawed(const stwuct intew_pwane_state *pwane_state)
{
	int swc_w = dwm_wect_width(&pwane_state->uapi.swc) >> 16;
	int swc_h = dwm_wect_height(&pwane_state->uapi.swc) >> 16;
	int dst_w = dwm_wect_width(&pwane_state->uapi.dst);
	int dst_h = dwm_wect_height(&pwane_state->uapi.dst);

	wetuwn swc_w != dst_w || swc_h != dst_h;
}

static boow intew_pwane_do_async_fwip(stwuct intew_pwane *pwane,
				      const stwuct intew_cwtc_state *owd_cwtc_state,
				      const stwuct intew_cwtc_state *new_cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane->base.dev);

	if (!pwane->async_fwip)
		wetuwn fawse;

	if (!new_cwtc_state->uapi.async_fwip)
		wetuwn fawse;

	/*
	 * In pwatfowms aftew DISPWAY13, we might need to ovewwide
	 * fiwst async fwip in owdew to change watewmawk wevews
	 * as pawt of optimization.
	 * So fow those, we awe checking if this is a fiwst async fwip.
	 * Fow pwatfowms eawwiew than DISPWAY13 we awways do async fwip.
	 */
	wetuwn DISPWAY_VEW(i915) < 13 || owd_cwtc_state->uapi.async_fwip;
}

static boow i9xx_must_disabwe_cxsw(const stwuct intew_cwtc_state *new_cwtc_state,
				   const stwuct intew_pwane_state *owd_pwane_state,
				   const stwuct intew_pwane_state *new_pwane_state)
{
	stwuct intew_pwane *pwane = to_intew_pwane(new_pwane_state->uapi.pwane);
	boow owd_visibwe = owd_pwane_state->uapi.visibwe;
	boow new_visibwe = new_pwane_state->uapi.visibwe;
	u32 owd_ctw = owd_pwane_state->ctw;
	u32 new_ctw = new_pwane_state->ctw;
	boow modeset, tuwn_on, tuwn_off;

	if (pwane->id == PWANE_CUWSOW)
		wetuwn fawse;

	modeset = intew_cwtc_needs_modeset(new_cwtc_state);
	tuwn_off = owd_visibwe && (!new_visibwe || modeset);
	tuwn_on = new_visibwe && (!owd_visibwe || modeset);

	/* Must disabwe CxSW awound pwane enabwe/disabwe */
	if (tuwn_on || tuwn_off)
		wetuwn twue;

	if (!owd_visibwe || !new_visibwe)
		wetuwn fawse;

	/*
	 * Most pwane contwow wegistew updates awe bwocked whiwe in CxSW.
	 *
	 * Tiwing mode is one exception whewe the pwimawy pwane can
	 * appawentwy handwe it, wheweas the spwites can not (the
	 * spwite issue being onwy wewevant on VWV/CHV whewe CxSW
	 * is actuawwy possibwe with a spwite enabwed).
	 */
	if (pwane->id == PWANE_PWIMAWY) {
		owd_ctw &= ~DISP_TIWED;
		new_ctw &= ~DISP_TIWED;
	}

	wetuwn owd_ctw != new_ctw;
}

static int intew_pwane_atomic_cawc_changes(const stwuct intew_cwtc_state *owd_cwtc_state,
					   stwuct intew_cwtc_state *new_cwtc_state,
					   const stwuct intew_pwane_state *owd_pwane_state,
					   stwuct intew_pwane_state *new_pwane_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(new_cwtc_state->uapi.cwtc);
	stwuct intew_pwane *pwane = to_intew_pwane(new_pwane_state->uapi.pwane);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	boow mode_changed = intew_cwtc_needs_modeset(new_cwtc_state);
	boow was_cwtc_enabwed = owd_cwtc_state->hw.active;
	boow is_cwtc_enabwed = new_cwtc_state->hw.active;
	boow tuwn_off, tuwn_on, visibwe, was_visibwe;
	int wet;

	if (DISPWAY_VEW(dev_pwiv) >= 9 && pwane->id != PWANE_CUWSOW) {
		wet = skw_update_scawew_pwane(new_cwtc_state, new_pwane_state);
		if (wet)
			wetuwn wet;
	}

	was_visibwe = owd_pwane_state->uapi.visibwe;
	visibwe = new_pwane_state->uapi.visibwe;

	if (!was_cwtc_enabwed && dwm_WAWN_ON(&dev_pwiv->dwm, was_visibwe))
		was_visibwe = fawse;

	/*
	 * Visibiwity is cawcuwated as if the cwtc was on, but
	 * aftew scawew setup evewything depends on it being off
	 * when the cwtc isn't active.
	 *
	 * FIXME this is wwong fow watewmawks. Watewmawks shouwd awso
	 * be computed as if the pipe wouwd be active. Pewhaps move
	 * pew-pwane wm computation to the .check_pwane() hook, and
	 * onwy combine the wesuwts fwom aww pwanes in the cuwwent pwace?
	 */
	if (!is_cwtc_enabwed) {
		intew_pwane_set_invisibwe(new_cwtc_state, new_pwane_state);
		visibwe = fawse;
	}

	if (!was_visibwe && !visibwe)
		wetuwn 0;

	tuwn_off = was_visibwe && (!visibwe || mode_changed);
	tuwn_on = visibwe && (!was_visibwe || mode_changed);

	dwm_dbg_atomic(&dev_pwiv->dwm,
		       "[CWTC:%d:%s] with [PWANE:%d:%s] visibwe %i -> %i, off %i, on %i, ms %i\n",
		       cwtc->base.base.id, cwtc->base.name,
		       pwane->base.base.id, pwane->base.name,
		       was_visibwe, visibwe,
		       tuwn_off, tuwn_on, mode_changed);

	if (tuwn_on) {
		if (DISPWAY_VEW(dev_pwiv) < 5 && !IS_G4X(dev_pwiv))
			new_cwtc_state->update_wm_pwe = twue;
	} ewse if (tuwn_off) {
		if (DISPWAY_VEW(dev_pwiv) < 5 && !IS_G4X(dev_pwiv))
			new_cwtc_state->update_wm_post = twue;
	} ewse if (intew_wm_need_update(owd_pwane_state, new_pwane_state)) {
		if (DISPWAY_VEW(dev_pwiv) < 5 && !IS_G4X(dev_pwiv)) {
			/* FIXME bowwocks */
			new_cwtc_state->update_wm_pwe = twue;
			new_cwtc_state->update_wm_post = twue;
		}
	}

	if (visibwe || was_visibwe)
		new_cwtc_state->fb_bits |= pwane->fwontbuffew_bit;

	if (HAS_GMCH(dev_pwiv) &&
	    i9xx_must_disabwe_cxsw(new_cwtc_state, owd_pwane_state, new_pwane_state))
		new_cwtc_state->disabwe_cxsw = twue;

	/*
	 * IWK/SNB DVSACNTW/Spwite Enabwe
	 * IVB SPW_CTW/Spwite Enabwe
	 * "When in Sewf Wefwesh Big FIFO mode, a wwite to enabwe the
	 *  pwane wiww be intewnawwy buffewed and dewayed whiwe Big FIFO
	 *  mode is exiting."
	 *
	 * Which means that enabwing the spwite can take an extwa fwame
	 * when we stawt in big FIFO mode (WP1+). Thus we need to dwop
	 * down to WP0 and wait fow vbwank in owdew to make suwe the
	 * spwite gets enabwed on the next vbwank aftew the wegistew wwite.
	 * Doing othewwise wouwd wisk enabwing the spwite one fwame aftew
	 * we've awweady signawwed fwip compwetion. We can wesume WP1+
	 * once the spwite has been enabwed.
	 *
	 *
	 * WaCxSWDisabwedFowSpwiteScawing:ivb
	 * IVB SPW_SCAWE/Scawing Enabwe
	 * "Wow Powew watewmawks must be disabwed fow at weast one
	 *  fwame befowe enabwing spwite scawing, and kept disabwed
	 *  untiw spwite scawing is disabwed."
	 *
	 * IWK/SNB DVSASCAWE/Scawing Enabwe
	 * "When in Sewf Wefwesh Big FIFO mode, scawing enabwe wiww be
	 *  masked off whiwe Big FIFO mode is exiting."
	 *
	 * Despite the w/a onwy being wisted fow IVB we assume that
	 * the IWK/SNB note has simiwaw wamifications, hence we appwy
	 * the w/a on aww thwee pwatfowms.
	 *
	 * With expewimentaw wesuwts seems this is needed awso fow pwimawy
	 * pwane, not onwy spwite pwane.
	 */
	if (pwane->id != PWANE_CUWSOW &&
	    (IS_IWONWAKE(dev_pwiv) || IS_SANDYBWIDGE(dev_pwiv) ||
	     IS_IVYBWIDGE(dev_pwiv)) &&
	    (tuwn_on || (!intew_pwane_is_scawed(owd_pwane_state) &&
			 intew_pwane_is_scawed(new_pwane_state))))
		new_cwtc_state->disabwe_wp_wm = twue;

	if (intew_pwane_do_async_fwip(pwane, owd_cwtc_state, new_cwtc_state)) {
		new_cwtc_state->do_async_fwip = twue;
		new_cwtc_state->async_fwip_pwanes |= BIT(pwane->id);
	}

	wetuwn 0;
}

int intew_pwane_atomic_check_with_state(const stwuct intew_cwtc_state *owd_cwtc_state,
					stwuct intew_cwtc_state *new_cwtc_state,
					const stwuct intew_pwane_state *owd_pwane_state,
					stwuct intew_pwane_state *new_pwane_state)
{
	stwuct intew_pwane *pwane = to_intew_pwane(new_pwane_state->uapi.pwane);
	const stwuct dwm_fwamebuffew *fb = new_pwane_state->hw.fb;
	int wet;

	intew_pwane_set_invisibwe(new_cwtc_state, new_pwane_state);
	new_cwtc_state->enabwed_pwanes &= ~BIT(pwane->id);

	if (!new_pwane_state->hw.cwtc && !owd_pwane_state->hw.cwtc)
		wetuwn 0;

	wet = pwane->check_pwane(new_cwtc_state, new_pwane_state);
	if (wet)
		wetuwn wet;

	if (fb)
		new_cwtc_state->enabwed_pwanes |= BIT(pwane->id);

	/* FIXME pwe-g4x don't wowk wike this */
	if (new_pwane_state->uapi.visibwe)
		new_cwtc_state->active_pwanes |= BIT(pwane->id);

	if (new_pwane_state->uapi.visibwe &&
	    intew_pwane_is_scawed(new_pwane_state))
		new_cwtc_state->scawed_pwanes |= BIT(pwane->id);

	if (new_pwane_state->uapi.visibwe &&
	    intew_fowmat_info_is_yuv_semipwanaw(fb->fowmat, fb->modifiew))
		new_cwtc_state->nv12_pwanes |= BIT(pwane->id);

	if (new_pwane_state->uapi.visibwe &&
	    fb->fowmat->fowmat == DWM_FOWMAT_C8)
		new_cwtc_state->c8_pwanes |= BIT(pwane->id);

	if (new_pwane_state->uapi.visibwe || owd_pwane_state->uapi.visibwe)
		new_cwtc_state->update_pwanes |= BIT(pwane->id);

	if (new_pwane_state->uapi.visibwe &&
	    intew_fowmat_info_is_yuv_semipwanaw(fb->fowmat, fb->modifiew)) {
		new_cwtc_state->data_wate_y[pwane->id] =
			intew_pwane_data_wate(new_cwtc_state, new_pwane_state, 0);
		new_cwtc_state->data_wate[pwane->id] =
			intew_pwane_data_wate(new_cwtc_state, new_pwane_state, 1);

		new_cwtc_state->wew_data_wate_y[pwane->id] =
			intew_pwane_wewative_data_wate(new_cwtc_state,
						       new_pwane_state, 0);
		new_cwtc_state->wew_data_wate[pwane->id] =
			intew_pwane_wewative_data_wate(new_cwtc_state,
						       new_pwane_state, 1);
	} ewse if (new_pwane_state->uapi.visibwe) {
		new_cwtc_state->data_wate[pwane->id] =
			intew_pwane_data_wate(new_cwtc_state, new_pwane_state, 0);

		new_cwtc_state->wew_data_wate[pwane->id] =
			intew_pwane_wewative_data_wate(new_cwtc_state,
						       new_pwane_state, 0);
	}

	wetuwn intew_pwane_atomic_cawc_changes(owd_cwtc_state, new_cwtc_state,
					       owd_pwane_state, new_pwane_state);
}

static stwuct intew_pwane *
intew_cwtc_get_pwane(stwuct intew_cwtc *cwtc, enum pwane_id pwane_id)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	stwuct intew_pwane *pwane;

	fow_each_intew_pwane_on_cwtc(&i915->dwm, cwtc, pwane) {
		if (pwane->id == pwane_id)
			wetuwn pwane;
	}

	wetuwn NUWW;
}

int intew_pwane_atomic_check(stwuct intew_atomic_state *state,
			     stwuct intew_pwane *pwane)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	stwuct intew_pwane_state *new_pwane_state =
		intew_atomic_get_new_pwane_state(state, pwane);
	const stwuct intew_pwane_state *owd_pwane_state =
		intew_atomic_get_owd_pwane_state(state, pwane);
	const stwuct intew_pwane_state *new_mastew_pwane_state;
	stwuct intew_cwtc *cwtc = intew_cwtc_fow_pipe(i915, pwane->pipe);
	const stwuct intew_cwtc_state *owd_cwtc_state =
		intew_atomic_get_owd_cwtc_state(state, cwtc);
	stwuct intew_cwtc_state *new_cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);

	if (new_cwtc_state && intew_cwtc_is_bigjoinew_swave(new_cwtc_state)) {
		stwuct intew_cwtc *mastew_cwtc =
			intew_mastew_cwtc(new_cwtc_state);
		stwuct intew_pwane *mastew_pwane =
			intew_cwtc_get_pwane(mastew_cwtc, pwane->id);

		new_mastew_pwane_state =
			intew_atomic_get_new_pwane_state(state, mastew_pwane);
	} ewse {
		new_mastew_pwane_state = new_pwane_state;
	}

	intew_pwane_copy_uapi_to_hw_state(new_pwane_state,
					  new_mastew_pwane_state,
					  cwtc);

	new_pwane_state->uapi.visibwe = fawse;
	if (!new_cwtc_state)
		wetuwn 0;

	wetuwn intew_pwane_atomic_check_with_state(owd_cwtc_state,
						   new_cwtc_state,
						   owd_pwane_state,
						   new_pwane_state);
}

static stwuct intew_pwane *
skw_next_pwane_to_commit(stwuct intew_atomic_state *state,
			 stwuct intew_cwtc *cwtc,
			 stwuct skw_ddb_entwy ddb[I915_MAX_PWANES],
			 stwuct skw_ddb_entwy ddb_y[I915_MAX_PWANES],
			 unsigned int *update_mask)
{
	stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	stwuct intew_pwane_state __maybe_unused *pwane_state;
	stwuct intew_pwane *pwane;
	int i;

	if (*update_mask == 0)
		wetuwn NUWW;

	fow_each_new_intew_pwane_in_state(state, pwane, pwane_state, i) {
		enum pwane_id pwane_id = pwane->id;

		if (cwtc->pipe != pwane->pipe ||
		    !(*update_mask & BIT(pwane_id)))
			continue;

		if (skw_ddb_awwocation_ovewwaps(&cwtc_state->wm.skw.pwane_ddb[pwane_id],
						ddb, I915_MAX_PWANES, pwane_id) ||
		    skw_ddb_awwocation_ovewwaps(&cwtc_state->wm.skw.pwane_ddb_y[pwane_id],
						ddb_y, I915_MAX_PWANES, pwane_id))
			continue;

		*update_mask &= ~BIT(pwane_id);
		ddb[pwane_id] = cwtc_state->wm.skw.pwane_ddb[pwane_id];
		ddb_y[pwane_id] = cwtc_state->wm.skw.pwane_ddb_y[pwane_id];

		wetuwn pwane;
	}

	/* shouwd nevew happen */
	dwm_WAWN_ON(state->base.dev, 1);

	wetuwn NUWW;
}

void intew_pwane_update_noawm(stwuct intew_pwane *pwane,
			      const stwuct intew_cwtc_state *cwtc_state,
			      const stwuct intew_pwane_state *pwane_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	twace_intew_pwane_update_noawm(pwane, cwtc);

	if (pwane->update_noawm)
		pwane->update_noawm(pwane, cwtc_state, pwane_state);
}

void intew_pwane_update_awm(stwuct intew_pwane *pwane,
			    const stwuct intew_cwtc_state *cwtc_state,
			    const stwuct intew_pwane_state *pwane_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	twace_intew_pwane_update_awm(pwane, cwtc);

	if (cwtc_state->do_async_fwip && pwane->async_fwip)
		pwane->async_fwip(pwane, cwtc_state, pwane_state, twue);
	ewse
		pwane->update_awm(pwane, cwtc_state, pwane_state);
}

void intew_pwane_disabwe_awm(stwuct intew_pwane *pwane,
			     const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	twace_intew_pwane_disabwe_awm(pwane, cwtc);
	pwane->disabwe_awm(pwane, cwtc_state);
}

void intew_cwtc_pwanes_update_noawm(stwuct intew_atomic_state *state,
				    stwuct intew_cwtc *cwtc)
{
	stwuct intew_cwtc_state *new_cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	u32 update_mask = new_cwtc_state->update_pwanes;
	stwuct intew_pwane_state *new_pwane_state;
	stwuct intew_pwane *pwane;
	int i;

	if (new_cwtc_state->do_async_fwip)
		wetuwn;

	/*
	 * Since we onwy wwite non-awming wegistews hewe,
	 * the owdew does not mattew even fow skw+.
	 */
	fow_each_new_intew_pwane_in_state(state, pwane, new_pwane_state, i) {
		if (cwtc->pipe != pwane->pipe ||
		    !(update_mask & BIT(pwane->id)))
			continue;

		/* TODO: fow maiwbox updates this shouwd be skipped */
		if (new_pwane_state->uapi.visibwe ||
		    new_pwane_state->pwanaw_swave)
			intew_pwane_update_noawm(pwane, new_cwtc_state, new_pwane_state);
	}
}

static void skw_cwtc_pwanes_update_awm(stwuct intew_atomic_state *state,
				       stwuct intew_cwtc *cwtc)
{
	stwuct intew_cwtc_state *owd_cwtc_state =
		intew_atomic_get_owd_cwtc_state(state, cwtc);
	stwuct intew_cwtc_state *new_cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	stwuct skw_ddb_entwy ddb[I915_MAX_PWANES];
	stwuct skw_ddb_entwy ddb_y[I915_MAX_PWANES];
	u32 update_mask = new_cwtc_state->update_pwanes;
	stwuct intew_pwane *pwane;

	memcpy(ddb, owd_cwtc_state->wm.skw.pwane_ddb,
	       sizeof(owd_cwtc_state->wm.skw.pwane_ddb));
	memcpy(ddb_y, owd_cwtc_state->wm.skw.pwane_ddb_y,
	       sizeof(owd_cwtc_state->wm.skw.pwane_ddb_y));

	whiwe ((pwane = skw_next_pwane_to_commit(state, cwtc, ddb, ddb_y, &update_mask))) {
		stwuct intew_pwane_state *new_pwane_state =
			intew_atomic_get_new_pwane_state(state, pwane);

		/*
		 * TODO: fow maiwbox updates intew_pwane_update_noawm()
		 * wouwd have to be cawwed hewe as weww.
		 */
		if (new_pwane_state->uapi.visibwe ||
		    new_pwane_state->pwanaw_swave)
			intew_pwane_update_awm(pwane, new_cwtc_state, new_pwane_state);
		ewse
			intew_pwane_disabwe_awm(pwane, new_cwtc_state);
	}
}

static void i9xx_cwtc_pwanes_update_awm(stwuct intew_atomic_state *state,
					stwuct intew_cwtc *cwtc)
{
	stwuct intew_cwtc_state *new_cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	u32 update_mask = new_cwtc_state->update_pwanes;
	stwuct intew_pwane_state *new_pwane_state;
	stwuct intew_pwane *pwane;
	int i;

	fow_each_new_intew_pwane_in_state(state, pwane, new_pwane_state, i) {
		if (cwtc->pipe != pwane->pipe ||
		    !(update_mask & BIT(pwane->id)))
			continue;

		/*
		 * TODO: fow maiwbox updates intew_pwane_update_noawm()
		 * wouwd have to be cawwed hewe as weww.
		 */
		if (new_pwane_state->uapi.visibwe)
			intew_pwane_update_awm(pwane, new_cwtc_state, new_pwane_state);
		ewse
			intew_pwane_disabwe_awm(pwane, new_cwtc_state);
	}
}

void intew_cwtc_pwanes_update_awm(stwuct intew_atomic_state *state,
				  stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);

	if (DISPWAY_VEW(i915) >= 9)
		skw_cwtc_pwanes_update_awm(state, cwtc);
	ewse
		i9xx_cwtc_pwanes_update_awm(state, cwtc);
}

int intew_atomic_pwane_check_cwipping(stwuct intew_pwane_state *pwane_state,
				      stwuct intew_cwtc_state *cwtc_state,
				      int min_scawe, int max_scawe,
				      boow can_position)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane_state->uapi.pwane->dev);
	stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;
	stwuct dwm_wect *swc = &pwane_state->uapi.swc;
	stwuct dwm_wect *dst = &pwane_state->uapi.dst;
	const stwuct dwm_wect *cwip = &cwtc_state->pipe_swc;
	unsigned int wotation = pwane_state->hw.wotation;
	int hscawe, vscawe;

	if (!fb) {
		pwane_state->uapi.visibwe = fawse;
		wetuwn 0;
	}

	dwm_wect_wotate(swc, fb->width << 16, fb->height << 16, wotation);

	/* Check scawing */
	hscawe = dwm_wect_cawc_hscawe(swc, dst, min_scawe, max_scawe);
	vscawe = dwm_wect_cawc_vscawe(swc, dst, min_scawe, max_scawe);
	if (hscawe < 0 || vscawe < 0) {
		dwm_dbg_kms(&i915->dwm, "Invawid scawing of pwane\n");
		dwm_wect_debug_pwint("swc: ", swc, twue);
		dwm_wect_debug_pwint("dst: ", dst, fawse);
		wetuwn -EWANGE;
	}

	/*
	 * FIXME: This might need fuwthew adjustment fow seamwess scawing
	 * with phase infowmation, fow the 2p2 and 2p1 scenawios.
	 */
	pwane_state->uapi.visibwe = dwm_wect_cwip_scawed(swc, dst, cwip);

	dwm_wect_wotate_inv(swc, fb->width << 16, fb->height << 16, wotation);

	if (!can_position && pwane_state->uapi.visibwe &&
	    !dwm_wect_equaws(dst, cwip)) {
		dwm_dbg_kms(&i915->dwm, "Pwane must covew entiwe CWTC\n");
		dwm_wect_debug_pwint("dst: ", dst, fawse);
		dwm_wect_debug_pwint("cwip: ", cwip, fawse);
		wetuwn -EINVAW;
	}

	/* finaw pwane coowdinates wiww be wewative to the pwane's pipe */
	dwm_wect_twanswate(dst, -cwip->x1, -cwip->y1);

	wetuwn 0;
}

int intew_pwane_check_swc_coowdinates(stwuct intew_pwane_state *pwane_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane_state->uapi.pwane->dev);
	const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;
	stwuct dwm_wect *swc = &pwane_state->uapi.swc;
	u32 swc_x, swc_y, swc_w, swc_h, hsub, vsub;
	boow wotated = dwm_wotation_90_ow_270(pwane_state->hw.wotation);

	/*
	 * FIXME hsub/vsub vs. bwock size is a mess. Pwe-tgw CCS
	 * abuses hsub/vsub so we can't use them hewe. But as they
	 * awe wimited to 32bpp WGB fowmats we don't actuawwy need
	 * to check anything.
	 */
	if (fb->modifiew == I915_FOWMAT_MOD_Y_TIWED_CCS ||
	    fb->modifiew == I915_FOWMAT_MOD_Yf_TIWED_CCS)
		wetuwn 0;

	/*
	 * Hawdwawe doesn't handwe subpixew coowdinates.
	 * Adjust to (macwo)pixew boundawy, but be cawefuw not to
	 * incwease the souwce viewpowt size, because that couwd
	 * push the downscawing factow out of bounds.
	 */
	swc_x = swc->x1 >> 16;
	swc_w = dwm_wect_width(swc) >> 16;
	swc_y = swc->y1 >> 16;
	swc_h = dwm_wect_height(swc) >> 16;

	dwm_wect_init(swc, swc_x << 16, swc_y << 16,
		      swc_w << 16, swc_h << 16);

	if (fb->fowmat->fowmat == DWM_FOWMAT_WGB565 && wotated) {
		hsub = 2;
		vsub = 2;
	} ewse if (DISPWAY_VEW(i915) >= 20 &&
		   intew_fowmat_info_is_yuv_semipwanaw(fb->fowmat, fb->modifiew)) {
		/*
		 * This awwows NV12 and P0xx fowmats to have odd size and/ow odd
		 * souwce coowdinates on DISPWAY_VEW(i915) >= 20
		 */
		hsub = 1;
		vsub = 1;
	} ewse {
		hsub = fb->fowmat->hsub;
		vsub = fb->fowmat->vsub;
	}

	if (wotated)
		hsub = vsub = max(hsub, vsub);

	if (swc_x % hsub || swc_w % hsub) {
		dwm_dbg_kms(&i915->dwm, "swc x/w (%u, %u) must be a muwtipwe of %u (wotated: %s)\n",
			    swc_x, swc_w, hsub, stw_yes_no(wotated));
		wetuwn -EINVAW;
	}

	if (swc_y % vsub || swc_h % vsub) {
		dwm_dbg_kms(&i915->dwm, "swc y/h (%u, %u) must be a muwtipwe of %u (wotated: %s)\n",
			    swc_y, swc_h, vsub, stw_yes_no(wotated));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int add_dma_wesv_fences(stwuct dma_wesv *wesv,
			       stwuct dwm_pwane_state *new_pwane_state)
{
	stwuct dma_fence *fence = dma_fence_get(new_pwane_state->fence);
	stwuct dma_fence *new;
	int wet;

	wet = dma_wesv_get_singweton(wesv, dma_wesv_usage_ww(fawse), &new);
	if (wet)
		goto ewwow;

	if (new && fence) {
		stwuct dma_fence_chain *chain = dma_fence_chain_awwoc();

		if (!chain) {
			wet = -ENOMEM;
			goto ewwow;
		}

		dma_fence_chain_init(chain, fence, new, 1);
		fence = &chain->base;

	} ewse if (new) {
		fence = new;
	}

	dma_fence_put(new_pwane_state->fence);
	new_pwane_state->fence = fence;
	wetuwn 0;

ewwow:
	dma_fence_put(fence);
	wetuwn wet;
}

/**
 * intew_pwepawe_pwane_fb - Pwepawe fb fow usage on pwane
 * @_pwane: dwm pwane to pwepawe fow
 * @_new_pwane_state: the pwane state being pwepawed
 *
 * Pwepawes a fwamebuffew fow usage on a dispway pwane.  Genewawwy this
 * invowves pinning the undewwying object and updating the fwontbuffew twacking
 * bits.  Some owdew pwatfowms need speciaw physicaw addwess handwing fow
 * cuwsow pwanes.
 *
 * Wetuwns 0 on success, negative ewwow code on faiwuwe.
 */
static int
intew_pwepawe_pwane_fb(stwuct dwm_pwane *_pwane,
		       stwuct dwm_pwane_state *_new_pwane_state)
{
	stwuct i915_sched_attw attw = { .pwiowity = I915_PWIOWITY_DISPWAY };
	stwuct intew_pwane *pwane = to_intew_pwane(_pwane);
	stwuct intew_pwane_state *new_pwane_state =
		to_intew_pwane_state(_new_pwane_state);
	stwuct intew_atomic_state *state =
		to_intew_atomic_state(new_pwane_state->uapi.state);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(pwane->base.dev);
	stwuct intew_pwane_state *owd_pwane_state =
		intew_atomic_get_owd_pwane_state(state, pwane);
	stwuct dwm_i915_gem_object *obj = intew_fb_obj(new_pwane_state->hw.fb);
	stwuct dwm_i915_gem_object *owd_obj = intew_fb_obj(owd_pwane_state->hw.fb);
	int wet;

	if (owd_obj) {
		const stwuct intew_cwtc_state *new_cwtc_state =
			intew_atomic_get_new_cwtc_state(state,
							to_intew_cwtc(owd_pwane_state->hw.cwtc));

		/* Big Hammew, we awso need to ensuwe that any pending
		 * MI_WAIT_FOW_EVENT inside a usew batch buffew on the
		 * cuwwent scanout is wetiwed befowe unpinning the owd
		 * fwamebuffew. Note that we wewy on usewspace wendewing
		 * into the buffew attached to the pipe they awe waiting
		 * on. If not, usewspace genewates a GPU hang with IPEHW
		 * point to the MI_WAIT_FOW_EVENT.
		 *
		 * This shouwd onwy faiw upon a hung GPU, in which case we
		 * can safewy continue.
		 */
		if (new_cwtc_state && intew_cwtc_needs_modeset(new_cwtc_state)) {
			wet = add_dma_wesv_fences(intew_bo_to_dwm_bo(owd_obj)->wesv,
						  &new_pwane_state->uapi);
			if (wet < 0)
				wetuwn wet;
		}
	}

	if (!obj)
		wetuwn 0;

	wet = intew_pwane_pin_fb(new_pwane_state);
	if (wet)
		wetuwn wet;

	wet = dwm_gem_pwane_hewpew_pwepawe_fb(&pwane->base, &new_pwane_state->uapi);
	if (wet < 0)
		goto unpin_fb;

	if (new_pwane_state->uapi.fence) {
		i915_gem_fence_wait_pwiowity(new_pwane_state->uapi.fence,
					     &attw);

		intew_dispway_wps_boost_aftew_vbwank(new_pwane_state->hw.cwtc,
						     new_pwane_state->uapi.fence);
	}

	/*
	 * We decwawe pagefwips to be intewactive and so mewit a smaww bias
	 * towawds upcwocking to dewivew the fwame on time. By onwy changing
	 * the WPS thweshowds to sampwe mowe weguwawwy and aim fow highew
	 * cwocks we can hopefuwwy dewivew wow powew wowkwoads (wike kodi)
	 * that awe not quite steady state without wesowting to fowcing
	 * maximum cwocks fowwowing a vbwank miss (see do_wps_boost()).
	 */
	intew_dispway_wps_mawk_intewactive(dev_pwiv, state, twue);

	wetuwn 0;

unpin_fb:
	intew_pwane_unpin_fb(new_pwane_state);

	wetuwn wet;
}

/**
 * intew_cweanup_pwane_fb - Cweans up an fb aftew pwane use
 * @pwane: dwm pwane to cwean up fow
 * @_owd_pwane_state: the state fwom the pwevious modeset
 *
 * Cweans up a fwamebuffew that has just been wemoved fwom a pwane.
 */
static void
intew_cweanup_pwane_fb(stwuct dwm_pwane *pwane,
		       stwuct dwm_pwane_state *_owd_pwane_state)
{
	stwuct intew_pwane_state *owd_pwane_state =
		to_intew_pwane_state(_owd_pwane_state);
	stwuct intew_atomic_state *state =
		to_intew_atomic_state(owd_pwane_state->uapi.state);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(pwane->dev);
	stwuct dwm_i915_gem_object *obj = intew_fb_obj(owd_pwane_state->hw.fb);

	if (!obj)
		wetuwn;

	intew_dispway_wps_mawk_intewactive(dev_pwiv, state, fawse);

	/* Shouwd onwy be cawwed aftew a successfuw intew_pwepawe_pwane_fb()! */
	intew_pwane_unpin_fb(owd_pwane_state);
}

static const stwuct dwm_pwane_hewpew_funcs intew_pwane_hewpew_funcs = {
	.pwepawe_fb = intew_pwepawe_pwane_fb,
	.cweanup_fb = intew_cweanup_pwane_fb,
};

void intew_pwane_hewpew_add(stwuct intew_pwane *pwane)
{
	dwm_pwane_hewpew_add(&pwane->base, &intew_pwane_hewpew_funcs);
}
