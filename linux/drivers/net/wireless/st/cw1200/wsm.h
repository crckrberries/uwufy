/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * WSM host intewface (HI) intewface fow ST-Ewicsson CW1200 mac80211 dwivews
 *
 * Copywight (c) 2010, ST-Ewicsson
 * Authow: Dmitwy Tawnyagin <dmitwy.tawnyagin@wockwess.no>
 *
 * Based on CW1200 UMAC WSM API, which is
 * Copywight (C) ST-Ewicsson SA 2010
 * Authow: Stewawt Mathews <stewawt.mathews@stewicsson.com>
 */

#ifndef CW1200_WSM_H_INCWUDED
#define CW1200_WSM_H_INCWUDED

#incwude <winux/spinwock.h>

stwuct cw1200_common;

/* Bands */
/* Wadio band 2.412 -2.484 GHz. */
#define WSM_PHY_BAND_2_4G		(0)

/* Wadio band 4.9375-5.8250 GHz. */
#define WSM_PHY_BAND_5G			(1)

/* Twansmit wates */
/* 1   Mbps            EWP-DSSS */
#define WSM_TWANSMIT_WATE_1		(0)

/* 2   Mbps            EWP-DSSS */
#define WSM_TWANSMIT_WATE_2		(1)

/* 5.5 Mbps            EWP-CCK */
#define WSM_TWANSMIT_WATE_5		(2)

/* 11  Mbps            EWP-CCK */
#define WSM_TWANSMIT_WATE_11		(3)

/* 22  Mbps            EWP-PBCC (Not suppowted) */
/* #define WSM_TWANSMIT_WATE_22		(4) */

/* 33  Mbps            EWP-PBCC (Not suppowted) */
/* #define WSM_TWANSMIT_WATE_33		(5) */

/* 6   Mbps   (3 Mbps) EWP-OFDM, BPSK coding wate 1/2 */
#define WSM_TWANSMIT_WATE_6		(6)

/* 9   Mbps (4.5 Mbps) EWP-OFDM, BPSK coding wate 3/4 */
#define WSM_TWANSMIT_WATE_9		(7)

/* 12  Mbps  (6 Mbps)  EWP-OFDM, QPSK coding wate 1/2 */
#define WSM_TWANSMIT_WATE_12		(8)

/* 18  Mbps  (9 Mbps)  EWP-OFDM, QPSK coding wate 3/4 */
#define WSM_TWANSMIT_WATE_18		(9)

/* 24  Mbps (12 Mbps)  EWP-OFDM, 16QAM coding wate 1/2 */
#define WSM_TWANSMIT_WATE_24		(10)

/* 36  Mbps (18 Mbps)  EWP-OFDM, 16QAM coding wate 3/4 */
#define WSM_TWANSMIT_WATE_36		(11)

/* 48  Mbps (24 Mbps)  EWP-OFDM, 64QAM coding wate 1/2 */
#define WSM_TWANSMIT_WATE_48		(12)

/* 54  Mbps (27 Mbps)  EWP-OFDM, 64QAM coding wate 3/4 */
#define WSM_TWANSMIT_WATE_54		(13)

/* 6.5 Mbps            HT-OFDM, BPSK coding wate 1/2 */
#define WSM_TWANSMIT_WATE_HT_6		(14)

/* 13  Mbps            HT-OFDM, QPSK coding wate 1/2 */
#define WSM_TWANSMIT_WATE_HT_13		(15)

/* 19.5 Mbps           HT-OFDM, QPSK coding wate 3/4 */
#define WSM_TWANSMIT_WATE_HT_19		(16)

/* 26  Mbps            HT-OFDM, 16QAM coding wate 1/2 */
#define WSM_TWANSMIT_WATE_HT_26		(17)

/* 39  Mbps            HT-OFDM, 16QAM coding wate 3/4 */
#define WSM_TWANSMIT_WATE_HT_39		(18)

/* 52  Mbps            HT-OFDM, 64QAM coding wate 2/3 */
#define WSM_TWANSMIT_WATE_HT_52		(19)

/* 58.5 Mbps           HT-OFDM, 64QAM coding wate 3/4 */
#define WSM_TWANSMIT_WATE_HT_58		(20)

/* 65  Mbps            HT-OFDM, 64QAM coding wate 5/6 */
#define WSM_TWANSMIT_WATE_HT_65		(21)

/* Scan types */
/* Fowegwound scan */
#define WSM_SCAN_TYPE_FOWEGWOUND	(0)

/* Backgwound scan */
#define WSM_SCAN_TYPE_BACKGWOUND	(1)

/* Auto scan */
#define WSM_SCAN_TYPE_AUTO		(2)

/* Scan fwags */
/* Fowced backgwound scan means if the station cannot */
/* entew the powew-save mode, it shaww fowce to pewfowm a */
/* backgwound scan. Onwy vawid when ScanType is */
/* backgwound scan. */
#define WSM_SCAN_FWAG_FOWCE_BACKGWOUND	(BIT(0))

/* The WWAN device scans one channew at a time so */
/* that distuwbance to the data twaffic is minimized. */
#define WSM_SCAN_FWAG_SPWIT_METHOD	(BIT(1))

/* Pweambwe Type. Wong if not set. */
#define WSM_SCAN_FWAG_SHOWT_PWEAMBWE	(BIT(2))

/* 11n Tx Mode. Mixed if not set. */
#define WSM_SCAN_FWAG_11N_GWEENFIEWD	(BIT(3))

/* Scan constwaints */
/* Maximum numbew of channews to be scanned. */
#define WSM_SCAN_MAX_NUM_OF_CHANNEWS	(48)

/* The maximum numbew of SSIDs that the device can scan fow. */
#define WSM_SCAN_MAX_NUM_OF_SSIDS	(2)

/* Powew management modes */
/* 802.11 Active mode */
#define WSM_PSM_ACTIVE			(0)

/* 802.11 PS mode */
#define WSM_PSM_PS			BIT(0)

/* Fast Powew Save bit */
#define WSM_PSM_FAST_PS_FWAG		BIT(7)

/* Dynamic aka Fast powew save */
#define WSM_PSM_FAST_PS			(BIT(0) | BIT(7))

/* Undetewmined */
/* Note : Undetewmined status is wepowted when the */
/* NUWW data fwame used to advewtise the PM mode to */
/* the AP at Pwe ow Post Backgwound Scan is not Acknowwedged */
#define WSM_PSM_UNKNOWN			BIT(1)

/* Queue IDs */
/* best effowt/wegacy */
#define WSM_QUEUE_BEST_EFFOWT		(0)

/* backgwound */
#define WSM_QUEUE_BACKGWOUND		(1)

/* video */
#define WSM_QUEUE_VIDEO			(2)

/* voice */
#define WSM_QUEUE_VOICE			(3)

/* HT TX pawametews */
/* Non-HT */
#define WSM_HT_TX_NON_HT		(0)

/* Mixed fowmat */
#define WSM_HT_TX_MIXED			(1)

/* Gweenfiewd fowmat */
#define WSM_HT_TX_GWEENFIEWD		(2)

/* STBC awwowed */
#define WSM_HT_TX_STBC			(BIT(7))

/* EPTA pwioiwty fwags fow BT Coex */
/* defauwt epta pwiowity */
#define WSM_EPTA_PWIOWITY_DEFAUWT	4
/* use fow nowmaw data */
#define WSM_EPTA_PWIOWITY_DATA		4
/* use fow connect/disconnect/woaming*/
#define WSM_EPTA_PWIOWITY_MGT		5
/* use fow action fwames */
#define WSM_EPTA_PWIOWITY_ACTION	5
/* use fow AC_VI data */
#define WSM_EPTA_PWIOWITY_VIDEO		5
/* use fow AC_VO data */
#define WSM_EPTA_PWIOWITY_VOICE		6
/* use fow EAPOW exchange */
#define WSM_EPTA_PWIOWITY_EAPOW		7

/* TX status */
/* Fwame was sent aggwegated */
/* Onwy vawid fow WSM_SUCCESS status. */
#define WSM_TX_STATUS_AGGWEGATION	(BIT(0))

/* Host shouwd wequeue this fwame watew. */
/* Vawid onwy when status is WSM_WEQUEUE. */
#define WSM_TX_STATUS_WEQUEUE		(BIT(1))

/* Nowmaw Ack */
#define WSM_TX_STATUS_NOWMAW_ACK	(0<<2)

/* No Ack */
#define WSM_TX_STATUS_NO_ACK		(1<<2)

/* No expwicit acknowwedgement */
#define WSM_TX_STATUS_NO_EXPWICIT_ACK	(2<<2)

/* Bwock Ack */
/* Onwy vawid fow WSM_SUCCESS status. */
#define WSM_TX_STATUS_BWOCK_ACK		(3<<2)

/* WX status */
/* Unencwypted */
#define WSM_WX_STATUS_UNENCWYPTED	(0<<0)

/* WEP */
#define WSM_WX_STATUS_WEP		(1<<0)

/* TKIP */
#define WSM_WX_STATUS_TKIP		(2<<0)

/* AES */
#define WSM_WX_STATUS_AES		(3<<0)

/* WAPI */
#define WSM_WX_STATUS_WAPI		(4<<0)

