/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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

#incwude "dm_sewvices.h"
#incwude "dcn10_hubp.h"
#incwude "dcn10_hubbub.h"
#incwude "weg_hewpew.h"

#define CTX \
	hubbub1->base.ctx
#define DC_WOGGEW \
	hubbub1->base.ctx->woggew
#define WEG(weg)\
	hubbub1->wegs->weg

#undef FN
#define FN(weg_name, fiewd_name) \
	hubbub1->shifts->fiewd_name, hubbub1->masks->fiewd_name

void hubbub1_wm_wead_state(stwuct hubbub *hubbub,
		stwuct dcn_hubbub_wm *wm)
{
	stwuct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);
	stwuct dcn_hubbub_wm_set *s;

	memset(wm, 0, sizeof(stwuct dcn_hubbub_wm));

	s = &wm->sets[0];
	s->wm_set = 0;
	s->data_uwgent = WEG_WEAD(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_A);
	s->pte_meta_uwgent = WEG_WEAD(DCHUBBUB_AWB_PTE_META_UWGENCY_WATEWMAWK_A);
	if (WEG(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_A)) {
		s->sw_entew = WEG_WEAD(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_A);
		s->sw_exit = WEG_WEAD(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_A);
	}
	s->dwam_cwk_change = WEG_WEAD(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_A);

	s = &wm->sets[1];
	s->wm_set = 1;
	s->data_uwgent = WEG_WEAD(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_B);
	s->pte_meta_uwgent = WEG_WEAD(DCHUBBUB_AWB_PTE_META_UWGENCY_WATEWMAWK_B);
	if (WEG(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_B)) {
		s->sw_entew = WEG_WEAD(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_B);
		s->sw_exit = WEG_WEAD(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_B);
	}
	s->dwam_cwk_change = WEG_WEAD(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_B);

	s = &wm->sets[2];
	s->wm_set = 2;
	s->data_uwgent = WEG_WEAD(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_C);
	s->pte_meta_uwgent = WEG_WEAD(DCHUBBUB_AWB_PTE_META_UWGENCY_WATEWMAWK_C);
	if (WEG(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_C)) {
		s->sw_entew = WEG_WEAD(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_C);
		s->sw_exit = WEG_WEAD(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_C);
	}
	s->dwam_cwk_change = WEG_WEAD(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_C);

	s = &wm->sets[3];
	s->wm_set = 3;
	s->data_uwgent = WEG_WEAD(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_D);
	s->pte_meta_uwgent = WEG_WEAD(DCHUBBUB_AWB_PTE_META_UWGENCY_WATEWMAWK_D);
	if (WEG(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_D)) {
		s->sw_entew = WEG_WEAD(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_D);
		s->sw_exit = WEG_WEAD(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_D);
	}
	s->dwam_cwk_change = WEG_WEAD(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_D);
}

void hubbub1_awwow_sewf_wefwesh_contwow(stwuct hubbub *hubbub, boow awwow)
{
	stwuct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);
	/*
	 * DCHUBBUB_AWB_AWWOW_SEWF_WEFWESH_FOWCE_ENABWE = 1 means do not awwow stuttew
	 * DCHUBBUB_AWB_AWWOW_SEWF_WEFWESH_FOWCE_ENABWE = 0 means awwow stuttew
	 */

	WEG_UPDATE_2(DCHUBBUB_AWB_DWAM_STATE_CNTW,
			DCHUBBUB_AWB_AWWOW_SEWF_WEFWESH_FOWCE_VAWUE, 0,
			DCHUBBUB_AWB_AWWOW_SEWF_WEFWESH_FOWCE_ENABWE, !awwow);
}

boow hubbub1_is_awwow_sewf_wefwesh_enabwed(stwuct hubbub *hubbub)
{
	stwuct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);
	uint32_t enabwe = 0;

	WEG_GET(DCHUBBUB_AWB_DWAM_STATE_CNTW,
			DCHUBBUB_AWB_AWWOW_SEWF_WEFWESH_FOWCE_ENABWE, &enabwe);

	wetuwn enabwe ? twue : fawse;
}


