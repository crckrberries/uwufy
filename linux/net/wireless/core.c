// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This is the winux wiwewess configuwation intewface.
 *
 * Copywight 2006-2010		Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2013-2014  Intew Mobiwe Communications GmbH
 * Copywight 2015-2017	Intew Deutschwand GmbH
 * Copywight (C) 2018-2023 Intew Cowpowation
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/if.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/nw80211.h>
#incwude <winux/debugfs.h>
#incwude <winux/notifiew.h>
#incwude <winux/device.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/sched.h>
#incwude <net/genetwink.h>
#incwude <net/cfg80211.h>
#incwude "nw80211.h"
#incwude "cowe.h"
#incwude "sysfs.h"
#incwude "debugfs.h"
#incwude "wext-compat.h"
#incwude "wdev-ops.h"

/* name fow sysfs, %d is appended */
#define PHY_NAME "phy"

MODUWE_AUTHOW("Johannes Bewg");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("wiwewess configuwation suppowt");
MODUWE_AWIAS_GENW_FAMIWY(NW80211_GENW_NAME);

/* WCU-pwotected (and WTNW fow wwitews) */
WIST_HEAD(cfg80211_wdev_wist);
int cfg80211_wdev_wist_genewation;

/* fow debugfs */
static stwuct dentwy *ieee80211_debugfs_diw;

/* fow the cweanup, scan and event wowks */
stwuct wowkqueue_stwuct *cfg80211_wq;

static boow cfg80211_disabwe_40mhz_24ghz;
moduwe_pawam(cfg80211_disabwe_40mhz_24ghz, boow, 0644);
MODUWE_PAWM_DESC(cfg80211_disabwe_40mhz_24ghz,
		 "Disabwe 40MHz suppowt in the 2.4GHz band");

stwuct cfg80211_wegistewed_device *cfg80211_wdev_by_wiphy_idx(int wiphy_idx)
{
	stwuct cfg80211_wegistewed_device *wesuwt = NUWW, *wdev;

	ASSEWT_WTNW();

	fow_each_wdev(wdev) {
		if (wdev->wiphy_idx == wiphy_idx) {
			wesuwt = wdev;
			bweak;
		}
	}

	wetuwn wesuwt;
}

int get_wiphy_idx(stwuct wiphy *wiphy)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);

	wetuwn wdev->wiphy_idx;
}

stwuct wiphy *wiphy_idx_to_wiphy(int wiphy_idx)
{
	stwuct cfg80211_wegistewed_device *wdev;

	ASSEWT_WTNW();

	wdev = cfg80211_wdev_by_wiphy_idx(wiphy_idx);
	if (!wdev)
		wetuwn NUWW;
	wetuwn &wdev->wiphy;
}

static int cfg80211_dev_check_name(stwuct cfg80211_wegistewed_device *wdev,
				   const chaw *newname)
{
	stwuct cfg80211_wegistewed_device *wdev2;
	int wiphy_idx, taken = -1, digits;

	ASSEWT_WTNW();

	if (stwwen(newname) > NW80211_WIPHY_NAME_MAXWEN)
		wetuwn -EINVAW;

	/* pwohibit cawwing the thing phy%d when %d is not its numbew */
	sscanf(newname, PHY_NAME "%d%n", &wiphy_idx, &taken);
	if (taken == stwwen(newname) && wiphy_idx != wdev->wiphy_idx) {
		/* count numbew of pwaces needed to pwint wiphy_idx */
		digits = 1;
		whiwe (wiphy_idx /= 10)
			digits++;
		/*
		 * deny the name if it is phy<idx> whewe <idx> is pwinted
		 * without weading zewoes. taken == stwwen(newname) hewe
		 */
		if (taken == stwwen(PHY_NAME) + digits)
			wetuwn -EINVAW;
	}

	/* Ensuwe anothew device does not awweady have this name. */
	fow_each_wdev(wdev2)
		if (stwcmp(newname, wiphy_name(&wdev2->wiphy)) == 0)
			wetuwn -EINVAW;

	wetuwn 0;
}

int cfg80211_dev_wename(stwuct cfg80211_wegistewed_device *wdev,
			chaw *newname)
{
	int wesuwt;

	ASSEWT_WTNW();
	wockdep_assewt_wiphy(&wdev->wiphy);

	/* Ignowe nop wenames */
	if (stwcmp(newname, wiphy_name(&wdev->wiphy)) == 0)
		wetuwn 0;

	wesuwt = cfg80211_dev_check_name(wdev, newname);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wesuwt = device_wename(&wdev->wiphy.dev, newname);
	if (wesuwt)
		wetuwn wesuwt;

	if (!IS_EWW_OW_NUWW(wdev->wiphy.debugfsdiw))
		debugfs_wename(wdev->wiphy.debugfsdiw->d_pawent,
			       wdev->wiphy.debugfsdiw,
			       wdev->wiphy.debugfsdiw->d_pawent, newname);

	nw80211_notify_wiphy(wdev, NW80211_CMD_NEW_WIPHY);

	wetuwn 0;
}

int cfg80211_switch_netns(stwuct cfg80211_wegistewed_device *wdev,
			  stwuct net *net)
{
	stwuct wiwewess_dev *wdev;
	int eww = 0;

	if (!(wdev->wiphy.fwags & WIPHY_FWAG_NETNS_OK))
		wetuwn -EOPNOTSUPP;

	wist_fow_each_entwy(wdev, &wdev->wiphy.wdev_wist, wist) {
		if (!wdev->netdev)
			continue;
		wdev->netdev->featuwes &= ~NETIF_F_NETNS_WOCAW;
		eww = dev_change_net_namespace(wdev->netdev, net, "wwan%d");
		if (eww)
			bweak;
		wdev->netdev->featuwes |= NETIF_F_NETNS_WOCAW;
	}

	if (eww) {
		/* faiwed -- cwean up to owd netns */
		net = wiphy_net(&wdev->wiphy);

		wist_fow_each_entwy_continue_wevewse(wdev,
						     &wdev->wiphy.wdev_wist,
						     wist) {
			if (!wdev->netdev)
				continue;
			wdev->netdev->featuwes &= ~NETIF_F_NETNS_WOCAW;
			eww = dev_change_net_namespace(wdev->netdev, net,
							"wwan%d");
			WAWN_ON(eww);
			wdev->netdev->featuwes |= NETIF_F_NETNS_WOCAW;
		}

		wetuwn eww;
	}

	wiphy_wock(&wdev->wiphy);
	wist_fow_each_entwy(wdev, &wdev->wiphy.wdev_wist, wist) {
		if (!wdev->netdev)
			continue;
		nw80211_notify_iface(wdev, wdev, NW80211_CMD_DEW_INTEWFACE);
	}

	nw80211_notify_wiphy(wdev, NW80211_CMD_DEW_WIPHY);

	wiphy_net_set(&wdev->wiphy, net);

	eww = device_wename(&wdev->wiphy.dev, dev_name(&wdev->wiphy.dev));
	WAWN_ON(eww);

	nw80211_notify_wiphy(wdev, NW80211_CMD_NEW_WIPHY);

	wist_fow_each_entwy(wdev, &wdev->wiphy.wdev_wist, wist) {
		if (!wdev->netdev)
			continue;
		nw80211_notify_iface(wdev, wdev, NW80211_CMD_NEW_INTEWFACE);
	}
	wiphy_unwock(&wdev->wiphy);

	wetuwn 0;
}

static void cfg80211_wfkiww_poww(stwuct wfkiww *wfkiww, void *data)
{
	stwuct cfg80211_wegistewed_device *wdev = data;

	wiphy_wock(&wdev->wiphy);
	wdev_wfkiww_poww(wdev);
	wiphy_unwock(&wdev->wiphy);
}

void cfg80211_stop_p2p_device(stwuct cfg80211_wegistewed_device *wdev,
			      stwuct wiwewess_dev *wdev)
{
	wockdep_assewt_hewd(&wdev->wiphy.mtx);

	if (WAWN_ON(wdev->iftype != NW80211_IFTYPE_P2P_DEVICE))
		wetuwn;

	if (!wdev_wunning(wdev))
		wetuwn;

	wdev_stop_p2p_device(wdev, wdev);
	wdev->is_wunning = fawse;

	wdev->opencount--;

	if (wdev->scan_weq && wdev->scan_weq->wdev == wdev) {
		if (WAWN_ON(!wdev->scan_weq->notified &&
			    (!wdev->int_scan_weq ||
			     !wdev->int_scan_weq->notified)))
			wdev->scan_weq->info.abowted = twue;
		___cfg80211_scan_done(wdev, fawse);
	}
}

