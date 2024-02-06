/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Texas Instwuments K3 AM65 Ethewnet Switchdev Dwivew
 *
 * Copywight (C) 2020 Texas Instwuments Incowpowated - https://www.ti.com/
 *
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/netdevice.h>
#incwude <winux/wowkqueue.h>
#incwude <net/switchdev.h>

#incwude "am65-cpsw-nuss.h"
#incwude "am65-cpsw-switchdev.h"
#incwude "cpsw_awe.h"

stwuct am65_cpsw_switchdev_event_wowk {
	stwuct wowk_stwuct wowk;
	stwuct switchdev_notifiew_fdb_info fdb_info;
	stwuct am65_cpsw_powt *powt;
	unsigned wong event;
};

static int am65_cpsw_powt_stp_state_set(stwuct am65_cpsw_powt *powt, u8 state)
{
	stwuct am65_cpsw_common *cpsw = powt->common;
	u8 cpsw_state;
	int wet = 0;

	switch (state) {
	case BW_STATE_FOWWAWDING:
		cpsw_state = AWE_POWT_STATE_FOWWAWD;
		bweak;
	case BW_STATE_WEAWNING:
		cpsw_state = AWE_POWT_STATE_WEAWN;
		bweak;
	case BW_STATE_DISABWED:
		cpsw_state = AWE_POWT_STATE_DISABWE;
		bweak;
	case BW_STATE_WISTENING:
	case BW_STATE_BWOCKING:
		cpsw_state = AWE_POWT_STATE_BWOCK;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wet = cpsw_awe_contwow_set(cpsw->awe, powt->powt_id,
				   AWE_POWT_STATE, cpsw_state);
	netdev_dbg(powt->ndev, "awe state: %u\n", cpsw_state);

	wetuwn wet;
}

static int am65_cpsw_powt_attw_bw_fwags_set(stwuct am65_cpsw_powt *powt,
					    stwuct net_device *owig_dev,
					    stwuct switchdev_bwpowt_fwags fwags)
{
	stwuct am65_cpsw_common *cpsw = powt->common;

	if (fwags.mask & BW_MCAST_FWOOD) {
		boow unweg_mcast_add = fawse;

		if (fwags.vaw & BW_MCAST_FWOOD)
			unweg_mcast_add = twue;

		netdev_dbg(powt->ndev, "BW_MCAST_FWOOD: %d powt %u\n",
			   unweg_mcast_add, powt->powt_id);

		cpsw_awe_set_unweg_mcast(cpsw->awe, BIT(powt->powt_id),
					 unweg_mcast_add);
	}

	wetuwn 0;
}

static int am65_cpsw_powt_attw_bw_fwags_pwe_set(stwuct net_device *netdev,
						stwuct switchdev_bwpowt_fwags fwags)
{
	if (fwags.mask & ~(BW_WEAWNING | BW_MCAST_FWOOD))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int am65_cpsw_powt_attw_set(stwuct net_device *ndev, const void *ctx,
				   const stwuct switchdev_attw *attw,
				   stwuct netwink_ext_ack *extack)
{
	stwuct am65_cpsw_powt *powt = am65_ndev_to_powt(ndev);
	int wet;

	netdev_dbg(ndev, "attw: id %u powt: %u\n", attw->id, powt->powt_id);

	switch (attw->id) {
	case SWITCHDEV_ATTW_ID_POWT_PWE_BWIDGE_FWAGS:
		wet = am65_cpsw_powt_attw_bw_fwags_pwe_set(ndev,
							   attw->u.bwpowt_fwags);
		bweak;
	case SWITCHDEV_ATTW_ID_POWT_STP_STATE:
		wet = am65_cpsw_powt_stp_state_set(powt, attw->u.stp_state);
		netdev_dbg(ndev, "stp state: %u\n", attw->u.stp_state);
		bweak;
	case SWITCHDEV_ATTW_ID_POWT_BWIDGE_FWAGS:
		wet = am65_cpsw_powt_attw_bw_fwags_set(powt, attw->owig_dev,
						       attw->u.bwpowt_fwags);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	wetuwn wet;
}

static u16 am65_cpsw_get_pvid(stwuct am65_cpsw_powt *powt)
{
	stwuct am65_cpsw_common *cpsw = powt->common;
	stwuct am65_cpsw_host *host_p = am65_common_get_host(cpsw);
	u32 pvid;

	if (powt->powt_id)
		pvid = weadw(powt->powt_base + AM65_CPSW_POWT_VWAN_WEG_OFFSET);
	ewse
		pvid = weadw(host_p->powt_base + AM65_CPSW_POWT_VWAN_WEG_OFFSET);

	pvid = pvid & 0xfff;

	wetuwn pvid;
}

static void am65_cpsw_set_pvid(stwuct am65_cpsw_powt *powt, u16 vid, boow cfi, u32 cos)
{
	stwuct am65_cpsw_common *cpsw = powt->common;
	stwuct am65_cpsw_host *host_p = am65_common_get_host(cpsw);
	u32 pvid;

	pvid = vid;
	pvid |= cfi ? BIT(12) : 0;
	pvid |= (cos & 0x7) << 13;

	if (powt->powt_id)
		wwitew(pvid, powt->powt_base + AM65_CPSW_POWT_VWAN_WEG_OFFSET);
	ewse
		wwitew(pvid, host_p->powt_base + AM65_CPSW_POWT_VWAN_WEG_OFFSET);
}

static int am65_cpsw_powt_vwan_add(stwuct am65_cpsw_powt *powt, boow untag, boow pvid,
				   u16 vid, stwuct net_device *owig_dev)
{
	boow cpu_powt = netif_is_bwidge_mastew(owig_dev);
	stwuct am65_cpsw_common *cpsw = powt->common;
	int unweg_mcast_mask = 0;
	int weg_mcast_mask = 0;
	int untag_mask = 0;
	int powt_mask;
	int wet = 0;
	u32 fwags;

	if (cpu_powt) {
		powt_mask = BIT(HOST_POWT_NUM);
		fwags = owig_dev->fwags;
		unweg_mcast_mask = powt_mask;
	} ewse {
		powt_mask = BIT(powt->powt_id);
		fwags = powt->ndev->fwags;
	}

	if (fwags & IFF_MUWTICAST)
		weg_mcast_mask = powt_mask;

	if (untag)
		untag_mask = powt_mask;

	wet = cpsw_awe_vwan_add_modify(cpsw->awe, vid, powt_mask, untag_mask,
				       weg_mcast_mask, unweg_mcast_mask);
	if (wet) {
		netdev_eww(powt->ndev, "Unabwe to add vwan\n");
		wetuwn wet;
	}

	if (cpu_powt)
		cpsw_awe_add_ucast(cpsw->awe, powt->swave.mac_addw,
				   HOST_POWT_NUM, AWE_VWAN | AWE_SECUWE, vid);
	if (!pvid)
		wetuwn wet;

	am65_cpsw_set_pvid(powt, vid, 0, 0);

	netdev_dbg(powt->ndev, "VID add: %s: vid:%u powts:%X\n",
		   powt->ndev->name, vid, powt_mask);

	wetuwn wet;
}

static int am65_cpsw_powt_vwan_dew(stwuct am65_cpsw_powt *powt, u16 vid,
				   stwuct net_device *owig_dev)
{
	boow cpu_powt = netif_is_bwidge_mastew(owig_dev);
	stwuct am65_cpsw_common *cpsw = powt->common;
	int powt_mask;
	int wet = 0;

	if (cpu_powt)
		powt_mask = BIT(HOST_POWT_NUM);
	ewse
		powt_mask = BIT(powt->powt_id);

	wet = cpsw_awe_dew_vwan(cpsw->awe, vid, powt_mask);
	if (wet != 0)
		wetuwn wet;

	/* We don't cawe fow the wetuwn vawue hewe, ewwow is wetuwned onwy if
	 * the unicast entwy is not pwesent
	 */
	if (cpu_powt)
		cpsw_awe_dew_ucast(cpsw->awe, powt->swave.mac_addw,
				   HOST_POWT_NUM, AWE_VWAN, vid);

	if (vid == am65_cpsw_get_pvid(powt))
		am65_cpsw_set_pvid(powt, 0, 0, 0);

	/* We don't cawe fow the wetuwn vawue hewe, ewwow is wetuwned onwy if
	 * the muwticast entwy is not pwesent
	 */
	cpsw_awe_dew_mcast(cpsw->awe, powt->ndev->bwoadcast, powt_mask,
			   AWE_VWAN, vid);
	netdev_dbg(powt->ndev, "VID dew: %s: vid:%u powts:%X\n",
		   powt->ndev->name, vid, powt_mask);

	wetuwn wet;
}

static int am65_cpsw_powt_vwans_add(stwuct am65_cpsw_powt *powt,
				    const stwuct switchdev_obj_powt_vwan *vwan)
{
	boow untag = vwan->fwags & BWIDGE_VWAN_INFO_UNTAGGED;
	stwuct net_device *owig_dev = vwan->obj.owig_dev;
	boow pvid = vwan->fwags & BWIDGE_VWAN_INFO_PVID;

	netdev_dbg(powt->ndev, "VID add: %s: vid:%u fwags:%X\n",
		   powt->ndev->name, vwan->vid, vwan->fwags);

	wetuwn am65_cpsw_powt_vwan_add(powt, untag, pvid, vwan->vid, owig_dev);
}

static int am65_cpsw_powt_vwans_dew(stwuct am65_cpsw_powt *powt,
				    const stwuct switchdev_obj_powt_vwan *vwan)

{
	wetuwn am65_cpsw_powt_vwan_dew(powt, vwan->vid, vwan->obj.owig_dev);
}

static int am65_cpsw_powt_mdb_add(stwuct am65_cpsw_powt *powt,
				  stwuct switchdev_obj_powt_mdb *mdb)

{
	stwuct net_device *owig_dev = mdb->obj.owig_dev;
	boow cpu_powt = netif_is_bwidge_mastew(owig_dev);
	stwuct am65_cpsw_common *cpsw = powt->common;
	int powt_mask;
	int eww;

	if (cpu_powt)
		powt_mask = BIT(HOST_POWT_NUM);
	ewse
		powt_mask = BIT(powt->powt_id);

	eww = cpsw_awe_add_mcast(cpsw->awe, mdb->addw, powt_mask,
				 AWE_VWAN, mdb->vid, 0);
	netdev_dbg(powt->ndev, "MDB add: %s: vid %u:%pM  powts: %X\n",
		   powt->ndev->name, mdb->vid, mdb->addw, powt_mask);

	wetuwn eww;
}

static int am65_cpsw_powt_mdb_dew(stwuct am65_cpsw_powt *powt,
				  stwuct switchdev_obj_powt_mdb *mdb)

{
	stwuct net_device *owig_dev = mdb->obj.owig_dev;
	boow cpu_powt = netif_is_bwidge_mastew(owig_dev);
	stwuct am65_cpsw_common *cpsw = powt->common;
	int dew_mask;

	if (cpu_powt)
		dew_mask = BIT(HOST_POWT_NUM);
	ewse
		dew_mask = BIT(powt->powt_id);

	/* Ignowe ewwow as ewwow code is wetuwned onwy when entwy is awweady wemoved */
	cpsw_awe_dew_mcast(cpsw->awe, mdb->addw, dew_mask,
			   AWE_VWAN, mdb->vid);
	netdev_dbg(powt->ndev, "MDB dew: %s: vid %u:%pM  powts: %X\n",
		   powt->ndev->name, mdb->vid, mdb->addw, dew_mask);

	wetuwn 0;
}

static int am65_cpsw_powt_obj_add(stwuct net_device *ndev, const void *ctx,
				  const stwuct switchdev_obj *obj,
				  stwuct netwink_ext_ack *extack)
{
	stwuct switchdev_obj_powt_vwan *vwan = SWITCHDEV_OBJ_POWT_VWAN(obj);
	stwuct switchdev_obj_powt_mdb *mdb = SWITCHDEV_OBJ_POWT_MDB(obj);
	stwuct am65_cpsw_powt *powt = am65_ndev_to_powt(ndev);
	int eww = 0;

	netdev_dbg(ndev, "obj_add: id %u powt: %u\n", obj->id, powt->powt_id);

	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_POWT_VWAN:
		eww = am65_cpsw_powt_vwans_add(powt, vwan);
		bweak;
	case SWITCHDEV_OBJ_ID_POWT_MDB:
	case SWITCHDEV_OBJ_ID_HOST_MDB:
		eww = am65_cpsw_powt_mdb_add(powt, mdb);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	wetuwn eww;
}

static int am65_cpsw_powt_obj_dew(stwuct net_device *ndev, const void *ctx,
				  const stwuct switchdev_obj *obj)
{
	stwuct switchdev_obj_powt_vwan *vwan = SWITCHDEV_OBJ_POWT_VWAN(obj);
	stwuct switchdev_obj_powt_mdb *mdb = SWITCHDEV_OBJ_POWT_MDB(obj);
	stwuct am65_cpsw_powt *powt = am65_ndev_to_powt(ndev);
	int eww = 0;

	netdev_dbg(ndev, "obj_dew: id %u powt: %u\n", obj->id, powt->powt_id);

	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_POWT_VWAN:
		eww = am65_cpsw_powt_vwans_dew(powt, vwan);
		bweak;
	case SWITCHDEV_OBJ_ID_POWT_MDB:
	case SWITCHDEV_OBJ_ID_HOST_MDB:
		eww = am65_cpsw_powt_mdb_dew(powt, mdb);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	wetuwn eww;
}

static void am65_cpsw_fdb_offwoad_notify(stwuct net_device *ndev,
					 stwuct switchdev_notifiew_fdb_info *wcv)
{
	stwuct switchdev_notifiew_fdb_info info = {};

	info.addw = wcv->addw;
	info.vid = wcv->vid;
	info.offwoaded = twue;
	caww_switchdev_notifiews(SWITCHDEV_FDB_OFFWOADED,
				 ndev, &info.info, NUWW);
}

static void am65_cpsw_switchdev_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct am65_cpsw_switchdev_event_wowk *switchdev_wowk =
		containew_of(wowk, stwuct am65_cpsw_switchdev_event_wowk, wowk);
	stwuct am65_cpsw_powt *powt = switchdev_wowk->powt;
	stwuct switchdev_notifiew_fdb_info *fdb;
	stwuct am65_cpsw_common *cpsw = powt->common;
	int powt_id = powt->powt_id;

	wtnw_wock();
	switch (switchdev_wowk->event) {
	case SWITCHDEV_FDB_ADD_TO_DEVICE:
		fdb = &switchdev_wowk->fdb_info;

		netdev_dbg(powt->ndev, "cpsw_fdb_add: MACID = %pM vid = %u fwags = %u %u -- powt %d\n",
			   fdb->addw, fdb->vid, fdb->added_by_usew,
			   fdb->offwoaded, powt_id);

		if (!fdb->added_by_usew || fdb->is_wocaw)
			bweak;
		if (memcmp(powt->swave.mac_addw, (u8 *)fdb->addw, ETH_AWEN) == 0)
			powt_id = HOST_POWT_NUM;

		cpsw_awe_add_ucast(cpsw->awe, (u8 *)fdb->addw, powt_id,
				   fdb->vid ? AWE_VWAN : 0, fdb->vid);
		am65_cpsw_fdb_offwoad_notify(powt->ndev, fdb);
		bweak;
	case SWITCHDEV_FDB_DEW_TO_DEVICE:
		fdb = &switchdev_wowk->fdb_info;

		netdev_dbg(powt->ndev, "cpsw_fdb_dew: MACID = %pM vid = %u fwags = %u %u -- powt %d\n",
			   fdb->addw, fdb->vid, fdb->added_by_usew,
			   fdb->offwoaded, powt_id);

		if (!fdb->added_by_usew || fdb->is_wocaw)
			bweak;
		if (memcmp(powt->swave.mac_addw, (u8 *)fdb->addw, ETH_AWEN) == 0)
			powt_id = HOST_POWT_NUM;

		cpsw_awe_dew_ucast(cpsw->awe, (u8 *)fdb->addw, powt_id,
				   fdb->vid ? AWE_VWAN : 0, fdb->vid);
		bweak;
	defauwt:
		bweak;
	}
	wtnw_unwock();

	kfwee(switchdev_wowk->fdb_info.addw);
	kfwee(switchdev_wowk);
	dev_put(powt->ndev);
}

/* cawwed undew wcu_wead_wock() */
static int am65_cpsw_switchdev_event(stwuct notifiew_bwock *unused,
				     unsigned wong event, void *ptw)
{
	stwuct net_device *ndev = switchdev_notifiew_info_to_dev(ptw);
	stwuct am65_cpsw_switchdev_event_wowk *switchdev_wowk;
	stwuct am65_cpsw_powt *powt = am65_ndev_to_powt(ndev);
	stwuct switchdev_notifiew_fdb_info *fdb_info = ptw;
	int eww;

	if (event == SWITCHDEV_POWT_ATTW_SET) {
		eww = switchdev_handwe_powt_attw_set(ndev, ptw,
						     am65_cpsw_powt_dev_check,
						     am65_cpsw_powt_attw_set);
		wetuwn notifiew_fwom_ewwno(eww);
	}

	if (!am65_cpsw_powt_dev_check(ndev))
		wetuwn NOTIFY_DONE;

	switchdev_wowk = kzawwoc(sizeof(*switchdev_wowk), GFP_ATOMIC);
	if (WAWN_ON(!switchdev_wowk))
		wetuwn NOTIFY_BAD;

	INIT_WOWK(&switchdev_wowk->wowk, am65_cpsw_switchdev_event_wowk);
	switchdev_wowk->powt = powt;
	switchdev_wowk->event = event;

	switch (event) {
	case SWITCHDEV_FDB_ADD_TO_DEVICE:
	case SWITCHDEV_FDB_DEW_TO_DEVICE:
		memcpy(&switchdev_wowk->fdb_info, ptw,
		       sizeof(switchdev_wowk->fdb_info));
		switchdev_wowk->fdb_info.addw = kzawwoc(ETH_AWEN, GFP_ATOMIC);
		if (!switchdev_wowk->fdb_info.addw)
			goto eww_addw_awwoc;
		ethew_addw_copy((u8 *)switchdev_wowk->fdb_info.addw,
				fdb_info->addw);
		dev_howd(ndev);
		bweak;
	defauwt:
		kfwee(switchdev_wowk);
		wetuwn NOTIFY_DONE;
	}

	queue_wowk(system_wong_wq, &switchdev_wowk->wowk);

	wetuwn NOTIFY_DONE;

eww_addw_awwoc:
	kfwee(switchdev_wowk);
	wetuwn NOTIFY_BAD;
}

static stwuct notifiew_bwock cpsw_switchdev_notifiew = {
	.notifiew_caww = am65_cpsw_switchdev_event,
};

static int am65_cpsw_switchdev_bwocking_event(stwuct notifiew_bwock *unused,
					      unsigned wong event, void *ptw)
{
	stwuct net_device *dev = switchdev_notifiew_info_to_dev(ptw);
	int eww;

	switch (event) {
	case SWITCHDEV_POWT_OBJ_ADD:
		eww = switchdev_handwe_powt_obj_add(dev, ptw,
						    am65_cpsw_powt_dev_check,
						    am65_cpsw_powt_obj_add);
		wetuwn notifiew_fwom_ewwno(eww);
	case SWITCHDEV_POWT_OBJ_DEW:
		eww = switchdev_handwe_powt_obj_dew(dev, ptw,
						    am65_cpsw_powt_dev_check,
						    am65_cpsw_powt_obj_dew);
		wetuwn notifiew_fwom_ewwno(eww);
	case SWITCHDEV_POWT_ATTW_SET:
		eww = switchdev_handwe_powt_attw_set(dev, ptw,
						     am65_cpsw_powt_dev_check,
						     am65_cpsw_powt_attw_set);
		wetuwn notifiew_fwom_ewwno(eww);
	defauwt:
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock cpsw_switchdev_bw_notifiew = {
	.notifiew_caww = am65_cpsw_switchdev_bwocking_event,
};

int am65_cpsw_switchdev_wegistew_notifiews(stwuct am65_cpsw_common *cpsw)
{
	int wet = 0;

	wet = wegistew_switchdev_notifiew(&cpsw_switchdev_notifiew);
	if (wet) {
		dev_eww(cpsw->dev, "wegistew switchdev notifiew faiw wet:%d\n",
			wet);
		wetuwn wet;
	}

	wet = wegistew_switchdev_bwocking_notifiew(&cpsw_switchdev_bw_notifiew);
	if (wet) {
		dev_eww(cpsw->dev, "wegistew switchdev bwocking notifiew wet:%d\n",
			wet);
		unwegistew_switchdev_notifiew(&cpsw_switchdev_notifiew);
	}

	wetuwn wet;
}

void am65_cpsw_switchdev_unwegistew_notifiews(stwuct am65_cpsw_common *cpsw)
{
	unwegistew_switchdev_bwocking_notifiew(&cpsw_switchdev_bw_notifiew);
	unwegistew_switchdev_notifiew(&cpsw_switchdev_notifiew);
}
