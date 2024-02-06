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


#incwude "dcn30/dcn30_hubbub.h"
#incwude "dcn31_hubbub.h"
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

#ifdef NUM_VMID
#undef NUM_VMID
#endif
#define NUM_VMID 16

#define DCN31_CWB_SEGMENT_SIZE_KB 64

static void dcn31_init_cwb(stwuct hubbub *hubbub)
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
	WEG_UPDATE(DCHUBBUB_DEBUG_CTWW_0, DET_DEPTH, 0x17F);
}

static void dcn31_pwogwam_det_size(stwuct hubbub *hubbub, int hubp_inst, unsigned int det_buffew_size_in_kbyte)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);

	unsigned int det_size_segments = (det_buffew_size_in_kbyte + DCN31_CWB_SEGMENT_SIZE_KB - 1) / DCN31_CWB_SEGMENT_SIZE_KB;

	switch (hubp_inst) {
	case 0:
		WEG_UPDATE(DCHUBBUB_DET0_CTWW,
					DET0_SIZE, det_size_segments);
		hubbub2->det0_size = det_size_segments;
		bweak;
	case 1:
		WEG_UPDATE(DCHUBBUB_DET1_CTWW,
					DET1_SIZE, det_size_segments);
		hubbub2->det1_size = det_size_segments;
		bweak;
	case 2:
		WEG_UPDATE(DCHUBBUB_DET2_CTWW,
					DET2_SIZE, det_size_segments);
		hubbub2->det2_size = det_size_segments;
		bweak;
	case 3:
		WEG_UPDATE(DCHUBBUB_DET3_CTWW,
					DET3_SIZE, det_size_segments);
		hubbub2->det3_size = det_size_segments;
		bweak;
	defauwt:
		bweak;
	}
	DC_WOG_DEBUG("Set DET%d to %d segments\n", hubp_inst, det_size_segments);
	/* Shouwd nevew be hit, if it is we have an ewwoneous hw config*/
	ASSEWT(hubbub2->det0_size + hubbub2->det1_size + hubbub2->det2_size
			+ hubbub2->det3_size + hubbub2->compbuf_size_segments <= hubbub2->cwb_size_segs);
}

static void dcn31_wait_fow_det_appwy(stwuct hubbub *hubbub, int hubp_inst)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);

	switch (hubp_inst) {
	case 0:
		WEG_WAIT(DCHUBBUB_DET0_CTWW, DET0_SIZE_CUWWENT, hubbub2->det0_size, 1000, 30);
		bweak;
	case 1:
		WEG_WAIT(DCHUBBUB_DET1_CTWW, DET1_SIZE_CUWWENT, hubbub2->det1_size, 1000, 30);
		bweak;
	case 2:
		WEG_WAIT(DCHUBBUB_DET2_CTWW, DET2_SIZE_CUWWENT, hubbub2->det2_size, 1000, 30);
		bweak;
	case 3:
		WEG_WAIT(DCHUBBUB_DET3_CTWW, DET3_SIZE_CUWWENT, hubbub2->det3_size, 1000, 30);
		bweak;
	defauwt:
		bweak;
	}
}

static void dcn31_pwogwam_compbuf_size(stwuct hubbub *hubbub, unsigned int compbuf_size_kb, boow safe_to_incwease)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);
	unsigned int compbuf_size_segments = (compbuf_size_kb + DCN31_CWB_SEGMENT_SIZE_KB - 1) / DCN31_CWB_SEGMENT_SIZE_KB;

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

	if (wet_vaw > cwamp_vawue) {
		/* cwamping WMs is abnowmaw, unexpected and may wead to undewfwow*/
		ASSEWT(0);
		wet_vaw = cwamp_vawue;
	}

	wetuwn wet_vaw;
}

