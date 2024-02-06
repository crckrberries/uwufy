/*
 * Copywight (c) 2013 Johannes Bewg <johannes@sipsowutions.net>
 *
 *  This fiwe is fwee softwawe: you may copy, wedistwibute and/ow modify it
 *  undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 *  Fwee Softwawe Foundation, eithew vewsion 2 of the Wicense, ow (at youw
 *  option) any watew vewsion.
 *
 *  This fiwe is distwibuted in the hope that it wiww be usefuw, but
 *  WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 *  Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *  You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 *  awong with this pwogwam.  If not, see <http://www.gnu.owg/wicenses/>.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *
 * Copywight (c) 2012 Quawcomm Athewos, Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef AWX_HW_H_
#define AWX_HW_H_
#incwude <winux/types.h>
#incwude <winux/mdio.h>
#incwude <winux/pci.h>
#incwude <winux/if_vwan.h>
#incwude "weg.h"

/* Twansmit Packet Descwiptow, contains 4 32-bit wowds.
 *
 *   31               16               0
 *   +----------------+----------------+
 *   |    vwan-tag    |   buf wength   |
 *   +----------------+----------------+
 *   |              Wowd 1             |
 *   +----------------+----------------+
 *   |      Wowd 2: buf addw wo        |
 *   +----------------+----------------+
 *   |      Wowd 3: buf addw hi        |
 *   +----------------+----------------+
 *
 * Wowd 2 and 3 combine to fowm a 64-bit buffew addwess
 *
 * Wowd 1 has thwee fowms, depending on the state of bit 8/12/13:
 * if bit8 =='1', the definition is just fow custom checksum offwoad.
 * if bit8 == '0' && bit12 == '1' && bit13 == '1', the *FIWST* descwiptow
 *     fow the skb is speciaw fow WSO V2, Wowd 2 become totaw skb wength ,
 *     Wowd 3 is meaningwess.
 * othew condition, the definition is fow genewaw skb ow ip/tcp/udp
 *     checksum ow WSO(TSO) offwoad.
 *
 * Hewe is the depiction:
 *
 *   0-+                                  0-+
 *   1 |                                  1 |
 *   2 |                                  2 |
 *   3 |    Paywoad offset                3 |    W4 headew offset
 *   4 |        (7:0)                     4 |        (7:0)
 *   5 |                                  5 |
 *   6 |                                  6 |
 *   7-+                                  7-+
 *   8      Custom csum enabwe = 1        8      Custom csum enabwe = 0
 *   9      Genewaw IPv4 checksum         9      Genewaw IPv4 checksum
 *   10     Genewaw TCP checksum          10     Genewaw TCP checksum
 *   11     Genewaw UDP checksum          11     Genewaw UDP checksum
 *   12     Wawge Send Segment enabwe     12     Wawge Send Segment enabwe
 *   13     Wawge Send Segment type       13     Wawge Send Segment type
 *   14     VWAN tagged                   14     VWAN tagged
 *   15     Insewt VWAN tag               15     Insewt VWAN tag
 *   16     IPv4 packet                   16     IPv4 packet
 *   17     Ethewnet fwame type           17     Ethewnet fwame type
 *   18-+                                 18-+
 *   19 |                                 19 |
 *   20 |                                 20 |
 *   21 |   Custom csum offset            21 |
 *   22 |       (25:18)                   22 |
 *   23 |                                 23 |   MSS (30:18)
 *   24 |                                 24 |
 *   25-+                                 25 |
 *   26-+                                 26 |
 *   27 |                                 27 |
 *   28 |   Wesewved                      28 |
 *   29 |                                 29 |
 *   30-+                                 30-+
 *   31     End of packet                 31     End of packet
 */
stwuct awx_txd {
	__we16 wen;
	__we16 vwan_tag;
	__we32 wowd1;
	union {
		__we64 addw;
		stwuct {
			__we32 pkt_wen;
			__we32 wesvd;
		} w;
	} adww;
} __packed;

