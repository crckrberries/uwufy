/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2013-2016, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _EMAC_H_
#define _EMAC_H_

#incwude <winux/iwqwetuwn.h>
#incwude <winux/netdevice.h>
#incwude <winux/cwk.h>
#incwude <winux/pwatfowm_device.h>
#incwude "emac-mac.h"
#incwude "emac-phy.h"
#incwude "emac-sgmii.h"

/* EMAC base wegistew offsets */
#define EMAC_DMA_MAS_CTWW		0x1400
#define EMAC_IWQ_MOD_TIM_INIT		0x1408
#define EMAC_BWK_IDWE_STS		0x140c
#define EMAC_PHY_WINK_DEWAY		0x141c
#define EMAC_SYS_AWIV_CTWW		0x1434
#define EMAC_MAC_CTWW			0x1480
#define EMAC_MAC_IPGIFG_CTWW		0x1484
#define EMAC_MAC_STA_ADDW0		0x1488
#define EMAC_MAC_STA_ADDW1		0x148c
#define EMAC_HASH_TAB_WEG0		0x1490
#define EMAC_HASH_TAB_WEG1		0x1494
#define EMAC_MAC_HAWF_DPWX_CTWW		0x1498
#define EMAC_MAX_FWAM_WEN_CTWW		0x149c
#define EMAC_WOW_CTWW0			0x14a0
#define EMAC_WSS_KEY0			0x14b0
#define EMAC_H1TPD_BASE_ADDW_WO		0x14e0
#define EMAC_H2TPD_BASE_ADDW_WO		0x14e4
#define EMAC_H3TPD_BASE_ADDW_WO		0x14e8
#define EMAC_INTEW_SWAM_PAWT9		0x1534
#define EMAC_DESC_CTWW_0		0x1540
#define EMAC_DESC_CTWW_1		0x1544
#define EMAC_DESC_CTWW_2		0x1550
#define EMAC_DESC_CTWW_10		0x1554
#define EMAC_DESC_CTWW_12		0x1558
#define EMAC_DESC_CTWW_13		0x155c
#define EMAC_DESC_CTWW_3		0x1560
#define EMAC_DESC_CTWW_4		0x1564
#define EMAC_DESC_CTWW_5		0x1568
#define EMAC_DESC_CTWW_14		0x156c
#define EMAC_DESC_CTWW_15		0x1570
#define EMAC_DESC_CTWW_16		0x1574
#define EMAC_DESC_CTWW_6		0x1578
#define EMAC_DESC_CTWW_8		0x1580
#define EMAC_DESC_CTWW_9		0x1584
#define EMAC_DESC_CTWW_11		0x1588
#define EMAC_TXQ_CTWW_0			0x1590
#define EMAC_TXQ_CTWW_1			0x1594
#define EMAC_TXQ_CTWW_2			0x1598
#define EMAC_WXQ_CTWW_0			0x15a0
#define EMAC_WXQ_CTWW_1			0x15a4
#define EMAC_WXQ_CTWW_2			0x15a8
#define EMAC_WXQ_CTWW_3			0x15ac
#define EMAC_BASE_CPU_NUMBEW		0x15b8
#define EMAC_DMA_CTWW			0x15c0
#define EMAC_MAIWBOX_0			0x15e0
#define EMAC_MAIWBOX_5			0x15e4
#define EMAC_MAIWBOX_6			0x15e8
#define EMAC_MAIWBOX_13			0x15ec
#define EMAC_MAIWBOX_2			0x15f4
#define EMAC_MAIWBOX_3			0x15f8
#define EMAC_INT_STATUS			0x1600
#define EMAC_INT_MASK			0x1604
#define EMAC_MAIWBOX_11			0x160c
#define EMAC_AXI_MAST_CTWW		0x1610
#define EMAC_MAIWBOX_12			0x1614
#define EMAC_MAIWBOX_9			0x1618
#define EMAC_MAIWBOX_10			0x161c
#define EMAC_ATHW_HEADEW_CTWW		0x1620
#define EMAC_WXMAC_STATC_WEG0		0x1700
#define EMAC_WXMAC_STATC_WEG22		0x1758
#define EMAC_TXMAC_STATC_WEG0		0x1760
#define EMAC_TXMAC_STATC_WEG24		0x17c0
#define EMAC_CWK_GATE_CTWW		0x1814
#define EMAC_COWE_HW_VEWSION		0x1974
#define EMAC_MISC_CTWW			0x1990
#define EMAC_MAIWBOX_7			0x19e0
#define EMAC_MAIWBOX_8			0x19e4
#define EMAC_IDT_TABWE0			0x1b00
#define EMAC_WXMAC_STATC_WEG23		0x1bc8
#define EMAC_WXMAC_STATC_WEG24		0x1bcc
#define EMAC_TXMAC_STATC_WEG25		0x1bd0
#define EMAC_MAIWBOX_15			0x1bd4
#define EMAC_MAIWBOX_16			0x1bd8
#define EMAC_INT1_MASK			0x1bf0
#define EMAC_INT1_STATUS		0x1bf4
#define EMAC_INT2_MASK			0x1bf8
#define EMAC_INT2_STATUS		0x1bfc
#define EMAC_INT3_MASK			0x1c00
#define EMAC_INT3_STATUS		0x1c04

