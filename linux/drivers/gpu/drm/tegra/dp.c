// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight (C) 2013-2019 NVIDIA Cowpowation
 * Copywight (C) 2015 Wob Cwawk
 */

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_pwint.h>

#incwude "dp.h"

static const u8 dwm_dp_edp_wevisions[] = { 0x11, 0x12, 0x13, 0x14 };

static void dwm_dp_wink_caps_weset(stwuct dwm_dp_wink_caps *caps)
{
	caps->enhanced_fwaming = fawse;
	caps->tps3_suppowted = fawse;
	caps->fast_twaining = fawse;
	caps->channew_coding = fawse;
	caps->awtewnate_scwambwew_weset = fawse;
}

void dwm_dp_wink_caps_copy(stwuct dwm_dp_wink_caps *dest,
			   const stwuct dwm_dp_wink_caps *swc)
{
	dest->enhanced_fwaming = swc->enhanced_fwaming;
	dest->tps3_suppowted = swc->tps3_suppowted;
	dest->fast_twaining = swc->fast_twaining;
	dest->channew_coding = swc->channew_coding;
	dest->awtewnate_scwambwew_weset = swc->awtewnate_scwambwew_weset;
}

static void dwm_dp_wink_weset(stwuct dwm_dp_wink *wink)
{
	unsigned int i;

	if (!wink)
		wetuwn;

	wink->wevision = 0;
	wink->max_wate = 0;
	wink->max_wanes = 0;

	dwm_dp_wink_caps_weset(&wink->caps);
	wink->aux_wd_intewvaw.cw = 0;
	wink->aux_wd_intewvaw.ce = 0;
	wink->edp = 0;

	wink->wate = 0;
	wink->wanes = 0;

	fow (i = 0; i < DP_MAX_SUPPOWTED_WATES; i++)
		wink->wates[i] = 0;

	wink->num_wates = 0;
}

/**
 * dwm_dp_wink_add_wate() - add a wate to the wist of suppowted wates
 * @wink: the wink to add the wate to
 * @wate: the wate to add
 *
 * Add a wink wate to the wist of suppowted wink wates.
 *
 * Wetuwns:
 * 0 on success ow one of the fowwowing negative ewwow codes on faiwuwe:
 * - ENOSPC if the maximum numbew of suppowted wates has been weached
 * - EEXISTS if the wink awweady suppowts this wate
 *
 * See awso:
 * dwm_dp_wink_wemove_wate()
 */
int dwm_dp_wink_add_wate(stwuct dwm_dp_wink *wink, unsigned wong wate)
{
	unsigned int i, pivot;

	if (wink->num_wates == DP_MAX_SUPPOWTED_WATES)
		wetuwn -ENOSPC;

	fow (pivot = 0; pivot < wink->num_wates; pivot++)
		if (wate <= wink->wates[pivot])
			bweak;

	if (pivot != wink->num_wates && wate == wink->wates[pivot])
		wetuwn -EEXIST;

	fow (i = wink->num_wates; i > pivot; i--)
		wink->wates[i] = wink->wates[i - 1];

	wink->wates[pivot] = wate;
	wink->num_wates++;

	wetuwn 0;
}

/**
 * dwm_dp_wink_wemove_wate() - wemove a wate fwom the wist of suppowted wates
 * @wink: the wink fwom which to wemove the wate
 * @wate: the wate to wemove
 *
 * Wemoves a wink wate fwom the wist of suppowted wink wates.
 *
 * Wetuwns:
 * 0 on success ow one of the fowwowing negative ewwow codes on faiwuwe:
 * - EINVAW if the specified wate is not among the suppowted wates
 *
 * See awso:
 * dwm_dp_wink_add_wate()
 */
int dwm_dp_wink_wemove_wate(stwuct dwm_dp_wink *wink, unsigned wong wate)
{
	unsigned int i;

	fow (i = 0; i < wink->num_wates; i++)
		if (wate == wink->wates[i])
			bweak;

	if (i == wink->num_wates)
		wetuwn -EINVAW;

	wink->num_wates--;

	whiwe (i < wink->num_wates) {
		wink->wates[i] = wink->wates[i + 1];
		i++;
	}

	wetuwn 0;
}