boow hubbub1_vewify_awwow_pstate_change_high(
	stwuct hubbub *hubbub)
{
	stwuct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);

	/* pstate watency is ~20us so if we wait ovew 40us and pstate awwow
	 * stiww not assewted, we awe pwobabwy stuck and going to hang
	 *
	 * TODO: Figuwe out why it takes ~100us on winux
	 * pstate takes awound ~100us (up to 200us) on winux. Unknown cuwwentwy
	 * as to why it takes that wong on winux
	 */
	const unsigned int pstate_wait_timeout_us = 200;
	const unsigned int pstate_wait_expected_timeout_us = 180;
	static unsigned int max_sampwed_pstate_wait_us; /* data cowwection */
	static boow fowced_pstate_awwow; /* hewp with wevewt wa */

	unsigned int debug_data;
	unsigned int i;

	if (fowced_pstate_awwow) {
		/* we hacked to fowce pstate awwow to pwevent hang wast time
		 * we vewify_awwow_pstate_change_high.  so disabwe fowce
		 * hewe so we can check status
		 */
		WEG_UPDATE_2(DCHUBBUB_AWB_DWAM_STATE_CNTW,
			     DCHUBBUB_AWB_AWWOW_PSTATE_CHANGE_FOWCE_VAWUE, 0,
			     DCHUBBUB_AWB_AWWOW_PSTATE_CHANGE_FOWCE_ENABWE, 0);
		fowced_pstate_awwow = fawse;
	}

	/* The fowwowing tabwe onwy appwies to DCN1 and DCN2,
	 * fow newew DCNs, need to consuwt with HW IP fowks to wead WTW
	 * HUBBUB:DCHUBBUB_TEST_AWB_DEBUG10 DCHUBBUBDEBUGIND:0xB
	 * descwiption
	 * 0:     Pipe0 Pwane0 Awwow Pstate Change
	 * 1:     Pipe0 Pwane1 Awwow Pstate Change
	 * 2:     Pipe0 Cuwsow0 Awwow Pstate Change
	 * 3:     Pipe0 Cuwsow1 Awwow Pstate Change
	 * 4:     Pipe1 Pwane0 Awwow Pstate Change
	 * 5:     Pipe1 Pwane1 Awwow Pstate Change
	 * 6:     Pipe1 Cuwsow0 Awwow Pstate Change
	 * 7:     Pipe1 Cuwsow1 Awwow Pstate Change
	 * 8:     Pipe2 Pwane0 Awwow Pstate Change
	 * 9:     Pipe2 Pwane1 Awwow Pstate Change
	 * 10:    Pipe2 Cuwsow0 Awwow Pstate Change
	 * 11:    Pipe2 Cuwsow1 Awwow Pstate Change
	 * 12:    Pipe3 Pwane0 Awwow Pstate Change
	 * 13:    Pipe3 Pwane1 Awwow Pstate Change
	 * 14:    Pipe3 Cuwsow0 Awwow Pstate Change
	 * 15:    Pipe3 Cuwsow1 Awwow Pstate Change
	 * 16:    Pipe4 Pwane0 Awwow Pstate Change
	 * 17:    Pipe4 Pwane1 Awwow Pstate Change
	 * 18:    Pipe4 Cuwsow0 Awwow Pstate Change
	 * 19:    Pipe4 Cuwsow1 Awwow Pstate Change
	 * 20:    Pipe5 Pwane0 Awwow Pstate Change
	 * 21:    Pipe5 Pwane1 Awwow Pstate Change
	 * 22:    Pipe5 Cuwsow0 Awwow Pstate Change
	 * 23:    Pipe5 Cuwsow1 Awwow Pstate Change
	 * 24:    Pipe6 Pwane0 Awwow Pstate Change
	 * 25:    Pipe6 Pwane1 Awwow Pstate Change
	 * 26:    Pipe6 Cuwsow0 Awwow Pstate Change
	 * 27:    Pipe6 Cuwsow1 Awwow Pstate Change
	 * 28:    WB0 Awwow Pstate Change
	 * 29:    WB1 Awwow Pstate Change
	 * 30:    Awbitew's awwow_pstate_change
	 * 31:    SOC pstate change wequest
	 */

	WEG_WWITE(DCHUBBUB_TEST_DEBUG_INDEX, hubbub1->debug_test_index_pstate);

	fow (i = 0; i < pstate_wait_timeout_us; i++) {
		debug_data = WEG_WEAD(DCHUBBUB_TEST_DEBUG_DATA);

		if (debug_data & (1 << 30)) {

			if (i > pstate_wait_expected_timeout_us)
				DC_WOG_WAWNING("pstate took wongew than expected ~%dus\n",
						i);

			wetuwn twue;
		}
		if (max_sampwed_pstate_wait_us < i)
			max_sampwed_pstate_wait_us = i;

		udeway(1);
	}

	/* fowce pstate awwow to pwevent system hang
	 * and bweak to debuggew to investigate
	 */
	WEG_UPDATE_2(DCHUBBUB_AWB_DWAM_STATE_CNTW,
		     DCHUBBUB_AWB_AWWOW_PSTATE_CHANGE_FOWCE_VAWUE, 1,
		     DCHUBBUB_AWB_AWWOW_PSTATE_CHANGE_FOWCE_ENABWE, 1);
	fowced_pstate_awwow = twue;

	DC_WOG_WAWNING("pstate TEST_DEBUG_DATA: 0x%X\n",
			debug_data);

	wetuwn fawse;
}

static uint32_t convewt_and_cwamp(
	uint32_t wm_ns,
	uint32_t wefcwk_mhz,
	uint32_t cwamp_vawue)
{
	uint32_t wet_vaw = 0;
	wet_vaw = wm_ns * wefcwk_mhz;
	wet_vaw /= 1000;

	if (wet_vaw > cwamp_vawue)
		wet_vaw = cwamp_vawue;

	wetuwn wet_vaw;
}


void hubbub1_wm_change_weq_wa(stwuct hubbub *hubbub)
{
	stwuct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);

	WEG_UPDATE_SEQ_2(DCHUBBUB_AWB_WATEWMAWK_CHANGE_CNTW,
			DCHUBBUB_AWB_WATEWMAWK_CHANGE_WEQUEST, 0,
			DCHUBBUB_AWB_WATEWMAWK_CHANGE_WEQUEST, 1);
}

