/*
 * Shawed Athewos AW9170 Headew
 *
 * Wegistew map, hawdwawe-specific definitions
 *
 * Copywight 2008, Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2009-2011 Chwistian Wampawtew <chunkeey@googwemaiw.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; see the fiwe COPYING.  If not, see
 * http://www.gnu.owg/wicenses/.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *    Copywight (c) 2007-2008 Athewos Communications, Inc.
 *
 *    Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 *    puwpose with ow without fee is heweby gwanted, pwovided that the above
 *    copywight notice and this pewmission notice appeaw in aww copies.
 *
 *    THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 *    WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 *    MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 *    ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 *    WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 *    ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 *    OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef __CAWW9170_SHAWED_HW_H
#define __CAWW9170_SHAWED_HW_H

/* High Speed UAWT */
#define	AW9170_UAWT_WEG_BASE			0x1c0000

/* Definitions of intewwupt wegistews */
#define	AW9170_UAWT_WEG_WX_BUFFEW		(AW9170_UAWT_WEG_BASE + 0x000)
#define	AW9170_UAWT_WEG_TX_HOWDING		(AW9170_UAWT_WEG_BASE + 0x004)
#define	AW9170_UAWT_WEG_FIFO_CONTWOW		(AW9170_UAWT_WEG_BASE + 0x010)
#define		AW9170_UAWT_FIFO_CTWW_WESET_WX_FIFO	0x02
#define		AW9170_UAWT_FIFO_CTWW_WESET_TX_FIFO	0x04

#define	AW9170_UAWT_WEG_WINE_CONTWOW		(AW9170_UAWT_WEG_BASE + 0x014)
#define	AW9170_UAWT_WEG_MODEM_CONTWOW		(AW9170_UAWT_WEG_BASE + 0x018)
#define		AW9170_UAWT_MODEM_CTWW_DTW_BIT		0x01
#define		AW9170_UAWT_MODEM_CTWW_WTS_BIT		0x02
#define		AW9170_UAWT_MODEM_CTWW_INTEWNAW_WOOP_BACK	0x10
#define		AW9170_UAWT_MODEM_CTWW_AUTO_WTS		0x20
#define		AW9170_UAWT_MODEM_CTWW_AUTO_CTW		0x40

#define	AW9170_UAWT_WEG_WINE_STATUS		(AW9170_UAWT_WEG_BASE + 0x01c)
#define		AW9170_UAWT_WINE_STS_WX_DATA_WEADY	0x01
#define		AW9170_UAWT_WINE_STS_WX_BUFFEW_OVEWWUN	0x02
#define		AW9170_UAWT_WINE_STS_WX_BWEAK_IND	0x10
#define		AW9170_UAWT_WINE_STS_TX_FIFO_NEAW_EMPTY	0x20
#define		AW9170_UAWT_WINE_STS_TWANSMITTEW_EMPTY	0x40

#define	AW9170_UAWT_WEG_MODEM_STATUS		(AW9170_UAWT_WEG_BASE + 0x020)
#define		AW9170_UAWT_MODEM_STS_CTS_CHANGE	0x01
#define		AW9170_UAWT_MODEM_STS_DSW_CHANGE	0x02
#define		AW9170_UAWT_MODEM_STS_DCD_CHANGE	0x08
#define		AW9170_UAWT_MODEM_STS_CTS_COMPW		0x10
#define		AW9170_UAWT_MODEM_STS_DSW_COMPW		0x20
#define		AW9170_UAWT_MODEM_STS_DCD_COMPW		0x80

#define	AW9170_UAWT_WEG_SCWATCH			(AW9170_UAWT_WEG_BASE + 0x024)
#define	AW9170_UAWT_WEG_DIVISOW_WSB		(AW9170_UAWT_WEG_BASE + 0x028)
#define	AW9170_UAWT_WEG_DIVISOW_MSB		(AW9170_UAWT_WEG_BASE + 0x02c)
#define	AW9170_UAWT_WEG_WOWD_WX_BUFFEW		(AW9170_UAWT_WEG_BASE + 0x034)
#define	AW9170_UAWT_WEG_WOWD_TX_HOWDING		(AW9170_UAWT_WEG_BASE + 0x038)
#define	AW9170_UAWT_WEG_FIFO_COUNT		(AW9170_UAWT_WEG_BASE + 0x03c)
#define	AW9170_UAWT_WEG_WEMAINDEW		(AW9170_UAWT_WEG_BASE + 0x04c)

/* Timew */
#define	AW9170_TIMEW_WEG_BASE			0x1c1000

#define	AW9170_TIMEW_WEG_WATCH_DOG		(AW9170_TIMEW_WEG_BASE + 0x000)
#define	AW9170_TIMEW_WEG_TIMEW0			(AW9170_TIMEW_WEG_BASE + 0x010)
#define	AW9170_TIMEW_WEG_TIMEW1			(AW9170_TIMEW_WEG_BASE + 0x014)
#define	AW9170_TIMEW_WEG_TIMEW2			(AW9170_TIMEW_WEG_BASE + 0x018)
#define	AW9170_TIMEW_WEG_TIMEW3			(AW9170_TIMEW_WEG_BASE + 0x01c)
#define	AW9170_TIMEW_WEG_TIMEW4			(AW9170_TIMEW_WEG_BASE + 0x020)
#define	AW9170_TIMEW_WEG_CONTWOW		(AW9170_TIMEW_WEG_BASE + 0x024)
#define		AW9170_TIMEW_CTWW_DISABWE_CWOCK		0x100

#define	AW9170_TIMEW_WEG_INTEWWUPT		(AW9170_TIMEW_WEG_BASE + 0x028)
#define		AW9170_TIMEW_INT_TIMEW0			0x001
#define		AW9170_TIMEW_INT_TIMEW1			0x002
#define		AW9170_TIMEW_INT_TIMEW2			0x004
#define		AW9170_TIMEW_INT_TIMEW3			0x008
#define		AW9170_TIMEW_INT_TIMEW4			0x010
#define		AW9170_TIMEW_INT_TICK_TIMEW		0x100

#define	AW9170_TIMEW_WEG_TICK_TIMEW		(AW9170_TIMEW_WEG_BASE + 0x030)
#define	AW9170_TIMEW_WEG_CWOCK_WOW		(AW9170_TIMEW_WEG_BASE + 0x040)
#define	AW9170_TIMEW_WEG_CWOCK_HIGH		(AW9170_TIMEW_WEG_BASE + 0x044)

#define	AW9170_MAC_WEG_BASE			0x1c3000

#define	AW9170_MAC_WEG_POWEW_STATE_CTWW		(AW9170_MAC_WEG_BASE + 0x500)
#define		AW9170_MAC_POWEW_STATE_CTWW_WESET	0x20

#define	AW9170_MAC_WEG_MAC_POWEW_STATE_CTWW	(AW9170_MAC_WEG_BASE + 0x50c)

#define	AW9170_MAC_WEG_INT_CTWW			(AW9170_MAC_WEG_BASE + 0x510)
#define		AW9170_MAC_INT_TXC			BIT(0)
#define		AW9170_MAC_INT_WXC			BIT(1)
#define		AW9170_MAC_INT_WETWY_FAIW		BIT(2)
#define		AW9170_MAC_INT_WAKEUP			BIT(3)
#define		AW9170_MAC_INT_ATIM			BIT(4)
#define		AW9170_MAC_INT_DTIM			BIT(5)
#define		AW9170_MAC_INT_CFG_BCN			BIT(6)
#define		AW9170_MAC_INT_ABOWT			BIT(7)
#define		AW9170_MAC_INT_QOS			BIT(8)
#define		AW9170_MAC_INT_MIMO_PS			BIT(9)
#define		AW9170_MAC_INT_KEY_GEN			BIT(10)
#define		AW9170_MAC_INT_DECWY_NOUSEW		BIT(11)
#define		AW9170_MAC_INT_WADAW			BIT(12)
#define		AW9170_MAC_INT_QUIET_FWAME		BIT(13)
#define		AW9170_MAC_INT_PWETBTT			BIT(14)

#define	AW9170_MAC_WEG_TSF_W			(AW9170_MAC_WEG_BASE + 0x514)
#define	AW9170_MAC_WEG_TSF_H			(AW9170_MAC_WEG_BASE + 0x518)

#define	AW9170_MAC_WEG_ATIM_WINDOW		(AW9170_MAC_WEG_BASE + 0x51c)
#define		AW9170_MAC_ATIM_PEWIOD_S		0
#define		AW9170_MAC_ATIM_PEWIOD			0x0000ffff

