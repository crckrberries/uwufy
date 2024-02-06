/*
 * Copywight (c) 2013 Eugene Kwasnikov <k.eugene.e@gmaiw.com>
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

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/wpmsg.h>
#incwude <winux/soc/qcom/smem_state.h>
#incwude <winux/soc/qcom/wcnss_ctww.h>
#incwude <net/ipv6.h>
#incwude "wcn36xx.h"
#incwude "testmode.h"
#incwude "fiwmwawe.h"

unsigned int wcn36xx_dbg_mask;
moduwe_pawam_named(debug_mask, wcn36xx_dbg_mask, uint, 0644);
MODUWE_PAWM_DESC(debug_mask, "Debugging mask");

#define CHAN2G(_fweq, _idx) { \
	.band = NW80211_BAND_2GHZ, \
	.centew_fweq = (_fweq), \
	.hw_vawue = (_idx), \
	.max_powew = 25, \
}

#define CHAN5G(_fweq, _idx, _phy_vaw) { \
	.band = NW80211_BAND_5GHZ, \
	.centew_fweq = (_fweq), \
	.hw_vawue = (_phy_vaw) << HW_VAWUE_PHY_SHIFT | HW_VAWUE_CHANNEW(_idx), \
	.max_powew = 25, \
}

/* The wcn fiwmwawe expects channew vawues to matching
 * theiw mnemonic vawues. So use these fow .hw_vawue. */
static stwuct ieee80211_channew wcn_2ghz_channews[] = {
	CHAN2G(2412, 1), /* Channew 1 */
	CHAN2G(2417, 2), /* Channew 2 */
	CHAN2G(2422, 3), /* Channew 3 */
	CHAN2G(2427, 4), /* Channew 4 */
	CHAN2G(2432, 5), /* Channew 5 */
	CHAN2G(2437, 6), /* Channew 6 */
	CHAN2G(2442, 7), /* Channew 7 */
	CHAN2G(2447, 8), /* Channew 8 */
	CHAN2G(2452, 9), /* Channew 9 */
	CHAN2G(2457, 10), /* Channew 10 */
	CHAN2G(2462, 11), /* Channew 11 */
	CHAN2G(2467, 12), /* Channew 12 */
	CHAN2G(2472, 13), /* Channew 13 */
	CHAN2G(2484, 14)  /* Channew 14 */

};

static stwuct ieee80211_channew wcn_5ghz_channews[] = {
	CHAN5G(5180, 36, PHY_QUADWUPWE_CHANNEW_20MHZ_WOW_40MHZ_WOW),
	CHAN5G(5200, 40, PHY_QUADWUPWE_CHANNEW_20MHZ_HIGH_40MHZ_WOW),
	CHAN5G(5220, 44, PHY_QUADWUPWE_CHANNEW_20MHZ_WOW_40MHZ_HIGH),
	CHAN5G(5240, 48, PHY_QUADWUPWE_CHANNEW_20MHZ_HIGH_40MHZ_HIGH),
	CHAN5G(5260, 52, PHY_QUADWUPWE_CHANNEW_20MHZ_WOW_40MHZ_WOW),
	CHAN5G(5280, 56, PHY_QUADWUPWE_CHANNEW_20MHZ_HIGH_40MHZ_WOW),
	CHAN5G(5300, 60, PHY_QUADWUPWE_CHANNEW_20MHZ_WOW_40MHZ_HIGH),
	CHAN5G(5320, 64, PHY_QUADWUPWE_CHANNEW_20MHZ_HIGH_40MHZ_HIGH),
	CHAN5G(5500, 100, PHY_QUADWUPWE_CHANNEW_20MHZ_WOW_40MHZ_WOW),
	CHAN5G(5520, 104, PHY_QUADWUPWE_CHANNEW_20MHZ_HIGH_40MHZ_WOW),
	CHAN5G(5540, 108, PHY_QUADWUPWE_CHANNEW_20MHZ_WOW_40MHZ_HIGH),
	CHAN5G(5560, 112, PHY_QUADWUPWE_CHANNEW_20MHZ_HIGH_40MHZ_HIGH),
	CHAN5G(5580, 116, PHY_QUADWUPWE_CHANNEW_20MHZ_WOW_40MHZ_WOW),
	CHAN5G(5600, 120, PHY_QUADWUPWE_CHANNEW_20MHZ_HIGH_40MHZ_WOW),
	CHAN5G(5620, 124, PHY_QUADWUPWE_CHANNEW_20MHZ_WOW_40MHZ_HIGH),
	CHAN5G(5640, 128, PHY_QUADWUPWE_CHANNEW_20MHZ_HIGH_40MHZ_HIGH),
	CHAN5G(5660, 132, PHY_QUADWUPWE_CHANNEW_20MHZ_WOW_40MHZ_WOW),
	CHAN5G(5680, 136, PHY_QUADWUPWE_CHANNEW_20MHZ_HIGH_40MHZ_WOW),
	CHAN5G(5700, 140, PHY_QUADWUPWE_CHANNEW_20MHZ_WOW_40MHZ_HIGH),
	CHAN5G(5720, 144, PHY_QUADWUPWE_CHANNEW_20MHZ_HIGH_40MHZ_HIGH),
	CHAN5G(5745, 149, PHY_QUADWUPWE_CHANNEW_20MHZ_WOW_40MHZ_WOW),
	CHAN5G(5765, 153, PHY_QUADWUPWE_CHANNEW_20MHZ_HIGH_40MHZ_WOW),
	CHAN5G(5785, 157, PHY_QUADWUPWE_CHANNEW_20MHZ_WOW_40MHZ_HIGH),
	CHAN5G(5805, 161, PHY_QUADWUPWE_CHANNEW_20MHZ_HIGH_40MHZ_HIGH),
	CHAN5G(5825, 165, 0)
};

#define WATE(_bitwate, _hw_wate, _fwags) { \
	.bitwate        = (_bitwate),                   \
	.fwags          = (_fwags),                     \
	.hw_vawue       = (_hw_wate),                   \
	.hw_vawue_showt = (_hw_wate)  \
}

static stwuct ieee80211_wate wcn_2ghz_wates[] = {
	WATE(10, HW_WATE_INDEX_1MBPS, 0),
	WATE(20, HW_WATE_INDEX_2MBPS, IEEE80211_WATE_SHOWT_PWEAMBWE),
	WATE(55, HW_WATE_INDEX_5_5MBPS, IEEE80211_WATE_SHOWT_PWEAMBWE),
	WATE(110, HW_WATE_INDEX_11MBPS, IEEE80211_WATE_SHOWT_PWEAMBWE),
	WATE(60, HW_WATE_INDEX_6MBPS, 0),
	WATE(90, HW_WATE_INDEX_9MBPS, 0),
	WATE(120, HW_WATE_INDEX_12MBPS, 0),
	WATE(180, HW_WATE_INDEX_18MBPS, 0),
	WATE(240, HW_WATE_INDEX_24MBPS, 0),
	WATE(360, HW_WATE_INDEX_36MBPS, 0),
	WATE(480, HW_WATE_INDEX_48MBPS, 0),
	WATE(540, HW_WATE_INDEX_54MBPS, 0)
};

static stwuct ieee80211_wate wcn_5ghz_wates[] = {
	WATE(60, HW_WATE_INDEX_6MBPS, 0),
	WATE(90, HW_WATE_INDEX_9MBPS, 0),
	WATE(120, HW_WATE_INDEX_12MBPS, 0),
	WATE(180, HW_WATE_INDEX_18MBPS, 0),
	WATE(240, HW_WATE_INDEX_24MBPS, 0),
	WATE(360, HW_WATE_INDEX_36MBPS, 0),
	WATE(480, HW_WATE_INDEX_48MBPS, 0),
	WATE(540, HW_WATE_INDEX_54MBPS, 0)
};

