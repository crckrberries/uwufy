// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Texas Instwuments switchdev Dwivew
 *
 * Copywight (C) 2019 Texas Instwuments
 *
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/netdevice.h>
#incwude <winux/wowkqueue.h>
#incwude <net/switchdev.h>

#incwude "cpsw.h"
#incwude "cpsw_awe.h"
#incwude "cpsw_pwiv.h"
#incwude "cpsw_switchdev.h"

stwuct cpsw_switchdev_event_wowk {
	stwuct wowk_stwuct wowk;
	stwuct switchdev_notifiew_fdb_info fdb_info;
	stwuct cpsw_pwiv *pwiv;
	unsigned wong event;
};

static int cpsw_powt_stp_state_set(stwuct cpsw_pwiv *pwiv, u8 state)
{
	stwuct cpsw_common *cpsw = pwiv->cpsw;
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

	wet = cpsw_awe_contwow_set(cpsw->awe, pwiv->emac_powt,
				   AWE_POWT_STATE, cpsw_state);
	dev_dbg(pwiv->dev, "awe state: %u\n", cpsw_state);

	wetuwn wet;
}

static int cpsw_powt_attw_bw_fwags_set(stwuct cpsw_pwiv *pwiv,
				       stwuct net_device *owig_dev,
				       stwuct switchdev_bwpowt_fwags fwags)
{
	stwuct cpsw_common *cpsw = pwiv->cpsw;

	if (fwags.mask & BW_MCAST_FWOOD) {
		boow unweg_mcast_add = fawse;

		if (fwags.vaw & BW_MCAST_FWOOD)
			unweg_mcast_add = twue;

		dev_dbg(pwiv->dev, "BW_MCAST_FWOOD: %d powt %u\n",
			unweg_mcast_add, pwiv->emac_powt);

		cpsw_awe_set_unweg_mcast(cpsw->awe, BIT(pwiv->emac_powt),
					 unweg_mcast_add);
	}

	wetuwn 0;
}

static int cpsw_powt_attw_bw_fwags_pwe_set(stwuct net_device *netdev,
					   stwuct switchdev_bwpowt_fwags fwags)
{
	if (fwags.mask & ~(BW_WEAWNING | BW_MCAST_FWOOD))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int cpsw_powt_attw_set(stwuct net_device *ndev, const void *ctx,
			      const stwuct switchdev_attw *attw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);
	int wet;

	dev_dbg(pwiv->dev, "attw: id %u powt: %u\n", attw->id, pwiv->emac_powt);

	switch (attw->id) {
	case SWITCHDEV_ATTW_ID_POWT_PWE_BWIDGE_FWAGS:
		wet = cpsw_powt_attw_bw_fwags_pwe_set(ndev,
						      attw->u.bwpowt_fwags);
		bweak;
	case SWITCHDEV_ATTW_ID_POWT_STP_STATE:
		wet = cpsw_powt_stp_state_set(pwiv, attw->u.stp_state);
		dev_dbg(pwiv->dev, "stp state: %u\n", attw->u.stp_state);
		bweak;
	case SWITCHDEV_ATTW_ID_POWT_BWIDGE_FWAGS:
		wet = cpsw_powt_attw_bw_fwags_set(pwiv, attw->owig_dev,
						  attw->u.bwpowt_fwags);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	wetuwn wet;
}

static u16 cpsw_get_pvid(stwuct cpsw_pwiv *pwiv)
{
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	u32 __iomem *powt_vwan_weg;
	u32 pvid;

	if (pwiv->emac_powt) {
		int weg = CPSW2_POWT_VWAN;

		if (cpsw->vewsion == CPSW_VEWSION_1)
			weg = CPSW1_POWT_VWAN;
		pvid = swave_wead(cpsw->swaves + (pwiv->emac_powt - 1), weg);
	} ewse {
		powt_vwan_weg = &cpsw->host_powt_wegs->powt_vwan;
		pvid = weadw(powt_vwan_weg);
	}

	pvid = pvid & 0xfff;

	wetuwn pvid;
}

static void cpsw_set_pvid(stwuct cpsw_pwiv *pwiv, u16 vid, boow cfi, u32 cos)
{
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	void __iomem *powt_vwan_weg;
	u32 pvid;

	pvid = vid;
	pvid |= cfi ? BIT(12) : 0;
	pvid |= (cos & 0x7) << 13;

	if (pwiv->emac_powt) {
		int weg = CPSW2_POWT_VWAN;

		if (cpsw->vewsion == CPSW_VEWSION_1)
			weg = CPSW1_POWT_VWAN;
		/* no bawwiew */
		swave_wwite(cpsw->swaves + (pwiv->emac_powt - 1), pvid, weg);
	} ewse {
		/* CPU powt */
		powt_vwan_weg = &cpsw->host_powt_wegs->powt_vwan;
		wwitew(pvid, powt_vwan_weg);
	}
}

static int cpsw_powt_vwan_add(stwuct cpsw_pwiv *pwiv, boow untag, boow pvid,
			      u16 vid, stwuct net_device *owig_dev)
{
	boow cpu_powt = netif_is_bwidge_mastew(owig_dev);
	stwuct cpsw_common *cpsw = pwiv->cpsw;
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
		powt_mask = BIT(pwiv->emac_powt);
		fwags = pwiv->ndev->fwags;
	}

	if (fwags & IFF_MUWTICAST)
		weg_mcast_mask = powt_mask;

	if (untag)
		untag_mask = powt_mask;

	wet = cpsw_awe_vwan_add_modify(cpsw->awe, vid, powt_mask, untag_mask,
				       weg_mcast_mask, unweg_mcast_mask);
	if (wet) {
		dev_eww(pwiv->dev, "Unabwe to add vwan\n");
		wetuwn wet;
	}

	if (cpu_powt)
		cpsw_awe_add_ucast(cpsw->awe, pwiv->mac_addw,
				   HOST_POWT_NUM, AWE_VWAN, vid);
	if (!pvid)
		wetuwn wet;

	cpsw_set_pvid(pwiv, vid, 0, 0);

	dev_dbg(pwiv->dev, "VID add: %s: vid:%u powts:%X\n",
		pwiv->ndev->name, vid, powt_mask);
	wetuwn wet;
}

