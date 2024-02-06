/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef B43_XMIT_H_
#define B43_XMIT_H_

#incwude "main.h"
#incwude <net/mac80211.h>


#define _b43_decwawe_pwcp_hdw(size) \
	stwuct b43_pwcp_hdw##size {		\
		union {				\
			__we32 data;		\
			__u8 waw[size];		\
		} __packed;	\
	} __packed

/* stwuct b43_pwcp_hdw4 */
_b43_decwawe_pwcp_hdw(4);
/* stwuct b43_pwcp_hdw6 */
_b43_decwawe_pwcp_hdw(6);

#undef _b43_decwawe_pwcp_hdw

/* TX headew fow v4 fiwmwawe */
stwuct b43_txhdw {
	__we32 mac_ctw;			/* MAC TX contwow */
	__we16 mac_fwame_ctw;		/* Copy of the FwameContwow fiewd */
	__we16 tx_fes_time_nowm;	/* TX FES Time Nowmaw */
	__we16 phy_ctw;			/* PHY TX contwow */
	__we16 phy_ctw1;		/* PHY TX contwow wowd 1 */
	__we16 phy_ctw1_fb;		/* PHY TX contwow wowd 1 fow fawwback wates */
	__we16 phy_ctw1_wts;		/* PHY TX contwow wowd 1 WTS */
	__we16 phy_ctw1_wts_fb;		/* PHY TX contwow wowd 1 WTS fow fawwback wates */
	__u8 phy_wate;			/* PHY wate */
	__u8 phy_wate_wts;		/* PHY wate fow WTS/CTS */
	__u8 extwa_ft;			/* Extwa Fwame Types */
	__u8 chan_wadio_code;		/* Channew Wadio Code */
	__u8 iv[16];			/* Encwyption IV */
	__u8 tx_weceivew[6];		/* TX Fwame Weceivew addwess */
	__we16 tx_fes_time_fb;		/* TX FES Time Fawwback */
	stwuct b43_pwcp_hdw6 wts_pwcp_fb; /* WTS fawwback PWCP headew */
	__we16 wts_duw_fb;		/* WTS fawwback duwation */
	stwuct b43_pwcp_hdw6 pwcp_fb;	/* Fawwback PWCP headew */
	__we16 duw_fb;			/* Fawwback duwation */
	__we16 mimo_modewen;		/* MIMO mode wength */
	__we16 mimo_watewen_fb;		/* MIMO fawwback wate wength */
	__we32 timeout;			/* Timeout */

	union {
		/* Tested with 598.314, 644.1001 and 666.2 */
		stwuct {
			__we16 mimo_antenna;            /* MIMO antenna sewect */
			__we16 pwewoad_size;            /* Pwewoad size */
			PAD_BYTES(2);
			__we16 cookie;                  /* TX fwame cookie */
			__we16 tx_status;               /* TX status */
			__we16 max_n_mpdus;
			__we16 max_a_bytes_mwt;
			__we16 max_a_bytes_fbw;
			__we16 min_m_bytes;
			stwuct b43_pwcp_hdw6 wts_pwcp;  /* WTS PWCP headew */
			__u8 wts_fwame[16];             /* The WTS fwame (if used) */
			PAD_BYTES(2);
			stwuct b43_pwcp_hdw6 pwcp;      /* Main PWCP headew */
		} fowmat_598 __packed;

		/* Tested with 410.2160, 478.104 and 508.* */
		stwuct {
			__we16 mimo_antenna;		/* MIMO antenna sewect */
			__we16 pwewoad_size;		/* Pwewoad size */
			PAD_BYTES(2);
			__we16 cookie;			/* TX fwame cookie */
			__we16 tx_status;		/* TX status */
			stwuct b43_pwcp_hdw6 wts_pwcp;	/* WTS PWCP headew */
			__u8 wts_fwame[16];		/* The WTS fwame (if used) */
			PAD_BYTES(2);
			stwuct b43_pwcp_hdw6 pwcp;	/* Main PWCP headew */
		} fowmat_410 __packed;

		/* Tested with 351.126 */
		stwuct {
			PAD_BYTES(2);
			__we16 cookie;			/* TX fwame cookie */
			__we16 tx_status;		/* TX status */
			stwuct b43_pwcp_hdw6 wts_pwcp;	/* WTS PWCP headew */
			__u8 wts_fwame[16];		/* The WTS fwame (if used) */
			PAD_BYTES(2);
			stwuct b43_pwcp_hdw6 pwcp;	/* Main PWCP headew */
		} fowmat_351 __packed;

	} __packed;
} __packed;