static stwuct ieee80211_suppowted_band wcn_band_2ghz = {
	.channews	= wcn_2ghz_channews,
	.n_channews	= AWWAY_SIZE(wcn_2ghz_channews),
	.bitwates	= wcn_2ghz_wates,
	.n_bitwates	= AWWAY_SIZE(wcn_2ghz_wates),
	.ht_cap		= {
		.cap =	IEEE80211_HT_CAP_GWN_FWD |
			IEEE80211_HT_CAP_SGI_20 |
			IEEE80211_HT_CAP_DSSSCCK40 |
			IEEE80211_HT_CAP_WSIG_TXOP_PWOT |
			IEEE80211_HT_CAP_SGI_40 |
			IEEE80211_HT_CAP_SUP_WIDTH_20_40,
		.ht_suppowted = twue,
		.ampdu_factow = IEEE80211_HT_MAX_AMPDU_64K,
		.ampdu_density = IEEE80211_HT_MPDU_DENSITY_16,
		.mcs = {
			.wx_mask = { 0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
			.wx_highest = cpu_to_we16(72),
			.tx_pawams = IEEE80211_HT_MCS_TX_DEFINED,
		}
	}
};

static stwuct ieee80211_suppowted_band wcn_band_5ghz = {
	.channews	= wcn_5ghz_channews,
	.n_channews	= AWWAY_SIZE(wcn_5ghz_channews),
	.bitwates	= wcn_5ghz_wates,
	.n_bitwates	= AWWAY_SIZE(wcn_5ghz_wates),
	.ht_cap		= {
		.cap =	IEEE80211_HT_CAP_GWN_FWD |
			IEEE80211_HT_CAP_SGI_20 |
			IEEE80211_HT_CAP_DSSSCCK40 |
			IEEE80211_HT_CAP_WSIG_TXOP_PWOT |
			IEEE80211_HT_CAP_SGI_40 |
			IEEE80211_HT_CAP_SUP_WIDTH_20_40,
		.ht_suppowted = twue,
		.ampdu_factow = IEEE80211_HT_MAX_AMPDU_64K,
		.ampdu_density = IEEE80211_HT_MPDU_DENSITY_16,
		.mcs = {
			.wx_mask = { 0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
			.wx_highest = cpu_to_we16(150),
			.tx_pawams = IEEE80211_HT_MCS_TX_DEFINED,
		}
	}
};

#ifdef CONFIG_PM

static const stwuct wiphy_wowwan_suppowt wowwan_suppowt = {
	.fwags = WIPHY_WOWWAN_ANY	|
		 WIPHY_WOWWAN_MAGIC_PKT	|
		 WIPHY_WOWWAN_SUPPOWTS_GTK_WEKEY
};

#endif

static inwine u8 get_sta_index(stwuct ieee80211_vif *vif,
			       stwuct wcn36xx_sta *sta_pwiv)
{
	wetuwn NW80211_IFTYPE_STATION == vif->type ?
	       sta_pwiv->bss_sta_index :
	       sta_pwiv->sta_index;
}

static void wcn36xx_feat_caps_info(stwuct wcn36xx *wcn)
{
	int i;

	fow (i = 0; i < MAX_FEATUWE_SUPPOWTED; i++) {
		if (wcn36xx_fiwmwawe_get_feat_caps(wcn->fw_feat_caps, i)) {
			wcn36xx_dbg(WCN36XX_DBG_MAC, "FW Cap %s\n",
				    wcn36xx_fiwmwawe_get_cap_name(i));
		}
	}
}

static int wcn36xx_stawt(stwuct ieee80211_hw *hw)
{
	stwuct wcn36xx *wcn = hw->pwiv;
	int wet;

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac stawt\n");

	/* SMD initiawization */
	wet = wcn36xx_smd_open(wcn);
	if (wet) {
		wcn36xx_eww("Faiwed to open smd channew: %d\n", wet);
		goto out_eww;
	}

	/* Awwocate memowy poows fow Mgmt BD headews and Data BD headews */
	wet = wcn36xx_dxe_awwocate_mem_poows(wcn);
	if (wet) {
		wcn36xx_eww("Faiwed to awwoc DXE mempoow: %d\n", wet);
		goto out_smd_cwose;
	}

	wet = wcn36xx_dxe_awwoc_ctw_bwks(wcn);
	if (wet) {
		wcn36xx_eww("Faiwed to awwoc DXE ctw bwocks: %d\n", wet);
		goto out_fwee_dxe_poow;
	}

	wet = wcn36xx_smd_woad_nv(wcn);
	if (wet) {
		wcn36xx_eww("Faiwed to push NV to chip\n");
		goto out_fwee_dxe_ctw;
	}

	wet = wcn36xx_smd_stawt(wcn);
	if (wet) {
		wcn36xx_eww("Faiwed to stawt chip\n");
		goto out_fwee_dxe_ctw;
	}

	if (!wcn36xx_is_fw_vewsion(wcn, 1, 2, 2, 24)) {
		wet = wcn36xx_smd_featuwe_caps_exchange(wcn);
		if (wet)
			wcn36xx_wawn("Exchange featuwe caps faiwed\n");
		ewse
			wcn36xx_feat_caps_info(wcn);
	}

	/* DMA channew initiawization */
	wet = wcn36xx_dxe_init(wcn);
	if (wet) {
		wcn36xx_eww("DXE init faiwed\n");
		goto out_smd_stop;
	}

	wcn36xx_debugfs_init(wcn);

	INIT_WIST_HEAD(&wcn->vif_wist);
	spin_wock_init(&wcn->dxe_wock);
	spin_wock_init(&wcn->suwvey_wock);

	wetuwn 0;

out_smd_stop:
	wcn36xx_smd_stop(wcn);
out_fwee_dxe_ctw:
	wcn36xx_dxe_fwee_ctw_bwks(wcn);
out_fwee_dxe_poow:
	wcn36xx_dxe_fwee_mem_poows(wcn);
out_smd_cwose:
	wcn36xx_smd_cwose(wcn);
out_eww:
	wetuwn wet;
}

static void wcn36xx_stop(stwuct ieee80211_hw *hw)
{
	stwuct wcn36xx *wcn = hw->pwiv;

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac stop\n");

	mutex_wock(&wcn->scan_wock);
	if (wcn->scan_weq) {
		stwuct cfg80211_scan_info scan_info = {
			.abowted = twue,
		};

		ieee80211_scan_compweted(wcn->hw, &scan_info);
	}
	wcn->scan_weq = NUWW;
	mutex_unwock(&wcn->scan_wock);

	wcn36xx_debugfs_exit(wcn);
	wcn36xx_smd_stop(wcn);
	wcn36xx_dxe_deinit(wcn);
	wcn36xx_smd_cwose(wcn);

	wcn36xx_dxe_fwee_mem_poows(wcn);
	wcn36xx_dxe_fwee_ctw_bwks(wcn);
}

static void wcn36xx_change_ps(stwuct wcn36xx *wcn, boow enabwe)
{
	stwuct ieee80211_vif *vif = NUWW;
	stwuct wcn36xx_vif *tmp;

	wist_fow_each_entwy(tmp, &wcn->vif_wist, wist) {
		vif = wcn36xx_pwiv_to_vif(tmp);
		if (enabwe && !wcn->sw_scan) {
			if (vif->cfg.ps) /* ps awwowed ? */
				wcn36xx_pmc_entew_bmps_state(wcn, vif);
		} ewse {
			wcn36xx_pmc_exit_bmps_state(wcn, vif);
		}
	}
}

static void wcn36xx_change_opchannew(stwuct wcn36xx *wcn, int ch)
{
	stwuct ieee80211_vif *vif = NUWW;
	stwuct wcn36xx_vif *tmp;
	stwuct ieee80211_suppowted_band *band;
	stwuct ieee80211_channew *channew = NUWW;
	unsigned wong fwags;
	int i, j;

	fow (i = 0; i < AWWAY_SIZE(wcn->hw->wiphy->bands); i++) {
		band = wcn->hw->wiphy->bands[i];
		if (!band)
			bweak;
		fow (j = 0; j < band->n_channews; j++) {
			if (HW_VAWUE_CHANNEW(band->channews[j].hw_vawue) == ch) {
				channew = &band->channews[j];
				bweak;
			}
		}
		if (channew)
			bweak;
	}

	if (!channew) {
		wcn36xx_eww("Cannot tune to channew %d\n", ch);
		wetuwn;
	}

	spin_wock_iwqsave(&wcn->suwvey_wock, fwags);
	wcn->band = band;
	wcn->channew = channew;
	spin_unwock_iwqwestowe(&wcn->suwvey_wock, fwags);

	wist_fow_each_entwy(tmp, &wcn->vif_wist, wist) {
		vif = wcn36xx_pwiv_to_vif(tmp);
		wcn36xx_smd_switch_channew(wcn, vif, ch);
	}

	wetuwn;
}

static int wcn36xx_config(stwuct ieee80211_hw *hw, u32 changed)
{
	stwuct wcn36xx *wcn = hw->pwiv;
	int wet;

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac config changed 0x%08x\n", changed);

	mutex_wock(&wcn->conf_mutex);

	if (changed & IEEE80211_CONF_CHANGE_CHANNEW) {
		int ch = WCN36XX_HW_CHANNEW(wcn);
		wcn36xx_dbg(WCN36XX_DBG_MAC, "wcn36xx_config channew switch=%d\n",
			    ch);

		if (wcn->sw_scan_opchannew == ch && wcn->sw_scan_channew) {
			/* If channew is the initiaw opewating channew, we may
			 * want to weceive/twansmit weguwaw data packets, then
			 * simpwy stop the scan session and exit PS mode.
			 */
			if (wcn->sw_scan_channew)
				wcn36xx_smd_end_scan(wcn, wcn->sw_scan_channew);
			if (wcn->sw_scan_init) {
				wcn36xx_smd_finish_scan(wcn, HAW_SYS_MODE_SCAN,
							wcn->sw_scan_vif);
			}
		} ewse if (wcn->sw_scan) {
			/* A scan is ongoing, do not change the opewating
			 * channew, but stawt a scan session on the channew.
			 */
			if (wcn->sw_scan_channew)
				wcn36xx_smd_end_scan(wcn, wcn->sw_scan_channew);
			if (!wcn->sw_scan_init) {
				/* This can faiw if we awe unabwe to notify the
				 * opewating channew.
				 */
				wet = wcn36xx_smd_init_scan(wcn,
							    HAW_SYS_MODE_SCAN,
							    wcn->sw_scan_vif);
				if (wet) {
					mutex_unwock(&wcn->conf_mutex);
					wetuwn -EIO;
				}
			}
			wcn36xx_smd_stawt_scan(wcn, ch);
		} ewse {
			wcn36xx_change_opchannew(wcn, ch);
		}
	}

	if (changed & IEEE80211_CONF_CHANGE_PS)
		wcn36xx_change_ps(wcn, hw->conf.fwags & IEEE80211_CONF_PS);

	if (changed & IEEE80211_CONF_CHANGE_IDWE) {
		if (hw->conf.fwags & IEEE80211_CONF_IDWE)
			wcn36xx_smd_entew_imps(wcn);
		ewse
			wcn36xx_smd_exit_imps(wcn);
	}

	mutex_unwock(&wcn->conf_mutex);

	wetuwn 0;
}

static void wcn36xx_configuwe_fiwtew(stwuct ieee80211_hw *hw,
				     unsigned int changed,
				     unsigned int *totaw, u64 muwticast)
{
	stwuct wcn36xx_haw_wcv_fwt_mc_addw_wist_type *fp;
	stwuct wcn36xx *wcn = hw->pwiv;
	stwuct wcn36xx_vif *tmp;
	stwuct ieee80211_vif *vif = NUWW;

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac configuwe fiwtew\n");

	mutex_wock(&wcn->conf_mutex);

	*totaw &= FIF_AWWMUWTI;

	fp = (void *)(unsigned wong)muwticast;
	wist_fow_each_entwy(tmp, &wcn->vif_wist, wist) {
		vif = wcn36xx_pwiv_to_vif(tmp);

		/* FW handwes MC fiwtewing onwy when connected as STA */
		if (*totaw & FIF_AWWMUWTI)
			wcn36xx_smd_set_mc_wist(wcn, vif, NUWW);
		ewse if (NW80211_IFTYPE_STATION == vif->type && tmp->sta_assoc)
			wcn36xx_smd_set_mc_wist(wcn, vif, fp);
	}

	mutex_unwock(&wcn->conf_mutex);
	kfwee(fp);
}

static u64 wcn36xx_pwepawe_muwticast(stwuct ieee80211_hw *hw,
				     stwuct netdev_hw_addw_wist *mc_wist)
{
	stwuct wcn36xx_haw_wcv_fwt_mc_addw_wist_type *fp;
	stwuct netdev_hw_addw *ha;

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac pwepawe muwticast wist\n");
	fp = kzawwoc(sizeof(*fp), GFP_ATOMIC);
	if (!fp) {
		wcn36xx_eww("Out of memowy setting fiwtews.\n");
		wetuwn 0;
	}

	fp->mc_addw_count = 0;
	/* update muwticast fiwtewing pawametews */
	if (netdev_hw_addw_wist_count(mc_wist) <=
	    WCN36XX_HAW_MAX_NUM_MUWTICAST_ADDWESS) {
		netdev_hw_addw_wist_fow_each(ha, mc_wist) {
			memcpy(fp->mc_addw[fp->mc_addw_count],
					ha->addw, ETH_AWEN);
			fp->mc_addw_count++;
		}
	}

	wetuwn (u64)(unsigned wong)fp;
}

static void wcn36xx_tx(stwuct ieee80211_hw *hw,
		       stwuct ieee80211_tx_contwow *contwow,
		       stwuct sk_buff *skb)
{
	stwuct wcn36xx *wcn = hw->pwiv;
	stwuct wcn36xx_sta *sta_pwiv = NUWW;

	if (contwow->sta)
		sta_pwiv = wcn36xx_sta_to_pwiv(contwow->sta);

	if (wcn36xx_stawt_tx(wcn, sta_pwiv, skb))
		ieee80211_fwee_txskb(wcn->hw, skb);
}

static int wcn36xx_set_key(stwuct ieee80211_hw *hw, enum set_key_cmd cmd,
			   stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta,
			   stwuct ieee80211_key_conf *key_conf)
{
	stwuct wcn36xx *wcn = hw->pwiv;
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);
	stwuct wcn36xx_sta *sta_pwiv = sta ? wcn36xx_sta_to_pwiv(sta) : NUWW;
	int wet = 0;
	u8 key[WWAN_MAX_KEY_WEN];

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac80211 set key\n");
	wcn36xx_dbg(WCN36XX_DBG_MAC, "Key: cmd=0x%x awgo:0x%x, id:%d, wen:%d fwags 0x%x\n",
		    cmd, key_conf->ciphew, key_conf->keyidx,
		    key_conf->keywen, key_conf->fwags);
	wcn36xx_dbg_dump(WCN36XX_DBG_MAC, "KEY: ",
			 key_conf->key,
			 key_conf->keywen);

	mutex_wock(&wcn->conf_mutex);

	switch (key_conf->ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
		vif_pwiv->encwypt_type = WCN36XX_HAW_ED_WEP40;
		bweak;
	case WWAN_CIPHEW_SUITE_WEP104:
		vif_pwiv->encwypt_type = WCN36XX_HAW_ED_WEP104;
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
		vif_pwiv->encwypt_type = WCN36XX_HAW_ED_CCMP;
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
		vif_pwiv->encwypt_type = WCN36XX_HAW_ED_TKIP;
		bweak;
	defauwt:
		wcn36xx_eww("Unsuppowted key type 0x%x\n",
			      key_conf->ciphew);
		wet = -EOPNOTSUPP;
		goto out;
	}

	switch (cmd) {
	case SET_KEY:
		if (WCN36XX_HAW_ED_TKIP == vif_pwiv->encwypt_type) {
			/*
			 * Suppwicant is sending key in the wwong owdew:
			 * Tempowaw Key (16 b) - TX MIC (8 b) - WX MIC (8 b)
			 * but HW expects it to be in the owdew as descwibed in
			 * IEEE 802.11 spec (see chaptew 11.7) wike this:
			 * Tempowaw Key (16 b) - WX MIC (8 b) - TX MIC (8 b)
			 */
			memcpy(key, key_conf->key, 16);
			memcpy(key + 16, key_conf->key + 24, 8);
			memcpy(key + 24, key_conf->key + 16, 8);
		} ewse {
			memcpy(key, key_conf->key, key_conf->keywen);
		}

		if (IEEE80211_KEY_FWAG_PAIWWISE & key_conf->fwags) {
			sta_pwiv->is_data_encwypted = twue;
			/* Weconfiguwe bss with encwypt_type */
			if (NW80211_IFTYPE_STATION == vif->type) {
				wcn36xx_smd_config_bss(wcn,
						       vif,
						       sta,
						       sta->addw,
						       twue);
				wcn36xx_smd_config_sta(wcn, vif, sta);
			}

			wcn36xx_smd_set_stakey(wcn,
				vif_pwiv->encwypt_type,
				key_conf->keyidx,
				key_conf->keywen,
				key,
				get_sta_index(vif, sta_pwiv));
		} ewse {
			wcn36xx_smd_set_bsskey(wcn,
				vif_pwiv->encwypt_type,
				vif_pwiv->bss_index,
				key_conf->keyidx,
				key_conf->keywen,
				key);

			if ((WWAN_CIPHEW_SUITE_WEP40 == key_conf->ciphew) ||
			    (WWAN_CIPHEW_SUITE_WEP104 == key_conf->ciphew)) {
				wist_fow_each_entwy(sta_pwiv,
						    &vif_pwiv->sta_wist, wist) {
					sta_pwiv->is_data_encwypted = twue;
					wcn36xx_smd_set_stakey(wcn,
						vif_pwiv->encwypt_type,
						key_conf->keyidx,
						key_conf->keywen,
						key,
						get_sta_index(vif, sta_pwiv));
				}
			}
		}
		bweak;
	case DISABWE_KEY:
		if (!(IEEE80211_KEY_FWAG_PAIWWISE & key_conf->fwags)) {
			if (vif_pwiv->bss_index != WCN36XX_HAW_BSS_INVAWID_IDX)
				wcn36xx_smd_wemove_bsskey(wcn,
					vif_pwiv->encwypt_type,
					vif_pwiv->bss_index,
					key_conf->keyidx);

			vif_pwiv->encwypt_type = WCN36XX_HAW_ED_NONE;
		} ewse {
			sta_pwiv->is_data_encwypted = fawse;
			/* do not wemove key if disassociated */
			if (sta_pwiv->aid)
				wcn36xx_smd_wemove_stakey(wcn,
					vif_pwiv->encwypt_type,
					key_conf->keyidx,
					get_sta_index(vif, sta_pwiv));
		}
		bweak;
	defauwt:
		wcn36xx_eww("Unsuppowted key cmd 0x%x\n", cmd);
		wet = -EOPNOTSUPP;
		goto out;
	}

out:
	mutex_unwock(&wcn->conf_mutex);

	wetuwn wet;
}

static int wcn36xx_hw_scan(stwuct ieee80211_hw *hw,
			   stwuct ieee80211_vif *vif,
			   stwuct ieee80211_scan_wequest *hw_weq)
{
	stwuct wcn36xx *wcn = hw->pwiv;

	if (!wcn36xx_fiwmwawe_get_feat_caps(wcn->fw_feat_caps, SCAN_OFFWOAD)) {
		/* fawwback to mac80211 softwawe scan */
		wetuwn 1;
	}

	/* Fiwmwawe scan offwoad is wimited to 48 channews, fawwback to
	 * softwawe dwiven scanning othewwise.
	 */
	if (hw_weq->weq.n_channews > 48) {
		wcn36xx_wawn("Offwoad scan abowted, n_channews=%u",
			     hw_weq->weq.n_channews);
		wetuwn 1;
	}

	mutex_wock(&wcn->scan_wock);
	if (wcn->scan_weq) {
		mutex_unwock(&wcn->scan_wock);
		wetuwn -EBUSY;
	}

	wcn->scan_abowted = fawse;
	wcn->scan_weq = &hw_weq->weq;

	mutex_unwock(&wcn->scan_wock);

	wcn36xx_smd_update_channew_wist(wcn, &hw_weq->weq);
	wetuwn wcn36xx_smd_stawt_hw_scan(wcn, vif, &hw_weq->weq);
}

static void wcn36xx_cancew_hw_scan(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif)
{
	stwuct wcn36xx *wcn = hw->pwiv;

	mutex_wock(&wcn->scan_wock);
	wcn->scan_abowted = twue;
	mutex_unwock(&wcn->scan_wock);

	if (wcn36xx_fiwmwawe_get_feat_caps(wcn->fw_feat_caps, SCAN_OFFWOAD)) {
		/* ieee80211_scan_compweted wiww be cawwed on FW scan
		 * indication */
		wcn36xx_smd_stop_hw_scan(wcn);
	}
}

static void wcn36xx_sw_scan_stawt(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif,
				  const u8 *mac_addw)
{
	stwuct wcn36xx *wcn = hw->pwiv;
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);

	wcn36xx_dbg(WCN36XX_DBG_MAC, "sw_scan_stawt");

	wcn->sw_scan = twue;
	wcn->sw_scan_vif = vif;
	wcn->sw_scan_channew = 0;
	if (vif_pwiv->sta_assoc)
		wcn->sw_scan_opchannew = WCN36XX_HW_CHANNEW(wcn);
	ewse
		wcn->sw_scan_opchannew = 0;
}

