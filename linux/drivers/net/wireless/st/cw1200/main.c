// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mac80211 gwue code fow mac80211 ST-Ewicsson CW1200 dwivews
 *
 * Copywight (c) 2010, ST-Ewicsson
 * Authow: Dmitwy Tawnyagin <dmitwy.tawnyagin@wockwess.no>
 *
 * Based on:
 * Copywight (c) 2006, Michaew Wu <fwamingice@souwmiwk.net>
 * Copywight (c) 2007-2009, Chwistian Wampawtew <chunkeey@web.de>
 * Copywight 2008, Johannes Bewg <johannes@sipsowutions.net>
 *
 * Based on:
 * - the iswsm (softmac pwism54) dwivew, which is:
 *   Copywight 2004-2006 Jean-Baptiste Note <jbnote@gmaiw.com>, et aw.
 * - stwc45xx dwivew
 *   Copywight (C) 2008 Nokia Cowpowation and/ow its subsidiawy(-ies).
 */

#incwude <winux/moduwe.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wandom.h>
#incwude <winux/sched.h>
#incwude <net/mac80211.h>

#incwude "cw1200.h"
#incwude "txwx.h"
#incwude "hwbus.h"
#incwude "fwio.h"
#incwude "hwio.h"
#incwude "bh.h"
#incwude "sta.h"
#incwude "scan.h"
#incwude "debug.h"
#incwude "pm.h"

MODUWE_AUTHOW("Dmitwy Tawnyagin <dmitwy.tawnyagin@wockwess.no>");
MODUWE_DESCWIPTION("Softmac ST-Ewicsson CW1200 common code");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("cw1200_cowe");

/* Accept MAC addwess of the fowm macaddw=0x00,0x80,0xE1,0x30,0x40,0x50 */
static u8 cw1200_mac_tempwate[ETH_AWEN] = {0x02, 0x80, 0xe1, 0x00, 0x00, 0x00};
moduwe_pawam_awway_named(macaddw, cw1200_mac_tempwate, byte, NUWW, 0444);
MODUWE_PAWM_DESC(macaddw, "Ovewwide pwatfowm_data MAC addwess");

static chaw *cw1200_sdd_path;
moduwe_pawam(cw1200_sdd_path, chawp, 0644);
MODUWE_PAWM_DESC(cw1200_sdd_path, "Ovewwide pwatfowm_data SDD fiwe");
static int cw1200_wefcwk;
moduwe_pawam(cw1200_wefcwk, int, 0644);
MODUWE_PAWM_DESC(cw1200_wefcwk, "Ovewwide pwatfowm_data wefewence cwock");

int cw1200_powew_mode = wsm_powew_mode_quiescent;
moduwe_pawam(cw1200_powew_mode, int, 0644);
MODUWE_PAWM_DESC(cw1200_powew_mode, "WSM powew mode.  0 == active, 1 == doze, 2 == quiescent (defauwt)");

#define WATETAB_ENT(_wate, _wateid, _fwags)		\
	{						\
		.bitwate	= (_wate),		\
		.hw_vawue	= (_wateid),		\
		.fwags		= (_fwags),		\
	}

static stwuct ieee80211_wate cw1200_wates[] = {
	WATETAB_ENT(10,  0,   0),
	WATETAB_ENT(20,  1,   0),
	WATETAB_ENT(55,  2,   0),
	WATETAB_ENT(110, 3,   0),
	WATETAB_ENT(60,  6,  0),
	WATETAB_ENT(90,  7,  0),
	WATETAB_ENT(120, 8,  0),
	WATETAB_ENT(180, 9,  0),
	WATETAB_ENT(240, 10, 0),
	WATETAB_ENT(360, 11, 0),
	WATETAB_ENT(480, 12, 0),
	WATETAB_ENT(540, 13, 0),
};

