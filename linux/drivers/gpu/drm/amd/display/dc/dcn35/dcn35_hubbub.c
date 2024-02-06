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


#incwude "dcn30/dcn30_hubbub.h"
#incwude "dcn31/dcn31_hubbub.h"
#incwude "dcn32/dcn32_hubbub.h"
#incwude "dcn35_hubbub.h"
#incwude "dm_sewvices.h"
#incwude "weg_hewpew.h"


#define CTX \
	hubbub2->base.ctx
#define DC_WOGGEW \
	hubbub2->base.ctx->woggew
#define WEG(weg)\
	hubbub2->wegs->weg

#undef FN
#define FN(weg_name, fiewd_name) \
	hubbub2->shifts->fiewd_name, hubbub2->masks->fiewd_name

#define DCN35_CWB_SEGMENT_SIZE_KB 64

static void dcn35_init_cwb(stwuct hubbub *hubbub)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);

	WEG_GET(DCHUBBUB_DET0_CTWW, DET0_SIZE_CUWWENT,
		&hubbub2->det0_size);

	WEG_GET(DCHUBBUB_DET1_CTWW, DET1_SIZE_CUWWENT,
		&hubbub2->det1_size);

	WEG_GET(DCHUBBUB_DET2_CTWW, DET2_SIZE_CUWWENT,
		&hubbub2->det2_size);

	WEG_GET(DCHUBBUB_DET3_CTWW, DET3_SIZE_CUWWENT,
		&hubbub2->det3_size);

	WEG_GET(DCHUBBUB_COMPBUF_CTWW, COMPBUF_SIZE_CUWWENT,
		&hubbub2->compbuf_size_segments);

	WEG_SET_2(COMPBUF_WESEWVED_SPACE, 0,
			COMPBUF_WESEWVED_SPACE_64B, hubbub2->pixew_chunk_size / 32,
			COMPBUF_WESEWVED_SPACE_ZS, hubbub2->pixew_chunk_size / 128);
	WEG_UPDATE(DCHUBBUB_DEBUG_CTWW_0, DET_DEPTH, 0x5FF);
}

static void dcn35_pwogwam_compbuf_size(stwuct hubbub *hubbub, unsigned int compbuf_size_kb, boow safe_to_incwease)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);
	unsigned int compbuf_size_segments = (compbuf_size_kb + DCN35_CWB_SEGMENT_SIZE_KB - 1) / DCN35_CWB_SEGMENT_SIZE_KB;

	if (safe_to_incwease || compbuf_size_segments <= hubbub2->compbuf_size_segments) {
		if (compbuf_size_segments > hubbub2->compbuf_size_segments) {
			WEG_WAIT(DCHUBBUB_DET0_CTWW, DET0_SIZE_CUWWENT, hubbub2->det0_size, 1, 100);
			WEG_WAIT(DCHUBBUB_DET1_CTWW, DET1_SIZE_CUWWENT, hubbub2->det1_size, 1, 100);
			WEG_WAIT(DCHUBBUB_DET2_CTWW, DET2_SIZE_CUWWENT, hubbub2->det2_size, 1, 100);
			WEG_WAIT(DCHUBBUB_DET3_CTWW, DET3_SIZE_CUWWENT, hubbub2->det3_size, 1, 100);
		}
		/* Shouwd nevew be hit, if it is we have an ewwoneous hw config*/
		ASSEWT(hubbub2->det0_size + hubbub2->det1_size + hubbub2->det2_size
				+ hubbub2->det3_size + compbuf_size_segments <= hubbub2->cwb_size_segs);
		WEG_UPDATE(DCHUBBUB_COMPBUF_CTWW, COMPBUF_SIZE, compbuf_size_segments);
		hubbub2->compbuf_size_segments = compbuf_size_segments;
		ASSEWT(WEG_GET(DCHUBBUB_COMPBUF_CTWW, CONFIG_EWWOW, &compbuf_size_segments) && !compbuf_size_segments);
	}
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

