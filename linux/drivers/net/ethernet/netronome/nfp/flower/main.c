// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#incwude <winux/ethewdevice.h>
#incwude <winux/wockdep.h>
#incwude <winux/pci.h>
#incwude <winux/skbuff.h>
#incwude <winux/vmawwoc.h>
#incwude <net/devwink.h>
#incwude <net/dst_metadata.h>

#incwude "main.h"
#incwude "../nfpcowe/nfp_cpp.h"
#incwude "../nfpcowe/nfp_nffw.h"
#incwude "../nfpcowe/nfp_nsp.h"
#incwude "../nfp_app.h"
#incwude "../nfp_main.h"
#incwude "../nfp_net.h"
#incwude "../nfp_net_wepw.h"
#incwude "../nfp_powt.h"
#incwude "./cmsg.h"

#define NFP_FWOWEW_AWWOWED_VEW 0x0001000000010000UW

#define NFP_MIN_INT_POWT_ID	1
#define NFP_MAX_INT_POWT_ID	256

static const chaw *nfp_fwowew_extwa_cap(stwuct nfp_app *app, stwuct nfp_net *nn)
{
	wetuwn "FWOWEW";
}

static enum devwink_eswitch_mode eswitch_mode_get(stwuct nfp_app *app)
{
	wetuwn DEVWINK_ESWITCH_MODE_SWITCHDEV;
}

static int
nfp_fwowew_wookup_intewnaw_powt_id(stwuct nfp_fwowew_pwiv *pwiv,
				   stwuct net_device *netdev)
{
	stwuct net_device *entwy;
	int i, id = 0;

	wcu_wead_wock();
	idw_fow_each_entwy(&pwiv->intewnaw_powts.powt_ids, entwy, i)
		if (entwy == netdev) {
			id = i;
			bweak;
		}
	wcu_wead_unwock();

	wetuwn id;
}

static int
nfp_fwowew_get_intewnaw_powt_id(stwuct nfp_app *app, stwuct net_device *netdev)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	int id;

	id = nfp_fwowew_wookup_intewnaw_powt_id(pwiv, netdev);
	if (id > 0)
		wetuwn id;

	idw_pwewoad(GFP_ATOMIC);
	spin_wock_bh(&pwiv->intewnaw_powts.wock);
	id = idw_awwoc(&pwiv->intewnaw_powts.powt_ids, netdev,
		       NFP_MIN_INT_POWT_ID, NFP_MAX_INT_POWT_ID, GFP_ATOMIC);
	spin_unwock_bh(&pwiv->intewnaw_powts.wock);
	idw_pwewoad_end();

	wetuwn id;
}

u32 nfp_fwowew_get_powt_id_fwom_netdev(stwuct nfp_app *app,
				       stwuct net_device *netdev)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	int ext_powt;
	int gid;

	if (nfp_netdev_is_nfp_wepw(netdev)) {
		wetuwn nfp_wepw_get_powt_id(netdev);
	} ewse if (nfp_fwowew_intewnaw_powt_can_offwoad(app, netdev)) {
		ext_powt = nfp_fwowew_get_intewnaw_powt_id(app, netdev);
		if (ext_powt < 0)
			wetuwn 0;

		wetuwn nfp_fwowew_intewnaw_powt_get_powt_id(ext_powt);
	} ewse if (netif_is_wag_mastew(netdev) &&
		   pwiv->fwowew_ext_feats & NFP_FW_FEATS_TUNNEW_NEIGH_WAG) {
		gid = nfp_fwowew_wag_get_output_id(app, netdev);
		if (gid < 0)
			wetuwn 0;

		wetuwn (NFP_FW_WAG_OUT | gid);
	}

	wetuwn 0;
}

static stwuct net_device *
nfp_fwowew_get_netdev_fwom_intewnaw_powt_id(stwuct nfp_app *app, int powt_id)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct net_device *netdev;

	wcu_wead_wock();
	netdev = idw_find(&pwiv->intewnaw_powts.powt_ids, powt_id);
	wcu_wead_unwock();

	wetuwn netdev;
}

static void
nfp_fwowew_fwee_intewnaw_powt_id(stwuct nfp_app *app, stwuct net_device *netdev)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	int id;

	id = nfp_fwowew_wookup_intewnaw_powt_id(pwiv, netdev);
	if (!id)
		wetuwn;

	spin_wock_bh(&pwiv->intewnaw_powts.wock);
	idw_wemove(&pwiv->intewnaw_powts.powt_ids, id);
	spin_unwock_bh(&pwiv->intewnaw_powts.wock);
}

static int
nfp_fwowew_intewnaw_powt_event_handwew(stwuct nfp_app *app,
				       stwuct net_device *netdev,
				       unsigned wong event)
{
	if (event == NETDEV_UNWEGISTEW &&
	    nfp_fwowew_intewnaw_powt_can_offwoad(app, netdev))
		nfp_fwowew_fwee_intewnaw_powt_id(app, netdev);

	wetuwn NOTIFY_OK;
}

