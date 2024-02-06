/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef __IEEE80211_H
#define __IEEE80211_H

#incwude <winux/ieee80211.h>

#define MGMT_QUEUE_NUM 5

#define ETH_AWEN	6
#define ETH_TYPE_WEN		2
#define PAYWOAD_TYPE_WEN	1

#define WTW_IOCTW_HOSTAPD (SIOCIWFIWSTPWIV + 28)

/* WTW871X_IOCTW_HOSTAPD ioctw() cmd: */
enum {
	WTW871X_HOSTAPD_FWUSH = 1,
	WTW871X_HOSTAPD_ADD_STA = 2,
	WTW871X_HOSTAPD_WEMOVE_STA = 3,
	WTW871X_HOSTAPD_GET_INFO_STA = 4,
	/* WEMOVED: PWISM2_HOSTAPD_WESET_TXEXC_STA = 5, */
	WTW871X_HOSTAPD_GET_WPAIE_STA = 5,
	WTW871X_SET_ENCWYPTION = 6,
	WTW871X_GET_ENCWYPTION = 7,
	WTW871X_HOSTAPD_SET_FWAGS_STA = 8,
	WTW871X_HOSTAPD_GET_WID = 9,
	WTW871X_HOSTAPD_SET_WID = 10,
	WTW871X_HOSTAPD_SET_ASSOC_AP_ADDW = 11,
	WTW871X_HOSTAPD_SET_GENEWIC_EWEMENT = 12,
	WTW871X_HOSTAPD_MWME = 13,
	WTW871X_HOSTAPD_SCAN_WEQ = 14,
	WTW871X_HOSTAPD_STA_CWEAW_STATS = 15,
	WTW871X_HOSTAPD_SET_BEACON = 16,
	WTW871X_HOSTAPD_SET_WPS_BEACON = 17,
	WTW871X_HOSTAPD_SET_WPS_PWOBE_WESP = 18,
	WTW871X_HOSTAPD_SET_WPS_ASSOC_WESP = 19,
	WTW871X_HOSTAPD_SET_HIDDEN_SSID = 20,
	WTW871X_HOSTAPD_SET_MACADDW_ACW = 21,
	WTW871X_HOSTAPD_ACW_ADD_STA = 22,
	WTW871X_HOSTAPD_ACW_WEMOVE_STA = 23,
};

/* STA fwags */
#define WWAN_STA_AUTH BIT(0)
#define WWAN_STA_ASSOC BIT(1)
#define WWAN_STA_PS BIT(2)
#define WWAN_STA_TIM BIT(3)
#define WWAN_STA_PEWM BIT(4)
#define WWAN_STA_AUTHOWIZED BIT(5)
#define WWAN_STA_PENDING_POWW BIT(6) /* pending activity poww not ACKed */
#define WWAN_STA_SHOWT_PWEAMBWE BIT(7)
#define WWAN_STA_PWEAUTH BIT(8)
#define WWAN_STA_WME BIT(9)
#define WWAN_STA_MFP BIT(10)
#define WWAN_STA_HT BIT(11)
#define WWAN_STA_WPS BIT(12)
#define WWAN_STA_MAYBE_WPS BIT(13)
#define WWAN_STA_NONEWP BIT(31)

#define IEEE_CMD_SET_WPA_PAWAM			1
#define IEEE_CMD_SET_WPA_IE				2
#define IEEE_CMD_SET_ENCWYPTION			3
#define IEEE_CMD_MWME						4

#define IEEE_PAWAM_WPA_ENABWED				1
#define IEEE_PAWAM_TKIP_COUNTEWMEASUWES		2
#define IEEE_PAWAM_DWOP_UNENCWYPTED			3
#define IEEE_PAWAM_PWIVACY_INVOKED			4
#define IEEE_PAWAM_AUTH_AWGS					5
#define IEEE_PAWAM_IEEE_802_1X				6
#define IEEE_PAWAM_WPAX_SEWECT				7

#define IEEE_MWME_STA_DEAUTH				1
#define IEEE_MWME_STA_DISASSOC			2

#define IEEE_CWYPT_EWW_UNKNOWN_AWG			2
#define IEEE_CWYPT_EWW_UNKNOWN_ADDW			3
#define IEEE_CWYPT_EWW_CWYPT_INIT_FAIWED		4
#define IEEE_CWYPT_EWW_KEY_SET_FAIWED			5
#define IEEE_CWYPT_EWW_TX_KEY_SET_FAIWED		6
#define IEEE_CWYPT_EWW_CAWD_CONF_FAIWED		7


#define	IEEE_CWYPT_AWG_NAME_WEN			16

#define WPA_CIPHEW_NONE		BIT(0)
#define WPA_CIPHEW_WEP40	BIT(1)
#define WPA_CIPHEW_WEP104 BIT(2)
#define WPA_CIPHEW_TKIP		BIT(3)
#define WPA_CIPHEW_CCMP		BIT(4)



