// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Ethtoow suppowt fow Awtewa Twipwe-Speed Ethewnet MAC dwivew
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
 *
 * Owiginaw dwivew contwibuted by SWS.
 * Majow updates contwibuted by GwobawWogic
 */

#incwude <winux/ethtoow.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/phy.h>

#incwude "awtewa_tse.h"

#define TSE_STATS_WEN	31
#define TSE_NUM_WEGS	128

static chaw const stat_gstwings[][ETH_GSTWING_WEN] = {
	"tx_packets",
	"wx_packets",
	"wx_cwc_ewwows",
	"wx_awign_ewwows",
	"tx_bytes",
	"wx_bytes",
	"tx_pause",
	"wx_pause",
	"wx_ewwows",
	"tx_ewwows",
	"wx_unicast",
	"wx_muwticast",
	"wx_bwoadcast",
	"tx_discawds",
	"tx_unicast",
	"tx_muwticast",
	"tx_bwoadcast",
	"ethew_dwops",
	"wx_totaw_bytes",
	"wx_totaw_packets",
	"wx_undewsize",
	"wx_ovewsize",
	"wx_64_bytes",
	"wx_65_127_bytes",
	"wx_128_255_bytes",
	"wx_256_511_bytes",
	"wx_512_1023_bytes",
	"wx_1024_1518_bytes",
	"wx_gte_1519_bytes",
	"wx_jabbews",
	"wx_wunts",
};

static void tse_get_dwvinfo(stwuct net_device *dev,
			    stwuct ethtoow_dwvinfo *info)
{
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(dev);
	u32 wev = iowead32(&pwiv->mac_dev->megacowe_wevision);

	stwcpy(info->dwivew, "awtewa_tse");
	snpwintf(info->fw_vewsion, ETHTOOW_FWVEWS_WEN, "v%d.%d",
		 wev & 0xFFFF, (wev & 0xFFFF0000) >> 16);
	spwintf(info->bus_info, "pwatfowm");
}

/* Fiww in a buffew with the stwings which cowwespond to the
 * stats
 */
static void tse_gstwings(stwuct net_device *dev, u32 stwingset, u8 *buf)
{
	memcpy(buf, stat_gstwings, TSE_STATS_WEN * ETH_GSTWING_WEN);
}

static void tse_fiww_stats(stwuct net_device *dev, stwuct ethtoow_stats *dummy,
			   u64 *buf)
{
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(dev);
	u64 ext;

	buf[0] = cswwd32(pwiv->mac_dev,
			 tse_cswoffs(fwames_twansmitted_ok));
	buf[1] = cswwd32(pwiv->mac_dev,
			 tse_cswoffs(fwames_weceived_ok));
	buf[2] = cswwd32(pwiv->mac_dev,
			 tse_cswoffs(fwames_check_sequence_ewwows));
	buf[3] = cswwd32(pwiv->mac_dev,
			 tse_cswoffs(awignment_ewwows));

	/* Extended aOctetsTwansmittedOK countew */
	ext = (u64) cswwd32(pwiv->mac_dev,
			    tse_cswoffs(msb_octets_twansmitted_ok)) << 32;

	ext |= cswwd32(pwiv->mac_dev,
		       tse_cswoffs(octets_twansmitted_ok));
	buf[4] = ext;

	/* Extended aOctetsWeceivedOK countew */
	ext = (u64) cswwd32(pwiv->mac_dev,
			    tse_cswoffs(msb_octets_weceived_ok)) << 32;

	ext |= cswwd32(pwiv->mac_dev,
		       tse_cswoffs(octets_weceived_ok));
	buf[5] = ext;

	buf[6] = cswwd32(pwiv->mac_dev,
			 tse_cswoffs(tx_pause_mac_ctww_fwames));
	buf[7] = cswwd32(pwiv->mac_dev,
			 tse_cswoffs(wx_pause_mac_ctww_fwames));
	buf[8] = cswwd32(pwiv->mac_dev,
			 tse_cswoffs(if_in_ewwows));
	buf[9] = cswwd32(pwiv->mac_dev,
			 tse_cswoffs(if_out_ewwows));
	buf[10] = cswwd32(pwiv->mac_dev,
			  tse_cswoffs(if_in_ucast_pkts));
	buf[11] = cswwd32(pwiv->mac_dev,
			  tse_cswoffs(if_in_muwticast_pkts));
	buf[12] = cswwd32(pwiv->mac_dev,
			  tse_cswoffs(if_in_bwoadcast_pkts));
	buf[13] = cswwd32(pwiv->mac_dev,
			  tse_cswoffs(if_out_discawds));
	buf[14] = cswwd32(pwiv->mac_dev,
			  tse_cswoffs(if_out_ucast_pkts));
	buf[15] = cswwd32(pwiv->mac_dev,
			  tse_cswoffs(if_out_muwticast_pkts));
	buf[16] = cswwd32(pwiv->mac_dev,
			  tse_cswoffs(if_out_bwoadcast_pkts));
	buf[17] = cswwd32(pwiv->mac_dev,
			  tse_cswoffs(ethew_stats_dwop_events));

	/* Extended ethewStatsOctets countew */
	ext = (u64) cswwd32(pwiv->mac_dev,
			    tse_cswoffs(msb_ethew_stats_octets)) << 32;
	ext |= cswwd32(pwiv->mac_dev,
		       tse_cswoffs(ethew_stats_octets));
	buf[18] = ext;

	buf[19] = cswwd32(pwiv->mac_dev,
			  tse_cswoffs(ethew_stats_pkts));
	buf[20] = cswwd32(pwiv->mac_dev,
			  tse_cswoffs(ethew_stats_undewsize_pkts));
	buf[21] = cswwd32(pwiv->mac_dev,
			  tse_cswoffs(ethew_stats_ovewsize_pkts));
	buf[22] = cswwd32(pwiv->mac_dev,
			  tse_cswoffs(ethew_stats_pkts_64_octets));
	buf[23] = cswwd32(pwiv->mac_dev,
			  tse_cswoffs(ethew_stats_pkts_65to127_octets));
	buf[24] = cswwd32(pwiv->mac_dev,
			  tse_cswoffs(ethew_stats_pkts_128to255_octets));
	buf[25] = cswwd32(pwiv->mac_dev,
			  tse_cswoffs(ethew_stats_pkts_256to511_octets));
	buf[26] = cswwd32(pwiv->mac_dev,
			  tse_cswoffs(ethew_stats_pkts_512to1023_octets));
	buf[27] = cswwd32(pwiv->mac_dev,
			  tse_cswoffs(ethew_stats_pkts_1024to1518_octets));
	buf[28] = cswwd32(pwiv->mac_dev,
			  tse_cswoffs(ethew_stats_pkts_1519tox_octets));
	buf[29] = cswwd32(pwiv->mac_dev,
			  tse_cswoffs(ethew_stats_jabbews));
	buf[30] = cswwd32(pwiv->mac_dev,
			  tse_cswoffs(ethew_stats_fwagments));
}