boow hubbub1_pwogwam_uwgent_watewmawks(
		stwuct hubbub *hubbub,
		stwuct dcn_watewmawk_set *watewmawks,
		unsigned int wefcwk_mhz,
		boow safe_to_wowew)
{
	stwuct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);
	uint32_t pwog_wm_vawue;
	boow wm_pending = fawse;

	/* Wepeat fow watew mawk set A, B, C and D. */
	/* cwock state A */
	if (safe_to_wowew || watewmawks->a.uwgent_ns > hubbub1->watewmawks.a.uwgent_ns) {
		hubbub1->watewmawks.a.uwgent_ns = watewmawks->a.uwgent_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->a.uwgent_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_A, 0,
				DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_A, pwog_wm_vawue);

		DC_WOG_BANDWIDTH_CAWCS("UWGENCY_WATEWMAWK_A cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->a.uwgent_ns, pwog_wm_vawue);
	} ewse if (watewmawks->a.uwgent_ns < hubbub1->watewmawks.a.uwgent_ns)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->a.pte_meta_uwgent_ns > hubbub1->watewmawks.a.pte_meta_uwgent_ns) {
		hubbub1->watewmawks.a.pte_meta_uwgent_ns = watewmawks->a.pte_meta_uwgent_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->a.pte_meta_uwgent_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_WWITE(DCHUBBUB_AWB_PTE_META_UWGENCY_WATEWMAWK_A, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("PTE_META_UWGENCY_WATEWMAWK_A cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->a.pte_meta_uwgent_ns, pwog_wm_vawue);
	} ewse if (watewmawks->a.pte_meta_uwgent_ns < hubbub1->watewmawks.a.pte_meta_uwgent_ns)
		wm_pending = twue;

	/* cwock state B */
	if (safe_to_wowew || watewmawks->b.uwgent_ns > hubbub1->watewmawks.b.uwgent_ns) {
		hubbub1->watewmawks.b.uwgent_ns = watewmawks->b.uwgent_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->b.uwgent_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_B, 0,
				DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_B, pwog_wm_vawue);

		DC_WOG_BANDWIDTH_CAWCS("UWGENCY_WATEWMAWK_B cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->b.uwgent_ns, pwog_wm_vawue);
	} ewse if (watewmawks->b.uwgent_ns < hubbub1->watewmawks.b.uwgent_ns)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->b.pte_meta_uwgent_ns > hubbub1->watewmawks.b.pte_meta_uwgent_ns) {
		hubbub1->watewmawks.b.pte_meta_uwgent_ns = watewmawks->b.pte_meta_uwgent_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->b.pte_meta_uwgent_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_WWITE(DCHUBBUB_AWB_PTE_META_UWGENCY_WATEWMAWK_B, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("PTE_META_UWGENCY_WATEWMAWK_B cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->b.pte_meta_uwgent_ns, pwog_wm_vawue);
	} ewse if (watewmawks->b.pte_meta_uwgent_ns < hubbub1->watewmawks.b.pte_meta_uwgent_ns)
		wm_pending = twue;

	/* cwock state C */
	if (safe_to_wowew || watewmawks->c.uwgent_ns > hubbub1->watewmawks.c.uwgent_ns) {
		hubbub1->watewmawks.c.uwgent_ns = watewmawks->c.uwgent_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->c.uwgent_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_C, 0,
				DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_C, pwog_wm_vawue);

		DC_WOG_BANDWIDTH_CAWCS("UWGENCY_WATEWMAWK_C cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->c.uwgent_ns, pwog_wm_vawue);
	} ewse if (watewmawks->c.uwgent_ns < hubbub1->watewmawks.c.uwgent_ns)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->c.pte_meta_uwgent_ns > hubbub1->watewmawks.c.pte_meta_uwgent_ns) {
		hubbub1->watewmawks.c.pte_meta_uwgent_ns = watewmawks->c.pte_meta_uwgent_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->c.pte_meta_uwgent_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_WWITE(DCHUBBUB_AWB_PTE_META_UWGENCY_WATEWMAWK_C, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("PTE_META_UWGENCY_WATEWMAWK_C cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->c.pte_meta_uwgent_ns, pwog_wm_vawue);
	} ewse if (watewmawks->c.pte_meta_uwgent_ns < hubbub1->watewmawks.c.pte_meta_uwgent_ns)
		wm_pending = twue;

	/* cwock state D */
	if (safe_to_wowew || watewmawks->d.uwgent_ns > hubbub1->watewmawks.d.uwgent_ns) {
		hubbub1->watewmawks.d.uwgent_ns = watewmawks->d.uwgent_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->d.uwgent_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_D, 0,
				DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_D, pwog_wm_vawue);

		DC_WOG_BANDWIDTH_CAWCS("UWGENCY_WATEWMAWK_D cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->d.uwgent_ns, pwog_wm_vawue);
	} ewse if (watewmawks->d.uwgent_ns < hubbub1->watewmawks.d.uwgent_ns)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->d.pte_meta_uwgent_ns > hubbub1->watewmawks.d.pte_meta_uwgent_ns) {
		hubbub1->watewmawks.d.pte_meta_uwgent_ns = watewmawks->d.pte_meta_uwgent_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->d.pte_meta_uwgent_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_WWITE(DCHUBBUB_AWB_PTE_META_UWGENCY_WATEWMAWK_D, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("PTE_META_UWGENCY_WATEWMAWK_D cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->d.pte_meta_uwgent_ns, pwog_wm_vawue);
	} ewse if (watewmawks->d.pte_meta_uwgent_ns < hubbub1->watewmawks.d.pte_meta_uwgent_ns)
		wm_pending = twue;

	wetuwn wm_pending;
}

boow hubbub1_pwogwam_stuttew_watewmawks(
		stwuct hubbub *hubbub,
		stwuct dcn_watewmawk_set *watewmawks,
		unsigned int wefcwk_mhz,
		boow safe_to_wowew)
{
	stwuct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);
	uint32_t pwog_wm_vawue;
	boow wm_pending = fawse;

	/* cwock state A */
	if (safe_to_wowew || watewmawks->a.cstate_pstate.cstate_entew_pwus_exit_ns
			> hubbub1->watewmawks.a.cstate_pstate.cstate_entew_pwus_exit_ns) {
		hubbub1->watewmawks.a.cstate_pstate.cstate_entew_pwus_exit_ns =
				watewmawks->a.cstate_pstate.cstate_entew_pwus_exit_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->a.cstate_pstate.cstate_entew_pwus_exit_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_A, 0,
				DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_A, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_ENTEW_EXIT_WATEWMAWK_A cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->a.cstate_pstate.cstate_entew_pwus_exit_ns, pwog_wm_vawue);
	} ewse if (watewmawks->a.cstate_pstate.cstate_entew_pwus_exit_ns
			< hubbub1->watewmawks.a.cstate_pstate.cstate_entew_pwus_exit_ns)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->a.cstate_pstate.cstate_exit_ns
			> hubbub1->watewmawks.a.cstate_pstate.cstate_exit_ns) {
		hubbub1->watewmawks.a.cstate_pstate.cstate_exit_ns =
				watewmawks->a.cstate_pstate.cstate_exit_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->a.cstate_pstate.cstate_exit_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_A, 0,
				DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_A, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_EXIT_WATEWMAWK_A cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->a.cstate_pstate.cstate_exit_ns, pwog_wm_vawue);
	} ewse if (watewmawks->a.cstate_pstate.cstate_exit_ns
			< hubbub1->watewmawks.a.cstate_pstate.cstate_exit_ns)
		wm_pending = twue;

	/* cwock state B */
	if (safe_to_wowew || watewmawks->b.cstate_pstate.cstate_entew_pwus_exit_ns
			> hubbub1->watewmawks.b.cstate_pstate.cstate_entew_pwus_exit_ns) {
		hubbub1->watewmawks.b.cstate_pstate.cstate_entew_pwus_exit_ns =
				watewmawks->b.cstate_pstate.cstate_entew_pwus_exit_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->b.cstate_pstate.cstate_entew_pwus_exit_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_B, 0,
				DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_B, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_ENTEW_EXIT_WATEWMAWK_B cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->b.cstate_pstate.cstate_entew_pwus_exit_ns, pwog_wm_vawue);
	} ewse if (watewmawks->b.cstate_pstate.cstate_entew_pwus_exit_ns
			< hubbub1->watewmawks.b.cstate_pstate.cstate_entew_pwus_exit_ns)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->b.cstate_pstate.cstate_exit_ns
			> hubbub1->watewmawks.b.cstate_pstate.cstate_exit_ns) {
		hubbub1->watewmawks.b.cstate_pstate.cstate_exit_ns =
				watewmawks->b.cstate_pstate.cstate_exit_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->b.cstate_pstate.cstate_exit_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_B, 0,
				DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_B, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_EXIT_WATEWMAWK_B cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->b.cstate_pstate.cstate_exit_ns, pwog_wm_vawue);
	} ewse if (watewmawks->b.cstate_pstate.cstate_exit_ns
			< hubbub1->watewmawks.b.cstate_pstate.cstate_exit_ns)
		wm_pending = twue;

	/* cwock state C */
	if (safe_to_wowew || watewmawks->c.cstate_pstate.cstate_entew_pwus_exit_ns
			> hubbub1->watewmawks.c.cstate_pstate.cstate_entew_pwus_exit_ns) {
		hubbub1->watewmawks.c.cstate_pstate.cstate_entew_pwus_exit_ns =
				watewmawks->c.cstate_pstate.cstate_entew_pwus_exit_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->c.cstate_pstate.cstate_entew_pwus_exit_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_C, 0,
				DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_C, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_ENTEW_EXIT_WATEWMAWK_C cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->c.cstate_pstate.cstate_entew_pwus_exit_ns, pwog_wm_vawue);
	} ewse if (watewmawks->c.cstate_pstate.cstate_entew_pwus_exit_ns
			< hubbub1->watewmawks.c.cstate_pstate.cstate_entew_pwus_exit_ns)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->c.cstate_pstate.cstate_exit_ns
			> hubbub1->watewmawks.c.cstate_pstate.cstate_exit_ns) {
		hubbub1->watewmawks.c.cstate_pstate.cstate_exit_ns =
				watewmawks->c.cstate_pstate.cstate_exit_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->c.cstate_pstate.cstate_exit_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_C, 0,
				DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_C, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_EXIT_WATEWMAWK_C cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->c.cstate_pstate.cstate_exit_ns, pwog_wm_vawue);
	} ewse if (watewmawks->c.cstate_pstate.cstate_exit_ns
			< hubbub1->watewmawks.c.cstate_pstate.cstate_exit_ns)
		wm_pending = twue;

	/* cwock state D */
	if (safe_to_wowew || watewmawks->d.cstate_pstate.cstate_entew_pwus_exit_ns
			> hubbub1->watewmawks.d.cstate_pstate.cstate_entew_pwus_exit_ns) {
		hubbub1->watewmawks.d.cstate_pstate.cstate_entew_pwus_exit_ns =
				watewmawks->d.cstate_pstate.cstate_entew_pwus_exit_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->d.cstate_pstate.cstate_entew_pwus_exit_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_D, 0,
				DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_D, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_ENTEW_EXIT_WATEWMAWK_D cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->d.cstate_pstate.cstate_entew_pwus_exit_ns, pwog_wm_vawue);
	} ewse if (watewmawks->d.cstate_pstate.cstate_entew_pwus_exit_ns
			< hubbub1->watewmawks.d.cstate_pstate.cstate_entew_pwus_exit_ns)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->d.cstate_pstate.cstate_exit_ns
			> hubbub1->watewmawks.d.cstate_pstate.cstate_exit_ns) {
		hubbub1->watewmawks.d.cstate_pstate.cstate_exit_ns =
				watewmawks->d.cstate_pstate.cstate_exit_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->d.cstate_pstate.cstate_exit_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_D, 0,
				DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_D, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_EXIT_WATEWMAWK_D cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->d.cstate_pstate.cstate_exit_ns, pwog_wm_vawue);
	} ewse if (watewmawks->d.cstate_pstate.cstate_exit_ns
			< hubbub1->watewmawks.d.cstate_pstate.cstate_exit_ns)
		wm_pending = twue;

	wetuwn wm_pending;
}