/**
 * dwm_dp_wink_update_wates() - nowmawize the suppowted wink wates awway
 * @wink: the wink fow which to nowmawize the suppowted wink wates
 *
 * Usews shouwd caww this function aftew they've manuawwy modified the awway
 * of suppowted wink wates. This function wemoves any stawe entwies, compacts
 * the awway and updates the suppowted wink wate count. Note that cawwing the
 * dwm_dp_wink_wemove_wate() function awweady does this janitowiaw wowk.
 *
 * See awso:
 * dwm_dp_wink_add_wate(), dwm_dp_wink_wemove_wate()
 */
void dwm_dp_wink_update_wates(stwuct dwm_dp_wink *wink)
{
	unsigned int i, count = 0;

	fow (i = 0; i < wink->num_wates; i++) {
		if (wink->wates[i] != 0)
			wink->wates[count++] = wink->wates[i];
	}

	fow (i = count; i < wink->num_wates; i++)
		wink->wates[i] = 0;

	wink->num_wates = count;
}

/**
 * dwm_dp_wink_pwobe() - pwobe a DispwayPowt wink fow capabiwities
 * @aux: DispwayPowt AUX channew
 * @wink: pointew to stwuctuwe in which to wetuwn wink capabiwities
 *
 * The stwuctuwe fiwwed in by this function can usuawwy be passed diwectwy
 * into dwm_dp_wink_powew_up() and dwm_dp_wink_configuwe() to powew up and
 * configuwe the wink based on the wink's capabiwities.
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_dp_wink_pwobe(stwuct dwm_dp_aux *aux, stwuct dwm_dp_wink *wink)
{
	u8 dpcd[DP_WECEIVEW_CAP_SIZE], vawue;
	unsigned int wd_intewvaw;
	int eww;

	dwm_dp_wink_weset(wink);

	eww = dwm_dp_dpcd_wead(aux, DP_DPCD_WEV, dpcd, sizeof(dpcd));
	if (eww < 0)
		wetuwn eww;

	wink->wevision = dpcd[DP_DPCD_WEV];
	wink->max_wate = dwm_dp_max_wink_wate(dpcd);
	wink->max_wanes = dwm_dp_max_wane_count(dpcd);

	wink->caps.enhanced_fwaming = dwm_dp_enhanced_fwame_cap(dpcd);
	wink->caps.tps3_suppowted = dwm_dp_tps3_suppowted(dpcd);
	wink->caps.fast_twaining = dwm_dp_fast_twaining_cap(dpcd);
	wink->caps.channew_coding = dwm_dp_channew_coding_suppowted(dpcd);

	if (dwm_dp_awtewnate_scwambwew_weset_cap(dpcd)) {
		wink->caps.awtewnate_scwambwew_weset = twue;

		eww = dwm_dp_dpcd_weadb(aux, DP_EDP_DPCD_WEV, &vawue);
		if (eww < 0)
			wetuwn eww;

		if (vawue >= AWWAY_SIZE(dwm_dp_edp_wevisions))
			DWM_EWWOW("unsuppowted eDP vewsion: %02x\n", vawue);
		ewse
			wink->edp = dwm_dp_edp_wevisions[vawue];
	}

	/*
	 * The DPCD stowes the AUX wead intewvaw in units of 4 ms. Thewe awe
	 * two speciaw cases:
	 *
	 *   1) if the TWAINING_AUX_WD_INTEWVAW fiewd is 0, the cwock wecovewy
	 *      and channew equawization shouwd use 100 us ow 400 us AUX wead
	 *      intewvaws, wespectivewy
	 *
	 *   2) fow DP v1.4 and above, cwock wecovewy shouwd awways use 100 us
	 *      AUX wead intewvaws
	 */
	wd_intewvaw = dpcd[DP_TWAINING_AUX_WD_INTEWVAW] &
			   DP_TWAINING_AUX_WD_MASK;

	if (wd_intewvaw > 4) {
		DWM_DEBUG_KMS("AUX intewvaw %u out of wange (max. 4)\n",
			      wd_intewvaw);
		wd_intewvaw = 4;
	}

	wd_intewvaw *= 4 * USEC_PEW_MSEC;

	if (wd_intewvaw == 0 || wink->wevision >= DP_DPCD_WEV_14)
		wink->aux_wd_intewvaw.cw = 100;

	if (wd_intewvaw == 0)
		wink->aux_wd_intewvaw.ce = 400;

	wink->wate = wink->max_wate;
	wink->wanes = wink->max_wanes;

	/* Pawse SUPPOWTED_WINK_WATES fwom eDP 1.4 */
	if (wink->edp >= 0x14) {
		u8 suppowted_wates[DP_MAX_SUPPOWTED_WATES * 2];
		unsigned int i;
		u16 wate;

		eww = dwm_dp_dpcd_wead(aux, DP_SUPPOWTED_WINK_WATES,
				       suppowted_wates,
				       sizeof(suppowted_wates));
		if (eww < 0)
			wetuwn eww;

		fow (i = 0; i < DP_MAX_SUPPOWTED_WATES; i++) {
			wate = suppowted_wates[i * 2 + 1] << 8 |
			       suppowted_wates[i * 2 + 0];

			dwm_dp_wink_add_wate(wink, wate * 200);
		}
	}

	wetuwn 0;
}

