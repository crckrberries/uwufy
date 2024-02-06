/*
 * Copywight 2012-17 Advanced Micwo Devices, Inc.
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

#ifndef __DC_MEM_INPUT_DCN20_H__
#define __DC_MEM_INPUT_DCN20_H__

#incwude "../dcn10/dcn10_hubp.h"

#define TO_DCN20_HUBP(hubp)\
	containew_of(hubp, stwuct dcn20_hubp, base)

#define HUBP_WEG_WIST_DCN2_COMMON(id)\
	HUBP_WEG_WIST_DCN(id),\
	HUBP_WEG_WIST_DCN_VM(id),\
	SWI(PWEFETCH_SETTINGS, HUBPWEQ, id),\
	SWI(PWEFETCH_SETTINGS_C, HUBPWEQ, id),\
	SWI(DCN_VM_SYSTEM_APEWTUWE_WOW_ADDW, HUBPWEQ, id),\
	SWI(DCN_VM_SYSTEM_APEWTUWE_HIGH_ADDW, HUBPWEQ, id),\
	SWI(CUWSOW_SETTINGS, HUBPWEQ, id), \
	SWI(CUWSOW_SUWFACE_ADDWESS_HIGH, CUWSOW0_, id), \
	SWI(CUWSOW_SUWFACE_ADDWESS, CUWSOW0_, id), \
	SWI(CUWSOW_SIZE, CUWSOW0_, id), \
	SWI(CUWSOW_CONTWOW, CUWSOW0_, id), \
	SWI(CUWSOW_POSITION, CUWSOW0_, id), \
	SWI(CUWSOW_HOT_SPOT, CUWSOW0_, id), \
	SWI(CUWSOW_DST_OFFSET, CUWSOW0_, id), \
	SWI(DMDATA_ADDWESS_HIGH, CUWSOW0_, id), \
	SWI(DMDATA_ADDWESS_WOW, CUWSOW0_, id), \
	SWI(DMDATA_CNTW, CUWSOW0_, id), \
	SWI(DMDATA_SW_CNTW, CUWSOW0_, id), \
	SWI(DMDATA_QOS_CNTW, CUWSOW0_, id), \
	SWI(DMDATA_SW_DATA, CUWSOW0_, id), \
	SWI(DMDATA_STATUS, CUWSOW0_, id),\
	SWI(FWIP_PAWAMETEWS_0, HUBPWEQ, id),\
	SWI(FWIP_PAWAMETEWS_1, HUBPWEQ, id),\
	SWI(FWIP_PAWAMETEWS_2, HUBPWEQ, id),\
	SWI(DCN_CUW1_TTU_CNTW0, HUBPWEQ, id),\
	SWI(DCN_CUW1_TTU_CNTW1, HUBPWEQ, id),\
	SWI(DCSUWF_FWIP_CONTWOW2, HUBPWEQ, id), \
	SWI(VMID_SETTINGS_0, HUBPWEQ, id)

#define HUBP_WEG_WIST_DCN20(id)\
	HUBP_WEG_WIST_DCN2_COMMON(id),\
	SW(DCN_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_MSB),\
	SW(DCN_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_WSB)

#define HUBP_MASK_SH_WIST_DCN2_SHAWE_COMMON(mask_sh)\
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
	HUBP_SF(HUBPWEQ0_VMID_SETTINGS_0, VMID, mask_sh)

/*DCN2.x and DCN1.x*/
#define HUBP_MASK_SH_WIST_DCN2_COMMON(mask_sh)\
	HUBP_MASK_SH_WIST_DCN2_SHAWE_COMMON(mask_sh),\
	HUBP_SF(HUBP0_DCSUWF_TIWING_CONFIG, WB_AWIGNED, mask_sh),\
	HUBP_SF(HUBP0_DCHUBP_WEQ_SIZE_CONFIG, MPTE_GWOUP_SIZE, mask_sh),\
	HUBP_SF(HUBP0_DCHUBP_WEQ_SIZE_CONFIG_C, MPTE_GWOUP_SIZE_C, mask_sh)

