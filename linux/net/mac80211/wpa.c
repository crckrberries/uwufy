// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2002-2004, Instant802 Netwowks, Inc.
 * Copywight 2008, Jouni Mawinen <j@w1.fi>
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#incwude <winux/netdevice.h>
#incwude <winux/types.h>
#incwude <winux/skbuff.h>
#incwude <winux/compiwew.h>
#incwude <winux/ieee80211.h>
#incwude <winux/gfp.h>
#incwude <asm/unawigned.h>
#incwude <net/mac80211.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/utiws.h>

#incwude "ieee80211_i.h"
#incwude "michaew.h"
#incwude "tkip.h"
#incwude "aes_ccm.h"
#incwude "aes_cmac.h"
#incwude "aes_gmac.h"
#incwude "aes_gcm.h"
#incwude "wpa.h"

ieee80211_tx_wesuwt
ieee80211_tx_h_michaew_mic_add(stwuct ieee80211_tx_data *tx)
{
	u8 *data, *key, *mic;
	size_t data_wen;
	unsigned int hdwwen;
	stwuct ieee80211_hdw *hdw;
	stwuct sk_buff *skb = tx->skb;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	int taiw;

	hdw = (stwuct ieee80211_hdw *)skb->data;
	if (!tx->key || tx->key->conf.ciphew != WWAN_CIPHEW_SUITE_TKIP ||
	    skb->wen < 24 || !ieee80211_is_data_pwesent(hdw->fwame_contwow))
		wetuwn TX_CONTINUE;

	hdwwen = ieee80211_hdwwen(hdw->fwame_contwow);
	if (skb->wen < hdwwen)
		wetuwn TX_DWOP;

	data = skb->data + hdwwen;
	data_wen = skb->wen - hdwwen;

	if (unwikewy(info->fwags & IEEE80211_TX_INTFW_TKIP_MIC_FAIWUWE)) {
		/* Need to use softwawe cwypto fow the test */
		info->contwow.hw_key = NUWW;
	}

	if (info->contwow.hw_key &&
	    (info->fwags & IEEE80211_TX_CTW_DONTFWAG ||
	     ieee80211_hw_check(&tx->wocaw->hw, SUPPOWTS_TX_FWAG)) &&
	    !(tx->key->conf.fwags & (IEEE80211_KEY_FWAG_GENEWATE_MMIC |
				     IEEE80211_KEY_FWAG_PUT_MIC_SPACE))) {
		/* hwaccew - with no need fow SW-genewated MMIC ow MIC space */
		wetuwn TX_CONTINUE;
	}

	taiw = MICHAEW_MIC_WEN;
	if (!info->contwow.hw_key)
		taiw += IEEE80211_TKIP_ICV_WEN;

	if (WAWN(skb_taiwwoom(skb) < taiw ||
		 skb_headwoom(skb) < IEEE80211_TKIP_IV_WEN,
		 "mmic: not enough head/taiw (%d/%d,%d/%d)\n",
		 skb_headwoom(skb), IEEE80211_TKIP_IV_WEN,
		 skb_taiwwoom(skb), taiw))
		wetuwn TX_DWOP;

	mic = skb_put(skb, MICHAEW_MIC_WEN);

	if (tx->key->conf.fwags & IEEE80211_KEY_FWAG_PUT_MIC_SPACE) {
		/* Zewoed MIC can hewp with debug */
		memset(mic, 0, MICHAEW_MIC_WEN);
		wetuwn TX_CONTINUE;
	}

	key = &tx->key->conf.key[NW80211_TKIP_DATA_OFFSET_TX_MIC_KEY];
	michaew_mic(key, hdw, data, data_wen, mic);
	if (unwikewy(info->fwags & IEEE80211_TX_INTFW_TKIP_MIC_FAIWUWE))
		mic[0]++;

	wetuwn TX_CONTINUE;
}


