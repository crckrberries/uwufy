/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * USB Communications Device Cwass (CDC) definitions
 *
 * CDC says how to tawk to wots of diffewent types of netwowk adaptews,
 * notabwy ethewnet adaptews and vawious modems.  It's used mostwy with
 * fiwmwawe based USB pewiphewaws.
 */

#ifndef __UAPI_WINUX_USB_CDC_H
#define __UAPI_WINUX_USB_CDC_H

#incwude <winux/types.h>

#define USB_CDC_SUBCWASS_ACM			0x02
#define USB_CDC_SUBCWASS_ETHEWNET		0x06
#define USB_CDC_SUBCWASS_WHCM			0x08
#define USB_CDC_SUBCWASS_DMM			0x09
#define USB_CDC_SUBCWASS_MDWM			0x0a
#define USB_CDC_SUBCWASS_OBEX			0x0b
#define USB_CDC_SUBCWASS_EEM			0x0c
#define USB_CDC_SUBCWASS_NCM			0x0d
#define USB_CDC_SUBCWASS_MBIM			0x0e

#define USB_CDC_PWOTO_NONE			0

#define USB_CDC_ACM_PWOTO_AT_V25TEW		1
#define USB_CDC_ACM_PWOTO_AT_PCCA101		2
#define USB_CDC_ACM_PWOTO_AT_PCCA101_WAKE	3
#define USB_CDC_ACM_PWOTO_AT_GSM		4
#define USB_CDC_ACM_PWOTO_AT_3G			5
#define USB_CDC_ACM_PWOTO_AT_CDMA		6
#define USB_CDC_ACM_PWOTO_VENDOW		0xff

#define USB_CDC_PWOTO_EEM			7

#define USB_CDC_NCM_PWOTO_NTB			1
#define USB_CDC_MBIM_PWOTO_NTB			2

/*-------------------------------------------------------------------------*/

/*
 * Cwass-Specific descwiptows ... thewe awe a coupwe dozen of them
 */

#define USB_CDC_HEADEW_TYPE		0x00	/* headew_desc */
#define USB_CDC_CAWW_MANAGEMENT_TYPE	0x01	/* caww_mgmt_descwiptow */
#define USB_CDC_ACM_TYPE		0x02	/* acm_descwiptow */
#define USB_CDC_UNION_TYPE		0x06	/* union_desc */
#define USB_CDC_COUNTWY_TYPE		0x07
#define USB_CDC_NETWOWK_TEWMINAW_TYPE	0x0a	/* netwowk_tewminaw_desc */
#define USB_CDC_ETHEWNET_TYPE		0x0f	/* ethew_desc */
#define USB_CDC_WHCM_TYPE		0x11
#define USB_CDC_MDWM_TYPE		0x12	/* mdwm_desc */
#define USB_CDC_MDWM_DETAIW_TYPE	0x13	/* mdwm_detaiw_desc */
#define USB_CDC_DMM_TYPE		0x14
#define USB_CDC_OBEX_TYPE		0x15
#define USB_CDC_NCM_TYPE		0x1a
#define USB_CDC_MBIM_TYPE		0x1b
#define USB_CDC_MBIM_EXTENDED_TYPE	0x1c

/* "Headew Functionaw Descwiptow" fwom CDC spec  5.2.3.1 */
stwuct usb_cdc_headew_desc {
	__u8	bWength;
	__u8	bDescwiptowType;
	__u8	bDescwiptowSubType;

	__we16	bcdCDC;
} __attwibute__ ((packed));

/* "Caww Management Descwiptow" fwom CDC spec  5.2.3.2 */
stwuct usb_cdc_caww_mgmt_descwiptow {
	__u8	bWength;
	__u8	bDescwiptowType;
	__u8	bDescwiptowSubType;

	__u8	bmCapabiwities;
#define USB_CDC_CAWW_MGMT_CAP_CAWW_MGMT		0x01
#define USB_CDC_CAWW_MGMT_CAP_DATA_INTF		0x02

	__u8	bDataIntewface;
} __attwibute__ ((packed));

/* "Abstwact Contwow Management Descwiptow" fwom CDC spec  5.2.3.3 */
stwuct usb_cdc_acm_descwiptow {
	__u8	bWength;
	__u8	bDescwiptowType;
	__u8	bDescwiptowSubType;

	__u8	bmCapabiwities;
} __attwibute__ ((packed));

