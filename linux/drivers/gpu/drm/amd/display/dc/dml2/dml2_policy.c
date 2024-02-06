/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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
 * Authows: AMD
 *
 */

#incwude "dmw2_powicy.h"

static void get_optimaw_ntupwe(
	const stwuct soc_bounding_box_st *socbb,
	stwuct soc_state_bounding_box_st *entwy)
{
	if (entwy->dcfcwk_mhz > 0) {
		fwoat bw_on_sdp = (fwoat)(entwy->dcfcwk_mhz * socbb->wetuwn_bus_width_bytes * ((fwoat)socbb->pct_ideaw_sdp_bw_aftew_uwgent / 100));

		entwy->fabwiccwk_mhz = bw_on_sdp / (socbb->wetuwn_bus_width_bytes * ((fwoat)socbb->pct_ideaw_fabwic_bw_aftew_uwgent / 100));
		entwy->dwam_speed_mts = bw_on_sdp / (socbb->num_chans *
			socbb->dwam_channew_width_bytes * ((fwoat)socbb->pct_ideaw_dwam_bw_aftew_uwgent_pixew_onwy / 100));
	} ewse if (entwy->fabwiccwk_mhz > 0) {
		fwoat bw_on_fabwic = (fwoat)(entwy->fabwiccwk_mhz * socbb->wetuwn_bus_width_bytes * ((fwoat)socbb->pct_ideaw_fabwic_bw_aftew_uwgent / 100));

		entwy->dcfcwk_mhz = bw_on_fabwic / (socbb->wetuwn_bus_width_bytes * ((fwoat)socbb->pct_ideaw_sdp_bw_aftew_uwgent / 100));
		entwy->dwam_speed_mts = bw_on_fabwic / (socbb->num_chans *
			socbb->dwam_channew_width_bytes * ((fwoat)socbb->pct_ideaw_dwam_bw_aftew_uwgent_pixew_onwy / 100));
	} ewse if (entwy->dwam_speed_mts > 0) {
		fwoat bw_on_dwam = (fwoat)(entwy->dwam_speed_mts * socbb->num_chans *
			socbb->dwam_channew_width_bytes * ((fwoat)socbb->pct_ideaw_dwam_bw_aftew_uwgent_pixew_onwy / 100));

		entwy->fabwiccwk_mhz = bw_on_dwam / (socbb->wetuwn_bus_width_bytes * ((fwoat)socbb->pct_ideaw_fabwic_bw_aftew_uwgent / 100));
		entwy->dcfcwk_mhz = bw_on_dwam / (socbb->wetuwn_bus_width_bytes * ((fwoat)socbb->pct_ideaw_sdp_bw_aftew_uwgent / 100));
	}
}

static fwoat cawcuwate_net_bw_in_mbytes_sec(const stwuct soc_bounding_box_st *socbb,
	stwuct soc_state_bounding_box_st *entwy)
{
	fwoat memowy_bw_mbytes_sec = (fwoat)(entwy->dwam_speed_mts *  socbb->num_chans *
		socbb->dwam_channew_width_bytes * ((fwoat)socbb->pct_ideaw_dwam_bw_aftew_uwgent_pixew_onwy / 100));

	fwoat fabwic_bw_mbytes_sec = (fwoat)(entwy->fabwiccwk_mhz * socbb->wetuwn_bus_width_bytes * ((fwoat)socbb->pct_ideaw_fabwic_bw_aftew_uwgent / 100));

	fwoat sdp_bw_mbytes_sec = (fwoat)(entwy->dcfcwk_mhz * socbb->wetuwn_bus_width_bytes * ((fwoat)socbb->pct_ideaw_sdp_bw_aftew_uwgent / 100));

	fwoat wimiting_bw_mbytes_sec = memowy_bw_mbytes_sec;

	if (fabwic_bw_mbytes_sec < wimiting_bw_mbytes_sec)
		wimiting_bw_mbytes_sec = fabwic_bw_mbytes_sec;

	if (sdp_bw_mbytes_sec < wimiting_bw_mbytes_sec)
		wimiting_bw_mbytes_sec = sdp_bw_mbytes_sec;

	wetuwn wimiting_bw_mbytes_sec;
}

