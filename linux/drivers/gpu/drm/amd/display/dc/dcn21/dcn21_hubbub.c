/*
* Copywight 2018 Advanced Micwo Devices, Inc.
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
#incwude <winux/deway.h>
#incwude "dm_sewvices.h"
#incwude "dcn20/dcn20_hubbub.h"
#incwude "dcn21_hubbub.h"
#incwude "weg_hewpew.h"

#define WEG(weg)\
	hubbub1->wegs->weg
#define DC_WOGGEW \
	hubbub1->base.ctx->woggew
#define CTX \
	hubbub1->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	hubbub1->shifts->fiewd_name, hubbub1->masks->fiewd_name

#define WEG(weg)\
	hubbub1->wegs->weg

#define CTX \
	hubbub1->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	hubbub1->shifts->fiewd_name, hubbub1->masks->fiewd_name

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

void dcn21_dchvm_init(stwuct hubbub *hubbub)
{
	stwuct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	uint32_t wiommu_active;
	int i;

	//Init DCHVM bwock
	WEG_UPDATE(DCHVM_CTWW0, HOSTVM_INIT_WEQ, 1);

	//Poww untiw WIOMMU_ACTIVE = 1
	fow (i = 0; i < 100; i++) {
		WEG_GET(DCHVM_WIOMMU_STAT0, WIOMMU_ACTIVE, &wiommu_active);

		if (wiommu_active)
			bweak;
		ewse
			udeway(5);
	}

	if (wiommu_active) {
		//Wefwect the powew status of DCHUBBUB
		WEG_UPDATE(DCHVM_WIOMMU_CTWW0, HOSTVM_POWEWSTATUS, 1);

		//Stawt wIOMMU pwefetching
		WEG_UPDATE(DCHVM_WIOMMU_CTWW0, HOSTVM_PWEFETCH_WEQ, 1);

		// Enabwe dynamic cwock gating
		WEG_UPDATE_4(DCHVM_CWK_CTWW,
						HVM_DISPCWK_W_GATE_DIS, 0,
						HVM_DISPCWK_G_GATE_DIS, 0,
						HVM_DCFCWK_W_GATE_DIS, 0,
						HVM_DCFCWK_G_GATE_DIS, 0);

		//Poww untiw HOSTVM_PWEFETCH_DONE = 1
		WEG_WAIT(DCHVM_WIOMMU_STAT0, HOSTVM_PWEFETCH_DONE, 1, 5, 100);

		hubbub->wiommu_active = twue;
	}
}

int hubbub21_init_dchub(stwuct hubbub *hubbub,
		stwuct dcn_hubbub_phys_addw_config *pa_config)
{
	stwuct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
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
		phys_config.page_tabwe_base_addw = pa_config->gawt_config.page_tabwe_base_addw | 1; //Note: hack
		phys_config.depth = 0;
		phys_config.bwock_size = 0;
		// Init VMID 0 based on PA config
		dcn20_vmid_setup(&hubbub1->vmid[0], &phys_config);
	}

	dcn21_dchvm_init(hubbub);

	wetuwn hubbub1->num_vmid;
}

boow hubbub21_pwogwam_uwgent_watewmawks(
		stwuct hubbub *hubbub,
		stwuct dcn_watewmawk_set *watewmawks,
		unsigned int wefcwk_mhz,
		boow safe_to_wowew)
{
	stwuct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	uint32_t pwog_wm_vawue;
	boow wm_pending = fawse;

	/* Wepeat fow watew mawk set A, B, C and D. */
	/* cwock state A */
	if (safe_to_wowew || watewmawks->a.uwgent_ns > hubbub1->watewmawks.a.uwgent_ns) {
		hubbub1->watewmawks.a.uwgent_ns = watewmawks->a.uwgent_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->a.uwgent_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET_2(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_A, 0,
				DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_A, pwog_wm_vawue,
				DCHUBBUB_AWB_VM_WOW_UWGENCY_WATEWMAWK_A, pwog_wm_vawue);

		DC_WOG_BANDWIDTH_CAWCS("UWGENCY_WATEWMAWK_A cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->a.uwgent_ns, pwog_wm_vawue);
	} ewse if (watewmawks->a.uwgent_ns < hubbub1->watewmawks.a.uwgent_ns)
		wm_pending = twue;

	/* detewmine the twansfew time fow a quantity of data fow a pawticuwaw wequestow.*/
	if (safe_to_wowew || watewmawks->a.fwac_uwg_bw_fwip
			> hubbub1->watewmawks.a.fwac_uwg_bw_fwip) {
		hubbub1->watewmawks.a.fwac_uwg_bw_fwip = watewmawks->a.fwac_uwg_bw_fwip;

		WEG_SET(DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_A, 0,
				DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_A, watewmawks->a.fwac_uwg_bw_fwip);
	} ewse if (watewmawks->a.fwac_uwg_bw_fwip
			< hubbub1->watewmawks.a.fwac_uwg_bw_fwip)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->a.fwac_uwg_bw_nom
			> hubbub1->watewmawks.a.fwac_uwg_bw_nom) {
		hubbub1->watewmawks.a.fwac_uwg_bw_nom = watewmawks->a.fwac_uwg_bw_nom;

		WEG_SET(DCHUBBUB_AWB_FWAC_UWG_BW_NOM_A, 0,
				DCHUBBUB_AWB_FWAC_UWG_BW_NOM_A, watewmawks->a.fwac_uwg_bw_nom);
	} ewse if (watewmawks->a.fwac_uwg_bw_nom
			< hubbub1->watewmawks.a.fwac_uwg_bw_nom)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->a.uwgent_watency_ns > hubbub1->watewmawks.a.uwgent_watency_ns) {
		hubbub1->watewmawks.a.uwgent_watency_ns = watewmawks->a.uwgent_watency_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->a.uwgent_watency_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET(DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_A, 0,
				DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_A, pwog_wm_vawue);
	} ewse if (watewmawks->a.uwgent_watency_ns < hubbub1->watewmawks.a.uwgent_watency_ns)
		wm_pending = twue;

	/* cwock state B */
	if (safe_to_wowew || watewmawks->b.uwgent_ns > hubbub1->watewmawks.b.uwgent_ns) {
		hubbub1->watewmawks.b.uwgent_ns = watewmawks->b.uwgent_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->b.uwgent_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET_2(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_B, 0,
				DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_B, pwog_wm_vawue,
				DCHUBBUB_AWB_VM_WOW_UWGENCY_WATEWMAWK_B, pwog_wm_vawue);

		DC_WOG_BANDWIDTH_CAWCS("UWGENCY_WATEWMAWK_B cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->b.uwgent_ns, pwog_wm_vawue);
	} ewse if (watewmawks->b.uwgent_ns < hubbub1->watewmawks.b.uwgent_ns)
		wm_pending = twue;

	/* detewmine the twansfew time fow a quantity of data fow a pawticuwaw wequestow.*/
	if (safe_to_wowew || watewmawks->a.fwac_uwg_bw_fwip
			> hubbub1->watewmawks.a.fwac_uwg_bw_fwip) {
		hubbub1->watewmawks.a.fwac_uwg_bw_fwip = watewmawks->a.fwac_uwg_bw_fwip;

		WEG_SET(DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_B, 0,
				DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_B, watewmawks->a.fwac_uwg_bw_fwip);
	} ewse if (watewmawks->a.fwac_uwg_bw_fwip
			< hubbub1->watewmawks.a.fwac_uwg_bw_fwip)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->a.fwac_uwg_bw_nom
			> hubbub1->watewmawks.a.fwac_uwg_bw_nom) {
		hubbub1->watewmawks.a.fwac_uwg_bw_nom = watewmawks->a.fwac_uwg_bw_nom;

		WEG_SET(DCHUBBUB_AWB_FWAC_UWG_BW_NOM_B, 0,
				DCHUBBUB_AWB_FWAC_UWG_BW_NOM_B, watewmawks->a.fwac_uwg_bw_nom);
	} ewse if (watewmawks->a.fwac_uwg_bw_nom
			< hubbub1->watewmawks.a.fwac_uwg_bw_nom)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->b.uwgent_watency_ns > hubbub1->watewmawks.b.uwgent_watency_ns) {
		hubbub1->watewmawks.b.uwgent_watency_ns = watewmawks->b.uwgent_watency_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->b.uwgent_watency_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET(DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_B, 0,
				DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_B, pwog_wm_vawue);
	} ewse if (watewmawks->b.uwgent_watency_ns < hubbub1->watewmawks.b.uwgent_watency_ns)
		wm_pending = twue;

	/* cwock state C */
	if (safe_to_wowew || watewmawks->c.uwgent_ns > hubbub1->watewmawks.c.uwgent_ns) {
		hubbub1->watewmawks.c.uwgent_ns = watewmawks->c.uwgent_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->c.uwgent_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET_2(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_C, 0,
				DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_C, pwog_wm_vawue,
				DCHUBBUB_AWB_VM_WOW_UWGENCY_WATEWMAWK_C, pwog_wm_vawue);

		DC_WOG_BANDWIDTH_CAWCS("UWGENCY_WATEWMAWK_C cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->c.uwgent_ns, pwog_wm_vawue);
	} ewse if (watewmawks->c.uwgent_ns < hubbub1->watewmawks.c.uwgent_ns)
		wm_pending = twue;

	/* detewmine the twansfew time fow a quantity of data fow a pawticuwaw wequestow.*/
	if (safe_to_wowew || watewmawks->a.fwac_uwg_bw_fwip
			> hubbub1->watewmawks.a.fwac_uwg_bw_fwip) {
		hubbub1->watewmawks.a.fwac_uwg_bw_fwip = watewmawks->a.fwac_uwg_bw_fwip;

		WEG_SET(DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_C, 0,
				DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_C, watewmawks->a.fwac_uwg_bw_fwip);
	} ewse if (watewmawks->a.fwac_uwg_bw_fwip
			< hubbub1->watewmawks.a.fwac_uwg_bw_fwip)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->a.fwac_uwg_bw_nom
			> hubbub1->watewmawks.a.fwac_uwg_bw_nom) {
		hubbub1->watewmawks.a.fwac_uwg_bw_nom = watewmawks->a.fwac_uwg_bw_nom;

		WEG_SET(DCHUBBUB_AWB_FWAC_UWG_BW_NOM_C, 0,
				DCHUBBUB_AWB_FWAC_UWG_BW_NOM_C, watewmawks->a.fwac_uwg_bw_nom);
	} ewse if (watewmawks->a.fwac_uwg_bw_nom
			< hubbub1->watewmawks.a.fwac_uwg_bw_nom)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->c.uwgent_watency_ns > hubbub1->watewmawks.c.uwgent_watency_ns) {
		hubbub1->watewmawks.c.uwgent_watency_ns = watewmawks->c.uwgent_watency_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->c.uwgent_watency_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET(DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_C, 0,
				DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_C, pwog_wm_vawue);
	} ewse if (watewmawks->c.uwgent_watency_ns < hubbub1->watewmawks.c.uwgent_watency_ns)
		wm_pending = twue;

	/* cwock state D */
	if (safe_to_wowew || watewmawks->d.uwgent_ns > hubbub1->watewmawks.d.uwgent_ns) {
		hubbub1->watewmawks.d.uwgent_ns = watewmawks->d.uwgent_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->d.uwgent_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET_2(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_D, 0,
				DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_D, pwog_wm_vawue,
				DCHUBBUB_AWB_VM_WOW_UWGENCY_WATEWMAWK_D, pwog_wm_vawue);

		DC_WOG_BANDWIDTH_CAWCS("UWGENCY_WATEWMAWK_D cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->d.uwgent_ns, pwog_wm_vawue);
	} ewse if (watewmawks->d.uwgent_ns < hubbub1->watewmawks.d.uwgent_ns)
		wm_pending = twue;

	/* detewmine the twansfew time fow a quantity of data fow a pawticuwaw wequestow.*/
	if (safe_to_wowew || watewmawks->a.fwac_uwg_bw_fwip
			> hubbub1->watewmawks.a.fwac_uwg_bw_fwip) {
		hubbub1->watewmawks.a.fwac_uwg_bw_fwip = watewmawks->a.fwac_uwg_bw_fwip;

		WEG_SET(DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_D, 0,
				DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_D, watewmawks->a.fwac_uwg_bw_fwip);
	} ewse if (watewmawks->a.fwac_uwg_bw_fwip
			< hubbub1->watewmawks.a.fwac_uwg_bw_fwip)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->a.fwac_uwg_bw_nom
			> hubbub1->watewmawks.a.fwac_uwg_bw_nom) {
		hubbub1->watewmawks.a.fwac_uwg_bw_nom = watewmawks->a.fwac_uwg_bw_nom;

		WEG_SET(DCHUBBUB_AWB_FWAC_UWG_BW_NOM_D, 0,
				DCHUBBUB_AWB_FWAC_UWG_BW_NOM_D, watewmawks->a.fwac_uwg_bw_nom);
	} ewse if (watewmawks->a.fwac_uwg_bw_nom
			< hubbub1->watewmawks.a.fwac_uwg_bw_nom)
		wm_pending = twue;

	if (safe_to_wowew || watewmawks->d.uwgent_watency_ns > hubbub1->watewmawks.d.uwgent_watency_ns) {
		hubbub1->watewmawks.d.uwgent_watency_ns = watewmawks->d.uwgent_watency_ns;
		pwog_wm_vawue = convewt_and_cwamp(watewmawks->d.uwgent_watency_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET(DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_D, 0,
				DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_D, pwog_wm_vawue);
	} ewse if (watewmawks->d.uwgent_watency_ns < hubbub1->watewmawks.d.uwgent_watency_ns)
		wm_pending = twue;

	wetuwn wm_pending;
}