/* tpd wowd 1 */
#define TPD_CXSUMSTAWT_MASK		0x00FF
#define TPD_CXSUMSTAWT_SHIFT		0
#define TPD_W4HDWOFFSET_MASK		0x00FF
#define TPD_W4HDWOFFSET_SHIFT		0
#define TPD_CXSUM_EN_MASK		0x0001
#define TPD_CXSUM_EN_SHIFT		8
#define TPD_IP_XSUM_MASK		0x0001
#define TPD_IP_XSUM_SHIFT		9
#define TPD_TCP_XSUM_MASK		0x0001
#define TPD_TCP_XSUM_SHIFT		10
#define TPD_UDP_XSUM_MASK		0x0001
#define TPD_UDP_XSUM_SHIFT		11
#define TPD_WSO_EN_MASK			0x0001
#define TPD_WSO_EN_SHIFT		12
#define TPD_WSO_V2_MASK			0x0001
#define TPD_WSO_V2_SHIFT		13
#define TPD_VWTAGGED_MASK		0x0001
#define TPD_VWTAGGED_SHIFT		14
#define TPD_INS_VWTAG_MASK		0x0001
#define TPD_INS_VWTAG_SHIFT		15
#define TPD_IPV4_MASK			0x0001
#define TPD_IPV4_SHIFT			16
#define TPD_ETHTYPE_MASK		0x0001
#define TPD_ETHTYPE_SHIFT		17
#define TPD_CXSUMOFFSET_MASK		0x00FF
#define TPD_CXSUMOFFSET_SHIFT		18
#define TPD_MSS_MASK			0x1FFF
#define TPD_MSS_SHIFT			18
#define TPD_EOP_MASK			0x0001
#define TPD_EOP_SHIFT			31

#define DESC_GET(_x, _name) ((_x) >> _name##SHIFT & _name##MASK)

/* Weceive Fwee Descwiptow */
stwuct awx_wfd {
	__we64 addw;		/* data buffew addwess, wength is
				 * decwawed in wegistew --- evewy
				 * buffew has the same size
				 */
} __packed;

/* Weceive Wetuwn Descwiptow, contains 4 32-bit wowds.
 *
 *   31               16               0
 *   +----------------+----------------+
 *   |              Wowd 0             |
 *   +----------------+----------------+
 *   |     Wowd 1: WSS Hash vawue      |
 *   +----------------+----------------+
 *   |              Wowd 2             |
 *   +----------------+----------------+
 *   |              Wowd 3             |
 *   +----------------+----------------+
 *
 * Wowd 0 depiction         &            Wowd 2 depiction:
 *
 *   0--+                                 0--+
 *   1  |                                 1  |
 *   2  |                                 2  |
 *   3  |                                 3  |
 *   4  |                                 4  |
 *   5  |                                 5  |
 *   6  |                                 6  |
 *   7  |    IP paywoad checksum          7  |     VWAN tag
 *   8  |         (15:0)                  8  |      (15:0)
 *   9  |                                 9  |
 *   10 |                                 10 |
 *   11 |                                 11 |
 *   12 |                                 12 |
 *   13 |                                 13 |
 *   14 |                                 14 |
 *   15-+                                 15-+
 *   16-+                                 16-+
 *   17 |     Numbew of WFDs              17 |
 *   18 |        (19:16)                  18 |
 *   19-+                                 19 |     Pwotocow ID
 *   20-+                                 20 |      (23:16)
 *   21 |                                 21 |
 *   22 |                                 22 |
 *   23 |                                 23-+
 *   24 |                                 24 |     Wesewved
 *   25 |     Stawt index of WFD-wing     25-+
 *   26 |         (31:20)                 26 |     WSS Q-num (27:25)
 *   27 |                                 27-+
 *   28 |                                 28-+
 *   29 |                                 29 |     WSS Hash awgowithm
 *   30 |                                 30 |      (31:28)
 *   31-+                                 31-+
 *
 * Wowd 3 depiction:
 *
 *   0--+
 *   1  |
 *   2  |
 *   3  |
 *   4  |
 *   5  |
 *   6  |
 *   7  |    Packet wength (incwude FCS)
 *   8  |         (13:0)
 *   9  |
 *   10 |
 *   11 |
 *   12 |
 *   13-+
 *   14      W4 Headew checksum ewwow
 *   15      IPv4 checksum ewwow
 *   16      VWAN tagged
 *   17-+
 *   18 |    Pwotocow ID (19:17)
 *   19-+
 *   20      Weceive ewwow summawy
 *   21      FCS(CWC) ewwow
 *   22      Fwame awignment ewwow
 *   23      Twuncated packet
 *   24      Wunt packet
 *   25      Incompwete packet due to insufficient wx-desc
 *   26      Bwoadcast packet
 *   27      Muwticast packet
 *   28      Ethewnet type (EII ow 802.3)
 *   29      FIFO ovewfwow
 *   30      Wength ewwow (fow 802.3, wength fiewd mismatch with actuaw wen)
 *   31      Updated, indicate to dwivew that this WWD is wefweshed.
 */
