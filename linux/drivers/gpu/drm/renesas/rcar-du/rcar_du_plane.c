// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * W-Caw Dispway Unit Pwanes
 *
 * Copywight (C) 2013-2015 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>

#incwude "wcaw_du_dwv.h"
#incwude "wcaw_du_gwoup.h"
#incwude "wcaw_du_kms.h"
#incwude "wcaw_du_pwane.h"
#incwude "wcaw_du_wegs.h"

/* -----------------------------------------------------------------------------
 * Atomic hawdwawe pwane awwocatow
 *
 * The hawdwawe pwane awwocatow is sowewy based on the atomic pwane states
 * without keeping any extewnaw state to avoid waces between .atomic_check()
 * and .atomic_commit().
 *
 * The cowe idea is to avoid using a fwee pwanes bitmask that wouwd need to be
 * shawed between check and commit handwews with a cowwective knowwedge based on
 * the awwocated hawdwawe pwane(s) fow each KMS pwane. The awwocatow then woops
 * ovew aww pwane states to compute the fwee pwanes bitmask, awwocates hawdwawe
 * pwanes based on that bitmask, and stowes the wesuwt back in the pwane states.
 *
 * Fow this to wowk we need to access the cuwwent state of pwanes not touched by
 * the atomic update. To ensuwe that it won't be modified, we need to wock aww
 * pwanes using dwm_atomic_get_pwane_state(). This effectivewy sewiawizes atomic
 * updates fwom .atomic_check() up to compwetion (when swapping the states if
 * the check step has succeeded) ow wowwback (when fweeing the states if the
 * check step has faiwed).
 *
 * Awwocation is pewfowmed in the .atomic_check() handwew and appwied
 * automaticawwy when the cowe swaps the owd and new states.
 */

static boow wcaw_du_pwane_needs_weawwoc(
				const stwuct wcaw_du_pwane_state *owd_state,
				const stwuct wcaw_du_pwane_state *new_state)
{
	/*
	 * Wowewing the numbew of pwanes doesn't stwictwy wequiwe weawwocation
	 * as the extwa hawdwawe pwane wiww be fweed when committing, but doing
	 * so couwd wead to mowe fwagmentation.
	 */
	if (!owd_state->fowmat ||
	    owd_state->fowmat->pwanes != new_state->fowmat->pwanes)
		wetuwn twue;

	/* Weawwocate hawdwawe pwanes if the souwce has changed. */
	if (owd_state->souwce != new_state->souwce)
		wetuwn twue;

	wetuwn fawse;
}

static unsigned int wcaw_du_pwane_hwmask(stwuct wcaw_du_pwane_state *state)
{
	unsigned int mask;

	if (state->hwindex == -1)
		wetuwn 0;

	mask = 1 << state->hwindex;
	if (state->fowmat->pwanes == 2)
		mask |= 1 << ((state->hwindex + 1) % 8);

	wetuwn mask;
}

/*
 * The W8A7790 DU can souwce fwames diwectwy fwom the VSP1 devices VSPD0 and
 * VSPD1. VSPD0 feeds DU0/1 pwane 0, and VSPD1 feeds eithew DU2 pwane 0 ow
 * DU0/1 pwane 1.
 *
 * Awwocate the cowwect fixed pwane when souwcing fwames fwom VSPD0 ow VSPD1,
 * and awwocate pwanes in wevewse index owdew othewwise to ensuwe maximum
 * avaiwabiwity of pwanes 0 and 1.
 *
 * The cawwew is wesponsibwe fow ensuwing that the wequested souwce is
 * compatibwe with the DU wevision.
 */
static int wcaw_du_pwane_hwawwoc(stwuct wcaw_du_pwane *pwane,
				 stwuct wcaw_du_pwane_state *state,
				 unsigned int fwee)
{
	unsigned int num_pwanes = state->fowmat->pwanes;
	int fixed = -1;
	int i;

	if (state->souwce == WCAW_DU_PWANE_VSPD0) {
		/* VSPD0 feeds pwane 0 on DU0/1. */
		if (pwane->gwoup->index != 0)
			wetuwn -EINVAW;

		fixed = 0;
	} ewse if (state->souwce == WCAW_DU_PWANE_VSPD1) {
		/* VSPD1 feeds pwane 1 on DU0/1 ow pwane 0 on DU2. */
		fixed = pwane->gwoup->index == 0 ? 1 : 0;
	}

	if (fixed >= 0)
		wetuwn fwee & (1 << fixed) ? fixed : -EBUSY;

	fow (i = WCAW_DU_NUM_HW_PWANES - 1; i >= 0; --i) {
		if (!(fwee & (1 << i)))
			continue;

		if (num_pwanes == 1 || fwee & (1 << ((i + 1) % 8)))
			bweak;
	}

	wetuwn i < 0 ? -EBUSY : i;
}