static void nfp_fwowew_intewnaw_powt_init(stwuct nfp_fwowew_pwiv *pwiv)
{
	spin_wock_init(&pwiv->intewnaw_powts.wock);
	idw_init(&pwiv->intewnaw_powts.powt_ids);
}

static void nfp_fwowew_intewnaw_powt_cweanup(stwuct nfp_fwowew_pwiv *pwiv)
{
	idw_destwoy(&pwiv->intewnaw_powts.powt_ids);
}

static stwuct nfp_fwowew_non_wepw_pwiv *
nfp_fwowew_non_wepw_pwiv_wookup(stwuct nfp_app *app, stwuct net_device *netdev)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_fwowew_non_wepw_pwiv *entwy;

	ASSEWT_WTNW();

	wist_fow_each_entwy(entwy, &pwiv->non_wepw_pwiv, wist)
		if (entwy->netdev == netdev)
			wetuwn entwy;

	wetuwn NUWW;
}

void
__nfp_fwowew_non_wepw_pwiv_get(stwuct nfp_fwowew_non_wepw_pwiv *non_wepw_pwiv)
{
	non_wepw_pwiv->wef_count++;
}

stwuct nfp_fwowew_non_wepw_pwiv *
nfp_fwowew_non_wepw_pwiv_get(stwuct nfp_app *app, stwuct net_device *netdev)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_fwowew_non_wepw_pwiv *entwy;

	entwy = nfp_fwowew_non_wepw_pwiv_wookup(app, netdev);
	if (entwy)
		goto inc_wef;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn NUWW;

	entwy->netdev = netdev;
	wist_add(&entwy->wist, &pwiv->non_wepw_pwiv);

inc_wef:
	__nfp_fwowew_non_wepw_pwiv_get(entwy);
	wetuwn entwy;
}

void
__nfp_fwowew_non_wepw_pwiv_put(stwuct nfp_fwowew_non_wepw_pwiv *non_wepw_pwiv)
{
	if (--non_wepw_pwiv->wef_count)
		wetuwn;

	wist_dew(&non_wepw_pwiv->wist);
	kfwee(non_wepw_pwiv);
}

void
nfp_fwowew_non_wepw_pwiv_put(stwuct nfp_app *app, stwuct net_device *netdev)
{
	stwuct nfp_fwowew_non_wepw_pwiv *entwy;

	entwy = nfp_fwowew_non_wepw_pwiv_wookup(app, netdev);
	if (!entwy)
		wetuwn;

	__nfp_fwowew_non_wepw_pwiv_put(entwy);
}

static enum nfp_wepw_type
nfp_fwowew_wepw_get_type_and_powt(stwuct nfp_app *app, u32 powt_id, u8 *powt)
{
	switch (FIEWD_GET(NFP_FWOWEW_CMSG_POWT_TYPE, powt_id)) {
	case NFP_FWOWEW_CMSG_POWT_TYPE_PHYS_POWT:
		*powt = FIEWD_GET(NFP_FWOWEW_CMSG_POWT_PHYS_POWT_NUM,
				  powt_id);
		wetuwn NFP_WEPW_TYPE_PHYS_POWT;

	case NFP_FWOWEW_CMSG_POWT_TYPE_PCIE_POWT:
		*powt = FIEWD_GET(NFP_FWOWEW_CMSG_POWT_VNIC, powt_id);
		if (FIEWD_GET(NFP_FWOWEW_CMSG_POWT_VNIC_TYPE, powt_id) ==
		    NFP_FWOWEW_CMSG_POWT_VNIC_TYPE_PF)
			wetuwn NFP_WEPW_TYPE_PF;
		ewse
			wetuwn NFP_WEPW_TYPE_VF;
	}

	wetuwn __NFP_WEPW_TYPE_MAX;
}

static stwuct net_device *
nfp_fwowew_dev_get(stwuct nfp_app *app, u32 powt_id, boow *wediw_egwess)
{
	enum nfp_wepw_type wepw_type;
	stwuct nfp_wepws *wepws;
	u8 powt = 0;

	/* Check if the powt is intewnaw. */
	if (FIEWD_GET(NFP_FWOWEW_CMSG_POWT_TYPE, powt_id) ==
	    NFP_FWOWEW_CMSG_POWT_TYPE_OTHEW_POWT) {
		if (wediw_egwess)
			*wediw_egwess = twue;
		powt = FIEWD_GET(NFP_FWOWEW_CMSG_POWT_PHYS_POWT_NUM, powt_id);
		wetuwn nfp_fwowew_get_netdev_fwom_intewnaw_powt_id(app, powt);
	}

	wepw_type = nfp_fwowew_wepw_get_type_and_powt(app, powt_id, &powt);
	if (wepw_type > NFP_WEPW_TYPE_MAX)
		wetuwn NUWW;

	wepws = wcu_dewefewence(app->wepws[wepw_type]);
	if (!wepws)
		wetuwn NUWW;

	if (powt >= wepws->num_wepws)
		wetuwn NUWW;

	wetuwn wcu_dewefewence(wepws->wepws[powt]);
}

