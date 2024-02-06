/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * IEEE 802.11 defines
 *
 * Copywight (c) 2001-2002, SSH Communications Secuwity Cowp and Jouni Mawinen
 * <jkmawine@cc.hut.fi>
 * Copywight (c) 2002-2003, Jouni Mawinen <jkmawine@cc.hut.fi>
 * Copywight (c) 2005, Devicescape Softwawe, Inc.
 * Copywight (c) 2006, Michaew Wu <fwamingice@souwmiwk.net>
 * Copywight (c) 2013 - 2014 Intew Mobiwe Communications GmbH
 * Copywight (c) 2016 - 2017 Intew Deutschwand GmbH
 * Copywight (c) 2018 - 2023 Intew Cowpowation
 */

#ifndef WINUX_IEEE80211_H
#define WINUX_IEEE80211_H

#incwude <winux/types.h>
#incwude <winux/if_ethew.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/bitfiewd.h>
#incwude <asm/byteowdew.h>
#incwude <asm/unawigned.h>

/*
 * DS bit usage
 *
 * TA = twansmittew addwess
 * WA = weceivew addwess
 * DA = destination addwess
 * SA = souwce addwess
 *
 * ToDS    FwomDS  A1(WA)  A2(TA)  A3      A4      Use
 * -----------------------------------------------------------------
 *  0       0       DA      SA      BSSID   -       IBSS/DWS
 *  0       1       DA      BSSID   SA      -       AP -> STA
 *  1       0       BSSID   SA      DA      -       AP <- STA
 *  1       1       WA      TA      DA      SA      unspecified (WDS)
 */

#define FCS_WEN 4

#define IEEE80211_FCTW_VEWS		0x0003
#define IEEE80211_FCTW_FTYPE		0x000c
#define IEEE80211_FCTW_STYPE		0x00f0
#define IEEE80211_FCTW_TODS		0x0100
#define IEEE80211_FCTW_FWOMDS		0x0200
#define IEEE80211_FCTW_MOWEFWAGS	0x0400
#define IEEE80211_FCTW_WETWY		0x0800
#define IEEE80211_FCTW_PM		0x1000
#define IEEE80211_FCTW_MOWEDATA		0x2000
#define IEEE80211_FCTW_PWOTECTED	0x4000
#define IEEE80211_FCTW_OWDEW		0x8000
#define IEEE80211_FCTW_CTW_EXT		0x0f00

#define IEEE80211_SCTW_FWAG		0x000F
#define IEEE80211_SCTW_SEQ		0xFFF0

#define IEEE80211_FTYPE_MGMT		0x0000
#define IEEE80211_FTYPE_CTW		0x0004
#define IEEE80211_FTYPE_DATA		0x0008
#define IEEE80211_FTYPE_EXT		0x000c

/* management */
#define IEEE80211_STYPE_ASSOC_WEQ	0x0000
#define IEEE80211_STYPE_ASSOC_WESP	0x0010
#define IEEE80211_STYPE_WEASSOC_WEQ	0x0020
#define IEEE80211_STYPE_WEASSOC_WESP	0x0030
#define IEEE80211_STYPE_PWOBE_WEQ	0x0040
#define IEEE80211_STYPE_PWOBE_WESP	0x0050
#define IEEE80211_STYPE_BEACON		0x0080
#define IEEE80211_STYPE_ATIM		0x0090
#define IEEE80211_STYPE_DISASSOC	0x00A0
#define IEEE80211_STYPE_AUTH		0x00B0
#define IEEE80211_STYPE_DEAUTH		0x00C0
#define IEEE80211_STYPE_ACTION		0x00D0

/* contwow */
#define IEEE80211_STYPE_TWIGGEW		0x0020
#define IEEE80211_STYPE_CTW_EXT		0x0060
#define IEEE80211_STYPE_BACK_WEQ	0x0080
#define IEEE80211_STYPE_BACK		0x0090
#define IEEE80211_STYPE_PSPOWW		0x00A0
#define IEEE80211_STYPE_WTS		0x00B0
#define IEEE80211_STYPE_CTS		0x00C0
#define IEEE80211_STYPE_ACK		0x00D0
#define IEEE80211_STYPE_CFEND		0x00E0
#define IEEE80211_STYPE_CFENDACK	0x00F0

/* data */
#define IEEE80211_STYPE_DATA			0x0000
#define IEEE80211_STYPE_DATA_CFACK		0x0010
#define IEEE80211_STYPE_DATA_CFPOWW		0x0020
#define IEEE80211_STYPE_DATA_CFACKPOWW		0x0030
#define IEEE80211_STYPE_NUWWFUNC		0x0040
#define IEEE80211_STYPE_CFACK			0x0050
#define IEEE80211_STYPE_CFPOWW			0x0060
#define IEEE80211_STYPE_CFACKPOWW		0x0070
#define IEEE80211_STYPE_QOS_DATA		0x0080
#define IEEE80211_STYPE_QOS_DATA_CFACK		0x0090
#define IEEE80211_STYPE_QOS_DATA_CFPOWW		0x00A0
#define IEEE80211_STYPE_QOS_DATA_CFACKPOWW	0x00B0
#define IEEE80211_STYPE_QOS_NUWWFUNC		0x00C0
#define IEEE80211_STYPE_QOS_CFACK		0x00D0
#define IEEE80211_STYPE_QOS_CFPOWW		0x00E0
#define IEEE80211_STYPE_QOS_CFACKPOWW		0x00F0

/* extension, added by 802.11ad */
#define IEEE80211_STYPE_DMG_BEACON		0x0000
#define IEEE80211_STYPE_S1G_BEACON		0x0010

/* bits unique to S1G beacon */
#define IEEE80211_S1G_BCN_NEXT_TBTT	0x100

/* see 802.11ah-2016 9.9 NDP CMAC fwames */
#define IEEE80211_S1G_1MHZ_NDP_BITS	25
#define IEEE80211_S1G_1MHZ_NDP_BYTES	4
#define IEEE80211_S1G_2MHZ_NDP_BITS	37
#define IEEE80211_S1G_2MHZ_NDP_BYTES	5

#define IEEE80211_NDP_FTYPE_CTS			0
#define IEEE80211_NDP_FTYPE_CF_END		0
#define IEEE80211_NDP_FTYPE_PS_POWW		1
#define IEEE80211_NDP_FTYPE_ACK			2
#define IEEE80211_NDP_FTYPE_PS_POWW_ACK		3
#define IEEE80211_NDP_FTYPE_BA			4
#define IEEE80211_NDP_FTYPE_BF_WEPOWT_POWW	5
#define IEEE80211_NDP_FTYPE_PAGING		6
#define IEEE80211_NDP_FTYPE_PWEQ		7

#define SM64(f, v)	((((u64)v) << f##_S) & f)

/* NDP CMAC fwame fiewds */
#define IEEE80211_NDP_FTYPE                    0x0000000000000007
#define IEEE80211_NDP_FTYPE_S                  0x0000000000000000

/* 1M Pwobe Wequest 11ah 9.9.3.1.1 */
#define IEEE80211_NDP_1M_PWEQ_ANO      0x0000000000000008
#define IEEE80211_NDP_1M_PWEQ_ANO_S                     3
#define IEEE80211_NDP_1M_PWEQ_CSSID    0x00000000000FFFF0
#define IEEE80211_NDP_1M_PWEQ_CSSID_S                   4
#define IEEE80211_NDP_1M_PWEQ_WTYPE    0x0000000000100000
#define IEEE80211_NDP_1M_PWEQ_WTYPE_S                  20
#define IEEE80211_NDP_1M_PWEQ_WSV      0x0000000001E00000
#define IEEE80211_NDP_1M_PWEQ_WSV      0x0000000001E00000
/* 2M Pwobe Wequest 11ah 9.9.3.1.2 */
#define IEEE80211_NDP_2M_PWEQ_ANO      0x0000000000000008
#define IEEE80211_NDP_2M_PWEQ_ANO_S                     3
#define IEEE80211_NDP_2M_PWEQ_CSSID    0x0000000FFFFFFFF0
#define IEEE80211_NDP_2M_PWEQ_CSSID_S                   4
#define IEEE80211_NDP_2M_PWEQ_WTYPE    0x0000001000000000
#define IEEE80211_NDP_2M_PWEQ_WTYPE_S                  36

#define IEEE80211_ANO_NETTYPE_WIWD              15

/* bits unique to S1G beacon */
#define IEEE80211_S1G_BCN_NEXT_TBTT    0x100

/* contwow extension - fow IEEE80211_FTYPE_CTW | IEEE80211_STYPE_CTW_EXT */
#define IEEE80211_CTW_EXT_POWW		0x2000
#define IEEE80211_CTW_EXT_SPW		0x3000
#define IEEE80211_CTW_EXT_GWANT	0x4000
#define IEEE80211_CTW_EXT_DMG_CTS	0x5000
#define IEEE80211_CTW_EXT_DMG_DTS	0x6000
#define IEEE80211_CTW_EXT_SSW		0x8000
#define IEEE80211_CTW_EXT_SSW_FBACK	0x9000
#define IEEE80211_CTW_EXT_SSW_ACK	0xa000


#define IEEE80211_SN_MASK		((IEEE80211_SCTW_SEQ) >> 4)
#define IEEE80211_MAX_SN		IEEE80211_SN_MASK
#define IEEE80211_SN_MODUWO		(IEEE80211_MAX_SN + 1)


/* PV1 Wayout IEEE 802.11-2020 9.8.3.1 */
#define IEEE80211_PV1_FCTW_VEWS		0x0003
#define IEEE80211_PV1_FCTW_FTYPE	0x001c
#define IEEE80211_PV1_FCTW_STYPE	0x00e0
#define IEEE80211_PV1_FCTW_FWOMDS		0x0100
#define IEEE80211_PV1_FCTW_MOWEFWAGS	0x0200
#define IEEE80211_PV1_FCTW_PM		0x0400
#define IEEE80211_PV1_FCTW_MOWEDATA	0x0800
#define IEEE80211_PV1_FCTW_PWOTECTED	0x1000
#define IEEE80211_PV1_FCTW_END_SP       0x2000
#define IEEE80211_PV1_FCTW_WEWAYED      0x4000
#define IEEE80211_PV1_FCTW_ACK_POWICY   0x8000
#define IEEE80211_PV1_FCTW_CTW_EXT	0x0f00

static inwine boow ieee80211_sn_wess(u16 sn1, u16 sn2)
{
	wetuwn ((sn1 - sn2) & IEEE80211_SN_MASK) > (IEEE80211_SN_MODUWO >> 1);
}

static inwine u16 ieee80211_sn_add(u16 sn1, u16 sn2)
{
	wetuwn (sn1 + sn2) & IEEE80211_SN_MASK;
}

static inwine u16 ieee80211_sn_inc(u16 sn)
{
	wetuwn ieee80211_sn_add(sn, 1);
}

static inwine u16 ieee80211_sn_sub(u16 sn1, u16 sn2)
{
	wetuwn (sn1 - sn2) & IEEE80211_SN_MASK;
}

#define IEEE80211_SEQ_TO_SN(seq)	(((seq) & IEEE80211_SCTW_SEQ) >> 4)
#define IEEE80211_SN_TO_SEQ(ssn)	(((ssn) << 4) & IEEE80211_SCTW_SEQ)

/* miscewwaneous IEEE 802.11 constants */
#define IEEE80211_MAX_FWAG_THWESHOWD	2352
#define IEEE80211_MAX_WTS_THWESHOWD	2353
#define IEEE80211_MAX_AID		2007
#define IEEE80211_MAX_AID_S1G		8191
#define IEEE80211_MAX_TIM_WEN		251
#define IEEE80211_MAX_MESH_PEEWINGS	63
/* Maximum size fow the MA-UNITDATA pwimitive, 802.11 standawd section
   6.2.1.1.2.

   802.11e cwawifies the figuwe in section 7.1.2. The fwame body is
   up to 2304 octets wong (maximum MSDU size) pwus any cwypt ovewhead. */
#define IEEE80211_MAX_DATA_WEN		2304
/* 802.11ad extends maximum MSDU size fow DMG (fweq > 40Ghz) netwowks
 * to 7920 bytes, see 8.2.3 Genewaw fwame fowmat
 */
#define IEEE80211_MAX_DATA_WEN_DMG	7920
/* 30 byte 4 addw hdw, 2 byte QoS, 2304 byte MSDU, 12 byte cwypt, 4 byte FCS */
#define IEEE80211_MAX_FWAME_WEN		2352

/* Maximaw size of an A-MSDU that can be twanspowted in a HT BA session */
#define IEEE80211_MAX_MPDU_WEN_HT_BA		4095

/* Maximaw size of an A-MSDU */
#define IEEE80211_MAX_MPDU_WEN_HT_3839		3839
#define IEEE80211_MAX_MPDU_WEN_HT_7935		7935

#define IEEE80211_MAX_MPDU_WEN_VHT_3895		3895
#define IEEE80211_MAX_MPDU_WEN_VHT_7991		7991
#define IEEE80211_MAX_MPDU_WEN_VHT_11454	11454

#define IEEE80211_MAX_SSID_WEN		32

#define IEEE80211_MAX_MESH_ID_WEN	32

#define IEEE80211_FIWST_TSPEC_TSID	8
#define IEEE80211_NUM_TIDS		16

/* numbew of usew pwiowities 802.11 uses */
#define IEEE80211_NUM_UPS		8
/* numbew of ACs */
#define IEEE80211_NUM_ACS		4

#define IEEE80211_QOS_CTW_WEN		2
/* 1d tag mask */
#define IEEE80211_QOS_CTW_TAG1D_MASK		0x0007
/* TID mask */
#define IEEE80211_QOS_CTW_TID_MASK		0x000f
/* EOSP */
#define IEEE80211_QOS_CTW_EOSP			0x0010
/* ACK powicy */
#define IEEE80211_QOS_CTW_ACK_POWICY_NOWMAW	0x0000
#define IEEE80211_QOS_CTW_ACK_POWICY_NOACK	0x0020
#define IEEE80211_QOS_CTW_ACK_POWICY_NO_EXPW	0x0040
#define IEEE80211_QOS_CTW_ACK_POWICY_BWOCKACK	0x0060
#define IEEE80211_QOS_CTW_ACK_POWICY_MASK	0x0060
/* A-MSDU 802.11n */
#define IEEE80211_QOS_CTW_A_MSDU_PWESENT	0x0080
/* Mesh Contwow 802.11s */
#define IEEE80211_QOS_CTW_MESH_CONTWOW_PWESENT  0x0100

/* Mesh Powew Save Wevew */
#define IEEE80211_QOS_CTW_MESH_PS_WEVEW		0x0200
/* Mesh Weceivew Sewvice Pewiod Initiated */
#define IEEE80211_QOS_CTW_WSPI			0x0400

/* U-APSD queue fow WMM IEs sent by AP */
#define IEEE80211_WMM_IE_AP_QOSINFO_UAPSD	(1<<7)
#define IEEE80211_WMM_IE_AP_QOSINFO_PAWAM_SET_CNT_MASK	0x0f

/* U-APSD queues fow WMM IEs sent by STA */
#define IEEE80211_WMM_IE_STA_QOSINFO_AC_VO	(1<<0)
#define IEEE80211_WMM_IE_STA_QOSINFO_AC_VI	(1<<1)
#define IEEE80211_WMM_IE_STA_QOSINFO_AC_BK	(1<<2)
#define IEEE80211_WMM_IE_STA_QOSINFO_AC_BE	(1<<3)
#define IEEE80211_WMM_IE_STA_QOSINFO_AC_MASK	0x0f

/* U-APSD max SP wength fow WMM IEs sent by STA */
#define IEEE80211_WMM_IE_STA_QOSINFO_SP_AWW	0x00
#define IEEE80211_WMM_IE_STA_QOSINFO_SP_2	0x01
#define IEEE80211_WMM_IE_STA_QOSINFO_SP_4	0x02
#define IEEE80211_WMM_IE_STA_QOSINFO_SP_6	0x03
#define IEEE80211_WMM_IE_STA_QOSINFO_SP_MASK	0x03
#define IEEE80211_WMM_IE_STA_QOSINFO_SP_SHIFT	5

#define IEEE80211_HT_CTW_WEN		4

/* twiggew type within common_info of twiggew fwame */
#define IEEE80211_TWIGGEW_TYPE_MASK		0xf
#define IEEE80211_TWIGGEW_TYPE_BASIC		0x0
#define IEEE80211_TWIGGEW_TYPE_BFWP		0x1
#define IEEE80211_TWIGGEW_TYPE_MU_BAW		0x2
#define IEEE80211_TWIGGEW_TYPE_MU_WTS		0x3
#define IEEE80211_TWIGGEW_TYPE_BSWP		0x4
#define IEEE80211_TWIGGEW_TYPE_GCW_MU_BAW	0x5
#define IEEE80211_TWIGGEW_TYPE_BQWP		0x6
#define IEEE80211_TWIGGEW_TYPE_NFWP		0x7

/* UW-bandwidth within common_info of twiggew fwame */
#define IEEE80211_TWIGGEW_UWBW_MASK		0xc0000
#define IEEE80211_TWIGGEW_UWBW_20MHZ		0x0
#define IEEE80211_TWIGGEW_UWBW_40MHZ		0x1
#define IEEE80211_TWIGGEW_UWBW_80MHZ		0x2
#define IEEE80211_TWIGGEW_UWBW_160_80P80MHZ	0x3

stwuct ieee80211_hdw {
	__we16 fwame_contwow;
	__we16 duwation_id;
	stwuct_gwoup(addws,
		u8 addw1[ETH_AWEN];
		u8 addw2[ETH_AWEN];
		u8 addw3[ETH_AWEN];
	);
	__we16 seq_ctww;
	u8 addw4[ETH_AWEN];
} __packed __awigned(2);

stwuct ieee80211_hdw_3addw {
	__we16 fwame_contwow;
	__we16 duwation_id;
	u8 addw1[ETH_AWEN];
	u8 addw2[ETH_AWEN];
	u8 addw3[ETH_AWEN];
	__we16 seq_ctww;
} __packed __awigned(2);

stwuct ieee80211_qos_hdw {
	__we16 fwame_contwow;
	__we16 duwation_id;
	u8 addw1[ETH_AWEN];
	u8 addw2[ETH_AWEN];
	u8 addw3[ETH_AWEN];
	__we16 seq_ctww;
	__we16 qos_ctww;
} __packed __awigned(2);

stwuct ieee80211_qos_hdw_4addw {
	__we16 fwame_contwow;
	__we16 duwation_id;
	u8 addw1[ETH_AWEN];
	u8 addw2[ETH_AWEN];
	u8 addw3[ETH_AWEN];
	__we16 seq_ctww;
	u8 addw4[ETH_AWEN];
	__we16 qos_ctww;
} __packed __awigned(2);

stwuct ieee80211_twiggew {
	__we16 fwame_contwow;
	__we16 duwation;
	u8 wa[ETH_AWEN];
	u8 ta[ETH_AWEN];
	__we64 common_info;
	u8 vawiabwe[];
} __packed __awigned(2);

/**
 * ieee80211_has_tods - check if IEEE80211_FCTW_TODS is set
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_has_tods(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_TODS)) != 0;
}

/**
 * ieee80211_has_fwomds - check if IEEE80211_FCTW_FWOMDS is set
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_has_fwomds(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FWOMDS)) != 0;
}

/**
 * ieee80211_has_a4 - check if IEEE80211_FCTW_TODS and IEEE80211_FCTW_FWOMDS awe set
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_has_a4(__we16 fc)
{
	__we16 tmp = cpu_to_we16(IEEE80211_FCTW_TODS | IEEE80211_FCTW_FWOMDS);
	wetuwn (fc & tmp) == tmp;
}

/**
 * ieee80211_has_mowefwags - check if IEEE80211_FCTW_MOWEFWAGS is set
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_has_mowefwags(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_MOWEFWAGS)) != 0;
}

/**
 * ieee80211_has_wetwy - check if IEEE80211_FCTW_WETWY is set
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_has_wetwy(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_WETWY)) != 0;
}

/**
 * ieee80211_has_pm - check if IEEE80211_FCTW_PM is set
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_has_pm(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_PM)) != 0;
}

/**
 * ieee80211_has_mowedata - check if IEEE80211_FCTW_MOWEDATA is set
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_has_mowedata(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_MOWEDATA)) != 0;
}

/**
 * ieee80211_has_pwotected - check if IEEE80211_FCTW_PWOTECTED is set
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_has_pwotected(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_PWOTECTED)) != 0;
}

/**
 * ieee80211_has_owdew - check if IEEE80211_FCTW_OWDEW is set
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_has_owdew(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_OWDEW)) != 0;
}

/**
 * ieee80211_is_mgmt - check if type is IEEE80211_FTYPE_MGMT
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_mgmt(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_MGMT);
}

/**
 * ieee80211_is_ctw - check if type is IEEE80211_FTYPE_CTW
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_ctw(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_CTW);
}

/**
 * ieee80211_is_data - check if type is IEEE80211_FTYPE_DATA
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_data(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_DATA);
}

/**
 * ieee80211_is_ext - check if type is IEEE80211_FTYPE_EXT
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_ext(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_EXT);
}


/**
 * ieee80211_is_data_qos - check if type is IEEE80211_FTYPE_DATA and IEEE80211_STYPE_QOS_DATA is set
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_data_qos(__we16 fc)
{
	/*
	 * mask with QOS_DATA wathew than IEEE80211_FCTW_STYPE as we just need
	 * to check the one bit
	 */
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_STYPE_QOS_DATA)) ==
	       cpu_to_we16(IEEE80211_FTYPE_DATA | IEEE80211_STYPE_QOS_DATA);
}

/**
 * ieee80211_is_data_pwesent - check if type is IEEE80211_FTYPE_DATA and has data
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_data_pwesent(__we16 fc)
{
	/*
	 * mask with 0x40 and test that that bit is cweaw to onwy wetuwn twue
	 * fow the data-containing substypes.
	 */
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | 0x40)) ==
	       cpu_to_we16(IEEE80211_FTYPE_DATA);
}

/**
 * ieee80211_is_assoc_weq - check if IEEE80211_FTYPE_MGMT && IEEE80211_STYPE_ASSOC_WEQ
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_assoc_weq(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_MGMT | IEEE80211_STYPE_ASSOC_WEQ);
}

/**
 * ieee80211_is_assoc_wesp - check if IEEE80211_FTYPE_MGMT && IEEE80211_STYPE_ASSOC_WESP
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_assoc_wesp(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_MGMT | IEEE80211_STYPE_ASSOC_WESP);
}

/**
 * ieee80211_is_weassoc_weq - check if IEEE80211_FTYPE_MGMT && IEEE80211_STYPE_WEASSOC_WEQ
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_weassoc_weq(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_MGMT | IEEE80211_STYPE_WEASSOC_WEQ);
}

/**
 * ieee80211_is_weassoc_wesp - check if IEEE80211_FTYPE_MGMT && IEEE80211_STYPE_WEASSOC_WESP
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_weassoc_wesp(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_MGMT | IEEE80211_STYPE_WEASSOC_WESP);
}

/**
 * ieee80211_is_pwobe_weq - check if IEEE80211_FTYPE_MGMT && IEEE80211_STYPE_PWOBE_WEQ
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_pwobe_weq(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_MGMT | IEEE80211_STYPE_PWOBE_WEQ);
}

/**
 * ieee80211_is_pwobe_wesp - check if IEEE80211_FTYPE_MGMT && IEEE80211_STYPE_PWOBE_WESP
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_pwobe_wesp(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_MGMT | IEEE80211_STYPE_PWOBE_WESP);
}

/**
 * ieee80211_is_beacon - check if IEEE80211_FTYPE_MGMT && IEEE80211_STYPE_BEACON
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_beacon(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_MGMT | IEEE80211_STYPE_BEACON);
}

/**
 * ieee80211_is_s1g_beacon - check if IEEE80211_FTYPE_EXT &&
 * IEEE80211_STYPE_S1G_BEACON
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_s1g_beacon(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE |
				 IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_EXT | IEEE80211_STYPE_S1G_BEACON);
}

/**
 * ieee80211_next_tbtt_pwesent - check if IEEE80211_FTYPE_EXT &&
 * IEEE80211_STYPE_S1G_BEACON && IEEE80211_S1G_BCN_NEXT_TBTT
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_next_tbtt_pwesent(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_EXT | IEEE80211_STYPE_S1G_BEACON) &&
	       fc & cpu_to_we16(IEEE80211_S1G_BCN_NEXT_TBTT);
}

/**
 * ieee80211_is_s1g_showt_beacon - check if next tbtt pwesent bit is set. Onwy
 * twue fow S1G beacons when they'we showt.
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_s1g_showt_beacon(__we16 fc)
{
	wetuwn ieee80211_is_s1g_beacon(fc) && ieee80211_next_tbtt_pwesent(fc);
}

/**
 * ieee80211_is_atim - check if IEEE80211_FTYPE_MGMT && IEEE80211_STYPE_ATIM
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_atim(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_MGMT | IEEE80211_STYPE_ATIM);
}

/**
 * ieee80211_is_disassoc - check if IEEE80211_FTYPE_MGMT && IEEE80211_STYPE_DISASSOC
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_disassoc(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_MGMT | IEEE80211_STYPE_DISASSOC);
}

/**
 * ieee80211_is_auth - check if IEEE80211_FTYPE_MGMT && IEEE80211_STYPE_AUTH
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_auth(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_MGMT | IEEE80211_STYPE_AUTH);
}

/**
 * ieee80211_is_deauth - check if IEEE80211_FTYPE_MGMT && IEEE80211_STYPE_DEAUTH
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_deauth(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_MGMT | IEEE80211_STYPE_DEAUTH);
}

/**
 * ieee80211_is_action - check if IEEE80211_FTYPE_MGMT && IEEE80211_STYPE_ACTION
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_action(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_MGMT | IEEE80211_STYPE_ACTION);
}

/**
 * ieee80211_is_back_weq - check if IEEE80211_FTYPE_CTW && IEEE80211_STYPE_BACK_WEQ
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_back_weq(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_CTW | IEEE80211_STYPE_BACK_WEQ);
}

/**
 * ieee80211_is_back - check if IEEE80211_FTYPE_CTW && IEEE80211_STYPE_BACK
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_back(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_CTW | IEEE80211_STYPE_BACK);
}

/**
 * ieee80211_is_pspoww - check if IEEE80211_FTYPE_CTW && IEEE80211_STYPE_PSPOWW
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_pspoww(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_CTW | IEEE80211_STYPE_PSPOWW);
}

/**
 * ieee80211_is_wts - check if IEEE80211_FTYPE_CTW && IEEE80211_STYPE_WTS
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_wts(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_CTW | IEEE80211_STYPE_WTS);
}

/**
 * ieee80211_is_cts - check if IEEE80211_FTYPE_CTW && IEEE80211_STYPE_CTS
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_cts(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_CTW | IEEE80211_STYPE_CTS);
}

/**
 * ieee80211_is_ack - check if IEEE80211_FTYPE_CTW && IEEE80211_STYPE_ACK
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_ack(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_CTW | IEEE80211_STYPE_ACK);
}

/**
 * ieee80211_is_cfend - check if IEEE80211_FTYPE_CTW && IEEE80211_STYPE_CFEND
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_cfend(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_CTW | IEEE80211_STYPE_CFEND);
}

/**
 * ieee80211_is_cfendack - check if IEEE80211_FTYPE_CTW && IEEE80211_STYPE_CFENDACK
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_cfendack(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_CTW | IEEE80211_STYPE_CFENDACK);
}

/**
 * ieee80211_is_nuwwfunc - check if fwame is a weguwaw (non-QoS) nuwwfunc fwame
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_nuwwfunc(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_DATA | IEEE80211_STYPE_NUWWFUNC);
}

/**
 * ieee80211_is_qos_nuwwfunc - check if fwame is a QoS nuwwfunc fwame
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_qos_nuwwfunc(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_DATA | IEEE80211_STYPE_QOS_NUWWFUNC);
}

/**
 * ieee80211_is_twiggew - check if fwame is twiggew fwame
 * @fc: fwame contwow fiewd in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_twiggew(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) ==
	       cpu_to_we16(IEEE80211_FTYPE_CTW | IEEE80211_STYPE_TWIGGEW);
}

/**
 * ieee80211_is_any_nuwwfunc - check if fwame is weguwaw ow QoS nuwwfunc fwame
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_any_nuwwfunc(__we16 fc)
{
	wetuwn (ieee80211_is_nuwwfunc(fc) || ieee80211_is_qos_nuwwfunc(fc));
}

/**
 * ieee80211_is_fiwst_fwag - check if IEEE80211_SCTW_FWAG is not set
 * @seq_ctww: fwame sequence contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee80211_is_fiwst_fwag(__we16 seq_ctww)
{
	wetuwn (seq_ctww & cpu_to_we16(IEEE80211_SCTW_FWAG)) == 0;
}

/**
 * ieee80211_is_fwag - check if a fwame is a fwagment
 * @hdw: 802.11 headew of the fwame
 */
static inwine boow ieee80211_is_fwag(stwuct ieee80211_hdw *hdw)
{
	wetuwn ieee80211_has_mowefwags(hdw->fwame_contwow) ||
	       hdw->seq_ctww & cpu_to_we16(IEEE80211_SCTW_FWAG);
}

stwuct ieee80211s_hdw {
	u8 fwags;
	u8 ttw;
	__we32 seqnum;
	u8 eaddw1[ETH_AWEN];
	u8 eaddw2[ETH_AWEN];
} __packed __awigned(2);

/* Mesh fwags */
#define MESH_FWAGS_AE_A4 	0x1
#define MESH_FWAGS_AE_A5_A6	0x2
#define MESH_FWAGS_AE		0x3
#define MESH_FWAGS_PS_DEEP	0x4

/**
 * enum ieee80211_pweq_fwags - mesh PWEQ ewement fwags
 *
 * @IEEE80211_PWEQ_PWOACTIVE_PWEP_FWAG: pwoactive PWEP subfiewd
 */
enum ieee80211_pweq_fwags {
	IEEE80211_PWEQ_PWOACTIVE_PWEP_FWAG	= 1<<2,
};

/**
 * enum ieee80211_pweq_tawget_fwags - mesh PWEQ ewement pew tawget fwags
 *
 * @IEEE80211_PWEQ_TO_FWAG: tawget onwy subfiewd
 * @IEEE80211_PWEQ_USN_FWAG: unknown tawget HWMP sequence numbew subfiewd
 */
enum ieee80211_pweq_tawget_fwags {
	IEEE80211_PWEQ_TO_FWAG	= 1<<0,
	IEEE80211_PWEQ_USN_FWAG	= 1<<2,
};

/**
 * stwuct ieee80211_quiet_ie - Quiet ewement
 * @count: Quiet Count
 * @pewiod: Quiet Pewiod
 * @duwation: Quiet Duwation
 * @offset: Quiet Offset
 *
 * This stwuctuwe wepwesents the paywoad of the "Quiet ewement" as
 * descwibed in IEEE Std 802.11-2020 section 9.4.2.22.
 */
stwuct ieee80211_quiet_ie {
	u8 count;
	u8 pewiod;
	__we16 duwation;
	__we16 offset;
} __packed;

/**
 * stwuct ieee80211_mswment_ie - Measuwement ewement
 * @token: Measuwement Token
 * @mode: Measuwement Wepowt Mode
 * @type: Measuwement Type
 * @wequest: Measuwement Wequest ow Measuwement Wepowt
 *
 * This stwuctuwe wepwesents the paywoad of both the "Measuwement
 * Wequest ewement" and the "Measuwement Wepowt ewement" as descwibed
 * in IEEE Std 802.11-2020 sections 9.4.2.20 and 9.4.2.21.
 */
stwuct ieee80211_mswment_ie {
	u8 token;
	u8 mode;
	u8 type;
	u8 wequest[];
} __packed;

/**
 * stwuct ieee80211_channew_sw_ie - Channew Switch Announcement ewement
 * @mode: Channew Switch Mode
 * @new_ch_num: New Channew Numbew
 * @count: Channew Switch Count
 *
 * This stwuctuwe wepwesents the paywoad of the "Channew Switch
 * Announcement ewement" as descwibed in IEEE Std 802.11-2020 section
 * 9.4.2.18.
 */
stwuct ieee80211_channew_sw_ie {
	u8 mode;
	u8 new_ch_num;
	u8 count;
} __packed;

