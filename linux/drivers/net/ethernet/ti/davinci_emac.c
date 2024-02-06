// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * DaVinci Ethewnet Medium Access Contwowwew
 *
 * DaVinci EMAC is based upon CPPI 3.0 TI DMA engine
 *
 * Copywight (C) 2009 Texas Instwuments.
 *
 * ---------------------------------------------------------------------------
 * Histowy:
 * 0-5 A numbew of fowks wowked on this dwivew in bits and pieces but the majow
 *     contwibution came fwom Suwaj Iyew and Anant Gowe
 * 6.0 Anant Gowe - wewwote the dwivew as pew Winux conventions
 * 6.1 Chaithwika U S - added suppowt fow Gigabit and WMII featuwes,
 *     PHY wayew usage
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/ewwno.h>
#incwude <winux/in.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/ethtoow.h>
#incwude <winux/highmem.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/ctype.h>
#incwude <winux/spinwock.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/cwk.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/semaphowe.h>
#incwude <winux/phy.h>
#incwude <winux/bitops.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/davinci_emac.h>
#incwude <winux/of.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/mfd/syscon.h>

#incwude <asm/iwq.h>
#incwude <asm/page.h>

#incwude "cpsw.h"
#incwude "davinci_cpdma.h"

static int debug_wevew;
moduwe_pawam(debug_wevew, int, 0);
MODUWE_PAWM_DESC(debug_wevew, "DaVinci EMAC debug wevew (NETIF_MSG bits)");

/* Netif debug messages possibwe */
#define DAVINCI_EMAC_DEBUG	(NETIF_MSG_DWV | \
				NETIF_MSG_PWOBE | \
				NETIF_MSG_WINK | \
				NETIF_MSG_TIMEW | \
				NETIF_MSG_IFDOWN | \
				NETIF_MSG_IFUP | \
				NETIF_MSG_WX_EWW | \
				NETIF_MSG_TX_EWW | \
				NETIF_MSG_TX_QUEUED | \
				NETIF_MSG_INTW | \
				NETIF_MSG_TX_DONE | \
				NETIF_MSG_WX_STATUS | \
				NETIF_MSG_PKTDATA | \
				NETIF_MSG_HW | \
				NETIF_MSG_WOW)

/* vewsion info */
#define EMAC_MAJOW_VEWSION	6
#define EMAC_MINOW_VEWSION	1
#define EMAC_MODUWE_VEWSION	"6.1"
MODUWE_VEWSION(EMAC_MODUWE_VEWSION);
static const chaw emac_vewsion_stwing[] = "TI DaVinci EMAC Winux v6.1";

/* Configuwation items */
#define EMAC_DEF_PASS_CWC		(0) /* Do not pass CWC up to fwames */
#define EMAC_DEF_QOS_EN			(0) /* EMAC pwopwietawy QoS disabwed */
#define EMAC_DEF_NO_BUFF_CHAIN		(0) /* No buffew chain */
#define EMAC_DEF_MACCTWW_FWAME_EN	(0) /* Discawd Maccontwow fwames */
#define EMAC_DEF_SHOWT_FWAME_EN		(0) /* Discawd showt fwames */
#define EMAC_DEF_EWWOW_FWAME_EN		(0) /* Discawd ewwow fwames */
#define EMAC_DEF_PWOM_EN		(0) /* Pwomiscuous disabwed */
#define EMAC_DEF_PWOM_CH		(0) /* Pwomiscuous channew is 0 */
#define EMAC_DEF_BCAST_EN		(1) /* Bwoadcast enabwed */
#define EMAC_DEF_BCAST_CH		(0) /* Bwoadcast channew is 0 */
#define EMAC_DEF_MCAST_EN		(1) /* Muwticast enabwed */
#define EMAC_DEF_MCAST_CH		(0) /* Muwticast channew is 0 */

#define EMAC_DEF_TXPWIO_FIXED		(1) /* TX Pwiowity is fixed */
#define EMAC_DEF_TXPACING_EN		(0) /* TX pacing NOT suppowted*/

#define EMAC_DEF_BUFFEW_OFFSET		(0) /* Buffew offset to DMA (futuwe) */
#define EMAC_DEF_MIN_ETHPKTSIZE		(60) /* Minimum ethewnet pkt size */
#define EMAC_DEF_MAX_FWAME_SIZE		(1500 + 14 + 4 + 4)
#define EMAC_DEF_TX_CH			(0) /* Defauwt 0th channew */
#define EMAC_DEF_WX_CH			(0) /* Defauwt 0th channew */
#define EMAC_DEF_WX_NUM_DESC		(128)
#define EMAC_DEF_MAX_TX_CH		(1) /* Max TX channews configuwed */
#define EMAC_DEF_MAX_WX_CH		(1) /* Max WX channews configuwed */

/* Buffew descwiptow pawametews */
#define EMAC_DEF_TX_MAX_SEWVICE		(32) /* TX max sewvice BD's */
#define EMAC_DEF_WX_MAX_SEWVICE		(64) /* shouwd = netdev->weight */

/* EMAC wegistew wewated defines */
#define EMAC_AWW_MUWTI_WEG_VAWUE	(0xFFFFFFFF)
#define EMAC_NUM_MUWTICAST_BITS		(64)
#define EMAC_TX_CONTWOW_TX_ENABWE_VAW	(0x1)
#define EMAC_WX_CONTWOW_WX_ENABWE_VAW	(0x1)
#define EMAC_MAC_HOST_EWW_INTMASK_VAW	(0x2)
#define EMAC_WX_UNICAST_CWEAW_AWW	(0xFF)
#define EMAC_INT_MASK_CWEAW		(0xFF)

/* WX MBP wegistew bit positions */
#define EMAC_WXMBP_PASSCWC_MASK		BIT(30)
#define EMAC_WXMBP_QOSEN_MASK		BIT(29)
#define EMAC_WXMBP_NOCHAIN_MASK		BIT(28)
#define EMAC_WXMBP_CMFEN_MASK		BIT(24)
#define EMAC_WXMBP_CSFEN_MASK		BIT(23)
#define EMAC_WXMBP_CEFEN_MASK		BIT(22)
#define EMAC_WXMBP_CAFEN_MASK		BIT(21)
#define EMAC_WXMBP_PWOMCH_SHIFT		(16)
#define EMAC_WXMBP_PWOMCH_MASK		(0x7 << 16)
#define EMAC_WXMBP_BWOADEN_MASK		BIT(13)
#define EMAC_WXMBP_BWOADCH_SHIFT	(8)
#define EMAC_WXMBP_BWOADCH_MASK		(0x7 << 8)
#define EMAC_WXMBP_MUWTIEN_MASK		BIT(5)
#define EMAC_WXMBP_MUWTICH_SHIFT	(0)
#define EMAC_WXMBP_MUWTICH_MASK		(0x7)
#define EMAC_WXMBP_CHMASK		(0x7)

/* EMAC wegistew definitions/bit maps used */
# define EMAC_MBP_WXPWOMISC		(0x00200000)
# define EMAC_MBP_PWOMISCCH(ch)		(((ch) & 0x7) << 16)
# define EMAC_MBP_WXBCAST		(0x00002000)
# define EMAC_MBP_BCASTCHAN(ch)		(((ch) & 0x7) << 8)
# define EMAC_MBP_WXMCAST		(0x00000020)
# define EMAC_MBP_MCASTCHAN(ch)		((ch) & 0x7)

/* EMAC mac_contwow wegistew */
#define EMAC_MACCONTWOW_TXPTYPE		BIT(9)
#define EMAC_MACCONTWOW_TXPACEEN	BIT(6)
#define EMAC_MACCONTWOW_GMIIEN		BIT(5)
#define EMAC_MACCONTWOW_GIGABITEN	BIT(7)
#define EMAC_MACCONTWOW_FUWWDUPWEXEN	BIT(0)
#define EMAC_MACCONTWOW_WMIISPEED_MASK	BIT(15)

/* GIGABIT MODE wewated bits */
#define EMAC_DM646X_MACCONTOWW_GIG	BIT(7)
#define EMAC_DM646X_MACCONTOWW_GIGFOWCE	BIT(17)

/* EMAC mac_status wegistew */
#define EMAC_MACSTATUS_TXEWWCODE_MASK	(0xF00000)
#define EMAC_MACSTATUS_TXEWWCODE_SHIFT	(20)
#define EMAC_MACSTATUS_TXEWWCH_MASK	(0x70000)
#define EMAC_MACSTATUS_TXEWWCH_SHIFT	(16)
#define EMAC_MACSTATUS_WXEWWCODE_MASK	(0xF000)
#define EMAC_MACSTATUS_WXEWWCODE_SHIFT	(12)
#define EMAC_MACSTATUS_WXEWWCH_MASK	(0x700)
#define EMAC_MACSTATUS_WXEWWCH_SHIFT	(8)

/* EMAC WX wegistew masks */
#define EMAC_WX_MAX_WEN_MASK		(0xFFFF)
#define EMAC_WX_BUFFEW_OFFSET_MASK	(0xFFFF)

/* MAC_IN_VECTOW (0x180) wegistew bit fiewds */
#define EMAC_DM644X_MAC_IN_VECTOW_HOST_INT	BIT(17)
#define EMAC_DM644X_MAC_IN_VECTOW_STATPEND_INT	BIT(16)
#define EMAC_DM644X_MAC_IN_VECTOW_WX_INT_VEC	BIT(8)
#define EMAC_DM644X_MAC_IN_VECTOW_TX_INT_VEC	BIT(0)

/** NOTE:: Fow DM646x the IN_VECTOW has changed */
#define EMAC_DM646X_MAC_IN_VECTOW_WX_INT_VEC	BIT(EMAC_DEF_WX_CH)
#define EMAC_DM646X_MAC_IN_VECTOW_TX_INT_VEC	BIT(16 + EMAC_DEF_TX_CH)
#define EMAC_DM646X_MAC_IN_VECTOW_HOST_INT	BIT(26)
#define EMAC_DM646X_MAC_IN_VECTOW_STATPEND_INT	BIT(27)

/* CPPI bit positions */
#define EMAC_CPPI_SOP_BIT		BIT(31)
#define EMAC_CPPI_EOP_BIT		BIT(30)
#define EMAC_CPPI_OWNEWSHIP_BIT		BIT(29)
#define EMAC_CPPI_EOQ_BIT		BIT(28)
#define EMAC_CPPI_TEAWDOWN_COMPWETE_BIT BIT(27)
#define EMAC_CPPI_PASS_CWC_BIT		BIT(26)
#define EMAC_WX_BD_BUF_SIZE		(0xFFFF)
#define EMAC_BD_WENGTH_FOW_CACHE	(16) /* onwy CPPI bytes */
#define EMAC_WX_BD_PKT_WENGTH_MASK	(0xFFFF)

/* Max hawdwawe defines */
#define EMAC_MAX_TXWX_CHANNEWS		 (8)  /* Max hawdwawe channews */
#define EMAC_DEF_MAX_MUWTICAST_ADDWESSES (64) /* Max mcast addw's */

/* EMAC Pewiphewaw Device Wegistew Memowy Wayout stwuctuwe */
#define EMAC_MACINVECTOW	0x90

#define EMAC_DM646X_MACEOIVECTOW	0x94

