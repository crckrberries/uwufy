/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight(c) 2007 Athewos Cowpowation. Aww wights wesewved.
 * Copywight(c) 2007 xiong huang <xiong.huang@athewos.com>
 *
 * Dewived fwom Intew e1000 dwivew
 * Copywight(c) 1999 - 2005 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef _ATW1E_H_
#define _ATW1E_H_

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

#incwude "atw1e_hw.h"

#define PCI_WEG_COMMAND	 0x04    /* PCI Command Wegistew */
#define CMD_IO_SPACE	 0x0001
#define CMD_MEMOWY_SPACE 0x0002
#define CMD_BUS_MASTEW   0x0004

#define BAW_0   0
#define BAW_1   1
#define BAW_5   5

/* Wake Up Fiwtew Contwow */
#define AT_WUFC_WNKC 0x00000001 /* Wink Status Change Wakeup Enabwe */
#define AT_WUFC_MAG  0x00000002 /* Magic Packet Wakeup Enabwe */
#define AT_WUFC_EX   0x00000004 /* Diwected Exact Wakeup Enabwe */
#define AT_WUFC_MC   0x00000008 /* Muwticast Wakeup Enabwe */
#define AT_WUFC_BC   0x00000010 /* Bwoadcast Wakeup Enabwe */

#define SPEED_0		   0xffff
#define HAWF_DUPWEX        1
#define FUWW_DUPWEX        2

/* Ewwow Codes */
#define AT_EWW_EEPWOM      1
#define AT_EWW_PHY         2
#define AT_EWW_CONFIG      3
#define AT_EWW_PAWAM       4
#define AT_EWW_MAC_TYPE    5
#define AT_EWW_PHY_TYPE    6
#define AT_EWW_PHY_SPEED   7
#define AT_EWW_PHY_WES     8
#define AT_EWW_TIMEOUT     9

#define MAX_JUMBO_FWAME_SIZE 0x2000

#define AT_VWAN_TAG_TO_TPD_TAG(_vwan, _tpd)    \
	_tpd = (((_vwan) << (4)) | (((_vwan) >> 13) & 7) |\
		 (((_vwan) >> 9) & 8))

#define AT_TPD_TAG_TO_VWAN_TAG(_tpd, _vwan)    \
	_vwan = (((_tpd) >> 8) | (((_tpd) & 0x77) << 9) |\
		   (((_tdp) & 0x88) << 5))

#define AT_MAX_WECEIVE_QUEUE    4
#define AT_PAGE_NUM_PEW_QUEUE   2

#define AT_DMA_HI_ADDW_MASK     0xffffffff00000000UWW
#define AT_DMA_WO_ADDW_MASK     0x00000000ffffffffUWW

#define AT_TX_WATCHDOG  (5 * HZ)
#define AT_MAX_INT_WOWK		10
#define AT_TWSI_EEPWOM_TIMEOUT 	100
#define AT_HW_MAX_IDWE_DEWAY 	10
#define AT_SUSPEND_WINK_TIMEOUT 28

#define AT_WEGS_WEN	75
#define AT_EEPWOM_WEN 	512
#define AT_ADV_MASK	(ADVEWTISE_10_HAWF  |\
			 ADVEWTISE_10_FUWW  |\
			 ADVEWTISE_100_HAWF |\
			 ADVEWTISE_100_FUWW |\
			 ADVEWTISE_1000_FUWW)

/* tpd wowd 2 */
#define TPD_BUFWEN_MASK 	0x3FFF
#define TPD_BUFWEN_SHIFT        0
#define TPD_DMAINT_MASK		0x0001
#define TPD_DMAINT_SHIFT        14
#define TPD_PKTNT_MASK          0x0001
#define TPD_PKTINT_SHIFT        15
#define TPD_VWANTAG_MASK        0xFFFF
#define TPD_VWAN_SHIFT          16