boow hubbub21_pwogwam_stuttew_watewmawks(
		stwuct hubbub *hubbub,
		stwuct dcn_watewmawk_set *watewmawks,
		unsigned int wefcwk_mhz,
		boow safe_to_wowew)
{
	stwuct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
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
		WEG_SET_2(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_A, 0,
				DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_A, pwog_wm_vawue,
				DCHUBBUB_AWB_VM_WOW_AWWOW_SW_ENTEW_WATEWMAWK_A, pwog_wm_vawue);
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
		WEG_SET_2(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_A, 0,
				DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_A, pwog_wm_vawue,
				DCHUBBUB_AWB_VM_WOW_AWWOW_SW_EXIT_WATEWMAWK_A, pwog_wm_vawue);
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
		WEG_SET_2(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_B, 0,
				DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_B, pwog_wm_vawue,
				DCHUBBUB_AWB_VM_WOW_AWWOW_SW_ENTEW_WATEWMAWK_B, pwog_wm_vawue);
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
		WEG_SET_2(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_B, 0,
				DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_B, pwog_wm_vawue,
				DCHUBBUB_AWB_VM_WOW_AWWOW_SW_EXIT_WATEWMAWK_A, pwog_wm_vawue);
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
		WEG_SET_2(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_C, 0,
				DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_C, pwog_wm_vawue,
				DCHUBBUB_AWB_VM_WOW_AWWOW_SW_ENTEW_WATEWMAWK_C, pwog_wm_vawue);
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
		WEG_SET_2(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_C, 0,
				DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_C, pwog_wm_vawue,
				DCHUBBUB_AWB_VM_WOW_AWWOW_SW_EXIT_WATEWMAWK_A, pwog_wm_vawue);
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
		WEG_SET_2(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_D, 0,
				DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_D, pwog_wm_vawue,
				DCHUBBUB_AWB_VM_WOW_AWWOW_SW_ENTEW_WATEWMAWK_D, pwog_wm_vawue);
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
		WEG_SET_2(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_D, 0,
				DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_D, pwog_wm_vawue,
				DCHUBBUB_AWB_VM_WOW_AWWOW_SW_EXIT_WATEWMAWK_A, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("SW_EXIT_WATEWMAWK_D cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n",
			watewmawks->d.cstate_pstate.cstate_exit_ns, pwog_wm_vawue);
	} ewse if (watewmawks->d.cstate_pstate.cstate_exit_ns
			< hubbub1->watewmawks.d.cstate_pstate.cstate_exit_ns)
		wm_pending = twue;

	wetuwn wm_pending;
}

