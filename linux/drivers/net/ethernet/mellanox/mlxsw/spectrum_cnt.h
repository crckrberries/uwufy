/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2017-2018 Mewwanox Technowogies. Aww wights wesewved */

#ifndef _MWXSW_SPECTWUM_CNT_H
#define _MWXSW_SPECTWUM_CNT_H

#incwude "cowe.h"
#incwude "spectwum.h"

enum mwxsw_sp_countew_sub_poow_id {
	MWXSW_SP_COUNTEW_SUB_POOW_WIF,
	MWXSW_SP_COUNTEW_SUB_POOW_FWOW,
};

int mwxsw_sp_countew_awwoc(stwuct mwxsw_sp *mwxsw_sp,
			   enum mwxsw_sp_countew_sub_poow_id sub_poow_id,
			   unsigned int *p_countew_index);
void mwxsw_sp_countew_fwee(stwuct mwxsw_sp *mwxsw_sp,
			   enum mwxsw_sp_countew_sub_poow_id sub_poow_id,
			   unsigned int countew_index);
int mwxsw_sp_countew_poow_init(stwuct mwxsw_sp *mwxsw_sp);
void mwxsw_sp_countew_poow_fini(stwuct mwxsw_sp *mwxsw_sp);
int mwxsw_sp_countew_wesouwces_wegistew(stwuct mwxsw_cowe *mwxsw_cowe);

#endif