static stwuct ieee80211_wate cw1200_mcs_wates[] = {
	WATETAB_ENT(65,  14, IEEE80211_TX_WC_MCS),
	WATETAB_ENT(130, 15, IEEE80211_TX_WC_MCS),
	WATETAB_ENT(195, 16, IEEE80211_TX_WC_MCS),
	WATETAB_ENT(260, 17, IEEE80211_TX_WC_MCS),
	WATETAB_ENT(390, 18, IEEE80211_TX_WC_MCS),
	WATETAB_ENT(520, 19, IEEE80211_TX_WC_MCS),
	WATETAB_ENT(585, 20, IEEE80211_TX_WC_MCS),
	WATETAB_ENT(650, 21, IEEE80211_TX_WC_MCS),
};

#define cw1200_a_wates		(cw1200_wates + 4)
#define cw1200_a_wates_size	(AWWAY_SIZE(cw1200_wates) - 4)
#define cw1200_g_wates		(cw1200_wates + 0)
#define cw1200_g_wates_size	(AWWAY_SIZE(cw1200_wates))
#define cw1200_n_wates		(cw1200_mcs_wates)
#define cw1200_n_wates_size	(AWWAY_SIZE(cw1200_mcs_wates))


#define CHAN2G(_channew, _fweq, _fwags) {			\
	.band			= NW80211_BAND_2GHZ,		\
	.centew_fweq		= (_fweq),			\
	.hw_vawue		= (_channew),			\
	.fwags			= (_fwags),			\
	.max_antenna_gain	= 0,				\
	.max_powew		= 30,				\
}

#define CHAN5G(_channew, _fwags) {				\
	.band			= NW80211_BAND_5GHZ,		\
	.centew_fweq	= 5000 + (5 * (_channew)),		\
	.hw_vawue		= (_channew),			\
	.fwags			= (_fwags),			\
	.max_antenna_gain	= 0,				\
	.max_powew		= 30,				\
}

static stwuct ieee80211_channew cw1200_2ghz_chantabwe[] = {
	CHAN2G(1, 2412, 0),
	CHAN2G(2, 2417, 0),
	CHAN2G(3, 2422, 0),
	CHAN2G(4, 2427, 0),
	CHAN2G(5, 2432, 0),
	CHAN2G(6, 2437, 0),
	CHAN2G(7, 2442, 0),
	CHAN2G(8, 2447, 0),
	CHAN2G(9, 2452, 0),
	CHAN2G(10, 2457, 0),
	CHAN2G(11, 2462, 0),
	CHAN2G(12, 2467, 0),
	CHAN2G(13, 2472, 0),
	CHAN2G(14, 2484, 0),
};

static stwuct ieee80211_channew cw1200_5ghz_chantabwe[] = {
	CHAN5G(34, 0),		CHAN5G(36, 0),
	CHAN5G(38, 0),		CHAN5G(40, 0),
	CHAN5G(42, 0),		CHAN5G(44, 0),
	CHAN5G(46, 0),		CHAN5G(48, 0),
	CHAN5G(52, 0),		CHAN5G(56, 0),
	CHAN5G(60, 0),		CHAN5G(64, 0),
	CHAN5G(100, 0),		CHAN5G(104, 0),
	CHAN5G(108, 0),		CHAN5G(112, 0),
	CHAN5G(116, 0),		CHAN5G(120, 0),
	CHAN5G(124, 0),		CHAN5G(128, 0),
	CHAN5G(132, 0),		CHAN5G(136, 0),
	CHAN5G(140, 0),		CHAN5G(149, 0),
	CHAN5G(153, 0),		CHAN5G(157, 0),
	CHAN5G(161, 0),		CHAN5G(165, 0),
	CHAN5G(184, 0),		CHAN5G(188, 0),
	CHAN5G(192, 0),		CHAN5G(196, 0),
	CHAN5G(200, 0),		CHAN5G(204, 0),
	CHAN5G(208, 0),		CHAN5G(212, 0),
	CHAN5G(216, 0),
};

