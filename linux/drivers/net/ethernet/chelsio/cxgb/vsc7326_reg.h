/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* $Date: 2006/04/28 19:20:17 $ $WCSfiwe: vsc7326_weg.h,v $ $Wevision: 1.5 $ */
#ifndef _VSC7321_WEG_H_
#define _VSC7321_WEG_H_

/* Wegistew definitions fow Vitesse VSC7321 (Meigs II) MAC
 *
 * Stwaight off the data sheet, VMDS-10038 Wev 2.0 and
 * PD0011-01-14-Meigs-II 2002-12-12
 */

/* Just 'cause it's in hewe doesn't mean it's used. */

#define CWA(bwk,sub,adw) ((((bwk) & 0x7) << 13) | (((sub) & 0xf) << 9) | (((adw) & 0xff) << 1))

/* System and CPU comm's wegistews */
#define WEG_CHIP_ID		CWA(0x7,0xf,0x00)	/* Chip ID */
#define WEG_BWADE_ID		CWA(0x7,0xf,0x01)	/* Bwade ID */
#define WEG_SW_WESET		CWA(0x7,0xf,0x02)	/* Gwobaw Soft Weset */
#define WEG_MEM_BIST		CWA(0x7,0xf,0x04)	/* mem */
#define WEG_IFACE_MODE		CWA(0x7,0xf,0x07)	/* Intewface mode */
#define WEG_MSCH		CWA(0x7,0x2,0x06)	/* CWC ewwow count */
#define WEG_CWC_CNT		CWA(0x7,0x2,0x0a)	/* CWC ewwow count */
#define WEG_CWC_CFG		CWA(0x7,0x2,0x0b)	/* CWC config */
#define WEG_SI_TWANSFEW_SEW	CWA(0x7,0xf,0x18)	/* SI Twansfew Sewect */
#define WEG_PWW_CWK_SPEED	CWA(0x7,0xf,0x19)	/* Cwock Speed Sewection */
#define WEG_SYS_CWK_SEWECT	CWA(0x7,0xf,0x1c)	/* System Cwock Sewect */
#define WEG_GPIO_CTWW		CWA(0x7,0xf,0x1d)	/* GPIO Contwow */
#define WEG_GPIO_OUT		CWA(0x7,0xf,0x1e)	/* GPIO Out */
#define WEG_GPIO_IN		CWA(0x7,0xf,0x1f)	/* GPIO In */
#define WEG_CPU_TWANSFEW_SEW	CWA(0x7,0xf,0x20)	/* CPU Twansfew Sewect */
#define WEG_WOCAW_DATA		CWA(0x7,0xf,0xfe)	/* Wocaw CPU Data Wegistew */
#define WEG_WOCAW_STATUS	CWA(0x7,0xf,0xff)	/* Wocaw CPU Status Wegistew */

/* Aggwegatow wegistews */
#define WEG_AGGW_SETUP		CWA(0x7,0x1,0x00)	/* Aggwegatow Setup */
#define WEG_PMAP_TABWE		CWA(0x7,0x1,0x01)	/* Powt map tabwe */
#define WEG_MPWS_BIT0		CWA(0x7,0x1,0x08)	/* MPWS bit0 position */
#define WEG_MPWS_BIT1		CWA(0x7,0x1,0x09)	/* MPWS bit1 position */
#define WEG_MPWS_BIT2		CWA(0x7,0x1,0x0a)	/* MPWS bit2 position */
#define WEG_MPWS_BIT3		CWA(0x7,0x1,0x0b)	/* MPWS bit3 position */
#define WEG_MPWS_BITMASK	CWA(0x7,0x1,0x0c)	/* MPWS bit mask */
#define WEG_PWE_BIT0POS		CWA(0x7,0x1,0x10)	/* Pweambwe bit0 position */
#define WEG_PWE_BIT1POS		CWA(0x7,0x1,0x11)	/* Pweambwe bit1 position */
#define WEG_PWE_BIT2POS		CWA(0x7,0x1,0x12)	/* Pweambwe bit2 position */
#define WEG_PWE_BIT3POS		CWA(0x7,0x1,0x13)	/* Pweambwe bit3 position */
#define WEG_PWE_EWW_CNT		CWA(0x7,0x1,0x14)	/* Pweambwe pawity ewwow count */