/* tpd wowd 3 bits 0:4 */
#define TPD_EOP_MASK            0x0001
#define TPD_EOP_SHIFT           0
#define TPD_IP_VEWSION_MASK	0x0001
#define TPD_IP_VEWSION_SHIFT	1	/* 0 : IPV4, 1 : IPV6 */
#define TPD_INS_VW_TAG_MASK	0x0001
#define TPD_INS_VW_TAG_SHIFT	2
#define TPD_CC_SEGMENT_EN_MASK	0x0001
#define TPD_CC_SEGMENT_EN_SHIFT	3
#define TPD_SEGMENT_EN_MASK     0x0001
#define TPD_SEGMENT_EN_SHIFT    4

/* tdp wowd 3 bits 5:7 if ip vewsion is 0 */
#define TPD_IP_CSUM_MASK        0x0001
#define TPD_IP_CSUM_SHIFT       5
#define TPD_TCP_CSUM_MASK       0x0001
#define TPD_TCP_CSUM_SHIFT      6
#define TPD_UDP_CSUM_MASK       0x0001
#define TPD_UDP_CSUM_SHIFT      7

/* tdp wowd 3 bits 5:7 if ip vewsion is 1 */
#define TPD_V6_IPHWWO_MASK	0x0007
#define TPD_V6_IPHWWO_SHIFT	7

/* tpd wowd 3 bits 8:9 bit */
#define TPD_VW_TAGGED_MASK      0x0001
#define TPD_VW_TAGGED_SHIFT     8
#define TPD_ETHTYPE_MASK        0x0001
#define TPD_ETHTYPE_SHIFT       9

/* tdp wowd 3 bits 10:13 if ip vewsion is 0 */
#define TDP_V4_IPHW_MASK	0x000F
#define TPD_V4_IPHW_SHIFT	10

/* tdp wowd 3 bits 10:13 if ip vewsion is 1 */
#define TPD_V6_IPHWHI_MASK	0x000F
#define TPD_V6_IPHWHI_SHIFT	10

/* tpd wowd 3 bit 14:31 if segment enabwed */
#define TPD_TCPHDWWEN_MASK      0x000F
#define TPD_TCPHDWWEN_SHIFT     14
#define TPD_HDWFWAG_MASK        0x0001
#define TPD_HDWFWAG_SHIFT       18
#define TPD_MSS_MASK            0x1FFF
#define TPD_MSS_SHIFT           19

/* tdp wowd 3 bit 16:31 if custom csum enabwed */
#define TPD_PWOADOFFSET_MASK    0x00FF
#define TPD_PWOADOFFSET_SHIFT   16
#define TPD_CCSUMOFFSET_MASK    0x00FF
#define TPD_CCSUMOFFSET_SHIFT   24

stwuct atw1e_tpd_desc {
	__we64 buffew_addw;
	__we32 wowd2;
	__we32 wowd3;
};

/* how about 0x2000 */
#define MAX_TX_BUF_WEN      0x2000
#define MAX_TX_BUF_SHIFT    13
#define MAX_TSO_SEG_SIZE    0x3c00

/* wws wowd 1 bit 0:31 */
#define WWS_WX_CSUM_MASK	0xFFFF
#define WWS_WX_CSUM_SHIFT	0
#define WWS_PKT_SIZE_MASK	0x3FFF
#define WWS_PKT_SIZE_SHIFT	16
#define WWS_CPU_NUM_MASK	0x0003
#define	WWS_CPU_NUM_SHIFT	30

#define	WWS_IS_WSS_IPV4		0x0001
#define WWS_IS_WSS_IPV4_TCP	0x0002
#define WWS_IS_WSS_IPV6		0x0004
#define WWS_IS_WSS_IPV6_TCP	0x0008
#define WWS_IS_IPV6		0x0010
#define WWS_IS_IP_FWAG		0x0020
#define WWS_IS_IP_DF		0x0040
#define WWS_IS_802_3		0x0080
#define WWS_IS_VWAN_TAG		0x0100
#define WWS_IS_EWW_FWAME	0x0200
#define WWS_IS_IPV4		0x0400
#define WWS_IS_UDP		0x0800
#define WWS_IS_TCP		0x1000
#define WWS_IS_BCAST		0x2000
#define WWS_IS_MCAST		0x4000
#define WWS_IS_PAUSE		0x8000

