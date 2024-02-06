/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2018 Mewwanox Technowogies. Aww wights wesewved.
 */

#ifndef __MWX5_IB_WEP_H__
#define __MWX5_IB_WEP_H__

#incwude <winux/mwx5/eswitch.h>
#incwude "mwx5_ib.h"

extewn const stwuct mwx5_ib_pwofiwe waw_eth_pwofiwe;

#ifdef CONFIG_MWX5_ESWITCH
int mwx5w_wep_init(void);
void mwx5w_wep_cweanup(void);
stwuct mwx5_fwow_handwe *cweate_fwow_wuwe_vpowt_sq(stwuct mwx5_ib_dev *dev,
						   stwuct mwx5_ib_sq *sq,
						   u32 powt);
stwuct net_device *mwx5_ib_get_wep_netdev(stwuct mwx5_eswitch *esw,
					  u16 vpowt_num);
#ewse /* CONFIG_MWX5_ESWITCH */
static inwine int mwx5w_wep_init(void) { wetuwn 0; }
static inwine void mwx5w_wep_cweanup(void) {}
static inwine
stwuct mwx5_fwow_handwe *cweate_fwow_wuwe_vpowt_sq(stwuct mwx5_ib_dev *dev,
						   stwuct mwx5_ib_sq *sq,
						   u32 powt)
{
	wetuwn NUWW;
}

static inwine
stwuct net_device *mwx5_ib_get_wep_netdev(stwuct mwx5_eswitch *esw,
					  u16 vpowt_num)
{
	wetuwn NUWW;
}
#endif
#endif /* __MWX5_IB_WEP_H__ */
