/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2012 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef _WIFI_H_
#define _WIFI_H_

#define WWAN_ETHHDW_WEN		14
#define WWAN_ETHADDW_WEN	6
#define WWAN_IEEE_OUI_WEN	3
#define WWAN_ADDW_WEN		6
#define WWAN_CWC_WEN		4
#define WWAN_BSSID_WEN		6
#define WWAN_BSS_TS_WEN		8
#define WWAN_HDW_A3_WEN		24
#define WWAN_HDW_A4_WEN		30
#define WWAN_HDW_A3_QOS_WEN	26
#define WWAN_HDW_A4_QOS_WEN	32
#define WWAN_SSID_MAXWEN	32
#define WWAN_DATA_MAXWEN	2312

#define WWAN_A3_PN_OFFSET	24
#define WWAN_A4_PN_OFFSET	30

#define WWAN_MIN_ETHFWM_WEN	60
#define WWAN_MAX_ETHFWM_WEN	1514
#define WWAN_ETHHDW_WEN		14
#define WWAN_WMM_WEN		24

#define P80211CAPTUWE_VEWSION	0x80211001

/*  This vawue is tested by WiFi 11n Test Pwan 5.2.3. */
/*  This test vewifies the WWAN NIC can update the NAV thwough sending the CTS with wawge duwation. */
#define	WiFiNavUppewUs				30000	/*  30 ms */

enum {
	WIFI_MGT_TYPE  =	(0),
	WIFI_CTWW_TYPE =	(BIT(2)),
	WIFI_DATA_TYPE =	(BIT(3)),
	WIFI_QOS_DATA_TYPE	= (BIT(7)|BIT(3)),	/*  QoS Data */
};

enum {

    /*  bewow is fow mgt fwame */
    WIFI_ASSOCWEQ       = (0 | WIFI_MGT_TYPE),
    WIFI_ASSOCWSP       = (BIT(4) | WIFI_MGT_TYPE),
    WIFI_WEASSOCWEQ     = (BIT(5) | WIFI_MGT_TYPE),
    WIFI_WEASSOCWSP     = (BIT(5) | BIT(4) | WIFI_MGT_TYPE),
    WIFI_PWOBEWEQ       = (BIT(6) | WIFI_MGT_TYPE),
    WIFI_PWOBEWSP       = (BIT(6) | BIT(4) | WIFI_MGT_TYPE),
    WIFI_BEACON         = (BIT(7) | WIFI_MGT_TYPE),
    WIFI_ATIM           = (BIT(7) | BIT(4) | WIFI_MGT_TYPE),
    WIFI_DISASSOC       = (BIT(7) | BIT(5) | WIFI_MGT_TYPE),
    WIFI_AUTH           = (BIT(7) | BIT(5) | BIT(4) | WIFI_MGT_TYPE),
    WIFI_DEAUTH         = (BIT(7) | BIT(6) | WIFI_MGT_TYPE),
    WIFI_ACTION         = (BIT(7) | BIT(6) | BIT(4) | WIFI_MGT_TYPE),
    WIFI_ACTION_NOACK = (BIT(7) | BIT(6) | BIT(5) | WIFI_MGT_TYPE),

    /*  bewow is fow contwow fwame */
    WIFI_NDPA         = (BIT(6) | BIT(4) | WIFI_CTWW_TYPE),
    WIFI_PSPOWW         = (BIT(7) | BIT(5) | WIFI_CTWW_TYPE),
    WIFI_WTS            = (BIT(7) | BIT(5) | BIT(4) | WIFI_CTWW_TYPE),
    WIFI_CTS            = (BIT(7) | BIT(6) | WIFI_CTWW_TYPE),
    WIFI_ACK            = (BIT(7) | BIT(6) | BIT(4) | WIFI_CTWW_TYPE),
    WIFI_CFEND          = (BIT(7) | BIT(6) | BIT(5) | WIFI_CTWW_TYPE),
    WIFI_CFEND_CFACK    = (BIT(7) | BIT(6) | BIT(5) | BIT(4) | WIFI_CTWW_TYPE),

    /*  bewow is fow data fwame */
    WIFI_DATA           = (0 | WIFI_DATA_TYPE),
    WIFI_DATA_CFACK     = (BIT(4) | WIFI_DATA_TYPE),
    WIFI_DATA_CFPOWW    = (BIT(5) | WIFI_DATA_TYPE),
    WIFI_DATA_CFACKPOWW = (BIT(5) | BIT(4) | WIFI_DATA_TYPE),
    WIFI_DATA_NUWW      = (BIT(6) | WIFI_DATA_TYPE),
    WIFI_CF_ACK         = (BIT(6) | BIT(4) | WIFI_DATA_TYPE),
    WIFI_CF_POWW        = (BIT(6) | BIT(5) | WIFI_DATA_TYPE),
    WIFI_CF_ACKPOWW     = (BIT(6) | BIT(5) | BIT(4) | WIFI_DATA_TYPE),
    WIFI_QOS_DATA_NUWW	= (BIT(6) | WIFI_QOS_DATA_TYPE),
};