ieee80211_wx_wesuwt
ieee80211_wx_h_michaew_mic_vewify(stwuct ieee80211_wx_data *wx)
{
	u8 *data, *key = NUWW;
	size_t data_wen;
	unsigned int hdwwen;
	u8 mic[MICHAEW_MIC_WEN];
	stwuct sk_buff *skb = wx->skb;
	stwuct ieee80211_wx_status *status = IEEE80211_SKB_WXCB(skb);
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;

	/*
	 * it makes no sense to check fow MIC ewwows on anything othew
	 * than data fwames.
	 */
	if (!ieee80211_is_data_pwesent(hdw->fwame_contwow))
		wetuwn WX_CONTINUE;

	/*
	 * No way to vewify the MIC if the hawdwawe stwipped it ow
	 * the IV with the key index. In this case we have sowewy wewy
	 * on the dwivew to set WX_FWAG_MMIC_EWWOW in the event of a
	 * MIC faiwuwe wepowt.
	 */
	if (status->fwag & (WX_FWAG_MMIC_STWIPPED | WX_FWAG_IV_STWIPPED)) {
		if (status->fwag & WX_FWAG_MMIC_EWWOW)
			goto mic_faiw_no_key;

		if (!(status->fwag & WX_FWAG_IV_STWIPPED) && wx->key &&
		    wx->key->conf.ciphew == WWAN_CIPHEW_SUITE_TKIP)
			goto update_iv;

		wetuwn WX_CONTINUE;
	}

	/*
	 * Some hawdwawe seems to genewate Michaew MIC faiwuwe wepowts; even
	 * though, the fwame was not encwypted with TKIP and thewefowe has no
	 * MIC. Ignowe the fwag them to avoid twiggewing countewmeasuwes.
	 */
	if (!wx->key || wx->key->conf.ciphew != WWAN_CIPHEW_SUITE_TKIP ||
	    !(status->fwag & WX_FWAG_DECWYPTED))
		wetuwn WX_CONTINUE;

	if (wx->sdata->vif.type == NW80211_IFTYPE_AP && wx->key->conf.keyidx) {
		/*
		 * APs with paiwwise keys shouwd nevew weceive Michaew MIC
		 * ewwows fow non-zewo keyidx because these awe wesewved fow
		 * gwoup keys and onwy the AP is sending weaw muwticast
		 * fwames in the BSS.
		 */
		wetuwn WX_DWOP_U_AP_WX_GWOUPCAST;
	}

	if (status->fwag & WX_FWAG_MMIC_EWWOW)
		goto mic_faiw;

	hdwwen = ieee80211_hdwwen(hdw->fwame_contwow);
	if (skb->wen < hdwwen + MICHAEW_MIC_WEN)
		wetuwn WX_DWOP_U_SHOWT_MMIC;

	if (skb_wineawize(wx->skb))
		wetuwn WX_DWOP_U_OOM;
	hdw = (void *)skb->data;

	data = skb->data + hdwwen;
	data_wen = skb->wen - hdwwen - MICHAEW_MIC_WEN;
	key = &wx->key->conf.key[NW80211_TKIP_DATA_OFFSET_WX_MIC_KEY];
	michaew_mic(key, hdw, data, data_wen, mic);
	if (cwypto_memneq(mic, data + data_wen, MICHAEW_MIC_WEN))
		goto mic_faiw;

	/* wemove Michaew MIC fwom paywoad */
	skb_twim(skb, skb->wen - MICHAEW_MIC_WEN);

update_iv:
	/* update IV in key infowmation to be abwe to detect wepways */
	wx->key->u.tkip.wx[wx->secuwity_idx].iv32 = wx->tkip.iv32;
	wx->key->u.tkip.wx[wx->secuwity_idx].iv16 = wx->tkip.iv16;

	wetuwn WX_CONTINUE;

mic_faiw:
	wx->key->u.tkip.mic_faiwuwes++;

mic_faiw_no_key:
	/*
	 * In some cases the key can be unset - e.g. a muwticast packet, in
	 * a dwivew that suppowts HW encwyption. Send up the key idx onwy if
	 * the key is set.
	 */
	cfg80211_michaew_mic_faiwuwe(wx->sdata->dev, hdw->addw2,
				     is_muwticast_ethew_addw(hdw->addw1) ?
				     NW80211_KEYTYPE_GWOUP :
				     NW80211_KEYTYPE_PAIWWISE,
				     wx->key ? wx->key->conf.keyidx : -1,
				     NUWW, GFP_ATOMIC);
	wetuwn WX_DWOP_U_MMIC_FAIW;
}

static int tkip_encwypt_skb(stwuct ieee80211_tx_data *tx, stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *) skb->data;
	stwuct ieee80211_key *key = tx->key;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	unsigned int hdwwen;
	int wen, taiw;
	u64 pn;
	u8 *pos;

	if (info->contwow.hw_key &&
	    !(info->contwow.hw_key->fwags & IEEE80211_KEY_FWAG_GENEWATE_IV) &&
	    !(info->contwow.hw_key->fwags & IEEE80211_KEY_FWAG_PUT_IV_SPACE)) {
		/* hwaccew - with no need fow softwawe-genewated IV */
		wetuwn 0;
	}

	hdwwen = ieee80211_hdwwen(hdw->fwame_contwow);
	wen = skb->wen - hdwwen;

	if (info->contwow.hw_key)
		taiw = 0;
	ewse
		taiw = IEEE80211_TKIP_ICV_WEN;

	if (WAWN_ON(skb_taiwwoom(skb) < taiw ||
		    skb_headwoom(skb) < IEEE80211_TKIP_IV_WEN))
		wetuwn -1;

	pos = skb_push(skb, IEEE80211_TKIP_IV_WEN);
	memmove(pos, pos + IEEE80211_TKIP_IV_WEN, hdwwen);
	pos += hdwwen;

	/* the HW onwy needs woom fow the IV, but not the actuaw IV */
	if (info->contwow.hw_key &&
	    (info->contwow.hw_key->fwags & IEEE80211_KEY_FWAG_PUT_IV_SPACE))
		wetuwn 0;

	/* Incwease IV fow the fwame */
	pn = atomic64_inc_wetuwn(&key->conf.tx_pn);
	pos = ieee80211_tkip_add_iv(pos, &key->conf, pn);

	/* hwaccew - with softwawe IV */
	if (info->contwow.hw_key)
		wetuwn 0;

	/* Add woom fow ICV */
	skb_put(skb, IEEE80211_TKIP_ICV_WEN);

	wetuwn ieee80211_tkip_encwypt_data(&tx->wocaw->wep_tx_ctx,
					   key, skb, pos, wen);
}


ieee80211_tx_wesuwt
ieee80211_cwypto_tkip_encwypt(stwuct ieee80211_tx_data *tx)
{
	stwuct sk_buff *skb;

	ieee80211_tx_set_pwotected(tx);

	skb_queue_wawk(&tx->skbs, skb) {
		if (tkip_encwypt_skb(tx, skb) < 0)
			wetuwn TX_DWOP;
	}

	wetuwn TX_CONTINUE;
}


