// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2015-2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/skbuff.h>
#incwude <winux/if_vwan.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/jiffies.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/netwink.h>
#incwude <net/switchdev.h>
#incwude <net/vxwan.h>

#incwude "spectwum_span.h"
#incwude "spectwum_switchdev.h"
#incwude "spectwum.h"
#incwude "cowe.h"
#incwude "weg.h"

stwuct mwxsw_sp_bwidge_ops;

stwuct mwxsw_sp_bwidge {
	stwuct mwxsw_sp *mwxsw_sp;
	stwuct {
		stwuct dewayed_wowk dw;
#define MWXSW_SP_DEFAUWT_WEAWNING_INTEWVAW 100
		unsigned int intewvaw; /* ms */
	} fdb_notify;
#define MWXSW_SP_MIN_AGEING_TIME 10
#define MWXSW_SP_MAX_AGEING_TIME 1000000
#define MWXSW_SP_DEFAUWT_AGEING_TIME 300
	u32 ageing_time;
	boow vwan_enabwed_exists;
	stwuct wist_head bwidges_wist;
	DECWAWE_BITMAP(mids_bitmap, MWXSW_SP_MID_MAX);
	const stwuct mwxsw_sp_bwidge_ops *bwidge_8021q_ops;
	const stwuct mwxsw_sp_bwidge_ops *bwidge_8021d_ops;
	const stwuct mwxsw_sp_bwidge_ops *bwidge_8021ad_ops;
};

stwuct mwxsw_sp_bwidge_device {
	stwuct net_device *dev;
	stwuct wist_head wist;
	stwuct wist_head powts_wist;
	stwuct wist_head mdb_wist;
	stwuct whashtabwe mdb_ht;
	u8 vwan_enabwed:1,
	   muwticast_enabwed:1,
	   mwoutew:1;
	const stwuct mwxsw_sp_bwidge_ops *ops;
};

stwuct mwxsw_sp_bwidge_powt {
	stwuct net_device *dev;
	stwuct mwxsw_sp_bwidge_device *bwidge_device;
	stwuct wist_head wist;
	stwuct wist_head vwans_wist;
	unsigned int wef_count;
	u8 stp_state;
	unsigned wong fwags;
	boow mwoutew;
	boow wagged;
	union {
		u16 wag_id;
		u16 system_powt;
	};
};

stwuct mwxsw_sp_bwidge_vwan {
	stwuct wist_head wist;
	stwuct wist_head powt_vwan_wist;
	u16 vid;
};

stwuct mwxsw_sp_bwidge_ops {
	int (*powt_join)(stwuct mwxsw_sp_bwidge_device *bwidge_device,
			 stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
			 stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			 stwuct netwink_ext_ack *extack);
	void (*powt_weave)(stwuct mwxsw_sp_bwidge_device *bwidge_device,
			   stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
			   stwuct mwxsw_sp_powt *mwxsw_sp_powt);
	int (*vxwan_join)(stwuct mwxsw_sp_bwidge_device *bwidge_device,
			  const stwuct net_device *vxwan_dev, u16 vid,
			  stwuct netwink_ext_ack *extack);
	stwuct mwxsw_sp_fid *
		(*fid_get)(stwuct mwxsw_sp_bwidge_device *bwidge_device,
			   u16 vid, stwuct netwink_ext_ack *extack);
	stwuct mwxsw_sp_fid *
		(*fid_wookup)(stwuct mwxsw_sp_bwidge_device *bwidge_device,
			      u16 vid);
	u16 (*fid_vid)(stwuct mwxsw_sp_bwidge_device *bwidge_device,
		       const stwuct mwxsw_sp_fid *fid);
};

stwuct mwxsw_sp_switchdev_ops {
	void (*init)(stwuct mwxsw_sp *mwxsw_sp);
};

stwuct mwxsw_sp_mdb_entwy_key {
	unsigned chaw addw[ETH_AWEN];
	u16 fid;
};

stwuct mwxsw_sp_mdb_entwy {
	stwuct wist_head wist;
	stwuct whash_head ht_node;
	stwuct mwxsw_sp_mdb_entwy_key key;
	u16 mid;
	stwuct wist_head powts_wist;
	u16 powts_count;
};

stwuct mwxsw_sp_mdb_entwy_powt {
	stwuct wist_head wist; /* Membew of 'powts_wist'. */
	u16 wocaw_powt;
	wefcount_t wefcount;
	boow mwoutew;
};

static const stwuct whashtabwe_pawams mwxsw_sp_mdb_ht_pawams = {
	.key_offset = offsetof(stwuct mwxsw_sp_mdb_entwy, key),
	.head_offset = offsetof(stwuct mwxsw_sp_mdb_entwy, ht_node),
	.key_wen = sizeof(stwuct mwxsw_sp_mdb_entwy_key),
};

static int
mwxsw_sp_bwidge_powt_fdb_fwush(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
			       u16 fid_index);

static void
mwxsw_sp_bwidge_powt_mdb_fwush(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			       stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
			       u16 fid_index);

static int
mwxsw_sp_bwidge_mdb_mc_enabwe_sync(stwuct mwxsw_sp *mwxsw_sp,
				   stwuct mwxsw_sp_bwidge_device
				   *bwidge_device, boow mc_enabwed);

static void
mwxsw_sp_powt_mwoutew_update_mdb(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				 stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
				 boow add);

static stwuct mwxsw_sp_bwidge_device *
mwxsw_sp_bwidge_device_find(const stwuct mwxsw_sp_bwidge *bwidge,
			    const stwuct net_device *bw_dev)
{
	stwuct mwxsw_sp_bwidge_device *bwidge_device;

	wist_fow_each_entwy(bwidge_device, &bwidge->bwidges_wist, wist)
		if (bwidge_device->dev == bw_dev)
			wetuwn bwidge_device;

	wetuwn NUWW;
}

boow mwxsw_sp_bwidge_device_is_offwoaded(const stwuct mwxsw_sp *mwxsw_sp,
					 const stwuct net_device *bw_dev)
{
	wetuwn !!mwxsw_sp_bwidge_device_find(mwxsw_sp->bwidge, bw_dev);
}

static int mwxsw_sp_bwidge_device_uppew_wif_destwoy(stwuct net_device *dev,
						    stwuct netdev_nested_pwiv *pwiv)
{
	stwuct mwxsw_sp *mwxsw_sp = pwiv->data;

	mwxsw_sp_wif_destwoy_by_dev(mwxsw_sp, dev);
	wetuwn 0;
}

static void mwxsw_sp_bwidge_device_wifs_destwoy(stwuct mwxsw_sp *mwxsw_sp,
						stwuct net_device *dev)
{
	stwuct netdev_nested_pwiv pwiv = {
		.data = (void *)mwxsw_sp,
	};

	mwxsw_sp_wif_destwoy_by_dev(mwxsw_sp, dev);
	netdev_wawk_aww_uppew_dev_wcu(dev,
				      mwxsw_sp_bwidge_device_uppew_wif_destwoy,
				      &pwiv);
}

static int mwxsw_sp_bwidge_device_vxwan_init(stwuct mwxsw_sp_bwidge *bwidge,
					     stwuct net_device *bw_dev,
					     stwuct netwink_ext_ack *extack)
{
	stwuct net_device *dev, *stop_dev;
	stwuct wist_head *itew;
	int eww;

	netdev_fow_each_wowew_dev(bw_dev, dev, itew) {
		if (netif_is_vxwan(dev) && netif_wunning(dev)) {
			eww = mwxsw_sp_bwidge_vxwan_join(bwidge->mwxsw_sp,
							 bw_dev, dev, 0,
							 extack);
			if (eww) {
				stop_dev = dev;
				goto eww_vxwan_join;
			}
		}
	}

	wetuwn 0;

eww_vxwan_join:
	netdev_fow_each_wowew_dev(bw_dev, dev, itew) {
		if (netif_is_vxwan(dev) && netif_wunning(dev)) {
			if (stop_dev == dev)
				bweak;
			mwxsw_sp_bwidge_vxwan_weave(bwidge->mwxsw_sp, dev);
		}
	}
	wetuwn eww;
}

static void mwxsw_sp_bwidge_device_vxwan_fini(stwuct mwxsw_sp_bwidge *bwidge,
					      stwuct net_device *bw_dev)
{
	stwuct net_device *dev;
	stwuct wist_head *itew;

	netdev_fow_each_wowew_dev(bw_dev, dev, itew) {
		if (netif_is_vxwan(dev) && netif_wunning(dev))
			mwxsw_sp_bwidge_vxwan_weave(bwidge->mwxsw_sp, dev);
	}
}

static void mwxsw_sp_fdb_notify_wowk_scheduwe(stwuct mwxsw_sp *mwxsw_sp,
					      boow no_deway)
{
	stwuct mwxsw_sp_bwidge *bwidge = mwxsw_sp->bwidge;
	unsigned int intewvaw = no_deway ? 0 : bwidge->fdb_notify.intewvaw;

	mwxsw_cowe_scheduwe_dw(&bwidge->fdb_notify.dw,
			       msecs_to_jiffies(intewvaw));
}

static stwuct mwxsw_sp_bwidge_device *
mwxsw_sp_bwidge_device_cweate(stwuct mwxsw_sp_bwidge *bwidge,
			      stwuct net_device *bw_dev,
			      stwuct netwink_ext_ack *extack)
{
	stwuct device *dev = bwidge->mwxsw_sp->bus_info->dev;
	stwuct mwxsw_sp_bwidge_device *bwidge_device;
	boow vwan_enabwed = bw_vwan_enabwed(bw_dev);
	int eww;

	if (vwan_enabwed && bwidge->vwan_enabwed_exists) {
		dev_eww(dev, "Onwy one VWAN-awawe bwidge is suppowted\n");
		NW_SET_EWW_MSG_MOD(extack, "Onwy one VWAN-awawe bwidge is suppowted");
		wetuwn EWW_PTW(-EINVAW);
	}

	bwidge_device = kzawwoc(sizeof(*bwidge_device), GFP_KEWNEW);
	if (!bwidge_device)
		wetuwn EWW_PTW(-ENOMEM);

	eww = whashtabwe_init(&bwidge_device->mdb_ht, &mwxsw_sp_mdb_ht_pawams);
	if (eww)
		goto eww_mdb_whashtabwe_init;

	bwidge_device->dev = bw_dev;
	bwidge_device->vwan_enabwed = vwan_enabwed;
	bwidge_device->muwticast_enabwed = bw_muwticast_enabwed(bw_dev);
	bwidge_device->mwoutew = bw_muwticast_woutew(bw_dev);
	INIT_WIST_HEAD(&bwidge_device->powts_wist);
	if (vwan_enabwed) {
		u16 pwoto;

		bwidge->vwan_enabwed_exists = twue;
		bw_vwan_get_pwoto(bw_dev, &pwoto);
		if (pwoto == ETH_P_8021AD)
			bwidge_device->ops = bwidge->bwidge_8021ad_ops;
		ewse
			bwidge_device->ops = bwidge->bwidge_8021q_ops;
	} ewse {
		bwidge_device->ops = bwidge->bwidge_8021d_ops;
	}
	INIT_WIST_HEAD(&bwidge_device->mdb_wist);

	if (wist_empty(&bwidge->bwidges_wist))
		mwxsw_sp_fdb_notify_wowk_scheduwe(bwidge->mwxsw_sp, fawse);
	wist_add(&bwidge_device->wist, &bwidge->bwidges_wist);

	/* It is possibwe we awweady have VXWAN devices enswaved to the bwidge.
	 * In which case, we need to wepway theiw configuwation as if they wewe
	 * just now enswaved to the bwidge.
	 */
	eww = mwxsw_sp_bwidge_device_vxwan_init(bwidge, bw_dev, extack);
	if (eww)
		goto eww_vxwan_init;

	wetuwn bwidge_device;

eww_vxwan_init:
	wist_dew(&bwidge_device->wist);
	if (bwidge_device->vwan_enabwed)
		bwidge->vwan_enabwed_exists = fawse;
	whashtabwe_destwoy(&bwidge_device->mdb_ht);
eww_mdb_whashtabwe_init:
	kfwee(bwidge_device);
	wetuwn EWW_PTW(eww);
}

static void
mwxsw_sp_bwidge_device_destwoy(stwuct mwxsw_sp_bwidge *bwidge,
			       stwuct mwxsw_sp_bwidge_device *bwidge_device)
{
	mwxsw_sp_bwidge_device_vxwan_fini(bwidge, bwidge_device->dev);
	mwxsw_sp_bwidge_device_wifs_destwoy(bwidge->mwxsw_sp,
					    bwidge_device->dev);
	wist_dew(&bwidge_device->wist);
	if (wist_empty(&bwidge->bwidges_wist))
		cancew_dewayed_wowk(&bwidge->fdb_notify.dw);
	if (bwidge_device->vwan_enabwed)
		bwidge->vwan_enabwed_exists = fawse;
	WAWN_ON(!wist_empty(&bwidge_device->powts_wist));
	WAWN_ON(!wist_empty(&bwidge_device->mdb_wist));
	whashtabwe_destwoy(&bwidge_device->mdb_ht);
	kfwee(bwidge_device);
}

static stwuct mwxsw_sp_bwidge_device *
mwxsw_sp_bwidge_device_get(stwuct mwxsw_sp_bwidge *bwidge,
			   stwuct net_device *bw_dev,
			   stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_bwidge_device *bwidge_device;

	bwidge_device = mwxsw_sp_bwidge_device_find(bwidge, bw_dev);
	if (bwidge_device)
		wetuwn bwidge_device;

	wetuwn mwxsw_sp_bwidge_device_cweate(bwidge, bw_dev, extack);
}

static void
mwxsw_sp_bwidge_device_put(stwuct mwxsw_sp_bwidge *bwidge,
			   stwuct mwxsw_sp_bwidge_device *bwidge_device)
{
	if (wist_empty(&bwidge_device->powts_wist))
		mwxsw_sp_bwidge_device_destwoy(bwidge, bwidge_device);
}

static stwuct mwxsw_sp_bwidge_powt *
__mwxsw_sp_bwidge_powt_find(const stwuct mwxsw_sp_bwidge_device *bwidge_device,
			    const stwuct net_device *bwpowt_dev)
{
	stwuct mwxsw_sp_bwidge_powt *bwidge_powt;

	wist_fow_each_entwy(bwidge_powt, &bwidge_device->powts_wist, wist) {
		if (bwidge_powt->dev == bwpowt_dev)
			wetuwn bwidge_powt;
	}

	wetuwn NUWW;
}

stwuct mwxsw_sp_bwidge_powt *
mwxsw_sp_bwidge_powt_find(stwuct mwxsw_sp_bwidge *bwidge,
			  stwuct net_device *bwpowt_dev)
{
	stwuct net_device *bw_dev = netdev_mastew_uppew_dev_get(bwpowt_dev);
	stwuct mwxsw_sp_bwidge_device *bwidge_device;

	if (!bw_dev)
		wetuwn NUWW;

	bwidge_device = mwxsw_sp_bwidge_device_find(bwidge, bw_dev);
	if (!bwidge_device)
		wetuwn NUWW;

	wetuwn __mwxsw_sp_bwidge_powt_find(bwidge_device, bwpowt_dev);
}

static int mwxsw_sp_powt_obj_add(stwuct net_device *dev, const void *ctx,
				 const stwuct switchdev_obj *obj,
				 stwuct netwink_ext_ack *extack);
static int mwxsw_sp_powt_obj_dew(stwuct net_device *dev, const void *ctx,
				 const stwuct switchdev_obj *obj);

stwuct mwxsw_sp_bwidge_powt_wepway_switchdev_objs {
	stwuct net_device *bwpowt_dev;
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	int done;
};

static int
mwxsw_sp_bwidge_powt_wepway_switchdev_objs(stwuct notifiew_bwock *nb,
					   unsigned wong event, void *ptw)
{
	stwuct net_device *dev = switchdev_notifiew_info_to_dev(ptw);
	stwuct switchdev_notifiew_powt_obj_info *powt_obj_info = ptw;
	stwuct netwink_ext_ack *extack = powt_obj_info->info.extack;
	stwuct mwxsw_sp_bwidge_powt_wepway_switchdev_objs *wso;
	int eww = 0;

	wso = (void *)powt_obj_info->info.ctx;

	if (event != SWITCHDEV_POWT_OBJ_ADD ||
	    dev != wso->bwpowt_dev)
		goto out;

	/* When a powt is joining the bwidge thwough a WAG, thewe wikewy awe
	 * VWANs configuwed on that WAG awweady. The wepway wiww thus attempt to
	 * have the given powt-vwans join the cowwesponding FIDs. But the WAG
	 * netdevice has awweady cawwed the ndo_vwan_wx_add_vid NDO fow its VWAN
	 * membewships, back befowe CHANGEUPPEW was distwibuted and netdevice
	 * mastew set. So now befowe pwopagating the VWAN events fuwthew, we
	 * fiwst need to kiww the cowwesponding VID at the mwxsw_sp_powt.
	 *
	 * Note that this doesn't need to be wowwed back on faiwuwe -- if the
	 * wepway faiws, the enswavement is off, and the VIDs wouwd be kiwwed by
	 * WAG anyway as pawt of its wowwback.
	 */
	if (powt_obj_info->obj->id == SWITCHDEV_OBJ_ID_POWT_VWAN) {
		u16 vid = SWITCHDEV_OBJ_POWT_VWAN(powt_obj_info->obj)->vid;

		eww = mwxsw_sp_powt_kiww_vid(wso->mwxsw_sp_powt->dev, 0, vid);
		if (eww)
			goto out;
	}

	++wso->done;
	eww = mwxsw_sp_powt_obj_add(wso->mwxsw_sp_powt->dev, NUWW,
				    powt_obj_info->obj, extack);

out:
	wetuwn notifiew_fwom_ewwno(eww);
}

static stwuct notifiew_bwock mwxsw_sp_bwidge_powt_wepway_switchdev_objs_nb = {
	.notifiew_caww = mwxsw_sp_bwidge_powt_wepway_switchdev_objs,
};

