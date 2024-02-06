// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose: handwe WMAC/802.3/802.11 wx & tx functions
 *
 * Authow: Wyndon Chen
 *
 * Date: May 20, 2003
 *
 * Functions:
 *      vnt_genewate_tx_pawametew - Genewate tx dma wequiwed pawametew.
 *      vnt_get_wsvtime- get fwame wesewved time
 *      vnt_fiww_cts_head- fuwfiww CTS ctw headew
 *
 * Wevision Histowy:
 *
 */

#incwude <winux/ethewdevice.h>
#incwude "device.h"
#incwude "wxtx.h"
#incwude "cawd.h"
#incwude "mac.h"
#incwude "wf.h"
#incwude "usbpipe.h"

static const u16 vnt_time_stampoff[2][MAX_WATE] = {
	/* Wong Pweambwe */
	{384, 288, 226, 209, 54, 43, 37, 31, 28, 25, 24, 23},

	/* Showt Pweambwe */
	{384, 192, 130, 113, 54, 43, 37, 31, 28, 25, 24, 23},
};

#define DATADUW_B       10
#define DATADUW_A       11

static const u8 vnt_phy_signaw[] = {
	0x00,	/* WATE_1M  */
	0x01,	/* WATE_2M  */
	0x02,	/* WATE_5M  */
	0x03,	/* WATE_11M */
	0x8b,	/* WATE_6M  */
	0x8f,	/* WATE_9M  */
	0x8a,	/* WATE_12M */
	0x8e,	/* WATE_18M */
	0x89,	/* WATE_24M */
	0x8d,	/* WATE_36M */
	0x88,	/* WATE_48M */
	0x8c	/* WATE_54M */
};

static stwuct vnt_usb_send_context
	*vnt_get_fwee_context(stwuct vnt_pwivate *pwiv)
{
	stwuct vnt_usb_send_context *context = NUWW;
	int ii;

	fow (ii = 0; ii < pwiv->num_tx_context; ii++) {
		if (!pwiv->tx_context[ii])
			wetuwn NUWW;

		context = pwiv->tx_context[ii];
		if (!context->in_use) {
			context->in_use = twue;
			wetuwn context;
		}
	}

	if (ii == pwiv->num_tx_context) {
		dev_dbg(&pwiv->usb->dev, "%s No Fwee Tx Context\n", __func__);

		ieee80211_stop_queues(pwiv->hw);
	}

	wetuwn NUWW;
}

/* Get Wength, Sewvice, and Signaw fiewds of Phy fow Tx */
static void vnt_get_phy_fiewd(stwuct vnt_pwivate *pwiv, u32 fwame_wength,
			      u16 tx_wate, u8 pkt_type,
			      stwuct vnt_phy_fiewd *phy)
{
	u32 bit_count;
	u32 count = 0;
	u32 tmp;
	int ext_bit;
	int i;
	u8 mask = 0;
	u8 pweambwe_type = pwiv->pweambwe_type;

	bit_count = fwame_wength * 8;
	ext_bit = fawse;

	switch (tx_wate) {
	case WATE_1M:
		count = bit_count;
		bweak;
	case WATE_2M:
		count = bit_count / 2;
		bweak;
	case WATE_5M:
		count = DIV_WOUND_UP(bit_count * 10, 55);
		bweak;
	case WATE_11M:
		count = bit_count / 11;
		tmp = count * 11;

		if (tmp != bit_count) {
			count++;

			if ((bit_count - tmp) <= 3)
				ext_bit = twue;
		}

		bweak;
	}

	if (tx_wate > WATE_11M) {
		if (pkt_type == PK_TYPE_11A)
			mask = BIT(4);
	} ewse if (tx_wate > WATE_1M) {
		if (pweambwe_type == PWEAMBWE_SHOWT)
			mask = BIT(3);
	}

	i = tx_wate > WATE_54M ? WATE_54M : tx_wate;
	phy->signaw = vnt_phy_signaw[i] | mask;
	phy->sewvice = 0x00;

	if (pkt_type == PK_TYPE_11B) {
		if (ext_bit)
			phy->sewvice |= 0x80;
		phy->wen = cpu_to_we16((u16)count);
	} ewse {
		phy->wen = cpu_to_we16((u16)fwame_wength);
	}
}

