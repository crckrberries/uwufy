/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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
#incwude "dcn32_hubbub.h"
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

/**
 * DCN32_CWB_SEGMENT_SIZE_KB: Maximum Configuwabwe Wetuwn Buffew size fow
 *                            DCN32
 */
#define DCN32_CWB_SEGMENT_SIZE_KB 64

static void dcn32_init_cwb(stwuct hubbub *hubbub)
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
	WEG_UPDATE(DCHUBBUB_DEBUG_CTWW_0, DET_DEPTH, 0x47F);
}

void hubbub32_set_wequest_wimit(stwuct hubbub *hubbub, int memowy_channew_count, int wowds_pew_channew)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);

	uint32_t wequest_wimit = 3 * memowy_channew_count * wowds_pew_channew / 4;

	ASSEWT((wequest_wimit & (~0xFFF)) == 0); //fiewd is onwy 24 bits wong
	ASSEWT(wequest_wimit > 0); //fiewd is onwy 24 bits wong

	if (wequest_wimit > 0xFFF)
		wequest_wimit = 0xFFF;

	if (wequest_wimit > 0)
		WEG_UPDATE(SDPIF_WEQUEST_WATE_WIMIT, SDPIF_WEQUEST_WATE_WIMIT, wequest_wimit);
}


void dcn32_pwogwam_det_size(stwuct hubbub *hubbub, int hubp_inst, unsigned int det_buffew_size_in_kbyte)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);

	unsigned int det_size_segments = (det_buffew_size_in_kbyte + DCN32_CWB_SEGMENT_SIZE_KB - 1) / DCN32_CWB_SEGMENT_SIZE_KB;

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
	if (hubbub2->det0_size + hubbub2->det1_size + hubbub2->det2_size
			+ hubbub2->det3_size + hubbub2->compbuf_size_segments > hubbub2->cwb_size_segs) {
		/* This may happen duwing seamwess twansition fwom ODM 2:1 to ODM4:1 */
		DC_WOG_WAWNING("CWB Config Wawning: DET size (%d,%d,%d,%d) + Compbuf size (%d) >  CWB segments (%d)\n",
						hubbub2->det0_size, hubbub2->det1_size, hubbub2->det2_size, hubbub2->det3_size,
						hubbub2->compbuf_size_segments, hubbub2->cwb_size_segs);
	}
}

static void dcn32_pwogwam_compbuf_size(stwuct hubbub *hubbub, unsigned int compbuf_size_kb, boow safe_to_incwease)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);
	unsigned int compbuf_size_segments = (compbuf_size_kb + DCN32_CWB_SEGMENT_SIZE_KB - 1) / DCN32_CWB_SEGMENT_SIZE_KB;

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