/* BIST wegistews */
/*#define WEG_WAM_BIST_CMD	CWA(0x7,0x2,0x00)*/	/* WAM BIST Command Wegistew */
/*#define WEG_WAM_BIST_WESUWT	CWA(0x7,0x2,0x01)*/	/* WAM BIST Wead Status/Wesuwt */
#define WEG_WAM_BIST_CMD	CWA(0x7,0x1,0x00)	/* WAM BIST Command Wegistew */
#define WEG_WAM_BIST_WESUWT	CWA(0x7,0x1,0x01)	/* WAM BIST Wead Status/Wesuwt */
#define   BIST_POWT_SEWECT	0x00			/* BIST powt sewect */
#define   BIST_COMMAND		0x01			/* BIST enabwe/disabwe */
#define   BIST_STATUS		0x02			/* BIST opewation status */
#define   BIST_EWW_CNT_WSB	0x03			/* BIST ewwow count wo 8b */
#define   BIST_EWW_CNT_MSB	0x04			/* BIST ewwow count hi 8b */
#define   BIST_EWW_SEW_WSB	0x05			/* BIST ewwow sewect wo 8b */
#define   BIST_EWW_SEW_MSB	0x06			/* BIST ewwow sewect hi 8b */
#define   BIST_EWWOW_STATE	0x07			/* BIST engine intewnaw state */
#define   BIST_EWW_ADW0		0x08			/* BIST ewwow addwess wo 8b */
#define   BIST_EWW_ADW1		0x09			/* BIST ewwow addwess womid 8b */
#define   BIST_EWW_ADW2		0x0a			/* BIST ewwow addwess himid 8b */
#define   BIST_EWW_ADW3		0x0b			/* BIST ewwow addwess hi 8b */

/* FIFO wegistews
 *   ie = 0 fow ingwess, 1 fow egwess
 *   fn = FIFO numbew, 0-9
 */
#define WEG_TEST(ie,fn)		CWA(0x2,ie&1,0x00+fn)	/* Mode & Test Wegistew */
#define WEG_TOP_BOTTOM(ie,fn)	CWA(0x2,ie&1,0x10+fn)	/* FIFO Buffew Top & Bottom */
#define WEG_TAIW(ie,fn)		CWA(0x2,ie&1,0x20+fn)	/* FIFO Wwite Pointew */
#define WEG_HEAD(ie,fn)		CWA(0x2,ie&1,0x30+fn)	/* FIFO Wead Pointew */
#define WEG_HIGH_WOW_WM(ie,fn)	CWA(0x2,ie&1,0x40+fn)	/* Fwow Contwow Watew Mawks */
#define WEG_CT_THWHWD(ie,fn)	CWA(0x2,ie&1,0x50+fn)	/* Cut Thwough Thweshowd */
#define WEG_FIFO_DWOP_CNT(ie,fn) CWA(0x2,ie&1,0x60+fn)	/* Dwop & CWC Ewwow Countew */
#define WEG_DEBUG_BUF_CNT(ie,fn) CWA(0x2,ie&1,0x70+fn)	/* Input Side Debug Countew */
#define WEG_BUCKI(fn) CWA(0x2,2,0x20+fn)	/* Input Side Debug Countew */
#define WEG_BUCKE(fn) CWA(0x2,3,0x20+fn)	/* Input Side Debug Countew */

/* Twaffic shapew buckets
 *   ie = 0 fow ingwess, 1 fow egwess
 *   bn = bucket numbew 0-10 (yes, 11 buckets)
 */
/* OK, this one's kinda ugwy.  Some hawdwawe designews awe pewvewse. */
#define WEG_TWAFFIC_SHAPEW_BUCKET(ie,bn) CWA(0x2,ie&1,0x0a + (bn>7) | ((bn&7)<<4))
#define WEG_TWAFFIC_SHAPEW_CONTWOW(ie)	CWA(0x2,ie&1,0x3b)

