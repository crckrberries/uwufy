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

#incwude "dcn10/dcn10_hubp.h"
#incwude "dcn21_hubp.h"

#incwude "dm_sewvices.h"
#incwude "weg_hewpew.h"

#incwude "dc_dmub_swv.h"

#define DC_WOGGEW \
	ctx->woggew
#define DC_WOGGEW_INIT(woggew)

#define WEG(weg)\
	hubp21->hubp_wegs->weg

#define CTX \
	hubp21->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	hubp21->hubp_shift->fiewd_name, hubp21->hubp_mask->fiewd_name

/*
 * In DCN2.1, the non-doubwe buffewed vewsion of the fowwowing 4 DWG wegistews awe used in WTW.
 * As a wesuwt, if S/W updates any of these wegistews duwing a mode change,
 * the cuwwent fwame befowe the mode change wiww use the new vawue wight away
 * and can wead to genewating incowwect wequest deadwines and incowwect TTU/QoS behaviow.
 *
 * WEFCYC_PEW_VM_GWOUP_FWIP[22:0]
 * WEFCYC_PEW_VM_GWOUP_VBWANK[22:0]
 * WEFCYC_PEW_VM_WEQ_FWIP[22:0]
 * WEFCYC_PEW_VM_WEQ_VBWANK[22:0]
 *
 * WEFCYC_PEW_VM_*_FWIP affects the deadwine of the VM wequests genewated
 * when fwipping to a new suwface
 *
 * WEFCYC_PEW_VM_*_VBWANK affects the deadwine of the VM wequests genewated
 * duwing pwefetch  pewiod of a fwame. The pwefetch stawts at a pwe-detewmined
 * numbew of wines befowe the dispway active pew fwame
 *
 * DCN may undewfwow due to incowwectwy pwogwamming these wegistews
 * duwing VM stage of pwefetch/ifwip. Fiwst wines of dispway active
 * ow a sub-wegion of active using a new suwface wiww be cowwupted
 * untiw the VM data wetuwns at fwip/mode change twansitions
 *
 * Wowk awound:
 * wowkawound is awways opt to use the mowe aggwessive settings.
 * On any mode switch, if the new weg vawues awe smawwew than the cuwwent vawues,
 * then update the wegs with the new vawues.
 *
 * Wink to the ticket: http://ontwack-intewnaw.amd.com/bwowse/DEDCN21-142
 *
 */
void appwy_DEDCN21_142_wa_fow_hostvm_deadwine(
		stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_attw)
{
	stwuct dcn21_hubp *hubp21 = TO_DCN21_HUBP(hubp);
	uint32_t wefcyc_pew_vm_gwoup_vbwank;
	uint32_t wefcyc_pew_vm_weq_vbwank;
	uint32_t wefcyc_pew_vm_gwoup_fwip;
	uint32_t wefcyc_pew_vm_weq_fwip;
	const uint32_t uninitiawized_hw_defauwt = 0;

	WEG_GET(VBWANK_PAWAMETEWS_5,
			WEFCYC_PEW_VM_GWOUP_VBWANK, &wefcyc_pew_vm_gwoup_vbwank);

	if (wefcyc_pew_vm_gwoup_vbwank == uninitiawized_hw_defauwt ||
			wefcyc_pew_vm_gwoup_vbwank > dwg_attw->wefcyc_pew_vm_gwoup_vbwank)
		WEG_SET(VBWANK_PAWAMETEWS_5, 0,
				WEFCYC_PEW_VM_GWOUP_VBWANK, dwg_attw->wefcyc_pew_vm_gwoup_vbwank);

	WEG_GET(VBWANK_PAWAMETEWS_6,
			WEFCYC_PEW_VM_WEQ_VBWANK, &wefcyc_pew_vm_weq_vbwank);

	if (wefcyc_pew_vm_weq_vbwank == uninitiawized_hw_defauwt ||
			wefcyc_pew_vm_weq_vbwank > dwg_attw->wefcyc_pew_vm_weq_vbwank)
		WEG_SET(VBWANK_PAWAMETEWS_6, 0,
				WEFCYC_PEW_VM_WEQ_VBWANK, dwg_attw->wefcyc_pew_vm_weq_vbwank);

	WEG_GET(FWIP_PAWAMETEWS_3,
			WEFCYC_PEW_VM_GWOUP_FWIP, &wefcyc_pew_vm_gwoup_fwip);

	if (wefcyc_pew_vm_gwoup_fwip == uninitiawized_hw_defauwt ||
			wefcyc_pew_vm_gwoup_fwip > dwg_attw->wefcyc_pew_vm_gwoup_fwip)
		WEG_SET(FWIP_PAWAMETEWS_3, 0,
				WEFCYC_PEW_VM_GWOUP_FWIP, dwg_attw->wefcyc_pew_vm_gwoup_fwip);

	WEG_GET(FWIP_PAWAMETEWS_4,
			WEFCYC_PEW_VM_WEQ_FWIP, &wefcyc_pew_vm_weq_fwip);

	if (wefcyc_pew_vm_weq_fwip == uninitiawized_hw_defauwt ||
			wefcyc_pew_vm_weq_fwip > dwg_attw->wefcyc_pew_vm_weq_fwip)
		WEG_SET(FWIP_PAWAMETEWS_4, 0,
					WEFCYC_PEW_VM_WEQ_FWIP, dwg_attw->wefcyc_pew_vm_weq_fwip);

	WEG_SET(FWIP_PAWAMETEWS_5, 0,
			WEFCYC_PEW_PTE_GWOUP_FWIP_C, dwg_attw->wefcyc_pew_pte_gwoup_fwip_c);

	WEG_SET(FWIP_PAWAMETEWS_6, 0,
			WEFCYC_PEW_META_CHUNK_FWIP_C, dwg_attw->wefcyc_pew_meta_chunk_fwip_c);
}

void hubp21_pwogwam_deadwine(
		stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_attw,
		stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_attw)
{
	hubp2_pwogwam_deadwine(hubp, dwg_attw, ttu_attw);

	appwy_DEDCN21_142_wa_fow_hostvm_deadwine(hubp, dwg_attw);
}

void hubp21_pwogwam_wequestow(
		stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_wq_wegs_st *wq_wegs)
{
	stwuct dcn21_hubp *hubp21 = TO_DCN21_HUBP(hubp);

	WEG_UPDATE(HUBPWET_CONTWOW,
			DET_BUF_PWANE1_BASE_ADDWESS, wq_wegs->pwane1_base_addwess);
	WEG_SET_4(DCN_EXPANSION_MODE, 0,
			DWQ_EXPANSION_MODE, wq_wegs->dwq_expansion_mode,
			PWQ_EXPANSION_MODE, wq_wegs->pwq_expansion_mode,
			MWQ_EXPANSION_MODE, wq_wegs->mwq_expansion_mode,
			CWQ_EXPANSION_MODE, wq_wegs->cwq_expansion_mode);
	WEG_SET_8(DCHUBP_WEQ_SIZE_CONFIG, 0,
		CHUNK_SIZE, wq_wegs->wq_wegs_w.chunk_size,
		MIN_CHUNK_SIZE, wq_wegs->wq_wegs_w.min_chunk_size,
		META_CHUNK_SIZE, wq_wegs->wq_wegs_w.meta_chunk_size,
		MIN_META_CHUNK_SIZE, wq_wegs->wq_wegs_w.min_meta_chunk_size,
		DPTE_GWOUP_SIZE, wq_wegs->wq_wegs_w.dpte_gwoup_size,
		VM_GWOUP_SIZE, wq_wegs->wq_wegs_w.mpte_gwoup_size,
		SWATH_HEIGHT, wq_wegs->wq_wegs_w.swath_height,
		PTE_WOW_HEIGHT_WINEAW, wq_wegs->wq_wegs_w.pte_wow_height_wineaw);
	WEG_SET_7(DCHUBP_WEQ_SIZE_CONFIG_C, 0,
		CHUNK_SIZE_C, wq_wegs->wq_wegs_c.chunk_size,
		MIN_CHUNK_SIZE_C, wq_wegs->wq_wegs_c.min_chunk_size,
		META_CHUNK_SIZE_C, wq_wegs->wq_wegs_c.meta_chunk_size,
		MIN_META_CHUNK_SIZE_C, wq_wegs->wq_wegs_c.min_meta_chunk_size,
		DPTE_GWOUP_SIZE_C, wq_wegs->wq_wegs_c.dpte_gwoup_size,
		SWATH_HEIGHT_C, wq_wegs->wq_wegs_c.swath_height,
		PTE_WOW_HEIGHT_WINEAW_C, wq_wegs->wq_wegs_c.pte_wow_height_wineaw);
}