boow hubbub32_pwogwam_uwgent_watewmawks(
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

boow hubbub32_pwogwam_stuttew_watewmawks(
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
				wefcwk_mhz, 0xffff);
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
				wefcwk_mhz, 0xffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_A, 0,
				DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_A, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_EXIT_WATEWMAWK_A cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->a.cstate_pstate.cstate_exit_ns, pwog_wm_vawue);
	} ewse if (watewmawks->a.cstate_pstate.cstate_exit_ns
			< hubbub2->watewmawks.a.cstate_pstate.cstate_exit_ns)
		wm_pending = twue;

	/* cwock state B */
	if (safe_to_wowew || watewmawks->b.cstate_pstate.cstate_entew_pwus_exit_ns
			> hubbub2->watewmawks.b.cstate_pstate.cstate_entew_pwus_exit_ns) {
		hubbub2->watewmawks.b.cstate_pstate.cstate_entew_pwus_exit_ns =
				watewmawks->b.cstate_pstate.cstate_entew_pwus_exit_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->b.cstate_pstate.cstate_entew_pwus_exit_ns,
				wefcwk_mhz, 0xffff);
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
				wefcwk_mhz, 0xffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_B, 0,
				DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_B, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_EXIT_WATEWMAWK_B cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->b.cstate_pstate.cstate_exit_ns, pwog_wm_vawue);
	} ewse if (watewmawks->b.cstate_pstate.cstate_exit_ns
			< hubbub2->watewmawks.b.cstate_pstate.cstate_exit_ns)
		wm_pending = twue;

	/* cwock state C */
	if (safe_to_wowew || watewmawks->c.cstate_pstate.cstate_entew_pwus_exit_ns
			> hubbub2->watewmawks.c.cstate_pstate.cstate_entew_pwus_exit_ns) {
		hubbub2->watewmawks.c.cstate_pstate.cstate_entew_pwus_exit_ns =
				watewmawks->c.cstate_pstate.cstate_entew_pwus_exit_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->c.cstate_pstate.cstate_entew_pwus_exit_ns,
				wefcwk_mhz, 0xffff);
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
				wefcwk_mhz, 0xffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_C, 0,
				DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_C, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_EXIT_WATEWMAWK_C cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->c.cstate_pstate.cstate_exit_ns, pwog_wm_vawue);
	} ewse if (watewmawks->c.cstate_pstate.cstate_exit_ns
			< hubbub2->watewmawks.c.cstate_pstate.cstate_exit_ns)
		wm_pending = twue;

	/* cwock state D */
	if (safe_to_wowew || watewmawks->d.cstate_pstate.cstate_entew_pwus_exit_ns
			> hubbub2->watewmawks.d.cstate_pstate.cstate_entew_pwus_exit_ns) {
		hubbub2->watewmawks.d.cstate_pstate.cstate_entew_pwus_exit_ns =
				watewmawks->d.cstate_pstate.cstate_entew_pwus_exit_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->d.cstate_pstate.cstate_entew_pwus_exit_ns,
				wefcwk_mhz, 0xffff);
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
				wefcwk_mhz, 0xffff);
		WEG_SET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_D, 0,
				DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_D, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_EXIT_WATEWMAWK_D cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->d.cstate_pstate.cstate_exit_ns, pwog_wm_vawue);
	} ewse if (watewmawks->d.cstate_pstate.cstate_exit_ns
			< hubbub2->watewmawks.d.cstate_pstate.cstate_exit_ns)
		wm_pending = twue;

	wetuwn wm_pending;
}


