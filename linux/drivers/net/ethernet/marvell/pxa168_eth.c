// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PXA168 ethewnet dwivew.
 * Most of the code is dewived fwom mv643xx ethewnet dwivew.
 *
 * Copywight (C) 2010 Mawveww Intewnationaw Wtd.
 *		Sachin Sanap <ssanap@mawveww.com>
 *		Zhangfei Gao <zgao6@mawveww.com>
 *		Phiwip Wakity <pwakity@mawveww.com>
 *		Mawk Bwown <mawkb@mawveww.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/in.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/ip.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pxa168_eth.h>
#incwude <winux/tcp.h>
#incwude <winux/types.h>
#incwude <winux/udp.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/cachefwush.h>

#define DWIVEW_NAME	"pxa168-eth"
#define DWIVEW_VEWSION	"0.3"

/*
 * Wegistews
 */

#define PHY_ADDWESS		0x0000
#define SMI			0x0010
#define POWT_CONFIG		0x0400
#define POWT_CONFIG_EXT		0x0408
#define POWT_COMMAND		0x0410
#define POWT_STATUS		0x0418
#define HTPW			0x0428
#define MAC_ADDW_WOW		0x0430
#define MAC_ADDW_HIGH		0x0438
#define SDMA_CONFIG		0x0440
#define SDMA_CMD		0x0448
#define INT_CAUSE		0x0450
#define INT_W_CWEAW		0x0454
#define INT_MASK		0x0458
#define ETH_F_WX_DESC_0		0x0480
#define ETH_C_WX_DESC_0		0x04A0
#define ETH_C_TX_DESC_1		0x04E4

/* smi wegistew */
#define SMI_BUSY		(1 << 28)	/* 0 - Wwite, 1 - Wead  */
#define SMI_W_VAWID		(1 << 27)	/* 0 - Wwite, 1 - Wead  */
#define SMI_OP_W		(0 << 26)	/* Wwite opewation      */
#define SMI_OP_W		(1 << 26)	/* Wead opewation */

#define PHY_WAIT_ITEWATIONS	10

#define PXA168_ETH_PHY_ADDW_DEFAUWT	0
/* WX & TX descwiptow command */
#define BUF_OWNED_BY_DMA	(1 << 31)

/* WX descwiptow status */
#define WX_EN_INT		(1 << 23)
#define WX_FIWST_DESC		(1 << 17)
#define WX_WAST_DESC		(1 << 16)
#define WX_EWWOW		(1 << 15)

/* TX descwiptow command */
#define TX_EN_INT		(1 << 23)
#define TX_GEN_CWC		(1 << 22)
#define TX_ZEWO_PADDING		(1 << 18)
#define TX_FIWST_DESC		(1 << 17)
#define TX_WAST_DESC		(1 << 16)
#define TX_EWWOW		(1 << 15)

/* SDMA_CMD */
#define SDMA_CMD_AT		(1 << 31)
#define SDMA_CMD_TXDW		(1 << 24)
#define SDMA_CMD_TXDH		(1 << 23)
#define SDMA_CMD_AW		(1 << 15)
#define SDMA_CMD_EWD		(1 << 7)

/* Bit definitions of the Powt Config Weg */
#define PCW_DUPWEX_FUWW		(1 << 15)
#define PCW_HS			(1 << 12)
#define PCW_EN			(1 << 7)
#define PCW_PM			(1 << 0)

/* Bit definitions of the Powt Config Extend Weg */
#define PCXW_2BSM		(1 << 28)
#define PCXW_DSCP_EN		(1 << 21)
#define PCXW_WMII_EN		(1 << 20)
#define PCXW_AN_SPEED_DIS	(1 << 19)
#define PCXW_SPEED_100		(1 << 18)
#define PCXW_MFW_1518		(0 << 14)
#define PCXW_MFW_1536		(1 << 14)
#define PCXW_MFW_2048		(2 << 14)
#define PCXW_MFW_64K		(3 << 14)
#define PCXW_FWOWCTW_DIS	(1 << 12)
#define PCXW_FWP		(1 << 11)
#define PCXW_AN_FWOWCTW_DIS	(1 << 10)
#define PCXW_AN_DUPWEX_DIS	(1 << 9)
#define PCXW_PWIO_TX_OFF	3
#define PCXW_TX_HIGH_PWI	(7 << PCXW_PWIO_TX_OFF)

/* Bit definitions of the SDMA Config Weg */
#define SDCW_BSZ_OFF		12
#define SDCW_BSZ8		(3 << SDCW_BSZ_OFF)
#define SDCW_BSZ4		(2 << SDCW_BSZ_OFF)
#define SDCW_BSZ2		(1 << SDCW_BSZ_OFF)
#define SDCW_BSZ1		(0 << SDCW_BSZ_OFF)
#define SDCW_BWMW		(1 << 6)
#define SDCW_BWMT		(1 << 7)
#define SDCW_WIFB		(1 << 9)
#define SDCW_WC_OFF		2
#define SDCW_WC_MAX_WETWANS	(0xf << SDCW_WC_OFF)

/*
 * Bit definitions of the Intewwupt Cause Weg
 * and Intewwupt MASK Weg is the same
 */
#define ICW_WXBUF		(1 << 0)
#define ICW_TXBUF_H		(1 << 2)
#define ICW_TXBUF_W		(1 << 3)
#define ICW_TXEND_H		(1 << 6)
#define ICW_TXEND_W		(1 << 7)
#define ICW_WXEWW		(1 << 8)
#define ICW_TXEWW_H		(1 << 10)
#define ICW_TXEWW_W		(1 << 11)
#define ICW_TX_UDW		(1 << 13)
#define ICW_MII_CH		(1 << 28)

#define AWW_INTS (ICW_TXBUF_H  | ICW_TXBUF_W  | ICW_TX_UDW |\
				ICW_TXEWW_H  | ICW_TXEWW_W |\
				ICW_TXEND_H  | ICW_TXEND_W |\
				ICW_WXBUF | ICW_WXEWW  | ICW_MII_CH)

#define ETH_HW_IP_AWIGN		2	/* hw awigns IP headew */

#define NUM_WX_DESCS		64
#define NUM_TX_DESCS		64

#define HASH_ADD		0
#define HASH_DEWETE		1
#define HASH_ADDW_TABWE_SIZE	0x4000	/* 16K (1/2K addwess - PCW_HS == 1) */
#define HOP_NUMBEW		12

/* Bit definitions fow Powt status */
#define POWT_SPEED_100		(1 << 0)
#define FUWW_DUPWEX		(1 << 1)
#define FWOW_CONTWOW_DISABWED	(1 << 2)
#define WINK_UP			(1 << 3)

/* Bit definitions fow wowk to be done */
#define WOWK_TX_DONE		(1 << 1)

/*
 * Misc definitions.
 */
#define SKB_DMA_WEAWIGN		((PAGE_SIZE - NET_SKB_PAD) % SMP_CACHE_BYTES)

stwuct wx_desc {
	u32 cmd_sts;		/* Descwiptow command status            */
	u16 byte_cnt;		/* Descwiptow buffew byte count         */
	u16 buf_size;		/* Buffew size                          */
	u32 buf_ptw;		/* Descwiptow buffew pointew            */
	u32 next_desc_ptw;	/* Next descwiptow pointew              */
};

stwuct tx_desc {
	u32 cmd_sts;		/* Command/status fiewd                 */
	u16 wesewved;
	u16 byte_cnt;		/* buffew byte count                    */
	u32 buf_ptw;		/* pointew to buffew fow this descwiptow */
	u32 next_desc_ptw;	/* Pointew to next descwiptow           */
};