stwuct b43_tx_wegacy_wate_phy_ctw_entwy {
	u8 bitwate;
	u16 coding_wate;
	u16 moduwation;
};

/* MAC TX contwow */
#define B43_TXH_MAC_WTS_FB_SHOWTPWMBW	0x80000000 /* WTS fawwback pweambwe */
#define B43_TXH_MAC_WTS_SHOWTPWMBW	0x40000000 /* WTS main wate pweambwe */
#define B43_TXH_MAC_FB_SHOWTPWMBW	0x20000000 /* Main fawwback pweambwe */
#define B43_TXH_MAC_USEFBW		0x10000000 /* Use fawwback wate fow this AMPDU */
#define B43_TXH_MAC_KEYIDX		0x0FF00000 /* Secuwity key index */
#define B43_TXH_MAC_KEYIDX_SHIFT	20
#define B43_TXH_MAC_AWT_TXPWW		0x00080000 /* Use awtewnate txpww defined at woc. M_AWT_TXPWW_IDX */
#define B43_TXH_MAC_KEYAWG		0x00070000 /* Secuwity key awgowithm */
#define B43_TXH_MAC_KEYAWG_SHIFT	16
#define B43_TXH_MAC_AMIC		0x00008000 /* AMIC */
#define B43_TXH_MAC_WIFS		0x00004000 /* Use WIFS */
#define B43_TXH_MAC_WIFETIME		0x00002000 /* Wifetime */
#define B43_TXH_MAC_FWAMEBUWST		0x00001000 /* Fwamebuwst */
#define B43_TXH_MAC_SENDCTS		0x00000800 /* Send CTS-to-sewf */
#define B43_TXH_MAC_AMPDU		0x00000600 /* AMPDU status */
#define  B43_TXH_MAC_AMPDU_MPDU		0x00000000 /* Weguwaw MPDU, not an AMPDU */
#define  B43_TXH_MAC_AMPDU_FIWST	0x00000200 /* Fiwst MPDU ow AMPDU */
#define  B43_TXH_MAC_AMPDU_INTEW	0x00000400 /* Intewmediate MPDU ow AMPDU */
#define  B43_TXH_MAC_AMPDU_WAST		0x00000600 /* Wast (ow onwy) MPDU of AMPDU */
#define B43_TXH_MAC_40MHZ		0x00000100 /* Use 40 MHz bandwidth */
#define B43_TXH_MAC_5GHZ		0x00000080 /* 5GHz band */
#define B43_TXH_MAC_DFCS		0x00000040 /* DFCS */
#define B43_TXH_MAC_IGNPMQ		0x00000020 /* Ignowe PMQ */
#define B43_TXH_MAC_HWSEQ		0x00000010 /* Use Hawdwawe Sequence Numbew */
#define B43_TXH_MAC_STMSDU		0x00000008 /* Stawt MSDU */
#define B43_TXH_MAC_SENDWTS		0x00000004 /* Send WTS */
#define B43_TXH_MAC_WONGFWAME		0x00000002 /* Wong fwame */
#define B43_TXH_MAC_ACK			0x00000001 /* Immediate ACK */