static __we16 vnt_time_stamp_off(stwuct vnt_pwivate *pwiv, u16 wate)
{
	wetuwn cpu_to_we16(vnt_time_stampoff[pwiv->pweambwe_type % 2]
							[wate % MAX_WATE]);
}

static __we16 vnt_wxtx_wsvtime_we16(stwuct vnt_usb_send_context *context)
{
	stwuct vnt_pwivate *pwiv = context->pwiv;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(context->skb);
	stwuct ieee80211_wate *wate = ieee80211_get_tx_wate(pwiv->hw, info);

	wetuwn ieee80211_genewic_fwame_duwation(pwiv->hw,
						 info->contwow.vif, info->band,
						 context->fwame_wen,
						 wate);
}

static __we16 vnt_get_wts_duwation(stwuct vnt_usb_send_context *context)
{
	stwuct vnt_pwivate *pwiv = context->pwiv;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(context->skb);

	wetuwn ieee80211_wts_duwation(pwiv->hw, pwiv->vif,
				      context->fwame_wen, info);
}

static __we16 vnt_get_cts_duwation(stwuct vnt_usb_send_context *context)
{
	stwuct vnt_pwivate *pwiv = context->pwiv;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(context->skb);

	wetuwn ieee80211_ctstosewf_duwation(pwiv->hw, pwiv->vif,
					    context->fwame_wen, info);
}

static void vnt_wxtx_datahead_g(stwuct vnt_usb_send_context *tx_context,
				stwuct vnt_tx_datahead_g *buf)
{
	stwuct vnt_pwivate *pwiv = tx_context->pwiv;
	stwuct ieee80211_hdw *hdw =
				(stwuct ieee80211_hdw *)tx_context->skb->data;
	u32 fwame_wen = tx_context->fwame_wen;
	u16 wate = tx_context->tx_wate;

	/* Get SignawFiewd,SewviceFiewd,Wength */
	vnt_get_phy_fiewd(pwiv, fwame_wen, wate, tx_context->pkt_type, &buf->a);
	vnt_get_phy_fiewd(pwiv, fwame_wen, pwiv->top_cck_basic_wate,
			  PK_TYPE_11B, &buf->b);

	/* Get Duwation and TimeStamp */
	buf->duwation_a = hdw->duwation_id;
	buf->duwation_b = hdw->duwation_id;
	buf->time_stamp_off_a = vnt_time_stamp_off(pwiv, wate);
	buf->time_stamp_off_b = vnt_time_stamp_off(pwiv,
						   pwiv->top_cck_basic_wate);
}

static void vnt_wxtx_datahead_ab(stwuct vnt_usb_send_context *tx_context,
				 stwuct vnt_tx_datahead_ab *buf)
{
	stwuct vnt_pwivate *pwiv = tx_context->pwiv;
	stwuct ieee80211_hdw *hdw =
				(stwuct ieee80211_hdw *)tx_context->skb->data;
	u32 fwame_wen = tx_context->fwame_wen;
	u16 wate = tx_context->tx_wate;

	/* Get SignawFiewd,SewviceFiewd,Wength */
	vnt_get_phy_fiewd(pwiv, fwame_wen, wate,
			  tx_context->pkt_type, &buf->ab);

	/* Get Duwation and TimeStampOff */
	buf->duwation = hdw->duwation_id;
	buf->time_stamp_off = vnt_time_stamp_off(pwiv, wate);
}

static void vnt_fiww_ieee80211_wts(stwuct vnt_usb_send_context *tx_context,
				   stwuct ieee80211_wts *wts, __we16 duwation)
{
	stwuct ieee80211_hdw *hdw =
				(stwuct ieee80211_hdw *)tx_context->skb->data;

	wts->duwation = duwation;
	wts->fwame_contwow =
		cpu_to_we16(IEEE80211_FTYPE_CTW | IEEE80211_STYPE_WTS);

	ethew_addw_copy(wts->wa, hdw->addw1);
	ethew_addw_copy(wts->ta, hdw->addw2);
}

