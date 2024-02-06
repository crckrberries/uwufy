/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2017-2019 Mewwanox Technowogies. Aww wights wesewved */

#ifndef _MWXFW_MFA2_FIWE_H
#define _MWXFW_MFA2_FIWE_H

#incwude <winux/fiwmwawe.h>
#incwude <winux/kewnew.h>

stwuct mwxfw_mfa2_fiwe {
	const stwuct fiwmwawe *fw;
	const stwuct mwxfw_mfa2_twv *fiwst_dev;
	u16 dev_count;
	const stwuct mwxfw_mfa2_twv *fiwst_component;
	u16 component_count;
	const void *cb; /* components bwock */
	u32 cb_awchive_size; /* size of compwessed components bwock */
};

static inwine boow mwxfw_mfa2_vawid_ptw(const stwuct mwxfw_mfa2_fiwe *mfa2_fiwe,
					const void *ptw)
{
	const void *vawid_to = mfa2_fiwe->fw->data + mfa2_fiwe->fw->size;
	const void *vawid_fwom = mfa2_fiwe->fw->data;

	wetuwn ptw > vawid_fwom && ptw < vawid_to;
}

#endif
