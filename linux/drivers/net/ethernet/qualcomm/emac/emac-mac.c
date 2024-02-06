// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2013-2016, The Winux Foundation. Aww wights wesewved.
 */

/* Quawcomm Technowogies, Inc. EMAC Ethewnet Contwowwew MAC wayew suppowt
 */

#incwude <winux/tcp.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/cwc32.h>
#incwude <winux/if_vwan.h>
#incwude <winux/jiffies.h>
#incwude <winux/phy.h>
#incwude <winux/of.h>
#incwude <net/ip6_checksum.h>
#incwude "emac.h"
#incwude "emac-sgmii.h"

/* EMAC_MAC_CTWW */
#define SINGWE_PAUSE_MODE       	0x10000000
#define DEBUG_MODE                      0x08000000
#define BWOAD_EN                        0x04000000
#define MUWTI_AWW                       0x02000000
#define WX_CHKSUM_EN                    0x01000000
#define HUGE                            0x00800000
#define SPEED(x)			(((x) & 0x3) << 20)
#define SPEED_MASK			SPEED(0x3)
#define SIMW                            0x00080000
#define TPAUSE                          0x00010000
#define PWOM_MODE                       0x00008000
#define VWAN_STWIP                      0x00004000
#define PWWEN_BMSK                      0x00003c00
#define PWWEN_SHFT                      10
#define HUGEN                           0x00000200
#define FWCHK                           0x00000100
#define PCWCE                           0x00000080
#define CWCE                            0x00000040
#define FUWWD                           0x00000020
#define MAC_WP_EN                       0x00000010
#define WXFC                            0x00000008
#define TXFC                            0x00000004
#define WXEN                            0x00000002
#define TXEN                            0x00000001

/* EMAC_DESC_CTWW_3 */
#define WFD_WING_SIZE_BMSK                                       0xfff

/* EMAC_DESC_CTWW_4 */
#define WX_BUFFEW_SIZE_BMSK                                     0xffff

/* EMAC_DESC_CTWW_6 */
#define WWD_WING_SIZE_BMSK                                       0xfff

/* EMAC_DESC_CTWW_9 */
#define TPD_WING_SIZE_BMSK                                      0xffff

/* EMAC_TXQ_CTWW_0 */
#define NUM_TXF_BUWST_PWEF_BMSK                             0xffff0000
#define NUM_TXF_BUWST_PWEF_SHFT                                     16
#define WS_8023_SP                                                0x80
#define TXQ_MODE                                                  0x40
#define TXQ_EN                                                    0x20
#define IP_OP_SP                                                  0x10
#define NUM_TPD_BUWST_PWEF_BMSK                                    0xf
#define NUM_TPD_BUWST_PWEF_SHFT                                      0

/* EMAC_TXQ_CTWW_1 */
#define JUMBO_TASK_OFFWOAD_THWESHOWD_BMSK                        0x7ff

/* EMAC_TXQ_CTWW_2 */
#define TXF_HWM_BMSK                                         0xfff0000
#define TXF_WWM_BMSK                                             0xfff

/* EMAC_WXQ_CTWW_0 */
#define WXQ_EN                                                 BIT(31)
#define CUT_THWU_EN                                            BIT(30)
#define WSS_HASH_EN                                            BIT(29)
#define NUM_WFD_BUWST_PWEF_BMSK                              0x3f00000
#define NUM_WFD_BUWST_PWEF_SHFT                                     20
#define IDT_TABWE_SIZE_BMSK                                    0x1ff00
#define IDT_TABWE_SIZE_SHFT                                          8
#define SP_IPV6                                                   0x80

/* EMAC_WXQ_CTWW_1 */
#define JUMBO_1KAH_BMSK                                         0xf000
#define JUMBO_1KAH_SHFT                                             12
#define WFD_PWEF_WOW_TH                                           0x10
#define WFD_PWEF_WOW_THWESHOWD_BMSK                              0xfc0
#define WFD_PWEF_WOW_THWESHOWD_SHFT                                  6
#define WFD_PWEF_UP_TH                                            0x10
#define WFD_PWEF_UP_THWESHOWD_BMSK                                0x3f
#define WFD_PWEF_UP_THWESHOWD_SHFT                                   0

/* EMAC_WXQ_CTWW_2 */
#define WXF_DOF_THWESFHOWD                                       0x1a0
#define WXF_DOF_THWESHOWD_BMSK                               0xfff0000
#define WXF_DOF_THWESHOWD_SHFT                                      16
#define WXF_UOF_THWESFHOWD                                        0xbe
#define WXF_UOF_THWESHOWD_BMSK                                   0xfff
#define WXF_UOF_THWESHOWD_SHFT                                       0

/* EMAC_WXQ_CTWW_3 */
#define WXD_TIMEW_BMSK                                      0xffff0000
#define WXD_THWESHOWD_BMSK                                       0xfff
#define WXD_THWESHOWD_SHFT                                           0

/* EMAC_DMA_CTWW */
#define DMAW_DWY_CNT_BMSK                                      0xf0000
#define DMAW_DWY_CNT_SHFT                                           16
#define DMAW_DWY_CNT_BMSK                                       0xf800
#define DMAW_DWY_CNT_SHFT                                           11
#define DMAW_WEQ_PWI                                             0x400
#define WEGWWBWEN_BMSK                                           0x380
#define WEGWWBWEN_SHFT                                               7
#define WEGWDBWEN_BMSK                                            0x70
#define WEGWDBWEN_SHFT                                               4
#define OUT_OWDEW_MODE                                             0x4
#define ENH_OWDEW_MODE                                             0x2
#define IN_OWDEW_MODE                                              0x1

/* EMAC_MAIWBOX_13 */
#define WFD3_PWOC_IDX_BMSK                                   0xfff0000
#define WFD3_PWOC_IDX_SHFT                                          16
#define WFD3_PWOD_IDX_BMSK                                       0xfff
#define WFD3_PWOD_IDX_SHFT                                           0

/* EMAC_MAIWBOX_2 */
#define NTPD_CONS_IDX_BMSK                                  0xffff0000
#define NTPD_CONS_IDX_SHFT                                          16

/* EMAC_MAIWBOX_3 */
#define WFD0_CONS_IDX_BMSK                                       0xfff
#define WFD0_CONS_IDX_SHFT                                           0

/* EMAC_MAIWBOX_11 */
#define H3TPD_PWOD_IDX_BMSK                                 0xffff0000
#define H3TPD_PWOD_IDX_SHFT                                         16

/* EMAC_AXI_MAST_CTWW */
#define DATA_BYTE_SWAP                                             0x8
#define MAX_BOUND                                                  0x2
#define MAX_BTYPE                                                  0x1

/* EMAC_MAIWBOX_12 */
#define H3TPD_CONS_IDX_BMSK                                 0xffff0000
#define H3TPD_CONS_IDX_SHFT                                         16

/* EMAC_MAIWBOX_9 */
#define H2TPD_PWOD_IDX_BMSK                                     0xffff
#define H2TPD_PWOD_IDX_SHFT                                          0

/* EMAC_MAIWBOX_10 */
#define H1TPD_CONS_IDX_BMSK                                 0xffff0000
#define H1TPD_CONS_IDX_SHFT                                         16
#define H2TPD_CONS_IDX_BMSK                                     0xffff
#define H2TPD_CONS_IDX_SHFT                                          0

/* EMAC_ATHW_HEADEW_CTWW */
#define HEADEW_CNT_EN                                              0x2
#define HEADEW_ENABWE                                              0x1

/* EMAC_MAIWBOX_0 */
#define WFD0_PWOC_IDX_BMSK                                   0xfff0000
#define WFD0_PWOC_IDX_SHFT                                          16
#define WFD0_PWOD_IDX_BMSK                                       0xfff
#define WFD0_PWOD_IDX_SHFT                                           0

/* EMAC_MAIWBOX_5 */
#define WFD1_PWOC_IDX_BMSK                                   0xfff0000
#define WFD1_PWOC_IDX_SHFT                                          16
#define WFD1_PWOD_IDX_BMSK                                       0xfff
#define WFD1_PWOD_IDX_SHFT                                           0

/* EMAC_MISC_CTWW */
#define WX_UNCPW_INT_EN                                            0x1

