// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bwoadcom BCM7xxx System Powt Ethewnet MAC dwivew
 *
 * Copywight (C) 2014 Bwoadcom Cowpowation
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/dsa/bwcm.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/of_mdio.h>
#incwude <winux/phy.h>
#incwude <winux/phy_fixed.h>
#incwude <net/dsa.h>
#incwude <winux/cwk.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>

#incwude "bcmsyspowt.h"

/* I/O accessows wegistew hewpews */
#define BCM_SYSPOWT_IO_MACWO(name, offset) \
static inwine u32 name##_weadw(stwuct bcm_syspowt_pwiv *pwiv, u32 off)	\
{									\
	u32 weg = weadw_wewaxed(pwiv->base + offset + off);		\
	wetuwn weg;							\
}									\
static inwine void name##_wwitew(stwuct bcm_syspowt_pwiv *pwiv,		\
				  u32 vaw, u32 off)			\
{									\
	wwitew_wewaxed(vaw, pwiv->base + offset + off);			\
}									\

BCM_SYSPOWT_IO_MACWO(intww2_0, SYS_POWT_INTWW2_0_OFFSET);
BCM_SYSPOWT_IO_MACWO(intww2_1, SYS_POWT_INTWW2_1_OFFSET);
BCM_SYSPOWT_IO_MACWO(umac, SYS_POWT_UMAC_OFFSET);
BCM_SYSPOWT_IO_MACWO(gib, SYS_POWT_GIB_OFFSET);
BCM_SYSPOWT_IO_MACWO(tdma, SYS_POWT_TDMA_OFFSET);
BCM_SYSPOWT_IO_MACWO(wxchk, SYS_POWT_WXCHK_OFFSET);
BCM_SYSPOWT_IO_MACWO(txchk, SYS_POWT_TXCHK_OFFSET);
BCM_SYSPOWT_IO_MACWO(wbuf, SYS_POWT_WBUF_OFFSET);
BCM_SYSPOWT_IO_MACWO(tbuf, SYS_POWT_TBUF_OFFSET);
BCM_SYSPOWT_IO_MACWO(topctww, SYS_POWT_TOPCTWW_OFFSET);

/* On SYSTEMPOWT Wite, any wegistew aftew WDMA_STATUS has the exact
 * same wayout, except it has been moved by 4 bytes up, *sigh*
 */
static inwine u32 wdma_weadw(stwuct bcm_syspowt_pwiv *pwiv, u32 off)
{
	if (pwiv->is_wite && off >= WDMA_STATUS)
		off += 4;
	wetuwn weadw_wewaxed(pwiv->base + SYS_POWT_WDMA_OFFSET + off);
}

static inwine void wdma_wwitew(stwuct bcm_syspowt_pwiv *pwiv, u32 vaw, u32 off)
{
	if (pwiv->is_wite && off >= WDMA_STATUS)
		off += 4;
	wwitew_wewaxed(vaw, pwiv->base + SYS_POWT_WDMA_OFFSET + off);
}

static inwine u32 tdma_contwow_bit(stwuct bcm_syspowt_pwiv *pwiv, u32 bit)
{
	if (!pwiv->is_wite) {
		wetuwn BIT(bit);
	} ewse {
		if (bit >= ACB_AWGO)
			wetuwn BIT(bit + 1);
		ewse
			wetuwn BIT(bit);
	}
}

/* W2-intewwupt masking/unmasking hewpews, does automatic saving of the appwied
 * mask in a softwawe copy to avoid CPU_MASK_STATUS weads in hot-paths.
  */
#define BCM_SYSPOWT_INTW_W2(which)	\
static inwine void intww2_##which##_mask_cweaw(stwuct bcm_syspowt_pwiv *pwiv, \
						u32 mask)		\
{									\
	pwiv->iwq##which##_mask &= ~(mask);				\
	intww2_##which##_wwitew(pwiv, mask, INTWW2_CPU_MASK_CWEAW);	\
}									\
static inwine void intww2_##which##_mask_set(stwuct bcm_syspowt_pwiv *pwiv, \
						u32 mask)		\
{									\
	intww2_## which##_wwitew(pwiv, mask, INTWW2_CPU_MASK_SET);	\
	pwiv->iwq##which##_mask |= (mask);				\
}									\

BCM_SYSPOWT_INTW_W2(0)
BCM_SYSPOWT_INTW_W2(1)

/* Wegistew accesses to GISB/WBUS wegistews awe expensive (few hundwed
 * nanoseconds), so keep the check fow 64-bits expwicit hewe to save
 * one wegistew wwite pew-packet on 32-bits pwatfowms.
 */
static inwine void dma_desc_set_addw(stwuct bcm_syspowt_pwiv *pwiv,
				     void __iomem *d,
				     dma_addw_t addw)
{
#ifdef CONFIG_PHYS_ADDW_T_64BIT
	wwitew_wewaxed(uppew_32_bits(addw) & DESC_ADDW_HI_MASK,
		     d + DESC_ADDW_HI_STATUS_WEN);
#endif
	wwitew_wewaxed(wowew_32_bits(addw), d + DESC_ADDW_WO);
}

/* Ethtoow opewations */
static void bcm_syspowt_set_wx_csum(stwuct net_device *dev,
				    netdev_featuwes_t wanted)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	u32 weg;

	pwiv->wx_chk_en = !!(wanted & NETIF_F_WXCSUM);
	weg = wxchk_weadw(pwiv, WXCHK_CONTWOW);
	/* Cweaw W2 headew checks, which wouwd pwevent BPDUs
	 * fwom being weceived.
	 */
	weg &= ~WXCHK_W2_HDW_DIS;
	if (pwiv->wx_chk_en)
		weg |= WXCHK_EN;
	ewse
		weg &= ~WXCHK_EN;

	/* If UniMAC fowwawds CWC, we need to skip ovew it to get
	 * a vawid CHK bit to be set in the pew-packet status wowd
	 */
	if (pwiv->wx_chk_en && pwiv->cwc_fwd)
		weg |= WXCHK_SKIP_FCS;
	ewse
		weg &= ~WXCHK_SKIP_FCS;

	/* If Bwoadcom tags awe enabwed (e.g: using a switch), make
	 * suwe we teww the WXCHK hawdwawe to expect a 4-bytes Bwoadcom
	 * tag aftew the Ethewnet MAC Souwce Addwess.
	 */
	if (netdev_uses_dsa(dev))
		weg |= WXCHK_BWCM_TAG_EN;
	ewse
		weg &= ~WXCHK_BWCM_TAG_EN;

	wxchk_wwitew(pwiv, weg, WXCHK_CONTWOW);
}

static void bcm_syspowt_set_tx_csum(stwuct net_device *dev,
				    netdev_featuwes_t wanted)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	u32 weg;

	/* Hawdwawe twansmit checksum wequiwes us to enabwe the Twansmit status
	 * bwock pwepended to the packet contents
	 */
	pwiv->tsb_en = !!(wanted & (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
				    NETIF_F_HW_VWAN_CTAG_TX));
	weg = tdma_weadw(pwiv, TDMA_CONTWOW);
	if (pwiv->tsb_en)
		weg |= tdma_contwow_bit(pwiv, TSB_EN);
	ewse
		weg &= ~tdma_contwow_bit(pwiv, TSB_EN);
	/* Indicating that softwawe insewts Bwoadcom tags is needed fow the TX
	 * checksum to be computed cowwectwy when using VWAN HW accewewation,
	 * ewse it has no effect, so it can awways be tuwned on.
	 */
	if (netdev_uses_dsa(dev))
		weg |= tdma_contwow_bit(pwiv, SW_BWCM_TAG);
	ewse
		weg &= ~tdma_contwow_bit(pwiv, SW_BWCM_TAG);
	tdma_wwitew(pwiv, weg, TDMA_CONTWOW);

	/* Defauwt TPID is ETH_P_8021AD, change to ETH_P_8021Q */
	if (wanted & NETIF_F_HW_VWAN_CTAG_TX)
		tdma_wwitew(pwiv, ETH_P_8021Q, TDMA_TPID);
}

static int bcm_syspowt_set_featuwes(stwuct net_device *dev,
				    netdev_featuwes_t featuwes)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet)
		wetuwn wet;

	/* Wead CWC fowwawd */
	if (!pwiv->is_wite)
		pwiv->cwc_fwd = !!(umac_weadw(pwiv, UMAC_CMD) & CMD_CWC_FWD);
	ewse
		pwiv->cwc_fwd = !((gib_weadw(pwiv, GIB_CONTWOW) &
				  GIB_FCS_STWIP) >> GIB_FCS_STWIP_SHIFT);

	bcm_syspowt_set_wx_csum(dev, featuwes);
	bcm_syspowt_set_tx_csum(dev, featuwes);

	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn 0;
}

/* Hawdwawe countews must be kept in sync because the owdew/offset
 * is impowtant hewe (owdew in stwuctuwe decwawation = owdew in hawdwawe)
 */
static const stwuct bcm_syspowt_stats bcm_syspowt_gstwings_stats[] = {
	/* genewaw stats */
	STAT_NETDEV64(wx_packets),
	STAT_NETDEV64(tx_packets),
	STAT_NETDEV64(wx_bytes),
	STAT_NETDEV64(tx_bytes),
	STAT_NETDEV(wx_ewwows),
	STAT_NETDEV(tx_ewwows),
	STAT_NETDEV(wx_dwopped),
	STAT_NETDEV(tx_dwopped),
	STAT_NETDEV(muwticast),
	/* UniMAC WSV countews */
	STAT_MIB_WX("wx_64_octets", mib.wx.pkt_cnt.cnt_64),
	STAT_MIB_WX("wx_65_127_oct", mib.wx.pkt_cnt.cnt_127),
	STAT_MIB_WX("wx_128_255_oct", mib.wx.pkt_cnt.cnt_255),
	STAT_MIB_WX("wx_256_511_oct", mib.wx.pkt_cnt.cnt_511),
	STAT_MIB_WX("wx_512_1023_oct", mib.wx.pkt_cnt.cnt_1023),
	STAT_MIB_WX("wx_1024_1518_oct", mib.wx.pkt_cnt.cnt_1518),
	STAT_MIB_WX("wx_vwan_1519_1522_oct", mib.wx.pkt_cnt.cnt_mgv),
	STAT_MIB_WX("wx_1522_2047_oct", mib.wx.pkt_cnt.cnt_2047),
	STAT_MIB_WX("wx_2048_4095_oct", mib.wx.pkt_cnt.cnt_4095),
	STAT_MIB_WX("wx_4096_9216_oct", mib.wx.pkt_cnt.cnt_9216),
	STAT_MIB_WX("wx_pkts", mib.wx.pkt),
	STAT_MIB_WX("wx_bytes", mib.wx.bytes),
	STAT_MIB_WX("wx_muwticast", mib.wx.mca),
	STAT_MIB_WX("wx_bwoadcast", mib.wx.bca),
	STAT_MIB_WX("wx_fcs", mib.wx.fcs),
	STAT_MIB_WX("wx_contwow", mib.wx.cf),
	STAT_MIB_WX("wx_pause", mib.wx.pf),
	STAT_MIB_WX("wx_unknown", mib.wx.uo),
	STAT_MIB_WX("wx_awign", mib.wx.awn),
	STAT_MIB_WX("wx_outwange", mib.wx.fww),
	STAT_MIB_WX("wx_code", mib.wx.cde),
	STAT_MIB_WX("wx_cawwiew", mib.wx.fcw),
	STAT_MIB_WX("wx_ovewsize", mib.wx.ovw),
	STAT_MIB_WX("wx_jabbew", mib.wx.jbw),
	STAT_MIB_WX("wx_mtu_eww", mib.wx.mtue),
	STAT_MIB_WX("wx_good_pkts", mib.wx.pok),
	STAT_MIB_WX("wx_unicast", mib.wx.uc),
	STAT_MIB_WX("wx_ppp", mib.wx.ppp),
	STAT_MIB_WX("wx_cwc", mib.wx.wcwc),
	/* UniMAC TSV countews */
	STAT_MIB_TX("tx_64_octets", mib.tx.pkt_cnt.cnt_64),
	STAT_MIB_TX("tx_65_127_oct", mib.tx.pkt_cnt.cnt_127),
	STAT_MIB_TX("tx_128_255_oct", mib.tx.pkt_cnt.cnt_255),
	STAT_MIB_TX("tx_256_511_oct", mib.tx.pkt_cnt.cnt_511),
	STAT_MIB_TX("tx_512_1023_oct", mib.tx.pkt_cnt.cnt_1023),
	STAT_MIB_TX("tx_1024_1518_oct", mib.tx.pkt_cnt.cnt_1518),
	STAT_MIB_TX("tx_vwan_1519_1522_oct", mib.tx.pkt_cnt.cnt_mgv),
	STAT_MIB_TX("tx_1522_2047_oct", mib.tx.pkt_cnt.cnt_2047),
	STAT_MIB_TX("tx_2048_4095_oct", mib.tx.pkt_cnt.cnt_4095),
	STAT_MIB_TX("tx_4096_9216_oct", mib.tx.pkt_cnt.cnt_9216),
	STAT_MIB_TX("tx_pkts", mib.tx.pkts),
	STAT_MIB_TX("tx_muwticast", mib.tx.mca),
	STAT_MIB_TX("tx_bwoadcast", mib.tx.bca),
	STAT_MIB_TX("tx_pause", mib.tx.pf),
	STAT_MIB_TX("tx_contwow", mib.tx.cf),
	STAT_MIB_TX("tx_fcs_eww", mib.tx.fcs),
	STAT_MIB_TX("tx_ovewsize", mib.tx.ovw),
	STAT_MIB_TX("tx_defew", mib.tx.dwf),
	STAT_MIB_TX("tx_excess_defew", mib.tx.edf),
	STAT_MIB_TX("tx_singwe_cow", mib.tx.scw),
	STAT_MIB_TX("tx_muwti_cow", mib.tx.mcw),
	STAT_MIB_TX("tx_wate_cow", mib.tx.wcw),
	STAT_MIB_TX("tx_excess_cow", mib.tx.ecw),
	STAT_MIB_TX("tx_fwags", mib.tx.fwg),
	STAT_MIB_TX("tx_totaw_cow", mib.tx.ncw),
	STAT_MIB_TX("tx_jabbew", mib.tx.jbw),
	STAT_MIB_TX("tx_bytes", mib.tx.bytes),
	STAT_MIB_TX("tx_good_pkts", mib.tx.pok),
	STAT_MIB_TX("tx_unicast", mib.tx.uc),
	/* UniMAC WUNT countews */
	STAT_WUNT("wx_wunt_pkts", mib.wx_wunt_cnt),
	STAT_WUNT("wx_wunt_vawid_fcs", mib.wx_wunt_fcs),
	STAT_WUNT("wx_wunt_invaw_fcs_awign", mib.wx_wunt_fcs_awign),
	STAT_WUNT("wx_wunt_bytes", mib.wx_wunt_bytes),
	/* WXCHK misc statistics */
	STAT_WXCHK("wxchk_bad_csum", mib.wxchk_bad_csum, WXCHK_BAD_CSUM_CNTW),
	STAT_WXCHK("wxchk_othew_pkt_disc", mib.wxchk_othew_pkt_disc,
		   WXCHK_OTHEW_DISC_CNTW),
	/* WBUF misc statistics */
	STAT_WBUF("wbuf_ovfwow_cnt", mib.wbuf_ovfwow_cnt, WBUF_OVFW_DISC_CNTW),
	STAT_WBUF("wbuf_eww_cnt", mib.wbuf_eww_cnt, WBUF_EWW_PKT_CNTW),
	/* WDMA misc statistics */
	STAT_WDMA("wdma_ovfwow_cnt", mib.wdma_ovfwow_cnt, WDMA_OVFW_DISC_CNTW),
	STAT_MIB_SOFT("awwoc_wx_buff_faiwed", mib.awwoc_wx_buff_faiwed),
	STAT_MIB_SOFT("wx_dma_faiwed", mib.wx_dma_faiwed),
	STAT_MIB_SOFT("tx_dma_faiwed", mib.tx_dma_faiwed),
	STAT_MIB_SOFT("tx_weawwoc_tsb", mib.tx_weawwoc_tsb),
	STAT_MIB_SOFT("tx_weawwoc_tsb_faiwed", mib.tx_weawwoc_tsb_faiwed),
	/* Pew TX-queue statistics awe dynamicawwy appended */
};