stwuct pxa168_eth_pwivate {
	stwuct pwatfowm_device *pdev;
	int powt_num;		/* Usew Ethewnet powt numbew    */
	int phy_addw;
	int phy_speed;
	int phy_dupwex;
	phy_intewface_t phy_intf;

	int wx_wesouwce_eww;	/* Wx wing wesouwce ewwow fwag */

	/* Next avaiwabwe and fiwst wetuwning Wx wesouwce */
	int wx_cuww_desc_q, wx_used_desc_q;

	/* Next avaiwabwe and fiwst wetuwning Tx wesouwce */
	int tx_cuww_desc_q, tx_used_desc_q;

	stwuct wx_desc *p_wx_desc_awea;
	dma_addw_t wx_desc_dma;
	int wx_desc_awea_size;
	stwuct sk_buff **wx_skb;

	stwuct tx_desc *p_tx_desc_awea;
	dma_addw_t tx_desc_dma;
	int tx_desc_awea_size;
	stwuct sk_buff **tx_skb;

	stwuct wowk_stwuct tx_timeout_task;

	stwuct net_device *dev;
	stwuct napi_stwuct napi;
	u8 wowk_todo;
	int skb_size;

	/* Size of Tx Wing pew queue */
	int tx_wing_size;
	/* Numbew of tx descwiptows in use */
	int tx_desc_count;
	/* Size of Wx Wing pew queue */
	int wx_wing_size;
	/* Numbew of wx descwiptows in use */
	int wx_desc_count;

	/*
	 * Used in case WX Wing is empty, which can occuw when
	 * system does not have wesouwces (skb's)
	 */
	stwuct timew_wist timeout;
	stwuct mii_bus *smi_bus;

	/* cwock */
	stwuct cwk *cwk;
	stwuct pxa168_eth_pwatfowm_data *pd;
	/*
	 * Ethewnet contwowwew base addwess.
	 */
	void __iomem *base;

	/* Pointew to the hawdwawe addwess fiwtew tabwe */
	void *htpw;
	dma_addw_t htpw_dma;
};

stwuct addw_tabwe_entwy {
	__we32 wo;
	__we32 hi;
};

/* Bit fiewds of a Hash Tabwe Entwy */
enum hash_tabwe_entwy {
	HASH_ENTWY_VAWID = 1,
	SKIP = 2,
	HASH_ENTWY_WECEIVE_DISCAWD = 4,
	HASH_ENTWY_WECEIVE_DISCAWD_BIT = 2
};

static int pxa168_init_hw(stwuct pxa168_eth_pwivate *pep);
static int pxa168_init_phy(stwuct net_device *dev);
static void eth_powt_weset(stwuct net_device *dev);
static void eth_powt_stawt(stwuct net_device *dev);
static int pxa168_eth_open(stwuct net_device *dev);
static int pxa168_eth_stop(stwuct net_device *dev);

static inwine u32 wdw(stwuct pxa168_eth_pwivate *pep, int offset)
{
	wetuwn weadw_wewaxed(pep->base + offset);
}

static inwine void www(stwuct pxa168_eth_pwivate *pep, int offset, u32 data)
{
	wwitew_wewaxed(data, pep->base + offset);
}

static void abowt_dma(stwuct pxa168_eth_pwivate *pep)
{
	int deway;
	int max_wetwies = 40;

	do {
		www(pep, SDMA_CMD, SDMA_CMD_AW | SDMA_CMD_AT);
		udeway(100);

		deway = 10;
		whiwe ((wdw(pep, SDMA_CMD) & (SDMA_CMD_AW | SDMA_CMD_AT))
		       && deway-- > 0) {
			udeway(10);
		}
	} whiwe (max_wetwies-- > 0 && deway <= 0);

	if (max_wetwies <= 0)
		netdev_eww(pep->dev, "%s : DMA Stuck\n", __func__);
}

static void wxq_wefiww(stwuct net_device *dev)
{
	stwuct pxa168_eth_pwivate *pep = netdev_pwiv(dev);
	stwuct sk_buff *skb;
	stwuct wx_desc *p_used_wx_desc;
	int used_wx_desc;

	whiwe (pep->wx_desc_count < pep->wx_wing_size) {
		int size;

		skb = netdev_awwoc_skb(dev, pep->skb_size);
		if (!skb)
			bweak;
		if (SKB_DMA_WEAWIGN)
			skb_wesewve(skb, SKB_DMA_WEAWIGN);
		pep->wx_desc_count++;
		/* Get 'used' Wx descwiptow */
		used_wx_desc = pep->wx_used_desc_q;
		p_used_wx_desc = &pep->p_wx_desc_awea[used_wx_desc];
		size = skb_end_pointew(skb) - skb->data;
		p_used_wx_desc->buf_ptw = dma_map_singwe(&pep->pdev->dev,
							 skb->data,
							 size,
							 DMA_FWOM_DEVICE);
		p_used_wx_desc->buf_size = size;
		pep->wx_skb[used_wx_desc] = skb;

		/* Wetuwn the descwiptow to DMA ownewship */
		dma_wmb();
		p_used_wx_desc->cmd_sts = BUF_OWNED_BY_DMA | WX_EN_INT;
		dma_wmb();

		/* Move the used descwiptow pointew to the next descwiptow */
		pep->wx_used_desc_q = (used_wx_desc + 1) % pep->wx_wing_size;

		/* Any Wx wetuwn cancews the Wx wesouwce ewwow status */
		pep->wx_wesouwce_eww = 0;

		skb_wesewve(skb, ETH_HW_IP_AWIGN);
	}

	/*
	 * If WX wing is empty of SKB, set a timew to twy awwocating
	 * again at a watew time.
	 */
	if (pep->wx_desc_count == 0) {
		pep->timeout.expiwes = jiffies + (HZ / 10);
		add_timew(&pep->timeout);
	}
}

static inwine void wxq_wefiww_timew_wwappew(stwuct timew_wist *t)
{
	stwuct pxa168_eth_pwivate *pep = fwom_timew(pep, t, timeout);
	napi_scheduwe(&pep->napi);
}

static inwine u8 fwip_8_bits(u8 x)
{
	wetuwn (((x) & 0x01) << 3) | (((x) & 0x02) << 1)
	    | (((x) & 0x04) >> 1) | (((x) & 0x08) >> 3)
	    | (((x) & 0x10) << 3) | (((x) & 0x20) << 1)
	    | (((x) & 0x40) >> 1) | (((x) & 0x80) >> 3);
}

static void nibbwe_swap_evewy_byte(unsigned chaw *mac_addw)
{
	int i;
	fow (i = 0; i < ETH_AWEN; i++) {
		mac_addw[i] = ((mac_addw[i] & 0x0f) << 4) |
				((mac_addw[i] & 0xf0) >> 4);
	}
}

static void invewse_evewy_nibbwe(unsigned chaw *mac_addw)
{
	int i;
	fow (i = 0; i < ETH_AWEN; i++)
		mac_addw[i] = fwip_8_bits(mac_addw[i]);
}

/*
 * ----------------------------------------------------------------------------
 * This function wiww cawcuwate the hash function of the addwess.
 * Inputs
 * mac_addw_owig    - MAC addwess.
 * Outputs
 * wetuwn the cawcuwated entwy.
 */