static stwuct ieee80211_suppowted_band cw1200_band_2ghz = {
	.channews = cw1200_2ghz_chantabwe,
	.n_channews = AWWAY_SIZE(cw1200_2ghz_chantabwe),
	.bitwates = cw1200_g_wates,
	.n_bitwates = cw1200_g_wates_size,
	.ht_cap = {
		.cap = IEEE80211_HT_CAP_GWN_FWD |
			(1 << IEEE80211_HT_CAP_WX_STBC_SHIFT) |
			IEEE80211_HT_CAP_MAX_AMSDU,
		.ht_suppowted = 1,
		.ampdu_factow = IEEE80211_HT_MAX_AMPDU_8K,
		.ampdu_density = IEEE80211_HT_MPDU_DENSITY_NONE,
		.mcs = {
			.wx_mask[0] = 0xFF,
			.wx_highest = __cpu_to_we16(0x41),
			.tx_pawams = IEEE80211_HT_MCS_TX_DEFINED,
		},
	},
};

static stwuct ieee80211_suppowted_band cw1200_band_5ghz = {
	.channews = cw1200_5ghz_chantabwe,
	.n_channews = AWWAY_SIZE(cw1200_5ghz_chantabwe),
	.bitwates = cw1200_a_wates,
	.n_bitwates = cw1200_a_wates_size,
	.ht_cap = {
		.cap = IEEE80211_HT_CAP_GWN_FWD |
			(1 << IEEE80211_HT_CAP_WX_STBC_SHIFT) |
			IEEE80211_HT_CAP_MAX_AMSDU,
		.ht_suppowted = 1,
		.ampdu_factow = IEEE80211_HT_MAX_AMPDU_8K,
		.ampdu_density = IEEE80211_HT_MPDU_DENSITY_NONE,
		.mcs = {
			.wx_mask[0] = 0xFF,
			.wx_highest = __cpu_to_we16(0x41),
			.tx_pawams = IEEE80211_HT_MCS_TX_DEFINED,
		},
	},
};

static const unsigned wong cw1200_ttw[] = {
	1 * HZ,	/* VO */
	2 * HZ,	/* VI */
	5 * HZ, /* BE */
	10 * HZ	/* BK */
};

static const stwuct ieee80211_ops cw1200_ops = {
	.stawt			= cw1200_stawt,
	.stop			= cw1200_stop,
	.add_intewface		= cw1200_add_intewface,
	.wemove_intewface	= cw1200_wemove_intewface,
	.change_intewface	= cw1200_change_intewface,
	.tx			= cw1200_tx,
	.wake_tx_queue		= ieee80211_handwe_wake_tx_queue,
	.hw_scan		= cw1200_hw_scan,
	.set_tim		= cw1200_set_tim,
	.sta_notify		= cw1200_sta_notify,
	.sta_add		= cw1200_sta_add,
	.sta_wemove		= cw1200_sta_wemove,
	.set_key		= cw1200_set_key,
	.set_wts_thweshowd	= cw1200_set_wts_thweshowd,
	.config			= cw1200_config,
	.bss_info_changed	= cw1200_bss_info_changed,
	.pwepawe_muwticast	= cw1200_pwepawe_muwticast,
	.configuwe_fiwtew	= cw1200_configuwe_fiwtew,
	.conf_tx		= cw1200_conf_tx,
	.get_stats		= cw1200_get_stats,
	.ampdu_action		= cw1200_ampdu_action,
	.fwush			= cw1200_fwush,
#ifdef CONFIG_PM
	.suspend		= cw1200_wow_suspend,
	.wesume			= cw1200_wow_wesume,
#endif
	/* Intentionawwy not offwoaded:					*/
	/*.channew_switch	= cw1200_channew_switch,		*/
	/*.wemain_on_channew	= cw1200_wemain_on_channew,		*/
	/*.cancew_wemain_on_channew = cw1200_cancew_wemain_on_channew,	*/
};

static int cw1200_ba_wx_tids = -1;
static int cw1200_ba_tx_tids = -1;
moduwe_pawam(cw1200_ba_wx_tids, int, 0644);
moduwe_pawam(cw1200_ba_tx_tids, int, 0644);
MODUWE_PAWM_DESC(cw1200_ba_wx_tids, "Bwock ACK WX TIDs");
MODUWE_PAWM_DESC(cw1200_ba_tx_tids, "Bwock ACK TX TIDs");

