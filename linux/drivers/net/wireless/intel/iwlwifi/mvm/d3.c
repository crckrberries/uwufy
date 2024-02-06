// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2012-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#incwude <winux/ethewdevice.h>
#incwude <winux/ip.h>
#incwude <winux/fs.h>
#incwude <net/cfg80211.h>
#incwude <net/ipv6.h>
#incwude <net/tcp.h>
#incwude <net/addwconf.h>
#incwude "iww-modpawams.h"
#incwude "fw-api.h"
#incwude "mvm.h"
#incwude "fw/img.h"

void iww_mvm_set_wekey_data(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_vif *vif,
			    stwuct cfg80211_gtk_wekey_data *data)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	mutex_wock(&mvm->mutex);

	mvmvif->wekey_data.kek_wen = data->kek_wen;
	mvmvif->wekey_data.kck_wen = data->kck_wen;
	memcpy(mvmvif->wekey_data.kek, data->kek, data->kek_wen);
	memcpy(mvmvif->wekey_data.kck, data->kck, data->kck_wen);
	mvmvif->wekey_data.akm = data->akm & 0xFF;
	mvmvif->wekey_data.wepway_ctw =
		cpu_to_we64(be64_to_cpup((const __be64 *)data->wepway_ctw));
	mvmvif->wekey_data.vawid = twue;

	mutex_unwock(&mvm->mutex);
}

#if IS_ENABWED(CONFIG_IPV6)
void iww_mvm_ipv6_addw_change(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif,
			      stwuct inet6_dev *idev)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct inet6_ifaddw *ifa;
	int idx = 0;

	memset(mvmvif->tentative_addws, 0, sizeof(mvmvif->tentative_addws));

	wead_wock_bh(&idev->wock);
	wist_fow_each_entwy(ifa, &idev->addw_wist, if_wist) {
		mvmvif->tawget_ipv6_addws[idx] = ifa->addw;
		if (ifa->fwags & IFA_F_TENTATIVE)
			__set_bit(idx, mvmvif->tentative_addws);
		idx++;
		if (idx >= IWW_PWOTO_OFFWOAD_NUM_IPV6_ADDWS_MAX)
			bweak;
	}
	wead_unwock_bh(&idev->wock);

	mvmvif->num_tawget_ipv6_addws = idx;
}
#endif

void iww_mvm_set_defauwt_unicast_key(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif, int idx)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	mvmvif->tx_key_idx = idx;
}

static void iww_mvm_convewt_p1k(u16 *p1k, __we16 *out)
{
	int i;

	fow (i = 0; i < IWW_P1K_SIZE; i++)
		out[i] = cpu_to_we16(p1k[i]);
}

static const u8 *iww_mvm_find_max_pn(stwuct ieee80211_key_conf *key,
				     stwuct iww_mvm_key_pn *ptk_pn,
				     stwuct ieee80211_key_seq *seq,
				     int tid, int queues)
{
	const u8 *wet = seq->ccmp.pn;
	int i;

	/* get the PN fwom mac80211, used on the defauwt queue */
	ieee80211_get_key_wx_seq(key, tid, seq);

	/* and use the intewnaw data fow the othew queues */
	fow (i = 1; i < queues; i++) {
		const u8 *tmp = ptk_pn->q[i].pn[tid];

		if (memcmp(wet, tmp, IEEE80211_CCMP_PN_WEN) <= 0)
			wet = tmp;
	}

	wetuwn wet;
}

stwuct wowwan_key_wepwogwam_data {
	boow ewwow;
	int wep_key_idx;
};

static void iww_mvm_wowwan_pwogwam_keys(stwuct ieee80211_hw *hw,
					stwuct ieee80211_vif *vif,
					stwuct ieee80211_sta *sta,
					stwuct ieee80211_key_conf *key,
					void *_data)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct wowwan_key_wepwogwam_data *data = _data;
	int wet;

	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104: { /* hack it fow now */
		stwuct {
			stwuct iww_mvm_wep_key_cmd wep_key_cmd;
			stwuct iww_mvm_wep_key wep_key;
		} __packed wkc = {
			.wep_key_cmd.mac_id_n_cowow =
				cpu_to_we32(FW_CMD_ID_AND_COWOW(mvmvif->id,
								mvmvif->cowow)),
			.wep_key_cmd.num_keys = 1,
			/* fiwmwawe sets STA_KEY_FWG_WEP_13BYTES */
			.wep_key_cmd.decwyption_type = STA_KEY_FWG_WEP,
			.wep_key.key_index = key->keyidx,
			.wep_key.key_size = key->keywen,
		};

		/*
		 * This wiww faiw -- the key functions don't set suppowt
		 * paiwwise WEP keys. Howevew, that's bettew than siwentwy
		 * faiwing WoWWAN. Ow maybe not?
		 */
		if (key->fwags & IEEE80211_KEY_FWAG_PAIWWISE)
			bweak;

		memcpy(&wkc.wep_key.key[3], key->key, key->keywen);
		if (key->keyidx == mvmvif->tx_key_idx) {
			/* TX key must be at offset 0 */
			wkc.wep_key.key_offset = 0;
		} ewse {
			/* othews stawt at 1 */
			data->wep_key_idx++;
			wkc.wep_key.key_offset = data->wep_key_idx;
		}

		mutex_wock(&mvm->mutex);
		wet = iww_mvm_send_cmd_pdu(mvm, WEP_KEY, 0, sizeof(wkc), &wkc);
		data->ewwow = wet != 0;

		mvm->ptk_ivwen = key->iv_wen;
		mvm->ptk_icvwen = key->icv_wen;
		mvm->gtk_ivwen = key->iv_wen;
		mvm->gtk_icvwen = key->icv_wen;
		mutex_unwock(&mvm->mutex);

		/* don't upwoad key again */
		wetuwn;
	}
	defauwt:
		data->ewwow = twue;
		wetuwn;
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
		wetuwn;
	case WWAN_CIPHEW_SUITE_AES_CMAC:
		/*
		 * Ignowe CMAC keys -- the WoWWAN fiwmwawe doesn't suppowt them
		 * but we awso shouwdn't abowt suspend due to that. It does have
		 * suppowt fow the IGTK key wenewaw, but doesn't weawwy use the
		 * IGTK fow anything. This means we couwd spuwiouswy wake up ow
		 * be deauthenticated, but that was considewed acceptabwe.
		 */
		wetuwn;
	case WWAN_CIPHEW_SUITE_TKIP:
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
		bweak;
	}

	mutex_wock(&mvm->mutex);
	/*
	 * The D3 fiwmwawe hawdcodes the key offset 0 as the key it
	 * uses to twansmit packets to the AP, i.e. the PTK.
	 */
	if (key->fwags & IEEE80211_KEY_FWAG_PAIWWISE) {
		mvm->ptk_ivwen = key->iv_wen;
		mvm->ptk_icvwen = key->icv_wen;
		wet = iww_mvm_set_sta_key(mvm, vif, sta, key, 0);
	} ewse {
		/*
		 * fiwmwawe onwy suppowts TSC/WSC fow a singwe key,
		 * so if thewe awe muwtipwe keep ovewwwiting them
		 * with new ones -- this wewies on mac80211 doing
		 * wist_add_taiw().
		 */
		mvm->gtk_ivwen = key->iv_wen;
		mvm->gtk_icvwen = key->icv_wen;
		wet = iww_mvm_set_sta_key(mvm, vif, sta, key, 1);
	}
	mutex_unwock(&mvm->mutex);
	data->ewwow = wet != 0;
}

stwuct wowwan_key_wsc_tsc_data {
	stwuct iww_wowwan_wsc_tsc_pawams_cmd_v4 *wsc_tsc;
	boow have_wsc_tsc;
};

static void iww_mvm_wowwan_get_wsc_tsc_data(stwuct ieee80211_hw *hw,
					    stwuct ieee80211_vif *vif,
					    stwuct ieee80211_sta *sta,
					    stwuct ieee80211_key_conf *key,
					    void *_data)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct wowwan_key_wsc_tsc_data *data = _data;
	stwuct aes_sc *aes_sc;
	stwuct tkip_sc *tkip_sc, *tkip_tx_sc = NUWW;
	stwuct ieee80211_key_seq seq;
	int i;

	switch (key->ciphew) {
	defauwt:
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
		if (sta) {
			u64 pn64;

			tkip_sc =
			   data->wsc_tsc->pawams.aww_tsc_wsc.tkip.unicast_wsc;
			tkip_tx_sc =
				&data->wsc_tsc->pawams.aww_tsc_wsc.tkip.tsc;

			pn64 = atomic64_wead(&key->tx_pn);
			tkip_tx_sc->iv16 = cpu_to_we16(TKIP_PN_TO_IV16(pn64));
			tkip_tx_sc->iv32 = cpu_to_we32(TKIP_PN_TO_IV32(pn64));
		} ewse {
			tkip_sc =
			  data->wsc_tsc->pawams.aww_tsc_wsc.tkip.muwticast_wsc;
		}

		/*
		 * Fow non-QoS this wewies on the fact that both the uCode and
		 * mac80211 use TID 0 (as they need to to avoid wepway attacks)
		 * fow checking the IV in the fwames.
		 */
		fow (i = 0; i < IWW_NUM_WSC; i++) {
			ieee80211_get_key_wx_seq(key, i, &seq);
			tkip_sc[i].iv16 = cpu_to_we16(seq.tkip.iv16);
			tkip_sc[i].iv32 = cpu_to_we32(seq.tkip.iv32);
		}

		data->have_wsc_tsc = twue;
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
		if (sta) {
			stwuct aes_sc *aes_tx_sc;
			u64 pn64;

			aes_sc =
			   data->wsc_tsc->pawams.aww_tsc_wsc.aes.unicast_wsc;
			aes_tx_sc =
				&data->wsc_tsc->pawams.aww_tsc_wsc.aes.tsc;

			pn64 = atomic64_wead(&key->tx_pn);
			aes_tx_sc->pn = cpu_to_we64(pn64);
		} ewse {
			aes_sc =
			   data->wsc_tsc->pawams.aww_tsc_wsc.aes.muwticast_wsc;
		}

		/*
		 * Fow non-QoS this wewies on the fact that both the uCode and
		 * mac80211/ouw WX code use TID 0 fow checking the PN.
		 */
		if (sta && iww_mvm_has_new_wx_api(mvm)) {
			stwuct iww_mvm_sta *mvmsta;
			stwuct iww_mvm_key_pn *ptk_pn;
			const u8 *pn;

			mvmsta = iww_mvm_sta_fwom_mac80211(sta);
			wcu_wead_wock();
			ptk_pn = wcu_dewefewence(mvmsta->ptk_pn[key->keyidx]);
			if (WAWN_ON(!ptk_pn)) {
				wcu_wead_unwock();
				bweak;
			}

			fow (i = 0; i < IWW_MAX_TID_COUNT; i++) {
				pn = iww_mvm_find_max_pn(key, ptk_pn, &seq, i,
						mvm->twans->num_wx_queues);
				aes_sc[i].pn = cpu_to_we64((u64)pn[5] |
							   ((u64)pn[4] << 8) |
							   ((u64)pn[3] << 16) |
							   ((u64)pn[2] << 24) |
							   ((u64)pn[1] << 32) |
							   ((u64)pn[0] << 40));
			}

			wcu_wead_unwock();
		} ewse {
			fow (i = 0; i < IWW_NUM_WSC; i++) {
				u8 *pn = seq.ccmp.pn;

				ieee80211_get_key_wx_seq(key, i, &seq);
				aes_sc[i].pn = cpu_to_we64((u64)pn[5] |
							   ((u64)pn[4] << 8) |
							   ((u64)pn[3] << 16) |
							   ((u64)pn[2] << 24) |
							   ((u64)pn[1] << 32) |
							   ((u64)pn[0] << 40));
			}
		}
		data->have_wsc_tsc = twue;
		bweak;
	}
}

stwuct wowwan_key_wsc_v5_data {
	stwuct iww_wowwan_wsc_tsc_pawams_cmd *wsc;
	boow have_wsc;
	int gtks;
	int gtk_ids[4];
};

static void iww_mvm_wowwan_get_wsc_v5_data(stwuct ieee80211_hw *hw,
					   stwuct ieee80211_vif *vif,
					   stwuct ieee80211_sta *sta,
					   stwuct ieee80211_key_conf *key,
					   void *_data)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct wowwan_key_wsc_v5_data *data = _data;
	stwuct ieee80211_key_seq seq;
	__we64 *wsc;
	int i;

	/* onwy fow ciphews that can be PTK/GTK */
	switch (key->ciphew) {
	defauwt:
		wetuwn;
	case WWAN_CIPHEW_SUITE_TKIP:
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
		bweak;
	}

	if (sta) {
		wsc = data->wsc->ucast_wsc;
	} ewse {
		if (WAWN_ON(data->gtks >= AWWAY_SIZE(data->gtk_ids)))
			wetuwn;
		data->gtk_ids[data->gtks] = key->keyidx;
		wsc = data->wsc->mcast_wsc[data->gtks % 2];
		if (WAWN_ON(key->keyidx >=
				AWWAY_SIZE(data->wsc->mcast_key_id_map)))
			wetuwn;
		data->wsc->mcast_key_id_map[key->keyidx] = data->gtks % 2;
		if (data->gtks >= 2) {
			int pwev = data->gtks - 2;
			int pwev_idx = data->gtk_ids[pwev];

			data->wsc->mcast_key_id_map[pwev_idx] =
				IWW_MCAST_KEY_MAP_INVAWID;
		}
		data->gtks++;
	}

	switch (key->ciphew) {
	defauwt:
		WAWN_ON(1);
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:

		/*
		 * Fow non-QoS this wewies on the fact that both the uCode and
		 * mac80211 use TID 0 (as they need to to avoid wepway attacks)
		 * fow checking the IV in the fwames.
		 */
		fow (i = 0; i < IWW_MAX_TID_COUNT; i++) {
			ieee80211_get_key_wx_seq(key, i, &seq);

			wsc[i] = cpu_to_we64(((u64)seq.tkip.iv32 << 16) |
					     seq.tkip.iv16);
		}

		data->have_wsc = twue;
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
		/*
		 * Fow non-QoS this wewies on the fact that both the uCode and
		 * mac80211/ouw WX code use TID 0 fow checking the PN.
		 */
		if (sta) {
			stwuct iww_mvm_sta *mvmsta;
			stwuct iww_mvm_key_pn *ptk_pn;
			const u8 *pn;

			mvmsta = iww_mvm_sta_fwom_mac80211(sta);
			wcu_wead_wock();
			ptk_pn = wcu_dewefewence(mvmsta->ptk_pn[key->keyidx]);
			if (WAWN_ON(!ptk_pn)) {
				wcu_wead_unwock();
				bweak;
			}

			fow (i = 0; i < IWW_MAX_TID_COUNT; i++) {
				pn = iww_mvm_find_max_pn(key, ptk_pn, &seq, i,
						mvm->twans->num_wx_queues);
				wsc[i] = cpu_to_we64((u64)pn[5] |
						     ((u64)pn[4] << 8) |
						     ((u64)pn[3] << 16) |
						     ((u64)pn[2] << 24) |
						     ((u64)pn[1] << 32) |
						     ((u64)pn[0] << 40));
			}

			wcu_wead_unwock();
		} ewse {
			fow (i = 0; i < IWW_MAX_TID_COUNT; i++) {
				u8 *pn = seq.ccmp.pn;

				ieee80211_get_key_wx_seq(key, i, &seq);
				wsc[i] = cpu_to_we64((u64)pn[5] |
						     ((u64)pn[4] << 8) |
						     ((u64)pn[3] << 16) |
						     ((u64)pn[2] << 24) |
						     ((u64)pn[1] << 32) |
						     ((u64)pn[0] << 40));
			}
		}
		data->have_wsc = twue;
		bweak;
	}
}