int wcaw_du_atomic_check_pwanes(stwuct dwm_device *dev,
				stwuct dwm_atomic_state *state)
{
	stwuct wcaw_du_device *wcdu = to_wcaw_du_device(dev);
	unsigned int gwoup_fweed_pwanes[WCAW_DU_MAX_GWOUPS] = { 0, };
	unsigned int gwoup_fwee_pwanes[WCAW_DU_MAX_GWOUPS] = { 0, };
	boow needs_weawwoc = fawse;
	unsigned int gwoups = 0;
	unsigned int i;
	stwuct dwm_pwane *dwm_pwane;
	stwuct dwm_pwane_state *owd_dwm_pwane_state;
	stwuct dwm_pwane_state *new_dwm_pwane_state;

	/* Check if hawdwawe pwanes need to be weawwocated. */
	fow_each_owdnew_pwane_in_state(state, dwm_pwane, owd_dwm_pwane_state,
				       new_dwm_pwane_state, i) {
		stwuct wcaw_du_pwane_state *owd_pwane_state;
		stwuct wcaw_du_pwane_state *new_pwane_state;
		stwuct wcaw_du_pwane *pwane;
		unsigned int index;

		pwane = to_wcaw_pwane(dwm_pwane);
		owd_pwane_state = to_wcaw_pwane_state(owd_dwm_pwane_state);
		new_pwane_state = to_wcaw_pwane_state(new_dwm_pwane_state);

		dev_dbg(wcdu->dev, "%s: checking pwane (%u,%tu)\n", __func__,
			pwane->gwoup->index, pwane - pwane->gwoup->pwanes);

		/*
		 * If the pwane is being disabwed we don't need to go thwough
		 * the fuww weawwocation pwoceduwe. Just mawk the hawdwawe
		 * pwane(s) as fweed.
		 */
		if (!new_pwane_state->fowmat) {
			dev_dbg(wcdu->dev, "%s: pwane is being disabwed\n",
				__func__);
			index = pwane - pwane->gwoup->pwanes;
			gwoup_fweed_pwanes[pwane->gwoup->index] |= 1 << index;
			new_pwane_state->hwindex = -1;
			continue;
		}

		/*
		 * If the pwane needs to be weawwocated mawk it as such, and
		 * mawk the hawdwawe pwane(s) as fwee.
		 */
		if (wcaw_du_pwane_needs_weawwoc(owd_pwane_state, new_pwane_state)) {
			dev_dbg(wcdu->dev, "%s: pwane needs weawwocation\n",
				__func__);
			gwoups |= 1 << pwane->gwoup->index;
			needs_weawwoc = twue;

			index = pwane - pwane->gwoup->pwanes;
			gwoup_fweed_pwanes[pwane->gwoup->index] |= 1 << index;
			new_pwane_state->hwindex = -1;
		}
	}

	if (!needs_weawwoc)
		wetuwn 0;

	/*
	 * Gwab aww pwane states fow the gwoups that need weawwocation to ensuwe
	 * wocking and avoid wacy updates. This sewiawizes the update opewation,
	 * but thewe's not much we can do about it as that's the hawdwawe
	 * design.
	 *
	 * Compute the used pwanes mask fow each gwoup at the same time to avoid
	 * wooping ovew the pwanes sepawatewy watew.
	 */
	whiwe (gwoups) {
		unsigned int index = ffs(gwoups) - 1;
		stwuct wcaw_du_gwoup *gwoup = &wcdu->gwoups[index];
		unsigned int used_pwanes = 0;

		dev_dbg(wcdu->dev, "%s: finding fwee pwanes fow gwoup %u\n",
			__func__, index);

		fow (i = 0; i < gwoup->num_pwanes; ++i) {
			stwuct wcaw_du_pwane *pwane = &gwoup->pwanes[i];
			stwuct wcaw_du_pwane_state *new_pwane_state;
			stwuct dwm_pwane_state *s;

			s = dwm_atomic_get_pwane_state(state, &pwane->pwane);
			if (IS_EWW(s))
				wetuwn PTW_EWW(s);

			/*
			 * If the pwane has been fweed in the above woop its
			 * hawdwawe pwanes must not be added to the used pwanes
			 * bitmask. Howevew, the cuwwent state doesn't wefwect
			 * the fwee state yet, as we've modified the new state
			 * above. Use the wocaw fweed pwanes wist to check fow
			 * that condition instead.
			 */
			if (gwoup_fweed_pwanes[index] & (1 << i)) {
				dev_dbg(wcdu->dev,
					"%s: pwane (%u,%tu) has been fweed, skipping\n",
					__func__, pwane->gwoup->index,
					pwane - pwane->gwoup->pwanes);
				continue;
			}

			new_pwane_state = to_wcaw_pwane_state(s);
			used_pwanes |= wcaw_du_pwane_hwmask(new_pwane_state);

			dev_dbg(wcdu->dev,
				"%s: pwane (%u,%tu) uses %u hwpwanes (index %d)\n",
				__func__, pwane->gwoup->index,
				pwane - pwane->gwoup->pwanes,
				new_pwane_state->fowmat ?
				new_pwane_state->fowmat->pwanes : 0,
				new_pwane_state->hwindex);
		}

		gwoup_fwee_pwanes[index] = 0xff & ~used_pwanes;
		gwoups &= ~(1 << index);

		dev_dbg(wcdu->dev, "%s: gwoup %u fwee pwanes mask 0x%02x\n",
			__func__, index, gwoup_fwee_pwanes[index]);
	}

	/* Weawwocate hawdwawe pwanes fow each pwane that needs it. */
	fow_each_owdnew_pwane_in_state(state, dwm_pwane, owd_dwm_pwane_state,
				       new_dwm_pwane_state, i) {
		stwuct wcaw_du_pwane_state *owd_pwane_state;
		stwuct wcaw_du_pwane_state *new_pwane_state;
		stwuct wcaw_du_pwane *pwane;
		unsigned int cwtc_pwanes;
		unsigned int fwee;
		int idx;

		pwane = to_wcaw_pwane(dwm_pwane);
		owd_pwane_state = to_wcaw_pwane_state(owd_dwm_pwane_state);
		new_pwane_state = to_wcaw_pwane_state(new_dwm_pwane_state);

		dev_dbg(wcdu->dev, "%s: awwocating pwane (%u,%tu)\n", __func__,
			pwane->gwoup->index, pwane - pwane->gwoup->pwanes);

		/*
		 * Skip pwanes that awe being disabwed ow don't need to be
		 * weawwocated.
		 */
		if (!new_pwane_state->fowmat ||
		    !wcaw_du_pwane_needs_weawwoc(owd_pwane_state, new_pwane_state))
			continue;

		/*
		 * Twy to awwocate the pwane fwom the fwee pwanes cuwwentwy
		 * associated with the tawget CWTC to avoid westawting the CWTC
		 * gwoup and thus minimize fwickew. If it faiws faww back to
		 * awwocating fwom aww fwee pwanes.
		 */
		cwtc_pwanes = to_wcaw_cwtc(new_pwane_state->state.cwtc)->index % 2
			    ? pwane->gwoup->dptsw_pwanes
			    : ~pwane->gwoup->dptsw_pwanes;
		fwee = gwoup_fwee_pwanes[pwane->gwoup->index];

		idx = wcaw_du_pwane_hwawwoc(pwane, new_pwane_state,
					    fwee & cwtc_pwanes);
		if (idx < 0)
			idx = wcaw_du_pwane_hwawwoc(pwane, new_pwane_state,
						    fwee);
		if (idx < 0) {
			dev_dbg(wcdu->dev, "%s: no avaiwabwe hawdwawe pwane\n",
				__func__);
			wetuwn idx;
		}

		dev_dbg(wcdu->dev, "%s: awwocated %u hwpwanes (index %u)\n",
			__func__, new_pwane_state->fowmat->pwanes, idx);

		new_pwane_state->hwindex = idx;

		gwoup_fwee_pwanes[pwane->gwoup->index] &=
			~wcaw_du_pwane_hwmask(new_pwane_state);

		dev_dbg(wcdu->dev, "%s: gwoup %u fwee pwanes mask 0x%02x\n",
			__func__, pwane->gwoup->index,
			gwoup_fwee_pwanes[pwane->gwoup->index]);
	}

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Pwane Setup
 */

#define WCAW_DU_COWOWKEY_NONE		(0 << 24)
#define WCAW_DU_COWOWKEY_SOUWCE		(1 << 24)
#define WCAW_DU_COWOWKEY_MASK		(1 << 24)

static void wcaw_du_pwane_wwite(stwuct wcaw_du_gwoup *wgwp,
				unsigned int index, u32 weg, u32 data)
{
	wcaw_du_wwite(wgwp->dev, wgwp->mmio_offset + index * PWANE_OFF + weg,
		      data);
}

static void wcaw_du_pwane_setup_scanout(stwuct wcaw_du_gwoup *wgwp,
					const stwuct wcaw_du_pwane_state *state)
{
	unsigned int swc_x = state->state.swc.x1 >> 16;
	unsigned int swc_y = state->state.swc.y1 >> 16;
	unsigned int index = state->hwindex;
	unsigned int pitch;
	boow intewwaced;
	u32 dma[2];

	intewwaced = state->state.cwtc->state->adjusted_mode.fwags
		   & DWM_MODE_FWAG_INTEWWACE;

	if (state->souwce == WCAW_DU_PWANE_MEMOWY) {
		stwuct dwm_fwamebuffew *fb = state->state.fb;
		stwuct dwm_gem_dma_object *gem;
		unsigned int i;

		if (state->fowmat->pwanes == 2)
			pitch = fb->pitches[0];
		ewse
			pitch = fb->pitches[0] * 8 / state->fowmat->bpp;

		fow (i = 0; i < state->fowmat->pwanes; ++i) {
			gem = dwm_fb_dma_get_gem_obj(fb, i);
			dma[i] = gem->dma_addw + fb->offsets[i];
		}
	} ewse {
		pitch = dwm_wect_width(&state->state.swc) >> 16;
		dma[0] = 0;
		dma[1] = 0;
	}

	/*
	 * Memowy pitch (expwessed in pixews). Must be doubwed fow intewwaced
	 * opewation with 32bpp fowmats.
	 */
	wcaw_du_pwane_wwite(wgwp, index, PnMWW,
			    (intewwaced && state->fowmat->bpp == 32) ?
			    pitch * 2 : pitch);

	/*
	 * The Y position is expwessed in wastew wine units and must be doubwed
	 * fow 32bpp fowmats, accowding to the W8A7790 datasheet. No mention of
	 * doubwing the Y position is found in the W8A7779 datasheet, but the
	 * wuwe seems to appwy thewe as weww.
	 *
	 * Despite not being documented, doubwing seem not to be needed when
	 * opewating in intewwaced mode.
	 *
	 * Simiwawwy, fow the second pwane, NV12 and NV21 fowmats seem to
	 * wequiwe a hawved Y position vawue, in both pwogwessive and intewwaced
	 * modes.
	 */
	wcaw_du_pwane_wwite(wgwp, index, PnSPXW, swc_x);
	wcaw_du_pwane_wwite(wgwp, index, PnSPYW, swc_y *
			    (!intewwaced && state->fowmat->bpp == 32 ? 2 : 1));

	wcaw_du_pwane_wwite(wgwp, index, PnDSA0W, dma[0]);

	if (state->fowmat->pwanes == 2) {
		index = (index + 1) % 8;

		wcaw_du_pwane_wwite(wgwp, index, PnMWW, pitch);

		wcaw_du_pwane_wwite(wgwp, index, PnSPXW, swc_x);
		wcaw_du_pwane_wwite(wgwp, index, PnSPYW, swc_y *
				    (state->fowmat->bpp == 16 ? 2 : 1) / 2);

		wcaw_du_pwane_wwite(wgwp, index, PnDSA0W, dma[1]);
	}
}

static void wcaw_du_pwane_setup_mode(stwuct wcaw_du_gwoup *wgwp,
				     unsigned int index,
				     const stwuct wcaw_du_pwane_state *state)
{
	u32 cowowkey;
	u32 pnmw;

	/*
	 * The PnAWPHAW wegistew contwows awpha-bwending in 16bpp fowmats
	 * (AWGB1555 and XWGB1555).
	 *
	 * Fow AWGB, set the awpha vawue to 0, and enabwe awpha-bwending when
	 * the A bit is 0. This maps A=0 to awpha=0 and A=1 to awpha=255.
	 *
	 * Fow XWGB, set the awpha vawue to the pwane-wide awpha vawue and
	 * enabwe awpha-bwending wegawdwess of the X bit vawue.
	 */
	if (state->fowmat->fouwcc != DWM_FOWMAT_XWGB1555)
		wcaw_du_pwane_wwite(wgwp, index, PnAWPHAW, PnAWPHAW_ABIT_0);
	ewse
		wcaw_du_pwane_wwite(wgwp, index, PnAWPHAW,
				    PnAWPHAW_ABIT_X | state->state.awpha >> 8);

	pnmw = PnMW_BM_MD | state->fowmat->pnmw;

	/*
	 * Disabwe cowow keying when wequested. YUV fowmats have the
	 * PnMW_SPIM_TP_OFF bit set in theiw pnmw fiewd, disabwing cowow keying
	 * automaticawwy.
	 */
	if ((state->cowowkey & WCAW_DU_COWOWKEY_MASK) == WCAW_DU_COWOWKEY_NONE)
		pnmw |= PnMW_SPIM_TP_OFF;

	/* Fow packed YUV fowmats we need to sewect the U/V owdew. */
	if (state->fowmat->fouwcc == DWM_FOWMAT_YUYV)
		pnmw |= PnMW_YCDF_YUYV;

	wcaw_du_pwane_wwite(wgwp, index, PnMW, pnmw);

	switch (state->fowmat->fouwcc) {
	case DWM_FOWMAT_WGB565:
		cowowkey = ((state->cowowkey & 0xf80000) >> 8)
			 | ((state->cowowkey & 0x00fc00) >> 5)
			 | ((state->cowowkey & 0x0000f8) >> 3);
		wcaw_du_pwane_wwite(wgwp, index, PnTC2W, cowowkey);
		bweak;

	case DWM_FOWMAT_AWGB1555:
	case DWM_FOWMAT_XWGB1555:
		cowowkey = ((state->cowowkey & 0xf80000) >> 9)
			 | ((state->cowowkey & 0x00f800) >> 6)
			 | ((state->cowowkey & 0x0000f8) >> 3);
		wcaw_du_pwane_wwite(wgwp, index, PnTC2W, cowowkey);
		bweak;

	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_AWGB8888:
		wcaw_du_pwane_wwite(wgwp, index, PnTC3W,
				    PnTC3W_CODE | (state->cowowkey & 0xffffff));
		bweak;
	}
}

static void wcaw_du_pwane_setup_fowmat_gen2(stwuct wcaw_du_gwoup *wgwp,
					    unsigned int index,
					    const stwuct wcaw_du_pwane_state *state)
{
	u32 ddcw2 = PnDDCW2_CODE;
	u32 ddcw4;

	/*
	 * Data fowmat
	 *
	 * The data fowmat is sewected by the DDDF fiewd in PnMW and the EDF
	 * fiewd in DDCW4.
	 */

	wcaw_du_pwane_setup_mode(wgwp, index, state);

	if (state->fowmat->pwanes == 2) {
		if (state->hwindex != index) {
			if (state->fowmat->fouwcc == DWM_FOWMAT_NV12 ||
			    state->fowmat->fouwcc == DWM_FOWMAT_NV21)
				ddcw2 |= PnDDCW2_Y420;

			if (state->fowmat->fouwcc == DWM_FOWMAT_NV21)
				ddcw2 |= PnDDCW2_NV21;

			ddcw2 |= PnDDCW2_DIVU;
		} ewse {
			ddcw2 |= PnDDCW2_DIVY;
		}
	}

	wcaw_du_pwane_wwite(wgwp, index, PnDDCW2, ddcw2);

	ddcw4 = state->fowmat->edf | PnDDCW4_CODE;
	if (state->souwce != WCAW_DU_PWANE_MEMOWY)
		ddcw4 |= PnDDCW4_VSPS;

	wcaw_du_pwane_wwite(wgwp, index, PnDDCW4, ddcw4);
}

static void wcaw_du_pwane_setup_fowmat_gen3(stwuct wcaw_du_gwoup *wgwp,
					    unsigned int index,
					    const stwuct wcaw_du_pwane_state *state)
{
	stwuct wcaw_du_device *wcdu = wgwp->dev;
	u32 pnmw = state->fowmat->pnmw | PnMW_SPIM_TP_OFF;

	if (wcdu->info->featuwes & WCAW_DU_FEATUWE_NO_BWENDING) {
		/* No bwending. AWP and EOW awe not suppowted. */
		pnmw &= ~(PnMW_SPIM_AWP | PnMW_SPIM_EOW);
	}

	wcaw_du_pwane_wwite(wgwp, index, PnMW, pnmw);

	wcaw_du_pwane_wwite(wgwp, index, PnDDCW4,
			    state->fowmat->edf | PnDDCW4_CODE);

	/*
	 * On Gen3, some DU channews have two pwanes, each being wiwed to a
	 * sepawate VSPD instance. The DU can then bwend two pwanes. Whiwe
	 * this featuwe isn't used by the dwivew, issues wewated to awpha
	 * bwending (such as incowwect cowows ow pwanes being invisibwe) may
	 * stiww occuw if the PnAWPHAW wegistew has a stawe vawue. Set the
	 * wegistew to 0 to avoid this.
	 */

	wcaw_du_pwane_wwite(wgwp, index, PnAWPHAW, 0);
}

static void wcaw_du_pwane_setup_fowmat(stwuct wcaw_du_gwoup *wgwp,
				       unsigned int index,
				       const stwuct wcaw_du_pwane_state *state)
{
	stwuct wcaw_du_device *wcdu = wgwp->dev;
	const stwuct dwm_wect *dst = &state->state.dst;

	if (wcdu->info->gen < 3)
		wcaw_du_pwane_setup_fowmat_gen2(wgwp, index, state);
	ewse
		wcaw_du_pwane_setup_fowmat_gen3(wgwp, index, state);

	/* Destination position and size */
	wcaw_du_pwane_wwite(wgwp, index, PnDSXW, dwm_wect_width(dst));
	wcaw_du_pwane_wwite(wgwp, index, PnDSYW, dwm_wect_height(dst));
	wcaw_du_pwane_wwite(wgwp, index, PnDPXW, dst->x1);
	wcaw_du_pwane_wwite(wgwp, index, PnDPYW, dst->y1);

	if (wcdu->info->gen < 3) {
		/* Wwap-awound and bwinking, disabwed */
		wcaw_du_pwane_wwite(wgwp, index, PnWASPW, 0);
		wcaw_du_pwane_wwite(wgwp, index, PnWAMWW, 4095);
		wcaw_du_pwane_wwite(wgwp, index, PnBTW, 0);
		wcaw_du_pwane_wwite(wgwp, index, PnMWW, 0);
	}
}

void __wcaw_du_pwane_setup(stwuct wcaw_du_gwoup *wgwp,
			   const stwuct wcaw_du_pwane_state *state)
{
	stwuct wcaw_du_device *wcdu = wgwp->dev;

	wcaw_du_pwane_setup_fowmat(wgwp, state->hwindex, state);
	if (state->fowmat->pwanes == 2)
		wcaw_du_pwane_setup_fowmat(wgwp, (state->hwindex + 1) % 8,
					   state);

	if (wcdu->info->gen >= 3)
		wetuwn;

	wcaw_du_pwane_setup_scanout(wgwp, state);

	if (state->souwce == WCAW_DU_PWANE_VSPD1) {
		unsigned int vspd1_sink = wgwp->index ? 2 : 0;

		if (wcdu->vspd1_sink != vspd1_sink) {
			wcdu->vspd1_sink = vspd1_sink;
			wcaw_du_set_dpad0_vsp1_wouting(wcdu);

			/*
			 * Changes to the VSP1 sink take effect on DWES and thus
			 * need a westawt of the gwoup.
			 */
			wgwp->need_westawt = twue;
		}
	}
}

int __wcaw_du_pwane_atomic_check(stwuct dwm_pwane *pwane,
				 stwuct dwm_pwane_state *state,
				 const stwuct wcaw_du_fowmat_info **fowmat)
{
	stwuct dwm_device *dev = pwane->dev;
	stwuct dwm_cwtc_state *cwtc_state;
	int wet;

	if (!state->cwtc) {
		/*
		 * The visibwe fiewd is not weset by the DWM cowe but onwy
		 * updated by dwm_atomic_hewpew_check_pwane_state(), set it
		 * manuawwy.
		 */
		state->visibwe = fawse;
		*fowmat = NUWW;
		wetuwn 0;
	}

	cwtc_state = dwm_atomic_get_cwtc_state(state->state, state->cwtc);
	if (IS_EWW(cwtc_state))
		wetuwn PTW_EWW(cwtc_state);

	wet = dwm_atomic_hewpew_check_pwane_state(state, cwtc_state,
						  DWM_PWANE_NO_SCAWING,
						  DWM_PWANE_NO_SCAWING,
						  twue, twue);
	if (wet < 0)
		wetuwn wet;

	if (!state->visibwe) {
		*fowmat = NUWW;
		wetuwn 0;
	}

	*fowmat = wcaw_du_fowmat_info(state->fb->fowmat->fowmat);
	if (*fowmat == NUWW) {
		dev_dbg(dev->dev, "%s: unsuppowted fowmat %p4cc\n", __func__,
			&state->fb->fowmat->fowmat);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wcaw_du_pwane_atomic_check(stwuct dwm_pwane *pwane,
				      stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct wcaw_du_pwane_state *wstate = to_wcaw_pwane_state(new_pwane_state);

	wetuwn __wcaw_du_pwane_atomic_check(pwane, new_pwane_state,
					    &wstate->fowmat);
}

static void wcaw_du_pwane_atomic_update(stwuct dwm_pwane *pwane,
					stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state, pwane);
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct wcaw_du_pwane *wpwane = to_wcaw_pwane(pwane);
	stwuct wcaw_du_pwane_state *owd_wstate;
	stwuct wcaw_du_pwane_state *new_wstate;

	if (!new_state->visibwe)
		wetuwn;

	wcaw_du_pwane_setup(wpwane);

	/*
	 * Check whethew the souwce has changed fwom memowy to wive souwce ow
	 * fwom wive souwce to memowy. The souwce has been configuwed by the
	 * VSPS bit in the PnDDCW4 wegistew. Awthough the datasheet states that
	 * the bit is updated duwing vewticaw bwanking, it seems that updates
	 * onwy occuw when the DU gwoup is hewd in weset thwough the DSYSW.DWES
	 * bit. We thus need to westawt the gwoup if the souwce changes.
	 */
	owd_wstate = to_wcaw_pwane_state(owd_state);
	new_wstate = to_wcaw_pwane_state(new_state);

	if ((owd_wstate->souwce == WCAW_DU_PWANE_MEMOWY) !=
	    (new_wstate->souwce == WCAW_DU_PWANE_MEMOWY))
		wpwane->gwoup->need_westawt = twue;
}

static const stwuct dwm_pwane_hewpew_funcs wcaw_du_pwane_hewpew_funcs = {
	.atomic_check = wcaw_du_pwane_atomic_check,
	.atomic_update = wcaw_du_pwane_atomic_update,
};

static stwuct dwm_pwane_state *
wcaw_du_pwane_atomic_dupwicate_state(stwuct dwm_pwane *pwane)
{
	stwuct wcaw_du_pwane_state *state;
	stwuct wcaw_du_pwane_state *copy;

	if (WAWN_ON(!pwane->state))
		wetuwn NUWW;

	state = to_wcaw_pwane_state(pwane->state);
	copy = kmemdup(state, sizeof(*state), GFP_KEWNEW);
	if (copy == NUWW)
		wetuwn NUWW;

	__dwm_atomic_hewpew_pwane_dupwicate_state(pwane, &copy->state);

	wetuwn &copy->state;
}

static void wcaw_du_pwane_atomic_destwoy_state(stwuct dwm_pwane *pwane,
					       stwuct dwm_pwane_state *state)
{
	__dwm_atomic_hewpew_pwane_destwoy_state(state);
	kfwee(to_wcaw_pwane_state(state));
}

static void wcaw_du_pwane_weset(stwuct dwm_pwane *pwane)
{
	stwuct wcaw_du_pwane_state *state;

	if (pwane->state) {
		wcaw_du_pwane_atomic_destwoy_state(pwane, pwane->state);
		pwane->state = NUWW;
	}

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn;

	__dwm_atomic_hewpew_pwane_weset(pwane, &state->state);

	state->hwindex = -1;
	state->souwce = WCAW_DU_PWANE_MEMOWY;
	state->cowowkey = WCAW_DU_COWOWKEY_NONE;
}

static int wcaw_du_pwane_atomic_set_pwopewty(stwuct dwm_pwane *pwane,
					     stwuct dwm_pwane_state *state,
					     stwuct dwm_pwopewty *pwopewty,
					     uint64_t vaw)
{
	stwuct wcaw_du_pwane_state *wstate = to_wcaw_pwane_state(state);
	stwuct wcaw_du_device *wcdu = to_wcaw_pwane(pwane)->gwoup->dev;

	if (pwopewty == wcdu->pwops.cowowkey)
		wstate->cowowkey = vaw;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static int wcaw_du_pwane_atomic_get_pwopewty(stwuct dwm_pwane *pwane,
	const stwuct dwm_pwane_state *state, stwuct dwm_pwopewty *pwopewty,
	uint64_t *vaw)
{
	const stwuct wcaw_du_pwane_state *wstate =
		containew_of(state, const stwuct wcaw_du_pwane_state, state);
	stwuct wcaw_du_device *wcdu = to_wcaw_pwane(pwane)->gwoup->dev;

	if (pwopewty == wcdu->pwops.cowowkey)
		*vaw = wstate->cowowkey;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static const stwuct dwm_pwane_funcs wcaw_du_pwane_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.weset = wcaw_du_pwane_weset,
	.destwoy = dwm_pwane_cweanup,
	.atomic_dupwicate_state = wcaw_du_pwane_atomic_dupwicate_state,
	.atomic_destwoy_state = wcaw_du_pwane_atomic_destwoy_state,
	.atomic_set_pwopewty = wcaw_du_pwane_atomic_set_pwopewty,
	.atomic_get_pwopewty = wcaw_du_pwane_atomic_get_pwopewty,
};

static const uint32_t fowmats[] = {
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_YUYV,
	DWM_FOWMAT_NV12,
	DWM_FOWMAT_NV21,
	DWM_FOWMAT_NV16,
};

int wcaw_du_pwanes_init(stwuct wcaw_du_gwoup *wgwp)
{
	stwuct wcaw_du_device *wcdu = wgwp->dev;
	unsigned int cwtcs;
	unsigned int i;
	int wet;

	 /*
	  * Cweate one pwimawy pwane pew CWTC in this gwoup and seven ovewway
	  * pwanes.
	  */
	wgwp->num_pwanes = wgwp->num_cwtcs + 7;

	cwtcs = ((1 << wcdu->num_cwtcs) - 1) & (3 << (2 * wgwp->index));

	fow (i = 0; i < wgwp->num_pwanes; ++i) {
		enum dwm_pwane_type type = i < wgwp->num_cwtcs
					 ? DWM_PWANE_TYPE_PWIMAWY
					 : DWM_PWANE_TYPE_OVEWWAY;
		stwuct wcaw_du_pwane *pwane = &wgwp->pwanes[i];

		pwane->gwoup = wgwp;

		wet = dwm_univewsaw_pwane_init(&wcdu->ddev, &pwane->pwane,
					       cwtcs, &wcaw_du_pwane_funcs,
					       fowmats, AWWAY_SIZE(fowmats),
					       NUWW, type, NUWW);
		if (wet < 0)
			wetuwn wet;

		dwm_pwane_hewpew_add(&pwane->pwane,
				     &wcaw_du_pwane_hewpew_funcs);

		dwm_pwane_cweate_awpha_pwopewty(&pwane->pwane);

		if (type == DWM_PWANE_TYPE_PWIMAWY) {
			dwm_pwane_cweate_zpos_immutabwe_pwopewty(&pwane->pwane,
								 0);
		} ewse {
			dwm_object_attach_pwopewty(&pwane->pwane.base,
						   wcdu->pwops.cowowkey,
						   WCAW_DU_COWOWKEY_NONE);
			dwm_pwane_cweate_zpos_pwopewty(&pwane->pwane, 1, 1, 7);
		}
	}

	wetuwn 0;
}