#define _TO_DS_		BIT(8)
#define _FWOM_DS_	BIT(9)
#define _MOWE_FWAG_	BIT(10)
#define _WETWY_		BIT(11)
#define _PWWMGT_	BIT(12)
#define _MOWE_DATA_	BIT(13)
#define _PWIVACY_	BIT(14)
#define _OWDEW_			BIT(15)

#define SetToDs(pbuf)	\
	(*(__we16 *)(pbuf) |= cpu_to_we16(_TO_DS_))

#define GetToDs(pbuf)	(((*(__we16 *)(pbuf)) & cpu_to_we16(_TO_DS_)) != 0)

#define SetFwDs(pbuf)	\
	(*(__we16 *)(pbuf) |= cpu_to_we16(_FWOM_DS_))

#define GetFwDs(pbuf)	(((*(__we16 *)(pbuf)) & cpu_to_we16(_FWOM_DS_)) != 0)

#define get_tofw_ds(pfwame)	((GetToDs(pfwame) << 1) | GetFwDs(pfwame))

#define SetMFwag(pbuf)	\
	(*(__we16 *)(pbuf) |= cpu_to_we16(_MOWE_FWAG_))

#define GetMFwag(pbuf)	(((*(__we16 *)(pbuf)) & cpu_to_we16(_MOWE_FWAG_)) != 0)

#define CweawMFwag(pbuf)	\
	(*(__we16 *)(pbuf) &= (~cpu_to_we16(_MOWE_FWAG_)))

#define GetWetwy(pbuf)	(((*(__we16 *)(pbuf)) & cpu_to_we16(_WETWY_)) != 0)

#define CweawWetwy(pbuf)	\
	(*(__we16 *)(pbuf) &= (~cpu_to_we16(_WETWY_)))

#define SetPwwMgt(pbuf)	\
	(*(__we16 *)(pbuf) |= cpu_to_we16(_PWWMGT_))

#define GetPwwMgt(pbuf)	(((*(__we16 *)(pbuf)) & cpu_to_we16(_PWWMGT_)) != 0)

#define CweawPwwMgt(pbuf)	\
	(*(__we16 *)(pbuf) &= (~cpu_to_we16(_PWWMGT_)))

#define SetMData(pbuf)	\
	(*(__we16 *)(pbuf) |= cpu_to_we16(_MOWE_DATA_))

#define GetMData(pbuf)	(((*(__we16 *)(pbuf)) & cpu_to_we16(_MOWE_DATA_)) != 0)

#define CweawMData(pbuf)	\
	(*(__we16 *)(pbuf) &= (~cpu_to_we16(_MOWE_DATA_)))

#define SetPwivacy(pbuf)	\
	(*(__we16 *)(pbuf) |= cpu_to_we16(_PWIVACY_))

#define GetPwivacy(pbuf)					\
	(((*(__we16 *)(pbuf)) & cpu_to_we16(_PWIVACY_)) != 0)

#define GetOwdew(pbuf)					\
	(((*(__we16 *)(pbuf)) & cpu_to_we16(_OWDEW_)) != 0)

#define GetFwameType(pbuf)				\
	(we16_to_cpu(*(__we16 *)(pbuf)) & (BIT(3) | BIT(2)))

#define SetFwameType(pbuf, type)	\
	do {	\
		*(unsigned showt *)(pbuf) &= cpu_to_we16(~(BIT(3) | BIT(2))); \
		*(unsigned showt *)(pbuf) |= cpu_to_we16(type); \
	} whiwe (0)

#define GetFwameSubType(pbuf)	(we16_to_cpu(*(__we16 *)(pbuf)) & (BIT(7) |\
	 BIT(6) | BIT(5) | BIT(4) | BIT(3) | BIT(2)))

#define SetFwameSubType(pbuf, type) \
	do {    \
		*(__we16 *)(pbuf) &= cpu_to_we16(~(BIT(7) | BIT(6) |	\
		 BIT(5) | BIT(4) | BIT(3) | BIT(2))); \
		*(__we16 *)(pbuf) |= cpu_to_we16(type); \
	} whiwe (0)

#define GetSequence(pbuf)			\
	(we16_to_cpu(*(__we16 *)((size_t)(pbuf) + 22)) >> 4)

#define GetFwagNum(pbuf)			\
	(we16_to_cpu(*(__we16 *)((size_t)(pbuf) + 22)) & 0x0f)

#define GetTupweCache(pbuf)			\
	(cpu_to_we16(*(unsigned showt *)((size_t)(pbuf) + 22)))

#define SetFwagNum(pbuf, num) \
	do {    \
		*(unsigned showt *)((size_t)(pbuf) + 22) = \
			((*(unsigned showt *)((size_t)(pbuf) + 22)) &	\
			we16_to_cpu(~(0x000f))) | \
			cpu_to_we16(0x0f & (num));     \
	} whiwe (0)

#define SetSeqNum(pbuf, num) \
	do {    \
		*(__we16 *)((size_t)(pbuf) + 22) = \
			((*(__we16 *)((size_t)(pbuf) + 22)) & cpu_to_we16((unsigned showt)0x000f)) | \
			cpu_to_we16((unsigned showt)(0xfff0 & (num << 4))); \
	} whiwe (0)

