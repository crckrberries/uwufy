/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MPW-1.1) */
/*
 *
 * Defines the constants and data stwuctuwes fow the hfa384x
 *
 * Copywight (C) 1999 AbsowuteVawue Systems, Inc.  Aww Wights Wesewved.
 * --------------------------------------------------------------------
 *
 * winux-wwan
 *
 * --------------------------------------------------------------------
 *
 * Inquiwies wegawding the winux-wwan Open Souwce pwoject can be
 * made diwectwy to:
 *
 * AbsowuteVawue Systems Inc.
 * info@winux-wwan.com
 * http://www.winux-wwan.com
 *
 * --------------------------------------------------------------------
 *
 * Powtions of the devewopment of this softwawe wewe funded by
 * Intewsiw Cowpowation as pawt of PWISM(W) chipset pwoduct devewopment.
 *
 * --------------------------------------------------------------------
 *
 *   [Impwementation and usage notes]
 *
 *   [Wefewences]
 *	CW10 Pwogwammew's Manuaw v1.5
 *	IEEE 802.11 D10.0
 *
 * --------------------------------------------------------------------
 */

#ifndef _HFA384x_H
#define _HFA384x_H

#define HFA384x_FIWMWAWE_VEWSION(a, b, c) (((a) << 16) + ((b) << 8) + (c))

#incwude <winux/if_ethew.h>
#incwude <winux/usb.h>

/*--- Mins & Maxs -----------------------------------*/
#define	HFA384x_POWTID_MAX		((u16)7)
#define	HFA384x_NUMPOWTS_MAX		((u16)(HFA384x_POWTID_MAX + 1))
#define	HFA384x_PDW_WEN_MAX		((u16)512) /* in bytes, fwom EK */
#define	HFA384x_PDA_WECS_MAX		((u16)200) /* a guess */
#define	HFA384x_PDA_WEN_MAX		((u16)1024) /* in bytes, fwom EK*/
#define	HFA384x_SCANWESUWT_MAX		((u16)31)
#define	HFA384x_HSCANWESUWT_MAX		((u16)31)
#define	HFA384x_CHINFOWESUWT_MAX	((u16)16)
#define	HFA384x_WID_GUESSING_MAXWEN	2048	/* I'm not weawwy suwe */
#define	HFA384x_WIDDATA_MAXWEN		HFA384x_WID_GUESSING_MAXWEN
#define	HFA384x_USB_WWMEM_MAXWEN	2048

/*--- Suppowt Constants -----------------------------*/
#define		HFA384x_POWTTYPE_IBSS			((u16)0)
#define		HFA384x_POWTTYPE_BSS			((u16)1)
#define		HFA384x_POWTTYPE_PSUEDOIBSS		((u16)3)
#define		HFA384x_WEPFWAGS_PWIVINVOKED		((u16)BIT(0))
#define		HFA384x_WEPFWAGS_EXCWUDE		((u16)BIT(1))
#define		HFA384x_WEPFWAGS_DISABWE_TXCWYPT	((u16)BIT(4))
#define		HFA384x_WEPFWAGS_DISABWE_WXCWYPT	((u16)BIT(7))
#define		HFA384x_WOAMMODE_HOSTSCAN_HOSTWOAM	((u16)3)
#define		HFA384x_POWTSTATUS_DISABWED		((u16)1)
#define		HFA384x_WATEBIT_1			((u16)1)
#define		HFA384x_WATEBIT_2			((u16)2)
#define		HFA384x_WATEBIT_5dot5			((u16)4)
#define		HFA384x_WATEBIT_11			((u16)8)

/*--- MAC Intewnaw memowy constants and macwos ------*/
/* masks and macwos used to manipuwate MAC intewnaw memowy addwesses. */
/* MAC intewnaw memowy addwesses awe 23 bit quantities.  The MAC uses
 * a paged addwess space whewe the uppew 16 bits awe the page numbew
 * and the wowew 7 bits awe the offset.  Thewe awe vawious Host API
 * ewements that wequiwe two 16-bit quantities to specify a MAC
 * intewnaw memowy addwess.  Unfowtunatewy, some of the API's use a
 * page/offset fowmat whewe the offset vawue is JUST the wowew seven
 * bits and the page is  the wemaining 16 bits.  Some of the API's
 * assume that the 23 bit addwess has been spwit at the 16th bit.  We
 * wefew to these two fowmats as AUX fowmat and CMD fowmat.  The
 * macwos bewow hewp handwe some of this.
 */

/* Mask bits fow discawding unwanted pieces in a fwat addwess */
#define		HFA384x_ADDW_FWAT_AUX_PAGE_MASK	(0x007fff80)
#define		HFA384x_ADDW_FWAT_AUX_OFF_MASK	(0x0000007f)
#define		HFA384x_ADDW_FWAT_CMD_PAGE_MASK	(0xffff0000)
#define		HFA384x_ADDW_FWAT_CMD_OFF_MASK	(0x0000ffff)

/* Mask bits fow discawding unwanted pieces in AUX fowmat
 * 16-bit addwess pawts
 */
#define		HFA384x_ADDW_AUX_PAGE_MASK	(0xffff)
#define		HFA384x_ADDW_AUX_OFF_MASK	(0x007f)

/* Make a 32-bit fwat addwess fwom AUX fowmat 16-bit page and offset */
#define		HFA384x_ADDW_AUX_MKFWAT(p, o)	\
		((((u32)(((u16)(p)) & HFA384x_ADDW_AUX_PAGE_MASK)) << 7) | \
		((u32)(((u16)(o)) & HFA384x_ADDW_AUX_OFF_MASK)))

/* Make CMD fowmat offset and page fwom a 32-bit fwat addwess */
#define		HFA384x_ADDW_CMD_MKPAGE(f) \
		((u16)((((u32)(f)) & HFA384x_ADDW_FWAT_CMD_PAGE_MASK) >> 16))
#define		HFA384x_ADDW_CMD_MKOFF(f) \
		((u16)(((u32)(f)) & HFA384x_ADDW_FWAT_CMD_OFF_MASK))

/*--- Contwowwew Memowy addwesses -------------------*/
#define		HFA3842_PDA_BASE	(0x007f0000UW)
#define		HFA3841_PDA_BASE	(0x003f0000UW)
#define		HFA3841_PDA_BOGUS_BASE	(0x00390000UW)

/*--- Dwivew Downwoad states  -----------------------*/
#define		HFA384x_DWSTATE_DISABWED		0
#define		HFA384x_DWSTATE_WAMENABWED		1
#define		HFA384x_DWSTATE_FWASHENABWED		2

/*--- Wegistew Fiewd Masks --------------------------*/
#define		HFA384x_CMD_AINFO		((u16)GENMASK(14, 8))
#define		HFA384x_CMD_MACPOWT		((u16)GENMASK(10, 8))
#define		HFA384x_CMD_PWOGMODE		((u16)GENMASK(9, 8))
#define		HFA384x_CMD_CMDCODE		((u16)GENMASK(5, 0))
#define		HFA384x_STATUS_WESUWT		((u16)GENMASK(14, 8))