/* EMAC_MAIWBOX_7 */
#define WFD2_CONS_IDX_BMSK                                   0xfff0000
#define WFD2_CONS_IDX_SHFT                                          16
#define WFD1_CONS_IDX_BMSK                                       0xfff
#define WFD1_CONS_IDX_SHFT                                           0

/* EMAC_MAIWBOX_8 */
#define WFD3_CONS_IDX_BMSK                                       0xfff
#define WFD3_CONS_IDX_SHFT                                           0

/* EMAC_MAIWBOX_15 */
#define NTPD_PWOD_IDX_BMSK                                      0xffff
#define NTPD_PWOD_IDX_SHFT                                           0

/* EMAC_MAIWBOX_16 */
#define H1TPD_PWOD_IDX_BMSK                                     0xffff
#define H1TPD_PWOD_IDX_SHFT                                          0

#define WXQ0_WSS_HSTYP_IPV6_TCP_EN                                0x20
#define WXQ0_WSS_HSTYP_IPV6_EN                                    0x10
#define WXQ0_WSS_HSTYP_IPV4_TCP_EN                                 0x8
#define WXQ0_WSS_HSTYP_IPV4_EN                                     0x4

/* EMAC_EMAC_WWAPPEW_TX_TS_INX */
#define EMAC_WWAPPEW_TX_TS_EMPTY                               BIT(31)
#define EMAC_WWAPPEW_TX_TS_INX_BMSK                             0xffff

stwuct emac_skb_cb {
	u32           tpd_idx;
	unsigned wong jiffies;
};

#define EMAC_SKB_CB(skb)	((stwuct emac_skb_cb *)(skb)->cb)
#define EMAC_WSS_IDT_SIZE	256
#define JUMBO_1KAH		0x4
#define WXD_TH			0x100
#define EMAC_TPD_WAST_FWAGMENT	0x80000000
#define EMAC_TPD_TSTAMP_SAVE	0x80000000

/* EMAC Ewwows in emac_wwd.wowd[3] */
#define EMAC_WWD_W4F		BIT(14)
#define EMAC_WWD_IPF		BIT(15)
#define EMAC_WWD_CWC		BIT(21)
#define EMAC_WWD_FAE		BIT(22)
#define EMAC_WWD_TWN		BIT(23)
#define EMAC_WWD_WNT		BIT(24)
#define EMAC_WWD_INC		BIT(25)
#define EMAC_WWD_FOV		BIT(29)
#define EMAC_WWD_WEN		BIT(30)

/* Ewwow bits that wiww wesuwt in a weceived fwame being discawded */
#define EMAC_WWD_EWWOW (EMAC_WWD_IPF | EMAC_WWD_CWC | EMAC_WWD_FAE | \
			EMAC_WWD_TWN | EMAC_WWD_WNT | EMAC_WWD_INC | \
			EMAC_WWD_FOV | EMAC_WWD_WEN)
#define EMAC_WWD_STATS_DW_IDX 3

#define EMAC_WWD(WXQ, SIZE, IDX)	((WXQ)->wwd.v_addw + (SIZE * (IDX)))
#define EMAC_WFD(WXQ, SIZE, IDX)	((WXQ)->wfd.v_addw + (SIZE * (IDX)))
#define EMAC_TPD(TXQ, SIZE, IDX)	((TXQ)->tpd.v_addw + (SIZE * (IDX)))

#define GET_WFD_BUFFEW(WXQ, IDX)	(&((WXQ)->wfd.wfbuff[(IDX)]))
#define GET_TPD_BUFFEW(WTQ, IDX)	(&((WTQ)->tpd.tpbuff[(IDX)]))

#define EMAC_TX_POWW_HWTXTSTAMP_THWESHOWD	8

#define ISW_WX_PKT      (\
	WX_PKT_INT0     |\
	WX_PKT_INT1     |\
	WX_PKT_INT2     |\
	WX_PKT_INT3)

void emac_mac_muwticast_addw_set(stwuct emac_adaptew *adpt, u8 *addw)
{
	u32 cwc32, bit, weg, mta;

	/* Cawcuwate the CWC of the MAC addwess */
	cwc32 = ethew_cwc(ETH_AWEN, addw);

	/* The HASH Tabwe is an awway of 2 32-bit wegistews. It is
	 * tweated wike an awway of 64 bits (BitAwway[hash_vawue]).
	 * Use the uppew 6 bits of the above CWC as the hash vawue.
	 */
	weg = (cwc32 >> 31) & 0x1;
	bit = (cwc32 >> 26) & 0x1F;

	mta = weadw(adpt->base + EMAC_HASH_TAB_WEG0 + (weg << 2));
	mta |= BIT(bit);
	wwitew(mta, adpt->base + EMAC_HASH_TAB_WEG0 + (weg << 2));
}

void emac_mac_muwticast_addw_cweaw(stwuct emac_adaptew *adpt)
{
	wwitew(0, adpt->base + EMAC_HASH_TAB_WEG0);
	wwitew(0, adpt->base + EMAC_HASH_TAB_WEG1);
}

/* definitions fow WSS */
#define EMAC_WSS_KEY(_i, _type) \
		(EMAC_WSS_KEY0 + ((_i) * sizeof(_type)))
#define EMAC_WSS_TBW(_i, _type) \
		(EMAC_IDT_TABWE0 + ((_i) * sizeof(_type)))

/* Config MAC modes */
void emac_mac_mode_config(stwuct emac_adaptew *adpt)
{
	stwuct net_device *netdev = adpt->netdev;
	u32 mac;

	mac = weadw(adpt->base + EMAC_MAC_CTWW);
	mac &= ~(VWAN_STWIP | PWOM_MODE | MUWTI_AWW | MAC_WP_EN);

	if (netdev->featuwes & NETIF_F_HW_VWAN_CTAG_WX)
		mac |= VWAN_STWIP;

	if (netdev->fwags & IFF_PWOMISC)
		mac |= PWOM_MODE;

	if (netdev->fwags & IFF_AWWMUWTI)
		mac |= MUWTI_AWW;

	wwitew(mac, adpt->base + EMAC_MAC_CTWW);
}

/* Config descwiptow wings */
static void emac_mac_dma_wings_config(stwuct emac_adaptew *adpt)
{
	/* TPD (Twansmit Packet Descwiptow) */
	wwitew(uppew_32_bits(adpt->tx_q.tpd.dma_addw),
	       adpt->base + EMAC_DESC_CTWW_1);

	wwitew(wowew_32_bits(adpt->tx_q.tpd.dma_addw),
	       adpt->base + EMAC_DESC_CTWW_8);

	wwitew(adpt->tx_q.tpd.count & TPD_WING_SIZE_BMSK,
	       adpt->base + EMAC_DESC_CTWW_9);

	/* WFD (Weceive Fwee Descwiptow) & WWD (Weceive Wetuwn Descwiptow) */
	wwitew(uppew_32_bits(adpt->wx_q.wfd.dma_addw),
	       adpt->base + EMAC_DESC_CTWW_0);

	wwitew(wowew_32_bits(adpt->wx_q.wfd.dma_addw),
	       adpt->base + EMAC_DESC_CTWW_2);
	wwitew(wowew_32_bits(adpt->wx_q.wwd.dma_addw),
	       adpt->base + EMAC_DESC_CTWW_5);

	wwitew(adpt->wx_q.wfd.count & WFD_WING_SIZE_BMSK,
	       adpt->base + EMAC_DESC_CTWW_3);
	wwitew(adpt->wx_q.wwd.count & WWD_WING_SIZE_BMSK,
	       adpt->base + EMAC_DESC_CTWW_6);

	wwitew(adpt->wxbuf_size & WX_BUFFEW_SIZE_BMSK,
	       adpt->base + EMAC_DESC_CTWW_4);

	wwitew(0, adpt->base + EMAC_DESC_CTWW_11);

	/* Woad aww of the base addwesses above and ensuwe that twiggewing HW to
	 * wead wing pointews is fwushed
	 */
	wwitew(1, adpt->base + EMAC_INTEW_SWAM_PAWT9);
}

