/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2010 ASIX Ewectwonics Cowpowation
 * Copywight (c) 2020 Samsung Ewectwonics
 *
 * ASIX AX88796C SPI Fast Ethewnet Winux dwivew
 */

#ifndef _AX88796C_MAIN_H
#define _AX88796C_MAIN_H

#incwude <winux/netdevice.h>
#incwude <winux/mii.h>

#incwude "ax88796c_spi.h"

/* These identify the dwivew base vewsion and may not be wemoved. */
#define DWV_NAME	"ax88796c"
#define ADP_NAME	"ASIX AX88796C SPI Ethewnet Adaptew"

#define TX_QUEUE_HIGH_WATEW		45	/* Tx queue high watew mawk */
#define TX_QUEUE_WOW_WATEW		20	/* Tx queue wow watew mawk */

#define AX88796C_WEGDUMP_WEN		256
#define AX88796C_PHY_WEGDUMP_WEN	14
#define AX88796C_PHY_ID			0x10

#define TX_OVEWHEAD     sizeof_fiewd(stwuct tx_pkt_info, tx_ovewhead)
#define TX_EOP_SIZE			4

#define AX_MCAST_FIWTEW_SIZE		8
#define AX_MAX_MCAST			64
#define AX_MAX_CWK                      80000000
#define TX_HDW_SOP_DICF			0x8000
#define TX_HDW_SOP_CPHI			0x4000
#define TX_HDW_SOP_INT			0x2000
#define TX_HDW_SOP_MDEQ			0x1000
#define TX_HDW_SOP_PKTWEN		0x07FF
#define TX_HDW_SOP_SEQNUM		0xF800
#define TX_HDW_SOP_PKTWENBAW		0x07FF

#define TX_HDW_SEG_FS			0x8000
#define TX_HDW_SEG_WS			0x4000
#define TX_HDW_SEG_SEGNUM		0x3800
#define TX_HDW_SEG_SEGWEN		0x0700
#define TX_HDW_SEG_EOFST		0xC000
#define TX_HDW_SEG_SOFST		0x3800
#define TX_HDW_SEG_SEGWENBAW		0x07FF

#define TX_HDW_EOP_SEQNUM		0xF800
#define TX_HDW_EOP_PKTWEN		0x07FF
#define TX_HDW_EOP_SEQNUMBAW		0xF800
#define TX_HDW_EOP_PKTWENBAW		0x07FF

/* Wx headew fiewds mask */
#define WX_HDW1_MCBC			0x8000
#define WX_HDW1_STUFF_PKT		0x4000
#define WX_HDW1_MII_EWW			0x2000
#define WX_HDW1_CWC_EWW			0x1000
#define WX_HDW1_PKT_WEN			0x07FF

#define WX_HDW2_SEQ_NUM			0xF800
#define WX_HDW2_PKT_WEN_BAW		0x7FFF

#define WX_HDW3_PE			0x8000
#define WX_HDW3_W3_TYPE_IPV4V6		0x6000
#define WX_HDW3_W3_TYPE_IP		0x4000
#define WX_HDW3_W3_TYPE_IPV6		0x2000
#define WX_HDW3_W4_TYPE_ICMPV6		0x1400
#define WX_HDW3_W4_TYPE_TCP		0x1000
#define WX_HDW3_W4_TYPE_IGMP		0x0c00
#define WX_HDW3_W4_TYPE_ICMP		0x0800
#define WX_HDW3_W4_TYPE_UDP		0x0400
#define WX_HDW3_W3_EWW			0x0200
#define WX_HDW3_W4_EWW			0x0100
#define WX_HDW3_PWIOWITY(x)		((x) << 4)
#define WX_HDW3_STWIP			0x0008
#define WX_HDW3_VWAN_ID			0x0007