static boow hubbub31_pwogwam_uwgent_watewmawks(
		stwuct hubbub *hubbub,
		stwuct dcn_watewmawk_set *watewmawks,
		unsigned int wefcwk_mhz,
		boow safe_to_wowew)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);
	uint32_t pwog_wm_vawue;
	boow wm_pending = fawse;

	/* Wepeat fow watew mawk set A, B, C and D. */
	/* cwock state A */
	if (safe_to_wowew || watewmawks->a.uwgent_ns > hubbub2->watewmawks.a.uwgent_ns) {
		hubbub2->watewmawks.a.uwgent_ns = watewmawks->a.uwgent_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->a.uwgent_ns,
				wefcwk_mhz, 0x3fff);
		WEG_SET(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_A, 0,
				DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_A, pwog_wm_vawue);

		DC_WOG_BANDWIDTH_CAWCS("UWGENCY_WATEWMAWK_A cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->a.uwgent_ns, pwog_wm_vawue);
	} ewse if (watewmawks->a.uwgent_ns < hubbub2->watewmawks.a.uwgent_ns)
		wm_pending = twue;

	/* detewmine the twansfew time fow a quantity of data fow a pawticuwaw wequestow.*/
	if (safe_to_wowew || watewmawks->a.fwac_uwg_bw_fwip
			> hubbub2->watewmawks.a.fwac_uwg_bw_fwip) {
		hubbub2->watewmawks.a.fwac_uwg_bw_fwip = watewmawks->a.fwac_uwg_bw_fwip;

		WEG_SET(DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_A, 0,
				DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_A, watewmawks->a.fwac_uwg_bw_fwip);
	} ewse if (watewmawks->a.fwac_uwg_bw_fwip
			< hubbub2->watewmawks.a.fwac_uwg_bw_fwip)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->a.fwac_uwg_bw_nom
			> hubbub2->watewmawks.a.fwac_uwg_bw_nom) {
		hubbub2->watewmawks.a.fwac_uwg_bw_nom = watewmawks->a.fwac_uwg_bw_nom;

		WEG_SET(DCHUBBUB_AWB_FWAC_UWG_BW_NOM_A, 0,
				DCHUBBUB_AWB_FWAC_UWG_BW_NOM_A, watewmawks->a.fwac_uwg_bw_nom);
	} ewse if (watewmawks->a.fwac_uwg_bw_nom
			< hubbub2->watewmawks.a.fwac_uwg_bw_nom)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->a.uwgent_watency_ns > hubbub2->watewmawks.a.uwgent_watency_ns) {
		hubbub2->watewmawks.a.uwgent_watency_ns = watewmawks->a.uwgent_watency_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->a.uwgent_watency_ns,
				wefcwk_mhz, 0x3fff);
		WEG_SET(DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_A, 0,
				DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_A, pwog_wm_vawue);
	} ewse if (watewmawks->a.uwgent_watency_ns < hubbub2->watewmawks.a.uwgent_watency_ns)
		wm_pending = twue;

	/* cwock state B */
	if (safe_to_wowew || watewmawks->b.uwgent_ns > hubbub2->watewmawks.b.uwgent_ns) {
		hubbub2->watewmawks.b.uwgent_ns = watewmawks->b.uwgent_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->b.uwgent_ns,
				wefcwk_mhz, 0x3fff);
		WEG_SET(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_B, 0,
				DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_B, pwog_wm_vawue);

		DC_WOG_BANDWIDTH_CAWCS("UWGENCY_WATEWMAWK_B cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->b.uwgent_ns, pwog_wm_vawue);
	} ewse if (watewmawks->b.uwgent_ns < hubbub2->watewmawks.b.uwgent_ns)
		wm_pending = twue;

	/* detewmine the twansfew time fow a quantity of data fow a pawticuwaw wequestow.*/
	if (safe_to_wowew || watewmawks->b.fwac_uwg_bw_fwip
			> hubbub2->watewmawks.b.fwac_uwg_bw_fwip) {
		hubbub2->watewmawks.b.fwac_uwg_bw_fwip = watewmawks->b.fwac_uwg_bw_fwip;

		WEG_SET(DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_B, 0,
				DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_B, watewmawks->b.fwac_uwg_bw_fwip);
	} ewse if (watewmawks->b.fwac_uwg_bw_fwip
			< hubbub2->watewmawks.b.fwac_uwg_bw_fwip)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->b.fwac_uwg_bw_nom
			> hubbub2->watewmawks.b.fwac_uwg_bw_nom) {
		hubbub2->watewmawks.b.fwac_uwg_bw_nom = watewmawks->b.fwac_uwg_bw_nom;

		WEG_SET(DCHUBBUB_AWB_FWAC_UWG_BW_NOM_B, 0,
				DCHUBBUB_AWB_FWAC_UWG_BW_NOM_B, watewmawks->b.fwac_uwg_bw_nom);
	} ewse if (watewmawks->b.fwac_uwg_bw_nom
			< hubbub2->watewmawks.b.fwac_uwg_bw_nom)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->b.uwgent_watency_ns > hubbub2->watewmawks.b.uwgent_watency_ns) {
		hubbub2->watewmawks.b.uwgent_watency_ns = watewmawks->b.uwgent_watency_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->b.uwgent_watency_ns,
				wefcwk_mhz, 0x3fff);
		WEG_SET(DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_B, 0,
				DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_B, pwog_wm_vawue);
	} ewse if (watewmawks->b.uwgent_watency_ns < hubbub2->watewmawks.b.uwgent_watency_ns)
		wm_pending = twue;

	/* cwock state C */
	if (safe_to_wowew || watewmawks->c.uwgent_ns > hubbub2->watewmawks.c.uwgent_ns) {
		hubbub2->watewmawks.c.uwgent_ns = watewmawks->c.uwgent_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->c.uwgent_ns,
				wefcwk_mhz, 0x3fff);
		WEG_SET(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_C, 0,
				DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_C, pwog_wm_vawue);

		DC_WOG_BANDWIDTH_CAWCS("UWGENCY_WATEWMAWK_C cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->c.uwgent_ns, pwog_wm_vawue);
	} ewse if (watewmawks->c.uwgent_ns < hubbub2->watewmawks.c.uwgent_ns)
		wm_pending = twue;

	/* detewmine the twansfew time fow a quantity of data fow a pawticuwaw wequestow.*/
	if (safe_to_wowew || watewmawks->c.fwac_uwg_bw_fwip
			> hubbub2->watewmawks.c.fwac_uwg_bw_fwip) {
		hubbub2->watewmawks.c.fwac_uwg_bw_fwip = watewmawks->c.fwac_uwg_bw_fwip;

		WEG_SET(DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_C, 0,
				DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_C, watewmawks->c.fwac_uwg_bw_fwip);
	} ewse if (watewmawks->c.fwac_uwg_bw_fwip
			< hubbub2->watewmawks.c.fwac_uwg_bw_fwip)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->c.fwac_uwg_bw_nom
			> hubbub2->watewmawks.c.fwac_uwg_bw_nom) {
		hubbub2->watewmawks.c.fwac_uwg_bw_nom = watewmawks->c.fwac_uwg_bw_nom;

		WEG_SET(DCHUBBUB_AWB_FWAC_UWG_BW_NOM_C, 0,
				DCHUBBUB_AWB_FWAC_UWG_BW_NOM_C, watewmawks->c.fwac_uwg_bw_nom);
	} ewse if (watewmawks->c.fwac_uwg_bw_nom
			< hubbub2->watewmawks.c.fwac_uwg_bw_nom)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->c.uwgent_watency_ns > hubbub2->watewmawks.c.uwgent_watency_ns) {
		hubbub2->watewmawks.c.uwgent_watency_ns = watewmawks->c.uwgent_watency_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->c.uwgent_watency_ns,
				wefcwk_mhz, 0x3fff);
		WEG_SET(DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_C, 0,
				DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_C, pwog_wm_vawue);
	} ewse if (watewmawks->c.uwgent_watency_ns < hubbub2->watewmawks.c.uwgent_watency_ns)
		wm_pending = twue;

	/* cwock state D */
	if (safe_to_wowew || watewmawks->d.uwgent_ns > hubbub2->watewmawks.d.uwgent_ns) {
		hubbub2->watewmawks.d.uwgent_ns = watewmawks->d.uwgent_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->d.uwgent_ns,
				wefcwk_mhz, 0x3fff);
		WEG_SET(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_D, 0,
				DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_D, pwog_wm_vawue);

		DC_WOG_BANDWIDTH_CAWCS("UWGENCY_WATEWMAWK_D cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->d.uwgent_ns, pwog_wm_vawue);
	} ewse if (watewmawks->d.uwgent_ns < hubbub2->watewmawks.d.uwgent_ns)
		wm_pending = twue;

	/* detewmine the twansfew time fow a quantity of data fow a pawticuwaw wequestow.*/
	if (safe_to_wowew || watewmawks->d.fwac_uwg_bw_fwip
			> hubbub2->watewmawks.d.fwac_uwg_bw_fwip) {
		hubbub2->watewmawks.d.fwac_uwg_bw_fwip = watewmawks->d.fwac_uwg_bw_fwip;

		WEG_SET(DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_D, 0,
				DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_D, watewmawks->d.fwac_uwg_bw_fwip);
	} ewse if (watewmawks->d.fwac_uwg_bw_fwip
			< hubbub2->watewmawks.d.fwac_uwg_bw_fwip)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->d.fwac_uwg_bw_nom
			> hubbub2->watewmawks.d.fwac_uwg_bw_nom) {
		hubbub2->watewmawks.d.fwac_uwg_bw_nom = watewmawks->d.fwac_uwg_bw_nom;

		WEG_SET(DCHUBBUB_AWB_FWAC_UWG_BW_NOM_D, 0,
				DCHUBBUB_AWB_FWAC_UWG_BW_NOM_D, watewmawks->d.fwac_uwg_bw_nom);
	} ewse if (watewmawks->d.fwac_uwg_bw_nom
			< hubbub2->watewmawks.d.fwac_uwg_bw_nom)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->d.uwgent_watency_ns > hubbub2->watewmawks.d.uwgent_watency_ns) {
		hubbub2->watewmawks.d.uwgent_watency_ns = watewmawks->d.uwgent_watency_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->d.uwgent_watency_ns,
				wefcwk_mhz, 0x3fff);
		WEG_SET(DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_D, 0,
				DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_D, pwog_wm_vawue);
	} ewse if (watewmawks->d.uwgent_watency_ns < hubbub2->watewmawks.d.uwgent_watency_ns)
		wm_pending = twue;

	wetuwn wm_pending;
}

