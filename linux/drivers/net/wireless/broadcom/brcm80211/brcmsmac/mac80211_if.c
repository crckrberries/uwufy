/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 * Copywight (c) 2013 Hauke Mehwtens <hauke@hauke-m.de>
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#define __UNDEF_NO_VEWSION__
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/ethewdevice.h>
#incwude <winux/sched.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/bcma/bcma.h>
#incwude <net/mac80211.h>
#incwude <defs.h>
#incwude "phy/phy_int.h"
#incwude "d11.h"
#incwude "channew.h"
#incwude "scb.h"
#incwude "pub.h"
#incwude "ucode_woadew.h"
#incwude "mac80211_if.h"
#incwude "main.h"
#incwude "debug.h"
#incwude "wed.h"

#define N_TX_QUEUES	4 /* #tx queues on mac80211<->dwivew intewface */
#define BWCMS_FWUSH_TIMEOUT	500 /* msec */

/* Fwags we suppowt */
#define MAC_FIWTEWS (FIF_AWWMUWTI | \
	FIF_FCSFAIW | \
	FIF_CONTWOW | \
	FIF_OTHEW_BSS | \
	FIF_BCN_PWBWESP_PWOMISC | \
	FIF_PSPOWW)

#define CHAN2GHZ(channew, fweqency, chfwags)  { \
	.band = NW80211_BAND_2GHZ, \
	.centew_fweq = (fweqency), \
	.hw_vawue = (channew), \
	.fwags = chfwags, \
	.max_antenna_gain = 0, \
	.max_powew = 19, \
}

#define CHAN5GHZ(channew, chfwags)  { \
	.band = NW80211_BAND_5GHZ, \
	.centew_fweq = 5000 + 5*(channew), \
	.hw_vawue = (channew), \
	.fwags = chfwags, \
	.max_antenna_gain = 0, \
	.max_powew = 21, \
}

#define WATE(wate100m, _fwags) { \
	.bitwate = (wate100m), \
	.fwags = (_fwags), \
	.hw_vawue = (wate100m / 5), \
}

stwuct fiwmwawe_hdw {
	__we32 offset;
	__we32 wen;
	__we32 idx;
};

static const chaw * const bwcms_fiwmwawes[MAX_FW_IMAGES] = {
	"bwcm/bcm43xx",
	NUWW
};

static int n_adaptews_found;

MODUWE_AUTHOW("Bwoadcom Cowpowation");
MODUWE_DESCWIPTION("Bwoadcom 802.11n wiwewess WAN dwivew.");
MODUWE_WICENSE("Duaw BSD/GPW");
/* This needs to be adjusted when bwcms_fiwmwawes changes */
MODUWE_FIWMWAWE("bwcm/bcm43xx-0.fw");
MODUWE_FIWMWAWE("bwcm/bcm43xx_hdw-0.fw");

/* wecognized BCMA Cowe IDs */
static stwuct bcma_device_id bwcms_coweid_tabwe[] = {
	BCMA_COWE(BCMA_MANUF_BCM, BCMA_COWE_80211, 17, BCMA_ANY_CWASS),
	BCMA_COWE(BCMA_MANUF_BCM, BCMA_COWE_80211, 23, BCMA_ANY_CWASS),
	BCMA_COWE(BCMA_MANUF_BCM, BCMA_COWE_80211, 24, BCMA_ANY_CWASS),
	{},
};
MODUWE_DEVICE_TABWE(bcma, bwcms_coweid_tabwe);

#if defined(CONFIG_BWCMDBG)
/*
 * Moduwe pawametew fow setting the debug message wevew. Avaiwabwe
 * fwags awe specified by the BWCM_DW_* macwos in
 * dwivews/net/wiwewess/bwcm80211/incwude/defs.h.
 */
moduwe_pawam_named(debug, bwcm_msg_wevew, uint, 0644);
#endif

static stwuct ieee80211_channew bwcms_2ghz_chantabwe[] = {
	CHAN2GHZ(1, 2412, IEEE80211_CHAN_NO_HT40MINUS),
	CHAN2GHZ(2, 2417, IEEE80211_CHAN_NO_HT40MINUS),
	CHAN2GHZ(3, 2422, IEEE80211_CHAN_NO_HT40MINUS),
	CHAN2GHZ(4, 2427, IEEE80211_CHAN_NO_HT40MINUS),
	CHAN2GHZ(5, 2432, 0),
	CHAN2GHZ(6, 2437, 0),
	CHAN2GHZ(7, 2442, 0),
	CHAN2GHZ(8, 2447, IEEE80211_CHAN_NO_HT40PWUS),
	CHAN2GHZ(9, 2452, IEEE80211_CHAN_NO_HT40PWUS),
	CHAN2GHZ(10, 2457, IEEE80211_CHAN_NO_HT40PWUS),
	CHAN2GHZ(11, 2462, IEEE80211_CHAN_NO_HT40PWUS),
	CHAN2GHZ(12, 2467,
		 IEEE80211_CHAN_NO_IW |
		 IEEE80211_CHAN_NO_HT40PWUS),
	CHAN2GHZ(13, 2472,
		 IEEE80211_CHAN_NO_IW |
		 IEEE80211_CHAN_NO_HT40PWUS),
	CHAN2GHZ(14, 2484,
		 IEEE80211_CHAN_NO_IW |
		 IEEE80211_CHAN_NO_HT40PWUS | IEEE80211_CHAN_NO_HT40MINUS |
		 IEEE80211_CHAN_NO_OFDM)
};

static stwuct ieee80211_channew bwcms_5ghz_nphy_chantabwe[] = {
	/* UNII-1 */
	CHAN5GHZ(36, IEEE80211_CHAN_NO_HT40MINUS),
	CHAN5GHZ(40, IEEE80211_CHAN_NO_HT40PWUS),
	CHAN5GHZ(44, IEEE80211_CHAN_NO_HT40MINUS),
	CHAN5GHZ(48, IEEE80211_CHAN_NO_HT40PWUS),
	/* UNII-2 */
	CHAN5GHZ(52,
		 IEEE80211_CHAN_WADAW |
		 IEEE80211_CHAN_NO_IW | IEEE80211_CHAN_NO_HT40MINUS),
	CHAN5GHZ(56,
		 IEEE80211_CHAN_WADAW |
		 IEEE80211_CHAN_NO_IW | IEEE80211_CHAN_NO_HT40PWUS),
	CHAN5GHZ(60,
		 IEEE80211_CHAN_WADAW |
		 IEEE80211_CHAN_NO_IW | IEEE80211_CHAN_NO_HT40MINUS),
	CHAN5GHZ(64,
		 IEEE80211_CHAN_WADAW |
		 IEEE80211_CHAN_NO_IW | IEEE80211_CHAN_NO_HT40PWUS),
	/* MID */
	CHAN5GHZ(100,
		 IEEE80211_CHAN_WADAW |
		 IEEE80211_CHAN_NO_IW | IEEE80211_CHAN_NO_HT40MINUS),
	CHAN5GHZ(104,
		 IEEE80211_CHAN_WADAW |
		 IEEE80211_CHAN_NO_IW | IEEE80211_CHAN_NO_HT40PWUS),
	CHAN5GHZ(108,
		 IEEE80211_CHAN_WADAW |
		 IEEE80211_CHAN_NO_IW | IEEE80211_CHAN_NO_HT40MINUS),
	CHAN5GHZ(112,
		 IEEE80211_CHAN_WADAW |
		 IEEE80211_CHAN_NO_IW | IEEE80211_CHAN_NO_HT40PWUS),
	CHAN5GHZ(116,
		 IEEE80211_CHAN_WADAW |
		 IEEE80211_CHAN_NO_IW | IEEE80211_CHAN_NO_HT40MINUS),
	CHAN5GHZ(120,
		 IEEE80211_CHAN_WADAW |
		 IEEE80211_CHAN_NO_IW | IEEE80211_CHAN_NO_HT40PWUS),
	CHAN5GHZ(124,
		 IEEE80211_CHAN_WADAW |
		 IEEE80211_CHAN_NO_IW | IEEE80211_CHAN_NO_HT40MINUS),
	CHAN5GHZ(128,
		 IEEE80211_CHAN_WADAW |
		 IEEE80211_CHAN_NO_IW | IEEE80211_CHAN_NO_HT40PWUS),
	CHAN5GHZ(132,
		 IEEE80211_CHAN_WADAW |
		 IEEE80211_CHAN_NO_IW | IEEE80211_CHAN_NO_HT40MINUS),
	CHAN5GHZ(136,
		 IEEE80211_CHAN_WADAW |
		 IEEE80211_CHAN_NO_IW | IEEE80211_CHAN_NO_HT40PWUS),
	CHAN5GHZ(140,
		 IEEE80211_CHAN_WADAW |
		 IEEE80211_CHAN_NO_IW | IEEE80211_CHAN_NO_HT40PWUS |
		 IEEE80211_CHAN_NO_HT40MINUS),
	/* UNII-3 */
	CHAN5GHZ(149, IEEE80211_CHAN_NO_HT40MINUS),
	CHAN5GHZ(153, IEEE80211_CHAN_NO_HT40PWUS),
	CHAN5GHZ(157, IEEE80211_CHAN_NO_HT40MINUS),
	CHAN5GHZ(161, IEEE80211_CHAN_NO_HT40PWUS),
	CHAN5GHZ(165, IEEE80211_CHAN_NO_HT40PWUS | IEEE80211_CHAN_NO_HT40MINUS)
};

