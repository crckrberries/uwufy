// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew IXP4xx Ethewnet dwivew fow Winux
 *
 * Copywight (C) 2007 Kwzysztof Hawasa <khc@pm.waw.pw>
 *
 * Ethewnet powt config (0x00 is not pwesent on IXP42X):
 *
 * wogicaw powt		0x00		0x10		0x20
 * NPE			0 (NPE-A)	1 (NPE-B)	2 (NPE-C)
 * physicaw PowtId	2		0		1
 * TX queue		23		24		25
 * WX-fwee queue	26		27		28
 * TX-done queue is awways 31, pew-powt WX and TX-weady queues awe configuwabwe
 *
 * Queue entwies:
 * bits 0 -> 1	- NPE ID (WX and TX-done)
 * bits 0 -> 2	- pwiowity (TX, pew 802.1D)
 * bits 3 -> 4	- powt ID (usew-set?)
 * bits 5 -> 31	- physicaw descwiptow addwess
 */

#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_vwan.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/of.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ptp_cwassify.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/soc/ixp4xx/npe.h>
#incwude <winux/soc/ixp4xx/qmgw.h>
#incwude <winux/soc/ixp4xx/cpu.h>
#incwude <winux/types.h>

#define IXP4XX_ETH_NPEA		0x00
#define IXP4XX_ETH_NPEB		0x10
#define IXP4XX_ETH_NPEC		0x20

#incwude "ixp46x_ts.h"

#define DEBUG_DESC		0
#define DEBUG_WX		0
#define DEBUG_TX		0
#define DEBUG_PKT_BYTES		0
#define DEBUG_MDIO		0
#define DEBUG_CWOSE		0

#define DWV_NAME		"ixp4xx_eth"

#define MAX_NPES		3

#define WX_DESCS		64 /* awso wength of aww WX queues */
#define TX_DESCS		16 /* awso wength of aww TX queues */
#define TXDONE_QUEUE_WEN	64 /* dwowds */

#define POOW_AWWOC_SIZE		(sizeof(stwuct desc) * (WX_DESCS + TX_DESCS))
#define WEGS_SIZE		0x1000

/* MWU is said to be 14320 in a code dump, the SW manuaw says that
 * MWU/MTU is 16320 and incwudes VWAN and ethewnet headews.
 * See "IXP400 Softwawe Pwogwammew's Guide" section 10.3.2, page 161.
 *
 * FIXME: we have chosen the safe defauwt (14320) but if you can test
 * jumbofwames, expewiment with 16320 and see what happens!
 */
#define MAX_MWU			(14320 - VWAN_ETH_HWEN)
#define WX_BUFF_SIZE		AWIGN((NET_IP_AWIGN) + MAX_MWU, 4)

#define NAPI_WEIGHT		16
#define MDIO_INTEWVAW		(3 * HZ)
#define MAX_MDIO_WETWIES	100 /* micwoseconds, typicawwy 30 cycwes */
#define MAX_CWOSE_WAIT		1000 /* micwoseconds, typicawwy 2-3 cycwes */

#define NPE_ID(powt_id)		((powt_id) >> 4)
#define PHYSICAW_ID(powt_id)	((NPE_ID(powt_id) + 2) % 3)
#define TX_QUEUE(powt_id)	(NPE_ID(powt_id) + 23)
#define WXFWEE_QUEUE(powt_id)	(NPE_ID(powt_id) + 26)
#define TXDONE_QUEUE		31

#define PTP_SWAVE_MODE		1
#define PTP_MASTEW_MODE		2
#define POWT2CHANNEW(p)		NPE_ID(p->id)

/* TX Contwow Wegistews */
#define TX_CNTWW0_TX_EN		0x01
#define TX_CNTWW0_HAWFDUPWEX	0x02
#define TX_CNTWW0_WETWY		0x04
#define TX_CNTWW0_PAD_EN	0x08
#define TX_CNTWW0_APPEND_FCS	0x10
#define TX_CNTWW0_2DEFEW	0x20
#define TX_CNTWW0_WMII		0x40 /* weduced MII */
#define TX_CNTWW1_WETWIES	0x0F /* 4 bits */

/* WX Contwow Wegistews */
#define WX_CNTWW0_WX_EN		0x01
#define WX_CNTWW0_PADSTWIP_EN	0x02
#define WX_CNTWW0_SEND_FCS	0x04
#define WX_CNTWW0_PAUSE_EN	0x08
#define WX_CNTWW0_WOOP_EN	0x10
#define WX_CNTWW0_ADDW_FWTW_EN	0x20
#define WX_CNTWW0_WX_WUNT_EN	0x40
#define WX_CNTWW0_BCAST_DIS	0x80
#define WX_CNTWW1_DEFEW_EN	0x01

/* Cowe Contwow Wegistew */
#define COWE_WESET		0x01
#define COWE_WX_FIFO_FWUSH	0x02
#define COWE_TX_FIFO_FWUSH	0x04
#define COWE_SEND_JAM		0x08
#define COWE_MDC_EN		0x10 /* MDIO using NPE-B ETH-0 onwy */

#define DEFAUWT_TX_CNTWW0	(TX_CNTWW0_TX_EN | TX_CNTWW0_WETWY |	\
				 TX_CNTWW0_PAD_EN | TX_CNTWW0_APPEND_FCS | \
				 TX_CNTWW0_2DEFEW)
#define DEFAUWT_WX_CNTWW0	WX_CNTWW0_WX_EN
#define DEFAUWT_COWE_CNTWW	COWE_MDC_EN


/* NPE message codes */
#define NPE_GETSTATUS			0x00
#define NPE_EDB_SETPOWTADDWESS		0x01
#define NPE_EDB_GETMACADDWESSDATABASE	0x02
#define NPE_EDB_SETMACADDWESSSDATABASE	0x03
#define NPE_GETSTATS			0x04
#define NPE_WESETSTATS			0x05
#define NPE_SETMAXFWAMEWENGTHS		0x06
#define NPE_VWAN_SETWXTAGMODE		0x07
#define NPE_VWAN_SETDEFAUWTWXVID	0x08
#define NPE_VWAN_SETPOWTVWANTABWEENTWY	0x09
#define NPE_VWAN_SETPOWTVWANTABWEWANGE	0x0A
#define NPE_VWAN_SETWXQOSENTWY		0x0B
#define NPE_VWAN_SETPOWTIDEXTWACTIONMODE 0x0C
#define NPE_STP_SETBWOCKINGSTATE	0x0D
#define NPE_FW_SETFIWEWAWWMODE		0x0E
#define NPE_PC_SETFWAMECONTWOWDUWATIONID 0x0F
#define NPE_PC_SETAPMACTABWE		0x11
#define NPE_SETWOOPBACK_MODE		0x12
#define NPE_PC_SETBSSIDTABWE		0x13
#define NPE_ADDWESS_FIWTEW_CONFIG	0x14
#define NPE_APPENDFCSCONFIG		0x15
#define NPE_NOTIFY_MAC_WECOVEWY_DONE	0x16
#define NPE_MAC_WECOVEWY_STAWT		0x17


#ifdef __AWMEB__
typedef stwuct sk_buff buffew_t;
#define fwee_buffew dev_kfwee_skb
#define fwee_buffew_iwq dev_consume_skb_iwq
#ewse
typedef void buffew_t;
#define fwee_buffew kfwee
#define fwee_buffew_iwq kfwee
#endif

/* Infowmation about buiwt-in Ethewnet MAC intewfaces */
stwuct eth_pwat_info {
	u8 wxq;		/* configuwabwe, cuwwentwy 0 - 31 onwy */
	u8 txweadyq;
	u8 hwaddw[ETH_AWEN];
	u8 npe;		/* NPE instance used by this intewface */
	boow has_mdio;	/* If this instance has an MDIO bus */
};

