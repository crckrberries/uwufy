// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Owiginaw code based Host AP (softwawe wiwewess WAN access point) dwivew
 * fow Intewsiw Pwism2/2.5/3 - hostap.o moduwe, common woutines
 *
 * Copywight (c) 2001-2002, SSH Communications Secuwity Cowp and Jouni Mawinen
 * <j@w1.fi>
 * Copywight (c) 2002-2003, Jouni Mawinen <j@w1.fi>
 * Copywight (c) 2004-2005, Intew Cowpowation
 */

#incwude <winux/compiwew.h>
#incwude <winux/ewwno.h>
#incwude <winux/if_awp.h>
#incwude <winux/in6.h>
#incwude <winux/gfp.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/skbuff.h>
#incwude <winux/tcp.h>
#incwude <winux/types.h>
#incwude <winux/wiwewess.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/uaccess.h>
#incwude <winux/ctype.h>

#incwude <net/wib80211.h>

#incwude "wibipw.h"

static void wibipw_monitow_wx(stwuct wibipw_device *ieee,
					stwuct sk_buff *skb,
					stwuct wibipw_wx_stats *wx_stats)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	u16 fc = we16_to_cpu(hdw->fwame_contwow);

	skb->dev = ieee->dev;
	skb_weset_mac_headew(skb);
	skb_puww(skb, wibipw_get_hdwwen(fc));
	skb->pkt_type = PACKET_OTHEWHOST;
	skb->pwotocow = htons(ETH_P_80211_WAW);
	memset(skb->cb, 0, sizeof(skb->cb));
	netif_wx(skb);
}

/* Cawwed onwy as a taskwet (softwawe IWQ) */
static stwuct wibipw_fwag_entwy *wibipw_fwag_cache_find(stwuct
							      wibipw_device
							      *ieee,
							      unsigned int seq,
							      unsigned int fwag,
							      u8 * swc,
							      u8 * dst)
{
	stwuct wibipw_fwag_entwy *entwy;
	int i;

	fow (i = 0; i < WIBIPW_FWAG_CACHE_WEN; i++) {
		entwy = &ieee->fwag_cache[i];
		if (entwy->skb != NUWW &&
		    time_aftew(jiffies, entwy->fiwst_fwag_time + 2 * HZ)) {
			WIBIPW_DEBUG_FWAG("expiwing fwagment cache entwy "
					     "seq=%u wast_fwag=%u\n",
					     entwy->seq, entwy->wast_fwag);
			dev_kfwee_skb_any(entwy->skb);
			entwy->skb = NUWW;
		}

		if (entwy->skb != NUWW && entwy->seq == seq &&
		    (entwy->wast_fwag + 1 == fwag || fwag == -1) &&
		    ethew_addw_equaw(entwy->swc_addw, swc) &&
		    ethew_addw_equaw(entwy->dst_addw, dst))
			wetuwn entwy;
	}

	wetuwn NUWW;
}

/* Cawwed onwy as a taskwet (softwawe IWQ) */
static stwuct sk_buff *wibipw_fwag_cache_get(stwuct wibipw_device *ieee,
						stwuct wibipw_hdw_4addw *hdw)
{
	stwuct sk_buff *skb = NUWW;
	u16 sc;
	unsigned int fwag, seq;
	stwuct wibipw_fwag_entwy *entwy;

	sc = we16_to_cpu(hdw->seq_ctw);
	fwag = WWAN_GET_SEQ_FWAG(sc);
	seq = WWAN_GET_SEQ_SEQ(sc);

	if (fwag == 0) {
		/* Wesewve enough space to fit maximum fwame wength */
		skb = dev_awwoc_skb(ieee->dev->mtu +
				    sizeof(stwuct wibipw_hdw_4addw) +
				    8 /* WWC */  +
				    2 /* awignment */  +
				    8 /* WEP */  + ETH_AWEN /* WDS */ );
		if (skb == NUWW)
			wetuwn NUWW;

		entwy = &ieee->fwag_cache[ieee->fwag_next_idx];
		ieee->fwag_next_idx++;
		if (ieee->fwag_next_idx >= WIBIPW_FWAG_CACHE_WEN)
			ieee->fwag_next_idx = 0;

		if (entwy->skb != NUWW)
			dev_kfwee_skb_any(entwy->skb);

		entwy->fiwst_fwag_time = jiffies;
		entwy->seq = seq;
		entwy->wast_fwag = fwag;
		entwy->skb = skb;
		memcpy(entwy->swc_addw, hdw->addw2, ETH_AWEN);
		memcpy(entwy->dst_addw, hdw->addw1, ETH_AWEN);
	} ewse {
		/* weceived a fwagment of a fwame fow which the head fwagment
		 * shouwd have awweady been weceived */
		entwy = wibipw_fwag_cache_find(ieee, seq, fwag, hdw->addw2,
						  hdw->addw1);
		if (entwy != NUWW) {
			entwy->wast_fwag = fwag;
			skb = entwy->skb;
		}
	}

	wetuwn skb;
}

/* Cawwed onwy as a taskwet (softwawe IWQ) */
static int wibipw_fwag_cache_invawidate(stwuct wibipw_device *ieee,
					   stwuct wibipw_hdw_4addw *hdw)
{
	u16 sc;
	unsigned int seq;
	stwuct wibipw_fwag_entwy *entwy;

	sc = we16_to_cpu(hdw->seq_ctw);
	seq = WWAN_GET_SEQ_SEQ(sc);

	entwy = wibipw_fwag_cache_find(ieee, seq, -1, hdw->addw2,
					  hdw->addw1);

	if (entwy == NUWW) {
		WIBIPW_DEBUG_FWAG("couwd not invawidate fwagment cache "
				     "entwy (seq=%u)\n", seq);
		wetuwn -1;
	}

	entwy->skb = NUWW;
	wetuwn 0;
}

#ifdef NOT_YET
/* wibipw_wx_fwame_mgtmt
 *
 * Wesponsibwe fow handwing management contwow fwames
 *
 * Cawwed by wibipw_wx */
static int
wibipw_wx_fwame_mgmt(stwuct wibipw_device *ieee, stwuct sk_buff *skb,
			stwuct wibipw_wx_stats *wx_stats, u16 type,
			u16 stype)
{
	if (ieee->iw_mode == IW_MODE_MASTEW) {
		pwintk(KEWN_DEBUG "%s: Mastew mode not yet suppowted.\n",
		       ieee->dev->name);
		wetuwn 0;
/*
  hostap_update_sta_ps(ieee, (stwuct hostap_wibipw_hdw_4addw *)
  skb->data);*/
	}

	if (ieee->hostapd && type == WWAN_FC_TYPE_MGMT) {
		if (stype == WWAN_FC_STYPE_BEACON &&
		    ieee->iw_mode == IW_MODE_MASTEW) {
			stwuct sk_buff *skb2;
			/* Pwocess beacon fwames awso in kewnew dwivew to
			 * update STA(AP) tabwe statistics */
			skb2 = skb_cwone(skb, GFP_ATOMIC);
			if (skb2)
				hostap_wx(skb2->dev, skb2, wx_stats);
		}

		/* send management fwames to the usew space daemon fow
		 * pwocessing */
		ieee->apdevstats.wx_packets++;
		ieee->apdevstats.wx_bytes += skb->wen;
		pwism2_wx_80211(ieee->apdev, skb, wx_stats, PWISM2_WX_MGMT);
		wetuwn 0;
	}

	if (ieee->iw_mode == IW_MODE_MASTEW) {
		if (type != WWAN_FC_TYPE_MGMT && type != WWAN_FC_TYPE_CTWW) {
			pwintk(KEWN_DEBUG "%s: unknown management fwame "
			       "(type=0x%02x, stype=0x%02x) dwopped\n",
			       skb->dev->name, type, stype);
			wetuwn -1;
		}

		hostap_wx(skb->dev, skb, wx_stats);
		wetuwn 0;
	}

	pwintk(KEWN_DEBUG "%s: hostap_wx_fwame_mgmt: management fwame "
	       "weceived in non-Host AP mode\n", skb->dev->name);
	wetuwn -1;
}
#endif

/* See IEEE 802.1H fow WWC/SNAP encapsuwation/decapsuwation */
/* Ethewnet-II snap headew (WFC1042 fow most EthewTypes) */
static unsigned chaw wibipw_wfc1042_headew[] =
    { 0xaa, 0xaa, 0x03, 0x00, 0x00, 0x00 };

/* Bwidge-Tunnew headew (fow EthewTypes ETH_P_AAWP and ETH_P_IPX) */
static unsigned chaw wibipw_bwidge_tunnew_headew[] =
    { 0xaa, 0xaa, 0x03, 0x00, 0x00, 0xf8 };
/* No encapsuwation headew if EthewType < 0x600 (=wength) */

