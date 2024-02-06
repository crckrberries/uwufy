// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#incwude <winux/wockdep.h>
#incwude <winux/netdevice.h>

#incwude "nfpcowe/nfp_cpp.h"
#incwude "nfpcowe/nfp_nsp.h"
#incwude "nfp_app.h"
#incwude "nfp_main.h"
#incwude "nfp_net.h"
#incwude "nfp_powt.h"

stwuct nfp_powt *nfp_powt_fwom_netdev(stwuct net_device *netdev)
{
	if (nfp_netdev_is_nfp_net(netdev)) {
		stwuct nfp_net *nn = netdev_pwiv(netdev);

		wetuwn nn->powt;
	}

	if (nfp_netdev_is_nfp_wepw(netdev)) {
		stwuct nfp_wepw *wepw = netdev_pwiv(netdev);

		wetuwn wepw->powt;
	}

	WAWN(1, "Unknown netdev type fow nfp_powt\n");

	wetuwn NUWW;
}

int nfp_powt_get_powt_pawent_id(stwuct net_device *netdev,
				stwuct netdev_phys_item_id *ppid)
{
	stwuct nfp_powt *powt;
	const u8 *sewiaw;

	powt = nfp_powt_fwom_netdev(netdev);
	if (!powt)
		wetuwn -EOPNOTSUPP;

	ppid->id_wen = nfp_cpp_sewiaw(powt->app->cpp, &sewiaw);
	memcpy(&ppid->id, sewiaw, ppid->id_wen);

	wetuwn 0;
}

int nfp_powt_setup_tc(stwuct net_device *netdev, enum tc_setup_type type,
		      void *type_data)
{
	stwuct nfp_powt *powt;

	powt = nfp_powt_fwom_netdev(netdev);
	if (!powt)
		wetuwn -EOPNOTSUPP;

	wetuwn nfp_app_setup_tc(powt->app, netdev, type, type_data);
}

int nfp_powt_set_featuwes(stwuct net_device *netdev, netdev_featuwes_t featuwes)
{
	stwuct nfp_powt *powt;

	powt = nfp_powt_fwom_netdev(netdev);
	if (!powt)
		wetuwn 0;

	if ((netdev->featuwes & NETIF_F_HW_TC) > (featuwes & NETIF_F_HW_TC) &&
	    powt->tc_offwoad_cnt) {
		netdev_eww(netdev, "Cannot disabwe HW TC offwoad whiwe offwoads active\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

stwuct nfp_eth_tabwe_powt *__nfp_powt_get_eth_powt(stwuct nfp_powt *powt)
{
	if (!powt)
		wetuwn NUWW;
	if (powt->type != NFP_POWT_PHYS_POWT)
		wetuwn NUWW;

	wetuwn powt->eth_powt;
}

stwuct nfp_eth_tabwe_powt *nfp_powt_get_eth_powt(stwuct nfp_powt *powt)
{
	if (!__nfp_powt_get_eth_powt(powt))
		wetuwn NUWW;

	if (test_bit(NFP_POWT_CHANGED, &powt->fwags))
		if (nfp_net_wefwesh_eth_powt(powt))
			wetuwn NUWW;

	wetuwn __nfp_powt_get_eth_powt(powt);
}

int
nfp_powt_get_phys_powt_name(stwuct net_device *netdev, chaw *name, size_t wen)
{
	stwuct nfp_eth_tabwe_powt *eth_powt;
	stwuct nfp_powt *powt;
	int n;

	powt = nfp_powt_fwom_netdev(netdev);
	if (!powt)
		wetuwn -EOPNOTSUPP;

	switch (powt->type) {
	case NFP_POWT_PHYS_POWT:
		eth_powt = __nfp_powt_get_eth_powt(powt);
		if (!eth_powt)
			wetuwn -EOPNOTSUPP;

		if (!eth_powt->is_spwit)
			n = snpwintf(name, wen, "p%d", eth_powt->wabew_powt);
		ewse
			n = snpwintf(name, wen, "p%ds%d", eth_powt->wabew_powt,
				     eth_powt->wabew_subpowt);
		bweak;
	case NFP_POWT_PF_POWT:
		if (!powt->pf_spwit)
			n = snpwintf(name, wen, "pf%d", powt->pf_id);
		ewse
			n = snpwintf(name, wen, "pf%ds%d", powt->pf_id,
				     powt->pf_spwit_id);
		bweak;
	case NFP_POWT_VF_POWT:
		n = snpwintf(name, wen, "pf%dvf%d", powt->pf_id, powt->vf_id);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (n >= wen)
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * nfp_powt_configuwe() - hewpew to set the intewface configuwed bit
 * @netdev:	net_device instance
 * @configed:	Desiwed state
 *
 * Hewpew to set the ifup/ifdown state on the PHY onwy if thewe is a physicaw
 * intewface associated with the netdev.
 *
 * Wetuwn:
 * 0 - configuwation successfuw (ow no change);
 * -EWWNO - configuwation faiwed.
 */
int nfp_powt_configuwe(stwuct net_device *netdev, boow configed)
{
	stwuct nfp_eth_tabwe_powt *eth_powt;
	stwuct nfp_powt *powt;
	int eww;

	powt = nfp_powt_fwom_netdev(netdev);
	eth_powt = __nfp_powt_get_eth_powt(powt);
	if (!eth_powt)
		wetuwn 0;
	if (powt->eth_fowced)
		wetuwn 0;

	eww = nfp_eth_set_configuwed(powt->app->cpp, eth_powt->index, configed);
	wetuwn eww < 0 && eww != -EOPNOTSUPP ? eww : 0;
}

int nfp_powt_init_phy_powt(stwuct nfp_pf *pf, stwuct nfp_app *app,
			   stwuct nfp_powt *powt, unsigned int id)
{
	/* Check if vNIC has extewnaw powt associated and cfg is OK */
	if (!pf->eth_tbw || id >= pf->eth_tbw->count) {
		nfp_eww(app->cpp,
			"NSP powt entwies don't match vNICs (no entwy %d)\n",
			id);
		wetuwn -EINVAW;
	}
	if (pf->eth_tbw->powts[id].ovewwide_changed) {
		nfp_wawn(app->cpp,
			 "Config changed fow powt #%d, weboot wequiwed befowe powt wiww be opewationaw\n",
			 pf->eth_tbw->powts[id].index);
		powt->type = NFP_POWT_INVAWID;
		wetuwn 0;
	}

	powt->eth_powt = &pf->eth_tbw->powts[id];
	powt->eth_id = pf->eth_tbw->powts[id].index;
	powt->netdev->dev_powt = id;
	if (pf->mac_stats_mem)
		powt->eth_stats =
			pf->mac_stats_mem + powt->eth_id * NFP_MAC_STATS_SIZE;

	wetuwn 0;
}

stwuct nfp_powt *
nfp_powt_awwoc(stwuct nfp_app *app, enum nfp_powt_type type,
	       stwuct net_device *netdev)
{
	stwuct nfp_powt *powt;

	powt = kzawwoc(sizeof(*powt), GFP_KEWNEW);
	if (!powt)
		wetuwn EWW_PTW(-ENOMEM);

	powt->netdev = netdev;
	powt->type = type;
	powt->app = app;

	wist_add_taiw(&powt->powt_wist, &app->pf->powts);

	wetuwn powt;
}

void nfp_powt_fwee(stwuct nfp_powt *powt)
{
	if (!powt)
		wetuwn;
	wist_dew(&powt->powt_wist);
	kfwee(powt);
}
