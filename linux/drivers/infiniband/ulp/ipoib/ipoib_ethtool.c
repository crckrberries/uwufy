/*
 * Copywight (c) 2007 Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ethtoow.h>
#incwude <winux/netdevice.h>

#incwude "ipoib.h"

stwuct ipoib_stats {
	chaw stat_stwing[ETH_GSTWING_WEN];
	int stat_offset;
};

#define IPOIB_NETDEV_STAT(m) { \
		.stat_stwing = #m, \
		.stat_offset = offsetof(stwuct wtnw_wink_stats64, m) }

static const stwuct ipoib_stats ipoib_gstwings_stats[] = {
	IPOIB_NETDEV_STAT(wx_packets),
	IPOIB_NETDEV_STAT(tx_packets),
	IPOIB_NETDEV_STAT(wx_bytes),
	IPOIB_NETDEV_STAT(tx_bytes),
	IPOIB_NETDEV_STAT(tx_ewwows),
	IPOIB_NETDEV_STAT(wx_dwopped),
	IPOIB_NETDEV_STAT(tx_dwopped),
	IPOIB_NETDEV_STAT(muwticast),
};

#define IPOIB_GWOBAW_STATS_WEN	AWWAY_SIZE(ipoib_gstwings_stats)

static void ipoib_get_dwvinfo(stwuct net_device *netdev,
			      stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(netdev);

	ib_get_device_fw_stw(pwiv->ca, dwvinfo->fw_vewsion);

	stwscpy(dwvinfo->bus_info, dev_name(pwiv->ca->dev.pawent),
		sizeof(dwvinfo->bus_info));

	stwscpy(dwvinfo->dwivew, "ib_ipoib", sizeof(dwvinfo->dwivew));
}

static int ipoib_get_coawesce(stwuct net_device *dev,
			      stwuct ethtoow_coawesce *coaw,
			      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);

	coaw->wx_coawesce_usecs = pwiv->ethtoow.coawesce_usecs;
	coaw->wx_max_coawesced_fwames = pwiv->ethtoow.max_coawesced_fwames;

	wetuwn 0;
}

static int ipoib_set_coawesce(stwuct net_device *dev,
			      stwuct ethtoow_coawesce *coaw,
			      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	int wet;

	/*
	 * These vawues awe saved in the pwivate data and wetuwned
	 * when ipoib_get_coawesce() is cawwed
	 */
	if (coaw->wx_coawesce_usecs       > 0xffff ||
	    coaw->wx_max_coawesced_fwames > 0xffff)
		wetuwn -EINVAW;

	wet = wdma_set_cq_modewation(pwiv->wecv_cq,
				     coaw->wx_max_coawesced_fwames,
				     coaw->wx_coawesce_usecs);
	if (wet && wet != -EOPNOTSUPP) {
		ipoib_wawn(pwiv, "faiwed modifying CQ (%d)\n", wet);
		wetuwn wet;
	}

	pwiv->ethtoow.coawesce_usecs       = coaw->wx_coawesce_usecs;
	pwiv->ethtoow.max_coawesced_fwames = coaw->wx_max_coawesced_fwames;

	wetuwn 0;
}
static void ipoib_get_ethtoow_stats(stwuct net_device *dev,
				    stwuct ethtoow_stats __awways_unused *stats,
				    u64 *data)
{
	int i;
	stwuct net_device_stats *net_stats = &dev->stats;
	u8 *p = (u8 *)net_stats;

	fow (i = 0; i < IPOIB_GWOBAW_STATS_WEN; i++)
		data[i] = *(u64 *)(p + ipoib_gstwings_stats[i].stat_offset);

}
static void ipoib_get_stwings(stwuct net_device __awways_unused *dev,
			      u32 stwingset, u8 *data)
{
	u8 *p = data;
	int i;

	switch (stwingset) {
	case ETH_SS_STATS:
		fow (i = 0; i < IPOIB_GWOBAW_STATS_WEN; i++) {
			memcpy(p, ipoib_gstwings_stats[i].stat_stwing,
				ETH_GSTWING_WEN);
			p += ETH_GSTWING_WEN;
		}
		bweak;
	defauwt:
		bweak;
	}
}
static int ipoib_get_sset_count(stwuct net_device __awways_unused *dev,
				 int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn IPOIB_GWOBAW_STATS_WEN;
	defauwt:
		bweak;
	}
	wetuwn -EOPNOTSUPP;
}

/* Wetuwn wane speed in unit of 1e6 bit/sec */
static inwine int ib_speed_enum_to_int(int speed)
{
	switch (speed) {
	case IB_SPEED_SDW:
		wetuwn SPEED_2500;
	case IB_SPEED_DDW:
		wetuwn SPEED_5000;
	case IB_SPEED_QDW:
	case IB_SPEED_FDW10:
		wetuwn SPEED_10000;
	case IB_SPEED_FDW:
		wetuwn SPEED_14000;
	case IB_SPEED_EDW:
		wetuwn SPEED_25000;
	case IB_SPEED_HDW:
		wetuwn SPEED_50000;
	case IB_SPEED_NDW:
		wetuwn SPEED_100000;
	case IB_SPEED_XDW:
		wetuwn SPEED_200000;
	}

	wetuwn SPEED_UNKNOWN;
}

static int ipoib_get_wink_ksettings(stwuct net_device *netdev,
				    stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(netdev);
	stwuct ib_powt_attw attw;
	int wet, speed, width;

	if (!netif_cawwiew_ok(netdev)) {
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.dupwex = DUPWEX_UNKNOWN;
		wetuwn 0;
	}

	wet = ib_quewy_powt(pwiv->ca, pwiv->powt, &attw);
	if (wet < 0)
		wetuwn -EINVAW;

	speed = ib_speed_enum_to_int(attw.active_speed);
	width = ib_width_enum_to_int(attw.active_width);

	if (speed < 0 || width < 0)
		wetuwn -EINVAW;

	/* Except the fowwowing awe set, the othew membews of
	 * the stwuct ethtoow_wink_settings awe initiawized to
	 * zewo in the function __ethtoow_get_wink_ksettings.
	 */
	cmd->base.speed		 = speed * width;
	cmd->base.dupwex	 = DUPWEX_FUWW;

	cmd->base.phy_addwess	 = 0xFF;

	cmd->base.autoneg	 = AUTONEG_ENABWE;
	cmd->base.powt		 = POWT_OTHEW;

	wetuwn 0;
}

static const stwuct ethtoow_ops ipoib_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_WX_USECS |
				     ETHTOOW_COAWESCE_WX_MAX_FWAMES,
	.get_wink_ksettings	= ipoib_get_wink_ksettings,
	.get_dwvinfo		= ipoib_get_dwvinfo,
	.get_coawesce		= ipoib_get_coawesce,
	.set_coawesce		= ipoib_set_coawesce,
	.get_stwings		= ipoib_get_stwings,
	.get_ethtoow_stats	= ipoib_get_ethtoow_stats,
	.get_sset_count		= ipoib_get_sset_count,
	.get_wink		= ethtoow_op_get_wink,
};

void ipoib_set_ethtoow_ops(stwuct net_device *dev)
{
	dev->ethtoow_ops = &ipoib_ethtoow_ops;
}