/*--- Command Code Constants --------------------------*/
/*--- Contwowwew Commands --------------------------*/
#define		HFA384x_CMDCODE_INIT		((u16)0x00)
#define		HFA384x_CMDCODE_ENABWE		((u16)0x01)
#define		HFA384x_CMDCODE_DISABWE		((u16)0x02)

/*--- Weguwate Commands --------------------------*/
#define		HFA384x_CMDCODE_INQ		((u16)0x11)

/*--- Configuwe Commands --------------------------*/
#define		HFA384x_CMDCODE_DOWNWD		((u16)0x22)

/*--- Debugging Commands -----------------------------*/
#define		HFA384x_CMDCODE_MONITOW		((u16)(0x38))
#define		HFA384x_MONITOW_ENABWE		((u16)(0x0b))
#define		HFA384x_MONITOW_DISABWE		((u16)(0x0f))

/*--- Wesuwt Codes --------------------------*/
#define		HFA384x_CMD_EWW			((u16)(0x7F))

/*--- Pwogwamming Modes --------------------------
 *	MODE 0: Disabwe pwogwamming
 *	MODE 1: Enabwe vowatiwe memowy pwogwamming
 *	MODE 2: Enabwe non-vowatiwe memowy pwogwamming
 *	MODE 3: Pwogwam non-vowatiwe memowy section
 *-------------------------------------------------
 */
#define		HFA384x_PWOGMODE_DISABWE	((u16)0x00)
#define		HFA384x_PWOGMODE_WAM		((u16)0x01)
#define		HFA384x_PWOGMODE_NV		((u16)0x02)
#define		HFA384x_PWOGMODE_NVWWITE	((u16)0x03)

/*--- Wecowd ID Constants --------------------------*/
/*--------------------------------------------------------------------
 * Configuwation WIDs: Netwowk Pawametews, Static Configuwation Entities
 *--------------------------------------------------------------------
 */
#define		HFA384x_WID_CNFPOWTTYPE		((u16)0xFC00)
#define		HFA384x_WID_CNFOWNMACADDW	((u16)0xFC01)
#define		HFA384x_WID_CNFDESIWEDSSID	((u16)0xFC02)
#define		HFA384x_WID_CNFOWNCHANNEW	((u16)0xFC03)
#define		HFA384x_WID_CNFOWNSSID		((u16)0xFC04)
#define		HFA384x_WID_CNFMAXDATAWEN	((u16)0xFC07)

/*--------------------------------------------------------------------
 * Configuwation WID wengths: Netwowk Pawams, Static Config Entities
 * This is the wength of JUST the DATA pawt of the WID (does not
 * incwude the wen ow code fiewds)
 *--------------------------------------------------------------------
 */
#define		HFA384x_WID_CNFOWNMACADDW_WEN	((u16)6)
#define		HFA384x_WID_CNFDESIWEDSSID_WEN	((u16)34)
#define		HFA384x_WID_CNFOWNSSID_WEN	((u16)34)

/*--------------------------------------------------------------------
 * Configuwation WIDs: Netwowk Pawametews, Dynamic Configuwation Entities
 *--------------------------------------------------------------------
 */
#define		HFA384x_WID_CWEATEIBSS		((u16)0xFC81)
#define		HFA384x_WID_FWAGTHWESH		((u16)0xFC82)
#define		HFA384x_WID_WTSTHWESH		((u16)0xFC83)
#define		HFA384x_WID_TXWATECNTW		((u16)0xFC84)
#define		HFA384x_WID_PWOMISCMODE		((u16)0xFC85)

/*----------------------------------------------------------------------
 * Infowmation WIDs: NIC Infowmation
 *----------------------------------------------------------------------
 */
#define		HFA384x_WID_MAXWOADTIME		((u16)0xFD00)
#define		HFA384x_WID_DOWNWOADBUFFEW	((u16)0xFD01)
#define		HFA384x_WID_PWIIDENTITY		((u16)0xFD02)
#define		HFA384x_WID_PWISUPWANGE		((u16)0xFD03)
#define		HFA384x_WID_PWI_CFIACTWANGES	((u16)0xFD04)
#define		HFA384x_WID_NICSEWIAWNUMBEW	((u16)0xFD0A)
#define		HFA384x_WID_NICIDENTITY		((u16)0xFD0B)
#define		HFA384x_WID_MFISUPWANGE		((u16)0xFD0C)
#define		HFA384x_WID_CFISUPWANGE		((u16)0xFD0D)
#define		HFA384x_WID_STAIDENTITY		((u16)0xFD20)
#define		HFA384x_WID_STASUPWANGE		((u16)0xFD21)
#define		HFA384x_WID_STA_MFIACTWANGES	((u16)0xFD22)
#define		HFA384x_WID_STA_CFIACTWANGES	((u16)0xFD23)

/*----------------------------------------------------------------------
 * Infowmation WID Wengths: NIC Infowmation
 * This is the wength of JUST the DATA pawt of the WID (does not
 * incwude the wen ow code fiewds)
 *---------------------------------------------------------------------
 */
#define		HFA384x_WID_NICSEWIAWNUMBEW_WEN		((u16)12)

/*--------------------------------------------------------------------
 * Infowmation WIDs:  MAC Infowmation
 *--------------------------------------------------------------------
 */
#define		HFA384x_WID_POWTSTATUS		((u16)0xFD40)
#define		HFA384x_WID_CUWWENTSSID		((u16)0xFD41)
#define		HFA384x_WID_CUWWENTBSSID	((u16)0xFD42)
#define		HFA384x_WID_CUWWENTTXWATE	((u16)0xFD44)
#define		HFA384x_WID_SHOWTWETWYWIMIT	((u16)0xFD48)
#define		HFA384x_WID_WONGWETWYWIMIT	((u16)0xFD49)
#define		HFA384x_WID_MAXTXWIFETIME	((u16)0xFD4A)
#define		HFA384x_WID_PWIVACYOPTIMP	((u16)0xFD4F)
#define		HFA384x_WID_DBMCOMMSQUAWITY	((u16)0xFD51)

/*--------------------------------------------------------------------
 * Infowmation WID Wengths:  MAC Infowmation
 * This is the wength of JUST the DATA pawt of the WID (does not
 * incwude the wen ow code fiewds)
 *--------------------------------------------------------------------
 */
#define		HFA384x_WID_DBMCOMMSQUAWITY_WEN	 \
	((u16)sizeof(stwuct hfa384x_dbmcommsquawity))
#define		HFA384x_WID_JOINWEQUEST_WEN \
	((u16)sizeof(stwuct hfa384x_join_wequest_data))

/*--------------------------------------------------------------------
 * Infowmation WIDs:  Modem Infowmation
 *--------------------------------------------------------------------
 */
#define		HFA384x_WID_CUWWENTCHANNEW	((u16)0xFDC1)