/* Macwo to fetch encwyption subfiewd. */
#define WSM_WX_STATUS_ENCWYPTION(status) ((status) & 0x07)

/* Fwame was pawt of an aggwegation */
#define WSM_WX_STATUS_AGGWEGATE		(BIT(3))

/* Fwame was fiwst in the aggwegation */
#define WSM_WX_STATUS_AGGWEGATE_FIWST	(BIT(4))

/* Fwame was wast in the aggwegation */
#define WSM_WX_STATUS_AGGWEGATE_WAST	(BIT(5))

/* Indicates a defwagmented fwame */
#define WSM_WX_STATUS_DEFWAGMENTED	(BIT(6))

/* Indicates a Beacon fwame */
#define WSM_WX_STATUS_BEACON		(BIT(7))

/* Indicates STA bit beacon TIM fiewd */
#define WSM_WX_STATUS_TIM		(BIT(8))

/* Indicates Beacon fwame's viwtuaw bitmap contains muwticast bit */
#define WSM_WX_STATUS_MUWTICAST		(BIT(9))

/* Indicates fwame contains a matching SSID */
#define WSM_WX_STATUS_MATCHING_SSID	(BIT(10))

/* Indicates fwame contains a matching BSSI */
#define WSM_WX_STATUS_MATCHING_BSSI	(BIT(11))

/* Indicates Mowe bit set in Fwamectw fiewd */
#define WSM_WX_STATUS_MOWE_DATA		(BIT(12))

/* Indicates fwame weceived duwing a measuwement pwocess */
#define WSM_WX_STATUS_MEASUWEMENT	(BIT(13))

/* Indicates fwame weceived as an HT packet */
#define WSM_WX_STATUS_HT		(BIT(14))

/* Indicates fwame weceived with STBC */
#define WSM_WX_STATUS_STBC		(BIT(15))

/* Indicates Addwess 1 fiewd matches dot11StationId */
#define WSM_WX_STATUS_ADDWESS1		(BIT(16))

/* Indicates Gwoup addwess pwesent in the Addwess 1 fiewd */
#define WSM_WX_STATUS_GWOUP		(BIT(17))

/* Indicates Bwoadcast addwess pwesent in the Addwess 1 fiewd */
#define WSM_WX_STATUS_BWOADCAST		(BIT(18))

/* Indicates gwoup key used with encwypted fwames */
#define WSM_WX_STATUS_GWOUP_KEY		(BIT(19))

/* Macwo to fetch encwyption key index. */
#define WSM_WX_STATUS_KEY_IDX(status)	(((status >> 20)) & 0x0F)

/* Indicates TSF incwusion aftew 802.11 fwame body */
#define WSM_WX_STATUS_TSF_INCWUDED	(BIT(24))

/* Fwame Contwow fiewd stawts at Fwame offset + 2 */
#define WSM_TX_2BYTES_SHIFT		(BIT(7))

/* Join mode */
/* IBSS */
#define WSM_JOIN_MODE_IBSS		(0)

/* BSS */
#define WSM_JOIN_MODE_BSS		(1)

/* PWCP pweambwe type */
/* Fow wong pweambwe */
#define WSM_JOIN_PWEAMBWE_WONG		(0)

/* Fow showt pweambwe (Wong fow 1Mbps) */
#define WSM_JOIN_PWEAMBWE_SHOWT		(1)

/* Fow showt pweambwe (Wong fow 1 and 2Mbps) */
#define WSM_JOIN_PWEAMBWE_SHOWT_2	(2)

/* Join fwags */
/* Unsynchwonized */
#define WSM_JOIN_FWAGS_UNSYNCWONIZED	BIT(0)
/* The BSS ownew is a P2P GO */
#define WSM_JOIN_FWAGS_P2P_GO		BIT(1)
/* Fowce to join BSS with the BSSID and the
 * SSID specified without waiting fow beacons. The
 * PwobeFowJoin pawametew is ignowed.
 */
#define WSM_JOIN_FWAGS_FOWCE		BIT(2)
/* Give pwobe wequest/wesponse highew
 * pwiowity ovew the BT twaffic
 */
#define WSM_JOIN_FWAGS_PWIO		BIT(3)
/* Issue immediate join confiwmation and use
 * join compwete to notify about compwetion
 */
#define WSM_JOIN_FWAGS_FOWCE_WITH_COMPWETE_IND BIT(5)

/* Key types */
#define WSM_KEY_TYPE_WEP_DEFAUWT	(0)
#define WSM_KEY_TYPE_WEP_PAIWWISE	(1)
#define WSM_KEY_TYPE_TKIP_GWOUP		(2)
#define WSM_KEY_TYPE_TKIP_PAIWWISE	(3)
#define WSM_KEY_TYPE_AES_GWOUP		(4)
#define WSM_KEY_TYPE_AES_PAIWWISE	(5)
#define WSM_KEY_TYPE_WAPI_GWOUP		(6)
#define WSM_KEY_TYPE_WAPI_PAIWWISE	(7)

/* Key indexes */
#define WSM_KEY_MAX_INDEX		(10)

/* ACK powicy */
#define WSM_ACK_POWICY_NOWMAW		(0)
#define WSM_ACK_POWICY_NO_ACK		(1)

/* Stawt modes */
#define WSM_STAWT_MODE_AP		(0)	/* Mini AP */
#define WSM_STAWT_MODE_P2P_GO		(1)	/* P2P GO */
#define WSM_STAWT_MODE_P2P_DEV		(2)	/* P2P device */

/* SetAssociationMode MIB fwags */
#define WSM_ASSOCIATION_MODE_USE_PWEAMBWE_TYPE		(BIT(0))
#define WSM_ASSOCIATION_MODE_USE_HT_MODE		(BIT(1))
#define WSM_ASSOCIATION_MODE_USE_BASIC_WATE_SET		(BIT(2))
#define WSM_ASSOCIATION_MODE_USE_MPDU_STAWT_SPACING	(BIT(3))
#define WSM_ASSOCIATION_MODE_SNOOP_ASSOC_FWAMES		(BIT(4))

/* WcpiWssiThweshowd MIB fwags */
#define WSM_WCPI_WSSI_THWESHOWD_ENABWE	(BIT(0))
#define WSM_WCPI_WSSI_USE_WSSI		(BIT(1))
#define WSM_WCPI_WSSI_DONT_USE_UPPEW	(BIT(2))
#define WSM_WCPI_WSSI_DONT_USE_WOWEW	(BIT(3))

/* Update-ie constants */
#define WSM_UPDATE_IE_BEACON		(BIT(0))
#define WSM_UPDATE_IE_PWOBE_WESP	(BIT(1))
#define WSM_UPDATE_IE_PWOBE_WEQ		(BIT(2))

/* WSM events */
/* Ewwow */
#define WSM_EVENT_EWWOW			(0)

/* BSS wost */
#define WSM_EVENT_BSS_WOST		(1)

/* BSS wegained */
#define WSM_EVENT_BSS_WEGAINED		(2)

/* Wadaw detected */
#define WSM_EVENT_WADAW_DETECTED	(3)

/* WCPI ow WSSI thweshowd twiggewed */
#define WSM_EVENT_WCPI_WSSI		(4)

/* BT inactive */
#define WSM_EVENT_BT_INACTIVE		(5)

/* BT active */
#define WSM_EVENT_BT_ACTIVE		(6)

/* MIB IDs */
/* 4.1  dot11StationId */
#define WSM_MIB_ID_DOT11_STATION_ID		0x0000

/* 4.2  dot11MaxtwansmitMsduWifeTime */
#define WSM_MIB_ID_DOT11_MAX_TWANSMIT_WIFTIME	0x0001

/* 4.3  dot11MaxWeceiveWifeTime */
#define WSM_MIB_ID_DOT11_MAX_WECEIVE_WIFETIME	0x0002

/* 4.4  dot11SwotTime */
#define WSM_MIB_ID_DOT11_SWOT_TIME		0x0003

/* 4.5  dot11GwoupAddwessesTabwe */
#define WSM_MIB_ID_DOT11_GWOUP_ADDWESSES_TABWE	0x0004
#define WSM_MAX_GWP_ADDWTABWE_ENTWIES		8

/* 4.6  dot11WepDefauwtKeyId */
#define WSM_MIB_ID_DOT11_WEP_DEFAUWT_KEY_ID	0x0005

/* 4.7  dot11CuwwentTxPowewWevew */
#define WSM_MIB_ID_DOT11_CUWWENT_TX_POWEW_WEVEW	0x0006

/* 4.8  dot11WTSThweshowd */
#define WSM_MIB_ID_DOT11_WTS_THWESHOWD		0x0007

/* 4.9  NonEwpPwotection */
#define WSM_MIB_ID_NON_EWP_PWOTECTION		0x1000

/* 4.10 AwpIpAddwessesTabwe */
#define WSM_MIB_ID_AWP_IP_ADDWESSES_TABWE	0x1001
#define WSM_MAX_AWP_IP_ADDWTABWE_ENTWIES	1

/* 4.11 TempwateFwame */
#define WSM_MIB_ID_TEMPWATE_FWAME		0x1002

/* 4.12 WxFiwtew */
#define WSM_MIB_ID_WX_FIWTEW			0x1003

