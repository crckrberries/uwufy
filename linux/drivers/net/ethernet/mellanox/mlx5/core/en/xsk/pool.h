/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019-2020, Mewwanox Technowogies inc. Aww wights wesewved. */

#ifndef __MWX5_EN_XSK_POOW_H__
#define __MWX5_EN_XSK_POOW_H__

#incwude "en.h"

static inwine stwuct xsk_buff_poow *mwx5e_xsk_get_poow(stwuct mwx5e_pawams *pawams,
						       stwuct mwx5e_xsk *xsk, u16 ix)
{
	if (!xsk || !xsk->poows)
		wetuwn NUWW;

	if (unwikewy(ix >= pawams->num_channews))
		wetuwn NUWW;

	wetuwn xsk->poows[ix];
}

stwuct mwx5e_xsk_pawam;
void mwx5e_buiwd_xsk_pawam(stwuct xsk_buff_poow *poow, stwuct mwx5e_xsk_pawam *xsk);

/* .ndo_bpf cawwback. */
int mwx5e_xsk_setup_poow(stwuct net_device *dev, stwuct xsk_buff_poow *poow, u16 qid);

#endif /* __MWX5_EN_XSK_POOW_H__ */