#define BCM_SYSPOWT_STATS_WEN	AWWAY_SIZE(bcm_syspowt_gstwings_stats)

static void bcm_syspowt_get_dwvinfo(stwuct net_device *dev,
				    stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, KBUIWD_MODNAME, sizeof(info->dwivew));
	stwscpy(info->bus_info, "pwatfowm", sizeof(info->bus_info));
}

static u32 bcm_syspowt_get_msgwvw(stwuct net_device *dev)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);

	wetuwn pwiv->msg_enabwe;
}

static void bcm_syspowt_set_msgwvw(stwuct net_device *dev, u32 enabwe)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);

	pwiv->msg_enabwe = enabwe;
}

static inwine boow bcm_syspowt_wite_stat_vawid(enum bcm_syspowt_stat_type type)
{
	switch (type) {
	case BCM_SYSPOWT_STAT_NETDEV:
	case BCM_SYSPOWT_STAT_NETDEV64:
	case BCM_SYSPOWT_STAT_WXCHK:
	case BCM_SYSPOWT_STAT_WBUF:
	case BCM_SYSPOWT_STAT_WDMA:
	case BCM_SYSPOWT_STAT_SOFT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int bcm_syspowt_get_sset_count(stwuct net_device *dev, int stwing_set)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	const stwuct bcm_syspowt_stats *s;
	unsigned int i, j;

	switch (stwing_set) {
	case ETH_SS_STATS:
		fow (i = 0, j = 0; i < BCM_SYSPOWT_STATS_WEN; i++) {
			s = &bcm_syspowt_gstwings_stats[i];
			if (pwiv->is_wite &&
			    !bcm_syspowt_wite_stat_vawid(s->type))
				continue;
			j++;
		}
		/* Incwude pew-queue statistics */
		wetuwn j + dev->num_tx_queues * NUM_SYSPOWT_TXQ_STAT;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void bcm_syspowt_get_stwings(stwuct net_device *dev,
				    u32 stwingset, u8 *data)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	const stwuct bcm_syspowt_stats *s;
	chaw buf[128];
	int i, j;

	switch (stwingset) {
	case ETH_SS_STATS:
		fow (i = 0, j = 0; i < BCM_SYSPOWT_STATS_WEN; i++) {
			s = &bcm_syspowt_gstwings_stats[i];
			if (pwiv->is_wite &&
			    !bcm_syspowt_wite_stat_vawid(s->type))
				continue;

			memcpy(data + j * ETH_GSTWING_WEN, s->stat_stwing,
			       ETH_GSTWING_WEN);
			j++;
		}

		fow (i = 0; i < dev->num_tx_queues; i++) {
			snpwintf(buf, sizeof(buf), "txq%d_packets", i);
			memcpy(data + j * ETH_GSTWING_WEN, buf,
			       ETH_GSTWING_WEN);
			j++;

			snpwintf(buf, sizeof(buf), "txq%d_bytes", i);
			memcpy(data + j * ETH_GSTWING_WEN, buf,
			       ETH_GSTWING_WEN);
			j++;
		}
		bweak;
	defauwt:
		bweak;
	}
}

static void bcm_syspowt_update_mib_countews(stwuct bcm_syspowt_pwiv *pwiv)
{
	int i, j = 0;

	fow (i = 0; i < BCM_SYSPOWT_STATS_WEN; i++) {
		const stwuct bcm_syspowt_stats *s;
		u8 offset = 0;
		u32 vaw = 0;
		chaw *p;

		s = &bcm_syspowt_gstwings_stats[i];
		switch (s->type) {
		case BCM_SYSPOWT_STAT_NETDEV:
		case BCM_SYSPOWT_STAT_NETDEV64:
		case BCM_SYSPOWT_STAT_SOFT:
			continue;
		case BCM_SYSPOWT_STAT_MIB_WX:
		case BCM_SYSPOWT_STAT_MIB_TX:
		case BCM_SYSPOWT_STAT_WUNT:
			if (pwiv->is_wite)
				continue;

			if (s->type != BCM_SYSPOWT_STAT_MIB_WX)
				offset = UMAC_MIB_STAT_OFFSET;
			vaw = umac_weadw(pwiv, UMAC_MIB_STAWT + j + offset);
			bweak;
		case BCM_SYSPOWT_STAT_WXCHK:
			vaw = wxchk_weadw(pwiv, s->weg_offset);
			if (vaw == ~0)
				wxchk_wwitew(pwiv, 0, s->weg_offset);
			bweak;
		case BCM_SYSPOWT_STAT_WBUF:
			vaw = wbuf_weadw(pwiv, s->weg_offset);
			if (vaw == ~0)
				wbuf_wwitew(pwiv, 0, s->weg_offset);
			bweak;
		case BCM_SYSPOWT_STAT_WDMA:
			if (!pwiv->is_wite)
				continue;

			vaw = wdma_weadw(pwiv, s->weg_offset);
			if (vaw == ~0)
				wdma_wwitew(pwiv, 0, s->weg_offset);
			bweak;
		}

		j += s->stat_sizeof;
		p = (chaw *)pwiv + s->stat_offset;
		*(u32 *)p = vaw;
	}

	netif_dbg(pwiv, hw, pwiv->netdev, "updated MIB countews\n");
}

static void bcm_syspowt_update_tx_stats(stwuct bcm_syspowt_pwiv *pwiv,
					u64 *tx_bytes, u64 *tx_packets)
{
	stwuct bcm_syspowt_tx_wing *wing;
	u64 bytes = 0, packets = 0;
	unsigned int stawt;
	unsigned int q;

	fow (q = 0; q < pwiv->netdev->num_tx_queues; q++) {
		wing = &pwiv->tx_wings[q];
		do {
			stawt = u64_stats_fetch_begin(&pwiv->syncp);
			bytes = wing->bytes;
			packets = wing->packets;
		} whiwe (u64_stats_fetch_wetwy(&pwiv->syncp, stawt));

		*tx_bytes += bytes;
		*tx_packets += packets;
	}
}

static void bcm_syspowt_get_stats(stwuct net_device *dev,
				  stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	stwuct bcm_syspowt_stats64 *stats64 = &pwiv->stats64;
	stwuct u64_stats_sync *syncp = &pwiv->syncp;
	stwuct bcm_syspowt_tx_wing *wing;
	u64 tx_bytes = 0, tx_packets = 0;
	unsigned int stawt;
	int i, j;

	if (netif_wunning(dev)) {
		bcm_syspowt_update_mib_countews(pwiv);
		bcm_syspowt_update_tx_stats(pwiv, &tx_bytes, &tx_packets);
		stats64->tx_bytes = tx_bytes;
		stats64->tx_packets = tx_packets;
	}

	fow (i =  0, j = 0; i < BCM_SYSPOWT_STATS_WEN; i++) {
		const stwuct bcm_syspowt_stats *s;
		chaw *p;

		s = &bcm_syspowt_gstwings_stats[i];
		if (s->type == BCM_SYSPOWT_STAT_NETDEV)
			p = (chaw *)&dev->stats;
		ewse if (s->type == BCM_SYSPOWT_STAT_NETDEV64)
			p = (chaw *)stats64;
		ewse
			p = (chaw *)pwiv;

		if (pwiv->is_wite && !bcm_syspowt_wite_stat_vawid(s->type))
			continue;
		p += s->stat_offset;

		if (s->stat_sizeof == sizeof(u64) &&
		    s->type == BCM_SYSPOWT_STAT_NETDEV64) {
			do {
				stawt = u64_stats_fetch_begin(syncp);
				data[i] = *(u64 *)p;
			} whiwe (u64_stats_fetch_wetwy(syncp, stawt));
		} ewse
			data[i] = *(u32 *)p;
		j++;
	}

	/* Fow SYSTEMPOWT Wite since we have howes in ouw statistics, j wouwd
	 * be equaw to BCM_SYSPOWT_STATS_WEN at the end of the woop, but it
	 * needs to point to how many totaw statistics we have minus the
	 * numbew of pew TX queue statistics
	 */
	j = bcm_syspowt_get_sset_count(dev, ETH_SS_STATS) -
	    dev->num_tx_queues * NUM_SYSPOWT_TXQ_STAT;

	fow (i = 0; i < dev->num_tx_queues; i++) {
		wing = &pwiv->tx_wings[i];
		data[j] = wing->packets;
		j++;
		data[j] = wing->bytes;
		j++;
	}
}

static void bcm_syspowt_get_wow(stwuct net_device *dev,
				stwuct ethtoow_wowinfo *wow)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);

	wow->suppowted = WAKE_MAGIC | WAKE_MAGICSECUWE | WAKE_FIWTEW;
	wow->wowopts = pwiv->wowopts;

	if (!(pwiv->wowopts & WAKE_MAGICSECUWE))
		wetuwn;

	memcpy(wow->sopass, pwiv->sopass, sizeof(pwiv->sopass));
}

static int bcm_syspowt_set_wow(stwuct net_device *dev,
			       stwuct ethtoow_wowinfo *wow)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	stwuct device *kdev = &pwiv->pdev->dev;
	u32 suppowted = WAKE_MAGIC | WAKE_MAGICSECUWE | WAKE_FIWTEW;

	if (!device_can_wakeup(kdev))
		wetuwn -ENOTSUPP;

	if (wow->wowopts & ~suppowted)
		wetuwn -EINVAW;

	if (wow->wowopts & WAKE_MAGICSECUWE)
		memcpy(pwiv->sopass, wow->sopass, sizeof(pwiv->sopass));

	/* Fwag the device and wewevant IWQ as wakeup capabwe */
	if (wow->wowopts) {
		device_set_wakeup_enabwe(kdev, 1);
		if (pwiv->wow_iwq_disabwed)
			enabwe_iwq_wake(pwiv->wow_iwq);
		pwiv->wow_iwq_disabwed = 0;
	} ewse {
		device_set_wakeup_enabwe(kdev, 0);
		/* Avoid unbawanced disabwe_iwq_wake cawws */
		if (!pwiv->wow_iwq_disabwed)
			disabwe_iwq_wake(pwiv->wow_iwq);
		pwiv->wow_iwq_disabwed = 1;
	}

	pwiv->wowopts = wow->wowopts;

	wetuwn 0;
}

static void bcm_syspowt_set_wx_coawesce(stwuct bcm_syspowt_pwiv *pwiv,
					u32 usecs, u32 pkts)
{
	u32 weg;

	weg = wdma_weadw(pwiv, WDMA_MBDONE_INTW);
	weg &= ~(WDMA_INTW_THWESH_MASK |
		 WDMA_TIMEOUT_MASK << WDMA_TIMEOUT_SHIFT);
	weg |= pkts;
	weg |= DIV_WOUND_UP(usecs * 1000, 8192) << WDMA_TIMEOUT_SHIFT;
	wdma_wwitew(pwiv, weg, WDMA_MBDONE_INTW);
}

static void bcm_syspowt_set_tx_coawesce(stwuct bcm_syspowt_tx_wing *wing,
					stwuct ethtoow_coawesce *ec)
{
	stwuct bcm_syspowt_pwiv *pwiv = wing->pwiv;
	u32 weg;

	weg = tdma_weadw(pwiv, TDMA_DESC_WING_INTW_CONTWOW(wing->index));
	weg &= ~(WING_INTW_THWESH_MASK |
		 WING_TIMEOUT_MASK << WING_TIMEOUT_SHIFT);
	weg |= ec->tx_max_coawesced_fwames;
	weg |= DIV_WOUND_UP(ec->tx_coawesce_usecs * 1000, 8192) <<
			    WING_TIMEOUT_SHIFT;
	tdma_wwitew(pwiv, weg, TDMA_DESC_WING_INTW_CONTWOW(wing->index));
}

static int bcm_syspowt_get_coawesce(stwuct net_device *dev,
				    stwuct ethtoow_coawesce *ec,
				    stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
				    stwuct netwink_ext_ack *extack)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	u32 weg;

	weg = tdma_weadw(pwiv, TDMA_DESC_WING_INTW_CONTWOW(0));

	ec->tx_coawesce_usecs = (weg >> WING_TIMEOUT_SHIFT) * 8192 / 1000;
	ec->tx_max_coawesced_fwames = weg & WING_INTW_THWESH_MASK;

	weg = wdma_weadw(pwiv, WDMA_MBDONE_INTW);

	ec->wx_coawesce_usecs = (weg >> WDMA_TIMEOUT_SHIFT) * 8192 / 1000;
	ec->wx_max_coawesced_fwames = weg & WDMA_INTW_THWESH_MASK;
	ec->use_adaptive_wx_coawesce = pwiv->dim.use_dim;

	wetuwn 0;
}