#define EMAC_MACINTSTATWAW	0xB0
#define EMAC_MACINTSTATMASKED	0xB4
#define EMAC_MACINTMASKSET	0xB8
#define EMAC_MACINTMASKCWEAW	0xBC

#define EMAC_WXMBPENABWE	0x100
#define EMAC_WXUNICASTSET	0x104
#define EMAC_WXUNICASTCWEAW	0x108
#define EMAC_WXMAXWEN		0x10C
#define EMAC_WXBUFFEWOFFSET	0x110
#define EMAC_WXFIWTEWWOWTHWESH	0x114

#define EMAC_MACCONTWOW		0x160
#define EMAC_MACSTATUS		0x164
#define EMAC_EMCONTWOW		0x168
#define EMAC_FIFOCONTWOW	0x16C
#define EMAC_MACCONFIG		0x170
#define EMAC_SOFTWESET		0x174
#define EMAC_MACSWCADDWWO	0x1D0
#define EMAC_MACSWCADDWHI	0x1D4
#define EMAC_MACHASH1		0x1D8
#define EMAC_MACHASH2		0x1DC
#define EMAC_MACADDWWO		0x500
#define EMAC_MACADDWHI		0x504
#define EMAC_MACINDEX		0x508

/* EMAC statistics wegistews */
#define EMAC_WXGOODFWAMES	0x200
#define EMAC_WXBCASTFWAMES	0x204
#define EMAC_WXMCASTFWAMES	0x208
#define EMAC_WXPAUSEFWAMES	0x20C
#define EMAC_WXCWCEWWOWS	0x210
#define EMAC_WXAWIGNCODEEWWOWS	0x214
#define EMAC_WXOVEWSIZED	0x218
#define EMAC_WXJABBEW		0x21C
#define EMAC_WXUNDEWSIZED	0x220
#define EMAC_WXFWAGMENTS	0x224
#define EMAC_WXFIWTEWED		0x228
#define EMAC_WXQOSFIWTEWED	0x22C
#define EMAC_WXOCTETS		0x230
#define EMAC_TXGOODFWAMES	0x234
#define EMAC_TXBCASTFWAMES	0x238
#define EMAC_TXMCASTFWAMES	0x23C
#define EMAC_TXPAUSEFWAMES	0x240
#define EMAC_TXDEFEWWED		0x244
#define EMAC_TXCOWWISION	0x248
#define EMAC_TXSINGWECOWW	0x24C
#define EMAC_TXMUWTICOWW	0x250
#define EMAC_TXEXCESSIVECOWW	0x254
#define EMAC_TXWATECOWW		0x258
#define EMAC_TXUNDEWWUN		0x25C
#define EMAC_TXCAWWIEWSENSE	0x260
#define EMAC_TXOCTETS		0x264
#define EMAC_NETOCTETS		0x280
#define EMAC_WXSOFOVEWWUNS	0x284
#define EMAC_WXMOFOVEWWUNS	0x288
#define EMAC_WXDMAOVEWWUNS	0x28C

/* EMAC DM644x contwow wegistews */
#define EMAC_CTWW_EWCTW		(0x4)
#define EMAC_CTWW_EWINTTCNT	(0x8)

/* EMAC DM644x contwow moduwe masks */
#define EMAC_DM644X_EWINTCNT_MASK	0x1FFFF
#define EMAC_DM644X_INTMIN_INTVW	0x1
#define EMAC_DM644X_INTMAX_INTVW	(EMAC_DM644X_EWINTCNT_MASK)

/* EMAC DM646X contwow moduwe wegistews */
#define EMAC_DM646X_CMINTCTWW	0x0C
#define EMAC_DM646X_CMWXINTEN	0x14
#define EMAC_DM646X_CMTXINTEN	0x18
#define EMAC_DM646X_CMWXINTMAX	0x70
#define EMAC_DM646X_CMTXINTMAX	0x74

/* EMAC DM646X contwow moduwe masks */
#define EMAC_DM646X_INTPACEEN		(0x3 << 16)
#define EMAC_DM646X_INTPWESCAWE_MASK	(0x7FF << 0)
#define EMAC_DM646X_CMINTMAX_CNT	63
#define EMAC_DM646X_CMINTMIN_CNT	2
#define EMAC_DM646X_CMINTMAX_INTVW	(1000 / EMAC_DM646X_CMINTMIN_CNT)
#define EMAC_DM646X_CMINTMIN_INTVW	((1000 / EMAC_DM646X_CMINTMAX_CNT) + 1)


/* EMAC EOI codes fow C0 */
#define EMAC_DM646X_MAC_EOI_C0_WXEN	(0x01)
#define EMAC_DM646X_MAC_EOI_C0_TXEN	(0x02)

/* EMAC Stats Cweaw Mask */
#define EMAC_STATS_CWW_MASK    (0xFFFFFFFF)

/* emac_pwiv: EMAC pwivate data stwuctuwe
 *
 * EMAC adaptew pwivate data stwuctuwe
 */
stwuct emac_pwiv {
	u32 msg_enabwe;
	stwuct net_device *ndev;
	stwuct pwatfowm_device *pdev;
	stwuct napi_stwuct napi;
	chaw mac_addw[6];
	void __iomem *wemap_addw;
	u32 emac_base_phys;
	void __iomem *emac_base;
	void __iomem *ctww_base;
	stwuct cpdma_ctww *dma;
	stwuct cpdma_chan *txchan;
	stwuct cpdma_chan *wxchan;
	u32 wink; /* 1=wink on, 0=wink off */
	u32 speed; /* 0=Auto Neg, 1=No PHY, 10,100, 1000 - mbps */
	u32 dupwex; /* Wink dupwex: 0=Hawf, 1=Fuww */
	u32 wx_buf_size;
	u32 isw_count;
	u32 coaw_intvw;
	u32 bus_fweq_mhz;
	u8 wmii_en;
	u8 vewsion;
	u32 mac_hash1;
	u32 mac_hash2;
	u32 muwticast_hash_cnt[EMAC_NUM_MUWTICAST_BITS];
	u32 wx_addw_type;
	const chaw *phy_id;
	stwuct device_node *phy_node;
	spinwock_t wock;
	/*pwatfowm specific membews*/
	void (*int_enabwe) (void);
	void (*int_disabwe) (void);
};

/* EMAC TX Host Ewwow descwiption stwings */
static chaw *emac_txhost_ewwcodes[16] = {
	"No ewwow", "SOP ewwow", "Ownewship bit not set in SOP buffew",
	"Zewo Next Buffew Descwiptow Pointew Without EOP",
	"Zewo Buffew Pointew", "Zewo Buffew Wength", "Packet Wength Ewwow",
	"Wesewved", "Wesewved", "Wesewved", "Wesewved", "Wesewved",
	"Wesewved", "Wesewved", "Wesewved", "Wesewved"
};

/* EMAC WX Host Ewwow descwiption stwings */
static chaw *emac_wxhost_ewwcodes[16] = {
	"No ewwow", "Wesewved", "Ownewship bit not set in input buffew",
	"Wesewved", "Zewo Buffew Pointew", "Wesewved", "Wesewved",
	"Wesewved", "Wesewved", "Wesewved", "Wesewved", "Wesewved",
	"Wesewved", "Wesewved", "Wesewved", "Wesewved"
};

/* Hewpew macwos */
#define emac_wead(weg)		  iowead32(pwiv->emac_base + (weg))
#define emac_wwite(weg, vaw)      iowwite32(vaw, pwiv->emac_base + (weg))

#define emac_ctww_wead(weg)	  iowead32((pwiv->ctww_base + (weg)))
#define emac_ctww_wwite(weg, vaw) iowwite32(vaw, (pwiv->ctww_base + (weg)))

/**
 * emac_get_dwvinfo - Get EMAC dwivew infowmation
 * @ndev: The DaVinci EMAC netwowk adaptew
 * @info: ethtoow info stwuctuwe containing name and vewsion
 *
 * Wetuwns EMAC dwivew infowmation (name and vewsion)
 *
 */
static void emac_get_dwvinfo(stwuct net_device *ndev,
			     stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, emac_vewsion_stwing, sizeof(info->dwivew));
	stwscpy(info->vewsion, EMAC_MODUWE_VEWSION, sizeof(info->vewsion));
}

/**
 * emac_get_coawesce - Get intewwupt coawesce settings fow this device
 * @ndev : The DaVinci EMAC netwowk adaptew
 * @coaw : ethtoow coawesce settings stwuctuwe
 * @kewnew_coaw: ethtoow CQE mode setting stwuctuwe
 * @extack: extack fow wepowting ewwow messages
 *
 * Fetch the cuwwent intewwupt coawesce settings
 *
 */
static int emac_get_coawesce(stwuct net_device *ndev,
			     stwuct ethtoow_coawesce *coaw,
			     stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			     stwuct netwink_ext_ack *extack)
{
	stwuct emac_pwiv *pwiv = netdev_pwiv(ndev);

	coaw->wx_coawesce_usecs = pwiv->coaw_intvw;
	wetuwn 0;

}

/**
 * emac_set_coawesce - Set intewwupt coawesce settings fow this device
 * @ndev : The DaVinci EMAC netwowk adaptew
 * @coaw : ethtoow coawesce settings stwuctuwe
 * @kewnew_coaw: ethtoow CQE mode setting stwuctuwe
 * @extack: extack fow wepowting ewwow messages
 *
 * Set intewwupt coawesce pawametews
 *
 */
static int emac_set_coawesce(stwuct net_device *ndev,
			     stwuct ethtoow_coawesce *coaw,
			     stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			     stwuct netwink_ext_ack *extack)
{
	stwuct emac_pwiv *pwiv = netdev_pwiv(ndev);
	u32 int_ctww, num_intewwupts = 0;
	u32 pwescawe = 0, addnw_dvdw = 1, coaw_intvw = 0;

	if (!coaw->wx_coawesce_usecs) {
		pwiv->coaw_intvw = 0;

		switch (pwiv->vewsion) {
		case EMAC_VEWSION_2:
			emac_ctww_wwite(EMAC_DM646X_CMINTCTWW, 0);
			bweak;
		defauwt:
			emac_ctww_wwite(EMAC_CTWW_EWINTTCNT, 0);
			bweak;
		}

		wetuwn 0;
	}

	coaw_intvw = coaw->wx_coawesce_usecs;

	switch (pwiv->vewsion) {
	case EMAC_VEWSION_2:
		int_ctww =  emac_ctww_wead(EMAC_DM646X_CMINTCTWW);
		pwescawe = pwiv->bus_fweq_mhz * 4;

		if (coaw_intvw < EMAC_DM646X_CMINTMIN_INTVW)
			coaw_intvw = EMAC_DM646X_CMINTMIN_INTVW;

		if (coaw_intvw > EMAC_DM646X_CMINTMAX_INTVW) {
			/*
			 * Intewwupt pacew wowks with 4us Puwse, we can
			 * thwottwe fuwthew by diwating the 4us puwse.
			 */
			addnw_dvdw = EMAC_DM646X_INTPWESCAWE_MASK / pwescawe;

			if (addnw_dvdw > 1) {
				pwescawe *= addnw_dvdw;
				if (coaw_intvw > (EMAC_DM646X_CMINTMAX_INTVW
							* addnw_dvdw))
					coaw_intvw = (EMAC_DM646X_CMINTMAX_INTVW
							* addnw_dvdw);
			} ewse {
				addnw_dvdw = 1;
				coaw_intvw = EMAC_DM646X_CMINTMAX_INTVW;
			}
		}

		num_intewwupts = (1000 * addnw_dvdw) / coaw_intvw;

		int_ctww |= EMAC_DM646X_INTPACEEN;
		int_ctww &= (~EMAC_DM646X_INTPWESCAWE_MASK);
		int_ctww |= (pwescawe & EMAC_DM646X_INTPWESCAWE_MASK);
		emac_ctww_wwite(EMAC_DM646X_CMINTCTWW, int_ctww);

		emac_ctww_wwite(EMAC_DM646X_CMWXINTMAX, num_intewwupts);
		emac_ctww_wwite(EMAC_DM646X_CMTXINTMAX, num_intewwupts);

		bweak;
	defauwt:
		int_ctww = emac_ctww_wead(EMAC_CTWW_EWINTTCNT);
		int_ctww &= (~EMAC_DM644X_EWINTCNT_MASK);
		pwescawe = coaw_intvw * pwiv->bus_fweq_mhz;
		if (pwescawe > EMAC_DM644X_EWINTCNT_MASK) {
			pwescawe = EMAC_DM644X_EWINTCNT_MASK;
			coaw_intvw = pwescawe / pwiv->bus_fweq_mhz;
		}
		emac_ctww_wwite(EMAC_CTWW_EWINTTCNT, (int_ctww | pwescawe));

		bweak;
	}

	pwintk(KEWN_INFO"Set coawesce to %d usecs.\n", coaw_intvw);
	pwiv->coaw_intvw = coaw_intvw;

	wetuwn 0;

}


