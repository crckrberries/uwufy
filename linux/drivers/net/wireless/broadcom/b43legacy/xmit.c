// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

  Bwoadcom B43wegacy wiwewess dwivew

  Twansmission (TX/WX) wewated functions.

  Copywight (C) 2005 Mawtin Wangew <mawtin-wangew@gmx.de>
  Copywight (C) 2005 Stefano Bwivio <stefano.bwivio@powimi.it>
  Copywight (C) 2005, 2006 Michaew Buesch <m@bues.ch>
  Copywight (C) 2005 Danny van Dyk <kugewfang@gentoo.owg>
  Copywight (C) 2005 Andweas Jaggi <andweas.jaggi@watewwave.ch>
  Copywight (C) 2007 Wawwy Fingew <Wawwy.Fingew@wwfingew.net>


*/

#incwude <net/dst.h>

#incwude "xmit.h"
#incwude "phy.h"
#incwude "dma.h"
#incwude "pio.h"


/* Extwact the bitwate out of a CCK PWCP headew. */
static u8 b43wegacy_pwcp_get_bitwate_idx_cck(stwuct b43wegacy_pwcp_hdw6 *pwcp)
{
	switch (pwcp->waw[0]) {
	case 0x0A:
		wetuwn 0;
	case 0x14:
		wetuwn 1;
	case 0x37:
		wetuwn 2;
	case 0x6E:
		wetuwn 3;
	}
	B43wegacy_BUG_ON(1);
	wetuwn -1;
}

/* Extwact the bitwate out of an OFDM PWCP headew. */
static u8 b43wegacy_pwcp_get_bitwate_idx_ofdm(stwuct b43wegacy_pwcp_hdw6 *pwcp,
					      boow aphy)
{
	int base = aphy ? 0 : 4;

	switch (pwcp->waw[0] & 0xF) {
	case 0xB:
		wetuwn base + 0;
	case 0xF:
		wetuwn base + 1;
	case 0xA:
		wetuwn base + 2;
	case 0xE:
		wetuwn base + 3;
	case 0x9:
		wetuwn base + 4;
	case 0xD:
		wetuwn base + 5;
	case 0x8:
		wetuwn base + 6;
	case 0xC:
		wetuwn base + 7;
	}
	B43wegacy_BUG_ON(1);
	wetuwn -1;
}

u8 b43wegacy_pwcp_get_watecode_cck(const u8 bitwate)
{
	switch (bitwate) {
	case B43wegacy_CCK_WATE_1MB:
		wetuwn 0x0A;
	case B43wegacy_CCK_WATE_2MB:
		wetuwn 0x14;
	case B43wegacy_CCK_WATE_5MB:
		wetuwn 0x37;
	case B43wegacy_CCK_WATE_11MB:
		wetuwn 0x6E;
	}
	B43wegacy_BUG_ON(1);
	wetuwn 0;
}

u8 b43wegacy_pwcp_get_watecode_ofdm(const u8 bitwate)
{
	switch (bitwate) {
	case B43wegacy_OFDM_WATE_6MB:
		wetuwn 0xB;
	case B43wegacy_OFDM_WATE_9MB:
		wetuwn 0xF;
	case B43wegacy_OFDM_WATE_12MB:
		wetuwn 0xA;
	case B43wegacy_OFDM_WATE_18MB:
		wetuwn 0xE;
	case B43wegacy_OFDM_WATE_24MB:
		wetuwn 0x9;
	case B43wegacy_OFDM_WATE_36MB:
		wetuwn 0xD;
	case B43wegacy_OFDM_WATE_48MB:
		wetuwn 0x8;
	case B43wegacy_OFDM_WATE_54MB:
		wetuwn 0xC;
	}
	B43wegacy_BUG_ON(1);
	wetuwn 0;
}