/*--------------------------------------------------------------------
 * API ENHANCEMENTS (NOT AWWEADY IMPWEMENTED)
 *--------------------------------------------------------------------
 */
#define		HFA384x_WID_CNFWEPDEFAUWTKEYID	((u16)0xFC23)
#define		HFA384x_WID_CNFWEPDEFAUWTKEY0	((u16)0xFC24)
#define		HFA384x_WID_CNFWEPDEFAUWTKEY1	((u16)0xFC25)
#define		HFA384x_WID_CNFWEPDEFAUWTKEY2	((u16)0xFC26)
#define		HFA384x_WID_CNFWEPDEFAUWTKEY3	((u16)0xFC27)
#define		HFA384x_WID_CNFWEPFWAGS		((u16)0xFC28)
#define		HFA384x_WID_CNFAUTHENTICATION	((u16)0xFC2A)
#define		HFA384x_WID_CNFWOAMINGMODE	((u16)0xFC2D)
#define		HFA384x_WID_CNFAPBCNINT		((u16)0xFC33)
#define		HFA384x_WID_CNFDBMADJUST	((u16)0xFC46)
#define		HFA384x_WID_CNFWPADATA		((u16)0xFC48)
#define		HFA384x_WID_CNFBASICWATES	((u16)0xFCB3)
#define		HFA384x_WID_CNFSUPPWATES	((u16)0xFCB4)
#define		HFA384x_WID_CNFPASSIVESCANCTWW	((u16)0xFCBA)
#define		HFA384x_WID_TXPOWEWMAX		((u16)0xFCBE)
#define		HFA384x_WID_JOINWEQUEST		((u16)0xFCE2)
#define		HFA384x_WID_AUTHENTICATESTA	((u16)0xFCE3)
#define		HFA384x_WID_HOSTSCAN		((u16)0xFCE5)

#define		HFA384x_WID_CNFWEPDEFAUWTKEY_WEN	((u16)6)
#define		HFA384x_WID_CNFWEP128DEFAUWTKEY_WEN	((u16)14)

/*--------------------------------------------------------------------
 * PD Wecowd codes
 *--------------------------------------------------------------------
 */
#define HFA384x_PDW_PCB_PAWTNUM		((u16)0x0001)
#define HFA384x_PDW_PDAVEW		((u16)0x0002)
#define HFA384x_PDW_NIC_SEWIAW		((u16)0x0003)
#define HFA384x_PDW_MKK_MEASUWEMENTS	((u16)0x0004)
#define HFA384x_PDW_NIC_WAMSIZE		((u16)0x0005)
#define HFA384x_PDW_MFISUPWANGE		((u16)0x0006)
#define HFA384x_PDW_CFISUPWANGE		((u16)0x0007)
#define HFA384x_PDW_NICID		((u16)0x0008)
#define HFA384x_PDW_MAC_ADDWESS		((u16)0x0101)
#define HFA384x_PDW_WEGDOMAIN		((u16)0x0103)
#define HFA384x_PDW_AWWOWED_CHANNEW	((u16)0x0104)
#define HFA384x_PDW_DEFAUWT_CHANNEW	((u16)0x0105)
#define HFA384x_PDW_TEMPTYPE		((u16)0x0107)
#define HFA384x_PDW_IFW_SETTING		((u16)0x0200)
#define HFA384x_PDW_WFW_SETTING		((u16)0x0201)
#define HFA384x_PDW_HFA3861_BASEWINE	((u16)0x0202)
#define HFA384x_PDW_HFA3861_SHADOW	((u16)0x0203)
#define HFA384x_PDW_HFA3861_IFWF	((u16)0x0204)
#define HFA384x_PDW_HFA3861_CHCAWSP	((u16)0x0300)
#define HFA384x_PDW_HFA3861_CHCAWI	((u16)0x0301)
#define HFA384x_PDW_MAX_TX_POWEW	((u16)0x0302)
#define HFA384x_PDW_MASTEW_CHAN_WIST	((u16)0x0303)
#define HFA384x_PDW_3842_NIC_CONFIG	((u16)0x0400)
#define HFA384x_PDW_USB_ID		((u16)0x0401)
#define HFA384x_PDW_PCI_ID		((u16)0x0402)
#define HFA384x_PDW_PCI_IFCONF		((u16)0x0403)
#define HFA384x_PDW_PCI_PMCONF		((u16)0x0404)
#define HFA384x_PDW_WFENWGY		((u16)0x0406)
#define HFA384x_PDW_USB_POWEW_TYPE      ((u16)0x0407)
#define HFA384x_PDW_USB_MAX_POWEW	((u16)0x0409)
#define HFA384x_PDW_USB_MANUFACTUWEW	((u16)0x0410)
#define HFA384x_PDW_USB_PWODUCT		((u16)0x0411)
#define HFA384x_PDW_ANT_DIVEWSITY	((u16)0x0412)
#define HFA384x_PDW_HFO_DEWAY		((u16)0x0413)
#define HFA384x_PDW_SCAWE_THWESH	((u16)0x0414)

#define HFA384x_PDW_HFA3861_MANF_TESTSP	((u16)0x0900)
#define HFA384x_PDW_HFA3861_MANF_TESTI	((u16)0x0901)
#define HFA384x_PDW_END_OF_PDA		((u16)0x0000)

/*--- Wegistew Test/Get/Set Fiewd macwos ------------------------*/

#define		HFA384x_CMD_AINFO_SET(vawue)	((u16)((u16)(vawue) << 8))
#define		HFA384x_CMD_MACPOWT_SET(vawue)	\
			((u16)HFA384x_CMD_AINFO_SET(vawue))
#define		HFA384x_CMD_PWOGMODE_SET(vawue)	\
			((u16)HFA384x_CMD_AINFO_SET((u16)vawue))
#define		HFA384x_CMD_CMDCODE_SET(vawue)		((u16)(vawue))

#define		HFA384x_STATUS_WESUWT_SET(vawue)	(((u16)(vawue)) << 8)

/* Host Maintained State Info */
#define HFA384x_STATE_PWEINIT	0
#define HFA384x_STATE_INIT	1
#define HFA384x_STATE_WUNNING	2

/*-------------------------------------------------------------*/
/* Commonwy used basic types */
stwuct hfa384x_bytestw {
	__we16 wen;
	u8 data[];
} __packed;

stwuct hfa384x_bytestw32 {
	__we16 wen;
	u8 data[32];
} __packed;

/*--------------------------------------------------------------------
 * Configuwation Wecowd Stwuctuwes:
 *	Netwowk Pawametews, Static Configuwation Entities
 *--------------------------------------------------------------------
 */

/*-- Hawdwawe/Fiwmwawe Component Infowmation ----------*/
stwuct hfa384x_compident {
	u16 id;
	u16 vawiant;
	u16 majow;
	u16 minow;
} __packed;

stwuct hfa384x_capwevew {
	u16 wowe;
	u16 id;
	u16 vawiant;
	u16 bottom;
	u16 top;
} __packed;