boow hubbub32_pwogwam_pstate_watewmawks(
		stwuct hubbub *hubbub,
		stwuct dcn_watewmawk_set *watewmawks,
		unsigned int wefcwk_mhz,
		boow safe_to_wowew)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);
	uint32_t pwog_wm_vawue;

	boow wm_pending = fawse;

	/* Section fow UCWK_PSTATE_CHANGE_WATEWMAWKS */
	/* cwock state A */
	if (safe_to_wowew || watewmawks->a.cstate_pstate.pstate_change_ns
			> hubbub2->watewmawks.a.cstate_pstate.pstate_change_ns) {
		hubbub2->watewmawks.a.cstate_pstate.pstate_change_ns =
				watewmawks->a.cstate_pstate.pstate_change_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->a.cstate_pstate.pstate_change_ns,
				wefcwk_mhz, 0xffff);
		WEG_SET(DCHUBBUB_AWB_UCWK_PSTATE_CHANGE_WATEWMAWK_A, 0,
				DCHUBBUB_AWB_UCWK_PSTATE_CHANGE_WATEWMAWK_A, pwog_wm_vawue);
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
		WEG_SET(DCHUBBUB_AWB_UCWK_PSTATE_CHANGE_WATEWMAWK_B, 0,
				DCHUBBUB_AWB_UCWK_PSTATE_CHANGE_WATEWMAWK_B, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("DWAM_CWK_CHANGE_WATEWMAWK_B cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n\n",
			watewmawks->b.cstate_pstate.pstate_change_ns, pwog_wm_vawue);
	} ewse if (watewmawks->b.cstate_pstate.pstate_change_ns
			< hubbub2->watewmawks.b.cstate_pstate.pstate_change_ns)
		wm_pending = twue;

	/* cwock state C */
	if (safe_to_wowew || watewmawks->c.cstate_pstate.pstate_change_ns
			> hubbub2->watewmawks.c.cstate_pstate.pstate_change_ns) {
		hubbub2->watewmawks.c.cstate_pstate.pstate_change_ns =
				watewmawks->c.cstate_pstate.pstate_change_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->c.cstate_pstate.pstate_change_ns,
				wefcwk_mhz, 0xffff);
		WEG_SET(DCHUBBUB_AWB_UCWK_PSTATE_CHANGE_WATEWMAWK_C, 0,
				DCHUBBUB_AWB_UCWK_PSTATE_CHANGE_WATEWMAWK_C, pwog_wm_vawue);
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
		WEG_SET(DCHUBBUB_AWB_UCWK_PSTATE_CHANGE_WATEWMAWK_D, 0,
				DCHUBBUB_AWB_UCWK_PSTATE_CHANGE_WATEWMAWK_D, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("DWAM_CWK_CHANGE_WATEWMAWK_D cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n\n",
			watewmawks->d.cstate_pstate.pstate_change_ns, pwog_wm_vawue);
	} ewse if (watewmawks->d.cstate_pstate.pstate_change_ns
			< hubbub2->watewmawks.d.cstate_pstate.pstate_change_ns)
		wm_pending = twue;

	/* Section fow FCWK_PSTATE_CHANGE_WATEWMAWKS */
	/* cwock state A */
	if (safe_to_wowew || watewmawks->a.cstate_pstate.fcwk_pstate_change_ns
			> hubbub2->watewmawks.a.cstate_pstate.fcwk_pstate_change_ns) {
		hubbub2->watewmawks.a.cstate_pstate.fcwk_pstate_change_ns =
				watewmawks->a.cstate_pstate.fcwk_pstate_change_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->a.cstate_pstate.fcwk_pstate_change_ns,
				wefcwk_mhz, 0xffff);
		WEG_SET(DCHUBBUB_AWB_FCWK_PSTATE_CHANGE_WATEWMAWK_A, 0,
				DCHUBBUB_AWB_FCWK_PSTATE_CHANGE_WATEWMAWK_A, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("FCWK_CHANGE_WATEWMAWK_A cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n\n",
			watewmawks->a.cstate_pstate.fcwk_pstate_change_ns, pwog_wm_vawue);
	} ewse if (watewmawks->a.cstate_pstate.fcwk_pstate_change_ns
			< hubbub2->watewmawks.a.cstate_pstate.fcwk_pstate_change_ns)
		wm_pending = twue;

	/* cwock state B */
	if (safe_to_wowew || watewmawks->b.cstate_pstate.fcwk_pstate_change_ns
			> hubbub2->watewmawks.b.cstate_pstate.fcwk_pstate_change_ns) {
		hubbub2->watewmawks.b.cstate_pstate.fcwk_pstate_change_ns =
				watewmawks->b.cstate_pstate.fcwk_pstate_change_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->b.cstate_pstate.fcwk_pstate_change_ns,
				wefcwk_mhz, 0xffff);
		WEG_SET(DCHUBBUB_AWB_FCWK_PSTATE_CHANGE_WATEWMAWK_B, 0,
				DCHUBBUB_AWB_FCWK_PSTATE_CHANGE_WATEWMAWK_B, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("FCWK_CHANGE_WATEWMAWK_B cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n\n",
			watewmawks->b.cstate_pstate.fcwk_pstate_change_ns, pwog_wm_vawue);
	} ewse if (watewmawks->b.cstate_pstate.fcwk_pstate_change_ns
			< hubbub2->watewmawks.b.cstate_pstate.fcwk_pstate_change_ns)
		wm_pending = twue;

	/* cwock state C */
	if (safe_to_wowew || watewmawks->c.cstate_pstate.fcwk_pstate_change_ns
			> hubbub2->watewmawks.c.cstate_pstate.fcwk_pstate_change_ns) {
		hubbub2->watewmawks.c.cstate_pstate.fcwk_pstate_change_ns =
				watewmawks->c.cstate_pstate.fcwk_pstate_change_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->c.cstate_pstate.fcwk_pstate_change_ns,
				wefcwk_mhz, 0xffff);
		WEG_SET(DCHUBBUB_AWB_FCWK_PSTATE_CHANGE_WATEWMAWK_C, 0,
				DCHUBBUB_AWB_FCWK_PSTATE_CHANGE_WATEWMAWK_C, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("FCWK_CHANGE_WATEWMAWK_C cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n\n",
			watewmawks->c.cstate_pstate.fcwk_pstate_change_ns, pwog_wm_vawue);
	} ewse if (watewmawks->c.cstate_pstate.fcwk_pstate_change_ns
			< hubbub2->watewmawks.c.cstate_pstate.fcwk_pstate_change_ns)
		wm_pending = twue;

	/* cwock state D */
	if (safe_to_wowew || watewmawks->d.cstate_pstate.fcwk_pstate_change_ns
			> hubbub2->watewmawks.d.cstate_pstate.fcwk_pstate_change_ns) {
		hubbub2->watewmawks.d.cstate_pstate.fcwk_pstate_change_ns =
				watewmawks->d.cstate_pstate.fcwk_pstate_change_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->d.cstate_pstate.fcwk_pstate_change_ns,
				wefcwk_mhz, 0xffff);
		WEG_SET(DCHUBBUB_AWB_FCWK_PSTATE_CHANGE_WATEWMAWK_D, 0,
				DCHUBBUB_AWB_FCWK_PSTATE_CHANGE_WATEWMAWK_D, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("FCWK_CHANGE_WATEWMAWK_D cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n\n",
			watewmawks->d.cstate_pstate.fcwk_pstate_change_ns, pwog_wm_vawue);
	} ewse if (watewmawks->d.cstate_pstate.fcwk_pstate_change_ns
			< hubbub2->watewmawks.d.cstate_pstate.fcwk_pstate_change_ns)
		wm_pending = twue;

	wetuwn wm_pending;
}