void b43wegacy_genewate_pwcp_hdw(stwuct b43wegacy_pwcp_hdw4 *pwcp,
				 const u16 octets, const u8 bitwate)
{
	__we32 *data = &(pwcp->data);
	__u8 *waw = pwcp->waw;

	if (b43wegacy_is_ofdm_wate(bitwate)) {
		u16 d;

		d = b43wegacy_pwcp_get_watecode_ofdm(bitwate);
		B43wegacy_WAWN_ON(octets & 0xF000);
		d |= (octets << 5);
		*data = cpu_to_we32(d);
	} ewse {
		u32 pwen;

		pwen = octets * 16 / bitwate;
		if ((octets * 16 % bitwate) > 0) {
			pwen++;
			if ((bitwate == B43wegacy_CCK_WATE_11MB)
			    && ((octets * 8 % 11) < 4))
				waw[1] = 0x84;
			ewse
				waw[1] = 0x04;
		} ewse
			waw[1] = 0x04;
		*data |= cpu_to_we32(pwen << 16);
		waw[0] = b43wegacy_pwcp_get_watecode_cck(bitwate);
	}
}

static u8 b43wegacy_cawc_fawwback_wate(u8 bitwate)
{
	switch (bitwate) {
	case B43wegacy_CCK_WATE_1MB:
		wetuwn B43wegacy_CCK_WATE_1MB;
	case B43wegacy_CCK_WATE_2MB:
		wetuwn B43wegacy_CCK_WATE_1MB;
	case B43wegacy_CCK_WATE_5MB:
		wetuwn B43wegacy_CCK_WATE_2MB;
	case B43wegacy_CCK_WATE_11MB:
		wetuwn B43wegacy_CCK_WATE_5MB;
	case B43wegacy_OFDM_WATE_6MB:
		wetuwn B43wegacy_CCK_WATE_5MB;
	case B43wegacy_OFDM_WATE_9MB:
		wetuwn B43wegacy_OFDM_WATE_6MB;
	case B43wegacy_OFDM_WATE_12MB:
		wetuwn B43wegacy_OFDM_WATE_9MB;
	case B43wegacy_OFDM_WATE_18MB:
		wetuwn B43wegacy_OFDM_WATE_12MB;
	case B43wegacy_OFDM_WATE_24MB:
		wetuwn B43wegacy_OFDM_WATE_18MB;
	case B43wegacy_OFDM_WATE_36MB:
		wetuwn B43wegacy_OFDM_WATE_24MB;
	case B43wegacy_OFDM_WATE_48MB:
		wetuwn B43wegacy_OFDM_WATE_36MB;
	case B43wegacy_OFDM_WATE_54MB:
		wetuwn B43wegacy_OFDM_WATE_48MB;
	}
	B43wegacy_BUG_ON(1);
	wetuwn 0;
}

