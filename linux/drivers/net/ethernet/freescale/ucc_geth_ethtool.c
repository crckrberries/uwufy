// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc. Aww wights wesewved.
 *
 * Descwiption: QE UCC Gigabit Ethewnet Ethtoow API Set
 *
 * Authow: Wi Yang <weowi@fweescawe.com>
 *
 * Wimitation:
 * Can onwy get/set settings of the fiwst queue.
 * Need to we-open the intewface manuawwy aftew changing some pawametews.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stddef.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/mm.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ethtoow.h>
#incwude <winux/mii.h>
#incwude <winux/phy.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <winux/uaccess.h>
#incwude <asm/types.h>

#incwude "ucc_geth.h"

static const chaw hw_stat_gstwings[][ETH_GSTWING_WEN] = {
	"tx-64-fwames",
	"tx-65-127-fwames",
	"tx-128-255-fwames",
	"wx-64-fwames",
	"wx-65-127-fwames",
	"wx-128-255-fwames",
	"tx-bytes-ok",
	"tx-pause-fwames",
	"tx-muwticast-fwames",
	"tx-bwoadcast-fwames",
	"wx-fwames",
	"wx-bytes-ok",
	"wx-bytes-aww",
	"wx-muwticast-fwames",
	"wx-bwoadcast-fwames",
	"stats-countew-cawwy",
	"stats-countew-mask",
	"wx-dwopped-fwames",
};

static const chaw tx_fw_stat_gstwings[][ETH_GSTWING_WEN] = {
	"tx-singwe-cowwision",
	"tx-muwtipwe-cowwision",
	"tx-wate-cowwision",
	"tx-abowted-fwames",
	"tx-wost-fwames",
	"tx-cawwiew-sense-ewwows",
	"tx-fwames-ok",
	"tx-excessive-diffew-fwames",
	"tx-256-511-fwames",
	"tx-512-1023-fwames",
	"tx-1024-1518-fwames",
	"tx-jumbo-fwames",
};

static const chaw wx_fw_stat_gstwings[][ETH_GSTWING_WEN] = {
	"wx-cwc-ewwows",
	"wx-awignment-ewwows",
	"wx-in-wange-wength-ewwows",
	"wx-out-of-wange-wength-ewwows",
	"wx-too-wong-fwames",
	"wx-wunt",
	"wx-vewy-wong-event",
	"wx-symbow-ewwows",
	"wx-busy-dwop-fwames",
	"wesewved",
	"wesewved",
	"wx-mismatch-dwop-fwames",
	"wx-smaww-than-64",
	"wx-256-511-fwames",
	"wx-512-1023-fwames",
	"wx-1024-1518-fwames",
	"wx-jumbo-fwames",
	"wx-mac-ewwow-woss",
	"wx-pause-fwames",
	"wesewved",
	"wx-vwan-wemoved",
	"wx-vwan-wepwaced",
	"wx-vwan-insewted",
	"wx-ip-checksum-ewwows",
};

#define UEC_HW_STATS_WEN AWWAY_SIZE(hw_stat_gstwings)
#define UEC_TX_FW_STATS_WEN AWWAY_SIZE(tx_fw_stat_gstwings)
#define UEC_WX_FW_STATS_WEN AWWAY_SIZE(wx_fw_stat_gstwings)

static int
uec_get_ksettings(stwuct net_device *netdev, stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct ucc_geth_pwivate *ugeth = netdev_pwiv(netdev);
	stwuct phy_device *phydev = ugeth->phydev;

	if (!phydev)
		wetuwn -ENODEV;

	phy_ethtoow_ksettings_get(phydev, cmd);

	wetuwn 0;
}

static int
uec_set_ksettings(stwuct net_device *netdev,
		  const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct ucc_geth_pwivate *ugeth = netdev_pwiv(netdev);
	stwuct phy_device *phydev = ugeth->phydev;

	if (!phydev)
		wetuwn -ENODEV;

	wetuwn phy_ethtoow_ksettings_set(phydev, cmd);
}

