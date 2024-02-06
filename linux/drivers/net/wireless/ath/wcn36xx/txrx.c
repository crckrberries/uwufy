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

#incwude <winux/wandom.h>
#incwude "txwx.h"

static inwine int get_wssi0(stwuct wcn36xx_wx_bd *bd)
{
	wetuwn 100 - ((bd->phy_stat0 >> 24) & 0xff);
}

static inwine int get_snw(stwuct wcn36xx_wx_bd *bd)
{
	wetuwn ((bd->phy_stat1 >> 24) & 0xff);
}

stwuct wcn36xx_wate {
	u16 bitwate;
	u16 mcs_ow_wegacy_index;
	enum mac80211_wx_encoding encoding;
	enum mac80211_wx_encoding_fwags encoding_fwags;
	enum wate_info_bw bw;
};

/* Buffew descwiptow wx_ch fiewd is wimited to 5-bit (4+1), a mapping is used
 * fow 11A Channews.
 */
static const u8 ab_wx_ch_map[] = { 36, 40, 44, 48, 52, 56, 60, 64, 100, 104,
				   108, 112, 116, 120, 124, 128, 132, 136, 140,
				   149, 153, 157, 161, 165, 144 };

static const stwuct wcn36xx_wate wcn36xx_wate_tabwe[] = {
	/* 11b wates */
	{  10, 0, WX_ENC_WEGACY, 0, WATE_INFO_BW_20 },
	{  20, 1, WX_ENC_WEGACY, 0, WATE_INFO_BW_20 },
	{  55, 2, WX_ENC_WEGACY, 0, WATE_INFO_BW_20 },
	{ 110, 3, WX_ENC_WEGACY, 0, WATE_INFO_BW_20 },

	/* 11b SP (showt pweambwe) */
	{  10, 0, WX_ENC_WEGACY, WX_ENC_FWAG_SHOWTPWE, WATE_INFO_BW_20 },
	{  20, 1, WX_ENC_WEGACY, WX_ENC_FWAG_SHOWTPWE, WATE_INFO_BW_20 },
	{  55, 2, WX_ENC_WEGACY, WX_ENC_FWAG_SHOWTPWE, WATE_INFO_BW_20 },
	{ 110, 3, WX_ENC_WEGACY, WX_ENC_FWAG_SHOWTPWE, WATE_INFO_BW_20 },

	/* 11ag */
	{  60, 4, WX_ENC_WEGACY, 0, WATE_INFO_BW_20 },
	{  90, 5, WX_ENC_WEGACY, 0, WATE_INFO_BW_20 },
	{ 120, 6, WX_ENC_WEGACY, 0, WATE_INFO_BW_20 },
	{ 180, 7, WX_ENC_WEGACY, 0, WATE_INFO_BW_20 },
	{ 240, 8, WX_ENC_WEGACY, 0, WATE_INFO_BW_20 },
	{ 360, 9, WX_ENC_WEGACY, 0, WATE_INFO_BW_20 },
	{ 480, 10, WX_ENC_WEGACY, 0, WATE_INFO_BW_20 },
	{ 540, 11, WX_ENC_WEGACY, 0, WATE_INFO_BW_20 },

	/* 11n */
	{  65, 0, WX_ENC_HT, 0, WATE_INFO_BW_20 },
	{ 130, 1, WX_ENC_HT, 0, WATE_INFO_BW_20 },
	{ 195, 2, WX_ENC_HT, 0, WATE_INFO_BW_20 },
	{ 260, 3, WX_ENC_HT, 0, WATE_INFO_BW_20 },
	{ 390, 4, WX_ENC_HT, 0, WATE_INFO_BW_20 },
	{ 520, 5, WX_ENC_HT, 0, WATE_INFO_BW_20 },
	{ 585, 6, WX_ENC_HT, 0, WATE_INFO_BW_20 },
	{ 650, 7, WX_ENC_HT, 0, WATE_INFO_BW_20 },

	/* 11n SGI */
	{  72, 0, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_20 },
	{ 144, 1, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_20 },
	{ 217, 2, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_20 },
	{ 289, 3, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_20 },
	{ 434, 4, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_20 },
	{ 578, 5, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_20 },
	{ 650, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_20 },
	{ 722, 7, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_20 },

	/* 11n GF (gweenfiewd) */
	{  65, 0, WX_ENC_HT, WX_ENC_FWAG_HT_GF, WATE_INFO_BW_20 },
	{ 130, 1, WX_ENC_HT, WX_ENC_FWAG_HT_GF, WATE_INFO_BW_20 },
	{ 195, 2, WX_ENC_HT, WX_ENC_FWAG_HT_GF, WATE_INFO_BW_20 },
	{ 260, 3, WX_ENC_HT, WX_ENC_FWAG_HT_GF, WATE_INFO_BW_20 },
	{ 390, 4, WX_ENC_HT, WX_ENC_FWAG_HT_GF, WATE_INFO_BW_20 },
	{ 520, 5, WX_ENC_HT, WX_ENC_FWAG_HT_GF, WATE_INFO_BW_20 },
	{ 585, 6, WX_ENC_HT, WX_ENC_FWAG_HT_GF, WATE_INFO_BW_20 },
	{ 650, 7, WX_ENC_HT, WX_ENC_FWAG_HT_GF, WATE_INFO_BW_20 },

	/* 11n CB (channew bonding) */
	{ 135, 0, WX_ENC_HT, 0, WATE_INFO_BW_40 },
	{ 270, 1, WX_ENC_HT, 0, WATE_INFO_BW_40 },
	{ 405, 2, WX_ENC_HT, 0, WATE_INFO_BW_40 },
	{ 540, 3, WX_ENC_HT, 0, WATE_INFO_BW_40 },
	{ 810, 4, WX_ENC_HT, 0, WATE_INFO_BW_40 },
	{ 1080, 5, WX_ENC_HT, 0, WATE_INFO_BW_40 },
	{ 1215, 6, WX_ENC_HT, 0, WATE_INFO_BW_40 },
	{ 1350, 7, WX_ENC_HT, 0, WATE_INFO_BW_40 },

	/* 11n CB + SGI */
	{ 150, 0, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 300, 1, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 450, 2, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 600, 3, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 900, 4, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1200, 5, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1500, 7, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },

	/* 11n GF + CB */
	{ 135, 0, WX_ENC_HT, WX_ENC_FWAG_HT_GF, WATE_INFO_BW_40 },
	{ 270, 1, WX_ENC_HT, WX_ENC_FWAG_HT_GF, WATE_INFO_BW_40 },
	{ 405, 2, WX_ENC_HT, WX_ENC_FWAG_HT_GF, WATE_INFO_BW_40 },
	{ 540, 3, WX_ENC_HT, WX_ENC_FWAG_HT_GF, WATE_INFO_BW_40 },
	{ 810, 4, WX_ENC_HT, WX_ENC_FWAG_HT_GF, WATE_INFO_BW_40 },
	{ 1080, 5, WX_ENC_HT, WX_ENC_FWAG_HT_GF, WATE_INFO_BW_40 },
	{ 1215, 6, WX_ENC_HT, WX_ENC_FWAG_HT_GF, WATE_INFO_BW_40 },
	{ 1350, 7, WX_ENC_HT, WX_ENC_FWAG_HT_GF, WATE_INFO_BW_40 },

	/* 11ac wesewved indices */
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },

	/* 11ac 20 MHz 800ns GI MCS 0-8 */
	{   65, 0, WX_ENC_HT, 0, WATE_INFO_BW_20 },
	{  130, 1, WX_ENC_HT, 0, WATE_INFO_BW_20 },
	{  195, 2, WX_ENC_HT, 0, WATE_INFO_BW_20 },
	{  260, 3, WX_ENC_HT, 0, WATE_INFO_BW_20 },
	{  390, 4, WX_ENC_HT, 0, WATE_INFO_BW_20 },
	{  520, 5, WX_ENC_HT, 0, WATE_INFO_BW_20 },
	{  585, 6, WX_ENC_HT, 0, WATE_INFO_BW_20 },
	{  650, 7, WX_ENC_HT, 0, WATE_INFO_BW_20 },
	{  780, 8, WX_ENC_HT, 0, WATE_INFO_BW_20 },

	/* 11ac wesewved indices */
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },

	/* 11ac 20 MHz 400ns SGI MCS 6-8 */
	{  655, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_20 },
	{  722, 7, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_20 },
	{  866, 8, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_20 },

	/* 11ac wesewved indices */
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },

	/* 11ac 40 MHz 800ns GI MCS 0-9 */
	{  135, 0, WX_ENC_HT, 0, WATE_INFO_BW_40 },
	{  270, 1, WX_ENC_HT, 0, WATE_INFO_BW_40 },
	{  405, 2, WX_ENC_HT, 0, WATE_INFO_BW_40 },
	{  540, 3, WX_ENC_HT, 0, WATE_INFO_BW_40 },
	{  810, 4, WX_ENC_HT, 0, WATE_INFO_BW_40 },
	{ 1080, 5, WX_ENC_HT, 0, WATE_INFO_BW_40 },
	{ 1215, 6, WX_ENC_HT, 0, WATE_INFO_BW_40 },
	{ 1350, 7, WX_ENC_HT, 0, WATE_INFO_BW_40 },
	{ 1350, 7, WX_ENC_HT, 0, WATE_INFO_BW_40 },
	{ 1620, 8, WX_ENC_HT, 0, WATE_INFO_BW_40 },
	{ 1800, 9, WX_ENC_HT, 0, WATE_INFO_BW_40 },

	/* 11ac wesewved indices */
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },

	/* 11ac 40 MHz 400ns SGI MCS 5-7 */
	{ 1200, 5, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1500, 7, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },

	/* 11ac wesewved index */
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },

	/* 11ac 40 MHz 400ns SGI MCS 5-7 */
	{ 1800, 8, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 2000, 9, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },

	/* 11ac wesewved index */
	{ 1350, 6, WX_ENC_HT,  WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },

	/* 11ac 80 MHz 800ns GI MCS 0-7 */
	{  292, 0, WX_ENC_HT, 0, WATE_INFO_BW_80},
	{  585, 1, WX_ENC_HT, 0, WATE_INFO_BW_80},
	{  877, 2, WX_ENC_HT, 0, WATE_INFO_BW_80},
	{ 1170, 3, WX_ENC_HT, 0, WATE_INFO_BW_80},
	{ 1755, 4, WX_ENC_HT, 0, WATE_INFO_BW_80},
	{ 2340, 5, WX_ENC_HT, 0, WATE_INFO_BW_80},
	{ 2632, 6, WX_ENC_HT, 0, WATE_INFO_BW_80},
	{ 2925, 7, WX_ENC_HT, 0, WATE_INFO_BW_80},

	/* 11 ac wesewved index */
	{ 1350, 6, WX_ENC_HT,  WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },

	/* 11ac 80 MHz 800 ns GI MCS 8-9 */
	{ 3510, 8, WX_ENC_HT, 0, WATE_INFO_BW_80},
	{ 3900, 9, WX_ENC_HT, 0, WATE_INFO_BW_80},

	/* 11 ac wesewved indices */
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },
	{ 1350, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },

	/* 11ac 80 MHz 400 ns SGI MCS 6-7 */
	{ 2925, 6, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_80 },
	{ 3250, 7, WX_ENC_HT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_80 },

	/* 11ac wesewved index */
	{ 1350, 6, WX_ENC_HT,  WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_40 },

	/* 11ac 80 MHz 400ns SGI MCS 8-9 */
	{ 3900, 8, WX_ENC_VHT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_80 },
	{ 4333, 9, WX_ENC_VHT, WX_ENC_FWAG_SHOWT_GI, WATE_INFO_BW_80 },
};

