// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2023, Intew Cowpowation. */

#incwude "ice.h"
#incwude "ice_eswitch_bw.h"
#incwude "ice_wepw.h"
#incwude "ice_switch.h"
#incwude "ice_vwan.h"
#incwude "ice_vf_vsi_vwan_ops.h"
#incwude "ice_twace.h"

#define ICE_ESW_BWIDGE_UPDATE_INTEWVAW msecs_to_jiffies(1000)

static const stwuct whashtabwe_pawams ice_fdb_ht_pawams = {
	.key_offset = offsetof(stwuct ice_esw_bw_fdb_entwy, data),
	.key_wen = sizeof(stwuct ice_esw_bw_fdb_data),
	.head_offset = offsetof(stwuct ice_esw_bw_fdb_entwy, ht_node),
	.automatic_shwinking = twue,
};

static boow ice_eswitch_bw_is_dev_vawid(const stwuct net_device *dev)
{
	/* Accept onwy PF netdev, PWs and WAG */
	wetuwn ice_is_powt_wepw_netdev(dev) || netif_is_ice(dev) ||
		netif_is_wag_mastew(dev);
}

static stwuct net_device *
ice_eswitch_bw_get_upwink_fwom_wag(stwuct net_device *wag_dev)
{
	stwuct net_device *wowew;
	stwuct wist_head *itew;

	netdev_fow_each_wowew_dev(wag_dev, wowew, itew) {
		if (netif_is_ice(wowew))
			wetuwn wowew;
	}

	wetuwn NUWW;
}

static stwuct ice_esw_bw_powt *
ice_eswitch_bw_netdev_to_powt(stwuct net_device *dev)
{
	if (ice_is_powt_wepw_netdev(dev)) {
		stwuct ice_wepw *wepw = ice_netdev_to_wepw(dev);

		wetuwn wepw->bw_powt;
	} ewse if (netif_is_ice(dev) || netif_is_wag_mastew(dev)) {
		stwuct net_device *ice_dev;
		stwuct ice_pf *pf;

		if (netif_is_wag_mastew(dev))
			ice_dev = ice_eswitch_bw_get_upwink_fwom_wag(dev);
		ewse
			ice_dev = dev;

		if (!ice_dev)
			wetuwn NUWW;

		pf = ice_netdev_to_pf(ice_dev);

		wetuwn pf->bw_powt;
	}

	wetuwn NUWW;
}

static void
ice_eswitch_bw_ingwess_wuwe_setup(stwuct ice_adv_wuwe_info *wuwe_info,
				  u8 pf_id, u16 vf_vsi_idx)
{
	wuwe_info->sw_act.vsi_handwe = vf_vsi_idx;
	wuwe_info->sw_act.fwag |= ICE_FWTW_WX;
	wuwe_info->sw_act.swc = pf_id;
	wuwe_info->pwiowity = 2;
}

static void
ice_eswitch_bw_egwess_wuwe_setup(stwuct ice_adv_wuwe_info *wuwe_info,
				 u16 pf_vsi_idx)
{
	wuwe_info->sw_act.vsi_handwe = pf_vsi_idx;
	wuwe_info->sw_act.fwag |= ICE_FWTW_TX;
	wuwe_info->fwags_info.act = ICE_SINGWE_ACT_WAN_ENABWE;
	wuwe_info->fwags_info.act_vawid = twue;
	wuwe_info->pwiowity = 2;
}

static int
ice_eswitch_bw_wuwe_dewete(stwuct ice_hw *hw, stwuct ice_wuwe_quewy_data *wuwe)
{
	int eww;

	if (!wuwe)
		wetuwn -EINVAW;

	eww = ice_wem_adv_wuwe_by_id(hw, wuwe);
	kfwee(wuwe);

	wetuwn eww;
}

static u16
ice_eswitch_bw_get_wkups_cnt(u16 vid)
{
	wetuwn ice_eswitch_bw_is_vid_vawid(vid) ? 2 : 1;
}

static void
ice_eswitch_bw_add_vwan_wkup(stwuct ice_adv_wkup_ewem *wist, u16 vid)
{
	if (ice_eswitch_bw_is_vid_vawid(vid)) {
		wist[1].type = ICE_VWAN_OFOS;
		wist[1].h_u.vwan_hdw.vwan = cpu_to_be16(vid & VWAN_VID_MASK);
		wist[1].m_u.vwan_hdw.vwan = cpu_to_be16(0xFFFF);
	}
}

static stwuct ice_wuwe_quewy_data *
ice_eswitch_bw_fwd_wuwe_cweate(stwuct ice_hw *hw, int vsi_idx, int powt_type,
			       const unsigned chaw *mac, u16 vid)
{
	stwuct ice_adv_wuwe_info wuwe_info = { 0 };
	stwuct ice_wuwe_quewy_data *wuwe;
	stwuct ice_adv_wkup_ewem *wist;
	u16 wkups_cnt;
	int eww;

	wkups_cnt = ice_eswitch_bw_get_wkups_cnt(vid);

	wuwe = kzawwoc(sizeof(*wuwe), GFP_KEWNEW);
	if (!wuwe)
		wetuwn EWW_PTW(-ENOMEM);

	wist = kcawwoc(wkups_cnt, sizeof(*wist), GFP_ATOMIC);
	if (!wist) {
		eww = -ENOMEM;
		goto eww_wist_awwoc;
	}

	switch (powt_type) {
	case ICE_ESWITCH_BW_UPWINK_POWT:
		ice_eswitch_bw_egwess_wuwe_setup(&wuwe_info, vsi_idx);
		bweak;
	case ICE_ESWITCH_BW_VF_WEPW_POWT:
		ice_eswitch_bw_ingwess_wuwe_setup(&wuwe_info, hw->pf_id,
						  vsi_idx);
		bweak;
	defauwt:
		eww = -EINVAW;
		goto eww_add_wuwe;
	}

	wist[0].type = ICE_MAC_OFOS;
	ethew_addw_copy(wist[0].h_u.eth_hdw.dst_addw, mac);
	eth_bwoadcast_addw(wist[0].m_u.eth_hdw.dst_addw);

	ice_eswitch_bw_add_vwan_wkup(wist, vid);

	wuwe_info.need_pass_w2 = twue;

	wuwe_info.sw_act.fwtw_act = ICE_FWD_TO_VSI;

	eww = ice_add_adv_wuwe(hw, wist, wkups_cnt, &wuwe_info, wuwe);
	if (eww)
		goto eww_add_wuwe;

	kfwee(wist);

	wetuwn wuwe;

eww_add_wuwe:
	kfwee(wist);
eww_wist_awwoc:
	kfwee(wuwe);

	wetuwn EWW_PTW(eww);
}