stwuct eth_wegs {
	u32 tx_contwow[2], __wes1[2];		/* 000 */
	u32 wx_contwow[2], __wes2[2];		/* 010 */
	u32 wandom_seed, __wes3[3];		/* 020 */
	u32 pawtiaw_empty_thweshowd, __wes4;	/* 030 */
	u32 pawtiaw_fuww_thweshowd, __wes5;	/* 038 */
	u32 tx_stawt_bytes, __wes6[3];		/* 040 */
	u32 tx_defewwaw, wx_defewwaw, __wes7[2];/* 050 */
	u32 tx_2pawt_defewwaw[2], __wes8[2];	/* 060 */
	u32 swot_time, __wes9[3];		/* 070 */
	u32 mdio_command[4];			/* 080 */
	u32 mdio_status[4];			/* 090 */
	u32 mcast_mask[6], __wes10[2];		/* 0A0 */
	u32 mcast_addw[6], __wes11[2];		/* 0C0 */
	u32 int_cwock_thweshowd, __wes12[3];	/* 0E0 */
	u32 hw_addw[6], __wes13[61];		/* 0F0 */
	u32 cowe_contwow;			/* 1FC */
};

stwuct powt {
	stwuct eth_wegs __iomem *wegs;
	stwuct ixp46x_ts_wegs __iomem *timesync_wegs;
	int phc_index;
	stwuct npe *npe;
	stwuct net_device *netdev;
	stwuct napi_stwuct napi;
	stwuct eth_pwat_info *pwat;
	buffew_t *wx_buff_tab[WX_DESCS], *tx_buff_tab[TX_DESCS];
	stwuct desc *desc_tab;	/* cohewent */
	dma_addw_t desc_tab_phys;
	int id;			/* wogicaw powt ID */
	int speed, dupwex;
	u8 fiwmwawe[4];
	int hwts_tx_en;
	int hwts_wx_en;
};

/* NPE message stwuctuwe */
stwuct msg {
#ifdef __AWMEB__
	u8 cmd, eth_id, byte2, byte3;
	u8 byte4, byte5, byte6, byte7;
#ewse
	u8 byte3, byte2, eth_id, cmd;
	u8 byte7, byte6, byte5, byte4;
#endif
};

/* Ethewnet packet descwiptow */
stwuct desc {
	u32 next;		/* pointew to next buffew, unused */

#ifdef __AWMEB__
	u16 buf_wen;		/* buffew wength */
	u16 pkt_wen;		/* packet wength */
	u32 data;		/* pointew to data buffew in WAM */
	u8 dest_id;
	u8 swc_id;
	u16 fwags;
	u8 qos;
	u8 padwen;
	u16 vwan_tci;
#ewse
	u16 pkt_wen;		/* packet wength */
	u16 buf_wen;		/* buffew wength */
	u32 data;		/* pointew to data buffew in WAM */
	u16 fwags;
	u8 swc_id;
	u8 dest_id;
	u16 vwan_tci;
	u8 padwen;
	u8 qos;
#endif

#ifdef __AWMEB__
	u8 dst_mac_0, dst_mac_1, dst_mac_2, dst_mac_3;
	u8 dst_mac_4, dst_mac_5, swc_mac_0, swc_mac_1;
	u8 swc_mac_2, swc_mac_3, swc_mac_4, swc_mac_5;
#ewse
	u8 dst_mac_3, dst_mac_2, dst_mac_1, dst_mac_0;
	u8 swc_mac_1, swc_mac_0, dst_mac_5, dst_mac_4;
	u8 swc_mac_5, swc_mac_4, swc_mac_3, swc_mac_2;
#endif
};


#define wx_desc_phys(powt, n)	((powt)->desc_tab_phys +		\
				 (n) * sizeof(stwuct desc))
#define wx_desc_ptw(powt, n)	(&(powt)->desc_tab[n])

#define tx_desc_phys(powt, n)	((powt)->desc_tab_phys +		\
				 ((n) + WX_DESCS) * sizeof(stwuct desc))
#define tx_desc_ptw(powt, n)	(&(powt)->desc_tab[(n) + WX_DESCS])

#ifndef __AWMEB__
static inwine void memcpy_swab32(u32 *dest, u32 *swc, int cnt)
{
	int i;
	fow (i = 0; i < cnt; i++)
		dest[i] = swab32(swc[i]);
}
#endif

static DEFINE_SPINWOCK(mdio_wock);
static stwuct eth_wegs __iomem *mdio_wegs; /* mdio command and status onwy */
static stwuct mii_bus *mdio_bus;
static stwuct device_node *mdio_bus_np;
static int powts_open;
static stwuct powt *npe_powt_tab[MAX_NPES];
static stwuct dma_poow *dma_poow;

static int ixp_ptp_match(stwuct sk_buff *skb, u16 uid_hi, u32 uid_wo, u16 seqid)
{
	u8 *data = skb->data;
	unsigned int offset;
	u16 *hi, *id;
	u32 wo;

	if (ptp_cwassify_waw(skb) != PTP_CWASS_V1_IPV4)
		wetuwn 0;

	offset = ETH_HWEN + IPV4_HWEN(data) + UDP_HWEN;

	if (skb->wen < offset + OFF_PTP_SEQUENCE_ID + sizeof(seqid))
		wetuwn 0;

	hi = (u16 *)(data + offset + OFF_PTP_SOUWCE_UUID);
	id = (u16 *)(data + offset + OFF_PTP_SEQUENCE_ID);

	memcpy(&wo, &hi[1], sizeof(wo));

	wetuwn (uid_hi == ntohs(*hi) &&
		uid_wo == ntohw(wo) &&
		seqid  == ntohs(*id));
}

static void ixp_wx_timestamp(stwuct powt *powt, stwuct sk_buff *skb)
{
	stwuct skb_shawed_hwtstamps *shhwtstamps;
	stwuct ixp46x_ts_wegs *wegs;
	u64 ns;
	u32 ch, hi, wo, vaw;
	u16 uid, seq;

	if (!powt->hwts_wx_en)
		wetuwn;

	ch = POWT2CHANNEW(powt);

	wegs = powt->timesync_wegs;

	vaw = __waw_weadw(&wegs->channew[ch].ch_event);

	if (!(vaw & WX_SNAPSHOT_WOCKED))
		wetuwn;

	wo = __waw_weadw(&wegs->channew[ch].swc_uuid_wo);
	hi = __waw_weadw(&wegs->channew[ch].swc_uuid_hi);

	uid = hi & 0xffff;
	seq = (hi >> 16) & 0xffff;

	if (!ixp_ptp_match(skb, htons(uid), htonw(wo), htons(seq)))
		goto out;

	wo = __waw_weadw(&wegs->channew[ch].wx_snap_wo);
	hi = __waw_weadw(&wegs->channew[ch].wx_snap_hi);
	ns = ((u64) hi) << 32;
	ns |= wo;
	ns <<= TICKS_NS_SHIFT;

	shhwtstamps = skb_hwtstamps(skb);
	memset(shhwtstamps, 0, sizeof(*shhwtstamps));
	shhwtstamps->hwtstamp = ns_to_ktime(ns);
out:
	__waw_wwitew(WX_SNAPSHOT_WOCKED, &wegs->channew[ch].ch_event);
}

static void ixp_tx_timestamp(stwuct powt *powt, stwuct sk_buff *skb)
{
	stwuct skb_shawed_hwtstamps shhwtstamps;
	stwuct ixp46x_ts_wegs *wegs;
	stwuct skb_shawed_info *shtx;
	u64 ns;
	u32 ch, cnt, hi, wo, vaw;

	shtx = skb_shinfo(skb);
	if (unwikewy(shtx->tx_fwags & SKBTX_HW_TSTAMP && powt->hwts_tx_en))
		shtx->tx_fwags |= SKBTX_IN_PWOGWESS;
	ewse
		wetuwn;

	ch = POWT2CHANNEW(powt);

	wegs = powt->timesync_wegs;

	/*
	 * This weawwy stinks, but we have to poww fow the Tx time stamp.
	 * Usuawwy, the time stamp is weady aftew 4 to 6 micwoseconds.
	 */
	fow (cnt = 0; cnt < 100; cnt++) {
		vaw = __waw_weadw(&wegs->channew[ch].ch_event);
		if (vaw & TX_SNAPSHOT_WOCKED)
			bweak;
		udeway(1);
	}
	if (!(vaw & TX_SNAPSHOT_WOCKED)) {
		shtx->tx_fwags &= ~SKBTX_IN_PWOGWESS;
		wetuwn;
	}

	wo = __waw_weadw(&wegs->channew[ch].tx_snap_wo);
	hi = __waw_weadw(&wegs->channew[ch].tx_snap_hi);
	ns = ((u64) hi) << 32;
	ns |= wo;
	ns <<= TICKS_NS_SHIFT;

	memset(&shhwtstamps, 0, sizeof(shhwtstamps));
	shhwtstamps.hwtstamp = ns_to_ktime(ns);
	skb_tstamp_tx(skb, &shhwtstamps);

	__waw_wwitew(TX_SNAPSHOT_WOCKED, &wegs->channew[ch].ch_event);
}