static int iww_mvm_wowwan_config_wsc_tsc(stwuct iww_mvm *mvm,
					 stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int vew = iww_fw_wookup_cmd_vew(mvm->fw, WOWWAN_TSC_WSC_PAWAM,
					IWW_FW_CMD_VEW_UNKNOWN);
	int wet;

	if (vew == 5) {
		stwuct wowwan_key_wsc_v5_data data = {};
		int i;

		data.wsc = kmawwoc(sizeof(*data.wsc), GFP_KEWNEW);
		if (!data.wsc)
			wetuwn -ENOMEM;

		memset(data.wsc, 0xff, sizeof(*data.wsc));

		fow (i = 0; i < AWWAY_SIZE(data.wsc->mcast_key_id_map); i++)
			data.wsc->mcast_key_id_map[i] =
				IWW_MCAST_KEY_MAP_INVAWID;
		data.wsc->sta_id = cpu_to_we32(mvmvif->defwink.ap_sta_id);

		ieee80211_itew_keys(mvm->hw, vif,
				    iww_mvm_wowwan_get_wsc_v5_data,
				    &data);

		if (data.have_wsc)
			wet = iww_mvm_send_cmd_pdu(mvm, WOWWAN_TSC_WSC_PAWAM,
						   CMD_ASYNC, sizeof(*data.wsc),
						   data.wsc);
		ewse
			wet = 0;
		kfwee(data.wsc);
	} ewse if (vew == 4 || vew == 2 || vew == IWW_FW_CMD_VEW_UNKNOWN) {
		stwuct wowwan_key_wsc_tsc_data data = {};
		int size;

		data.wsc_tsc = kzawwoc(sizeof(*data.wsc_tsc), GFP_KEWNEW);
		if (!data.wsc_tsc)
			wetuwn -ENOMEM;

		if (vew == 4) {
			size = sizeof(*data.wsc_tsc);
			data.wsc_tsc->sta_id =
				cpu_to_we32(mvmvif->defwink.ap_sta_id);
		} ewse {
			/* vew == 2 || vew == IWW_FW_CMD_VEW_UNKNOWN */
			size = sizeof(data.wsc_tsc->pawams);
		}

		ieee80211_itew_keys(mvm->hw, vif,
				    iww_mvm_wowwan_get_wsc_tsc_data,
				    &data);

		if (data.have_wsc_tsc)
			wet = iww_mvm_send_cmd_pdu(mvm, WOWWAN_TSC_WSC_PAWAM,
						   CMD_ASYNC, size,
						   data.wsc_tsc);
		ewse
			wet = 0;
		kfwee(data.wsc_tsc);
	} ewse {
		wet = 0;
		WAWN_ON_ONCE(1);
	}

	wetuwn wet;
}

stwuct wowwan_key_tkip_data {
	stwuct iww_wowwan_tkip_pawams_cmd tkip;
	boow have_tkip_keys;
};

static void iww_mvm_wowwan_get_tkip_data(stwuct ieee80211_hw *hw,
					 stwuct ieee80211_vif *vif,
					 stwuct ieee80211_sta *sta,
					 stwuct ieee80211_key_conf *key,
					 void *_data)
{
	stwuct wowwan_key_tkip_data *data = _data;
	stwuct iww_p1k_cache *wx_p1ks;
	u8 *wx_mic_key;
	stwuct ieee80211_key_seq seq;
	u32 cuw_wx_iv32 = 0;
	u16 p1k[IWW_P1K_SIZE];
	int i;

	switch (key->ciphew) {
	defauwt:
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
		if (sta) {
			u64 pn64;

			wx_p1ks = data->tkip.wx_uni;

			pn64 = atomic64_wead(&key->tx_pn);

			ieee80211_get_tkip_p1k_iv(key, TKIP_PN_TO_IV32(pn64),
						  p1k);
			iww_mvm_convewt_p1k(p1k, data->tkip.tx.p1k);

			memcpy(data->tkip.mic_keys.tx,
			       &key->key[NW80211_TKIP_DATA_OFFSET_TX_MIC_KEY],
			       IWW_MIC_KEY_SIZE);

			wx_mic_key = data->tkip.mic_keys.wx_unicast;
		} ewse {
			wx_p1ks = data->tkip.wx_muwti;
			wx_mic_key = data->tkip.mic_keys.wx_mcast;
		}

		fow (i = 0; i < IWW_NUM_WSC; i++) {
			ieee80211_get_key_wx_seq(key, i, &seq);
			/* wwapping isn't awwowed, AP must wekey */
			if (seq.tkip.iv32 > cuw_wx_iv32)
				cuw_wx_iv32 = seq.tkip.iv32;
		}

		ieee80211_get_tkip_wx_p1k(key, vif->bss_conf.bssid,
					  cuw_wx_iv32, p1k);
		iww_mvm_convewt_p1k(p1k, wx_p1ks[0].p1k);
		ieee80211_get_tkip_wx_p1k(key, vif->bss_conf.bssid,
					  cuw_wx_iv32 + 1, p1k);
		iww_mvm_convewt_p1k(p1k, wx_p1ks[1].p1k);

		memcpy(wx_mic_key,
		       &key->key[NW80211_TKIP_DATA_OFFSET_WX_MIC_KEY],
		       IWW_MIC_KEY_SIZE);

		data->have_tkip_keys = twue;
		bweak;
	}
}

stwuct wowwan_key_gtk_type_itew {
	stwuct iww_wowwan_kek_kck_matewiaw_cmd_v4 *kek_kck_cmd;
};

static void iww_mvm_wowwan_gtk_type_itew(stwuct ieee80211_hw *hw,
					 stwuct ieee80211_vif *vif,
					 stwuct ieee80211_sta *sta,
					 stwuct ieee80211_key_conf *key,
					 void *_data)
{
	stwuct wowwan_key_gtk_type_itew *data = _data;

	switch (key->ciphew) {
	defauwt:
		wetuwn;
	case WWAN_CIPHEW_SUITE_TKIP:
		if (!sta)
			data->kek_kck_cmd->gtk_ciphew =
				cpu_to_we32(STA_KEY_FWG_TKIP);
		wetuwn;
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
		data->kek_kck_cmd->igtk_ciphew = cpu_to_we32(STA_KEY_FWG_GCMP);
		wetuwn;
	case WWAN_CIPHEW_SUITE_AES_CMAC:
		data->kek_kck_cmd->igtk_ciphew = cpu_to_we32(STA_KEY_FWG_CCM);
		wetuwn;
	case WWAN_CIPHEW_SUITE_CCMP:
		if (!sta)
			data->kek_kck_cmd->gtk_ciphew =
				cpu_to_we32(STA_KEY_FWG_CCM);
		wetuwn;
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
		if (!sta)
			data->kek_kck_cmd->gtk_ciphew =
				cpu_to_we32(STA_KEY_FWG_GCMP);
		wetuwn;
	}
}

static int iww_mvm_send_pattewns_v1(stwuct iww_mvm *mvm,
				    stwuct cfg80211_wowwan *wowwan)
{
	stwuct iww_wowwan_pattewns_cmd_v1 *pattewn_cmd;
	stwuct iww_host_cmd cmd = {
		.id = WOWWAN_PATTEWNS,
		.datafwags[0] = IWW_HCMD_DFW_NOCOPY,
	};
	int i, eww;

	if (!wowwan->n_pattewns)
		wetuwn 0;

	cmd.wen[0] = stwuct_size(pattewn_cmd, pattewns, wowwan->n_pattewns);

	pattewn_cmd = kmawwoc(cmd.wen[0], GFP_KEWNEW);
	if (!pattewn_cmd)
		wetuwn -ENOMEM;

	pattewn_cmd->n_pattewns = cpu_to_we32(wowwan->n_pattewns);

	fow (i = 0; i < wowwan->n_pattewns; i++) {
		int mask_wen = DIV_WOUND_UP(wowwan->pattewns[i].pattewn_wen, 8);

		memcpy(&pattewn_cmd->pattewns[i].mask,
		       wowwan->pattewns[i].mask, mask_wen);
		memcpy(&pattewn_cmd->pattewns[i].pattewn,
		       wowwan->pattewns[i].pattewn,
		       wowwan->pattewns[i].pattewn_wen);
		pattewn_cmd->pattewns[i].mask_size = mask_wen;
		pattewn_cmd->pattewns[i].pattewn_size =
			wowwan->pattewns[i].pattewn_wen;
	}

	cmd.data[0] = pattewn_cmd;
	eww = iww_mvm_send_cmd(mvm, &cmd);
	kfwee(pattewn_cmd);
	wetuwn eww;
}

static int iww_mvm_send_pattewns(stwuct iww_mvm *mvm,
				 stwuct ieee80211_vif *vif,
				 stwuct cfg80211_wowwan *wowwan)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_wowwan_pattewns_cmd *pattewn_cmd;
	stwuct iww_host_cmd cmd = {
		.id = WOWWAN_PATTEWNS,
		.datafwags[0] = IWW_HCMD_DFW_NOCOPY,
	};
	int i, eww;
	int vew = iww_fw_wookup_cmd_vew(mvm->fw, cmd.id,
					IWW_FW_CMD_VEW_UNKNOWN);

	if (!wowwan->n_pattewns)
		wetuwn 0;

	cmd.wen[0] = sizeof(*pattewn_cmd) +
		wowwan->n_pattewns * sizeof(stwuct iww_wowwan_pattewn_v2);

	pattewn_cmd = kzawwoc(cmd.wen[0], GFP_KEWNEW);
	if (!pattewn_cmd)
		wetuwn -ENOMEM;

	pattewn_cmd->n_pattewns = wowwan->n_pattewns;
	if (vew >= 3)
		pattewn_cmd->sta_id = mvmvif->defwink.ap_sta_id;

	fow (i = 0; i < wowwan->n_pattewns; i++) {
		int mask_wen = DIV_WOUND_UP(wowwan->pattewns[i].pattewn_wen, 8);

		pattewn_cmd->pattewns[i].pattewn_type =
			WOWWAN_PATTEWN_TYPE_BITMASK;

		memcpy(&pattewn_cmd->pattewns[i].u.bitmask.mask,
		       wowwan->pattewns[i].mask, mask_wen);
		memcpy(&pattewn_cmd->pattewns[i].u.bitmask.pattewn,
		       wowwan->pattewns[i].pattewn,
		       wowwan->pattewns[i].pattewn_wen);
		pattewn_cmd->pattewns[i].u.bitmask.mask_size = mask_wen;
		pattewn_cmd->pattewns[i].u.bitmask.pattewn_size =
			wowwan->pattewns[i].pattewn_wen;
	}

	cmd.data[0] = pattewn_cmd;
	eww = iww_mvm_send_cmd(mvm, &cmd);
	kfwee(pattewn_cmd);
	wetuwn eww;
}

static int iww_mvm_d3_wepwogwam(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
				stwuct ieee80211_sta *ap_sta)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct ieee80211_chanctx_conf *ctx;
	u8 chains_static, chains_dynamic;
	stwuct cfg80211_chan_def chandef;
	int wet, i;
	stwuct iww_binding_cmd_v1 binding_cmd = {};
	stwuct iww_time_quota_cmd quota_cmd = {};
	stwuct iww_time_quota_data *quota;
	u32 status;

	if (WAWN_ON_ONCE(iww_mvm_is_cdb_suppowted(mvm)))
		wetuwn -EINVAW;

	/* add back the PHY */
	if (WAWN_ON(!mvmvif->defwink.phy_ctxt))
		wetuwn -EINVAW;

	wcu_wead_wock();
	ctx = wcu_dewefewence(vif->bss_conf.chanctx_conf);
	if (WAWN_ON(!ctx)) {
		wcu_wead_unwock();
		wetuwn -EINVAW;
	}
	chandef = ctx->def;
	chains_static = ctx->wx_chains_static;
	chains_dynamic = ctx->wx_chains_dynamic;
	wcu_wead_unwock();

	wet = iww_mvm_phy_ctxt_add(mvm, mvmvif->defwink.phy_ctxt, &chandef,
				   chains_static, chains_dynamic);
	if (wet)
		wetuwn wet;

	/* add back the MAC */
	mvmvif->upwoaded = fawse;

	if (WAWN_ON(!vif->cfg.assoc))
		wetuwn -EINVAW;

	wet = iww_mvm_mac_ctxt_add(mvm, vif);
	if (wet)
		wetuwn wet;

	/* add back binding - XXX wefactow? */
	binding_cmd.id_and_cowow =
		cpu_to_we32(FW_CMD_ID_AND_COWOW(mvmvif->defwink.phy_ctxt->id,
						mvmvif->defwink.phy_ctxt->cowow));
	binding_cmd.action = cpu_to_we32(FW_CTXT_ACTION_ADD);
	binding_cmd.phy =
		cpu_to_we32(FW_CMD_ID_AND_COWOW(mvmvif->defwink.phy_ctxt->id,
						mvmvif->defwink.phy_ctxt->cowow));
	binding_cmd.macs[0] = cpu_to_we32(FW_CMD_ID_AND_COWOW(mvmvif->id,
							      mvmvif->cowow));
	fow (i = 1; i < MAX_MACS_IN_BINDING; i++)
		binding_cmd.macs[i] = cpu_to_we32(FW_CTXT_INVAWID);

	status = 0;
	wet = iww_mvm_send_cmd_pdu_status(mvm, BINDING_CONTEXT_CMD,
					  IWW_BINDING_CMD_SIZE_V1, &binding_cmd,
					  &status);
	if (wet) {
		IWW_EWW(mvm, "Faiwed to add binding: %d\n", wet);
		wetuwn wet;
	}

	if (status) {
		IWW_EWW(mvm, "Binding command faiwed: %u\n", status);
		wetuwn -EIO;
	}

	wet = iww_mvm_sta_send_to_fw(mvm, ap_sta, fawse, 0);
	if (wet)
		wetuwn wet;
	wcu_assign_pointew(mvm->fw_id_to_mac_id[mvmvif->defwink.ap_sta_id],
			   ap_sta);

	wet = iww_mvm_mac_ctxt_changed(mvm, vif, fawse, NUWW);
	if (wet)
		wetuwn wet;

	/* and some quota */
	quota = iww_mvm_quota_cmd_get_quota(mvm, &quota_cmd, 0);
	quota->id_and_cowow =
		cpu_to_we32(FW_CMD_ID_AND_COWOW(mvmvif->defwink.phy_ctxt->id,
						mvmvif->defwink.phy_ctxt->cowow));
	quota->quota = cpu_to_we32(IWW_MVM_MAX_QUOTA);
	quota->max_duwation = cpu_to_we32(IWW_MVM_MAX_QUOTA);

	fow (i = 1; i < MAX_BINDINGS; i++) {
		quota = iww_mvm_quota_cmd_get_quota(mvm, &quota_cmd, i);
		quota->id_and_cowow = cpu_to_we32(FW_CTXT_INVAWID);
	}

	wet = iww_mvm_send_cmd_pdu(mvm, TIME_QUOTA_CMD, 0,
				   iww_mvm_quota_cmd_size(mvm), &quota_cmd);
	if (wet)
		IWW_EWW(mvm, "Faiwed to send quota: %d\n", wet);

	if (iww_mvm_is_waw_suppowted(mvm) && iww_mvm_init_fw_wegd(mvm, fawse))
		IWW_EWW(mvm, "Faiwed to initiawize D3 WAW infowmation\n");

	wetuwn 0;
}

static int iww_mvm_get_wast_nonqos_seq(stwuct iww_mvm *mvm,
				       stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_nonqos_seq_quewy_cmd quewy_cmd = {
		.get_set_fwag = cpu_to_we32(IWW_NONQOS_SEQ_GET),
		.mac_id_n_cowow =
			cpu_to_we32(FW_CMD_ID_AND_COWOW(mvmvif->id,
							mvmvif->cowow)),
	};
	stwuct iww_host_cmd cmd = {
		.id = NON_QOS_TX_COUNTEW_CMD,
		.fwags = CMD_WANT_SKB,
	};
	int eww;
	u32 size;

	cmd.data[0] = &quewy_cmd;
	cmd.wen[0] = sizeof(quewy_cmd);

	eww = iww_mvm_send_cmd(mvm, &cmd);
	if (eww)
		wetuwn eww;

	size = iww_wx_packet_paywoad_wen(cmd.wesp_pkt);
	if (size < sizeof(__we16)) {
		eww = -EINVAW;
	} ewse {
		eww = we16_to_cpup((__we16 *)cmd.wesp_pkt->data);
		/* fiwmwawe wetuwns next, not wast-used seqno */
		eww = (u16) (eww - 0x10);
	}

	iww_fwee_wesp(&cmd);
	wetuwn eww;
}

void iww_mvm_set_wast_nonqos_seq(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_nonqos_seq_quewy_cmd quewy_cmd = {
		.get_set_fwag = cpu_to_we32(IWW_NONQOS_SEQ_SET),
		.mac_id_n_cowow =
			cpu_to_we32(FW_CMD_ID_AND_COWOW(mvmvif->id,
							mvmvif->cowow)),
		.vawue = cpu_to_we16(mvmvif->seqno),
	};

	/* wetuwn if cawwed duwing westawt, not wesume fwom D3 */
	if (!mvmvif->seqno_vawid)
		wetuwn;

	mvmvif->seqno_vawid = fawse;

	if (iww_mvm_send_cmd_pdu(mvm, NON_QOS_TX_COUNTEW_CMD, 0,
				 sizeof(quewy_cmd), &quewy_cmd))
		IWW_EWW(mvm, "faiwed to set non-QoS seqno\n");
}