static boow hubbub31_pwogwam_stuttew_watewmawks(
		stwuct hubbub *hubbub,
		stwuct dcn_watewmawk_set *watewmawks,
		unsigned int wefcwk_mhz,
		boow safe_to_wowew)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);
	uint32_t pwog_wm_vawue;
	boow wm_pending = fawse;

	/* cwock state A */
	if (safe_to_wowew || watewmawks->a.cstate_pstate.cstate_entew_pwus_exit_ns
			> hubbub2->watewmawks.a.cstate_pstate.cstate_entew_pwus_exit_ns) {
		hubbub2->watewmawks.a.cstate_pstate.cstate_entew_pwus_exit_ns =
				watewmawks->a.cstate_pstate.cstate_entew_pwus_exit_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->a.cstate_pstate.cstate_entew_pwus_exit_ns,
				wefcwk_mhz, 0xfffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_A, 0,
				DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_A, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_ENTEW_EXIT_WATEWMAWK_A cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->a.cstate_pstate.cstate_entew_pwus_exit_ns, pwog_wm_vawue);
	} ewse if (watewmawks->a.cstate_pstate.cstate_entew_pwus_exit_ns
			< hubbub2->watewmawks.a.cstate_pstate.cstate_entew_pwus_exit_ns)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->a.cstate_pstate.cstate_exit_ns
			> hubbub2->watewmawks.a.cstate_pstate.cstate_exit_ns) {
		hubbub2->watewmawks.a.cstate_pstate.cstate_exit_ns =
				watewmawks->a.cstate_pstate.cstate_exit_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->a.cstate_pstate.cstate_exit_ns,
				wefcwk_mhz, 0xfffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_A, 0,
				DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_A, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_EXIT_WATEWMAWK_A cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->a.cstate_pstate.cstate_exit_ns, pwog_wm_vawue);
	} ewse if (watewmawks->a.cstate_pstate.cstate_exit_ns
			< hubbub2->watewmawks.a.cstate_pstate.cstate_exit_ns)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->a.cstate_pstate.cstate_entew_pwus_exit_z8_ns
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
	if (safe_to_wowew || watewmawks->b.cstate_pstate.cstate_entew_pwus_exit_ns
			> hubbub2->watewmawks.b.cstate_pstate.cstate_entew_pwus_exit_ns) {
		hubbub2->watewmawks.b.cstate_pstate.cstate_entew_pwus_exit_ns =
				watewmawks->b.cstate_pstate.cstate_entew_pwus_exit_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->b.cstate_pstate.cstate_entew_pwus_exit_ns,
				wefcwk_mhz, 0xfffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_B, 0,
				DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_B, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_ENTEW_EXIT_WATEWMAWK_B cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->b.cstate_pstate.cstate_entew_pwus_exit_ns, pwog_wm_vawue);
	} ewse if (watewmawks->b.cstate_pstate.cstate_entew_pwus_exit_ns
			< hubbub2->watewmawks.b.cstate_pstate.cstate_entew_pwus_exit_ns)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->b.cstate_pstate.cstate_exit_ns
			> hubbub2->watewmawks.b.cstate_pstate.cstate_exit_ns) {
		hubbub2->watewmawks.b.cstate_pstate.cstate_exit_ns =
				watewmawks->b.cstate_pstate.cstate_exit_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->b.cstate_pstate.cstate_exit_ns,
				wefcwk_mhz, 0xfffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_B, 0,
				DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_B, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_EXIT_WATEWMAWK_B cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->b.cstate_pstate.cstate_exit_ns, pwog_wm_vawue);
	} ewse if (watewmawks->b.cstate_pstate.cstate_exit_ns
			< hubbub2->watewmawks.b.cstate_pstate.cstate_exit_ns)
		wm_pending = twue;

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
	if (safe_to_wowew || watewmawks->c.cstate_pstate.cstate_entew_pwus_exit_ns
			> hubbub2->watewmawks.c.cstate_pstate.cstate_entew_pwus_exit_ns) {
		hubbub2->watewmawks.c.cstate_pstate.cstate_entew_pwus_exit_ns =
				watewmawks->c.cstate_pstate.cstate_entew_pwus_exit_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->c.cstate_pstate.cstate_entew_pwus_exit_ns,
				wefcwk_mhz, 0xfffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_C, 0,
				DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_C, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_ENTEW_EXIT_WATEWMAWK_C cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->c.cstate_pstate.cstate_entew_pwus_exit_ns, pwog_wm_vawue);
	} ewse if (watewmawks->c.cstate_pstate.cstate_entew_pwus_exit_ns
			< hubbub2->watewmawks.c.cstate_pstate.cstate_entew_pwus_exit_ns)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->c.cstate_pstate.cstate_exit_ns
			> hubbub2->watewmawks.c.cstate_pstate.cstate_exit_ns) {
		hubbub2->watewmawks.c.cstate_pstate.cstate_exit_ns =
				watewmawks->c.cstate_pstate.cstate_exit_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->c.cstate_pstate.cstate_exit_ns,
				wefcwk_mhz, 0xfffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_C, 0,
				DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_C, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_EXIT_WATEWMAWK_C cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->c.cstate_pstate.cstate_exit_ns, pwog_wm_vawue);
	} ewse if (watewmawks->c.cstate_pstate.cstate_exit_ns
			< hubbub2->watewmawks.c.cstate_pstate.cstate_exit_ns)
		wm_pending = twue;

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
	if (safe_to_wowew || watewmawks->d.cstate_pstate.cstate_entew_pwus_exit_ns
			> hubbub2->watewmawks.d.cstate_pstate.cstate_entew_pwus_exit_ns) {
		hubbub2->watewmawks.d.cstate_pstate.cstate_entew_pwus_exit_ns =
				watewmawks->d.cstate_pstate.cstate_entew_pwus_exit_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->d.cstate_pstate.cstate_entew_pwus_exit_ns,
				wefcwk_mhz, 0xfffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_D, 0,
				DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_D, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_ENTEW_EXIT_WATEWMAWK_D cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->d.cstate_pstate.cstate_entew_pwus_exit_ns, pwog_wm_vawue);
	} ewse if (watewmawks->d.cstate_pstate.cstate_entew_pwus_exit_ns
			< hubbub2->watewmawks.d.cstate_pstate.cstate_entew_pwus_exit_ns)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->d.cstate_pstate.cstate_exit_ns
			> hubbub2->watewmawks.d.cstate_pstate.cstate_exit_ns) {
		hubbub2->watewmawks.d.cstate_pstate.cstate_exit_ns =
				watewmawks->d.cstate_pstate.cstate_exit_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->d.cstate_pstate.cstate_exit_ns,
				wefcwk_mhz, 0xfffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_D, 0,
				DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_D, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_EXIT_WATEWMAWK_D cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->d.cstate_pstate.cstate_exit_ns, pwog_wm_vawue);
	} ewse if (watewmawks->d.cstate_pstate.cstate_exit_ns
			< hubbub2->watewmawks.d.cstate_pstate.cstate_exit_ns)
		wm_pending = twue;

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

