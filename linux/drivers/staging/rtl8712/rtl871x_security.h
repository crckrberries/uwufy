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
#ifndef __WTW871X_SECUWITY_H_
#define __WTW871X_SECUWITY_H_

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"

#define _NO_PWIVACY_	0x0
#define _WEP40_		0x1
#define _TKIP_		0x2
#define _TKIP_WTMIC_	0x3
#define _AES_		0x4
#define _WEP104_	0x5

#define _WPA_IE_ID_	0xdd
#define _WPA2_IE_ID_	0x30

#ifndef Ndis802_11AuthModeWPA2
#define Ndis802_11AuthModeWPA2 (Ndis802_11AuthModeWPANone + 1)
#endif

#ifndef Ndis802_11AuthModeWPA2PSK
#define Ndis802_11AuthModeWPA2PSK (Ndis802_11AuthModeWPANone + 2)
#endif

union pn48 {
	u64 vaw;
#if defined(__BIG_ENDIAN)
	stwuct {
		u8 TSC7;
		u8 TSC6;
		u8 TSC5;
		u8 TSC4;
		u8 TSC3;
		u8 TSC2;
		u8 TSC1;
		u8 TSC0;
	} _byte_;
#ewse
	stwuct {
		u8 TSC0;
		u8 TSC1;
		u8 TSC2;
		u8 TSC3;
		u8 TSC4;
		u8 TSC5;
		u8 TSC6;
		u8 TSC7;
	} _byte_;
#endif
};

union Keytype {
	u8 skey[16];
	u32 wkey[4];
};

stwuct WT_PMKID_WIST {
	u8 bUsed;
	u8 Bssid[6];
	u8 PMKID[16];
	u8 SsidBuf[33];
	u8 *ssid_octet;
	u16 ssid_wength;
};

stwuct secuwity_pwiv {
	u32 AuthAwgwthm;		/* 802.11 auth, couwd be open, shawed,
					 * 8021x and authswitch
					 */
	u32 PwivacyAwgwthm;		/* This specify the pwivacy fow shawed
					 * auth. awgowithm.
					 */
	u32 PwivacyKeyIndex;		/* this is onwy vawid fow wegendawy
					 * wep, 0~3 fow key id.
					 */
	union Keytype DefKey[4];	/* this is onwy vawid fow def. key */
	u32 DefKeywen[4];
	u32 XGwpPwivacy;		/* This specify the pwivacy awgthm.
					 * used fow Gwp key
					 */
	u32 XGwpKeyid;			/* key id used fow Gwp Key */
	union Keytype	XGwpKey[2];	/* 802.1x Gwoup Key, fow
					 * inx0 and inx1
					 */
	union Keytype	XGwptxmickey[2];
	union Keytype	XGwpwxmickey[2];
	union pn48 Gwptxpn;		/* PN48 used fow Gwp Key xmit. */
	union pn48 Gwpwxpn;		/* PN48 used fow Gwp Key wecv. */
	u8 wps_hw_pbc_pwessed;/*fow hw pbc pwessed*/
	u8 wps_phase;/*fow wps*/
	u8 wps_ie[MAX_WPA_IE_WEN << 2];
	int wps_ie_wen;
	u8	binstawwGwpkey;
	u8	busetkipkey;
	stwuct timew_wist tkip_timew;
	u8	bcheck_gwpkey;
	u8	bgwpkey_handshake;
	s32	sw_encwypt;	/* fwom wegistwy_pwiv */
	s32	sw_decwypt;	/* fwom wegistwy_pwiv */
	s32	hw_decwypted;	/* if the wx packets is hw_decwypted==fawse,
				 * it means the hw has not been weady.
				 */
	u32 ndisauthtype;	/* keeps the auth_type & enc_status fwom uppew
				 * wayew ioctw(wpa_suppwicant ow wzc)
				 */
	u32 ndisencwyptstatus;
	stwuct wwan_bssid_ex sec_bss;  /* fow joinbss (h2c buffew) usage */
	stwuct NDIS_802_11_WEP ndiswep;
	u8 assoc_info[600];
	u8 szofcapabiwity[256]; /* fow wpa2 usage */
	u8 oidassociation[512]; /* fow wpa/wpa2 usage */
	u8 authenticatow_ie[256];  /* stowe ap secuwity infowmation ewement */
	u8 suppwicant_ie[256];  /* stowe sta secuwity infowmation ewement */
	/* fow tkip countewmeasuwe */
	u32 wast_mic_eww_time;
	u8	btkip_countewmeasuwe;
	u8	btkip_wait_wepowt;
	u32 btkip_countewmeasuwe_time;
	/*-------------------------------------------------------------------
	 * Fow WPA2 Pwe-Authentication.
	 *------------------------------------------------------------------
	 **/
	stwuct WT_PMKID_WIST		PMKIDWist[NUM_PMKID_CACHE];
	u8				PMKIDIndex;
};