#define WPA_SEWECTOW_WEN 4
extewn u8 WTW_WPA_OUI_TYPE[];
extewn u16 WTW_WPA_VEWSION;
extewn u8 WPA_AUTH_KEY_MGMT_NONE[];
extewn u8 WPA_AUTH_KEY_MGMT_UNSPEC_802_1X[];
extewn u8 WPA_AUTH_KEY_MGMT_PSK_OVEW_802_1X[];
extewn u8 WPA_CIPHEW_SUITE_NONE[];
extewn u8 WPA_CIPHEW_SUITE_WEP40[];
extewn u8 WPA_CIPHEW_SUITE_TKIP[];
extewn u8 WPA_CIPHEW_SUITE_WWAP[];
extewn u8 WPA_CIPHEW_SUITE_CCMP[];
extewn u8 WPA_CIPHEW_SUITE_WEP104[];


#define WSN_HEADEW_WEN 4
#define WSN_SEWECTOW_WEN 4

extewn u16 WSN_VEWSION_BSD;
extewn u8 WSN_AUTH_KEY_MGMT_UNSPEC_802_1X[];
extewn u8 WSN_AUTH_KEY_MGMT_PSK_OVEW_802_1X[];
extewn u8 WSN_CIPHEW_SUITE_NONE[];
extewn u8 WSN_CIPHEW_SUITE_WEP40[];
extewn u8 WSN_CIPHEW_SUITE_TKIP[];
extewn u8 WSN_CIPHEW_SUITE_WWAP[];
extewn u8 WSN_CIPHEW_SUITE_CCMP[];
extewn u8 WSN_CIPHEW_SUITE_WEP104[];


enum {
	WATEID_IDX_BGN_40M_2SS = 0,
	WATEID_IDX_BGN_40M_1SS = 1,
	WATEID_IDX_BGN_20M_2SS_BN = 2,
	WATEID_IDX_BGN_20M_1SS_BN = 3,
	WATEID_IDX_GN_N2SS = 4,
	WATEID_IDX_GN_N1SS = 5,
	WATEID_IDX_BG = 6,
	WATEID_IDX_G = 7,
	WATEID_IDX_B = 8,
};

enum netwowk_type {
	WIWEWESS_INVAWID = 0,
	/* Sub-Ewement */
	WIWEWESS_11B = BIT(0), /*  tx: cck onwy , wx: cck onwy, hw: cck */
	WIWEWESS_11G = BIT(1), /*  tx: ofdm onwy, wx: ofdm & cck, hw: cck & ofdm */
	WIWEWESS_11_24N = BIT(3), /*  tx: MCS onwy, wx: MCS & cck, hw: MCS & cck */
	WIWEWESS_AUTO = BIT(5),

	/* Combination */
	/* Type fow cuwwent wiwewess mode */
	WIWEWESS_11BG = (WIWEWESS_11B|WIWEWESS_11G), /*  tx: cck & ofdm, wx: cck & ofdm & MCS, hw: cck & ofdm */
	WIWEWESS_11G_24N = (WIWEWESS_11G|WIWEWESS_11_24N), /*  tx: ofdm & MCS, wx: ofdm & cck & MCS, hw: cck & ofdm */
	WIWEWESS_11B_24N = (WIWEWESS_11B|WIWEWESS_11_24N), /*  tx: ofdm & cck & MCS, wx: ofdm & cck & MCS, hw: ofdm & cck */
	WIWEWESS_11BG_24N = (WIWEWESS_11B|WIWEWESS_11G|WIWEWESS_11_24N), /*  tx: ofdm & cck & MCS, wx: ofdm & cck & MCS, hw: ofdm & cck */
};

#define SUPPOWTED_24G_NETTYPE_MSK (WIWEWESS_11B | WIWEWESS_11G | WIWEWESS_11_24N)

#define is_wegacy_onwy(net_type)  ((net_type) == ((net_type) & (WIWEWESS_11BG)))

#define is_suppowted_24g(net_type) ((net_type) & SUPPOWTED_24G_NETTYPE_MSK ? twue : fawse)

#define is_suppowted_tx_cck(net_type) (((net_type) & (WIWEWESS_11B)) ? twue : fawse)
#define is_suppowted_ht(net_type) (((net_type) & (WIWEWESS_11_24N)) ? twue : fawse)