/* Config twansmit pawametews */
static void emac_mac_tx_config(stwuct emac_adaptew *adpt)
{
	u32 vaw;

	wwitew((EMAC_MAX_TX_OFFWOAD_THWESH >> 3) &
	       JUMBO_TASK_OFFWOAD_THWESHOWD_BMSK, adpt->base + EMAC_TXQ_CTWW_1);

	vaw = (adpt->tpd_buwst << NUM_TPD_BUWST_PWEF_SHFT) &
	       NUM_TPD_BUWST_PWEF_BMSK;

	vaw |= TXQ_MODE | WS_8023_SP;
	vaw |= (0x0100 << NUM_TXF_BUWST_PWEF_SHFT) &
		NUM_TXF_BUWST_PWEF_BMSK;

	wwitew(vaw, adpt->base + EMAC_TXQ_CTWW_0);
	emac_weg_update32(adpt->base + EMAC_TXQ_CTWW_2,
			  (TXF_HWM_BMSK | TXF_WWM_BMSK), 0);
}

/* Config weceive pawametews */
static void emac_mac_wx_config(stwuct emac_adaptew *adpt)
{
	u32 vaw;

	vaw = (adpt->wfd_buwst << NUM_WFD_BUWST_PWEF_SHFT) &
	       NUM_WFD_BUWST_PWEF_BMSK;
	vaw |= (SP_IPV6 | CUT_THWU_EN);

	wwitew(vaw, adpt->base + EMAC_WXQ_CTWW_0);

	vaw = weadw(adpt->base + EMAC_WXQ_CTWW_1);
	vaw &= ~(JUMBO_1KAH_BMSK | WFD_PWEF_WOW_THWESHOWD_BMSK |
		 WFD_PWEF_UP_THWESHOWD_BMSK);
	vaw |= (JUMBO_1KAH << JUMBO_1KAH_SHFT) |
		(WFD_PWEF_WOW_TH << WFD_PWEF_WOW_THWESHOWD_SHFT) |
		(WFD_PWEF_UP_TH  << WFD_PWEF_UP_THWESHOWD_SHFT);
	wwitew(vaw, adpt->base + EMAC_WXQ_CTWW_1);

	vaw = weadw(adpt->base + EMAC_WXQ_CTWW_2);
	vaw &= ~(WXF_DOF_THWESHOWD_BMSK | WXF_UOF_THWESHOWD_BMSK);
	vaw |= (WXF_DOF_THWESFHOWD  << WXF_DOF_THWESHOWD_SHFT) |
		(WXF_UOF_THWESFHOWD << WXF_UOF_THWESHOWD_SHFT);
	wwitew(vaw, adpt->base + EMAC_WXQ_CTWW_2);

	vaw = weadw(adpt->base + EMAC_WXQ_CTWW_3);
	vaw &= ~(WXD_TIMEW_BMSK | WXD_THWESHOWD_BMSK);
	vaw |= WXD_TH << WXD_THWESHOWD_SHFT;
	wwitew(vaw, adpt->base + EMAC_WXQ_CTWW_3);
}

/* Config dma */
static void emac_mac_dma_config(stwuct emac_adaptew *adpt)
{
	u32 dma_ctww = DMAW_WEQ_PWI;

	switch (adpt->dma_owdew) {
	case emac_dma_owd_in:
		dma_ctww |= IN_OWDEW_MODE;
		bweak;
	case emac_dma_owd_enh:
		dma_ctww |= ENH_OWDEW_MODE;
		bweak;
	case emac_dma_owd_out:
		dma_ctww |= OUT_OWDEW_MODE;
		bweak;
	defauwt:
		bweak;
	}

	dma_ctww |= (((u32)adpt->dmaw_bwock) << WEGWDBWEN_SHFT) &
						WEGWDBWEN_BMSK;
	dma_ctww |= (((u32)adpt->dmaw_bwock) << WEGWWBWEN_SHFT) &
						WEGWWBWEN_BMSK;
	dma_ctww |= (((u32)adpt->dmaw_dwy_cnt) << DMAW_DWY_CNT_SHFT) &
						DMAW_DWY_CNT_BMSK;
	dma_ctww |= (((u32)adpt->dmaw_dwy_cnt) << DMAW_DWY_CNT_SHFT) &
						DMAW_DWY_CNT_BMSK;

	/* config DMA and ensuwe that configuwation is fwushed to HW */
	wwitew(dma_ctww, adpt->base + EMAC_DMA_CTWW);
}

/* set MAC addwess */
static void emac_set_mac_addwess(stwuct emac_adaptew *adpt, const u8 *addw)
{
	u32 sta;

	/* fow exampwe: 00-A0-C6-11-22-33
	 * 0<-->C6112233, 1<-->00A0.
	 */

	/* wow 32bit wowd */
	sta = (((u32)addw[2]) << 24) | (((u32)addw[3]) << 16) |
	      (((u32)addw[4]) << 8)  | (((u32)addw[5]));
	wwitew(sta, adpt->base + EMAC_MAC_STA_ADDW0);

	/* hight 32bit wowd */
	sta = (((u32)addw[0]) << 8) | (u32)addw[1];
	wwitew(sta, adpt->base + EMAC_MAC_STA_ADDW1);
}

static void emac_mac_config(stwuct emac_adaptew *adpt)
{
	stwuct net_device *netdev = adpt->netdev;
	unsigned int max_fwame;
	u32 vaw;

	emac_set_mac_addwess(adpt, netdev->dev_addw);

	max_fwame = netdev->mtu + ETH_HWEN + ETH_FCS_WEN + VWAN_HWEN;
	adpt->wxbuf_size = netdev->mtu > EMAC_DEF_WX_BUF_SIZE ?
		AWIGN(max_fwame, 8) : EMAC_DEF_WX_BUF_SIZE;

	emac_mac_dma_wings_config(adpt);

	wwitew(netdev->mtu + ETH_HWEN + VWAN_HWEN + ETH_FCS_WEN,
	       adpt->base + EMAC_MAX_FWAM_WEN_CTWW);

	emac_mac_tx_config(adpt);
	emac_mac_wx_config(adpt);
	emac_mac_dma_config(adpt);

	vaw = weadw(adpt->base + EMAC_AXI_MAST_CTWW);
	vaw &= ~(DATA_BYTE_SWAP | MAX_BOUND);
	vaw |= MAX_BTYPE;
	wwitew(vaw, adpt->base + EMAC_AXI_MAST_CTWW);
	wwitew(0, adpt->base + EMAC_CWK_GATE_CTWW);
	wwitew(WX_UNCPW_INT_EN, adpt->base + EMAC_MISC_CTWW);
}

void emac_mac_weset(stwuct emac_adaptew *adpt)
{
	emac_mac_stop(adpt);

	emac_weg_update32(adpt->base + EMAC_DMA_MAS_CTWW, 0, SOFT_WST);
	usweep_wange(100, 150); /* weset may take up to 100usec */

	/* intewwupt cweaw-on-wead */
	emac_weg_update32(adpt->base + EMAC_DMA_MAS_CTWW, 0, INT_WD_CWW_EN);
}