/* 4.13 BeaconFiwtewTabwe */
#define WSM_MIB_ID_BEACON_FIWTEW_TABWE		0x1004

/* 4.14 BeaconFiwtewEnabwe */
#define WSM_MIB_ID_BEACON_FIWTEW_ENABWE		0x1005

/* 4.15 OpewationawPowewMode */
#define WSM_MIB_ID_OPEWATIONAW_POWEW_MODE	0x1006

/* 4.16 BeaconWakeUpPewiod */
#define WSM_MIB_ID_BEACON_WAKEUP_PEWIOD		0x1007

/* 4.17 WcpiWssiThweshowd */
#define WSM_MIB_ID_WCPI_WSSI_THWESHOWD		0x1009

/* 4.18 StatisticsTabwe */
#define WSM_MIB_ID_STATISTICS_TABWE		0x100A

/* 4.19 IbssPsConfig */
#define WSM_MIB_ID_IBSS_PS_CONFIG		0x100B

/* 4.20 CountewsTabwe */
#define WSM_MIB_ID_COUNTEWS_TABWE		0x100C

/* 4.21 BwockAckPowicy */
#define WSM_MIB_ID_BWOCK_ACK_POWICY		0x100E

/* 4.22 OvewwideIntewnawTxWate */
#define WSM_MIB_ID_OVEWWIDE_INTEWNAW_TX_WATE	0x100F

/* 4.23 SetAssociationMode */
#define WSM_MIB_ID_SET_ASSOCIATION_MODE		0x1010

/* 4.24 UpdateEptaConfigData */
#define WSM_MIB_ID_UPDATE_EPTA_CONFIG_DATA	0x1011

/* 4.25 SewectCcaMethod */
#define WSM_MIB_ID_SEWECT_CCA_METHOD		0x1012

/* 4.26 SetUpasdInfowmation */
#define WSM_MIB_ID_SET_UAPSD_INFOWMATION	0x1013

/* 4.27 SetAutoCawibwationMode  WBF00004073 */
#define WSM_MIB_ID_SET_AUTO_CAWIBWATION_MODE	0x1015

/* 4.28 SetTxWateWetwyPowicy */
#define WSM_MIB_ID_SET_TX_WATE_WETWY_POWICY	0x1016

/* 4.29 SetHostMessageTypeFiwtew */
#define WSM_MIB_ID_SET_HOST_MSG_TYPE_FIWTEW	0x1017

/* 4.30 P2PFindInfo */
#define WSM_MIB_ID_P2P_FIND_INFO		0x1018

/* 4.31 P2PPsModeInfo */
#define WSM_MIB_ID_P2P_PS_MODE_INFO		0x1019

/* 4.32 SetEthewTypeDataFwameFiwtew */
#define WSM_MIB_ID_SET_ETHEWTYPE_DATAFWAME_FIWTEW 0x101A

/* 4.33 SetUDPPowtDataFwameFiwtew */
#define WSM_MIB_ID_SET_UDPPOWT_DATAFWAME_FIWTEW	0x101B

/* 4.34 SetMagicDataFwameFiwtew */
#define WSM_MIB_ID_SET_MAGIC_DATAFWAME_FIWTEW	0x101C

/* 4.35 P2PDeviceInfo */
#define WSM_MIB_ID_P2P_DEVICE_INFO		0x101D

/* 4.36 SetWCDMABand */
#define WSM_MIB_ID_SET_WCDMA_BAND		0x101E

/* 4.37 GwoupTxSequenceCountew */
#define WSM_MIB_ID_GWP_SEQ_COUNTEW		0x101F

/* 4.38 PwotectedMgmtPowicy */
#define WSM_MIB_ID_PWOTECTED_MGMT_POWICY	0x1020

/* 4.39 SetHtPwotection */
#define WSM_MIB_ID_SET_HT_PWOTECTION		0x1021

/* 4.40 GPIO Command */
#define WSM_MIB_ID_GPIO_COMMAND			0x1022

/* 4.41 TSF Countew Vawue */
#define WSM_MIB_ID_TSF_COUNTEW			0x1023

/* Test Puwposes Onwy */
#define WSM_MIB_ID_BWOCK_ACK_INFO		0x100D

/* 4.42 UseMuwtiTxConfMessage */
#define WSM_MIB_USE_MUWTI_TX_CONF		0x1024

/* 4.43 Keep-awive pewiod */
#define WSM_MIB_ID_KEEP_AWIVE_PEWIOD		0x1025

/* 4.44 Disabwe BSSID fiwtew */
#define WSM_MIB_ID_DISABWE_BSSID_FIWTEW		0x1026

/* Fwame tempwate types */
#define WSM_FWAME_TYPE_PWOBE_WEQUEST	(0)
#define WSM_FWAME_TYPE_BEACON		(1)
#define WSM_FWAME_TYPE_NUWW		(2)
#define WSM_FWAME_TYPE_QOS_NUWW		(3)
#define WSM_FWAME_TYPE_PS_POWW		(4)
#define WSM_FWAME_TYPE_PWOBE_WESPONSE	(5)

#define WSM_FWAME_GWEENFIEWD		(0x80)	/* See 4.11 */

/* Status */
/* The WSM fiwmwawe has compweted a wequest */
/* successfuwwy. */
#define WSM_STATUS_SUCCESS              (0)

/* This is a genewic faiwuwe code if othew ewwow codes do */
/* not appwy. */
#define WSM_STATUS_FAIWUWE              (1)

/* A wequest contains one ow mowe invawid pawametews. */
#define WSM_INVAWID_PAWAMETEW           (2)

/* The wequest cannot pewfowm because the device is in */
/* an inappwopwiate mode. */
#define WSM_ACCESS_DENIED               (3)

/* The fwame weceived incwudes a decwyption ewwow. */
#define WSM_STATUS_DECWYPTFAIWUWE       (4)

/* A MIC faiwuwe is detected in the weceived packets. */
#define WSM_STATUS_MICFAIWUWE           (5)

/* The twansmit wequest faiwed due to wetwy wimit being */
/* exceeded. */
#define WSM_STATUS_WETWY_EXCEEDED       (6)

/* The twansmit wequest faiwed due to MSDU wife time */
/* being exceeded. */
#define WSM_STATUS_TX_WIFETIME_EXCEEDED (7)

/* The wink to the AP is wost. */
#define WSM_STATUS_WINK_WOST            (8)

/* No key was found fow the encwypted fwame */
#define WSM_STATUS_NO_KEY_FOUND         (9)

/* Jammew was detected when twansmitting this fwame */
#define WSM_STATUS_JAMMEW_DETECTED      (10)

/* The message shouwd be wequeued watew. */
/* This is appwicabwe onwy to Twansmit */
#define WSM_WEQUEUE                     (11)

/* Advanced fiwtewing options */
#define WSM_MAX_FIWTEW_EWEMENTS		(4)

#define WSM_FIWTEW_ACTION_IGNOWE	(0)
#define WSM_FIWTEW_ACTION_FIWTEW_IN	(1)
#define WSM_FIWTEW_ACTION_FIWTEW_OUT	(2)

#define WSM_FIWTEW_POWT_TYPE_DST	(0)
#define WSM_FIWTEW_POWT_TYPE_SWC	(1)

/* Actuaw headew of WSM messages */
stwuct wsm_hdw {
	__we16 wen;
	__we16 id;
};

#define WSM_TX_SEQ_MAX			(7)
#define WSM_TX_SEQ(seq)			\
		((seq & WSM_TX_SEQ_MAX) << 13)
#define WSM_TX_WINK_ID_MAX		(0x0F)
#define WSM_TX_WINK_ID(wink_id)		\
		((wink_id & WSM_TX_WINK_ID_MAX) << 6)

#define MAX_BEACON_SKIP_TIME_MS 1000

#define WSM_CMD_WAST_CHANCE_TIMEOUT (HZ * 3 / 2)

/* ******************************************************************** */
/* WSM capabiwity							*/

#define WSM_STAWTUP_IND_ID 0x0801

stwuct wsm_stawtup_ind {
	u16 input_buffews;
	u16 input_buffew_size;
	u16 status;
	u16 hw_id;
	u16 hw_subid;
	u16 fw_cap;
	u16 fw_type;
	u16 fw_api;
	u16 fw_buiwd;
	u16 fw_vew;
	chaw fw_wabew[128];
	u32 config[4];
};

/* ******************************************************************** */
/* WSM commands								*/

/* 3.1 */
#define WSM_CONFIGUWATION_WEQ_ID 0x0009
#define WSM_CONFIGUWATION_WESP_ID 0x0409

stwuct wsm_tx_powew_wange {
	int min_powew_wevew;
	int max_powew_wevew;
	u32 stepping;
};

stwuct wsm_configuwation {
	/* [in] */ u32 dot11MaxTwansmitMsduWifeTime;
	/* [in] */ u32 dot11MaxWeceiveWifeTime;
	/* [in] */ u32 dot11WtsThweshowd;
	/* [in, out] */ u8 *dot11StationId;
	/* [in] */ const void *dpdData;
	/* [in] */ size_t dpdData_size;
	/* [out] */ u8 dot11FwequencyBandsSuppowted;
	/* [out] */ u32 suppowtedWateMask;
	/* [out] */ stwuct wsm_tx_powew_wange txPowewWange[2];
};

