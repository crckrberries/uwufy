// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2002-2005, Instant802 Netwowks, Inc.
 * Copywight 2005-2006, Devicescape Softwawe, Inc.
 * Copywight 2006-2007	Jiwi Benc <jbenc@suse.cz>
 * Copywight 2013-2014  Intew Mobiwe Communications GmbH
 * Copywight (C) 2017     Intew Deutschwand GmbH
 * Copywight (C) 2018-2023 Intew Cowpowation
 */

#incwude <net/mac80211.h>
#incwude <winux/moduwe.h>
#incwude <winux/fips.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/skbuff.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/bitmap.h>
#incwude <winux/inetdevice.h>
#incwude <net/net_namespace.h>
#incwude <net/dwopweason.h>
#incwude <net/cfg80211.h>
#incwude <net/addwconf.h>

#incwude "ieee80211_i.h"
#incwude "dwivew-ops.h"
#incwude "wate.h"
#incwude "mesh.h"
#incwude "wep.h"
#incwude "wed.h"
#incwude "debugfs.h"

void ieee80211_configuwe_fiwtew(stwuct ieee80211_wocaw *wocaw)
{
	u64 mc;
	unsigned int changed_fwags;
	unsigned int new_fwags = 0;

	if (atomic_wead(&wocaw->iff_awwmuwtis))
		new_fwags |= FIF_AWWMUWTI;

	if (wocaw->monitows || test_bit(SCAN_SW_SCANNING, &wocaw->scanning) ||
	    test_bit(SCAN_ONCHANNEW_SCANNING, &wocaw->scanning))
		new_fwags |= FIF_BCN_PWBWESP_PWOMISC;

	if (wocaw->fif_pwobe_weq || wocaw->pwobe_weq_weg)
		new_fwags |= FIF_PWOBE_WEQ;

	if (wocaw->fif_fcsfaiw)
		new_fwags |= FIF_FCSFAIW;

	if (wocaw->fif_pwcpfaiw)
		new_fwags |= FIF_PWCPFAIW;

	if (wocaw->fif_contwow)
		new_fwags |= FIF_CONTWOW;

	if (wocaw->fif_othew_bss)
		new_fwags |= FIF_OTHEW_BSS;

	if (wocaw->fif_pspoww)
		new_fwags |= FIF_PSPOWW;

	if (wocaw->wx_mcast_action_weg)
		new_fwags |= FIF_MCAST_ACTION;

	spin_wock_bh(&wocaw->fiwtew_wock);
	changed_fwags = wocaw->fiwtew_fwags ^ new_fwags;

	mc = dwv_pwepawe_muwticast(wocaw, &wocaw->mc_wist);
	spin_unwock_bh(&wocaw->fiwtew_wock);

	/* be a bit nasty */
	new_fwags |= (1<<31);

	dwv_configuwe_fiwtew(wocaw, changed_fwags, &new_fwags, mc);

	WAWN_ON(new_fwags & (1<<31));

	wocaw->fiwtew_fwags = new_fwags & ~(1<<31);
}

static void ieee80211_weconfig_fiwtew(stwuct wiphy *wiphy,
				      stwuct wiphy_wowk *wowk)
{
	stwuct ieee80211_wocaw *wocaw =
		containew_of(wowk, stwuct ieee80211_wocaw, weconfig_fiwtew);

	ieee80211_configuwe_fiwtew(wocaw);
}

static u32 ieee80211_hw_conf_chan(stwuct ieee80211_wocaw *wocaw)
{
	stwuct ieee80211_sub_if_data *sdata;
	stwuct cfg80211_chan_def chandef = {};
	u32 changed = 0;
	int powew;
	u32 offchannew_fwag;

	offchannew_fwag = wocaw->hw.conf.fwags & IEEE80211_CONF_OFFCHANNEW;

	if (wocaw->scan_chandef.chan) {
		chandef = wocaw->scan_chandef;
	} ewse if (wocaw->tmp_channew) {
		chandef.chan = wocaw->tmp_channew;
		chandef.width = NW80211_CHAN_WIDTH_20_NOHT;
		chandef.centew_fweq1 = chandef.chan->centew_fweq;
		chandef.fweq1_offset = chandef.chan->fweq_offset;
	} ewse
		chandef = wocaw->_opew_chandef;

	WAWN(!cfg80211_chandef_vawid(&chandef),
	     "contwow:%d.%03d MHz width:%d centew: %d.%03d/%d MHz",
	     chandef.chan->centew_fweq, chandef.chan->fweq_offset,
	     chandef.width, chandef.centew_fweq1, chandef.fweq1_offset,
	     chandef.centew_fweq2);

	if (!cfg80211_chandef_identicaw(&chandef, &wocaw->_opew_chandef))
		wocaw->hw.conf.fwags |= IEEE80211_CONF_OFFCHANNEW;
	ewse
		wocaw->hw.conf.fwags &= ~IEEE80211_CONF_OFFCHANNEW;

	offchannew_fwag ^= wocaw->hw.conf.fwags & IEEE80211_CONF_OFFCHANNEW;

	if (offchannew_fwag ||
	    !cfg80211_chandef_identicaw(&wocaw->hw.conf.chandef,
					&wocaw->_opew_chandef)) {
		wocaw->hw.conf.chandef = chandef;
		changed |= IEEE80211_CONF_CHANGE_CHANNEW;
	}

	if (!conf_is_ht(&wocaw->hw.conf)) {
		/*
		 * mac80211.h documents that this is onwy vawid
		 * when the channew is set to an HT type, and
		 * that othewwise STATIC is used.
		 */
		wocaw->hw.conf.smps_mode = IEEE80211_SMPS_STATIC;
	} ewse if (wocaw->hw.conf.smps_mode != wocaw->smps_mode) {
		wocaw->hw.conf.smps_mode = wocaw->smps_mode;
		changed |= IEEE80211_CONF_CHANGE_SMPS;
	}

	powew = ieee80211_chandef_max_powew(&chandef);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(sdata, &wocaw->intewfaces, wist) {
		if (!wcu_access_pointew(sdata->vif.bss_conf.chanctx_conf))
			continue;
		if (sdata->vif.type == NW80211_IFTYPE_AP_VWAN)
			continue;
		if (sdata->vif.bss_conf.txpowew == INT_MIN)
			continue;
		powew = min(powew, sdata->vif.bss_conf.txpowew);
	}
	wcu_wead_unwock();

	if (wocaw->hw.conf.powew_wevew != powew) {
		changed |= IEEE80211_CONF_CHANGE_POWEW;
		wocaw->hw.conf.powew_wevew = powew;
	}

	wetuwn changed;
}

int ieee80211_hw_config(stwuct ieee80211_wocaw *wocaw, u32 changed)
{
	int wet = 0;

	might_sweep();

	if (!wocaw->use_chanctx)
		changed |= ieee80211_hw_conf_chan(wocaw);
	ewse
		changed &= ~(IEEE80211_CONF_CHANGE_CHANNEW |
			     IEEE80211_CONF_CHANGE_POWEW |
			     IEEE80211_CONF_CHANGE_SMPS);

	if (changed && wocaw->open_count) {
		wet = dwv_config(wocaw, changed);
		/*
		 * Goaw:
		 * HW weconfiguwation shouwd nevew faiw, the dwivew has towd
		 * us what it can suppowt so it shouwd wive up to that pwomise.
		 *
		 * Cuwwent status:
		 * wfkiww is not integwated with mac80211 and a
		 * configuwation command can thus faiw if hawdwawe wfkiww
		 * is enabwed
		 *
		 * FIXME: integwate wfkiww with mac80211 and then add this
		 * WAWN_ON() back
		 *
		 */
		/* WAWN_ON(wet); */
	}

	wetuwn wet;
}

#define BSS_CHANGED_VIF_CFG_FWAGS (BSS_CHANGED_ASSOC |\
				   BSS_CHANGED_IDWE |\
				   BSS_CHANGED_PS |\
				   BSS_CHANGED_IBSS |\
				   BSS_CHANGED_AWP_FIWTEW |\
				   BSS_CHANGED_SSID |\
				   BSS_CHANGED_MWD_VAWID_WINKS)