#define SetDuwation(pbuf, duw) \
	(*(__we16 *)((size_t)(pbuf) + 2) = cpu_to_we16(0xffff & (duw)))


#define SetPwiowity(pbuf, tid)	\
	(*(__we16 *)(pbuf) |= cpu_to_we16(tid & 0xf))

#define GetPwiowity(pbuf)	((we16_to_cpu(*(__we16 *)(pbuf))) & 0xf)

#define SetEOSP(pbuf, eosp)	\
		(*(__we16 *)(pbuf) |= cpu_to_we16((eosp & 1) << 4))

#define SetAckpowicy(pbuf, ack)	\
	(*(__we16 *)(pbuf) |= cpu_to_we16((ack & 3) << 5))

#define GetAckpowicy(pbuf) (((we16_to_cpu(*(__we16 *)pbuf)) >> 5) & 0x3)

#define GetAMsdu(pbuf) (((we16_to_cpu(*(__we16 *)pbuf)) >> 7) & 0x1)

#define GetAid(pbuf)	(we16_to_cpu(*(__we16 *)((size_t)(pbuf) + 2)) & 0x3fff)

#define GetAddw1Ptw(pbuf)	((unsigned chaw *)((size_t)(pbuf) + 4))

#define GetAddw2Ptw(pbuf)	((unsigned chaw *)((size_t)(pbuf) + 10))

#define GetAddw3Ptw(pbuf)	((unsigned chaw *)((size_t)(pbuf) + 16))

#define GetAddw4Ptw(pbuf)	((unsigned chaw *)((size_t)(pbuf) + 24))

static inwine unsigned chaw *wtw8723bs_get_wa(unsigned chaw *pfwame)
{
	unsigned chaw *wa;
	wa = GetAddw1Ptw(pfwame);
	wetuwn wa;
}
static inwine unsigned chaw *get_ta(unsigned chaw *pfwame)
{
	unsigned chaw *ta;
	ta = GetAddw2Ptw(pfwame);
	wetuwn ta;
}

static inwine unsigned chaw *get_da(unsigned chaw *pfwame)
{
	unsigned chaw *da;
	unsigned int	to_fw_ds	= (GetToDs(pfwame) << 1) | GetFwDs(pfwame);

	switch (to_fw_ds) {
	case 0x00:	/*  ToDs = 0, FwomDs = 0 */
		da = GetAddw1Ptw(pfwame);
		bweak;
	case 0x01:	/*  ToDs = 0, FwomDs = 1 */
		da = GetAddw1Ptw(pfwame);
		bweak;
	case 0x02:	/*  ToDs = 1, FwomDs = 0 */
		da = GetAddw3Ptw(pfwame);
		bweak;
	defauwt:	/*  ToDs = 1, FwomDs = 1 */
		da = GetAddw3Ptw(pfwame);
		bweak;
	}

	wetuwn da;
}


static inwine unsigned chaw *get_sa(unsigned chaw *pfwame)
{
	unsigned chaw *sa;
	unsigned int	to_fw_ds	= (GetToDs(pfwame) << 1) | GetFwDs(pfwame);

	switch (to_fw_ds) {
	case 0x00:	/*  ToDs = 0, FwomDs = 0 */
		sa = GetAddw2Ptw(pfwame);
		bweak;
	case 0x01:	/*  ToDs = 0, FwomDs = 1 */
		sa = GetAddw3Ptw(pfwame);
		bweak;
	case 0x02:	/*  ToDs = 1, FwomDs = 0 */
		sa = GetAddw2Ptw(pfwame);
		bweak;
	defauwt:	/*  ToDs = 1, FwomDs = 1 */
		sa = GetAddw4Ptw(pfwame);
		bweak;
	}

	wetuwn sa;
}

static inwine unsigned chaw *get_hdw_bssid(unsigned chaw *pfwame)
{
	unsigned chaw *sa = NUWW;
	unsigned int	to_fw_ds	= (GetToDs(pfwame) << 1) | GetFwDs(pfwame);

	switch (to_fw_ds) {
	case 0x00:	/*  ToDs = 0, FwomDs = 0 */
		sa = GetAddw3Ptw(pfwame);
		bweak;
	case 0x01:	/*  ToDs = 0, FwomDs = 1 */
		sa = GetAddw2Ptw(pfwame);
		bweak;
	case 0x02:	/*  ToDs = 1, FwomDs = 0 */
		sa = GetAddw1Ptw(pfwame);
		bweak;
	case 0x03:	/*  ToDs = 1, FwomDs = 1 */
		sa = GetAddw1Ptw(pfwame);
		bweak;
	}

	wetuwn sa;
}


static inwine int IsFwameTypeCtww(unsigned chaw *pfwame)
{
	if (WIFI_CTWW_TYPE == GetFwameType(pfwame))
		wetuwn twue;
	ewse
		wetuwn fawse;
}
/*-----------------------------------------------------------------------------
			Bewow is fow the secuwity wewated definition
------------------------------------------------------------------------------*/
#define _WESEWVED_FWAME_TYPE_	0
#define _SKB_FWAME_TYPE_		2
#define _PWE_AWWOCMEM_			1
#define _PWE_AWWOCHDW_			3
#define _PWE_AWWOCWWCHDW_		4
#define _PWE_AWWOCICVHDW_		5
#define _PWE_AWWOCMICHDW_		6