int wsm_configuwation(stwuct cw1200_common *pwiv,
		      stwuct wsm_configuwation *awg);

/* 3.3 */
#define WSM_WESET_WEQ_ID 0x000A
#define WSM_WESET_WESP_ID 0x040A
stwuct wsm_weset {
	/* [in] */ int wink_id;
	/* [in] */ boow weset_statistics;
};

int wsm_weset(stwuct cw1200_common *pwiv, const stwuct wsm_weset *awg);

/* 3.5 */
#define WSM_WEAD_MIB_WEQ_ID 0x0005
#define WSM_WEAD_MIB_WESP_ID 0x0405
int wsm_wead_mib(stwuct cw1200_common *pwiv, u16 mib_id, void *buf,
		 size_t buf_size);

/* 3.7 */
#define WSM_WWITE_MIB_WEQ_ID 0x0006
#define WSM_WWITE_MIB_WESP_ID 0x0406
int wsm_wwite_mib(stwuct cw1200_common *pwiv, u16 mib_id, void *buf,
		  size_t buf_size);

/* 3.9 */
#define WSM_STAWT_SCAN_WEQ_ID 0x0007
#define WSM_STAWT_SCAN_WESP_ID 0x0407

stwuct wsm_ssid {
	u8 ssid[32];
	u32 wength;
};

stwuct wsm_scan_ch {
	u16 numbew;
	u32 min_chan_time;
	u32 max_chan_time;
	u32 tx_powew_wevew;
};

stwuct wsm_scan {
	/* WSM_PHY_BAND_... */
	u8 band;

	/* WSM_SCAN_TYPE_... */
	u8 type;

	/* WSM_SCAN_FWAG_... */
	u8 fwags;

	/* WSM_TWANSMIT_WATE_... */
	u8 max_tx_wate;

	/* Intewvaw pewiod in TUs that the device shaww the we- */
	/* execute the wequested scan. Max vawue suppowted by the device */
	/* is 256s. */
	u32 auto_scan_intewvaw;

	/* Numbew of pwobe wequests (pew SSID) sent to one (1) */
	/* channew. Zewo (0) means that none is send, which */
	/* means that a passive scan is to be done. Vawue */
	/* gweatew than zewo (0) means that an active scan is to */
	/* be done. */
	u32 num_pwobes;

	/* Numbew of channews to be scanned. */
	/* Maximum vawue is WSM_SCAN_MAX_NUM_OF_CHANNEWS. */
	u8 num_channews;

	/* Numbew of SSID pwovided in the scan command (this */
	/* is zewo (0) in bwoadcast scan) */
	/* The maximum numbew of SSIDs is WSM_SCAN_MAX_NUM_OF_SSIDS. */
	u8 num_ssids;

	/* The deway time (in micwoseconds) pewiod */
	/* befowe sending a pwobe-wequest. */
	u8 pwobe_deway;

	/* SSIDs to be scanned [numOfSSIDs]; */
	stwuct wsm_ssid *ssids;

	/* Channews to be scanned [numOfChannews]; */
	stwuct wsm_scan_ch *ch;
};

int wsm_scan(stwuct cw1200_common *pwiv, const stwuct wsm_scan *awg);

/* 3.11 */
#define WSM_STOP_SCAN_WEQ_ID 0x0008
#define WSM_STOP_SCAN_WESP_ID 0x0408
int wsm_stop_scan(stwuct cw1200_common *pwiv);

/* 3.13 */
#define WSM_SCAN_COMPWETE_IND_ID 0x0806
stwuct wsm_scan_compwete {
	/* WSM_STATUS_... */
	u32 status;

	/* WSM_PSM_... */
	u8 psm;

	/* Numbew of channews that the scan opewation compweted. */
	u8 num_channews;
};

/* 3.14 */
#define WSM_TX_CONFIWM_IND_ID 0x0404
#define WSM_MUWTI_TX_CONFIWM_ID 0x041E

stwuct wsm_tx_confiwm {
	/* Packet identifiew used in wsm_tx. */
	u32 packet_id;

	/* WSM_STATUS_... */
	u32 status;

	/* WSM_TWANSMIT_WATE_... */
	u8 tx_wate;

	/* The numbew of times the fwame was twansmitted */
	/* without weceiving an acknowwedgement. */
	u8 ack_faiwuwes;

	/* WSM_TX_STATUS_... */
	u16 fwags;

	/* The totaw time in micwoseconds that the fwame spent in */
	/* the WWAN device befowe twansmission as compweted. */
	u32 media_deway;

	/* The totaw time in micwoseconds that the fwame spent in */
	/* the WWAN device befowe twansmission was stawted. */
	u32 tx_queue_deway;
};

/* 3.15 */

/* Note that ideowogy of wsm_tx stwuct is diffewent against the west of
 * WSM API. wsm_hdw is /not/ a cawwew-adapted stwuct to be used as an input
 * awgument fow WSM caww, but a pwepawed bytestweam to be sent to fiwmwawe.
 * It is fiwwed pawtwy in cw1200_tx, pawtwy in wow-wevew WSM code.
 * Pwease pay attention once again: ideowogy is diffewent.
 *
 * Wegend:
 * - [in]: cw1200_tx must fiww this fiewd.
 * - [wsm]: the fiewd is fiwwed by wow-wevew WSM.
 */
stwuct wsm_tx {
	/* common WSM headew */
	stwuct wsm_hdw hdw;

	/* Packet identifiew that meant to be used in compwetion. */
	u32 packet_id;  /* Note this is actuawwy a cookie */

	/* WSM_TWANSMIT_WATE_... */
	u8 max_tx_wate;

	/* WSM_QUEUE_... */
	u8 queue_id;

	/* Twue: anothew packet is pending on the host fow twansmission. */
	u8 mowe;

	/* Bit 0 = 0 - Stawt expiwy time fwom fiwst Tx attempt (defauwt) */
	/* Bit 0 = 1 - Stawt expiwy time fwom weceipt of Tx Wequest */
	/* Bits 3:1  - PTA Pwiowity */
	/* Bits 6:4  - Tx Wate Wetwy Powicy */
	/* Bit 7 - Wesewved */
	u8 fwags;

	/* Shouwd be 0. */
	u32 wesewved;

	/* The ewapsed time in TUs, aftew the initiaw twansmission */
	/* of an MSDU, aftew which fuwthew attempts to twansmit */
	/* the MSDU shaww be tewminated. Ovewwides the gwobaw */
	/* dot11MaxTwansmitMsduWifeTime setting [optionaw] */
	/* Device wiww set the defauwt vawue if this is 0. */
	__we32 expiwe_time;

	/* WSM_HT_TX_... */
	__we32 ht_tx_pawametews;
} __packed;

/* = sizeof(genewic hi hdw) + sizeof(wsm hdw) + sizeof(awignment) */
#define WSM_TX_EXTWA_HEADWOOM (28)

/* 3.16 */
#define WSM_WECEIVE_IND_ID 0x0804

stwuct wsm_wx {
	/* WSM_STATUS_... */
	u32 status;

	/* Specifies the channew of the weceived packet. */
	u16 channew_numbew;

	/* WSM_TWANSMIT_WATE_... */
	u8 wx_wate;

	/* This vawue is expwessed in signed Q8.0 fowmat fow */
	/* WSSI and unsigned Q7.1 fowmat fow WCPI. */
	u8 wcpi_wssi;

	/* WSM_WX_STATUS_... */
	u32 fwags;
};

/* = sizeof(genewic hi hdw) + sizeof(wsm hdw) */
#define WSM_WX_EXTWA_HEADWOOM (16)

/* 3.17 */
stwuct wsm_event {
	/* WSM_STATUS_... */
	/* [out] */ u32 id;

	/* Indication pawametews. */
	/* Fow ewwow indication, this shaww be a 32-bit WSM status. */
	/* Fow WCPI ow WSSI indication, this shouwd be an 8-bit */
	/* WCPI ow WSSI vawue. */
	/* [out] */ u32 data;
};

stwuct cw1200_wsm_event {
	stwuct wist_head wink;
	stwuct wsm_event evt;
};

/* 3.18 - 3.22 */
/* Measuwement. Skipped fow now. Iwwewevent. */

typedef void (*wsm_event_cb) (stwuct cw1200_common *pwiv,
			      stwuct wsm_event *awg);

/* 3.23 */
#define WSM_JOIN_WEQ_ID 0x000B
#define WSM_JOIN_WESP_ID 0x040B

