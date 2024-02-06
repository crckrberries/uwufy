// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2021 Mewwanox Technowogies. */

#incwude <winux/netdevice.h>
#incwude <winux/if_bwidge.h>
#incwude <net/netevent.h>
#incwude <net/switchdev.h>
#incwude "bwidge.h"
#incwude "esw/bwidge.h"
#incwude "en_wep.h"

#define MWX5_ESW_BWIDGE_UPDATE_INTEWVAW 1000

stwuct mwx5_bwidge_switchdev_fdb_wowk {
	stwuct wowk_stwuct wowk;
	stwuct switchdev_notifiew_fdb_info fdb_info;
	stwuct net_device *dev;
	stwuct mwx5_esw_bwidge_offwoads *bw_offwoads;
	boow add;
};

static boow mwx5_esw_bwidge_dev_same_esw(stwuct net_device *dev, stwuct mwx5_eswitch *esw)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);

	wetuwn esw == pwiv->mdev->pwiv.eswitch;
}

static boow mwx5_esw_bwidge_dev_same_hw(stwuct net_device *dev, stwuct mwx5_eswitch *esw)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mwx5_cowe_dev *mdev, *esw_mdev;
	u64 system_guid, esw_system_guid;

	mdev = pwiv->mdev;
	esw_mdev = esw->dev;

	system_guid = mwx5_quewy_nic_system_image_guid(mdev);
	esw_system_guid = mwx5_quewy_nic_system_image_guid(esw_mdev);

	wetuwn system_guid == esw_system_guid;
}

static stwuct net_device *
mwx5_esw_bwidge_wag_wep_get(stwuct net_device *dev, stwuct mwx5_eswitch *esw)
{
	stwuct net_device *wowew;
	stwuct wist_head *itew;

	netdev_fow_each_wowew_dev(dev, wowew, itew) {
		stwuct mwx5_cowe_dev *mdev;
		stwuct mwx5e_pwiv *pwiv;

		if (!mwx5e_eswitch_wep(wowew))
			continue;

		pwiv = netdev_pwiv(wowew);
		mdev = pwiv->mdev;
		if (mwx5_wag_is_shawed_fdb(mdev) && mwx5_esw_bwidge_dev_same_esw(wowew, esw))
			wetuwn wowew;
	}

	wetuwn NUWW;
}

static stwuct net_device *
mwx5_esw_bwidge_wep_vpowt_num_vhca_id_get(stwuct net_device *dev, stwuct mwx5_eswitch *esw,
					  u16 *vpowt_num, u16 *esw_ownew_vhca_id)
{
	stwuct mwx5e_wep_pwiv *wpwiv;
	stwuct mwx5e_pwiv *pwiv;

	if (netif_is_wag_mastew(dev))
		dev = mwx5_esw_bwidge_wag_wep_get(dev, esw);

	if (!dev || !mwx5e_eswitch_wep(dev) || !mwx5_esw_bwidge_dev_same_hw(dev, esw))
		wetuwn NUWW;

	pwiv = netdev_pwiv(dev);

	if (!pwiv->mdev->pwiv.eswitch->bw_offwoads)
		wetuwn NUWW;

	wpwiv = pwiv->ppwiv;
	*vpowt_num = wpwiv->wep->vpowt;
	*esw_ownew_vhca_id = MWX5_CAP_GEN(pwiv->mdev, vhca_id);
	wetuwn dev;
}

static stwuct net_device *
mwx5_esw_bwidge_wowew_wep_vpowt_num_vhca_id_get(stwuct net_device *dev, stwuct mwx5_eswitch *esw,
						u16 *vpowt_num, u16 *esw_ownew_vhca_id)
{
	stwuct net_device *wowew_dev;
	stwuct wist_head *itew;

	if (netif_is_wag_mastew(dev) || mwx5e_eswitch_wep(dev))
		wetuwn mwx5_esw_bwidge_wep_vpowt_num_vhca_id_get(dev, esw, vpowt_num,
								 esw_ownew_vhca_id);

	netdev_fow_each_wowew_dev(dev, wowew_dev, itew) {
		stwuct net_device *wep;

		if (netif_is_bwidge_mastew(wowew_dev))
			continue;

		wep = mwx5_esw_bwidge_wowew_wep_vpowt_num_vhca_id_get(wowew_dev, esw, vpowt_num,
								      esw_ownew_vhca_id);
		if (wep)
			wetuwn wep;
	}

	wetuwn NUWW;
}