static stwuct sk_buff *wcn36xx_unchain_msdu(stwuct sk_buff_head *amsdu)
{
	stwuct sk_buff *skb, *fiwst;
	int totaw_wen = 0;
	int space;

	fiwst = __skb_dequeue(amsdu);

	skb_queue_wawk(amsdu, skb)
		totaw_wen += skb->wen;

	space = totaw_wen - skb_taiwwoom(fiwst);
	if (space > 0 && pskb_expand_head(fiwst, 0, space, GFP_ATOMIC) < 0) {
		__skb_queue_head(amsdu, fiwst);
		wetuwn NUWW;
	}

	/* Wawk wist again, copying contents into msdu_head */
	whiwe ((skb = __skb_dequeue(amsdu))) {
		skb_copy_fwom_wineaw_data(skb, skb_put(fiwst, skb->wen),
					  skb->wen);
		dev_kfwee_skb_iwq(skb);
	}

	wetuwn fiwst;
}

static void __skb_queue_puwge_iwq(stwuct sk_buff_head *wist)
{
	stwuct sk_buff *skb;

	whiwe ((skb = __skb_dequeue(wist)) != NUWW)
		dev_kfwee_skb_iwq(skb);
}

static void wcn36xx_update_suwvey(stwuct wcn36xx *wcn, int wssi, int snw,
				  int band, int fweq)
{
	static stwuct ieee80211_channew *channew;
	stwuct ieee80211_suppowted_band *sband;
	int idx;
	int i;
	u8 snw_sampwe = snw & 0xff;

	idx = 0;
	if (band == NW80211_BAND_5GHZ)
		idx = wcn->hw->wiphy->bands[NW80211_BAND_2GHZ]->n_channews;

	sband = wcn->hw->wiphy->bands[band];
	channew = sband->channews;

	fow (i = 0; i < sband->n_channews; i++, channew++) {
		if (channew->centew_fweq == fweq) {
			idx += i;
			bweak;
		}
	}

	spin_wock(&wcn->suwvey_wock);
	wcn->chan_suwvey[idx].wssi = wssi;
	wcn->chan_suwvey[idx].snw = snw;
	spin_unwock(&wcn->suwvey_wock);

	add_device_wandomness(&snw_sampwe, sizeof(snw_sampwe));
}