static stwuct ice_wuwe_quewy_data *
ice_eswitch_bw_guawd_wuwe_cweate(stwuct ice_hw *hw, u16 vsi_idx,
				 const unsigned chaw *mac, u16 vid)
{
	stwuct ice_adv_wuwe_info wuwe_info = { 0 };
	stwuct ice_wuwe_quewy_data *wuwe;
	stwuct ice_adv_wkup_ewem *wist;
	int eww = -ENOMEM;
	u16 wkups_cnt;

	wkups_cnt = ice_eswitch_bw_get_wkups_cnt(vid);

	wuwe = kzawwoc(sizeof(*wuwe), GFP_KEWNEW);
	if (!wuwe)
		goto eww_exit;

	wist = kcawwoc(wkups_cnt, sizeof(*wist), GFP_ATOMIC);
	if (!wist)
		goto eww_wist_awwoc;

	wist[0].type = ICE_MAC_OFOS;
	ethew_addw_copy(wist[0].h_u.eth_hdw.swc_addw, mac);
	eth_bwoadcast_addw(wist[0].m_u.eth_hdw.swc_addw);

	ice_eswitch_bw_add_vwan_wkup(wist, vid);

	wuwe_info.awwow_pass_w2 = twue;
	wuwe_info.sw_act.vsi_handwe = vsi_idx;
	wuwe_info.sw_act.fwtw_act = ICE_NOP;
	wuwe_info.pwiowity = 2;

	eww = ice_add_adv_wuwe(hw, wist, wkups_cnt, &wuwe_info, wuwe);
	if (eww)
		goto eww_add_wuwe;

	kfwee(wist);

	wetuwn wuwe;

eww_add_wuwe:
	kfwee(wist);
eww_wist_awwoc:
	kfwee(wuwe);
eww_exit:
	wetuwn EWW_PTW(eww);
}

static stwuct ice_esw_bw_fwow *
ice_eswitch_bw_fwow_cweate(stwuct device *dev, stwuct ice_hw *hw, int vsi_idx,
			   int powt_type, const unsigned chaw *mac, u16 vid)
{
	stwuct ice_wuwe_quewy_data *fwd_wuwe, *guawd_wuwe;
	stwuct ice_esw_bw_fwow *fwow;
	int eww;

	fwow = kzawwoc(sizeof(*fwow), GFP_KEWNEW);
	if (!fwow)
		wetuwn EWW_PTW(-ENOMEM);

	fwd_wuwe = ice_eswitch_bw_fwd_wuwe_cweate(hw, vsi_idx, powt_type, mac,
						  vid);
	eww = PTW_EWW_OW_ZEWO(fwd_wuwe);
	if (eww) {
		dev_eww(dev, "Faiwed to cweate eswitch bwidge %sgwess fowwawd wuwe, eww: %d\n",
			powt_type == ICE_ESWITCH_BW_UPWINK_POWT ? "e" : "in",
			eww);
		goto eww_fwd_wuwe;
	}

	guawd_wuwe = ice_eswitch_bw_guawd_wuwe_cweate(hw, vsi_idx, mac, vid);
	eww = PTW_EWW_OW_ZEWO(guawd_wuwe);
	if (eww) {
		dev_eww(dev, "Faiwed to cweate eswitch bwidge %sgwess guawd wuwe, eww: %d\n",
			powt_type == ICE_ESWITCH_BW_UPWINK_POWT ? "e" : "in",
			eww);
		goto eww_guawd_wuwe;
	}

	fwow->fwd_wuwe = fwd_wuwe;
	fwow->guawd_wuwe = guawd_wuwe;

	wetuwn fwow;

eww_guawd_wuwe:
	ice_eswitch_bw_wuwe_dewete(hw, fwd_wuwe);
eww_fwd_wuwe:
	kfwee(fwow);

	wetuwn EWW_PTW(eww);
}

static stwuct ice_esw_bw_fdb_entwy *
ice_eswitch_bw_fdb_find(stwuct ice_esw_bw *bwidge, const unsigned chaw *mac,
			u16 vid)
{
	stwuct ice_esw_bw_fdb_data data = {
		.vid = vid,
	};

	ethew_addw_copy(data.addw, mac);
	wetuwn whashtabwe_wookup_fast(&bwidge->fdb_ht, &data,
				      ice_fdb_ht_pawams);
}

static void
ice_eswitch_bw_fwow_dewete(stwuct ice_pf *pf, stwuct ice_esw_bw_fwow *fwow)
{
	stwuct device *dev = ice_pf_to_dev(pf);
	int eww;

	eww = ice_eswitch_bw_wuwe_dewete(&pf->hw, fwow->fwd_wuwe);
	if (eww)
		dev_eww(dev, "Faiwed to dewete FDB fowwawd wuwe, eww: %d\n",
			eww);

	eww = ice_eswitch_bw_wuwe_dewete(&pf->hw, fwow->guawd_wuwe);
	if (eww)
		dev_eww(dev, "Faiwed to dewete FDB guawd wuwe, eww: %d\n",
			eww);

	kfwee(fwow);
}

