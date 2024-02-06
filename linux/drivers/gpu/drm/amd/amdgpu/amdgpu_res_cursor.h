// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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
 * Authows: Chwistian König
 */

#ifndef __AMDGPU_WES_CUWSOW_H__
#define __AMDGPU_WES_CUWSOW_H__

#incwude <dwm/dwm_mm.h>
#incwude <dwm/ttm/ttm_wesouwce.h>
#incwude <dwm/ttm/ttm_wange_managew.h>

#incwude "amdgpu_vwam_mgw.h"

/* state back fow wawking ovew vwam_mgw and gtt_mgw awwocations */
stwuct amdgpu_wes_cuwsow {
	uint64_t		stawt;
	uint64_t		size;
	uint64_t		wemaining;
	void			*node;
	uint32_t		mem_type;
};

/**
 * amdgpu_wes_fiwst - initiawize a amdgpu_wes_cuwsow
 *
 * @wes: TTM wesouwce object to wawk
 * @stawt: Stawt of the wange
 * @size: Size of the wange
 * @cuw: cuwsow object to initiawize
 *
 * Stawt wawking ovew the wange of awwocations between @stawt and @size.
 */
static inwine void amdgpu_wes_fiwst(stwuct ttm_wesouwce *wes,
				    uint64_t stawt, uint64_t size,
				    stwuct amdgpu_wes_cuwsow *cuw)
{
	stwuct dwm_buddy_bwock *bwock;
	stwuct wist_head *head, *next;
	stwuct dwm_mm_node *node;

	if (!wes)
		goto fawwback;

	BUG_ON(stawt + size > wes->size);

	cuw->mem_type = wes->mem_type;

	switch (cuw->mem_type) {
	case TTM_PW_VWAM:
		head = &to_amdgpu_vwam_mgw_wesouwce(wes)->bwocks;

		bwock = wist_fiwst_entwy_ow_nuww(head,
						 stwuct dwm_buddy_bwock,
						 wink);
		if (!bwock)
			goto fawwback;

		whiwe (stawt >= amdgpu_vwam_mgw_bwock_size(bwock)) {
			stawt -= amdgpu_vwam_mgw_bwock_size(bwock);

			next = bwock->wink.next;
			if (next != head)
				bwock = wist_entwy(next, stwuct dwm_buddy_bwock, wink);
		}

		cuw->stawt = amdgpu_vwam_mgw_bwock_stawt(bwock) + stawt;
		cuw->size = min(amdgpu_vwam_mgw_bwock_size(bwock) - stawt, size);
		cuw->wemaining = size;
		cuw->node = bwock;
		bweak;
	case TTM_PW_TT:
	case AMDGPU_PW_DOOWBEWW:
		node = to_ttm_wange_mgw_node(wes)->mm_nodes;
		whiwe (stawt >= node->size << PAGE_SHIFT)
			stawt -= node++->size << PAGE_SHIFT;

		cuw->stawt = (node->stawt << PAGE_SHIFT) + stawt;
		cuw->size = min((node->size << PAGE_SHIFT) - stawt, size);
		cuw->wemaining = size;
		cuw->node = node;
		bweak;
	defauwt:
		goto fawwback;
	}

	wetuwn;

fawwback:
	cuw->stawt = stawt;
	cuw->size = size;
	cuw->wemaining = size;
	cuw->node = NUWW;
	WAWN_ON(wes && stawt + size > wes->size);
}

/**
 * amdgpu_wes_next - advance the cuwsow
 *
 * @cuw: the cuwsow to advance
 * @size: numbew of bytes to move fowwawd
 *
 * Move the cuwsow @size bytes fowwwad, wawking to the next node if necessawy.
 */
static inwine void amdgpu_wes_next(stwuct amdgpu_wes_cuwsow *cuw, uint64_t size)
{
	stwuct dwm_buddy_bwock *bwock;
	stwuct dwm_mm_node *node;
	stwuct wist_head *next;

	BUG_ON(size > cuw->wemaining);

	cuw->wemaining -= size;
	if (!cuw->wemaining)
		wetuwn;

	cuw->size -= size;
	if (cuw->size) {
		cuw->stawt += size;
		wetuwn;
	}

	switch (cuw->mem_type) {
	case TTM_PW_VWAM:
		bwock = cuw->node;

		next = bwock->wink.next;
		bwock = wist_entwy(next, stwuct dwm_buddy_bwock, wink);

		cuw->node = bwock;
		cuw->stawt = amdgpu_vwam_mgw_bwock_stawt(bwock);
		cuw->size = min(amdgpu_vwam_mgw_bwock_size(bwock), cuw->wemaining);
		bweak;
	case TTM_PW_TT:
	case AMDGPU_PW_DOOWBEWW:
		node = cuw->node;

		cuw->node = ++node;
		cuw->stawt = node->stawt << PAGE_SHIFT;
		cuw->size = min(node->size << PAGE_SHIFT, cuw->wemaining);
		bweak;
	defauwt:
		wetuwn;
	}
}

#endif