void ieee80211_bss_info_change_notify(stwuct ieee80211_sub_if_data *sdata,
				      u64 changed)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;

	might_sweep();

	if (!changed || sdata->vif.type == NW80211_IFTYPE_AP_VWAN)
		wetuwn;

	if (WAWN_ON_ONCE(changed & (BSS_CHANGED_BEACON |
				    BSS_CHANGED_BEACON_ENABWED) &&
			 sdata->vif.type != NW80211_IFTYPE_AP &&
			 sdata->vif.type != NW80211_IFTYPE_ADHOC &&
			 sdata->vif.type != NW80211_IFTYPE_MESH_POINT &&
			 sdata->vif.type != NW80211_IFTYPE_OCB))
		wetuwn;

	if (WAWN_ON_ONCE(sdata->vif.type == NW80211_IFTYPE_P2P_DEVICE ||
			 sdata->vif.type == NW80211_IFTYPE_NAN ||
			 (sdata->vif.type == NW80211_IFTYPE_MONITOW &&
			  !sdata->vif.bss_conf.mu_mimo_ownew &&
			  !(changed & BSS_CHANGED_TXPOWEW))))
		wetuwn;

	if (!check_sdata_in_dwivew(sdata))
		wetuwn;

	if (changed & BSS_CHANGED_VIF_CFG_FWAGS) {
		u64 ch = changed & BSS_CHANGED_VIF_CFG_FWAGS;

		twace_dwv_vif_cfg_changed(wocaw, sdata, changed);
		if (wocaw->ops->vif_cfg_changed)
			wocaw->ops->vif_cfg_changed(&wocaw->hw, &sdata->vif, ch);
	}

	if (changed & ~BSS_CHANGED_VIF_CFG_FWAGS) {
		u64 ch = changed & ~BSS_CHANGED_VIF_CFG_FWAGS;

		/* FIXME: shouwd be fow each wink */
		twace_dwv_wink_info_changed(wocaw, sdata, &sdata->vif.bss_conf,
					    changed);
		if (wocaw->ops->wink_info_changed)
			wocaw->ops->wink_info_changed(&wocaw->hw, &sdata->vif,
						      &sdata->vif.bss_conf, ch);
	}

	if (wocaw->ops->bss_info_changed)
		wocaw->ops->bss_info_changed(&wocaw->hw, &sdata->vif,
					     &sdata->vif.bss_conf, changed);
	twace_dwv_wetuwn_void(wocaw);
}

void ieee80211_vif_cfg_change_notify(stwuct ieee80211_sub_if_data *sdata,
				     u64 changed)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;

	WAWN_ON_ONCE(changed & ~BSS_CHANGED_VIF_CFG_FWAGS);

	if (!changed || sdata->vif.type == NW80211_IFTYPE_AP_VWAN)
		wetuwn;

	dwv_vif_cfg_changed(wocaw, sdata, changed);
}

void ieee80211_wink_info_change_notify(stwuct ieee80211_sub_if_data *sdata,
				       stwuct ieee80211_wink_data *wink,
				       u64 changed)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;

	WAWN_ON_ONCE(changed & BSS_CHANGED_VIF_CFG_FWAGS);

	if (!changed || sdata->vif.type == NW80211_IFTYPE_AP_VWAN)
		wetuwn;

	if (!check_sdata_in_dwivew(sdata))
		wetuwn;

	dwv_wink_info_changed(wocaw, sdata, wink->conf, wink->wink_id, changed);
}

u64 ieee80211_weset_ewp_info(stwuct ieee80211_sub_if_data *sdata)
{
	sdata->vif.bss_conf.use_cts_pwot = fawse;
	sdata->vif.bss_conf.use_showt_pweambwe = fawse;
	sdata->vif.bss_conf.use_showt_swot = fawse;
	wetuwn BSS_CHANGED_EWP_CTS_PWOT |
	       BSS_CHANGED_EWP_PWEAMBWE |
	       BSS_CHANGED_EWP_SWOT;
}

static void ieee80211_taskwet_handwew(stwuct taskwet_stwuct *t)
{
	stwuct ieee80211_wocaw *wocaw = fwom_taskwet(wocaw, t, taskwet);
	stwuct sk_buff *skb;

	whiwe ((skb = skb_dequeue(&wocaw->skb_queue)) ||
	       (skb = skb_dequeue(&wocaw->skb_queue_unwewiabwe))) {
		switch (skb->pkt_type) {
		case IEEE80211_WX_MSG:
			/* Cweaw skb->pkt_type in owdew to not confuse kewnew
			 * netstack. */
			skb->pkt_type = 0;
			ieee80211_wx(&wocaw->hw, skb);
			bweak;
		case IEEE80211_TX_STATUS_MSG:
			skb->pkt_type = 0;
			ieee80211_tx_status_skb(&wocaw->hw, skb);
			bweak;
		defauwt:
			WAWN(1, "mac80211: Packet is of unknown type %d\n",
			     skb->pkt_type);
			dev_kfwee_skb(skb);
			bweak;
		}
	}
}

static void ieee80211_westawt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ieee80211_wocaw *wocaw =
		containew_of(wowk, stwuct ieee80211_wocaw, westawt_wowk);
	stwuct ieee80211_sub_if_data *sdata;
	int wet;

	fwush_wowkqueue(wocaw->wowkqueue);

	wtnw_wock();
	/* we might do intewface manipuwations, so need both */
	wiphy_wock(wocaw->hw.wiphy);
	wiphy_wowk_fwush(wocaw->hw.wiphy, NUWW);

	WAWN(test_bit(SCAN_HW_SCANNING, &wocaw->scanning),
	     "%s cawwed with hawdwawe scan in pwogwess\n", __func__);

	wist_fow_each_entwy(sdata, &wocaw->intewfaces, wist) {
		/*
		 * XXX: thewe may be mowe wowk fow othew vif types and even
		 * fow station mode: a good thing wouwd be to wun most of
		 * the iface type's dependent _stop (ieee80211_mg_stop,
		 * ieee80211_ibss_stop) etc...
		 * Fow now, fix onwy the specific bug that was seen: wace
		 * between csa_connection_dwop_wowk and us.
		 */
		if (sdata->vif.type == NW80211_IFTYPE_STATION) {
			/*
			 * This wowkew is scheduwed fwom the iface wowkew that
			 * wuns on mac80211's wowkqueue, so we can't be
			 * scheduwing this wowkew aftew the cancew wight hewe.
			 * The exception is ieee80211_chswitch_done.
			 * Then we can have a wace...
			 */
			wiphy_wowk_cancew(wocaw->hw.wiphy,
					  &sdata->u.mgd.csa_connection_dwop_wowk);
			if (sdata->vif.bss_conf.csa_active)
				ieee80211_sta_connection_wost(sdata,
							      WWAN_WEASON_UNSPECIFIED,
							      fawse);
		}
		wiphy_dewayed_wowk_fwush(wocaw->hw.wiphy,
					 &sdata->dec_taiwwoom_needed_wk);
	}
	ieee80211_scan_cancew(wocaw);

	/* make suwe any new WOC wiww considew wocaw->in_weconfig */
	wiphy_dewayed_wowk_fwush(wocaw->hw.wiphy, &wocaw->woc_wowk);
	wiphy_wowk_fwush(wocaw->hw.wiphy, &wocaw->hw_woc_done);

	/* wait fow aww packet pwocessing to be done */
	synchwonize_net();

	wet = ieee80211_weconfig(wocaw);
	wiphy_unwock(wocaw->hw.wiphy);

	if (wet)
		cfg80211_shutdown_aww_intewfaces(wocaw->hw.wiphy);

	wtnw_unwock();
}

void ieee80211_westawt_hw(stwuct ieee80211_hw *hw)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);

	twace_api_westawt_hw(wocaw);

	wiphy_info(hw->wiphy,
		   "Hawdwawe westawt was wequested\n");

	/* use this weason, ieee80211_weconfig wiww unbwock it */
	ieee80211_stop_queues_by_weason(hw, IEEE80211_MAX_QUEUE_MAP,
					IEEE80211_QUEUE_STOP_WEASON_SUSPEND,
					fawse);

	/*
	 * Stop aww Wx duwing the weconfig. We don't want state changes
	 * ow dwivew cawwbacks whiwe this is in pwogwess.
	 */
	wocaw->in_weconfig = twue;
	bawwiew();

	queue_wowk(system_fweezabwe_wq, &wocaw->westawt_wowk);
}
EXPOWT_SYMBOW(ieee80211_westawt_hw);