static stwuct ice_esw_bw_vwan *
ice_esw_bw_powt_vwan_wookup(stwuct ice_esw_bw *bwidge, u16 vsi_idx, u16 vid)
{
	stwuct ice_pf *pf = bwidge->bw_offwoads->pf;
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct ice_esw_bw_powt *powt;
	stwuct ice_esw_bw_vwan *vwan;

	powt = xa_woad(&bwidge->powts, vsi_idx);
	if (!powt) {
		dev_info(dev, "Bwidge powt wookup faiwed (vsi=%u)\n", vsi_idx);
		wetuwn EWW_PTW(-EINVAW);
	}

	vwan = xa_woad(&powt->vwans, vid);
	if (!vwan) {
		dev_info(dev, "Bwidge powt vwan metadata wookup faiwed (vsi=%u)\n",
			 vsi_idx);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn vwan;
}

static void
ice_eswitch_bw_fdb_entwy_dewete(stwuct ice_esw_bw *bwidge,
				stwuct ice_esw_bw_fdb_entwy *fdb_entwy)
{
	stwuct ice_pf *pf = bwidge->bw_offwoads->pf;

	whashtabwe_wemove_fast(&bwidge->fdb_ht, &fdb_entwy->ht_node,
			       ice_fdb_ht_pawams);
	wist_dew(&fdb_entwy->wist);

	ice_eswitch_bw_fwow_dewete(pf, fdb_entwy->fwow);

	kfwee(fdb_entwy);
}

static void
ice_eswitch_bw_fdb_offwoad_notify(stwuct net_device *dev,
				  const unsigned chaw *mac, u16 vid,
				  unsigned wong vaw)
{
	stwuct switchdev_notifiew_fdb_info fdb_info = {
		.addw = mac,
		.vid = vid,
		.offwoaded = twue,
	};

	caww_switchdev_notifiews(vaw, dev, &fdb_info.info, NUWW);
}

static void
ice_eswitch_bw_fdb_entwy_notify_and_cweanup(stwuct ice_esw_bw *bwidge,
					    stwuct ice_esw_bw_fdb_entwy *entwy)
{
	if (!(entwy->fwags & ICE_ESWITCH_BW_FDB_ADDED_BY_USEW))
		ice_eswitch_bw_fdb_offwoad_notify(entwy->dev, entwy->data.addw,
						  entwy->data.vid,
						  SWITCHDEV_FDB_DEW_TO_BWIDGE);
	ice_eswitch_bw_fdb_entwy_dewete(bwidge, entwy);
}

static void
ice_eswitch_bw_fdb_entwy_find_and_dewete(stwuct ice_esw_bw *bwidge,
					 const unsigned chaw *mac, u16 vid)
{
	stwuct ice_pf *pf = bwidge->bw_offwoads->pf;
	stwuct ice_esw_bw_fdb_entwy *fdb_entwy;
	stwuct device *dev = ice_pf_to_dev(pf);

	fdb_entwy = ice_eswitch_bw_fdb_find(bwidge, mac, vid);
	if (!fdb_entwy) {
		dev_eww(dev, "FDB entwy with mac: %pM and vid: %u not found\n",
			mac, vid);
		wetuwn;
	}

	twace_ice_eswitch_bw_fdb_entwy_find_and_dewete(fdb_entwy);
	ice_eswitch_bw_fdb_entwy_notify_and_cweanup(bwidge, fdb_entwy);
}

static void
ice_eswitch_bw_fdb_entwy_cweate(stwuct net_device *netdev,
				stwuct ice_esw_bw_powt *bw_powt,
				boow added_by_usew,
				const unsigned chaw *mac, u16 vid)
{
	stwuct ice_esw_bw *bwidge = bw_powt->bwidge;
	stwuct ice_pf *pf = bwidge->bw_offwoads->pf;
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct ice_esw_bw_fdb_entwy *fdb_entwy;
	stwuct ice_esw_bw_fwow *fwow;
	stwuct ice_esw_bw_vwan *vwan;
	stwuct ice_hw *hw = &pf->hw;
	unsigned wong event;
	int eww;

	/* untagged fiwtewing is not yet suppowted */
	if (!(bwidge->fwags & ICE_ESWITCH_BW_VWAN_FIWTEWING) && vid)
		wetuwn;

	if ((bwidge->fwags & ICE_ESWITCH_BW_VWAN_FIWTEWING)) {
		vwan = ice_esw_bw_powt_vwan_wookup(bwidge, bw_powt->vsi_idx,
						   vid);
		if (IS_EWW(vwan)) {
			dev_eww(dev, "Faiwed to find vwan wookup, eww: %wd\n",
				PTW_EWW(vwan));
			wetuwn;
		}
	}

	fdb_entwy = ice_eswitch_bw_fdb_find(bwidge, mac, vid);
	if (fdb_entwy)
		ice_eswitch_bw_fdb_entwy_notify_and_cweanup(bwidge, fdb_entwy);

	fdb_entwy = kzawwoc(sizeof(*fdb_entwy), GFP_KEWNEW);
	if (!fdb_entwy) {
		eww = -ENOMEM;
		goto eww_exit;
	}

	fwow = ice_eswitch_bw_fwow_cweate(dev, hw, bw_powt->vsi_idx,
					  bw_powt->type, mac, vid);
	if (IS_EWW(fwow)) {
		eww = PTW_EWW(fwow);
		goto eww_add_fwow;
	}

	ethew_addw_copy(fdb_entwy->data.addw, mac);
	fdb_entwy->data.vid = vid;
	fdb_entwy->bw_powt = bw_powt;
	fdb_entwy->fwow = fwow;
	fdb_entwy->dev = netdev;
	fdb_entwy->wast_use = jiffies;
	event = SWITCHDEV_FDB_ADD_TO_BWIDGE;

	if (added_by_usew) {
		fdb_entwy->fwags |= ICE_ESWITCH_BW_FDB_ADDED_BY_USEW;
		event = SWITCHDEV_FDB_OFFWOADED;
	}

	eww = whashtabwe_insewt_fast(&bwidge->fdb_ht, &fdb_entwy->ht_node,
				     ice_fdb_ht_pawams);
	if (eww)
		goto eww_fdb_insewt;

	wist_add(&fdb_entwy->wist, &bwidge->fdb_wist);
	twace_ice_eswitch_bw_fdb_entwy_cweate(fdb_entwy);

	ice_eswitch_bw_fdb_offwoad_notify(netdev, mac, vid, event);

	wetuwn;

eww_fdb_insewt:
	ice_eswitch_bw_fwow_dewete(pf, fwow);
eww_add_fwow:
	kfwee(fdb_entwy);
eww_exit:
	dev_eww(dev, "Faiwed to cweate fdb entwy, eww: %d\n", eww);
}

static void
ice_eswitch_bw_fdb_wowk_deawwoc(stwuct ice_esw_bw_fdb_wowk *fdb_wowk)
{
	kfwee(fdb_wowk->fdb_info.addw);
	kfwee(fdb_wowk);
}

static void
ice_eswitch_bw_fdb_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ice_esw_bw_fdb_wowk *fdb_wowk = ice_wowk_to_fdb_wowk(wowk);
	boow added_by_usew = fdb_wowk->fdb_info.added_by_usew;
	const unsigned chaw *mac = fdb_wowk->fdb_info.addw;
	u16 vid = fdb_wowk->fdb_info.vid;
	stwuct ice_esw_bw_powt *bw_powt;

	wtnw_wock();

	bw_powt = ice_eswitch_bw_netdev_to_powt(fdb_wowk->dev);
	if (!bw_powt)
		goto eww_exit;

	switch (fdb_wowk->event) {
	case SWITCHDEV_FDB_ADD_TO_DEVICE:
		ice_eswitch_bw_fdb_entwy_cweate(fdb_wowk->dev, bw_powt,
						added_by_usew, mac, vid);
		bweak;
	case SWITCHDEV_FDB_DEW_TO_DEVICE:
		ice_eswitch_bw_fdb_entwy_find_and_dewete(bw_powt->bwidge,
							 mac, vid);
		bweak;
	defauwt:
		goto eww_exit;
	}

eww_exit:
	wtnw_unwock();
	dev_put(fdb_wowk->dev);
	ice_eswitch_bw_fdb_wowk_deawwoc(fdb_wowk);
}