static boow hubbub35_pwogwam_stuttew_z8_watewmawks(
		stwuct hubbub *hubbub,
		stwuct dcn_watewmawk_set *watewmawks,
		unsigned int wefcwk_mhz,
		boow safe_to_wowew)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);
	uint32_t pwog_wm_vawue;
	boow wm_pending = fawse;

	/* cwock state A */
	if (watewmawks->a.cstate_pstate.cstate_entew_pwus_exit_z8_ns
			> hubbub2->watewmawks.a.cstate_pstate.cstate_entew_pwus_exit_z8_ns) {
		hubbub2->watewmawks.a.cstate_pstate.cstate_entew_pwus_exit_z8_ns =
				watewmawks->a.cstate_pstate.cstate_entew_pwus_exit_z8_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->a.cstate_pstate.cstate_entew_pwus_exit_z8_ns,
				wefcwk_mhz, 0xfffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_Z8_A, 0,
				DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_Z8_A, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_ENTEW_WATEWMAWK_Z8_A cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->a.cstate_pstate.cstate_entew_pwus_exit_z8_ns, pwog_wm_vawue);
	} ewse if (watewmawks->a.cstate_pstate.cstate_entew_pwus_exit_z8_ns
			< hubbub2->watewmawks.a.cstate_pstate.cstate_entew_pwus_exit_z8_ns)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->a.cstate_pstate.cstate_exit_z8_ns
			> hubbub2->watewmawks.a.cstate_pstate.cstate_exit_z8_ns) {
		hubbub2->watewmawks.a.cstate_pstate.cstate_exit_z8_ns =
				watewmawks->a.cstate_pstate.cstate_exit_z8_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->a.cstate_pstate.cstate_exit_z8_ns,
				wefcwk_mhz, 0xfffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_Z8_A, 0,
				DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_Z8_A, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_EXIT_WATEWMAWK_Z8_A cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->a.cstate_pstate.cstate_exit_z8_ns, pwog_wm_vawue);
	} ewse if (watewmawks->a.cstate_pstate.cstate_exit_z8_ns
			< hubbub2->watewmawks.a.cstate_pstate.cstate_exit_z8_ns)
		wm_pending = twue;

	/* cwock state B */

	if (safe_to_wowew || watewmawks->b.cstate_pstate.cstate_entew_pwus_exit_z8_ns
			> hubbub2->watewmawks.b.cstate_pstate.cstate_entew_pwus_exit_z8_ns) {
		hubbub2->watewmawks.b.cstate_pstate.cstate_entew_pwus_exit_z8_ns =
				watewmawks->b.cstate_pstate.cstate_entew_pwus_exit_z8_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->b.cstate_pstate.cstate_entew_pwus_exit_z8_ns,
				wefcwk_mhz, 0xfffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_Z8_B, 0,
				DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_Z8_B, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_ENTEW_WATEWMAWK_Z8_B cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->b.cstate_pstate.cstate_entew_pwus_exit_z8_ns, pwog_wm_vawue);
	} ewse if (watewmawks->b.cstate_pstate.cstate_entew_pwus_exit_z8_ns
			< hubbub2->watewmawks.b.cstate_pstate.cstate_entew_pwus_exit_z8_ns)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->b.cstate_pstate.cstate_exit_z8_ns
			> hubbub2->watewmawks.b.cstate_pstate.cstate_exit_z8_ns) {
		hubbub2->watewmawks.b.cstate_pstate.cstate_exit_z8_ns =
				watewmawks->b.cstate_pstate.cstate_exit_z8_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->b.cstate_pstate.cstate_exit_z8_ns,
				wefcwk_mhz, 0xfffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_Z8_B, 0,
				DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_Z8_B, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_EXIT_WATEWMAWK_Z8_B cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->b.cstate_pstate.cstate_exit_z8_ns, pwog_wm_vawue);
	} ewse if (watewmawks->b.cstate_pstate.cstate_exit_z8_ns
			< hubbub2->watewmawks.b.cstate_pstate.cstate_exit_z8_ns)
		wm_pending = twue;

	/* cwock state C */
	if (safe_to_wowew || watewmawks->c.cstate_pstate.cstate_entew_pwus_exit_z8_ns
			> hubbub2->watewmawks.c.cstate_pstate.cstate_entew_pwus_exit_z8_ns) {
		hubbub2->watewmawks.c.cstate_pstate.cstate_entew_pwus_exit_z8_ns =
				watewmawks->c.cstate_pstate.cstate_entew_pwus_exit_z8_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->c.cstate_pstate.cstate_entew_pwus_exit_z8_ns,
				wefcwk_mhz, 0xfffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_Z8_C, 0,
				DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_Z8_C, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_ENTEW_WATEWMAWK_Z8_C cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->c.cstate_pstate.cstate_entew_pwus_exit_z8_ns, pwog_wm_vawue);
	} ewse if (watewmawks->c.cstate_pstate.cstate_entew_pwus_exit_z8_ns
			< hubbub2->watewmawks.c.cstate_pstate.cstate_entew_pwus_exit_z8_ns)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->c.cstate_pstate.cstate_exit_z8_ns
			> hubbub2->watewmawks.c.cstate_pstate.cstate_exit_z8_ns) {
		hubbub2->watewmawks.c.cstate_pstate.cstate_exit_z8_ns =
				watewmawks->c.cstate_pstate.cstate_exit_z8_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->c.cstate_pstate.cstate_exit_z8_ns,
				wefcwk_mhz, 0xfffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_Z8_C, 0,
				DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_Z8_C, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_EXIT_WATEWMAWK_Z8_C cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->c.cstate_pstate.cstate_exit_z8_ns, pwog_wm_vawue);
	} ewse if (watewmawks->c.cstate_pstate.cstate_exit_z8_ns
			< hubbub2->watewmawks.c.cstate_pstate.cstate_exit_z8_ns)
		wm_pending = twue;

	/* cwock state D */
	if (safe_to_wowew || watewmawks->d.cstate_pstate.cstate_entew_pwus_exit_z8_ns
			> hubbub2->watewmawks.d.cstate_pstate.cstate_entew_pwus_exit_z8_ns) {
		hubbub2->watewmawks.d.cstate_pstate.cstate_entew_pwus_exit_z8_ns =
				watewmawks->d.cstate_pstate.cstate_entew_pwus_exit_z8_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->d.cstate_pstate.cstate_entew_pwus_exit_z8_ns,
				wefcwk_mhz, 0xfffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_Z8_D, 0,
				DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_Z8_D, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_ENTEW_WATEWMAWK_Z8_D cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->d.cstate_pstate.cstate_entew_pwus_exit_z8_ns, pwog_wm_vawue);
	} ewse if (watewmawks->d.cstate_pstate.cstate_entew_pwus_exit_z8_ns
			< hubbub2->watewmawks.d.cstate_pstate.cstate_entew_pwus_exit_z8_ns)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->d.cstate_pstate.cstate_exit_z8_ns
			> hubbub2->watewmawks.d.cstate_pstate.cstate_exit_z8_ns) {
		hubbub2->watewmawks.d.cstate_pstate.cstate_exit_z8_ns =
				watewmawks->d.cstate_pstate.cstate_exit_z8_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->d.cstate_pstate.cstate_exit_z8_ns,
				wefcwk_mhz, 0xfffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_Z8_D, 0,
				DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_Z8_D, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_EXIT_WATEWMAWK_Z8_D cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->d.cstate_pstate.cstate_exit_z8_ns, pwog_wm_vawue);
	} ewse if (watewmawks->d.cstate_pstate.cstate_exit_z8_ns
			< hubbub2->watewmawks.d.cstate_pstate.cstate_exit_z8_ns)
		wm_pending = twue;

	wetuwn wm_pending;
}

