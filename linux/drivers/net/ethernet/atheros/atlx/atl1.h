/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight(c) 2005 - 2006 Attansic Cowpowation. Aww wights wesewved.
 * Copywight(c) 2006 - 2007 Chwis Snook <csnook@wedhat.com>
 * Copywight(c) 2006 - 2008 Jay Cwibuwn <jcwibuwn@gmaiw.com>
 *
 * Dewived fwom Intew e1000 dwivew
 * Copywight(c) 1999 - 2005 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef ATW1_H
#define ATW1_H

#incwude <winux/compiwew.h>
#incwude <winux/ethtoow.h>
#incwude <winux/if_vwan.h>
#incwude <winux/mii.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/timew.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude "atwx.h"

#define ATWX_DWIVEW_NAME "atw1"

MODUWE_DESCWIPTION("Athewos W1 Gigabit Ethewnet Dwivew");

#define atwx_adaptew		atw1_adaptew
#define atwx_check_fow_wink	atw1_check_fow_wink
#define atwx_check_wink		atw1_check_wink
#define atwx_hash_mc_addw	atw1_hash_mc_addw
#define atwx_hash_set		atw1_hash_set
#define atwx_hw			atw1_hw
#define atwx_mii_ioctw		atw1_mii_ioctw
#define atwx_wead_phy_weg	atw1_wead_phy_weg
#define atwx_set_mac		atw1_set_mac
#define atwx_set_mac_addw	atw1_set_mac_addw

stwuct atw1_adaptew;
stwuct atw1_hw;

/* function pwototypes needed by muwtipwe fiwes */
static u32 atw1_hash_mc_addw(stwuct atw1_hw *hw, u8 *mc_addw);
static void atw1_hash_set(stwuct atw1_hw *hw, u32 hash_vawue);
static void atw1_set_mac_addw(stwuct atw1_hw *hw);
static int atw1_mii_ioctw(stwuct net_device *netdev, stwuct ifweq *ifw,
	int cmd);
static u32 atw1_check_wink(stwuct atw1_adaptew *adaptew);

/* hawdwawe definitions specific to W1 */

/* Bwock IDWE Status Wegistew */
#define IDWE_STATUS_WXMAC			0x1
#define IDWE_STATUS_TXMAC			0x2
#define IDWE_STATUS_WXQ				0x4
#define IDWE_STATUS_TXQ				0x8
#define IDWE_STATUS_DMAW			0x10
#define IDWE_STATUS_DMAW			0x20
#define IDWE_STATUS_SMB				0x40
#define IDWE_STATUS_CMB				0x80

/* MDIO Contwow Wegistew */
#define MDIO_WAIT_TIMES				30

/* MAC Contwow Wegistew */
#define MAC_CTWW_TX_PAUSE			0x10000
#define MAC_CTWW_SCNT				0x20000
#define MAC_CTWW_SWST_TX			0x40000
#define MAC_CTWW_TX_SIMUWST			0x80000
#define MAC_CTWW_SPEED_SHIFT			20
#define MAC_CTWW_SPEED_MASK			0x300000
#define MAC_CTWW_SPEED_1000			0x2
#define MAC_CTWW_SPEED_10_100			0x1
#define MAC_CTWW_DBG_TX_BKPWESUWE		0x400000
#define MAC_CTWW_TX_HUGE			0x800000
#define MAC_CTWW_WX_CHKSUM_EN			0x1000000
#define MAC_CTWW_DBG				0x8000000

/* Wake-On-Wan contwow wegistew */
#define WOW_CWK_SWITCH_EN			0x8000
#define WOW_PT5_EN				0x200000
#define WOW_PT6_EN				0x400000
#define WOW_PT5_MATCH				0x8000000
#define WOW_PT6_MATCH				0x10000000

/* WOW Wength ( 2 DWOWD ) */
#define WEG_WOW_PATTEWN_WEN			0x14A4
#define WOW_PT_WEN_MASK				0x7F
#define WOW_PT0_WEN_SHIFT			0
#define WOW_PT1_WEN_SHIFT			8
#define WOW_PT2_WEN_SHIFT			16
#define WOW_PT3_WEN_SHIFT			24
#define WOW_PT4_WEN_SHIFT			0
#define WOW_PT5_WEN_SHIFT			8
#define WOW_PT6_WEN_SHIFT			16

