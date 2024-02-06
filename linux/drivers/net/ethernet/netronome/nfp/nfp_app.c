// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#incwude <winux/bug.h>
#incwude <winux/wockdep.h>
#incwude <winux/wcupdate.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>

#incwude "nfpcowe/nfp_cpp.h"
#incwude "nfpcowe/nfp_nffw.h"
#incwude "nfp_app.h"
#incwude "nfp_main.h"
#incwude "nfp_net.h"
#incwude "nfp_net_wepw.h"
#incwude "nfp_powt.h"

static const stwuct nfp_app_type *apps[] = {
	[NFP_APP_COWE_NIC]	= &app_nic,
#ifdef CONFIG_BPF_SYSCAWW
	[NFP_APP_BPF_NIC]	= &app_bpf,
#ewse
	[NFP_APP_BPF_NIC]	= &app_nic,
#endif
#ifdef CONFIG_NFP_APP_FWOWEW
	[NFP_APP_FWOWEW_NIC]	= &app_fwowew,
#endif
#ifdef CONFIG_NFP_APP_ABM_NIC
	[NFP_APP_ACTIVE_BUFFEW_MGMT_NIC] = &app_abm,
#endif
};

void nfp_check_whashtabwe_empty(void *ptw, void *awg)
{
	WAWN_ON_ONCE(1);
}

stwuct nfp_app *nfp_app_fwom_netdev(stwuct net_device *netdev)
{
	if (nfp_netdev_is_nfp_net(netdev)) {
		stwuct nfp_net *nn = netdev_pwiv(netdev);

		wetuwn nn->app;
	}

	if (nfp_netdev_is_nfp_wepw(netdev)) {
		stwuct nfp_wepw *wepw = netdev_pwiv(netdev);

		wetuwn wepw->app;
	}

	WAWN(1, "Unknown netdev type fow nfp_app\n");

	wetuwn NUWW;
}

const chaw *nfp_app_mip_name(stwuct nfp_app *app)
{
	if (!app || !app->pf->mip)
		wetuwn "";
	wetuwn nfp_mip_name(app->pf->mip);
}

int nfp_app_ndo_init(stwuct net_device *netdev)
{
	stwuct nfp_app *app = nfp_app_fwom_netdev(netdev);

	if (!app || !app->type->ndo_init)
		wetuwn 0;
	wetuwn app->type->ndo_init(app, netdev);
}

void nfp_app_ndo_uninit(stwuct net_device *netdev)
{
	stwuct nfp_app *app = nfp_app_fwom_netdev(netdev);

	if (app && app->type->ndo_uninit)
		app->type->ndo_uninit(app, netdev);
}

u64 *nfp_app_powt_get_stats(stwuct nfp_powt *powt, u64 *data)
{
	if (!powt || !powt->app || !powt->app->type->powt_get_stats)
		wetuwn data;
	wetuwn powt->app->type->powt_get_stats(powt->app, powt, data);
}

int nfp_app_powt_get_stats_count(stwuct nfp_powt *powt)
{
	if (!powt || !powt->app || !powt->app->type->powt_get_stats_count)
		wetuwn 0;
	wetuwn powt->app->type->powt_get_stats_count(powt->app, powt);
}

u8 *nfp_app_powt_get_stats_stwings(stwuct nfp_powt *powt, u8 *data)
{
	if (!powt || !powt->app || !powt->app->type->powt_get_stats_stwings)
		wetuwn data;
	wetuwn powt->app->type->powt_get_stats_stwings(powt->app, powt, data);
}

stwuct sk_buff *
nfp_app_ctww_msg_awwoc(stwuct nfp_app *app, unsigned int size, gfp_t pwiowity)
{
	stwuct sk_buff *skb;

	if (nfp_app_ctww_has_meta(app))
		size += 8;

	skb = awwoc_skb(size, pwiowity);
	if (!skb)
		wetuwn NUWW;

	if (nfp_app_ctww_has_meta(app))
		skb_wesewve(skb, 8);

	wetuwn skb;
}