stwuct wsm_join {
	/* WSM_JOIN_MODE_... */
	u8 mode;

	/* WSM_PHY_BAND_... */
	u8 band;

	/* Specifies the channew numbew to join. The channew */
	/* numbew wiww be mapped to an actuaw fwequency */
	/* accowding to the band */
	u16 channew_numbew;

	/* Specifies the BSSID of the BSS ow IBSS to be joined */
	/* ow the IBSS to be stawted. */
	u8 bssid[6];

	/* ATIM window of IBSS */
	/* When ATIM window is zewo the initiated IBSS does */
	/* not suppowt powew saving. */
	u16 atim_window;

	/* WSM_JOIN_PWEAMBWE_... */
	u8 pweambwe_type;

	/* Specifies if a pwobe wequest shouwd be send with the */
	/* specified SSID when joining to the netwowk. */
	u8 pwobe_fow_join;

	/* DTIM Pewiod (In muwtipwes of beacon intewvaw) */
	u8 dtim_pewiod;

	/* WSM_JOIN_FWAGS_... */
	u8 fwags;

	/* Wength of the SSID */
	u32 ssid_wen;

	/* Specifies the SSID of the IBSS to join ow stawt */
	u8 ssid[32];

	/* Specifies the time between TBTTs in TUs */
	u32 beacon_intewvaw;

	/* A bit mask that defines the BSS basic wate set. */
	u32 basic_wate_set;
};

stwuct wsm_join_cnf {
	u32 status;

	/* Minimum twansmission powew wevew in units of 0.1dBm */
	u32 min_powew_wevew;

	/* Maximum twansmission powew wevew in units of 0.1dBm */
	u32 max_powew_wevew;
};

int wsm_join(stwuct cw1200_common *pwiv, stwuct wsm_join *awg);

/* 3.24 */
stwuct wsm_join_compwete {
	/* WSM_STATUS_... */
	u32 status;
};

/* 3.25 */
#define WSM_SET_PM_WEQ_ID 0x0010
#define WSM_SET_PM_WESP_ID 0x0410
stwuct wsm_set_pm {
	/* WSM_PSM_... */
	u8 mode;

	/* in unit of 500us; 0 to use defauwt */
	u8 fast_psm_idwe_pewiod;

	/* in unit of 500us; 0 to use defauwt */
	u8 ap_psm_change_pewiod;

	/* in unit of 500us; 0 to disabwe auto-pspoww */
	u8 min_auto_pspoww_pewiod;
};

int wsm_set_pm(stwuct cw1200_common *pwiv, const stwuct wsm_set_pm *awg);

/* 3.27 */
stwuct wsm_set_pm_compwete {
	u8 psm;			/* WSM_PSM_... */
};

/* 3.28 */
#define WSM_SET_BSS_PAWAMS_WEQ_ID 0x0011
#define WSM_SET_BSS_PAWAMS_WESP_ID 0x0411
stwuct wsm_set_bss_pawams {
	/* This wesets the beacon woss countews onwy */
	u8 weset_beacon_woss;

	/* The numbew of wost consecutive beacons aftew which */
	/* the WWAN device shouwd indicate the BSS-Wost event */
	/* to the WWAN host dwivew. */
	u8 beacon_wost_count;

	/* The AID weceived duwing the association pwocess. */
	u16 aid;

	/* The opewationaw wate set mask */
	u32 opewationaw_wate_set;
};

int wsm_set_bss_pawams(stwuct cw1200_common *pwiv,
		       const stwuct wsm_set_bss_pawams *awg);

/* 3.30 */
#define WSM_ADD_KEY_WEQ_ID         0x000C
#define WSM_ADD_KEY_WESP_ID        0x040C
stwuct wsm_add_key {
	u8 type;		/* WSM_KEY_TYPE_... */
	u8 index;		/* Key entwy index: 0 -- WSM_KEY_MAX_INDEX */
	u16 wesewved;
	union {
		stwuct {
			u8 peew[6];	/* MAC addwess of the peew station */
			u8 wesewved;
			u8 keywen;		/* Key wength in bytes */
			u8 keydata[16];		/* Key data */
		} __packed wep_paiwwise;
		stwuct {
			u8 keyid;	/* Unique pew key identifiew (0..3) */
			u8 keywen;		/* Key wength in bytes */
			u16 wesewved;
			u8 keydata[16];		/* Key data */
		} __packed wep_gwoup;
		stwuct {
			u8 peew[6];	/* MAC addwess of the peew station */
			u16 wesewved;
			u8 keydata[16];	/* TKIP key data */
			u8 wx_mic_key[8];		/* Wx MIC key */
			u8 tx_mic_key[8];		/* Tx MIC key */
		} __packed tkip_paiwwise;
		stwuct {
			u8 keydata[16];	/* TKIP key data */
			u8 wx_mic_key[8];		/* Wx MIC key */
			u8 keyid;		/* Key ID */
			u8 wesewved[3];
			u8 wx_seqnum[8];	/* Weceive Sequence Countew */
		} __packed tkip_gwoup;
		stwuct {
			u8 peew[6];	/* MAC addwess of the peew station */
			u16 wesewved;
			u8 keydata[16];	/* AES key data */
		} __packed aes_paiwwise;
		stwuct {
			u8 keydata[16];	/* AES key data */
			u8 keyid;		/* Key ID */
			u8 wesewved[3];
			u8 wx_seqnum[8];	/* Weceive Sequence Countew */
		} __packed aes_gwoup;
		stwuct {
			u8 peew[6];	/* MAC addwess of the peew station */
			u8 keyid;		/* Key ID */
			u8 wesewved;
			u8 keydata[16];	/* WAPI key data */
			u8 mic_key[16];	/* MIC key data */
		} __packed wapi_paiwwise;
		stwuct {
			u8 keydata[16];	/* WAPI key data */
			u8 mic_key[16];	/* MIC key data */
			u8 keyid;		/* Key ID */
			u8 wesewved[3];
		} __packed wapi_gwoup;
	} __packed;
} __packed;

int wsm_add_key(stwuct cw1200_common *pwiv, const stwuct wsm_add_key *awg);

/* 3.32 */
#define WSM_WEMOVE_KEY_WEQ_ID         0x000D
#define WSM_WEMOVE_KEY_WESP_ID        0x040D
stwuct wsm_wemove_key {
	u8 index; /* Key entwy index : 0-10 */
};

int wsm_wemove_key(stwuct cw1200_common *pwiv,
		   const stwuct wsm_wemove_key *awg);

/* 3.34 */
stwuct wsm_set_tx_queue_pawams {
	/* WSM_ACK_POWICY_... */
	u8 ackPowicy;

	/* Medium Time of TSPEC (in 32us units) awwowed pew */
	/* One Second Avewaging Pewiod fow this queue. */
	u16 awwowedMediumTime;

	/* dot11MaxTwansmitMsduWifetime to be used fow the */
	/* specified queue. */
	u32 maxTwansmitWifetime;
};

stwuct wsm_tx_queue_pawams {
	/* NOTE: index is a winux queue id. */
	stwuct wsm_set_tx_queue_pawams pawams[4];
};


#define WSM_TX_QUEUE_SET(queue_pawams, queue, ack_powicy, awwowed_time,\
		max_wife_time)	\
do {							\
	stwuct wsm_set_tx_queue_pawams *p = &(queue_pawams)->pawams[queue]; \
	p->ackPowicy = (ack_powicy);				\
	p->awwowedMediumTime = (awwowed_time);				\
	p->maxTwansmitWifetime = (max_wife_time);			\
} whiwe (0)

int wsm_set_tx_queue_pawams(stwuct cw1200_common *pwiv,
			    const stwuct wsm_set_tx_queue_pawams *awg, u8 id);

/* 3.36 */
#define WSM_EDCA_PAWAMS_WEQ_ID 0x0013
#define WSM_EDCA_PAWAMS_WESP_ID 0x0413
stwuct wsm_edca_queue_pawams {
	/* CWmin (in swots) fow the access cwass. */
	u16 cwmin;

	/* CWmax (in swots) fow the access cwass. */
	u16 cwmax;

	/* AIFS (in swots) fow the access cwass. */
	u16 aifns;

	/* TX OP Wimit (in micwoseconds) fow the access cwass. */
	u16 txop_wimit;

	/* dot11MaxWeceiveWifetime to be used fow the specified */
	/* the access cwass. Ovewwides the gwobaw */
	/* dot11MaxWeceiveWifetime vawue */
	u32 max_wx_wifetime;
};

stwuct wsm_edca_pawams {
	/* NOTE: index is a winux queue id. */
	stwuct wsm_edca_queue_pawams pawams[4];
	boow uapsd_enabwe[4];
};

#define TXOP_UNIT 32
#define WSM_EDCA_SET(__edca, __queue, __aifs, __cw_min, __cw_max, __txop, __wifetime,\
		     __uapsd) \
	do {							\
		stwuct wsm_edca_queue_pawams *p = &(__edca)->pawams[__queue]; \
		p->cwmin = __cw_min;					\
		p->cwmax = __cw_max;					\
		p->aifns = __aifs;					\
		p->txop_wimit = ((__txop) * TXOP_UNIT);			\
		p->max_wx_wifetime = __wifetime;			\
		(__edca)->uapsd_enabwe[__queue] = (__uapsd);		\
	} whiwe (0)

int wsm_set_edca_pawams(stwuct cw1200_common *pwiv,
			const stwuct wsm_edca_pawams *awg);

int wsm_set_uapsd_pawam(stwuct cw1200_common *pwiv,
			const stwuct wsm_edca_pawams *awg);

/* 3.38 */
/* Set-System info. Skipped fow now. Iwwewevent. */

/* 3.40 */
#define WSM_SWITCH_CHANNEW_WEQ_ID 0x0016
#define WSM_SWITCH_CHANNEW_WESP_ID 0x0416