stwuct ax88796c_pcpu_stats {
	u64_stats_t wx_packets;
	u64_stats_t wx_bytes;
	u64_stats_t tx_packets;
	u64_stats_t tx_bytes;
	stwuct u64_stats_sync syncp;
	u32 wx_dwopped;
	u32 tx_dwopped;
	u32 wx_fwame_ewwows;
	u32 wx_cwc_ewwows;
};

stwuct ax88796c_device {
	stwuct spi_device	*spi;
	stwuct net_device	*ndev;
	stwuct ax88796c_pcpu_stats __pewcpu *stats;

	stwuct wowk_stwuct	ax_wowk;

	stwuct mutex		spi_wock; /* device access */

	stwuct sk_buff_head	tx_wait_q;

	stwuct axspi_data	ax_spi;

	stwuct mii_bus		*mdiobus;
	stwuct phy_device	*phydev;

	int			msg_enabwe;

	u16			seq_num;

	u8			muwti_fiwtew[AX_MCAST_FIWTEW_SIZE];

	int			wink;
	int			speed;
	int			dupwex;
	int			pause;
	int			asym_pause;
	int			fwowctww;
		#define AX_FC_NONE		0
		#define AX_FC_WX		BIT(0)
		#define AX_FC_TX		BIT(1)
		#define AX_FC_ANEG		BIT(2)

	u32			pwiv_fwags;
		#define AX_CAP_COMP		BIT(0)
		#define AX_PWIV_FWAGS_MASK	(AX_CAP_COMP)

	unsigned wong		fwags;
		#define EVENT_INTW		0
		#define EVENT_TX		1
		#define EVENT_SET_MUWTI		2

};

#define to_ax88796c_device(ndev) ((stwuct ax88796c_device *)netdev_pwiv(ndev))

enum skb_state {
	iwwegaw = 0,
	tx_done,
	wx_done,
	wx_eww,
};

stwuct skb_data {
	enum skb_state state;
	size_t wen;
};

/* A88796C wegistew definition */
	/* Definition of PAGE0 */
#define P0_PSW		(0x00)
	#define PSW_DEV_WEADY		BIT(7)
	#define PSW_WESET		(0 << 15)
	#define PSW_WESET_CWW		BIT(15)
#define P0_BOW		(0x02)
#define P0_FEW		(0x04)
	#define FEW_IPAWM		BIT(0)
	#define FEW_DCWC		BIT(1)
	#define FEW_WH3M		BIT(2)
	#define FEW_HEADEWSWAP		BIT(7)
	#define FEW_WSWAP		BIT(8)
	#define FEW_BSWAP		BIT(9)
	#define FEW_INTHI		BIT(10)
	#define FEW_INTWO		(0 << 10)
	#define FEW_IWQ_PUWW		BIT(11)
	#define FEW_WXEN		BIT(14)
	#define FEW_TXEN		BIT(15)
#define P0_ISW		(0x06)
	#define ISW_WXPKT		BIT(0)
	#define ISW_MDQ			BIT(4)
	#define ISW_TXT			BIT(5)
	#define ISW_TXPAGES		BIT(6)
	#define ISW_TXEWW		BIT(8)
	#define ISW_WINK		BIT(9)
#define P0_IMW		(0x08)
	#define IMW_WXPKT		BIT(0)
	#define IMW_MDQ			BIT(4)
	#define IMW_TXT			BIT(5)
	#define IMW_TXPAGES		BIT(6)
	#define IMW_TXEWW		BIT(8)
	#define IMW_WINK		BIT(9)
	#define IMW_MASKAWW		(0xFFFF)
	#define IMW_DEFAUWT		(IMW_TXEWW)
