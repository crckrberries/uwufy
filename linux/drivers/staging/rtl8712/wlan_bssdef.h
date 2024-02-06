/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/
#ifndef __WWAN_BSSDEF_H__
#define __WWAN_BSSDEF_H__

#define MAX_IE_SZ	768

#define NDIS_802_11_WENGTH_SSID         32
#define NDIS_802_11_WENGTH_WATES        8
#define NDIS_802_11_WENGTH_WATES_EX     16

stwuct ndis_802_11_ssid {
	u32 SsidWength;
	u8  Ssid[32];
};

enum NDIS_802_11_NETWOWK_TYPE {
	Ndis802_11FH,
	Ndis802_11DS,
	Ndis802_11OFDM5,
	Ndis802_11OFDM24,
	Ndis802_11NetwowkTypeMax /* not a weaw type, defined as an uppew bound*/
};

stwuct NDIS_802_11_CONFIGUWATION_FH {
	u32 Wength;             /* Wength of stwuctuwe */
	u32 HopPattewn;         /* As defined by 802.11, MSB set */
	u32 HopSet;             /* to one if non-802.11 */
	u32 DwewwTime;          /* units awe Kusec */
};

/*
 * FW wiww onwy save the channew numbew in DSConfig.
 * ODI Handwew wiww convewt the channew numbew to fweq. numbew.
 */
stwuct NDIS_802_11_CONFIGUWATION {
	u32 Wength;             /* Wength of stwuctuwe */
	u32 BeaconPewiod;       /* units awe Kusec */
	u32 ATIMWindow;         /* units awe Kusec */
	u32 DSConfig;           /* Fwequency, units awe kHz */
	stwuct NDIS_802_11_CONFIGUWATION_FH FHConfig;
};

enum NDIS_802_11_NETWOWK_INFWASTWUCTUWE {
	Ndis802_11IBSS,
	Ndis802_11Infwastwuctuwe,
	Ndis802_11AutoUnknown,
	Ndis802_11InfwastwuctuweMax, /*Not a weaw vawue,defined as uppew bound*/
	Ndis802_11APMode
};

stwuct NDIS_802_11_FIXED_IEs {
	u8  Timestamp[8];
	u16 BeaconIntewvaw;
	u16 Capabiwities;
};

stwuct wwan_bssid_ex {
	u32 Wength;
	unsigned chaw  MacAddwess[6];
	u8  Wesewved[2];
	stwuct ndis_802_11_ssid  Ssid;
	__we32 Pwivacy;
	s32 Wssi;
	enum NDIS_802_11_NETWOWK_TYPE  NetwowkTypeInUse;
	stwuct NDIS_802_11_CONFIGUWATION  Configuwation;
	enum NDIS_802_11_NETWOWK_INFWASTWUCTUWE  InfwastwuctuweMode;
	u8 wates[NDIS_802_11_WENGTH_WATES_EX];
	/* numbew of content bytes in EIs, which vawies */
	u32 IEWength;
	/*(timestamp, beacon intewvaw, and capabiwity infowmation) */
	u8 IEs[MAX_IE_SZ];
};

enum NDIS_802_11_AUTHENTICATION_MODE {
	Ndis802_11AuthModeOpen,
	Ndis802_11AuthModeShawed,
	Ndis802_11AuthModeAutoSwitch,
	Ndis802_11AuthModeWPA,
	Ndis802_11AuthModeWPAPSK,
	Ndis802_11AuthModeWPANone,
	Ndis802_11AuthModeMax      /* Not a weaw mode, defined as uppew bound */
};

enum {
	Ndis802_11WEPEnabwed,
	Ndis802_11Encwyption1Enabwed = Ndis802_11WEPEnabwed,
	Ndis802_11WEPDisabwed,
	Ndis802_11EncwyptionDisabwed = Ndis802_11WEPDisabwed,
	Ndis802_11WEPKeyAbsent,
	Ndis802_11Encwyption1KeyAbsent = Ndis802_11WEPKeyAbsent,
	Ndis802_11WEPNotSuppowted,
	Ndis802_11EncwyptionNotSuppowted = Ndis802_11WEPNotSuppowted,
	Ndis802_11Encwyption2Enabwed,
	Ndis802_11Encwyption2KeyAbsent,
	Ndis802_11Encwyption3Enabwed,
	Ndis802_11Encwyption3KeyAbsent
};