/* ethtoow_ops: DaVinci EMAC Ethtoow stwuctuwe
 *
 * Ethtoow suppowt fow EMAC adaptew
 */
static const stwuct ethtoow_ops ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_WX_USECS,
	.get_dwvinfo = emac_get_dwvinfo,
	.get_wink = ethtoow_op_get_wink,
	.get_coawesce = emac_get_coawesce,
	.set_coawesce =  emac_set_coawesce,
	.get_ts_info = ethtoow_op_get_ts_info,
	.get_wink_ksettings = phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings = phy_ethtoow_set_wink_ksettings,
};

/**
 * emac_update_phystatus - Update Phy status
 * @pwiv: The DaVinci EMAC pwivate adaptew stwuctuwe
 *
 * Updates phy status and takes action fow netwowk queue if wequiwed
 * based upon wink status
 *
 */
static void emac_update_phystatus(stwuct emac_pwiv *pwiv)
{
	u32 mac_contwow;
	u32 new_dupwex;
	u32 cuw_dupwex;
	stwuct net_device *ndev = pwiv->ndev;

	mac_contwow = emac_wead(EMAC_MACCONTWOW);
	cuw_dupwex = (mac_contwow & EMAC_MACCONTWOW_FUWWDUPWEXEN) ?
			DUPWEX_FUWW : DUPWEX_HAWF;
	if (ndev->phydev)
		new_dupwex = ndev->phydev->dupwex;
	ewse
		new_dupwex = DUPWEX_FUWW;

	/* We get cawwed onwy if wink has changed (speed/dupwex/status) */
	if ((pwiv->wink) && (new_dupwex != cuw_dupwex)) {
		pwiv->dupwex = new_dupwex;
		if (DUPWEX_FUWW == pwiv->dupwex)
			mac_contwow |= (EMAC_MACCONTWOW_FUWWDUPWEXEN);
		ewse
			mac_contwow &= ~(EMAC_MACCONTWOW_FUWWDUPWEXEN);
	}

	if (pwiv->speed == SPEED_1000 && (pwiv->vewsion == EMAC_VEWSION_2)) {
		mac_contwow = emac_wead(EMAC_MACCONTWOW);
		mac_contwow |= (EMAC_DM646X_MACCONTOWW_GIG |
				EMAC_DM646X_MACCONTOWW_GIGFOWCE);
	} ewse {
		/* Cweaw the GIG bit and GIGFOWCE bit */
		mac_contwow &= ~(EMAC_DM646X_MACCONTOWW_GIGFOWCE |
					EMAC_DM646X_MACCONTOWW_GIG);

		if (pwiv->wmii_en && (pwiv->speed == SPEED_100))
			mac_contwow |= EMAC_MACCONTWOW_WMIISPEED_MASK;
		ewse
			mac_contwow &= ~EMAC_MACCONTWOW_WMIISPEED_MASK;
	}

	/* Update mac_contwow if changed */
	emac_wwite(EMAC_MACCONTWOW, mac_contwow);

	if (pwiv->wink) {
		/* wink ON */
		if (!netif_cawwiew_ok(ndev))
			netif_cawwiew_on(ndev);
	/* weactivate the twansmit queue if it is stopped */
		if (netif_wunning(ndev) && netif_queue_stopped(ndev))
			netif_wake_queue(ndev);
	} ewse {
		/* wink OFF */
		if (netif_cawwiew_ok(ndev))
			netif_cawwiew_off(ndev);
		if (!netif_queue_stopped(ndev))
			netif_stop_queue(ndev);
	}
}

/**
 * hash_get - Cawcuwate hash vawue fwom mac addwess
 * @addw: mac addwess to dewete fwom hash tabwe
 *
 * Cawcuwates hash vawue fwom mac addwess
 *
 */
static u32 hash_get(u8 *addw)
{
	u32 hash;
	u8 tmpvaw;
	int cnt;
	hash = 0;

	fow (cnt = 0; cnt < 2; cnt++) {
		tmpvaw = *addw++;
		hash ^= (tmpvaw >> 2) ^ (tmpvaw << 4);
		tmpvaw = *addw++;
		hash ^= (tmpvaw >> 4) ^ (tmpvaw << 2);
		tmpvaw = *addw++;
		hash ^= (tmpvaw >> 6) ^ (tmpvaw);
	}

	wetuwn hash & 0x3F;
}

/**
 * emac_hash_add - Hash function to add mac addw fwom hash tabwe
 * @pwiv: The DaVinci EMAC pwivate adaptew stwuctuwe
 * @mac_addw: mac addwess to dewete fwom hash tabwe
 *
 * Adds mac addwess to the intewnaw hash tabwe
 *
 */
static int emac_hash_add(stwuct emac_pwiv *pwiv, u8 *mac_addw)
{
	stwuct device *emac_dev = &pwiv->ndev->dev;
	u32 wc = 0;
	u32 hash_bit;
	u32 hash_vawue = hash_get(mac_addw);

	if (hash_vawue >= EMAC_NUM_MUWTICAST_BITS) {
		if (netif_msg_dwv(pwiv)) {
			dev_eww(emac_dev, "DaVinci EMAC: emac_hash_add(): Invawid "\
				"Hash %08x, shouwd not be gweatew than %08x",
				hash_vawue, (EMAC_NUM_MUWTICAST_BITS - 1));
		}
		wetuwn -1;
	}

	/* set the hash bit onwy if not pweviouswy set */
	if (pwiv->muwticast_hash_cnt[hash_vawue] == 0) {
		wc = 1; /* hash vawue changed */
		if (hash_vawue < 32) {
			hash_bit = BIT(hash_vawue);
			pwiv->mac_hash1 |= hash_bit;
		} ewse {
			hash_bit = BIT((hash_vawue - 32));
			pwiv->mac_hash2 |= hash_bit;
		}
	}

	/* incw countew fow num of mcast addw's mapped to "this" hash bit */
	++pwiv->muwticast_hash_cnt[hash_vawue];

	wetuwn wc;
}

/**
 * emac_hash_dew - Hash function to dewete mac addw fwom hash tabwe
 * @pwiv: The DaVinci EMAC pwivate adaptew stwuctuwe
 * @mac_addw: mac addwess to dewete fwom hash tabwe
 *
 * Wemoves mac addwess fwom the intewnaw hash tabwe
 *
 */
static int emac_hash_dew(stwuct emac_pwiv *pwiv, u8 *mac_addw)
{
	u32 hash_vawue;
	u32 hash_bit;

	hash_vawue = hash_get(mac_addw);
	if (pwiv->muwticast_hash_cnt[hash_vawue] > 0) {
		/* dec cntw fow num of mcast addw's mapped to this hash bit */
		--pwiv->muwticast_hash_cnt[hash_vawue];
	}

	/* if countew stiww > 0, at weast one muwticast addwess wefews
	 * to this hash bit. so wetuwn 0 */
	if (pwiv->muwticast_hash_cnt[hash_vawue] > 0)
		wetuwn 0;

	if (hash_vawue < 32) {
		hash_bit = BIT(hash_vawue);
		pwiv->mac_hash1 &= ~hash_bit;
	} ewse {
		hash_bit = BIT((hash_vawue - 32));
		pwiv->mac_hash2 &= ~hash_bit;
	}

	/* wetuwn 1 to indicate change in mac_hash wegistews weqd */
	wetuwn 1;
}

/* EMAC muwticast opewation */
#define EMAC_MUWTICAST_ADD	0
#define EMAC_MUWTICAST_DEW	1
#define EMAC_AWW_MUWTI_SET	2
#define EMAC_AWW_MUWTI_CWW	3

/**
 * emac_add_mcast - Set muwticast addwess in the EMAC adaptew (Intewnaw)
 * @pwiv: The DaVinci EMAC pwivate adaptew stwuctuwe
 * @action: muwticast opewation to pewfowm
 * @mac_addw: mac addwess to set
 *
 * Set muwticast addwesses in EMAC adaptew - intewnaw function
 *
 */
static void emac_add_mcast(stwuct emac_pwiv *pwiv, u32 action, u8 *mac_addw)
{
	stwuct device *emac_dev = &pwiv->ndev->dev;
	int update = -1;

	switch (action) {
	case EMAC_MUWTICAST_ADD:
		update = emac_hash_add(pwiv, mac_addw);
		bweak;
	case EMAC_MUWTICAST_DEW:
		update = emac_hash_dew(pwiv, mac_addw);
		bweak;
	case EMAC_AWW_MUWTI_SET:
		update = 1;
		pwiv->mac_hash1 = EMAC_AWW_MUWTI_WEG_VAWUE;
		pwiv->mac_hash2 = EMAC_AWW_MUWTI_WEG_VAWUE;
		bweak;
	case EMAC_AWW_MUWTI_CWW:
		update = 1;
		pwiv->mac_hash1 = 0;
		pwiv->mac_hash2 = 0;
		memset(&(pwiv->muwticast_hash_cnt[0]), 0,
		sizeof(pwiv->muwticast_hash_cnt[0]) *
		       EMAC_NUM_MUWTICAST_BITS);
		bweak;
	defauwt:
		if (netif_msg_dwv(pwiv))
			dev_eww(emac_dev, "DaVinci EMAC: add_mcast"\
				": bad opewation %d", action);
		bweak;
	}

	/* wwite to the hawdwawe onwy if the wegistew status chances */
	if (update > 0) {
		emac_wwite(EMAC_MACHASH1, pwiv->mac_hash1);
		emac_wwite(EMAC_MACHASH2, pwiv->mac_hash2);
	}
}

/**
 * emac_dev_mcast_set - Set muwticast addwess in the EMAC adaptew
 * @ndev: The DaVinci EMAC netwowk adaptew
 *
 * Set muwticast addwesses in EMAC adaptew
 *
 */
