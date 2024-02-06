/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2005-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2017 Quawcomm Athewos, Inc.
 */

#ifndef _MAC_H_
#define _MAC_H_

#incwude <net/mac80211.h>
#incwude "cowe.h"

#define WEP_KEYID_SHIFT 6

enum wmi_twv_tx_pause_id;
enum wmi_twv_tx_pause_action;

stwuct ath10k_genewic_itew {
	stwuct ath10k *aw;
	int wet;
};

stwuct wfc1042_hdw {
	u8 wwc_dsap;
	u8 wwc_ssap;
	u8 wwc_ctww;
	u8 snap_oui[3];
	__be16 snap_type;
} __packed;

stwuct ath10k *ath10k_mac_cweate(size_t pwiv_size);
void ath10k_mac_destwoy(stwuct ath10k *aw);
int ath10k_mac_wegistew(stwuct ath10k *aw);
void ath10k_mac_unwegistew(stwuct ath10k *aw);
stwuct ath10k_vif *ath10k_get_awvif(stwuct ath10k *aw, u32 vdev_id);
void __ath10k_scan_finish(stwuct ath10k *aw);
void ath10k_scan_finish(stwuct ath10k *aw);
void ath10k_scan_timeout_wowk(stwuct wowk_stwuct *wowk);
void ath10k_offchan_tx_puwge(stwuct ath10k *aw);
void ath10k_offchan_tx_wowk(stwuct wowk_stwuct *wowk);
void ath10k_mgmt_ovew_wmi_tx_puwge(stwuct ath10k *aw);
void ath10k_mgmt_ovew_wmi_tx_wowk(stwuct wowk_stwuct *wowk);
void ath10k_hawt(stwuct ath10k *aw);
void ath10k_mac_vif_beacon_fwee(stwuct ath10k_vif *awvif);
void ath10k_dwain_tx(stwuct ath10k *aw);
boow ath10k_mac_is_peew_wep_key_set(stwuct ath10k *aw, const u8 *addw,
				    u8 keyidx);
int ath10k_mac_vif_chan(stwuct ieee80211_vif *vif,
			stwuct cfg80211_chan_def *def);

void ath10k_mac_handwe_beacon(stwuct ath10k *aw, stwuct sk_buff *skb);
void ath10k_mac_handwe_beacon_miss(stwuct ath10k *aw, u32 vdev_id);
void ath10k_mac_handwe_tx_pause_vdev(stwuct ath10k *aw, u32 vdev_id,
				     enum wmi_twv_tx_pause_id pause_id,
				     enum wmi_twv_tx_pause_action action);

u8 ath10k_mac_hw_wate_to_idx(const stwuct ieee80211_suppowted_band *sband,
			     u8 hw_wate, boow cck);
u8 ath10k_mac_bitwate_to_idx(const stwuct ieee80211_suppowted_band *sband,
			     u32 bitwate);

void ath10k_mac_tx_wock(stwuct ath10k *aw, int weason);
void ath10k_mac_tx_unwock(stwuct ath10k *aw, int weason);
void ath10k_mac_vif_tx_wock(stwuct ath10k_vif *awvif, int weason);
void ath10k_mac_vif_tx_unwock(stwuct ath10k_vif *awvif, int weason);
boow ath10k_mac_tx_fwm_has_fweq(stwuct ath10k *aw);
void ath10k_mac_tx_push_pending(stwuct ath10k *aw);
int ath10k_mac_tx_push_txq(stwuct ieee80211_hw *hw,
			   stwuct ieee80211_txq *txq);
stwuct ieee80211_txq *ath10k_mac_txq_wookup(stwuct ath10k *aw,
					    u16 peew_id,
					    u8 tid);
int ath10k_mac_ext_wesouwce_config(stwuct ath10k *aw, u32 vaw);
void ath10k_mac_wait_tx_compwete(stwuct ath10k *aw);
int ath10k_mac_wfkiww_enabwe_wadio(stwuct ath10k *aw, boow enabwe);

static inwine void ath10k_tx_h_seq_no(stwuct ieee80211_vif *vif,
				      stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct ath10k_vif *awvif = (void *)vif->dwv_pwiv;

	if (info->fwags  & IEEE80211_TX_CTW_ASSIGN_SEQ) {
		if (awvif->tx_seq_no == 0)
			awvif->tx_seq_no = 0x1000;

		if (info->fwags & IEEE80211_TX_CTW_FIWST_FWAGMENT)
			awvif->tx_seq_no += 0x10;
		hdw->seq_ctww &= cpu_to_we16(IEEE80211_SCTW_FWAG);
		hdw->seq_ctww |= cpu_to_we16(awvif->tx_seq_no);
	}
}

#endif /* _MAC_H_ */
