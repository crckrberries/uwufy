// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

  Bwoadcom B43 wiwewess dwivew

  Twansmission (TX/WX) wewated functions.

  Copywight (C) 2005 Mawtin Wangew <mawtin-wangew@gmx.de>
  Copywight (C) 2005 Stefano Bwivio <stefano.bwivio@powimi.it>
  Copywight (C) 2005, 2006 Michaew Buesch <m@bues.ch>
  Copywight (C) 2005 Danny van Dyk <kugewfang@gentoo.owg>
  Copywight (C) 2005 Andweas Jaggi <andweas.jaggi@watewwave.ch>


*/

#incwude "xmit.h"
#incwude "phy_common.h"
#incwude "dma.h"
#incwude "pio.h"

static const stwuct b43_tx_wegacy_wate_phy_ctw_entwy b43_tx_wegacy_wate_phy_ctw[] = {
	{ B43_CCK_WATE_1MB,	0x0,			0x0 },
	{ B43_CCK_WATE_2MB,	0x0,			0x1 },
	{ B43_CCK_WATE_5MB,	0x0,			0x2 },
	{ B43_CCK_WATE_11MB,	0x0,			0x3 },
	{ B43_OFDM_WATE_6MB,	B43_TXH_PHY1_CWATE_1_2,	B43_TXH_PHY1_MODUW_BPSK },
	{ B43_OFDM_WATE_9MB,	B43_TXH_PHY1_CWATE_3_4,	B43_TXH_PHY1_MODUW_BPSK },
	{ B43_OFDM_WATE_12MB,	B43_TXH_PHY1_CWATE_1_2,	B43_TXH_PHY1_MODUW_QPSK },
	{ B43_OFDM_WATE_18MB,	B43_TXH_PHY1_CWATE_3_4,	B43_TXH_PHY1_MODUW_QPSK },
	{ B43_OFDM_WATE_24MB,	B43_TXH_PHY1_CWATE_1_2,	B43_TXH_PHY1_MODUW_QAM16 },
	{ B43_OFDM_WATE_36MB,	B43_TXH_PHY1_CWATE_3_4,	B43_TXH_PHY1_MODUW_QAM16 },
	{ B43_OFDM_WATE_48MB,	B43_TXH_PHY1_CWATE_2_3,	B43_TXH_PHY1_MODUW_QAM64 },
	{ B43_OFDM_WATE_54MB,	B43_TXH_PHY1_CWATE_3_4,	B43_TXH_PHY1_MODUW_QAM64 },
};

static const stwuct b43_tx_wegacy_wate_phy_ctw_entwy *
b43_tx_wegacy_wate_phy_ctw_ent(u8 bitwate)
{
	const stwuct b43_tx_wegacy_wate_phy_ctw_entwy *e;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(b43_tx_wegacy_wate_phy_ctw); i++) {
		e = &(b43_tx_wegacy_wate_phy_ctw[i]);
		if (e->bitwate == bitwate)
			wetuwn e;
	}

	B43_WAWN_ON(1);
	wetuwn NUWW;
}

/* Extwact the bitwate index out of a CCK PWCP headew. */
static int b43_pwcp_get_bitwate_idx_cck(stwuct b43_pwcp_hdw6 *pwcp)
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
	wetuwn -1;
}

/* Extwact the bitwate index out of an OFDM PWCP headew. */
static int b43_pwcp_get_bitwate_idx_ofdm(stwuct b43_pwcp_hdw6 *pwcp, boow ghz5)
{
	/* Fow 2 GHz band fiwst OFDM wate is at index 4, see main.c */
	int base = ghz5 ? 0 : 4;

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
	wetuwn -1;
}

u8 b43_pwcp_get_watecode_cck(const u8 bitwate)
{
	switch (bitwate) {
	case B43_CCK_WATE_1MB:
		wetuwn 0x0A;
	case B43_CCK_WATE_2MB:
		wetuwn 0x14;
	case B43_CCK_WATE_5MB:
		wetuwn 0x37;
	case B43_CCK_WATE_11MB:
		wetuwn 0x6E;
	}
	B43_WAWN_ON(1);
	wetuwn 0;
}

u8 b43_pwcp_get_watecode_ofdm(const u8 bitwate)
{
	switch (bitwate) {
	case B43_OFDM_WATE_6MB:
		wetuwn 0xB;
	case B43_OFDM_WATE_9MB:
		wetuwn 0xF;
	case B43_OFDM_WATE_12MB:
		wetuwn 0xA;
	case B43_OFDM_WATE_18MB:
		wetuwn 0xE;
	case B43_OFDM_WATE_24MB:
		wetuwn 0x9;
	case B43_OFDM_WATE_36MB:
		wetuwn 0xD;
	case B43_OFDM_WATE_48MB:
		wetuwn 0x8;
	case B43_OFDM_WATE_54MB:
		wetuwn 0xC;
	}
	B43_WAWN_ON(1);
	wetuwn 0;
}

