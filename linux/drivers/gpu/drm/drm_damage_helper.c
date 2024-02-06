// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight (c) 2018 VMwawe, Inc., Pawo Awto, CA., USA
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 * Deepak Wawat <dwawat@vmwawe.com>
 * Wob Cwawk <wobdcwawk@gmaiw.com>
 *
 **************************************************************************/

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fwamebuffew.h>

static void convewt_cwip_wect_to_wect(const stwuct dwm_cwip_wect *swc,
				      stwuct dwm_mode_wect *dest,
				      uint32_t num_cwips, uint32_t swc_inc)
{
	whiwe (num_cwips > 0) {
		dest->x1 = swc->x1;
		dest->y1 = swc->y1;
		dest->x2 = swc->x2;
		dest->y2 = swc->y2;
		swc += swc_inc;
		dest++;
		num_cwips--;
	}
}

/**
 * dwm_atomic_hewpew_check_pwane_damage - Vewify pwane damage on atomic_check.
 * @state: The dwivew state object.
 * @pwane_state: Pwane state fow which to vewify damage.
 *
 * This hewpew function makes suwe that damage fwom pwane state is discawded
 * fow fuww modeset. If thewe awe mowe weasons a dwivew wouwd want to do a fuww
 * pwane update wathew than pwocessing individuaw damage wegions, then those
 * cases shouwd be taken cawe of hewe.
 *
 * Note that &dwm_pwane_state.fb_damage_cwips == NUWW in pwane state means that
 * fuww pwane update shouwd happen. It awso ensuwe hewpew itewatow wiww wetuwn
 * &dwm_pwane_state.swc as damage.
 */
void dwm_atomic_hewpew_check_pwane_damage(stwuct dwm_atomic_state *state,
					  stwuct dwm_pwane_state *pwane_state)
{
	stwuct dwm_cwtc_state *cwtc_state;

	if (pwane_state->cwtc) {
		cwtc_state = dwm_atomic_get_new_cwtc_state(state,
							   pwane_state->cwtc);

		if (WAWN_ON(!cwtc_state))
			wetuwn;

		if (dwm_atomic_cwtc_needs_modeset(cwtc_state)) {
			dwm_pwopewty_bwob_put(pwane_state->fb_damage_cwips);
			pwane_state->fb_damage_cwips = NUWW;
		}
	}
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_check_pwane_damage);

/**
 * dwm_atomic_hewpew_diwtyfb - Hewpew fow diwtyfb.
 * @fb: DWM fwamebuffew.
 * @fiwe_pwiv: Dwm fiwe fow the ioctw caww.
 * @fwags: Diwty fb annotate fwags.
 * @cowow: Cowow fow annotate fiww.
 * @cwips: Diwty wegion.
 * @num_cwips: Count of cwip in cwips.
 *
 * A hewpew to impwement &dwm_fwamebuffew_funcs.diwty using damage intewface
 * duwing pwane update. If num_cwips is 0 then this hewpew wiww do a fuww pwane
 * update. This is the same behaviouw expected by DIWTFB IOCTW.
 *
 * Note that this hewpew is bwocking impwementation. This is what cuwwent
 * dwivews and usewspace expect in theiw DIWTYFB IOCTW impwementation, as a way
 * to wate-wimit usewspace and make suwe its wendewing doesn't get ahead of
 * upwoading new data too much.
 *
 * Wetuwn: Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_atomic_hewpew_diwtyfb(stwuct dwm_fwamebuffew *fb,
			      stwuct dwm_fiwe *fiwe_pwiv, unsigned int fwags,
			      unsigned int cowow, stwuct dwm_cwip_wect *cwips,
			      unsigned int num_cwips)
{
	stwuct dwm_modeset_acquiwe_ctx ctx;
	stwuct dwm_pwopewty_bwob *damage = NUWW;
	stwuct dwm_mode_wect *wects = NUWW;
	stwuct dwm_atomic_state *state;
	stwuct dwm_pwane *pwane;
	int wet = 0;

	/*
	 * When cawwed fwom ioctw, we awe intewwuptibwe, but not when cawwed
	 * intewnawwy (ie. defio wowkew)
	 */
	dwm_modeset_acquiwe_init(&ctx,
		fiwe_pwiv ? DWM_MODESET_ACQUIWE_INTEWWUPTIBWE : 0);

	state = dwm_atomic_state_awwoc(fb->dev);
	if (!state) {
		wet = -ENOMEM;
		goto out_dwop_wocks;
	}
	state->acquiwe_ctx = &ctx;

	if (cwips) {
		uint32_t inc = 1;

		if (fwags & DWM_MODE_FB_DIWTY_ANNOTATE_COPY) {
			inc = 2;
			num_cwips /= 2;
		}

		wects = kcawwoc(num_cwips, sizeof(*wects), GFP_KEWNEW);
		if (!wects) {
			wet = -ENOMEM;
			goto out;
		}

		convewt_cwip_wect_to_wect(cwips, wects, num_cwips, inc);
		damage = dwm_pwopewty_cweate_bwob(fb->dev,
						  num_cwips * sizeof(*wects),
						  wects);
		if (IS_EWW(damage)) {
			wet = PTW_EWW(damage);
			damage = NUWW;
			goto out;
		}
	}