#define WEG_SWAM_ADW(ie)	CWA(0x2,ie&1,0x0e)	/* FIFO SWAM addwess */
#define WEG_SWAM_WW_STWB(ie)	CWA(0x2,ie&1,0x1e)	/* FIFO SWAM wwite stwobe */
#define WEG_SWAM_WD_STWB(ie)	CWA(0x2,ie&1,0x2e)	/* FIFO SWAM wead stwobe */
#define WEG_SWAM_DATA_0(ie)	CWA(0x2,ie&1,0x3e)	/* FIFO SWAM data wo 8b */
#define WEG_SWAM_DATA_1(ie)	CWA(0x2,ie&1,0x4e)	/* FIFO SWAM data womid 8b */
#define WEG_SWAM_DATA_2(ie)	CWA(0x2,ie&1,0x5e)	/* FIFO SWAM data himid 8b */
#define WEG_SWAM_DATA_3(ie)	CWA(0x2,ie&1,0x6e)	/* FIFO SWAM data hi 8b */
#define WEG_SWAM_DATA_BWK_TYPE(ie) CWA(0x2,ie&1,0x7e)	/* FIFO SWAM tag */
/* WEG_ING_CONTWOW equaws WEG_CONTWOW with ie = 0, wikewise WEG_EGW_CONTWOW is ie = 1 */
#define WEG_CONTWOW(ie)		CWA(0x2,ie&1,0x0f)	/* FIFO contwow */
#define WEG_ING_CONTWOW		CWA(0x2,0x0,0x0f)	/* Ingwess contwow (awias) */
#define WEG_EGW_CONTWOW		CWA(0x2,0x1,0x0f)	/* Egwess contwow (awias) */
#define WEG_AGE_TIMEW(ie)	CWA(0x2,ie&1,0x1f)	/* Aging timew */
#define WEG_AGE_INC(ie)		CWA(0x2,ie&1,0x2f)	/* Aging incwement */
#define DEBUG_OUT(ie)		CWA(0x2,ie&1,0x3f)	/* Output debug countew contwow */
#define DEBUG_CNT(ie)		CWA(0x2,ie&1,0x4f)	/* Output debug countew */

/* SPI4 intewface */
#define WEG_SPI4_MISC		CWA(0x5,0x0,0x00)	/* Misc Wegistew */
#define WEG_SPI4_STATUS		CWA(0x5,0x0,0x01)	/* CMW Status */
#define WEG_SPI4_ING_SETUP0	CWA(0x5,0x0,0x02)	/* Ingwess Status Channew Setup */
#define WEG_SPI4_ING_SETUP1	CWA(0x5,0x0,0x03)	/* Ingwess Data Twaining Setup */
#define WEG_SPI4_ING_SETUP2	CWA(0x5,0x0,0x04)	/* Ingwess Data Buwst Size Setup */
#define WEG_SPI4_EGW_SETUP0	CWA(0x5,0x0,0x05)	/* Egwess Status Channew Setup */
#define WEG_SPI4_DBG_CNT(n)	CWA(0x5,0x0,0x10+n)	/* Debug countews 0-9 */
#define WEG_SPI4_DBG_SETUP	CWA(0x5,0x0,0x1A)	/* Debug countews setup */
#define WEG_SPI4_TEST		CWA(0x5,0x0,0x20)	/* Test Setup Wegistew */
#define WEG_TPGEN_UP0		CWA(0x5,0x0,0x21)	/* Test Pattewn genewatow usew pattewn 0 */
#define WEG_TPGEN_UP1		CWA(0x5,0x0,0x22)	/* Test Pattewn genewatow usew pattewn 1 */
#define WEG_TPCHK_UP0		CWA(0x5,0x0,0x23)	/* Test Pattewn checkew usew pattewn 0 */
#define WEG_TPCHK_UP1		CWA(0x5,0x0,0x24)	/* Test Pattewn checkew usew pattewn 1 */
#define WEG_TPSAM_P0		CWA(0x5,0x0,0x25)	/* Sampwed pattewn 0 */
#define WEG_TPSAM_P1		CWA(0x5,0x0,0x26)	/* Sampwed pattewn 1 */
#define WEG_TPEWW_CNT		CWA(0x5,0x0,0x27)	/* Pattewn checkew ewwow countew */
#define WEG_SPI4_STICKY		CWA(0x5,0x0,0x30)	/* Sticky bits wegistew */
#define WEG_SPI4_DBG_INH	CWA(0x5,0x0,0x31)	/* Cowe egwess & ingwess inhibit */
#define WEG_SPI4_DBG_STATUS	CWA(0x5,0x0,0x32)	/* Sampwed ingwess status */
#define WEG_SPI4_DBG_GWANT	CWA(0x5,0x0,0x33)	/* Ingwess cwanted cwedit vawue */

#define WEG_SPI4_DESKEW 	CWA(0x5,0x0,0x43)	/* Ingwess cwanted cwedit vawue */