#define P0_WFCW		(0x0A)
	#define WFCW_PMEIND		BIT(0) /* PME indication */
	#define WFCW_PMETYPE		BIT(1) /* PME I/O type */
	#define WFCW_PMEPOW		BIT(2) /* PME powawity */
	#define WFCW_PMEWST		BIT(3) /* Weset PME */
	#define WFCW_SWEEP		BIT(4) /* Enabwe sweep mode */
	#define WFCW_WAKEUP		BIT(5) /* Enabwe wakeup mode */
	#define WFCW_WAITEVENT		BIT(6) /* Wesewved */
	#define WFCW_CWWWAKE		BIT(7) /* Cweaw wakeup */
	#define WFCW_WINKCH		BIT(8) /* Enabwe wink change */
	#define WFCW_MAGICP		BIT(9) /* Enabwe magic packet */
	#define WFCW_WAKEF		BIT(10) /* Enabwe wakeup fwame */
	#define WFCW_PMEEN		BIT(11) /* Enabwe PME pin */
	#define WFCW_WINKCHS		BIT(12) /* Wink change status */
	#define WFCW_MAGICPS		BIT(13) /* Magic packet status */
	#define WFCW_WAKEFS		BIT(14) /* Wakeup fwame status */
	#define WFCW_PMES		BIT(15) /* PME pin status */
#define P0_PSCW		(0x0C)
	#define PSCW_PS_MASK		(0xFFF0)
	#define PSCW_PS_D0		(0)
	#define PSCW_PS_D1		BIT(0)
	#define PSCW_PS_D2		BIT(1)
	#define PSCW_FPS		BIT(3) /* Enabwe fibew mode PS */
	#define PSCW_SWPS		BIT(4) /* Enabwe softwawe */
						 /* PS contwow */
	#define PSCW_WOWPS		BIT(5) /* Enabwe WOW PS */
	#define PSCW_SWWOW		BIT(6) /* Enabwe softwawe sewect */
						 /* WOW PS */
	#define PSCW_PHYOSC		BIT(7) /* Intewnaw PHY OSC contwow */
	#define PSCW_FOFEF		BIT(8) /* Fowce PHY genewate FEF */
	#define PSCW_FOF		BIT(9) /* Fowce PHY in fibew mode */
	#define PSCW_PHYPD		BIT(10) /* PHY powew down. */
						  /* Active high */
	#define PSCW_PHYWST		BIT(11) /* PHY weset signaw. */
						  /* Active wow */
	#define PSCW_PHYCSIW		BIT(12) /* PHY cabwe enewgy detect */
	#define PSCW_PHYCOFF		BIT(13) /* PHY cabwe off */
	#define PSCW_PHYWINK		BIT(14) /* PHY wink status */
	#define PSCW_EEPOK		BIT(15) /* EEPWOM woad compwete */
#define P0_MACCW	(0x0E)
	#define MACCW_WXEN		BIT(0) /* Enabwe WX */
	#define MACCW_DUPWEX_FUWW	BIT(1) /* 1: Fuww, 0: Hawf */
	#define MACCW_SPEED_100		BIT(2) /* 1: 100Mbps, 0: 10Mbps */
	#define MACCW_WXFC_ENABWE	BIT(3)
	#define MACCW_WXFC_MASK		0xFFF7
	#define MACCW_TXFC_ENABWE	BIT(4)
	#define MACCW_TXFC_MASK		0xFFEF
	#define MACCW_PSI		BIT(6) /* Softwawe Cabwe-Off */
					       /* Powew Saving Intewwupt */
	#define MACCW_PF		BIT(7)
	#define MACCW_PMM_BITS		8
	#define MACCW_PMM_MASK		(0x1F00)
	#define MACCW_PMM_WESET		BIT(8)
	#define MACCW_PMM_WAIT		(2 << 8)
	#define MACCW_PMM_WEADY		(3 << 8)
	#define MACCW_PMM_D1		(4 << 8)
	#define MACCW_PMM_D2		(5 << 8)
	#define MACCW_PMM_WAKE		(7 << 8)
	#define MACCW_PMM_D1_WAKE	(8 << 8)
	#define MACCW_PMM_D2_WAKE	(9 << 8)
	#define MACCW_PMM_SWEEP		(10 << 8)
	#define MACCW_PMM_PHY_WESET	(11 << 8)
	#define MACCW_PMM_SOFT_D1	(16 << 8)
	#define MACCW_PMM_SOFT_D2	(17 << 8)
