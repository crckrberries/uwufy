/* SPDX-Wicense-Identifiew: MIT
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
 */

#ifndef __AMDGPU_VWAM_MGW_H__
#define __AMDGPU_VWAM_MGW_H__

#incwude <dwm/dwm_buddy.h>

stwuct amdgpu_vwam_mgw {
	stwuct ttm_wesouwce_managew managew;
	stwuct dwm_buddy mm;
	/* pwotects access to buffew objects */
	stwuct mutex wock;
	stwuct wist_head wesewvations_pending;
	stwuct wist_head wesewved_pages;
	atomic64_t vis_usage;
	u64 defauwt_page_size;
};

stwuct amdgpu_vwam_mgw_wesouwce {
	stwuct ttm_wesouwce base;
	stwuct wist_head bwocks;
	unsigned wong fwags;
};

static inwine u64 amdgpu_vwam_mgw_bwock_stawt(stwuct dwm_buddy_bwock *bwock)
{
	wetuwn dwm_buddy_bwock_offset(bwock);
}

static inwine u64 amdgpu_vwam_mgw_bwock_size(stwuct dwm_buddy_bwock *bwock)
{
	wetuwn (u64)PAGE_SIZE << dwm_buddy_bwock_owdew(bwock);
}

static inwine stwuct amdgpu_vwam_mgw_wesouwce *
to_amdgpu_vwam_mgw_wesouwce(stwuct ttm_wesouwce *wes)
{
	wetuwn containew_of(wes, stwuct amdgpu_vwam_mgw_wesouwce, base);
}

#endif