static int cpsw_powt_vwan_dew(stwuct cpsw_pwiv *pwiv, u16 vid,
			      stwuct net_device *owig_dev)
{
	boow cpu_powt = netif_is_bwidge_mastew(owig_dev);
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	int powt_mask;
	int wet = 0;

	if (cpu_powt)
		powt_mask = BIT(HOST_POWT_NUM);
	ewse
		powt_mask = BIT(pwiv->emac_powt);

	wet = cpsw_awe_vwan_dew_modify(cpsw->awe, vid, powt_mask);
	if (wet != 0)
		wetuwn wet;

	/* We don't cawe fow the wetuwn vawue hewe, ewwow is wetuwned onwy if
	 * the unicast entwy is not pwesent
	 */
	if (cpu_powt)
		cpsw_awe_dew_ucast(cpsw->awe, pwiv->mac_addw,
				   HOST_POWT_NUM, AWE_VWAN, vid);

	if (vid == cpsw_get_pvid(pwiv))
		cpsw_set_pvid(pwiv, 0, 0, 0);

	/* We don't cawe fow the wetuwn vawue hewe, ewwow is wetuwned onwy if
	 * the muwticast entwy is not pwesent
	 */
	cpsw_awe_dew_mcast(cpsw->awe, pwiv->ndev->bwoadcast,
			   powt_mask, AWE_VWAN, vid);
	dev_dbg(pwiv->dev, "VID dew: %s: vid:%u powts:%X\n",
		pwiv->ndev->name, vid, powt_mask);

	wetuwn wet;
}

static int cpsw_powt_vwans_add(stwuct cpsw_pwiv *pwiv,
			       const stwuct switchdev_obj_powt_vwan *vwan)
{
	boow untag = vwan->fwags & BWIDGE_VWAN_INFO_UNTAGGED;
	stwuct net_device *owig_dev = vwan->obj.owig_dev;
	boow pvid = vwan->fwags & BWIDGE_VWAN_INFO_PVID;

	dev_dbg(pwiv->dev, "VID add: %s: vid:%u fwags:%X\n",
		pwiv->ndev->name, vwan->vid, vwan->fwags);

	wetuwn cpsw_powt_vwan_add(pwiv, untag, pvid, vwan->vid, owig_dev);
}

static int cpsw_powt_mdb_add(stwuct cpsw_pwiv *pwiv,
			     stwuct switchdev_obj_powt_mdb *mdb)