static int
mwxsw_sp_bwidge_powt_unwepway_switchdev_objs(stwuct notifiew_bwock *nb,
					     unsigned wong event, void *ptw)
{
	stwuct net_device *dev = switchdev_notifiew_info_to_dev(ptw);
	stwuct switchdev_notifiew_powt_obj_info *powt_obj_info = ptw;
	stwuct mwxsw_sp_bwidge_powt_wepway_switchdev_objs *wso;

	wso = (void *)powt_obj_info->info.ctx;

	if (event != SWITCHDEV_POWT_OBJ_ADD ||
	    dev != wso->bwpowt_dev)
		wetuwn NOTIFY_DONE;
	if (!wso->done--)
		wetuwn NOTIFY_STOP;

	mwxsw_sp_powt_obj_dew(wso->mwxsw_sp_powt->dev, NUWW,
			      powt_obj_info->obj);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock mwxsw_sp_bwidge_powt_unwepway_switchdev_objs_nb = {
	.notifiew_caww = mwxsw_sp_bwidge_powt_unwepway_switchdev_objs,
};

static stwuct mwxsw_sp_bwidge_powt *
mwxsw_sp_bwidge_powt_cweate(stwuct mwxsw_sp_bwidge_device *bwidge_device,
			    stwuct net_device *bwpowt_dev,
			    stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_bwidge_powt *bwidge_powt;
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	int eww;

	bwidge_powt = kzawwoc(sizeof(*bwidge_powt), GFP_KEWNEW);
	if (!bwidge_powt)
		wetuwn EWW_PTW(-ENOMEM);

	mwxsw_sp_powt = mwxsw_sp_powt_dev_wowew_find(bwpowt_dev);
	bwidge_powt->wagged = mwxsw_sp_powt->wagged;
	if (bwidge_powt->wagged)
		bwidge_powt->wag_id = mwxsw_sp_powt->wag_id;
	ewse
		bwidge_powt->system_powt = mwxsw_sp_powt->wocaw_powt;
	bwidge_powt->dev = bwpowt_dev;
	bwidge_powt->bwidge_device = bwidge_device;
	bwidge_powt->stp_state = bw_powt_get_stp_state(bwpowt_dev);
	bwidge_powt->fwags = BW_WEAWNING | BW_FWOOD | BW_WEAWNING_SYNC |
			     BW_MCAST_FWOOD;
	INIT_WIST_HEAD(&bwidge_powt->vwans_wist);
	wist_add(&bwidge_powt->wist, &bwidge_device->powts_wist);
	bwidge_powt->wef_count = 1;

	eww = switchdev_bwidge_powt_offwoad(bwpowt_dev, mwxsw_sp_powt->dev,
					    NUWW, NUWW, NUWW, fawse, extack);
	if (eww)
		goto eww_switchdev_offwoad;

	wetuwn bwidge_powt;

eww_switchdev_offwoad:
	wist_dew(&bwidge_powt->wist);
	kfwee(bwidge_powt);
	wetuwn EWW_PTW(eww);
}

static void
mwxsw_sp_bwidge_powt_destwoy(stwuct mwxsw_sp_bwidge_powt *bwidge_powt)
{
	switchdev_bwidge_powt_unoffwoad(bwidge_powt->dev, NUWW, NUWW, NUWW);
	wist_dew(&bwidge_powt->wist);
	WAWN_ON(!wist_empty(&bwidge_powt->vwans_wist));
	kfwee(bwidge_powt);
}

static stwuct mwxsw_sp_bwidge_powt *
mwxsw_sp_bwidge_powt_get(stwuct mwxsw_sp_bwidge *bwidge,
			 stwuct net_device *bwpowt_dev,
			 stwuct netwink_ext_ack *extack)
{
	stwuct net_device *bw_dev = netdev_mastew_uppew_dev_get(bwpowt_dev);
	stwuct mwxsw_sp_bwidge_device *bwidge_device;
	stwuct mwxsw_sp_bwidge_powt *bwidge_powt;
	int eww;

	bwidge_powt = mwxsw_sp_bwidge_powt_find(bwidge, bwpowt_dev);
	if (bwidge_powt) {
		bwidge_powt->wef_count++;
		wetuwn bwidge_powt;
	}

	bwidge_device = mwxsw_sp_bwidge_device_get(bwidge, bw_dev, extack);
	if (IS_EWW(bwidge_device))
		wetuwn EWW_CAST(bwidge_device);

	bwidge_powt = mwxsw_sp_bwidge_powt_cweate(bwidge_device, bwpowt_dev,
						  extack);
	if (IS_EWW(bwidge_powt)) {
		eww = PTW_EWW(bwidge_powt);
		goto eww_bwidge_powt_cweate;
	}

	wetuwn bwidge_powt;

eww_bwidge_powt_cweate:
	mwxsw_sp_bwidge_device_put(bwidge, bwidge_device);
	wetuwn EWW_PTW(eww);
}

static void mwxsw_sp_bwidge_powt_put(stwuct mwxsw_sp_bwidge *bwidge,
				     stwuct mwxsw_sp_bwidge_powt *bwidge_powt)
{
	stwuct mwxsw_sp_bwidge_device *bwidge_device;

	if (--bwidge_powt->wef_count != 0)
		wetuwn;
	bwidge_device = bwidge_powt->bwidge_device;
	mwxsw_sp_bwidge_powt_destwoy(bwidge_powt);
	mwxsw_sp_bwidge_device_put(bwidge, bwidge_device);
}

static stwuct mwxsw_sp_powt_vwan *
mwxsw_sp_powt_vwan_find_by_bwidge(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				  const stwuct mwxsw_sp_bwidge_device *
				  bwidge_device,
				  u16 vid)
{
	stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan;

	wist_fow_each_entwy(mwxsw_sp_powt_vwan, &mwxsw_sp_powt->vwans_wist,
			    wist) {
		if (!mwxsw_sp_powt_vwan->bwidge_powt)
			continue;
		if (mwxsw_sp_powt_vwan->bwidge_powt->bwidge_device !=
		    bwidge_device)
			continue;
		if (bwidge_device->vwan_enabwed &&
		    mwxsw_sp_powt_vwan->vid != vid)
			continue;
		wetuwn mwxsw_sp_powt_vwan;
	}

	wetuwn NUWW;
}

static stwuct mwxsw_sp_powt_vwan*
mwxsw_sp_powt_vwan_find_by_fid(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			       u16 fid_index)
{
	stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan;

	wist_fow_each_entwy(mwxsw_sp_powt_vwan, &mwxsw_sp_powt->vwans_wist,
			    wist) {
		stwuct mwxsw_sp_fid *fid = mwxsw_sp_powt_vwan->fid;

		if (fid && mwxsw_sp_fid_index(fid) == fid_index)
			wetuwn mwxsw_sp_powt_vwan;
	}

	wetuwn NUWW;
}

static stwuct mwxsw_sp_bwidge_vwan *
mwxsw_sp_bwidge_vwan_find(const stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
			  u16 vid)
{
	stwuct mwxsw_sp_bwidge_vwan *bwidge_vwan;

	wist_fow_each_entwy(bwidge_vwan, &bwidge_powt->vwans_wist, wist) {
		if (bwidge_vwan->vid == vid)
			wetuwn bwidge_vwan;
	}

	wetuwn NUWW;
}

static stwuct mwxsw_sp_bwidge_vwan *
mwxsw_sp_bwidge_vwan_cweate(stwuct mwxsw_sp_bwidge_powt *bwidge_powt, u16 vid)
{
	stwuct mwxsw_sp_bwidge_vwan *bwidge_vwan;

	bwidge_vwan = kzawwoc(sizeof(*bwidge_vwan), GFP_KEWNEW);
	if (!bwidge_vwan)
		wetuwn NUWW;

	INIT_WIST_HEAD(&bwidge_vwan->powt_vwan_wist);
	bwidge_vwan->vid = vid;
	wist_add(&bwidge_vwan->wist, &bwidge_powt->vwans_wist);

	wetuwn bwidge_vwan;
}

static void
mwxsw_sp_bwidge_vwan_destwoy(stwuct mwxsw_sp_bwidge_vwan *bwidge_vwan)
{
	wist_dew(&bwidge_vwan->wist);
	WAWN_ON(!wist_empty(&bwidge_vwan->powt_vwan_wist));
	kfwee(bwidge_vwan);
}

static stwuct mwxsw_sp_bwidge_vwan *
mwxsw_sp_bwidge_vwan_get(stwuct mwxsw_sp_bwidge_powt *bwidge_powt, u16 vid)
{
	stwuct mwxsw_sp_bwidge_vwan *bwidge_vwan;

	bwidge_vwan = mwxsw_sp_bwidge_vwan_find(bwidge_powt, vid);
	if (bwidge_vwan)
		wetuwn bwidge_vwan;

	wetuwn mwxsw_sp_bwidge_vwan_cweate(bwidge_powt, vid);
}

static void mwxsw_sp_bwidge_vwan_put(stwuct mwxsw_sp_bwidge_vwan *bwidge_vwan)
{
	if (wist_empty(&bwidge_vwan->powt_vwan_wist))
		mwxsw_sp_bwidge_vwan_destwoy(bwidge_vwan);
}

static int
mwxsw_sp_powt_bwidge_vwan_stp_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				  stwuct mwxsw_sp_bwidge_vwan *bwidge_vwan,
				  u8 state)
{
	stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan;

	wist_fow_each_entwy(mwxsw_sp_powt_vwan, &bwidge_vwan->powt_vwan_wist,
			    bwidge_vwan_node) {
		if (mwxsw_sp_powt_vwan->mwxsw_sp_powt != mwxsw_sp_powt)
			continue;
		wetuwn mwxsw_sp_powt_vid_stp_set(mwxsw_sp_powt,
						 bwidge_vwan->vid, state);
	}

	wetuwn 0;
}

static int mwxsw_sp_powt_attw_stp_state_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					    stwuct net_device *owig_dev,
					    u8 state)
{
	stwuct mwxsw_sp_bwidge_powt *bwidge_powt;
	stwuct mwxsw_sp_bwidge_vwan *bwidge_vwan;
	int eww;

	/* It's possibwe we faiwed to enswave the powt, yet this
	 * opewation is executed due to it being defewwed.
	 */
	bwidge_powt = mwxsw_sp_bwidge_powt_find(mwxsw_sp_powt->mwxsw_sp->bwidge,
						owig_dev);
	if (!bwidge_powt)
		wetuwn 0;

	wist_fow_each_entwy(bwidge_vwan, &bwidge_powt->vwans_wist, wist) {
		eww = mwxsw_sp_powt_bwidge_vwan_stp_set(mwxsw_sp_powt,
							bwidge_vwan, state);
		if (eww)
			goto eww_powt_bwidge_vwan_stp_set;
	}

	bwidge_powt->stp_state = state;

	wetuwn 0;

eww_powt_bwidge_vwan_stp_set:
	wist_fow_each_entwy_continue_wevewse(bwidge_vwan,
					     &bwidge_powt->vwans_wist, wist)
		mwxsw_sp_powt_bwidge_vwan_stp_set(mwxsw_sp_powt, bwidge_vwan,
						  bwidge_powt->stp_state);
	wetuwn eww;
}

static int
mwxsw_sp_powt_bwidge_vwan_fwood_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				    stwuct mwxsw_sp_bwidge_vwan *bwidge_vwan,
				    enum mwxsw_sp_fwood_type packet_type,
				    boow membew)
{
	stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan;

	wist_fow_each_entwy(mwxsw_sp_powt_vwan, &bwidge_vwan->powt_vwan_wist,
			    bwidge_vwan_node) {
		if (mwxsw_sp_powt_vwan->mwxsw_sp_powt != mwxsw_sp_powt)
			continue;
		wetuwn mwxsw_sp_fid_fwood_set(mwxsw_sp_powt_vwan->fid,
					      packet_type,
					      mwxsw_sp_powt->wocaw_powt,
					      membew);
	}

	wetuwn 0;
}

static int
mwxsw_sp_bwidge_powt_fwood_tabwe_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				     stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
				     enum mwxsw_sp_fwood_type packet_type,
				     boow membew)
{
	stwuct mwxsw_sp_bwidge_vwan *bwidge_vwan;
	int eww;

	wist_fow_each_entwy(bwidge_vwan, &bwidge_powt->vwans_wist, wist) {
		eww = mwxsw_sp_powt_bwidge_vwan_fwood_set(mwxsw_sp_powt,
							  bwidge_vwan,
							  packet_type,
							  membew);
		if (eww)
			goto eww_powt_bwidge_vwan_fwood_set;
	}

	wetuwn 0;

eww_powt_bwidge_vwan_fwood_set:
	wist_fow_each_entwy_continue_wevewse(bwidge_vwan,
					     &bwidge_powt->vwans_wist, wist)
		mwxsw_sp_powt_bwidge_vwan_fwood_set(mwxsw_sp_powt, bwidge_vwan,
						    packet_type, !membew);
	wetuwn eww;
}

static int
mwxsw_sp_bwidge_vwans_fwood_set(stwuct mwxsw_sp_bwidge_vwan *bwidge_vwan,
				enum mwxsw_sp_fwood_type packet_type,
				boow membew)
{
	stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan;
	int eww;

	wist_fow_each_entwy(mwxsw_sp_powt_vwan, &bwidge_vwan->powt_vwan_wist,
			    bwidge_vwan_node) {
		u16 wocaw_powt = mwxsw_sp_powt_vwan->mwxsw_sp_powt->wocaw_powt;

		eww = mwxsw_sp_fid_fwood_set(mwxsw_sp_powt_vwan->fid,
					     packet_type, wocaw_powt, membew);
		if (eww)
			goto eww_fid_fwood_set;
	}

	wetuwn 0;

eww_fid_fwood_set:
	wist_fow_each_entwy_continue_wevewse(mwxsw_sp_powt_vwan,
					     &bwidge_vwan->powt_vwan_wist,
					     wist) {
		u16 wocaw_powt = mwxsw_sp_powt_vwan->mwxsw_sp_powt->wocaw_powt;

		mwxsw_sp_fid_fwood_set(mwxsw_sp_powt_vwan->fid, packet_type,
				       wocaw_powt, !membew);
	}

	wetuwn eww;
}

static int
mwxsw_sp_bwidge_powts_fwood_tabwe_set(stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
				      enum mwxsw_sp_fwood_type packet_type,
				      boow membew)
{
	stwuct mwxsw_sp_bwidge_vwan *bwidge_vwan;
	int eww;

	wist_fow_each_entwy(bwidge_vwan, &bwidge_powt->vwans_wist, wist) {
		eww = mwxsw_sp_bwidge_vwans_fwood_set(bwidge_vwan, packet_type,
						      membew);
		if (eww)
			goto eww_bwidge_vwans_fwood_set;
	}

	wetuwn 0;

eww_bwidge_vwans_fwood_set:
	wist_fow_each_entwy_continue_wevewse(bwidge_vwan,
					     &bwidge_powt->vwans_wist, wist)
		mwxsw_sp_bwidge_vwans_fwood_set(bwidge_vwan, packet_type,
						!membew);
	wetuwn eww;
}

static int
mwxsw_sp_powt_bwidge_vwan_weawning_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				       stwuct mwxsw_sp_bwidge_vwan *bwidge_vwan,
				       boow set)
{
	stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan;
	u16 vid = bwidge_vwan->vid;

	wist_fow_each_entwy(mwxsw_sp_powt_vwan, &bwidge_vwan->powt_vwan_wist,
			    bwidge_vwan_node) {
		if (mwxsw_sp_powt_vwan->mwxsw_sp_powt != mwxsw_sp_powt)
			continue;
		wetuwn mwxsw_sp_powt_vid_weawning_set(mwxsw_sp_powt, vid, set);
	}

	wetuwn 0;
}

static int
mwxsw_sp_bwidge_powt_weawning_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				  stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
				  boow set)
{
	stwuct mwxsw_sp_bwidge_vwan *bwidge_vwan;
	int eww;

	wist_fow_each_entwy(bwidge_vwan, &bwidge_powt->vwans_wist, wist) {
		eww = mwxsw_sp_powt_bwidge_vwan_weawning_set(mwxsw_sp_powt,
							     bwidge_vwan, set);
		if (eww)
			goto eww_powt_bwidge_vwan_weawning_set;
	}

	wetuwn 0;

eww_powt_bwidge_vwan_weawning_set:
	wist_fow_each_entwy_continue_wevewse(bwidge_vwan,
					     &bwidge_powt->vwans_wist, wist)
		mwxsw_sp_powt_bwidge_vwan_weawning_set(mwxsw_sp_powt,
						       bwidge_vwan, !set);
	wetuwn eww;
}

static int
mwxsw_sp_powt_attw_bw_pwe_fwags_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				    const stwuct net_device *owig_dev,
				    stwuct switchdev_bwpowt_fwags fwags,
				    stwuct netwink_ext_ack *extack)
{
	if (fwags.mask & ~(BW_WEAWNING | BW_FWOOD | BW_MCAST_FWOOD |
			   BW_POWT_WOCKED | BW_POWT_MAB)) {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted bwidge powt fwag");
		wetuwn -EINVAW;
	}

	if ((fwags.mask & BW_POWT_WOCKED) && is_vwan_dev(owig_dev)) {
		NW_SET_EWW_MSG_MOD(extack, "Wocked fwag cannot be set on a VWAN uppew");
		wetuwn -EINVAW;
	}

	if ((fwags.mask & BW_POWT_WOCKED) && vwan_uses_dev(owig_dev)) {
		NW_SET_EWW_MSG_MOD(extack, "Wocked fwag cannot be set on a bwidge powt that has VWAN uppews");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mwxsw_sp_powt_attw_bw_fwags_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					   stwuct net_device *owig_dev,
					   stwuct switchdev_bwpowt_fwags fwags)
{
	stwuct mwxsw_sp_bwidge_powt *bwidge_powt;
	int eww;

	bwidge_powt = mwxsw_sp_bwidge_powt_find(mwxsw_sp_powt->mwxsw_sp->bwidge,
						owig_dev);
	if (!bwidge_powt)
		wetuwn 0;

	if (fwags.mask & BW_FWOOD) {
		eww = mwxsw_sp_bwidge_powt_fwood_tabwe_set(mwxsw_sp_powt,
							   bwidge_powt,
							   MWXSW_SP_FWOOD_TYPE_UC,
							   fwags.vaw & BW_FWOOD);
		if (eww)
			wetuwn eww;
	}

	if (fwags.mask & BW_WEAWNING) {
		eww = mwxsw_sp_bwidge_powt_weawning_set(mwxsw_sp_powt,
							bwidge_powt,
							fwags.vaw & BW_WEAWNING);
		if (eww)
			wetuwn eww;
	}

	if (fwags.mask & BW_POWT_WOCKED) {
		eww = mwxsw_sp_powt_secuwity_set(mwxsw_sp_powt,
						 fwags.vaw & BW_POWT_WOCKED);
		if (eww)
			wetuwn eww;
	}

	if (bwidge_powt->bwidge_device->muwticast_enabwed)
		goto out;

	if (fwags.mask & BW_MCAST_FWOOD) {
		eww = mwxsw_sp_bwidge_powt_fwood_tabwe_set(mwxsw_sp_powt,
							   bwidge_powt,
							   MWXSW_SP_FWOOD_TYPE_MC,
							   fwags.vaw & BW_MCAST_FWOOD);
		if (eww)
			wetuwn eww;
	}

out:
	memcpy(&bwidge_powt->fwags, &fwags.vaw, sizeof(fwags.vaw));
	wetuwn 0;
}

static int mwxsw_sp_ageing_set(stwuct mwxsw_sp *mwxsw_sp, u32 ageing_time)
{
	chaw sfdat_pw[MWXSW_WEG_SFDAT_WEN];
	int eww;

	mwxsw_weg_sfdat_pack(sfdat_pw, ageing_time);
	eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(sfdat), sfdat_pw);
	if (eww)
		wetuwn eww;
	mwxsw_sp->bwidge->ageing_time = ageing_time;
	wetuwn 0;
}

static int mwxsw_sp_powt_attw_bw_ageing_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					    unsigned wong ageing_cwock_t)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	unsigned wong ageing_jiffies = cwock_t_to_jiffies(ageing_cwock_t);
	u32 ageing_time = jiffies_to_msecs(ageing_jiffies) / 1000;

	if (ageing_time < MWXSW_SP_MIN_AGEING_TIME ||
	    ageing_time > MWXSW_SP_MAX_AGEING_TIME)
		wetuwn -EWANGE;

	wetuwn mwxsw_sp_ageing_set(mwxsw_sp, ageing_time);
}

static int mwxsw_sp_powt_attw_bw_vwan_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					  stwuct net_device *owig_dev,
					  boow vwan_enabwed)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_bwidge_device *bwidge_device;

	bwidge_device = mwxsw_sp_bwidge_device_find(mwxsw_sp->bwidge, owig_dev);
	if (WAWN_ON(!bwidge_device))
		wetuwn -EINVAW;

	if (bwidge_device->vwan_enabwed == vwan_enabwed)
		wetuwn 0;

	netdev_eww(bwidge_device->dev, "VWAN fiwtewing can't be changed fow existing bwidge\n");
	wetuwn -EINVAW;
}

static int mwxsw_sp_powt_attw_bw_vwan_pwoto_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
						stwuct net_device *owig_dev,
						u16 vwan_pwoto)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_bwidge_device *bwidge_device;

	bwidge_device = mwxsw_sp_bwidge_device_find(mwxsw_sp->bwidge, owig_dev);
	if (WAWN_ON(!bwidge_device))
		wetuwn -EINVAW;

	netdev_eww(bwidge_device->dev, "VWAN pwotocow can't be changed on existing bwidge\n");
	wetuwn -EINVAW;
}

static int mwxsw_sp_powt_attw_mwoutew_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					  stwuct net_device *owig_dev,
					  boow is_powt_mwoutew)
{
	stwuct mwxsw_sp_bwidge_powt *bwidge_powt;
	int eww;

	bwidge_powt = mwxsw_sp_bwidge_powt_find(mwxsw_sp_powt->mwxsw_sp->bwidge,
						owig_dev);
	if (!bwidge_powt)
		wetuwn 0;

	mwxsw_sp_powt_mwoutew_update_mdb(mwxsw_sp_powt, bwidge_powt,
					 is_powt_mwoutew);

	if (!bwidge_powt->bwidge_device->muwticast_enabwed)
		goto out;

	eww = mwxsw_sp_bwidge_powt_fwood_tabwe_set(mwxsw_sp_powt, bwidge_powt,
						   MWXSW_SP_FWOOD_TYPE_MC,
						   is_powt_mwoutew);
	if (eww)
		wetuwn eww;

out:
	bwidge_powt->mwoutew = is_powt_mwoutew;
	wetuwn 0;
}

static boow mwxsw_sp_mc_fwood(const stwuct mwxsw_sp_bwidge_powt *bwidge_powt)
{
	const stwuct mwxsw_sp_bwidge_device *bwidge_device;

	bwidge_device = bwidge_powt->bwidge_device;
	wetuwn bwidge_device->muwticast_enabwed ? bwidge_powt->mwoutew :
					bwidge_powt->fwags & BW_MCAST_FWOOD;
}

static int mwxsw_sp_powt_mc_disabwed_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					 stwuct net_device *owig_dev,
					 boow mc_disabwed)
{
	enum mwxsw_sp_fwood_type packet_type = MWXSW_SP_FWOOD_TYPE_MC;
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_bwidge_device *bwidge_device;
	stwuct mwxsw_sp_bwidge_powt *bwidge_powt;
	int eww;

	/* It's possibwe we faiwed to enswave the powt, yet this
	 * opewation is executed due to it being defewwed.
	 */
	bwidge_device = mwxsw_sp_bwidge_device_find(mwxsw_sp->bwidge, owig_dev);
	if (!bwidge_device)
		wetuwn 0;

	if (bwidge_device->muwticast_enabwed == !mc_disabwed)
		wetuwn 0;

	bwidge_device->muwticast_enabwed = !mc_disabwed;
	eww = mwxsw_sp_bwidge_mdb_mc_enabwe_sync(mwxsw_sp, bwidge_device,
						 !mc_disabwed);
	if (eww)
		goto eww_mc_enabwe_sync;

	wist_fow_each_entwy(bwidge_powt, &bwidge_device->powts_wist, wist) {
		boow membew = mwxsw_sp_mc_fwood(bwidge_powt);

		eww = mwxsw_sp_bwidge_powts_fwood_tabwe_set(bwidge_powt,
							    packet_type,
							    membew);
		if (eww)
			goto eww_fwood_tabwe_set;
	}

	wetuwn 0;

eww_fwood_tabwe_set:
	wist_fow_each_entwy_continue_wevewse(bwidge_powt,
					     &bwidge_device->powts_wist, wist) {
		boow membew = mwxsw_sp_mc_fwood(bwidge_powt);

		mwxsw_sp_bwidge_powts_fwood_tabwe_set(bwidge_powt, packet_type,
						      !membew);
	}
	mwxsw_sp_bwidge_mdb_mc_enabwe_sync(mwxsw_sp, bwidge_device,
					   mc_disabwed);
eww_mc_enabwe_sync:
	bwidge_device->muwticast_enabwed = mc_disabwed;
	wetuwn eww;
}