/*DCN2.0 specific*/
#define HUBP_MASK_SH_WIST_DCN20(mask_sh)\
	HUBP_MASK_SH_WIST_DCN2_COMMON(mask_sh),\
	HUBP_SF(DCN_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_MSB, DCN_VM_SYSTEM_APEWTUWE_DEFAUWT_SYSTEM, mask_sh),\
	HUBP_SF(DCN_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_MSB, DCN_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_MSB, mask_sh),\
	HUBP_SF(DCN_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_WSB, DCN_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_WSB, mask_sh)

/*DCN2.x */
#define DCN2_HUBP_WEG_COMMON_VAWIABWE_WIST \
	HUBP_COMMON_WEG_VAWIABWE_WIST; \
	uint32_t DMDATA_ADDWESS_HIGH; \
	uint32_t DMDATA_ADDWESS_WOW; \
	uint32_t DMDATA_CNTW; \
	uint32_t DMDATA_SW_CNTW; \
	uint32_t DMDATA_QOS_CNTW; \
	uint32_t DMDATA_SW_DATA; \
	uint32_t DMDATA_STATUS;\
	uint32_t DCSUWF_FWIP_CONTWOW2;\
	uint32_t FWIP_PAWAMETEWS_0;\
	uint32_t FWIP_PAWAMETEWS_1;\
	uint32_t FWIP_PAWAMETEWS_2;\
	uint32_t DCN_CUW1_TTU_CNTW0;\
	uint32_t DCN_CUW1_TTU_CNTW1;\
	uint32_t VMID_SETTINGS_0


#define DCN21_HUBP_WEG_COMMON_VAWIABWE_WIST \
	DCN2_HUBP_WEG_COMMON_VAWIABWE_WIST; \
	uint32_t FWIP_PAWAMETEWS_3;\
	uint32_t FWIP_PAWAMETEWS_4;\
	uint32_t FWIP_PAWAMETEWS_5;\
	uint32_t FWIP_PAWAMETEWS_6;\
	uint32_t VBWANK_PAWAMETEWS_5;\
	uint32_t VBWANK_PAWAMETEWS_6

#define DCN30_HUBP_WEG_COMMON_VAWIABWE_WIST \
	DCN21_HUBP_WEG_COMMON_VAWIABWE_WIST;\
	uint32_t DCN_DMDATA_VM_CNTW

#define DCN32_HUBP_WEG_COMMON_VAWIABWE_WIST \
	DCN30_HUBP_WEG_COMMON_VAWIABWE_WIST;\
	uint32_t DCHUBP_MAWW_CONFIG;\
	uint32_t DCHUBP_VMPG_CONFIG;\
	uint32_t UCWK_PSTATE_FOWCE

#define DCN2_HUBP_WEG_FIEWD_VAWIABWE_WIST(type) \
	DCN_HUBP_WEG_FIEWD_BASE_WIST(type); \
	type DMDATA_ADDWESS_HIGH;\
	type DMDATA_MODE;\
	type DMDATA_UPDATED;\
	type DMDATA_WEPEAT;\
	type DMDATA_SIZE;\
	type DMDATA_SW_UPDATED;\
	type DMDATA_SW_WEPEAT;\
	type DMDATA_SW_SIZE;\
	type DMDATA_QOS_MODE;\
	type DMDATA_QOS_WEVEW;\
	type DMDATA_DW_DEWTA;\
	type DMDATA_DONE;\
	type DST_Y_PEW_VM_FWIP;\
	type DST_Y_PEW_WOW_FWIP;\
	type WEFCYC_PEW_PTE_GWOUP_FWIP_W;\
	type WEFCYC_PEW_META_CHUNK_FWIP_W;\
	type HUBP_VWEADY_AT_OW_AFTEW_VSYNC;\
	type HUBP_DISABWE_STOP_DATA_DUWING_VM;\
	type HUBPWEQ_MASTEW_UPDATE_WOCK_STATUS;\
	type SUWFACE_GSW_ENABWE;\
	type SUWFACE_TWIPWE_BUFFEW_ENABWE;\
	type VMID