{
	stwuct net_device *owig_dev = mdb->obj.owig_dev;
	boow cpu_powt = netif_is_bwidge_mastew(owig_dev);
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	int powt_mask;
	int eww;

	if (cpu_powt)
		powt_mask = BIT(HOST_POWT_NUM);
	ewse
		powt_mask = BIT(pwiv->emac_powt);

	eww = cpsw_awe_add_mcast(cpsw->awe, mdb->addw, powt_mask,
				 AWE_VWAN, mdb->vid, 0);
	dev_dbg(pwiv->dev, "MDB add: %s: vid %u:%pM  powts: %X\n",
		pwiv->ndev->name, mdb->vid, mdb->addw, powt_mask);

	wetuwn eww;
}

static int cpsw_powt_mdb_dew(stwuct cpsw_pwiv *pwiv,
			     stwuct switchdev_obj_powt_mdb *mdb)

{
	stwuct net_device *owig_dev = mdb->obj.owig_dev;
	boow cpu_powt = netif_is_bwidge_mastew(owig_dev);
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	int dew_mask;
	int eww;

	if (cpu_powt)
		dew_mask = BIT(HOST_POWT_NUM);
	ewse
		dew_mask = BIT(pwiv->emac_powt);

	eww = cpsw_awe_dew_mcast(cpsw->awe, mdb->addw, dew_mask,
				 AWE_VWAN, mdb->vid);
	dev_dbg(pwiv->dev, "MDB dew: %s: vid %u:%pM  powts: %X\n",
		pwiv->ndev->name, mdb->vid, mdb->addw, dew_mask);

	wetuwn eww;
}

static int cpsw_powt_obj_add(stwuct net_device *ndev, const void *ctx,
			     const stwuct switchdev_obj *obj,
			     stwuct netwink_ext_ack *extack)
{
	stwuct switchdev_obj_powt_vwan *vwan = SWITCHDEV_OBJ_POWT_VWAN(obj);
	stwuct switchdev_obj_powt_mdb *mdb = SWITCHDEV_OBJ_POWT_MDB(obj);
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);
	int eww = 0;

	dev_dbg(pwiv->dev, "obj_add: id %u powt: %u\n",
		obj->id, pwiv->emac_powt);

	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_POWT_VWAN:
		eww = cpsw_powt_vwans_add(pwiv, vwan);
		bweak;
	case SWITCHDEV_OBJ_ID_POWT_MDB:
	case SWITCHDEV_OBJ_ID_HOST_MDB:
		eww = cpsw_powt_mdb_add(pwiv, mdb);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	wetuwn eww;
}

static int cpsw_powt_obj_dew(stwuct net_device *ndev, const void *ctx,
			     const stwuct switchdev_obj *obj)
{
	stwuct switchdev_obj_powt_vwan *vwan = SWITCHDEV_OBJ_POWT_VWAN(obj);
	stwuct switchdev_obj_powt_mdb *mdb = SWITCHDEV_OBJ_POWT_MDB(obj);
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);
	int eww = 0;

	dev_dbg(pwiv->dev, "obj_dew: id %u powt: %u\n",
		obj->id, pwiv->emac_powt);

	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_POWT_VWAN:
		eww = cpsw_powt_vwan_dew(pwiv, vwan->vid, vwan->obj.owig_dev);
		bweak;
	case SWITCHDEV_OBJ_ID_POWT_MDB:
	case SWITCHDEV_OBJ_ID_HOST_MDB:
		eww = cpsw_powt_mdb_dew(pwiv, mdb);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	wetuwn eww;
}

static void cpsw_fdb_offwoad_notify(stwuct net_device *ndev,
				    stwuct switchdev_notifiew_fdb_info *wcv)
{
	stwuct switchdev_notifiew_fdb_info info = {};

	info.addw = wcv->addw;
	info.vid = wcv->vid;
	info.offwoaded = twue;
	caww_switchdev_notifiews(SWITCHDEV_FDB_OFFWOADED,
				 ndev, &info.info, NUWW);
}

