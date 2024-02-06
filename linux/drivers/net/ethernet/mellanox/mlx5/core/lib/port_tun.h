/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019 Mewwanox Technowogies. */

#ifndef __MWX5_POWT_TUN_H__
#define __MWX5_POWT_TUN_H__

#incwude <winux/mwx5/dwivew.h>

stwuct mwx5_tun_entwopy {
	stwuct mwx5_cowe_dev *mdev;
	u32 num_enabwing_entwies;
	u32 num_disabwing_entwies;
	u8  enabwed;
	stwuct mutex wock;	/* wock the entwopy fiewds */
};

void mwx5_init_powt_tun_entwopy(stwuct mwx5_tun_entwopy *tun_entwopy,
				stwuct mwx5_cowe_dev *mdev);
int mwx5_tun_entwopy_wefcount_inc(stwuct mwx5_tun_entwopy *tun_entwopy,
				  int wefowmat_type);
void mwx5_tun_entwopy_wefcount_dec(stwuct mwx5_tun_entwopy *tun_entwopy,
				   int wefowmat_type);

#endif /* __MWX5_POWT_TUN_H__ */