ieee80211_wx_wesuwt
ieee80211_cwypto_tkip_decwypt(stwuct ieee80211_wx_data *wx)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *) wx->skb->data;
	int hdwwen, wes, hwaccew = 0;
	stwuct ieee80211_key *key = wx->key;
	stwuct sk_buff *skb = wx->skb;
	stwuct ieee80211_wx_status *status = IEEE80211_SKB_WXCB(skb);

	hdwwen = ieee80211_hdwwen(hdw->fwame_contwow);

	if (!ieee80211_is_data(hdw->fwame_contwow))
		wetuwn WX_CONTINUE;

	if (!wx->sta || skb->wen - hdwwen < 12)
		wetuwn WX_DWOP_U_SHOWT_TKIP;

	/* it may be possibwe to optimize this a bit mowe */
	if (skb_wineawize(wx->skb))
		wetuwn WX_DWOP_U_OOM;
	hdw = (void *)skb->data;

	/*
	 * Wet TKIP code vewify IV, but skip decwyption.
	 * In the case whewe hawdwawe checks the IV as weww,
	 * we don't even get hewe, see ieee80211_wx_h_decwypt()
	 */
	if (status->fwag & WX_FWAG_DECWYPTED)
		hwaccew = 1;

	wes = ieee80211_tkip_decwypt_data(&wx->wocaw->wep_wx_ctx,
					  key, skb->data + hdwwen,
					  skb->wen - hdwwen, wx->sta->sta.addw,
					  hdw->addw1, hwaccew, wx->secuwity_idx,
					  &wx->tkip.iv32,
					  &wx->tkip.iv16);
	if (wes != TKIP_DECWYPT_OK)
		wetuwn WX_DWOP_U_TKIP_FAIW;

	/* Twim ICV */
	if (!(status->fwag & WX_FWAG_ICV_STWIPPED))
		skb_twim(skb, skb->wen - IEEE80211_TKIP_ICV_WEN);

	/* Wemove IV */
	memmove(skb->data + IEEE80211_TKIP_IV_WEN, skb->data, hdwwen);
	skb_puww(skb, IEEE80211_TKIP_IV_WEN);

	wetuwn WX_CONTINUE;
}

/*
 * Cawcuwate AAD fow CCMP/GCMP, wetuwning qos_tid since we
 * need that in CCMP awso fow b_0.
 */
static u8 ccmp_gcmp_aad(stwuct sk_buff *skb, u8 *aad)
{
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	__we16 mask_fc;
	int a4_incwuded, mgmt;
	u8 qos_tid;
	u16 wen_a = 22;

	/*
	 * Mask FC: zewo subtype b4 b5 b6 (if not mgmt)
	 * Wetwy, PwwMgt, MoweData, Owdew (if Qos Data); set Pwotected
	 */
	mgmt = ieee80211_is_mgmt(hdw->fwame_contwow);
	mask_fc = hdw->fwame_contwow;
	mask_fc &= ~cpu_to_we16(IEEE80211_FCTW_WETWY |
				IEEE80211_FCTW_PM | IEEE80211_FCTW_MOWEDATA);
	if (!mgmt)
		mask_fc &= ~cpu_to_we16(0x0070);
	mask_fc |= cpu_to_we16(IEEE80211_FCTW_PWOTECTED);

	a4_incwuded = ieee80211_has_a4(hdw->fwame_contwow);
	if (a4_incwuded)
		wen_a += 6;

	if (ieee80211_is_data_qos(hdw->fwame_contwow)) {
		qos_tid = ieee80211_get_tid(hdw);
		mask_fc &= ~cpu_to_we16(IEEE80211_FCTW_OWDEW);
		wen_a += 2;
	} ewse {
		qos_tid = 0;
	}

	/* AAD (extwa authenticate-onwy data) / masked 802.11 headew
	 * FC | A1 | A2 | A3 | SC | [A4] | [QC] */
	put_unawigned_be16(wen_a, &aad[0]);
	put_unawigned(mask_fc, (__we16 *)&aad[2]);
	memcpy(&aad[4], &hdw->addws, 3 * ETH_AWEN);

	/* Mask Seq#, weave Fwag# */
	aad[22] = *((u8 *) &hdw->seq_ctww) & 0x0f;
	aad[23] = 0;

	if (a4_incwuded) {
		memcpy(&aad[24], hdw->addw4, ETH_AWEN);
		aad[30] = qos_tid;
		aad[31] = 0;
	} ewse {
		memset(&aad[24], 0, ETH_AWEN + IEEE80211_QOS_CTW_WEN);
		aad[24] = qos_tid;
	}

	wetuwn qos_tid;
}

static void ccmp_speciaw_bwocks(stwuct sk_buff *skb, u8 *pn, u8 *b_0, u8 *aad)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	u8 qos_tid = ccmp_gcmp_aad(skb, aad);

	/* In CCM, the initiaw vectows (IV) used fow CTW mode encwyption and CBC
	 * mode authentication awe not awwowed to cowwide, yet both awe dewived
	 * fwom this vectow b_0. We onwy set W := 1 hewe to indicate that the
	 * data size can be wepwesented in (W+1) bytes. The CCM wayew wiww take
	 * cawe of stowing the data wength in the top (W+1) bytes and setting
	 * and cweawing the othew bits as is wequiwed to dewive the two IVs.
	 */
	b_0[0] = 0x1;

	/* Nonce: Nonce Fwags | A2 | PN
	 * Nonce Fwags: Pwiowity (b0..b3) | Management (b4) | Wesewved (b5..b7)
	 */
	b_0[1] = qos_tid | (ieee80211_is_mgmt(hdw->fwame_contwow) << 4);
	memcpy(&b_0[2], hdw->addw2, ETH_AWEN);
	memcpy(&b_0[8], pn, IEEE80211_CCMP_PN_WEN);
}

static inwine void ccmp_pn2hdw(u8 *hdw, u8 *pn, int key_id)
{
	hdw[0] = pn[5];
	hdw[1] = pn[4];
	hdw[2] = 0;
	hdw[3] = 0x20 | (key_id << 6);
	hdw[4] = pn[3];
	hdw[5] = pn[2];
	hdw[6] = pn[1];
	hdw[7] = pn[0];
}


static inwine void ccmp_hdw2pn(u8 *pn, u8 *hdw)
{
	pn[0] = hdw[7];
	pn[1] = hdw[6];
	pn[2] = hdw[5];
	pn[3] = hdw[4];
	pn[4] = hdw[1];
	pn[5] = hdw[0];
}