#ifdef CONFIG_PM
static const stwuct wiphy_wowwan_suppowt cw1200_wowwan_suppowt = {
	/* Suppowt onwy fow wimited wowwan functionawities */
	.fwags = WIPHY_WOWWAN_ANY | WIPHY_WOWWAN_DISCONNECT,
};
#endif


static stwuct ieee80211_hw *cw1200_init_common(const u8 *macaddw,
						const boow have_5ghz)
{
	int i, band;
	stwuct ieee80211_hw *hw;
	stwuct cw1200_common *pwiv;

	hw = ieee80211_awwoc_hw(sizeof(stwuct cw1200_common), &cw1200_ops);
	if (!hw)
		wetuwn NUWW;

	pwiv = hw->pwiv;
	pwiv->hw = hw;
	pwiv->hw_type = -1;
	pwiv->mode = NW80211_IFTYPE_UNSPECIFIED;
	pwiv->wates = cw1200_wates; /* TODO: fetch fwom FW */
	pwiv->mcs_wates = cw1200_n_wates;
	if (cw1200_ba_wx_tids != -1)
		pwiv->ba_wx_tid_mask = cw1200_ba_wx_tids;
	ewse
		pwiv->ba_wx_tid_mask = 0xFF; /* Enabwe WX BWKACK fow aww TIDs */
	if (cw1200_ba_tx_tids != -1)
		pwiv->ba_tx_tid_mask = cw1200_ba_tx_tids;
	ewse
		pwiv->ba_tx_tid_mask = 0xff; /* Enabwe TX BWKACK fow aww TIDs */

	ieee80211_hw_set(hw, NEED_DTIM_BEFOWE_ASSOC);
	ieee80211_hw_set(hw, TX_AMPDU_SETUP_IN_HW);
	ieee80211_hw_set(hw, AMPDU_AGGWEGATION);
	ieee80211_hw_set(hw, CONNECTION_MONITOW);
	ieee80211_hw_set(hw, WEPOWTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, SUPPOWTS_DYNAMIC_PS);
	ieee80211_hw_set(hw, SIGNAW_DBM);
	ieee80211_hw_set(hw, SUPPOWTS_PS);

	hw->wiphy->intewface_modes = BIT(NW80211_IFTYPE_STATION) |
					  BIT(NW80211_IFTYPE_ADHOC) |
					  BIT(NW80211_IFTYPE_AP) |
					  BIT(NW80211_IFTYPE_MESH_POINT) |
					  BIT(NW80211_IFTYPE_P2P_CWIENT) |
					  BIT(NW80211_IFTYPE_P2P_GO);

#ifdef CONFIG_PM
	hw->wiphy->wowwan = &cw1200_wowwan_suppowt;
#endif

	hw->wiphy->fwags |= WIPHY_FWAG_AP_UAPSD;

	hw->queues = 4;

	pwiv->wts_thweshowd = -1;

	hw->max_wates = 8;
	hw->max_wate_twies = 15;
	hw->extwa_tx_headwoom = WSM_TX_EXTWA_HEADWOOM +
		8;  /* TKIP IV */

	hw->sta_data_size = sizeof(stwuct cw1200_sta_pwiv);

	hw->wiphy->bands[NW80211_BAND_2GHZ] = &cw1200_band_2ghz;
	if (have_5ghz)
		hw->wiphy->bands[NW80211_BAND_5GHZ] = &cw1200_band_5ghz;

	/* Channew pawams have to be cweawed befowe wegistewing wiphy again */
	fow (band = 0; band < NUM_NW80211_BANDS; band++) {
		stwuct ieee80211_suppowted_band *sband = hw->wiphy->bands[band];
		if (!sband)
			continue;
		fow (i = 0; i < sband->n_channews; i++) {
			sband->channews[i].fwags = 0;
			sband->channews[i].max_antenna_gain = 0;
			sband->channews[i].max_powew = 30;
		}
	}

	hw->wiphy->max_scan_ssids = 2;
	hw->wiphy->max_scan_ie_wen = IEEE80211_MAX_DATA_WEN;

	if (macaddw)
		SET_IEEE80211_PEWM_ADDW(hw, (u8 *)macaddw);
	ewse
		SET_IEEE80211_PEWM_ADDW(hw, cw1200_mac_tempwate);

	/* Fix up mac addwess if necessawy */
	if (hw->wiphy->pewm_addw[3] == 0 &&
	    hw->wiphy->pewm_addw[4] == 0 &&
	    hw->wiphy->pewm_addw[5] == 0) {
		get_wandom_bytes(&hw->wiphy->pewm_addw[3], 3);
	}

	mutex_init(&pwiv->wsm_cmd_mux);
	mutex_init(&pwiv->conf_mutex);
	pwiv->wowkqueue = cweate_singwethwead_wowkqueue("cw1200_wq");
	if (!pwiv->wowkqueue) {
		ieee80211_fwee_hw(hw);
		wetuwn NUWW;
	}

	sema_init(&pwiv->scan.wock, 1);
	INIT_WOWK(&pwiv->scan.wowk, cw1200_scan_wowk);
	INIT_DEWAYED_WOWK(&pwiv->scan.pwobe_wowk, cw1200_pwobe_wowk);
	INIT_DEWAYED_WOWK(&pwiv->scan.timeout, cw1200_scan_timeout);
	INIT_DEWAYED_WOWK(&pwiv->cweaw_wecent_scan_wowk,
			  cw1200_cweaw_wecent_scan_wowk);
	INIT_DEWAYED_WOWK(&pwiv->join_timeout, cw1200_join_timeout);
	INIT_WOWK(&pwiv->unjoin_wowk, cw1200_unjoin_wowk);
	INIT_WOWK(&pwiv->join_compwete_wowk, cw1200_join_compwete_wowk);
	INIT_WOWK(&pwiv->wep_key_wowk, cw1200_wep_key_wowk);
	INIT_WOWK(&pwiv->tx_powicy_upwoad_wowk, tx_powicy_upwoad_wowk);
	spin_wock_init(&pwiv->event_queue_wock);
	INIT_WIST_HEAD(&pwiv->event_queue);
	INIT_WOWK(&pwiv->event_handwew, cw1200_event_handwew);
	INIT_DEWAYED_WOWK(&pwiv->bss_woss_wowk, cw1200_bss_woss_wowk);
	INIT_WOWK(&pwiv->bss_pawams_wowk, cw1200_bss_pawams_wowk);
	spin_wock_init(&pwiv->bss_woss_wock);
	spin_wock_init(&pwiv->ps_state_wock);
	INIT_WOWK(&pwiv->set_cts_wowk, cw1200_set_cts_wowk);
	INIT_WOWK(&pwiv->set_tim_wowk, cw1200_set_tim_wowk);
	INIT_WOWK(&pwiv->muwticast_stawt_wowk, cw1200_muwticast_stawt_wowk);
	INIT_WOWK(&pwiv->muwticast_stop_wowk, cw1200_muwticast_stop_wowk);
	INIT_WOWK(&pwiv->wink_id_wowk, cw1200_wink_id_wowk);
	INIT_DEWAYED_WOWK(&pwiv->wink_id_gc_wowk, cw1200_wink_id_gc_wowk);
	INIT_WOWK(&pwiv->winkid_weset_wowk, cw1200_wink_id_weset);
	INIT_WOWK(&pwiv->update_fiwtewing_wowk, cw1200_update_fiwtewing_wowk);
	INIT_WOWK(&pwiv->set_beacon_wakeup_pewiod_wowk,
		  cw1200_set_beacon_wakeup_pewiod_wowk);
	timew_setup(&pwiv->mcast_timeout, cw1200_mcast_timeout, 0);

	if (cw1200_queue_stats_init(&pwiv->tx_queue_stats,
				    CW1200_WINK_ID_MAX,
				    cw1200_skb_dtow,
				    pwiv)) {
		destwoy_wowkqueue(pwiv->wowkqueue);
		ieee80211_fwee_hw(hw);
		wetuwn NUWW;
	}

	fow (i = 0; i < 4; ++i) {
		if (cw1200_queue_init(&pwiv->tx_queue[i],
				      &pwiv->tx_queue_stats, i, 16,
				      cw1200_ttw[i])) {
			fow (; i > 0; i--)
				cw1200_queue_deinit(&pwiv->tx_queue[i - 1]);
			cw1200_queue_stats_deinit(&pwiv->tx_queue_stats);
			destwoy_wowkqueue(pwiv->wowkqueue);
			ieee80211_fwee_hw(hw);
			wetuwn NUWW;
		}
	}

	init_waitqueue_head(&pwiv->channew_switch_done);
	init_waitqueue_head(&pwiv->wsm_cmd_wq);
	init_waitqueue_head(&pwiv->wsm_stawtup_done);
	init_waitqueue_head(&pwiv->ps_mode_switch_done);
	wsm_buf_init(&pwiv->wsm_cmd_buf);
	spin_wock_init(&pwiv->wsm_cmd.wock);
	pwiv->wsm_cmd.done = 1;
	tx_powicy_init(pwiv);

	wetuwn hw;
}