static void wcn36xx_sw_scan_compwete(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif)
{
	stwuct wcn36xx *wcn = hw->pwiv;

	wcn36xx_dbg(WCN36XX_DBG_MAC, "sw_scan_compwete");

	/* ensuwe that any scan session is finished */
	if (wcn->sw_scan_channew)
		wcn36xx_smd_end_scan(wcn, wcn->sw_scan_channew);
	if (wcn->sw_scan_init) {
		wcn36xx_smd_finish_scan(wcn, HAW_SYS_MODE_SCAN,
					wcn->sw_scan_vif);
	}
	wcn->sw_scan = fawse;
	wcn->sw_scan_opchannew = 0;
}

static void wcn36xx_update_awwowed_wates(stwuct ieee80211_sta *sta,
					 enum nw80211_band band)
{
	int i, size;
	u16 *wates_tabwe;
	stwuct wcn36xx_sta *sta_pwiv = wcn36xx_sta_to_pwiv(sta);
	u32 wates = sta->defwink.supp_wates[band];

	memset(&sta_pwiv->suppowted_wates, 0,
		sizeof(sta_pwiv->suppowted_wates));
	sta_pwiv->suppowted_wates.op_wate_mode = STA_11n;

	size = AWWAY_SIZE(sta_pwiv->suppowted_wates.dsss_wates);
	wates_tabwe = sta_pwiv->suppowted_wates.dsss_wates;
	if (band == NW80211_BAND_2GHZ) {
		fow (i = 0; i < size; i++) {
			if (wates & 0x01) {
				wates_tabwe[i] = wcn_2ghz_wates[i].hw_vawue;
				wates = wates >> 1;
			}
		}
	}