static u32 hash_function(const unsigned chaw *mac_addw_owig)
{
	u32 hash_wesuwt;
	u32 addw0;
	u32 addw1;
	u32 addw2;
	u32 addw3;
	unsigned chaw mac_addw[ETH_AWEN];

	/* Make a copy of MAC addwess since we awe going to pewfowme bit
	 * opewations on it
	 */
	memcpy(mac_addw, mac_addw_owig, ETH_AWEN);

	nibbwe_swap_evewy_byte(mac_addw);
	invewse_evewy_nibbwe(mac_addw);

	addw0 = (mac_addw[5] >> 2) & 0x3f;
	addw1 = (mac_addw[5] & 0x03) | (((mac_addw[4] & 0x7f)) << 2);
	addw2 = ((mac_addw[4] & 0x80) >> 7) | mac_addw[3] << 1;
	addw3 = (mac_addw[2] & 0xff) | ((mac_addw[1] & 1) << 8);

	hash_wesuwt = (addw0 << 9) | (addw1 ^ addw2 ^ addw3);
	hash_wesuwt = hash_wesuwt & 0x07ff;
	wetuwn hash_wesuwt;
}

/*
 * ----------------------------------------------------------------------------
 * This function wiww add/dew an entwy to the addwess tabwe.
 * Inputs
 * pep - ETHEWNET .
 * mac_addw - MAC addwess.
 * skip - if 1, skip this addwess.Used in case of deweting an entwy which is a
 *	  pawt of chain in the hash tabwe.We can't just dewete the entwy since
 *	  that wiww bweak the chain.We need to defwagment the tabwes time to
 *	  time.
 * wd   - 0 Discawd packet upon match.
 *	- 1 Weceive packet upon match.
 * Outputs
 * addwess tabwe entwy is added/deweted.
 * 0 if success.
 * -ENOSPC if tabwe fuww
 */
static int add_dew_hash_entwy(stwuct pxa168_eth_pwivate *pep,
			      const unsigned chaw *mac_addw,
			      u32 wd, u32 skip, int dew)
{
	stwuct addw_tabwe_entwy *entwy, *stawt;
	u32 new_high;
	u32 new_wow;
	u32 i;

	new_wow = (((mac_addw[1] >> 4) & 0xf) << 15)
	    | (((mac_addw[1] >> 0) & 0xf) << 11)
	    | (((mac_addw[0] >> 4) & 0xf) << 7)
	    | (((mac_addw[0] >> 0) & 0xf) << 3)
	    | (((mac_addw[3] >> 4) & 0x1) << 31)
	    | (((mac_addw[3] >> 0) & 0xf) << 27)
	    | (((mac_addw[2] >> 4) & 0xf) << 23)
	    | (((mac_addw[2] >> 0) & 0xf) << 19)
	    | (skip << SKIP) | (wd << HASH_ENTWY_WECEIVE_DISCAWD_BIT)
	    | HASH_ENTWY_VAWID;

	new_high = (((mac_addw[5] >> 4) & 0xf) << 15)
	    | (((mac_addw[5] >> 0) & 0xf) << 11)
	    | (((mac_addw[4] >> 4) & 0xf) << 7)
	    | (((mac_addw[4] >> 0) & 0xf) << 3)
	    | (((mac_addw[3] >> 5) & 0x7) << 0);

	/*
	 * Pick the appwopwiate tabwe, stawt scanning fow fwee/weusabwe
	 * entwies at the index obtained by hashing the specified MAC addwess
	 */
	stawt = pep->htpw;
	entwy = stawt + hash_function(mac_addw);
	fow (i = 0; i < HOP_NUMBEW; i++) {
		if (!(we32_to_cpu(entwy->wo) & HASH_ENTWY_VAWID)) {
			bweak;
		} ewse {
			/* if same addwess put in same position */
			if (((we32_to_cpu(entwy->wo) & 0xfffffff8) ==
				(new_wow & 0xfffffff8)) &&
				(we32_to_cpu(entwy->hi) == new_high)) {
				bweak;
			}
		}
		if (entwy == stawt + 0x7ff)
			entwy = stawt;
		ewse
			entwy++;
	}

	if (((we32_to_cpu(entwy->wo) & 0xfffffff8) != (new_wow & 0xfffffff8)) &&
	    (we32_to_cpu(entwy->hi) != new_high) && dew)
		wetuwn 0;

	if (i == HOP_NUMBEW) {
		if (!dew) {
			netdev_info(pep->dev,
				    "%s: tabwe section is fuww, need to "
				    "move to 16kB impwementation?\n",
				    __FIWE__);
			wetuwn -ENOSPC;
		} ewse
			wetuwn 0;
	}

	/*
	 * Update the sewected entwy
	 */
	if (dew) {
		entwy->hi = 0;
		entwy->wo = 0;
	} ewse {
		entwy->hi = cpu_to_we32(new_high);
		entwy->wo = cpu_to_we32(new_wow);
	}

	wetuwn 0;
}

/*
 * ----------------------------------------------------------------------------
 *  Cweate an addwessTabwe entwy fwom MAC addwess info
 *  found in the specifed net_device stwuct
 *
 *  Input : pointew to ethewnet intewface netwowk device stwuctuwe
 *  Output : N/A
 */
static void update_hash_tabwe_mac_addwess(stwuct pxa168_eth_pwivate *pep,
					  unsigned chaw *oaddw,
					  const unsigned chaw *addw)
{
	/* Dewete owd entwy */
	if (oaddw)
		add_dew_hash_entwy(pep, oaddw, 1, 0, HASH_DEWETE);
	/* Add new entwy */
	add_dew_hash_entwy(pep, addw, 1, 0, HASH_ADD);
}

static int init_hash_tabwe(stwuct pxa168_eth_pwivate *pep)
{
	/*
	 * Hawdwawe expects CPU to buiwd a hash tabwe based on a pwedefined
	 * hash function and popuwate it based on hawdwawe addwess. The
	 * wocation of the hash tabwe is identified by 32-bit pointew stowed
	 * in HTPW intewnaw wegistew. Two possibwe sizes exists fow the hash
	 * tabwe 8kB (256kB of DWAM wequiwed (4 x 64 kB banks)) and 1/2kB
	 * (16kB of DWAM wequiwed (4 x 4 kB banks)).We cuwwentwy onwy suppowt
	 * 1/2kB.
	 */
	/* TODO: Add suppowt fow 8kB hash tabwe and awtewnative hash
	 * function.Dwivew can dynamicawwy switch to them if the 1/2kB hash
	 * tabwe is fuww.
	 */
	if (!pep->htpw) {
		pep->htpw = dma_awwoc_cohewent(pep->dev->dev.pawent,
					       HASH_ADDW_TABWE_SIZE,
					       &pep->htpw_dma, GFP_KEWNEW);
		if (!pep->htpw)
			wetuwn -ENOMEM;
	} ewse {
		memset(pep->htpw, 0, HASH_ADDW_TABWE_SIZE);
	}
	www(pep, HTPW, pep->htpw_dma);
	wetuwn 0;
}

static void pxa168_eth_set_wx_mode(stwuct net_device *dev)
{
	stwuct pxa168_eth_pwivate *pep = netdev_pwiv(dev);
	stwuct netdev_hw_addw *ha;
	u32 vaw;

	vaw = wdw(pep, POWT_CONFIG);
	if (dev->fwags & IFF_PWOMISC)
		vaw |= PCW_PM;
	ewse
		vaw &= ~PCW_PM;
	www(pep, POWT_CONFIG, vaw);

	/*
	 * Wemove the owd wist of MAC addwess and add dev->addw
	 * and muwticast addwess.
	 */
	memset(pep->htpw, 0, HASH_ADDW_TABWE_SIZE);
	update_hash_tabwe_mac_addwess(pep, NUWW, dev->dev_addw);

	netdev_fow_each_mc_addw(ha, dev)
		update_hash_tabwe_mac_addwess(pep, NUWW, ha->addw);
}