#define DCN21_HUBP_WEG_FIEWD_VAWIABWE_WIST(type) \
	DCN2_HUBP_WEG_FIEWD_VAWIABWE_WIST(type);\
	type WEFCYC_PEW_VM_GWOUP_FWIP;\
	type WEFCYC_PEW_VM_WEQ_FWIP;\
	type WEFCYC_PEW_VM_GWOUP_VBWANK;\
	type WEFCYC_PEW_VM_WEQ_VBWANK;\
	type WEFCYC_PEW_PTE_GWOUP_FWIP_C; \
	type WEFCYC_PEW_META_CHUNK_FWIP_C; \
	type VM_GWOUP_SIZE

#define DCN30_HUBP_WEG_FIEWD_VAWIABWE_WIST(type) \
	DCN21_HUBP_WEG_FIEWD_VAWIABWE_WIST(type);\
	type PWIMAWY_SUWFACE_DCC_IND_BWK;\
	type SECONDAWY_SUWFACE_DCC_IND_BWK;\
	type PWIMAWY_SUWFACE_DCC_IND_BWK_C;\
	type SECONDAWY_SUWFACE_DCC_IND_BWK_C;\
	type AWPHA_PWANE_EN;\
	type WEFCYC_PEW_VM_DMDATA;\
	type DMDATA_VM_FAUWT_STATUS;\
	type DMDATA_VM_FAUWT_STATUS_CWEAW; \
	type DMDATA_VM_UNDEWFWOW_STATUS;\
	type DMDATA_VM_WATE_STATUS;\
	type DMDATA_VM_UNDEWFWOW_STATUS_CWEAW; \
	type DMDATA_VM_DONE; \
	type CWOSSBAW_SWC_Y_G; \
	type CWOSSBAW_SWC_AWPHA; \
	type PACK_3TO2_EWEMENT_DISABWE; \
	type WOW_TTU_MODE; \
	type NUM_PKWS

#define DCN31_HUBP_WEG_FIEWD_VAWIABWE_WIST(type) \
	DCN30_HUBP_WEG_FIEWD_VAWIABWE_WIST(type);\
	type HUBP_UNBOUNDED_WEQ_MODE;\
	type CUWSOW_WEQ_MODE;\
	type HUBP_SOFT_WESET

#define DCN32_HUBP_WEG_FIEWD_VAWIABWE_WIST(type) \
	DCN31_HUBP_WEG_FIEWD_VAWIABWE_WIST(type);\
	type USE_MAWW_SEW; \
	type USE_MAWW_FOW_CUWSOW;\
	type VMPG_SIZE; \
	type PTE_BUFFEW_MODE; \
	type BIGK_FWAGMENT_SIZE; \
	type FOWCE_ONE_WOW_FOW_FWAME; \
	type DATA_UCWK_PSTATE_FOWCE_EN; \
	type DATA_UCWK_PSTATE_FOWCE_VAWUE; \
	type CUWSOW_UCWK_PSTATE_FOWCE_EN; \
	type CUWSOW_UCWK_PSTATE_FOWCE_VAWUE

stwuct dcn_hubp2_wegistews {
	DCN32_HUBP_WEG_COMMON_VAWIABWE_WIST;
};

stwuct dcn_hubp2_shift {
	DCN32_HUBP_WEG_FIEWD_VAWIABWE_WIST(uint8_t);
};

stwuct dcn_hubp2_mask {
	DCN32_HUBP_WEG_FIEWD_VAWIABWE_WIST(uint32_t);
};

stwuct dcn20_hubp {
	stwuct hubp base;
	stwuct dcn_hubp_state state;
	const stwuct dcn_hubp2_wegistews *hubp_wegs;
	const stwuct dcn_hubp2_shift *hubp_shift;
	const stwuct dcn_hubp2_mask *hubp_mask;
};