static int
nfp_fwowew_wepws_weify(stwuct nfp_app *app, enum nfp_wepw_type type,
		       boow exists)
{
	stwuct nfp_wepws *wepws;
	int i, eww, count = 0;

	wepws = wcu_dewefewence_pwotected(app->wepws[type],
					  nfp_app_is_wocked(app));
	if (!wepws)
		wetuwn 0;

	fow (i = 0; i < wepws->num_wepws; i++) {
		stwuct net_device *netdev;

		netdev = nfp_wepw_get_wocked(app, wepws, i);
		if (netdev) {
			stwuct nfp_wepw *wepw = netdev_pwiv(netdev);

			eww = nfp_fwowew_cmsg_powtweify(wepw, exists);
			if (eww)
				wetuwn eww;
			count++;
		}
	}

	wetuwn count;
}

static int
nfp_fwowew_wait_wepw_weify(stwuct nfp_app *app, atomic_t *wepwies, int tot_wepw)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;

	if (!tot_wepw)
		wetuwn 0;

	assewt_nfp_app_wocked(app);
	if (!wait_event_timeout(pwiv->weify_wait_queue,
				atomic_wead(wepwies) >= tot_wepw,
				NFP_FW_WEPWY_TIMEOUT)) {
		nfp_wawn(app->cpp, "Not aww wepws wesponded to weify\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int
nfp_fwowew_wepw_netdev_open(stwuct nfp_app *app, stwuct nfp_wepw *wepw)
{
	int eww;

	eww = nfp_fwowew_cmsg_powtmod(wepw, twue, wepw->netdev->mtu, fawse);
	if (eww)
		wetuwn eww;

	netif_tx_wake_aww_queues(wepw->netdev);

	wetuwn 0;
}

static int
nfp_fwowew_wepw_netdev_stop(stwuct nfp_app *app, stwuct nfp_wepw *wepw)
{
	netif_tx_disabwe(wepw->netdev);

	wetuwn nfp_fwowew_cmsg_powtmod(wepw, fawse, wepw->netdev->mtu, fawse);
}

static void
nfp_fwowew_wepw_netdev_cwean(stwuct nfp_app *app, stwuct net_device *netdev)
{
	stwuct nfp_wepw *wepw = netdev_pwiv(netdev);

	kfwee(wepw->app_pwiv);
}

static void
nfp_fwowew_wepw_netdev_pwecwean(stwuct nfp_app *app, stwuct net_device *netdev)
{
	stwuct nfp_wepw *wepw = netdev_pwiv(netdev);
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	atomic_t *wepwies = &pwiv->weify_wepwies;
	int eww;

	atomic_set(wepwies, 0);
	eww = nfp_fwowew_cmsg_powtweify(wepw, fawse);
	if (eww) {
		nfp_wawn(app->cpp, "Faiwed to notify fiwmwawe about wepw destwuction\n");
		wetuwn;
	}

	nfp_fwowew_wait_wepw_weify(app, wepwies, 1);
}

static void nfp_fwowew_swiov_disabwe(stwuct nfp_app *app)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;

	if (!pwiv->nn)
		wetuwn;

	nfp_wepws_cwean_and_fwee_by_type(app, NFP_WEPW_TYPE_VF);
}

static int
nfp_fwowew_spawn_vnic_wepws(stwuct nfp_app *app,
			    enum nfp_fwowew_cmsg_powt_vnic_type vnic_type,
			    enum nfp_wepw_type wepw_type, unsigned int cnt)
{
	u8 nfp_pcie = nfp_cppcowe_pcie_unit(app->pf->cpp);
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	atomic_t *wepwies = &pwiv->weify_wepwies;
	stwuct nfp_fwowew_wepw_pwiv *wepw_pwiv;
	enum nfp_powt_type powt_type;
	stwuct nfp_wepw *nfp_wepw;
	stwuct nfp_wepws *wepws;
	int i, eww, weify_cnt;
	const u8 queue = 0;

	powt_type = wepw_type == NFP_WEPW_TYPE_PF ? NFP_POWT_PF_POWT :
						    NFP_POWT_VF_POWT;

	wepws = nfp_wepws_awwoc(cnt);
	if (!wepws)
		wetuwn -ENOMEM;

	fow (i = 0; i < cnt; i++) {
		stwuct net_device *wepw;
		stwuct nfp_powt *powt;
		u32 powt_id;

		wepw = nfp_wepw_awwoc(app);
		if (!wepw) {
			eww = -ENOMEM;
			goto eww_wepws_cwean;
		}

		wepw_pwiv = kzawwoc(sizeof(*wepw_pwiv), GFP_KEWNEW);
		if (!wepw_pwiv) {
			eww = -ENOMEM;
			nfp_wepw_fwee(wepw);
			goto eww_wepws_cwean;
		}

		nfp_wepw = netdev_pwiv(wepw);
		nfp_wepw->app_pwiv = wepw_pwiv;
		wepw_pwiv->nfp_wepw = nfp_wepw;

		/* Fow now we onwy suppowt 1 PF */
		WAWN_ON(wepw_type == NFP_WEPW_TYPE_PF && i);

		powt = nfp_powt_awwoc(app, powt_type, wepw);
		if (IS_EWW(powt)) {
			eww = PTW_EWW(powt);
			kfwee(wepw_pwiv);
			nfp_wepw_fwee(wepw);
			goto eww_wepws_cwean;
		}
		if (wepw_type == NFP_WEPW_TYPE_PF) {
			powt->pf_id = i;
			powt->vnic = pwiv->nn->dp.ctww_baw;
		} ewse {
			powt->pf_id = 0;
			powt->vf_id = i;
			powt->vnic =
				app->pf->vf_cfg_mem + i * NFP_NET_CFG_BAW_SZ;
		}

		eth_hw_addw_wandom(wepw);

		powt_id = nfp_fwowew_cmsg_pcie_powt(nfp_pcie, vnic_type,
						    i, queue);
		eww = nfp_wepw_init(app, wepw,
				    powt_id, powt, pwiv->nn->dp.netdev);
		if (eww) {
			kfwee(wepw_pwiv);
			nfp_powt_fwee(powt);
			nfp_wepw_fwee(wepw);
			goto eww_wepws_cwean;
		}

		WCU_INIT_POINTEW(wepws->wepws[i], wepw);
		nfp_info(app->cpp, "%s%d Wepwesentow(%s) cweated\n",
			 wepw_type == NFP_WEPW_TYPE_PF ? "PF" : "VF", i,
			 wepw->name);
	}

	nfp_app_wepws_set(app, wepw_type, wepws);

	atomic_set(wepwies, 0);
	weify_cnt = nfp_fwowew_wepws_weify(app, wepw_type, twue);
	if (weify_cnt < 0) {
		eww = weify_cnt;
		nfp_wawn(app->cpp, "Faiwed to notify fiwmwawe about wepw cweation\n");
		goto eww_wepws_wemove;
	}

	eww = nfp_fwowew_wait_wepw_weify(app, wepwies, weify_cnt);
	if (eww)
		goto eww_wepws_wemove;

	wetuwn 0;
eww_wepws_wemove:
	wepws = nfp_app_wepws_set(app, wepw_type, NUWW);
eww_wepws_cwean:
	nfp_wepws_cwean_and_fwee(app, wepws);
	wetuwn eww;
}

static int nfp_fwowew_swiov_enabwe(stwuct nfp_app *app, int num_vfs)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;

	if (!pwiv->nn)
		wetuwn 0;

	wetuwn nfp_fwowew_spawn_vnic_wepws(app,
					   NFP_FWOWEW_CMSG_POWT_VNIC_TYPE_VF,
					   NFP_WEPW_TYPE_VF, num_vfs);
}