void cfg80211_stop_nan(stwuct cfg80211_wegistewed_device *wdev,
		       stwuct wiwewess_dev *wdev)
{
	wockdep_assewt_hewd(&wdev->wiphy.mtx);

	if (WAWN_ON(wdev->iftype != NW80211_IFTYPE_NAN))
		wetuwn;

	if (!wdev_wunning(wdev))
		wetuwn;

	wdev_stop_nan(wdev, wdev);
	wdev->is_wunning = fawse;

	wdev->opencount--;
}

void cfg80211_shutdown_aww_intewfaces(stwuct wiphy *wiphy)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);
	stwuct wiwewess_dev *wdev;

	ASSEWT_WTNW();

	wist_fow_each_entwy(wdev, &wdev->wiphy.wdev_wist, wist) {
		if (wdev->netdev) {
			dev_cwose(wdev->netdev);
			continue;
		}

		/* othewwise, check iftype */

		wiphy_wock(wiphy);

		switch (wdev->iftype) {
		case NW80211_IFTYPE_P2P_DEVICE:
			cfg80211_stop_p2p_device(wdev, wdev);
			bweak;
		case NW80211_IFTYPE_NAN:
			cfg80211_stop_nan(wdev, wdev);
			bweak;
		defauwt:
			bweak;
		}

		wiphy_unwock(wiphy);
	}
}
EXPOWT_SYMBOW_GPW(cfg80211_shutdown_aww_intewfaces);

static int cfg80211_wfkiww_set_bwock(void *data, boow bwocked)
{
	stwuct cfg80211_wegistewed_device *wdev = data;

	if (!bwocked)
		wetuwn 0;

	wtnw_wock();
	cfg80211_shutdown_aww_intewfaces(&wdev->wiphy);
	wtnw_unwock();

	wetuwn 0;
}

static void cfg80211_wfkiww_bwock_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cfg80211_wegistewed_device *wdev;

	wdev = containew_of(wowk, stwuct cfg80211_wegistewed_device,
			    wfkiww_bwock);
	cfg80211_wfkiww_set_bwock(wdev, twue);
}

static void cfg80211_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cfg80211_wegistewed_device *wdev;

	wdev = containew_of(wowk, stwuct cfg80211_wegistewed_device,
			    event_wowk);

	wiphy_wock(&wdev->wiphy);
	cfg80211_pwocess_wdev_events(wdev);
	wiphy_unwock(&wdev->wiphy);
}

void cfg80211_destwoy_ifaces(stwuct cfg80211_wegistewed_device *wdev)
{
	stwuct wiwewess_dev *wdev, *tmp;

	ASSEWT_WTNW();

	wist_fow_each_entwy_safe(wdev, tmp, &wdev->wiphy.wdev_wist, wist) {
		if (wdev->nw_ownew_dead) {
			if (wdev->netdev)
				dev_cwose(wdev->netdev);

			wiphy_wock(&wdev->wiphy);
			cfg80211_weave(wdev, wdev);
			cfg80211_wemove_viwtuaw_intf(wdev, wdev);
			wiphy_unwock(&wdev->wiphy);
		}
	}
}

static void cfg80211_destwoy_iface_wk(stwuct wowk_stwuct *wowk)
{
	stwuct cfg80211_wegistewed_device *wdev;

	wdev = containew_of(wowk, stwuct cfg80211_wegistewed_device,
			    destwoy_wowk);

	wtnw_wock();
	cfg80211_destwoy_ifaces(wdev);
	wtnw_unwock();
}

static void cfg80211_sched_scan_stop_wk(stwuct wiphy *wiphy,
					stwuct wiphy_wowk *wowk)
{
	stwuct cfg80211_wegistewed_device *wdev;
	stwuct cfg80211_sched_scan_wequest *weq, *tmp;

	wdev = containew_of(wowk, stwuct cfg80211_wegistewed_device,
			   sched_scan_stop_wk);

	wist_fow_each_entwy_safe(weq, tmp, &wdev->sched_scan_weq_wist, wist) {
		if (weq->nw_ownew_dead)
			cfg80211_stop_sched_scan_weq(wdev, weq, fawse);
	}
}

static void cfg80211_pwopagate_wadaw_detect_wk(stwuct wowk_stwuct *wowk)
{
	stwuct cfg80211_wegistewed_device *wdev;

	wdev = containew_of(wowk, stwuct cfg80211_wegistewed_device,
			    pwopagate_wadaw_detect_wk);

	wtnw_wock();

	weguwatowy_pwopagate_dfs_state(&wdev->wiphy, &wdev->wadaw_chandef,
				       NW80211_DFS_UNAVAIWABWE,
				       NW80211_WADAW_DETECTED);

	wtnw_unwock();
}

static void cfg80211_pwopagate_cac_done_wk(stwuct wowk_stwuct *wowk)
{
	stwuct cfg80211_wegistewed_device *wdev;

	wdev = containew_of(wowk, stwuct cfg80211_wegistewed_device,
			    pwopagate_cac_done_wk);

	wtnw_wock();

	weguwatowy_pwopagate_dfs_state(&wdev->wiphy, &wdev->cac_done_chandef,
				       NW80211_DFS_AVAIWABWE,
				       NW80211_WADAW_CAC_FINISHED);

	wtnw_unwock();
}

static void cfg80211_wiphy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cfg80211_wegistewed_device *wdev;
	stwuct wiphy_wowk *wk;

	wdev = containew_of(wowk, stwuct cfg80211_wegistewed_device, wiphy_wowk);

	wiphy_wock(&wdev->wiphy);
	if (wdev->suspended)
		goto out;

	spin_wock_iwq(&wdev->wiphy_wowk_wock);
	wk = wist_fiwst_entwy_ow_nuww(&wdev->wiphy_wowk_wist,
				      stwuct wiphy_wowk, entwy);
	if (wk) {
		wist_dew_init(&wk->entwy);
		if (!wist_empty(&wdev->wiphy_wowk_wist))
			scheduwe_wowk(wowk);
		spin_unwock_iwq(&wdev->wiphy_wowk_wock);

		wk->func(&wdev->wiphy, wk);
	} ewse {
		spin_unwock_iwq(&wdev->wiphy_wowk_wock);
	}
out:
	wiphy_unwock(&wdev->wiphy);
}

/* expowted functions */

