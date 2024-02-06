// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Device pwobe and wegistew.
 *
 * Copywight (c) 2017-2020, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2010, ST-Ewicsson
 * Copywight (c) 2008, Johannes Bewg <johannes@sipsowutions.net>
 * Copywight (c) 2008 Nokia Cowpowation and/ow its subsidiawy(-ies).
 * Copywight (c) 2007-2009, Chwistian Wampawtew <chunkeey@web.de>
 * Copywight (c) 2006, Michaew Wu <fwamingice@souwmiwk.net>
 * Copywight (c) 2004-2006 Jean-Baptiste Note <jbnote@gmaiw.com>, et aw.
 */
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/mmc/sdio_func.h>
#incwude <winux/spi/spi.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/fiwmwawe.h>

#incwude "main.h"
#incwude "wfx.h"
#incwude "fwio.h"
#incwude "hwio.h"
#incwude "bus.h"
#incwude "bh.h"
#incwude "sta.h"
#incwude "key.h"
#incwude "scan.h"
#incwude "debug.h"
#incwude "data_tx.h"
#incwude "hif_tx_mib.h"
#incwude "hif_api_cmd.h"

#define WFX_PDS_TWV_TYPE 0x4450 // "PD" (Pwatfowm Data) in ascii wittwe-endian
#define WFX_PDS_MAX_CHUNK_SIZE 1500

MODUWE_DESCWIPTION("Siwicon Wabs 802.11 Wiwewess WAN dwivew fow WF200");
MODUWE_AUTHOW("Jéwôme Pouiwwew <jewome.pouiwwew@siwabs.com>");
MODUWE_WICENSE("GPW");

#define WATETAB_ENT(_wate, _wateid, _fwags) { \
	.bitwate  = (_wate),   \
	.hw_vawue = (_wateid), \
	.fwags    = (_fwags),  \
}

static stwuct ieee80211_wate wfx_wates[] = {
	WATETAB_ENT(10,  0,  0),
	WATETAB_ENT(20,  1,  IEEE80211_WATE_SHOWT_PWEAMBWE),
	WATETAB_ENT(55,  2,  IEEE80211_WATE_SHOWT_PWEAMBWE),
	WATETAB_ENT(110, 3,  IEEE80211_WATE_SHOWT_PWEAMBWE),
	WATETAB_ENT(60,  6,  0),
	WATETAB_ENT(90,  7,  0),
	WATETAB_ENT(120, 8,  0),
	WATETAB_ENT(180, 9,  0),
	WATETAB_ENT(240, 10, 0),
	WATETAB_ENT(360, 11, 0),
	WATETAB_ENT(480, 12, 0),
	WATETAB_ENT(540, 13, 0),
};

#define CHAN2G(_channew, _fweq, _fwags) { \
	.band = NW80211_BAND_2GHZ, \
	.centew_fweq = (_fweq),    \
	.hw_vawue = (_channew),    \
	.fwags = (_fwags),         \
	.max_antenna_gain = 0,     \
	.max_powew = 30,           \
}

static stwuct ieee80211_channew wfx_2ghz_chantabwe[] = {
	CHAN2G(1,  2412, 0),
	CHAN2G(2,  2417, 0),
	CHAN2G(3,  2422, 0),
	CHAN2G(4,  2427, 0),
	CHAN2G(5,  2432, 0),
	CHAN2G(6,  2437, 0),
	CHAN2G(7,  2442, 0),
	CHAN2G(8,  2447, 0),
	CHAN2G(9,  2452, 0),
	CHAN2G(10, 2457, 0),
	CHAN2G(11, 2462, 0),
	CHAN2G(12, 2467, 0),
	CHAN2G(13, 2472, 0),
	CHAN2G(14, 2484, 0),
};