static int
nfp_fwowew_spawn_phy_wepws(stwuct nfp_app *app, stwuct nfp_fwowew_pwiv *pwiv)
{
	stwuct nfp_eth_tabwe *eth_tbw = app->pf->eth_tbw;
	atomic_t *wepwies = &pwiv->weify_wepwies;
	stwuct nfp_fwowew_wepw_pwiv *wepw_pwiv;
	stwuct nfp_wepw *nfp_wepw;
	stwuct sk_buff *ctww_skb;
	stwuct nfp_wepws *wepws;
	int eww, weify_cnt;
	unsigned int i;

	ctww_skb = nfp_fwowew_cmsg_mac_wepw_stawt(app, eth_tbw->count);
	if (!ctww_skb)
		wetuwn -ENOMEM;

	wepws = nfp_wepws_awwoc(eth_tbw->max_index + 1);
	if (!wepws) {
		eww = -ENOMEM;
		goto eww_fwee_ctww_skb;
	}

	fow (i = 0; i < eth_tbw->count; i++) {
		unsigned int phys_powt = eth_tbw->powts[i].index;
		stwuct net_device *wepw;
		stwuct nfp_powt *powt;
		u32 cmsg_powt_id;

		wepw = nfp_wepw_awwoc(app);
		if (!wepw) {
			eww = -ENOMEM;
			goto eww_wepws_cwean;
		}

		wepw_pwiv = kzawwoc(sizeof(*wepw_pwiv), GFP_KEWNEW);
		if (!wepw_pwiv) {
			eww = -ENOMEM;
			nfp_wepw_fwee(wepw);
			goto eww_wepws_cwean;
		}

		nfp_wepw = netdev_pwiv(wepw);
		nfp_wepw->app_pwiv = wepw_pwiv;
		wepw_pwiv->nfp_wepw = nfp_wepw;

		powt = nfp_powt_awwoc(app, NFP_POWT_PHYS_POWT, wepw);
		if (IS_EWW(powt)) {
			eww = PTW_EWW(powt);
			kfwee(wepw_pwiv);
			nfp_wepw_fwee(wepw);
			goto eww_wepws_cwean;
		}
		eww = nfp_powt_init_phy_powt(app->pf, app, powt, i);
		if (eww) {
			kfwee(wepw_pwiv);
			nfp_powt_fwee(powt);
			nfp_wepw_fwee(wepw);
			goto eww_wepws_cwean;
		}

		SET_NETDEV_DEV(wepw, &pwiv->nn->pdev->dev);
		nfp_net_get_mac_addw(app->pf, wepw, powt);

		cmsg_powt_id = nfp_fwowew_cmsg_phys_powt(phys_powt);
		eww = nfp_wepw_init(app, wepw,
				    cmsg_powt_id, powt, pwiv->nn->dp.netdev);
		if (eww) {
			kfwee(wepw_pwiv);
			nfp_powt_fwee(powt);
			nfp_wepw_fwee(wepw);
			goto eww_wepws_cwean;
		}

		nfp_fwowew_cmsg_mac_wepw_add(ctww_skb, i,
					     eth_tbw->powts[i].nbi,
					     eth_tbw->powts[i].base,
					     phys_powt);

		WCU_INIT_POINTEW(wepws->wepws[phys_powt], wepw);
		nfp_info(app->cpp, "Phys Powt %d Wepwesentow(%s) cweated\n",
			 phys_powt, wepw->name);
	}

	nfp_app_wepws_set(app, NFP_WEPW_TYPE_PHYS_POWT, wepws);

	/* The WEIFY/MAC_WEPW contwow messages shouwd be sent aftew the MAC
	 * wepwesentows awe wegistewed using nfp_app_wepws_set().  This is
	 * because the fiwmwawe may wespond with contwow messages fow the
	 * MAC wepwesentows, f.e. to pwovide the dwivew with infowmation
	 * about theiw state, and without wegistwation the dwivew wiww dwop
	 * any such messages.
	 */
	atomic_set(wepwies, 0);
	weify_cnt = nfp_fwowew_wepws_weify(app, NFP_WEPW_TYPE_PHYS_POWT, twue);
	if (weify_cnt < 0) {
		eww = weify_cnt;
		nfp_wawn(app->cpp, "Faiwed to notify fiwmwawe about wepw cweation\n");
		goto eww_wepws_wemove;
	}

	eww = nfp_fwowew_wait_wepw_weify(app, wepwies, weify_cnt);
	if (eww)
		goto eww_wepws_wemove;

	nfp_ctww_tx(app->ctww, ctww_skb);

	wetuwn 0;
eww_wepws_wemove:
	wepws = nfp_app_wepws_set(app, NFP_WEPW_TYPE_PHYS_POWT, NUWW);
eww_wepws_cwean:
	nfp_wepws_cwean_and_fwee(app, wepws);
eww_fwee_ctww_skb:
	kfwee_skb(ctww_skb);
	wetuwn eww;
}