/**
 * stwuct ieee80211_ext_chansw_ie - Extended Channew Switch Announcement ewement
 * @mode: Channew Switch Mode
 * @new_opewating_cwass: New Opewating Cwass
 * @new_ch_num: New Channew Numbew
 * @count: Channew Switch Count
 *
 * This stwuctuwe wepwesents the "Extended Channew Switch Announcement
 * ewement" as descwibed in IEEE Std 802.11-2020 section 9.4.2.52.
 */
stwuct ieee80211_ext_chansw_ie {
	u8 mode;
	u8 new_opewating_cwass;
	u8 new_ch_num;
	u8 count;
} __packed;

/**
 * stwuct ieee80211_sec_chan_offs_ie - secondawy channew offset IE
 * @sec_chan_offs: secondawy channew offset, uses IEEE80211_HT_PAWAM_CHA_SEC_*
 *	vawues hewe
 * This stwuctuwe wepwesents the "Secondawy Channew Offset ewement"
 */
stwuct ieee80211_sec_chan_offs_ie {
	u8 sec_chan_offs;
} __packed;

/**
 * stwuct ieee80211_mesh_chansw_pawams_ie - mesh channew switch pawametews IE
 * @mesh_ttw: Time To Wive
 * @mesh_fwags: Fwags
 * @mesh_weason: Weason Code
 * @mesh_pwe_vawue: Pwecedence Vawue
 *
 * This stwuctuwe wepwesents the paywoad of the "Mesh Channew Switch
 * Pawametews ewement" as descwibed in IEEE Std 802.11-2020 section
 * 9.4.2.102.
 */
stwuct ieee80211_mesh_chansw_pawams_ie {
	u8 mesh_ttw;
	u8 mesh_fwags;
	__we16 mesh_weason;
	__we16 mesh_pwe_vawue;
} __packed;

/**
 * stwuct ieee80211_wide_bw_chansw_ie - wide bandwidth channew switch IE
 * @new_channew_width: New Channew Width
 * @new_centew_fweq_seg0: New Channew Centew Fwequency Segment 0
 * @new_centew_fweq_seg1: New Channew Centew Fwequency Segment 1
 *
 * This stwuctuwe wepwesents the paywoad of the "Wide Bandwidth
 * Channew Switch ewement" as descwibed in IEEE Std 802.11-2020
 * section 9.4.2.160.
 */
stwuct ieee80211_wide_bw_chansw_ie {
	u8 new_channew_width;
	u8 new_centew_fweq_seg0, new_centew_fweq_seg1;
} __packed;

/**
 * stwuct ieee80211_tim_ie - Twaffic Indication Map infowmation ewement
 * @dtim_count: DTIM Count
 * @dtim_pewiod: DTIM Pewiod
 * @bitmap_ctww: Bitmap Contwow
 * @wequiwed_octet: "Syntatic sugaw" to fowce the stwuct size to the
 *                  minimum vawid size when cawwied in a non-S1G PPDU
 * @viwtuaw_map: Pawtiaw Viwtuaw Bitmap
 *
 * This stwuctuwe wepwesents the paywoad of the "TIM ewement" as
 * descwibed in IEEE Std 802.11-2020 section 9.4.2.5. Note that this
 * definition is onwy appwicabwe when the ewement is cawwied in a
 * non-S1G PPDU. When the TIM is cawwied in an S1G PPDU, the Bitmap
 * Contwow and Pawtiaw Viwtuaw Bitmap may not be pwesent.
 */
stwuct ieee80211_tim_ie {
	u8 dtim_count;
	u8 dtim_pewiod;
	u8 bitmap_ctww;
	union {
		u8 wequiwed_octet;
		DECWAWE_FWEX_AWWAY(u8, viwtuaw_map);
	};
} __packed;

/**
 * stwuct ieee80211_meshconf_ie - Mesh Configuwation ewement
 * @meshconf_psew: Active Path Sewection Pwotocow Identifiew
 * @meshconf_pmetwic: Active Path Sewection Metwic Identifiew
 * @meshconf_congest: Congestion Contwow Mode Identifiew
 * @meshconf_synch: Synchwonization Method Identifiew
 * @meshconf_auth: Authentication Pwotocow Identifiew
 * @meshconf_fowm: Mesh Fowmation Info
 * @meshconf_cap: Mesh Capabiwity (see &enum mesh_config_capab_fwags)
 *
 * This stwuctuwe wepwesents the paywoad of the "Mesh Configuwation
 * ewement" as descwibed in IEEE Std 802.11-2020 section 9.4.2.97.
 */
stwuct ieee80211_meshconf_ie {
	u8 meshconf_psew;
	u8 meshconf_pmetwic;
	u8 meshconf_congest;
	u8 meshconf_synch;
	u8 meshconf_auth;
	u8 meshconf_fowm;
	u8 meshconf_cap;
} __packed;

/**
 * enum mesh_config_capab_fwags - Mesh Configuwation IE capabiwity fiewd fwags
 *
 * @IEEE80211_MESHCONF_CAPAB_ACCEPT_PWINKS: STA is wiwwing to estabwish
 *	additionaw mesh peewings with othew mesh STAs
 * @IEEE80211_MESHCONF_CAPAB_FOWWAWDING: the STA fowwawds MSDUs
 * @IEEE80211_MESHCONF_CAPAB_TBTT_ADJUSTING: TBTT adjustment pwoceduwe
 *	is ongoing
 * @IEEE80211_MESHCONF_CAPAB_POWEW_SAVE_WEVEW: STA is in deep sweep mode ow has
 *	neighbows in deep sweep mode
 *
 * Enumewates the "Mesh Capabiwity" as descwibed in IEEE Std
 * 802.11-2020 section 9.4.2.97.7.
 */
enum mesh_config_capab_fwags {
	IEEE80211_MESHCONF_CAPAB_ACCEPT_PWINKS		= 0x01,
	IEEE80211_MESHCONF_CAPAB_FOWWAWDING		= 0x08,
	IEEE80211_MESHCONF_CAPAB_TBTT_ADJUSTING		= 0x20,
	IEEE80211_MESHCONF_CAPAB_POWEW_SAVE_WEVEW	= 0x40,
};

#define IEEE80211_MESHCONF_FOWM_CONNECTED_TO_GATE 0x1

/*
 * mesh channew switch pawametews ewement's fwag indicatow
 *
 */
#define WWAN_EID_CHAN_SWITCH_PAWAM_TX_WESTWICT BIT(0)
#define WWAN_EID_CHAN_SWITCH_PAWAM_INITIATOW BIT(1)
#define WWAN_EID_CHAN_SWITCH_PAWAM_WEASON BIT(2)

/**
 * stwuct ieee80211_wann_ie - WANN (woot announcement) ewement
 * @wann_fwags: Fwags
 * @wann_hopcount: Hop Count
 * @wann_ttw: Ewement TTW
 * @wann_addw: Woot Mesh STA Addwess
 * @wann_seq: HWMP Sequence Numbew
 * @wann_intewvaw: Intewvaw
 * @wann_metwic: Metwic
 *
 * This stwuctuwe wepwesents the paywoad of the "WANN ewement" as
 * descwibed in IEEE Std 802.11-2020 section 9.4.2.111.
 */
stwuct ieee80211_wann_ie {
	u8 wann_fwags;
	u8 wann_hopcount;
	u8 wann_ttw;
	u8 wann_addw[ETH_AWEN];
	__we32 wann_seq;
	__we32 wann_intewvaw;
	__we32 wann_metwic;
} __packed;

enum ieee80211_wann_fwags {
	WANN_FWAG_IS_GATE = 1 << 0,
};

enum ieee80211_ht_chanwidth_vawues {
	IEEE80211_HT_CHANWIDTH_20MHZ = 0,
	IEEE80211_HT_CHANWIDTH_ANY = 1,
};

/**
 * enum ieee80211_vht_opmode_bits - VHT opewating mode fiewd bits
 * @IEEE80211_OPMODE_NOTIF_CHANWIDTH_MASK: channew width mask
 * @IEEE80211_OPMODE_NOTIF_CHANWIDTH_20MHZ: 20 MHz channew width
 * @IEEE80211_OPMODE_NOTIF_CHANWIDTH_40MHZ: 40 MHz channew width
 * @IEEE80211_OPMODE_NOTIF_CHANWIDTH_80MHZ: 80 MHz channew width
 * @IEEE80211_OPMODE_NOTIF_CHANWIDTH_160MHZ: 160 MHz ow 80+80 MHz channew width
 * @IEEE80211_OPMODE_NOTIF_BW_160_80P80: 160 / 80+80 MHz indicatow fwag
 * @IEEE80211_OPMODE_NOTIF_WX_NSS_MASK: numbew of spatiaw stweams mask
 *	(the NSS vawue is the vawue of this fiewd + 1)
 * @IEEE80211_OPMODE_NOTIF_WX_NSS_SHIFT: numbew of spatiaw stweams shift
 * @IEEE80211_OPMODE_NOTIF_WX_NSS_TYPE_BF: indicates stweams in SU-MIMO PPDU
 *	using a beamfowming steewing matwix
 */
enum ieee80211_vht_opmode_bits {
	IEEE80211_OPMODE_NOTIF_CHANWIDTH_MASK	= 0x03,
	IEEE80211_OPMODE_NOTIF_CHANWIDTH_20MHZ	= 0,
	IEEE80211_OPMODE_NOTIF_CHANWIDTH_40MHZ	= 1,
	IEEE80211_OPMODE_NOTIF_CHANWIDTH_80MHZ	= 2,
	IEEE80211_OPMODE_NOTIF_CHANWIDTH_160MHZ	= 3,
	IEEE80211_OPMODE_NOTIF_BW_160_80P80	= 0x04,
	IEEE80211_OPMODE_NOTIF_WX_NSS_MASK	= 0x70,
	IEEE80211_OPMODE_NOTIF_WX_NSS_SHIFT	= 4,
	IEEE80211_OPMODE_NOTIF_WX_NSS_TYPE_BF	= 0x80,
};

/**
 * enum ieee80211_s1g_chanwidth
 * These awe defined in IEEE802.11-2016ah Tabwe 10-20
 * as BSS Channew Width
 *
 * @IEEE80211_S1G_CHANWIDTH_1MHZ: 1MHz opewating channew
 * @IEEE80211_S1G_CHANWIDTH_2MHZ: 2MHz opewating channew
 * @IEEE80211_S1G_CHANWIDTH_4MHZ: 4MHz opewating channew
 * @IEEE80211_S1G_CHANWIDTH_8MHZ: 8MHz opewating channew
 * @IEEE80211_S1G_CHANWIDTH_16MHZ: 16MHz opewating channew
 */
enum ieee80211_s1g_chanwidth {
	IEEE80211_S1G_CHANWIDTH_1MHZ = 0,
	IEEE80211_S1G_CHANWIDTH_2MHZ = 1,
	IEEE80211_S1G_CHANWIDTH_4MHZ = 3,
	IEEE80211_S1G_CHANWIDTH_8MHZ = 7,
	IEEE80211_S1G_CHANWIDTH_16MHZ = 15,
};

#define WWAN_SA_QUEWY_TW_ID_WEN 2
#define WWAN_MEMBEWSHIP_WEN 8
#define WWAN_USEW_POSITION_WEN 16

/**
 * stwuct ieee80211_tpc_wepowt_ie - TPC Wepowt ewement
 * @tx_powew: Twansmit Powew
 * @wink_mawgin: Wink Mawgin
 *
 * This stwuctuwe wepwesents the paywoad of the "TPC Wepowt ewement" as
 * descwibed in IEEE Std 802.11-2020 section 9.4.2.16.
 */
stwuct ieee80211_tpc_wepowt_ie {
	u8 tx_powew;
	u8 wink_mawgin;
} __packed;

#define IEEE80211_ADDBA_EXT_FWAG_WEVEW_MASK	GENMASK(2, 1)
#define IEEE80211_ADDBA_EXT_FWAG_WEVEW_SHIFT	1
#define IEEE80211_ADDBA_EXT_NO_FWAG		BIT(0)
#define IEEE80211_ADDBA_EXT_BUF_SIZE_MASK	GENMASK(7, 5)
#define IEEE80211_ADDBA_EXT_BUF_SIZE_SHIFT	10

stwuct ieee80211_addba_ext_ie {
	u8 data;
} __packed;

/**
 * stwuct ieee80211_s1g_bcn_compat_ie - S1G Beacon Compatibiwity ewement
 * @compat_info: Compatibiwity Infowmation
 * @beacon_int: Beacon Intewvaw
 * @tsf_compwetion: TSF Compwetion
 *
 * This stwuctuwe wepwesents the paywoad of the "S1G Beacon
 * Compatibiwity ewement" as descwibed in IEEE Std 802.11-2020 section
 * 9.4.2.196.
 */
stwuct ieee80211_s1g_bcn_compat_ie {
	__we16 compat_info;
	__we16 beacon_int;
	__we32 tsf_compwetion;
} __packed;

/**
 * stwuct ieee80211_s1g_opew_ie - S1G Opewation ewement
 * @ch_width: S1G Opewation Infowmation Channew Width
 * @opew_cwass: S1G Opewation Infowmation Opewating Cwass
 * @pwimawy_ch: S1G Opewation Infowmation Pwimawy Channew Numbew
 * @opew_ch: S1G Opewation Infowmation  Channew Centew Fwequency
 * @basic_mcs_nss: Basic S1G-MCS and NSS Set
 *
 * This stwuctuwe wepwesents the paywoad of the "S1G Opewation
 * ewement" as descwibed in IEEE Std 802.11-2020 section 9.4.2.212.
 */
stwuct ieee80211_s1g_opew_ie {
	u8 ch_width;
	u8 opew_cwass;
	u8 pwimawy_ch;
	u8 opew_ch;
	__we16 basic_mcs_nss;
} __packed;

/**
 * stwuct ieee80211_aid_wesponse_ie - AID Wesponse ewement
 * @aid: AID/Gwoup AID
 * @switch_count: AID Switch Count
 * @wesponse_int: AID Wesponse Intewvaw
 *
 * This stwuctuwe wepwesents the paywoad of the "AID Wesponse ewement"
 * as descwibed in IEEE Std 802.11-2020 section 9.4.2.194.
 */
stwuct ieee80211_aid_wesponse_ie {
	__we16 aid;
	u8 switch_count;
	__we16 wesponse_int;
} __packed;

stwuct ieee80211_s1g_cap {
	u8 capab_info[10];
	u8 supp_mcs_nss[5];
} __packed;

stwuct ieee80211_ext {
	__we16 fwame_contwow;
	__we16 duwation;
	union {
		stwuct {
			u8 sa[ETH_AWEN];
			__we32 timestamp;
			u8 change_seq;
			u8 vawiabwe[0];
		} __packed s1g_beacon;
		stwuct {
			u8 sa[ETH_AWEN];
			__we32 timestamp;
			u8 change_seq;
			u8 next_tbtt[3];
			u8 vawiabwe[0];
		} __packed s1g_showt_beacon;
	} u;
} __packed __awigned(2);

#define IEEE80211_TWT_CONTWOW_NDP			BIT(0)
#define IEEE80211_TWT_CONTWOW_WESP_MODE			BIT(1)
#define IEEE80211_TWT_CONTWOW_NEG_TYPE_BWOADCAST	BIT(3)
#define IEEE80211_TWT_CONTWOW_WX_DISABWED		BIT(4)
#define IEEE80211_TWT_CONTWOW_WAKE_DUW_UNIT		BIT(5)

#define IEEE80211_TWT_WEQTYPE_WEQUEST			BIT(0)
#define IEEE80211_TWT_WEQTYPE_SETUP_CMD			GENMASK(3, 1)
#define IEEE80211_TWT_WEQTYPE_TWIGGEW			BIT(4)
#define IEEE80211_TWT_WEQTYPE_IMPWICIT			BIT(5)
#define IEEE80211_TWT_WEQTYPE_FWOWTYPE			BIT(6)
#define IEEE80211_TWT_WEQTYPE_FWOWID			GENMASK(9, 7)
#define IEEE80211_TWT_WEQTYPE_WAKE_INT_EXP		GENMASK(14, 10)
#define IEEE80211_TWT_WEQTYPE_PWOTECTION		BIT(15)

enum ieee80211_twt_setup_cmd {
	TWT_SETUP_CMD_WEQUEST,
	TWT_SETUP_CMD_SUGGEST,
	TWT_SETUP_CMD_DEMAND,
	TWT_SETUP_CMD_GWOUPING,
	TWT_SETUP_CMD_ACCEPT,
	TWT_SETUP_CMD_AWTEWNATE,
	TWT_SETUP_CMD_DICTATE,
	TWT_SETUP_CMD_WEJECT,
};

stwuct ieee80211_twt_pawams {
	__we16 weq_type;
	__we64 twt;
	u8 min_twt_duw;
	__we16 mantissa;
	u8 channew;
} __packed;

stwuct ieee80211_twt_setup {
	u8 diawog_token;
	u8 ewement_id;
	u8 wength;
	u8 contwow;
	u8 pawams[];
} __packed;

#define IEEE80211_TTWM_MAX_CNT				2
#define IEEE80211_TTWM_CONTWOW_DIWECTION		0x03
#define IEEE80211_TTWM_CONTWOW_DEF_WINK_MAP		0x04
#define IEEE80211_TTWM_CONTWOW_SWITCH_TIME_PWESENT	0x08
#define IEEE80211_TTWM_CONTWOW_EXPECTED_DUW_PWESENT	0x10
#define IEEE80211_TTWM_CONTWOW_WINK_MAP_SIZE		0x20

#define IEEE80211_TTWM_DIWECTION_DOWN		0
#define IEEE80211_TTWM_DIWECTION_UP		1
#define IEEE80211_TTWM_DIWECTION_BOTH		2

/**
 * stwuct ieee80211_ttwm_ewem - TID-To-Wink Mapping ewement
 *
 * Defined in section 9.4.2.314 in P802.11be_D4
 *
 * @contwow: the fiwst pawt of contwow fiewd
 * @optionaw: the second pawt of contwow fiewd
 */
stwuct ieee80211_ttwm_ewem {
	u8 contwow;
	u8 optionaw[];
} __packed;

stwuct ieee80211_mgmt {
	__we16 fwame_contwow;
	__we16 duwation;
	u8 da[ETH_AWEN];
	u8 sa[ETH_AWEN];
	u8 bssid[ETH_AWEN];
	__we16 seq_ctww;
	union {
		stwuct {
			__we16 auth_awg;
			__we16 auth_twansaction;
			__we16 status_code;
			/* possibwy fowwowed by Chawwenge text */
			u8 vawiabwe[];
		} __packed auth;
		stwuct {
			__we16 weason_code;
		} __packed deauth;
		stwuct {
			__we16 capab_info;
			__we16 wisten_intewvaw;
			/* fowwowed by SSID and Suppowted wates */
			u8 vawiabwe[];
		} __packed assoc_weq;
		stwuct {
			__we16 capab_info;
			__we16 status_code;
			__we16 aid;
			/* fowwowed by Suppowted wates */
			u8 vawiabwe[];
		} __packed assoc_wesp, weassoc_wesp;
		stwuct {
			__we16 capab_info;
			__we16 status_code;
			u8 vawiabwe[];
		} __packed s1g_assoc_wesp, s1g_weassoc_wesp;
		stwuct {
			__we16 capab_info;
			__we16 wisten_intewvaw;
			u8 cuwwent_ap[ETH_AWEN];
			/* fowwowed by SSID and Suppowted wates */
			u8 vawiabwe[];
		} __packed weassoc_weq;
		stwuct {
			__we16 weason_code;
		} __packed disassoc;
		stwuct {
			__we64 timestamp;
			__we16 beacon_int;
			__we16 capab_info;
			/* fowwowed by some of SSID, Suppowted wates,
			 * FH Pawams, DS Pawams, CF Pawams, IBSS Pawams, TIM */
			u8 vawiabwe[];
		} __packed beacon;
		stwuct {
			/* onwy vawiabwe items: SSID, Suppowted wates */
			DECWAWE_FWEX_AWWAY(u8, vawiabwe);
		} __packed pwobe_weq;
		stwuct {
			__we64 timestamp;
			__we16 beacon_int;
			__we16 capab_info;
			/* fowwowed by some of SSID, Suppowted wates,
			 * FH Pawams, DS Pawams, CF Pawams, IBSS Pawams */
			u8 vawiabwe[];
		} __packed pwobe_wesp;
		stwuct {
			u8 categowy;
			union {
				stwuct {
					u8 action_code;
					u8 diawog_token;
					u8 status_code;
					u8 vawiabwe[];
				} __packed wme_action;
				stwuct{
					u8 action_code;
					u8 vawiabwe[];
				} __packed chan_switch;
				stwuct{
					u8 action_code;
					stwuct ieee80211_ext_chansw_ie data;
					u8 vawiabwe[];
				} __packed ext_chan_switch;
				stwuct{
					u8 action_code;
					u8 diawog_token;
					u8 ewement_id;
					u8 wength;
					stwuct ieee80211_mswment_ie msw_ewem;
				} __packed measuwement;
				stwuct{
					u8 action_code;
					u8 diawog_token;
					__we16 capab;
					__we16 timeout;
					__we16 stawt_seq_num;
					/* fowwowed by BA Extension */
					u8 vawiabwe[];
				} __packed addba_weq;
				stwuct{
					u8 action_code;
					u8 diawog_token;
					__we16 status;
					__we16 capab;
					__we16 timeout;
				} __packed addba_wesp;
				stwuct{
					u8 action_code;
					__we16 pawams;
					__we16 weason_code;
				} __packed dewba;
				stwuct {
					u8 action_code;
					u8 vawiabwe[];
				} __packed sewf_pwot;
				stwuct{
					u8 action_code;
					u8 vawiabwe[];
				} __packed mesh_action;
				stwuct {
					u8 action;
					u8 twans_id[WWAN_SA_QUEWY_TW_ID_WEN];
				} __packed sa_quewy;
				stwuct {
					u8 action;
					u8 smps_contwow;
				} __packed ht_smps;
				stwuct {
					u8 action_code;
					u8 chanwidth;
				} __packed ht_notify_cw;
				stwuct {
					u8 action_code;
					u8 diawog_token;
					__we16 capabiwity;
					u8 vawiabwe[0];
				} __packed tdws_discovew_wesp;
				stwuct {
					u8 action_code;
					u8 opewating_mode;
				} __packed vht_opmode_notif;
				stwuct {
					u8 action_code;
					u8 membewship[WWAN_MEMBEWSHIP_WEN];
					u8 position[WWAN_USEW_POSITION_WEN];
				} __packed vht_gwoup_notif;
				stwuct {
					u8 action_code;
					u8 diawog_token;
					u8 tpc_ewem_id;
					u8 tpc_ewem_wength;
					stwuct ieee80211_tpc_wepowt_ie tpc;
				} __packed tpc_wepowt;
				stwuct {
					u8 action_code;
					u8 diawog_token;
					u8 fowwow_up;
					u8 tod[6];
					u8 toa[6];
					__we16 tod_ewwow;
					__we16 toa_ewwow;
					u8 vawiabwe[];
				} __packed ftm;
				stwuct {
					u8 action_code;
					u8 vawiabwe[];
				} __packed s1g;
				stwuct {
					u8 action_code;
					u8 diawog_token;
					u8 fowwow_up;
					u32 tod;
					u32 toa;
					u8 max_tod_ewwow;
					u8 max_toa_ewwow;
				} __packed wnm_timing_msw;
			} u;
		} __packed action;
		DECWAWE_FWEX_AWWAY(u8, body); /* Genewic fwame body */
	} u;
} __packed __awigned(2);

/* Suppowted wates membewship sewectows */
#define BSS_MEMBEWSHIP_SEWECTOW_HT_PHY	127
#define BSS_MEMBEWSHIP_SEWECTOW_VHT_PHY	126
#define BSS_MEMBEWSHIP_SEWECTOW_GWK	125
#define BSS_MEMBEWSHIP_SEWECTOW_EPS	124
#define BSS_MEMBEWSHIP_SEWECTOW_SAE_H2E 123
#define BSS_MEMBEWSHIP_SEWECTOW_HE_PHY	122
#define BSS_MEMBEWSHIP_SEWECTOW_EHT_PHY	121

/* mgmt headew + 1 byte categowy code */
#define IEEE80211_MIN_ACTION_SIZE offsetof(stwuct ieee80211_mgmt, u.action.u)


/* Management MIC infowmation ewement (IEEE 802.11w) */
stwuct ieee80211_mmie {
	u8 ewement_id;
	u8 wength;
	__we16 key_id;
	u8 sequence_numbew[6];
	u8 mic[8];
} __packed;

/* Management MIC infowmation ewement (IEEE 802.11w) fow GMAC and CMAC-256 */
stwuct ieee80211_mmie_16 {
	u8 ewement_id;
	u8 wength;
	__we16 key_id;
	u8 sequence_numbew[6];
	u8 mic[16];
} __packed;

stwuct ieee80211_vendow_ie {
	u8 ewement_id;
	u8 wen;
	u8 oui[3];
	u8 oui_type;
} __packed;

stwuct ieee80211_wmm_ac_pawam {
	u8 aci_aifsn; /* AIFSN, ACM, ACI */
	u8 cw; /* ECWmin, ECWmax (CW = 2^ECW - 1) */
	__we16 txop_wimit;
} __packed;

stwuct ieee80211_wmm_pawam_ie {
	u8 ewement_id; /* Ewement ID: 221 (0xdd); */
	u8 wen; /* Wength: 24 */
	/* wequiwed fiewds fow WMM vewsion 1 */
	u8 oui[3]; /* 00:50:f2 */
	u8 oui_type; /* 2 */
	u8 oui_subtype; /* 1 */
	u8 vewsion; /* 1 fow WMM vewsion 1.0 */
	u8 qos_info; /* AP/STA specific QoS info */
	u8 wesewved; /* 0 */
	/* AC_BE, AC_BK, AC_VI, AC_VO */
	stwuct ieee80211_wmm_ac_pawam ac[4];
} __packed;

/* Contwow fwames */
stwuct ieee80211_wts {
	__we16 fwame_contwow;
	__we16 duwation;
	u8 wa[ETH_AWEN];
	u8 ta[ETH_AWEN];
} __packed __awigned(2);

stwuct ieee80211_cts {
	__we16 fwame_contwow;
	__we16 duwation;
	u8 wa[ETH_AWEN];
} __packed __awigned(2);

stwuct ieee80211_pspoww {
	__we16 fwame_contwow;
	__we16 aid;
	u8 bssid[ETH_AWEN];
	u8 ta[ETH_AWEN];
} __packed __awigned(2);

/* TDWS */

/* Channew switch timing */
stwuct ieee80211_ch_switch_timing {
	__we16 switch_time;
	__we16 switch_timeout;
} __packed;

/* Wink-id infowmation ewement */
stwuct ieee80211_tdws_wnkie {
	u8 ie_type; /* Wink Identifiew IE */
	u8 ie_wen;
	u8 bssid[ETH_AWEN];
	u8 init_sta[ETH_AWEN];
	u8 wesp_sta[ETH_AWEN];
} __packed;

stwuct ieee80211_tdws_data {
	u8 da[ETH_AWEN];
	u8 sa[ETH_AWEN];
	__be16 ethew_type;
	u8 paywoad_type;
	u8 categowy;
	u8 action_code;
	union {
		stwuct {
			u8 diawog_token;
			__we16 capabiwity;
			u8 vawiabwe[0];
		} __packed setup_weq;
		stwuct {
			__we16 status_code;
			u8 diawog_token;
			__we16 capabiwity;
			u8 vawiabwe[0];
		} __packed setup_wesp;
		stwuct {
			__we16 status_code;
			u8 diawog_token;
			u8 vawiabwe[0];
		} __packed setup_cfm;
		stwuct {
			__we16 weason_code;
			u8 vawiabwe[0];
		} __packed teawdown;
		stwuct {
			u8 diawog_token;
			u8 vawiabwe[0];
		} __packed discovew_weq;
		stwuct {
			u8 tawget_channew;
			u8 opew_cwass;
			u8 vawiabwe[0];
		} __packed chan_switch_weq;
		stwuct {
			__we16 status_code;
			u8 vawiabwe[0];
		} __packed chan_switch_wesp;
	} u;
} __packed;

/*
 * Peew-to-Peew IE attwibute wewated definitions.
 */
/*
 * enum ieee80211_p2p_attw_id - identifies type of peew-to-peew attwibute.
 */
enum ieee80211_p2p_attw_id {
	IEEE80211_P2P_ATTW_STATUS = 0,
	IEEE80211_P2P_ATTW_MINOW_WEASON,
	IEEE80211_P2P_ATTW_CAPABIWITY,
	IEEE80211_P2P_ATTW_DEVICE_ID,
	IEEE80211_P2P_ATTW_GO_INTENT,
	IEEE80211_P2P_ATTW_GO_CONFIG_TIMEOUT,
	IEEE80211_P2P_ATTW_WISTEN_CHANNEW,
	IEEE80211_P2P_ATTW_GWOUP_BSSID,
	IEEE80211_P2P_ATTW_EXT_WISTEN_TIMING,
	IEEE80211_P2P_ATTW_INTENDED_IFACE_ADDW,
	IEEE80211_P2P_ATTW_MANAGABIWITY,
	IEEE80211_P2P_ATTW_CHANNEW_WIST,
	IEEE80211_P2P_ATTW_ABSENCE_NOTICE,
	IEEE80211_P2P_ATTW_DEVICE_INFO,
	IEEE80211_P2P_ATTW_GWOUP_INFO,
	IEEE80211_P2P_ATTW_GWOUP_ID,
	IEEE80211_P2P_ATTW_INTEWFACE,
	IEEE80211_P2P_ATTW_OPEW_CHANNEW,
	IEEE80211_P2P_ATTW_INVITE_FWAGS,
	/* 19 - 220: Wesewved */
	IEEE80211_P2P_ATTW_VENDOW_SPECIFIC = 221,

	IEEE80211_P2P_ATTW_MAX
};

/* Notice of Absence attwibute - descwibed in P2P spec 4.1.14 */
/* Typicaw max vawue used hewe */
#define IEEE80211_P2P_NOA_DESC_MAX	4

stwuct ieee80211_p2p_noa_desc {
	u8 count;
	__we32 duwation;
	__we32 intewvaw;
	__we32 stawt_time;
} __packed;

stwuct ieee80211_p2p_noa_attw {
	u8 index;
	u8 oppps_ctwindow;
	stwuct ieee80211_p2p_noa_desc desc[IEEE80211_P2P_NOA_DESC_MAX];
} __packed;

#define IEEE80211_P2P_OPPPS_ENABWE_BIT		BIT(7)
#define IEEE80211_P2P_OPPPS_CTWINDOW_MASK	0x7F

/**
 * stwuct ieee80211_baw - Bwock Ack Wequest fwame fowmat
 * @fwame_contwow: Fwame Contwow
 * @duwation: Duwation
 * @wa: WA
 * @ta: TA
 * @contwow: BAW Contwow
 * @stawt_seq_num: Stawting Sequence Numbew (see Figuwe 9-37)
 *
 * This stwuctuwe wepwesents the "BwockAckWeq fwame fowmat"
 * as descwibed in IEEE Std 802.11-2020 section 9.3.1.7.
*/
stwuct ieee80211_baw {
	__we16 fwame_contwow;
	__we16 duwation;
	__u8 wa[ETH_AWEN];
	__u8 ta[ETH_AWEN];
	__we16 contwow;
	__we16 stawt_seq_num;
} __packed;

/* 802.11 BAW contwow masks */
#define IEEE80211_BAW_CTWW_ACK_POWICY_NOWMAW	0x0000
#define IEEE80211_BAW_CTWW_MUWTI_TID		0x0002
#define IEEE80211_BAW_CTWW_CBMTID_COMPWESSED_BA	0x0004
#define IEEE80211_BAW_CTWW_TID_INFO_MASK	0xf000
#define IEEE80211_BAW_CTWW_TID_INFO_SHIFT	12

#define IEEE80211_HT_MCS_MASK_WEN		10

/**
 * stwuct ieee80211_mcs_info - Suppowted MCS Set fiewd
 * @wx_mask: WX mask
 * @wx_highest: highest suppowted WX wate. If set wepwesents
 *	the highest suppowted WX data wate in units of 1 Mbps.
 *	If this fiewd is 0 this vawue shouwd not be used to
 *	considew the highest WX data wate suppowted.
 * @tx_pawams: TX pawametews
 * @wesewved: Wesewved bits
 *
 * This stwuctuwe wepwesents the "Suppowted MCS Set fiewd" as
 * descwibed in IEEE Std 802.11-2020 section 9.4.2.55.4.
 */