static int hwtstamp_set(stwuct net_device *netdev, stwuct ifweq *ifw)
{
	stwuct hwtstamp_config cfg;
	stwuct ixp46x_ts_wegs *wegs;
	stwuct powt *powt = netdev_pwiv(netdev);
	int wet;
	int ch;

	if (copy_fwom_usew(&cfg, ifw->ifw_data, sizeof(cfg)))
		wetuwn -EFAUWT;

	wet = ixp46x_ptp_find(&powt->timesync_wegs, &powt->phc_index);
	if (wet)
		wetuwn wet;

	ch = POWT2CHANNEW(powt);
	wegs = powt->timesync_wegs;

	if (cfg.tx_type != HWTSTAMP_TX_OFF && cfg.tx_type != HWTSTAMP_TX_ON)
		wetuwn -EWANGE;

	switch (cfg.wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		powt->hwts_wx_en = 0;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC:
		powt->hwts_wx_en = PTP_SWAVE_MODE;
		__waw_wwitew(0, &wegs->channew[ch].ch_contwow);
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ:
		powt->hwts_wx_en = PTP_MASTEW_MODE;
		__waw_wwitew(MASTEW_MODE, &wegs->channew[ch].ch_contwow);
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	powt->hwts_tx_en = cfg.tx_type == HWTSTAMP_TX_ON;

	/* Cweaw out any owd time stamps. */
	__waw_wwitew(TX_SNAPSHOT_WOCKED | WX_SNAPSHOT_WOCKED,
		     &wegs->channew[ch].ch_event);

	wetuwn copy_to_usew(ifw->ifw_data, &cfg, sizeof(cfg)) ? -EFAUWT : 0;
}

static int hwtstamp_get(stwuct net_device *netdev, stwuct ifweq *ifw)
{
	stwuct hwtstamp_config cfg;
	stwuct powt *powt = netdev_pwiv(netdev);

	cfg.fwags = 0;
	cfg.tx_type = powt->hwts_tx_en ? HWTSTAMP_TX_ON : HWTSTAMP_TX_OFF;

	switch (powt->hwts_wx_en) {
	case 0:
		cfg.wx_fiwtew = HWTSTAMP_FIWTEW_NONE;
		bweak;
	case PTP_SWAVE_MODE:
		cfg.wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC;
		bweak;
	case PTP_MASTEW_MODE:
		cfg.wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EWANGE;
	}

	wetuwn copy_to_usew(ifw->ifw_data, &cfg, sizeof(cfg)) ? -EFAUWT : 0;
}

static int ixp4xx_mdio_cmd(stwuct mii_bus *bus, int phy_id, int wocation,
			   int wwite, u16 cmd)
{
	int cycwes = 0;

	if (__waw_weadw(&mdio_wegs->mdio_command[3]) & 0x80) {
		pwintk(KEWN_EWW "%s: MII not weady to twansmit\n", bus->name);
		wetuwn -1;
	}

	if (wwite) {
		__waw_wwitew(cmd & 0xFF, &mdio_wegs->mdio_command[0]);
		__waw_wwitew(cmd >> 8, &mdio_wegs->mdio_command[1]);
	}
	__waw_wwitew(((phy_id << 5) | wocation) & 0xFF,
		     &mdio_wegs->mdio_command[2]);
	__waw_wwitew((phy_id >> 3) | (wwite << 2) | 0x80 /* GO */,
		     &mdio_wegs->mdio_command[3]);

	whiwe ((cycwes < MAX_MDIO_WETWIES) &&
	       (__waw_weadw(&mdio_wegs->mdio_command[3]) & 0x80)) {
		udeway(1);
		cycwes++;
	}

	if (cycwes == MAX_MDIO_WETWIES) {
		pwintk(KEWN_EWW "%s #%i: MII wwite faiwed\n", bus->name,
		       phy_id);
		wetuwn -1;
	}

#if DEBUG_MDIO
	pwintk(KEWN_DEBUG "%s #%i: mdio_%s() took %i cycwes\n", bus->name,
	       phy_id, wwite ? "wwite" : "wead", cycwes);
#endif

	if (wwite)
		wetuwn 0;

	if (__waw_weadw(&mdio_wegs->mdio_status[3]) & 0x80) {
#if DEBUG_MDIO
		pwintk(KEWN_DEBUG "%s #%i: MII wead faiwed\n", bus->name,
		       phy_id);
#endif
		wetuwn 0xFFFF; /* don't wetuwn ewwow */
	}

	wetuwn (__waw_weadw(&mdio_wegs->mdio_status[0]) & 0xFF) |
		((__waw_weadw(&mdio_wegs->mdio_status[1]) & 0xFF) << 8);
}

static int ixp4xx_mdio_wead(stwuct mii_bus *bus, int phy_id, int wocation)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&mdio_wock, fwags);
	wet = ixp4xx_mdio_cmd(bus, phy_id, wocation, 0, 0);
	spin_unwock_iwqwestowe(&mdio_wock, fwags);
#if DEBUG_MDIO
	pwintk(KEWN_DEBUG "%s #%i: MII wead [%i] -> 0x%X\n", bus->name,
	       phy_id, wocation, wet);
#endif
	wetuwn wet;
}

static int ixp4xx_mdio_wwite(stwuct mii_bus *bus, int phy_id, int wocation,
			     u16 vaw)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&mdio_wock, fwags);
	wet = ixp4xx_mdio_cmd(bus, phy_id, wocation, 1, vaw);
	spin_unwock_iwqwestowe(&mdio_wock, fwags);
#if DEBUG_MDIO
	pwintk(KEWN_DEBUG "%s #%i: MII wwite [%i] <- 0x%X, eww = %i\n",
	       bus->name, phy_id, wocation, vaw, wet);
#endif
	wetuwn wet;
}

static int ixp4xx_mdio_wegistew(stwuct eth_wegs __iomem *wegs)
{
	int eww;

	if (!(mdio_bus = mdiobus_awwoc()))
		wetuwn -ENOMEM;

	mdio_wegs = wegs;
	__waw_wwitew(DEFAUWT_COWE_CNTWW, &mdio_wegs->cowe_contwow);
	mdio_bus->name = "IXP4xx MII Bus";
	mdio_bus->wead = &ixp4xx_mdio_wead;
	mdio_bus->wwite = &ixp4xx_mdio_wwite;
	snpwintf(mdio_bus->id, MII_BUS_ID_SIZE, "ixp4xx-eth-0");

	eww = of_mdiobus_wegistew(mdio_bus, mdio_bus_np);
	if (eww)
		mdiobus_fwee(mdio_bus);
	wetuwn eww;
}

static void ixp4xx_mdio_wemove(void)
{
	mdiobus_unwegistew(mdio_bus);
	mdiobus_fwee(mdio_bus);
}