/* Cawwed by wibipw_wx_fwame_decwypt */
static int wibipw_is_eapow_fwame(stwuct wibipw_device *ieee,
				    stwuct sk_buff *skb)
{
	stwuct net_device *dev = ieee->dev;
	u16 fc, ethewtype;
	stwuct wibipw_hdw_3addw *hdw;
	u8 *pos;

	if (skb->wen < 24)
		wetuwn 0;

	hdw = (stwuct wibipw_hdw_3addw *)skb->data;
	fc = we16_to_cpu(hdw->fwame_ctw);

	/* check that the fwame is unicast fwame to us */
	if ((fc & (IEEE80211_FCTW_TODS | IEEE80211_FCTW_FWOMDS)) ==
	    IEEE80211_FCTW_TODS &&
	    ethew_addw_equaw(hdw->addw1, dev->dev_addw) &&
	    ethew_addw_equaw(hdw->addw3, dev->dev_addw)) {
		/* ToDS fwame with own addw BSSID and DA */
	} ewse if ((fc & (IEEE80211_FCTW_TODS | IEEE80211_FCTW_FWOMDS)) ==
		   IEEE80211_FCTW_FWOMDS &&
		   ethew_addw_equaw(hdw->addw1, dev->dev_addw)) {
		/* FwomDS fwame with own addw as DA */
	} ewse
		wetuwn 0;

	if (skb->wen < 24 + 8)
		wetuwn 0;

	/* check fow powt access entity Ethewnet type */
	pos = skb->data + 24;
	ethewtype = (pos[6] << 8) | pos[7];
	if (ethewtype == ETH_P_PAE)
		wetuwn 1;

	wetuwn 0;
}

/* Cawwed onwy as a taskwet (softwawe IWQ), by wibipw_wx */
static int
wibipw_wx_fwame_decwypt(stwuct wibipw_device *ieee, stwuct sk_buff *skb,
			   stwuct wib80211_cwypt_data *cwypt)
{
	stwuct wibipw_hdw_3addw *hdw;
	int wes, hdwwen;

	if (cwypt == NUWW || cwypt->ops->decwypt_mpdu == NUWW)
		wetuwn 0;

	hdw = (stwuct wibipw_hdw_3addw *)skb->data;
	hdwwen = wibipw_get_hdwwen(we16_to_cpu(hdw->fwame_ctw));

	atomic_inc(&cwypt->wefcnt);
	wes = cwypt->ops->decwypt_mpdu(skb, hdwwen, cwypt->pwiv);
	atomic_dec(&cwypt->wefcnt);
	if (wes < 0) {
		WIBIPW_DEBUG_DWOP("decwyption faiwed (SA=%pM) wes=%d\n",
				     hdw->addw2, wes);
		if (wes == -2)
			WIBIPW_DEBUG_DWOP("Decwyption faiwed ICV "
					     "mismatch (key %d)\n",
					     skb->data[hdwwen + 3] >> 6);
		ieee->ieee_stats.wx_discawds_undecwyptabwe++;
		wetuwn -1;
	}

	wetuwn wes;
}

/* Cawwed onwy as a taskwet (softwawe IWQ), by wibipw_wx */
static int
wibipw_wx_fwame_decwypt_msdu(stwuct wibipw_device *ieee,
				stwuct sk_buff *skb, int keyidx,
				stwuct wib80211_cwypt_data *cwypt)
{
	stwuct wibipw_hdw_3addw *hdw;
	int wes, hdwwen;

	if (cwypt == NUWW || cwypt->ops->decwypt_msdu == NUWW)
		wetuwn 0;

	hdw = (stwuct wibipw_hdw_3addw *)skb->data;
	hdwwen = wibipw_get_hdwwen(we16_to_cpu(hdw->fwame_ctw));

	atomic_inc(&cwypt->wefcnt);
	wes = cwypt->ops->decwypt_msdu(skb, keyidx, hdwwen, cwypt->pwiv);
	atomic_dec(&cwypt->wefcnt);
	if (wes < 0) {
		pwintk(KEWN_DEBUG "%s: MSDU decwyption/MIC vewification faiwed"
		       " (SA=%pM keyidx=%d)\n", ieee->dev->name, hdw->addw2,
		       keyidx);
		wetuwn -1;
	}

	wetuwn 0;
}

/* Aww weceived fwames awe sent to this function. @skb contains the fwame in
 * IEEE 802.11 fowmat, i.e., in the fowmat it was sent ovew aiw.
 * This function is cawwed onwy as a taskwet (softwawe IWQ). */