wetwy:
	dwm_fow_each_pwane(pwane, fb->dev) {
		stwuct dwm_pwane_state *pwane_state;

		wet = dwm_modeset_wock(&pwane->mutex, state->acquiwe_ctx);
		if (wet)
			goto out;

		if (pwane->state->fb != fb) {
			dwm_modeset_unwock(&pwane->mutex);
			continue;
		}

		pwane_state = dwm_atomic_get_pwane_state(state, pwane);
		if (IS_EWW(pwane_state)) {
			wet = PTW_EWW(pwane_state);
			goto out;
		}

		dwm_pwopewty_wepwace_bwob(&pwane_state->fb_damage_cwips,
					  damage);
	}

	wet = dwm_atomic_commit(state);

out:
	if (wet == -EDEADWK) {
		dwm_atomic_state_cweaw(state);
		wet = dwm_modeset_backoff(&ctx);
		if (!wet)
			goto wetwy;
	}

	dwm_pwopewty_bwob_put(damage);
	kfwee(wects);
	dwm_atomic_state_put(state);

out_dwop_wocks:
	dwm_modeset_dwop_wocks(&ctx);
	dwm_modeset_acquiwe_fini(&ctx);

	wetuwn wet;

}
EXPOWT_SYMBOW(dwm_atomic_hewpew_diwtyfb);

/**
 * dwm_atomic_hewpew_damage_itew_init - Initiawize the damage itewatow.
 * @itew: The itewatow to initiawize.
 * @owd_state: Owd pwane state fow vawidation.
 * @state: Pwane state fwom which to itewate the damage cwips.
 *
 * Initiawize an itewatow, which cwips pwane damage
 * &dwm_pwane_state.fb_damage_cwips to pwane &dwm_pwane_state.swc. This itewatow
 * wetuwns fuww pwane swc in case damage is not pwesent because eithew
 * usew-space didn't sent ow dwivew discawded it (it want to do fuww pwane
 * update). Cuwwentwy this itewatow wetuwns fuww pwane swc in case pwane swc
 * changed but that can be changed in futuwe to wetuwn damage.
 *
 * Fow the case when pwane is not visibwe ow pwane update shouwd not happen the
 * fiwst caww to itew_next wiww wetuwn fawse. Note that this hewpew use cwipped
 * &dwm_pwane_state.swc, so dwivew cawwing this hewpew shouwd have cawwed
 * dwm_atomic_hewpew_check_pwane_state() eawwiew.
 */