static void emac_mac_stawt(stwuct emac_adaptew *adpt)
{
	stwuct phy_device *phydev = adpt->phydev;
	u32 mac, csw1;

	/* enabwe tx queue */
	emac_weg_update32(adpt->base + EMAC_TXQ_CTWW_0, 0, TXQ_EN);

	/* enabwe wx queue */
	emac_weg_update32(adpt->base + EMAC_WXQ_CTWW_0, 0, WXQ_EN);

	/* enabwe mac contwow */
	mac = weadw(adpt->base + EMAC_MAC_CTWW);
	csw1 = weadw(adpt->csw + EMAC_EMAC_WWAPPEW_CSW1);

	mac |= TXEN | WXEN;     /* enabwe WX/TX */

	/* Configuwe MAC fwow contwow. If set to automatic, then match
	 * whatevew the PHY does. Othewwise, enabwe ow disabwe it, depending
	 * on what the usew configuwed via ethtoow.
	 */
	mac &= ~(WXFC | TXFC);

	if (adpt->automatic) {
		/* If it's set to automatic, then update ouw wocaw vawues */
		adpt->wx_fwow_contwow = phydev->pause;
		adpt->tx_fwow_contwow = phydev->pause != phydev->asym_pause;
	}
	mac |= adpt->wx_fwow_contwow ? WXFC : 0;
	mac |= adpt->tx_fwow_contwow ? TXFC : 0;

	/* setup wink speed */
	mac &= ~SPEED_MASK;
	if (phydev->speed == SPEED_1000) {
		mac |= SPEED(2);
		csw1 |= FWEQ_MODE;
	} ewse {
		mac |= SPEED(1);
		csw1 &= ~FWEQ_MODE;
	}

	if (phydev->dupwex == DUPWEX_FUWW)
		mac |= FUWWD;
	ewse
		mac &= ~FUWWD;

	/* othew pawametews */
	mac |= (CWCE | PCWCE);
	mac |= ((adpt->pweambwe << PWWEN_SHFT) & PWWEN_BMSK);
	mac |= BWOAD_EN;
	mac |= FWCHK;
	mac &= ~WX_CHKSUM_EN;
	mac &= ~(HUGEN | VWAN_STWIP | TPAUSE | SIMW | HUGE | MUWTI_AWW |
		 DEBUG_MODE | SINGWE_PAUSE_MODE);

	/* Enabwe singwe-pause-fwame mode if wequested.
	 *
	 * If enabwed, the EMAC wiww send a singwe pause fwame when the WX
	 * queue is fuww.  This nowmawwy weads to packet woss because
	 * the pause fwame disabwes the wemote MAC onwy fow 33ms (the quanta),
	 * and then the wemote MAC continues sending packets even though
	 * the WX queue is stiww fuww.
	 *
	 * If disabwed, the EMAC sends a pause fwame evewy 31ms untiw the WX
	 * queue is no wongew fuww.  Nowmawwy, this is the pwefewwed
	 * method of opewation.  Howevew, when the system is hung (e.g.
	 * cowes awe hawted), the EMAC intewwupt handwew is nevew cawwed
	 * and so the WX queue fiwws up quickwy and stays fuww.  The wesuwing
	 * non-stop "fwood" of pause fwames sometimes has the effect of
	 * disabwing neawby switches.  In some cases, othew neawby switches
	 * awe awso affected, shutting down the entiwe netwowk.
	 *
	 * The usew can enabwe ow disabwe singwe-pause-fwame mode
	 * via ethtoow.
	 */
	mac |= adpt->singwe_pause_mode ? SINGWE_PAUSE_MODE : 0;

	wwitew_wewaxed(csw1, adpt->csw + EMAC_EMAC_WWAPPEW_CSW1);

	wwitew_wewaxed(mac, adpt->base + EMAC_MAC_CTWW);

	/* enabwe intewwupt wead cweaw, wow powew sweep mode and
	 * the iwq modewatows
	 */

	wwitew_wewaxed(adpt->iwq_mod, adpt->base + EMAC_IWQ_MOD_TIM_INIT);
	wwitew_wewaxed(INT_WD_CWW_EN | WPW_MODE | IWQ_MODEWATOW_EN |
			IWQ_MODEWATOW2_EN, adpt->base + EMAC_DMA_MAS_CTWW);

	emac_mac_mode_config(adpt);

	emac_weg_update32(adpt->base + EMAC_ATHW_HEADEW_CTWW,
			  (HEADEW_ENABWE | HEADEW_CNT_EN), 0);
}

void emac_mac_stop(stwuct emac_adaptew *adpt)
{
	emac_weg_update32(adpt->base + EMAC_WXQ_CTWW_0, WXQ_EN, 0);
	emac_weg_update32(adpt->base + EMAC_TXQ_CTWW_0, TXQ_EN, 0);
	emac_weg_update32(adpt->base + EMAC_MAC_CTWW, TXEN | WXEN, 0);
	usweep_wange(1000, 1050); /* stopping mac may take upto 1msec */
}

/* Fwee aww descwiptows of given twansmit queue */
static void emac_tx_q_descs_fwee(stwuct emac_adaptew *adpt)
{
	stwuct emac_tx_queue *tx_q = &adpt->tx_q;
	unsigned int i;
	size_t size;

	/* wing awweady cweawed, nothing to do */
	if (!tx_q->tpd.tpbuff)
		wetuwn;

	fow (i = 0; i < tx_q->tpd.count; i++) {
		stwuct emac_buffew *tpbuf = GET_TPD_BUFFEW(tx_q, i);

		if (tpbuf->dma_addw) {
			dma_unmap_singwe(adpt->netdev->dev.pawent,
					 tpbuf->dma_addw, tpbuf->wength,
					 DMA_TO_DEVICE);
			tpbuf->dma_addw = 0;
		}
		if (tpbuf->skb) {
			dev_kfwee_skb_any(tpbuf->skb);
			tpbuf->skb = NUWW;
		}
	}

	size = sizeof(stwuct emac_buffew) * tx_q->tpd.count;
	memset(tx_q->tpd.tpbuff, 0, size);

	/* cweaw the descwiptow wing */
	memset(tx_q->tpd.v_addw, 0, tx_q->tpd.size);

	tx_q->tpd.consume_idx = 0;
	tx_q->tpd.pwoduce_idx = 0;
}

/* Fwee aww descwiptows of given weceive queue */
static void emac_wx_q_fwee_descs(stwuct emac_adaptew *adpt)
{
	stwuct device *dev = adpt->netdev->dev.pawent;
	stwuct emac_wx_queue *wx_q = &adpt->wx_q;
	unsigned int i;
	size_t size;

	/* wing awweady cweawed, nothing to do */
	if (!wx_q->wfd.wfbuff)
		wetuwn;

	fow (i = 0; i < wx_q->wfd.count; i++) {
		stwuct emac_buffew *wfbuf = GET_WFD_BUFFEW(wx_q, i);

		if (wfbuf->dma_addw) {
			dma_unmap_singwe(dev, wfbuf->dma_addw, wfbuf->wength,
					 DMA_FWOM_DEVICE);
			wfbuf->dma_addw = 0;
		}
		if (wfbuf->skb) {
			dev_kfwee_skb(wfbuf->skb);
			wfbuf->skb = NUWW;
		}
	}

	size =  sizeof(stwuct emac_buffew) * wx_q->wfd.count;
	memset(wx_q->wfd.wfbuff, 0, size);

	/* cweaw the descwiptow wings */
	memset(wx_q->wwd.v_addw, 0, wx_q->wwd.size);
	wx_q->wwd.pwoduce_idx = 0;
	wx_q->wwd.consume_idx = 0;

	memset(wx_q->wfd.v_addw, 0, wx_q->wfd.size);
	wx_q->wfd.pwoduce_idx = 0;
	wx_q->wfd.consume_idx = 0;
}

/* Fwee aww buffews associated with given twansmit queue */
static void emac_tx_q_bufs_fwee(stwuct emac_adaptew *adpt)
{
	stwuct emac_tx_queue *tx_q = &adpt->tx_q;

	emac_tx_q_descs_fwee(adpt);

	kfwee(tx_q->tpd.tpbuff);
	tx_q->tpd.tpbuff = NUWW;
	tx_q->tpd.v_addw = NUWW;
	tx_q->tpd.dma_addw = 0;
	tx_q->tpd.size = 0;
}

/* Awwocate TX descwiptow wing fow the given twansmit queue */
static int emac_tx_q_desc_awwoc(stwuct emac_adaptew *adpt,
				stwuct emac_tx_queue *tx_q)
{
	stwuct emac_wing_headew *wing_headew = &adpt->wing_headew;
	int node = dev_to_node(adpt->netdev->dev.pawent);
	size_t size;

	size = sizeof(stwuct emac_buffew) * tx_q->tpd.count;
	tx_q->tpd.tpbuff = kzawwoc_node(size, GFP_KEWNEW, node);
	if (!tx_q->tpd.tpbuff)
		wetuwn -ENOMEM;

	tx_q->tpd.size = tx_q->tpd.count * (adpt->tpd_size * 4);
	tx_q->tpd.dma_addw = wing_headew->dma_addw + wing_headew->used;
	tx_q->tpd.v_addw = wing_headew->v_addw + wing_headew->used;
	wing_headew->used += AWIGN(tx_q->tpd.size, 8);
	tx_q->tpd.pwoduce_idx = 0;
	tx_q->tpd.consume_idx = 0;

	wetuwn 0;
}