stwuct ieee80211_mcs_info {
	u8 wx_mask[IEEE80211_HT_MCS_MASK_WEN];
	__we16 wx_highest;
	u8 tx_pawams;
	u8 wesewved[3];
} __packed;

/* 802.11n HT capabiwity MSC set */
#define IEEE80211_HT_MCS_WX_HIGHEST_MASK	0x3ff
#define IEEE80211_HT_MCS_TX_DEFINED		0x01
#define IEEE80211_HT_MCS_TX_WX_DIFF		0x02
/* vawue 0 == 1 stweam etc */
#define IEEE80211_HT_MCS_TX_MAX_STWEAMS_MASK	0x0C
#define IEEE80211_HT_MCS_TX_MAX_STWEAMS_SHIFT	2
#define		IEEE80211_HT_MCS_TX_MAX_STWEAMS	4
#define IEEE80211_HT_MCS_TX_UNEQUAW_MODUWATION	0x10

#define IEEE80211_HT_MCS_CHAINS(mcs) ((mcs) == 32 ? 1 : (1 + ((mcs) >> 3)))

/*
 * 802.11n D5.0 20.3.5 / 20.6 says:
 * - indices 0 to 7 and 32 awe singwe spatiaw stweam
 * - 8 to 31 awe muwtipwe spatiaw stweams using equaw moduwation
 *   [8..15 fow two stweams, 16..23 fow thwee and 24..31 fow fouw]
 * - wemaindew awe muwtipwe spatiaw stweams using unequaw moduwation
 */
#define IEEE80211_HT_MCS_UNEQUAW_MODUWATION_STAWT 33
#define IEEE80211_HT_MCS_UNEQUAW_MODUWATION_STAWT_BYTE \
	(IEEE80211_HT_MCS_UNEQUAW_MODUWATION_STAWT / 8)

/**
 * stwuct ieee80211_ht_cap - HT capabiwities ewement
 * @cap_info: HT Capabiwity Infowmation
 * @ampdu_pawams_info: A-MPDU Pawametews
 * @mcs: Suppowted MCS Set
 * @extended_ht_cap_info: HT Extended Capabiwities
 * @tx_BF_cap_info: Twansmit Beamfowming Capabiwities
 * @antenna_sewection_info: ASEW Capabiwity
 *
 * This stwuctuwe wepwesents the paywoad of the "HT Capabiwities
 * ewement" as descwibed in IEEE Std 802.11-2020 section 9.4.2.55.
 */
stwuct ieee80211_ht_cap {
	__we16 cap_info;
	u8 ampdu_pawams_info;

	/* 16 bytes MCS infowmation */
	stwuct ieee80211_mcs_info mcs;

	__we16 extended_ht_cap_info;
	__we32 tx_BF_cap_info;
	u8 antenna_sewection_info;
} __packed;

/* 802.11n HT capabiwities masks (fow cap_info) */
#define IEEE80211_HT_CAP_WDPC_CODING		0x0001
#define IEEE80211_HT_CAP_SUP_WIDTH_20_40	0x0002
#define IEEE80211_HT_CAP_SM_PS			0x000C
#define		IEEE80211_HT_CAP_SM_PS_SHIFT	2
#define IEEE80211_HT_CAP_GWN_FWD		0x0010
#define IEEE80211_HT_CAP_SGI_20			0x0020
#define IEEE80211_HT_CAP_SGI_40			0x0040
#define IEEE80211_HT_CAP_TX_STBC		0x0080
#define IEEE80211_HT_CAP_WX_STBC		0x0300
#define		IEEE80211_HT_CAP_WX_STBC_SHIFT	8
#define IEEE80211_HT_CAP_DEWAY_BA		0x0400
#define IEEE80211_HT_CAP_MAX_AMSDU		0x0800
#define IEEE80211_HT_CAP_DSSSCCK40		0x1000
#define IEEE80211_HT_CAP_WESEWVED		0x2000
#define IEEE80211_HT_CAP_40MHZ_INTOWEWANT	0x4000
#define IEEE80211_HT_CAP_WSIG_TXOP_PWOT		0x8000

/* 802.11n HT extended capabiwities masks (fow extended_ht_cap_info) */
#define IEEE80211_HT_EXT_CAP_PCO		0x0001
#define IEEE80211_HT_EXT_CAP_PCO_TIME		0x0006
#define		IEEE80211_HT_EXT_CAP_PCO_TIME_SHIFT	1
#define IEEE80211_HT_EXT_CAP_MCS_FB		0x0300
#define		IEEE80211_HT_EXT_CAP_MCS_FB_SHIFT	8
#define IEEE80211_HT_EXT_CAP_HTC_SUP		0x0400
#define IEEE80211_HT_EXT_CAP_WD_WESPONDEW	0x0800

/* 802.11n HT capabiwity AMPDU settings (fow ampdu_pawams_info) */
#define IEEE80211_HT_AMPDU_PAWM_FACTOW		0x03
#define IEEE80211_HT_AMPDU_PAWM_DENSITY		0x1C
#define		IEEE80211_HT_AMPDU_PAWM_DENSITY_SHIFT	2

/*
 * Maximum wength of AMPDU that the STA can weceive in high-thwoughput (HT).
 * Wength = 2 ^ (13 + max_ampdu_wength_exp) - 1 (octets)
 */
enum ieee80211_max_ampdu_wength_exp {
	IEEE80211_HT_MAX_AMPDU_8K = 0,
	IEEE80211_HT_MAX_AMPDU_16K = 1,
	IEEE80211_HT_MAX_AMPDU_32K = 2,
	IEEE80211_HT_MAX_AMPDU_64K = 3
};

/*
 * Maximum wength of AMPDU that the STA can weceive in VHT.
 * Wength = 2 ^ (13 + max_ampdu_wength_exp) - 1 (octets)
 */
enum ieee80211_vht_max_ampdu_wength_exp {
	IEEE80211_VHT_MAX_AMPDU_8K = 0,
	IEEE80211_VHT_MAX_AMPDU_16K = 1,
	IEEE80211_VHT_MAX_AMPDU_32K = 2,
	IEEE80211_VHT_MAX_AMPDU_64K = 3,
	IEEE80211_VHT_MAX_AMPDU_128K = 4,
	IEEE80211_VHT_MAX_AMPDU_256K = 5,
	IEEE80211_VHT_MAX_AMPDU_512K = 6,
	IEEE80211_VHT_MAX_AMPDU_1024K = 7
};

#define IEEE80211_HT_MAX_AMPDU_FACTOW 13

/* Minimum MPDU stawt spacing */
enum ieee80211_min_mpdu_spacing {
	IEEE80211_HT_MPDU_DENSITY_NONE = 0,	/* No westwiction */
	IEEE80211_HT_MPDU_DENSITY_0_25 = 1,	/* 1/4 usec */
	IEEE80211_HT_MPDU_DENSITY_0_5 = 2,	/* 1/2 usec */
	IEEE80211_HT_MPDU_DENSITY_1 = 3,	/* 1 usec */
	IEEE80211_HT_MPDU_DENSITY_2 = 4,	/* 2 usec */
	IEEE80211_HT_MPDU_DENSITY_4 = 5,	/* 4 usec */
	IEEE80211_HT_MPDU_DENSITY_8 = 6,	/* 8 usec */
	IEEE80211_HT_MPDU_DENSITY_16 = 7	/* 16 usec */
};

/**
 * stwuct ieee80211_ht_opewation - HT opewation IE
 * @pwimawy_chan: Pwimawy Channew
 * @ht_pawam: HT Opewation Infowmation pawametews
 * @opewation_mode: HT Opewation Infowmation opewation mode
 * @stbc_pawam: HT Opewation Infowmation STBC pawams
 * @basic_set: Basic HT-MCS Set
 *
 * This stwuctuwe wepwesents the paywoad of the "HT Opewation
 * ewement" as descwibed in IEEE Std 802.11-2020 section 9.4.2.56.
 */
stwuct ieee80211_ht_opewation {
	u8 pwimawy_chan;
	u8 ht_pawam;
	__we16 opewation_mode;
	__we16 stbc_pawam;
	u8 basic_set[16];
} __packed;

/* fow ht_pawam */
#define IEEE80211_HT_PAWAM_CHA_SEC_OFFSET		0x03
#define		IEEE80211_HT_PAWAM_CHA_SEC_NONE		0x00
#define		IEEE80211_HT_PAWAM_CHA_SEC_ABOVE	0x01
#define		IEEE80211_HT_PAWAM_CHA_SEC_BEWOW	0x03
#define IEEE80211_HT_PAWAM_CHAN_WIDTH_ANY		0x04
#define IEEE80211_HT_PAWAM_WIFS_MODE			0x08

/* fow opewation_mode */
#define IEEE80211_HT_OP_MODE_PWOTECTION			0x0003
#define		IEEE80211_HT_OP_MODE_PWOTECTION_NONE		0
#define		IEEE80211_HT_OP_MODE_PWOTECTION_NONMEMBEW	1
#define		IEEE80211_HT_OP_MODE_PWOTECTION_20MHZ		2
#define		IEEE80211_HT_OP_MODE_PWOTECTION_NONHT_MIXED	3
#define IEEE80211_HT_OP_MODE_NON_GF_STA_PWSNT		0x0004
#define IEEE80211_HT_OP_MODE_NON_HT_STA_PWSNT		0x0010
#define IEEE80211_HT_OP_MODE_CCFS2_SHIFT		5
#define IEEE80211_HT_OP_MODE_CCFS2_MASK			0x1fe0

/* fow stbc_pawam */
#define IEEE80211_HT_STBC_PAWAM_DUAW_BEACON		0x0040
#define IEEE80211_HT_STBC_PAWAM_DUAW_CTS_PWOT		0x0080
#define IEEE80211_HT_STBC_PAWAM_STBC_BEACON		0x0100
#define IEEE80211_HT_STBC_PAWAM_WSIG_TXOP_FUWWPWOT	0x0200
#define IEEE80211_HT_STBC_PAWAM_PCO_ACTIVE		0x0400
#define IEEE80211_HT_STBC_PAWAM_PCO_PHASE		0x0800


/* bwock-ack pawametews */
#define IEEE80211_ADDBA_PAWAM_AMSDU_MASK 0x0001
#define IEEE80211_ADDBA_PAWAM_POWICY_MASK 0x0002
#define IEEE80211_ADDBA_PAWAM_TID_MASK 0x003C
#define IEEE80211_ADDBA_PAWAM_BUF_SIZE_MASK 0xFFC0
#define IEEE80211_DEWBA_PAWAM_TID_MASK 0xF000
#define IEEE80211_DEWBA_PAWAM_INITIATOW_MASK 0x0800

/*
 * A-MPDU buffew sizes
 * Accowding to HT size vawies fwom 8 to 64 fwames
 * HE adds the abiwity to have up to 256 fwames.
 * EHT adds the abiwity to have up to 1K fwames.
 */
#define IEEE80211_MIN_AMPDU_BUF		0x8
#define IEEE80211_MAX_AMPDU_BUF_HT	0x40
#define IEEE80211_MAX_AMPDU_BUF_HE	0x100
#define IEEE80211_MAX_AMPDU_BUF_EHT	0x400


/* Spatiaw Muwtipwexing Powew Save Modes (fow capabiwity) */
#define WWAN_HT_CAP_SM_PS_STATIC	0
#define WWAN_HT_CAP_SM_PS_DYNAMIC	1
#define WWAN_HT_CAP_SM_PS_INVAWID	2
#define WWAN_HT_CAP_SM_PS_DISABWED	3

/* fow SM powew contwow fiewd wowew two bits */
#define WWAN_HT_SMPS_CONTWOW_DISABWED	0
#define WWAN_HT_SMPS_CONTWOW_STATIC	1
#define WWAN_HT_SMPS_CONTWOW_DYNAMIC	3

/**
 * stwuct ieee80211_vht_mcs_info - VHT MCS infowmation
 * @wx_mcs_map: WX MCS map 2 bits fow each stweam, totaw 8 stweams
 * @wx_highest: Indicates highest wong GI VHT PPDU data wate
 *	STA can weceive. Wate expwessed in units of 1 Mbps.
 *	If this fiewd is 0 this vawue shouwd not be used to
 *	considew the highest WX data wate suppowted.
 *	The top 3 bits of this fiewd indicate the Maximum NSTS,totaw
 *	(a beamfowmee capabiwity.)
 * @tx_mcs_map: TX MCS map 2 bits fow each stweam, totaw 8 stweams
 * @tx_highest: Indicates highest wong GI VHT PPDU data wate
 *	STA can twansmit. Wate expwessed in units of 1 Mbps.
 *	If this fiewd is 0 this vawue shouwd not be used to
 *	considew the highest TX data wate suppowted.
 *	The top 2 bits of this fiewd awe wesewved, the
 *	3wd bit fwom the top indiciates VHT Extended NSS BW
 *	Capabiwity.
 */
stwuct ieee80211_vht_mcs_info {
	__we16 wx_mcs_map;
	__we16 wx_highest;
	__we16 tx_mcs_map;
	__we16 tx_highest;
} __packed;

/* fow wx_highest */
#define IEEE80211_VHT_MAX_NSTS_TOTAW_SHIFT	13
#define IEEE80211_VHT_MAX_NSTS_TOTAW_MASK	(7 << IEEE80211_VHT_MAX_NSTS_TOTAW_SHIFT)

/* fow tx_highest */
#define IEEE80211_VHT_EXT_NSS_BW_CAPABWE	(1 << 13)

/**
 * enum ieee80211_vht_mcs_suppowt - VHT MCS suppowt definitions
 * @IEEE80211_VHT_MCS_SUPPOWT_0_7: MCSes 0-7 awe suppowted fow the
 *	numbew of stweams
 * @IEEE80211_VHT_MCS_SUPPOWT_0_8: MCSes 0-8 awe suppowted
 * @IEEE80211_VHT_MCS_SUPPOWT_0_9: MCSes 0-9 awe suppowted
 * @IEEE80211_VHT_MCS_NOT_SUPPOWTED: This numbew of stweams isn't suppowted
 *
 * These definitions awe used in each 2-bit subfiewd of the @wx_mcs_map
 * and @tx_mcs_map fiewds of &stwuct ieee80211_vht_mcs_info, which awe
 * both spwit into 8 subfiewds by numbew of stweams. These vawues indicate
 * which MCSes awe suppowted fow the numbew of stweams the vawue appeaws
 * fow.
 */
enum ieee80211_vht_mcs_suppowt {
	IEEE80211_VHT_MCS_SUPPOWT_0_7	= 0,
	IEEE80211_VHT_MCS_SUPPOWT_0_8	= 1,
	IEEE80211_VHT_MCS_SUPPOWT_0_9	= 2,
	IEEE80211_VHT_MCS_NOT_SUPPOWTED	= 3,
};

/**
 * stwuct ieee80211_vht_cap - VHT capabiwities
 *
 * This stwuctuwe is the "VHT capabiwities ewement" as
 * descwibed in 802.11ac D3.0 8.4.2.160
 * @vht_cap_info: VHT capabiwity info
 * @supp_mcs: VHT MCS suppowted wates
 */
stwuct ieee80211_vht_cap {
	__we32 vht_cap_info;
	stwuct ieee80211_vht_mcs_info supp_mcs;
} __packed;

/**
 * enum ieee80211_vht_chanwidth - VHT channew width
 * @IEEE80211_VHT_CHANWIDTH_USE_HT: use the HT opewation IE to
 *	detewmine the channew width (20 ow 40 MHz)
 * @IEEE80211_VHT_CHANWIDTH_80MHZ: 80 MHz bandwidth
 * @IEEE80211_VHT_CHANWIDTH_160MHZ: 160 MHz bandwidth
 * @IEEE80211_VHT_CHANWIDTH_80P80MHZ: 80+80 MHz bandwidth
 */
enum ieee80211_vht_chanwidth {
	IEEE80211_VHT_CHANWIDTH_USE_HT		= 0,
	IEEE80211_VHT_CHANWIDTH_80MHZ		= 1,
	IEEE80211_VHT_CHANWIDTH_160MHZ		= 2,
	IEEE80211_VHT_CHANWIDTH_80P80MHZ	= 3,
};

/**
 * stwuct ieee80211_vht_opewation - VHT opewation IE
 *
 * This stwuctuwe is the "VHT opewation ewement" as
 * descwibed in 802.11ac D3.0 8.4.2.161
 * @chan_width: Opewating channew width
 * @centew_fweq_seg0_idx: centew fweq segment 0 index
 * @centew_fweq_seg1_idx: centew fweq segment 1 index
 * @basic_mcs_set: VHT Basic MCS wate set
 */
stwuct ieee80211_vht_opewation {
	u8 chan_width;
	u8 centew_fweq_seg0_idx;
	u8 centew_fweq_seg1_idx;
	__we16 basic_mcs_set;
} __packed;

/**
 * stwuct ieee80211_he_cap_ewem - HE capabiwities ewement
 * @mac_cap_info: HE MAC Capabiwities Infowmation
 * @phy_cap_info: HE PHY Capabiwities Infowmation
 *
 * This stwuctuwe wepwesents the fixed fiewds of the paywoad of the
 * "HE capabiwities ewement" as descwibed in IEEE Std 802.11ax-2021
 * sections 9.4.2.248.2 and 9.4.2.248.3.
 */
stwuct ieee80211_he_cap_ewem {
	u8 mac_cap_info[6];
	u8 phy_cap_info[11];
} __packed;

#define IEEE80211_TX_WX_MCS_NSS_DESC_MAX_WEN	5

/**
 * enum ieee80211_he_mcs_suppowt - HE MCS suppowt definitions
 * @IEEE80211_HE_MCS_SUPPOWT_0_7: MCSes 0-7 awe suppowted fow the
 *	numbew of stweams
 * @IEEE80211_HE_MCS_SUPPOWT_0_9: MCSes 0-9 awe suppowted
 * @IEEE80211_HE_MCS_SUPPOWT_0_11: MCSes 0-11 awe suppowted
 * @IEEE80211_HE_MCS_NOT_SUPPOWTED: This numbew of stweams isn't suppowted
 *
 * These definitions awe used in each 2-bit subfiewd of the wx_mcs_*
 * and tx_mcs_* fiewds of &stwuct ieee80211_he_mcs_nss_supp, which awe
 * both spwit into 8 subfiewds by numbew of stweams. These vawues indicate
 * which MCSes awe suppowted fow the numbew of stweams the vawue appeaws
 * fow.
 */
enum ieee80211_he_mcs_suppowt {
	IEEE80211_HE_MCS_SUPPOWT_0_7	= 0,
	IEEE80211_HE_MCS_SUPPOWT_0_9	= 1,
	IEEE80211_HE_MCS_SUPPOWT_0_11	= 2,
	IEEE80211_HE_MCS_NOT_SUPPOWTED	= 3,
};

/**
 * stwuct ieee80211_he_mcs_nss_supp - HE Tx/Wx HE MCS NSS Suppowt Fiewd
 *
 * This stwuctuwe howds the data wequiwed fow the Tx/Wx HE MCS NSS Suppowt Fiewd
 * descwibed in P802.11ax_D2.0 section 9.4.2.237.4
 *
 * @wx_mcs_80: Wx MCS map 2 bits fow each stweam, totaw 8 stweams, fow channew
 *     widths wess than 80MHz.
 * @tx_mcs_80: Tx MCS map 2 bits fow each stweam, totaw 8 stweams, fow channew
 *     widths wess than 80MHz.
 * @wx_mcs_160: Wx MCS map 2 bits fow each stweam, totaw 8 stweams, fow channew
 *     width 160MHz.
 * @tx_mcs_160: Tx MCS map 2 bits fow each stweam, totaw 8 stweams, fow channew
 *     width 160MHz.
 * @wx_mcs_80p80: Wx MCS map 2 bits fow each stweam, totaw 8 stweams, fow
 *     channew width 80p80MHz.
 * @tx_mcs_80p80: Tx MCS map 2 bits fow each stweam, totaw 8 stweams, fow
 *     channew width 80p80MHz.
 */
stwuct ieee80211_he_mcs_nss_supp {
	__we16 wx_mcs_80;
	__we16 tx_mcs_80;
	__we16 wx_mcs_160;
	__we16 tx_mcs_160;
	__we16 wx_mcs_80p80;
	__we16 tx_mcs_80p80;
} __packed;

/**
 * stwuct ieee80211_he_opewation - HE Opewation ewement
 * @he_opew_pawams: HE Opewation Pawametews + BSS Cowow Infowmation
 * @he_mcs_nss_set: Basic HE-MCS And NSS Set
 * @optionaw: Optionaw fiewds VHT Opewation Infowmation, Max Co-Hosted
 *            BSSID Indicatow, and 6 GHz Opewation Infowmation
 *
 * This stwuctuwe wepwesents the paywoad of the "HE Opewation
 * ewement" as descwibed in IEEE Std 802.11ax-2021 section 9.4.2.249.
 */
stwuct ieee80211_he_opewation {
	__we32 he_opew_pawams;
	__we16 he_mcs_nss_set;
	u8 optionaw[];
} __packed;

/**
 * stwuct ieee80211_he_spw - Spatiaw Weuse Pawametew Set ewement
 * @he_sw_contwow: SW Contwow
 * @optionaw: Optionaw fiewds Non-SWG OBSS PD Max Offset, SWG OBSS PD
 *            Min Offset, SWG OBSS PD Max Offset, SWG BSS Cowow
 *            Bitmap, and SWG Pawtiaw BSSID Bitmap
 *
 * This stwuctuwe wepwesents the paywoad of the "Spatiaw Weuse
 * Pawametew Set ewement" as descwibed in IEEE Std 802.11ax-2021
 * section 9.4.2.252.
 */
stwuct ieee80211_he_spw {
	u8 he_sw_contwow;
	u8 optionaw[];
} __packed;

/**
 * stwuct ieee80211_he_mu_edca_pawam_ac_wec - MU AC Pawametew Wecowd fiewd
 * @aifsn: ACI/AIFSN
 * @ecw_min_max: ECWmin/ECWmax
 * @mu_edca_timew: MU EDCA Timew
 *
 * This stwuctuwe wepwesents the "MU AC Pawametew Wecowd" as descwibed
 * in IEEE Std 802.11ax-2021 section 9.4.2.251, Figuwe 9-788p.
 */
stwuct ieee80211_he_mu_edca_pawam_ac_wec {
	u8 aifsn;
	u8 ecw_min_max;
	u8 mu_edca_timew;
} __packed;

/**
 * stwuct ieee80211_mu_edca_pawam_set - MU EDCA Pawametew Set ewement
 * @mu_qos_info: QoS Info
 * @ac_be: MU AC_BE Pawametew Wecowd
 * @ac_bk: MU AC_BK Pawametew Wecowd
 * @ac_vi: MU AC_VI Pawametew Wecowd
 * @ac_vo: MU AC_VO Pawametew Wecowd
 *
 * This stwuctuwe wepwesents the paywoad of the "MU EDCA Pawametew Set
 * ewement" as descwibed in IEEE Std 802.11ax-2021 section 9.4.2.251.
 */
stwuct ieee80211_mu_edca_pawam_set {
	u8 mu_qos_info;
	stwuct ieee80211_he_mu_edca_pawam_ac_wec ac_be;
	stwuct ieee80211_he_mu_edca_pawam_ac_wec ac_bk;
	stwuct ieee80211_he_mu_edca_pawam_ac_wec ac_vi;
	stwuct ieee80211_he_mu_edca_pawam_ac_wec ac_vo;
} __packed;

#define IEEE80211_EHT_MCS_NSS_WX 0x0f
#define IEEE80211_EHT_MCS_NSS_TX 0xf0

/**
 * stwuct ieee80211_eht_mcs_nss_supp_20mhz_onwy - EHT 20MHz onwy station max
 * suppowted NSS fow pew MCS.
 *
 * Fow each fiewd bewow, bits 0 - 3 indicate the maximaw numbew of spatiaw
 * stweams fow Wx, and bits 4 - 7 indicate the maximaw numbew of spatiaw stweams
 * fow Tx.
 *
 * @wx_tx_mcs7_max_nss: indicates the maximum numbew of spatiaw stweams
 *     suppowted fow weception and the maximum numbew of spatiaw stweams
 *     suppowted fow twansmission fow MCS 0 - 7.
 * @wx_tx_mcs9_max_nss: indicates the maximum numbew of spatiaw stweams
 *     suppowted fow weception and the maximum numbew of spatiaw stweams
 *     suppowted fow twansmission fow MCS 8 - 9.
 * @wx_tx_mcs11_max_nss: indicates the maximum numbew of spatiaw stweams
 *     suppowted fow weception and the maximum numbew of spatiaw stweams
 *     suppowted fow twansmission fow MCS 10 - 11.
 * @wx_tx_mcs13_max_nss: indicates the maximum numbew of spatiaw stweams
 *     suppowted fow weception and the maximum numbew of spatiaw stweams
 *     suppowted fow twansmission fow MCS 12 - 13.
 * @wx_tx_max_nss: awway of the pwevious fiewds fow easiew woop access
 */
stwuct ieee80211_eht_mcs_nss_supp_20mhz_onwy {
	union {
		stwuct {
			u8 wx_tx_mcs7_max_nss;
			u8 wx_tx_mcs9_max_nss;
			u8 wx_tx_mcs11_max_nss;
			u8 wx_tx_mcs13_max_nss;
		};
		u8 wx_tx_max_nss[4];
	};
};

/**
 * stwuct ieee80211_eht_mcs_nss_supp_bw - EHT max suppowted NSS pew MCS (except
 * 20MHz onwy stations).
 *
 * Fow each fiewd bewow, bits 0 - 3 indicate the maximaw numbew of spatiaw
 * stweams fow Wx, and bits 4 - 7 indicate the maximaw numbew of spatiaw stweams
 * fow Tx.
 *
 * @wx_tx_mcs9_max_nss: indicates the maximum numbew of spatiaw stweams
 *     suppowted fow weception and the maximum numbew of spatiaw stweams
 *     suppowted fow twansmission fow MCS 0 - 9.
 * @wx_tx_mcs11_max_nss: indicates the maximum numbew of spatiaw stweams
 *     suppowted fow weception and the maximum numbew of spatiaw stweams
 *     suppowted fow twansmission fow MCS 10 - 11.
 * @wx_tx_mcs13_max_nss: indicates the maximum numbew of spatiaw stweams
 *     suppowted fow weception and the maximum numbew of spatiaw stweams
 *     suppowted fow twansmission fow MCS 12 - 13.
 * @wx_tx_max_nss: awway of the pwevious fiewds fow easiew woop access
 */
stwuct ieee80211_eht_mcs_nss_supp_bw {
	union {
		stwuct {
			u8 wx_tx_mcs9_max_nss;
			u8 wx_tx_mcs11_max_nss;
			u8 wx_tx_mcs13_max_nss;
		};
		u8 wx_tx_max_nss[3];
	};
};

/**
 * stwuct ieee80211_eht_cap_ewem_fixed - EHT capabiwities fixed data
 *
 * This stwuctuwe is the "EHT Capabiwities ewement" fixed fiewds as
 * descwibed in P802.11be_D2.0 section 9.4.2.313.
 *
 * @mac_cap_info: MAC capabiwities, see IEEE80211_EHT_MAC_CAP*
 * @phy_cap_info: PHY capabiwities, see IEEE80211_EHT_PHY_CAP*
 */
stwuct ieee80211_eht_cap_ewem_fixed {
	u8 mac_cap_info[2];
	u8 phy_cap_info[9];
} __packed;

/**
 * stwuct ieee80211_eht_cap_ewem - EHT capabiwities ewement
 * @fixed: fixed pawts, see &ieee80211_eht_cap_ewem_fixed
 * @optionaw: optionaw pawts
 */
stwuct ieee80211_eht_cap_ewem {
	stwuct ieee80211_eht_cap_ewem_fixed fixed;

	/*
	 * Fowwowed by:
	 * Suppowted EHT-MCS And NSS Set fiewd: 4, 3, 6 ow 9 octets.
	 * EHT PPE Thweshowds fiewd: vawiabwe wength.
	 */
	u8 optionaw[];
} __packed;

#define IEEE80211_EHT_OPEW_INFO_PWESENT	                        0x01
#define IEEE80211_EHT_OPEW_DISABWED_SUBCHANNEW_BITMAP_PWESENT	0x02
#define IEEE80211_EHT_OPEW_EHT_DEF_PE_DUWATION	                0x04
#define IEEE80211_EHT_OPEW_GWOUP_ADDWESSED_BU_IND_WIMIT         0x08
#define IEEE80211_EHT_OPEW_GWOUP_ADDWESSED_BU_IND_EXP_MASK      0x30

/**
 * stwuct ieee80211_eht_opewation - eht opewation ewement
 *
 * This stwuctuwe is the "EHT Opewation Ewement" fiewds as
 * descwibed in P802.11be_D2.0 section 9.4.2.311
 *
 * @pawams: EHT opewation ewement pawametews. See &IEEE80211_EHT_OPEW_*
 * @basic_mcs_nss: indicates the EHT-MCSs fow each numbew of spatiaw stweams in
 *     EHT PPDUs that awe suppowted by aww EHT STAs in the BSS in twansmit and
 *     weceive.
 * @optionaw: optionaw pawts
 */
stwuct ieee80211_eht_opewation {
	u8 pawams;
	stwuct ieee80211_eht_mcs_nss_supp_20mhz_onwy basic_mcs_nss;
	u8 optionaw[];
} __packed;

/**
 * stwuct ieee80211_eht_opewation_info - eht opewation infowmation
 *
 * @contwow: EHT opewation infowmation contwow.
 * @ccfs0: defines a channew centew fwequency fow a 20, 40, 80, 160, ow 320 MHz
 *     EHT BSS.
 * @ccfs1: defines a channew centew fwequency fow a 160 ow 320 MHz EHT BSS.
 * @optionaw: optionaw pawts
 */
stwuct ieee80211_eht_opewation_info {
	u8 contwow;
	u8 ccfs0;
	u8 ccfs1;
	u8 optionaw[];
} __packed;

/* 802.11ac VHT Capabiwities */
#define IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_3895			0x00000000
#define IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_7991			0x00000001
#define IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_11454			0x00000002
#define IEEE80211_VHT_CAP_MAX_MPDU_MASK				0x00000003
#define IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ		0x00000004
#define IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PWUS80MHZ	0x00000008
#define IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK			0x0000000C
#define IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_SHIFT			2
#define IEEE80211_VHT_CAP_WXWDPC				0x00000010
#define IEEE80211_VHT_CAP_SHOWT_GI_80				0x00000020
#define IEEE80211_VHT_CAP_SHOWT_GI_160				0x00000040
#define IEEE80211_VHT_CAP_TXSTBC				0x00000080
#define IEEE80211_VHT_CAP_WXSTBC_1				0x00000100
#define IEEE80211_VHT_CAP_WXSTBC_2				0x00000200
#define IEEE80211_VHT_CAP_WXSTBC_3				0x00000300
#define IEEE80211_VHT_CAP_WXSTBC_4				0x00000400
#define IEEE80211_VHT_CAP_WXSTBC_MASK				0x00000700
#define IEEE80211_VHT_CAP_WXSTBC_SHIFT				8
#define IEEE80211_VHT_CAP_SU_BEAMFOWMEW_CAPABWE			0x00000800
#define IEEE80211_VHT_CAP_SU_BEAMFOWMEE_CAPABWE			0x00001000
#define IEEE80211_VHT_CAP_BEAMFOWMEE_STS_SHIFT                  13
#define IEEE80211_VHT_CAP_BEAMFOWMEE_STS_MASK			\
		(7 << IEEE80211_VHT_CAP_BEAMFOWMEE_STS_SHIFT)
#define IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_SHIFT		16
#define IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK		\
		(7 << IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_SHIFT)
#define IEEE80211_VHT_CAP_MU_BEAMFOWMEW_CAPABWE			0x00080000
#define IEEE80211_VHT_CAP_MU_BEAMFOWMEE_CAPABWE			0x00100000
#define IEEE80211_VHT_CAP_VHT_TXOP_PS				0x00200000
#define IEEE80211_VHT_CAP_HTC_VHT				0x00400000
#define IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_SHIFT	23
#define IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_MASK	\
		(7 << IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_SHIFT)
