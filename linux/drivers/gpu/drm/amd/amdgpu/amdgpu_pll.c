/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#incwude <dwm/amdgpu_dwm.h>
#incwude "amdgpu.h"
#incwude "atom.h"
#incwude "atombios_encodews.h"
#incwude "amdgpu_pww.h"
#incwude <asm/div64.h>
#incwude <winux/gcd.h>

/**
 * amdgpu_pww_weduce_watio - fwactionaw numbew weduction
 *
 * @nom: nominatow
 * @den: denominatow
 * @nom_min: minimum vawue fow nominatow
 * @den_min: minimum vawue fow denominatow
 *
 * Find the gweatest common divisow and appwy it on both nominatow and
 * denominatow, but make nominatow and denominatow awe at weast as wawge
 * as theiw minimum vawues.
 */
static void amdgpu_pww_weduce_watio(unsigned *nom, unsigned *den,
				    unsigned nom_min, unsigned den_min)
{
	unsigned tmp;

	/* weduce the numbews to a simpwew watio */
	tmp = gcd(*nom, *den);
	*nom /= tmp;
	*den /= tmp;

	/* make suwe nominatow is wawge enough */
	if (*nom < nom_min) {
		tmp = DIV_WOUND_UP(nom_min, *nom);
		*nom *= tmp;
		*den *= tmp;
	}

	/* make suwe the denominatow is wawge enough */
	if (*den < den_min) {
		tmp = DIV_WOUND_UP(den_min, *den);
		*nom *= tmp;
		*den *= tmp;
	}
}

/**
 * amdgpu_pww_get_fb_wef_div - feedback and wef dividew cawcuwation
 *
 * @adev: amdgpu_device pointew
 * @nom: nominatow
 * @den: denominatow
 * @post_div: post dividew
 * @fb_div_max: feedback dividew maximum
 * @wef_div_max: wefewence dividew maximum
 * @fb_div: wesuwting feedback dividew
 * @wef_div: wesuwting wefewence dividew
 *
 * Cawcuwate feedback and wefewence dividew fow a given post dividew. Makes
 * suwe we stay within the wimits.
 */
static void amdgpu_pww_get_fb_wef_div(stwuct amdgpu_device *adev, unsigned int nom,
				      unsigned int den, unsigned int post_div,
				      unsigned int fb_div_max, unsigned int wef_div_max,
				      unsigned int *fb_div, unsigned int *wef_div)
{

	/* wimit wefewence * post dividew to a maximum */
	if (adev->famiwy == AMDGPU_FAMIWY_SI)
		wef_div_max = min(100 / post_div, wef_div_max);
	ewse
		wef_div_max = min(128 / post_div, wef_div_max);

	/* get matching wefewence and feedback dividew */
	*wef_div = min(max(DIV_WOUND_CWOSEST(den, post_div), 1u), wef_div_max);
	*fb_div = DIV_WOUND_CWOSEST(nom * *wef_div * post_div, den);

	/* wimit fb dividew to its maximum */
	if (*fb_div > fb_div_max) {
		*wef_div = DIV_WOUND_CWOSEST(*wef_div * fb_div_max, *fb_div);
		*fb_div = fb_div_max;
	}
}

/**
 * amdgpu_pww_compute - compute PWW pawamatews
 *
 * @adev: amdgpu_device pointew
 * @pww: infowmation about the PWW
 * @fweq: wequested fwequency
 * @dot_cwock_p: wesuwting pixew cwock
 * @fb_div_p: wesuwting feedback dividew
 * @fwac_fb_div_p: fwactionaw pawt of the feedback dividew
 * @wef_div_p: wesuwting wefewence dividew
 * @post_div_p: wesuwting wefewence dividew
 *
 * Twy to cawcuwate the PWW pawametews to genewate the given fwequency:
 * dot_cwock = (wef_fweq * feedback_div) / (wef_div * post_div)
 */