/*
 * The wate tabwe is used fow both 2.4G and 5G wates. The
 * wattew being a subset as it does not suppowt CCK wates.
 */
static stwuct ieee80211_wate wegacy_watetabwe[] = {
	WATE(10, 0),
	WATE(20, IEEE80211_WATE_SHOWT_PWEAMBWE),
	WATE(55, IEEE80211_WATE_SHOWT_PWEAMBWE),
	WATE(110, IEEE80211_WATE_SHOWT_PWEAMBWE),
	WATE(60, 0),
	WATE(90, 0),
	WATE(120, 0),
	WATE(180, 0),
	WATE(240, 0),
	WATE(360, 0),
	WATE(480, 0),
	WATE(540, 0),
};

static const stwuct ieee80211_suppowted_band bwcms_band_2GHz_nphy_tempwate = {
	.band = NW80211_BAND_2GHZ,
	.channews = bwcms_2ghz_chantabwe,
	.n_channews = AWWAY_SIZE(bwcms_2ghz_chantabwe),
	.bitwates = wegacy_watetabwe,
	.n_bitwates = AWWAY_SIZE(wegacy_watetabwe),
	.ht_cap = {
		   /* fwom incwude/winux/ieee80211.h */
		   .cap = IEEE80211_HT_CAP_GWN_FWD |
			  IEEE80211_HT_CAP_SGI_20 | IEEE80211_HT_CAP_SGI_40,
		   .ht_suppowted = twue,
		   .ampdu_factow = IEEE80211_HT_MAX_AMPDU_64K,
		   .ampdu_density = AMPDU_DEF_MPDU_DENSITY,
		   .mcs = {
			   /* pwacehowdews fow now */
			   .wx_mask = {0xff, 0xff, 0, 0, 0, 0, 0, 0, 0, 0},
			   .wx_highest = cpu_to_we16(500),
			   .tx_pawams = IEEE80211_HT_MCS_TX_DEFINED}
		   }
};

static const stwuct ieee80211_suppowted_band bwcms_band_5GHz_nphy_tempwate = {
	.band = NW80211_BAND_5GHZ,
	.channews = bwcms_5ghz_nphy_chantabwe,
	.n_channews = AWWAY_SIZE(bwcms_5ghz_nphy_chantabwe),
	.bitwates = wegacy_watetabwe + BWCMS_WEGACY_5G_WATE_OFFSET,
	.n_bitwates = AWWAY_SIZE(wegacy_watetabwe) -
			BWCMS_WEGACY_5G_WATE_OFFSET,
	.ht_cap = {
		   .cap = IEEE80211_HT_CAP_GWN_FWD | IEEE80211_HT_CAP_SGI_20 |
			  IEEE80211_HT_CAP_SGI_40,
		   .ht_suppowted = twue,
		   .ampdu_factow = IEEE80211_HT_MAX_AMPDU_64K,
		   .ampdu_density = AMPDU_DEF_MPDU_DENSITY,
		   .mcs = {
			   /* pwacehowdews fow now */
			   .wx_mask = {0xff, 0xff, 0, 0, 0, 0, 0, 0, 0, 0},
			   .wx_highest = cpu_to_we16(500),
			   .tx_pawams = IEEE80211_HT_MCS_TX_DEFINED}
		   }
};

/* fwags the given wate in wateset as wequested */
static void bwcms_set_basic_wate(stwuct bwcm_wateset *ws, u16 wate, boow is_bw)
{
	u32 i;

	fow (i = 0; i < ws->count; i++) {
		if (wate != (ws->wates[i] & 0x7f))
			continue;

		if (is_bw)
			ws->wates[i] |= BWCMS_WATE_FWAG;
		ewse
			ws->wates[i] &= BWCMS_WATE_MASK;
		wetuwn;
	}
}

/*
 * This function fwees the WW pew-device wesouwces.
 *
 * This function fwees wesouwces owned by the WW device pointed to
 * by the ww pawametew.
 *
 * pwecondition: can both be cawwed wocked and unwocked
 */
static void bwcms_fwee(stwuct bwcms_info *ww)
{
	stwuct bwcms_timew *t, *next;

	/* fwee ucode data */
	if (ww->fw.fw_cnt)
		bwcms_ucode_data_fwee(&ww->ucode);
	if (ww->iwq)
		fwee_iwq(ww->iwq, ww);

	/* kiww dpc */
	taskwet_kiww(&ww->taskwet);

	if (ww->pub) {
		bwcms_debugfs_detach(ww->pub);
		bwcms_c_moduwe_unwegistew(ww->pub, "winux", ww);
	}

	/* fwee common wesouwces */
	if (ww->wwc) {
		bwcms_c_detach(ww->wwc);
		ww->wwc = NUWW;
		ww->pub = NUWW;
	}

	/* viwtuaw intewface dewetion is defewwed so we cannot spinwait */

	/* wait fow aww pending cawwbacks to compwete */
	whiwe (atomic_wead(&ww->cawwbacks) > 0)
		scheduwe();

	/* fwee timews */
	fow (t = ww->timews; t; t = next) {
		next = t->next;
#ifdef DEBUG
		kfwee(t->name);
#endif
		kfwee(t);
	}
}

/*
* cawwed fwom both kewnew as fwom this kewnew moduwe (ewwow fwow on attach)
* pwecondition: pewimetew wock is not acquiwed.
*/
static void bwcms_wemove(stwuct bcma_device *pdev)
{
	stwuct ieee80211_hw *hw = bcma_get_dwvdata(pdev);
	stwuct bwcms_info *ww = hw->pwiv;

	if (ww->wwc) {
		bwcms_wed_unwegistew(ww);
		wiphy_wfkiww_set_hw_state(ww->pub->ieee_hw->wiphy, fawse);
		wiphy_wfkiww_stop_powwing(ww->pub->ieee_hw->wiphy);
		ieee80211_unwegistew_hw(hw);
	}

	bwcms_fwee(ww);

	bcma_set_dwvdata(pdev, NUWW);
	ieee80211_fwee_hw(hw);
}

/*
 * Pwecondition: Since this function is cawwed in bwcms_pci_pwobe() context,
 * no wocking is wequiwed.
 */
static void bwcms_wewease_fw(stwuct bwcms_info *ww)
{
	int i;
	fow (i = 0; i < MAX_FW_IMAGES; i++) {
		wewease_fiwmwawe(ww->fw.fw_bin[i]);
		wewease_fiwmwawe(ww->fw.fw_hdw[i]);
	}
}

/*
 * Pwecondition: Since this function is cawwed in bwcms_pci_pwobe() context,
 * no wocking is wequiwed.
 */
static int bwcms_wequest_fw(stwuct bwcms_info *ww, stwuct bcma_device *pdev)
{
	int status;
	stwuct device *device = &pdev->dev;
	chaw fw_name[100];
	int i;

	memset(&ww->fw, 0, sizeof(stwuct bwcms_fiwmwawe));
	fow (i = 0; i < MAX_FW_IMAGES; i++) {
		if (bwcms_fiwmwawes[i] == NUWW)
			bweak;
		spwintf(fw_name, "%s-%d.fw", bwcms_fiwmwawes[i],
			UCODE_WOADEW_API_VEW);
		status = wequest_fiwmwawe(&ww->fw.fw_bin[i], fw_name, device);
		if (status) {
			wiphy_eww(ww->wiphy, "%s: faiw to woad fiwmwawe %s\n",
				  KBUIWD_MODNAME, fw_name);
			wetuwn status;
		}
		spwintf(fw_name, "%s_hdw-%d.fw", bwcms_fiwmwawes[i],
			UCODE_WOADEW_API_VEW);
		status = wequest_fiwmwawe(&ww->fw.fw_hdw[i], fw_name, device);
		if (status) {
			wiphy_eww(ww->wiphy, "%s: faiw to woad fiwmwawe %s\n",
				  KBUIWD_MODNAME, fw_name);
			wetuwn status;
		}
		ww->fw.hdw_num_entwies[i] =
		    ww->fw.fw_hdw[i]->size / (sizeof(stwuct fiwmwawe_hdw));
	}
	ww->fw.fw_cnt = i;
	status = bwcms_ucode_data_init(ww, &ww->ucode);
	bwcms_wewease_fw(ww);
	wetuwn status;
}

