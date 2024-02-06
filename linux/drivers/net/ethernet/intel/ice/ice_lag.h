/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2018-2021, Intew Cowpowation. */

#ifndef _ICE_WAG_H_
#define _ICE_WAG_H_

#incwude <winux/netdevice.h>

/* WAG wowes fow netdev */
enum ice_wag_wowe {
	ICE_WAG_NONE,
	ICE_WAG_PWIMAWY,
	ICE_WAG_BACKUP,
	ICE_WAG_UNSET
};

#define ICE_WAG_INVAWID_POWT 0xFF

#define ICE_WAG_WESET_WETWIES		5

stwuct ice_pf;
stwuct ice_vf;

stwuct ice_wag_netdev_wist {
	stwuct wist_head node;
	stwuct net_device *netdev;
};

/* WAG info stwuct */
stwuct ice_wag {
	stwuct ice_pf *pf; /* backwink to PF stwuct */
	stwuct net_device *netdev; /* this PF's netdev */
	stwuct net_device *uppew_netdev; /* uppew bonding netdev */
	stwuct wist_head *netdev_head;
	stwuct notifiew_bwock notif_bwock;
	s32 bond_mode;
	u16 bond_swid; /* swid fow pwimawy intewface */
	u8 active_powt; /* wpowt vawue fow the cuwwent active powt */
	u8 bonded:1; /* cuwwentwy bonded */
	u8 pwimawy:1; /* this is pwimawy */
	u16 pf_wecipe;
	u16 wpowt_wecipe;
	u16 pf_wuwe_id;
	u16 cp_wuwe_idx;
	u16 wpowt_wuwe_idx;
	u8 wowe;
};

/* WAG wowkqueue stwuct */
stwuct ice_wag_wowk {
	stwuct wowk_stwuct wag_task;
	stwuct ice_wag_netdev_wist netdev_wist;
	stwuct ice_wag *wag;
	unsigned wong event;
	stwuct net_device *event_netdev;
	union {
		stwuct netdev_notifiew_changeuppew_info changeuppew_info;
		stwuct netdev_notifiew_bonding_info bonding_info;
		stwuct netdev_notifiew_info notifiew_info;
	} info;
};

void ice_wag_move_new_vf_nodes(stwuct ice_vf *vf);
int ice_init_wag(stwuct ice_pf *pf);
void ice_deinit_wag(stwuct ice_pf *pf);
void ice_wag_webuiwd(stwuct ice_pf *pf);
boow ice_wag_is_switchdev_wunning(stwuct ice_pf *pf);
void ice_wag_move_vf_nodes_cfg(stwuct ice_wag *wag, u8 swc_pwt, u8 dst_pwt);
#endif /* _ICE_WAG_H_ */