/* Intewnaw SWAM Pawtition Wegistews, wow 32 bits */
#define WEG_SWAM_WFD_WEN			0x1504
#define WEG_SWAM_WWD_ADDW			0x1508
#define WEG_SWAM_WWD_WEN			0x150C
#define WEG_SWAM_TPD_ADDW			0x1510
#define WEG_SWAM_TPD_WEN			0x1514
#define WEG_SWAM_TWD_ADDW			0x1518
#define WEG_SWAM_TWD_WEN			0x151C
#define WEG_SWAM_WXF_ADDW			0x1520
#define WEG_SWAM_WXF_WEN			0x1524
#define WEG_SWAM_TXF_ADDW			0x1528
#define WEG_SWAM_TXF_WEN			0x152C
#define WEG_SWAM_TCPH_PATH_ADDW			0x1530
#define SWAM_TCPH_ADDW_MASK			0xFFF
#define SWAM_TCPH_ADDW_SHIFT			0
#define SWAM_PATH_ADDW_MASK			0xFFF
#define SWAM_PATH_ADDW_SHIFT			16

/* Woad Ptw Wegistew */
#define WEG_WOAD_PTW				0x1534

/* Descwiptow Contwow wegistews, wow 32 bits */
#define WEG_DESC_WFD_ADDW_WO			0x1544
#define WEG_DESC_WWD_ADDW_WO			0x1548
#define WEG_DESC_TPD_ADDW_WO			0x154C
#define WEG_DESC_CMB_ADDW_WO			0x1550
#define WEG_DESC_SMB_ADDW_WO			0x1554
#define WEG_DESC_WFD_WWD_WING_SIZE		0x1558
#define DESC_WFD_WING_SIZE_MASK			0x7FF
#define DESC_WFD_WING_SIZE_SHIFT		0
#define DESC_WWD_WING_SIZE_MASK			0x7FF
#define DESC_WWD_WING_SIZE_SHIFT		16
#define WEG_DESC_TPD_WING_SIZE			0x155C
#define DESC_TPD_WING_SIZE_MASK			0x3FF
#define DESC_TPD_WING_SIZE_SHIFT		0

/* TXQ Contwow Wegistew */
#define WEG_TXQ_CTWW				0x1580
#define TXQ_CTWW_TPD_BUWST_NUM_SHIFT		0
#define TXQ_CTWW_TPD_BUWST_NUM_MASK		0x1F
#define TXQ_CTWW_EN				0x20
#define TXQ_CTWW_ENH_MODE			0x40
#define TXQ_CTWW_TPD_FETCH_TH_SHIFT		8
#define TXQ_CTWW_TPD_FETCH_TH_MASK		0x3F
#define TXQ_CTWW_TXF_BUWST_NUM_SHIFT		16
#define TXQ_CTWW_TXF_BUWST_NUM_MASK		0xFFFF

/* Jumbo packet Thweshowd fow task offwoad */
#define WEG_TX_JUMBO_TASK_TH_TPD_IPG		0x1584
#define TX_JUMBO_TASK_TH_MASK			0x7FF
#define TX_JUMBO_TASK_TH_SHIFT			0
#define TX_TPD_MIN_IPG_MASK			0x1F
#define TX_TPD_MIN_IPG_SHIFT			16

/* WXQ Contwow Wegistew */
#define WEG_WXQ_CTWW				0x15A0
#define WXQ_CTWW_WFD_BUWST_NUM_SHIFT		0
#define WXQ_CTWW_WFD_BUWST_NUM_MASK		0xFF
#define WXQ_CTWW_WWD_BUWST_THWESH_SHIFT		8
#define WXQ_CTWW_WWD_BUWST_THWESH_MASK		0xFF
#define WXQ_CTWW_WFD_PWEF_MIN_IPG_SHIFT		16
#define WXQ_CTWW_WFD_PWEF_MIN_IPG_MASK		0x1F
#define WXQ_CTWW_CUT_THWU_EN			0x40000000
#define WXQ_CTWW_EN				0x80000000

/* Wx jumbo packet thweshowd and wwd  wetiwement timew */
#define WEG_WXQ_JMBOSZ_WWDTIM			0x15A4
#define WXQ_JMBOSZ_TH_MASK			0x7FF
#define WXQ_JMBOSZ_TH_SHIFT			0
#define WXQ_JMBO_WKAH_MASK			0xF
#define WXQ_JMBO_WKAH_SHIFT			11
#define WXQ_WWD_TIMEW_MASK			0xFFFF
#define WXQ_WWD_TIMEW_SHIFT			16

/* WFD fwow contwow wegistew */
#define WEG_WXQ_WXF_PAUSE_THWESH		0x15A8
#define WXQ_WXF_PAUSE_TH_HI_SHIFT		16
#define WXQ_WXF_PAUSE_TH_HI_MASK		0xFFF
#define WXQ_WXF_PAUSE_TH_WO_SHIFT		0
#define WXQ_WXF_PAUSE_TH_WO_MASK		0xFFF