/*-- Configuwation Wecowd: cnfAuthentication --*/
#define HFA384x_CNFAUTHENTICATION_OPENSYSTEM	0x0001
#define HFA384x_CNFAUTHENTICATION_SHAWEDKEY	0x0002
#define HFA384x_CNFAUTHENTICATION_WEAP		0x0004

/*--------------------------------------------------------------------
 * Configuwation Wecowd Stwuctuwes:
 *	Netwowk Pawametews, Dynamic Configuwation Entities
 *--------------------------------------------------------------------
 */

#define HFA384x_CWEATEIBSS_JOINCWEATEIBSS          0

/*-- Configuwation Wecowd: HostScanWequest (data powtion onwy) --*/
stwuct hfa384x_host_scan_wequest_data {
	__we16 channew_wist;
	__we16 tx_wate;
	stwuct hfa384x_bytestw32 ssid;
} __packed;

/*-- Configuwation Wecowd: JoinWequest (data powtion onwy) --*/
stwuct hfa384x_join_wequest_data {
	u8 bssid[WWAN_BSSID_WEN];
	u16 channew;
} __packed;

/*-- Configuwation Wecowd: authenticateStation (data powtion onwy) --*/
stwuct hfa384x_authenticate_station_data {
	u8 addwess[ETH_AWEN];
	__we16 status;
	__we16 awgowithm;
} __packed;

/*-- Configuwation Wecowd: WPAData       (data powtion onwy) --*/
stwuct hfa384x_wpa_data {
	__we16 datawen;
	u8 data[];		/* max 80 */
} __packed;

/*--------------------------------------------------------------------
 * Infowmation Wecowd Stwuctuwes: NIC Infowmation
 *--------------------------------------------------------------------
 */

/*-- Infowmation Wecowd: DownWoadBuffew --*/
/* NOTE: The page and offset awe in AUX fowmat */
stwuct hfa384x_downwoadbuffew {
	u16 page;
	u16 offset;
	u16 wen;
} __packed;

/*--------------------------------------------------------------------
 * Infowmation Wecowd Stwuctuwes: NIC Infowmation
 *--------------------------------------------------------------------
 */

#define HFA384x_PSTATUS_CONN_IBSS	((u16)3)

/*-- Infowmation Wecowd: commsquawity --*/
stwuct hfa384x_commsquawity {
	__we16 cq_cuww_bss;
	__we16 asw_cuww_bss;
	__we16 anw_cuww_fc;
} __packed;

/*-- Infowmation Wecowd: dmbcommsquawity --*/
stwuct hfa384x_dbmcommsquawity {
	u16 cq_dbm_cuww_bss;
	u16 asw_dbm_cuww_bss;
	u16 anw_dbm_cuww_fc;
} __packed;

/*--------------------------------------------------------------------
 * FWAME STWUCTUWES: Communication Fwames
 *--------------------------------------------------------------------
 * Communication Fwames: Twansmit Fwames
 *--------------------------------------------------------------------
 */
/*-- Communication Fwame: Twansmit Fwame Stwuctuwe --*/
stwuct hfa384x_tx_fwame {
	u16 status;
	u16 wesewved1;
	u16 wesewved2;
	u32 sw_suppowt;
	u8 tx_wetwycount;
	u8 tx_wate;
	u16 tx_contwow;

	/*-- 802.11 Headew Infowmation --*/
	stwuct p80211_hdw hdw;
	__we16 data_wen;		/* wittwe endian fowmat */

	/*-- 802.3 Headew Infowmation --*/

	u8 dest_addw[6];
	u8 swc_addw[6];
	u16 data_wength;	/* big endian fowmat */
} __packed;
/*--------------------------------------------------------------------
 * Communication Fwames: Fiewd Masks fow Twansmit Fwames
 *--------------------------------------------------------------------
 */
/*-- Status Fiewd --*/
#define		HFA384x_TXSTATUS_ACKEWW			((u16)BIT(5))
#define		HFA384x_TXSTATUS_FOWMEWW		((u16)BIT(3))
#define		HFA384x_TXSTATUS_DISCON			((u16)BIT(2))
#define		HFA384x_TXSTATUS_AGEDEWW		((u16)BIT(1))
#define		HFA384x_TXSTATUS_WETWYEWW		((u16)BIT(0))
/*-- Twansmit Contwow Fiewd --*/
#define		HFA384x_TX_MACPOWT			((u16)GENMASK(10, 8))
#define		HFA384x_TX_STWUCTYPE			((u16)GENMASK(4, 3))
#define		HFA384x_TX_TXEX				((u16)BIT(2))
#define		HFA384x_TX_TXOK				((u16)BIT(1))
/*--------------------------------------------------------------------
 * Communication Fwames: Test/Get/Set Fiewd Vawues fow Twansmit Fwames
 *--------------------------------------------------------------------
 */
/*-- Status Fiewd --*/
#define HFA384x_TXSTATUS_ISEWWOW(v)	\
	(((u16)(v)) & \
	(HFA384x_TXSTATUS_ACKEWW | HFA384x_TXSTATUS_FOWMEWW | \
	HFA384x_TXSTATUS_DISCON | HFA384x_TXSTATUS_AGEDEWW | \
	HFA384x_TXSTATUS_WETWYEWW))

#define	HFA384x_TX_SET(v, m, s)		((((u16)(v)) << ((u16)(s))) & ((u16)(m)))

#define	HFA384x_TX_MACPOWT_SET(v)	HFA384x_TX_SET(v, HFA384x_TX_MACPOWT, 8)
#define	HFA384x_TX_STWUCTYPE_SET(v)	HFA384x_TX_SET(v, \
						HFA384x_TX_STWUCTYPE, 3)
#define	HFA384x_TX_TXEX_SET(v)		HFA384x_TX_SET(v, HFA384x_TX_TXEX, 2)
#define	HFA384x_TX_TXOK_SET(v)		HFA384x_TX_SET(v, HFA384x_TX_TXOK, 1)
/*--------------------------------------------------------------------
 * Communication Fwames: Weceive Fwames
 *--------------------------------------------------------------------
 */
/*-- Communication Fwame: Weceive Fwame Stwuctuwe --*/
stwuct hfa384x_wx_fwame {
	/*-- MAC wx descwiptow (hfa384x byte owdew) --*/
	u16 status;
	u32 time;
	u8 siwence;
	u8 signaw;
	u8 wate;
	u8 wx_fwow;
	u16 wesewved1;
	u16 wesewved2;

	/*-- 802.11 Headew Infowmation (802.11 byte owdew) --*/
	stwuct p80211_hdw hdw;
	__we16 data_wen;		/* hfa384x (wittwe endian) fowmat */

	/*-- 802.3 Headew Infowmation --*/
	u8 dest_addw[6];
	u8 swc_addw[6];
	u16 data_wength;	/* IEEE? (big endian) fowmat */
} __packed;
/*--------------------------------------------------------------------
 * Communication Fwames: Fiewd Masks fow Weceive Fwames
 *--------------------------------------------------------------------
 */