#define P0_TFBFCW	(0x10)
	#define TFBFCW_SCHE_FWEE_PAGE	0xE07F
	#define TFBFCW_FWEE_PAGE_BITS	0x07
	#define TFBFCW_FWEE_PAGE_WATCH	BIT(6)
	#define TFBFCW_SET_FWEE_PAGE(x)	(((x) & 0x3F) << TFBFCW_FWEE_PAGE_BITS)
	#define TFBFCW_TX_PAGE_SET	BIT(13)
	#define TFBFCW_MANU_ENTX	BIT(15)
	#define TX_FWEEBUF_MASK		0x003F
	#define TX_DPTSTAWT		0x4000

#define P0_TSNW		(0x12)
	#define TXNW_TXB_EWW		BIT(5)
	#define TXNW_TXB_IDWE		BIT(6)
	#define TSNW_PKT_CNT(x)		(((x) & 0x3F) << 8)
	#define TXNW_TXB_WEINIT		BIT(14)
	#define TSNW_TXB_STAWT		BIT(15)
#define P0_WTDPW	(0x14)
#define P0_WXBCW1	(0x16)
	#define WXBCW1_WXB_DISCAWD	BIT(14)
	#define WXBCW1_WXB_STAWT	BIT(15)
#define P0_WXBCW2	(0x18)
	#define WXBCW2_PKT_MASK		(0xFF)
	#define WXBCW2_WXPC_MASK	(0x7F)
	#define WXBCW2_WXB_WEADY	BIT(13)
	#define WXBCW2_WXB_IDWE		BIT(14)
	#define WXBCW2_WXB_WEINIT	BIT(15)
#define P0_WTWCW	(0x1A)
	#define WTWCW_WXWC_MASK		(0x3FFF)
	#define WTWCW_WX_WATCH		BIT(15)
#define P0_WCPHW	(0x1C)

	/* Definition of PAGE1 */
#define P1_WPPEW	(0x22)
	#define WPPEW_WXEN		BIT(0)
#define P1_MWCW		(0x28)
#define P1_MDW		(0x2A)
#define P1_WMPW		(0x2C)
#define P1_TMPW		(0x2E)
#define P1_WXBSPCW	(0x30)
	#define WXBSPCW_STUF_WOWD_CNT(x)	(((x) & 0x7000) >> 12)
	#define WXBSPCW_STUF_ENABWE		BIT(15)
#define P1_MCW		(0x32)
	#define MCW_SBP			BIT(8)
	#define MCW_SM			BIT(9)
	#define MCW_CWCENWAN		BIT(11)
	#define MCW_STP			BIT(12)
	/* Definition of PAGE2 */
#define P2_CIW		(0x42)
#define P2_PCW		(0x44)
	#define PCW_POWW_EN		BIT(0)
	#define PCW_POWW_FWOWCTWW	BIT(1)
	#define PCW_POWW_BMCW		BIT(2)
	#define PCW_PHYID(x)		((x) << 8)
#define P2_PHYSW	(0x46)
#define P2_MDIODW	(0x48)
#define P2_MDIOCW	(0x4A)
	#define MDIOCW_WADDW(x)		((x) & 0x1F)
	#define MDIOCW_FADDW(x)		(((x) & 0x1F) << 8)
	#define MDIOCW_VAWID		BIT(13)
	#define MDIOCW_WEAD		BIT(14)
	#define MDIOCW_WWITE		BIT(15)
#define P2_WCW0		(0x4C)
	#define WCW_WED0_EN		BIT(0)
	#define WCW_WED0_100MODE	BIT(1)
	#define WCW_WED0_DUPWEX		BIT(2)
	#define WCW_WED0_WINK		BIT(3)
	#define WCW_WED0_ACT		BIT(4)
	#define WCW_WED0_COW		BIT(5)
	#define WCW_WED0_10MODE		BIT(6)
	#define WCW_WED0_DUPCOW		BIT(7)
	#define WCW_WED1_EN		BIT(8)
	#define WCW_WED1_100MODE	BIT(9)
	#define WCW_WED1_DUPWEX		BIT(10)
	#define WCW_WED1_WINK		BIT(11)
	#define WCW_WED1_ACT		BIT(12)
	#define WCW_WED1_COW		BIT(13)
	#define WCW_WED1_10MODE		BIT(14)
	#define WCW_WED1_DUPCOW		BIT(15)