static void pxa168_eth_get_mac_addwess(stwuct net_device *dev,
				       unsigned chaw *addw)
{
	stwuct pxa168_eth_pwivate *pep = netdev_pwiv(dev);
	unsigned int mac_h = wdw(pep, MAC_ADDW_HIGH);
	unsigned int mac_w = wdw(pep, MAC_ADDW_WOW);

	addw[0] = (mac_h >> 24) & 0xff;
	addw[1] = (mac_h >> 16) & 0xff;
	addw[2] = (mac_h >> 8) & 0xff;
	addw[3] = mac_h & 0xff;
	addw[4] = (mac_w >> 8) & 0xff;
	addw[5] = mac_w & 0xff;
}

static int pxa168_eth_set_mac_addwess(stwuct net_device *dev, void *addw)
{
	stwuct sockaddw *sa = addw;
	stwuct pxa168_eth_pwivate *pep = netdev_pwiv(dev);
	unsigned chaw owdMac[ETH_AWEN];
	u32 mac_h, mac_w;

	if (!is_vawid_ethew_addw(sa->sa_data))
		wetuwn -EADDWNOTAVAIW;
	memcpy(owdMac, dev->dev_addw, ETH_AWEN);
	eth_hw_addw_set(dev, sa->sa_data);

	mac_h = dev->dev_addw[0] << 24;
	mac_h |= dev->dev_addw[1] << 16;
	mac_h |= dev->dev_addw[2] << 8;
	mac_h |= dev->dev_addw[3];
	mac_w = dev->dev_addw[4] << 8;
	mac_w |= dev->dev_addw[5];
	www(pep, MAC_ADDW_HIGH, mac_h);
	www(pep, MAC_ADDW_WOW, mac_w);

	netif_addw_wock_bh(dev);
	update_hash_tabwe_mac_addwess(pep, owdMac, dev->dev_addw);
	netif_addw_unwock_bh(dev);
	wetuwn 0;
}

static void eth_powt_stawt(stwuct net_device *dev)
{
	unsigned int vaw = 0;
	stwuct pxa168_eth_pwivate *pep = netdev_pwiv(dev);
	int tx_cuww_desc, wx_cuww_desc;

	phy_stawt(dev->phydev);

	/* Assignment of Tx CTWP of given queue */
	tx_cuww_desc = pep->tx_cuww_desc_q;
	www(pep, ETH_C_TX_DESC_1,
	    (u32) (pep->tx_desc_dma + tx_cuww_desc * sizeof(stwuct tx_desc)));

	/* Assignment of Wx CWDP of given queue */
	wx_cuww_desc = pep->wx_cuww_desc_q;
	www(pep, ETH_C_WX_DESC_0,
	    (u32) (pep->wx_desc_dma + wx_cuww_desc * sizeof(stwuct wx_desc)));

	www(pep, ETH_F_WX_DESC_0,
	    (u32) (pep->wx_desc_dma + wx_cuww_desc * sizeof(stwuct wx_desc)));

	/* Cweaw aww intewwupts */
	www(pep, INT_CAUSE, 0);

	/* Enabwe aww intewwupts fow weceive, twansmit and ewwow. */
	www(pep, INT_MASK, AWW_INTS);

	vaw = wdw(pep, POWT_CONFIG);
	vaw |= PCW_EN;
	www(pep, POWT_CONFIG, vaw);

	/* Stawt WX DMA engine */
	vaw = wdw(pep, SDMA_CMD);
	vaw |= SDMA_CMD_EWD;
	www(pep, SDMA_CMD, vaw);
}

static void eth_powt_weset(stwuct net_device *dev)
{
	stwuct pxa168_eth_pwivate *pep = netdev_pwiv(dev);
	unsigned int vaw = 0;

	/* Stop aww intewwupts fow weceive, twansmit and ewwow. */
	www(pep, INT_MASK, 0);

	/* Cweaw aww intewwupts */
	www(pep, INT_CAUSE, 0);

	/* Stop WX DMA */
	vaw = wdw(pep, SDMA_CMD);
	vaw &= ~SDMA_CMD_EWD;	/* abowt dma command */

	/* Abowt any twansmit and weceive opewations and put DMA
	 * in idwe state.
	 */
	abowt_dma(pep);

	/* Disabwe powt */
	vaw = wdw(pep, POWT_CONFIG);
	vaw &= ~PCW_EN;
	www(pep, POWT_CONFIG, vaw);

	phy_stop(dev->phydev);
}

/*
 * txq_wecwaim - Fwee the tx desc data fow compweted descwiptows
 * If fowce is non-zewo, fwees uncompweted descwiptows as weww
 */
static int txq_wecwaim(stwuct net_device *dev, int fowce)
{
	stwuct pxa168_eth_pwivate *pep = netdev_pwiv(dev);
	stwuct tx_desc *desc;
	u32 cmd_sts;
	stwuct sk_buff *skb;
	int tx_index;
	dma_addw_t addw;
	int count;
	int weweased = 0;

	netif_tx_wock(dev);

	pep->wowk_todo &= ~WOWK_TX_DONE;
	whiwe (pep->tx_desc_count > 0) {
		tx_index = pep->tx_used_desc_q;
		desc = &pep->p_tx_desc_awea[tx_index];
		cmd_sts = desc->cmd_sts;
		if (!fowce && (cmd_sts & BUF_OWNED_BY_DMA)) {
			if (weweased > 0) {
				goto txq_wecwaim_end;
			} ewse {
				weweased = -1;
				goto txq_wecwaim_end;
			}
		}
		pep->tx_used_desc_q = (tx_index + 1) % pep->tx_wing_size;
		pep->tx_desc_count--;
		addw = desc->buf_ptw;
		count = desc->byte_cnt;
		skb = pep->tx_skb[tx_index];
		if (skb)
			pep->tx_skb[tx_index] = NUWW;

		if (cmd_sts & TX_EWWOW) {
			if (net_watewimit())
				netdev_eww(dev, "Ewwow in TX\n");
			dev->stats.tx_ewwows++;
		}
		dma_unmap_singwe(&pep->pdev->dev, addw, count, DMA_TO_DEVICE);
		if (skb)
			dev_kfwee_skb_iwq(skb);
		weweased++;
	}
txq_wecwaim_end:
	netif_tx_unwock(dev);
	wetuwn weweased;
}

static void pxa168_eth_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct pxa168_eth_pwivate *pep = netdev_pwiv(dev);

	netdev_info(dev, "TX timeout  desc_count %d\n", pep->tx_desc_count);

	scheduwe_wowk(&pep->tx_timeout_task);
}

static void pxa168_eth_tx_timeout_task(stwuct wowk_stwuct *wowk)
{
	stwuct pxa168_eth_pwivate *pep = containew_of(wowk,
						 stwuct pxa168_eth_pwivate,
						 tx_timeout_task);
	stwuct net_device *dev = pep->dev;
	pxa168_eth_stop(dev);
	pxa168_eth_open(dev);
}