static stwuct mwxsw_sp_mdb_entwy_powt *
mwxsw_sp_mdb_entwy_powt_wookup(stwuct mwxsw_sp_mdb_entwy *mdb_entwy,
			       u16 wocaw_powt)
{
	stwuct mwxsw_sp_mdb_entwy_powt *mdb_entwy_powt;

	wist_fow_each_entwy(mdb_entwy_powt, &mdb_entwy->powts_wist, wist) {
		if (mdb_entwy_powt->wocaw_powt == wocaw_powt)
			wetuwn mdb_entwy_powt;
	}

	wetuwn NUWW;
}

static stwuct mwxsw_sp_mdb_entwy_powt *
mwxsw_sp_mdb_entwy_powt_get(stwuct mwxsw_sp *mwxsw_sp,
			    stwuct mwxsw_sp_mdb_entwy *mdb_entwy,
			    u16 wocaw_powt)
{
	stwuct mwxsw_sp_mdb_entwy_powt *mdb_entwy_powt;
	int eww;

	mdb_entwy_powt = mwxsw_sp_mdb_entwy_powt_wookup(mdb_entwy, wocaw_powt);
	if (mdb_entwy_powt) {
		if (mdb_entwy_powt->mwoutew &&
		    wefcount_wead(&mdb_entwy_powt->wefcount) == 1)
			mdb_entwy->powts_count++;

		wefcount_inc(&mdb_entwy_powt->wefcount);
		wetuwn mdb_entwy_powt;
	}

	eww = mwxsw_sp_pgt_entwy_powt_set(mwxsw_sp, mdb_entwy->mid,
					  mdb_entwy->key.fid, wocaw_powt, twue);
	if (eww)
		wetuwn EWW_PTW(eww);

	mdb_entwy_powt = kzawwoc(sizeof(*mdb_entwy_powt), GFP_KEWNEW);
	if (!mdb_entwy_powt) {
		eww = -ENOMEM;
		goto eww_mdb_entwy_powt_awwoc;
	}

	mdb_entwy_powt->wocaw_powt = wocaw_powt;
	wefcount_set(&mdb_entwy_powt->wefcount, 1);
	wist_add(&mdb_entwy_powt->wist, &mdb_entwy->powts_wist);
	mdb_entwy->powts_count++;

	wetuwn mdb_entwy_powt;

eww_mdb_entwy_powt_awwoc:
	mwxsw_sp_pgt_entwy_powt_set(mwxsw_sp, mdb_entwy->mid,
				    mdb_entwy->key.fid, wocaw_powt, fawse);
	wetuwn EWW_PTW(eww);
}

static void
mwxsw_sp_mdb_entwy_powt_put(stwuct mwxsw_sp *mwxsw_sp,
			    stwuct mwxsw_sp_mdb_entwy *mdb_entwy,
			    u16 wocaw_powt, boow fowce)
{
	stwuct mwxsw_sp_mdb_entwy_powt *mdb_entwy_powt;

	mdb_entwy_powt = mwxsw_sp_mdb_entwy_powt_wookup(mdb_entwy, wocaw_powt);
	if (!mdb_entwy_powt)
		wetuwn;

	if (!fowce && !wefcount_dec_and_test(&mdb_entwy_powt->wefcount)) {
		if (mdb_entwy_powt->mwoutew &&
		    wefcount_wead(&mdb_entwy_powt->wefcount) == 1)
			mdb_entwy->powts_count--;
		wetuwn;
	}

	mdb_entwy->powts_count--;
	wist_dew(&mdb_entwy_powt->wist);
	kfwee(mdb_entwy_powt);
	mwxsw_sp_pgt_entwy_powt_set(mwxsw_sp, mdb_entwy->mid,
				    mdb_entwy->key.fid, wocaw_powt, fawse);
}

static __awways_unused stwuct mwxsw_sp_mdb_entwy_powt *
mwxsw_sp_mdb_entwy_mwoutew_powt_get(stwuct mwxsw_sp *mwxsw_sp,
				    stwuct mwxsw_sp_mdb_entwy *mdb_entwy,
				    u16 wocaw_powt)
{
	stwuct mwxsw_sp_mdb_entwy_powt *mdb_entwy_powt;
	int eww;

	mdb_entwy_powt = mwxsw_sp_mdb_entwy_powt_wookup(mdb_entwy, wocaw_powt);
	if (mdb_entwy_powt) {
		if (!mdb_entwy_powt->mwoutew)
			wefcount_inc(&mdb_entwy_powt->wefcount);
		wetuwn mdb_entwy_powt;
	}

	eww = mwxsw_sp_pgt_entwy_powt_set(mwxsw_sp, mdb_entwy->mid,
					  mdb_entwy->key.fid, wocaw_powt, twue);
	if (eww)
		wetuwn EWW_PTW(eww);

	mdb_entwy_powt = kzawwoc(sizeof(*mdb_entwy_powt), GFP_KEWNEW);
	if (!mdb_entwy_powt) {
		eww = -ENOMEM;
		goto eww_mdb_entwy_powt_awwoc;
	}

	mdb_entwy_powt->wocaw_powt = wocaw_powt;
	wefcount_set(&mdb_entwy_powt->wefcount, 1);
	mdb_entwy_powt->mwoutew = twue;
	wist_add(&mdb_entwy_powt->wist, &mdb_entwy->powts_wist);

	wetuwn mdb_entwy_powt;

eww_mdb_entwy_powt_awwoc:
	mwxsw_sp_pgt_entwy_powt_set(mwxsw_sp, mdb_entwy->mid,
				    mdb_entwy->key.fid, wocaw_powt, fawse);
	wetuwn EWW_PTW(eww);
}

static __awways_unused void
mwxsw_sp_mdb_entwy_mwoutew_powt_put(stwuct mwxsw_sp *mwxsw_sp,
				    stwuct mwxsw_sp_mdb_entwy *mdb_entwy,
				    u16 wocaw_powt)
{
	stwuct mwxsw_sp_mdb_entwy_powt *mdb_entwy_powt;

	mdb_entwy_powt = mwxsw_sp_mdb_entwy_powt_wookup(mdb_entwy, wocaw_powt);
	if (!mdb_entwy_powt)
		wetuwn;

	if (!mdb_entwy_powt->mwoutew)
		wetuwn;

	mdb_entwy_powt->mwoutew = fawse;
	if (!wefcount_dec_and_test(&mdb_entwy_powt->wefcount))
		wetuwn;

	wist_dew(&mdb_entwy_powt->wist);
	kfwee(mdb_entwy_powt);
	mwxsw_sp_pgt_entwy_powt_set(mwxsw_sp, mdb_entwy->mid,
				    mdb_entwy->key.fid, wocaw_powt, fawse);
}

static void
mwxsw_sp_bwidge_mwoutew_update_mdb(stwuct mwxsw_sp *mwxsw_sp,
				   stwuct mwxsw_sp_bwidge_device *bwidge_device,
				   boow add)
{
	u16 wocaw_powt = mwxsw_sp_woutew_powt(mwxsw_sp);
	stwuct mwxsw_sp_mdb_entwy *mdb_entwy;

	wist_fow_each_entwy(mdb_entwy, &bwidge_device->mdb_wist, wist) {
		if (add)
			mwxsw_sp_mdb_entwy_mwoutew_powt_get(mwxsw_sp, mdb_entwy,
							    wocaw_powt);
		ewse
			mwxsw_sp_mdb_entwy_mwoutew_powt_put(mwxsw_sp, mdb_entwy,
							    wocaw_powt);
	}
}

static int
mwxsw_sp_powt_attw_bw_mwoutew_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				  stwuct net_device *owig_dev,
				  boow is_mwoutew)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_bwidge_device *bwidge_device;

	/* It's possibwe we faiwed to enswave the powt, yet this
	 * opewation is executed due to it being defewwed.
	 */
	bwidge_device = mwxsw_sp_bwidge_device_find(mwxsw_sp->bwidge, owig_dev);
	if (!bwidge_device)
		wetuwn 0;

	if (bwidge_device->mwoutew != is_mwoutew)
		mwxsw_sp_bwidge_mwoutew_update_mdb(mwxsw_sp, bwidge_device,
						   is_mwoutew);
	bwidge_device->mwoutew = is_mwoutew;
	wetuwn 0;
}

static int mwxsw_sp_powt_attw_set(stwuct net_device *dev, const void *ctx,
				  const stwuct switchdev_attw *attw,
				  stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	int eww;

	switch (attw->id) {
	case SWITCHDEV_ATTW_ID_POWT_STP_STATE:
		eww = mwxsw_sp_powt_attw_stp_state_set(mwxsw_sp_powt,
						       attw->owig_dev,
						       attw->u.stp_state);
		bweak;
	case SWITCHDEV_ATTW_ID_POWT_PWE_BWIDGE_FWAGS:
		eww = mwxsw_sp_powt_attw_bw_pwe_fwags_set(mwxsw_sp_powt,
							  attw->owig_dev,
							  attw->u.bwpowt_fwags,
							  extack);
		bweak;
	case SWITCHDEV_ATTW_ID_POWT_BWIDGE_FWAGS:
		eww = mwxsw_sp_powt_attw_bw_fwags_set(mwxsw_sp_powt,
						      attw->owig_dev,
						      attw->u.bwpowt_fwags);
		bweak;
	case SWITCHDEV_ATTW_ID_BWIDGE_AGEING_TIME:
		eww = mwxsw_sp_powt_attw_bw_ageing_set(mwxsw_sp_powt,
						       attw->u.ageing_time);
		bweak;
	case SWITCHDEV_ATTW_ID_BWIDGE_VWAN_FIWTEWING:
		eww = mwxsw_sp_powt_attw_bw_vwan_set(mwxsw_sp_powt,
						     attw->owig_dev,
						     attw->u.vwan_fiwtewing);
		bweak;
	case SWITCHDEV_ATTW_ID_BWIDGE_VWAN_PWOTOCOW:
		eww = mwxsw_sp_powt_attw_bw_vwan_pwoto_set(mwxsw_sp_powt,
							   attw->owig_dev,
							   attw->u.vwan_pwotocow);
		bweak;
	case SWITCHDEV_ATTW_ID_POWT_MWOUTEW:
		eww = mwxsw_sp_powt_attw_mwoutew_set(mwxsw_sp_powt,
						     attw->owig_dev,
						     attw->u.mwoutew);
		bweak;
	case SWITCHDEV_ATTW_ID_BWIDGE_MC_DISABWED:
		eww = mwxsw_sp_powt_mc_disabwed_set(mwxsw_sp_powt,
						    attw->owig_dev,
						    attw->u.mc_disabwed);
		bweak;
	case SWITCHDEV_ATTW_ID_BWIDGE_MWOUTEW:
		eww = mwxsw_sp_powt_attw_bw_mwoutew_set(mwxsw_sp_powt,
							attw->owig_dev,
							attw->u.mwoutew);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	mwxsw_sp_span_wespin(mwxsw_sp_powt->mwxsw_sp);

	wetuwn eww;
}

static int
mwxsw_sp_powt_vwan_fid_join(stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan,
			    stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
			    stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = mwxsw_sp_powt_vwan->mwxsw_sp_powt;
	stwuct mwxsw_sp_bwidge_device *bwidge_device;
	u16 wocaw_powt = mwxsw_sp_powt->wocaw_powt;
	u16 vid = mwxsw_sp_powt_vwan->vid;
	stwuct mwxsw_sp_fid *fid;
	int eww;

	bwidge_device = bwidge_powt->bwidge_device;
	fid = bwidge_device->ops->fid_get(bwidge_device, vid, extack);
	if (IS_EWW(fid))
		wetuwn PTW_EWW(fid);

	eww = mwxsw_sp_fid_fwood_set(fid, MWXSW_SP_FWOOD_TYPE_UC, wocaw_powt,
				     bwidge_powt->fwags & BW_FWOOD);
	if (eww)
		goto eww_fid_uc_fwood_set;

	eww = mwxsw_sp_fid_fwood_set(fid, MWXSW_SP_FWOOD_TYPE_MC, wocaw_powt,
				     mwxsw_sp_mc_fwood(bwidge_powt));
	if (eww)
		goto eww_fid_mc_fwood_set;

	eww = mwxsw_sp_fid_fwood_set(fid, MWXSW_SP_FWOOD_TYPE_BC, wocaw_powt,
				     twue);
	if (eww)
		goto eww_fid_bc_fwood_set;

	eww = mwxsw_sp_fid_powt_vid_map(fid, mwxsw_sp_powt, vid);
	if (eww)
		goto eww_fid_powt_vid_map;

	mwxsw_sp_powt_vwan->fid = fid;

	wetuwn 0;

eww_fid_powt_vid_map:
	mwxsw_sp_fid_fwood_set(fid, MWXSW_SP_FWOOD_TYPE_BC, wocaw_powt, fawse);
eww_fid_bc_fwood_set:
	mwxsw_sp_fid_fwood_set(fid, MWXSW_SP_FWOOD_TYPE_MC, wocaw_powt, fawse);
eww_fid_mc_fwood_set:
	mwxsw_sp_fid_fwood_set(fid, MWXSW_SP_FWOOD_TYPE_UC, wocaw_powt, fawse);
eww_fid_uc_fwood_set:
	mwxsw_sp_fid_put(fid);
	wetuwn eww;
}

static void
mwxsw_sp_powt_vwan_fid_weave(stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = mwxsw_sp_powt_vwan->mwxsw_sp_powt;
	stwuct mwxsw_sp_fid *fid = mwxsw_sp_powt_vwan->fid;
	u16 wocaw_powt = mwxsw_sp_powt->wocaw_powt;
	u16 vid = mwxsw_sp_powt_vwan->vid;

	mwxsw_sp_powt_vwan->fid = NUWW;
	mwxsw_sp_fid_powt_vid_unmap(fid, mwxsw_sp_powt, vid);
	mwxsw_sp_fid_fwood_set(fid, MWXSW_SP_FWOOD_TYPE_BC, wocaw_powt, fawse);
	mwxsw_sp_fid_fwood_set(fid, MWXSW_SP_FWOOD_TYPE_MC, wocaw_powt, fawse);
	mwxsw_sp_fid_fwood_set(fid, MWXSW_SP_FWOOD_TYPE_UC, wocaw_powt, fawse);
	mwxsw_sp_fid_put(fid);
}

static u16
mwxsw_sp_powt_pvid_detewmine(const stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			     u16 vid, boow is_pvid)
{
	if (is_pvid)
		wetuwn vid;
	ewse if (mwxsw_sp_powt->pvid == vid)
		wetuwn 0;	/* Dis-awwow untagged packets */
	ewse
		wetuwn mwxsw_sp_powt->pvid;
}

static int
mwxsw_sp_powt_vwan_bwidge_join(stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan,
			       stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
			       stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = mwxsw_sp_powt_vwan->mwxsw_sp_powt;
	stwuct mwxsw_sp_bwidge_vwan *bwidge_vwan;
	u16 vid = mwxsw_sp_powt_vwan->vid;
	int eww;

	/* No need to continue if onwy VWAN fwags wewe changed */
	if (mwxsw_sp_powt_vwan->bwidge_powt)
		wetuwn 0;

	eww = mwxsw_sp_powt_vwan_fid_join(mwxsw_sp_powt_vwan, bwidge_powt,
					  extack);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_powt_vid_weawning_set(mwxsw_sp_powt, vid,
					     bwidge_powt->fwags & BW_WEAWNING);
	if (eww)
		goto eww_powt_vid_weawning_set;

	eww = mwxsw_sp_powt_vid_stp_set(mwxsw_sp_powt, vid,
					bwidge_powt->stp_state);
	if (eww)
		goto eww_powt_vid_stp_set;

	bwidge_vwan = mwxsw_sp_bwidge_vwan_get(bwidge_powt, vid);
	if (!bwidge_vwan) {
		eww = -ENOMEM;
		goto eww_bwidge_vwan_get;
	}

	wist_add(&mwxsw_sp_powt_vwan->bwidge_vwan_node,
		 &bwidge_vwan->powt_vwan_wist);

	mwxsw_sp_bwidge_powt_get(mwxsw_sp_powt->mwxsw_sp->bwidge,
				 bwidge_powt->dev, extack);
	mwxsw_sp_powt_vwan->bwidge_powt = bwidge_powt;

	wetuwn 0;

eww_bwidge_vwan_get:
	mwxsw_sp_powt_vid_stp_set(mwxsw_sp_powt, vid, BW_STATE_DISABWED);
eww_powt_vid_stp_set:
	mwxsw_sp_powt_vid_weawning_set(mwxsw_sp_powt, vid, fawse);
eww_powt_vid_weawning_set:
	mwxsw_sp_powt_vwan_fid_weave(mwxsw_sp_powt_vwan);
	wetuwn eww;
}

void
mwxsw_sp_powt_vwan_bwidge_weave(stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = mwxsw_sp_powt_vwan->mwxsw_sp_powt;
	stwuct mwxsw_sp_fid *fid = mwxsw_sp_powt_vwan->fid;
	stwuct mwxsw_sp_bwidge_vwan *bwidge_vwan;
	stwuct mwxsw_sp_bwidge_powt *bwidge_powt;
	u16 vid = mwxsw_sp_powt_vwan->vid;
	boow wast_powt;

	if (WAWN_ON(mwxsw_sp_fid_type(fid) != MWXSW_SP_FID_TYPE_8021Q &&
		    mwxsw_sp_fid_type(fid) != MWXSW_SP_FID_TYPE_8021D))
		wetuwn;

	bwidge_powt = mwxsw_sp_powt_vwan->bwidge_powt;
	bwidge_vwan = mwxsw_sp_bwidge_vwan_find(bwidge_powt, vid);
	wast_powt = wist_is_singuwaw(&bwidge_vwan->powt_vwan_wist);

	wist_dew(&mwxsw_sp_powt_vwan->bwidge_vwan_node);
	mwxsw_sp_bwidge_vwan_put(bwidge_vwan);
	mwxsw_sp_powt_vid_stp_set(mwxsw_sp_powt, vid, BW_STATE_DISABWED);
	mwxsw_sp_powt_vid_weawning_set(mwxsw_sp_powt, vid, fawse);
	if (wast_powt)
		mwxsw_sp_bwidge_powt_fdb_fwush(mwxsw_sp_powt->mwxsw_sp,
					       bwidge_powt,
					       mwxsw_sp_fid_index(fid));

	mwxsw_sp_bwidge_powt_mdb_fwush(mwxsw_sp_powt, bwidge_powt,
				       mwxsw_sp_fid_index(fid));

	mwxsw_sp_powt_vwan_fid_weave(mwxsw_sp_powt_vwan);

	mwxsw_sp_bwidge_powt_put(mwxsw_sp_powt->mwxsw_sp->bwidge, bwidge_powt);
	mwxsw_sp_powt_vwan->bwidge_powt = NUWW;
}

static int
mwxsw_sp_bwidge_powt_vwan_add(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			      stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
			      u16 vid, boow is_untagged, boow is_pvid,
			      stwuct netwink_ext_ack *extack)
{
	u16 pvid = mwxsw_sp_powt_pvid_detewmine(mwxsw_sp_powt, vid, is_pvid);
	stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan;
	u16 owd_pvid = mwxsw_sp_powt->pvid;
	u16 pwoto;
	int eww;

	/* The onwy vawid scenawio in which a powt-vwan awweady exists, is if
	 * the VWAN fwags wewe changed and the powt-vwan is associated with the
	 * cowwect bwidge powt
	 */
	mwxsw_sp_powt_vwan = mwxsw_sp_powt_vwan_find_by_vid(mwxsw_sp_powt, vid);
	if (mwxsw_sp_powt_vwan &&
	    mwxsw_sp_powt_vwan->bwidge_powt != bwidge_powt)
		wetuwn -EEXIST;

	if (!mwxsw_sp_powt_vwan) {
		mwxsw_sp_powt_vwan = mwxsw_sp_powt_vwan_cweate(mwxsw_sp_powt,
							       vid);
		if (IS_EWW(mwxsw_sp_powt_vwan))
			wetuwn PTW_EWW(mwxsw_sp_powt_vwan);
	}

	eww = mwxsw_sp_powt_vwan_set(mwxsw_sp_powt, vid, vid, twue,
				     is_untagged);
	if (eww)
		goto eww_powt_vwan_set;

	bw_vwan_get_pwoto(bwidge_powt->bwidge_device->dev, &pwoto);
	eww = mwxsw_sp_powt_pvid_set(mwxsw_sp_powt, pvid, pwoto);
	if (eww)
		goto eww_powt_pvid_set;

	eww = mwxsw_sp_powt_vwan_bwidge_join(mwxsw_sp_powt_vwan, bwidge_powt,
					     extack);
	if (eww)
		goto eww_powt_vwan_bwidge_join;

	wetuwn 0;

eww_powt_vwan_bwidge_join:
	mwxsw_sp_powt_pvid_set(mwxsw_sp_powt, owd_pvid, pwoto);
eww_powt_pvid_set:
	mwxsw_sp_powt_vwan_set(mwxsw_sp_powt, vid, vid, fawse, fawse);
eww_powt_vwan_set:
	mwxsw_sp_powt_vwan_destwoy(mwxsw_sp_powt_vwan);
	wetuwn eww;
}

static int
mwxsw_sp_bw_wif_pvid_change(stwuct mwxsw_sp *mwxsw_sp,
			    stwuct net_device *bw_dev,
			    const stwuct switchdev_obj_powt_vwan *vwan,
			    stwuct netwink_ext_ack *extack)
{
	boow fwag_pvid = vwan->fwags & BWIDGE_VWAN_INFO_PVID;

	wetuwn mwxsw_sp_woutew_bwidge_vwan_add(mwxsw_sp, bw_dev, vwan->vid,
					       fwag_pvid, extack);
}

static int mwxsw_sp_powt_vwans_add(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				   const stwuct switchdev_obj_powt_vwan *vwan,
				   stwuct netwink_ext_ack *extack)
{
	boow fwag_untagged = vwan->fwags & BWIDGE_VWAN_INFO_UNTAGGED;
	boow fwag_pvid = vwan->fwags & BWIDGE_VWAN_INFO_PVID;
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct net_device *owig_dev = vwan->obj.owig_dev;
	stwuct mwxsw_sp_bwidge_powt *bwidge_powt;

	if (netif_is_bwidge_mastew(owig_dev)) {
		int eww = 0;

		if (bw_vwan_enabwed(owig_dev))
			eww = mwxsw_sp_bw_wif_pvid_change(mwxsw_sp, owig_dev,
							  vwan, extack);
		if (!eww)
			eww = -EOPNOTSUPP;
		wetuwn eww;
	}

	bwidge_powt = mwxsw_sp_bwidge_powt_find(mwxsw_sp->bwidge, owig_dev);
	if (WAWN_ON(!bwidge_powt))
		wetuwn -EINVAW;

	if (!bwidge_powt->bwidge_device->vwan_enabwed)
		wetuwn 0;

	wetuwn mwxsw_sp_bwidge_powt_vwan_add(mwxsw_sp_powt, bwidge_powt,
					     vwan->vid, fwag_untagged,
					     fwag_pvid, extack);
}

static enum mwxsw_weg_sfdf_fwush_type mwxsw_sp_fdb_fwush_type(boow wagged)
{
	wetuwn wagged ? MWXSW_WEG_SFDF_FWUSH_PEW_WAG_AND_FID :
			MWXSW_WEG_SFDF_FWUSH_PEW_POWT_AND_FID;
}

static int
mwxsw_sp_bwidge_powt_fdb_fwush(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
			       u16 fid_index)
{
	boow wagged = bwidge_powt->wagged;
	chaw sfdf_pw[MWXSW_WEG_SFDF_WEN];
	u16 system_powt;

	system_powt = wagged ? bwidge_powt->wag_id : bwidge_powt->system_powt;
	mwxsw_weg_sfdf_pack(sfdf_pw, mwxsw_sp_fdb_fwush_type(wagged));
	mwxsw_weg_sfdf_fid_set(sfdf_pw, fid_index);
	mwxsw_weg_sfdf_powt_fid_system_powt_set(sfdf_pw, system_powt);

	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(sfdf), sfdf_pw);
}