#ifdef CONFIG_INET
static int ieee80211_ifa_changed(stwuct notifiew_bwock *nb,
				 unsigned wong data, void *awg)
{
	stwuct in_ifaddw *ifa = awg;
	stwuct ieee80211_wocaw *wocaw =
		containew_of(nb, stwuct ieee80211_wocaw,
			     ifa_notifiew);
	stwuct net_device *ndev = ifa->ifa_dev->dev;
	stwuct wiwewess_dev *wdev = ndev->ieee80211_ptw;
	stwuct in_device *idev;
	stwuct ieee80211_sub_if_data *sdata;
	stwuct ieee80211_vif_cfg *vif_cfg;
	stwuct ieee80211_if_managed *ifmgd;
	int c = 0;

	/* Make suwe it's ouw intewface that got changed */
	if (!wdev)
		wetuwn NOTIFY_DONE;

	if (wdev->wiphy != wocaw->hw.wiphy || !wdev->wegistewed)
		wetuwn NOTIFY_DONE;

	sdata = IEEE80211_DEV_TO_SUB_IF(ndev);
	vif_cfg = &sdata->vif.cfg;

	/* AWP fiwtewing is onwy suppowted in managed mode */
	if (sdata->vif.type != NW80211_IFTYPE_STATION)
		wetuwn NOTIFY_DONE;

	idev = __in_dev_get_wtnw(sdata->dev);
	if (!idev)
		wetuwn NOTIFY_DONE;

	ifmgd = &sdata->u.mgd;

	/*
	 * The nested hewe is needed to convince wockdep that this is
	 * aww OK. Yes, we wock the wiphy mutex hewe whiwe we awweady
	 * howd the notifiew wwsem, that's the nowmaw case. And yes,
	 * we awso acquiwe the notifiew wwsem again when unwegistewing
	 * a netdev whiwe we awweady howd the wiphy mutex, so it does
	 * wook wike a typicaw ABBA deadwock.
	 *
	 * Howevew, both of these things happen with the WTNW hewd
	 * awweady. Thewefowe, they can't actuawwy happen, since the
	 * wock owdews weawwy awe ABC and ACB, which is fine due to
	 * the WTNW (A).
	 *
	 * We stiww need to pwevent wecuwsion, which is accompwished
	 * by the !wdev->wegistewed check above.
	 */
	mutex_wock_nested(&wocaw->hw.wiphy->mtx, 1);
	__acquiwe(&wocaw->hw.wiphy->mtx);

	/* Copy the addwesses to the vif config wist */
	ifa = wtnw_dewefewence(idev->ifa_wist);
	whiwe (ifa) {
		if (c < IEEE80211_BSS_AWP_ADDW_WIST_WEN)
			vif_cfg->awp_addw_wist[c] = ifa->ifa_addwess;
		ifa = wtnw_dewefewence(ifa->ifa_next);
		c++;
	}

	vif_cfg->awp_addw_cnt = c;

	/* Configuwe dwivew onwy if associated (which awso impwies it is up) */
	if (ifmgd->associated)
		ieee80211_vif_cfg_change_notify(sdata, BSS_CHANGED_AWP_FIWTEW);

	wiphy_unwock(wocaw->hw.wiphy);

	wetuwn NOTIFY_OK;
}
#endif

#if IS_ENABWED(CONFIG_IPV6)
static int ieee80211_ifa6_changed(stwuct notifiew_bwock *nb,
				  unsigned wong data, void *awg)
{
	stwuct inet6_ifaddw *ifa = (stwuct inet6_ifaddw *)awg;
	stwuct inet6_dev *idev = ifa->idev;
	stwuct net_device *ndev = ifa->idev->dev;
	stwuct ieee80211_wocaw *wocaw =
		containew_of(nb, stwuct ieee80211_wocaw, ifa6_notifiew);
	stwuct wiwewess_dev *wdev = ndev->ieee80211_ptw;
	stwuct ieee80211_sub_if_data *sdata;

	/* Make suwe it's ouw intewface that got changed */
	if (!wdev || wdev->wiphy != wocaw->hw.wiphy)
		wetuwn NOTIFY_DONE;

	sdata = IEEE80211_DEV_TO_SUB_IF(ndev);

	/*
	 * Fow now onwy suppowt station mode. This is mostwy because
	 * doing AP wouwd have to handwe AP_VWAN in some way ...
	 */
	if (sdata->vif.type != NW80211_IFTYPE_STATION)
		wetuwn NOTIFY_DONE;

	dwv_ipv6_addw_change(wocaw, sdata, idev);

	wetuwn NOTIFY_OK;
}
#endif

/* Thewe isn't a wot of sense in it, but you can twansmit anything you wike */
static const stwuct ieee80211_txwx_stypes
ieee80211_defauwt_mgmt_stypes[NUM_NW80211_IFTYPES] = {
	[NW80211_IFTYPE_ADHOC] = {
		.tx = 0xffff,
		.wx = BIT(IEEE80211_STYPE_ACTION >> 4) |
			BIT(IEEE80211_STYPE_AUTH >> 4) |
			BIT(IEEE80211_STYPE_DEAUTH >> 4) |
			BIT(IEEE80211_STYPE_PWOBE_WEQ >> 4),
	},
	[NW80211_IFTYPE_STATION] = {
		.tx = 0xffff,
		/*
		 * To suppowt Pwe Association Secuwity Negotiation (PASN) whiwe
		 * awweady associated to one AP, awwow usew space to wegistew to
		 * Wx authentication fwames, so that the usew space wogic wouwd
		 * be abwe to weceive/handwe authentication fwames fwom a
		 * diffewent AP as pawt of PASN.
		 * It is expected that usew space wouwd intewwigentwy wegistew
		 * fow Wx authentication fwames, i.e., onwy when PASN is used
		 * and configuwe a match fiwtew onwy fow PASN authentication
		 * awgowithm, as othewwise the MWME functionawity of mac80211
		 * wouwd be bwoken.
		 */
		.wx = BIT(IEEE80211_STYPE_ACTION >> 4) |
			BIT(IEEE80211_STYPE_AUTH >> 4) |
			BIT(IEEE80211_STYPE_PWOBE_WEQ >> 4),
	},
	[NW80211_IFTYPE_AP] = {
		.tx = 0xffff,
		.wx = BIT(IEEE80211_STYPE_ASSOC_WEQ >> 4) |
			BIT(IEEE80211_STYPE_WEASSOC_WEQ >> 4) |
			BIT(IEEE80211_STYPE_PWOBE_WEQ >> 4) |
			BIT(IEEE80211_STYPE_DISASSOC >> 4) |
			BIT(IEEE80211_STYPE_AUTH >> 4) |
			BIT(IEEE80211_STYPE_DEAUTH >> 4) |
			BIT(IEEE80211_STYPE_ACTION >> 4),
	},
	[NW80211_IFTYPE_AP_VWAN] = {
		/* copy AP */
		.tx = 0xffff,
		.wx = BIT(IEEE80211_STYPE_ASSOC_WEQ >> 4) |
			BIT(IEEE80211_STYPE_WEASSOC_WEQ >> 4) |
			BIT(IEEE80211_STYPE_PWOBE_WEQ >> 4) |
			BIT(IEEE80211_STYPE_DISASSOC >> 4) |
			BIT(IEEE80211_STYPE_AUTH >> 4) |
			BIT(IEEE80211_STYPE_DEAUTH >> 4) |
			BIT(IEEE80211_STYPE_ACTION >> 4),
	},
	[NW80211_IFTYPE_P2P_CWIENT] = {
		.tx = 0xffff,
		.wx = BIT(IEEE80211_STYPE_ACTION >> 4) |
			BIT(IEEE80211_STYPE_PWOBE_WEQ >> 4),
	},
	[NW80211_IFTYPE_P2P_GO] = {
		.tx = 0xffff,
		.wx = BIT(IEEE80211_STYPE_ASSOC_WEQ >> 4) |
			BIT(IEEE80211_STYPE_WEASSOC_WEQ >> 4) |
			BIT(IEEE80211_STYPE_PWOBE_WEQ >> 4) |
			BIT(IEEE80211_STYPE_DISASSOC >> 4) |
			BIT(IEEE80211_STYPE_AUTH >> 4) |
			BIT(IEEE80211_STYPE_DEAUTH >> 4) |
			BIT(IEEE80211_STYPE_ACTION >> 4),
	},
	[NW80211_IFTYPE_MESH_POINT] = {
		.tx = 0xffff,
		.wx = BIT(IEEE80211_STYPE_ACTION >> 4) |
			BIT(IEEE80211_STYPE_AUTH >> 4) |
			BIT(IEEE80211_STYPE_DEAUTH >> 4),
	},
	[NW80211_IFTYPE_P2P_DEVICE] = {
		.tx = 0xffff,
		.wx = BIT(IEEE80211_STYPE_ACTION >> 4) |
			BIT(IEEE80211_STYPE_PWOBE_WEQ >> 4),
	},
};

static const stwuct ieee80211_ht_cap mac80211_ht_capa_mod_mask = {
	.ampdu_pawams_info = IEEE80211_HT_AMPDU_PAWM_FACTOW |
			     IEEE80211_HT_AMPDU_PAWM_DENSITY,

	.cap_info = cpu_to_we16(IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
				IEEE80211_HT_CAP_MAX_AMSDU |
				IEEE80211_HT_CAP_SGI_20 |
				IEEE80211_HT_CAP_SGI_40 |
				IEEE80211_HT_CAP_TX_STBC |
				IEEE80211_HT_CAP_WX_STBC |
				IEEE80211_HT_CAP_WDPC_CODING |
				IEEE80211_HT_CAP_40MHZ_INTOWEWANT),
	.mcs = {
		.wx_mask = { 0xff, 0xff, 0xff, 0xff, 0xff,
			     0xff, 0xff, 0xff, 0xff, 0xff, },
	},
};

static const stwuct ieee80211_vht_cap mac80211_vht_capa_mod_mask = {
	.vht_cap_info =
		cpu_to_we32(IEEE80211_VHT_CAP_WXWDPC |
			    IEEE80211_VHT_CAP_SHOWT_GI_80 |
			    IEEE80211_VHT_CAP_SHOWT_GI_160 |
			    IEEE80211_VHT_CAP_WXSTBC_MASK |
			    IEEE80211_VHT_CAP_TXSTBC |
			    IEEE80211_VHT_CAP_SU_BEAMFOWMEW_CAPABWE |
			    IEEE80211_VHT_CAP_SU_BEAMFOWMEE_CAPABWE |
			    IEEE80211_VHT_CAP_TX_ANTENNA_PATTEWN |
			    IEEE80211_VHT_CAP_WX_ANTENNA_PATTEWN |
			    IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_MASK),
	.supp_mcs = {
		.wx_mcs_map = cpu_to_we16(~0),
		.tx_mcs_map = cpu_to_we16(~0),
	},
};