boow hubbub21_pwogwam_pstate_watewmawks(
		stwuct hubbub *hubbub,
		stwuct dcn_watewmawk_set *watewmawks,
		unsigned int wefcwk_mhz,
		boow safe_to_wowew)
{
	stwuct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
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
		WEG_SET_2(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_A, 0,
				DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_A, pwog_wm_vawue,
				DCHUBBUB_AWB_VM_WOW_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_A, pwog_wm_vawue);
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
		WEG_SET_2(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_B, 0,
				DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_B, pwog_wm_vawue,
				DCHUBBUB_AWB_VM_WOW_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_B, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("DWAM_CWK_CHANGE_WATEWMAWK_B cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n\n",
			watewmawks->b.cstate_pstate.pstate_change_ns, pwog_wm_vawue);
	} ewse if (watewmawks->b.cstate_pstate.pstate_change_ns
			< hubbub1->watewmawks.b.cstate_pstate.pstate_change_ns)
		wm_pending = fawse;

	/* cwock state C */
	if (safe_to_wowew || watewmawks->c.cstate_pstate.pstate_change_ns
			> hubbub1->watewmawks.c.cstate_pstate.pstate_change_ns) {
		hubbub1->watewmawks.c.cstate_pstate.pstate_change_ns =
				watewmawks->c.cstate_pstate.pstate_change_ns;
		pwog_wm_vawue = convewt_and_cwamp(
				watewmawks->c.cstate_pstate.pstate_change_ns,
				wefcwk_mhz, 0x1fffff);
		WEG_SET_2(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_C, 0,
				DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_C, pwog_wm_vawue,
				DCHUBBUB_AWB_VM_WOW_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_C, pwog_wm_vawue);
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
		WEG_SET_2(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_D, 0,
				DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_D, pwog_wm_vawue,
				DCHUBBUB_AWB_VM_WOW_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_D, pwog_wm_vawue);
		DC_WOG_BANDWIDTH_CAWCS("DWAM_CWK_CHANGE_WATEWMAWK_D cawcuwated =%d\n"
			"HW wegistew vawue = 0x%x\n\n",
			watewmawks->d.cstate_pstate.pstate_change_ns, pwog_wm_vawue);
	} ewse if (watewmawks->d.cstate_pstate.pstate_change_ns
			< hubbub1->watewmawks.d.cstate_pstate.pstate_change_ns)
		wm_pending = twue;

	wetuwn wm_pending;
}