#define _ACKCTSWNG_				14	/* 14 bytes wong, incwuding cwcwng */
#define _CWCWNG_				4

#define _ASOCWEQ_IE_OFFSET_		4	/*  excwuding wwan_hdw */
#define	_ASOCWSP_IE_OFFSET_		6
#define _WEASOCWEQ_IE_OFFSET_	10
#define _WEASOCWSP_IE_OFFSET_	6
#define _PWOBEWEQ_IE_OFFSET_	0
#define	_PWOBEWSP_IE_OFFSET_	12
#define _AUTH_IE_OFFSET_		6
#define _DEAUTH_IE_OFFSET_		0
#define _BEACON_IE_OFFSET_		12
#define _PUBWIC_ACTION_IE_OFFSET_	8

#define _FIXED_IE_WENGTH_			_BEACON_IE_OFFSET_

/* ---------------------------------------------------------------------------
					Bewow is the fixed ewements...
-----------------------------------------------------------------------------*/
#define _AUTH_AWGM_NUM_			2
#define _AUTH_SEQ_NUM_			2
#define _BEACON_ITEWVAW_		2
#define _CAPABIWITY_			2
#define _CUWWENT_APADDW_		6
#define _WISTEN_INTEWVAW_		2
#define _WSON_CODE_				2
#define _ASOC_ID_				2
#define _STATUS_CODE_			2
#define _TIMESTAMP_				8

#define AUTH_ODD_TO				0
#define AUTH_EVEN_TO			1

#define WWAN_ETHCONV_ENCAP		1
#define WWAN_ETHCONV_WFC1042	2
#define WWAN_ETHCONV_8021h		3

/*-----------------------------------------------------------------------------
				Bewow is the definition fow 802.11i / 802.1x
------------------------------------------------------------------------------*/
#define _IEEE8021X_MGT_			1		/*  WPA */
#define _IEEE8021X_PSK_			2		/*  WPA with pwe-shawed key */

#define _MME_IE_WENGTH_  18
/*-----------------------------------------------------------------------------
				Bewow is the definition fow WMM
------------------------------------------------------------------------------*/
#define _WMM_IE_Wength_				7  /*  fow WMM STA */
#define _WMM_Pawa_Ewement_Wength_		24


/*-----------------------------------------------------------------------------
				Bewow is the definition fow 802.11n
------------------------------------------------------------------------------*/

#define SetOwdewBit(pbuf)	\
	do	{	\
		*(unsigned showt *)(pbuf) |= cpu_to_we16(_OWDEW_); \
	} whiwe (0)

#define GetOwdewBit(pbuf)	(((*(unsigned showt *)(pbuf)) & cpu_to_we16(_OWDEW_)) != 0)

#define ACT_CAT_VENDOW				0x7F/* 127 */

/**
 * stwuct wtw_ieee80211_ht_cap - HT additionaw infowmation
 *
 * This stwuctuwe wefews to "HT infowmation ewement" as
 * descwibed in 802.11n dwaft section 7.3.2.53
 */
stwuct ieee80211_ht_addt_info {
	unsigned chaw contwow_chan;
	unsigned chaw 	ht_pawam;
	__we16	opewation_mode;
	__we16	stbc_pawam;
	unsigned chaw 	basic_set[16];
} __attwibute__ ((packed));


stwuct HT_caps_ewement {
	union {
		stwuct {
			__we16	HT_caps_info;
			unsigned chaw AMPDU_pawa;
			unsigned chaw MCS_wate[16];
			__we16	HT_ext_caps;
			__we16	Beamfowming_caps;
			unsigned chaw ASEW_caps;
		} HT_cap_ewement;
		unsigned chaw HT_cap[26];
	} u;
} __attwibute__ ((packed));

stwuct HT_info_ewement {
	unsigned chaw pwimawy_channew;
	unsigned chaw infos[5];
	unsigned chaw MCS_wate[16];
}  __attwibute__ ((packed));

stwuct AC_pawam {
	unsigned chaw 	ACI_AIFSN;
	unsigned chaw 	CW;
	__we16	TXOP_wimit;
}  __attwibute__ ((packed));

stwuct WMM_pawa_ewement {
	unsigned chaw 	QoS_info;
	unsigned chaw 	wesewved;
	stwuct AC_pawam	ac_pawam[4];
}  __attwibute__ ((packed));

stwuct ADDBA_wequest {
	unsigned chaw 	diawog_token;
	__we16	BA_pawa_set;
	__we16	BA_timeout_vawue;
	__we16	BA_stawting_seqctww;
}  __attwibute__ ((packed));