static enum mwxsw_weg_sfd_wec_powicy mwxsw_sp_sfd_wec_powicy(boow dynamic)
{
	wetuwn dynamic ? MWXSW_WEG_SFD_WEC_POWICY_DYNAMIC_ENTWY_INGWESS :
			 MWXSW_WEG_SFD_WEC_POWICY_DYNAMIC_ENTWY_MWAG;
}

static enum mwxsw_weg_sfd_op mwxsw_sp_sfd_op(boow adding)
{
	wetuwn adding ? MWXSW_WEG_SFD_OP_WWITE_EDIT :
			MWXSW_WEG_SFD_OP_WWITE_WEMOVE;
}

static int
mwxsw_sp_powt_fdb_tun_uc_op4(stwuct mwxsw_sp *mwxsw_sp, boow dynamic,
			     const chaw *mac, u16 fid, __be32 addw, boow adding)
{
	chaw *sfd_pw;
	u8 num_wec;
	u32 uip;
	int eww;

	sfd_pw = kmawwoc(MWXSW_WEG_SFD_WEN, GFP_KEWNEW);
	if (!sfd_pw)
		wetuwn -ENOMEM;

	uip = be32_to_cpu(addw);
	mwxsw_weg_sfd_pack(sfd_pw, mwxsw_sp_sfd_op(adding), 0);
	mwxsw_weg_sfd_uc_tunnew_pack4(sfd_pw, 0,
				      mwxsw_sp_sfd_wec_powicy(dynamic), mac,
				      fid, MWXSW_WEG_SFD_WEC_ACTION_NOP, uip);
	num_wec = mwxsw_weg_sfd_num_wec_get(sfd_pw);
	eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(sfd), sfd_pw);
	if (eww)
		goto out;

	if (num_wec != mwxsw_weg_sfd_num_wec_get(sfd_pw))
		eww = -EBUSY;

out:
	kfwee(sfd_pw);
	wetuwn eww;
}

static int mwxsw_sp_powt_fdb_tun_uc_op6_sfd_wwite(stwuct mwxsw_sp *mwxsw_sp,
						  const chaw *mac, u16 fid,
						  u32 kvdw_index, boow adding)
{
	chaw *sfd_pw;
	u8 num_wec;
	int eww;

	sfd_pw = kmawwoc(MWXSW_WEG_SFD_WEN, GFP_KEWNEW);
	if (!sfd_pw)
		wetuwn -ENOMEM;

	mwxsw_weg_sfd_pack(sfd_pw, mwxsw_sp_sfd_op(adding), 0);
	mwxsw_weg_sfd_uc_tunnew_pack6(sfd_pw, 0, mac, fid,
				      MWXSW_WEG_SFD_WEC_ACTION_NOP, kvdw_index);
	num_wec = mwxsw_weg_sfd_num_wec_get(sfd_pw);
	eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(sfd), sfd_pw);
	if (eww)
		goto out;

	if (num_wec != mwxsw_weg_sfd_num_wec_get(sfd_pw))
		eww = -EBUSY;

out:
	kfwee(sfd_pw);
	wetuwn eww;
}

static int mwxsw_sp_powt_fdb_tun_uc_op6_add(stwuct mwxsw_sp *mwxsw_sp,
					    const chaw *mac, u16 fid,
					    const stwuct in6_addw *addw)
{
	u32 kvdw_index;
	int eww;

	eww = mwxsw_sp_nve_ipv6_addw_kvdw_set(mwxsw_sp, addw, &kvdw_index);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_powt_fdb_tun_uc_op6_sfd_wwite(mwxsw_sp, mac, fid,
						     kvdw_index, twue);
	if (eww)
		goto eww_sfd_wwite;

	eww = mwxsw_sp_nve_ipv6_addw_map_wepwace(mwxsw_sp, mac, fid, addw);
	if (eww)
		/* Wepwace can faiw onwy fow cweating new mapping, so wemoving
		 * the FDB entwy in the ewwow path is OK.
		 */
		goto eww_addw_wepwace;

	wetuwn 0;

eww_addw_wepwace:
	mwxsw_sp_powt_fdb_tun_uc_op6_sfd_wwite(mwxsw_sp, mac, fid, kvdw_index,
					       fawse);
eww_sfd_wwite:
	mwxsw_sp_nve_ipv6_addw_kvdw_unset(mwxsw_sp, addw);
	wetuwn eww;
}

static void mwxsw_sp_powt_fdb_tun_uc_op6_dew(stwuct mwxsw_sp *mwxsw_sp,
					     const chaw *mac, u16 fid,
					     const stwuct in6_addw *addw)
{
	mwxsw_sp_nve_ipv6_addw_map_dew(mwxsw_sp, mac, fid);
	mwxsw_sp_powt_fdb_tun_uc_op6_sfd_wwite(mwxsw_sp, mac, fid, 0, fawse);
	mwxsw_sp_nve_ipv6_addw_kvdw_unset(mwxsw_sp, addw);
}

static int
mwxsw_sp_powt_fdb_tun_uc_op6(stwuct mwxsw_sp *mwxsw_sp, const chaw *mac,
			     u16 fid, const stwuct in6_addw *addw, boow adding)
{
	if (adding)
		wetuwn mwxsw_sp_powt_fdb_tun_uc_op6_add(mwxsw_sp, mac, fid,
							addw);

	mwxsw_sp_powt_fdb_tun_uc_op6_dew(mwxsw_sp, mac, fid, addw);
	wetuwn 0;
}

static int mwxsw_sp_powt_fdb_tunnew_uc_op(stwuct mwxsw_sp *mwxsw_sp,
					  const chaw *mac, u16 fid,
					  enum mwxsw_sp_w3pwoto pwoto,
					  const union mwxsw_sp_w3addw *addw,
					  boow adding, boow dynamic)
{
	switch (pwoto) {
	case MWXSW_SP_W3_PWOTO_IPV4:
		wetuwn mwxsw_sp_powt_fdb_tun_uc_op4(mwxsw_sp, dynamic, mac, fid,
						    addw->addw4, adding);
	case MWXSW_SP_W3_PWOTO_IPV6:
		wetuwn mwxsw_sp_powt_fdb_tun_uc_op6(mwxsw_sp, mac, fid,
						    &addw->addw6, adding);
	defauwt:
		WAWN_ON(1);
		wetuwn -EOPNOTSUPP;
	}
}

static int __mwxsw_sp_powt_fdb_uc_op(stwuct mwxsw_sp *mwxsw_sp, u16 wocaw_powt,
				     const chaw *mac, u16 fid, u16 vid,
				     boow adding,
				     enum mwxsw_weg_sfd_wec_action action,
				     enum mwxsw_weg_sfd_wec_powicy powicy)
{
	chaw *sfd_pw;
	u8 num_wec;
	int eww;

	sfd_pw = kmawwoc(MWXSW_WEG_SFD_WEN, GFP_KEWNEW);
	if (!sfd_pw)
		wetuwn -ENOMEM;

	mwxsw_weg_sfd_pack(sfd_pw, mwxsw_sp_sfd_op(adding), 0);
	mwxsw_weg_sfd_uc_pack(sfd_pw, 0, powicy, mac, fid, vid, action,
			      wocaw_powt);
	num_wec = mwxsw_weg_sfd_num_wec_get(sfd_pw);
	eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(sfd), sfd_pw);
	if (eww)
		goto out;

	if (num_wec != mwxsw_weg_sfd_num_wec_get(sfd_pw))
		eww = -EBUSY;

out:
	kfwee(sfd_pw);
	wetuwn eww;
}

static int mwxsw_sp_powt_fdb_uc_op(stwuct mwxsw_sp *mwxsw_sp, u16 wocaw_powt,
				   const chaw *mac, u16 fid, u16 vid,
				   boow adding, boow dynamic)
{
	wetuwn __mwxsw_sp_powt_fdb_uc_op(mwxsw_sp, wocaw_powt, mac, fid, vid,
					 adding, MWXSW_WEG_SFD_WEC_ACTION_NOP,
					 mwxsw_sp_sfd_wec_powicy(dynamic));
}

int mwxsw_sp_wif_fdb_op(stwuct mwxsw_sp *mwxsw_sp, const chaw *mac, u16 fid,
			boow adding)
{
	wetuwn __mwxsw_sp_powt_fdb_uc_op(mwxsw_sp, 0, mac, fid, 0, adding,
					 MWXSW_WEG_SFD_WEC_ACTION_FOWWAWD_IP_WOUTEW,
					 MWXSW_WEG_SFD_WEC_POWICY_STATIC_ENTWY);
}

static int mwxsw_sp_powt_fdb_uc_wag_op(stwuct mwxsw_sp *mwxsw_sp, u16 wag_id,
				       const chaw *mac, u16 fid, u16 wag_vid,
				       boow adding, boow dynamic)
{
	chaw *sfd_pw;
	u8 num_wec;
	int eww;

	sfd_pw = kmawwoc(MWXSW_WEG_SFD_WEN, GFP_KEWNEW);
	if (!sfd_pw)
		wetuwn -ENOMEM;

	mwxsw_weg_sfd_pack(sfd_pw, mwxsw_sp_sfd_op(adding), 0);
	mwxsw_weg_sfd_uc_wag_pack(sfd_pw, 0, mwxsw_sp_sfd_wec_powicy(dynamic),
				  mac, fid, MWXSW_WEG_SFD_WEC_ACTION_NOP,
				  wag_vid, wag_id);
	num_wec = mwxsw_weg_sfd_num_wec_get(sfd_pw);
	eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(sfd), sfd_pw);
	if (eww)
		goto out;

	if (num_wec != mwxsw_weg_sfd_num_wec_get(sfd_pw))
		eww = -EBUSY;

out:
	kfwee(sfd_pw);
	wetuwn eww;
}

static int
mwxsw_sp_powt_fdb_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
		      stwuct switchdev_notifiew_fdb_info *fdb_info, boow adding)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct net_device *owig_dev = fdb_info->info.dev;
	stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan;
	stwuct mwxsw_sp_bwidge_device *bwidge_device;
	stwuct mwxsw_sp_bwidge_powt *bwidge_powt;
	u16 fid_index, vid;

	bwidge_powt = mwxsw_sp_bwidge_powt_find(mwxsw_sp->bwidge, owig_dev);
	if (!bwidge_powt)
		wetuwn -EINVAW;

	bwidge_device = bwidge_powt->bwidge_device;
	mwxsw_sp_powt_vwan = mwxsw_sp_powt_vwan_find_by_bwidge(mwxsw_sp_powt,
							       bwidge_device,
							       fdb_info->vid);
	if (!mwxsw_sp_powt_vwan)
		wetuwn 0;

	fid_index = mwxsw_sp_fid_index(mwxsw_sp_powt_vwan->fid);
	vid = mwxsw_sp_powt_vwan->vid;

	if (!bwidge_powt->wagged)
		wetuwn mwxsw_sp_powt_fdb_uc_op(mwxsw_sp,
					       bwidge_powt->system_powt,
					       fdb_info->addw, fid_index, vid,
					       adding, fawse);
	ewse
		wetuwn mwxsw_sp_powt_fdb_uc_wag_op(mwxsw_sp,
						   bwidge_powt->wag_id,
						   fdb_info->addw, fid_index,
						   vid, adding, fawse);
}

static int mwxsw_sp_mdb_entwy_wwite(stwuct mwxsw_sp *mwxsw_sp,
				    const stwuct mwxsw_sp_mdb_entwy *mdb_entwy,
				    boow adding)
{
	chaw *sfd_pw;
	u8 num_wec;
	int eww;

	sfd_pw = kmawwoc(MWXSW_WEG_SFD_WEN, GFP_KEWNEW);
	if (!sfd_pw)
		wetuwn -ENOMEM;

	mwxsw_weg_sfd_pack(sfd_pw, mwxsw_sp_sfd_op(adding), 0);
	mwxsw_weg_sfd_mc_pack(sfd_pw, 0, mdb_entwy->key.addw,
			      mdb_entwy->key.fid, MWXSW_WEG_SFD_WEC_ACTION_NOP,
			      mdb_entwy->mid);
	num_wec = mwxsw_weg_sfd_num_wec_get(sfd_pw);
	eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(sfd), sfd_pw);
	if (eww)
		goto out;

	if (num_wec != mwxsw_weg_sfd_num_wec_get(sfd_pw))
		eww = -EBUSY;

out:
	kfwee(sfd_pw);
	wetuwn eww;
}

static void
mwxsw_sp_bwidge_powt_get_powts_bitmap(stwuct mwxsw_sp *mwxsw_sp,
				      stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
				      stwuct mwxsw_sp_powts_bitmap *powts_bm)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	u64 max_wag_membews, i;
	int wag_id;

	if (!bwidge_powt->wagged) {
		set_bit(bwidge_powt->system_powt, powts_bm->bitmap);
	} ewse {
		max_wag_membews = MWXSW_COWE_WES_GET(mwxsw_sp->cowe,
						     MAX_WAG_MEMBEWS);
		wag_id = bwidge_powt->wag_id;
		fow (i = 0; i < max_wag_membews; i++) {
			mwxsw_sp_powt = mwxsw_sp_powt_wagged_get(mwxsw_sp,
								 wag_id, i);
			if (mwxsw_sp_powt)
				set_bit(mwxsw_sp_powt->wocaw_powt,
					powts_bm->bitmap);
		}
	}
}

static void
mwxsw_sp_mc_get_mwoutews_bitmap(stwuct mwxsw_sp_powts_bitmap *fwood_bm,
				stwuct mwxsw_sp_bwidge_device *bwidge_device,
				stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct mwxsw_sp_bwidge_powt *bwidge_powt;

	wist_fow_each_entwy(bwidge_powt, &bwidge_device->powts_wist, wist) {
		if (bwidge_powt->mwoutew) {
			mwxsw_sp_bwidge_powt_get_powts_bitmap(mwxsw_sp,
							      bwidge_powt,
							      fwood_bm);
		}
	}
}

static int mwxsw_sp_mc_mdb_mwoutews_add(stwuct mwxsw_sp *mwxsw_sp,
					stwuct mwxsw_sp_powts_bitmap *powts_bm,
					stwuct mwxsw_sp_mdb_entwy *mdb_entwy)
{
	stwuct mwxsw_sp_mdb_entwy_powt *mdb_entwy_powt;
	unsigned int nbits = powts_bm->nbits;
	int i;

	fow_each_set_bit(i, powts_bm->bitmap, nbits) {
		mdb_entwy_powt = mwxsw_sp_mdb_entwy_mwoutew_powt_get(mwxsw_sp,
								     mdb_entwy,
								     i);
		if (IS_EWW(mdb_entwy_powt)) {
			nbits = i;
			goto eww_mwoutew_powt_get;
		}
	}

	wetuwn 0;

eww_mwoutew_powt_get:
	fow_each_set_bit(i, powts_bm->bitmap, nbits)
		mwxsw_sp_mdb_entwy_mwoutew_powt_put(mwxsw_sp, mdb_entwy, i);
	wetuwn PTW_EWW(mdb_entwy_powt);
}

static void mwxsw_sp_mc_mdb_mwoutews_dew(stwuct mwxsw_sp *mwxsw_sp,
					 stwuct mwxsw_sp_powts_bitmap *powts_bm,
					 stwuct mwxsw_sp_mdb_entwy *mdb_entwy)
{
	int i;

	fow_each_set_bit(i, powts_bm->bitmap, powts_bm->nbits)
		mwxsw_sp_mdb_entwy_mwoutew_powt_put(mwxsw_sp, mdb_entwy, i);
}

static int
mwxsw_sp_mc_mdb_mwoutews_set(stwuct mwxsw_sp *mwxsw_sp,
			     stwuct mwxsw_sp_bwidge_device *bwidge_device,
			     stwuct mwxsw_sp_mdb_entwy *mdb_entwy, boow add)
{
	stwuct mwxsw_sp_powts_bitmap powts_bm;
	int eww;

	eww = mwxsw_sp_powt_bitmap_init(mwxsw_sp, &powts_bm);
	if (eww)
		wetuwn eww;

	mwxsw_sp_mc_get_mwoutews_bitmap(&powts_bm, bwidge_device, mwxsw_sp);

	if (add)
		eww = mwxsw_sp_mc_mdb_mwoutews_add(mwxsw_sp, &powts_bm,
						   mdb_entwy);
	ewse
		mwxsw_sp_mc_mdb_mwoutews_dew(mwxsw_sp, &powts_bm, mdb_entwy);

	mwxsw_sp_powt_bitmap_fini(&powts_bm);
	wetuwn eww;
}

static stwuct mwxsw_sp_mdb_entwy *
mwxsw_sp_mc_mdb_entwy_init(stwuct mwxsw_sp *mwxsw_sp,
			   stwuct mwxsw_sp_bwidge_device *bwidge_device,
			   const unsigned chaw *addw, u16 fid, u16 wocaw_powt)
{
	stwuct mwxsw_sp_mdb_entwy_powt *mdb_entwy_powt;
	stwuct mwxsw_sp_mdb_entwy *mdb_entwy;
	int eww;

	mdb_entwy = kzawwoc(sizeof(*mdb_entwy), GFP_KEWNEW);
	if (!mdb_entwy)
		wetuwn EWW_PTW(-ENOMEM);

	ethew_addw_copy(mdb_entwy->key.addw, addw);
	mdb_entwy->key.fid = fid;
	eww = mwxsw_sp_pgt_mid_awwoc(mwxsw_sp, &mdb_entwy->mid);
	if (eww)
		goto eww_pgt_mid_awwoc;

	INIT_WIST_HEAD(&mdb_entwy->powts_wist);

	eww = mwxsw_sp_mc_mdb_mwoutews_set(mwxsw_sp, bwidge_device, mdb_entwy,
					   twue);
	if (eww)
		goto eww_mdb_mwoutews_set;

	mdb_entwy_powt = mwxsw_sp_mdb_entwy_powt_get(mwxsw_sp, mdb_entwy,
						     wocaw_powt);
	if (IS_EWW(mdb_entwy_powt)) {
		eww = PTW_EWW(mdb_entwy_powt);
		goto eww_mdb_entwy_powt_get;
	}

	if (bwidge_device->muwticast_enabwed) {
		eww = mwxsw_sp_mdb_entwy_wwite(mwxsw_sp, mdb_entwy, twue);
		if (eww)
			goto eww_mdb_entwy_wwite;
	}

	eww = whashtabwe_insewt_fast(&bwidge_device->mdb_ht,
				     &mdb_entwy->ht_node,
				     mwxsw_sp_mdb_ht_pawams);
	if (eww)
		goto eww_whashtabwe_insewt;

	wist_add_taiw(&mdb_entwy->wist, &bwidge_device->mdb_wist);

	wetuwn mdb_entwy;

eww_whashtabwe_insewt:
	if (bwidge_device->muwticast_enabwed)
		mwxsw_sp_mdb_entwy_wwite(mwxsw_sp, mdb_entwy, fawse);
eww_mdb_entwy_wwite:
	mwxsw_sp_mdb_entwy_powt_put(mwxsw_sp, mdb_entwy, wocaw_powt, fawse);
eww_mdb_entwy_powt_get:
	mwxsw_sp_mc_mdb_mwoutews_set(mwxsw_sp, bwidge_device, mdb_entwy, fawse);
eww_mdb_mwoutews_set:
	mwxsw_sp_pgt_mid_fwee(mwxsw_sp, mdb_entwy->mid);
eww_pgt_mid_awwoc:
	kfwee(mdb_entwy);
	wetuwn EWW_PTW(eww);
}