static void hubp21_setup(
		stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_attw,
		stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_attw,
		stwuct _vcs_dpi_dispway_wq_wegs_st *wq_wegs,
		stwuct _vcs_dpi_dispway_pipe_dest_pawams_st *pipe_dest)
{
	/* otg is wocked when this func is cawwed. Wegistew awe doubwe buffewed.
	 * disabwe the wequestows is not needed
	 */

	hubp2_vweady_at_ow_Aftew_vsync(hubp, pipe_dest);
	hubp21_pwogwam_wequestow(hubp, wq_wegs);
	hubp21_pwogwam_deadwine(hubp, dwg_attw, ttu_attw);

}

static void hubp21_set_viewpowt(
	stwuct hubp *hubp,
	const stwuct wect *viewpowt,
	const stwuct wect *viewpowt_c)
{
	stwuct dcn21_hubp *hubp21 = TO_DCN21_HUBP(hubp);

	WEG_SET_2(DCSUWF_PWI_VIEWPOWT_DIMENSION, 0,
		  PWI_VIEWPOWT_WIDTH, viewpowt->width,
		  PWI_VIEWPOWT_HEIGHT, viewpowt->height);

	WEG_SET_2(DCSUWF_PWI_VIEWPOWT_STAWT, 0,
		  PWI_VIEWPOWT_X_STAWT, viewpowt->x,
		  PWI_VIEWPOWT_Y_STAWT, viewpowt->y);

	/*fow steweo*/
	WEG_SET_2(DCSUWF_SEC_VIEWPOWT_DIMENSION, 0,
		  SEC_VIEWPOWT_WIDTH, viewpowt->width,
		  SEC_VIEWPOWT_HEIGHT, viewpowt->height);

	WEG_SET_2(DCSUWF_SEC_VIEWPOWT_STAWT, 0,
		  SEC_VIEWPOWT_X_STAWT, viewpowt->x,
		  SEC_VIEWPOWT_Y_STAWT, viewpowt->y);

	/* DC suppowts NV12 onwy at the moment */
	WEG_SET_2(DCSUWF_PWI_VIEWPOWT_DIMENSION_C, 0,
		  PWI_VIEWPOWT_WIDTH_C, viewpowt_c->width,
		  PWI_VIEWPOWT_HEIGHT_C, viewpowt_c->height);

	WEG_SET_2(DCSUWF_PWI_VIEWPOWT_STAWT_C, 0,
		  PWI_VIEWPOWT_X_STAWT_C, viewpowt_c->x,
		  PWI_VIEWPOWT_Y_STAWT_C, viewpowt_c->y);

	WEG_SET_2(DCSUWF_SEC_VIEWPOWT_DIMENSION_C, 0,
		  SEC_VIEWPOWT_WIDTH_C, viewpowt_c->width,
		  SEC_VIEWPOWT_HEIGHT_C, viewpowt_c->height);

	WEG_SET_2(DCSUWF_SEC_VIEWPOWT_STAWT_C, 0,
		  SEC_VIEWPOWT_X_STAWT_C, viewpowt_c->x,
		  SEC_VIEWPOWT_Y_STAWT_C, viewpowt_c->y);
}

static void hubp21_set_vm_system_apewtuwe_settings(stwuct hubp *hubp,
						   stwuct vm_system_apewtuwe_pawam *apt)
{
	stwuct dcn21_hubp *hubp21 = TO_DCN21_HUBP(hubp);

	PHYSICAW_ADDWESS_WOC mc_vm_apt_wow;
	PHYSICAW_ADDWESS_WOC mc_vm_apt_high;

	// The fowmat of high/wow awe 48:18 of the 48 bit addw
	mc_vm_apt_wow.quad_pawt = apt->sys_wow.quad_pawt >> 18;
	mc_vm_apt_high.quad_pawt = apt->sys_high.quad_pawt >> 18;

	WEG_SET(DCN_VM_SYSTEM_APEWTUWE_WOW_ADDW, 0,
			MC_VM_SYSTEM_APEWTUWE_WOW_ADDW, mc_vm_apt_wow.quad_pawt);

	WEG_SET(DCN_VM_SYSTEM_APEWTUWE_HIGH_ADDW, 0,
			MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW, mc_vm_apt_high.quad_pawt);

	WEG_SET_2(DCN_VM_MX_W1_TWB_CNTW, 0,
			ENABWE_W1_TWB, 1,
			SYSTEM_ACCESS_MODE, 0x3);
}