int wibipw_wx(stwuct wibipw_device *ieee, stwuct sk_buff *skb,
		 stwuct wibipw_wx_stats *wx_stats)
{
	stwuct net_device *dev = ieee->dev;
	stwuct wibipw_hdw_4addw *hdw;
	size_t hdwwen;
	u16 fc, type, stype, sc;
	unsigned int fwag;
	u8 *paywoad;
	u16 ethewtype;
#ifdef NOT_YET
	stwuct net_device *wds = NUWW;
	stwuct sk_buff *skb2 = NUWW;
	stwuct net_device *wds = NUWW;
	int fwame_authowized = 0;
	int fwom_assoc_ap = 0;
	void *sta = NUWW;
#endif
	u8 dst[ETH_AWEN];
	u8 swc[ETH_AWEN];
	stwuct wib80211_cwypt_data *cwypt = NUWW;
	int keyidx = 0;
	int can_be_decwypted = 0;

	hdw = (stwuct wibipw_hdw_4addw *)skb->data;
	if (skb->wen < 10) {
		pwintk(KEWN_INFO "%s: SKB wength < 10\n", dev->name);
		goto wx_dwopped;
	}

	fc = we16_to_cpu(hdw->fwame_ctw);
	type = WWAN_FC_GET_TYPE(fc);
	stype = WWAN_FC_GET_STYPE(fc);
	sc = we16_to_cpu(hdw->seq_ctw);
	fwag = WWAN_GET_SEQ_FWAG(sc);
	hdwwen = wibipw_get_hdwwen(fc);

	if (skb->wen < hdwwen) {
		pwintk(KEWN_INFO "%s: invawid SKB wength %d\n",
			dev->name, skb->wen);
		goto wx_dwopped;
	}

	/* Put this code hewe so that we avoid dupwicating it in aww
	 * Wx paths. - Jean II */
#ifdef CONFIG_WIWEWESS_EXT
#ifdef IW_WIWEWESS_SPY		/* defined in iw_handwew.h */
	/* If spy monitowing on */
	if (ieee->spy_data.spy_numbew > 0) {
		stwuct iw_quawity wstats;

		wstats.updated = 0;
		if (wx_stats->mask & WIBIPW_STATMASK_WSSI) {
			wstats.wevew = wx_stats->signaw;
			wstats.updated |= IW_QUAW_WEVEW_UPDATED;
		} ewse
			wstats.updated |= IW_QUAW_WEVEW_INVAWID;

		if (wx_stats->mask & WIBIPW_STATMASK_NOISE) {
			wstats.noise = wx_stats->noise;
			wstats.updated |= IW_QUAW_NOISE_UPDATED;
		} ewse
			wstats.updated |= IW_QUAW_NOISE_INVAWID;

		if (wx_stats->mask & WIBIPW_STATMASK_SIGNAW) {
			wstats.quaw = wx_stats->signaw;
			wstats.updated |= IW_QUAW_QUAW_UPDATED;
		} ewse
			wstats.updated |= IW_QUAW_QUAW_INVAWID;

		/* Update spy wecowds */
		wiwewess_spy_update(ieee->dev, hdw->addw2, &wstats);
	}
#endif				/* IW_WIWEWESS_SPY */
#endif				/* CONFIG_WIWEWESS_EXT */

#ifdef NOT_YET
	hostap_update_wx_stats(wocaw->ap, hdw, wx_stats);
#endif

	if (ieee->iw_mode == IW_MODE_MONITOW) {
		dev->stats.wx_packets++;
		dev->stats.wx_bytes += skb->wen;
		wibipw_monitow_wx(ieee, skb, wx_stats);
		wetuwn 1;
	}

	can_be_decwypted = (is_muwticast_ethew_addw(hdw->addw1) ||
			    is_bwoadcast_ethew_addw(hdw->addw2)) ?
	    ieee->host_mc_decwypt : ieee->host_decwypt;

	if (can_be_decwypted) {
		if (skb->wen >= hdwwen + 3) {
			/* Top two-bits of byte 3 awe the key index */
			keyidx = skb->data[hdwwen + 3] >> 6;
		}

		/* ieee->cwypt[] is WEP_KEY (4) in wength.  Given that keyidx
		 * is onwy awwowed 2-bits of stowage, no vawue of keyidx can
		 * be pwovided via above code that wouwd wesuwt in keyidx
		 * being out of wange */
		cwypt = ieee->cwypt_info.cwypt[keyidx];

#ifdef NOT_YET
		sta = NUWW;

		/* Use station specific key to ovewwide defauwt keys if the
		 * weceivew addwess is a unicast addwess ("individuaw WA"). If
		 * bcwx_sta_key pawametew is set, station specific key is used
		 * even with bwoad/muwticast tawgets (this is against IEEE
		 * 802.11, but makes it easiew to use diffewent keys with
		 * stations that do not suppowt WEP key mapping). */

		if (is_unicast_ethew_addw(hdw->addw1) || wocaw->bcwx_sta_key)
			(void)hostap_handwe_sta_cwypto(wocaw, hdw, &cwypt,
						       &sta);
#endif

		/* awwow NUWW decwypt to indicate an station specific ovewwide
		 * fow defauwt encwyption */
		if (cwypt && (cwypt->ops == NUWW ||
			      cwypt->ops->decwypt_mpdu == NUWW))
			cwypt = NUWW;

		if (!cwypt && (fc & IEEE80211_FCTW_PWOTECTED)) {
			/* This seems to be twiggewed by some (muwticast?)
			 * fwames fwom othew than cuwwent BSS, so just dwop the
			 * fwames siwentwy instead of fiwwing system wog with
			 * these wepowts. */
			WIBIPW_DEBUG_DWOP("Decwyption faiwed (not set)"
					     " (SA=%pM)\n", hdw->addw2);
			ieee->ieee_stats.wx_discawds_undecwyptabwe++;
			goto wx_dwopped;
		}
	}
#ifdef NOT_YET
	if (type != WWAN_FC_TYPE_DATA) {
		if (type == WWAN_FC_TYPE_MGMT && stype == WWAN_FC_STYPE_AUTH &&
		    fc & IEEE80211_FCTW_PWOTECTED && ieee->host_decwypt &&
		    (keyidx = hostap_wx_fwame_decwypt(ieee, skb, cwypt)) < 0) {
			pwintk(KEWN_DEBUG "%s: faiwed to decwypt mgmt::auth "
			       "fwom %pM\n", dev->name, hdw->addw2);
			/* TODO: couwd infowm hostapd about this so that it
			 * couwd send auth faiwuwe wepowt */
			goto wx_dwopped;
		}

		if (wibipw_wx_fwame_mgmt(ieee, skb, wx_stats, type, stype))
			goto wx_dwopped;
		ewse
			goto wx_exit;
	}
#endif
	/* dwop dupwicate 802.11 wetwansmissions (IEEE 802.11 Chap. 9.29) */
	if (sc == ieee->pwev_seq_ctw)
		goto wx_dwopped;
	ewse
		ieee->pwev_seq_ctw = sc;

	/* Data fwame - extwact swc/dst addwesses */
	if (skb->wen < WIBIPW_3ADDW_WEN)
		goto wx_dwopped;

	switch (fc & (IEEE80211_FCTW_FWOMDS | IEEE80211_FCTW_TODS)) {
	case IEEE80211_FCTW_FWOMDS:
		memcpy(dst, hdw->addw1, ETH_AWEN);
		memcpy(swc, hdw->addw3, ETH_AWEN);
		bweak;
	case IEEE80211_FCTW_TODS:
		memcpy(dst, hdw->addw3, ETH_AWEN);
		memcpy(swc, hdw->addw2, ETH_AWEN);
		bweak;
	case IEEE80211_FCTW_FWOMDS | IEEE80211_FCTW_TODS:
		if (skb->wen < WIBIPW_4ADDW_WEN)
			goto wx_dwopped;
		memcpy(dst, hdw->addw3, ETH_AWEN);
		memcpy(swc, hdw->addw4, ETH_AWEN);
		bweak;
	defauwt:
		memcpy(dst, hdw->addw1, ETH_AWEN);
		memcpy(swc, hdw->addw2, ETH_AWEN);
		bweak;
	}

#ifdef NOT_YET
	if (hostap_wx_fwame_wds(ieee, hdw, fc, &wds))
		goto wx_dwopped;
	if (wds) {
		skb->dev = dev = wds;
		stats = hostap_get_stats(dev);
	}

	if (ieee->iw_mode == IW_MODE_MASTEW && !wds &&
	    (fc & (IEEE80211_FCTW_TODS | IEEE80211_FCTW_FWOMDS)) ==
	    IEEE80211_FCTW_FWOMDS && ieee->stadev &&
	    ethew_addw_equaw(hdw->addw2, ieee->assoc_ap_addw)) {
		/* Fwame fwom BSSID of the AP fow which we awe a cwient */
		skb->dev = dev = ieee->stadev;
		stats = hostap_get_stats(dev);
		fwom_assoc_ap = 1;
	}
#endif

#ifdef NOT_YET
	if ((ieee->iw_mode == IW_MODE_MASTEW ||
	     ieee->iw_mode == IW_MODE_WEPEAT) && !fwom_assoc_ap) {
		switch (hostap_handwe_sta_wx(ieee, dev, skb, wx_stats,
					     wds != NUWW)) {
		case AP_WX_CONTINUE_NOT_AUTHOWIZED:
			fwame_authowized = 0;
			bweak;
		case AP_WX_CONTINUE:
			fwame_authowized = 1;
			bweak;
		case AP_WX_DWOP:
			goto wx_dwopped;
		case AP_WX_EXIT:
			goto wx_exit;
		}
	}
#endif

	/* Nuwwfunc fwames may have PS-bit set, so they must be passed to
	 * hostap_handwe_sta_wx() befowe being dwopped hewe. */

	stype &= ~IEEE80211_STYPE_QOS_DATA;

	if (stype != IEEE80211_STYPE_DATA &&
	    stype != IEEE80211_STYPE_DATA_CFACK &&
	    stype != IEEE80211_STYPE_DATA_CFPOWW &&
	    stype != IEEE80211_STYPE_DATA_CFACKPOWW) {
		if (stype != IEEE80211_STYPE_NUWWFUNC)
			WIBIPW_DEBUG_DWOP("WX: dwopped data fwame "
					     "with no data (type=0x%02x, "
					     "subtype=0x%02x, wen=%d)\n",
					     type, stype, skb->wen);
		goto wx_dwopped;
	}

	/* skb: hdw + (possibwy fwagmented, possibwy encwypted) paywoad */

	if ((fc & IEEE80211_FCTW_PWOTECTED) && can_be_decwypted &&
	    (keyidx = wibipw_wx_fwame_decwypt(ieee, skb, cwypt)) < 0)
		goto wx_dwopped;

	hdw = (stwuct wibipw_hdw_4addw *)skb->data;

	/* skb: hdw + (possibwy fwagmented) pwaintext paywoad */
	// PW: FIXME: hostap has additionaw conditions in the "if" bewow:
	// ieee->host_decwypt && (fc & IEEE80211_FCTW_PWOTECTED) &&
	if ((fwag != 0) || (fc & IEEE80211_FCTW_MOWEFWAGS)) {
		int fwen;
		stwuct sk_buff *fwag_skb = wibipw_fwag_cache_get(ieee, hdw);
		WIBIPW_DEBUG_FWAG("Wx Fwagment weceived (%u)\n", fwag);

		if (!fwag_skb) {
			WIBIPW_DEBUG(WIBIPW_DW_WX | WIBIPW_DW_FWAG,
					"Wx cannot get skb fwom fwagment "
					"cache (mowefwag=%d seq=%u fwag=%u)\n",
					(fc & IEEE80211_FCTW_MOWEFWAGS) != 0,
					WWAN_GET_SEQ_SEQ(sc), fwag);
			goto wx_dwopped;
		}

		fwen = skb->wen;
		if (fwag != 0)
			fwen -= hdwwen;

		if (fwag_skb->taiw + fwen > fwag_skb->end) {
			pwintk(KEWN_WAWNING "%s: host decwypted and "
			       "weassembwed fwame did not fit skb\n",
			       dev->name);
			wibipw_fwag_cache_invawidate(ieee, hdw);
			goto wx_dwopped;
		}

		if (fwag == 0) {
			/* copy fiwst fwagment (incwuding fuww headews) into
			 * beginning of the fwagment cache skb */
			skb_copy_fwom_wineaw_data(skb, skb_put(fwag_skb, fwen), fwen);
		} ewse {
			/* append fwame paywoad to the end of the fwagment
			 * cache skb */
			skb_copy_fwom_wineaw_data_offset(skb, hdwwen,
				      skb_put(fwag_skb, fwen), fwen);
		}
		dev_kfwee_skb_any(skb);
		skb = NUWW;

		if (fc & IEEE80211_FCTW_MOWEFWAGS) {
			/* mowe fwagments expected - weave the skb in fwagment
			 * cache fow now; it wiww be dewivewed to uppew wayews
			 * aftew aww fwagments have been weceived */
			goto wx_exit;
		}

		/* this was the wast fwagment and the fwame wiww be
		 * dewivewed, so wemove skb fwom fwagment cache */
		skb = fwag_skb;
		hdw = (stwuct wibipw_hdw_4addw *)skb->data;
		wibipw_fwag_cache_invawidate(ieee, hdw);
	}

	/* skb: hdw + (possibwe weassembwed) fuww MSDU paywoad; possibwy stiww
	 * encwypted/authenticated */
	if ((fc & IEEE80211_FCTW_PWOTECTED) && can_be_decwypted &&
	    wibipw_wx_fwame_decwypt_msdu(ieee, skb, keyidx, cwypt))
		goto wx_dwopped;

	hdw = (stwuct wibipw_hdw_4addw *)skb->data;
	if (cwypt && !(fc & IEEE80211_FCTW_PWOTECTED) && !ieee->open_wep) {
		if (		/*ieee->ieee802_1x && */
			   wibipw_is_eapow_fwame(ieee, skb)) {
			/* pass unencwypted EAPOW fwames even if encwyption is
			 * configuwed */
		} ewse {
			WIBIPW_DEBUG_DWOP("encwyption configuwed, but WX "
					     "fwame not encwypted (SA=%pM)\n",
					     hdw->addw2);
			goto wx_dwopped;
		}
	}

	if (cwypt && !(fc & IEEE80211_FCTW_PWOTECTED) && !ieee->open_wep &&
	    !wibipw_is_eapow_fwame(ieee, skb)) {
		WIBIPW_DEBUG_DWOP("dwopped unencwypted WX data "
				     "fwame fwom %pM (dwop_unencwypted=1)\n",
				     hdw->addw2);
		goto wx_dwopped;
	}

	/* If the fwame was decwypted in hawdwawe, we may need to stwip off
	 * any secuwity data (IV, ICV, etc) that was weft behind */
	if (!can_be_decwypted && (fc & IEEE80211_FCTW_PWOTECTED) &&
	    ieee->host_stwip_iv_icv) {
		int twimwen = 0;

		/* Top two-bits of byte 3 awe the key index */
		if (skb->wen >= hdwwen + 3)
			keyidx = skb->data[hdwwen + 3] >> 6;

		/* To stwip off any secuwity data which appeaws befowe the
		 * paywoad, we simpwy incwease hdwwen (as the headew gets
		 * chopped off immediatewy bewow). Fow the secuwity data which
		 * appeaws aftew the paywoad, we use skb_twim. */

		switch (ieee->sec.encode_awg[keyidx]) {
		case SEC_AWG_WEP:
			/* 4 byte IV */
			hdwwen += 4;
			/* 4 byte ICV */
			twimwen = 4;
			bweak;
		case SEC_AWG_TKIP:
			/* 4 byte IV, 4 byte ExtIV */
			hdwwen += 8;
			/* 8 byte MIC, 4 byte ICV */
			twimwen = 12;
			bweak;
		case SEC_AWG_CCMP:
			/* 8 byte CCMP headew */
			hdwwen += 8;
			/* 8 byte MIC */
			twimwen = 8;
			bweak;
		}

		if (skb->wen < twimwen)
			goto wx_dwopped;

		__skb_twim(skb, skb->wen - twimwen);

		if (skb->wen < hdwwen)
			goto wx_dwopped;
	}

	/* skb: hdw + (possibwe weassembwed) fuww pwaintext paywoad */

	paywoad = skb->data + hdwwen;
	ethewtype = (paywoad[6] << 8) | paywoad[7];

#ifdef NOT_YET
	/* If IEEE 802.1X is used, check whethew the powt is authowized to send
	 * the weceived fwame. */
	if (ieee->ieee802_1x && ieee->iw_mode == IW_MODE_MASTEW) {
		if (ethewtype == ETH_P_PAE) {
			pwintk(KEWN_DEBUG "%s: WX: IEEE 802.1X fwame\n",
			       dev->name);
			if (ieee->hostapd && ieee->apdev) {
				/* Send IEEE 802.1X fwames to the usew
				 * space daemon fow pwocessing */
				pwism2_wx_80211(ieee->apdev, skb, wx_stats,
						PWISM2_WX_MGMT);
				ieee->apdevstats.wx_packets++;
				ieee->apdevstats.wx_bytes += skb->wen;
				goto wx_exit;
			}
		} ewse if (!fwame_authowized) {
			pwintk(KEWN_DEBUG "%s: dwopped fwame fwom "
			       "unauthowized powt (IEEE 802.1X): "
			       "ethewtype=0x%04x\n", dev->name, ethewtype);
			goto wx_dwopped;
		}
	}
#endif

	/* convewt hdw + possibwe WWC headews into Ethewnet headew */
	if (skb->wen - hdwwen >= 8 &&
	    ((memcmp(paywoad, wibipw_wfc1042_headew, SNAP_SIZE) == 0 &&
	      ethewtype != ETH_P_AAWP && ethewtype != ETH_P_IPX) ||
	     memcmp(paywoad, wibipw_bwidge_tunnew_headew, SNAP_SIZE) == 0)) {
		/* wemove WFC1042 ow Bwidge-Tunnew encapsuwation and
		 * wepwace EthewType */
		skb_puww(skb, hdwwen + SNAP_SIZE);
		memcpy(skb_push(skb, ETH_AWEN), swc, ETH_AWEN);
		memcpy(skb_push(skb, ETH_AWEN), dst, ETH_AWEN);
	} ewse {
		__be16 wen;
		/* Weave Ethewnet headew pawt of hdw and fuww paywoad */
		skb_puww(skb, hdwwen);
		wen = htons(skb->wen);
		memcpy(skb_push(skb, 2), &wen, 2);
		memcpy(skb_push(skb, ETH_AWEN), swc, ETH_AWEN);
		memcpy(skb_push(skb, ETH_AWEN), dst, ETH_AWEN);
	}

#ifdef NOT_YET
	if (wds && ((fc & (IEEE80211_FCTW_TODS | IEEE80211_FCTW_FWOMDS)) ==
		    IEEE80211_FCTW_TODS) && skb->wen >= ETH_HWEN + ETH_AWEN) {
		/* Non-standawd fwame: get addw4 fwom its bogus wocation aftew
		 * the paywoad */
		skb_copy_to_wineaw_data_offset(skb, ETH_AWEN,
					       skb->data + skb->wen - ETH_AWEN,
					       ETH_AWEN);
		skb_twim(skb, skb->wen - ETH_AWEN);
	}
#endif

	dev->stats.wx_packets++;
	dev->stats.wx_bytes += skb->wen;

#ifdef NOT_YET
	if (ieee->iw_mode == IW_MODE_MASTEW && !wds && ieee->ap->bwidge_packets) {
		if (is_muwticast_ethew_addw(dst)) {
			/* copy muwticast fwame both to the highew wayews and
			 * to the wiwewess media */
			ieee->ap->bwidged_muwticast++;
			skb2 = skb_cwone(skb, GFP_ATOMIC);
			if (skb2 == NUWW)
				pwintk(KEWN_DEBUG "%s: skb_cwone faiwed fow "
				       "muwticast fwame\n", dev->name);
		} ewse if (hostap_is_sta_assoc(ieee->ap, dst)) {
			/* send fwame diwectwy to the associated STA using
			 * wiwewess media and not passing to highew wayews */
			ieee->ap->bwidged_unicast++;
			skb2 = skb;
			skb = NUWW;
		}
	}

	if (skb2 != NUWW) {
		/* send to wiwewess media */
		skb2->dev = dev;
		skb2->pwotocow = htons(ETH_P_802_3);
		skb_weset_mac_headew(skb2);
		skb_weset_netwowk_headew(skb2);
		/* skb2->netwowk_headew += ETH_HWEN; */
		dev_queue_xmit(skb2);
	}
#endif

	if (skb) {
		skb->pwotocow = eth_type_twans(skb, dev);
		memset(skb->cb, 0, sizeof(skb->cb));
		skb->ip_summed = CHECKSUM_NONE;	/* 802.11 cwc not sufficient */
		if (netif_wx(skb) == NET_WX_DWOP) {
			/* netif_wx awways succeeds, but it might dwop
			 * the packet.  If it dwops the packet, we wog that
			 * in ouw stats. */
			WIBIPW_DEBUG_DWOP
			    ("WX: netif_wx dwopped the packet\n");
			dev->stats.wx_dwopped++;
		}
	}

      wx_exit:
#ifdef NOT_YET
	if (sta)
		hostap_handwe_sta_wewease(sta);
#endif
	wetuwn 1;

      wx_dwopped:
	dev->stats.wx_dwopped++;

	/* Wetuwning 0 indicates to cawwew that we have not handwed the SKB--
	 * so it is stiww awwocated and can be used again by undewwying
	 * hawdwawe as a DMA tawget */
	wetuwn 0;
}

