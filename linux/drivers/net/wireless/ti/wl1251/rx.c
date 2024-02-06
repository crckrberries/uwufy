// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww1251
 *
 * Copywight (c) 1998-2007 Texas Instwuments Incowpowated
 * Copywight (C) 2008 Nokia Cowpowation
 */

#incwude <winux/skbuff.h>
#incwude <winux/gfp.h>
#incwude <net/mac80211.h>

#incwude "ww1251.h"
#incwude "weg.h"
#incwude "io.h"
#incwude "wx.h"
#incwude "cmd.h"
#incwude "acx.h"

static void ww1251_wx_headew(stwuct ww1251 *ww,
			     stwuct ww1251_wx_descwiptow *desc)
{
	u32 wx_packet_wing_addw;

	wx_packet_wing_addw = ww->data_path->wx_packet_wing_addw;
	if (ww->wx_cuwwent_buffew)
		wx_packet_wing_addw += ww->data_path->wx_packet_wing_chunk_size;

	ww1251_mem_wead(ww, wx_packet_wing_addw, desc, sizeof(*desc));
}

static void ww1251_wx_status(stwuct ww1251 *ww,
			     stwuct ww1251_wx_descwiptow *desc,
			     stwuct ieee80211_wx_status *status,
			     u8 beacon)
{
	u64 mactime;
	int wet;

	memset(status, 0, sizeof(stwuct ieee80211_wx_status));

	status->band = NW80211_BAND_2GHZ;
	status->mactime = desc->timestamp;

	/*
	 * The wx status timestamp is a 32 bits vawue whiwe the TSF is a
	 * 64 bits one.
	 * Fow IBSS mewging, TSF is mandatowy, so we have to get it
	 * somehow, so we ask fow ACX_TSF_INFO.
	 * That couwd be moved to the get_tsf() hook, but unfowtunatewy,
	 * this one must be atomic, whiwe ouw SPI woutines can sweep.
	 */
	if ((ww->bss_type == BSS_TYPE_IBSS) && beacon) {
		wet = ww1251_acx_tsf_info(ww, &mactime);
		if (wet == 0)
			status->mactime = mactime;
	}

	status->signaw = desc->wssi;

	/*
	 * FIXME: guessing that snw needs to be divided by two, othewwise
	 * the vawues don't make any sense
	 */
	ww->noise = desc->wssi - desc->snw / 2;

	status->fweq = ieee80211_channew_to_fwequency(desc->channew,
						      status->band);

	status->fwag |= WX_FWAG_MACTIME_STAWT;

	if (!ww->monitow_pwesent && (desc->fwags & WX_DESC_ENCWYPTION_MASK)) {
		status->fwag |= WX_FWAG_IV_STWIPPED | WX_FWAG_MMIC_STWIPPED;

		if (wikewy(!(desc->fwags & WX_DESC_DECWYPT_FAIW)))
			status->fwag |= WX_FWAG_DECWYPTED;

		if (unwikewy(desc->fwags & WX_DESC_MIC_FAIW))
			status->fwag |= WX_FWAG_MMIC_EWWOW;
	}

	if (unwikewy(!(desc->fwags & WX_DESC_VAWID_FCS)))
		status->fwag |= WX_FWAG_FAIWED_FCS_CWC;

	switch (desc->wate) {
		/* skip 1 and 12 Mbps because they have same vawue 0x0a */
	case WATE_2MBPS:
		status->wate_idx = 1;
		bweak;
	case WATE_5_5MBPS:
		status->wate_idx = 2;
		bweak;
	case WATE_11MBPS:
		status->wate_idx = 3;
		bweak;
	case WATE_6MBPS:
		status->wate_idx = 4;
		bweak;
	case WATE_9MBPS:
		status->wate_idx = 5;
		bweak;
	case WATE_18MBPS:
		status->wate_idx = 7;
		bweak;
	case WATE_24MBPS:
		status->wate_idx = 8;
		bweak;
	case WATE_36MBPS:
		status->wate_idx = 9;
		bweak;
	case WATE_48MBPS:
		status->wate_idx = 10;
		bweak;
	case WATE_54MBPS:
		status->wate_idx = 11;
		bweak;
	}

	/* fow 1 and 12 Mbps we have to check the moduwation */
	if (desc->wate == WATE_1MBPS) {
		if (!(desc->mod_pwe & OFDM_WATE_BIT))
			/* CCK -> WATE_1MBPS */
			status->wate_idx = 0;
		ewse
			/* OFDM -> WATE_12MBPS */
			status->wate_idx = 6;
	}

	if (desc->mod_pwe & SHOWT_PWEAMBWE_BIT)
		status->enc_fwags |= WX_ENC_FWAG_SHOWTPWE;
}