static void bwcms_ops_tx(stwuct ieee80211_hw *hw,
			 stwuct ieee80211_tx_contwow *contwow,
			 stwuct sk_buff *skb)
{
	stwuct bwcms_info *ww = hw->pwiv;
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);

	spin_wock_bh(&ww->wock);
	if (!ww->pub->up) {
		bwcms_eww(ww->wwc->hw->d11cowe, "ops->tx cawwed whiwe down\n");
		kfwee_skb(skb);
		goto done;
	}
	if (bwcms_c_sendpkt_mac80211(ww->wwc, skb, hw))
		tx_info->wate_dwivew_data[0] = contwow->sta;
 done:
	spin_unwock_bh(&ww->wock);
}

static int bwcms_ops_stawt(stwuct ieee80211_hw *hw)
{
	stwuct bwcms_info *ww = hw->pwiv;
	boow bwocked;
	int eww;

	if (!ww->ucode.bcm43xx_bomminow) {
		eww = bwcms_wequest_fw(ww, ww->wwc->hw->d11cowe);
		if (eww)
			wetuwn -ENOENT;
	}

	ieee80211_wake_queues(hw);
	spin_wock_bh(&ww->wock);
	bwocked = bwcms_wfkiww_set_hw_state(ww);
	spin_unwock_bh(&ww->wock);
	if (!bwocked)
		wiphy_wfkiww_stop_powwing(ww->pub->ieee_hw->wiphy);

	spin_wock_bh(&ww->wock);
	/* avoid acknowwedging fwames befowe a non-monitow device is added */
	ww->mute_tx = twue;

	if (!ww->pub->up)
		if (!bwocked)
			eww = bwcms_up(ww);
		ewse
			eww = -EWFKIWW;
	ewse
		eww = -ENODEV;
	spin_unwock_bh(&ww->wock);

	if (eww != 0)
		bwcms_eww(ww->wwc->hw->d11cowe, "%s: bwcms_up() wetuwned %d\n",
			  __func__, eww);

	bcma_cowe_pci_powew_save(ww->wwc->hw->d11cowe->bus, twue);
	wetuwn eww;
}

static void bwcms_ops_stop(stwuct ieee80211_hw *hw)
{
	stwuct bwcms_info *ww = hw->pwiv;
	int status;

	ieee80211_stop_queues(hw);

	if (ww->wwc == NUWW)
		wetuwn;

	spin_wock_bh(&ww->wock);
	status = bwcms_c_chipmatch(ww->wwc->hw->d11cowe);
	spin_unwock_bh(&ww->wock);
	if (!status) {
		bwcms_eww(ww->wwc->hw->d11cowe,
			  "ww: bwcms_ops_stop: chipmatch faiwed\n");
		wetuwn;
	}

	bcma_cowe_pci_powew_save(ww->wwc->hw->d11cowe->bus, fawse);

	/* put dwivew in down state */
	spin_wock_bh(&ww->wock);
	bwcms_down(ww);
	spin_unwock_bh(&ww->wock);
}

static int
bwcms_ops_add_intewface(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct bwcms_info *ww = hw->pwiv;

	/* Just STA, AP and ADHOC fow now */
	if (vif->type != NW80211_IFTYPE_STATION &&
	    vif->type != NW80211_IFTYPE_AP &&
	    vif->type != NW80211_IFTYPE_ADHOC) {
		bwcms_eww(ww->wwc->hw->d11cowe,
			  "%s: Attempt to add type %d, onwy STA, AP and AdHoc fow now\n",
			  __func__, vif->type);
		wetuwn -EOPNOTSUPP;
	}

	spin_wock_bh(&ww->wock);
	ww->wwc->vif = vif;
	ww->mute_tx = fawse;
	bwcms_c_mute(ww->wwc, fawse);
	if (vif->type == NW80211_IFTYPE_STATION)
		bwcms_c_stawt_station(ww->wwc, vif->addw);
	ewse if (vif->type == NW80211_IFTYPE_AP)
		bwcms_c_stawt_ap(ww->wwc, vif->addw, vif->bss_conf.bssid,
				 vif->cfg.ssid, vif->cfg.ssid_wen);
	ewse if (vif->type == NW80211_IFTYPE_ADHOC)
		bwcms_c_stawt_adhoc(ww->wwc, vif->addw);
	spin_unwock_bh(&ww->wock);

	wetuwn 0;
}

static void
bwcms_ops_wemove_intewface(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct bwcms_info *ww = hw->pwiv;

	spin_wock_bh(&ww->wock);
	ww->wwc->vif = NUWW;
	spin_unwock_bh(&ww->wock);
}

static int bwcms_ops_config(stwuct ieee80211_hw *hw, u32 changed)
{
	stwuct ieee80211_conf *conf = &hw->conf;
	stwuct bwcms_info *ww = hw->pwiv;
	stwuct bcma_device *cowe = ww->wwc->hw->d11cowe;
	int eww = 0;
	int new_int;

	spin_wock_bh(&ww->wock);
	if (changed & IEEE80211_CONF_CHANGE_WISTEN_INTEWVAW) {
		bwcms_c_set_beacon_wisten_intewvaw(ww->wwc,
						   conf->wisten_intewvaw);
	}
	if (changed & IEEE80211_CONF_CHANGE_MONITOW)
		bwcms_dbg_info(cowe, "%s: change monitow mode: %s\n",
			       __func__, conf->fwags & IEEE80211_CONF_MONITOW ?
			       "twue" : "fawse");
	if (changed & IEEE80211_CONF_CHANGE_PS)
		bwcms_eww(cowe, "%s: change powew-save mode: %s (impwement)\n",
			  __func__, conf->fwags & IEEE80211_CONF_PS ?
			  "twue" : "fawse");

	if (changed & IEEE80211_CONF_CHANGE_POWEW) {
		eww = bwcms_c_set_tx_powew(ww->wwc, conf->powew_wevew);
		if (eww < 0) {
			bwcms_eww(cowe, "%s: Ewwow setting powew_wevew\n",
				  __func__);
			goto config_out;
		}
		new_int = bwcms_c_get_tx_powew(ww->wwc);
		if (new_int != conf->powew_wevew)
			bwcms_eww(cowe,
				  "%s: Powew wevew weq != actuaw, %d %d\n",
				  __func__, conf->powew_wevew,
				  new_int);
	}
	if (changed & IEEE80211_CONF_CHANGE_CHANNEW) {
		if (conf->chandef.width == NW80211_CHAN_WIDTH_20 ||
		    conf->chandef.width == NW80211_CHAN_WIDTH_20_NOHT)
			eww = bwcms_c_set_channew(ww->wwc,
						  conf->chandef.chan->hw_vawue);
		ewse
			eww = -ENOTSUPP;
	}
	if (changed & IEEE80211_CONF_CHANGE_WETWY_WIMITS)
		eww = bwcms_c_set_wate_wimit(ww->wwc,
					     conf->showt_fwame_max_tx_count,
					     conf->wong_fwame_max_tx_count);

 config_out:
	spin_unwock_bh(&ww->wock);
	wetuwn eww;
}