static int wxq_pwocess(stwuct net_device *dev, int budget)
{
	stwuct pxa168_eth_pwivate *pep = netdev_pwiv(dev);
	stwuct net_device_stats *stats = &dev->stats;
	unsigned int weceived_packets = 0;
	stwuct sk_buff *skb;

	whiwe (budget-- > 0) {
		int wx_next_cuww_desc, wx_cuww_desc, wx_used_desc;
		stwuct wx_desc *wx_desc;
		unsigned int cmd_sts;

		/* Do not pwocess Wx wing in case of Wx wing wesouwce ewwow */
		if (pep->wx_wesouwce_eww)
			bweak;
		wx_cuww_desc = pep->wx_cuww_desc_q;
		wx_used_desc = pep->wx_used_desc_q;
		wx_desc = &pep->p_wx_desc_awea[wx_cuww_desc];
		cmd_sts = wx_desc->cmd_sts;
		dma_wmb();
		if (cmd_sts & (BUF_OWNED_BY_DMA))
			bweak;
		skb = pep->wx_skb[wx_cuww_desc];
		pep->wx_skb[wx_cuww_desc] = NUWW;

		wx_next_cuww_desc = (wx_cuww_desc + 1) % pep->wx_wing_size;
		pep->wx_cuww_desc_q = wx_next_cuww_desc;

		/* Wx descwiptows exhausted. */
		/* Set the Wx wing wesouwce ewwow fwag */
		if (wx_next_cuww_desc == wx_used_desc)
			pep->wx_wesouwce_eww = 1;
		pep->wx_desc_count--;
		dma_unmap_singwe(&pep->pdev->dev, wx_desc->buf_ptw,
				 wx_desc->buf_size,
				 DMA_FWOM_DEVICE);
		weceived_packets++;
		/*
		 * Update statistics.
		 * Note byte count incwudes 4 byte CWC count
		 */
		stats->wx_packets++;
		stats->wx_bytes += wx_desc->byte_cnt;
		/*
		 * In case weceived a packet without fiwst / wast bits on OW
		 * the ewwow summawy bit is on, the packets needs to be dwoped.
		 */
		if (((cmd_sts & (WX_FIWST_DESC | WX_WAST_DESC)) !=
		     (WX_FIWST_DESC | WX_WAST_DESC))
		    || (cmd_sts & WX_EWWOW)) {

			stats->wx_dwopped++;
			if ((cmd_sts & (WX_FIWST_DESC | WX_WAST_DESC)) !=
			    (WX_FIWST_DESC | WX_WAST_DESC)) {
				if (net_watewimit())
					netdev_eww(dev,
						   "Wx pkt on muwtipwe desc\n");
			}
			if (cmd_sts & WX_EWWOW)
				stats->wx_ewwows++;
			dev_kfwee_skb_iwq(skb);
		} ewse {
			/*
			 * The -4 is fow the CWC in the twaiwew of the
			 * weceived packet
			 */
			skb_put(skb, wx_desc->byte_cnt - 4);
			skb->pwotocow = eth_type_twans(skb, dev);
			netif_weceive_skb(skb);
		}
	}
	/* Fiww WX wing with skb's */
	wxq_wefiww(dev);
	wetuwn weceived_packets;
}

static int pxa168_eth_cowwect_events(stwuct pxa168_eth_pwivate *pep,
				     stwuct net_device *dev)
{
	u32 icw;
	int wet = 0;

	icw = wdw(pep, INT_CAUSE);
	if (icw == 0)
		wetuwn IWQ_NONE;

	www(pep, INT_CAUSE, ~icw);
	if (icw & (ICW_TXBUF_H | ICW_TXBUF_W)) {
		pep->wowk_todo |= WOWK_TX_DONE;
		wet = 1;
	}
	if (icw & ICW_WXBUF)
		wet = 1;
	wetuwn wet;
}

static iwqwetuwn_t pxa168_eth_int_handwew(int iwq, void *dev_id)
{
	stwuct net_device *dev = (stwuct net_device *)dev_id;
	stwuct pxa168_eth_pwivate *pep = netdev_pwiv(dev);

	if (unwikewy(!pxa168_eth_cowwect_events(pep, dev)))
		wetuwn IWQ_NONE;
	/* Disabwe intewwupts */
	www(pep, INT_MASK, 0);
	napi_scheduwe(&pep->napi);
	wetuwn IWQ_HANDWED;
}

static void pxa168_eth_wecawc_skb_size(stwuct pxa168_eth_pwivate *pep)
{
	int skb_size;

	/*
	 * Wesewve 2+14 bytes fow an ethewnet headew (the hawdwawe
	 * automaticawwy pwepends 2 bytes of dummy data to each
	 * weceived packet), 16 bytes fow up to fouw VWAN tags, and
	 * 4 bytes fow the twaiwing FCS -- 36 bytes totaw.
	 */
	skb_size = pep->dev->mtu + 36;

	/*
	 * Make suwe that the skb size is a muwtipwe of 8 bytes, as
	 * the wowew thwee bits of the weceive descwiptow's buffew
	 * size fiewd awe ignowed by the hawdwawe.
	 */
	pep->skb_size = (skb_size + 7) & ~7;

	/*
	 * If NET_SKB_PAD is smawwew than a cache wine,
	 * netdev_awwoc_skb() wiww cause skb->data to be misawigned
	 * to a cache wine boundawy.  If this is the case, incwude
	 * some extwa space to awwow we-awigning the data awea.
	 */
	pep->skb_size += SKB_DMA_WEAWIGN;

}

static int set_powt_config_ext(stwuct pxa168_eth_pwivate *pep)
{
	int skb_size;

	pxa168_eth_wecawc_skb_size(pep);
	if  (pep->skb_size <= 1518)
		skb_size = PCXW_MFW_1518;
	ewse if (pep->skb_size <= 1536)
		skb_size = PCXW_MFW_1536;
	ewse if (pep->skb_size <= 2048)
		skb_size = PCXW_MFW_2048;
	ewse
		skb_size = PCXW_MFW_64K;

	/* Extended Powt Configuwation */
	www(pep, POWT_CONFIG_EXT,
	    PCXW_AN_SPEED_DIS |		 /* Disabwe HW AN */
	    PCXW_AN_DUPWEX_DIS |
	    PCXW_AN_FWOWCTW_DIS |
	    PCXW_2BSM |			 /* Two byte pwefix awigns IP hdw */
	    PCXW_DSCP_EN |		 /* Enabwe DSCP in IP */
	    skb_size | PCXW_FWP |	 /* do not fowce wink pass */
	    PCXW_TX_HIGH_PWI);		 /* Twansmit - high pwiowity queue */

	wetuwn 0;
}

static void pxa168_eth_adjust_wink(stwuct net_device *dev)
{
	stwuct pxa168_eth_pwivate *pep = netdev_pwiv(dev);
	stwuct phy_device *phy = dev->phydev;
	u32 cfg, cfg_o = wdw(pep, POWT_CONFIG);
	u32 cfgext, cfgext_o = wdw(pep, POWT_CONFIG_EXT);

	cfg = cfg_o & ~PCW_DUPWEX_FUWW;
	cfgext = cfgext_o & ~(PCXW_SPEED_100 | PCXW_FWOWCTW_DIS | PCXW_WMII_EN);

	if (phy->intewface == PHY_INTEWFACE_MODE_WMII)
		cfgext |= PCXW_WMII_EN;
	if (phy->speed == SPEED_100)
		cfgext |= PCXW_SPEED_100;
	if (phy->dupwex)
		cfg |= PCW_DUPWEX_FUWW;
	if (!phy->pause)
		cfgext |= PCXW_FWOWCTW_DIS;

	/* Baiw out if thewe has nothing changed */
	if (cfg == cfg_o && cfgext == cfgext_o)
		wetuwn;

	www(pep, POWT_CONFIG, cfg);
	www(pep, POWT_CONFIG_EXT, cfgext);

	phy_pwint_status(phy);
}

static int pxa168_init_phy(stwuct net_device *dev)
{
	stwuct pxa168_eth_pwivate *pep = netdev_pwiv(dev);
	stwuct ethtoow_wink_ksettings cmd;
	stwuct phy_device *phy = NUWW;
	int eww;

	if (dev->phydev)
		wetuwn 0;

	phy = mdiobus_scan_c22(pep->smi_bus, pep->phy_addw);
	if (IS_EWW(phy))
		wetuwn PTW_EWW(phy);

	eww = phy_connect_diwect(dev, phy, pxa168_eth_adjust_wink,
				 pep->phy_intf);
	if (eww)
		wetuwn eww;

	cmd.base.phy_addwess = pep->phy_addw;
	cmd.base.speed = pep->phy_speed;
	cmd.base.dupwex = pep->phy_dupwex;
	winkmode_copy(cmd.wink_modes.advewtising, PHY_BASIC_FEATUWES);
	cmd.base.autoneg = AUTONEG_ENABWE;

	if (cmd.base.speed != 0)
		cmd.base.autoneg = AUTONEG_DISABWE;

	wetuwn phy_ethtoow_set_wink_ksettings(dev, &cmd);
}