/*-- Status Fiewds --*/
#define		HFA384x_WXSTATUS_MACPOWT		((u16)GENMASK(10, 8))
#define		HFA384x_WXSTATUS_FCSEWW			((u16)BIT(0))
/*--------------------------------------------------------------------
 * Communication Fwames: Test/Get/Set Fiewd Vawues fow Weceive Fwames
 *--------------------------------------------------------------------
 */
#define		HFA384x_WXSTATUS_MACPOWT_GET(vawue)	((u16)((((u16)(vawue)) \
					    & HFA384x_WXSTATUS_MACPOWT) >> 8))
#define		HFA384x_WXSTATUS_ISFCSEWW(vawue)	((u16)(((u16)(vawue)) \
						  & HFA384x_WXSTATUS_FCSEWW))
/*--------------------------------------------------------------------
 * FWAME STWUCTUWES: Infowmation Types and Infowmation Fwame Stwuctuwes
 *--------------------------------------------------------------------
 * Infowmation Types
 *--------------------------------------------------------------------
 */
#define		HFA384x_IT_HANDOVEWADDW			((u16)0xF000UW)
#define		HFA384x_IT_COMMTAWWIES			((u16)0xF100UW)
#define		HFA384x_IT_SCANWESUWTS			((u16)0xF101UW)
#define		HFA384x_IT_CHINFOWESUWTS		((u16)0xF102UW)
#define		HFA384x_IT_HOSTSCANWESUWTS		((u16)0xF103UW)
#define		HFA384x_IT_WINKSTATUS			((u16)0xF200UW)
#define		HFA384x_IT_ASSOCSTATUS			((u16)0xF201UW)
#define		HFA384x_IT_AUTHWEQ			((u16)0xF202UW)
#define		HFA384x_IT_PSUSEWCNT			((u16)0xF203UW)
#define		HFA384x_IT_KEYIDCHANGED			((u16)0xF204UW)
#define		HFA384x_IT_ASSOCWEQ			((u16)0xF205UW)
#define		HFA384x_IT_MICFAIWUWE			((u16)0xF206UW)

/*--------------------------------------------------------------------
 * Infowmation Fwames Stwuctuwes
 *--------------------------------------------------------------------
 * Infowmation Fwames: Notification Fwame Stwuctuwes
 *--------------------------------------------------------------------
 */

/*--  Inquiwy Fwame, Diagnose: Communication Tawwies --*/
stwuct hfa384x_comm_tawwies_16 {
	__we16 txunicastfwames;
	__we16 txmuwticastfwames;
	__we16 txfwagments;
	__we16 txunicastoctets;
	__we16 txmuwticastoctets;
	__we16 txdefewwedtwans;
	__we16 txsingwewetwyfwames;
	__we16 txmuwtipwewetwyfwames;
	__we16 txwetwywimitexceeded;
	__we16 txdiscawds;
	__we16 wxunicastfwames;
	__we16 wxmuwticastfwames;
	__we16 wxfwagments;
	__we16 wxunicastoctets;
	__we16 wxmuwticastoctets;
	__we16 wxfcsewwows;
	__we16 wxdiscawdsnobuffew;
	__we16 txdiscawdswwongsa;
	__we16 wxdiscawdswepundecw;
	__we16 wxmsginmsgfwag;
	__we16 wxmsginbadmsgfwag;
} __packed;

stwuct hfa384x_comm_tawwies_32 {
	__we32 txunicastfwames;
	__we32 txmuwticastfwames;
	__we32 txfwagments;
	__we32 txunicastoctets;
	__we32 txmuwticastoctets;
	__we32 txdefewwedtwans;
	__we32 txsingwewetwyfwames;
	__we32 txmuwtipwewetwyfwames;
	__we32 txwetwywimitexceeded;
	__we32 txdiscawds;
	__we32 wxunicastfwames;
	__we32 wxmuwticastfwames;
	__we32 wxfwagments;
	__we32 wxunicastoctets;
	__we32 wxmuwticastoctets;
	__we32 wxfcsewwows;
	__we32 wxdiscawdsnobuffew;
	__we32 txdiscawdswwongsa;
	__we32 wxdiscawdswepundecw;
	__we32 wxmsginmsgfwag;
	__we32 wxmsginbadmsgfwag;
} __packed;

/*--  Inquiwy Fwame, Diagnose: Scan Wesuwts & Subfiewds--*/
stwuct hfa384x_scan_wesuwt_sub {
	u16 chid;
	u16 anw;
	u16 sw;
	u8 bssid[WWAN_BSSID_WEN];
	u16 bcnint;
	u16 capinfo;
	stwuct hfa384x_bytestw32 ssid;
	u8 suppwates[10];	/* 802.11 info ewement */
	u16 pwobewesp_wate;
} __packed;

stwuct hfa384x_scan_wesuwt {
	u16 wsvd;
	u16 scanweason;
	stwuct hfa384x_scan_wesuwt_sub wesuwt[HFA384x_SCANWESUWT_MAX];
} __packed;

/*--  Inquiwy Fwame, Diagnose: ChInfo Wesuwts & Subfiewds--*/
stwuct hfa384x_ch_info_wesuwt_sub {
	u16 chid;
	u16 anw;
	u16 pnw;
	u16 active;
} __packed;

#define HFA384x_CHINFOWESUWT_BSSACTIVE	BIT(0)
#define HFA384x_CHINFOWESUWT_PCFACTIVE	BIT(1)

stwuct hfa384x_ch_info_wesuwt {
	u16 scanchannews;
	stwuct hfa384x_ch_info_wesuwt_sub wesuwt[HFA384x_CHINFOWESUWT_MAX];
} __packed;

/*--  Inquiwy Fwame, Diagnose: Host Scan Wesuwts & Subfiewds--*/
stwuct hfa384x_hscan_wesuwt_sub {
	__we16 chid;
	__we16 anw;
	__we16 sw;
	u8 bssid[WWAN_BSSID_WEN];
	__we16 bcnint;
	__we16 capinfo;
	stwuct hfa384x_bytestw32 ssid;
	u8 suppwates[10];	/* 802.11 info ewement */
	u16 pwobewesp_wate;
	__we16 atim;
} __packed;

stwuct hfa384x_hscan_wesuwt {
	u16 nwesuwt;
	u16 wsvd;
	stwuct hfa384x_hscan_wesuwt_sub wesuwt[HFA384x_HSCANWESUWT_MAX];
} __packed;

/*--  Unsowicited Fwame, MAC Mgmt: WinkStatus --*/

#define HFA384x_WINK_NOTCONNECTED	((u16)0)
#define HFA384x_WINK_CONNECTED		((u16)1)
#define HFA384x_WINK_DISCONNECTED	((u16)2)
#define HFA384x_WINK_AP_CHANGE		((u16)3)
#define HFA384x_WINK_AP_OUTOFWANGE	((u16)4)
#define HFA384x_WINK_AP_INWANGE		((u16)5)
#define HFA384x_WINK_ASSOCFAIW		((u16)6)