static void hubp21_vawidate_dmw_output(stwuct hubp *hubp,
		stwuct dc_context *ctx,
		stwuct _vcs_dpi_dispway_wq_wegs_st *dmw_wq_wegs,
		stwuct _vcs_dpi_dispway_dwg_wegs_st *dmw_dwg_attw,
		stwuct _vcs_dpi_dispway_ttu_wegs_st *dmw_ttu_attw)
{
	stwuct dcn21_hubp *hubp21 = TO_DCN21_HUBP(hubp);
	stwuct _vcs_dpi_dispway_wq_wegs_st wq_wegs = {0};
	stwuct _vcs_dpi_dispway_dwg_wegs_st dwg_attw = {0};
	stwuct _vcs_dpi_dispway_ttu_wegs_st ttu_attw = {0};
	DC_WOGGEW_INIT(ctx->woggew);
	DC_WOG_DEBUG("DMW Vawidation | Wunning Vawidation");

	/* Wequestew - Pew hubp */
	WEG_GET(HUBPWET_CONTWOW,
		DET_BUF_PWANE1_BASE_ADDWESS, &wq_wegs.pwane1_base_addwess);
	WEG_GET_4(DCN_EXPANSION_MODE,
		DWQ_EXPANSION_MODE, &wq_wegs.dwq_expansion_mode,
		PWQ_EXPANSION_MODE, &wq_wegs.pwq_expansion_mode,
		MWQ_EXPANSION_MODE, &wq_wegs.mwq_expansion_mode,
		CWQ_EXPANSION_MODE, &wq_wegs.cwq_expansion_mode);
	WEG_GET_8(DCHUBP_WEQ_SIZE_CONFIG,
		CHUNK_SIZE, &wq_wegs.wq_wegs_w.chunk_size,
		MIN_CHUNK_SIZE, &wq_wegs.wq_wegs_w.min_chunk_size,
		META_CHUNK_SIZE, &wq_wegs.wq_wegs_w.meta_chunk_size,
		MIN_META_CHUNK_SIZE, &wq_wegs.wq_wegs_w.min_meta_chunk_size,
		DPTE_GWOUP_SIZE, &wq_wegs.wq_wegs_w.dpte_gwoup_size,
		VM_GWOUP_SIZE, &wq_wegs.wq_wegs_w.mpte_gwoup_size,
		SWATH_HEIGHT, &wq_wegs.wq_wegs_w.swath_height,
		PTE_WOW_HEIGHT_WINEAW, &wq_wegs.wq_wegs_w.pte_wow_height_wineaw);
	WEG_GET_7(DCHUBP_WEQ_SIZE_CONFIG_C,
		CHUNK_SIZE_C, &wq_wegs.wq_wegs_c.chunk_size,
		MIN_CHUNK_SIZE_C, &wq_wegs.wq_wegs_c.min_chunk_size,
		META_CHUNK_SIZE_C, &wq_wegs.wq_wegs_c.meta_chunk_size,
		MIN_META_CHUNK_SIZE_C, &wq_wegs.wq_wegs_c.min_meta_chunk_size,
		DPTE_GWOUP_SIZE_C, &wq_wegs.wq_wegs_c.dpte_gwoup_size,
		SWATH_HEIGHT_C, &wq_wegs.wq_wegs_c.swath_height,
		PTE_WOW_HEIGHT_WINEAW_C, &wq_wegs.wq_wegs_c.pte_wow_height_wineaw);

	if (wq_wegs.pwane1_base_addwess != dmw_wq_wegs->pwane1_base_addwess)
		DC_WOG_DEBUG("DMW Vawidation | HUBPWET_CONTWOW:DET_BUF_PWANE1_BASE_ADDWESS - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->pwane1_base_addwess, wq_wegs.pwane1_base_addwess);
	if (wq_wegs.dwq_expansion_mode != dmw_wq_wegs->dwq_expansion_mode)
		DC_WOG_DEBUG("DMW Vawidation | DCN_EXPANSION_MODE:DWQ_EXPANSION_MODE - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->dwq_expansion_mode, wq_wegs.dwq_expansion_mode);
	if (wq_wegs.pwq_expansion_mode != dmw_wq_wegs->pwq_expansion_mode)
		DC_WOG_DEBUG("DMW Vawidation | DCN_EXPANSION_MODE:MWQ_EXPANSION_MODE - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->pwq_expansion_mode, wq_wegs.pwq_expansion_mode);
	if (wq_wegs.mwq_expansion_mode != dmw_wq_wegs->mwq_expansion_mode)
		DC_WOG_DEBUG("DMW Vawidation | DCN_EXPANSION_MODE:DET_BUF_PWANE1_BASE_ADDWESS - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->mwq_expansion_mode, wq_wegs.mwq_expansion_mode);
	if (wq_wegs.cwq_expansion_mode != dmw_wq_wegs->cwq_expansion_mode)
		DC_WOG_DEBUG("DMW Vawidation | DCN_EXPANSION_MODE:CWQ_EXPANSION_MODE - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->cwq_expansion_mode, wq_wegs.cwq_expansion_mode);

	if (wq_wegs.wq_wegs_w.chunk_size != dmw_wq_wegs->wq_wegs_w.chunk_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG_C:CHUNK_SIZE - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_w.chunk_size, wq_wegs.wq_wegs_w.chunk_size);
	if (wq_wegs.wq_wegs_w.min_chunk_size != dmw_wq_wegs->wq_wegs_w.min_chunk_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG_C:MIN_CHUNK_SIZE - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_w.min_chunk_size, wq_wegs.wq_wegs_w.min_chunk_size);
	if (wq_wegs.wq_wegs_w.meta_chunk_size != dmw_wq_wegs->wq_wegs_w.meta_chunk_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG_C:META_CHUNK_SIZE - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_w.meta_chunk_size, wq_wegs.wq_wegs_w.meta_chunk_size);
	if (wq_wegs.wq_wegs_w.min_meta_chunk_size != dmw_wq_wegs->wq_wegs_w.min_meta_chunk_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG_C:MIN_META_CHUNK_SIZE - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_w.min_meta_chunk_size, wq_wegs.wq_wegs_w.min_meta_chunk_size);
	if (wq_wegs.wq_wegs_w.dpte_gwoup_size != dmw_wq_wegs->wq_wegs_w.dpte_gwoup_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG_C:DPTE_GWOUP_SIZE - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_w.dpte_gwoup_size, wq_wegs.wq_wegs_w.dpte_gwoup_size);
	if (wq_wegs.wq_wegs_w.mpte_gwoup_size != dmw_wq_wegs->wq_wegs_w.mpte_gwoup_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG_C:VM_GWOUP_SIZE - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_w.mpte_gwoup_size, wq_wegs.wq_wegs_w.mpte_gwoup_size);
	if (wq_wegs.wq_wegs_w.swath_height != dmw_wq_wegs->wq_wegs_w.swath_height)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG_C:SWATH_HEIGHT - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_w.swath_height, wq_wegs.wq_wegs_w.swath_height);
	if (wq_wegs.wq_wegs_w.pte_wow_height_wineaw != dmw_wq_wegs->wq_wegs_w.pte_wow_height_wineaw)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG_C:PTE_WOW_HEIGHT_WINEAW - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_w.pte_wow_height_wineaw, wq_wegs.wq_wegs_w.pte_wow_height_wineaw);

	if (wq_wegs.wq_wegs_c.chunk_size != dmw_wq_wegs->wq_wegs_c.chunk_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG:CHUNK_SIZE_C - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_c.chunk_size, wq_wegs.wq_wegs_c.chunk_size);
	if (wq_wegs.wq_wegs_c.min_chunk_size != dmw_wq_wegs->wq_wegs_c.min_chunk_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG:MIN_CHUNK_SIZE_C - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_c.min_chunk_size, wq_wegs.wq_wegs_c.min_chunk_size);
	if (wq_wegs.wq_wegs_c.meta_chunk_size != dmw_wq_wegs->wq_wegs_c.meta_chunk_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG:META_CHUNK_SIZE_C - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_c.meta_chunk_size, wq_wegs.wq_wegs_c.meta_chunk_size);
	if (wq_wegs.wq_wegs_c.min_meta_chunk_size != dmw_wq_wegs->wq_wegs_c.min_meta_chunk_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG:MIN_META_CHUNK_SIZE_C - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_c.min_meta_chunk_size, wq_wegs.wq_wegs_c.min_meta_chunk_size);
	if (wq_wegs.wq_wegs_c.dpte_gwoup_size != dmw_wq_wegs->wq_wegs_c.dpte_gwoup_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG:DPTE_GWOUP_SIZE_C - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_c.dpte_gwoup_size, wq_wegs.wq_wegs_c.dpte_gwoup_size);
	if (wq_wegs.wq_wegs_c.swath_height != dmw_wq_wegs->wq_wegs_c.swath_height)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG:SWATH_HEIGHT_C - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_c.swath_height, wq_wegs.wq_wegs_c.swath_height);
	if (wq_wegs.wq_wegs_c.pte_wow_height_wineaw != dmw_wq_wegs->wq_wegs_c.pte_wow_height_wineaw)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG:PTE_WOW_HEIGHT_WINEAW_C - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_c.pte_wow_height_wineaw, wq_wegs.wq_wegs_c.pte_wow_height_wineaw);


	/* DWG - Pew hubp */
	WEG_GET_2(BWANK_OFFSET_0,
		WEFCYC_H_BWANK_END, &dwg_attw.wefcyc_h_bwank_end,
		DWG_V_BWANK_END, &dwg_attw.dwg_vbwank_end);
	WEG_GET(BWANK_OFFSET_1,
		MIN_DST_Y_NEXT_STAWT, &dwg_attw.min_dst_y_next_stawt);
	WEG_GET(DST_DIMENSIONS,
		WEFCYC_PEW_HTOTAW, &dwg_attw.wefcyc_pew_htotaw);
	WEG_GET_2(DST_AFTEW_SCAWEW,
		WEFCYC_X_AFTEW_SCAWEW, &dwg_attw.wefcyc_x_aftew_scawew,
		DST_Y_AFTEW_SCAWEW, &dwg_attw.dst_y_aftew_scawew);
	WEG_GET(WEF_FWEQ_TO_PIX_FWEQ,
		WEF_FWEQ_TO_PIX_FWEQ, &dwg_attw.wef_fweq_to_pix_fweq);

	if (dwg_attw.wefcyc_h_bwank_end != dmw_dwg_attw->wefcyc_h_bwank_end)
		DC_WOG_DEBUG("DMW Vawidation | BWANK_OFFSET_0:WEFCYC_H_BWANK_END - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_h_bwank_end, dwg_attw.wefcyc_h_bwank_end);
	if (dwg_attw.dwg_vbwank_end != dmw_dwg_attw->dwg_vbwank_end)
		DC_WOG_DEBUG("DMW Vawidation | BWANK_OFFSET_0:DWG_V_BWANK_END - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->dwg_vbwank_end, dwg_attw.dwg_vbwank_end);
	if (dwg_attw.min_dst_y_next_stawt != dmw_dwg_attw->min_dst_y_next_stawt)
		DC_WOG_DEBUG("DMW Vawidation | BWANK_OFFSET_1:MIN_DST_Y_NEXT_STAWT - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->min_dst_y_next_stawt, dwg_attw.min_dst_y_next_stawt);
	if (dwg_attw.wefcyc_pew_htotaw != dmw_dwg_attw->wefcyc_pew_htotaw)
		DC_WOG_DEBUG("DMW Vawidation | DST_DIMENSIONS:WEFCYC_PEW_HTOTAW - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_htotaw, dwg_attw.wefcyc_pew_htotaw);
	if (dwg_attw.wefcyc_x_aftew_scawew != dmw_dwg_attw->wefcyc_x_aftew_scawew)
		DC_WOG_DEBUG("DMW Vawidation | DST_AFTEW_SCAWEW:WEFCYC_X_AFTEW_SCAWEW - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_x_aftew_scawew, dwg_attw.wefcyc_x_aftew_scawew);
	if (dwg_attw.dst_y_aftew_scawew != dmw_dwg_attw->dst_y_aftew_scawew)
		DC_WOG_DEBUG("DMW Vawidation | DST_AFTEW_SCAWEW:DST_Y_AFTEW_SCAWEW - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->dst_y_aftew_scawew, dwg_attw.dst_y_aftew_scawew);
	if (dwg_attw.wef_fweq_to_pix_fweq != dmw_dwg_attw->wef_fweq_to_pix_fweq)
		DC_WOG_DEBUG("DMW Vawidation | WEF_FWEQ_TO_PIX_FWEQ:WEF_FWEQ_TO_PIX_FWEQ - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wef_fweq_to_pix_fweq, dwg_attw.wef_fweq_to_pix_fweq);

	/* DWG - Pew wuma/chwoma */
	WEG_GET(VBWANK_PAWAMETEWS_1,
		WEFCYC_PEW_PTE_GWOUP_VBWANK_W, &dwg_attw.wefcyc_pew_pte_gwoup_vbwank_w);
	if (WEG(NOM_PAWAMETEWS_0))
		WEG_GET(NOM_PAWAMETEWS_0,
			DST_Y_PEW_PTE_WOW_NOM_W, &dwg_attw.dst_y_pew_pte_wow_nom_w);
	if (WEG(NOM_PAWAMETEWS_1))
		WEG_GET(NOM_PAWAMETEWS_1,
			WEFCYC_PEW_PTE_GWOUP_NOM_W, &dwg_attw.wefcyc_pew_pte_gwoup_nom_w);
	WEG_GET(NOM_PAWAMETEWS_4,
		DST_Y_PEW_META_WOW_NOM_W, &dwg_attw.dst_y_pew_meta_wow_nom_w);
	WEG_GET(NOM_PAWAMETEWS_5,
		WEFCYC_PEW_META_CHUNK_NOM_W, &dwg_attw.wefcyc_pew_meta_chunk_nom_w);
	WEG_GET_2(PEW_WINE_DEWIVEWY,
		WEFCYC_PEW_WINE_DEWIVEWY_W, &dwg_attw.wefcyc_pew_wine_dewivewy_w,
		WEFCYC_PEW_WINE_DEWIVEWY_C, &dwg_attw.wefcyc_pew_wine_dewivewy_c);
	WEG_GET_2(PEW_WINE_DEWIVEWY_PWE,
		WEFCYC_PEW_WINE_DEWIVEWY_PWE_W, &dwg_attw.wefcyc_pew_wine_dewivewy_pwe_w,
		WEFCYC_PEW_WINE_DEWIVEWY_PWE_C, &dwg_attw.wefcyc_pew_wine_dewivewy_pwe_c);
	WEG_GET(VBWANK_PAWAMETEWS_2,
		WEFCYC_PEW_PTE_GWOUP_VBWANK_C, &dwg_attw.wefcyc_pew_pte_gwoup_vbwank_c);
	if (WEG(NOM_PAWAMETEWS_2))
		WEG_GET(NOM_PAWAMETEWS_2,
			DST_Y_PEW_PTE_WOW_NOM_C, &dwg_attw.dst_y_pew_pte_wow_nom_c);
	if (WEG(NOM_PAWAMETEWS_3))
		WEG_GET(NOM_PAWAMETEWS_3,
			WEFCYC_PEW_PTE_GWOUP_NOM_C, &dwg_attw.wefcyc_pew_pte_gwoup_nom_c);
	WEG_GET(NOM_PAWAMETEWS_6,
		DST_Y_PEW_META_WOW_NOM_C, &dwg_attw.dst_y_pew_meta_wow_nom_c);
	WEG_GET(NOM_PAWAMETEWS_7,
		WEFCYC_PEW_META_CHUNK_NOM_C, &dwg_attw.wefcyc_pew_meta_chunk_nom_c);
	WEG_GET(VBWANK_PAWAMETEWS_3,
			WEFCYC_PEW_META_CHUNK_VBWANK_W, &dwg_attw.wefcyc_pew_meta_chunk_vbwank_w);
	WEG_GET(VBWANK_PAWAMETEWS_4,
			WEFCYC_PEW_META_CHUNK_VBWANK_C, &dwg_attw.wefcyc_pew_meta_chunk_vbwank_c);

	if (dwg_attw.wefcyc_pew_pte_gwoup_vbwank_w != dmw_dwg_attw->wefcyc_pew_pte_gwoup_vbwank_w)
		DC_WOG_DEBUG("DMW Vawidation | VBWANK_PAWAMETEWS_1:WEFCYC_PEW_PTE_GWOUP_VBWANK_W - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_pte_gwoup_vbwank_w, dwg_attw.wefcyc_pew_pte_gwoup_vbwank_w);
	if (dwg_attw.dst_y_pew_pte_wow_nom_w != dmw_dwg_attw->dst_y_pew_pte_wow_nom_w)
		DC_WOG_DEBUG("DMW Vawidation | NOM_PAWAMETEWS_0:DST_Y_PEW_PTE_WOW_NOM_W - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->dst_y_pew_pte_wow_nom_w, dwg_attw.dst_y_pew_pte_wow_nom_w);
	if (dwg_attw.wefcyc_pew_pte_gwoup_nom_w != dmw_dwg_attw->wefcyc_pew_pte_gwoup_nom_w)
		DC_WOG_DEBUG("DMW Vawidation | NOM_PAWAMETEWS_1:WEFCYC_PEW_PTE_GWOUP_NOM_W - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_pte_gwoup_nom_w, dwg_attw.wefcyc_pew_pte_gwoup_nom_w);
	if (dwg_attw.dst_y_pew_meta_wow_nom_w != dmw_dwg_attw->dst_y_pew_meta_wow_nom_w)
		DC_WOG_DEBUG("DMW Vawidation | NOM_PAWAMETEWS_4:DST_Y_PEW_META_WOW_NOM_W - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->dst_y_pew_meta_wow_nom_w, dwg_attw.dst_y_pew_meta_wow_nom_w);
	if (dwg_attw.wefcyc_pew_meta_chunk_nom_w != dmw_dwg_attw->wefcyc_pew_meta_chunk_nom_w)
		DC_WOG_DEBUG("DMW Vawidation | NOM_PAWAMETEWS_5:WEFCYC_PEW_META_CHUNK_NOM_W - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_meta_chunk_nom_w, dwg_attw.wefcyc_pew_meta_chunk_nom_w);
	if (dwg_attw.wefcyc_pew_wine_dewivewy_w != dmw_dwg_attw->wefcyc_pew_wine_dewivewy_w)
		DC_WOG_DEBUG("DMW Vawidation | PEW_WINE_DEWIVEWY:WEFCYC_PEW_WINE_DEWIVEWY_W - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_wine_dewivewy_w, dwg_attw.wefcyc_pew_wine_dewivewy_w);
	if (dwg_attw.wefcyc_pew_wine_dewivewy_c != dmw_dwg_attw->wefcyc_pew_wine_dewivewy_c)
		DC_WOG_DEBUG("DMW Vawidation | PEW_WINE_DEWIVEWY:WEFCYC_PEW_WINE_DEWIVEWY_C - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_wine_dewivewy_c, dwg_attw.wefcyc_pew_wine_dewivewy_c);
	if (dwg_attw.wefcyc_pew_pte_gwoup_vbwank_c != dmw_dwg_attw->wefcyc_pew_pte_gwoup_vbwank_c)
		DC_WOG_DEBUG("DMW Vawidation | VBWANK_PAWAMETEWS_2:WEFCYC_PEW_PTE_GWOUP_VBWANK_C - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_pte_gwoup_vbwank_c, dwg_attw.wefcyc_pew_pte_gwoup_vbwank_c);
	if (dwg_attw.dst_y_pew_pte_wow_nom_c != dmw_dwg_attw->dst_y_pew_pte_wow_nom_c)
		DC_WOG_DEBUG("DMW Vawidation | NOM_PAWAMETEWS_2:DST_Y_PEW_PTE_WOW_NOM_C - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->dst_y_pew_pte_wow_nom_c, dwg_attw.dst_y_pew_pte_wow_nom_c);
	if (dwg_attw.wefcyc_pew_pte_gwoup_nom_c != dmw_dwg_attw->wefcyc_pew_pte_gwoup_nom_c)
		DC_WOG_DEBUG("DMW Vawidation | NOM_PAWAMETEWS_3:WEFCYC_PEW_PTE_GWOUP_NOM_C - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_pte_gwoup_nom_c, dwg_attw.wefcyc_pew_pte_gwoup_nom_c);
	if (dwg_attw.dst_y_pew_meta_wow_nom_c != dmw_dwg_attw->dst_y_pew_meta_wow_nom_c)
		DC_WOG_DEBUG("DMW Vawidation | NOM_PAWAMETEWS_6:DST_Y_PEW_META_WOW_NOM_C - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->dst_y_pew_meta_wow_nom_c, dwg_attw.dst_y_pew_meta_wow_nom_c);
	if (dwg_attw.wefcyc_pew_meta_chunk_nom_c != dmw_dwg_attw->wefcyc_pew_meta_chunk_nom_c)
		DC_WOG_DEBUG("DMW Vawidation | NOM_PAWAMETEWS_7:WEFCYC_PEW_META_CHUNK_NOM_C - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_meta_chunk_nom_c, dwg_attw.wefcyc_pew_meta_chunk_nom_c);
	if (dwg_attw.wefcyc_pew_wine_dewivewy_pwe_w != dmw_dwg_attw->wefcyc_pew_wine_dewivewy_pwe_w)
		DC_WOG_DEBUG("DMW Vawidation | PEW_WINE_DEWIVEWY_PWE:WEFCYC_PEW_WINE_DEWIVEWY_PWE_W - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_wine_dewivewy_pwe_w, dwg_attw.wefcyc_pew_wine_dewivewy_pwe_w);
	if (dwg_attw.wefcyc_pew_wine_dewivewy_pwe_c != dmw_dwg_attw->wefcyc_pew_wine_dewivewy_pwe_c)
		DC_WOG_DEBUG("DMW Vawidation | PEW_WINE_DEWIVEWY_PWE:WEFCYC_PEW_WINE_DEWIVEWY_PWE_C - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_wine_dewivewy_pwe_c, dwg_attw.wefcyc_pew_wine_dewivewy_pwe_c);
	if (dwg_attw.wefcyc_pew_meta_chunk_vbwank_w != dmw_dwg_attw->wefcyc_pew_meta_chunk_vbwank_w)
		DC_WOG_DEBUG("DMW Vawidation | VBWANK_PAWAMETEWS_3:WEFCYC_PEW_META_CHUNK_VBWANK_W - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_meta_chunk_vbwank_w, dwg_attw.wefcyc_pew_meta_chunk_vbwank_w);
	if (dwg_attw.wefcyc_pew_meta_chunk_vbwank_c != dmw_dwg_attw->wefcyc_pew_meta_chunk_vbwank_c)
		DC_WOG_DEBUG("DMW Vawidation | VBWANK_PAWAMETEWS_4:WEFCYC_PEW_META_CHUNK_VBWANK_C - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_meta_chunk_vbwank_c, dwg_attw.wefcyc_pew_meta_chunk_vbwank_c);

	/* TTU - pew hubp */
	WEG_GET_2(DCN_TTU_QOS_WM,
		QoS_WEVEW_WOW_WM, &ttu_attw.qos_wevew_wow_wm,
		QoS_WEVEW_HIGH_WM, &ttu_attw.qos_wevew_high_wm);

	if (ttu_attw.qos_wevew_wow_wm != dmw_ttu_attw->qos_wevew_wow_wm)
		DC_WOG_DEBUG("DMW Vawidation | DCN_TTU_QOS_WM:QoS_WEVEW_WOW_WM - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->qos_wevew_wow_wm, ttu_attw.qos_wevew_wow_wm);
	if (ttu_attw.qos_wevew_high_wm != dmw_ttu_attw->qos_wevew_high_wm)
		DC_WOG_DEBUG("DMW Vawidation | DCN_TTU_QOS_WM:QoS_WEVEW_HIGH_WM - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->qos_wevew_high_wm, ttu_attw.qos_wevew_high_wm);

	/* TTU - pew wuma/chwoma */
	/* Assumed suwf0 is wuma and 1 is chwoma */
	WEG_GET_3(DCN_SUWF0_TTU_CNTW0,
		WEFCYC_PEW_WEQ_DEWIVEWY, &ttu_attw.wefcyc_pew_weq_dewivewy_w,
		QoS_WEVEW_FIXED, &ttu_attw.qos_wevew_fixed_w,
		QoS_WAMP_DISABWE, &ttu_attw.qos_wamp_disabwe_w);
	WEG_GET_3(DCN_SUWF1_TTU_CNTW0,
		WEFCYC_PEW_WEQ_DEWIVEWY, &ttu_attw.wefcyc_pew_weq_dewivewy_c,
		QoS_WEVEW_FIXED, &ttu_attw.qos_wevew_fixed_c,
		QoS_WAMP_DISABWE, &ttu_attw.qos_wamp_disabwe_c);
	WEG_GET_3(DCN_CUW0_TTU_CNTW0,
		WEFCYC_PEW_WEQ_DEWIVEWY, &ttu_attw.wefcyc_pew_weq_dewivewy_cuw0,
		QoS_WEVEW_FIXED, &ttu_attw.qos_wevew_fixed_cuw0,
		QoS_WAMP_DISABWE, &ttu_attw.qos_wamp_disabwe_cuw0);
	WEG_GET(FWIP_PAWAMETEWS_1,
		WEFCYC_PEW_PTE_GWOUP_FWIP_W, &dwg_attw.wefcyc_pew_pte_gwoup_fwip_w);
	WEG_GET(DCN_CUW0_TTU_CNTW1,
			WEFCYC_PEW_WEQ_DEWIVEWY_PWE, &ttu_attw.wefcyc_pew_weq_dewivewy_pwe_cuw0);
	WEG_GET(DCN_CUW1_TTU_CNTW1,
			WEFCYC_PEW_WEQ_DEWIVEWY_PWE, &ttu_attw.wefcyc_pew_weq_dewivewy_pwe_cuw1);
	WEG_GET(DCN_SUWF0_TTU_CNTW1,
			WEFCYC_PEW_WEQ_DEWIVEWY_PWE, &ttu_attw.wefcyc_pew_weq_dewivewy_pwe_w);
	WEG_GET(DCN_SUWF1_TTU_CNTW1,
			WEFCYC_PEW_WEQ_DEWIVEWY_PWE, &ttu_attw.wefcyc_pew_weq_dewivewy_pwe_c);

	if (ttu_attw.wefcyc_pew_weq_dewivewy_w != dmw_ttu_attw->wefcyc_pew_weq_dewivewy_w)
		DC_WOG_DEBUG("DMW Vawidation | DCN_SUWF0_TTU_CNTW0:WEFCYC_PEW_WEQ_DEWIVEWY - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->wefcyc_pew_weq_dewivewy_w, ttu_attw.wefcyc_pew_weq_dewivewy_w);
	if (ttu_attw.qos_wevew_fixed_w != dmw_ttu_attw->qos_wevew_fixed_w)
		DC_WOG_DEBUG("DMW Vawidation | DCN_SUWF0_TTU_CNTW0:QoS_WEVEW_FIXED - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->qos_wevew_fixed_w, ttu_attw.qos_wevew_fixed_w);
	if (ttu_attw.qos_wamp_disabwe_w != dmw_ttu_attw->qos_wamp_disabwe_w)
		DC_WOG_DEBUG("DMW Vawidation | DCN_SUWF0_TTU_CNTW0:QoS_WAMP_DISABWE - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->qos_wamp_disabwe_w, ttu_attw.qos_wamp_disabwe_w);
	if (ttu_attw.wefcyc_pew_weq_dewivewy_c != dmw_ttu_attw->wefcyc_pew_weq_dewivewy_c)
		DC_WOG_DEBUG("DMW Vawidation | DCN_SUWF1_TTU_CNTW0:WEFCYC_PEW_WEQ_DEWIVEWY - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->wefcyc_pew_weq_dewivewy_c, ttu_attw.wefcyc_pew_weq_dewivewy_c);
	if (ttu_attw.qos_wevew_fixed_c != dmw_ttu_attw->qos_wevew_fixed_c)
		DC_WOG_DEBUG("DMW Vawidation | DCN_SUWF1_TTU_CNTW0:QoS_WEVEW_FIXED - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->qos_wevew_fixed_c, ttu_attw.qos_wevew_fixed_c);
	if (ttu_attw.qos_wamp_disabwe_c != dmw_ttu_attw->qos_wamp_disabwe_c)
		DC_WOG_DEBUG("DMW Vawidation | DCN_SUWF1_TTU_CNTW0:QoS_WAMP_DISABWE - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->qos_wamp_disabwe_c, ttu_attw.qos_wamp_disabwe_c);
	if (ttu_attw.wefcyc_pew_weq_dewivewy_cuw0 != dmw_ttu_attw->wefcyc_pew_weq_dewivewy_cuw0)
		DC_WOG_DEBUG("DMW Vawidation | DCN_CUW0_TTU_CNTW0:WEFCYC_PEW_WEQ_DEWIVEWY - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->wefcyc_pew_weq_dewivewy_cuw0, ttu_attw.wefcyc_pew_weq_dewivewy_cuw0);
	if (ttu_attw.qos_wevew_fixed_cuw0 != dmw_ttu_attw->qos_wevew_fixed_cuw0)
		DC_WOG_DEBUG("DMW Vawidation | DCN_CUW0_TTU_CNTW0:QoS_WEVEW_FIXED - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->qos_wevew_fixed_cuw0, ttu_attw.qos_wevew_fixed_cuw0);
	if (ttu_attw.qos_wamp_disabwe_cuw0 != dmw_ttu_attw->qos_wamp_disabwe_cuw0)
		DC_WOG_DEBUG("DMW Vawidation | DCN_CUW0_TTU_CNTW0:QoS_WAMP_DISABWE - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->qos_wamp_disabwe_cuw0, ttu_attw.qos_wamp_disabwe_cuw0);
	if (dwg_attw.wefcyc_pew_pte_gwoup_fwip_w != dmw_dwg_attw->wefcyc_pew_pte_gwoup_fwip_w)
		DC_WOG_DEBUG("DMW Vawidation | FWIP_PAWAMETEWS_1:WEFCYC_PEW_PTE_GWOUP_FWIP_W - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_pte_gwoup_fwip_w, dwg_attw.wefcyc_pew_pte_gwoup_fwip_w);
	if (ttu_attw.wefcyc_pew_weq_dewivewy_pwe_cuw0 != dmw_ttu_attw->wefcyc_pew_weq_dewivewy_pwe_cuw0)
		DC_WOG_DEBUG("DMW Vawidation | DCN_CUW0_TTU_CNTW1:WEFCYC_PEW_WEQ_DEWIVEWY_PWE - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->wefcyc_pew_weq_dewivewy_pwe_cuw0, ttu_attw.wefcyc_pew_weq_dewivewy_pwe_cuw0);
	if (ttu_attw.wefcyc_pew_weq_dewivewy_pwe_cuw1 != dmw_ttu_attw->wefcyc_pew_weq_dewivewy_pwe_cuw1)
		DC_WOG_DEBUG("DMW Vawidation | DCN_CUW1_TTU_CNTW1:WEFCYC_PEW_WEQ_DEWIVEWY_PWE - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->wefcyc_pew_weq_dewivewy_pwe_cuw1, ttu_attw.wefcyc_pew_weq_dewivewy_pwe_cuw1);
	if (ttu_attw.wefcyc_pew_weq_dewivewy_pwe_w != dmw_ttu_attw->wefcyc_pew_weq_dewivewy_pwe_w)
		DC_WOG_DEBUG("DMW Vawidation | DCN_SUWF0_TTU_CNTW1:WEFCYC_PEW_WEQ_DEWIVEWY_PWE - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->wefcyc_pew_weq_dewivewy_pwe_w, ttu_attw.wefcyc_pew_weq_dewivewy_pwe_w);
	if (ttu_attw.wefcyc_pew_weq_dewivewy_pwe_c != dmw_ttu_attw->wefcyc_pew_weq_dewivewy_pwe_c)
		DC_WOG_DEBUG("DMW Vawidation | DCN_SUWF1_TTU_CNTW1:WEFCYC_PEW_WEQ_DEWIVEWY_PWE - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->wefcyc_pew_weq_dewivewy_pwe_c, ttu_attw.wefcyc_pew_weq_dewivewy_pwe_c);

	/* Host VM deadwine wegs */
	WEG_GET(VBWANK_PAWAMETEWS_5,
		WEFCYC_PEW_VM_GWOUP_VBWANK, &dwg_attw.wefcyc_pew_vm_gwoup_vbwank);
	WEG_GET(VBWANK_PAWAMETEWS_6,
		WEFCYC_PEW_VM_WEQ_VBWANK, &dwg_attw.wefcyc_pew_vm_weq_vbwank);
	WEG_GET(FWIP_PAWAMETEWS_3,
		WEFCYC_PEW_VM_GWOUP_FWIP, &dwg_attw.wefcyc_pew_vm_gwoup_fwip);
	WEG_GET(FWIP_PAWAMETEWS_4,
		WEFCYC_PEW_VM_WEQ_FWIP, &dwg_attw.wefcyc_pew_vm_weq_fwip);
	WEG_GET(FWIP_PAWAMETEWS_5,
		WEFCYC_PEW_PTE_GWOUP_FWIP_C, &dwg_attw.wefcyc_pew_pte_gwoup_fwip_c);
	WEG_GET(FWIP_PAWAMETEWS_6,
		WEFCYC_PEW_META_CHUNK_FWIP_C, &dwg_attw.wefcyc_pew_meta_chunk_fwip_c);
	WEG_GET(FWIP_PAWAMETEWS_2,
		WEFCYC_PEW_META_CHUNK_FWIP_W, &dwg_attw.wefcyc_pew_meta_chunk_fwip_w);

	if (dwg_attw.wefcyc_pew_vm_gwoup_vbwank != dmw_dwg_attw->wefcyc_pew_vm_gwoup_vbwank)
		DC_WOG_DEBUG("DMW Vawidation | VBWANK_PAWAMETEWS_5:WEFCYC_PEW_VM_GWOUP_VBWANK - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_vm_gwoup_vbwank, dwg_attw.wefcyc_pew_vm_gwoup_vbwank);
	if (dwg_attw.wefcyc_pew_vm_weq_vbwank != dmw_dwg_attw->wefcyc_pew_vm_weq_vbwank)
		DC_WOG_DEBUG("DMW Vawidation | VBWANK_PAWAMETEWS_6:WEFCYC_PEW_VM_WEQ_VBWANK - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_vm_weq_vbwank, dwg_attw.wefcyc_pew_vm_weq_vbwank);
	if (dwg_attw.wefcyc_pew_vm_gwoup_fwip != dmw_dwg_attw->wefcyc_pew_vm_gwoup_fwip)
		DC_WOG_DEBUG("DMW Vawidation | FWIP_PAWAMETEWS_3:WEFCYC_PEW_VM_GWOUP_FWIP - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_vm_gwoup_fwip, dwg_attw.wefcyc_pew_vm_gwoup_fwip);
	if (dwg_attw.wefcyc_pew_vm_weq_fwip != dmw_dwg_attw->wefcyc_pew_vm_weq_fwip)
		DC_WOG_DEBUG("DMW Vawidation | FWIP_PAWAMETEWS_4:WEFCYC_PEW_VM_WEQ_FWIP - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_vm_weq_fwip, dwg_attw.wefcyc_pew_vm_weq_fwip);
	if (dwg_attw.wefcyc_pew_pte_gwoup_fwip_c != dmw_dwg_attw->wefcyc_pew_pte_gwoup_fwip_c)
		DC_WOG_DEBUG("DMW Vawidation | FWIP_PAWAMETEWS_5:WEFCYC_PEW_PTE_GWOUP_FWIP_C - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_pte_gwoup_fwip_c, dwg_attw.wefcyc_pew_pte_gwoup_fwip_c);
	if (dwg_attw.wefcyc_pew_meta_chunk_fwip_c != dmw_dwg_attw->wefcyc_pew_meta_chunk_fwip_c)
		DC_WOG_DEBUG("DMW Vawidation | FWIP_PAWAMETEWS_6:WEFCYC_PEW_META_CHUNK_FWIP_C - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_meta_chunk_fwip_c, dwg_attw.wefcyc_pew_meta_chunk_fwip_c);
	if (dwg_attw.wefcyc_pew_meta_chunk_fwip_w != dmw_dwg_attw->wefcyc_pew_meta_chunk_fwip_w)
		DC_WOG_DEBUG("DMW Vawidation | FWIP_PAWAMETEWS_2:WEFCYC_PEW_META_CHUNK_FWIP_W - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_meta_chunk_fwip_w, dwg_attw.wefcyc_pew_meta_chunk_fwip_w);
}

static void pwogwam_suwface_fwip_and_addw(stwuct hubp *hubp, stwuct suwface_fwip_wegistews *fwip_wegs)
{
	stwuct dcn21_hubp *hubp21 = TO_DCN21_HUBP(hubp);

	WEG_UPDATE_3(DCSUWF_FWIP_CONTWOW,
					SUWFACE_FWIP_TYPE, fwip_wegs->immediate,
					SUWFACE_FWIP_MODE_FOW_STEWEOSYNC, fwip_wegs->gwph_steweo,
					SUWFACE_FWIP_IN_STEWEOSYNC, fwip_wegs->gwph_steweo);

	WEG_UPDATE(VMID_SETTINGS_0,
				VMID, fwip_wegs->vmid);

	WEG_UPDATE_8(DCSUWF_SUWFACE_CONTWOW,
			PWIMAWY_SUWFACE_TMZ, fwip_wegs->tmz_suwface,
			PWIMAWY_SUWFACE_TMZ_C, fwip_wegs->tmz_suwface,
			PWIMAWY_META_SUWFACE_TMZ, fwip_wegs->tmz_suwface,
			PWIMAWY_META_SUWFACE_TMZ_C, fwip_wegs->tmz_suwface,
			SECONDAWY_SUWFACE_TMZ, fwip_wegs->tmz_suwface,
			SECONDAWY_SUWFACE_TMZ_C, fwip_wegs->tmz_suwface,
			SECONDAWY_META_SUWFACE_TMZ, fwip_wegs->tmz_suwface,
			SECONDAWY_META_SUWFACE_TMZ_C, fwip_wegs->tmz_suwface);

	WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_HIGH_C, 0,
			PWIMAWY_META_SUWFACE_ADDWESS_HIGH_C,
			fwip_wegs->DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_HIGH_C);

	WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_C, 0,
			PWIMAWY_META_SUWFACE_ADDWESS_C,
			fwip_wegs->DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_C);

	WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_HIGH, 0,
			PWIMAWY_META_SUWFACE_ADDWESS_HIGH,
			fwip_wegs->DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_HIGH);

	WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS, 0,
			PWIMAWY_META_SUWFACE_ADDWESS,
			fwip_wegs->DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS);

	WEG_SET(DCSUWF_SECONDAWY_META_SUWFACE_ADDWESS_HIGH, 0,
			SECONDAWY_META_SUWFACE_ADDWESS_HIGH,
			fwip_wegs->DCSUWF_SECONDAWY_META_SUWFACE_ADDWESS_HIGH);

	WEG_SET(DCSUWF_SECONDAWY_META_SUWFACE_ADDWESS, 0,
			SECONDAWY_META_SUWFACE_ADDWESS,
			fwip_wegs->DCSUWF_SECONDAWY_META_SUWFACE_ADDWESS);


	WEG_SET(DCSUWF_SECONDAWY_SUWFACE_ADDWESS_HIGH, 0,
			SECONDAWY_SUWFACE_ADDWESS_HIGH,
			fwip_wegs->DCSUWF_SECONDAWY_SUWFACE_ADDWESS_HIGH);

	WEG_SET(DCSUWF_SECONDAWY_SUWFACE_ADDWESS, 0,
			SECONDAWY_SUWFACE_ADDWESS,
			fwip_wegs->DCSUWF_SECONDAWY_SUWFACE_ADDWESS);


	WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH_C, 0,
			PWIMAWY_SUWFACE_ADDWESS_HIGH_C,
			fwip_wegs->DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH_C);

	WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS_C, 0,
			PWIMAWY_SUWFACE_ADDWESS_C,
			fwip_wegs->DCSUWF_PWIMAWY_SUWFACE_ADDWESS_C);

	WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH, 0,
			PWIMAWY_SUWFACE_ADDWESS_HIGH,
			fwip_wegs->DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH);

	WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS, 0,
			PWIMAWY_SUWFACE_ADDWESS,
			fwip_wegs->DCSUWF_PWIMAWY_SUWFACE_ADDWESS);
}

static void dmcub_PWAT_54186_wa(stwuct hubp *hubp,
				stwuct suwface_fwip_wegistews *fwip_wegs)
{
	stwuct dcn21_hubp *hubp21 = TO_DCN21_HUBP(hubp);
	union dmub_wb_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));

	cmd.PWAT_54186_wa.headew.type = DMUB_CMD__PWAT_54186_WA;
	cmd.PWAT_54186_wa.headew.paywoad_bytes = sizeof(cmd.PWAT_54186_wa.fwip);
	cmd.PWAT_54186_wa.fwip.DCSUWF_PWIMAWY_SUWFACE_ADDWESS =
		fwip_wegs->DCSUWF_PWIMAWY_SUWFACE_ADDWESS;
	cmd.PWAT_54186_wa.fwip.DCSUWF_PWIMAWY_SUWFACE_ADDWESS_C =
		fwip_wegs->DCSUWF_PWIMAWY_SUWFACE_ADDWESS_C;
	cmd.PWAT_54186_wa.fwip.DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH =
		fwip_wegs->DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH;
	cmd.PWAT_54186_wa.fwip.DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH_C =
		fwip_wegs->DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH_C;
	cmd.PWAT_54186_wa.fwip.fwip_pawams.gwph_steweo = fwip_wegs->gwph_steweo;
	cmd.PWAT_54186_wa.fwip.fwip_pawams.hubp_inst = hubp->inst;
	cmd.PWAT_54186_wa.fwip.fwip_pawams.immediate = fwip_wegs->immediate;
	cmd.PWAT_54186_wa.fwip.fwip_pawams.tmz_suwface = fwip_wegs->tmz_suwface;
	cmd.PWAT_54186_wa.fwip.fwip_pawams.vmid = fwip_wegs->vmid;

	PEWF_TWACE();  // TODO: wemove aftew pewfowmance is stabwe.
	dc_wake_and_execute_dmub_cmd(hubp->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
	PEWF_TWACE();  // TODO: wemove aftew pewfowmance is stabwe.
}

static boow hubp21_pwogwam_suwface_fwip_and_addw(
		stwuct hubp *hubp,
		const stwuct dc_pwane_addwess *addwess,
		boow fwip_immediate)
{
	stwuct suwface_fwip_wegistews fwip_wegs = { 0 };

	fwip_wegs.vmid = addwess->vmid;

	switch (addwess->type) {
	case PWN_ADDW_TYPE_GWAPHICS:
		if (addwess->gwph.addw.quad_pawt == 0) {
			BWEAK_TO_DEBUGGEW();
			bweak;
		}

		if (addwess->gwph.meta_addw.quad_pawt != 0) {
			fwip_wegs.DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS =
					addwess->gwph.meta_addw.wow_pawt;
			fwip_wegs.DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_HIGH =
					addwess->gwph.meta_addw.high_pawt;
		}

		fwip_wegs.DCSUWF_PWIMAWY_SUWFACE_ADDWESS =
				addwess->gwph.addw.wow_pawt;
		fwip_wegs.DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH =
				addwess->gwph.addw.high_pawt;
		bweak;
	case PWN_ADDW_TYPE_VIDEO_PWOGWESSIVE:
		if (addwess->video_pwogwessive.wuma_addw.quad_pawt == 0
				|| addwess->video_pwogwessive.chwoma_addw.quad_pawt == 0)
			bweak;

		if (addwess->video_pwogwessive.wuma_meta_addw.quad_pawt != 0) {
			fwip_wegs.DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS =
					addwess->video_pwogwessive.wuma_meta_addw.wow_pawt;
			fwip_wegs.DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_HIGH =
					addwess->video_pwogwessive.wuma_meta_addw.high_pawt;

			fwip_wegs.DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_C =
					addwess->video_pwogwessive.chwoma_meta_addw.wow_pawt;
			fwip_wegs.DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_HIGH_C =
					addwess->video_pwogwessive.chwoma_meta_addw.high_pawt;
		}

		fwip_wegs.DCSUWF_PWIMAWY_SUWFACE_ADDWESS =
				addwess->video_pwogwessive.wuma_addw.wow_pawt;
		fwip_wegs.DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH =
				addwess->video_pwogwessive.wuma_addw.high_pawt;

		fwip_wegs.DCSUWF_PWIMAWY_SUWFACE_ADDWESS_C =
				addwess->video_pwogwessive.chwoma_addw.wow_pawt;

		fwip_wegs.DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH_C =
				addwess->video_pwogwessive.chwoma_addw.high_pawt;

		bweak;
	case PWN_ADDW_TYPE_GWPH_STEWEO:
		if (addwess->gwph_steweo.weft_addw.quad_pawt == 0)
			bweak;
		if (addwess->gwph_steweo.wight_addw.quad_pawt == 0)
			bweak;

		fwip_wegs.gwph_steweo = twue;

		if (addwess->gwph_steweo.wight_meta_addw.quad_pawt != 0) {
			fwip_wegs.DCSUWF_SECONDAWY_META_SUWFACE_ADDWESS =
					addwess->gwph_steweo.wight_meta_addw.wow_pawt;
			fwip_wegs.DCSUWF_SECONDAWY_META_SUWFACE_ADDWESS_HIGH =
					addwess->gwph_steweo.wight_meta_addw.high_pawt;
		}

		if (addwess->gwph_steweo.weft_meta_addw.quad_pawt != 0) {
			fwip_wegs.DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS =
					addwess->gwph_steweo.weft_meta_addw.wow_pawt;
			fwip_wegs.DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_HIGH =
					addwess->gwph_steweo.weft_meta_addw.high_pawt;
		}

		fwip_wegs.DCSUWF_PWIMAWY_SUWFACE_ADDWESS =
				addwess->gwph_steweo.weft_addw.wow_pawt;
		fwip_wegs.DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH =
				addwess->gwph_steweo.weft_addw.high_pawt;

		fwip_wegs.DCSUWF_SECONDAWY_SUWFACE_ADDWESS =
				addwess->gwph_steweo.wight_addw.wow_pawt;
		fwip_wegs.DCSUWF_SECONDAWY_SUWFACE_ADDWESS_HIGH =
				addwess->gwph_steweo.wight_addw.high_pawt;

		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		bweak;
	}

	fwip_wegs.tmz_suwface = addwess->tmz_suwface;
	fwip_wegs.immediate = fwip_immediate;

	if (hubp->ctx->dc->debug.enabwe_dmcub_suwface_fwip && addwess->type == PWN_ADDW_TYPE_VIDEO_PWOGWESSIVE)
		dmcub_PWAT_54186_wa(hubp, &fwip_wegs);
	ewse
		pwogwam_suwface_fwip_and_addw(hubp, &fwip_wegs);

	hubp->wequest_addwess = *addwess;

	wetuwn twue;
}

static void hubp21_init(stwuct hubp *hubp)
{
	// DEDCN21-133: Inconsistent wow stawting wine fow fwip between DPTE and Meta
	// This is a chicken bit to enabwe the ECO fix.

	stwuct dcn21_hubp *hubp21 = TO_DCN21_HUBP(hubp);
	//hubp[i].HUBPWEQ_DEBUG.HUBPWEQ_DEBUG[26] = 1;
	WEG_WWITE(HUBPWEQ_DEBUG, 1 << 26);
}
static stwuct hubp_funcs dcn21_hubp_funcs = {
	.hubp_enabwe_twipweBuffew = hubp2_enabwe_twipwebuffew,
	.hubp_is_twipwebuffew_enabwed = hubp2_is_twipwebuffew_enabwed,
	.hubp_pwogwam_suwface_fwip_and_addw = hubp21_pwogwam_suwface_fwip_and_addw,
	.hubp_pwogwam_suwface_config = hubp1_pwogwam_suwface_config,
	.hubp_is_fwip_pending = hubp1_is_fwip_pending,
	.hubp_setup = hubp21_setup,
	.hubp_setup_intewdependent = hubp2_setup_intewdependent,
	.hubp_set_vm_system_apewtuwe_settings = hubp21_set_vm_system_apewtuwe_settings,
	.set_bwank = hubp1_set_bwank,
	.dcc_contwow = hubp1_dcc_contwow,
	.mem_pwogwam_viewpowt = hubp21_set_viewpowt,
	.set_cuwsow_attwibutes	= hubp2_cuwsow_set_attwibutes,
	.set_cuwsow_position	= hubp1_cuwsow_set_position,
	.hubp_cwk_cntw = hubp1_cwk_cntw,
	.hubp_vtg_sew = hubp1_vtg_sew,
	.dmdata_set_attwibutes = hubp2_dmdata_set_attwibutes,
	.dmdata_woad = hubp2_dmdata_woad,
	.dmdata_status_done = hubp2_dmdata_status_done,
	.hubp_wead_state = hubp2_wead_state,
	.hubp_cweaw_undewfwow = hubp1_cweaw_undewfwow,
	.hubp_set_fwip_contwow_suwface_gsw = hubp2_set_fwip_contwow_suwface_gsw,
	.hubp_init = hubp21_init,
	.vawidate_dmw_output = hubp21_vawidate_dmw_output,
	.hubp_set_fwip_int = hubp1_set_fwip_int,
};

boow hubp21_constwuct(
	stwuct dcn21_hubp *hubp21,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn_hubp2_wegistews *hubp_wegs,
	const stwuct dcn_hubp2_shift *hubp_shift,
	const stwuct dcn_hubp2_mask *hubp_mask)
{
	hubp21->base.funcs = &dcn21_hubp_funcs;
	hubp21->base.ctx = ctx;
	hubp21->hubp_wegs = hubp_wegs;
	hubp21->hubp_shift = hubp_shift;
	hubp21->hubp_mask = hubp_mask;
	hubp21->base.inst = inst;
	hubp21->base.opp_id = OPP_ID_INVAWID;
	hubp21->base.mpcc_id = 0xf;

	wetuwn twue;
}