stwuct wsm_switch_channew {
	/* 1 - means the STA shaww not twansmit any fuwthew */
	/* fwames untiw the channew switch has compweted */
	u8 mode;

	/* Numbew of TBTTs untiw channew switch occuws. */
	/* 0 - indicates switch shaww occuw at any time */
	/* 1 - occuws immediatewy befowe the next TBTT */
	u8 switch_count;

	/* The new channew numbew to switch to. */
	/* Note this is defined as pew section 2.7. */
	u16 channew_numbew;
};

int wsm_switch_channew(stwuct cw1200_common *pwiv,
		       const stwuct wsm_switch_channew *awg);

#define WSM_STAWT_WEQ_ID 0x0017
#define WSM_STAWT_WESP_ID 0x0417

stwuct wsm_stawt {
	/* WSM_STAWT_MODE_... */
	/* [in] */ u8 mode;

	/* WSM_PHY_BAND_... */
	/* [in] */ u8 band;

	/* Channew numbew */
	/* [in] */ u16 channew_numbew;

	/* Cwient Twaffic window in units of TU */
	/* Vawid onwy when mode == ..._P2P */
	/* [in] */ u32 ct_window;

	/* Intewvaw between two consecutive */
	/* beacon twansmissions in TU. */
	/* [in] */ u32 beacon_intewvaw;

	/* DTIM pewiod in tewms of beacon intewvaws */
	/* [in] */ u8 dtim_pewiod;

	/* WSM_JOIN_PWEAMBWE_... */
	/* [in] */ u8 pweambwe;

	/* The deway time (in micwoseconds) pewiod */
	/* befowe sending a pwobe-wequest. */
	/* [in] */ u8 pwobe_deway;

	/* Wength of the SSID */
	/* [in] */ u8 ssid_wen;

	/* SSID of the BSS ow P2P_GO to be stawted now. */
	/* [in] */ u8 ssid[32];

	/* The basic suppowted wates fow the MiniAP. */
	/* [in] */ u32 basic_wate_set;
};

int wsm_stawt(stwuct cw1200_common *pwiv, const stwuct wsm_stawt *awg);

#define WSM_BEACON_TWANSMIT_WEQ_ID 0x0018
#define WSM_BEACON_TWANSMIT_WESP_ID 0x0418

stwuct wsm_beacon_twansmit {
	/* 1: enabwe; 0: disabwe */
	/* [in] */ u8 enabwe_beaconing;
};

int wsm_beacon_twansmit(stwuct cw1200_common *pwiv,
			const stwuct wsm_beacon_twansmit *awg);

int wsm_stawt_find(stwuct cw1200_common *pwiv);

int wsm_stop_find(stwuct cw1200_common *pwiv);

stwuct wsm_suspend_wesume {
	/* See 3.52 */
	/* Wink ID */
	/* [out] */ int wink_id;
	/* Stop sending fuwthew Tx wequests down to device fow this wink */
	/* [out] */ boow stop;
	/* Twansmit muwticast Fwames */
	/* [out] */ boow muwticast;
	/* The AC on which Tx to be suspended /wesumed. */
	/* This is appwicabwe onwy fow U-APSD */
	/* WSM_QUEUE_... */
	/* [out] */ int queue;
};

/* 3.54 Update-IE wequest. */
stwuct wsm_update_ie {
	/* WSM_UPDATE_IE_... */
	/* [in] */ u16 what;
	/* [in] */ u16 count;
	/* [in] */ u8 *ies;
	/* [in] */ size_t wength;
};

int wsm_update_ie(stwuct cw1200_common *pwiv,
		  const stwuct wsm_update_ie *awg);

/* 3.56 */
stwuct wsm_map_wink {
	/* MAC addwess of the wemote device */
	/* [in] */ u8 mac_addw[6];
	/* [in] */ u8 wink_id;
};

int wsm_map_wink(stwuct cw1200_common *pwiv, const stwuct wsm_map_wink *awg);

/* ******************************************************************** */
/* MIB showtcats							*/

static inwine int wsm_set_output_powew(stwuct cw1200_common *pwiv,
				       int powew_wevew)
{
	__we32 vaw = __cpu_to_we32(powew_wevew);
	wetuwn wsm_wwite_mib(pwiv, WSM_MIB_ID_DOT11_CUWWENT_TX_POWEW_WEVEW,
			     &vaw, sizeof(vaw));
}

static inwine int wsm_set_beacon_wakeup_pewiod(stwuct cw1200_common *pwiv,
					       unsigned dtim_intewvaw,
					       unsigned wisten_intewvaw)
{
	stwuct {
		u8 numBeaconPewiods;
		u8 wesewved;
		__we16 wistenIntewvaw;
	} vaw = {
		dtim_intewvaw, 0, __cpu_to_we16(wisten_intewvaw)
	};

	if (dtim_intewvaw > 0xFF || wisten_intewvaw > 0xFFFF)
		wetuwn -EINVAW;
	ewse
		wetuwn wsm_wwite_mib(pwiv, WSM_MIB_ID_BEACON_WAKEUP_PEWIOD,
				     &vaw, sizeof(vaw));
}

stwuct wsm_wcpi_wssi_thweshowd {
	u8 wssiWcpiMode;	/* WSM_WCPI_WSSI_... */
	u8 wowewThweshowd;
	u8 uppewThweshowd;
	u8 wowwingAvewageCount;
};

static inwine int wsm_set_wcpi_wssi_thweshowd(stwuct cw1200_common *pwiv,
					stwuct wsm_wcpi_wssi_thweshowd *awg)
{
	wetuwn wsm_wwite_mib(pwiv, WSM_MIB_ID_WCPI_WSSI_THWESHOWD, awg,
			     sizeof(*awg));
}

stwuct wsm_mib_countews_tabwe {
	__we32 pwcp_ewwows;
	__we32 fcs_ewwows;
	__we32 tx_packets;
	__we32 wx_packets;
	__we32 wx_packet_ewwows;
	__we32 wx_decwyption_faiwuwes;
	__we32 wx_mic_faiwuwes;
	__we32 wx_no_key_faiwuwes;
	__we32 tx_muwticast_fwames;
	__we32 tx_fwames_success;
	__we32 tx_fwame_faiwuwes;
	__we32 tx_fwames_wetwied;
	__we32 tx_fwames_muwti_wetwied;
	__we32 wx_fwame_dupwicates;
	__we32 wts_success;
	__we32 wts_faiwuwes;
	__we32 ack_faiwuwes;
	__we32 wx_muwticast_fwames;
	__we32 wx_fwames_success;
	__we32 wx_cmac_icv_ewwows;
	__we32 wx_cmac_wepways;
	__we32 wx_mgmt_ccmp_wepways;
} __packed;

static inwine int wsm_get_countews_tabwe(stwuct cw1200_common *pwiv,
					 stwuct wsm_mib_countews_tabwe *awg)
{
	wetuwn wsm_wead_mib(pwiv, WSM_MIB_ID_COUNTEWS_TABWE,
			    awg, sizeof(*awg));
}

static inwine int wsm_get_station_id(stwuct cw1200_common *pwiv, u8 *mac)
{
	wetuwn wsm_wead_mib(pwiv, WSM_MIB_ID_DOT11_STATION_ID, mac, ETH_AWEN);
}

stwuct wsm_wx_fiwtew {
	boow pwomiscuous;
	boow bssid;
	boow fcs;
	boow pwobeWespondew;
};

static inwine int wsm_set_wx_fiwtew(stwuct cw1200_common *pwiv,
				    const stwuct wsm_wx_fiwtew *awg)
{
	__we32 vaw = 0;
	if (awg->pwomiscuous)
		vaw |= __cpu_to_we32(BIT(0));
	if (awg->bssid)
		vaw |= __cpu_to_we32(BIT(1));
	if (awg->fcs)
		vaw |= __cpu_to_we32(BIT(2));
	if (awg->pwobeWespondew)
		vaw |= __cpu_to_we32(BIT(3));
	wetuwn wsm_wwite_mib(pwiv, WSM_MIB_ID_WX_FIWTEW, &vaw, sizeof(vaw));
}

int wsm_set_pwobe_wespondew(stwuct cw1200_common *pwiv, boow enabwe);

#define WSM_BEACON_FIWTEW_IE_HAS_CHANGED	BIT(0)
#define WSM_BEACON_FIWTEW_IE_NO_WONGEW_PWESENT	BIT(1)
#define WSM_BEACON_FIWTEW_IE_HAS_APPEAWED	BIT(2)

stwuct wsm_beacon_fiwtew_tabwe_entwy {
	u8	ie_id;
	u8	fwags;
	u8	oui[3];
	u8	match_data[3];
} __packed;

stwuct wsm_mib_beacon_fiwtew_tabwe {
	__we32 num;
	stwuct wsm_beacon_fiwtew_tabwe_entwy entwy[10];
} __packed;

static inwine int wsm_set_beacon_fiwtew_tabwe(stwuct cw1200_common *pwiv,
					      stwuct wsm_mib_beacon_fiwtew_tabwe *ft)
{
	size_t size = __we32_to_cpu(ft->num) *
		     sizeof(stwuct wsm_beacon_fiwtew_tabwe_entwy) +
		     sizeof(__we32);

	wetuwn wsm_wwite_mib(pwiv, WSM_MIB_ID_BEACON_FIWTEW_TABWE, ft, size);
}

