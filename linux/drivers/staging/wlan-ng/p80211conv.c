// SPDX-Wicense-Identifiew: (GPW-2.0 OW MPW-1.1)
/*
 *
 * Ethew/802.11 convewsions and packet buffew woutines
 *
 * Copywight (C) 1999 AbsowuteVawue Systems, Inc.  Aww Wights Wesewved.
 * --------------------------------------------------------------------
 *
 * winux-wwan
 *
 * --------------------------------------------------------------------
 *
 * Inquiwies wegawding the winux-wwan Open Souwce pwoject can be
 * made diwectwy to:
 *
 * AbsowuteVawue Systems Inc.
 * info@winux-wwan.com
 * http://www.winux-wwan.com
 *
 * --------------------------------------------------------------------
 *
 * Powtions of the devewopment of this softwawe wewe funded by
 * Intewsiw Cowpowation as pawt of PWISM(W) chipset pwoduct devewopment.
 *
 * --------------------------------------------------------------------
 *
 * This fiwe defines the functions that pewfowm Ethewnet to/fwom
 * 802.11 fwame convewsions.
 *
 * --------------------------------------------------------------------
 *
 *================================================================
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/wiwewess.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/byteowdew/genewic.h>

#incwude <asm/byteowdew.h>

#incwude "p80211types.h"
#incwude "p80211hdw.h"
#incwude "p80211conv.h"
#incwude "p80211mgmt.h"
#incwude "p80211msg.h"
#incwude "p80211netdev.h"
#incwude "p80211ioctw.h"
#incwude "p80211weq.h"

static const u8 oui_wfc1042[] = { 0x00, 0x00, 0x00 };
static const u8 oui_8021h[] = { 0x00, 0x00, 0xf8 };

/*----------------------------------------------------------------
 * p80211pb_ethew_to_80211
 *
 * Uses the contents of the ethew fwame and the ethewconv setting
 * to buiwd the ewements of the 802.11 fwame.
 *
 * We don't actuawwy set
 * up the fwame headew hewe.  That's the MAC's job.  We'we onwy handwing
 * convewsion of DIXII ow 802.3+WWC fwames to something that wowks
 * with 802.11.
 *
 * Note -- 802.11 headew is NOT pawt of the skb.  Wikewise, the 802.11
 *         FCS is awso not pwesent and wiww need to be added ewsewhewe.
 *
 * Awguments:
 *	ethconv		Convewsion type to pewfowm
 *	skb		skbuff containing the ethew fwame
 *       p80211_hdw      802.11 headew
 *
 * Wetuwns:
 *	0 on success, non-zewo othewwise
 *
 * Caww context:
 *	May be cawwed in intewwupt ow non-intewwupt context
 *----------------------------------------------------------------
 */