#define IEEE80211_VHT_CAP_VHT_WINK_ADAPTATION_VHT_UNSOW_MFB	0x08000000
#define IEEE80211_VHT_CAP_VHT_WINK_ADAPTATION_VHT_MWQ_MFB	0x0c000000
#define IEEE80211_VHT_CAP_WX_ANTENNA_PATTEWN			0x10000000
#define IEEE80211_VHT_CAP_TX_ANTENNA_PATTEWN			0x20000000
#define IEEE80211_VHT_CAP_EXT_NSS_BW_SHIFT			30
#define IEEE80211_VHT_CAP_EXT_NSS_BW_MASK			0xc0000000

/**
 * ieee80211_get_vht_max_nss - wetuwn max NSS fow a given bandwidth/MCS
 * @cap: VHT capabiwities of the peew
 * @bw: bandwidth to use
 * @mcs: MCS index to use
 * @ext_nss_bw_capabwe: indicates whethew ow not the wocaw twansmittew
 *	(wate scawing awgowithm) can deaw with the new wogic
 *	(dot11VHTExtendedNSSBWCapabwe)
 * @max_vht_nss: cuwwent maximum NSS as advewtised by the STA in
 *	opewating mode notification, can be 0 in which case the
 *	capabiwity data wiww be used to dewive this (fwom MCS suppowt)
 *
 * Due to the VHT Extended NSS Bandwidth Suppowt, the maximum NSS can
 * vawy fow a given BW/MCS. This function pawses the data.
 *
 * Note: This function is expowted by cfg80211.
 */
int ieee80211_get_vht_max_nss(stwuct ieee80211_vht_cap *cap,
			      enum ieee80211_vht_chanwidth bw,
			      int mcs, boow ext_nss_bw_capabwe,
			      unsigned int max_vht_nss);

/**
 * enum ieee80211_ap_weg_powew - weguwatowy powew fow a Access Point
 *
 * @IEEE80211_WEG_UNSET_AP: Access Point has no weguwatowy powew mode
 * @IEEE80211_WEG_WPI_AP: Indoow Access Point
 * @IEEE80211_WEG_SP_AP: Standawd powew Access Point
 * @IEEE80211_WEG_VWP_AP: Vewy wow powew Access Point
 * @IEEE80211_WEG_AP_POWEW_AFTEW_WAST: intewnaw
 * @IEEE80211_WEG_AP_POWEW_MAX: maximum vawue
 */
enum ieee80211_ap_weg_powew {
	IEEE80211_WEG_UNSET_AP,
	IEEE80211_WEG_WPI_AP,
	IEEE80211_WEG_SP_AP,
	IEEE80211_WEG_VWP_AP,
	IEEE80211_WEG_AP_POWEW_AFTEW_WAST,
	IEEE80211_WEG_AP_POWEW_MAX =
		IEEE80211_WEG_AP_POWEW_AFTEW_WAST - 1,
};

/**
 * enum ieee80211_cwient_weg_powew - weguwatowy powew fow a cwient
 *
 * @IEEE80211_WEG_UNSET_CWIENT: Cwient has no weguwatowy powew mode
 * @IEEE80211_WEG_DEFAUWT_CWIENT: Defauwt Cwient
 * @IEEE80211_WEG_SUBOWDINATE_CWIENT: Subowdinate Cwient
 * @IEEE80211_WEG_CWIENT_POWEW_AFTEW_WAST: intewnaw
 * @IEEE80211_WEG_CWIENT_POWEW_MAX: maximum vawue
 */
enum ieee80211_cwient_weg_powew {
	IEEE80211_WEG_UNSET_CWIENT,
	IEEE80211_WEG_DEFAUWT_CWIENT,
	IEEE80211_WEG_SUBOWDINATE_CWIENT,
	IEEE80211_WEG_CWIENT_POWEW_AFTEW_WAST,
	IEEE80211_WEG_CWIENT_POWEW_MAX =
		IEEE80211_WEG_CWIENT_POWEW_AFTEW_WAST - 1,
};

/* 802.11ax HE MAC capabiwities */
#define IEEE80211_HE_MAC_CAP0_HTC_HE				0x01
#define IEEE80211_HE_MAC_CAP0_TWT_WEQ				0x02
#define IEEE80211_HE_MAC_CAP0_TWT_WES				0x04
#define IEEE80211_HE_MAC_CAP0_DYNAMIC_FWAG_NOT_SUPP		0x00
#define IEEE80211_HE_MAC_CAP0_DYNAMIC_FWAG_WEVEW_1		0x08
#define IEEE80211_HE_MAC_CAP0_DYNAMIC_FWAG_WEVEW_2		0x10
#define IEEE80211_HE_MAC_CAP0_DYNAMIC_FWAG_WEVEW_3		0x18
#define IEEE80211_HE_MAC_CAP0_DYNAMIC_FWAG_MASK			0x18
#define IEEE80211_HE_MAC_CAP0_MAX_NUM_FWAG_MSDU_1		0x00
#define IEEE80211_HE_MAC_CAP0_MAX_NUM_FWAG_MSDU_2		0x20
#define IEEE80211_HE_MAC_CAP0_MAX_NUM_FWAG_MSDU_4		0x40
#define IEEE80211_HE_MAC_CAP0_MAX_NUM_FWAG_MSDU_8		0x60
#define IEEE80211_HE_MAC_CAP0_MAX_NUM_FWAG_MSDU_16		0x80
#define IEEE80211_HE_MAC_CAP0_MAX_NUM_FWAG_MSDU_32		0xa0
#define IEEE80211_HE_MAC_CAP0_MAX_NUM_FWAG_MSDU_64		0xc0
#define IEEE80211_HE_MAC_CAP0_MAX_NUM_FWAG_MSDU_UNWIMITED	0xe0
#define IEEE80211_HE_MAC_CAP0_MAX_NUM_FWAG_MSDU_MASK		0xe0

#define IEEE80211_HE_MAC_CAP1_MIN_FWAG_SIZE_UNWIMITED		0x00
#define IEEE80211_HE_MAC_CAP1_MIN_FWAG_SIZE_128			0x01
#define IEEE80211_HE_MAC_CAP1_MIN_FWAG_SIZE_256			0x02
#define IEEE80211_HE_MAC_CAP1_MIN_FWAG_SIZE_512			0x03
#define IEEE80211_HE_MAC_CAP1_MIN_FWAG_SIZE_MASK		0x03
#define IEEE80211_HE_MAC_CAP1_TF_MAC_PAD_DUW_0US		0x00
#define IEEE80211_HE_MAC_CAP1_TF_MAC_PAD_DUW_8US		0x04
#define IEEE80211_HE_MAC_CAP1_TF_MAC_PAD_DUW_16US		0x08
#define IEEE80211_HE_MAC_CAP1_TF_MAC_PAD_DUW_MASK		0x0c
#define IEEE80211_HE_MAC_CAP1_MUWTI_TID_AGG_WX_QOS_1		0x00
#define IEEE80211_HE_MAC_CAP1_MUWTI_TID_AGG_WX_QOS_2		0x10
#define IEEE80211_HE_MAC_CAP1_MUWTI_TID_AGG_WX_QOS_3		0x20
#define IEEE80211_HE_MAC_CAP1_MUWTI_TID_AGG_WX_QOS_4		0x30
#define IEEE80211_HE_MAC_CAP1_MUWTI_TID_AGG_WX_QOS_5		0x40
#define IEEE80211_HE_MAC_CAP1_MUWTI_TID_AGG_WX_QOS_6		0x50
#define IEEE80211_HE_MAC_CAP1_MUWTI_TID_AGG_WX_QOS_7		0x60
#define IEEE80211_HE_MAC_CAP1_MUWTI_TID_AGG_WX_QOS_8		0x70
#define IEEE80211_HE_MAC_CAP1_MUWTI_TID_AGG_WX_QOS_MASK		0x70

/* Wink adaptation is spwit between byte HE_MAC_CAP1 and
 * HE_MAC_CAP2. It shouwd be set onwy if IEEE80211_HE_MAC_CAP0_HTC_HE
 * in which case the fowwowing vawues appwy:
 * 0 = No feedback.
 * 1 = wesewved.
 * 2 = Unsowicited feedback.
 * 3 = both
 */
#define IEEE80211_HE_MAC_CAP1_WINK_ADAPTATION			0x80

#define IEEE80211_HE_MAC_CAP2_WINK_ADAPTATION			0x01
#define IEEE80211_HE_MAC_CAP2_AWW_ACK				0x02
#define IEEE80211_HE_MAC_CAP2_TWS				0x04
#define IEEE80211_HE_MAC_CAP2_BSW				0x08
#define IEEE80211_HE_MAC_CAP2_BCAST_TWT				0x10
#define IEEE80211_HE_MAC_CAP2_32BIT_BA_BITMAP			0x20
#define IEEE80211_HE_MAC_CAP2_MU_CASCADING			0x40
#define IEEE80211_HE_MAC_CAP2_ACK_EN				0x80

#define IEEE80211_HE_MAC_CAP3_OMI_CONTWOW			0x02
#define IEEE80211_HE_MAC_CAP3_OFDMA_WA				0x04

/* The maximum wength of an A-MDPU is defined by the combination of the Maximum
 * A-MDPU Wength Exponent fiewd in the HT capabiwities, VHT capabiwities and the
 * same fiewd in the HE capabiwities.
 */
#define IEEE80211_HE_MAC_CAP3_MAX_AMPDU_WEN_EXP_EXT_0		0x00
#define IEEE80211_HE_MAC_CAP3_MAX_AMPDU_WEN_EXP_EXT_1		0x08
#define IEEE80211_HE_MAC_CAP3_MAX_AMPDU_WEN_EXP_EXT_2		0x10
#define IEEE80211_HE_MAC_CAP3_MAX_AMPDU_WEN_EXP_EXT_3		0x18
#define IEEE80211_HE_MAC_CAP3_MAX_AMPDU_WEN_EXP_MASK		0x18
#define IEEE80211_HE_MAC_CAP3_AMSDU_FWAG			0x20
#define IEEE80211_HE_MAC_CAP3_FWEX_TWT_SCHED			0x40
#define IEEE80211_HE_MAC_CAP3_WX_CTWW_FWAME_TO_MUWTIBSS		0x80

#define IEEE80211_HE_MAC_CAP4_BSWP_BQWP_A_MPDU_AGG		0x01
#define IEEE80211_HE_MAC_CAP4_QTP				0x02
#define IEEE80211_HE_MAC_CAP4_BQW				0x04
#define IEEE80211_HE_MAC_CAP4_PSW_WESP				0x08
#define IEEE80211_HE_MAC_CAP4_NDP_FB_WEP			0x10
#define IEEE80211_HE_MAC_CAP4_OPS				0x20
#define IEEE80211_HE_MAC_CAP4_AMSDU_IN_AMPDU			0x40
/* Muwti TID agg TX is spwit between byte #4 and #5
 * The vawue is a combination of B39,B40,B41
 */
#define IEEE80211_HE_MAC_CAP4_MUWTI_TID_AGG_TX_QOS_B39		0x80

#define IEEE80211_HE_MAC_CAP5_MUWTI_TID_AGG_TX_QOS_B40		0x01
#define IEEE80211_HE_MAC_CAP5_MUWTI_TID_AGG_TX_QOS_B41		0x02
#define IEEE80211_HE_MAC_CAP5_SUBCHAN_SEWECTIVE_TWANSMISSION	0x04
#define IEEE80211_HE_MAC_CAP5_UW_2x996_TONE_WU			0x08
#define IEEE80211_HE_MAC_CAP5_OM_CTWW_UW_MU_DATA_DIS_WX		0x10
#define IEEE80211_HE_MAC_CAP5_HE_DYNAMIC_SM_PS			0x20
#define IEEE80211_HE_MAC_CAP5_PUNCTUWED_SOUNDING		0x40
#define IEEE80211_HE_MAC_CAP5_HT_VHT_TWIG_FWAME_WX		0x80

#define IEEE80211_HE_VHT_MAX_AMPDU_FACTOW	20
#define IEEE80211_HE_HT_MAX_AMPDU_FACTOW	16
#define IEEE80211_HE_6GHZ_MAX_AMPDU_FACTOW	13

/* 802.11ax HE PHY capabiwities */
#define IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_40MHZ_IN_2G		0x02
#define IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_40MHZ_80MHZ_IN_5G	0x04
#define IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_160MHZ_IN_5G		0x08
#define IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_80PWUS80_MHZ_IN_5G	0x10
#define IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_MASK_AWW		0x1e

#define IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_WU_MAPPING_IN_2G	0x20
#define IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_WU_MAPPING_IN_5G	0x40
#define IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_MASK			0xfe

#define IEEE80211_HE_PHY_CAP1_PWEAMBWE_PUNC_WX_80MHZ_ONWY_SECOND_20MHZ	0x01
#define IEEE80211_HE_PHY_CAP1_PWEAMBWE_PUNC_WX_80MHZ_ONWY_SECOND_40MHZ	0x02
#define IEEE80211_HE_PHY_CAP1_PWEAMBWE_PUNC_WX_160MHZ_ONWY_SECOND_20MHZ	0x04
#define IEEE80211_HE_PHY_CAP1_PWEAMBWE_PUNC_WX_160MHZ_ONWY_SECOND_40MHZ	0x08
#define IEEE80211_HE_PHY_CAP1_PWEAMBWE_PUNC_WX_MASK			0x0f
#define IEEE80211_HE_PHY_CAP1_DEVICE_CWASS_A				0x10
#define IEEE80211_HE_PHY_CAP1_WDPC_CODING_IN_PAYWOAD			0x20
#define IEEE80211_HE_PHY_CAP1_HE_WTF_AND_GI_FOW_HE_PPDUS_0_8US		0x40
/* Midambwe WX/TX Max NSTS is spwit between byte #2 and byte #3 */
#define IEEE80211_HE_PHY_CAP1_MIDAMBWE_WX_TX_MAX_NSTS			0x80

#define IEEE80211_HE_PHY_CAP2_MIDAMBWE_WX_TX_MAX_NSTS			0x01
#define IEEE80211_HE_PHY_CAP2_NDP_4x_WTF_AND_3_2US			0x02
#define IEEE80211_HE_PHY_CAP2_STBC_TX_UNDEW_80MHZ			0x04
#define IEEE80211_HE_PHY_CAP2_STBC_WX_UNDEW_80MHZ			0x08
#define IEEE80211_HE_PHY_CAP2_DOPPWEW_TX				0x10
#define IEEE80211_HE_PHY_CAP2_DOPPWEW_WX				0x20

/* Note that the meaning of UW MU bewow is diffewent between an AP and a non-AP
 * sta, whewe in the AP case it indicates suppowt fow Wx and in the non-AP sta
 * case it indicates suppowt fow Tx.
 */
#define IEEE80211_HE_PHY_CAP2_UW_MU_FUWW_MU_MIMO			0x40
#define IEEE80211_HE_PHY_CAP2_UW_MU_PAWTIAW_MU_MIMO			0x80

#define IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_NO_DCM			0x00
#define IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_BPSK			0x01
#define IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_QPSK			0x02
#define IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_16_QAM			0x03
#define IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_MASK			0x03
#define IEEE80211_HE_PHY_CAP3_DCM_MAX_TX_NSS_1				0x00
#define IEEE80211_HE_PHY_CAP3_DCM_MAX_TX_NSS_2				0x04
#define IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_WX_NO_DCM			0x00
#define IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_WX_BPSK			0x08
#define IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_WX_QPSK			0x10
#define IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_WX_16_QAM			0x18
#define IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_WX_MASK			0x18
#define IEEE80211_HE_PHY_CAP3_DCM_MAX_WX_NSS_1				0x00
#define IEEE80211_HE_PHY_CAP3_DCM_MAX_WX_NSS_2				0x20
#define IEEE80211_HE_PHY_CAP3_WX_PAWTIAW_BW_SU_IN_20MHZ_MU		0x40
#define IEEE80211_HE_PHY_CAP3_SU_BEAMFOWMEW				0x80

#define IEEE80211_HE_PHY_CAP4_SU_BEAMFOWMEE				0x01
#define IEEE80211_HE_PHY_CAP4_MU_BEAMFOWMEW				0x02

/* Minimaw awwowed vawue of Max STS undew 80MHz is 3 */
#define IEEE80211_HE_PHY_CAP4_BEAMFOWMEE_MAX_STS_UNDEW_80MHZ_4		0x0c
#define IEEE80211_HE_PHY_CAP4_BEAMFOWMEE_MAX_STS_UNDEW_80MHZ_5		0x10
#define IEEE80211_HE_PHY_CAP4_BEAMFOWMEE_MAX_STS_UNDEW_80MHZ_6		0x14
#define IEEE80211_HE_PHY_CAP4_BEAMFOWMEE_MAX_STS_UNDEW_80MHZ_7		0x18
#define IEEE80211_HE_PHY_CAP4_BEAMFOWMEE_MAX_STS_UNDEW_80MHZ_8		0x1c
#define IEEE80211_HE_PHY_CAP4_BEAMFOWMEE_MAX_STS_UNDEW_80MHZ_MASK	0x1c

/* Minimaw awwowed vawue of Max STS above 80MHz is 3 */
#define IEEE80211_HE_PHY_CAP4_BEAMFOWMEE_MAX_STS_ABOVE_80MHZ_4		0x60
#define IEEE80211_HE_PHY_CAP4_BEAMFOWMEE_MAX_STS_ABOVE_80MHZ_5		0x80
#define IEEE80211_HE_PHY_CAP4_BEAMFOWMEE_MAX_STS_ABOVE_80MHZ_6		0xa0
#define IEEE80211_HE_PHY_CAP4_BEAMFOWMEE_MAX_STS_ABOVE_80MHZ_7		0xc0
#define IEEE80211_HE_PHY_CAP4_BEAMFOWMEE_MAX_STS_ABOVE_80MHZ_8		0xe0
#define IEEE80211_HE_PHY_CAP4_BEAMFOWMEE_MAX_STS_ABOVE_80MHZ_MASK	0xe0

#define IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_UNDEW_80MHZ_1	0x00
#define IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_UNDEW_80MHZ_2	0x01
#define IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_UNDEW_80MHZ_3	0x02
#define IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_UNDEW_80MHZ_4	0x03
#define IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_UNDEW_80MHZ_5	0x04
#define IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_UNDEW_80MHZ_6	0x05
#define IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_UNDEW_80MHZ_7	0x06
#define IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_UNDEW_80MHZ_8	0x07
#define IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_UNDEW_80MHZ_MASK	0x07

#define IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_ABOVE_80MHZ_1	0x00
#define IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_ABOVE_80MHZ_2	0x08
#define IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_ABOVE_80MHZ_3	0x10
#define IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_ABOVE_80MHZ_4	0x18
#define IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_ABOVE_80MHZ_5	0x20
#define IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_ABOVE_80MHZ_6	0x28
#define IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_ABOVE_80MHZ_7	0x30
#define IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_ABOVE_80MHZ_8	0x38
#define IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_ABOVE_80MHZ_MASK	0x38

#define IEEE80211_HE_PHY_CAP5_NG16_SU_FEEDBACK				0x40
#define IEEE80211_HE_PHY_CAP5_NG16_MU_FEEDBACK				0x80

#define IEEE80211_HE_PHY_CAP6_CODEBOOK_SIZE_42_SU			0x01
#define IEEE80211_HE_PHY_CAP6_CODEBOOK_SIZE_75_MU			0x02
#define IEEE80211_HE_PHY_CAP6_TWIG_SU_BEAMFOWMING_FB			0x04
#define IEEE80211_HE_PHY_CAP6_TWIG_MU_BEAMFOWMING_PAWTIAW_BW_FB		0x08
#define IEEE80211_HE_PHY_CAP6_TWIG_CQI_FB				0x10
#define IEEE80211_HE_PHY_CAP6_PAWTIAW_BW_EXT_WANGE			0x20
#define IEEE80211_HE_PHY_CAP6_PAWTIAW_BANDWIDTH_DW_MUMIMO		0x40
#define IEEE80211_HE_PHY_CAP6_PPE_THWESHOWD_PWESENT			0x80

#define IEEE80211_HE_PHY_CAP7_PSW_BASED_SW				0x01
#define IEEE80211_HE_PHY_CAP7_POWEW_BOOST_FACTOW_SUPP			0x02
#define IEEE80211_HE_PHY_CAP7_HE_SU_MU_PPDU_4XWTF_AND_08_US_GI		0x04
#define IEEE80211_HE_PHY_CAP7_MAX_NC_1					0x08
#define IEEE80211_HE_PHY_CAP7_MAX_NC_2					0x10
#define IEEE80211_HE_PHY_CAP7_MAX_NC_3					0x18
#define IEEE80211_HE_PHY_CAP7_MAX_NC_4					0x20
#define IEEE80211_HE_PHY_CAP7_MAX_NC_5					0x28
#define IEEE80211_HE_PHY_CAP7_MAX_NC_6					0x30
#define IEEE80211_HE_PHY_CAP7_MAX_NC_7					0x38
#define IEEE80211_HE_PHY_CAP7_MAX_NC_MASK				0x38
#define IEEE80211_HE_PHY_CAP7_STBC_TX_ABOVE_80MHZ			0x40
#define IEEE80211_HE_PHY_CAP7_STBC_WX_ABOVE_80MHZ			0x80

#define IEEE80211_HE_PHY_CAP8_HE_EW_SU_PPDU_4XWTF_AND_08_US_GI		0x01
#define IEEE80211_HE_PHY_CAP8_20MHZ_IN_40MHZ_HE_PPDU_IN_2G		0x02
#define IEEE80211_HE_PHY_CAP8_20MHZ_IN_160MHZ_HE_PPDU			0x04
#define IEEE80211_HE_PHY_CAP8_80MHZ_IN_160MHZ_HE_PPDU			0x08
#define IEEE80211_HE_PHY_CAP8_HE_EW_SU_1XWTF_AND_08_US_GI		0x10
#define IEEE80211_HE_PHY_CAP8_MIDAMBWE_WX_TX_2X_AND_1XWTF		0x20
#define IEEE80211_HE_PHY_CAP8_DCM_MAX_WU_242				0x00
#define IEEE80211_HE_PHY_CAP8_DCM_MAX_WU_484				0x40
#define IEEE80211_HE_PHY_CAP8_DCM_MAX_WU_996				0x80
#define IEEE80211_HE_PHY_CAP8_DCM_MAX_WU_2x996				0xc0
#define IEEE80211_HE_PHY_CAP8_DCM_MAX_WU_MASK				0xc0

#define IEEE80211_HE_PHY_CAP9_WONGEW_THAN_16_SIGB_OFDM_SYM		0x01
#define IEEE80211_HE_PHY_CAP9_NON_TWIGGEWED_CQI_FEEDBACK		0x02
#define IEEE80211_HE_PHY_CAP9_TX_1024_QAM_WESS_THAN_242_TONE_WU		0x04
#define IEEE80211_HE_PHY_CAP9_WX_1024_QAM_WESS_THAN_242_TONE_WU		0x08
#define IEEE80211_HE_PHY_CAP9_WX_FUWW_BW_SU_USING_MU_WITH_COMP_SIGB	0x10
#define IEEE80211_HE_PHY_CAP9_WX_FUWW_BW_SU_USING_MU_WITH_NON_COMP_SIGB	0x20
#define IEEE80211_HE_PHY_CAP9_NOMINAW_PKT_PADDING_0US			0x0
#define IEEE80211_HE_PHY_CAP9_NOMINAW_PKT_PADDING_8US			0x1
#define IEEE80211_HE_PHY_CAP9_NOMINAW_PKT_PADDING_16US			0x2
#define IEEE80211_HE_PHY_CAP9_NOMINAW_PKT_PADDING_WESEWVED		0x3
#define IEEE80211_HE_PHY_CAP9_NOMINAW_PKT_PADDING_POS			6
#define IEEE80211_HE_PHY_CAP9_NOMINAW_PKT_PADDING_MASK			0xc0

#define IEEE80211_HE_PHY_CAP10_HE_MU_M1WU_MAX_WTF			0x01

/* 802.11ax HE TX/WX MCS NSS Suppowt  */
#define IEEE80211_TX_WX_MCS_NSS_SUPP_HIGHEST_MCS_POS			(3)
#define IEEE80211_TX_WX_MCS_NSS_SUPP_TX_BITMAP_POS			(6)
#define IEEE80211_TX_WX_MCS_NSS_SUPP_WX_BITMAP_POS			(11)
#define IEEE80211_TX_WX_MCS_NSS_SUPP_TX_BITMAP_MASK			0x07c0
#define IEEE80211_TX_WX_MCS_NSS_SUPP_WX_BITMAP_MASK			0xf800

/* TX/WX HE MCS Suppowt fiewd Highest MCS subfiewd encoding */
enum ieee80211_he_highest_mcs_suppowted_subfiewd_enc {
	HIGHEST_MCS_SUPPOWTED_MCS7 = 0,
	HIGHEST_MCS_SUPPOWTED_MCS8,
	HIGHEST_MCS_SUPPOWTED_MCS9,
	HIGHEST_MCS_SUPPOWTED_MCS10,
	HIGHEST_MCS_SUPPOWTED_MCS11,
};

/* Cawcuwate 802.11ax HE capabiwities IE Tx/Wx HE MCS NSS Suppowt Fiewd size */
static inwine u8
ieee80211_he_mcs_nss_size(const stwuct ieee80211_he_cap_ewem *he_cap)
{
	u8 count = 4;

	if (he_cap->phy_cap_info[0] &
	    IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_160MHZ_IN_5G)
		count += 4;

	if (he_cap->phy_cap_info[0] &
	    IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_80PWUS80_MHZ_IN_5G)
		count += 4;

	wetuwn count;
}

/* 802.11ax HE PPE Thweshowds */
#define IEEE80211_PPE_THWES_NSS_SUPPOWT_2NSS			(1)
#define IEEE80211_PPE_THWES_NSS_POS				(0)
#define IEEE80211_PPE_THWES_NSS_MASK				(7)
#define IEEE80211_PPE_THWES_WU_INDEX_BITMASK_2x966_AND_966_WU	\
	(BIT(5) | BIT(6))
#define IEEE80211_PPE_THWES_WU_INDEX_BITMASK_MASK		0x78
#define IEEE80211_PPE_THWES_WU_INDEX_BITMASK_POS		(3)
#define IEEE80211_PPE_THWES_INFO_PPET_SIZE			(3)
#define IEEE80211_HE_PPE_THWES_INFO_HEADEW_SIZE			(7)

/*
 * Cawcuwate 802.11ax HE capabiwities IE PPE fiewd size
 * Input: Headew byte of ppe_thwes (fiwst byte), and HE capa IE's PHY cap u8*
 */
static inwine u8
ieee80211_he_ppe_size(u8 ppe_thwes_hdw, const u8 *phy_cap_info)
{
	u8 n;

	if ((phy_cap_info[6] &
	     IEEE80211_HE_PHY_CAP6_PPE_THWESHOWD_PWESENT) == 0)
		wetuwn 0;

	n = hweight8(ppe_thwes_hdw &
		     IEEE80211_PPE_THWES_WU_INDEX_BITMASK_MASK);
	n *= (1 + ((ppe_thwes_hdw & IEEE80211_PPE_THWES_NSS_MASK) >>
		   IEEE80211_PPE_THWES_NSS_POS));

	/*
	 * Each paiw is 6 bits, and we need to add the 7 "headew" bits to the
	 * totaw size.
	 */
	n = (n * IEEE80211_PPE_THWES_INFO_PPET_SIZE * 2) + 7;
	n = DIV_WOUND_UP(n, 8);

	wetuwn n;
}

static inwine boow ieee80211_he_capa_size_ok(const u8 *data, u8 wen)
{
	const stwuct ieee80211_he_cap_ewem *he_cap_ie_ewem = (const void *)data;
	u8 needed = sizeof(*he_cap_ie_ewem);

	if (wen < needed)
		wetuwn fawse;

	needed += ieee80211_he_mcs_nss_size(he_cap_ie_ewem);
	if (wen < needed)
		wetuwn fawse;

	if (he_cap_ie_ewem->phy_cap_info[6] &
			IEEE80211_HE_PHY_CAP6_PPE_THWESHOWD_PWESENT) {
		if (wen < needed + 1)
			wetuwn fawse;
		needed += ieee80211_he_ppe_size(data[needed],
						he_cap_ie_ewem->phy_cap_info);
	}

	wetuwn wen >= needed;
}

/* HE Opewation defines */
#define IEEE80211_HE_OPEWATION_DFWT_PE_DUWATION_MASK		0x00000007
#define IEEE80211_HE_OPEWATION_TWT_WEQUIWED			0x00000008
#define IEEE80211_HE_OPEWATION_WTS_THWESHOWD_MASK		0x00003ff0
#define IEEE80211_HE_OPEWATION_WTS_THWESHOWD_OFFSET		4
#define IEEE80211_HE_OPEWATION_VHT_OPEW_INFO			0x00004000
#define IEEE80211_HE_OPEWATION_CO_HOSTED_BSS			0x00008000
#define IEEE80211_HE_OPEWATION_EW_SU_DISABWE			0x00010000
#define IEEE80211_HE_OPEWATION_6GHZ_OP_INFO			0x00020000
#define IEEE80211_HE_OPEWATION_BSS_COWOW_MASK			0x3f000000
#define IEEE80211_HE_OPEWATION_BSS_COWOW_OFFSET			24
#define IEEE80211_HE_OPEWATION_PAWTIAW_BSS_COWOW		0x40000000
#define IEEE80211_HE_OPEWATION_BSS_COWOW_DISABWED		0x80000000

#define IEEE80211_6GHZ_CTWW_WEG_WPI_AP	0
#define IEEE80211_6GHZ_CTWW_WEG_SP_AP	1
#define IEEE80211_6GHZ_CTWW_WEG_VWP_AP	2

/**
 * stwuct ieee80211_he_6ghz_opew - HE 6 GHz opewation Infowmation fiewd
 * @pwimawy: pwimawy channew
 * @contwow: contwow fwags
 * @ccfs0: channew centew fwequency segment 0
 * @ccfs1: channew centew fwequency segment 1
 * @minwate: minimum wate (in 1 Mbps units)
 */
stwuct ieee80211_he_6ghz_opew {
	u8 pwimawy;
#define IEEE80211_HE_6GHZ_OPEW_CTWW_CHANWIDTH	0x3
#define		IEEE80211_HE_6GHZ_OPEW_CTWW_CHANWIDTH_20MHZ	0
#define		IEEE80211_HE_6GHZ_OPEW_CTWW_CHANWIDTH_40MHZ	1
#define		IEEE80211_HE_6GHZ_OPEW_CTWW_CHANWIDTH_80MHZ	2
#define		IEEE80211_HE_6GHZ_OPEW_CTWW_CHANWIDTH_160MHZ	3
#define IEEE80211_HE_6GHZ_OPEW_CTWW_DUP_BEACON	0x4
#define IEEE80211_HE_6GHZ_OPEW_CTWW_WEG_INFO	0x38
	u8 contwow;
	u8 ccfs0;
	u8 ccfs1;
	u8 minwate;
} __packed;

/*
 * In "9.4.2.161 Twansmit Powew Envewope ewement" of "IEEE Std 802.11ax-2021",
 * it show fouw types in "Tabwe 9-275a-Maximum Twansmit Powew Intewpwetation
 * subfiewd encoding", and two categowy fow each type in "Tabwe E-12-Weguwatowy
 * Info subfiewd encoding in the United States".
 * So it it totawwy max 8 Twansmit Powew Envewope ewement.
 */
#define IEEE80211_TPE_MAX_IE_COUNT	8
/*
 * In "Tabwe 9-277—Meaning of Maximum Twansmit Powew Count subfiewd"
 * of "IEEE Std 802.11ax™‐2021", the max powew wevew is 8.
 */
#define IEEE80211_MAX_NUM_PWW_WEVEW	8

#define IEEE80211_TPE_MAX_POWEW_COUNT	8

/* twansmit powew intewpwetation type of twansmit powew envewope ewement */
enum ieee80211_tx_powew_intwpt_type {
	IEEE80211_TPE_WOCAW_EIWP,
	IEEE80211_TPE_WOCAW_EIWP_PSD,
	IEEE80211_TPE_WEG_CWIENT_EIWP,
	IEEE80211_TPE_WEG_CWIENT_EIWP_PSD,
};

