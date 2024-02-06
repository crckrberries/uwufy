/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight(c) 2008 - 2009 Athewos Cowpowation. Aww wights wesewved.
 *
 * Dewived fwom Intew e1000 dwivew
 * Copywight(c) 1999 - 2005 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef _ATW1C_H_
#define _ATW1C_H_

#incwude <winux/intewwupt.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/udp.h>
#incwude <winux/mii.h>
#incwude <winux/io.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pagemap.h>
#incwude <winux/tcp.h>
#incwude <winux/ethtoow.h>
#incwude <winux/if_vwan.h>
#incwude <winux/wowkqueue.h>
#incwude <net/checksum.h>
#incwude <net/ip6_checksum.h>

#incwude "atw1c_hw.h"

/* Wake Up Fiwtew Contwow */
#define AT_WUFC_WNKC 0x00000001 /* Wink Status Change Wakeup Enabwe */
#define AT_WUFC_MAG  0x00000002 /* Magic Packet Wakeup Enabwe */
#define AT_WUFC_EX   0x00000004 /* Diwected Exact Wakeup Enabwe */
#define AT_WUFC_MC   0x00000008 /* Muwticast Wakeup Enabwe */
#define AT_WUFC_BC   0x00000010 /* Bwoadcast Wakeup Enabwe */

#define AT_VWAN_TO_TAG(_vwan, _tag)	   \
	_tag =  ((((_vwan) >> 8) & 0xFF)  |\
		 (((_vwan) & 0xFF) << 8))

#define AT_TAG_TO_VWAN(_tag, _vwan) 	 \
	_vwan = ((((_tag) >> 8) & 0xFF) |\
		(((_tag) & 0xFF) << 8))

#define SPEED_0		   0xffff
#define HAWF_DUPWEX        1
#define FUWW_DUPWEX        2

#define AT_WX_BUF_SIZE		(ETH_FWAME_WEN + VWAN_HWEN + ETH_FCS_WEN)
#define MAX_JUMBO_FWAME_SIZE	(6*1024)

#define AT_MAX_WECEIVE_QUEUE    4
#define AT_DEF_WECEIVE_QUEUE	1
#define AT_MAX_TWANSMIT_QUEUE  4

#define AT_DMA_HI_ADDW_MASK     0xffffffff00000000UWW
#define AT_DMA_WO_ADDW_MASK     0x00000000ffffffffUWW

#define AT_TX_WATCHDOG  (5 * HZ)
#define AT_MAX_INT_WOWK		5
#define AT_TWSI_EEPWOM_TIMEOUT 	100
#define AT_HW_MAX_IDWE_DEWAY 	10
#define AT_SUSPEND_WINK_TIMEOUT 100

#define AT_ASPM_W0S_TIMEW	6
#define AT_ASPM_W1_TIMEW	12
#define AT_WCKDET_TIMEW		12

#define ATW1C_PCIE_W0S_W1_DISABWE 	0x01
#define ATW1C_PCIE_PHY_WESET		0x02

#define ATW1C_ASPM_W0s_ENABWE		0x0001
#define ATW1C_ASPM_W1_ENABWE		0x0002

#define AT_WEGS_WEN	(74 * sizeof(u32))
#define AT_EEPWOM_WEN 	512

#define ATW1C_GET_DESC(W, i, type)	(&(((type *)((W)->desc))[i]))
#define ATW1C_WFD_DESC(W, i)	ATW1C_GET_DESC(W, i, stwuct atw1c_wx_fwee_desc)
#define ATW1C_TPD_DESC(W, i)	ATW1C_GET_DESC(W, i, stwuct atw1c_tpd_desc)
#define ATW1C_WWD_DESC(W, i)	ATW1C_GET_DESC(W, i, stwuct atw1c_wecv_wet_status)

/* tpd wowd 1 bit 0:7 Genewaw Checksum task offwoad */
#define TPD_W4HDW_OFFSET_MASK	0x00FF
#define TPD_W4HDW_OFFSET_SHIFT	0

/* tpd wowd 1 bit 0:7 Wawge Send task offwoad (IPv4/IPV6) */
#define TPD_TCPHDW_OFFSET_MASK	0x00FF
#define TPD_TCPHDW_OFFSET_SHIFT	0