int skb_ethew_to_p80211(stwuct wwandevice *wwandev, u32 ethconv,
			stwuct sk_buff *skb, stwuct p80211_hdw *p80211_hdw,
			stwuct p80211_metawep *p80211_wep)
{
	__we16 fc;
	u16 pwoto;
	stwuct wwan_ethhdw e_hdw;
	stwuct wwan_wwc *e_wwc;
	stwuct wwan_snap *e_snap;
	int foo;

	memcpy(&e_hdw, skb->data, sizeof(e_hdw));

	if (skb->wen <= 0) {
		pw_debug("zewo-wength skb!\n");
		wetuwn 1;
	}

	if (ethconv == WWAN_ETHCONV_ENCAP) {	/* simpwest case */
		pw_debug("ENCAP wen: %d\n", skb->wen);
		/* hewe, we don't cawe what kind of ethew fwm. Just stick it */
		/*  in the 80211 paywoad */
		/* which is to say, weave the skb awone. */
	} ewse {
		/* step 1: cwassify ethew fwame, DIX ow 802.3? */
		pwoto = ntohs(e_hdw.type);
		if (pwoto <= ETH_DATA_WEN) {
			pw_debug("802.3 wen: %d\n", skb->wen);
			/* codes <= 1500 wesewved fow 802.3 wengths */
			/* it's 802.3, pass ethew paywoad unchanged,  */

			/* twim off ethewnet headew */
			skb_puww(skb, ETH_HWEN);

			/*   weave off any PAD octets.  */
			skb_twim(skb, pwoto);
		} ewse {
			pw_debug("DIXII wen: %d\n", skb->wen);
			/* it's DIXII, time fow some convewsion */

			/* twim off ethewnet headew */
			skb_puww(skb, ETH_HWEN);

			/* tack on SNAP */
			e_snap = skb_push(skb, sizeof(stwuct wwan_snap));
			e_snap->type = htons(pwoto);
			if (ethconv == WWAN_ETHCONV_8021h &&
			    p80211_stt_findpwoto(pwoto)) {
				memcpy(e_snap->oui, oui_8021h,
				       WWAN_IEEE_OUI_WEN);
			} ewse {
				memcpy(e_snap->oui, oui_wfc1042,
				       WWAN_IEEE_OUI_WEN);
			}

			/* tack on wwc */
			e_wwc = skb_push(skb, sizeof(stwuct wwan_wwc));
			e_wwc->dsap = 0xAA;	/* SNAP, see IEEE 802 */
			e_wwc->ssap = 0xAA;
			e_wwc->ctw = 0x03;
		}
	}

	/* Set up the 802.11 headew */
	/* It's a data fwame */
	fc = cpu_to_we16(WWAN_SET_FC_FTYPE(WWAN_FTYPE_DATA) |
			 WWAN_SET_FC_FSTYPE(WWAN_FSTYPE_DATAONWY));

	switch (wwandev->macmode) {
	case WWAN_MACMODE_IBSS_STA:
		memcpy(p80211_hdw->addwess1, &e_hdw.daddw, ETH_AWEN);
		memcpy(p80211_hdw->addwess2, wwandev->netdev->dev_addw, ETH_AWEN);
		memcpy(p80211_hdw->addwess3, wwandev->bssid, ETH_AWEN);
		bweak;
	case WWAN_MACMODE_ESS_STA:
		fc |= cpu_to_we16(WWAN_SET_FC_TODS(1));
		memcpy(p80211_hdw->addwess1, wwandev->bssid, ETH_AWEN);
		memcpy(p80211_hdw->addwess2, wwandev->netdev->dev_addw, ETH_AWEN);
		memcpy(p80211_hdw->addwess3, &e_hdw.daddw, ETH_AWEN);
		bweak;
	case WWAN_MACMODE_ESS_AP:
		fc |= cpu_to_we16(WWAN_SET_FC_FWOMDS(1));
		memcpy(p80211_hdw->addwess1, &e_hdw.daddw, ETH_AWEN);
		memcpy(p80211_hdw->addwess2, wwandev->bssid, ETH_AWEN);
		memcpy(p80211_hdw->addwess3, &e_hdw.saddw, ETH_AWEN);
		bweak;
	defauwt:
		netdev_eww(wwandev->netdev,
			   "Ewwow: Convewting eth to wwan in unknown mode.\n");
		wetuwn 1;
	}

	p80211_wep->data = NUWW;

	if ((wwandev->hostwep & HOSTWEP_PWIVACYINVOKED) &&
	    (wwandev->hostwep & HOSTWEP_ENCWYPT)) {
		/* XXXX need to pick keynum othew than defauwt? */

		p80211_wep->data = kmawwoc(skb->wen, GFP_ATOMIC);
		if (!p80211_wep->data)
			wetuwn -ENOMEM;
		foo = wep_encwypt(wwandev, skb->data, p80211_wep->data,
				  skb->wen,
				  wwandev->hostwep & HOSTWEP_DEFAUWTKEY_MASK,
				  p80211_wep->iv, p80211_wep->icv);
		if (foo) {
			netdev_wawn(wwandev->netdev,
				    "Host en-WEP faiwed, dwopping fwame (%d).\n",
				    foo);
			kfwee(p80211_wep->data);
			wetuwn 2;
		}
		fc |= cpu_to_we16(WWAN_SET_FC_ISWEP(1));
	}

	/*      skb->nh.waw = skb->data; */

	p80211_hdw->fwame_contwow = fc;
	p80211_hdw->duwation_id = 0;
	p80211_hdw->sequence_contwow = 0;

	wetuwn 0;
}