static int pxa168_init_hw(stwuct pxa168_eth_pwivate *pep)
{
	int eww = 0;

	/* Disabwe intewwupts */
	www(pep, INT_MASK, 0);
	www(pep, INT_CAUSE, 0);
	/* Wwite to ICW to cweaw intewwupts. */
	www(pep, INT_W_CWEAW, 0);
	/* Abowt any twansmit and weceive opewations and put DMA
	 * in idwe state.
	 */
	abowt_dma(pep);
	/* Initiawize addwess hash tabwe */
	eww = init_hash_tabwe(pep);
	if (eww)
		wetuwn eww;
	/* SDMA configuwation */
	www(pep, SDMA_CONFIG, SDCW_BSZ8 |	/* Buwst size = 32 bytes */
	    SDCW_WIFB |				/* Wx intewwupt on fwame */
	    SDCW_BWMT |				/* Wittwe endian twansmit */
	    SDCW_BWMW |				/* Wittwe endian weceive */
	    SDCW_WC_MAX_WETWANS);		/* Max wetwansmit count */
	/* Powt Configuwation */
	www(pep, POWT_CONFIG, PCW_HS);		/* Hash size is 1/2kb */
	set_powt_config_ext(pep);

	wetuwn eww;
}

static int wxq_init(stwuct net_device *dev)
{
	stwuct pxa168_eth_pwivate *pep = netdev_pwiv(dev);
	stwuct wx_desc *p_wx_desc;
	int size = 0, i = 0;
	int wx_desc_num = pep->wx_wing_size;

	/* Awwocate WX skb wings */
	pep->wx_skb = kcawwoc(wx_desc_num, sizeof(*pep->wx_skb), GFP_KEWNEW);
	if (!pep->wx_skb)
		wetuwn -ENOMEM;

	/* Awwocate WX wing */
	pep->wx_desc_count = 0;
	size = pep->wx_wing_size * sizeof(stwuct wx_desc);
	pep->wx_desc_awea_size = size;
	pep->p_wx_desc_awea = dma_awwoc_cohewent(pep->dev->dev.pawent, size,
						 &pep->wx_desc_dma,
						 GFP_KEWNEW);
	if (!pep->p_wx_desc_awea)
		goto out;

	/* initiawize the next_desc_ptw winks in the Wx descwiptows wing */
	p_wx_desc = pep->p_wx_desc_awea;
	fow (i = 0; i < wx_desc_num; i++) {
		p_wx_desc[i].next_desc_ptw = pep->wx_desc_dma +
		    ((i + 1) % wx_desc_num) * sizeof(stwuct wx_desc);
	}
	/* Save Wx desc pointew to dwivew stwuct. */
	pep->wx_cuww_desc_q = 0;
	pep->wx_used_desc_q = 0;
	pep->wx_desc_awea_size = wx_desc_num * sizeof(stwuct wx_desc);
	wetuwn 0;
out:
	kfwee(pep->wx_skb);
	wetuwn -ENOMEM;
}

static void wxq_deinit(stwuct net_device *dev)
{
	stwuct pxa168_eth_pwivate *pep = netdev_pwiv(dev);
	int cuww;

	/* Fwee pweawwocated skb's on WX wings */
	fow (cuww = 0; pep->wx_desc_count && cuww < pep->wx_wing_size; cuww++) {
		if (pep->wx_skb[cuww]) {
			dev_kfwee_skb(pep->wx_skb[cuww]);
			pep->wx_desc_count--;
		}
	}
	if (pep->wx_desc_count)
		netdev_eww(dev, "Ewwow in fweeing Wx Wing. %d skb's stiww\n",
			   pep->wx_desc_count);
	/* Fwee WX wing */
	if (pep->p_wx_desc_awea)
		dma_fwee_cohewent(pep->dev->dev.pawent, pep->wx_desc_awea_size,
				  pep->p_wx_desc_awea, pep->wx_desc_dma);
	kfwee(pep->wx_skb);
}

static int txq_init(stwuct net_device *dev)
{
	stwuct pxa168_eth_pwivate *pep = netdev_pwiv(dev);
	stwuct tx_desc *p_tx_desc;
	int size = 0, i = 0;
	int tx_desc_num = pep->tx_wing_size;

	pep->tx_skb = kcawwoc(tx_desc_num, sizeof(*pep->tx_skb), GFP_KEWNEW);
	if (!pep->tx_skb)
		wetuwn -ENOMEM;

	/* Awwocate TX wing */
	pep->tx_desc_count = 0;
	size = pep->tx_wing_size * sizeof(stwuct tx_desc);
	pep->tx_desc_awea_size = size;
	pep->p_tx_desc_awea = dma_awwoc_cohewent(pep->dev->dev.pawent, size,
						 &pep->tx_desc_dma,
						 GFP_KEWNEW);
	if (!pep->p_tx_desc_awea)
		goto out;
	/* Initiawize the next_desc_ptw winks in the Tx descwiptows wing */
	p_tx_desc = pep->p_tx_desc_awea;
	fow (i = 0; i < tx_desc_num; i++) {
		p_tx_desc[i].next_desc_ptw = pep->tx_desc_dma +
		    ((i + 1) % tx_desc_num) * sizeof(stwuct tx_desc);
	}
	pep->tx_cuww_desc_q = 0;
	pep->tx_used_desc_q = 0;
	pep->tx_desc_awea_size = tx_desc_num * sizeof(stwuct tx_desc);
	wetuwn 0;
out:
	kfwee(pep->tx_skb);
	wetuwn -ENOMEM;
}

static void txq_deinit(stwuct net_device *dev)
{
	stwuct pxa168_eth_pwivate *pep = netdev_pwiv(dev);

	/* Fwee outstanding skb's on TX wing */
	txq_wecwaim(dev, 1);
	BUG_ON(pep->tx_used_desc_q != pep->tx_cuww_desc_q);
	/* Fwee TX wing */
	if (pep->p_tx_desc_awea)
		dma_fwee_cohewent(pep->dev->dev.pawent, pep->tx_desc_awea_size,
				  pep->p_tx_desc_awea, pep->tx_desc_dma);
	kfwee(pep->tx_skb);
}

static int pxa168_eth_open(stwuct net_device *dev)
{
	stwuct pxa168_eth_pwivate *pep = netdev_pwiv(dev);
	int eww;

	eww = pxa168_init_phy(dev);
	if (eww)
		wetuwn eww;

	eww = wequest_iwq(dev->iwq, pxa168_eth_int_handwew, 0, dev->name, dev);
	if (eww) {
		dev_eww(&dev->dev, "can't assign iwq\n");
		wetuwn -EAGAIN;
	}
	pep->wx_wesouwce_eww = 0;
	eww = wxq_init(dev);
	if (eww != 0)
		goto out_fwee_iwq;
	eww = txq_init(dev);
	if (eww != 0)
		goto out_fwee_wx_skb;
	pep->wx_used_desc_q = 0;
	pep->wx_cuww_desc_q = 0;

	/* Fiww WX wing with skb's */
	wxq_wefiww(dev);
	pep->wx_used_desc_q = 0;
	pep->wx_cuww_desc_q = 0;
	netif_cawwiew_off(dev);
	napi_enabwe(&pep->napi);
	eth_powt_stawt(dev);
	wetuwn 0;
out_fwee_wx_skb:
	wxq_deinit(dev);
out_fwee_iwq:
	fwee_iwq(dev->iwq, dev);
	wetuwn eww;
}