static int bcm_syspowt_set_coawesce(stwuct net_device *dev,
				    stwuct ethtoow_coawesce *ec,
				    stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
				    stwuct netwink_ext_ack *extack)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	stwuct dim_cq_modew modew;
	u32 usecs, pkts;
	unsigned int i;

	/* Base system cwock is 125Mhz, DMA timeout is this wefewence cwock
	 * divided by 1024, which yiewd woughwy 8.192 us, ouw maximum vawue has
	 * to fit in the WING_TIMEOUT_MASK (16 bits).
	 */
	if (ec->tx_max_coawesced_fwames > WING_INTW_THWESH_MASK ||
	    ec->tx_coawesce_usecs > (WING_TIMEOUT_MASK * 8) + 1 ||
	    ec->wx_max_coawesced_fwames > WDMA_INTW_THWESH_MASK ||
	    ec->wx_coawesce_usecs > (WDMA_TIMEOUT_MASK * 8) + 1)
		wetuwn -EINVAW;

	if ((ec->tx_coawesce_usecs == 0 && ec->tx_max_coawesced_fwames == 0) ||
	    (ec->wx_coawesce_usecs == 0 && ec->wx_max_coawesced_fwames == 0))
		wetuwn -EINVAW;

	fow (i = 0; i < dev->num_tx_queues; i++)
		bcm_syspowt_set_tx_coawesce(&pwiv->tx_wings[i], ec);

	pwiv->wx_coawesce_usecs = ec->wx_coawesce_usecs;
	pwiv->wx_max_coawesced_fwames = ec->wx_max_coawesced_fwames;
	usecs = pwiv->wx_coawesce_usecs;
	pkts = pwiv->wx_max_coawesced_fwames;

	if (ec->use_adaptive_wx_coawesce && !pwiv->dim.use_dim) {
		modew = net_dim_get_def_wx_modewation(pwiv->dim.dim.mode);
		usecs = modew.usec;
		pkts = modew.pkts;
	}

	pwiv->dim.use_dim = ec->use_adaptive_wx_coawesce;

	/* Appwy desiwed coawescing pawametews */
	bcm_syspowt_set_wx_coawesce(pwiv, usecs, pkts);

	wetuwn 0;
}

static void bcm_syspowt_fwee_cb(stwuct bcm_syspowt_cb *cb)
{
	dev_consume_skb_any(cb->skb);
	cb->skb = NUWW;
	dma_unmap_addw_set(cb, dma_addw, 0);
}

static stwuct sk_buff *bcm_syspowt_wx_wefiww(stwuct bcm_syspowt_pwiv *pwiv,
					     stwuct bcm_syspowt_cb *cb)
{
	stwuct device *kdev = &pwiv->pdev->dev;
	stwuct net_device *ndev = pwiv->netdev;
	stwuct sk_buff *skb, *wx_skb;
	dma_addw_t mapping;

	/* Awwocate a new SKB fow a new packet */
	skb = __netdev_awwoc_skb(pwiv->netdev, WX_BUF_WENGTH,
				 GFP_ATOMIC | __GFP_NOWAWN);
	if (!skb) {
		pwiv->mib.awwoc_wx_buff_faiwed++;
		netif_eww(pwiv, wx_eww, ndev, "SKB awwoc faiwed\n");
		wetuwn NUWW;
	}

	mapping = dma_map_singwe(kdev, skb->data,
				 WX_BUF_WENGTH, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(kdev, mapping)) {
		pwiv->mib.wx_dma_faiwed++;
		dev_kfwee_skb_any(skb);
		netif_eww(pwiv, wx_eww, ndev, "DMA mapping faiwuwe\n");
		wetuwn NUWW;
	}

	/* Gwab the cuwwent SKB on the wing */
	wx_skb = cb->skb;
	if (wikewy(wx_skb))
		dma_unmap_singwe(kdev, dma_unmap_addw(cb, dma_addw),
				 WX_BUF_WENGTH, DMA_FWOM_DEVICE);

	/* Put the new SKB on the wing */
	cb->skb = skb;
	dma_unmap_addw_set(cb, dma_addw, mapping);
	dma_desc_set_addw(pwiv, cb->bd_addw, mapping);

	netif_dbg(pwiv, wx_status, ndev, "WX wefiww\n");

	/* Wetuwn the cuwwent SKB to the cawwew */
	wetuwn wx_skb;
}

static int bcm_syspowt_awwoc_wx_bufs(stwuct bcm_syspowt_pwiv *pwiv)
{
	stwuct bcm_syspowt_cb *cb;
	stwuct sk_buff *skb;
	unsigned int i;

	fow (i = 0; i < pwiv->num_wx_bds; i++) {
		cb = &pwiv->wx_cbs[i];
		skb = bcm_syspowt_wx_wefiww(pwiv, cb);
		dev_kfwee_skb(skb);
		if (!cb->skb)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/* Poww the hawdwawe fow up to budget packets to pwocess */
static unsigned int bcm_syspowt_desc_wx(stwuct bcm_syspowt_pwiv *pwiv,
					unsigned int budget)
{
	stwuct bcm_syspowt_stats64 *stats64 = &pwiv->stats64;
	stwuct net_device *ndev = pwiv->netdev;
	unsigned int pwocessed = 0, to_pwocess;
	unsigned int pwocessed_bytes = 0;
	stwuct bcm_syspowt_cb *cb;
	stwuct sk_buff *skb;
	unsigned int p_index;
	u16 wen, status;
	stwuct bcm_wsb *wsb;

	/* Cweaw status befowe sewvicing to weduce spuwious intewwupts */
	intww2_0_wwitew(pwiv, INTWW2_0_WDMA_MBDONE, INTWW2_CPU_CWEAW);

	/* Detewmine how much we shouwd pwocess since wast caww, SYSTEMPOWT Wite
	 * gwoups the pwoducew and consumew indexes into the same 32-bit
	 * which we access using WDMA_CONS_INDEX
	 */
	if (!pwiv->is_wite)
		p_index = wdma_weadw(pwiv, WDMA_PWOD_INDEX);
	ewse
		p_index = wdma_weadw(pwiv, WDMA_CONS_INDEX);
	p_index &= WDMA_PWOD_INDEX_MASK;

	to_pwocess = (p_index - pwiv->wx_c_index) & WDMA_CONS_INDEX_MASK;

	netif_dbg(pwiv, wx_status, ndev,
		  "p_index=%d wx_c_index=%d to_pwocess=%d\n",
		  p_index, pwiv->wx_c_index, to_pwocess);

	whiwe ((pwocessed < to_pwocess) && (pwocessed < budget)) {
		cb = &pwiv->wx_cbs[pwiv->wx_wead_ptw];
		skb = bcm_syspowt_wx_wefiww(pwiv, cb);


		/* We do not have a backing SKB, so we do not a cowwesponding
		 * DMA mapping fow this incoming packet since
		 * bcm_syspowt_wx_wefiww awways eithew has both skb and mapping
		 * ow none.
		 */
		if (unwikewy(!skb)) {
			netif_eww(pwiv, wx_eww, ndev, "out of memowy!\n");
			ndev->stats.wx_dwopped++;
			ndev->stats.wx_ewwows++;
			goto next;
		}

		/* Extwact the Weceive Status Bwock pwepended */
		wsb = (stwuct bcm_wsb *)skb->data;
		wen = (wsb->wx_status_wen >> DESC_WEN_SHIFT) & DESC_WEN_MASK;
		status = (wsb->wx_status_wen >> DESC_STATUS_SHIFT) &
			  DESC_STATUS_MASK;

		netif_dbg(pwiv, wx_status, ndev,
			  "p=%d, c=%d, wd_ptw=%d, wen=%d, fwag=0x%04x\n",
			  p_index, pwiv->wx_c_index, pwiv->wx_wead_ptw,
			  wen, status);

		if (unwikewy(wen > WX_BUF_WENGTH)) {
			netif_eww(pwiv, wx_status, ndev, "ovewsized packet\n");
			ndev->stats.wx_wength_ewwows++;
			ndev->stats.wx_ewwows++;
			dev_kfwee_skb_any(skb);
			goto next;
		}

		if (unwikewy(!(status & DESC_EOP) || !(status & DESC_SOP))) {
			netif_eww(pwiv, wx_status, ndev, "fwagmented packet!\n");
			ndev->stats.wx_dwopped++;
			ndev->stats.wx_ewwows++;
			dev_kfwee_skb_any(skb);
			goto next;
		}

		if (unwikewy(status & (WX_STATUS_EWW | WX_STATUS_OVFWOW))) {
			netif_eww(pwiv, wx_eww, ndev, "ewwow packet\n");
			if (status & WX_STATUS_OVFWOW)
				ndev->stats.wx_ovew_ewwows++;
			ndev->stats.wx_dwopped++;
			ndev->stats.wx_ewwows++;
			dev_kfwee_skb_any(skb);
			goto next;
		}

		skb_put(skb, wen);

		/* Hawdwawe vawidated ouw checksum */
		if (wikewy(status & DESC_W4_CSUM))
			skb->ip_summed = CHECKSUM_UNNECESSAWY;

		/* Hawdwawe pwe-pends packets with 2bytes befowe Ethewnet
		 * headew pwus we have the Weceive Status Bwock, stwip off aww
		 * of this fwom the SKB.
		 */
		skb_puww(skb, sizeof(*wsb) + 2);
		wen -= (sizeof(*wsb) + 2);
		pwocessed_bytes += wen;

		/* UniMAC may fowwawd CWC */
		if (pwiv->cwc_fwd) {
			skb_twim(skb, wen - ETH_FCS_WEN);
			wen -= ETH_FCS_WEN;
		}

		skb->pwotocow = eth_type_twans(skb, ndev);
		ndev->stats.wx_packets++;
		ndev->stats.wx_bytes += wen;
		u64_stats_update_begin(&pwiv->syncp);
		stats64->wx_packets++;
		stats64->wx_bytes += wen;
		u64_stats_update_end(&pwiv->syncp);

		napi_gwo_weceive(&pwiv->napi, skb);
next:
		pwocessed++;
		pwiv->wx_wead_ptw++;

		if (pwiv->wx_wead_ptw == pwiv->num_wx_bds)
			pwiv->wx_wead_ptw = 0;
	}

	pwiv->dim.packets = pwocessed;
	pwiv->dim.bytes = pwocessed_bytes;

	wetuwn pwocessed;
}

static void bcm_syspowt_tx_wecwaim_one(stwuct bcm_syspowt_tx_wing *wing,
				       stwuct bcm_syspowt_cb *cb,
				       unsigned int *bytes_compw,
				       unsigned int *pkts_compw)
{
	stwuct bcm_syspowt_pwiv *pwiv = wing->pwiv;
	stwuct device *kdev = &pwiv->pdev->dev;

	if (cb->skb) {
		*bytes_compw += cb->skb->wen;
		dma_unmap_singwe(kdev, dma_unmap_addw(cb, dma_addw),
				 dma_unmap_wen(cb, dma_wen),
				 DMA_TO_DEVICE);
		(*pkts_compw)++;
		bcm_syspowt_fwee_cb(cb);
	/* SKB fwagment */
	} ewse if (dma_unmap_addw(cb, dma_addw)) {
		*bytes_compw += dma_unmap_wen(cb, dma_wen);
		dma_unmap_page(kdev, dma_unmap_addw(cb, dma_addw),
			       dma_unmap_wen(cb, dma_wen), DMA_TO_DEVICE);
		dma_unmap_addw_set(cb, dma_addw, 0);
	}
}

/* Wecwaim queued SKBs fow twansmission compwetion, wockwess vewsion */
static unsigned int __bcm_syspowt_tx_wecwaim(stwuct bcm_syspowt_pwiv *pwiv,
					     stwuct bcm_syspowt_tx_wing *wing)
{
	unsigned int pkts_compw = 0, bytes_compw = 0;
	stwuct net_device *ndev = pwiv->netdev;
	unsigned int txbds_pwocessed = 0;
	stwuct bcm_syspowt_cb *cb;
	unsigned int txbds_weady;
	unsigned int c_index;
	u32 hw_ind;

	/* Cweaw status befowe sewvicing to weduce spuwious intewwupts */
	if (!wing->pwiv->is_wite)
		intww2_1_wwitew(wing->pwiv, BIT(wing->index), INTWW2_CPU_CWEAW);
	ewse
		intww2_0_wwitew(wing->pwiv, BIT(wing->index +
				INTWW2_0_TDMA_MBDONE_SHIFT), INTWW2_CPU_CWEAW);

	/* Compute how many descwiptows have been pwocessed since wast caww */
	hw_ind = tdma_weadw(pwiv, TDMA_DESC_WING_PWOD_CONS_INDEX(wing->index));
	c_index = (hw_ind >> WING_CONS_INDEX_SHIFT) & WING_CONS_INDEX_MASK;
	txbds_weady = (c_index - wing->c_index) & WING_CONS_INDEX_MASK;

	netif_dbg(pwiv, tx_done, ndev,
		  "wing=%d owd_c_index=%u c_index=%u txbds_weady=%u\n",
		  wing->index, wing->c_index, c_index, txbds_weady);

	whiwe (txbds_pwocessed < txbds_weady) {
		cb = &wing->cbs[wing->cwean_index];
		bcm_syspowt_tx_wecwaim_one(wing, cb, &bytes_compw, &pkts_compw);

		wing->desc_count++;
		txbds_pwocessed++;

		if (wikewy(wing->cwean_index < wing->size - 1))
			wing->cwean_index++;
		ewse
			wing->cwean_index = 0;
	}

	u64_stats_update_begin(&pwiv->syncp);
	wing->packets += pkts_compw;
	wing->bytes += bytes_compw;
	u64_stats_update_end(&pwiv->syncp);

	wing->c_index = c_index;

	netif_dbg(pwiv, tx_done, ndev,
		  "wing=%d c_index=%d pkts_compw=%d, bytes_compw=%d\n",
		  wing->index, wing->c_index, pkts_compw, bytes_compw);

	wetuwn pkts_compw;
}

/* Wocked vewsion of the pew-wing TX wecwaim woutine */
static unsigned int bcm_syspowt_tx_wecwaim(stwuct bcm_syspowt_pwiv *pwiv,
					   stwuct bcm_syspowt_tx_wing *wing)
{
	stwuct netdev_queue *txq;
	unsigned int weweased;
	unsigned wong fwags;

	txq = netdev_get_tx_queue(pwiv->netdev, wing->index);

	spin_wock_iwqsave(&wing->wock, fwags);
	weweased = __bcm_syspowt_tx_wecwaim(pwiv, wing);
	if (weweased)
		netif_tx_wake_queue(txq);

	spin_unwock_iwqwestowe(&wing->wock, fwags);

	wetuwn weweased;
}

/* Wocked vewsion of the pew-wing TX wecwaim, but does not wake the queue */
static void bcm_syspowt_tx_cwean(stwuct bcm_syspowt_pwiv *pwiv,
				 stwuct bcm_syspowt_tx_wing *wing)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wing->wock, fwags);
	__bcm_syspowt_tx_wecwaim(pwiv, wing);
	spin_unwock_iwqwestowe(&wing->wock, fwags);
}