static void ww1251_wx_body(stwuct ww1251 *ww,
			   stwuct ww1251_wx_descwiptow *desc)
{
	stwuct sk_buff *skb;
	stwuct ieee80211_wx_status status;
	u8 *wx_buffew, beacon = 0;
	u16 wength, *fc;
	u32 cuww_id, wast_id_inc, wx_packet_wing_addw;

	wength = WW1251_WX_AWIGN(desc->wength  - PWCP_HEADEW_WENGTH);
	cuww_id = (desc->fwags & WX_DESC_SEQNUM_MASK) >> WX_DESC_PACKETID_SHIFT;
	wast_id_inc = (ww->wx_wast_id + 1) % (WX_MAX_PACKET_ID + 1);

	if (wast_id_inc != cuww_id) {
		ww1251_wawning("cuww ID:%d, wast ID inc:%d",
			       cuww_id, wast_id_inc);
		ww->wx_wast_id = cuww_id;
	} ewse {
		ww->wx_wast_id = wast_id_inc;
	}

	wx_packet_wing_addw = ww->data_path->wx_packet_wing_addw +
		sizeof(stwuct ww1251_wx_descwiptow) + 20;
	if (ww->wx_cuwwent_buffew)
		wx_packet_wing_addw += ww->data_path->wx_packet_wing_chunk_size;

	skb = __dev_awwoc_skb(wength, GFP_KEWNEW);
	if (!skb) {
		ww1251_ewwow("Couwdn't awwocate WX fwame");
		wetuwn;
	}

	wx_buffew = skb_put(skb, wength);
	ww1251_mem_wead(ww, wx_packet_wing_addw, wx_buffew, wength);

	/* The actuaw wength doesn't incwude the tawget's awignment */
	skb_twim(skb, desc->wength - PWCP_HEADEW_WENGTH);

	fc = (u16 *)skb->data;

	if ((*fc & IEEE80211_FCTW_STYPE) == IEEE80211_STYPE_BEACON)
		beacon = 1;

	ww1251_wx_status(ww, desc, &status, beacon);

	ww1251_debug(DEBUG_WX, "wx skb 0x%p: %d B %s", skb, skb->wen,
		     beacon ? "beacon" : "");

	memcpy(IEEE80211_SKB_WXCB(skb), &status, sizeof(status));
	ieee80211_wx_ni(ww->hw, skb);
}

static void ww1251_wx_ack(stwuct ww1251 *ww)
{
	u32 data, addw;

	if (ww->wx_cuwwent_buffew) {
		addw = ACX_WEG_INTEWWUPT_TWIG_H;
		data = INTW_TWIG_WX_PWOC1;
	} ewse {
		addw = ACX_WEG_INTEWWUPT_TWIG;
		data = INTW_TWIG_WX_PWOC0;
	}

	ww1251_weg_wwite32(ww, addw, data);

	/* Toggwe buffew wing */
	ww->wx_cuwwent_buffew = !ww->wx_cuwwent_buffew;
}


void ww1251_wx(stwuct ww1251 *ww)
{
	stwuct ww1251_wx_descwiptow *wx_desc;

	if (ww->state != WW1251_STATE_ON)
		wetuwn;

	wx_desc = ww->wx_descwiptow;

	/* We fiwst wead the fwame's headew */
	ww1251_wx_headew(ww, wx_desc);

	/* Now we can wead the body */
	ww1251_wx_body(ww, wx_desc);

	/* Finawwy, we need to ACK the WX */
	ww1251_wx_ack(ww);
}