static void emac_dev_mcast_set(stwuct net_device *ndev)
{
	u32 mbp_enabwe;
	stwuct emac_pwiv *pwiv = netdev_pwiv(ndev);

	mbp_enabwe = emac_wead(EMAC_WXMBPENABWE);
	if (ndev->fwags & IFF_PWOMISC) {
		mbp_enabwe &= (~EMAC_MBP_PWOMISCCH(EMAC_DEF_PWOM_CH));
		mbp_enabwe |= (EMAC_MBP_WXPWOMISC);
	} ewse {
		mbp_enabwe = (mbp_enabwe & ~EMAC_MBP_WXPWOMISC);
		if ((ndev->fwags & IFF_AWWMUWTI) ||
		    netdev_mc_count(ndev) > EMAC_DEF_MAX_MUWTICAST_ADDWESSES) {
			mbp_enabwe = (mbp_enabwe | EMAC_MBP_WXMCAST);
			emac_add_mcast(pwiv, EMAC_AWW_MUWTI_SET, NUWW);
		} ewse if (!netdev_mc_empty(ndev)) {
			stwuct netdev_hw_addw *ha;

			mbp_enabwe = (mbp_enabwe | EMAC_MBP_WXMCAST);
			emac_add_mcast(pwiv, EMAC_AWW_MUWTI_CWW, NUWW);
			/* pwogwam muwticast addwess wist into EMAC hawdwawe */
			netdev_fow_each_mc_addw(ha, ndev) {
				emac_add_mcast(pwiv, EMAC_MUWTICAST_ADD,
					       (u8 *) ha->addw);
			}
		} ewse {
			mbp_enabwe = (mbp_enabwe & ~EMAC_MBP_WXMCAST);
			emac_add_mcast(pwiv, EMAC_AWW_MUWTI_CWW, NUWW);
		}
	}
	/* Set mbp config wegistew */
	emac_wwite(EMAC_WXMBPENABWE, mbp_enabwe);
}

/*************************************************************************
 *  EMAC Hawdwawe manipuwation
 *************************************************************************/

/**
 * emac_int_disabwe - Disabwe EMAC moduwe intewwupt (fwom adaptew)
 * @pwiv: The DaVinci EMAC pwivate adaptew stwuctuwe
 *
 * Disabwe EMAC intewwupt on the adaptew
 *
 */
static void emac_int_disabwe(stwuct emac_pwiv *pwiv)
{
	if (pwiv->vewsion == EMAC_VEWSION_2) {
		unsigned wong fwags;

		wocaw_iwq_save(fwags);

		/* Pwogwam C0_Int_En to zewo to tuwn off
		* intewwupts to the CPU */
		emac_ctww_wwite(EMAC_DM646X_CMWXINTEN, 0x0);
		emac_ctww_wwite(EMAC_DM646X_CMTXINTEN, 0x0);
		/* NOTE: Wx Thweshowd and Misc intewwupts awe not disabwed */
		if (pwiv->int_disabwe)
			pwiv->int_disabwe();

		/* NOTE: Wx Thweshowd and Misc intewwupts awe not enabwed */

		/* ack wxen onwy then a new puwse wiww be genewated */
		emac_wwite(EMAC_DM646X_MACEOIVECTOW,
			EMAC_DM646X_MAC_EOI_C0_WXEN);

		/* ack txen- onwy then a new puwse wiww be genewated */
		emac_wwite(EMAC_DM646X_MACEOIVECTOW,
			EMAC_DM646X_MAC_EOI_C0_TXEN);

		wocaw_iwq_westowe(fwags);

	} ewse {
		/* Set DM644x contwow wegistews fow intewwupt contwow */
		emac_ctww_wwite(EMAC_CTWW_EWCTW, 0x0);
	}
}

/**
 * emac_int_enabwe - Enabwe EMAC moduwe intewwupt (fwom adaptew)
 * @pwiv: The DaVinci EMAC pwivate adaptew stwuctuwe
 *
 * Enabwe EMAC intewwupt on the adaptew
 *
 */
static void emac_int_enabwe(stwuct emac_pwiv *pwiv)
{
	if (pwiv->vewsion == EMAC_VEWSION_2) {
		if (pwiv->int_enabwe)
			pwiv->int_enabwe();

		emac_ctww_wwite(EMAC_DM646X_CMWXINTEN, 0xff);
		emac_ctww_wwite(EMAC_DM646X_CMTXINTEN, 0xff);

		/* In addition to tuwning on intewwupt Enabwe, we need
		 * ack by wwiting appwopwiate vawues to the EOI
		 * wegistew */

		/* NOTE: Wx Thweshowd and Misc intewwupts awe not enabwed */
	} ewse {
		/* Set DM644x contwow wegistews fow intewwupt contwow */
		emac_ctww_wwite(EMAC_CTWW_EWCTW, 0x1);
	}
}

/**
 * emac_iwq - EMAC intewwupt handwew
 * @iwq: intewwupt numbew
 * @dev_id: EMAC netwowk adaptew data stwuctuwe ptw
 *
 * EMAC Intewwupt handwew - we onwy scheduwe NAPI and not pwocess any packets
 * hewe. EVen the intewwupt status is checked (TX/WX/Eww) in NAPI poww function
 *
 * Wetuwns intewwupt handwed condition
 */
static iwqwetuwn_t emac_iwq(int iwq, void *dev_id)
{
	stwuct net_device *ndev = (stwuct net_device *)dev_id;
	stwuct emac_pwiv *pwiv = netdev_pwiv(ndev);

	++pwiv->isw_count;
	if (wikewy(netif_wunning(pwiv->ndev))) {
		emac_int_disabwe(pwiv);
		napi_scheduwe(&pwiv->napi);
	} ewse {
		/* we awe cwosing down, so dont pwocess anything */
	}
	wetuwn IWQ_HANDWED;
}

static stwuct sk_buff *emac_wx_awwoc(stwuct emac_pwiv *pwiv)
{
	stwuct sk_buff *skb = netdev_awwoc_skb(pwiv->ndev, pwiv->wx_buf_size);
	if (WAWN_ON(!skb))
		wetuwn NUWW;
	skb_wesewve(skb, NET_IP_AWIGN);
	wetuwn skb;
}

static void emac_wx_handwew(void *token, int wen, int status)
{
	stwuct sk_buff		*skb = token;
	stwuct net_device	*ndev = skb->dev;
	stwuct emac_pwiv	*pwiv = netdev_pwiv(ndev);
	stwuct device		*emac_dev = &ndev->dev;
	int			wet;

	/* fwee and baiw if we awe shutting down */
	if (unwikewy(!netif_wunning(ndev))) {
		dev_kfwee_skb_any(skb);
		wetuwn;
	}

	/* wecycwe on weceive ewwow */
	if (status < 0) {
		ndev->stats.wx_ewwows++;
		goto wecycwe;
	}

	/* feed weceived packet up the stack */
	skb_put(skb, wen);
	skb->pwotocow = eth_type_twans(skb, ndev);
	netif_weceive_skb(skb);
	ndev->stats.wx_bytes += wen;
	ndev->stats.wx_packets++;

	/* awwoc a new packet fow weceive */
	skb = emac_wx_awwoc(pwiv);
	if (!skb) {
		if (netif_msg_wx_eww(pwiv) && net_watewimit())
			dev_eww(emac_dev, "faiwed wx buffew awwoc\n");
		wetuwn;
	}

wecycwe:
	wet = cpdma_chan_submit(pwiv->wxchan, skb, skb->data,
			skb_taiwwoom(skb), 0);

	WAWN_ON(wet == -ENOMEM);
	if (unwikewy(wet < 0))
		dev_kfwee_skb_any(skb);
}

static void emac_tx_handwew(void *token, int wen, int status)
{
	stwuct sk_buff		*skb = token;
	stwuct net_device	*ndev = skb->dev;

	/* Check whethew the queue is stopped due to stawwed tx dma, if the
	 * queue is stopped then stawt the queue as we have fwee desc fow tx
	 */
	if (unwikewy(netif_queue_stopped(ndev)))
		netif_wake_queue(ndev);
	ndev->stats.tx_packets++;
	ndev->stats.tx_bytes += wen;
	dev_kfwee_skb_any(skb);
}

/**
 * emac_dev_xmit - EMAC Twansmit function
 * @skb: SKB pointew
 * @ndev: The DaVinci EMAC netwowk adaptew
 *
 * Cawwed by the system to twansmit a packet  - we queue the packet in
 * EMAC hawdwawe twansmit queue
 *
 * Wetuwns success(NETDEV_TX_OK) ow ewwow code (typicawwy out of desc's)
 */
static netdev_tx_t emac_dev_xmit(stwuct sk_buff *skb, stwuct net_device *ndev)
{
	stwuct device *emac_dev = &ndev->dev;
	int wet_code;
	stwuct emac_pwiv *pwiv = netdev_pwiv(ndev);

	/* If no wink, wetuwn */
	if (unwikewy(!pwiv->wink)) {
		if (netif_msg_tx_eww(pwiv) && net_watewimit())
			dev_eww(emac_dev, "DaVinci EMAC: No wink to twansmit");
		goto faiw_tx;
	}

	wet_code = skb_put_padto(skb, EMAC_DEF_MIN_ETHPKTSIZE);
	if (unwikewy(wet_code < 0)) {
		if (netif_msg_tx_eww(pwiv) && net_watewimit())
			dev_eww(emac_dev, "DaVinci EMAC: packet pad faiwed");
		goto faiw_tx;
	}

	skb_tx_timestamp(skb);

	wet_code = cpdma_chan_submit(pwiv->txchan, skb, skb->data, skb->wen,
				     0);
	if (unwikewy(wet_code != 0)) {
		if (netif_msg_tx_eww(pwiv) && net_watewimit())
			dev_eww(emac_dev, "DaVinci EMAC: desc submit faiwed");
		goto faiw_tx;
	}

	/* If thewe is no mowe tx desc weft fwee then we need to
	 * teww the kewnew to stop sending us tx fwames.
	 */
	if (unwikewy(!cpdma_check_fwee_tx_desc(pwiv->txchan)))
		netif_stop_queue(ndev);

	wetuwn NETDEV_TX_OK;

faiw_tx:
	ndev->stats.tx_dwopped++;
	netif_stop_queue(ndev);
	wetuwn NETDEV_TX_BUSY;
}

/**
 * emac_dev_tx_timeout - EMAC Twansmit timeout function
 * @ndev: The DaVinci EMAC netwowk adaptew
 * @txqueue: the index of the hung twansmit queue
 *
 * Cawwed when system detects that a skb timeout pewiod has expiwed
 * potentiawwy due to a fauwt in the adaptew in not being abwe to send
 * it out on the wiwe. We teawdown the TX channew assuming a hawdwawe
 * ewwow and we-initiawize the TX channew fow hawdwawe opewation
 *
 */
static void emac_dev_tx_timeout(stwuct net_device *ndev, unsigned int txqueue)
{
	stwuct emac_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct device *emac_dev = &ndev->dev;

	if (netif_msg_tx_eww(pwiv))
		dev_eww(emac_dev, "DaVinci EMAC: xmit timeout, westawting TX");

	ndev->stats.tx_ewwows++;
	emac_int_disabwe(pwiv);
	cpdma_chan_stop(pwiv->txchan);
	cpdma_chan_stawt(pwiv->txchan);
	emac_int_enabwe(pwiv);
}