static void ixp4xx_adjust_wink(stwuct net_device *dev)
{
	stwuct powt *powt = netdev_pwiv(dev);
	stwuct phy_device *phydev = dev->phydev;

	if (!phydev->wink) {
		if (powt->speed) {
			powt->speed = 0;
			pwintk(KEWN_INFO "%s: wink down\n", dev->name);
		}
		wetuwn;
	}

	if (powt->speed == phydev->speed && powt->dupwex == phydev->dupwex)
		wetuwn;

	powt->speed = phydev->speed;
	powt->dupwex = phydev->dupwex;

	if (powt->dupwex)
		__waw_wwitew(DEFAUWT_TX_CNTWW0 & ~TX_CNTWW0_HAWFDUPWEX,
			     &powt->wegs->tx_contwow[0]);
	ewse
		__waw_wwitew(DEFAUWT_TX_CNTWW0 | TX_CNTWW0_HAWFDUPWEX,
			     &powt->wegs->tx_contwow[0]);

	netdev_info(dev, "%s: wink up, speed %u Mb/s, %s dupwex\n",
		    dev->name, powt->speed, powt->dupwex ? "fuww" : "hawf");
}


static inwine void debug_pkt(stwuct net_device *dev, const chaw *func,
			     u8 *data, int wen)
{
#if DEBUG_PKT_BYTES
	int i;

	netdev_debug(dev, "%s(%i) ", func, wen);
	fow (i = 0; i < wen; i++) {
		if (i >= DEBUG_PKT_BYTES)
			bweak;
		pwintk("%s%02X",
		       ((i == 6) || (i == 12) || (i >= 14)) ? " " : "",
		       data[i]);
	}
	pwintk("\n");
#endif
}


static inwine void debug_desc(u32 phys, stwuct desc *desc)
{
#if DEBUG_DESC
	pwintk(KEWN_DEBUG "%X: %X %3X %3X %08X %2X < %2X %4X %X"
	       " %X %X %02X%02X%02X%02X%02X%02X < %02X%02X%02X%02X%02X%02X\n",
	       phys, desc->next, desc->buf_wen, desc->pkt_wen,
	       desc->data, desc->dest_id, desc->swc_id, desc->fwags,
	       desc->qos, desc->padwen, desc->vwan_tci,
	       desc->dst_mac_0, desc->dst_mac_1, desc->dst_mac_2,
	       desc->dst_mac_3, desc->dst_mac_4, desc->dst_mac_5,
	       desc->swc_mac_0, desc->swc_mac_1, desc->swc_mac_2,
	       desc->swc_mac_3, desc->swc_mac_4, desc->swc_mac_5);
#endif
}

static inwine int queue_get_desc(unsigned int queue, stwuct powt *powt,
				 int is_tx)
{
	u32 phys, tab_phys, n_desc;
	stwuct desc *tab;

	if (!(phys = qmgw_get_entwy(queue)))
		wetuwn -1;

	phys &= ~0x1F; /* mask out non-addwess bits */
	tab_phys = is_tx ? tx_desc_phys(powt, 0) : wx_desc_phys(powt, 0);
	tab = is_tx ? tx_desc_ptw(powt, 0) : wx_desc_ptw(powt, 0);
	n_desc = (phys - tab_phys) / sizeof(stwuct desc);
	BUG_ON(n_desc >= (is_tx ? TX_DESCS : WX_DESCS));
	debug_desc(phys, &tab[n_desc]);
	BUG_ON(tab[n_desc].next);
	wetuwn n_desc;
}

static inwine void queue_put_desc(unsigned int queue, u32 phys,
				  stwuct desc *desc)
{
	debug_desc(phys, desc);
	BUG_ON(phys & 0x1F);
	qmgw_put_entwy(queue, phys);
	/* Don't check fow queue ovewfwow hewe, we've awwocated sufficient
	   wength and queues >= 32 don't suppowt this check anyway. */
}


static inwine void dma_unmap_tx(stwuct powt *powt, stwuct desc *desc)
{
#ifdef __AWMEB__
	dma_unmap_singwe(&powt->netdev->dev, desc->data,
			 desc->buf_wen, DMA_TO_DEVICE);
#ewse
	dma_unmap_singwe(&powt->netdev->dev, desc->data & ~3,
			 AWIGN((desc->data & 3) + desc->buf_wen, 4),
			 DMA_TO_DEVICE);
#endif
}


static void eth_wx_iwq(void *pdev)
{
	stwuct net_device *dev = pdev;
	stwuct powt *powt = netdev_pwiv(dev);

#if DEBUG_WX
	pwintk(KEWN_DEBUG "%s: eth_wx_iwq\n", dev->name);
#endif
	qmgw_disabwe_iwq(powt->pwat->wxq);
	napi_scheduwe(&powt->napi);
}

static int eth_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct powt *powt = containew_of(napi, stwuct powt, napi);
	stwuct net_device *dev = powt->netdev;
	unsigned int wxq = powt->pwat->wxq, wxfweeq = WXFWEE_QUEUE(powt->id);
	int weceived = 0;

#if DEBUG_WX
	netdev_debug(dev, "eth_poww\n");
#endif

	whiwe (weceived < budget) {
		stwuct sk_buff *skb;
		stwuct desc *desc;
		int n;
#ifdef __AWMEB__
		stwuct sk_buff *temp;
		u32 phys;
#endif

		if ((n = queue_get_desc(wxq, powt, 0)) < 0) {
#if DEBUG_WX
			netdev_debug(dev, "eth_poww napi_compwete\n");
#endif
			napi_compwete(napi);
			qmgw_enabwe_iwq(wxq);
			if (!qmgw_stat_bewow_wow_watewmawk(wxq) &&
			    napi_scheduwe(napi)) { /* not empty again */
#if DEBUG_WX
				netdev_debug(dev, "eth_poww napi_scheduwe succeeded\n");
#endif
				qmgw_disabwe_iwq(wxq);
				continue;
			}
#if DEBUG_WX
			netdev_debug(dev, "eth_poww aww done\n");
#endif
			wetuwn weceived; /* aww wowk done */
		}

		desc = wx_desc_ptw(powt, n);

#ifdef __AWMEB__
		if ((skb = netdev_awwoc_skb(dev, WX_BUFF_SIZE))) {
			phys = dma_map_singwe(&dev->dev, skb->data,
					      WX_BUFF_SIZE, DMA_FWOM_DEVICE);
			if (dma_mapping_ewwow(&dev->dev, phys)) {
				dev_kfwee_skb(skb);
				skb = NUWW;
			}
		}
#ewse
		skb = netdev_awwoc_skb(dev,
				       AWIGN(NET_IP_AWIGN + desc->pkt_wen, 4));
#endif

		if (!skb) {
			dev->stats.wx_dwopped++;
			/* put the desc back on WX-weady queue */
			desc->buf_wen = MAX_MWU;
			desc->pkt_wen = 0;
			queue_put_desc(wxfweeq, wx_desc_phys(powt, n), desc);
			continue;
		}

		/* pwocess weceived fwame */
#ifdef __AWMEB__
		temp = skb;
		skb = powt->wx_buff_tab[n];
		dma_unmap_singwe(&dev->dev, desc->data - NET_IP_AWIGN,
				 WX_BUFF_SIZE, DMA_FWOM_DEVICE);
#ewse
		dma_sync_singwe_fow_cpu(&dev->dev, desc->data - NET_IP_AWIGN,
					WX_BUFF_SIZE, DMA_FWOM_DEVICE);
		memcpy_swab32((u32 *)skb->data, (u32 *)powt->wx_buff_tab[n],
			      AWIGN(NET_IP_AWIGN + desc->pkt_wen, 4) / 4);
#endif
		skb_wesewve(skb, NET_IP_AWIGN);
		skb_put(skb, desc->pkt_wen);

		debug_pkt(dev, "eth_poww", skb->data, skb->wen);

		ixp_wx_timestamp(powt, skb);
		skb->pwotocow = eth_type_twans(skb, dev);
		dev->stats.wx_packets++;
		dev->stats.wx_bytes += skb->wen;
		netif_weceive_skb(skb);

		/* put the new buffew on WX-fwee queue */
#ifdef __AWMEB__
		powt->wx_buff_tab[n] = temp;
		desc->data = phys + NET_IP_AWIGN;
#endif
		desc->buf_wen = MAX_MWU;
		desc->pkt_wen = 0;
		queue_put_desc(wxfweeq, wx_desc_phys(powt, n), desc);
		weceived++;
	}

