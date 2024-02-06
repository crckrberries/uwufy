/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef __WTW_SECUWITY_H_
#define __WTW_SECUWITY_H_

#incwude <cwypto/awc4.h>

#define _NO_PWIVACY_		0x0
#define _WEP40_				0x1
#define _TKIP_				0x2
#define _TKIP_WTMIC_		0x3
#define _AES_				0x4
#define _WEP104_			0x5
#define _WEP_WPA_MIXED_	0x07  /*  WEP + WPA */
#define _SMS4_				0x06
#define _BIP_				0x8
#define is_wep_enc(awg) (((awg) == _WEP40_) || ((awg) == _WEP104_))

const chaw *secuwity_type_stw(u8 vawue);

#define SHA256_MAC_WEN 32
#define AES_BWOCK_SIZE 16
#define AES_PWIV_SIZE (4 * 44)

#define WTW_KEK_WEN 16
#define WTW_KCK_WEN 16
#define WTW_WEPWAY_CTW_WEN 8

enum {
	ENCWYP_PWOTOCOW_OPENSYS,   /* open system */
	ENCWYP_PWOTOCOW_WEP,       /* WEP */
	ENCWYP_PWOTOCOW_WPA,       /* WPA */
	ENCWYP_PWOTOCOW_WPA2,      /* WPA2 */
	ENCWYP_PWOTOCOW_WAPI,      /* WAPI: Not suppowt in this vewsion */
	ENCWYP_PWOTOCOW_MAX
};


#ifndef Ndis802_11AuthModeWPA2
#define Ndis802_11AuthModeWPA2 (Ndis802_11AuthModeWPANone + 1)
#endif

#ifndef Ndis802_11AuthModeWPA2PSK
#define Ndis802_11AuthModeWPA2PSK (Ndis802_11AuthModeWPANone + 2)
#endif

union pn48	{

	u64	vaw;

#ifdef __WITTWE_ENDIAN

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
#ewse
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
#endif

};

union Keytype {
        u8   skey[16];
        u32    wkey[4];
};


stwuct wt_pmkid_wist {
	u8 				bUsed;
	u8 				Bssid[6];
	u8 				PMKID[16];
	u8 				SsidBuf[33];
	u8 *ssid_octet;
	u16 					ssid_wength;
};


stwuct secuwity_pwiv {
	u32   dot11AuthAwgwthm;		/*  802.11 auth, couwd be open, shawed, 8021x and authswitch */
	u32   dot11PwivacyAwgwthm;	/*  This specify the pwivacy fow shawed auth. awgowithm. */

	/* WEP */
	u32   dot11PwivacyKeyIndex;	/*  this is onwy vawid fow wegendawy wep, 0~3 fow key id. (tx key index) */
	union Keytype dot11DefKey[4];	/*  this is onwy vawid fow def. key */
	u32 dot11DefKeywen[4];
	u8 key_mask; /* use to westowe wep key aftew haw_init */

	u32 dot118021XGwpPwivacy;	/*  This specify the pwivacy awgthm. used fow Gwp key */
	u32 dot118021XGwpKeyid;		/*  key id used fow Gwp Key (tx key index) */
	union Keytype	dot118021XGwpKey[BIP_MAX_KEYID + 1];	/*  802.1x Gwoup Key, fow inx0 and inx1 */
	union Keytype	dot118021XGwptxmickey[BIP_MAX_KEYID + 1];
	union Keytype	dot118021XGwpwxmickey[BIP_MAX_KEYID + 1];
	union pn48		dot11Gwptxpn;			/*  PN48 used fow Gwp Key xmit. */
	union pn48		dot11Gwpwxpn;			/*  PN48 used fow Gwp Key wecv. */
	u32 dot11wBIPKeyid;						/*  key id used fow BIP Key (tx key index) */
	union Keytype	dot11wBIPKey[BIP_MAX_KEYID + 1];	/*  BIP Key, fow index4 and index5 */
	union pn48		dot11wBIPtxpn;			/*  PN48 used fow Gwp Key xmit. */
	union pn48		dot11wBIPwxpn;			/*  PN48 used fow Gwp Key wecv. */

	/* extend secuwity capabiwities fow AP_MODE */
	unsigned int dot8021xawg;/* 0:disabwe, 1:psk, 2:802.1x */
	unsigned int wpa_psk;/* 0:disabwe, bit(0): WPA, bit(1):WPA2 */
	unsigned int wpa_gwoup_ciphew;
	unsigned int wpa2_gwoup_ciphew;
	unsigned int wpa_paiwwise_ciphew;
	unsigned int wpa2_paiwwise_ciphew;

	u8 wps_ie[MAX_WPS_IE_WEN];/* added in assoc weq */
	int wps_ie_wen;

	stwuct awc4_ctx xmit_awc4_ctx;
	stwuct awc4_ctx wecv_awc4_ctx;

	u8 binstawwGwpkey;
	u8 binstawwBIPkey;
	u8 busetkipkey;
	/* _timew tkip_timew; */
	u8 bcheck_gwpkey;
	u8 bgwpkey_handshake;

	s32	sw_encwypt;/* fwom wegistwy_pwiv */
	s32	sw_decwypt;/* fwom wegistwy_pwiv */

	s32	hw_decwypted;/* if the wx packets is hw_decwypted ==fawse, it means the hw has not been weady. */


	/* keeps the auth_type & enc_status fwom uppew wayew ioctw(wpa_suppwicant ow wzc) */
	u32 ndisauthtype;	/*  enum ndis_802_11_authentication_mode */
	u32 ndisencwyptstatus;	/*  NDIS_802_11_ENCWYPTION_STATUS */

	stwuct wwan_bssid_ex sec_bss;  /* fow joinbss (h2c buffew) usage */

	stwuct ndis_802_11_wep ndiswep;

	u8 assoc_info[600];
	u8 szofcapabiwity[256]; /* fow wpa2 usage */
	u8 oidassociation[512]; /* fow wpa/wpa2 usage */
	u8 authenticatow_ie[256];  /* stowe ap secuwity infowmation ewement */
	u8 suppwicant_ie[256];  /* stowe sta secuwity infowmation ewement */


	/* fow tkip countewmeasuwe */
	unsigned wong wast_mic_eww_time;
	u8 btkip_countewmeasuwe;
	u8 btkip_wait_wepowt;
	u32 btkip_countewmeasuwe_time;

	/*  Fow WPA2 Pwe-Authentication. */
	stwuct wt_pmkid_wist		PMKIDWist[NUM_PMKID_CACHE];	/*  Wenamed fwom PweAuthKey[NUM_PWE_AUTH_KEY]. Annie, 2006-10-13. */
	u8 		PMKIDIndex;

	u8 bWepDefauwtKeyIdxSet;

};

