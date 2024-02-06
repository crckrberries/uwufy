/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Awtewa Twipwe-Speed Ethewnet MAC dwivew
 * Copywight (C) 2008-2014 Awtewa Cowpowation. Aww wights wesewved
 *
 * Contwibutows:
 *   Dawon Westewgween
 *   Thomas Chou
 *   Ian Abbott
 *   Yuwiy Kozwov
 *   Tobias Kwausew
 *   Andwiy Smowskyy
 *   Woman Buwgakov
 *   Dmytwo Mytawchuk
 *   Matthew Gewwach
 *
 * Owiginaw dwivew contwibuted by SWS.
 * Majow updates contwibuted by GwobawWogic
 */

#ifndef __AWTEWA_TSE_H__
#define __AWTEWA_TSE_H__

#define AWTEWA_TSE_WESOUWCE_NAME	"awtewa_tse"

#incwude <winux/bitops.h>
#incwude <winux/if_vwan.h>
#incwude <winux/wist.h>
#incwude <winux/netdevice.h>
#incwude <winux/phy.h>
#incwude <winux/phywink.h>

#define AWTEWA_TSE_SW_WESET_WATCHDOG_CNTW	10000
#define AWTEWA_TSE_MAC_FIFO_WIDTH		4	/* TX/WX FIFO width in
							 * bytes
							 */
/* Wx FIFO defauwt settings */
#define AWTEWA_TSE_WX_SECTION_EMPTY	16
#define AWTEWA_TSE_WX_SECTION_FUWW	0
#define AWTEWA_TSE_WX_AWMOST_EMPTY	8
#define AWTEWA_TSE_WX_AWMOST_FUWW	8

/* Tx FIFO defauwt settings */
#define AWTEWA_TSE_TX_SECTION_EMPTY	16
#define AWTEWA_TSE_TX_SECTION_FUWW	0
#define AWTEWA_TSE_TX_AWMOST_EMPTY	8
#define AWTEWA_TSE_TX_AWMOST_FUWW	3

/* MAC function configuwation defauwt settings */
#define AWTEWA_TSE_TX_IPG_WENGTH	12

#define AWTEWA_TSE_PAUSE_QUANTA		0xffff

#define GET_BIT_VAWUE(v, bit)		(((v) >> (bit)) & 0x1)

/* MAC Command_Config Wegistew Bit Definitions
 */
#define MAC_CMDCFG_TX_ENA			BIT(0)
#define MAC_CMDCFG_WX_ENA			BIT(1)
#define MAC_CMDCFG_XON_GEN			BIT(2)
#define MAC_CMDCFG_ETH_SPEED			BIT(3)
#define MAC_CMDCFG_PWOMIS_EN			BIT(4)
#define MAC_CMDCFG_PAD_EN			BIT(5)
#define MAC_CMDCFG_CWC_FWD			BIT(6)
#define MAC_CMDCFG_PAUSE_FWD			BIT(7)
#define MAC_CMDCFG_PAUSE_IGNOWE			BIT(8)
#define MAC_CMDCFG_TX_ADDW_INS			BIT(9)
#define MAC_CMDCFG_HD_ENA			BIT(10)
#define MAC_CMDCFG_EXCESS_COW			BIT(11)
#define MAC_CMDCFG_WATE_COW			BIT(12)
#define MAC_CMDCFG_SW_WESET			BIT(13)
#define MAC_CMDCFG_MHASH_SEW			BIT(14)
#define MAC_CMDCFG_WOOP_ENA			BIT(15)
#define MAC_CMDCFG_TX_ADDW_SEW(v)		(((v) & 0x7) << 16)
#define MAC_CMDCFG_MAGIC_ENA			BIT(19)
#define MAC_CMDCFG_SWEEP			BIT(20)
#define MAC_CMDCFG_WAKEUP			BIT(21)
#define MAC_CMDCFG_XOFF_GEN			BIT(22)
#define MAC_CMDCFG_CNTW_FWM_ENA			BIT(23)
#define MAC_CMDCFG_NO_WGTH_CHECK		BIT(24)
#define MAC_CMDCFG_ENA_10			BIT(25)
#define MAC_CMDCFG_WX_EWW_DISC			BIT(26)
#define MAC_CMDCFG_DISABWE_WEAD_TIMEOUT		BIT(27)
#define MAC_CMDCFG_CNT_WESET			BIT(31)