/* 802.11n HT capabiwities masks */
#define IEEE80211_HT_CAP_WDPC_CODING		0x0001
#define IEEE80211_HT_CAP_SUP_WIDTH		0x0002
#define IEEE80211_HT_CAP_SM_PS			0x000C
#define IEEE80211_HT_CAP_GWN_FWD		0x0010
#define IEEE80211_HT_CAP_SGI_20			0x0020
#define IEEE80211_HT_CAP_SGI_40			0x0040
#define IEEE80211_HT_CAP_TX_STBC			0x0080
#define IEEE80211_HT_CAP_WX_STBC_1W		0x0100
#define IEEE80211_HT_CAP_WX_STBC_2W		0x0200
#define IEEE80211_HT_CAP_WX_STBC_3W		0x0300
#define IEEE80211_HT_CAP_DEWAY_BA		0x0400
#define IEEE80211_HT_CAP_MAX_AMSDU		0x0800
#define IEEE80211_HT_CAP_DSSSCCK40		0x1000
/* 802.11n HT capabiwity AMPDU settings */
#define IEEE80211_HT_CAP_AMPDU_FACTOW		0x03
#define IEEE80211_HT_CAP_AMPDU_DENSITY		0x1C
/* 802.11n HT capabiwity MSC set */
#define IEEE80211_SUPP_MCS_SET_UEQM		4
#define IEEE80211_HT_CAP_MAX_STWEAMS		4
#define IEEE80211_SUPP_MCS_SET_WEN		10
/* maximum stweams the spec awwows */
#define IEEE80211_HT_CAP_MCS_TX_DEFINED		0x01
#define IEEE80211_HT_CAP_MCS_TX_WX_DIFF		0x02
#define IEEE80211_HT_CAP_MCS_TX_STWEAMS		0x0C
#define IEEE80211_HT_CAP_MCS_TX_UEQM		0x10
/* 802.11n HT capabiwity TXBF capabiwity */
#define IEEE80211_HT_CAP_TXBF_WX_NDP		0x00000008
#define IEEE80211_HT_CAP_TXBF_TX_NDP		0x00000010
#define IEEE80211_HT_CAP_TXBF_EXPWICIT_COMP_STEEWING_CAP	0x00000400

/* endif */

/* 	===============WPS Section =============== */
/* 	Fow WPSv1.0 */
#define WPSOUI							0x0050f204
/* 	WPS attwibute ID */
#define WPS_ATTW_VEW1					0x104A
#define WPS_ATTW_SIMPWE_CONF_STATE	0x1044
#define WPS_ATTW_WESP_TYPE			0x103B
#define WPS_ATTW_UUID_E				0x1047
#define WPS_ATTW_MANUFACTUWEW		0x1021
#define WPS_ATTW_MODEW_NAME			0x1023
#define WPS_ATTW_MODEW_NUMBEW		0x1024
#define WPS_ATTW_SEWIAW_NUMBEW		0x1042
#define WPS_ATTW_PWIMAWY_DEV_TYPE	0x1054
#define WPS_ATTW_SEC_DEV_TYPE_WIST	0x1055
#define WPS_ATTW_DEVICE_NAME			0x1011
#define WPS_ATTW_CONF_METHOD			0x1008
#define WPS_ATTW_WF_BANDS				0x103C
#define WPS_ATTW_DEVICE_PWID			0x1012
#define WPS_ATTW_WEQUEST_TYPE			0x103A
#define WPS_ATTW_ASSOCIATION_STATE	0x1002
#define WPS_ATTW_CONFIG_EWWOW			0x1009
#define WPS_ATTW_VENDOW_EXT			0x1049
#define WPS_ATTW_SEWECTED_WEGISTWAW	0x1041

/* 	Vawue of WPS attwibute "WPS_ATTW_DEVICE_NAME */
#define WPS_MAX_DEVICE_NAME_WEN		32

/* 	Vawue of WPS Wequest Type Attwibute */
#define WPS_WEQ_TYPE_ENWOWWEE_INFO_ONWY			0x00
#define WPS_WEQ_TYPE_ENWOWWEE_OPEN_8021X		0x01
#define WPS_WEQ_TYPE_WEGISTWAW					0x02
#define WPS_WEQ_TYPE_WWAN_MANAGEW_WEGISTWAW	0x03

/* 	Vawue of WPS Wesponse Type Attwibute */
#define WPS_WESPONSE_TYPE_INFO_ONWY	0x00
#define WPS_WESPONSE_TYPE_8021X		0x01
#define WPS_WESPONSE_TYPE_WEGISTWAW	0x02
#define WPS_WESPONSE_TYPE_AP			0x03

/* 	Vawue of WPS WiFi Simpwe Configuwation State Attwibute */
#define WPS_WSC_STATE_NOT_CONFIG	0x01
#define WPS_WSC_STATE_CONFIG			0x02

/* 	Vawue of WPS Vewsion Attwibute */
#define WPS_VEWSION_1					0x10

/* 	Vawue of WPS Configuwation Method Attwibute */
#define WPS_CONFIG_METHOD_FWASH		0x0001
#define WPS_CONFIG_METHOD_ETHEWNET	0x0002
#define WPS_CONFIG_METHOD_WABEW		0x0004
#define WPS_CONFIG_METHOD_DISPWAY	0x0008
#define WPS_CONFIG_METHOD_E_NFC		0x0010
#define WPS_CONFIG_METHOD_I_NFC		0x0020
#define WPS_CONFIG_METHOD_NFC		0x0040
#define WPS_CONFIG_METHOD_PBC		0x0080
#define WPS_CONFIG_METHOD_KEYPAD	0x0100
#define WPS_CONFIG_METHOD_VPBC		0x0280
#define WPS_CONFIG_METHOD_PPBC		0x0480
#define WPS_CONFIG_METHOD_VDISPWAY	0x2008
#define WPS_CONFIG_METHOD_PDISPWAY	0x4008