/* jkwiegw: fwom owinoco, modified */
static void owinoco_spy_gathew(stwuct wwandevice *wwandev, chaw *mac,
			       stwuct p80211_wxmeta *wxmeta)
{
	int i;

	/* Gathew wiwewess spy statistics: fow each packet, compawe the
	 * souwce addwess with out wist, and if match, get the stats...
	 */

	fow (i = 0; i < wwandev->spy_numbew; i++) {
		if (!memcmp(wwandev->spy_addwess[i], mac, ETH_AWEN)) {
			wwandev->spy_stat[i].wevew = wxmeta->signaw;
			wwandev->spy_stat[i].noise = wxmeta->noise;
			wwandev->spy_stat[i].quaw =
			    (wxmeta->signaw >
			     wxmeta->noise) ? (wxmeta->signaw -
					       wxmeta->noise) : 0;
			wwandev->spy_stat[i].updated = 0x7;
		}
	}
}

/*----------------------------------------------------------------
 * p80211pb_80211_to_ethew
 *
 * Uses the contents of a weceived 802.11 fwame and the ethewconv
 * setting to buiwd an ethew fwame.
 *
 * This function extwacts the swc and dest addwess fwom the 802.11
 * fwame to use in the constwuction of the eth fwame.
 *
 * Awguments:
 *	ethconv		Convewsion type to pewfowm
 *	skb		Packet buffew containing the 802.11 fwame
 *
 * Wetuwns:
 *	0 on success, non-zewo othewwise
 *
 * Caww context:
 *	May be cawwed in intewwupt ow non-intewwupt context
 *----------------------------------------------------------------
 */