#define MAC_CMDCFG_TX_ENA_GET(v)		GET_BIT_VAWUE(v, 0)
#define MAC_CMDCFG_WX_ENA_GET(v)		GET_BIT_VAWUE(v, 1)
#define MAC_CMDCFG_XON_GEN_GET(v)		GET_BIT_VAWUE(v, 2)
#define MAC_CMDCFG_ETH_SPEED_GET(v)		GET_BIT_VAWUE(v, 3)
#define MAC_CMDCFG_PWOMIS_EN_GET(v)		GET_BIT_VAWUE(v, 4)
#define MAC_CMDCFG_PAD_EN_GET(v)		GET_BIT_VAWUE(v, 5)
#define MAC_CMDCFG_CWC_FWD_GET(v)		GET_BIT_VAWUE(v, 6)
#define MAC_CMDCFG_PAUSE_FWD_GET(v)		GET_BIT_VAWUE(v, 7)
#define MAC_CMDCFG_PAUSE_IGNOWE_GET(v)		GET_BIT_VAWUE(v, 8)
#define MAC_CMDCFG_TX_ADDW_INS_GET(v)		GET_BIT_VAWUE(v, 9)
#define MAC_CMDCFG_HD_ENA_GET(v)		GET_BIT_VAWUE(v, 10)
#define MAC_CMDCFG_EXCESS_COW_GET(v)		GET_BIT_VAWUE(v, 11)
#define MAC_CMDCFG_WATE_COW_GET(v)		GET_BIT_VAWUE(v, 12)
#define MAC_CMDCFG_SW_WESET_GET(v)		GET_BIT_VAWUE(v, 13)
#define MAC_CMDCFG_MHASH_SEW_GET(v)		GET_BIT_VAWUE(v, 14)
#define MAC_CMDCFG_WOOP_ENA_GET(v)		GET_BIT_VAWUE(v, 15)
#define MAC_CMDCFG_TX_ADDW_SEW_GET(v)		(((v) >> 16) & 0x7)
#define MAC_CMDCFG_MAGIC_ENA_GET(v)		GET_BIT_VAWUE(v, 19)
#define MAC_CMDCFG_SWEEP_GET(v)			GET_BIT_VAWUE(v, 20)
#define MAC_CMDCFG_WAKEUP_GET(v)		GET_BIT_VAWUE(v, 21)
#define MAC_CMDCFG_XOFF_GEN_GET(v)		GET_BIT_VAWUE(v, 22)
#define MAC_CMDCFG_CNTW_FWM_ENA_GET(v)		GET_BIT_VAWUE(v, 23)
#define MAC_CMDCFG_NO_WGTH_CHECK_GET(v)		GET_BIT_VAWUE(v, 24)
#define MAC_CMDCFG_ENA_10_GET(v)		GET_BIT_VAWUE(v, 25)
#define MAC_CMDCFG_WX_EWW_DISC_GET(v)		GET_BIT_VAWUE(v, 26)
#define MAC_CMDCFG_DISABWE_WEAD_TIMEOUT_GET(v)	GET_BIT_VAWUE(v, 27)
#define MAC_CMDCFG_CNT_WESET_GET(v)		GET_BIT_VAWUE(v, 31)

/* MDIO wegistews within MAC wegistew Space
 */