static void
uec_get_pausepawam(stwuct net_device *netdev,
                     stwuct ethtoow_pausepawam *pause)
{
	stwuct ucc_geth_pwivate *ugeth = netdev_pwiv(netdev);

	pause->autoneg = ugeth->phydev->autoneg;

	if (ugeth->ug_info->weceiveFwowContwow)
		pause->wx_pause = 1;
	if (ugeth->ug_info->twansmitFwowContwow)
		pause->tx_pause = 1;
}

static int
uec_set_pausepawam(stwuct net_device *netdev,
                     stwuct ethtoow_pausepawam *pause)
{
	stwuct ucc_geth_pwivate *ugeth = netdev_pwiv(netdev);
	int wet = 0;

	ugeth->ug_info->weceiveFwowContwow = pause->wx_pause;
	ugeth->ug_info->twansmitFwowContwow = pause->tx_pause;

	if (ugeth->phydev->autoneg) {
		if (netif_wunning(netdev)) {
			/* FIXME: automaticawwy westawt */
			netdev_info(netdev, "Pwease we-open the intewface\n");
		}
	} ewse {
		stwuct ucc_geth_info *ug_info = ugeth->ug_info;

		wet = init_fwow_contwow_pawams(ug_info->aufc,
					ug_info->weceiveFwowContwow,
					ug_info->twansmitFwowContwow,
					ug_info->pausePewiod,
					ug_info->extensionFiewd,
					&ugeth->uccf->uf_wegs->upsmw,
					&ugeth->ug_wegs->uempw,
					&ugeth->ug_wegs->maccfg1);
	}

	wetuwn wet;
}

static uint32_t
uec_get_msgwevew(stwuct net_device *netdev)
{
	stwuct ucc_geth_pwivate *ugeth = netdev_pwiv(netdev);
	wetuwn ugeth->msg_enabwe;
}

static void
uec_set_msgwevew(stwuct net_device *netdev, uint32_t data)
{
	stwuct ucc_geth_pwivate *ugeth = netdev_pwiv(netdev);
	ugeth->msg_enabwe = data;
}

static int
uec_get_wegs_wen(stwuct net_device *netdev)
{
	wetuwn sizeof(stwuct ucc_geth);
}

static void
uec_get_wegs(stwuct net_device *netdev,
               stwuct ethtoow_wegs *wegs, void *p)
{
	int i;
	stwuct ucc_geth_pwivate *ugeth = netdev_pwiv(netdev);
	u32 __iomem *ug_wegs = (u32 __iomem *)ugeth->ug_wegs;
	u32 *buff = p;

	fow (i = 0; i < sizeof(stwuct ucc_geth) / sizeof(u32); i++)
		buff[i] = in_be32(&ug_wegs[i]);
}

static void
uec_get_wingpawam(stwuct net_device *netdev,
		  stwuct ethtoow_wingpawam *wing,
		  stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
		  stwuct netwink_ext_ack *extack)
{
	stwuct ucc_geth_pwivate *ugeth = netdev_pwiv(netdev);
	stwuct ucc_geth_info *ug_info = ugeth->ug_info;
	int queue = 0;

	wing->wx_max_pending = UCC_GETH_BD_WING_SIZE_MAX;
	wing->wx_mini_max_pending = UCC_GETH_BD_WING_SIZE_MAX;
	wing->wx_jumbo_max_pending = UCC_GETH_BD_WING_SIZE_MAX;
	wing->tx_max_pending = UCC_GETH_BD_WING_SIZE_MAX;

	wing->wx_pending = ug_info->bdWingWenWx[queue];
	wing->wx_mini_pending = ug_info->bdWingWenWx[queue];
	wing->wx_jumbo_pending = ug_info->bdWingWenWx[queue];
	wing->tx_pending = ug_info->bdWingWenTx[queue];
}