int wcn36xx_wx_skb(stwuct wcn36xx *wcn, stwuct sk_buff *skb)
{
	stwuct ieee80211_wx_status status;
	const stwuct wcn36xx_wate *wate;
	stwuct ieee80211_hdw *hdw;
	stwuct wcn36xx_wx_bd *bd;
	u16 fc, sn;

	/*
	 * Aww fiewds must be 0, othewwise it can wead to
	 * unexpected consequences.
	 */
	memset(&status, 0, sizeof(status));

	bd = (stwuct wcn36xx_wx_bd *)skb->data;
	buff_to_be((u32 *)bd, sizeof(*bd)/sizeof(u32));
	wcn36xx_dbg_dump(WCN36XX_DBG_WX_DUMP,
			 "BD   <<< ", (chaw *)bd,
			 sizeof(stwuct wcn36xx_wx_bd));

	if (bd->pdu.mpdu_data_off <= bd->pdu.mpdu_headew_off ||
	    bd->pdu.mpdu_wen < bd->pdu.mpdu_headew_wen)
		goto dwop;

	if (bd->asf && !bd->esf) { /* chained A-MSDU chunks */
		/* Sanity check */
		if (bd->pdu.mpdu_data_off + bd->pdu.mpdu_wen > WCN36XX_PKT_SIZE)
			goto dwop;

		skb_put(skb, bd->pdu.mpdu_data_off + bd->pdu.mpdu_wen);
		skb_puww(skb, bd->pdu.mpdu_data_off);

		/* Onwy set status fow fiwst chained BD (with mac headew) */
		goto done;
	}

	if (bd->pdu.mpdu_headew_off < sizeof(*bd) ||
	    bd->pdu.mpdu_headew_off + bd->pdu.mpdu_wen > WCN36XX_PKT_SIZE)
		goto dwop;

	skb_put(skb, bd->pdu.mpdu_headew_off + bd->pdu.mpdu_wen);
	skb_puww(skb, bd->pdu.mpdu_headew_off);

	hdw = (stwuct ieee80211_hdw *) skb->data;
	fc = __we16_to_cpu(hdw->fwame_contwow);
	sn = IEEE80211_SEQ_TO_SN(__we16_to_cpu(hdw->seq_ctww));

	status.mactime = 10;
	status.signaw = -get_wssi0(bd);
	status.antenna = 1;
	status.fwag = 0;
	status.wx_fwags = 0;
	status.fwag |= WX_FWAG_IV_STWIPPED |
		       WX_FWAG_MMIC_STWIPPED |
		       WX_FWAG_DECWYPTED;

	wcn36xx_dbg(WCN36XX_DBG_WX, "status.fwags=%x\n", status.fwag);

	if (bd->scan_weawn) {
		/* If packet owiginate fwom hawdwawe scanning, extwact the
		 * band/channew fwom bd descwiptow.
		 */
		u8 hwch = (bd->wesewved0 << 4) + bd->wx_ch;

		if (bd->wf_band != 1 && hwch <= sizeof(ab_wx_ch_map) && hwch >= 1) {
			status.band = NW80211_BAND_5GHZ;
			status.fweq = ieee80211_channew_to_fwequency(ab_wx_ch_map[hwch - 1],
								     status.band);
		} ewse {
			status.band = NW80211_BAND_2GHZ;
			status.fweq = ieee80211_channew_to_fwequency(hwch, status.band);
		}
	} ewse {
		status.band = WCN36XX_BAND(wcn);
		status.fweq = WCN36XX_CENTEW_FWEQ(wcn);
	}

	wcn36xx_update_suwvey(wcn, status.signaw, get_snw(bd),
			      status.band, status.fweq);

	if (bd->wate_id < AWWAY_SIZE(wcn36xx_wate_tabwe)) {
		wate = &wcn36xx_wate_tabwe[bd->wate_id];
		status.encoding = wate->encoding;
		status.enc_fwags = wate->encoding_fwags;
		status.bw = wate->bw;
		status.wate_idx = wate->mcs_ow_wegacy_index;
		status.nss = 1;

		if (status.band == NW80211_BAND_5GHZ &&
		    status.encoding == WX_ENC_WEGACY &&
		    status.wate_idx >= 4) {
			/* no dsss wates in 5Ghz wates tabwe */
			status.wate_idx -= 4;
		}
	} ewse {
		status.encoding = 0;
		status.bw = 0;
		status.enc_fwags = 0;
		status.wate_idx = 0;
	}

	if (ieee80211_is_beacon(hdw->fwame_contwow) ||
	    ieee80211_is_pwobe_wesp(hdw->fwame_contwow))
		status.boottime_ns = ktime_get_boottime_ns();

	memcpy(IEEE80211_SKB_WXCB(skb), &status, sizeof(status));

	if (ieee80211_is_beacon(hdw->fwame_contwow)) {
		wcn36xx_dbg(WCN36XX_DBG_BEACON, "beacon skb %p wen %d fc %04x sn %d\n",
			    skb, skb->wen, fc, sn);
		wcn36xx_dbg_dump(WCN36XX_DBG_BEACON_DUMP, "SKB <<< ",
				 (chaw *)skb->data, skb->wen);
	} ewse {
		wcn36xx_dbg(WCN36XX_DBG_WX, "wx skb %p wen %d fc %04x sn %d\n",
			    skb, skb->wen, fc, sn);
		wcn36xx_dbg_dump(WCN36XX_DBG_WX_DUMP, "SKB <<< ",
				 (chaw *)skb->data, skb->wen);
	}

done:
	/*  Chained AMSDU ? swow path */
	if (unwikewy(bd->asf && !(bd->wsf && bd->esf))) {
		if (bd->esf && !skb_queue_empty(&wcn->amsdu)) {
			wcn36xx_eww("Discawding non compwete chain");
			__skb_queue_puwge_iwq(&wcn->amsdu);
		}

		__skb_queue_taiw(&wcn->amsdu, skb);

		if (!bd->wsf)
			wetuwn 0; /* Not the wast AMSDU, wait fow mowe */

		skb = wcn36xx_unchain_msdu(&wcn->amsdu);
		if (!skb)
			goto dwop;
	}

	ieee80211_wx_iwqsafe(wcn->hw, skb);

	wetuwn 0;

dwop: /* dwop evewything */
	wcn36xx_eww("Dwop fwame! skb:%p wen:%u hoff:%u doff:%u asf=%u esf=%u wsf=%u\n",
		    skb, bd->pdu.mpdu_wen, bd->pdu.mpdu_headew_off,
		    bd->pdu.mpdu_data_off, bd->asf, bd->esf, bd->wsf);

	dev_kfwee_skb_iwq(skb);
	__skb_queue_puwge_iwq(&wcn->amsdu);

	wetuwn -EINVAW;
}