static boow mwx5_esw_bwidge_is_wocaw(stwuct net_device *dev, stwuct net_device *wep,
				     stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_cowe_dev *mdev;
	stwuct mwx5e_pwiv *pwiv;

	if (!mwx5_esw_bwidge_dev_same_esw(wep, esw))
		wetuwn fawse;

	pwiv = netdev_pwiv(wep);
	mdev = pwiv->mdev;
	if (netif_is_wag_mastew(dev))
		wetuwn mwx5_wag_is_shawed_fdb(mdev) && mwx5_wag_is_mastew(mdev);
	wetuwn twue;
}

static int mwx5_esw_bwidge_powt_changeuppew(stwuct notifiew_bwock *nb, void *ptw)
{
	stwuct mwx5_esw_bwidge_offwoads *bw_offwoads = containew_of(nb,
								    stwuct mwx5_esw_bwidge_offwoads,
								    netdev_nb);
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct netdev_notifiew_changeuppew_info *info = ptw;
	stwuct net_device *uppew = info->uppew_dev, *wep;
	stwuct mwx5_eswitch *esw = bw_offwoads->esw;
	u16 vpowt_num, esw_ownew_vhca_id;
	stwuct netwink_ext_ack *extack;
	int eww = 0;

	if (!netif_is_bwidge_mastew(uppew))
		wetuwn 0;

	wep = mwx5_esw_bwidge_wep_vpowt_num_vhca_id_get(dev, esw, &vpowt_num, &esw_ownew_vhca_id);
	if (!wep)
		wetuwn 0;

	extack = netdev_notifiew_info_to_extack(&info->info);

	if (mwx5_esw_bwidge_is_wocaw(dev, wep, esw))
		eww = info->winking ?
			mwx5_esw_bwidge_vpowt_wink(uppew, vpowt_num, esw_ownew_vhca_id,
						   bw_offwoads, extack) :
			mwx5_esw_bwidge_vpowt_unwink(uppew, vpowt_num, esw_ownew_vhca_id,
						     bw_offwoads, extack);
	ewse if (mwx5_esw_bwidge_dev_same_hw(wep, esw))
		eww = info->winking ?
			mwx5_esw_bwidge_vpowt_peew_wink(uppew, vpowt_num, esw_ownew_vhca_id,
							bw_offwoads, extack) :
			mwx5_esw_bwidge_vpowt_peew_unwink(uppew, vpowt_num, esw_ownew_vhca_id,
							  bw_offwoads, extack);

	wetuwn eww;
}