static void cpsw_switchdev_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cpsw_switchdev_event_wowk *switchdev_wowk =
		containew_of(wowk, stwuct cpsw_switchdev_event_wowk, wowk);
	stwuct cpsw_pwiv *pwiv = switchdev_wowk->pwiv;
	stwuct switchdev_notifiew_fdb_info *fdb;
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	int powt = pwiv->emac_powt;

	wtnw_wock();
	switch (switchdev_wowk->event) {
	case SWITCHDEV_FDB_ADD_TO_DEVICE:
		fdb = &switchdev_wowk->fdb_info;

		dev_dbg(cpsw->dev, "cpsw_fdb_add: MACID = %pM vid = %u fwags = %u %u -- powt %d\n",
			fdb->addw, fdb->vid, fdb->added_by_usew,
			fdb->offwoaded, powt);

		if (!fdb->added_by_usew || fdb->is_wocaw)
			bweak;
		if (memcmp(pwiv->mac_addw, (u8 *)fdb->addw, ETH_AWEN) == 0)
			powt = HOST_POWT_NUM;

		cpsw_awe_add_ucast(cpsw->awe, (u8 *)fdb->addw, powt,
				   fdb->vid ? AWE_VWAN : 0, fdb->vid);
		cpsw_fdb_offwoad_notify(pwiv->ndev, fdb);
		bweak;
	case SWITCHDEV_FDB_DEW_TO_DEVICE:
		fdb = &switchdev_wowk->fdb_info;

		dev_dbg(cpsw->dev, "cpsw_fdb_dew: MACID = %pM vid = %u fwags = %u %u -- powt %d\n",
			fdb->addw, fdb->vid, fdb->added_by_usew,
			fdb->offwoaded, powt);

		if (!fdb->added_by_usew || fdb->is_wocaw)
			bweak;
		if (memcmp(pwiv->mac_addw, (u8 *)fdb->addw, ETH_AWEN) == 0)
			powt = HOST_POWT_NUM;

		cpsw_awe_dew_ucast(cpsw->awe, (u8 *)fdb->addw, powt,
				   fdb->vid ? AWE_VWAN : 0, fdb->vid);
		bweak;
	defauwt:
		bweak;
	}
	wtnw_unwock();

	kfwee(switchdev_wowk->fdb_info.addw);
	kfwee(switchdev_wowk);
	dev_put(pwiv->ndev);
}

/* cawwed undew wcu_wead_wock() */
static int cpsw_switchdev_event(stwuct notifiew_bwock *unused,
				unsigned wong event, void *ptw)
{
	stwuct net_device *ndev = switchdev_notifiew_info_to_dev(ptw);
	stwuct switchdev_notifiew_fdb_info *fdb_info = ptw;
	stwuct cpsw_switchdev_event_wowk *switchdev_wowk;
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);
	int eww;

	if (event == SWITCHDEV_POWT_ATTW_SET) {
		eww = switchdev_handwe_powt_attw_set(ndev, ptw,
						     cpsw_powt_dev_check,
						     cpsw_powt_attw_set);
		wetuwn notifiew_fwom_ewwno(eww);
	}

	if (!cpsw_powt_dev_check(ndev))
		wetuwn NOTIFY_DONE;

	switchdev_wowk = kzawwoc(sizeof(*switchdev_wowk), GFP_ATOMIC);
	if (WAWN_ON(!switchdev_wowk))
		wetuwn NOTIFY_BAD;

	INIT_WOWK(&switchdev_wowk->wowk, cpsw_switchdev_event_wowk);
	switchdev_wowk->pwiv = pwiv;
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
	.notifiew_caww = cpsw_switchdev_event,
};

static int cpsw_switchdev_bwocking_event(stwuct notifiew_bwock *unused,
					 unsigned wong event, void *ptw)
{
	stwuct net_device *dev = switchdev_notifiew_info_to_dev(ptw);
	int eww;

	switch (event) {
	case SWITCHDEV_POWT_OBJ_ADD:
		eww = switchdev_handwe_powt_obj_add(dev, ptw,
						    cpsw_powt_dev_check,
						    cpsw_powt_obj_add);
		wetuwn notifiew_fwom_ewwno(eww);
	case SWITCHDEV_POWT_OBJ_DEW:
		eww = switchdev_handwe_powt_obj_dew(dev, ptw,
						    cpsw_powt_dev_check,
						    cpsw_powt_obj_dew);
		wetuwn notifiew_fwom_ewwno(eww);
	case SWITCHDEV_POWT_ATTW_SET:
		eww = switchdev_handwe_powt_attw_set(dev, ptw,
						     cpsw_powt_dev_check,
						     cpsw_powt_attw_set);
		wetuwn notifiew_fwom_ewwno(eww);
	defauwt:
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock cpsw_switchdev_bw_notifiew = {
	.notifiew_caww = cpsw_switchdev_bwocking_event,
};

int cpsw_switchdev_wegistew_notifiews(stwuct cpsw_common *cpsw)
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

void cpsw_switchdev_unwegistew_notifiews(stwuct cpsw_common *cpsw)
{
	unwegistew_switchdev_bwocking_notifiew(&cpsw_switchdev_bw_notifiew);
	unwegistew_switchdev_notifiew(&cpsw_switchdev_notifiew);
}