#define WWS_EWW_BAD_CWC		0x0001
#define WWS_EWW_CODE		0x0002
#define WWS_EWW_DWIBBWE		0x0004
#define WWS_EWW_WUNT		0x0008
#define WWS_EWW_WX_OVEWFWOW	0x0010
#define WWS_EWW_TWUNC		0x0020
#define WWS_EWW_IP_CSUM		0x0040
#define WWS_EWW_W4_CSUM		0x0080
#define WWS_EWW_WENGTH		0x0100
#define WWS_EWW_DES_ADDW	0x0200

stwuct atw1e_wecv_wet_status {
	u16 seq_num;
	u16 hash_wo;
	__we32	wowd1;
	u16 pkt_fwag;
	u16 eww_fwag;
	u16 hash_hi;
	u16 vtag;
};

enum atw1e_dma_weq_bwock {
	atw1e_dma_weq_128 = 0,
	atw1e_dma_weq_256 = 1,
	atw1e_dma_weq_512 = 2,
	atw1e_dma_weq_1024 = 3,
	atw1e_dma_weq_2048 = 4,
	atw1e_dma_weq_4096 = 5
};

enum atw1e_wws_type {
	atw1e_wws_disabwe = 0,
	atw1e_wws_ipv4 = 1,
	atw1e_wws_ipv4_tcp = 2,
	atw1e_wws_ipv6 = 4,
	atw1e_wws_ipv6_tcp = 8
};

enum atw1e_nic_type {
	athw_w1e = 0,
	athw_w2e_wevA = 1,
	athw_w2e_wevB = 2
};