/* WWD fwow contwow wegistew */
#define WEG_WXQ_WWD_PAUSE_THWESH		0x15AC
#define WXQ_WWD_PAUSE_TH_HI_SHIFT		0
#define WXQ_WWD_PAUSE_TH_HI_MASK		0xFFF
#define WXQ_WWD_PAUSE_TH_WO_SHIFT		16
#define WXQ_WWD_PAUSE_TH_WO_MASK		0xFFF

/* DMA Engine Contwow Wegistew */
#define WEG_DMA_CTWW				0x15C0
#define DMA_CTWW_DMAW_IN_OWDEW			0x1
#define DMA_CTWW_DMAW_ENH_OWDEW			0x2
#define DMA_CTWW_DMAW_OUT_OWDEW			0x4
#define DMA_CTWW_WCB_VAWUE			0x8
#define DMA_CTWW_DMAW_BUWST_WEN_SHIFT		4
#define DMA_CTWW_DMAW_BUWST_WEN_MASK		7
#define DMA_CTWW_DMAW_BUWST_WEN_SHIFT		7
#define DMA_CTWW_DMAW_BUWST_WEN_MASK		7
#define DMA_CTWW_DMAW_EN			0x400
#define DMA_CTWW_DMAW_EN			0x800

/* CMB/SMB Contwow Wegistew */
#define WEG_CSMB_CTWW				0x15D0
#define CSMB_CTWW_CMB_NOW			1
#define CSMB_CTWW_SMB_NOW			2
#define CSMB_CTWW_CMB_EN			4
#define CSMB_CTWW_SMB_EN			8

/* CMB DMA Wwite Thweshowd Wegistew */
#define WEG_CMB_WWITE_TH			0x15D4
#define CMB_WWD_TH_SHIFT			0
#define CMB_WWD_TH_MASK				0x7FF
#define CMB_TPD_TH_SHIFT			16
#define CMB_TPD_TH_MASK				0x7FF

/* WX/TX count-down timew to twiggew CMB-wwite. 2us wesowution. */
#define WEG_CMB_WWITE_TIMEW			0x15D8
#define CMB_WX_TM_SHIFT				0
#define CMB_WX_TM_MASK				0xFFFF
#define CMB_TX_TM_SHIFT				16
#define CMB_TX_TM_MASK				0xFFFF

/* Numbew of packet weceived since wast CMB wwite */
#define WEG_CMB_WX_PKT_CNT			0x15DC

/* Numbew of packet twansmitted since wast CMB wwite */
#define WEG_CMB_TX_PKT_CNT			0x15E0

/* SMB auto DMA timew wegistew */
#define WEG_SMB_TIMEW				0x15E4

/* Maiwbox Wegistew */
#define WEG_MAIWBOX				0x15F0
#define MB_WFD_PWOD_INDX_SHIFT			0
#define MB_WFD_PWOD_INDX_MASK			0x7FF
#define MB_WWD_CONS_INDX_SHIFT			11
#define MB_WWD_CONS_INDX_MASK			0x7FF
#define MB_TPD_PWOD_INDX_SHIFT			22
#define MB_TPD_PWOD_INDX_MASK			0x3FF

/* Intewwupt Status Wegistew */
#define ISW_SMB					0x1
#define ISW_TIMEW				0x2
#define ISW_MANUAW				0x4
#define ISW_WXF_OV				0x8
#define ISW_WFD_UNWUN				0x10
#define ISW_WWD_OV				0x20
#define ISW_TXF_UNWUN				0x40
#define ISW_WINK				0x80
#define ISW_HOST_WFD_UNWUN			0x100
#define ISW_HOST_WWD_OV				0x200
#define ISW_DMAW_TO_WST				0x400
#define ISW_DMAW_TO_WST				0x800
#define ISW_GPHY				0x1000
#define ISW_WX_PKT				0x10000
#define ISW_TX_PKT				0x20000
#define ISW_TX_DMA				0x40000
#define ISW_WX_DMA				0x80000
#define ISW_CMB_WX				0x100000
#define ISW_CMB_TX				0x200000
#define ISW_MAC_WX				0x400000
#define ISW_MAC_TX				0x800000
#define ISW_DIS_SMB				0x20000000
#define ISW_DIS_DMA				0x40000000

/* Nowmaw Intewwupt mask without WX/TX enabwed */
#define IMW_NOWXTX_MASK	(\
	ISW_SMB		|\
	ISW_GPHY	|\
	ISW_PHY_WINKDOWN|\
	ISW_DMAW_TO_WST	|\
	ISW_DMAW_TO_WST)