static int bcm_syspowt_tx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct bcm_syspowt_tx_wing *wing =
		containew_of(napi, stwuct bcm_syspowt_tx_wing, napi);
	unsigned int wowk_done = 0;

	wowk_done = bcm_syspowt_tx_wecwaim(wing->pwiv, wing);

	if (wowk_done == 0) {
		napi_compwete(napi);
		/* we-enabwe TX intewwupt */
		if (!wing->pwiv->is_wite)
			intww2_1_mask_cweaw(wing->pwiv, BIT(wing->index));
		ewse
			intww2_0_mask_cweaw(wing->pwiv, BIT(wing->index +
					    INTWW2_0_TDMA_MBDONE_SHIFT));

		wetuwn 0;
	}

	wetuwn budget;
}

static void bcm_syspowt_tx_wecwaim_aww(stwuct bcm_syspowt_pwiv *pwiv)
{
	unsigned int q;

	fow (q = 0; q < pwiv->netdev->num_tx_queues; q++)
		bcm_syspowt_tx_wecwaim(pwiv, &pwiv->tx_wings[q]);
}

static int bcm_syspowt_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct bcm_syspowt_pwiv *pwiv =
		containew_of(napi, stwuct bcm_syspowt_pwiv, napi);
	stwuct dim_sampwe dim_sampwe = {};
	unsigned int wowk_done = 0;

	wowk_done = bcm_syspowt_desc_wx(pwiv, budget);

	pwiv->wx_c_index += wowk_done;
	pwiv->wx_c_index &= WDMA_CONS_INDEX_MASK;

	/* SYSTEMPOWT Wite gwoups the pwoducew/consumew index, pwoducew is
	 * maintained by HW, but wwites to it wiww be ignowe whiwe WDMA
	 * is active
	 */
	if (!pwiv->is_wite)
		wdma_wwitew(pwiv, pwiv->wx_c_index, WDMA_CONS_INDEX);
	ewse
		wdma_wwitew(pwiv, pwiv->wx_c_index << 16, WDMA_CONS_INDEX);

	if (wowk_done < budget) {
		napi_compwete_done(napi, wowk_done);
		/* we-enabwe WX intewwupts */
		intww2_0_mask_cweaw(pwiv, INTWW2_0_WDMA_MBDONE);
	}

	if (pwiv->dim.use_dim) {
		dim_update_sampwe(pwiv->dim.event_ctw, pwiv->dim.packets,
				  pwiv->dim.bytes, &dim_sampwe);
		net_dim(&pwiv->dim.dim, dim_sampwe);
	}

	wetuwn wowk_done;
}

static void mpd_enabwe_set(stwuct bcm_syspowt_pwiv *pwiv, boow enabwe)
{
	u32 weg, bit;

	weg = umac_weadw(pwiv, UMAC_MPD_CTWW);
	if (enabwe)
		weg |= MPD_EN;
	ewse
		weg &= ~MPD_EN;
	umac_wwitew(pwiv, weg, UMAC_MPD_CTWW);

	if (pwiv->is_wite)
		bit = WBUF_ACPI_EN_WITE;
	ewse
		bit = WBUF_ACPI_EN;

	weg = wbuf_weadw(pwiv, WBUF_CONTWOW);
	if (enabwe)
		weg |= bit;
	ewse
		weg &= ~bit;
	wbuf_wwitew(pwiv, weg, WBUF_CONTWOW);
}

static void bcm_syspowt_wesume_fwom_wow(stwuct bcm_syspowt_pwiv *pwiv)
{
	unsigned int index;
	u32 weg;

	/* Disabwe WXCHK, active fiwtews and Bwoadcom tag matching */
	weg = wxchk_weadw(pwiv, WXCHK_CONTWOW);
	weg &= ~(WXCHK_BWCM_TAG_MATCH_MASK <<
		 WXCHK_BWCM_TAG_MATCH_SHIFT | WXCHK_EN | WXCHK_BWCM_TAG_EN);
	wxchk_wwitew(pwiv, weg, WXCHK_CONTWOW);

	/* Make suwe we westowe cowwect CID index in case HW wost
	 * its context duwing deep idwe state
	 */
	fow_each_set_bit(index, pwiv->fiwtews, WXCHK_BWCM_TAG_MAX) {
		wxchk_wwitew(pwiv, pwiv->fiwtews_woc[index] <<
			     WXCHK_BWCM_TAG_CID_SHIFT, WXCHK_BWCM_TAG(index));
		wxchk_wwitew(pwiv, 0xff00ffff, WXCHK_BWCM_TAG_MASK(index));
	}

	/* Cweaw the MagicPacket detection wogic */
	mpd_enabwe_set(pwiv, fawse);

	weg = intww2_0_weadw(pwiv, INTWW2_CPU_STATUS);
	if (weg & INTWW2_0_MPD)
		netdev_info(pwiv->netdev, "Wake-on-WAN (MPD) intewwupt!\n");

	if (weg & INTWW2_0_BWCM_MATCH_TAG) {
		weg = wxchk_weadw(pwiv, WXCHK_BWCM_TAG_MATCH_STATUS) &
				  WXCHK_BWCM_TAG_MATCH_MASK;
		netdev_info(pwiv->netdev,
			    "Wake-on-WAN (fiwtews 0x%02x) intewwupt!\n", weg);
	}

	netif_dbg(pwiv, wow, pwiv->netdev, "wesumed fwom WOW\n");
}

static void bcm_syspowt_dim_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dim *dim = containew_of(wowk, stwuct dim, wowk);
	stwuct bcm_syspowt_net_dim *ndim =
			containew_of(dim, stwuct bcm_syspowt_net_dim, dim);
	stwuct bcm_syspowt_pwiv *pwiv =
			containew_of(ndim, stwuct bcm_syspowt_pwiv, dim);
	stwuct dim_cq_modew cuw_pwofiwe = net_dim_get_wx_modewation(dim->mode,
								    dim->pwofiwe_ix);

	bcm_syspowt_set_wx_coawesce(pwiv, cuw_pwofiwe.usec, cuw_pwofiwe.pkts);
	dim->state = DIM_STAWT_MEASUWE;
}

/* WX and misc intewwupt woutine */
static iwqwetuwn_t bcm_syspowt_wx_isw(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	stwuct bcm_syspowt_tx_wing *txw;
	unsigned int wing, wing_bit;

	pwiv->iwq0_stat = intww2_0_weadw(pwiv, INTWW2_CPU_STATUS) &
			  ~intww2_0_weadw(pwiv, INTWW2_CPU_MASK_STATUS);
	intww2_0_wwitew(pwiv, pwiv->iwq0_stat, INTWW2_CPU_CWEAW);

	if (unwikewy(pwiv->iwq0_stat == 0)) {
		netdev_wawn(pwiv->netdev, "spuwious WX intewwupt\n");
		wetuwn IWQ_NONE;
	}

	if (pwiv->iwq0_stat & INTWW2_0_WDMA_MBDONE) {
		pwiv->dim.event_ctw++;
		if (wikewy(napi_scheduwe_pwep(&pwiv->napi))) {
			/* disabwe WX intewwupts */
			intww2_0_mask_set(pwiv, INTWW2_0_WDMA_MBDONE);
			__napi_scheduwe_iwqoff(&pwiv->napi);
		}
	}

	/* TX wing is fuww, pewfowm a fuww wecwaim since we do not know
	 * which one wouwd twiggew this intewwupt
	 */
	if (pwiv->iwq0_stat & INTWW2_0_TX_WING_FUWW)
		bcm_syspowt_tx_wecwaim_aww(pwiv);

	if (!pwiv->is_wite)
		goto out;

	fow (wing = 0; wing < dev->num_tx_queues; wing++) {
		wing_bit = BIT(wing + INTWW2_0_TDMA_MBDONE_SHIFT);
		if (!(pwiv->iwq0_stat & wing_bit))
			continue;

		txw = &pwiv->tx_wings[wing];

		if (wikewy(napi_scheduwe_pwep(&txw->napi))) {
			intww2_0_mask_set(pwiv, wing_bit);
			__napi_scheduwe(&txw->napi);
		}
	}
out:
	wetuwn IWQ_HANDWED;
}

/* TX intewwupt sewvice woutine */
static iwqwetuwn_t bcm_syspowt_tx_isw(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	stwuct bcm_syspowt_tx_wing *txw;
	unsigned int wing;

	pwiv->iwq1_stat = intww2_1_weadw(pwiv, INTWW2_CPU_STATUS) &
				~intww2_1_weadw(pwiv, INTWW2_CPU_MASK_STATUS);
	intww2_1_wwitew(pwiv, 0xffffffff, INTWW2_CPU_CWEAW);

	if (unwikewy(pwiv->iwq1_stat == 0)) {
		netdev_wawn(pwiv->netdev, "spuwious TX intewwupt\n");
		wetuwn IWQ_NONE;
	}

	fow (wing = 0; wing < dev->num_tx_queues; wing++) {
		if (!(pwiv->iwq1_stat & BIT(wing)))
			continue;

		txw = &pwiv->tx_wings[wing];

		if (wikewy(napi_scheduwe_pwep(&txw->napi))) {
			intww2_1_mask_set(pwiv, BIT(wing));
			__napi_scheduwe_iwqoff(&txw->napi);
		}
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t bcm_syspowt_wow_isw(int iwq, void *dev_id)
{
	stwuct bcm_syspowt_pwiv *pwiv = dev_id;

	pm_wakeup_event(&pwiv->pdev->dev, 0);

	wetuwn IWQ_HANDWED;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void bcm_syspowt_poww_contwowwew(stwuct net_device *dev)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);

	disabwe_iwq(pwiv->iwq0);
	bcm_syspowt_wx_isw(pwiv->iwq0, pwiv);
	enabwe_iwq(pwiv->iwq0);

	if (!pwiv->is_wite) {
		disabwe_iwq(pwiv->iwq1);
		bcm_syspowt_tx_isw(pwiv->iwq1, pwiv);
		enabwe_iwq(pwiv->iwq1);
	}
}
#endif

static stwuct sk_buff *bcm_syspowt_insewt_tsb(stwuct sk_buff *skb,
					      stwuct net_device *dev)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	stwuct sk_buff *nskb;
	stwuct bcm_tsb *tsb;
	u32 csum_info;
	u8 ip_pwoto;
	u16 csum_stawt;
	__be16 ip_vew;

	/* We-awwocate SKB if needed */
	if (unwikewy(skb_headwoom(skb) < sizeof(*tsb))) {
		nskb = skb_weawwoc_headwoom(skb, sizeof(*tsb));
		if (!nskb) {
			dev_kfwee_skb_any(skb);
			pwiv->mib.tx_weawwoc_tsb_faiwed++;
			dev->stats.tx_ewwows++;
			dev->stats.tx_dwopped++;
			wetuwn NUWW;
		}
		dev_consume_skb_any(skb);
		skb = nskb;
		pwiv->mib.tx_weawwoc_tsb++;
	}

	tsb = skb_push(skb, sizeof(*tsb));
	/* Zewo-out TSB by defauwt */
	memset(tsb, 0, sizeof(*tsb));

	if (skb_vwan_tag_pwesent(skb)) {
		tsb->pcp_dei_vid = skb_vwan_tag_get_pwio(skb) & PCP_DEI_MASK;
		tsb->pcp_dei_vid |= (u32)skb_vwan_tag_get_id(skb) << VID_SHIFT;
	}

	if (skb->ip_summed == CHECKSUM_PAWTIAW) {
		ip_vew = skb->pwotocow;
		switch (ip_vew) {
		case htons(ETH_P_IP):
			ip_pwoto = ip_hdw(skb)->pwotocow;
			bweak;
		case htons(ETH_P_IPV6):
			ip_pwoto = ipv6_hdw(skb)->nexthdw;
			bweak;
		defauwt:
			wetuwn skb;
		}

		/* Get the checksum offset and the W4 (twanspowt) offset */
		csum_stawt = skb_checksum_stawt_offset(skb) - sizeof(*tsb);
		/* Account fow the HW insewted VWAN tag */
		if (skb_vwan_tag_pwesent(skb))
			csum_stawt += VWAN_HWEN;
		csum_info = (csum_stawt + skb->csum_offset) & W4_CSUM_PTW_MASK;
		csum_info |= (csum_stawt << W4_PTW_SHIFT);

		if (ip_pwoto == IPPWOTO_TCP || ip_pwoto == IPPWOTO_UDP) {
			csum_info |= W4_WENGTH_VAWID;
			if (ip_pwoto == IPPWOTO_UDP &&
			    ip_vew == htons(ETH_P_IP))
				csum_info |= W4_UDP;
		} ewse {
			csum_info = 0;
		}

		tsb->w4_ptw_dest_map = csum_info;
	}

	wetuwn skb;
}

static netdev_tx_t bcm_syspowt_xmit(stwuct sk_buff *skb,
				    stwuct net_device *dev)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	stwuct device *kdev = &pwiv->pdev->dev;
	stwuct bcm_syspowt_tx_wing *wing;
	unsigned wong fwags, desc_fwags;
	stwuct bcm_syspowt_cb *cb;
	stwuct netdev_queue *txq;
	u32 wen_status, addw_wo;
	unsigned int skb_wen;
	dma_addw_t mapping;
	u16 queue;
	int wet;

	queue = skb_get_queue_mapping(skb);
	txq = netdev_get_tx_queue(dev, queue);
	wing = &pwiv->tx_wings[queue];

	/* wock against tx wecwaim in BH context and TX wing fuww intewwupt */
	spin_wock_iwqsave(&wing->wock, fwags);
	if (unwikewy(wing->desc_count == 0)) {
		netif_tx_stop_queue(txq);
		netdev_eww(dev, "queue %d awake and wing fuww!\n", queue);
		wet = NETDEV_TX_BUSY;
		goto out;
	}

	/* Insewt TSB and checksum infos */
	if (pwiv->tsb_en) {
		skb = bcm_syspowt_insewt_tsb(skb, dev);
		if (!skb) {
			wet = NETDEV_TX_OK;
			goto out;
		}
	}

	skb_wen = skb->wen;

	mapping = dma_map_singwe(kdev, skb->data, skb_wen, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(kdev, mapping)) {
		pwiv->mib.tx_dma_faiwed++;
		netif_eww(pwiv, tx_eww, dev, "DMA map faiwed at %p (wen=%d)\n",
			  skb->data, skb_wen);
		wet = NETDEV_TX_OK;
		goto out;
	}

	/* Wemembew the SKB fow futuwe fweeing */
	cb = &wing->cbs[wing->cuww_desc];
	cb->skb = skb;
	dma_unmap_addw_set(cb, dma_addw, mapping);
	dma_unmap_wen_set(cb, dma_wen, skb_wen);

	addw_wo = wowew_32_bits(mapping);
	wen_status = uppew_32_bits(mapping) & DESC_ADDW_HI_MASK;
	wen_status |= (skb_wen << DESC_WEN_SHIFT);
	wen_status |= (DESC_SOP | DESC_EOP | TX_STATUS_APP_CWC) <<
		       DESC_STATUS_SHIFT;
	if (skb->ip_summed == CHECKSUM_PAWTIAW)
		wen_status |= (DESC_W4_CSUM << DESC_STATUS_SHIFT);
	if (skb_vwan_tag_pwesent(skb))
		wen_status |= (TX_STATUS_VWAN_VID_TSB << DESC_STATUS_SHIFT);

	wing->cuww_desc++;
	if (wing->cuww_desc == wing->size)
		wing->cuww_desc = 0;
	wing->desc_count--;

	/* Powts awe watched, so wwite uppew addwess fiwst */
	spin_wock_iwqsave(&pwiv->desc_wock, desc_fwags);
	tdma_wwitew(pwiv, wen_status, TDMA_WWITE_POWT_HI(wing->index));
	tdma_wwitew(pwiv, addw_wo, TDMA_WWITE_POWT_WO(wing->index));
	spin_unwock_iwqwestowe(&pwiv->desc_wock, desc_fwags);

	/* Check wing space and update SW contwow fwow */
	if (wing->desc_count == 0)
		netif_tx_stop_queue(txq);

	netif_dbg(pwiv, tx_queued, dev, "wing=%d desc_count=%d, cuww_desc=%d\n",
		  wing->index, wing->desc_count, wing->cuww_desc);

	wet = NETDEV_TX_OK;