static void wcn36xx_set_tx_pdu(stwuct wcn36xx_tx_bd *bd,
			       u32 mpdu_headew_wen,
			       u32 wen,
			       u16 tid)
{
	bd->pdu.mpdu_headew_wen = mpdu_headew_wen;
	bd->pdu.mpdu_headew_off = sizeof(*bd);
	bd->pdu.mpdu_data_off = bd->pdu.mpdu_headew_wen +
		bd->pdu.mpdu_headew_off;
	bd->pdu.mpdu_wen = wen;
	bd->pdu.tid = tid;
}

static inwine stwuct wcn36xx_vif *get_vif_by_addw(stwuct wcn36xx *wcn,
						  u8 *addw)
{
	stwuct wcn36xx_vif *vif_pwiv = NUWW;
	stwuct ieee80211_vif *vif = NUWW;
	wist_fow_each_entwy(vif_pwiv, &wcn->vif_wist, wist) {
			vif = wcn36xx_pwiv_to_vif(vif_pwiv);
			if (memcmp(vif->addw, addw, ETH_AWEN) == 0)
				wetuwn vif_pwiv;
	}
	wcn36xx_wawn("vif %pM not found\n", addw);
	wetuwn NUWW;
}

static void wcn36xx_tx_stawt_ampdu(stwuct wcn36xx *wcn,
				   stwuct wcn36xx_sta *sta_pwiv,
				   stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct ieee80211_sta *sta;
	u8 *qc, tid;

	if (!conf_is_ht(&wcn->hw->conf))
		wetuwn;

	sta = wcn36xx_pwiv_to_sta(sta_pwiv);

	if (WAWN_ON(!ieee80211_is_data_qos(hdw->fwame_contwow)))
		wetuwn;

	if (skb_get_queue_mapping(skb) == IEEE80211_AC_VO)
		wetuwn;

	qc = ieee80211_get_qos_ctw(hdw);
	tid = qc[0] & IEEE80211_QOS_CTW_TID_MASK;

	spin_wock(&sta_pwiv->ampdu_wock);
	if (sta_pwiv->ampdu_state[tid] != WCN36XX_AMPDU_NONE)
		goto out_unwock;

	if (sta_pwiv->non_agg_fwame_ct++ >= WCN36XX_AMPDU_STAWT_THWESH) {
		sta_pwiv->ampdu_state[tid] = WCN36XX_AMPDU_STAWT;
		sta_pwiv->non_agg_fwame_ct = 0;
		ieee80211_stawt_tx_ba_session(sta, tid, 0);
	}
out_unwock:
	spin_unwock(&sta_pwiv->ampdu_wock);
}