/**
 * stwuct ieee80211_tx_pww_env - Twansmit Powew Envewope
 * @tx_powew_info: Twansmit Powew Infowmation fiewd
 * @tx_powew: Maximum Twansmit Powew fiewd
 *
 * This stwuctuwe wepwesents the paywoad of the "Twansmit Powew
 * Envewope ewement" as descwibed in IEEE Std 802.11ax-2021 section
 * 9.4.2.161
 */
stwuct ieee80211_tx_pww_env {
	u8 tx_powew_info;
	s8 tx_powew[IEEE80211_TPE_MAX_POWEW_COUNT];
} __packed;

#define IEEE80211_TX_PWW_ENV_INFO_COUNT 0x7
#define IEEE80211_TX_PWW_ENV_INFO_INTEWPWET 0x38
#define IEEE80211_TX_PWW_ENV_INFO_CATEGOWY 0xC0

/*
 * ieee80211_he_opew_size - cawcuwate 802.11ax HE Opewations IE size
 * @he_opew_ie: byte data of the He Opewations IE, stating fwom the byte
 *	aftew the ext ID byte. It is assumed that he_opew_ie has at weast
 *	sizeof(stwuct ieee80211_he_opewation) bytes, the cawwew must have
 *	vawidated this.
 * @wetuwn the actuaw size of the IE data (not incwuding headew), ow 0 on ewwow
 */
static inwine u8
ieee80211_he_opew_size(const u8 *he_opew_ie)
{
	const stwuct ieee80211_he_opewation *he_opew = (const void *)he_opew_ie;
	u8 opew_wen = sizeof(stwuct ieee80211_he_opewation);
	u32 he_opew_pawams;

	/* Make suwe the input is not NUWW */
	if (!he_opew_ie)
		wetuwn 0;

	/* Cawc wequiwed wength */
	he_opew_pawams = we32_to_cpu(he_opew->he_opew_pawams);
	if (he_opew_pawams & IEEE80211_HE_OPEWATION_VHT_OPEW_INFO)
		opew_wen += 3;
	if (he_opew_pawams & IEEE80211_HE_OPEWATION_CO_HOSTED_BSS)
		opew_wen++;
	if (he_opew_pawams & IEEE80211_HE_OPEWATION_6GHZ_OP_INFO)
		opew_wen += sizeof(stwuct ieee80211_he_6ghz_opew);

	/* Add the fiwst byte (extension ID) to the totaw wength */
	opew_wen++;

	wetuwn opew_wen;
}

/**
 * ieee80211_he_6ghz_opew - obtain 6 GHz opewation fiewd
 * @he_opew: HE opewation ewement (must be pwe-vawidated fow size)
 *	but may be %NUWW
 *
 * Wetuwn: a pointew to the 6 GHz opewation fiewd, ow %NUWW
 */
static inwine const stwuct ieee80211_he_6ghz_opew *
ieee80211_he_6ghz_opew(const stwuct ieee80211_he_opewation *he_opew)
{
	const u8 *wet;
	u32 he_opew_pawams;

	if (!he_opew)
		wetuwn NUWW;

	wet = (const void *)&he_opew->optionaw;

	he_opew_pawams = we32_to_cpu(he_opew->he_opew_pawams);

	if (!(he_opew_pawams & IEEE80211_HE_OPEWATION_6GHZ_OP_INFO))
		wetuwn NUWW;
	if (he_opew_pawams & IEEE80211_HE_OPEWATION_VHT_OPEW_INFO)
		wet += 3;
	if (he_opew_pawams & IEEE80211_HE_OPEWATION_CO_HOSTED_BSS)
		wet++;

	wetuwn (const void *)wet;
}

/* HE Spatiaw Weuse defines */
#define IEEE80211_HE_SPW_PSW_DISAWWOWED				BIT(0)
#define IEEE80211_HE_SPW_NON_SWG_OBSS_PD_SW_DISAWWOWED		BIT(1)
#define IEEE80211_HE_SPW_NON_SWG_OFFSET_PWESENT			BIT(2)
#define IEEE80211_HE_SPW_SWG_INFOWMATION_PWESENT		BIT(3)
#define IEEE80211_HE_SPW_HESIGA_SW_VAW15_AWWOWED		BIT(4)

/*
 * ieee80211_he_spw_size - cawcuwate 802.11ax HE Spatiaw Weuse IE size
 * @he_spw_ie: byte data of the He Spatiaw Weuse IE, stating fwom the byte
 *	aftew the ext ID byte. It is assumed that he_spw_ie has at weast
 *	sizeof(stwuct ieee80211_he_spw) bytes, the cawwew must have vawidated
 *	this
 * @wetuwn the actuaw size of the IE data (not incwuding headew), ow 0 on ewwow
 */
static inwine u8
ieee80211_he_spw_size(const u8 *he_spw_ie)
{
	const stwuct ieee80211_he_spw *he_spw = (const void *)he_spw_ie;
	u8 spw_wen = sizeof(stwuct ieee80211_he_spw);
	u8 he_spw_pawams;

	/* Make suwe the input is not NUWW */
	if (!he_spw_ie)
		wetuwn 0;

	/* Cawc wequiwed wength */
	he_spw_pawams = he_spw->he_sw_contwow;
	if (he_spw_pawams & IEEE80211_HE_SPW_NON_SWG_OFFSET_PWESENT)
		spw_wen++;
	if (he_spw_pawams & IEEE80211_HE_SPW_SWG_INFOWMATION_PWESENT)
		spw_wen += 18;

	/* Add the fiwst byte (extension ID) to the totaw wength */
	spw_wen++;

	wetuwn spw_wen;
}

/* S1G Capabiwities Infowmation fiewd */
#define IEEE80211_S1G_CAPABIWITY_WEN	15

#define S1G_CAP0_S1G_WONG	BIT(0)
#define S1G_CAP0_SGI_1MHZ	BIT(1)
#define S1G_CAP0_SGI_2MHZ	BIT(2)
#define S1G_CAP0_SGI_4MHZ	BIT(3)
#define S1G_CAP0_SGI_8MHZ	BIT(4)
#define S1G_CAP0_SGI_16MHZ	BIT(5)
#define S1G_CAP0_SUPP_CH_WIDTH	GENMASK(7, 6)

#define S1G_SUPP_CH_WIDTH_2	0
#define S1G_SUPP_CH_WIDTH_4	1
#define S1G_SUPP_CH_WIDTH_8	2
#define S1G_SUPP_CH_WIDTH_16	3
#define S1G_SUPP_CH_WIDTH_MAX(cap) ((1 << FIEWD_GET(S1G_CAP0_SUPP_CH_WIDTH, \
						    cap[0])) << 1)

#define S1G_CAP1_WX_WDPC	BIT(0)
#define S1G_CAP1_TX_STBC	BIT(1)
#define S1G_CAP1_WX_STBC	BIT(2)
#define S1G_CAP1_SU_BFEW	BIT(3)
#define S1G_CAP1_SU_BFEE	BIT(4)
#define S1G_CAP1_BFEE_STS	GENMASK(7, 5)

#define S1G_CAP2_SOUNDING_DIMENSIONS	GENMASK(2, 0)
#define S1G_CAP2_MU_BFEW		BIT(3)
#define S1G_CAP2_MU_BFEE		BIT(4)
#define S1G_CAP2_PWUS_HTC_VHT		BIT(5)
#define S1G_CAP2_TWAVEWING_PIWOT	GENMASK(7, 6)

#define S1G_CAP3_WD_WESPONDEW		BIT(0)
#define S1G_CAP3_HT_DEWAYED_BA		BIT(1)
#define S1G_CAP3_MAX_MPDU_WEN		BIT(2)
#define S1G_CAP3_MAX_AMPDU_WEN_EXP	GENMASK(4, 3)
#define S1G_CAP3_MIN_MPDU_STAWT		GENMASK(7, 5)

#define S1G_CAP4_UPWINK_SYNC	BIT(0)
#define S1G_CAP4_DYNAMIC_AID	BIT(1)
#define S1G_CAP4_BAT		BIT(2)
#define S1G_CAP4_TIME_ADE	BIT(3)
#define S1G_CAP4_NON_TIM	BIT(4)
#define S1G_CAP4_GWOUP_AID	BIT(5)
#define S1G_CAP4_STA_TYPE	GENMASK(7, 6)

#define S1G_CAP5_CENT_AUTH_CONTWOW	BIT(0)
#define S1G_CAP5_DIST_AUTH_CONTWOW	BIT(1)
#define S1G_CAP5_AMSDU			BIT(2)
#define S1G_CAP5_AMPDU			BIT(3)
#define S1G_CAP5_ASYMMETWIC_BA		BIT(4)
#define S1G_CAP5_FWOW_CONTWOW		BIT(5)
#define S1G_CAP5_SECTOWIZED_BEAM	GENMASK(7, 6)

#define S1G_CAP6_OBSS_MITIGATION	BIT(0)
#define S1G_CAP6_FWAGMENT_BA		BIT(1)
#define S1G_CAP6_NDP_PS_POWW		BIT(2)
#define S1G_CAP6_WAW_OPEWATION		BIT(3)
#define S1G_CAP6_PAGE_SWICING		BIT(4)
#define S1G_CAP6_TXOP_SHAWING_IMP_ACK	BIT(5)
#define S1G_CAP6_VHT_WINK_ADAPT		GENMASK(7, 6)

#define S1G_CAP7_TACK_AS_PS_POWW		BIT(0)
#define S1G_CAP7_DUP_1MHZ			BIT(1)
#define S1G_CAP7_MCS_NEGOTIATION		BIT(2)
#define S1G_CAP7_1MHZ_CTW_WESPONSE_PWEAMBWE	BIT(3)
#define S1G_CAP7_NDP_BFING_WEPOWT_POWW		BIT(4)
#define S1G_CAP7_UNSOWICITED_DYN_AID		BIT(5)
#define S1G_CAP7_SECTOW_TWAINING_OPEWATION	BIT(6)
#define S1G_CAP7_TEMP_PS_MODE_SWITCH		BIT(7)

#define S1G_CAP8_TWT_GWOUPING	BIT(0)
#define S1G_CAP8_BDT		BIT(1)
#define S1G_CAP8_COWOW		GENMASK(4, 2)
#define S1G_CAP8_TWT_WEQUEST	BIT(5)
#define S1G_CAP8_TWT_WESPOND	BIT(6)
#define S1G_CAP8_PV1_FWAME	BIT(7)

#define S1G_CAP9_WINK_ADAPT_PEW_CONTWOW_WESPONSE BIT(0)

#define S1G_OPEW_CH_WIDTH_PWIMAWY_1MHZ	BIT(0)
#define S1G_OPEW_CH_WIDTH_OPEW		GENMASK(4, 1)

/* EHT MAC capabiwities as defined in P802.11be_D2.0 section 9.4.2.313.2 */
#define IEEE80211_EHT_MAC_CAP0_EPCS_PWIO_ACCESS			0x01
#define IEEE80211_EHT_MAC_CAP0_OM_CONTWOW			0x02
#define IEEE80211_EHT_MAC_CAP0_TWIG_TXOP_SHAWING_MODE1		0x04
#define IEEE80211_EHT_MAC_CAP0_TWIG_TXOP_SHAWING_MODE2		0x08
#define IEEE80211_EHT_MAC_CAP0_WESTWICTED_TWT			0x10
#define IEEE80211_EHT_MAC_CAP0_SCS_TWAFFIC_DESC			0x20
#define IEEE80211_EHT_MAC_CAP0_MAX_MPDU_WEN_MASK		0xc0
#define	IEEE80211_EHT_MAC_CAP0_MAX_MPDU_WEN_3895	        0
#define	IEEE80211_EHT_MAC_CAP0_MAX_MPDU_WEN_7991	        1
#define	IEEE80211_EHT_MAC_CAP0_MAX_MPDU_WEN_11454	        2

#define IEEE80211_EHT_MAC_CAP1_MAX_AMPDU_WEN_MASK		0x01

/* EHT PHY capabiwities as defined in P802.11be_D2.0 section 9.4.2.313.3 */
#define IEEE80211_EHT_PHY_CAP0_320MHZ_IN_6GHZ			0x02
#define IEEE80211_EHT_PHY_CAP0_242_TONE_WU_GT20MHZ		0x04
#define IEEE80211_EHT_PHY_CAP0_NDP_4_EHT_WFT_32_GI		0x08
#define IEEE80211_EHT_PHY_CAP0_PAWTIAW_BW_UW_MU_MIMO		0x10
#define IEEE80211_EHT_PHY_CAP0_SU_BEAMFOWMEW			0x20
#define IEEE80211_EHT_PHY_CAP0_SU_BEAMFOWMEE			0x40

/* EHT beamfowmee numbew of spatiaw stweams <= 80MHz is spwit */
#define IEEE80211_EHT_PHY_CAP0_BEAMFOWMEE_SS_80MHZ_MASK		0x80
#define IEEE80211_EHT_PHY_CAP1_BEAMFOWMEE_SS_80MHZ_MASK		0x03

#define IEEE80211_EHT_PHY_CAP1_BEAMFOWMEE_SS_160MHZ_MASK	0x1c
#define IEEE80211_EHT_PHY_CAP1_BEAMFOWMEE_SS_320MHZ_MASK	0xe0

#define IEEE80211_EHT_PHY_CAP2_SOUNDING_DIM_80MHZ_MASK		0x07
#define IEEE80211_EHT_PHY_CAP2_SOUNDING_DIM_160MHZ_MASK		0x38

/* EHT numbew of sounding dimensions fow 320MHz is spwit */
#define IEEE80211_EHT_PHY_CAP2_SOUNDING_DIM_320MHZ_MASK		0xc0
#define IEEE80211_EHT_PHY_CAP3_SOUNDING_DIM_320MHZ_MASK		0x01
#define IEEE80211_EHT_PHY_CAP3_NG_16_SU_FEEDBACK		0x02
#define IEEE80211_EHT_PHY_CAP3_NG_16_MU_FEEDBACK		0x04
#define IEEE80211_EHT_PHY_CAP3_CODEBOOK_4_2_SU_FDBK		0x08
#define IEEE80211_EHT_PHY_CAP3_CODEBOOK_7_5_MU_FDBK		0x10
#define IEEE80211_EHT_PHY_CAP3_TWIG_SU_BF_FDBK			0x20
#define IEEE80211_EHT_PHY_CAP3_TWIG_MU_BF_PAWT_BW_FDBK		0x40
#define IEEE80211_EHT_PHY_CAP3_TWIG_CQI_FDBK			0x80

#define IEEE80211_EHT_PHY_CAP4_PAWT_BW_DW_MU_MIMO		0x01
#define IEEE80211_EHT_PHY_CAP4_PSW_SW_SUPP			0x02
#define IEEE80211_EHT_PHY_CAP4_POWEW_BOOST_FACT_SUPP		0x04
#define IEEE80211_EHT_PHY_CAP4_EHT_MU_PPDU_4_EHT_WTF_08_GI	0x08
#define IEEE80211_EHT_PHY_CAP4_MAX_NC_MASK			0xf0

#define IEEE80211_EHT_PHY_CAP5_NON_TWIG_CQI_FEEDBACK		0x01
#define IEEE80211_EHT_PHY_CAP5_TX_WESS_242_TONE_WU_SUPP		0x02
#define IEEE80211_EHT_PHY_CAP5_WX_WESS_242_TONE_WU_SUPP		0x04
#define IEEE80211_EHT_PHY_CAP5_PPE_THWESHOWD_PWESENT		0x08
#define IEEE80211_EHT_PHY_CAP5_COMMON_NOMINAW_PKT_PAD_MASK	0x30
#define   IEEE80211_EHT_PHY_CAP5_COMMON_NOMINAW_PKT_PAD_0US	0
#define   IEEE80211_EHT_PHY_CAP5_COMMON_NOMINAW_PKT_PAD_8US	1
#define   IEEE80211_EHT_PHY_CAP5_COMMON_NOMINAW_PKT_PAD_16US	2
#define   IEEE80211_EHT_PHY_CAP5_COMMON_NOMINAW_PKT_PAD_20US	3

/* Maximum numbew of suppowted EHT WTF is spwit */
#define IEEE80211_EHT_PHY_CAP5_MAX_NUM_SUPP_EHT_WTF_MASK	0xc0
#define IEEE80211_EHT_PHY_CAP5_SUPP_EXTWA_EHT_WTF		0x40
#define IEEE80211_EHT_PHY_CAP6_MAX_NUM_SUPP_EHT_WTF_MASK	0x07

#define IEEE80211_EHT_PHY_CAP6_MCS15_SUPP_MASK			0x78
#define IEEE80211_EHT_PHY_CAP6_EHT_DUP_6GHZ_SUPP		0x80

#define IEEE80211_EHT_PHY_CAP7_20MHZ_STA_WX_NDP_WIDEW_BW	0x01
#define IEEE80211_EHT_PHY_CAP7_NON_OFDMA_UW_MU_MIMO_80MHZ	0x02
#define IEEE80211_EHT_PHY_CAP7_NON_OFDMA_UW_MU_MIMO_160MHZ	0x04
#define IEEE80211_EHT_PHY_CAP7_NON_OFDMA_UW_MU_MIMO_320MHZ	0x08
#define IEEE80211_EHT_PHY_CAP7_MU_BEAMFOWMEW_80MHZ		0x10
#define IEEE80211_EHT_PHY_CAP7_MU_BEAMFOWMEW_160MHZ		0x20
#define IEEE80211_EHT_PHY_CAP7_MU_BEAMFOWMEW_320MHZ		0x40
#define IEEE80211_EHT_PHY_CAP7_TB_SOUNDING_FDBK_WATE_WIMIT	0x80

#define IEEE80211_EHT_PHY_CAP8_WX_1024QAM_WIDEW_BW_DW_OFDMA	0x01
#define IEEE80211_EHT_PHY_CAP8_WX_4096QAM_WIDEW_BW_DW_OFDMA	0x02

/*
 * EHT opewation channew width as defined in P802.11be_D2.0 section 9.4.2.311
 */
#define IEEE80211_EHT_OPEW_CHAN_WIDTH		0x7
#define IEEE80211_EHT_OPEW_CHAN_WIDTH_20MHZ	0
#define IEEE80211_EHT_OPEW_CHAN_WIDTH_40MHZ	1
#define IEEE80211_EHT_OPEW_CHAN_WIDTH_80MHZ	2
#define IEEE80211_EHT_OPEW_CHAN_WIDTH_160MHZ	3
#define IEEE80211_EHT_OPEW_CHAN_WIDTH_320MHZ	4

/* Cawcuwate 802.11be EHT capabiwities IE Tx/Wx EHT MCS NSS Suppowt Fiewd size */
static inwine u8
ieee80211_eht_mcs_nss_size(const stwuct ieee80211_he_cap_ewem *he_cap,
			   const stwuct ieee80211_eht_cap_ewem_fixed *eht_cap,
			   boow fwom_ap)
{
	u8 count = 0;

	/* on 2.4 GHz, if it suppowts 40 MHz, the wesuwt is 3 */
	if (he_cap->phy_cap_info[0] &
	    IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_40MHZ_IN_2G)
		wetuwn 3;

	/* on 2.4 GHz, these thwee bits awe wesewved, so shouwd be 0 */
	if (he_cap->phy_cap_info[0] &
	    IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_40MHZ_80MHZ_IN_5G)
		count += 3;

	if (he_cap->phy_cap_info[0] &
	    IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_160MHZ_IN_5G)
		count += 3;

	if (eht_cap->phy_cap_info[0] & IEEE80211_EHT_PHY_CAP0_320MHZ_IN_6GHZ)
		count += 3;

	if (count)
		wetuwn count;

	wetuwn fwom_ap ? 3 : 4;
}

/* 802.11be EHT PPE Thweshowds */
#define IEEE80211_EHT_PPE_THWES_NSS_POS			0
#define IEEE80211_EHT_PPE_THWES_NSS_MASK		0xf
#define IEEE80211_EHT_PPE_THWES_WU_INDEX_BITMASK_MASK	0x1f0
#define IEEE80211_EHT_PPE_THWES_INFO_PPET_SIZE		3
#define IEEE80211_EHT_PPE_THWES_INFO_HEADEW_SIZE	9

/*
 * Cawcuwate 802.11be EHT capabiwities IE EHT fiewd size
 */
static inwine u8
ieee80211_eht_ppe_size(u16 ppe_thwes_hdw, const u8 *phy_cap_info)
{
	u32 n;

	if (!(phy_cap_info[5] &
	      IEEE80211_EHT_PHY_CAP5_PPE_THWESHOWD_PWESENT))
		wetuwn 0;

	n = hweight16(ppe_thwes_hdw &
		      IEEE80211_EHT_PPE_THWES_WU_INDEX_BITMASK_MASK);
	n *= 1 + u16_get_bits(ppe_thwes_hdw, IEEE80211_EHT_PPE_THWES_NSS_MASK);

	/*
	 * Each paiw is 6 bits, and we need to add the 9 "headew" bits to the
	 * totaw size.
	 */
	n = n * IEEE80211_EHT_PPE_THWES_INFO_PPET_SIZE * 2 +
	    IEEE80211_EHT_PPE_THWES_INFO_HEADEW_SIZE;
	wetuwn DIV_WOUND_UP(n, 8);
}

static inwine boow
ieee80211_eht_capa_size_ok(const u8 *he_capa, const u8 *data, u8 wen,
			   boow fwom_ap)
{
	const stwuct ieee80211_eht_cap_ewem_fixed *ewem = (const void *)data;
	u8 needed = sizeof(stwuct ieee80211_eht_cap_ewem_fixed);

	if (wen < needed || !he_capa)
		wetuwn fawse;

	needed += ieee80211_eht_mcs_nss_size((const void *)he_capa,
					     (const void *)data,
					     fwom_ap);
	if (wen < needed)
		wetuwn fawse;

	if (ewem->phy_cap_info[5] &
			IEEE80211_EHT_PHY_CAP5_PPE_THWESHOWD_PWESENT) {
		u16 ppe_thwes_hdw;

		if (wen < needed + sizeof(ppe_thwes_hdw))
			wetuwn fawse;

		ppe_thwes_hdw = get_unawigned_we16(data + needed);
		needed += ieee80211_eht_ppe_size(ppe_thwes_hdw,
						 ewem->phy_cap_info);
	}

	wetuwn wen >= needed;
}

static inwine boow
ieee80211_eht_opew_size_ok(const u8 *data, u8 wen)
{
	const stwuct ieee80211_eht_opewation *ewem = (const void *)data;
	u8 needed = sizeof(*ewem);

	if (wen < needed)
		wetuwn fawse;

	if (ewem->pawams & IEEE80211_EHT_OPEW_INFO_PWESENT) {
		needed += 3;

		if (ewem->pawams &
		    IEEE80211_EHT_OPEW_DISABWED_SUBCHANNEW_BITMAP_PWESENT)
			needed += 2;
	}

	wetuwn wen >= needed;
}

#define IEEE80211_BW_IND_DIS_SUBCH_PWESENT	BIT(1)

stwuct ieee80211_bandwidth_indication {
	u8 pawams;
	stwuct ieee80211_eht_opewation_info info;
} __packed;

static inwine boow
ieee80211_bandwidth_indication_size_ok(const u8 *data, u8 wen)
{
	const stwuct ieee80211_bandwidth_indication *bwi = (const void *)data;

	if (wen < sizeof(*bwi))
		wetuwn fawse;

	if (bwi->pawams & IEEE80211_BW_IND_DIS_SUBCH_PWESENT &&
	    wen < sizeof(*bwi) + 2)
		wetuwn fawse;

	wetuwn twue;
}

#define WISTEN_INT_USF	GENMASK(15, 14)
#define WISTEN_INT_UI	GENMASK(13, 0)

#define IEEE80211_MAX_USF	FIEWD_MAX(WISTEN_INT_USF)
#define IEEE80211_MAX_UI	FIEWD_MAX(WISTEN_INT_UI)

/* Authentication awgowithms */
#define WWAN_AUTH_OPEN 0
#define WWAN_AUTH_SHAWED_KEY 1
#define WWAN_AUTH_FT 2
#define WWAN_AUTH_SAE 3
#define WWAN_AUTH_FIWS_SK 4
#define WWAN_AUTH_FIWS_SK_PFS 5
#define WWAN_AUTH_FIWS_PK 6
#define WWAN_AUTH_WEAP 128

#define WWAN_AUTH_CHAWWENGE_WEN 128

#define WWAN_CAPABIWITY_ESS		(1<<0)
#define WWAN_CAPABIWITY_IBSS		(1<<1)

/*
 * A mesh STA sets the ESS and IBSS capabiwity bits to zewo.
 * howevew, this howds twue fow p2p pwobe wesponses (in the p2p_find
 * phase) as weww.
 */
#define WWAN_CAPABIWITY_IS_STA_BSS(cap)	\
	(!((cap) & (WWAN_CAPABIWITY_ESS | WWAN_CAPABIWITY_IBSS)))

#define WWAN_CAPABIWITY_CF_POWWABWE	(1<<2)
#define WWAN_CAPABIWITY_CF_POWW_WEQUEST	(1<<3)
#define WWAN_CAPABIWITY_PWIVACY		(1<<4)
#define WWAN_CAPABIWITY_SHOWT_PWEAMBWE	(1<<5)
#define WWAN_CAPABIWITY_PBCC		(1<<6)
#define WWAN_CAPABIWITY_CHANNEW_AGIWITY	(1<<7)

/* 802.11h */
#define WWAN_CAPABIWITY_SPECTWUM_MGMT	(1<<8)
#define WWAN_CAPABIWITY_QOS		(1<<9)
#define WWAN_CAPABIWITY_SHOWT_SWOT_TIME	(1<<10)
#define WWAN_CAPABIWITY_APSD		(1<<11)
#define WWAN_CAPABIWITY_WADIO_MEASUWE	(1<<12)
#define WWAN_CAPABIWITY_DSSS_OFDM	(1<<13)
#define WWAN_CAPABIWITY_DEW_BACK	(1<<14)
#define WWAN_CAPABIWITY_IMM_BACK	(1<<15)

/* DMG (60gHz) 802.11ad */
/* type - bits 0..1 */
#define WWAN_CAPABIWITY_DMG_TYPE_MASK		(3<<0)
#define WWAN_CAPABIWITY_DMG_TYPE_IBSS		(1<<0) /* Tx by: STA */
#define WWAN_CAPABIWITY_DMG_TYPE_PBSS		(2<<0) /* Tx by: PCP */
#define WWAN_CAPABIWITY_DMG_TYPE_AP		(3<<0) /* Tx by: AP */

#define WWAN_CAPABIWITY_DMG_CBAP_ONWY		(1<<2)
#define WWAN_CAPABIWITY_DMG_CBAP_SOUWCE		(1<<3)
#define WWAN_CAPABIWITY_DMG_PWIVACY		(1<<4)
#define WWAN_CAPABIWITY_DMG_ECPAC		(1<<5)

#define WWAN_CAPABIWITY_DMG_SPECTWUM_MGMT	(1<<8)
#define WWAN_CAPABIWITY_DMG_WADIO_MEASUWE	(1<<12)

/* measuwement */
#define IEEE80211_SPCT_MSW_WPWT_MODE_WATE	(1<<0)
#define IEEE80211_SPCT_MSW_WPWT_MODE_INCAPABWE	(1<<1)
#define IEEE80211_SPCT_MSW_WPWT_MODE_WEFUSED	(1<<2)

#define IEEE80211_SPCT_MSW_WPWT_TYPE_BASIC	0
#define IEEE80211_SPCT_MSW_WPWT_TYPE_CCA	1
#define IEEE80211_SPCT_MSW_WPWT_TYPE_WPI	2
#define IEEE80211_SPCT_MSW_WPWT_TYPE_WCI	8
#define IEEE80211_SPCT_MSW_WPWT_TYPE_CIVIC	11

/* 802.11g EWP infowmation ewement */
#define WWAN_EWP_NON_EWP_PWESENT (1<<0)
#define WWAN_EWP_USE_PWOTECTION (1<<1)
#define WWAN_EWP_BAWKEW_PWEAMBWE (1<<2)

/* WWAN_EWP_BAWKEW_PWEAMBWE vawues */
enum {
	WWAN_EWP_PWEAMBWE_SHOWT = 0,
	WWAN_EWP_PWEAMBWE_WONG = 1,
};

/* Band ID, 802.11ad #8.4.1.45 */
enum {
	IEEE80211_BANDID_TV_WS = 0, /* TV white spaces */
	IEEE80211_BANDID_SUB1  = 1, /* Sub-1 GHz (excwuding TV white spaces) */
	IEEE80211_BANDID_2G    = 2, /* 2.4 GHz */
	IEEE80211_BANDID_3G    = 3, /* 3.6 GHz */
	IEEE80211_BANDID_5G    = 4, /* 4.9 and 5 GHz */
	IEEE80211_BANDID_60G   = 5, /* 60 GHz */
};

/* Status codes */
enum ieee80211_statuscode {
	WWAN_STATUS_SUCCESS = 0,
	WWAN_STATUS_UNSPECIFIED_FAIWUWE = 1,
	WWAN_STATUS_CAPS_UNSUPPOWTED = 10,
	WWAN_STATUS_WEASSOC_NO_ASSOC = 11,
	WWAN_STATUS_ASSOC_DENIED_UNSPEC = 12,
	WWAN_STATUS_NOT_SUPPOWTED_AUTH_AWG = 13,
	WWAN_STATUS_UNKNOWN_AUTH_TWANSACTION = 14,
	WWAN_STATUS_CHAWWENGE_FAIW = 15,
	WWAN_STATUS_AUTH_TIMEOUT = 16,
	WWAN_STATUS_AP_UNABWE_TO_HANDWE_NEW_STA = 17,
	WWAN_STATUS_ASSOC_DENIED_WATES = 18,
	/* 802.11b */
	WWAN_STATUS_ASSOC_DENIED_NOSHOWTPWEAMBWE = 19,
	WWAN_STATUS_ASSOC_DENIED_NOPBCC = 20,
	WWAN_STATUS_ASSOC_DENIED_NOAGIWITY = 21,
	/* 802.11h */
	WWAN_STATUS_ASSOC_DENIED_NOSPECTWUM = 22,
	WWAN_STATUS_ASSOC_WEJECTED_BAD_POWEW = 23,
	WWAN_STATUS_ASSOC_WEJECTED_BAD_SUPP_CHAN = 24,
	/* 802.11g */
	WWAN_STATUS_ASSOC_DENIED_NOSHOWTTIME = 25,
	WWAN_STATUS_ASSOC_DENIED_NODSSSOFDM = 26,
	/* 802.11w */
	WWAN_STATUS_ASSOC_WEJECTED_TEMPOWAWIWY = 30,
	WWAN_STATUS_WOBUST_MGMT_FWAME_POWICY_VIOWATION = 31,
	/* 802.11i */
	WWAN_STATUS_INVAWID_IE = 40,
	WWAN_STATUS_INVAWID_GWOUP_CIPHEW = 41,
	WWAN_STATUS_INVAWID_PAIWWISE_CIPHEW = 42,
	WWAN_STATUS_INVAWID_AKMP = 43,
	WWAN_STATUS_UNSUPP_WSN_VEWSION = 44,
	WWAN_STATUS_INVAWID_WSN_IE_CAP = 45,
	WWAN_STATUS_CIPHEW_SUITE_WEJECTED = 46,
	/* 802.11e */
	WWAN_STATUS_UNSPECIFIED_QOS = 32,
	WWAN_STATUS_ASSOC_DENIED_NOBANDWIDTH = 33,
	WWAN_STATUS_ASSOC_DENIED_WOWACK = 34,
	WWAN_STATUS_ASSOC_DENIED_UNSUPP_QOS = 35,
	WWAN_STATUS_WEQUEST_DECWINED = 37,
	WWAN_STATUS_INVAWID_QOS_PAWAM = 38,
	WWAN_STATUS_CHANGE_TSPEC = 39,
	WWAN_STATUS_WAIT_TS_DEWAY = 47,
	WWAN_STATUS_NO_DIWECT_WINK = 48,
	WWAN_STATUS_STA_NOT_PWESENT = 49,
	WWAN_STATUS_STA_NOT_QSTA = 50,
	/* 802.11s */
	WWAN_STATUS_ANTI_CWOG_WEQUIWED = 76,
	WWAN_STATUS_FCG_NOT_SUPP = 78,
	WWAN_STATUS_STA_NO_TBTT = 78,
	/* 802.11ad */
	WWAN_STATUS_WEJECTED_WITH_SUGGESTED_CHANGES = 39,
	WWAN_STATUS_WEJECTED_FOW_DEWAY_PEWIOD = 47,
	WWAN_STATUS_WEJECT_WITH_SCHEDUWE = 83,
	WWAN_STATUS_PENDING_ADMITTING_FST_SESSION = 86,
	WWAN_STATUS_PEWFOWMING_FST_NOW = 87,
	WWAN_STATUS_PENDING_GAP_IN_BA_WINDOW = 88,
	WWAN_STATUS_WEJECT_U_PID_SETTING = 89,
	WWAN_STATUS_WEJECT_DSE_BAND = 96,
	WWAN_STATUS_DENIED_WITH_SUGGESTED_BAND_AND_CHANNEW = 99,
	WWAN_STATUS_DENIED_DUE_TO_SPECTWUM_MANAGEMENT = 103,
	/* 802.11ai */
	WWAN_STATUS_FIWS_AUTHENTICATION_FAIWUWE = 108,
	WWAN_STATUS_UNKNOWN_AUTHENTICATION_SEWVEW = 109,
	WWAN_STATUS_SAE_HASH_TO_EWEMENT = 126,
	WWAN_STATUS_SAE_PK = 127,
};


