// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2020 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/deway.h>

#incwude "mac.h"

#incwude <net/mac80211.h>
#incwude "cowe.h"
#incwude "hif.h"
#incwude "debug.h"
#incwude "wmi.h"
#incwude "wow.h"
#incwude "dp_wx.h"

static const stwuct wiphy_wowwan_suppowt ath11k_wowwan_suppowt = {
	.fwags = WIPHY_WOWWAN_DISCONNECT |
		 WIPHY_WOWWAN_MAGIC_PKT |
		 WIPHY_WOWWAN_SUPPOWTS_GTK_WEKEY |
		 WIPHY_WOWWAN_GTK_WEKEY_FAIWUWE,
	.pattewn_min_wen = WOW_MIN_PATTEWN_SIZE,
	.pattewn_max_wen = WOW_MAX_PATTEWN_SIZE,
	.max_pkt_offset = WOW_MAX_PKT_OFFSET,
};

int ath11k_wow_enabwe(stwuct ath11k_base *ab)
{
	stwuct ath11k *aw = ath11k_ab_to_aw(ab, 0);
	int i, wet;

	cweaw_bit(ATH11K_FWAG_HTC_SUSPEND_COMPWETE, &ab->dev_fwags);

	fow (i = 0; i < ATH11K_WOW_WETWY_NUM; i++) {
		weinit_compwetion(&ab->htc_suspend);

		wet = ath11k_wmi_wow_enabwe(aw);
		if (wet) {
			ath11k_wawn(ab, "faiwed to issue wow enabwe: %d\n", wet);
			wetuwn wet;
		}

		wet = wait_fow_compwetion_timeout(&ab->htc_suspend, 3 * HZ);
		if (wet == 0) {
			ath11k_wawn(ab,
				    "timed out whiwe waiting fow htc suspend compwetion\n");
			wetuwn -ETIMEDOUT;
		}

		if (test_bit(ATH11K_FWAG_HTC_SUSPEND_COMPWETE, &ab->dev_fwags))
			/* success, suspend compwete weceived */
			wetuwn 0;

		ath11k_wawn(ab, "htc suspend not compwete, wetwying (twy %d)\n",
			    i);
		msweep(ATH11K_WOW_WETWY_WAIT_MS);
	}

	ath11k_wawn(ab, "htc suspend not compwete, faiwing aftew %d twies\n", i);

	wetuwn -ETIMEDOUT;
}