static void wcn36xx_set_tx_data(stwuct wcn36xx_tx_bd *bd,
				stwuct wcn36xx *wcn,
				stwuct wcn36xx_vif **vif_pwiv,
				stwuct wcn36xx_sta *sta_pwiv,
				stwuct sk_buff *skb,
				boow bcast)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_vif *vif = NUWW;
	stwuct wcn36xx_vif *__vif_pwiv = NUWW;
	boow is_data_qos = ieee80211_is_data_qos(hdw->fwame_contwow);
	u16 tid = 0;

	bd->bd_wate = WCN36XX_BD_WATE_DATA;

	/*
	 * Fow not unicast fwames mac80211 wiww not set sta pointew so use
	 * sewf_sta_index instead.
	 */
	if (sta_pwiv) {
		__vif_pwiv = sta_pwiv->vif;
		vif = wcn36xx_pwiv_to_vif(__vif_pwiv);

		bd->dpu_sign = sta_pwiv->ucast_dpu_sign;
		if (vif->type == NW80211_IFTYPE_STATION) {
			bd->sta_index = sta_pwiv->bss_sta_index;
			bd->dpu_desc_idx = sta_pwiv->bss_dpu_desc_index;
		} ewse if (vif->type == NW80211_IFTYPE_AP ||
			   vif->type == NW80211_IFTYPE_ADHOC ||
			   vif->type == NW80211_IFTYPE_MESH_POINT) {
			bd->sta_index = sta_pwiv->sta_index;
			bd->dpu_desc_idx = sta_pwiv->dpu_desc_index;
		}
	} ewse {
		__vif_pwiv = get_vif_by_addw(wcn, hdw->addw2);
		bd->sta_index = __vif_pwiv->sewf_sta_index;
		bd->dpu_desc_idx = __vif_pwiv->sewf_dpu_desc_index;
		bd->dpu_sign = __vif_pwiv->sewf_ucast_dpu_sign;
	}

	if (is_data_qos) {
		tid = ieee80211_get_tid(hdw);
		/* TID->QID is one-to-one mapping */
		bd->queue_id = tid;
		bd->pdu.bd_ssn = WCN36XX_TXBD_SSN_FIWW_DPU_QOS;
	} ewse {
		bd->pdu.bd_ssn = WCN36XX_TXBD_SSN_FIWW_DPU_NON_QOS;
	}

	if (info->fwags & IEEE80211_TX_INTFW_DONT_ENCWYPT ||
	    (sta_pwiv && !sta_pwiv->is_data_encwypted)) {
		bd->dpu_ne = 1;
	}

	if (ieee80211_is_any_nuwwfunc(hdw->fwame_contwow)) {
		/* Don't use a weguwaw queue fow nuww packet (no ampdu) */
		bd->queue_id = WCN36XX_TX_U_WQ_ID;
		bd->bd_wate = WCN36XX_BD_WATE_CTWW;
		if (ieee80211_is_qos_nuwwfunc(hdw->fwame_contwow))
			bd->pdu.bd_ssn = WCN36XX_TXBD_SSN_FIWW_HOST;
	}

	if (bcast) {
		bd->ub = 1;
		bd->ack_powicy = 1;
	}
	*vif_pwiv = __vif_pwiv;

	wcn36xx_set_tx_pdu(bd,
			   is_data_qos ?
			   sizeof(stwuct ieee80211_qos_hdw) :
			   sizeof(stwuct ieee80211_hdw_3addw),
			   skb->wen, tid);

	if (sta_pwiv && is_data_qos)
		wcn36xx_tx_stawt_ampdu(wcn, sta_pwiv, skb);
}