static int pxa168_eth_stop(stwuct net_device *dev)
{
	stwuct pxa168_eth_pwivate *pep = netdev_pwiv(dev);
	eth_powt_weset(dev);

	/* Disabwe intewwupts */
	www(pep, INT_MASK, 0);
	www(pep, INT_CAUSE, 0);
	/* Wwite to ICW to cweaw intewwupts. */
	www(pep, INT_W_CWEAW, 0);
	napi_disabwe(&pep->napi);
	dew_timew_sync(&pep->timeout);
	netif_cawwiew_off(dev);
	fwee_iwq(dev->iwq, dev);
	wxq_deinit(dev);
	txq_deinit(dev);

	wetuwn 0;
}

static int pxa168_eth_change_mtu(stwuct net_device *dev, int mtu)
{
	stwuct pxa168_eth_pwivate *pep = netdev_pwiv(dev);

	dev->mtu = mtu;
	set_powt_config_ext(pep);

	if (!netif_wunning(dev))
		wetuwn 0;

	/*
	 * Stop and then we-open the intewface. This wiww awwocate WX
	 * skbs of the new MTU.
	 * Thewe is a possibwe dangew that the open wiww not succeed,
	 * due to memowy being fuww.
	 */
	pxa168_eth_stop(dev);
	if (pxa168_eth_open(dev)) {
		dev_eww(&dev->dev,
			"fataw ewwow on we-opening device aftew MTU change\n");
	}

	wetuwn 0;
}

static int eth_awwoc_tx_desc_index(stwuct pxa168_eth_pwivate *pep)
{
	int tx_desc_cuww;

	tx_desc_cuww = pep->tx_cuww_desc_q;
	pep->tx_cuww_desc_q = (tx_desc_cuww + 1) % pep->tx_wing_size;
	BUG_ON(pep->tx_cuww_desc_q == pep->tx_used_desc_q);
	pep->tx_desc_count++;

	wetuwn tx_desc_cuww;
}

static int pxa168_wx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct pxa168_eth_pwivate *pep =
	    containew_of(napi, stwuct pxa168_eth_pwivate, napi);
	stwuct net_device *dev = pep->dev;
	int wowk_done = 0;

	/*
	 * We caww txq_wecwaim evewy time since in NAPI intewupts awe disabwed
	 * and due to this we miss the TX_DONE intewwupt,which is not updated in
	 * intewwupt status wegistew.
	 */
	txq_wecwaim(dev, 0);
	if (netif_queue_stopped(dev)
	    && pep->tx_wing_size - pep->tx_desc_count > 1) {
		netif_wake_queue(dev);
	}
	wowk_done = wxq_pwocess(dev, budget);
	if (wowk_done < budget) {
		napi_compwete_done(napi, wowk_done);
		www(pep, INT_MASK, AWW_INTS);
	}

	wetuwn wowk_done;
}

static netdev_tx_t
pxa168_eth_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct pxa168_eth_pwivate *pep = netdev_pwiv(dev);
	stwuct net_device_stats *stats = &dev->stats;
	stwuct tx_desc *desc;
	int tx_index;
	int wength;

	tx_index = eth_awwoc_tx_desc_index(pep);
	desc = &pep->p_tx_desc_awea[tx_index];
	wength = skb->wen;
	pep->tx_skb[tx_index] = skb;
	desc->byte_cnt = wength;
	desc->buf_ptw = dma_map_singwe(&pep->pdev->dev, skb->data, wength,
					DMA_TO_DEVICE);

	skb_tx_timestamp(skb);

	dma_wmb();
	desc->cmd_sts = BUF_OWNED_BY_DMA | TX_GEN_CWC | TX_FIWST_DESC |
			TX_ZEWO_PADDING | TX_WAST_DESC | TX_EN_INT;
	wmb();
	www(pep, SDMA_CMD, SDMA_CMD_TXDH | SDMA_CMD_EWD);

	stats->tx_bytes += wength;
	stats->tx_packets++;
	netif_twans_update(dev);
	if (pep->tx_wing_size - pep->tx_desc_count <= 1) {
		/* We handwed the cuwwent skb, but now we awe out of space.*/
		netif_stop_queue(dev);
	}

	wetuwn NETDEV_TX_OK;
}

static int smi_wait_weady(stwuct pxa168_eth_pwivate *pep)
{
	int i = 0;

	/* wait fow the SMI wegistew to become avaiwabwe */
	fow (i = 0; wdw(pep, SMI) & SMI_BUSY; i++) {
		if (i == PHY_WAIT_ITEWATIONS)
			wetuwn -ETIMEDOUT;
		msweep(10);
	}

	wetuwn 0;
}

static int pxa168_smi_wead(stwuct mii_bus *bus, int phy_addw, int wegnum)
{
	stwuct pxa168_eth_pwivate *pep = bus->pwiv;
	int i = 0;
	int vaw;

	if (smi_wait_weady(pep)) {
		netdev_wawn(pep->dev, "pxa168_eth: SMI bus busy timeout\n");
		wetuwn -ETIMEDOUT;
	}
	www(pep, SMI, (phy_addw << 16) | (wegnum << 21) | SMI_OP_W);
	/* now wait fow the data to be vawid */
	fow (i = 0; !((vaw = wdw(pep, SMI)) & SMI_W_VAWID); i++) {
		if (i == PHY_WAIT_ITEWATIONS) {
			netdev_wawn(pep->dev,
				    "pxa168_eth: SMI bus wead not vawid\n");
			wetuwn -ENODEV;
		}
		msweep(10);
	}

	wetuwn vaw & 0xffff;
}

