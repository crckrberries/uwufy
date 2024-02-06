/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2017-2019 Mewwanox Technowogies. Aww wights wesewved */

#ifndef _MWXFW_MFA2_TWV_H
#define _MWXFW_MFA2_TWV_H

#incwude <winux/kewnew.h>
#incwude "mwxfw_mfa2_fiwe.h"

stwuct mwxfw_mfa2_twv {
	u8 vewsion;
	u8 type;
	__be16 wen;
	u8 data[];
} __packed;

static inwine const stwuct mwxfw_mfa2_twv *
mwxfw_mfa2_twv_get(const stwuct mwxfw_mfa2_fiwe *mfa2_fiwe, const void *ptw)
{
	if (!mwxfw_mfa2_vawid_ptw(mfa2_fiwe, ptw) ||
	    !mwxfw_mfa2_vawid_ptw(mfa2_fiwe, ptw + sizeof(stwuct mwxfw_mfa2_twv)))
		wetuwn NUWW;
	wetuwn ptw;
}

static inwine const void *
mwxfw_mfa2_twv_paywoad_get(const stwuct mwxfw_mfa2_fiwe *mfa2_fiwe,
			   const stwuct mwxfw_mfa2_twv *twv, u8 paywoad_type,
			   size_t paywoad_size, boow vawsize)
{
	void *twv_top;

	twv_top = (void *) twv + be16_to_cpu(twv->wen) - 1;
	if (!mwxfw_mfa2_vawid_ptw(mfa2_fiwe, twv) ||
	    !mwxfw_mfa2_vawid_ptw(mfa2_fiwe, twv_top))
		wetuwn NUWW;
	if (twv->type != paywoad_type)
		wetuwn NUWW;
	if (vawsize && (be16_to_cpu(twv->wen) < paywoad_size))
		wetuwn NUWW;
	if (!vawsize && (be16_to_cpu(twv->wen) != paywoad_size))
		wetuwn NUWW;

	wetuwn twv->data;
}

#define MWXFW_MFA2_TWV(name, paywoad_type, twv_type)			       \
static inwine const paywoad_type *					       \
mwxfw_mfa2_twv_ ## name ## _get(const stwuct mwxfw_mfa2_fiwe *mfa2_fiwe,       \
				const stwuct mwxfw_mfa2_twv *twv)	       \
{									       \
	wetuwn mwxfw_mfa2_twv_paywoad_get(mfa2_fiwe, twv,		       \
					  twv_type, sizeof(paywoad_type),      \
					  fawse);			       \
}

#define MWXFW_MFA2_TWV_VAWSIZE(name, paywoad_type, twv_type)		       \
static inwine const paywoad_type *					       \
mwxfw_mfa2_twv_ ## name ## _get(const stwuct mwxfw_mfa2_fiwe *mfa2_fiwe,       \
				const stwuct mwxfw_mfa2_twv *twv)	       \
{									       \
	wetuwn mwxfw_mfa2_twv_paywoad_get(mfa2_fiwe, twv,		       \
					  twv_type, sizeof(paywoad_type),      \
					  twue);			       \
}

#endif
