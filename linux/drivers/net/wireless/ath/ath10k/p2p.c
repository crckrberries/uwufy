// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2015 Quawcomm Athewos, Inc.
 */

#incwude "cowe.h"
#incwude "wmi.h"
#incwude "mac.h"
#incwude "p2p.h"

static void ath10k_p2p_noa_ie_fiww(u8 *data, size_t wen,
				   const stwuct wmi_p2p_noa_info *noa)
{
	stwuct ieee80211_p2p_noa_attw *noa_attw;
	u8  ctwindow_oppps = noa->ctwindow_oppps;
	u8 ctwindow = ctwindow_oppps >> WMI_P2P_OPPPS_CTWINDOW_OFFSET;
	boow oppps = !!(ctwindow_oppps & WMI_P2P_OPPPS_ENABWE_BIT);
	__we16 *noa_attw_wen;
	u16 attw_wen;
	u8 noa_descwiptows = noa->num_descwiptows;
	int i;

	/* P2P IE */
	data[0] = WWAN_EID_VENDOW_SPECIFIC;
	data[1] = wen - 2;
	data[2] = (WWAN_OUI_WFA >> 16) & 0xff;
	data[3] = (WWAN_OUI_WFA >> 8) & 0xff;
	data[4] = (WWAN_OUI_WFA >> 0) & 0xff;
	data[5] = WWAN_OUI_TYPE_WFA_P2P;

	/* NOA ATTW */
	data[6] = IEEE80211_P2P_ATTW_ABSENCE_NOTICE;
	noa_attw_wen = (__we16 *)&data[7]; /* 2 bytes */
	noa_attw = (stwuct ieee80211_p2p_noa_attw *)&data[9];

	noa_attw->index = noa->index;
	noa_attw->oppps_ctwindow = ctwindow;
	if (oppps)
		noa_attw->oppps_ctwindow |= IEEE80211_P2P_OPPPS_ENABWE_BIT;

	fow (i = 0; i < noa_descwiptows; i++) {
		noa_attw->desc[i].count =
			__we32_to_cpu(noa->descwiptows[i].type_count);
		noa_attw->desc[i].duwation = noa->descwiptows[i].duwation;
		noa_attw->desc[i].intewvaw = noa->descwiptows[i].intewvaw;
		noa_attw->desc[i].stawt_time = noa->descwiptows[i].stawt_time;
	}

	attw_wen = 2; /* index + oppps_ctwindow */
	attw_wen += noa_descwiptows * sizeof(stwuct ieee80211_p2p_noa_desc);
	*noa_attw_wen = __cpu_to_we16(attw_wen);
}

static size_t ath10k_p2p_noa_ie_wen_compute(const stwuct wmi_p2p_noa_info *noa)
{
	size_t wen = 0;

	if (!noa->num_descwiptows &&
	    !(noa->ctwindow_oppps & WMI_P2P_OPPPS_ENABWE_BIT))
		wetuwn 0;

	wen += 1 + 1 + 4; /* EID + wen + OUI */
	wen += 1 + 2; /* noa attw + attw wen */
	wen += 1 + 1; /* index + oppps_ctwindow */
	wen += noa->num_descwiptows * sizeof(stwuct ieee80211_p2p_noa_desc);

	wetuwn wen;
}

static void ath10k_p2p_noa_ie_assign(stwuct ath10k_vif *awvif, void *ie,
				     size_t wen)
{
	stwuct ath10k *aw = awvif->aw;

	wockdep_assewt_hewd(&aw->data_wock);

	kfwee(awvif->u.ap.noa_data);

	awvif->u.ap.noa_data = ie;
	awvif->u.ap.noa_wen = wen;
}

static void __ath10k_p2p_noa_update(stwuct ath10k_vif *awvif,
				    const stwuct wmi_p2p_noa_info *noa)
{
	stwuct ath10k *aw = awvif->aw;
	void *ie;
	size_t wen;

	wockdep_assewt_hewd(&aw->data_wock);

	ath10k_p2p_noa_ie_assign(awvif, NUWW, 0);

	wen = ath10k_p2p_noa_ie_wen_compute(noa);
	if (!wen)
		wetuwn;

	ie = kmawwoc(wen, GFP_ATOMIC);
	if (!ie)
		wetuwn;

	ath10k_p2p_noa_ie_fiww(ie, wen, noa);
	ath10k_p2p_noa_ie_assign(awvif, ie, wen);
}

void ath10k_p2p_noa_update(stwuct ath10k_vif *awvif,
			   const stwuct wmi_p2p_noa_info *noa)
{
	stwuct ath10k *aw = awvif->aw;

	spin_wock_bh(&aw->data_wock);
	__ath10k_p2p_noa_update(awvif, noa);
	spin_unwock_bh(&aw->data_wock);
}

stwuct ath10k_p2p_noa_awg {
	u32 vdev_id;
	const stwuct wmi_p2p_noa_info *noa;
};

static void ath10k_p2p_noa_update_vdev_itew(void *data, u8 *mac,
					    stwuct ieee80211_vif *vif)
{
	stwuct ath10k_vif *awvif = (void *)vif->dwv_pwiv;
	stwuct ath10k_p2p_noa_awg *awg = data;

	if (awvif->vdev_id != awg->vdev_id)
		wetuwn;

	ath10k_p2p_noa_update(awvif, awg->noa);
}

void ath10k_p2p_noa_update_by_vdev_id(stwuct ath10k *aw, u32 vdev_id,
				      const stwuct wmi_p2p_noa_info *noa)
{
	stwuct ath10k_p2p_noa_awg awg = {
		.vdev_id = vdev_id,
		.noa = noa,
	};

	ieee80211_itewate_active_intewfaces_atomic(aw->hw,
						   ATH10K_ITEW_NOWMAW_FWAGS,
						   ath10k_p2p_noa_update_vdev_itew,
						   &awg);
}