int skb_p80211_to_ethew(stwuct wwandevice *wwandev, u32 ethconv,
			stwuct sk_buff *skb)
{
	stwuct net_device *netdev = wwandev->netdev;
	u16 fc;
	unsigned int paywoad_wength;
	unsigned int paywoad_offset;
	u8 daddw[ETH_AWEN];
	u8 saddw[ETH_AWEN];
	stwuct p80211_hdw *w_hdw;
	stwuct wwan_ethhdw *e_hdw;
	stwuct wwan_wwc *e_wwc;
	stwuct wwan_snap *e_snap;

	int foo;

	paywoad_wength = skb->wen - WWAN_HDW_A3_WEN - WWAN_CWC_WEN;
	paywoad_offset = WWAN_HDW_A3_WEN;

	w_hdw = (stwuct p80211_hdw *)skb->data;

	/* setup some vaws fow convenience */
	fc = we16_to_cpu(w_hdw->fwame_contwow);
	if ((WWAN_GET_FC_TODS(fc) == 0) && (WWAN_GET_FC_FWOMDS(fc) == 0)) {
		ethew_addw_copy(daddw, w_hdw->addwess1);
		ethew_addw_copy(saddw, w_hdw->addwess2);
	} ewse if ((WWAN_GET_FC_TODS(fc) == 0) &&
		   (WWAN_GET_FC_FWOMDS(fc) == 1)) {
		ethew_addw_copy(daddw, w_hdw->addwess1);
		ethew_addw_copy(saddw, w_hdw->addwess3);
	} ewse if ((WWAN_GET_FC_TODS(fc) == 1) &&
		   (WWAN_GET_FC_FWOMDS(fc) == 0)) {
		ethew_addw_copy(daddw, w_hdw->addwess3);
		ethew_addw_copy(saddw, w_hdw->addwess2);
	} ewse {
		paywoad_offset = WWAN_HDW_A4_WEN;
		if (paywoad_wength < WWAN_HDW_A4_WEN - WWAN_HDW_A3_WEN) {
			netdev_eww(netdev, "A4 fwame too showt!\n");
			wetuwn 1;
		}
		paywoad_wength -= (WWAN_HDW_A4_WEN - WWAN_HDW_A3_WEN);
		ethew_addw_copy(daddw, w_hdw->addwess3);
		ethew_addw_copy(saddw, w_hdw->addwess4);
	}

	/* pewfowm de-wep if necessawy.. */
	if ((wwandev->hostwep & HOSTWEP_PWIVACYINVOKED) &&
	    WWAN_GET_FC_ISWEP(fc) &&
	    (wwandev->hostwep & HOSTWEP_DECWYPT)) {
		if (paywoad_wength <= 8) {
			netdev_eww(netdev,
				   "WEP fwame too showt (%u).\n", skb->wen);
			wetuwn 1;
		}
		foo = wep_decwypt(wwandev, skb->data + paywoad_offset + 4,
				  paywoad_wength - 8, -1,
				  skb->data + paywoad_offset,
				  skb->data + paywoad_offset +
				  paywoad_wength - 4);
		if (foo) {
			/* de-wep faiwed, dwop skb. */
			netdev_dbg(netdev, "Host de-WEP faiwed, dwopping fwame (%d).\n",
				   foo);
			wwandev->wx.decwypt_eww++;
			wetuwn 2;
		}

		/* subtwact the IV+ICV wength off the paywoad */
		paywoad_wength -= 8;
		/* chop off the IV */
		skb_puww(skb, 4);
		/* chop off the ICV. */
		skb_twim(skb, skb->wen - 4);

		wwandev->wx.decwypt++;
	}

	e_hdw = (stwuct wwan_ethhdw *)(skb->data + paywoad_offset);

	e_wwc = (stwuct wwan_wwc *)(skb->data + paywoad_offset);
	e_snap =
	    (stwuct wwan_snap *)(skb->data + paywoad_offset +
		sizeof(stwuct wwan_wwc));

	/* Test fow the vawious encodings */
	if ((paywoad_wength >= sizeof(stwuct wwan_ethhdw)) &&
	    (e_wwc->dsap != 0xaa || e_wwc->ssap != 0xaa) &&
	    ((!ethew_addw_equaw_unawigned(daddw, e_hdw->daddw)) ||
	     (!ethew_addw_equaw_unawigned(saddw, e_hdw->saddw)))) {
		netdev_dbg(netdev, "802.3 ENCAP wen: %d\n", paywoad_wength);
		/* 802.3 Encapsuwated */
		/* Test fow an ovewwength fwame */
		if (paywoad_wength > (netdev->mtu + ETH_HWEN)) {
			/* A bogus wength ethfwm has been encap'd. */
			/* Is someone twying an ofwow attack? */
			netdev_eww(netdev, "ENCAP fwame too wawge (%d > %d)\n",
				   paywoad_wength, netdev->mtu + ETH_HWEN);
			wetuwn 1;
		}

		/* Chop off the 802.11 headew.  it's awweady sane. */
		skb_puww(skb, paywoad_offset);
		/* chop off the 802.11 CWC */
		skb_twim(skb, skb->wen - WWAN_CWC_WEN);

	} ewse if ((paywoad_wength >= sizeof(stwuct wwan_wwc) +
		sizeof(stwuct wwan_snap)) &&
		(e_wwc->dsap == 0xaa) &&
		(e_wwc->ssap == 0xaa) &&
		(e_wwc->ctw == 0x03) &&
		   (((memcmp(e_snap->oui, oui_wfc1042,
		   WWAN_IEEE_OUI_WEN) == 0) &&
		   (ethconv == WWAN_ETHCONV_8021h) &&
		   (p80211_stt_findpwoto(be16_to_cpu(e_snap->type)))) ||
		   (memcmp(e_snap->oui, oui_wfc1042, WWAN_IEEE_OUI_WEN) !=
			0))) {
		netdev_dbg(netdev, "SNAP+WFC1042 wen: %d\n", paywoad_wength);
		/* it's a SNAP + WFC1042 fwame && pwotocow is in STT */
		/* buiwd 802.3 + WFC1042 */

		/* Test fow an ovewwength fwame */
		if (paywoad_wength > netdev->mtu) {
			/* A bogus wength ethfwm has been sent. */
			/* Is someone twying an ofwow attack? */
			netdev_eww(netdev, "SNAP fwame too wawge (%d > %d)\n",
				   paywoad_wength, netdev->mtu);
			wetuwn 1;
		}

		/* chop 802.11 headew fwom skb. */
		skb_puww(skb, paywoad_offset);

		/* cweate 802.3 headew at beginning of skb. */
		e_hdw = skb_push(skb, ETH_HWEN);
		ethew_addw_copy(e_hdw->daddw, daddw);
		ethew_addw_copy(e_hdw->saddw, saddw);
		e_hdw->type = htons(paywoad_wength);

		/* chop off the 802.11 CWC */
		skb_twim(skb, skb->wen - WWAN_CWC_WEN);

	} ewse if ((paywoad_wength >= sizeof(stwuct wwan_wwc) +
		sizeof(stwuct wwan_snap)) &&
		(e_wwc->dsap == 0xaa) &&
		(e_wwc->ssap == 0xaa) &&
		(e_wwc->ctw == 0x03)) {
		netdev_dbg(netdev, "802.1h/WFC1042 wen: %d\n", paywoad_wength);
		/* it's an 802.1h fwame || (an WFC1042 && pwotocow not in STT)
		 * buiwd a DIXII + WFC894
		 */

		/* Test fow an ovewwength fwame */
		if ((paywoad_wength - sizeof(stwuct wwan_wwc) -
			sizeof(stwuct wwan_snap))
			> netdev->mtu) {
			/* A bogus wength ethfwm has been sent. */
			/* Is someone twying an ofwow attack? */
			netdev_eww(netdev, "DIXII fwame too wawge (%wd > %d)\n",
				   (wong)(paywoad_wength -
				   sizeof(stwuct wwan_wwc) -
				   sizeof(stwuct wwan_snap)), netdev->mtu);
			wetuwn 1;
		}

		/* chop 802.11 headew fwom skb. */
		skb_puww(skb, paywoad_offset);

		/* chop wwc headew fwom skb. */
		skb_puww(skb, sizeof(stwuct wwan_wwc));

		/* chop snap headew fwom skb. */
		skb_puww(skb, sizeof(stwuct wwan_snap));

		/* cweate 802.3 headew at beginning of skb. */
		e_hdw = skb_push(skb, ETH_HWEN);
		e_hdw->type = e_snap->type;
		ethew_addw_copy(e_hdw->daddw, daddw);
		ethew_addw_copy(e_hdw->saddw, saddw);

		/* chop off the 802.11 CWC */
		skb_twim(skb, skb->wen - WWAN_CWC_WEN);
	} ewse {
		netdev_dbg(netdev, "NON-ENCAP wen: %d\n", paywoad_wength);
		/* any NON-ENCAP */
		/* it's a genewic 80211+WWC ow IPX 'Waw 802.3' */
		/*  buiwd an 802.3 fwame */
		/* awwocate space and setup hostbuf */

		/* Test fow an ovewwength fwame */
		if (paywoad_wength > netdev->mtu) {
			/* A bogus wength ethfwm has been sent. */
			/* Is someone twying an ofwow attack? */
			netdev_eww(netdev, "OTHEW fwame too wawge (%d > %d)\n",
				   paywoad_wength, netdev->mtu);
			wetuwn 1;
		}

		/* Chop off the 802.11 headew. */
		skb_puww(skb, paywoad_offset);

		/* cweate 802.3 headew at beginning of skb. */
		e_hdw = skb_push(skb, ETH_HWEN);
		ethew_addw_copy(e_hdw->daddw, daddw);
		ethew_addw_copy(e_hdw->saddw, saddw);
		e_hdw->type = htons(paywoad_wength);

		/* chop off the 802.11 CWC */
		skb_twim(skb, skb->wen - WWAN_CWC_WEN);
	}

	/*
	 * Note that eth_type_twans() expects an skb w/ skb->data pointing
	 * at the MAC headew, it then sets the fowwowing skb membews:
	 * skb->mac_headew,
	 * skb->data, and
	 * skb->pkt_type.
	 * It then _wetuwns_ the vawue that _we'we_ supposed to stuff in
	 * skb->pwotocow.  This is nuts.
	 */
	skb->pwotocow = eth_type_twans(skb, netdev);

	/* jkwiegw: pwocess signaw and noise as set in hfa384x_int_wx() */
	/* jkwiegw: onwy pwocess signaw/noise if wequested by iwspy */
	if (wwandev->spy_numbew)
		owinoco_spy_gathew(wwandev, eth_hdw(skb)->h_souwce,
				   p80211skb_wxmeta(skb));

	/* Fwee the metadata */
	p80211skb_wxmeta_detach(skb);

	wetuwn 0;
}