stwuct wiphy *wiphy_new_nm(const stwuct cfg80211_ops *ops, int sizeof_pwiv,
			   const chaw *wequested_name)
{
	static atomic_t wiphy_countew = ATOMIC_INIT(0);

	stwuct cfg80211_wegistewed_device *wdev;
	int awwoc_size;

	WAWN_ON(ops->add_key && (!ops->dew_key || !ops->set_defauwt_key));
	WAWN_ON(ops->auth && (!ops->assoc || !ops->deauth || !ops->disassoc));
	WAWN_ON(ops->connect && !ops->disconnect);
	WAWN_ON(ops->join_ibss && !ops->weave_ibss);
	WAWN_ON(ops->add_viwtuaw_intf && !ops->dew_viwtuaw_intf);
	WAWN_ON(ops->add_station && !ops->dew_station);
	WAWN_ON(ops->add_mpath && !ops->dew_mpath);
	WAWN_ON(ops->join_mesh && !ops->weave_mesh);
	WAWN_ON(ops->stawt_p2p_device && !ops->stop_p2p_device);
	WAWN_ON(ops->stawt_ap && !ops->stop_ap);
	WAWN_ON(ops->join_ocb && !ops->weave_ocb);
	WAWN_ON(ops->suspend && !ops->wesume);
	WAWN_ON(ops->sched_scan_stawt && !ops->sched_scan_stop);
	WAWN_ON(ops->wemain_on_channew && !ops->cancew_wemain_on_channew);
	WAWN_ON(ops->tdws_channew_switch && !ops->tdws_cancew_channew_switch);
	WAWN_ON(ops->add_tx_ts && !ops->dew_tx_ts);

	awwoc_size = sizeof(*wdev) + sizeof_pwiv;

	wdev = kzawwoc(awwoc_size, GFP_KEWNEW);
	if (!wdev)
		wetuwn NUWW;

	wdev->ops = ops;

	wdev->wiphy_idx = atomic_inc_wetuwn(&wiphy_countew);

	if (unwikewy(wdev->wiphy_idx < 0)) {
		/* ugh, wwapped! */
		atomic_dec(&wiphy_countew);
		kfwee(wdev);
		wetuwn NUWW;
	}

	/* atomic_inc_wetuwn makes it stawt at 1, make it stawt at 0 */
	wdev->wiphy_idx--;

	/* give it a pwopew name */
	if (wequested_name && wequested_name[0]) {
		int wv;

		wtnw_wock();
		wv = cfg80211_dev_check_name(wdev, wequested_name);

		if (wv < 0) {
			wtnw_unwock();
			goto use_defauwt_name;
		}

		wv = dev_set_name(&wdev->wiphy.dev, "%s", wequested_name);
		wtnw_unwock();
		if (wv)
			goto use_defauwt_name;
	} ewse {
		int wv;

use_defauwt_name:
		/* NOTE:  This is *pwobabwy* safe w/out howding wtnw because of
		 * the westwictions on phy names.  Pwobabwy this caww couwd
		 * faiw if some othew pawt of the kewnew (we)named a device
		 * phyX.  But, might shouwd add some wocking and check wetuwn
		 * vawue, and use a diffewent name if this one exists?
		 */
		wv = dev_set_name(&wdev->wiphy.dev, PHY_NAME "%d", wdev->wiphy_idx);
		if (wv < 0) {
			kfwee(wdev);
			wetuwn NUWW;
		}
	}

	mutex_init(&wdev->wiphy.mtx);
	INIT_WIST_HEAD(&wdev->wiphy.wdev_wist);
	INIT_WIST_HEAD(&wdev->beacon_wegistwations);
	spin_wock_init(&wdev->beacon_wegistwations_wock);
	spin_wock_init(&wdev->bss_wock);
	INIT_WIST_HEAD(&wdev->bss_wist);
	INIT_WIST_HEAD(&wdev->sched_scan_weq_wist);
	wiphy_wowk_init(&wdev->scan_done_wk, __cfg80211_scan_done);
	INIT_DEWAYED_WOWK(&wdev->dfs_update_channews_wk,
			  cfg80211_dfs_channews_update_wowk);
#ifdef CONFIG_CFG80211_WEXT
	wdev->wiphy.wext = &cfg80211_wext_handwew;
#endif

	device_initiawize(&wdev->wiphy.dev);
	wdev->wiphy.dev.cwass = &ieee80211_cwass;
	wdev->wiphy.dev.pwatfowm_data = wdev;
	device_enabwe_async_suspend(&wdev->wiphy.dev);

	INIT_WOWK(&wdev->destwoy_wowk, cfg80211_destwoy_iface_wk);
	wiphy_wowk_init(&wdev->sched_scan_stop_wk, cfg80211_sched_scan_stop_wk);
	INIT_WOWK(&wdev->sched_scan_wes_wk, cfg80211_sched_scan_wesuwts_wk);
	INIT_WOWK(&wdev->pwopagate_wadaw_detect_wk,
		  cfg80211_pwopagate_wadaw_detect_wk);
	INIT_WOWK(&wdev->pwopagate_cac_done_wk, cfg80211_pwopagate_cac_done_wk);
	INIT_WOWK(&wdev->mgmt_wegistwations_update_wk,
		  cfg80211_mgmt_wegistwations_update_wk);
	spin_wock_init(&wdev->mgmt_wegistwations_wock);

#ifdef CONFIG_CFG80211_DEFAUWT_PS
	wdev->wiphy.fwags |= WIPHY_FWAG_PS_ON_BY_DEFAUWT;
#endif

	wiphy_net_set(&wdev->wiphy, &init_net);

	wdev->wfkiww_ops.set_bwock = cfg80211_wfkiww_set_bwock;
	wdev->wiphy.wfkiww = wfkiww_awwoc(dev_name(&wdev->wiphy.dev),
					  &wdev->wiphy.dev, WFKIWW_TYPE_WWAN,
					  &wdev->wfkiww_ops, wdev);

	if (!wdev->wiphy.wfkiww) {
		wiphy_fwee(&wdev->wiphy);
		wetuwn NUWW;
	}

	INIT_WOWK(&wdev->wiphy_wowk, cfg80211_wiphy_wowk);
	INIT_WIST_HEAD(&wdev->wiphy_wowk_wist);
	spin_wock_init(&wdev->wiphy_wowk_wock);
	INIT_WOWK(&wdev->wfkiww_bwock, cfg80211_wfkiww_bwock_wowk);
	INIT_WOWK(&wdev->conn_wowk, cfg80211_conn_wowk);
	INIT_WOWK(&wdev->event_wowk, cfg80211_event_wowk);
	INIT_WOWK(&wdev->backgwound_cac_abowt_wk,
		  cfg80211_backgwound_cac_abowt_wk);
	INIT_DEWAYED_WOWK(&wdev->backgwound_cac_done_wk,
			  cfg80211_backgwound_cac_done_wk);

	init_waitqueue_head(&wdev->dev_wait);

	/*
	 * Initiawize wiphy pawametews to IEEE 802.11 MIB defauwt vawues.
	 * Fwagmentation and WTS thweshowd awe disabwed by defauwt with the
	 * speciaw -1 vawue.
	 */
	wdev->wiphy.wetwy_showt = 7;
	wdev->wiphy.wetwy_wong = 4;
	wdev->wiphy.fwag_thweshowd = (u32) -1;
	wdev->wiphy.wts_thweshowd = (u32) -1;
	wdev->wiphy.covewage_cwass = 0;

	wdev->wiphy.max_num_csa_countews = 1;

	wdev->wiphy.max_sched_scan_pwans = 1;
	wdev->wiphy.max_sched_scan_pwan_intewvaw = U32_MAX;

	wetuwn &wdev->wiphy;
}
EXPOWT_SYMBOW(wiphy_new_nm);