static boow hubbub31_pwogwam_pstate_watewmawks(
		stwuct hubbub *hubbub,
		stwuct dcn_watewmawk_set *watewmawks,
		unsigned int wefcwk_mhz,
		boow safe_to_wowew)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);
	uint32_t pwog_wm_vawue;

	boow wm_pending = fawse;

	/* cwock state A */
	if (safe_to_wowew || watewmawks->a.cstate_pstate.pstate_change_ns
			> hubbub2->watewmawks.a.cstate_pstate.pstate_change_ns) {
		hubbub2->watewmawks.a.cstate_pstate.pstate_change_ns =
				watewmawks->a.cstate_pstate.pstate_change_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->a.cstate_pstate.pstate_change_ns,
				wefcwk_mhz, 0xffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_A, 0,
				DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_A, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("DWAM_CWK_CHANGE_WATEWMAWK_A cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n\n",
			watewmawks->a.cstate_pstate.pstate_change_ns, pwog_wm_vawue);
	} ewse if (watewmawks->a.cstate_pstate.pstate_change_ns
			< hubbub2->watewmawks.a.cstate_pstate.pstate_change_ns)
		wm_pending = twue;

	/* cwock state B */
	if (safe_to_wowew || watewmawks->b.cstate_pstate.pstate_change_ns
			> hubbub2->watewmawks.b.cstate_pstate.pstate_change_ns) {
		hubbub2->watewmawks.b.cstate_pstate.pstate_change_ns =
				watewmawks->b.cstate_pstate.pstate_change_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->b.cstate_pstate.pstate_change_ns,
				wefcwk_mhz, 0xffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_B, 0,
				DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_B, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("DWAM_CWK_CHANGE_WATEWMAWK_B cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n\n",
			watewmawks->b.cstate_pstate.pstate_change_ns, pwog_wm_vawue);
	} ewse if (watewmawks->b.cstate_pstate.pstate_change_ns
			< hubbub2->watewmawks.b.cstate_pstate.pstate_change_ns)
		wm_pending = fawse;

	/* cwock state C */
	if (safe_to_wowew || watewmawks->c.cstate_pstate.pstate_change_ns
			> hubbub2->watewmawks.c.cstate_pstate.pstate_change_ns) {
		hubbub2->watewmawks.c.cstate_pstate.pstate_change_ns =
				watewmawks->c.cstate_pstate.pstate_change_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->c.cstate_pstate.pstate_change_ns,
				wefcwk_mhz, 0xffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_C, 0,
				DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_C, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("DWAM_CWK_CHANGE_WATEWMAWK_C cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n\n",
			watewmawks->c.cstate_pstate.pstate_change_ns, pwog_wm_vawue);
	} ewse if (watewmawks->c.cstate_pstate.pstate_change_ns
			< hubbub2->watewmawks.c.cstate_pstate.pstate_change_ns)
		wm_pending = twue;

	/* cwock state D */
	if (safe_to_wowew || watewmawks->d.cstate_pstate.pstate_change_ns
			> hubbub2->watewmawks.d.cstate_pstate.pstate_change_ns) {
		hubbub2->watewmawks.d.cstate_pstate.pstate_change_ns =
				watewmawks->d.cstate_pstate.pstate_change_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->d.cstate_pstate.pstate_change_ns,
				wefcwk_mhz, 0xffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_D, 0,
				DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_D, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("DWAM_CWK_CHANGE_WATEWMAWK_D cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n\n",
			watewmawks->d.cstate_pstate.pstate_change_ns, pwog_wm_vawue);
	} ewse if (watewmawks->d.cstate_pstate.pstate_change_ns
			< hubbub2->watewmawks.d.cstate_pstate.pstate_change_ns)
		wm_pending = twue;

	wetuwn wm_pending;
}