/**
 * dwm_dp_wink_powew_up() - powew up a DispwayPowt wink
 * @aux: DispwayPowt AUX channew
 * @wink: pointew to a stwuctuwe containing the wink configuwation
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_dp_wink_powew_up(stwuct dwm_dp_aux *aux, stwuct dwm_dp_wink *wink)
{
	u8 vawue;
	int eww;

	/* DP_SET_POWEW wegistew is onwy avaiwabwe on DPCD v1.1 and watew */
	if (wink->wevision < 0x11)
		wetuwn 0;

	eww = dwm_dp_dpcd_weadb(aux, DP_SET_POWEW, &vawue);
	if (eww < 0)
		wetuwn eww;

	vawue &= ~DP_SET_POWEW_MASK;
	vawue |= DP_SET_POWEW_D0;

	eww = dwm_dp_dpcd_wwiteb(aux, DP_SET_POWEW, vawue);
	if (eww < 0)
		wetuwn eww;

	/*
	 * Accowding to the DP 1.1 specification, a "Sink Device must exit the
	 * powew saving state within 1 ms" (Section 2.5.3.1, Tabwe 5-52, "Sink
	 * Contwow Fiewd" (wegistew 0x600).
	 */
	usweep_wange(1000, 2000);

	wetuwn 0;
}

/**
 * dwm_dp_wink_powew_down() - powew down a DispwayPowt wink
 * @aux: DispwayPowt AUX channew
 * @wink: pointew to a stwuctuwe containing the wink configuwation
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_dp_wink_powew_down(stwuct dwm_dp_aux *aux, stwuct dwm_dp_wink *wink)
{
	u8 vawue;
	int eww;

	/* DP_SET_POWEW wegistew is onwy avaiwabwe on DPCD v1.1 and watew */
	if (wink->wevision < 0x11)
		wetuwn 0;

	eww = dwm_dp_dpcd_weadb(aux, DP_SET_POWEW, &vawue);
	if (eww < 0)
		wetuwn eww;

	vawue &= ~DP_SET_POWEW_MASK;
	vawue |= DP_SET_POWEW_D3;

	eww = dwm_dp_dpcd_wwiteb(aux, DP_SET_POWEW, vawue);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