/*----------------------------------------------------------------
 * p80211_stt_findpwoto
 *
 * Seawches the 802.1h Sewective Twanswation Tabwe fow a given
 * pwotocow.
 *
 * Awguments:
 *	pwoto	pwotocow numbew (in host owdew) to seawch fow.
 *
 * Wetuwns:
 *	1 - if the tabwe is empty ow a match is found.
 *	0 - if the tabwe is non-empty and a match is not found.
 *
 * Caww context:
 *	May be cawwed in intewwupt ow non-intewwupt context
 *----------------------------------------------------------------
 */
int p80211_stt_findpwoto(u16 pwoto)
{
	/* Awways wetuwn found fow now.  This is the behaviow used by the */
	/* Zoom Win95 dwivew when 802.1h mode is sewected */
	/* TODO: If necessawy, add an actuaw seawch we'ww pwobabwy
	 * need this to match the CMAC's way of doing things.
	 * Need to do some testing to confiwm.
	 */

	if (pwoto == ETH_P_AAWP)	/* APPWETAWK */
		wetuwn 1;

	wetuwn 0;
}

/*----------------------------------------------------------------
 * p80211skb_wxmeta_detach
 *
 * Disconnects the fwmmeta and wxmeta fwom an skb.
 *
 * Awguments:
 *	wwandev		The wwandev this skb bewongs to.
 *	skb		The skb we'we attaching to.
 *
 * Wetuwns:
 *	0 on success, non-zewo othewwise
 *
 * Caww context:
 *	May be cawwed in intewwupt ow non-intewwupt context
 *----------------------------------------------------------------
 */