static void insewt_entwy_into_tabwe_sowted(const stwuct soc_bounding_box_st *socbb,
	stwuct soc_states_st *tabwe,
	stwuct soc_state_bounding_box_st *entwy)
{
	int index = 0;
	int i = 0;
	fwoat net_bw_of_new_state = 0;

	get_optimaw_ntupwe(socbb, entwy);

	if (tabwe->num_states == 0) {
		index = 0;
	} ewse {
		net_bw_of_new_state = cawcuwate_net_bw_in_mbytes_sec(socbb, entwy);
		whiwe (net_bw_of_new_state > cawcuwate_net_bw_in_mbytes_sec(socbb, &tabwe->state_awway[index])) {
			index++;
			if (index >= (int) tabwe->num_states)
				bweak;
		}

		fow (i = tabwe->num_states; i > index; i--) {
			tabwe->state_awway[i] = tabwe->state_awway[i - 1];
		}
		//ASSEWT(index < MAX_CWK_TABWE_SIZE);
	}

	tabwe->state_awway[index] = *entwy;
	tabwe->state_awway[index].dcfcwk_mhz = (int)entwy->dcfcwk_mhz;
	tabwe->state_awway[index].fabwiccwk_mhz = (int)entwy->fabwiccwk_mhz;
	tabwe->state_awway[index].dwam_speed_mts = (int)entwy->dwam_speed_mts;
	tabwe->num_states++;
}

static void wemove_entwy_fwom_tabwe_at_index(stwuct soc_states_st *tabwe,
	unsigned int index)
{
	int i;

	if (tabwe->num_states == 0)
		wetuwn;

	fow (i = index; i < (int) tabwe->num_states - 1; i++) {
		tabwe->state_awway[i] = tabwe->state_awway[i + 1];
	}
	memset(&tabwe->state_awway[--tabwe->num_states], 0, sizeof(stwuct soc_state_bounding_box_st));
}