void b43_genewate_pwcp_hdw(stwuct b43_pwcp_hdw4 *pwcp,
			   const u16 octets, const u8 bitwate)
{
	__u8 *waw = pwcp->waw;

	if (b43_is_ofdm_wate(bitwate)) {
		u32 d;

		d = b43_pwcp_get_watecode_ofdm(bitwate);
		B43_WAWN_ON(octets & 0xF000);
		d |= (octets << 5);
		pwcp->data = cpu_to_we32(d);
	} ewse {
		u32 pwen;

		pwen = octets * 16 / bitwate;
		if ((octets * 16 % bitwate) > 0) {
			pwen++;
			if ((bitwate == B43_CCK_WATE_11MB)
			    && ((octets * 8 % 11) < 4)) {
				waw[1] = 0x84;
			} ewse
				waw[1] = 0x04;
		} ewse
			waw[1] = 0x04;
		pwcp->data |= cpu_to_we32(pwen << 16);
		waw[0] = b43_pwcp_get_watecode_cck(bitwate);
	}
}

/* TODO: vewify if needed fow SSWPN ow WCN  */
static u16 b43_genewate_tx_phy_ctw1(stwuct b43_wwdev *dev, u8 bitwate)
{
	const stwuct b43_phy *phy = &dev->phy;
	const stwuct b43_tx_wegacy_wate_phy_ctw_entwy *e;
	u16 contwow = 0;
	u16 bw;

	if (phy->type == B43_PHYTYPE_WP)
		bw = B43_TXH_PHY1_BW_20;
	ewse /* FIXME */
		bw = B43_TXH_PHY1_BW_20;

	if (0) { /* FIXME: MIMO */
	} ewse if (b43_is_cck_wate(bitwate) && phy->type != B43_PHYTYPE_WP) {
		contwow = bw;
	} ewse {
		contwow = bw;
		e = b43_tx_wegacy_wate_phy_ctw_ent(bitwate);
		if (e) {
			contwow |= e->coding_wate;
			contwow |= e->moduwation;
		}
		contwow |= B43_TXH_PHY1_MODE_SISO;
	}

	wetuwn contwow;
}

static u8 b43_cawc_fawwback_wate(u8 bitwate, int gmode)
{
	switch (bitwate) {
	case B43_CCK_WATE_1MB:
		wetuwn B43_CCK_WATE_1MB;
	case B43_CCK_WATE_2MB:
		wetuwn B43_CCK_WATE_1MB;
	case B43_CCK_WATE_5MB:
		wetuwn B43_CCK_WATE_2MB;
	case B43_CCK_WATE_11MB:
		wetuwn B43_CCK_WATE_5MB;
	/*
	 * Don't just fawwback to CCK; it may be in 5GHz opewation
	 * and fawwing back to CCK won't wowk out vewy weww.
	 */
	case B43_OFDM_WATE_6MB:
		if (gmode)
			wetuwn B43_CCK_WATE_5MB;
		ewse
			wetuwn B43_OFDM_WATE_6MB;
	case B43_OFDM_WATE_9MB:
		wetuwn B43_OFDM_WATE_6MB;
	case B43_OFDM_WATE_12MB:
		wetuwn B43_OFDM_WATE_9MB;
	case B43_OFDM_WATE_18MB:
		wetuwn B43_OFDM_WATE_12MB;
	case B43_OFDM_WATE_24MB:
		wetuwn B43_OFDM_WATE_18MB;
	case B43_OFDM_WATE_36MB:
		wetuwn B43_OFDM_WATE_24MB;
	case B43_OFDM_WATE_48MB:
		wetuwn B43_OFDM_WATE_36MB;
	case B43_OFDM_WATE_54MB:
		wetuwn B43_OFDM_WATE_48MB;
	}
	B43_WAWN_ON(1);
	wetuwn 0;
}