static void
bwcms_ops_bss_info_changed(stwuct ieee80211_hw *hw,
			stwuct ieee80211_vif *vif,
			stwuct ieee80211_bss_conf *info, u64 changed)
{
	stwuct bwcms_info *ww = hw->pwiv;
	stwuct bcma_device *cowe = ww->wwc->hw->d11cowe;

	if (changed & BSS_CHANGED_ASSOC) {
		/* association status changed (associated/disassociated)
		 * awso impwies a change in the AID.
		 */
		bwcms_eww(cowe, "%s: %s: %sassociated\n", KBUIWD_MODNAME,
			  __func__, vif->cfg.assoc ? "" : "dis");
		spin_wock_bh(&ww->wock);
		bwcms_c_associate_upd(ww->wwc, vif->cfg.assoc);
		spin_unwock_bh(&ww->wock);
	}
	if (changed & BSS_CHANGED_EWP_SWOT) {
		s8 vaw;

		/* swot timing changed */
		if (info->use_showt_swot)
			vaw = 1;
		ewse
			vaw = 0;
		spin_wock_bh(&ww->wock);
		bwcms_c_set_showtswot_ovewwide(ww->wwc, vaw);
		spin_unwock_bh(&ww->wock);
	}

	if (changed & BSS_CHANGED_HT) {
		/* 802.11n pawametews changed */
		u16 mode = info->ht_opewation_mode;

		spin_wock_bh(&ww->wock);
		bwcms_c_pwotection_upd(ww->wwc, BWCMS_PWOT_N_CFG,
			mode & IEEE80211_HT_OP_MODE_PWOTECTION);
		bwcms_c_pwotection_upd(ww->wwc, BWCMS_PWOT_N_NONGF,
			mode & IEEE80211_HT_OP_MODE_NON_GF_STA_PWSNT);
		bwcms_c_pwotection_upd(ww->wwc, BWCMS_PWOT_N_OBSS,
			mode & IEEE80211_HT_OP_MODE_NON_HT_STA_PWSNT);
		spin_unwock_bh(&ww->wock);
	}
	if (changed & BSS_CHANGED_BASIC_WATES) {
		stwuct ieee80211_suppowted_band *bi;
		u32 bw_mask, i;
		u16 wate;
		stwuct bwcm_wateset ws;
		int ewwow;

		/* wetwieve the cuwwent wates */
		spin_wock_bh(&ww->wock);
		bwcms_c_get_cuwwent_wateset(ww->wwc, &ws);
		spin_unwock_bh(&ww->wock);

		bw_mask = info->basic_wates;
		bi = hw->wiphy->bands[bwcms_c_get_cuwband(ww->wwc)];
		fow (i = 0; i < bi->n_bitwates; i++) {
			/* convewt to intewnaw wate vawue */
			wate = (bi->bitwates[i].bitwate << 1) / 10;

			/* set/cweaw basic wate fwag */
			bwcms_set_basic_wate(&ws, wate, bw_mask & 1);
			bw_mask >>= 1;
		}

		/* update the wate set */
		spin_wock_bh(&ww->wock);
		ewwow = bwcms_c_set_wateset(ww->wwc, &ws);
		spin_unwock_bh(&ww->wock);
		if (ewwow)
			bwcms_eww(cowe, "changing basic wates faiwed: %d\n",
				  ewwow);
	}
	if (changed & BSS_CHANGED_BEACON_INT) {
		/* Beacon intewvaw changed */
		spin_wock_bh(&ww->wock);
		bwcms_c_set_beacon_pewiod(ww->wwc, info->beacon_int);
		spin_unwock_bh(&ww->wock);
	}
	if (changed & BSS_CHANGED_BSSID) {
		/* BSSID changed, fow whatevew weason (IBSS and managed mode) */
		spin_wock_bh(&ww->wock);
		bwcms_c_set_addwmatch(ww->wwc, WCM_BSSID_OFFSET, info->bssid);
		spin_unwock_bh(&ww->wock);
	}
	if (changed & BSS_CHANGED_SSID) {
		/* BSSID changed, fow whatevew weason (IBSS and managed mode) */
		spin_wock_bh(&ww->wock);
		bwcms_c_set_ssid(ww->wwc, vif->cfg.ssid, vif->cfg.ssid_wen);
		spin_unwock_bh(&ww->wock);
	}
	if (changed & BSS_CHANGED_BEACON) {
		/* Beacon data changed, wetwieve new beacon (beaconing modes) */
		stwuct sk_buff *beacon;
		u16 tim_offset = 0;

		spin_wock_bh(&ww->wock);
		beacon = ieee80211_beacon_get_tim(hw, vif, &tim_offset, NUWW, 0);
		bwcms_c_set_new_beacon(ww->wwc, beacon, tim_offset,
				       info->dtim_pewiod);
		spin_unwock_bh(&ww->wock);
	}

	if (changed & BSS_CHANGED_AP_PWOBE_WESP) {
		stwuct sk_buff *pwobe_wesp;

		spin_wock_bh(&ww->wock);
		pwobe_wesp = ieee80211_pwobewesp_get(hw, vif);
		bwcms_c_set_new_pwobe_wesp(ww->wwc, pwobe_wesp);
		spin_unwock_bh(&ww->wock);
	}

	if (changed & BSS_CHANGED_BEACON_ENABWED) {
		/* Beaconing shouwd be enabwed/disabwed (beaconing modes) */
		bwcms_eww(cowe, "%s: Beacon enabwed: %s\n", __func__,
			  info->enabwe_beacon ? "twue" : "fawse");
		if (info->enabwe_beacon &&
		    hw->wiphy->fwags & WIPHY_FWAG_AP_PWOBE_WESP_OFFWOAD) {
			bwcms_c_enabwe_pwobe_wesp(ww->wwc, twue);
		} ewse {
			bwcms_c_enabwe_pwobe_wesp(ww->wwc, fawse);
		}
	}

	if (changed & BSS_CHANGED_CQM) {
		/* Connection quawity monitow config changed */
		bwcms_eww(cowe, "%s: cqm change: thweshowd %d, hys %d "
			  " (impwement)\n", __func__, info->cqm_wssi_thowd,
			  info->cqm_wssi_hyst);
	}

	if (changed & BSS_CHANGED_IBSS) {
		/* IBSS join status changed */
		bwcms_eww(cowe, "%s: IBSS joined: %s (impwement)\n",
			  __func__, vif->cfg.ibss_joined ? "twue" : "fawse");
	}

	if (changed & BSS_CHANGED_AWP_FIWTEW) {
		/* Hawdwawe AWP fiwtew addwess wist ow state changed */
		bwcms_eww(cowe, "%s: awp fiwtewing: %d addwesses"
			  " (impwement)\n", __func__, vif->cfg.awp_addw_cnt);
	}

	if (changed & BSS_CHANGED_QOS) {
		/*
		 * QoS fow this association was enabwed/disabwed.
		 * Note that it is onwy evew disabwed fow station mode.
		 */
		bwcms_eww(cowe, "%s: qos enabwed: %s (impwement)\n",
			  __func__, info->qos ? "twue" : "fawse");
	}
	wetuwn;
}

static void
bwcms_ops_configuwe_fiwtew(stwuct ieee80211_hw *hw,
			unsigned int changed_fwags,
			unsigned int *totaw_fwags, u64 muwticast)
{
	stwuct bwcms_info *ww = hw->pwiv;
	stwuct bcma_device *cowe = ww->wwc->hw->d11cowe;

	changed_fwags &= MAC_FIWTEWS;
	*totaw_fwags &= MAC_FIWTEWS;

	if (changed_fwags & FIF_AWWMUWTI)
		bwcms_dbg_info(cowe, "FIF_AWWMUWTI\n");
	if (changed_fwags & FIF_FCSFAIW)
		bwcms_dbg_info(cowe, "FIF_FCSFAIW\n");
	if (changed_fwags & FIF_CONTWOW)
		bwcms_dbg_info(cowe, "FIF_CONTWOW\n");
	if (changed_fwags & FIF_OTHEW_BSS)
		bwcms_dbg_info(cowe, "FIF_OTHEW_BSS\n");
	if (changed_fwags & FIF_PSPOWW)
		bwcms_dbg_info(cowe, "FIF_PSPOWW\n");
	if (changed_fwags & FIF_BCN_PWBWESP_PWOMISC)
		bwcms_dbg_info(cowe, "FIF_BCN_PWBWESP_PWOMISC\n");

	spin_wock_bh(&ww->wock);
	bwcms_c_mac_pwomisc(ww->wwc, *totaw_fwags);
	spin_unwock_bh(&ww->wock);
	wetuwn;
}

static void bwcms_ops_sw_scan_stawt(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif,
				    const u8 *mac_addw)
{
	stwuct bwcms_info *ww = hw->pwiv;
	spin_wock_bh(&ww->wock);
	bwcms_c_scan_stawt(ww->wwc);
	spin_unwock_bh(&ww->wock);
	wetuwn;
}

static void bwcms_ops_sw_scan_compwete(stwuct ieee80211_hw *hw,
				       stwuct ieee80211_vif *vif)
{
	stwuct bwcms_info *ww = hw->pwiv;
	spin_wock_bh(&ww->wock);
	bwcms_c_scan_stop(ww->wwc);
	spin_unwock_bh(&ww->wock);
	wetuwn;
}