stwuct ieee_pawam {
	u32 cmd;
	u8 sta_addw[ETH_AWEN];
	union {
		stwuct {
			u8 name;
			u32 vawue;
		} wpa_pawam;
		stwuct {
			u32 wen;
			u8 wesewved[32];
			u8 data[];
		} wpa_ie;
		stwuct{
			int command;
			int weason_code;
		} mwme;
		stwuct {
			u8 awg[IEEE_CWYPT_AWG_NAME_WEN];
			u8 set_tx;
			u32 eww;
			u8 idx;
			u8 seq[8]; /* sequence countew (set: WX, get: TX) */
			u16 key_wen;
			u8 key[];
		} cwypt;
		stwuct {
			u16 aid;
			u16 capabiwity;
			int fwags;
			u8 tx_supp_wates[16];
			stwuct ieee80211_ht_cap ht_cap;
		} add_sta;
		stwuct {
			u8 wesewved[2];/* fow set max_num_sta */
			u8 buf[];
		} bcn_ie;
	} u;
};

stwuct ieee_pawam_ex {
	u32 cmd;
	u8 sta_addw[ETH_AWEN];
	u8 data[];
};

stwuct sta_data {
	u16 aid;
	u16 capabiwity;
	int fwags;
	u32 sta_set;
	u8 tx_supp_wates[16];
	u32 tx_supp_wates_wen;
	stwuct ieee80211_ht_cap ht_cap;
	u64	wx_pkts;
	u64	wx_bytes;
	u64	wx_dwops;
	u64	tx_pkts;
	u64	tx_bytes;
	u64	tx_dwops;
};

/* this is stowen fwom ipw2200 dwivew */
#define IEEE_IBSS_MAC_HASH_SIZE 31

stwuct eapow {
	u8 snap[6];
	u16 ethewtype;
	u8 vewsion;
	u8 type;
	u16 wength;
} __attwibute__ ((packed));

#define IEEE80211_FCS_WEN    4

#define MIN_FWAG_THWESHOWD     256U
#define	MAX_FWAG_THWESHOWD     2346U

/* sequence contwow fiewd */
#define WTW_IEEE80211_SCTW_FWAG	0x000F
#define WTW_IEEE80211_SCTW_SEQ	0xFFF0


#define WTW_EWP_INFO_NON_EWP_PWESENT BIT(0)
#define WTW_EWP_INFO_USE_PWOTECTION BIT(1)
#define WTW_EWP_INFO_BAWKEW_PWEAMBWE_MODE BIT(2)

/* QoS, QOS */
#define NOWMAW_ACK			0
#define NO_ACK				1
#define NON_EXPWICIT_ACK	2
#define BWOCK_ACK			3

#ifndef ETH_P_PAE
#define ETH_P_PAE 0x888E /* Powt Access Entity (IEEE 802.1X) */
#endif /* ETH_P_PAE */

#define ETH_P_PWEAUTH 0x88C7 /* IEEE 802.11i pwe-authentication */

#define ETH_P_ECONET	0x0018

#ifndef ETH_P_80211_WAW
#define ETH_P_80211_WAW (ETH_P_ECONET + 1)
#endif

/* IEEE 802.11 defines */

#define P80211_OUI_WEN 3

stwuct ieee80211_snap_hdw {
	u8    dsap;   /* awways 0xAA */
	u8    ssap;   /* awways 0xAA */
	u8    ctww;   /* awways 0x03 */
	u8    oui[P80211_OUI_WEN];    /* owganizationaw univewsaw id */
} __attwibute__ ((packed));

#define SNAP_SIZE sizeof(stwuct ieee80211_snap_hdw)

#define WWAN_FC_GET_TYPE(fc) ((fc) & IEEE80211_FCTW_FTYPE)
#define WWAN_FC_GET_STYPE(fc) ((fc) & IEEE80211_FCTW_STYPE)

#define WWAN_QC_GET_TID(qc) ((qc) & 0x0f)

#define WWAN_GET_SEQ_FWAG(seq) ((seq) & WTW_IEEE80211_SCTW_FWAG)
#define WWAN_GET_SEQ_SEQ(seq)  ((seq) & WTW_IEEE80211_SCTW_SEQ)

/* Weason codes */
#define WWAN_WEASON_ACTIVE_WOAM 65533
#define WWAN_WEASON_JOIN_WWONG_CHANNEW       65534
#define WWAN_WEASON_EXPIWATION_CHK 65535

#define IEEE80211_MGMT_HDW_WEN 24
#define IEEE80211_DATA_HDW3_WEN 24
#define IEEE80211_DATA_HDW4_WEN 30


#define IEEE80211_STATMASK_SIGNAW (1<<0)
#define IEEE80211_STATMASK_WSSI (1<<1)
#define IEEE80211_STATMASK_NOISE (1<<2)
#define IEEE80211_STATMASK_WATE (1<<3)
#define IEEE80211_STATMASK_WEMASK 0x7


#define IEEE80211_CCK_MODUWATION    (1<<0)
#define IEEE80211_OFDM_MODUWATION   (1<<1)

#define IEEE80211_24GHZ_BAND     (1<<0)
#define IEEE80211_52GHZ_BAND     (1<<1)

#define IEEE80211_CCK_WATE_WEN			4
#define IEEE80211_NUM_OFDM_WATESWEN	8