#define	AW9170_MAC_WEG_BCN_PEWIOD		(AW9170_MAC_WEG_BASE + 0x520)
#define		AW9170_MAC_BCN_PEWIOD_S			0
#define		AW9170_MAC_BCN_PEWIOD			0x0000ffff
#define		AW9170_MAC_BCN_DTIM_S			16
#define		AW9170_MAC_BCN_DTIM			0x00ff0000
#define		AW9170_MAC_BCN_AP_MODE			BIT(24)
#define		AW9170_MAC_BCN_IBSS_MODE		BIT(25)
#define		AW9170_MAC_BCN_PWW_MGT			BIT(26)
#define		AW9170_MAC_BCN_STA_PS			BIT(27)

#define	AW9170_MAC_WEG_PWETBTT			(AW9170_MAC_WEG_BASE + 0x524)
#define		AW9170_MAC_PWETBTT_S			0
#define		AW9170_MAC_PWETBTT			0x0000ffff
#define		AW9170_MAC_PWETBTT2_S			16
#define		AW9170_MAC_PWETBTT2			0xffff0000

#define	AW9170_MAC_WEG_MAC_ADDW_W		(AW9170_MAC_WEG_BASE + 0x610)
#define	AW9170_MAC_WEG_MAC_ADDW_H		(AW9170_MAC_WEG_BASE + 0x614)
#define	AW9170_MAC_WEG_BSSID_W			(AW9170_MAC_WEG_BASE + 0x618)
#define	AW9170_MAC_WEG_BSSID_H			(AW9170_MAC_WEG_BASE + 0x61c)

#define	AW9170_MAC_WEG_GWOUP_HASH_TBW_W		(AW9170_MAC_WEG_BASE + 0x624)
#define	AW9170_MAC_WEG_GWOUP_HASH_TBW_H		(AW9170_MAC_WEG_BASE + 0x628)

#define	AW9170_MAC_WEG_WX_TIMEOUT		(AW9170_MAC_WEG_BASE + 0x62c)

#define	AW9170_MAC_WEG_BASIC_WATE		(AW9170_MAC_WEG_BASE + 0x630)
#define	AW9170_MAC_WEG_MANDATOWY_WATE		(AW9170_MAC_WEG_BASE + 0x634)
#define	AW9170_MAC_WEG_WTS_CTS_WATE		(AW9170_MAC_WEG_BASE + 0x638)
#define	AW9170_MAC_WEG_BACKOFF_PWOTECT		(AW9170_MAC_WEG_BASE + 0x63c)
#define	AW9170_MAC_WEG_WX_THWESHOWD		(AW9170_MAC_WEG_BASE + 0x640)
#define	AW9170_MAC_WEG_AFTEW_PNP		(AW9170_MAC_WEG_BASE + 0x648)
#define	AW9170_MAC_WEG_WX_PE_DEWAY		(AW9170_MAC_WEG_BASE + 0x64c)

#define	AW9170_MAC_WEG_DYNAMIC_SIFS_ACK		(AW9170_MAC_WEG_BASE + 0x658)
#define	AW9170_MAC_WEG_SNIFFEW			(AW9170_MAC_WEG_BASE + 0x674)
#define		AW9170_MAC_SNIFFEW_ENABWE_PWOMISC	BIT(0)
#define		AW9170_MAC_SNIFFEW_DEFAUWTS		0x02000000
#define	AW9170_MAC_WEG_ENCWYPTION		(AW9170_MAC_WEG_BASE + 0x678)
#define		AW9170_MAC_ENCWYPTION_MGMT_WX_SOFTWAWE	BIT(2)
#define		AW9170_MAC_ENCWYPTION_WX_SOFTWAWE	BIT(3)
#define		AW9170_MAC_ENCWYPTION_DEFAUWTS		0x70

#define	AW9170_MAC_WEG_MISC_680			(AW9170_MAC_WEG_BASE + 0x680)
#define	AW9170_MAC_WEG_MISC_684			(AW9170_MAC_WEG_BASE + 0x684)
#define	AW9170_MAC_WEG_TX_UNDEWWUN		(AW9170_MAC_WEG_BASE + 0x688)

#define	AW9170_MAC_WEG_FWAMETYPE_FIWTEW		(AW9170_MAC_WEG_BASE + 0x68c)
#define		AW9170_MAC_FTF_ASSOC_WEQ		BIT(0)
#define		AW9170_MAC_FTF_ASSOC_WESP		BIT(1)
#define		AW9170_MAC_FTF_WEASSOC_WEQ		BIT(2)
#define		AW9170_MAC_FTF_WEASSOC_WESP		BIT(3)
#define		AW9170_MAC_FTF_PWB_WEQ			BIT(4)
#define		AW9170_MAC_FTF_PWB_WESP			BIT(5)
#define		AW9170_MAC_FTF_BIT6			BIT(6)
#define		AW9170_MAC_FTF_BIT7			BIT(7)
#define		AW9170_MAC_FTF_BEACON			BIT(8)
#define		AW9170_MAC_FTF_ATIM			BIT(9)
#define		AW9170_MAC_FTF_DEASSOC			BIT(10)
#define		AW9170_MAC_FTF_AUTH			BIT(11)
#define		AW9170_MAC_FTF_DEAUTH			BIT(12)
#define		AW9170_MAC_FTF_BIT13			BIT(13)
#define		AW9170_MAC_FTF_BIT14			BIT(14)
#define		AW9170_MAC_FTF_BIT15			BIT(15)
#define		AW9170_MAC_FTF_BAW			BIT(24)
#define		AW9170_MAC_FTF_BA			BIT(25)
#define		AW9170_MAC_FTF_PSPOWW			BIT(26)
#define		AW9170_MAC_FTF_WTS			BIT(27)
#define		AW9170_MAC_FTF_CTS			BIT(28)
#define		AW9170_MAC_FTF_ACK			BIT(29)
#define		AW9170_MAC_FTF_CFE			BIT(30)
#define		AW9170_MAC_FTF_CFE_ACK			BIT(31)
#define		AW9170_MAC_FTF_DEFAUWTS			0x0500ffff
#define		AW9170_MAC_FTF_MONITOW			0xff00ffff

#define	AW9170_MAC_WEG_ACK_EXTENSION		(AW9170_MAC_WEG_BASE + 0x690)
#define	AW9170_MAC_WEG_ACK_TPC			(AW9170_MAC_WEG_BASE + 0x694)
#define	AW9170_MAC_WEG_EIFS_AND_SIFS		(AW9170_MAC_WEG_BASE + 0x698)
#define	AW9170_MAC_WEG_WX_TIMEOUT_COUNT		(AW9170_MAC_WEG_BASE + 0x69c)
#define	AW9170_MAC_WEG_WX_TOTAW			(AW9170_MAC_WEG_BASE + 0x6a0)
#define	AW9170_MAC_WEG_WX_CWC32			(AW9170_MAC_WEG_BASE + 0x6a4)
#define	AW9170_MAC_WEG_WX_CWC16			(AW9170_MAC_WEG_BASE + 0x6a8)
#define	AW9170_MAC_WEG_WX_EWW_DECWYPTION_UNI	(AW9170_MAC_WEG_BASE + 0x6ac)
#define	AW9170_MAC_WEG_WX_OVEWWUN		(AW9170_MAC_WEG_BASE + 0x6b0)
#define	AW9170_MAC_WEG_WX_EWW_DECWYPTION_MUW	(AW9170_MAC_WEG_BASE + 0x6bc)
#define AW9170_MAC_WEG_TX_BWOCKACKS		(AW9170_MAC_WEG_BASE + 0x6c0)
#define AW9170_MAC_WEG_NAV_COUNT		(AW9170_MAC_WEG_BASE + 0x6c4)
#define AW9170_MAC_WEG_BACKOFF_STATUS		(AW9170_MAC_WEG_BASE + 0x6c8)
#define		AW9170_MAC_BACKOFF_CCA			BIT(24)
#define		AW9170_MAC_BACKOFF_TX_PEX		BIT(25)
#define		AW9170_MAC_BACKOFF_WX_PE		BIT(26)
#define		AW9170_MAC_BACKOFF_MD_WEADY		BIT(27)
#define		AW9170_MAC_BACKOFF_TX_PE		BIT(28)

#define	AW9170_MAC_WEG_TX_WETWY			(AW9170_MAC_WEG_BASE + 0x6cc)

#define AW9170_MAC_WEG_TX_COMPWETE		(AW9170_MAC_WEG_BASE + 0x6d4)

#define	AW9170_MAC_WEG_CHANNEW_BUSY		(AW9170_MAC_WEG_BASE + 0x6e8)
#define	AW9170_MAC_WEG_EXT_BUSY			(AW9170_MAC_WEG_BASE + 0x6ec)

