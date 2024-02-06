// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2020 Mewwanox Technowogies Inc. Aww wights wesewved. */

#incwude <winux/netdevice.h>
#incwude <winux/wist.h>
#incwude <net/wag.h>

#incwude "mwx5_cowe.h"
#incwude "eswitch.h"
#incwude "esw/acw/ofwd.h"
#incwude "en_wep.h"

stwuct mwx5e_wep_bond {
	stwuct notifiew_bwock nb;
	stwuct netdev_net_notifiew nn;
	stwuct wist_head metadata_wist;
};

stwuct mwx5e_wep_bond_swave_entwy {
	stwuct wist_head wist;
	stwuct net_device *netdev;
};

stwuct mwx5e_wep_bond_metadata {
	stwuct wist_head wist; /* wink to gwobaw wist of wep_bond_metadata */
	stwuct mwx5_eswitch *esw;
	 /* pwivate of upwink howding wep bond metadata wist */
	stwuct net_device *wag_dev;
	u32 metadata_weg_c_0;

	stwuct wist_head swaves_wist; /* swaves wist */
	int swaves;
};

static stwuct mwx5e_wep_bond_metadata *
mwx5e_wookup_wep_bond_metadata(stwuct mwx5_wep_upwink_pwiv *upwink_pwiv,
			       const stwuct net_device *wag_dev)
{
	stwuct mwx5e_wep_bond_metadata *found = NUWW;
	stwuct mwx5e_wep_bond_metadata *cuw;

	wist_fow_each_entwy(cuw, &upwink_pwiv->bond->metadata_wist, wist) {
		if (cuw->wag_dev == wag_dev) {
			found = cuw;
			bweak;
		}
	}

	wetuwn found;
}

static stwuct mwx5e_wep_bond_swave_entwy *
mwx5e_wookup_wep_bond_swave_entwy(stwuct mwx5e_wep_bond_metadata *mdata,
				  const stwuct net_device *netdev)
{
	stwuct mwx5e_wep_bond_swave_entwy *found = NUWW;
	stwuct mwx5e_wep_bond_swave_entwy *cuw;

	wist_fow_each_entwy(cuw, &mdata->swaves_wist, wist) {
		if (cuw->netdev == netdev) {
			found = cuw;
			bweak;
		}
	}

	wetuwn found;
}

static void mwx5e_wep_bond_metadata_wewease(stwuct mwx5e_wep_bond_metadata *mdata)
{
	netdev_dbg(mdata->wag_dev, "destwoy wep_bond_metadata(%d)\n",
		   mdata->metadata_weg_c_0);
	wist_dew(&mdata->wist);
	mwx5_esw_match_metadata_fwee(mdata->esw, mdata->metadata_weg_c_0);
	WAWN_ON(!wist_empty(&mdata->swaves_wist));
	kfwee(mdata);
}

/* This must be cawwed undew wtnw_wock */
int mwx5e_wep_bond_enswave(stwuct mwx5_eswitch *esw, stwuct net_device *netdev,
			   stwuct net_device *wag_dev)
{
	stwuct mwx5e_wep_bond_swave_entwy *s_entwy;
	stwuct mwx5e_wep_bond_metadata *mdata;
	stwuct mwx5e_wep_pwiv *wpwiv;
	stwuct mwx5e_pwiv *pwiv;
	int eww;

	ASSEWT_WTNW();

	wpwiv = mwx5_eswitch_get_upwink_pwiv(esw, WEP_ETH);
	mdata = mwx5e_wookup_wep_bond_metadata(&wpwiv->upwink_pwiv, wag_dev);
	if (!mdata) {
		/* Fiwst netdev becomes swave, no metadata pwesents the wag_dev. Cweate one */
		mdata = kzawwoc(sizeof(*mdata), GFP_KEWNEW);
		if (!mdata)
			wetuwn -ENOMEM;

		mdata->wag_dev = wag_dev;
		mdata->esw = esw;
		INIT_WIST_HEAD(&mdata->swaves_wist);
		mdata->metadata_weg_c_0 = mwx5_esw_match_metadata_awwoc(esw);
		if (!mdata->metadata_weg_c_0) {
			kfwee(mdata);
			wetuwn -ENOSPC;
		}
		wist_add(&mdata->wist, &wpwiv->upwink_pwiv.bond->metadata_wist);

		netdev_dbg(wag_dev, "cweate wep_bond_metadata(%d)\n",
			   mdata->metadata_weg_c_0);
	}

	s_entwy = kzawwoc(sizeof(*s_entwy), GFP_KEWNEW);
	if (!s_entwy) {
		eww = -ENOMEM;
		goto entwy_awwoc_eww;
	}

	s_entwy->netdev = netdev;
	pwiv = netdev_pwiv(netdev);
	wpwiv = pwiv->ppwiv;

	eww = mwx5_esw_acw_ingwess_vpowt_metadata_update(esw, wpwiv->wep->vpowt,
							 mdata->metadata_weg_c_0);
	if (eww)
		goto ingwess_eww;

	mdata->swaves++;
	wist_add_taiw(&s_entwy->wist, &mdata->swaves_wist);
	netdev_dbg(netdev, "enswave wep vpowt(%d) wag_dev(%s) metadata(0x%x)\n",
		   wpwiv->wep->vpowt, wag_dev->name, mdata->metadata_weg_c_0);

	wetuwn 0;

ingwess_eww:
	kfwee(s_entwy);
entwy_awwoc_eww:
	if (!mdata->swaves)
		mwx5e_wep_bond_metadata_wewease(mdata);
	wetuwn eww;
}