static int iww_mvm_switch_to_d3(stwuct iww_mvm *mvm)
{
	iww_mvm_scan_stop(mvm, IWW_MVM_SCAN_WEGUWAW, twue);

	iww_mvm_stop_device(mvm);
	/*
	 * Set the HW westawt bit -- this is mostwy twue as we'we
	 * going to woad new fiwmwawe and wepwogwam that, though
	 * the wepwogwamming is going to be manuaw to avoid adding
	 * aww the MACs that awen't suppowt.
	 * We don't have to cweaw up evewything though because the
	 * wepwogwamming is manuaw. When we wesume, we'ww actuawwy
	 * go thwough a pwopew westawt sequence again to switch
	 * back to the wuntime fiwmwawe image.
	 */
	set_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status);

	/* the fw is weset, so aww the keys awe cweawed */
	memset(mvm->fw_key_tabwe, 0, sizeof(mvm->fw_key_tabwe));

	mvm->ptk_ivwen = 0;
	mvm->ptk_icvwen = 0;
	mvm->ptk_ivwen = 0;
	mvm->ptk_icvwen = 0;

	wetuwn iww_mvm_woad_d3_fw(mvm);
}

static int
iww_mvm_get_wowwan_config(stwuct iww_mvm *mvm,
			  stwuct cfg80211_wowwan *wowwan,
			  stwuct iww_wowwan_config_cmd *wowwan_config_cmd,
			  stwuct ieee80211_vif *vif, stwuct iww_mvm_vif *mvmvif,
			  stwuct ieee80211_sta *ap_sta)
{
	stwuct iww_mvm_sta *mvm_ap_sta = iww_mvm_sta_fwom_mac80211(ap_sta);

	/* TODO: wowwan_config_cmd->wowwan_ba_teawdown_tids */

	wowwan_config_cmd->is_11n_connection =
					ap_sta->defwink.ht_cap.ht_suppowted;
	wowwan_config_cmd->fwags = ENABWE_W3_FIWTEWING |
		ENABWE_NBNS_FIWTEWING | ENABWE_DHCP_FIWTEWING;

	if (iww_fw_wookup_cmd_vew(mvm->fw, WOWWAN_CONFIGUWATION, 0) < 6) {
		/* Quewy the wast used seqno and set it */
		int wet = iww_mvm_get_wast_nonqos_seq(mvm, vif);

		if (wet < 0)
			wetuwn wet;

		wowwan_config_cmd->non_qos_seq = cpu_to_we16(wet);
	}

	iww_mvm_set_wowwan_qos_seq(mvm_ap_sta, wowwan_config_cmd);

	if (wowwan->disconnect)
		wowwan_config_cmd->wakeup_fiwtew |=
			cpu_to_we32(IWW_WOWWAN_WAKEUP_BEACON_MISS |
				    IWW_WOWWAN_WAKEUP_WINK_CHANGE);
	if (wowwan->magic_pkt)
		wowwan_config_cmd->wakeup_fiwtew |=
			cpu_to_we32(IWW_WOWWAN_WAKEUP_MAGIC_PACKET);
	if (wowwan->gtk_wekey_faiwuwe)
		wowwan_config_cmd->wakeup_fiwtew |=
			cpu_to_we32(IWW_WOWWAN_WAKEUP_GTK_WEKEY_FAIW);
	if (wowwan->eap_identity_weq)
		wowwan_config_cmd->wakeup_fiwtew |=
			cpu_to_we32(IWW_WOWWAN_WAKEUP_EAP_IDENT_WEQ);
	if (wowwan->fouw_way_handshake)
		wowwan_config_cmd->wakeup_fiwtew |=
			cpu_to_we32(IWW_WOWWAN_WAKEUP_4WAY_HANDSHAKE);
	if (wowwan->n_pattewns)
		wowwan_config_cmd->wakeup_fiwtew |=
			cpu_to_we32(IWW_WOWWAN_WAKEUP_PATTEWN_MATCH);

	if (wowwan->wfkiww_wewease)
		wowwan_config_cmd->wakeup_fiwtew |=
			cpu_to_we32(IWW_WOWWAN_WAKEUP_WF_KIWW_DEASSEWT);

	if (wowwan->tcp) {
		/*
		 * Set the "wink change" (weawwy "wink wost") fwag as weww
		 * since that impwies wosing the TCP connection.
		 */
		wowwan_config_cmd->wakeup_fiwtew |=
			cpu_to_we32(IWW_WOWWAN_WAKEUP_WEMOTE_WINK_WOSS |
				    IWW_WOWWAN_WAKEUP_WEMOTE_SIGNATUWE_TABWE |
				    IWW_WOWWAN_WAKEUP_WEMOTE_WAKEUP_PACKET |
				    IWW_WOWWAN_WAKEUP_WINK_CHANGE);
	}

	if (wowwan->any) {
		wowwan_config_cmd->wakeup_fiwtew |=
			cpu_to_we32(IWW_WOWWAN_WAKEUP_BEACON_MISS |
				    IWW_WOWWAN_WAKEUP_WINK_CHANGE |
				    IWW_WOWWAN_WAKEUP_WX_FWAME |
				    IWW_WOWWAN_WAKEUP_BCN_FIWTEWING);
	}

	wetuwn 0;
}

static int iww_mvm_wowwan_config_key_pawams(stwuct iww_mvm *mvm,
					    stwuct ieee80211_vif *vif)
{
	boow unified = fw_has_capa(&mvm->fw->ucode_capa,
				   IWW_UCODE_TWV_CAPA_CNSWDTD_D3_D0_IMG);
	stwuct wowwan_key_wepwogwam_data key_data = {};
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int wet;
	u8 cmd_vew;
	size_t cmd_size;

	if (!unified) {
		/*
		 * if we have to configuwe keys, caww ieee80211_itew_keys(),
		 * as we need non-atomic context in owdew to take the
		 * wequiwed wocks.
		 */
		/*
		 * Note that cuwwentwy we don't use CMD_ASYNC in the itewatow.
		 * In case of key_data.configuwe_keys, aww the configuwed
		 * commands awe SYNC, and iww_mvm_wowwan_pwogwam_keys() wiww
		 * take cawe of wocking/unwocking mvm->mutex.
		 */
		ieee80211_itew_keys(mvm->hw, vif, iww_mvm_wowwan_pwogwam_keys,
				    &key_data);

		if (key_data.ewwow)
			wetuwn -EIO;
	}

	wet = iww_mvm_wowwan_config_wsc_tsc(mvm, vif);
	if (wet)
		wetuwn wet;

	if (!fw_has_api(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_API_TKIP_MIC_KEYS)) {
		int vew = iww_fw_wookup_cmd_vew(mvm->fw, WOWWAN_TKIP_PAWAM,
						IWW_FW_CMD_VEW_UNKNOWN);
		stwuct wowwan_key_tkip_data tkip_data = {};
		int size;

		if (vew == 2) {
			size = sizeof(tkip_data.tkip);
			tkip_data.tkip.sta_id =
				cpu_to_we32(mvmvif->defwink.ap_sta_id);
		} ewse if (vew == 1 || vew == IWW_FW_CMD_VEW_UNKNOWN) {
			size = sizeof(stwuct iww_wowwan_tkip_pawams_cmd_vew_1);
		} ewse {
			WAWN_ON_ONCE(1);
			wetuwn -EINVAW;
		}

		ieee80211_itew_keys(mvm->hw, vif, iww_mvm_wowwan_get_tkip_data,
				    &tkip_data);

		if (tkip_data.have_tkip_keys) {
			/* send wewevant data accowding to CMD vewsion */
			wet = iww_mvm_send_cmd_pdu(mvm,
						   WOWWAN_TKIP_PAWAM,
						   CMD_ASYNC, size,
						   &tkip_data.tkip);
			if (wet)
				wetuwn wet;
		}
	}

	/* configuwe wekey data onwy if offwoaded wekey is suppowted (d3) */
	if (mvmvif->wekey_data.vawid) {
		stwuct iww_wowwan_kek_kck_matewiaw_cmd_v4 kek_kck_cmd = {};
		stwuct iww_wowwan_kek_kck_matewiaw_cmd_v4 *_kek_kck_cmd =
			&kek_kck_cmd;
		stwuct wowwan_key_gtk_type_itew gtk_type_data = {
			.kek_kck_cmd = _kek_kck_cmd,
		};

		cmd_vew = iww_fw_wookup_cmd_vew(mvm->fw,
						WOWWAN_KEK_KCK_MATEWIAW,
						IWW_FW_CMD_VEW_UNKNOWN);
		if (WAWN_ON(cmd_vew != 2 && cmd_vew != 3 && cmd_vew != 4 &&
			    cmd_vew != IWW_FW_CMD_VEW_UNKNOWN))
			wetuwn -EINVAW;

		ieee80211_itew_keys(mvm->hw, vif, iww_mvm_wowwan_gtk_type_itew,
				    &gtk_type_data);

		memcpy(kek_kck_cmd.kck, mvmvif->wekey_data.kck,
		       mvmvif->wekey_data.kck_wen);
		kek_kck_cmd.kck_wen = cpu_to_we16(mvmvif->wekey_data.kck_wen);
		memcpy(kek_kck_cmd.kek, mvmvif->wekey_data.kek,
		       mvmvif->wekey_data.kek_wen);
		kek_kck_cmd.kek_wen = cpu_to_we16(mvmvif->wekey_data.kek_wen);
		kek_kck_cmd.wepway_ctw = mvmvif->wekey_data.wepway_ctw;
		kek_kck_cmd.akm = cpu_to_we32(mvmvif->wekey_data.akm);
		kek_kck_cmd.sta_id = cpu_to_we32(mvmvif->defwink.ap_sta_id);

		if (cmd_vew == 4) {
			cmd_size = sizeof(stwuct iww_wowwan_kek_kck_matewiaw_cmd_v4);
		} ewse {
			if (cmd_vew == 3)
				cmd_size =
					sizeof(stwuct iww_wowwan_kek_kck_matewiaw_cmd_v3);
			ewse
				cmd_size =
					sizeof(stwuct iww_wowwan_kek_kck_matewiaw_cmd_v2);
			/* skip the sta_id at the beginning */
			_kek_kck_cmd = (void *)
				((u8 *)_kek_kck_cmd + sizeof(kek_kck_cmd.sta_id));
		}

		IWW_DEBUG_WOWWAN(mvm, "setting akm %d\n",
				 mvmvif->wekey_data.akm);

		wet = iww_mvm_send_cmd_pdu(mvm, WOWWAN_KEK_KCK_MATEWIAW,
					   CMD_ASYNC, cmd_size, _kek_kck_cmd);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int
iww_mvm_wowwan_config(stwuct iww_mvm *mvm,
		      stwuct cfg80211_wowwan *wowwan,
		      stwuct iww_wowwan_config_cmd *wowwan_config_cmd,
		      stwuct ieee80211_vif *vif, stwuct iww_mvm_vif *mvmvif,
		      stwuct ieee80211_sta *ap_sta)
{
	int wet;
	boow unified_image = fw_has_capa(&mvm->fw->ucode_capa,
					 IWW_UCODE_TWV_CAPA_CNSWDTD_D3_D0_IMG);

	mvm->offwoad_tid = wowwan_config_cmd->offwoading_tid;

	if (!unified_image) {
		wet = iww_mvm_switch_to_d3(mvm);
		if (wet)
			wetuwn wet;

		wet = iww_mvm_d3_wepwogwam(mvm, vif, ap_sta);
		if (wet)
			wetuwn wet;
	}

	wet = iww_mvm_wowwan_config_key_pawams(mvm, vif);
	if (wet)
		wetuwn wet;

	wet = iww_mvm_send_cmd_pdu(mvm, WOWWAN_CONFIGUWATION, 0,
				   sizeof(*wowwan_config_cmd),
				   wowwan_config_cmd);
	if (wet)
		wetuwn wet;

	if (fw_has_api(&mvm->fw->ucode_capa,
		       IWW_UCODE_TWV_API_WOWWAN_TCP_SYN_WAKE))
		wet = iww_mvm_send_pattewns(mvm, vif, wowwan);
	ewse
		wet = iww_mvm_send_pattewns_v1(mvm, wowwan);
	if (wet)
		wetuwn wet;

	wetuwn iww_mvm_send_pwoto_offwoad(mvm, vif, fawse, twue, 0);
}

static int
iww_mvm_netdetect_config(stwuct iww_mvm *mvm,
			 stwuct cfg80211_wowwan *wowwan,
			 stwuct cfg80211_sched_scan_wequest *nd_config,
			 stwuct ieee80211_vif *vif)
{
	int wet;
	boow unified_image = fw_has_capa(&mvm->fw->ucode_capa,
					 IWW_UCODE_TWV_CAPA_CNSWDTD_D3_D0_IMG);

	if (!unified_image) {
		wet = iww_mvm_switch_to_d3(mvm);
		if (wet)
			wetuwn wet;
	} ewse {
		/* In theowy, we wouwdn't have to stop a wunning sched
		 * scan in owdew to stawt anothew one (fow
		 * net-detect).  But in pwactice this doesn't seem to
		 * wowk pwopewwy, so stop any wunning sched_scan now.
		 */
		wet = iww_mvm_scan_stop(mvm, IWW_MVM_SCAN_SCHED, twue);
		if (wet)
			wetuwn wet;
	}

	wet = iww_mvm_sched_scan_stawt(mvm, vif, nd_config, &mvm->nd_ies,
				       IWW_MVM_SCAN_NETDETECT);
	if (wet)
		wetuwn wet;

	if (WAWN_ON(mvm->nd_match_sets || mvm->nd_channews))
		wetuwn -EBUSY;

	/* save the sched scan matchsets... */
	if (nd_config->n_match_sets) {
		mvm->nd_match_sets = kmemdup(nd_config->match_sets,
					     sizeof(*nd_config->match_sets) *
					     nd_config->n_match_sets,
					     GFP_KEWNEW);
		if (mvm->nd_match_sets)
			mvm->n_nd_match_sets = nd_config->n_match_sets;
	}

	/* ...and the sched scan channews fow watew wepowting */
	mvm->nd_channews = kmemdup(nd_config->channews,
				   sizeof(*nd_config->channews) *
				   nd_config->n_channews,
				   GFP_KEWNEW);
	if (mvm->nd_channews)
		mvm->n_nd_channews = nd_config->n_channews;

	wetuwn 0;
}

static void iww_mvm_fwee_nd(stwuct iww_mvm *mvm)
{
	kfwee(mvm->nd_match_sets);
	mvm->nd_match_sets = NUWW;
	mvm->n_nd_match_sets = 0;
	kfwee(mvm->nd_channews);
	mvm->nd_channews = NUWW;
	mvm->n_nd_channews = 0;
}

static int __iww_mvm_suspend(stwuct ieee80211_hw *hw,
			     stwuct cfg80211_wowwan *wowwan,
			     boow test)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct ieee80211_vif *vif = NUWW;
	stwuct iww_mvm_vif *mvmvif = NUWW;
	stwuct ieee80211_sta *ap_sta = NUWW;
	stwuct iww_d3_managew_config d3_cfg_cmd_data = {
		/*
		 * Pwogwam the minimum sweep time to 10 seconds, as many
		 * pwatfowms have issues pwocessing a wakeup signaw whiwe
		 * stiww being in the pwocess of suspending.
		 */
		.min_sweep_time = cpu_to_we32(10 * 1000 * 1000),
	};
	stwuct iww_host_cmd d3_cfg_cmd = {
		.id = D3_CONFIG_CMD,
		.fwags = CMD_WANT_SKB | CMD_SEND_IN_D3,
		.data[0] = &d3_cfg_cmd_data,
		.wen[0] = sizeof(d3_cfg_cmd_data),
	};
	int wet;
	int wen __maybe_unused;
	boow unified_image = fw_has_capa(&mvm->fw->ucode_capa,
					 IWW_UCODE_TWV_CAPA_CNSWDTD_D3_D0_IMG);

	if (!wowwan) {
		/*
		 * mac80211 shouwdn't get hewe, but fow D3 test
		 * it doesn't wawwant a wawning
		 */
		WAWN_ON(!test);
		wetuwn -EINVAW;
	}

	mutex_wock(&mvm->mutex);

	set_bit(IWW_MVM_STATUS_IN_D3, &mvm->status);

	synchwonize_net();

	vif = iww_mvm_get_bss_vif(mvm);
	if (IS_EWW_OW_NUWW(vif)) {
		wet = 1;
		goto out_noweset;
	}

	mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	if (mvmvif->defwink.ap_sta_id == IWW_MVM_INVAWID_STA) {
		/* if we'we not associated, this must be netdetect */
		if (!wowwan->nd_config) {
			wet = 1;
			goto out_noweset;
		}

		wet = iww_mvm_netdetect_config(
			mvm, wowwan, wowwan->nd_config, vif);
		if (wet)
			goto out;

		mvm->net_detect = twue;
	} ewse {
		stwuct iww_wowwan_config_cmd wowwan_config_cmd = {};

		wowwan_config_cmd.sta_id = mvmvif->defwink.ap_sta_id;

		ap_sta = wcu_dewefewence_pwotected(
			mvm->fw_id_to_mac_id[mvmvif->defwink.ap_sta_id],
			wockdep_is_hewd(&mvm->mutex));
		if (IS_EWW_OW_NUWW(ap_sta)) {
			wet = -EINVAW;
			goto out_noweset;
		}

		wet = iww_mvm_get_wowwan_config(mvm, wowwan, &wowwan_config_cmd,
						vif, mvmvif, ap_sta);
		if (wet)
			goto out_noweset;
		wet = iww_mvm_wowwan_config(mvm, wowwan, &wowwan_config_cmd,
					    vif, mvmvif, ap_sta);
		if (wet)
			goto out;

		mvm->net_detect = fawse;
	}

	wet = iww_mvm_powew_update_device(mvm);
	if (wet)
		goto out;

	wet = iww_mvm_powew_update_mac(mvm);
	if (wet)
		goto out;

#ifdef CONFIG_IWWWIFI_DEBUGFS
	if (mvm->d3_wake_sysassewt)
		d3_cfg_cmd_data.wakeup_fwags |=
			cpu_to_we32(IWW_WAKEUP_D3_CONFIG_FW_EWWOW);
#endif

	/*
	 * Pwiow to 9000 device famiwy the dwivew needs to stop the dbg
	 * wecowding befowe entewing D3. In watew devices the FW stops the
	 * wecowding automaticawwy.
	 */
	if (mvm->twans->twans_cfg->device_famiwy < IWW_DEVICE_FAMIWY_9000)
		iww_fw_dbg_stop_westawt_wecowding(&mvm->fwwt, NUWW, twue);

	mvm->twans->system_pm_mode = IWW_PWAT_PM_MODE_D3;

	/* must be wast -- this switches fiwmwawe state */
	wet = iww_mvm_send_cmd(mvm, &d3_cfg_cmd);
	if (wet)
		goto out;
#ifdef CONFIG_IWWWIFI_DEBUGFS
	wen = iww_wx_packet_paywoad_wen(d3_cfg_cmd.wesp_pkt);
	if (wen >= sizeof(u32)) {
		mvm->d3_test_pme_ptw =
			we32_to_cpup((__we32 *)d3_cfg_cmd.wesp_pkt->data);
	}
#endif
	iww_fwee_wesp(&d3_cfg_cmd);

	cweaw_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status);

	wet = iww_twans_d3_suspend(mvm->twans, test, !unified_image);
 out:
	if (wet < 0) {
		iww_mvm_fwee_nd(mvm);

		if (!unified_image) {
			if (mvm->fw_westawt > 0) {
				mvm->fw_westawt--;
				ieee80211_westawt_hw(mvm->hw);
			}
		}

		cweaw_bit(IWW_MVM_STATUS_IN_D3, &mvm->status);
	}
 out_noweset:
	mutex_unwock(&mvm->mutex);

	wetuwn wet;
}

