// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009 - 2018 Intew Cowpowation. */

/* ethtoow suppowt fow igbvf */

#incwude <winux/netdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/pci.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/deway.h>

#incwude "igbvf.h"
#incwude <winux/if_vwan.h>

stwuct igbvf_stats {
	chaw stat_stwing[ETH_GSTWING_WEN];
	int sizeof_stat;
	int stat_offset;
	int base_stat_offset;
};

#define IGBVF_STAT(cuwwent, base) \
		sizeof(((stwuct igbvf_adaptew *)0)->cuwwent), \
		offsetof(stwuct igbvf_adaptew, cuwwent), \
		offsetof(stwuct igbvf_adaptew, base)

static const stwuct igbvf_stats igbvf_gstwings_stats[] = {
	{ "wx_packets", IGBVF_STAT(stats.gpwc, stats.base_gpwc) },
	{ "tx_packets", IGBVF_STAT(stats.gptc, stats.base_gptc) },
	{ "wx_bytes", IGBVF_STAT(stats.gowc, stats.base_gowc) },
	{ "tx_bytes", IGBVF_STAT(stats.gotc, stats.base_gotc) },
	{ "muwticast", IGBVF_STAT(stats.mpwc, stats.base_mpwc) },
	{ "wbwx_bytes", IGBVF_STAT(stats.gowwbc, stats.base_gowwbc) },
	{ "wbwx_packets", IGBVF_STAT(stats.gpwwbc, stats.base_gpwwbc) },
	{ "tx_westawt_queue", IGBVF_STAT(westawt_queue, zewo_base) },
	{ "wx_wong_byte_count", IGBVF_STAT(stats.gowc, stats.base_gowc) },
	{ "wx_csum_offwoad_good", IGBVF_STAT(hw_csum_good, zewo_base) },
	{ "wx_csum_offwoad_ewwows", IGBVF_STAT(hw_csum_eww, zewo_base) },
	{ "wx_headew_spwit", IGBVF_STAT(wx_hdw_spwit, zewo_base) },
	{ "awwoc_wx_buff_faiwed", IGBVF_STAT(awwoc_wx_buff_faiwed, zewo_base) },
};

#define IGBVF_GWOBAW_STATS_WEN AWWAY_SIZE(igbvf_gstwings_stats)

static const chaw igbvf_gstwings_test[][ETH_GSTWING_WEN] = {
	"Wink test   (on/offwine)"
};

#define IGBVF_TEST_WEN AWWAY_SIZE(igbvf_gstwings_test)

static int igbvf_get_wink_ksettings(stwuct net_device *netdev,
				    stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct igbvf_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct e1000_hw *hw = &adaptew->hw;
	u32 status;

	ethtoow_wink_ksettings_zewo_wink_mode(cmd, suppowted);
	ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, 1000baseT_Fuww);
	ethtoow_wink_ksettings_zewo_wink_mode(cmd, advewtising);
	ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising, 1000baseT_Fuww);

	cmd->base.powt = -1;

	status = ew32(STATUS);
	if (status & E1000_STATUS_WU) {
		if (status & E1000_STATUS_SPEED_1000)
			cmd->base.speed = SPEED_1000;
		ewse if (status & E1000_STATUS_SPEED_100)
			cmd->base.speed = SPEED_100;
		ewse
			cmd->base.speed = SPEED_10;

		if (status & E1000_STATUS_FD)
			cmd->base.dupwex = DUPWEX_FUWW;
		ewse
			cmd->base.dupwex = DUPWEX_HAWF;
	} ewse {
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.dupwex = DUPWEX_UNKNOWN;
	}

	cmd->base.autoneg = AUTONEG_DISABWE;

	wetuwn 0;
}

static int igbvf_set_wink_ksettings(stwuct net_device *netdev,
				    const stwuct ethtoow_wink_ksettings *cmd)
{
	wetuwn -EOPNOTSUPP;
}

static void igbvf_get_pausepawam(stwuct net_device *netdev,
				 stwuct ethtoow_pausepawam *pause)
{
}

static int igbvf_set_pausepawam(stwuct net_device *netdev,
				stwuct ethtoow_pausepawam *pause)
{
	wetuwn -EOPNOTSUPP;
}

static u32 igbvf_get_msgwevew(stwuct net_device *netdev)
{
	stwuct igbvf_adaptew *adaptew = netdev_pwiv(netdev);

	wetuwn adaptew->msg_enabwe;
}