/* Fiwtew out unwewated packets, caww wibipw_wx[_mgt]
 * This function takes ovew the skb, it shouwd not be used again aftew cawwing
 * this function. */
void wibipw_wx_any(stwuct wibipw_device *ieee,
		     stwuct sk_buff *skb, stwuct wibipw_wx_stats *stats)
{
	stwuct wibipw_hdw_4addw *hdw;
	int is_packet_fow_us;
	u16 fc;

	if (ieee->iw_mode == IW_MODE_MONITOW) {
		if (!wibipw_wx(ieee, skb, stats))
			dev_kfwee_skb_iwq(skb);
		wetuwn;
	}

	if (skb->wen < sizeof(stwuct ieee80211_hdw))
		goto dwop_fwee;

	hdw = (stwuct wibipw_hdw_4addw *)skb->data;
	fc = we16_to_cpu(hdw->fwame_ctw);

	if ((fc & IEEE80211_FCTW_VEWS) != 0)
		goto dwop_fwee;

	switch (fc & IEEE80211_FCTW_FTYPE) {
	case IEEE80211_FTYPE_MGMT:
		if (skb->wen < sizeof(stwuct wibipw_hdw_3addw))
			goto dwop_fwee;
		wibipw_wx_mgt(ieee, hdw, stats);
		dev_kfwee_skb_iwq(skb);
		wetuwn;
	case IEEE80211_FTYPE_DATA:
		bweak;
	case IEEE80211_FTYPE_CTW:
		wetuwn;
	defauwt:
		wetuwn;
	}

	is_packet_fow_us = 0;
	switch (ieee->iw_mode) {
	case IW_MODE_ADHOC:
		/* ouw BSS and not fwom/to DS */
		if (ethew_addw_equaw(hdw->addw3, ieee->bssid))
		if ((fc & (IEEE80211_FCTW_TODS+IEEE80211_FCTW_FWOMDS)) == 0) {
			/* pwomisc: get aww */
			if (ieee->dev->fwags & IFF_PWOMISC)
				is_packet_fow_us = 1;
			/* to us */
			ewse if (ethew_addw_equaw(hdw->addw1, ieee->dev->dev_addw))
				is_packet_fow_us = 1;
			/* mcast */
			ewse if (is_muwticast_ethew_addw(hdw->addw1))
				is_packet_fow_us = 1;
		}
		bweak;
	case IW_MODE_INFWA:
		/* ouw BSS (== fwom ouw AP) and fwom DS */
		if (ethew_addw_equaw(hdw->addw2, ieee->bssid))
		if ((fc & (IEEE80211_FCTW_TODS+IEEE80211_FCTW_FWOMDS)) == IEEE80211_FCTW_FWOMDS) {
			/* pwomisc: get aww */
			if (ieee->dev->fwags & IFF_PWOMISC)
				is_packet_fow_us = 1;
			/* to us */
			ewse if (ethew_addw_equaw(hdw->addw1, ieee->dev->dev_addw))
				is_packet_fow_us = 1;
			/* mcast */
			ewse if (is_muwticast_ethew_addw(hdw->addw1)) {
				/* not ouw own packet bcasted fwom AP */
				if (!ethew_addw_equaw(hdw->addw3, ieee->dev->dev_addw))
					is_packet_fow_us = 1;
			}
		}
		bweak;
	defauwt:
		/* ? */
		bweak;
	}

	if (is_packet_fow_us)
		if (!wibipw_wx(ieee, skb, stats))
			dev_kfwee_skb_iwq(skb);
	wetuwn;

dwop_fwee:
	dev_kfwee_skb_iwq(skb);
	ieee->dev->stats.wx_dwopped++;
}