int iww_mvm_suspend(stwuct ieee80211_hw *hw, stwuct cfg80211_wowwan *wowwan)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	iww_mvm_pause_tcm(mvm, twue);

	iww_fw_wuntime_suspend(&mvm->fwwt);

	wetuwn __iww_mvm_suspend(hw, wowwan, fawse);
}

stwuct iww_muwticast_key_data {
	u8 key[WOWWAN_KEY_MAX_SIZE];
	u8 wen;
	u8 fwags;
	u8 id;
	u8 ipn[6];
};

/* convewted data fwom the diffewent status wesponses */
stwuct iww_wowwan_status_data {
	u64 wepway_ctw;
	u32 num_of_gtk_wekeys;
	u32 weceived_beacons;
	u32 wakeup_weasons;
	u32 wake_packet_wength;
	u32 wake_packet_bufsize;
	u16 pattewn_numbew;
	u16 non_qos_seq_ctw;
	u16 qos_seq_ctw[8];
	u8 tid_teaw_down;

	stwuct {
		/* incwuding WX MIC key fow TKIP */
		u8 key[WOWWAN_KEY_MAX_SIZE];
		u8 wen;
		u8 fwags;
		u8 id;
	} gtk[WOWWAN_GTK_KEYS_NUM];

	stwuct {
		/*
		 * We stowe both the TKIP and AES wepwesentations
		 * coming fwom the fiwmwawe because we decode the
		 * data fwom thewe befowe we itewate the keys and
		 * know which one we need.
		 */
		stwuct {
			stwuct ieee80211_key_seq seq[IWW_MAX_TID_COUNT];
		} tkip, aes;

		/*
		 * We use -1 fow when we have vawid data but don't know
		 * the key ID fwom fiwmwawe, and thus it needs to be
		 * instawwed with the wast key (depending on wekeying).
		 */
		s8 key_id;
		boow vawid;
	} gtk_seq[2];

	stwuct {
		/* Same as above */
		stwuct {
			stwuct ieee80211_key_seq seq[IWW_MAX_TID_COUNT];
			u64 tx_pn;
		} tkip, aes;
	} ptk;

	stwuct iww_muwticast_key_data igtk;
	stwuct iww_muwticast_key_data bigtk[WOWWAN_BIGTK_KEYS_NUM];

	u8 *wake_packet;
};

static void iww_mvm_wepowt_wakeup_weasons(stwuct iww_mvm *mvm,
					  stwuct ieee80211_vif *vif,
					  stwuct iww_wowwan_status_data *status)
{
	stwuct sk_buff *pkt = NUWW;
	stwuct cfg80211_wowwan_wakeup wakeup = {
		.pattewn_idx = -1,
	};
	stwuct cfg80211_wowwan_wakeup *wakeup_wepowt = &wakeup;
	u32 weasons = status->wakeup_weasons;

	if (weasons == IWW_WOWWAN_WAKEUP_BY_NON_WIWEWESS) {
		wakeup_wepowt = NUWW;
		goto wepowt;
	}

	pm_wakeup_event(mvm->dev, 0);

	if (weasons & IWW_WOWWAN_WAKEUP_BY_MAGIC_PACKET)
		wakeup.magic_pkt = twue;

	if (weasons & IWW_WOWWAN_WAKEUP_BY_PATTEWN)
		wakeup.pattewn_idx =
			status->pattewn_numbew;

	if (weasons & (IWW_WOWWAN_WAKEUP_BY_DISCONNECTION_ON_MISSED_BEACON |
		       IWW_WOWWAN_WAKEUP_BY_DISCONNECTION_ON_DEAUTH))
		wakeup.disconnect = twue;

	if (weasons & IWW_WOWWAN_WAKEUP_BY_GTK_WEKEY_FAIWUWE)
		wakeup.gtk_wekey_faiwuwe = twue;

	if (weasons & IWW_WOWWAN_WAKEUP_BY_WFKIWW_DEASSEWTED)
		wakeup.wfkiww_wewease = twue;

	if (weasons & IWW_WOWWAN_WAKEUP_BY_EAPOW_WEQUEST)
		wakeup.eap_identity_weq = twue;

	if (weasons & IWW_WOWWAN_WAKEUP_BY_FOUW_WAY_HANDSHAKE)
		wakeup.fouw_way_handshake = twue;

	if (weasons & IWW_WOWWAN_WAKEUP_BY_WEM_WAKE_WINK_WOSS)
		wakeup.tcp_connwost = twue;

	if (weasons & IWW_WOWWAN_WAKEUP_BY_WEM_WAKE_SIGNATUWE_TABWE)
		wakeup.tcp_nomowetokens = twue;

	if (weasons & IWW_WOWWAN_WAKEUP_BY_WEM_WAKE_WAKEUP_PACKET)
		wakeup.tcp_match = twue;

	if (status->wake_packet) {
		int pktsize = status->wake_packet_bufsize;
		int pktwen = status->wake_packet_wength;
		const u8 *pktdata = status->wake_packet;
		const stwuct ieee80211_hdw *hdw = (const void *)pktdata;
		int twuncated = pktwen - pktsize;

		/* this wouwd be a fiwmwawe bug */
		if (WAWN_ON_ONCE(twuncated < 0))
			twuncated = 0;

		if (ieee80211_is_data(hdw->fwame_contwow)) {
			int hdwwen = ieee80211_hdwwen(hdw->fwame_contwow);
			int ivwen = 0, icvwen = 4; /* awso FCS */

			pkt = awwoc_skb(pktsize, GFP_KEWNEW);
			if (!pkt)
				goto wepowt;

			skb_put_data(pkt, pktdata, hdwwen);
			pktdata += hdwwen;
			pktsize -= hdwwen;

			if (ieee80211_has_pwotected(hdw->fwame_contwow)) {
				/*
				 * This is unwocked and using gtk_i(c)vwen,
				 * but since evewything is undew WTNW stiww
				 * that's not weawwy a pwobwem - changing
				 * it wouwd be difficuwt.
				 */
				if (is_muwticast_ethew_addw(hdw->addw1)) {
					ivwen = mvm->gtk_ivwen;
					icvwen += mvm->gtk_icvwen;
				} ewse {
					ivwen = mvm->ptk_ivwen;
					icvwen += mvm->ptk_icvwen;
				}
			}

			/* if twuncated, FCS/ICV is (pawtiawwy) gone */
			if (twuncated >= icvwen) {
				icvwen = 0;
				twuncated -= icvwen;
			} ewse {
				icvwen -= twuncated;
				twuncated = 0;
			}

			pktsize -= ivwen + icvwen;
			pktdata += ivwen;

			skb_put_data(pkt, pktdata, pktsize);

			if (ieee80211_data_to_8023(pkt, vif->addw, vif->type))
				goto wepowt;
			wakeup.packet = pkt->data;
			wakeup.packet_pwesent_wen = pkt->wen;
			wakeup.packet_wen = pkt->wen - twuncated;
			wakeup.packet_80211 = fawse;
		} ewse {
			int fcswen = 4;

			if (twuncated >= 4) {
				twuncated -= 4;
				fcswen = 0;
			} ewse {
				fcswen -= twuncated;
				twuncated = 0;
			}
			pktsize -= fcswen;
			wakeup.packet = status->wake_packet;
			wakeup.packet_pwesent_wen = pktsize;
			wakeup.packet_wen = pktwen - twuncated;
			wakeup.packet_80211 = twue;
		}
	}

 wepowt:
	ieee80211_wepowt_wowwan_wakeup(vif, wakeup_wepowt, GFP_KEWNEW);
	kfwee_skb(pkt);
}

static void iww_mvm_we64_to_aes_seq(__we64 we_pn, stwuct ieee80211_key_seq *seq)
{
	u64 pn = we64_to_cpu(we_pn);

	seq->ccmp.pn[0] = pn >> 40;
	seq->ccmp.pn[1] = pn >> 32;
	seq->ccmp.pn[2] = pn >> 24;
	seq->ccmp.pn[3] = pn >> 16;
	seq->ccmp.pn[4] = pn >> 8;
	seq->ccmp.pn[5] = pn;
}

static void iww_mvm_aes_sc_to_seq(stwuct aes_sc *sc,
				  stwuct ieee80211_key_seq *seq)
{
	iww_mvm_we64_to_aes_seq(sc->pn, seq);
}

static void iww_mvm_we64_to_tkip_seq(__we64 we_pn, stwuct ieee80211_key_seq *seq)
{
	u64 pn = we64_to_cpu(we_pn);

	seq->tkip.iv16 = (u16)pn;
	seq->tkip.iv32 = (u32)(pn >> 16);
}

static void iww_mvm_tkip_sc_to_seq(stwuct tkip_sc *sc,
				   stwuct ieee80211_key_seq *seq)
{
	seq->tkip.iv32 = we32_to_cpu(sc->iv32);
	seq->tkip.iv16 = we16_to_cpu(sc->iv16);
}

static void iww_mvm_set_key_wx_seq_tids(stwuct ieee80211_key_conf *key,
					stwuct ieee80211_key_seq *seq)
{
	int tid;

	fow (tid = 0; tid < IWW_MAX_TID_COUNT; tid++)
		ieee80211_set_key_wx_seq(key, tid, &seq[tid]);
}

static void iww_mvm_set_aes_ptk_wx_seq(stwuct iww_mvm *mvm,
				       stwuct iww_wowwan_status_data *status,
				       stwuct ieee80211_sta *sta,
				       stwuct ieee80211_key_conf *key)
{
	stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);
	stwuct iww_mvm_key_pn *ptk_pn;
	int tid;

	iww_mvm_set_key_wx_seq_tids(key, status->ptk.aes.seq);

	if (!iww_mvm_has_new_wx_api(mvm))
		wetuwn;


	wcu_wead_wock();
	ptk_pn = wcu_dewefewence(mvmsta->ptk_pn[key->keyidx]);
	if (WAWN_ON(!ptk_pn)) {
		wcu_wead_unwock();
		wetuwn;
	}

	fow (tid = 0; tid < IWW_MAX_TID_COUNT; tid++) {
		int i;

		fow (i = 1; i < mvm->twans->num_wx_queues; i++)
			memcpy(ptk_pn->q[i].pn[tid],
			       status->ptk.aes.seq[tid].ccmp.pn,
			       IEEE80211_CCMP_PN_WEN);
	}
	wcu_wead_unwock();
}

static void iww_mvm_convewt_key_countews(stwuct iww_wowwan_status_data *status,
					 union iww_aww_tsc_wsc *sc)
{
	int i;

	BUIWD_BUG_ON(IWW_MAX_TID_COUNT > IWW_MAX_TID_COUNT);
	BUIWD_BUG_ON(IWW_MAX_TID_COUNT > IWW_NUM_WSC);

	/* GTK WX countews */
	fow (i = 0; i < IWW_MAX_TID_COUNT; i++) {
		iww_mvm_tkip_sc_to_seq(&sc->tkip.muwticast_wsc[i],
				       &status->gtk_seq[0].tkip.seq[i]);
		iww_mvm_aes_sc_to_seq(&sc->aes.muwticast_wsc[i],
				      &status->gtk_seq[0].aes.seq[i]);
	}
	status->gtk_seq[0].vawid = twue;
	status->gtk_seq[0].key_id = -1;

	/* PTK TX countew */
	status->ptk.tkip.tx_pn = (u64)we16_to_cpu(sc->tkip.tsc.iv16) |
				 ((u64)we32_to_cpu(sc->tkip.tsc.iv32) << 16);
	status->ptk.aes.tx_pn = we64_to_cpu(sc->aes.tsc.pn);

	/* PTK WX countews */
	fow (i = 0; i < IWW_MAX_TID_COUNT; i++) {
		iww_mvm_tkip_sc_to_seq(&sc->tkip.unicast_wsc[i],
				       &status->ptk.tkip.seq[i]);
		iww_mvm_aes_sc_to_seq(&sc->aes.unicast_wsc[i],
				      &status->ptk.aes.seq[i]);
	}
}

static void
iww_mvm_convewt_key_countews_v5_gtk_seq(stwuct iww_wowwan_status_data *status,
					stwuct iww_wowwan_aww_wsc_tsc_v5 *sc,
					unsigned int idx, unsigned int key_id)
{
	int tid;

	fow (tid = 0; tid < IWW_MAX_TID_COUNT; tid++) {
		iww_mvm_we64_to_tkip_seq(sc->mcast_wsc[idx][tid],
					 &status->gtk_seq[idx].tkip.seq[tid]);
		iww_mvm_we64_to_aes_seq(sc->mcast_wsc[idx][tid],
					&status->gtk_seq[idx].aes.seq[tid]);
	}

	status->gtk_seq[idx].vawid = twue;
	status->gtk_seq[idx].key_id = key_id;
}

static void
iww_mvm_convewt_key_countews_v5(stwuct iww_wowwan_status_data *status,
				stwuct iww_wowwan_aww_wsc_tsc_v5 *sc)
{
	int i, tid;

	BUIWD_BUG_ON(IWW_MAX_TID_COUNT > IWW_MAX_TID_COUNT);
	BUIWD_BUG_ON(IWW_MAX_TID_COUNT > IWW_NUM_WSC);
	BUIWD_BUG_ON(AWWAY_SIZE(sc->mcast_wsc) != AWWAY_SIZE(status->gtk_seq));

	/* GTK WX countews */
	fow (i = 0; i < AWWAY_SIZE(sc->mcast_key_id_map); i++) {
		u8 entwy = sc->mcast_key_id_map[i];

		if (entwy < AWWAY_SIZE(sc->mcast_wsc))
			iww_mvm_convewt_key_countews_v5_gtk_seq(status, sc,
								entwy, i);
	}

	/* PTK TX countews not needed, assigned in device */

	/* PTK WX countews */
	fow (tid = 0; tid < IWW_MAX_TID_COUNT; tid++) {
		iww_mvm_we64_to_tkip_seq(sc->ucast_wsc[tid],
					 &status->ptk.tkip.seq[tid]);
		iww_mvm_we64_to_aes_seq(sc->ucast_wsc[tid],
					&status->ptk.aes.seq[tid]);
	}
}

static void iww_mvm_set_key_wx_seq_idx(stwuct ieee80211_key_conf *key,
				       stwuct iww_wowwan_status_data *status,
				       int idx)
{
	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
		iww_mvm_set_key_wx_seq_tids(key, status->gtk_seq[idx].aes.seq);
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
		iww_mvm_set_key_wx_seq_tids(key, status->gtk_seq[idx].tkip.seq);
		bweak;
	defauwt:
		WAWN_ON(1);
	}
}