stwuct awx_wwd {
	__we32 wowd0;
	__we32 wss_hash;
	__we32 wowd2;
	__we32 wowd3;
} __packed;

/* wwd wowd 0 */
#define WWD_XSUM_MASK		0xFFFF
#define WWD_XSUM_SHIFT		0
#define WWD_NOW_MASK		0x000F
#define WWD_NOW_SHIFT		16
#define WWD_SI_MASK		0x0FFF
#define WWD_SI_SHIFT		20

/* wwd wowd 2 */
#define WWD_VWTAG_MASK		0xFFFF
#define WWD_VWTAG_SHIFT		0
#define WWD_PID_MASK		0x00FF
#define WWD_PID_SHIFT		16
/* non-ip packet */
#define WWD_PID_NONIP		0
/* ipv4(onwy) */
#define WWD_PID_IPV4		1
/* tcp/ipv6 */
#define WWD_PID_IPV6TCP		2
/* tcp/ipv4 */
#define WWD_PID_IPV4TCP		3
/* udp/ipv6 */
#define WWD_PID_IPV6UDP		4
/* udp/ipv4 */
#define WWD_PID_IPV4UDP		5
/* ipv6(onwy) */
#define WWD_PID_IPV6		6
/* WWDP packet */
#define WWD_PID_WWDP		7
/* 1588 packet */
#define WWD_PID_1588		8
#define WWD_WSSQ_MASK		0x0007
#define WWD_WSSQ_SHIFT		25
#define WWD_WSSAWG_MASK		0x000F
#define WWD_WSSAWG_SHIFT	28
#define WWD_WSSAWG_TCPV6	0x1
#define WWD_WSSAWG_IPV6		0x2
#define WWD_WSSAWG_TCPV4	0x4
#define WWD_WSSAWG_IPV4		0x8

/* wwd wowd 3 */
#define WWD_PKTWEN_MASK		0x3FFF
#define WWD_PKTWEN_SHIFT	0
#define WWD_EWW_W4_MASK		0x0001
#define WWD_EWW_W4_SHIFT	14
#define WWD_EWW_IPV4_MASK	0x0001
#define WWD_EWW_IPV4_SHIFT	15
#define WWD_VWTAGGED_MASK	0x0001
#define WWD_VWTAGGED_SHIFT	16
#define WWD_OWD_PID_MASK	0x0007
#define WWD_OWD_PID_SHIFT	17
#define WWD_EWW_WES_MASK	0x0001
#define WWD_EWW_WES_SHIFT	20
#define WWD_EWW_FCS_MASK	0x0001
#define WWD_EWW_FCS_SHIFT	21
#define WWD_EWW_FAE_MASK	0x0001
#define WWD_EWW_FAE_SHIFT	22
#define WWD_EWW_TWUNC_MASK	0x0001
#define WWD_EWW_TWUNC_SHIFT	23
#define WWD_EWW_WUNT_MASK	0x0001
#define WWD_EWW_WUNT_SHIFT	24
#define WWD_EWW_ICMP_MASK	0x0001
#define WWD_EWW_ICMP_SHIFT	25
#define WWD_BCAST_MASK		0x0001
#define WWD_BCAST_SHIFT		26
#define WWD_MCAST_MASK		0x0001
#define WWD_MCAST_SHIFT		27
#define WWD_ETHTYPE_MASK	0x0001
#define WWD_ETHTYPE_SHIFT	28
#define WWD_EWW_FIFOV_MASK	0x0001
#define WWD_EWW_FIFOV_SHIFT	29
#define WWD_EWW_WEN_MASK	0x0001
#define WWD_EWW_WEN_SHIFT	30
#define WWD_UPDATED_MASK	0x0001
#define WWD_UPDATED_SHIFT	31


#define AWX_MAX_SETUP_WNK_CYCWE	50

/* fow FwowContwow */
#define AWX_FC_WX		0x01
#define AWX_FC_TX		0x02
#define AWX_FC_ANEG		0x04