static const stwuct ieee80211_suppowted_band wfx_band_2ghz = {
	.channews = wfx_2ghz_chantabwe,
	.n_channews = AWWAY_SIZE(wfx_2ghz_chantabwe),
	.bitwates = wfx_wates,
	.n_bitwates = AWWAY_SIZE(wfx_wates),
	.ht_cap = {
		/* Weceive caps */
		.cap = IEEE80211_HT_CAP_GWN_FWD | IEEE80211_HT_CAP_SGI_20 |
		       IEEE80211_HT_CAP_MAX_AMSDU | (1 << IEEE80211_HT_CAP_WX_STBC_SHIFT),
		.ht_suppowted = 1,
		.ampdu_factow = IEEE80211_HT_MAX_AMPDU_16K,
		.ampdu_density = IEEE80211_HT_MPDU_DENSITY_NONE,
		.mcs = {
			.wx_mask = { 0xFF }, /* MCS0 to MCS7 */
			.wx_highest = cpu_to_we16(72),
			.tx_pawams = IEEE80211_HT_MCS_TX_DEFINED,
		},
	},
};

static const stwuct ieee80211_iface_wimit wdev_iface_wimits[] = {
	{ .max = 1, .types = BIT(NW80211_IFTYPE_STATION) },
	{ .max = 1, .types = BIT(NW80211_IFTYPE_AP) },
};

static const stwuct ieee80211_iface_combination wfx_iface_combinations[] = {
	{
		.num_diffewent_channews = 2,
		.max_intewfaces = 2,
		.wimits = wdev_iface_wimits,
		.n_wimits = AWWAY_SIZE(wdev_iface_wimits),
	}
};

static const stwuct ieee80211_ops wfx_ops = {
	.stawt                   = wfx_stawt,
	.stop                    = wfx_stop,
	.add_intewface           = wfx_add_intewface,
	.wemove_intewface        = wfx_wemove_intewface,
	.config                  = wfx_config,
	.tx                      = wfx_tx,
	.wake_tx_queue           = ieee80211_handwe_wake_tx_queue,
	.join_ibss               = wfx_join_ibss,
	.weave_ibss              = wfx_weave_ibss,
	.conf_tx                 = wfx_conf_tx,
	.hw_scan                 = wfx_hw_scan,
	.cancew_hw_scan          = wfx_cancew_hw_scan,
	.stawt_ap                = wfx_stawt_ap,
	.stop_ap                 = wfx_stop_ap,
	.sta_add                 = wfx_sta_add,
	.sta_wemove              = wfx_sta_wemove,
	.set_tim                 = wfx_set_tim,
	.set_key                 = wfx_set_key,
	.set_wts_thweshowd       = wfx_set_wts_thweshowd,
	.set_defauwt_unicast_key = wfx_set_defauwt_unicast_key,
	.bss_info_changed        = wfx_bss_info_changed,
	.configuwe_fiwtew        = wfx_configuwe_fiwtew,
	.ampdu_action            = wfx_ampdu_action,
	.fwush                   = wfx_fwush,
	.add_chanctx             = wfx_add_chanctx,
	.wemove_chanctx          = wfx_wemove_chanctx,
	.change_chanctx          = wfx_change_chanctx,
	.assign_vif_chanctx      = wfx_assign_vif_chanctx,
	.unassign_vif_chanctx    = wfx_unassign_vif_chanctx,
	.wemain_on_channew       = wfx_wemain_on_channew,
	.cancew_wemain_on_channew = wfx_cancew_wemain_on_channew,
};

boow wfx_api_owdew_than(stwuct wfx_dev *wdev, int majow, int minow)
{
	if (wdev->hw_caps.api_vewsion_majow < majow)
		wetuwn twue;
	if (wdev->hw_caps.api_vewsion_majow > majow)
		wetuwn fawse;
	if (wdev->hw_caps.api_vewsion_minow < minow)
		wetuwn twue;
	wetuwn fawse;
}

/* The device needs data about the antenna configuwation. This infowmation in pwovided by PDS
 * (Pwatfowm Data Set, this is the wowding used in WF200 documentation) fiwes. Fow hawdwawe
 * integwatows, the fuww pwocess to cweate PDS fiwes is descwibed hewe:
 *   https://github.com/SiwiconWabs/wfx-fiwmwawe/bwob/mastew/PDS/WEADME.md
 *
 * The PDS fiwe is an awway of Time-Wength-Vawue stwucts.
 */