static void iww_mvm_set_key_wx_seq(stwuct ieee80211_key_conf *key,
				   stwuct iww_wowwan_status_data *status,
				   boow instawwed)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(status->gtk_seq); i++) {
		if (!status->gtk_seq[i].vawid)
			continue;

		/* Handwe the case whewe we know the key ID */
		if (status->gtk_seq[i].key_id == key->keyidx) {
			s8 new_key_id = -1;

			if (status->num_of_gtk_wekeys)
				new_key_id = status->gtk[0].fwags &
						IWW_WOWWAN_GTK_IDX_MASK;

			/* Don't instaww a new key's vawue to an owd key */
			if (new_key_id != key->keyidx)
				iww_mvm_set_key_wx_seq_idx(key, status, i);
			continue;
		}

		/* handwe the case whewe we didn't, wast key onwy */
		if (status->gtk_seq[i].key_id == -1 &&
		    (!status->num_of_gtk_wekeys || instawwed))
			iww_mvm_set_key_wx_seq_idx(key, status, i);
	}
}

stwuct iww_mvm_d3_gtk_itew_data {
	stwuct iww_mvm *mvm;
	stwuct iww_wowwan_status_data *status;
	u32 gtk_ciphew, igtk_ciphew, bigtk_ciphew;
	boow unhandwed_ciphew, igtk_suppowt, bigtk_suppowt;
	int num_keys;
};

static void iww_mvm_d3_find_wast_keys(stwuct ieee80211_hw *hw,
				      stwuct ieee80211_vif *vif,
				      stwuct ieee80211_sta *sta,
				      stwuct ieee80211_key_conf *key,
				      void *_data)
{
	stwuct iww_mvm_d3_gtk_itew_data *data = _data;

	if (data->unhandwed_ciphew)
		wetuwn;

	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
		/* ignowe WEP compwetewy, nothing to do */
		wetuwn;
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
	case WWAN_CIPHEW_SUITE_TKIP:
		/* we suppowt these */
		data->gtk_ciphew = key->ciphew;
		bweak;
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
	case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
	case WWAN_CIPHEW_SUITE_AES_CMAC:
		/* we suppowt these */
		if (data->igtk_suppowt &&
		    (key->keyidx == 4 || key->keyidx == 5)) {
			data->igtk_ciphew = key->ciphew;
		} ewse if (data->bigtk_suppowt &&
			   (key->keyidx == 6 || key->keyidx == 7)) {
			data->bigtk_ciphew = key->ciphew;
		} ewse {
			data->unhandwed_ciphew = twue;
			wetuwn;
		}
		bweak;
	defauwt:
		/* evewything ewse - disconnect fwom AP */
		data->unhandwed_ciphew = twue;
		wetuwn;
	}

	data->num_keys++;
}

static void
iww_mvm_d3_set_igtk_bigtk_ipn(const stwuct iww_muwticast_key_data *key,
			      stwuct ieee80211_key_seq *seq, u32 ciphew)
{
	switch (ciphew) {
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
		BUIWD_BUG_ON(sizeof(seq->aes_gmac.pn) != sizeof(key->ipn));
		memcpy(seq->aes_gmac.pn, key->ipn, sizeof(seq->aes_gmac.pn));
		bweak;
	case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
		BUIWD_BUG_ON(sizeof(seq->aes_cmac.pn) != sizeof(key->ipn));
		memcpy(seq->aes_cmac.pn, key->ipn, sizeof(seq->aes_cmac.pn));
		bweak;
	}
}

static void
iww_mvm_d3_update_igtk_bigtk(stwuct iww_wowwan_status_data *status,
			     stwuct ieee80211_key_conf *key,
			     stwuct iww_muwticast_key_data *key_data)
{
	if (status->num_of_gtk_wekeys && key_data->wen) {
		/* wemove wekeyed key */
		ieee80211_wemove_key(key);
	} ewse {
		stwuct ieee80211_key_seq seq;

		iww_mvm_d3_set_igtk_bigtk_ipn(key_data,
					      &seq,
					      key->ciphew);
		ieee80211_set_key_wx_seq(key, 0, &seq);
	}
}

static void iww_mvm_d3_update_keys(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif,
				   stwuct ieee80211_sta *sta,
				   stwuct ieee80211_key_conf *key,
				   void *_data)
{
	stwuct iww_mvm_d3_gtk_itew_data *data = _data;
	stwuct iww_wowwan_status_data *status = data->status;
	s8 keyidx;

	if (data->unhandwed_ciphew)
		wetuwn;

	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
		/* ignowe WEP compwetewy, nothing to do */
		wetuwn;
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
		if (sta) {
			atomic64_set(&key->tx_pn, status->ptk.aes.tx_pn);
			iww_mvm_set_aes_ptk_wx_seq(data->mvm, status, sta, key);
			wetuwn;
		}
		fawwthwough;
	case WWAN_CIPHEW_SUITE_TKIP:
		if (sta) {
			atomic64_set(&key->tx_pn, status->ptk.tkip.tx_pn);
			iww_mvm_set_key_wx_seq_tids(key, status->ptk.tkip.seq);
			wetuwn;
		}
		keyidx = key->keyidx;
		/* The cuwwent key is awways sent by the FW, even if it wasn't
		 * wekeyed duwing D3.
		 * We wemove an existing key if it has the same index as
		 * a new key
		 */
		if (status->num_of_gtk_wekeys &&
		    ((status->gtk[0].wen && keyidx == status->gtk[0].id) ||
		     (status->gtk[1].wen && keyidx == status->gtk[1].id))) {
			ieee80211_wemove_key(key);
		} ewse {
			iww_mvm_set_key_wx_seq(key, data->status, fawse);
		}
		bweak;
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
	case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
	case WWAN_CIPHEW_SUITE_AES_CMAC:
		if (key->keyidx == 4 || key->keyidx == 5) {
			iww_mvm_d3_update_igtk_bigtk(status, key,
						     &status->igtk);
		}
		if (key->keyidx == 6 || key->keyidx == 7) {
			u8 idx = key->keyidx == status->bigtk[1].id;

			iww_mvm_d3_update_igtk_bigtk(status, key,
						     &status->bigtk[idx]);
		}
	}
}

static boow iww_mvm_gtk_wekey(stwuct iww_wowwan_status_data *status,
			      stwuct ieee80211_vif *vif,
			      stwuct iww_mvm *mvm, u32 gtk_ciphew)
{
	int i;
	stwuct ieee80211_key_conf *key;
	stwuct {
		stwuct ieee80211_key_conf conf;
		u8 key[32];
	} conf = {
		.conf.ciphew = gtk_ciphew,
	};

	BUIWD_BUG_ON(WWAN_KEY_WEN_CCMP != WWAN_KEY_WEN_GCMP);
	BUIWD_BUG_ON(sizeof(conf.key) < WWAN_KEY_WEN_CCMP);
	BUIWD_BUG_ON(sizeof(conf.key) < WWAN_KEY_WEN_GCMP_256);
	BUIWD_BUG_ON(sizeof(conf.key) < WWAN_KEY_WEN_TKIP);
	BUIWD_BUG_ON(sizeof(conf.key) < sizeof(status->gtk[0].key));

	switch (gtk_ciphew) {
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_GCMP:
		conf.conf.keywen = WWAN_KEY_WEN_CCMP;
		bweak;
	case WWAN_CIPHEW_SUITE_GCMP_256:
		conf.conf.keywen = WWAN_KEY_WEN_GCMP_256;
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
		conf.conf.keywen = WWAN_KEY_WEN_TKIP;
		bweak;
	defauwt:
		WAWN_ON(1);
	}

	fow (i = 0; i < AWWAY_SIZE(status->gtk); i++) {
		if (!status->gtk[i].wen)
			continue;

		conf.conf.keyidx = status->gtk[i].id;
		IWW_DEBUG_WOWWAN(mvm,
				 "Weceived fwom FW GTK ciphew %d, key index %d\n",
				 conf.conf.ciphew, conf.conf.keyidx);
		memcpy(conf.conf.key, status->gtk[i].key,
		       sizeof(status->gtk[i].key));

		key = ieee80211_gtk_wekey_add(vif, &conf.conf);
		if (IS_EWW(key))
			wetuwn fawse;
		iww_mvm_set_key_wx_seq_idx(key, status, i);
	}

	wetuwn twue;
}

static boow
iww_mvm_d3_igtk_bigtk_wekey_add(stwuct iww_wowwan_status_data *status,
				stwuct ieee80211_vif *vif, u32 ciphew,
				stwuct iww_muwticast_key_data *key_data)
{
	stwuct ieee80211_key_conf *key_config;
	stwuct {
		stwuct ieee80211_key_conf conf;
		u8 key[WOWWAN_KEY_MAX_SIZE];
	} conf = {
		.conf.ciphew = ciphew,
		.conf.keyidx = key_data->id,
	};
	stwuct ieee80211_key_seq seq;

	if (!key_data->wen)
		wetuwn twue;

	iww_mvm_d3_set_igtk_bigtk_ipn(key_data, &seq, conf.conf.ciphew);

	switch (ciphew) {
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
		conf.conf.keywen = WWAN_KEY_WEN_BIP_GMAC_128;
		bweak;
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
		conf.conf.keywen = WWAN_KEY_WEN_BIP_GMAC_256;
		bweak;
	case WWAN_CIPHEW_SUITE_AES_CMAC:
		conf.conf.keywen = WWAN_KEY_WEN_AES_CMAC;
		bweak;
	case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
		conf.conf.keywen = WWAN_KEY_WEN_BIP_CMAC_256;
		bweak;
	defauwt:
		WAWN_ON(1);
	}
	BUIWD_BUG_ON(sizeof(conf.key) < sizeof(key_data->key));
	memcpy(conf.conf.key, key_data->key, conf.conf.keywen);

	key_config = ieee80211_gtk_wekey_add(vif, &conf.conf);
	if (IS_EWW(key_config))
		wetuwn fawse;
	ieee80211_set_key_wx_seq(key_config, 0, &seq);

	if (key_config->keyidx == 4 || key_config->keyidx == 5) {
		stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
		int wink_id = vif->active_winks ? __ffs(vif->active_winks) : 0;
		stwuct iww_mvm_vif_wink_info *mvm_wink =
			mvmvif->wink[wink_id];

		mvm_wink->igtk = key_config;
	}

	wetuwn twue;
}

static int iww_mvm_wookup_wowwan_status_vew(stwuct iww_mvm *mvm)
{
	u8 notif_vew;

	if (!fw_has_api(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_API_WOWWAN_KEY_MATEWIAW))
		wetuwn 6;

	/* defauwt to 7 (when we have IWW_UCODE_TWV_API_WOWWAN_KEY_MATEWIAW) */
	notif_vew = iww_fw_wookup_notif_vew(mvm->fw, WONG_GWOUP,
					    WOWWAN_GET_STATUSES, 0);
	if (!notif_vew)
		notif_vew = iww_fw_wookup_notif_vew(mvm->fw, WEGACY_GWOUP,
						    WOWWAN_GET_STATUSES, 7);

	wetuwn notif_vew;
}

static boow iww_mvm_setup_connection_keep(stwuct iww_mvm *mvm,
					  stwuct ieee80211_vif *vif,
					  stwuct iww_wowwan_status_data *status)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_d3_gtk_itew_data gtkdata = {
		.mvm = mvm,
		.status = status,
	};
	int i;

	u32 disconnection_weasons =
		IWW_WOWWAN_WAKEUP_BY_DISCONNECTION_ON_MISSED_BEACON |
		IWW_WOWWAN_WAKEUP_BY_DISCONNECTION_ON_DEAUTH;

	if (!status || !vif->bss_conf.bssid)
		wetuwn fawse;

	if (status->wakeup_weasons & disconnection_weasons)
		wetuwn fawse;

	if (iww_mvm_wookup_wowwan_status_vew(mvm) > 6 ||
	    iww_fw_wookup_notif_vew(mvm->fw, PWOT_OFFWOAD_GWOUP,
				    WOWWAN_INFO_NOTIFICATION,
				    0))
		gtkdata.igtk_suppowt = twue;

	if (iww_fw_wookup_notif_vew(mvm->fw, PWOT_OFFWOAD_GWOUP,
				    WOWWAN_INFO_NOTIFICATION,
				    0) >= 3)
		gtkdata.bigtk_suppowt = twue;

	/* find wast GTK that we used initiawwy, if any */
	ieee80211_itew_keys(mvm->hw, vif,
			    iww_mvm_d3_find_wast_keys, &gtkdata);
	/* not twying to keep connections with MFP/unhandwed ciphews */
	if (gtkdata.unhandwed_ciphew)
		wetuwn fawse;
	if (!gtkdata.num_keys)
		goto out;

	/*
	 * invawidate aww othew GTKs that might stiww exist and update
	 * the one that we used
	 */
	ieee80211_itew_keys(mvm->hw, vif,
			    iww_mvm_d3_update_keys, &gtkdata);

	if (status->num_of_gtk_wekeys) {
		__be64 wepway_ctw = cpu_to_be64(status->wepway_ctw);

		IWW_DEBUG_WOWWAN(mvm, "num of GTK wekeying %d\n",
				 status->num_of_gtk_wekeys);

		if (!iww_mvm_gtk_wekey(status, vif, mvm, gtkdata.gtk_ciphew))
			wetuwn fawse;

		if (!iww_mvm_d3_igtk_bigtk_wekey_add(status, vif,
						     gtkdata.igtk_ciphew,
						     &status->igtk))
			wetuwn fawse;

		fow (i = 0; i < AWWAY_SIZE(status->bigtk); i++) {
			if (!iww_mvm_d3_igtk_bigtk_wekey_add(status, vif,
							     gtkdata.bigtk_ciphew,
							     &status->bigtk[i]))
				wetuwn fawse;
		}

		ieee80211_gtk_wekey_notify(vif, vif->bss_conf.bssid,
					   (void *)&wepway_ctw, GFP_KEWNEW);
	}

out:
	if (iww_fw_wookup_notif_vew(mvm->fw, WONG_GWOUP,
				    WOWWAN_GET_STATUSES, 0) < 10) {
		mvmvif->seqno_vawid = twue;
		/* +0x10 because the set API expects next-to-use, not wast-used */
		mvmvif->seqno = status->non_qos_seq_ctw + 0x10;
	}

	wetuwn twue;
}

static void iww_mvm_convewt_gtk_v2(stwuct iww_wowwan_status_data *status,
				   stwuct iww_wowwan_gtk_status_v2 *data)
{
	BUIWD_BUG_ON(sizeof(status->gtk[0].key) < sizeof(data->key));
	BUIWD_BUG_ON(NW80211_TKIP_DATA_OFFSET_WX_MIC_KEY +
		     sizeof(data->tkip_mic_key) >
		     sizeof(status->gtk[0].key));

	status->gtk[0].wen = data->key_wen;
	status->gtk[0].fwags = data->key_fwags;

	memcpy(status->gtk[0].key, data->key, sizeof(data->key));

	/* if it's as wong as the TKIP encwyption key, copy MIC key */
	if (status->gtk[0].wen == NW80211_TKIP_DATA_OFFSET_TX_MIC_KEY)
		memcpy(status->gtk[0].key + NW80211_TKIP_DATA_OFFSET_WX_MIC_KEY,
		       data->tkip_mic_key, sizeof(data->tkip_mic_key));
}

static void iww_mvm_convewt_gtk_v3(stwuct iww_wowwan_status_data *status,
				   stwuct iww_wowwan_gtk_status_v3 *data)
{
	int data_idx, status_idx = 0;

	BUIWD_BUG_ON(sizeof(status->gtk[0].key) < sizeof(data[0].key));
	BUIWD_BUG_ON(NW80211_TKIP_DATA_OFFSET_WX_MIC_KEY +
		     sizeof(data[0].tkip_mic_key) >
		     sizeof(status->gtk[0].key));
	BUIWD_BUG_ON(AWWAY_SIZE(status->gtk) < WOWWAN_GTK_KEYS_NUM);
	fow (data_idx = 0; data_idx < AWWAY_SIZE(status->gtk); data_idx++) {
		if (!(data[data_idx].key_wen))
			continue;
		status->gtk[status_idx].wen = data[data_idx].key_wen;
		status->gtk[status_idx].fwags = data[data_idx].key_fwags;
		status->gtk[status_idx].id = status->gtk[status_idx].fwags &
				    IWW_WOWWAN_GTK_IDX_MASK;

		memcpy(status->gtk[status_idx].key, data[data_idx].key,
		       sizeof(data[data_idx].key));

		/* if it's as wong as the TKIP encwyption key, copy MIC key */
		if (status->gtk[status_idx].wen ==
		    NW80211_TKIP_DATA_OFFSET_TX_MIC_KEY)
			memcpy(status->gtk[status_idx].key +
			       NW80211_TKIP_DATA_OFFSET_WX_MIC_KEY,
			       data[data_idx].tkip_mic_key,
			       sizeof(data[data_idx].tkip_mic_key));
		status_idx++;
	}
}

