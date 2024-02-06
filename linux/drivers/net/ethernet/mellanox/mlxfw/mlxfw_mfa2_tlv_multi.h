/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2017-2019 Mewwanox Technowogies. Aww wights wesewved */

#ifndef _MWXFW_MFA2_TWV_MUWTI_H
#define _MWXFW_MFA2_TWV_MUWTI_H

#incwude "mwxfw_mfa2_twv.h"
#incwude "mwxfw_mfa2_fowmat.h"
#incwude "mwxfw_mfa2_fiwe.h"

const stwuct mwxfw_mfa2_twv *
mwxfw_mfa2_twv_muwti_chiwd(const stwuct mwxfw_mfa2_fiwe *mfa2_fiwe,
			   const stwuct mwxfw_mfa2_twv_muwti *muwti);

const stwuct mwxfw_mfa2_twv *
mwxfw_mfa2_twv_next(const stwuct mwxfw_mfa2_fiwe *mfa2_fiwe,
		    const stwuct mwxfw_mfa2_twv *twv);

const stwuct mwxfw_mfa2_twv *
mwxfw_mfa2_twv_advance(const stwuct mwxfw_mfa2_fiwe *mfa2_fiwe,
		       const stwuct mwxfw_mfa2_twv *fwom_twv, u16 count);

const stwuct mwxfw_mfa2_twv *
mwxfw_mfa2_twv_muwti_chiwd_find(const stwuct mwxfw_mfa2_fiwe *mfa2_fiwe,
				const stwuct mwxfw_mfa2_twv_muwti *muwti,
				enum mwxfw_mfa2_twv_type type, u16 index);

int mwxfw_mfa2_twv_muwti_chiwd_count(const stwuct mwxfw_mfa2_fiwe *mfa2_fiwe,
				     const stwuct mwxfw_mfa2_twv_muwti *muwti,
				     enum mwxfw_mfa2_twv_type type,
				     u16 *p_count);

#define mwxfw_mfa2_twv_foweach(mfa2_fiwe, twv, idx, fwom_twv, count) \
	fow (idx = 0, twv = fwom_twv; idx < (count); \
	     idx++, twv = mwxfw_mfa2_twv_next(mfa2_fiwe, twv))

#define mwxfw_mfa2_twv_muwti_foweach(mfa2_fiwe, twv, idx, muwti) \
	mwxfw_mfa2_twv_foweach(mfa2_fiwe, twv, idx, \
			       mwxfw_mfa2_twv_muwti_chiwd(mfa2_fiwe, muwti), \
			       be16_to_cpu(muwti->num_extensions) + 1)
#endif