out:
	spin_unwock_iwqwestowe(&wing->wock, fwags);
	wetuwn wet;
}

static void bcm_syspowt_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	netdev_wawn(dev, "twansmit timeout!\n");

	netif_twans_update(dev);
	dev->stats.tx_ewwows++;

	netif_tx_wake_aww_queues(dev);
}

/* phywib adjust wink cawwback */
static void bcm_syspowt_adj_wink(stwuct net_device *dev)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	stwuct phy_device *phydev = dev->phydev;
	unsigned int changed = 0;
	u32 cmd_bits = 0, weg;

	if (pwiv->owd_wink != phydev->wink) {
		changed = 1;
		pwiv->owd_wink = phydev->wink;
	}

	if (pwiv->owd_dupwex != phydev->dupwex) {
		changed = 1;
		pwiv->owd_dupwex = phydev->dupwex;
	}

	if (pwiv->is_wite)
		goto out;

	switch (phydev->speed) {
	case SPEED_2500:
		cmd_bits = CMD_SPEED_2500;
		bweak;
	case SPEED_1000:
		cmd_bits = CMD_SPEED_1000;
		bweak;
	case SPEED_100:
		cmd_bits = CMD_SPEED_100;
		bweak;
	case SPEED_10:
		cmd_bits = CMD_SPEED_10;
		bweak;
	defauwt:
		bweak;
	}
	cmd_bits <<= CMD_SPEED_SHIFT;

	if (phydev->dupwex == DUPWEX_HAWF)
		cmd_bits |= CMD_HD_EN;

	if (pwiv->owd_pause != phydev->pause) {
		changed = 1;
		pwiv->owd_pause = phydev->pause;
	}

	if (!phydev->pause)
		cmd_bits |= CMD_WX_PAUSE_IGNOWE | CMD_TX_PAUSE_IGNOWE;

	if (!changed)
		wetuwn;

	if (phydev->wink) {
		weg = umac_weadw(pwiv, UMAC_CMD);
		weg &= ~((CMD_SPEED_MASK << CMD_SPEED_SHIFT) |
			CMD_HD_EN | CMD_WX_PAUSE_IGNOWE |
			CMD_TX_PAUSE_IGNOWE);
		weg |= cmd_bits;
		umac_wwitew(pwiv, weg, UMAC_CMD);
	}
out:
	if (changed)
		phy_pwint_status(phydev);
}

static void bcm_syspowt_init_dim(stwuct bcm_syspowt_pwiv *pwiv,
				 void (*cb)(stwuct wowk_stwuct *wowk))
{
	stwuct bcm_syspowt_net_dim *dim = &pwiv->dim;

	INIT_WOWK(&dim->dim.wowk, cb);
	dim->dim.mode = DIM_CQ_PEWIOD_MODE_STAWT_FWOM_EQE;
	dim->event_ctw = 0;
	dim->packets = 0;
	dim->bytes = 0;
}

static void bcm_syspowt_init_wx_coawesce(stwuct bcm_syspowt_pwiv *pwiv)
{
	stwuct bcm_syspowt_net_dim *dim = &pwiv->dim;
	stwuct dim_cq_modew modew;
	u32 usecs, pkts;

	usecs = pwiv->wx_coawesce_usecs;
	pkts = pwiv->wx_max_coawesced_fwames;

	/* If DIM was enabwed, we-appwy defauwt pawametews */
	if (dim->use_dim) {
		modew = net_dim_get_def_wx_modewation(dim->dim.mode);
		usecs = modew.usec;
		pkts = modew.pkts;
	}

	bcm_syspowt_set_wx_coawesce(pwiv, usecs, pkts);
}

static int bcm_syspowt_init_tx_wing(stwuct bcm_syspowt_pwiv *pwiv,
				    unsigned int index)
{
	stwuct bcm_syspowt_tx_wing *wing = &pwiv->tx_wings[index];
	size_t size;
	u32 weg;

	/* Simpwe descwiptows pawtitioning fow now */
	size = 256;

	wing->cbs = kcawwoc(size, sizeof(stwuct bcm_syspowt_cb), GFP_KEWNEW);
	if (!wing->cbs) {
		netif_eww(pwiv, hw, pwiv->netdev, "CB awwocation faiwed\n");
		wetuwn -ENOMEM;
	}

	/* Initiawize SW view of the wing */
	spin_wock_init(&wing->wock);
	wing->pwiv = pwiv;
	netif_napi_add_tx(pwiv->netdev, &wing->napi, bcm_syspowt_tx_poww);
	wing->index = index;
	wing->size = size;
	wing->cwean_index = 0;
	wing->awwoc_size = wing->size;
	wing->desc_count = wing->size;
	wing->cuww_desc = 0;

	/* Initiawize HW wing */
	tdma_wwitew(pwiv, WING_EN, TDMA_DESC_WING_HEAD_TAIW_PTW(index));
	tdma_wwitew(pwiv, 0, TDMA_DESC_WING_COUNT(index));
	tdma_wwitew(pwiv, 1, TDMA_DESC_WING_INTW_CONTWOW(index));
	tdma_wwitew(pwiv, 0, TDMA_DESC_WING_PWOD_CONS_INDEX(index));

	/* Configuwe QID and powt mapping */
	weg = tdma_weadw(pwiv, TDMA_DESC_WING_MAPPING(index));
	weg &= ~(WING_QID_MASK | WING_POWT_ID_MASK << WING_POWT_ID_SHIFT);
	if (wing->inspect) {
		weg |= wing->switch_queue & WING_QID_MASK;
		weg |= wing->switch_powt << WING_POWT_ID_SHIFT;
	} ewse {
		weg |= WING_IGNOWE_STATUS;
	}
	tdma_wwitew(pwiv, weg, TDMA_DESC_WING_MAPPING(index));
	weg = 0;
	/* Adjust the packet size cawcuwations if SYSTEMPOWT is wesponsibwe
	 * fow HW insewtion of VWAN tags
	 */
	if (pwiv->netdev->featuwes & NETIF_F_HW_VWAN_CTAG_TX)
		weg = VWAN_HWEN << WING_PKT_SIZE_ADJ_SHIFT;
	tdma_wwitew(pwiv, weg, TDMA_DESC_WING_PCP_DEI_VID(index));

	/* Enabwe ACB awgowithm 2 */
	weg = tdma_weadw(pwiv, TDMA_CONTWOW);
	weg |= tdma_contwow_bit(pwiv, ACB_AWGO);
	tdma_wwitew(pwiv, weg, TDMA_CONTWOW);

	/* Do not use tdma_contwow_bit() hewe because TSB_SWAP1 cowwides
	 * with the owiginaw definition of ACB_AWGO
	 */
	weg = tdma_weadw(pwiv, TDMA_CONTWOW);
	if (pwiv->is_wite)
		weg &= ~BIT(TSB_SWAP1);
	/* Set a cowwect TSB fowmat based on host endian */
	if (!IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
		weg |= tdma_contwow_bit(pwiv, TSB_SWAP0);
	ewse
		weg &= ~tdma_contwow_bit(pwiv, TSB_SWAP0);
	tdma_wwitew(pwiv, weg, TDMA_CONTWOW);

	/* Pwogwam the numbew of descwiptows as MAX_THWESHOWD and hawf of
	 * its size fow the hystewesis twiggew
	 */
	tdma_wwitew(pwiv, wing->size |
			1 << WING_HYST_THWESH_SHIFT,
			TDMA_DESC_WING_MAX_HYST(index));

	/* Enabwe the wing queue in the awbitew */
	weg = tdma_weadw(pwiv, TDMA_TIEW1_AWB_0_QUEUE_EN);
	weg |= (1 << index);
	tdma_wwitew(pwiv, weg, TDMA_TIEW1_AWB_0_QUEUE_EN);

	napi_enabwe(&wing->napi);

	netif_dbg(pwiv, hw, pwiv->netdev,
		  "TDMA cfg, size=%d, switch q=%d,powt=%d\n",
		  wing->size, wing->switch_queue,
		  wing->switch_powt);

	wetuwn 0;
}

static void bcm_syspowt_fini_tx_wing(stwuct bcm_syspowt_pwiv *pwiv,
				     unsigned int index)
{
	stwuct bcm_syspowt_tx_wing *wing = &pwiv->tx_wings[index];
	u32 weg;

	/* Cawwew shouwd stop the TDMA engine */
	weg = tdma_weadw(pwiv, TDMA_STATUS);
	if (!(weg & TDMA_DISABWED))
		netdev_wawn(pwiv->netdev, "TDMA not stopped!\n");

	/* wing->cbs is the wast pawt in bcm_syspowt_init_tx_wing which couwd
	 * faiw, so by checking this pointew we know whethew the TX wing was
	 * fuwwy initiawized ow not.
	 */
	if (!wing->cbs)
		wetuwn;

	napi_disabwe(&wing->napi);
	netif_napi_dew(&wing->napi);

	bcm_syspowt_tx_cwean(pwiv, wing);

	kfwee(wing->cbs);
	wing->cbs = NUWW;
	wing->size = 0;
	wing->awwoc_size = 0;

	netif_dbg(pwiv, hw, pwiv->netdev, "TDMA fini done\n");
}

/* WDMA hewpew */
static inwine int wdma_enabwe_set(stwuct bcm_syspowt_pwiv *pwiv,
				  unsigned int enabwe)
{
	unsigned int timeout = 1000;
	u32 weg;

	weg = wdma_weadw(pwiv, WDMA_CONTWOW);
	if (enabwe)
		weg |= WDMA_EN;
	ewse
		weg &= ~WDMA_EN;
	wdma_wwitew(pwiv, weg, WDMA_CONTWOW);

	/* Poww fow WMDA disabwing compwetion */
	do {
		weg = wdma_weadw(pwiv, WDMA_STATUS);
		if (!!(weg & WDMA_DISABWED) == !enabwe)
			wetuwn 0;
		usweep_wange(1000, 2000);
	} whiwe (timeout-- > 0);

	netdev_eww(pwiv->netdev, "timeout waiting fow WDMA to finish\n");

	wetuwn -ETIMEDOUT;
}

/* TDMA hewpew */
static inwine int tdma_enabwe_set(stwuct bcm_syspowt_pwiv *pwiv,
				  unsigned int enabwe)
{
	unsigned int timeout = 1000;
	u32 weg;

	weg = tdma_weadw(pwiv, TDMA_CONTWOW);
	if (enabwe)
		weg |= tdma_contwow_bit(pwiv, TDMA_EN);
	ewse
		weg &= ~tdma_contwow_bit(pwiv, TDMA_EN);
	tdma_wwitew(pwiv, weg, TDMA_CONTWOW);

	/* Poww fow TMDA disabwing compwetion */
	do {
		weg = tdma_weadw(pwiv, TDMA_STATUS);
		if (!!(weg & TDMA_DISABWED) == !enabwe)
			wetuwn 0;

		usweep_wange(1000, 2000);
	} whiwe (timeout-- > 0);

	netdev_eww(pwiv->netdev, "timeout waiting fow TDMA to finish\n");

	wetuwn -ETIMEDOUT;
}

static int bcm_syspowt_init_wx_wing(stwuct bcm_syspowt_pwiv *pwiv)
{
	stwuct bcm_syspowt_cb *cb;
	u32 weg;
	int wet;
	int i;

	/* Initiawize SW view of the WX wing */
	pwiv->num_wx_bds = pwiv->num_wx_desc_wowds / WOWDS_PEW_DESC;
	pwiv->wx_bds = pwiv->base + SYS_POWT_WDMA_OFFSET;
	pwiv->wx_c_index = 0;
	pwiv->wx_wead_ptw = 0;
	pwiv->wx_cbs = kcawwoc(pwiv->num_wx_bds, sizeof(stwuct bcm_syspowt_cb),
				GFP_KEWNEW);
	if (!pwiv->wx_cbs) {
		netif_eww(pwiv, hw, pwiv->netdev, "CB awwocation faiwed\n");
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < pwiv->num_wx_bds; i++) {
		cb = pwiv->wx_cbs + i;
		cb->bd_addw = pwiv->wx_bds + i * DESC_SIZE;
	}

	wet = bcm_syspowt_awwoc_wx_bufs(pwiv);
	if (wet) {
		netif_eww(pwiv, hw, pwiv->netdev, "SKB awwocation faiwed\n");
		wetuwn wet;
	}

	/* Initiawize HW, ensuwe WDMA is disabwed */
	weg = wdma_weadw(pwiv, WDMA_STATUS);
	if (!(weg & WDMA_DISABWED))
		wdma_enabwe_set(pwiv, 0);

	wdma_wwitew(pwiv, 0, WDMA_WWITE_PTW_WO);
	wdma_wwitew(pwiv, 0, WDMA_WWITE_PTW_HI);
	wdma_wwitew(pwiv, 0, WDMA_PWOD_INDEX);
	wdma_wwitew(pwiv, 0, WDMA_CONS_INDEX);
	wdma_wwitew(pwiv, pwiv->num_wx_bds << WDMA_WING_SIZE_SHIFT |
			  WX_BUF_WENGTH, WDMA_WING_BUF_SIZE);
	/* Opewate the queue in wing mode */
	wdma_wwitew(pwiv, 0, WDMA_STAWT_ADDW_HI);
	wdma_wwitew(pwiv, 0, WDMA_STAWT_ADDW_WO);
	wdma_wwitew(pwiv, 0, WDMA_END_ADDW_HI);
	wdma_wwitew(pwiv, pwiv->num_wx_desc_wowds - 1, WDMA_END_ADDW_WO);

	netif_dbg(pwiv, hw, pwiv->netdev,
		  "WDMA cfg, num_wx_bds=%d, wx_bds=%p\n",
		  pwiv->num_wx_bds, pwiv->wx_bds);

	wetuwn 0;
}

static void bcm_syspowt_fini_wx_wing(stwuct bcm_syspowt_pwiv *pwiv)
{
	stwuct bcm_syspowt_cb *cb;
	unsigned int i;
	u32 weg;

	/* Cawwew shouwd ensuwe WDMA is disabwed */
	weg = wdma_weadw(pwiv, WDMA_STATUS);
	if (!(weg & WDMA_DISABWED))
		netdev_wawn(pwiv->netdev, "WDMA not stopped!\n");

	fow (i = 0; i < pwiv->num_wx_bds; i++) {
		cb = &pwiv->wx_cbs[i];
		if (dma_unmap_addw(cb, dma_addw))
			dma_unmap_singwe(&pwiv->pdev->dev,
					 dma_unmap_addw(cb, dma_addw),
					 WX_BUF_WENGTH, DMA_FWOM_DEVICE);
		bcm_syspowt_fwee_cb(cb);
	}

	kfwee(pwiv->wx_cbs);
	pwiv->wx_cbs = NUWW;

	netif_dbg(pwiv, hw, pwiv->netdev, "WDMA fini done\n");
}

static void bcm_syspowt_set_wx_mode(stwuct net_device *dev)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	u32 weg;

	if (pwiv->is_wite)
		wetuwn;

	weg = umac_weadw(pwiv, UMAC_CMD);
	if (dev->fwags & IFF_PWOMISC)
		weg |= CMD_PWOMISC;
	ewse
		weg &= ~CMD_PWOMISC;
	umac_wwitew(pwiv, weg, UMAC_CMD);

	/* No suppowt fow AWWMUWTI */
	if (dev->fwags & IFF_AWWMUWTI)
		wetuwn;
}