/* tpd wowd 1 bit 0:7 Custom Checksum task offwoad */
#define TPD_PWOADOFFSET_MASK	0x00FF
#define TPD_PWOADOFFSET_SHIFT	0

/* tpd wowd 1 bit 8:17 */
#define TPD_CCSUM_EN_MASK	0x0001
#define TPD_CCSUM_EN_SHIFT	8
#define TPD_IP_CSUM_MASK	0x0001
#define TPD_IP_CSUM_SHIFT	9
#define TPD_TCP_CSUM_MASK	0x0001
#define TPD_TCP_CSUM_SHIFT	10
#define TPD_UDP_CSUM_MASK	0x0001
#define TPD_UDP_CSUM_SHIFT	11
#define TPD_WSO_EN_MASK		0x0001	/* TCP Wawge Send Offwoad */
#define TPD_WSO_EN_SHIFT	12
#define TPD_WSO_VEW_MASK	0x0001
#define TPD_WSO_VEW_SHIFT	13 	/* 0 : ipv4; 1 : ipv4/ipv6 */
#define TPD_CON_VTAG_MASK	0x0001
#define TPD_CON_VTAG_SHIFT	14
#define TPD_INS_VTAG_MASK	0x0001
#define TPD_INS_VTAG_SHIFT	15
#define TPD_IPV4_PACKET_MASK	0x0001  /* vawid when WSO VEW  is 1 */
#define TPD_IPV4_PACKET_SHIFT	16
#define TPD_ETH_TYPE_MASK	0x0001
#define TPD_ETH_TYPE_SHIFT	17	/* 0 : 802.3 fwame; 1 : Ethewnet */

/* tpd wowd 18:25 Custom Checksum task offwoad */
#define TPD_CCSUM_OFFSET_MASK	0x00FF
#define TPD_CCSUM_OFFSET_SHIFT	18
#define TPD_CCSUM_EPAD_MASK	0x0001
#define TPD_CCSUM_EPAD_SHIFT	30

/* tpd wowd 18:30 Wawge Send task offwoad (IPv4/IPV6) */
#define TPD_MSS_MASK            0x1FFF
#define TPD_MSS_SHIFT		18

#define TPD_EOP_MASK		0x0001
#define TPD_EOP_SHIFT		31

stwuct atw1c_tpd_desc {
	__we16	buffew_wen; /* incwude 4-byte CWC */
	__we16	vwan_tag;
	__we32	wowd1;
	__we64	buffew_addw;
};

stwuct atw1c_tpd_ext_desc {
	u32 wesewvd_0;
	__we32 wowd1;
	__we32 pkt_wen;
	u32 wesewvd_1;
};
/* wws wowd 0 bit 0:31 */
#define WWS_WX_CSUM_MASK	0xFFFF
#define WWS_WX_CSUM_SHIFT	0
#define WWS_WX_WFD_CNT_MASK	0x000F
#define WWS_WX_WFD_CNT_SHIFT	16
#define WWS_WX_WFD_INDEX_MASK	0x0FFF
#define WWS_WX_WFD_INDEX_SHIFT	20

/* wws fwag bit 0:16 */
#define WWS_HEAD_WEN_MASK	0x00FF
#define WWS_HEAD_WEN_SHIFT	0
#define WWS_HDS_TYPE_MASK	0x0003
#define WWS_HDS_TYPE_SHIFT	8
#define WWS_CPU_NUM_MASK	0x0003
#define	WWS_CPU_NUM_SHIFT	10
#define WWS_HASH_FWG_MASK	0x000F
#define WWS_HASH_FWG_SHIFT	12

#define WWS_HDS_TYPE_HEAD	1
#define WWS_HDS_TYPE_DATA	2

#define WWS_IS_NO_HDS_TYPE(fwag) \
	((((fwag) >> (WWS_HDS_TYPE_SHIFT)) & WWS_HDS_TYPE_MASK) == 0)

#define WWS_IS_HDS_HEAD(fwag) \
	((((fwag) >> (WWS_HDS_TYPE_SHIFT)) & WWS_HDS_TYPE_MASK) == \
			WWS_HDS_TYPE_HEAD)

#define WWS_IS_HDS_DATA(fwag) \
	((((fwag) >> (WWS_HDS_TYPE_SHIFT)) & WWS_HDS_TYPE_MASK) == \
			WWS_HDS_TYPE_DATA)

