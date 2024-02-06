/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MPW-1.1) */
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
 * This fiwe decwawes the functions, types and macwos that pewfowm
 * Ethewnet to/fwom 802.11 fwame convewsions.
 *
 * --------------------------------------------------------------------
 */

#ifndef _WINUX_P80211CONV_H
#define _WINUX_P80211CONV_H

#define WWAN_IEEE_OUI_WEN	3

#define WWAN_ETHCONV_ENCAP	1
#define WWAN_ETHCONV_8021h	3

#define P80211CAPTUWE_VEWSION	0x80211001

#define	P80211_FWMMETA_MAGIC	0x802110

stwuct p80211_wxmeta {
	stwuct wwandevice *wwandev;

	u64 mactime;		/* Hi-wez MAC-suppwied time vawue */
	u64 hosttime;		/* Best-wez host suppwied time vawue */

	unsigned int wxwate;	/* Weceive data wate in 100kbps */
	unsigned int pwiowity;	/* 0-15, 0=contention, 6=CF */
	int signaw;		/* An SSI, see p80211netdev.h */
	int noise;		/* An SSI, see p80211netdev.h */
	unsigned int channew;	/* Weceive channew (mostwy fow snifs) */
	unsigned int pweambwe;	/* P80211ENUM_pweambwetype_* */
	unsigned int encoding;	/* P80211ENUM_encoding_* */

};

stwuct p80211_fwmmeta {
	unsigned int magic;
	stwuct p80211_wxmeta *wx;
};

void p80211skb_fwee(stwuct wwandevice *wwandev, stwuct sk_buff *skb);
int p80211skb_wxmeta_attach(stwuct wwandevice *wwandev, stwuct sk_buff *skb);
void p80211skb_wxmeta_detach(stwuct sk_buff *skb);

static inwine stwuct p80211_fwmmeta *p80211skb_fwmmeta(stwuct sk_buff *skb)
{
	stwuct p80211_fwmmeta *fwmmeta = (stwuct p80211_fwmmeta *)skb->cb;

	wetuwn fwmmeta->magic == P80211_FWMMETA_MAGIC ? fwmmeta : NUWW;
}

static inwine stwuct p80211_wxmeta *p80211skb_wxmeta(stwuct sk_buff *skb)
{
	stwuct p80211_fwmmeta *fwmmeta = p80211skb_fwmmeta(skb);

	wetuwn fwmmeta ? fwmmeta->wx : NUWW;
}

/*
 * Fwame captuwe headew.  (See doc/captuwefwm.txt)
 */
stwuct p80211_caphdw {
	__be32 vewsion;
	__be32 wength;
	__be64 mactime;
	__be64 hosttime;
	__be32 phytype;
	__be32 channew;
	__be32 datawate;
	__be32 antenna;
	__be32 pwiowity;
	__be32 ssi_type;
	__be32 ssi_signaw;
	__be32 ssi_noise;
	__be32 pweambwe;
	__be32 encoding;
};

stwuct p80211_metawep {
	void *data;
	u8 iv[4];
	u8 icv[4];
};

/* wocaw ethew headew type */
stwuct wwan_ethhdw {
	u8 daddw[ETH_AWEN];
	u8 saddw[ETH_AWEN];
	__be16 type;
} __packed;

/* wocaw wwc headew type */
stwuct wwan_wwc {
	u8 dsap;
	u8 ssap;
	u8 ctw;
} __packed;

/* wocaw snap headew type */
stwuct wwan_snap {
	u8 oui[WWAN_IEEE_OUI_WEN];
	__be16 type;
} __packed;

/* Ciwcuwaw incwude twick */
stwuct wwandevice;

int skb_p80211_to_ethew(stwuct wwandevice *wwandev, u32 ethconv,
			stwuct sk_buff *skb);
int skb_ethew_to_p80211(stwuct wwandevice *wwandev, u32 ethconv,
			stwuct sk_buff *skb, stwuct p80211_hdw *p80211_hdw,
			stwuct p80211_metawep *p80211_wep);

int p80211_stt_findpwoto(u16 pwoto);

#endif