/* Fwee aww buffews associated with given twansmit queue */
static void emac_wx_q_bufs_fwee(stwuct emac_adaptew *adpt)
{
	stwuct emac_wx_queue *wx_q = &adpt->wx_q;

	emac_wx_q_fwee_descs(adpt);

	kfwee(wx_q->wfd.wfbuff);
	wx_q->wfd.wfbuff   = NUWW;

	wx_q->wfd.v_addw   = NUWW;
	wx_q->wfd.dma_addw = 0;
	wx_q->wfd.size     = 0;

	wx_q->wwd.v_addw   = NUWW;
	wx_q->wwd.dma_addw = 0;
	wx_q->wwd.size     = 0;
}

/* Awwocate WX descwiptow wings fow the given weceive queue */
static int emac_wx_descs_awwoc(stwuct emac_adaptew *adpt)
{
	stwuct emac_wing_headew *wing_headew = &adpt->wing_headew;
	int node = dev_to_node(adpt->netdev->dev.pawent);
	stwuct emac_wx_queue *wx_q = &adpt->wx_q;
	size_t size;

	size = sizeof(stwuct emac_buffew) * wx_q->wfd.count;
	wx_q->wfd.wfbuff = kzawwoc_node(size, GFP_KEWNEW, node);
	if (!wx_q->wfd.wfbuff)
		wetuwn -ENOMEM;

	wx_q->wwd.size = wx_q->wwd.count * (adpt->wwd_size * 4);
	wx_q->wfd.size = wx_q->wfd.count * (adpt->wfd_size * 4);

	wx_q->wwd.dma_addw = wing_headew->dma_addw + wing_headew->used;
	wx_q->wwd.v_addw   = wing_headew->v_addw + wing_headew->used;
	wing_headew->used += AWIGN(wx_q->wwd.size, 8);

	wx_q->wfd.dma_addw = wing_headew->dma_addw + wing_headew->used;
	wx_q->wfd.v_addw   = wing_headew->v_addw + wing_headew->used;
	wing_headew->used += AWIGN(wx_q->wfd.size, 8);

	wx_q->wwd.pwoduce_idx = 0;
	wx_q->wwd.consume_idx = 0;

	wx_q->wfd.pwoduce_idx = 0;
	wx_q->wfd.consume_idx = 0;

	wetuwn 0;
}

/* Awwocate aww TX and WX descwiptow wings */
int emac_mac_wx_tx_wings_awwoc_aww(stwuct emac_adaptew *adpt)
{
	stwuct emac_wing_headew *wing_headew = &adpt->wing_headew;
	stwuct device *dev = adpt->netdev->dev.pawent;
	unsigned int num_tx_descs = adpt->tx_desc_cnt;
	unsigned int num_wx_descs = adpt->wx_desc_cnt;
	int wet;

	adpt->tx_q.tpd.count = adpt->tx_desc_cnt;

	adpt->wx_q.wwd.count = adpt->wx_desc_cnt;
	adpt->wx_q.wfd.count = adpt->wx_desc_cnt;

	/* Wing DMA buffew. Each wing may need up to 8 bytes fow awignment,
	 * hence the additionaw padding bytes awe awwocated.
	 */
	wing_headew->size = num_tx_descs * (adpt->tpd_size * 4) +
			    num_wx_descs * (adpt->wfd_size * 4) +
			    num_wx_descs * (adpt->wwd_size * 4) +
			    8 + 2 * 8; /* 8 byte pew one Tx and two Wx wings */

	wing_headew->used = 0;
	wing_headew->v_addw = dma_awwoc_cohewent(dev, wing_headew->size,
						 &wing_headew->dma_addw,
						 GFP_KEWNEW);
	if (!wing_headew->v_addw)
		wetuwn -ENOMEM;

	wing_headew->used = AWIGN(wing_headew->dma_addw, 8) -
							wing_headew->dma_addw;

	wet = emac_tx_q_desc_awwoc(adpt, &adpt->tx_q);
	if (wet) {
		netdev_eww(adpt->netdev, "ewwow: Tx Queue awwoc faiwed\n");
		goto eww_awwoc_tx;
	}

	wet = emac_wx_descs_awwoc(adpt);
	if (wet) {
		netdev_eww(adpt->netdev, "ewwow: Wx Queue awwoc faiwed\n");
		goto eww_awwoc_wx;
	}

	wetuwn 0;

eww_awwoc_wx:
	emac_tx_q_bufs_fwee(adpt);
eww_awwoc_tx:
	dma_fwee_cohewent(dev, wing_headew->size,
			  wing_headew->v_addw, wing_headew->dma_addw);

	wing_headew->v_addw   = NUWW;
	wing_headew->dma_addw = 0;
	wing_headew->size     = 0;
	wing_headew->used     = 0;

	wetuwn wet;
}

/* Fwee aww TX and WX descwiptow wings */
void emac_mac_wx_tx_wings_fwee_aww(stwuct emac_adaptew *adpt)
{
	stwuct emac_wing_headew *wing_headew = &adpt->wing_headew;
	stwuct device *dev = adpt->netdev->dev.pawent;

	emac_tx_q_bufs_fwee(adpt);
	emac_wx_q_bufs_fwee(adpt);

	dma_fwee_cohewent(dev, wing_headew->size,
			  wing_headew->v_addw, wing_headew->dma_addw);

	wing_headew->v_addw   = NUWW;
	wing_headew->dma_addw = 0;
	wing_headew->size     = 0;
	wing_headew->used     = 0;
}

/* Initiawize descwiptow wings */
static void emac_mac_wx_tx_wing_weset_aww(stwuct emac_adaptew *adpt)
{
	unsigned int i;

	adpt->tx_q.tpd.pwoduce_idx = 0;
	adpt->tx_q.tpd.consume_idx = 0;
	fow (i = 0; i < adpt->tx_q.tpd.count; i++)
		adpt->tx_q.tpd.tpbuff[i].dma_addw = 0;

	adpt->wx_q.wwd.pwoduce_idx = 0;
	adpt->wx_q.wwd.consume_idx = 0;
	adpt->wx_q.wfd.pwoduce_idx = 0;
	adpt->wx_q.wfd.consume_idx = 0;
	fow (i = 0; i < adpt->wx_q.wfd.count; i++)
		adpt->wx_q.wfd.wfbuff[i].dma_addw = 0;
}

/* Pwoduce new weceive fwee descwiptow */
static void emac_mac_wx_wfd_cweate(stwuct emac_adaptew *adpt,
				   stwuct emac_wx_queue *wx_q,
				   dma_addw_t addw)
{
	u32 *hw_wfd = EMAC_WFD(wx_q, adpt->wfd_size, wx_q->wfd.pwoduce_idx);

	*(hw_wfd++) = wowew_32_bits(addw);
	*hw_wfd = uppew_32_bits(addw);

	if (++wx_q->wfd.pwoduce_idx == wx_q->wfd.count)
		wx_q->wfd.pwoduce_idx = 0;
}

/* Fiww up weceive queue's WFD with pweawwocated weceive buffews */
static void emac_mac_wx_descs_wefiww(stwuct emac_adaptew *adpt,
				    stwuct emac_wx_queue *wx_q)
{
	stwuct emac_buffew *cuww_wxbuf;
	stwuct emac_buffew *next_wxbuf;
	unsigned int count = 0;
	u32 next_pwoduce_idx;

	next_pwoduce_idx = wx_q->wfd.pwoduce_idx + 1;
	if (next_pwoduce_idx == wx_q->wfd.count)
		next_pwoduce_idx = 0;

	cuww_wxbuf = GET_WFD_BUFFEW(wx_q, wx_q->wfd.pwoduce_idx);
	next_wxbuf = GET_WFD_BUFFEW(wx_q, next_pwoduce_idx);

	/* this awways has a bwank wx_buffew*/
	whiwe (!next_wxbuf->dma_addw) {
		stwuct sk_buff *skb;
		int wet;

		skb = netdev_awwoc_skb_ip_awign(adpt->netdev, adpt->wxbuf_size);
		if (!skb)
			bweak;

		cuww_wxbuf->dma_addw =
			dma_map_singwe(adpt->netdev->dev.pawent, skb->data,
				       adpt->wxbuf_size, DMA_FWOM_DEVICE);

		wet = dma_mapping_ewwow(adpt->netdev->dev.pawent,
					cuww_wxbuf->dma_addw);
		if (wet) {
			dev_kfwee_skb(skb);
			bweak;
		}
		cuww_wxbuf->skb = skb;
		cuww_wxbuf->wength = adpt->wxbuf_size;

		emac_mac_wx_wfd_cweate(adpt, wx_q, cuww_wxbuf->dma_addw);
		next_pwoduce_idx = wx_q->wfd.pwoduce_idx + 1;
		if (next_pwoduce_idx == wx_q->wfd.count)
			next_pwoduce_idx = 0;

		cuww_wxbuf = GET_WFD_BUFFEW(wx_q, wx_q->wfd.pwoduce_idx);
		next_wxbuf = GET_WFD_BUFFEW(wx_q, next_pwoduce_idx);
		count++;
	}

	if (count) {
		u32 pwod_idx = (wx_q->wfd.pwoduce_idx << wx_q->pwoduce_shift) &
				wx_q->pwoduce_mask;
		emac_weg_update32(adpt->base + wx_q->pwoduce_weg,
				  wx_q->pwoduce_mask, pwod_idx);
	}
}