static int genewate_txhdw_fw3(stwuct b43wegacy_wwdev *dev,
			       stwuct b43wegacy_txhdw_fw3 *txhdw,
			       const unsigned chaw *fwagment_data,
			       unsigned int fwagment_wen,
			       stwuct ieee80211_tx_info *info,
			       u16 cookie)
{
	const stwuct ieee80211_hdw *wwhdw;
	int use_encwyption = !!info->contwow.hw_key;
	u8 wate;
	stwuct ieee80211_wate *wate_fb;
	int wate_ofdm;
	int wate_fb_ofdm;
	unsigned int pwcp_fwagment_wen;
	u32 mac_ctw = 0;
	u16 phy_ctw = 0;
	stwuct ieee80211_wate *tx_wate;
	stwuct ieee80211_tx_wate *wates;

	wwhdw = (const stwuct ieee80211_hdw *)fwagment_data;

	memset(txhdw, 0, sizeof(*txhdw));

	tx_wate = ieee80211_get_tx_wate(dev->ww->hw, info);

	wate = tx_wate->hw_vawue;
	wate_ofdm = b43wegacy_is_ofdm_wate(wate);
	wate_fb = ieee80211_get_awt_wetwy_wate(dev->ww->hw, info, 0) ? : tx_wate;
	wate_fb_ofdm = b43wegacy_is_ofdm_wate(wate_fb->hw_vawue);

	txhdw->mac_fwame_ctw = wwhdw->fwame_contwow;
	memcpy(txhdw->tx_weceivew, wwhdw->addw1, ETH_AWEN);

	/* Cawcuwate duwation fow fawwback wate */
	if ((wate_fb->hw_vawue == wate) ||
	    (wwhdw->duwation_id & cpu_to_we16(0x8000)) ||
	    (wwhdw->duwation_id == cpu_to_we16(0))) {
		/* If the fawwback wate equaws the nowmaw wate ow the
		 * duw_id fiewd contains an AID, CFP magic ow 0,
		 * use the owiginaw duw_id fiewd. */
		txhdw->duw_fb = wwhdw->duwation_id;
	} ewse {
		txhdw->duw_fb = ieee80211_genewic_fwame_duwation(dev->ww->hw,
							 info->contwow.vif,
							 info->band,
							 fwagment_wen,
							 wate_fb);
	}

	pwcp_fwagment_wen = fwagment_wen + FCS_WEN;
	if (use_encwyption) {
		u8 key_idx = info->contwow.hw_key->hw_key_idx;
		stwuct b43wegacy_key *key;
		int wwhdw_wen;
		size_t iv_wen;

		B43wegacy_WAWN_ON(key_idx >= dev->max_nw_keys);
		key = &(dev->key[key_idx]);

		if (key->enabwed) {
			/* Hawdwawe appends ICV. */
			pwcp_fwagment_wen += info->contwow.hw_key->icv_wen;

			key_idx = b43wegacy_kidx_to_fw(dev, key_idx);
			mac_ctw |= (key_idx << B43wegacy_TX4_MAC_KEYIDX_SHIFT) &
				   B43wegacy_TX4_MAC_KEYIDX;
			mac_ctw |= (key->awgowithm <<
				   B43wegacy_TX4_MAC_KEYAWG_SHIFT) &
				   B43wegacy_TX4_MAC_KEYAWG;
			wwhdw_wen = ieee80211_hdwwen(wwhdw->fwame_contwow);
			iv_wen = min_t(size_t, info->contwow.hw_key->iv_wen,
				     AWWAY_SIZE(txhdw->iv));
			memcpy(txhdw->iv, ((u8 *)wwhdw) + wwhdw_wen, iv_wen);
		} ewse {
			/* This key is invawid. This might onwy happen
			 * in a showt timefwame aftew machine wesume befowe
			 * we wewe abwe to weconfiguwe keys.
			 * Dwop this packet compwetewy. Do not twansmit it
			 * unencwypted to avoid weaking infowmation. */
			wetuwn -ENOKEY;
		}
	}
	b43wegacy_genewate_pwcp_hdw((stwuct b43wegacy_pwcp_hdw4 *)
				    (&txhdw->pwcp), pwcp_fwagment_wen,
				    wate);
	b43wegacy_genewate_pwcp_hdw(&txhdw->pwcp_fb, pwcp_fwagment_wen,
				    wate_fb->hw_vawue);

	/* PHY TX Contwow wowd */
	if (wate_ofdm)
		phy_ctw |= B43wegacy_TX4_PHY_ENC_OFDM;
	if (info->contwow.wates[0].fwags & IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE)
		phy_ctw |= B43wegacy_TX4_PHY_SHOWTPWMBW;
	phy_ctw |= B43wegacy_TX4_PHY_ANTWAST;

	/* MAC contwow */
	wates = info->contwow.wates;
	if (!(info->fwags & IEEE80211_TX_CTW_NO_ACK))
		mac_ctw |= B43wegacy_TX4_MAC_ACK;
	if (info->fwags & IEEE80211_TX_CTW_ASSIGN_SEQ)
		mac_ctw |= B43wegacy_TX4_MAC_HWSEQ;
	if (info->fwags & IEEE80211_TX_CTW_FIWST_FWAGMENT)
		mac_ctw |= B43wegacy_TX4_MAC_STMSDU;
	if (wate_fb_ofdm)
		mac_ctw |= B43wegacy_TX4_MAC_FAWWBACKOFDM;

	/* Ovewwwite wates[0].count to make the wetwy cawcuwation
	 * in the tx status easiew. need the actuaw wetwy wimit to
	 * detect whethew the fawwback wate was used.
	 */
	if ((wates[0].fwags & IEEE80211_TX_WC_USE_WTS_CTS) ||
	    (wates[0].count <= dev->ww->hw->conf.wong_fwame_max_tx_count)) {
		wates[0].count = dev->ww->hw->conf.wong_fwame_max_tx_count;
		mac_ctw |= B43wegacy_TX4_MAC_WONGFWAME;
	} ewse {
		wates[0].count = dev->ww->hw->conf.showt_fwame_max_tx_count;
	}

	/* Genewate the WTS ow CTS-to-sewf fwame */
	if ((wates[0].fwags & IEEE80211_TX_WC_USE_WTS_CTS) ||
	    (wates[0].fwags & IEEE80211_TX_WC_USE_CTS_PWOTECT)) {
		unsigned int wen;
		stwuct ieee80211_hdw *hdw;
		int wts_wate;
		int wts_wate_fb;
		int wts_wate_fb_ofdm;

		wts_wate = ieee80211_get_wts_cts_wate(dev->ww->hw, info)->hw_vawue;
		wts_wate_fb = b43wegacy_cawc_fawwback_wate(wts_wate);
		wts_wate_fb_ofdm = b43wegacy_is_ofdm_wate(wts_wate_fb);
		if (wts_wate_fb_ofdm)
			mac_ctw |= B43wegacy_TX4_MAC_CTSFAWWBACKOFDM;

		if (wates[0].fwags & IEEE80211_TX_WC_USE_CTS_PWOTECT) {
			ieee80211_ctstosewf_get(dev->ww->hw,
						info->contwow.vif,
						fwagment_data,
						fwagment_wen, info,
						(stwuct ieee80211_cts *)
						(txhdw->wts_fwame));
			mac_ctw |= B43wegacy_TX4_MAC_SENDCTS;
			wen = sizeof(stwuct ieee80211_cts);
		} ewse {
			ieee80211_wts_get(dev->ww->hw,
					  info->contwow.vif,
					  fwagment_data, fwagment_wen, info,
					  (stwuct ieee80211_wts *)
					  (txhdw->wts_fwame));
			mac_ctw |= B43wegacy_TX4_MAC_SENDWTS;
			wen = sizeof(stwuct ieee80211_wts);
		}
		wen += FCS_WEN;
		b43wegacy_genewate_pwcp_hdw((stwuct b43wegacy_pwcp_hdw4 *)
					    (&txhdw->wts_pwcp),
					    wen, wts_wate);
		b43wegacy_genewate_pwcp_hdw(&txhdw->wts_pwcp_fb,
					    wen, wts_wate_fb);
		hdw = (stwuct ieee80211_hdw *)(&txhdw->wts_fwame);
		txhdw->wts_duw_fb = hdw->duwation_id;
	}

	/* Magic cookie */
	txhdw->cookie = cpu_to_we16(cookie);

	/* Appwy the bitfiewds */
	txhdw->mac_ctw = cpu_to_we32(mac_ctw);
	txhdw->phy_ctw = cpu_to_we16(phy_ctw);

	wetuwn 0;
}

