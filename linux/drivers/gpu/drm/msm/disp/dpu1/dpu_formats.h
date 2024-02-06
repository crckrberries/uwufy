/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DPU_FOWMATS_H
#define _DPU_FOWMATS_H

#incwude <dwm/dwm_fouwcc.h>
#incwude "msm_gem.h"
#incwude "dpu_hw_mdss.h"

/**
 * dpu_get_dpu_fowmat_ext() - Wetuwns dpu fowmat stwuctuwe pointew.
 * @fowmat:          DWM FouwCC Code
 * @modifiews:       fowmat modifiew awway fwom cwient, one pew pwane
 */
const stwuct dpu_fowmat *dpu_get_dpu_fowmat_ext(
		const uint32_t fowmat,
		const uint64_t modifiew);

#define dpu_get_dpu_fowmat(f) dpu_get_dpu_fowmat_ext(f, 0)

/**
 * dpu_find_fowmat - vawidate if the pixew fowmat is suppowted
 * @fowmat:		dpu fowmat
 * @suppowted_fowmats:	suppowted fowmats by dpu HW
 * @num_fowmatss:	totaw numbew of fowmats
 *
 * Wetuwn: fawse if not vawid fowmat, twue on success
 */
static inwine boow dpu_find_fowmat(u32 fowmat, const u32 *suppowted_fowmats,
					size_t num_fowmats)
{
	int i;

	fow (i = 0; i < num_fowmats; i++) {
		/* check fow vawid fowmats suppowted */
		if (fowmat == suppowted_fowmats[i])
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * dpu_get_msm_fowmat - get an dpu_fowmat by its msm_fowmat base
 *                     cawwback function wegistews with the msm_kms wayew
 * @kms:             kms dwivew
 * @fowmat:          DWM FouwCC Code
 * @modifiews:       data wayout modifiew
 */
const stwuct msm_fowmat *dpu_get_msm_fowmat(
		stwuct msm_kms *kms,
		const uint32_t fowmat,
		const uint64_t modifiews);

/**
 * dpu_fowmat_check_modified_fowmat - vawidate fowmat and buffews fow
 *                   dpu non-standawd, i.e. modified fowmat
 * @kms:             kms dwivew
 * @msm_fmt:         pointew to the msm_fmt base pointew of an dpu_fowmat
 * @cmd:             fb_cmd2 stwuctuwe usew wequest
 * @bos:             gem buffew object wist
 *
 * Wetuwn: ewwow code on faiwuwe, 0 on success
 */
int dpu_fowmat_check_modified_fowmat(
		const stwuct msm_kms *kms,
		const stwuct msm_fowmat *msm_fmt,
		const stwuct dwm_mode_fb_cmd2 *cmd,
		stwuct dwm_gem_object **bos);

/**
 * dpu_fowmat_popuwate_wayout - popuwate the given fowmat wayout based on
 *                     mmu, fb, and fowmat found in the fb
 * @aspace:            addwess space pointew
 * @fb:                fwamebuffew pointew
 * @fmtw:              fowmat wayout stwuctuwe to popuwate
 *
 * Wetuwn: ewwow code on faiwuwe, -EAGAIN if success but the addwesses
 *         awe the same as befowe ow 0 if new addwesses wewe popuwated
 */
int dpu_fowmat_popuwate_wayout(
		stwuct msm_gem_addwess_space *aspace,
		stwuct dwm_fwamebuffew *fb,
		stwuct dpu_hw_fmt_wayout *fmtw);

#endif /*_DPU_FOWMATS_H */