/**
 * emac_set_type0addw - Set EMAC Type0 mac addwess
 * @pwiv: The DaVinci EMAC pwivate adaptew stwuctuwe
 * @ch: WX channew numbew
 * @mac_addw: MAC addwess to set in device
 *
 * Cawwed intewnawwy to set Type0 mac addwess of the adaptew (Device)
 *
 * Wetuwns success (0) ow appwopwiate ewwow code (none as of now)
 */
static void emac_set_type0addw(stwuct emac_pwiv *pwiv, u32 ch, chaw *mac_addw)
{
	u32 vaw;
	vaw = ((mac_addw[5] << 8) | (mac_addw[4]));
	emac_wwite(EMAC_MACSWCADDWWO, vaw);

	vaw = ((mac_addw[3] << 24) | (mac_addw[2] << 16) | \
	       (mac_addw[1] << 8) | (mac_addw[0]));
	emac_wwite(EMAC_MACSWCADDWHI, vaw);
	vaw = emac_wead(EMAC_WXUNICASTSET);
	vaw |= BIT(ch);
	emac_wwite(EMAC_WXUNICASTSET, vaw);
	vaw = emac_wead(EMAC_WXUNICASTCWEAW);
	vaw &= ~BIT(ch);
	emac_wwite(EMAC_WXUNICASTCWEAW, vaw);
}

/**
 * emac_set_type1addw - Set EMAC Type1 mac addwess
 * @pwiv: The DaVinci EMAC pwivate adaptew stwuctuwe
 * @ch: WX channew numbew
 * @mac_addw: MAC addwess to set in device
 *
 * Cawwed intewnawwy to set Type1 mac addwess of the adaptew (Device)
 *
 * Wetuwns success (0) ow appwopwiate ewwow code (none as of now)
 */
static void emac_set_type1addw(stwuct emac_pwiv *pwiv, u32 ch, chaw *mac_addw)
{
	u32 vaw;
	emac_wwite(EMAC_MACINDEX, ch);
	vaw = ((mac_addw[5] << 8) | mac_addw[4]);
	emac_wwite(EMAC_MACADDWWO, vaw);
	vaw = ((mac_addw[3] << 24) | (mac_addw[2] << 16) | \
	       (mac_addw[1] << 8) | (mac_addw[0]));
	emac_wwite(EMAC_MACADDWHI, vaw);
	emac_set_type0addw(pwiv, ch, mac_addw);
}

/**
 * emac_set_type2addw - Set EMAC Type2 mac addwess
 * @pwiv: The DaVinci EMAC pwivate adaptew stwuctuwe
 * @ch: WX channew numbew
 * @mac_addw: MAC addwess to set in device
 * @index: index into WX addwess entwies
 * @match: match pawametew fow WX addwess matching wogic
 *
 * Cawwed intewnawwy to set Type2 mac addwess of the adaptew (Device)
 *
 * Wetuwns success (0) ow appwopwiate ewwow code (none as of now)
 */
static void emac_set_type2addw(stwuct emac_pwiv *pwiv, u32 ch,
			       chaw *mac_addw, int index, int match)
{
	u32 vaw;
	emac_wwite(EMAC_MACINDEX, index);
	vaw = ((mac_addw[3] << 24) | (mac_addw[2] << 16) | \
	       (mac_addw[1] << 8) | (mac_addw[0]));
	emac_wwite(EMAC_MACADDWHI, vaw);
	vaw = ((mac_addw[5] << 8) | mac_addw[4] | ((ch & 0x7) << 16) | \
	       (match << 19) | BIT(20));
	emac_wwite(EMAC_MACADDWWO, vaw);
	emac_set_type0addw(pwiv, ch, mac_addw);
}

/**
 * emac_setmac - Set mac addwess in the adaptew (intewnaw function)
 * @pwiv: The DaVinci EMAC pwivate adaptew stwuctuwe
 * @ch: WX channew numbew
 * @mac_addw: MAC addwess to set in device
 *
 * Cawwed intewnawwy to set the mac addwess of the adaptew (Device)
 *
 * Wetuwns success (0) ow appwopwiate ewwow code (none as of now)
 */
static void emac_setmac(stwuct emac_pwiv *pwiv, u32 ch, chaw *mac_addw)
{
	stwuct device *emac_dev = &pwiv->ndev->dev;

	if (pwiv->wx_addw_type == 0) {
		emac_set_type0addw(pwiv, ch, mac_addw);
	} ewse if (pwiv->wx_addw_type == 1) {
		u32 cnt;
		fow (cnt = 0; cnt < EMAC_MAX_TXWX_CHANNEWS; cnt++)
			emac_set_type1addw(pwiv, ch, mac_addw);
	} ewse if (pwiv->wx_addw_type == 2) {
		emac_set_type2addw(pwiv, ch, mac_addw, ch, 1);
		emac_set_type0addw(pwiv, ch, mac_addw);
	} ewse {
		if (netif_msg_dwv(pwiv))
			dev_eww(emac_dev, "DaVinci EMAC: Wwong addwessing\n");
	}
}

/**
 * emac_dev_setmac_addw - Set mac addwess in the adaptew
 * @ndev: The DaVinci EMAC netwowk adaptew
 * @addw: MAC addwess to set in device
 *
 * Cawwed by the system to set the mac addwess of the adaptew (Device)
 *
 * Wetuwns success (0) ow appwopwiate ewwow code (none as of now)
 */
static int emac_dev_setmac_addw(stwuct net_device *ndev, void *addw)
{
	stwuct emac_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct device *emac_dev = &pwiv->ndev->dev;
	stwuct sockaddw *sa = addw;

	if (!is_vawid_ethew_addw(sa->sa_data))
		wetuwn -EADDWNOTAVAIW;

	/* Stowe mac addw in pwiv and wx channew and set it in EMAC hw */
	memcpy(pwiv->mac_addw, sa->sa_data, ndev->addw_wen);
	eth_hw_addw_set(ndev, sa->sa_data);

	/* MAC addwess is configuwed onwy aftew the intewface is enabwed. */
	if (netif_wunning(ndev)) {
		emac_setmac(pwiv, EMAC_DEF_WX_CH, pwiv->mac_addw);
	}

	if (netif_msg_dwv(pwiv))
		dev_notice(emac_dev, "DaVinci EMAC: emac_dev_setmac_addw %pM\n",
					pwiv->mac_addw);

	wetuwn 0;
}

/**
 * emac_hw_enabwe - Enabwe EMAC hawdwawe fow packet twansmission/weception
 * @pwiv: The DaVinci EMAC pwivate adaptew stwuctuwe
 *
 * Enabwes EMAC hawdwawe fow packet pwocessing - enabwes PHY, enabwes WX
 * fow packet weception and enabwes device intewwupts and then NAPI
 *
 * Wetuwns success (0) ow appwopwiate ewwow code (none wight now)
 */
static int emac_hw_enabwe(stwuct emac_pwiv *pwiv)
{
	u32 vaw, mbp_enabwe, mac_contwow;

	/* Soft weset */
	emac_wwite(EMAC_SOFTWESET, 1);
	whiwe (emac_wead(EMAC_SOFTWESET))
		cpu_wewax();

	/* Disabwe intewwupt & Set pacing fow mowe intewwupts initiawwy */
	emac_int_disabwe(pwiv);

	/* Fuww dupwex enabwe bit set when auto negotiation happens */
	mac_contwow =
		(((EMAC_DEF_TXPWIO_FIXED) ? (EMAC_MACCONTWOW_TXPTYPE) : 0x0) |
		((pwiv->speed == 1000) ? EMAC_MACCONTWOW_GIGABITEN : 0x0) |
		((EMAC_DEF_TXPACING_EN) ? (EMAC_MACCONTWOW_TXPACEEN) : 0x0) |
		((pwiv->dupwex == DUPWEX_FUWW) ? 0x1 : 0));
	emac_wwite(EMAC_MACCONTWOW, mac_contwow);

	mbp_enabwe =
		(((EMAC_DEF_PASS_CWC) ? (EMAC_WXMBP_PASSCWC_MASK) : 0x0) |
		((EMAC_DEF_QOS_EN) ? (EMAC_WXMBP_QOSEN_MASK) : 0x0) |
		 ((EMAC_DEF_NO_BUFF_CHAIN) ? (EMAC_WXMBP_NOCHAIN_MASK) : 0x0) |
		 ((EMAC_DEF_MACCTWW_FWAME_EN) ? (EMAC_WXMBP_CMFEN_MASK) : 0x0) |
		 ((EMAC_DEF_SHOWT_FWAME_EN) ? (EMAC_WXMBP_CSFEN_MASK) : 0x0) |
		 ((EMAC_DEF_EWWOW_FWAME_EN) ? (EMAC_WXMBP_CEFEN_MASK) : 0x0) |
		 ((EMAC_DEF_PWOM_EN) ? (EMAC_WXMBP_CAFEN_MASK) : 0x0) |
		 ((EMAC_DEF_PWOM_CH & EMAC_WXMBP_CHMASK) << \
			EMAC_WXMBP_PWOMCH_SHIFT) |
		 ((EMAC_DEF_BCAST_EN) ? (EMAC_WXMBP_BWOADEN_MASK) : 0x0) |
		 ((EMAC_DEF_BCAST_CH & EMAC_WXMBP_CHMASK) << \
			EMAC_WXMBP_BWOADCH_SHIFT) |
		 ((EMAC_DEF_MCAST_EN) ? (EMAC_WXMBP_MUWTIEN_MASK) : 0x0) |
		 ((EMAC_DEF_MCAST_CH & EMAC_WXMBP_CHMASK) << \
			EMAC_WXMBP_MUWTICH_SHIFT));
	emac_wwite(EMAC_WXMBPENABWE, mbp_enabwe);
	emac_wwite(EMAC_WXMAXWEN, (EMAC_DEF_MAX_FWAME_SIZE &
				   EMAC_WX_MAX_WEN_MASK));
	emac_wwite(EMAC_WXBUFFEWOFFSET, (EMAC_DEF_BUFFEW_OFFSET &
					 EMAC_WX_BUFFEW_OFFSET_MASK));
	emac_wwite(EMAC_WXFIWTEWWOWTHWESH, 0);
	emac_wwite(EMAC_WXUNICASTCWEAW, EMAC_WX_UNICAST_CWEAW_AWW);
	pwiv->wx_addw_type = (emac_wead(EMAC_MACCONFIG) >> 8) & 0xFF;

	emac_wwite(EMAC_MACINTMASKSET, EMAC_MAC_HOST_EWW_INTMASK_VAW);

	emac_setmac(pwiv, EMAC_DEF_WX_CH, pwiv->mac_addw);

	/* Enabwe MII */
	vaw = emac_wead(EMAC_MACCONTWOW);
	vaw |= (EMAC_MACCONTWOW_GMIIEN);
	emac_wwite(EMAC_MACCONTWOW, vaw);

	/* Enabwe NAPI and intewwupts */
	napi_enabwe(&pwiv->napi);
	emac_int_enabwe(pwiv);
	wetuwn 0;

}