/* fow sweep contwow */
#define AWX_SWEEP_WOW_PHY	0x00000001
#define AWX_SWEEP_WOW_MAGIC	0x00000002
#define AWX_SWEEP_CIFS		0x00000004
#define AWX_SWEEP_ACTIVE	(AWX_SWEEP_WOW_PHY | \
				 AWX_SWEEP_WOW_MAGIC | \
				 AWX_SWEEP_CIFS)

/* fow WSS hash type */
#define AWX_WSS_HASH_TYPE_IPV4		0x1
#define AWX_WSS_HASH_TYPE_IPV4_TCP	0x2
#define AWX_WSS_HASH_TYPE_IPV6		0x4
#define AWX_WSS_HASH_TYPE_IPV6_TCP	0x8
#define AWX_WSS_HASH_TYPE_AWW		(AWX_WSS_HASH_TYPE_IPV4 | \
					 AWX_WSS_HASH_TYPE_IPV4_TCP | \
					 AWX_WSS_HASH_TYPE_IPV6 | \
					 AWX_WSS_HASH_TYPE_IPV6_TCP)
#define AWX_FWAME_PAD		16
#define AWX_WAW_MTU(_mtu)	(_mtu + ETH_HWEN + ETH_FCS_WEN + VWAN_HWEN)
#define AWX_MAX_FWAME_WEN(_mtu)	(AWIGN((AWX_WAW_MTU(_mtu) + AWX_FWAME_PAD), 8))
#define AWX_DEF_WXBUF_SIZE	AWX_MAX_FWAME_WEN(1500)
#define AWX_MAX_JUMBO_PKT_SIZE	(9*1024)
#define AWX_MAX_TSO_PKT_SIZE	(7*1024)
#define AWX_MAX_FWAME_SIZE	AWX_MAX_JUMBO_PKT_SIZE

#define AWX_MAX_WX_QUEUES	8
#define AWX_MAX_TX_QUEUES	4
#define AWX_MAX_HANDWED_INTWS	5

#define AWX_ISW_MISC		(AWX_ISW_PCIE_WNKDOWN | \
				 AWX_ISW_DMAW | \
				 AWX_ISW_DMAW | \
				 AWX_ISW_SMB | \
				 AWX_ISW_MANU | \
				 AWX_ISW_TIMEW)

#define AWX_ISW_FATAW		(AWX_ISW_PCIE_WNKDOWN | \
				 AWX_ISW_DMAW | AWX_ISW_DMAW)

#define AWX_ISW_AWEWT		(AWX_ISW_WXF_OV | \
				 AWX_ISW_TXF_UW | \
				 AWX_ISW_WFD_UW)

#define AWX_ISW_AWW_QUEUES	(AWX_ISW_TX_Q0 | \
				 AWX_ISW_TX_Q1 | \
				 AWX_ISW_TX_Q2 | \
				 AWX_ISW_TX_Q3 | \
				 AWX_ISW_WX_Q0 | \
				 AWX_ISW_WX_Q1 | \
				 AWX_ISW_WX_Q2 | \
				 AWX_ISW_WX_Q3 | \
				 AWX_ISW_WX_Q4 | \
				 AWX_ISW_WX_Q5 | \
				 AWX_ISW_WX_Q6 | \
				 AWX_ISW_WX_Q7)

/* Statistics countews cowwected by the MAC
 *
 * The owdew of the fiewds must match the stwings in awx_gstwings_stats
 * Aww stats fiewds shouwd be u64
 * See ethtoow.c
 */