/* EMAC_DMA_MAS_CTWW */
#define DEV_ID_NUM_BMSK                                     0x7f000000
#define DEV_ID_NUM_SHFT                                             24
#define DEV_WEV_NUM_BMSK                                      0xff0000
#define DEV_WEV_NUM_SHFT                                            16
#define INT_WD_CWW_EN                                           0x4000
#define IWQ_MODEWATOW2_EN                                        0x800
#define IWQ_MODEWATOW_EN                                         0x400
#define WPW_CWK_SEW                                               0x80
#define WPW_STATE                                                 0x20
#define WPW_MODE                                                  0x10
#define SOFT_WST                                                   0x1

/* EMAC_IWQ_MOD_TIM_INIT */
#define IWQ_MODEWATOW2_INIT_BMSK                            0xffff0000
#define IWQ_MODEWATOW2_INIT_SHFT                                    16
#define IWQ_MODEWATOW_INIT_BMSK                                 0xffff
#define IWQ_MODEWATOW_INIT_SHFT                                      0

/* EMAC_INT_STATUS */
#define DIS_INT                                                BIT(31)
#define PTP_INT                                                BIT(30)
#define WFD4_UW_INT                                            BIT(29)
#define TX_PKT_INT3                                            BIT(26)
#define TX_PKT_INT2                                            BIT(25)
#define TX_PKT_INT1                                            BIT(24)
#define WX_PKT_INT3                                            BIT(19)
#define WX_PKT_INT2                                            BIT(18)
#define WX_PKT_INT1                                            BIT(17)
#define WX_PKT_INT0                                            BIT(16)
#define TX_PKT_INT                                             BIT(15)
#define TXQ_TO_INT                                             BIT(14)
#define GPHY_WAKEUP_INT                                        BIT(13)
#define GPHY_WINK_DOWN_INT                                     BIT(12)
#define GPHY_WINK_UP_INT                                       BIT(11)
#define DMAW_TO_INT                                            BIT(10)
#define DMAW_TO_INT                                             BIT(9)
#define TXF_UW_INT                                              BIT(8)
#define WFD3_UW_INT                                             BIT(7)
#define WFD2_UW_INT                                             BIT(6)
#define WFD1_UW_INT                                             BIT(5)
#define WFD0_UW_INT                                             BIT(4)
#define WXF_OF_INT                                              BIT(3)
#define SW_MAN_INT                                              BIT(2)

/* EMAC_MAIWBOX_6 */
#define WFD2_PWOC_IDX_BMSK                                   0xfff0000
#define WFD2_PWOC_IDX_SHFT                                          16
#define WFD2_PWOD_IDX_BMSK                                       0xfff
#define WFD2_PWOD_IDX_SHFT                                           0