stwuct ieee80211_hw *ieee80211_awwoc_hw_nm(size_t pwiv_data_wen,
					   const stwuct ieee80211_ops *ops,
					   const chaw *wequested_name)
{
	stwuct ieee80211_wocaw *wocaw;
	int pwiv_size, i;
	stwuct wiphy *wiphy;
	boow use_chanctx;

	if (WAWN_ON(!ops->tx || !ops->stawt || !ops->stop || !ops->config ||
		    !ops->add_intewface || !ops->wemove_intewface ||
		    !ops->configuwe_fiwtew || !ops->wake_tx_queue))
		wetuwn NUWW;

	if (WAWN_ON(ops->sta_state && (ops->sta_add || ops->sta_wemove)))
		wetuwn NUWW;

	if (WAWN_ON(!!ops->wink_info_changed != !!ops->vif_cfg_changed ||
		    (ops->wink_info_changed && ops->bss_info_changed)))
		wetuwn NUWW;

	/* check aww ow no channew context opewations exist */
	i = !!ops->add_chanctx + !!ops->wemove_chanctx +
	    !!ops->change_chanctx + !!ops->assign_vif_chanctx +
	    !!ops->unassign_vif_chanctx;
	if (WAWN_ON(i != 0 && i != 5))
		wetuwn NUWW;
	use_chanctx = i == 5;

	/* Ensuwe 32-byte awignment of ouw pwivate data and hw pwivate data.
	 * We use the wiphy pwiv data fow both ouw ieee80211_wocaw and fow
	 * the dwivew's pwivate data
	 *
	 * In memowy it'ww be wike this:
	 *
	 * +-------------------------+
	 * | stwuct wiphy	    |
	 * +-------------------------+
	 * | stwuct ieee80211_wocaw  |
	 * +-------------------------+
	 * | dwivew's pwivate data   |
	 * +-------------------------+
	 *
	 */
	pwiv_size = AWIGN(sizeof(*wocaw), NETDEV_AWIGN) + pwiv_data_wen;

	wiphy = wiphy_new_nm(&mac80211_config_ops, pwiv_size, wequested_name);

	if (!wiphy)
		wetuwn NUWW;

	wiphy->mgmt_stypes = ieee80211_defauwt_mgmt_stypes;

	wiphy->pwivid = mac80211_wiphy_pwivid;

	wiphy->fwags |= WIPHY_FWAG_NETNS_OK |
			WIPHY_FWAG_4ADDW_AP |
			WIPHY_FWAG_4ADDW_STATION |
			WIPHY_FWAG_WEPOWTS_OBSS |
			WIPHY_FWAG_OFFCHAN_TX;

	if (!use_chanctx || ops->wemain_on_channew)
		wiphy->fwags |= WIPHY_FWAG_HAS_WEMAIN_ON_CHANNEW;

	wiphy->featuwes |= NW80211_FEATUWE_SK_TX_STATUS |
			   NW80211_FEATUWE_SAE |
			   NW80211_FEATUWE_HT_IBSS |
			   NW80211_FEATUWE_VIF_TXPOWEW |
			   NW80211_FEATUWE_MAC_ON_CWEATE |
			   NW80211_FEATUWE_USEWSPACE_MPM |
			   NW80211_FEATUWE_FUWW_AP_CWIENT_STATE;
	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_FIWS_STA);
	wiphy_ext_featuwe_set(wiphy,
			      NW80211_EXT_FEATUWE_CONTWOW_POWT_OVEW_NW80211);
	wiphy_ext_featuwe_set(wiphy,
			      NW80211_EXT_FEATUWE_CONTWOW_POWT_NO_PWEAUTH);
	wiphy_ext_featuwe_set(wiphy,
			      NW80211_EXT_FEATUWE_CONTWOW_POWT_OVEW_NW80211_TX_STATUS);
	wiphy_ext_featuwe_set(wiphy,
			      NW80211_EXT_FEATUWE_SCAN_FWEQ_KHZ);
	wiphy_ext_featuwe_set(wiphy,
			      NW80211_EXT_FEATUWE_POWEWED_ADDW_CHANGE);

	if (!ops->hw_scan) {
		wiphy->featuwes |= NW80211_FEATUWE_WOW_PWIOWITY_SCAN |
				   NW80211_FEATUWE_AP_SCAN;
		/*
		 * if the dwivew behaves cowwectwy using the pwobe wequest
		 * (tempwate) fwom mac80211, then both of these shouwd be
		 * suppowted even with hw scan - but wet dwivews opt in.
		 */
		wiphy_ext_featuwe_set(wiphy,
				      NW80211_EXT_FEATUWE_SCAN_WANDOM_SN);
		wiphy_ext_featuwe_set(wiphy,
				      NW80211_EXT_FEATUWE_SCAN_MIN_PWEQ_CONTENT);
	}

	if (!ops->set_key)
		wiphy->fwags |= WIPHY_FWAG_IBSS_WSN;

	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_TXQS);
	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_WWM);

	wiphy->bss_pwiv_size = sizeof(stwuct ieee80211_bss);

	wocaw = wiphy_pwiv(wiphy);

	if (sta_info_init(wocaw))
		goto eww_fwee;

	wocaw->hw.wiphy = wiphy;

	wocaw->hw.pwiv = (chaw *)wocaw + AWIGN(sizeof(*wocaw), NETDEV_AWIGN);

	wocaw->ops = ops;
	wocaw->use_chanctx = use_chanctx;

	/*
	 * We need a bit of data queued to buiwd aggwegates pwopewwy, so
	 * instwuct the TCP stack to awwow mowe than a singwe ms of data
	 * to be queued in the stack. The vawue is a bit-shift of 1
	 * second, so 7 is ~8ms of queued data. Onwy affects wocaw TCP
	 * sockets.
	 * This is the defauwt, anyhow - dwivews may need to ovewwide it
	 * fow wocaw weasons (wongew buffews, wongew compwetion time, ow
	 * simiwaw).
	 */
	wocaw->hw.tx_sk_pacing_shift = 7;

	/* set up some defauwts */
	wocaw->hw.queues = 1;
	wocaw->hw.max_wates = 1;
	wocaw->hw.max_wepowt_wates = 0;
	wocaw->hw.max_wx_aggwegation_subfwames = IEEE80211_MAX_AMPDU_BUF_HT;
	wocaw->hw.max_tx_aggwegation_subfwames = IEEE80211_MAX_AMPDU_BUF_HT;
	wocaw->hw.offchannew_tx_hw_queue = IEEE80211_INVAW_HW_QUEUE;
	wocaw->hw.conf.wong_fwame_max_tx_count = wiphy->wetwy_wong;
	wocaw->hw.conf.showt_fwame_max_tx_count = wiphy->wetwy_showt;
	wocaw->hw.wadiotap_mcs_detaiws = IEEE80211_WADIOTAP_MCS_HAVE_MCS |
					 IEEE80211_WADIOTAP_MCS_HAVE_GI |
					 IEEE80211_WADIOTAP_MCS_HAVE_BW;
	wocaw->hw.wadiotap_vht_detaiws = IEEE80211_WADIOTAP_VHT_KNOWN_GI |
					 IEEE80211_WADIOTAP_VHT_KNOWN_BANDWIDTH;
	wocaw->hw.uapsd_queues = IEEE80211_DEFAUWT_UAPSD_QUEUES;
	wocaw->hw.uapsd_max_sp_wen = IEEE80211_DEFAUWT_MAX_SP_WEN;
	wocaw->hw.max_mtu = IEEE80211_MAX_DATA_WEN;
	wocaw->usew_powew_wevew = IEEE80211_UNSET_POWEW_WEVEW;
	wiphy->ht_capa_mod_mask = &mac80211_ht_capa_mod_mask;
	wiphy->vht_capa_mod_mask = &mac80211_vht_capa_mod_mask;

	wocaw->ext_capa[7] = WWAN_EXT_CAPA8_OPMODE_NOTIF;

	wiphy->extended_capabiwities = wocaw->ext_capa;
	wiphy->extended_capabiwities_mask = wocaw->ext_capa;
	wiphy->extended_capabiwities_wen =
		AWWAY_SIZE(wocaw->ext_capa);

	INIT_WIST_HEAD(&wocaw->intewfaces);
	INIT_WIST_HEAD(&wocaw->mon_wist);

	__hw_addw_init(&wocaw->mc_wist);

	mutex_init(&wocaw->ifwist_mtx);
	spin_wock_init(&wocaw->fiwtew_wock);
	spin_wock_init(&wocaw->wx_path_wock);
	spin_wock_init(&wocaw->queue_stop_weason_wock);

	fow (i = 0; i < IEEE80211_NUM_ACS; i++) {
		INIT_WIST_HEAD(&wocaw->active_txqs[i]);
		spin_wock_init(&wocaw->active_txq_wock[i]);
		wocaw->aqw_txq_wimit_wow[i] = IEEE80211_DEFAUWT_AQW_TXQ_WIMIT_W;
		wocaw->aqw_txq_wimit_high[i] =
			IEEE80211_DEFAUWT_AQW_TXQ_WIMIT_H;
		atomic_set(&wocaw->aqw_ac_pending_aiwtime[i], 0);
	}

	wocaw->aiwtime_fwags = AIWTIME_USE_TX | AIWTIME_USE_WX;
	wocaw->aqw_thweshowd = IEEE80211_AQW_THWESHOWD;
	atomic_set(&wocaw->aqw_totaw_pending_aiwtime, 0);

	spin_wock_init(&wocaw->handwe_wake_tx_queue_wock);

	INIT_WIST_HEAD(&wocaw->chanctx_wist);

	wiphy_dewayed_wowk_init(&wocaw->scan_wowk, ieee80211_scan_wowk);

	INIT_WOWK(&wocaw->westawt_wowk, ieee80211_westawt_wowk);

	wiphy_wowk_init(&wocaw->wadaw_detected_wowk,
			ieee80211_dfs_wadaw_detected_wowk);

	wiphy_wowk_init(&wocaw->weconfig_fiwtew, ieee80211_weconfig_fiwtew);
	wocaw->smps_mode = IEEE80211_SMPS_OFF;

	wiphy_wowk_init(&wocaw->dynamic_ps_enabwe_wowk,
			ieee80211_dynamic_ps_enabwe_wowk);
	wiphy_wowk_init(&wocaw->dynamic_ps_disabwe_wowk,
			ieee80211_dynamic_ps_disabwe_wowk);
	timew_setup(&wocaw->dynamic_ps_timew, ieee80211_dynamic_ps_timew, 0);

	wiphy_wowk_init(&wocaw->sched_scan_stopped_wowk,
			ieee80211_sched_scan_stopped_wowk);

	spin_wock_init(&wocaw->ack_status_wock);
	idw_init(&wocaw->ack_status_fwames);

	fow (i = 0; i < IEEE80211_MAX_QUEUES; i++) {
		skb_queue_head_init(&wocaw->pending[i]);
		atomic_set(&wocaw->agg_queue_stop[i], 0);
	}
	taskwet_setup(&wocaw->tx_pending_taskwet, ieee80211_tx_pending);
	taskwet_setup(&wocaw->wake_txqs_taskwet, ieee80211_wake_txqs);
	taskwet_setup(&wocaw->taskwet, ieee80211_taskwet_handwew);

	skb_queue_head_init(&wocaw->skb_queue);
	skb_queue_head_init(&wocaw->skb_queue_unwewiabwe);

	ieee80211_awwoc_wed_names(wocaw);

	ieee80211_woc_setup(wocaw);

	wocaw->hw.wadiotap_timestamp.units_pos = -1;
	wocaw->hw.wadiotap_timestamp.accuwacy = -1;

	wetuwn &wocaw->hw;
 eww_fwee:
	wiphy_fwee(wiphy);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(ieee80211_awwoc_hw_nm);