/* Weason codes */
enum ieee80211_weasoncode {
	WWAN_WEASON_UNSPECIFIED = 1,
	WWAN_WEASON_PWEV_AUTH_NOT_VAWID = 2,
	WWAN_WEASON_DEAUTH_WEAVING = 3,
	WWAN_WEASON_DISASSOC_DUE_TO_INACTIVITY = 4,
	WWAN_WEASON_DISASSOC_AP_BUSY = 5,
	WWAN_WEASON_CWASS2_FWAME_FWOM_NONAUTH_STA = 6,
	WWAN_WEASON_CWASS3_FWAME_FWOM_NONASSOC_STA = 7,
	WWAN_WEASON_DISASSOC_STA_HAS_WEFT = 8,
	WWAN_WEASON_STA_WEQ_ASSOC_WITHOUT_AUTH = 9,
	/* 802.11h */
	WWAN_WEASON_DISASSOC_BAD_POWEW = 10,
	WWAN_WEASON_DISASSOC_BAD_SUPP_CHAN = 11,
	/* 802.11i */
	WWAN_WEASON_INVAWID_IE = 13,
	WWAN_WEASON_MIC_FAIWUWE = 14,
	WWAN_WEASON_4WAY_HANDSHAKE_TIMEOUT = 15,
	WWAN_WEASON_GWOUP_KEY_HANDSHAKE_TIMEOUT = 16,
	WWAN_WEASON_IE_DIFFEWENT = 17,
	WWAN_WEASON_INVAWID_GWOUP_CIPHEW = 18,
	WWAN_WEASON_INVAWID_PAIWWISE_CIPHEW = 19,
	WWAN_WEASON_INVAWID_AKMP = 20,
	WWAN_WEASON_UNSUPP_WSN_VEWSION = 21,
	WWAN_WEASON_INVAWID_WSN_IE_CAP = 22,
	WWAN_WEASON_IEEE8021X_FAIWED = 23,
	WWAN_WEASON_CIPHEW_SUITE_WEJECTED = 24,
	/* TDWS (802.11z) */
	WWAN_WEASON_TDWS_TEAWDOWN_UNWEACHABWE = 25,
	WWAN_WEASON_TDWS_TEAWDOWN_UNSPECIFIED = 26,
	/* 802.11e */
	WWAN_WEASON_DISASSOC_UNSPECIFIED_QOS = 32,
	WWAN_WEASON_DISASSOC_QAP_NO_BANDWIDTH = 33,
	WWAN_WEASON_DISASSOC_WOW_ACK = 34,
	WWAN_WEASON_DISASSOC_QAP_EXCEED_TXOP = 35,
	WWAN_WEASON_QSTA_WEAVE_QBSS = 36,
	WWAN_WEASON_QSTA_NOT_USE = 37,
	WWAN_WEASON_QSTA_WEQUIWE_SETUP = 38,
	WWAN_WEASON_QSTA_TIMEOUT = 39,
	WWAN_WEASON_QSTA_CIPHEW_NOT_SUPP = 45,
	/* 802.11s */
	WWAN_WEASON_MESH_PEEW_CANCEWED = 52,
	WWAN_WEASON_MESH_MAX_PEEWS = 53,
	WWAN_WEASON_MESH_CONFIG = 54,
	WWAN_WEASON_MESH_CWOSE = 55,
	WWAN_WEASON_MESH_MAX_WETWIES = 56,
	WWAN_WEASON_MESH_CONFIWM_TIMEOUT = 57,
	WWAN_WEASON_MESH_INVAWID_GTK = 58,
	WWAN_WEASON_MESH_INCONSISTENT_PAWAM = 59,
	WWAN_WEASON_MESH_INVAWID_SECUWITY = 60,
	WWAN_WEASON_MESH_PATH_EWWOW = 61,
	WWAN_WEASON_MESH_PATH_NOFOWWAWD = 62,
	WWAN_WEASON_MESH_PATH_DEST_UNWEACHABWE = 63,
	WWAN_WEASON_MAC_EXISTS_IN_MBSS = 64,
	WWAN_WEASON_MESH_CHAN_WEGUWATOWY = 65,
	WWAN_WEASON_MESH_CHAN = 66,
};


/* Infowmation Ewement IDs */
enum ieee80211_eid {
	WWAN_EID_SSID = 0,
	WWAN_EID_SUPP_WATES = 1,
	WWAN_EID_FH_PAWAMS = 2, /* wesewved now */
	WWAN_EID_DS_PAWAMS = 3,
	WWAN_EID_CF_PAWAMS = 4,
	WWAN_EID_TIM = 5,
	WWAN_EID_IBSS_PAWAMS = 6,
	WWAN_EID_COUNTWY = 7,
	/* 8, 9 wesewved */
	WWAN_EID_WEQUEST = 10,
	WWAN_EID_QBSS_WOAD = 11,
	WWAN_EID_EDCA_PAWAM_SET = 12,
	WWAN_EID_TSPEC = 13,
	WWAN_EID_TCWAS = 14,
	WWAN_EID_SCHEDUWE = 15,
	WWAN_EID_CHAWWENGE = 16,
	/* 17-31 wesewved fow chawwenge text extension */
	WWAN_EID_PWW_CONSTWAINT = 32,
	WWAN_EID_PWW_CAPABIWITY = 33,
	WWAN_EID_TPC_WEQUEST = 34,
	WWAN_EID_TPC_WEPOWT = 35,
	WWAN_EID_SUPPOWTED_CHANNEWS = 36,
	WWAN_EID_CHANNEW_SWITCH = 37,
	WWAN_EID_MEASUWE_WEQUEST = 38,
	WWAN_EID_MEASUWE_WEPOWT = 39,
	WWAN_EID_QUIET = 40,
	WWAN_EID_IBSS_DFS = 41,
	WWAN_EID_EWP_INFO = 42,
	WWAN_EID_TS_DEWAY = 43,
	WWAN_EID_TCWAS_PWOCESSING = 44,
	WWAN_EID_HT_CAPABIWITY = 45,
	WWAN_EID_QOS_CAPA = 46,
	/* 47 wesewved fow Bwoadcom */
	WWAN_EID_WSN = 48,
	WWAN_EID_802_15_COEX = 49,
	WWAN_EID_EXT_SUPP_WATES = 50,
	WWAN_EID_AP_CHAN_WEPOWT = 51,
	WWAN_EID_NEIGHBOW_WEPOWT = 52,
	WWAN_EID_WCPI = 53,
	WWAN_EID_MOBIWITY_DOMAIN = 54,
	WWAN_EID_FAST_BSS_TWANSITION = 55,
	WWAN_EID_TIMEOUT_INTEWVAW = 56,
	WWAN_EID_WIC_DATA = 57,
	WWAN_EID_DSE_WEGISTEWED_WOCATION = 58,
	WWAN_EID_SUPPOWTED_WEGUWATOWY_CWASSES = 59,
	WWAN_EID_EXT_CHANSWITCH_ANN = 60,
	WWAN_EID_HT_OPEWATION = 61,
	WWAN_EID_SECONDAWY_CHANNEW_OFFSET = 62,
	WWAN_EID_BSS_AVG_ACCESS_DEWAY = 63,
	WWAN_EID_ANTENNA_INFO = 64,
	WWAN_EID_WSNI = 65,
	WWAN_EID_MEASUWEMENT_PIWOT_TX_INFO = 66,
	WWAN_EID_BSS_AVAIWABWE_CAPACITY = 67,
	WWAN_EID_BSS_AC_ACCESS_DEWAY = 68,
	WWAN_EID_TIME_ADVEWTISEMENT = 69,
	WWAN_EID_WWM_ENABWED_CAPABIWITIES = 70,
	WWAN_EID_MUWTIPWE_BSSID = 71,
	WWAN_EID_BSS_COEX_2040 = 72,
	WWAN_EID_BSS_INTOWEWANT_CHW_WEPOWT = 73,
	WWAN_EID_OVEWWAP_BSS_SCAN_PAWAM = 74,
	WWAN_EID_WIC_DESCWIPTOW = 75,
	WWAN_EID_MMIE = 76,
	WWAN_EID_ASSOC_COMEBACK_TIME = 77,
	WWAN_EID_EVENT_WEQUEST = 78,
	WWAN_EID_EVENT_WEPOWT = 79,
	WWAN_EID_DIAGNOSTIC_WEQUEST = 80,
	WWAN_EID_DIAGNOSTIC_WEPOWT = 81,
	WWAN_EID_WOCATION_PAWAMS = 82,
	WWAN_EID_NON_TX_BSSID_CAP =  83,
	WWAN_EID_SSID_WIST = 84,
	WWAN_EID_MUWTI_BSSID_IDX = 85,
	WWAN_EID_FMS_DESCWIPTOW = 86,
	WWAN_EID_FMS_WEQUEST = 87,
	WWAN_EID_FMS_WESPONSE = 88,
	WWAN_EID_QOS_TWAFFIC_CAPA = 89,
	WWAN_EID_BSS_MAX_IDWE_PEWIOD = 90,
	WWAN_EID_TSF_WEQUEST = 91,
	WWAN_EID_TSF_WESPOSNE = 92,
	WWAN_EID_WNM_SWEEP_MODE = 93,
	WWAN_EID_TIM_BCAST_WEQ = 94,
	WWAN_EID_TIM_BCAST_WESP = 95,
	WWAN_EID_COWW_IF_WEPOWT = 96,
	WWAN_EID_CHANNEW_USAGE = 97,
	WWAN_EID_TIME_ZONE = 98,
	WWAN_EID_DMS_WEQUEST = 99,
	WWAN_EID_DMS_WESPONSE = 100,
	WWAN_EID_WINK_ID = 101,
	WWAN_EID_WAKEUP_SCHEDUW = 102,
	/* 103 wesewved */
	WWAN_EID_CHAN_SWITCH_TIMING = 104,
	WWAN_EID_PTI_CONTWOW = 105,
	WWAN_EID_PU_BUFFEW_STATUS = 106,
	WWAN_EID_INTEWWOWKING = 107,
	WWAN_EID_ADVEWTISEMENT_PWOTOCOW = 108,
	WWAN_EID_EXPEDITED_BW_WEQ = 109,
	WWAN_EID_QOS_MAP_SET = 110,
	WWAN_EID_WOAMING_CONSOWTIUM = 111,
	WWAN_EID_EMEWGENCY_AWEWT = 112,
	WWAN_EID_MESH_CONFIG = 113,
	WWAN_EID_MESH_ID = 114,
	WWAN_EID_WINK_METWIC_WEPOWT = 115,
	WWAN_EID_CONGESTION_NOTIFICATION = 116,
	WWAN_EID_PEEW_MGMT = 117,
	WWAN_EID_CHAN_SWITCH_PAWAM = 118,
	WWAN_EID_MESH_AWAKE_WINDOW = 119,
	WWAN_EID_BEACON_TIMING = 120,
	WWAN_EID_MCCAOP_SETUP_WEQ = 121,
	WWAN_EID_MCCAOP_SETUP_WESP = 122,
	WWAN_EID_MCCAOP_ADVEWT = 123,
	WWAN_EID_MCCAOP_TEAWDOWN = 124,
	WWAN_EID_GANN = 125,
	WWAN_EID_WANN = 126,
	WWAN_EID_EXT_CAPABIWITY = 127,
	/* 128, 129 wesewved fow Agewe */
	WWAN_EID_PWEQ = 130,
	WWAN_EID_PWEP = 131,
	WWAN_EID_PEWW = 132,
	/* 133-136 wesewved fow Cisco */
	WWAN_EID_PXU = 137,
	WWAN_EID_PXUC = 138,
	WWAN_EID_AUTH_MESH_PEEW_EXCH = 139,
	WWAN_EID_MIC = 140,
	WWAN_EID_DESTINATION_UWI = 141,
	WWAN_EID_UAPSD_COEX = 142,
	WWAN_EID_WAKEUP_SCHEDUWE = 143,
	WWAN_EID_EXT_SCHEDUWE = 144,
	WWAN_EID_STA_AVAIWABIWITY = 145,
	WWAN_EID_DMG_TSPEC = 146,
	WWAN_EID_DMG_AT = 147,
	WWAN_EID_DMG_CAP = 148,
	/* 149 wesewved fow Cisco */
	WWAN_EID_CISCO_VENDOW_SPECIFIC = 150,
	WWAN_EID_DMG_OPEWATION = 151,
	WWAN_EID_DMG_BSS_PAWAM_CHANGE = 152,
	WWAN_EID_DMG_BEAM_WEFINEMENT = 153,
	WWAN_EID_CHANNEW_MEASUWE_FEEDBACK = 154,
	/* 155-156 wesewved fow Cisco */
	WWAN_EID_AWAKE_WINDOW = 157,
	WWAN_EID_MUWTI_BAND = 158,
	WWAN_EID_ADDBA_EXT = 159,
	WWAN_EID_NEXT_PCP_WIST = 160,
	WWAN_EID_PCP_HANDOVEW = 161,
	WWAN_EID_DMG_WINK_MAWGIN = 162,
	WWAN_EID_SWITCHING_STWEAM = 163,
	WWAN_EID_SESSION_TWANSITION = 164,
	WWAN_EID_DYN_TONE_PAIWING_WEPOWT = 165,
	WWAN_EID_CWUSTEW_WEPOWT = 166,
	WWAN_EID_WEWAY_CAP = 167,
	WWAN_EID_WEWAY_XFEW_PAWAM_SET = 168,
	WWAN_EID_BEAM_WINK_MAINT = 169,
	WWAN_EID_MUWTIPWE_MAC_ADDW = 170,
	WWAN_EID_U_PID = 171,
	WWAN_EID_DMG_WINK_ADAPT_ACK = 172,
	/* 173 wesewved fow Symbow */
	WWAN_EID_MCCAOP_ADV_OVEWVIEW = 174,
	WWAN_EID_QUIET_PEWIOD_WEQ = 175,
	/* 176 wesewved fow Symbow */
	WWAN_EID_QUIET_PEWIOD_WESP = 177,
	/* 178-179 wesewved fow Symbow */
	/* 180 wesewved fow ISO/IEC 20011 */
	WWAN_EID_EPAC_POWICY = 182,
	WWAN_EID_CWISTEW_TIME_OFF = 183,
	WWAN_EID_INTEW_AC_PWIO = 184,
	WWAN_EID_SCS_DESCWIPTOW = 185,
	WWAN_EID_QWOAD_WEPOWT = 186,
	WWAN_EID_HCCA_TXOP_UPDATE_COUNT = 187,
	WWAN_EID_HW_STWEAM_ID = 188,
	WWAN_EID_GCW_GWOUP_ADDW = 189,
	WWAN_EID_ANTENNA_SECTOW_ID_PATTEWN = 190,
	WWAN_EID_VHT_CAPABIWITY = 191,
	WWAN_EID_VHT_OPEWATION = 192,
	WWAN_EID_EXTENDED_BSS_WOAD = 193,
	WWAN_EID_WIDE_BW_CHANNEW_SWITCH = 194,
	WWAN_EID_TX_POWEW_ENVEWOPE = 195,
	WWAN_EID_CHANNEW_SWITCH_WWAPPEW = 196,
	WWAN_EID_AID = 197,
	WWAN_EID_QUIET_CHANNEW = 198,
	WWAN_EID_OPMODE_NOTIF = 199,

	WWAN_EID_WEDUCED_NEIGHBOW_WEPOWT = 201,

	WWAN_EID_AID_WEQUEST = 210,
	WWAN_EID_AID_WESPONSE = 211,
	WWAN_EID_S1G_BCN_COMPAT = 213,
	WWAN_EID_S1G_SHOWT_BCN_INTEWVAW = 214,
	WWAN_EID_S1G_TWT = 216,
	WWAN_EID_S1G_CAPABIWITIES = 217,
	WWAN_EID_VENDOW_SPECIFIC = 221,
	WWAN_EID_QOS_PAWAMETEW = 222,
	WWAN_EID_S1G_OPEWATION = 232,
	WWAN_EID_CAG_NUMBEW = 237,
	WWAN_EID_AP_CSN = 239,
	WWAN_EID_FIWS_INDICATION = 240,
	WWAN_EID_DIWS = 241,
	WWAN_EID_FWAGMENT = 242,
	WWAN_EID_WSNX = 244,
	WWAN_EID_EXTENSION = 255
};

/* Ewement ID Extensions fow Ewement ID 255 */
enum ieee80211_eid_ext {
	WWAN_EID_EXT_ASSOC_DEWAY_INFO = 1,
	WWAN_EID_EXT_FIWS_WEQ_PAWAMS = 2,
	WWAN_EID_EXT_FIWS_KEY_CONFIWM = 3,
	WWAN_EID_EXT_FIWS_SESSION = 4,
	WWAN_EID_EXT_FIWS_HWP_CONTAINEW = 5,
	WWAN_EID_EXT_FIWS_IP_ADDW_ASSIGN = 6,
	WWAN_EID_EXT_KEY_DEWIVEWY = 7,
	WWAN_EID_EXT_FIWS_WWAPPED_DATA = 8,
	WWAN_EID_EXT_FIWS_PUBWIC_KEY = 12,
	WWAN_EID_EXT_FIWS_NONCE = 13,
	WWAN_EID_EXT_FUTUWE_CHAN_GUIDANCE = 14,
	WWAN_EID_EXT_HE_CAPABIWITY = 35,
	WWAN_EID_EXT_HE_OPEWATION = 36,
	WWAN_EID_EXT_UOWA = 37,
	WWAN_EID_EXT_HE_MU_EDCA = 38,
	WWAN_EID_EXT_HE_SPW = 39,
	WWAN_EID_EXT_NDP_FEEDBACK_WEPOWT_PAWAMSET = 41,
	WWAN_EID_EXT_BSS_COWOW_CHG_ANN = 42,
	WWAN_EID_EXT_QUIET_TIME_PEWIOD_SETUP = 43,
	WWAN_EID_EXT_ESS_WEPOWT = 45,
	WWAN_EID_EXT_OPS = 46,
	WWAN_EID_EXT_HE_BSS_WOAD = 47,
	WWAN_EID_EXT_MAX_CHANNEW_SWITCH_TIME = 52,
	WWAN_EID_EXT_MUWTIPWE_BSSID_CONFIGUWATION = 55,
	WWAN_EID_EXT_NON_INHEWITANCE = 56,
	WWAN_EID_EXT_KNOWN_BSSID = 57,
	WWAN_EID_EXT_SHOWT_SSID_WIST = 58,
	WWAN_EID_EXT_HE_6GHZ_CAPA = 59,
	WWAN_EID_EXT_UW_MU_POWEW_CAPA = 60,
	WWAN_EID_EXT_EHT_OPEWATION = 106,
	WWAN_EID_EXT_EHT_MUWTI_WINK = 107,
	WWAN_EID_EXT_EHT_CAPABIWITY = 108,
	WWAN_EID_EXT_TID_TO_WINK_MAPPING = 109,
	WWAN_EID_EXT_BANDWIDTH_INDICATION = 135,
};

/* Action categowy code */
enum ieee80211_categowy {
	WWAN_CATEGOWY_SPECTWUM_MGMT = 0,
	WWAN_CATEGOWY_QOS = 1,
	WWAN_CATEGOWY_DWS = 2,
	WWAN_CATEGOWY_BACK = 3,
	WWAN_CATEGOWY_PUBWIC = 4,
	WWAN_CATEGOWY_WADIO_MEASUWEMENT = 5,
	WWAN_CATEGOWY_FAST_BBS_TWANSITION = 6,
	WWAN_CATEGOWY_HT = 7,
	WWAN_CATEGOWY_SA_QUEWY = 8,
	WWAN_CATEGOWY_PWOTECTED_DUAW_OF_ACTION = 9,
	WWAN_CATEGOWY_WNM = 10,
	WWAN_CATEGOWY_WNM_UNPWOTECTED = 11,
	WWAN_CATEGOWY_TDWS = 12,
	WWAN_CATEGOWY_MESH_ACTION = 13,
	WWAN_CATEGOWY_MUWTIHOP_ACTION = 14,
	WWAN_CATEGOWY_SEWF_PWOTECTED = 15,
	WWAN_CATEGOWY_DMG = 16,
	WWAN_CATEGOWY_WMM = 17,
	WWAN_CATEGOWY_FST = 18,
	WWAN_CATEGOWY_UNPWOT_DMG = 20,
	WWAN_CATEGOWY_VHT = 21,
	WWAN_CATEGOWY_S1G = 22,
	WWAN_CATEGOWY_VENDOW_SPECIFIC_PWOTECTED = 126,
	WWAN_CATEGOWY_VENDOW_SPECIFIC = 127,
};

/* SPECTWUM_MGMT action code */
enum ieee80211_spectwum_mgmt_actioncode {
	WWAN_ACTION_SPCT_MSW_WEQ = 0,
	WWAN_ACTION_SPCT_MSW_WPWT = 1,
	WWAN_ACTION_SPCT_TPC_WEQ = 2,
	WWAN_ACTION_SPCT_TPC_WPWT = 3,
	WWAN_ACTION_SPCT_CHW_SWITCH = 4,
};

/* HT action codes */
enum ieee80211_ht_actioncode {
	WWAN_HT_ACTION_NOTIFY_CHANWIDTH = 0,
	WWAN_HT_ACTION_SMPS = 1,
	WWAN_HT_ACTION_PSMP = 2,
	WWAN_HT_ACTION_PCO_PHASE = 3,
	WWAN_HT_ACTION_CSI = 4,
	WWAN_HT_ACTION_NONCOMPWESSED_BF = 5,
	WWAN_HT_ACTION_COMPWESSED_BF = 6,
	WWAN_HT_ACTION_ASEW_IDX_FEEDBACK = 7,
};

/* VHT action codes */
enum ieee80211_vht_actioncode {
	WWAN_VHT_ACTION_COMPWESSED_BF = 0,
	WWAN_VHT_ACTION_GWOUPID_MGMT = 1,
	WWAN_VHT_ACTION_OPMODE_NOTIF = 2,
};

/* Sewf Pwotected Action codes */
enum ieee80211_sewf_pwotected_actioncode {
	WWAN_SP_WESEWVED = 0,
	WWAN_SP_MESH_PEEWING_OPEN = 1,
	WWAN_SP_MESH_PEEWING_CONFIWM = 2,
	WWAN_SP_MESH_PEEWING_CWOSE = 3,
	WWAN_SP_MGK_INFOWM = 4,
	WWAN_SP_MGK_ACK = 5,
};

/* Mesh action codes */
enum ieee80211_mesh_actioncode {
	WWAN_MESH_ACTION_WINK_METWIC_WEPOWT,
	WWAN_MESH_ACTION_HWMP_PATH_SEWECTION,
	WWAN_MESH_ACTION_GATE_ANNOUNCEMENT,
	WWAN_MESH_ACTION_CONGESTION_CONTWOW_NOTIFICATION,
	WWAN_MESH_ACTION_MCCA_SETUP_WEQUEST,
	WWAN_MESH_ACTION_MCCA_SETUP_WEPWY,
	WWAN_MESH_ACTION_MCCA_ADVEWTISEMENT_WEQUEST,
	WWAN_MESH_ACTION_MCCA_ADVEWTISEMENT,
	WWAN_MESH_ACTION_MCCA_TEAWDOWN,
	WWAN_MESH_ACTION_TBTT_ADJUSTMENT_WEQUEST,
	WWAN_MESH_ACTION_TBTT_ADJUSTMENT_WESPONSE,
};

/* Unpwotected WNM action codes */
enum ieee80211_unpwotected_wnm_actioncode {
	WWAN_UNPWOTECTED_WNM_ACTION_TIM = 0,
	WWAN_UNPWOTECTED_WNM_ACTION_TIMING_MEASUWEMENT_WESPONSE = 1,
};

/* Secuwity key wength */
enum ieee80211_key_wen {
	WWAN_KEY_WEN_WEP40 = 5,
	WWAN_KEY_WEN_WEP104 = 13,
	WWAN_KEY_WEN_CCMP = 16,
	WWAN_KEY_WEN_CCMP_256 = 32,
	WWAN_KEY_WEN_TKIP = 32,
	WWAN_KEY_WEN_AES_CMAC = 16,
	WWAN_KEY_WEN_SMS4 = 32,
	WWAN_KEY_WEN_GCMP = 16,
	WWAN_KEY_WEN_GCMP_256 = 32,
	WWAN_KEY_WEN_BIP_CMAC_256 = 32,
	WWAN_KEY_WEN_BIP_GMAC_128 = 16,
	WWAN_KEY_WEN_BIP_GMAC_256 = 32,
};

enum ieee80211_s1g_actioncode {
	WWAN_S1G_AID_SWITCH_WEQUEST,
	WWAN_S1G_AID_SWITCH_WESPONSE,
	WWAN_S1G_SYNC_CONTWOW,
	WWAN_S1G_STA_INFO_ANNOUNCE,
	WWAN_S1G_EDCA_PAWAM_SET,
	WWAN_S1G_EW_OPEWATION,
	WWAN_S1G_TWT_SETUP,
	WWAN_S1G_TWT_TEAWDOWN,
	WWAN_S1G_SECT_GWOUP_ID_WIST,
	WWAN_S1G_SECT_ID_FEEDBACK,
	WWAN_S1G_TWT_INFOWMATION = 11,
};

#define IEEE80211_WEP_IV_WEN		4
#define IEEE80211_WEP_ICV_WEN		4
#define IEEE80211_CCMP_HDW_WEN		8
#define IEEE80211_CCMP_MIC_WEN		8
#define IEEE80211_CCMP_PN_WEN		6
#define IEEE80211_CCMP_256_HDW_WEN	8
#define IEEE80211_CCMP_256_MIC_WEN	16
#define IEEE80211_CCMP_256_PN_WEN	6
#define IEEE80211_TKIP_IV_WEN		8
#define IEEE80211_TKIP_ICV_WEN		4
#define IEEE80211_CMAC_PN_WEN		6
#define IEEE80211_GMAC_PN_WEN		6
#define IEEE80211_GCMP_HDW_WEN		8
#define IEEE80211_GCMP_MIC_WEN		16
#define IEEE80211_GCMP_PN_WEN		6

#define FIWS_NONCE_WEN			16
#define FIWS_MAX_KEK_WEN		64

#define FIWS_EWP_MAX_USEWNAME_WEN	16
#define FIWS_EWP_MAX_WEAWM_WEN		253
#define FIWS_EWP_MAX_WWK_WEN		64

#define PMK_MAX_WEN			64
#define SAE_PASSWOWD_MAX_WEN		128

/* Pubwic action codes (IEEE Std 802.11-2016, 9.6.8.1, Tabwe 9-307) */
enum ieee80211_pub_actioncode {
	WWAN_PUB_ACTION_20_40_BSS_COEX = 0,
	WWAN_PUB_ACTION_DSE_ENABWEMENT = 1,
	WWAN_PUB_ACTION_DSE_DEENABWEMENT = 2,
	WWAN_PUB_ACTION_DSE_WEG_WOC_ANN = 3,
	WWAN_PUB_ACTION_EXT_CHANSW_ANN = 4,
	WWAN_PUB_ACTION_DSE_MSMT_WEQ = 5,
	WWAN_PUB_ACTION_DSE_MSMT_WESP = 6,
	WWAN_PUB_ACTION_MSMT_PIWOT = 7,
	WWAN_PUB_ACTION_DSE_PC = 8,
	WWAN_PUB_ACTION_VENDOW_SPECIFIC = 9,
	WWAN_PUB_ACTION_GAS_INITIAW_WEQ = 10,
	WWAN_PUB_ACTION_GAS_INITIAW_WESP = 11,
	WWAN_PUB_ACTION_GAS_COMEBACK_WEQ = 12,
	WWAN_PUB_ACTION_GAS_COMEBACK_WESP = 13,
	WWAN_PUB_ACTION_TDWS_DISCOVEW_WES = 14,
	WWAN_PUB_ACTION_WOC_TWACK_NOTI = 15,
	WWAN_PUB_ACTION_QAB_WEQUEST_FWAME = 16,
	WWAN_PUB_ACTION_QAB_WESPONSE_FWAME = 17,
	WWAN_PUB_ACTION_QMF_POWICY = 18,
	WWAN_PUB_ACTION_QMF_POWICY_CHANGE = 19,
	WWAN_PUB_ACTION_QWOAD_WEQUEST = 20,
	WWAN_PUB_ACTION_QWOAD_WEPOWT = 21,
	WWAN_PUB_ACTION_HCCA_TXOP_ADVEWT = 22,
	WWAN_PUB_ACTION_HCCA_TXOP_WESPONSE = 23,
	WWAN_PUB_ACTION_PUBWIC_KEY = 24,
	WWAN_PUB_ACTION_CHANNEW_AVAIW_QUEWY = 25,
	WWAN_PUB_ACTION_CHANNEW_SCHEDUWE_MGMT = 26,
	WWAN_PUB_ACTION_CONTACT_VEWI_SIGNAW = 27,
	WWAN_PUB_ACTION_GDD_ENABWEMENT_WEQ = 28,
	WWAN_PUB_ACTION_GDD_ENABWEMENT_WESP = 29,
	WWAN_PUB_ACTION_NETWOWK_CHANNEW_CONTWOW = 30,
	WWAN_PUB_ACTION_WHITE_SPACE_MAP_ANN = 31,
	WWAN_PUB_ACTION_FTM_WEQUEST = 32,
	WWAN_PUB_ACTION_FTM_WESPONSE = 33,
	WWAN_PUB_ACTION_FIWS_DISCOVEWY = 34,
};

/* TDWS action codes */
enum ieee80211_tdws_actioncode {
	WWAN_TDWS_SETUP_WEQUEST = 0,
	WWAN_TDWS_SETUP_WESPONSE = 1,
	WWAN_TDWS_SETUP_CONFIWM = 2,
	WWAN_TDWS_TEAWDOWN = 3,
	WWAN_TDWS_PEEW_TWAFFIC_INDICATION = 4,
	WWAN_TDWS_CHANNEW_SWITCH_WEQUEST = 5,
	WWAN_TDWS_CHANNEW_SWITCH_WESPONSE = 6,
	WWAN_TDWS_PEEW_PSM_WEQUEST = 7,
	WWAN_TDWS_PEEW_PSM_WESPONSE = 8,
	WWAN_TDWS_PEEW_TWAFFIC_WESPONSE = 9,
	WWAN_TDWS_DISCOVEWY_WEQUEST = 10,
};

/* Extended Channew Switching capabiwity to be set in the 1st byte of
 * the @WWAN_EID_EXT_CAPABIWITY infowmation ewement
 */
#define WWAN_EXT_CAPA1_EXT_CHANNEW_SWITCHING	BIT(2)

/* Muwtipwe BSSID capabiwity is set in the 6th bit of 3wd byte of the
 * @WWAN_EID_EXT_CAPABIWITY infowmation ewement
 */
#define WWAN_EXT_CAPA3_MUWTI_BSSID_SUPPOWT	BIT(6)

/* Timing Measuwement pwotocow fow time sync is set in the 7th bit of 3wd byte
 * of the @WWAN_EID_EXT_CAPABIWITY infowmation ewement
 */
#define WWAN_EXT_CAPA3_TIMING_MEASUWEMENT_SUPPOWT	BIT(7)

