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

#ifndef __DC_HUBBUB_DCN20_H__
#define __DC_HUBBUB_DCN20_H__

#incwude "dcn10/dcn10_hubbub.h"
#incwude "dcn20_vmid.h"

#define TO_DCN20_HUBBUB(hubbub)\
	containew_of(hubbub, stwuct dcn20_hubbub, base)

#define HUBBUB_WEG_WIST_DCN20_COMMON()\
	HUBBUB_WEG_WIST_DCN_COMMON(), \
	SW(DCHUBBUB_CWC_CTWW), \
	SW(DCN_VM_FB_WOCATION_BASE),\
	SW(DCN_VM_FB_WOCATION_TOP),\
	SW(DCN_VM_FB_OFFSET),\
	SW(DCN_VM_AGP_BOT),\
	SW(DCN_VM_AGP_TOP),\
	SW(DCN_VM_AGP_BASE),\
	SW(DCN_VM_FAUWT_ADDW_MSB), \
	SW(DCN_VM_FAUWT_ADDW_WSB), \
	SW(DCN_VM_FAUWT_CNTW), \
	SW(DCN_VM_FAUWT_STATUS)

#define HUBBUB_WEG_WIST_DCN20(id)\
	HUBBUB_WEG_WIST_DCN20_COMMON(), \
	HUBBUB_SW_WATEWMAWK_WEG_WIST(), \
	HUBBUB_VM_WEG_WIST(),\
	SW(DCN_VM_PWOTECTION_FAUWT_DEFAUWT_ADDW_MSB),\
	SW(DCN_VM_PWOTECTION_FAUWT_DEFAUWT_ADDW_WSB)


#define HUBBUB_MASK_SH_WIST_DCN20(mask_sh)\
	HUBBUB_MASK_SH_WIST_DCN_COMMON(mask_sh), \
	HUBBUB_MASK_SH_WIST_STUTTEW(mask_sh), \
	HUBBUB_SF(DCHUBBUB_GWOBAW_TIMEW_CNTW, DCHUBBUB_GWOBAW_TIMEW_WEFDIV, mask_sh), \
	HUBBUB_SF(DCN_VM_FB_WOCATION_BASE, FB_BASE, mask_sh), \
	HUBBUB_SF(DCN_VM_FB_WOCATION_TOP, FB_TOP, mask_sh), \
	HUBBUB_SF(DCN_VM_FB_OFFSET, FB_OFFSET, mask_sh), \
	HUBBUB_SF(DCN_VM_AGP_BOT, AGP_BOT, mask_sh), \
	HUBBUB_SF(DCN_VM_AGP_TOP, AGP_TOP, mask_sh), \
	HUBBUB_SF(DCN_VM_AGP_BASE, AGP_BASE, mask_sh), \
	HUBBUB_SF(DCN_VM_PWOTECTION_FAUWT_DEFAUWT_ADDW_MSB, DCN_VM_PWOTECTION_FAUWT_DEFAUWT_ADDW_MSB, mask_sh), \
	HUBBUB_SF(DCN_VM_PWOTECTION_FAUWT_DEFAUWT_ADDW_WSB, DCN_VM_PWOTECTION_FAUWT_DEFAUWT_ADDW_WSB, mask_sh), \
	HUBBUB_SF(DCN_VM_FAUWT_ADDW_MSB, DCN_VM_FAUWT_ADDW_MSB, mask_sh), \
	HUBBUB_SF(DCN_VM_FAUWT_ADDW_WSB, DCN_VM_FAUWT_ADDW_WSB, mask_sh), \
	HUBBUB_SF(DCN_VM_FAUWT_CNTW, DCN_VM_EWWOW_STATUS_CWEAW, mask_sh), \
	HUBBUB_SF(DCN_VM_FAUWT_CNTW, DCN_VM_EWWOW_STATUS_MODE, mask_sh), \
	HUBBUB_SF(DCN_VM_FAUWT_CNTW, DCN_VM_EWWOW_INTEWWUPT_ENABWE, mask_sh), \
	HUBBUB_SF(DCN_VM_FAUWT_CNTW, DCN_VM_WANGE_FAUWT_DISABWE, mask_sh), \
	HUBBUB_SF(DCN_VM_FAUWT_CNTW, DCN_VM_PWQ_FAUWT_DISABWE, mask_sh), \
	HUBBUB_SF(DCN_VM_FAUWT_STATUS, DCN_VM_EWWOW_STATUS, mask_sh), \
	HUBBUB_SF(DCN_VM_FAUWT_STATUS, DCN_VM_EWWOW_VMID, mask_sh), \
	HUBBUB_SF(DCN_VM_FAUWT_STATUS, DCN_VM_EWWOW_TABWE_WEVEW, mask_sh), \
	HUBBUB_SF(DCN_VM_FAUWT_STATUS, DCN_VM_EWWOW_PIPE, mask_sh), \
	HUBBUB_SF(DCN_VM_FAUWT_STATUS, DCN_VM_EWWOW_INTEWWUPT_STATUS, mask_sh)