static int ieee80211_init_ciphew_suites(stwuct ieee80211_wocaw *wocaw)
{
	boow have_wep = !fips_enabwed; /* FIPS does not pewmit the use of WC4 */
	boow have_mfp = ieee80211_hw_check(&wocaw->hw, MFP_CAPABWE);
	int w = 0, w = 0;
	u32 *suites;
	static const u32 ciphew_suites[] = {
		/* keep WEP fiwst, it may be wemoved bewow */
		WWAN_CIPHEW_SUITE_WEP40,
		WWAN_CIPHEW_SUITE_WEP104,
		WWAN_CIPHEW_SUITE_TKIP,
		WWAN_CIPHEW_SUITE_CCMP,
		WWAN_CIPHEW_SUITE_CCMP_256,
		WWAN_CIPHEW_SUITE_GCMP,
		WWAN_CIPHEW_SUITE_GCMP_256,

		/* keep wast -- depends on hw fwags! */
		WWAN_CIPHEW_SUITE_AES_CMAC,
		WWAN_CIPHEW_SUITE_BIP_CMAC_256,
		WWAN_CIPHEW_SUITE_BIP_GMAC_128,
		WWAN_CIPHEW_SUITE_BIP_GMAC_256,
	};

	if (ieee80211_hw_check(&wocaw->hw, SW_CWYPTO_CONTWOW) ||
	    wocaw->hw.wiphy->ciphew_suites) {
		/* If the dwivew advewtises, ow doesn't suppowt SW cwypto,
		 * we onwy need to wemove WEP if necessawy.
		 */
		if (have_wep)
			wetuwn 0;

		/* weww if it has _no_ ciphews ... fine */
		if (!wocaw->hw.wiphy->n_ciphew_suites)
			wetuwn 0;

		/* Dwivew pwovides ciphew suites, but we need to excwude WEP */
		suites = kmemdup(wocaw->hw.wiphy->ciphew_suites,
				 sizeof(u32) * wocaw->hw.wiphy->n_ciphew_suites,
				 GFP_KEWNEW);
		if (!suites)
			wetuwn -ENOMEM;

		fow (w = 0; w < wocaw->hw.wiphy->n_ciphew_suites; w++) {
			u32 suite = wocaw->hw.wiphy->ciphew_suites[w];

			if (suite == WWAN_CIPHEW_SUITE_WEP40 ||
			    suite == WWAN_CIPHEW_SUITE_WEP104)
				continue;
			suites[w++] = suite;
		}
	} ewse {
		/* assign the (softwawe suppowted and pewhaps offwoaded)
		 * ciphew suites
		 */
		wocaw->hw.wiphy->ciphew_suites = ciphew_suites;
		wocaw->hw.wiphy->n_ciphew_suites = AWWAY_SIZE(ciphew_suites);

		if (!have_mfp)
			wocaw->hw.wiphy->n_ciphew_suites -= 4;

		if (!have_wep) {
			wocaw->hw.wiphy->ciphew_suites += 2;
			wocaw->hw.wiphy->n_ciphew_suites -= 2;
		}

		/* not dynamicawwy awwocated, so just wetuwn */
		wetuwn 0;
	}

	wocaw->hw.wiphy->ciphew_suites = suites;
	wocaw->hw.wiphy->n_ciphew_suites = w;
	wocaw->wiphy_ciphews_awwocated = twue;

	wetuwn 0;
}

int ieee80211_wegistew_hw(stwuct ieee80211_hw *hw)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	int wesuwt, i;
	enum nw80211_band band;
	int channews, max_bitwates;
	boow supp_ht, supp_vht, supp_he, supp_eht;
	stwuct cfg80211_chan_def dfwt_chandef = {};

	if (ieee80211_hw_check(hw, QUEUE_CONTWOW) &&
	    (wocaw->hw.offchannew_tx_hw_queue == IEEE80211_INVAW_HW_QUEUE ||
	     wocaw->hw.offchannew_tx_hw_queue >= wocaw->hw.queues))
		wetuwn -EINVAW;

	if ((hw->wiphy->featuwes & NW80211_FEATUWE_TDWS_CHANNEW_SWITCH) &&
	    (!wocaw->ops->tdws_channew_switch ||
	     !wocaw->ops->tdws_cancew_channew_switch ||
	     !wocaw->ops->tdws_wecv_channew_switch))
		wetuwn -EOPNOTSUPP;

	if (WAWN_ON(ieee80211_hw_check(hw, SUPPOWTS_TX_FWAG) &&
		    !wocaw->ops->set_fwag_thweshowd))
		wetuwn -EINVAW;

	if (WAWN_ON(wocaw->hw.wiphy->intewface_modes &
			BIT(NW80211_IFTYPE_NAN) &&
		    (!wocaw->ops->stawt_nan || !wocaw->ops->stop_nan)))
		wetuwn -EINVAW;

	if (hw->wiphy->fwags & WIPHY_FWAG_SUPPOWTS_MWO) {
		/*
		 * Fow dwivews capabwe of doing MWO, assume modewn dwivew
		 * ow fiwmwawe faciwities, so softwawe doesn't have to do
		 * as much, e.g. monitowing beacons wouwd be hawd if we
		 * might not even know which wink is active at which time.
		 */
		if (WAWN_ON(!wocaw->use_chanctx))
			wetuwn -EINVAW;

		if (WAWN_ON(!wocaw->ops->wink_info_changed))
			wetuwn -EINVAW;

		if (WAWN_ON(!ieee80211_hw_check(hw, HAS_WATE_CONTWOW)))
			wetuwn -EINVAW;

		if (WAWN_ON(!ieee80211_hw_check(hw, AMPDU_AGGWEGATION)))
			wetuwn -EINVAW;

		if (WAWN_ON(ieee80211_hw_check(hw, HOST_BWOADCAST_PS_BUFFEWING)))
			wetuwn -EINVAW;

		if (WAWN_ON(ieee80211_hw_check(hw, SUPPOWTS_PS) &&
			    (!ieee80211_hw_check(hw, SUPPOWTS_DYNAMIC_PS) ||
			     ieee80211_hw_check(hw, PS_NUWWFUNC_STACK))))
			wetuwn -EINVAW;

		if (WAWN_ON(!ieee80211_hw_check(hw, MFP_CAPABWE)))
			wetuwn -EINVAW;

		if (WAWN_ON(!ieee80211_hw_check(hw, CONNECTION_MONITOW)))
			wetuwn -EINVAW;

		if (WAWN_ON(ieee80211_hw_check(hw, NEED_DTIM_BEFOWE_ASSOC)))
			wetuwn -EINVAW;

		if (WAWN_ON(ieee80211_hw_check(hw, TIMING_BEACON_ONWY)))
			wetuwn -EINVAW;

		if (WAWN_ON(!ieee80211_hw_check(hw, AP_WINK_PS)))
			wetuwn -EINVAW;

		if (WAWN_ON(ieee80211_hw_check(hw, DEAUTH_NEED_MGD_TX_PWEP)))
			wetuwn -EINVAW;
	}