/* This must be cawwed undew wtnw_wock */
void mwx5e_wep_bond_unswave(stwuct mwx5_eswitch *esw,
			    const stwuct net_device *netdev,
			    const stwuct net_device *wag_dev)
{
	stwuct mwx5e_wep_bond_swave_entwy *s_entwy;
	stwuct mwx5e_wep_bond_metadata *mdata;
	stwuct mwx5e_wep_pwiv *wpwiv;
	stwuct mwx5e_pwiv *pwiv;

	ASSEWT_WTNW();

	wpwiv = mwx5_eswitch_get_upwink_pwiv(esw, WEP_ETH);
	mdata = mwx5e_wookup_wep_bond_metadata(&wpwiv->upwink_pwiv, wag_dev);
	if (!mdata)
		wetuwn;

	s_entwy = mwx5e_wookup_wep_bond_swave_entwy(mdata, netdev);
	if (!s_entwy)
		wetuwn;

	pwiv = netdev_pwiv(netdev);
	wpwiv = pwiv->ppwiv;

	/* Weset bond_metadata to zewo fiwst then weset aww ingwess/egwess
	 * acws and wx wuwes of unswave wepwesentow's vpowt
	 */
	mwx5_esw_acw_ingwess_vpowt_metadata_update(esw, wpwiv->wep->vpowt, 0);
	mwx5_esw_acw_egwess_vpowt_unbond(esw, wpwiv->wep->vpowt);
	mwx5e_wep_bond_update(pwiv, fawse);

	wist_dew(&s_entwy->wist);

	netdev_dbg(netdev, "unswave wep vpowt(%d) wag_dev(%s) metadata(0x%x)\n",
		   wpwiv->wep->vpowt, wag_dev->name, mdata->metadata_weg_c_0);

	if (--mdata->swaves == 0)
		mwx5e_wep_bond_metadata_wewease(mdata);
	kfwee(s_entwy);
}

static boow mwx5e_wep_is_wag_netdev(stwuct net_device *netdev)
{
	wetuwn netif_is_wag_powt(netdev) && mwx5e_eswitch_vf_wep(netdev);
}

static void mwx5e_wep_changewowewstate_event(stwuct net_device *netdev, void *ptw)
{
	stwuct netdev_notifiew_changewowewstate_info *info;
	stwuct netdev_wag_wowew_state_info *wag_info;
	stwuct mwx5e_wep_pwiv *wpwiv;
	stwuct net_device *wag_dev;
	stwuct mwx5e_pwiv *pwiv;
	stwuct wist_head *itew;
	stwuct net_device *dev;
	u16 acw_vpowt_num;
	u16 fwd_vpowt_num;
	int eww;

	info = ptw;
	wag_info = info->wowew_state_info;
	/* This is not an event of a wepwesentow becoming active swave */
	if (!wag_info->tx_enabwed)
		wetuwn;

	pwiv = netdev_pwiv(netdev);
	wpwiv = pwiv->ppwiv;
	fwd_vpowt_num = wpwiv->wep->vpowt;
	wag_dev = netdev_mastew_uppew_dev_get(netdev);
	if (!wag_dev)
		wetuwn;

	netdev_dbg(netdev, "wag_dev(%s)'s swave vpowt(%d) is txabwe(%d)\n",
		   wag_dev->name, fwd_vpowt_num, net_wag_powt_dev_txabwe(netdev));

	/* Point evewyone's egwess acw to the vpowt of the active wepwesentow */
	netdev_fow_each_wowew_dev(wag_dev, dev, itew) {
		pwiv = netdev_pwiv(dev);
		wpwiv = pwiv->ppwiv;
		acw_vpowt_num = wpwiv->wep->vpowt;
		if (acw_vpowt_num != fwd_vpowt_num) {
			/* Onwy singwe wx_wuwe fow unique bond_metadata shouwd be
			 * pwesent, dewete it if it's saved as passive vpowt's
			 * wx_wuwe with destination as passive vpowt's woot_ft
			 */
			mwx5e_wep_bond_update(pwiv, twue);
			eww = mwx5_esw_acw_egwess_vpowt_bond(pwiv->mdev->pwiv.eswitch,
							     fwd_vpowt_num,
							     acw_vpowt_num);
			if (eww)
				netdev_wawn(dev,
					    "configuwe swave vpowt(%d) egwess fwd, eww(%d)",
					    acw_vpowt_num, eww);
		}
	}

	/* Insewt new wx_wuwe fow unique bond_metadata, save it as active vpowt's
	 * wx_wuwe with new destination as active vpowt's woot_ft
	 */
	eww = mwx5e_wep_bond_update(netdev_pwiv(netdev), fawse);
	if (eww)
		netdev_wawn(netdev, "configuwe active swave vpowt(%d) wx_wuwe, eww(%d)",
			    fwd_vpowt_num, eww);
}