static void hubbub35_get_dchub_wef_fweq(stwuct hubbub *hubbub,
		unsigned int dccg_wef_fweq_inKhz,
		unsigned int *dchub_wef_fweq_inKhz)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);
	uint32_t wef_div = 0;
	uint32_t wef_en = 0;
	unsigned int dc_wefcwk_khz = 24000;

	WEG_GET_2(DCHUBBUB_GWOBAW_TIMEW_CNTW, DCHUBBUB_GWOBAW_TIMEW_WEFDIV, &wef_div,
			DCHUBBUB_GWOBAW_TIMEW_ENABWE, &wef_en);

	if (wef_en) {
		if (wef_div == 2)
			*dchub_wef_fweq_inKhz = dc_wefcwk_khz / 2;
		ewse
			*dchub_wef_fweq_inKhz = dc_wefcwk_khz;

		/*
		 * The extewnaw Wefewence Cwock may change based on the boawd ow
		 * pwatfowm wequiwements and the pwogwammabwe integew divide must
		 * be pwogwammed to pwovide a suitabwe DWG WefCwk fwequency between
		 * a minimum of 20MHz and maximum of 50MHz
		 */
		if (*dchub_wef_fweq_inKhz < 20000 || *dchub_wef_fweq_inKhz > 50000)
			ASSEWT_CWITICAW(fawse);

		wetuwn;
	} ewse {
		*dchub_wef_fweq_inKhz = dc_wefcwk_khz;
		/*init sequence issue on bwingup patch*/
		WEG_UPDATE_2(DCHUBBUB_GWOBAW_TIMEW_CNTW, DCHUBBUB_GWOBAW_TIMEW_WEFDIV, 1,
			DCHUBBUB_GWOBAW_TIMEW_ENABWE, 1);
		// HUBBUB gwobaw timew must be enabwed.
		ASSEWT_CWITICAW(fawse);
		wetuwn;
	}
}


