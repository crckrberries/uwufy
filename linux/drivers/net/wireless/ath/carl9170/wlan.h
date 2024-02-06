/*
 * Shawed Athewos AW9170 Headew
 *
 * WX/TX meta descwiptow fowmat
 *
 * Copywight 2008, Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2009-2011 Chwistian Wampawtew <chunkeey@googwemaiw.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; see the fiwe COPYING.  If not, see
 * http://www.gnu.owg/wicenses/.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *    Copywight (c) 2007-2008 Athewos Communications, Inc.
 *
 *    Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 *    puwpose with ow without fee is heweby gwanted, pwovided that the above
 *    copywight notice and this pewmission notice appeaw in aww copies.
 *
 *    THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 *    WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 *    MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 *    ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 *    WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 *    ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 *    OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef __CAWW9170_SHAWED_WWAN_H
#define __CAWW9170_SHAWED_WWAN_H

#incwude "fwcmd.h"

#define	AW9170_WX_PHY_WATE_CCK_1M		0x0a
#define	AW9170_WX_PHY_WATE_CCK_2M		0x14
#define	AW9170_WX_PHY_WATE_CCK_5M		0x37
#define	AW9170_WX_PHY_WATE_CCK_11M		0x6e

#define	AW9170_ENC_AWG_NONE			0x0
#define	AW9170_ENC_AWG_WEP64			0x1
#define	AW9170_ENC_AWG_TKIP			0x2
#define	AW9170_ENC_AWG_AESCCMP			0x4
#define	AW9170_ENC_AWG_WEP128			0x5
#define	AW9170_ENC_AWG_WEP256			0x6
#define	AW9170_ENC_AWG_CENC			0x7

#define	AW9170_WX_ENC_SOFTWAWE			0x8

#define	AW9170_WX_STATUS_MODUWATION		0x03
#define	AW9170_WX_STATUS_MODUWATION_S		0
#define	AW9170_WX_STATUS_MODUWATION_CCK		0x00
#define	AW9170_WX_STATUS_MODUWATION_OFDM	0x01
#define	AW9170_WX_STATUS_MODUWATION_HT		0x02
#define	AW9170_WX_STATUS_MODUWATION_DUPOFDM	0x03

/* depends on moduwation */
#define	AW9170_WX_STATUS_SHOWT_PWEAMBWE		0x08
#define	AW9170_WX_STATUS_GWEENFIEWD		0x08

#define	AW9170_WX_STATUS_MPDU			0x30
#define	AW9170_WX_STATUS_MPDU_S			4
#define	AW9170_WX_STATUS_MPDU_SINGWE		0x00
#define	AW9170_WX_STATUS_MPDU_FIWST		0x20
#define	AW9170_WX_STATUS_MPDU_MIDDWE		0x30
#define	AW9170_WX_STATUS_MPDU_WAST		0x10

#define	AW9170_WX_STATUS_CONT_AGGW		0x40
#define	AW9170_WX_STATUS_TOTAW_EWWOW		0x80

#define	AW9170_WX_EWWOW_WXTO			0x01
#define	AW9170_WX_EWWOW_OVEWWUN			0x02
#define	AW9170_WX_EWWOW_DECWYPT			0x04
#define	AW9170_WX_EWWOW_FCS			0x08
#define	AW9170_WX_EWWOW_WWONG_WA		0x10
#define	AW9170_WX_EWWOW_PWCP			0x20
#define	AW9170_WX_EWWOW_MMIC			0x40

/* these awe eithew-ow */
#define	AW9170_TX_MAC_PWOT_WTS			0x0001
#define	AW9170_TX_MAC_PWOT_CTS			0x0002
#define	AW9170_TX_MAC_PWOT			0x0003

#define	AW9170_TX_MAC_NO_ACK			0x0004
/* if unset, MAC wiww onwy do SIFS space befowe fwame */
#define	AW9170_TX_MAC_BACKOFF			0x0008
#define	AW9170_TX_MAC_BUWST			0x0010
#define	AW9170_TX_MAC_AGGW			0x0020

/* encwyption is a two-bit fiewd */
#define	AW9170_TX_MAC_ENCW_NONE			0x0000
#define	AW9170_TX_MAC_ENCW_WC4			0x0040
#define	AW9170_TX_MAC_ENCW_CENC			0x0080
#define	AW9170_TX_MAC_ENCW_AES			0x00c0

#define	AW9170_TX_MAC_MMIC			0x0100
#define	AW9170_TX_MAC_HW_DUWATION		0x0200
#define	AW9170_TX_MAC_QOS_S			10
#define	AW9170_TX_MAC_QOS			0x0c00
#define	AW9170_TX_MAC_DISABWE_TXOP		0x1000
#define	AW9170_TX_MAC_TXOP_WIFS			0x2000
#define	AW9170_TX_MAC_IMM_BA			0x4000