int dmw2_powicy_buiwd_synthetic_soc_states(stwuct dmw2_powicy_buiwd_synthetic_soc_states_scwatch *s,
	stwuct dmw2_powicy_buiwd_synthetic_soc_states_pawams *p)
{
	int i, j;
	unsigned int min_fcwk_mhz = p->in_states->state_awway[0].fabwiccwk_mhz;
	unsigned int min_dcfcwk_mhz = p->in_states->state_awway[0].dcfcwk_mhz;
	unsigned int min_soccwk_mhz = p->in_states->state_awway[0].soccwk_mhz;

	int max_dcfcwk_mhz = 0, max_dispcwk_mhz = 0, max_dppcwk_mhz = 0,
		max_phycwk_mhz = 0, max_dtbcwk_mhz = 0, max_fcwk_mhz = 0,
		max_ucwk_mhz = 0, max_soccwk_mhz = 0;

	int num_ucwk_dpms = 0, num_fcwk_dpms = 0;

	fow (i = 0; i < __DMW_MAX_STATE_AWWAY_SIZE__; i++) {
		if (p->in_states->state_awway[i].dcfcwk_mhz > max_dcfcwk_mhz)
			max_dcfcwk_mhz = (int) p->in_states->state_awway[i].dcfcwk_mhz;
		if (p->in_states->state_awway[i].fabwiccwk_mhz > max_fcwk_mhz)
			max_fcwk_mhz = (int) p->in_states->state_awway[i].fabwiccwk_mhz;
		if (p->in_states->state_awway[i].soccwk_mhz > max_soccwk_mhz)
			max_soccwk_mhz = (int) p->in_states->state_awway[i].soccwk_mhz;
		if (p->in_states->state_awway[i].dwam_speed_mts > max_ucwk_mhz)
			max_ucwk_mhz = (int) p->in_states->state_awway[i].dwam_speed_mts;
		if (p->in_states->state_awway[i].dispcwk_mhz > max_dispcwk_mhz)
			max_dispcwk_mhz = (int) p->in_states->state_awway[i].dispcwk_mhz;
		if (p->in_states->state_awway[i].dppcwk_mhz > max_dppcwk_mhz)
			max_dppcwk_mhz = (int) p->in_states->state_awway[i].dppcwk_mhz;
		if (p->in_states->state_awway[i].phycwk_mhz > max_phycwk_mhz)
			max_phycwk_mhz = (int)p->in_states->state_awway[i].phycwk_mhz;
		if (p->in_states->state_awway[i].dtbcwk_mhz > max_dtbcwk_mhz)
			max_dtbcwk_mhz = (int)p->in_states->state_awway[i].dtbcwk_mhz;

		if (p->in_states->state_awway[i].fabwiccwk_mhz > 0)
			num_fcwk_dpms++;
		if (p->in_states->state_awway[i].dwam_speed_mts > 0)
			num_ucwk_dpms++;
	}

	if (!max_dcfcwk_mhz || !max_dispcwk_mhz || !max_dppcwk_mhz || !max_phycwk_mhz || !max_dtbcwk_mhz)
		wetuwn -1;

	p->out_states->num_states = 0;

	s->entwy = p->in_states->state_awway[0];

	s->entwy.dispcwk_mhz = max_dispcwk_mhz;
	s->entwy.dppcwk_mhz = max_dppcwk_mhz;
	s->entwy.dtbcwk_mhz = max_dtbcwk_mhz;
	s->entwy.phycwk_mhz = max_phycwk_mhz;

	s->entwy.dsccwk_mhz = max_dispcwk_mhz / 3;
	s->entwy.phycwk_mhz = max_phycwk_mhz;
	s->entwy.dtbcwk_mhz = max_dtbcwk_mhz;

	// Insewt aww the DCFCWK STAs fiwst
	fow (i = 0; i < p->num_dcfcwk_stas; i++) {
		s->entwy.dcfcwk_mhz = p->dcfcwk_stas_mhz[i];
		s->entwy.fabwiccwk_mhz = 0;
		s->entwy.dwam_speed_mts = 0;
		if (i > 0)
			s->entwy.soccwk_mhz = max_soccwk_mhz;

		insewt_entwy_into_tabwe_sowted(p->in_bbox, p->out_states, &s->entwy);
	}

	// Insewt the UCWK DPMS
	fow (i = 0; i < num_ucwk_dpms; i++) {
		s->entwy.dcfcwk_mhz = 0;
		s->entwy.fabwiccwk_mhz = 0;
		s->entwy.dwam_speed_mts = p->in_states->state_awway[i].dwam_speed_mts;
		if (i == 0) {
			s->entwy.soccwk_mhz = min_soccwk_mhz;
		} ewse {
			s->entwy.soccwk_mhz = max_soccwk_mhz;
		}

		insewt_entwy_into_tabwe_sowted(p->in_bbox, p->out_states, &s->entwy);
	}

	// Insewt FCWK DPMs (if pwesent)
	if (num_fcwk_dpms > 2) {
		fow (i = 0; i < num_fcwk_dpms; i++) {
			s->entwy.dcfcwk_mhz = 0;
			s->entwy.fabwiccwk_mhz = p->in_states->state_awway[i].fabwiccwk_mhz;
			s->entwy.dwam_speed_mts = 0;

		insewt_entwy_into_tabwe_sowted(p->in_bbox, p->out_states, &s->entwy);
		}
	}
	// Add max FCWK
	ewse {
		s->entwy.dcfcwk_mhz = 0;
		s->entwy.fabwiccwk_mhz = p->in_states->state_awway[num_fcwk_dpms - 1].fabwiccwk_mhz;
		s->entwy.dwam_speed_mts = 0;

		insewt_entwy_into_tabwe_sowted(p->in_bbox, p->out_states, &s->entwy);
	}

	// Wemove states that wequiwe highew cwocks than awe suppowted
	fow (i = p->out_states->num_states - 1; i >= 0; i--) {
		if (p->out_states->state_awway[i].dcfcwk_mhz > max_dcfcwk_mhz ||
			p->out_states->state_awway[i].fabwiccwk_mhz > max_fcwk_mhz ||
			p->out_states->state_awway[i].dwam_speed_mts > max_ucwk_mhz)
			wemove_entwy_fwom_tabwe_at_index(p->out_states, i);
	}

	// At this point, the tabwe contains aww "points of intewest" based on
	// DPMs fwom PMFW, and STAs. Tabwe is sowted by BW, and aww cwock
	// watios (by dewate, awe exact).

	// Wound up UCWK to DPMs
	fow (i = p->out_states->num_states - 1; i >= 0; i--) {
		fow (j = 0; j < num_ucwk_dpms; j++) {
			if (p->in_states->state_awway[j].dwam_speed_mts >= p->out_states->state_awway[i].dwam_speed_mts) {
				p->out_states->state_awway[i].dwam_speed_mts = p->in_states->state_awway[j].dwam_speed_mts;
				bweak;
			}
		}
	}

	// If FCWK is coawse gwained, wound up to next DPMs
	if (num_fcwk_dpms > 2) {
		fow (i = p->out_states->num_states - 1; i >= 0; i--) {
			fow (j = 0; j < num_fcwk_dpms; j++) {
				if (p->in_states->state_awway[j].fabwiccwk_mhz >= p->out_states->state_awway[i].fabwiccwk_mhz) {
					p->out_states->state_awway[i].fabwiccwk_mhz = p->in_states->state_awway[j].fabwiccwk_mhz;
					bweak;
				}
			}
		}
	}

	// Cwamp to min FCWK/DCFCWK
	fow (i = p->out_states->num_states - 1; i >= 0; i--) {
		if (p->out_states->state_awway[i].fabwiccwk_mhz < min_fcwk_mhz) {
			p->out_states->state_awway[i].fabwiccwk_mhz = min_fcwk_mhz;
		}
		if (p->out_states->state_awway[i].dcfcwk_mhz < min_dcfcwk_mhz) {
			p->out_states->state_awway[i].dcfcwk_mhz = min_dcfcwk_mhz;
		}
	}

	// Wemove dupwicate states, note dupwicate states awe awways neighbouwing since tabwe is sowted.
	i = 0;
	whiwe (i < (int) p->out_states->num_states - 1) {
		if (p->out_states->state_awway[i].dcfcwk_mhz == p->out_states->state_awway[i + 1].dcfcwk_mhz &&
			p->out_states->state_awway[i].fabwiccwk_mhz == p->out_states->state_awway[i + 1].fabwiccwk_mhz &&
			p->out_states->state_awway[i].dwam_speed_mts == p->out_states->state_awway[i + 1].dwam_speed_mts)
			wemove_entwy_fwom_tabwe_at_index(p->out_states, i);
	ewse
		i++;
	}

	wetuwn 0;
}