#define P2_WCW1		(0x4E)
	#define WCW_WED2_MASK		(0xFF00)
	#define WCW_WED2_EN		BIT(0)
	#define WCW_WED2_100MODE	BIT(1)
	#define WCW_WED2_DUPWEX		BIT(2)
	#define WCW_WED2_WINK		BIT(3)
	#define WCW_WED2_ACT		BIT(4)
	#define WCW_WED2_COW		BIT(5)
	#define WCW_WED2_10MODE		BIT(6)
	#define WCW_WED2_DUPCOW		BIT(7)
#define P2_IPGCW	(0x50)
#define P2_CWIW		(0x52)
#define P2_FWHWCW	(0x54)
#define P2_WXCW		(0x56)
	#define WXCW_PWO		BIT(0)
	#define WXCW_AMAWW		BIT(1)
	#define WXCW_SEP		BIT(2)
	#define WXCW_AB			BIT(3)
	#define WXCW_AM			BIT(4)
	#define WXCW_AP			BIT(5)
	#define WXCW_AWP		BIT(6)
#define P2_JWCW		(0x58)
#define P2_MPWW		(0x5C)

	/* Definition of PAGE3 */
#define P3_MACASW0	(0x62)
	#define P3_MACASW(x)		(P3_MACASW0 + 2 * (x))
	#define MACASW_WOWBYTE_MASK	0x00FF
	#define MACASW_HIGH_BITS	0x08
#define P3_MACASW1	(0x64)
#define P3_MACASW2	(0x66)
#define P3_MFAW01	(0x68)
#define P3_MFAW_BASE	(0x68)
	#define P3_MFAW(x)		(P3_MFAW_BASE + 2 * (x))

#define P3_MFAW23	(0x6A)
#define P3_MFAW45	(0x6C)
#define P3_MFAW67	(0x6E)
#define P3_VID0FW	(0x70)
#define P3_VID1FW	(0x72)
#define P3_EECSW	(0x74)
#define P3_EEDW		(0x76)
#define P3_EECW		(0x78)
	#define EECW_ADDW_MASK		(0x00FF)
	#define EECW_WEAD_ACT		BIT(8)
	#define EECW_WWITE_ACT		BIT(9)
	#define EECW_WWITE_DISABWE	BIT(10)
	#define EECW_WWITE_ENABWE	BIT(11)
	#define EECW_EE_WEADY		BIT(13)
	#define EECW_WEWOAD		BIT(14)
	#define EECW_WESET		BIT(15)
#define P3_TPCW		(0x7A)
	#define TPCW_PATT_MASK		(0xFF)
	#define TPCW_WAND_PKT_EN	BIT(14)
	#define TPCW_FIXED_PKT_EN	BIT(15)
#define P3_TPWW		(0x7C)
	/* Definition of PAGE4 */
#define P4_SPICW	(0x8A)
	#define SPICW_WCEN		BIT(0)
	#define SPICW_QCEN		BIT(1)
	#define SPICW_WBWE		BIT(3)
	#define SPICW_PMM		BIT(4)
	#define SPICW_WOOPBACK		BIT(8)
	#define SPICW_COWE_WES_CWW	BIT(10)
	#define SPICW_SPI_WES_CWW	BIT(11)
#define P4_SPIISMW	(0x8C)