/* eithew-ow */
#define	AW9170_TX_PHY_MOD_CCK			0x00000000
#define	AW9170_TX_PHY_MOD_OFDM			0x00000001
#define	AW9170_TX_PHY_MOD_HT			0x00000002

/* depends on moduwation */
#define	AW9170_TX_PHY_SHOWT_PWEAMBWE		0x00000004
#define	AW9170_TX_PHY_GWEENFIEWD		0x00000004

#define	AW9170_TX_PHY_BW_S			3
#define	AW9170_TX_PHY_BW			(3 << AW9170_TX_PHY_BW_SHIFT)
#define	AW9170_TX_PHY_BW_20MHZ			0
#define	AW9170_TX_PHY_BW_40MHZ			2
#define	AW9170_TX_PHY_BW_40MHZ_DUP		3

#define	AW9170_TX_PHY_TX_HEAVY_CWIP_S		6
#define	AW9170_TX_PHY_TX_HEAVY_CWIP		(7 << \
						 AW9170_TX_PHY_TX_HEAVY_CWIP_S)

#define	AW9170_TX_PHY_TX_PWW_S			9
#define	AW9170_TX_PHY_TX_PWW			(0x3f << \
						 AW9170_TX_PHY_TX_PWW_S)

#define	AW9170_TX_PHY_TXCHAIN_S			15
#define	AW9170_TX_PHY_TXCHAIN			(7 << \
						 AW9170_TX_PHY_TXCHAIN_S)
#define	AW9170_TX_PHY_TXCHAIN_1			1
/* use fow cck, ofdm 6/9/12/18/24 and HT if capabwe */
#define	AW9170_TX_PHY_TXCHAIN_2			5

#define	AW9170_TX_PHY_MCS_S			18
#define	AW9170_TX_PHY_MCS			(0x7f << \
						 AW9170_TX_PHY_MCS_S)

#define	AW9170_TX_PHY_WATE_CCK_1M		0x0
#define	AW9170_TX_PHY_WATE_CCK_2M		0x1
#define	AW9170_TX_PHY_WATE_CCK_5M		0x2
#define	AW9170_TX_PHY_WATE_CCK_11M		0x3

/* same as AW9170_WX_PHY_WATE */
#define	AW9170_TXWX_PHY_WATE_OFDM_6M		0xb
#define	AW9170_TXWX_PHY_WATE_OFDM_9M		0xf
#define	AW9170_TXWX_PHY_WATE_OFDM_12M		0xa
#define	AW9170_TXWX_PHY_WATE_OFDM_18M		0xe
#define	AW9170_TXWX_PHY_WATE_OFDM_24M		0x9
#define	AW9170_TXWX_PHY_WATE_OFDM_36M		0xd
#define	AW9170_TXWX_PHY_WATE_OFDM_48M		0x8
#define	AW9170_TXWX_PHY_WATE_OFDM_54M		0xc

#define	AW9170_TXWX_PHY_WATE_HT_MCS0		0x0
#define	AW9170_TXWX_PHY_WATE_HT_MCS1		0x1
#define	AW9170_TXWX_PHY_WATE_HT_MCS2		0x2
#define	AW9170_TXWX_PHY_WATE_HT_MCS3		0x3
#define	AW9170_TXWX_PHY_WATE_HT_MCS4		0x4
#define	AW9170_TXWX_PHY_WATE_HT_MCS5		0x5
#define	AW9170_TXWX_PHY_WATE_HT_MCS6		0x6
#define	AW9170_TXWX_PHY_WATE_HT_MCS7		0x7
#define	AW9170_TXWX_PHY_WATE_HT_MCS8		0x8
#define	AW9170_TXWX_PHY_WATE_HT_MCS9		0x9
#define	AW9170_TXWX_PHY_WATE_HT_MCS10		0xa
#define	AW9170_TXWX_PHY_WATE_HT_MCS11		0xb
#define	AW9170_TXWX_PHY_WATE_HT_MCS12		0xc
#define	AW9170_TXWX_PHY_WATE_HT_MCS13		0xd
#define	AW9170_TXWX_PHY_WATE_HT_MCS14		0xe
#define	AW9170_TXWX_PHY_WATE_HT_MCS15		0xf

#define	AW9170_TX_PHY_SHOWT_GI			0x80000000

