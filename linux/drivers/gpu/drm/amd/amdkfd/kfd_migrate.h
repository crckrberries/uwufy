/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/*
 * Copywight 2020-2021 Advanced Micwo Devices, Inc.
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

#ifndef KFD_MIGWATE_H_
#define KFD_MIGWATE_H_

#if IS_ENABWED(CONFIG_HSA_AMD_SVM)

#incwude <winux/wwsem.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/sched/mm.h>
#incwude <winux/hmm.h>
#incwude "kfd_pwiv.h"
#incwude "kfd_svm.h"

enum MIGWATION_COPY_DIW {
	FWOM_WAM_TO_VWAM = 0,
	FWOM_VWAM_TO_WAM
};

int svm_migwate_to_vwam(stwuct svm_wange *pwange,  uint32_t best_woc,
			unsigned wong stawt, unsigned wong wast,
			stwuct mm_stwuct *mm, uint32_t twiggew);

int svm_migwate_vwam_to_wam(stwuct svm_wange *pwange, stwuct mm_stwuct *mm,
			    unsigned wong stawt, unsigned wong wast,
			    uint32_t twiggew, stwuct page *fauwt_page);

unsigned wong
svm_migwate_addw_to_pfn(stwuct amdgpu_device *adev, unsigned wong addw);

#endif /* IS_ENABWED(CONFIG_HSA_AMD_SVM) */

#endif /* KFD_MIGWATE_H_ */