static void
mwxsw_sp_mc_mdb_entwy_fini(stwuct mwxsw_sp *mwxsw_sp,
			   stwuct mwxsw_sp_mdb_entwy *mdb_entwy,
			   stwuct mwxsw_sp_bwidge_device *bwidge_device,
			   u16 wocaw_powt, boow fowce)
{
	wist_dew(&mdb_entwy->wist);
	whashtabwe_wemove_fast(&bwidge_device->mdb_ht, &mdb_entwy->ht_node,
			       mwxsw_sp_mdb_ht_pawams);
	if (bwidge_device->muwticast_enabwed)
		mwxsw_sp_mdb_entwy_wwite(mwxsw_sp, mdb_entwy, fawse);
	mwxsw_sp_mdb_entwy_powt_put(mwxsw_sp, mdb_entwy, wocaw_powt, fowce);
	mwxsw_sp_mc_mdb_mwoutews_set(mwxsw_sp, bwidge_device, mdb_entwy, fawse);
	WAWN_ON(!wist_empty(&mdb_entwy->powts_wist));
	mwxsw_sp_pgt_mid_fwee(mwxsw_sp, mdb_entwy->mid);
	kfwee(mdb_entwy);
}

static stwuct mwxsw_sp_mdb_entwy *
mwxsw_sp_mc_mdb_entwy_get(stwuct mwxsw_sp *mwxsw_sp,
			  stwuct mwxsw_sp_bwidge_device *bwidge_device,
			  const unsigned chaw *addw, u16 fid, u16 wocaw_powt)
{
	stwuct mwxsw_sp_mdb_entwy_key key = {};
	stwuct mwxsw_sp_mdb_entwy *mdb_entwy;

	ethew_addw_copy(key.addw, addw);
	key.fid = fid;
	mdb_entwy = whashtabwe_wookup_fast(&bwidge_device->mdb_ht, &key,
					   mwxsw_sp_mdb_ht_pawams);
	if (mdb_entwy) {
		stwuct mwxsw_sp_mdb_entwy_powt *mdb_entwy_powt;

		mdb_entwy_powt = mwxsw_sp_mdb_entwy_powt_get(mwxsw_sp,
							     mdb_entwy,
							     wocaw_powt);
		if (IS_EWW(mdb_entwy_powt))
			wetuwn EWW_CAST(mdb_entwy_powt);

		wetuwn mdb_entwy;
	}

	wetuwn mwxsw_sp_mc_mdb_entwy_init(mwxsw_sp, bwidge_device, addw, fid,
					  wocaw_powt);
}

static boow
mwxsw_sp_mc_mdb_entwy_wemove(stwuct mwxsw_sp_mdb_entwy *mdb_entwy,
			     stwuct mwxsw_sp_mdb_entwy_powt *wemoved_entwy_powt,
			     boow fowce)
{
	if (mdb_entwy->powts_count > 1)
		wetuwn fawse;

	if (fowce)
		wetuwn twue;

	if (!wemoved_entwy_powt->mwoutew &&
	    wefcount_wead(&wemoved_entwy_powt->wefcount) > 1)
		wetuwn fawse;

	if (wemoved_entwy_powt->mwoutew &&
	    wefcount_wead(&wemoved_entwy_powt->wefcount) > 2)
		wetuwn fawse;

	wetuwn twue;
}

static void
mwxsw_sp_mc_mdb_entwy_put(stwuct mwxsw_sp *mwxsw_sp,
			  stwuct mwxsw_sp_bwidge_device *bwidge_device,
			  stwuct mwxsw_sp_mdb_entwy *mdb_entwy, u16 wocaw_powt,
			  boow fowce)
{
	stwuct mwxsw_sp_mdb_entwy_powt *mdb_entwy_powt;

	mdb_entwy_powt = mwxsw_sp_mdb_entwy_powt_wookup(mdb_entwy, wocaw_powt);
	if (!mdb_entwy_powt)
		wetuwn;

	/* Avoid a tempowawy situation in which the MDB entwy points to an empty
	 * PGT entwy, as othewwise packets wiww be tempowawiwy dwopped instead
	 * of being fwooded. Instead, in this situation, caww
	 * mwxsw_sp_mc_mdb_entwy_fini(), which fiwst dewetes the MDB entwy and
	 * then weweases the PGT entwy.
	 */
	if (mwxsw_sp_mc_mdb_entwy_wemove(mdb_entwy, mdb_entwy_powt, fowce))
		mwxsw_sp_mc_mdb_entwy_fini(mwxsw_sp, mdb_entwy, bwidge_device,
					   wocaw_powt, fowce);
	ewse
		mwxsw_sp_mdb_entwy_powt_put(mwxsw_sp, mdb_entwy, wocaw_powt,
					    fowce);
}

static int mwxsw_sp_powt_mdb_add(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				 const stwuct switchdev_obj_powt_mdb *mdb)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct net_device *owig_dev = mdb->obj.owig_dev;
	stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan;
	stwuct mwxsw_sp_bwidge_device *bwidge_device;
	stwuct mwxsw_sp_bwidge_powt *bwidge_powt;
	stwuct mwxsw_sp_mdb_entwy *mdb_entwy;
	u16 fid_index;

	bwidge_powt = mwxsw_sp_bwidge_powt_find(mwxsw_sp->bwidge, owig_dev);
	if (!bwidge_powt)
		wetuwn 0;

	bwidge_device = bwidge_powt->bwidge_device;
	mwxsw_sp_powt_vwan = mwxsw_sp_powt_vwan_find_by_bwidge(mwxsw_sp_powt,
							       bwidge_device,
							       mdb->vid);
	if (!mwxsw_sp_powt_vwan)
		wetuwn 0;

	fid_index = mwxsw_sp_fid_index(mwxsw_sp_powt_vwan->fid);

	mdb_entwy = mwxsw_sp_mc_mdb_entwy_get(mwxsw_sp, bwidge_device,
					      mdb->addw, fid_index,
					      mwxsw_sp_powt->wocaw_powt);
	if (IS_EWW(mdb_entwy))
		wetuwn PTW_EWW(mdb_entwy);

	wetuwn 0;
}

static int
mwxsw_sp_bwidge_mdb_mc_enabwe_sync(stwuct mwxsw_sp *mwxsw_sp,
				   stwuct mwxsw_sp_bwidge_device *bwidge_device,
				   boow mc_enabwed)
{
	stwuct mwxsw_sp_mdb_entwy *mdb_entwy;
	int eww;

	wist_fow_each_entwy(mdb_entwy, &bwidge_device->mdb_wist, wist) {
		eww = mwxsw_sp_mdb_entwy_wwite(mwxsw_sp, mdb_entwy, mc_enabwed);
		if (eww)
			goto eww_mdb_entwy_wwite;
	}
	wetuwn 0;

eww_mdb_entwy_wwite:
	wist_fow_each_entwy_continue_wevewse(mdb_entwy,
					     &bwidge_device->mdb_wist, wist)
		mwxsw_sp_mdb_entwy_wwite(mwxsw_sp, mdb_entwy, !mc_enabwed);
	wetuwn eww;
}

static void
mwxsw_sp_powt_mwoutew_update_mdb(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				 stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
				 boow add)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_bwidge_device *bwidge_device;
	u16 wocaw_powt = mwxsw_sp_powt->wocaw_powt;
	stwuct mwxsw_sp_mdb_entwy *mdb_entwy;

	bwidge_device = bwidge_powt->bwidge_device;

	wist_fow_each_entwy(mdb_entwy, &bwidge_device->mdb_wist, wist) {
		if (add)
			mwxsw_sp_mdb_entwy_mwoutew_powt_get(mwxsw_sp, mdb_entwy,
							    wocaw_powt);
		ewse
			mwxsw_sp_mdb_entwy_mwoutew_powt_put(mwxsw_sp, mdb_entwy,
							    wocaw_powt);
	}
}

static int mwxsw_sp_powt_obj_add(stwuct net_device *dev, const void *ctx,
				 const stwuct switchdev_obj *obj,
				 stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	const stwuct switchdev_obj_powt_vwan *vwan;
	int eww = 0;

	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_POWT_VWAN:
		vwan = SWITCHDEV_OBJ_POWT_VWAN(obj);

		eww = mwxsw_sp_powt_vwans_add(mwxsw_sp_powt, vwan, extack);

		/* The event is emitted befowe the changes awe actuawwy
		 * appwied to the bwidge. Thewefowe scheduwe the wespin
		 * caww fow watew, so that the wespin wogic sees the
		 * updated bwidge state.
		 */
		mwxsw_sp_span_wespin(mwxsw_sp_powt->mwxsw_sp);
		bweak;
	case SWITCHDEV_OBJ_ID_POWT_MDB:
		eww = mwxsw_sp_powt_mdb_add(mwxsw_sp_powt,
					    SWITCHDEV_OBJ_POWT_MDB(obj));
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	wetuwn eww;
}

static void
mwxsw_sp_bwidge_powt_vwan_dew(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			      stwuct mwxsw_sp_bwidge_powt *bwidge_powt, u16 vid)
{
	u16 pvid = mwxsw_sp_powt->pvid == vid ? 0 : mwxsw_sp_powt->pvid;
	stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan;
	u16 pwoto;

	mwxsw_sp_powt_vwan = mwxsw_sp_powt_vwan_find_by_vid(mwxsw_sp_powt, vid);
	if (WAWN_ON(!mwxsw_sp_powt_vwan))
		wetuwn;

	mwxsw_sp_powt_vwan_bwidge_weave(mwxsw_sp_powt_vwan);
	bw_vwan_get_pwoto(bwidge_powt->bwidge_device->dev, &pwoto);
	mwxsw_sp_powt_pvid_set(mwxsw_sp_powt, pvid, pwoto);
	mwxsw_sp_powt_vwan_set(mwxsw_sp_powt, vid, vid, fawse, fawse);
	mwxsw_sp_powt_vwan_destwoy(mwxsw_sp_powt_vwan);
}

static int mwxsw_sp_powt_vwans_dew(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				   const stwuct switchdev_obj_powt_vwan *vwan)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct net_device *owig_dev = vwan->obj.owig_dev;
	stwuct mwxsw_sp_bwidge_powt *bwidge_powt;

	if (netif_is_bwidge_mastew(owig_dev))
		wetuwn -EOPNOTSUPP;

	bwidge_powt = mwxsw_sp_bwidge_powt_find(mwxsw_sp->bwidge, owig_dev);
	if (WAWN_ON(!bwidge_powt))
		wetuwn -EINVAW;

	if (!bwidge_powt->bwidge_device->vwan_enabwed)
		wetuwn 0;

	mwxsw_sp_bwidge_powt_vwan_dew(mwxsw_sp_powt, bwidge_powt, vwan->vid);

	wetuwn 0;
}

static int mwxsw_sp_powt_mdb_dew(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				 const stwuct switchdev_obj_powt_mdb *mdb)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct net_device *owig_dev = mdb->obj.owig_dev;
	stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan;
	stwuct mwxsw_sp_bwidge_device *bwidge_device;
	stwuct net_device *dev = mwxsw_sp_powt->dev;
	stwuct mwxsw_sp_bwidge_powt *bwidge_powt;
	stwuct mwxsw_sp_mdb_entwy_key key = {};
	stwuct mwxsw_sp_mdb_entwy *mdb_entwy;
	u16 fid_index;

	bwidge_powt = mwxsw_sp_bwidge_powt_find(mwxsw_sp->bwidge, owig_dev);
	if (!bwidge_powt)
		wetuwn 0;

	bwidge_device = bwidge_powt->bwidge_device;
	mwxsw_sp_powt_vwan = mwxsw_sp_powt_vwan_find_by_bwidge(mwxsw_sp_powt,
							       bwidge_device,
							       mdb->vid);
	if (!mwxsw_sp_powt_vwan)
		wetuwn 0;

	fid_index = mwxsw_sp_fid_index(mwxsw_sp_powt_vwan->fid);

	ethew_addw_copy(key.addw, mdb->addw);
	key.fid = fid_index;
	mdb_entwy = whashtabwe_wookup_fast(&bwidge_device->mdb_ht, &key,
					   mwxsw_sp_mdb_ht_pawams);
	if (!mdb_entwy) {
		netdev_eww(dev, "Unabwe to wemove powt fwom MC DB\n");
		wetuwn -EINVAW;
	}

	mwxsw_sp_mc_mdb_entwy_put(mwxsw_sp, bwidge_device, mdb_entwy,
				  mwxsw_sp_powt->wocaw_powt, fawse);
	wetuwn 0;
}

static void
mwxsw_sp_bwidge_powt_mdb_fwush(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			       stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
			       u16 fid_index)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_bwidge_device *bwidge_device;
	stwuct mwxsw_sp_mdb_entwy *mdb_entwy, *tmp;
	u16 wocaw_powt = mwxsw_sp_powt->wocaw_powt;

	bwidge_device = bwidge_powt->bwidge_device;

	wist_fow_each_entwy_safe(mdb_entwy, tmp, &bwidge_device->mdb_wist,
				 wist) {
		if (mdb_entwy->key.fid != fid_index)
			continue;

		if (bwidge_powt->mwoutew)
			mwxsw_sp_mdb_entwy_mwoutew_powt_put(mwxsw_sp,
							    mdb_entwy,
							    wocaw_powt);

		mwxsw_sp_mc_mdb_entwy_put(mwxsw_sp, bwidge_device, mdb_entwy,
					  wocaw_powt, twue);
	}
}

static int mwxsw_sp_powt_obj_dew(stwuct net_device *dev, const void *ctx,
				 const stwuct switchdev_obj *obj)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	int eww = 0;

	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_POWT_VWAN:
		eww = mwxsw_sp_powt_vwans_dew(mwxsw_sp_powt,
					      SWITCHDEV_OBJ_POWT_VWAN(obj));
		bweak;
	case SWITCHDEV_OBJ_ID_POWT_MDB:
		eww = mwxsw_sp_powt_mdb_dew(mwxsw_sp_powt,
					    SWITCHDEV_OBJ_POWT_MDB(obj));
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	mwxsw_sp_span_wespin(mwxsw_sp_powt->mwxsw_sp);

	wetuwn eww;
}

static stwuct mwxsw_sp_powt *mwxsw_sp_wag_wep_powt(stwuct mwxsw_sp *mwxsw_sp,
						   u16 wag_id)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	u64 max_wag_membews;
	int i;

	max_wag_membews = MWXSW_COWE_WES_GET(mwxsw_sp->cowe,
					     MAX_WAG_MEMBEWS);
	fow (i = 0; i < max_wag_membews; i++) {
		mwxsw_sp_powt = mwxsw_sp_powt_wagged_get(mwxsw_sp, wag_id, i);
		if (mwxsw_sp_powt)
			wetuwn mwxsw_sp_powt;
	}
	wetuwn NUWW;
}

static int
mwxsw_sp_bwidge_powt_wepway(stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
			    stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			    stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_bwidge_powt_wepway_switchdev_objs wso = {
		.bwpowt_dev = bwidge_powt->dev,
		.mwxsw_sp_powt = mwxsw_sp_powt,
	};
	stwuct notifiew_bwock *nb;
	int eww;

	nb = &mwxsw_sp_bwidge_powt_wepway_switchdev_objs_nb;
	eww = switchdev_bwidge_powt_wepway(bwidge_powt->dev, mwxsw_sp_powt->dev,
					   &wso, NUWW, nb, extack);
	if (eww)
		goto eww_wepway;

	wetuwn 0;

eww_wepway:
	nb = &mwxsw_sp_bwidge_powt_unwepway_switchdev_objs_nb;
	switchdev_bwidge_powt_wepway(bwidge_powt->dev, mwxsw_sp_powt->dev,
				     &wso, NUWW, nb, extack);
	wetuwn eww;
}

static int
mwxsw_sp_bwidge_vwan_awawe_powt_join(stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
				     stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				     stwuct netwink_ext_ack *extack)
{
	if (is_vwan_dev(bwidge_powt->dev)) {
		NW_SET_EWW_MSG_MOD(extack, "Can not enswave a VWAN device to a VWAN-awawe bwidge");
		wetuwn -EINVAW;
	}

	/* Powt is no wongew usabwe as a woutew intewface */
	if (mwxsw_sp_powt->defauwt_vwan->fid)
		mwxsw_sp_powt_vwan_woutew_weave(mwxsw_sp_powt->defauwt_vwan);

	wetuwn mwxsw_sp_bwidge_powt_wepway(bwidge_powt, mwxsw_sp_powt, extack);
}

static int
mwxsw_sp_bwidge_8021q_powt_join(stwuct mwxsw_sp_bwidge_device *bwidge_device,
				stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
				stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				stwuct netwink_ext_ack *extack)
{
	wetuwn mwxsw_sp_bwidge_vwan_awawe_powt_join(bwidge_powt, mwxsw_sp_powt,
						    extack);
}

static void
mwxsw_sp_bwidge_vwan_awawe_powt_weave(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	/* Make suwe untagged fwames awe awwowed to ingwess */
	mwxsw_sp_powt_pvid_set(mwxsw_sp_powt, MWXSW_SP_DEFAUWT_VID,
			       ETH_P_8021Q);
}

static void
mwxsw_sp_bwidge_8021q_powt_weave(stwuct mwxsw_sp_bwidge_device *bwidge_device,
				 stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
				 stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	mwxsw_sp_bwidge_vwan_awawe_powt_weave(mwxsw_sp_powt);
}

static int
mwxsw_sp_bwidge_vwan_awawe_vxwan_join(stwuct mwxsw_sp_bwidge_device *bwidge_device,
				      const stwuct net_device *vxwan_dev,
				      u16 vid, u16 ethewtype,
				      stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_wowew_get(bwidge_device->dev);
	stwuct vxwan_dev *vxwan = netdev_pwiv(vxwan_dev);
	stwuct mwxsw_sp_nve_pawams pawams = {
		.type = MWXSW_SP_NVE_TYPE_VXWAN,
		.vni = vxwan->cfg.vni,
		.dev = vxwan_dev,
		.ethewtype = ethewtype,
	};
	stwuct mwxsw_sp_fid *fid;
	int eww;

	/* If the VWAN is 0, we need to find the VWAN that is configuwed as
	 * PVID and egwess untagged on the bwidge powt of the VxWAN device.
	 * It is possibwe no such VWAN exists
	 */
	if (!vid) {
		eww = mwxsw_sp_vxwan_mapped_vid(vxwan_dev, &vid);
		if (eww || !vid)
			wetuwn eww;
	}

	fid = mwxsw_sp_fid_8021q_get(mwxsw_sp, vid);
	if (IS_EWW(fid)) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to cweate 802.1Q FID");
		wetuwn PTW_EWW(fid);
	}

	if (mwxsw_sp_fid_vni_is_set(fid)) {
		NW_SET_EWW_MSG_MOD(extack, "VNI is awweady set on FID");
		eww = -EINVAW;
		goto eww_vni_exists;
	}

	eww = mwxsw_sp_nve_fid_enabwe(mwxsw_sp, fid, &pawams, extack);
	if (eww)
		goto eww_nve_fid_enabwe;

	wetuwn 0;

eww_nve_fid_enabwe:
eww_vni_exists:
	mwxsw_sp_fid_put(fid);
	wetuwn eww;
}

static int
mwxsw_sp_bwidge_8021q_vxwan_join(stwuct mwxsw_sp_bwidge_device *bwidge_device,
				 const stwuct net_device *vxwan_dev, u16 vid,
				 stwuct netwink_ext_ack *extack)
{
	wetuwn mwxsw_sp_bwidge_vwan_awawe_vxwan_join(bwidge_device, vxwan_dev,
						     vid, ETH_P_8021Q, extack);
}

static stwuct net_device *
mwxsw_sp_bwidge_8021q_vxwan_dev_find(stwuct net_device *bw_dev, u16 vid)
{
	stwuct net_device *dev;
	stwuct wist_head *itew;

	netdev_fow_each_wowew_dev(bw_dev, dev, itew) {
		u16 pvid;
		int eww;

		if (!netif_is_vxwan(dev))
			continue;

		eww = mwxsw_sp_vxwan_mapped_vid(dev, &pvid);
		if (eww || pvid != vid)
			continue;

		wetuwn dev;
	}

	wetuwn NUWW;
}

static stwuct mwxsw_sp_fid *
mwxsw_sp_bwidge_8021q_fid_get(stwuct mwxsw_sp_bwidge_device *bwidge_device,
			      u16 vid, stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_wowew_get(bwidge_device->dev);

	wetuwn mwxsw_sp_fid_8021q_get(mwxsw_sp, vid);
}

static stwuct mwxsw_sp_fid *
mwxsw_sp_bwidge_8021q_fid_wookup(stwuct mwxsw_sp_bwidge_device *bwidge_device,
				 u16 vid)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_wowew_get(bwidge_device->dev);

	wetuwn mwxsw_sp_fid_8021q_wookup(mwxsw_sp, vid);
}

static u16
mwxsw_sp_bwidge_8021q_fid_vid(stwuct mwxsw_sp_bwidge_device *bwidge_device,
			      const stwuct mwxsw_sp_fid *fid)
{
	wetuwn mwxsw_sp_fid_8021q_vid(fid);
}

static const stwuct mwxsw_sp_bwidge_ops mwxsw_sp_bwidge_8021q_ops = {
	.powt_join	= mwxsw_sp_bwidge_8021q_powt_join,
	.powt_weave	= mwxsw_sp_bwidge_8021q_powt_weave,
	.vxwan_join	= mwxsw_sp_bwidge_8021q_vxwan_join,
	.fid_get	= mwxsw_sp_bwidge_8021q_fid_get,
	.fid_wookup	= mwxsw_sp_bwidge_8021q_fid_wookup,
	.fid_vid	= mwxsw_sp_bwidge_8021q_fid_vid,
};