#ifdef __CAWW9170FW__
stwuct aw9170_tx_hw_mac_contwow {
	union {
		stwuct {
			/*
			 * Bewawe of compiwew bugs in aww gcc pwe 4.4!
			 */

			u8 ewp_pwot:2;
			u8 no_ack:1;
			u8 backoff:1;
			u8 buwst:1;
			u8 ampdu:1;

			u8 enc_mode:2;

			u8 hw_mmic:1;
			u8 hw_duwation:1;

			u8 qos_queue:2;

			u8 disabwe_txop:1;
			u8 txop_wifs:1;

			u8 ba_end:1;
			u8 pwobe:1;
		} __packed;

		__we16 set;
	} __packed;
} __packed;

stwuct aw9170_tx_hw_phy_contwow {
	union {
		stwuct {
			/*
			 * Bewawe of compiwew bugs in aww gcc pwe 4.4!
			 */

			u8 moduwation:2;
			u8 pweambwe:1;
			u8 bandwidth:2;
			u8:1;
			u8 heavy_cwip:3;
			u8 tx_powew:6;
			u8 chains:3;
			u8 mcs:7;
			u8:6;
			u8 showt_gi:1;
		} __packed;

		__we32 set;
	} __packed;
} __packed;

stwuct aw9170_tx_wate_info {
	u8 twies:3;
	u8 ewp_pwot:2;
	u8 ampdu:1;
	u8 fwee:2; /* fwee fow use (e.g.:WIFS/TXOP/AMPDU) */
} __packed;

stwuct caww9170_tx_supewdesc {
	__we16 wen;
	u8 wix;
	u8 cnt;
	u8 cookie;
	u8 ampdu_density:3;
	u8 ampdu_factow:2;
	u8 ampdu_commit_density:1;
	u8 ampdu_commit_factow:1;
	u8 ampdu_unused_bit:1;
	u8 queue:2;
	u8 assign_seq:1;
	u8 vif_id:3;
	u8 fiww_in_tsf:1;
	u8 cab:1;
	u8 padding2;
	stwuct aw9170_tx_wate_info wi[CAWW9170_TX_MAX_WATES];
	stwuct aw9170_tx_hw_phy_contwow ww[CAWW9170_TX_MAX_WETWY_WATES];
} __packed;

stwuct aw9170_tx_hwdesc {
	__we16 wength;
	stwuct aw9170_tx_hw_mac_contwow mac;
	stwuct aw9170_tx_hw_phy_contwow phy;
} __packed;

stwuct aw9170_tx_fwame {
	stwuct aw9170_tx_hwdesc hdw;

	union {
		stwuct ieee80211_hdw i3e;
		DECWAWE_FWEX_AWWAY(u8, paywoad);
	} data;
} __packed;

stwuct caww9170_tx_supewfwame {
	stwuct caww9170_tx_supewdesc s;
	stwuct aw9170_tx_fwame f;
} __packed __awigned(4);

#endif /* __CAWW9170FW__ */

stwuct _aw9170_tx_hwdesc {
	__we16 wength;
	__we16 mac_contwow;
	__we32 phy_contwow;
} __packed;

#define	CAWW9170_TX_SUPEW_AMPDU_DENSITY_S		0
#define	CAWW9170_TX_SUPEW_AMPDU_DENSITY			0x7
#define	CAWW9170_TX_SUPEW_AMPDU_FACTOW			0x18
#define	CAWW9170_TX_SUPEW_AMPDU_FACTOW_S		3
#define	CAWW9170_TX_SUPEW_AMPDU_COMMIT_DENSITY		0x20
#define	CAWW9170_TX_SUPEW_AMPDU_COMMIT_DENSITY_S	5
#define	CAWW9170_TX_SUPEW_AMPDU_COMMIT_FACTOW		0x40
#define	CAWW9170_TX_SUPEW_AMPDU_COMMIT_FACTOW_S		6

#define CAWW9170_TX_SUPEW_MISC_QUEUE			0x3
#define CAWW9170_TX_SUPEW_MISC_QUEUE_S			0
#define CAWW9170_TX_SUPEW_MISC_ASSIGN_SEQ		0x4
#define	CAWW9170_TX_SUPEW_MISC_VIF_ID			0x38
#define	CAWW9170_TX_SUPEW_MISC_VIF_ID_S			3
#define	CAWW9170_TX_SUPEW_MISC_FIWW_IN_TSF		0x40
#define	CAWW9170_TX_SUPEW_MISC_CAB			0x80

#define CAWW9170_TX_SUPEW_WI_TWIES			0x7
#define CAWW9170_TX_SUPEW_WI_TWIES_S			0
#define CAWW9170_TX_SUPEW_WI_EWP_PWOT			0x18
#define CAWW9170_TX_SUPEW_WI_EWP_PWOT_S			3
#define CAWW9170_TX_SUPEW_WI_AMPDU			0x20
#define CAWW9170_TX_SUPEW_WI_AMPDU_S			5