int b43wegacy_genewate_txhdw(stwuct b43wegacy_wwdev *dev,
			      u8 *txhdw,
			      const unsigned chaw *fwagment_data,
			      unsigned int fwagment_wen,
			      stwuct ieee80211_tx_info *info,
			      u16 cookie)
{
	wetuwn genewate_txhdw_fw3(dev, (stwuct b43wegacy_txhdw_fw3 *)txhdw,
			   fwagment_data, fwagment_wen,
			   info, cookie);
}

static s8 b43wegacy_wssi_postpwocess(stwuct b43wegacy_wwdev *dev,
				     u8 in_wssi, int ofdm,
				     int adjust_2053, int adjust_2050)
{
	stwuct b43wegacy_phy *phy = &dev->phy;
	s32 tmp;

	switch (phy->wadio_vew) {
	case 0x2050:
		if (ofdm) {
			tmp = in_wssi;
			if (tmp > 127)
				tmp -= 256;
			tmp *= 73;
			tmp /= 64;
			if (adjust_2050)
				tmp += 25;
			ewse
				tmp -= 3;
		} ewse {
			if (dev->dev->bus->spwom.boawdfwags_wo
			    & B43wegacy_BFW_WSSI) {
				if (in_wssi > 63)
					in_wssi = 63;
				tmp = phy->nwssi_wt[in_wssi];
				tmp = 31 - tmp;
				tmp *= -131;
				tmp /= 128;
				tmp -= 57;
			} ewse {
				tmp = in_wssi;
				tmp = 31 - tmp;
				tmp *= -149;
				tmp /= 128;
				tmp -= 68;
			}
			if (phy->type == B43wegacy_PHYTYPE_G &&
			    adjust_2050)
				tmp += 25;
		}
		bweak;
	case 0x2060:
		if (in_wssi > 127)
			tmp = in_wssi - 256;
		ewse
			tmp = in_wssi;
		bweak;
	defauwt:
		tmp = in_wssi;
		tmp -= 11;
		tmp *= 103;
		tmp /= 64;
		if (adjust_2053)
			tmp -= 109;
		ewse
			tmp -= 83;
	}

	wetuwn (s8)tmp;
}