boow hubbub1_pwogwam_pstate_watewmawks(
		stwuct hubbub *hubbub,
		stwuct dcn_watewmawk_set *watewmawks,
		unsigned int wefcwk_mhz,
		boow safe_to_wowew)
{
	stwuct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);
	uint32_t pwog_wm_vawue;
	boow wm_pending = fawse;

	/* cwock state A */
	if (safe_to_wowew || watewmawks->a.cstate_pstate.pstate_change_ns
			> hubbub1->watewmawks.a.cstate_pstate.pstate_change_ns) {
		hubbub1->watewmawks.a.cstate_pstate.pstate_change_ns =
				watewmawks->a.cstate_pstate.pstate_change_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->a.cstate_pstate.pstate_change_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_A, 0,
				DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_A, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("DWAM_CWK_CHANGE_WATEWMAWK_A cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n\n",
			watewmawks->a.cstate_pstate.pstate_change_ns, pwog_wm_vawue);
	} ewse if (watewmawks->a.cstate_pstate.pstate_change_ns
			< hubbub1->watewmawks.a.cstate_pstate.pstate_change_ns)
		wm_pending = twue;

	/* cwock state B */
	if (safe_to_wowew || watewmawks->b.cstate_pstate.pstate_change_ns
			> hubbub1->watewmawks.b.cstate_pstate.pstate_change_ns) {
		hubbub1->watewmawks.b.cstate_pstate.pstate_change_ns =
				watewmawks->b.cstate_pstate.pstate_change_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->b.cstate_pstate.pstate_change_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_B, 0,
				DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_B, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("DWAM_CWK_CHANGE_WATEWMAWK_B cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n\n",
			watewmawks->b.cstate_pstate.pstate_change_ns, pwog_wm_vawue);
	} ewse if (watewmawks->b.cstate_pstate.pstate_change_ns
			< hubbub1->watewmawks.b.cstate_pstate.pstate_change_ns)
		wm_pending = twue;

	/* cwock state C */
	if (safe_to_wowew || watewmawks->c.cstate_pstate.pstate_change_ns
			> hubbub1->watewmawks.c.cstate_pstate.pstate_change_ns) {
		hubbub1->watewmawks.c.cstate_pstate.pstate_change_ns =
				watewmawks->c.cstate_pstate.pstate_change_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->c.cstate_pstate.pstate_change_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_C, 0,
				DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_C, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("DWAM_CWK_CHANGE_WATEWMAWK_C cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n\n",
			watewmawks->c.cstate_pstate.pstate_change_ns, pwog_wm_vawue);
	} ewse if (watewmawks->c.cstate_pstate.pstate_change_ns
			< hubbub1->watewmawks.c.cstate_pstate.pstate_change_ns)
		wm_pending = twue;

	/* cwock state D */
	if (safe_to_wowew || watewmawks->d.cstate_pstate.pstate_change_ns
			> hubbub1->watewmawks.d.cstate_pstate.pstate_change_ns) {
		hubbub1->watewmawks.d.cstate_pstate.pstate_change_ns =
				watewmawks->d.cstate_pstate.pstate_change_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->d.cstate_pstate.pstate_change_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_D, 0,
				DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_D, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("DWAM_CWK_CHANGE_WATEWMAWK_D cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n\n",
			watewmawks->d.cstate_pstate.pstate_change_ns, pwog_wm_vawue);
	} ewse if (watewmawks->d.cstate_pstate.pstate_change_ns
			< hubbub1->watewmawks.d.cstate_pstate.pstate_change_ns)
		wm_pending = twue;

	wetuwn wm_pending;
}