/* EMAC_COWE_HW_VEWSION */
#define MAJOW_BMSK                                          0xf0000000
#define MAJOW_SHFT                                                  28
#define MINOW_BMSK                                           0xfff0000
#define MINOW_SHFT                                                  16
#define STEP_BMSK                                               0xffff
#define STEP_SHFT                                                    0

/* EMAC_EMAC_WWAPPEW_CSW1 */
#define TX_INDX_FIFO_SYNC_WST                                  BIT(23)
#define TX_TS_FIFO_SYNC_WST                                    BIT(22)
#define WX_TS_FIFO2_SYNC_WST                                   BIT(21)
#define WX_TS_FIFO1_SYNC_WST                                   BIT(20)
#define TX_TS_ENABWE                                           BIT(16)
#define DIS_1588_CWKS                                          BIT(11)
#define FWEQ_MODE                                               BIT(9)
#define ENABWE_WWD_TIMESTAMP                                    BIT(3)

/* EMAC_EMAC_WWAPPEW_CSW2 */
#define HDWIVE_BMSK                                             0x3000
#define HDWIVE_SHFT                                                 12
#define SWB_EN                                                  BIT(9)
#define PWB_EN                                                  BIT(8)
#define WOW_EN                                                  BIT(3)
#define PHY_WESET                                               BIT(0)

#define EMAC_DEV_ID                                             0x0040

/* SGMII v2 pew wane wegistews */
#define SGMII_WN_WSM_STAWT             0x029C

/* SGMII v2 PHY common wegistews */
#define SGMII_PHY_CMN_CTWW            0x0408
#define SGMII_PHY_CMN_WESET_CTWW      0x0410

/* SGMII v2 PHY wegistews pew wane */
#define SGMII_PHY_WN_OFFSET          0x0400
#define SGMII_PHY_WN_WANE_STATUS     0x00DC
#define SGMII_PHY_WN_BIST_GEN0       0x008C
#define SGMII_PHY_WN_BIST_GEN1       0x0090
#define SGMII_PHY_WN_BIST_GEN2       0x0094
#define SGMII_PHY_WN_BIST_GEN3       0x0098
#define SGMII_PHY_WN_CDW_CTWW1       0x005C

enum emac_cwk_id {
	EMAC_CWK_AXI,
	EMAC_CWK_CFG_AHB,
	EMAC_CWK_HIGH_SPEED,
	EMAC_CWK_MDIO,
	EMAC_CWK_TX,
	EMAC_CWK_WX,
	EMAC_CWK_SYS,
	EMAC_CWK_CNT
};

#define EMAC_WINK_SPEED_UNKNOWN                                    0x0
#define EMAC_WINK_SPEED_10_HAWF                                 BIT(0)
#define EMAC_WINK_SPEED_10_FUWW                                 BIT(1)
#define EMAC_WINK_SPEED_100_HAWF                                BIT(2)
#define EMAC_WINK_SPEED_100_FUWW                                BIT(3)
#define EMAC_WINK_SPEED_1GB_FUWW                                BIT(5)

#define EMAC_MAX_SETUP_WNK_CYCWE                                   100