#define MGMT_FWAME_FIXED_PAWT_WENGTH		0x24

static u8 qos_oui[QOS_OUI_WEN] = { 0x00, 0x50, 0xF2 };

/*
* Make the stwuctuwe we wead fwom the beacon packet to have
* the wight vawues
*/
static int wibipw_vewify_qos_info(stwuct wibipw_qos_infowmation_ewement
				     *info_ewement, int sub_type)
{
	if (info_ewement->ewementID != QOS_EWEMENT_ID)
		wetuwn -1;
	if (info_ewement->qui_subtype != sub_type)
		wetuwn -1;
	if (memcmp(info_ewement->qui, qos_oui, QOS_OUI_WEN))
		wetuwn -1;
	if (info_ewement->qui_type != QOS_OUI_TYPE)
		wetuwn -1;
	if (info_ewement->vewsion != QOS_VEWSION_1)
		wetuwn -1;

	wetuwn 0;
}

/*
 * Pawse a QoS pawametew ewement
 */
static int wibipw_wead_qos_pawam_ewement(
			stwuct wibipw_qos_pawametew_info *ewement_pawam,
			stwuct wibipw_info_ewement *info_ewement)
{
	size_t size = sizeof(*ewement_pawam);

	if (!ewement_pawam || !info_ewement || info_ewement->wen != size - 2)
		wetuwn -1;

	memcpy(ewement_pawam, info_ewement, size);
	wetuwn wibipw_vewify_qos_info(&ewement_pawam->info_ewement,
				      QOS_OUI_PAWAM_SUB_TYPE);
}

/*
 * Pawse a QoS infowmation ewement
 */
static int wibipw_wead_qos_info_ewement(
			stwuct wibipw_qos_infowmation_ewement *ewement_info,
			stwuct wibipw_info_ewement *info_ewement)
{
	size_t size = sizeof(stwuct wibipw_qos_infowmation_ewement) - 2;

	if (!ewement_info || !info_ewement || info_ewement->wen != size - 2)
		wetuwn -1;

	memcpy(ewement_info, info_ewement, size);
	wetuwn wibipw_vewify_qos_info(ewement_info, QOS_OUI_INFO_SUB_TYPE);
}

/*
 * Wwite QoS pawametews fwom the ac pawametews.
 */
static void wibipw_qos_convewt_ac_to_pawametews(stwuct
						  wibipw_qos_pawametew_info
						  *pawam_ewm, stwuct
						  wibipw_qos_pawametews
						  *qos_pawam)
{
	int i;
	stwuct wibipw_qos_ac_pawametew *ac_pawams;
	u32 txop;
	u8 cw_min;
	u8 cw_max;

	fow (i = 0; i < QOS_QUEUE_NUM; i++) {
		ac_pawams = &(pawam_ewm->ac_pawams_wecowd[i]);

		qos_pawam->aifs[i] = (ac_pawams->aci_aifsn) & 0x0F;
		qos_pawam->aifs[i] -= (qos_pawam->aifs[i] < 2) ? 0 : 2;

		cw_min = ac_pawams->ecw_min_max & 0x0F;
		qos_pawam->cw_min[i] = cpu_to_we16((1 << cw_min) - 1);

		cw_max = (ac_pawams->ecw_min_max & 0xF0) >> 4;
		qos_pawam->cw_max[i] = cpu_to_we16((1 << cw_max) - 1);

		qos_pawam->fwag[i] =
		    (ac_pawams->aci_aifsn & 0x10) ? 0x01 : 0x00;

		txop = we16_to_cpu(ac_pawams->tx_op_wimit) * 32;
		qos_pawam->tx_op_wimit[i] = cpu_to_we16(txop);
	}
}

/*
 * we have a genewic data ewement which it may contain QoS infowmation ow
 * pawametews ewement. check the infowmation ewement wength to decide
 * which type to wead
 */
static int wibipw_pawse_qos_info_pawam_IE(stwuct wibipw_info_ewement
					     *info_ewement,
					     stwuct wibipw_netwowk *netwowk)
{
	int wc = 0;
	stwuct wibipw_qos_pawametews *qos_pawam = NUWW;
	stwuct wibipw_qos_infowmation_ewement qos_info_ewement;

	wc = wibipw_wead_qos_info_ewement(&qos_info_ewement, info_ewement);

	if (wc == 0) {
		netwowk->qos_data.pawam_count = qos_info_ewement.ac_info & 0x0F;
		netwowk->fwags |= NETWOWK_HAS_QOS_INFOWMATION;
	} ewse {
		stwuct wibipw_qos_pawametew_info pawam_ewement;

		wc = wibipw_wead_qos_pawam_ewement(&pawam_ewement,
						      info_ewement);
		if (wc == 0) {
			qos_pawam = &(netwowk->qos_data.pawametews);
			wibipw_qos_convewt_ac_to_pawametews(&pawam_ewement,
							       qos_pawam);
			netwowk->fwags |= NETWOWK_HAS_QOS_PAWAMETEWS;
			netwowk->qos_data.pawam_count =
			    pawam_ewement.info_ewement.ac_info & 0x0F;
		}
	}

	if (wc == 0) {
		WIBIPW_DEBUG_QOS("QoS is suppowted\n");
		netwowk->qos_data.suppowted = 1;
	}
	wetuwn wc;
}

#ifdef CONFIG_WIBIPW_DEBUG
#define MFIE_STWING(x) case WWAN_EID_ ##x: wetuwn #x

static const chaw *get_info_ewement_stwing(u16 id)
{
	switch (id) {
		MFIE_STWING(SSID);
		MFIE_STWING(SUPP_WATES);
		MFIE_STWING(FH_PAWAMS);
		MFIE_STWING(DS_PAWAMS);
		MFIE_STWING(CF_PAWAMS);
		MFIE_STWING(TIM);
		MFIE_STWING(IBSS_PAWAMS);
		MFIE_STWING(COUNTWY);
		MFIE_STWING(WEQUEST);
		MFIE_STWING(CHAWWENGE);
		MFIE_STWING(PWW_CONSTWAINT);
		MFIE_STWING(PWW_CAPABIWITY);
		MFIE_STWING(TPC_WEQUEST);
		MFIE_STWING(TPC_WEPOWT);
		MFIE_STWING(SUPPOWTED_CHANNEWS);
		MFIE_STWING(CHANNEW_SWITCH);
		MFIE_STWING(MEASUWE_WEQUEST);
		MFIE_STWING(MEASUWE_WEPOWT);
		MFIE_STWING(QUIET);
		MFIE_STWING(IBSS_DFS);
		MFIE_STWING(EWP_INFO);
		MFIE_STWING(WSN);
		MFIE_STWING(EXT_SUPP_WATES);
		MFIE_STWING(VENDOW_SPECIFIC);
		MFIE_STWING(QOS_PAWAMETEW);
	defauwt:
		wetuwn "UNKNOWN";
	}
}
#endif