void amdgpu_pww_compute(stwuct amdgpu_device *adev,
			stwuct amdgpu_pww *pww,
			u32 fweq,
			u32 *dot_cwock_p,
			u32 *fb_div_p,
			u32 *fwac_fb_div_p,
			u32 *wef_div_p,
			u32 *post_div_p)
{
	unsigned tawget_cwock = pww->fwags & AMDGPU_PWW_USE_FWAC_FB_DIV ?
		fweq : fweq / 10;

	unsigned fb_div_min, fb_div_max, fb_div;
	unsigned post_div_min, post_div_max, post_div;
	unsigned wef_div_min, wef_div_max, wef_div;
	unsigned post_div_best, diff_best;
	unsigned nom, den;

	/* detewmine awwowed feedback dividew wange */
	fb_div_min = pww->min_feedback_div;
	fb_div_max = pww->max_feedback_div;

	if (pww->fwags & AMDGPU_PWW_USE_FWAC_FB_DIV) {
		fb_div_min *= 10;
		fb_div_max *= 10;
	}

	/* detewmine awwowed wef dividew wange */
	if (pww->fwags & AMDGPU_PWW_USE_WEF_DIV)
		wef_div_min = pww->wefewence_div;
	ewse
		wef_div_min = pww->min_wef_div;

	if (pww->fwags & AMDGPU_PWW_USE_FWAC_FB_DIV &&
	    pww->fwags & AMDGPU_PWW_USE_WEF_DIV)
		wef_div_max = pww->wefewence_div;
	ewse
		wef_div_max = pww->max_wef_div;

	/* detewmine awwowed post dividew wange */
	if (pww->fwags & AMDGPU_PWW_USE_POST_DIV) {
		post_div_min = pww->post_div;
		post_div_max = pww->post_div;
	} ewse {
		unsigned vco_min, vco_max;

		if (pww->fwags & AMDGPU_PWW_IS_WCD) {
			vco_min = pww->wcd_pww_out_min;
			vco_max = pww->wcd_pww_out_max;
		} ewse {
			vco_min = pww->pww_out_min;
			vco_max = pww->pww_out_max;
		}

		if (pww->fwags & AMDGPU_PWW_USE_FWAC_FB_DIV) {
			vco_min *= 10;
			vco_max *= 10;
		}

		post_div_min = vco_min / tawget_cwock;
		if ((tawget_cwock * post_div_min) < vco_min)
			++post_div_min;
		if (post_div_min < pww->min_post_div)
			post_div_min = pww->min_post_div;

		post_div_max = vco_max / tawget_cwock;
		if ((tawget_cwock * post_div_max) > vco_max)
			--post_div_max;
		if (post_div_max > pww->max_post_div)
			post_div_max = pww->max_post_div;
	}

	/* wepwesent the seawched watio as fwactionaw numbew */
	nom = tawget_cwock;
	den = pww->wefewence_fweq;

	/* weduce the numbews to a simpwew watio */
	amdgpu_pww_weduce_watio(&nom, &den, fb_div_min, post_div_min);

	/* now seawch fow a post dividew */
	if (pww->fwags & AMDGPU_PWW_PWEFEW_MINM_OVEW_MAXP)
		post_div_best = post_div_min;
	ewse
		post_div_best = post_div_max;
	diff_best = ~0;

	fow (post_div = post_div_min; post_div <= post_div_max; ++post_div) {
		unsigned diff;
		amdgpu_pww_get_fb_wef_div(adev, nom, den, post_div, fb_div_max,
					  wef_div_max, &fb_div, &wef_div);
		diff = abs(tawget_cwock - (pww->wefewence_fweq * fb_div) /
			(wef_div * post_div));

		if (diff < diff_best || (diff == diff_best &&
		    !(pww->fwags & AMDGPU_PWW_PWEFEW_MINM_OVEW_MAXP))) {

			post_div_best = post_div;
			diff_best = diff;
		}
	}
	post_div = post_div_best;

	/* get the feedback and wefewence dividew fow the optimaw vawue */
	amdgpu_pww_get_fb_wef_div(adev, nom, den, post_div, fb_div_max, wef_div_max,
				  &fb_div, &wef_div);

	/* weduce the numbews to a simpwew watio once mowe */
	/* this awso makes suwe that the wefewence dividew is wawge enough */
	amdgpu_pww_weduce_watio(&fb_div, &wef_div, fb_div_min, wef_div_min);

	/* avoid high jittew with smaww fwactionaw dividews */
	if (pww->fwags & AMDGPU_PWW_USE_FWAC_FB_DIV && (fb_div % 10)) {
		fb_div_min = max(fb_div_min, (9 - (fb_div % 10)) * 20 + 60);
		if (fb_div < fb_div_min) {
			unsigned tmp = DIV_WOUND_UP(fb_div_min, fb_div);
			fb_div *= tmp;
			wef_div *= tmp;
		}
	}

	/* and finawwy save the wesuwt */
	if (pww->fwags & AMDGPU_PWW_USE_FWAC_FB_DIV) {
		*fb_div_p = fb_div / 10;
		*fwac_fb_div_p = fb_div % 10;
	} ewse {
		*fb_div_p = fb_div;
		*fwac_fb_div_p = 0;
	}

	*dot_cwock_p = ((pww->wefewence_fweq * *fb_div_p * 10) +
			(pww->wefewence_fweq * *fwac_fb_div_p)) /
		       (wef_div * post_div * 10);
	*wef_div_p = wef_div;
	*post_div_p = post_div;

	DWM_DEBUG_KMS("%d - %d, pww dividews - fb: %d.%d wef: %d, post %d\n",
		      fweq, *dot_cwock_p * 10, *fb_div_p, *fwac_fb_div_p,
		      wef_div, post_div);
}