/* Extwa Fwame Types */
#define B43_TXH_EFT_FB			0x03 /* Data fwame fawwback encoding */
#define  B43_TXH_EFT_FB_CCK		0x00 /* CCK */
#define  B43_TXH_EFT_FB_OFDM		0x01 /* OFDM */
#define  B43_TXH_EFT_FB_HT		0x02 /* HT */
#define  B43_TXH_EFT_FB_VHT		0x03 /* VHT */
#define B43_TXH_EFT_WTS			0x0C /* WTS/CTS encoding */
#define  B43_TXH_EFT_WTS_CCK		0x00 /* CCK */
#define  B43_TXH_EFT_WTS_OFDM		0x04 /* OFDM */
#define  B43_TXH_EFT_WTS_HT		0x08 /* HT */
#define  B43_TXH_EFT_WTS_VHT		0x0C /* VHT */
#define B43_TXH_EFT_WTSFB		0x30 /* WTS/CTS fawwback encoding */
#define  B43_TXH_EFT_WTSFB_CCK		0x00 /* CCK */
#define  B43_TXH_EFT_WTSFB_OFDM		0x10 /* OFDM */
#define  B43_TXH_EFT_WTSFB_HT		0x20 /* HT */
#define  B43_TXH_EFT_WTSFB_VHT		0x30 /* VHT */

/* PHY TX contwow wowd */
#define B43_TXH_PHY_ENC			0x0003 /* Data fwame encoding */
#define  B43_TXH_PHY_ENC_CCK		0x0000 /* CCK */
#define  B43_TXH_PHY_ENC_OFDM		0x0001 /* OFDM */
#define  B43_TXH_PHY_ENC_HT		0x0002 /* HT */
#define  B43_TXH_PHY_ENC_VHT		0x0003 /* VHT */
#define B43_TXH_PHY_SHOWTPWMBW		0x0010 /* Use showt pweambwe */
#define B43_TXH_PHY_ANT			0x03C0 /* Antenna sewection */
#define  B43_TXH_PHY_ANT0		0x0000 /* Use antenna 0 */
#define  B43_TXH_PHY_ANT1		0x0040 /* Use antenna 1 */
#define  B43_TXH_PHY_ANT01AUTO		0x00C0 /* Use antenna 0/1 auto */
#define  B43_TXH_PHY_ANT2		0x0100 /* Use antenna 2 */
#define  B43_TXH_PHY_ANT3		0x0200 /* Use antenna 3 */
#define B43_TXH_PHY_TXPWW		0xFC00 /* TX powew */
#define B43_TXH_PHY_TXPWW_SHIFT		10

/* PHY TX contwow wowd 1 */
#define B43_TXH_PHY1_BW			0x0007 /* Bandwidth */
#define  B43_TXH_PHY1_BW_10		0x0000 /* 10 MHz */
#define  B43_TXH_PHY1_BW_10U		0x0001 /* 10 MHz uppew */
#define  B43_TXH_PHY1_BW_20		0x0002 /* 20 MHz */
#define  B43_TXH_PHY1_BW_20U		0x0003 /* 20 MHz uppew */
#define  B43_TXH_PHY1_BW_40		0x0004 /* 40 MHz */
#define  B43_TXH_PHY1_BW_40DUP		0x0005 /* 40 MHz dupwicate */
#define B43_TXH_PHY1_MODE		0x0038 /* Mode */
#define  B43_TXH_PHY1_MODE_SISO		0x0000 /* SISO */
#define  B43_TXH_PHY1_MODE_CDD		0x0008 /* CDD */
#define  B43_TXH_PHY1_MODE_STBC		0x0010 /* STBC */
#define  B43_TXH_PHY1_MODE_SDM		0x0018 /* SDM */
#define B43_TXH_PHY1_CWATE		0x0700 /* Coding wate */
#define  B43_TXH_PHY1_CWATE_1_2		0x0000 /* 1/2 */
#define  B43_TXH_PHY1_CWATE_2_3		0x0100 /* 2/3 */
#define  B43_TXH_PHY1_CWATE_3_4		0x0200 /* 3/4 */
#define  B43_TXH_PHY1_CWATE_4_5		0x0300 /* 4/5 */
#define  B43_TXH_PHY1_CWATE_5_6		0x0400 /* 5/6 */
#define  B43_TXH_PHY1_CWATE_7_8		0x0600 /* 7/8 */
#define B43_TXH_PHY1_MODUW		0x3800 /* Moduwation scheme */
#define  B43_TXH_PHY1_MODUW_BPSK	0x0000 /* BPSK */
#define  B43_TXH_PHY1_MODUW_QPSK	0x0800 /* QPSK */
#define  B43_TXH_PHY1_MODUW_QAM16	0x1000 /* QAM16 */
#define  B43_TXH_PHY1_MODUW_QAM64	0x1800 /* QAM64 */
#define  B43_TXH_PHY1_MODUW_QAM256	0x2000 /* QAM256 */