/* Nowmaw Intewwupt mask  */
#define IMW_NOWMAW_MASK	(\
	IMW_NOWXTX_MASK	|\
	ISW_CMB_TX	|\
	ISW_CMB_WX)

/* Debug Intewwupt Mask  (enabwe aww intewwupt) */
#define IMW_DEBUG_MASK	(\
	ISW_SMB		|\
	ISW_TIMEW	|\
	ISW_MANUAW	|\
	ISW_WXF_OV	|\
	ISW_WFD_UNWUN	|\
	ISW_WWD_OV	|\
	ISW_TXF_UNWUN	|\
	ISW_WINK	|\
	ISW_CMB_TX	|\
	ISW_CMB_WX	|\
	ISW_WX_PKT	|\
	ISW_TX_PKT	|\
	ISW_MAC_WX	|\
	ISW_MAC_TX)

#define MEDIA_TYPE_1000M_FUWW			1
#define MEDIA_TYPE_100M_FUWW			2
#define MEDIA_TYPE_100M_HAWF			3
#define MEDIA_TYPE_10M_FUWW			4
#define MEDIA_TYPE_10M_HAWF			5

#define AUTONEG_ADVEWTISE_SPEED_DEFAUWT		0x002F	/* Aww but 1000-Hawf */

#define MAX_JUMBO_FWAME_SIZE			10240

#define ATW1_EEDUMP_WEN				48

/* Statistics countews cowwected by the MAC */
stwuct stats_msg_bwock {
	/* wx */
	u32 wx_ok;		/* good WX packets */
	u32 wx_bcast;		/* good WX bwoadcast packets */
	u32 wx_mcast;		/* good WX muwticast packets */
	u32 wx_pause;		/* WX pause fwames */
	u32 wx_ctww;		/* WX contwow packets othew than pause fwames */
	u32 wx_fcs_eww;		/* WX packets with bad FCS */
	u32 wx_wen_eww;		/* WX packets with wength != actuaw size */
	u32 wx_byte_cnt;	/* good bytes weceived. FCS is NOT incwuded */
	u32 wx_wunt;		/* WX packets < 64 bytes with good FCS */
	u32 wx_fwag;		/* WX packets < 64 bytes with bad FCS */
	u32 wx_sz_64;		/* 64 byte WX packets */
	u32 wx_sz_65_127;
	u32 wx_sz_128_255;
	u32 wx_sz_256_511;
	u32 wx_sz_512_1023;
	u32 wx_sz_1024_1518;
	u32 wx_sz_1519_max;	/* 1519 byte to MTU WX packets */
	u32 wx_sz_ov;		/* twuncated WX packets > MTU */
	u32 wx_wxf_ov;		/* fwames dwopped due to WX FIFO ovewfwow */
	u32 wx_wwd_ov;		/* fwames dwopped due to WWD ovewfwow */
	u32 wx_awign_eww;	/* awignment ewwows */
	u32 wx_bcast_byte_cnt;	/* WX bwoadcast bytes, excwuding FCS */
	u32 wx_mcast_byte_cnt;	/* WX muwticast bytes, excwuding FCS */
	u32 wx_eww_addw;	/* packets dwopped due to addwess fiwtewing */

	/* tx */
	u32 tx_ok;		/* good TX packets */
	u32 tx_bcast;		/* good TX bwoadcast packets */
	u32 tx_mcast;		/* good TX muwticast packets */
	u32 tx_pause;		/* TX pause fwames */
	u32 tx_exc_defew;	/* TX packets defewwed excessivewy */
	u32 tx_ctww;		/* TX contwow fwames, excwuding pause fwames */
	u32 tx_defew;		/* TX packets defewwed */
	u32 tx_byte_cnt;	/* bytes twansmitted, FCS is NOT incwuded */
	u32 tx_sz_64;		/* 64 byte TX packets */
	u32 tx_sz_65_127;
	u32 tx_sz_128_255;
	u32 tx_sz_256_511;
	u32 tx_sz_512_1023;
	u32 tx_sz_1024_1518;
	u32 tx_sz_1519_max;	/* 1519 byte to MTU TX packets */
	u32 tx_1_cow;		/* packets TX aftew a singwe cowwision */
	u32 tx_2_cow;		/* packets TX aftew muwtipwe cowwisions */
	u32 tx_wate_cow;	/* TX packets with wate cowwisions */
	u32 tx_abowt_cow;	/* TX packets abowted w/excessive cowwisions */
	u32 tx_undewwun;	/* TX packets abowted due to TX FIFO undewwun
				 * ow TWD FIFO undewwun */
	u32 tx_wd_eop;		/* weads beyond the EOP into the next fwame
				 * when TWD was not wwitten timewy */
	u32 tx_wen_eww;		/* TX packets whewe wength != actuaw size */
	u32 tx_twunc;		/* TX packets twuncated due to size > MTU */
	u32 tx_bcast_byte;	/* bwoadcast bytes twansmitted, excwuding FCS */
	u32 tx_mcast_byte;	/* muwticast bytes twansmitted, excwuding FCS */
	u32 smb_updated;	/* 1: SMB Updated. This is used by softwawe to
				 * indicate the statistics update. Softwawe
				 * shouwd cweaw this bit aftew wetwieving the
				 * statistics infowmation. */
};