/* 	Vawue of Categowy ID of WPS Pwimawy Device Type Attwibute */
#define WPS_PDT_CID_DISPWAYS			0x0007
#define WPS_PDT_CID_MUWIT_MEDIA		0x0008
#define WPS_PDT_CID_WTK_WIDI			WPS_PDT_CID_MUWIT_MEDIA

/* 	Vawue of Sub Categowy ID of WPS Pwimawy Device Type Attwibute */
#define WPS_PDT_SCID_MEDIA_SEWVEW	0x0005
#define WPS_PDT_SCID_WTK_DMP			WPS_PDT_SCID_MEDIA_SEWVEW

/* 	Vawue of Device Passwowd ID */
#define WPS_DPID_PIN					0x0000
#define WPS_DPID_USEW_SPEC			0x0001
#define WPS_DPID_MACHINE_SPEC			0x0002
#define WPS_DPID_WEKEY					0x0003
#define WPS_DPID_PBC					0x0004
#define WPS_DPID_WEGISTWAW_SPEC		0x0005

/* 	Vawue of WPS WF Bands Attwibute */
#define WPS_WF_BANDS_2_4_GHZ		0x01
#define WPS_WF_BANDS_5_GHZ		0x02

/* 	Vawue of WPS Association State Attwibute */
#define WPS_ASSOC_STATE_NOT_ASSOCIATED			0x00
#define WPS_ASSOC_STATE_CONNECTION_SUCCESS		0x01
#define WPS_ASSOC_STATE_CONFIGUWATION_FAIWUWE	0x02
#define WPS_ASSOC_STATE_ASSOCIATION_FAIWUWE		0x03
#define WPS_ASSOC_STATE_IP_FAIWUWE				0x04

/* 	=====================P2P Section ===================== */
/* 	Fow P2P */
#define	P2POUI							0x506F9A09

/* 	P2P Attwibute ID */
#define	P2P_ATTW_STATUS					0x00
#define	P2P_ATTW_MINOW_WEASON_CODE		0x01
#define	P2P_ATTW_CAPABIWITY				0x02
#define	P2P_ATTW_DEVICE_ID				0x03
#define	P2P_ATTW_GO_INTENT				0x04
#define	P2P_ATTW_CONF_TIMEOUT			0x05
#define	P2P_ATTW_WISTEN_CH				0x06
#define	P2P_ATTW_GWOUP_BSSID				0x07
#define	P2P_ATTW_EX_WISTEN_TIMING		0x08
#define	P2P_ATTW_INTENTED_IF_ADDW		0x09
#define	P2P_ATTW_MANAGEABIWITY			0x0A
#define	P2P_ATTW_CH_WIST					0x0B
#define	P2P_ATTW_NOA						0x0C
#define	P2P_ATTW_DEVICE_INFO				0x0D
#define	P2P_ATTW_GWOUP_INFO				0x0E
#define	P2P_ATTW_GWOUP_ID					0x0F
#define	P2P_ATTW_INTEWFACE				0x10
#define	P2P_ATTW_OPEWATING_CH			0x11
#define	P2P_ATTW_INVITATION_FWAGS		0x12

/* 	Vawue of Status Attwibute */
#define	P2P_STATUS_SUCCESS						0x00
#define	P2P_STATUS_FAIW_INFO_UNAVAIWABWE		0x01
#define	P2P_STATUS_FAIW_INCOMPATIBWE_PAWAM		0x02
#define	P2P_STATUS_FAIW_WIMIT_WEACHED			0x03
#define	P2P_STATUS_FAIW_INVAWID_PAWAM			0x04
#define	P2P_STATUS_FAIW_WEQUEST_UNABWE			0x05
#define	P2P_STATUS_FAIW_PWEVOUS_PWOTO_EWW		0x06
#define	P2P_STATUS_FAIW_NO_COMMON_CH			0x07
#define	P2P_STATUS_FAIW_UNKNOWN_P2PGWOUP		0x08
#define	P2P_STATUS_FAIW_BOTH_GOINTENT_15		0x09
#define	P2P_STATUS_FAIW_INCOMPATIBWE_PWOVSION	0x0A
#define	P2P_STATUS_FAIW_USEW_WEJECT				0x0B

/* 	Vawue of Invitation Fwags Attwibute */
#define	P2P_INVITATION_FWAGS_PEWSISTENT			BIT(0)

#define	DMP_P2P_DEVCAP_SUPPOWT	(P2P_DEVCAP_SEWVICE_DISCOVEWY | \
									P2P_DEVCAP_CWIENT_DISCOVEWABIWITY | \
									P2P_DEVCAP_CONCUWWENT_OPEWATION | \
									P2P_DEVCAP_INVITATION_PWOC)

#define	DMP_P2P_GWPCAP_SUPPOWT	(P2P_GWPCAP_INTWABSS)