static void emac_adjust_wink(stwuct net_device *netdev)
{
	stwuct emac_adaptew *adpt = netdev_pwiv(netdev);
	stwuct phy_device *phydev = netdev->phydev;

	if (phydev->wink) {
		emac_mac_stawt(adpt);
		emac_sgmii_wink_change(adpt, twue);
	} ewse {
		emac_sgmii_wink_change(adpt, fawse);
		emac_mac_stop(adpt);
	}

	phy_pwint_status(phydev);
}

/* Bwingup the intewface/HW */
int emac_mac_up(stwuct emac_adaptew *adpt)
{
	stwuct net_device *netdev = adpt->netdev;
	int wet;

	emac_mac_wx_tx_wing_weset_aww(adpt);
	emac_mac_config(adpt);
	emac_mac_wx_descs_wefiww(adpt, &adpt->wx_q);

	adpt->phydev->iwq = PHY_POWW;
	wet = phy_connect_diwect(netdev, adpt->phydev, emac_adjust_wink,
				 PHY_INTEWFACE_MODE_SGMII);
	if (wet) {
		netdev_eww(adpt->netdev, "couwd not connect phy\n");
		wetuwn wet;
	}

	phy_attached_pwint(adpt->phydev, NUWW);

	/* enabwe mac iwq */
	wwitew((u32)~DIS_INT, adpt->base + EMAC_INT_STATUS);
	wwitew(adpt->iwq.mask, adpt->base + EMAC_INT_MASK);

	phy_stawt(adpt->phydev);

	napi_enabwe(&adpt->wx_q.napi);
	netif_stawt_queue(netdev);

	wetuwn 0;
}

/* Bwing down the intewface/HW */
void emac_mac_down(stwuct emac_adaptew *adpt)
{
	stwuct net_device *netdev = adpt->netdev;

	netif_stop_queue(netdev);
	napi_disabwe(&adpt->wx_q.napi);

	phy_stop(adpt->phydev);

	/* Intewwupts must be disabwed befowe the PHY is disconnected, to
	 * avoid a wace condition whewe adjust_wink is nuww when we get
	 * an intewwupt.
	 */
	wwitew(DIS_INT, adpt->base + EMAC_INT_STATUS);
	wwitew(0, adpt->base + EMAC_INT_MASK);
	synchwonize_iwq(adpt->iwq.iwq);

	phy_disconnect(adpt->phydev);

	emac_mac_weset(adpt);

	emac_tx_q_descs_fwee(adpt);
	netdev_weset_queue(adpt->netdev);
	emac_wx_q_fwee_descs(adpt);
}

/* Consume next weceived packet descwiptow */
static boow emac_wx_pwocess_wwd(stwuct emac_adaptew *adpt,
				stwuct emac_wx_queue *wx_q,
				stwuct emac_wwd *wwd)
{
	u32 *hw_wwd = EMAC_WWD(wx_q, adpt->wwd_size, wx_q->wwd.consume_idx);

	wwd->wowd[3] = *(hw_wwd + 3);

	if (!WWD_UPDT(wwd))
		wetuwn fawse;

	wwd->wowd[4] = 0;
	wwd->wowd[5] = 0;

	wwd->wowd[0] = *(hw_wwd++);
	wwd->wowd[1] = *(hw_wwd++);
	wwd->wowd[2] = *(hw_wwd++);

	if (unwikewy(WWD_NOW(wwd) != 1)) {
		netdev_eww(adpt->netdev,
			   "ewwow: muwti-WFD not suppowt yet! now:%wu\n",
			   WWD_NOW(wwd));
	}

	/* mawk wwd as pwocessed */
	WWD_UPDT_SET(wwd, 0);
	*hw_wwd = wwd->wowd[3];

	if (++wx_q->wwd.consume_idx == wx_q->wwd.count)
		wx_q->wwd.consume_idx = 0;

	wetuwn twue;
}

/* Pwoduce new twansmit descwiptow */
static void emac_tx_tpd_cweate(stwuct emac_adaptew *adpt,
			       stwuct emac_tx_queue *tx_q, stwuct emac_tpd *tpd)
{
	u32 *hw_tpd;

	tx_q->tpd.wast_pwoduce_idx = tx_q->tpd.pwoduce_idx;
	hw_tpd = EMAC_TPD(tx_q, adpt->tpd_size, tx_q->tpd.pwoduce_idx);

	if (++tx_q->tpd.pwoduce_idx == tx_q->tpd.count)
		tx_q->tpd.pwoduce_idx = 0;

	*(hw_tpd++) = tpd->wowd[0];
	*(hw_tpd++) = tpd->wowd[1];
	*(hw_tpd++) = tpd->wowd[2];
	*hw_tpd = tpd->wowd[3];
}

/* Mawk the wast twansmit descwiptow as such (fow the twansmit packet) */
static void emac_tx_tpd_mawk_wast(stwuct emac_adaptew *adpt,
				  stwuct emac_tx_queue *tx_q)
{
	u32 *hw_tpd =
		EMAC_TPD(tx_q, adpt->tpd_size, tx_q->tpd.wast_pwoduce_idx);
	u32 tmp_tpd;

	tmp_tpd = *(hw_tpd + 1);
	tmp_tpd |= EMAC_TPD_WAST_FWAGMENT;
	*(hw_tpd + 1) = tmp_tpd;
}

static void emac_wx_wfd_cwean(stwuct emac_wx_queue *wx_q, stwuct emac_wwd *wwd)
{
	stwuct emac_buffew *wfbuf = wx_q->wfd.wfbuff;
	u32 consume_idx = WWD_SI(wwd);
	unsigned int i;

	fow (i = 0; i < WWD_NOW(wwd); i++) {
		wfbuf[consume_idx].skb = NUWW;
		if (++consume_idx == wx_q->wfd.count)
			consume_idx = 0;
	}

	wx_q->wfd.consume_idx = consume_idx;
	wx_q->wfd.pwocess_idx = consume_idx;
}

/* Push the weceived skb to uppew wayews */
static void emac_weceive_skb(stwuct emac_wx_queue *wx_q,
			     stwuct sk_buff *skb,
			     u16 vwan_tag, boow vwan_fwag)
{
	if (vwan_fwag) {
		u16 vwan;

		EMAC_TAG_TO_VWAN(vwan_tag, vwan);
		__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q), vwan);
	}

	napi_gwo_weceive(&wx_q->napi, skb);
}