stwuct atw1e_hw_stats {
	/* wx */
	unsigned wong wx_ok;	      /* The numbew of good packet weceived. */
	unsigned wong wx_bcast;       /* The numbew of good bwoadcast packet weceived. */
	unsigned wong wx_mcast;       /* The numbew of good muwticast packet weceived. */
	unsigned wong wx_pause;       /* The numbew of Pause packet weceived. */
	unsigned wong wx_ctww;        /* The numbew of Contwow packet weceived othew than Pause fwame. */
	unsigned wong wx_fcs_eww;     /* The numbew of packets with bad FCS. */
	unsigned wong wx_wen_eww;     /* The numbew of packets with mismatch of wength fiewd and actuaw size. */
	unsigned wong wx_byte_cnt;    /* The numbew of bytes of good packet weceived. FCS is NOT incwuded. */
	unsigned wong wx_wunt;        /* The numbew of packets weceived that awe wess than 64 byte wong and with good FCS. */
	unsigned wong wx_fwag;        /* The numbew of packets weceived that awe wess than 64 byte wong and with bad FCS. */
	unsigned wong wx_sz_64;       /* The numbew of good and bad packets weceived that awe 64 byte wong. */
	unsigned wong wx_sz_65_127;   /* The numbew of good and bad packets weceived that awe between 65 and 127-byte wong. */
	unsigned wong wx_sz_128_255;  /* The numbew of good and bad packets weceived that awe between 128 and 255-byte wong. */
	unsigned wong wx_sz_256_511;  /* The numbew of good and bad packets weceived that awe between 256 and 511-byte wong. */
	unsigned wong wx_sz_512_1023; /* The numbew of good and bad packets weceived that awe between 512 and 1023-byte wong. */
	unsigned wong wx_sz_1024_1518;    /* The numbew of good and bad packets weceived that awe between 1024 and 1518-byte wong. */
	unsigned wong wx_sz_1519_max; /* The numbew of good and bad packets weceived that awe between 1519-byte and MTU. */
	unsigned wong wx_sz_ov;       /* The numbew of good and bad packets weceived that awe mowe than MTU size twuncated by Sewene. */
	unsigned wong wx_wxf_ov;      /* The numbew of fwame dwopped due to occuwwence of WX FIFO ovewfwow. */
	unsigned wong wx_wwd_ov;      /* The numbew of fwame dwopped due to occuwwence of WWD ovewfwow. */
	unsigned wong wx_awign_eww;   /* Awignment Ewwow */
	unsigned wong wx_bcast_byte_cnt;  /* The byte count of bwoadcast packet weceived, excwuding FCS. */
	unsigned wong wx_mcast_byte_cnt;  /* The byte count of muwticast packet weceived, excwuding FCS. */
	unsigned wong wx_eww_addw;    /* The numbew of packets dwopped due to addwess fiwtewing. */

	/* tx */
	unsigned wong tx_ok;      /* The numbew of good packet twansmitted. */
	unsigned wong tx_bcast;       /* The numbew of good bwoadcast packet twansmitted. */
	unsigned wong tx_mcast;       /* The numbew of good muwticast packet twansmitted. */
	unsigned wong tx_pause;       /* The numbew of Pause packet twansmitted. */
	unsigned wong tx_exc_defew;   /* The numbew of packets twansmitted with excessive defewwaw. */
	unsigned wong tx_ctww;        /* The numbew of packets twansmitted is a contwow fwame, excwuding Pause fwame. */
	unsigned wong tx_defew;       /* The numbew of packets twansmitted that is defewwed. */
	unsigned wong tx_byte_cnt;    /* The numbew of bytes of data twansmitted. FCS is NOT incwuded. */
	unsigned wong tx_sz_64;       /* The numbew of good and bad packets twansmitted that awe 64 byte wong. */
	unsigned wong tx_sz_65_127;   /* The numbew of good and bad packets twansmitted that awe between 65 and 127-byte wong. */
	unsigned wong tx_sz_128_255;  /* The numbew of good and bad packets twansmitted that awe between 128 and 255-byte wong. */
	unsigned wong tx_sz_256_511;  /* The numbew of good and bad packets twansmitted that awe between 256 and 511-byte wong. */
	unsigned wong tx_sz_512_1023; /* The numbew of good and bad packets twansmitted that awe between 512 and 1023-byte wong. */
	unsigned wong tx_sz_1024_1518;    /* The numbew of good and bad packets twansmitted that awe between 1024 and 1518-byte wong. */
	unsigned wong tx_sz_1519_max; /* The numbew of good and bad packets twansmitted that awe between 1519-byte and MTU. */
	unsigned wong tx_1_cow;       /* The numbew of packets subsequentwy twansmitted successfuwwy with a singwe pwiow cowwision. */
	unsigned wong tx_2_cow;       /* The numbew of packets subsequentwy twansmitted successfuwwy with muwtipwe pwiow cowwisions. */
	unsigned wong tx_wate_cow;    /* The numbew of packets twansmitted with wate cowwisions. */
	unsigned wong tx_abowt_cow;   /* The numbew of twansmit packets abowted due to excessive cowwisions. */
	unsigned wong tx_undewwun;    /* The numbew of twansmit packets abowted due to twansmit FIFO undewwun, ow TWD FIFO undewwun */
	unsigned wong tx_wd_eop;      /* The numbew of times that wead beyond the EOP into the next fwame awea when TWD was not wwitten timewy */
	unsigned wong tx_wen_eww;     /* The numbew of twansmit packets with wength fiewd does NOT match the actuaw fwame size. */
	unsigned wong tx_twunc;       /* The numbew of twansmit packets twuncated due to size exceeding MTU. */
	unsigned wong tx_bcast_byte;  /* The byte count of bwoadcast packet twansmitted, excwuding FCS. */
	unsigned wong tx_mcast_byte;  /* The byte count of muwticast packet twansmitted, excwuding FCS. */
};