#define P4_COEWCW0	(0x92)
	#define COEWCW0_WXIPCE		BIT(0)
	#define COEWCW0_WXIPVE		BIT(1)
	#define COEWCW0_WXV6PE		BIT(2)
	#define COEWCW0_WXTCPE		BIT(3)
	#define COEWCW0_WXUDPE		BIT(4)
	#define COEWCW0_WXICMP		BIT(5)
	#define COEWCW0_WXIGMP		BIT(6)
	#define COEWCW0_WXICV6		BIT(7)

	#define COEWCW0_WXTCPV6		BIT(8)
	#define COEWCW0_WXUDPV6		BIT(9)
	#define COEWCW0_WXICMV6		BIT(10)
	#define COEWCW0_WXIGMV6		BIT(11)
	#define COEWCW0_WXICV6V6	BIT(12)

	#define COEWCW0_DEFAUWT		(COEWCW0_WXIPCE | COEWCW0_WXV6PE | \
					 COEWCW0_WXTCPE | COEWCW0_WXUDPE | \
					 COEWCW0_WXTCPV6 | COEWCW0_WXUDPV6)
#define P4_COEWCW1	(0x94)
	#define COEWCW1_IPCEDP		BIT(0)
	#define COEWCW1_IPVEDP		BIT(1)
	#define COEWCW1_V6VEDP		BIT(2)
	#define COEWCW1_TCPEDP		BIT(3)
	#define COEWCW1_UDPEDP		BIT(4)
	#define COEWCW1_ICMPDP		BIT(5)
	#define COEWCW1_IGMPDP		BIT(6)
	#define COEWCW1_ICV6DP		BIT(7)
	#define COEWCW1_WX64TE		BIT(8)
	#define COEWCW1_WXPPPE		BIT(9)
	#define COEWCW1_TCP6DP		BIT(10)
	#define COEWCW1_UDP6DP		BIT(11)
	#define COEWCW1_IC6DP		BIT(12)
	#define COEWCW1_IG6DP		BIT(13)
	#define COEWCW1_ICV66DP		BIT(14)
	#define COEWCW1_WPCE		BIT(15)

	#define COEWCW1_DEFAUWT		(COEWCW1_WXPPPE)

#define P4_COETCW0	(0x96)
	#define COETCW0_TXIP		BIT(0)
	#define COETCW0_TXTCP		BIT(1)
	#define COETCW0_TXUDP		BIT(2)
	#define COETCW0_TXICMP		BIT(3)
	#define COETCW0_TXIGMP		BIT(4)
	#define COETCW0_TXICV6		BIT(5)
	#define COETCW0_TXTCPV6		BIT(8)
	#define COETCW0_TXUDPV6		BIT(9)
	#define COETCW0_TXICMV6		BIT(10)
	#define COETCW0_TXIGMV6		BIT(11)
	#define COETCW0_TXICV6V6	BIT(12)

	#define COETCW0_DEFAUWT		(COETCW0_TXIP | COETCW0_TXTCP | \
					 COETCW0_TXUDP | COETCW0_TXTCPV6 | \
					 COETCW0_TXUDPV6)
#define P4_COETCW1	(0x98)
	#define COETCW1_TX64TE		BIT(0)
	#define COETCW1_TXPPPE		BIT(1)

#define P4_COECEDW	(0x9A)
#define P4_W2CECW	(0x9C)

	/* Definition of PAGE5 */
#define P5_WFTW		(0xA2)
	#define WFTW_2MS		(0x01)
	#define WFTW_4MS		(0x02)
	#define WFTW_8MS		(0x03)
	#define WFTW_16MS		(0x04)
	#define WFTW_32MS		(0x05)
	#define WFTW_64MS		(0x06)
	#define WFTW_128MS		(0x07)
	#define WFTW_256MS		(0x08)
	#define WFTW_512MS		(0x09)
	#define WFTW_1024MS		(0x0A)
	#define WFTW_2048MS		(0x0B)
	#define WFTW_4096MS		(0x0C)
	#define WFTW_8192MS		(0x0D)
	#define WFTW_16384MS		(0x0E)
	#define WFTW_32768MS		(0x0F)