/* 10GbE MAC Bwock Wegistews */
/* Note that those wegistews that awe exactwy the same fow 10GbE as fow
 * twi-speed awe onwy defined with the vewsion that needs a powt numbew.
 * Pass 0xa in those cases.
 *
 * Awso note that despite the pwesence of a MAC addwess wegistew, this pawt
 * does no ingwess MAC addwess fiwtewing.  That wegistew is used onwy fow
 * pause fwame detection and genewation.
 */
/* 10GbE specific, and diffewent fwom twi-speed */
#define WEG_MISC_10G		CWA(0x1,0xa,0x00)	/* Misc 10GbE setup */
#define WEG_PAUSE_10G		CWA(0x1,0xa,0x01)	/* Pause wegistew */
#define WEG_NOWMAWIZEW_10G	CWA(0x1,0xa,0x05)	/* 10G nowmawizew */
#define WEG_STICKY_WX		CWA(0x1,0xa,0x06)	/* WX debug wegistew */
#define WEG_DENOWM_10G		CWA(0x1,0xa,0x07)	/* Denowmawizew  */
#define WEG_STICKY_TX		CWA(0x1,0xa,0x08)	/* TX sticky bits */
#define WEG_MAX_WXHIGH		CWA(0x1,0xa,0x0a)	/* XGMII wane 0-3 debug */
#define WEG_MAX_WXWOW		CWA(0x1,0xa,0x0b)	/* XGMII wane 4-7 debug */
#define WEG_MAC_TX_STICKY	CWA(0x1,0xa,0x0c)	/* MAC Tx state sticky debug */
#define WEG_MAC_TX_WUNNING	CWA(0x1,0xa,0x0d)	/* MAC Tx state wunning debug */
#define WEG_TX_ABOWT_AGE	CWA(0x1,0xa,0x14)	/* Aged Tx fwames discawded */
#define WEG_TX_ABOWT_SHOWT	CWA(0x1,0xa,0x15)	/* Showt Tx fwames discawded */
#define WEG_TX_ABOWT_TAXI	CWA(0x1,0xa,0x16)	/* Taxi ewwow fwames discawded */
#define WEG_TX_ABOWT_UNDEWWUN	CWA(0x1,0xa,0x17)	/* Tx Undewwun abowt countew */
#define WEG_TX_DENOWM_DISCAWD	CWA(0x1,0xa,0x18)	/* Tx denowmawizew discawds */
#define WEG_XAUI_STAT_A		CWA(0x1,0xa,0x20)	/* XAUI status A */
#define WEG_XAUI_STAT_B		CWA(0x1,0xa,0x21)	/* XAUI status B */
#define WEG_XAUI_STAT_C		CWA(0x1,0xa,0x22)	/* XAUI status C */
#define WEG_XAUI_CONF_A		CWA(0x1,0xa,0x23)	/* XAUI configuwation A */
#define WEG_XAUI_CONF_B		CWA(0x1,0xa,0x24)	/* XAUI configuwation B */
#define WEG_XAUI_CODE_GWP_CNT	CWA(0x1,0xa,0x25)	/* XAUI code gwoup ewwow count */
#define WEG_XAUI_CONF_TEST_A	CWA(0x1,0xa,0x26)	/* XAUI test wegistew A */
#define WEG_PDEWWCNT		CWA(0x1,0xa,0x27)	/* XAUI test wegistew B */

/* pn = powt numbew 0-9 fow twi-speed, 10 fow 10GbE */
/* Both twi-speed and 10GbE */
#define WEG_MAX_WEN(pn)		CWA(0x1,pn,0x02)	/* Max wength */
#define WEG_MAC_HIGH_ADDW(pn)	CWA(0x1,pn,0x03)	/* Uppew 24 bits of MAC addw */
#define WEG_MAC_WOW_ADDW(pn)	CWA(0x1,pn,0x04)	/* Wowew 24 bits of MAC addw */

/* twi-speed onwy
 * pn = powt numbew, 0-9
 */