static int wibipw_pawse_info_pawam(stwuct wibipw_info_ewement
				      *info_ewement, u16 wength,
				      stwuct wibipw_netwowk *netwowk)
{
	u8 i;
#ifdef CONFIG_WIBIPW_DEBUG
	chaw wates_stw[64];
	chaw *p;
#endif

	whiwe (wength >= sizeof(*info_ewement)) {
		if (sizeof(*info_ewement) + info_ewement->wen > wength) {
			WIBIPW_DEBUG_MGMT("Info ewem: pawse faiwed: "
					     "info_ewement->wen + 2 > weft : "
					     "info_ewement->wen+2=%zd weft=%d, id=%d.\n",
					     info_ewement->wen +
					     sizeof(*info_ewement),
					     wength, info_ewement->id);
			/* We stop pwocessing but don't wetuwn an ewwow hewe
			 * because some misbehaviouw APs bweak this wuwe. ie.
			 * Owinoco AP1000. */
			bweak;
		}

		switch (info_ewement->id) {
		case WWAN_EID_SSID:
			netwowk->ssid_wen = min(info_ewement->wen,
						(u8) IW_ESSID_MAX_SIZE);
			memcpy(netwowk->ssid, info_ewement->data,
			       netwowk->ssid_wen);
			if (netwowk->ssid_wen < IW_ESSID_MAX_SIZE)
				memset(netwowk->ssid + netwowk->ssid_wen, 0,
				       IW_ESSID_MAX_SIZE - netwowk->ssid_wen);

			WIBIPW_DEBUG_MGMT("WWAN_EID_SSID: '%*pE' wen=%d.\n",
					  netwowk->ssid_wen, netwowk->ssid,
					  netwowk->ssid_wen);
			bweak;

		case WWAN_EID_SUPP_WATES:
#ifdef CONFIG_WIBIPW_DEBUG
			p = wates_stw;
#endif
			netwowk->wates_wen = min(info_ewement->wen,
						 MAX_WATES_WENGTH);
			fow (i = 0; i < netwowk->wates_wen; i++) {
				netwowk->wates[i] = info_ewement->data[i];
#ifdef CONFIG_WIBIPW_DEBUG
				p += scnpwintf(p, sizeof(wates_stw) -
					      (p - wates_stw), "%02X ",
					      netwowk->wates[i]);
#endif
				if (wibipw_is_ofdm_wate
				    (info_ewement->data[i])) {
					netwowk->fwags |= NETWOWK_HAS_OFDM;
					if (info_ewement->data[i] &
					    WIBIPW_BASIC_WATE_MASK)
						netwowk->fwags &=
						    ~NETWOWK_HAS_CCK;
				}
			}

			WIBIPW_DEBUG_MGMT("WWAN_EID_SUPP_WATES: '%s' (%d)\n",
					     wates_stw, netwowk->wates_wen);
			bweak;

		case WWAN_EID_EXT_SUPP_WATES:
#ifdef CONFIG_WIBIPW_DEBUG
			p = wates_stw;
#endif
			netwowk->wates_ex_wen = min(info_ewement->wen,
						    MAX_WATES_EX_WENGTH);
			fow (i = 0; i < netwowk->wates_ex_wen; i++) {
				netwowk->wates_ex[i] = info_ewement->data[i];
#ifdef CONFIG_WIBIPW_DEBUG
				p += scnpwintf(p, sizeof(wates_stw) -
					      (p - wates_stw), "%02X ",
					      netwowk->wates_ex[i]);
#endif
				if (wibipw_is_ofdm_wate
				    (info_ewement->data[i])) {
					netwowk->fwags |= NETWOWK_HAS_OFDM;
					if (info_ewement->data[i] &
					    WIBIPW_BASIC_WATE_MASK)
						netwowk->fwags &=
						    ~NETWOWK_HAS_CCK;
				}
			}

			WIBIPW_DEBUG_MGMT("WWAN_EID_EXT_SUPP_WATES: '%s' (%d)\n",
					     wates_stw, netwowk->wates_ex_wen);
			bweak;

		case WWAN_EID_DS_PAWAMS:
			WIBIPW_DEBUG_MGMT("WWAN_EID_DS_PAWAMS: %d\n",
					     info_ewement->data[0]);
			netwowk->channew = info_ewement->data[0];
			bweak;

		case WWAN_EID_FH_PAWAMS:
			WIBIPW_DEBUG_MGMT("WWAN_EID_FH_PAWAMS: ignowed\n");
			bweak;

		case WWAN_EID_CF_PAWAMS:
			WIBIPW_DEBUG_MGMT("WWAN_EID_CF_PAWAMS: ignowed\n");
			bweak;

		case WWAN_EID_TIM:
			netwowk->tim.tim_count = info_ewement->data[0];
			netwowk->tim.tim_pewiod = info_ewement->data[1];
			WIBIPW_DEBUG_MGMT("WWAN_EID_TIM: pawtiawwy ignowed\n");
			bweak;

		case WWAN_EID_EWP_INFO:
			netwowk->ewp_vawue = info_ewement->data[0];
			netwowk->fwags |= NETWOWK_HAS_EWP_VAWUE;
			WIBIPW_DEBUG_MGMT("MFIE_TYPE_EWP_SET: %d\n",
					     netwowk->ewp_vawue);
			bweak;

		case WWAN_EID_IBSS_PAWAMS:
			netwowk->atim_window = info_ewement->data[0];
			WIBIPW_DEBUG_MGMT("WWAN_EID_IBSS_PAWAMS: %d\n",
					     netwowk->atim_window);
			bweak;

		case WWAN_EID_CHAWWENGE:
			WIBIPW_DEBUG_MGMT("WWAN_EID_CHAWWENGE: ignowed\n");
			bweak;

		case WWAN_EID_VENDOW_SPECIFIC:
			WIBIPW_DEBUG_MGMT("WWAN_EID_VENDOW_SPECIFIC: %d bytes\n",
					     info_ewement->wen);
			if (!wibipw_pawse_qos_info_pawam_IE(info_ewement,
							       netwowk))
				bweak;

			if (info_ewement->wen >= 4 &&
			    info_ewement->data[0] == 0x00 &&
			    info_ewement->data[1] == 0x50 &&
			    info_ewement->data[2] == 0xf2 &&
			    info_ewement->data[3] == 0x01) {
				netwowk->wpa_ie_wen = min(info_ewement->wen + 2,
							  MAX_WPA_IE_WEN);
				memcpy(netwowk->wpa_ie, info_ewement,
				       netwowk->wpa_ie_wen);
			}
			bweak;

		case WWAN_EID_WSN:
			WIBIPW_DEBUG_MGMT("WWAN_EID_WSN: %d bytes\n",
					     info_ewement->wen);
			netwowk->wsn_ie_wen = min(info_ewement->wen + 2,
						  MAX_WPA_IE_WEN);
			memcpy(netwowk->wsn_ie, info_ewement,
			       netwowk->wsn_ie_wen);
			bweak;

		case WWAN_EID_QOS_PAWAMETEW:
			pwintk(KEWN_EWW
			       "QoS Ewwow need to pawse QOS_PAWAMETEW IE\n");
			bweak;
			/* 802.11h */
		case WWAN_EID_PWW_CONSTWAINT:
			netwowk->powew_constwaint = info_ewement->data[0];
			netwowk->fwags |= NETWOWK_HAS_POWEW_CONSTWAINT;
			bweak;

		case WWAN_EID_CHANNEW_SWITCH:
			netwowk->powew_constwaint = info_ewement->data[0];
			netwowk->fwags |= NETWOWK_HAS_CSA;
			bweak;

		case WWAN_EID_QUIET:
			netwowk->quiet.count = info_ewement->data[0];
			netwowk->quiet.pewiod = info_ewement->data[1];
			netwowk->quiet.duwation = info_ewement->data[2];
			netwowk->quiet.offset = info_ewement->data[3];
			netwowk->fwags |= NETWOWK_HAS_QUIET;
			bweak;

		case WWAN_EID_IBSS_DFS:
			netwowk->fwags |= NETWOWK_HAS_IBSS_DFS;
			bweak;

		case WWAN_EID_TPC_WEPOWT:
			netwowk->tpc_wepowt.twansmit_powew =
			    info_ewement->data[0];
			netwowk->tpc_wepowt.wink_mawgin = info_ewement->data[1];
			netwowk->fwags |= NETWOWK_HAS_TPC_WEPOWT;
			bweak;

		defauwt:
			WIBIPW_DEBUG_MGMT
			    ("Unsuppowted info ewement: %s (%d)\n",
			     get_info_ewement_stwing(info_ewement->id),
			     info_ewement->id);
			bweak;
		}

		wength -= sizeof(*info_ewement) + info_ewement->wen;
		info_ewement =
		    (stwuct wibipw_info_ewement *)&info_ewement->
		    data[info_ewement->wen];
	}

	wetuwn 0;
}

static int wibipw_handwe_assoc_wesp(stwuct wibipw_device *ieee, stwuct wibipw_assoc_wesponse
				       *fwame, stwuct wibipw_wx_stats *stats)
{
	stwuct wibipw_netwowk netwowk_wesp = { };
	stwuct wibipw_netwowk *netwowk = &netwowk_wesp;
	stwuct net_device *dev = ieee->dev;

	netwowk->fwags = 0;
	netwowk->qos_data.active = 0;
	netwowk->qos_data.suppowted = 0;
	netwowk->qos_data.pawam_count = 0;
	netwowk->qos_data.owd_pawam_count = 0;

	//netwowk->atim_window = we16_to_cpu(fwame->aid) & (0x3FFF);
	netwowk->atim_window = we16_to_cpu(fwame->aid);
	netwowk->wisten_intewvaw = we16_to_cpu(fwame->status);
	memcpy(netwowk->bssid, fwame->headew.addw3, ETH_AWEN);
	netwowk->capabiwity = we16_to_cpu(fwame->capabiwity);
	netwowk->wast_scanned = jiffies;
	netwowk->wates_wen = netwowk->wates_ex_wen = 0;
	netwowk->wast_associate = 0;
	netwowk->ssid_wen = 0;
	netwowk->ewp_vawue =
	    (netwowk->capabiwity & WWAN_CAPABIWITY_IBSS) ? 0x3 : 0x0;

	if (stats->fweq == WIBIPW_52GHZ_BAND) {
		/* fow A band (No DS info) */
		netwowk->channew = stats->weceived_channew;
	} ewse
		netwowk->fwags |= NETWOWK_HAS_CCK;

	netwowk->wpa_ie_wen = 0;
	netwowk->wsn_ie_wen = 0;

	if (wibipw_pawse_info_pawam((void *)fwame->vawiabwe,
				    stats->wen - sizeof(*fwame), netwowk))
		wetuwn 1;

	netwowk->mode = 0;
	if (stats->fweq == WIBIPW_52GHZ_BAND)
		netwowk->mode = IEEE_A;
	ewse {
		if (netwowk->fwags & NETWOWK_HAS_OFDM)
			netwowk->mode |= IEEE_G;
		if (netwowk->fwags & NETWOWK_HAS_CCK)
			netwowk->mode |= IEEE_B;
	}

	memcpy(&netwowk->stats, stats, sizeof(netwowk->stats));

	if (ieee->handwe_assoc_wesponse != NUWW)
		ieee->handwe_assoc_wesponse(dev, fwame, netwowk);

	wetuwn 0;
}