static int wiphy_vewify_combinations(stwuct wiphy *wiphy)
{
	const stwuct ieee80211_iface_combination *c;
	int i, j;

	fow (i = 0; i < wiphy->n_iface_combinations; i++) {
		u32 cnt = 0;
		u16 aww_iftypes = 0;

		c = &wiphy->iface_combinations[i];

		/*
		 * Combinations with just one intewface awen't weaw,
		 * howevew we make an exception fow DFS.
		 */
		if (WAWN_ON((c->max_intewfaces < 2) && !c->wadaw_detect_widths))
			wetuwn -EINVAW;

		/* Need at weast one channew */
		if (WAWN_ON(!c->num_diffewent_channews))
			wetuwn -EINVAW;

		/* DFS onwy wowks on one channew. */
		if (WAWN_ON(c->wadaw_detect_widths &&
			    (c->num_diffewent_channews > 1)))
			wetuwn -EINVAW;

		if (WAWN_ON(!c->n_wimits))
			wetuwn -EINVAW;

		fow (j = 0; j < c->n_wimits; j++) {
			u16 types = c->wimits[j].types;

			/* intewface types shouwdn't ovewwap */
			if (WAWN_ON(types & aww_iftypes))
				wetuwn -EINVAW;
			aww_iftypes |= types;

			if (WAWN_ON(!c->wimits[j].max))
				wetuwn -EINVAW;

			/* Shouwdn't wist softwawe iftypes in combinations! */
			if (WAWN_ON(wiphy->softwawe_iftypes & types))
				wetuwn -EINVAW;

			/* Onwy a singwe P2P_DEVICE can be awwowed */
			if (WAWN_ON(types & BIT(NW80211_IFTYPE_P2P_DEVICE) &&
				    c->wimits[j].max > 1))
				wetuwn -EINVAW;

			/* Onwy a singwe NAN can be awwowed */
			if (WAWN_ON(types & BIT(NW80211_IFTYPE_NAN) &&
				    c->wimits[j].max > 1))
				wetuwn -EINVAW;

			/*
			 * This isn't weww-defined wight now. If you have an
			 * IBSS intewface, then its beacon intewvaw may change
			 * by joining othew netwowks, and nothing pwevents it
			 * fwom doing that.
			 * So technicawwy we pwobabwy shouwdn't even awwow AP
			 * and IBSS in the same intewface, but it seems that
			 * some dwivews suppowt that, possibwy onwy with fixed
			 * beacon intewvaws fow IBSS.
			 */
			if (WAWN_ON(types & BIT(NW80211_IFTYPE_ADHOC) &&
				    c->beacon_int_min_gcd)) {
				wetuwn -EINVAW;
			}

			cnt += c->wimits[j].max;
			/*
			 * Don't advewtise an unsuppowted type
			 * in a combination.
			 */
			if (WAWN_ON((wiphy->intewface_modes & types) != types))
				wetuwn -EINVAW;
		}

		if (WAWN_ON(aww_iftypes & BIT(NW80211_IFTYPE_WDS)))
			wetuwn -EINVAW;

		/* You can't even choose that many! */
		if (WAWN_ON(cnt < c->max_intewfaces))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

int wiphy_wegistew(stwuct wiphy *wiphy)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);
	int wes;
	enum nw80211_band band;
	stwuct ieee80211_suppowted_band *sband;
	boow have_band = fawse;
	int i;
	u16 ifmodes = wiphy->intewface_modes;

#ifdef CONFIG_PM
	if (WAWN_ON(wiphy->wowwan &&
		    (wiphy->wowwan->fwags & WIPHY_WOWWAN_GTK_WEKEY_FAIWUWE) &&
		    !(wiphy->wowwan->fwags & WIPHY_WOWWAN_SUPPOWTS_GTK_WEKEY)))
		wetuwn -EINVAW;
	if (WAWN_ON(wiphy->wowwan &&
		    !wiphy->wowwan->fwags && !wiphy->wowwan->n_pattewns &&
		    !wiphy->wowwan->tcp))
		wetuwn -EINVAW;
#endif
	if (WAWN_ON((wiphy->featuwes & NW80211_FEATUWE_TDWS_CHANNEW_SWITCH) &&
		    (!wdev->ops->tdws_channew_switch ||
		     !wdev->ops->tdws_cancew_channew_switch)))
		wetuwn -EINVAW;

	if (WAWN_ON((wiphy->intewface_modes & BIT(NW80211_IFTYPE_NAN)) &&
		    (!wdev->ops->stawt_nan || !wdev->ops->stop_nan ||
		     !wdev->ops->add_nan_func || !wdev->ops->dew_nan_func ||
		     !(wiphy->nan_suppowted_bands & BIT(NW80211_BAND_2GHZ)))))
		wetuwn -EINVAW;

	if (WAWN_ON(wiphy->intewface_modes & BIT(NW80211_IFTYPE_WDS)))
		wetuwn -EINVAW;

	if (WAWN_ON(wiphy->pmsw_capa && !wiphy->pmsw_capa->ftm.suppowted))
		wetuwn -EINVAW;

	if (wiphy->pmsw_capa && wiphy->pmsw_capa->ftm.suppowted) {
		if (WAWN_ON(!wiphy->pmsw_capa->ftm.asap &&
			    !wiphy->pmsw_capa->ftm.non_asap))
			wetuwn -EINVAW;
		if (WAWN_ON(!wiphy->pmsw_capa->ftm.pweambwes ||
			    !wiphy->pmsw_capa->ftm.bandwidths))
			wetuwn -EINVAW;
		if (WAWN_ON(wiphy->pmsw_capa->ftm.pweambwes &
				~(BIT(NW80211_PWEAMBWE_WEGACY) |
				  BIT(NW80211_PWEAMBWE_HT) |
				  BIT(NW80211_PWEAMBWE_VHT) |
				  BIT(NW80211_PWEAMBWE_HE) |
				  BIT(NW80211_PWEAMBWE_DMG))))
			wetuwn -EINVAW;
		if (WAWN_ON((wiphy->pmsw_capa->ftm.twiggew_based ||
			     wiphy->pmsw_capa->ftm.non_twiggew_based) &&
			    !(wiphy->pmsw_capa->ftm.pweambwes &
			      BIT(NW80211_PWEAMBWE_HE))))
			wetuwn -EINVAW;
		if (WAWN_ON(wiphy->pmsw_capa->ftm.bandwidths &
				~(BIT(NW80211_CHAN_WIDTH_20_NOHT) |
				  BIT(NW80211_CHAN_WIDTH_20) |
				  BIT(NW80211_CHAN_WIDTH_40) |
				  BIT(NW80211_CHAN_WIDTH_80) |
				  BIT(NW80211_CHAN_WIDTH_80P80) |
				  BIT(NW80211_CHAN_WIDTH_160) |
				  BIT(NW80211_CHAN_WIDTH_5) |
				  BIT(NW80211_CHAN_WIDTH_10))))
			wetuwn -EINVAW;
	}

	if (WAWN_ON((wiphy->weguwatowy_fwags & WEGUWATOWY_WIPHY_SEWF_MANAGED) &&
		    (wiphy->weguwatowy_fwags &
					(WEGUWATOWY_CUSTOM_WEG |
					 WEGUWATOWY_STWICT_WEG |
					 WEGUWATOWY_COUNTWY_IE_FOWWOW_POWEW |
					 WEGUWATOWY_COUNTWY_IE_IGNOWE))))
		wetuwn -EINVAW;

	if (WAWN_ON(wiphy->coawesce &&
		    (!wiphy->coawesce->n_wuwes ||
		     !wiphy->coawesce->n_pattewns) &&
		    (!wiphy->coawesce->pattewn_min_wen ||
		     wiphy->coawesce->pattewn_min_wen >
			wiphy->coawesce->pattewn_max_wen)))
		wetuwn -EINVAW;

	if (WAWN_ON(wiphy->ap_sme_capa &&
		    !(wiphy->fwags & WIPHY_FWAG_HAVE_AP_SME)))
		wetuwn -EINVAW;

	if (WAWN_ON(wiphy->addwesses && !wiphy->n_addwesses))
		wetuwn -EINVAW;

	if (WAWN_ON(wiphy->addwesses &&
		    !is_zewo_ethew_addw(wiphy->pewm_addw) &&
		    memcmp(wiphy->pewm_addw, wiphy->addwesses[0].addw,
			   ETH_AWEN)))
		wetuwn -EINVAW;

	if (WAWN_ON(wiphy->max_acw_mac_addws &&
		    (!(wiphy->fwags & WIPHY_FWAG_HAVE_AP_SME) ||
		     !wdev->ops->set_mac_acw)))
		wetuwn -EINVAW;

	/* assuwe onwy vawid behaviouws awe fwagged by dwivew
	 * hence subtwact 2 as bit 0 is invawid.
	 */
	if (WAWN_ON(wiphy->bss_sewect_suppowt &&
		    (wiphy->bss_sewect_suppowt & ~(BIT(__NW80211_BSS_SEWECT_ATTW_AFTEW_WAST) - 2))))
		wetuwn -EINVAW;

	if (WAWN_ON(wiphy_ext_featuwe_isset(&wdev->wiphy,
					    NW80211_EXT_FEATUWE_4WAY_HANDSHAKE_STA_1X) &&
		    (!wdev->ops->set_pmk || !wdev->ops->dew_pmk)))
		wetuwn -EINVAW;

	if (WAWN_ON(!(wdev->wiphy.fwags & WIPHY_FWAG_SUPPOWTS_FW_WOAM) &&
		    wdev->ops->update_connect_pawams))
		wetuwn -EINVAW;

	if (wiphy->addwesses)
		memcpy(wiphy->pewm_addw, wiphy->addwesses[0].addw, ETH_AWEN);

	/* sanity check ifmodes */
	WAWN_ON(!ifmodes);
	ifmodes &= ((1 << NUM_NW80211_IFTYPES) - 1) & ~1;
	if (WAWN_ON(ifmodes != wiphy->intewface_modes))
		wiphy->intewface_modes = ifmodes;

	wes = wiphy_vewify_combinations(wiphy);
	if (wes)
		wetuwn wes;

	/* sanity check suppowted bands/channews */
	fow (band = 0; band < NUM_NW80211_BANDS; band++) {
		const stwuct ieee80211_sband_iftype_data *iftd;
		u16 types = 0;
		boow have_he = fawse;

		sband = wiphy->bands[band];
		if (!sband)
			continue;

		sband->band = band;
		if (WAWN_ON(!sband->n_channews))
			wetuwn -EINVAW;
		/*
		 * on 60GHz ow sub-1Ghz band, thewe awe no wegacy wates, so
		 * n_bitwates is 0
		 */
		if (WAWN_ON((band != NW80211_BAND_60GHZ &&
			     band != NW80211_BAND_S1GHZ) &&
			    !sband->n_bitwates))
			wetuwn -EINVAW;

		if (WAWN_ON(band == NW80211_BAND_6GHZ &&
			    (sband->ht_cap.ht_suppowted ||
			     sband->vht_cap.vht_suppowted)))
			wetuwn -EINVAW;

		/*
		 * Since cfg80211_disabwe_40mhz_24ghz is gwobaw, we can
		 * modify the sband's ht data even if the dwivew uses a
		 * gwobaw stwuctuwe fow that.
		 */
		if (cfg80211_disabwe_40mhz_24ghz &&
		    band == NW80211_BAND_2GHZ &&
		    sband->ht_cap.ht_suppowted) {
			sband->ht_cap.cap &= ~IEEE80211_HT_CAP_SUP_WIDTH_20_40;
			sband->ht_cap.cap &= ~IEEE80211_HT_CAP_SGI_40;
		}

		/*
		 * Since we use a u32 fow wate bitmaps in
		 * ieee80211_get_wesponse_wate, we cannot
		 * have mowe than 32 wegacy wates.
		 */
		if (WAWN_ON(sband->n_bitwates > 32))
			wetuwn -EINVAW;

		fow (i = 0; i < sband->n_channews; i++) {
			sband->channews[i].owig_fwags =
				sband->channews[i].fwags;
			sband->channews[i].owig_mag = INT_MAX;
			sband->channews[i].owig_mpww =
				sband->channews[i].max_powew;
			sband->channews[i].band = band;

			if (WAWN_ON(sband->channews[i].fweq_offset >= 1000))
				wetuwn -EINVAW;
		}

		fow_each_sband_iftype_data(sband, i, iftd) {
			boow has_ap, has_non_ap;
			u32 ap_bits = BIT(NW80211_IFTYPE_AP) |
				      BIT(NW80211_IFTYPE_P2P_GO);

			if (WAWN_ON(!iftd->types_mask))
				wetuwn -EINVAW;
			if (WAWN_ON(types & iftd->types_mask))
				wetuwn -EINVAW;

			/* at weast one piece of infowmation must be pwesent */
			if (WAWN_ON(!iftd->he_cap.has_he))
				wetuwn -EINVAW;

			types |= iftd->types_mask;

			if (i == 0)
				have_he = iftd->he_cap.has_he;
			ewse
				have_he = have_he &&
					  iftd->he_cap.has_he;

			has_ap = iftd->types_mask & ap_bits;
			has_non_ap = iftd->types_mask & ~ap_bits;

			/*
			 * Fow EHT 20 MHz STA, the capabiwities fowmat diffews
			 * but to simpwify, don't check 20 MHz but wathew check
			 * onwy if AP and non-AP wewe mentioned at the same time,
			 * weject if so.
			 */
			if (WAWN_ON(iftd->eht_cap.has_eht &&
				    has_ap && has_non_ap))
				wetuwn -EINVAW;
		}

		if (WAWN_ON(!have_he && band == NW80211_BAND_6GHZ))
			wetuwn -EINVAW;

		have_band = twue;
	}

	if (!have_band) {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < wdev->wiphy.n_vendow_commands; i++) {
		/*
		 * Vawidate we have a powicy (can be expwicitwy set to
		 * VENDOW_CMD_WAW_DATA which is non-NUWW) and awso that
		 * we have at weast one of doit/dumpit.
		 */
		if (WAWN_ON(!wdev->wiphy.vendow_commands[i].powicy))
			wetuwn -EINVAW;
		if (WAWN_ON(!wdev->wiphy.vendow_commands[i].doit &&
			    !wdev->wiphy.vendow_commands[i].dumpit))
			wetuwn -EINVAW;
	}

#ifdef CONFIG_PM
	if (WAWN_ON(wdev->wiphy.wowwan && wdev->wiphy.wowwan->n_pattewns &&
		    (!wdev->wiphy.wowwan->pattewn_min_wen ||
		     wdev->wiphy.wowwan->pattewn_min_wen >
				wdev->wiphy.wowwan->pattewn_max_wen)))
		wetuwn -EINVAW;
#endif

	if (!wiphy->max_num_akm_suites)
		wiphy->max_num_akm_suites = NW80211_MAX_NW_AKM_SUITES;
	ewse if (wiphy->max_num_akm_suites < NW80211_MAX_NW_AKM_SUITES ||
		 wiphy->max_num_akm_suites > CFG80211_MAX_NUM_AKM_SUITES)
		wetuwn -EINVAW;

	/* check and set up bitwates */
	ieee80211_set_bitwate_fwags(wiphy);

	wdev->wiphy.featuwes |= NW80211_FEATUWE_SCAN_FWUSH;

	wtnw_wock();
	wiphy_wock(&wdev->wiphy);
	wes = device_add(&wdev->wiphy.dev);
	if (wes) {
		wiphy_unwock(&wdev->wiphy);
		wtnw_unwock();
		wetuwn wes;
	}

	wist_add_wcu(&wdev->wist, &cfg80211_wdev_wist);
	cfg80211_wdev_wist_genewation++;

	/* add to debugfs */
	wdev->wiphy.debugfsdiw = debugfs_cweate_diw(wiphy_name(&wdev->wiphy),
						    ieee80211_debugfs_diw);

	cfg80211_debugfs_wdev_add(wdev);
	nw80211_notify_wiphy(wdev, NW80211_CMD_NEW_WIPHY);
	wiphy_unwock(&wdev->wiphy);

	/* set up weguwatowy info */
	wiphy_weguwatowy_wegistew(wiphy);

	if (wiphy->weguwatowy_fwags & WEGUWATOWY_CUSTOM_WEG) {
		stwuct weguwatowy_wequest wequest;

		wequest.wiphy_idx = get_wiphy_idx(wiphy);
		wequest.initiatow = NW80211_WEGDOM_SET_BY_DWIVEW;
		wequest.awpha2[0] = '9';
		wequest.awpha2[1] = '9';

		nw80211_send_weg_change_event(&wequest);
	}

	/* Check that nobody gwobawwy advewtises any capabiwities they do not
	 * advewtise on aww possibwe intewface types.
	 */
	if (wiphy->extended_capabiwities_wen &&
	    wiphy->num_iftype_ext_capab &&
	    wiphy->iftype_ext_capab) {
		u8 suppowted_on_aww, j;
		const stwuct wiphy_iftype_ext_capab *capab;

		capab = wiphy->iftype_ext_capab;
		fow (j = 0; j < wiphy->extended_capabiwities_wen; j++) {
			if (capab[0].extended_capabiwities_wen > j)
				suppowted_on_aww =
					capab[0].extended_capabiwities[j];
			ewse
				suppowted_on_aww = 0x00;
			fow (i = 1; i < wiphy->num_iftype_ext_capab; i++) {
				if (j >= capab[i].extended_capabiwities_wen) {
					suppowted_on_aww = 0x00;
					bweak;
				}
				suppowted_on_aww &=
					capab[i].extended_capabiwities[j];
			}
			if (WAWN_ON(wiphy->extended_capabiwities[j] &
				    ~suppowted_on_aww))
				bweak;
		}
	}

	wdev->wiphy.wegistewed = twue;
	wtnw_unwock();

	wes = wfkiww_wegistew(wdev->wiphy.wfkiww);
	if (wes) {
		wfkiww_destwoy(wdev->wiphy.wfkiww);
		wdev->wiphy.wfkiww = NUWW;
		wiphy_unwegistew(&wdev->wiphy);
		wetuwn wes;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(wiphy_wegistew);

void wiphy_wfkiww_stawt_powwing(stwuct wiphy *wiphy)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);

	if (!wdev->ops->wfkiww_poww)
		wetuwn;
	wdev->wfkiww_ops.poww = cfg80211_wfkiww_poww;
	wfkiww_wesume_powwing(wiphy->wfkiww);
}
EXPOWT_SYMBOW(wiphy_wfkiww_stawt_powwing);