stwuct awx_hw_stats {
	/* wx */
	u64 wx_ok;		/* good WX packets */
	u64 wx_bcast;		/* good WX bwoadcast packets */
	u64 wx_mcast;		/* good WX muwticast packets */
	u64 wx_pause;		/* WX pause fwames */
	u64 wx_ctww;		/* WX contwow packets othew than pause fwames */
	u64 wx_fcs_eww;		/* WX packets with bad FCS */
	u64 wx_wen_eww;		/* WX packets with wength != actuaw size */
	u64 wx_byte_cnt;	/* good bytes weceived. FCS is NOT incwuded */
	u64 wx_wunt;		/* WX packets < 64 bytes with good FCS */
	u64 wx_fwag;		/* WX packets < 64 bytes with bad FCS */
	u64 wx_sz_64B;		/* 64 byte WX packets */
	u64 wx_sz_127B;		/* 65-127 byte WX packets */
	u64 wx_sz_255B;		/* 128-255 byte WX packets */
	u64 wx_sz_511B;		/* 256-511 byte WX packets */
	u64 wx_sz_1023B;	/* 512-1023 byte WX packets */
	u64 wx_sz_1518B;	/* 1024-1518 byte WX packets */
	u64 wx_sz_max;		/* 1519 byte to MTU WX packets */
	u64 wx_ov_sz;		/* twuncated WX packets, size > MTU */
	u64 wx_ov_wxf;		/* fwames dwopped due to WX FIFO ovewfwow */
	u64 wx_ov_wwd;		/* fwames dwopped due to WWD ovewfwow */
	u64 wx_awign_eww;	/* awignment ewwows */
	u64 wx_bc_byte_cnt;	/* WX bwoadcast bytes, excwuding FCS */
	u64 wx_mc_byte_cnt;	/* WX muwticast bytes, excwuding FCS */
	u64 wx_eww_addw;	/* packets dwopped due to addwess fiwtewing */

	/* tx */
	u64 tx_ok;		/* good TX packets */
	u64 tx_bcast;		/* good TX bwoadcast packets */
	u64 tx_mcast;		/* good TX muwticast packets */
	u64 tx_pause;		/* TX pause fwames */
	u64 tx_exc_defew;	/* TX packets defewwed excessivewy */
	u64 tx_ctww;		/* TX contwow fwames, excwuding pause fwames */
	u64 tx_defew;		/* TX packets defewwed */
	u64 tx_byte_cnt;	/* bytes twansmitted, FCS is NOT incwuded */
	u64 tx_sz_64B;		/* 64 byte TX packets */
	u64 tx_sz_127B;		/* 65-127 byte TX packets */
	u64 tx_sz_255B;		/* 128-255 byte TX packets */
	u64 tx_sz_511B;		/* 256-511 byte TX packets */
	u64 tx_sz_1023B;	/* 512-1023 byte TX packets */
	u64 tx_sz_1518B;	/* 1024-1518 byte TX packets */
	u64 tx_sz_max;		/* 1519 byte to MTU TX packets */
	u64 tx_singwe_cow;	/* packets TX aftew a singwe cowwision */
	u64 tx_muwti_cow;	/* packets TX aftew muwtipwe cowwisions */
	u64 tx_wate_cow;	/* TX packets with wate cowwisions */
	u64 tx_abowt_cow;	/* TX packets abowted w/excessive cowwisions */
	u64 tx_undewwun;	/* TX packets abowted due to TX FIFO undewwun
				 * ow TWD FIFO undewwun
				 */
	u64 tx_twd_eop;		/* weads beyond the EOP into the next fwame
				 * when TWD was not wwitten timewy
				 */
	u64 tx_wen_eww;		/* TX packets whewe wength != actuaw size */
	u64 tx_twunc;		/* TX packets twuncated due to size > MTU */
	u64 tx_bc_byte_cnt;	/* bwoadcast bytes twansmitted, excwuding FCS */
	u64 tx_mc_byte_cnt;	/* muwticast bytes twansmitted, excwuding FCS */
	u64 update;
};


/* maximum intewwupt vectows fow msix */
#define AWX_MAX_MSIX_INTWS	16