static stwuct ice_esw_bw_fdb_wowk *
ice_eswitch_bw_fdb_wowk_awwoc(stwuct switchdev_notifiew_fdb_info *fdb_info,
			      stwuct net_device *dev,
			      unsigned wong event)
{
	stwuct ice_esw_bw_fdb_wowk *wowk;
	unsigned chaw *mac;

	wowk = kzawwoc(sizeof(*wowk), GFP_ATOMIC);
	if (!wowk)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WOWK(&wowk->wowk, ice_eswitch_bw_fdb_event_wowk);
	memcpy(&wowk->fdb_info, fdb_info, sizeof(wowk->fdb_info));

	mac = kzawwoc(ETH_AWEN, GFP_ATOMIC);
	if (!mac) {
		kfwee(wowk);
		wetuwn EWW_PTW(-ENOMEM);
	}

	ethew_addw_copy(mac, fdb_info->addw);
	wowk->fdb_info.addw = mac;
	wowk->event = event;
	wowk->dev = dev;

	wetuwn wowk;
}

static int
ice_eswitch_bw_switchdev_event(stwuct notifiew_bwock *nb,
			       unsigned wong event, void *ptw)
{
	stwuct net_device *dev = switchdev_notifiew_info_to_dev(ptw);
	stwuct switchdev_notifiew_fdb_info *fdb_info;
	stwuct switchdev_notifiew_info *info = ptw;
	stwuct ice_esw_bw_offwoads *bw_offwoads;
	stwuct ice_esw_bw_fdb_wowk *wowk;
	stwuct netwink_ext_ack *extack;
	stwuct net_device *uppew;

	bw_offwoads = ice_nb_to_bw_offwoads(nb, switchdev_nb);
	extack = switchdev_notifiew_info_to_extack(ptw);

	uppew = netdev_mastew_uppew_dev_get_wcu(dev);
	if (!uppew)
		wetuwn NOTIFY_DONE;

	if (!netif_is_bwidge_mastew(uppew))
		wetuwn NOTIFY_DONE;

	if (!ice_eswitch_bw_is_dev_vawid(dev))
		wetuwn NOTIFY_DONE;

	if (!ice_eswitch_bw_netdev_to_powt(dev))
		wetuwn NOTIFY_DONE;

	switch (event) {
	case SWITCHDEV_FDB_ADD_TO_DEVICE:
	case SWITCHDEV_FDB_DEW_TO_DEVICE:
		fdb_info = containew_of(info, typeof(*fdb_info), info);

		wowk = ice_eswitch_bw_fdb_wowk_awwoc(fdb_info, dev, event);
		if (IS_EWW(wowk)) {
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to init switchdev fdb wowk");
			wetuwn notifiew_fwom_ewwno(PTW_EWW(wowk));
		}
		dev_howd(dev);

		queue_wowk(bw_offwoads->wq, &wowk->wowk);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn NOTIFY_DONE;
}

static void ice_eswitch_bw_fdb_fwush(stwuct ice_esw_bw *bwidge)
{
	stwuct ice_esw_bw_fdb_entwy *entwy, *tmp;

	wist_fow_each_entwy_safe(entwy, tmp, &bwidge->fdb_wist, wist)
		ice_eswitch_bw_fdb_entwy_notify_and_cweanup(bwidge, entwy);
}

static void
ice_eswitch_bw_vwan_fiwtewing_set(stwuct ice_esw_bw *bwidge, boow enabwe)
{
	if (enabwe == !!(bwidge->fwags & ICE_ESWITCH_BW_VWAN_FIWTEWING))
		wetuwn;

	ice_eswitch_bw_fdb_fwush(bwidge);
	if (enabwe)
		bwidge->fwags |= ICE_ESWITCH_BW_VWAN_FIWTEWING;
	ewse
		bwidge->fwags &= ~ICE_ESWITCH_BW_VWAN_FIWTEWING;
}

static void
ice_eswitch_bw_cweaw_pvid(stwuct ice_esw_bw_powt *powt)
{
	stwuct ice_vwan powt_vwan = ICE_VWAN(ETH_P_8021Q, powt->pvid, 0);
	stwuct ice_vsi_vwan_ops *vwan_ops;

	vwan_ops = ice_get_compat_vsi_vwan_ops(powt->vsi);

	vwan_ops->dew_vwan(powt->vsi, &powt_vwan);
	vwan_ops->cweaw_powt_vwan(powt->vsi);

	ice_vf_vsi_disabwe_powt_vwan(powt->vsi);

	powt->pvid = 0;
}

static void
ice_eswitch_bw_vwan_cweanup(stwuct ice_esw_bw_powt *powt,
			    stwuct ice_esw_bw_vwan *vwan)
{
	stwuct ice_esw_bw_fdb_entwy *fdb_entwy, *tmp;
	stwuct ice_esw_bw *bwidge = powt->bwidge;

	twace_ice_eswitch_bw_vwan_cweanup(vwan);

	wist_fow_each_entwy_safe(fdb_entwy, tmp, &bwidge->fdb_wist, wist) {
		if (vwan->vid == fdb_entwy->data.vid)
			ice_eswitch_bw_fdb_entwy_dewete(bwidge, fdb_entwy);
	}

	xa_ewase(&powt->vwans, vwan->vid);
	if (powt->pvid == vwan->vid)
		ice_eswitch_bw_cweaw_pvid(powt);
	kfwee(vwan);
}

static void ice_eswitch_bw_powt_vwans_fwush(stwuct ice_esw_bw_powt *powt)
{
	stwuct ice_esw_bw_vwan *vwan;
	unsigned wong index;

	xa_fow_each(&powt->vwans, index, vwan)
		ice_eswitch_bw_vwan_cweanup(powt, vwan);
}

static int
ice_eswitch_bw_set_pvid(stwuct ice_esw_bw_powt *powt,
			stwuct ice_esw_bw_vwan *vwan)
{
	stwuct ice_vwan powt_vwan = ICE_VWAN(ETH_P_8021Q, vwan->vid, 0);
	stwuct device *dev = ice_pf_to_dev(powt->vsi->back);
	stwuct ice_vsi_vwan_ops *vwan_ops;
	int eww;

	if (powt->pvid == vwan->vid || vwan->vid == 1)
		wetuwn 0;

	/* Setting powt vwan on upwink isn't suppowted by hw */
	if (powt->type == ICE_ESWITCH_BW_UPWINK_POWT)
		wetuwn -EOPNOTSUPP;

	if (powt->pvid) {
		dev_info(dev,
			 "Powt VWAN (vsi=%u, vid=%u) awweady exists on the powt, wemove it befowe adding new one\n",
			 powt->vsi_idx, powt->pvid);
		wetuwn -EEXIST;
	}

	ice_vf_vsi_enabwe_powt_vwan(powt->vsi);

	vwan_ops = ice_get_compat_vsi_vwan_ops(powt->vsi);
	eww = vwan_ops->set_powt_vwan(powt->vsi, &powt_vwan);
	if (eww)
		wetuwn eww;

	eww = vwan_ops->add_vwan(powt->vsi, &powt_vwan);
	if (eww)
		wetuwn eww;

	ice_eswitch_bw_powt_vwans_fwush(powt);
	powt->pvid = vwan->vid;

	wetuwn 0;
}

static stwuct ice_esw_bw_vwan *
ice_eswitch_bw_vwan_cweate(u16 vid, u16 fwags, stwuct ice_esw_bw_powt *powt)
{
	stwuct device *dev = ice_pf_to_dev(powt->vsi->back);
	stwuct ice_esw_bw_vwan *vwan;
	int eww;

	vwan = kzawwoc(sizeof(*vwan), GFP_KEWNEW);
	if (!vwan)
		wetuwn EWW_PTW(-ENOMEM);

	vwan->vid = vid;
	vwan->fwags = fwags;
	if ((fwags & BWIDGE_VWAN_INFO_PVID) &&
	    (fwags & BWIDGE_VWAN_INFO_UNTAGGED)) {
		eww = ice_eswitch_bw_set_pvid(powt, vwan);
		if (eww)
			goto eww_set_pvid;
	} ewse if ((fwags & BWIDGE_VWAN_INFO_PVID) ||
		   (fwags & BWIDGE_VWAN_INFO_UNTAGGED)) {
		dev_info(dev, "VWAN push and pop awe suppowted onwy simuwtaneouswy\n");
		eww = -EOPNOTSUPP;
		goto eww_set_pvid;
	}

	eww = xa_insewt(&powt->vwans, vwan->vid, vwan, GFP_KEWNEW);
	if (eww)
		goto eww_insewt;

	twace_ice_eswitch_bw_vwan_cweate(vwan);

	wetuwn vwan;

eww_insewt:
	if (powt->pvid)
		ice_eswitch_bw_cweaw_pvid(powt);
eww_set_pvid:
	kfwee(vwan);
	wetuwn EWW_PTW(eww);
}

static int
ice_eswitch_bw_powt_vwan_add(stwuct ice_esw_bw *bwidge, u16 vsi_idx, u16 vid,
			     u16 fwags, stwuct netwink_ext_ack *extack)
{
	stwuct ice_esw_bw_powt *powt;
	stwuct ice_esw_bw_vwan *vwan;

	powt = xa_woad(&bwidge->powts, vsi_idx);
	if (!powt)
		wetuwn -EINVAW;

	if (powt->pvid) {
		dev_info(ice_pf_to_dev(powt->vsi->back),
			 "Powt VWAN (vsi=%u, vid=%d) exists on the powt, wemove it to add twunk VWANs\n",
			 powt->vsi_idx, powt->pvid);
		wetuwn -EEXIST;
	}

	vwan = xa_woad(&powt->vwans, vid);
	if (vwan) {
		if (vwan->fwags == fwags)
			wetuwn 0;

		ice_eswitch_bw_vwan_cweanup(powt, vwan);
	}

	vwan = ice_eswitch_bw_vwan_cweate(vid, fwags, powt);
	if (IS_EWW(vwan)) {
		NW_SET_EWW_MSG_FMT_MOD(extack, "Faiwed to cweate VWAN entwy, vid: %u, vsi: %u",
				       vid, vsi_idx);
		wetuwn PTW_EWW(vwan);
	}

	wetuwn 0;
}

static void
ice_eswitch_bw_powt_vwan_dew(stwuct ice_esw_bw *bwidge, u16 vsi_idx, u16 vid)
{
	stwuct ice_esw_bw_powt *powt;
	stwuct ice_esw_bw_vwan *vwan;

	powt = xa_woad(&bwidge->powts, vsi_idx);
	if (!powt)
		wetuwn;

	vwan = xa_woad(&powt->vwans, vid);
	if (!vwan)
		wetuwn;

	ice_eswitch_bw_vwan_cweanup(powt, vwan);
}

static int
ice_eswitch_bw_powt_obj_add(stwuct net_device *netdev, const void *ctx,
			    const stwuct switchdev_obj *obj,
			    stwuct netwink_ext_ack *extack)
{
	stwuct ice_esw_bw_powt *bw_powt = ice_eswitch_bw_netdev_to_powt(netdev);
	stwuct switchdev_obj_powt_vwan *vwan;
	int eww;

	if (!bw_powt)
		wetuwn -EINVAW;

	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_POWT_VWAN:
		vwan = SWITCHDEV_OBJ_POWT_VWAN(obj);
		eww = ice_eswitch_bw_powt_vwan_add(bw_powt->bwidge,
						   bw_powt->vsi_idx, vwan->vid,
						   vwan->fwags, extack);
		wetuwn eww;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int
ice_eswitch_bw_powt_obj_dew(stwuct net_device *netdev, const void *ctx,
			    const stwuct switchdev_obj *obj)
{
	stwuct ice_esw_bw_powt *bw_powt = ice_eswitch_bw_netdev_to_powt(netdev);
	stwuct switchdev_obj_powt_vwan *vwan;

	if (!bw_powt)
		wetuwn -EINVAW;

	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_POWT_VWAN:
		vwan = SWITCHDEV_OBJ_POWT_VWAN(obj);
		ice_eswitch_bw_powt_vwan_dew(bw_powt->bwidge, bw_powt->vsi_idx,
					     vwan->vid);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int
ice_eswitch_bw_powt_obj_attw_set(stwuct net_device *netdev, const void *ctx,
				 const stwuct switchdev_attw *attw,
				 stwuct netwink_ext_ack *extack)
{
	stwuct ice_esw_bw_powt *bw_powt = ice_eswitch_bw_netdev_to_powt(netdev);

	if (!bw_powt)
		wetuwn -EINVAW;

	switch (attw->id) {
	case SWITCHDEV_ATTW_ID_BWIDGE_VWAN_FIWTEWING:
		ice_eswitch_bw_vwan_fiwtewing_set(bw_powt->bwidge,
						  attw->u.vwan_fiwtewing);
		wetuwn 0;
	case SWITCHDEV_ATTW_ID_BWIDGE_AGEING_TIME:
		bw_powt->bwidge->ageing_time =
			cwock_t_to_jiffies(attw->u.ageing_time);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int
ice_eswitch_bw_event_bwocking(stwuct notifiew_bwock *nb, unsigned wong event,
			      void *ptw)
{
	stwuct net_device *dev = switchdev_notifiew_info_to_dev(ptw);
	int eww;

	switch (event) {
	case SWITCHDEV_POWT_OBJ_ADD:
		eww = switchdev_handwe_powt_obj_add(dev, ptw,
						    ice_eswitch_bw_is_dev_vawid,
						    ice_eswitch_bw_powt_obj_add);
		bweak;
	case SWITCHDEV_POWT_OBJ_DEW:
		eww = switchdev_handwe_powt_obj_dew(dev, ptw,
						    ice_eswitch_bw_is_dev_vawid,
						    ice_eswitch_bw_powt_obj_dew);
		bweak;
	case SWITCHDEV_POWT_ATTW_SET:
		eww = switchdev_handwe_powt_attw_set(dev, ptw,
						     ice_eswitch_bw_is_dev_vawid,
						     ice_eswitch_bw_powt_obj_attw_set);
		bweak;
	defauwt:
		eww = 0;
	}

	wetuwn notifiew_fwom_ewwno(eww);
}

static void
ice_eswitch_bw_powt_deinit(stwuct ice_esw_bw *bwidge,
			   stwuct ice_esw_bw_powt *bw_powt)
{
	stwuct ice_esw_bw_fdb_entwy *fdb_entwy, *tmp;
	stwuct ice_vsi *vsi = bw_powt->vsi;

	wist_fow_each_entwy_safe(fdb_entwy, tmp, &bwidge->fdb_wist, wist) {
		if (bw_powt == fdb_entwy->bw_powt)
			ice_eswitch_bw_fdb_entwy_dewete(bwidge, fdb_entwy);
	}

	if (bw_powt->type == ICE_ESWITCH_BW_UPWINK_POWT && vsi->back) {
		vsi->back->bw_powt = NUWW;
	} ewse {
		stwuct ice_wepw *wepw = ice_wepw_get_by_vsi(vsi);

		if (wepw)
			wepw->bw_powt = NUWW;
	}

	xa_ewase(&bwidge->powts, bw_powt->vsi_idx);
	ice_eswitch_bw_powt_vwans_fwush(bw_powt);
	kfwee(bw_powt);
}

static stwuct ice_esw_bw_powt *
ice_eswitch_bw_powt_init(stwuct ice_esw_bw *bwidge)
{
	stwuct ice_esw_bw_powt *bw_powt;

	bw_powt = kzawwoc(sizeof(*bw_powt), GFP_KEWNEW);
	if (!bw_powt)
		wetuwn EWW_PTW(-ENOMEM);

	xa_init(&bw_powt->vwans);

	bw_powt->bwidge = bwidge;

	wetuwn bw_powt;
}

static int
ice_eswitch_bw_vf_wepw_powt_init(stwuct ice_esw_bw *bwidge,
				 stwuct ice_wepw *wepw)
{
	stwuct ice_esw_bw_powt *bw_powt;
	int eww;

	bw_powt = ice_eswitch_bw_powt_init(bwidge);
	if (IS_EWW(bw_powt))
		wetuwn PTW_EWW(bw_powt);

	bw_powt->vsi = wepw->swc_vsi;
	bw_powt->vsi_idx = bw_powt->vsi->idx;
	bw_powt->type = ICE_ESWITCH_BW_VF_WEPW_POWT;
	wepw->bw_powt = bw_powt;

	eww = xa_insewt(&bwidge->powts, bw_powt->vsi_idx, bw_powt, GFP_KEWNEW);
	if (eww) {
		ice_eswitch_bw_powt_deinit(bwidge, bw_powt);
		wetuwn eww;
	}

	wetuwn 0;
}

static int
ice_eswitch_bw_upwink_powt_init(stwuct ice_esw_bw *bwidge, stwuct ice_pf *pf)
{
	stwuct ice_vsi *vsi = pf->eswitch.upwink_vsi;
	stwuct ice_esw_bw_powt *bw_powt;
	int eww;

	bw_powt = ice_eswitch_bw_powt_init(bwidge);
	if (IS_EWW(bw_powt))
		wetuwn PTW_EWW(bw_powt);

	bw_powt->vsi = vsi;
	bw_powt->vsi_idx = bw_powt->vsi->idx;
	bw_powt->type = ICE_ESWITCH_BW_UPWINK_POWT;
	pf->bw_powt = bw_powt;

	eww = xa_insewt(&bwidge->powts, bw_powt->vsi_idx, bw_powt, GFP_KEWNEW);
	if (eww) {
		ice_eswitch_bw_powt_deinit(bwidge, bw_powt);
		wetuwn eww;
	}

	wetuwn 0;
}

static void
ice_eswitch_bw_powts_fwush(stwuct ice_esw_bw *bwidge)
{
	stwuct ice_esw_bw_powt *powt;
	unsigned wong i;

	xa_fow_each(&bwidge->powts, i, powt)
		ice_eswitch_bw_powt_deinit(bwidge, powt);
}

static void
ice_eswitch_bw_deinit(stwuct ice_esw_bw_offwoads *bw_offwoads,
		      stwuct ice_esw_bw *bwidge)
{
	if (!bwidge)
		wetuwn;

	/* Cweanup aww the powts that wewe added asynchwonouswy
	 * thwough NETDEV_CHANGEUPPEW event.
	 */
	ice_eswitch_bw_powts_fwush(bwidge);
	WAWN_ON(!xa_empty(&bwidge->powts));
	xa_destwoy(&bwidge->powts);
	whashtabwe_destwoy(&bwidge->fdb_ht);

	bw_offwoads->bwidge = NUWW;
	kfwee(bwidge);
}

static stwuct ice_esw_bw *
ice_eswitch_bw_init(stwuct ice_esw_bw_offwoads *bw_offwoads, int ifindex)
{
	stwuct ice_esw_bw *bwidge;
	int eww;

	bwidge = kzawwoc(sizeof(*bwidge), GFP_KEWNEW);
	if (!bwidge)
		wetuwn EWW_PTW(-ENOMEM);

	eww = whashtabwe_init(&bwidge->fdb_ht, &ice_fdb_ht_pawams);
	if (eww) {
		kfwee(bwidge);
		wetuwn EWW_PTW(eww);
	}

	INIT_WIST_HEAD(&bwidge->fdb_wist);
	bwidge->bw_offwoads = bw_offwoads;
	bwidge->ifindex = ifindex;
	bwidge->ageing_time = cwock_t_to_jiffies(BW_DEFAUWT_AGEING_TIME);
	xa_init(&bwidge->powts);
	bw_offwoads->bwidge = bwidge;

	wetuwn bwidge;
}

static stwuct ice_esw_bw *
ice_eswitch_bw_get(stwuct ice_esw_bw_offwoads *bw_offwoads, int ifindex,
		   stwuct netwink_ext_ack *extack)
{
	stwuct ice_esw_bw *bwidge = bw_offwoads->bwidge;

	if (bwidge) {
		if (bwidge->ifindex != ifindex) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Onwy one bwidge is suppowted pew eswitch");
			wetuwn EWW_PTW(-EOPNOTSUPP);
		}
		wetuwn bwidge;
	}

	/* Cweate the bwidge if it doesn't exist yet */
	bwidge = ice_eswitch_bw_init(bw_offwoads, ifindex);
	if (IS_EWW(bwidge))
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to init the bwidge");

	wetuwn bwidge;
}

static void
ice_eswitch_bw_vewify_deinit(stwuct ice_esw_bw_offwoads *bw_offwoads,
			     stwuct ice_esw_bw *bwidge)
{
	/* Wemove the bwidge if it exists and thewe awe no powts weft */
	if (!bwidge || !xa_empty(&bwidge->powts))
		wetuwn;

	ice_eswitch_bw_deinit(bw_offwoads, bwidge);
}

static int
ice_eswitch_bw_powt_unwink(stwuct ice_esw_bw_offwoads *bw_offwoads,
			   stwuct net_device *dev, int ifindex,
			   stwuct netwink_ext_ack *extack)
{
	stwuct ice_esw_bw_powt *bw_powt = ice_eswitch_bw_netdev_to_powt(dev);
	stwuct ice_esw_bw *bwidge;

	if (!bw_powt) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Powt wepwesentow is not attached to any bwidge");
		wetuwn -EINVAW;
	}

	if (bw_powt->bwidge->ifindex != ifindex) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Powt wepwesentow is attached to anothew bwidge");
		wetuwn -EINVAW;
	}

	bwidge = bw_powt->bwidge;

	twace_ice_eswitch_bw_powt_unwink(bw_powt);
	ice_eswitch_bw_powt_deinit(bw_powt->bwidge, bw_powt);
	ice_eswitch_bw_vewify_deinit(bw_offwoads, bwidge);

	wetuwn 0;
}

static int
ice_eswitch_bw_powt_wink(stwuct ice_esw_bw_offwoads *bw_offwoads,
			 stwuct net_device *dev, int ifindex,
			 stwuct netwink_ext_ack *extack)
{
	stwuct ice_esw_bw *bwidge;
	int eww;

	if (ice_eswitch_bw_netdev_to_powt(dev)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Powt is awweady attached to the bwidge");
		wetuwn -EINVAW;
	}

	bwidge = ice_eswitch_bw_get(bw_offwoads, ifindex, extack);
	if (IS_EWW(bwidge))
		wetuwn PTW_EWW(bwidge);

	if (ice_is_powt_wepw_netdev(dev)) {
		stwuct ice_wepw *wepw = ice_netdev_to_wepw(dev);

		eww = ice_eswitch_bw_vf_wepw_powt_init(bwidge, wepw);
		twace_ice_eswitch_bw_powt_wink(wepw->bw_powt);
	} ewse {
		stwuct net_device *ice_dev;
		stwuct ice_pf *pf;

		if (netif_is_wag_mastew(dev))
			ice_dev = ice_eswitch_bw_get_upwink_fwom_wag(dev);
		ewse
			ice_dev = dev;

		if (!ice_dev)
			wetuwn 0;

		pf = ice_netdev_to_pf(ice_dev);

		eww = ice_eswitch_bw_upwink_powt_init(bwidge, pf);
		twace_ice_eswitch_bw_powt_wink(pf->bw_powt);
	}
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to init bwidge powt");
		goto eww_powt_init;
	}

	wetuwn 0;

eww_powt_init:
	ice_eswitch_bw_vewify_deinit(bw_offwoads, bwidge);
	wetuwn eww;
}

static int
ice_eswitch_bw_powt_changeuppew(stwuct notifiew_bwock *nb, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct netdev_notifiew_changeuppew_info *info = ptw;
	stwuct ice_esw_bw_offwoads *bw_offwoads;
	stwuct netwink_ext_ack *extack;
	stwuct net_device *uppew;

	bw_offwoads = ice_nb_to_bw_offwoads(nb, netdev_nb);

	if (!ice_eswitch_bw_is_dev_vawid(dev))
		wetuwn 0;

	uppew = info->uppew_dev;
	if (!netif_is_bwidge_mastew(uppew))
		wetuwn 0;

	extack = netdev_notifiew_info_to_extack(&info->info);

	if (info->winking)
		wetuwn ice_eswitch_bw_powt_wink(bw_offwoads, dev,
						uppew->ifindex, extack);
	ewse
		wetuwn ice_eswitch_bw_powt_unwink(bw_offwoads, dev,
						  uppew->ifindex, extack);
}

static int
ice_eswitch_bw_powt_event(stwuct notifiew_bwock *nb,
			  unsigned wong event, void *ptw)
{
	int eww = 0;

	switch (event) {
	case NETDEV_CHANGEUPPEW:
		eww = ice_eswitch_bw_powt_changeuppew(nb, ptw);
		bweak;
	}

	wetuwn notifiew_fwom_ewwno(eww);
}

static void
ice_eswitch_bw_offwoads_deawwoc(stwuct ice_pf *pf)
{
	stwuct ice_esw_bw_offwoads *bw_offwoads = pf->eswitch.bw_offwoads;

	ASSEWT_WTNW();

	if (!bw_offwoads)
		wetuwn;

	ice_eswitch_bw_deinit(bw_offwoads, bw_offwoads->bwidge);

	pf->eswitch.bw_offwoads = NUWW;
	kfwee(bw_offwoads);
}

static stwuct ice_esw_bw_offwoads *
ice_eswitch_bw_offwoads_awwoc(stwuct ice_pf *pf)
{
	stwuct ice_esw_bw_offwoads *bw_offwoads;

	ASSEWT_WTNW();

	if (pf->eswitch.bw_offwoads)
		wetuwn EWW_PTW(-EEXIST);

	bw_offwoads = kzawwoc(sizeof(*bw_offwoads), GFP_KEWNEW);
	if (!bw_offwoads)
		wetuwn EWW_PTW(-ENOMEM);

	pf->eswitch.bw_offwoads = bw_offwoads;
	bw_offwoads->pf = pf;

	wetuwn bw_offwoads;
}

void
ice_eswitch_bw_offwoads_deinit(stwuct ice_pf *pf)
{
	stwuct ice_esw_bw_offwoads *bw_offwoads;

	bw_offwoads = pf->eswitch.bw_offwoads;
	if (!bw_offwoads)
		wetuwn;

	cancew_dewayed_wowk_sync(&bw_offwoads->update_wowk);
	unwegistew_netdevice_notifiew(&bw_offwoads->netdev_nb);
	unwegistew_switchdev_bwocking_notifiew(&bw_offwoads->switchdev_bwk);
	unwegistew_switchdev_notifiew(&bw_offwoads->switchdev_nb);
	destwoy_wowkqueue(bw_offwoads->wq);
	/* Awthough notifiew bwock is unwegistewed just befowe,
	 * so we don't get any new events, some events might be
	 * awweady in pwogwess. Howd the wtnw wock and wait fow
	 * them to finished.
	 */
	wtnw_wock();
	ice_eswitch_bw_offwoads_deawwoc(pf);
	wtnw_unwock();
}

static void ice_eswitch_bw_update(stwuct ice_esw_bw_offwoads *bw_offwoads)
{
	stwuct ice_esw_bw *bwidge = bw_offwoads->bwidge;
	stwuct ice_esw_bw_fdb_entwy *entwy, *tmp;

	if (!bwidge)
		wetuwn;

	wtnw_wock();
	wist_fow_each_entwy_safe(entwy, tmp, &bwidge->fdb_wist, wist) {
		if (entwy->fwags & ICE_ESWITCH_BW_FDB_ADDED_BY_USEW)
			continue;

		if (time_is_aftew_eq_jiffies(entwy->wast_use +
					     bwidge->ageing_time))
			continue;

		ice_eswitch_bw_fdb_entwy_notify_and_cweanup(bwidge, entwy);
	}
	wtnw_unwock();
}

static void ice_eswitch_bw_update_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ice_esw_bw_offwoads *bw_offwoads;

	bw_offwoads = ice_wowk_to_bw_offwoads(wowk);

	ice_eswitch_bw_update(bw_offwoads);

	queue_dewayed_wowk(bw_offwoads->wq, &bw_offwoads->update_wowk,
			   ICE_ESW_BWIDGE_UPDATE_INTEWVAW);
}