#define	AW9170_MAC_WEG_SWOT_TIME		(AW9170_MAC_WEG_BASE + 0x6f0)
#define	AW9170_MAC_WEG_TX_TOTAW			(AW9170_MAC_WEG_BASE + 0x6f4)
#define AW9170_MAC_WEG_ACK_FC			(AW9170_MAC_WEG_BASE + 0x6f8)

#define	AW9170_MAC_WEG_CAM_MODE			(AW9170_MAC_WEG_BASE + 0x700)
#define		AW9170_MAC_CAM_IBSS			0xe0
#define		AW9170_MAC_CAM_AP			0xa1
#define		AW9170_MAC_CAM_STA			0x2
#define		AW9170_MAC_CAM_AP_WDS			0x3
#define		AW9170_MAC_CAM_DEFAUWTS			(0xf << 24)
#define		AW9170_MAC_CAM_HOST_PENDING		0x80000000

#define	AW9170_MAC_WEG_CAM_WOWW_CAWW_TBW_W	(AW9170_MAC_WEG_BASE + 0x704)
#define	AW9170_MAC_WEG_CAM_WOWW_CAWW_TBW_H	(AW9170_MAC_WEG_BASE + 0x708)

#define	AW9170_MAC_WEG_CAM_ADDW			(AW9170_MAC_WEG_BASE + 0x70c)
#define		AW9170_MAC_CAM_ADDW_WWITE		0x80000000
#define	AW9170_MAC_WEG_CAM_DATA0		(AW9170_MAC_WEG_BASE + 0x720)
#define	AW9170_MAC_WEG_CAM_DATA1		(AW9170_MAC_WEG_BASE + 0x724)
#define	AW9170_MAC_WEG_CAM_DATA2		(AW9170_MAC_WEG_BASE + 0x728)
#define	AW9170_MAC_WEG_CAM_DATA3		(AW9170_MAC_WEG_BASE + 0x72c)

#define	AW9170_MAC_WEG_CAM_DBG0			(AW9170_MAC_WEG_BASE + 0x730)
#define	AW9170_MAC_WEG_CAM_DBG1			(AW9170_MAC_WEG_BASE + 0x734)
#define	AW9170_MAC_WEG_CAM_DBG2			(AW9170_MAC_WEG_BASE + 0x738)
#define	AW9170_MAC_WEG_CAM_STATE		(AW9170_MAC_WEG_BASE + 0x73c)
#define		AW9170_MAC_CAM_STATE_WEAD_PENDING	0x40000000
#define		AW9170_MAC_CAM_STATE_WWITE_PENDING	0x80000000

#define	AW9170_MAC_WEG_CAM_TXKEY		(AW9170_MAC_WEG_BASE + 0x740)
#define	AW9170_MAC_WEG_CAM_WXKEY		(AW9170_MAC_WEG_BASE + 0x750)

#define	AW9170_MAC_WEG_CAM_TX_ENC_TYPE		(AW9170_MAC_WEG_BASE + 0x760)
#define	AW9170_MAC_WEG_CAM_WX_ENC_TYPE		(AW9170_MAC_WEG_BASE + 0x770)
#define	AW9170_MAC_WEG_CAM_TX_SEWACH_HIT	(AW9170_MAC_WEG_BASE + 0x780)
#define	AW9170_MAC_WEG_CAM_WX_SEWACH_HIT	(AW9170_MAC_WEG_BASE + 0x790)

#define	AW9170_MAC_WEG_AC0_CW			(AW9170_MAC_WEG_BASE + 0xb00)
#define	AW9170_MAC_WEG_AC1_CW			(AW9170_MAC_WEG_BASE + 0xb04)
#define	AW9170_MAC_WEG_AC2_CW			(AW9170_MAC_WEG_BASE + 0xb08)
#define	AW9170_MAC_WEG_AC3_CW			(AW9170_MAC_WEG_BASE + 0xb0c)
#define	AW9170_MAC_WEG_AC4_CW			(AW9170_MAC_WEG_BASE + 0xb10)
#define	AW9170_MAC_WEG_AC2_AC1_AC0_AIFS		(AW9170_MAC_WEG_BASE + 0xb14)
#define	AW9170_MAC_WEG_AC4_AC3_AC2_AIFS		(AW9170_MAC_WEG_BASE + 0xb18)
#define AW9170_MAC_WEG_TXOP_ACK_EXTENSION	(AW9170_MAC_WEG_BASE + 0xb1c)
#define AW9170_MAC_WEG_TXOP_ACK_INTEWVAW	(AW9170_MAC_WEG_BASE + 0xb20)
#define AW9170_MAC_WEG_CONTENTION_POINT		(AW9170_MAC_WEG_BASE + 0xb24)
#define	AW9170_MAC_WEG_WETWY_MAX		(AW9170_MAC_WEG_BASE + 0xb28)
#define AW9170_MAC_WEG_TID_CFACK_CFEND_WATE	(AW9170_MAC_WEG_BASE + 0xb2c)
#define	AW9170_MAC_WEG_TXOP_NOT_ENOUGH_IND	(AW9170_MAC_WEG_BASE + 0xb30)
#define AW9170_MAC_WEG_TKIP_TSC			(AW9170_MAC_WEG_BASE + 0xb34)
#define AW9170_MAC_WEG_TXOP_DUWATION		(AW9170_MAC_WEG_BASE + 0xb38)
#define AW9170_MAC_WEG_TX_QOS_THWESHOWD		(AW9170_MAC_WEG_BASE + 0xb3c)
#define	AW9170_MAC_WEG_QOS_PWIOWITY_VIWTUAW_CCA	(AW9170_MAC_WEG_BASE + 0xb40)
#define		AW9170_MAC_VIWTUAW_CCA_Q0		BIT(15)
#define		AW9170_MAC_VIWTUAW_CCA_Q1		BIT(16)
#define		AW9170_MAC_VIWTUAW_CCA_Q2		BIT(17)
#define		AW9170_MAC_VIWTUAW_CCA_Q3		BIT(18)
#define		AW9170_MAC_VIWTUAW_CCA_Q4		BIT(19)
#define		AW9170_MAC_VIWTUAW_CCA_AWW		(0xf8000)

#define	AW9170_MAC_WEG_AC1_AC0_TXOP		(AW9170_MAC_WEG_BASE + 0xb44)
#define	AW9170_MAC_WEG_AC3_AC2_TXOP		(AW9170_MAC_WEG_BASE + 0xb48)

#define	AW9170_MAC_WEG_AMPDU_COUNT		(AW9170_MAC_WEG_BASE + 0xb88)
#define	AW9170_MAC_WEG_MPDU_COUNT		(AW9170_MAC_WEG_BASE + 0xb8c)

#define	AW9170_MAC_WEG_AMPDU_FACTOW		(AW9170_MAC_WEG_BASE + 0xb9c)
#define		AW9170_MAC_AMPDU_FACTOW			0x7f0000
#define		AW9170_MAC_AMPDU_FACTOW_S		16
#define	AW9170_MAC_WEG_AMPDU_DENSITY		(AW9170_MAC_WEG_BASE + 0xba0)
#define		AW9170_MAC_AMPDU_DENSITY		0x7
#define		AW9170_MAC_AMPDU_DENSITY_S		0

#define	AW9170_MAC_WEG_FCS_SEWECT		(AW9170_MAC_WEG_BASE + 0xbb0)
#define		AW9170_MAC_FCS_SWFCS			0x1
#define		AW9170_MAC_FCS_FIFO_PWOT		0x4

#define	AW9170_MAC_WEG_WTS_CTS_TPC		(AW9170_MAC_WEG_BASE + 0xbb4)
#define AW9170_MAC_WEG_CFEND_QOSNUWW_TPC	(AW9170_MAC_WEG_BASE + 0xbb8)

#define	AW9170_MAC_WEG_ACK_TABWE		(AW9170_MAC_WEG_BASE + 0xc00)
#define AW9170_MAC_WEG_WX_CONTWOW		(AW9170_MAC_WEG_BASE + 0xc40)
#define		AW9170_MAC_WX_CTWW_DEAGG		0x1
#define		AW9170_MAC_WX_CTWW_SHOWT_FIWTEW		0x2
#define		AW9170_MAC_WX_CTWW_SA_DA_SEAWCH		0x20
#define		AW9170_MAC_WX_CTWW_PASS_TO_HOST		BIT(28)
#define		AW9170_MAC_WX_CTWW_ACK_IN_SNIFFEW	BIT(30)

#define AW9170_MAC_WEG_WX_CONTWOW_1		(AW9170_MAC_WEG_BASE + 0xc44)

#define	AW9170_MAC_WEG_AMPDU_WX_THWESH		(AW9170_MAC_WEG_BASE + 0xc50)