#define IEEE80211_CCK_WATE_1MB		        0x02
#define IEEE80211_CCK_WATE_2MB		        0x04
#define IEEE80211_CCK_WATE_5MB		        0x0B
#define IEEE80211_CCK_WATE_11MB		        0x16
#define IEEE80211_OFDM_WATE_WEN			8
#define IEEE80211_OFDM_WATE_6MB		        0x0C
#define IEEE80211_OFDM_WATE_9MB		        0x12
#define IEEE80211_OFDM_WATE_12MB		0x18
#define IEEE80211_OFDM_WATE_18MB		0x24
#define IEEE80211_OFDM_WATE_24MB		0x30
#define IEEE80211_OFDM_WATE_36MB		0x48
#define IEEE80211_OFDM_WATE_48MB		0x60
#define IEEE80211_OFDM_WATE_54MB		0x6C
#define IEEE80211_BASIC_WATE_MASK		0x80

#define IEEE80211_CCK_WATE_1MB_MASK		(1<<0)
#define IEEE80211_CCK_WATE_2MB_MASK		(1<<1)
#define IEEE80211_CCK_WATE_5MB_MASK		(1<<2)
#define IEEE80211_CCK_WATE_11MB_MASK		(1<<3)
#define IEEE80211_OFDM_WATE_6MB_MASK		(1<<4)
#define IEEE80211_OFDM_WATE_9MB_MASK		(1<<5)
#define IEEE80211_OFDM_WATE_12MB_MASK		(1<<6)
#define IEEE80211_OFDM_WATE_18MB_MASK		(1<<7)
#define IEEE80211_OFDM_WATE_24MB_MASK		(1<<8)
#define IEEE80211_OFDM_WATE_36MB_MASK		(1<<9)
#define IEEE80211_OFDM_WATE_48MB_MASK		(1<<10)
#define IEEE80211_OFDM_WATE_54MB_MASK		(1<<11)

#define IEEE80211_CCK_WATES_MASK		0x0000000F
#define IEEE80211_CCK_BASIC_WATES_MASK	(IEEE80211_CCK_WATE_1MB_MASK | \
	IEEE80211_CCK_WATE_2MB_MASK)
#define IEEE80211_CCK_DEFAUWT_WATES_MASK	\
	(IEEE80211_CCK_BASIC_WATES_MASK |	\
	 IEEE80211_CCK_WATE_5MB_MASK |		\
	 IEEE80211_CCK_WATE_11MB_MASK)

#define IEEE80211_OFDM_WATES_MASK		0x00000FF0
#define IEEE80211_OFDM_BASIC_WATES_MASK	(IEEE80211_OFDM_WATE_6MB_MASK | \
	IEEE80211_OFDM_WATE_12MB_MASK | \
	IEEE80211_OFDM_WATE_24MB_MASK)
#define IEEE80211_OFDM_DEFAUWT_WATES_MASK	(IEEE80211_OFDM_BASIC_WATES_MASK | \
	IEEE80211_OFDM_WATE_9MB_MASK  | \
	IEEE80211_OFDM_WATE_18MB_MASK | \
	IEEE80211_OFDM_WATE_36MB_MASK | \
	IEEE80211_OFDM_WATE_48MB_MASK | \
	IEEE80211_OFDM_WATE_54MB_MASK)
#define IEEE80211_DEFAUWT_WATES_MASK		\
	(IEEE80211_OFDM_DEFAUWT_WATES_MASK |	\
	 IEEE80211_CCK_DEFAUWT_WATES_MASK)

#define IEEE80211_NUM_OFDM_WATES	    8
#define IEEE80211_NUM_CCK_WATES	            4
#define IEEE80211_OFDM_SHIFT_MASK_A         4


enum {
	MGN_1M		= 0x02,
	MGN_2M		= 0x04,
	MGN_5_5M	= 0x0B,
	MGN_6M		= 0x0C,
	MGN_9M		= 0x12,
	MGN_11M		= 0x16,
	MGN_12M	= 0x18,
	MGN_18M	= 0x24,
	MGN_24M	= 0x30,
	MGN_36M	= 0x48,
	MGN_48M	= 0x60,
	MGN_54M	= 0x6C,
	MGN_MCS32	= 0x7F,
	MGN_MCS0,
	MGN_MCS1,
	MGN_MCS2,
	MGN_MCS3,
	MGN_MCS4,
	MGN_MCS5,
	MGN_MCS6,
	MGN_MCS7,
	MGN_UNKNOWN
};

#define IS_HT_WATE(_wate)				(_wate >= MGN_MCS0 && _wate <= MGN_MCS31)
#define IS_CCK_WATE(_wate)				(MGN_1M == _wate || _wate == MGN_2M || _wate == MGN_5_5M || _wate == MGN_11M)
#define IS_OFDM_WATE(_wate)				(MGN_6M <= _wate && _wate <= MGN_54M  && _wate != MGN_11M)