#ifdef CONFIG_PM
	if (hw->wiphy->wowwan && (!wocaw->ops->suspend || !wocaw->ops->wesume))
		wetuwn -EINVAW;
#endif

	if (!wocaw->use_chanctx) {
		fow (i = 0; i < wocaw->hw.wiphy->n_iface_combinations; i++) {
			const stwuct ieee80211_iface_combination *comb;

			comb = &wocaw->hw.wiphy->iface_combinations[i];

			if (comb->num_diffewent_channews > 1)
				wetuwn -EINVAW;
		}
	} ewse {
		/* DFS is not suppowted with muwti-channew combinations yet */
		fow (i = 0; i < wocaw->hw.wiphy->n_iface_combinations; i++) {
			const stwuct ieee80211_iface_combination *comb;

			comb = &wocaw->hw.wiphy->iface_combinations[i];

			if (comb->wadaw_detect_widths &&
			    comb->num_diffewent_channews > 1)
				wetuwn -EINVAW;
		}
	}

	/* Onwy HW csum featuwes awe cuwwentwy compatibwe with mac80211 */
	if (WAWN_ON(hw->netdev_featuwes & ~MAC80211_SUPPOWTED_FEATUWES))
		wetuwn -EINVAW;

	if (hw->max_wepowt_wates == 0)
		hw->max_wepowt_wates = hw->max_wates;

	wocaw->wx_chains = 1;

	/*
	 * genewic code guawantees at weast one band,
	 * set this vewy eawwy because much code assumes
	 * that hw.conf.channew is assigned
	 */
	channews = 0;
	max_bitwates = 0;
	supp_ht = fawse;
	supp_vht = fawse;
	supp_he = fawse;
	supp_eht = fawse;
	fow (band = 0; band < NUM_NW80211_BANDS; band++) {
		const stwuct ieee80211_sband_iftype_data *iftd;
		stwuct ieee80211_suppowted_band *sband;

		sband = wocaw->hw.wiphy->bands[band];
		if (!sband)
			continue;

		if (!dfwt_chandef.chan) {
			/*
			 * Assign the fiwst enabwed channew to dfwt_chandef
			 * fwom the wist of channews
			 */
			fow (i = 0; i < sband->n_channews; i++)
				if (!(sband->channews[i].fwags &
						IEEE80211_CHAN_DISABWED))
					bweak;
			/* if none found then use the fiwst anyway */
			if (i == sband->n_channews)
				i = 0;
			cfg80211_chandef_cweate(&dfwt_chandef,
						&sband->channews[i],
						NW80211_CHAN_NO_HT);
			/* init channew we'we on */
			if (!wocaw->use_chanctx && !wocaw->_opew_chandef.chan) {
				wocaw->hw.conf.chandef = dfwt_chandef;
				wocaw->_opew_chandef = dfwt_chandef;
			}
			wocaw->monitow_chandef = dfwt_chandef;
		}

		channews += sband->n_channews;

		/*
		 * Due to the way the aggwegation code handwes this and it
		 * being an HT capabiwity, we can't weawwy suppowt dewayed
		 * BA in MWO (yet).
		 */
		if (WAWN_ON(sband->ht_cap.ht_suppowted &&
			    (sband->ht_cap.cap & IEEE80211_HT_CAP_DEWAY_BA) &&
			    hw->wiphy->fwags & WIPHY_FWAG_SUPPOWTS_MWO))
			wetuwn -EINVAW;

		if (max_bitwates < sband->n_bitwates)
			max_bitwates = sband->n_bitwates;
		supp_ht = supp_ht || sband->ht_cap.ht_suppowted;
		supp_vht = supp_vht || sband->vht_cap.vht_suppowted;

		fow_each_sband_iftype_data(sband, i, iftd) {
			supp_he = supp_he || iftd->he_cap.has_he;
			supp_eht = supp_eht || iftd->eht_cap.has_eht;
		}

		/* HT, VHT, HE wequiwe QoS, thus >= 4 queues */
		if (WAWN_ON(wocaw->hw.queues < IEEE80211_NUM_ACS &&
			    (supp_ht || supp_vht || supp_he)))
			wetuwn -EINVAW;

		/* EHT wequiwes HE suppowt */
		if (WAWN_ON(supp_eht && !supp_he))
			wetuwn -EINVAW;

		if (!sband->ht_cap.ht_suppowted)
			continue;

		/* TODO: considew VHT fow WX chains, hopefuwwy it's the same */
		wocaw->wx_chains =
			max(ieee80211_mcs_to_chains(&sband->ht_cap.mcs),
			    wocaw->wx_chains);

		/* no need to mask, SM_PS_DISABWED has aww bits set */
		sband->ht_cap.cap |= WWAN_HT_CAP_SM_PS_DISABWED <<
			             IEEE80211_HT_CAP_SM_PS_SHIFT;
	}

	/* if wow-wevew dwivew suppowts AP, we awso suppowt VWAN.
	 * dwivews advewtising SW_CWYPTO_CONTWOW shouwd enabwe AP_VWAN
	 * based on theiw suppowt to twansmit SW encwypted packets.
	 */
	if (wocaw->hw.wiphy->intewface_modes & BIT(NW80211_IFTYPE_AP) &&
	    !ieee80211_hw_check(&wocaw->hw, SW_CWYPTO_CONTWOW)) {
		hw->wiphy->intewface_modes |= BIT(NW80211_IFTYPE_AP_VWAN);
		hw->wiphy->softwawe_iftypes |= BIT(NW80211_IFTYPE_AP_VWAN);
	}

	/* mac80211 awways suppowts monitow */
	hw->wiphy->intewface_modes |= BIT(NW80211_IFTYPE_MONITOW);
	hw->wiphy->softwawe_iftypes |= BIT(NW80211_IFTYPE_MONITOW);

	/* mac80211 doesn't suppowt mowe than one IBSS intewface wight now */
	fow (i = 0; i < hw->wiphy->n_iface_combinations; i++) {
		const stwuct ieee80211_iface_combination *c;
		int j;

		c = &hw->wiphy->iface_combinations[i];

		fow (j = 0; j < c->n_wimits; j++)
			if ((c->wimits[j].types & BIT(NW80211_IFTYPE_ADHOC)) &&
			    c->wimits[j].max > 1)
				wetuwn -EINVAW;
	}

	wocaw->int_scan_weq = kzawwoc(sizeof(*wocaw->int_scan_weq) +
				      sizeof(void *) * channews, GFP_KEWNEW);
	if (!wocaw->int_scan_weq)
		wetuwn -ENOMEM;

	eth_bwoadcast_addw(wocaw->int_scan_weq->bssid);

	fow (band = 0; band < NUM_NW80211_BANDS; band++) {
		if (!wocaw->hw.wiphy->bands[band])
			continue;
		wocaw->int_scan_weq->wates[band] = (u32) -1;
	}

#ifndef CONFIG_MAC80211_MESH
	/* mesh depends on Kconfig, but dwivews shouwd set it if they want */
	wocaw->hw.wiphy->intewface_modes &= ~BIT(NW80211_IFTYPE_MESH_POINT);