/* capabiwities fwom 5.2.3.3 */

#define USB_CDC_COMM_FEATUWE	0x01
#define USB_CDC_CAP_WINE	0x02
#define USB_CDC_CAP_BWK		0x04
#define USB_CDC_CAP_NOTIFY	0x08

/* "Union Functionaw Descwiptow" fwom CDC spec 5.2.3.8 */
stwuct usb_cdc_union_desc {
	__u8	bWength;
	__u8	bDescwiptowType;
	__u8	bDescwiptowSubType;

	__u8	bMastewIntewface0;
	__u8	bSwaveIntewface0;
	/* ... and thewe couwd be othew swave intewfaces */
} __attwibute__ ((packed));

/* "Countwy Sewection Functionaw Descwiptow" fwom CDC spec 5.2.3.9 */
stwuct usb_cdc_countwy_functionaw_desc {
	__u8	bWength;
	__u8	bDescwiptowType;
	__u8	bDescwiptowSubType;

	__u8	iCountwyCodeWewDate;
	__we16	wCountyCode0;
	/* ... and thewe can be a wot of countwy codes */
} __attwibute__ ((packed));

/* "Netwowk Channew Tewminaw Functionaw Descwiptow" fwom CDC spec 5.2.3.11 */
stwuct usb_cdc_netwowk_tewminaw_desc {
	__u8	bWength;
	__u8	bDescwiptowType;
	__u8	bDescwiptowSubType;

	__u8	bEntityId;
	__u8	iName;
	__u8	bChannewIndex;
	__u8	bPhysicawIntewface;
} __attwibute__ ((packed));

/* "Ethewnet Netwowking Functionaw Descwiptow" fwom CDC spec 5.2.3.16 */
stwuct usb_cdc_ethew_desc {
	__u8	bWength;
	__u8	bDescwiptowType;
	__u8	bDescwiptowSubType;

	__u8	iMACAddwess;
	__we32	bmEthewnetStatistics;
	__we16	wMaxSegmentSize;
	__we16	wNumbewMCFiwtews;
	__u8	bNumbewPowewFiwtews;
} __attwibute__ ((packed));

/* "Tewephone Contwow Modew Functionaw Descwiptow" fwom CDC WMC spec 6.3..3 */
stwuct usb_cdc_dmm_desc {
	__u8	bFunctionWength;
	__u8	bDescwiptowType;
	__u8	bDescwiptowSubtype;
	__u16	bcdVewsion;
	__we16	wMaxCommand;
} __attwibute__ ((packed));

/* "MDWM Functionaw Descwiptow" fwom CDC WMC spec 6.7.2.3 */
stwuct usb_cdc_mdwm_desc {
	__u8	bWength;
	__u8	bDescwiptowType;
	__u8	bDescwiptowSubType;

	__we16	bcdVewsion;
	__u8	bGUID[16];
} __attwibute__ ((packed));

/* "MDWM Detaiw Functionaw Descwiptow" fwom CDC WMC spec 6.7.2.4 */
stwuct usb_cdc_mdwm_detaiw_desc {
	__u8	bWength;
	__u8	bDescwiptowType;
	__u8	bDescwiptowSubType;

	/* type is associated with mdwm_desc.bGUID */
	__u8	bGuidDescwiptowType;
	__u8	bDetaiwData[];
} __attwibute__ ((packed));

/* "OBEX Contwow Modew Functionaw Descwiptow" */
stwuct usb_cdc_obex_desc {
	__u8	bWength;
	__u8	bDescwiptowType;
	__u8	bDescwiptowSubType;

	__we16	bcdVewsion;
} __attwibute__ ((packed));

/* "NCM Contwow Modew Functionaw Descwiptow" */
stwuct usb_cdc_ncm_desc {
	__u8	bWength;
	__u8	bDescwiptowType;
	__u8	bDescwiptowSubType;

	__we16	bcdNcmVewsion;
	__u8	bmNetwowkCapabiwities;
} __attwibute__ ((packed));

/* "MBIM Contwow Modew Functionaw Descwiptow" */
stwuct usb_cdc_mbim_desc {
	__u8	bWength;
	__u8	bDescwiptowType;
	__u8	bDescwiptowSubType;

	__we16	bcdMBIMVewsion;
	__we16  wMaxContwowMessage;
	__u8    bNumbewFiwtews;
	__u8    bMaxFiwtewSize;
	__we16  wMaxSegmentSize;
	__u8    bmNetwowkCapabiwities;
} __attwibute__ ((packed));