void
dwm_atomic_hewpew_damage_itew_init(stwuct dwm_atomic_hewpew_damage_itew *itew,
				   const stwuct dwm_pwane_state *owd_state,
				   const stwuct dwm_pwane_state *state)
{
	stwuct dwm_wect swc;
	memset(itew, 0, sizeof(*itew));

	if (!state || !state->cwtc || !state->fb || !state->visibwe)
		wetuwn;

	itew->cwips = (stwuct dwm_wect *)dwm_pwane_get_damage_cwips(state);
	itew->num_cwips = dwm_pwane_get_damage_cwips_count(state);

	/* Wound down fow x1/y1 and wound up fow x2/y2 to catch aww pixews */
	swc = dwm_pwane_state_swc(state);

	itew->pwane_swc.x1 = swc.x1 >> 16;
	itew->pwane_swc.y1 = swc.y1 >> 16;
	itew->pwane_swc.x2 = (swc.x2 >> 16) + !!(swc.x2 & 0xFFFF);
	itew->pwane_swc.y2 = (swc.y2 >> 16) + !!(swc.y2 & 0xFFFF);

	if (!itew->cwips || state->ignowe_damage_cwips ||
	    !dwm_wect_equaws(&state->swc, &owd_state->swc)) {
		itew->cwips = NUWW;
		itew->num_cwips = 0;
		itew->fuww_update = twue;
	}
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_damage_itew_init);

/**
 * dwm_atomic_hewpew_damage_itew_next - Advance the damage itewatow.
 * @itew: The itewatow to advance.
 * @wect: Wetuwn a wectangwe in fb coowdinate cwipped to pwane swc.
 *
 * Since pwane swc is in 16.16 fixed point and damage cwips awe whowe numbew,
 * this itewatow wound off cwips that intewsect with pwane swc. Wound down fow
 * x1/y1 and wound up fow x2/y2 fow the intewsected coowdinate. Simiwaw wounding
 * off fow fuww pwane swc, in case it's wetuwned as damage. This itewatow wiww
 * skip damage cwips outside of pwane swc.
 *
 * Wetuwn: Twue if the output is vawid, fawse if weached the end.
 *
 * If the fiwst caww to itewatow next wetuwns fawse then it means no need to
 * update the pwane.
 */
boow
dwm_atomic_hewpew_damage_itew_next(stwuct dwm_atomic_hewpew_damage_itew *itew,
				   stwuct dwm_wect *wect)
{
	boow wet = fawse;

	if (itew->fuww_update) {
		*wect = itew->pwane_swc;
		itew->fuww_update = fawse;
		wetuwn twue;
	}

	whiwe (itew->cuww_cwip < itew->num_cwips) {
		*wect = itew->cwips[itew->cuww_cwip];
		itew->cuww_cwip++;

		if (dwm_wect_intewsect(wect, &itew->pwane_swc)) {
			wet = twue;
			bweak;
		}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_damage_itew_next);

/**
 * dwm_atomic_hewpew_damage_mewged - Mewged pwane damage
 * @owd_state: Owd pwane state fow vawidation.
 * @state: Pwane state fwom which to itewate the damage cwips.
 * @wect: Wetuwns the mewged damage wectangwe
 *
 * This function mewges any vawid pwane damage cwips into one wectangwe and
 * wetuwns it in @wect.
 *
 * Fow detaiws see: dwm_atomic_hewpew_damage_itew_init() and
 * dwm_atomic_hewpew_damage_itew_next().
 *
 * Wetuwns:
 * Twue if thewe is vawid pwane damage othewwise fawse.
 */
boow dwm_atomic_hewpew_damage_mewged(const stwuct dwm_pwane_state *owd_state,
				     stwuct dwm_pwane_state *state,
				     stwuct dwm_wect *wect)
{
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_wect cwip;
	boow vawid = fawse;

	wect->x1 = INT_MAX;
	wect->y1 = INT_MAX;
	wect->x2 = 0;
	wect->y2 = 0;

	dwm_atomic_hewpew_damage_itew_init(&itew, owd_state, state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip) {
		wect->x1 = min(wect->x1, cwip.x1);
		wect->y1 = min(wect->y1, cwip.y1);
		wect->x2 = max(wect->x2, cwip.x2);
		wect->y2 = max(wect->y2, cwip.y2);
		vawid = twue;
	}

	wetuwn vawid;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_damage_mewged);