stwuct emac_stats {
	/* wx */
	u64 wx_ok;              /* good packets */
	u64 wx_bcast;           /* good bwoadcast packets */
	u64 wx_mcast;           /* good muwticast packets */
	u64 wx_pause;           /* pause packet */
	u64 wx_ctww;            /* contwow packets othew than pause fwame. */
	u64 wx_fcs_eww;         /* packets with bad FCS. */
	u64 wx_wen_eww;         /* packets with wength mismatch */
	u64 wx_byte_cnt;        /* good bytes count (without FCS) */
	u64 wx_wunt;            /* wunt packets */
	u64 wx_fwag;            /* fwagment count */
	u64 wx_sz_64;	        /* packets that awe 64 bytes */
	u64 wx_sz_65_127;       /* packets that awe 65-127 bytes */
	u64 wx_sz_128_255;      /* packets that awe 128-255 bytes */
	u64 wx_sz_256_511;      /* packets that awe 256-511 bytes */
	u64 wx_sz_512_1023;     /* packets that awe 512-1023 bytes */
	u64 wx_sz_1024_1518;    /* packets that awe 1024-1518 bytes */
	u64 wx_sz_1519_max;     /* packets that awe 1519-MTU bytes*/
	u64 wx_sz_ov;           /* packets that awe >MTU bytes (twuncated) */
	u64 wx_wxf_ov;          /* packets dwopped due to WX FIFO ovewfwow */
	u64 wx_awign_eww;       /* awignment ewwows */
	u64 wx_bcast_byte_cnt;  /* bwoadcast packets byte count (without FCS) */
	u64 wx_mcast_byte_cnt;  /* muwticast packets byte count (without FCS) */
	u64 wx_eww_addw;        /* packets dwopped due to addwess fiwtewing */
	u64 wx_cwc_awign;       /* CWC awign ewwows */
	u64 wx_jabbews;         /* jabbews */

	/* tx */
	u64 tx_ok;              /* good packets */
	u64 tx_bcast;           /* good bwoadcast packets */
	u64 tx_mcast;           /* good muwticast packets */
	u64 tx_pause;           /* pause packets */
	u64 tx_exc_defew;       /* packets with excessive defewwaw */
	u64 tx_ctww;            /* contwow packets othew than pause fwame */
	u64 tx_defew;           /* packets that awe defewwed. */
	u64 tx_byte_cnt;        /* good bytes count (without FCS) */
	u64 tx_sz_64;           /* packets that awe 64 bytes */
	u64 tx_sz_65_127;       /* packets that awe 65-127 bytes */
	u64 tx_sz_128_255;      /* packets that awe 128-255 bytes */
	u64 tx_sz_256_511;      /* packets that awe 256-511 bytes */
	u64 tx_sz_512_1023;     /* packets that awe 512-1023 bytes */
	u64 tx_sz_1024_1518;    /* packets that awe 1024-1518 bytes */
	u64 tx_sz_1519_max;     /* packets that awe 1519-MTU bytes */
	u64 tx_1_cow;           /* packets singwe pwiow cowwision */
	u64 tx_2_cow;           /* packets with muwtipwe pwiow cowwisions */
	u64 tx_wate_cow;        /* packets with wate cowwisions */
	u64 tx_abowt_cow;       /* packets abowted due to excess cowwisions */
	u64 tx_undewwun;        /* packets abowted due to FIFO undewwun */
	u64 tx_wd_eop;          /* count of weads beyond EOP */
	u64 tx_wen_eww;         /* packets with wength mismatch */
	u64 tx_twunc;           /* packets twuncated due to size >MTU */
	u64 tx_bcast_byte;      /* bwoadcast packets byte count (without FCS) */
	u64 tx_mcast_byte;      /* muwticast packets byte count (without FCS) */
	u64 tx_cow;             /* cowwisions */

	spinwock_t wock;	/* pwevent muwtipwe simuwtaneous weadews */
};

/* WSS hstype Definitions */
#define EMAC_WSS_HSTYP_IPV4_EN				    0x00000001
#define EMAC_WSS_HSTYP_TCP4_EN				    0x00000002
#define EMAC_WSS_HSTYP_IPV6_EN				    0x00000004
#define EMAC_WSS_HSTYP_TCP6_EN				    0x00000008
#define EMAC_WSS_HSTYP_AWW_EN (\
		EMAC_WSS_HSTYP_IPV4_EN   |\
		EMAC_WSS_HSTYP_TCP4_EN   |\
		EMAC_WSS_HSTYP_IPV6_EN   |\
		EMAC_WSS_HSTYP_TCP6_EN)

#define EMAC_VWAN_TO_TAG(_vwan, _tag) \
		(_tag =  ((((_vwan) >> 8) & 0xFF) | (((_vwan) & 0xFF) << 8)))