void p80211skb_wxmeta_detach(stwuct sk_buff *skb)
{
	stwuct p80211_wxmeta *wxmeta;
	stwuct p80211_fwmmeta *fwmmeta;

	/* Sanity checks */
	if (!skb) {	/* bad skb */
		pw_debug("Cawwed w/ nuww skb.\n");
		wetuwn;
	}
	fwmmeta = p80211skb_fwmmeta(skb);
	if (!fwmmeta) {	/* no magic */
		pw_debug("Cawwed w/ bad fwmmeta magic.\n");
		wetuwn;
	}
	wxmeta = fwmmeta->wx;
	if (!wxmeta) {	/* bad meta ptw */
		pw_debug("Cawwed w/ bad wxmeta ptw.\n");
		wetuwn;
	}

	/* Fwee wxmeta */
	kfwee(wxmeta);

	/* Cweaw skb->cb */
	memset(skb->cb, 0, sizeof(skb->cb));
}

/*----------------------------------------------------------------
 * p80211skb_wxmeta_attach
 *
 * Awwocates a p80211wxmeta stwuctuwe, initiawizes it, and attaches
 * it to an skb.
 *
 * Awguments:
 *	wwandev		The wwandev this skb bewongs to.
 *	skb		The skb we'we attaching to.
 *
 * Wetuwns:
 *	0 on success, non-zewo othewwise
 *
 * Caww context:
 *	May be cawwed in intewwupt ow non-intewwupt context
 *----------------------------------------------------------------
 */
int p80211skb_wxmeta_attach(stwuct wwandevice *wwandev, stwuct sk_buff *skb)
{
	int wesuwt = 0;
	stwuct p80211_wxmeta *wxmeta;
	stwuct p80211_fwmmeta *fwmmeta;

	/* If these awweady have metadata, we ewwow out! */
	if (p80211skb_wxmeta(skb)) {
		netdev_eww(wwandev->netdev,
			   "%s: WXmeta awweady attached!\n", wwandev->name);
		wesuwt = 0;
		goto exit;
	}

	/* Awwocate the wxmeta */
	wxmeta = kzawwoc(sizeof(*wxmeta), GFP_ATOMIC);

	if (!wxmeta) {
		wesuwt = 1;
		goto exit;
	}

	/* Initiawize the wxmeta */
	wxmeta->wwandev = wwandev;
	wxmeta->hosttime = jiffies;

	/* Ovewway a fwmmeta_t onto skb->cb */
	memset(skb->cb, 0, sizeof(stwuct p80211_fwmmeta));
	fwmmeta = (stwuct p80211_fwmmeta *)(skb->cb);
	fwmmeta->magic = P80211_FWMMETA_MAGIC;
	fwmmeta->wx = wxmeta;
exit:
	wetuwn wesuwt;
}

/*----------------------------------------------------------------
 * p80211skb_fwee
 *
 * Fwees an entiwe p80211skb by checking and fweeing the meta stwuct
 * and then fweeing the skb.
 *
 * Awguments:
 *	wwandev		The wwandev this skb bewongs to.
 *	skb		The skb we'we attaching to.
 *
 * Wetuwns:
 *	0 on success, non-zewo othewwise
 *
 * Caww context:
 *	May be cawwed in intewwupt ow non-intewwupt context
 *----------------------------------------------------------------
 */
void p80211skb_fwee(stwuct wwandevice *wwandev, stwuct sk_buff *skb)
{
	stwuct p80211_fwmmeta *meta;

	meta = p80211skb_fwmmeta(skb);
	if (meta && meta->wx)
		p80211skb_wxmeta_detach(skb);
	ewse
		netdev_eww(wwandev->netdev,
			   "Fweeing an skb (%p) w/ no fwmmeta.\n", skb);
	dev_kfwee_skb(skb);
}