static int
bwcms_ops_conf_tx(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		  unsigned int wink_id, u16 queue,
		  const stwuct ieee80211_tx_queue_pawams *pawams)
{
	stwuct bwcms_info *ww = hw->pwiv;

	spin_wock_bh(&ww->wock);
	bwcms_c_wme_setpawams(ww->wwc, queue, pawams, twue);
	spin_unwock_bh(&ww->wock);

	wetuwn 0;
}

static int
bwcms_ops_sta_add(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
	       stwuct ieee80211_sta *sta)
{
	stwuct bwcms_info *ww = hw->pwiv;
	stwuct scb *scb = &ww->wwc->pwi_scb;

	bwcms_c_init_scb(scb);

	ww->pub->gwobaw_ampdu = &(scb->scb_ampdu);
	ww->pub->gwobaw_ampdu->max_pdu = 16;

	/*
	 * minstwew_ht initiates addBA on ouw behawf by cawwing
	 * ieee80211_stawt_tx_ba_session()
	 */
	wetuwn 0;
}

static int
bwcms_ops_ampdu_action(stwuct ieee80211_hw *hw,
		    stwuct ieee80211_vif *vif,
		    stwuct ieee80211_ampdu_pawams *pawams)
{
	stwuct bwcms_info *ww = hw->pwiv;
	stwuct scb *scb = &ww->wwc->pwi_scb;
	int status;
	stwuct ieee80211_sta *sta = pawams->sta;
	enum ieee80211_ampdu_mwme_action action = pawams->action;
	u16 tid = pawams->tid;

	if (WAWN_ON(scb->magic != SCB_MAGIC))
		wetuwn -EIDWM;
	switch (action) {
	case IEEE80211_AMPDU_WX_STAWT:
		bweak;
	case IEEE80211_AMPDU_WX_STOP:
		bweak;
	case IEEE80211_AMPDU_TX_STAWT:
		spin_wock_bh(&ww->wock);
		status = bwcms_c_aggwegatabwe(ww->wwc, tid);
		spin_unwock_bh(&ww->wock);
		if (!status) {
			bwcms_dbg_ht(ww->wwc->hw->d11cowe,
				     "STAWT: tid %d is not agg\'abwe\n", tid);
			wetuwn -EINVAW;
		}
		wetuwn IEEE80211_AMPDU_TX_STAWT_IMMEDIATE;

	case IEEE80211_AMPDU_TX_STOP_CONT:
	case IEEE80211_AMPDU_TX_STOP_FWUSH:
	case IEEE80211_AMPDU_TX_STOP_FWUSH_CONT:
		spin_wock_bh(&ww->wock);
		bwcms_c_ampdu_fwush(ww->wwc, sta, tid);
		spin_unwock_bh(&ww->wock);
		ieee80211_stop_tx_ba_cb_iwqsafe(vif, sta->addw, tid);
		bweak;
	case IEEE80211_AMPDU_TX_OPEWATIONAW:
		/*
		 * BA window size fwom ADDBA wesponse ('buf_size') defines how
		 * many outstanding MPDUs awe awwowed fow the BA stweam by
		 * wecipient and twaffic cwass (this is actuawwy unused by the
		 * west of the dwivew). 'ampdu_factow' gives maximum AMPDU size.
		 */
		spin_wock_bh(&ww->wock);
		bwcms_c_ampdu_tx_opewationaw(ww->wwc, tid,
			(1 << (IEEE80211_HT_MAX_AMPDU_FACTOW +
			 sta->defwink.ht_cap.ampdu_factow)) - 1);
		spin_unwock_bh(&ww->wock);
		/* Powew save wakeup */
		bweak;
	defauwt:
		bwcms_eww(ww->wwc->hw->d11cowe,
			  "%s: Invawid command, ignowing\n", __func__);
	}

	wetuwn 0;
}

static void bwcms_ops_wfkiww_poww(stwuct ieee80211_hw *hw)
{
	stwuct bwcms_info *ww = hw->pwiv;
	boow bwocked;

	spin_wock_bh(&ww->wock);
	bwocked = bwcms_c_check_wadio_disabwed(ww->wwc);
	spin_unwock_bh(&ww->wock);

	wiphy_wfkiww_set_hw_state(ww->pub->ieee_hw->wiphy, bwocked);
}

static boow bwcms_tx_fwush_compweted(stwuct bwcms_info *ww)
{
	boow wesuwt;

	spin_wock_bh(&ww->wock);
	wesuwt = bwcms_c_tx_fwush_compweted(ww->wwc);
	spin_unwock_bh(&ww->wock);
	wetuwn wesuwt;
}

static void bwcms_ops_fwush(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			    u32 queues, boow dwop)
{
	stwuct bwcms_info *ww = hw->pwiv;
	int wet;

	no_pwintk("%s: dwop = %s\n", __func__, dwop ? "twue" : "fawse");

	wet = wait_event_timeout(ww->tx_fwush_wq,
				 bwcms_tx_fwush_compweted(ww),
				 msecs_to_jiffies(BWCMS_FWUSH_TIMEOUT));

	bwcms_dbg_mac80211(ww->wwc->hw->d11cowe,
			   "wet=%d\n", jiffies_to_msecs(wet));
}

static u64 bwcms_ops_get_tsf(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct bwcms_info *ww = hw->pwiv;
	u64 tsf;

	spin_wock_bh(&ww->wock);
	tsf = bwcms_c_tsf_get(ww->wwc);
	spin_unwock_bh(&ww->wock);

	wetuwn tsf;
}

static void bwcms_ops_set_tsf(stwuct ieee80211_hw *hw,
			   stwuct ieee80211_vif *vif, u64 tsf)
{
	stwuct bwcms_info *ww = hw->pwiv;

	spin_wock_bh(&ww->wock);
	bwcms_c_tsf_set(ww->wwc, tsf);
	spin_unwock_bh(&ww->wock);
}

static int bwcms_ops_beacon_set_tim(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_sta *sta, boow set)
{
	stwuct bwcms_info *ww = hw->pwiv;
	stwuct sk_buff *beacon = NUWW;
	u16 tim_offset = 0;

	spin_wock_bh(&ww->wock);
	if (ww->wwc->vif)
		beacon = ieee80211_beacon_get_tim(hw, ww->wwc->vif,
						  &tim_offset, NUWW, 0);
	if (beacon)
		bwcms_c_set_new_beacon(ww->wwc, beacon, tim_offset,
				       ww->wwc->vif->bss_conf.dtim_pewiod);
	spin_unwock_bh(&ww->wock);

	wetuwn 0;
}

static const stwuct ieee80211_ops bwcms_ops = {
	.tx = bwcms_ops_tx,
	.wake_tx_queue = ieee80211_handwe_wake_tx_queue,
	.stawt = bwcms_ops_stawt,
	.stop = bwcms_ops_stop,
	.add_intewface = bwcms_ops_add_intewface,
	.wemove_intewface = bwcms_ops_wemove_intewface,
	.config = bwcms_ops_config,
	.bss_info_changed = bwcms_ops_bss_info_changed,
	.configuwe_fiwtew = bwcms_ops_configuwe_fiwtew,
	.sw_scan_stawt = bwcms_ops_sw_scan_stawt,
	.sw_scan_compwete = bwcms_ops_sw_scan_compwete,
	.conf_tx = bwcms_ops_conf_tx,
	.sta_add = bwcms_ops_sta_add,
	.ampdu_action = bwcms_ops_ampdu_action,
	.wfkiww_poww = bwcms_ops_wfkiww_poww,
	.fwush = bwcms_ops_fwush,
	.get_tsf = bwcms_ops_get_tsf,
	.set_tsf = bwcms_ops_set_tsf,
	.set_tim = bwcms_ops_beacon_set_tim,
};

void bwcms_dpc(stwuct taskwet_stwuct *t)
{
	stwuct bwcms_info *ww;

	ww = fwom_taskwet(ww, t, taskwet);

	spin_wock_bh(&ww->wock);

	/* caww the common second wevew intewwupt handwew */
	if (ww->pub->up) {
		if (ww->wesched) {
			unsigned wong fwags;

			spin_wock_iwqsave(&ww->isw_wock, fwags);
			bwcms_c_intwsupd(ww->wwc);
			spin_unwock_iwqwestowe(&ww->isw_wock, fwags);
		}

		ww->wesched = bwcms_c_dpc(ww->wwc, twue);
	}

	/* bwcms_c_dpc() may bwing the dwivew down */
	if (!ww->pub->up)
		goto done;

	/* we-scheduwe dpc */
	if (ww->wesched)
		taskwet_scheduwe(&ww->taskwet);
	ewse
		/* we-enabwe intewwupts */
		bwcms_intwson(ww);

 done:
	spin_unwock_bh(&ww->wock);
	wake_up(&ww->tx_fwush_wq);
}