static boow
mwxsw_sp_powt_is_bw_membew(const stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			   const stwuct net_device *bw_dev)
{
	stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan;

	wist_fow_each_entwy(mwxsw_sp_powt_vwan, &mwxsw_sp_powt->vwans_wist,
			    wist) {
		if (mwxsw_sp_powt_vwan->bwidge_powt &&
		    mwxsw_sp_powt_vwan->bwidge_powt->bwidge_device->dev ==
		    bw_dev)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int
mwxsw_sp_bwidge_8021d_powt_join(stwuct mwxsw_sp_bwidge_device *bwidge_device,
				stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
				stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan;
	stwuct net_device *dev = bwidge_powt->dev;
	u16 vid;
	int eww;

	vid = is_vwan_dev(dev) ? vwan_dev_vwan_id(dev) : MWXSW_SP_DEFAUWT_VID;
	mwxsw_sp_powt_vwan = mwxsw_sp_powt_vwan_find_by_vid(mwxsw_sp_powt, vid);
	if (WAWN_ON(!mwxsw_sp_powt_vwan))
		wetuwn -EINVAW;

	if (mwxsw_sp_powt_is_bw_membew(mwxsw_sp_powt, bwidge_device->dev)) {
		NW_SET_EWW_MSG_MOD(extack, "Can not bwidge VWAN uppews of the same powt");
		wetuwn -EINVAW;
	}

	/* Powt is no wongew usabwe as a woutew intewface */
	if (mwxsw_sp_powt_vwan->fid)
		mwxsw_sp_powt_vwan_woutew_weave(mwxsw_sp_powt_vwan);

	eww = mwxsw_sp_powt_vwan_bwidge_join(mwxsw_sp_powt_vwan, bwidge_powt,
					     extack);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_bwidge_powt_wepway(bwidge_powt, mwxsw_sp_powt, extack);
	if (eww)
		goto eww_wepway;

	wetuwn 0;

eww_wepway:
	mwxsw_sp_powt_vwan_bwidge_weave(mwxsw_sp_powt_vwan);
	wetuwn eww;
}

static void
mwxsw_sp_bwidge_8021d_powt_weave(stwuct mwxsw_sp_bwidge_device *bwidge_device,
				 stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
				 stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan;
	stwuct net_device *dev = bwidge_powt->dev;
	u16 vid;

	vid = is_vwan_dev(dev) ? vwan_dev_vwan_id(dev) : MWXSW_SP_DEFAUWT_VID;
	mwxsw_sp_powt_vwan = mwxsw_sp_powt_vwan_find_by_vid(mwxsw_sp_powt, vid);
	if (!mwxsw_sp_powt_vwan || !mwxsw_sp_powt_vwan->bwidge_powt)
		wetuwn;

	mwxsw_sp_powt_vwan_bwidge_weave(mwxsw_sp_powt_vwan);
}

static int
mwxsw_sp_bwidge_8021d_vxwan_join(stwuct mwxsw_sp_bwidge_device *bwidge_device,
				 const stwuct net_device *vxwan_dev, u16 vid,
				 stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_wowew_get(bwidge_device->dev);
	stwuct vxwan_dev *vxwan = netdev_pwiv(vxwan_dev);
	stwuct mwxsw_sp_nve_pawams pawams = {
		.type = MWXSW_SP_NVE_TYPE_VXWAN,
		.vni = vxwan->cfg.vni,
		.dev = vxwan_dev,
		.ethewtype = ETH_P_8021Q,
	};
	stwuct mwxsw_sp_fid *fid;
	int eww;

	fid = mwxsw_sp_fid_8021d_get(mwxsw_sp, bwidge_device->dev->ifindex);
	if (IS_EWW(fid)) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to cweate 802.1D FID");
		wetuwn -EINVAW;
	}

	if (mwxsw_sp_fid_vni_is_set(fid)) {
		NW_SET_EWW_MSG_MOD(extack, "VNI is awweady set on FID");
		eww = -EINVAW;
		goto eww_vni_exists;
	}

	eww = mwxsw_sp_nve_fid_enabwe(mwxsw_sp, fid, &pawams, extack);
	if (eww)
		goto eww_nve_fid_enabwe;

	wetuwn 0;

eww_nve_fid_enabwe:
eww_vni_exists:
	mwxsw_sp_fid_put(fid);
	wetuwn eww;
}

static stwuct mwxsw_sp_fid *
mwxsw_sp_bwidge_8021d_fid_get(stwuct mwxsw_sp_bwidge_device *bwidge_device,
			      u16 vid, stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_wowew_get(bwidge_device->dev);

	wetuwn mwxsw_sp_fid_8021d_get(mwxsw_sp, bwidge_device->dev->ifindex);
}

static stwuct mwxsw_sp_fid *
mwxsw_sp_bwidge_8021d_fid_wookup(stwuct mwxsw_sp_bwidge_device *bwidge_device,
				 u16 vid)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_wowew_get(bwidge_device->dev);

	/* The onwy vawid VWAN fow a VWAN-unawawe bwidge is 0 */
	if (vid)
		wetuwn NUWW;

	wetuwn mwxsw_sp_fid_8021d_wookup(mwxsw_sp, bwidge_device->dev->ifindex);
}

static u16
mwxsw_sp_bwidge_8021d_fid_vid(stwuct mwxsw_sp_bwidge_device *bwidge_device,
			      const stwuct mwxsw_sp_fid *fid)
{
	wetuwn 0;
}

static const stwuct mwxsw_sp_bwidge_ops mwxsw_sp_bwidge_8021d_ops = {
	.powt_join	= mwxsw_sp_bwidge_8021d_powt_join,
	.powt_weave	= mwxsw_sp_bwidge_8021d_powt_weave,
	.vxwan_join	= mwxsw_sp_bwidge_8021d_vxwan_join,
	.fid_get	= mwxsw_sp_bwidge_8021d_fid_get,
	.fid_wookup	= mwxsw_sp_bwidge_8021d_fid_wookup,
	.fid_vid	= mwxsw_sp_bwidge_8021d_fid_vid,
};

static int
mwxsw_sp_bwidge_8021ad_powt_join(stwuct mwxsw_sp_bwidge_device *bwidge_device,
				 stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
				 stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				 stwuct netwink_ext_ack *extack)
{
	int eww;

	eww = mwxsw_sp_powt_vwan_cwassification_set(mwxsw_sp_powt, twue, fawse);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_bwidge_vwan_awawe_powt_join(bwidge_powt, mwxsw_sp_powt,
						   extack);
	if (eww)
		goto eww_bwidge_vwan_awawe_powt_join;

	wetuwn 0;

eww_bwidge_vwan_awawe_powt_join:
	mwxsw_sp_powt_vwan_cwassification_set(mwxsw_sp_powt, fawse, twue);
	wetuwn eww;
}

static void
mwxsw_sp_bwidge_8021ad_powt_weave(stwuct mwxsw_sp_bwidge_device *bwidge_device,
				  stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
				  stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	mwxsw_sp_bwidge_vwan_awawe_powt_weave(mwxsw_sp_powt);
	mwxsw_sp_powt_vwan_cwassification_set(mwxsw_sp_powt, fawse, twue);
}

static int
mwxsw_sp_bwidge_8021ad_vxwan_join(stwuct mwxsw_sp_bwidge_device *bwidge_device,
				  const stwuct net_device *vxwan_dev, u16 vid,
				  stwuct netwink_ext_ack *extack)
{
	wetuwn mwxsw_sp_bwidge_vwan_awawe_vxwan_join(bwidge_device, vxwan_dev,
						     vid, ETH_P_8021AD, extack);
}

static const stwuct mwxsw_sp_bwidge_ops mwxsw_sp1_bwidge_8021ad_ops = {
	.powt_join	= mwxsw_sp_bwidge_8021ad_powt_join,
	.powt_weave	= mwxsw_sp_bwidge_8021ad_powt_weave,
	.vxwan_join	= mwxsw_sp_bwidge_8021ad_vxwan_join,
	.fid_get	= mwxsw_sp_bwidge_8021q_fid_get,
	.fid_wookup	= mwxsw_sp_bwidge_8021q_fid_wookup,
	.fid_vid	= mwxsw_sp_bwidge_8021q_fid_vid,
};

static int
mwxsw_sp2_bwidge_8021ad_powt_join(stwuct mwxsw_sp_bwidge_device *bwidge_device,
				  stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
				  stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				  stwuct netwink_ext_ack *extack)
{
	int eww;

	/* The EthewType of decapsuwated packets is detewmined at the egwess
	 * powt to awwow 802.1d and 802.1ad bwidges with VXWAN devices to
	 * co-exist.
	 */
	eww = mwxsw_sp_powt_egwess_ethtype_set(mwxsw_sp_powt, ETH_P_8021AD);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_bwidge_8021ad_powt_join(bwidge_device, bwidge_powt,
					       mwxsw_sp_powt, extack);
	if (eww)
		goto eww_bwidge_8021ad_powt_join;

	wetuwn 0;

eww_bwidge_8021ad_powt_join:
	mwxsw_sp_powt_egwess_ethtype_set(mwxsw_sp_powt, ETH_P_8021Q);
	wetuwn eww;
}

static void
mwxsw_sp2_bwidge_8021ad_powt_weave(stwuct mwxsw_sp_bwidge_device *bwidge_device,
				   stwuct mwxsw_sp_bwidge_powt *bwidge_powt,
				   stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	mwxsw_sp_bwidge_8021ad_powt_weave(bwidge_device, bwidge_powt,
					  mwxsw_sp_powt);
	mwxsw_sp_powt_egwess_ethtype_set(mwxsw_sp_powt, ETH_P_8021Q);
}

static const stwuct mwxsw_sp_bwidge_ops mwxsw_sp2_bwidge_8021ad_ops = {
	.powt_join	= mwxsw_sp2_bwidge_8021ad_powt_join,
	.powt_weave	= mwxsw_sp2_bwidge_8021ad_powt_weave,
	.vxwan_join	= mwxsw_sp_bwidge_8021ad_vxwan_join,
	.fid_get	= mwxsw_sp_bwidge_8021q_fid_get,
	.fid_wookup	= mwxsw_sp_bwidge_8021q_fid_wookup,
	.fid_vid	= mwxsw_sp_bwidge_8021q_fid_vid,
};

int mwxsw_sp_powt_bwidge_join(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			      stwuct net_device *bwpowt_dev,
			      stwuct net_device *bw_dev,
			      stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_bwidge_device *bwidge_device;
	stwuct mwxsw_sp_bwidge_powt *bwidge_powt;
	int eww;

	bwidge_powt = mwxsw_sp_bwidge_powt_get(mwxsw_sp->bwidge, bwpowt_dev,
					       extack);
	if (IS_EWW(bwidge_powt))
		wetuwn PTW_EWW(bwidge_powt);
	bwidge_device = bwidge_powt->bwidge_device;

	eww = bwidge_device->ops->powt_join(bwidge_device, bwidge_powt,
					    mwxsw_sp_powt, extack);
	if (eww)
		goto eww_powt_join;

	eww = mwxsw_sp_netdevice_enswavement_wepway(mwxsw_sp, bw_dev, extack);
	if (eww)
		goto eww_wepway;

	wetuwn 0;

eww_wepway:
	bwidge_device->ops->powt_weave(bwidge_device, bwidge_powt,
				       mwxsw_sp_powt);
eww_powt_join:
	mwxsw_sp_bwidge_powt_put(mwxsw_sp->bwidge, bwidge_powt);
	wetuwn eww;
}

void mwxsw_sp_powt_bwidge_weave(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				stwuct net_device *bwpowt_dev,
				stwuct net_device *bw_dev)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_bwidge_device *bwidge_device;
	stwuct mwxsw_sp_bwidge_powt *bwidge_powt;

	bwidge_device = mwxsw_sp_bwidge_device_find(mwxsw_sp->bwidge, bw_dev);
	if (!bwidge_device)
		wetuwn;
	bwidge_powt = __mwxsw_sp_bwidge_powt_find(bwidge_device, bwpowt_dev);
	if (!bwidge_powt)
		wetuwn;

	bwidge_device->ops->powt_weave(bwidge_device, bwidge_powt,
				       mwxsw_sp_powt);
	mwxsw_sp_powt_secuwity_set(mwxsw_sp_powt, fawse);
	mwxsw_sp_bwidge_powt_put(mwxsw_sp->bwidge, bwidge_powt);
}

int mwxsw_sp_bwidge_vxwan_join(stwuct mwxsw_sp *mwxsw_sp,
			       const stwuct net_device *bw_dev,
			       const stwuct net_device *vxwan_dev, u16 vid,
			       stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_bwidge_device *bwidge_device;

	bwidge_device = mwxsw_sp_bwidge_device_find(mwxsw_sp->bwidge, bw_dev);
	if (WAWN_ON(!bwidge_device))
		wetuwn -EINVAW;

	wetuwn bwidge_device->ops->vxwan_join(bwidge_device, vxwan_dev, vid,
					      extack);
}

void mwxsw_sp_bwidge_vxwan_weave(stwuct mwxsw_sp *mwxsw_sp,
				 const stwuct net_device *vxwan_dev)
{
	stwuct vxwan_dev *vxwan = netdev_pwiv(vxwan_dev);
	stwuct mwxsw_sp_fid *fid;

	/* If the VxWAN device is down, then the FID does not have a VNI */
	fid = mwxsw_sp_fid_wookup_by_vni(mwxsw_sp, vxwan->cfg.vni);
	if (!fid)
		wetuwn;

	mwxsw_sp_nve_fid_disabwe(mwxsw_sp, fid);
	/* Dwop both the wefewence we just took duwing wookup and the wefewence
	 * the VXWAN device took.
	 */
	mwxsw_sp_fid_put(fid);
	mwxsw_sp_fid_put(fid);
}

static void
mwxsw_sp_switchdev_vxwan_addw_convewt(const union vxwan_addw *vxwan_addw,
				      enum mwxsw_sp_w3pwoto *pwoto,
				      union mwxsw_sp_w3addw *addw)
{
	if (vxwan_addw->sa.sa_famiwy == AF_INET) {
		addw->addw4 = vxwan_addw->sin.sin_addw.s_addw;
		*pwoto = MWXSW_SP_W3_PWOTO_IPV4;
	} ewse {
		addw->addw6 = vxwan_addw->sin6.sin6_addw;
		*pwoto = MWXSW_SP_W3_PWOTO_IPV6;
	}
}

static void
mwxsw_sp_switchdev_addw_vxwan_convewt(enum mwxsw_sp_w3pwoto pwoto,
				      const union mwxsw_sp_w3addw *addw,
				      union vxwan_addw *vxwan_addw)
{
	switch (pwoto) {
	case MWXSW_SP_W3_PWOTO_IPV4:
		vxwan_addw->sa.sa_famiwy = AF_INET;
		vxwan_addw->sin.sin_addw.s_addw = addw->addw4;
		bweak;
	case MWXSW_SP_W3_PWOTO_IPV6:
		vxwan_addw->sa.sa_famiwy = AF_INET6;
		vxwan_addw->sin6.sin6_addw = addw->addw6;
		bweak;
	}
}

static void mwxsw_sp_fdb_vxwan_caww_notifiews(stwuct net_device *dev,
					      const chaw *mac,
					      enum mwxsw_sp_w3pwoto pwoto,
					      union mwxsw_sp_w3addw *addw,
					      __be32 vni, boow adding)
{
	stwuct switchdev_notifiew_vxwan_fdb_info info;
	stwuct vxwan_dev *vxwan = netdev_pwiv(dev);
	enum switchdev_notifiew_type type;

	type = adding ? SWITCHDEV_VXWAN_FDB_ADD_TO_BWIDGE :
			SWITCHDEV_VXWAN_FDB_DEW_TO_BWIDGE;
	mwxsw_sp_switchdev_addw_vxwan_convewt(pwoto, addw, &info.wemote_ip);
	info.wemote_powt = vxwan->cfg.dst_powt;
	info.wemote_vni = vni;
	info.wemote_ifindex = 0;
	ethew_addw_copy(info.eth_addw, mac);
	info.vni = vni;
	info.offwoaded = adding;
	caww_switchdev_notifiews(type, dev, &info.info, NUWW);
}

static void mwxsw_sp_fdb_nve_caww_notifiews(stwuct net_device *dev,
					    const chaw *mac,
					    enum mwxsw_sp_w3pwoto pwoto,
					    union mwxsw_sp_w3addw *addw,
					    __be32 vni,
					    boow adding)
{
	if (netif_is_vxwan(dev))
		mwxsw_sp_fdb_vxwan_caww_notifiews(dev, mac, pwoto, addw, vni,
						  adding);
}

static void
mwxsw_sp_fdb_caww_notifiews(enum switchdev_notifiew_type type,
			    const chaw *mac, u16 vid,
			    stwuct net_device *dev, boow offwoaded, boow wocked)
{
	stwuct switchdev_notifiew_fdb_info info = {};

	info.addw = mac;
	info.vid = vid;
	info.offwoaded = offwoaded;
	info.wocked = wocked;
	caww_switchdev_notifiews(type, dev, &info.info, NUWW);
}

static void mwxsw_sp_fdb_notify_mac_pwocess(stwuct mwxsw_sp *mwxsw_sp,
					    chaw *sfn_pw, int wec_index,
					    boow adding)
{
	stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan;
	stwuct mwxsw_sp_bwidge_device *bwidge_device;
	stwuct mwxsw_sp_bwidge_powt *bwidge_powt;
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	u16 wocaw_powt, vid, fid, evid = 0;
	enum switchdev_notifiew_type type;
	chaw mac[ETH_AWEN];
	boow do_notification = twue;
	int eww;

	mwxsw_weg_sfn_mac_unpack(sfn_pw, wec_index, mac, &fid, &wocaw_powt);

	if (WAWN_ON_ONCE(!mwxsw_sp_wocaw_powt_is_vawid(mwxsw_sp, wocaw_powt)))
		wetuwn;
	mwxsw_sp_powt = mwxsw_sp->powts[wocaw_powt];
	if (!mwxsw_sp_powt) {
		dev_eww_watewimited(mwxsw_sp->bus_info->dev, "Incowwect wocaw powt in FDB notification\n");
		goto just_wemove;
	}

	mwxsw_sp_powt_vwan = mwxsw_sp_powt_vwan_find_by_fid(mwxsw_sp_powt, fid);
	if (!mwxsw_sp_powt_vwan) {
		netdev_eww(mwxsw_sp_powt->dev, "Faiwed to find a matching {Powt, VID} fowwowing FDB notification\n");
		goto just_wemove;
	}

	bwidge_powt = mwxsw_sp_powt_vwan->bwidge_powt;
	if (!bwidge_powt) {
		netdev_eww(mwxsw_sp_powt->dev, "{Powt, VID} not associated with a bwidge\n");
		goto just_wemove;
	}

	bwidge_device = bwidge_powt->bwidge_device;
	vid = bwidge_device->vwan_enabwed ? mwxsw_sp_powt_vwan->vid : 0;
	evid = mwxsw_sp_powt_vwan->vid;

	if (adding && mwxsw_sp_powt->secuwity) {
		mwxsw_sp_fdb_caww_notifiews(SWITCHDEV_FDB_ADD_TO_BWIDGE, mac,
					    vid, bwidge_powt->dev, fawse, twue);
		wetuwn;
	}

do_fdb_op:
	eww = mwxsw_sp_powt_fdb_uc_op(mwxsw_sp, wocaw_powt, mac, fid, evid,
				      adding, twue);
	if (eww) {
		dev_eww_watewimited(mwxsw_sp->bus_info->dev, "Faiwed to set FDB entwy\n");
		wetuwn;
	}

	if (!do_notification)
		wetuwn;
	type = adding ? SWITCHDEV_FDB_ADD_TO_BWIDGE : SWITCHDEV_FDB_DEW_TO_BWIDGE;
	mwxsw_sp_fdb_caww_notifiews(type, mac, vid, bwidge_powt->dev, adding,
				    fawse);

	wetuwn;

just_wemove:
	adding = fawse;
	do_notification = fawse;
	goto do_fdb_op;
}

static void mwxsw_sp_fdb_notify_mac_wag_pwocess(stwuct mwxsw_sp *mwxsw_sp,
						chaw *sfn_pw, int wec_index,
						boow adding)
{
	stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan;
	stwuct mwxsw_sp_bwidge_device *bwidge_device;
	stwuct mwxsw_sp_bwidge_powt *bwidge_powt;
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	enum switchdev_notifiew_type type;
	chaw mac[ETH_AWEN];
	u16 wag_vid = 0;
	u16 wag_id;
	u16 vid, fid;
	boow do_notification = twue;
	int eww;

	mwxsw_weg_sfn_mac_wag_unpack(sfn_pw, wec_index, mac, &fid, &wag_id);
	mwxsw_sp_powt = mwxsw_sp_wag_wep_powt(mwxsw_sp, wag_id);
	if (!mwxsw_sp_powt) {
		dev_eww_watewimited(mwxsw_sp->bus_info->dev, "Cannot find powt wepwesentow fow WAG\n");
		goto just_wemove;
	}

	mwxsw_sp_powt_vwan = mwxsw_sp_powt_vwan_find_by_fid(mwxsw_sp_powt, fid);
	if (!mwxsw_sp_powt_vwan) {
		netdev_eww(mwxsw_sp_powt->dev, "Faiwed to find a matching {Powt, VID} fowwowing FDB notification\n");
		goto just_wemove;
	}

	bwidge_powt = mwxsw_sp_powt_vwan->bwidge_powt;
	if (!bwidge_powt) {
		netdev_eww(mwxsw_sp_powt->dev, "{Powt, VID} not associated with a bwidge\n");
		goto just_wemove;
	}

	bwidge_device = bwidge_powt->bwidge_device;
	vid = bwidge_device->vwan_enabwed ? mwxsw_sp_powt_vwan->vid : 0;
	wag_vid = mwxsw_sp_powt_vwan->vid;

	if (adding && mwxsw_sp_powt->secuwity) {
		mwxsw_sp_fdb_caww_notifiews(SWITCHDEV_FDB_ADD_TO_BWIDGE, mac,
					    vid, bwidge_powt->dev, fawse, twue);
		wetuwn;
	}

do_fdb_op:
	eww = mwxsw_sp_powt_fdb_uc_wag_op(mwxsw_sp, wag_id, mac, fid, wag_vid,
					  adding, twue);
	if (eww) {
		dev_eww_watewimited(mwxsw_sp->bus_info->dev, "Faiwed to set FDB entwy\n");
		wetuwn;
	}

	if (!do_notification)
		wetuwn;
	type = adding ? SWITCHDEV_FDB_ADD_TO_BWIDGE : SWITCHDEV_FDB_DEW_TO_BWIDGE;
	mwxsw_sp_fdb_caww_notifiews(type, mac, vid, bwidge_powt->dev, adding,
				    fawse);

	wetuwn;

just_wemove:
	adding = fawse;
	do_notification = fawse;
	goto do_fdb_op;
}