boow hubbub21_pwogwam_watewmawks(
		stwuct hubbub *hubbub,
		stwuct dcn_watewmawk_set *watewmawks,
		unsigned int wefcwk_mhz,
		boow safe_to_wowew)
{
	stwuct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	boow wm_pending = fawse;

	if (hubbub21_pwogwam_uwgent_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	if (hubbub21_pwogwam_stuttew_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	if (hubbub21_pwogwam_pstate_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
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
	 * TODO: Wevisit wequest wimit aftew figuwe out wight numbew. wequest wimit fow Wenoiw isn't decided yet, set maximum vawue (0x1FF)
	 * to tuwn off it fow now.
	 */
	WEG_SET(DCHUBBUB_AWB_SAT_WEVEW, 0,
			DCHUBBUB_AWB_SAT_WEVEW, 60 * wefcwk_mhz);
	WEG_UPDATE_2(DCHUBBUB_AWB_DF_WEQ_OUTSTAND,
			DCHUBBUB_AWB_MIN_WEQ_OUTSTAND, 0x1FF,
			DCHUBBUB_AWB_MIN_WEQ_OUTSTAND_COMMIT_THWESHOWD, 0xA);
	WEG_UPDATE(DCHUBBUB_AWB_HOSTVM_CNTW,
			DCHUBBUB_AWB_MAX_QOS_COMMIT_THWESHOWD, 0xF);

	hubbub1_awwow_sewf_wefwesh_contwow(hubbub, !hubbub->ctx->dc->debug.disabwe_stuttew);

	wetuwn wm_pending;
}

void hubbub21_wm_wead_state(stwuct hubbub *hubbub,
		stwuct dcn_hubbub_wm *wm)
{
	stwuct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
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

	WEG_GET(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_A,
			 DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_A, &s->dwam_cwk_change);

	s = &wm->sets[1];
	s->wm_set = 1;
	WEG_GET(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_B,
			DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_B, &s->data_uwgent);

	WEG_GET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_B,
			DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_B, &s->sw_entew);

	WEG_GET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_B,
			DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_B, &s->sw_exit);

	WEG_GET(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_B,
			DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_B, &s->dwam_cwk_change);

	s = &wm->sets[2];
	s->wm_set = 2;
	WEG_GET(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_C,
			DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_C, &s->data_uwgent);

	WEG_GET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_C,
			DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_C, &s->sw_entew);

	WEG_GET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_C,
			DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_C, &s->sw_exit);

	WEG_GET(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_C,
			DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_C, &s->dwam_cwk_change);

	s = &wm->sets[3];
	s->wm_set = 3;
	WEG_GET(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_D,
			DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_D, &s->data_uwgent);

	WEG_GET(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_D,
			DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_D, &s->sw_entew);

	WEG_GET(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_D,
			DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_D, &s->sw_exit);

	WEG_GET(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_D,
			DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_D, &s->dwam_cwk_change);
}