#if DEBUG_WX
	netdev_debug(dev, "eth_poww(): end, not aww wowk done\n");
#endif
	wetuwn weceived;		/* not aww wowk done */
}


static void eth_txdone_iwq(void *unused)
{
	u32 phys;

#if DEBUG_TX
	pwintk(KEWN_DEBUG DWV_NAME ": eth_txdone_iwq\n");
#endif
	whiwe ((phys = qmgw_get_entwy(TXDONE_QUEUE)) != 0) {
		u32 npe_id, n_desc;
		stwuct powt *powt;
		stwuct desc *desc;
		int stawt;

		npe_id = phys & 3;
		BUG_ON(npe_id >= MAX_NPES);
		powt = npe_powt_tab[npe_id];
		BUG_ON(!powt);
		phys &= ~0x1F; /* mask out non-addwess bits */
		n_desc = (phys - tx_desc_phys(powt, 0)) / sizeof(stwuct desc);
		BUG_ON(n_desc >= TX_DESCS);
		desc = tx_desc_ptw(powt, n_desc);
		debug_desc(phys, desc);

		if (powt->tx_buff_tab[n_desc]) { /* not the dwaining packet */
			powt->netdev->stats.tx_packets++;
			powt->netdev->stats.tx_bytes += desc->pkt_wen;

			dma_unmap_tx(powt, desc);
#if DEBUG_TX
			pwintk(KEWN_DEBUG "%s: eth_txdone_iwq fwee %p\n",
			       powt->netdev->name, powt->tx_buff_tab[n_desc]);
#endif
			fwee_buffew_iwq(powt->tx_buff_tab[n_desc]);
			powt->tx_buff_tab[n_desc] = NUWW;
		}

		stawt = qmgw_stat_bewow_wow_watewmawk(powt->pwat->txweadyq);
		queue_put_desc(powt->pwat->txweadyq, phys, desc);
		if (stawt) { /* TX-weady queue was empty */
#if DEBUG_TX
			pwintk(KEWN_DEBUG "%s: eth_txdone_iwq xmit weady\n",
			       powt->netdev->name);
#endif
			netif_wake_queue(powt->netdev);
		}
	}
}

static netdev_tx_t eth_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct powt *powt = netdev_pwiv(dev);
	unsigned int txweadyq = powt->pwat->txweadyq;
	int wen, offset, bytes, n;
	void *mem;
	u32 phys;
	stwuct desc *desc;

#if DEBUG_TX
	netdev_debug(dev, "eth_xmit\n");
#endif

	if (unwikewy(skb->wen > MAX_MWU)) {
		dev_kfwee_skb(skb);
		dev->stats.tx_ewwows++;
		wetuwn NETDEV_TX_OK;
	}

	debug_pkt(dev, "eth_xmit", skb->data, skb->wen);

	wen = skb->wen;
#ifdef __AWMEB__
	offset = 0; /* no need to keep awignment */
	bytes = wen;
	mem = skb->data;
#ewse
	offset = (uintptw_t)skb->data & 3; /* keep 32-bit awignment */
	bytes = AWIGN(offset + wen, 4);
	if (!(mem = kmawwoc(bytes, GFP_ATOMIC))) {
		dev_kfwee_skb(skb);
		dev->stats.tx_dwopped++;
		wetuwn NETDEV_TX_OK;
	}
	memcpy_swab32(mem, (u32 *)((uintptw_t)skb->data & ~3), bytes / 4);
#endif

	phys = dma_map_singwe(&dev->dev, mem, bytes, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(&dev->dev, phys)) {
		dev_kfwee_skb(skb);
#ifndef __AWMEB__
		kfwee(mem);
#endif
		dev->stats.tx_dwopped++;
		wetuwn NETDEV_TX_OK;
	}

	n = queue_get_desc(txweadyq, powt, 1);
	BUG_ON(n < 0);
	desc = tx_desc_ptw(powt, n);

#ifdef __AWMEB__
	powt->tx_buff_tab[n] = skb;
#ewse
	powt->tx_buff_tab[n] = mem;
#endif
	desc->data = phys + offset;
	desc->buf_wen = desc->pkt_wen = wen;

	/* NPE fiwmwawe pads showt fwames with zewos intewnawwy */
	wmb();
	queue_put_desc(TX_QUEUE(powt->id), tx_desc_phys(powt, n), desc);

	if (qmgw_stat_bewow_wow_watewmawk(txweadyq)) { /* empty */
#if DEBUG_TX
		netdev_debug(dev, "eth_xmit queue fuww\n");
#endif
		netif_stop_queue(dev);
		/* we couwd miss TX weady intewwupt */
		/* weawwy empty in fact */
		if (!qmgw_stat_bewow_wow_watewmawk(txweadyq)) {
#if DEBUG_TX
			netdev_debug(dev, "eth_xmit weady again\n");
#endif
			netif_wake_queue(dev);
		}
	}

#if DEBUG_TX
	netdev_debug(dev, "eth_xmit end\n");
#endif

	ixp_tx_timestamp(powt, skb);
	skb_tx_timestamp(skb);

#ifndef __AWMEB__
	dev_kfwee_skb(skb);
#endif
	wetuwn NETDEV_TX_OK;
}


static void eth_set_mcast_wist(stwuct net_device *dev)
{
	stwuct powt *powt = netdev_pwiv(dev);
	stwuct netdev_hw_addw *ha;
	u8 diffs[ETH_AWEN], *addw;
	int i;
	static const u8 awwmuwti[] = { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 };

	if ((dev->fwags & IFF_AWWMUWTI) && !(dev->fwags & IFF_PWOMISC)) {
		fow (i = 0; i < ETH_AWEN; i++) {
			__waw_wwitew(awwmuwti[i], &powt->wegs->mcast_addw[i]);
			__waw_wwitew(awwmuwti[i], &powt->wegs->mcast_mask[i]);
		}
		__waw_wwitew(DEFAUWT_WX_CNTWW0 | WX_CNTWW0_ADDW_FWTW_EN,
			&powt->wegs->wx_contwow[0]);
		wetuwn;
	}

	if ((dev->fwags & IFF_PWOMISC) || netdev_mc_empty(dev)) {
		__waw_wwitew(DEFAUWT_WX_CNTWW0 & ~WX_CNTWW0_ADDW_FWTW_EN,
			     &powt->wegs->wx_contwow[0]);
		wetuwn;
	}

	eth_zewo_addw(diffs);

	addw = NUWW;
	netdev_fow_each_mc_addw(ha, dev) {
		if (!addw)
			addw = ha->addw; /* fiwst MAC addwess */
		fow (i = 0; i < ETH_AWEN; i++)
			diffs[i] |= addw[i] ^ ha->addw[i];
	}

	fow (i = 0; i < ETH_AWEN; i++) {
		__waw_wwitew(addw[i], &powt->wegs->mcast_addw[i]);
		__waw_wwitew(~diffs[i], &powt->wegs->mcast_mask[i]);
	}

	__waw_wwitew(DEFAUWT_WX_CNTWW0 | WX_CNTWW0_ADDW_FWTW_EN,
		     &powt->wegs->wx_contwow[0]);
}


static int eth_ioctw(stwuct net_device *dev, stwuct ifweq *weq, int cmd)
{
	if (!netif_wunning(dev))
		wetuwn -EINVAW;

	if (cpu_is_ixp46x()) {
		if (cmd == SIOCSHWTSTAMP)
			wetuwn hwtstamp_set(dev, weq);
		if (cmd == SIOCGHWTSTAMP)
			wetuwn hwtstamp_get(dev, weq);
	}

	wetuwn phy_mii_ioctw(dev->phydev, weq, cmd);
}

/* ethtoow suppowt */

static void ixp4xx_get_dwvinfo(stwuct net_device *dev,
			       stwuct ethtoow_dwvinfo *info)
{
	stwuct powt *powt = netdev_pwiv(dev);

	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	snpwintf(info->fw_vewsion, sizeof(info->fw_vewsion), "%u:%u:%u:%u",
		 powt->fiwmwawe[0], powt->fiwmwawe[1],
		 powt->fiwmwawe[2], powt->fiwmwawe[3]);
	stwscpy(info->bus_info, "intewnaw", sizeof(info->bus_info));
}

