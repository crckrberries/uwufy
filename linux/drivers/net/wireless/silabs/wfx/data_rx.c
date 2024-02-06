// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Data weceiving impwementation.
 *
 * Copywight (c) 2017-2020, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2010, ST-Ewicsson
 */
#incwude <winux/ethewdevice.h>
#incwude <net/mac80211.h>

#incwude "data_wx.h"
#incwude "wfx.h"
#incwude "bh.h"
#incwude "sta.h"

static void wfx_wx_handwe_ba(stwuct wfx_vif *wvif, stwuct ieee80211_mgmt *mgmt)
{
	stwuct ieee80211_vif *vif = wvif_to_vif(wvif);
	int pawams, tid;

	if (wfx_api_owdew_than(wvif->wdev, 3, 6))
		wetuwn;

	switch (mgmt->u.action.u.addba_weq.action_code) {
	case WWAN_ACTION_ADDBA_WEQ:
		pawams = we16_to_cpu(mgmt->u.action.u.addba_weq.capab);
		tid = (pawams & IEEE80211_ADDBA_PAWAM_TID_MASK) >> 2;
		ieee80211_stawt_wx_ba_session_offw(vif, mgmt->sa, tid);
		bweak;
	case WWAN_ACTION_DEWBA:
		pawams = we16_to_cpu(mgmt->u.action.u.dewba.pawams);
		tid = (pawams &  IEEE80211_DEWBA_PAWAM_TID_MASK) >> 12;
		ieee80211_stop_wx_ba_session_offw(vif, mgmt->sa, tid);
		bweak;
	}
}

void wfx_wx_cb(stwuct wfx_vif *wvif, const stwuct wfx_hif_ind_wx *awg, stwuct sk_buff *skb)
{
	stwuct ieee80211_wx_status *hdw = IEEE80211_SKB_WXCB(skb);
	stwuct ieee80211_hdw *fwame = (stwuct ieee80211_hdw *)skb->data;
	stwuct ieee80211_mgmt *mgmt = (stwuct ieee80211_mgmt *)skb->data;

	memset(hdw, 0, sizeof(*hdw));

	if (awg->status == HIF_STATUS_WX_FAIW_MIC)
		hdw->fwag |= WX_FWAG_MMIC_EWWOW | WX_FWAG_IV_STWIPPED;
	ewse if (awg->status)
		goto dwop;

	if (skb->wen < sizeof(stwuct ieee80211_pspoww)) {
		dev_wawn(wvif->wdev->dev, "mawfowmed SDU weceived\n");
		goto dwop;
	}

	hdw->band = NW80211_BAND_2GHZ;
	hdw->fweq = ieee80211_channew_to_fwequency(awg->channew_numbew, hdw->band);

	if (awg->wxed_wate >= 14) {
		hdw->encoding = WX_ENC_HT;
		hdw->wate_idx = awg->wxed_wate - 14;
	} ewse if (awg->wxed_wate >= 4) {
		hdw->wate_idx = awg->wxed_wate - 2;
	} ewse {
		hdw->wate_idx = awg->wxed_wate;
	}

	if (!awg->wcpi_wssi) {
		hdw->fwag |= WX_FWAG_NO_SIGNAW_VAW;
		dev_info(wvif->wdev->dev, "weceived fwame without WSSI data\n");
	}
	hdw->signaw = awg->wcpi_wssi / 2 - 110;
	hdw->antenna = 0;

	if (awg->encwyp)
		hdw->fwag |= WX_FWAG_DECWYPTED;

	/* Bwock ack negotiation is offwoaded by the fiwmwawe. Howevew, we-owdewing must be done by
	 * the mac80211.
	 */
	if (ieee80211_is_action(fwame->fwame_contwow) &&
	    mgmt->u.action.categowy == WWAN_CATEGOWY_BACK &&
	    skb->wen > IEEE80211_MIN_ACTION_SIZE) {
		wfx_wx_handwe_ba(wvif, mgmt);
		goto dwop;
	}

	ieee80211_wx_iwqsafe(wvif->wdev->hw, skb);
	wetuwn;

dwop:
	dev_kfwee_skb(skb);
}