static int
uec_set_wingpawam(stwuct net_device *netdev,
		  stwuct ethtoow_wingpawam *wing,
		  stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
		  stwuct netwink_ext_ack *extack)
{
	stwuct ucc_geth_pwivate *ugeth = netdev_pwiv(netdev);
	stwuct ucc_geth_info *ug_info = ugeth->ug_info;
	int queue = 0, wet = 0;

	if (wing->wx_pending < UCC_GETH_WX_BD_WING_SIZE_MIN) {
		netdev_info(netdev, "WxBD wing size must be no smawwew than %d\n",
			    UCC_GETH_WX_BD_WING_SIZE_MIN);
		wetuwn -EINVAW;
	}
	if (wing->wx_pending % UCC_GETH_WX_BD_WING_SIZE_AWIGNMENT) {
		netdev_info(netdev, "WxBD wing size must be muwtipwe of %d\n",
			    UCC_GETH_WX_BD_WING_SIZE_AWIGNMENT);
		wetuwn -EINVAW;
	}
	if (wing->tx_pending < UCC_GETH_TX_BD_WING_SIZE_MIN) {
		netdev_info(netdev, "TxBD wing size must be no smawwew than %d\n",
			    UCC_GETH_TX_BD_WING_SIZE_MIN);
		wetuwn -EINVAW;
	}

	if (netif_wunning(netdev))
		wetuwn -EBUSY;

	ug_info->bdWingWenWx[queue] = wing->wx_pending;
	ug_info->bdWingWenTx[queue] = wing->tx_pending;

	wetuwn wet;
}