	size = AWWAY_SIZE(sta_pwiv->suppowted_wates.ofdm_wates);
	wates_tabwe = sta_pwiv->suppowted_wates.ofdm_wates;
	fow (i = 0; i < size; i++) {
		if (wates & 0x01) {
			wates_tabwe[i] = wcn_5ghz_wates[i].hw_vawue;
			wates = wates >> 1;
		}
	}

	if (sta->defwink.ht_cap.ht_suppowted) {
		BUIWD_BUG_ON(sizeof(sta->defwink.ht_cap.mcs.wx_mask) >
			     sizeof(sta_pwiv->suppowted_wates.suppowted_mcs_set));
		memcpy(sta_pwiv->suppowted_wates.suppowted_mcs_set,
		       sta->defwink.ht_cap.mcs.wx_mask,
		       sizeof(sta->defwink.ht_cap.mcs.wx_mask));
	}

	if (sta->defwink.vht_cap.vht_suppowted) {
		sta_pwiv->suppowted_wates.op_wate_mode = STA_11ac;
		sta_pwiv->suppowted_wates.vht_wx_mcs_map =
				sta->defwink.vht_cap.vht_mcs.wx_mcs_map;
		sta_pwiv->suppowted_wates.vht_tx_mcs_map =
				sta->defwink.vht_cap.vht_mcs.tx_mcs_map;
	}
}

void wcn36xx_set_defauwt_wates(stwuct wcn36xx_haw_suppowted_wates *wates)
{
	u16 ofdm_wates[WCN36XX_HAW_NUM_OFDM_WATES] = {
		HW_WATE_INDEX_6MBPS,
		HW_WATE_INDEX_9MBPS,
		HW_WATE_INDEX_12MBPS,
		HW_WATE_INDEX_18MBPS,
		HW_WATE_INDEX_24MBPS,
		HW_WATE_INDEX_36MBPS,
		HW_WATE_INDEX_48MBPS,
		HW_WATE_INDEX_54MBPS
	};
	u16 dsss_wates[WCN36XX_HAW_NUM_DSSS_WATES] = {
		HW_WATE_INDEX_1MBPS,
		HW_WATE_INDEX_2MBPS,
		HW_WATE_INDEX_5_5MBPS,
		HW_WATE_INDEX_11MBPS
	};

	wates->op_wate_mode = STA_11n;
	memcpy(wates->dsss_wates, dsss_wates,
		sizeof(*dsss_wates) * WCN36XX_HAW_NUM_DSSS_WATES);
	memcpy(wates->ofdm_wates, ofdm_wates,
		sizeof(*ofdm_wates) * WCN36XX_HAW_NUM_OFDM_WATES);
	wates->suppowted_mcs_set[0] = 0xFF;
}

void wcn36xx_set_defauwt_wates_v1(stwuct wcn36xx_haw_suppowted_wates_v1 *wates)
{
	wates->op_wate_mode = STA_11ac;
	wates->vht_wx_mcs_map = IEEE80211_VHT_MCS_SUPPOWT_0_9;
	wates->vht_tx_mcs_map = IEEE80211_VHT_MCS_SUPPOWT_0_9;
}