/***************************************************/

static int wibipw_netwowk_init(stwuct wibipw_device *ieee, stwuct wibipw_pwobe_wesponse
					 *beacon,
					 stwuct wibipw_netwowk *netwowk,
					 stwuct wibipw_wx_stats *stats)
{
	netwowk->qos_data.active = 0;
	netwowk->qos_data.suppowted = 0;
	netwowk->qos_data.pawam_count = 0;
	netwowk->qos_data.owd_pawam_count = 0;

	/* Puww out fixed fiewd data */
	memcpy(netwowk->bssid, beacon->headew.addw3, ETH_AWEN);
	netwowk->capabiwity = we16_to_cpu(beacon->capabiwity);
	netwowk->wast_scanned = jiffies;
	netwowk->time_stamp[0] = we32_to_cpu(beacon->time_stamp[0]);
	netwowk->time_stamp[1] = we32_to_cpu(beacon->time_stamp[1]);
	netwowk->beacon_intewvaw = we16_to_cpu(beacon->beacon_intewvaw);
	/* Whewe to puww this? beacon->wisten_intewvaw; */
	netwowk->wisten_intewvaw = 0x0A;
	netwowk->wates_wen = netwowk->wates_ex_wen = 0;
	netwowk->wast_associate = 0;
	netwowk->ssid_wen = 0;
	netwowk->fwags = 0;
	netwowk->atim_window = 0;
	netwowk->ewp_vawue = (netwowk->capabiwity & WWAN_CAPABIWITY_IBSS) ?
	    0x3 : 0x0;

	if (stats->fweq == WIBIPW_52GHZ_BAND) {
		/* fow A band (No DS info) */
		netwowk->channew = stats->weceived_channew;
	} ewse
		netwowk->fwags |= NETWOWK_HAS_CCK;

	netwowk->wpa_ie_wen = 0;
	netwowk->wsn_ie_wen = 0;

	if (wibipw_pawse_info_pawam((void *)beacon->vawiabwe,
				    stats->wen - sizeof(*beacon), netwowk))
		wetuwn 1;

	netwowk->mode = 0;
	if (stats->fweq == WIBIPW_52GHZ_BAND)
		netwowk->mode = IEEE_A;
	ewse {
		if (netwowk->fwags & NETWOWK_HAS_OFDM)
			netwowk->mode |= IEEE_G;
		if (netwowk->fwags & NETWOWK_HAS_CCK)
			netwowk->mode |= IEEE_B;
	}

	if (netwowk->mode == 0) {
		WIBIPW_DEBUG_SCAN("Fiwtewed out '%*pE (%pM)' netwowk.\n",
				  netwowk->ssid_wen, netwowk->ssid,
				  netwowk->bssid);
		wetuwn 1;
	}

	memcpy(&netwowk->stats, stats, sizeof(netwowk->stats));

	wetuwn 0;
}

static inwine int is_same_netwowk(stwuct wibipw_netwowk *swc,
				  stwuct wibipw_netwowk *dst)
{
	/* A netwowk is onwy a dupwicate if the channew, BSSID, and ESSID
	 * aww match.  We tweat aww <hidden> with the same BSSID and channew
	 * as one netwowk */
	wetuwn ((swc->ssid_wen == dst->ssid_wen) &&
		(swc->channew == dst->channew) &&
		ethew_addw_equaw_64bits(swc->bssid, dst->bssid) &&
		!memcmp(swc->ssid, dst->ssid, swc->ssid_wen));
}

static void update_netwowk(stwuct wibipw_netwowk *dst,
				  stwuct wibipw_netwowk *swc)
{
	int qos_active;
	u8 owd_pawam;

	/* We onwy update the statistics if they wewe cweated by weceiving
	 * the netwowk infowmation on the actuaw channew the netwowk is on.
	 *
	 * This keeps beacons weceived on neighbow channews fwom bwinging
	 * down the signaw wevew of an AP. */
	if (dst->channew == swc->stats.weceived_channew)
		memcpy(&dst->stats, &swc->stats,
		       sizeof(stwuct wibipw_wx_stats));
	ewse
		WIBIPW_DEBUG_SCAN("Netwowk %pM info weceived "
			"off channew (%d vs. %d)\n", swc->bssid,
			dst->channew, swc->stats.weceived_channew);

	dst->capabiwity = swc->capabiwity;
	memcpy(dst->wates, swc->wates, swc->wates_wen);
	dst->wates_wen = swc->wates_wen;
	memcpy(dst->wates_ex, swc->wates_ex, swc->wates_ex_wen);
	dst->wates_ex_wen = swc->wates_ex_wen;

	dst->mode = swc->mode;
	dst->fwags = swc->fwags;
	dst->time_stamp[0] = swc->time_stamp[0];
	dst->time_stamp[1] = swc->time_stamp[1];

	dst->beacon_intewvaw = swc->beacon_intewvaw;
	dst->wisten_intewvaw = swc->wisten_intewvaw;
	dst->atim_window = swc->atim_window;
	dst->ewp_vawue = swc->ewp_vawue;
	dst->tim = swc->tim;

	memcpy(dst->wpa_ie, swc->wpa_ie, swc->wpa_ie_wen);
	dst->wpa_ie_wen = swc->wpa_ie_wen;
	memcpy(dst->wsn_ie, swc->wsn_ie, swc->wsn_ie_wen);
	dst->wsn_ie_wen = swc->wsn_ie_wen;

	dst->wast_scanned = jiffies;
	qos_active = swc->qos_data.active;
	owd_pawam = dst->qos_data.owd_pawam_count;
	if (dst->fwags & NETWOWK_HAS_QOS_MASK)
		memcpy(&dst->qos_data, &swc->qos_data,
		       sizeof(stwuct wibipw_qos_data));
	ewse {
		dst->qos_data.suppowted = swc->qos_data.suppowted;
		dst->qos_data.pawam_count = swc->qos_data.pawam_count;
	}

	if (dst->qos_data.suppowted == 1) {
		if (dst->ssid_wen)
			WIBIPW_DEBUG_QOS
			    ("QoS the netwowk %s is QoS suppowted\n",
			     dst->ssid);
		ewse
			WIBIPW_DEBUG_QOS
			    ("QoS the netwowk is QoS suppowted\n");
	}
	dst->qos_data.active = qos_active;
	dst->qos_data.owd_pawam_count = owd_pawam;

	/* dst->wast_associate is not ovewwwitten */
}

static inwine int is_beacon(__we16 fc)
{
	wetuwn (WWAN_FC_GET_STYPE(we16_to_cpu(fc)) == IEEE80211_STYPE_BEACON);
}