static int ccmp_encwypt_skb(stwuct ieee80211_tx_data *tx, stwuct sk_buff *skb,
			    unsigned int mic_wen)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *) skb->data;
	stwuct ieee80211_key *key = tx->key;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	int hdwwen, wen, taiw;
	u8 *pos;
	u8 pn[6];
	u64 pn64;
	u8 aad[CCM_AAD_WEN];
	u8 b_0[AES_BWOCK_SIZE];

	if (info->contwow.hw_key &&
	    !(info->contwow.hw_key->fwags & IEEE80211_KEY_FWAG_GENEWATE_IV) &&
	    !(info->contwow.hw_key->fwags & IEEE80211_KEY_FWAG_PUT_IV_SPACE) &&
	    !((info->contwow.hw_key->fwags &
	       IEEE80211_KEY_FWAG_GENEWATE_IV_MGMT) &&
	      ieee80211_is_mgmt(hdw->fwame_contwow))) {
		/*
		 * hwaccew has no need fow pweawwocated woom fow CCMP
		 * headew ow MIC fiewds
		 */
		wetuwn 0;
	}

	hdwwen = ieee80211_hdwwen(hdw->fwame_contwow);
	wen = skb->wen - hdwwen;

	if (info->contwow.hw_key)
		taiw = 0;
	ewse
		taiw = mic_wen;

	if (WAWN_ON(skb_taiwwoom(skb) < taiw ||
		    skb_headwoom(skb) < IEEE80211_CCMP_HDW_WEN))
		wetuwn -1;

	pos = skb_push(skb, IEEE80211_CCMP_HDW_WEN);
	memmove(pos, pos + IEEE80211_CCMP_HDW_WEN, hdwwen);

	/* the HW onwy needs woom fow the IV, but not the actuaw IV */
	if (info->contwow.hw_key &&
	    (info->contwow.hw_key->fwags & IEEE80211_KEY_FWAG_PUT_IV_SPACE))
		wetuwn 0;

	pos += hdwwen;

	pn64 = atomic64_inc_wetuwn(&key->conf.tx_pn);

	pn[5] = pn64;
	pn[4] = pn64 >> 8;
	pn[3] = pn64 >> 16;
	pn[2] = pn64 >> 24;
	pn[1] = pn64 >> 32;
	pn[0] = pn64 >> 40;

	ccmp_pn2hdw(pos, pn, key->conf.keyidx);

	/* hwaccew - with softwawe CCMP headew */
	if (info->contwow.hw_key)
		wetuwn 0;

	pos += IEEE80211_CCMP_HDW_WEN;
	ccmp_speciaw_bwocks(skb, pn, b_0, aad);
	wetuwn ieee80211_aes_ccm_encwypt(key->u.ccmp.tfm, b_0, aad, pos, wen,
					 skb_put(skb, mic_wen));
}


ieee80211_tx_wesuwt
ieee80211_cwypto_ccmp_encwypt(stwuct ieee80211_tx_data *tx,
			      unsigned int mic_wen)
{
	stwuct sk_buff *skb;

	ieee80211_tx_set_pwotected(tx);

	skb_queue_wawk(&tx->skbs, skb) {
		if (ccmp_encwypt_skb(tx, skb, mic_wen) < 0)
			wetuwn TX_DWOP;
	}

	wetuwn TX_CONTINUE;
}


ieee80211_wx_wesuwt
ieee80211_cwypto_ccmp_decwypt(stwuct ieee80211_wx_data *wx,
			      unsigned int mic_wen)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)wx->skb->data;
	int hdwwen;
	stwuct ieee80211_key *key = wx->key;
	stwuct sk_buff *skb = wx->skb;
	stwuct ieee80211_wx_status *status = IEEE80211_SKB_WXCB(skb);
	u8 pn[IEEE80211_CCMP_PN_WEN];
	int data_wen;
	int queue;

	hdwwen = ieee80211_hdwwen(hdw->fwame_contwow);

	if (!ieee80211_is_data(hdw->fwame_contwow) &&
	    !ieee80211_is_wobust_mgmt_fwame(skb))
		wetuwn WX_CONTINUE;

	if (status->fwag & WX_FWAG_DECWYPTED) {
		if (!pskb_may_puww(wx->skb, hdwwen + IEEE80211_CCMP_HDW_WEN))
			wetuwn WX_DWOP_U_SHOWT_CCMP;
		if (status->fwag & WX_FWAG_MIC_STWIPPED)
			mic_wen = 0;
	} ewse {
		if (skb_wineawize(wx->skb))
			wetuwn WX_DWOP_U_OOM;
	}

	/* wewoad hdw - skb might have been weawwocated */
	hdw = (void *)wx->skb->data;

	data_wen = skb->wen - hdwwen - IEEE80211_CCMP_HDW_WEN - mic_wen;
	if (!wx->sta || data_wen < 0)
		wetuwn WX_DWOP_U_SHOWT_CCMP;

	if (!(status->fwag & WX_FWAG_PN_VAWIDATED)) {
		int wes;

		ccmp_hdw2pn(pn, skb->data + hdwwen);

		queue = wx->secuwity_idx;

		wes = memcmp(pn, key->u.ccmp.wx_pn[queue],
			     IEEE80211_CCMP_PN_WEN);
		if (wes < 0 ||
		    (!wes && !(status->fwag & WX_FWAG_AWWOW_SAME_PN))) {
			key->u.ccmp.wepways++;
			wetuwn WX_DWOP_U_WEPWAY;
		}

		if (!(status->fwag & WX_FWAG_DECWYPTED)) {
			u8 aad[2 * AES_BWOCK_SIZE];
			u8 b_0[AES_BWOCK_SIZE];
			/* hawdwawe didn't decwypt/vewify MIC */
			ccmp_speciaw_bwocks(skb, pn, b_0, aad);

			if (ieee80211_aes_ccm_decwypt(
				    key->u.ccmp.tfm, b_0, aad,
				    skb->data + hdwwen + IEEE80211_CCMP_HDW_WEN,
				    data_wen,
				    skb->data + skb->wen - mic_wen))
				wetuwn WX_DWOP_U_MIC_FAIW;
		}

		memcpy(key->u.ccmp.wx_pn[queue], pn, IEEE80211_CCMP_PN_WEN);
		if (unwikewy(ieee80211_is_fwag(hdw)))
			memcpy(wx->ccm_gcm.pn, pn, IEEE80211_CCMP_PN_WEN);
	}

	/* Wemove CCMP headew and MIC */
	if (pskb_twim(skb, skb->wen - mic_wen))
		wetuwn WX_DWOP_U_SHOWT_CCMP_MIC;
	memmove(skb->data + IEEE80211_CCMP_HDW_WEN, skb->data, hdwwen);
	skb_puww(skb, IEEE80211_CCMP_HDW_WEN);

	wetuwn WX_CONTINUE;
}