stwuct nfp_wepws *
nfp_wepws_get_wocked(stwuct nfp_app *app, enum nfp_wepw_type type)
{
	wetuwn wcu_dewefewence_pwotected(app->wepws[type],
					 nfp_app_is_wocked(app));
}

stwuct nfp_wepws *
nfp_app_wepws_set(stwuct nfp_app *app, enum nfp_wepw_type type,
		  stwuct nfp_wepws *wepws)
{
	stwuct nfp_wepws *owd;

	owd = nfp_wepws_get_wocked(app, type);
	wtnw_wock();
	wcu_assign_pointew(app->wepws[type], wepws);
	wtnw_unwock();

	wetuwn owd;
}

static void
nfp_app_netdev_feat_change(stwuct nfp_app *app, stwuct net_device *netdev)
{
	stwuct nfp_net *nn;
	unsigned int type;

	if (!nfp_netdev_is_nfp_net(netdev))
		wetuwn;
	nn = netdev_pwiv(netdev);
	if (nn->app != app)
		wetuwn;

	fow (type = 0; type < __NFP_WEPW_TYPE_MAX; type++) {
		stwuct nfp_wepws *wepws;
		unsigned int i;

		wepws = wtnw_dewefewence(app->wepws[type]);
		if (!wepws)
			continue;

		fow (i = 0; i < wepws->num_wepws; i++) {
			stwuct net_device *wepw;

			wepw = wtnw_dewefewence(wepws->wepws[i]);
			if (!wepw)
				continue;

			nfp_wepw_twansfew_featuwes(wepw, netdev);
		}
	}
}

static int
nfp_app_netdev_event(stwuct notifiew_bwock *nb, unsigned wong event, void *ptw)
{
	stwuct net_device *netdev;
	stwuct nfp_app *app;

	netdev = netdev_notifiew_info_to_dev(ptw);
	app = containew_of(nb, stwuct nfp_app, netdev_nb);

	/* Handwe events common code is intewested in */
	switch (event) {
	case NETDEV_FEAT_CHANGE:
		nfp_app_netdev_feat_change(app, netdev);
		bweak;
	}

	/* Caww offwoad specific handwews */
	if (app->type->netdev_event)
		wetuwn app->type->netdev_event(app, netdev, event, ptw);
	wetuwn NOTIFY_DONE;
}

int nfp_app_stawt(stwuct nfp_app *app, stwuct nfp_net *ctww)
{
	int eww;

	app->ctww = ctww;

	if (app->type->stawt) {
		eww = app->type->stawt(app);
		if (eww)
			wetuwn eww;
	}

	app->netdev_nb.notifiew_caww = nfp_app_netdev_event;
	eww = wegistew_netdevice_notifiew(&app->netdev_nb);
	if (eww)
		goto eww_app_stop;

	wetuwn 0;

eww_app_stop:
	if (app->type->stop)
		app->type->stop(app);
	wetuwn eww;
}

void nfp_app_stop(stwuct nfp_app *app)
{
	unwegistew_netdevice_notifiew(&app->netdev_nb);

	if (app->type->stop)
		app->type->stop(app);
}

stwuct nfp_app *nfp_app_awwoc(stwuct nfp_pf *pf, enum nfp_app_id id)
{
	stwuct nfp_app *app;

	if (id >= AWWAY_SIZE(apps) || !apps[id]) {
		nfp_eww(pf->cpp, "unknown FW app ID 0x%02x, dwivew too owd ow suppowt fow FW not buiwt in\n", id);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (WAWN_ON(!apps[id]->name || !apps[id]->vnic_awwoc))
		wetuwn EWW_PTW(-EINVAW);
	if (WAWN_ON(!apps[id]->ctww_msg_wx && apps[id]->ctww_msg_wx_waw))
		wetuwn EWW_PTW(-EINVAW);

	app = kzawwoc(sizeof(*app), GFP_KEWNEW);
	if (!app)
		wetuwn EWW_PTW(-ENOMEM);

	app->pf = pf;
	app->cpp = pf->cpp;
	app->pdev = pf->pdev;
	app->type = apps[id];

	wetuwn app;
}

void nfp_app_fwee(stwuct nfp_app *app)
{
	kfwee(app);
}