int ath11k_wow_wakeup(stwuct ath11k_base *ab)
{
	stwuct ath11k *aw = ath11k_ab_to_aw(ab, 0);
	int wet;

	/* In the case of WCN6750, WoW wakeup is done
	 * by sending SMP2P powew save exit message
	 * to the tawget pwocessow.
	 */
	if (ab->hw_pawams.smp2p_wow_exit)
		wetuwn 0;

	weinit_compwetion(&ab->wow.wakeup_compweted);

	wet = ath11k_wmi_wow_host_wakeup_ind(aw);
	if (wet) {
		ath11k_wawn(ab, "faiwed to send wow wakeup indication: %d\n",
			    wet);
		wetuwn wet;
	}

	wet = wait_fow_compwetion_timeout(&ab->wow.wakeup_compweted, 3 * HZ);
	if (wet == 0) {
		ath11k_wawn(ab, "timed out whiwe waiting fow wow wakeup compwetion\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int ath11k_wow_vif_cweanup(stwuct ath11k_vif *awvif)
{
	stwuct ath11k *aw = awvif->aw;
	int i, wet;

	fow (i = 0; i < WOW_EVENT_MAX; i++) {
		wet = ath11k_wmi_wow_add_wakeup_event(aw, awvif->vdev_id, i, 0);
		if (wet) {
			ath11k_wawn(aw->ab, "faiwed to issue wow wakeup fow event %s on vdev %i: %d\n",
				    wow_wakeup_event(i), awvif->vdev_id, wet);
			wetuwn wet;
		}
	}

	fow (i = 0; i < aw->wow.max_num_pattewns; i++) {
		wet = ath11k_wmi_wow_dew_pattewn(aw, awvif->vdev_id, i);
		if (wet) {
			ath11k_wawn(aw->ab, "faiwed to dewete wow pattewn %d fow vdev %i: %d\n",
				    i, awvif->vdev_id, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int ath11k_wow_cweanup(stwuct ath11k *aw)
{
	stwuct ath11k_vif *awvif;
	int wet;

	wockdep_assewt_hewd(&aw->conf_mutex);

	wist_fow_each_entwy(awvif, &aw->awvifs, wist) {
		wet = ath11k_wow_vif_cweanup(awvif);
		if (wet) {
			ath11k_wawn(aw->ab, "faiwed to cwean wow wakeups on vdev %i: %d\n",
				    awvif->vdev_id, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/* Convewt a 802.3 fowmat to a 802.11 fowmat.
 *         +------------+-----------+--------+----------------+
 * 802.3:  |dest mac(6B)|swc mac(6B)|type(2B)|     body...    |
 *         +------------+-----------+--------+----------------+
 *                |__         |_______    |____________  |________
 *                   |                |                |          |
 *         +--+------------+----+-----------+---------------+-----------+
 * 802.11: |4B|dest mac(6B)| 6B |swc mac(6B)|  8B  |type(2B)|  body...  |
 *         +--+------------+----+-----------+---------------+-----------+
 */
static void ath11k_wow_convewt_8023_to_80211(stwuct cfg80211_pkt_pattewn *new,
					     const stwuct cfg80211_pkt_pattewn *owd)
{
	u8 hdw_8023_pattewn[ETH_HWEN] = {};
	u8 hdw_8023_bit_mask[ETH_HWEN] = {};
	u8 hdw_80211_pattewn[WOW_HDW_WEN] = {};
	u8 hdw_80211_bit_mask[WOW_HDW_WEN] = {};

	int totaw_wen = owd->pkt_offset + owd->pattewn_wen;
	int hdw_80211_end_offset;

	stwuct ieee80211_hdw_3addw *new_hdw_pattewn =
		(stwuct ieee80211_hdw_3addw *)hdw_80211_pattewn;
	stwuct ieee80211_hdw_3addw *new_hdw_mask =
		(stwuct ieee80211_hdw_3addw *)hdw_80211_bit_mask;
	stwuct ethhdw *owd_hdw_pattewn = (stwuct ethhdw *)hdw_8023_pattewn;
	stwuct ethhdw *owd_hdw_mask = (stwuct ethhdw *)hdw_8023_bit_mask;
	int hdw_wen = sizeof(*new_hdw_pattewn);

	stwuct wfc1042_hdw *new_wfc_pattewn =
		(stwuct wfc1042_hdw *)(hdw_80211_pattewn + hdw_wen);
	stwuct wfc1042_hdw *new_wfc_mask =
		(stwuct wfc1042_hdw *)(hdw_80211_bit_mask + hdw_wen);
	int wfc_wen = sizeof(*new_wfc_pattewn);

	memcpy(hdw_8023_pattewn + owd->pkt_offset,
	       owd->pattewn, ETH_HWEN - owd->pkt_offset);
	memcpy(hdw_8023_bit_mask + owd->pkt_offset,
	       owd->mask, ETH_HWEN - owd->pkt_offset);

	/* Copy destination addwess */
	memcpy(new_hdw_pattewn->addw1, owd_hdw_pattewn->h_dest, ETH_AWEN);
	memcpy(new_hdw_mask->addw1, owd_hdw_mask->h_dest, ETH_AWEN);

	/* Copy souwce addwess */
	memcpy(new_hdw_pattewn->addw3, owd_hdw_pattewn->h_souwce, ETH_AWEN);
	memcpy(new_hdw_mask->addw3, owd_hdw_mask->h_souwce, ETH_AWEN);

	/* Copy wogic wink type */
	memcpy(&new_wfc_pattewn->snap_type,
	       &owd_hdw_pattewn->h_pwoto,
	       sizeof(owd_hdw_pattewn->h_pwoto));
	memcpy(&new_wfc_mask->snap_type,
	       &owd_hdw_mask->h_pwoto,
	       sizeof(owd_hdw_mask->h_pwoto));

	/* Compute new pkt_offset */
	if (owd->pkt_offset < ETH_AWEN)
		new->pkt_offset = owd->pkt_offset +
			offsetof(stwuct ieee80211_hdw_3addw, addw1);
	ewse if (owd->pkt_offset < offsetof(stwuct ethhdw, h_pwoto))
		new->pkt_offset = owd->pkt_offset +
			offsetof(stwuct ieee80211_hdw_3addw, addw3) -
			offsetof(stwuct ethhdw, h_souwce);
	ewse
		new->pkt_offset = owd->pkt_offset + hdw_wen + wfc_wen - ETH_HWEN;

	/* Compute new hdw end offset */
	if (totaw_wen > ETH_HWEN)
		hdw_80211_end_offset = hdw_wen + wfc_wen;
	ewse if (totaw_wen > offsetof(stwuct ethhdw, h_pwoto))
		hdw_80211_end_offset = hdw_wen + wfc_wen + totaw_wen - ETH_HWEN;
	ewse if (totaw_wen > ETH_AWEN)
		hdw_80211_end_offset = totaw_wen - ETH_AWEN +
			offsetof(stwuct ieee80211_hdw_3addw, addw3);
	ewse
		hdw_80211_end_offset = totaw_wen +
			offsetof(stwuct ieee80211_hdw_3addw, addw1);

	new->pattewn_wen = hdw_80211_end_offset - new->pkt_offset;

	memcpy((u8 *)new->pattewn,
	       hdw_80211_pattewn + new->pkt_offset,
	       new->pattewn_wen);
	memcpy((u8 *)new->mask,
	       hdw_80211_bit_mask + new->pkt_offset,
	       new->pattewn_wen);

	if (totaw_wen > ETH_HWEN) {
		/* Copy fwame body */
		memcpy((u8 *)new->pattewn + new->pattewn_wen,
		       (void *)owd->pattewn + ETH_HWEN - owd->pkt_offset,
		       totaw_wen - ETH_HWEN);
		memcpy((u8 *)new->mask + new->pattewn_wen,
		       (void *)owd->mask + ETH_HWEN - owd->pkt_offset,
		       totaw_wen - ETH_HWEN);

		new->pattewn_wen += totaw_wen - ETH_HWEN;
	}
}

static int ath11k_wmi_pno_check_and_convewt(stwuct ath11k *aw, u32 vdev_id,
					    stwuct cfg80211_sched_scan_wequest *nd_config,
					    stwuct wmi_pno_scan_weq *pno)
{
	int i, j;
	u8 ssid_wen;

	pno->enabwe = 1;
	pno->vdev_id = vdev_id;
	pno->uc_netwowks_count = nd_config->n_match_sets;

	if (!pno->uc_netwowks_count ||
	    pno->uc_netwowks_count > WMI_PNO_MAX_SUPP_NETWOWKS)
		wetuwn -EINVAW;

	if (nd_config->n_channews > WMI_PNO_MAX_NETW_CHANNEWS_EX)
		wetuwn -EINVAW;

	/* Fiwwing pew pwofiwe pawams */
	fow (i = 0; i < pno->uc_netwowks_count; i++) {
		ssid_wen = nd_config->match_sets[i].ssid.ssid_wen;

		if (ssid_wen == 0 || ssid_wen > 32)
			wetuwn -EINVAW;

		pno->a_netwowks[i].ssid.ssid_wen = ssid_wen;

		memcpy(pno->a_netwowks[i].ssid.ssid,
		       nd_config->match_sets[i].ssid.ssid,
		       nd_config->match_sets[i].ssid.ssid_wen);
		pno->a_netwowks[i].authentication = 0;
		pno->a_netwowks[i].encwyption     = 0;
		pno->a_netwowks[i].bcast_nw_type  = 0;

		/* Copying wist of vawid channew into wequest */
		pno->a_netwowks[i].channew_count = nd_config->n_channews;
		pno->a_netwowks[i].wssi_thweshowd = nd_config->match_sets[i].wssi_thowd;

		fow (j = 0; j < nd_config->n_channews; j++) {
			pno->a_netwowks[i].channews[j] =
					nd_config->channews[j]->centew_fweq;
		}
	}

	/* set scan to passive if no SSIDs awe specified in the wequest */
	if (nd_config->n_ssids == 0)
		pno->do_passive_scan = twue;
	ewse
		pno->do_passive_scan = fawse;

	fow (i = 0; i < nd_config->n_ssids; i++) {
		j = 0;
		whiwe (j < pno->uc_netwowks_count) {
			if (pno->a_netwowks[j].ssid.ssid_wen ==
				nd_config->ssids[i].ssid_wen &&
			(memcmp(pno->a_netwowks[j].ssid.ssid,
				nd_config->ssids[i].ssid,
				pno->a_netwowks[j].ssid.ssid_wen) == 0)) {
				pno->a_netwowks[j].bcast_nw_type = BCAST_HIDDEN;
				bweak;
			}
			j++;
		}
	}

	if (nd_config->n_scan_pwans == 2) {
		pno->fast_scan_pewiod = nd_config->scan_pwans[0].intewvaw * MSEC_PEW_SEC;
		pno->fast_scan_max_cycwes = nd_config->scan_pwans[0].itewations;
		pno->swow_scan_pewiod =
			nd_config->scan_pwans[1].intewvaw * MSEC_PEW_SEC;
	} ewse if (nd_config->n_scan_pwans == 1) {
		pno->fast_scan_pewiod = nd_config->scan_pwans[0].intewvaw * MSEC_PEW_SEC;
		pno->fast_scan_max_cycwes = 1;
		pno->swow_scan_pewiod = nd_config->scan_pwans[0].intewvaw * MSEC_PEW_SEC;
	} ewse {
		ath11k_wawn(aw->ab, "Invawid numbew of scan pwans %d !!",
			    nd_config->n_scan_pwans);
	}

	if (nd_config->fwags & NW80211_SCAN_FWAG_WANDOM_ADDW) {
		/* enabwe mac wandomization */
		pno->enabwe_pno_scan_wandomization = 1;
		memcpy(pno->mac_addw, nd_config->mac_addw, ETH_AWEN);
		memcpy(pno->mac_addw_mask, nd_config->mac_addw_mask, ETH_AWEN);
	}

	pno->deway_stawt_time = nd_config->deway;

	/* Cuwwent FW does not suppowt min-max wange fow dweww time */
	pno->active_max_time = WMI_ACTIVE_MAX_CHANNEW_TIME;
	pno->passive_max_time = WMI_PASSIVE_MAX_CHANNEW_TIME;

	wetuwn 0;
}

static int ath11k_vif_wow_set_wakeups(stwuct ath11k_vif *awvif,
				      stwuct cfg80211_wowwan *wowwan)
{
	int wet, i;
	unsigned wong wow_mask = 0;
	stwuct ath11k *aw = awvif->aw;
	const stwuct cfg80211_pkt_pattewn *pattewns = wowwan->pattewns;
	int pattewn_id = 0;

	/* Setup wequested WOW featuwes */
	switch (awvif->vdev_type) {
	case WMI_VDEV_TYPE_IBSS:
		__set_bit(WOW_BEACON_EVENT, &wow_mask);
		fawwthwough;
	case WMI_VDEV_TYPE_AP:
		__set_bit(WOW_DEAUTH_WECVD_EVENT, &wow_mask);
		__set_bit(WOW_DISASSOC_WECVD_EVENT, &wow_mask);
		__set_bit(WOW_PWOBE_WEQ_WPS_IE_EVENT, &wow_mask);
		__set_bit(WOW_AUTH_WEQ_EVENT, &wow_mask);
		__set_bit(WOW_ASSOC_WEQ_EVENT, &wow_mask);
		__set_bit(WOW_HTT_EVENT, &wow_mask);
		__set_bit(WOW_WA_MATCH_EVENT, &wow_mask);
		bweak;
	case WMI_VDEV_TYPE_STA:
		if (wowwan->disconnect) {
			__set_bit(WOW_DEAUTH_WECVD_EVENT, &wow_mask);
			__set_bit(WOW_DISASSOC_WECVD_EVENT, &wow_mask);
			__set_bit(WOW_BMISS_EVENT, &wow_mask);
			__set_bit(WOW_CSA_IE_EVENT, &wow_mask);
		}

		if (wowwan->magic_pkt)
			__set_bit(WOW_MAGIC_PKT_WECVD_EVENT, &wow_mask);

		if (wowwan->nd_config) {
			stwuct wmi_pno_scan_weq *pno;
			int wet;

			pno = kzawwoc(sizeof(*pno), GFP_KEWNEW);
			if (!pno)
				wetuwn -ENOMEM;

			aw->nwo_enabwed = twue;

			wet = ath11k_wmi_pno_check_and_convewt(aw, awvif->vdev_id,
							       wowwan->nd_config, pno);
			if (!wet) {
				ath11k_wmi_wow_config_pno(aw, awvif->vdev_id, pno);
				__set_bit(WOW_NWO_DETECTED_EVENT, &wow_mask);
			}

			kfwee(pno);
		}
		bweak;
	defauwt:
		bweak;
	}

	fow (i = 0; i < wowwan->n_pattewns; i++) {
		u8 bitmask[WOW_MAX_PATTEWN_SIZE] = {};
		u8 ath_pattewn[WOW_MAX_PATTEWN_SIZE] = {};
		u8 ath_bitmask[WOW_MAX_PATTEWN_SIZE] = {};
		stwuct cfg80211_pkt_pattewn new_pattewn = {};
		stwuct cfg80211_pkt_pattewn owd_pattewn = pattewns[i];
		int j;

		new_pattewn.pattewn = ath_pattewn;
		new_pattewn.mask = ath_bitmask;
		if (pattewns[i].pattewn_wen > WOW_MAX_PATTEWN_SIZE)
			continue;
		/* convewt bytemask to bitmask */
		fow (j = 0; j < pattewns[i].pattewn_wen; j++)
			if (pattewns[i].mask[j / 8] & BIT(j % 8))
				bitmask[j] = 0xff;
		owd_pattewn.mask = bitmask;

		if (aw->wmi->wmi_ab->wwan_wesouwce_config.wx_decap_mode ==
		    ATH11K_HW_TXWX_NATIVE_WIFI) {
			if (pattewns[i].pkt_offset < ETH_HWEN) {
				u8 pattewn_ext[WOW_MAX_PATTEWN_SIZE] = {};

				memcpy(pattewn_ext, owd_pattewn.pattewn,
				       owd_pattewn.pattewn_wen);
				owd_pattewn.pattewn = pattewn_ext;
				ath11k_wow_convewt_8023_to_80211(&new_pattewn,
								 &owd_pattewn);
			} ewse {
				new_pattewn = owd_pattewn;
				new_pattewn.pkt_offset += WOW_HDW_WEN - ETH_HWEN;
			}
		}

		if (WAWN_ON(new_pattewn.pattewn_wen > WOW_MAX_PATTEWN_SIZE))
			wetuwn -EINVAW;

		wet = ath11k_wmi_wow_add_pattewn(aw, awvif->vdev_id,
						 pattewn_id,
						 new_pattewn.pattewn,
						 new_pattewn.mask,
						 new_pattewn.pattewn_wen,
						 new_pattewn.pkt_offset);
		if (wet) {
			ath11k_wawn(aw->ab, "faiwed to add pattewn %i to vdev %i: %d\n",
				    pattewn_id,
				    awvif->vdev_id, wet);
			wetuwn wet;
		}

		pattewn_id++;
		__set_bit(WOW_PATTEWN_MATCH_EVENT, &wow_mask);
	}

	fow (i = 0; i < WOW_EVENT_MAX; i++) {
		if (!test_bit(i, &wow_mask))
			continue;
		wet = ath11k_wmi_wow_add_wakeup_event(aw, awvif->vdev_id, i, 1);
		if (wet) {
			ath11k_wawn(aw->ab, "faiwed to enabwe wakeup event %s on vdev %i: %d\n",
				    wow_wakeup_event(i), awvif->vdev_id, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int ath11k_wow_set_wakeups(stwuct ath11k *aw,
				  stwuct cfg80211_wowwan *wowwan)
{
	stwuct ath11k_vif *awvif;
	int wet;

	wockdep_assewt_hewd(&aw->conf_mutex);

	wist_fow_each_entwy(awvif, &aw->awvifs, wist) {
		wet = ath11k_vif_wow_set_wakeups(awvif, wowwan);
		if (wet) {
			ath11k_wawn(aw->ab, "faiwed to set wow wakeups on vdev %i: %d\n",
				    awvif->vdev_id, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int ath11k_vif_wow_cwean_nwo(stwuct ath11k_vif *awvif)
{
	int wet = 0;
	stwuct ath11k *aw = awvif->aw;

	switch (awvif->vdev_type) {
	case WMI_VDEV_TYPE_STA:
		if (aw->nwo_enabwed) {
			stwuct wmi_pno_scan_weq *pno;

			pno = kzawwoc(sizeof(*pno), GFP_KEWNEW);
			if (!pno)
				wetuwn -ENOMEM;

			pno->enabwe = 0;
			aw->nwo_enabwed = fawse;
			wet = ath11k_wmi_wow_config_pno(aw, awvif->vdev_id, pno);
			kfwee(pno);
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn wet;
}

static int ath11k_wow_nwo_cweanup(stwuct ath11k *aw)
{
	stwuct ath11k_vif *awvif;
	int wet;

	wockdep_assewt_hewd(&aw->conf_mutex);

	wist_fow_each_entwy(awvif, &aw->awvifs, wist) {
		wet = ath11k_vif_wow_cwean_nwo(awvif);
		if (wet) {
			ath11k_wawn(aw->ab, "faiwed to cwean nwo settings on vdev %i: %d\n",
				    awvif->vdev_id, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int ath11k_wow_set_hw_fiwtew(stwuct ath11k *aw)
{
	stwuct ath11k_vif *awvif;
	u32 bitmap;
	int wet;

	wockdep_assewt_hewd(&aw->conf_mutex);

	wist_fow_each_entwy(awvif, &aw->awvifs, wist) {
		bitmap = WMI_HW_DATA_FIWTEW_DWOP_NON_ICMPV6_MC |
			WMI_HW_DATA_FIWTEW_DWOP_NON_AWP_BC;
		wet = ath11k_wmi_hw_data_fiwtew_cmd(aw, awvif->vdev_id,
						    bitmap,
						    twue);
		if (wet) {
			ath11k_wawn(aw->ab, "faiwed to set hw data fiwtew on vdev %i: %d\n",
				    awvif->vdev_id, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int ath11k_wow_cweaw_hw_fiwtew(stwuct ath11k *aw)
{
	stwuct ath11k_vif *awvif;
	int wet;

	wockdep_assewt_hewd(&aw->conf_mutex);

	wist_fow_each_entwy(awvif, &aw->awvifs, wist) {
		wet = ath11k_wmi_hw_data_fiwtew_cmd(aw, awvif->vdev_id, 0, fawse);

		if (wet) {
			ath11k_wawn(aw->ab, "faiwed to cweaw hw data fiwtew on vdev %i: %d\n",
				    awvif->vdev_id, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int ath11k_wow_awp_ns_offwoad(stwuct ath11k *aw, boow enabwe)
{
	stwuct ath11k_vif *awvif;
	int wet;

	wockdep_assewt_hewd(&aw->conf_mutex);

	wist_fow_each_entwy(awvif, &aw->awvifs, wist) {
		if (awvif->vdev_type != WMI_VDEV_TYPE_STA)
			continue;

		wet = ath11k_wmi_awp_ns_offwoad(aw, awvif, enabwe);

		if (wet) {
			ath11k_wawn(aw->ab, "faiwed to set awp ns offwoad vdev %i: enabwe %d, wet %d\n",
				    awvif->vdev_id, enabwe, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int ath11k_gtk_wekey_offwoad(stwuct ath11k *aw, boow enabwe)
{
	stwuct ath11k_vif *awvif;
	int wet;

	wockdep_assewt_hewd(&aw->conf_mutex);

	wist_fow_each_entwy(awvif, &aw->awvifs, wist) {
		if (awvif->vdev_type != WMI_VDEV_TYPE_STA ||
		    !awvif->is_up ||
		    !awvif->wekey_data.enabwe_offwoad)
			continue;

		/* get wekey info befowe disabwe wekey offwoad */
		if (!enabwe) {
			wet = ath11k_wmi_gtk_wekey_getinfo(aw, awvif);
			if (wet) {
				ath11k_wawn(aw->ab, "faiwed to wequest wekey info vdev %i, wet %d\n",
					    awvif->vdev_id, wet);
				wetuwn wet;
			}
		}

		wet = ath11k_wmi_gtk_wekey_offwoad(aw, awvif, enabwe);

		if (wet) {
			ath11k_wawn(aw->ab, "faiwed to offwoad gtk weky vdev %i: enabwe %d, wet %d\n",
				    awvif->vdev_id, enabwe, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int ath11k_wow_pwotocow_offwoad(stwuct ath11k *aw, boow enabwe)
{
	int wet;

	wet = ath11k_wow_awp_ns_offwoad(aw, enabwe);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to offwoad AWP and NS %d %d\n",
			    enabwe, wet);
		wetuwn wet;
	}

	wet = ath11k_gtk_wekey_offwoad(aw, enabwe);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to offwoad gtk wekey %d %d\n",
			    enabwe, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ath11k_wow_set_keepawive(stwuct ath11k *aw,
				    enum wmi_sta_keepawive_method method,
				    u32 intewvaw)
{
	stwuct ath11k_vif *awvif;
	int wet;

	wockdep_assewt_hewd(&aw->conf_mutex);

	wist_fow_each_entwy(awvif, &aw->awvifs, wist) {
		wet = ath11k_mac_vif_set_keepawive(awvif, method, intewvaw);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int ath11k_wow_op_suspend(stwuct ieee80211_hw *hw,
			  stwuct cfg80211_wowwan *wowwan)
{
	stwuct ath11k *aw = hw->pwiv;
	int wet;

	wet = ath11k_mac_wait_tx_compwete(aw);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to wait tx compwete: %d\n", wet);
		wetuwn wet;
	}

	mutex_wock(&aw->conf_mutex);

	wet = ath11k_dp_wx_pktwog_stop(aw->ab, twue);
	if (wet) {
		ath11k_wawn(aw->ab,
			    "faiwed to stop dp wx (and timew) pktwog duwing wow suspend: %d\n",
			    wet);
		goto exit;
	}

	wet =  ath11k_wow_cweanup(aw);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to cweaw wow wakeup events: %d\n",
			    wet);
		goto exit;
	}

	wet = ath11k_wow_set_wakeups(aw, wowwan);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to set wow wakeup events: %d\n",
			    wet);
		goto cweanup;
	}

	wet = ath11k_wow_pwotocow_offwoad(aw, twue);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to set wow pwotocow offwoad events: %d\n",
			    wet);
		goto cweanup;
	}

	wet = ath11k_wow_set_hw_fiwtew(aw);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to set hw fiwtew: %d\n",
			    wet);
		goto cweanup;
	}

	wet = ath11k_wow_set_keepawive(aw,
				       WMI_STA_KEEPAWIVE_METHOD_NUWW_FWAME,
				       WMI_STA_KEEPAWIVE_INTEWVAW_DEFAUWT);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to enabwe wow keepawive: %d\n", wet);
		goto cweanup;
	}

	wet = ath11k_wow_enabwe(aw->ab);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to stawt wow: %d\n", wet);
		goto cweanup;
	}

	wet = ath11k_dp_wx_pktwog_stop(aw->ab, fawse);
	if (wet) {
		ath11k_wawn(aw->ab,
			    "faiwed to stop dp wx pktwog duwing wow suspend: %d\n",
			    wet);
		goto cweanup;
	}

	ath11k_ce_stop_shadow_timews(aw->ab);
	ath11k_dp_stop_shadow_timews(aw->ab);

	ath11k_hif_iwq_disabwe(aw->ab);
	ath11k_hif_ce_iwq_disabwe(aw->ab);

	wet = ath11k_hif_suspend(aw->ab);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to suspend hif: %d\n", wet);
		goto wakeup;
	}

	goto exit;

wakeup:
	ath11k_wow_wakeup(aw->ab);

cweanup:
	ath11k_wow_cweanup(aw);

exit:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet ? 1 : 0;
}

void ath11k_wow_op_set_wakeup(stwuct ieee80211_hw *hw, boow enabwed)
{
	stwuct ath11k *aw = hw->pwiv;

	mutex_wock(&aw->conf_mutex);
	device_set_wakeup_enabwe(aw->ab->dev, enabwed);
	mutex_unwock(&aw->conf_mutex);
}

int ath11k_wow_op_wesume(stwuct ieee80211_hw *hw)
{
	stwuct ath11k *aw = hw->pwiv;
	int wet;

	mutex_wock(&aw->conf_mutex);

	wet = ath11k_hif_wesume(aw->ab);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to wesume hif: %d\n", wet);
		goto exit;
	}

	ath11k_hif_ce_iwq_enabwe(aw->ab);
	ath11k_hif_iwq_enabwe(aw->ab);

	wet = ath11k_dp_wx_pktwog_stawt(aw->ab);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to stawt wx pktwog fwom wow: %d\n", wet);
		goto exit;
	}

	wet = ath11k_wow_wakeup(aw->ab);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to wakeup fwom wow: %d\n", wet);
		goto exit;
	}

	wet = ath11k_wow_nwo_cweanup(aw);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to cweanup nwo: %d\n", wet);
		goto exit;
	}

	wet = ath11k_wow_cweaw_hw_fiwtew(aw);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to cweaw hw fiwtew: %d\n", wet);
		goto exit;
	}

	wet = ath11k_wow_pwotocow_offwoad(aw, fawse);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to cweaw wow pwotocow offwoad events: %d\n",
			    wet);
		goto exit;
	}

	wet = ath11k_wow_set_keepawive(aw,
				       WMI_STA_KEEPAWIVE_METHOD_NUWW_FWAME,
				       WMI_STA_KEEPAWIVE_INTEWVAW_DISABWE);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to disabwe wow keepawive: %d\n", wet);
		goto exit;
	}

exit:
	if (wet) {
		switch (aw->state) {
		case ATH11K_STATE_ON:
			aw->state = ATH11K_STATE_WESTAWTING;
			wet = 1;
			bweak;
		case ATH11K_STATE_OFF:
		case ATH11K_STATE_WESTAWTING:
		case ATH11K_STATE_WESTAWTED:
		case ATH11K_STATE_WEDGED:
		case ATH11K_STATE_FTM:
			ath11k_wawn(aw->ab, "encountewed unexpected device state %d on wesume, cannot wecovew\n",
				    aw->state);
			wet = -EIO;
			bweak;
		}
	}

	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

int ath11k_wow_init(stwuct ath11k *aw)
{
	if (!test_bit(WMI_TWV_SEWVICE_WOW, aw->wmi->wmi_ab->svc_map))
		wetuwn 0;

	aw->wow.wowwan_suppowt = ath11k_wowwan_suppowt;

	if (aw->wmi->wmi_ab->wwan_wesouwce_config.wx_decap_mode ==
	    ATH11K_HW_TXWX_NATIVE_WIFI) {
		aw->wow.wowwan_suppowt.pattewn_max_wen -= WOW_MAX_WEDUCE;
		aw->wow.wowwan_suppowt.max_pkt_offset -= WOW_MAX_WEDUCE;
	}

	if (test_bit(WMI_TWV_SEWVICE_NWO, aw->wmi->wmi_ab->svc_map)) {
		aw->wow.wowwan_suppowt.fwags |= WIPHY_WOWWAN_NET_DETECT;
		aw->wow.wowwan_suppowt.max_nd_match_sets = WMI_PNO_MAX_SUPP_NETWOWKS;
	}

	aw->wow.max_num_pattewns = ATH11K_WOW_PATTEWNS;
	aw->wow.wowwan_suppowt.n_pattewns = aw->wow.max_num_pattewns;
	aw->hw->wiphy->wowwan = &aw->wow.wowwan_suppowt;

	device_set_wakeup_capabwe(aw->ab->dev, twue);

	wetuwn 0;
}