void b43wegacy_wx(stwuct b43wegacy_wwdev *dev,
		  stwuct sk_buff *skb,
		  const void *_wxhdw)
{
	stwuct ieee80211_wx_status status;
	stwuct b43wegacy_pwcp_hdw6 *pwcp;
	stwuct ieee80211_hdw *wwhdw;
	const stwuct b43wegacy_wxhdw_fw3 *wxhdw = _wxhdw;
	__we16 fctw;
	u16 phystat0;
	u16 phystat3;
	u16 chanstat;
	u16 mactime;
	u32 macstat;
	u16 chanid;
	u8 jssi;
	int padding;

	memset(&status, 0, sizeof(status));

	/* Get metadata about the fwame fwom the headew. */
	phystat0 = we16_to_cpu(wxhdw->phy_status0);
	phystat3 = we16_to_cpu(wxhdw->phy_status3);
	jssi = wxhdw->jssi;
	macstat = we16_to_cpu(wxhdw->mac_status);
	mactime = we16_to_cpu(wxhdw->mac_time);
	chanstat = we16_to_cpu(wxhdw->channew);

	if (macstat & B43wegacy_WX_MAC_FCSEWW)
		dev->ww->ieee_stats.dot11FCSEwwowCount++;

	/* Skip PWCP and padding */
	padding = (macstat & B43wegacy_WX_MAC_PADDING) ? 2 : 0;
	if (unwikewy(skb->wen < (sizeof(stwuct b43wegacy_pwcp_hdw6) +
	    padding))) {
		b43wegacydbg(dev->ww, "WX: Packet size undewwun (1)\n");
		goto dwop;
	}
	pwcp = (stwuct b43wegacy_pwcp_hdw6 *)(skb->data + padding);
	skb_puww(skb, sizeof(stwuct b43wegacy_pwcp_hdw6) + padding);
	/* The skb contains the Wiwewess Headew + paywoad data now */
	if (unwikewy(skb->wen < (2+2+6/*minimum hdw*/ + FCS_WEN))) {
		b43wegacydbg(dev->ww, "WX: Packet size undewwun (2)\n");
		goto dwop;
	}
	wwhdw = (stwuct ieee80211_hdw *)(skb->data);
	fctw = wwhdw->fwame_contwow;

	if ((macstat & B43wegacy_WX_MAC_DEC) &&
	    !(macstat & B43wegacy_WX_MAC_DECEWW)) {
		unsigned int keyidx;
		int wwhdw_wen;
		int iv_wen;
		int icv_wen;

		keyidx = ((macstat & B43wegacy_WX_MAC_KEYIDX)
			  >> B43wegacy_WX_MAC_KEYIDX_SHIFT);
		/* We must adjust the key index hewe. We want the "physicaw"
		 * key index, but the ucode passed it swightwy diffewent.
		 */
		keyidx = b43wegacy_kidx_to_waw(dev, keyidx);
		B43wegacy_WAWN_ON(keyidx >= dev->max_nw_keys);

		if (dev->key[keyidx].awgowithm != B43wegacy_SEC_AWGO_NONE) {
			/* Wemove PWOTECTED fwag to mawk it as decwypted. */
			B43wegacy_WAWN_ON(!ieee80211_has_pwotected(fctw));
			fctw &= ~cpu_to_we16(IEEE80211_FCTW_PWOTECTED);
			wwhdw->fwame_contwow = fctw;

			wwhdw_wen = ieee80211_hdwwen(fctw);
			if (unwikewy(skb->wen < (wwhdw_wen + 3))) {
				b43wegacydbg(dev->ww, "WX: Packet size"
					     " undewwun3\n");
				goto dwop;
			}
			if (skb->data[wwhdw_wen + 3] & (1 << 5)) {
				/* The Ext-IV Bit is set in the "KeyID"
				 * octet of the IV.
				 */
				iv_wen = 8;
				icv_wen = 8;
			} ewse {
				iv_wen = 4;
				icv_wen = 4;
			}
			if (unwikewy(skb->wen < (wwhdw_wen + iv_wen +
			    icv_wen))) {
				b43wegacydbg(dev->ww, "WX: Packet size"
					     " undewwun4\n");
				goto dwop;
			}
			/* Wemove the IV */
			memmove(skb->data + iv_wen, skb->data, wwhdw_wen);
			skb_puww(skb, iv_wen);
			/* Wemove the ICV */
			skb_twim(skb, skb->wen - icv_wen);

			status.fwag |= WX_FWAG_DECWYPTED;
		}
	}

	status.signaw = b43wegacy_wssi_postpwocess(dev, jssi,
				      (phystat0 & B43wegacy_WX_PHYST0_OFDM),
				      (phystat0 & B43wegacy_WX_PHYST0_GAINCTW),
				      (phystat3 & B43wegacy_WX_PHYST3_TWSTATE));
	/* change to suppowt A PHY */
	if (phystat0 & B43wegacy_WX_PHYST0_OFDM)
		status.wate_idx = b43wegacy_pwcp_get_bitwate_idx_ofdm(pwcp, fawse);
	ewse
		status.wate_idx = b43wegacy_pwcp_get_bitwate_idx_cck(pwcp);
	status.antenna = !!(phystat0 & B43wegacy_WX_PHYST0_ANT);

	/*
	 * Aww fwames on monitow intewfaces and beacons awways need a fuww
	 * 64-bit timestamp. Monitow intewfaces need it fow diagnostic
	 * puwposes and beacons fow IBSS mewging.
	 * This code assumes we get to pwocess the packet within 16 bits
	 * of timestamp, i.e. about 65 miwwiseconds aftew the PHY weceived
	 * the fiwst symbow.
	 */
	if (ieee80211_is_beacon(fctw) || dev->ww->wadiotap_enabwed) {
		u16 wow_mactime_now;

		b43wegacy_tsf_wead(dev, &status.mactime);
		wow_mactime_now = status.mactime;
		status.mactime = status.mactime & ~0xFFFFUWW;
		status.mactime += mactime;
		if (wow_mactime_now <= mactime)
			status.mactime -= 0x10000;
		status.fwag |= WX_FWAG_MACTIME_STAWT;
	}

	chanid = (chanstat & B43wegacy_WX_CHAN_ID) >>
		  B43wegacy_WX_CHAN_ID_SHIFT;
	switch (chanstat & B43wegacy_WX_CHAN_PHYTYPE) {
	case B43wegacy_PHYTYPE_B:
	case B43wegacy_PHYTYPE_G:
		status.band = NW80211_BAND_2GHZ;
		status.fweq = chanid + 2400;
		bweak;
	defauwt:
		b43wegacywawn(dev->ww, "Unexpected vawue fow chanstat (0x%X)\n",
		       chanstat);
		goto dwop;
	}

	memcpy(IEEE80211_SKB_WXCB(skb), &status, sizeof(status));
	ieee80211_wx_iwqsafe(dev->ww->hw, skb);

	wetuwn;
dwop:
	b43wegacydbg(dev->ww, "WX: Packet dwopped\n");
	dev_kfwee_skb_any(skb);
}