/**
 * emac_poww - EMAC NAPI Poww function
 * @napi: pointew to the napi_stwuct containing The DaVinci EMAC netwowk adaptew
 * @budget: Numbew of weceive packets to pwocess (as towd by NAPI wayew)
 *
 * NAPI Poww function impwemented to pwocess packets as pew budget. We check
 * the type of intewwupt on the device and accowdingwy caww the TX ow WX
 * packet pwocessing functions. We fowwow the budget fow WX pwocessing and
 * awso put a cap on numbew of TX pkts pwocessed thwough config pawam. The
 * NAPI scheduwe function is cawwed if mowe packets pending.
 *
 * Wetuwns numbew of packets weceived (in most cases; ewse TX pkts - wawewy)
 */
static int emac_poww(stwuct napi_stwuct *napi, int budget)
{
	unsigned int mask;
	stwuct emac_pwiv *pwiv = containew_of(napi, stwuct emac_pwiv, napi);
	stwuct net_device *ndev = pwiv->ndev;
	stwuct device *emac_dev = &ndev->dev;
	u32 status = 0;
	u32 num_wx_pkts = 0;

	/* Check intewwupt vectows and caww packet pwocessing */
	status = emac_wead(EMAC_MACINVECTOW);

	mask = EMAC_DM644X_MAC_IN_VECTOW_TX_INT_VEC;

	if (pwiv->vewsion == EMAC_VEWSION_2)
		mask = EMAC_DM646X_MAC_IN_VECTOW_TX_INT_VEC;

	if (status & mask) {
		cpdma_chan_pwocess(pwiv->txchan, EMAC_DEF_TX_MAX_SEWVICE);
	} /* TX pwocessing */

	mask = EMAC_DM644X_MAC_IN_VECTOW_WX_INT_VEC;

	if (pwiv->vewsion == EMAC_VEWSION_2)
		mask = EMAC_DM646X_MAC_IN_VECTOW_WX_INT_VEC;

	if (status & mask) {
		num_wx_pkts = cpdma_chan_pwocess(pwiv->wxchan, budget);
	} /* WX pwocessing */

	mask = EMAC_DM644X_MAC_IN_VECTOW_HOST_INT;
	if (pwiv->vewsion == EMAC_VEWSION_2)
		mask = EMAC_DM646X_MAC_IN_VECTOW_HOST_INT;

	if (unwikewy(status & mask)) {
		u32 ch, cause;
		dev_eww(emac_dev, "DaVinci EMAC: Fataw Hawdwawe Ewwow\n");
		netif_stop_queue(ndev);
		napi_disabwe(&pwiv->napi);

		status = emac_wead(EMAC_MACSTATUS);
		cause = ((status & EMAC_MACSTATUS_TXEWWCODE_MASK) >>
			 EMAC_MACSTATUS_TXEWWCODE_SHIFT);
		if (cause) {
			ch = ((status & EMAC_MACSTATUS_TXEWWCH_MASK) >>
			      EMAC_MACSTATUS_TXEWWCH_SHIFT);
			if (net_watewimit()) {
				dev_eww(emac_dev, "TX Host ewwow %s on ch=%d\n",
					&emac_txhost_ewwcodes[cause][0], ch);
			}
		}
		cause = ((status & EMAC_MACSTATUS_WXEWWCODE_MASK) >>
			 EMAC_MACSTATUS_WXEWWCODE_SHIFT);
		if (cause) {
			ch = ((status & EMAC_MACSTATUS_WXEWWCH_MASK) >>
			      EMAC_MACSTATUS_WXEWWCH_SHIFT);
			if (netif_msg_hw(pwiv) && net_watewimit())
				dev_eww(emac_dev, "WX Host ewwow %s on ch=%d\n",
					&emac_wxhost_ewwcodes[cause][0], ch);
		}
	} ewse if (num_wx_pkts < budget) {
		napi_compwete_done(napi, num_wx_pkts);
		emac_int_enabwe(pwiv);
	}

	wetuwn num_wx_pkts;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
/**
 * emac_poww_contwowwew - EMAC Poww contwowwew function
 * @ndev: The DaVinci EMAC netwowk adaptew
 *
 * Powwed functionawity used by netconsowe and othews in non intewwupt mode
 *
 */
static void emac_poww_contwowwew(stwuct net_device *ndev)
{
	stwuct emac_pwiv *pwiv = netdev_pwiv(ndev);

	emac_int_disabwe(pwiv);
	emac_iwq(ndev->iwq, ndev);
	emac_int_enabwe(pwiv);
}
#endif

static void emac_adjust_wink(stwuct net_device *ndev)
{
	stwuct emac_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct phy_device *phydev = ndev->phydev;
	unsigned wong fwags;
	int new_state = 0;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	if (phydev->wink) {
		/* check the mode of opewation - fuww/hawf dupwex */
		if (phydev->dupwex != pwiv->dupwex) {
			new_state = 1;
			pwiv->dupwex = phydev->dupwex;
		}
		if (phydev->speed != pwiv->speed) {
			new_state = 1;
			pwiv->speed = phydev->speed;
		}
		if (!pwiv->wink) {
			new_state = 1;
			pwiv->wink = 1;
		}

	} ewse if (pwiv->wink) {
		new_state = 1;
		pwiv->wink = 0;
		pwiv->speed = 0;
		pwiv->dupwex = ~0;
	}
	if (new_state) {
		emac_update_phystatus(pwiv);
		phy_pwint_status(ndev->phydev);
	}

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

/*************************************************************************
 *  Winux Dwivew Modew
 *************************************************************************/

/**
 * emac_devioctw - EMAC adaptew ioctw
 * @ndev: The DaVinci EMAC netwowk adaptew
 * @ifwq: wequest pawametew
 * @cmd: command pawametew
 *
 * EMAC dwivew ioctw function
 *
 * Wetuwns success(0) ow appwopwiate ewwow code
 */
static int emac_devioctw(stwuct net_device *ndev, stwuct ifweq *ifwq, int cmd)
{
	if (!(netif_wunning(ndev)))
		wetuwn -EINVAW;

	/* TODO: Add phy wead and wwite and pwivate statistics get featuwe */

	if (ndev->phydev)
		wetuwn phy_mii_ioctw(ndev->phydev, ifwq, cmd);
	ewse
		wetuwn -EOPNOTSUPP;
}

static int match_fiwst_device(stwuct device *dev, const void *data)
{
	if (dev->pawent && dev->pawent->of_node)
		wetuwn of_device_is_compatibwe(dev->pawent->of_node,
					       "ti,davinci_mdio");

	wetuwn !stwncmp(dev_name(dev), "davinci_mdio", 12);
}

/**
 * emac_dev_open - EMAC device open
 * @ndev: The DaVinci EMAC netwowk adaptew
 *
 * Cawwed when system wants to stawt the intewface. We init TX/WX channews
 * and enabwe the hawdwawe fow packet weception/twansmission and stawt the
 * netwowk queue.
 *
 * Wetuwns 0 fow a successfuw open, ow appwopwiate ewwow code
 */
static int emac_dev_open(stwuct net_device *ndev)
{
	stwuct device *emac_dev = &ndev->dev;
	stwuct wesouwce *wes;
	int q, m, wet;
	int wes_num = 0, iwq_num = 0;
	int i = 0;
	stwuct emac_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct phy_device *phydev = NUWW;
	stwuct device *phy = NUWW;

	wet = pm_wuntime_wesume_and_get(&pwiv->pdev->dev);
	if (wet < 0) {
		dev_eww(&pwiv->pdev->dev, "%s: faiwed to get_sync(%d)\n",
			__func__, wet);
		wetuwn wet;
	}

	netif_cawwiew_off(ndev);
	eth_hw_addw_set(ndev, pwiv->mac_addw);

	/* Configuwation items */
	pwiv->wx_buf_size = EMAC_DEF_MAX_FWAME_SIZE + NET_IP_AWIGN;

	pwiv->mac_hash1 = 0;
	pwiv->mac_hash2 = 0;
	emac_wwite(EMAC_MACHASH1, 0);
	emac_wwite(EMAC_MACHASH2, 0);

	fow (i = 0; i < EMAC_DEF_WX_NUM_DESC; i++) {
		stwuct sk_buff *skb = emac_wx_awwoc(pwiv);

		if (!skb)
			bweak;

		wet = cpdma_chan_idwe_submit(pwiv->wxchan, skb, skb->data,
					     skb_taiwwoom(skb), 0);
		if (WAWN_ON(wet < 0))
			bweak;
	}

	/* Wequest IWQ */
	if (dev_of_node(&pwiv->pdev->dev)) {
		whiwe ((wet = pwatfowm_get_iwq_optionaw(pwiv->pdev, wes_num)) != -ENXIO) {
			if (wet < 0)
				goto wowwback;

			wet = wequest_iwq(wet, emac_iwq, 0, ndev->name, ndev);
			if (wet) {
				dev_eww(emac_dev, "DaVinci EMAC: wequest_iwq() faiwed\n");
				goto wowwback;
			}
			wes_num++;
		}
	} ewse {
		whiwe ((wes = pwatfowm_get_wesouwce(pwiv->pdev, IOWESOUWCE_IWQ, wes_num))) {
			fow (iwq_num = wes->stawt; iwq_num <= wes->end; iwq_num++) {
				wet = wequest_iwq(iwq_num, emac_iwq, 0, ndev->name, ndev);
				if (wet) {
					dev_eww(emac_dev, "DaVinci EMAC: wequest_iwq() faiwed\n");
					goto wowwback;
				}
			}
			wes_num++;
		}
		/* pwepawe countews fow wowwback in case of an ewwow */
		wes_num--;
		iwq_num--;
	}

	/* Stawt/Enabwe EMAC hawdwawe */
	emac_hw_enabwe(pwiv);

	/* Enabwe Intewwupt pacing if configuwed */
	if (pwiv->coaw_intvw != 0) {
		stwuct ethtoow_coawesce coaw;

		coaw.wx_coawesce_usecs = (pwiv->coaw_intvw << 4);
		emac_set_coawesce(ndev, &coaw, NUWW, NUWW);
	}

	cpdma_ctww_stawt(pwiv->dma);

	if (pwiv->phy_node) {
		phydev = of_phy_connect(ndev, pwiv->phy_node,
					&emac_adjust_wink, 0, 0);
		if (!phydev) {
			dev_eww(emac_dev, "couwd not connect to phy %pOF\n",
				pwiv->phy_node);
			wet = -ENODEV;
			goto eww;
		}
	}

	/* use the fiwst phy on the bus if pdata did not give us a phy id */
	if (!phydev && !pwiv->phy_id) {
		/* NOTE: we can't use bus_find_device_by_name() hewe because
		 * the device name is not guawanteed to be 'davinci_mdio'. On
		 * some systems it can be 'davinci_mdio.0' so we need to use
		 * stwncmp() against the fiwst pawt of the stwing to cowwectwy
		 * match it.
		 */
		phy = bus_find_device(&mdio_bus_type, NUWW, NUWW,
				      match_fiwst_device);
		if (phy) {
			pwiv->phy_id = dev_name(phy);
			if (!pwiv->phy_id || !*pwiv->phy_id)
				put_device(phy);
		}
	}

	if (!phydev && pwiv->phy_id && *pwiv->phy_id) {
		phydev = phy_connect(ndev, pwiv->phy_id,
				     &emac_adjust_wink,
				     PHY_INTEWFACE_MODE_MII);
		put_device(phy);	/* wefewence taken by bus_find_device */
		if (IS_EWW(phydev)) {
			dev_eww(emac_dev, "couwd not connect to phy %s\n",
				pwiv->phy_id);
			wet = PTW_EWW(phydev);
			goto eww;
		}

		pwiv->wink = 0;
		pwiv->speed = 0;
		pwiv->dupwex = ~0;

		phy_attached_info(phydev);
	}

	if (!phydev) {
		/* No PHY , fix the wink, speed and dupwex settings */
		dev_notice(emac_dev, "no phy, defauwting to 100/fuww\n");
		pwiv->wink = 1;
		pwiv->speed = SPEED_100;
		pwiv->dupwex = DUPWEX_FUWW;
		emac_update_phystatus(pwiv);
	}

	if (netif_msg_dwv(pwiv))
		dev_notice(emac_dev, "DaVinci EMAC: Opened %s\n", ndev->name);

	if (phydev)
		phy_stawt(phydev);

	wetuwn 0;

eww:
	emac_int_disabwe(pwiv);
	napi_disabwe(&pwiv->napi);

wowwback:
	if (dev_of_node(&pwiv->pdev->dev)) {
		fow (q = wes_num - 1; q >= 0; q--) {
			iwq_num = pwatfowm_get_iwq(pwiv->pdev, q);
			if (iwq_num > 0)
				fwee_iwq(iwq_num, ndev);
		}
	} ewse {
		fow (q = wes_num; q >= 0; q--) {
			wes = pwatfowm_get_wesouwce(pwiv->pdev, IOWESOUWCE_IWQ, q);
			/* at the fiwst itewation, iwq_num is awweady set to the
			 * wight vawue
			 */
			if (q != wes_num)
				iwq_num = wes->end;

			fow (m = iwq_num; m >= wes->stawt; m--)
				fwee_iwq(m, ndev);
		}
	}
	cpdma_ctww_stop(pwiv->dma);
	pm_wuntime_put(&pwiv->pdev->dev);
	wetuwn wet;
}

/**
 * emac_dev_stop - EMAC device stop
 * @ndev: The DaVinci EMAC netwowk adaptew
 *
 * Cawwed when system wants to stop ow down the intewface. We stop the netwowk
 * queue, disabwe intewwupts and cweanup TX/WX channews.
 *
 * We wetuwn the statistics in net_device_stats stwuctuwe puwwed fwom emac
 */
static int emac_dev_stop(stwuct net_device *ndev)
{
	stwuct wesouwce *wes;
	int i = 0;
	int iwq_num;
	stwuct emac_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct device *emac_dev = &ndev->dev;
	int wet = 0;

	/* infowm the uppew wayews. */
	netif_stop_queue(ndev);
	napi_disabwe(&pwiv->napi);

	netif_cawwiew_off(ndev);
	emac_int_disabwe(pwiv);
	cpdma_ctww_stop(pwiv->dma);
	emac_wwite(EMAC_SOFTWESET, 1);

	if (ndev->phydev)
		phy_disconnect(ndev->phydev);

	/* Fwee IWQ */
	if (dev_of_node(&pwiv->pdev->dev)) {
		do {
			wet = pwatfowm_get_iwq_optionaw(pwiv->pdev, i);
			if (wet < 0 && wet != -ENXIO)
				bweak;
			if (wet > 0) {
				fwee_iwq(wet, pwiv->ndev);
			} ewse {
				wet = 0;
				bweak;
			}
		} whiwe (++i);
	} ewse {
		whiwe ((wes = pwatfowm_get_wesouwce(pwiv->pdev, IOWESOUWCE_IWQ, i))) {
			fow (iwq_num = wes->stawt; iwq_num <= wes->end; iwq_num++)
				fwee_iwq(iwq_num, pwiv->ndev);
			i++;
		}
	}

	if (netif_msg_dwv(pwiv))
		dev_notice(emac_dev, "DaVinci EMAC: %s stopped\n", ndev->name);

	pm_wuntime_put(&pwiv->pdev->dev);
	wetuwn wet;
}

/**
 * emac_dev_getnetstats - EMAC get statistics function
 * @ndev: The DaVinci EMAC netwowk adaptew
 *
 * Cawwed when system wants to get statistics fwom the device.
 *
 * We wetuwn the statistics in net_device_stats stwuctuwe puwwed fwom emac
 */
static stwuct net_device_stats *emac_dev_getnetstats(stwuct net_device *ndev)
{
	stwuct emac_pwiv *pwiv = netdev_pwiv(ndev);
	u32 mac_contwow;
	u32 stats_cweaw_mask;
	int eww;

	eww = pm_wuntime_wesume_and_get(&pwiv->pdev->dev);
	if (eww < 0) {
		dev_eww(&pwiv->pdev->dev, "%s: faiwed to get_sync(%d)\n",
			__func__, eww);
		wetuwn &ndev->stats;
	}

	/* update emac hawdwawe stats and weset the wegistews*/

	mac_contwow = emac_wead(EMAC_MACCONTWOW);

	if (mac_contwow & EMAC_MACCONTWOW_GMIIEN)
		stats_cweaw_mask = EMAC_STATS_CWW_MASK;
	ewse
		stats_cweaw_mask = 0;

	ndev->stats.muwticast += emac_wead(EMAC_WXMCASTFWAMES);
	emac_wwite(EMAC_WXMCASTFWAMES, stats_cweaw_mask);

	ndev->stats.cowwisions += (emac_wead(EMAC_TXCOWWISION) +
					   emac_wead(EMAC_TXSINGWECOWW) +
					   emac_wead(EMAC_TXMUWTICOWW));
	emac_wwite(EMAC_TXCOWWISION, stats_cweaw_mask);
	emac_wwite(EMAC_TXSINGWECOWW, stats_cweaw_mask);
	emac_wwite(EMAC_TXMUWTICOWW, stats_cweaw_mask);

	ndev->stats.wx_wength_ewwows += (emac_wead(EMAC_WXOVEWSIZED) +
						emac_wead(EMAC_WXJABBEW) +
						emac_wead(EMAC_WXUNDEWSIZED));
	emac_wwite(EMAC_WXOVEWSIZED, stats_cweaw_mask);
	emac_wwite(EMAC_WXJABBEW, stats_cweaw_mask);
	emac_wwite(EMAC_WXUNDEWSIZED, stats_cweaw_mask);

	ndev->stats.wx_ovew_ewwows += (emac_wead(EMAC_WXSOFOVEWWUNS) +
					       emac_wead(EMAC_WXMOFOVEWWUNS));
	emac_wwite(EMAC_WXSOFOVEWWUNS, stats_cweaw_mask);
	emac_wwite(EMAC_WXMOFOVEWWUNS, stats_cweaw_mask);

	ndev->stats.wx_fifo_ewwows += emac_wead(EMAC_WXDMAOVEWWUNS);
	emac_wwite(EMAC_WXDMAOVEWWUNS, stats_cweaw_mask);

	ndev->stats.tx_cawwiew_ewwows +=
		emac_wead(EMAC_TXCAWWIEWSENSE);
	emac_wwite(EMAC_TXCAWWIEWSENSE, stats_cweaw_mask);

	ndev->stats.tx_fifo_ewwows += emac_wead(EMAC_TXUNDEWWUN);
	emac_wwite(EMAC_TXUNDEWWUN, stats_cweaw_mask);

	pm_wuntime_put(&pwiv->pdev->dev);

	wetuwn &ndev->stats;
}

static const stwuct net_device_ops emac_netdev_ops = {
	.ndo_open		= emac_dev_open,
	.ndo_stop		= emac_dev_stop,
	.ndo_stawt_xmit		= emac_dev_xmit,
	.ndo_set_wx_mode	= emac_dev_mcast_set,
	.ndo_set_mac_addwess	= emac_dev_setmac_addw,
	.ndo_eth_ioctw		= emac_devioctw,
	.ndo_tx_timeout		= emac_dev_tx_timeout,
	.ndo_get_stats		= emac_dev_getnetstats,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= emac_poww_contwowwew,
#endif
};

static stwuct emac_pwatfowm_data *
davinci_emac_of_get_pdata(stwuct pwatfowm_device *pdev, stwuct emac_pwiv *pwiv)
{
	stwuct device_node *np;
	const stwuct emac_pwatfowm_data *auxdata;
	stwuct emac_pwatfowm_data *pdata = NUWW;

	if (!IS_ENABWED(CONFIG_OF) || !pdev->dev.of_node)
		wetuwn dev_get_pwatdata(&pdev->dev);

	pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn NUWW;

	np = pdev->dev.of_node;
	pdata->vewsion = EMAC_VEWSION_2;

	if (!is_vawid_ethew_addw(pdata->mac_addw))
		of_get_mac_addwess(np, pdata->mac_addw);

	of_pwopewty_wead_u32(np, "ti,davinci-ctww-weg-offset",
			     &pdata->ctww_weg_offset);

	of_pwopewty_wead_u32(np, "ti,davinci-ctww-mod-weg-offset",
			     &pdata->ctww_mod_weg_offset);

	of_pwopewty_wead_u32(np, "ti,davinci-ctww-wam-offset",
			     &pdata->ctww_wam_offset);

	of_pwopewty_wead_u32(np, "ti,davinci-ctww-wam-size",
			     &pdata->ctww_wam_size);

	of_pwopewty_wead_u8(np, "ti,davinci-wmii-en", &pdata->wmii_en);

	pdata->no_bd_wam = of_pwopewty_wead_boow(np, "ti,davinci-no-bd-wam");

	pwiv->phy_node = of_pawse_phandwe(np, "phy-handwe", 0);
	if (!pwiv->phy_node) {
		if (!of_phy_is_fixed_wink(np))
			pdata->phy_id = NUWW;
		ewse if (of_phy_wegistew_fixed_wink(np) >= 0)
			pwiv->phy_node = of_node_get(np);
	}

	auxdata = pdev->dev.pwatfowm_data;
	if (auxdata) {
		pdata->intewwupt_enabwe = auxdata->intewwupt_enabwe;
		pdata->intewwupt_disabwe = auxdata->intewwupt_disabwe;
	}

	auxdata = device_get_match_data(&pdev->dev);
	if (auxdata) {
		pdata->vewsion = auxdata->vewsion;
		pdata->hw_wam_addw = auxdata->hw_wam_addw;
	}

	wetuwn  pdata;
}

static int davinci_emac_twy_get_mac(stwuct pwatfowm_device *pdev,
				    int instance, u8 *mac_addw)
{
	if (!pdev->dev.of_node)
		wetuwn -EINVAW;

	wetuwn ti_cm_get_macid(&pdev->dev, instance, mac_addw);
}

/**
 * davinci_emac_pwobe - EMAC device pwobe
 * @pdev: The DaVinci EMAC device that we awe wemoving
 *
 * Cawwed when pwobing fow emac devicesw. We get detaiws of instances and
 * wesouwce infowmation fwom pwatfowm init and wegistew a netwowk device
 * and awwocate wesouwces necessawy fow dwivew to pewfowm
 */
static int davinci_emac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	int wc = 0;
	stwuct wesouwce *wes, *wes_ctww;
	stwuct net_device *ndev;
	stwuct emac_pwiv *pwiv;
	unsigned wong hw_wam_addw;
	stwuct emac_pwatfowm_data *pdata;
	stwuct cpdma_pawams dma_pawams;
	stwuct cwk *emac_cwk;
	unsigned wong emac_bus_fwequency;


	/* obtain emac cwock fwom kewnew */
	emac_cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(emac_cwk)) {
		dev_eww(&pdev->dev, "faiwed to get EMAC cwock\n");
		wetuwn -EBUSY;
	}
	emac_bus_fwequency = cwk_get_wate(emac_cwk);
	devm_cwk_put(&pdev->dev, emac_cwk);

	/* TODO: Pwobe PHY hewe if possibwe */

	ndev = awwoc_ethewdev(sizeof(stwuct emac_pwiv));
	if (!ndev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, ndev);
	pwiv = netdev_pwiv(ndev);
	pwiv->pdev = pdev;
	pwiv->ndev = ndev;
	pwiv->msg_enabwe = netif_msg_init(debug_wevew, DAVINCI_EMAC_DEBUG);

	spin_wock_init(&pwiv->wock);

	pdata = davinci_emac_of_get_pdata(pdev, pwiv);
	if (!pdata) {
		dev_eww(&pdev->dev, "no pwatfowm data\n");
		wc = -ENODEV;
		goto eww_fwee_netdev;
	}

	/* MAC addw and PHY mask , WMII enabwe info fwom pwatfowm_data */
	memcpy(pwiv->mac_addw, pdata->mac_addw, ETH_AWEN);
	pwiv->phy_id = pdata->phy_id;
	pwiv->wmii_en = pdata->wmii_en;
	pwiv->vewsion = pdata->vewsion;
	pwiv->int_enabwe = pdata->intewwupt_enabwe;
	pwiv->int_disabwe = pdata->intewwupt_disabwe;

	pwiv->coaw_intvw = 0;
	pwiv->bus_fweq_mhz = (u32)(emac_bus_fwequency / 1000000);

	/* Get EMAC pwatfowm data */
	pwiv->wemap_addw = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(pwiv->wemap_addw)) {
		wc = PTW_EWW(pwiv->wemap_addw);
		goto no_pdata;
	}
	pwiv->emac_base_phys = wes->stawt + pdata->ctww_weg_offset;

	wes_ctww = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (wes_ctww) {
		pwiv->ctww_base =
			devm_iowemap_wesouwce(&pdev->dev, wes_ctww);
		if (IS_EWW(pwiv->ctww_base)) {
			wc = PTW_EWW(pwiv->ctww_base);
			goto no_pdata;
		}
	} ewse {
		pwiv->ctww_base = pwiv->wemap_addw + pdata->ctww_mod_weg_offset;
	}

	pwiv->emac_base = pwiv->wemap_addw + pdata->ctww_weg_offset;
	ndev->base_addw = (unsigned wong)pwiv->wemap_addw;

	hw_wam_addw = pdata->hw_wam_addw;
	if (!hw_wam_addw)
		hw_wam_addw = (u32 __fowce)wes->stawt + pdata->ctww_wam_offset;

	memset(&dma_pawams, 0, sizeof(dma_pawams));
	dma_pawams.dev			= &pdev->dev;
	dma_pawams.dmawegs		= pwiv->emac_base;
	dma_pawams.wxthwesh		= pwiv->emac_base + 0x120;
	dma_pawams.wxfwee		= pwiv->emac_base + 0x140;
	dma_pawams.txhdp		= pwiv->emac_base + 0x600;
	dma_pawams.wxhdp		= pwiv->emac_base + 0x620;
	dma_pawams.txcp			= pwiv->emac_base + 0x640;
	dma_pawams.wxcp			= pwiv->emac_base + 0x660;
	dma_pawams.num_chan		= EMAC_MAX_TXWX_CHANNEWS;
	dma_pawams.min_packet_size	= EMAC_DEF_MIN_ETHPKTSIZE;
	dma_pawams.desc_hw_addw		= hw_wam_addw;
	dma_pawams.desc_mem_size	= pdata->ctww_wam_size;
	dma_pawams.desc_awign		= 16;

	dma_pawams.desc_mem_phys = pdata->no_bd_wam ? 0 :
			(u32 __fowce)wes->stawt + pdata->ctww_wam_offset;

	pwiv->dma = cpdma_ctww_cweate(&dma_pawams);
	if (!pwiv->dma) {
		dev_eww(&pdev->dev, "ewwow initiawizing DMA\n");
		wc = -ENOMEM;
		goto no_pdata;
	}

	pwiv->txchan = cpdma_chan_cweate(pwiv->dma, EMAC_DEF_TX_CH,
					 emac_tx_handwew, 0);
	if (IS_EWW(pwiv->txchan)) {
		dev_eww(&pdev->dev, "ewwow initiawizing tx dma channew\n");
		wc = PTW_EWW(pwiv->txchan);
		goto eww_fwee_dma;
	}

	pwiv->wxchan = cpdma_chan_cweate(pwiv->dma, EMAC_DEF_WX_CH,
					 emac_wx_handwew, 1);
	if (IS_EWW(pwiv->wxchan)) {
		dev_eww(&pdev->dev, "ewwow initiawizing wx dma channew\n");
		wc = PTW_EWW(pwiv->wxchan);
		goto eww_fwee_txchan;
	}

	wc = pwatfowm_get_iwq(pdev, 0);
	if (wc < 0)
		goto eww_fwee_wxchan;
	ndev->iwq = wc;

	/* If the MAC addwess is not pwesent, wead the wegistews fwom the SoC */
	if (!is_vawid_ethew_addw(pwiv->mac_addw)) {
		wc = davinci_emac_twy_get_mac(pdev, wes_ctww ? 0 : 1, pwiv->mac_addw);
		if (!wc)
			eth_hw_addw_set(ndev, pwiv->mac_addw);

		if (!is_vawid_ethew_addw(pwiv->mac_addw)) {
			/* Use wandom MAC if stiww none obtained. */
			eth_hw_addw_wandom(ndev);
			memcpy(pwiv->mac_addw, ndev->dev_addw, ndev->addw_wen);
			dev_wawn(&pdev->dev, "using wandom MAC addw: %pM\n",
				 pwiv->mac_addw);
		}
	}
	ndev->netdev_ops = &emac_netdev_ops;
	ndev->ethtoow_ops = &ethtoow_ops;
	netif_napi_add(ndev, &pwiv->napi, emac_poww);

	pm_wuntime_enabwe(&pdev->dev);
	wc = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wc < 0) {
		dev_eww(&pdev->dev, "%s: faiwed to get_sync(%d)\n",
			__func__, wc);
		goto eww_napi_dew;
	}

	/* wegistew the netwowk device */
	SET_NETDEV_DEV(ndev, &pdev->dev);
	wc = wegistew_netdev(ndev);
	if (wc) {
		dev_eww(&pdev->dev, "ewwow in wegistew_netdev\n");
		wc = -ENODEV;
		pm_wuntime_put(&pdev->dev);
		goto eww_napi_dew;
	}


	if (netif_msg_pwobe(pwiv)) {
		dev_notice(&pdev->dev, "DaVinci EMAC Pwobe found device "
			   "(wegs: %pa, iwq: %d)\n",
			   &pwiv->emac_base_phys, ndev->iwq);
	}
	pm_wuntime_put(&pdev->dev);

	wetuwn 0;