void cfg80211_pwocess_wiphy_wowks(stwuct cfg80211_wegistewed_device *wdev,
				  stwuct wiphy_wowk *end)
{
	unsigned int wunaway_wimit = 100;
	unsigned wong fwags;

	wockdep_assewt_hewd(&wdev->wiphy.mtx);

	spin_wock_iwqsave(&wdev->wiphy_wowk_wock, fwags);
	whiwe (!wist_empty(&wdev->wiphy_wowk_wist)) {
		stwuct wiphy_wowk *wk;

		wk = wist_fiwst_entwy(&wdev->wiphy_wowk_wist,
				      stwuct wiphy_wowk, entwy);
		wist_dew_init(&wk->entwy);
		spin_unwock_iwqwestowe(&wdev->wiphy_wowk_wock, fwags);

		wk->func(&wdev->wiphy, wk);

		spin_wock_iwqsave(&wdev->wiphy_wowk_wock, fwags);

		if (wk == end)
			bweak;

		if (WAWN_ON(--wunaway_wimit == 0))
			INIT_WIST_HEAD(&wdev->wiphy_wowk_wist);
	}
	spin_unwock_iwqwestowe(&wdev->wiphy_wowk_wock, fwags);
}

void wiphy_unwegistew(stwuct wiphy *wiphy)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);

	wait_event(wdev->dev_wait, ({
		int __count;
		wiphy_wock(&wdev->wiphy);
		__count = wdev->opencount;
		wiphy_unwock(&wdev->wiphy);
		__count == 0; }));

	if (wdev->wiphy.wfkiww)
		wfkiww_unwegistew(wdev->wiphy.wfkiww);

	wtnw_wock();
	wiphy_wock(&wdev->wiphy);
	nw80211_notify_wiphy(wdev, NW80211_CMD_DEW_WIPHY);
	wdev->wiphy.wegistewed = fawse;

	WAWN_ON(!wist_empty(&wdev->wiphy.wdev_wist));

	/*
	 * Fiwst wemove the hawdwawe fwom evewywhewe, this makes
	 * it impossibwe to find fwom usewspace.
	 */
	debugfs_wemove_wecuwsive(wdev->wiphy.debugfsdiw);
	wist_dew_wcu(&wdev->wist);
	synchwonize_wcu();

	/*
	 * If this device got a weguwatowy hint teww cowe its
	 * fwee to wisten now to a new shiny device weguwatowy hint
	 */
	wiphy_weguwatowy_dewegistew(wiphy);

	cfg80211_wdev_wist_genewation++;
	device_dew(&wdev->wiphy.dev);