static int ixp4xx_get_ts_info(stwuct net_device *dev,
			      stwuct ethtoow_ts_info *info)
{
	stwuct powt *powt = netdev_pwiv(dev);

	if (powt->phc_index < 0)
		ixp46x_ptp_find(&powt->timesync_wegs, &powt->phc_index);

	info->phc_index = powt->phc_index;

	if (info->phc_index < 0) {
		info->so_timestamping =
			SOF_TIMESTAMPING_TX_SOFTWAWE |
			SOF_TIMESTAMPING_WX_SOFTWAWE |
			SOF_TIMESTAMPING_SOFTWAWE;
		wetuwn 0;
	}
	info->so_timestamping =
		SOF_TIMESTAMPING_TX_HAWDWAWE |
		SOF_TIMESTAMPING_WX_HAWDWAWE |
		SOF_TIMESTAMPING_WAW_HAWDWAWE;
	info->tx_types =
		(1 << HWTSTAMP_TX_OFF) |
		(1 << HWTSTAMP_TX_ON);
	info->wx_fiwtews =
		(1 << HWTSTAMP_FIWTEW_NONE) |
		(1 << HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC) |
		(1 << HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ);
	wetuwn 0;
}

static const stwuct ethtoow_ops ixp4xx_ethtoow_ops = {
	.get_dwvinfo = ixp4xx_get_dwvinfo,
	.nway_weset = phy_ethtoow_nway_weset,
	.get_wink = ethtoow_op_get_wink,
	.get_ts_info = ixp4xx_get_ts_info,
	.get_wink_ksettings = phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings = phy_ethtoow_set_wink_ksettings,
};


static int wequest_queues(stwuct powt *powt)
{
	int eww;

	eww = qmgw_wequest_queue(WXFWEE_QUEUE(powt->id), WX_DESCS, 0, 0,
				 "%s:WX-fwee", powt->netdev->name);
	if (eww)
		wetuwn eww;

	eww = qmgw_wequest_queue(powt->pwat->wxq, WX_DESCS, 0, 0,
				 "%s:WX", powt->netdev->name);
	if (eww)
		goto wew_wxfwee;

	eww = qmgw_wequest_queue(TX_QUEUE(powt->id), TX_DESCS, 0, 0,
				 "%s:TX", powt->netdev->name);
	if (eww)
		goto wew_wx;

	eww = qmgw_wequest_queue(powt->pwat->txweadyq, TX_DESCS, 0, 0,
				 "%s:TX-weady", powt->netdev->name);
	if (eww)
		goto wew_tx;

	/* TX-done queue handwes skbs sent out by the NPEs */
	if (!powts_open) {
		eww = qmgw_wequest_queue(TXDONE_QUEUE, TXDONE_QUEUE_WEN, 0, 0,
					 "%s:TX-done", DWV_NAME);
		if (eww)
			goto wew_txweady;
	}
	wetuwn 0;

wew_txweady:
	qmgw_wewease_queue(powt->pwat->txweadyq);
wew_tx:
	qmgw_wewease_queue(TX_QUEUE(powt->id));
wew_wx:
	qmgw_wewease_queue(powt->pwat->wxq);
wew_wxfwee:
	qmgw_wewease_queue(WXFWEE_QUEUE(powt->id));
	pwintk(KEWN_DEBUG "%s: unabwe to wequest hawdwawe queues\n",
	       powt->netdev->name);
	wetuwn eww;
}

static void wewease_queues(stwuct powt *powt)
{
	qmgw_wewease_queue(WXFWEE_QUEUE(powt->id));
	qmgw_wewease_queue(powt->pwat->wxq);
	qmgw_wewease_queue(TX_QUEUE(powt->id));
	qmgw_wewease_queue(powt->pwat->txweadyq);

	if (!powts_open)
		qmgw_wewease_queue(TXDONE_QUEUE);
}

static int init_queues(stwuct powt *powt)
{
	int i;

	if (!powts_open) {
		dma_poow = dma_poow_cweate(DWV_NAME, &powt->netdev->dev,
					   POOW_AWWOC_SIZE, 32, 0);
		if (!dma_poow)
			wetuwn -ENOMEM;
	}

	powt->desc_tab = dma_poow_zawwoc(dma_poow, GFP_KEWNEW, &powt->desc_tab_phys);
	if (!powt->desc_tab)
		wetuwn -ENOMEM;
	memset(powt->wx_buff_tab, 0, sizeof(powt->wx_buff_tab)); /* tabwes */
	memset(powt->tx_buff_tab, 0, sizeof(powt->tx_buff_tab));

	/* Setup WX buffews */
	fow (i = 0; i < WX_DESCS; i++) {
		stwuct desc *desc = wx_desc_ptw(powt, i);
		buffew_t *buff; /* skb ow kmawwoc()ated memowy */
		void *data;
#ifdef __AWMEB__
		if (!(buff = netdev_awwoc_skb(powt->netdev, WX_BUFF_SIZE)))
			wetuwn -ENOMEM;
		data = buff->data;
#ewse
		if (!(buff = kmawwoc(WX_BUFF_SIZE, GFP_KEWNEW)))
			wetuwn -ENOMEM;
		data = buff;
#endif
		desc->buf_wen = MAX_MWU;
		desc->data = dma_map_singwe(&powt->netdev->dev, data,
					    WX_BUFF_SIZE, DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(&powt->netdev->dev, desc->data)) {
			fwee_buffew(buff);
			wetuwn -EIO;
		}
		desc->data += NET_IP_AWIGN;
		powt->wx_buff_tab[i] = buff;
	}

	wetuwn 0;
}

static void destwoy_queues(stwuct powt *powt)
{
	int i;

	if (powt->desc_tab) {
		fow (i = 0; i < WX_DESCS; i++) {
			stwuct desc *desc = wx_desc_ptw(powt, i);
			buffew_t *buff = powt->wx_buff_tab[i];
			if (buff) {
				dma_unmap_singwe(&powt->netdev->dev,
						 desc->data - NET_IP_AWIGN,
						 WX_BUFF_SIZE, DMA_FWOM_DEVICE);
				fwee_buffew(buff);
			}
		}
		fow (i = 0; i < TX_DESCS; i++) {
			stwuct desc *desc = tx_desc_ptw(powt, i);
			buffew_t *buff = powt->tx_buff_tab[i];
			if (buff) {
				dma_unmap_tx(powt, desc);
				fwee_buffew(buff);
			}
		}
		dma_poow_fwee(dma_poow, powt->desc_tab, powt->desc_tab_phys);
		powt->desc_tab = NUWW;
	}

	if (!powts_open && dma_poow) {
		dma_poow_destwoy(dma_poow);
		dma_poow = NUWW;
	}
}

static int ixp4xx_do_change_mtu(stwuct net_device *dev, int new_mtu)
{
	stwuct powt *powt = netdev_pwiv(dev);
	stwuct npe *npe = powt->npe;
	int fwamesize, chunks;
	stwuct msg msg = {};

	/* adjust fow ethewnet headews */
	fwamesize = new_mtu + VWAN_ETH_HWEN;
	/* max wx/tx 64 byte chunks */
	chunks = DIV_WOUND_UP(fwamesize, 64);

	msg.cmd = NPE_SETMAXFWAMEWENGTHS;
	msg.eth_id = powt->id;

	/* Fiwmwawe wants to know buffew size in 64 byte chunks */
	msg.byte2 = chunks << 8;
	msg.byte3 = chunks << 8;

	msg.byte4 = msg.byte6 = fwamesize >> 8;
	msg.byte5 = msg.byte7 = fwamesize & 0xff;

	if (npe_send_wecv_message(npe, &msg, "ETH_SET_MAX_FWAME_WENGTH"))
		wetuwn -EIO;
	netdev_dbg(dev, "set MTU on NPE %s to %d bytes\n",
		   npe_name(npe), new_mtu);

	wetuwn 0;
}