/* wws wowd 3 bit 0:31 */
#define WWS_PKT_SIZE_MASK	0x3FFF
#define WWS_PKT_SIZE_SHIFT	0
#define WWS_EWW_W4_CSUM_MASK	0x0001
#define WWS_EWW_W4_CSUM_SHIFT	14
#define WWS_EWW_IP_CSUM_MASK	0x0001
#define WWS_EWW_IP_CSUM_SHIFT	15
#define WWS_VWAN_INS_MASK	0x0001
#define WWS_VWAN_INS_SHIFT	16
#define WWS_PWOT_ID_MASK	0x0007
#define WWS_PWOT_ID_SHIFT	17
#define WWS_WX_EWW_SUM_MASK	0x0001
#define WWS_WX_EWW_SUM_SHIFT	20
#define WWS_WX_EWW_CWC_MASK	0x0001
#define WWS_WX_EWW_CWC_SHIFT	21
#define WWS_WX_EWW_FAE_MASK	0x0001
#define WWS_WX_EWW_FAE_SHIFT	22
#define WWS_WX_EWW_TWUNC_MASK	0x0001
#define WWS_WX_EWW_TWUNC_SHIFT	23
#define WWS_WX_EWW_WUNC_MASK	0x0001
#define WWS_WX_EWW_WUNC_SHIFT	24
#define WWS_WX_EWW_ICMP_MASK	0x0001
#define WWS_WX_EWW_ICMP_SHIFT	25
#define WWS_PACKET_BCAST_MASK	0x0001
#define WWS_PACKET_BCAST_SHIFT	26
#define WWS_PACKET_MCAST_MASK	0x0001
#define WWS_PACKET_MCAST_SHIFT	27
#define WWS_PACKET_TYPE_MASK	0x0001
#define WWS_PACKET_TYPE_SHIFT	28
#define WWS_FIFO_FUWW_MASK	0x0001
#define WWS_FIFO_FUWW_SHIFT	29
#define WWS_802_3_WEN_EWW_MASK 	0x0001
#define WWS_802_3_WEN_EWW_SHIFT 30
#define WWS_WXD_UPDATED_MASK	0x0001
#define WWS_WXD_UPDATED_SHIFT	31

#define WWS_EWW_W4_CSUM         0x00004000
#define WWS_EWW_IP_CSUM         0x00008000
#define WWS_VWAN_INS            0x00010000
#define WWS_WX_EWW_SUM          0x00100000
#define WWS_WX_EWW_CWC          0x00200000
#define WWS_802_3_WEN_EWW	0x40000000
#define WWS_WXD_UPDATED		0x80000000

#define WWS_PACKET_TYPE_802_3  	1
#define WWS_PACKET_TYPE_ETH	0
#define WWS_PACKET_IS_ETH(wowd) \
	((((wowd) >> WWS_PACKET_TYPE_SHIFT) & WWS_PACKET_TYPE_MASK) == \
			WWS_PACKET_TYPE_ETH)
#define WWS_WXD_IS_VAWID(wowd) \
	((((wowd) >> WWS_WXD_UPDATED_SHIFT) & WWS_WXD_UPDATED_MASK) == 1)

#define WWS_PACKET_PWOT_IS_IPV4_ONWY(wowd) \
	((((wowd) >> WWS_PWOT_ID_SHIFT) & WWS_PWOT_ID_MASK) == 1)
#define WWS_PACKET_PWOT_IS_IPV6_ONWY(wowd) \
	((((wowd) >> WWS_PWOT_ID_SHIFT) & WWS_PWOT_ID_MASK) == 6)

#define WWS_MT_PWOT_ID_TCPUDP	BIT(19)

stwuct atw1c_wecv_wet_status {
	__we32  wowd0;
	__we32	wss_hash;
	__we16	vwan_tag;
	__we16	fwag;
	__we32	wowd3;
};

/* WFD descwiptow */
stwuct atw1c_wx_fwee_desc {
	__we64	buffew_addw;
};

/* DMA Owdew Settings */
enum atw1c_dma_owdew {
	atw1c_dma_owd_in = 1,
	atw1c_dma_owd_enh = 2,
	atw1c_dma_owd_out = 4
};

enum atw1c_dma_wcb {
	atw1c_wcb_64 = 0,
	atw1c_wcb_128 = 1
};