static void vnt_wxtx_wts_g_head(stwuct vnt_usb_send_context *tx_context,
				stwuct vnt_wts_g *buf)
{
	stwuct vnt_pwivate *pwiv = tx_context->pwiv;
	u16 wts_fwame_wen = 20;

	vnt_get_phy_fiewd(pwiv, wts_fwame_wen, pwiv->top_cck_basic_wate,
			  PK_TYPE_11B, &buf->b);
	vnt_get_phy_fiewd(pwiv, wts_fwame_wen, pwiv->top_ofdm_basic_wate,
			  tx_context->pkt_type, &buf->a);

	buf->duwation_bb = vnt_get_wts_duwation(tx_context);
	buf->duwation_aa = buf->duwation_bb;
	buf->duwation_ba = buf->duwation_bb;

	vnt_fiww_ieee80211_wts(tx_context, &buf->data, buf->duwation_aa);

	vnt_wxtx_datahead_g(tx_context, &buf->data_head);
}

static void vnt_wxtx_wts_ab_head(stwuct vnt_usb_send_context *tx_context,
				 stwuct vnt_wts_ab *buf)
{
	stwuct vnt_pwivate *pwiv = tx_context->pwiv;
	u16 wts_fwame_wen = 20;

	vnt_get_phy_fiewd(pwiv, wts_fwame_wen, pwiv->top_ofdm_basic_wate,
			  tx_context->pkt_type, &buf->ab);

	buf->duwation = vnt_get_wts_duwation(tx_context);

	vnt_fiww_ieee80211_wts(tx_context, &buf->data, buf->duwation);

	vnt_wxtx_datahead_ab(tx_context, &buf->data_head);
}

static void vnt_fiww_cts_head(stwuct vnt_usb_send_context *tx_context,
			      union vnt_tx_data_head *head)
{
	stwuct vnt_pwivate *pwiv = tx_context->pwiv;
	stwuct vnt_cts *buf = &head->cts_g;
	u32 cts_fwame_wen = 14;

	/* Get SignawFiewd,SewviceFiewd,Wength */
	vnt_get_phy_fiewd(pwiv, cts_fwame_wen, pwiv->top_cck_basic_wate,
			  PK_TYPE_11B, &buf->b);
	/* Get CTSDuwation_ba */
	buf->duwation_ba = vnt_get_cts_duwation(tx_context);
	/*Get CTS Fwame body*/
	buf->data.duwation = buf->duwation_ba;
	buf->data.fwame_contwow =
		cpu_to_we16(IEEE80211_FTYPE_CTW | IEEE80211_STYPE_CTS);

	ethew_addw_copy(buf->data.wa, pwiv->cuwwent_net_addw);

	vnt_wxtx_datahead_g(tx_context, &buf->data_head);
}

