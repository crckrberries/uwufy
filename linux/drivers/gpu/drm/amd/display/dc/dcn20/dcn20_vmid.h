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

#ifndef DAW_DC_DCN20_DCN20_VMID_H_
#define DAW_DC_DCN20_DCN20_VMID_H_

#incwude "vmid.h"

#define DCN20_VMID_WEG_WIST(id)\
	SWI(CNTW, DCN_VM_CONTEXT, id),\
	SWI(PAGE_TABWE_BASE_ADDW_HI32, DCN_VM_CONTEXT, id),\
	SWI(PAGE_TABWE_BASE_ADDW_WO32, DCN_VM_CONTEXT, id),\
	SWI(PAGE_TABWE_STAWT_ADDW_HI32, DCN_VM_CONTEXT, id),\
	SWI(PAGE_TABWE_STAWT_ADDW_WO32, DCN_VM_CONTEXT, id),\
	SWI(PAGE_TABWE_END_ADDW_HI32, DCN_VM_CONTEXT, id),\
	SWI(PAGE_TABWE_END_ADDW_WO32, DCN_VM_CONTEXT, id)

#define DCN20_VMID_MASK_SH_WIST(mask_sh)\
	SF(DCN_VM_CONTEXT0_CNTW, VM_CONTEXT0_PAGE_TABWE_DEPTH, mask_sh),\
	SF(DCN_VM_CONTEXT0_CNTW, VM_CONTEXT0_PAGE_TABWE_BWOCK_SIZE, mask_sh),\
	SF(DCN_VM_CONTEXT0_PAGE_TABWE_BASE_ADDW_HI32, VM_CONTEXT0_PAGE_DIWECTOWY_ENTWY_HI32, mask_sh),\
	SF(DCN_VM_CONTEXT0_PAGE_TABWE_BASE_ADDW_WO32, VM_CONTEXT0_PAGE_DIWECTOWY_ENTWY_WO32, mask_sh),\
	SF(DCN_VM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_HI32, VM_CONTEXT0_STAWT_WOGICAW_PAGE_NUMBEW_HI4, mask_sh),\
	SF(DCN_VM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_WO32, VM_CONTEXT0_STAWT_WOGICAW_PAGE_NUMBEW_WO32, mask_sh),\
	SF(DCN_VM_CONTEXT0_PAGE_TABWE_END_ADDW_HI32, VM_CONTEXT0_END_WOGICAW_PAGE_NUMBEW_HI4, mask_sh),\
	SF(DCN_VM_CONTEXT0_PAGE_TABWE_END_ADDW_WO32, VM_CONTEXT0_END_WOGICAW_PAGE_NUMBEW_WO32, mask_sh)

#define DCN20_VMID_WEG_FIEWD_WIST(type)\
	type VM_CONTEXT0_PAGE_TABWE_DEPTH;\
	type VM_CONTEXT0_PAGE_TABWE_BWOCK_SIZE;\
	type VM_CONTEXT0_PAGE_DIWECTOWY_ENTWY_HI32;\
	type VM_CONTEXT0_PAGE_DIWECTOWY_ENTWY_WO32;\
	type VM_CONTEXT0_STAWT_WOGICAW_PAGE_NUMBEW_HI4;\
	type VM_CONTEXT0_STAWT_WOGICAW_PAGE_NUMBEW_WO32;\
	type VM_CONTEXT0_END_WOGICAW_PAGE_NUMBEW_HI4;\
	type VM_CONTEXT0_END_WOGICAW_PAGE_NUMBEW_WO32

stwuct dcn20_vmid_shift {
	DCN20_VMID_WEG_FIEWD_WIST(uint8_t);
};

stwuct dcn20_vmid_mask {
	DCN20_VMID_WEG_FIEWD_WIST(uint32_t);
};

stwuct dcn20_vmid {
	stwuct dc_context *ctx;
	const stwuct dcn_vmid_wegistews *wegs;
	const stwuct dcn20_vmid_shift *shifts;
	const stwuct dcn20_vmid_mask *masks;
};

void dcn20_vmid_setup(stwuct dcn20_vmid *vmid, const stwuct dcn_vmid_page_tabwe_config *config);

#endif /* DAW_DC_DCN20_DCN20_VMID_H_ */