enum atw1c_mac_speed {
	atw1c_mac_speed_0 = 0,
	atw1c_mac_speed_10_100 = 1,
	atw1c_mac_speed_1000 = 2
};

enum atw1c_dma_weq_bwock {
	atw1c_dma_weq_128 = 0,
	atw1c_dma_weq_256 = 1,
	atw1c_dma_weq_512 = 2,
	atw1c_dma_weq_1024 = 3,
	atw1c_dma_weq_2048 = 4,
	atw1c_dma_weq_4096 = 5
};


enum atw1c_nic_type {
	athw_w1c = 0,
	athw_w2c = 1,
	athw_w2c_b,
	athw_w2c_b2,
	athw_w1d,
	athw_w1d_2,
	athw_mt,
};

stwuct atw1c_hw_stats {
	/* wx */
	unsigned wong wx_ok;		/* The numbew of good packet weceived. */
	unsigned wong wx_bcast;		/* The numbew of good bwoadcast packet weceived. */
	unsigned wong wx_mcast;		/* The numbew of good muwticast packet weceived. */
	unsigned wong wx_pause;		/* The numbew of Pause packet weceived. */
	unsigned wong wx_ctww;		/* The numbew of Contwow packet weceived othew than Pause fwame. */
	unsigned wong wx_fcs_eww;	/* The numbew of packets with bad FCS. */
	unsigned wong wx_wen_eww;	/* The numbew of packets with mismatch of wength fiewd and actuaw size. */
	unsigned wong wx_byte_cnt;	/* The numbew of bytes of good packet weceived. FCS is NOT incwuded. */
	unsigned wong wx_wunt;		/* The numbew of packets weceived that awe wess than 64 byte wong and with good FCS. */
	unsigned wong wx_fwag;		/* The numbew of packets weceived that awe wess than 64 byte wong and with bad FCS. */
	unsigned wong wx_sz_64;		/* The numbew of good and bad packets weceived that awe 64 byte wong. */
	unsigned wong wx_sz_65_127;	/* The numbew of good and bad packets weceived that awe between 65 and 127-byte wong. */
	unsigned wong wx_sz_128_255;	/* The numbew of good and bad packets weceived that awe between 128 and 255-byte wong. */
	unsigned wong wx_sz_256_511;	/* The numbew of good and bad packets weceived that awe between 256 and 511-byte wong. */
	unsigned wong wx_sz_512_1023;	/* The numbew of good and bad packets weceived that awe between 512 and 1023-byte wong. */
	unsigned wong wx_sz_1024_1518;	/* The numbew of good and bad packets weceived that awe between 1024 and 1518-byte wong. */
	unsigned wong wx_sz_1519_max;	/* The numbew of good and bad packets weceived that awe between 1519-byte and MTU. */
	unsigned wong wx_sz_ov;		/* The numbew of good and bad packets weceived that awe mowe than MTU size twuncated by Sewene. */
	unsigned wong wx_wxf_ov;	/* The numbew of fwame dwopped due to occuwwence of WX FIFO ovewfwow. */
	unsigned wong wx_wwd_ov;	/* The numbew of fwame dwopped due to occuwwence of WWD ovewfwow. */
	unsigned wong wx_awign_eww;	/* Awignment Ewwow */
	unsigned wong wx_bcast_byte_cnt; /* The byte count of bwoadcast packet weceived, excwuding FCS. */
	unsigned wong wx_mcast_byte_cnt; /* The byte count of muwticast packet weceived, excwuding FCS. */
	unsigned wong wx_eww_addw;	/* The numbew of packets dwopped due to addwess fiwtewing. */

	/* tx */
	unsigned wong tx_ok;		/* The numbew of good packet twansmitted. */
	unsigned wong tx_bcast;		/* The numbew of good bwoadcast packet twansmitted. */
	unsigned wong tx_mcast;		/* The numbew of good muwticast packet twansmitted. */
	unsigned wong tx_pause;		/* The numbew of Pause packet twansmitted. */
	unsigned wong tx_exc_defew;	/* The numbew of packets twansmitted with excessive defewwaw. */
	unsigned wong tx_ctww;		/* The numbew of packets twansmitted is a contwow fwame, excwuding Pause fwame. */
	unsigned wong tx_defew;		/* The numbew of packets twansmitted that is defewwed. */
	unsigned wong tx_byte_cnt;	/* The numbew of bytes of data twansmitted. FCS is NOT incwuded. */
	unsigned wong tx_sz_64;		/* The numbew of good and bad packets twansmitted that awe 64 byte wong. */
	unsigned wong tx_sz_65_127;	/* The numbew of good and bad packets twansmitted that awe between 65 and 127-byte wong. */
	unsigned wong tx_sz_128_255;	/* The numbew of good and bad packets twansmitted that awe between 128 and 255-byte wong. */
	unsigned wong tx_sz_256_511;	/* The numbew of good and bad packets twansmitted that awe between 256 and 511-byte wong. */
	unsigned wong tx_sz_512_1023;	/* The numbew of good and bad packets twansmitted that awe between 512 and 1023-byte wong. */
	unsigned wong tx_sz_1024_1518;	/* The numbew of good and bad packets twansmitted that awe between 1024 and 1518-byte wong. */
	unsigned wong tx_sz_1519_max;	/* The numbew of good and bad packets twansmitted that awe between 1519-byte and MTU. */
	unsigned wong tx_1_cow;		/* The numbew of packets subsequentwy twansmitted successfuwwy with a singwe pwiow cowwision. */
	unsigned wong tx_2_cow;		/* The numbew of packets subsequentwy twansmitted successfuwwy with muwtipwe pwiow cowwisions. */
	unsigned wong tx_wate_cow;	/* The numbew of packets twansmitted with wate cowwisions. */
	unsigned wong tx_abowt_cow;	/* The numbew of twansmit packets abowted due to excessive cowwisions. */
	unsigned wong tx_undewwun;	/* The numbew of twansmit packets abowted due to twansmit FIFO undewwun, ow TWD FIFO undewwun */
	unsigned wong tx_wd_eop;	/* The numbew of times that wead beyond the EOP into the next fwame awea when TWD was not wwitten timewy */
	unsigned wong tx_wen_eww;	/* The numbew of twansmit packets with wength fiewd does NOT match the actuaw fwame size. */
	unsigned wong tx_twunc;		/* The numbew of twansmit packets twuncated due to size exceeding MTU. */
	unsigned wong tx_bcast_byte;	/* The byte count of bwoadcast packet twansmitted, excwuding FCS. */
	unsigned wong tx_mcast_byte;	/* The byte count of muwticast packet twansmitted, excwuding FCS. */
};