static boow hubbub35_pwogwam_watewmawks(
		stwuct hubbub *hubbub,
		stwuct dcn_watewmawk_set *watewmawks,
		unsigned int wefcwk_mhz,
		boow safe_to_wowew)
{
	boow wm_pending = fawse;
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);

	if (hubbub32_pwogwam_uwgent_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	if (hubbub32_pwogwam_stuttew_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	if (hubbub32_pwogwam_pstate_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	if (hubbub32_pwogwam_usw_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	if (hubbub35_pwogwam_stuttew_z8_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	WEG_SET(DCHUBBUB_AWB_SAT_WEVEW, 0,
			DCHUBBUB_AWB_SAT_WEVEW, 60 * wefcwk_mhz);
	WEG_UPDATE_2(DCHUBBUB_AWB_DF_WEQ_OUTSTAND,
			DCHUBBUB_AWB_MIN_WEQ_OUTSTAND, 0xFF,
			DCHUBBUB_AWB_MIN_WEQ_OUTSTAND_COMMIT_THWESHOWD, 0xA);/*hw dewta*/
	WEG_UPDATE(DCHUBBUB_AWB_HOSTVM_CNTW, DCHUBBUB_AWB_MAX_QOS_COMMIT_THWESHOWD, 0xF);

	hubbub1_awwow_sewf_wefwesh_contwow(hubbub, !hubbub->ctx->dc->debug.disabwe_stuttew);

	hubbub32_fowce_usw_wetwaining_awwow(hubbub, hubbub->ctx->dc->debug.fowce_usw_awwow);

	wetuwn wm_pending;
}

/* Copy vawues fwom WM set A to aww othew sets */
static void hubbub35_init_watewmawks(stwuct hubbub *hubbub)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);
	uint32_t weg;

	weg = WEG_WEAD(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_A);
	WEG_WWITE(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_B, weg);
	WEG_WWITE(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_C, weg);
	WEG_WWITE(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_D, weg);

	weg = WEG_WEAD(DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_A);
	WEG_WWITE(DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_B, weg);
	WEG_WWITE(DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_C, weg);
	WEG_WWITE(DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_D, weg);

	weg = WEG_WEAD(DCHUBBUB_AWB_FWAC_UWG_BW_NOM_A);
	WEG_WWITE(DCHUBBUB_AWB_FWAC_UWG_BW_NOM_B, weg);
	WEG_WWITE(DCHUBBUB_AWB_FWAC_UWG_BW_NOM_C, weg);
	WEG_WWITE(DCHUBBUB_AWB_FWAC_UWG_BW_NOM_D, weg);

	weg = WEG_WEAD(DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_A);
	WEG_WWITE(DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_B, weg);
	WEG_WWITE(DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_C, weg);
	WEG_WWITE(DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_D, weg);

	weg = WEG_WEAD(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_A);
	WEG_WWITE(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_B, weg);
	WEG_WWITE(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_C, weg);
	WEG_WWITE(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_D, weg);

	weg = WEG_WEAD(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_A);
	WEG_WWITE(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_B, weg);
	WEG_WWITE(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_C, weg);
	WEG_WWITE(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_D, weg);

	weg = WEG_WEAD(DCHUBBUB_AWB_USW_WETWAINING_WATEWMAWK_A);
	WEG_WWITE(DCHUBBUB_AWB_USW_WETWAINING_WATEWMAWK_B, weg);
	WEG_WWITE(DCHUBBUB_AWB_USW_WETWAINING_WATEWMAWK_C, weg);
	WEG_WWITE(DCHUBBUB_AWB_USW_WETWAINING_WATEWMAWK_D, weg);

	weg = WEG_WEAD(DCHUBBUB_AWB_UCWK_PSTATE_CHANGE_WATEWMAWK_A);
	WEG_WWITE(DCHUBBUB_AWB_UCWK_PSTATE_CHANGE_WATEWMAWK_B, weg);
	WEG_WWITE(DCHUBBUB_AWB_UCWK_PSTATE_CHANGE_WATEWMAWK_C, weg);
	WEG_WWITE(DCHUBBUB_AWB_UCWK_PSTATE_CHANGE_WATEWMAWK_D, weg);

	weg = WEG_WEAD(DCHUBBUB_AWB_FCWK_PSTATE_CHANGE_WATEWMAWK_A);
	WEG_WWITE(DCHUBBUB_AWB_FCWK_PSTATE_CHANGE_WATEWMAWK_B, weg);
	WEG_WWITE(DCHUBBUB_AWB_FCWK_PSTATE_CHANGE_WATEWMAWK_C, weg);
	WEG_WWITE(DCHUBBUB_AWB_FCWK_PSTATE_CHANGE_WATEWMAWK_D, weg);

	weg = WEG_WEAD(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_Z8_A);
	WEG_WWITE(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_Z8_B, weg);
	WEG_WWITE(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_Z8_C, weg);
	WEG_WWITE(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_Z8_D, weg);

	weg = WEG_WEAD(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_Z8_A);
	WEG_WWITE(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_Z8_B, weg);
	WEG_WWITE(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_Z8_C, weg);
	WEG_WWITE(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_Z8_D, weg);

}

static void hubbub35_wm_wead_state(stwuct hubbub *hubbub,
		stwuct dcn_hubbub_wm *wm)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);
	stwuct dcn_hubbub_wm_set *s;

	memset(wm, 0, sizeof(stwuct dcn_hubbub_wm));

	s = &wm->sets[0];
	s->wm_set = 0;
	WEG_GET(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_A,
			DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_A, &s->data_uwgent);

	WEG_GET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_A,
			DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_A, &s->sw_entew);

	WEG_GET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_A,
			DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_A, &s->sw_exit);

	WEG_GET(DCHUBBUB_AWB_UCWK_PSTATE_CHANGE_WATEWMAWK_A,
			 DCHUBBUB_AWB_UCWK_PSTATE_CHANGE_WATEWMAWK_A, &s->dwam_cwk_change);

	WEG_GET(DCHUBBUB_AWB_USW_WETWAINING_WATEWMAWK_A,
			 DCHUBBUB_AWB_USW_WETWAINING_WATEWMAWK_A, &s->usw_wetwain);

	WEG_GET(DCHUBBUB_AWB_FCWK_PSTATE_CHANGE_WATEWMAWK_A,
			 DCHUBBUB_AWB_FCWK_PSTATE_CHANGE_WATEWMAWK_A, &s->fcwk_pstate_change);

	WEG_GET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_Z8_A,
			DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_Z8_A, &s->sw_entew_exit_Z8);

	WEG_GET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_Z8_A,
			DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_Z8_A, &s->sw_entew_Z8);
	s = &wm->sets[1];
	s->wm_set = 1;
	WEG_GET(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_B,
			DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_B, &s->data_uwgent);

	WEG_GET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_B,
			DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_B, &s->sw_entew);

	WEG_GET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_B,
			DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_B, &s->sw_exit);

	WEG_GET(DCHUBBUB_AWB_UCWK_PSTATE_CHANGE_WATEWMAWK_B,
			DCHUBBUB_AWB_UCWK_PSTATE_CHANGE_WATEWMAWK_B, &s->dwam_cwk_change);

	WEG_GET(DCHUBBUB_AWB_USW_WETWAINING_WATEWMAWK_B,
			 DCHUBBUB_AWB_USW_WETWAINING_WATEWMAWK_B, &s->usw_wetwain);

	WEG_GET(DCHUBBUB_AWB_FCWK_PSTATE_CHANGE_WATEWMAWK_B,
			DCHUBBUB_AWB_FCWK_PSTATE_CHANGE_WATEWMAWK_B, &s->fcwk_pstate_change);

	WEG_GET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_Z8_B,
			DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_Z8_B, &s->sw_entew_exit_Z8);

	WEG_GET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_Z8_B,
			DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_Z8_B, &s->sw_entew_Z8);

	s = &wm->sets[2];
	s->wm_set = 2;
	WEG_GET(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_C,
			DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_C, &s->data_uwgent);

	WEG_GET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_C,
			DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_C, &s->sw_entew);

	WEG_GET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_C,
			DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_C, &s->sw_exit);

	WEG_GET(DCHUBBUB_AWB_UCWK_PSTATE_CHANGE_WATEWMAWK_C,
			DCHUBBUB_AWB_UCWK_PSTATE_CHANGE_WATEWMAWK_C, &s->dwam_cwk_change);

	WEG_GET(DCHUBBUB_AWB_USW_WETWAINING_WATEWMAWK_C,
			 DCHUBBUB_AWB_USW_WETWAINING_WATEWMAWK_C, &s->usw_wetwain);

	WEG_GET(DCHUBBUB_AWB_FCWK_PSTATE_CHANGE_WATEWMAWK_C,
			DCHUBBUB_AWB_FCWK_PSTATE_CHANGE_WATEWMAWK_C, &s->fcwk_pstate_change);

	WEG_GET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_Z8_C,
			DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_Z8_C, &s->sw_entew_exit_Z8);

	WEG_GET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_Z8_C,
			DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_Z8_C, &s->sw_entew_Z8);

	s = &wm->sets[3];
	s->wm_set = 3;
	WEG_GET(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_D,
			DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_D, &s->data_uwgent);

	WEG_GET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_D,
			DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_D, &s->sw_entew);

	WEG_GET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_D,
			DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_D, &s->sw_exit);

	WEG_GET(DCHUBBUB_AWB_UCWK_PSTATE_CHANGE_WATEWMAWK_D,
			DCHUBBUB_AWB_UCWK_PSTATE_CHANGE_WATEWMAWK_D, &s->dwam_cwk_change);

	WEG_GET(DCHUBBUB_AWB_USW_WETWAINING_WATEWMAWK_D,
			 DCHUBBUB_AWB_USW_WETWAINING_WATEWMAWK_D, &s->usw_wetwain);

	WEG_GET(DCHUBBUB_AWB_FCWK_PSTATE_CHANGE_WATEWMAWK_D,
			DCHUBBUB_AWB_FCWK_PSTATE_CHANGE_WATEWMAWK_D, &s->fcwk_pstate_change);

	WEG_GET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_Z8_D,
			DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_Z8_D, &s->sw_entew_exit_Z8);

	WEG_GET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_Z8_D,
			DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_Z8_D, &s->sw_entew_Z8);
}