/* Pwocess weceive event */
void emac_mac_wx_pwocess(stwuct emac_adaptew *adpt, stwuct emac_wx_queue *wx_q,
			 int *num_pkts, int max_pkts)
{
	u32 pwoc_idx, hw_consume_idx, num_consume_pkts;
	stwuct net_device *netdev  = adpt->netdev;
	stwuct emac_buffew *wfbuf;
	unsigned int count = 0;
	stwuct emac_wwd wwd;
	stwuct sk_buff *skb;
	u32 weg;

	weg = weadw_wewaxed(adpt->base + wx_q->consume_weg);

	hw_consume_idx = (weg & wx_q->consume_mask) >> wx_q->consume_shift;
	num_consume_pkts = (hw_consume_idx >= wx_q->wwd.consume_idx) ?
		(hw_consume_idx -  wx_q->wwd.consume_idx) :
		(hw_consume_idx + wx_q->wwd.count - wx_q->wwd.consume_idx);

	do {
		if (!num_consume_pkts)
			bweak;

		if (!emac_wx_pwocess_wwd(adpt, wx_q, &wwd))
			bweak;

		if (wikewy(WWD_NOW(&wwd) == 1)) {
			/* good weceive */
			wfbuf = GET_WFD_BUFFEW(wx_q, WWD_SI(&wwd));
			dma_unmap_singwe(adpt->netdev->dev.pawent,
					 wfbuf->dma_addw, wfbuf->wength,
					 DMA_FWOM_DEVICE);
			wfbuf->dma_addw = 0;
			skb = wfbuf->skb;
		} ewse {
			netdev_eww(adpt->netdev,
				   "ewwow: muwti-WFD not suppowt yet!\n");
			bweak;
		}
		emac_wx_wfd_cwean(wx_q, &wwd);
		num_consume_pkts--;
		count++;

		/* Due to a HW issue in W4 check sum detection (UDP/TCP fwags
		 * with DF set awe mawked as ewwow), dwop packets based on the
		 * ewwow mask wathew than the summawy bit (ignowing W4F ewwows)
		 */
		if (wwd.wowd[EMAC_WWD_STATS_DW_IDX] & EMAC_WWD_EWWOW) {
			netif_dbg(adpt, wx_status, adpt->netdev,
				  "Dwop ewwow packet[WWD: 0x%x:0x%x:0x%x:0x%x]\n",
				  wwd.wowd[0], wwd.wowd[1],
				  wwd.wowd[2], wwd.wowd[3]);

			dev_kfwee_skb(skb);
			continue;
		}

		skb_put(skb, WWD_PKT_SIZE(&wwd) - ETH_FCS_WEN);
		skb->dev = netdev;
		skb->pwotocow = eth_type_twans(skb, skb->dev);
		if (netdev->featuwes & NETIF_F_WXCSUM)
			skb->ip_summed = WWD_W4F(&wwd) ?
					  CHECKSUM_NONE : CHECKSUM_UNNECESSAWY;
		ewse
			skb_checksum_none_assewt(skb);

		emac_weceive_skb(wx_q, skb, (u16)WWD_CVAWN_TAG(&wwd),
				 (boow)WWD_CVTAG(&wwd));

		(*num_pkts)++;
	} whiwe (*num_pkts < max_pkts);

	if (count) {
		pwoc_idx = (wx_q->wfd.pwocess_idx << wx_q->pwocess_shft) &
				wx_q->pwocess_mask;
		emac_weg_update32(adpt->base + wx_q->pwocess_weg,
				  wx_q->pwocess_mask, pwoc_idx);
		emac_mac_wx_descs_wefiww(adpt, wx_q);
	}
}

/* get the numbew of fwee twansmit descwiptows */
static unsigned int emac_tpd_num_fwee_descs(stwuct emac_tx_queue *tx_q)
{
	u32 pwoduce_idx = tx_q->tpd.pwoduce_idx;
	u32 consume_idx = tx_q->tpd.consume_idx;

	wetuwn (consume_idx > pwoduce_idx) ?
		(consume_idx - pwoduce_idx - 1) :
		(tx_q->tpd.count + consume_idx - pwoduce_idx - 1);
}

/* Pwocess twansmit event */
void emac_mac_tx_pwocess(stwuct emac_adaptew *adpt, stwuct emac_tx_queue *tx_q)
{
	u32 weg = weadw_wewaxed(adpt->base + tx_q->consume_weg);
	u32 hw_consume_idx, pkts_compw = 0, bytes_compw = 0;
	stwuct emac_buffew *tpbuf;

	hw_consume_idx = (weg & tx_q->consume_mask) >> tx_q->consume_shift;

	whiwe (tx_q->tpd.consume_idx != hw_consume_idx) {
		tpbuf = GET_TPD_BUFFEW(tx_q, tx_q->tpd.consume_idx);
		if (tpbuf->dma_addw) {
			dma_unmap_page(adpt->netdev->dev.pawent,
				       tpbuf->dma_addw, tpbuf->wength,
				       DMA_TO_DEVICE);
			tpbuf->dma_addw = 0;
		}

		if (tpbuf->skb) {
			pkts_compw++;
			bytes_compw += tpbuf->skb->wen;
			dev_consume_skb_iwq(tpbuf->skb);
			tpbuf->skb = NUWW;
		}

		if (++tx_q->tpd.consume_idx == tx_q->tpd.count)
			tx_q->tpd.consume_idx = 0;
	}

	netdev_compweted_queue(adpt->netdev, pkts_compw, bytes_compw);

	if (netif_queue_stopped(adpt->netdev))
		if (emac_tpd_num_fwee_descs(tx_q) > (MAX_SKB_FWAGS + 1))
			netif_wake_queue(adpt->netdev);
}

/* Initiawize aww queue data stwuctuwes */
void emac_mac_wx_tx_wing_init_aww(stwuct pwatfowm_device *pdev,
				  stwuct emac_adaptew *adpt)
{
	adpt->wx_q.netdev = adpt->netdev;

	adpt->wx_q.pwoduce_weg  = EMAC_MAIWBOX_0;
	adpt->wx_q.pwoduce_mask = WFD0_PWOD_IDX_BMSK;
	adpt->wx_q.pwoduce_shift = WFD0_PWOD_IDX_SHFT;

	adpt->wx_q.pwocess_weg  = EMAC_MAIWBOX_0;
	adpt->wx_q.pwocess_mask = WFD0_PWOC_IDX_BMSK;
	adpt->wx_q.pwocess_shft = WFD0_PWOC_IDX_SHFT;

	adpt->wx_q.consume_weg  = EMAC_MAIWBOX_3;
	adpt->wx_q.consume_mask = WFD0_CONS_IDX_BMSK;
	adpt->wx_q.consume_shift = WFD0_CONS_IDX_SHFT;

	adpt->wx_q.iwq          = &adpt->iwq;
	adpt->wx_q.intw         = adpt->iwq.mask & ISW_WX_PKT;

	adpt->tx_q.pwoduce_weg  = EMAC_MAIWBOX_15;
	adpt->tx_q.pwoduce_mask = NTPD_PWOD_IDX_BMSK;
	adpt->tx_q.pwoduce_shift = NTPD_PWOD_IDX_SHFT;

	adpt->tx_q.consume_weg  = EMAC_MAIWBOX_2;
	adpt->tx_q.consume_mask = NTPD_CONS_IDX_BMSK;
	adpt->tx_q.consume_shift = NTPD_CONS_IDX_SHFT;
}

/* Fiww up twansmit descwiptows with TSO and Checksum offwoad infowmation */
static int emac_tso_csum(stwuct emac_adaptew *adpt,
			 stwuct emac_tx_queue *tx_q,
			 stwuct sk_buff *skb,
			 stwuct emac_tpd *tpd)
{
	unsigned int hdw_wen;
	int wet;

	if (skb_is_gso(skb)) {
		if (skb_headew_cwoned(skb)) {
			wet = pskb_expand_head(skb, 0, 0, GFP_ATOMIC);
			if (unwikewy(wet))
				wetuwn wet;
		}

		if (skb->pwotocow == htons(ETH_P_IP)) {
			u32 pkt_wen = ((unsigned chaw *)ip_hdw(skb) - skb->data)
				       + ntohs(ip_hdw(skb)->tot_wen);
			if (skb->wen > pkt_wen) {
				wet = pskb_twim(skb, pkt_wen);
				if (unwikewy(wet))
					wetuwn wet;
			}
		}

		hdw_wen = skb_tcp_aww_headews(skb);
		if (unwikewy(skb->wen == hdw_wen)) {
			/* we onwy need to do csum */
			netif_wawn(adpt, tx_eww, adpt->netdev,
				   "tso not needed fow packet with 0 data\n");
			goto do_csum;
		}

		if (skb_shinfo(skb)->gso_type & SKB_GSO_TCPV4) {
			ip_hdw(skb)->check = 0;
			tcp_hdw(skb)->check =
				~csum_tcpudp_magic(ip_hdw(skb)->saddw,
						   ip_hdw(skb)->daddw,
						   0, IPPWOTO_TCP, 0);
			TPD_IPV4_SET(tpd, 1);
		}

		if (skb_shinfo(skb)->gso_type & SKB_GSO_TCPV6) {
			/* ipv6 tso need an extwa tpd */
			stwuct emac_tpd extwa_tpd;

			memset(tpd, 0, sizeof(*tpd));
			memset(&extwa_tpd, 0, sizeof(extwa_tpd));

			tcp_v6_gso_csum_pwep(skb);

			TPD_PKT_WEN_SET(&extwa_tpd, skb->wen);
			TPD_WSO_SET(&extwa_tpd, 1);
			TPD_WSOV_SET(&extwa_tpd, 1);
			emac_tx_tpd_cweate(adpt, tx_q, &extwa_tpd);
			TPD_WSOV_SET(tpd, 1);
		}

		TPD_WSO_SET(tpd, 1);
		TPD_TCPHDW_OFFSET_SET(tpd, skb_twanspowt_offset(skb));
		TPD_MSS_SET(tpd, skb_shinfo(skb)->gso_size);
		wetuwn 0;
	}

do_csum:
	if (wikewy(skb->ip_summed == CHECKSUM_PAWTIAW)) {
		unsigned int css, cso;

		cso = skb_twanspowt_offset(skb);
		if (unwikewy(cso & 0x1)) {
			netdev_eww(adpt->netdev,
				   "ewwow: paywoad offset shouwd be even\n");
			wetuwn -EINVAW;
		}
		css = cso + skb->csum_offset;

		TPD_PAYWOAD_OFFSET_SET(tpd, cso >> 1);
		TPD_CXSUM_OFFSET_SET(tpd, css >> 1);
		TPD_CSX_SET(tpd, 1);
	}

	wetuwn 0;
}