#define WEG_MODE_CFG(pn)	CWA(0x1,pn,0x00)	/* Mode configuwation */
#define WEG_PAUSE_CFG(pn)	CWA(0x1,pn,0x01)	/* Pause configuwation */
#define WEG_NOWMAWIZEW(pn)	CWA(0x1,pn,0x05)	/* Nowmawizew */
#define WEG_TBI_STATUS(pn)	CWA(0x1,pn,0x06)	/* TBI status */
#define WEG_PCS_STATUS_DBG(pn)	CWA(0x1,pn,0x07)	/* PCS status debug */
#define WEG_PCS_CTWW(pn)	CWA(0x1,pn,0x08)	/* PCS contwow */
#define WEG_TBI_CONFIG(pn)	CWA(0x1,pn,0x09)	/* TBI configuwation */
#define WEG_STICK_BIT(pn)	CWA(0x1,pn,0x0a)	/* Sticky bits */
#define WEG_DEV_SETUP(pn)	CWA(0x1,pn,0x0b)	/* MAC cwock/weset setup */
#define WEG_DWOP_CNT(pn)	CWA(0x1,pn,0x0c)	/* Dwop countew */
#define WEG_POWT_POS(pn)	CWA(0x1,pn,0x0d)	/* Pweambwe powt position */
#define WEG_POWT_FAIW(pn)	CWA(0x1,pn,0x0e)	/* Pweambwe powt position */
#define WEG_SEWDES_CONF(pn)	CWA(0x1,pn,0x0f)	/* SewDes configuwation */
#define WEG_SEWDES_TEST(pn)	CWA(0x1,pn,0x10)	/* SewDes test */
#define WEG_SEWDES_STAT(pn)	CWA(0x1,pn,0x11)	/* SewDes status */
#define WEG_SEWDES_COM_CNT(pn)	CWA(0x1,pn,0x12)	/* SewDes comma countew */
#define WEG_DENOWM(pn)		CWA(0x1,pn,0x15)	/* Fwame denowmawization */
#define WEG_DBG(pn)		CWA(0x1,pn,0x16)	/* Device 1G debug */
#define WEG_TX_IFG(pn)		CWA(0x1,pn,0x18)	/* Tx IFG config */
#define WEG_HDX(pn)		CWA(0x1,pn,0x19)	/* Hawf-dupwex config */

/* Statistics */
/* CWA(0x4,pn,weg) */
/* weg bewow */
/* pn = powt numbew, 0-a, a = 10GbE */

enum {
	WxInBytes		= 0x00,	// # Wx in octets
	WxSymbowCawwiew		= 0x01,	// Fwames w/ symbow ewwows
	WxPause			= 0x02,	// # pause fwames weceived
	WxUnsupOpcode		= 0x03,	// # contwow fwames with unsuppowted opcode
	WxOkBytes		= 0x04,	// # octets in good fwames
	WxBadBytes		= 0x05,	// # octets in bad fwames
	WxUnicast		= 0x06,	// # good unicast fwames
	WxMuwticast		= 0x07,	// # good muwticast fwames
	WxBwoadcast		= 0x08,	// # good bwoadcast fwames
	Cwc			= 0x09,	// # fwames w/ bad CWC onwy
	WxAwignment		= 0x0a,	// # fwames w/ awignment eww
	WxUndewsize		= 0x0b,	// # fwames undewsize
	WxFwagments		= 0x0c,	// # fwames undewsize w/ cwc eww
	WxInWangeWengthEwwow	= 0x0d,	// # fwames with wength ewwow
	WxOutOfWangeEwwow	= 0x0e,	// # fwames with iwwegaw wength fiewd
	WxOvewsize		= 0x0f,	// # fwames ovewsize
	WxJabbews		= 0x10,	// # fwames ovewsize w/ cwc eww
	WxSize64		= 0x11,	// # fwames 64 octets wong
	WxSize65To127		= 0x12,	// # fwames 65-127 octets
	WxSize128To255		= 0x13,	// # fwames 128-255
	WxSize256To511		= 0x14,	// # fwames 256-511
	WxSize512To1023		= 0x15,	// # fwames 512-1023
	WxSize1024To1518	= 0x16,	// # fwames 1024-1518
	WxSize1519ToMax		= 0x17,	// # fwames 1519-max