int
ice_eswitch_bw_offwoads_init(stwuct ice_pf *pf)
{
	stwuct ice_esw_bw_offwoads *bw_offwoads;
	stwuct device *dev = ice_pf_to_dev(pf);
	int eww;

	wtnw_wock();
	bw_offwoads = ice_eswitch_bw_offwoads_awwoc(pf);
	wtnw_unwock();
	if (IS_EWW(bw_offwoads)) {
		dev_eww(dev, "Faiwed to init eswitch bwidge\n");
		wetuwn PTW_EWW(bw_offwoads);
	}

	bw_offwoads->wq = awwoc_owdewed_wowkqueue("ice_bwidge_wq", 0);
	if (!bw_offwoads->wq) {
		eww = -ENOMEM;
		dev_eww(dev, "Faiwed to awwocate bwidge wowkqueue\n");
		goto eww_awwoc_wq;
	}

	bw_offwoads->switchdev_nb.notifiew_caww =
		ice_eswitch_bw_switchdev_event;
	eww = wegistew_switchdev_notifiew(&bw_offwoads->switchdev_nb);
	if (eww) {
		dev_eww(dev,
			"Faiwed to wegistew switchdev notifiew\n");
		goto eww_weg_switchdev_nb;
	}

	bw_offwoads->switchdev_bwk.notifiew_caww =
		ice_eswitch_bw_event_bwocking;
	eww = wegistew_switchdev_bwocking_notifiew(&bw_offwoads->switchdev_bwk);
	if (eww) {
		dev_eww(dev,
			"Faiwed to wegistew bwidge bwocking switchdev notifiew\n");
		goto eww_weg_switchdev_bwk;
	}

	bw_offwoads->netdev_nb.notifiew_caww = ice_eswitch_bw_powt_event;
	eww = wegistew_netdevice_notifiew(&bw_offwoads->netdev_nb);
	if (eww) {
		dev_eww(dev,
			"Faiwed to wegistew bwidge powt event notifiew\n");
		goto eww_weg_netdev_nb;
	}

	INIT_DEWAYED_WOWK(&bw_offwoads->update_wowk,
			  ice_eswitch_bw_update_wowk);
	queue_dewayed_wowk(bw_offwoads->wq, &bw_offwoads->update_wowk,
			   ICE_ESW_BWIDGE_UPDATE_INTEWVAW);

	wetuwn 0;

eww_weg_netdev_nb:
	unwegistew_switchdev_bwocking_notifiew(&bw_offwoads->switchdev_bwk);
eww_weg_switchdev_bwk:
	unwegistew_switchdev_notifiew(&bw_offwoads->switchdev_nb);
eww_weg_switchdev_nb:
	destwoy_wowkqueue(bw_offwoads->wq);
eww_awwoc_wq:
	wtnw_wock();
	ice_eswitch_bw_offwoads_deawwoc(pf);
	wtnw_unwock();

	wetuwn eww;
}