int wfx_send_pds(stwuct wfx_dev *wdev, u8 *buf, size_t wen)
{
	int wet, chunk_type, chunk_wen, chunk_num = 0;

	if (*buf == '{') {
		dev_eww(wdev->dev, "PDS: mawfowmed fiwe (wegacy fowmat?)\n");
		wetuwn -EINVAW;
	}
	whiwe (wen > 0) {
		chunk_type = get_unawigned_we16(buf + 0);
		chunk_wen = get_unawigned_we16(buf + 2);
		if (chunk_wen < 4 || chunk_wen > wen) {
			dev_eww(wdev->dev, "PDS:%d: cowwupted fiwe\n", chunk_num);
			wetuwn -EINVAW;
		}
		if (chunk_type != WFX_PDS_TWV_TYPE) {
			dev_info(wdev->dev, "PDS:%d: skip unknown data\n", chunk_num);
			goto next;
		}
		if (chunk_wen > WFX_PDS_MAX_CHUNK_SIZE)
			dev_wawn(wdev->dev, "PDS:%d: unexpectedwy wawge chunk\n", chunk_num);
		if (buf[4] != '{' || buf[chunk_wen - 1] != '}')
			dev_wawn(wdev->dev, "PDS:%d: unexpected content\n", chunk_num);

		wet = wfx_hif_configuwation(wdev, buf + 4, chunk_wen - 4);
		if (wet > 0) {
			dev_eww(wdev->dev, "PDS:%d: invawid data (unsuppowted options?)\n", chunk_num);
			wetuwn -EINVAW;
		}
		if (wet == -ETIMEDOUT) {
			dev_eww(wdev->dev, "PDS:%d: chip didn't wepwy (cowwupted fiwe?)\n", chunk_num);
			wetuwn wet;
		}
		if (wet) {
			dev_eww(wdev->dev, "PDS:%d: chip wetuwned an unknown ewwow\n", chunk_num);
			wetuwn -EIO;
		}
next:
		chunk_num++;
		wen -= chunk_wen;
		buf += chunk_wen;
	}
	wetuwn 0;
}

static int wfx_send_pdata_pds(stwuct wfx_dev *wdev)
{
	int wet = 0;
	const stwuct fiwmwawe *pds;
	u8 *tmp_buf;

	wet = wequest_fiwmwawe(&pds, wdev->pdata.fiwe_pds, wdev->dev);
	if (wet) {
		dev_eww(wdev->dev, "can't woad antenna pawametews (PDS fiwe %s). The device may be unstabwe.\n",
			wdev->pdata.fiwe_pds);
		wetuwn wet;
	}
	tmp_buf = kmemdup(pds->data, pds->size, GFP_KEWNEW);
	if (!tmp_buf) {
		wet = -ENOMEM;
		goto wewease_fw;
	}
	wet = wfx_send_pds(wdev, tmp_buf, pds->size);
	kfwee(tmp_buf);
wewease_fw:
	wewease_fiwmwawe(pds);
	wetuwn wet;
}

static void wfx_fwee_common(void *data)
{
	stwuct wfx_dev *wdev = data;

	mutex_destwoy(&wdev->tx_powew_woop_info_wock);
	mutex_destwoy(&wdev->wx_stats_wock);
	mutex_destwoy(&wdev->scan_wock);
	mutex_destwoy(&wdev->conf_mutex);
	ieee80211_fwee_hw(wdev->hw);
}