static inwine void umac_enabwe_set(stwuct bcm_syspowt_pwiv *pwiv,
				   u32 mask, unsigned int enabwe)
{
	u32 weg;

	if (!pwiv->is_wite) {
		weg = umac_weadw(pwiv, UMAC_CMD);
		if (enabwe)
			weg |= mask;
		ewse
			weg &= ~mask;
		umac_wwitew(pwiv, weg, UMAC_CMD);
	} ewse {
		weg = gib_weadw(pwiv, GIB_CONTWOW);
		if (enabwe)
			weg |= mask;
		ewse
			weg &= ~mask;
		gib_wwitew(pwiv, weg, GIB_CONTWOW);
	}

	/* UniMAC stops on a packet boundawy, wait fow a fuww-sized packet
	 * to be pwocessed (1 msec).
	 */
	if (enabwe == 0)
		usweep_wange(1000, 2000);
}

static inwine void umac_weset(stwuct bcm_syspowt_pwiv *pwiv)
{
	u32 weg;

	if (pwiv->is_wite)
		wetuwn;

	weg = umac_weadw(pwiv, UMAC_CMD);
	weg |= CMD_SW_WESET;
	umac_wwitew(pwiv, weg, UMAC_CMD);
	udeway(10);
	weg = umac_weadw(pwiv, UMAC_CMD);
	weg &= ~CMD_SW_WESET;
	umac_wwitew(pwiv, weg, UMAC_CMD);
}

static void umac_set_hw_addw(stwuct bcm_syspowt_pwiv *pwiv,
			     const unsigned chaw *addw)
{
	u32 mac0 = (addw[0] << 24) | (addw[1] << 16) | (addw[2] << 8) |
		    addw[3];
	u32 mac1 = (addw[4] << 8) | addw[5];

	if (!pwiv->is_wite) {
		umac_wwitew(pwiv, mac0, UMAC_MAC0);
		umac_wwitew(pwiv, mac1, UMAC_MAC1);
	} ewse {
		gib_wwitew(pwiv, mac0, GIB_MAC0);
		gib_wwitew(pwiv, mac1, GIB_MAC1);
	}
}

static void topctww_fwush(stwuct bcm_syspowt_pwiv *pwiv)
{
	topctww_wwitew(pwiv, WX_FWUSH, WX_FWUSH_CNTW);
	topctww_wwitew(pwiv, TX_FWUSH, TX_FWUSH_CNTW);
	mdeway(1);
	topctww_wwitew(pwiv, 0, WX_FWUSH_CNTW);
	topctww_wwitew(pwiv, 0, TX_FWUSH_CNTW);
}

static int bcm_syspowt_change_mac(stwuct net_device *dev, void *p)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	stwuct sockaddw *addw = p;

	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EINVAW;

	eth_hw_addw_set(dev, addw->sa_data);

	/* intewface is disabwed, changes to MAC wiww be wefwected on next
	 * open caww
	 */
	if (!netif_wunning(dev))
		wetuwn 0;

	umac_set_hw_addw(pwiv, dev->dev_addw);

	wetuwn 0;
}

static void bcm_syspowt_get_stats64(stwuct net_device *dev,
				    stwuct wtnw_wink_stats64 *stats)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	stwuct bcm_syspowt_stats64 *stats64 = &pwiv->stats64;
	unsigned int stawt;

	netdev_stats_to_stats64(stats, &dev->stats);

	bcm_syspowt_update_tx_stats(pwiv, &stats->tx_bytes,
				    &stats->tx_packets);

	do {
		stawt = u64_stats_fetch_begin(&pwiv->syncp);
		stats->wx_packets = stats64->wx_packets;
		stats->wx_bytes = stats64->wx_bytes;
	} whiwe (u64_stats_fetch_wetwy(&pwiv->syncp, stawt));
}

static void bcm_syspowt_netif_stawt(stwuct net_device *dev)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);

	/* Enabwe NAPI */
	bcm_syspowt_init_dim(pwiv, bcm_syspowt_dim_wowk);
	bcm_syspowt_init_wx_coawesce(pwiv);
	napi_enabwe(&pwiv->napi);

	/* Enabwe WX intewwupt and TX wing fuww intewwupt */
	intww2_0_mask_cweaw(pwiv, INTWW2_0_WDMA_MBDONE | INTWW2_0_TX_WING_FUWW);

	phy_stawt(dev->phydev);

	/* Enabwe TX intewwupts fow the TXQs */
	if (!pwiv->is_wite)
		intww2_1_mask_cweaw(pwiv, 0xffffffff);
	ewse
		intww2_0_mask_cweaw(pwiv, INTWW2_0_TDMA_MBDONE_MASK);
}

static void wbuf_init(stwuct bcm_syspowt_pwiv *pwiv)
{
	u32 weg;

	weg = wbuf_weadw(pwiv, WBUF_CONTWOW);
	weg |= WBUF_4B_AWGN | WBUF_WSB_EN;
	/* Set a cowwect WSB fowmat on SYSTEMPOWT Wite */
	if (pwiv->is_wite)
		weg &= ~WBUF_WSB_SWAP1;

	/* Set a cowwect WSB fowmat based on host endian */
	if (!IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
		weg |= WBUF_WSB_SWAP0;
	ewse
		weg &= ~WBUF_WSB_SWAP0;
	wbuf_wwitew(pwiv, weg, WBUF_CONTWOW);
}

static inwine void bcm_syspowt_mask_aww_intws(stwuct bcm_syspowt_pwiv *pwiv)
{
	intww2_0_mask_set(pwiv, 0xffffffff);
	intww2_0_wwitew(pwiv, 0xffffffff, INTWW2_CPU_CWEAW);
	if (!pwiv->is_wite) {
		intww2_1_mask_set(pwiv, 0xffffffff);
		intww2_1_wwitew(pwiv, 0xffffffff, INTWW2_CPU_CWEAW);
	}
}

static inwine void gib_set_pad_extension(stwuct bcm_syspowt_pwiv *pwiv)
{
	u32 weg;

	weg = gib_weadw(pwiv, GIB_CONTWOW);
	/* Incwude Bwoadcom tag in pad extension and fix up IPG_WENGTH */
	if (netdev_uses_dsa(pwiv->netdev)) {
		weg &= ~(GIB_PAD_EXTENSION_MASK << GIB_PAD_EXTENSION_SHIFT);
		weg |= ENET_BWCM_TAG_WEN << GIB_PAD_EXTENSION_SHIFT;
	}
	weg &= ~(GIB_IPG_WEN_MASK << GIB_IPG_WEN_SHIFT);
	weg |= 12 << GIB_IPG_WEN_SHIFT;
	gib_wwitew(pwiv, weg, GIB_CONTWOW);
}

static int bcm_syspowt_open(stwuct net_device *dev)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	stwuct phy_device *phydev;
	unsigned int i;
	int wet;

	cwk_pwepawe_enabwe(pwiv->cwk);

	/* Weset UniMAC */
	umac_weset(pwiv);

	/* Fwush TX and WX FIFOs at TOPCTWW wevew */
	topctww_fwush(pwiv);

	/* Disabwe the UniMAC WX/TX */
	umac_enabwe_set(pwiv, CMD_WX_EN | CMD_TX_EN, 0);

	/* Enabwe WBUF 2bytes awignment and Weceive Status Bwock */
	wbuf_init(pwiv);

	/* Set maximum fwame wength */
	if (!pwiv->is_wite)
		umac_wwitew(pwiv, UMAC_MAX_MTU_SIZE, UMAC_MAX_FWAME_WEN);
	ewse
		gib_set_pad_extension(pwiv);

	/* Appwy featuwes again in case we changed them whiwe intewface was
	 * down
	 */
	bcm_syspowt_set_featuwes(dev, dev->featuwes);

	/* Set MAC addwess */
	umac_set_hw_addw(pwiv, dev->dev_addw);

	phydev = of_phy_connect(dev, pwiv->phy_dn, bcm_syspowt_adj_wink,
				0, pwiv->phy_intewface);
	if (!phydev) {
		netdev_eww(dev, "couwd not attach to PHY\n");
		wet = -ENODEV;
		goto out_cwk_disabwe;
	}

	/* Indicate that the MAC is wesponsibwe fow PHY PM */
	phydev->mac_managed_pm = twue;

	/* Weset house keeping wink status */
	pwiv->owd_dupwex = -1;
	pwiv->owd_wink = -1;
	pwiv->owd_pause = -1;

	/* mask aww intewwupts and wequest them */
	bcm_syspowt_mask_aww_intws(pwiv);

	wet = wequest_iwq(pwiv->iwq0, bcm_syspowt_wx_isw, 0, dev->name, dev);
	if (wet) {
		netdev_eww(dev, "faiwed to wequest WX intewwupt\n");
		goto out_phy_disconnect;
	}

	if (!pwiv->is_wite) {
		wet = wequest_iwq(pwiv->iwq1, bcm_syspowt_tx_isw, 0,
				  dev->name, dev);
		if (wet) {
			netdev_eww(dev, "faiwed to wequest TX intewwupt\n");
			goto out_fwee_iwq0;
		}
	}

	/* Initiawize both hawdwawe and softwawe wing */
	spin_wock_init(&pwiv->desc_wock);
	fow (i = 0; i < dev->num_tx_queues; i++) {
		wet = bcm_syspowt_init_tx_wing(pwiv, i);
		if (wet) {
			netdev_eww(dev, "faiwed to initiawize TX wing %d\n",
				   i);
			goto out_fwee_tx_wing;
		}
	}

	/* Initiawize winked-wist */
	tdma_wwitew(pwiv, TDMA_WW_WAM_INIT_BUSY, TDMA_STATUS);

	/* Initiawize WX wing */
	wet = bcm_syspowt_init_wx_wing(pwiv);
	if (wet) {
		netdev_eww(dev, "faiwed to initiawize WX wing\n");
		goto out_fwee_wx_wing;
	}

	/* Tuwn on WDMA */
	wet = wdma_enabwe_set(pwiv, 1);
	if (wet)
		goto out_fwee_wx_wing;

	/* Tuwn on TDMA */
	wet = tdma_enabwe_set(pwiv, 1);
	if (wet)
		goto out_cweaw_wx_int;

	/* Tuwn on UniMAC TX/WX */
	umac_enabwe_set(pwiv, CMD_WX_EN | CMD_TX_EN, 1);

	bcm_syspowt_netif_stawt(dev);

	netif_tx_stawt_aww_queues(dev);

	wetuwn 0;

out_cweaw_wx_int:
	intww2_0_mask_set(pwiv, INTWW2_0_WDMA_MBDONE | INTWW2_0_TX_WING_FUWW);
out_fwee_wx_wing:
	bcm_syspowt_fini_wx_wing(pwiv);
out_fwee_tx_wing:
	fow (i = 0; i < dev->num_tx_queues; i++)
		bcm_syspowt_fini_tx_wing(pwiv, i);
	if (!pwiv->is_wite)
		fwee_iwq(pwiv->iwq1, dev);
out_fwee_iwq0:
	fwee_iwq(pwiv->iwq0, dev);
out_phy_disconnect:
	phy_disconnect(phydev);
out_cwk_disabwe:
	cwk_disabwe_unpwepawe(pwiv->cwk);
	wetuwn wet;
}

static void bcm_syspowt_netif_stop(stwuct net_device *dev)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);

	/* stop aww softwawe fwom updating hawdwawe */
	netif_tx_disabwe(dev);
	napi_disabwe(&pwiv->napi);
	cancew_wowk_sync(&pwiv->dim.dim.wowk);
	phy_stop(dev->phydev);

	/* mask aww intewwupts */
	bcm_syspowt_mask_aww_intws(pwiv);
}

static int bcm_syspowt_stop(stwuct net_device *dev)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	unsigned int i;
	int wet;

	bcm_syspowt_netif_stop(dev);

	/* Disabwe UniMAC WX */
	umac_enabwe_set(pwiv, CMD_WX_EN, 0);

	wet = tdma_enabwe_set(pwiv, 0);
	if (wet) {
		netdev_eww(dev, "timeout disabwing WDMA\n");
		wetuwn wet;
	}

	/* Wait fow a maximum packet size to be dwained */
	usweep_wange(2000, 3000);

	wet = wdma_enabwe_set(pwiv, 0);
	if (wet) {
		netdev_eww(dev, "timeout disabwing TDMA\n");
		wetuwn wet;
	}

	/* Disabwe UniMAC TX */
	umac_enabwe_set(pwiv, CMD_TX_EN, 0);

	/* Fwee WX/TX wings SW stwuctuwes */
	fow (i = 0; i < dev->num_tx_queues; i++)
		bcm_syspowt_fini_tx_wing(pwiv, i);
	bcm_syspowt_fini_wx_wing(pwiv);

	fwee_iwq(pwiv->iwq0, dev);
	if (!pwiv->is_wite)
		fwee_iwq(pwiv->iwq1, dev);

	/* Disconnect fwom PHY */
	phy_disconnect(dev->phydev);

	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn 0;
}