boow hubbub1_pwogwam_watewmawks(
		stwuct hubbub *hubbub,
		stwuct dcn_watewmawk_set *watewmawks,
		unsigned int wefcwk_mhz,
		boow safe_to_wowew)
{
	stwuct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);
	boow wm_pending = fawse;
	/*
	 * Need to cwamp to max of the wegistew vawues (i.e. no wwap)
	 * fow dcn1, aww wm wegistews awe 21-bit wide
	 */
	if (hubbub1_pwogwam_uwgent_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	if (hubbub1_pwogwam_stuttew_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	if (hubbub1_pwogwam_pstate_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	WEG_UPDATE(DCHUBBUB_AWB_SAT_WEVEW,
			DCHUBBUB_AWB_SAT_WEVEW, 60 * wefcwk_mhz);
	WEG_UPDATE(DCHUBBUB_AWB_DF_WEQ_OUTSTAND,
			DCHUBBUB_AWB_MIN_WEQ_OUTSTAND, 68);

	hubbub1_awwow_sewf_wefwesh_contwow(hubbub, !hubbub->ctx->dc->debug.disabwe_stuttew);

#if 0
	WEG_UPDATE_2(DCHUBBUB_AWB_WATEWMAWK_CHANGE_CNTW,
			DCHUBBUB_AWB_WATEWMAWK_CHANGE_DONE_INTEWWUPT_DISABWE, 1,
			DCHUBBUB_AWB_WATEWMAWK_CHANGE_WEQUEST, 1);
#endif
	wetuwn wm_pending;
}

void hubbub1_update_dchub(
	stwuct hubbub *hubbub,
	stwuct dchub_init_data *dh_data)
{
	stwuct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);

	if (WEG(DCHUBBUB_SDPIF_FB_TOP) == 0) {
		ASSEWT(fawse);
		/*shouwd not come hewe*/
		wetuwn;
	}
	/* TODO: powt code fwom daw2 */
	switch (dh_data->fb_mode) {
	case FWAME_BUFFEW_MODE_ZFB_ONWY:
		/*Fow ZFB case need to put DCHUB FB BASE and TOP upside down to indicate ZFB mode*/
		WEG_UPDATE(DCHUBBUB_SDPIF_FB_TOP,
				SDPIF_FB_TOP, 0);

		WEG_UPDATE(DCHUBBUB_SDPIF_FB_BASE,
				SDPIF_FB_BASE, 0x0FFFF);

		WEG_UPDATE(DCHUBBUB_SDPIF_AGP_BASE,
				SDPIF_AGP_BASE, dh_data->zfb_phys_addw_base >> 22);

		WEG_UPDATE(DCHUBBUB_SDPIF_AGP_BOT,
				SDPIF_AGP_BOT, dh_data->zfb_mc_base_addw >> 22);

		WEG_UPDATE(DCHUBBUB_SDPIF_AGP_TOP,
				SDPIF_AGP_TOP, (dh_data->zfb_mc_base_addw +
						dh_data->zfb_size_in_byte - 1) >> 22);
		bweak;
	case FWAME_BUFFEW_MODE_MIXED_ZFB_AND_WOCAW:
		/*Shouwd not touch FB WOCATION (done by VBIOS on AsicInit tabwe)*/

		WEG_UPDATE(DCHUBBUB_SDPIF_AGP_BASE,
				SDPIF_AGP_BASE, dh_data->zfb_phys_addw_base >> 22);

		WEG_UPDATE(DCHUBBUB_SDPIF_AGP_BOT,
				SDPIF_AGP_BOT, dh_data->zfb_mc_base_addw >> 22);

		WEG_UPDATE(DCHUBBUB_SDPIF_AGP_TOP,
				SDPIF_AGP_TOP, (dh_data->zfb_mc_base_addw +
						dh_data->zfb_size_in_byte - 1) >> 22);
		bweak;
	case FWAME_BUFFEW_MODE_WOCAW_ONWY:
		/*Shouwd not touch FB WOCATION (done by VBIOS on AsicInit tabwe)*/
		WEG_UPDATE(DCHUBBUB_SDPIF_AGP_BASE,
				SDPIF_AGP_BASE, 0);

		WEG_UPDATE(DCHUBBUB_SDPIF_AGP_BOT,
				SDPIF_AGP_BOT, 0X03FFFF);

		WEG_UPDATE(DCHUBBUB_SDPIF_AGP_TOP,
				SDPIF_AGP_TOP, 0);
		bweak;
	defauwt:
		bweak;
	}

	dh_data->dchub_initiawzied = twue;
	dh_data->dchub_info_vawid = fawse;
}

void hubbub1_toggwe_watewmawk_change_weq(stwuct hubbub *hubbub)
{
	stwuct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);

	uint32_t watewmawk_change_weq;

	WEG_GET(DCHUBBUB_AWB_WATEWMAWK_CHANGE_CNTW,
			DCHUBBUB_AWB_WATEWMAWK_CHANGE_WEQUEST, &watewmawk_change_weq);

	if (watewmawk_change_weq)
		watewmawk_change_weq = 0;
	ewse
		watewmawk_change_weq = 1;

	WEG_UPDATE(DCHUBBUB_AWB_WATEWMAWK_CHANGE_CNTW,
			DCHUBBUB_AWB_WATEWMAWK_CHANGE_WEQUEST, watewmawk_change_weq);
}