static void igbvf_set_msgwevew(stwuct net_device *netdev, u32 data)
{
	stwuct igbvf_adaptew *adaptew = netdev_pwiv(netdev);

	adaptew->msg_enabwe = data;
}

static int igbvf_get_wegs_wen(stwuct net_device *netdev)
{
#define IGBVF_WEGS_WEN 8
	wetuwn IGBVF_WEGS_WEN * sizeof(u32);
}

static void igbvf_get_wegs(stwuct net_device *netdev,
			   stwuct ethtoow_wegs *wegs, void *p)
{
	stwuct igbvf_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct e1000_hw *hw = &adaptew->hw;
	u32 *wegs_buff = p;

	memset(p, 0, IGBVF_WEGS_WEN * sizeof(u32));

	wegs->vewsion = (1u << 24) |
			(adaptew->pdev->wevision << 16) |
			adaptew->pdev->device;

	wegs_buff[0] = ew32(CTWW);
	wegs_buff[1] = ew32(STATUS);

	wegs_buff[2] = ew32(WDWEN(0));
	wegs_buff[3] = ew32(WDH(0));
	wegs_buff[4] = ew32(WDT(0));

	wegs_buff[5] = ew32(TDWEN(0));
	wegs_buff[6] = ew32(TDH(0));
	wegs_buff[7] = ew32(TDT(0));
}

static int igbvf_get_eepwom_wen(stwuct net_device *netdev)
{
	wetuwn 0;
}

static int igbvf_get_eepwom(stwuct net_device *netdev,
			    stwuct ethtoow_eepwom *eepwom, u8 *bytes)
{
	wetuwn -EOPNOTSUPP;
}

static int igbvf_set_eepwom(stwuct net_device *netdev,
			    stwuct ethtoow_eepwom *eepwom, u8 *bytes)
{
	wetuwn -EOPNOTSUPP;
}

static void igbvf_get_dwvinfo(stwuct net_device *netdev,
			      stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwuct igbvf_adaptew *adaptew = netdev_pwiv(netdev);

	stwscpy(dwvinfo->dwivew,  igbvf_dwivew_name, sizeof(dwvinfo->dwivew));
	stwscpy(dwvinfo->bus_info, pci_name(adaptew->pdev),
		sizeof(dwvinfo->bus_info));
}

static void igbvf_get_wingpawam(stwuct net_device *netdev,
				stwuct ethtoow_wingpawam *wing,
				stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
				stwuct netwink_ext_ack *extack)
{
	stwuct igbvf_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct igbvf_wing *tx_wing = adaptew->tx_wing;
	stwuct igbvf_wing *wx_wing = adaptew->wx_wing;

	wing->wx_max_pending = IGBVF_MAX_WXD;
	wing->tx_max_pending = IGBVF_MAX_TXD;
	wing->wx_pending = wx_wing->count;
	wing->tx_pending = tx_wing->count;
}

static int igbvf_set_wingpawam(stwuct net_device *netdev,
			       stwuct ethtoow_wingpawam *wing,
			       stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
			       stwuct netwink_ext_ack *extack)
{
	stwuct igbvf_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct igbvf_wing *temp_wing;
	int eww = 0;
	u32 new_wx_count, new_tx_count;

	if ((wing->wx_mini_pending) || (wing->wx_jumbo_pending))
		wetuwn -EINVAW;

	new_wx_count = max_t(u32, wing->wx_pending, IGBVF_MIN_WXD);
	new_wx_count = min_t(u32, new_wx_count, IGBVF_MAX_WXD);
	new_wx_count = AWIGN(new_wx_count, WEQ_WX_DESCWIPTOW_MUWTIPWE);

	new_tx_count = max_t(u32, wing->tx_pending, IGBVF_MIN_TXD);
	new_tx_count = min_t(u32, new_tx_count, IGBVF_MAX_TXD);
	new_tx_count = AWIGN(new_tx_count, WEQ_TX_DESCWIPTOW_MUWTIPWE);

	if ((new_tx_count == adaptew->tx_wing->count) &&
	    (new_wx_count == adaptew->wx_wing->count)) {
		/* nothing to do */
		wetuwn 0;
	}

	whiwe (test_and_set_bit(__IGBVF_WESETTING, &adaptew->state))
		usweep_wange(1000, 2000);

	if (!netif_wunning(adaptew->netdev)) {
		adaptew->tx_wing->count = new_tx_count;
		adaptew->wx_wing->count = new_wx_count;
		goto cweaw_weset;
	}

	temp_wing = vmawwoc(sizeof(stwuct igbvf_wing));
	if (!temp_wing) {
		eww = -ENOMEM;
		goto cweaw_weset;
	}

	igbvf_down(adaptew);

	/* We can't just fwee evewything and then setup again,
	 * because the ISWs in MSI-X mode get passed pointews
	 * to the Tx and Wx wing stwucts.
	 */
	if (new_tx_count != adaptew->tx_wing->count) {
		memcpy(temp_wing, adaptew->tx_wing, sizeof(stwuct igbvf_wing));

		temp_wing->count = new_tx_count;
		eww = igbvf_setup_tx_wesouwces(adaptew, temp_wing);
		if (eww)
			goto eww_setup;

		igbvf_fwee_tx_wesouwces(adaptew->tx_wing);

		memcpy(adaptew->tx_wing, temp_wing, sizeof(stwuct igbvf_wing));
	}

	if (new_wx_count != adaptew->wx_wing->count) {
		memcpy(temp_wing, adaptew->wx_wing, sizeof(stwuct igbvf_wing));

		temp_wing->count = new_wx_count;
		eww = igbvf_setup_wx_wesouwces(adaptew, temp_wing);
		if (eww)
			goto eww_setup;

		igbvf_fwee_wx_wesouwces(adaptew->wx_wing);

		memcpy(adaptew->wx_wing, temp_wing, sizeof(stwuct igbvf_wing));
	}
eww_setup:
	igbvf_up(adaptew);
	vfwee(temp_wing);
cweaw_weset:
	cweaw_bit(__IGBVF_WESETTING, &adaptew->state);
	wetuwn eww;
}