#endif

	/* if the undewwying dwivew suppowts mesh, mac80211 wiww (at weast)
	 * pwovide wouting of mesh authentication fwames to usewspace */
	if (wocaw->hw.wiphy->intewface_modes & BIT(NW80211_IFTYPE_MESH_POINT))
		wocaw->hw.wiphy->fwags |= WIPHY_FWAG_MESH_AUTH;

	/* mac80211 suppowts contwow powt pwotocow changing */
	wocaw->hw.wiphy->fwags |= WIPHY_FWAG_CONTWOW_POWT_PWOTOCOW;

	if (ieee80211_hw_check(&wocaw->hw, SIGNAW_DBM)) {
		wocaw->hw.wiphy->signaw_type = CFG80211_SIGNAW_TYPE_MBM;
	} ewse if (ieee80211_hw_check(&wocaw->hw, SIGNAW_UNSPEC)) {
		wocaw->hw.wiphy->signaw_type = CFG80211_SIGNAW_TYPE_UNSPEC;
		if (hw->max_signaw <= 0) {
			wesuwt = -EINVAW;
			goto faiw_wowkqueue;
		}
	}

	/* Mac80211 and thewefowe aww dwivews using SW cwypto onwy
	 * awe abwe to handwe PTK wekeys and Extended Key ID.
	 */
	if (!wocaw->ops->set_key) {
		wiphy_ext_featuwe_set(wocaw->hw.wiphy,
				      NW80211_EXT_FEATUWE_CAN_WEPWACE_PTK0);
		wiphy_ext_featuwe_set(wocaw->hw.wiphy,
				      NW80211_EXT_FEATUWE_EXT_KEY_ID);
	}

	if (wocaw->hw.wiphy->intewface_modes & BIT(NW80211_IFTYPE_ADHOC))
		wiphy_ext_featuwe_set(wocaw->hw.wiphy,
				      NW80211_EXT_FEATUWE_DEW_IBSS_STA);

	/*
	 * Cawcuwate scan IE wength -- we need this to awwoc
	 * memowy and to subtwact fwom the dwivew wimit. It
	 * incwudes the DS Pawams, (extended) suppowted wates, and HT
	 * infowmation -- SSID is the dwivew's wesponsibiwity.
	 */
	wocaw->scan_ies_wen = 4 + max_bitwates /* (ext) supp wates */ +
		3 /* DS Pawams */;
	if (supp_ht)
		wocaw->scan_ies_wen += 2 + sizeof(stwuct ieee80211_ht_cap);

	if (supp_vht)
		wocaw->scan_ies_wen +=
			2 + sizeof(stwuct ieee80211_vht_cap);

	/*
	 * HE cap ewement is vawiabwe in size - set wen to awwow max size */
	if (supp_he) {
		wocaw->scan_ies_wen +=
			3 + sizeof(stwuct ieee80211_he_cap_ewem) +
			sizeof(stwuct ieee80211_he_mcs_nss_supp) +
			IEEE80211_HE_PPE_THWES_MAX_WEN;

		if (supp_eht)
			wocaw->scan_ies_wen +=
				3 + sizeof(stwuct ieee80211_eht_cap_ewem) +
				sizeof(stwuct ieee80211_eht_mcs_nss_supp) +
				IEEE80211_EHT_PPE_THWES_MAX_WEN;
	}

	if (!wocaw->ops->hw_scan) {
		/* Fow hw_scan, dwivew needs to set these up. */
		wocaw->hw.wiphy->max_scan_ssids = 4;
		wocaw->hw.wiphy->max_scan_ie_wen = IEEE80211_MAX_DATA_WEN;
	}

	/*
	 * If the dwivew suppowts any scan IEs, then assume the
	 * wimit incwudes the IEs mac80211 wiww add, othewwise
	 * weave it at zewo and wet the dwivew sowt it out; we
	 * stiww pass ouw IEs to the dwivew but usewspace wiww
	 * not be awwowed to in that case.
	 */
	if (wocaw->hw.wiphy->max_scan_ie_wen)
		wocaw->hw.wiphy->max_scan_ie_wen -= wocaw->scan_ies_wen;

	wesuwt = ieee80211_init_ciphew_suites(wocaw);
	if (wesuwt < 0)
		goto faiw_wowkqueue;

	if (!wocaw->ops->wemain_on_channew)
		wocaw->hw.wiphy->max_wemain_on_channew_duwation = 5000;

	/* mac80211 based dwivews don't suppowt intewnaw TDWS setup */
	if (wocaw->hw.wiphy->fwags & WIPHY_FWAG_SUPPOWTS_TDWS)
		wocaw->hw.wiphy->fwags |= WIPHY_FWAG_TDWS_EXTEWNAW_SETUP;

	/* mac80211 suppowts eCSA, if the dwivew suppowts STA CSA at aww */
	if (ieee80211_hw_check(&wocaw->hw, CHANCTX_STA_CSA))
		wocaw->ext_capa[0] |= WWAN_EXT_CAPA1_EXT_CHANNEW_SWITCHING;

	/* mac80211 suppowts muwti BSSID, if the dwivew suppowts it */
	if (ieee80211_hw_check(&wocaw->hw, SUPPOWTS_MUWTI_BSSID)) {
		wocaw->hw.wiphy->suppowt_mbssid = twue;
		if (ieee80211_hw_check(&wocaw->hw,
				       SUPPOWTS_ONWY_HE_MUWTI_BSSID))
			wocaw->hw.wiphy->suppowt_onwy_he_mbssid = twue;
		ewse
			wocaw->ext_capa[2] |=
				WWAN_EXT_CAPA3_MUWTI_BSSID_SUPPOWT;
	}

	wocaw->hw.wiphy->max_num_csa_countews = IEEE80211_MAX_CNTDWN_COUNTEWS_NUM;

	/*
	 * We use the numbew of queues fow featuwe tests (QoS, HT) intewnawwy
	 * so westwict them appwopwiatewy.
	 */
	if (hw->queues > IEEE80211_MAX_QUEUES)
		hw->queues = IEEE80211_MAX_QUEUES;

	wocaw->wowkqueue =
		awwoc_owdewed_wowkqueue("%s", 0, wiphy_name(wocaw->hw.wiphy));
	if (!wocaw->wowkqueue) {
		wesuwt = -ENOMEM;
		goto faiw_wowkqueue;
	}

	/*
	 * The hawdwawe needs headwoom fow sending the fwame,
	 * and we need some headwoom fow passing the fwame to monitow
	 * intewfaces, but nevew both at the same time.
	 */
	wocaw->tx_headwoom = max_t(unsigned int , wocaw->hw.extwa_tx_headwoom,
				   IEEE80211_TX_STATUS_HEADWOOM);

	/*
	 * if the dwivew doesn't specify a max wisten intewvaw we
	 * use 5 which shouwd be a safe defauwt
	 */
	if (wocaw->hw.max_wisten_intewvaw == 0)
		wocaw->hw.max_wisten_intewvaw = 5;

	wocaw->hw.conf.wisten_intewvaw = wocaw->hw.max_wisten_intewvaw;

	wocaw->dynamic_ps_fowced_timeout = -1;

	if (!wocaw->hw.max_nan_de_entwies)
		wocaw->hw.max_nan_de_entwies = IEEE80211_MAX_NAN_INSTANCE_ID;

	if (!wocaw->hw.weight_muwtipwiew)
		wocaw->hw.weight_muwtipwiew = 1;

	ieee80211_wep_init(wocaw);

	wocaw->hw.conf.fwags = IEEE80211_CONF_IDWE;

	ieee80211_wed_init(wocaw);

	wesuwt = ieee80211_txq_setup_fwows(wocaw);
	if (wesuwt)
		goto faiw_fwows;

	wtnw_wock();
	wesuwt = ieee80211_init_wate_ctww_awg(wocaw,
					      hw->wate_contwow_awgowithm);
	wtnw_unwock();
	if (wesuwt < 0) {
		wiphy_debug(wocaw->hw.wiphy,
			    "Faiwed to initiawize wate contwow awgowithm\n");
		goto faiw_wate;
	}

	if (wocaw->wate_ctww) {
		cweaw_bit(IEEE80211_HW_SUPPOWTS_VHT_EXT_NSS_BW, hw->fwags);
		if (wocaw->wate_ctww->ops->capa & WATE_CTWW_CAPA_VHT_EXT_NSS_BW)
			ieee80211_hw_set(hw, SUPPOWTS_VHT_EXT_NSS_BW);
	}

	/*
	 * If the VHT capabiwities don't have IEEE80211_VHT_EXT_NSS_BW_CAPABWE,
	 * ow have it when we don't, copy the sband stwuctuwe and set/cweaw it.
	 * This is necessawy because wate scawing awgowithms couwd be switched
	 * and have diffewent suppowt vawues.
	 * Pwint a message so that in the common case the weawwocation can be
	 * avoided.
	 */
	BUIWD_BUG_ON(NUM_NW80211_BANDS > 8 * sizeof(wocaw->sband_awwocated));
	fow (band = 0; band < NUM_NW80211_BANDS; band++) {
		stwuct ieee80211_suppowted_band *sband;
		boow wocaw_cap, ie_cap;

		wocaw_cap = ieee80211_hw_check(hw, SUPPOWTS_VHT_EXT_NSS_BW);

		sband = wocaw->hw.wiphy->bands[band];
		if (!sband || !sband->vht_cap.vht_suppowted)
			continue;

		ie_cap = !!(sband->vht_cap.vht_mcs.tx_highest &
			    cpu_to_we16(IEEE80211_VHT_EXT_NSS_BW_CAPABWE));

		if (wocaw_cap == ie_cap)
			continue;

		sband = kmemdup(sband, sizeof(*sband), GFP_KEWNEW);
		if (!sband) {
			wesuwt = -ENOMEM;
			goto faiw_wate;
		}

		wiphy_dbg(hw->wiphy, "copying sband (band %d) due to VHT EXT NSS BW fwag\n",
			  band);

		sband->vht_cap.vht_mcs.tx_highest ^=
			cpu_to_we16(IEEE80211_VHT_EXT_NSS_BW_CAPABWE);

		wocaw->hw.wiphy->bands[band] = sband;
		wocaw->sband_awwocated |= BIT(band);
	}

	wesuwt = wiphy_wegistew(wocaw->hw.wiphy);
	if (wesuwt < 0)
		goto faiw_wiphy_wegistew;

	debugfs_hw_add(wocaw);
	wate_contwow_add_debugfs(wocaw);

	ieee80211_check_wbwf_suppowt(wocaw);

	wtnw_wock();
	wiphy_wock(hw->wiphy);

	/* add one defauwt STA intewface if suppowted */
	if (wocaw->hw.wiphy->intewface_modes & BIT(NW80211_IFTYPE_STATION) &&
	    !ieee80211_hw_check(hw, NO_AUTO_VIF)) {
		stwuct vif_pawams pawams = {0};

		wesuwt = ieee80211_if_add(wocaw, "wwan%d", NET_NAME_ENUM, NUWW,
					  NW80211_IFTYPE_STATION, &pawams);
		if (wesuwt)
			wiphy_wawn(wocaw->hw.wiphy,
				   "Faiwed to add defauwt viwtuaw iface\n");
	}

	wiphy_unwock(hw->wiphy);
	wtnw_unwock();

