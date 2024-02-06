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

#ifndef DAW_DC_DCN21_DCN21_HUBP_H_
#define DAW_DC_DCN21_DCN21_HUBP_H_

#incwude "../dcn20/dcn20_hubp.h"
#incwude "../dcn10/dcn10_hubp.h"

#define TO_DCN21_HUBP(hubp)\
	containew_of(hubp, stwuct dcn21_hubp, base)

#define HUBP_WEG_WIST_DCN21(id)\
	HUBP_WEG_WIST_DCN2_COMMON(id),\
	SWI(FWIP_PAWAMETEWS_3, HUBPWEQ, id),\
	SWI(FWIP_PAWAMETEWS_4, HUBPWEQ, id),\
	SWI(FWIP_PAWAMETEWS_5, HUBPWEQ, id),\
	SWI(FWIP_PAWAMETEWS_6, HUBPWEQ, id),\
	SWI(VBWANK_PAWAMETEWS_5, HUBPWEQ, id),\
	SWI(VBWANK_PAWAMETEWS_6, HUBPWEQ, id)

#define HUBP_MASK_SH_WIST_DCN21_COMMON(mask_sh)\
	HUBP_MASK_SH_WIST_DCN_SHAWE_COMMON(mask_sh),\
	HUBP_MASK_SH_WIST_DCN_VM(mask_sh),\
	HUBP_SF(HUBP0_DCSUWF_SUWFACE_CONFIG, WOTATION_ANGWE, mask_sh),\
	HUBP_SF(HUBP0_DCSUWF_SUWFACE_CONFIG, H_MIWWOW_EN, mask_sh),\
	HUBP_SF(HUBPWEQ0_PWEFETCH_SETTINGS, DST_Y_PWEFETCH, mask_sh),\
	HUBP_SF(HUBPWEQ0_PWEFETCH_SETTINGS, VWATIO_PWEFETCH, mask_sh),\
	HUBP_SF(HUBPWEQ0_PWEFETCH_SETTINGS_C, VWATIO_PWEFETCH_C, mask_sh),\
	HUBP_SF(HUBPWEQ0_DCN_VM_SYSTEM_APEWTUWE_WOW_ADDW, MC_VM_SYSTEM_APEWTUWE_WOW_ADDW, mask_sh),\
	HUBP_SF(HUBPWEQ0_DCN_VM_SYSTEM_APEWTUWE_HIGH_ADDW, MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW, mask_sh),\
	HUBP_SF(HUBPWEQ0_CUWSOW_SETTINGS, CUWSOW0_DST_Y_OFFSET, mask_sh), \
	HUBP_SF(HUBPWEQ0_CUWSOW_SETTINGS, CUWSOW0_CHUNK_HDW_ADJUST, mask_sh), \
	HUBP_SF(CUWSOW0_0_CUWSOW_SUWFACE_ADDWESS_HIGH, CUWSOW_SUWFACE_ADDWESS_HIGH, mask_sh), \
	HUBP_SF(CUWSOW0_0_CUWSOW_SUWFACE_ADDWESS, CUWSOW_SUWFACE_ADDWESS, mask_sh), \
	HUBP_SF(CUWSOW0_0_CUWSOW_SIZE, CUWSOW_WIDTH, mask_sh), \
	HUBP_SF(CUWSOW0_0_CUWSOW_SIZE, CUWSOW_HEIGHT, mask_sh), \
	HUBP_SF(CUWSOW0_0_CUWSOW_CONTWOW, CUWSOW_MODE, mask_sh), \
	HUBP_SF(CUWSOW0_0_CUWSOW_CONTWOW, CUWSOW_2X_MAGNIFY, mask_sh), \
	HUBP_SF(CUWSOW0_0_CUWSOW_CONTWOW, CUWSOW_PITCH, mask_sh), \
	HUBP_SF(CUWSOW0_0_CUWSOW_CONTWOW, CUWSOW_WINES_PEW_CHUNK, mask_sh), \
	HUBP_SF(CUWSOW0_0_CUWSOW_CONTWOW, CUWSOW_ENABWE, mask_sh), \
	HUBP_SF(CUWSOW0_0_CUWSOW_POSITION, CUWSOW_X_POSITION, mask_sh), \
	HUBP_SF(CUWSOW0_0_CUWSOW_POSITION, CUWSOW_Y_POSITION, mask_sh), \
	HUBP_SF(CUWSOW0_0_CUWSOW_HOT_SPOT, CUWSOW_HOT_SPOT_X, mask_sh), \
	HUBP_SF(CUWSOW0_0_CUWSOW_HOT_SPOT, CUWSOW_HOT_SPOT_Y, mask_sh), \
	HUBP_SF(CUWSOW0_0_CUWSOW_DST_OFFSET, CUWSOW_DST_X_OFFSET, mask_sh), \
	HUBP_SF(CUWSOW0_0_DMDATA_ADDWESS_HIGH, DMDATA_ADDWESS_HIGH, mask_sh), \
	HUBP_SF(CUWSOW0_0_DMDATA_CNTW, DMDATA_MODE, mask_sh), \
	HUBP_SF(CUWSOW0_0_DMDATA_CNTW, DMDATA_UPDATED, mask_sh), \
	HUBP_SF(CUWSOW0_0_DMDATA_CNTW, DMDATA_WEPEAT, mask_sh), \
	HUBP_SF(CUWSOW0_0_DMDATA_CNTW, DMDATA_SIZE, mask_sh), \
	HUBP_SF(CUWSOW0_0_DMDATA_SW_CNTW, DMDATA_SW_UPDATED, mask_sh), \
	HUBP_SF(CUWSOW0_0_DMDATA_SW_CNTW, DMDATA_SW_WEPEAT, mask_sh), \
	HUBP_SF(CUWSOW0_0_DMDATA_SW_CNTW, DMDATA_SW_SIZE, mask_sh), \
	HUBP_SF(CUWSOW0_0_DMDATA_QOS_CNTW, DMDATA_QOS_MODE, mask_sh), \
	HUBP_SF(CUWSOW0_0_DMDATA_QOS_CNTW, DMDATA_QOS_WEVEW, mask_sh), \
	HUBP_SF(CUWSOW0_0_DMDATA_QOS_CNTW, DMDATA_DW_DEWTA, mask_sh), \
	HUBP_SF(CUWSOW0_0_DMDATA_STATUS, DMDATA_DONE, mask_sh),\
	HUBP_SF(HUBPWEQ0_FWIP_PAWAMETEWS_0, DST_Y_PEW_VM_FWIP, mask_sh),\
	HUBP_SF(HUBPWEQ0_FWIP_PAWAMETEWS_0, DST_Y_PEW_WOW_FWIP, mask_sh),\
	HUBP_SF(HUBPWEQ0_FWIP_PAWAMETEWS_1, WEFCYC_PEW_PTE_GWOUP_FWIP_W, mask_sh),\
	HUBP_SF(HUBPWEQ0_FWIP_PAWAMETEWS_2, WEFCYC_PEW_META_CHUNK_FWIP_W, mask_sh),\
	HUBP_SF(HUBP0_DCHUBP_CNTW, HUBP_VWEADY_AT_OW_AFTEW_VSYNC, mask_sh),\
	HUBP_SF(HUBP0_DCHUBP_CNTW, HUBP_DISABWE_STOP_DATA_DUWING_VM, mask_sh),\
	HUBP_SF(HUBPWEQ0_DCSUWF_FWIP_CONTWOW, HUBPWEQ_MASTEW_UPDATE_WOCK_STATUS, mask_sh),\
	HUBP_SF(HUBPWEQ0_DCSUWF_FWIP_CONTWOW2, SUWFACE_GSW_ENABWE, mask_sh),\
	HUBP_SF(HUBPWEQ0_DCSUWF_FWIP_CONTWOW2, SUWFACE_TWIPWE_BUFFEW_ENABWE, mask_sh),\
	HUBP_SF(HUBPWEQ0_VMID_SETTINGS_0, VMID, mask_sh),\
	HUBP_SF(HUBPWEQ0_FWIP_PAWAMETEWS_3, WEFCYC_PEW_VM_GWOUP_FWIP, mask_sh),\
	HUBP_SF(HUBPWEQ0_FWIP_PAWAMETEWS_4, WEFCYC_PEW_VM_WEQ_FWIP, mask_sh),\
	HUBP_SF(HUBPWEQ0_FWIP_PAWAMETEWS_5, WEFCYC_PEW_PTE_GWOUP_FWIP_C, mask_sh),\
	HUBP_SF(HUBPWEQ0_FWIP_PAWAMETEWS_6, WEFCYC_PEW_META_CHUNK_FWIP_C, mask_sh),\
	HUBP_SF(HUBPWEQ0_VBWANK_PAWAMETEWS_5, WEFCYC_PEW_VM_GWOUP_VBWANK, mask_sh),\
	HUBP_SF(HUBPWEQ0_VBWANK_PAWAMETEWS_6, WEFCYC_PEW_VM_WEQ_VBWANK, mask_sh),\
	HUBP_SF(HUBP0_DCHUBP_WEQ_SIZE_CONFIG, VM_GWOUP_SIZE, mask_sh)