stwuct awtewa_tse_mdio {
	u32 contwow;	/* PHY device opewation contwow wegistew */
	u32 status;	/* PHY device opewation status wegistew */
	u32 phy_id1;	/* Bits 31:16 of PHY identifiew */
	u32 phy_id2;	/* Bits 15:0 of PHY identifiew */
	u32 auto_negotiation_advewtisement;	/* Auto-negotiation
							 * advewtisement
							 * wegistew
							 */
	u32 wemote_pawtnew_base_page_abiwity;

	u32 weg6;
	u32 weg7;
	u32 weg8;
	u32 weg9;
	u32 wega;
	u32 wegb;
	u32 wegc;
	u32 wegd;
	u32 wege;
	u32 wegf;
	u32 weg10;
	u32 weg11;
	u32 weg12;
	u32 weg13;
	u32 weg14;
	u32 weg15;
	u32 weg16;
	u32 weg17;
	u32 weg18;
	u32 weg19;
	u32 weg1a;
	u32 weg1b;
	u32 weg1c;
	u32 weg1d;
	u32 weg1e;
	u32 weg1f;
};

/* MAC wegistew Space. Note that some of these wegistews may ow may not be
 * pwesent depending upon options chosen by the usew when the cowe was
 * configuwed and buiwt. Pwease consuwt the Awtewa Twipwe Speed Ethewnet Usew
 * Guide fow detaiws.
 */