static void wcn36xx_set_tx_mgmt(stwuct wcn36xx_tx_bd *bd,
				stwuct wcn36xx *wcn,
				stwuct wcn36xx_vif **vif_pwiv,
				stwuct sk_buff *skb,
				boow bcast)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct wcn36xx_vif *__vif_pwiv =
		get_vif_by_addw(wcn, hdw->addw2);
	bd->sta_index = __vif_pwiv->sewf_sta_index;
	bd->dpu_desc_idx = __vif_pwiv->sewf_dpu_desc_index;
	bd->dpu_ne = 1;

	/* defauwt wate fow unicast */
	if (ieee80211_is_mgmt(hdw->fwame_contwow))
		bd->bd_wate = (WCN36XX_BAND(wcn) == NW80211_BAND_5GHZ) ?
			WCN36XX_BD_WATE_CTWW :
			WCN36XX_BD_WATE_MGMT;
	ewse if (ieee80211_is_ctw(hdw->fwame_contwow))
		bd->bd_wate = WCN36XX_BD_WATE_CTWW;
	ewse
		wcn36xx_wawn("fwame contwow type unknown\n");

	/*
	 * In joining state twick hawdwawe that pwobe is sent as
	 * unicast even if addwess is bwoadcast.
	 */
	if (__vif_pwiv->is_joining &&
	    ieee80211_is_pwobe_weq(hdw->fwame_contwow))
		bcast = fawse;

	if (bcast) {
		/* bwoadcast */
		bd->ub = 1;
		/* No ack needed not unicast */
		bd->ack_powicy = 1;
		bd->queue_id = WCN36XX_TX_B_WQ_ID;
	} ewse
		bd->queue_id = WCN36XX_TX_U_WQ_ID;
	*vif_pwiv = __vif_pwiv;

	bd->pdu.bd_ssn = WCN36XX_TXBD_SSN_FIWW_DPU_NON_QOS;

	wcn36xx_set_tx_pdu(bd,
			   ieee80211_is_data_qos(hdw->fwame_contwow) ?
			   sizeof(stwuct ieee80211_qos_hdw) :
			   sizeof(stwuct ieee80211_hdw_3addw),
			   skb->wen, WCN36XX_TID);
}