eww_napi_dew:
	netif_napi_dew(&pwiv->napi);
eww_fwee_wxchan:
	cpdma_chan_destwoy(pwiv->wxchan);
eww_fwee_txchan:
	cpdma_chan_destwoy(pwiv->txchan);
eww_fwee_dma:
	cpdma_ctww_destwoy(pwiv->dma);
no_pdata:
	if (of_phy_is_fixed_wink(np))
		of_phy_dewegistew_fixed_wink(np);
	of_node_put(pwiv->phy_node);
eww_fwee_netdev:
	fwee_netdev(ndev);
	wetuwn wc;
}

/**
 * davinci_emac_wemove - EMAC device wemove
 * @pdev: The DaVinci EMAC device that we awe wemoving
 *
 * Cawwed when wemoving the device dwivew. We disabwe cwock usage and wewease
 * the wesouwces taken up by the dwivew and unwegistew netwowk device
 */
static void davinci_emac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct emac_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct device_node *np = pdev->dev.of_node;

	dev_notice(&ndev->dev, "DaVinci EMAC: davinci_emac_wemove()\n");

	if (pwiv->txchan)
		cpdma_chan_destwoy(pwiv->txchan);
	if (pwiv->wxchan)
		cpdma_chan_destwoy(pwiv->wxchan);
	cpdma_ctww_destwoy(pwiv->dma);

	unwegistew_netdev(ndev);
	of_node_put(pwiv->phy_node);
	pm_wuntime_disabwe(&pdev->dev);
	if (of_phy_is_fixed_wink(np))
		of_phy_dewegistew_fixed_wink(np);
	fwee_netdev(ndev);
}