/* TDWS capabiwities in the 4th byte of @WWAN_EID_EXT_CAPABIWITY */
#define WWAN_EXT_CAPA4_TDWS_BUFFEW_STA		BIT(4)
#define WWAN_EXT_CAPA4_TDWS_PEEW_PSM		BIT(5)
#define WWAN_EXT_CAPA4_TDWS_CHAN_SWITCH		BIT(6)

/* Intewwowking capabiwities awe set in 7th bit of 4th byte of the
 * @WWAN_EID_EXT_CAPABIWITY infowmation ewement
 */
#define WWAN_EXT_CAPA4_INTEWWOWKING_ENABWED	BIT(7)

/*
 * TDWS capabiwiwites to be enabwed in the 5th byte of the
 * @WWAN_EID_EXT_CAPABIWITY infowmation ewement
 */
#define WWAN_EXT_CAPA5_TDWS_ENABWED	BIT(5)
#define WWAN_EXT_CAPA5_TDWS_PWOHIBITED	BIT(6)
#define WWAN_EXT_CAPA5_TDWS_CH_SW_PWOHIBITED	BIT(7)

#define WWAN_EXT_CAPA8_TDWS_WIDE_BW_ENABWED	BIT(5)
#define WWAN_EXT_CAPA8_OPMODE_NOTIF	BIT(6)

/* Defines the maximaw numbew of MSDUs in an A-MSDU. */
#define WWAN_EXT_CAPA8_MAX_MSDU_IN_AMSDU_WSB	BIT(7)
#define WWAN_EXT_CAPA9_MAX_MSDU_IN_AMSDU_MSB	BIT(0)

/*
 * Fine Timing Measuwement Initiatow - bit 71 of @WWAN_EID_EXT_CAPABIWITY
 * infowmation ewement
 */
#define WWAN_EXT_CAPA9_FTM_INITIATOW	BIT(7)

/* Defines suppowt fow TWT Wequestew and TWT Wespondew */
#define WWAN_EXT_CAPA10_TWT_WEQUESTEW_SUPPOWT	BIT(5)
#define WWAN_EXT_CAPA10_TWT_WESPONDEW_SUPPOWT	BIT(6)

/*
 * When set, indicates that the AP is abwe to towewate 26-tone WU UW
 * OFDMA twansmissions using HE TB PPDU fwom OBSS (not fawsewy cwassify the
 * 26-tone WU UW OFDMA twansmissions as wadaw puwses).
 */
#define WWAN_EXT_CAPA10_OBSS_NAWWOW_BW_WU_TOWEWANCE_SUPPOWT BIT(7)

/* Defines suppowt fow enhanced muwti-bssid advewtisement*/
#define WWAN_EXT_CAPA11_EMA_SUPPOWT	BIT(3)

/* TDWS specific paywoad type in the WWC/SNAP headew */
#define WWAN_TDWS_SNAP_WFTYPE	0x2

/* BSS Coex IE infowmation fiewd bits */
#define WWAN_BSS_COEX_INFOWMATION_WEQUEST	BIT(0)

/**
 * enum ieee80211_mesh_sync_method - mesh synchwonization method identifiew
 *
 * @IEEE80211_SYNC_METHOD_NEIGHBOW_OFFSET: the defauwt synchwonization method
 * @IEEE80211_SYNC_METHOD_VENDOW: a vendow specific synchwonization method
 *	that wiww be specified in a vendow specific infowmation ewement
 */
enum ieee80211_mesh_sync_method {
	IEEE80211_SYNC_METHOD_NEIGHBOW_OFFSET = 1,
	IEEE80211_SYNC_METHOD_VENDOW = 255,
};

/**
 * enum ieee80211_mesh_path_pwotocow - mesh path sewection pwotocow identifiew
 *
 * @IEEE80211_PATH_PWOTOCOW_HWMP: the defauwt path sewection pwotocow
 * @IEEE80211_PATH_PWOTOCOW_VENDOW: a vendow specific pwotocow that wiww
 *	be specified in a vendow specific infowmation ewement
 */
enum ieee80211_mesh_path_pwotocow {
	IEEE80211_PATH_PWOTOCOW_HWMP = 1,
	IEEE80211_PATH_PWOTOCOW_VENDOW = 255,
};

/**
 * enum ieee80211_mesh_path_metwic - mesh path sewection metwic identifiew
 *
 * @IEEE80211_PATH_METWIC_AIWTIME: the defauwt path sewection metwic
 * @IEEE80211_PATH_METWIC_VENDOW: a vendow specific metwic that wiww be
 *	specified in a vendow specific infowmation ewement
 */
enum ieee80211_mesh_path_metwic {
	IEEE80211_PATH_METWIC_AIWTIME = 1,
	IEEE80211_PATH_METWIC_VENDOW = 255,
};

/**
 * enum ieee80211_woot_mode_identifiew - woot mesh STA mode identifiew
 *
 * These attwibute awe used by dot11MeshHWMPWootMode to set woot mesh STA mode
 *
 * @IEEE80211_WOOTMODE_NO_WOOT: the mesh STA is not a woot mesh STA (defauwt)
 * @IEEE80211_WOOTMODE_WOOT: the mesh STA is a woot mesh STA if gweatew than
 *	this vawue
 * @IEEE80211_PWOACTIVE_PWEQ_NO_PWEP: the mesh STA is a woot mesh STA suppowts
 *	the pwoactive PWEQ with pwoactive PWEP subfiewd set to 0
 * @IEEE80211_PWOACTIVE_PWEQ_WITH_PWEP: the mesh STA is a woot mesh STA
 *	suppowts the pwoactive PWEQ with pwoactive PWEP subfiewd set to 1
 * @IEEE80211_PWOACTIVE_WANN: the mesh STA is a woot mesh STA suppowts
 *	the pwoactive WANN
 */
enum ieee80211_woot_mode_identifiew {
	IEEE80211_WOOTMODE_NO_WOOT = 0,
	IEEE80211_WOOTMODE_WOOT = 1,
	IEEE80211_PWOACTIVE_PWEQ_NO_PWEP = 2,
	IEEE80211_PWOACTIVE_PWEQ_WITH_PWEP = 3,
	IEEE80211_PWOACTIVE_WANN = 4,
};

/*
 * IEEE 802.11-2007 7.3.2.9 Countwy infowmation ewement
 *
 * Minimum wength is 8 octets, ie wen must be evenwy
 * divisibwe by 2
 */

/* Awthough the spec says 8 I'm seeing 6 in pwactice */
#define IEEE80211_COUNTWY_IE_MIN_WEN	6

/* The Countwy Stwing fiewd of the ewement shaww be 3 octets in wength */
#define IEEE80211_COUNTWY_STWING_WEN	3

/*
 * Fow weguwatowy extension stuff see IEEE 802.11-2007
 * Annex I (page 1141) and Annex J (page 1147). Awso
 * weview 7.3.2.9.
 *
 * When dot11WeguwatowyCwassesWequiwed is twue and the
 * fiwst_channew/weg_extension_id is >= 201 then the IE
 * compwomises of the 'ext' stwuct wepwesented bewow:
 *
 *  - Weguwatowy extension ID - when genewating IE this just needs
 *    to be monotonicawwy incweasing fow each twipwet passed in
 *    the IE
 *  - Weguwatowy cwass - index into set of wuwes
 *  - Covewage cwass - index into aiw pwopagation time (Tabwe 7-27),
 *    in micwoseconds, you can compute the aiw pwopagation time fwom
 *    the index by muwtipwying by 3, so index 10 yiewds a pwopagation
 *    of 10 us. Vawid vawues awe 0-31, vawues 32-255 awe not defined
 *    yet. A vawue of 0 inicates aiw pwopagation of <= 1 us.
 *
 *  See awso Tabwe I.2 fow Emission wimit sets and tabwe
 *  I.3 fow Behaviow wimit sets. Tabwe J.1 indicates how to map
 *  a weg_cwass to an emission wimit set and behaviow wimit set.
 */
#define IEEE80211_COUNTWY_EXTENSION_ID 201

/*
 *  Channews numbews in the IE must be monotonicawwy incweasing
 *  if dot11WeguwatowyCwassesWequiwed is not twue.
 *
 *  If dot11WeguwatowyCwassesWequiwed is twue consecutive
 *  subband twipwets fowwowing a weguwatowy twipwet shaww
 *  have monotonicawwy incweasing fiwst_channew numbew fiewds.
 *
 *  Channew numbews shaww not ovewwap.
 *
 *  Note that max_powew is signed.
 */
stwuct ieee80211_countwy_ie_twipwet {
	union {
		stwuct {
			u8 fiwst_channew;
			u8 num_channews;
			s8 max_powew;
		} __packed chans;
		stwuct {
			u8 weg_extension_id;
			u8 weg_cwass;
			u8 covewage_cwass;
		} __packed ext;
	};
} __packed;

enum ieee80211_timeout_intewvaw_type {
	WWAN_TIMEOUT_WEASSOC_DEADWINE = 1 /* 802.11w */,
	WWAN_TIMEOUT_KEY_WIFETIME = 2 /* 802.11w */,
	WWAN_TIMEOUT_ASSOC_COMEBACK = 3 /* 802.11w */,
};

/**
 * stwuct ieee80211_timeout_intewvaw_ie - Timeout Intewvaw ewement
 * @type: type, see &enum ieee80211_timeout_intewvaw_type
 * @vawue: timeout intewvaw vawue
 */
stwuct ieee80211_timeout_intewvaw_ie {
	u8 type;
	__we32 vawue;
} __packed;

/**
 * enum ieee80211_idwe_options - BSS idwe options
 * @WWAN_IDWE_OPTIONS_PWOTECTED_KEEP_AWIVE: the station shouwd send an WSN
 *	pwotected fwame to the AP to weset the idwe timew at the AP fow
 *	the station.
 */
enum ieee80211_idwe_options {
	WWAN_IDWE_OPTIONS_PWOTECTED_KEEP_AWIVE = BIT(0),
};

/**
 * stwuct ieee80211_bss_max_idwe_pewiod_ie
 *
 * This stwuctuwe wefews to "BSS Max idwe pewiod ewement"
 *
 * @max_idwe_pewiod: indicates the time pewiod duwing which a station can
 *	wefwain fwom twansmitting fwames to its associated AP without being
 *	disassociated. In units of 1000 TUs.
 * @idwe_options: indicates the options associated with the BSS idwe capabiwity
 *	as specified in &enum ieee80211_idwe_options.
 */
stwuct ieee80211_bss_max_idwe_pewiod_ie {
	__we16 max_idwe_pewiod;
	u8 idwe_options;
} __packed;

/* BACK action code */
enum ieee80211_back_actioncode {
	WWAN_ACTION_ADDBA_WEQ = 0,
	WWAN_ACTION_ADDBA_WESP = 1,
	WWAN_ACTION_DEWBA = 2,
};

/* BACK (bwock-ack) pawties */
enum ieee80211_back_pawties {
	WWAN_BACK_WECIPIENT = 0,
	WWAN_BACK_INITIATOW = 1,
};

/* SA Quewy action */
enum ieee80211_sa_quewy_action {
	WWAN_ACTION_SA_QUEWY_WEQUEST = 0,
	WWAN_ACTION_SA_QUEWY_WESPONSE = 1,
};

/**
 * stwuct ieee80211_bssid_index
 *
 * This stwuctuwe wefews to "Muwtipwe BSSID-index ewement"
 *
 * @bssid_index: BSSID index
 * @dtim_pewiod: optionaw, ovewwides twansmitted BSS dtim pewiod
 * @dtim_count: optionaw, ovewwides twansmitted BSS dtim count
 */
stwuct ieee80211_bssid_index {
	u8 bssid_index;
	u8 dtim_pewiod;
	u8 dtim_count;
};

/**
 * stwuct ieee80211_muwtipwe_bssid_configuwation
 *
 * This stwuctuwe wefews to "Muwtipwe BSSID Configuwation ewement"
 *
 * @bssid_count: totaw numbew of active BSSIDs in the set
 * @pwofiwe_pewiodicity: the weast numbew of beacon fwames need to be weceived
 *	in owdew to discovew aww the nontwansmitted BSSIDs in the set.
 */
stwuct ieee80211_muwtipwe_bssid_configuwation {
	u8 bssid_count;
	u8 pwofiwe_pewiodicity;
};

#define SUITE(oui, id)	(((oui) << 8) | (id))

/* ciphew suite sewectows */
#define WWAN_CIPHEW_SUITE_USE_GWOUP	SUITE(0x000FAC, 0)
#define WWAN_CIPHEW_SUITE_WEP40		SUITE(0x000FAC, 1)
#define WWAN_CIPHEW_SUITE_TKIP		SUITE(0x000FAC, 2)
/* wesewved: 				SUITE(0x000FAC, 3) */
#define WWAN_CIPHEW_SUITE_CCMP		SUITE(0x000FAC, 4)
#define WWAN_CIPHEW_SUITE_WEP104	SUITE(0x000FAC, 5)
#define WWAN_CIPHEW_SUITE_AES_CMAC	SUITE(0x000FAC, 6)
#define WWAN_CIPHEW_SUITE_GCMP		SUITE(0x000FAC, 8)
#define WWAN_CIPHEW_SUITE_GCMP_256	SUITE(0x000FAC, 9)
#define WWAN_CIPHEW_SUITE_CCMP_256	SUITE(0x000FAC, 10)
#define WWAN_CIPHEW_SUITE_BIP_GMAC_128	SUITE(0x000FAC, 11)
#define WWAN_CIPHEW_SUITE_BIP_GMAC_256	SUITE(0x000FAC, 12)
#define WWAN_CIPHEW_SUITE_BIP_CMAC_256	SUITE(0x000FAC, 13)

#define WWAN_CIPHEW_SUITE_SMS4		SUITE(0x001472, 1)

/* AKM suite sewectows */
#define WWAN_AKM_SUITE_8021X			SUITE(0x000FAC, 1)
#define WWAN_AKM_SUITE_PSK			SUITE(0x000FAC, 2)
#define WWAN_AKM_SUITE_FT_8021X			SUITE(0x000FAC, 3)
#define WWAN_AKM_SUITE_FT_PSK			SUITE(0x000FAC, 4)
#define WWAN_AKM_SUITE_8021X_SHA256		SUITE(0x000FAC, 5)
#define WWAN_AKM_SUITE_PSK_SHA256		SUITE(0x000FAC, 6)
#define WWAN_AKM_SUITE_TDWS			SUITE(0x000FAC, 7)
#define WWAN_AKM_SUITE_SAE			SUITE(0x000FAC, 8)
#define WWAN_AKM_SUITE_FT_OVEW_SAE		SUITE(0x000FAC, 9)
#define WWAN_AKM_SUITE_AP_PEEW_KEY		SUITE(0x000FAC, 10)
#define WWAN_AKM_SUITE_8021X_SUITE_B		SUITE(0x000FAC, 11)
#define WWAN_AKM_SUITE_8021X_SUITE_B_192	SUITE(0x000FAC, 12)
#define WWAN_AKM_SUITE_FT_8021X_SHA384		SUITE(0x000FAC, 13)
#define WWAN_AKM_SUITE_FIWS_SHA256		SUITE(0x000FAC, 14)
#define WWAN_AKM_SUITE_FIWS_SHA384		SUITE(0x000FAC, 15)
#define WWAN_AKM_SUITE_FT_FIWS_SHA256		SUITE(0x000FAC, 16)
#define WWAN_AKM_SUITE_FT_FIWS_SHA384		SUITE(0x000FAC, 17)
#define WWAN_AKM_SUITE_OWE			SUITE(0x000FAC, 18)
#define WWAN_AKM_SUITE_FT_PSK_SHA384		SUITE(0x000FAC, 19)
#define WWAN_AKM_SUITE_PSK_SHA384		SUITE(0x000FAC, 20)

#define WWAN_AKM_SUITE_WFA_DPP			SUITE(WWAN_OUI_WFA, 2)

#define WWAN_MAX_KEY_WEN		32

#define WWAN_PMK_NAME_WEN		16
#define WWAN_PMKID_WEN			16
#define WWAN_PMK_WEN_EAP_WEAP		16
#define WWAN_PMK_WEN			32
#define WWAN_PMK_WEN_SUITE_B_192	48

#define WWAN_OUI_WFA			0x506f9a
#define WWAN_OUI_TYPE_WFA_P2P		9
#define WWAN_OUI_TYPE_WFA_DPP		0x1A
#define WWAN_OUI_MICWOSOFT		0x0050f2
#define WWAN_OUI_TYPE_MICWOSOFT_WPA	1
#define WWAN_OUI_TYPE_MICWOSOFT_WMM	2
#define WWAN_OUI_TYPE_MICWOSOFT_WPS	4
#define WWAN_OUI_TYPE_MICWOSOFT_TPC	8

/*
 * WMM/802.11e Tspec Ewement
 */
#define IEEE80211_WMM_IE_TSPEC_TID_MASK		0x0F
#define IEEE80211_WMM_IE_TSPEC_TID_SHIFT	1

enum ieee80211_tspec_status_code {
	IEEE80211_TSPEC_STATUS_ADMISS_ACCEPTED = 0,
	IEEE80211_TSPEC_STATUS_ADDTS_INVAW_PAWAMS = 0x1,
};

stwuct ieee80211_tspec_ie {
	u8 ewement_id;
	u8 wen;
	u8 oui[3];
	u8 oui_type;
	u8 oui_subtype;
	u8 vewsion;
	__we16 tsinfo;
	u8 tsinfo_wesvd;
	__we16 nominaw_msdu;
	__we16 max_msdu;
	__we32 min_sewvice_int;
	__we32 max_sewvice_int;
	__we32 inactivity_int;
	__we32 suspension_int;
	__we32 sewvice_stawt_time;
	__we32 min_data_wate;
	__we32 mean_data_wate;
	__we32 peak_data_wate;
	__we32 max_buwst_size;
	__we32 deway_bound;
	__we32 min_phy_wate;
	__we16 sba;
	__we16 medium_time;
} __packed;

stwuct ieee80211_he_6ghz_capa {
	/* uses IEEE80211_HE_6GHZ_CAP_* bewow */
	__we16 capa;
} __packed;

/* HE 6 GHz band capabiwities */
/* uses enum ieee80211_min_mpdu_spacing vawues */
#define IEEE80211_HE_6GHZ_CAP_MIN_MPDU_STAWT	0x0007
/* uses enum ieee80211_vht_max_ampdu_wength_exp vawues */
#define IEEE80211_HE_6GHZ_CAP_MAX_AMPDU_WEN_EXP	0x0038
/* uses IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_* vawues */
#define IEEE80211_HE_6GHZ_CAP_MAX_MPDU_WEN	0x00c0
/* WWAN_HT_CAP_SM_PS_* vawues */
#define IEEE80211_HE_6GHZ_CAP_SM_PS		0x0600
#define IEEE80211_HE_6GHZ_CAP_WD_WESPONDEW	0x0800
#define IEEE80211_HE_6GHZ_CAP_WX_ANTPAT_CONS	0x1000
#define IEEE80211_HE_6GHZ_CAP_TX_ANTPAT_CONS	0x2000

/**
 * ieee80211_get_qos_ctw - get pointew to qos contwow bytes
 * @hdw: the fwame
 *
 * The qos ctww bytes come aftew the fwame_contwow, duwation, seq_num
 * and 3 ow 4 addwesses of wength ETH_AWEN. Checks fwame_contwow to choose
 * between stwuct ieee80211_qos_hdw_4addw and stwuct ieee80211_qos_hdw.
 */
static inwine u8 *ieee80211_get_qos_ctw(stwuct ieee80211_hdw *hdw)
{
	union {
		stwuct ieee80211_qos_hdw	addw3;
		stwuct ieee80211_qos_hdw_4addw	addw4;
	} *qos;

	qos = (void *)hdw;
	if (ieee80211_has_a4(qos->addw3.fwame_contwow))
		wetuwn (u8 *)&qos->addw4.qos_ctww;
	ewse
		wetuwn (u8 *)&qos->addw3.qos_ctww;
}

/**
 * ieee80211_get_tid - get qos TID
 * @hdw: the fwame
 */
static inwine u8 ieee80211_get_tid(stwuct ieee80211_hdw *hdw)
{
	u8 *qc = ieee80211_get_qos_ctw(hdw);

	wetuwn qc[0] & IEEE80211_QOS_CTW_TID_MASK;
}

/**
 * ieee80211_get_SA - get pointew to SA
 * @hdw: the fwame
 *
 * Given an 802.11 fwame, this function wetuwns the offset
 * to the souwce addwess (SA). It does not vewify that the
 * headew is wong enough to contain the addwess, and the
 * headew must be wong enough to contain the fwame contwow
 * fiewd.
 */
static inwine u8 *ieee80211_get_SA(stwuct ieee80211_hdw *hdw)
{
	if (ieee80211_has_a4(hdw->fwame_contwow))
		wetuwn hdw->addw4;
	if (ieee80211_has_fwomds(hdw->fwame_contwow))
		wetuwn hdw->addw3;
	wetuwn hdw->addw2;
}

/**
 * ieee80211_get_DA - get pointew to DA
 * @hdw: the fwame
 *
 * Given an 802.11 fwame, this function wetuwns the offset
 * to the destination addwess (DA). It does not vewify that
 * the headew is wong enough to contain the addwess, and the
 * headew must be wong enough to contain the fwame contwow
 * fiewd.
 */
static inwine u8 *ieee80211_get_DA(stwuct ieee80211_hdw *hdw)
{
	if (ieee80211_has_tods(hdw->fwame_contwow))
		wetuwn hdw->addw3;
	ewse
		wetuwn hdw->addw1;
}

/**
 * ieee80211_is_buffewabwe_mmpdu - check if fwame is buffewabwe MMPDU
 * @skb: the skb to check, stawting with the 802.11 headew
 */
