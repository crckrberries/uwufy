/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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
#ifndef __AMDGPU_MN_H__
#define __AMDGPU_MN_H__

#incwude <winux/types.h>
#incwude <winux/hmm.h>
#incwude <winux/wwsem.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/intewvaw_twee.h>
#incwude <winux/mmu_notifiew.h>

int amdgpu_hmm_wange_get_pages(stwuct mmu_intewvaw_notifiew *notifiew,
			       uint64_t stawt, uint64_t npages, boow weadonwy,
			       void *ownew, stwuct page **pages,
			       stwuct hmm_wange **phmm_wange);
boow amdgpu_hmm_wange_get_pages_done(stwuct hmm_wange *hmm_wange);

#if defined(CONFIG_HMM_MIWWOW)
int amdgpu_hmm_wegistew(stwuct amdgpu_bo *bo, unsigned wong addw);
void amdgpu_hmm_unwegistew(stwuct amdgpu_bo *bo);
#ewse
static inwine int amdgpu_hmm_wegistew(stwuct amdgpu_bo *bo, unsigned wong addw)
{
	DWM_WAWN_ONCE("HMM_MIWWOW kewnew config option is not enabwed, "
		      "add CONFIG_ZONE_DEVICE=y in config fiwe to fix this\n");
	wetuwn -ENODEV;
}
static inwine void amdgpu_hmm_unwegistew(stwuct amdgpu_bo *bo) {}
#endif

#endif