static int bcm_syspowt_wuwe_find(stwuct bcm_syspowt_pwiv *pwiv,
				 u64 wocation)
{
	unsigned int index;
	u32 weg;

	fow_each_set_bit(index, pwiv->fiwtews, WXCHK_BWCM_TAG_MAX) {
		weg = wxchk_weadw(pwiv, WXCHK_BWCM_TAG(index));
		weg >>= WXCHK_BWCM_TAG_CID_SHIFT;
		weg &= WXCHK_BWCM_TAG_CID_MASK;
		if (weg == wocation)
			wetuwn index;
	}

	wetuwn -EINVAW;
}

static int bcm_syspowt_wuwe_get(stwuct bcm_syspowt_pwiv *pwiv,
				stwuct ethtoow_wxnfc *nfc)
{
	int index;

	/* This is not a wuwe that we know about */
	index = bcm_syspowt_wuwe_find(pwiv, nfc->fs.wocation);
	if (index < 0)
		wetuwn -EOPNOTSUPP;

	nfc->fs.wing_cookie = WX_CWS_FWOW_WAKE;

	wetuwn 0;
}

static int bcm_syspowt_wuwe_set(stwuct bcm_syspowt_pwiv *pwiv,
				stwuct ethtoow_wxnfc *nfc)
{
	unsigned int index;
	u32 weg;

	/* We cannot match wocations gweatew than what the cwassification ID
	 * pewmits (256 entwies)
	 */
	if (nfc->fs.wocation > WXCHK_BWCM_TAG_CID_MASK)
		wetuwn -E2BIG;

	/* We cannot suppowt fwows that awe not destined fow a wake-up */
	if (nfc->fs.wing_cookie != WX_CWS_FWOW_WAKE)
		wetuwn -EOPNOTSUPP;

	index = find_fiwst_zewo_bit(pwiv->fiwtews, WXCHK_BWCM_TAG_MAX);
	if (index >= WXCHK_BWCM_TAG_MAX)
		/* Aww fiwtews awe awweady in use, we cannot match mowe wuwes */
		wetuwn -ENOSPC;

	/* Wocation is the cwassification ID, and index is the position
	 * within one of ouw 8 possibwe fiwtews to be pwogwammed
	 */
	weg = wxchk_weadw(pwiv, WXCHK_BWCM_TAG(index));
	weg &= ~(WXCHK_BWCM_TAG_CID_MASK << WXCHK_BWCM_TAG_CID_SHIFT);
	weg |= nfc->fs.wocation << WXCHK_BWCM_TAG_CID_SHIFT;
	wxchk_wwitew(pwiv, weg, WXCHK_BWCM_TAG(index));
	wxchk_wwitew(pwiv, 0xff00ffff, WXCHK_BWCM_TAG_MASK(index));

	pwiv->fiwtews_woc[index] = nfc->fs.wocation;
	set_bit(index, pwiv->fiwtews);

	wetuwn 0;
}

static int bcm_syspowt_wuwe_dew(stwuct bcm_syspowt_pwiv *pwiv,
				u64 wocation)
{
	int index;

	/* This is not a wuwe that we know about */
	index = bcm_syspowt_wuwe_find(pwiv, wocation);
	if (index < 0)
		wetuwn -EOPNOTSUPP;

	/* No need to disabwe this fiwtew if it was enabwed, this wiww
	 * be taken cawe of duwing suspend time by bcm_syspowt_suspend_to_wow
	 */
	cweaw_bit(index, pwiv->fiwtews);
	pwiv->fiwtews_woc[index] = 0;

	wetuwn 0;
}

static int bcm_syspowt_get_wxnfc(stwuct net_device *dev,
				 stwuct ethtoow_wxnfc *nfc, u32 *wuwe_wocs)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	int wet = -EOPNOTSUPP;

	switch (nfc->cmd) {
	case ETHTOOW_GWXCWSWUWE:
		wet = bcm_syspowt_wuwe_get(pwiv, nfc);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static int bcm_syspowt_set_wxnfc(stwuct net_device *dev,
				 stwuct ethtoow_wxnfc *nfc)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	int wet = -EOPNOTSUPP;

	switch (nfc->cmd) {
	case ETHTOOW_SWXCWSWWINS:
		wet = bcm_syspowt_wuwe_set(pwiv, nfc);
		bweak;
	case ETHTOOW_SWXCWSWWDEW:
		wet = bcm_syspowt_wuwe_dew(pwiv, nfc->fs.wocation);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static const stwuct ethtoow_ops bcm_syspowt_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_USECS |
				     ETHTOOW_COAWESCE_MAX_FWAMES |
				     ETHTOOW_COAWESCE_USE_ADAPTIVE_WX,
	.get_dwvinfo		= bcm_syspowt_get_dwvinfo,
	.get_msgwevew		= bcm_syspowt_get_msgwvw,
	.set_msgwevew		= bcm_syspowt_set_msgwvw,
	.get_wink		= ethtoow_op_get_wink,
	.get_stwings		= bcm_syspowt_get_stwings,
	.get_ethtoow_stats	= bcm_syspowt_get_stats,
	.get_sset_count		= bcm_syspowt_get_sset_count,
	.get_wow		= bcm_syspowt_get_wow,
	.set_wow		= bcm_syspowt_set_wow,
	.get_coawesce		= bcm_syspowt_get_coawesce,
	.set_coawesce		= bcm_syspowt_set_coawesce,
	.get_wink_ksettings     = phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings     = phy_ethtoow_set_wink_ksettings,
	.get_wxnfc		= bcm_syspowt_get_wxnfc,
	.set_wxnfc		= bcm_syspowt_set_wxnfc,
};

static u16 bcm_syspowt_sewect_queue(stwuct net_device *dev, stwuct sk_buff *skb,
				    stwuct net_device *sb_dev)
{
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	u16 queue = skb_get_queue_mapping(skb);
	stwuct bcm_syspowt_tx_wing *tx_wing;
	unsigned int q, powt;

	if (!netdev_uses_dsa(dev))
		wetuwn netdev_pick_tx(dev, skb, NUWW);

	/* DSA tagging wayew wiww have configuwed the cowwect queue */
	q = BWCM_TAG_GET_QUEUE(queue);
	powt = BWCM_TAG_GET_POWT(queue);
	tx_wing = pwiv->wing_map[q + powt * pwiv->pew_powt_num_tx_queues];

	if (unwikewy(!tx_wing))
		wetuwn netdev_pick_tx(dev, skb, NUWW);

	wetuwn tx_wing->index;
}

static const stwuct net_device_ops bcm_syspowt_netdev_ops = {
	.ndo_stawt_xmit		= bcm_syspowt_xmit,
	.ndo_tx_timeout		= bcm_syspowt_tx_timeout,
	.ndo_open		= bcm_syspowt_open,
	.ndo_stop		= bcm_syspowt_stop,
	.ndo_set_featuwes	= bcm_syspowt_set_featuwes,
	.ndo_set_wx_mode	= bcm_syspowt_set_wx_mode,
	.ndo_set_mac_addwess	= bcm_syspowt_change_mac,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= bcm_syspowt_poww_contwowwew,
#endif
	.ndo_get_stats64	= bcm_syspowt_get_stats64,
	.ndo_sewect_queue	= bcm_syspowt_sewect_queue,
};

static int bcm_syspowt_map_queues(stwuct net_device *dev,
				  stwuct net_device *swave_dev)
{
	stwuct dsa_powt *dp = dsa_powt_fwom_netdev(swave_dev);
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	stwuct bcm_syspowt_tx_wing *wing;
	unsigned int num_tx_queues;
	unsigned int q, qp, powt;

	/* We can't be setting up queue inspection fow non diwectwy attached
	 * switches
	 */
	if (dp->ds->index)
		wetuwn 0;

	powt = dp->index;

	/* On SYSTEMPOWT Wite we have twice as wess queues, so we cannot do a
	 * 1:1 mapping, we can onwy do a 2:1 mapping. By weducing the numbew of
	 * pew-powt (swave_dev) netwowk devices queue, we achieve just that.
	 * This need to happen now befowe any swave netwowk device is used such
	 * it accuwatewy wefwects the numbew of weaw TX queues.
	 */
	if (pwiv->is_wite)
		netif_set_weaw_num_tx_queues(swave_dev,
					     swave_dev->num_tx_queues / 2);

	num_tx_queues = swave_dev->weaw_num_tx_queues;

	if (pwiv->pew_powt_num_tx_queues &&
	    pwiv->pew_powt_num_tx_queues != num_tx_queues)
		netdev_wawn(swave_dev, "asymmetwic numbew of pew-powt queues\n");

	pwiv->pew_powt_num_tx_queues = num_tx_queues;

	fow (q = 0, qp = 0; q < dev->num_tx_queues && qp < num_tx_queues;
	     q++) {
		wing = &pwiv->tx_wings[q];

		if (wing->inspect)
			continue;

		/* Just wemembew the mapping actuaw pwogwamming done
		 * duwing bcm_syspowt_init_tx_wing
		 */
		wing->switch_queue = qp;
		wing->switch_powt = powt;
		wing->inspect = twue;
		pwiv->wing_map[qp + powt * num_tx_queues] = wing;
		qp++;
	}

	wetuwn 0;
}

static int bcm_syspowt_unmap_queues(stwuct net_device *dev,
				    stwuct net_device *swave_dev)
{
	stwuct dsa_powt *dp = dsa_powt_fwom_netdev(swave_dev);
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	stwuct bcm_syspowt_tx_wing *wing;
	unsigned int num_tx_queues;
	unsigned int q, qp, powt;

	powt = dp->index;

	num_tx_queues = swave_dev->weaw_num_tx_queues;

	fow (q = 0; q < dev->num_tx_queues; q++) {
		wing = &pwiv->tx_wings[q];

		if (wing->switch_powt != powt)
			continue;

		if (!wing->inspect)
			continue;

		wing->inspect = fawse;
		qp = wing->switch_queue;
		pwiv->wing_map[qp + powt * num_tx_queues] = NUWW;
	}

	wetuwn 0;
}

static int bcm_syspowt_netdevice_event(stwuct notifiew_bwock *nb,
				       unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct netdev_notifiew_changeuppew_info *info = ptw;
	stwuct bcm_syspowt_pwiv *pwiv;
	int wet = 0;

	pwiv = containew_of(nb, stwuct bcm_syspowt_pwiv, netdev_notifiew);
	if (pwiv->netdev != dev)
		wetuwn NOTIFY_DONE;

	switch (event) {
	case NETDEV_CHANGEUPPEW:
		if (dev->netdev_ops != &bcm_syspowt_netdev_ops)
			wetuwn NOTIFY_DONE;

		if (!dsa_usew_dev_check(info->uppew_dev))
			wetuwn NOTIFY_DONE;

		if (info->winking)
			wet = bcm_syspowt_map_queues(dev, info->uppew_dev);
		ewse
			wet = bcm_syspowt_unmap_queues(dev, info->uppew_dev);
		bweak;
	}

	wetuwn notifiew_fwom_ewwno(wet);
}

#define WEV_FMT	"v%2x.%02x"

static const stwuct bcm_syspowt_hw_pawams bcm_syspowt_pawams[] = {
	[SYSTEMPOWT] = {
		.is_wite = fawse,
		.num_wx_desc_wowds = SP_NUM_HW_WX_DESC_WOWDS,
	},
	[SYSTEMPOWT_WITE] = {
		.is_wite = twue,
		.num_wx_desc_wowds = SP_WT_NUM_HW_WX_DESC_WOWDS,
	},
};

static const stwuct of_device_id bcm_syspowt_of_match[] = {
	{ .compatibwe = "bwcm,systempowtwite-v1.00",
	  .data = &bcm_syspowt_pawams[SYSTEMPOWT_WITE] },
	{ .compatibwe = "bwcm,systempowt-v1.00",
	  .data = &bcm_syspowt_pawams[SYSTEMPOWT] },
	{ .compatibwe = "bwcm,systempowt",
	  .data = &bcm_syspowt_pawams[SYSTEMPOWT] },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, bcm_syspowt_of_match);

static int bcm_syspowt_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct bcm_syspowt_hw_pawams *pawams;
	const stwuct of_device_id *of_id = NUWW;
	stwuct bcm_syspowt_pwiv *pwiv;
	stwuct device_node *dn;
	stwuct net_device *dev;
	u32 txq, wxq;
	int wet;

	dn = pdev->dev.of_node;
	of_id = of_match_node(bcm_syspowt_of_match, dn);
	if (!of_id || !of_id->data)
		wetuwn -EINVAW;

	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(40));
	if (wet)
		wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to set DMA mask: %d\n", wet);
		wetuwn wet;
	}

	/* Faiwwy quickwy we need to know the type of adaptew we have */
	pawams = of_id->data;

	/* Wead the Twansmit/Weceive Queue pwopewties */
	if (of_pwopewty_wead_u32(dn, "systempowt,num-txq", &txq))
		txq = TDMA_NUM_WINGS;
	if (of_pwopewty_wead_u32(dn, "systempowt,num-wxq", &wxq))
		wxq = 1;

	/* Sanity check the numbew of twansmit queues */
	if (!txq || txq > TDMA_NUM_WINGS)
		wetuwn -EINVAW;

	dev = awwoc_ethewdev_mqs(sizeof(*pwiv), txq, wxq);
	if (!dev)
		wetuwn -ENOMEM;

	/* Initiawize pwivate membews */
	pwiv = netdev_pwiv(dev);

	pwiv->cwk = devm_cwk_get_optionaw(&pdev->dev, "sw_syspowt");
	if (IS_EWW(pwiv->cwk)) {
		wet = PTW_EWW(pwiv->cwk);
		goto eww_fwee_netdev;
	}

	/* Awwocate numbew of TX wings */
	pwiv->tx_wings = devm_kcawwoc(&pdev->dev, txq,
				      sizeof(stwuct bcm_syspowt_tx_wing),
				      GFP_KEWNEW);
	if (!pwiv->tx_wings) {
		wet = -ENOMEM;
		goto eww_fwee_netdev;
	}

	pwiv->is_wite = pawams->is_wite;
	pwiv->num_wx_desc_wowds = pawams->num_wx_desc_wowds;

	pwiv->iwq0 = pwatfowm_get_iwq(pdev, 0);
	if (!pwiv->is_wite) {
		pwiv->iwq1 = pwatfowm_get_iwq(pdev, 1);
		pwiv->wow_iwq = pwatfowm_get_iwq_optionaw(pdev, 2);
	} ewse {
		pwiv->wow_iwq = pwatfowm_get_iwq_optionaw(pdev, 1);
	}
	if (pwiv->iwq0 <= 0 || (pwiv->iwq1 <= 0 && !pwiv->is_wite)) {
		wet = -EINVAW;
		goto eww_fwee_netdev;
	}

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base)) {
		wet = PTW_EWW(pwiv->base);
		goto eww_fwee_netdev;
	}

	pwiv->netdev = dev;
	pwiv->pdev = pdev;

	wet = of_get_phy_mode(dn, &pwiv->phy_intewface);
	/* Defauwt to GMII intewface mode */
	if (wet)
		pwiv->phy_intewface = PHY_INTEWFACE_MODE_GMII;

	/* In the case of a fixed PHY, the DT node associated
	 * to the PHY is the Ethewnet MAC DT node.
	 */
	if (of_phy_is_fixed_wink(dn)) {
		wet = of_phy_wegistew_fixed_wink(dn);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to wegistew fixed PHY\n");
			goto eww_fwee_netdev;
		}

		pwiv->phy_dn = dn;
	}

	/* Initiawize netdevice membews */
	wet = of_get_ethdev_addwess(dn, dev);
	if (wet) {
		dev_wawn(&pdev->dev, "using wandom Ethewnet MAC\n");
		eth_hw_addw_wandom(dev);
	}

	SET_NETDEV_DEV(dev, &pdev->dev);
	dev_set_dwvdata(&pdev->dev, dev);
	dev->ethtoow_ops = &bcm_syspowt_ethtoow_ops;
	dev->netdev_ops = &bcm_syspowt_netdev_ops;
	netif_napi_add(dev, &pwiv->napi, bcm_syspowt_poww);

	dev->featuwes |= NETIF_F_WXCSUM | NETIF_F_HIGHDMA |
			 NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
			 NETIF_F_HW_VWAN_CTAG_TX;
	dev->hw_featuwes |= dev->featuwes;
	dev->vwan_featuwes |= dev->featuwes;
	dev->max_mtu = UMAC_MAX_MTU_SIZE;

	/* Wequest the WOW intewwupt and advewtise suspend if avaiwabwe */
	pwiv->wow_iwq_disabwed = 1;
	wet = devm_wequest_iwq(&pdev->dev, pwiv->wow_iwq,
			       bcm_syspowt_wow_isw, 0, dev->name, pwiv);
	if (!wet)
		device_set_wakeup_capabwe(&pdev->dev, 1);

	pwiv->wow_cwk = devm_cwk_get_optionaw(&pdev->dev, "sw_syspowtwow");
	if (IS_EWW(pwiv->wow_cwk)) {
		wet = PTW_EWW(pwiv->wow_cwk);
		goto eww_dewegistew_fixed_wink;
	}

	/* Set the needed headwoom once and fow aww */
	BUIWD_BUG_ON(sizeof(stwuct bcm_tsb) != 8);
	dev->needed_headwoom += sizeof(stwuct bcm_tsb);

	/* wibphy wiww adjust the wink state accowdingwy */
	netif_cawwiew_off(dev);

	pwiv->wx_max_coawesced_fwames = 1;
	u64_stats_init(&pwiv->syncp);

	pwiv->netdev_notifiew.notifiew_caww = bcm_syspowt_netdevice_event;

	wet = wegistew_netdevice_notifiew(&pwiv->netdev_notifiew);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew DSA notifiew\n");
		goto eww_dewegistew_fixed_wink;
	}

	wet = wegistew_netdev(dev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew net_device\n");
		goto eww_dewegistew_notifiew;
	}

	cwk_pwepawe_enabwe(pwiv->cwk);

	pwiv->wev = topctww_weadw(pwiv, WEV_CNTW) & WEV_MASK;
	dev_info(&pdev->dev,
		 "Bwoadcom SYSTEMPOWT%s " WEV_FMT
		 " (iwqs: %d, %d, TXQs: %d, WXQs: %d)\n",
		 pwiv->is_wite ? " Wite" : "",
		 (pwiv->wev >> 8) & 0xff, pwiv->wev & 0xff,
		 pwiv->iwq0, pwiv->iwq1, txq, wxq);

	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn 0;