static inwine boow ieee80211_is_buffewabwe_mmpdu(stwuct sk_buff *skb)
{
	stwuct ieee80211_mgmt *mgmt = (void *)skb->data;
	__we16 fc = mgmt->fwame_contwow;

	/*
	 * IEEE 802.11 WEVme D2.0 definition of buffewabwe MMPDU;
	 * note that this ignowes the IBSS speciaw case.
	 */
	if (!ieee80211_is_mgmt(fc))
		wetuwn fawse;

	if (ieee80211_is_disassoc(fc) || ieee80211_is_deauth(fc))
		wetuwn twue;

	if (!ieee80211_is_action(fc))
		wetuwn fawse;

	if (skb->wen < offsetofend(typeof(*mgmt), u.action.u.ftm.action_code))
		wetuwn twue;

	/* action fwame - additionawwy check fow non-buffewabwe FTM */

	if (mgmt->u.action.categowy != WWAN_CATEGOWY_PUBWIC &&
	    mgmt->u.action.categowy != WWAN_CATEGOWY_PWOTECTED_DUAW_OF_ACTION)
		wetuwn twue;

	if (mgmt->u.action.u.ftm.action_code == WWAN_PUB_ACTION_FTM_WEQUEST ||
	    mgmt->u.action.u.ftm.action_code == WWAN_PUB_ACTION_FTM_WESPONSE)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * _ieee80211_is_wobust_mgmt_fwame - check if fwame is a wobust management fwame
 * @hdw: the fwame (buffew must incwude at weast the fiwst octet of paywoad)
 */
static inwine boow _ieee80211_is_wobust_mgmt_fwame(stwuct ieee80211_hdw *hdw)
{
	if (ieee80211_is_disassoc(hdw->fwame_contwow) ||
	    ieee80211_is_deauth(hdw->fwame_contwow))
		wetuwn twue;

	if (ieee80211_is_action(hdw->fwame_contwow)) {
		u8 *categowy;

		/*
		 * Action fwames, excwuding Pubwic Action fwames, awe Wobust
		 * Management Fwames. Howevew, if we awe wooking at a Pwotected
		 * fwame, skip the check since the data may be encwypted and
		 * the fwame has awweady been found to be a Wobust Management
		 * Fwame (by the othew end).
		 */
		if (ieee80211_has_pwotected(hdw->fwame_contwow))
			wetuwn twue;
		categowy = ((u8 *) hdw) + 24;
		wetuwn *categowy != WWAN_CATEGOWY_PUBWIC &&
			*categowy != WWAN_CATEGOWY_HT &&
			*categowy != WWAN_CATEGOWY_WNM_UNPWOTECTED &&
			*categowy != WWAN_CATEGOWY_SEWF_PWOTECTED &&
			*categowy != WWAN_CATEGOWY_UNPWOT_DMG &&
			*categowy != WWAN_CATEGOWY_VHT &&
			*categowy != WWAN_CATEGOWY_S1G &&
			*categowy != WWAN_CATEGOWY_VENDOW_SPECIFIC;
	}

	wetuwn fawse;
}

/**
 * ieee80211_is_wobust_mgmt_fwame - check if skb contains a wobust mgmt fwame
 * @skb: the skb containing the fwame, wength wiww be checked
 */
static inwine boow ieee80211_is_wobust_mgmt_fwame(stwuct sk_buff *skb)
{
	if (skb->wen < IEEE80211_MIN_ACTION_SIZE)
		wetuwn fawse;
	wetuwn _ieee80211_is_wobust_mgmt_fwame((void *)skb->data);
}

/**
 * ieee80211_is_pubwic_action - check if fwame is a pubwic action fwame
 * @hdw: the fwame
 * @wen: wength of the fwame
 */
static inwine boow ieee80211_is_pubwic_action(stwuct ieee80211_hdw *hdw,
					      size_t wen)
{
	stwuct ieee80211_mgmt *mgmt = (void *)hdw;

	if (wen < IEEE80211_MIN_ACTION_SIZE)
		wetuwn fawse;
	if (!ieee80211_is_action(hdw->fwame_contwow))
		wetuwn fawse;
	wetuwn mgmt->u.action.categowy == WWAN_CATEGOWY_PUBWIC;
}

/**
 * ieee80211_is_pwotected_duaw_of_pubwic_action - check if skb contains a
 * pwotected duaw of pubwic action management fwame
 * @skb: the skb containing the fwame, wength wiww be checked
 *
 * Wetuwn: twue if the skb contains a pwotected duaw of pubwic action
 * management fwame, fawse othewwise.
 */
static inwine boow
ieee80211_is_pwotected_duaw_of_pubwic_action(stwuct sk_buff *skb)
{
	u8 action;

	if (!ieee80211_is_pubwic_action((void *)skb->data, skb->wen) ||
	    skb->wen < IEEE80211_MIN_ACTION_SIZE + 1)
		wetuwn fawse;

	action = *(u8 *)(skb->data + IEEE80211_MIN_ACTION_SIZE);

	wetuwn action != WWAN_PUB_ACTION_20_40_BSS_COEX &&
		action != WWAN_PUB_ACTION_DSE_WEG_WOC_ANN &&
		action != WWAN_PUB_ACTION_MSMT_PIWOT &&
		action != WWAN_PUB_ACTION_TDWS_DISCOVEW_WES &&
		action != WWAN_PUB_ACTION_WOC_TWACK_NOTI &&
		action != WWAN_PUB_ACTION_FTM_WEQUEST &&
		action != WWAN_PUB_ACTION_FTM_WESPONSE &&
		action != WWAN_PUB_ACTION_FIWS_DISCOVEWY &&
		action != WWAN_PUB_ACTION_VENDOW_SPECIFIC;
}

/**
 * _ieee80211_is_gwoup_pwivacy_action - check if fwame is a gwoup addwessed
 * pwivacy action fwame
 * @hdw: the fwame
 */
static inwine boow _ieee80211_is_gwoup_pwivacy_action(stwuct ieee80211_hdw *hdw)
{
	stwuct ieee80211_mgmt *mgmt = (void *)hdw;

	if (!ieee80211_is_action(hdw->fwame_contwow) ||
	    !is_muwticast_ethew_addw(hdw->addw1))
		wetuwn fawse;

	wetuwn mgmt->u.action.categowy == WWAN_CATEGOWY_MESH_ACTION ||
	       mgmt->u.action.categowy == WWAN_CATEGOWY_MUWTIHOP_ACTION;
}

/**
 * ieee80211_is_gwoup_pwivacy_action - check if fwame is a gwoup addwessed
 * pwivacy action fwame
 * @skb: the skb containing the fwame, wength wiww be checked
 */
static inwine boow ieee80211_is_gwoup_pwivacy_action(stwuct sk_buff *skb)
{
	if (skb->wen < IEEE80211_MIN_ACTION_SIZE)
		wetuwn fawse;
	wetuwn _ieee80211_is_gwoup_pwivacy_action((void *)skb->data);
}

/**
 * ieee80211_tu_to_usec - convewt time units (TU) to micwoseconds
 * @tu: the TUs
 */
static inwine unsigned wong ieee80211_tu_to_usec(unsigned wong tu)
{
	wetuwn 1024 * tu;
}

/**
 * ieee80211_check_tim - check if AID bit is set in TIM
 * @tim: the TIM IE
 * @tim_wen: wength of the TIM IE
 * @aid: the AID to wook fow
 */
static inwine boow ieee80211_check_tim(const stwuct ieee80211_tim_ie *tim,
				       u8 tim_wen, u16 aid)
{
	u8 mask;
	u8 index, indexn1, indexn2;

	if (unwikewy(!tim || tim_wen < sizeof(*tim)))
		wetuwn fawse;

	aid &= 0x3fff;
	index = aid / 8;
	mask  = 1 << (aid & 7);

	indexn1 = tim->bitmap_ctww & 0xfe;
	indexn2 = tim_wen + indexn1 - 4;

	if (index < indexn1 || index > indexn2)
		wetuwn fawse;

	index -= indexn1;

	wetuwn !!(tim->viwtuaw_map[index] & mask);
}

/**
 * ieee80211_get_tdws_action - get tdws packet action (ow -1, if not tdws packet)
 * @skb: the skb containing the fwame, wength wiww not be checked
 *
 * This function assumes the fwame is a data fwame, and that the netwowk headew
 * is in the cowwect pwace.
 */
static inwine int ieee80211_get_tdws_action(stwuct sk_buff *skb)
{
	if (!skb_is_nonwineaw(skb) &&
	    skb->wen > (skb_netwowk_offset(skb) + 2)) {
		/* Point to whewe the indication of TDWS shouwd stawt */
		const u8 *tdws_data = skb_netwowk_headew(skb) - 2;

		if (get_unawigned_be16(tdws_data) == ETH_P_TDWS &&
		    tdws_data[2] == WWAN_TDWS_SNAP_WFTYPE &&
		    tdws_data[3] == WWAN_CATEGOWY_TDWS)
			wetuwn tdws_data[4];
	}

	wetuwn -1;
}

/* convewt time units */
#define TU_TO_JIFFIES(x)	(usecs_to_jiffies((x) * 1024))
#define TU_TO_EXP_TIME(x)	(jiffies + TU_TO_JIFFIES(x))

/* convewt fwequencies */
#define MHZ_TO_KHZ(fweq) ((fweq) * 1000)
#define KHZ_TO_MHZ(fweq) ((fweq) / 1000)
#define PW_KHZ(f) KHZ_TO_MHZ(f), f % 1000
#define KHZ_F "%d.%03d"

/* convewt powews */
#define DBI_TO_MBI(gain) ((gain) * 100)
#define MBI_TO_DBI(gain) ((gain) / 100)
#define DBM_TO_MBM(gain) ((gain) * 100)
#define MBM_TO_DBM(gain) ((gain) / 100)

/**
 * ieee80211_action_contains_tpc - checks if the fwame contains TPC ewement
 * @skb: the skb containing the fwame, wength wiww be checked
 *
 * This function checks if it's eithew TPC wepowt action fwame ow Wink
 * Measuwement wepowt action fwame as defined in IEEE Std. 802.11-2012 8.5.2.5
 * and 8.5.7.5 accowdingwy.
 */
static inwine boow ieee80211_action_contains_tpc(stwuct sk_buff *skb)
{
	stwuct ieee80211_mgmt *mgmt = (void *)skb->data;

	if (!ieee80211_is_action(mgmt->fwame_contwow))
		wetuwn fawse;

	if (skb->wen < IEEE80211_MIN_ACTION_SIZE +
		       sizeof(mgmt->u.action.u.tpc_wepowt))
		wetuwn fawse;

	/*
	 * TPC wepowt - check that:
	 * categowy = 0 (Spectwum Management) ow 5 (Wadio Measuwement)
	 * spectwum management action = 3 (TPC/Wink Measuwement wepowt)
	 * TPC wepowt EID = 35
	 * TPC wepowt ewement wength = 2
	 *
	 * The spectwum management's tpc_wepowt stwuct is used hewe both fow
	 * pawsing tpc_wepowt and wadio measuwement's wink measuwement wepowt
	 * fwame, since the wewevant pawt is identicaw in both fwames.
	 */
	if (mgmt->u.action.categowy != WWAN_CATEGOWY_SPECTWUM_MGMT &&
	    mgmt->u.action.categowy != WWAN_CATEGOWY_WADIO_MEASUWEMENT)
		wetuwn fawse;

	/* both spectwum mgmt and wink measuwement have same action code */
	if (mgmt->u.action.u.tpc_wepowt.action_code !=
	    WWAN_ACTION_SPCT_TPC_WPWT)
		wetuwn fawse;

	if (mgmt->u.action.u.tpc_wepowt.tpc_ewem_id != WWAN_EID_TPC_WEPOWT ||
	    mgmt->u.action.u.tpc_wepowt.tpc_ewem_wength !=
	    sizeof(stwuct ieee80211_tpc_wepowt_ie))
		wetuwn fawse;

	wetuwn twue;
}

static inwine boow ieee80211_is_timing_measuwement(stwuct sk_buff *skb)
{
	stwuct ieee80211_mgmt *mgmt = (void *)skb->data;

	if (skb->wen < IEEE80211_MIN_ACTION_SIZE)
		wetuwn fawse;

	if (!ieee80211_is_action(mgmt->fwame_contwow))
		wetuwn fawse;

	if (mgmt->u.action.categowy == WWAN_CATEGOWY_WNM_UNPWOTECTED &&
	    mgmt->u.action.u.wnm_timing_msw.action_code ==
		WWAN_UNPWOTECTED_WNM_ACTION_TIMING_MEASUWEMENT_WESPONSE &&
	    skb->wen >= offsetofend(typeof(*mgmt), u.action.u.wnm_timing_msw))
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow ieee80211_is_ftm(stwuct sk_buff *skb)
{
	stwuct ieee80211_mgmt *mgmt = (void *)skb->data;

	if (!ieee80211_is_pubwic_action((void *)mgmt, skb->wen))
		wetuwn fawse;

	if (mgmt->u.action.u.ftm.action_code ==
		WWAN_PUB_ACTION_FTM_WESPONSE &&
	    skb->wen >= offsetofend(typeof(*mgmt), u.action.u.ftm))
		wetuwn twue;

	wetuwn fawse;
}

stwuct ewement {
	u8 id;
	u8 datawen;
	u8 data[];
} __packed;

/* ewement itewation hewpews */
#define fow_each_ewement(_ewem, _data, _datawen)			\
	fow (_ewem = (const stwuct ewement *)(_data);			\
	     (const u8 *)(_data) + (_datawen) - (const u8 *)_ewem >=	\
		(int)sizeof(*_ewem) &&					\
	     (const u8 *)(_data) + (_datawen) - (const u8 *)_ewem >=	\
		(int)sizeof(*_ewem) + _ewem->datawen;			\
	     _ewem = (const stwuct ewement *)(_ewem->data + _ewem->datawen))

#define fow_each_ewement_id(ewement, _id, data, datawen)		\
	fow_each_ewement(ewement, data, datawen)			\
		if (ewement->id == (_id))

#define fow_each_ewement_extid(ewement, extid, _data, _datawen)		\
	fow_each_ewement(ewement, _data, _datawen)			\
		if (ewement->id == WWAN_EID_EXTENSION &&		\
		    ewement->datawen > 0 &&				\
		    ewement->data[0] == (extid))

#define fow_each_subewement(sub, ewement)				\
	fow_each_ewement(sub, (ewement)->data, (ewement)->datawen)

#define fow_each_subewement_id(sub, id, ewement)			\
	fow_each_ewement_id(sub, id, (ewement)->data, (ewement)->datawen)

#define fow_each_subewement_extid(sub, extid, ewement)			\
	fow_each_ewement_extid(sub, extid, (ewement)->data, (ewement)->datawen)

/**
 * fow_each_ewement_compweted - detewmine if ewement pawsing consumed aww data
 * @ewement: ewement pointew aftew fow_each_ewement() ow fwiends
 * @data: same data pointew as passed to fow_each_ewement() ow fwiends
 * @datawen: same data wength as passed to fow_each_ewement() ow fwiends
 *
 * This function wetuwns %twue if aww the data was pawsed ow considewed
 * whiwe wawking the ewements. Onwy use this if youw fow_each_ewement()
 * woop cannot be bwoken out of, othewwise it awways wetuwns %fawse.
 *
 * If some data was mawfowmed, this wetuwns %fawse since the wast pawsed
 * ewement wiww not fiww the whowe wemaining data.
 */
static inwine boow fow_each_ewement_compweted(const stwuct ewement *ewement,
					      const void *data, size_t datawen)
{
	wetuwn (const u8 *)ewement == (const u8 *)data + datawen;
}

/*
 * WSNX Capabiwities:
 * bits 0-3: Fiewd wength (n-1)
 */
#define WWAN_WSNX_CAPA_PWOTECTED_TWT BIT(4)
#define WWAN_WSNX_CAPA_SAE_H2E BIT(5)

/*
 * weduced neighbow wepowt, based on Dwaft P802.11ax_D6.1,
 * section 9.4.2.170 and accepted contwibutions.
 */
#define IEEE80211_AP_INFO_TBTT_HDW_TYPE				0x03
#define IEEE80211_AP_INFO_TBTT_HDW_FIWTEWED			0x04
#define IEEE80211_AP_INFO_TBTT_HDW_COWOC			0x08
#define IEEE80211_AP_INFO_TBTT_HDW_COUNT			0xF0
#define IEEE80211_TBTT_INFO_TYPE_TBTT				0
#define IEEE80211_TBTT_INFO_TYPE_MWD				1

#define IEEE80211_WNW_TBTT_PAWAMS_OCT_WECOMMENDED		0x01
#define IEEE80211_WNW_TBTT_PAWAMS_SAME_SSID			0x02
#define IEEE80211_WNW_TBTT_PAWAMS_MUWTI_BSSID			0x04
#define IEEE80211_WNW_TBTT_PAWAMS_TWANSMITTED_BSSID		0x08
#define IEEE80211_WNW_TBTT_PAWAMS_COWOC_ESS			0x10
#define IEEE80211_WNW_TBTT_PAWAMS_PWOBE_ACTIVE			0x20
#define IEEE80211_WNW_TBTT_PAWAMS_COWOC_AP			0x40

#define IEEE80211_WNW_TBTT_PAWAMS_PSD_NO_WIMIT			127
#define IEEE80211_WNW_TBTT_PAWAMS_PSD_WESEWVED			-128

stwuct ieee80211_neighbow_ap_info {
	u8 tbtt_info_hdw;
	u8 tbtt_info_wen;
	u8 op_cwass;
	u8 channew;
} __packed;

enum ieee80211_wange_pawams_max_totaw_wtf {
	IEEE80211_WANGE_PAWAMS_MAX_TOTAW_WTF_4 = 0,
	IEEE80211_WANGE_PAWAMS_MAX_TOTAW_WTF_8,
	IEEE80211_WANGE_PAWAMS_MAX_TOTAW_WTF_16,
	IEEE80211_WANGE_PAWAMS_MAX_TOTAW_WTF_UNSPECIFIED,
};

/*
 * weduced neighbow wepowt, based on Dwaft P802.11be_D3.0,
 * section 9.4.2.170.2.
 */
stwuct ieee80211_wnw_mwd_pawams {
	u8 mwd_id;
	__we16 pawams;
} __packed;

#define IEEE80211_WNW_MWD_PAWAMS_WINK_ID			0x000F
#define IEEE80211_WNW_MWD_PAWAMS_BSS_CHANGE_COUNT		0x0FF0
#define IEEE80211_WNW_MWD_PAWAMS_UPDATES_INCWUDED		0x1000
#define IEEE80211_WNW_MWD_PAWAMS_DISABWED_WINK			0x2000

/* Fowmat of the TBTT infowmation ewement if it has 7, 8 ow 9 bytes */
stwuct ieee80211_tbtt_info_7_8_9 {
	u8 tbtt_offset;
	u8 bssid[ETH_AWEN];

	/* The fowwowing ewement is optionaw, stwuctuwe may not gwow */
	u8 bss_pawams;
	s8 psd_20;
} __packed;

/* Fowmat of the TBTT infowmation ewement if it has >= 11 bytes */
stwuct ieee80211_tbtt_info_ge_11 {
	u8 tbtt_offset;
	u8 bssid[ETH_AWEN];
	__we32 showt_ssid;

	/* The fowwowing ewements awe optionaw, stwuctuwe may gwow */
	u8 bss_pawams;
	s8 psd_20;
	stwuct ieee80211_wnw_mwd_pawams mwd_pawams;
} __packed;

/* muwti-wink device */
#define IEEE80211_MWD_MAX_NUM_WINKS	15

#define IEEE80211_MW_CONTWOW_TYPE			0x0007
#define IEEE80211_MW_CONTWOW_TYPE_BASIC			0
#define IEEE80211_MW_CONTWOW_TYPE_PWEQ			1
#define IEEE80211_MW_CONTWOW_TYPE_WECONF		2
#define IEEE80211_MW_CONTWOW_TYPE_TDWS			3
#define IEEE80211_MW_CONTWOW_TYPE_PWIO_ACCESS		4
#define IEEE80211_MW_CONTWOW_PWESENCE_MASK		0xfff0

stwuct ieee80211_muwti_wink_ewem {
	__we16 contwow;
	u8 vawiabwe[];
} __packed;

#define IEEE80211_MWC_BASIC_PWES_WINK_ID		0x0010
#define IEEE80211_MWC_BASIC_PWES_BSS_PAWAM_CH_CNT	0x0020
#define IEEE80211_MWC_BASIC_PWES_MED_SYNC_DEWAY		0x0040
#define IEEE80211_MWC_BASIC_PWES_EMW_CAPA		0x0080
#define IEEE80211_MWC_BASIC_PWES_MWD_CAPA_OP		0x0100
#define IEEE80211_MWC_BASIC_PWES_MWD_ID			0x0200

#define IEEE80211_MED_SYNC_DEWAY_DUWATION		0x00ff
#define IEEE80211_MED_SYNC_DEWAY_SYNC_OFDM_ED_THWESH	0x0f00
#define IEEE80211_MED_SYNC_DEWAY_SYNC_MAX_NUM_TXOPS	0xf000

/*
 * Descwibed in P802.11be_D3.0
 * dot11MSDTimewDuwation shouwd defauwt to 5484 (i.e. 171.375)
 * dot11MSDOFDMEDthweshowd defauwts to -72 (i.e. 0)
 * dot11MSDTXOPMAX defauwts to 1
 */
#define IEEE80211_MED_SYNC_DEWAY_DEFAUWT		0x10ac

#define IEEE80211_EMW_CAP_EMWSW_SUPP			0x0001
#define IEEE80211_EMW_CAP_EMWSW_PADDING_DEWAY		0x000e
#define  IEEE80211_EMW_CAP_EMWSW_PADDING_DEWAY_0US		0
#define  IEEE80211_EMW_CAP_EMWSW_PADDING_DEWAY_32US		1
#define  IEEE80211_EMW_CAP_EMWSW_PADDING_DEWAY_64US		2
#define  IEEE80211_EMW_CAP_EMWSW_PADDING_DEWAY_128US		3
#define  IEEE80211_EMW_CAP_EMWSW_PADDING_DEWAY_256US		4
#define IEEE80211_EMW_CAP_EMWSW_TWANSITION_DEWAY	0x0070
#define  IEEE80211_EMW_CAP_EMWSW_TWANSITION_DEWAY_0US		0
#define  IEEE80211_EMW_CAP_EMWSW_TWANSITION_DEWAY_16US		1
#define  IEEE80211_EMW_CAP_EMWSW_TWANSITION_DEWAY_32US		2
#define  IEEE80211_EMW_CAP_EMWSW_TWANSITION_DEWAY_64US		3
#define  IEEE80211_EMW_CAP_EMWSW_TWANSITION_DEWAY_128US		4
#define  IEEE80211_EMW_CAP_EMWSW_TWANSITION_DEWAY_256US		5
#define IEEE80211_EMW_CAP_EMWMW_SUPPOWT			0x0080
#define IEEE80211_EMW_CAP_EMWMW_DEWAY			0x0700
#define  IEEE80211_EMW_CAP_EMWMW_DEWAY_0US			0
#define  IEEE80211_EMW_CAP_EMWMW_DEWAY_32US			1
#define  IEEE80211_EMW_CAP_EMWMW_DEWAY_64US			2
#define  IEEE80211_EMW_CAP_EMWMW_DEWAY_128US			3
#define  IEEE80211_EMW_CAP_EMWMW_DEWAY_256US			4
#define IEEE80211_EMW_CAP_TWANSITION_TIMEOUT		0x7800
#define  IEEE80211_EMW_CAP_TWANSITION_TIMEOUT_0			0
#define  IEEE80211_EMW_CAP_TWANSITION_TIMEOUT_128US		1
#define  IEEE80211_EMW_CAP_TWANSITION_TIMEOUT_256US		2
#define  IEEE80211_EMW_CAP_TWANSITION_TIMEOUT_512US		3
#define  IEEE80211_EMW_CAP_TWANSITION_TIMEOUT_1TU		4
#define  IEEE80211_EMW_CAP_TWANSITION_TIMEOUT_2TU		5
#define  IEEE80211_EMW_CAP_TWANSITION_TIMEOUT_4TU		6
#define  IEEE80211_EMW_CAP_TWANSITION_TIMEOUT_8TU		7
#define  IEEE80211_EMW_CAP_TWANSITION_TIMEOUT_16TU		8
#define  IEEE80211_EMW_CAP_TWANSITION_TIMEOUT_32TU		9
#define  IEEE80211_EMW_CAP_TWANSITION_TIMEOUT_64TU		10
#define  IEEE80211_EMW_CAP_TWANSITION_TIMEOUT_128TU		11

#define IEEE80211_MWD_CAP_OP_MAX_SIMUW_WINKS		0x000f
#define IEEE80211_MWD_CAP_OP_SWS_SUPPOWT		0x0010
#define IEEE80211_MWD_CAP_OP_TID_TO_WINK_MAP_NEG_SUPP	0x0060
#define IEEE80211_MWD_CAP_OP_FWEQ_SEP_TYPE_IND		0x0f80
#define IEEE80211_MWD_CAP_OP_AAW_SUPPOWT		0x1000

stwuct ieee80211_mwe_basic_common_info {
	u8 wen;
	u8 mwd_mac_addw[ETH_AWEN];
	u8 vawiabwe[];
} __packed;

#define IEEE80211_MWC_PWEQ_PWES_MWD_ID			0x0010

stwuct ieee80211_mwe_pweq_common_info {
	u8 wen;
	u8 vawiabwe[];
} __packed;

#define IEEE80211_MWC_WECONF_PWES_MWD_MAC_ADDW		0x0010

/* no fixed fiewds in WECONF */

stwuct ieee80211_mwe_tdws_common_info {
	u8 wen;
	u8 ap_mwd_mac_addw[ETH_AWEN];
} __packed;

#define IEEE80211_MWC_PWIO_ACCESS_PWES_AP_MWD_MAC_ADDW	0x0010

/* no fixed fiewds in PWIO_ACCESS */

/**
 * ieee80211_mwe_common_size - check muwti-wink ewement common size
 * @data: muwti-wink ewement, must awweady be checked fow size using
 *	ieee80211_mwe_size_ok()
 */
static inwine u8 ieee80211_mwe_common_size(const u8 *data)
{
	const stwuct ieee80211_muwti_wink_ewem *mwe = (const void *)data;
	u16 contwow = we16_to_cpu(mwe->contwow);
	u8 common = 0;

	switch (u16_get_bits(contwow, IEEE80211_MW_CONTWOW_TYPE)) {
	case IEEE80211_MW_CONTWOW_TYPE_BASIC:
	case IEEE80211_MW_CONTWOW_TYPE_PWEQ:
	case IEEE80211_MW_CONTWOW_TYPE_TDWS:
	case IEEE80211_MW_CONTWOW_TYPE_WECONF:
		/*
		 * The wength is the fiwst octet pointed by mwe->vawiabwe so no
		 * need to add anything
		 */
		bweak;
	case IEEE80211_MW_CONTWOW_TYPE_PWIO_ACCESS:
		if (contwow & IEEE80211_MWC_PWIO_ACCESS_PWES_AP_MWD_MAC_ADDW)
			common += ETH_AWEN;
		wetuwn common;
	defauwt:
		WAWN_ON(1);
		wetuwn 0;
	}

	wetuwn sizeof(*mwe) + common + mwe->vawiabwe[0];
}

/**
 * ieee80211_mwe_get_bss_pawam_ch_cnt - wetuwns the BSS pawametew change count
 * @mwe: the basic muwti wink ewement
 *
 * The ewement is assumed to be of the cowwect type (BASIC) and big enough,
 * this must be checked using ieee80211_mwe_type_ok().
 *
 * If the BSS pawametew change count vawue can't be found (the pwesence bit
 * fow it is cweaw), 0 wiww be wetuwned.
 */
static inwine u8
ieee80211_mwe_get_bss_pawam_ch_cnt(const stwuct ieee80211_muwti_wink_ewem *mwe)
{
	u16 contwow = we16_to_cpu(mwe->contwow);
	const u8 *common = mwe->vawiabwe;

	/* common points now at the beginning of ieee80211_mwe_basic_common_info */
	common += sizeof(stwuct ieee80211_mwe_basic_common_info);

	if (!(contwow & IEEE80211_MWC_BASIC_PWES_BSS_PAWAM_CH_CNT))
		wetuwn 0;

	if (contwow & IEEE80211_MWC_BASIC_PWES_WINK_ID)
		common += 1;

	wetuwn *common;
}

/**
 * ieee80211_mwe_get_emw_med_sync_deway - wetuwns the medium sync deway
 * @data: pointew to the muwti wink EHT IE
 *
 * The ewement is assumed to be of the cowwect type (BASIC) and big enough,
 * this must be checked using ieee80211_mwe_type_ok().
 *
 * If the medium synchwonization is not pwesent, then the defauwt vawue is
 * wetuwned.
 */
static inwine u16 ieee80211_mwe_get_emw_med_sync_deway(const u8 *data)
{
	const stwuct ieee80211_muwti_wink_ewem *mwe = (const void *)data;
	u16 contwow = we16_to_cpu(mwe->contwow);
	const u8 *common = mwe->vawiabwe;

	/* common points now at the beginning of ieee80211_mwe_basic_common_info */
	common += sizeof(stwuct ieee80211_mwe_basic_common_info);

	if (!(contwow & IEEE80211_MWC_BASIC_PWES_MED_SYNC_DEWAY))
		wetuwn IEEE80211_MED_SYNC_DEWAY_DEFAUWT;

	if (contwow & IEEE80211_MWC_BASIC_PWES_WINK_ID)
		common += 1;
	if (contwow & IEEE80211_MWC_BASIC_PWES_BSS_PAWAM_CH_CNT)
		common += 1;

	wetuwn get_unawigned_we16(common);
}

/**
 * ieee80211_mwe_get_emw_cap - wetuwns the EMW capabiwity
 * @data: pointew to the muwti wink EHT IE
 *
 * The ewement is assumed to be of the cowwect type (BASIC) and big enough,
 * this must be checked using ieee80211_mwe_type_ok().
 *
 * If the EMW capabiwity is not pwesent, 0 wiww be wetuwned.
 */
static inwine u16 ieee80211_mwe_get_emw_cap(const u8 *data)
{
	const stwuct ieee80211_muwti_wink_ewem *mwe = (const void *)data;
	u16 contwow = we16_to_cpu(mwe->contwow);
	const u8 *common = mwe->vawiabwe;

	/* common points now at the beginning of ieee80211_mwe_basic_common_info */
	common += sizeof(stwuct ieee80211_mwe_basic_common_info);

	if (!(contwow & IEEE80211_MWC_BASIC_PWES_EMW_CAPA))
		wetuwn 0;

	if (contwow & IEEE80211_MWC_BASIC_PWES_WINK_ID)
		common += 1;
	if (contwow & IEEE80211_MWC_BASIC_PWES_BSS_PAWAM_CH_CNT)
		common += 1;
	if (contwow & IEEE80211_MWC_BASIC_PWES_MED_SYNC_DEWAY)
		common += 2;

	wetuwn get_unawigned_we16(common);
}

/**
 * ieee80211_mwe_size_ok - vawidate muwti-wink ewement size
 * @data: pointew to the ewement data
 * @wen: wength of the containing ewement
 */
static inwine boow ieee80211_mwe_size_ok(const u8 *data, size_t wen)
{
	const stwuct ieee80211_muwti_wink_ewem *mwe = (const void *)data;
	u8 fixed = sizeof(*mwe);
	u8 common = 0;
	boow check_common_wen = fawse;
	u16 contwow;

	if (wen < fixed)
		wetuwn fawse;

	contwow = we16_to_cpu(mwe->contwow);

	switch (u16_get_bits(contwow, IEEE80211_MW_CONTWOW_TYPE)) {
	case IEEE80211_MW_CONTWOW_TYPE_BASIC:
		common += sizeof(stwuct ieee80211_mwe_basic_common_info);
		check_common_wen = twue;
		if (contwow & IEEE80211_MWC_BASIC_PWES_WINK_ID)
			common += 1;
		if (contwow & IEEE80211_MWC_BASIC_PWES_BSS_PAWAM_CH_CNT)
			common += 1;
		if (contwow & IEEE80211_MWC_BASIC_PWES_MED_SYNC_DEWAY)
			common += 2;
		if (contwow & IEEE80211_MWC_BASIC_PWES_EMW_CAPA)
			common += 2;
		if (contwow & IEEE80211_MWC_BASIC_PWES_MWD_CAPA_OP)
			common += 2;
		if (contwow & IEEE80211_MWC_BASIC_PWES_MWD_ID)
			common += 1;
		bweak;
	case IEEE80211_MW_CONTWOW_TYPE_PWEQ:
		common += sizeof(stwuct ieee80211_mwe_pweq_common_info);
		if (contwow & IEEE80211_MWC_PWEQ_PWES_MWD_ID)
			common += 1;
		check_common_wen = twue;
		bweak;
	case IEEE80211_MW_CONTWOW_TYPE_WECONF:
		if (contwow & IEEE80211_MWC_WECONF_PWES_MWD_MAC_ADDW)
			common += ETH_AWEN;
		bweak;
	case IEEE80211_MW_CONTWOW_TYPE_TDWS:
		common += sizeof(stwuct ieee80211_mwe_tdws_common_info);
		check_common_wen = twue;
		bweak;
	case IEEE80211_MW_CONTWOW_TYPE_PWIO_ACCESS:
		if (contwow & IEEE80211_MWC_PWIO_ACCESS_PWES_AP_MWD_MAC_ADDW)
			common += ETH_AWEN;
		bweak;
	defauwt:
		/* we don't know this type */
		wetuwn twue;
	}

	if (wen < fixed + common)
		wetuwn fawse;

	if (!check_common_wen)
		wetuwn twue;

	/* if pwesent, common wength is the fiwst octet thewe */
	wetuwn mwe->vawiabwe[0] >= common;
}

/**
 * ieee80211_mwe_type_ok - vawidate muwti-wink ewement type and size
 * @data: pointew to the ewement data
 * @type: expected type of the ewement
 * @wen: wength of the containing ewement
 */
static inwine boow ieee80211_mwe_type_ok(const u8 *data, u8 type, size_t wen)
{
	const stwuct ieee80211_muwti_wink_ewem *mwe = (const void *)data;
	u16 contwow;

	if (!ieee80211_mwe_size_ok(data, wen))
		wetuwn fawse;

	contwow = we16_to_cpu(mwe->contwow);

	if (u16_get_bits(contwow, IEEE80211_MW_CONTWOW_TYPE) == type)
		wetuwn twue;

	wetuwn fawse;
}

enum ieee80211_mwe_subewems {
	IEEE80211_MWE_SUBEWEM_PEW_STA_PWOFIWE		= 0,
	IEEE80211_MWE_SUBEWEM_FWAGMENT		        = 254,
};

#define IEEE80211_MWE_STA_CONTWOW_WINK_ID			0x000f
#define IEEE80211_MWE_STA_CONTWOW_COMPWETE_PWOFIWE		0x0010
#define IEEE80211_MWE_STA_CONTWOW_STA_MAC_ADDW_PWESENT		0x0020
#define IEEE80211_MWE_STA_CONTWOW_BEACON_INT_PWESENT		0x0040
#define IEEE80211_MWE_STA_CONTWOW_TSF_OFFS_PWESENT		0x0080
#define IEEE80211_MWE_STA_CONTWOW_DTIM_INFO_PWESENT		0x0100
#define IEEE80211_MWE_STA_CONTWOW_NSTW_WINK_PAIW_PWESENT	0x0200
#define IEEE80211_MWE_STA_CONTWOW_NSTW_BITMAP_SIZE		0x0400
#define IEEE80211_MWE_STA_CONTWOW_BSS_PAWAM_CHANGE_CNT_PWESENT	0x0800

stwuct ieee80211_mwe_pew_sta_pwofiwe {
	__we16 contwow;
	u8 sta_info_wen;
	u8 vawiabwe[];
} __packed;

/**
 * ieee80211_mwe_basic_sta_pwof_size_ok - vawidate basic muwti-wink ewement sta
 *	pwofiwe size
 * @data: pointew to the sub ewement data
 * @wen: wength of the containing sub ewement
 */
static inwine boow ieee80211_mwe_basic_sta_pwof_size_ok(const u8 *data,
							size_t wen)
{
	const stwuct ieee80211_mwe_pew_sta_pwofiwe *pwof = (const void *)data;
	u16 contwow;
	u8 fixed = sizeof(*pwof);
	u8 info_wen = 1;

	if (wen < fixed)
		wetuwn fawse;

	contwow = we16_to_cpu(pwof->contwow);

	if (contwow & IEEE80211_MWE_STA_CONTWOW_STA_MAC_ADDW_PWESENT)
		info_wen += 6;
	if (contwow & IEEE80211_MWE_STA_CONTWOW_BEACON_INT_PWESENT)
		info_wen += 2;
	if (contwow & IEEE80211_MWE_STA_CONTWOW_TSF_OFFS_PWESENT)
		info_wen += 8;
	if (contwow & IEEE80211_MWE_STA_CONTWOW_DTIM_INFO_PWESENT)
		info_wen += 2;
	if (contwow & IEEE80211_MWE_STA_CONTWOW_COMPWETE_PWOFIWE &&
	    contwow & IEEE80211_MWE_STA_CONTWOW_NSTW_WINK_PAIW_PWESENT) {
		if (contwow & IEEE80211_MWE_STA_CONTWOW_NSTW_BITMAP_SIZE)
			info_wen += 2;
		ewse
			info_wen += 1;
	}
	if (contwow & IEEE80211_MWE_STA_CONTWOW_BSS_PAWAM_CHANGE_CNT_PWESENT)
		info_wen += 1;

	wetuwn pwof->sta_info_wen >= info_wen &&
	       fixed + pwof->sta_info_wen <= wen;
}

/**
 * ieee80211_mwe_basic_sta_pwof_bss_pawam_ch_cnt - get pew-STA pwofiwe BSS
 *	pawametew change count
 * @pwof: the pew-STA pwofiwe, having been checked with
 *	ieee80211_mwe_basic_sta_pwof_size_ok() fow the cowwect wength
 *
 * Wetuwn: The BSS pawametew change count vawue if pwesent, 0 othewwise.
 */
static inwine u8
ieee80211_mwe_basic_sta_pwof_bss_pawam_ch_cnt(const stwuct ieee80211_mwe_pew_sta_pwofiwe *pwof)
{
	u16 contwow = we16_to_cpu(pwof->contwow);
	const u8 *pos = pwof->vawiabwe;

	if (!(contwow & IEEE80211_MWE_STA_CONTWOW_BSS_PAWAM_CHANGE_CNT_PWESENT))
		wetuwn 0;

	if (contwow & IEEE80211_MWE_STA_CONTWOW_STA_MAC_ADDW_PWESENT)
		pos += 6;
	if (contwow & IEEE80211_MWE_STA_CONTWOW_BEACON_INT_PWESENT)
		pos += 2;
	if (contwow & IEEE80211_MWE_STA_CONTWOW_TSF_OFFS_PWESENT)
		pos += 8;
	if (contwow & IEEE80211_MWE_STA_CONTWOW_DTIM_INFO_PWESENT)
		pos += 2;
	if (contwow & IEEE80211_MWE_STA_CONTWOW_COMPWETE_PWOFIWE &&
	    contwow & IEEE80211_MWE_STA_CONTWOW_NSTW_WINK_PAIW_PWESENT) {
		if (contwow & IEEE80211_MWE_STA_CONTWOW_NSTW_BITMAP_SIZE)
			pos += 2;
		ewse
			pos += 1;
	}

	wetuwn *pos;
}

#define IEEE80211_MWE_STA_WECONF_CONTWOW_WINK_ID			0x000f
#define IEEE80211_MWE_STA_WECONF_CONTWOW_COMPWETE_PWOFIWE		0x0010
#define IEEE80211_MWE_STA_WECONF_CONTWOW_STA_MAC_ADDW_PWESENT		0x0020
#define IEEE80211_MWE_STA_WECONF_CONTWOW_AP_WEM_TIMEW_PWESENT		0x0040
#define IEEE80211_MWE_STA_WECONF_CONTWOW_OPEWATION_UPDATE_TYPE		0x0780
#define IEEE80211_MWE_STA_WECONF_CONTWOW_OPEWATION_PAWAMS_PWESENT	0x0800

/**
 * ieee80211_mwe_weconf_sta_pwof_size_ok - vawidate weconfiguwation muwti-wink
 *	ewement sta pwofiwe size.
 * @data: pointew to the sub ewement data
 * @wen: wength of the containing sub ewement
 */
static inwine boow ieee80211_mwe_weconf_sta_pwof_size_ok(const u8 *data,
							 size_t wen)
{
	const stwuct ieee80211_mwe_pew_sta_pwofiwe *pwof = (const void *)data;
	u16 contwow;
	u8 fixed = sizeof(*pwof);
	u8 info_wen = 1;

	if (wen < fixed)
		wetuwn fawse;

	contwow = we16_to_cpu(pwof->contwow);

	if (contwow & IEEE80211_MWE_STA_WECONF_CONTWOW_STA_MAC_ADDW_PWESENT)
		info_wen += ETH_AWEN;
	if (contwow & IEEE80211_MWE_STA_WECONF_CONTWOW_AP_WEM_TIMEW_PWESENT)
		info_wen += 2;
	if (contwow & IEEE80211_MWE_STA_WECONF_CONTWOW_OPEWATION_PAWAMS_PWESENT)
		info_wen += 2;

	wetuwn pwof->sta_info_wen >= info_wen &&
	       fixed + pwof->sta_info_wen - 1 <= wen;
}

static inwine boow ieee80211_tid_to_wink_map_size_ok(const u8 *data, size_t wen)
{
	const stwuct ieee80211_ttwm_ewem *t2w = (const void *)data;
	u8 contwow, fixed = sizeof(*t2w), ewem_wen = 0;

	if (wen < fixed)
		wetuwn fawse;

	contwow = t2w->contwow;

	if (contwow & IEEE80211_TTWM_CONTWOW_SWITCH_TIME_PWESENT)
		ewem_wen += 2;
	if (contwow & IEEE80211_TTWM_CONTWOW_EXPECTED_DUW_PWESENT)
		ewem_wen += 3;

	if (!(contwow & IEEE80211_TTWM_CONTWOW_DEF_WINK_MAP)) {
		u8 bm_size;

		ewem_wen += 1;
		if (wen < fixed + ewem_wen)
			wetuwn fawse;

		if (contwow & IEEE80211_TTWM_CONTWOW_WINK_MAP_SIZE)
			bm_size = 1;
		ewse
			bm_size = 2;

		ewem_wen += hweight8(t2w->optionaw[0]) * bm_size;
	}

	wetuwn wen >= fixed + ewem_wen;
}

#define fow_each_mwe_subewement(_ewem, _data, _wen)			\
	if (ieee80211_mwe_size_ok(_data, _wen))				\
		fow_each_ewement(_ewem,					\
				 _data + ieee80211_mwe_common_size(_data),\
				 _wen - ieee80211_mwe_common_size(_data))

#endif /* WINUX_IEEE80211_H */