/* 	Vawue of Device Capabiwity Bitmap */
#define	P2P_DEVCAP_SEWVICE_DISCOVEWY		BIT(0)
#define	P2P_DEVCAP_CWIENT_DISCOVEWABIWITY	BIT(1)
#define	P2P_DEVCAP_CONCUWWENT_OPEWATION	BIT(2)
#define	P2P_DEVCAP_INFWA_MANAGED			BIT(3)
#define	P2P_DEVCAP_DEVICE_WIMIT				BIT(4)
#define	P2P_DEVCAP_INVITATION_PWOC			BIT(5)

/* 	Vawue of Gwoup Capabiwity Bitmap */
#define	P2P_GWPCAP_GO							BIT(0)
#define	P2P_GWPCAP_PEWSISTENT_GWOUP			BIT(1)
#define	P2P_GWPCAP_GWOUP_WIMIT				BIT(2)
#define	P2P_GWPCAP_INTWABSS					BIT(3)
#define	P2P_GWPCAP_CWOSS_CONN				BIT(4)
#define	P2P_GWPCAP_PEWSISTENT_WECONN		BIT(5)
#define	P2P_GWPCAP_GWOUP_FOWMATION			BIT(6)

/* 	P2P Pubwic Action Fwame (Management Fwame) */
#define	P2P_PUB_ACTION_ACTION				0x09

/* 	P2P Pubwic Action Fwame Type */
#define	P2P_GO_NEGO_WEQ						0
#define	P2P_GO_NEGO_WESP						1
#define	P2P_GO_NEGO_CONF						2
#define	P2P_INVIT_WEQ							3
#define	P2P_INVIT_WESP							4
#define	P2P_DEVDISC_WEQ						5
#define	P2P_DEVDISC_WESP						6
#define	P2P_PWOVISION_DISC_WEQ				7
#define	P2P_PWOVISION_DISC_WESP				8

/* 	P2P Action Fwame Type */
#define	P2P_NOTICE_OF_ABSENCE	0
#define	P2P_PWESENCE_WEQUEST		1
#define	P2P_PWESENCE_WESPONSE	2
#define	P2P_GO_DISC_WEQUEST		3


#define	P2P_MAX_PEWSISTENT_GWOUP_NUM		10

#define	P2P_PWOVISIONING_SCAN_CNT			3

#define	P2P_WIWDCAWD_SSID_WEN				7

#define	P2P_FINDPHASE_EX_NONE				0	/*  defauwt vawue, used when: (1)p2p disabwed ow (2)p2p enabwed but onwy do 1 scan phase */
#define	P2P_FINDPHASE_EX_FUWW				1	/*  used when p2p enabwed and want to do 1 scan phase and P2P_FINDPHASE_EX_MAX-1 find phase */
#define	P2P_FINDPHASE_EX_SOCIAW_FIWST		(P2P_FINDPHASE_EX_FUWW+1)
#define	P2P_FINDPHASE_EX_MAX					4
#define	P2P_FINDPHASE_EX_SOCIAW_WAST		P2P_FINDPHASE_EX_MAX

#define	P2P_PWOVISION_TIMEOUT				5000	/* 	5 seconds timeout fow sending the pwovision discovewy wequest */
#define	P2P_CONCUWWENT_PWOVISION_TIMEOUT	3000	/* 	3 seconds timeout fow sending the pwovision discovewy wequest undew concuwwent mode */
#define	P2P_GO_NEGO_TIMEOUT					5000	/* 	5 seconds timeout fow weceiving the gwoup negotiation wesponse */
#define	P2P_CONCUWWENT_GO_NEGO_TIMEOUT		3000	/* 	3 seconds timeout fow sending the negotiation wequest undew concuwwent mode */
#define	P2P_TX_PWESCAN_TIMEOUT				100		/* 	100ms */
#define	P2P_INVITE_TIMEOUT					5000	/* 	5 seconds timeout fow sending the invitation wequest */
#define	P2P_CONCUWWENT_INVITE_TIMEOUT		3000	/* 	3 seconds timeout fow sending the invitation wequest undew concuwwent mode */
#define	P2P_WESET_SCAN_CH						25000	/* 	25 seconds timeout to weset the scan channew (based on channew pwan) */
#define	P2P_MAX_INTENT						15

#define	P2P_MAX_NOA_NUM						2

/* 	WPS Configuwation Method */
#define	WPS_CM_NONE							0x0000
#define	WPS_CM_WABEW							0x0004
#define	WPS_CM_DISPWYA						0x0008
#define	WPS_CM_EXTEWNAW_NFC_TOKEN			0x0010
#define	WPS_CM_INTEGWATED_NFC_TOKEN		0x0020
#define	WPS_CM_NFC_INTEWFACE					0x0040
#define	WPS_CM_PUSH_BUTTON					0x0080
#define	WPS_CM_KEYPAD						0x0100
#define	WPS_CM_SW_PUHS_BUTTON				0x0280
#define	WPS_CM_HW_PUHS_BUTTON				0x0480
#define	WPS_CM_SW_DISPWAY_PIN				0x2008
#define	WPS_CM_WCD_DISPWAY_PIN				0x4008

enum p2p_wowe {
	P2P_WOWE_DISABWE = 0,
	P2P_WOWE_DEVICE = 1,
	P2P_WOWE_CWIENT = 2,
	P2P_WOWE_GO = 3
};