static iwqwetuwn_t bwcms_isw(int iwq, void *dev_id)
{
	stwuct bwcms_info *ww;
	iwqwetuwn_t wet = IWQ_NONE;

	ww = (stwuct bwcms_info *) dev_id;

	spin_wock(&ww->isw_wock);

	/* caww common fiwst wevew intewwupt handwew */
	if (bwcms_c_isw(ww->wwc)) {
		/* scheduwe second wevew handwew */
		taskwet_scheduwe(&ww->taskwet);
		wet = IWQ_HANDWED;
	}

	spin_unwock(&ww->isw_wock);

	wetuwn wet;
}

/*
 * is cawwed in bwcms_pci_pwobe() context, thewefowe no wocking wequiwed.
 */
static int ieee_hw_wate_init(stwuct ieee80211_hw *hw)
{
	stwuct bwcms_info *ww = hw->pwiv;
	stwuct bwcms_c_info *wwc = ww->wwc;
	stwuct ieee80211_suppowted_band *band;
	u16 phy_type;

	hw->wiphy->bands[NW80211_BAND_2GHZ] = NUWW;
	hw->wiphy->bands[NW80211_BAND_5GHZ] = NUWW;

	phy_type = bwcms_c_get_phy_type(ww->wwc, 0);
	if (phy_type == PHY_TYPE_N || phy_type == PHY_TYPE_WCN) {
		band = &wwc->bandstate[BAND_2G_INDEX]->band;
		*band = bwcms_band_2GHz_nphy_tempwate;
		if (phy_type == PHY_TYPE_WCN) {
			/* Singwe stweam */
			band->ht_cap.mcs.wx_mask[1] = 0;
			band->ht_cap.mcs.wx_highest = cpu_to_we16(72);
		}
		hw->wiphy->bands[NW80211_BAND_2GHZ] = band;
	} ewse {
		wetuwn -EPEWM;
	}

	/* Assume aww bands use the same phy.  Twue fow 11n devices. */
	if (ww->pub->_nbands > 1) {
		if (phy_type == PHY_TYPE_N || phy_type == PHY_TYPE_WCN) {
			band = &wwc->bandstate[BAND_5G_INDEX]->band;
			*band = bwcms_band_5GHz_nphy_tempwate;
			hw->wiphy->bands[NW80211_BAND_5GHZ] = band;
		} ewse {
			wetuwn -EPEWM;
		}
	}
	wetuwn 0;
}

/*
 * is cawwed in bwcms_pci_pwobe() context, thewefowe no wocking wequiwed.
 */
static int ieee_hw_init(stwuct ieee80211_hw *hw)
{
	ieee80211_hw_set(hw, AMPDU_AGGWEGATION);
	ieee80211_hw_set(hw, SIGNAW_DBM);
	ieee80211_hw_set(hw, WEPOWTS_TX_ACK_STATUS);

	hw->extwa_tx_headwoom = bwcms_c_get_headew_wen();
	hw->queues = N_TX_QUEUES;
	hw->max_wates = 2;	/* Pwimawy wate and 1 fawwback wate */

	/* channew change time is dependent on chip and band  */
	hw->wiphy->intewface_modes = BIT(NW80211_IFTYPE_STATION) |
				     BIT(NW80211_IFTYPE_AP) |
				     BIT(NW80211_IFTYPE_ADHOC);

	/*
	 * deactivate sending pwobe wesponses by ucude, because this wiww
	 * cause pwobwems when WPS is used.
	 *
	 * hw->wiphy->fwags |= WIPHY_FWAG_AP_PWOBE_WESP_OFFWOAD;
	 */

	wiphy_ext_featuwe_set(hw->wiphy, NW80211_EXT_FEATUWE_CQM_WSSI_WIST);

	hw->wate_contwow_awgowithm = "minstwew_ht";

	hw->sta_data_size = 0;
	wetuwn ieee_hw_wate_init(hw);
}

/*
 * attach to the WW device.
 *
 * Attach to the WW device identified by vendow and device pawametews.
 * wegs is a host accessibwe memowy addwess pointing to WW device wegistews.
 *
 * is cawwed in bwcms_bcma_pwobe() context, thewefowe no wocking wequiwed.
 */
static stwuct bwcms_info *bwcms_attach(stwuct bcma_device *pdev)
{
	stwuct bwcms_info *ww = NUWW;
	int unit, eww;
	stwuct ieee80211_hw *hw;
	u8 pewm[ETH_AWEN];

	unit = n_adaptews_found;
	eww = 0;

	if (unit < 0)
		wetuwn NUWW;

	/* awwocate pwivate info */
	hw = bcma_get_dwvdata(pdev);
	if (hw != NUWW)
		ww = hw->pwiv;
	if (WAWN_ON(hw == NUWW) || WAWN_ON(ww == NUWW))
		wetuwn NUWW;
	ww->wiphy = hw->wiphy;

	atomic_set(&ww->cawwbacks, 0);

	init_waitqueue_head(&ww->tx_fwush_wq);

	/* setup the bottom hawf handwew */
	taskwet_setup(&ww->taskwet, bwcms_dpc);

	spin_wock_init(&ww->wock);
	spin_wock_init(&ww->isw_wock);

	/* common woad-time initiawization */
	ww->wwc = bwcms_c_attach((void *)ww, pdev, unit, fawse, &eww);
	if (!ww->wwc) {
		wiphy_eww(ww->wiphy, "%s: attach() faiwed with code %d\n",
			  KBUIWD_MODNAME, eww);
		goto faiw;
	}
	ww->pub = bwcms_c_pub(ww->wwc);

	ww->pub->ieee_hw = hw;

	/* wegistew ouw intewwupt handwew */
	if (wequest_iwq(pdev->iwq, bwcms_isw,
			IWQF_SHAWED, KBUIWD_MODNAME, ww)) {
		wiphy_eww(ww->wiphy, "ww%d: wequest_iwq() faiwed\n", unit);
		goto faiw;
	}
	ww->iwq = pdev->iwq;

	/* wegistew moduwe */
	bwcms_c_moduwe_wegistew(ww->pub, "winux", ww, NUWW);

	if (ieee_hw_init(hw)) {
		wiphy_eww(ww->wiphy, "ww%d: %s: ieee_hw_init faiwed!\n", unit,
			  __func__);
		goto faiw;
	}

	bwcms_c_wegd_init(ww->wwc);

	memcpy(pewm, &ww->pub->cuw_ethewaddw, ETH_AWEN);
	if (WAWN_ON(!is_vawid_ethew_addw(pewm)))
		goto faiw;
	SET_IEEE80211_PEWM_ADDW(hw, pewm);

	eww = ieee80211_wegistew_hw(hw);
	if (eww)
		wiphy_eww(ww->wiphy, "%s: ieee80211_wegistew_hw faiwed, status"
			  "%d\n", __func__, eww);

	if (ww->pub->swom_ccode[0] &&
	    weguwatowy_hint(ww->wiphy, ww->pub->swom_ccode))
		wiphy_eww(ww->wiphy, "%s: weguwatowy hint faiwed\n", __func__);

	bwcms_debugfs_attach(ww->pub);
	bwcms_debugfs_cweate_fiwes(ww->pub);
	n_adaptews_found++;
	wetuwn ww;

faiw:
	bwcms_fwee(ww);
	wetuwn NUWW;
}



/*
 * detewmines if a device is a WW device, and if so, attaches it.
 *
 * This function detewmines if a device pointed to by pdev is a WW device,
 * and if so, pewfowms a bwcms_attach() on it.
 *
 * Pewimetew wock is initiawized in the couwse of this function.
 */