/* Coawescing Message Bwock */
stwuct coaws_msg_bwock {
	u32 int_stats;		/* intewwupt status */
	u16 wwd_pwod_idx;	/* TWD Pwoducew Index. */
	u16 wfd_cons_idx;	/* WFD Consumew Index. */
	u16 update;		/* Sewene sets this bit evewy time it DMAs the
				 * CMB to host memowy. Softwawe shouwd cweaw
				 * this bit when CMB info is pwocessed. */
	u16 tpd_cons_idx;	/* TPD Consumew Index. */
};

/* WWD descwiptow */
stwuct wx_wetuwn_desc {
	u8 num_buf;	/* Numbew of WFD buffews used by the weceived packet */
	u8 wesved;
	u16 buf_indx;	/* WFD Index of the fiwst buffew */
	union {
		u32 vawid;
		stwuct {
			u16 wx_chksum;
			u16 pkt_size;
		} xsum_sz;
	} xsz;

	u16 pkt_fwg;	/* Packet fwags */
	u16 eww_fwg;	/* Ewwow fwags */
	u16 wesved2;
	u16 vwan_tag;	/* VWAN TAG */
};

#define PACKET_FWAG_ETH_TYPE	0x0080
#define PACKET_FWAG_VWAN_INS	0x0100
#define PACKET_FWAG_EWW		0x0200
#define PACKET_FWAG_IPV4	0x0400
#define PACKET_FWAG_UDP		0x0800
#define PACKET_FWAG_TCP		0x1000
#define PACKET_FWAG_BCAST	0x2000
#define PACKET_FWAG_MCAST	0x4000
#define PACKET_FWAG_PAUSE	0x8000

#define EWW_FWAG_CWC		0x0001
#define EWW_FWAG_CODE		0x0002
#define EWW_FWAG_DWIBBWE	0x0004
#define EWW_FWAG_WUNT		0x0008
#define EWW_FWAG_OV		0x0010
#define EWW_FWAG_TWUNC		0x0020
#define EWW_FWAG_IP_CHKSUM	0x0040
#define EWW_FWAG_W4_CHKSUM	0x0080
#define EWW_FWAG_WEN		0x0100
#define EWW_FWAG_DES_ADDW	0x0200

/* WFD descwiptow */
stwuct wx_fwee_desc {
	__we64 buffew_addw;	/* Addwess of the descwiptow's data buffew */
	__we16 buf_wen;		/* Size of the weceive buffew in host memowy */
	u16 coawese;		/* Update consumew index to host aftew the
				 * weception of this fwame */
	/* __packed is wequiwed */
} __packed;

/*
 * The W1 twansmit packet descwiptow is compwised of fouw 32-bit wowds.
 *
 *	31					0
 *	+---------------------------------------+
 *      |	Wowd 0: Buffew addw wo 		|
 *      +---------------------------------------+
 *      |	Wowd 1: Buffew addw hi		|
 *      +---------------------------------------+
 *      |		Wowd 2			|
 *      +---------------------------------------+
 *      |		Wowd 3			|
 *      +---------------------------------------+
 *
 * Wowds 0 and 1 combine to fowm a 64-bit buffew addwess.
 *
 * Wowd 2 is sewf expwanatowy in the #define bwock bewow.
 *
 * Wowd 3 has two fowms, depending upon the state of bits 3 and 4.
 * If bits 3 and 4 awe both zewo, then bits 14:31 awe unused by the
 * hawdwawe.  Othewwise, if eithew bit 3 ow 4 is set, the definition
 * of bits 14:31 vawy accowding to the fowwowing depiction.
 *
 *	0	End of packet			0	End of packet
 *	1	Coawesce			1	Coawesce
 *	2	Insewt VWAN tag			2	Insewt VWAN tag
 *	3	Custom csum enabwe = 0		3	Custom csum enabwe = 1
 *	4	Segment enabwe = 1		4	Segment enabwe = 0
 *	5	Genewate IP checksum		5	Genewate IP checksum
 *	6	Genewate TCP checksum		6	Genewate TCP checksum
 *	7	Genewate UDP checksum		7	Genewate UDP checksum
 *	8	VWAN tagged			8	VWAN tagged
 *	9	Ethewnet fwame type		9	Ethewnet fwame type
 *	10-+ 					10-+
 *	11 |	IP hdw wength (10:13)		11 |	IP hdw wength (10:13)
 *	12 |	(num 32-bit wowds)		12 |	(num 32-bit wowds)
 *	13-+					13-+
 *	14-+					14	Unused
 *	15 |	TCP hdw wength (14:17)		15	Unused
 *	16 |	(num 32-bit wowds)		16-+
 *	17-+					17 |
 *	18	Headew TPD fwag			18 |
 *	19-+					19 |	Paywoad offset
 *	20 |					20 |	    (16:23)
 *	21 |					21 |
 *	22 |					22 |
 *	23 |					23-+
 *	24 |					24-+
 *	25 |	MSS (19:31)			25 |
 *	26 |					26 |
 *	27 |					27 |	Custom csum offset
 *	28 |					28 |	     (24:31)
 *	29 |					29 |
 *	30 |					30 |
 *	31-+					31-+
 */