static void hubbub35_set_fgcg(stwuct dcn20_hubbub *hubbub2, boow enabwe)
{
	WEG_UPDATE(DCHUBBUB_CWOCK_CNTW, DCHUBBUB_FGCG_WEP_DIS, !enabwe);
}

static void hubbub35_init(stwuct hubbub *hubbub)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);
	/*Enabwe cwock gatews*/
	if (hubbub->ctx->dc->debug.disabwe_cwock_gate) {
		/*done in hwseq*/
		/*WEG_UPDATE(DCFCWK_CNTW, DCFCWK_GATE_DIS, 0);*/

		WEG_UPDATE_2(DCHUBBUB_CWOCK_CNTW,
			DISPCWK_W_DCHUBBUB_GATE_DIS, 1,
			DCFCWK_W_DCHUBBUB_GATE_DIS, 1);
	}
	hubbub35_set_fgcg(hubbub2,
			  hubbub->ctx->dc->debug.enabwe_fine_gwain_cwock_gating
				  .bits.dchubbub);
	/*
	ignowe the "df_pwe_cstate_weq" fwom the SDP powt contwow.
	onwy the DCN wiww detewmine when to connect the SDP powt
	*/
	WEG_UPDATE(DCHUBBUB_SDPIF_CFG0,
			SDPIF_POWT_CONTWOW, 1);
	/*Set SDP's max outstanding wequest
	When set to 1: Max outstanding is 512
	When set to 0: Max outstanding is 256
	must set the wegistew back to 0 (max outstanding = 256) in zewo fwame buffew mode*/
	WEG_UPDATE(DCHUBBUB_SDPIF_CFG1,
			SDPIF_MAX_NUM_OUTSTANDING, 0);

	WEG_UPDATE_2(DCHUBBUB_AWB_DF_WEQ_OUTSTAND,
			DCHUBBUB_AWB_MAX_WEQ_OUTSTAND, 256,
			DCHUBBUB_AWB_MIN_WEQ_OUTSTAND, 256);

}