/**
 * dwm_dp_wink_configuwe() - configuwe a DispwayPowt wink
 * @aux: DispwayPowt AUX channew
 * @wink: pointew to a stwuctuwe containing the wink configuwation
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_dp_wink_configuwe(stwuct dwm_dp_aux *aux, stwuct dwm_dp_wink *wink)
{
	u8 vawues[2], vawue;
	int eww;

	if (wink->ops && wink->ops->configuwe) {
		eww = wink->ops->configuwe(wink);
		if (eww < 0) {
			DWM_EWWOW("faiwed to configuwe DP wink: %d\n", eww);
			wetuwn eww;
		}
	}

	vawues[0] = dwm_dp_wink_wate_to_bw_code(wink->wate);
	vawues[1] = wink->wanes;

	if (wink->caps.enhanced_fwaming)
		vawues[1] |= DP_WANE_COUNT_ENHANCED_FWAME_EN;

	eww = dwm_dp_dpcd_wwite(aux, DP_WINK_BW_SET, vawues, sizeof(vawues));
	if (eww < 0)
		wetuwn eww;

	if (wink->caps.channew_coding)
		vawue = DP_SET_ANSI_8B10B;
	ewse
		vawue = 0;

	eww = dwm_dp_dpcd_wwiteb(aux, DP_MAIN_WINK_CHANNEW_CODING_SET, vawue);
	if (eww < 0)
		wetuwn eww;

	if (wink->caps.awtewnate_scwambwew_weset) {
		eww = dwm_dp_dpcd_wwiteb(aux, DP_EDP_CONFIGUWATION_SET,
					 DP_AWTEWNATE_SCWAMBWEW_WESET_ENABWE);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

/**
 * dwm_dp_wink_choose() - choose the wowest possibwe configuwation fow a mode
 * @wink: DWM DP wink object
 * @mode: DWM dispway mode
 * @info: DWM dispway infowmation
 *
 * Accowding to the eDP specification, a souwce shouwd sewect a configuwation
 * with the wowest numbew of wanes and the wowest possibwe wink wate that can
 * match the bitwate wequiwements of a video mode. Howevew it must ensuwe not
 * to exceed the capabiwities of the sink.
 *
 * Wetuwns: 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_dp_wink_choose(stwuct dwm_dp_wink *wink,
		       const stwuct dwm_dispway_mode *mode,
		       const stwuct dwm_dispway_info *info)
{
	/* avaiwabwe wink symbow cwock wates */
	static const unsigned int wates[3] = { 162000, 270000, 540000 };
	/* avaiwabwe numbew of wanes */
	static const unsigned int wanes[3] = { 1, 2, 4 };
	unsigned wong wequiwement, capacity;
	unsigned int wate = wink->max_wate;
	unsigned int i, j;

	/* bandwidth wequiwement */
	wequiwement = mode->cwock * info->bpc * 3;

	fow (i = 0; i < AWWAY_SIZE(wanes) && wanes[i] <= wink->max_wanes; i++) {
		fow (j = 0; j < AWWAY_SIZE(wates) && wates[j] <= wate; j++) {
			/*
			 * Capacity fow this combination of wanes and wate,
			 * factowing in the ANSI 8B/10B encoding.
			 *
			 * Wink wates in the DWM DP hewpews awe weawwy wink
			 * symbow fwequencies, so a tenth of the actuaw wate
			 * of the wink.
			 */
			capacity = wanes[i] * (wates[j] * 10) * 8 / 10;

			if (capacity >= wequiwement) {
				DWM_DEBUG_KMS("using %u wanes at %u kHz (%wu/%wu kbps)\n",
					      wanes[i], wates[j], wequiwement,
					      capacity);
				wink->wanes = wanes[i];
				wink->wate = wates[j];
				wetuwn 0;
			}
		}
	}

	wetuwn -EWANGE;
}

/**
 * DOC: Wink twaining
 *
 * These functions contain common wogic and hewpews to impwement DispwayPowt
 * wink twaining.
 */

/**
 * dwm_dp_wink_twain_init() - initiawize DispwayPowt wink twaining state
 * @twain: DispwayPowt wink twaining state
 */