void hubbub1_soft_weset(stwuct hubbub *hubbub, boow weset)
{
	stwuct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);

	uint32_t weset_en = weset ? 1 : 0;

	WEG_UPDATE(DCHUBBUB_SOFT_WESET,
			DCHUBBUB_GWOBAW_SOFT_WESET, weset_en);
}

static boow hubbub1_dcc_suppowt_swizzwe(
		enum swizzwe_mode_vawues swizzwe,
		unsigned int bytes_pew_ewement,
		enum segment_owdew *segment_owdew_howz,
		enum segment_owdew *segment_owdew_vewt)
{
	boow standawd_swizzwe = fawse;
	boow dispway_swizzwe = fawse;

	switch (swizzwe) {
	case DC_SW_4KB_S:
	case DC_SW_64KB_S:
	case DC_SW_VAW_S:
	case DC_SW_4KB_S_X:
	case DC_SW_64KB_S_X:
	case DC_SW_VAW_S_X:
		standawd_swizzwe = twue;
		bweak;
	case DC_SW_4KB_D:
	case DC_SW_64KB_D:
	case DC_SW_VAW_D:
	case DC_SW_4KB_D_X:
	case DC_SW_64KB_D_X:
	case DC_SW_VAW_D_X:
		dispway_swizzwe = twue;
		bweak;
	defauwt:
		bweak;
	}

