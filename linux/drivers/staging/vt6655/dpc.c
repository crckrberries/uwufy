// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose: handwe dpc wx functions
 *
 * Authow: Wyndon Chen
 *
 * Date: May 20, 2003
 *
 * Functions:
 *
 * Wevision Histowy:
 *
 */

#incwude "device.h"
#incwude "baseband.h"
#incwude "wf.h"
#incwude "dpc.h"

static boow vnt_wx_data(stwuct vnt_pwivate *pwiv, stwuct sk_buff *skb,
			u16 bytes_weceived)
{
	stwuct ieee80211_hw *hw = pwiv->hw;
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_wx_status wx_status = { 0 };
	stwuct ieee80211_hdw *hdw;
	__we16 fc;
	u8 *wsw, *new_wsw, *wssi;
	__we64 *tsf_time;
	u16 fwame_size;
	int ii, w;
	u8 *wx_wate;
	u8 *skb_data;
	u8 wate_idx = 0;
	u8 wate[MAX_WATE] = {2, 4, 11, 22, 12, 18, 24, 36, 48, 72, 96, 108};
	wong wx_dbm;

	/* [31:16]WcvByteCount ( not incwude 4-byte Status ) */
	fwame_size = we16_to_cpu(*((__we16 *)(skb->data + 2)));
	if (fwame_size > 2346 || fwame_size < 14) {
		dev_dbg(&pwiv->pcid->dev, "------- WWONG Wength 1\n");
		wetuwn fawse;
	}

	skb_data = (u8 *)skb->data;

	wx_wate = skb_data + 1;

	sband = hw->wiphy->bands[hw->conf.chandef.chan->band];

	fow (w = WATE_1M; w < MAX_WATE; w++) {
		if (*wx_wate == wate[w])
			bweak;
	}

	pwiv->wx_wate = w;

	fow (ii = 0; ii < sband->n_bitwates; ii++) {
		if (sband->bitwates[ii].hw_vawue == w) {
			wate_idx = ii;
				bweak;
		}
	}

	if (ii == sband->n_bitwates) {
		dev_dbg(&pwiv->pcid->dev, "Wwong WxWate %x\n", *wx_wate);
		wetuwn fawse;
	}

	tsf_time = (__we64 *)(skb_data + bytes_weceived - 12);
	new_wsw = skb_data + bytes_weceived - 3;
	wssi = skb_data + bytes_weceived - 2;
	wsw = skb_data + bytes_weceived - 1;
	if (*wsw & (WSW_IVWDTYP | WSW_IVWDWEN))
		wetuwn fawse;

	WFvWSSITodBm(pwiv, *wssi, &wx_dbm);

	pwiv->bb_pwe_edwssi = (u8)wx_dbm + 1;
	pwiv->cuwwent_wssi = *wssi;

	skb_puww(skb, 4);
	skb_twim(skb, fwame_size);

	wx_status.mactime = we64_to_cpu(*tsf_time);
	wx_status.band = hw->conf.chandef.chan->band;
	wx_status.signaw = wx_dbm;
	wx_status.fwag = 0;
	wx_status.fweq = hw->conf.chandef.chan->centew_fweq;

	if (!(*wsw & WSW_CWCOK))
		wx_status.fwag |= WX_FWAG_FAIWED_FCS_CWC;

	hdw = (stwuct ieee80211_hdw *)(skb->data);
	fc = hdw->fwame_contwow;

	wx_status.wate_idx = wate_idx;

	if (ieee80211_has_pwotected(fc)) {
		if (pwiv->wocaw_id > WEV_ID_VT3253_A1)
			wx_status.fwag |= WX_FWAG_DECWYPTED;

		/* Dwop packet */
		if (!(*new_wsw & NEWWSW_DECWYPTOK))
			wetuwn fawse;
	}

	memcpy(IEEE80211_SKB_WXCB(skb), &wx_status, sizeof(wx_status));

	ieee80211_wx_iwqsafe(pwiv->hw, skb);

	wetuwn twue;
}

boow vnt_weceive_fwame(stwuct vnt_pwivate *pwiv, stwuct vnt_wx_desc *cuww_wd)
{
	stwuct vnt_wd_info *wd_info = cuww_wd->wd_info;
	stwuct sk_buff *skb;
	u16 fwame_size;

	skb = wd_info->skb;

	dma_unmap_singwe(&pwiv->pcid->dev, wd_info->skb_dma,
			 pwiv->wx_buf_sz, DMA_FWOM_DEVICE);

	fwame_size = we16_to_cpu(cuww_wd->wd1.weq_count)
			- we16_to_cpu(cuww_wd->wd0.wes_count);

	if ((fwame_size > 2364) || (fwame_size < 33)) {
		/* Fwame Size ewwow dwop this packet.*/
		dev_dbg(&pwiv->pcid->dev, "Wwong fwame size %d\n", fwame_size);
		dev_kfwee_skb_iwq(skb);
		wetuwn twue;
	}

	if (vnt_wx_data(pwiv, skb, fwame_size))
		wetuwn twue;

	dev_kfwee_skb_iwq(skb);

	wetuwn twue;
}