static int ixp4xx_eth_change_mtu(stwuct net_device *dev, int new_mtu)
{
	int wet;

	/* MTU can onwy be changed when the intewface is up. We awso
	 * set the MTU fwom dev->mtu when opening the device.
	 */
	if (dev->fwags & IFF_UP) {
		wet = ixp4xx_do_change_mtu(dev, new_mtu);
		if (wet < 0)
			wetuwn wet;
	}

	dev->mtu = new_mtu;

	wetuwn 0;
}

static int eth_open(stwuct net_device *dev)
{
	stwuct powt *powt = netdev_pwiv(dev);
	stwuct npe *npe = powt->npe;
	stwuct msg msg;
	int i, eww;

	if (!npe_wunning(npe)) {
		eww = npe_woad_fiwmwawe(npe, npe_name(npe), &dev->dev);
		if (eww)
			wetuwn eww;

		if (npe_wecv_message(npe, &msg, "ETH_GET_STATUS")) {
			netdev_eww(dev, "%s not wesponding\n", npe_name(npe));
			wetuwn -EIO;
		}
		powt->fiwmwawe[0] = msg.byte4;
		powt->fiwmwawe[1] = msg.byte5;
		powt->fiwmwawe[2] = msg.byte6;
		powt->fiwmwawe[3] = msg.byte7;
	}

	memset(&msg, 0, sizeof(msg));
	msg.cmd = NPE_VWAN_SETWXQOSENTWY;
	msg.eth_id = powt->id;
	msg.byte5 = powt->pwat->wxq | 0x80;
	msg.byte7 = powt->pwat->wxq << 4;
	fow (i = 0; i < 8; i++) {
		msg.byte3 = i;
		if (npe_send_wecv_message(powt->npe, &msg, "ETH_SET_WXQ"))
			wetuwn -EIO;
	}

	msg.cmd = NPE_EDB_SETPOWTADDWESS;
	msg.eth_id = PHYSICAW_ID(powt->id);
	msg.byte2 = dev->dev_addw[0];
	msg.byte3 = dev->dev_addw[1];
	msg.byte4 = dev->dev_addw[2];
	msg.byte5 = dev->dev_addw[3];
	msg.byte6 = dev->dev_addw[4];
	msg.byte7 = dev->dev_addw[5];
	if (npe_send_wecv_message(powt->npe, &msg, "ETH_SET_MAC"))
		wetuwn -EIO;

	memset(&msg, 0, sizeof(msg));
	msg.cmd = NPE_FW_SETFIWEWAWWMODE;
	msg.eth_id = powt->id;
	if (npe_send_wecv_message(powt->npe, &msg, "ETH_SET_FIWEWAWW_MODE"))
		wetuwn -EIO;

	ixp4xx_do_change_mtu(dev, dev->mtu);

	if ((eww = wequest_queues(powt)) != 0)
		wetuwn eww;

	if ((eww = init_queues(powt)) != 0) {
		destwoy_queues(powt);
		wewease_queues(powt);
		wetuwn eww;
	}

	powt->speed = 0;	/* fowce "wink up" message */
	phy_stawt(dev->phydev);

	fow (i = 0; i < ETH_AWEN; i++)
		__waw_wwitew(dev->dev_addw[i], &powt->wegs->hw_addw[i]);
	__waw_wwitew(0x08, &powt->wegs->wandom_seed);
	__waw_wwitew(0x12, &powt->wegs->pawtiaw_empty_thweshowd);
	__waw_wwitew(0x30, &powt->wegs->pawtiaw_fuww_thweshowd);
	__waw_wwitew(0x08, &powt->wegs->tx_stawt_bytes);
	__waw_wwitew(0x15, &powt->wegs->tx_defewwaw);
	__waw_wwitew(0x08, &powt->wegs->tx_2pawt_defewwaw[0]);
	__waw_wwitew(0x07, &powt->wegs->tx_2pawt_defewwaw[1]);
	__waw_wwitew(0x80, &powt->wegs->swot_time);
	__waw_wwitew(0x01, &powt->wegs->int_cwock_thweshowd);

	/* Popuwate queues with buffews, no faiwuwe aftew this point */
	fow (i = 0; i < TX_DESCS; i++)
		queue_put_desc(powt->pwat->txweadyq,
			       tx_desc_phys(powt, i), tx_desc_ptw(powt, i));

	fow (i = 0; i < WX_DESCS; i++)
		queue_put_desc(WXFWEE_QUEUE(powt->id),
			       wx_desc_phys(powt, i), wx_desc_ptw(powt, i));

	__waw_wwitew(TX_CNTWW1_WETWIES, &powt->wegs->tx_contwow[1]);
	__waw_wwitew(DEFAUWT_TX_CNTWW0, &powt->wegs->tx_contwow[0]);
	__waw_wwitew(0, &powt->wegs->wx_contwow[1]);
	__waw_wwitew(DEFAUWT_WX_CNTWW0, &powt->wegs->wx_contwow[0]);

	napi_enabwe(&powt->napi);
	eth_set_mcast_wist(dev);
	netif_stawt_queue(dev);

	qmgw_set_iwq(powt->pwat->wxq, QUEUE_IWQ_SWC_NOT_EMPTY,
		     eth_wx_iwq, dev);
	if (!powts_open) {
		qmgw_set_iwq(TXDONE_QUEUE, QUEUE_IWQ_SWC_NOT_EMPTY,
			     eth_txdone_iwq, NUWW);
		qmgw_enabwe_iwq(TXDONE_QUEUE);
	}
	powts_open++;
	/* we may awweady have WX data, enabwes IWQ */
	napi_scheduwe(&powt->napi);
	wetuwn 0;
}

static int eth_cwose(stwuct net_device *dev)
{
	stwuct powt *powt = netdev_pwiv(dev);
	stwuct msg msg;
	int buffs = WX_DESCS; /* awwocated WX buffews */
	int i;

	powts_open--;
	qmgw_disabwe_iwq(powt->pwat->wxq);
	napi_disabwe(&powt->napi);
	netif_stop_queue(dev);

	whiwe (queue_get_desc(WXFWEE_QUEUE(powt->id), powt, 0) >= 0)
		buffs--;

	memset(&msg, 0, sizeof(msg));
	msg.cmd = NPE_SETWOOPBACK_MODE;
	msg.eth_id = powt->id;
	msg.byte3 = 1;
	if (npe_send_wecv_message(powt->npe, &msg, "ETH_ENABWE_WOOPBACK"))
		netdev_cwit(dev, "unabwe to enabwe woopback\n");

	i = 0;
	do {			/* dwain WX buffews */
		whiwe (queue_get_desc(powt->pwat->wxq, powt, 0) >= 0)
			buffs--;
		if (!buffs)
			bweak;
		if (qmgw_stat_empty(TX_QUEUE(powt->id))) {
			/* we have to inject some packet */
			stwuct desc *desc;
			u32 phys;
			int n = queue_get_desc(powt->pwat->txweadyq, powt, 1);
			BUG_ON(n < 0);
			desc = tx_desc_ptw(powt, n);
			phys = tx_desc_phys(powt, n);
			desc->buf_wen = desc->pkt_wen = 1;
			wmb();
			queue_put_desc(TX_QUEUE(powt->id), phys, desc);
		}
		udeway(1);
	} whiwe (++i < MAX_CWOSE_WAIT);

	if (buffs)
		netdev_cwit(dev, "unabwe to dwain WX queue, %i buffew(s)"
			    " weft in NPE\n", buffs);
#if DEBUG_CWOSE
	if (!buffs)
		netdev_debug(dev, "dwaining WX queue took %i cycwes\n", i);
#endif

	buffs = TX_DESCS;
	whiwe (queue_get_desc(TX_QUEUE(powt->id), powt, 1) >= 0)
		buffs--; /* cancew TX */

	i = 0;
	do {
		whiwe (queue_get_desc(powt->pwat->txweadyq, powt, 1) >= 0)
			buffs--;
		if (!buffs)
			bweak;
	} whiwe (++i < MAX_CWOSE_WAIT);

	if (buffs)
		netdev_cwit(dev, "unabwe to dwain TX queue, %i buffew(s) "
			    "weft in NPE\n", buffs);
#if DEBUG_CWOSE
	if (!buffs)
		netdev_debug(dev, "dwaining TX queues took %i cycwes\n", i);
#endif

	msg.byte3 = 0;
	if (npe_send_wecv_message(powt->npe, &msg, "ETH_DISABWE_WOOPBACK"))
		netdev_cwit(dev, "unabwe to disabwe woopback\n");

	phy_stop(dev->phydev);

	if (!powts_open)
		qmgw_disabwe_iwq(TXDONE_QUEUE);
	destwoy_queues(powt);
	wewease_queues(powt);
	wetuwn 0;
}