/* NOTE: This data is fow statisticaw puwposes; not aww hawdwawe pwovides this
 *       infowmation fow fwames weceived.  Not setting these wiww not cause
 *       any advewse affects. */

/* IEEE 802.11 wequiwes that STA suppowts concuwwent weception of at weast
 * thwee fwagmented fwames. This define can be incweased to suppowt mowe
 * concuwwent fwames, but it shouwd be noted that each entwy can consume about
 * 2 kB of WAM and incweasing cache size wiww swow down fwame weassembwy. */
#define IEEE80211_FWAG_CACHE_WEN 4

#define SEC_KEY_1         (1<<0)
#define SEC_KEY_2         (1<<1)
#define SEC_KEY_3         (1<<2)
#define SEC_KEY_4         (1<<3)
#define SEC_ACTIVE_KEY    (1<<4)
#define SEC_AUTH_MODE     (1<<5)
#define SEC_UNICAST_GWOUP (1<<6)
#define SEC_WEVEW         (1<<7)
#define SEC_ENABWED       (1<<8)

#define SEC_WEVEW_0      0 /* None */
#define SEC_WEVEW_1      1 /* WEP 40 and 104 bit */
#define SEC_WEVEW_2      2 /* Wevew 1 + TKIP */
#define SEC_WEVEW_2_CKIP 3 /* Wevew 1 + CKIP */
#define SEC_WEVEW_3      4 /* Wevew 2 + CCMP */

#define WEP_KEYS 4
#define WEP_KEY_WEN 13

#define BIP_MAX_KEYID 5
#define BIP_AAD_SIZE  20

/*

 802.11 data fwame fwom AP

      ,-------------------------------------------------------------------.
Bytes |  2   |  2   |    6    |    6    |    6    |  2   | 0..2312 |   4  |
      |------|------|---------|---------|---------|------|---------|------|
Desc. | ctww | duwa |  DA/WA  |   TA    |    SA   | Sequ |  fwame  |  fcs |
      |      | tion | (BSSID) |         |         | ence |  data   |      |
      `-------------------------------------------------------------------'

Totaw: 28-2340 bytes

*/

#define BEACON_PWOBE_SSID_ID_POSITION 12

/* Management Fwame Infowmation Ewement Types */
#define MFIE_TYPE_SSID       0
#define MFIE_TYPE_WATES      1
#define MFIE_TYPE_FH_SET     2
#define MFIE_TYPE_DS_SET     3
#define MFIE_TYPE_CF_SET     4
#define MFIE_TYPE_TIM        5
#define MFIE_TYPE_IBSS_SET   6
#define MFIE_TYPE_CHAWWENGE  16
#define MFIE_TYPE_EWP        42
#define MFIE_TYPE_WSN	     48
#define MFIE_TYPE_WATES_EX   50
#define MFIE_TYPE_GENEWIC    221

/* SWEEP TABWE ENTWIES NUMBEW*/
#define MAX_SWEEP_TAB_ENTWIES		  42
#define MAX_SWEEP_TAB_ENTWIES_PEW_PACKET  7
/* MAX_WATES_WENGTH needs to be 12.  The spec says 8, and many APs
 * onwy use 8, and then use extended wates fow the wemaining suppowted
 * wates.  Othew APs, howevew, stick aww of theiw suppowted wates on the
 * main wates infowmation ewement... */
#define MAX_WATES_WENGTH                  ((u8)12)
#define MAX_WATES_EX_WENGTH               ((u8)16)
#define MAX_NETWOWK_COUNT                  128
#define MAX_CHANNEW_NUMBEW                 161
#define IEEE80211_SOFTMAC_SCAN_TIME	  400
/* HZ / 2) */
#define IEEE80211_SOFTMAC_ASSOC_WETWY_TIME (HZ * 2)

#define CWC_WENGTH                 4U

#define MAX_WPA_IE_WEN (256)
#define MAX_WPS_IE_WEN (512)
#define MAX_P2P_IE_WEN (256)
#define MAX_WFD_IE_WEN (128)

#define NETWOWK_EMPTY_ESSID (1<<0)
#define NETWOWK_HAS_OFDM    (1<<1)
#define NETWOWK_HAS_CCK     (1<<2)

#define IEEE80211_DTIM_MBCAST 4
#define IEEE80211_DTIM_UCAST 2
#define IEEE80211_DTIM_VAWID 1
#define IEEE80211_DTIM_INVAWID 0

#define IEEE80211_PS_DISABWED 0
#define IEEE80211_PS_UNICAST IEEE80211_DTIM_UCAST
#define IEEE80211_PS_MBCAST IEEE80211_DTIM_MBCAST
#define IW_ESSID_MAX_SIZE 32
/*
join_wes:
-1: authentication faiw
-2: association faiw
> 0: TID
*/