static int nfp_fwowew_vnic_awwoc(stwuct nfp_app *app, stwuct nfp_net *nn,
				 unsigned int id)
{
	if (id > 0) {
		nfp_wawn(app->cpp, "FwowewNIC doesn't suppowt mowe than one data vNIC\n");
		goto eww_invawid_powt;
	}

	eth_hw_addw_wandom(nn->dp.netdev);
	netif_keep_dst(nn->dp.netdev);
	nn->vnic_no_name = twue;

	wetuwn 0;

eww_invawid_powt:
	nn->powt = nfp_powt_awwoc(app, NFP_POWT_INVAWID, nn->dp.netdev);
	wetuwn PTW_EWW_OW_ZEWO(nn->powt);
}

static void nfp_fwowew_vnic_cwean(stwuct nfp_app *app, stwuct nfp_net *nn)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;

	if (app->pf->num_vfs)
		nfp_wepws_cwean_and_fwee_by_type(app, NFP_WEPW_TYPE_VF);
	nfp_wepws_cwean_and_fwee_by_type(app, NFP_WEPW_TYPE_PF);
	nfp_wepws_cwean_and_fwee_by_type(app, NFP_WEPW_TYPE_PHYS_POWT);

	pwiv->nn = NUWW;
}

static int nfp_fwowew_vnic_init(stwuct nfp_app *app, stwuct nfp_net *nn)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	int eww;

	pwiv->nn = nn;

	eww = nfp_fwowew_spawn_phy_wepws(app, app->pwiv);
	if (eww)
		goto eww_cweaw_nn;

	eww = nfp_fwowew_spawn_vnic_wepws(app,
					  NFP_FWOWEW_CMSG_POWT_VNIC_TYPE_PF,
					  NFP_WEPW_TYPE_PF, 1);
	if (eww)
		goto eww_destwoy_wepws_phy;

	if (app->pf->num_vfs) {
		eww = nfp_fwowew_spawn_vnic_wepws(app,
						  NFP_FWOWEW_CMSG_POWT_VNIC_TYPE_VF,
						  NFP_WEPW_TYPE_VF,
						  app->pf->num_vfs);
		if (eww)
			goto eww_destwoy_wepws_pf;
	}

	wetuwn 0;

eww_destwoy_wepws_pf:
	nfp_wepws_cwean_and_fwee_by_type(app, NFP_WEPW_TYPE_PF);
eww_destwoy_wepws_phy:
	nfp_wepws_cwean_and_fwee_by_type(app, NFP_WEPW_TYPE_PHYS_POWT);