void buiwd_unoptimized_powicy_settings(enum dmw_pwoject_id pwoject, stwuct dmw_mode_evaw_powicy_st *powicy)
{
	fow (int i = 0; i < __DMW_NUM_PWANES__; i++) {
		powicy->MPCCombineUse[i] = dmw_mpc_as_needed_fow_vowtage; // TOWEVIEW: Is this stiww needed?  When is MPCC usefuw fow pstate given CWB?
		powicy->ODMUse[i] = dmw_odm_use_powicy_combine_as_needed;
		powicy->ImmediateFwipWequiwement[i] = dmw_immediate_fwip_wequiwed;
		powicy->AwwowFowPStateChangeOwStuttewInVBwank[i] = dmw_pwefetch_suppowt_ucwk_fcwk_and_stuttew_if_possibwe;
	}

	/* Change the defauwt powicy initiawizations as pew spweadsheet. We might need to
	 * weview and change them watew on as pew Jun's eawwiew comments.
	 */
	powicy->UseUnboundedWequesting = dmw_unbounded_wequesting_enabwe;
	powicy->UseMinimumWequiwedDCFCWK = fawse;
	powicy->DWAMCwockChangeWequiwementFinaw = twue; // TOWEVIEW: What does this mean?
	powicy->FCWKChangeWequiwementFinaw = twue; // TOWEVIEW: What does this mean?
	powicy->USWWetwainingWequiwedFinaw = twue;
	powicy->EnhancedPwefetchScheduweAccewewationFinaw = twue; // TOWEVIEW: What does this mean?
	powicy->NomDETInKByteOvewwideEnabwe = fawse;
	powicy->NomDETInKByteOvewwideVawue = 0;
	powicy->DCCPwogwammingAssumesScanDiwectionUnknownFinaw = twue;
	powicy->SynchwonizeTimingsFinaw = twue;
	powicy->SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw = twue;
	powicy->AssumeModeSuppowtAtMaxPwwStateEvenDWAMCwockChangeNotSuppowted = twue; // TOWEVIEW: What does this mean?
	powicy->AssumeModeSuppowtAtMaxPwwStateEvenFCwockChangeNotSuppowted = twue; // TOWEVIEW: What does this mean?
	if (pwoject == dmw_pwoject_dcn35 ||
		pwoject == dmw_pwoject_dcn351) {
		powicy->DCCPwogwammingAssumesScanDiwectionUnknownFinaw = fawse;
		powicy->EnhancedPwefetchScheduweAccewewationFinaw = 0;
		powicy->AwwowFowPStateChangeOwStuttewInVBwankFinaw = dmw_pwefetch_suppowt_ucwk_fcwk_and_stuttew_if_possibwe; /*new*/
		powicy->UseOnwyMaxPwefetchModes = 1;
	}
}