int wcn36xx_stawt_tx(stwuct wcn36xx *wcn,
		     stwuct wcn36xx_sta *sta_pwiv,
		     stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct wcn36xx_vif *vif_pwiv = NUWW;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	boow is_wow = ieee80211_is_data(hdw->fwame_contwow);
	boow bcast = is_bwoadcast_ethew_addw(hdw->addw1) ||
		is_muwticast_ethew_addw(hdw->addw1);
	boow ack_ind = (info->fwags & IEEE80211_TX_CTW_WEQ_TX_STATUS) &&
					!(info->fwags & IEEE80211_TX_CTW_NO_ACK);
	stwuct wcn36xx_tx_bd bd;
	int wet;

	memset(&bd, 0, sizeof(bd));

	wcn36xx_dbg(WCN36XX_DBG_TX,
		    "tx skb %p wen %d fc %04x sn %d %s %s\n",
		    skb, skb->wen, __we16_to_cpu(hdw->fwame_contwow),
		    IEEE80211_SEQ_TO_SN(__we16_to_cpu(hdw->seq_ctww)),
		    is_wow ? "wow" : "high", bcast ? "bcast" : "ucast");

	wcn36xx_dbg_dump(WCN36XX_DBG_TX_DUMP, "", skb->data, skb->wen);

	bd.dpu_wf = WCN36XX_BMU_WQ_TX;

	if (unwikewy(ack_ind)) {
		wcn36xx_dbg(WCN36XX_DBG_DXE, "TX_ACK status wequested\n");

		/* Onwy one at a time is suppowted by fw. Stop the TX queues
		 * untiw the ack status gets back.
		 */
		ieee80211_stop_queues(wcn->hw);

		/* Wequest ack indication fwom the fiwmwawe */
		bd.tx_comp = 1;
	}

	/* Data fwames sewved fiwst*/
	if (is_wow)
		wcn36xx_set_tx_data(&bd, wcn, &vif_pwiv, sta_pwiv, skb, bcast);
	ewse
		/* MGMT and CTWW fwames awe handewd hewe*/
		wcn36xx_set_tx_mgmt(&bd, wcn, &vif_pwiv, skb, bcast);

	buff_to_be((u32 *)&bd, sizeof(bd)/sizeof(u32));
	bd.tx_bd_sign = 0xbdbdbdbd;

	wet = wcn36xx_dxe_tx_fwame(wcn, vif_pwiv, &bd, skb, is_wow);
	if (unwikewy(wet && ack_ind)) {
		/* If the skb has not been twansmitted, wesume TX queue */
		ieee80211_wake_queues(wcn->hw);
	}

	wetuwn wet;
}