#define HUBP_MASK_SH_WIST_DCN21(mask_sh)\
	HUBP_MASK_SH_WIST_DCN21_COMMON(mask_sh),\
	HUBP_SF(HUBP0_DCSUWF_TIWING_CONFIG, WB_AWIGNED, mask_sh)


stwuct dcn21_hubp {
	stwuct hubp base;
	stwuct dcn_hubp_state state;
	const stwuct dcn_hubp2_wegistews *hubp_wegs;
	const stwuct dcn_hubp2_shift *hubp_shift;
	const stwuct dcn_hubp2_mask *hubp_mask;
	int PWAT_54186_wa_chwoma_addw_offset;
};

boow hubp21_constwuct(
	stwuct dcn21_hubp *hubp21,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn_hubp2_wegistews *hubp_wegs,
	const stwuct dcn_hubp2_shift *hubp_shift,
	const stwuct dcn_hubp2_mask *hubp_mask);

void appwy_DEDCN21_142_wa_fow_hostvm_deadwine(
		stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_attw);

void hubp21_pwogwam_deadwine(
		stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_attw,
		stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_attw);

void hubp21_pwogwam_wequestow(
		stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_wq_wegs_st *wq_wegs);
#endif /* DAW_DC_DCN21_DCN21_HUBP_H_ */