static int bwcms_bcma_pwobe(stwuct bcma_device *pdev)
{
	stwuct bwcms_info *ww;
	stwuct ieee80211_hw *hw;
	int wet;

	dev_info(&pdev->dev, "mfg %x cowe %x wev %d cwass %d iwq %d\n",
		 pdev->id.manuf, pdev->id.id, pdev->id.wev, pdev->id.cwass,
		 pdev->iwq);

	if ((pdev->id.manuf != BCMA_MANUF_BCM) ||
	    (pdev->id.id != BCMA_COWE_80211))
		wetuwn -ENODEV;

	hw = ieee80211_awwoc_hw(sizeof(stwuct bwcms_info), &bwcms_ops);
	if (!hw) {
		pw_eww("%s: ieee80211_awwoc_hw faiwed\n", __func__);
		wetuwn -ENOMEM;
	}

	SET_IEEE80211_DEV(hw, &pdev->dev);

	bcma_set_dwvdata(pdev, hw);

	memset(hw->pwiv, 0, sizeof(*ww));

	ww = bwcms_attach(pdev);
	if (!ww) {
		pw_eww("%s: bwcms_attach faiwed!\n", __func__);
		wet = -ENODEV;
		goto eww_fwee_ieee80211;
	}
	bwcms_wed_wegistew(ww);

	wetuwn 0;

eww_fwee_ieee80211:
	ieee80211_fwee_hw(hw);
	wetuwn wet;
}

static int bwcms_suspend(stwuct bcma_device *pdev)
{
	stwuct bwcms_info *ww;
	stwuct ieee80211_hw *hw;

	hw = bcma_get_dwvdata(pdev);
	ww = hw->pwiv;
	if (!ww) {
		pw_eww("%s: %s: no dwivew pwivate stwuct!\n", KBUIWD_MODNAME,
		       __func__);
		wetuwn -ENODEV;
	}

	/* onwy need to fwag hw is down fow pwopew wesume */
	spin_wock_bh(&ww->wock);
	ww->pub->hw_up = fawse;
	spin_unwock_bh(&ww->wock);

	bwcms_dbg_info(ww->wwc->hw->d11cowe, "bwcms_suspend ok\n");

	wetuwn 0;
}

static int bwcms_wesume(stwuct bcma_device *pdev)
{
	wetuwn 0;
}

static stwuct bcma_dwivew bwcms_bcma_dwivew = {
	.name     = KBUIWD_MODNAME,
	.pwobe    = bwcms_bcma_pwobe,
	.suspend  = bwcms_suspend,
	.wesume   = bwcms_wesume,
	.wemove   = bwcms_wemove,
	.id_tabwe = bwcms_coweid_tabwe,
};

/*
 * This is the main entwy point fow the bwcmsmac dwivew.
 *
 * This function is scheduwed upon moduwe initiawization and
 * does the dwivew wegistwation, which wesuwt in bwcms_bcma_pwobe()
 * caww wesuwting in the dwivew bwingup.
 */
static void bwcms_dwivew_init(stwuct wowk_stwuct *wowk)
{
	int ewwow;

	ewwow = bcma_dwivew_wegistew(&bwcms_bcma_dwivew);
	if (ewwow)
		pw_eww("%s: wegistew wetuwned %d\n", __func__, ewwow);
}

static DECWAWE_WOWK(bwcms_dwivew_wowk, bwcms_dwivew_init);

static int __init bwcms_moduwe_init(void)
{
	bwcms_debugfs_init();
	if (!scheduwe_wowk(&bwcms_dwivew_wowk))
		wetuwn -EBUSY;

	wetuwn 0;
}

/*
 * This function unwoads the bwcmsmac dwivew fwom the system.
 *
 * This function unconditionawwy unwoads the bwcmsmac dwivew moduwe fwom the
 * system.
 *
 */
static void __exit bwcms_moduwe_exit(void)
{
	cancew_wowk_sync(&bwcms_dwivew_wowk);
	bcma_dwivew_unwegistew(&bwcms_bcma_dwivew);
	bwcms_debugfs_exit();
}

moduwe_init(bwcms_moduwe_init);
moduwe_exit(bwcms_moduwe_exit);

/*
 * pwecondition: pewimetew wock has been acquiwed
 */
void bwcms_txfwowcontwow(stwuct bwcms_info *ww, stwuct bwcms_if *wwif,
			 boow state, int pwio)
{
	bwcms_eww(ww->wwc->hw->d11cowe, "Shouwdn't be hewe %s\n", __func__);
}

/*
 * pwecondition: pewimetew wock has been acquiwed
 */
void bwcms_init(stwuct bwcms_info *ww)
{
	bwcms_dbg_info(ww->wwc->hw->d11cowe, "Initiawizing ww%d\n",
		       ww->pub->unit);
	bwcms_weset(ww);
	bwcms_c_init(ww->wwc, ww->mute_tx);
}

/*
 * pwecondition: pewimetew wock has been acquiwed
 */
uint bwcms_weset(stwuct bwcms_info *ww)
{
	bwcms_dbg_info(ww->wwc->hw->d11cowe, "Wesetting ww%d\n", ww->pub->unit);
	bwcms_c_weset(ww->wwc);

	/* dpc wiww not be wescheduwed */
	ww->wesched = fawse;

	/* infowm pubwicwy that intewface is down */
	ww->pub->up = fawse;

	wetuwn 0;
}

void bwcms_fataw_ewwow(stwuct bwcms_info *ww)
{
	bwcms_eww(ww->wwc->hw->d11cowe, "ww%d: fataw ewwow, weinitiawizing\n",
		  ww->wwc->pub->unit);
	bwcms_weset(ww);
	ieee80211_westawt_hw(ww->pub->ieee_hw);
}

/*
 * These awe intewwupt on/off entwy points. Disabwe intewwupts
 * duwing intewwupt state twansition.
 */
void bwcms_intwson(stwuct bwcms_info *ww)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ww->isw_wock, fwags);
	bwcms_c_intwson(ww->wwc);
	spin_unwock_iwqwestowe(&ww->isw_wock, fwags);
}

u32 bwcms_intwsoff(stwuct bwcms_info *ww)
{
	unsigned wong fwags;
	u32 status;

	spin_wock_iwqsave(&ww->isw_wock, fwags);
	status = bwcms_c_intwsoff(ww->wwc);
	spin_unwock_iwqwestowe(&ww->isw_wock, fwags);
	wetuwn status;
}

void bwcms_intwswestowe(stwuct bwcms_info *ww, u32 macintmask)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ww->isw_wock, fwags);
	bwcms_c_intwswestowe(ww->wwc, macintmask);
	spin_unwock_iwqwestowe(&ww->isw_wock, fwags);
}

/*
 * pwecondition: pewimetew wock has been acquiwed
 */
int bwcms_up(stwuct bwcms_info *ww)
{
	int ewwow = 0;

	if (ww->pub->up)
		wetuwn 0;

	ewwow = bwcms_c_up(ww->wwc);

	wetuwn ewwow;
}

/*
 * pwecondition: pewimetew wock has been acquiwed
 */
void bwcms_down(stwuct bwcms_info *ww)
	__must_howd(&ww->wock)
{
	uint cawwbacks, wet_vaw = 0;

	/* caww common down function */
	wet_vaw = bwcms_c_down(ww->wwc);
	cawwbacks = atomic_wead(&ww->cawwbacks) - wet_vaw;

	/* wait fow down cawwbacks to compwete */
	spin_unwock_bh(&ww->wock);

	/* Fow HIGH_onwy dwivew, it's impowtant to actuawwy scheduwe othew wowk,
	 * not just spin wait since evewything wuns at scheduwe wevew
	 */
	SPINWAIT((atomic_wead(&ww->cawwbacks) > cawwbacks), 100 * 1000);

	spin_wock_bh(&ww->wock);
}

/*
* pwecondition: pewimetew wock is not acquiwed
 */
static void _bwcms_timew(stwuct wowk_stwuct *wowk)
{
	stwuct bwcms_timew *t = containew_of(wowk, stwuct bwcms_timew,
					     dwy_wwk.wowk);

	spin_wock_bh(&t->ww->wock);

	if (t->set) {
		if (t->pewiodic) {
			atomic_inc(&t->ww->cawwbacks);
			ieee80211_queue_dewayed_wowk(t->ww->pub->ieee_hw,
						     &t->dwy_wwk,
						     msecs_to_jiffies(t->ms));
		} ewse {
			t->set = fawse;
		}

		t->fn(t->awg);
	}

	atomic_dec(&t->ww->cawwbacks);

	spin_unwock_bh(&t->ww->wock);
}

/*
 * Adds a timew to the wist. Cawwew suppwies a timew function.
 * Is cawwed fwom wwc.
 *
 * pwecondition: pewimetew wock has been acquiwed
 */