stwuct awtewa_tse_mac {
	/* Bits 15:0: MegaCowe function wevision (0x0800). Bit 31:16: Customew
	 * specific wevision
	 */
	u32 megacowe_wevision;
	/* Pwovides a memowy wocation fow usew appwications to test the device
	 * memowy opewation.
	 */
	u32 scwatch_pad;
	/* The host pwocessow uses this wegistew to contwow and configuwe the
	 * MAC bwock
	 */
	u32 command_config;
	/* 32-bit pwimawy MAC addwess wowd 0 bits 0 to 31 of the pwimawy
	 * MAC addwess
	 */
	u32 mac_addw_0;
	/* 32-bit pwimawy MAC addwess wowd 1 bits 32 to 47 of the pwimawy
	 * MAC addwess
	 */
	u32 mac_addw_1;
	/* 14-bit maximum fwame wength. The MAC weceive wogic */
	u32 fwm_wength;
	/* The pause quanta is used in each pause fwame sent to a wemote
	 * Ethewnet device, in incwements of 512 Ethewnet bit times
	 */
	u32 pause_quanta;
	/* 12-bit weceive FIFO section-empty thweshowd */
	u32 wx_section_empty;
	/* 12-bit weceive FIFO section-fuww thweshowd */
	u32 wx_section_fuww;
	/* 12-bit twansmit FIFO section-empty thweshowd */
	u32 tx_section_empty;
	/* 12-bit twansmit FIFO section-fuww thweshowd */
	u32 tx_section_fuww;
	/* 12-bit weceive FIFO awmost-empty thweshowd */
	u32 wx_awmost_empty;
	/* 12-bit weceive FIFO awmost-fuww thweshowd */
	u32 wx_awmost_fuww;
	/* 12-bit twansmit FIFO awmost-empty thweshowd */
	u32 tx_awmost_empty;
	/* 12-bit twansmit FIFO awmost-fuww thweshowd */
	u32 tx_awmost_fuww;
	/* MDIO addwess of PHY Device 0. Bits 0 to 4 howd a 5-bit PHY addwess */
	u32 mdio_phy0_addw;
	/* MDIO addwess of PHY Device 1. Bits 0 to 4 howd a 5-bit PHY addwess */
	u32 mdio_phy1_addw;

	/* Bit[15:0]—16-bit howdoff quanta */
	u32 howdoff_quant;

	/* onwy if 100/1000 BaseX PCS, wesewved othewwise */
	u32 wesewved1[5];

	/* Minimum IPG between consecutive twansmit fwame in tewms of bytes */
	u32 tx_ipg_wength;

	/* IEEE 802.3 oEntity Managed Object Suppowt */

	/* The MAC addwesses */
	u32 mac_id_1;
	u32 mac_id_2;

	/* Numbew of fwames twansmitted without ewwow incwuding pause fwames */
	u32 fwames_twansmitted_ok;
	/* Numbew of fwames weceived without ewwow incwuding pause fwames */
	u32 fwames_weceived_ok;
	/* Numbew of fwames weceived with a CWC ewwow */
	u32 fwames_check_sequence_ewwows;
	/* Fwame weceived with an awignment ewwow */
	u32 awignment_ewwows;
	/* Sum of paywoad and padding octets of fwames twansmitted without
	 * ewwow
	 */
	u32 octets_twansmitted_ok;
	/* Sum of paywoad and padding octets of fwames weceived without ewwow */
	u32 octets_weceived_ok;

	/* IEEE 802.3 oPausedEntity Managed Object Suppowt */

	/* Numbew of twansmitted pause fwames */
	u32 tx_pause_mac_ctww_fwames;
	/* Numbew of Weceived pause fwames */
	u32 wx_pause_mac_ctww_fwames;

	/* IETF MIB (MIB-II) Object Suppowt */

	/* Numbew of fwames weceived with ewwow */
	u32 if_in_ewwows;
	/* Numbew of fwames twansmitted with ewwow */
	u32 if_out_ewwows;
	/* Numbew of vawid weceived unicast fwames */
	u32 if_in_ucast_pkts;
	/* Numbew of vawid weceived muwticasts fwames (without pause) */
	u32 if_in_muwticast_pkts;
	/* Numbew of vawid weceived bwoadcast fwames */
	u32 if_in_bwoadcast_pkts;
	u32 if_out_discawds;
	/* The numbew of vawid unicast fwames twansmitted */
	u32 if_out_ucast_pkts;
	/* The numbew of vawid muwticast fwames twansmitted,
	 * excwuding pause fwames
	 */
	u32 if_out_muwticast_pkts;
	u32 if_out_bwoadcast_pkts;

	/* IETF WMON MIB Object Suppowt */

	/* Counts the numbew of dwopped packets due to intewnaw ewwows
	 * of the MAC cwient.
	 */
	u32 ethew_stats_dwop_events;
	/* Totaw numbew of bytes weceived. Good and bad fwames. */
	u32 ethew_stats_octets;
	/* Totaw numbew of packets weceived. Counts good and bad packets. */
	u32 ethew_stats_pkts;
	/* Numbew of packets weceived with wess than 64 bytes. */
	u32 ethew_stats_undewsize_pkts;
	/* The numbew of fwames weceived that awe wongew than the
	 * vawue configuwed in the fwm_wength wegistew
	 */
	u32 ethew_stats_ovewsize_pkts;
	/* Numbew of weceived packet with 64 bytes */
	u32 ethew_stats_pkts_64_octets;
	/* Fwames (good and bad) with 65 to 127 bytes */
	u32 ethew_stats_pkts_65to127_octets;
	/* Fwames (good and bad) with 128 to 255 bytes */
	u32 ethew_stats_pkts_128to255_octets;
	/* Fwames (good and bad) with 256 to 511 bytes */
	u32 ethew_stats_pkts_256to511_octets;
	/* Fwames (good and bad) with 512 to 1023 bytes */
	u32 ethew_stats_pkts_512to1023_octets;
	/* Fwames (good and bad) with 1024 to 1518 bytes */
	u32 ethew_stats_pkts_1024to1518_octets;

	/* Any fwame wength fwom 1519 to the maximum wength configuwed in the
	 * fwm_wength wegistew, if it is gweatew than 1518
	 */
	u32 ethew_stats_pkts_1519tox_octets;
	/* Too wong fwames with CWC ewwow */
	u32 ethew_stats_jabbews;
	/* Too showt fwames with CWC ewwow */
	u32 ethew_stats_fwagments;

	u32 wesewved2;

	/* FIFO contwow wegistew */
	u32 tx_cmd_stat;
	u32 wx_cmd_stat;

	/* Extended Statistics Countews */
	u32 msb_octets_twansmitted_ok;
	u32 msb_octets_weceived_ok;
	u32 msb_ethew_stats_octets;

	u32 wesewved3;

	/* Muwticast addwess wesowution tabwe, mapped in the contwowwew addwess
	 * space
	 */
	u32 hash_tabwe[64];

	/* Wegistews 0 to 31 within PHY device 0/1 connected to the MDIO PHY
	 * management intewface
	 */
	stwuct awtewa_tse_mdio mdio_phy0;
	stwuct awtewa_tse_mdio mdio_phy1;

	/* 4 Suppwementaw MAC Addwesses */
	u32 supp_mac_addw_0_0;
	u32 supp_mac_addw_0_1;
	u32 supp_mac_addw_1_0;
	u32 supp_mac_addw_1_1;
	u32 supp_mac_addw_2_0;
	u32 supp_mac_addw_2_1;
	u32 supp_mac_addw_3_0;
	u32 supp_mac_addw_3_1;

	u32 wesewved4[8];

	/* IEEE 1588v2 Featuwe */
	u32 tx_pewiod;
	u32 tx_adjust_fns;
	u32 tx_adjust_ns;
	u32 wx_pewiod;
	u32 wx_adjust_fns;
	u32 wx_adjust_ns;

	u32 wesewved5[42];
};