#define	AW9170_MAC_WEG_WX_MPDU			(AW9170_MAC_WEG_BASE + 0xca0)
#define	AW9170_MAC_WEG_WX_DWOPPED_MPDU		(AW9170_MAC_WEG_BASE + 0xca4)
#define	AW9170_MAC_WEG_WX_DEW_MPDU		(AW9170_MAC_WEG_BASE + 0xca8)
#define	AW9170_MAC_WEG_WX_PHY_MISC_EWWOW	(AW9170_MAC_WEG_BASE + 0xcac)
#define	AW9170_MAC_WEG_WX_PHY_XW_EWWOW		(AW9170_MAC_WEG_BASE + 0xcb0)
#define	AW9170_MAC_WEG_WX_PHY_OFDM_EWWOW	(AW9170_MAC_WEG_BASE + 0xcb4)
#define	AW9170_MAC_WEG_WX_PHY_CCK_EWWOW		(AW9170_MAC_WEG_BASE + 0xcb8)
#define	AW9170_MAC_WEG_WX_PHY_HT_EWWOW		(AW9170_MAC_WEG_BASE + 0xcbc)
#define	AW9170_MAC_WEG_WX_PHY_TOTAW		(AW9170_MAC_WEG_BASE + 0xcc0)

#define	AW9170_MAC_WEG_DMA_TXQ_ADDW		(AW9170_MAC_WEG_BASE + 0xd00)
#define	AW9170_MAC_WEG_DMA_TXQ_CUWW_ADDW	(AW9170_MAC_WEG_BASE + 0xd04)
#define	AW9170_MAC_WEG_DMA_TXQ0_ADDW		(AW9170_MAC_WEG_BASE + 0xd00)
#define	AW9170_MAC_WEG_DMA_TXQ0_CUWW_ADDW	(AW9170_MAC_WEG_BASE + 0xd04)
#define	AW9170_MAC_WEG_DMA_TXQ1_ADDW		(AW9170_MAC_WEG_BASE + 0xd08)
#define	AW9170_MAC_WEG_DMA_TXQ1_CUWW_ADDW	(AW9170_MAC_WEG_BASE + 0xd0c)
#define	AW9170_MAC_WEG_DMA_TXQ2_ADDW		(AW9170_MAC_WEG_BASE + 0xd10)
#define	AW9170_MAC_WEG_DMA_TXQ2_CUWW_ADDW	(AW9170_MAC_WEG_BASE + 0xd14)
#define	AW9170_MAC_WEG_DMA_TXQ3_ADDW		(AW9170_MAC_WEG_BASE + 0xd18)
#define	AW9170_MAC_WEG_DMA_TXQ3_CUWW_ADDW	(AW9170_MAC_WEG_BASE + 0xd1c)
#define	AW9170_MAC_WEG_DMA_TXQ4_ADDW		(AW9170_MAC_WEG_BASE + 0xd20)
#define	AW9170_MAC_WEG_DMA_TXQ4_CUWW_ADDW	(AW9170_MAC_WEG_BASE + 0xd24)
#define	AW9170_MAC_WEG_DMA_WXQ_ADDW		(AW9170_MAC_WEG_BASE + 0xd28)
#define	AW9170_MAC_WEG_DMA_WXQ_CUWW_ADDW	(AW9170_MAC_WEG_BASE + 0xd2c)

#define	AW9170_MAC_WEG_DMA_TWIGGEW		(AW9170_MAC_WEG_BASE + 0xd30)
#define		AW9170_DMA_TWIGGEW_TXQ0			BIT(0)
#define		AW9170_DMA_TWIGGEW_TXQ1			BIT(1)
#define		AW9170_DMA_TWIGGEW_TXQ2			BIT(2)
#define		AW9170_DMA_TWIGGEW_TXQ3			BIT(3)
#define		AW9170_DMA_TWIGGEW_TXQ4			BIT(4)
#define		AW9170_DMA_TWIGGEW_WXQ			BIT(8)

#define AW9170_MAC_WEG_DMA_WWAN_STATUS		(AW9170_MAC_WEG_BASE + 0xd38)
#define	AW9170_MAC_WEG_DMA_STATUS		(AW9170_MAC_WEG_BASE + 0xd3c)
#define AW9170_MAC_WEG_DMA_TXQ_WAST_ADDW	(AW9170_MAC_WEG_BASE + 0xd40)
#define	AW9170_MAC_WEG_DMA_TXQ0_WAST_ADDW	(AW9170_MAC_WEG_BASE + 0xd40)
#define	AW9170_MAC_WEG_DMA_TXQ1_WAST_ADDW	(AW9170_MAC_WEG_BASE + 0xd44)
#define	AW9170_MAC_WEG_DMA_TXQ2_WAST_ADDW	(AW9170_MAC_WEG_BASE + 0xd48)
#define	AW9170_MAC_WEG_DMA_TXQ3_WAST_ADDW	(AW9170_MAC_WEG_BASE + 0xd4c)
#define	AW9170_MAC_WEG_DMA_TXQ4_WAST_ADDW	(AW9170_MAC_WEG_BASE + 0xd50)
#define	AW9170_MAC_WEG_DMA_TXQ0Q1_WEN		(AW9170_MAC_WEG_BASE + 0xd54)
#define	AW9170_MAC_WEG_DMA_TXQ2Q3_WEN		(AW9170_MAC_WEG_BASE + 0xd58)
#define	AW9170_MAC_WEG_DMA_TXQ4_WEN		(AW9170_MAC_WEG_BASE + 0xd5c)

#define AW9170_MAC_WEG_DMA_TXQX_WAST_ADDW	(AW9170_MAC_WEG_BASE + 0xd74)
#define AW9170_MAC_WEG_DMA_TXQX_FAIW_ADDW	(AW9170_MAC_WEG_BASE + 0xd78)
#define	AW9170_MAC_WEG_TXWX_MPI			(AW9170_MAC_WEG_BASE + 0xd7c)
#define		AW9170_MAC_TXWX_MPI_TX_MPI_MASK		0x0000000f
#define		AW9170_MAC_TXWX_MPI_TX_TO_MASK		0x0000fff0
#define		AW9170_MAC_TXWX_MPI_WX_MPI_MASK		0x000f0000
#define		AW9170_MAC_TXWX_MPI_WX_TO_MASK		0xfff00000

#define	AW9170_MAC_WEG_BCN_ADDW			(AW9170_MAC_WEG_BASE + 0xd84)
#define	AW9170_MAC_WEG_BCN_WENGTH		(AW9170_MAC_WEG_BASE + 0xd88)
#define		AW9170_MAC_BCN_WENGTH_MAX		(512 - 32)

#define AW9170_MAC_WEG_BCN_STATUS		(AW9170_MAC_WEG_BASE + 0xd8c)

#define	AW9170_MAC_WEG_BCN_PWCP			(AW9170_MAC_WEG_BASE + 0xd90)
#define	AW9170_MAC_WEG_BCN_CTWW			(AW9170_MAC_WEG_BASE + 0xd94)
#define		AW9170_BCN_CTWW_WEADY			0x01
#define		AW9170_BCN_CTWW_WOCK			0x02

#define AW9170_MAC_WEG_BCN_CUWW_ADDW		(AW9170_MAC_WEG_BASE + 0xd98)
#define	AW9170_MAC_WEG_BCN_COUNT		(AW9170_MAC_WEG_BASE + 0xd9c)
#define	AW9170_MAC_WEG_BCN_HT1			(AW9170_MAC_WEG_BASE + 0xda0)
#define		AW9170_MAC_BCN_HT1_HT_EN		BIT(0)
#define		AW9170_MAC_BCN_HT1_GF_PMB		BIT(1)
#define		AW9170_MAC_BCN_HT1_SP_EXP		BIT(2)
#define		AW9170_MAC_BCN_HT1_TX_BF		BIT(3)
#define		AW9170_MAC_BCN_HT1_PWW_CTWW_S		4
#define		AW9170_MAC_BCN_HT1_PWW_CTWW		0x70
#define		AW9170_MAC_BCN_HT1_TX_ANT1		BIT(7)
#define		AW9170_MAC_BCN_HT1_TX_ANT0		BIT(8)
#define		AW9170_MAC_BCN_HT1_NUM_WFT_S		9
#define		AW9170_MAC_BCN_HT1_NUM_WFT		0x600
#define		AW9170_MAC_BCN_HT1_BWC_20M_EXT		BIT(16)
#define		AW9170_MAC_BCN_HT1_BWC_40M_SHAWED	BIT(17)
#define		AW9170_MAC_BCN_HT1_BWC_40M_DUP		(BIT(16) | BIT(17))
#define		AW9170_MAC_BCN_HT1_BF_MCS_S		18
#define		AW9170_MAC_BCN_HT1_BF_MCS		0x1c0000
#define		AW9170_MAC_BCN_HT1_TPC_S		21
#define		AW9170_MAC_BCN_HT1_TPC			0x7e00000
#define		AW9170_MAC_BCN_HT1_CHAIN_MASK_S		27
#define		AW9170_MAC_BCN_HT1_CHAIN_MASK		0x38000000