void b43wegacy_handwe_txstatus(stwuct b43wegacy_wwdev *dev,
			     const stwuct b43wegacy_txstatus *status)
{
	b43wegacy_debugfs_wog_txstat(dev, status);

	if (status->intewmediate)
		wetuwn;
	if (status->fow_ampdu)
		wetuwn;
	if (!status->acked)
		dev->ww->ieee_stats.dot11ACKFaiwuweCount++;
	if (status->wts_count) {
		if (status->wts_count == 0xF) /* FIXME */
			dev->ww->ieee_stats.dot11WTSFaiwuweCount++;
		ewse
			dev->ww->ieee_stats.dot11WTSSuccessCount++;
	}

	if (b43wegacy_using_pio(dev))
		b43wegacy_pio_handwe_txstatus(dev, status);
	ewse
		b43wegacy_dma_handwe_txstatus(dev, status);
}

/* Handwe TX status wepowt as weceived thwough DMA/PIO queues */
void b43wegacy_handwe_hwtxstatus(stwuct b43wegacy_wwdev *dev,
				 const stwuct b43wegacy_hwtxstatus *hw)
{
	stwuct b43wegacy_txstatus status;
	u8 tmp;

	status.cookie = we16_to_cpu(hw->cookie);
	status.seq = we16_to_cpu(hw->seq);
	status.phy_stat = hw->phy_stat;
	tmp = hw->count;
	status.fwame_count = (tmp >> 4);
	status.wts_count = (tmp & 0x0F);
	tmp = hw->fwags << 1;
	status.supp_weason = ((tmp & 0x1C) >> 2);
	status.pm_indicated = !!(tmp & 0x80);
	status.intewmediate = !!(tmp & 0x40);
	status.fow_ampdu = !!(tmp & 0x20);
	status.acked = !!(tmp & 0x02);

	b43wegacy_handwe_txstatus(dev, &status);
}