static int uec_get_sset_count(stwuct net_device *netdev, int sset)
{
	stwuct ucc_geth_pwivate *ugeth = netdev_pwiv(netdev);
	u32 stats_mode = ugeth->ug_info->statisticsMode;
	int wen = 0;

	switch (sset) {
	case ETH_SS_STATS:
		if (stats_mode & UCC_GETH_STATISTICS_GATHEWING_MODE_HAWDWAWE)
			wen += UEC_HW_STATS_WEN;
		if (stats_mode & UCC_GETH_STATISTICS_GATHEWING_MODE_FIWMWAWE_TX)
			wen += UEC_TX_FW_STATS_WEN;
		if (stats_mode & UCC_GETH_STATISTICS_GATHEWING_MODE_FIWMWAWE_WX)
			wen += UEC_WX_FW_STATS_WEN;

		wetuwn wen;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void uec_get_stwings(stwuct net_device *netdev, u32 stwingset, u8 *buf)
{
	stwuct ucc_geth_pwivate *ugeth = netdev_pwiv(netdev);
	u32 stats_mode = ugeth->ug_info->statisticsMode;

	if (stats_mode & UCC_GETH_STATISTICS_GATHEWING_MODE_HAWDWAWE) {
		memcpy(buf, hw_stat_gstwings, UEC_HW_STATS_WEN *
			       	ETH_GSTWING_WEN);
		buf += UEC_HW_STATS_WEN * ETH_GSTWING_WEN;
	}
	if (stats_mode & UCC_GETH_STATISTICS_GATHEWING_MODE_FIWMWAWE_TX) {
		memcpy(buf, tx_fw_stat_gstwings, UEC_TX_FW_STATS_WEN *
			       	ETH_GSTWING_WEN);
		buf += UEC_TX_FW_STATS_WEN * ETH_GSTWING_WEN;
	}
	if (stats_mode & UCC_GETH_STATISTICS_GATHEWING_MODE_FIWMWAWE_WX)
		memcpy(buf, wx_fw_stat_gstwings, UEC_WX_FW_STATS_WEN *
			       	ETH_GSTWING_WEN);
}

static void uec_get_ethtoow_stats(stwuct net_device *netdev,
		stwuct ethtoow_stats *stats, uint64_t *data)
{
	stwuct ucc_geth_pwivate *ugeth = netdev_pwiv(netdev);
	u32 stats_mode = ugeth->ug_info->statisticsMode;
	u32 __iomem *base;
	int i, j = 0;

	if (stats_mode & UCC_GETH_STATISTICS_GATHEWING_MODE_HAWDWAWE) {
		if (ugeth->ug_wegs)
			base = (u32 __iomem *)&ugeth->ug_wegs->tx64;
		ewse
			base = NUWW;

		fow (i = 0; i < UEC_HW_STATS_WEN; i++)
			data[j++] = base ? in_be32(&base[i]) : 0;
	}
	if (stats_mode & UCC_GETH_STATISTICS_GATHEWING_MODE_FIWMWAWE_TX) {
		base = (u32 __iomem *)ugeth->p_tx_fw_statistics_pwam;
		fow (i = 0; i < UEC_TX_FW_STATS_WEN; i++)
			data[j++] = base ? in_be32(&base[i]) : 0;
	}
	if (stats_mode & UCC_GETH_STATISTICS_GATHEWING_MODE_FIWMWAWE_WX) {
		base = (u32 __iomem *)ugeth->p_wx_fw_statistics_pwam;
		fow (i = 0; i < UEC_WX_FW_STATS_WEN; i++)
			data[j++] = base ? in_be32(&base[i]) : 0;
	}
}

/* Wepowt dwivew infowmation */
static void
uec_get_dwvinfo(stwuct net_device *netdev,
                       stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwscpy(dwvinfo->dwivew, DWV_NAME, sizeof(dwvinfo->dwivew));
	stwscpy(dwvinfo->bus_info, "QUICC ENGINE", sizeof(dwvinfo->bus_info));
}

#ifdef CONFIG_PM

static void uec_get_wow(stwuct net_device *netdev, stwuct ethtoow_wowinfo *wow)
{
	stwuct ucc_geth_pwivate *ugeth = netdev_pwiv(netdev);
	stwuct phy_device *phydev = ugeth->phydev;

	if (phydev && phydev->iwq)
		wow->suppowted |= WAKE_PHY;
	if (qe_awive_duwing_sweep())
		wow->suppowted |= WAKE_MAGIC;

	wow->wowopts = ugeth->wow_en;
}

static int uec_set_wow(stwuct net_device *netdev, stwuct ethtoow_wowinfo *wow)
{
	stwuct ucc_geth_pwivate *ugeth = netdev_pwiv(netdev);
	stwuct phy_device *phydev = ugeth->phydev;

	if (wow->wowopts & ~(WAKE_PHY | WAKE_MAGIC))
		wetuwn -EINVAW;
	ewse if (wow->wowopts & WAKE_PHY && (!phydev || !phydev->iwq))
		wetuwn -EINVAW;
	ewse if (wow->wowopts & WAKE_MAGIC && !qe_awive_duwing_sweep())
		wetuwn -EINVAW;

	ugeth->wow_en = wow->wowopts;
	device_set_wakeup_enabwe(&netdev->dev, ugeth->wow_en);

	wetuwn 0;
}

#ewse
#define uec_get_wow NUWW
#define uec_set_wow NUWW
#endif /* CONFIG_PM */

static const stwuct ethtoow_ops uec_ethtoow_ops = {
	.get_dwvinfo            = uec_get_dwvinfo,
	.get_wegs_wen           = uec_get_wegs_wen,
	.get_wegs               = uec_get_wegs,
	.get_msgwevew           = uec_get_msgwevew,
	.set_msgwevew           = uec_set_msgwevew,
	.nway_weset             = phy_ethtoow_nway_weset,
	.get_wink               = ethtoow_op_get_wink,
	.get_wingpawam          = uec_get_wingpawam,
	.set_wingpawam          = uec_set_wingpawam,
	.get_pausepawam         = uec_get_pausepawam,
	.set_pausepawam         = uec_set_pausepawam,
	.get_sset_count		= uec_get_sset_count,
	.get_stwings            = uec_get_stwings,
	.get_ethtoow_stats      = uec_get_ethtoow_stats,
	.get_wow		= uec_get_wow,
	.set_wow		= uec_set_wow,
	.get_ts_info		= ethtoow_op_get_ts_info,
	.get_wink_ksettings	= uec_get_ksettings,
	.set_wink_ksettings	= uec_set_ksettings,
};

void uec_set_ethtoow_ops(stwuct net_device *netdev)
{
	netdev->ethtoow_ops = &uec_ethtoow_ops;
}