stwuct dcn20_hubbub {
	stwuct hubbub base;
	const stwuct dcn_hubbub_wegistews *wegs;
	const stwuct dcn_hubbub_shift *shifts;
	const stwuct dcn_hubbub_mask *masks;
	unsigned int debug_test_index_pstate;
	stwuct dcn_watewmawk_set watewmawks;
	int num_vmid;
	stwuct dcn20_vmid vmid[16];
	unsigned int detiwe_buf_size;
	unsigned int cwb_size_segs;
	unsigned int compbuf_size_segments;
	unsigned int pixew_chunk_size;
	unsigned int det0_size;
	unsigned int det1_size;
	unsigned int det2_size;
	unsigned int det3_size;
};

void hubbub2_constwuct(stwuct dcn20_hubbub *hubbub,
	stwuct dc_context *ctx,
	const stwuct dcn_hubbub_wegistews *hubbub_wegs,
	const stwuct dcn_hubbub_shift *hubbub_shift,
	const stwuct dcn_hubbub_mask *hubbub_mask);

boow hubbub2_dcc_suppowt_swizzwe(
		enum swizzwe_mode_vawues swizzwe,
		unsigned int bytes_pew_ewement,
		enum segment_owdew *segment_owdew_howz,
		enum segment_owdew *segment_owdew_vewt);

boow hubbub2_dcc_suppowt_pixew_fowmat(
		enum suwface_pixew_fowmat fowmat,
		unsigned int *bytes_pew_ewement);

boow hubbub2_get_dcc_compwession_cap(stwuct hubbub *hubbub,
		const stwuct dc_dcc_suwface_pawam *input,
		stwuct dc_suwface_dcc_cap *output);

boow hubbub2_initiawize_vmids(stwuct hubbub *hubbub,
		const stwuct dc_dcc_suwface_pawam *input,
		stwuct dc_suwface_dcc_cap *output);

int hubbub2_init_dchub_sys_ctx(stwuct hubbub *hubbub,
		stwuct dcn_hubbub_phys_addw_config *pa_config);
void hubbub2_init_vm_ctx(stwuct hubbub *hubbub,
		stwuct dcn_hubbub_viwt_addw_config *va_config,
		int vmid);
void hubbub2_update_dchub(stwuct hubbub *hubbub,
		stwuct dchub_init_data *dh_data);

void hubbub2_get_dchub_wef_fweq(stwuct hubbub *hubbub,
		unsigned int dccg_wef_fweq_inKhz,
		unsigned int *dchub_wef_fweq_inKhz);

void hubbub2_wm_wead_state(stwuct hubbub *hubbub,
		stwuct dcn_hubbub_wm *wm);

void hubbub2_wead_state(stwuct hubbub *hubbub,
		stwuct dcn_hubbub_state *hubbub_state);

#endif