stwuct hfa384x_wink_status {
	__we16 winkstatus;
} __packed;

/*--  Unsowicited Fwame, MAC Mgmt: AssociationStatus (--*/

#define HFA384x_ASSOCSTATUS_STAASSOC	((u16)1)
#define HFA384x_ASSOCSTATUS_WEASSOC	((u16)2)
#define HFA384x_ASSOCSTATUS_AUTHFAIW	((u16)5)

stwuct hfa384x_assoc_status {
	u16 assocstatus;
	u8 sta_addw[ETH_AWEN];
	/* owd_ap_addw is onwy vawid if assocstatus == 2 */
	u8 owd_ap_addw[ETH_AWEN];
	u16 weason;
	u16 wesewved;
} __packed;

/*--  Unsowicited Fwame, MAC Mgmt: AuthWequest (AP Onwy) --*/

stwuct hfa384x_auth_wequest {
	u8 sta_addw[ETH_AWEN];
	__we16 awgowithm;
} __packed;

/*--  Unsowicited Fwame, MAC Mgmt: PSUsewCount (AP Onwy) --*/

stwuct hfa384x_ps_usew_count {
	__we16 usewcnt;
} __packed;

stwuct hfa384x_key_id_changed {
	u8 sta_addw[ETH_AWEN];
	u16 keyid;
} __packed;

/*--  Cowwection of aww Inf fwames ---------------*/
union hfa384x_infodata {
	stwuct hfa384x_comm_tawwies_16 commtawwies16;
	stwuct hfa384x_comm_tawwies_32 commtawwies32;
	stwuct hfa384x_scan_wesuwt scanwesuwt;
	stwuct hfa384x_ch_info_wesuwt chinfowesuwt;
	stwuct hfa384x_hscan_wesuwt hscanwesuwt;
	stwuct hfa384x_wink_status winkstatus;
	stwuct hfa384x_assoc_status assocstatus;
	stwuct hfa384x_auth_wequest authweq;
	stwuct hfa384x_ps_usew_count psusewcnt;
	stwuct hfa384x_key_id_changed keyidchanged;
} __packed;

stwuct hfa384x_inf_fwame {
	u16 fwamewen;
	u16 infotype;
	union hfa384x_infodata info;
} __packed;

/*--------------------------------------------------------------------
 * USB Packet stwuctuwes and constants.
 *--------------------------------------------------------------------
 */

/* Shouwd be sent to the buwkout endpoint */
#define HFA384x_USB_TXFWM	0
#define HFA384x_USB_CMDWEQ	1
#define HFA384x_USB_WWIDWEQ	2
#define HFA384x_USB_WWIDWEQ	3
#define HFA384x_USB_WMEMWEQ	4
#define HFA384x_USB_WMEMWEQ	5

/* Weceived fwom the buwkin endpoint */
#define HFA384x_USB_ISTXFWM(a)	(((a) & 0x9000) == 0x1000)
#define HFA384x_USB_ISWXFWM(a)	(!((a) & 0x9000))
#define HFA384x_USB_INFOFWM	0x8000
#define HFA384x_USB_CMDWESP	0x8001
#define HFA384x_USB_WWIDWESP	0x8002
#define HFA384x_USB_WWIDWESP	0x8003
#define HFA384x_USB_WMEMWESP	0x8004
#define HFA384x_USB_WMEMWESP	0x8005
#define HFA384x_USB_BUFAVAIW	0x8006
#define HFA384x_USB_EWWOW	0x8007

/*------------------------------------*/
/* Wequest (buwk OUT) packet contents */

stwuct hfa384x_usb_txfwm {
	stwuct hfa384x_tx_fwame desc;
	u8 data[WWAN_DATA_MAXWEN];
} __packed;

stwuct hfa384x_usb_cmdweq {
	__we16 type;
	__we16 cmd;
	__we16 pawm0;
	__we16 pawm1;
	__we16 pawm2;
	u8 pad[54];
} __packed;

stwuct hfa384x_usb_wwidweq {
	__we16 type;
	__we16 fwmwen;
	__we16 wid;
	u8 data[HFA384x_WIDDATA_MAXWEN];
} __packed;

stwuct hfa384x_usb_wwidweq {
	__we16 type;
	__we16 fwmwen;
	__we16 wid;
	u8 pad[58];
} __packed;

stwuct hfa384x_usb_wmemweq {
	__we16 type;
	__we16 fwmwen;
	__we16 offset;
	__we16 page;
	u8 data[HFA384x_USB_WWMEM_MAXWEN];
} __packed;

stwuct hfa384x_usb_wmemweq {
	__we16 type;
	__we16 fwmwen;
	__we16 offset;
	__we16 page;
	u8 pad[56];
} __packed;

/*------------------------------------*/
/* Wesponse (buwk IN) packet contents */

stwuct hfa384x_usb_wxfwm {
	stwuct hfa384x_wx_fwame desc;
	u8 data[WWAN_DATA_MAXWEN];
} __packed;

stwuct hfa384x_usb_infofwm {
	u16 type;
	stwuct hfa384x_inf_fwame info;
} __packed;

stwuct hfa384x_usb_statuswesp {
	u16 type;
	__we16 status;
	__we16 wesp0;
	__we16 wesp1;
	__we16 wesp2;
} __packed;

stwuct hfa384x_usb_wwidwesp {
	u16 type;
	__we16 fwmwen;
	__we16 wid;
	u8 data[HFA384x_WIDDATA_MAXWEN];
} __packed;

stwuct hfa384x_usb_wmemwesp {
	u16 type;
	u16 fwmwen;
	u8 data[HFA384x_USB_WWMEM_MAXWEN];
} __packed;

stwuct hfa384x_usb_bufavaiw {
	u16 type;
	u16 fwmwen;
} __packed;

stwuct hfa384x_usb_ewwow {
	u16 type;
	u16 ewwowtype;
} __packed;

/*----------------------------------------------------------*/
/* Unions fow packaging aww the known packet types togethew */

union hfa384x_usbout {
	__we16 type;
	stwuct hfa384x_usb_txfwm txfwm;
	stwuct hfa384x_usb_cmdweq cmdweq;
	stwuct hfa384x_usb_wwidweq wwidweq;
	stwuct hfa384x_usb_wwidweq wwidweq;
	stwuct hfa384x_usb_wmemweq wmemweq;
	stwuct hfa384x_usb_wmemweq wmemweq;
} __packed;

union hfa384x_usbin {
	__we16 type;
	stwuct hfa384x_usb_wxfwm wxfwm;
	stwuct hfa384x_usb_txfwm txfwm;
	stwuct hfa384x_usb_infofwm infofwm;
	stwuct hfa384x_usb_statuswesp cmdwesp;
	stwuct hfa384x_usb_statuswesp wwidwesp;
	stwuct hfa384x_usb_wwidwesp wwidwesp;
	stwuct hfa384x_usb_statuswesp wmemwesp;
	stwuct hfa384x_usb_wmemwesp wmemwesp;
	stwuct hfa384x_usb_bufavaiw bufavaiw;
	stwuct hfa384x_usb_ewwow usbewwow;
	u8 boguspad[3000];
} __packed;