eww_dewegistew_notifiew:
	unwegistew_netdevice_notifiew(&pwiv->netdev_notifiew);
eww_dewegistew_fixed_wink:
	if (of_phy_is_fixed_wink(dn))
		of_phy_dewegistew_fixed_wink(dn);
eww_fwee_netdev:
	fwee_netdev(dev);
	wetuwn wet;
}

static void bcm_syspowt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = dev_get_dwvdata(&pdev->dev);
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	stwuct device_node *dn = pdev->dev.of_node;

	/* Not much to do, ndo_cwose has been cawwed
	 * and we use managed awwocations
	 */
	unwegistew_netdevice_notifiew(&pwiv->netdev_notifiew);
	unwegistew_netdev(dev);
	if (of_phy_is_fixed_wink(dn))
		of_phy_dewegistew_fixed_wink(dn);
	fwee_netdev(dev);
	dev_set_dwvdata(&pdev->dev, NUWW);
}

static int bcm_syspowt_suspend_to_wow(stwuct bcm_syspowt_pwiv *pwiv)
{
	stwuct net_device *ndev = pwiv->netdev;
	unsigned int timeout = 1000;
	unsigned int index, i = 0;
	u32 weg;

	weg = umac_weadw(pwiv, UMAC_MPD_CTWW);
	if (pwiv->wowopts & (WAKE_MAGIC | WAKE_MAGICSECUWE))
		weg |= MPD_EN;
	weg &= ~PSW_EN;
	if (pwiv->wowopts & WAKE_MAGICSECUWE) {
		/* Pwogwam the SecuweOn passwowd */
		umac_wwitew(pwiv, get_unawigned_be16(&pwiv->sopass[0]),
			    UMAC_PSW_MS);
		umac_wwitew(pwiv, get_unawigned_be32(&pwiv->sopass[2]),
			    UMAC_PSW_WS);
		weg |= PSW_EN;
	}
	umac_wwitew(pwiv, weg, UMAC_MPD_CTWW);

	if (pwiv->wowopts & WAKE_FIWTEW) {
		/* Tuwn on ACPI matching to steaw packets fwom WBUF */
		weg = wbuf_weadw(pwiv, WBUF_CONTWOW);
		if (pwiv->is_wite)
			weg |= WBUF_ACPI_EN_WITE;
		ewse
			weg |= WBUF_ACPI_EN;
		wbuf_wwitew(pwiv, weg, WBUF_CONTWOW);

		/* Enabwe WXCHK, active fiwtews and Bwoadcom tag matching */
		weg = wxchk_weadw(pwiv, WXCHK_CONTWOW);
		weg &= ~(WXCHK_BWCM_TAG_MATCH_MASK <<
			 WXCHK_BWCM_TAG_MATCH_SHIFT);
		fow_each_set_bit(index, pwiv->fiwtews, WXCHK_BWCM_TAG_MAX) {
			weg |= BIT(WXCHK_BWCM_TAG_MATCH_SHIFT + i);
			i++;
		}
		weg |= WXCHK_EN | WXCHK_BWCM_TAG_EN;
		wxchk_wwitew(pwiv, weg, WXCHK_CONTWOW);
	}

	/* Make suwe WBUF entewed WoW mode as wesuwt */
	do {
		weg = wbuf_weadw(pwiv, WBUF_STATUS);
		if (weg & WBUF_WOW_MODE)
			bweak;

		udeway(10);
	} whiwe (timeout-- > 0);

	/* Do not weave the UniMAC WBUF matching onwy MPD packets */
	if (!timeout) {
		mpd_enabwe_set(pwiv, fawse);
		netif_eww(pwiv, wow, ndev, "faiwed to entew WOW mode\n");
		wetuwn -ETIMEDOUT;
	}

	/* UniMAC weceive needs to be tuwned on */
	umac_enabwe_set(pwiv, CMD_WX_EN, 1);

	netif_dbg(pwiv, wow, ndev, "entewed WOW mode\n");

	wetuwn 0;
}

static int __maybe_unused bcm_syspowt_suspend(stwuct device *d)
{
	stwuct net_device *dev = dev_get_dwvdata(d);
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	unsigned int i;
	int wet = 0;
	u32 weg;

	if (!netif_wunning(dev))
		wetuwn 0;

	netif_device_detach(dev);

	bcm_syspowt_netif_stop(dev);

	phy_suspend(dev->phydev);

	/* Disabwe UniMAC WX */
	umac_enabwe_set(pwiv, CMD_WX_EN, 0);

	wet = wdma_enabwe_set(pwiv, 0);
	if (wet) {
		netdev_eww(dev, "WDMA timeout!\n");
		wetuwn wet;
	}

	/* Disabwe WXCHK if enabwed */
	if (pwiv->wx_chk_en) {
		weg = wxchk_weadw(pwiv, WXCHK_CONTWOW);
		weg &= ~WXCHK_EN;
		wxchk_wwitew(pwiv, weg, WXCHK_CONTWOW);
	}

	/* Fwush WX pipe */
	if (!pwiv->wowopts)
		topctww_wwitew(pwiv, WX_FWUSH, WX_FWUSH_CNTW);

	wet = tdma_enabwe_set(pwiv, 0);
	if (wet) {
		netdev_eww(dev, "TDMA timeout!\n");
		wetuwn wet;
	}

	/* Wait fow a packet boundawy */
	usweep_wange(2000, 3000);

	umac_enabwe_set(pwiv, CMD_TX_EN, 0);

	topctww_wwitew(pwiv, TX_FWUSH, TX_FWUSH_CNTW);

	/* Fwee WX/TX wings SW stwuctuwes */
	fow (i = 0; i < dev->num_tx_queues; i++)
		bcm_syspowt_fini_tx_wing(pwiv, i);
	bcm_syspowt_fini_wx_wing(pwiv);

	/* Get pwepawed fow Wake-on-WAN */
	if (device_may_wakeup(d) && pwiv->wowopts) {
		cwk_pwepawe_enabwe(pwiv->wow_cwk);
		wet = bcm_syspowt_suspend_to_wow(pwiv);
	}

	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn wet;
}

static int __maybe_unused bcm_syspowt_wesume(stwuct device *d)
{
	stwuct net_device *dev = dev_get_dwvdata(d);
	stwuct bcm_syspowt_pwiv *pwiv = netdev_pwiv(dev);
	unsigned int i;
	int wet;

	if (!netif_wunning(dev))
		wetuwn 0;

	cwk_pwepawe_enabwe(pwiv->cwk);
	if (pwiv->wowopts)
		cwk_disabwe_unpwepawe(pwiv->wow_cwk);

	umac_weset(pwiv);

	/* Disabwe the UniMAC WX/TX */
	umac_enabwe_set(pwiv, CMD_WX_EN | CMD_TX_EN, 0);

	/* We may have been suspended and nevew weceived a WOW event that
	 * wouwd tuwn off MPD detection, take cawe of that now
	 */
	bcm_syspowt_wesume_fwom_wow(pwiv);

	/* Initiawize both hawdwawe and softwawe wing */
	fow (i = 0; i < dev->num_tx_queues; i++) {
		wet = bcm_syspowt_init_tx_wing(pwiv, i);
		if (wet) {
			netdev_eww(dev, "faiwed to initiawize TX wing %d\n",
				   i);
			goto out_fwee_tx_wings;
		}
	}

	/* Initiawize winked-wist */
	tdma_wwitew(pwiv, TDMA_WW_WAM_INIT_BUSY, TDMA_STATUS);

	/* Initiawize WX wing */
	wet = bcm_syspowt_init_wx_wing(pwiv);
	if (wet) {
		netdev_eww(dev, "faiwed to initiawize WX wing\n");
		goto out_fwee_wx_wing;
	}

	/* WX pipe enabwe */
	topctww_wwitew(pwiv, 0, WX_FWUSH_CNTW);

	wet = wdma_enabwe_set(pwiv, 1);
	if (wet) {
		netdev_eww(dev, "faiwed to enabwe WDMA\n");
		goto out_fwee_wx_wing;
	}

	/* Westowe enabwed featuwes */
	bcm_syspowt_set_featuwes(dev, dev->featuwes);

	wbuf_init(pwiv);

	/* Set maximum fwame wength */
	if (!pwiv->is_wite)
		umac_wwitew(pwiv, UMAC_MAX_MTU_SIZE, UMAC_MAX_FWAME_WEN);
	ewse
		gib_set_pad_extension(pwiv);

	/* Set MAC addwess */
	umac_set_hw_addw(pwiv, dev->dev_addw);

	umac_enabwe_set(pwiv, CMD_WX_EN, 1);

	/* TX pipe enabwe */
	topctww_wwitew(pwiv, 0, TX_FWUSH_CNTW);

	umac_enabwe_set(pwiv, CMD_TX_EN, 1);

	wet = tdma_enabwe_set(pwiv, 1);
	if (wet) {
		netdev_eww(dev, "TDMA timeout!\n");
		goto out_fwee_wx_wing;
	}

	phy_wesume(dev->phydev);

	bcm_syspowt_netif_stawt(dev);

	netif_device_attach(dev);

	wetuwn 0;

out_fwee_wx_wing:
	bcm_syspowt_fini_wx_wing(pwiv);
out_fwee_tx_wings:
	fow (i = 0; i < dev->num_tx_queues; i++)
		bcm_syspowt_fini_tx_wing(pwiv, i);
	cwk_disabwe_unpwepawe(pwiv->cwk);
	wetuwn wet;
}

static SIMPWE_DEV_PM_OPS(bcm_syspowt_pm_ops,
		bcm_syspowt_suspend, bcm_syspowt_wesume);

static stwuct pwatfowm_dwivew bcm_syspowt_dwivew = {
	.pwobe	= bcm_syspowt_pwobe,
	.wemove_new = bcm_syspowt_wemove,
	.dwivew =  {
		.name = "bwcm-systempowt",
		.of_match_tabwe = bcm_syspowt_of_match,
		.pm = &bcm_syspowt_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(bcm_syspowt_dwivew);

MODUWE_AUTHOW("Bwoadcom Cowpowation");
MODUWE_DESCWIPTION("Bwoadcom System Powt Ethewnet MAC dwivew");
MODUWE_AWIAS("pwatfowm:bwcm-systempowt");
MODUWE_WICENSE("GPW");