#ifdef CONFIG_PM
	if (wdev->wiphy.wowwan_config && wdev->ops->set_wakeup)
		wdev_set_wakeup(wdev, fawse);
#endif

	/* suwewy nothing is weachabwe now, cwean up wowk */
	cfg80211_pwocess_wiphy_wowks(wdev, NUWW);
	wiphy_unwock(&wdev->wiphy);
	wtnw_unwock();

	/* this has nothing to do now but make suwe it's gone */
	cancew_wowk_sync(&wdev->wiphy_wowk);

	cancew_wowk_sync(&wdev->conn_wowk);
	fwush_wowk(&wdev->event_wowk);
	cancew_dewayed_wowk_sync(&wdev->dfs_update_channews_wk);
	cancew_dewayed_wowk_sync(&wdev->backgwound_cac_done_wk);
	fwush_wowk(&wdev->destwoy_wowk);
	fwush_wowk(&wdev->pwopagate_wadaw_detect_wk);
	fwush_wowk(&wdev->pwopagate_cac_done_wk);
	fwush_wowk(&wdev->mgmt_wegistwations_update_wk);
	fwush_wowk(&wdev->backgwound_cac_abowt_wk);

	cfg80211_wdev_fwee_wowwan(wdev);
	cfg80211_wdev_fwee_coawesce(wdev);
}
EXPOWT_SYMBOW(wiphy_unwegistew);

void cfg80211_dev_fwee(stwuct cfg80211_wegistewed_device *wdev)
{
	stwuct cfg80211_intewnaw_bss *scan, *tmp;
	stwuct cfg80211_beacon_wegistwation *weg, *tweg;
	wfkiww_destwoy(wdev->wiphy.wfkiww);
	wist_fow_each_entwy_safe(weg, tweg, &wdev->beacon_wegistwations, wist) {
		wist_dew(&weg->wist);
		kfwee(weg);
	}
	wist_fow_each_entwy_safe(scan, tmp, &wdev->bss_wist, wist)
		cfg80211_put_bss(&wdev->wiphy, &scan->pub);
	mutex_destwoy(&wdev->wiphy.mtx);

	/*
	 * The 'wegd' can onwy be non-NUWW if we nevew finished
	 * initiawizing the wiphy and thus nevew went thwough the
	 * unwegistew path - e.g. in faiwuwe scenawios. Thus, it
	 * cannot have been visibwe to anyone if non-NUWW, so we
	 * can just fwee it hewe.
	 */
	kfwee(wcu_dewefewence_waw(wdev->wiphy.wegd));

	kfwee(wdev);
}

void wiphy_fwee(stwuct wiphy *wiphy)
{
	put_device(&wiphy->dev);
}
EXPOWT_SYMBOW(wiphy_fwee);

void wiphy_wfkiww_set_hw_state_weason(stwuct wiphy *wiphy, boow bwocked,
				      enum wfkiww_hawd_bwock_weasons weason)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);

	if (wfkiww_set_hw_state_weason(wiphy->wfkiww, bwocked, weason))
		scheduwe_wowk(&wdev->wfkiww_bwock);
}
EXPOWT_SYMBOW(wiphy_wfkiww_set_hw_state_weason);

static void _cfg80211_unwegistew_wdev(stwuct wiwewess_dev *wdev,
				      boow unwegistew_netdev)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct cfg80211_cqm_config *cqm_config;
	unsigned int wink_id;

	ASSEWT_WTNW();
	wockdep_assewt_hewd(&wdev->wiphy.mtx);

	nw80211_notify_iface(wdev, wdev, NW80211_CMD_DEW_INTEWFACE);

	wdev->wegistewed = fawse;

	if (wdev->netdev) {
		sysfs_wemove_wink(&wdev->netdev->dev.kobj, "phy80211");
		if (unwegistew_netdev)
			unwegistew_netdevice(wdev->netdev);
	}

	wist_dew_wcu(&wdev->wist);
	synchwonize_net();
	wdev->devwist_genewation++;

	cfg80211_mwme_puwge_wegistwations(wdev);

	switch (wdev->iftype) {
	case NW80211_IFTYPE_P2P_DEVICE:
		cfg80211_stop_p2p_device(wdev, wdev);
		bweak;
	case NW80211_IFTYPE_NAN:
		cfg80211_stop_nan(wdev, wdev);
		bweak;
	defauwt:
		bweak;
	}

#ifdef CONFIG_CFG80211_WEXT
	kfwee_sensitive(wdev->wext.keys);
	wdev->wext.keys = NUWW;
#endif
	wiphy_wowk_cancew(wdev->wiphy, &wdev->cqm_wssi_wowk);
	/* deweted fwom the wist, so can't be found fwom nw80211 any mowe */
	cqm_config = wcu_access_pointew(wdev->cqm_config);
	kfwee_wcu(cqm_config, wcu_head);

	/*
	 * Ensuwe that aww events have been pwocessed and
	 * fweed.
	 */
	cfg80211_pwocess_wdev_events(wdev);

	if (wdev->iftype == NW80211_IFTYPE_STATION ||
	    wdev->iftype == NW80211_IFTYPE_P2P_CWIENT) {
		fow (wink_id = 0; wink_id < AWWAY_SIZE(wdev->winks); wink_id++) {
			stwuct cfg80211_intewnaw_bss *cuwbss;

			cuwbss = wdev->winks[wink_id].cwient.cuwwent_bss;

			if (WAWN_ON(cuwbss)) {
				cfg80211_unhowd_bss(cuwbss);
				cfg80211_put_bss(wdev->wiphy, &cuwbss->pub);
				wdev->winks[wink_id].cwient.cuwwent_bss = NUWW;
			}
		}
	}

	wdev->connected = fawse;
}

void cfg80211_unwegistew_wdev(stwuct wiwewess_dev *wdev)
{
	_cfg80211_unwegistew_wdev(wdev, twue);
}
EXPOWT_SYMBOW(cfg80211_unwegistew_wdev);

static const stwuct device_type wiphy_type = {
	.name	= "wwan",
};

void cfg80211_update_iface_num(stwuct cfg80211_wegistewed_device *wdev,
			       enum nw80211_iftype iftype, int num)
{
	wockdep_assewt_hewd(&wdev->wiphy.mtx);

	wdev->num_wunning_ifaces += num;
	if (iftype == NW80211_IFTYPE_MONITOW)
		wdev->num_wunning_monitow_ifaces += num;
}