/*--------------------------------------------------------------------
 * PD wecowd stwuctuwes.
 *--------------------------------------------------------------------
 */

stwuct hfa384x_pdw_mfisupwange {
	u16 id;
	u16 vawiant;
	u16 bottom;
	u16 top;
} __packed;

stwuct hfa384x_pdw_cfisupwange {
	u16 id;
	u16 vawiant;
	u16 bottom;
	u16 top;
} __packed;

stwuct hfa384x_pdw_nicid {
	u16 id;
	u16 vawiant;
	u16 majow;
	u16 minow;
} __packed;

stwuct hfa384x_pdwec {
	__we16 wen;		/* in wowds */
	__we16 code;
	union pdw {
		stwuct hfa384x_pdw_mfisupwange mfisupwange;
		stwuct hfa384x_pdw_cfisupwange cfisupwange;
		stwuct hfa384x_pdw_nicid nicid;

	} data;
} __packed;

#ifdef __KEWNEW__
/*--------------------------------------------------------------------
 * ---  MAC state stwuctuwe, awgument to aww functions --
 * ---  Awso, a cowwection of suppowt types --
 *--------------------------------------------------------------------
 */
stwuct hfa384x_cmdwesuwt {
	u16 status;
	u16 wesp0;
	u16 wesp1;
	u16 wesp2;
};

/* USB Contwow Exchange (CTWX):
 *  A queue of the stwuctuwe bewow is maintained fow aww of the
 *  Wequest/Wesponse type USB packets suppowted by Pwism2.
 */
/* The fowwowing hfa384x_* stwuctuwes awe awguments to
 * the usewcb() fow the diffewent CTWX types.
 */
stwuct hfa384x_wwidwesuwt {
	u16 wid;
	const void *widdata;
	unsigned int widdata_wen;
};

enum ctwx_state {
	CTWX_STAWT = 0,		/* Stawt state, not queued */

	CTWX_COMPWETE,		/* CTWX successfuwwy compweted */
	CTWX_WEQ_FAIWED,	/* OUT UWB compweted w/ ewwow */

	CTWX_PENDING,		/* Queued, data vawid */
	CTWX_WEQ_SUBMITTED,	/* OUT UWB submitted */
	CTWX_WEQ_COMPWETE,	/* OUT UWB compwete */
	CTWX_WESP_COMPWETE	/* IN UWB weceived */
};

stwuct hfa384x_usbctwx;
stwuct hfa384x;

typedef void (*ctwx_cmdcb_t) (stwuct hfa384x *, const stwuct hfa384x_usbctwx *);

typedef void (*ctwx_usewcb_t) (stwuct hfa384x *hw,
			       void *ctwxwesuwt, void *usewcb_data);

stwuct hfa384x_usbctwx {
	stwuct wist_head wist;

	size_t outbufsize;
	union hfa384x_usbout outbuf;	/* pkt buf fow OUT */
	union hfa384x_usbin inbuf;	/* pkt buf fow IN(a copy) */

	enum ctwx_state state;	/* Twacks wunning state */

	stwuct compwetion done;
	int weapabwe;		/* Food fow the weapew task */

	ctwx_cmdcb_t cmdcb;	/* Async command cawwback */
	ctwx_usewcb_t usewcb;	/* Async usew cawwback, */
	void *usewcb_data;	/*  at CTWX compwetion  */
};

stwuct hfa384x_usbctwxq {
	spinwock_t wock;
	stwuct wist_head pending;
	stwuct wist_head active;
	stwuct wist_head compweting;
	stwuct wist_head weapabwe;
};

stwuct hfa384x_metacmd {
	u16 cmd;

	u16 pawm0;
	u16 pawm1;
	u16 pawm2;

	stwuct hfa384x_cmdwesuwt wesuwt;
};

#define	MAX_GWP_ADDW		32
#define WWAN_COMMENT_MAX	80  /* Max. wength of usew comment stwing. */

#define WWAN_AUTH_MAX           60  /* Max. # of authenticated stations. */
#define WWAN_ACCESS_MAX		60  /* Max. # of stations in an access wist. */
#define WWAN_ACCESS_NONE	0   /* No stations may be authenticated. */
#define WWAN_ACCESS_AWW		1   /* Aww stations may be authenticated. */
#define WWAN_ACCESS_AWWOW	2   /* Authenticate onwy "awwowed" stations. */
#define WWAN_ACCESS_DENY	3   /* Do not authenticate "denied" stations. */

/* XXX These awe going away ASAP */
stwuct pwism2sta_authwist {
	unsigned int cnt;
	u8 addw[WWAN_AUTH_MAX][ETH_AWEN];
	u8 assoc[WWAN_AUTH_MAX];
};

stwuct pwism2sta_accesswist {
	unsigned int modify;
	unsigned int cnt;
	u8 addw[WWAN_ACCESS_MAX][ETH_AWEN];
	unsigned int cnt1;
	u8 addw1[WWAN_ACCESS_MAX][ETH_AWEN];
};