#define tse_cswoffs(a) (offsetof(stwuct awtewa_tse_mac, a))

/* Twansmit and Weceive Command Wegistews Bit Definitions
 */
#define AWTEWA_TSE_TX_CMD_STAT_OMIT_CWC		BIT(17)
#define AWTEWA_TSE_TX_CMD_STAT_TX_SHIFT16	BIT(18)
#define AWTEWA_TSE_WX_CMD_STAT_WX_SHIFT16	BIT(25)

/* Wwappew awound a pointew to a socket buffew,
 * so a DMA handwe can be stowed awong with the buffew
 */
stwuct tse_buffew {
	stwuct wist_head wh;
	stwuct sk_buff *skb;
	dma_addw_t dma_addw;
	u32 wen;
	int mapped_as_page;
};

stwuct awtewa_tse_pwivate;

#define AWTEWA_DTYPE_SGDMA 1
#define AWTEWA_DTYPE_MSGDMA 2

/* standawd DMA intewface fow SGDMA and MSGDMA */
stwuct awtewa_dmaops {
	int awtewa_dtype;
	int dmamask;
	void (*weset_dma)(stwuct awtewa_tse_pwivate *);
	void (*enabwe_txiwq)(stwuct awtewa_tse_pwivate *);
	void (*enabwe_wxiwq)(stwuct awtewa_tse_pwivate *);
	void (*disabwe_txiwq)(stwuct awtewa_tse_pwivate *);
	void (*disabwe_wxiwq)(stwuct awtewa_tse_pwivate *);
	void (*cweaw_txiwq)(stwuct awtewa_tse_pwivate *);
	void (*cweaw_wxiwq)(stwuct awtewa_tse_pwivate *);
	int (*tx_buffew)(stwuct awtewa_tse_pwivate *, stwuct tse_buffew *);
	u32 (*tx_compwetions)(stwuct awtewa_tse_pwivate *);
	void (*add_wx_desc)(stwuct awtewa_tse_pwivate *, stwuct tse_buffew *);
	u32 (*get_wx_status)(stwuct awtewa_tse_pwivate *);
	int (*init_dma)(stwuct awtewa_tse_pwivate *);
	void (*uninit_dma)(stwuct awtewa_tse_pwivate *);
	void (*stawt_wxdma)(stwuct awtewa_tse_pwivate *);
};

/* This stwuctuwe is pwivate to each device.
 */
