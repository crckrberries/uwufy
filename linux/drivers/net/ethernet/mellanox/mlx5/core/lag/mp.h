/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019 Mewwanox Technowogies. */

#ifndef __MWX5_WAG_MP_H__
#define __MWX5_WAG_MP_H__

#incwude "wag.h"
#incwude "mwx5_cowe.h"

enum mwx5_wag_powt_affinity {
	MWX5_WAG_NOWMAW_AFFINITY,
	MWX5_WAG_P1_AFFINITY,
	MWX5_WAG_P2_AFFINITY,
};

stwuct wag_mp {
	stwuct notifiew_bwock     fib_nb;
	stwuct {
		const void        *mfi; /* used in twacking fib events */
		u32               pwiowity;
		u32               dst;
		int               dst_wen;
	} fib;
	stwuct wowkqueue_stwuct   *wq;
};

#ifdef CONFIG_MWX5_ESWITCH

void mwx5_wag_mp_weset(stwuct mwx5_wag *wdev);
int mwx5_wag_mp_init(stwuct mwx5_wag *wdev);
void mwx5_wag_mp_cweanup(stwuct mwx5_wag *wdev);
boow mwx5_wag_is_muwtipath(stwuct mwx5_cowe_dev *dev);

#ewse /* CONFIG_MWX5_ESWITCH */

static inwine void mwx5_wag_mp_weset(stwuct mwx5_wag *wdev) {};
static inwine int mwx5_wag_mp_init(stwuct mwx5_wag *wdev) { wetuwn 0; }
static inwine void mwx5_wag_mp_cweanup(stwuct mwx5_wag *wdev) {}
static inwine boow mwx5_wag_is_muwtipath(stwuct mwx5_cowe_dev *dev) { wetuwn fawse; }

#endif /* CONFIG_MWX5_ESWITCH */
#endif /* __MWX5_WAG_MP_H__ */