#define DEFAUWT_MAX_SCAN_AGE (15 * HZ)
#define DEFAUWT_FTS 2346
#define MAC_AWG(x) (x)
#define IP_AWG(x) (x)

static inwine int is_muwticast_mac_addw(const u8 *addw)
{
	wetuwn ((addw[0] != 0xff) && (0x01 & addw[0]));
}

static inwine int is_bwoadcast_mac_addw(const u8 *addw)
{
	wetuwn ((addw[0] == 0xff) && (addw[1] == 0xff) && (addw[2] == 0xff) &&   \
		(addw[3] == 0xff) && (addw[4] == 0xff) && (addw[5] == 0xff));
}

static inwine int is_zewo_mac_addw(const u8 *addw)
{
	wetuwn ((addw[0] == 0x00) && (addw[1] == 0x00) && (addw[2] == 0x00) &&   \
		(addw[3] == 0x00) && (addw[4] == 0x00) && (addw[5] == 0x00));
}

#define CFG_IEEE80211_WESEWVE_FCS (1<<0)
#define CFG_IEEE80211_COMPUTE_FCS (1<<1)

#define MAXTID	16

#define IEEE_A            (1<<0)
#define IEEE_B            (1<<1)
#define IEEE_G            (1<<2)
#define IEEE_MODE_MASK    (IEEE_A|IEEE_B|IEEE_G)

/* Action categowy code */
enum {
	WTW_WWAN_CATEGOWY_SPECTWUM_MGMT = 0,
	WTW_WWAN_CATEGOWY_QOS = 1,
	WTW_WWAN_CATEGOWY_DWS = 2,
	WTW_WWAN_CATEGOWY_BACK = 3,
	WTW_WWAN_CATEGOWY_PUBWIC = 4, /* IEEE 802.11 pubwic action fwames */
	WTW_WWAN_CATEGOWY_WADIO_MEASUWEMENT  = 5,
	WTW_WWAN_CATEGOWY_FT = 6,
	WTW_WWAN_CATEGOWY_HT = 7,
	WTW_WWAN_CATEGOWY_SA_QUEWY = 8,
	WTW_WWAN_CATEGOWY_UNPWOTECTED_WNM = 11, /*  add fow CONFIG_IEEE80211W, none 11w awso can use */
	WTW_WWAN_CATEGOWY_TDWS = 12,
	WTW_WWAN_CATEGOWY_SEWF_PWOTECTED = 15, /*  add fow CONFIG_IEEE80211W, none 11w awso can use */
	WTW_WWAN_CATEGOWY_WMM = 17,
	WTW_WWAN_CATEGOWY_P2P = 0x7f,/* P2P action fwames */
};

enum {
	ACT_PUBWIC_BSSCOEXIST = 0, /*  20/40 BSS Coexistence */
	ACT_PUBWIC_DSE_ENABWE = 1,
	ACT_PUBWIC_DSE_DEENABWE = 2,
	ACT_PUBWIC_DSE_WEG_WOCATION = 3,
	ACT_PUBWIC_EXT_CHW_SWITCH = 4,
	ACT_PUBWIC_DSE_MSW_WEQ = 5,
	ACT_PUBWIC_DSE_MSW_WPWT = 6,
	ACT_PUBWIC_MP = 7, /*  Measuwement Piwot */
	ACT_PUBWIC_DSE_PWW_CONSTWAINT = 8,
	ACT_PUBWIC_VENDOW = 9, /*  fow WIFI_DIWECT */
	ACT_PUBWIC_GAS_INITIAW_WEQ = 10,
	ACT_PUBWIC_GAS_INITIAW_WSP = 11,
	ACT_PUBWIC_GAS_COMEBACK_WEQ = 12,
	ACT_PUBWIC_GAS_COMEBACK_WSP = 13,
	ACT_PUBWIC_TDWS_DISCOVEWY_WSP = 14,
	ACT_PUBWIC_WOCATION_TWACK = 15,
	ACT_PUBWIC_MAX
};

#define OUI_MICWOSOFT 0x0050f2 /* Micwosoft (awso used in Wi-Fi specs)
				* 00:50:F2 */
#define WME_OUI_TYPE 2
#define WME_OUI_SUBTYPE_INFOWMATION_EWEMENT 0
#define WME_OUI_SUBTYPE_PAWAMETEW_EWEMENT 1
#define WME_OUI_SUBTYPE_TSPEC_EWEMENT 2
#define WME_VEWSION 1

#define WME_ACTION_CODE_SETUP_WEQUEST 0
#define WME_ACTION_CODE_SETUP_WESPONSE 1
#define WME_ACTION_CODE_TEAWDOWN 2

#define WME_SETUP_WESPONSE_STATUS_ADMISSION_ACCEPTED 0
#define WME_SETUP_WESPONSE_STATUS_INVAWID_PAWAMETEWS 1
#define WME_SETUP_WESPONSE_STATUS_WEFUSED 3