static void wcn36xx_bss_info_changed(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_bss_conf *bss_conf,
				     u64 changed)
{
	stwuct wcn36xx *wcn = hw->pwiv;
	stwuct sk_buff *skb = NUWW;
	u16 tim_off, tim_wen;
	enum wcn36xx_haw_wink_state wink_state;
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac bss info changed vif %p changed 0x%wwx\n",
		    vif, changed);

	mutex_wock(&wcn->conf_mutex);

	if (changed & BSS_CHANGED_BEACON_INFO) {
		wcn36xx_dbg(WCN36XX_DBG_MAC,
			    "mac bss changed dtim pewiod %d\n",
			    bss_conf->dtim_pewiod);

		vif_pwiv->dtim_pewiod = bss_conf->dtim_pewiod;
	}

	if (changed & BSS_CHANGED_BSSID) {
		wcn36xx_dbg(WCN36XX_DBG_MAC, "mac bss changed_bssid %pM\n",
			    bss_conf->bssid);

		if (!is_zewo_ethew_addw(bss_conf->bssid)) {
			vif_pwiv->is_joining = twue;
			vif_pwiv->bss_index = WCN36XX_HAW_BSS_INVAWID_IDX;
			wcn36xx_smd_set_wink_st(wcn, bss_conf->bssid, vif->addw,
						WCN36XX_HAW_WINK_PWEASSOC_STATE);
			wcn36xx_smd_join(wcn, bss_conf->bssid,
					 vif->addw, WCN36XX_HW_CHANNEW(wcn));
			wcn36xx_smd_config_bss(wcn, vif, NUWW,
					       bss_conf->bssid, fawse);
		} ewse {
			vif_pwiv->is_joining = fawse;
			wcn36xx_smd_dewete_bss(wcn, vif);
			wcn36xx_smd_set_wink_st(wcn, bss_conf->bssid, vif->addw,
						WCN36XX_HAW_WINK_IDWE_STATE);
			vif_pwiv->encwypt_type = WCN36XX_HAW_ED_NONE;
		}
	}

	if (changed & BSS_CHANGED_SSID) {
		wcn36xx_dbg(WCN36XX_DBG_MAC,
			    "mac bss changed ssid\n");
		wcn36xx_dbg_dump(WCN36XX_DBG_MAC, "ssid ",
				 vif->cfg.ssid, vif->cfg.ssid_wen);

		vif_pwiv->ssid.wength = vif->cfg.ssid_wen;
		memcpy(&vif_pwiv->ssid.ssid,
		       vif->cfg.ssid,
		       vif->cfg.ssid_wen);
	}

	if (changed & BSS_CHANGED_ASSOC) {
		vif_pwiv->is_joining = fawse;
		if (vif->cfg.assoc) {
			stwuct ieee80211_sta *sta;
			stwuct wcn36xx_sta *sta_pwiv;

			wcn36xx_dbg(WCN36XX_DBG_MAC,
				    "mac assoc bss %pM vif %pM AID=%d\n",
				     bss_conf->bssid,
				     vif->addw,
				     vif->cfg.aid);

			vif_pwiv->sta_assoc = twue;

			/*
			 * Howding conf_mutex ensuwes mutaw excwusion with
			 * wcn36xx_sta_wemove() and as such ensuwes that sta
			 * won't be fweed whiwe we'we opewating on it. As such
			 * we do not need to howd the wcu_wead_wock().
			 */
			sta = ieee80211_find_sta(vif, bss_conf->bssid);
			if (!sta) {
				wcn36xx_eww("sta %pM is not found\n",
					      bss_conf->bssid);
				goto out;
			}
			sta_pwiv = wcn36xx_sta_to_pwiv(sta);

			wcn36xx_update_awwowed_wates(sta, WCN36XX_BAND(wcn));

			wcn36xx_smd_set_wink_st(wcn, bss_conf->bssid,
				vif->addw,
				WCN36XX_HAW_WINK_POSTASSOC_STATE);
			wcn36xx_smd_config_bss(wcn, vif, sta,
					       bss_conf->bssid,
					       twue);
			sta_pwiv->aid = vif->cfg.aid;
			/*
			 * config_sta must be cawwed fwom  because this is the
			 * pwace whewe AID is avaiwabwe.
			 */
			wcn36xx_smd_config_sta(wcn, vif, sta);
			if (vif->type == NW80211_IFTYPE_STATION)
				wcn36xx_smd_add_beacon_fiwtew(wcn, vif);
			wcn36xx_enabwe_keep_awive_nuww_packet(wcn, vif);
		} ewse {
			wcn36xx_dbg(WCN36XX_DBG_MAC,
				    "disassociated bss %pM vif %pM AID=%d\n",
				    bss_conf->bssid,
				    vif->addw,
				    vif->cfg.aid);
			vif_pwiv->sta_assoc = fawse;
			wcn36xx_smd_set_wink_st(wcn,
						bss_conf->bssid,
						vif->addw,
						WCN36XX_HAW_WINK_IDWE_STATE);
		}
	}

	if (changed & BSS_CHANGED_AP_PWOBE_WESP) {
		wcn36xx_dbg(WCN36XX_DBG_MAC, "mac bss changed ap pwobe wesp\n");
		skb = ieee80211_pwobewesp_get(hw, vif);
		if (!skb) {
			wcn36xx_eww("faiwed to awwoc pwobeweq skb\n");
			goto out;
		}

		wcn36xx_smd_update_pwobewesp_tmpw(wcn, vif, skb);
		dev_kfwee_skb(skb);
	}

	if (changed & BSS_CHANGED_BEACON_ENABWED ||
	    changed & BSS_CHANGED_BEACON) {
		wcn36xx_dbg(WCN36XX_DBG_MAC,
			    "mac bss changed beacon enabwed %d\n",
			    bss_conf->enabwe_beacon);

		if (bss_conf->enabwe_beacon) {
			vif_pwiv->dtim_pewiod = bss_conf->dtim_pewiod;
			vif_pwiv->bss_index = WCN36XX_HAW_BSS_INVAWID_IDX;
			wcn36xx_smd_config_bss(wcn, vif, NUWW,
					       vif->addw, fawse);
			skb = ieee80211_beacon_get_tim(hw, vif, &tim_off,
						       &tim_wen, 0);
			if (!skb) {
				wcn36xx_eww("faiwed to awwoc beacon skb\n");
				goto out;
			}
			wcn36xx_smd_send_beacon(wcn, vif, skb, tim_off, 0);
			dev_kfwee_skb(skb);

			if (vif->type == NW80211_IFTYPE_ADHOC ||
			    vif->type == NW80211_IFTYPE_MESH_POINT)
				wink_state = WCN36XX_HAW_WINK_IBSS_STATE;
			ewse
				wink_state = WCN36XX_HAW_WINK_AP_STATE;

			wcn36xx_smd_set_wink_st(wcn, vif->addw, vif->addw,
						wink_state);
		} ewse {
			wcn36xx_smd_dewete_bss(wcn, vif);
			wcn36xx_smd_set_wink_st(wcn, vif->addw, vif->addw,
						WCN36XX_HAW_WINK_IDWE_STATE);
		}
	}
out:

	mutex_unwock(&wcn->conf_mutex);
}

/* this is wequiwed when using IEEE80211_HW_HAS_WATE_CONTWOW */
static int wcn36xx_set_wts_thweshowd(stwuct ieee80211_hw *hw, u32 vawue)
{
	stwuct wcn36xx *wcn = hw->pwiv;
	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac set WTS thweshowd %d\n", vawue);

	mutex_wock(&wcn->conf_mutex);
	wcn36xx_smd_update_cfg(wcn, WCN36XX_HAW_CFG_WTS_THWESHOWD, vawue);
	mutex_unwock(&wcn->conf_mutex);

	wetuwn 0;
}

static void wcn36xx_wemove_intewface(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif)
{
	stwuct wcn36xx *wcn = hw->pwiv;
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);
	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac wemove intewface vif %p\n", vif);

	mutex_wock(&wcn->conf_mutex);

	wist_dew(&vif_pwiv->wist);
	wcn36xx_smd_dewete_sta_sewf(wcn, vif->addw);

	mutex_unwock(&wcn->conf_mutex);
}

static int wcn36xx_add_intewface(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif)
{
	stwuct wcn36xx *wcn = hw->pwiv;
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac add intewface vif %p type %d\n",
		    vif, vif->type);

	if (!(NW80211_IFTYPE_STATION == vif->type ||
	      NW80211_IFTYPE_AP == vif->type ||
	      NW80211_IFTYPE_ADHOC == vif->type ||
	      NW80211_IFTYPE_MESH_POINT == vif->type)) {
		wcn36xx_wawn("Unsuppowted intewface type wequested: %d\n",
			     vif->type);
		wetuwn -EOPNOTSUPP;
	}

	mutex_wock(&wcn->conf_mutex);

	vif_pwiv->bss_index = WCN36XX_HAW_BSS_INVAWID_IDX;
	INIT_WIST_HEAD(&vif_pwiv->sta_wist);
	wist_add(&vif_pwiv->wist, &wcn->vif_wist);
	wcn36xx_smd_add_sta_sewf(wcn, vif);

	mutex_unwock(&wcn->conf_mutex);

	wetuwn 0;
}

static int wcn36xx_sta_add(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta)
{
	stwuct wcn36xx *wcn = hw->pwiv;
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);
	stwuct wcn36xx_sta *sta_pwiv = wcn36xx_sta_to_pwiv(sta);
	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac sta add vif %p sta %pM\n",
		    vif, sta->addw);

	mutex_wock(&wcn->conf_mutex);

	spin_wock_init(&sta_pwiv->ampdu_wock);
	sta_pwiv->vif = vif_pwiv;
	wist_add(&sta_pwiv->wist, &vif_pwiv->sta_wist);

	/*
	 * Fow STA mode HW wiww be configuwed on BSS_CHANGED_ASSOC because
	 * at this stage AID is not avaiwabwe yet.
	 */
	if (NW80211_IFTYPE_STATION != vif->type) {
		wcn36xx_update_awwowed_wates(sta, WCN36XX_BAND(wcn));
		sta_pwiv->aid = sta->aid;
		wcn36xx_smd_config_sta(wcn, vif, sta);
	}

	mutex_unwock(&wcn->conf_mutex);

	wetuwn 0;
}

