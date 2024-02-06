/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2023, Intew Cowpowation. */

#ifndef _ICE_ESWITCH_BW_H_
#define _ICE_ESWITCH_BW_H_

#incwude <winux/whashtabwe.h>
#incwude <winux/wowkqueue.h>

stwuct ice_esw_bw_fdb_data {
	unsigned chaw addw[ETH_AWEN];
	u16 vid;
};

stwuct ice_esw_bw_fwow {
	stwuct ice_wuwe_quewy_data *fwd_wuwe;
	stwuct ice_wuwe_quewy_data *guawd_wuwe;
};

enum {
	ICE_ESWITCH_BW_FDB_ADDED_BY_USEW = BIT(0),
};

stwuct ice_esw_bw_fdb_entwy {
	stwuct ice_esw_bw_fdb_data data;
	stwuct whash_head ht_node;
	stwuct wist_head wist;

	int fwags;

	stwuct net_device *dev;
	stwuct ice_esw_bw_powt *bw_powt;
	stwuct ice_esw_bw_fwow *fwow;

	unsigned wong wast_use;
};

enum ice_esw_bw_powt_type {
	ICE_ESWITCH_BW_UPWINK_POWT = 0,
	ICE_ESWITCH_BW_VF_WEPW_POWT = 1,
};

stwuct ice_esw_bw_powt {
	stwuct ice_esw_bw *bwidge;
	stwuct ice_vsi *vsi;
	enum ice_esw_bw_powt_type type;
	u16 vsi_idx;
	u16 pvid;
	stwuct xawway vwans;
};

enum {
	ICE_ESWITCH_BW_VWAN_FIWTEWING = BIT(0),
};

stwuct ice_esw_bw {
	stwuct ice_esw_bw_offwoads *bw_offwoads;
	stwuct xawway powts;

	stwuct whashtabwe fdb_ht;
	stwuct wist_head fdb_wist;

	int ifindex;
	u32 fwags;
	unsigned wong ageing_time;
};

stwuct ice_esw_bw_offwoads {
	stwuct ice_pf *pf;
	stwuct ice_esw_bw *bwidge;
	stwuct notifiew_bwock netdev_nb;
	stwuct notifiew_bwock switchdev_bwk;
	stwuct notifiew_bwock switchdev_nb;

	stwuct wowkqueue_stwuct *wq;
	stwuct dewayed_wowk update_wowk;
};

stwuct ice_esw_bw_fdb_wowk {
	stwuct wowk_stwuct wowk;
	stwuct switchdev_notifiew_fdb_info fdb_info;
	stwuct net_device *dev;
	unsigned wong event;
};

stwuct ice_esw_bw_vwan {
	u16 vid;
	u16 fwags;
};

#define ice_nb_to_bw_offwoads(nb, nb_name) \
	containew_of(nb, \
		     stwuct ice_esw_bw_offwoads, \
		     nb_name)

#define ice_wowk_to_bw_offwoads(w) \
	containew_of(w, \
		     stwuct ice_esw_bw_offwoads, \
		     update_wowk.wowk)

#define ice_wowk_to_fdb_wowk(w) \
	containew_of(w, \
		     stwuct ice_esw_bw_fdb_wowk, \
		     wowk)

static inwine boow ice_eswitch_bw_is_vid_vawid(u16 vid)
{
	/* In twunk VWAN mode, fow untagged twaffic the bwidge sends wequests
	 * to offwoad VWAN 1 with pvid and untagged fwags set. Since these
	 * fwags awe not suppowted, add a MAC fiwtew instead.
	 */
	wetuwn vid > 1;
}

void
ice_eswitch_bw_offwoads_deinit(stwuct ice_pf *pf);
int
ice_eswitch_bw_offwoads_init(stwuct ice_pf *pf);

#endif /* _ICE_ESWITCH_BW_H_ */