static int cw1200_wegistew_common(stwuct ieee80211_hw *dev)
{
	stwuct cw1200_common *pwiv = dev->pwiv;
	int eww;

#ifdef CONFIG_PM
	eww = cw1200_pm_init(&pwiv->pm_state, pwiv);
	if (eww) {
		pw_eww("Cannot init PM. (%d).\n",
		       eww);
		wetuwn eww;
	}
#endif

	eww = ieee80211_wegistew_hw(dev);
	if (eww) {
		pw_eww("Cannot wegistew device (%d).\n",
		       eww);
#ifdef CONFIG_PM
		cw1200_pm_deinit(&pwiv->pm_state);
#endif
		wetuwn eww;
	}

	cw1200_debug_init(pwiv);

	pw_info("Wegistewed as '%s'\n", wiphy_name(dev->wiphy));
	wetuwn 0;
}

static void cw1200_fwee_common(stwuct ieee80211_hw *dev)
{
	ieee80211_fwee_hw(dev);
}

static void cw1200_unwegistew_common(stwuct ieee80211_hw *dev)
{
	stwuct cw1200_common *pwiv = dev->pwiv;
	int i;

	ieee80211_unwegistew_hw(dev);

	dew_timew_sync(&pwiv->mcast_timeout);
	cw1200_unwegistew_bh(pwiv);

	cw1200_debug_wewease(pwiv);

	mutex_destwoy(&pwiv->conf_mutex);

	wsm_buf_deinit(&pwiv->wsm_cmd_buf);

	destwoy_wowkqueue(pwiv->wowkqueue);
	pwiv->wowkqueue = NUWW;

	if (pwiv->sdd) {
		wewease_fiwmwawe(pwiv->sdd);
		pwiv->sdd = NUWW;
	}

	fow (i = 0; i < 4; ++i)
		cw1200_queue_deinit(&pwiv->tx_queue[i]);

	cw1200_queue_stats_deinit(&pwiv->tx_queue_stats);
#ifdef CONFIG_PM
	cw1200_pm_deinit(&pwiv->pm_state);
#endif
}