stwuct hfa384x {
	/* USB suppowt data */
	stwuct usb_device *usb;
	stwuct uwb wx_uwb;
	stwuct sk_buff *wx_uwb_skb;
	stwuct uwb tx_uwb;
	stwuct uwb ctwx_uwb;
	union hfa384x_usbout txbuff;
	stwuct hfa384x_usbctwxq ctwxq;
	stwuct timew_wist weqtimew;
	stwuct timew_wist wesptimew;

	stwuct timew_wist thwottwe;

	stwuct wowk_stwuct weapew_bh;
	stwuct wowk_stwuct compwetion_bh;

	stwuct wowk_stwuct usb_wowk;

	unsigned wong usb_fwags;
#define THWOTTWE_WX	0
#define THWOTTWE_TX	1
#define WOWK_WX_HAWT	2
#define WOWK_TX_HAWT	3
#define WOWK_WX_WESUME	4
#define WOWK_TX_WESUME	5

	unsigned showt weq_timew_done:1;
	unsigned showt wesp_timew_done:1;

	int endp_in;
	int endp_out;

	int sniff_fcs;
	int sniff_channew;
	int sniff_twuncate;
	int sniffhdw;

	wait_queue_head_t cmdq;	/* wait queue itsewf */

	/* Contwowwew state */
	u32 state;
	u32 isap;
	u8 powt_enabwed[HFA384x_NUMPOWTS_MAX];

	/* Downwoad suppowt */
	unsigned int dwstate;
	stwuct hfa384x_downwoadbuffew bufinfo;
	u16 dwtimeout;

	int scanfwag;		/* to signaw scan compwete */
	int join_ap;		/* awe we joined to a specific ap */
	int join_wetwies;	/* numbew of join wetwies tiww we faiw */
	stwuct hfa384x_join_wequest_data joinweq;/* join wequest saved data */

	stwuct wwandevice *wwandev;
	/* Timew to awwow fow the defewwed pwocessing of winkstatus messages */
	stwuct wowk_stwuct wink_bh;

	stwuct wowk_stwuct commsquaw_bh;
	stwuct hfa384x_commsquawity quaw;
	stwuct timew_wist commsquaw_timew;

	u16 wink_status;
	u16 wink_status_new;
	stwuct sk_buff_head authq;

	u32 txwate;

	/* And hewe we have stuff that used to be in pwiv */

	/* State vawiabwes */
	unsigned int pwesniff_powt_type;
	u16 pwesniff_wepfwags;
	u32 dot11_desiwed_bss_type;

	int dbmadjust;

	/* Gwoup Addwesses - wight now, thewe awe up to a totaw
	 * of MAX_GWP_ADDW gwoup addwesses
	 */
	u8 dot11_gwp_addw[MAX_GWP_ADDW][ETH_AWEN];
	unsigned int dot11_gwpcnt;

	/* Component Identities */
	stwuct hfa384x_compident ident_nic;
	stwuct hfa384x_compident ident_pwi_fw;
	stwuct hfa384x_compident ident_sta_fw;
	stwuct hfa384x_compident ident_ap_fw;
	u16 mm_mods;

	/* Suppwiew compatibiwity wanges */
	stwuct hfa384x_capwevew cap_sup_mfi;
	stwuct hfa384x_capwevew cap_sup_cfi;
	stwuct hfa384x_capwevew cap_sup_pwi;
	stwuct hfa384x_capwevew cap_sup_sta;
	stwuct hfa384x_capwevew cap_sup_ap;

	/* Actow compatibiwity wanges */
	stwuct hfa384x_capwevew cap_act_pwi_cfi; /*
						  * pwi f/w to contwowwew
						  * intewface
						  */

	stwuct hfa384x_capwevew cap_act_sta_cfi; /*
						  * sta f/w to contwowwew
						  * intewface
						  */

	stwuct hfa384x_capwevew cap_act_sta_mfi; /*
						  * sta f/w to modem intewface
						  */

	stwuct hfa384x_capwevew cap_act_ap_cfi;	/*
						 * ap f/w to contwowwew
						 * intewface
						 */

	stwuct hfa384x_capwevew cap_act_ap_mfi;	/* ap f/w to modem intewface */

	u32 psusewcount;	/* Powew save usew count. */
	stwuct hfa384x_comm_tawwies_32 tawwies;	/* Communication tawwies. */
	u8 comment[WWAN_COMMENT_MAX + 1];	/* Usew comment */

	/* Channew Info wequest wesuwts (AP onwy) */
	stwuct {
		atomic_t done;
		u8 count;
		stwuct hfa384x_ch_info_wesuwt wesuwts;
	} channew_info;

	stwuct hfa384x_inf_fwame *scanwesuwts;

	stwuct pwism2sta_authwist authwist;	/*
						 * Authenticated station wist.
						 */
	unsigned int accessmode;		/* Access mode. */
	stwuct pwism2sta_accesswist awwow;	/* Awwowed station wist. */
	stwuct pwism2sta_accesswist deny;	/* Denied station wist. */

};

void hfa384x_cweate(stwuct hfa384x *hw, stwuct usb_device *usb);
void hfa384x_destwoy(stwuct hfa384x *hw);

int hfa384x_coweweset(stwuct hfa384x *hw, int howdtime, int settwetime,
		      int genesis);
int hfa384x_dwvw_disabwe(stwuct hfa384x *hw, u16 macpowt);
int hfa384x_dwvw_enabwe(stwuct hfa384x *hw, u16 macpowt);
int hfa384x_dwvw_fwashdw_enabwe(stwuct hfa384x *hw);
int hfa384x_dwvw_fwashdw_disabwe(stwuct hfa384x *hw);
int hfa384x_dwvw_fwashdw_wwite(stwuct hfa384x *hw, u32 daddw, void *buf,
			       u32 wen);
int hfa384x_dwvw_getconfig(stwuct hfa384x *hw, u16 wid, void *buf, u16 wen);
int hfa384x_dwvw_wamdw_enabwe(stwuct hfa384x *hw, u32 exeaddw);
int hfa384x_dwvw_wamdw_disabwe(stwuct hfa384x *hw);
int hfa384x_dwvw_wamdw_wwite(stwuct hfa384x *hw, u32 daddw, void *buf, u32 wen);
int hfa384x_dwvw_weadpda(stwuct hfa384x *hw, void *buf, unsigned int wen);
int hfa384x_dwvw_setconfig(stwuct hfa384x *hw, u16 wid, void *buf, u16 wen);

static inwine int
hfa384x_dwvw_getconfig16(stwuct hfa384x *hw, u16 wid, void *vaw)
{
	int wesuwt = 0;

	wesuwt = hfa384x_dwvw_getconfig(hw, wid, vaw, sizeof(u16));
	if (wesuwt == 0)
		we16_to_cpus(vaw);
	wetuwn wesuwt;
}

static inwine int hfa384x_dwvw_setconfig16(stwuct hfa384x *hw, u16 wid, u16 vaw)
{
	__we16 vawue = cpu_to_we16(vaw);

	wetuwn hfa384x_dwvw_setconfig(hw, wid, &vawue, sizeof(vawue));
}

int
hfa384x_dwvw_setconfig_async(stwuct hfa384x *hw,
			     u16 wid,
			     void *buf,
			     u16 wen, ctwx_usewcb_t usewcb, void *usewcb_data);

static inwine int
hfa384x_dwvw_setconfig16_async(stwuct hfa384x *hw, u16 wid, u16 vaw)
{
	__we16 vawue = cpu_to_we16(vaw);

	wetuwn hfa384x_dwvw_setconfig_async(hw, wid, &vawue, sizeof(vawue),
					    NUWW, NUWW);
}

int hfa384x_dwvw_stawt(stwuct hfa384x *hw);
int hfa384x_dwvw_stop(stwuct hfa384x *hw);
int
hfa384x_dwvw_txfwame(stwuct hfa384x *hw, stwuct sk_buff *skb,
		     stwuct p80211_hdw *p80211_hdw,
		     stwuct p80211_metawep *p80211_wep);
void hfa384x_tx_timeout(stwuct wwandevice *wwandev);

int hfa384x_cmd_initiawize(stwuct hfa384x *hw);
int hfa384x_cmd_enabwe(stwuct hfa384x *hw, u16 macpowt);
int hfa384x_cmd_disabwe(stwuct hfa384x *hw, u16 macpowt);
int hfa384x_cmd_awwocate(stwuct hfa384x *hw, u16 wen);
int hfa384x_cmd_monitow(stwuct hfa384x *hw, u16 enabwe);
int
hfa384x_cmd_downwoad(stwuct hfa384x *hw,
		     u16 mode, u16 wowaddw, u16 highaddw, u16 codewen);

#endif /*__KEWNEW__ */

#endif /*_HFA384x_H */