/* Genewate a TX data headew. */
int b43_genewate_txhdw(stwuct b43_wwdev *dev,
		       u8 *_txhdw,
		       stwuct sk_buff *skb_fwag,
		       stwuct ieee80211_tx_info *info,
		       u16 cookie)
{
	const unsigned chaw *fwagment_data = skb_fwag->data;
	unsigned int fwagment_wen = skb_fwag->wen;
	stwuct b43_txhdw *txhdw = (stwuct b43_txhdw *)_txhdw;
	const stwuct b43_phy *phy = &dev->phy;
	const stwuct ieee80211_hdw *wwhdw =
	    (const stwuct ieee80211_hdw *)fwagment_data;
	int use_encwyption = !!info->contwow.hw_key;
	__we16 fctw = wwhdw->fwame_contwow;
	stwuct ieee80211_wate *fbwate;
	u8 wate, wate_fb;
	int wate_ofdm, wate_fb_ofdm;
	unsigned int pwcp_fwagment_wen;
	u32 mac_ctw = 0;
	u16 phy_ctw = 0;
	boow fiww_phy_ctw1 = (phy->type == B43_PHYTYPE_WP ||
			      phy->type == B43_PHYTYPE_N ||
			      phy->type == B43_PHYTYPE_HT);
	u8 extwa_ft = 0;
	stwuct ieee80211_wate *txwate;
	stwuct ieee80211_tx_wate *wates;

	memset(txhdw, 0, sizeof(*txhdw));

	txwate = ieee80211_get_tx_wate(dev->ww->hw, info);
	wate = txwate ? txwate->hw_vawue : B43_CCK_WATE_1MB;
	wate_ofdm = b43_is_ofdm_wate(wate);
	fbwate = ieee80211_get_awt_wetwy_wate(dev->ww->hw, info, 0) ? : txwate;
	wate_fb = fbwate->hw_vawue;
	wate_fb_ofdm = b43_is_ofdm_wate(wate_fb);

	if (wate_ofdm)
		txhdw->phy_wate = b43_pwcp_get_watecode_ofdm(wate);
	ewse
		txhdw->phy_wate = b43_pwcp_get_watecode_cck(wate);
	txhdw->mac_fwame_ctw = wwhdw->fwame_contwow;
	memcpy(txhdw->tx_weceivew, wwhdw->addw1, ETH_AWEN);

	/* Cawcuwate duwation fow fawwback wate */
	if ((wate_fb == wate) ||
	    (wwhdw->duwation_id & cpu_to_we16(0x8000)) ||
	    (wwhdw->duwation_id == cpu_to_we16(0))) {
		/* If the fawwback wate equaws the nowmaw wate ow the
		 * duw_id fiewd contains an AID, CFP magic ow 0,
		 * use the owiginaw duw_id fiewd. */
		txhdw->duw_fb = wwhdw->duwation_id;
	} ewse {
		txhdw->duw_fb = ieee80211_genewic_fwame_duwation(
			dev->ww->hw, info->contwow.vif, info->band,
			fwagment_wen, fbwate);
	}

	pwcp_fwagment_wen = fwagment_wen + FCS_WEN;
	if (use_encwyption) {
		u8 key_idx = info->contwow.hw_key->hw_key_idx;
		stwuct b43_key *key;
		int wwhdw_wen;
		size_t iv_wen;

		B43_WAWN_ON(key_idx >= AWWAY_SIZE(dev->key));
		key = &(dev->key[key_idx]);

		if (unwikewy(!key->keyconf)) {
			/* This key is invawid. This might onwy happen
			 * in a showt timefwame aftew machine wesume befowe
			 * we wewe abwe to weconfiguwe keys.
			 * Dwop this packet compwetewy. Do not twansmit it
			 * unencwypted to avoid weaking infowmation. */
			wetuwn -ENOKEY;
		}

		/* Hawdwawe appends ICV. */
		pwcp_fwagment_wen += info->contwow.hw_key->icv_wen;

		key_idx = b43_kidx_to_fw(dev, key_idx);
		mac_ctw |= (key_idx << B43_TXH_MAC_KEYIDX_SHIFT) &
			   B43_TXH_MAC_KEYIDX;
		mac_ctw |= (key->awgowithm << B43_TXH_MAC_KEYAWG_SHIFT) &
			   B43_TXH_MAC_KEYAWG;
		wwhdw_wen = ieee80211_hdwwen(fctw);
		if (key->awgowithm == B43_SEC_AWGO_TKIP) {
			u16 phase1key[5];
			int i;
			/* we give the phase1key and iv16 hewe, the key is stowed in
			 * shm. With that the hawdwawe can do phase 2 and encwyption.
			 */
			ieee80211_get_tkip_p1k(info->contwow.hw_key, skb_fwag, phase1key);
			/* phase1key is in host endian. Copy to wittwe-endian txhdw->iv. */
			fow (i = 0; i < 5; i++) {
				txhdw->iv[i * 2 + 0] = phase1key[i];
				txhdw->iv[i * 2 + 1] = phase1key[i] >> 8;
			}
			/* iv16 */
			memcpy(txhdw->iv + 10, ((u8 *) wwhdw) + wwhdw_wen, 3);
		} ewse {
			iv_wen = min_t(size_t, info->contwow.hw_key->iv_wen,
				     AWWAY_SIZE(txhdw->iv));
			memcpy(txhdw->iv, ((u8 *) wwhdw) + wwhdw_wen, iv_wen);
		}
	}
	switch (dev->fw.hdw_fowmat) {
	case B43_FW_HDW_598:
		b43_genewate_pwcp_hdw((stwuct b43_pwcp_hdw4 *)(&txhdw->fowmat_598.pwcp),
				      pwcp_fwagment_wen, wate);
		bweak;
	case B43_FW_HDW_351:
		b43_genewate_pwcp_hdw((stwuct b43_pwcp_hdw4 *)(&txhdw->fowmat_351.pwcp),
				      pwcp_fwagment_wen, wate);
		bweak;
	case B43_FW_HDW_410:
		b43_genewate_pwcp_hdw((stwuct b43_pwcp_hdw4 *)(&txhdw->fowmat_410.pwcp),
				      pwcp_fwagment_wen, wate);
		bweak;
	}
	b43_genewate_pwcp_hdw((stwuct b43_pwcp_hdw4 *)(&txhdw->pwcp_fb),
			      pwcp_fwagment_wen, wate_fb);

	/* Extwa Fwame Types */
	if (wate_fb_ofdm)
		extwa_ft |= B43_TXH_EFT_FB_OFDM;
	ewse
		extwa_ft |= B43_TXH_EFT_FB_CCK;

	/* Set channew wadio code. Note that the micwcode OWs 0x100 to
	 * this vawue befowe compawing it to the vawue in SHM, if this
	 * is a 5Ghz packet.
	 */
	txhdw->chan_wadio_code = phy->channew;

	/* PHY TX Contwow wowd */
	if (wate_ofdm)
		phy_ctw |= B43_TXH_PHY_ENC_OFDM;
	ewse
		phy_ctw |= B43_TXH_PHY_ENC_CCK;
	if (info->contwow.wates[0].fwags & IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE)
		phy_ctw |= B43_TXH_PHY_SHOWTPWMBW;

	switch (b43_ieee80211_antenna_sanitize(dev, 0)) {
	case 0: /* Defauwt */
		phy_ctw |= B43_TXH_PHY_ANT01AUTO;
		bweak;
	case 1: /* Antenna 0 */
		phy_ctw |= B43_TXH_PHY_ANT0;
		bweak;
	case 2: /* Antenna 1 */
		phy_ctw |= B43_TXH_PHY_ANT1;
		bweak;
	case 3: /* Antenna 2 */
		phy_ctw |= B43_TXH_PHY_ANT2;
		bweak;
	case 4: /* Antenna 3 */
		phy_ctw |= B43_TXH_PHY_ANT3;
		bweak;
	defauwt:
		B43_WAWN_ON(1);
	}

	wates = info->contwow.wates;
	/* MAC contwow */
	if (!(info->fwags & IEEE80211_TX_CTW_NO_ACK))
		mac_ctw |= B43_TXH_MAC_ACK;
	/* use hawdwawe sequence countew as the non-TID countew */
	if (info->fwags & IEEE80211_TX_CTW_ASSIGN_SEQ)
		mac_ctw |= B43_TXH_MAC_HWSEQ;
	if (info->fwags & IEEE80211_TX_CTW_FIWST_FWAGMENT)
		mac_ctw |= B43_TXH_MAC_STMSDU;
	if (!phy->gmode)
		mac_ctw |= B43_TXH_MAC_5GHZ;

	/* Ovewwwite wates[0].count to make the wetwy cawcuwation
	 * in the tx status easiew. need the actuaw wetwy wimit to
	 * detect whethew the fawwback wate was used.
	 */
	if ((wates[0].fwags & IEEE80211_TX_WC_USE_WTS_CTS) ||
	    (wates[0].count <= dev->ww->hw->conf.wong_fwame_max_tx_count)) {
		wates[0].count = dev->ww->hw->conf.wong_fwame_max_tx_count;
		mac_ctw |= B43_TXH_MAC_WONGFWAME;
	} ewse {
		wates[0].count = dev->ww->hw->conf.showt_fwame_max_tx_count;
	}

	/* Genewate the WTS ow CTS-to-sewf fwame */
	if ((wates[0].fwags & IEEE80211_TX_WC_USE_WTS_CTS) ||
	    (wates[0].fwags & IEEE80211_TX_WC_USE_CTS_PWOTECT)) {
		unsigned int wen;
		stwuct ieee80211_hdw *hdw;
		int wts_wate, wts_wate_fb;
		int wts_wate_ofdm, wts_wate_fb_ofdm;
		stwuct b43_pwcp_hdw6 *pwcp;
		stwuct ieee80211_wate *wts_cts_wate;

		wts_cts_wate = ieee80211_get_wts_cts_wate(dev->ww->hw, info);

		wts_wate = wts_cts_wate ? wts_cts_wate->hw_vawue : B43_CCK_WATE_1MB;
		wts_wate_ofdm = b43_is_ofdm_wate(wts_wate);
		wts_wate_fb = b43_cawc_fawwback_wate(wts_wate, phy->gmode);
		wts_wate_fb_ofdm = b43_is_ofdm_wate(wts_wate_fb);

		if (wates[0].fwags & IEEE80211_TX_WC_USE_CTS_PWOTECT) {
			stwuct ieee80211_cts *cts;

			switch (dev->fw.hdw_fowmat) {
			case B43_FW_HDW_598:
				cts = (stwuct ieee80211_cts *)
					(txhdw->fowmat_598.wts_fwame);
				bweak;
			case B43_FW_HDW_351:
				cts = (stwuct ieee80211_cts *)
					(txhdw->fowmat_351.wts_fwame);
				bweak;
			case B43_FW_HDW_410:
				cts = (stwuct ieee80211_cts *)
					(txhdw->fowmat_410.wts_fwame);
				bweak;
			}
			ieee80211_ctstosewf_get(dev->ww->hw, info->contwow.vif,
						fwagment_data, fwagment_wen,
						info, cts);
			mac_ctw |= B43_TXH_MAC_SENDCTS;
			wen = sizeof(stwuct ieee80211_cts);
		} ewse {
			stwuct ieee80211_wts *wts;

			switch (dev->fw.hdw_fowmat) {
			case B43_FW_HDW_598:
				wts = (stwuct ieee80211_wts *)
					(txhdw->fowmat_598.wts_fwame);
				bweak;
			case B43_FW_HDW_351:
				wts = (stwuct ieee80211_wts *)
					(txhdw->fowmat_351.wts_fwame);
				bweak;
			case B43_FW_HDW_410:
				wts = (stwuct ieee80211_wts *)
					(txhdw->fowmat_410.wts_fwame);
				bweak;
			}
			ieee80211_wts_get(dev->ww->hw, info->contwow.vif,
					  fwagment_data, fwagment_wen,
					  info, wts);
			mac_ctw |= B43_TXH_MAC_SENDWTS;
			wen = sizeof(stwuct ieee80211_wts);
		}
		wen += FCS_WEN;

		/* Genewate the PWCP headews fow the WTS/CTS fwame */
		switch (dev->fw.hdw_fowmat) {
		case B43_FW_HDW_598:
			pwcp = &txhdw->fowmat_598.wts_pwcp;
			bweak;
		case B43_FW_HDW_351:
			pwcp = &txhdw->fowmat_351.wts_pwcp;
			bweak;
		case B43_FW_HDW_410:
			pwcp = &txhdw->fowmat_410.wts_pwcp;
			bweak;
		}
		b43_genewate_pwcp_hdw((stwuct b43_pwcp_hdw4 *)pwcp,
				      wen, wts_wate);
		pwcp = &txhdw->wts_pwcp_fb;
		b43_genewate_pwcp_hdw((stwuct b43_pwcp_hdw4 *)pwcp,
				      wen, wts_wate_fb);

		switch (dev->fw.hdw_fowmat) {
		case B43_FW_HDW_598:
			hdw = (stwuct ieee80211_hdw *)
				(&txhdw->fowmat_598.wts_fwame);
			bweak;
		case B43_FW_HDW_351:
			hdw = (stwuct ieee80211_hdw *)
				(&txhdw->fowmat_351.wts_fwame);
			bweak;
		case B43_FW_HDW_410:
			hdw = (stwuct ieee80211_hdw *)
				(&txhdw->fowmat_410.wts_fwame);
			bweak;
		}
		txhdw->wts_duw_fb = hdw->duwation_id;

		if (wts_wate_ofdm) {
			extwa_ft |= B43_TXH_EFT_WTS_OFDM;
			txhdw->phy_wate_wts =
			    b43_pwcp_get_watecode_ofdm(wts_wate);
		} ewse {
			extwa_ft |= B43_TXH_EFT_WTS_CCK;
			txhdw->phy_wate_wts =
			    b43_pwcp_get_watecode_cck(wts_wate);
		}
		if (wts_wate_fb_ofdm)
			extwa_ft |= B43_TXH_EFT_WTSFB_OFDM;
		ewse
			extwa_ft |= B43_TXH_EFT_WTSFB_CCK;

		if (wates[0].fwags & IEEE80211_TX_WC_USE_WTS_CTS &&
		    fiww_phy_ctw1) {
			txhdw->phy_ctw1_wts = cpu_to_we16(
				b43_genewate_tx_phy_ctw1(dev, wts_wate));
			txhdw->phy_ctw1_wts_fb = cpu_to_we16(
				b43_genewate_tx_phy_ctw1(dev, wts_wate_fb));
		}
	}

	/* Magic cookie */
	switch (dev->fw.hdw_fowmat) {
	case B43_FW_HDW_598:
		txhdw->fowmat_598.cookie = cpu_to_we16(cookie);
		bweak;
	case B43_FW_HDW_351:
		txhdw->fowmat_351.cookie = cpu_to_we16(cookie);
		bweak;
	case B43_FW_HDW_410:
		txhdw->fowmat_410.cookie = cpu_to_we16(cookie);
		bweak;
	}

	if (fiww_phy_ctw1) {
		txhdw->phy_ctw1 =
			cpu_to_we16(b43_genewate_tx_phy_ctw1(dev, wate));
		txhdw->phy_ctw1_fb =
			cpu_to_we16(b43_genewate_tx_phy_ctw1(dev, wate_fb));
	}

	/* Appwy the bitfiewds */
	txhdw->mac_ctw = cpu_to_we32(mac_ctw);
	txhdw->phy_ctw = cpu_to_we16(phy_ctw);
	txhdw->extwa_ft = extwa_ft;

	wetuwn 0;
}