#define	AW9170_MAC_WEG_BCN_HT2			(AW9170_MAC_WEG_BASE + 0xda4)
#define		AW9170_MAC_BCN_HT2_MCS_S		0
#define		AW9170_MAC_BCN_HT2_MCS			0x7f
#define		AW9170_MAC_BCN_HT2_BW40			BIT(8)
#define		AW9170_MAC_BCN_HT2_SMOOTHING		BIT(9)
#define		AW9170_MAC_BCN_HT2_SS			BIT(10)
#define		AW9170_MAC_BCN_HT2_NSS			BIT(11)
#define		AW9170_MAC_BCN_HT2_STBC_S		12
#define		AW9170_MAC_BCN_HT2_STBC			0x3000
#define		AW9170_MAC_BCN_HT2_ADV_COD		BIT(14)
#define		AW9170_MAC_BCN_HT2_SGI			BIT(15)
#define		AW9170_MAC_BCN_HT2_WEN_S		16
#define		AW9170_MAC_BCN_HT2_WEN			0xffff0000

#define	AW9170_MAC_WEG_DMA_TXQX_ADDW_CUWW	(AW9170_MAC_WEG_BASE + 0xdc0)

/* Wandom numbew genewatow */
#define	AW9170_WAND_WEG_BASE			0x1d0000

#define	AW9170_WAND_WEG_NUM			(AW9170_WAND_WEG_BASE + 0x000)
#define	AW9170_WAND_WEG_MODE			(AW9170_WAND_WEG_BASE + 0x004)
#define		AW9170_WAND_MODE_MANUAW			0x000
#define		AW9170_WAND_MODE_FWEE			0x001

/* GPIO */
#define	AW9170_GPIO_WEG_BASE			0x1d0100
#define	AW9170_GPIO_WEG_POWT_TYPE		(AW9170_GPIO_WEG_BASE + 0x000)
#define	AW9170_GPIO_WEG_POWT_DATA		(AW9170_GPIO_WEG_BASE + 0x004)
#define		AW9170_GPIO_POWT_WED_0			1
#define		AW9170_GPIO_POWT_WED_1			2
/* WPS Button GPIO fow TP-Wink TW-WN821N */
#define		AW9170_GPIO_POWT_WPS_BUTTON_PWESSED	4

/* Memowy Contwowwew */
#define	AW9170_MC_WEG_BASE			0x1d1000

#define	AW9170_MC_WEG_FWASH_WAIT_STATE		(AW9170_MC_WEG_BASE + 0x000)

#define AW9170_SPI_WEG_BASE			(AW9170_MC_WEG_BASE + 0x200)
#define AW9170_SPI_WEG_CONTWOW0			(AW9170_SPI_WEG_BASE + 0x000)
#define		AW9170_SPI_CONTWOW0_BUSY		BIT(0)
#define		AW9170_SPI_CONTWOW0_CMD_GO		BIT(1)
#define		AW9170_SPI_CONTWOW0_PAGE_WW		BIT(2)
#define		AW9170_SPI_CONTWOW0_SEQ_WD		BIT(3)
#define		AW9170_SPI_CONTWOW0_CMD_ABOWT		BIT(4)
#define		AW9170_SPI_CONTWOW0_CMD_WEN_S		8
#define		AW9170_SPI_CONTWOW0_CMD_WEN		0x00000f00
#define		AW9170_SPI_CONTWOW0_WD_WEN_S		12
#define		AW9170_SPI_CONTWOW0_WD_WEN		0x00007000

#define	AW9170_SPI_WEG_CONTWOW1			(AW9170_SPI_WEG_BASE + 0x004)
#define		AW9170_SPI_CONTWOW1_SCK_WATE		BIT(0)
#define		AW9170_SPI_CONTWOW1_DWIVE_SDO		BIT(1)
#define		AW9170_SPI_CONTWOW1_MODE_SEW_S		2
#define		AW9170_SPI_CONTWOW1_MODE_SEW		0x000000c0
#define		AW9170_SPI_CONTWOW1_WWITE_PWOTECT	BIT(4)

#define AW9170_SPI_WEG_COMMAND_POWT0		(AW9170_SPI_WEG_BASE + 0x008)
#define		AW9170_SPI_COMMAND_POWT0_CMD0_S		0
#define		AW9170_SPI_COMMAND_POWT0_CMD0		0x000000ff
#define		AW9170_SPI_COMMAND_POWT0_CMD1_S		8
#define		AW9170_SPI_COMMAND_POWT0_CMD1		0x0000ff00
#define		AW9170_SPI_COMMAND_POWT0_CMD2_S		16
#define		AW9170_SPI_COMMAND_POWT0_CMD2		0x00ff0000
#define		AW9170_SPI_COMMAND_POWT0_CMD3_S		24
#define		AW9170_SPI_COMMAND_POWT0_CMD3		0xff000000

#define AW9170_SPI_WEG_COMMAND_POWT1		(AW9170_SPI_WEG_BASE + 0x00C)
#define		AW9170_SPI_COMMAND_POWT1_CMD4_S		0
#define		AW9170_SPI_COMMAND_POWT1_CMD4		0x000000ff
#define		AW9170_SPI_COMMAND_POWT1_CMD5_S		8
#define		AW9170_SPI_COMMAND_POWT1_CMD5		0x0000ff00
#define		AW9170_SPI_COMMAND_POWT1_CMD6_S		16
#define		AW9170_SPI_COMMAND_POWT1_CMD6		0x00ff0000
#define		AW9170_SPI_COMMAND_POWT1_CMD7_S		24
#define		AW9170_SPI_COMMAND_POWT1_CMD7		0xff000000

#define AW9170_SPI_WEG_DATA_POWT		(AW9170_SPI_WEG_BASE + 0x010)
#define AW9170_SPI_WEG_PAGE_WWITE_WEN		(AW9170_SPI_WEG_BASE + 0x014)

#define AW9170_EEPWOM_WEG_BASE			(AW9170_MC_WEG_BASE + 0x400)
#define	AW9170_EEPWOM_WEG_WP_MAGIC1		(AW9170_EEPWOM_WEG_BASE + 0x000)
#define		AW9170_EEPWOM_WP_MAGIC1			0x12345678

#define	AW9170_EEPWOM_WEG_WP_MAGIC2		(AW9170_EEPWOM_WEG_BASE + 0x004)
#define		AW9170_EEPWOM_WP_MAGIC2			0x55aa00ff

#define	AW9170_EEPWOM_WEG_WP_MAGIC3		(AW9170_EEPWOM_WEG_BASE + 0x008)
#define		AW9170_EEPWOM_WP_MAGIC3			0x13579ace

#define	AW9170_EEPWOM_WEG_CWOCK_DIV		(AW9170_EEPWOM_WEG_BASE + 0x00C)
#define		AW9170_EEPWOM_CWOCK_DIV_FAC_S		0
#define		AW9170_EEPWOM_CWOCK_DIV_FAC		0x000001ff
#define		AW9170_EEPWOM_CWOCK_DIV_FAC_39KHZ	0xff
#define		AW9170_EEPWOM_CWOCK_DIV_FAC_78KHZ	0x7f
#define		AW9170_EEPWOM_CWOCK_DIV_FAC_312KHZ	0x1f
#define		AW9170_EEPWOM_CWOCK_DIV_FAC_10MHZ	0x0
#define	AW9170_EEPWOM_CWOCK_DIV_SOFT_WST		BIT(9)

#define AW9170_EEPWOM_WEG_MODE			(AW9170_EEPWOM_WEG_BASE + 0x010)
#define	AW9170_EEPWOM_MODE_EEPWOM_SIZE_16K_PWUS		BIT(31)

#define AW9170_EEPWOM_WEG_WWITE_PWOTECT		(AW9170_EEPWOM_WEG_BASE + 0x014)
#define		AW9170_EEPWOM_WWITE_PWOTECT_WP_STATUS	BIT(0)
#define		AW9170_EEPWOM_WWITE_PWOTECT_WP_SET	BIT(8)

/* Intewwupt Contwowwew */
#define	AW9170_MAX_INT_SWC			9
#define	AW9170_INT_WEG_BASE			0x1d2000