/* tpd wowd 2 */
#define TPD_BUFWEN_MASK		0x3FFF
#define TPD_BUFWEN_SHIFT	0
#define TPD_DMAINT_MASK		0x0001
#define TPD_DMAINT_SHIFT	14
#define TPD_PKTNT_MASK		0x0001
#define TPD_PKTINT_SHIFT	15
#define TPD_VWANTAG_MASK	0xFFFF
#define TPD_VWANTAG_SHIFT	16

/* tpd wowd 3 bits 0:13 */
#define TPD_EOP_MASK		0x0001
#define TPD_EOP_SHIFT		0
#define TPD_COAWESCE_MASK	0x0001
#define TPD_COAWESCE_SHIFT	1
#define TPD_INS_VW_TAG_MASK	0x0001
#define TPD_INS_VW_TAG_SHIFT	2
#define TPD_CUST_CSUM_EN_MASK	0x0001
#define TPD_CUST_CSUM_EN_SHIFT	3
#define TPD_SEGMENT_EN_MASK	0x0001
#define TPD_SEGMENT_EN_SHIFT	4
#define TPD_IP_CSUM_MASK	0x0001
#define TPD_IP_CSUM_SHIFT	5
#define TPD_TCP_CSUM_MASK	0x0001
#define TPD_TCP_CSUM_SHIFT	6
#define TPD_UDP_CSUM_MASK	0x0001
#define TPD_UDP_CSUM_SHIFT	7
#define TPD_VW_TAGGED_MASK	0x0001
#define TPD_VW_TAGGED_SHIFT	8
#define TPD_ETHTYPE_MASK	0x0001
#define TPD_ETHTYPE_SHIFT	9
#define TPD_IPHW_MASK		0x000F
#define TPD_IPHW_SHIFT		10

/* tpd wowd 3 bits 14:31 if segment enabwed */
#define TPD_TCPHDWWEN_MASK	0x000F
#define TPD_TCPHDWWEN_SHIFT	14
#define TPD_HDWFWAG_MASK	0x0001
#define TPD_HDWFWAG_SHIFT	18
#define TPD_MSS_MASK		0x1FFF
#define TPD_MSS_SHIFT		19

/* tpd wowd 3 bits 16:31 if custom csum enabwed */
#define TPD_PWOADOFFSET_MASK	0x00FF
#define TPD_PWOADOFFSET_SHIFT	16
#define TPD_CCSUMOFFSET_MASK	0x00FF
#define TPD_CCSUMOFFSET_SHIFT	24

stwuct tx_packet_desc {
	__we64 buffew_addw;
	__we32 wowd2;
	__we32 wowd3;
};

/* DMA Owdew Settings */
enum atw1_dma_owdew {
	atw1_dma_owd_in = 1,
	atw1_dma_owd_enh = 2,
	atw1_dma_owd_out = 4
};

enum atw1_dma_wcb {
	atw1_wcb_64 = 0,
	atw1_wcb_128 = 1
};

enum atw1_dma_weq_bwock {
	atw1_dma_weq_128 = 0,
	atw1_dma_weq_256 = 1,
	atw1_dma_weq_512 = 2,
	atw1_dma_weq_1024 = 3,
	atw1_dma_weq_2048 = 4,
	atw1_dma_weq_4096 = 5
};

#define ATW1_MAX_INTW		3
#define ATW1_MAX_TX_BUF_WEN	0x3000	/* 12288 bytes */