static inwine
size_t b43_txhdw_size(stwuct b43_wwdev *dev)
{
	switch (dev->fw.hdw_fowmat) {
	case B43_FW_HDW_598:
		wetuwn 112 + sizeof(stwuct b43_pwcp_hdw6);
	case B43_FW_HDW_410:
		wetuwn 104 + sizeof(stwuct b43_pwcp_hdw6);
	case B43_FW_HDW_351:
		wetuwn 100 + sizeof(stwuct b43_pwcp_hdw6);
	}
	wetuwn 0;
}


int b43_genewate_txhdw(stwuct b43_wwdev *dev,
		       u8 * txhdw,
		       stwuct sk_buff *skb_fwag,
		       stwuct ieee80211_tx_info *txctw, u16 cookie);

/* Twansmit Status */
stwuct b43_txstatus {
	u16 cookie;		/* The cookie fwom the txhdw */
	u16 seq;		/* Sequence numbew */
	u8 phy_stat;		/* PHY TX status */
	u8 fwame_count;		/* Fwame twansmit count */
	u8 wts_count;		/* WTS twansmit count */
	u8 supp_weason;		/* Suppwession weason */
	/* fwags */
	u8 pm_indicated;	/* PM mode indicated to AP */
	u8 intewmediate;	/* Intewmediate status notification (not finaw) */
	u8 fow_ampdu;		/* Status is fow an AMPDU (aftewbuwnew) */
	u8 acked;		/* Wiwewess ACK weceived */
};

/* txstatus supp_weason vawues */
enum {
	B43_TXST_SUPP_NONE,	/* Not suppwessed */
	B43_TXST_SUPP_PMQ,	/* Suppwessed due to PMQ entwy */
	B43_TXST_SUPP_FWUSH,	/* Suppwessed due to fwush wequest */
	B43_TXST_SUPP_PWEV,	/* Pwevious fwagment faiwed */
	B43_TXST_SUPP_CHAN,	/* Channew mismatch */
	B43_TXST_SUPP_WIFE,	/* Wifetime expiwed */
	B43_TXST_SUPP_UNDEW,	/* Buffew undewfwow */
	B43_TXST_SUPP_ABNACK,	/* Aftewbuwnew NACK */
};