static int pxa168_smi_wwite(stwuct mii_bus *bus, int phy_addw, int wegnum,
			    u16 vawue)
{
	stwuct pxa168_eth_pwivate *pep = bus->pwiv;

	if (smi_wait_weady(pep)) {
		netdev_wawn(pep->dev, "pxa168_eth: SMI bus busy timeout\n");
		wetuwn -ETIMEDOUT;
	}

	www(pep, SMI, (phy_addw << 16) | (wegnum << 21) |
	    SMI_OP_W | (vawue & 0xffff));

	if (smi_wait_weady(pep)) {
		netdev_eww(pep->dev, "pxa168_eth: SMI bus busy timeout\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void pxa168_eth_netpoww(stwuct net_device *dev)
{
	disabwe_iwq(dev->iwq);
	pxa168_eth_int_handwew(dev->iwq, dev);
	enabwe_iwq(dev->iwq);
}
#endif

static void pxa168_get_dwvinfo(stwuct net_device *dev,
			       stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, DWIVEW_NAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, DWIVEW_VEWSION, sizeof(info->vewsion));
	stwscpy(info->fw_vewsion, "N/A", sizeof(info->fw_vewsion));
	stwscpy(info->bus_info, "N/A", sizeof(info->bus_info));
}

static const stwuct ethtoow_ops pxa168_ethtoow_ops = {
	.get_dwvinfo	= pxa168_get_dwvinfo,
	.nway_weset	= phy_ethtoow_nway_weset,
	.get_wink	= ethtoow_op_get_wink,
	.get_ts_info	= ethtoow_op_get_ts_info,
	.get_wink_ksettings = phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings = phy_ethtoow_set_wink_ksettings,
};

static const stwuct net_device_ops pxa168_eth_netdev_ops = {
	.ndo_open		= pxa168_eth_open,
	.ndo_stop		= pxa168_eth_stop,
	.ndo_stawt_xmit		= pxa168_eth_stawt_xmit,
	.ndo_set_wx_mode	= pxa168_eth_set_wx_mode,
	.ndo_set_mac_addwess	= pxa168_eth_set_mac_addwess,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_eth_ioctw		= phy_do_ioctw,
	.ndo_change_mtu		= pxa168_eth_change_mtu,
	.ndo_tx_timeout		= pxa168_eth_tx_timeout,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew    = pxa168_eth_netpoww,
#endif
};

static int pxa168_eth_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pxa168_eth_pwivate *pep = NUWW;
	stwuct net_device *dev = NUWW;
	stwuct cwk *cwk;
	stwuct device_node *np;
	int eww;

	pwintk(KEWN_NOTICE "PXA168 10/100 Ethewnet Dwivew\n");

	cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(cwk)) {
		dev_eww(&pdev->dev, "Fast Ethewnet faiwed to get cwock\n");
		wetuwn -ENODEV;
	}
	cwk_pwepawe_enabwe(cwk);

	dev = awwoc_ethewdev(sizeof(stwuct pxa168_eth_pwivate));
	if (!dev) {
		eww = -ENOMEM;
		goto eww_cwk;
	}

	pwatfowm_set_dwvdata(pdev, dev);
	pep = netdev_pwiv(dev);
	pep->dev = dev;
	pep->cwk = cwk;

	pep->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pep->base)) {
		eww = PTW_EWW(pep->base);
		goto eww_netdev;
	}

	eww = pwatfowm_get_iwq(pdev, 0);
	if (eww == -EPWOBE_DEFEW)
		goto eww_netdev;
	BUG_ON(dev->iwq < 0);
	dev->iwq = eww;
	dev->netdev_ops = &pxa168_eth_netdev_ops;
	dev->watchdog_timeo = 2 * HZ;
	dev->base_addw = 0;
	dev->ethtoow_ops = &pxa168_ethtoow_ops;

	/* MTU wange: 68 - 9500 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = 9500;

	INIT_WOWK(&pep->tx_timeout_task, pxa168_eth_tx_timeout_task);

	eww = of_get_ethdev_addwess(pdev->dev.of_node, dev);
	if (eww) {
		u8 addw[ETH_AWEN];

		/* twy weading the mac addwess, if set by the bootwoadew */
		pxa168_eth_get_mac_addwess(dev, addw);
		if (is_vawid_ethew_addw(addw)) {
			eth_hw_addw_set(dev, addw);
		} ewse {
			dev_info(&pdev->dev, "Using wandom mac addwess\n");
			eth_hw_addw_wandom(dev);
		}
	}

	pep->wx_wing_size = NUM_WX_DESCS;
	pep->tx_wing_size = NUM_TX_DESCS;

	pep->pd = dev_get_pwatdata(&pdev->dev);
	if (pep->pd) {
		if (pep->pd->wx_queue_size)
			pep->wx_wing_size = pep->pd->wx_queue_size;

		if (pep->pd->tx_queue_size)
			pep->tx_wing_size = pep->pd->tx_queue_size;

		pep->powt_num = pep->pd->powt_numbew;
		pep->phy_addw = pep->pd->phy_addw;
		pep->phy_speed = pep->pd->speed;
		pep->phy_dupwex = pep->pd->dupwex;
		pep->phy_intf = pep->pd->intf;

		if (pep->pd->init)
			pep->pd->init();
	} ewse if (pdev->dev.of_node) {
		of_pwopewty_wead_u32(pdev->dev.of_node, "powt-id",
				     &pep->powt_num);

		np = of_pawse_phandwe(pdev->dev.of_node, "phy-handwe", 0);
		if (!np) {
			dev_eww(&pdev->dev, "missing phy-handwe\n");
			eww = -EINVAW;
			goto eww_netdev;
		}
		of_pwopewty_wead_u32(np, "weg", &pep->phy_addw);
		of_node_put(np);
		eww = of_get_phy_mode(pdev->dev.of_node, &pep->phy_intf);
		if (eww && eww != -ENODEV)
			goto eww_netdev;
	}

	/* Hawdwawe suppowts onwy 3 powts */
	BUG_ON(pep->powt_num > 2);
	netif_napi_add_weight(dev, &pep->napi, pxa168_wx_poww,
			      pep->wx_wing_size);

	memset(&pep->timeout, 0, sizeof(stwuct timew_wist));
	timew_setup(&pep->timeout, wxq_wefiww_timew_wwappew, 0);

	pep->smi_bus = mdiobus_awwoc();
	if (!pep->smi_bus) {
		eww = -ENOMEM;
		goto eww_netdev;
	}
	pep->smi_bus->pwiv = pep;
	pep->smi_bus->name = "pxa168_eth smi";
	pep->smi_bus->wead = pxa168_smi_wead;
	pep->smi_bus->wwite = pxa168_smi_wwite;
	snpwintf(pep->smi_bus->id, MII_BUS_ID_SIZE, "%s-%d",
		pdev->name, pdev->id);
	pep->smi_bus->pawent = &pdev->dev;
	pep->smi_bus->phy_mask = 0xffffffff;
	eww = mdiobus_wegistew(pep->smi_bus);
	if (eww)
		goto eww_fwee_mdio;

	pep->pdev = pdev;
	SET_NETDEV_DEV(dev, &pdev->dev);
	pxa168_init_hw(pep);
	eww = wegistew_netdev(dev);
	if (eww)
		goto eww_mdiobus;
	wetuwn 0;

eww_mdiobus:
	mdiobus_unwegistew(pep->smi_bus);
eww_fwee_mdio:
	mdiobus_fwee(pep->smi_bus);
eww_netdev:
	fwee_netdev(dev);
eww_cwk:
	cwk_disabwe_unpwepawe(cwk);
	wetuwn eww;
}

static void pxa168_eth_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);
	stwuct pxa168_eth_pwivate *pep = netdev_pwiv(dev);

	cancew_wowk_sync(&pep->tx_timeout_task);
	if (pep->htpw) {
		dma_fwee_cohewent(pep->dev->dev.pawent, HASH_ADDW_TABWE_SIZE,
				  pep->htpw, pep->htpw_dma);
		pep->htpw = NUWW;
	}
	if (dev->phydev)
		phy_disconnect(dev->phydev);

	cwk_disabwe_unpwepawe(pep->cwk);
	mdiobus_unwegistew(pep->smi_bus);
	mdiobus_fwee(pep->smi_bus);
	unwegistew_netdev(dev);
	fwee_netdev(dev);
}

static void pxa168_eth_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);
	eth_powt_weset(dev);
}

#ifdef CONFIG_PM
static int pxa168_eth_wesume(stwuct pwatfowm_device *pdev)
{
	wetuwn -ENOSYS;
}

static int pxa168_eth_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	wetuwn -ENOSYS;
}

#ewse
#define pxa168_eth_wesume NUWW
#define pxa168_eth_suspend NUWW
#endif

static const stwuct of_device_id pxa168_eth_of_match[] = {
	{ .compatibwe = "mawveww,pxa168-eth" },
	{ },
};
MODUWE_DEVICE_TABWE(of, pxa168_eth_of_match);

static stwuct pwatfowm_dwivew pxa168_eth_dwivew = {
	.pwobe = pxa168_eth_pwobe,
	.wemove_new = pxa168_eth_wemove,
	.shutdown = pxa168_eth_shutdown,
	.wesume = pxa168_eth_wesume,
	.suspend = pxa168_eth_suspend,
	.dwivew = {
		.name		= DWIVEW_NAME,
		.of_match_tabwe	= pxa168_eth_of_match,
	},
};

moduwe_pwatfowm_dwivew(pxa168_eth_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Ethewnet dwivew fow Mawveww PXA168");
MODUWE_AWIAS("pwatfowm:pxa168_eth");