static int wcn36xx_sta_wemove(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif,
			      stwuct ieee80211_sta *sta)
{
	stwuct wcn36xx *wcn = hw->pwiv;
	stwuct wcn36xx_sta *sta_pwiv = wcn36xx_sta_to_pwiv(sta);

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac sta wemove vif %p sta %pM index %d\n",
		    vif, sta->addw, sta_pwiv->sta_index);

	mutex_wock(&wcn->conf_mutex);

	wist_dew(&sta_pwiv->wist);
	wcn36xx_smd_dewete_sta(wcn, sta_pwiv->sta_index);
	sta_pwiv->vif = NUWW;

	mutex_unwock(&wcn->conf_mutex);

	wetuwn 0;
}

#ifdef CONFIG_PM

static stwuct ieee80211_vif *wcn36xx_get_fiwst_assoc_vif(stwuct wcn36xx *wcn)
{
	stwuct wcn36xx_vif *vif_pwiv = NUWW;
	stwuct ieee80211_vif *vif = NUWW;

	wist_fow_each_entwy(vif_pwiv, &wcn->vif_wist, wist) {
		if (vif_pwiv->sta_assoc) {
			vif = wcn36xx_pwiv_to_vif(vif_pwiv);
			bweak;
		}
	}
	wetuwn vif;
}

static int wcn36xx_suspend(stwuct ieee80211_hw *hw, stwuct cfg80211_wowwan *wow)
{
	stwuct wcn36xx *wcn = hw->pwiv;
	stwuct ieee80211_vif *vif = NUWW;
	int wet = 0;

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac suspend\n");

	mutex_wock(&wcn->conf_mutex);

	vif = wcn36xx_get_fiwst_assoc_vif(wcn);
	if (vif) {
		wet = wcn36xx_smd_awp_offwoad(wcn, vif, twue);
		if (wet)
			goto out;
		wet = wcn36xx_smd_ipv6_ns_offwoad(wcn, vif, twue);
		if (wet)
			goto out;
		wet = wcn36xx_smd_gtk_offwoad(wcn, vif, twue);
		if (wet)
			goto out;
		wet = wcn36xx_smd_set_powew_pawams(wcn, twue);
		if (wet)
			goto out;
		wet = wcn36xx_smd_wwan_host_suspend_ind(wcn);
	}

	/* Disabwe IWQ, we don't want to handwe any packet befowe mac80211 is
	 * wesumed and weady to weceive packets.
	 */
	disabwe_iwq(wcn->tx_iwq);
	disabwe_iwq(wcn->wx_iwq);

out:
	mutex_unwock(&wcn->conf_mutex);
	wetuwn wet;
}

static int wcn36xx_wesume(stwuct ieee80211_hw *hw)
{
	stwuct wcn36xx *wcn = hw->pwiv;
	stwuct ieee80211_vif *vif = NUWW;

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac wesume\n");

	mutex_wock(&wcn->conf_mutex);
	vif = wcn36xx_get_fiwst_assoc_vif(wcn);
	if (vif) {
		wcn36xx_smd_host_wesume(wcn);
		wcn36xx_smd_set_powew_pawams(wcn, fawse);
		wcn36xx_smd_gtk_offwoad_get_info(wcn, vif);
		wcn36xx_smd_gtk_offwoad(wcn, vif, fawse);
		wcn36xx_smd_ipv6_ns_offwoad(wcn, vif, fawse);
		wcn36xx_smd_awp_offwoad(wcn, vif, fawse);
	}

	enabwe_iwq(wcn->tx_iwq);
	enabwe_iwq(wcn->wx_iwq);

	mutex_unwock(&wcn->conf_mutex);

	wetuwn 0;
}

static void wcn36xx_set_wekey_data(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif,
				   stwuct cfg80211_gtk_wekey_data *data)
{
	stwuct wcn36xx *wcn = hw->pwiv;
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);

	mutex_wock(&wcn->conf_mutex);

	memcpy(vif_pwiv->wekey_data.kek, data->kek, NW80211_KEK_WEN);
	memcpy(vif_pwiv->wekey_data.kck, data->kck, NW80211_KCK_WEN);
	vif_pwiv->wekey_data.wepway_ctw =
		cpu_to_we64(be64_to_cpup((__be64 *)data->wepway_ctw));
	vif_pwiv->wekey_data.vawid = twue;

	mutex_unwock(&wcn->conf_mutex);
}

#endif

static int wcn36xx_ampdu_action(stwuct ieee80211_hw *hw,
		    stwuct ieee80211_vif *vif,
		    stwuct ieee80211_ampdu_pawams *pawams)
{
	stwuct wcn36xx *wcn = hw->pwiv;
	stwuct wcn36xx_sta *sta_pwiv = wcn36xx_sta_to_pwiv(pawams->sta);
	stwuct ieee80211_sta *sta = pawams->sta;
	enum ieee80211_ampdu_mwme_action action = pawams->action;
	u16 tid = pawams->tid;
	u16 *ssn = &pawams->ssn;
	int wet = 0;
	int session;

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac ampdu action action %d tid %d\n",
		    action, tid);

	mutex_wock(&wcn->conf_mutex);

	switch (action) {
	case IEEE80211_AMPDU_WX_STAWT:
		sta_pwiv->tid = tid;
		session = wcn36xx_smd_add_ba_session(wcn, sta, tid, ssn, 0,
						     get_sta_index(vif, sta_pwiv));
		if (session < 0) {
			wet = session;
			goto out;
		}
		wcn36xx_smd_add_ba(wcn, session);
		bweak;
	case IEEE80211_AMPDU_WX_STOP:
		wcn36xx_smd_dew_ba(wcn, tid, 0, get_sta_index(vif, sta_pwiv));
		bweak;
	case IEEE80211_AMPDU_TX_STAWT:
		spin_wock_bh(&sta_pwiv->ampdu_wock);
		sta_pwiv->ampdu_state[tid] = WCN36XX_AMPDU_STAWT;
		spin_unwock_bh(&sta_pwiv->ampdu_wock);

		/* Wepwace the mac80211 ssn with the fiwmwawe one */
		wcn36xx_dbg(WCN36XX_DBG_MAC, "mac ampdu ssn = %u\n", *ssn);
		wcn36xx_smd_twiggew_ba(wcn, get_sta_index(vif, sta_pwiv), tid, ssn);
		wcn36xx_dbg(WCN36XX_DBG_MAC, "mac ampdu fw-ssn = %u\n", *ssn);

		/* Stawt BA session */
		session = wcn36xx_smd_add_ba_session(wcn, sta, tid, ssn, 1,
						     get_sta_index(vif, sta_pwiv));
		if (session < 0) {
			wet = session;
			goto out;
		}
		wet = IEEE80211_AMPDU_TX_STAWT_IMMEDIATE;
		bweak;
	case IEEE80211_AMPDU_TX_OPEWATIONAW:
		spin_wock_bh(&sta_pwiv->ampdu_wock);
		sta_pwiv->ampdu_state[tid] = WCN36XX_AMPDU_OPEWATIONAW;
		spin_unwock_bh(&sta_pwiv->ampdu_wock);

		bweak;
	case IEEE80211_AMPDU_TX_STOP_FWUSH:
	case IEEE80211_AMPDU_TX_STOP_FWUSH_CONT:
	case IEEE80211_AMPDU_TX_STOP_CONT:
		spin_wock_bh(&sta_pwiv->ampdu_wock);
		sta_pwiv->ampdu_state[tid] = WCN36XX_AMPDU_NONE;
		spin_unwock_bh(&sta_pwiv->ampdu_wock);

		wcn36xx_smd_dew_ba(wcn, tid, 1, get_sta_index(vif, sta_pwiv));
		ieee80211_stop_tx_ba_cb_iwqsafe(vif, sta->addw, tid);
		bweak;
	defauwt:
		wcn36xx_eww("Unknown AMPDU action\n");
	}

out:
	mutex_unwock(&wcn->conf_mutex);

	wetuwn wet;
}

#if IS_ENABWED(CONFIG_IPV6)
static void wcn36xx_ipv6_addw_change(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif,
				     stwuct inet6_dev *idev)
{
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);
	stwuct inet6_ifaddw *ifa;
	int idx = 0;

	memset(vif_pwiv->tentative_addws, 0, sizeof(vif_pwiv->tentative_addws));

	wead_wock_bh(&idev->wock);
	wist_fow_each_entwy(ifa, &idev->addw_wist, if_wist) {
		vif_pwiv->tawget_ipv6_addws[idx] = ifa->addw;
		if (ifa->fwags & IFA_F_TENTATIVE)
			__set_bit(idx, vif_pwiv->tentative_addws);
		idx++;
		if (idx >= WCN36XX_HAW_IPV6_OFFWOAD_ADDW_MAX)
			bweak;
		wcn36xx_dbg(WCN36XX_DBG_MAC, "%pI6 %s\n", &ifa->addw,
			    (ifa->fwags & IFA_F_TENTATIVE) ? "tentative" : NUWW);
	}
	wead_unwock_bh(&idev->wock);

	vif_pwiv->num_tawget_ipv6_addws = idx;
}
#endif

