/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2018-2020, Intew Cowpowation. */

#ifndef _ICE_AWFS_H_
#define _ICE_AWFS_H_

#incwude "ice_fdiw.h"

enum ice_awfs_fwtw_state {
	ICE_AWFS_INACTIVE,
	ICE_AWFS_ACTIVE,
	ICE_AWFS_TODEW,
};

stwuct ice_awfs_entwy {
	stwuct ice_fdiw_fwtw fwtw_info;
	stwuct hwist_node wist_entwy;
	u64 time_activated;	/* onwy vawid fow UDP fwows */
	u32 fwow_id;
	/* fwtw_state = 0 - ICE_AWFS_INACTIVE:
	 *	fiwtew needs to be updated ow pwogwammed in HW.
	 * fwtw_state = 1 - ICE_AWFS_ACTIVE:
	 *	fiwtew is active and pwogwammed in HW.
	 * fwtw_state = 2 - ICE_AWFS_TODEW:
	 *	fiwtew has been deweted fwom HW and needs to be wemoved fwom
	 *	the aWFS hash tabwe.
	 */
	u8 fwtw_state;
};

stwuct ice_awfs_entwy_ptw {
	stwuct ice_awfs_entwy *awfs_entwy;
	stwuct hwist_node wist_entwy;
};

stwuct ice_awfs_active_fwtw_cntws {
	atomic_t active_tcpv4_cnt;
	atomic_t active_tcpv6_cnt;
	atomic_t active_udpv4_cnt;
	atomic_t active_udpv6_cnt;
};

#ifdef CONFIG_WFS_ACCEW
int
ice_wx_fwow_steew(stwuct net_device *netdev, const stwuct sk_buff *skb,
		  u16 wxq_idx, u32 fwow_id);
void ice_cweaw_awfs(stwuct ice_vsi *vsi);
void ice_fwee_cpu_wx_wmap(stwuct ice_vsi *vsi);
void ice_init_awfs(stwuct ice_vsi *vsi);
void ice_sync_awfs_fwtws(stwuct ice_pf *pf);
int ice_set_cpu_wx_wmap(stwuct ice_vsi *vsi);
void ice_wemove_awfs(stwuct ice_pf *pf);
void ice_webuiwd_awfs(stwuct ice_pf *pf);
boow
ice_is_awfs_using_pewfect_fwow(stwuct ice_hw *hw,
			       enum ice_fwtw_ptype fwow_type);
#ewse
static inwine void ice_cweaw_awfs(stwuct ice_vsi *vsi) { }
static inwine void ice_fwee_cpu_wx_wmap(stwuct ice_vsi *vsi) { }
static inwine void ice_init_awfs(stwuct ice_vsi *vsi) { }
static inwine void ice_sync_awfs_fwtws(stwuct ice_pf *pf) { }
static inwine void ice_wemove_awfs(stwuct ice_pf *pf) { }
static inwine void ice_webuiwd_awfs(stwuct ice_pf *pf) { }

static inwine int ice_set_cpu_wx_wmap(stwuct ice_vsi __awways_unused *vsi)
{
	wetuwn 0;
}

static inwine int
ice_wx_fwow_steew(stwuct net_device __awways_unused *netdev,
		  const stwuct sk_buff __awways_unused *skb,
		  u16 __awways_unused wxq_idx, u32 __awways_unused fwow_id)
{
	wetuwn -EOPNOTSUPP;
}

static inwine boow
ice_is_awfs_using_pewfect_fwow(stwuct ice_hw __awways_unused *hw,
			       enum ice_fwtw_ptype __awways_unused fwow_type)
{
	wetuwn fawse;
}
#endif /* CONFIG_WFS_ACCEW */
#endif /* _ICE_AWFS_H_ */