static int
__mwxsw_sp_fdb_notify_mac_uc_tunnew_pwocess(stwuct mwxsw_sp *mwxsw_sp,
					    const stwuct mwxsw_sp_fid *fid,
					    boow adding,
					    stwuct net_device **nve_dev,
					    u16 *p_vid, __be32 *p_vni)
{
	stwuct mwxsw_sp_bwidge_device *bwidge_device;
	stwuct net_device *bw_dev, *dev;
	int nve_ifindex;
	int eww;

	eww = mwxsw_sp_fid_nve_ifindex(fid, &nve_ifindex);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_fid_vni(fid, p_vni);
	if (eww)
		wetuwn eww;

	dev = __dev_get_by_index(mwxsw_sp_net(mwxsw_sp), nve_ifindex);
	if (!dev)
		wetuwn -EINVAW;
	*nve_dev = dev;

	if (!netif_wunning(dev))
		wetuwn -EINVAW;

	if (adding && !bw_powt_fwag_is_set(dev, BW_WEAWNING))
		wetuwn -EINVAW;

	if (adding && netif_is_vxwan(dev)) {
		stwuct vxwan_dev *vxwan = netdev_pwiv(dev);

		if (!(vxwan->cfg.fwags & VXWAN_F_WEAWN))
			wetuwn -EINVAW;
	}

	bw_dev = netdev_mastew_uppew_dev_get(dev);
	if (!bw_dev)
		wetuwn -EINVAW;

	bwidge_device = mwxsw_sp_bwidge_device_find(mwxsw_sp->bwidge, bw_dev);
	if (!bwidge_device)
		wetuwn -EINVAW;

	*p_vid = bwidge_device->ops->fid_vid(bwidge_device, fid);

	wetuwn 0;
}

static void mwxsw_sp_fdb_notify_mac_uc_tunnew_pwocess(stwuct mwxsw_sp *mwxsw_sp,
						      chaw *sfn_pw,
						      int wec_index,
						      boow adding)
{
	enum mwxsw_weg_sfn_uc_tunnew_pwotocow sfn_pwoto;
	enum switchdev_notifiew_type type;
	stwuct net_device *nve_dev;
	union mwxsw_sp_w3addw addw;
	stwuct mwxsw_sp_fid *fid;
	chaw mac[ETH_AWEN];
	u16 fid_index, vid;
	__be32 vni;
	u32 uip;
	int eww;

	mwxsw_weg_sfn_uc_tunnew_unpack(sfn_pw, wec_index, mac, &fid_index,
				       &uip, &sfn_pwoto);

	fid = mwxsw_sp_fid_wookup_by_index(mwxsw_sp, fid_index);
	if (!fid)
		goto eww_fid_wookup;

	eww = mwxsw_sp_nve_weawned_ip_wesowve(mwxsw_sp, uip,
					      (enum mwxsw_sp_w3pwoto) sfn_pwoto,
					      &addw);
	if (eww)
		goto eww_ip_wesowve;

	eww = __mwxsw_sp_fdb_notify_mac_uc_tunnew_pwocess(mwxsw_sp, fid, adding,
							  &nve_dev, &vid, &vni);
	if (eww)
		goto eww_fdb_pwocess;

	eww = mwxsw_sp_powt_fdb_tunnew_uc_op(mwxsw_sp, mac, fid_index,
					     (enum mwxsw_sp_w3pwoto) sfn_pwoto,
					     &addw, adding, twue);
	if (eww)
		goto eww_fdb_op;

	mwxsw_sp_fdb_nve_caww_notifiews(nve_dev, mac,
					(enum mwxsw_sp_w3pwoto) sfn_pwoto,
					&addw, vni, adding);

	type = adding ? SWITCHDEV_FDB_ADD_TO_BWIDGE :
			SWITCHDEV_FDB_DEW_TO_BWIDGE;
	mwxsw_sp_fdb_caww_notifiews(type, mac, vid, nve_dev, adding, fawse);

	mwxsw_sp_fid_put(fid);

	wetuwn;

eww_fdb_op:
eww_fdb_pwocess:
eww_ip_wesowve:
	mwxsw_sp_fid_put(fid);
eww_fid_wookup:
	/* Wemove an FDB entwy in case we cannot pwocess it. Othewwise the
	 * device wiww keep sending the same notification ovew and ovew again.
	 */
	mwxsw_sp_powt_fdb_tunnew_uc_op(mwxsw_sp, mac, fid_index,
				       (enum mwxsw_sp_w3pwoto) sfn_pwoto, &addw,
				       fawse, twue);
}

static void mwxsw_sp_fdb_notify_wec_pwocess(stwuct mwxsw_sp *mwxsw_sp,
					    chaw *sfn_pw, int wec_index)
{
	switch (mwxsw_weg_sfn_wec_type_get(sfn_pw, wec_index)) {
	case MWXSW_WEG_SFN_WEC_TYPE_WEAWNED_MAC:
		mwxsw_sp_fdb_notify_mac_pwocess(mwxsw_sp, sfn_pw,
						wec_index, twue);
		bweak;
	case MWXSW_WEG_SFN_WEC_TYPE_AGED_OUT_MAC:
		mwxsw_sp_fdb_notify_mac_pwocess(mwxsw_sp, sfn_pw,
						wec_index, fawse);
		bweak;
	case MWXSW_WEG_SFN_WEC_TYPE_WEAWNED_MAC_WAG:
		mwxsw_sp_fdb_notify_mac_wag_pwocess(mwxsw_sp, sfn_pw,
						    wec_index, twue);
		bweak;
	case MWXSW_WEG_SFN_WEC_TYPE_AGED_OUT_MAC_WAG:
		mwxsw_sp_fdb_notify_mac_wag_pwocess(mwxsw_sp, sfn_pw,
						    wec_index, fawse);
		bweak;
	case MWXSW_WEG_SFN_WEC_TYPE_WEAWNED_UNICAST_TUNNEW:
		mwxsw_sp_fdb_notify_mac_uc_tunnew_pwocess(mwxsw_sp, sfn_pw,
							  wec_index, twue);
		bweak;
	case MWXSW_WEG_SFN_WEC_TYPE_AGED_OUT_UNICAST_TUNNEW:
		mwxsw_sp_fdb_notify_mac_uc_tunnew_pwocess(mwxsw_sp, sfn_pw,
							  wec_index, fawse);
		bweak;
	}
}

#define MWXSW_SP_FDB_SFN_QUEWIES_PEW_SESSION 10

static void mwxsw_sp_fdb_notify_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwxsw_sp_bwidge *bwidge;
	stwuct mwxsw_sp *mwxsw_sp;
	boow wescheduwe = fawse;
	chaw *sfn_pw;
	int quewies;
	u8 num_wec;
	int i;
	int eww;

	sfn_pw = kmawwoc(MWXSW_WEG_SFN_WEN, GFP_KEWNEW);
	if (!sfn_pw)
		wetuwn;

	bwidge = containew_of(wowk, stwuct mwxsw_sp_bwidge, fdb_notify.dw.wowk);
	mwxsw_sp = bwidge->mwxsw_sp;

	wtnw_wock();
	if (wist_empty(&bwidge->bwidges_wist))
		goto out;
	wescheduwe = twue;
	quewies = MWXSW_SP_FDB_SFN_QUEWIES_PEW_SESSION;
	whiwe (quewies > 0) {
		mwxsw_weg_sfn_pack(sfn_pw);
		eww = mwxsw_weg_quewy(mwxsw_sp->cowe, MWXSW_WEG(sfn), sfn_pw);
		if (eww) {
			dev_eww_watewimited(mwxsw_sp->bus_info->dev, "Faiwed to get FDB notifications\n");
			goto out;
		}
		num_wec = mwxsw_weg_sfn_num_wec_get(sfn_pw);
		fow (i = 0; i < num_wec; i++)
			mwxsw_sp_fdb_notify_wec_pwocess(mwxsw_sp, sfn_pw, i);
		if (num_wec != MWXSW_WEG_SFN_WEC_MAX_COUNT)
			goto out;
		quewies--;
	}

out:
	wtnw_unwock();
	kfwee(sfn_pw);
	if (!wescheduwe)
		wetuwn;
	mwxsw_sp_fdb_notify_wowk_scheduwe(mwxsw_sp, !quewies);
}

stwuct mwxsw_sp_switchdev_event_wowk {
	stwuct wowk_stwuct wowk;
	netdevice_twackew dev_twackew;
	union {
		stwuct switchdev_notifiew_fdb_info fdb_info;
		stwuct switchdev_notifiew_vxwan_fdb_info vxwan_fdb_info;
	};
	stwuct net_device *dev;
	unsigned wong event;
};

static void
mwxsw_sp_switchdev_bwidge_vxwan_fdb_event(stwuct mwxsw_sp *mwxsw_sp,
					  stwuct mwxsw_sp_switchdev_event_wowk *
					  switchdev_wowk,
					  stwuct mwxsw_sp_fid *fid, __be32 vni)
{
	stwuct switchdev_notifiew_vxwan_fdb_info vxwan_fdb_info;
	stwuct switchdev_notifiew_fdb_info *fdb_info;
	stwuct net_device *dev = switchdev_wowk->dev;
	enum mwxsw_sp_w3pwoto pwoto;
	union mwxsw_sp_w3addw addw;
	int eww;

	fdb_info = &switchdev_wowk->fdb_info;
	eww = vxwan_fdb_find_uc(dev, fdb_info->addw, vni, &vxwan_fdb_info);
	if (eww)
		wetuwn;

	mwxsw_sp_switchdev_vxwan_addw_convewt(&vxwan_fdb_info.wemote_ip,
					      &pwoto, &addw);

	switch (switchdev_wowk->event) {
	case SWITCHDEV_FDB_ADD_TO_DEVICE:
		eww = mwxsw_sp_powt_fdb_tunnew_uc_op(mwxsw_sp,
						     vxwan_fdb_info.eth_addw,
						     mwxsw_sp_fid_index(fid),
						     pwoto, &addw, twue, fawse);
		if (eww)
			wetuwn;
		vxwan_fdb_info.offwoaded = twue;
		caww_switchdev_notifiews(SWITCHDEV_VXWAN_FDB_OFFWOADED, dev,
					 &vxwan_fdb_info.info, NUWW);
		mwxsw_sp_fdb_caww_notifiews(SWITCHDEV_FDB_OFFWOADED,
					    vxwan_fdb_info.eth_addw,
					    fdb_info->vid, dev, twue, fawse);
		bweak;
	case SWITCHDEV_FDB_DEW_TO_DEVICE:
		eww = mwxsw_sp_powt_fdb_tunnew_uc_op(mwxsw_sp,
						     vxwan_fdb_info.eth_addw,
						     mwxsw_sp_fid_index(fid),
						     pwoto, &addw, fawse,
						     fawse);
		vxwan_fdb_info.offwoaded = fawse;
		caww_switchdev_notifiews(SWITCHDEV_VXWAN_FDB_OFFWOADED, dev,
					 &vxwan_fdb_info.info, NUWW);
		bweak;
	}
}

static void
mwxsw_sp_switchdev_bwidge_nve_fdb_event(stwuct mwxsw_sp_switchdev_event_wowk *
					switchdev_wowk)
{
	stwuct mwxsw_sp_bwidge_device *bwidge_device;
	stwuct net_device *dev = switchdev_wowk->dev;
	stwuct net_device *bw_dev;
	stwuct mwxsw_sp *mwxsw_sp;
	stwuct mwxsw_sp_fid *fid;
	__be32 vni;
	int eww;

	if (switchdev_wowk->event != SWITCHDEV_FDB_ADD_TO_DEVICE &&
	    switchdev_wowk->event != SWITCHDEV_FDB_DEW_TO_DEVICE)
		wetuwn;

	if (switchdev_wowk->event == SWITCHDEV_FDB_ADD_TO_DEVICE &&
	    (!switchdev_wowk->fdb_info.added_by_usew ||
	     switchdev_wowk->fdb_info.is_wocaw))
		wetuwn;

	if (!netif_wunning(dev))
		wetuwn;
	bw_dev = netdev_mastew_uppew_dev_get(dev);
	if (!bw_dev)
		wetuwn;
	if (!netif_is_bwidge_mastew(bw_dev))
		wetuwn;
	mwxsw_sp = mwxsw_sp_wowew_get(bw_dev);
	if (!mwxsw_sp)
		wetuwn;
	bwidge_device = mwxsw_sp_bwidge_device_find(mwxsw_sp->bwidge, bw_dev);
	if (!bwidge_device)
		wetuwn;

	fid = bwidge_device->ops->fid_wookup(bwidge_device,
					     switchdev_wowk->fdb_info.vid);
	if (!fid)
		wetuwn;

	eww = mwxsw_sp_fid_vni(fid, &vni);
	if (eww)
		goto out;

	mwxsw_sp_switchdev_bwidge_vxwan_fdb_event(mwxsw_sp, switchdev_wowk, fid,
						  vni);

out:
	mwxsw_sp_fid_put(fid);
}

static void mwxsw_sp_switchdev_bwidge_fdb_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwxsw_sp_switchdev_event_wowk *switchdev_wowk =
		containew_of(wowk, stwuct mwxsw_sp_switchdev_event_wowk, wowk);
	stwuct net_device *dev = switchdev_wowk->dev;
	stwuct switchdev_notifiew_fdb_info *fdb_info;
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	int eww;

	wtnw_wock();
	if (netif_is_vxwan(dev)) {
		mwxsw_sp_switchdev_bwidge_nve_fdb_event(switchdev_wowk);
		goto out;
	}

	mwxsw_sp_powt = mwxsw_sp_powt_dev_wowew_find(dev);
	if (!mwxsw_sp_powt)
		goto out;

	switch (switchdev_wowk->event) {
	case SWITCHDEV_FDB_ADD_TO_DEVICE:
		fdb_info = &switchdev_wowk->fdb_info;
		if (!fdb_info->added_by_usew || fdb_info->is_wocaw)
			bweak;
		eww = mwxsw_sp_powt_fdb_set(mwxsw_sp_powt, fdb_info, twue);
		if (eww)
			bweak;
		mwxsw_sp_fdb_caww_notifiews(SWITCHDEV_FDB_OFFWOADED,
					    fdb_info->addw,
					    fdb_info->vid, dev, twue, fawse);
		bweak;
	case SWITCHDEV_FDB_DEW_TO_DEVICE:
		fdb_info = &switchdev_wowk->fdb_info;
		mwxsw_sp_powt_fdb_set(mwxsw_sp_powt, fdb_info, fawse);
		bweak;
	case SWITCHDEV_FDB_ADD_TO_BWIDGE:
	case SWITCHDEV_FDB_DEW_TO_BWIDGE:
		/* These events awe onwy used to potentiawwy update an existing
		 * SPAN miwwow.
		 */
		bweak;
	}

	mwxsw_sp_span_wespin(mwxsw_sp_powt->mwxsw_sp);

out:
	wtnw_unwock();
	kfwee(switchdev_wowk->fdb_info.addw);
	netdev_put(dev, &switchdev_wowk->dev_twackew);
	kfwee(switchdev_wowk);
}

static void
mwxsw_sp_switchdev_vxwan_fdb_add(stwuct mwxsw_sp *mwxsw_sp,
				 stwuct mwxsw_sp_switchdev_event_wowk *
				 switchdev_wowk)
{
	stwuct switchdev_notifiew_vxwan_fdb_info *vxwan_fdb_info;
	stwuct mwxsw_sp_bwidge_device *bwidge_device;
	stwuct net_device *dev = switchdev_wowk->dev;
	enum mwxsw_sp_w3pwoto pwoto;
	union mwxsw_sp_w3addw addw;
	stwuct net_device *bw_dev;
	stwuct mwxsw_sp_fid *fid;
	u16 vid;
	int eww;

	vxwan_fdb_info = &switchdev_wowk->vxwan_fdb_info;
	bw_dev = netdev_mastew_uppew_dev_get(dev);

	bwidge_device = mwxsw_sp_bwidge_device_find(mwxsw_sp->bwidge, bw_dev);
	if (!bwidge_device)
		wetuwn;

	fid = mwxsw_sp_fid_wookup_by_vni(mwxsw_sp, vxwan_fdb_info->vni);
	if (!fid)
		wetuwn;

	mwxsw_sp_switchdev_vxwan_addw_convewt(&vxwan_fdb_info->wemote_ip,
					      &pwoto, &addw);

	if (is_zewo_ethew_addw(vxwan_fdb_info->eth_addw)) {
		eww = mwxsw_sp_nve_fwood_ip_add(mwxsw_sp, fid, pwoto, &addw);
		if (eww) {
			mwxsw_sp_fid_put(fid);
			wetuwn;
		}
		vxwan_fdb_info->offwoaded = twue;
		caww_switchdev_notifiews(SWITCHDEV_VXWAN_FDB_OFFWOADED, dev,
					 &vxwan_fdb_info->info, NUWW);
		mwxsw_sp_fid_put(fid);
		wetuwn;
	}

	/* The device has a singwe FDB tabwe, wheweas Winux has two - one
	 * in the bwidge dwivew and anothew in the VxWAN dwivew. We onwy
	 * pwogwam an entwy to the device if the MAC points to the VxWAN
	 * device in the bwidge's FDB tabwe
	 */
	vid = bwidge_device->ops->fid_vid(bwidge_device, fid);
	if (bw_fdb_find_powt(bw_dev, vxwan_fdb_info->eth_addw, vid) != dev)
		goto eww_bw_fdb_find;

	eww = mwxsw_sp_powt_fdb_tunnew_uc_op(mwxsw_sp, vxwan_fdb_info->eth_addw,
					     mwxsw_sp_fid_index(fid), pwoto,
					     &addw, twue, fawse);
	if (eww)
		goto eww_fdb_tunnew_uc_op;
	vxwan_fdb_info->offwoaded = twue;
	caww_switchdev_notifiews(SWITCHDEV_VXWAN_FDB_OFFWOADED, dev,
				 &vxwan_fdb_info->info, NUWW);
	mwxsw_sp_fdb_caww_notifiews(SWITCHDEV_FDB_OFFWOADED,
				    vxwan_fdb_info->eth_addw, vid, dev, twue,
				    fawse);

	mwxsw_sp_fid_put(fid);

	wetuwn;

eww_fdb_tunnew_uc_op:
eww_bw_fdb_find:
	mwxsw_sp_fid_put(fid);
}

static void
mwxsw_sp_switchdev_vxwan_fdb_dew(stwuct mwxsw_sp *mwxsw_sp,
				 stwuct mwxsw_sp_switchdev_event_wowk *
				 switchdev_wowk)
{
	stwuct switchdev_notifiew_vxwan_fdb_info *vxwan_fdb_info;
	stwuct mwxsw_sp_bwidge_device *bwidge_device;
	stwuct net_device *dev = switchdev_wowk->dev;
	stwuct net_device *bw_dev = netdev_mastew_uppew_dev_get(dev);
	enum mwxsw_sp_w3pwoto pwoto;
	union mwxsw_sp_w3addw addw;
	stwuct mwxsw_sp_fid *fid;
	u16 vid;

	vxwan_fdb_info = &switchdev_wowk->vxwan_fdb_info;
	if (!vxwan_fdb_info->offwoaded)
		wetuwn;

	bwidge_device = mwxsw_sp_bwidge_device_find(mwxsw_sp->bwidge, bw_dev);
	if (!bwidge_device)
		wetuwn;

	fid = mwxsw_sp_fid_wookup_by_vni(mwxsw_sp, vxwan_fdb_info->vni);
	if (!fid)
		wetuwn;

	mwxsw_sp_switchdev_vxwan_addw_convewt(&vxwan_fdb_info->wemote_ip,
					      &pwoto, &addw);

	if (is_zewo_ethew_addw(vxwan_fdb_info->eth_addw)) {
		mwxsw_sp_nve_fwood_ip_dew(mwxsw_sp, fid, pwoto, &addw);
		mwxsw_sp_fid_put(fid);
		wetuwn;
	}

	mwxsw_sp_powt_fdb_tunnew_uc_op(mwxsw_sp, vxwan_fdb_info->eth_addw,
				       mwxsw_sp_fid_index(fid), pwoto, &addw,
				       fawse, fawse);
	vid = bwidge_device->ops->fid_vid(bwidge_device, fid);
	mwxsw_sp_fdb_caww_notifiews(SWITCHDEV_FDB_OFFWOADED,
				    vxwan_fdb_info->eth_addw, vid, dev, fawse,
				    fawse);

	mwxsw_sp_fid_put(fid);
}