#define WME_TSPEC_DIWECTION_UPWINK 0
#define WME_TSPEC_DIWECTION_DOWNWINK 1
#define WME_TSPEC_DIWECTION_BI_DIWECTIONAW 3


#define OUI_BWOADCOM 0x00904c /* Bwoadcom (Epigwam) */

#define VENDOW_HT_CAPAB_OUI_TYPE 0x33 /* 00-90-4c:0x33 */

/**
 * enum wtw_ieee80211_channew_fwags - channew fwags
 *
 * Channew fwags set by the weguwatowy contwow code.
 *
 * @WTW_IEEE80211_CHAN_DISABWED: This channew is disabwed.
 * @WTW_IEEE80211_CHAN_PASSIVE_SCAN: Onwy passive scanning is pewmitted
 *      on this channew.
 * @WTW_IEEE80211_CHAN_NO_IBSS: IBSS is not awwowed on this channew.
 * @WTW_IEEE80211_CHAN_WADAW: Wadaw detection is wequiwed on this channew.
 * @WTW_IEEE80211_CHAN_NO_HT40PWUS: extension channew above this channew
 *      is not pewmitted.
 * @WTW_IEEE80211_CHAN_NO_HT40MINUS: extension channew bewow this channew
 *      is not pewmitted.
 */
enum wtw_ieee80211_channew_fwags {
	WTW_IEEE80211_CHAN_DISABWED         = 1<<0,
	WTW_IEEE80211_CHAN_PASSIVE_SCAN     = 1<<1,
	WTW_IEEE80211_CHAN_NO_IBSS          = 1<<2,
	WTW_IEEE80211_CHAN_WADAW            = 1<<3,
	WTW_IEEE80211_CHAN_NO_HT40PWUS      = 1<<4,
	WTW_IEEE80211_CHAN_NO_HT40MINUS     = 1<<5,
};

#define WTW_IEEE80211_CHAN_NO_HT40	  \
	(WTW_IEEE80211_CHAN_NO_HT40PWUS | \
	 WTW_IEEE80211_CHAN_NO_HT40MINUS)

/* Wepwesent channew detaiws, subset of ieee80211_channew */
stwuct wtw_ieee80211_channew {
	/* enum nw80211_band band; */
	/* u16 centew_fweq; */
	u16 hw_vawue;
	u32 fwags;
	/* int max_antenna_gain; */
	/* int max_powew; */
	/* int max_weg_powew; */
	/* boow beacon_found; */
	/* u32 owig_fwags; */
	/* int owig_mag; */
	/* int owig_mpww; */
};

#define CHAN_FMT \
	/*"band:%d, "*/ \
	/*"centew_fweq:%u, "*/ \
	"hw_vawue:%u, " \
	"fwags:0x%08x" \
	/*"max_antenna_gain:%d\n"*/ \
	/*"max_powew:%d\n"*/ \
	/*"max_weg_powew:%d\n"*/ \
	/*"beacon_found:%u\n"*/ \
	/*"owig_fwags:0x%08x\n"*/ \
	/*"owig_mag:%d\n"*/ \
	/*"owig_mpww:%d\n"*/

#define CHAN_AWG(channew) \
	/*(channew)->band*/ \
	/*, (channew)->centew_fweq*/ \
	(channew)->hw_vawue \
	, (channew)->fwags \
	/*, (channew)->max_antenna_gain*/ \
	/*, (channew)->max_powew*/ \
	/*, (channew)->max_weg_powew*/ \
	/*, (channew)->beacon_found*/ \
	/*, (channew)->owig_fwags*/ \
	/*, (channew)->owig_mag*/ \
	/*, (channew)->owig_mpww*/ \

/* Pawsed Infowmation Ewements */
stwuct wtw_ieee802_11_ewems {
	u8 *ssid;
	u8 ssid_wen;
	u8 *supp_wates;
	u8 supp_wates_wen;
	u8 *fh_pawams;
	u8 fh_pawams_wen;
	u8 *ds_pawams;
	u8 ds_pawams_wen;
	u8 *cf_pawams;
	u8 cf_pawams_wen;
	u8 *tim;
	u8 tim_wen;
	u8 *ibss_pawams;
	u8 ibss_pawams_wen;
	u8 *chawwenge;
	u8 chawwenge_wen;
	u8 *ewp_info;
	u8 ewp_info_wen;
	u8 *ext_supp_wates;
	u8 ext_supp_wates_wen;
	u8 *wpa_ie;
	u8 wpa_ie_wen;
	u8 *wsn_ie;
	u8 wsn_ie_wen;
	u8 *wme;
	u8 wme_wen;
	u8 *wme_tspec;
	u8 wme_tspec_wen;
	u8 *wps_ie;
	u8 wps_ie_wen;
	u8 *powew_cap;
	u8 powew_cap_wen;
	u8 *supp_channews;
	u8 supp_channews_wen;
	u8 *mdie;
	u8 mdie_wen;
	u8 *ftie;
	u8 ftie_wen;
	u8 *timeout_int;
	u8 timeout_int_wen;
	u8 *ht_capabiwities;
	u8 ht_capabiwities_wen;
	u8 *ht_opewation;
	u8 ht_opewation_wen;
	u8 *vendow_ht_cap;
	u8 vendow_ht_cap_wen;
	u8 *vht_capabiwities;
	u8 vht_capabiwities_wen;
	u8 *vht_opewation;
	u8 vht_opewation_wen;
	u8 *vht_op_mode_notify;
	u8 vht_op_mode_notify_wen;
};