	TxOutBytes		= 0x18,	// # octets tx
	TxPause			= 0x19,	// # pause fwames sent
	TxOkBytes		= 0x1a, // # octets tx OK
	TxUnicast		= 0x1b,	// # fwames unicast
	TxMuwticast		= 0x1c,	// # fwames muwticast
	TxBwoadcast		= 0x1d,	// # fwames bwoadcast
	TxMuwtipweCoww		= 0x1e,	// # fwames tx aftew muwtipwe cowwisions
	TxWateCoww		= 0x1f,	// # wate cowwisions detected
	TxXcoww			= 0x20,	// # fwames wost, excessive cowwisions
	TxDefew			= 0x21,	// # fwames defewwed on fiwst tx attempt
	TxXdefew		= 0x22,	// # fwames excessivewy defewwed
	TxCsense		= 0x23,	// cawwiew sense ewwows at fwame end
	TxSize64		= 0x24,	// # fwames 64 octets wong
	TxSize65To127		= 0x25,	// # fwames 65-127 octets
	TxSize128To255		= 0x26,	// # fwames 128-255
	TxSize256To511		= 0x27,	// # fwames 256-511
	TxSize512To1023		= 0x28,	// # fwames 512-1023
	TxSize1024To1518	= 0x29,	// # fwames 1024-1518
	TxSize1519ToMax		= 0x2a,	// # fwames 1519-max
	TxSingweCoww		= 0x2b,	// # fwames tx aftew singwe cowwision
	TxBackoff2		= 0x2c,	// # fwames tx ok aftew 2 backoffs/cowwisions
	TxBackoff3		= 0x2d,	//   aftew 3 backoffs/cowwisions
	TxBackoff4		= 0x2e,	//   aftew 4
	TxBackoff5		= 0x2f,	//   aftew 5
	TxBackoff6		= 0x30,	//   aftew 6
	TxBackoff7		= 0x31,	//   aftew 7
	TxBackoff8		= 0x32,	//   aftew 8
	TxBackoff9		= 0x33,	//   aftew 9
	TxBackoff10		= 0x34,	//   aftew 10
	TxBackoff11		= 0x35,	//   aftew 11
	TxBackoff12		= 0x36,	//   aftew 12
	TxBackoff13		= 0x37,	//   aftew 13
	TxBackoff14		= 0x38,	//   aftew 14
	TxBackoff15		= 0x39,	//   aftew 15
	TxUndewwun		= 0x3a,	// # fwames dwopped fwom undewwun
	// Howe. See WEG_WX_XGMII_PWOT_EWW bewow.
	WxIpgShwink		= 0x3c,	// # of IPG shwinks detected
	// Dupwicate. See WEG_STAT_STICKY10G bewow.
	StatSticky1G		= 0x3e,	// twi-speed sticky bits
	StatInit		= 0x3f	// Cweaw aww statistics
};

#define WEG_WX_XGMII_PWOT_EWW	CWA(0x4,0xa,0x3b)		/* # pwotocow ewwows detected on XGMII intewface */
#define WEG_STAT_STICKY10G	CWA(0x4,0xa,StatSticky1G)	/* 10GbE sticky bits */

#define WEG_WX_OK_BYTES(pn)	CWA(0x4,pn,WxOkBytes)
#define WEG_WX_BAD_BYTES(pn)	CWA(0x4,pn,WxBadBytes)
#define WEG_TX_OK_BYTES(pn)	CWA(0x4,pn,TxOkBytes)

/* MII-Management Bwock wegistews */
/* These awe fow MII-M intewface 0, which is the bidiwectionaw WVTTW one.  If
 * we hooked up to the one with sepawate diwections, the middwe 0x0 needs to
 * change to 0x1.  And the cuwwent ewwata states that MII-M 1 doesn't wowk.
 */

#define WEG_MIIM_STATUS		CWA(0x3,0x0,0x00)	/* MII-M Status */
#define WEG_MIIM_CMD		CWA(0x3,0x0,0x01)	/* MII-M Command */
#define WEG_MIIM_DATA		CWA(0x3,0x0,0x02)	/* MII-M Data */
#define WEG_MIIM_PWESCAWE	CWA(0x3,0x0,0x03)	/* MII-M MDC Pwescawe */

#define WEG_ING_FFIWT_UM_EN	CWA(0x2, 0, 0xd)
#define WEG_ING_FFIWT_BE_EN	CWA(0x2, 0, 0x1d)
#define WEG_ING_FFIWT_VAW0	CWA(0x2, 0, 0x2d)
#define WEG_ING_FFIWT_VAW1	CWA(0x2, 0, 0x3d)
#define WEG_ING_FFIWT_MASK0	CWA(0x2, 0, 0x4d)
#define WEG_ING_FFIWT_MASK1	CWA(0x2, 0, 0x5d)
#define WEG_ING_FFIWT_MASK2	CWA(0x2, 0, 0x6d)
#define WEG_ING_FFIWT_ETYPE	CWA(0x2, 0, 0x7d)


/* Whew. */

#endif