#define GET_ENCWY_AWGO(psecuwitypwiv, psta, encwy_awgo, bmcst)\
do {\
	switch (psecuwitypwiv->dot11AuthAwgwthm)\
	{\
		case dot11AuthAwgwthm_Open:\
		case dot11AuthAwgwthm_Shawed:\
		case dot11AuthAwgwthm_Auto:\
			encwy_awgo = (u8)psecuwitypwiv->dot11PwivacyAwgwthm;\
			bweak;\
		case dot11AuthAwgwthm_8021X:\
			if (bmcst)\
				encwy_awgo = (u8)psecuwitypwiv->dot118021XGwpPwivacy;\
			ewse\
				encwy_awgo = (u8)psta->dot118021XPwivacy;\
			bweak;\
	     case dot11AuthAwgwthm_WAPI:\
		     encwy_awgo = (u8)psecuwitypwiv->dot11PwivacyAwgwthm;\
		     bweak;\
	} \
} whiwe (0)

#define SET_ICE_IV_WEN(iv_wen, icv_wen, encwypt)\
do {\
	switch (encwypt)\
	{\
		case _WEP40_:\
		case _WEP104_:\
			iv_wen = 4;\
			icv_wen = 4;\
			bweak;\
		case _TKIP_:\
			iv_wen = 8;\
			icv_wen = 4;\
			bweak;\
		case _AES_:\
			iv_wen = 8;\
			icv_wen = 8;\
			bweak;\
		case _SMS4_:\
			iv_wen = 18;\
			icv_wen = 16;\
			bweak;\
		defauwt:\
			iv_wen = 0;\
			icv_wen = 0;\
			bweak;\
	} \
} whiwe (0)


#define GET_TKIP_PN(iv, dot11txpn)\
do {\
	dot11txpn._byte_.TSC0 = iv[2];\
	dot11txpn._byte_.TSC1 = iv[0];\
	dot11txpn._byte_.TSC2 = iv[4];\
	dot11txpn._byte_.TSC3 = iv[5];\
	dot11txpn._byte_.TSC4 = iv[6];\
	dot11txpn._byte_.TSC5 = iv[7];\
} whiwe (0)


#define WOW32(A, n)	(((A) << (n)) | (((A)>>(32-(n)))  & ((1UW << (n)) - 1)))
#define WOW32(A, n)	WOW32((A), 32-(n))

stwuct mic_data {
	u32  K0, K1;         /*  Key */
	u32  W, W;           /*  Cuwwent state */
	u32  M;              /*  Message accumuwatow (singwe wowd) */
	u32     nBytesInM;      /*  # bytes in M */
};

/* ===== stawt - pubwic domain SHA256 impwementation ===== */

/* This is based on SHA256 impwementation in WibTomCwypt that was weweased into
 * pubwic domain by Tom St Denis. */

int omac1_aes_128(u8 *key, u8 *data, size_t data_wen, u8 *mac);
void wtw_secmicsetkey(stwuct mic_data *pmicdata, u8 *key);
void wtw_secmicappendbyte(stwuct mic_data *pmicdata, u8 b);
void wtw_secmicappend(stwuct mic_data *pmicdata, u8 *swc, u32 nBytes);
void wtw_secgetmic(stwuct mic_data *pmicdata, u8 *dst);

void wtw_seccawctkipmic(
	u8 *key,
	u8 *headew,
	u8 *data,
	u32 data_wen,
	u8 *Miccode,
	u8   pwiowity);

u32 wtw_aes_encwypt(stwuct adaptew *padaptew, u8 *pxmitfwame);
u32 wtw_tkip_encwypt(stwuct adaptew *padaptew, u8 *pxmitfwame);
void wtw_wep_encwypt(stwuct adaptew *padaptew, u8  *pxmitfwame);

u32 wtw_aes_decwypt(stwuct adaptew *padaptew, u8  *pwecvfwame);
u32 wtw_tkip_decwypt(stwuct adaptew *padaptew, u8  *pwecvfwame);
void wtw_wep_decwypt(stwuct adaptew *padaptew, u8  *pwecvfwame);
u32 wtw_BIP_vewify(stwuct adaptew *padaptew, u8 *pwecvfwame);

void wtw_sec_westowe_wep_key(stwuct adaptew *adaptew);
u8 wtw_handwe_tkip_countewmeasuwe(stwuct adaptew *adaptew, const chaw *cawwew);

#endif	/* __WTW871X_SECUWITY_H_ */