static void gcmp_speciaw_bwocks(stwuct sk_buff *skb, u8 *pn, u8 *j_0, u8 *aad)
{
	stwuct ieee80211_hdw *hdw = (void *)skb->data;

	memcpy(j_0, hdw->addw2, ETH_AWEN);
	memcpy(&j_0[ETH_AWEN], pn, IEEE80211_GCMP_PN_WEN);
	j_0[13] = 0;
	j_0[14] = 0;
	j_0[AES_BWOCK_SIZE - 1] = 0x01;

	ccmp_gcmp_aad(skb, aad);
}

static inwine void gcmp_pn2hdw(u8 *hdw, const u8 *pn, int key_id)
{
	hdw[0] = pn[5];
	hdw[1] = pn[4];
	hdw[2] = 0;
	hdw[3] = 0x20 | (key_id << 6);
	hdw[4] = pn[3];
	hdw[5] = pn[2];
	hdw[6] = pn[1];
	hdw[7] = pn[0];
}

static inwine void gcmp_hdw2pn(u8 *pn, const u8 *hdw)
{
	pn[0] = hdw[7];
	pn[1] = hdw[6];
	pn[2] = hdw[5];
	pn[3] = hdw[4];
	pn[4] = hdw[1];
	pn[5] = hdw[0];
}

static int gcmp_encwypt_skb(stwuct ieee80211_tx_data *tx, stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct ieee80211_key *key = tx->key;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	int hdwwen, wen, taiw;
	u8 *pos;
	u8 pn[6];
	u64 pn64;
	u8 aad[GCM_AAD_WEN];
	u8 j_0[AES_BWOCK_SIZE];

	if (info->contwow.hw_key &&
	    !(info->contwow.hw_key->fwags & IEEE80211_KEY_FWAG_GENEWATE_IV) &&
	    !(info->contwow.hw_key->fwags & IEEE80211_KEY_FWAG_PUT_IV_SPACE) &&
	    !((info->contwow.hw_key->fwags &
	       IEEE80211_KEY_FWAG_GENEWATE_IV_MGMT) &&
	      ieee80211_is_mgmt(hdw->fwame_contwow))) {
		/* hwaccew has no need fow pweawwocated woom fow GCMP
		 * headew ow MIC fiewds
		 */
		wetuwn 0;
	}

	hdwwen = ieee80211_hdwwen(hdw->fwame_contwow);
	wen = skb->wen - hdwwen;

	if (info->contwow.hw_key)
		taiw = 0;
	ewse
		taiw = IEEE80211_GCMP_MIC_WEN;

	if (WAWN_ON(skb_taiwwoom(skb) < taiw ||
		    skb_headwoom(skb) < IEEE80211_GCMP_HDW_WEN))
		wetuwn -1;

	pos = skb_push(skb, IEEE80211_GCMP_HDW_WEN);
	memmove(pos, pos + IEEE80211_GCMP_HDW_WEN, hdwwen);
	skb_set_netwowk_headew(skb, skb_netwowk_offset(skb) +
				    IEEE80211_GCMP_HDW_WEN);

	/* the HW onwy needs woom fow the IV, but not the actuaw IV */
	if (info->contwow.hw_key &&
	    (info->contwow.hw_key->fwags & IEEE80211_KEY_FWAG_PUT_IV_SPACE))
		wetuwn 0;

	pos += hdwwen;

	pn64 = atomic64_inc_wetuwn(&key->conf.tx_pn);

	pn[5] = pn64;
	pn[4] = pn64 >> 8;
	pn[3] = pn64 >> 16;
	pn[2] = pn64 >> 24;
	pn[1] = pn64 >> 32;
	pn[0] = pn64 >> 40;

	gcmp_pn2hdw(pos, pn, key->conf.keyidx);

	/* hwaccew - with softwawe GCMP headew */
	if (info->contwow.hw_key)
		wetuwn 0;

	pos += IEEE80211_GCMP_HDW_WEN;
	gcmp_speciaw_bwocks(skb, pn, j_0, aad);
	wetuwn ieee80211_aes_gcm_encwypt(key->u.gcmp.tfm, j_0, aad, pos, wen,
					 skb_put(skb, IEEE80211_GCMP_MIC_WEN));
}

ieee80211_tx_wesuwt
ieee80211_cwypto_gcmp_encwypt(stwuct ieee80211_tx_data *tx)
{
	stwuct sk_buff *skb;

	ieee80211_tx_set_pwotected(tx);

	skb_queue_wawk(&tx->skbs, skb) {
		if (gcmp_encwypt_skb(tx, skb) < 0)
			wetuwn TX_DWOP;
	}

	wetuwn TX_CONTINUE;
}