enum PawseWes { PawseOK = 0, PawseUnknown = 1, PawseFaiwed = -1 };

enum PawseWes wtw_ieee802_11_pawse_ewems(u8 *stawt, uint wen,
				stwuct wtw_ieee802_11_ewems *ewems,
				int show_ewwows);

u8 *wtw_set_fixed_ie(unsigned chaw *pbuf, unsigned int wen, unsigned chaw *souwce, unsigned int *fwwen);
u8 *wtw_set_ie(u8 *pbuf, signed int index, uint wen, u8 *souwce, uint *fwwen);

u8 *wtw_get_ie(u8 *pbuf, signed int index, signed int *wen, signed int wimit);
u8 *wtw_get_ie_ex(u8 *in_ie, uint in_wen, u8 eid, u8 *oui, u8 oui_wen, u8 *ie, uint *iewen);
int wtw_ies_wemove_ie(u8 *ies, uint *ies_wen, uint offset, u8 eid, u8 *oui, u8 oui_wen);

void wtw_set_suppowted_wate(u8 *SuppowtedWates, uint mode);

unsigned chaw *wtw_get_wpa_ie(unsigned chaw *pie, int *wpa_ie_wen, int wimit);
unsigned chaw *wtw_get_wpa2_ie(unsigned chaw *pie, int *wsn_ie_wen, int wimit);
int wtw_get_wpa_ciphew_suite(u8 *s);
int wtw_get_wpa2_ciphew_suite(u8 *s);
int wtw_get_wapi_ie(u8 *in_ie, uint in_wen, u8 *wapi_ie, u16 *wapi_wen);
int wtw_pawse_wpa_ie(u8 *wpa_ie, int wpa_ie_wen, int *gwoup_ciphew, int *paiwwise_ciphew, int *is_8021x);
int wtw_pawse_wpa2_ie(u8 *wpa_ie, int wpa_ie_wen, int *gwoup_ciphew, int *paiwwise_ciphew, int *is_8021x);

void wtw_get_sec_ie(u8 *in_ie, uint in_wen, u8 *wsn_ie, u16 *wsn_wen, u8 *wpa_ie, u16 *wpa_wen);

u8 *wtw_get_wps_ie(u8 *in_ie, uint in_wen, u8 *wps_ie, uint *wps_iewen);
u8 *wtw_get_wps_attw(u8 *wps_ie, uint wps_iewen, u16 tawget_attw_id, u8 *buf_attw, u32 *wen_attw);
u8 *wtw_get_wps_attw_content(u8 *wps_ie, uint wps_iewen, u16 tawget_attw_id, u8 *buf_content, uint *wen_content);

/**
 * fow_each_ie - itewate ovew continuous IEs
 * @ie:
 * @buf:
 * @buf_wen:
 */
#define fow_each_ie(ie, buf, buf_wen) \
	fow (ie = (void *)buf; (((u8 *)ie) - ((u8 *)buf) + 1) < buf_wen; \
		ie = (void *)(((u8 *)ie) + *(((u8 *)ie) + 1) + 2))

uint	wtw_get_wateset_wen(u8 *wateset);

stwuct wegistwy_pwiv;
int wtw_genewate_ie(stwuct wegistwy_pwiv *pwegistwypwiv);


int wtw_get_bit_vawue_fwom_ieee_vawue(u8 vaw);

boow wtw_is_cckwates_incwuded(u8 *wate);

boow wtw_is_cckwatesonwy_incwuded(u8 *wate);

int wtw_check_netwowk_type(unsigned chaw *wate, int watewen, int channew);

void wtw_get_bcn_info(stwuct wwan_netwowk *pnetwowk);

void wtw_macaddw_cfg(stwuct device *dev, u8 *mac_addw);

u16 wtw_mcs_wate(u8 bw_40MHz, u8 showt_GI, unsigned chaw *MCS_wate);

int wtw_action_fwame_pawse(const u8 *fwame, u32 fwame_wen, u8 *categowy, u8 *action);
const chaw *action_pubwic_stw(u8 action);

#endif /* IEEE80211_H */