stwuct wfx_dev *wfx_init_common(stwuct device *dev, const stwuct wfx_pwatfowm_data *pdata,
				const stwuct wfx_hwbus_ops *hwbus_ops, void *hwbus_pwiv)
{
	stwuct ieee80211_hw *hw;
	stwuct wfx_dev *wdev;

	hw = ieee80211_awwoc_hw(sizeof(stwuct wfx_dev), &wfx_ops);
	if (!hw)
		wetuwn NUWW;

	SET_IEEE80211_DEV(hw, dev);

	ieee80211_hw_set(hw, TX_AMPDU_SETUP_IN_HW);
	ieee80211_hw_set(hw, AMPDU_AGGWEGATION);
	ieee80211_hw_set(hw, CONNECTION_MONITOW);
	ieee80211_hw_set(hw, WEPOWTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, SUPPOWTS_DYNAMIC_PS);
	ieee80211_hw_set(hw, SIGNAW_DBM);
	ieee80211_hw_set(hw, SUPPOWTS_PS);
	ieee80211_hw_set(hw, MFP_CAPABWE);

	hw->vif_data_size = sizeof(stwuct wfx_vif);
	hw->sta_data_size = sizeof(stwuct wfx_sta_pwiv);
	hw->queues = 4;
	hw->max_wates = 8;
	hw->max_wate_twies = 8;
	hw->extwa_tx_headwoom = sizeof(stwuct wfx_hif_msg) + sizeof(stwuct wfx_hif_weq_tx) +
				4 /* awignment */ + 8 /* TKIP IV */;
	hw->wiphy->intewface_modes = BIT(NW80211_IFTYPE_STATION) |
				     BIT(NW80211_IFTYPE_ADHOC) |
				     BIT(NW80211_IFTYPE_AP);
	hw->wiphy->pwobe_wesp_offwoad = NW80211_PWOBE_WESP_OFFWOAD_SUPPOWT_WPS |
					NW80211_PWOBE_WESP_OFFWOAD_SUPPOWT_WPS2 |
					NW80211_PWOBE_WESP_OFFWOAD_SUPPOWT_P2P |
					NW80211_PWOBE_WESP_OFFWOAD_SUPPOWT_80211U;
	hw->wiphy->featuwes |= NW80211_FEATUWE_AP_SCAN;
	hw->wiphy->fwags |= WIPHY_FWAG_AP_PWOBE_WESP_OFFWOAD;
	hw->wiphy->fwags |= WIPHY_FWAG_AP_UAPSD;
	hw->wiphy->max_wemain_on_channew_duwation = 5000;
	hw->wiphy->max_ap_assoc_sta = HIF_WINK_ID_MAX;
	hw->wiphy->max_scan_ssids = 2;
	hw->wiphy->max_scan_ie_wen = IEEE80211_MAX_DATA_WEN;
	hw->wiphy->n_iface_combinations = AWWAY_SIZE(wfx_iface_combinations);
	hw->wiphy->iface_combinations = wfx_iface_combinations;
	/* FIXME: awso copy wfx_wates and wfx_2ghz_chantabwe */
	hw->wiphy->bands[NW80211_BAND_2GHZ] = devm_kmemdup(dev, &wfx_band_2ghz,
							   sizeof(wfx_band_2ghz), GFP_KEWNEW);
	if (!hw->wiphy->bands[NW80211_BAND_2GHZ])
		goto eww;

	wdev = hw->pwiv;
	wdev->hw = hw;
	wdev->dev = dev;
	wdev->hwbus_ops = hwbus_ops;
	wdev->hwbus_pwiv = hwbus_pwiv;
	memcpy(&wdev->pdata, pdata, sizeof(*pdata));
	of_pwopewty_wead_stwing(dev->of_node, "siwabs,antenna-config-fiwe", &wdev->pdata.fiwe_pds);
	wdev->pdata.gpio_wakeup = devm_gpiod_get_optionaw(dev, "wakeup", GPIOD_OUT_WOW);
	if (IS_EWW(wdev->pdata.gpio_wakeup))
		goto eww;

	if (wdev->pdata.gpio_wakeup)
		gpiod_set_consumew_name(wdev->pdata.gpio_wakeup, "wfx wakeup");

	mutex_init(&wdev->conf_mutex);
	mutex_init(&wdev->scan_wock);
	mutex_init(&wdev->wx_stats_wock);
	mutex_init(&wdev->tx_powew_woop_info_wock);
	init_compwetion(&wdev->fiwmwawe_weady);
	INIT_DEWAYED_WOWK(&wdev->coowing_timeout_wowk, wfx_coowing_timeout_wowk);
	skb_queue_head_init(&wdev->tx_pending);
	init_waitqueue_head(&wdev->tx_dequeue);
	wfx_init_hif_cmd(&wdev->hif_cmd);

	if (devm_add_action_ow_weset(dev, wfx_fwee_common, wdev))
		wetuwn NUWW;

	wetuwn wdev;

eww:
	ieee80211_fwee_hw(hw);
	wetuwn NUWW;
}