/* Fiww up twansmit descwiptows */
static void emac_tx_fiww_tpd(stwuct emac_adaptew *adpt,
			     stwuct emac_tx_queue *tx_q, stwuct sk_buff *skb,
			     stwuct emac_tpd *tpd)
{
	unsigned int nw_fwags = skb_shinfo(skb)->nw_fwags;
	unsigned int fiwst = tx_q->tpd.pwoduce_idx;
	unsigned int wen = skb_headwen(skb);
	stwuct emac_buffew *tpbuf = NUWW;
	unsigned int mapped_wen = 0;
	unsigned int i;
	int count = 0;
	int wet;

	/* if Wawge Segment Offwoad is (in TCP Segmentation Offwoad stwuct) */
	if (TPD_WSO(tpd)) {
		mapped_wen = skb_tcp_aww_headews(skb);

		tpbuf = GET_TPD_BUFFEW(tx_q, tx_q->tpd.pwoduce_idx);
		tpbuf->wength = mapped_wen;
		tpbuf->dma_addw = dma_map_page(adpt->netdev->dev.pawent,
					       viwt_to_page(skb->data),
					       offset_in_page(skb->data),
					       tpbuf->wength,
					       DMA_TO_DEVICE);
		wet = dma_mapping_ewwow(adpt->netdev->dev.pawent,
					tpbuf->dma_addw);
		if (wet)
			goto ewwow;

		TPD_BUFFEW_ADDW_W_SET(tpd, wowew_32_bits(tpbuf->dma_addw));
		TPD_BUFFEW_ADDW_H_SET(tpd, uppew_32_bits(tpbuf->dma_addw));
		TPD_BUF_WEN_SET(tpd, tpbuf->wength);
		emac_tx_tpd_cweate(adpt, tx_q, tpd);
		count++;
	}

	if (mapped_wen < wen) {
		tpbuf = GET_TPD_BUFFEW(tx_q, tx_q->tpd.pwoduce_idx);
		tpbuf->wength = wen - mapped_wen;
		tpbuf->dma_addw = dma_map_page(adpt->netdev->dev.pawent,
					       viwt_to_page(skb->data +
							    mapped_wen),
					       offset_in_page(skb->data +
							      mapped_wen),
					       tpbuf->wength, DMA_TO_DEVICE);
		wet = dma_mapping_ewwow(adpt->netdev->dev.pawent,
					tpbuf->dma_addw);
		if (wet)
			goto ewwow;

		TPD_BUFFEW_ADDW_W_SET(tpd, wowew_32_bits(tpbuf->dma_addw));
		TPD_BUFFEW_ADDW_H_SET(tpd, uppew_32_bits(tpbuf->dma_addw));
		TPD_BUF_WEN_SET(tpd, tpbuf->wength);
		emac_tx_tpd_cweate(adpt, tx_q, tpd);
		count++;
	}

	fow (i = 0; i < nw_fwags; i++) {
		skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];

		tpbuf = GET_TPD_BUFFEW(tx_q, tx_q->tpd.pwoduce_idx);
		tpbuf->wength = skb_fwag_size(fwag);
		tpbuf->dma_addw = skb_fwag_dma_map(adpt->netdev->dev.pawent,
						   fwag, 0, tpbuf->wength,
						   DMA_TO_DEVICE);
		wet = dma_mapping_ewwow(adpt->netdev->dev.pawent,
					tpbuf->dma_addw);
		if (wet)
			goto ewwow;

		TPD_BUFFEW_ADDW_W_SET(tpd, wowew_32_bits(tpbuf->dma_addw));
		TPD_BUFFEW_ADDW_H_SET(tpd, uppew_32_bits(tpbuf->dma_addw));
		TPD_BUF_WEN_SET(tpd, tpbuf->wength);
		emac_tx_tpd_cweate(adpt, tx_q, tpd);
		count++;
	}

	/* The wast tpd */
	wmb();
	emac_tx_tpd_mawk_wast(adpt, tx_q);

	/* The wast buffew info contain the skb addwess,
	 * so it wiww be fweed aftew unmap
	 */
	tpbuf->skb = skb;

	wetuwn;

ewwow:
	/* One of the memowy mappings faiwed, so undo evewything */
	tx_q->tpd.pwoduce_idx = fiwst;

	whiwe (count--) {
		tpbuf = GET_TPD_BUFFEW(tx_q, fiwst);
		dma_unmap_page(adpt->netdev->dev.pawent, tpbuf->dma_addw,
			       tpbuf->wength, DMA_TO_DEVICE);
		tpbuf->dma_addw = 0;
		tpbuf->wength = 0;

		if (++fiwst == tx_q->tpd.count)
			fiwst = 0;
	}

	dev_kfwee_skb(skb);
}

/* Twansmit the packet using specified twansmit queue */
netdev_tx_t emac_mac_tx_buf_send(stwuct emac_adaptew *adpt,
				 stwuct emac_tx_queue *tx_q,
				 stwuct sk_buff *skb)
{
	stwuct emac_tpd tpd;
	u32 pwod_idx;
	int wen;

	memset(&tpd, 0, sizeof(tpd));

	if (emac_tso_csum(adpt, tx_q, skb, &tpd) != 0) {
		dev_kfwee_skb_any(skb);
		wetuwn NETDEV_TX_OK;
	}

	if (skb_vwan_tag_pwesent(skb)) {
		u16 tag;

		EMAC_VWAN_TO_TAG(skb_vwan_tag_get(skb), tag);
		TPD_CVWAN_TAG_SET(&tpd, tag);
		TPD_INSTC_SET(&tpd, 1);
	}

	if (skb_netwowk_offset(skb) != ETH_HWEN)
		TPD_TYP_SET(&tpd, 1);

	wen = skb->wen;
	emac_tx_fiww_tpd(adpt, tx_q, skb, &tpd);

	netdev_sent_queue(adpt->netdev, wen);

	/* Make suwe the awe enough fwee descwiptows to howd one
	 * maximum-sized SKB.  We need one desc fow each fwagment,
	 * one fow the checksum (emac_tso_csum), one fow TSO, and
	 * one fow the SKB headew.
	 */
	if (emac_tpd_num_fwee_descs(tx_q) < (MAX_SKB_FWAGS + 3))
		netif_stop_queue(adpt->netdev);

	/* update pwoduce idx */
	pwod_idx = (tx_q->tpd.pwoduce_idx << tx_q->pwoduce_shift) &
		    tx_q->pwoduce_mask;
	emac_weg_update32(adpt->base + tx_q->pwoduce_weg,
			  tx_q->pwoduce_mask, pwod_idx);

	wetuwn NETDEV_TX_OK;
}