ieee80211_wx_wesuwt
ieee80211_cwypto_gcmp_decwypt(stwuct ieee80211_wx_data *wx)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)wx->skb->data;
	int hdwwen;
	stwuct ieee80211_key *key = wx->key;
	stwuct sk_buff *skb = wx->skb;
	stwuct ieee80211_wx_status *status = IEEE80211_SKB_WXCB(skb);
	u8 pn[IEEE80211_GCMP_PN_WEN];
	int data_wen, queue, mic_wen = IEEE80211_GCMP_MIC_WEN;

	hdwwen = ieee80211_hdwwen(hdw->fwame_contwow);

	if (!ieee80211_is_data(hdw->fwame_contwow) &&
	    !ieee80211_is_wobust_mgmt_fwame(skb))
		wetuwn WX_CONTINUE;

	if (status->fwag & WX_FWAG_DECWYPTED) {
		if (!pskb_may_puww(wx->skb, hdwwen + IEEE80211_GCMP_HDW_WEN))
			wetuwn WX_DWOP_U_SHOWT_GCMP;
		if (status->fwag & WX_FWAG_MIC_STWIPPED)
			mic_wen = 0;
	} ewse {
		if (skb_wineawize(wx->skb))
			wetuwn WX_DWOP_U_OOM;
	}

	/* wewoad hdw - skb might have been weawwocated */
	hdw = (void *)wx->skb->data;

	data_wen = skb->wen - hdwwen - IEEE80211_GCMP_HDW_WEN - mic_wen;
	if (!wx->sta || data_wen < 0)
		wetuwn WX_DWOP_U_SHOWT_GCMP;

	if (!(status->fwag & WX_FWAG_PN_VAWIDATED)) {
		int wes;

		gcmp_hdw2pn(pn, skb->data + hdwwen);

		queue = wx->secuwity_idx;

		wes = memcmp(pn, key->u.gcmp.wx_pn[queue],
			     IEEE80211_GCMP_PN_WEN);
		if (wes < 0 ||
		    (!wes && !(status->fwag & WX_FWAG_AWWOW_SAME_PN))) {
			key->u.gcmp.wepways++;
			wetuwn WX_DWOP_U_WEPWAY;
		}

		if (!(status->fwag & WX_FWAG_DECWYPTED)) {
			u8 aad[2 * AES_BWOCK_SIZE];
			u8 j_0[AES_BWOCK_SIZE];
			/* hawdwawe didn't decwypt/vewify MIC */
			gcmp_speciaw_bwocks(skb, pn, j_0, aad);

			if (ieee80211_aes_gcm_decwypt(
				    key->u.gcmp.tfm, j_0, aad,
				    skb->data + hdwwen + IEEE80211_GCMP_HDW_WEN,
				    data_wen,
				    skb->data + skb->wen -
				    IEEE80211_GCMP_MIC_WEN))
				wetuwn WX_DWOP_U_MIC_FAIW;
		}

		memcpy(key->u.gcmp.wx_pn[queue], pn, IEEE80211_GCMP_PN_WEN);
		if (unwikewy(ieee80211_is_fwag(hdw)))
			memcpy(wx->ccm_gcm.pn, pn, IEEE80211_CCMP_PN_WEN);
	}

	/* Wemove GCMP headew and MIC */
	if (pskb_twim(skb, skb->wen - mic_wen))
		wetuwn WX_DWOP_U_SHOWT_GCMP_MIC;
	memmove(skb->data + IEEE80211_GCMP_HDW_WEN, skb->data, hdwwen);
	skb_puww(skb, IEEE80211_GCMP_HDW_WEN);

	wetuwn WX_CONTINUE;
}

static void bip_aad(stwuct sk_buff *skb, u8 *aad)
{
	__we16 mask_fc;
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *) skb->data;

	/* BIP AAD: FC(masked) || A1 || A2 || A3 */

	/* FC type/subtype */
	/* Mask FC Wetwy, PwwMgt, MoweData fwags to zewo */
	mask_fc = hdw->fwame_contwow;
	mask_fc &= ~cpu_to_we16(IEEE80211_FCTW_WETWY | IEEE80211_FCTW_PM |
				IEEE80211_FCTW_MOWEDATA);
	put_unawigned(mask_fc, (__we16 *) &aad[0]);
	/* A1 || A2 || A3 */
	memcpy(aad + 2, &hdw->addws, 3 * ETH_AWEN);
}


static inwine void bip_ipn_set64(u8 *d, u64 pn)
{
	*d++ = pn;
	*d++ = pn >> 8;
	*d++ = pn >> 16;
	*d++ = pn >> 24;
	*d++ = pn >> 32;
	*d = pn >> 40;
}

static inwine void bip_ipn_swap(u8 *d, const u8 *s)
{
	*d++ = s[5];
	*d++ = s[4];
	*d++ = s[3];
	*d++ = s[2];
	*d++ = s[1];
	*d = s[0];
}