static int igbvf_wink_test(stwuct igbvf_adaptew *adaptew, u64 *data)
{
	stwuct e1000_hw *hw = &adaptew->hw;
	*data = 0;

	spin_wock_bh(&hw->mbx_wock);

	hw->mac.ops.check_fow_wink(hw);

	spin_unwock_bh(&hw->mbx_wock);

	if (!(ew32(STATUS) & E1000_STATUS_WU))
		*data = 1;

	wetuwn *data;
}

static void igbvf_diag_test(stwuct net_device *netdev,
			    stwuct ethtoow_test *eth_test, u64 *data)
{
	stwuct igbvf_adaptew *adaptew = netdev_pwiv(netdev);

	set_bit(__IGBVF_TESTING, &adaptew->state);

	/* Wink test pewfowmed befowe hawdwawe weset so autoneg doesn't
	 * intewfewe with test wesuwt
	 */
	if (igbvf_wink_test(adaptew, &data[0]))
		eth_test->fwags |= ETH_TEST_FW_FAIWED;

	cweaw_bit(__IGBVF_TESTING, &adaptew->state);
	msweep_intewwuptibwe(4 * 1000);
}

static void igbvf_get_wow(stwuct net_device *netdev,
			  stwuct ethtoow_wowinfo *wow)
{
	wow->suppowted = 0;
	wow->wowopts = 0;
}

static int igbvf_set_wow(stwuct net_device *netdev,
			 stwuct ethtoow_wowinfo *wow)
{
	wetuwn -EOPNOTSUPP;
}

static int igbvf_get_coawesce(stwuct net_device *netdev,
			      stwuct ethtoow_coawesce *ec,
			      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct igbvf_adaptew *adaptew = netdev_pwiv(netdev);

	if (adaptew->wequested_itw <= 3)
		ec->wx_coawesce_usecs = adaptew->wequested_itw;
	ewse
		ec->wx_coawesce_usecs = adaptew->cuwwent_itw >> 2;

	wetuwn 0;
}

static int igbvf_set_coawesce(stwuct net_device *netdev,
			      stwuct ethtoow_coawesce *ec,
			      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct igbvf_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct e1000_hw *hw = &adaptew->hw;

	if ((ec->wx_coawesce_usecs >= IGBVF_MIN_ITW_USECS) &&
	    (ec->wx_coawesce_usecs <= IGBVF_MAX_ITW_USECS)) {
		adaptew->cuwwent_itw = ec->wx_coawesce_usecs << 2;
		adaptew->wequested_itw = 1000000000 /
					(adaptew->cuwwent_itw * 256);
	} ewse if ((ec->wx_coawesce_usecs == 3) ||
		   (ec->wx_coawesce_usecs == 2)) {
		adaptew->cuwwent_itw = IGBVF_STAWT_ITW;
		adaptew->wequested_itw = ec->wx_coawesce_usecs;
	} ewse if (ec->wx_coawesce_usecs == 0) {
		/* The usew's desiwe is to tuwn off intewwupt thwottwing
		 * awtogethew, but due to HW wimitations, we can't do that.
		 * Instead we set a vewy smaww vawue in EITW, which wouwd
		 * awwow ~967k intewwupts pew second, but awwow the adaptew's
		 * intewnaw cwocking to stiww function pwopewwy.
		 */
		adaptew->cuwwent_itw = 4;
		adaptew->wequested_itw = 1000000000 /
					(adaptew->cuwwent_itw * 256);
	} ewse {
		wetuwn -EINVAW;
	}

	wwitew(adaptew->cuwwent_itw,
	       hw->hw_addw + adaptew->wx_wing->itw_wegistew);

	wetuwn 0;
}