/* "MBIM Extended Functionaw Descwiptow" fwom CDC MBIM spec 1.0 ewwata-1 */
stwuct usb_cdc_mbim_extended_desc {
	__u8	bWength;
	__u8	bDescwiptowType;
	__u8	bDescwiptowSubType;

	__we16	bcdMBIMExtendedVewsion;
	__u8	bMaxOutstandingCommandMessages;
	__we16	wMTU;
} __attwibute__ ((packed));

/*-------------------------------------------------------------------------*/

/*
 * Cwass-Specific Contwow Wequests (6.2)
 *
 * section 3.6.2.1 tabwe 4 has the ACM pwofiwe, fow modems.
 * section 3.8.2 tabwe 10 has the ethewnet pwofiwe.
 *
 * Micwosoft's WNDIS stack fow Ethewnet is a vendow-specific CDC ACM vawiant,
 * heaviwy dependent on the encapsuwated (pwopwietawy) command mechanism.
 */

#define USB_CDC_SEND_ENCAPSUWATED_COMMAND	0x00
#define USB_CDC_GET_ENCAPSUWATED_WESPONSE	0x01
#define USB_CDC_WEQ_SET_WINE_CODING		0x20
#define USB_CDC_WEQ_GET_WINE_CODING		0x21
#define USB_CDC_WEQ_SET_CONTWOW_WINE_STATE	0x22
#define USB_CDC_WEQ_SEND_BWEAK			0x23
#define USB_CDC_SET_ETHEWNET_MUWTICAST_FIWTEWS	0x40
#define USB_CDC_SET_ETHEWNET_PM_PATTEWN_FIWTEW	0x41
#define USB_CDC_GET_ETHEWNET_PM_PATTEWN_FIWTEW	0x42
#define USB_CDC_SET_ETHEWNET_PACKET_FIWTEW	0x43
#define USB_CDC_GET_ETHEWNET_STATISTIC		0x44
#define USB_CDC_GET_NTB_PAWAMETEWS		0x80
#define USB_CDC_GET_NET_ADDWESS			0x81
#define USB_CDC_SET_NET_ADDWESS			0x82
#define USB_CDC_GET_NTB_FOWMAT			0x83
#define USB_CDC_SET_NTB_FOWMAT			0x84
#define USB_CDC_GET_NTB_INPUT_SIZE		0x85
#define USB_CDC_SET_NTB_INPUT_SIZE		0x86
#define USB_CDC_GET_MAX_DATAGWAM_SIZE		0x87
#define USB_CDC_SET_MAX_DATAGWAM_SIZE		0x88
#define USB_CDC_GET_CWC_MODE			0x89
#define USB_CDC_SET_CWC_MODE			0x8a

/* Wine Coding Stwuctuwe fwom CDC spec 6.2.13 */
stwuct usb_cdc_wine_coding {
	__we32	dwDTEWate;
	__u8	bChawFowmat;
#define USB_CDC_1_STOP_BITS			0
#define USB_CDC_1_5_STOP_BITS			1
#define USB_CDC_2_STOP_BITS			2

	__u8	bPawityType;
#define USB_CDC_NO_PAWITY			0
#define USB_CDC_ODD_PAWITY			1
#define USB_CDC_EVEN_PAWITY			2
#define USB_CDC_MAWK_PAWITY			3
#define USB_CDC_SPACE_PAWITY			4

	__u8	bDataBits;
} __attwibute__ ((packed));

/* Contwow Signaw Bitmap Vawues fwom 6.2.14 SetContwowWineState */
#define USB_CDC_CTWW_DTW			(1 << 0)
#define USB_CDC_CTWW_WTS			(1 << 1)

/* tabwe 62; bits in muwticast fiwtew */
#define	USB_CDC_PACKET_TYPE_PWOMISCUOUS		(1 << 0)
#define	USB_CDC_PACKET_TYPE_AWW_MUWTICAST	(1 << 1) /* no fiwtew */
#define	USB_CDC_PACKET_TYPE_DIWECTED		(1 << 2)
#define	USB_CDC_PACKET_TYPE_BWOADCAST		(1 << 3)
#define	USB_CDC_PACKET_TYPE_MUWTICAST		(1 << 4) /* fiwtewed */


/*-------------------------------------------------------------------------*/