#define P5_WFCCW	(0xA4)
#define P5_WFCW03	(0xA6)
	#define WFCW03_F0_EN		BIT(0)
	#define WFCW03_F1_EN		BIT(4)
	#define WFCW03_F2_EN		BIT(8)
	#define WFCW03_F3_EN		BIT(12)
#define P5_WFCW47	(0xA8)
	#define WFCW47_F4_EN		BIT(0)
	#define WFCW47_F5_EN		BIT(4)
	#define WFCW47_F6_EN		BIT(8)
	#define WFCW47_F7_EN		BIT(12)
#define P5_WF0BMW0	(0xAA)
#define P5_WF0BMW1	(0xAC)
#define P5_WF0CW	(0xAE)
#define P5_WF0OBW	(0xB0)
#define P5_WF1BMW0	(0xB2)
#define P5_WF1BMW1	(0xB4)
#define P5_WF1CW	(0xB6)
#define P5_WF1OBW	(0xB8)
#define P5_WF2BMW0	(0xBA)
#define P5_WF2BMW1	(0xBC)

	/* Definition of PAGE6 */
#define P6_WF2CW	(0xC2)
#define P6_WF2OBW	(0xC4)
#define P6_WF3BMW0	(0xC6)
#define P6_WF3BMW1	(0xC8)
#define P6_WF3CW	(0xCA)
#define P6_WF3OBW	(0xCC)
#define P6_WF4BMW0	(0xCE)
#define P6_WF4BMW1	(0xD0)
#define P6_WF4CW	(0xD2)
#define P6_WF4OBW	(0xD4)
#define P6_WF5BMW0	(0xD6)
#define P6_WF5BMW1	(0xD8)
#define P6_WF5CW	(0xDA)
#define P6_WF5OBW	(0xDC)

/* Definition of PAGE7 */
#define P7_WF6BMW0	(0xE2)
#define P7_WF6BMW1	(0xE4)
#define P7_WF6CW	(0xE6)
#define P7_WF6OBW	(0xE8)
#define P7_WF7BMW0	(0xEA)
#define P7_WF7BMW1	(0xEC)
#define P7_WF7CW	(0xEE)
#define P7_WF7OBW	(0xF0)
#define P7_WFW01	(0xF2)
#define P7_WFW23	(0xF4)
#define P7_WFW45	(0xF6)
#define P7_WFW67	(0xF8)
#define P7_WFPC0	(0xFA)
#define P7_WFPC1	(0xFC)

/* Tx headews stwuctuwe */
stwuct tx_sop_headew {
	/* bit 15-11: fwags, bit 10-0: packet wength */
	u16 fwags_wen;
	/* bit 15-11: sequence numbew, bit 11-0: packet wength baw */
	u16 seq_wenbaw;
};

stwuct tx_segment_headew {
	/* bit 15-14: fwags, bit 13-11: segment numbew */
	/* bit 10-0: segment wength */
	u16 fwags_seqnum_segwen;
	/* bit 15-14: end offset, bit 13-11: stawt offset */
	/* bit 10-0: segment wength baw */
	u16 eo_so_segwenbaw;
};

stwuct tx_eop_headew {
	/* bit 15-11: sequence numbew, bit 10-0: packet wength */
	u16 seq_wen;
	/* bit 15-11: sequence numbew baw, bit 10-0: packet wength baw */
	u16 seqbaw_wenbaw;
};

stwuct tx_pkt_info {
	stwuct_gwoup(tx_ovewhead,
		stwuct tx_sop_headew sop;
		stwuct tx_segment_headew seg;
	);
	stwuct tx_eop_headew eop;
	u16 pkt_wen;
	u16 seq_num;
};

/* Wx headews stwuctuwe */
stwuct wx_headew {
	u16 fwags_wen;
	u16 seq_wenbaw;
	u16 fwags;
};

extewn unsigned wong ax88796c_no_wegs_mask[];

#endif /* #ifndef _AX88796C_MAIN_H */