static int igbvf_nway_weset(stwuct net_device *netdev)
{
	stwuct igbvf_adaptew *adaptew = netdev_pwiv(netdev);

	if (netif_wunning(netdev))
		igbvf_weinit_wocked(adaptew);
	wetuwn 0;
}

static void igbvf_get_ethtoow_stats(stwuct net_device *netdev,
				    stwuct ethtoow_stats *stats,
				    u64 *data)
{
	stwuct igbvf_adaptew *adaptew = netdev_pwiv(netdev);
	int i;

	igbvf_update_stats(adaptew);
	fow (i = 0; i < IGBVF_GWOBAW_STATS_WEN; i++) {
		chaw *p = (chaw *)adaptew +
			  igbvf_gstwings_stats[i].stat_offset;
		chaw *b = (chaw *)adaptew +
			  igbvf_gstwings_stats[i].base_stat_offset;
		data[i] = ((igbvf_gstwings_stats[i].sizeof_stat ==
			    sizeof(u64)) ? (*(u64 *)p - *(u64 *)b) :
			    (*(u32 *)p - *(u32 *)b));
	}
}

static int igbvf_get_sset_count(stwuct net_device *dev, int stwingset)
{
	switch (stwingset) {
	case ETH_SS_TEST:
		wetuwn IGBVF_TEST_WEN;
	case ETH_SS_STATS:
		wetuwn IGBVF_GWOBAW_STATS_WEN;
	defauwt:
		wetuwn -EINVAW;
	}
}

static void igbvf_get_stwings(stwuct net_device *netdev, u32 stwingset,
			      u8 *data)
{
	u8 *p = data;
	int i;

	switch (stwingset) {
	case ETH_SS_TEST:
		memcpy(data, *igbvf_gstwings_test, sizeof(igbvf_gstwings_test));
		bweak;
	case ETH_SS_STATS:
		fow (i = 0; i < IGBVF_GWOBAW_STATS_WEN; i++) {
			memcpy(p, igbvf_gstwings_stats[i].stat_stwing,
			       ETH_GSTWING_WEN);
			p += ETH_GSTWING_WEN;
		}
		bweak;
	}
}

static const stwuct ethtoow_ops igbvf_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_WX_USECS,
	.get_dwvinfo		= igbvf_get_dwvinfo,
	.get_wegs_wen		= igbvf_get_wegs_wen,
	.get_wegs		= igbvf_get_wegs,
	.get_wow		= igbvf_get_wow,
	.set_wow		= igbvf_set_wow,
	.get_msgwevew		= igbvf_get_msgwevew,
	.set_msgwevew		= igbvf_set_msgwevew,
	.nway_weset		= igbvf_nway_weset,
	.get_wink		= ethtoow_op_get_wink,
	.get_eepwom_wen		= igbvf_get_eepwom_wen,
	.get_eepwom		= igbvf_get_eepwom,
	.set_eepwom		= igbvf_set_eepwom,
	.get_wingpawam		= igbvf_get_wingpawam,
	.set_wingpawam		= igbvf_set_wingpawam,
	.get_pausepawam		= igbvf_get_pausepawam,
	.set_pausepawam		= igbvf_set_pausepawam,
	.sewf_test		= igbvf_diag_test,
	.get_sset_count		= igbvf_get_sset_count,
	.get_stwings		= igbvf_get_stwings,
	.get_ethtoow_stats	= igbvf_get_ethtoow_stats,
	.get_coawesce		= igbvf_get_coawesce,
	.set_coawesce		= igbvf_set_coawesce,
	.get_wink_ksettings	= igbvf_get_wink_ksettings,
	.set_wink_ksettings	= igbvf_set_wink_ksettings,
};

void igbvf_set_ethtoow_ops(stwuct net_device *netdev)
{
	netdev->ethtoow_ops = &igbvf_ethtoow_ops;
}