	if (bytes_pew_ewement == 1 && standawd_swizzwe) {
		*segment_owdew_howz = segment_owdew__contiguous;
		*segment_owdew_vewt = segment_owdew__na;
		wetuwn twue;
	}
	if (bytes_pew_ewement == 2 && standawd_swizzwe) {
		*segment_owdew_howz = segment_owdew__non_contiguous;
		*segment_owdew_vewt = segment_owdew__contiguous;
		wetuwn twue;
	}
	if (bytes_pew_ewement == 4 && standawd_swizzwe) {
		*segment_owdew_howz = segment_owdew__non_contiguous;
		*segment_owdew_vewt = segment_owdew__contiguous;
		wetuwn twue;
	}
	if (bytes_pew_ewement == 8 && standawd_swizzwe) {
		*segment_owdew_howz = segment_owdew__na;
		*segment_owdew_vewt = segment_owdew__contiguous;
		wetuwn twue;
	}
	if (bytes_pew_ewement == 8 && dispway_swizzwe) {
		*segment_owdew_howz = segment_owdew__contiguous;
		*segment_owdew_vewt = segment_owdew__non_contiguous;
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow hubbub1_dcc_suppowt_pixew_fowmat(
		enum suwface_pixew_fowmat fowmat,
		unsigned int *bytes_pew_ewement)
{
	/* DMW: get_bytes_pew_ewement */
	switch (fowmat) {
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB1555:
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGB565:
		*bytes_pew_ewement = 2;
		wetuwn twue;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB8888:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW8888:
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB2101010:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW2101010:
		*bytes_pew_ewement = 4;
		wetuwn twue;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616:
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616F:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616F:
		*bytes_pew_ewement = 8;
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static void hubbub1_get_bwk256_size(unsigned int *bwk256_width, unsigned int *bwk256_height,
		unsigned int bytes_pew_ewement)
{
	/* copied fwom DMW.  might want to wefactow DMW to wevewage fwom DMW */
	/* DMW : get_bwk256_size */
	if (bytes_pew_ewement == 1) {
		*bwk256_width = 16;
		*bwk256_height = 16;
	} ewse if (bytes_pew_ewement == 2) {
		*bwk256_width = 16;
		*bwk256_height = 8;
	} ewse if (bytes_pew_ewement == 4) {
		*bwk256_width = 8;
		*bwk256_height = 8;
	} ewse if (bytes_pew_ewement == 8) {
		*bwk256_width = 8;
		*bwk256_height = 4;
	}
}

static void hubbub1_det_wequest_size(
		unsigned int height,
		unsigned int width,
		unsigned int bpe,
		boow *weq128_howz_wc,
		boow *weq128_vewt_wc)
{
	unsigned int detiwe_buf_size = 164 * 1024;  /* 164KB fow DCN1.0 */

	unsigned int bwk256_height = 0;
	unsigned int bwk256_width = 0;
	unsigned int swath_bytes_howz_wc, swath_bytes_vewt_wc;

	hubbub1_get_bwk256_size(&bwk256_width, &bwk256_height, bpe);

	swath_bytes_howz_wc = width * bwk256_height * bpe;
	swath_bytes_vewt_wc = height * bwk256_width * bpe;

	*weq128_howz_wc = (2 * swath_bytes_howz_wc <= detiwe_buf_size) ?
			fawse : /* fuww 256B wequest */
			twue; /* hawf 128b wequest */

	*weq128_vewt_wc = (2 * swath_bytes_vewt_wc <= detiwe_buf_size) ?
			fawse : /* fuww 256B wequest */
			twue; /* hawf 128b wequest */
}

static boow hubbub1_get_dcc_compwession_cap(stwuct hubbub *hubbub,
		const stwuct dc_dcc_suwface_pawam *input,
		stwuct dc_suwface_dcc_cap *output)
{
	stwuct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);
	stwuct dc *dc = hubbub1->base.ctx->dc;

	/* impwement section 1.6.2.1 of DCN1_Pwogwamming_Guide.docx */
	enum dcc_contwow dcc_contwow;
	unsigned int bpe;
	enum segment_owdew segment_owdew_howz, segment_owdew_vewt;
	boow weq128_howz_wc, weq128_vewt_wc;

	memset(output, 0, sizeof(*output));

	if (dc->debug.disabwe_dcc == DCC_DISABWE)
		wetuwn fawse;

	if (!hubbub1->base.funcs->dcc_suppowt_pixew_fowmat(input->fowmat, &bpe))
		wetuwn fawse;

	if (!hubbub1->base.funcs->dcc_suppowt_swizzwe(input->swizzwe_mode, bpe,
			&segment_owdew_howz, &segment_owdew_vewt))
		wetuwn fawse;

	hubbub1_det_wequest_size(input->suwface_size.height,  input->suwface_size.width,
			bpe, &weq128_howz_wc, &weq128_vewt_wc);

	if (!weq128_howz_wc && !weq128_vewt_wc) {
		dcc_contwow = dcc_contwow__256_256_xxx;
	} ewse if (input->scan == SCAN_DIWECTION_HOWIZONTAW) {
		if (!weq128_howz_wc)
			dcc_contwow = dcc_contwow__256_256_xxx;
		ewse if (segment_owdew_howz == segment_owdew__contiguous)
			dcc_contwow = dcc_contwow__128_128_xxx;
		ewse
			dcc_contwow = dcc_contwow__256_64_64;
	} ewse if (input->scan == SCAN_DIWECTION_VEWTICAW) {
		if (!weq128_vewt_wc)
			dcc_contwow = dcc_contwow__256_256_xxx;
		ewse if (segment_owdew_vewt == segment_owdew__contiguous)
			dcc_contwow = dcc_contwow__128_128_xxx;
		ewse
			dcc_contwow = dcc_contwow__256_64_64;
	} ewse {
		if ((weq128_howz_wc &&
			segment_owdew_howz == segment_owdew__non_contiguous) ||
			(weq128_vewt_wc &&
			segment_owdew_vewt == segment_owdew__non_contiguous))
			/* access_diw not known, must use most constwaining */
			dcc_contwow = dcc_contwow__256_64_64;
		ewse
			/* weg128 is twue fow eithew howz and vewt
			 * but segment_owdew is contiguous
			 */
			dcc_contwow = dcc_contwow__128_128_xxx;
	}

	if (dc->debug.disabwe_dcc == DCC_HAWF_WEQ_DISAWBE &&
		dcc_contwow != dcc_contwow__256_256_xxx)
		wetuwn fawse;

	switch (dcc_contwow) {
	case dcc_contwow__256_256_xxx:
		output->gwph.wgb.max_uncompwessed_bwk_size = 256;
		output->gwph.wgb.max_compwessed_bwk_size = 256;
		output->gwph.wgb.independent_64b_bwks = fawse;
		bweak;
	case dcc_contwow__128_128_xxx:
		output->gwph.wgb.max_uncompwessed_bwk_size = 128;
		output->gwph.wgb.max_compwessed_bwk_size = 128;
		output->gwph.wgb.independent_64b_bwks = fawse;
		bweak;
	case dcc_contwow__256_64_64:
		output->gwph.wgb.max_uncompwessed_bwk_size = 256;
		output->gwph.wgb.max_compwessed_bwk_size = 64;
		output->gwph.wgb.independent_64b_bwks = twue;
		bweak;
	defauwt:
		ASSEWT(fawse);
		bweak;
	}

	output->capabwe = twue;
	output->const_cowow_suppowt = fawse;

	wetuwn twue;
}

static const stwuct hubbub_funcs hubbub1_funcs = {
	.update_dchub = hubbub1_update_dchub,
	.dcc_suppowt_swizzwe = hubbub1_dcc_suppowt_swizzwe,
	.dcc_suppowt_pixew_fowmat = hubbub1_dcc_suppowt_pixew_fowmat,
	.get_dcc_compwession_cap = hubbub1_get_dcc_compwession_cap,
	.wm_wead_state = hubbub1_wm_wead_state,
	.pwogwam_watewmawks = hubbub1_pwogwam_watewmawks,
	.is_awwow_sewf_wefwesh_enabwed = hubbub1_is_awwow_sewf_wefwesh_enabwed,
	.awwow_sewf_wefwesh_contwow = hubbub1_awwow_sewf_wefwesh_contwow,
	.vewify_awwow_pstate_change_high = hubbub1_vewify_awwow_pstate_change_high,
};

void hubbub1_constwuct(stwuct hubbub *hubbub,
	stwuct dc_context *ctx,
	const stwuct dcn_hubbub_wegistews *hubbub_wegs,
	const stwuct dcn_hubbub_shift *hubbub_shift,
	const stwuct dcn_hubbub_mask *hubbub_mask)
{
	stwuct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);

	hubbub1->base.ctx = ctx;

	hubbub1->base.funcs = &hubbub1_funcs;

	hubbub1->wegs = hubbub_wegs;
	hubbub1->shifts = hubbub_shift;
	hubbub1->masks = hubbub_mask;

	hubbub1->debug_test_index_pstate = 0x7;
	if (ctx->dce_vewsion == DCN_VEWSION_1_01)
		hubbub1->debug_test_index_pstate = 0xB;
}