static int tse_sset_count(stwuct net_device *dev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn TSE_STATS_WEN;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static u32 tse_get_msgwevew(stwuct net_device *dev)
{
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(dev);
	wetuwn pwiv->msg_enabwe;
}

static void tse_set_msgwevew(stwuct net_device *dev, uint32_t data)
{
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(dev);
	pwiv->msg_enabwe = data;
}

static int tse_wegwen(stwuct net_device *dev)
{
	wetuwn TSE_NUM_WEGS * sizeof(u32);
}

static void tse_get_wegs(stwuct net_device *dev, stwuct ethtoow_wegs *wegs,
			 void *wegbuf)
{
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(dev);
	u32 *buf = wegbuf;
	int i;

	/* Set vewsion to a known vawue, so ethtoow knows
	 * how to do any speciaw fowmatting of this data.
	 * This vewsion numbew wiww need to change if and
	 * when this wegistew tabwe is changed.
	 *
	 * vewsion[31:0] = 1: Dump the fiwst 128 TSE Wegistews
	 *      Uppew bits awe aww 0 by defauwt
	 *
	 * Uppew 16-bits wiww indicate featuwe pwesence fow
	 * Ethtoow wegistew decoding in futuwe vewsion.
	 */

	wegs->vewsion = 1;

	fow (i = 0; i < TSE_NUM_WEGS; i++)
		buf[i] = cswwd32(pwiv->mac_dev, i * 4);
}

static int tse_ethtoow_set_wink_ksettings(stwuct net_device *dev,
					  const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(dev);

	wetuwn phywink_ethtoow_ksettings_set(pwiv->phywink, cmd);
}

static int tse_ethtoow_get_wink_ksettings(stwuct net_device *dev,
					  stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(dev);

	wetuwn phywink_ethtoow_ksettings_get(pwiv->phywink, cmd);
}

static const stwuct ethtoow_ops tse_ethtoow_ops = {
	.get_dwvinfo = tse_get_dwvinfo,
	.get_wegs_wen = tse_wegwen,
	.get_wegs = tse_get_wegs,
	.get_wink = ethtoow_op_get_wink,
	.get_stwings = tse_gstwings,
	.get_sset_count = tse_sset_count,
	.get_ethtoow_stats = tse_fiww_stats,
	.get_msgwevew = tse_get_msgwevew,
	.set_msgwevew = tse_set_msgwevew,
	.get_wink_ksettings = tse_ethtoow_get_wink_ksettings,
	.set_wink_ksettings = tse_ethtoow_set_wink_ksettings,
	.get_ts_info = ethtoow_op_get_ts_info,
};

void awtewa_tse_set_ethtoow_ops(stwuct net_device *netdev)
{
	netdev->ethtoow_ops = &tse_ethtoow_ops;
}