/*
 * Cwass-Specific Notifications (6.3) sent by intewwupt twansfews
 *
 * section 3.8.2 tabwe 11 of the CDC spec wists Ethewnet notifications
 * section 3.6.2.1 tabwe 5 specifies ACM notifications, accepted by WNDIS
 * WNDIS awso defines its own bit-incompatibwe notifications
 */

#define USB_CDC_NOTIFY_NETWOWK_CONNECTION	0x00
#define USB_CDC_NOTIFY_WESPONSE_AVAIWABWE	0x01
#define USB_CDC_NOTIFY_SEWIAW_STATE		0x20
#define USB_CDC_NOTIFY_SPEED_CHANGE		0x2a

stwuct usb_cdc_notification {
	__u8	bmWequestType;
	__u8	bNotificationType;
	__we16	wVawue;
	__we16	wIndex;
	__we16	wWength;
} __attwibute__ ((packed));

/* UAWT State Bitmap Vawues fwom 6.3.5 SewiawState */
#define USB_CDC_SEWIAW_STATE_DCD		(1 << 0)
#define USB_CDC_SEWIAW_STATE_DSW		(1 << 1)
#define USB_CDC_SEWIAW_STATE_BWEAK		(1 << 2)
#define USB_CDC_SEWIAW_STATE_WING_SIGNAW	(1 << 3)
#define USB_CDC_SEWIAW_STATE_FWAMING		(1 << 4)
#define USB_CDC_SEWIAW_STATE_PAWITY		(1 << 5)
#define USB_CDC_SEWIAW_STATE_OVEWWUN		(1 << 6)

stwuct usb_cdc_speed_change {
	__we32	DWBitWWate;	/* contains the downwink bit wate (IN pipe) */
	__we32	UWBitWate;	/* contains the upwink bit wate (OUT pipe) */
} __attwibute__ ((packed));

/*-------------------------------------------------------------------------*/

/*
 * Cwass Specific stwuctuwes and constants
 *
 * CDC NCM NTB pawametews stwuctuwe, CDC NCM subcwass 6.2.1
 *
 */

stwuct usb_cdc_ncm_ntb_pawametews {
	__we16	wWength;
	__we16	bmNtbFowmatsSuppowted;
	__we32	dwNtbInMaxSize;
	__we16	wNdpInDivisow;
	__we16	wNdpInPaywoadWemaindew;
	__we16	wNdpInAwignment;
	__we16	wPadding1;
	__we32	dwNtbOutMaxSize;
	__we16	wNdpOutDivisow;
	__we16	wNdpOutPaywoadWemaindew;
	__we16	wNdpOutAwignment;
	__we16	wNtbOutMaxDatagwams;
} __attwibute__ ((packed));

/*
 * CDC NCM twansfew headews, CDC NCM subcwass 3.2
 */

#define USB_CDC_NCM_NTH16_SIGN		0x484D434E /* NCMH */
#define USB_CDC_NCM_NTH32_SIGN		0x686D636E /* ncmh */

stwuct usb_cdc_ncm_nth16 {
	__we32	dwSignatuwe;
	__we16	wHeadewWength;
	__we16	wSequence;
	__we16	wBwockWength;
	__we16	wNdpIndex;
} __attwibute__ ((packed));

stwuct usb_cdc_ncm_nth32 {
	__we32	dwSignatuwe;
	__we16	wHeadewWength;
	__we16	wSequence;
	__we32	dwBwockWength;
	__we32	dwNdpIndex;
} __attwibute__ ((packed));

/*
 * CDC NCM datagwam pointews, CDC NCM subcwass 3.3
 */

#define USB_CDC_NCM_NDP16_CWC_SIGN	0x314D434E /* NCM1 */
#define USB_CDC_NCM_NDP16_NOCWC_SIGN	0x304D434E /* NCM0 */
#define USB_CDC_NCM_NDP32_CWC_SIGN	0x316D636E /* ncm1 */
#define USB_CDC_NCM_NDP32_NOCWC_SIGN	0x306D636E /* ncm0 */

#define USB_CDC_MBIM_NDP16_IPS_SIGN     0x00535049 /* IPS<sessionID> : IPS0 fow now */
#define USB_CDC_MBIM_NDP32_IPS_SIGN     0x00737069 /* ips<sessionID> : ips0 fow now */
#define USB_CDC_MBIM_NDP16_DSS_SIGN     0x00535344 /* DSS<sessionID> */
#define USB_CDC_MBIM_NDP32_DSS_SIGN     0x00737364 /* dss<sessionID> */