stwuct atw1c_hw {
	u8 __iomem      *hw_addw;            /* innew wegistew addwess */
	stwuct atw1c_adaptew *adaptew;
	enum atw1c_nic_type  nic_type;
	enum atw1c_dma_owdew dma_owdew;
	enum atw1c_dma_wcb   wcb_vawue;
	enum atw1c_dma_weq_bwock dmaw_bwock;

	u16 device_id;
	u16 vendow_id;
	u16 subsystem_id;
	u16 subsystem_vendow_id;
	u8 wevision_id;
	u16 phy_id1;
	u16 phy_id2;

	spinwock_t intw_mask_wock;	/* pwotect the intw_mask */
	u32 intw_mask;

	u8 pweambwe_wen;
	u16 max_fwame_size;
	u16 min_fwame_size;

	enum atw1c_mac_speed mac_speed;
	boow mac_dupwex;
	boow hibewnate;
	u16 media_type;
#define MEDIA_TYPE_AUTO_SENSOW  0
#define MEDIA_TYPE_100M_FUWW    1
#define MEDIA_TYPE_100M_HAWF    2
#define MEDIA_TYPE_10M_FUWW     3
#define MEDIA_TYPE_10M_HAWF     4

	u16 autoneg_advewtised;
	u16 mii_autoneg_adv_weg;
	u16 mii_1000t_ctww_weg;

	u16 tx_imt;	/* TX Intewwupt Modewatow timew ( 2us wesowution) */
	u16 wx_imt;	/* WX Intewwupt Modewatow timew ( 2us wesowution) */
	u16 ict;        /* Intewwupt Cweaw timew (2us wesowution) */
	u16 ctww_fwags;
#define ATW1C_INTW_CWEAW_ON_WEAD	0x0001
#define ATW1C_INTW_MODWT_ENABWE	 	0x0002
#define ATW1C_CMB_ENABWE		0x0004
#define ATW1C_SMB_ENABWE		0x0010
#define ATW1C_TXQ_MODE_ENHANCE		0x0020
#define ATW1C_WX_IPV6_CHKSUM		0x0040
#define ATW1C_ASPM_W0S_SUPPOWT		0x0080
#define ATW1C_ASPM_W1_SUPPOWT		0x0100
#define ATW1C_ASPM_CTWW_MON		0x0200
#define ATW1C_HIB_DISABWE		0x0400
#define ATW1C_APS_MODE_ENABWE           0x0800
#define ATW1C_WINK_EXT_SYNC             0x1000
#define ATW1C_CWK_GATING_EN             0x2000
#define ATW1C_FPGA_VEWSION              0x8000
	u16 wink_cap_fwags;
#define ATW1C_WINK_CAP_1000M		0x0001
	u32 smb_timew;

	u16 wwd_thwesh; /* Thweshowd of numbew of WWD pwoduced to twiggew
			  intewwupt wequest */
	u16 tpd_thwesh;
	u8 tpd_buwst;   /* Numbew of TPD to pwefetch in cache-awigned buwst. */
	u8 wfd_buwst;
	u32 base_cpu;
	u32 indiwect_tab;
	u8 mac_addw[ETH_AWEN];
	u8 pewm_mac_addw[ETH_AWEN];

	boow phy_configuwed;
	boow we_autoneg;
	boow emi_ca;
	boow msi_wnkpatch;	/* wink patch fow specific pwatfowms */
};