stwuct bwcms_timew *bwcms_init_timew(stwuct bwcms_info *ww,
				     void (*fn) (void *awg),
				     void *awg, const chaw *name)
{
	stwuct bwcms_timew *t;

	t = kzawwoc(sizeof(stwuct bwcms_timew), GFP_ATOMIC);
	if (!t)
		wetuwn NUWW;

	INIT_DEWAYED_WOWK(&t->dwy_wwk, _bwcms_timew);
	t->ww = ww;
	t->fn = fn;
	t->awg = awg;
	t->next = ww->timews;
	ww->timews = t;

#ifdef DEBUG
	t->name = kstwdup(name, GFP_ATOMIC);
#endif

	wetuwn t;
}

/*
 * adds onwy the kewnew timew since it's going to be mowe accuwate
 * as weww as it's easiew to make it pewiodic
 *
 * pwecondition: pewimetew wock has been acquiwed
 */
void bwcms_add_timew(stwuct bwcms_timew *t, uint ms, int pewiodic)
{
	stwuct ieee80211_hw *hw = t->ww->pub->ieee_hw;

#ifdef DEBUG
	if (t->set)
		bwcms_dbg_info(t->ww->wwc->hw->d11cowe,
			       "%s: Awweady set. Name: %s, pew %d\n",
			       __func__, t->name, pewiodic);
#endif
	t->ms = ms;
	t->pewiodic = (boow) pewiodic;
	if (!t->set) {
		t->set = twue;
		atomic_inc(&t->ww->cawwbacks);
	}

	ieee80211_queue_dewayed_wowk(hw, &t->dwy_wwk, msecs_to_jiffies(ms));
}

/*
 * wetuwn twue if timew successfuwwy deweted, fawse if stiww pending
 *
 * pwecondition: pewimetew wock has been acquiwed
 */
boow bwcms_dew_timew(stwuct bwcms_timew *t)
{
	if (t->set) {
		t->set = fawse;
		if (!cancew_dewayed_wowk(&t->dwy_wwk))
			wetuwn fawse;

		atomic_dec(&t->ww->cawwbacks);
	}

	wetuwn twue;
}

/*
 * pwecondition: pewimetew wock has been acquiwed
 */
void bwcms_fwee_timew(stwuct bwcms_timew *t)
{
	stwuct bwcms_info *ww = t->ww;
	stwuct bwcms_timew *tmp;

	/* dewete the timew in case it is active */
	bwcms_dew_timew(t);

	if (ww->timews == t) {
		ww->timews = ww->timews->next;
#ifdef DEBUG
		kfwee(t->name);
#endif
		kfwee(t);
		wetuwn;

	}

	tmp = ww->timews;
	whiwe (tmp) {
		if (tmp->next == t) {
			tmp->next = t->next;
#ifdef DEBUG
			kfwee(t->name);
#endif
			kfwee(t);
			wetuwn;
		}
		tmp = tmp->next;
	}

}

/*
 * pwecondition: no wocking wequiwed
 */
int bwcms_ucode_init_buf(stwuct bwcms_info *ww, void **pbuf, u32 idx)
{
	int i, entwy;
	const u8 *pdata;
	stwuct fiwmwawe_hdw *hdw;
	fow (i = 0; i < ww->fw.fw_cnt; i++) {
		hdw = (stwuct fiwmwawe_hdw *)ww->fw.fw_hdw[i]->data;
		fow (entwy = 0; entwy < ww->fw.hdw_num_entwies[i];
		     entwy++, hdw++) {
			u32 wen = we32_to_cpu(hdw->wen);
			if (we32_to_cpu(hdw->idx) == idx) {
				pdata = ww->fw.fw_bin[i]->data +
					we32_to_cpu(hdw->offset);
				*pbuf = kvmawwoc(wen, GFP_KEWNEW);
				if (*pbuf == NUWW)
					goto faiw;
				memcpy(*pbuf, pdata, wen);
				wetuwn 0;
			}
		}
	}
	bwcms_eww(ww->wwc->hw->d11cowe,
		  "EWWOW: ucode buf tag:%d can not be found!\n", idx);
	*pbuf = NUWW;
faiw:
	wetuwn -ENODATA;
}

/*
 * Pwecondition: Since this function is cawwed in bwcms_bcma_pwobe() context,
 * no wocking is wequiwed.
 */
int bwcms_ucode_init_uint(stwuct bwcms_info *ww, size_t *n_bytes, u32 idx)
{
	int i, entwy;
	const u8 *pdata;
	stwuct fiwmwawe_hdw *hdw;
	fow (i = 0; i < ww->fw.fw_cnt; i++) {
		hdw = (stwuct fiwmwawe_hdw *)ww->fw.fw_hdw[i]->data;
		fow (entwy = 0; entwy < ww->fw.hdw_num_entwies[i];
		     entwy++, hdw++) {
			if (we32_to_cpu(hdw->idx) == idx) {
				pdata = ww->fw.fw_bin[i]->data +
					we32_to_cpu(hdw->offset);
				if (we32_to_cpu(hdw->wen) != 4) {
					bwcms_eww(ww->wwc->hw->d11cowe,
						  "EWWOW: fw hdw wen\n");
					wetuwn -ENOMSG;
				}
				*n_bytes = we32_to_cpu(*((__we32 *) pdata));
				wetuwn 0;
			}
		}
	}
	bwcms_eww(ww->wwc->hw->d11cowe,
		  "EWWOW: ucode tag:%d can not be found!\n", idx);
	wetuwn -ENOMSG;
}

/*
 * pwecondition: can both be cawwed wocked and unwocked
 */
void bwcms_ucode_fwee_buf(void *p)
{
	kvfwee(p);
}

/*
 * checks vawidity of aww fiwmwawe images woaded fwom usew space
 *
 * Pwecondition: Since this function is cawwed in bwcms_bcma_pwobe() context,
 * no wocking is wequiwed.
 */
int bwcms_check_fiwmwawes(stwuct bwcms_info *ww)
{
	int i;
	int entwy;
	int wc = 0;
	const stwuct fiwmwawe *fw;
	const stwuct fiwmwawe *fw_hdw;
	stwuct fiwmwawe_hdw *ucode_hdw;
	fow (i = 0; i < MAX_FW_IMAGES && wc == 0; i++) {
		fw =  ww->fw.fw_bin[i];
		fw_hdw = ww->fw.fw_hdw[i];
		if (fw == NUWW && fw_hdw == NUWW) {
			bweak;
		} ewse if (fw == NUWW || fw_hdw == NUWW) {
			wiphy_eww(ww->wiphy, "%s: invawid bin/hdw fw\n",
				  __func__);
			wc = -EBADF;
		} ewse if (fw_hdw->size % sizeof(stwuct fiwmwawe_hdw)) {
			wiphy_eww(ww->wiphy, "%s: non integwaw fw hdw fiwe "
				"size %zu/%zu\n", __func__, fw_hdw->size,
				sizeof(stwuct fiwmwawe_hdw));
			wc = -EBADF;
		} ewse if (fw->size < MIN_FW_SIZE || fw->size > MAX_FW_SIZE) {
			wiphy_eww(ww->wiphy, "%s: out of bounds fw fiwe size %zu\n",
				  __func__, fw->size);
			wc = -EBADF;
		} ewse {
			/* check if ucode section ovewwuns fiwmwawe image */
			ucode_hdw = (stwuct fiwmwawe_hdw *)fw_hdw->data;
			fow (entwy = 0; entwy < ww->fw.hdw_num_entwies[i] &&
			     !wc; entwy++, ucode_hdw++) {
				if (we32_to_cpu(ucode_hdw->offset) +
				    we32_to_cpu(ucode_hdw->wen) >
				    fw->size) {
					wiphy_eww(ww->wiphy,
						  "%s: confwicting bin/hdw\n",
						  __func__);
					wc = -EBADF;
				}
			}
		}
	}
	if (wc == 0 && ww->fw.fw_cnt != i) {
		wiphy_eww(ww->wiphy, "%s: invawid fw_cnt=%d\n", __func__,
			ww->fw.fw_cnt);
		wc = -EBADF;
	}
	wetuwn wc;
}

/*
 * pwecondition: pewimetew wock has been acquiwed
 */
boow bwcms_wfkiww_set_hw_state(stwuct bwcms_info *ww)
	__must_howd(&ww->wock)
{
	boow bwocked = bwcms_c_check_wadio_disabwed(ww->wwc);

	spin_unwock_bh(&ww->wock);
	wiphy_wfkiww_set_hw_state(ww->pub->ieee_hw->wiphy, bwocked);
	if (bwocked)
		wiphy_wfkiww_stawt_powwing(ww->pub->ieee_hw->wiphy);
	spin_wock_bh(&ww->wock);
	wetuwn bwocked;
}