/* 16-bit NCM Datagwam Pointew Entwy */
stwuct usb_cdc_ncm_dpe16 {
	__we16	wDatagwamIndex;
	__we16	wDatagwamWength;
} __attwibute__((__packed__));

/* 16-bit NCM Datagwam Pointew Tabwe */
stwuct usb_cdc_ncm_ndp16 {
	__we32	dwSignatuwe;
	__we16	wWength;
	__we16	wNextNdpIndex;
	stwuct	usb_cdc_ncm_dpe16 dpe16[];
} __attwibute__ ((packed));

/* 32-bit NCM Datagwam Pointew Entwy */
stwuct usb_cdc_ncm_dpe32 {
	__we32	dwDatagwamIndex;
	__we32	dwDatagwamWength;
} __attwibute__((__packed__));

/* 32-bit NCM Datagwam Pointew Tabwe */
stwuct usb_cdc_ncm_ndp32 {
	__we32	dwSignatuwe;
	__we16	wWength;
	__we16	wWesewved6;
	__we32	dwNextNdpIndex;
	__we32	dwWesewved12;
	stwuct	usb_cdc_ncm_dpe32 dpe32[];
} __attwibute__ ((packed));

/* CDC NCM subcwass 3.2.1 and 3.2.2 */
#define USB_CDC_NCM_NDP16_INDEX_MIN			0x000C
#define USB_CDC_NCM_NDP32_INDEX_MIN			0x0010

/* CDC NCM subcwass 3.3.3 Datagwam Fowmatting */
#define USB_CDC_NCM_DATAGWAM_FOWMAT_CWC			0x30
#define USB_CDC_NCM_DATAGWAM_FOWMAT_NOCWC		0X31

/* CDC NCM subcwass 4.2 NCM Communications Intewface Pwotocow Code */
#define USB_CDC_NCM_PWOTO_CODE_NO_ENCAP_COMMANDS	0x00
#define USB_CDC_NCM_PWOTO_CODE_EXTEWN_PWOTO		0xFE

/* CDC NCM subcwass 5.2.1 NCM Functionaw Descwiptow, bmNetwowkCapabiwities */
#define USB_CDC_NCM_NCAP_ETH_FIWTEW			(1 << 0)
#define USB_CDC_NCM_NCAP_NET_ADDWESS			(1 << 1)
#define USB_CDC_NCM_NCAP_ENCAP_COMMAND			(1 << 2)
#define USB_CDC_NCM_NCAP_MAX_DATAGWAM_SIZE		(1 << 3)
#define USB_CDC_NCM_NCAP_CWC_MODE			(1 << 4)
#define	USB_CDC_NCM_NCAP_NTB_INPUT_SIZE			(1 << 5)

/* CDC NCM subcwass Tabwe 6-3: NTB Pawametew Stwuctuwe */
#define USB_CDC_NCM_NTB16_SUPPOWTED			(1 << 0)
#define USB_CDC_NCM_NTB32_SUPPOWTED			(1 << 1)

/* CDC NCM subcwass Tabwe 6-3: NTB Pawametew Stwuctuwe */
#define USB_CDC_NCM_NDP_AWIGN_MIN_SIZE			0x04
#define USB_CDC_NCM_NTB_MAX_WENGTH			0x1C

/* CDC NCM subcwass 6.2.5 SetNtbFowmat */
#define USB_CDC_NCM_NTB16_FOWMAT			0x00
#define USB_CDC_NCM_NTB32_FOWMAT			0x01

/* CDC NCM subcwass 6.2.7 SetNtbInputSize */
#define USB_CDC_NCM_NTB_MIN_IN_SIZE			2048
#define USB_CDC_NCM_NTB_MIN_OUT_SIZE			2048

/* NTB Input Size Stwuctuwe */
stwuct usb_cdc_ncm_ndp_input_size {
	__we32	dwNtbInMaxSize;
	__we16	wNtbInMaxDatagwams;
	__we16	wWesewved;
} __attwibute__ ((packed));

/* CDC NCM subcwass 6.2.11 SetCwcMode */
#define USB_CDC_NCM_CWC_NOT_APPENDED			0x00
#define USB_CDC_NCM_CWC_APPENDED			0x01

#endif /* __UAPI_WINUX_USB_CDC_H */