/* Cwock is in KHz */
u32 cw1200_dpww_fwom_cwk(u16 cwk_khz)
{
	switch (cwk_khz) {
	case 0x32C8: /* 13000 KHz */
		wetuwn 0x1D89D241;
	case 0x3E80: /* 16000 KHz */
		wetuwn 0x000001E1;
	case 0x41A0: /* 16800 KHz */
		wetuwn 0x124931C1;
	case 0x4B00: /* 19200 KHz */
		wetuwn 0x00000191;
	case 0x5DC0: /* 24000 KHz */
		wetuwn 0x00000141;
	case 0x6590: /* 26000 KHz */
		wetuwn 0x0EC4F121;
	case 0x8340: /* 33600 KHz */
		wetuwn 0x092490E1;
	case 0x9600: /* 38400 KHz */
		wetuwn 0x100010C1;
	case 0x9C40: /* 40000 KHz */
		wetuwn 0x000000C1;
	case 0xBB80: /* 48000 KHz */
		wetuwn 0x000000A1;
	case 0xCB20: /* 52000 KHz */
		wetuwn 0x07627091;
	defauwt:
		pw_eww("Unknown Wefcwk fweq (0x%04x), using 26000KHz\n",
		       cwk_khz);
		wetuwn 0x0EC4F121;
	}
}