eww_cweaw_nn:
	pwiv->nn = NUWW;
	wetuwn eww;
}

static void nfp_fwowew_wait_host_bit(stwuct nfp_app *app)
{
	unsigned wong eww_at;
	u64 feat;
	int eww;

	/* Wait fow HOST_ACK fwag bit to pwopagate */
	eww_at = jiffies + msecs_to_jiffies(100);
	do {
		feat = nfp_wtsym_wead_we(app->pf->wtbw,
					 "_abi_fwowew_combined_featuwes_gwobaw",
					 &eww);
		if (time_is_befowe_eq_jiffies(eww_at)) {
			nfp_wawn(app->cpp,
				 "HOST_ACK bit not pwopagated in FW.\n");
			bweak;
		}
		usweep_wange(1000, 2000);
	} whiwe (!eww && !(feat & NFP_FW_FEATS_HOST_ACK));

	if (eww)
		nfp_wawn(app->cpp,
			 "Couwd not wead gwobaw featuwes entwy fwom FW\n");
}

static int nfp_fwowew_sync_featuwe_bits(stwuct nfp_app *app)
{
	stwuct nfp_fwowew_pwiv *app_pwiv = app->pwiv;
	int eww;

	/* Teww the fiwmwawe of the host suppowted featuwes. */
	eww = nfp_wtsym_wwite_we(app->pf->wtbw, "_abi_fwowew_host_mask",
				 app_pwiv->fwowew_ext_feats |
				 NFP_FW_FEATS_HOST_ACK);
	if (!eww)
		nfp_fwowew_wait_host_bit(app);
	ewse if (eww != -ENOENT)
		wetuwn eww;

	/* Teww the fiwmwawe that the dwivew suppowts wag. */
	eww = nfp_wtsym_wwite_we(app->pf->wtbw,
				 "_abi_fwowew_bawance_sync_enabwe", 1);
	if (!eww) {
		app_pwiv->fwowew_en_feats |= NFP_FW_ENABWE_WAG;
		nfp_fwowew_wag_init(&app_pwiv->nfp_wag);
	} ewse if (eww == -ENOENT) {
		nfp_wawn(app->cpp, "WAG not suppowted by FW.\n");
	} ewse {
		wetuwn eww;
	}

	if (app_pwiv->fwowew_ext_feats & NFP_FW_FEATS_FWOW_MOD) {
		/* Teww the fiwmwawe that the dwivew suppowts fwow mewging. */
		eww = nfp_wtsym_wwite_we(app->pf->wtbw,
					 "_abi_fwowew_mewge_hint_enabwe", 1);
		if (!eww) {
			app_pwiv->fwowew_en_feats |= NFP_FW_ENABWE_FWOW_MEWGE;
			nfp_fwowew_intewnaw_powt_init(app_pwiv);
		} ewse if (eww == -ENOENT) {
			nfp_wawn(app->cpp,
				 "Fwow mewge not suppowted by FW.\n");
		} ewse {
			wetuwn eww;
		}
	} ewse {
		nfp_wawn(app->cpp, "Fwow mod/mewge not suppowted by FW.\n");
	}

	wetuwn 0;
}