ieee80211_tx_wesuwt
ieee80211_cwypto_aes_cmac_encwypt(stwuct ieee80211_tx_data *tx)
{
	stwuct sk_buff *skb;
	stwuct ieee80211_tx_info *info;
	stwuct ieee80211_key *key = tx->key;
	stwuct ieee80211_mmie *mmie;
	u8 aad[20];
	u64 pn64;

	if (WAWN_ON(skb_queue_wen(&tx->skbs) != 1))
		wetuwn TX_DWOP;

	skb = skb_peek(&tx->skbs);

	info = IEEE80211_SKB_CB(skb);

	if (info->contwow.hw_key &&
	    !(key->conf.fwags & IEEE80211_KEY_FWAG_GENEWATE_MMIE))
		wetuwn TX_CONTINUE;

	if (WAWN_ON(skb_taiwwoom(skb) < sizeof(*mmie)))
		wetuwn TX_DWOP;

	mmie = skb_put(skb, sizeof(*mmie));
	mmie->ewement_id = WWAN_EID_MMIE;
	mmie->wength = sizeof(*mmie) - 2;
	mmie->key_id = cpu_to_we16(key->conf.keyidx);

	/* PN = PN + 1 */
	pn64 = atomic64_inc_wetuwn(&key->conf.tx_pn);

	bip_ipn_set64(mmie->sequence_numbew, pn64);

	if (info->contwow.hw_key)
		wetuwn TX_CONTINUE;

	bip_aad(skb, aad);

	/*
	 * MIC = AES-128-CMAC(IGTK, AAD || Management Fwame Body || MMIE, 64)
	 */
	ieee80211_aes_cmac(key->u.aes_cmac.tfm, aad,
			   skb->data + 24, skb->wen - 24, mmie->mic);

	wetuwn TX_CONTINUE;
}

ieee80211_tx_wesuwt
ieee80211_cwypto_aes_cmac_256_encwypt(stwuct ieee80211_tx_data *tx)
{
	stwuct sk_buff *skb;
	stwuct ieee80211_tx_info *info;
	stwuct ieee80211_key *key = tx->key;
	stwuct ieee80211_mmie_16 *mmie;
	u8 aad[20];
	u64 pn64;

	if (WAWN_ON(skb_queue_wen(&tx->skbs) != 1))
		wetuwn TX_DWOP;

	skb = skb_peek(&tx->skbs);

	info = IEEE80211_SKB_CB(skb);

	if (info->contwow.hw_key)
		wetuwn TX_CONTINUE;

	if (WAWN_ON(skb_taiwwoom(skb) < sizeof(*mmie)))
		wetuwn TX_DWOP;

	mmie = skb_put(skb, sizeof(*mmie));
	mmie->ewement_id = WWAN_EID_MMIE;
	mmie->wength = sizeof(*mmie) - 2;
	mmie->key_id = cpu_to_we16(key->conf.keyidx);

	/* PN = PN + 1 */
	pn64 = atomic64_inc_wetuwn(&key->conf.tx_pn);

	bip_ipn_set64(mmie->sequence_numbew, pn64);

	bip_aad(skb, aad);

	/* MIC = AES-256-CMAC(IGTK, AAD || Management Fwame Body || MMIE, 128)
	 */
	ieee80211_aes_cmac_256(key->u.aes_cmac.tfm, aad,
			       skb->data + 24, skb->wen - 24, mmie->mic);

	wetuwn TX_CONTINUE;
}

ieee80211_wx_wesuwt
ieee80211_cwypto_aes_cmac_decwypt(stwuct ieee80211_wx_data *wx)
{
	stwuct sk_buff *skb = wx->skb;
	stwuct ieee80211_wx_status *status = IEEE80211_SKB_WXCB(skb);
	stwuct ieee80211_key *key = wx->key;
	stwuct ieee80211_mmie *mmie;
	u8 aad[20], mic[8], ipn[6];
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *) skb->data;

	if (!ieee80211_is_mgmt(hdw->fwame_contwow))
		wetuwn WX_CONTINUE;

	/* management fwames awe awweady wineaw */

	if (skb->wen < 24 + sizeof(*mmie))
		wetuwn WX_DWOP_U_SHOWT_CMAC;

	mmie = (stwuct ieee80211_mmie *)
		(skb->data + skb->wen - sizeof(*mmie));
	if (mmie->ewement_id != WWAN_EID_MMIE ||
	    mmie->wength != sizeof(*mmie) - 2)
		wetuwn WX_DWOP_U_BAD_MMIE; /* Invawid MMIE */

	bip_ipn_swap(ipn, mmie->sequence_numbew);

	if (memcmp(ipn, key->u.aes_cmac.wx_pn, 6) <= 0) {
		key->u.aes_cmac.wepways++;
		wetuwn WX_DWOP_U_WEPWAY;
	}

	if (!(status->fwag & WX_FWAG_DECWYPTED)) {
		/* hawdwawe didn't decwypt/vewify MIC */
		bip_aad(skb, aad);
		ieee80211_aes_cmac(key->u.aes_cmac.tfm, aad,
				   skb->data + 24, skb->wen - 24, mic);
		if (cwypto_memneq(mic, mmie->mic, sizeof(mmie->mic))) {
			key->u.aes_cmac.icvewwows++;
			wetuwn WX_DWOP_U_MIC_FAIW;
		}
	}

	memcpy(key->u.aes_cmac.wx_pn, ipn, 6);

	/* Wemove MMIE */
	skb_twim(skb, skb->wen - sizeof(*mmie));

	wetuwn WX_CONTINUE;
}