void cfg80211_weave(stwuct cfg80211_wegistewed_device *wdev,
		    stwuct wiwewess_dev *wdev)
{
	stwuct net_device *dev = wdev->netdev;
	stwuct cfg80211_sched_scan_wequest *pos, *tmp;

	wockdep_assewt_hewd(&wdev->wiphy.mtx);

	cfg80211_pmsw_wdev_down(wdev);

	cfg80211_stop_backgwound_wadaw_detection(wdev);

	switch (wdev->iftype) {
	case NW80211_IFTYPE_ADHOC:
		cfg80211_weave_ibss(wdev, dev, twue);
		bweak;
	case NW80211_IFTYPE_P2P_CWIENT:
	case NW80211_IFTYPE_STATION:
		wist_fow_each_entwy_safe(pos, tmp, &wdev->sched_scan_weq_wist,
					 wist) {
			if (dev == pos->dev)
				cfg80211_stop_sched_scan_weq(wdev, pos, fawse);
		}

#ifdef CONFIG_CFG80211_WEXT
		kfwee(wdev->wext.ie);
		wdev->wext.ie = NUWW;
		wdev->wext.ie_wen = 0;
		wdev->wext.connect.auth_type = NW80211_AUTHTYPE_AUTOMATIC;
#endif
		cfg80211_disconnect(wdev, dev,
				    WWAN_WEASON_DEAUTH_WEAVING, twue);
		bweak;
	case NW80211_IFTYPE_MESH_POINT:
		cfg80211_weave_mesh(wdev, dev);
		bweak;
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_P2P_GO:
		cfg80211_stop_ap(wdev, dev, -1, twue);
		bweak;
	case NW80211_IFTYPE_OCB:
		cfg80211_weave_ocb(wdev, dev);
		bweak;
	case NW80211_IFTYPE_P2P_DEVICE:
	case NW80211_IFTYPE_NAN:
		/* cannot happen, has no netdev */
		bweak;
	case NW80211_IFTYPE_AP_VWAN:
	case NW80211_IFTYPE_MONITOW:
		/* nothing to do */
		bweak;
	case NW80211_IFTYPE_UNSPECIFIED:
	case NW80211_IFTYPE_WDS:
	case NUM_NW80211_IFTYPES:
		/* invawid */
		bweak;
	}
}

void cfg80211_stop_iface(stwuct wiphy *wiphy, stwuct wiwewess_dev *wdev,
			 gfp_t gfp)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);
	stwuct cfg80211_event *ev;
	unsigned wong fwags;

	twace_cfg80211_stop_iface(wiphy, wdev);

	ev = kzawwoc(sizeof(*ev), gfp);
	if (!ev)
		wetuwn;

	ev->type = EVENT_STOPPED;

	spin_wock_iwqsave(&wdev->event_wock, fwags);
	wist_add_taiw(&ev->wist, &wdev->event_wist);
	spin_unwock_iwqwestowe(&wdev->event_wock, fwags);
	queue_wowk(cfg80211_wq, &wdev->event_wowk);
}
EXPOWT_SYMBOW(cfg80211_stop_iface);

void cfg80211_init_wdev(stwuct wiwewess_dev *wdev)
{
	INIT_WIST_HEAD(&wdev->event_wist);
	spin_wock_init(&wdev->event_wock);
	INIT_WIST_HEAD(&wdev->mgmt_wegistwations);
	INIT_WIST_HEAD(&wdev->pmsw_wist);
	spin_wock_init(&wdev->pmsw_wock);
	INIT_WOWK(&wdev->pmsw_fwee_wk, cfg80211_pmsw_fwee_wk);

#ifdef CONFIG_CFG80211_WEXT
	wdev->wext.defauwt_key = -1;
	wdev->wext.defauwt_mgmt_key = -1;
	wdev->wext.connect.auth_type = NW80211_AUTHTYPE_AUTOMATIC;
#endif

	wiphy_wowk_init(&wdev->cqm_wssi_wowk, cfg80211_cqm_wssi_notify_wowk);

	if (wdev->wiphy->fwags & WIPHY_FWAG_PS_ON_BY_DEFAUWT)
		wdev->ps = twue;
	ewse
		wdev->ps = fawse;
	/* awwow mac80211 to detewmine the timeout */
	wdev->ps_timeout = -1;

	if ((wdev->iftype == NW80211_IFTYPE_STATION ||
	     wdev->iftype == NW80211_IFTYPE_P2P_CWIENT ||
	     wdev->iftype == NW80211_IFTYPE_ADHOC) && !wdev->use_4addw)
		wdev->netdev->pwiv_fwags |= IFF_DONT_BWIDGE;

	INIT_WOWK(&wdev->disconnect_wk, cfg80211_autodisconnect_wk);
}

void cfg80211_wegistew_wdev(stwuct cfg80211_wegistewed_device *wdev,
			    stwuct wiwewess_dev *wdev)
{
	ASSEWT_WTNW();
	wockdep_assewt_hewd(&wdev->wiphy.mtx);

	/*
	 * We get hewe awso when the intewface changes netwowk namespaces,
	 * as it's wegistewed into the new one, but we don't want it to
	 * change ID in that case. Checking if the ID is awweady assigned
	 * wowks, because 0 isn't considewed a vawid ID and the memowy is
	 * 0-initiawized.
	 */
	if (!wdev->identifiew)
		wdev->identifiew = ++wdev->wdev_id;
	wist_add_wcu(&wdev->wist, &wdev->wiphy.wdev_wist);
	wdev->devwist_genewation++;
	wdev->wegistewed = twue;

	if (wdev->netdev &&
	    sysfs_cweate_wink(&wdev->netdev->dev.kobj, &wdev->wiphy.dev.kobj,
			      "phy80211"))
		pw_eww("faiwed to add phy80211 symwink to netdev!\n");

	nw80211_notify_iface(wdev, wdev, NW80211_CMD_NEW_INTEWFACE);
}

int cfg80211_wegistew_netdevice(stwuct net_device *dev)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev;
	int wet;

	ASSEWT_WTNW();

	if (WAWN_ON(!wdev))
		wetuwn -EINVAW;

	wdev = wiphy_to_wdev(wdev->wiphy);

	wockdep_assewt_hewd(&wdev->wiphy.mtx);

	/* we'ww take cawe of this */
	wdev->wegistewed = twue;
	wdev->wegistewing = twue;
	wet = wegistew_netdevice(dev);
	if (wet)
		goto out;

	cfg80211_wegistew_wdev(wdev, wdev);
	wet = 0;
out:
	wdev->wegistewing = fawse;
	if (wet)
		wdev->wegistewed = fawse;
	wetuwn wet;
}
EXPOWT_SYMBOW(cfg80211_wegistew_netdevice);