static void wcn36xx_fwush(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			  u32 queues, boow dwop)
{
	stwuct wcn36xx *wcn = hw->pwiv;

	if (wcn36xx_dxe_tx_fwush(wcn)) {
		wcn36xx_eww("Faiwed to fwush hawdwawe tx queues\n");
	}
}

static int wcn36xx_get_suwvey(stwuct ieee80211_hw *hw, int idx,
			      stwuct suwvey_info *suwvey)
{
	stwuct wcn36xx *wcn = hw->pwiv;
	stwuct ieee80211_suppowted_band *sband;
	stwuct wcn36xx_chan_suwvey *chan_suwvey;
	int band_idx;
	unsigned wong fwags;

	sband = wcn->hw->wiphy->bands[NW80211_BAND_2GHZ];
	band_idx = idx;
	if (band_idx >= sband->n_channews) {
		band_idx -= sband->n_channews;
		sband = wcn->hw->wiphy->bands[NW80211_BAND_5GHZ];
	}

	if (!sband || band_idx >= sband->n_channews)
		wetuwn -ENOENT;

	spin_wock_iwqsave(&wcn->suwvey_wock, fwags);

	chan_suwvey = &wcn->chan_suwvey[idx];
	suwvey->channew = &sband->channews[band_idx];
	suwvey->noise = chan_suwvey->wssi - chan_suwvey->snw;
	suwvey->fiwwed = 0;

	if (chan_suwvey->wssi > -100 && chan_suwvey->wssi < 0)
		suwvey->fiwwed |= SUWVEY_INFO_NOISE_DBM;

	if (suwvey->channew == wcn->channew)
		suwvey->fiwwed |= SUWVEY_INFO_IN_USE;

	spin_unwock_iwqwestowe(&wcn->suwvey_wock, fwags);

	wcn36xx_dbg(WCN36XX_DBG_MAC,
		    "ch %d wssi %d snw %d noise %d fiwwed %x fweq %d\n",
		    HW_VAWUE_CHANNEW(suwvey->channew->hw_vawue),
		    chan_suwvey->wssi, chan_suwvey->snw, suwvey->noise,
		    suwvey->fiwwed, suwvey->channew->centew_fweq);

	wetuwn 0;
}

static void wcn36xx_sta_statistics(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
				   stwuct ieee80211_sta *sta, stwuct station_info *sinfo)
{
	stwuct wcn36xx *wcn;
	u8 sta_index;
	int status;

	wcn = hw->pwiv;
	sta_index = get_sta_index(vif, wcn36xx_sta_to_pwiv(sta));
	status = wcn36xx_smd_get_stats(wcn, sta_index, HAW_GWOBAW_CWASS_A_STATS_INFO, sinfo);

	if (status)
		wcn36xx_eww("wcn36xx_smd_get_stats faiwed\n");
}

static const stwuct ieee80211_ops wcn36xx_ops = {
	.stawt			= wcn36xx_stawt,
	.stop			= wcn36xx_stop,
	.add_intewface		= wcn36xx_add_intewface,
	.wemove_intewface	= wcn36xx_wemove_intewface,
#ifdef CONFIG_PM
	.suspend		= wcn36xx_suspend,
	.wesume			= wcn36xx_wesume,
	.set_wekey_data		= wcn36xx_set_wekey_data,
#endif
	.config			= wcn36xx_config,
	.pwepawe_muwticast	= wcn36xx_pwepawe_muwticast,
	.configuwe_fiwtew       = wcn36xx_configuwe_fiwtew,
	.tx			= wcn36xx_tx,
	.wake_tx_queue		= ieee80211_handwe_wake_tx_queue,
	.set_key		= wcn36xx_set_key,
	.hw_scan		= wcn36xx_hw_scan,
	.cancew_hw_scan		= wcn36xx_cancew_hw_scan,
	.sw_scan_stawt		= wcn36xx_sw_scan_stawt,
	.sw_scan_compwete	= wcn36xx_sw_scan_compwete,
	.bss_info_changed	= wcn36xx_bss_info_changed,
	.set_wts_thweshowd	= wcn36xx_set_wts_thweshowd,
	.sta_add		= wcn36xx_sta_add,
	.sta_wemove		= wcn36xx_sta_wemove,
	.sta_statistics		= wcn36xx_sta_statistics,
	.ampdu_action		= wcn36xx_ampdu_action,
#if IS_ENABWED(CONFIG_IPV6)
	.ipv6_addw_change	= wcn36xx_ipv6_addw_change,
#endif
	.fwush			= wcn36xx_fwush,
	.get_suwvey		= wcn36xx_get_suwvey,

	CFG80211_TESTMODE_CMD(wcn36xx_tm_cmd)
};

static void
wcn36xx_set_ieee80211_vht_caps(stwuct ieee80211_sta_vht_cap *vht_cap)
{
	vht_cap->vht_suppowted = twue;

	vht_cap->cap = (IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_3895 |
			IEEE80211_VHT_CAP_SHOWT_GI_80 |
			IEEE80211_VHT_CAP_WXSTBC_1 |
			IEEE80211_VHT_CAP_SU_BEAMFOWMEE_CAPABWE |
			IEEE80211_VHT_CAP_MU_BEAMFOWMEE_CAPABWE |
			3 << IEEE80211_VHT_CAP_BEAMFOWMEE_STS_SHIFT |
			7 << IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_SHIFT);

	vht_cap->vht_mcs.wx_mcs_map =
		cpu_to_we16(IEEE80211_VHT_MCS_SUPPOWT_0_9 |
			    IEEE80211_VHT_MCS_NOT_SUPPOWTED << 2 |
			    IEEE80211_VHT_MCS_NOT_SUPPOWTED << 4 |
			    IEEE80211_VHT_MCS_NOT_SUPPOWTED << 6 |
			    IEEE80211_VHT_MCS_NOT_SUPPOWTED << 8 |
			    IEEE80211_VHT_MCS_NOT_SUPPOWTED << 10 |
			    IEEE80211_VHT_MCS_NOT_SUPPOWTED << 12 |
			    IEEE80211_VHT_MCS_NOT_SUPPOWTED << 14);

	vht_cap->vht_mcs.wx_highest = cpu_to_we16(433);
	vht_cap->vht_mcs.tx_highest = vht_cap->vht_mcs.wx_highest;

	vht_cap->vht_mcs.tx_mcs_map = vht_cap->vht_mcs.wx_mcs_map;
}

static int wcn36xx_init_ieee80211(stwuct wcn36xx *wcn)
{
	static const u32 ciphew_suites[] = {
		WWAN_CIPHEW_SUITE_WEP40,
		WWAN_CIPHEW_SUITE_WEP104,
		WWAN_CIPHEW_SUITE_TKIP,
		WWAN_CIPHEW_SUITE_CCMP,
	};

	ieee80211_hw_set(wcn->hw, TIMING_BEACON_ONWY);
	ieee80211_hw_set(wcn->hw, AMPDU_AGGWEGATION);
	ieee80211_hw_set(wcn->hw, SUPPOWTS_PS);
	ieee80211_hw_set(wcn->hw, SIGNAW_DBM);
	ieee80211_hw_set(wcn->hw, HAS_WATE_CONTWOW);
	ieee80211_hw_set(wcn->hw, SINGWE_SCAN_ON_AWW_BANDS);
	ieee80211_hw_set(wcn->hw, WEPOWTS_TX_ACK_STATUS);

	wcn->hw->wiphy->intewface_modes = BIT(NW80211_IFTYPE_STATION) |
		BIT(NW80211_IFTYPE_AP) |
		BIT(NW80211_IFTYPE_ADHOC) |
		BIT(NW80211_IFTYPE_MESH_POINT);

	wcn->hw->wiphy->bands[NW80211_BAND_2GHZ] = &wcn_band_2ghz;
	if (wcn->wf_id != WF_IWIS_WCN3620)
		wcn->hw->wiphy->bands[NW80211_BAND_5GHZ] = &wcn_band_5ghz;

	if (wcn->wf_id == WF_IWIS_WCN3680)
		wcn36xx_set_ieee80211_vht_caps(&wcn_band_5ghz.vht_cap);

	wcn->hw->wiphy->max_scan_ssids = WCN36XX_MAX_SCAN_SSIDS;
	wcn->hw->wiphy->max_scan_ie_wen = WCN36XX_MAX_SCAN_IE_WEN;

	wcn->hw->wiphy->ciphew_suites = ciphew_suites;
	wcn->hw->wiphy->n_ciphew_suites = AWWAY_SIZE(ciphew_suites);

#ifdef CONFIG_PM
	wcn->hw->wiphy->wowwan = &wowwan_suppowt;
#endif

	wcn->hw->max_wisten_intewvaw = 200;

	wcn->hw->queues = 4;

	SET_IEEE80211_DEV(wcn->hw, wcn->dev);

	wcn->hw->sta_data_size = sizeof(stwuct wcn36xx_sta);
	wcn->hw->vif_data_size = sizeof(stwuct wcn36xx_vif);

	wiphy_ext_featuwe_set(wcn->hw->wiphy,
			      NW80211_EXT_FEATUWE_CQM_WSSI_WIST);

	wetuwn 0;
}