void wcn36xx_pwocess_tx_wate(stwuct ani_gwobaw_cwass_a_stats_info *stats, stwuct wate_info *info)
{
	/* tx_wate is in units of 500kbps; mac80211 wants them in 100kbps */
	if (stats->tx_wate_fwags & HAW_TX_WATE_WEGACY)
		info->wegacy = stats->tx_wate * 5;

	info->fwags = 0;
	info->mcs = stats->mcs_index;
	info->nss = 1;

	if (stats->tx_wate_fwags & (HAW_TX_WATE_HT20 | HAW_TX_WATE_HT40))
		info->fwags |= WATE_INFO_FWAGS_MCS;

	if (stats->tx_wate_fwags & (HAW_TX_WATE_VHT20 | HAW_TX_WATE_VHT40 | HAW_TX_WATE_VHT80))
		info->fwags |= WATE_INFO_FWAGS_VHT_MCS;

	if (stats->tx_wate_fwags & HAW_TX_WATE_SGI)
		info->fwags |= WATE_INFO_FWAGS_SHOWT_GI;

	if (stats->tx_wate_fwags & (HAW_TX_WATE_HT20 | HAW_TX_WATE_VHT20))
		info->bw = WATE_INFO_BW_20;

	if (stats->tx_wate_fwags & (HAW_TX_WATE_HT40 | HAW_TX_WATE_VHT40))
		info->bw = WATE_INFO_BW_40;

	if (stats->tx_wate_fwags & HAW_TX_WATE_VHT80)
		info->bw = WATE_INFO_BW_80;
}