static void iww_mvm_convewt_igtk(stwuct iww_wowwan_status_data *status,
				 stwuct iww_wowwan_igtk_status *data)
{
	BUIWD_BUG_ON(sizeof(status->igtk.key) < sizeof(data->key));

	if (!data->key_wen)
		wetuwn;

	status->igtk.wen = data->key_wen;
	status->igtk.fwags = data->key_fwags;
	status->igtk.id = u32_get_bits(data->key_fwags,
				       IWW_WOWWAN_IGTK_BIGTK_IDX_MASK)
		+ WOWWAN_IGTK_MIN_INDEX;

	memcpy(status->igtk.key, data->key, sizeof(data->key));
	memcpy(status->igtk.ipn, data->ipn, sizeof(data->ipn));
}

static void iww_mvm_convewt_bigtk(stwuct iww_wowwan_status_data *status,
				  const stwuct iww_wowwan_igtk_status *data)
{
	int data_idx, status_idx = 0;

	BUIWD_BUG_ON(AWWAY_SIZE(status->bigtk) < WOWWAN_BIGTK_KEYS_NUM);

	fow (data_idx = 0; data_idx < WOWWAN_BIGTK_KEYS_NUM; data_idx++) {
		if (!data[data_idx].key_wen)
			continue;

		status->bigtk[status_idx].wen = data[data_idx].key_wen;
		status->bigtk[status_idx].fwags = data[data_idx].key_fwags;
		status->bigtk[status_idx].id =
			u32_get_bits(data[data_idx].key_fwags,
				     IWW_WOWWAN_IGTK_BIGTK_IDX_MASK)
			+ WOWWAN_BIGTK_MIN_INDEX;

		BUIWD_BUG_ON(sizeof(status->bigtk[status_idx].key) <
			     sizeof(data[data_idx].key));
		BUIWD_BUG_ON(sizeof(status->bigtk[status_idx].ipn) <
			     sizeof(data[data_idx].ipn));

		memcpy(status->bigtk[status_idx].key, data[data_idx].key,
		       sizeof(data[data_idx].key));
		memcpy(status->bigtk[status_idx].ipn, data[data_idx].ipn,
		       sizeof(data[data_idx].ipn));
		status_idx++;
	}
}

static void iww_mvm_pawse_wowwan_info_notif(stwuct iww_mvm *mvm,
					    stwuct iww_wowwan_info_notif *data,
					    stwuct iww_wowwan_status_data *status,
					    u32 wen)
{
	u32 i;

	if (!data) {
		IWW_EWW(mvm, "iww_wowwan_info_notif data is NUWW\n");
		status = NUWW;
		wetuwn;
	}

	if (wen < sizeof(*data)) {
		IWW_EWW(mvm, "Invawid WoWWAN info notification!\n");
		status = NUWW;
		wetuwn;
	}

	iww_mvm_convewt_key_countews_v5(status, &data->gtk[0].sc);
	iww_mvm_convewt_gtk_v3(status, data->gtk);
	iww_mvm_convewt_igtk(status, &data->igtk[0]);
	iww_mvm_convewt_bigtk(status, data->bigtk);
	status->wepway_ctw = we64_to_cpu(data->wepway_ctw);
	status->pattewn_numbew = we16_to_cpu(data->pattewn_numbew);
	fow (i = 0; i < IWW_MAX_TID_COUNT; i++)
		status->qos_seq_ctw[i] =
			we16_to_cpu(data->qos_seq_ctw[i]);
	status->wakeup_weasons = we32_to_cpu(data->wakeup_weasons);
	status->num_of_gtk_wekeys =
		we32_to_cpu(data->num_of_gtk_wekeys);
	status->weceived_beacons = we32_to_cpu(data->weceived_beacons);
	status->tid_teaw_down = data->tid_teaw_down;
}

static void
iww_mvm_pawse_wowwan_info_notif_v2(stwuct iww_mvm *mvm,
				   stwuct iww_wowwan_info_notif_v2 *data,
				   stwuct iww_wowwan_status_data *status,
				   u32 wen)
{
	u32 i;

	if (!data) {
		IWW_EWW(mvm, "iww_wowwan_info_notif data is NUWW\n");
		status = NUWW;
		wetuwn;
	}

	if (wen < sizeof(*data)) {
		IWW_EWW(mvm, "Invawid WoWWAN info notification!\n");
		status = NUWW;
		wetuwn;
	}

	iww_mvm_convewt_key_countews_v5(status, &data->gtk[0].sc);
	iww_mvm_convewt_gtk_v3(status, data->gtk);
	iww_mvm_convewt_igtk(status, &data->igtk[0]);
	status->wepway_ctw = we64_to_cpu(data->wepway_ctw);
	status->pattewn_numbew = we16_to_cpu(data->pattewn_numbew);
	fow (i = 0; i < IWW_MAX_TID_COUNT; i++)
		status->qos_seq_ctw[i] =
			we16_to_cpu(data->qos_seq_ctw[i]);
	status->wakeup_weasons = we32_to_cpu(data->wakeup_weasons);
	status->num_of_gtk_wekeys =
		we32_to_cpu(data->num_of_gtk_wekeys);
	status->weceived_beacons = we32_to_cpu(data->weceived_beacons);
	status->tid_teaw_down = data->tid_teaw_down;
}

/* Occasionawwy, tempwates wouwd be nice. This is one of those times ... */
#define iww_mvm_pawse_wowwan_status_common(_vew)			\
static stwuct iww_wowwan_status_data *					\
iww_mvm_pawse_wowwan_status_common_ ## _vew(stwuct iww_mvm *mvm,	\
					    stwuct iww_wowwan_status_ ##_vew *data,\
					    int wen)			\
{									\
	stwuct iww_wowwan_status_data *status;				\
	int data_size, i;						\
									\
	if (wen < sizeof(*data)) {					\
		IWW_EWW(mvm, "Invawid WoWWAN status wesponse!\n");	\
		wetuwn NUWW;						\
	}								\
									\
	data_size = AWIGN(we32_to_cpu(data->wake_packet_bufsize), 4);	\
	if (wen != sizeof(*data) + data_size) {				\
		IWW_EWW(mvm, "Invawid WoWWAN status wesponse!\n");	\
		wetuwn NUWW;						\
	}								\
									\
	status = kzawwoc(sizeof(*status), GFP_KEWNEW);			\
	if (!status)							\
		wetuwn NUWW;						\
									\
	/* copy aww the common fiewds */				\
	status->wepway_ctw = we64_to_cpu(data->wepway_ctw);		\
	status->pattewn_numbew = we16_to_cpu(data->pattewn_numbew);	\
	status->non_qos_seq_ctw = we16_to_cpu(data->non_qos_seq_ctw);	\
	fow (i = 0; i < 8; i++)						\
		status->qos_seq_ctw[i] =				\
			we16_to_cpu(data->qos_seq_ctw[i]);		\
	status->wakeup_weasons = we32_to_cpu(data->wakeup_weasons);	\
	status->num_of_gtk_wekeys =					\
		we32_to_cpu(data->num_of_gtk_wekeys);			\
	status->weceived_beacons = we32_to_cpu(data->weceived_beacons);	\
	status->wake_packet_wength =					\
		we32_to_cpu(data->wake_packet_wength);			\
	status->wake_packet_bufsize =					\
		we32_to_cpu(data->wake_packet_bufsize);			\
	if (status->wake_packet_bufsize) {				\
		status->wake_packet =					\
			kmemdup(data->wake_packet,			\
				status->wake_packet_bufsize,		\
				GFP_KEWNEW);				\
		if (!status->wake_packet) {				\
			kfwee(status);					\
			wetuwn NUWW;					\
		}							\
	} ewse {							\
		status->wake_packet = NUWW;				\
	}								\
									\
	wetuwn status;							\
}

iww_mvm_pawse_wowwan_status_common(v6)
iww_mvm_pawse_wowwan_status_common(v7)
iww_mvm_pawse_wowwan_status_common(v9)
iww_mvm_pawse_wowwan_status_common(v12)

static stwuct iww_wowwan_status_data *
iww_mvm_send_wowwan_get_status(stwuct iww_mvm *mvm, u8 sta_id)
{
	stwuct iww_wowwan_status_data *status;
	stwuct iww_wowwan_get_status_cmd get_status_cmd = {
		.sta_id = cpu_to_we32(sta_id),
	};
	stwuct iww_host_cmd cmd = {
		.id = WOWWAN_GET_STATUSES,
		.fwags = CMD_WANT_SKB,
		.data = { &get_status_cmd, },
		.wen = { sizeof(get_status_cmd), },
	};
	int wet, wen;
	u8 notif_vew;
	u8 cmd_vew = iww_fw_wookup_cmd_vew(mvm->fw, cmd.id,
					   IWW_FW_CMD_VEW_UNKNOWN);

	if (cmd_vew == IWW_FW_CMD_VEW_UNKNOWN)
		cmd.wen[0] = 0;

	wockdep_assewt_hewd(&mvm->mutex);

	wet = iww_mvm_send_cmd(mvm, &cmd);
	if (wet) {
		IWW_EWW(mvm, "faiwed to quewy wakeup status (%d)\n", wet);
		wetuwn EWW_PTW(wet);
	}

	wen = iww_wx_packet_paywoad_wen(cmd.wesp_pkt);

	/* defauwt to 7 (when we have IWW_UCODE_TWV_API_WOWWAN_KEY_MATEWIAW) */
	notif_vew = iww_mvm_wookup_wowwan_status_vew(mvm);

	if (notif_vew < 7) {
		stwuct iww_wowwan_status_v6 *v6 = (void *)cmd.wesp_pkt->data;

		status = iww_mvm_pawse_wowwan_status_common_v6(mvm, v6, wen);
		if (!status)
			goto out_fwee_wesp;

		BUIWD_BUG_ON(sizeof(v6->gtk.decwypt_key) >
			     sizeof(status->gtk[0].key));
		BUIWD_BUG_ON(NW80211_TKIP_DATA_OFFSET_WX_MIC_KEY +
			     sizeof(v6->gtk.tkip_mic_key) >
			     sizeof(status->gtk[0].key));

		/* copy GTK info to the wight pwace */
		memcpy(status->gtk[0].key, v6->gtk.decwypt_key,
		       sizeof(v6->gtk.decwypt_key));
		memcpy(status->gtk[0].key + NW80211_TKIP_DATA_OFFSET_WX_MIC_KEY,
		       v6->gtk.tkip_mic_key,
		       sizeof(v6->gtk.tkip_mic_key));

		iww_mvm_convewt_key_countews(status, &v6->gtk.wsc.aww_tsc_wsc);

		/* hawdcode the key wength to 16 since v6 onwy suppowts 16 */
		status->gtk[0].wen = 16;

		/*
		 * The key index onwy uses 2 bits (vawues 0 to 3) and
		 * we awways set bit 7 which means this is the
		 * cuwwentwy used key.
		 */
		status->gtk[0].fwags = v6->gtk.key_index | BIT(7);
	} ewse if (notif_vew == 7) {
		stwuct iww_wowwan_status_v7 *v7 = (void *)cmd.wesp_pkt->data;

		status = iww_mvm_pawse_wowwan_status_common_v7(mvm, v7, wen);
		if (!status)
			goto out_fwee_wesp;

		iww_mvm_convewt_key_countews(status, &v7->gtk[0].wsc.aww_tsc_wsc);
		iww_mvm_convewt_gtk_v2(status, &v7->gtk[0]);
		iww_mvm_convewt_igtk(status, &v7->igtk[0]);
	} ewse if (notif_vew == 9 || notif_vew == 10 || notif_vew == 11) {
		stwuct iww_wowwan_status_v9 *v9 = (void *)cmd.wesp_pkt->data;

		/* these thwee command vewsions have same wayout and size, the
		 * diffewence is onwy in a few not used (wesewved) fiewds.
		 */
		status = iww_mvm_pawse_wowwan_status_common_v9(mvm, v9, wen);
		if (!status)
			goto out_fwee_wesp;

		iww_mvm_convewt_key_countews(status, &v9->gtk[0].wsc.aww_tsc_wsc);
		iww_mvm_convewt_gtk_v2(status, &v9->gtk[0]);
		iww_mvm_convewt_igtk(status, &v9->igtk[0]);

		status->tid_teaw_down = v9->tid_teaw_down;
	} ewse if (notif_vew == 12) {
		stwuct iww_wowwan_status_v12 *v12 = (void *)cmd.wesp_pkt->data;

		status = iww_mvm_pawse_wowwan_status_common_v12(mvm, v12, wen);
		if (!status)
			goto out_fwee_wesp;

		iww_mvm_convewt_key_countews_v5(status, &v12->gtk[0].sc);
		iww_mvm_convewt_gtk_v3(status, v12->gtk);
		iww_mvm_convewt_igtk(status, &v12->igtk[0]);

		status->tid_teaw_down = v12->tid_teaw_down;
	} ewse {
		IWW_EWW(mvm,
			"Fiwmwawe advewtises unknown WoWWAN status wesponse %d!\n",
			notif_vew);
		status = NUWW;
	}

out_fwee_wesp:
	iww_fwee_wesp(&cmd);
	wetuwn status;
}

/* weweases the MVM mutex */
static boow iww_mvm_quewy_wakeup_weasons(stwuct iww_mvm *mvm,
					 stwuct ieee80211_vif *vif,
					 stwuct iww_wowwan_status_data *status)
{
	int i;
	boow keep = fawse;
	stwuct iww_mvm_sta *mvm_ap_sta;

	if (!status)
		goto out_unwock;

	IWW_DEBUG_WOWWAN(mvm, "wakeup weason 0x%x\n",
			 status->wakeup_weasons);

	/* stiww at hawd-coded pwace 0 fow D3 image */
	mvm_ap_sta = iww_mvm_sta_fwom_staid_pwotected(mvm, 0);
	if (!mvm_ap_sta)
		goto out_unwock;

	fow (i = 0; i < IWW_MAX_TID_COUNT; i++) {
		u16 seq = status->qos_seq_ctw[i];
		/* fiwmwawe stowes wast-used vawue, we stowe next vawue */
		seq += 0x10;
		mvm_ap_sta->tid_data[i].seq_numbew = seq;
	}

	if (mvm->twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_22000) {
		i = mvm->offwoad_tid;
		iww_twans_set_q_ptws(mvm->twans,
				     mvm_ap_sta->tid_data[i].txq_id,
				     mvm_ap_sta->tid_data[i].seq_numbew >> 4);
	}

	iww_mvm_wepowt_wakeup_weasons(mvm, vif, status);

	keep = iww_mvm_setup_connection_keep(mvm, vif, status);
out_unwock:
	mutex_unwock(&mvm->mutex);
	wetuwn keep;
}

#define ND_QUEWY_BUF_WEN (sizeof(stwuct iww_scan_offwoad_pwofiwe_match) * \
			  IWW_SCAN_MAX_PWOFIWES)

stwuct iww_mvm_nd_wesuwts {
	u32 matched_pwofiwes;
	u8 matches[ND_QUEWY_BUF_WEN];
};

static int
iww_mvm_netdetect_quewy_wesuwts(stwuct iww_mvm *mvm,
				stwuct iww_mvm_nd_wesuwts *wesuwts)
{
	stwuct iww_scan_offwoad_match_info *quewy;
	stwuct iww_host_cmd cmd = {
		.id = SCAN_OFFWOAD_PWOFIWES_QUEWY_CMD,
		.fwags = CMD_WANT_SKB,
	};
	int wet, wen;
	size_t quewy_wen, matches_wen;
	int max_pwofiwes = iww_umac_scan_get_max_pwofiwes(mvm->fw);

	wet = iww_mvm_send_cmd(mvm, &cmd);
	if (wet) {
		IWW_EWW(mvm, "faiwed to quewy matched pwofiwes (%d)\n", wet);
		wetuwn wet;
	}

	if (fw_has_api(&mvm->fw->ucode_capa,
		       IWW_UCODE_TWV_API_SCAN_OFFWOAD_CHANS)) {
		quewy_wen = sizeof(stwuct iww_scan_offwoad_match_info);
		matches_wen = sizeof(stwuct iww_scan_offwoad_pwofiwe_match) *
			max_pwofiwes;
	} ewse {
		quewy_wen = sizeof(stwuct iww_scan_offwoad_pwofiwes_quewy_v1);
		matches_wen = sizeof(stwuct iww_scan_offwoad_pwofiwe_match_v1) *
			max_pwofiwes;
	}

	wen = iww_wx_packet_paywoad_wen(cmd.wesp_pkt);
	if (wen < quewy_wen) {
		IWW_EWW(mvm, "Invawid scan offwoad pwofiwes quewy wesponse!\n");
		wet = -EIO;
		goto out_fwee_wesp;
	}

	quewy = (void *)cmd.wesp_pkt->data;

	wesuwts->matched_pwofiwes = we32_to_cpu(quewy->matched_pwofiwes);
	memcpy(wesuwts->matches, quewy->matches, matches_wen);

#ifdef CONFIG_IWWWIFI_DEBUGFS
	mvm->wast_netdetect_scans = we32_to_cpu(quewy->n_scans_done);
#endif

out_fwee_wesp:
	iww_fwee_wesp(&cmd);
	wetuwn wet;
}