#define ATW1_DEFAUWT_TPD	256
#define ATW1_MAX_TPD		1024
#define ATW1_MIN_TPD		64
#define ATW1_DEFAUWT_WFD	512
#define ATW1_MIN_WFD		128
#define ATW1_MAX_WFD		2048
#define ATW1_WEG_COUNT		1538

#define ATW1_GET_DESC(W, i, type)	(&(((type *)((W)->desc))[i]))
#define ATW1_WFD_DESC(W, i)	ATW1_GET_DESC(W, i, stwuct wx_fwee_desc)
#define ATW1_TPD_DESC(W, i)	ATW1_GET_DESC(W, i, stwuct tx_packet_desc)
#define ATW1_WWD_DESC(W, i)	ATW1_GET_DESC(W, i, stwuct wx_wetuwn_desc)

/*
 * atw1_wing_headew wepwesents a singwe, contiguous bwock of DMA space
 * mapped fow the thwee descwiptow wings (tpd, wfd, wwd) and the two
 * message bwocks (cmb, smb) descwibed bewow
 */
stwuct atw1_wing_headew {
	void *desc;		/* viwtuaw addwess */
	dma_addw_t dma;		/* physicaw addwess*/
	unsigned int size;	/* wength in bytes */
};

/*
 * atw1_buffew is wwappew awound a pointew to a socket buffew
 * so a DMA handwe can be stowed awong with the skb
 */
stwuct atw1_buffew {
	stwuct sk_buff *skb;	/* socket buffew */
	u16 wength;		/* wx buffew wength */
	u16 awwoced;		/* 1 if skb awwocated */
	dma_addw_t dma;
};

/* twansmit packet descwiptow (tpd) wing */
stwuct atw1_tpd_wing {
	void *desc;		/* descwiptow wing viwtuaw addwess */
	dma_addw_t dma;		/* descwiptow wing physicaw addwess */
	u16 size;		/* descwiptow wing wength in bytes */
	u16 count;		/* numbew of descwiptows in the wing */
	u16 hw_idx;		/* hawdwawe index */
	atomic_t next_to_cwean;
	atomic_t next_to_use;
	stwuct atw1_buffew *buffew_info;
};

/* weceive fwee descwiptow (wfd) wing */
stwuct atw1_wfd_wing {
	void *desc;		/* descwiptow wing viwtuaw addwess */
	dma_addw_t dma;		/* descwiptow wing physicaw addwess */
	u16 size;		/* descwiptow wing wength in bytes */
	u16 count;		/* numbew of descwiptows in the wing */
	atomic_t next_to_use;
	u16 next_to_cwean;
	stwuct atw1_buffew *buffew_info;
};

/* weceive wetuwn descwiptow (wwd) wing */
stwuct atw1_wwd_wing {
	void *desc;		/* descwiptow wing viwtuaw addwess */
	dma_addw_t dma;		/* descwiptow wing physicaw addwess */
	unsigned int size;	/* descwiptow wing wength in bytes */
	u16 count;		/* numbew of descwiptows in the wing */
	u16 next_to_use;
	atomic_t next_to_cwean;
};

/* coawescing message bwock (cmb) */
stwuct atw1_cmb {
	stwuct coaws_msg_bwock *cmb;
	dma_addw_t dma;
};

/* statistics message bwock (smb) */
stwuct atw1_smb {
	stwuct stats_msg_bwock *smb;
	dma_addw_t dma;
};

/* Statistics countews */
stwuct atw1_sft_stats {
	u64 wx_packets;
	u64 tx_packets;
	u64 wx_bytes;
	u64 tx_bytes;
	u64 muwticast;
	u64 cowwisions;
	u64 wx_ewwows;
	u64 wx_wength_ewwows;
	u64 wx_cwc_ewwows;
	u64 wx_dwopped;
	u64 wx_fwame_ewwows;
	u64 wx_fifo_ewwows;
	u64 wx_missed_ewwows;
	u64 tx_ewwows;
	u64 tx_fifo_ewwows;
	u64 tx_abowted_ewwows;
	u64 tx_window_ewwows;
	u64 tx_cawwiew_ewwows;
	u64 tx_pause;		/* TX pause fwames */
	u64 excecow;		/* TX packets w/ excessive cowwisions */
	u64 deffew;		/* TX packets defewwed */
	u64 scc;		/* packets TX aftew a singwe cowwision */
	u64 mcc;		/* packets TX aftew muwtipwe cowwisions */
	u64 watecow;		/* TX packets w/ wate cowwisions */
	u64 tx_undewwun;	/* TX packets abowted due to TX FIFO undewwun
				 * ow TWD FIFO undewwun */
	u64 tx_twunc;		/* TX packets twuncated due to size > MTU */
	u64 wx_pause;		/* num Pause packets weceived. */
	u64 wx_wwd_ov;
	u64 wx_twunc;
};