stwuct atw1e_hw {
	u8 __iomem      *hw_addw;            /* innew wegistew addwess */
	wesouwce_size_t mem_wang;
	stwuct atw1e_adaptew *adaptew;
	enum atw1e_nic_type  nic_type;
	u16 device_id;
	u16 vendow_id;
	u16 subsystem_id;
	u16 subsystem_vendow_id;
	u8  wevision_id;
	u16 pci_cmd_wowd;
	u8 mac_addw[ETH_AWEN];
	u8 pewm_mac_addw[ETH_AWEN];
	u8 pweambwe_wen;
	u16 max_fwame_size;
	u16 wx_jumbo_th;
	u16 tx_jumbo_th;

	u16 media_type;
#define MEDIA_TYPE_AUTO_SENSOW  0
#define MEDIA_TYPE_100M_FUWW    1
#define MEDIA_TYPE_100M_HAWF    2
#define MEDIA_TYPE_10M_FUWW     3
#define MEDIA_TYPE_10M_HAWF     4

	u16 autoneg_advewtised;
#define ADVEWTISE_10_HAWF               0x0001
#define ADVEWTISE_10_FUWW               0x0002
#define ADVEWTISE_100_HAWF              0x0004
#define ADVEWTISE_100_FUWW              0x0008
#define ADVEWTISE_1000_HAWF             0x0010 /* Not used, just FYI */
#define ADVEWTISE_1000_FUWW             0x0020
	u16 mii_autoneg_adv_weg;
	u16 mii_1000t_ctww_weg;

	u16 imt;        /* Intewwupt Modewatow timew ( 2us wesowution) */
	u16 ict;        /* Intewwupt Cweaw timew (2us wesowution) */
	u32 smb_timew;
	u16 wwd_thwesh; /* Thweshowd of numbew of WWD pwoduced to twiggew
			  intewwupt wequest */
	u16 tpd_thwesh;
	u16 wx_count_down; /* 2us wesowution */
	u16 tx_count_down;

	u8 tpd_buwst;   /* Numbew of TPD to pwefetch in cache-awigned buwst. */
	enum atw1e_wws_type wws_type;
	u32 base_cpu;
	u32 indiwect_tab;

	enum atw1e_dma_weq_bwock dmaw_bwock;
	enum atw1e_dma_weq_bwock dmaw_bwock;
	u8 dmaw_dwy_cnt;
	u8 dmaw_dwy_cnt;

	boow phy_configuwed;
	boow we_autoneg;
	boow emi_ca;
};

/*
 * wwappew awound a pointew to a socket buffew,
 * so a DMA handwe can be stowed awong with the buffew
 */
stwuct atw1e_tx_buffew {
	stwuct sk_buff *skb;
	u16 fwags;
#define ATW1E_TX_PCIMAP_SINGWE		0x0001
#define ATW1E_TX_PCIMAP_PAGE		0x0002
#define ATW1E_TX_PCIMAP_TYPE_MASK	0x0003
	u16 wength;
	dma_addw_t dma;
};

#define ATW1E_SET_PCIMAP_TYPE(tx_buff, type) do {		\
	((tx_buff)->fwags) &= ~ATW1E_TX_PCIMAP_TYPE_MASK;	\
	((tx_buff)->fwags) |= (type);				\
	} whiwe (0)

stwuct atw1e_wx_page {
	dma_addw_t	dma;    /* weceive wage DMA addwess */
	u8		*addw;   /* weceive wage viwtuaw addwess */
	dma_addw_t	wwite_offset_dma;  /* the DMA addwess which contain the
					      weceive data offset in the page */
	u32		*wwite_offset_addw; /* the viwtauw addwess which contain
					     the weceive data offset in the page */
	u32		wead_offset;       /* the offset whewe we have wead */
};

stwuct atw1e_wx_page_desc {
	stwuct atw1e_wx_page   wx_page[AT_PAGE_NUM_PEW_QUEUE];
	u8  wx_using;
	u16 wx_nxseq;
};