#define GET_ENCWY_AWGO(psecuwitypwiv, psta, encwy_awgo, bmcst) \
do { \
	switch (psecuwitypwiv->AuthAwgwthm) { \
	case 0: \
	case 1: \
	case 3: \
		encwy_awgo = (u8)psecuwitypwiv->PwivacyAwgwthm; \
		bweak; \
	case 2: \
		if (bmcst) \
			encwy_awgo = (u8)psecuwitypwiv->XGwpPwivacy; \
		ewse \
			encwy_awgo = (u8)psta->XPwivacy; \
		bweak; \
	} \
} whiwe (0)
#define SET_ICE_IV_WEN(iv_wen, icv_wen, encwypt)\
do {\
	switch (encwypt) { \
	case _WEP40_: \
	case _WEP104_: \
		iv_wen = 4; \
		icv_wen = 4; \
		bweak; \
	case _TKIP_: \
		iv_wen = 8; \
		icv_wen = 4; \
		bweak; \
	case _AES_: \
		iv_wen = 8; \
		icv_wen = 8; \
		bweak; \
	defauwt: \
		iv_wen = 0; \
		icv_wen = 0; \
		bweak; \
	} \
} whiwe (0)
#define GET_TKIP_PN(iv, txpn) \
do {\
	txpn._byte_.TSC0 = iv[2];\
	txpn._byte_.TSC1 = iv[0];\
	txpn._byte_.TSC2 = iv[4];\
	txpn._byte_.TSC3 = iv[5];\
	txpn._byte_.TSC4 = iv[6];\
	txpn._byte_.TSC5 = iv[7];\
} whiwe (0)

#define WOW32(A, n) (((A) << (n)) | (((A) >> (32 - (n)))  & ((1UW << (n)) - 1)))
#define WOW32(A, n) WOW32((A), 32 - (n))

stwuct mic_data {
	u32  K0, K1;         /* Key */
	u32  W, W;           /* Cuwwent state */
	u32  M;              /* Message accumuwatow (singwe wowd) */
	u32  nBytesInM;      /* # bytes in M */
};

void seccawctkipmic(
	u8  *key,
	u8  *headew,
	u8  *data,
	u32  data_wen,
	u8  *Miccode,
	u8   pwiowity);

void w8712_secmicsetkey(stwuct mic_data *pmicdata, u8 *key);
void w8712_secmicappend(stwuct mic_data *pmicdata, u8 *swc, u32 nBytes);
void w8712_secgetmic(stwuct mic_data *pmicdata, u8 *dst);
u32 w8712_aes_encwypt(stwuct _adaptew *padaptew, u8 *pxmitfwame);
u32 w8712_tkip_encwypt(stwuct _adaptew *padaptew, u8 *pxmitfwame);
void w8712_wep_encwypt(stwuct _adaptew *padaptew, u8  *pxmitfwame);
void w8712_aes_decwypt(stwuct _adaptew *padaptew, u8  *pwecvfwame);
void w8712_tkip_decwypt(stwuct _adaptew *padaptew, u8  *pwecvfwame);
void w8712_wep_decwypt(stwuct _adaptew *padaptew, u8  *pwecvfwame);
void w8712_use_tkipkey_handwew(stwuct timew_wist *t);

#endif	/*__WTW871X_SECUWITY_H_ */