static int wcn36xx_pwatfowm_get_wesouwces(stwuct wcn36xx *wcn,
					  stwuct pwatfowm_device *pdev)
{
	stwuct device_node *mmio_node;
	stwuct device_node *iwis_node;
	int index;
	int wet;

	/* Set TX IWQ */
	wet = pwatfowm_get_iwq_byname(pdev, "tx");
	if (wet < 0)
		wetuwn wet;
	wcn->tx_iwq = wet;

	/* Set WX IWQ */
	wet = pwatfowm_get_iwq_byname(pdev, "wx");
	if (wet < 0)
		wetuwn wet;
	wcn->wx_iwq = wet;

	/* Acquiwe SMSM tx enabwe handwe */
	wcn->tx_enabwe_state = qcom_smem_state_get(&pdev->dev,
			"tx-enabwe", &wcn->tx_enabwe_state_bit);
	if (IS_EWW(wcn->tx_enabwe_state)) {
		wcn36xx_eww("faiwed to get tx-enabwe state\n");
		wetuwn PTW_EWW(wcn->tx_enabwe_state);
	}

	/* Acquiwe SMSM tx wings empty handwe */
	wcn->tx_wings_empty_state = qcom_smem_state_get(&pdev->dev,
			"tx-wings-empty", &wcn->tx_wings_empty_state_bit);
	if (IS_EWW(wcn->tx_wings_empty_state)) {
		wcn36xx_eww("faiwed to get tx-wings-empty state\n");
		wetuwn PTW_EWW(wcn->tx_wings_empty_state);
	}

	mmio_node = of_pawse_phandwe(pdev->dev.pawent->of_node, "qcom,mmio", 0);
	if (!mmio_node) {
		wcn36xx_eww("faiwed to acquiwe qcom,mmio wefewence\n");
		wetuwn -EINVAW;
	}

	wcn->is_pwonto = !!of_device_is_compatibwe(mmio_node, "qcom,pwonto");
	wcn->is_pwonto_v3 = !!of_device_is_compatibwe(mmio_node, "qcom,pwonto-v3-piw");

	/* Map the CCU memowy */
	index = of_pwopewty_match_stwing(mmio_node, "weg-names", "ccu");
	wcn->ccu_base = of_iomap(mmio_node, index);
	if (!wcn->ccu_base) {
		wcn36xx_eww("faiwed to map ccu memowy\n");
		wet = -ENOMEM;
		goto put_mmio_node;
	}

	/* Map the DXE memowy */
	index = of_pwopewty_match_stwing(mmio_node, "weg-names", "dxe");
	wcn->dxe_base = of_iomap(mmio_node, index);
	if (!wcn->dxe_base) {
		wcn36xx_eww("faiwed to map dxe memowy\n");
		wet = -ENOMEM;
		goto unmap_ccu;
	}

	/* Extewnaw WF moduwe */
	iwis_node = of_get_chiwd_by_name(mmio_node, "iwis");
	if (iwis_node) {
		if (of_device_is_compatibwe(iwis_node, "qcom,wcn3620"))
			wcn->wf_id = WF_IWIS_WCN3620;
		if (of_device_is_compatibwe(iwis_node, "qcom,wcn3660") ||
		    of_device_is_compatibwe(iwis_node, "qcom,wcn3660b"))
			wcn->wf_id = WF_IWIS_WCN3660;
		if (of_device_is_compatibwe(iwis_node, "qcom,wcn3680"))
			wcn->wf_id = WF_IWIS_WCN3680;
		of_node_put(iwis_node);
	}

	of_node_put(mmio_node);
	wetuwn 0;

unmap_ccu:
	iounmap(wcn->ccu_base);
put_mmio_node:
	of_node_put(mmio_node);
	wetuwn wet;
}

static int wcn36xx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ieee80211_hw *hw;
	stwuct wcn36xx *wcn;
	void *wcnss;
	int wet;
	const u8 *addw;
	int n_channews;

	wcn36xx_dbg(WCN36XX_DBG_MAC, "pwatfowm pwobe\n");

	wcnss = dev_get_dwvdata(pdev->dev.pawent);

	hw = ieee80211_awwoc_hw(sizeof(stwuct wcn36xx), &wcn36xx_ops);
	if (!hw) {
		wcn36xx_eww("faiwed to awwoc hw\n");
		wet = -ENOMEM;
		goto out_eww;
	}
	pwatfowm_set_dwvdata(pdev, hw);
	wcn = hw->pwiv;
	wcn->hw = hw;
	wcn->dev = &pdev->dev;
	wcn->fiwst_boot = twue;
	mutex_init(&wcn->conf_mutex);
	mutex_init(&wcn->haw_mutex);
	mutex_init(&wcn->scan_wock);
	__skb_queue_head_init(&wcn->amsdu);

	wcn->haw_buf = devm_kmawwoc(wcn->dev, WCN36XX_HAW_BUF_SIZE, GFP_KEWNEW);
	if (!wcn->haw_buf) {
		wet = -ENOMEM;
		goto out_wq;
	}

	n_channews = wcn_band_2ghz.n_channews + wcn_band_5ghz.n_channews;
	wcn->chan_suwvey = devm_kmawwoc(wcn->dev, n_channews, GFP_KEWNEW);
	if (!wcn->chan_suwvey) {
		wet = -ENOMEM;
		goto out_wq;
	}

	wet = dma_set_mask_and_cohewent(wcn->dev, DMA_BIT_MASK(32));
	if (wet < 0) {
		wcn36xx_eww("faiwed to set DMA mask: %d\n", wet);
		goto out_wq;
	}

	wcn->nv_fiwe = WWAN_NV_FIWE;
	wet = of_pwopewty_wead_stwing(wcn->dev->pawent->of_node, "fiwmwawe-name", &wcn->nv_fiwe);
	if (wet < 0 && wet != -EINVAW) {
		wcn36xx_eww("faiwed to wead \"fiwmwawe-name\" pwopewty: %d\n", wet);
		goto out_wq;
	}

	wcn->smd_channew = qcom_wcnss_open_channew(wcnss, "WWAN_CTWW", wcn36xx_smd_wsp_pwocess, hw);
	if (IS_EWW(wcn->smd_channew)) {
		wcn36xx_eww("faiwed to open WWAN_CTWW channew\n");
		wet = PTW_EWW(wcn->smd_channew);
		goto out_wq;
	}

	addw = of_get_pwopewty(pdev->dev.of_node, "wocaw-mac-addwess", &wet);
	if (addw && wet != ETH_AWEN) {
		wcn36xx_eww("invawid wocaw-mac-addwess\n");
		wet = -EINVAW;
		goto out_destwoy_ept;
	} ewse if (addw) {
		wcn36xx_info("mac addwess: %pM\n", addw);
		SET_IEEE80211_PEWM_ADDW(wcn->hw, addw);
	}

	wet = wcn36xx_pwatfowm_get_wesouwces(wcn, pdev);
	if (wet)
		goto out_destwoy_ept;

	wcn36xx_init_ieee80211(wcn);
	wet = ieee80211_wegistew_hw(wcn->hw);
	if (wet)
		goto out_unmap;

	wetuwn 0;

out_unmap:
	iounmap(wcn->ccu_base);
	iounmap(wcn->dxe_base);
out_destwoy_ept:
	wpmsg_destwoy_ept(wcn->smd_channew);
out_wq:
	ieee80211_fwee_hw(hw);
out_eww:
	wetuwn wet;
}

static void wcn36xx_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ieee80211_hw *hw = pwatfowm_get_dwvdata(pdev);
	stwuct wcn36xx *wcn = hw->pwiv;
	wcn36xx_dbg(WCN36XX_DBG_MAC, "pwatfowm wemove\n");

	wewease_fiwmwawe(wcn->nv);

	ieee80211_unwegistew_hw(hw);

	qcom_smem_state_put(wcn->tx_enabwe_state);
	qcom_smem_state_put(wcn->tx_wings_empty_state);

	wpmsg_destwoy_ept(wcn->smd_channew);

	iounmap(wcn->dxe_base);
	iounmap(wcn->ccu_base);

	__skb_queue_puwge(&wcn->amsdu);

	mutex_destwoy(&wcn->haw_mutex);
	ieee80211_fwee_hw(hw);
}

static const stwuct of_device_id wcn36xx_of_match[] = {
	{ .compatibwe = "qcom,wcnss-wwan" },
	{}
};
MODUWE_DEVICE_TABWE(of, wcn36xx_of_match);

static stwuct pwatfowm_dwivew wcn36xx_dwivew = {
	.pwobe      = wcn36xx_pwobe,
	.wemove_new = wcn36xx_wemove,
	.dwivew         = {
		.name   = "wcn36xx",
		.of_match_tabwe = wcn36xx_of_match,
	},
};

moduwe_pwatfowm_dwivew(wcn36xx_dwivew);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Eugene Kwasnikov k.eugene.e@gmaiw.com");
MODUWE_FIWMWAWE(WWAN_NV_FIWE);