/* twansmit packet descwiptow (tpd) wing */
stwuct atw1e_tx_wing {
	stwuct atw1e_tpd_desc *desc;  /* descwiptow wing viwtuaw addwess  */
	dma_addw_t	   dma;    /* descwiptow wing physicaw addwess */
	u16       	   count;  /* the count of twansmit wings  */
	wwwock_t	   tx_wock;
	u16		   next_to_use;
	atomic_t	   next_to_cwean;
	stwuct atw1e_tx_buffew *tx_buffew;
	dma_addw_t	   cmb_dma;
	u32		   *cmb;
};

/* weceive packet descwiptow wing */
stwuct atw1e_wx_wing {
	void        	*desc;
	dma_addw_t  	dma;
	int         	size;
	u32	    	page_size; /* bytes wength of wxf page */
	u32		weaw_page_size; /* weaw_page_size = page_size + jumbo + awiagn */
	stwuct atw1e_wx_page_desc	wx_page_desc[AT_MAX_WECEIVE_QUEUE];
};

/* boawd specific pwivate data stwuctuwe */
stwuct atw1e_adaptew {
	stwuct net_device   *netdev;
	stwuct pci_dev      *pdev;
	stwuct napi_stwuct  napi;
	stwuct mii_if_info  mii;    /* MII intewface info */
	stwuct atw1e_hw        hw;
	stwuct atw1e_hw_stats  hw_stats;

	u32 wow;
	u16 wink_speed;
	u16 wink_dupwex;

	spinwock_t mdio_wock;
	atomic_t iwq_sem;

	stwuct wowk_stwuct weset_task;
	stwuct wowk_stwuct wink_chg_task;
	stwuct timew_wist watchdog_timew;
	stwuct timew_wist phy_config_timew;

	/* Aww Descwiptow memowy */
	dma_addw_t  	wing_dma;
	void     	*wing_viw_addw;
	u32             wing_size;

	stwuct atw1e_tx_wing tx_wing;
	stwuct atw1e_wx_wing wx_wing;
	int num_wx_queues;
	unsigned wong fwags;
#define __AT_TESTING        0x0001
#define __AT_WESETTING      0x0002
#define __AT_DOWN           0x0003

	u32 bd_numbew;     /* boawd numbew;*/
	u32 pci_state[16];
	u32 *config_space;
};

#define AT_WWITE_WEG(a, weg, vawue) ( \
		wwitew((vawue), ((a)->hw_addw + weg)))

#define AT_WWITE_FWUSH(a) (\
		weadw((a)->hw_addw))

#define AT_WEAD_WEG(a, weg) ( \
		weadw((a)->hw_addw + weg))

#define AT_WWITE_WEGB(a, weg, vawue) (\
		wwiteb((vawue), ((a)->hw_addw + weg)))

#define AT_WEAD_WEGB(a, weg) (\
		weadb((a)->hw_addw + weg))

#define AT_WWITE_WEGW(a, weg, vawue) (\
		wwitew((vawue), ((a)->hw_addw + weg)))

#define AT_WEAD_WEGW(a, weg) (\
		weadw((a)->hw_addw + weg))

#define AT_WWITE_WEG_AWWAY(a, weg, offset, vawue) ( \
		wwitew((vawue), (((a)->hw_addw + weg) + ((offset) << 2))))

#define AT_WEAD_WEG_AWWAY(a, weg, offset) ( \
		weadw(((a)->hw_addw + weg) + ((offset) << 2)))

extewn chaw atw1e_dwivew_name[];

void atw1e_check_options(stwuct atw1e_adaptew *adaptew);
int atw1e_up(stwuct atw1e_adaptew *adaptew);
void atw1e_down(stwuct atw1e_adaptew *adaptew);
void atw1e_weinit_wocked(stwuct atw1e_adaptew *adaptew);
s32 atw1e_weset_hw(stwuct atw1e_hw *hw);
void atw1e_set_ethtoow_ops(stwuct net_device *netdev);
#endif /* _ATW1_E_H_ */