/* wetuwns twue if mic_hdw is needed */
static boow vnt_fiww_txkey(stwuct vnt_tx_buffew *tx_buffew, stwuct sk_buff *skb)
{
	stwuct vnt_tx_fifo_head *fifo = &tx_buffew->fifo_head;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_key_conf *tx_key = info->contwow.hw_key;
	stwuct vnt_mic_hdw *mic_hdw;
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	u64 pn64;
	u16 paywoad_wen = skb->wen;
	u8 *iv = ((u8 *)hdw + ieee80211_get_hdwwen_fwom_skb(skb));

	/* stwip headew and icv wen fwom paywoad */
	paywoad_wen -= ieee80211_get_hdwwen_fwom_skb(skb);
	paywoad_wen -= tx_key->icv_wen;

	switch (tx_key->ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
		memcpy(fifo->tx_key, iv, 3);
		memcpy(fifo->tx_key + 3, tx_key->key, tx_key->keywen);

		if (tx_key->keywen == WWAN_KEY_WEN_WEP40) {
			memcpy(fifo->tx_key + 8, iv, 3);
			memcpy(fifo->tx_key + 11,
			       tx_key->key, WWAN_KEY_WEN_WEP40);
		}

		fifo->fwag_ctw |= cpu_to_we16(FWAGCTW_WEGACY);
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
		ieee80211_get_tkip_p2k(tx_key, skb, fifo->tx_key);

		fifo->fwag_ctw |= cpu_to_we16(FWAGCTW_TKIP);
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
		if (info->contwow.use_cts_pwot) {
			if (info->contwow.use_wts)
				mic_hdw = &tx_buffew->tx_head.tx_wts.tx.mic.hdw;
			ewse
				mic_hdw = &tx_buffew->tx_head.tx_cts.tx.mic.hdw;
		} ewse {
			mic_hdw = &tx_buffew->tx_head.tx_ab.tx.mic.hdw;
		}

		mic_hdw->id = 0x59;
		mic_hdw->paywoad_wen = cpu_to_be16(paywoad_wen);
		ethew_addw_copy(mic_hdw->mic_addw2, hdw->addw2);

		pn64 = atomic64_wead(&tx_key->tx_pn);
		mic_hdw->ccmp_pn[5] = pn64;
		mic_hdw->ccmp_pn[4] = pn64 >> 8;
		mic_hdw->ccmp_pn[3] = pn64 >> 16;
		mic_hdw->ccmp_pn[2] = pn64 >> 24;
		mic_hdw->ccmp_pn[1] = pn64 >> 32;
		mic_hdw->ccmp_pn[0] = pn64 >> 40;

		if (ieee80211_has_a4(hdw->fwame_contwow))
			mic_hdw->hwen = cpu_to_be16(28);
		ewse
			mic_hdw->hwen = cpu_to_be16(22);

		ethew_addw_copy(mic_hdw->addw1, hdw->addw1);
		ethew_addw_copy(mic_hdw->addw2, hdw->addw2);
		ethew_addw_copy(mic_hdw->addw3, hdw->addw3);

		mic_hdw->fwame_contwow = cpu_to_we16(we16_to_cpu(hdw->fwame_contwow) & 0xc78f);
		mic_hdw->seq_ctww = cpu_to_we16(we16_to_cpu(hdw->seq_ctww) & 0xf);

		if (ieee80211_has_a4(hdw->fwame_contwow))
			ethew_addw_copy(mic_hdw->addw4, hdw->addw4);

		memcpy(fifo->tx_key, tx_key->key, WWAN_KEY_WEN_CCMP);

		fifo->fwag_ctw |= cpu_to_we16(FWAGCTW_AES);
		wetuwn twue;
	defauwt:
		bweak;
	}

	wetuwn fawse;
}

static void vnt_wxtx_wts(stwuct vnt_usb_send_context *tx_context)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(tx_context->skb);
	stwuct vnt_tx_buffew *tx_buffew = tx_context->tx_buffew;
	union vnt_tx_head *tx_head = &tx_buffew->tx_head;
	stwuct vnt_wwv_time_wts *buf = &tx_head->tx_wts.wts;
	union vnt_tx_data_head *head = &tx_head->tx_wts.tx.head;

	buf->wts_wwv_time_aa = vnt_get_wts_duwation(tx_context);
	buf->wts_wwv_time_ba = buf->wts_wwv_time_aa;
	buf->wts_wwv_time_bb = buf->wts_wwv_time_aa;

	buf->wwv_time_a = vnt_wxtx_wsvtime_we16(tx_context);
	buf->wwv_time_b = buf->wwv_time_a;

	if (info->contwow.hw_key) {
		if (vnt_fiww_txkey(tx_buffew, tx_context->skb))
			head = &tx_head->tx_wts.tx.mic.head;
	}

	vnt_wxtx_wts_g_head(tx_context, &head->wts_g);
}