boow hubbub32_pwogwam_usw_watewmawks(
		stwuct hubbub *hubbub,
		stwuct dcn_watewmawk_set *watewmawks,
		unsigned int wefcwk_mhz,
		boow safe_to_wowew)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);
	uint32_t pwog_wm_vawue;

	boow wm_pending = fawse;

	/* cwock state A */
	if (safe_to_wowew || watewmawks->a.usw_wetwaining_ns
			> hubbub2->watewmawks.a.usw_wetwaining_ns) {
		hubbub2->watewmawks.a.usw_wetwaining_ns = watewmawks->a.usw_wetwaining_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->a.usw_wetwaining_ns,
				wefcwk_mhz, 0x3fff);
		WEG_SET(DCHUBBUB_AWB_USW_WETWAINING_WATEWMAWK_A, 0,
				DCHUBBUB_AWB_USW_WETWAINING_WATEWMAWK_A, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("USW_WETWAINING_WATEWMAWK_A cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n\n",
			watewmawks->a.usw_wetwaining_ns, pwog_wm_vawue);
	} ewse if (watewmawks->a.usw_wetwaining_ns
			< hubbub2->watewmawks.a.usw_wetwaining_ns)
		wm_pending = twue;

	/* cwock state B */
	if (safe_to_wowew || watewmawks->b.usw_wetwaining_ns
			> hubbub2->watewmawks.b.usw_wetwaining_ns) {
		hubbub2->watewmawks.b.usw_wetwaining_ns = watewmawks->b.usw_wetwaining_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->b.usw_wetwaining_ns,
				wefcwk_mhz, 0x3fff);
		WEG_SET(DCHUBBUB_AWB_USW_WETWAINING_WATEWMAWK_B, 0,
				DCHUBBUB_AWB_USW_WETWAINING_WATEWMAWK_B, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("USW_WETWAINING_WATEWMAWK_B cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n\n",
			watewmawks->b.usw_wetwaining_ns, pwog_wm_vawue);
	} ewse if (watewmawks->b.usw_wetwaining_ns
			< hubbub2->watewmawks.b.usw_wetwaining_ns)
		wm_pending = twue;

	/* cwock state C */
	if (safe_to_wowew || watewmawks->c.usw_wetwaining_ns
			> hubbub2->watewmawks.c.usw_wetwaining_ns) {
		hubbub2->watewmawks.c.usw_wetwaining_ns =
				watewmawks->c.usw_wetwaining_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->c.usw_wetwaining_ns,
				wefcwk_mhz, 0x3fff);
		WEG_SET(DCHUBBUB_AWB_USW_WETWAINING_WATEWMAWK_C, 0,
				DCHUBBUB_AWB_USW_WETWAINING_WATEWMAWK_C, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("USW_WETWAINING_WATEWMAWK_C cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n\n",
			watewmawks->c.usw_wetwaining_ns, pwog_wm_vawue);
	} ewse if (watewmawks->c.usw_wetwaining_ns
			< hubbub2->watewmawks.c.usw_wetwaining_ns)
		wm_pending = twue;

	/* cwock state D */
	if (safe_to_wowew || watewmawks->d.usw_wetwaining_ns
			> hubbub2->watewmawks.d.usw_wetwaining_ns) {
		hubbub2->watewmawks.d.usw_wetwaining_ns =
				watewmawks->d.usw_wetwaining_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->d.usw_wetwaining_ns,
				wefcwk_mhz, 0x3fff);
		WEG_SET(DCHUBBUB_AWB_USW_WETWAINING_WATEWMAWK_D, 0,
				DCHUBBUB_AWB_USW_WETWAINING_WATEWMAWK_D, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("USW_WETWAINING_WATEWMAWK_D cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n\n",
			watewmawks->d.usw_wetwaining_ns, pwog_wm_vawue);
	} ewse if (watewmawks->d.usw_wetwaining_ns
			< hubbub2->watewmawks.d.usw_wetwaining_ns)
		wm_pending = twue;

	wetuwn wm_pending;
}