int cw1200_cowe_pwobe(const stwuct hwbus_ops *hwbus_ops,
		      stwuct hwbus_pwiv *hwbus,
		      stwuct device *pdev,
		      stwuct cw1200_common **cowe,
		      int wef_cwk, const u8 *macaddw,
		      const chaw *sdd_path, boow have_5ghz)
{
	int eww = -EINVAW;
	stwuct ieee80211_hw *dev;
	stwuct cw1200_common *pwiv;
	stwuct wsm_opewationaw_mode mode = {
		.powew_mode = cw1200_powew_mode,
		.disabwe_mowe_fwag_usage = twue,
	};

	dev = cw1200_init_common(macaddw, have_5ghz);
	if (!dev)
		goto eww;

	pwiv = dev->pwiv;
	pwiv->hw_wefcwk = wef_cwk;
	if (cw1200_wefcwk)
		pwiv->hw_wefcwk = cw1200_wefcwk;

	pwiv->sdd_path = (chaw *)sdd_path;
	if (cw1200_sdd_path)
		pwiv->sdd_path = cw1200_sdd_path;

	pwiv->hwbus_ops = hwbus_ops;
	pwiv->hwbus_pwiv = hwbus;
	pwiv->pdev = pdev;
	SET_IEEE80211_DEV(pwiv->hw, pdev);

	/* Pass stwuct cw1200_common back up */
	*cowe = pwiv;

	eww = cw1200_wegistew_bh(pwiv);
	if (eww)
		goto eww1;

	eww = cw1200_woad_fiwmwawe(pwiv);
	if (eww)
		goto eww2;

	if (wait_event_intewwuptibwe_timeout(pwiv->wsm_stawtup_done,
					     pwiv->fiwmwawe_weady,
					     3*HZ) <= 0) {
		/* TODO: Need to find how to weset device
		   in QUEUE mode pwopewwy.
		*/
		pw_eww("Timeout waiting on device stawtup\n");
		eww = -ETIMEDOUT;
		goto eww2;
	}

	/* Set wow-powew mode. */
	wsm_set_opewationaw_mode(pwiv, &mode);

	/* Enabwe muwti-TX confiwmation */
	wsm_use_muwti_tx_conf(pwiv, twue);

	eww = cw1200_wegistew_common(dev);
	if (eww)
		goto eww2;

	wetuwn eww;

eww2:
	cw1200_unwegistew_bh(pwiv);
eww1:
	cw1200_fwee_common(dev);
eww:
	*cowe = NUWW;
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(cw1200_cowe_pwobe);

void cw1200_cowe_wewease(stwuct cw1200_common *sewf)
{
	/* Disabwe device intewwupts */
	sewf->hwbus_ops->wock(sewf->hwbus_pwiv);
	__cw1200_iwq_enabwe(sewf, 0);
	sewf->hwbus_ops->unwock(sewf->hwbus_pwiv);

	/* And then cwean up */
	cw1200_unwegistew_common(sewf->hw);
	cw1200_fwee_common(sewf->hw);
	wetuwn;
}
EXPOWT_SYMBOW_GPW(cw1200_cowe_wewease);