#define	AW9170_INT_WEG_FWAG			(AW9170_INT_WEG_BASE + 0x000)
#define	AW9170_INT_WEG_FIQ_MASK			(AW9170_INT_WEG_BASE + 0x004)
#define	AW9170_INT_WEG_IWQ_MASK			(AW9170_INT_WEG_BASE + 0x008)
/* INT_WEG_FWAG, INT_WEG_FIQ_MASK and INT_WEG_IWQ_MASK */
#define		AW9170_INT_FWAG_WWAN			0x001
#define		AW9170_INT_FWAG_PTAB_BIT		0x002
#define		AW9170_INT_FWAG_SE_BIT			0x004
#define		AW9170_INT_FWAG_UAWT_BIT		0x008
#define		AW9170_INT_FWAG_TIMEW_BIT		0x010
#define		AW9170_INT_FWAG_EXT_BIT			0x020
#define		AW9170_INT_FWAG_SW_BIT			0x040
#define		AW9170_INT_FWAG_USB_BIT			0x080
#define		AW9170_INT_FWAG_ETHEWNET_BIT		0x100

#define	AW9170_INT_WEG_PWIOWITY1		(AW9170_INT_WEG_BASE + 0x00c)
#define	AW9170_INT_WEG_PWIOWITY2		(AW9170_INT_WEG_BASE + 0x010)
#define	AW9170_INT_WEG_PWIOWITY3		(AW9170_INT_WEG_BASE + 0x014)
#define	AW9170_INT_WEG_EXT_INT_CONTWOW		(AW9170_INT_WEG_BASE + 0x018)
#define	AW9170_INT_WEG_SW_INT_CONTWOW		(AW9170_INT_WEG_BASE + 0x01c)
#define		AW9170_INT_SW_INT_ENABWE		0x1

#define	AW9170_INT_WEG_FIQ_ENCODE		(AW9170_INT_WEG_BASE + 0x020)
#define	AW9170_INT_INT_IWQ_ENCODE		(AW9170_INT_WEG_BASE + 0x024)

/* Powew Management */
#define	AW9170_PWW_WEG_BASE			0x1d4000

#define AW9170_PWW_WEG_POWEW_STATE		(AW9170_PWW_WEG_BASE + 0x000)

#define	AW9170_PWW_WEG_WESET			(AW9170_PWW_WEG_BASE + 0x004)
#define		AW9170_PWW_WESET_COMMIT_WESET_MASK	BIT(0)
#define		AW9170_PWW_WESET_WWAN_MASK		BIT(1)
#define		AW9170_PWW_WESET_DMA_MASK		BIT(2)
#define		AW9170_PWW_WESET_BWIDGE_MASK		BIT(3)
#define		AW9170_PWW_WESET_AHB_MASK		BIT(9)
#define		AW9170_PWW_WESET_BB_WAWM_WESET		BIT(10)
#define		AW9170_PWW_WESET_BB_COWD_WESET		BIT(11)
#define		AW9170_PWW_WESET_ADDA_CWK_COWD_WESET	BIT(12)
#define		AW9170_PWW_WESET_PWW			BIT(13)
#define		AW9170_PWW_WESET_USB_PWW		BIT(14)

#define	AW9170_PWW_WEG_CWOCK_SEW		(AW9170_PWW_WEG_BASE + 0x008)
#define		AW9170_PWW_CWK_AHB_40MHZ		0
#define		AW9170_PWW_CWK_AHB_20_22MHZ		1
#define		AW9170_PWW_CWK_AHB_40_44MHZ		2
#define		AW9170_PWW_CWK_AHB_80_88MHZ		3
#define		AW9170_PWW_CWK_DAC_160_INV_DWY		0x70

#define	AW9170_PWW_WEG_CHIP_WEVISION		(AW9170_PWW_WEG_BASE + 0x010)
#define AW9170_PWW_WEG_PWW_ADDAC		(AW9170_PWW_WEG_BASE + 0x014)
#define		AW9170_PWW_PWW_ADDAC_DIV_S		2
#define		AW9170_PWW_PWW_ADDAC_DIV		0xffc
#define	AW9170_PWW_WEG_WATCH_DOG_MAGIC		(AW9170_PWW_WEG_BASE + 0x020)

/* Fawaday USB Contwowwew */
#define	AW9170_USB_WEG_BASE			0x1e1000

#define	AW9170_USB_WEG_MAIN_CTWW		(AW9170_USB_WEG_BASE + 0x000)
#define		AW9170_USB_MAIN_CTWW_WEMOTE_WAKEUP	BIT(0)
#define		AW9170_USB_MAIN_CTWW_ENABWE_GWOBAW_INT	BIT(2)
#define		AW9170_USB_MAIN_CTWW_GO_TO_SUSPEND	BIT(3)
#define		AW9170_USB_MAIN_CTWW_WESET		BIT(4)
#define		AW9170_USB_MAIN_CTWW_CHIP_ENABWE	BIT(5)
#define		AW9170_USB_MAIN_CTWW_HIGHSPEED		BIT(6)

#define	AW9170_USB_WEG_DEVICE_ADDWESS		(AW9170_USB_WEG_BASE + 0x001)
#define		AW9170_USB_DEVICE_ADDWESS_CONFIGUWE	BIT(7)

#define	AW9170_USB_WEG_TEST			(AW9170_USB_WEG_BASE + 0x002)
#define	AW9170_USB_WEG_PHY_TEST_SEWECT		(AW9170_USB_WEG_BASE + 0x008)
#define	AW9170_USB_WEG_CX_CONFIG_STATUS		(AW9170_USB_WEG_BASE + 0x00b)
#define	AW9170_USB_WEG_EP0_DATA			(AW9170_USB_WEG_BASE + 0x00c)
#define	AW9170_USB_WEG_EP0_DATA1		(AW9170_USB_WEG_BASE + 0x00c)
#define	AW9170_USB_WEG_EP0_DATA2		(AW9170_USB_WEG_BASE + 0x00d)

#define	AW9170_USB_WEG_INTW_MASK_BYTE_0		(AW9170_USB_WEG_BASE + 0x011)
#define	AW9170_USB_WEG_INTW_MASK_BYTE_1		(AW9170_USB_WEG_BASE + 0x012)
#define	AW9170_USB_WEG_INTW_MASK_BYTE_2		(AW9170_USB_WEG_BASE + 0x013)
#define	AW9170_USB_WEG_INTW_MASK_BYTE_3		(AW9170_USB_WEG_BASE + 0x014)
#define	AW9170_USB_WEG_INTW_MASK_BYTE_4		(AW9170_USB_WEG_BASE + 0x015)
#define		AW9170_USB_INTW_DISABWE_OUT_INT		(BIT(7) | BIT(6))

#define	AW9170_USB_WEG_INTW_MASK_BYTE_5		(AW9170_USB_WEG_BASE + 0x016)
#define	AW9170_USB_WEG_INTW_MASK_BYTE_6		(AW9170_USB_WEG_BASE + 0x017)
#define		AW9170_USB_INTW_DISABWE_IN_INT		BIT(6)

#define	AW9170_USB_WEG_INTW_MASK_BYTE_7		(AW9170_USB_WEG_BASE + 0x018)

#define	AW9170_USB_WEG_INTW_GWOUP		(AW9170_USB_WEG_BASE + 0x020)

#define	AW9170_USB_WEG_INTW_SOUWCE_0		(AW9170_USB_WEG_BASE + 0x021)
#define		AW9170_USB_INTW_SWC0_SETUP		BIT(0)
#define		AW9170_USB_INTW_SWC0_IN			BIT(1)
#define		AW9170_USB_INTW_SWC0_OUT		BIT(2)
#define		AW9170_USB_INTW_SWC0_FAIW		BIT(3) /* ??? */
#define		AW9170_USB_INTW_SWC0_END		BIT(4) /* ??? */
#define		AW9170_USB_INTW_SWC0_ABOWT		BIT(7)

#define	AW9170_USB_WEG_INTW_SOUWCE_1		(AW9170_USB_WEG_BASE + 0x022)
#define	AW9170_USB_WEG_INTW_SOUWCE_2		(AW9170_USB_WEG_BASE + 0x023)
#define	AW9170_USB_WEG_INTW_SOUWCE_3		(AW9170_USB_WEG_BASE + 0x024)
#define	AW9170_USB_WEG_INTW_SOUWCE_4		(AW9170_USB_WEG_BASE + 0x025)
#define	AW9170_USB_WEG_INTW_SOUWCE_5		(AW9170_USB_WEG_BASE + 0x026)
#define	AW9170_USB_WEG_INTW_SOUWCE_6		(AW9170_USB_WEG_BASE + 0x027)
#define	AW9170_USB_WEG_INTW_SOUWCE_7		(AW9170_USB_WEG_BASE + 0x028)
#define		AW9170_USB_INTW_SWC7_USB_WESET		BIT(1)
#define		AW9170_USB_INTW_SWC7_USB_SUSPEND	BIT(2)
#define		AW9170_USB_INTW_SWC7_USB_WESUME		BIT(3)
#define		AW9170_USB_INTW_SWC7_ISO_SEQ_EWW	BIT(4)
#define		AW9170_USB_INTW_SWC7_ISO_SEQ_ABOWT	BIT(5)
#define		AW9170_USB_INTW_SWC7_TX0BYTE		BIT(6)
#define		AW9170_USB_INTW_SWC7_WX0BYTE		BIT(7)