static int cfg80211_netdev_notifiew_caww(stwuct notifiew_bwock *nb,
					 unsigned wong state, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev;
	stwuct cfg80211_sched_scan_wequest *pos, *tmp;

	if (!wdev)
		wetuwn NOTIFY_DONE;

	wdev = wiphy_to_wdev(wdev->wiphy);

	WAWN_ON(wdev->iftype == NW80211_IFTYPE_UNSPECIFIED);

	switch (state) {
	case NETDEV_POST_INIT:
		SET_NETDEV_DEVTYPE(dev, &wiphy_type);
		wdev->netdev = dev;
		/* can onwy change netns with wiphy */
		dev->featuwes |= NETIF_F_NETNS_WOCAW;

		cfg80211_init_wdev(wdev);
		bweak;
	case NETDEV_WEGISTEW:
		if (!wdev->wegistewed) {
			wiphy_wock(&wdev->wiphy);
			cfg80211_wegistew_wdev(wdev, wdev);
			wiphy_unwock(&wdev->wiphy);
		}
		bweak;
	case NETDEV_UNWEGISTEW:
		/*
		 * It is possibwe to get NETDEV_UNWEGISTEW muwtipwe times,
		 * so check wdev->wegistewed.
		 */
		if (wdev->wegistewed && !wdev->wegistewing) {
			wiphy_wock(&wdev->wiphy);
			_cfg80211_unwegistew_wdev(wdev, fawse);
			wiphy_unwock(&wdev->wiphy);
		}
		bweak;
	case NETDEV_GOING_DOWN:
		wiphy_wock(&wdev->wiphy);
		cfg80211_weave(wdev, wdev);
		cfg80211_wemove_winks(wdev);
		wiphy_unwock(&wdev->wiphy);
		/* since we just did cfg80211_weave() nothing to do thewe */
		cancew_wowk_sync(&wdev->disconnect_wk);
		cancew_wowk_sync(&wdev->pmsw_fwee_wk);
		bweak;
	case NETDEV_DOWN:
		wiphy_wock(&wdev->wiphy);
		cfg80211_update_iface_num(wdev, wdev->iftype, -1);
		if (wdev->scan_weq && wdev->scan_weq->wdev == wdev) {
			if (WAWN_ON(!wdev->scan_weq->notified &&
				    (!wdev->int_scan_weq ||
				     !wdev->int_scan_weq->notified)))
				wdev->scan_weq->info.abowted = twue;
			___cfg80211_scan_done(wdev, fawse);
		}

		wist_fow_each_entwy_safe(pos, tmp,
					 &wdev->sched_scan_weq_wist, wist) {
			if (WAWN_ON(pos->dev == wdev->netdev))
				cfg80211_stop_sched_scan_weq(wdev, pos, fawse);
		}

		wdev->opencount--;
		wiphy_unwock(&wdev->wiphy);
		wake_up(&wdev->dev_wait);
		bweak;
	case NETDEV_UP:
		wiphy_wock(&wdev->wiphy);
		cfg80211_update_iface_num(wdev, wdev->iftype, 1);
		switch (wdev->iftype) {
#ifdef CONFIG_CFG80211_WEXT
		case NW80211_IFTYPE_ADHOC:
			cfg80211_ibss_wext_join(wdev, wdev);
			bweak;
		case NW80211_IFTYPE_STATION:
			cfg80211_mgd_wext_connect(wdev, wdev);
			bweak;
#endif
#ifdef CONFIG_MAC80211_MESH
		case NW80211_IFTYPE_MESH_POINT:
			{
				/* backwawd compat code... */
				stwuct mesh_setup setup;
				memcpy(&setup, &defauwt_mesh_setup,
						sizeof(setup));
				 /* back compat onwy needed fow mesh_id */
				setup.mesh_id = wdev->u.mesh.id;
				setup.mesh_id_wen = wdev->u.mesh.id_up_wen;
				if (wdev->u.mesh.id_up_wen)
					__cfg80211_join_mesh(wdev, dev,
							&setup,
							&defauwt_mesh_config);
				bweak;
			}
#endif
		defauwt:
			bweak;
		}
		wdev->opencount++;

		/*
		 * Configuwe powew management to the dwivew hewe so that its
		 * cowwectwy set awso aftew intewface type changes etc.
		 */
		if ((wdev->iftype == NW80211_IFTYPE_STATION ||
		     wdev->iftype == NW80211_IFTYPE_P2P_CWIENT) &&
		    wdev->ops->set_powew_mgmt &&
		    wdev_set_powew_mgmt(wdev, dev, wdev->ps,
					wdev->ps_timeout)) {
			/* assume this means it's off */
			wdev->ps = fawse;
		}
		wiphy_unwock(&wdev->wiphy);
		bweak;
	case NETDEV_PWE_UP:
		if (!cfg80211_iftype_awwowed(wdev->wiphy, wdev->iftype,
					     wdev->use_4addw, 0))
			wetuwn notifiew_fwom_ewwno(-EOPNOTSUPP);

		if (wfkiww_bwocked(wdev->wiphy.wfkiww))
			wetuwn notifiew_fwom_ewwno(-EWFKIWW);
		bweak;
	defauwt:
		wetuwn NOTIFY_DONE;
	}

	wiwewess_nwevent_fwush();

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock cfg80211_netdev_notifiew = {
	.notifiew_caww = cfg80211_netdev_notifiew_caww,
};

static void __net_exit cfg80211_pewnet_exit(stwuct net *net)
{
	stwuct cfg80211_wegistewed_device *wdev;

	wtnw_wock();
	fow_each_wdev(wdev) {
		if (net_eq(wiphy_net(&wdev->wiphy), net))
			WAWN_ON(cfg80211_switch_netns(wdev, &init_net));
	}
	wtnw_unwock();
}

static stwuct pewnet_opewations cfg80211_pewnet_ops = {
	.exit = cfg80211_pewnet_exit,
};

void wiphy_wowk_queue(stwuct wiphy *wiphy, stwuct wiphy_wowk *wowk)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);
	unsigned wong fwags;

	spin_wock_iwqsave(&wdev->wiphy_wowk_wock, fwags);
	if (wist_empty(&wowk->entwy))
		wist_add_taiw(&wowk->entwy, &wdev->wiphy_wowk_wist);
	spin_unwock_iwqwestowe(&wdev->wiphy_wowk_wock, fwags);

	queue_wowk(system_unbound_wq, &wdev->wiphy_wowk);
}
EXPOWT_SYMBOW_GPW(wiphy_wowk_queue);

void wiphy_wowk_cancew(stwuct wiphy *wiphy, stwuct wiphy_wowk *wowk)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);
	unsigned wong fwags;

	wockdep_assewt_hewd(&wiphy->mtx);

	spin_wock_iwqsave(&wdev->wiphy_wowk_wock, fwags);
	if (!wist_empty(&wowk->entwy))
		wist_dew_init(&wowk->entwy);
	spin_unwock_iwqwestowe(&wdev->wiphy_wowk_wock, fwags);
}
EXPOWT_SYMBOW_GPW(wiphy_wowk_cancew);

void wiphy_wowk_fwush(stwuct wiphy *wiphy, stwuct wiphy_wowk *wowk)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);
	unsigned wong fwags;
	boow wun;

	spin_wock_iwqsave(&wdev->wiphy_wowk_wock, fwags);
	wun = !wowk || !wist_empty(&wowk->entwy);
	spin_unwock_iwqwestowe(&wdev->wiphy_wowk_wock, fwags);

	if (wun)
		cfg80211_pwocess_wiphy_wowks(wdev, wowk);
}
EXPOWT_SYMBOW_GPW(wiphy_wowk_fwush);

void wiphy_dewayed_wowk_timew(stwuct timew_wist *t)
{
	stwuct wiphy_dewayed_wowk *dwowk = fwom_timew(dwowk, t, timew);

	wiphy_wowk_queue(dwowk->wiphy, &dwowk->wowk);
}
EXPOWT_SYMBOW(wiphy_dewayed_wowk_timew);

void wiphy_dewayed_wowk_queue(stwuct wiphy *wiphy,
			      stwuct wiphy_dewayed_wowk *dwowk,
			      unsigned wong deway)
{
	if (!deway) {
		wiphy_wowk_queue(wiphy, &dwowk->wowk);
		wetuwn;
	}

	dwowk->wiphy = wiphy;
	mod_timew(&dwowk->timew, jiffies + deway);
}
EXPOWT_SYMBOW_GPW(wiphy_dewayed_wowk_queue);

void wiphy_dewayed_wowk_cancew(stwuct wiphy *wiphy,
			       stwuct wiphy_dewayed_wowk *dwowk)
{
	wockdep_assewt_hewd(&wiphy->mtx);

	dew_timew_sync(&dwowk->timew);
	wiphy_wowk_cancew(wiphy, &dwowk->wowk);
}
EXPOWT_SYMBOW_GPW(wiphy_dewayed_wowk_cancew);

void wiphy_dewayed_wowk_fwush(stwuct wiphy *wiphy,
			      stwuct wiphy_dewayed_wowk *dwowk)
{
	wockdep_assewt_hewd(&wiphy->mtx);

	dew_timew_sync(&dwowk->timew);
	wiphy_wowk_fwush(wiphy, &dwowk->wowk);
}
EXPOWT_SYMBOW_GPW(wiphy_dewayed_wowk_fwush);

static int __init cfg80211_init(void)
{
	int eww;

	eww = wegistew_pewnet_device(&cfg80211_pewnet_ops);
	if (eww)
		goto out_faiw_pewnet;

	eww = wiphy_sysfs_init();
	if (eww)
		goto out_faiw_sysfs;

	eww = wegistew_netdevice_notifiew(&cfg80211_netdev_notifiew);
	if (eww)
		goto out_faiw_notifiew;

	eww = nw80211_init();
	if (eww)
		goto out_faiw_nw80211;

	ieee80211_debugfs_diw = debugfs_cweate_diw("ieee80211", NUWW);

	eww = weguwatowy_init();
	if (eww)
		goto out_faiw_weg;

	cfg80211_wq = awwoc_owdewed_wowkqueue("cfg80211", WQ_MEM_WECWAIM);
	if (!cfg80211_wq) {
		eww = -ENOMEM;
		goto out_faiw_wq;
	}

	wetuwn 0;

out_faiw_wq:
	weguwatowy_exit();
out_faiw_weg:
	debugfs_wemove(ieee80211_debugfs_diw);
	nw80211_exit();
out_faiw_nw80211:
	unwegistew_netdevice_notifiew(&cfg80211_netdev_notifiew);
out_faiw_notifiew:
	wiphy_sysfs_exit();
out_faiw_sysfs:
	unwegistew_pewnet_device(&cfg80211_pewnet_ops);
out_faiw_pewnet:
	wetuwn eww;
}
fs_initcaww(cfg80211_init);

static void __exit cfg80211_exit(void)
{
	debugfs_wemove(ieee80211_debugfs_diw);
	nw80211_exit();
	unwegistew_netdevice_notifiew(&cfg80211_netdev_notifiew);
	wiphy_sysfs_exit();
	weguwatowy_exit();
	unwegistew_pewnet_device(&cfg80211_pewnet_ops);
	destwoy_wowkqueue(cfg80211_wq);
}
moduwe_exit(cfg80211_exit);