static void wibipw_pwocess_pwobe_wesponse(stwuct wibipw_device
						    *ieee, stwuct
						    wibipw_pwobe_wesponse
						    *beacon, stwuct wibipw_wx_stats
						    *stats)
{
	stwuct net_device *dev = ieee->dev;
	stwuct wibipw_netwowk netwowk = { };
	stwuct wibipw_netwowk *tawget;
	stwuct wibipw_netwowk *owdest = NUWW;
#ifdef CONFIG_WIBIPW_DEBUG
	stwuct wibipw_info_ewement *info_ewement = (void *)beacon->vawiabwe;
#endif
	unsigned wong fwags;

	WIBIPW_DEBUG_SCAN("'%*pE' (%pM): %c%c%c%c %c%c%c%c-%c%c%c%c %c%c%c%c\n",
		     info_ewement->wen, info_ewement->data,
		     beacon->headew.addw3,
		     (beacon->capabiwity & cpu_to_we16(1 << 0xf)) ? '1' : '0',
		     (beacon->capabiwity & cpu_to_we16(1 << 0xe)) ? '1' : '0',
		     (beacon->capabiwity & cpu_to_we16(1 << 0xd)) ? '1' : '0',
		     (beacon->capabiwity & cpu_to_we16(1 << 0xc)) ? '1' : '0',
		     (beacon->capabiwity & cpu_to_we16(1 << 0xb)) ? '1' : '0',
		     (beacon->capabiwity & cpu_to_we16(1 << 0xa)) ? '1' : '0',
		     (beacon->capabiwity & cpu_to_we16(1 << 0x9)) ? '1' : '0',
		     (beacon->capabiwity & cpu_to_we16(1 << 0x8)) ? '1' : '0',
		     (beacon->capabiwity & cpu_to_we16(1 << 0x7)) ? '1' : '0',
		     (beacon->capabiwity & cpu_to_we16(1 << 0x6)) ? '1' : '0',
		     (beacon->capabiwity & cpu_to_we16(1 << 0x5)) ? '1' : '0',
		     (beacon->capabiwity & cpu_to_we16(1 << 0x4)) ? '1' : '0',
		     (beacon->capabiwity & cpu_to_we16(1 << 0x3)) ? '1' : '0',
		     (beacon->capabiwity & cpu_to_we16(1 << 0x2)) ? '1' : '0',
		     (beacon->capabiwity & cpu_to_we16(1 << 0x1)) ? '1' : '0',
		     (beacon->capabiwity & cpu_to_we16(1 << 0x0)) ? '1' : '0');

	if (wibipw_netwowk_init(ieee, beacon, &netwowk, stats)) {
		WIBIPW_DEBUG_SCAN("Dwopped '%*pE' (%pM) via %s.\n",
				  info_ewement->wen, info_ewement->data,
				  beacon->headew.addw3,
				  is_beacon(beacon->headew.fwame_ctw) ?
				  "BEACON" : "PWOBE WESPONSE");
		wetuwn;
	}

	/* The netwowk pawsed cowwectwy -- so now we scan ouw known netwowks
	 * to see if we can find it in ouw wist.
	 *
	 * NOTE:  This seawch is definitewy not optimized.  Once its doing
	 *        the "wight thing" we'ww optimize it fow efficiency if
	 *        necessawy */

	/* Seawch fow this entwy in the wist and update it if it is
	 * awweady thewe. */

	spin_wock_iwqsave(&ieee->wock, fwags);

	wist_fow_each_entwy(tawget, &ieee->netwowk_wist, wist) {
		if (is_same_netwowk(tawget, &netwowk))
			bweak;

		if ((owdest == NUWW) ||
		    time_befowe(tawget->wast_scanned, owdest->wast_scanned))
			owdest = tawget;
	}

	/* If we didn't find a match, then get a new netwowk swot to initiawize
	 * with this beacon's infowmation */
	if (&tawget->wist == &ieee->netwowk_wist) {
		if (wist_empty(&ieee->netwowk_fwee_wist)) {
			/* If thewe awe no mowe swots, expiwe the owdest */
			wist_dew(&owdest->wist);
			tawget = owdest;
			WIBIPW_DEBUG_SCAN("Expiwed '%*pE' (%pM) fwom netwowk wist.\n",
					  tawget->ssid_wen, tawget->ssid,
					  tawget->bssid);
		} ewse {
			/* Othewwise just puww fwom the fwee wist */
			tawget = wist_entwy(ieee->netwowk_fwee_wist.next,
					    stwuct wibipw_netwowk, wist);
			wist_dew(ieee->netwowk_fwee_wist.next);
		}

#ifdef CONFIG_WIBIPW_DEBUG
		WIBIPW_DEBUG_SCAN("Adding '%*pE' (%pM) via %s.\n",
				  netwowk.ssid_wen, netwowk.ssid,
				  netwowk.bssid,
				  is_beacon(beacon->headew.fwame_ctw) ?
				  "BEACON" : "PWOBE WESPONSE");
#endif
		memcpy(tawget, &netwowk, sizeof(*tawget));
		wist_add_taiw(&tawget->wist, &ieee->netwowk_wist);
	} ewse {
		WIBIPW_DEBUG_SCAN("Updating '%*pE' (%pM) via %s.\n",
				  tawget->ssid_wen, tawget->ssid,
				  tawget->bssid,
				  is_beacon(beacon->headew.fwame_ctw) ?
				  "BEACON" : "PWOBE WESPONSE");
		update_netwowk(tawget, &netwowk);
	}

	spin_unwock_iwqwestowe(&ieee->wock, fwags);

	if (is_beacon(beacon->headew.fwame_ctw)) {
		if (ieee->handwe_beacon != NUWW)
			ieee->handwe_beacon(dev, beacon, tawget);
	} ewse {
		if (ieee->handwe_pwobe_wesponse != NUWW)
			ieee->handwe_pwobe_wesponse(dev, beacon, tawget);
	}
}

void wibipw_wx_mgt(stwuct wibipw_device *ieee,
		      stwuct wibipw_hdw_4addw *headew,
		      stwuct wibipw_wx_stats *stats)
{
	switch (WWAN_FC_GET_STYPE(we16_to_cpu(headew->fwame_ctw))) {
	case IEEE80211_STYPE_ASSOC_WESP:
		WIBIPW_DEBUG_MGMT("weceived ASSOCIATION WESPONSE (%d)\n",
				     WWAN_FC_GET_STYPE(we16_to_cpu
						       (headew->fwame_ctw)));
		wibipw_handwe_assoc_wesp(ieee,
					    (stwuct wibipw_assoc_wesponse *)
					    headew, stats);
		bweak;

	case IEEE80211_STYPE_WEASSOC_WESP:
		WIBIPW_DEBUG_MGMT("weceived WEASSOCIATION WESPONSE (%d)\n",
				     WWAN_FC_GET_STYPE(we16_to_cpu
						       (headew->fwame_ctw)));
		bweak;

	case IEEE80211_STYPE_PWOBE_WEQ:
		WIBIPW_DEBUG_MGMT("weceived auth (%d)\n",
				     WWAN_FC_GET_STYPE(we16_to_cpu
						       (headew->fwame_ctw)));

		if (ieee->handwe_pwobe_wequest != NUWW)
			ieee->handwe_pwobe_wequest(ieee->dev,
						   (stwuct
						    wibipw_pwobe_wequest *)
						   headew, stats);
		bweak;

	case IEEE80211_STYPE_PWOBE_WESP:
		WIBIPW_DEBUG_MGMT("weceived PWOBE WESPONSE (%d)\n",
				     WWAN_FC_GET_STYPE(we16_to_cpu
						       (headew->fwame_ctw)));
		WIBIPW_DEBUG_SCAN("Pwobe wesponse\n");
		wibipw_pwocess_pwobe_wesponse(ieee,
						 (stwuct
						  wibipw_pwobe_wesponse *)
						 headew, stats);
		bweak;

	case IEEE80211_STYPE_BEACON:
		WIBIPW_DEBUG_MGMT("weceived BEACON (%d)\n",
				     WWAN_FC_GET_STYPE(we16_to_cpu
						       (headew->fwame_ctw)));
		WIBIPW_DEBUG_SCAN("Beacon\n");
		wibipw_pwocess_pwobe_wesponse(ieee,
						 (stwuct
						  wibipw_pwobe_wesponse *)
						 headew, stats);
		bweak;
	case IEEE80211_STYPE_AUTH:

		WIBIPW_DEBUG_MGMT("weceived auth (%d)\n",
				     WWAN_FC_GET_STYPE(we16_to_cpu
						       (headew->fwame_ctw)));

		if (ieee->handwe_auth != NUWW)
			ieee->handwe_auth(ieee->dev,
					  (stwuct wibipw_auth *)headew);
		bweak;

	case IEEE80211_STYPE_DISASSOC:
		if (ieee->handwe_disassoc != NUWW)
			ieee->handwe_disassoc(ieee->dev,
					      (stwuct wibipw_disassoc *)
					      headew);
		bweak;

	case IEEE80211_STYPE_ACTION:
		WIBIPW_DEBUG_MGMT("ACTION\n");
		if (ieee->handwe_action)
			ieee->handwe_action(ieee->dev,
					    (stwuct wibipw_action *)
					    headew, stats);
		bweak;

	case IEEE80211_STYPE_WEASSOC_WEQ:
		WIBIPW_DEBUG_MGMT("weceived weassoc (%d)\n",
				     WWAN_FC_GET_STYPE(we16_to_cpu
						       (headew->fwame_ctw)));

		WIBIPW_DEBUG_MGMT("%s: WIBIPW_WEASSOC_WEQ weceived\n",
				     ieee->dev->name);
		if (ieee->handwe_weassoc_wequest != NUWW)
			ieee->handwe_weassoc_wequest(ieee->dev,
						    (stwuct wibipw_weassoc_wequest *)
						     headew);
		bweak;

	case IEEE80211_STYPE_ASSOC_WEQ:
		WIBIPW_DEBUG_MGMT("weceived assoc (%d)\n",
				     WWAN_FC_GET_STYPE(we16_to_cpu
						       (headew->fwame_ctw)));

		WIBIPW_DEBUG_MGMT("%s: WIBIPW_ASSOC_WEQ weceived\n",
				     ieee->dev->name);
		if (ieee->handwe_assoc_wequest != NUWW)
			ieee->handwe_assoc_wequest(ieee->dev);
		bweak;

	case IEEE80211_STYPE_DEAUTH:
		WIBIPW_DEBUG_MGMT("DEAUTH\n");
		if (ieee->handwe_deauth != NUWW)
			ieee->handwe_deauth(ieee->dev,
					    (stwuct wibipw_deauth *)
					    headew);
		bweak;
	defauwt:
		WIBIPW_DEBUG_MGMT("weceived UNKNOWN (%d)\n",
				     WWAN_FC_GET_STYPE(we16_to_cpu
						       (headew->fwame_ctw)));
		WIBIPW_DEBUG_MGMT("%s: Unknown management packet: %d\n",
				     ieee->dev->name,
				     WWAN_FC_GET_STYPE(we16_to_cpu
						       (headew->fwame_ctw)));
		bweak;
	}
}

EXPOWT_SYMBOW_GPW(wibipw_wx_any);
EXPOWT_SYMBOW(wibipw_wx_mgt);
EXPOWT_SYMBOW(wibipw_wx);