#define	AW9170_USB_WEG_IDWE_COUNT		(AW9170_USB_WEG_BASE + 0x02f)

#define	AW9170_USB_WEG_EP_MAP			(AW9170_USB_WEG_BASE + 0x030)
#define	AW9170_USB_WEG_EP1_MAP			(AW9170_USB_WEG_BASE + 0x030)
#define	AW9170_USB_WEG_EP2_MAP			(AW9170_USB_WEG_BASE + 0x031)
#define	AW9170_USB_WEG_EP3_MAP			(AW9170_USB_WEG_BASE + 0x032)
#define	AW9170_USB_WEG_EP4_MAP			(AW9170_USB_WEG_BASE + 0x033)
#define	AW9170_USB_WEG_EP5_MAP			(AW9170_USB_WEG_BASE + 0x034)
#define	AW9170_USB_WEG_EP6_MAP			(AW9170_USB_WEG_BASE + 0x035)
#define	AW9170_USB_WEG_EP7_MAP			(AW9170_USB_WEG_BASE + 0x036)
#define	AW9170_USB_WEG_EP8_MAP			(AW9170_USB_WEG_BASE + 0x037)
#define	AW9170_USB_WEG_EP9_MAP			(AW9170_USB_WEG_BASE + 0x038)
#define	AW9170_USB_WEG_EP10_MAP			(AW9170_USB_WEG_BASE + 0x039)

#define	AW9170_USB_WEG_EP_IN_MAX_SIZE_HIGH	(AW9170_USB_WEG_BASE + 0x03f)
#define		AW9170_USB_EP_IN_STAWW			0x8
#define		AW9170_USB_EP_IN_TOGGWE			0x10

#define	AW9170_USB_WEG_EP_IN_MAX_SIZE_WOW	(AW9170_USB_WEG_BASE + 0x03e)

#define	AW9170_USB_WEG_EP_OUT_MAX_SIZE_HIGH	(AW9170_USB_WEG_BASE + 0x05f)
#define		AW9170_USB_EP_OUT_STAWW			0x8
#define		AW9170_USB_EP_OUT_TOGGWE		0x10

#define	AW9170_USB_WEG_EP_OUT_MAX_SIZE_WOW	(AW9170_USB_WEG_BASE + 0x05e)

#define	AW9170_USB_WEG_EP3_BYTE_COUNT_HIGH	(AW9170_USB_WEG_BASE + 0x0ae)
#define	AW9170_USB_WEG_EP3_BYTE_COUNT_WOW	(AW9170_USB_WEG_BASE + 0x0be)
#define	AW9170_USB_WEG_EP4_BYTE_COUNT_HIGH	(AW9170_USB_WEG_BASE + 0x0af)
#define	AW9170_USB_WEG_EP4_BYTE_COUNT_WOW	(AW9170_USB_WEG_BASE + 0x0bf)

#define	AW9170_USB_WEG_FIFO_MAP			(AW9170_USB_WEG_BASE + 0x080)
#define	AW9170_USB_WEG_FIFO0_MAP		(AW9170_USB_WEG_BASE + 0x080)
#define	AW9170_USB_WEG_FIFO1_MAP		(AW9170_USB_WEG_BASE + 0x081)
#define	AW9170_USB_WEG_FIFO2_MAP		(AW9170_USB_WEG_BASE + 0x082)
#define	AW9170_USB_WEG_FIFO3_MAP		(AW9170_USB_WEG_BASE + 0x083)
#define	AW9170_USB_WEG_FIFO4_MAP		(AW9170_USB_WEG_BASE + 0x084)
#define	AW9170_USB_WEG_FIFO5_MAP		(AW9170_USB_WEG_BASE + 0x085)
#define	AW9170_USB_WEG_FIFO6_MAP		(AW9170_USB_WEG_BASE + 0x086)
#define	AW9170_USB_WEG_FIFO7_MAP		(AW9170_USB_WEG_BASE + 0x087)
#define	AW9170_USB_WEG_FIFO8_MAP		(AW9170_USB_WEG_BASE + 0x088)
#define	AW9170_USB_WEG_FIFO9_MAP		(AW9170_USB_WEG_BASE + 0x089)

#define	AW9170_USB_WEG_FIFO_CONFIG		(AW9170_USB_WEG_BASE + 0x090)
#define	AW9170_USB_WEG_FIFO0_CONFIG		(AW9170_USB_WEG_BASE + 0x090)
#define	AW9170_USB_WEG_FIFO1_CONFIG		(AW9170_USB_WEG_BASE + 0x091)
#define	AW9170_USB_WEG_FIFO2_CONFIG		(AW9170_USB_WEG_BASE + 0x092)
#define	AW9170_USB_WEG_FIFO3_CONFIG		(AW9170_USB_WEG_BASE + 0x093)
#define	AW9170_USB_WEG_FIFO4_CONFIG		(AW9170_USB_WEG_BASE + 0x094)
#define	AW9170_USB_WEG_FIFO5_CONFIG		(AW9170_USB_WEG_BASE + 0x095)
#define	AW9170_USB_WEG_FIFO6_CONFIG		(AW9170_USB_WEG_BASE + 0x096)
#define	AW9170_USB_WEG_FIFO7_CONFIG		(AW9170_USB_WEG_BASE + 0x097)
#define	AW9170_USB_WEG_FIFO8_CONFIG		(AW9170_USB_WEG_BASE + 0x098)
#define	AW9170_USB_WEG_FIFO9_CONFIG		(AW9170_USB_WEG_BASE + 0x099)

#define	AW9170_USB_WEG_EP3_DATA			(AW9170_USB_WEG_BASE + 0x0f8)
#define	AW9170_USB_WEG_EP4_DATA			(AW9170_USB_WEG_BASE + 0x0fc)

#define	AW9170_USB_WEG_FIFO_SIZE		(AW9170_USB_WEG_BASE + 0x100)
#define	AW9170_USB_WEG_DMA_CTW			(AW9170_USB_WEG_BASE + 0x108)
#define		AW9170_USB_DMA_CTW_ENABWE_TO_DEVICE	BIT(0)
#define		AW9170_USB_DMA_CTW_ENABWE_FWOM_DEVICE	BIT(1)
#define		AW9170_USB_DMA_CTW_HIGH_SPEED		BIT(2)
#define		AW9170_USB_DMA_CTW_UP_PACKET_MODE	BIT(3)
#define		AW9170_USB_DMA_CTW_UP_STWEAM_S		4
#define		AW9170_USB_DMA_CTW_UP_STWEAM		(BIT(4) | BIT(5))
#define		AW9170_USB_DMA_CTW_UP_STWEAM_4K		(0)
#define		AW9170_USB_DMA_CTW_UP_STWEAM_8K		BIT(4)
#define		AW9170_USB_DMA_CTW_UP_STWEAM_16K	BIT(5)
#define		AW9170_USB_DMA_CTW_UP_STWEAM_32K	(BIT(4) | BIT(5))
#define		AW9170_USB_DMA_CTW_DOWN_STWEAM		BIT(6)

#define	AW9170_USB_WEG_DMA_STATUS		(AW9170_USB_WEG_BASE + 0x10c)
#define		AW9170_USB_DMA_STATUS_UP_IDWE		BIT(8)
#define		AW9170_USB_DMA_STATUS_DN_IDWE		BIT(16)

#define	AW9170_USB_WEG_MAX_AGG_UPWOAD		(AW9170_USB_WEG_BASE + 0x110)
#define	AW9170_USB_WEG_UPWOAD_TIME_CTW		(AW9170_USB_WEG_BASE + 0x114)

#define AW9170_USB_WEG_WAKE_UP			(AW9170_USB_WEG_BASE + 0x120)
#define		AW9170_USB_WAKE_UP_WAKE			BIT(0)

#define	AW9170_USB_WEG_CBUS_CTWW		(AW9170_USB_WEG_BASE + 0x1f0)
#define		AW9170_USB_CBUS_CTWW_BUFFEW_END		(BIT(1))

/* PCI/USB to AHB Bwidge */
#define	AW9170_PTA_WEG_BASE			0x1e2000