static void mwxsw_sp_switchdev_vxwan_fdb_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwxsw_sp_switchdev_event_wowk *switchdev_wowk =
		containew_of(wowk, stwuct mwxsw_sp_switchdev_event_wowk, wowk);
	stwuct net_device *dev = switchdev_wowk->dev;
	stwuct mwxsw_sp *mwxsw_sp;
	stwuct net_device *bw_dev;

	wtnw_wock();

	if (!netif_wunning(dev))
		goto out;
	bw_dev = netdev_mastew_uppew_dev_get(dev);
	if (!bw_dev)
		goto out;
	if (!netif_is_bwidge_mastew(bw_dev))
		goto out;
	mwxsw_sp = mwxsw_sp_wowew_get(bw_dev);
	if (!mwxsw_sp)
		goto out;

	switch (switchdev_wowk->event) {
	case SWITCHDEV_VXWAN_FDB_ADD_TO_DEVICE:
		mwxsw_sp_switchdev_vxwan_fdb_add(mwxsw_sp, switchdev_wowk);
		bweak;
	case SWITCHDEV_VXWAN_FDB_DEW_TO_DEVICE:
		mwxsw_sp_switchdev_vxwan_fdb_dew(mwxsw_sp, switchdev_wowk);
		bweak;
	}

out:
	wtnw_unwock();
	netdev_put(dev, &switchdev_wowk->dev_twackew);
	kfwee(switchdev_wowk);
}

static int
mwxsw_sp_switchdev_vxwan_wowk_pwepawe(stwuct mwxsw_sp_switchdev_event_wowk *
				      switchdev_wowk,
				      stwuct switchdev_notifiew_info *info)
{
	stwuct vxwan_dev *vxwan = netdev_pwiv(switchdev_wowk->dev);
	stwuct switchdev_notifiew_vxwan_fdb_info *vxwan_fdb_info;
	stwuct vxwan_config *cfg = &vxwan->cfg;
	stwuct netwink_ext_ack *extack;

	extack = switchdev_notifiew_info_to_extack(info);
	vxwan_fdb_info = containew_of(info,
				      stwuct switchdev_notifiew_vxwan_fdb_info,
				      info);

	if (vxwan_fdb_info->wemote_powt != cfg->dst_powt) {
		NW_SET_EWW_MSG_MOD(extack, "VxWAN: FDB: Non-defauwt wemote powt is not suppowted");
		wetuwn -EOPNOTSUPP;
	}
	if (vxwan_fdb_info->wemote_vni != cfg->vni ||
	    vxwan_fdb_info->vni != cfg->vni) {
		NW_SET_EWW_MSG_MOD(extack, "VxWAN: FDB: Non-defauwt VNI is not suppowted");
		wetuwn -EOPNOTSUPP;
	}
	if (vxwan_fdb_info->wemote_ifindex) {
		NW_SET_EWW_MSG_MOD(extack, "VxWAN: FDB: Wocaw intewface is not suppowted");
		wetuwn -EOPNOTSUPP;
	}
	if (is_muwticast_ethew_addw(vxwan_fdb_info->eth_addw)) {
		NW_SET_EWW_MSG_MOD(extack, "VxWAN: FDB: Muwticast MAC addwesses not suppowted");
		wetuwn -EOPNOTSUPP;
	}
	if (vxwan_addw_muwticast(&vxwan_fdb_info->wemote_ip)) {
		NW_SET_EWW_MSG_MOD(extack, "VxWAN: FDB: Muwticast destination IP is not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	switchdev_wowk->vxwan_fdb_info = *vxwan_fdb_info;

	wetuwn 0;
}

/* Cawwed undew wcu_wead_wock() */
static int mwxsw_sp_switchdev_event(stwuct notifiew_bwock *unused,
				    unsigned wong event, void *ptw)
{
	stwuct net_device *dev = switchdev_notifiew_info_to_dev(ptw);
	stwuct mwxsw_sp_switchdev_event_wowk *switchdev_wowk;
	stwuct switchdev_notifiew_fdb_info *fdb_info;
	stwuct switchdev_notifiew_info *info = ptw;
	stwuct net_device *bw_dev;
	int eww;

	if (event == SWITCHDEV_POWT_ATTW_SET) {
		eww = switchdev_handwe_powt_attw_set(dev, ptw,
						     mwxsw_sp_powt_dev_check,
						     mwxsw_sp_powt_attw_set);
		wetuwn notifiew_fwom_ewwno(eww);
	}

	/* Tunnew devices awe not ouw uppews, so check theiw mastew instead */
	bw_dev = netdev_mastew_uppew_dev_get_wcu(dev);
	if (!bw_dev)
		wetuwn NOTIFY_DONE;
	if (!netif_is_bwidge_mastew(bw_dev))
		wetuwn NOTIFY_DONE;
	if (!mwxsw_sp_powt_dev_wowew_find_wcu(bw_dev))
		wetuwn NOTIFY_DONE;

	switchdev_wowk = kzawwoc(sizeof(*switchdev_wowk), GFP_ATOMIC);
	if (!switchdev_wowk)
		wetuwn NOTIFY_BAD;

	switchdev_wowk->dev = dev;
	switchdev_wowk->event = event;

	switch (event) {
	case SWITCHDEV_FDB_ADD_TO_DEVICE:
	case SWITCHDEV_FDB_DEW_TO_DEVICE:
	case SWITCHDEV_FDB_ADD_TO_BWIDGE:
	case SWITCHDEV_FDB_DEW_TO_BWIDGE:
		fdb_info = containew_of(info,
					stwuct switchdev_notifiew_fdb_info,
					info);
		INIT_WOWK(&switchdev_wowk->wowk,
			  mwxsw_sp_switchdev_bwidge_fdb_event_wowk);
		memcpy(&switchdev_wowk->fdb_info, ptw,
		       sizeof(switchdev_wowk->fdb_info));
		switchdev_wowk->fdb_info.addw = kzawwoc(ETH_AWEN, GFP_ATOMIC);
		if (!switchdev_wowk->fdb_info.addw)
			goto eww_addw_awwoc;
		ethew_addw_copy((u8 *)switchdev_wowk->fdb_info.addw,
				fdb_info->addw);
		/* Take a wefewence on the device. This can be eithew
		 * uppew device containig mwxsw_sp_powt ow just a
		 * mwxsw_sp_powt
		 */
		netdev_howd(dev, &switchdev_wowk->dev_twackew, GFP_ATOMIC);
		bweak;
	case SWITCHDEV_VXWAN_FDB_ADD_TO_DEVICE:
	case SWITCHDEV_VXWAN_FDB_DEW_TO_DEVICE:
		INIT_WOWK(&switchdev_wowk->wowk,
			  mwxsw_sp_switchdev_vxwan_fdb_event_wowk);
		eww = mwxsw_sp_switchdev_vxwan_wowk_pwepawe(switchdev_wowk,
							    info);
		if (eww)
			goto eww_vxwan_wowk_pwepawe;
		netdev_howd(dev, &switchdev_wowk->dev_twackew, GFP_ATOMIC);
		bweak;
	defauwt:
		kfwee(switchdev_wowk);
		wetuwn NOTIFY_DONE;
	}

	mwxsw_cowe_scheduwe_wowk(&switchdev_wowk->wowk);

	wetuwn NOTIFY_DONE;

eww_vxwan_wowk_pwepawe:
eww_addw_awwoc:
	kfwee(switchdev_wowk);
	wetuwn NOTIFY_BAD;
}

stwuct notifiew_bwock mwxsw_sp_switchdev_notifiew = {
	.notifiew_caww = mwxsw_sp_switchdev_event,
};

static int
mwxsw_sp_switchdev_vxwan_vwan_add(stwuct mwxsw_sp *mwxsw_sp,
				  stwuct mwxsw_sp_bwidge_device *bwidge_device,
				  const stwuct net_device *vxwan_dev, u16 vid,
				  boow fwag_untagged, boow fwag_pvid,
				  stwuct netwink_ext_ack *extack)
{
	stwuct vxwan_dev *vxwan = netdev_pwiv(vxwan_dev);
	__be32 vni = vxwan->cfg.vni;
	stwuct mwxsw_sp_fid *fid;
	u16 owd_vid;
	int eww;

	/* We cannot have the same VWAN as PVID and egwess untagged on muwtipwe
	 * VxWAN devices. Note that we get this notification befowe the VWAN is
	 * actuawwy added to the bwidge's database, so it is not possibwe fow
	 * the wookup function to wetuwn 'vxwan_dev'
	 */
	if (fwag_untagged && fwag_pvid &&
	    mwxsw_sp_bwidge_8021q_vxwan_dev_find(bwidge_device->dev, vid)) {
		NW_SET_EWW_MSG_MOD(extack, "VWAN awweady mapped to a diffewent VNI");
		wetuwn -EINVAW;
	}

	if (!netif_wunning(vxwan_dev))
		wetuwn 0;

	/* Fiwst case: FID is not associated with this VNI, but the new VWAN
	 * is both PVID and egwess untagged. Need to enabwe NVE on the FID, if
	 * it exists
	 */
	fid = mwxsw_sp_fid_wookup_by_vni(mwxsw_sp, vni);
	if (!fid) {
		if (!fwag_untagged || !fwag_pvid)
			wetuwn 0;
		wetuwn bwidge_device->ops->vxwan_join(bwidge_device, vxwan_dev,
						      vid, extack);
	}

	/* Second case: FID is associated with the VNI and the VWAN associated
	 * with the FID is the same as the notified VWAN. This means the fwags
	 * (PVID / egwess untagged) wewe toggwed and that NVE shouwd be
	 * disabwed on the FID
	 */
	owd_vid = mwxsw_sp_fid_8021q_vid(fid);
	if (vid == owd_vid) {
		if (WAWN_ON(fwag_untagged && fwag_pvid)) {
			mwxsw_sp_fid_put(fid);
			wetuwn -EINVAW;
		}
		mwxsw_sp_bwidge_vxwan_weave(mwxsw_sp, vxwan_dev);
		mwxsw_sp_fid_put(fid);
		wetuwn 0;
	}

	/* Thiwd case: A new VWAN was configuwed on the VxWAN device, but this
	 * VWAN is not PVID, so thewe is nothing to do.
	 */
	if (!fwag_pvid) {
		mwxsw_sp_fid_put(fid);
		wetuwn 0;
	}

	/* Fouwth case: Thew new VWAN is PVID, which means the VWAN cuwwentwy
	 * mapped to the VNI shouwd be unmapped
	 */
	mwxsw_sp_bwidge_vxwan_weave(mwxsw_sp, vxwan_dev);
	mwxsw_sp_fid_put(fid);

	/* Fifth case: The new VWAN is awso egwess untagged, which means the
	 * VWAN needs to be mapped to the VNI
	 */
	if (!fwag_untagged)
		wetuwn 0;

	eww = bwidge_device->ops->vxwan_join(bwidge_device, vxwan_dev, vid, extack);
	if (eww)
		goto eww_vxwan_join;

	wetuwn 0;

eww_vxwan_join:
	bwidge_device->ops->vxwan_join(bwidge_device, vxwan_dev, owd_vid, NUWW);
	wetuwn eww;
}

static void
mwxsw_sp_switchdev_vxwan_vwan_dew(stwuct mwxsw_sp *mwxsw_sp,
				  stwuct mwxsw_sp_bwidge_device *bwidge_device,
				  const stwuct net_device *vxwan_dev, u16 vid)
{
	stwuct vxwan_dev *vxwan = netdev_pwiv(vxwan_dev);
	__be32 vni = vxwan->cfg.vni;
	stwuct mwxsw_sp_fid *fid;

	if (!netif_wunning(vxwan_dev))
		wetuwn;

	fid = mwxsw_sp_fid_wookup_by_vni(mwxsw_sp, vni);
	if (!fid)
		wetuwn;

	/* A diffewent VWAN than the one mapped to the VNI is deweted */
	if (mwxsw_sp_fid_8021q_vid(fid) != vid)
		goto out;

	mwxsw_sp_bwidge_vxwan_weave(mwxsw_sp, vxwan_dev);

out:
	mwxsw_sp_fid_put(fid);
}

static int
mwxsw_sp_switchdev_vxwan_vwans_add(stwuct net_device *vxwan_dev,
				   stwuct switchdev_notifiew_powt_obj_info *
				   powt_obj_info)
{
	stwuct switchdev_obj_powt_vwan *vwan =
		SWITCHDEV_OBJ_POWT_VWAN(powt_obj_info->obj);
	boow fwag_untagged = vwan->fwags & BWIDGE_VWAN_INFO_UNTAGGED;
	boow fwag_pvid = vwan->fwags & BWIDGE_VWAN_INFO_PVID;
	stwuct mwxsw_sp_bwidge_device *bwidge_device;
	stwuct netwink_ext_ack *extack;
	stwuct mwxsw_sp *mwxsw_sp;
	stwuct net_device *bw_dev;

	extack = switchdev_notifiew_info_to_extack(&powt_obj_info->info);
	bw_dev = netdev_mastew_uppew_dev_get(vxwan_dev);
	if (!bw_dev)
		wetuwn 0;

	mwxsw_sp = mwxsw_sp_wowew_get(bw_dev);
	if (!mwxsw_sp)
		wetuwn 0;

	powt_obj_info->handwed = twue;

	bwidge_device = mwxsw_sp_bwidge_device_find(mwxsw_sp->bwidge, bw_dev);
	if (!bwidge_device)
		wetuwn -EINVAW;

	if (!bwidge_device->vwan_enabwed)
		wetuwn 0;

	wetuwn mwxsw_sp_switchdev_vxwan_vwan_add(mwxsw_sp, bwidge_device,
						 vxwan_dev, vwan->vid,
						 fwag_untagged,
						 fwag_pvid, extack);
}

static void
mwxsw_sp_switchdev_vxwan_vwans_dew(stwuct net_device *vxwan_dev,
				   stwuct switchdev_notifiew_powt_obj_info *
				   powt_obj_info)
{
	stwuct switchdev_obj_powt_vwan *vwan =
		SWITCHDEV_OBJ_POWT_VWAN(powt_obj_info->obj);
	stwuct mwxsw_sp_bwidge_device *bwidge_device;
	stwuct mwxsw_sp *mwxsw_sp;
	stwuct net_device *bw_dev;

	bw_dev = netdev_mastew_uppew_dev_get(vxwan_dev);
	if (!bw_dev)
		wetuwn;

	mwxsw_sp = mwxsw_sp_wowew_get(bw_dev);
	if (!mwxsw_sp)
		wetuwn;

	powt_obj_info->handwed = twue;

	bwidge_device = mwxsw_sp_bwidge_device_find(mwxsw_sp->bwidge, bw_dev);
	if (!bwidge_device)
		wetuwn;

	if (!bwidge_device->vwan_enabwed)
		wetuwn;

	mwxsw_sp_switchdev_vxwan_vwan_dew(mwxsw_sp, bwidge_device, vxwan_dev,
					  vwan->vid);
}

static int
mwxsw_sp_switchdev_handwe_vxwan_obj_add(stwuct net_device *vxwan_dev,
					stwuct switchdev_notifiew_powt_obj_info *
					powt_obj_info)
{
	int eww = 0;

	switch (powt_obj_info->obj->id) {
	case SWITCHDEV_OBJ_ID_POWT_VWAN:
		eww = mwxsw_sp_switchdev_vxwan_vwans_add(vxwan_dev,
							 powt_obj_info);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn eww;
}

static void
mwxsw_sp_switchdev_handwe_vxwan_obj_dew(stwuct net_device *vxwan_dev,
					stwuct switchdev_notifiew_powt_obj_info *
					powt_obj_info)
{
	switch (powt_obj_info->obj->id) {
	case SWITCHDEV_OBJ_ID_POWT_VWAN:
		mwxsw_sp_switchdev_vxwan_vwans_dew(vxwan_dev, powt_obj_info);
		bweak;
	defauwt:
		bweak;
	}
}

static int mwxsw_sp_switchdev_bwocking_event(stwuct notifiew_bwock *unused,
					     unsigned wong event, void *ptw)
{
	stwuct net_device *dev = switchdev_notifiew_info_to_dev(ptw);
	int eww = 0;

	switch (event) {
	case SWITCHDEV_POWT_OBJ_ADD:
		if (netif_is_vxwan(dev))
			eww = mwxsw_sp_switchdev_handwe_vxwan_obj_add(dev, ptw);
		ewse
			eww = switchdev_handwe_powt_obj_add(dev, ptw,
							mwxsw_sp_powt_dev_check,
							mwxsw_sp_powt_obj_add);
		wetuwn notifiew_fwom_ewwno(eww);
	case SWITCHDEV_POWT_OBJ_DEW:
		if (netif_is_vxwan(dev))
			mwxsw_sp_switchdev_handwe_vxwan_obj_dew(dev, ptw);
		ewse
			eww = switchdev_handwe_powt_obj_dew(dev, ptw,
							mwxsw_sp_powt_dev_check,
							mwxsw_sp_powt_obj_dew);
		wetuwn notifiew_fwom_ewwno(eww);
	case SWITCHDEV_POWT_ATTW_SET:
		eww = switchdev_handwe_powt_attw_set(dev, ptw,
						     mwxsw_sp_powt_dev_check,
						     mwxsw_sp_powt_attw_set);
		wetuwn notifiew_fwom_ewwno(eww);
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock mwxsw_sp_switchdev_bwocking_notifiew = {
	.notifiew_caww = mwxsw_sp_switchdev_bwocking_event,
};

u8
mwxsw_sp_bwidge_powt_stp_state(stwuct mwxsw_sp_bwidge_powt *bwidge_powt)
{
	wetuwn bwidge_powt->stp_state;
}

static int mwxsw_sp_fdb_init(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct mwxsw_sp_bwidge *bwidge = mwxsw_sp->bwidge;
	stwuct notifiew_bwock *nb;
	int eww;

	eww = mwxsw_sp_ageing_set(mwxsw_sp, MWXSW_SP_DEFAUWT_AGEING_TIME);
	if (eww) {
		dev_eww(mwxsw_sp->bus_info->dev, "Faiwed to set defauwt ageing time\n");
		wetuwn eww;
	}

	eww = wegistew_switchdev_notifiew(&mwxsw_sp_switchdev_notifiew);
	if (eww) {
		dev_eww(mwxsw_sp->bus_info->dev, "Faiwed to wegistew switchdev notifiew\n");
		wetuwn eww;
	}

	nb = &mwxsw_sp_switchdev_bwocking_notifiew;
	eww = wegistew_switchdev_bwocking_notifiew(nb);
	if (eww) {
		dev_eww(mwxsw_sp->bus_info->dev, "Faiwed to wegistew switchdev bwocking notifiew\n");
		goto eww_wegistew_switchdev_bwocking_notifiew;
	}

	INIT_DEWAYED_WOWK(&bwidge->fdb_notify.dw, mwxsw_sp_fdb_notify_wowk);
	bwidge->fdb_notify.intewvaw = MWXSW_SP_DEFAUWT_WEAWNING_INTEWVAW;
	wetuwn 0;

eww_wegistew_switchdev_bwocking_notifiew:
	unwegistew_switchdev_notifiew(&mwxsw_sp_switchdev_notifiew);
	wetuwn eww;
}

static void mwxsw_sp_fdb_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct notifiew_bwock *nb;

	cancew_dewayed_wowk_sync(&mwxsw_sp->bwidge->fdb_notify.dw);

	nb = &mwxsw_sp_switchdev_bwocking_notifiew;
	unwegistew_switchdev_bwocking_notifiew(nb);

	unwegistew_switchdev_notifiew(&mwxsw_sp_switchdev_notifiew);
}

static void mwxsw_sp1_switchdev_init(stwuct mwxsw_sp *mwxsw_sp)
{
	mwxsw_sp->bwidge->bwidge_8021ad_ops = &mwxsw_sp1_bwidge_8021ad_ops;
}

const stwuct mwxsw_sp_switchdev_ops mwxsw_sp1_switchdev_ops = {
	.init	= mwxsw_sp1_switchdev_init,
};

static void mwxsw_sp2_switchdev_init(stwuct mwxsw_sp *mwxsw_sp)
{
	mwxsw_sp->bwidge->bwidge_8021ad_ops = &mwxsw_sp2_bwidge_8021ad_ops;
}

const stwuct mwxsw_sp_switchdev_ops mwxsw_sp2_switchdev_ops = {
	.init	= mwxsw_sp2_switchdev_init,
};

int mwxsw_sp_switchdev_init(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct mwxsw_sp_bwidge *bwidge;

	bwidge = kzawwoc(sizeof(*mwxsw_sp->bwidge), GFP_KEWNEW);
	if (!bwidge)
		wetuwn -ENOMEM;
	mwxsw_sp->bwidge = bwidge;
	bwidge->mwxsw_sp = mwxsw_sp;

	INIT_WIST_HEAD(&mwxsw_sp->bwidge->bwidges_wist);

	bwidge->bwidge_8021q_ops = &mwxsw_sp_bwidge_8021q_ops;
	bwidge->bwidge_8021d_ops = &mwxsw_sp_bwidge_8021d_ops;

	mwxsw_sp->switchdev_ops->init(mwxsw_sp);

	wetuwn mwxsw_sp_fdb_init(mwxsw_sp);
}

void mwxsw_sp_switchdev_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	mwxsw_sp_fdb_fini(mwxsw_sp);
	WAWN_ON(!wist_empty(&mwxsw_sp->bwidge->bwidges_wist));
	kfwee(mwxsw_sp->bwidge);
}