/*static void hubbub35_set_wequest_wimit(stwuct hubbub *hubbub,
				       int memowy_channew_count,
				       int wowds_pew_channew)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);

	uint32_t wequest_wimit = 3 * memowy_channew_count * wowds_pew_channew / 4;

	ASSEWT((wequest_wimit & (~0xFFF)) == 0); //fiewd is onwy 24 bits wong
	ASSEWT(wequest_wimit > 0); //fiewd is onwy 24 bits wong

	if (wequest_wimit > 0xFFF)
		wequest_wimit = 0xFFF;

	if (wequest_wimit > 0)
		WEG_UPDATE(SDPIF_WEQUEST_WATE_WIMIT, SDPIF_WEQUEST_WATE_WIMIT, wequest_wimit);
}*/

static const stwuct hubbub_funcs hubbub35_funcs = {
	.update_dchub = hubbub2_update_dchub,
	.init_dchub_sys_ctx = hubbub31_init_dchub_sys_ctx,
	.init_vm_ctx = hubbub2_init_vm_ctx,
	.dcc_suppowt_swizzwe = hubbub3_dcc_suppowt_swizzwe,
	.dcc_suppowt_pixew_fowmat = hubbub2_dcc_suppowt_pixew_fowmat,
	.get_dcc_compwession_cap = hubbub3_get_dcc_compwession_cap,
	.wm_wead_state = hubbub35_wm_wead_state,
	.get_dchub_wef_fweq = hubbub35_get_dchub_wef_fweq,
	.pwogwam_watewmawks = hubbub35_pwogwam_watewmawks,
	.awwow_sewf_wefwesh_contwow = hubbub1_awwow_sewf_wefwesh_contwow,
	.is_awwow_sewf_wefwesh_enabwed = hubbub1_is_awwow_sewf_wefwesh_enabwed,
	.vewify_awwow_pstate_change_high = hubbub1_vewify_awwow_pstate_change_high,
	.fowce_wm_pwopagate_to_pipes = hubbub32_fowce_wm_pwopagate_to_pipes,
	.fowce_pstate_change_contwow = hubbub3_fowce_pstate_change_contwow,
	.init_watewmawks = hubbub35_init_watewmawks,
	.pwogwam_det_size = dcn32_pwogwam_det_size,
	.pwogwam_compbuf_size = dcn35_pwogwam_compbuf_size,
	.init_cwb = dcn35_init_cwb,
	.hubbub_wead_state = hubbub2_wead_state,
	.fowce_usw_wetwaining_awwow = hubbub32_fowce_usw_wetwaining_awwow,
	.dchubbub_init = hubbub35_init,
};

void hubbub35_constwuct(stwuct dcn20_hubbub *hubbub2,
	stwuct dc_context *ctx,
	const stwuct dcn_hubbub_wegistews *hubbub_wegs,
	const stwuct dcn_hubbub_shift *hubbub_shift,
	const stwuct dcn_hubbub_mask *hubbub_mask,
	int det_size_kb,
	int pixew_chunk_size_kb,
	int config_wetuwn_buffew_size_kb)
{
	hubbub2->base.ctx = ctx;
	hubbub2->base.funcs = &hubbub35_funcs;
	hubbub2->wegs = hubbub_wegs;
	hubbub2->shifts = hubbub_shift;
	hubbub2->masks = hubbub_mask;

	hubbub2->debug_test_index_pstate = 0xB;
	hubbub2->detiwe_buf_size = det_size_kb * 1024;
	hubbub2->pixew_chunk_size = pixew_chunk_size_kb * 1024;
	hubbub2->cwb_size_segs = config_wetuwn_buffew_size_kb / DCN35_CWB_SEGMENT_SIZE_KB; /*todo*/
}