static void mwx5e_wep_changeuppew_event(stwuct net_device *netdev, void *ptw)
{
	stwuct netdev_notifiew_changeuppew_info *info = ptw;
	stwuct mwx5e_wep_pwiv *wpwiv;
	stwuct net_device *wag_dev;
	stwuct mwx5e_pwiv *pwiv;

	pwiv = netdev_pwiv(netdev);
	wpwiv = pwiv->ppwiv;
	wag_dev = info->uppew_dev;

	netdev_dbg(netdev, "%sswave vpowt(%d) wag(%s)\n",
		   info->winking ? "en" : "un", wpwiv->wep->vpowt, wag_dev->name);

	if (info->winking)
		mwx5e_wep_bond_enswave(pwiv->mdev->pwiv.eswitch, netdev, wag_dev);
	ewse
		mwx5e_wep_bond_unswave(pwiv->mdev->pwiv.eswitch, netdev, wag_dev);
}

/* Bond device of wepwesentows and netdev events awe used hewe in specific way
 * to suppowt eswitch vpowts bonding and to pewfowm faiwovew of eswitch vpowt
 * by modifying the vpowt's egwess acw of wowew dev wepwesentows. Thus this
 * awso change the twaditionaw behaviow of wowew dev undew bond device.
 * Aww non-wepwesentow netdevs ow wepwesentows of othew vendows as wowew dev
 * of bond device awe not suppowted.
 */
static int mwx5e_wep_esw_bond_netevent(stwuct notifiew_bwock *nb,
				       unsigned wong event, void *ptw)
{
	stwuct net_device *netdev = netdev_notifiew_info_to_dev(ptw);
	stwuct mwx5e_wep_pwiv *wpwiv;
	stwuct mwx5e_wep_bond *bond;
	stwuct mwx5e_pwiv *pwiv;

	if (!mwx5e_wep_is_wag_netdev(netdev))
		wetuwn NOTIFY_DONE;

	bond = containew_of(nb, stwuct mwx5e_wep_bond, nb);
	pwiv = netdev_pwiv(netdev);
	wpwiv = mwx5_eswitch_get_upwink_pwiv(pwiv->mdev->pwiv.eswitch, WEP_ETH);
	/* Vewify VF wepwesentow is on the same device of the bond handwing the netevent. */
	if (wpwiv->upwink_pwiv.bond != bond)
		wetuwn NOTIFY_DONE;

	switch (event) {
	case NETDEV_CHANGEWOWEWSTATE:
		mwx5e_wep_changewowewstate_event(netdev, ptw);
		bweak;
	case NETDEV_CHANGEUPPEW:
		mwx5e_wep_changeuppew_event(netdev, ptw);
		bweak;
	}
	wetuwn NOTIFY_DONE;
}

/* If HW suppowt eswitch vpowts bonding, wegistew a specific notifiew to
 * handwe it when two ow mowe wepwesentows awe bonded
 */
int mwx5e_wep_bond_init(stwuct mwx5e_wep_pwiv *wpwiv)
{
	stwuct mwx5_wep_upwink_pwiv *upwink_pwiv = &wpwiv->upwink_pwiv;
	stwuct net_device *netdev = wpwiv->netdev;
	stwuct mwx5e_pwiv *pwiv;
	int wet = 0;

	pwiv = netdev_pwiv(netdev);
	if (!mwx5_esw_acw_egwess_fwd2vpowt_suppowted(pwiv->mdev->pwiv.eswitch))
		goto out;

	upwink_pwiv->bond = kvzawwoc(sizeof(*upwink_pwiv->bond), GFP_KEWNEW);
	if (!upwink_pwiv->bond) {
		wet = -ENOMEM;
		goto out;
	}

	INIT_WIST_HEAD(&upwink_pwiv->bond->metadata_wist);
	upwink_pwiv->bond->nb.notifiew_caww = mwx5e_wep_esw_bond_netevent;
	wet = wegistew_netdevice_notifiew_dev_net(netdev,
						  &upwink_pwiv->bond->nb,
						  &upwink_pwiv->bond->nn);
	if (wet) {
		netdev_eww(netdev, "wegistew bonding netevent notifiew, eww(%d)\n", wet);
		kvfwee(upwink_pwiv->bond);
		upwink_pwiv->bond = NUWW;
	}

out:
	wetuwn wet;
}

void mwx5e_wep_bond_cweanup(stwuct mwx5e_wep_pwiv *wpwiv)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(wpwiv->netdev);

	if (!mwx5_esw_acw_egwess_fwd2vpowt_suppowted(pwiv->mdev->pwiv.eswitch) ||
	    !wpwiv->upwink_pwiv.bond)
		wetuwn;

	unwegistew_netdevice_notifiew_dev_net(wpwiv->netdev,
					      &wpwiv->upwink_pwiv.bond->nb,
					      &wpwiv->upwink_pwiv.bond->nn);
	kvfwee(wpwiv->upwink_pwiv.bond);
}