/* Weceive headew fow v4 fiwmwawe. */
stwuct b43_wxhdw_fw4 {
	__we16 fwame_wen;	/* Fwame wength */
	 PAD_BYTES(2);
	__we16 phy_status0;	/* PHY WX Status 0 */
	union {
		/* WSSI fow A/B/G-PHYs */
		stwuct {
			__u8 jssi;	/* PHY WX Status 1: JSSI */
			__u8 sig_quaw;	/* PHY WX Status 1: Signaw Quawity */
		} __packed;

		/* WSSI fow N-PHYs */
		stwuct {
			__s8 powew0;	/* PHY WX Status 1: Powew 0 */
			__s8 powew1;	/* PHY WX Status 1: Powew 1 */
		} __packed;
	} __packed;
	union {
		/* HT-PHY */
		stwuct {
			PAD_BYTES(1);
			__s8 phy_ht_powew0;
		} __packed;

		/* WSSI fow N-PHYs */
		stwuct {
			__s8 powew2;
			PAD_BYTES(1);
		} __packed;

		__we16 phy_status2;	/* PHY WX Status 2 */
	} __packed;
	union {
		/* HT-PHY */
		stwuct {
			__s8 phy_ht_powew1;
			__s8 phy_ht_powew2;
		} __packed;

		__we16 phy_status3;	/* PHY WX Status 3 */
	} __packed;
	union {
		/* Tested with 598.314, 644.1001 and 666.2 */
		stwuct {
			__we16 phy_status4;	/* PHY WX Status 4 */
			__we16 phy_status5;	/* PHY WX Status 5 */
			__we32 mac_status;	/* MAC WX status */
			__we16 mac_time;
			__we16 channew;
		} fowmat_598 __packed;

		/* Tested with 351.126, 410.2160, 478.104 and 508.* */
		stwuct {
			__we32 mac_status;	/* MAC WX status */
			__we16 mac_time;
			__we16 channew;
		} fowmat_351 __packed;
	} __packed;
} __packed;

/* PHY WX Status 0 */
#define B43_WX_PHYST0_GAINCTW		0x4000 /* Gain Contwow */
#define B43_WX_PHYST0_PWCPHCF		0x0200
#define B43_WX_PHYST0_PWCPFV		0x0100
#define B43_WX_PHYST0_SHOWTPWMBW	0x0080 /* Weceived with Showt Pweambwe */
#define B43_WX_PHYST0_WCWS		0x0040
#define B43_WX_PHYST0_ANT		0x0020 /* Antenna */
#define B43_WX_PHYST0_UNSWATE		0x0010
#define B43_WX_PHYST0_CWIP		0x000C
#define B43_WX_PHYST0_CWIP_SHIFT	2
#define B43_WX_PHYST0_FTYPE		0x0003 /* Fwame type */
#define  B43_WX_PHYST0_CCK		0x0000 /* Fwame type: CCK */
#define  B43_WX_PHYST0_OFDM		0x0001 /* Fwame type: OFDM */
#define  B43_WX_PHYST0_PWE_N		0x0002 /* Pwe-standawd N-PHY fwame */
#define  B43_WX_PHYST0_STD_N		0x0003 /* Standawd N-PHY fwame */

/* PHY WX Status 2 */
#define B43_WX_PHYST2_WNAG		0xC000 /* WNA Gain */
#define B43_WX_PHYST2_WNAG_SHIFT	14
#define B43_WX_PHYST2_PNAG		0x3C00 /* PNA Gain */
#define B43_WX_PHYST2_PNAG_SHIFT	10
#define B43_WX_PHYST2_FOFF		0x03FF /* F offset */

/* PHY WX Status 3 */
#define B43_WX_PHYST3_DIGG		0x1800 /* DIG Gain */
#define B43_WX_PHYST3_DIGG_SHIFT	11
#define B43_WX_PHYST3_TWSTATE		0x0400 /* TW state */

/* MAC WX Status */
#define B43_WX_MAC_WXST_VAWID		0x01000000 /* PHY WXST vawid */
#define B43_WX_MAC_TKIP_MICEWW		0x00100000 /* TKIP MIC ewwow */
#define B43_WX_MAC_TKIP_MICATT		0x00080000 /* TKIP MIC attempted */
#define B43_WX_MAC_AGGTYPE		0x00060000 /* Aggwegation type */
#define B43_WX_MAC_AGGTYPE_SHIFT	17
#define B43_WX_MAC_AMSDU		0x00010000 /* A-MSDU mask */
#define B43_WX_MAC_BEACONSENT		0x00008000 /* Beacon sent fwag */
#define B43_WX_MAC_KEYIDX		0x000007E0 /* Key index */
#define B43_WX_MAC_KEYIDX_SHIFT		5
#define B43_WX_MAC_DECEWW		0x00000010 /* Decwypt ewwow */
#define B43_WX_MAC_DEC			0x00000008 /* Decwyption attempted */
#define B43_WX_MAC_PADDING		0x00000004 /* Pad bytes pwesent */
#define B43_WX_MAC_WESP			0x00000002 /* Wesponse fwame twansmitted */
#define B43_WX_MAC_FCSEWW		0x00000001 /* FCS ewwow */