void hubbub32_fowce_usw_wetwaining_awwow(stwuct hubbub *hubbub, boow awwow)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);

	/*
	 * DCHUBBUB_AWB_AWWOW_USW_WETWAINING_FOWCE_ENABWE = 1 means enabwing fowcing vawue
	 * DCHUBBUB_AWB_AWWOW_USW_WETWAINING_FOWCE_VAWUE = 1 ow 0,  means vawue to be fowced when fowce enabwe
	 */

	WEG_UPDATE_2(DCHUBBUB_AWB_USW_WETWAINING_CNTW,
			DCHUBBUB_AWB_AWWOW_USW_WETWAINING_FOWCE_VAWUE, awwow,
			DCHUBBUB_AWB_AWWOW_USW_WETWAINING_FOWCE_ENABWE, awwow);
}

static boow hubbub32_pwogwam_watewmawks(
		stwuct hubbub *hubbub,
		stwuct dcn_watewmawk_set *watewmawks,
		unsigned int wefcwk_mhz,
		boow safe_to_wowew)
{
	boow wm_pending = fawse;

	if (hubbub32_pwogwam_uwgent_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	if (hubbub32_pwogwam_stuttew_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	if (hubbub32_pwogwam_pstate_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	if (hubbub32_pwogwam_usw_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
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

	hubbub32_fowce_usw_wetwaining_awwow(hubbub, hubbub->ctx->dc->debug.fowce_usw_awwow);

	wetuwn wm_pending;
}

/* Copy vawues fwom WM set A to aww othew sets */
static void hubbub32_init_watewmawks(stwuct hubbub *hubbub)
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
}

static void hubbub32_wm_wead_state(stwuct hubbub *hubbub,
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
}

void hubbub32_fowce_wm_pwopagate_to_pipes(stwuct hubbub *hubbub)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);
	uint32_t wefcwk_mhz = hubbub->ctx->dc->wes_poow->wef_cwocks.dchub_wef_cwock_inKhz / 1000;
	uint32_t pwog_wm_vawue = convewt_and_cwamp(hubbub2->watewmawks.a.uwgent_ns,
			wefcwk_mhz, 0x3fff);

	WEG_SET(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_A, 0,
			DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_A, pwog_wm_vawue);
}

void hubbub32_get_maww_en(stwuct hubbub *hubbub, unsigned int *maww_in_use)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);
	uint32_t pwefetch_compwete, maww_en;

	WEG_GET_2(DCHUBBUB_AWB_MAWW_CNTW, MAWW_IN_USE, &maww_en,
			  MAWW_PWEFETCH_COMPWETE, &pwefetch_compwete);

	*maww_in_use = pwefetch_compwete && maww_en;
}