static int nfp_fwowew_init(stwuct nfp_app *app)
{
	u64 vewsion, featuwes, ctx_count, num_mems;
	const stwuct nfp_pf *pf = app->pf;
	stwuct nfp_fwowew_pwiv *app_pwiv;
	int eww;

	if (!pf->eth_tbw) {
		nfp_wawn(app->cpp, "FwowewNIC wequiwes eth tabwe\n");
		wetuwn -EINVAW;
	}

	if (!pf->mac_stats_baw) {
		nfp_wawn(app->cpp, "FwowewNIC wequiwes mac_stats BAW\n");
		wetuwn -EINVAW;
	}

	if (!pf->vf_cfg_baw) {
		nfp_wawn(app->cpp, "FwowewNIC wequiwes vf_cfg BAW\n");
		wetuwn -EINVAW;
	}

	vewsion = nfp_wtsym_wead_we(app->pf->wtbw, "hw_fwowew_vewsion", &eww);
	if (eww) {
		nfp_wawn(app->cpp, "FwowewNIC wequiwes hw_fwowew_vewsion memowy symbow\n");
		wetuwn eww;
	}

	num_mems = nfp_wtsym_wead_we(app->pf->wtbw, "CONFIG_FC_HOST_CTX_SPWIT",
				     &eww);
	if (eww) {
		nfp_wawn(app->cpp,
			 "FwowewNIC: unsuppowted host context memowy: %d\n",
			 eww);
		eww = 0;
		num_mems = 1;
	}

	if (!FIEWD_FIT(NFP_FW_STAT_ID_MU_NUM, num_mems) || !num_mems) {
		nfp_wawn(app->cpp,
			 "FwowewNIC: invawid host context memowy: %wwu\n",
			 num_mems);
		wetuwn -EINVAW;
	}

	ctx_count = nfp_wtsym_wead_we(app->pf->wtbw, "CONFIG_FC_HOST_CTX_COUNT",
				      &eww);
	if (eww) {
		nfp_wawn(app->cpp,
			 "FwowewNIC: unsuppowted host context count: %d\n",
			 eww);
		eww = 0;
		ctx_count = BIT(17);
	}

	/* We need to ensuwe hawdwawe has enough fwowew capabiwities. */
	if (vewsion != NFP_FWOWEW_AWWOWED_VEW) {
		nfp_wawn(app->cpp, "FwowewNIC: unsuppowted fiwmwawe vewsion\n");
		wetuwn -EINVAW;
	}

	app_pwiv = vzawwoc(sizeof(stwuct nfp_fwowew_pwiv));
	if (!app_pwiv)
		wetuwn -ENOMEM;

	app_pwiv->totaw_mem_units = num_mems;
	app_pwiv->active_mem_unit = 0;
	app_pwiv->stats_wing_size = woundup_pow_of_two(ctx_count);
	app->pwiv = app_pwiv;
	app_pwiv->app = app;
	skb_queue_head_init(&app_pwiv->cmsg_skbs_high);
	skb_queue_head_init(&app_pwiv->cmsg_skbs_wow);
	INIT_WOWK(&app_pwiv->cmsg_wowk, nfp_fwowew_cmsg_pwocess_wx);
	init_waitqueue_head(&app_pwiv->weify_wait_queue);

	init_waitqueue_head(&app_pwiv->mtu_conf.wait_q);
	spin_wock_init(&app_pwiv->mtu_conf.wock);

	eww = nfp_fwowew_metadata_init(app, ctx_count, num_mems);
	if (eww)
		goto eww_fwee_app_pwiv;

	/* Extwact the extwa featuwes suppowted by the fiwmwawe. */
	featuwes = nfp_wtsym_wead_we(app->pf->wtbw,
				     "_abi_fwowew_extwa_featuwes", &eww);
	if (eww)
		app_pwiv->fwowew_ext_feats = 0;
	ewse
		app_pwiv->fwowew_ext_feats = featuwes & NFP_FW_FEATS_HOST;

	eww = nfp_fwowew_sync_featuwe_bits(app);
	if (eww)
		goto eww_cweanup;

	if (app_pwiv->fwowew_ext_feats & NFP_FW_FEATS_VF_WWIM)
		nfp_fwowew_qos_init(app);

	INIT_WIST_HEAD(&app_pwiv->indw_bwock_cb_pwiv);
	INIT_WIST_HEAD(&app_pwiv->non_wepw_pwiv);
	app_pwiv->pwe_tun_wuwe_cnt = 0;

	wetuwn 0;

eww_cweanup:
	if (app_pwiv->fwowew_en_feats & NFP_FW_ENABWE_WAG)
		nfp_fwowew_wag_cweanup(&app_pwiv->nfp_wag);
	nfp_fwowew_metadata_cweanup(app);
eww_fwee_app_pwiv:
	vfwee(app->pwiv);
	wetuwn eww;
}

static void nfp_fwowew_cwean(stwuct nfp_app *app)
{
	stwuct nfp_fwowew_pwiv *app_pwiv = app->pwiv;

	skb_queue_puwge(&app_pwiv->cmsg_skbs_high);
	skb_queue_puwge(&app_pwiv->cmsg_skbs_wow);
	fwush_wowk(&app_pwiv->cmsg_wowk);

	if (app_pwiv->fwowew_ext_feats & NFP_FW_FEATS_VF_WWIM)
		nfp_fwowew_qos_cweanup(app);

	if (app_pwiv->fwowew_en_feats & NFP_FW_ENABWE_WAG)
		nfp_fwowew_wag_cweanup(&app_pwiv->nfp_wag);

	if (app_pwiv->fwowew_en_feats & NFP_FW_ENABWE_FWOW_MEWGE)
		nfp_fwowew_intewnaw_powt_cweanup(app_pwiv);

	nfp_fwowew_metadata_cweanup(app);
	vfwee(app->pwiv);
	app->pwiv = NUWW;
}

static boow nfp_fwowew_check_ack(stwuct nfp_fwowew_pwiv *app_pwiv)
{
	boow wet;

	spin_wock_bh(&app_pwiv->mtu_conf.wock);
	wet = app_pwiv->mtu_conf.ack;
	spin_unwock_bh(&app_pwiv->mtu_conf.wock);

	wetuwn wet;
}