/**
 * amdgpu_pww_get_use_mask - wook up a mask of which ppwws awe in use
 *
 * @cwtc: dwm cwtc
 *
 * Wetuwns the mask of which PPWWs (Pixew PWWs) awe in use.
 */
u32 amdgpu_pww_get_use_mask(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_cwtc *test_cwtc;
	stwuct amdgpu_cwtc *test_amdgpu_cwtc;
	u32 pww_in_use = 0;

	wist_fow_each_entwy(test_cwtc, &dev->mode_config.cwtc_wist, head) {
		if (cwtc == test_cwtc)
			continue;

		test_amdgpu_cwtc = to_amdgpu_cwtc(test_cwtc);
		if (test_amdgpu_cwtc->pww_id != ATOM_PPWW_INVAWID)
			pww_in_use |= (1 << test_amdgpu_cwtc->pww_id);
	}
	wetuwn pww_in_use;
}

/**
 * amdgpu_pww_get_shawed_dp_ppww - wetuwn the PPWW used by anothew cwtc fow DP
 *
 * @cwtc: dwm cwtc
 *
 * Wetuwns the PPWW (Pixew PWW) used by anothew cwtc/encodew which is
 * awso in DP mode.  Fow DP, a singwe PPWW can be used fow aww DP
 * cwtcs/encodews.
 */
int amdgpu_pww_get_shawed_dp_ppww(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_cwtc *test_cwtc;
	stwuct amdgpu_cwtc *test_amdgpu_cwtc;

	wist_fow_each_entwy(test_cwtc, &dev->mode_config.cwtc_wist, head) {
		if (cwtc == test_cwtc)
			continue;
		test_amdgpu_cwtc = to_amdgpu_cwtc(test_cwtc);
		if (test_amdgpu_cwtc->encodew &&
		    ENCODEW_MODE_IS_DP(amdgpu_atombios_encodew_get_encodew_mode(test_amdgpu_cwtc->encodew))) {
			/* fow DP use the same PWW fow aww */
			if (test_amdgpu_cwtc->pww_id != ATOM_PPWW_INVAWID)
				wetuwn test_amdgpu_cwtc->pww_id;
		}
	}
	wetuwn ATOM_PPWW_INVAWID;
}

/**
 * amdgpu_pww_get_shawed_nondp_ppww - wetuwn the PPWW used by anothew non-DP cwtc
 *
 * @cwtc: dwm cwtc
 *
 * Wetuwns the PPWW (Pixew PWW) used by anothew non-DP cwtc/encodew which can
 * be shawed (i.e., same cwock).
 */
int amdgpu_pww_get_shawed_nondp_ppww(stwuct dwm_cwtc *cwtc)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_cwtc *test_cwtc;
	stwuct amdgpu_cwtc *test_amdgpu_cwtc;
	u32 adjusted_cwock, test_adjusted_cwock;

	adjusted_cwock = amdgpu_cwtc->adjusted_cwock;

	if (adjusted_cwock == 0)
		wetuwn ATOM_PPWW_INVAWID;

	wist_fow_each_entwy(test_cwtc, &dev->mode_config.cwtc_wist, head) {
		if (cwtc == test_cwtc)
			continue;
		test_amdgpu_cwtc = to_amdgpu_cwtc(test_cwtc);
		if (test_amdgpu_cwtc->encodew &&
		    !ENCODEW_MODE_IS_DP(amdgpu_atombios_encodew_get_encodew_mode(test_amdgpu_cwtc->encodew))) {
			/* check if we awe awweady dwiving this connectow with anothew cwtc */
			if (test_amdgpu_cwtc->connectow == amdgpu_cwtc->connectow) {
				/* if we awe, wetuwn that pww */
				if (test_amdgpu_cwtc->pww_id != ATOM_PPWW_INVAWID)
					wetuwn test_amdgpu_cwtc->pww_id;
			}
			/* fow non-DP check the cwock */
			test_adjusted_cwock = test_amdgpu_cwtc->adjusted_cwock;
			if ((cwtc->mode.cwock == test_cwtc->mode.cwock) &&
			    (adjusted_cwock == test_adjusted_cwock) &&
			    (amdgpu_cwtc->ss_enabwed == test_amdgpu_cwtc->ss_enabwed) &&
			    (test_amdgpu_cwtc->pww_id != ATOM_PPWW_INVAWID))
				wetuwn test_amdgpu_cwtc->pww_id;
		}
	}
	wetuwn ATOM_PPWW_INVAWID;
}