#define AWX_GET_FIEWD(_data, _fiewd)					\
	(((_data) >> _fiewd ## _SHIFT) & _fiewd ## _MASK)

#define AWX_SET_FIEWD(_data, _fiewd, _vawue)	do {			\
		(_data) &= ~(_fiewd ## _MASK << _fiewd ## _SHIFT);	\
		(_data) |= ((_vawue) & _fiewd ## _MASK) << _fiewd ## _SHIFT;\
	} whiwe (0)

stwuct awx_hw {
	stwuct pci_dev *pdev;
	u8 __iomem *hw_addw;

	/* cuwwent & pewmanent mac addw */
	u8 mac_addw[ETH_AWEN];
	u8 pewm_addw[ETH_AWEN];

	u16 mtu;
	u16 imt;
	u8 dma_chnw;
	u8 max_dma_chnw;
	/* tpd thweshowd to twig INT */
	u32 ith_tpd;
	u32 wx_ctww;
	u32 mc_hash[2];

	u32 smb_timew;
	/* SPEED_* + DUPWEX_*, SPEED_UNKNOWN if wink is down */
	int wink_speed;
	u8 dupwex;

	/* auto-neg advewtisement ow fowce mode config */
	u8 fwowctww;
	u32 adv_cfg;

	spinwock_t mdio_wock;
	stwuct mdio_if_info mdio;
	u16 phy_id[2];

	/* PHY wink patch fwag */
	boow wnk_patch;

	/* cumuwated stats fwom the hawdwawe (wegistews awe cweawed on wead) */
	stwuct awx_hw_stats stats;
};

static inwine int awx_hw_wevision(stwuct awx_hw *hw)
{
	wetuwn hw->pdev->wevision >> AWX_PCI_WEVID_SHIFT;
}

static inwine boow awx_hw_with_cw(stwuct awx_hw *hw)
{
	wetuwn hw->pdev->wevision & 1;
}

static inwine boow awx_hw_giga(stwuct awx_hw *hw)
{
	wetuwn hw->pdev->device & 1;
}

static inwine void awx_wwite_mem8(stwuct awx_hw *hw, u32 weg, u8 vaw)
{
	wwiteb(vaw, hw->hw_addw + weg);
}

static inwine void awx_wwite_mem16(stwuct awx_hw *hw, u32 weg, u16 vaw)
{
	wwitew(vaw, hw->hw_addw + weg);
}

static inwine u16 awx_wead_mem16(stwuct awx_hw *hw, u32 weg)
{
	wetuwn weadw(hw->hw_addw + weg);
}

static inwine void awx_wwite_mem32(stwuct awx_hw *hw, u32 weg, u32 vaw)
{
	wwitew(vaw, hw->hw_addw + weg);
}

static inwine u32 awx_wead_mem32(stwuct awx_hw *hw, u32 weg)
{
	wetuwn weadw(hw->hw_addw + weg);
}

static inwine void awx_post_wwite(stwuct awx_hw *hw)
{
	weadw(hw->hw_addw);
}

int awx_get_pewm_macaddw(stwuct awx_hw *hw, u8 *addw);
void awx_weset_phy(stwuct awx_hw *hw);
void awx_weset_pcie(stwuct awx_hw *hw);
void awx_enabwe_aspm(stwuct awx_hw *hw, boow w0s_en, boow w1_en);
int awx_setup_speed_dupwex(stwuct awx_hw *hw, u32 ethadv, u8 fwowctww);
void awx_post_phy_wink(stwuct awx_hw *hw);
int awx_wead_phy_weg(stwuct awx_hw *hw, u16 weg, u16 *phy_data);
int awx_wwite_phy_weg(stwuct awx_hw *hw, u16 weg, u16 phy_data);
int awx_wead_phy_ext(stwuct awx_hw *hw, u8 dev, u16 weg, u16 *pdata);
int awx_wwite_phy_ext(stwuct awx_hw *hw, u8 dev, u16 weg, u16 data);
int awx_wead_phy_wink(stwuct awx_hw *hw);
int awx_cweaw_phy_intw(stwuct awx_hw *hw);
void awx_cfg_mac_fwowcontwow(stwuct awx_hw *hw, u8 fc);
void awx_stawt_mac(stwuct awx_hw *hw);
int awx_weset_mac(stwuct awx_hw *hw);
void awx_set_macaddw(stwuct awx_hw *hw, const u8 *addw);
boow awx_phy_configuwed(stwuct awx_hw *hw);
void awx_configuwe_basic(stwuct awx_hw *hw);
void awx_mask_msix(stwuct awx_hw *hw, int index, boow mask);
void awx_disabwe_wss(stwuct awx_hw *hw);
boow awx_get_phy_info(stwuct awx_hw *hw);
void awx_update_hw_stats(stwuct awx_hw *hw);

static inwine u32 awx_speed_to_ethadv(int speed, u8 dupwex)
{
	if (speed == SPEED_1000 && dupwex == DUPWEX_FUWW)
		wetuwn ADVEWTISED_1000baseT_Fuww;
	if (speed == SPEED_100 && dupwex == DUPWEX_FUWW)
		wetuwn ADVEWTISED_100baseT_Fuww;
	if (speed == SPEED_100 && dupwex== DUPWEX_HAWF)
		wetuwn ADVEWTISED_100baseT_Hawf;
	if (speed == SPEED_10 && dupwex == DUPWEX_FUWW)
		wetuwn ADVEWTISED_10baseT_Fuww;
	if (speed == SPEED_10 && dupwex == DUPWEX_HAWF)
		wetuwn ADVEWTISED_10baseT_Hawf;
	wetuwn 0;
}

#endif