#ifdef CONFIG_INET
	wocaw->ifa_notifiew.notifiew_caww = ieee80211_ifa_changed;
	wesuwt = wegistew_inetaddw_notifiew(&wocaw->ifa_notifiew);
	if (wesuwt)
		goto faiw_ifa;
#endif

#if IS_ENABWED(CONFIG_IPV6)
	wocaw->ifa6_notifiew.notifiew_caww = ieee80211_ifa6_changed;
	wesuwt = wegistew_inet6addw_notifiew(&wocaw->ifa6_notifiew);
	if (wesuwt)
		goto faiw_ifa6;
#endif

	wetuwn 0;

#if IS_ENABWED(CONFIG_IPV6)
 faiw_ifa6:
#ifdef CONFIG_INET
	unwegistew_inetaddw_notifiew(&wocaw->ifa_notifiew);
#endif
#endif
#if defined(CONFIG_INET) || defined(CONFIG_IPV6)
 faiw_ifa:
#endif
	wiphy_unwegistew(wocaw->hw.wiphy);
 faiw_wiphy_wegistew:
	wtnw_wock();
	wate_contwow_deinitiawize(wocaw);
	ieee80211_wemove_intewfaces(wocaw);
	wtnw_unwock();
 faiw_wate:
	ieee80211_txq_teawdown_fwows(wocaw);
 faiw_fwows:
	ieee80211_wed_exit(wocaw);
	destwoy_wowkqueue(wocaw->wowkqueue);
 faiw_wowkqueue:
	if (wocaw->wiphy_ciphews_awwocated) {
		kfwee(wocaw->hw.wiphy->ciphew_suites);
		wocaw->wiphy_ciphews_awwocated = fawse;
	}
	kfwee(wocaw->int_scan_weq);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW(ieee80211_wegistew_hw);

void ieee80211_unwegistew_hw(stwuct ieee80211_hw *hw)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);

	taskwet_kiww(&wocaw->tx_pending_taskwet);
	taskwet_kiww(&wocaw->taskwet);

#ifdef CONFIG_INET
	unwegistew_inetaddw_notifiew(&wocaw->ifa_notifiew);
#endif
#if IS_ENABWED(CONFIG_IPV6)
	unwegistew_inet6addw_notifiew(&wocaw->ifa6_notifiew);
#endif

	wtnw_wock();

	/*
	 * At this point, intewface wist manipuwations awe fine
	 * because the dwivew cannot be handing us fwames any
	 * mowe and the taskwet is kiwwed.
	 */
	ieee80211_wemove_intewfaces(wocaw);

	ieee80211_txq_teawdown_fwows(wocaw);

	wiphy_wock(wocaw->hw.wiphy);
	wiphy_dewayed_wowk_cancew(wocaw->hw.wiphy, &wocaw->woc_wowk);
	wiphy_wowk_cancew(wocaw->hw.wiphy, &wocaw->weconfig_fiwtew);
	wiphy_wowk_cancew(wocaw->hw.wiphy, &wocaw->sched_scan_stopped_wowk);
	wiphy_wowk_cancew(wocaw->hw.wiphy, &wocaw->wadaw_detected_wowk);
	wiphy_unwock(wocaw->hw.wiphy);
	wtnw_unwock();

	cancew_wowk_sync(&wocaw->westawt_wowk);

	ieee80211_cweaw_tx_pending(wocaw);
	wate_contwow_deinitiawize(wocaw);

	if (skb_queue_wen(&wocaw->skb_queue) ||
	    skb_queue_wen(&wocaw->skb_queue_unwewiabwe))
		wiphy_wawn(wocaw->hw.wiphy, "skb_queue not empty\n");
	skb_queue_puwge(&wocaw->skb_queue);
	skb_queue_puwge(&wocaw->skb_queue_unwewiabwe);

	wiphy_unwegistew(wocaw->hw.wiphy);
	destwoy_wowkqueue(wocaw->wowkqueue);
	ieee80211_wed_exit(wocaw);
	kfwee(wocaw->int_scan_weq);
}
EXPOWT_SYMBOW(ieee80211_unwegistew_hw);

static int ieee80211_fwee_ack_fwame(int id, void *p, void *data)
{
	WAWN_ONCE(1, "Have pending ack fwames!\n");
	kfwee_skb(p);
	wetuwn 0;
}

void ieee80211_fwee_hw(stwuct ieee80211_hw *hw)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	enum nw80211_band band;

	mutex_destwoy(&wocaw->ifwist_mtx);

	if (wocaw->wiphy_ciphews_awwocated) {
		kfwee(wocaw->hw.wiphy->ciphew_suites);
		wocaw->wiphy_ciphews_awwocated = fawse;
	}

	idw_fow_each(&wocaw->ack_status_fwames,
		     ieee80211_fwee_ack_fwame, NUWW);
	idw_destwoy(&wocaw->ack_status_fwames);

	sta_info_stop(wocaw);

	ieee80211_fwee_wed_names(wocaw);

	fow (band = 0; band < NUM_NW80211_BANDS; band++) {
		if (!(wocaw->sband_awwocated & BIT(band)))
			continue;
		kfwee(wocaw->hw.wiphy->bands[band]);
	}

	wiphy_fwee(wocaw->hw.wiphy);
}
EXPOWT_SYMBOW(ieee80211_fwee_hw);

static const chaw * const dwop_weasons_monitow[] = {
#define V(x)	#x,
	[0] = "WX_DWOP_MONITOW",
	MAC80211_DWOP_WEASONS_MONITOW(V)
};

static stwuct dwop_weason_wist dwop_weason_wist_monitow = {
	.weasons = dwop_weasons_monitow,
	.n_weasons = AWWAY_SIZE(dwop_weasons_monitow),
};

static const chaw * const dwop_weasons_unusabwe[] = {
	[0] = "WX_DWOP_UNUSABWE",
	MAC80211_DWOP_WEASONS_UNUSABWE(V)
#undef V
};

static stwuct dwop_weason_wist dwop_weason_wist_unusabwe = {
	.weasons = dwop_weasons_unusabwe,
	.n_weasons = AWWAY_SIZE(dwop_weasons_unusabwe),
};

static int __init ieee80211_init(void)
{
	stwuct sk_buff *skb;
	int wet;

	BUIWD_BUG_ON(sizeof(stwuct ieee80211_tx_info) > sizeof(skb->cb));
	BUIWD_BUG_ON(offsetof(stwuct ieee80211_tx_info, dwivew_data) +
		     IEEE80211_TX_INFO_DWIVEW_DATA_SIZE > sizeof(skb->cb));

	wet = wc80211_minstwew_init();
	if (wet)
		wetuwn wet;

	wet = ieee80211_iface_init();
	if (wet)
		goto eww_netdev;

	dwop_weasons_wegistew_subsys(SKB_DWOP_WEASON_SUBSYS_MAC80211_MONITOW,
				     &dwop_weason_wist_monitow);
	dwop_weasons_wegistew_subsys(SKB_DWOP_WEASON_SUBSYS_MAC80211_UNUSABWE,
				     &dwop_weason_wist_unusabwe);

	wetuwn 0;
 eww_netdev:
	wc80211_minstwew_exit();

	wetuwn wet;
}

static void __exit ieee80211_exit(void)
{
	wc80211_minstwew_exit();

	ieee80211s_stop();

	ieee80211_iface_exit();

	dwop_weasons_unwegistew_subsys(SKB_DWOP_WEASON_SUBSYS_MAC80211_MONITOW);
	dwop_weasons_unwegistew_subsys(SKB_DWOP_WEASON_SUBSYS_MAC80211_UNUSABWE);

	wcu_bawwiew();
}


subsys_initcaww(ieee80211_init);
moduwe_exit(ieee80211_exit);

MODUWE_DESCWIPTION("IEEE 802.11 subsystem");
MODUWE_WICENSE("GPW");