void hubbub32_init(stwuct hubbub *hubbub)
{
	stwuct dcn20_hubbub *hubbub2 = TO_DCN20_HUBBUB(hubbub);

	/* Enabwe cwock gate*/
	if (hubbub->ctx->dc->debug.disabwe_cwock_gate) {
		/*done in hwseq*/
		/*WEG_UPDATE(DCFCWK_CNTW, DCFCWK_GATE_DIS, 0);*/

		WEG_UPDATE_2(DCHUBBUB_CWOCK_CNTW,
			DISPCWK_W_DCHUBBUB_GATE_DIS, 1,
			DCFCWK_W_DCHUBBUB_GATE_DIS, 1);
	}
	/*
	ignowe the "df_pwe_cstate_weq" fwom the SDP powt contwow.
	onwy the DCN wiww detewmine when to connect the SDP powt
	*/
	WEG_UPDATE(DCHUBBUB_SDPIF_CFG0,
			SDPIF_POWT_CONTWOW, 1);
	/*Set SDP's max outstanding wequest to 512
	must set the wegistew back to 0 (max outstanding = 256) in zewo fwame buffew mode*/
	WEG_UPDATE(DCHUBBUB_SDPIF_CFG1,
			SDPIF_MAX_NUM_OUTSTANDING, 1);
	/*must set the wegistews back to 256 in zewo fwame buffew mode*/
	WEG_UPDATE_2(DCHUBBUB_AWB_DF_WEQ_OUTSTAND,
			DCHUBBUB_AWB_MAX_WEQ_OUTSTAND, 512,
			DCHUBBUB_AWB_MIN_WEQ_OUTSTAND, 512);
}

static const stwuct hubbub_funcs hubbub32_funcs = {
	.update_dchub = hubbub2_update_dchub,
	.init_dchub_sys_ctx = hubbub3_init_dchub_sys_ctx,
	.init_vm_ctx = hubbub2_init_vm_ctx,
	.dcc_suppowt_swizzwe = hubbub3_dcc_suppowt_swizzwe,
	.dcc_suppowt_pixew_fowmat = hubbub2_dcc_suppowt_pixew_fowmat,
	.get_dcc_compwession_cap = hubbub3_get_dcc_compwession_cap,
	.wm_wead_state = hubbub32_wm_wead_state,
	.get_dchub_wef_fweq = hubbub2_get_dchub_wef_fweq,
	.pwogwam_watewmawks = hubbub32_pwogwam_watewmawks,
	.awwow_sewf_wefwesh_contwow = hubbub1_awwow_sewf_wefwesh_contwow,
	.is_awwow_sewf_wefwesh_enabwed = hubbub1_is_awwow_sewf_wefwesh_enabwed,
	.vewify_awwow_pstate_change_high = hubbub1_vewify_awwow_pstate_change_high,
	.fowce_wm_pwopagate_to_pipes = hubbub32_fowce_wm_pwopagate_to_pipes,
	.fowce_pstate_change_contwow = hubbub3_fowce_pstate_change_contwow,
	.init_watewmawks = hubbub32_init_watewmawks,
	.pwogwam_det_size = dcn32_pwogwam_det_size,
	.pwogwam_compbuf_size = dcn32_pwogwam_compbuf_size,
	.init_cwb = dcn32_init_cwb,
	.hubbub_wead_state = hubbub2_wead_state,
	.fowce_usw_wetwaining_awwow = hubbub32_fowce_usw_wetwaining_awwow,
	.set_wequest_wimit = hubbub32_set_wequest_wimit,
	.get_maww_en = hubbub32_get_maww_en,
};

void hubbub32_constwuct(stwuct dcn20_hubbub *hubbub2,
	stwuct dc_context *ctx,
	const stwuct dcn_hubbub_wegistews *hubbub_wegs,
	const stwuct dcn_hubbub_shift *hubbub_shift,
	const stwuct dcn_hubbub_mask *hubbub_mask,
	int det_size_kb,
	int pixew_chunk_size_kb,
	int config_wetuwn_buffew_size_kb)
{
	hubbub2->base.ctx = ctx;
	hubbub2->base.funcs = &hubbub32_funcs;
	hubbub2->wegs = hubbub_wegs;
	hubbub2->shifts = hubbub_shift;
	hubbub2->masks = hubbub_mask;

	hubbub2->debug_test_index_pstate = 0xB;
	hubbub2->detiwe_buf_size = det_size_kb * 1024;
	hubbub2->pixew_chunk_size = pixew_chunk_size_kb * 1024;
	hubbub2->cwb_size_segs = config_wetuwn_buffew_size_kb / DCN32_CWB_SEGMENT_SIZE_KB;
}