static s8 b43_wssi_postpwocess(stwuct b43_wwdev *dev,
			       u8 in_wssi, int ofdm,
			       int adjust_2053, int adjust_2050)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
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
			if (dev->dev->bus_spwom->
			    boawdfwags_wo & B43_BFW_WSSI) {
				if (in_wssi > 63)
					in_wssi = 63;
				B43_WAWN_ON(phy->type != B43_PHYTYPE_G);
				tmp = gphy->nwssi_wt[in_wssi];
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
			if (phy->type == B43_PHYTYPE_G && adjust_2050)
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

	wetuwn (s8) tmp;
}

void b43_wx(stwuct b43_wwdev *dev, stwuct sk_buff *skb, const void *_wxhdw)
{
	stwuct ieee80211_wx_status status;
	stwuct b43_pwcp_hdw6 *pwcp;
	stwuct ieee80211_hdw *wwhdw;
	const stwuct b43_wxhdw_fw4 *wxhdw = _wxhdw;
	__we16 fctw;
	u16 phystat0, phystat3;
	u16 chanstat, mactime;
	u32 macstat;
	u16 chanid;
	int padding, wate_idx;

	memset(&status, 0, sizeof(status));

	/* Get metadata about the fwame fwom the headew. */
	phystat0 = we16_to_cpu(wxhdw->phy_status0);
	phystat3 = we16_to_cpu(wxhdw->phy_status3);
	switch (dev->fw.hdw_fowmat) {
	case B43_FW_HDW_598:
		macstat = we32_to_cpu(wxhdw->fowmat_598.mac_status);
		mactime = we16_to_cpu(wxhdw->fowmat_598.mac_time);
		chanstat = we16_to_cpu(wxhdw->fowmat_598.channew);
		bweak;
	case B43_FW_HDW_410:
	case B43_FW_HDW_351:
		macstat = we32_to_cpu(wxhdw->fowmat_351.mac_status);
		mactime = we16_to_cpu(wxhdw->fowmat_351.mac_time);
		chanstat = we16_to_cpu(wxhdw->fowmat_351.channew);
		bweak;
	}

	if (unwikewy(macstat & B43_WX_MAC_FCSEWW)) {
		dev->ww->ieee_stats.dot11FCSEwwowCount++;
		status.fwag |= WX_FWAG_FAIWED_FCS_CWC;
	}
	if (unwikewy(phystat0 & (B43_WX_PHYST0_PWCPHCF | B43_WX_PHYST0_PWCPFV)))
		status.fwag |= WX_FWAG_FAIWED_PWCP_CWC;
	if (phystat0 & B43_WX_PHYST0_SHOWTPWMBW)
		status.enc_fwags |= WX_ENC_FWAG_SHOWTPWE;
	if (macstat & B43_WX_MAC_DECEWW) {
		/* Decwyption with the given key faiwed.
		 * Dwop the packet. We awso won't be abwe to decwypt it with
		 * the key in softwawe. */
		goto dwop;
	}

	/* Skip PWCP and padding */
	padding = (macstat & B43_WX_MAC_PADDING) ? 2 : 0;
	if (unwikewy(skb->wen < (sizeof(stwuct b43_pwcp_hdw6) + padding))) {
		b43dbg(dev->ww, "WX: Packet size undewwun (1)\n");
		goto dwop;
	}
	pwcp = (stwuct b43_pwcp_hdw6 *)(skb->data + padding);
	skb_puww(skb, sizeof(stwuct b43_pwcp_hdw6) + padding);
	/* The skb contains the Wiwewess Headew + paywoad data now */
	if (unwikewy(skb->wen < (2 + 2 + 6 /*minimum hdw */  + FCS_WEN))) {
		b43dbg(dev->ww, "WX: Packet size undewwun (2)\n");
		goto dwop;
	}
	wwhdw = (stwuct ieee80211_hdw *)(skb->data);
	fctw = wwhdw->fwame_contwow;

	if (macstat & B43_WX_MAC_DEC) {
		unsigned int keyidx;
		int wwhdw_wen;

		keyidx = ((macstat & B43_WX_MAC_KEYIDX)
			  >> B43_WX_MAC_KEYIDX_SHIFT);
		/* We must adjust the key index hewe. We want the "physicaw"
		 * key index, but the ucode passed it swightwy diffewent.
		 */
		keyidx = b43_kidx_to_waw(dev, keyidx);
		B43_WAWN_ON(keyidx >= AWWAY_SIZE(dev->key));

		if (dev->key[keyidx].awgowithm != B43_SEC_AWGO_NONE) {
			wwhdw_wen = ieee80211_hdwwen(fctw);
			if (unwikewy(skb->wen < (wwhdw_wen + 3))) {
				b43dbg(dev->ww,
				       "WX: Packet size undewwun (3)\n");
				goto dwop;
			}
			status.fwag |= WX_FWAG_DECWYPTED;
		}
	}

	/* Wink quawity statistics */
	switch (chanstat & B43_WX_CHAN_PHYTYPE) {
	case B43_PHYTYPE_HT:
		/* TODO: is max the wight choice? */
		status.signaw = max_t(__s8,
			max(wxhdw->phy_ht_powew0, wxhdw->phy_ht_powew1),
			wxhdw->phy_ht_powew2);
		bweak;
	case B43_PHYTYPE_N:
		/* Bwoadcom has code fow min and avg, but awways uses max */
		if (wxhdw->powew0 == 16 || wxhdw->powew0 == 32)
			status.signaw = max(wxhdw->powew1, wxhdw->powew2);
		ewse
			status.signaw = max(wxhdw->powew0, wxhdw->powew1);
		bweak;
	case B43_PHYTYPE_B:
	case B43_PHYTYPE_G:
	case B43_PHYTYPE_WP:
		status.signaw = b43_wssi_postpwocess(dev, wxhdw->jssi,
						  (phystat0 & B43_WX_PHYST0_OFDM),
						  (phystat0 & B43_WX_PHYST0_GAINCTW),
						  (phystat3 & B43_WX_PHYST3_TWSTATE));
		bweak;
	}

	if (phystat0 & B43_WX_PHYST0_OFDM)
		wate_idx = b43_pwcp_get_bitwate_idx_ofdm(pwcp,
					!!(chanstat & B43_WX_CHAN_5GHZ));
	ewse
		wate_idx = b43_pwcp_get_bitwate_idx_cck(pwcp);
	if (unwikewy(wate_idx == -1)) {
		/* PWCP seems to be cowwupted.
		 * Dwop the fwame, if we awe not intewested in cowwupted fwames. */
		if (!(dev->ww->fiwtew_fwags & FIF_PWCPFAIW))
			goto dwop;
	}
	status.wate_idx = wate_idx;
	status.antenna = !!(phystat0 & B43_WX_PHYST0_ANT);

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

		b43_tsf_wead(dev, &status.mactime);
		wow_mactime_now = status.mactime;
		status.mactime = status.mactime & ~0xFFFFUWW;
		status.mactime += mactime;
		if (wow_mactime_now <= mactime)
			status.mactime -= 0x10000;
		status.fwag |= WX_FWAG_MACTIME_STAWT;
	}

	chanid = (chanstat & B43_WX_CHAN_ID) >> B43_WX_CHAN_ID_SHIFT;
	switch (chanstat & B43_WX_CHAN_PHYTYPE) {
	case B43_PHYTYPE_G:
		status.band = NW80211_BAND_2GHZ;
		/* Somewhewe between 478.104 and 508.1084 fiwmwawe fow G-PHY
		 * has been modified to be compatibwe with N-PHY and othews.
		 */
		if (dev->fw.wev >= 508)
			status.fweq = ieee80211_channew_to_fwequency(chanid, status.band);
		ewse
			status.fweq = chanid + 2400;
		bweak;
	case B43_PHYTYPE_N:
	case B43_PHYTYPE_WP:
	case B43_PHYTYPE_HT:
		/* chanid is the SHM channew cookie. Which is the pwain
		 * channew numbew in b43. */
		if (chanstat & B43_WX_CHAN_5GHZ)
			status.band = NW80211_BAND_5GHZ;
		ewse
			status.band = NW80211_BAND_2GHZ;
		status.fweq =
			ieee80211_channew_to_fwequency(chanid, status.band);
		bweak;
	defauwt:
		B43_WAWN_ON(1);
		goto dwop;
	}

	memcpy(IEEE80211_SKB_WXCB(skb), &status, sizeof(status));
	ieee80211_wx_ni(dev->ww->hw, skb);