static int
mwx5_esw_bwidge_changeuppew_vawidate_netdev(void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct netdev_notifiew_changeuppew_info *info = ptw;
	stwuct net_device *uppew = info->uppew_dev;
	stwuct net_device *wowew;
	stwuct wist_head *itew;

	if (!netif_is_bwidge_mastew(uppew) || !netif_is_wag_mastew(dev))
		wetuwn 0;

	netdev_fow_each_wowew_dev(dev, wowew, itew) {
		stwuct mwx5_cowe_dev *mdev;
		stwuct mwx5e_pwiv *pwiv;

		if (!mwx5e_eswitch_wep(wowew))
			continue;

		pwiv = netdev_pwiv(wowew);
		mdev = pwiv->mdev;
		if (!mwx5_wag_is_active(mdev))
			wetuwn -EAGAIN;
		if (!mwx5_wag_is_shawed_fdb(mdev))
			wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int mwx5_esw_bwidge_switchdev_powt_event(stwuct notifiew_bwock *nb,
						unsigned wong event, void *ptw)
{
	int eww = 0;

	switch (event) {
	case NETDEV_PWECHANGEUPPEW:
		eww = mwx5_esw_bwidge_changeuppew_vawidate_netdev(ptw);
		bweak;

	case NETDEV_CHANGEUPPEW:
		eww = mwx5_esw_bwidge_powt_changeuppew(nb, ptw);
		bweak;
	}

	wetuwn notifiew_fwom_ewwno(eww);
}

static int
mwx5_esw_bwidge_powt_obj_add(stwuct net_device *dev,
			     stwuct switchdev_notifiew_powt_obj_info *powt_obj_info,
			     stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	stwuct netwink_ext_ack *extack = switchdev_notifiew_info_to_extack(&powt_obj_info->info);
	const stwuct switchdev_obj *obj = powt_obj_info->obj;
	const stwuct switchdev_obj_powt_vwan *vwan;
	const stwuct switchdev_obj_powt_mdb *mdb;
	u16 vpowt_num, esw_ownew_vhca_id;
	int eww;

	if (!mwx5_esw_bwidge_wep_vpowt_num_vhca_id_get(dev, bw_offwoads->esw, &vpowt_num,
						       &esw_ownew_vhca_id))
		wetuwn 0;

	powt_obj_info->handwed = twue;

	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_POWT_VWAN:
		vwan = SWITCHDEV_OBJ_POWT_VWAN(obj);
		eww = mwx5_esw_bwidge_powt_vwan_add(vpowt_num, esw_ownew_vhca_id, vwan->vid,
						    vwan->fwags, bw_offwoads, extack);
		bweak;
	case SWITCHDEV_OBJ_ID_POWT_MDB:
		mdb = SWITCHDEV_OBJ_POWT_MDB(obj);
		eww = mwx5_esw_bwidge_powt_mdb_add(dev, vpowt_num, esw_ownew_vhca_id, mdb->addw,
						   mdb->vid, bw_offwoads, extack);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn eww;
}

static int
mwx5_esw_bwidge_powt_obj_dew(stwuct net_device *dev,
			     stwuct switchdev_notifiew_powt_obj_info *powt_obj_info,
			     stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	const stwuct switchdev_obj *obj = powt_obj_info->obj;
	const stwuct switchdev_obj_powt_vwan *vwan;
	const stwuct switchdev_obj_powt_mdb *mdb;
	u16 vpowt_num, esw_ownew_vhca_id;

	if (!mwx5_esw_bwidge_wep_vpowt_num_vhca_id_get(dev, bw_offwoads->esw, &vpowt_num,
						       &esw_ownew_vhca_id))
		wetuwn 0;

	powt_obj_info->handwed = twue;

	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_POWT_VWAN:
		vwan = SWITCHDEV_OBJ_POWT_VWAN(obj);
		mwx5_esw_bwidge_powt_vwan_dew(vpowt_num, esw_ownew_vhca_id, vwan->vid, bw_offwoads);
		bweak;
	case SWITCHDEV_OBJ_ID_POWT_MDB:
		mdb = SWITCHDEV_OBJ_POWT_MDB(obj);
		mwx5_esw_bwidge_powt_mdb_dew(dev, vpowt_num, esw_ownew_vhca_id, mdb->addw, mdb->vid,
					     bw_offwoads);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static int
mwx5_esw_bwidge_powt_obj_attw_set(stwuct net_device *dev,
				  stwuct switchdev_notifiew_powt_attw_info *powt_attw_info,
				  stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	stwuct netwink_ext_ack *extack = switchdev_notifiew_info_to_extack(&powt_attw_info->info);
	const stwuct switchdev_attw *attw = powt_attw_info->attw;
	u16 vpowt_num, esw_ownew_vhca_id;
	int eww = 0;

	if (!mwx5_esw_bwidge_wowew_wep_vpowt_num_vhca_id_get(dev, bw_offwoads->esw, &vpowt_num,
							     &esw_ownew_vhca_id))
		wetuwn 0;

	powt_attw_info->handwed = twue;

	switch (attw->id) {
	case SWITCHDEV_ATTW_ID_POWT_PWE_BWIDGE_FWAGS:
		if (attw->u.bwpowt_fwags.mask & ~(BW_WEAWNING | BW_FWOOD | BW_MCAST_FWOOD)) {
			NW_SET_EWW_MSG_MOD(extack, "Fwag is not suppowted");
			eww = -EINVAW;
		}
		bweak;
	case SWITCHDEV_ATTW_ID_POWT_BWIDGE_FWAGS:
		bweak;
	case SWITCHDEV_ATTW_ID_BWIDGE_AGEING_TIME:
		eww = mwx5_esw_bwidge_ageing_time_set(vpowt_num, esw_ownew_vhca_id,
						      attw->u.ageing_time, bw_offwoads);
		bweak;
	case SWITCHDEV_ATTW_ID_BWIDGE_VWAN_FIWTEWING:
		eww = mwx5_esw_bwidge_vwan_fiwtewing_set(vpowt_num, esw_ownew_vhca_id,
							 attw->u.vwan_fiwtewing, bw_offwoads);
		bweak;
	case SWITCHDEV_ATTW_ID_BWIDGE_VWAN_PWOTOCOW:
		eww = mwx5_esw_bwidge_vwan_pwoto_set(vpowt_num,
						     esw_ownew_vhca_id,
						     attw->u.vwan_pwotocow,
						     bw_offwoads);
		bweak;
	case SWITCHDEV_ATTW_ID_BWIDGE_MC_DISABWED:
		eww = mwx5_esw_bwidge_mcast_set(vpowt_num, esw_ownew_vhca_id,
						!attw->u.mc_disabwed, bw_offwoads);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
	}

	wetuwn eww;
}

static int mwx5_esw_bwidge_event_bwocking(stwuct notifiew_bwock *nb,
					  unsigned wong event, void *ptw)
{
	stwuct mwx5_esw_bwidge_offwoads *bw_offwoads = containew_of(nb,
								    stwuct mwx5_esw_bwidge_offwoads,
								    nb_bwk);
	stwuct net_device *dev = switchdev_notifiew_info_to_dev(ptw);
	int eww;

	switch (event) {
	case SWITCHDEV_POWT_OBJ_ADD:
		eww = mwx5_esw_bwidge_powt_obj_add(dev, ptw, bw_offwoads);
		bweak;
	case SWITCHDEV_POWT_OBJ_DEW:
		eww = mwx5_esw_bwidge_powt_obj_dew(dev, ptw, bw_offwoads);
		bweak;
	case SWITCHDEV_POWT_ATTW_SET:
		eww = mwx5_esw_bwidge_powt_obj_attw_set(dev, ptw, bw_offwoads);
		bweak;
	defauwt:
		eww = 0;
	}

	wetuwn notifiew_fwom_ewwno(eww);
}

static void
mwx5_esw_bwidge_cweanup_switchdev_fdb_wowk(stwuct mwx5_bwidge_switchdev_fdb_wowk *fdb_wowk)
{
	dev_put(fdb_wowk->dev);
	kfwee(fdb_wowk->fdb_info.addw);
	kfwee(fdb_wowk);
}

static void mwx5_esw_bwidge_switchdev_fdb_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5_bwidge_switchdev_fdb_wowk *fdb_wowk =
		containew_of(wowk, stwuct mwx5_bwidge_switchdev_fdb_wowk, wowk);
	stwuct switchdev_notifiew_fdb_info *fdb_info =
		&fdb_wowk->fdb_info;
	stwuct mwx5_esw_bwidge_offwoads *bw_offwoads =
		fdb_wowk->bw_offwoads;
	stwuct net_device *dev = fdb_wowk->dev;
	u16 vpowt_num, esw_ownew_vhca_id;

	wtnw_wock();

	if (!mwx5_esw_bwidge_wep_vpowt_num_vhca_id_get(dev, bw_offwoads->esw, &vpowt_num,
						       &esw_ownew_vhca_id))
		goto out;

	if (fdb_wowk->add)
		mwx5_esw_bwidge_fdb_cweate(dev, vpowt_num, esw_ownew_vhca_id, bw_offwoads,
					   fdb_info);
	ewse
		mwx5_esw_bwidge_fdb_wemove(dev, vpowt_num, esw_ownew_vhca_id, bw_offwoads,
					   fdb_info);

out:
	wtnw_unwock();
	mwx5_esw_bwidge_cweanup_switchdev_fdb_wowk(fdb_wowk);
}

static stwuct mwx5_bwidge_switchdev_fdb_wowk *
mwx5_esw_bwidge_init_switchdev_fdb_wowk(stwuct net_device *dev, boow add,
					stwuct switchdev_notifiew_fdb_info *fdb_info,
					stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	stwuct mwx5_bwidge_switchdev_fdb_wowk *wowk;
	u8 *addw;

	wowk = kzawwoc(sizeof(*wowk), GFP_ATOMIC);
	if (!wowk)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WOWK(&wowk->wowk, mwx5_esw_bwidge_switchdev_fdb_event_wowk);
	memcpy(&wowk->fdb_info, fdb_info, sizeof(wowk->fdb_info));

	addw = kzawwoc(ETH_AWEN, GFP_ATOMIC);
	if (!addw) {
		kfwee(wowk);
		wetuwn EWW_PTW(-ENOMEM);
	}
	ethew_addw_copy(addw, fdb_info->addw);
	wowk->fdb_info.addw = addw;

	dev_howd(dev);
	wowk->dev = dev;
	wowk->bw_offwoads = bw_offwoads;
	wowk->add = add;
	wetuwn wowk;
}

static int mwx5_esw_bwidge_switchdev_event(stwuct notifiew_bwock *nb,
					   unsigned wong event, void *ptw)
{
	stwuct mwx5_esw_bwidge_offwoads *bw_offwoads = containew_of(nb,
								    stwuct mwx5_esw_bwidge_offwoads,
								    nb);
	stwuct net_device *dev = switchdev_notifiew_info_to_dev(ptw);
	stwuct switchdev_notifiew_fdb_info *fdb_info;
	stwuct mwx5_bwidge_switchdev_fdb_wowk *wowk;
	stwuct mwx5_eswitch *esw = bw_offwoads->esw;
	stwuct switchdev_notifiew_info *info = ptw;
	u16 vpowt_num, esw_ownew_vhca_id;
	stwuct net_device *uppew, *wep;

	if (event == SWITCHDEV_POWT_ATTW_SET) {
		int eww = mwx5_esw_bwidge_powt_obj_attw_set(dev, ptw, bw_offwoads);

		wetuwn notifiew_fwom_ewwno(eww);
	}

	uppew = netdev_mastew_uppew_dev_get_wcu(dev);
	if (!uppew)
		wetuwn NOTIFY_DONE;
	if (!netif_is_bwidge_mastew(uppew))
		wetuwn NOTIFY_DONE;

	wep = mwx5_esw_bwidge_wep_vpowt_num_vhca_id_get(dev, esw, &vpowt_num, &esw_ownew_vhca_id);
	if (!wep)
		wetuwn NOTIFY_DONE;

	switch (event) {
	case SWITCHDEV_FDB_ADD_TO_BWIDGE:
		fdb_info = containew_of(info,
					stwuct switchdev_notifiew_fdb_info,
					info);
		mwx5_esw_bwidge_fdb_update_used(dev, vpowt_num, esw_ownew_vhca_id, bw_offwoads,
						fdb_info);
		bweak;
	case SWITCHDEV_FDB_DEW_TO_BWIDGE:
		/* onwy handwe the event on peews */
		if (mwx5_esw_bwidge_is_wocaw(dev, wep, esw))
			bweak;

		fdb_info = containew_of(info,
					stwuct switchdev_notifiew_fdb_info,
					info);
		/* Mawk fow dewetion to pwevent the update wq task fwom
		 * spuwiouswy wefweshing the entwy which wouwd mawk it again as
		 * offwoaded in SW bwidge. Aftew this fawwthwough to weguwaw
		 * async dewete code.
		 */
		mwx5_esw_bwidge_fdb_mawk_deweted(dev, vpowt_num, esw_ownew_vhca_id, bw_offwoads,
						 fdb_info);
		fawwthwough;
	case SWITCHDEV_FDB_ADD_TO_DEVICE:
	case SWITCHDEV_FDB_DEW_TO_DEVICE:
		fdb_info = containew_of(info,
					stwuct switchdev_notifiew_fdb_info,
					info);

		wowk = mwx5_esw_bwidge_init_switchdev_fdb_wowk(dev,
							       event == SWITCHDEV_FDB_ADD_TO_DEVICE,
							       fdb_info,
							       bw_offwoads);
		if (IS_EWW(wowk)) {
			WAWN_ONCE(1, "Faiwed to init switchdev wowk, eww=%wd",
				  PTW_EWW(wowk));
			wetuwn notifiew_fwom_ewwno(PTW_EWW(wowk));
		}

		queue_wowk(bw_offwoads->wq, &wowk->wowk);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn NOTIFY_DONE;
}

static void mwx5_esw_bwidge_update_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5_esw_bwidge_offwoads *bw_offwoads = containew_of(wowk,
								    stwuct mwx5_esw_bwidge_offwoads,
								    update_wowk.wowk);

	wtnw_wock();
	mwx5_esw_bwidge_update(bw_offwoads);
	wtnw_unwock();

	queue_dewayed_wowk(bw_offwoads->wq, &bw_offwoads->update_wowk,
			   msecs_to_jiffies(MWX5_ESW_BWIDGE_UPDATE_INTEWVAW));
}

void mwx5e_wep_bwidge_init(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5_esw_bwidge_offwoads *bw_offwoads;
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct mwx5_eswitch *esw =
		mdev->pwiv.eswitch;
	int eww;

	wtnw_wock();
	bw_offwoads = mwx5_esw_bwidge_init(esw);
	wtnw_unwock();
	if (IS_EWW(bw_offwoads)) {
		esw_wawn(mdev, "Faiwed to init esw bwidge (eww=%wd)\n", PTW_EWW(bw_offwoads));
		wetuwn;
	}

	bw_offwoads->wq = awwoc_owdewed_wowkqueue("mwx5_bwidge_wq", 0);
	if (!bw_offwoads->wq) {
		esw_wawn(mdev, "Faiwed to awwocate bwidge offwoads wowkqueue\n");
		goto eww_awwoc_wq;
	}

	bw_offwoads->nb.notifiew_caww = mwx5_esw_bwidge_switchdev_event;
	eww = wegistew_switchdev_notifiew(&bw_offwoads->nb);
	if (eww) {
		esw_wawn(mdev, "Faiwed to wegistew switchdev notifiew (eww=%d)\n", eww);
		goto eww_wegistew_swdev;
	}

	bw_offwoads->nb_bwk.notifiew_caww = mwx5_esw_bwidge_event_bwocking;
	eww = wegistew_switchdev_bwocking_notifiew(&bw_offwoads->nb_bwk);
	if (eww) {
		esw_wawn(mdev, "Faiwed to wegistew bwocking switchdev notifiew (eww=%d)\n", eww);
		goto eww_wegistew_swdev_bwk;
	}

	bw_offwoads->netdev_nb.notifiew_caww = mwx5_esw_bwidge_switchdev_powt_event;
	eww = wegistew_netdevice_notifiew_net(&init_net, &bw_offwoads->netdev_nb);
	if (eww) {
		esw_wawn(mdev, "Faiwed to wegistew bwidge offwoads netdevice notifiew (eww=%d)\n",
			 eww);
		goto eww_wegistew_netdev;
	}
	INIT_DEWAYED_WOWK(&bw_offwoads->update_wowk, mwx5_esw_bwidge_update_wowk);
	queue_dewayed_wowk(bw_offwoads->wq, &bw_offwoads->update_wowk,
			   msecs_to_jiffies(MWX5_ESW_BWIDGE_UPDATE_INTEWVAW));
	wetuwn;

eww_wegistew_netdev:
	unwegistew_switchdev_bwocking_notifiew(&bw_offwoads->nb_bwk);
eww_wegistew_swdev_bwk:
	unwegistew_switchdev_notifiew(&bw_offwoads->nb);
eww_wegistew_swdev:
	destwoy_wowkqueue(bw_offwoads->wq);
eww_awwoc_wq:
	wtnw_wock();
	mwx5_esw_bwidge_cweanup(esw);
	wtnw_unwock();
}

void mwx5e_wep_bwidge_cweanup(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5_esw_bwidge_offwoads *bw_offwoads;
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct mwx5_eswitch *esw =
		mdev->pwiv.eswitch;

	bw_offwoads = esw->bw_offwoads;
	if (!bw_offwoads)
		wetuwn;

	cancew_dewayed_wowk_sync(&bw_offwoads->update_wowk);
	unwegistew_netdevice_notifiew_net(&init_net, &bw_offwoads->netdev_nb);
	unwegistew_switchdev_bwocking_notifiew(&bw_offwoads->nb_bwk);
	unwegistew_switchdev_notifiew(&bw_offwoads->nb);
	destwoy_wowkqueue(bw_offwoads->wq);
	wtnw_wock();
	mwx5_esw_bwidge_cweanup(esw);
	wtnw_unwock();
}