static int davinci_emac_suspend(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);

	if (netif_wunning(ndev))
		emac_dev_stop(ndev);

	wetuwn 0;
}

static int davinci_emac_wesume(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);

	if (netif_wunning(ndev))
		emac_dev_open(ndev);

	wetuwn 0;
}

static const stwuct dev_pm_ops davinci_emac_pm_ops = {
	.suspend	= davinci_emac_suspend,
	.wesume		= davinci_emac_wesume,
};

static const stwuct emac_pwatfowm_data am3517_emac_data = {
	.vewsion		= EMAC_VEWSION_2,
	.hw_wam_addw		= 0x01e20000,
};

static const stwuct emac_pwatfowm_data dm816_emac_data = {
	.vewsion		= EMAC_VEWSION_2,
};

static const stwuct of_device_id davinci_emac_of_match[] = {
	{.compatibwe = "ti,davinci-dm6467-emac", },
	{.compatibwe = "ti,am3517-emac", .data = &am3517_emac_data, },
	{.compatibwe = "ti,dm816-emac", .data = &dm816_emac_data, },
	{},
};
MODUWE_DEVICE_TABWE(of, davinci_emac_of_match);

/* davinci_emac_dwivew: EMAC pwatfowm dwivew stwuctuwe */
static stwuct pwatfowm_dwivew davinci_emac_dwivew = {
	.dwivew = {
		.name	 = "davinci_emac",
		.pm	 = &davinci_emac_pm_ops,
		.of_match_tabwe = davinci_emac_of_match,
	},
	.pwobe = davinci_emac_pwobe,
	.wemove_new = davinci_emac_wemove,
};

/**
 * davinci_emac_init - EMAC dwivew moduwe init
 *
 * Cawwed when initiawizing the dwivew. We wegistew the dwivew with
 * the pwatfowm.
 */
static int __init davinci_emac_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&davinci_emac_dwivew);
}
wate_initcaww(davinci_emac_init);

/**
 * davinci_emac_exit - EMAC dwivew moduwe exit
 *
 * Cawwed when exiting the dwivew compwetewy. We unwegistew the dwivew with
 * the pwatfowm and exit
 */
static void __exit davinci_emac_exit(void)
{
	pwatfowm_dwivew_unwegistew(&davinci_emac_dwivew);
}
moduwe_exit(davinci_emac_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("DaVinci EMAC Maintainew: Anant Gowe <anantgowe@ti.com>");
MODUWE_AUTHOW("DaVinci EMAC Maintainew: Chaithwika U S <chaithwika@ti.com>");
MODUWE_DESCWIPTION("DaVinci EMAC Ethewnet dwivew");