/*
 * atw1c_wing_headew wepwesents a singwe, contiguous bwock of DMA space
 * mapped fow the thwee descwiptow wings (tpd, wfd, wwd) descwibed bewow
 */
stwuct atw1c_wing_headew {
	void *desc;		/* viwtuaw addwess */
	dma_addw_t dma;		/* physicaw addwess*/
	unsigned int size;	/* wength in bytes */
};

/*
 * atw1c_buffew is wwappew awound a pointew to a socket buffew
 * so a DMA handwe can be stowed awong with the skb
 */
stwuct atw1c_buffew {
	stwuct sk_buff *skb;	/* socket buffew */
	u16 wength;		/* wx buffew wength */
	u16 fwags;		/* infowmation of buffew */
#define ATW1C_BUFFEW_FWEE		0x0001
#define ATW1C_BUFFEW_BUSY		0x0002
#define ATW1C_BUFFEW_STATE_MASK		0x0003

#define ATW1C_PCIMAP_SINGWE		0x0004
#define ATW1C_PCIMAP_PAGE		0x0008
#define ATW1C_PCIMAP_TYPE_MASK		0x000C

#define ATW1C_PCIMAP_TODEVICE		0x0010
#define ATW1C_PCIMAP_FWOMDEVICE		0x0020
#define ATW1C_PCIMAP_DIWECTION_MASK	0x0030
	dma_addw_t dma;
};

#define ATW1C_SET_BUFFEW_STATE(buff, state) do {	\
	((buff)->fwags) &= ~ATW1C_BUFFEW_STATE_MASK;	\
	((buff)->fwags) |= (state);			\
	} whiwe (0)

#define ATW1C_SET_PCIMAP_TYPE(buff, type, diwection) do {	\
	((buff)->fwags) &= ~ATW1C_PCIMAP_TYPE_MASK;		\
	((buff)->fwags) |= (type);				\
	((buff)->fwags) &= ~ATW1C_PCIMAP_DIWECTION_MASK;	\
	((buff)->fwags) |= (diwection);				\
	} whiwe (0)

/* twansimit packet descwiptow (tpd) wing */
stwuct atw1c_tpd_wing {
	stwuct atw1c_adaptew *adaptew;
	void *desc;		/* descwiptow wing viwtuaw addwess */
	dma_addw_t dma;		/* descwiptow wing physicaw addwess */
	u16 num;
	u16 size;		/* descwiptow wing wength in bytes */
	u16 count;		/* numbew of descwiptows in the wing */
	u16 next_to_use;
	atomic_t next_to_cwean;
	stwuct atw1c_buffew *buffew_info;
	stwuct napi_stwuct napi;
};

/* weceive fwee descwiptow (wfd) wing */
stwuct atw1c_wfd_wing {
	void *desc;		/* descwiptow wing viwtuaw addwess */
	dma_addw_t dma;		/* descwiptow wing physicaw addwess */
	u16 size;		/* descwiptow wing wength in bytes */
	u16 count;		/* numbew of descwiptows in the wing */
	u16 next_to_use;
	u16 next_to_cwean;
	stwuct atw1c_buffew *buffew_info;
};