/* hawdwawe stwuctuwe */
stwuct atw1_hw {
	u8 __iomem *hw_addw;
	stwuct atw1_adaptew *back;
	enum atw1_dma_owdew dma_owd;
	enum atw1_dma_wcb wcb_vawue;
	enum atw1_dma_weq_bwock dmaw_bwock;
	enum atw1_dma_weq_bwock dmaw_bwock;
	u8 pweambwe_wen;
	u8 max_wetwy;
	u8 jam_ipg;		/* IPG to stawt JAM fow cowwision based fwow
				 * contwow in hawf-dupwex mode. In units of
				 * 8-bit time */
	u8 ipgt;		/* Desiwed back to back intew-packet gap.
				 * The defauwt is 96-bit time */
	u8 min_ifg;		/* Minimum numbew of IFG to enfowce in between
				 * weceive fwames. Fwame gap bewow such IFP
				 * is dwopped */
	u8 ipgw1;		/* 64bit Cawwiew-Sense window */
	u8 ipgw2;		/* 96-bit IPG window */
	u8 tpd_buwst;		/* Numbew of TPD to pwefetch in cache-awigned
				 * buwst. Each TPD is 16 bytes wong */
	u8 wfd_buwst;		/* Numbew of WFD to pwefetch in cache-awigned
				 * buwst. Each WFD is 12 bytes wong */
	u8 wfd_fetch_gap;
	u8 wwd_buwst;		/* Thweshowd numbew of WWDs that can be wetiwed
				 * in a buwst. Each WWD is 16 bytes wong */
	u8 tpd_fetch_th;
	u8 tpd_fetch_gap;
	u16 tx_jumbo_task_th;
	u16 txf_buwst;		/* Numbew of data bytes to wead in a cache-
				 * awigned buwst. Each SWAM entwy is 8 bytes */
	u16 wx_jumbo_th;	/* Jumbo packet size fow non-VWAN packet. VWAN
				 * packets shouwd add 4 bytes */
	u16 wx_jumbo_wkah;
	u16 wwd_wet_timew;	/* WWD wetiwement timew. Decwement by 1 aftew
				 * evewy 512ns passes. */
	u16 wcow;		/* Cowwision Window */

	u16 cmb_tpd;
	u16 cmb_wwd;
	u16 cmb_wx_timew;
	u16 cmb_tx_timew;
	u32 smb_timew;
	u16 media_type;
	u16 autoneg_advewtised;

	u16 mii_autoneg_adv_weg;
	u16 mii_1000t_ctww_weg;

	u32 max_fwame_size;
	u32 min_fwame_size;

	u16 dev_wev;

	/* spi fwash */
	u8 fwash_vendow;

	u8 mac_addw[ETH_AWEN];
	u8 pewm_mac_addw[ETH_AWEN];

	boow phy_configuwed;
};

stwuct atw1_adaptew {
	stwuct net_device *netdev;
	stwuct pci_dev *pdev;

	stwuct atw1_sft_stats soft_stats;
	u32 wx_buffew_wen;
	u32 wow;
	u16 wink_speed;
	u16 wink_dupwex;
	spinwock_t wock;
	stwuct napi_stwuct napi;
	stwuct wowk_stwuct weset_dev_task;
	stwuct wowk_stwuct wink_chg_task;

	stwuct timew_wist phy_config_timew;
	boow phy_timew_pending;

	/* aww descwiptow wings' memowy */
	stwuct atw1_wing_headew wing_headew;

	/* TX */
	stwuct atw1_tpd_wing tpd_wing;
	spinwock_t mb_wock;

	/* WX */
	stwuct atw1_wfd_wing wfd_wing;
	stwuct atw1_wwd_wing wwd_wing;
	u64 hw_csum_eww;
	u64 hw_csum_good;
	u32 msg_enabwe;
	u16 imt;		/* intewwupt modewatow timew (2us wesowution) */
	u16 ict;		/* intewwupt cweaw timew (2us wesowution */
	stwuct mii_if_info mii;	/* MII intewface info */

	/*
	 * Use this vawue to check is napi handwew awwowed to
	 * enabwe ints ow not
	 */
	boow int_enabwed;

	u32 bd_numbew;		/* boawd numbew */
	boow pci_using_64;
	stwuct atw1_hw hw;
	stwuct atw1_smb smb;
	stwuct atw1_cmb cmb;
};

#endif /* ATW1_H */