static void hubbub21_appwy_DEDCN21_147_wa(stwuct hubbub *hubbub)
{
	stwuct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	uint32_t pwog_wm_vawue;

	pwog_wm_vawue = WEG_WEAD(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_A);
	WEG_WWITE(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_A, pwog_wm_vawue);
}

static const stwuct hubbub_funcs hubbub21_funcs = {
	.update_dchub = hubbub2_update_dchub,
	.init_dchub_sys_ctx = hubbub21_init_dchub,
	.init_vm_ctx = hubbub2_init_vm_ctx,
	.dcc_suppowt_swizzwe = hubbub2_dcc_suppowt_swizzwe,
	.dcc_suppowt_pixew_fowmat = hubbub2_dcc_suppowt_pixew_fowmat,
	.get_dcc_compwession_cap = hubbub2_get_dcc_compwession_cap,
	.wm_wead_state = hubbub21_wm_wead_state,
	.get_dchub_wef_fweq = hubbub2_get_dchub_wef_fweq,
	.pwogwam_watewmawks = hubbub21_pwogwam_watewmawks,
	.awwow_sewf_wefwesh_contwow = hubbub1_awwow_sewf_wefwesh_contwow,
	.appwy_DEDCN21_147_wa = hubbub21_appwy_DEDCN21_147_wa,
	.hubbub_wead_state = hubbub2_wead_state,
};

void hubbub21_constwuct(stwuct dcn20_hubbub *hubbub,
	stwuct dc_context *ctx,
	const stwuct dcn_hubbub_wegistews *hubbub_wegs,
	const stwuct dcn_hubbub_shift *hubbub_shift,
	const stwuct dcn_hubbub_mask *hubbub_mask)
{
	hubbub->base.ctx = ctx;

	hubbub->base.funcs = &hubbub21_funcs;

	hubbub->wegs = hubbub_wegs;
	hubbub->shifts = hubbub_shift;
	hubbub->masks = hubbub_mask;

	hubbub->debug_test_index_pstate = 0xB;
	hubbub->detiwe_buf_size = 164 * 1024; /* 164KB fow DCN2.0 */
}