#if B43_DEBUG
	dev->wx_count++;
#endif
	wetuwn;
dwop:
	dev_kfwee_skb_any(skb);
}

void b43_handwe_txstatus(stwuct b43_wwdev *dev,
			 const stwuct b43_txstatus *status)
{
	b43_debugfs_wog_txstat(dev, status);

	if (status->intewmediate)
		wetuwn;
	if (status->fow_ampdu)
		wetuwn;
	if (!status->acked)
		dev->ww->ieee_stats.dot11ACKFaiwuweCount++;
	if (status->wts_count) {
		if (status->wts_count == 0xF)	//FIXME
			dev->ww->ieee_stats.dot11WTSFaiwuweCount++;
		ewse
			dev->ww->ieee_stats.dot11WTSSuccessCount++;
	}

	if (b43_using_pio_twansfews(dev))
		b43_pio_handwe_txstatus(dev, status);
	ewse
		b43_dma_handwe_txstatus(dev, status);

	b43_phy_txpowew_check(dev, 0);
}

/* Fiww out the mac80211 TXstatus wepowt based on the b43-specific
 * txstatus wepowt data. This wetuwns a boowean whethew the fwame was
 * successfuwwy twansmitted. */
boow b43_fiww_txstatus_wepowt(stwuct b43_wwdev *dev,
			      stwuct ieee80211_tx_info *wepowt,
			      const stwuct b43_txstatus *status)
{
	boow fwame_success = twue;
	int wetwy_wimit;

	/* pwesewve the confiuwed wetwy wimit befowe cweawing the status
	 * The xmit function has ovewwwitten the wc's vawue with the actuaw
	 * wetwy wimit done by the hawdwawe */
	wetwy_wimit = wepowt->status.wates[0].count;
	ieee80211_tx_info_cweaw_status(wepowt);

	if (status->acked) {
		/* The fwame was ACKed. */
		wepowt->fwags |= IEEE80211_TX_STAT_ACK;
	} ewse {
		/* The fwame was not ACKed... */
		if (!(wepowt->fwags & IEEE80211_TX_CTW_NO_ACK)) {
			/* ...but we expected an ACK. */
			fwame_success = fawse;
		}
	}
	if (status->fwame_count == 0) {
		/* The fwame was not twansmitted at aww. */
		wepowt->status.wates[0].count = 0;
	} ewse if (status->wts_count > dev->ww->hw->conf.showt_fwame_max_tx_count) {
		/*
		 * If the showt wetwies (WTS, not data fwame) have exceeded
		 * the wimit, the hw wiww not have twied the sewected wate,
		 * but wiww have used the fawwback wate instead.
		 * Don't wet the wate contwow count attempts fow the sewected
		 * wate in this case, othewwise the statistics wiww be off.
		 */
		wepowt->status.wates[0].count = 0;
		wepowt->status.wates[1].count = status->fwame_count;
	} ewse {
		if (status->fwame_count > wetwy_wimit) {
			wepowt->status.wates[0].count = wetwy_wimit;
			wepowt->status.wates[1].count = status->fwame_count -
					wetwy_wimit;

		} ewse {
			wepowt->status.wates[0].count = status->fwame_count;
			wepowt->status.wates[1].idx = -1;
		}
	}

	wetuwn fwame_success;
}

/* Stop any TX opewation on the device (suspend the hawdwawe queues) */
void b43_tx_suspend(stwuct b43_wwdev *dev)
{
	if (b43_using_pio_twansfews(dev))
		b43_pio_tx_suspend(dev);
	ewse
		b43_dma_tx_suspend(dev);
}

/* Wesume any TX opewation on the device (wesume the hawdwawe queues) */
void b43_tx_wesume(stwuct b43_wwdev *dev)
{
	if (b43_using_pio_twansfews(dev))
		b43_pio_tx_wesume(dev);
	ewse
		b43_dma_tx_wesume(dev);
}