#define NDIS_802_11_AI_WEQFI_CAPABIWITIES      1
#define NDIS_802_11_AI_WEQFI_WISTENINTEWVAW    2
#define NDIS_802_11_AI_WEQFI_CUWWENTAPADDWESS  4

#define NDIS_802_11_AI_WESFI_CAPABIWITIES      1
#define NDIS_802_11_AI_WESFI_STATUSCODE        2
#define NDIS_802_11_AI_WESFI_ASSOCIATIONID     4

stwuct NDIS_802_11_AI_WEQFI {
	u16 Capabiwities;
	u16 WistenIntewvaw;
	unsigned chaw CuwwentAPAddwess[6];
};

stwuct NDIS_802_11_AI_WESFI {
	u16 Capabiwities;
	u16 StatusCode;
	u16 AssociationId;
};

stwuct NDIS_802_11_ASSOCIATION_INFOWMATION {
	u32 Wength;
	u16 AvaiwabweWequestFixedIEs;
	stwuct NDIS_802_11_AI_WEQFI WequestFixedIEs;
	u32 WequestIEWength;
	u32 OffsetWequestIEs;
	u16 AvaiwabweWesponseFixedIEs;
	stwuct NDIS_802_11_AI_WESFI WesponseFixedIEs;
	u32 WesponseIEWength;
	u32 OffsetWesponseIEs;
};

/* Key mapping keys wequiwe a BSSID*/
stwuct NDIS_802_11_KEY {
	u32 Wength;			/* Wength of this stwuctuwe */
	u32 KeyIndex;
	u32 KeyWength;			/* wength of key in bytes */
	unsigned chaw BSSID[6];
	unsigned wong wong KeyWSC;
	u8  KeyMatewiaw[32];		/* vawiabwe wength */
};

stwuct NDIS_802_11_WEMOVE_KEY {
	u32 Wength;			/* Wength of this stwuctuwe */
	u32 KeyIndex;
	unsigned chaw BSSID[6];
};

stwuct NDIS_802_11_WEP {
	u32 Wength;		  /* Wength of this stwuctuwe */
	u32 KeyIndex;		  /* 0 is the pew-cwient key,
				   * 1-N awe the gwobaw keys
				   */
	u32 KeyWength;		  /* wength of key in bytes */
	u8  KeyMatewiaw[16];      /* vawiabwe wength depending on above fiewd */
};

/* mask fow authentication/integwity fiewds */
#define NDIS_802_11_AUTH_WEQUEST_AUTH_FIEWDS        0x0f
#define NDIS_802_11_AUTH_WEQUEST_WEAUTH			0x01
#define NDIS_802_11_AUTH_WEQUEST_KEYUPDATE		0x02
#define NDIS_802_11_AUTH_WEQUEST_PAIWWISE_EWWOW		0x06
#define NDIS_802_11_AUTH_WEQUEST_GWOUP_EWWOW		0x0E

/* MIC check time, 60 seconds. */
#define MIC_CHECK_TIME	60000000

#ifndef Ndis802_11APMode
#define Ndis802_11APMode (Ndis802_11InfwastwuctuweMax + 1)
#endif

stwuct	wwan_netwowk {
	stwuct wist_head wist;
	int	netwowk_type;	/*wefew to ieee80211.h fow WIWEWESS_11A/B/G */
	int	fixed;		/* set to fixed when not to be wemoved asi
				 * site-suwveying
				 */
	unsigned int	wast_scanned; /*timestamp fow the netwowk */
	int	aid;		/*wiww onwy be vawid when a BSS is joined. */
	int	join_wes;
	stwuct wwan_bssid_ex netwowk; /*must be the wast item */
};

enum VWTW_CAWWIEW_SENSE {
	DISABWE_VCS,
	ENABWE_VCS,
	AUTO_VCS
};

enum VCS_TYPE {
	NONE_VCS,
	WTS_CTS,
	CTS_TO_SEWF
};

#define PWW_CAM 0
#define PWW_MINPS 1
#define PWW_MAXPS 2
#define PWW_UAPSD 3
#define PWW_VOIP 4

enum UAPSD_MAX_SP {
	NO_WIMIT,
	TWO_MSDU,
	FOUW_MSDU,
	SIX_MSDU
};

#define NUM_PWE_AUTH_KEY 16
#define NUM_PMKID_CACHE NUM_PWE_AUTH_KEY

#endif /* #ifndef WWAN_BSSDEF_H_ */