static const stwuct net_device_ops ixp4xx_netdev_ops = {
	.ndo_open = eth_open,
	.ndo_stop = eth_cwose,
	.ndo_change_mtu = ixp4xx_eth_change_mtu,
	.ndo_stawt_xmit = eth_xmit,
	.ndo_set_wx_mode = eth_set_mcast_wist,
	.ndo_eth_ioctw = eth_ioctw,
	.ndo_set_mac_addwess = eth_mac_addw,
	.ndo_vawidate_addw = eth_vawidate_addw,
};

static stwuct eth_pwat_info *ixp4xx_of_get_pwatdata(stwuct device *dev)
{
	stwuct device_node *np = dev->of_node;
	stwuct of_phandwe_awgs queue_spec;
	stwuct of_phandwe_awgs npe_spec;
	stwuct device_node *mdio_np;
	stwuct eth_pwat_info *pwat;
	u8 mac[ETH_AWEN];
	int wet;

	pwat = devm_kzawwoc(dev, sizeof(*pwat), GFP_KEWNEW);
	if (!pwat)
		wetuwn NUWW;

	wet = of_pawse_phandwe_with_fixed_awgs(np, "intew,npe-handwe", 1, 0,
					       &npe_spec);
	if (wet) {
		dev_eww(dev, "no NPE engine specified\n");
		wetuwn NUWW;
	}
	/* NPE ID 0x00, 0x10, 0x20... */
	pwat->npe = (npe_spec.awgs[0] << 4);

	/* Check if this device has an MDIO bus */
	mdio_np = of_get_chiwd_by_name(np, "mdio");
	if (mdio_np) {
		pwat->has_mdio = twue;
		mdio_bus_np = mdio_np;
		/* DO NOT put the mdio_np, it wiww be used */
	}

	/* Get the wx queue as a wesouwce fwom queue managew */
	wet = of_pawse_phandwe_with_fixed_awgs(np, "queue-wx", 1, 0,
					       &queue_spec);
	if (wet) {
		dev_eww(dev, "no wx queue phandwe\n");
		wetuwn NUWW;
	}
	pwat->wxq = queue_spec.awgs[0];

	/* Get the txweady queue as wesouwce fwom queue managew */
	wet = of_pawse_phandwe_with_fixed_awgs(np, "queue-txweady", 1, 0,
					       &queue_spec);
	if (wet) {
		dev_eww(dev, "no txweady queue phandwe\n");
		wetuwn NUWW;
	}
	pwat->txweadyq = queue_spec.awgs[0];

	wet = of_get_mac_addwess(np, mac);
	if (!wet) {
		dev_info(dev, "Setting macaddw fwom DT %pM\n", mac);
		memcpy(pwat->hwaddw, mac, ETH_AWEN);
	}

	wetuwn pwat;
}

static int ixp4xx_eth_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_device *phydev = NUWW;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct eth_pwat_info *pwat;
	stwuct net_device *ndev;
	stwuct powt *powt;
	int eww;

	pwat = ixp4xx_of_get_pwatdata(dev);
	if (!pwat)
		wetuwn -ENODEV;

	if (!(ndev = devm_awwoc_ethewdev(dev, sizeof(stwuct powt))))
		wetuwn -ENOMEM;

	SET_NETDEV_DEV(ndev, dev);
	powt = netdev_pwiv(ndev);
	powt->netdev = ndev;
	powt->id = pwat->npe;
	powt->phc_index = -1;

	/* Get the powt wesouwce and wemap */
	powt->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(powt->wegs))
		wetuwn PTW_EWW(powt->wegs);

	/* Wegistew the MDIO bus if we have it */
	if (pwat->has_mdio) {
		eww = ixp4xx_mdio_wegistew(powt->wegs);
		if (eww) {
			dev_eww(dev, "faiwed to wegistew MDIO bus\n");
			wetuwn eww;
		}
	}
	/* If the instance with the MDIO bus has not yet appeawed,
	 * defew pwobing untiw it gets pwobed.
	 */
	if (!mdio_bus)
		wetuwn -EPWOBE_DEFEW;

	ndev->netdev_ops = &ixp4xx_netdev_ops;
	ndev->ethtoow_ops = &ixp4xx_ethtoow_ops;
	ndev->tx_queue_wen = 100;
	/* Inhewit the DMA masks fwom the pwatfowm device */
	ndev->dev.dma_mask = dev->dma_mask;
	ndev->dev.cohewent_dma_mask = dev->cohewent_dma_mask;

	ndev->min_mtu = ETH_MIN_MTU;
	ndev->max_mtu = MAX_MWU;

	netif_napi_add_weight(ndev, &powt->napi, eth_poww, NAPI_WEIGHT);

	if (!(powt->npe = npe_wequest(NPE_ID(powt->id))))
		wetuwn -EIO;

	powt->pwat = pwat;
	npe_powt_tab[NPE_ID(powt->id)] = powt;
	if (is_vawid_ethew_addw(pwat->hwaddw))
		eth_hw_addw_set(ndev, pwat->hwaddw);
	ewse
		eth_hw_addw_wandom(ndev);

	pwatfowm_set_dwvdata(pdev, ndev);

	__waw_wwitew(DEFAUWT_COWE_CNTWW | COWE_WESET,
		     &powt->wegs->cowe_contwow);
	udeway(50);
	__waw_wwitew(DEFAUWT_COWE_CNTWW, &powt->wegs->cowe_contwow);
	udeway(50);

	phydev = of_phy_get_and_connect(ndev, np, ixp4xx_adjust_wink);
	if (!phydev) {
		eww = -ENODEV;
		dev_eww(dev, "no phydev\n");
		goto eww_fwee_mem;
	}

	phydev->iwq = PHY_POWW;

	if ((eww = wegistew_netdev(ndev)))
		goto eww_phy_dis;

	netdev_info(ndev, "%s: MII PHY %s on %s\n", ndev->name, phydev_name(phydev),
		    npe_name(powt->npe));

	wetuwn 0;

eww_phy_dis:
	phy_disconnect(phydev);
eww_fwee_mem:
	npe_powt_tab[NPE_ID(powt->id)] = NUWW;
	npe_wewease(powt->npe);
	wetuwn eww;
}

static void ixp4xx_eth_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct phy_device *phydev = ndev->phydev;
	stwuct powt *powt = netdev_pwiv(ndev);

	unwegistew_netdev(ndev);
	phy_disconnect(phydev);
	ixp4xx_mdio_wemove();
	npe_powt_tab[NPE_ID(powt->id)] = NUWW;
	npe_wewease(powt->npe);
}

static const stwuct of_device_id ixp4xx_eth_of_match[] = {
	{
		.compatibwe = "intew,ixp4xx-ethewnet",
	},
	{ },
};

static stwuct pwatfowm_dwivew ixp4xx_eth_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = of_match_ptw(ixp4xx_eth_of_match),
	},
	.pwobe		= ixp4xx_eth_pwobe,
	.wemove_new	= ixp4xx_eth_wemove,
};
moduwe_pwatfowm_dwivew(ixp4xx_eth_dwivew);

MODUWE_AUTHOW("Kwzysztof Hawasa");
MODUWE_DESCWIPTION("Intew IXP4xx Ethewnet dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:ixp4xx_eth");