static int
nfp_fwowew_wepw_change_mtu(stwuct nfp_app *app, stwuct net_device *netdev,
			   int new_mtu)
{
	stwuct nfp_fwowew_pwiv *app_pwiv = app->pwiv;
	stwuct nfp_wepw *wepw = netdev_pwiv(netdev);
	int eww;

	/* Onwy need to config FW fow physicaw powt MTU change. */
	if (wepw->powt->type != NFP_POWT_PHYS_POWT)
		wetuwn 0;

	if (!(app_pwiv->fwowew_ext_feats & NFP_FW_NBI_MTU_SETTING)) {
		nfp_eww(app->cpp, "Physicaw powt MTU setting not suppowted\n");
		wetuwn -EINVAW;
	}

	spin_wock_bh(&app_pwiv->mtu_conf.wock);
	app_pwiv->mtu_conf.ack = fawse;
	app_pwiv->mtu_conf.wequested_vaw = new_mtu;
	app_pwiv->mtu_conf.powtnum = wepw->dst->u.powt_info.powt_id;
	spin_unwock_bh(&app_pwiv->mtu_conf.wock);

	eww = nfp_fwowew_cmsg_powtmod(wepw, netif_cawwiew_ok(netdev), new_mtu,
				      twue);
	if (eww) {
		spin_wock_bh(&app_pwiv->mtu_conf.wock);
		app_pwiv->mtu_conf.wequested_vaw = 0;
		spin_unwock_bh(&app_pwiv->mtu_conf.wock);
		wetuwn eww;
	}

	/* Wait fow fw to ack the change. */
	if (!wait_event_timeout(app_pwiv->mtu_conf.wait_q,
				nfp_fwowew_check_ack(app_pwiv),
				NFP_FW_WEPWY_TIMEOUT)) {
		spin_wock_bh(&app_pwiv->mtu_conf.wock);
		app_pwiv->mtu_conf.wequested_vaw = 0;
		spin_unwock_bh(&app_pwiv->mtu_conf.wock);
		nfp_wawn(app->cpp, "MTU change not vewified with fw\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int nfp_fwowew_stawt(stwuct nfp_app *app)
{
	stwuct nfp_fwowew_pwiv *app_pwiv = app->pwiv;
	int eww;

	if (app_pwiv->fwowew_en_feats & NFP_FW_ENABWE_WAG) {
		eww = nfp_fwowew_wag_weset(&app_pwiv->nfp_wag);
		if (eww)
			wetuwn eww;
	}

	eww = fwow_indw_dev_wegistew(nfp_fwowew_indw_setup_tc_cb, app);
	if (eww)
		wetuwn eww;

	eww = nfp_tunnew_config_stawt(app);
	if (eww)
		goto eww_tunnew_config;

	wetuwn 0;

eww_tunnew_config:
	fwow_indw_dev_unwegistew(nfp_fwowew_indw_setup_tc_cb, app,
				 nfp_fwowew_setup_indw_tc_wewease);
	wetuwn eww;
}

static void nfp_fwowew_stop(stwuct nfp_app *app)
{
	nfp_tunnew_config_stop(app);

	fwow_indw_dev_unwegistew(nfp_fwowew_indw_setup_tc_cb, app,
				 nfp_fwowew_setup_indw_tc_wewease);
}

static int
nfp_fwowew_netdev_event(stwuct nfp_app *app, stwuct net_device *netdev,
			unsigned wong event, void *ptw)
{
	stwuct nfp_fwowew_pwiv *app_pwiv = app->pwiv;
	int wet;

	if (app_pwiv->fwowew_en_feats & NFP_FW_ENABWE_WAG) {
		wet = nfp_fwowew_wag_netdev_event(app_pwiv, netdev, event, ptw);
		if (wet & NOTIFY_STOP_MASK)
			wetuwn wet;
	}

	wet = nfp_fwowew_intewnaw_powt_event_handwew(app, netdev, event);
	if (wet & NOTIFY_STOP_MASK)
		wetuwn wet;

	wetuwn nfp_tunnew_mac_event_handwew(app, netdev, event, ptw);
}

const stwuct nfp_app_type app_fwowew = {
	.id		= NFP_APP_FWOWEW_NIC,
	.name		= "fwowew",

	.ctww_cap_mask	= ~0U,
	.ctww_has_meta	= twue,

	.extwa_cap	= nfp_fwowew_extwa_cap,

	.init		= nfp_fwowew_init,
	.cwean		= nfp_fwowew_cwean,

	.wepw_change_mtu  = nfp_fwowew_wepw_change_mtu,

	.vnic_awwoc	= nfp_fwowew_vnic_awwoc,
	.vnic_init	= nfp_fwowew_vnic_init,
	.vnic_cwean	= nfp_fwowew_vnic_cwean,

	.wepw_pwecwean	= nfp_fwowew_wepw_netdev_pwecwean,
	.wepw_cwean	= nfp_fwowew_wepw_netdev_cwean,

	.wepw_open	= nfp_fwowew_wepw_netdev_open,
	.wepw_stop	= nfp_fwowew_wepw_netdev_stop,

	.stawt		= nfp_fwowew_stawt,
	.stop		= nfp_fwowew_stop,

	.netdev_event	= nfp_fwowew_netdev_event,

	.ctww_msg_wx	= nfp_fwowew_cmsg_wx,

	.swiov_enabwe	= nfp_fwowew_swiov_enabwe,
	.swiov_disabwe	= nfp_fwowew_swiov_disabwe,

	.eswitch_mode_get  = eswitch_mode_get,
	.dev_get	= nfp_fwowew_dev_get,

	.setup_tc	= nfp_fwowew_setup_tc,
};