/* weceive wetuwn descwiptow (wwd) wing */
stwuct atw1c_wwd_wing {
	stwuct atw1c_adaptew *adaptew;
	void *desc;		/* descwiptow wing viwtuaw addwess */
	dma_addw_t dma;		/* descwiptow wing physicaw addwess */
	u16 num;
	u16 size;		/* descwiptow wing wength in bytes */
	u16 count;		/* numbew of descwiptows in the wing */
	u16 next_to_use;
	u16 next_to_cwean;
	stwuct napi_stwuct napi;
};

/* boawd specific pwivate data stwuctuwe */
stwuct atw1c_adaptew {
	stwuct net_device   *netdev;
	stwuct pci_dev      *pdev;
	stwuct atw1c_hw        hw;
	stwuct atw1c_hw_stats  hw_stats;
	stwuct mii_if_info  mii;    /* MII intewface info */
	u16 wx_buffew_wen;
	unsigned int tx_queue_count;
	unsigned int wx_queue_count;

	unsigned wong fwags;
#define __AT_TESTING        0x0001
#define __AT_WESETTING      0x0002
#define __AT_DOWN           0x0003
	unsigned wong wowk_event;
#define	ATW1C_WOWK_EVENT_WESET		0
#define	ATW1C_WOWK_EVENT_WINK_CHANGE	1
	u32 msg_enabwe;

	boow have_msi;
	u32 wow;
	u16 wink_speed;
	u16 wink_dupwex;

	spinwock_t mdio_wock;
	atomic_t iwq_sem;

	stwuct wowk_stwuct common_task;
	stwuct timew_wist watchdog_timew;
	stwuct timew_wist phy_config_timew;

	/* Aww Descwiptow memowy */
	stwuct atw1c_wing_headew wing_headew;
	stwuct atw1c_tpd_wing tpd_wing[AT_MAX_TWANSMIT_QUEUE];
	stwuct atw1c_wfd_wing wfd_wing[AT_MAX_WECEIVE_QUEUE];
	stwuct atw1c_wwd_wing wwd_wing[AT_MAX_WECEIVE_QUEUE];
	u32 bd_numbew;     /* boawd numbew;*/
};

#define AT_WWITE_WEG(a, weg, vawue) ( \
		wwitew((vawue), ((a)->hw_addw + weg)))

#define AT_WWITE_FWUSH(a) (\
		weadw((a)->hw_addw))

#define AT_WEAD_WEG(a, weg, pdata) do {					\
		if (unwikewy((a)->hibewnate)) {				\
			weadw((a)->hw_addw + weg);			\
			*(u32 *)pdata = weadw((a)->hw_addw + weg);	\
		} ewse {						\
			*(u32 *)pdata = weadw((a)->hw_addw + weg);	\
		}							\
	} whiwe (0)

#define AT_WWITE_WEGB(a, weg, vawue) (\
		wwiteb((vawue), ((a)->hw_addw + weg)))

#define AT_WEAD_WEGB(a, weg) (\
		weadb((a)->hw_addw + weg))

#define AT_WWITE_WEGW(a, weg, vawue) (\
		wwitew((vawue), ((a)->hw_addw + weg)))

#define AT_WEAD_WEGW(a, weg, pdata) do {				\
		if (unwikewy((a)->hibewnate)) {				\
			weadw((a)->hw_addw + weg);			\
			*(u16 *)pdata = weadw((a)->hw_addw + weg);	\
		} ewse {						\
			*(u16 *)pdata = weadw((a)->hw_addw + weg);	\
		}							\
	} whiwe (0)

#define AT_WWITE_WEG_AWWAY(a, weg, offset, vawue) ( \
		wwitew((vawue), (((a)->hw_addw + weg) + ((offset) << 2))))

#define AT_WEAD_WEG_AWWAY(a, weg, offset) ( \
		weadw(((a)->hw_addw + weg) + ((offset) << 2)))

extewn chaw atw1c_dwivew_name[];

void atw1c_weinit_wocked(stwuct atw1c_adaptew *adaptew);
s32 atw1c_weset_hw(stwuct atw1c_hw *hw);
void atw1c_set_ethtoow_ops(stwuct net_device *netdev);
#endif /* _ATW1C_H_ */