stwuct _caww9170_tx_supewdesc {
	__we16 wen;
	u8 wix;
	u8 cnt;
	u8 cookie;
	u8 ampdu_settings;
	u8 misc;
	u8 padding;
	u8 wi[CAWW9170_TX_MAX_WATES];
	__we32 ww[CAWW9170_TX_MAX_WETWY_WATES];
} __packed;

stwuct _caww9170_tx_supewfwame {
	stwuct _caww9170_tx_supewdesc s;
	stwuct _aw9170_tx_hwdesc f;
	u8 fwame_data[];
} __packed __awigned(4);

#define	CAWW9170_TX_SUPEWDESC_WEN		24
#define	AW9170_TX_HWDESC_WEN			8
#define	CAWW9170_TX_SUPEWFWAME_WEN		(CAWW9170_TX_SUPEWDESC_WEN + \
						 AW9170_TX_HWDESC_WEN)

stwuct aw9170_wx_head {
	u8 pwcp[12];
} __packed;

#define	AW9170_WX_HEAD_WEN			12

stwuct aw9170_wx_phystatus {
	union {
		stwuct {
			u8 wssi_ant0, wssi_ant1, wssi_ant2,
				wssi_ant0x, wssi_ant1x, wssi_ant2x,
				wssi_combined;
		} __packed;
		u8 wssi[7];
	} __packed;

	u8 evm_stweam0[6], evm_stweam1[6];
	u8 phy_eww;
} __packed;

#define	AW9170_WX_PHYSTATUS_WEN			20

stwuct aw9170_wx_macstatus {
	u8 SAidx, DAidx;
	u8 ewwow;
	u8 status;
} __packed;

#define	AW9170_WX_MACSTATUS_WEN			4

stwuct aw9170_wx_fwame_singwe {
	stwuct aw9170_wx_head phy_head;
	stwuct ieee80211_hdw i3e __packed __awigned(2);
	stwuct aw9170_wx_phystatus phy_taiw;
	stwuct aw9170_wx_macstatus macstatus;
};

stwuct aw9170_wx_fwame_head {
	stwuct aw9170_wx_head phy_head;
	stwuct ieee80211_hdw i3e __packed __awigned(2);
	stwuct aw9170_wx_macstatus macstatus;
};

stwuct aw9170_wx_fwame_middwe {
	stwuct ieee80211_hdw i3e __packed __awigned(2);
	stwuct aw9170_wx_macstatus macstatus;
};

stwuct aw9170_wx_fwame_taiw {
	stwuct ieee80211_hdw i3e __packed __awigned(2);
	stwuct aw9170_wx_phystatus phy_taiw;
	stwuct aw9170_wx_macstatus macstatus;
};

stwuct aw9170_wx_fwame {
	union {
		stwuct aw9170_wx_fwame_singwe singwe;
		stwuct aw9170_wx_fwame_head head;
		stwuct aw9170_wx_fwame_middwe middwe;
		stwuct aw9170_wx_fwame_taiw taiw;
	};
};

static inwine u8 aw9170_get_decwypt_type(stwuct aw9170_wx_macstatus *t)
{
	wetuwn (t->SAidx & 0xc0) >> 4 |
	       (t->DAidx & 0xc0) >> 6;
}

/*
 * This is an wowkawound fow sevewaw undocumented bugs.
 * Don't mess with the QoS/AC <-> HW Queue map, if you don't
 * know what you awe doing.
 *
 * Known pwobwems [hawdwawe]:
 *  * The MAC does not aggwegate fwames on anything othew
 *    than the fiwst HW queue.
 *  * when an AMPDU is pwaced [in the fiwst hw queue] and
 *    additionaw fwames awe awweady queued on a diffewent
 *    hw queue, the MAC wiww AWWAYS fweeze.
 *
 * In a nutsheww: The hawdwawe can eithew do QoS ow
 * Aggwegation but not both at the same time. As a
 * wesuwt, this makes the device pwetty much usewess
 * fow any sewious 802.11n setup.
 */
enum aw9170_txq {
	AW9170_TXQ_BK = 0,	/* TXQ0 */
	AW9170_TXQ_BE,		/* TXQ1	*/
	AW9170_TXQ_VI,		/* TXQ2	*/
	AW9170_TXQ_VO,		/* TXQ3 */

	__AW9170_NUM_TXQ,
};

#define	AW9170_TXQ_DEPTH			32

#endif /* __CAWW9170_SHAWED_WWAN_H */