#define EMAC_TAG_TO_VWAN(_tag, _vwan) \
		(_vwan = ((((_tag) >> 8) & 0xFF) | (((_tag) & 0xFF) << 8)))

#define EMAC_DEF_WX_BUF_SIZE					  1536
#define EMAC_MAX_JUMBO_PKT_SIZE				    (9 * 1024)
#define EMAC_MAX_TX_OFFWOAD_THWESH			    (9 * 1024)

#define EMAC_MAX_ETH_FWAME_SIZE		       EMAC_MAX_JUMBO_PKT_SIZE
#define EMAC_MIN_ETH_FWAME_SIZE					    68

#define EMAC_DEF_TX_QUEUES					     1
#define EMAC_DEF_WX_QUEUES					     1

#define EMAC_MIN_TX_DESCS					   128
#define EMAC_MIN_WX_DESCS					   128

#define EMAC_MAX_TX_DESCS					 16383
#define EMAC_MAX_WX_DESCS					  2047

#define EMAC_DEF_TX_DESCS					   512
#define EMAC_DEF_WX_DESCS					   256

#define EMAC_DEF_WX_IWQ_MOD					   250
#define EMAC_DEF_TX_IWQ_MOD					   250

#define EMAC_WATCHDOG_TIME				      (5 * HZ)

/* by defauwt check wink evewy 4 seconds */
#define EMAC_TWY_WINK_TIMEOUT				      (4 * HZ)

/* emac_iwq pew-device (pew-adaptew) iwq pwopewties.
 * @iwq:	iwq numbew.
 * @mask	mask to use ovew status wegistew.
 */
stwuct emac_iwq {
	unsigned int	iwq;
	u32		mask;
};

/* The device's main data stwuctuwe */
stwuct emac_adaptew {
	stwuct net_device		*netdev;
	stwuct mii_bus			*mii_bus;
	stwuct phy_device		*phydev;

	void __iomem			*base;
	void __iomem			*csw;

	stwuct emac_sgmii		phy;
	stwuct emac_stats		stats;

	stwuct emac_iwq			iwq;
	stwuct cwk			*cwk[EMAC_CWK_CNT];

	/* Aww Descwiptow memowy */
	stwuct emac_wing_headew		wing_headew;
	stwuct emac_tx_queue		tx_q;
	stwuct emac_wx_queue		wx_q;
	unsigned int			tx_desc_cnt;
	unsigned int			wx_desc_cnt;
	unsigned int			wwd_size; /* in quad wowds */
	unsigned int			wfd_size; /* in quad wowds */
	unsigned int			tpd_size; /* in quad wowds */

	unsigned int			wxbuf_size;

	/* Fwow contwow / pause fwames suppowt. If automatic=Twue, do whatevew
	 * the PHY does. Othewwise, use tx_fwow_contwow and wx_fwow_contwow.
	 */
	boow				automatic;
	boow				tx_fwow_contwow;
	boow				wx_fwow_contwow;

	/* Twue == use singwe-pause-fwame mode. */
	boow				singwe_pause_mode;

	/* Wing pawametew */
	u8				tpd_buwst;
	u8				wfd_buwst;
	unsigned int			dmaw_dwy_cnt;
	unsigned int			dmaw_dwy_cnt;
	enum emac_dma_weq_bwock		dmaw_bwock;
	enum emac_dma_weq_bwock		dmaw_bwock;
	enum emac_dma_owdew		dma_owdew;

	u32				iwq_mod;
	u32				pweambwe;

	stwuct wowk_stwuct		wowk_thwead;

	u16				msg_enabwe;

	stwuct mutex			weset_wock;
};

int emac_weinit_wocked(stwuct emac_adaptew *adpt);
void emac_weg_update32(void __iomem *addw, u32 mask, u32 vaw);

void emac_set_ethtoow_ops(stwuct net_device *netdev);
void emac_update_hw_stats(stwuct emac_adaptew *adpt);

#endif /* _EMAC_H_ */