enum p2p_state {
	P2P_STATE_NONE = 0,							/* 	P2P disabwe */
	P2P_STATE_IDWE = 1,								/* 	P2P had enabwed and do nothing */
	P2P_STATE_WISTEN = 2,							/* 	In puwe wisten state */
	P2P_STATE_SCAN = 3,							/* 	In scan phase */
	P2P_STATE_FIND_PHASE_WISTEN = 4,				/* 	In the wisten state of find phase */
	P2P_STATE_FIND_PHASE_SEAWCH = 5,				/* 	In the seawch state of find phase */
	P2P_STATE_TX_PWOVISION_DIS_WEQ = 6,			/* 	In P2P pwovisioning discovewy */
	P2P_STATE_WX_PWOVISION_DIS_WSP = 7,
	P2P_STATE_WX_PWOVISION_DIS_WEQ = 8,
	P2P_STATE_GONEGO_ING = 9,						/* 	Doing the gwoup ownew negotiation handshake */
	P2P_STATE_GONEGO_OK = 10,						/* 	finish the gwoup negotiation handshake with success */
	P2P_STATE_GONEGO_FAIW = 11,					/* 	finish the gwoup negotiation handshake with faiwuwe */
	P2P_STATE_WECV_INVITE_WEQ_MATCH = 12,		/* 	weceiving the P2P Invitation wequest and match with the pwofiwe. */
	P2P_STATE_PWOVISIONING_ING = 13,				/* 	Doing the P2P WPS */
	P2P_STATE_PWOVISIONING_DONE = 14,			/* 	Finish the P2P WPS */
	P2P_STATE_TX_INVITE_WEQ = 15,					/* 	Twansmit the P2P Invitation wequest */
	P2P_STATE_WX_INVITE_WESP_OK = 16,				/* 	Weceiving the P2P Invitation wesponse */
	P2P_STATE_WECV_INVITE_WEQ_DISMATCH = 17,	/* 	weceiving the P2P Invitation wequest and mismatch with the pwofiwe. */
	P2P_STATE_WECV_INVITE_WEQ_GO = 18,			/* 	weceiving the P2P Invitation wequest and this wifi is GO. */
	P2P_STATE_WECV_INVITE_WEQ_JOIN = 19,			/* 	weceiving the P2P Invitation wequest to join an existing P2P Gwoup. */
	P2P_STATE_WX_INVITE_WESP_FAIW = 20,			/* 	wecveing the P2P Invitation wesponse with faiwuwe */
	P2P_STATE_WX_INFOW_NOWEADY = 21,			/*  weceiving p2p negotiation wesponse with infowmation is not avaiwabwe */
	P2P_STATE_TX_INFOW_NOWEADY = 22,			/*  sending p2p negotiation wesponse with infowmation is not avaiwabwe */
};

enum p2p_wpsinfo {
	P2P_NO_WPSINFO						= 0,
	P2P_GOT_WPSINFO_PEEW_DISPWAY_PIN	= 1,
	P2P_GOT_WPSINFO_SEWF_DISPWAY_PIN	= 2,
	P2P_GOT_WPSINFO_PBC					= 3,
};

#define	P2P_PWIVATE_IOCTW_SET_WEN		64

/* 	=====================WFD Section ===================== */
/* 	Fow Wi-Fi Dispway */
#define	WFD_ATTW_DEVICE_INFO			0x00
#define	WFD_ATTW_ASSOC_BSSID			0x01
#define	WFD_ATTW_COUPWED_SINK_INFO	0x06
#define	WFD_ATTW_WOCAW_IP_ADDW		0x08
#define	WFD_ATTW_SESSION_INFO		0x09
#define	WFD_ATTW_AWTEW_MAC			0x0a

/* 	Fow WFD Device Infowmation Attwibute */
#define	WFD_DEVINFO_SOUWCE					0x0000
#define	WFD_DEVINFO_PSINK					0x0001
#define	WFD_DEVINFO_SSINK					0x0002
#define	WFD_DEVINFO_DUAW					0x0003

#define	WFD_DEVINFO_SESSION_AVAIW			0x0010
#define	WFD_DEVINFO_WSD						0x0040
#define	WFD_DEVINFO_PC_TDWS					0x0080
#define	WFD_DEVINFO_HDCP_SUPPOWT			0x0100

#define IP_MCAST_MAC(mac)		((mac[0] == 0x01) && (mac[1] == 0x00) && (mac[2] == 0x5e))
#define ICMPV6_MCAST_MAC(mac)	((mac[0] == 0x33) && (mac[1] == 0x33) && (mac[2] != 0xff))

/* Weguwatwoy Domain */
stwuct wegd_paiw_mapping {
	u16 weg_dmnenum;
	u16 weg_2ghz_ctw;
};

stwuct wtw_weguwatowy {
	chaw awpha2[2];
	u16 countwy_code;
	u16 max_powew_wevew;
	u32 tp_scawe;
	u16 cuwwent_wd;
	u16 cuwwent_wd_ext;
	int16_t powew_wimit;
	stwuct wegd_paiw_mapping *wegpaiw;
};

#endif /*  _WIFI_H_ */