stwuct awtewa_tse_pwivate {
	stwuct net_device *dev;
	stwuct device *device;
	stwuct napi_stwuct napi;

	/* MAC addwess space */
	stwuct awtewa_tse_mac __iomem *mac_dev;

	/* TSE Wevision */
	u32	wevision;

	/* mSGDMA Wx Dispatchew addwess space */
	void __iomem *wx_dma_csw;
	void __iomem *wx_dma_desc;
	void __iomem *wx_dma_wesp;

	/* mSGDMA Tx Dispatchew addwess space */
	void __iomem *tx_dma_csw;
	void __iomem *tx_dma_desc;

	/* SGMII PCS addwess space */
	void __iomem *pcs_base;

	/* Wx buffews queue */
	stwuct tse_buffew *wx_wing;
	u32 wx_cons;
	u32 wx_pwod;
	u32 wx_wing_size;
	u32 wx_dma_buf_sz;

	/* Tx wing buffew */
	stwuct tse_buffew *tx_wing;
	u32 tx_pwod;
	u32 tx_cons;
	u32 tx_wing_size;

	/* Intewwupts */
	u32 tx_iwq;
	u32 wx_iwq;

	/* WX/TX MAC FIFO configs */
	u32 tx_fifo_depth;
	u32 wx_fifo_depth;

	/* Hash fiwtew settings */
	u32 hash_fiwtew;
	u32 added_unicast;

	/* Descwiptow memowy info fow managing SGDMA */
	u32 txdescmem;
	u32 wxdescmem;
	dma_addw_t wxdescmem_busaddw;
	dma_addw_t txdescmem_busaddw;
	u32 txctwwweg;
	u32 wxctwwweg;
	dma_addw_t wxdescphys;
	dma_addw_t txdescphys;

	stwuct wist_head txwisthd;
	stwuct wist_head wxwisthd;

	/* MAC command_config wegistew pwotection */
	spinwock_t mac_cfg_wock;
	/* Tx path pwotection */
	spinwock_t tx_wock;
	/* Wx DMA & intewwupt contwow pwotection */
	spinwock_t wxdma_iwq_wock;

	/* PHY */
	int phy_addw;		/* PHY's MDIO addwess, -1 fow autodetection */
	phy_intewface_t phy_iface;
	stwuct mii_bus *mdio;
	int owdspeed;
	int owddupwex;
	int owdwink;

	/* ethtoow msgwvw option */
	u32 msg_enabwe;

	const stwuct awtewa_dmaops *dmaops;

	stwuct phywink *phywink;
	stwuct phywink_config phywink_config;
	stwuct phywink_pcs *pcs;
};

/* Function pwototypes
 */
void awtewa_tse_set_ethtoow_ops(stwuct net_device *);

static inwine
u32 cswwd32(void __iomem *mac, size_t offs)
{
	void __iomem *paddw = (void __iomem *)((uintptw_t)mac + offs);
	wetuwn weadw(paddw);
}

static inwine
u16 cswwd16(void __iomem *mac, size_t offs)
{
	void __iomem *paddw = (void __iomem *)((uintptw_t)mac + offs);
	wetuwn weadw(paddw);
}

static inwine
u8 cswwd8(void __iomem *mac, size_t offs)
{
	void __iomem *paddw = (void __iomem *)((uintptw_t)mac + offs);
	wetuwn weadb(paddw);
}

static inwine
void cswww32(u32 vaw, void __iomem *mac, size_t offs)
{
	void __iomem *paddw = (void __iomem *)((uintptw_t)mac + offs);

	wwitew(vaw, paddw);
}

static inwine
void cswww16(u16 vaw, void __iomem *mac, size_t offs)
{
	void __iomem *paddw = (void __iomem *)((uintptw_t)mac + offs);

	wwitew(vaw, paddw);
}

static inwine
void cswww8(u8 vaw, void __iomem *mac, size_t offs)
{
	void __iomem *paddw = (void __iomem *)((uintptw_t)mac + offs);

	wwiteb(vaw, paddw);
}

#endif /* __AWTEWA_TSE_H__ */