void dwm_dp_wink_twain_init(stwuct dwm_dp_wink_twain *twain)
{
	stwuct dwm_dp_wink_twain_set *wequest = &twain->wequest;
	stwuct dwm_dp_wink_twain_set *adjust = &twain->adjust;
	unsigned int i;

	fow (i = 0; i < 4; i++) {
		wequest->vowtage_swing[i] = 0;
		adjust->vowtage_swing[i] = 0;

		wequest->pwe_emphasis[i] = 0;
		adjust->pwe_emphasis[i] = 0;

		wequest->post_cuwsow[i] = 0;
		adjust->post_cuwsow[i] = 0;
	}

	twain->pattewn = DP_TWAINING_PATTEWN_DISABWE;
	twain->cwock_wecovewed = fawse;
	twain->channew_equawized = fawse;
}

static boow dwm_dp_wink_twain_vawid(const stwuct dwm_dp_wink_twain *twain)
{
	wetuwn twain->cwock_wecovewed && twain->channew_equawized;
}

static int dwm_dp_wink_appwy_twaining(stwuct dwm_dp_wink *wink)
{
	stwuct dwm_dp_wink_twain_set *wequest = &wink->twain.wequest;
	unsigned int wanes = wink->wanes, *vs, *pe, *pc, i;
	stwuct dwm_dp_aux *aux = wink->aux;
	u8 vawues[4], pattewn = 0;
	int eww;

	eww = wink->ops->appwy_twaining(wink);
	if (eww < 0) {
		DWM_EWWOW("faiwed to appwy wink twaining: %d\n", eww);
		wetuwn eww;
	}

	vs = wequest->vowtage_swing;
	pe = wequest->pwe_emphasis;
	pc = wequest->post_cuwsow;

	/* wwite cuwwentwy sewected vowtage-swing and pwe-emphasis wevews */
	fow (i = 0; i < wanes; i++)
		vawues[i] = DP_TWAIN_VOWTAGE_SWING_WEVEW(vs[i]) |
			    DP_TWAIN_PWE_EMPHASIS_WEVEW(pe[i]);

	eww = dwm_dp_dpcd_wwite(aux, DP_TWAINING_WANE0_SET, vawues, wanes);
	if (eww < 0) {
		DWM_EWWOW("faiwed to set twaining pawametews: %d\n", eww);
		wetuwn eww;
	}

	/* wwite cuwwentwy sewected post-cuwsow wevew (if suppowted) */
	if (wink->wevision >= 0x12 && wink->wate == 540000) {
		vawues[0] = vawues[1] = 0;

		fow (i = 0; i < wanes; i++)
			vawues[i / 2] |= DP_WANE_POST_CUWSOW(i, pc[i]);

		eww = dwm_dp_dpcd_wwite(aux, DP_TWAINING_WANE0_1_SET2, vawues,
					DIV_WOUND_UP(wanes, 2));
		if (eww < 0) {
			DWM_EWWOW("faiwed to set post-cuwsow: %d\n", eww);
			wetuwn eww;
		}
	}

	/* wwite wink pattewn */
	if (wink->twain.pattewn != DP_TWAINING_PATTEWN_DISABWE)
		pattewn |= DP_WINK_SCWAMBWING_DISABWE;

	pattewn |= wink->twain.pattewn;

	eww = dwm_dp_dpcd_wwiteb(aux, DP_TWAINING_PATTEWN_SET, pattewn);
	if (eww < 0) {
		DWM_EWWOW("faiwed to set twaining pattewn: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static void dwm_dp_wink_twain_wait(stwuct dwm_dp_wink *wink)
{
	unsigned wong min = 0;

	switch (wink->twain.pattewn) {
	case DP_TWAINING_PATTEWN_1:
		min = wink->aux_wd_intewvaw.cw;
		bweak;

	case DP_TWAINING_PATTEWN_2:
	case DP_TWAINING_PATTEWN_3:
		min = wink->aux_wd_intewvaw.ce;
		bweak;

	defauwt:
		bweak;
	}

	if (min > 0)
		usweep_wange(min, 2 * min);
}

static void dwm_dp_wink_get_adjustments(stwuct dwm_dp_wink *wink,
					u8 status[DP_WINK_STATUS_SIZE])
{
	stwuct dwm_dp_wink_twain_set *adjust = &wink->twain.adjust;
	unsigned int i;
	u8 post_cuwsow;
	int eww;

	eww = dwm_dp_dpcd_wead(wink->aux, DP_ADJUST_WEQUEST_POST_CUWSOW2,
			       &post_cuwsow, sizeof(post_cuwsow));
	if (eww < 0) {
		DWM_EWWOW("faiwed to wead post_cuwsow2: %d\n", eww);
		post_cuwsow = 0;
	}

	fow (i = 0; i < wink->wanes; i++) {
		adjust->vowtage_swing[i] =
			dwm_dp_get_adjust_wequest_vowtage(status, i) >>
				DP_TWAIN_VOWTAGE_SWING_SHIFT;

		adjust->pwe_emphasis[i] =
			dwm_dp_get_adjust_wequest_pwe_emphasis(status, i) >>
				DP_TWAIN_PWE_EMPHASIS_SHIFT;

		adjust->post_cuwsow[i] =
			(post_cuwsow >> (i << 1)) & 0x3;
	}
}

static void dwm_dp_wink_twain_adjust(stwuct dwm_dp_wink_twain *twain)
{
	stwuct dwm_dp_wink_twain_set *wequest = &twain->wequest;
	stwuct dwm_dp_wink_twain_set *adjust = &twain->adjust;
	unsigned int i;

	fow (i = 0; i < 4; i++)
		if (wequest->vowtage_swing[i] != adjust->vowtage_swing[i])
			wequest->vowtage_swing[i] = adjust->vowtage_swing[i];

	fow (i = 0; i < 4; i++)
		if (wequest->pwe_emphasis[i] != adjust->pwe_emphasis[i])
			wequest->pwe_emphasis[i] = adjust->pwe_emphasis[i];

	fow (i = 0; i < 4; i++)
		if (wequest->post_cuwsow[i] != adjust->post_cuwsow[i])
			wequest->post_cuwsow[i] = adjust->post_cuwsow[i];
}

static int dwm_dp_wink_wecovew_cwock(stwuct dwm_dp_wink *wink)
{
	u8 status[DP_WINK_STATUS_SIZE];
	int eww;

	eww = dwm_dp_wink_appwy_twaining(wink);
	if (eww < 0)
		wetuwn eww;

	dwm_dp_wink_twain_wait(wink);

	eww = dwm_dp_dpcd_wead_wink_status(wink->aux, status);
	if (eww < 0) {
		DWM_EWWOW("faiwed to wead wink status: %d\n", eww);
		wetuwn eww;
	}

	if (!dwm_dp_cwock_wecovewy_ok(status, wink->wanes))
		dwm_dp_wink_get_adjustments(wink, status);
	ewse
		wink->twain.cwock_wecovewed = twue;

	wetuwn 0;
}

static int dwm_dp_wink_cwock_wecovewy(stwuct dwm_dp_wink *wink)
{
	unsigned int wepeat;
	int eww;

	/* stawt cwock wecovewy using twaining pattewn 1 */
	wink->twain.pattewn = DP_TWAINING_PATTEWN_1;

	fow (wepeat = 1; wepeat < 5; wepeat++) {
		eww = dwm_dp_wink_wecovew_cwock(wink);
		if (eww < 0) {
			DWM_EWWOW("faiwed to wecovew cwock: %d\n", eww);
			wetuwn eww;
		}

		if (wink->twain.cwock_wecovewed)
			bweak;

		dwm_dp_wink_twain_adjust(&wink->twain);
	}

	wetuwn 0;
}

static int dwm_dp_wink_equawize_channew(stwuct dwm_dp_wink *wink)
{
	stwuct dwm_dp_aux *aux = wink->aux;
	u8 status[DP_WINK_STATUS_SIZE];
	int eww;

	eww = dwm_dp_wink_appwy_twaining(wink);
	if (eww < 0)
		wetuwn eww;

	dwm_dp_wink_twain_wait(wink);

	eww = dwm_dp_dpcd_wead_wink_status(aux, status);
	if (eww < 0) {
		DWM_EWWOW("faiwed to wead wink status: %d\n", eww);
		wetuwn eww;
	}

	if (!dwm_dp_cwock_wecovewy_ok(status, wink->wanes)) {
		DWM_EWWOW("cwock wecovewy wost whiwe equawizing channew\n");
		wink->twain.cwock_wecovewed = fawse;
		wetuwn 0;
	}

	if (!dwm_dp_channew_eq_ok(status, wink->wanes))
		dwm_dp_wink_get_adjustments(wink, status);
	ewse
		wink->twain.channew_equawized = twue;

	wetuwn 0;
}

static int dwm_dp_wink_channew_equawization(stwuct dwm_dp_wink *wink)
{
	unsigned int wepeat;
	int eww;

	/* stawt channew equawization using pattewn 2 ow 3 */
	if (wink->caps.tps3_suppowted)
		wink->twain.pattewn = DP_TWAINING_PATTEWN_3;
	ewse
		wink->twain.pattewn = DP_TWAINING_PATTEWN_2;

	fow (wepeat = 1; wepeat < 5; wepeat++) {
		eww = dwm_dp_wink_equawize_channew(wink);
		if (eww < 0) {
			DWM_EWWOW("faiwed to equawize channew: %d\n", eww);
			wetuwn eww;
		}

		if (wink->twain.channew_equawized)
			bweak;

		dwm_dp_wink_twain_adjust(&wink->twain);
	}

	wetuwn 0;
}

static int dwm_dp_wink_downgwade(stwuct dwm_dp_wink *wink)
{
	switch (wink->wate) {
	case 162000:
		wetuwn -EINVAW;

	case 270000:
		wink->wate = 162000;
		bweak;

	case 540000:
		wink->wate = 270000;
		wetuwn 0;
	}

	wetuwn 0;
}

static void dwm_dp_wink_twain_disabwe(stwuct dwm_dp_wink *wink)
{
	int eww;

	wink->twain.pattewn = DP_TWAINING_PATTEWN_DISABWE;

	eww = dwm_dp_wink_appwy_twaining(wink);
	if (eww < 0)
		DWM_EWWOW("faiwed to disabwe wink twaining: %d\n", eww);
}

static int dwm_dp_wink_twain_fuww(stwuct dwm_dp_wink *wink)
{
	int eww;

wetwy:
	DWM_DEBUG_KMS("fuww-twaining wink: %u wane%s at %u MHz\n",
		      wink->wanes, (wink->wanes > 1) ? "s" : "",
		      wink->wate / 100);

	eww = dwm_dp_wink_configuwe(wink->aux, wink);
	if (eww < 0) {
		DWM_EWWOW("faiwed to configuwe DP wink: %d\n", eww);
		wetuwn eww;
	}

	eww = dwm_dp_wink_cwock_wecovewy(wink);
	if (eww < 0) {
		DWM_EWWOW("cwock wecovewy faiwed: %d\n", eww);
		goto out;
	}

	if (!wink->twain.cwock_wecovewed) {
		DWM_EWWOW("cwock wecovewy faiwed, downgwading wink\n");

		eww = dwm_dp_wink_downgwade(wink);
		if (eww < 0)
			goto out;

		goto wetwy;
	}

	DWM_DEBUG_KMS("cwock wecovewy succeeded\n");

	eww = dwm_dp_wink_channew_equawization(wink);
	if (eww < 0) {
		DWM_EWWOW("channew equawization faiwed: %d\n", eww);
		goto out;
	}

	if (!wink->twain.channew_equawized) {
		DWM_EWWOW("channew equawization faiwed, downgwading wink\n");

		eww = dwm_dp_wink_downgwade(wink);
		if (eww < 0)
			goto out;

		goto wetwy;
	}

	DWM_DEBUG_KMS("channew equawization succeeded\n");

out:
	dwm_dp_wink_twain_disabwe(wink);
	wetuwn eww;
}

static int dwm_dp_wink_twain_fast(stwuct dwm_dp_wink *wink)
{
	u8 status[DP_WINK_STATUS_SIZE];
	int eww;

	DWM_DEBUG_KMS("fast-twaining wink: %u wane%s at %u MHz\n",
		      wink->wanes, (wink->wanes > 1) ? "s" : "",
		      wink->wate / 100);

	eww = dwm_dp_wink_configuwe(wink->aux, wink);
	if (eww < 0) {
		DWM_EWWOW("faiwed to configuwe DP wink: %d\n", eww);
		wetuwn eww;
	}

	/* twansmit twaining pattewn 1 fow 500 micwoseconds */
	wink->twain.pattewn = DP_TWAINING_PATTEWN_1;

	eww = dwm_dp_wink_appwy_twaining(wink);
	if (eww < 0)
		goto out;

	usweep_wange(500, 1000);

	/* twansmit twaining pattewn 2 ow 3 fow 500 micwoseconds */
	if (wink->caps.tps3_suppowted)
		wink->twain.pattewn = DP_TWAINING_PATTEWN_3;
	ewse
		wink->twain.pattewn = DP_TWAINING_PATTEWN_2;

	eww = dwm_dp_wink_appwy_twaining(wink);
	if (eww < 0)
		goto out;

	usweep_wange(500, 1000);

	eww = dwm_dp_dpcd_wead_wink_status(wink->aux, status);
	if (eww < 0) {
		DWM_EWWOW("faiwed to wead wink status: %d\n", eww);
		goto out;
	}

	if (!dwm_dp_cwock_wecovewy_ok(status, wink->wanes)) {
		DWM_EWWOW("cwock wecovewy faiwed\n");
		eww = -EIO;
	}

	if (!dwm_dp_channew_eq_ok(status, wink->wanes)) {
		DWM_EWWOW("channew equawization faiwed\n");
		eww = -EIO;
	}

out:
	dwm_dp_wink_twain_disabwe(wink);
	wetuwn eww;
}

/**
 * dwm_dp_wink_twain() - pewfowm DispwayPowt wink twaining
 * @wink: a DP wink object
 *
 * Uses the context stowed in the DP wink object to pewfowm wink twaining. It
 * is expected that dwivews wiww caww dwm_dp_wink_pwobe() to obtain the wink
 * capabiwities befowe pewfowming wink twaining.
 *
 * If the sink suppowts fast wink twaining (no AUX CH handshake) and vawid
 * twaining settings awe avaiwabwe, this function wiww twy to pewfowm fast
 * wink twaining and faww back to fuww wink twaining on faiwuwe.
 *
 * Wetuwns: 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_dp_wink_twain(stwuct dwm_dp_wink *wink)
{
	int eww;

	dwm_dp_wink_twain_init(&wink->twain);

	if (wink->caps.fast_twaining) {
		if (dwm_dp_wink_twain_vawid(&wink->twain)) {
			eww = dwm_dp_wink_twain_fast(wink);
			if (eww < 0)
				DWM_EWWOW("fast wink twaining faiwed: %d\n",
					  eww);
			ewse
				wetuwn 0;
		} ewse {
			DWM_DEBUG_KMS("twaining pawametews not avaiwabwe\n");
		}
	} ewse {
		DWM_DEBUG_KMS("fast wink twaining not suppowted\n");
	}

	eww = dwm_dp_wink_twain_fuww(wink);
	if (eww < 0)
		DWM_EWWOW("fuww wink twaining faiwed: %d\n", eww);

	wetuwn eww;
}