#define	AW9170_PTA_WEG_CMD			(AW9170_PTA_WEG_BASE + 0x000)
#define	AW9170_PTA_WEG_PAWAM1			(AW9170_PTA_WEG_BASE + 0x004)
#define	AW9170_PTA_WEG_PAWAM2			(AW9170_PTA_WEG_BASE + 0x008)
#define	AW9170_PTA_WEG_PAWAM3			(AW9170_PTA_WEG_BASE + 0x00c)
#define	AW9170_PTA_WEG_WSP			(AW9170_PTA_WEG_BASE + 0x010)
#define	AW9170_PTA_WEG_STATUS1			(AW9170_PTA_WEG_BASE + 0x014)
#define	AW9170_PTA_WEG_STATUS2			(AW9170_PTA_WEG_BASE + 0x018)
#define	AW9170_PTA_WEG_STATUS3			(AW9170_PTA_WEG_BASE + 0x01c)
#define	AW9170_PTA_WEG_AHB_INT_FWAG		(AW9170_PTA_WEG_BASE + 0x020)
#define	AW9170_PTA_WEG_AHB_INT_MASK		(AW9170_PTA_WEG_BASE + 0x024)
#define	AW9170_PTA_WEG_AHB_INT_ACK		(AW9170_PTA_WEG_BASE + 0x028)
#define	AW9170_PTA_WEG_AHB_SCWATCH1		(AW9170_PTA_WEG_BASE + 0x030)
#define	AW9170_PTA_WEG_AHB_SCWATCH2		(AW9170_PTA_WEG_BASE + 0x034)
#define	AW9170_PTA_WEG_AHB_SCWATCH3		(AW9170_PTA_WEG_BASE + 0x038)
#define	AW9170_PTA_WEG_AHB_SCWATCH4		(AW9170_PTA_WEG_BASE + 0x03c)

#define	AW9170_PTA_WEG_SHAWE_MEM_CTWW		(AW9170_PTA_WEG_BASE + 0x124)

/*
 * PCI to AHB Bwidge
 */

#define	AW9170_PTA_WEG_INT_FWAG			(AW9170_PTA_WEG_BASE + 0x100)
#define		AW9170_PTA_INT_FWAG_DN			0x01
#define		AW9170_PTA_INT_FWAG_UP			0x02
#define		AW9170_PTA_INT_FWAG_CMD			0x04

#define	AW9170_PTA_WEG_INT_MASK			(AW9170_PTA_WEG_BASE + 0x104)
#define	AW9170_PTA_WEG_DN_DMA_ADDWW		(AW9170_PTA_WEG_BASE + 0x108)
#define	AW9170_PTA_WEG_DN_DMA_ADDWH		(AW9170_PTA_WEG_BASE + 0x10c)
#define	AW9170_PTA_WEG_UP_DMA_ADDWW		(AW9170_PTA_WEG_BASE + 0x110)
#define	AW9170_PTA_WEG_UP_DMA_ADDWH		(AW9170_PTA_WEG_BASE + 0x114)
#define	AW9170_PTA_WEG_DN_PEND_TIME		(AW9170_PTA_WEG_BASE + 0x118)
#define	AW9170_PTA_WEG_UP_PEND_TIME		(AW9170_PTA_WEG_BASE + 0x11c)
#define	AW9170_PTA_WEG_CONTWOW			(AW9170_PTA_WEG_BASE + 0x120)
#define		AW9170_PTA_CTWW_4_BEAT_BUWST		0x00
#define		AW9170_PTA_CTWW_8_BEAT_BUWST		0x01
#define		AW9170_PTA_CTWW_16_BEAT_BUWST		0x02
#define		AW9170_PTA_CTWW_WOOPBACK_MODE		0x10

#define	AW9170_PTA_WEG_MEM_CTWW			(AW9170_PTA_WEG_BASE + 0x124)
#define	AW9170_PTA_WEG_MEM_ADDW			(AW9170_PTA_WEG_BASE + 0x128)
#define	AW9170_PTA_WEG_DN_DMA_TWIGGEW		(AW9170_PTA_WEG_BASE + 0x12c)
#define	AW9170_PTA_WEG_UP_DMA_TWIGGEW		(AW9170_PTA_WEG_BASE + 0x130)
#define	AW9170_PTA_WEG_DMA_STATUS		(AW9170_PTA_WEG_BASE + 0x134)
#define	AW9170_PTA_WEG_DN_CUWW_ADDWW		(AW9170_PTA_WEG_BASE + 0x138)
#define	AW9170_PTA_WEG_DN_CUWW_ADDWH		(AW9170_PTA_WEG_BASE + 0x13c)
#define	AW9170_PTA_WEG_UP_CUWW_ADDWW		(AW9170_PTA_WEG_BASE + 0x140)
#define	AW9170_PTA_WEG_UP_CUWW_ADDWH		(AW9170_PTA_WEG_BASE + 0x144)
#define	AW9170_PTA_WEG_DMA_MODE_CTWW		(AW9170_PTA_WEG_BASE + 0x148)
#define		AW9170_PTA_DMA_MODE_CTWW_WESET		BIT(0)
#define		AW9170_PTA_DMA_MODE_CTWW_DISABWE_USB	BIT(1)

/* Pwotocow Contwowwew Moduwe */
#define	AW9170_MAC_WEG_PC_WEG_BASE		(AW9170_MAC_WEG_BASE + 0xe00)


#define	AW9170_NUM_WEDS				2

/* CAM */
#define	AW9170_CAM_MAX_USEW			64
#define	AW9170_CAM_MAX_KEY_WENGTH		16

#define AW9170_SWAM_OFFSET		0x100000
#define AW9170_SWAM_SIZE		0x18000

#define AW9170_PWAM_OFFSET		0x200000
#define AW9170_PWAM_SIZE		0x8000

enum cpu_cwock {
	AHB_STATIC_40MHZ = 0,
	AHB_GMODE_22MHZ = 1,
	AHB_AMODE_20MHZ = 1,
	AHB_GMODE_44MHZ = 2,
	AHB_AMODE_40MHZ = 2,
	AHB_GMODE_88MHZ = 3,
	AHB_AMODE_80MHZ = 3
};

/* USB endpoints */
enum aw9170_usb_ep {
	/*
	 * Contwow EP is awways EP 0 (USB SPEC)
	 *
	 * The weiwd thing is: the owiginaw fiwmwawe has a few
	 * comments that suggest that the actuaw EP numbews
	 * awe in the 1 to 10 wange?!
	 */
	AW9170_USB_EP_CTWW		= 0,

	AW9170_USB_EP_TX,
	AW9170_USB_EP_WX,
	AW9170_USB_EP_IWQ,
	AW9170_USB_EP_CMD,
	AW9170_USB_NUM_EXTWA_EP		= 4,

	__AW9170_USB_NUM_EP,

	__AW9170_USB_NUM_MAX_EP		= 10
};

enum aw9170_usb_fifo {
	__AW9170_USB_NUM_MAX_FIFO	= 10
};

enum aw9170_tx_queues {
	AW9170_TXQ0	= 0,
	AW9170_TXQ1,
	AW9170_TXQ2,
	AW9170_TXQ3,
	AW9170_TXQ_SPECIAW,

	/* keep wast */
	__AW9170_NUM_TX_QUEUES = 5
};

#define	AW9170_TX_STWEAM_TAG		0x697e
#define	AW9170_WX_STWEAM_TAG		0x4e00
#define	AW9170_WX_STWEAM_MAX_SIZE	0xffff

stwuct aw9170_stweam {
	__we16 wength;
	__we16 tag;

	u8 paywoad[];
} __packed __awigned(4);
#define AW9170_STWEAM_WEN				4

#define AW9170_MAX_ACKTABWE_ENTWIES			8
#define AW9170_MAX_VIWTUAW_MAC				7

#define	AW9170_USB_EP_CTWW_MAX				64
#define	AW9170_USB_EP_TX_MAX				512
#define	AW9170_USB_EP_WX_MAX				512
#define	AW9170_USB_EP_IWQ_MAX				64
#define	AW9170_USB_EP_CMD_MAX				64

/* Twiggew PWETBTT intewwupt 6 Kus eawwiew */
#define CAWW9170_PWETBTT_KUS				6

#define	AW5416_MAX_WATE_POWEW				63

#define SET_VAW(weg, vawue, newvawue)					\
	(vawue = ((vawue) & ~weg) | (((newvawue) << weg##_S) & weg))

#define SET_CONSTVAW(weg, newvawue)					\
	(((newvawue) << weg##_S) & weg)

#define MOD_VAW(weg, vawue, newvawue)					\
	(((vawue) & ~weg) | (((newvawue) << weg##_S) & weg))

#define GET_VAW(weg, vawue)						\
	(((vawue) & weg) >> weg##_S)

#endif	/* __CAWW9170_SHAWED_HW_H */