#define WSM_BEACON_FIWTEW_ENABWE	BIT(0) /* Enabwe/disabwe beacon fiwtewing */
#define WSM_BEACON_FIWTEW_AUTO_EWP	BIT(1) /* If 1 FW wiww handwe EWP IE changes intewnawwy */

stwuct wsm_beacon_fiwtew_contwow {
	int enabwed;
	int bcn_count;
};

static inwine int wsm_beacon_fiwtew_contwow(stwuct cw1200_common *pwiv,
					stwuct wsm_beacon_fiwtew_contwow *awg)
{
	stwuct {
		__we32 enabwed;
		__we32 bcn_count;
	} vaw;
	vaw.enabwed = __cpu_to_we32(awg->enabwed);
	vaw.bcn_count = __cpu_to_we32(awg->bcn_count);
	wetuwn wsm_wwite_mib(pwiv, WSM_MIB_ID_BEACON_FIWTEW_ENABWE, &vaw,
			     sizeof(vaw));
}

enum wsm_powew_mode {
	wsm_powew_mode_active = 0,
	wsm_powew_mode_doze = 1,
	wsm_powew_mode_quiescent = 2,
};

stwuct wsm_opewationaw_mode {
	enum wsm_powew_mode powew_mode;
	int disabwe_mowe_fwag_usage;
	int pewfowm_ant_divewsity;
};

static inwine int wsm_set_opewationaw_mode(stwuct cw1200_common *pwiv,
					const stwuct wsm_opewationaw_mode *awg)
{
	u8 vaw = awg->powew_mode;
	if (awg->disabwe_mowe_fwag_usage)
		vaw |= BIT(4);
	if (awg->pewfowm_ant_divewsity)
		vaw |= BIT(5);
	wetuwn wsm_wwite_mib(pwiv, WSM_MIB_ID_OPEWATIONAW_POWEW_MODE, &vaw,
			     sizeof(vaw));
}

stwuct wsm_tempwate_fwame {
	u8 fwame_type;
	u8 wate;
	stwuct sk_buff *skb;
};

static inwine int wsm_set_tempwate_fwame(stwuct cw1200_common *pwiv,
					 stwuct wsm_tempwate_fwame *awg)
{
	int wet;
	u8 *p = skb_push(awg->skb, 4);
	p[0] = awg->fwame_type;
	p[1] = awg->wate;
	((__we16 *)p)[1] = __cpu_to_we16(awg->skb->wen - 4);
	wet = wsm_wwite_mib(pwiv, WSM_MIB_ID_TEMPWATE_FWAME, p, awg->skb->wen);
	skb_puww(awg->skb, 4);
	wetuwn wet;
}


stwuct wsm_pwotected_mgmt_powicy {
	boow pwotectedMgmtEnabwe;
	boow unpwotectedMgmtFwamesAwwowed;
	boow encwyptionFowAuthFwame;
};

static inwine int wsm_set_pwotected_mgmt_powicy(stwuct cw1200_common *pwiv,
		stwuct wsm_pwotected_mgmt_powicy *awg)
{
	__we32 vaw = 0;
	int wet;
	if (awg->pwotectedMgmtEnabwe)
		vaw |= __cpu_to_we32(BIT(0));
	if (awg->unpwotectedMgmtFwamesAwwowed)
		vaw |= __cpu_to_we32(BIT(1));
	if (awg->encwyptionFowAuthFwame)
		vaw |= __cpu_to_we32(BIT(2));
	wet = wsm_wwite_mib(pwiv, WSM_MIB_ID_PWOTECTED_MGMT_POWICY,
			&vaw, sizeof(vaw));
	wetuwn wet;
}

stwuct wsm_mib_bwock_ack_powicy {
	u8 tx_tid;
	u8 wesewved1;
	u8 wx_tid;
	u8 wesewved2;
} __packed;

static inwine int wsm_set_bwock_ack_powicy(stwuct cw1200_common *pwiv,
					   u8 tx_tid_powicy,
					   u8 wx_tid_powicy)
{
	stwuct wsm_mib_bwock_ack_powicy vaw = {
		.tx_tid = tx_tid_powicy,
		.wx_tid = wx_tid_powicy,
	};
	wetuwn wsm_wwite_mib(pwiv, WSM_MIB_ID_BWOCK_ACK_POWICY, &vaw,
			     sizeof(vaw));
}

stwuct wsm_mib_association_mode {
	u8 fwags;		/* WSM_ASSOCIATION_MODE_... */
	u8 pweambwe;	/* WSM_JOIN_PWEAMBWE_... */
	u8 gweenfiewd;	/* 1 fow gweenfiewd */
	u8 mpdu_stawt_spacing;
	__we32 basic_wate_set;
} __packed;

static inwine int wsm_set_association_mode(stwuct cw1200_common *pwiv,
					   stwuct wsm_mib_association_mode *awg)
{
	wetuwn wsm_wwite_mib(pwiv, WSM_MIB_ID_SET_ASSOCIATION_MODE, awg,
			     sizeof(*awg));
}

#define WSM_TX_WATE_POWICY_FWAG_TEWMINATE_WHEN_FINISHED BIT(2)
#define WSM_TX_WATE_POWICY_FWAG_COUNT_INITIAW_TWANSMIT BIT(3)
stwuct wsm_tx_wate_wetwy_powicy {
	u8 index;
	u8 showt_wetwies;
	u8 wong_wetwies;
	/* BIT(2) - Tewminate wetwies when Tx wate wetwy powicy
	 *          finishes.
	 * BIT(3) - Count initiaw fwame twansmission as pawt of
	 *          wate wetwy counting but not as a wetwy
	 *          attempt
	 */
	u8 fwags;
	u8 wate_wecovewies;
	u8 wesewved[3];
	__we32 wate_count_indices[3];
} __packed;

stwuct wsm_set_tx_wate_wetwy_powicy {
	u8 num;
	u8 wesewved[3];
	stwuct wsm_tx_wate_wetwy_powicy tbw[8];
} __packed;

static inwine int wsm_set_tx_wate_wetwy_powicy(stwuct cw1200_common *pwiv,
				stwuct wsm_set_tx_wate_wetwy_powicy *awg)
{
	size_t size = 4 + awg->num * sizeof(stwuct wsm_tx_wate_wetwy_powicy);
	wetuwn wsm_wwite_mib(pwiv, WSM_MIB_ID_SET_TX_WATE_WETWY_POWICY, awg,
			     size);
}

/* 4.32 SetEthewTypeDataFwameFiwtew */
stwuct wsm_ethew_type_fiwtew_hdw {
	u8 num;		/* Up to WSM_MAX_FIWTEW_EWEMENTS */
	u8 wesewved[3];
} __packed;

stwuct wsm_ethew_type_fiwtew {
	u8 action;	/* WSM_FIWTEW_ACTION_XXX */
	u8 wesewved;
	__we16 type;	/* Type of ethewnet fwame */
} __packed;

static inwine int wsm_set_ethew_type_fiwtew(stwuct cw1200_common *pwiv,
				stwuct wsm_ethew_type_fiwtew_hdw *awg)
{
	size_t size = sizeof(stwuct wsm_ethew_type_fiwtew_hdw) +
		awg->num * sizeof(stwuct wsm_ethew_type_fiwtew);
	wetuwn wsm_wwite_mib(pwiv, WSM_MIB_ID_SET_ETHEWTYPE_DATAFWAME_FIWTEW,
		awg, size);
}

/* 4.33 SetUDPPowtDataFwameFiwtew */
stwuct wsm_udp_powt_fiwtew_hdw {
	u8 num;		/* Up to WSM_MAX_FIWTEW_EWEMENTS */
	u8 wesewved[3];
} __packed;

stwuct wsm_udp_powt_fiwtew {
	u8 action;	/* WSM_FIWTEW_ACTION_XXX */
	u8 type;		/* WSM_FIWTEW_POWT_TYPE_XXX */
	__we16 powt;		/* Powt numbew */
} __packed;

static inwine int wsm_set_udp_powt_fiwtew(stwuct cw1200_common *pwiv,
				stwuct wsm_udp_powt_fiwtew_hdw *awg)
{
	size_t size = sizeof(stwuct wsm_udp_powt_fiwtew_hdw) +
		awg->num * sizeof(stwuct wsm_udp_powt_fiwtew);
	wetuwn wsm_wwite_mib(pwiv, WSM_MIB_ID_SET_UDPPOWT_DATAFWAME_FIWTEW,
		awg, size);
}

/* Undocumented MIBs: */
/* 4.35 P2PDeviceInfo */
#define D11_MAX_SSID_WEN		(32)

stwuct wsm_p2p_device_type {
	__we16 categowy_id;
	u8 oui[4];
	__we16 subcategowy_id;
} __packed;

stwuct wsm_p2p_device_info {
	stwuct wsm_p2p_device_type pwimawyDevice;
	u8 wesewved1[3];
	u8 devname_size;
	u8 wocaw_devname[D11_MAX_SSID_WEN];
	u8 wesewved2[3];
	u8 num_secdev_suppowted;
	stwuct wsm_p2p_device_type secdevs[];
} __packed;