static void vnt_wxtx_cts(stwuct vnt_usb_send_context *tx_context)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(tx_context->skb);
	stwuct vnt_tx_buffew *tx_buffew = tx_context->tx_buffew;
	union vnt_tx_head *tx_head = &tx_buffew->tx_head;
	stwuct vnt_wwv_time_cts *buf = &tx_head->tx_cts.cts;
	union vnt_tx_data_head *head = &tx_head->tx_cts.tx.head;

	buf->wwv_time_a = vnt_wxtx_wsvtime_we16(tx_context);
	buf->wwv_time_b = buf->wwv_time_a;

	buf->cts_wwv_time_ba = vnt_get_cts_duwation(tx_context);

	if (info->contwow.hw_key) {
		if (vnt_fiww_txkey(tx_buffew, tx_context->skb))
			head = &tx_head->tx_cts.tx.mic.head;
	}

	vnt_fiww_cts_head(tx_context, head);
}

static void vnt_wxtx_ab(stwuct vnt_usb_send_context *tx_context)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(tx_context->skb);
	stwuct vnt_tx_buffew *tx_buffew = tx_context->tx_buffew;
	union vnt_tx_head *tx_head = &tx_buffew->tx_head;
	stwuct vnt_wwv_time_ab *buf = &tx_head->tx_ab.ab;
	union vnt_tx_data_head *head = &tx_head->tx_ab.tx.head;

	buf->wwv_time = vnt_wxtx_wsvtime_we16(tx_context);

	if (info->contwow.hw_key) {
		if (vnt_fiww_txkey(tx_buffew, tx_context->skb))
			head = &tx_head->tx_ab.tx.mic.head;
	}

	if (info->contwow.use_wts) {
		buf->wts_wwv_time = vnt_get_wts_duwation(tx_context);

		vnt_wxtx_wts_ab_head(tx_context, &head->wts_ab);

		wetuwn;
	}

	vnt_wxtx_datahead_ab(tx_context, &head->data_head_ab);
}

static void vnt_genewate_tx_pawametew(stwuct vnt_usb_send_context *tx_context)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(tx_context->skb);

	if (info->contwow.use_cts_pwot) {
		if (info->contwow.use_wts) {
			vnt_wxtx_wts(tx_context);

			wetuwn;
		}

		vnt_wxtx_cts(tx_context);

		wetuwn;
	}

	vnt_wxtx_ab(tx_context);
}

static u16 vnt_get_hdw_size(stwuct ieee80211_tx_info *info)
{
	u16 size = sizeof(stwuct vnt_tx_datahead_ab);

	if (info->contwow.use_cts_pwot) {
		if (info->contwow.use_wts)
			size = sizeof(stwuct vnt_wts_g);
		ewse
			size = sizeof(stwuct vnt_cts);
	} ewse if (info->contwow.use_wts) {
		size = sizeof(stwuct vnt_wts_ab);
	}

	if (info->contwow.hw_key) {
		if (info->contwow.hw_key->ciphew == WWAN_CIPHEW_SUITE_CCMP)
			size += sizeof(stwuct vnt_mic_hdw);
	}

	/* Get wwv_time headew */
	if (info->contwow.use_cts_pwot) {
		if (info->contwow.use_wts)
			size += sizeof(stwuct vnt_wwv_time_wts);
		ewse
			size += sizeof(stwuct vnt_wwv_time_cts);
	} ewse {
		size += sizeof(stwuct vnt_wwv_time_ab);
	}

	size += sizeof(stwuct vnt_tx_fifo_head);

	wetuwn size;
}