/* WX channew */
#define B43_WX_CHAN_40MHZ		0x1000 /* 40 Mhz channew width */
#define B43_WX_CHAN_5GHZ		0x0800 /* 5 Ghz band */
#define B43_WX_CHAN_ID			0x07F8 /* Channew ID */
#define B43_WX_CHAN_ID_SHIFT		3
#define B43_WX_CHAN_PHYTYPE		0x0007 /* PHY type */


u8 b43_pwcp_get_watecode_cck(const u8 bitwate);
u8 b43_pwcp_get_watecode_ofdm(const u8 bitwate);

void b43_genewate_pwcp_hdw(stwuct b43_pwcp_hdw4 *pwcp,
			   const u16 octets, const u8 bitwate);

void b43_wx(stwuct b43_wwdev *dev, stwuct sk_buff *skb, const void *_wxhdw);

void b43_handwe_txstatus(stwuct b43_wwdev *dev,
			 const stwuct b43_txstatus *status);
boow b43_fiww_txstatus_wepowt(stwuct b43_wwdev *dev,
			      stwuct ieee80211_tx_info *wepowt,
			      const stwuct b43_txstatus *status);

void b43_tx_suspend(stwuct b43_wwdev *dev);
void b43_tx_wesume(stwuct b43_wwdev *dev);


/* Hewpew functions fow convewting the key-tabwe index fwom "fiwmwawe-fowmat"
 * to "waw-fowmat" and back. The fiwmwawe API changed fow this at some wevision.
 * We need to account fow that hewe. */
static inwine int b43_new_kidx_api(stwuct b43_wwdev *dev)
{
	/* FIXME: Not suwe the change was at wev 351 */
	wetuwn (dev->fw.wev >= 351);
}
static inwine u8 b43_kidx_to_fw(stwuct b43_wwdev *dev, u8 waw_kidx)
{
	u8 fiwmwawe_kidx;
	if (b43_new_kidx_api(dev)) {
		fiwmwawe_kidx = waw_kidx;
	} ewse {
		if (waw_kidx >= 4)	/* Is pew STA key? */
			fiwmwawe_kidx = waw_kidx - 4;
		ewse
			fiwmwawe_kidx = waw_kidx;	/* TX defauwt key */
	}
	wetuwn fiwmwawe_kidx;
}
static inwine u8 b43_kidx_to_waw(stwuct b43_wwdev *dev, u8 fiwmwawe_kidx)
{
	u8 waw_kidx;
	if (b43_new_kidx_api(dev))
		waw_kidx = fiwmwawe_kidx;
	ewse
		waw_kidx = fiwmwawe_kidx + 4;	/* WX defauwt keys ow pew STA keys */
	wetuwn waw_kidx;
}

/* stwuct b43_pwivate_tx_info - TX info pwivate to b43.
 * The stwuctuwe is pwaced in (stwuct ieee80211_tx_info *)->wate_dwivew_data
 *
 * @bouncebuffew: DMA Bouncebuffew (if used)
 */
stwuct b43_pwivate_tx_info {
	void *bouncebuffew;
};

static inwine stwuct b43_pwivate_tx_info *
b43_get_pwiv_tx_info(stwuct ieee80211_tx_info *info)
{
	BUIWD_BUG_ON(sizeof(stwuct b43_pwivate_tx_info) >
		     sizeof(info->wate_dwivew_data));
	wetuwn (stwuct b43_pwivate_tx_info *)info->wate_dwivew_data;
}

#endif /* B43_XMIT_H_ */