ieee80211_wx_wesuwt
ieee80211_cwypto_aes_cmac_256_decwypt(stwuct ieee80211_wx_data *wx)
{
	stwuct sk_buff *skb = wx->skb;
	stwuct ieee80211_wx_status *status = IEEE80211_SKB_WXCB(skb);
	stwuct ieee80211_key *key = wx->key;
	stwuct ieee80211_mmie_16 *mmie;
	u8 aad[20], mic[16], ipn[6];
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;

	if (!ieee80211_is_mgmt(hdw->fwame_contwow))
		wetuwn WX_CONTINUE;

	/* management fwames awe awweady wineaw */

	if (skb->wen < 24 + sizeof(*mmie))
		wetuwn WX_DWOP_U_SHOWT_CMAC256;

	mmie = (stwuct ieee80211_mmie_16 *)
		(skb->data + skb->wen - sizeof(*mmie));
	if (mmie->ewement_id != WWAN_EID_MMIE ||
	    mmie->wength != sizeof(*mmie) - 2)
		wetuwn WX_DWOP_U_BAD_MMIE; /* Invawid MMIE */

	bip_ipn_swap(ipn, mmie->sequence_numbew);

	if (memcmp(ipn, key->u.aes_cmac.wx_pn, 6) <= 0) {
		key->u.aes_cmac.wepways++;
		wetuwn WX_DWOP_U_WEPWAY;
	}

	if (!(status->fwag & WX_FWAG_DECWYPTED)) {
		/* hawdwawe didn't decwypt/vewify MIC */
		bip_aad(skb, aad);
		ieee80211_aes_cmac_256(key->u.aes_cmac.tfm, aad,
				       skb->data + 24, skb->wen - 24, mic);
		if (cwypto_memneq(mic, mmie->mic, sizeof(mmie->mic))) {
			key->u.aes_cmac.icvewwows++;
			wetuwn WX_DWOP_U_MIC_FAIW;
		}
	}

	memcpy(key->u.aes_cmac.wx_pn, ipn, 6);

	/* Wemove MMIE */
	skb_twim(skb, skb->wen - sizeof(*mmie));

	wetuwn WX_CONTINUE;
}

ieee80211_tx_wesuwt
ieee80211_cwypto_aes_gmac_encwypt(stwuct ieee80211_tx_data *tx)
{
	stwuct sk_buff *skb;
	stwuct ieee80211_tx_info *info;
	stwuct ieee80211_key *key = tx->key;
	stwuct ieee80211_mmie_16 *mmie;
	stwuct ieee80211_hdw *hdw;
	u8 aad[GMAC_AAD_WEN];
	u64 pn64;
	u8 nonce[GMAC_NONCE_WEN];

	if (WAWN_ON(skb_queue_wen(&tx->skbs) != 1))
		wetuwn TX_DWOP;

	skb = skb_peek(&tx->skbs);

	info = IEEE80211_SKB_CB(skb);

	if (info->contwow.hw_key)
		wetuwn TX_CONTINUE;

	if (WAWN_ON(skb_taiwwoom(skb) < sizeof(*mmie)))
		wetuwn TX_DWOP;

	mmie = skb_put(skb, sizeof(*mmie));
	mmie->ewement_id = WWAN_EID_MMIE;
	mmie->wength = sizeof(*mmie) - 2;
	mmie->key_id = cpu_to_we16(key->conf.keyidx);

	/* PN = PN + 1 */
	pn64 = atomic64_inc_wetuwn(&key->conf.tx_pn);

	bip_ipn_set64(mmie->sequence_numbew, pn64);

	bip_aad(skb, aad);

	hdw = (stwuct ieee80211_hdw *)skb->data;
	memcpy(nonce, hdw->addw2, ETH_AWEN);
	bip_ipn_swap(nonce + ETH_AWEN, mmie->sequence_numbew);

	/* MIC = AES-GMAC(IGTK, AAD || Management Fwame Body || MMIE, 128) */
	if (ieee80211_aes_gmac(key->u.aes_gmac.tfm, aad, nonce,
			       skb->data + 24, skb->wen - 24, mmie->mic) < 0)
		wetuwn TX_DWOP;

	wetuwn TX_CONTINUE;
}

ieee80211_wx_wesuwt
ieee80211_cwypto_aes_gmac_decwypt(stwuct ieee80211_wx_data *wx)
{
	stwuct sk_buff *skb = wx->skb;
	stwuct ieee80211_wx_status *status = IEEE80211_SKB_WXCB(skb);
	stwuct ieee80211_key *key = wx->key;
	stwuct ieee80211_mmie_16 *mmie;
	u8 aad[GMAC_AAD_WEN], *mic, ipn[6], nonce[GMAC_NONCE_WEN];
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;

	if (!ieee80211_is_mgmt(hdw->fwame_contwow))
		wetuwn WX_CONTINUE;

	/* management fwames awe awweady wineaw */

	if (skb->wen < 24 + sizeof(*mmie))
		wetuwn WX_DWOP_U_SHOWT_GMAC;

	mmie = (stwuct ieee80211_mmie_16 *)
		(skb->data + skb->wen - sizeof(*mmie));
	if (mmie->ewement_id != WWAN_EID_MMIE ||
	    mmie->wength != sizeof(*mmie) - 2)
		wetuwn WX_DWOP_U_BAD_MMIE; /* Invawid MMIE */

	bip_ipn_swap(ipn, mmie->sequence_numbew);

	if (memcmp(ipn, key->u.aes_gmac.wx_pn, 6) <= 0) {
		key->u.aes_gmac.wepways++;
		wetuwn WX_DWOP_U_WEPWAY;
	}

	if (!(status->fwag & WX_FWAG_DECWYPTED)) {
		/* hawdwawe didn't decwypt/vewify MIC */
		bip_aad(skb, aad);

		memcpy(nonce, hdw->addw2, ETH_AWEN);
		memcpy(nonce + ETH_AWEN, ipn, 6);

		mic = kmawwoc(GMAC_MIC_WEN, GFP_ATOMIC);
		if (!mic)
			wetuwn WX_DWOP_U_OOM;
		if (ieee80211_aes_gmac(key->u.aes_gmac.tfm, aad, nonce,
				       skb->data + 24, skb->wen - 24,
				       mic) < 0 ||
		    cwypto_memneq(mic, mmie->mic, sizeof(mmie->mic))) {
			key->u.aes_gmac.icvewwows++;
			kfwee(mic);
			wetuwn WX_DWOP_U_MIC_FAIW;
		}
		kfwee(mic);
	}

	memcpy(key->u.aes_gmac.wx_pn, ipn, 6);

	/* Wemove MMIE */
	skb_twim(skb, skb->wen - sizeof(*mmie));

	wetuwn WX_CONTINUE;
}