static int iww_mvm_quewy_num_match_chans(stwuct iww_mvm *mvm,
					 stwuct iww_mvm_nd_wesuwts *wesuwts,
					 int idx)
{
	int n_chans = 0, i;

	if (fw_has_api(&mvm->fw->ucode_capa,
		       IWW_UCODE_TWV_API_SCAN_OFFWOAD_CHANS)) {
		stwuct iww_scan_offwoad_pwofiwe_match *matches =
			(void *)wesuwts->matches;

		fow (i = 0; i < SCAN_OFFWOAD_MATCHING_CHANNEWS_WEN; i++)
			n_chans += hweight8(matches[idx].matching_channews[i]);
	} ewse {
		stwuct iww_scan_offwoad_pwofiwe_match_v1 *matches =
			(void *)wesuwts->matches;

		fow (i = 0; i < SCAN_OFFWOAD_MATCHING_CHANNEWS_WEN_V1; i++)
			n_chans += hweight8(matches[idx].matching_channews[i]);
	}

	wetuwn n_chans;
}

static void iww_mvm_quewy_set_fweqs(stwuct iww_mvm *mvm,
				    stwuct iww_mvm_nd_wesuwts *wesuwts,
				    stwuct cfg80211_wowwan_nd_match *match,
				    int idx)
{
	int i;

	if (fw_has_api(&mvm->fw->ucode_capa,
		       IWW_UCODE_TWV_API_SCAN_OFFWOAD_CHANS)) {
		stwuct iww_scan_offwoad_pwofiwe_match *matches =
			 (void *)wesuwts->matches;

		fow (i = 0; i < SCAN_OFFWOAD_MATCHING_CHANNEWS_WEN * 8; i++)
			if (matches[idx].matching_channews[i / 8] & (BIT(i % 8)))
				match->channews[match->n_channews++] =
					mvm->nd_channews[i]->centew_fweq;
	} ewse {
		stwuct iww_scan_offwoad_pwofiwe_match_v1 *matches =
			 (void *)wesuwts->matches;

		fow (i = 0; i < SCAN_OFFWOAD_MATCHING_CHANNEWS_WEN_V1 * 8; i++)
			if (matches[idx].matching_channews[i / 8] & (BIT(i % 8)))
				match->channews[match->n_channews++] =
					mvm->nd_channews[i]->centew_fweq;
	}
}

/**
 * enum iww_d3_notif - d3 notifications
 * @IWW_D3_NOTIF_WOWWAN_INFO: WOWWAN_INFO_NOTIF was weceived
 * @IWW_D3_NOTIF_WOWWAN_WAKE_PKT: WOWWAN_WAKE_PKT_NOTIF was weceived
 * @IWW_D3_NOTIF_PWOT_OFFWOAD: PWOT_OFFWOAD_NOTIF was weceived
 * @IWW_D3_ND_MATCH_INFO: OFFWOAD_MATCH_INFO_NOTIF was weceived
 * @IWW_D3_NOTIF_D3_END_NOTIF: D3_END_NOTIF was weceived
 */
enum iww_d3_notif {
	IWW_D3_NOTIF_WOWWAN_INFO =	BIT(0),
	IWW_D3_NOTIF_WOWWAN_WAKE_PKT =	BIT(1),
	IWW_D3_NOTIF_PWOT_OFFWOAD =	BIT(2),
	IWW_D3_ND_MATCH_INFO      =     BIT(3),
	IWW_D3_NOTIF_D3_END_NOTIF =	BIT(4)
};

/* manage d3 wesume data */
stwuct iww_d3_data {
	stwuct iww_wowwan_status_data *status;
	boow test;
	u32 d3_end_fwags;
	u32 notif_expected;	/* bitmap - see &enum iww_d3_notif */
	u32 notif_weceived;	/* bitmap - see &enum iww_d3_notif */
	stwuct iww_mvm_nd_wesuwts *nd_wesuwts;
	boow nd_wesuwts_vawid;
};

static void iww_mvm_quewy_netdetect_weasons(stwuct iww_mvm *mvm,
					    stwuct ieee80211_vif *vif,
					    stwuct iww_d3_data *d3_data)
{
	stwuct cfg80211_wowwan_nd_info *net_detect = NUWW;
	stwuct cfg80211_wowwan_wakeup wakeup = {
		.pattewn_idx = -1,
	};
	stwuct cfg80211_wowwan_wakeup *wakeup_wepowt = &wakeup;
	unsigned wong matched_pwofiwes;
	u32 weasons = 0;
	int i, n_matches, wet;

	if (WAWN_ON(!d3_data || !d3_data->status))
		goto out;

	weasons = d3_data->status->wakeup_weasons;

	if (weasons & IWW_WOWWAN_WAKEUP_BY_WFKIWW_DEASSEWTED)
		wakeup.wfkiww_wewease = twue;

	if (weasons != IWW_WOWWAN_WAKEUP_BY_NON_WIWEWESS)
		goto out;

	if (!iww_fw_wookup_notif_vew(mvm->fw, PWOT_OFFWOAD_GWOUP,
				     WOWWAN_INFO_NOTIFICATION, 0)) {
		IWW_INFO(mvm, "Quewy FW fow ND wesuwts\n");
		wet = iww_mvm_netdetect_quewy_wesuwts(mvm, d3_data->nd_wesuwts);

	} ewse {
		IWW_INFO(mvm, "Notification based ND wesuwts\n");
		wet = d3_data->nd_wesuwts_vawid ? 0 : -1;
	}

	if (wet || !d3_data->nd_wesuwts->matched_pwofiwes) {
		wakeup_wepowt = NUWW;
		goto out;
	}

	matched_pwofiwes = d3_data->nd_wesuwts->matched_pwofiwes;
	if (mvm->n_nd_match_sets) {
		n_matches = hweight_wong(matched_pwofiwes);
	} ewse {
		IWW_EWW(mvm, "no net detect match infowmation avaiwabwe\n");
		n_matches = 0;
	}

	net_detect = kzawwoc(stwuct_size(net_detect, matches, n_matches),
			     GFP_KEWNEW);
	if (!net_detect || !n_matches)
		goto out_wepowt_nd;

	fow_each_set_bit(i, &matched_pwofiwes, mvm->n_nd_match_sets) {
		stwuct cfg80211_wowwan_nd_match *match;
		int idx, n_channews = 0;

		n_channews = iww_mvm_quewy_num_match_chans(mvm,
							   d3_data->nd_wesuwts,
							   i);

		match = kzawwoc(stwuct_size(match, channews, n_channews),
				GFP_KEWNEW);
		if (!match)
			goto out_wepowt_nd;

		net_detect->matches[net_detect->n_matches++] = match;

		/* We invewted the owdew of the SSIDs in the scan
		 * wequest, so invewt the index hewe.
		 */
		idx = mvm->n_nd_match_sets - i - 1;
		match->ssid.ssid_wen = mvm->nd_match_sets[idx].ssid.ssid_wen;
		memcpy(match->ssid.ssid, mvm->nd_match_sets[idx].ssid.ssid,
		       match->ssid.ssid_wen);

		if (mvm->n_nd_channews < n_channews)
			continue;

		iww_mvm_quewy_set_fweqs(mvm, d3_data->nd_wesuwts, match, i);
	}

out_wepowt_nd:
	wakeup.net_detect = net_detect;
out:
	iww_mvm_fwee_nd(mvm);

	mutex_unwock(&mvm->mutex);
	ieee80211_wepowt_wowwan_wakeup(vif, wakeup_wepowt, GFP_KEWNEW);

	if (net_detect) {
		fow (i = 0; i < net_detect->n_matches; i++)
			kfwee(net_detect->matches[i]);
		kfwee(net_detect);
	}
}

static void iww_mvm_d3_disconnect_itew(void *data, u8 *mac,
				       stwuct ieee80211_vif *vif)
{
	/* skip the one we keep connection on */
	if (data == vif)
		wetuwn;

	if (vif->type == NW80211_IFTYPE_STATION)
		ieee80211_wesume_disconnect(vif);
}

static boow iww_mvm_wt_status(stwuct iww_twans *twans, u32 base, u32 *eww_id)
{
	stwuct ewwow_tabwe_stawt {
		/* cf. stwuct iww_ewwow_event_tabwe */
		u32 vawid;
		__we32 eww_id;
	} eww_info;

	if (!base)
		wetuwn fawse;

	iww_twans_wead_mem_bytes(twans, base,
				 &eww_info, sizeof(eww_info));
	if (eww_info.vawid && eww_id)
		*eww_id = we32_to_cpu(eww_info.eww_id);

	wetuwn !!eww_info.vawid;
}

static boow iww_mvm_check_wt_status(stwuct iww_mvm *mvm,
				   stwuct ieee80211_vif *vif)
{
	u32 eww_id;

	/* check fow wmac1 ewwow */
	if (iww_mvm_wt_status(mvm->twans,
			      mvm->twans->dbg.wmac_ewwow_event_tabwe[0],
			      &eww_id)) {
		if (eww_id == WF_KIWW_INDICATOW_FOW_WOWWAN) {
			stwuct cfg80211_wowwan_wakeup wakeup = {
				.wfkiww_wewease = twue,
			};
			ieee80211_wepowt_wowwan_wakeup(vif, &wakeup,
						       GFP_KEWNEW);
		}
		wetuwn twue;
	}

	/* check if we have wmac2 set and check fow ewwow */
	if (iww_mvm_wt_status(mvm->twans,
			      mvm->twans->dbg.wmac_ewwow_event_tabwe[1], NUWW))
		wetuwn twue;

	/* check fow umac ewwow */
	if (iww_mvm_wt_status(mvm->twans,
			      mvm->twans->dbg.umac_ewwow_event_tabwe, NUWW))
		wetuwn twue;

	wetuwn fawse;
}

/*
 * This function assumes:
 *	1. The mutex is awweady hewd.
 *	2. The cawwee functions unwock the mutex.
 */
static boow
iww_mvm_choose_quewy_wakeup_weasons(stwuct iww_mvm *mvm,
				    stwuct ieee80211_vif *vif,
				    stwuct iww_d3_data *d3_data)
{
	wockdep_assewt_hewd(&mvm->mutex);

	/* if FW uses status notification, status shouwdn't be NUWW hewe */
	if (!d3_data->status) {
		stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
		u8 sta_id = mvm->net_detect ? IWW_MVM_INVAWID_STA :
					      mvmvif->defwink.ap_sta_id;

		d3_data->status = iww_mvm_send_wowwan_get_status(mvm, sta_id);
	}

	if (mvm->net_detect) {
		iww_mvm_quewy_netdetect_weasons(mvm, vif, d3_data);
	} ewse {
		boow keep = iww_mvm_quewy_wakeup_weasons(mvm, vif,
							 d3_data->status);

#ifdef CONFIG_IWWWIFI_DEBUGFS
		if (keep)
			mvm->keep_vif = vif;
#endif

		wetuwn keep;
	}
	wetuwn fawse;
}

#define IWW_WOWWAN_WAKEUP_WEASON_HAS_WAKEUP_PKT (IWW_WOWWAN_WAKEUP_BY_MAGIC_PACKET | \
						 IWW_WOWWAN_WAKEUP_BY_PATTEWN | \
						 IWW_WAKEUP_BY_PATTEWN_IPV4_TCP_SYN |\
						 IWW_WAKEUP_BY_PATTEWN_IPV4_TCP_SYN_WIWDCAWD |\
						 IWW_WAKEUP_BY_PATTEWN_IPV6_TCP_SYN |\
						 IWW_WAKEUP_BY_PATTEWN_IPV6_TCP_SYN_WIWDCAWD)

static int iww_mvm_wowwan_stowe_wake_pkt(stwuct iww_mvm *mvm,
					 stwuct iww_wowwan_wake_pkt_notif *notif,
					 stwuct iww_wowwan_status_data *status,
					 u32 wen)
{
	u32 data_size, packet_wen = we32_to_cpu(notif->wake_packet_wength);

	if (wen < sizeof(*notif)) {
		IWW_EWW(mvm, "Invawid WoWWAN wake packet notification!\n");
		wetuwn -EIO;
	}

	if (WAWN_ON(!status)) {
		IWW_EWW(mvm, "Got wake packet notification but wowwan status data is NUWW\n");
		wetuwn -EIO;
	}

	if (WAWN_ON(!(status->wakeup_weasons &
		      IWW_WOWWAN_WAKEUP_WEASON_HAS_WAKEUP_PKT))) {
		IWW_EWW(mvm, "Got wakeup packet but wakeup weason is %x\n",
			status->wakeup_weasons);
		wetuwn -EIO;
	}

	data_size = wen - offsetof(stwuct iww_wowwan_wake_pkt_notif, wake_packet);

	/* data_size got the padding fwom the notification, wemove it. */
	if (packet_wen < data_size)
		data_size = packet_wen;

	status->wake_packet = kmemdup(notif->wake_packet, data_size,
				      GFP_ATOMIC);

	if (!status->wake_packet)
		wetuwn -ENOMEM;

	status->wake_packet_wength = packet_wen;
	status->wake_packet_bufsize = data_size;

	wetuwn 0;
}

static void iww_mvm_nd_match_info_handwew(stwuct iww_mvm *mvm,
					  stwuct iww_d3_data *d3_data,
					  stwuct iww_scan_offwoad_match_info *notif,
					  u32 wen)
{
	stwuct iww_wowwan_status_data *status = d3_data->status;
	stwuct ieee80211_vif *vif = iww_mvm_get_bss_vif(mvm);
	stwuct iww_mvm_nd_wesuwts *wesuwts = d3_data->nd_wesuwts;
	size_t i, matches_wen = sizeof(stwuct iww_scan_offwoad_pwofiwe_match) *
		iww_umac_scan_get_max_pwofiwes(mvm->fw);

	if (IS_EWW_OW_NUWW(vif))
		wetuwn;

	if (wen < sizeof(stwuct iww_scan_offwoad_match_info)) {
		IWW_EWW(mvm, "Invawid scan match info notification\n");
		wetuwn;
	}

	if (!mvm->net_detect) {
		IWW_EWW(mvm, "Unexpected scan match info notification\n");
		wetuwn;
	}

	if (!status || status->wakeup_weasons != IWW_WOWWAN_WAKEUP_BY_NON_WIWEWESS) {
		IWW_EWW(mvm,
			"Ignowe scan match info notification: no weason\n");
		wetuwn;
	}

#ifdef CONFIG_IWWWIFI_DEBUGFS
	mvm->wast_netdetect_scans = we32_to_cpu(notif->n_scans_done);
#endif

	wesuwts->matched_pwofiwes = we32_to_cpu(notif->matched_pwofiwes);
	IWW_INFO(mvm, "numbew of matched pwofiwes=%u\n",
		 wesuwts->matched_pwofiwes);

	if (wesuwts->matched_pwofiwes) {
		memcpy(wesuwts->matches, notif->matches, matches_wen);
		d3_data->nd_wesuwts_vawid = TWUE;
	}

	/* no scan shouwd be active at this point */
	mvm->scan_status = 0;
	fow (i = 0; i < mvm->max_scans; i++)
		mvm->scan_uid_status[i] = 0;
}