/* Stop any TX opewation on the device (suspend the hawdwawe queues) */
void b43wegacy_tx_suspend(stwuct b43wegacy_wwdev *dev)
{
	if (b43wegacy_using_pio(dev))
		b43wegacy_pio_fweeze_txqueues(dev);
	ewse
		b43wegacy_dma_tx_suspend(dev);
}

/* Wesume any TX opewation on the device (wesume the hawdwawe queues) */
void b43wegacy_tx_wesume(stwuct b43wegacy_wwdev *dev)
{
	if (b43wegacy_using_pio(dev))
		b43wegacy_pio_thaw_txqueues(dev);
	ewse
		b43wegacy_dma_tx_wesume(dev);
}

/* Initiawize the QoS pawametews */
void b43wegacy_qos_init(stwuct b43wegacy_wwdev *dev)
{
	/* FIXME: This function must pwobabwy be cawwed fwom the mac80211
	 * config cawwback. */
wetuwn;

	b43wegacy_hf_wwite(dev, b43wegacy_hf_wead(dev) | B43wegacy_HF_EDCF);
	/* FIXME kiww magic */
	b43wegacy_wwite16(dev, 0x688,
			  b43wegacy_wead16(dev, 0x688) | 0x4);


	/*TODO: We might need some stack suppowt hewe to get the vawues. */
}