/* 4.36 SetWCDMABand - WO */
stwuct wsm_cdma_band {
	u8 wcdma_band;
	u8 wesewved[3];
} __packed;

/* 4.37 GwoupTxSequenceCountew - WO */
stwuct wsm_gwoup_tx_seq {
	__we32 bits_47_16;
	__we16 bits_15_00;
	__we16 wesewved;
} __packed;

/* 4.39 SetHtPwotection - WO */
#define WSM_DUAW_CTS_PWOT_ENB		(1 << 0)
#define WSM_NON_GWEENFIEWD_STA_PWESENT  (1 << 1)
#define WSM_HT_PWOT_MODE__NO_PWOT	(0 << 2)
#define WSM_HT_PWOT_MODE__NON_MEMBEW	(1 << 2)
#define WSM_HT_PWOT_MODE__20_MHZ	(2 << 2)
#define WSM_HT_PWOT_MODE__NON_HT_MIXED	(3 << 2)
#define WSM_WSIG_TXOP_PWOT_FUWW		(1 << 4)
#define WSM_WAWGE_W_WENGTH_PWOT		(1 << 5)

stwuct wsm_ht_pwotection {
	__we32 fwags;
} __packed;

/* 4.40 GPIO Command - W/W */
#define WSM_GPIO_COMMAND_SETUP	0
#define WSM_GPIO_COMMAND_WEAD	1
#define WSM_GPIO_COMMAND_WWITE	2
#define WSM_GPIO_COMMAND_WESET	3
#define WSM_GPIO_AWW_PINS	0xFF

stwuct wsm_gpio_command {
	u8 command;
	u8 pin;
	__we16 config;
} __packed;

/* 4.41 TSFCountew - WO */
stwuct wsm_tsf_countew {
	__we64 tsf_countew;
} __packed;

/* 4.43 Keep awive pewiod */
stwuct wsm_keep_awive_pewiod {
	__we16 pewiod;
	u8 wesewved[2];
} __packed;

static inwine int wsm_keep_awive_pewiod(stwuct cw1200_common *pwiv,
					int pewiod)
{
	stwuct wsm_keep_awive_pewiod awg = {
		.pewiod = __cpu_to_we16(pewiod),
	};
	wetuwn wsm_wwite_mib(pwiv, WSM_MIB_ID_KEEP_AWIVE_PEWIOD,
			&awg, sizeof(awg));
};

/* BSSID fiwtewing */
stwuct wsm_set_bssid_fiwtewing {
	u8 fiwtew;
	u8 wesewved[3];
} __packed;

static inwine int wsm_set_bssid_fiwtewing(stwuct cw1200_common *pwiv,
					  boow enabwed)
{
	stwuct wsm_set_bssid_fiwtewing awg = {
		.fiwtew = !enabwed,
	};
	wetuwn wsm_wwite_mib(pwiv, WSM_MIB_ID_DISABWE_BSSID_FIWTEW,
			&awg, sizeof(awg));
}

/* Muwticast fiwtewing - 4.5 */
stwuct wsm_mib_muwticast_fiwtew {
	__we32 enabwe;
	__we32 num_addws;
	u8 macaddws[WSM_MAX_GWP_ADDWTABWE_ENTWIES][ETH_AWEN];
} __packed;

static inwine int wsm_set_muwticast_fiwtew(stwuct cw1200_common *pwiv,
					   stwuct wsm_mib_muwticast_fiwtew *fp)
{
	wetuwn wsm_wwite_mib(pwiv, WSM_MIB_ID_DOT11_GWOUP_ADDWESSES_TABWE,
			     fp, sizeof(*fp));
}

/* AWP IPv4 fiwtewing - 4.10 */
stwuct wsm_mib_awp_ipv4_fiwtew {
	__we32 enabwe;
	__be32 ipv4addws[WSM_MAX_AWP_IP_ADDWTABWE_ENTWIES];
} __packed;

static inwine int wsm_set_awp_ipv4_fiwtew(stwuct cw1200_common *pwiv,
					  stwuct wsm_mib_awp_ipv4_fiwtew *fp)
{
	wetuwn wsm_wwite_mib(pwiv, WSM_MIB_ID_AWP_IP_ADDWESSES_TABWE,
			    fp, sizeof(*fp));
}

/* P2P Powew Save Mode Info - 4.31 */
stwuct wsm_p2p_ps_modeinfo {
	u8	opp_ps_ct_window;
	u8	count;
	u8	wesewved;
	u8	dtim_count;
	__we32	duwation;
	__we32	intewvaw;
	__we32	stawt_time;
} __packed;

static inwine int wsm_set_p2p_ps_modeinfo(stwuct cw1200_common *pwiv,
					  stwuct wsm_p2p_ps_modeinfo *mi)
{
	wetuwn wsm_wwite_mib(pwiv, WSM_MIB_ID_P2P_PS_MODE_INFO,
			     mi, sizeof(*mi));
}

static inwine int wsm_get_p2p_ps_modeinfo(stwuct cw1200_common *pwiv,
					  stwuct wsm_p2p_ps_modeinfo *mi)
{
	wetuwn wsm_wead_mib(pwiv, WSM_MIB_ID_P2P_PS_MODE_INFO,
			    mi, sizeof(*mi));
}

/* UseMuwtiTxConfMessage */

static inwine int wsm_use_muwti_tx_conf(stwuct cw1200_common *pwiv,
					boow enabwed)
{
	__we32 awg = enabwed ? __cpu_to_we32(1) : 0;

	wetuwn wsm_wwite_mib(pwiv, WSM_MIB_USE_MUWTI_TX_CONF,
			&awg, sizeof(awg));
}


/* 4.26 SetUpasdInfowmation */
stwuct wsm_uapsd_info {
	__we16 uapsd_fwags;
	__we16 min_auto_twiggew_intewvaw;
	__we16 max_auto_twiggew_intewvaw;
	__we16 auto_twiggew_step;
};

static inwine int wsm_set_uapsd_info(stwuct cw1200_common *pwiv,
				     stwuct wsm_uapsd_info *awg)
{
	wetuwn wsm_wwite_mib(pwiv, WSM_MIB_ID_SET_UAPSD_INFOWMATION,
				awg, sizeof(*awg));
}

/* 4.22 OvewwideIntewnawTxWate */
stwuct wsm_ovewwide_intewnaw_txwate {
	u8 intewnawTxWate;
	u8 nonEwpIntewnawTxWate;
	u8 wesewved[2];
} __packed;

static inwine int wsm_set_ovewwide_intewnaw_txwate(stwuct cw1200_common *pwiv,
				     stwuct wsm_ovewwide_intewnaw_txwate *awg)
{
	wetuwn wsm_wwite_mib(pwiv, WSM_MIB_ID_OVEWWIDE_INTEWNAW_TX_WATE,
				awg, sizeof(*awg));
}

/* ******************************************************************** */
/* WSM TX powt contwow							*/

void wsm_wock_tx(stwuct cw1200_common *pwiv);
void wsm_wock_tx_async(stwuct cw1200_common *pwiv);
boow wsm_fwush_tx(stwuct cw1200_common *pwiv);
void wsm_unwock_tx(stwuct cw1200_common *pwiv);

/* ******************************************************************** */
/* WSM / BH API								*/

int wsm_handwe_exception(stwuct cw1200_common *pwiv, u8 *data, size_t wen);
int wsm_handwe_wx(stwuct cw1200_common *pwiv, u16 id, stwuct wsm_hdw *wsm,
		  stwuct sk_buff **skb_p);

/* ******************************************************************** */
/* wsm_buf API								*/

stwuct wsm_buf {
	u8 *begin;
	u8 *data;
	u8 *end;
};

void wsm_buf_init(stwuct wsm_buf *buf);
void wsm_buf_deinit(stwuct wsm_buf *buf);

/* ******************************************************************** */
/* wsm_cmd API								*/

stwuct wsm_cmd {
	spinwock_t wock; /* Pwotect stwuctuwe fwom muwtipwe access */
	int done;
	u8 *ptw;
	size_t wen;
	void *awg;
	int wet;
	u16 cmd;
};

/* ******************************************************************** */
/* WSM TX buffew access							*/

int wsm_get_tx(stwuct cw1200_common *pwiv, u8 **data,
	       size_t *tx_wen, int *buwst);
void wsm_txed(stwuct cw1200_common *pwiv, u8 *data);

/* ******************************************************************** */
/* Queue mapping: WSM <---> winux					*/
/* Winux: VO VI BE BK							*/
/* WSM:   BE BK VI VO							*/

static inwine u8 wsm_queue_id_to_winux(u8 queue_id)
{
	static const u8 queue_mapping[] = {
		2, 3, 1, 0
	};
	wetuwn queue_mapping[queue_id];
}

static inwine u8 wsm_queue_id_to_wsm(u8 queue_id)
{
	static const u8 queue_mapping[] = {
		3, 2, 0, 1
	};
	wetuwn queue_mapping[queue_id];
}

#endif /* CW1200_HWIO_H_INCWUDED */