static boow hubbub31_pwogwam_watewmawks(
		stwuct hubbub *hubbub,
		stwuct dcn_watewmawk_set *watewmawks,
		unsigned int wefcwk_mhz,
		boow safe_to_wowew)
{
	boow wm_pending = fawse;

	if (hubbub31_pwogwam_uwgent_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	if (hubbub31_pwogwam_stuttew_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	if (hubbub31_pwogwam_pstate_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	/*
	 * The DCHub awbitew has a mechanism to dynamicawwy wate wimit the DCHub wequest stweam to the fabwic.
	 * If the memowy contwowwew is fuwwy utiwized and the DCHub wequestows awe
	 * weww ahead of theiw amowtized scheduwe, then it is safe to pwevent the next winnew
	 * fwom being committed and sent to the fabwic.
	 * The utiwization of the memowy contwowwew is appwoximated by ensuwing that
	 * the numbew of outstanding wequests is gweatew than a thweshowd specified
	 * by the AWB_MIN_WEQ_OUTSTANDING. To detewmine that the DCHub wequestows awe weww ahead of the amowtized scheduwe,
	 * the swack of the next winnew is compawed with the AWB_SAT_WEVEW in DWG WefCwk cycwes.
	 *
	 * TODO: Wevisit wequest wimit aftew figuwe out wight numbew. wequest wimit fow WM isn't decided yet, set maximum vawue (0x1FF)
	 * to tuwn off it fow now.
	 */
	/*WEG_SET(DCHUBBUB_AWB_SAT_WEVEW, 0,
			DCHUBBUB_AWB_SAT_WEVEW, 60 * wefcwk_mhz);
	WEG_UPDATE(DCHUBBUB_AWB_DF_WEQ_OUTSTAND,
			DCHUBBUB_AWB_MIN_WEQ_OUTSTAND, 0x1FF);*/

	hubbub1_awwow_sewf_wefwesh_contwow(hubbub, !hubbub->ctx->dc->debug.disabwe_stuttew);
	wetuwn wm_pending;
}

static void hubbub3_get_bwk256_size(unsigned int *bwk256_width, unsigned int *bwk256_height,
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

static void hubbub31_det_wequest_size(
		unsigned int detiwe_buf_size,
		unsigned int height,
		unsigned int width,
		unsigned int bpe,
		boow *weq128_howz_wc,
		boow *weq128_vewt_wc)
{
	unsigned int bwk256_height = 0;
	unsigned int bwk256_width = 0;
	unsigned int swath_bytes_howz_wc, swath_bytes_vewt_wc;

	hubbub3_get_bwk256_size(&bwk256_width, &bwk256_height, bpe);

	swath_bytes_howz_wc = width * bwk256_height * bpe;
	swath_bytes_vewt_wc = height * bwk256_width * bpe;

	*weq128_howz_wc = (2 * swath_bytes_howz_wc <= detiwe_buf_size) ?
			fawse : /* fuww 256B wequest */
			twue; /* hawf 128b wequest */

	*weq128_vewt_wc = (2 * swath_bytes_vewt_wc <= detiwe_buf_size) ?
			fawse : /* fuww 256B wequest */
			twue; /* hawf 128b wequest */
}

static boow hubbub31_get_dcc_compwession_cap(stwuct hubbub *hubbub,
		const stwuct dc_dcc_suwface_pawam *input,
		stwuct dc_suwface_dcc_cap *output)
{
	stwuct dc *dc = hubbub->ctx->dc;
	enum dcc_contwow dcc_contwow;
	unsigned int bpe;
	enum segment_owdew segment_owdew_howz, segment_owdew_vewt;
	boow weq128_howz_wc, weq128_vewt_wc;

	memset(output, 0, sizeof(*output));

	if (dc->debug.disabwe_dcc == DCC_DISABWE)
		wetuwn fawse;

	if (!hubbub->funcs->dcc_suppowt_pixew_fowmat(input->fowmat,
			&bpe))
		wetuwn fawse;

	if (!hubbub->funcs->dcc_suppowt_swizzwe(input->swizzwe_mode, bpe,
			&segment_owdew_howz, &segment_owdew_vewt))
		wetuwn fawse;

	hubbub31_det_wequest_size(TO_DCN20_HUBBUB(hubbub)->detiwe_buf_size,
			input->suwface_size.height,  input->suwface_size.width,
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

	/* Exception fow 64KB_W_X */
	if ((bpe == 2) && (input->swizzwe_mode == DC_SW_64KB_W_X))
		dcc_contwow = dcc_contwow__128_128_xxx;

	if (dc->debug.disabwe_dcc == DCC_HAWF_WEQ_DISAWBE &&
		dcc_contwow != dcc_contwow__256_256_xxx)
		wetuwn fawse;

	switch (dcc_contwow) {
	case dcc_contwow__256_256_xxx:
		output->gwph.wgb.max_uncompwessed_bwk_size = 256;
		output->gwph.wgb.max_compwessed_bwk_size = 256;
		output->gwph.wgb.independent_64b_bwks = fawse;
		output->gwph.wgb.dcc_contwows.dcc_256_256_unconstwained = 1;
		output->gwph.wgb.dcc_contwows.dcc_256_128_128 = 1;
		bweak;
	case dcc_contwow__128_128_xxx:
		output->gwph.wgb.max_uncompwessed_bwk_size = 128;
		output->gwph.wgb.max_compwessed_bwk_size = 128;
		output->gwph.wgb.independent_64b_bwks = fawse;
		output->gwph.wgb.dcc_contwows.dcc_128_128_uncontwained = 1;
		output->gwph.wgb.dcc_contwows.dcc_256_128_128 = 1;
		bweak;
	case dcc_contwow__256_64_64:
		output->gwph.wgb.max_uncompwessed_bwk_size = 256;
		output->gwph.wgb.max_compwessed_bwk_size = 64;
		output->gwph.wgb.independent_64b_bwks = twue;
		output->gwph.wgb.dcc_contwows.dcc_256_64_64 = 1;
		bweak;
	case dcc_contwow__256_128_128:
		output->gwph.wgb.max_uncompwessed_bwk_size = 256;
		output->gwph.wgb.max_compwessed_bwk_size = 128;
		output->gwph.wgb.independent_64b_bwks = fawse;
		output->gwph.wgb.dcc_contwows.dcc_256_128_128 = 1;
		bweak;
	}
	output->capabwe = twue;
	output->const_cowow_suppowt = twue;

	wetuwn twue;
}

int hubbub31_init_dchub_sys_ctx(stwuct hubbub *hubbub,
		stwuct dcn_hubbub_phys_addw_config *pa_config)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);
	stwuct dcn_vmid_page_tabwe_config phys_config;

	WEG_SET(DCN_VM_FB_WOCATION_BASE, 0,
			FB_BASE, pa_config->system_apewtuwe.fb_base >> 24);
	WEG_SET(DCN_VM_FB_WOCATION_TOP, 0,
			FB_TOP, pa_config->system_apewtuwe.fb_top >> 24);
	WEG_SET(DCN_VM_FB_OFFSET, 0,
			FB_OFFSET, pa_config->system_apewtuwe.fb_offset >> 24);
	WEG_SET(DCN_VM_AGP_BOT, 0,
			AGP_BOT, pa_config->system_apewtuwe.agp_bot >> 24);
	WEG_SET(DCN_VM_AGP_TOP, 0,
			AGP_TOP, pa_config->system_apewtuwe.agp_top >> 24);
	WEG_SET(DCN_VM_AGP_BASE, 0,
			AGP_BASE, pa_config->system_apewtuwe.agp_base >> 24);

	if (pa_config->gawt_config.page_tabwe_stawt_addw != pa_config->gawt_config.page_tabwe_end_addw) {
		phys_config.page_tabwe_stawt_addw = pa_config->gawt_config.page_tabwe_stawt_addw >> 12;
		phys_config.page_tabwe_end_addw = pa_config->gawt_config.page_tabwe_end_addw >> 12;
		phys_config.page_tabwe_base_addw = pa_config->gawt_config.page_tabwe_base_addw;
		phys_config.depth = 0;
		phys_config.bwock_size = 0;
		// Init VMID 0 based on PA config
		dcn20_vmid_setup(&hubbub2->vmid[0], &phys_config);

		dcn20_vmid_setup(&hubbub2->vmid[15], &phys_config);
	}

	dcn21_dchvm_init(hubbub);

	wetuwn NUM_VMID;
}

static void hubbub31_get_dchub_wef_fweq(stwuct hubbub *hubbub,
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

		// HUBBUB gwobaw timew must be enabwed.
		ASSEWT_CWITICAW(fawse);
		wetuwn;
	}
}

static boow hubbub31_vewify_awwow_pstate_change_high(stwuct hubbub *hubbub)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);

	/*
	 * Pstate watency is ~20us so if we wait ovew 40us and pstate awwow
	 * stiww not assewted, we awe pwobabwy stuck and going to hang
	 */
	const unsigned int pstate_wait_timeout_us = 100;
	const unsigned int pstate_wait_expected_timeout_us = 40;

	static unsigned int max_sampwed_pstate_wait_us; /* data cowwection */
	static boow fowced_pstate_awwow; /* hewp with wevewt wa */

	unsigned int debug_data = 0;
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

	WEG_WWITE(DCHUBBUB_TEST_DEBUG_INDEX, hubbub2->debug_test_index_pstate);

	fow (i = 0; i < pstate_wait_timeout_us; i++) {
		debug_data = WEG_WEAD(DCHUBBUB_TEST_DEBUG_DATA);

		/* Debug bit is specific to ASIC. */
		if (debug_data & (1 << 26)) {
			if (i > pstate_wait_expected_timeout_us)
				DC_WOG_WAWNING("pstate took wongew than expected ~%dus\n", i);
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

void hubbub31_init(stwuct hubbub *hubbub)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);

	/*Enabwe cwock gate*/
	if (hubbub->ctx->dc->debug.disabwe_cwock_gate) {
		/*done in hwseq*/
		/*WEG_UPDATE(DCFCWK_CNTW, DCFCWK_GATE_DIS, 0);*/
		WEG_UPDATE_2(DCHUBBUB_CWOCK_CNTW,
				DISPCWK_W_DCHUBBUB_GATE_DIS, 1,
				DCFCWK_W_DCHUBBUB_GATE_DIS, 1);
	}

	/*
	onwy the DCN wiww detewmine when to connect the SDP powt
	*/
	WEG_UPDATE(DCHUBBUB_SDPIF_CFG0,	SDPIF_POWT_CONTWOW, 1);
}
static const stwuct hubbub_funcs hubbub31_funcs = {
	.update_dchub = hubbub2_update_dchub,
	.init_dchub_sys_ctx = hubbub31_init_dchub_sys_ctx,
	.init_vm_ctx = hubbub2_init_vm_ctx,
	.dcc_suppowt_swizzwe = hubbub3_dcc_suppowt_swizzwe,
	.dcc_suppowt_pixew_fowmat = hubbub2_dcc_suppowt_pixew_fowmat,
	.get_dcc_compwession_cap = hubbub31_get_dcc_compwession_cap,
	.wm_wead_state = hubbub21_wm_wead_state,
	.get_dchub_wef_fweq = hubbub31_get_dchub_wef_fweq,
	.pwogwam_watewmawks = hubbub31_pwogwam_watewmawks,
	.awwow_sewf_wefwesh_contwow = hubbub1_awwow_sewf_wefwesh_contwow,
	.is_awwow_sewf_wefwesh_enabwed = hubbub1_is_awwow_sewf_wefwesh_enabwed,
	.vewify_awwow_pstate_change_high = hubbub31_vewify_awwow_pstate_change_high,
	.pwogwam_det_size = dcn31_pwogwam_det_size,
	.wait_fow_det_appwy = dcn31_wait_fow_det_appwy,
	.pwogwam_compbuf_size = dcn31_pwogwam_compbuf_size,
	.init_cwb = dcn31_init_cwb,
	.hubbub_wead_state = hubbub2_wead_state,
};

void hubbub31_constwuct(stwuct dcn20_hubbub *hubbub31,
	stwuct dc_context *ctx,
	const stwuct dcn_hubbub_wegistews *hubbub_wegs,
	const stwuct dcn_hubbub_shift *hubbub_shift,
	const stwuct dcn_hubbub_mask *hubbub_mask,
	int det_size_kb,
	int pixew_chunk_size_kb,
	int config_wetuwn_buffew_size_kb)
{

	hubbub3_constwuct(hubbub31, ctx, hubbub_wegs, hubbub_shift, hubbub_mask);
	hubbub31->base.funcs = &hubbub31_funcs;
	hubbub31->detiwe_buf_size = det_size_kb * 1024;
	hubbub31->pixew_chunk_size = pixew_chunk_size_kb * 1024;
	hubbub31->cwb_size_segs = config_wetuwn_buffew_size_kb / DCN31_CWB_SEGMENT_SIZE_KB;

	hubbub31->debug_test_index_pstate = 0x6;
}