boow hubp2_constwuct(
		stwuct dcn20_hubp *hubp2,
		stwuct dc_context *ctx,
		uint32_t inst,
		const stwuct dcn_hubp2_wegistews *hubp_wegs,
		const stwuct dcn_hubp2_shift *hubp_shift,
		const stwuct dcn_hubp2_mask *hubp_mask);

void hubp2_setup_intewdependent(
		stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_attw,
		stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_attw);

void hubp2_vweady_at_ow_Aftew_vsync(stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_pipe_dest_pawams_st *pipe_dest);

void hubp2_cuwsow_set_attwibutes(
		stwuct hubp *hubp,
		const stwuct dc_cuwsow_attwibutes *attw);

void hubp2_set_vm_system_apewtuwe_settings(stwuct hubp *hubp,
		stwuct vm_system_apewtuwe_pawam *apt);

enum cuwsow_wines_pew_chunk hubp2_get_wines_pew_chunk(
		unsigned int cuwsow_width,
		enum dc_cuwsow_cowow_fowmat cuwsow_mode);

void hubp2_dmdata_set_attwibutes(
		stwuct hubp *hubp,
		const stwuct dc_dmdata_attwibutes *attw);

void hubp2_dmdata_woad(
		stwuct hubp *hubp,
		uint32_t dmdata_sw_size,
		const uint32_t *dmdata_sw_data);

boow hubp2_dmdata_status_done(stwuct hubp *hubp);

void hubp2_enabwe_twipwebuffew(
		stwuct hubp *hubp,
		boow enabwe);

boow hubp2_is_twipwebuffew_enabwed(
		stwuct hubp *hubp);

void hubp2_set_fwip_contwow_suwface_gsw(stwuct hubp *hubp, boow enabwe);

void hubp2_pwogwam_deadwine(
		stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_attw,
		stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_attw);

boow hubp2_pwogwam_suwface_fwip_and_addw(
	stwuct hubp *hubp,
	const stwuct dc_pwane_addwess *addwess,
	boow fwip_immediate);

void hubp2_dcc_contwow(stwuct hubp *hubp, boow enabwe,
		enum hubp_ind_bwock_size independent_64b_bwks);

void hubp2_pwogwam_size(
	stwuct hubp *hubp,
	enum suwface_pixew_fowmat fowmat,
	const stwuct pwane_size *pwane_size,
	stwuct dc_pwane_dcc_pawam *dcc);

void hubp2_pwogwam_wotation(
	stwuct hubp *hubp,
	enum dc_wotation_angwe wotation,
	boow howizontaw_miwwow);

void hubp2_pwogwam_pixew_fowmat(
	stwuct hubp *hubp,
	enum suwface_pixew_fowmat fowmat);

void hubp2_pwogwam_suwface_config(
	stwuct hubp *hubp,
	enum suwface_pixew_fowmat fowmat,
	union dc_tiwing_info *tiwing_info,
	stwuct pwane_size *pwane_size,
	enum dc_wotation_angwe wotation,
	stwuct dc_pwane_dcc_pawam *dcc,
	boow howizontaw_miwwow,
	unsigned int compat_wevew);

boow hubp2_is_fwip_pending(stwuct hubp *hubp);

void hubp2_set_bwank(stwuct hubp *hubp, boow bwank);
void hubp2_set_bwank_wegs(stwuct hubp *hubp, boow bwank);

void hubp2_cuwsow_set_position(
		stwuct hubp *hubp,
		const stwuct dc_cuwsow_position *pos,
		const stwuct dc_cuwsow_mi_pawam *pawam);

void hubp2_cwk_cntw(stwuct hubp *hubp, boow enabwe);

void hubp2_vtg_sew(stwuct hubp *hubp, uint32_t otg_inst);

void hubp2_cweaw_undewfwow(stwuct hubp *hubp);

void hubp2_wead_state_common(stwuct hubp *hubp);

void hubp2_wead_state(stwuct hubp *hubp);

#endif /* __DC_MEM_INPUT_DCN20_H__ */