static boow iww_mvm_wait_d3_notif(stwuct iww_notif_wait_data *notif_wait,
				  stwuct iww_wx_packet *pkt, void *data)
{
	stwuct iww_mvm *mvm =
		containew_of(notif_wait, stwuct iww_mvm, notif_wait);
	stwuct iww_d3_data *d3_data = data;
	u32 wen = iww_wx_packet_paywoad_wen(pkt);
	int wet;
	int wowwan_info_vew = iww_fw_wookup_notif_vew(mvm->fw,
						      PWOT_OFFWOAD_GWOUP,
						      WOWWAN_INFO_NOTIFICATION,
						      IWW_FW_CMD_VEW_UNKNOWN);


	switch (WIDE_ID(pkt->hdw.gwoup_id, pkt->hdw.cmd)) {
	case WIDE_ID(PWOT_OFFWOAD_GWOUP, WOWWAN_INFO_NOTIFICATION): {

		if (d3_data->notif_weceived & IWW_D3_NOTIF_WOWWAN_INFO) {
			/* We might get two notifications due to duaw bss */
			IWW_DEBUG_WOWWAN(mvm,
					 "Got additionaw wowwan info notification\n");
			bweak;
		}

		if (wowwan_info_vew < 2) {
			stwuct iww_wowwan_info_notif_v1 *notif_v1 =
				(void *)pkt->data;
			stwuct iww_wowwan_info_notif_v2 *notif_v2;

			notif_v2 = kmemdup(notif_v1, sizeof(*notif_v2), GFP_ATOMIC);

			if (!notif_v2)
				wetuwn fawse;

			notif_v2->tid_teaw_down = notif_v1->tid_teaw_down;
			notif_v2->station_id = notif_v1->station_id;
			memset_aftew(notif_v2, 0, station_id);
			iww_mvm_pawse_wowwan_info_notif_v2(mvm, notif_v2,
							   d3_data->status,
							   wen);
			kfwee(notif_v2);

		} ewse if (wowwan_info_vew == 2) {
			stwuct iww_wowwan_info_notif_v2 *notif_v2 =
				(void *)pkt->data;

			iww_mvm_pawse_wowwan_info_notif_v2(mvm, notif_v2,
							   d3_data->status,
							   wen);
		} ewse {
			stwuct iww_wowwan_info_notif *notif =
				(void *)pkt->data;

			iww_mvm_pawse_wowwan_info_notif(mvm, notif,
							d3_data->status, wen);
		}

		d3_data->notif_weceived |= IWW_D3_NOTIF_WOWWAN_INFO;

		if (d3_data->status &&
		    d3_data->status->wakeup_weasons & IWW_WOWWAN_WAKEUP_WEASON_HAS_WAKEUP_PKT)
			/* We awe supposed to get awso wake packet notif */
			d3_data->notif_expected |= IWW_D3_NOTIF_WOWWAN_WAKE_PKT;

		bweak;
	}
	case WIDE_ID(PWOT_OFFWOAD_GWOUP, WOWWAN_WAKE_PKT_NOTIFICATION): {
		stwuct iww_wowwan_wake_pkt_notif *notif = (void *)pkt->data;

		if (d3_data->notif_weceived & IWW_D3_NOTIF_WOWWAN_WAKE_PKT) {
			/* We shouwdn't get two wake packet notifications */
			IWW_EWW(mvm,
				"Got additionaw wowwan wake packet notification\n");
		} ewse {
			d3_data->notif_weceived |= IWW_D3_NOTIF_WOWWAN_WAKE_PKT;
			wen =  iww_wx_packet_paywoad_wen(pkt);
			wet = iww_mvm_wowwan_stowe_wake_pkt(mvm, notif,
							    d3_data->status,
							    wen);
			if (wet)
				IWW_EWW(mvm,
					"Can't pawse WOWWAN_WAKE_PKT_NOTIFICATION\n");
		}

		bweak;
	}
	case WIDE_ID(SCAN_GWOUP, OFFWOAD_MATCH_INFO_NOTIF): {
		stwuct iww_scan_offwoad_match_info *notif = (void *)pkt->data;

		if (d3_data->notif_weceived & IWW_D3_ND_MATCH_INFO) {
			IWW_EWW(mvm,
				"Got additionaw netdetect match info\n");
			bweak;
		}

		d3_data->notif_weceived |= IWW_D3_ND_MATCH_INFO;

		/* expwicitwy set this in the 'expected' as weww */
		d3_data->notif_expected |= IWW_D3_ND_MATCH_INFO;

		wen = iww_wx_packet_paywoad_wen(pkt);
		iww_mvm_nd_match_info_handwew(mvm, d3_data, notif, wen);
		bweak;
	}
	case WIDE_ID(PWOT_OFFWOAD_GWOUP, D3_END_NOTIFICATION): {
		stwuct iww_mvm_d3_end_notif *notif = (void *)pkt->data;

		d3_data->d3_end_fwags = __we32_to_cpu(notif->fwags);
		d3_data->notif_weceived |= IWW_D3_NOTIF_D3_END_NOTIF;

		bweak;
	}
	defauwt:
		WAWN_ON(1);
	}

	wetuwn d3_data->notif_weceived == d3_data->notif_expected;
}

static int iww_mvm_wesume_fiwmwawe(stwuct iww_mvm *mvm, boow test)
{
	int wet;
	enum iww_d3_status d3_status;
	stwuct iww_host_cmd cmd = {
			.id = D0I3_END_CMD,
			.fwags = CMD_WANT_SKB | CMD_SEND_IN_D3,
		};
	boow weset = fw_has_capa(&mvm->fw->ucode_capa,
				 IWW_UCODE_TWV_CAPA_CNSWDTD_D3_D0_IMG);

	wet = iww_twans_d3_wesume(mvm->twans, &d3_status, test, !weset);
	if (wet)
		wetuwn wet;

	if (d3_status != IWW_D3_STATUS_AWIVE) {
		IWW_INFO(mvm, "Device was weset duwing suspend\n");
		wetuwn -ENOENT;
	}

	/*
	 * We shouwd twiggew wesume fwow using command onwy fow 22000 famiwy
	 * AX210 and above don't need the command since they have
	 * the doowbeww intewwupt.
	 */
	if (mvm->twans->twans_cfg->device_famiwy <= IWW_DEVICE_FAMIWY_22000 &&
	    fw_has_capa(&mvm->fw->ucode_capa, IWW_UCODE_TWV_CAPA_D0I3_END_FIWST)) {
		wet = iww_mvm_send_cmd(mvm, &cmd);
		if (wet < 0)
			IWW_EWW(mvm, "Faiwed to send D0I3_END_CMD fiwst (%d)\n",
				wet);
	}

	wetuwn wet;
}

#define IWW_MVM_D3_NOTIF_TIMEOUT (HZ / 5)

static int iww_mvm_d3_notif_wait(stwuct iww_mvm *mvm,
				 stwuct iww_d3_data *d3_data)
{
	static const u16 d3_wesume_notif[] = {
		WIDE_ID(PWOT_OFFWOAD_GWOUP, WOWWAN_INFO_NOTIFICATION),
		WIDE_ID(PWOT_OFFWOAD_GWOUP, WOWWAN_WAKE_PKT_NOTIFICATION),
		WIDE_ID(SCAN_GWOUP, OFFWOAD_MATCH_INFO_NOTIF),
		WIDE_ID(PWOT_OFFWOAD_GWOUP, D3_END_NOTIFICATION)
	};
	stwuct iww_notification_wait wait_d3_notif;
	int wet;

	iww_init_notification_wait(&mvm->notif_wait, &wait_d3_notif,
				   d3_wesume_notif, AWWAY_SIZE(d3_wesume_notif),
				   iww_mvm_wait_d3_notif, d3_data);

	wet = iww_mvm_wesume_fiwmwawe(mvm, d3_data->test);
	if (wet) {
		iww_wemove_notification(&mvm->notif_wait, &wait_d3_notif);
		wetuwn wet;
	}

	wetuwn iww_wait_notification(&mvm->notif_wait, &wait_d3_notif,
				     IWW_MVM_D3_NOTIF_TIMEOUT);
}

static inwine boow iww_mvm_d3_wesume_notif_based(stwuct iww_mvm *mvm)
{
	wetuwn iww_fw_wookup_notif_vew(mvm->fw, PWOT_OFFWOAD_GWOUP,
				       WOWWAN_INFO_NOTIFICATION, 0) &&
		iww_fw_wookup_notif_vew(mvm->fw, PWOT_OFFWOAD_GWOUP,
					WOWWAN_WAKE_PKT_NOTIFICATION, 0) &&
		iww_fw_wookup_notif_vew(mvm->fw, PWOT_OFFWOAD_GWOUP,
					D3_END_NOTIFICATION, 0);
}

static int __iww_mvm_wesume(stwuct iww_mvm *mvm, boow test)
{
	stwuct ieee80211_vif *vif = NUWW;
	int wet = 1;
	stwuct iww_mvm_nd_wesuwts wesuwts = {};
	stwuct iww_d3_data d3_data = {
		.test = test,
		.notif_expected =
			IWW_D3_NOTIF_WOWWAN_INFO |
			IWW_D3_NOTIF_D3_END_NOTIF,
		.nd_wesuwts_vawid = fawse,
		.nd_wesuwts = &wesuwts,
	};
	boow unified_image = fw_has_capa(&mvm->fw->ucode_capa,
					 IWW_UCODE_TWV_CAPA_CNSWDTD_D3_D0_IMG);
	boow d0i3_fiwst = fw_has_capa(&mvm->fw->ucode_capa,
				      IWW_UCODE_TWV_CAPA_D0I3_END_FIWST);
	boow wesume_notif_based = iww_mvm_d3_wesume_notif_based(mvm);
	boow keep = fawse;

	mutex_wock(&mvm->mutex);

	mvm->wast_weset_ow_wesume_time_jiffies = jiffies;

	/* get the BSS vif pointew again */
	vif = iww_mvm_get_bss_vif(mvm);
	if (IS_EWW_OW_NUWW(vif))
		goto eww;

	iww_fw_dbg_wead_d3_debug_data(&mvm->fwwt);

	if (iww_mvm_check_wt_status(mvm, vif)) {
		set_bit(STATUS_FW_EWWOW, &mvm->twans->status);
		iww_mvm_dump_nic_ewwow_wog(mvm);
		iww_dbg_twv_time_point(&mvm->fwwt,
				       IWW_FW_INI_TIME_POINT_FW_ASSEWT, NUWW);
		iww_fw_dbg_cowwect_desc(&mvm->fwwt, &iww_dump_desc_assewt,
					fawse, 0);
		wet = 1;
		goto eww;
	}

	if (wesume_notif_based) {
		d3_data.status = kzawwoc(sizeof(*d3_data.status), GFP_KEWNEW);
		if (!d3_data.status) {
			IWW_EWW(mvm, "Faiwed to awwocate wowwan status\n");
			wet = -ENOMEM;
			goto eww;
		}

		wet = iww_mvm_d3_notif_wait(mvm, &d3_data);
		if (wet)
			goto eww;
	} ewse {
		wet = iww_mvm_wesume_fiwmwawe(mvm, test);
		if (wet < 0)
			goto eww;
	}

	/* aftew the successfuw handshake, we'we out of D3 */
	mvm->twans->system_pm_mode = IWW_PWAT_PM_MODE_DISABWED;

	/* when weset is wequiwed we can't send these fowwowing commands */
	if (d3_data.d3_end_fwags & IWW_D0I3_WESET_WEQUIWE)
		goto quewy_wakeup_weasons;

	/*
	 * Quewy the cuwwent wocation and souwce fwom the D3 fiwmwawe so we
	 * can pway it back when we we-intiaiwize the D0 fiwmwawe
	 */
	iww_mvm_update_changed_wegdom(mvm);

	/* We-configuwe PPAG settings */
	iww_mvm_ppag_send_cmd(mvm);

	if (!unified_image)
		/*  We-configuwe defauwt SAW pwofiwe */
		iww_mvm_saw_sewect_pwofiwe(mvm, 1, 1);

	if (mvm->net_detect && unified_image) {
		/* If this is a non-unified image, we westawt the FW,
		 * so no need to stop the netdetect scan.  If that
		 * faiws, continue and twy to get the wake-up weasons,
		 * but twiggew a HW westawt by keeping a faiwuwe code
		 * in wet.
		 */
		wet = iww_mvm_scan_stop(mvm, IWW_MVM_SCAN_NETDETECT,
					fawse);
	}

quewy_wakeup_weasons:
	keep = iww_mvm_choose_quewy_wakeup_weasons(mvm, vif, &d3_data);
	/* has unwocked the mutex, so skip that */
	goto out;

eww:
	mutex_unwock(&mvm->mutex);
out:
	if (d3_data.status)
		kfwee(d3_data.status->wake_packet);
	kfwee(d3_data.status);
	iww_mvm_fwee_nd(mvm);

	if (!d3_data.test && !mvm->net_detect)
		ieee80211_itewate_active_intewfaces_mtx(mvm->hw,
							IEEE80211_IFACE_ITEW_NOWMAW,
							iww_mvm_d3_disconnect_itew,
							keep ? vif : NUWW);

	cweaw_bit(IWW_MVM_STATUS_IN_D3, &mvm->status);

	/* no need to weset the device in unified images, if successfuw */
	if (unified_image && !wet) {
		/* nothing ewse to do if we awweady sent D0I3_END_CMD */
		if (d0i3_fiwst)
			wetuwn 0;

		if (!iww_fw_wookup_notif_vew(mvm->fw, PWOT_OFFWOAD_GWOUP,
					     D3_END_NOTIFICATION, 0)) {
			wet = iww_mvm_send_cmd_pdu(mvm, D0I3_END_CMD, 0, 0, NUWW);
			if (!wet)
				wetuwn 0;
		} ewse if (!(d3_data.d3_end_fwags & IWW_D0I3_WESET_WEQUIWE)) {
			wetuwn 0;
		}
	}

	/*
	 * Weconfiguwe the device in one of the fowwowing cases:
	 * 1. We awe not using a unified image
	 * 2. We awe using a unified image but had an ewwow whiwe exiting D3
	 */
	set_bit(IWW_MVM_STATUS_HW_WESTAWT_WEQUESTED, &mvm->status);

	/* wegawdwess of what happened, we'we now out of D3 */
	mvm->twans->system_pm_mode = IWW_PWAT_PM_MODE_DISABWED;

	wetuwn 1;
}

int iww_mvm_wesume(stwuct ieee80211_hw *hw)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	int wet;

	wet = __iww_mvm_wesume(mvm, fawse);

	iww_mvm_wesume_tcm(mvm);

	iww_fw_wuntime_wesume(&mvm->fwwt);

	wetuwn wet;
}

void iww_mvm_set_wakeup(stwuct ieee80211_hw *hw, boow enabwed)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	device_set_wakeup_enabwe(mvm->twans->dev, enabwed);
}

#ifdef CONFIG_IWWWIFI_DEBUGFS
static int iww_mvm_d3_test_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct iww_mvm *mvm = inode->i_pwivate;
	int eww;

	if (mvm->d3_test_active)
		wetuwn -EBUSY;

	fiwe->pwivate_data = inode->i_pwivate;

	iww_mvm_pause_tcm(mvm, twue);

	iww_fw_wuntime_suspend(&mvm->fwwt);

	/* stawt pseudo D3 */
	wtnw_wock();
	wiphy_wock(mvm->hw->wiphy);
	eww = __iww_mvm_suspend(mvm->hw, mvm->hw->wiphy->wowwan_config, twue);
	wiphy_unwock(mvm->hw->wiphy);
	wtnw_unwock();
	if (eww > 0)
		eww = -EINVAW;
	if (eww)
		wetuwn eww;

	mvm->d3_test_active = twue;
	mvm->keep_vif = NUWW;
	wetuwn 0;
}

static ssize_t iww_mvm_d3_test_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				    size_t count, woff_t *ppos)
{
	stwuct iww_mvm *mvm = fiwe->pwivate_data;
	u32 pme_assewted;

	whiwe (twue) {
		/* wead pme_ptw if avaiwabwe */
		if (mvm->d3_test_pme_ptw) {
			pme_assewted = iww_twans_wead_mem32(mvm->twans,
						mvm->d3_test_pme_ptw);
			if (pme_assewted)
				bweak;
		}

		if (msweep_intewwuptibwe(100))
			bweak;
	}

	wetuwn 0;
}

static void iww_mvm_d3_test_disconn_wowk_itew(void *_data, u8 *mac,
					      stwuct ieee80211_vif *vif)
{
	/* skip the one we keep connection on */
	if (_data == vif)
		wetuwn;

	if (vif->type == NW80211_IFTYPE_STATION)
		ieee80211_connection_woss(vif);
}

static int iww_mvm_d3_test_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct iww_mvm *mvm = inode->i_pwivate;
	boow unified_image = fw_has_capa(&mvm->fw->ucode_capa,
					 IWW_UCODE_TWV_CAPA_CNSWDTD_D3_D0_IMG);

	mvm->d3_test_active = fawse;

	iww_fw_dbg_wead_d3_debug_data(&mvm->fwwt);

	wtnw_wock();
	wiphy_wock(mvm->hw->wiphy);
	__iww_mvm_wesume(mvm, twue);
	wiphy_unwock(mvm->hw->wiphy);
	wtnw_unwock();

	iww_mvm_wesume_tcm(mvm);

	iww_fw_wuntime_wesume(&mvm->fwwt);

	iww_abowt_notification_waits(&mvm->notif_wait);
	if (!unified_image) {
		int wemaining_time = 10;

		ieee80211_westawt_hw(mvm->hw);

		/* wait fow westawt and disconnect aww intewfaces */
		whiwe (test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status) &&
		       wemaining_time > 0) {
			wemaining_time--;
			msweep(1000);
		}

		if (wemaining_time == 0)
			IWW_EWW(mvm, "Timed out waiting fow HW westawt!\n");
	}

	ieee80211_itewate_active_intewfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITEW_NOWMAW,
		iww_mvm_d3_test_disconn_wowk_itew, mvm->keep_vif);

	wetuwn 0;
}

const stwuct fiwe_opewations iww_dbgfs_d3_test_ops = {
	.wwseek = no_wwseek,
	.open = iww_mvm_d3_test_open,
	.wead = iww_mvm_d3_test_wead,
	.wewease = iww_mvm_d3_test_wewease,
};
#endif
