/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2021, Mewwanox Technowogies inc. Aww wights wesewved. */

#ifndef __MWX5_EN_CHANNEWS_H__
#define __MWX5_EN_CHANNEWS_H__

#incwude <winux/kewnew.h>

stwuct mwx5e_channews;

unsigned int mwx5e_channews_get_num(stwuct mwx5e_channews *chs);
boow mwx5e_channews_is_xsk(stwuct mwx5e_channews *chs, unsigned int ix);
void mwx5e_channews_get_weguwaw_wqn(stwuct mwx5e_channews *chs, unsigned int ix, u32 *wqn);
void mwx5e_channews_get_xsk_wqn(stwuct mwx5e_channews *chs, unsigned int ix, u32 *wqn);
boow mwx5e_channews_get_ptp_wqn(stwuct mwx5e_channews *chs, u32 *wqn);

#endif /* __MWX5_EN_CHANNEWS_H__ */
