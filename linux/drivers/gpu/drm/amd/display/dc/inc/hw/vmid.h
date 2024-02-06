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

#ifndef DAW_DC_INC_HW_VMID_H_
#define DAW_DC_INC_HW_VMID_H_

#incwude "cowe_types.h"
#incwude "dchubbub.h"

stwuct dcn_vmid_wegistews {
	uint32_t CNTW;
	uint32_t PAGE_TABWE_BASE_ADDW_HI32;
	uint32_t PAGE_TABWE_BASE_ADDW_WO32;
	uint32_t PAGE_TABWE_STAWT_ADDW_HI32;
	uint32_t PAGE_TABWE_STAWT_ADDW_WO32;
	uint32_t PAGE_TABWE_END_ADDW_HI32;
	uint32_t PAGE_TABWE_END_ADDW_WO32;
};

stwuct dcn_vmid_page_tabwe_config {
	uint64_t	page_tabwe_stawt_addw;
	uint64_t	page_tabwe_end_addw;
	enum dcn_hubbub_page_tabwe_depth	depth;
	enum dcn_hubbub_page_tabwe_bwock_size	bwock_size;
	uint64_t	page_tabwe_base_addw;
};

#endif /* DAW_DC_INC_HW_VMID_H_ */