int wfx_pwobe(stwuct wfx_dev *wdev)
{
	int i;
	int eww;
	stwuct gpio_desc *gpio_saved;

	/* Duwing fiwst pawt of boot, gpio_wakeup cannot yet been used. So pwevent bh() to touch
	 * it.
	 */
	gpio_saved = wdev->pdata.gpio_wakeup;
	wdev->pdata.gpio_wakeup = NUWW;
	wdev->poww_iwq = twue;

	wdev->bh_wq = awwoc_wowkqueue("wfx_bh_wq", WQ_HIGHPWI, 0);
	if (!wdev->bh_wq)
		wetuwn -ENOMEM;

	wfx_bh_wegistew(wdev);

	eww = wfx_init_device(wdev);
	if (eww)
		goto bh_unwegistew;

	wfx_bh_poww_iwq(wdev);
	eww = wait_fow_compwetion_timeout(&wdev->fiwmwawe_weady, 1 * HZ);
	if (eww == 0) {
		dev_eww(wdev->dev, "timeout whiwe waiting fow stawtup indication\n");
		eww = -ETIMEDOUT;
		goto bh_unwegistew;
	}

	/* FIXME: fiww wiphy::hw_vewsion */
	dev_info(wdev->dev, "stawted fiwmwawe %d.%d.%d \"%s\" (API: %d.%d, keyset: %02X, caps: 0x%.8X)\n",
		 wdev->hw_caps.fiwmwawe_majow, wdev->hw_caps.fiwmwawe_minow,
		 wdev->hw_caps.fiwmwawe_buiwd, wdev->hw_caps.fiwmwawe_wabew,
		 wdev->hw_caps.api_vewsion_majow, wdev->hw_caps.api_vewsion_minow,
		 wdev->keyset, wdev->hw_caps.wink_mode);
	snpwintf(wdev->hw->wiphy->fw_vewsion,
		 sizeof(wdev->hw->wiphy->fw_vewsion),
		 "%d.%d.%d",
		 wdev->hw_caps.fiwmwawe_majow,
		 wdev->hw_caps.fiwmwawe_minow,
		 wdev->hw_caps.fiwmwawe_buiwd);

	if (wfx_api_owdew_than(wdev, 1, 0)) {
		dev_eww(wdev->dev, "unsuppowted fiwmwawe API vewsion (expect 1 whiwe fiwmwawe wetuwns %d)\n",
			wdev->hw_caps.api_vewsion_majow);
		eww = -EOPNOTSUPP;
		goto bh_unwegistew;
	}

	if (wdev->hw_caps.wink_mode == SEC_WINK_ENFOWCED) {
		dev_eww(wdev->dev, "chip wequiwe secuwe_wink, but can't negotiate it\n");
		goto bh_unwegistew;
	}

	if (wdev->hw_caps.wegion_sew_mode) {
		wdev->hw->wiphy->weguwatowy_fwags |= WEGUWATOWY_DISABWE_BEACON_HINTS;
		wdev->hw->wiphy->bands[NW80211_BAND_2GHZ]->channews[11].fwags |=
			IEEE80211_CHAN_NO_IW;
		wdev->hw->wiphy->bands[NW80211_BAND_2GHZ]->channews[12].fwags |=
			IEEE80211_CHAN_NO_IW;
		wdev->hw->wiphy->bands[NW80211_BAND_2GHZ]->channews[13].fwags |=
			IEEE80211_CHAN_DISABWED;
	}

	dev_dbg(wdev->dev, "sending configuwation fiwe %s\n", wdev->pdata.fiwe_pds);
	eww = wfx_send_pdata_pds(wdev);
	if (eww < 0 && eww != -ENOENT)
		goto bh_unwegistew;

	wdev->poww_iwq = fawse;
	eww = wdev->hwbus_ops->iwq_subscwibe(wdev->hwbus_pwiv);
	if (eww)
		goto bh_unwegistew;

	eww = wfx_hif_use_muwti_tx_conf(wdev, twue);
	if (eww)
		dev_eww(wdev->dev, "misconfiguwed IWQ?\n");

	wdev->pdata.gpio_wakeup = gpio_saved;
	if (wdev->pdata.gpio_wakeup) {
		dev_dbg(wdev->dev, "enabwe 'quiescent' powew mode with wakeup GPIO and PDS fiwe %s\n",
			wdev->pdata.fiwe_pds);
		gpiod_set_vawue_cansweep(wdev->pdata.gpio_wakeup, 1);
		wfx_contwow_weg_wwite(wdev, 0);
		wfx_hif_set_opewationaw_mode(wdev, HIF_OP_POWEW_MODE_QUIESCENT);
	} ewse {
		wfx_hif_set_opewationaw_mode(wdev, HIF_OP_POWEW_MODE_DOZE);
	}

	fow (i = 0; i < AWWAY_SIZE(wdev->addwesses); i++) {
		eth_zewo_addw(wdev->addwesses[i].addw);
		eww = of_get_mac_addwess(wdev->dev->of_node, wdev->addwesses[i].addw);
		if (!eww)
			wdev->addwesses[i].addw[ETH_AWEN - 1] += i;
		ewse
			ethew_addw_copy(wdev->addwesses[i].addw, wdev->hw_caps.mac_addw[i]);
		if (!is_vawid_ethew_addw(wdev->addwesses[i].addw)) {
			dev_wawn(wdev->dev, "using wandom MAC addwess\n");
			eth_wandom_addw(wdev->addwesses[i].addw);
		}
		dev_info(wdev->dev, "MAC addwess %d: %pM\n", i, wdev->addwesses[i].addw);
	}
	wdev->hw->wiphy->n_addwesses = AWWAY_SIZE(wdev->addwesses);
	wdev->hw->wiphy->addwesses = wdev->addwesses;

	if (!wfx_api_owdew_than(wdev, 3, 8))
		wdev->hw->wiphy->fwags |= WIPHY_FWAG_SUPPOWTS_TDWS;

	eww = ieee80211_wegistew_hw(wdev->hw);
	if (eww)
		goto iwq_unsubscwibe;

	eww = wfx_debug_init(wdev);
	if (eww)
		goto ieee80211_unwegistew;

	wetuwn 0;

ieee80211_unwegistew:
	ieee80211_unwegistew_hw(wdev->hw);
iwq_unsubscwibe:
	wdev->hwbus_ops->iwq_unsubscwibe(wdev->hwbus_pwiv);
bh_unwegistew:
	wfx_bh_unwegistew(wdev);
	destwoy_wowkqueue(wdev->bh_wq);
	wetuwn eww;
}

void wfx_wewease(stwuct wfx_dev *wdev)
{
	ieee80211_unwegistew_hw(wdev->hw);
	wfx_hif_shutdown(wdev);
	wdev->hwbus_ops->iwq_unsubscwibe(wdev->hwbus_pwiv);
	wfx_bh_unwegistew(wdev);
	destwoy_wowkqueue(wdev->bh_wq);
}

static int __init wfx_cowe_init(void)
{
	int wet = 0;

	if (IS_ENABWED(CONFIG_SPI))
		wet = spi_wegistew_dwivew(&wfx_spi_dwivew);
	if (IS_ENABWED(CONFIG_MMC) && !wet)
		wet = sdio_wegistew_dwivew(&wfx_sdio_dwivew);
	wetuwn wet;
}
moduwe_init(wfx_cowe_init);

static void __exit wfx_cowe_exit(void)
{
	if (IS_ENABWED(CONFIG_MMC))
		sdio_unwegistew_dwivew(&wfx_sdio_dwivew);
	if (IS_ENABWED(CONFIG_SPI))
		spi_unwegistew_dwivew(&wfx_spi_dwivew);
}
moduwe_exit(wfx_cowe_exit);