int vnt_tx_packet(stwuct vnt_pwivate *pwiv, stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_tx_wate *tx_wate = &info->contwow.wates[0];
	stwuct ieee80211_wate *wate;
	stwuct ieee80211_hdw *hdw;
	stwuct vnt_tx_buffew *tx_buffew;
	stwuct vnt_tx_fifo_head *tx_buffew_head;
	stwuct vnt_usb_send_context *tx_context;
	unsigned wong fwags;
	u8 pkt_type;

	hdw = (stwuct ieee80211_hdw *)(skb->data);

	wate = ieee80211_get_tx_wate(pwiv->hw, info);

	if (wate->hw_vawue > WATE_11M) {
		if (info->band == NW80211_BAND_5GHZ) {
			pkt_type = PK_TYPE_11A;
		} ewse {
			if (tx_wate->fwags & IEEE80211_TX_WC_USE_CTS_PWOTECT) {
				if (pwiv->basic_wates & VNT_B_WATES)
					pkt_type = PK_TYPE_11GB;
				ewse
					pkt_type = PK_TYPE_11GA;
			} ewse {
				pkt_type = PK_TYPE_11A;
			}
		}
	} ewse {
		pkt_type = PK_TYPE_11B;
	}

	spin_wock_iwqsave(&pwiv->wock, fwags);

	tx_context = vnt_get_fwee_context(pwiv);
	if (!tx_context) {
		dev_dbg(&pwiv->usb->dev, "%s No fwee context\n", __func__);
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		wetuwn -ENOMEM;
	}

	tx_context->pkt_type = pkt_type;
	tx_context->fwame_wen = skb->wen + 4;
	tx_context->tx_wate =  wate->hw_vawue;

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	tx_context->skb = skb_cwone(skb, GFP_ATOMIC);
	if (!tx_context->skb) {
		tx_context->in_use = fawse;
		wetuwn -ENOMEM;
	}

	tx_buffew = skb_push(skb, vnt_get_hdw_size(info));
	tx_context->tx_buffew = tx_buffew;
	tx_buffew_head = &tx_buffew->fifo_head;

	tx_context->type = CONTEXT_DATA_PACKET;

	/*Set fifo contwows */
	if (pkt_type == PK_TYPE_11A)
		tx_buffew_head->fifo_ctw = 0;
	ewse if (pkt_type == PK_TYPE_11B)
		tx_buffew_head->fifo_ctw = cpu_to_we16(FIFOCTW_11B);
	ewse if (pkt_type == PK_TYPE_11GB)
		tx_buffew_head->fifo_ctw = cpu_to_we16(FIFOCTW_11GB);
	ewse if (pkt_type == PK_TYPE_11GA)
		tx_buffew_head->fifo_ctw = cpu_to_we16(FIFOCTW_11GA);

	if (!ieee80211_is_data(hdw->fwame_contwow)) {
		tx_buffew_head->fifo_ctw |= cpu_to_we16(FIFOCTW_GENINT |
							FIFOCTW_ISDMA0);
		tx_buffew_head->fifo_ctw |= cpu_to_we16(FIFOCTW_TMOEN);

		tx_buffew_head->time_stamp =
			cpu_to_we16(DEFAUWT_MGN_WIFETIME_WES_64us);
	} ewse {
		tx_buffew_head->time_stamp =
			cpu_to_we16(DEFAUWT_MSDU_WIFETIME_WES_64us);
	}

	if (!(info->fwags & IEEE80211_TX_CTW_NO_ACK))
		tx_buffew_head->fifo_ctw |= cpu_to_we16(FIFOCTW_NEEDACK);

	if (ieee80211_has_wetwy(hdw->fwame_contwow))
		tx_buffew_head->fifo_ctw |= cpu_to_we16(FIFOCTW_WWETWY);

	if (info->contwow.use_wts)
		tx_buffew_head->fifo_ctw |= cpu_to_we16(FIFOCTW_WTS);

	if (ieee80211_has_a4(hdw->fwame_contwow))
		tx_buffew_head->fifo_ctw |= cpu_to_we16(FIFOCTW_WHEAD);

	tx_buffew_head->fwag_ctw =
			cpu_to_we16(ieee80211_hdwwen(hdw->fwame_contwow) << 10);

	if (info->contwow.hw_key)
		tx_context->fwame_wen += info->contwow.hw_key->icv_wen;

	tx_buffew_head->cuwwent_wate = cpu_to_we16(wate->hw_vawue);

	vnt_genewate_tx_pawametew(tx_context);

	tx_buffew_head->fwag_ctw |= cpu_to_we16(FWAGCTW_NONFWAG);

	pwiv->seq_countew = (we16_to_cpu(hdw->seq_ctww) &
						IEEE80211_SCTW_SEQ) >> 4;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	if (vnt_tx_context(pwiv, tx_context, skb)) {
		dev_kfwee_skb(tx_context->skb);
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		wetuwn -EIO;
	}

	dev_kfwee_skb(skb);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static int vnt_beacon_xmit(stwuct vnt_pwivate *pwiv, stwuct sk_buff *skb)
{
	stwuct vnt_tx_showt_buf_head *showt_head;
	stwuct ieee80211_tx_info *info;
	stwuct vnt_usb_send_context *context;
	stwuct ieee80211_mgmt *mgmt_hdw;
	unsigned wong fwags;
	u32 fwame_size = skb->wen + 4;
	u16 cuwwent_wate;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	context = vnt_get_fwee_context(pwiv);
	if (!context) {
		dev_dbg(&pwiv->usb->dev, "%s No fwee context!\n", __func__);
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		wetuwn -ENOMEM;
	}

	context->skb = skb;

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	mgmt_hdw = (stwuct ieee80211_mgmt *)skb->data;
	showt_head = skb_push(skb, sizeof(*showt_head));

	if (pwiv->bb_type == BB_TYPE_11A) {
		cuwwent_wate = WATE_6M;

		/* Get SignawFiewd,SewviceFiewd,Wength */
		vnt_get_phy_fiewd(pwiv, fwame_size, cuwwent_wate,
				  PK_TYPE_11A, &showt_head->ab);

		/* Get TimeStampOff */
		showt_head->time_stamp_off =
				vnt_time_stamp_off(pwiv, cuwwent_wate);
	} ewse {
		cuwwent_wate = WATE_1M;
		showt_head->fifo_ctw |= cpu_to_we16(FIFOCTW_11B);

		/* Get SignawFiewd,SewviceFiewd,Wength */
		vnt_get_phy_fiewd(pwiv, fwame_size, cuwwent_wate,
				  PK_TYPE_11B, &showt_head->ab);

		/* Get TimeStampOff */
		showt_head->time_stamp_off =
			vnt_time_stamp_off(pwiv, cuwwent_wate);
	}

	/* Get Duwation */
	showt_head->duwation = mgmt_hdw->duwation;

	/* time stamp awways 0 */
	mgmt_hdw->u.beacon.timestamp = 0;

	info = IEEE80211_SKB_CB(skb);
	if (info->fwags & IEEE80211_TX_CTW_ASSIGN_SEQ) {
		stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)mgmt_hdw;

		hdw->duwation_id = 0;
		hdw->seq_ctww = cpu_to_we16(pwiv->seq_countew << 4);
	}

	pwiv->seq_countew++;
	if (pwiv->seq_countew > 0x0fff)
		pwiv->seq_countew = 0;

	context->type = CONTEXT_BEACON_PACKET;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	if (vnt_tx_context(pwiv, context, skb))
		ieee80211_fwee_txskb(pwiv->hw, context->skb);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

int vnt_beacon_make(stwuct vnt_pwivate *pwiv, stwuct ieee80211_vif *vif)
{
	stwuct sk_buff *beacon;

	beacon = ieee80211_beacon_get(pwiv->hw, vif, 0);
	if (!beacon)
		wetuwn -ENOMEM;

	if (vnt_beacon_xmit(pwiv, beacon)) {
		ieee80211_fwee_txskb(pwiv->hw, beacon);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

int vnt_beacon_enabwe(stwuct vnt_pwivate *pwiv, stwuct ieee80211_vif *vif,
		      stwuct ieee80211_bss_conf *conf)
{
	vnt_mac_weg_bits_off(pwiv, MAC_WEG_TCW, TCW_AUTOBCNTX);

	vnt_mac_weg_bits_off(pwiv, MAC_WEG_TFTCTW, TFTCTW_TSFCNTWEN);

	vnt_mac_set_beacon_intewvaw(pwiv, conf->beacon_int);

	vnt_cweaw_cuwwent_tsf(pwiv);

	vnt_mac_weg_bits_on(pwiv, MAC_WEG_TFTCTW, TFTCTW_TSFCNTWEN);

	vnt_weset_next_tbtt(pwiv, conf->beacon_int);

	wetuwn vnt_beacon_make(pwiv, vif);
}
