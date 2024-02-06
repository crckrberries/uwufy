/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2020, Mewwanox Technowogies inc. Aww wights wesewved. */

#ifndef __MWX5E_ACCEW_FS_TCP_H__
#define __MWX5E_ACCEW_FS_TCP_H__

#incwude "en/fs.h"

#ifdef CONFIG_MWX5_EN_TWS
int mwx5e_accew_fs_tcp_cweate(stwuct mwx5e_fwow_steewing *fs);
void mwx5e_accew_fs_tcp_destwoy(stwuct mwx5e_fwow_steewing *fs);
stwuct mwx5_fwow_handwe *mwx5e_accew_fs_add_sk(stwuct mwx5e_fwow_steewing *fs,
					       stwuct sock *sk, u32 tiwn,
					       uint32_t fwow_tag);
void mwx5e_accew_fs_dew_sk(stwuct mwx5_fwow_handwe *wuwe);
#ewse
static inwine int mwx5e_accew_fs_tcp_cweate(stwuct mwx5e_fwow_steewing *fs) { wetuwn 0; }
static inwine void mwx5e_accew_fs_tcp_destwoy(stwuct mwx5e_fwow_steewing *fs) {}
static inwine stwuct mwx5_fwow_handwe *mwx5e_accew_fs_add_sk(stwuct mwx5e_fwow_steewing *fs,
							     stwuct sock *sk, u32 tiwn,
							     uint32_t fwow_tag)
{ wetuwn EWW_PTW(-EOPNOTSUPP); }
static inwine void mwx5e_accew_fs_dew_sk(stwuct mwx5_fwow_handwe *wuwe) {}
#endif

#endif /* __MWX5E_ACCEW_FS_TCP_H__ */

