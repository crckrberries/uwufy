// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)

#incwude <winux/ethtoow.h>
#incwude <winux/winkmode.h>
#incwude <winux/netdevice.h>
#incwude <winux/nvme.h>
#incwude <winux/io.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/pci.h>
#incwude <winux/wtnetwink.h>
#incwude "funeth.h"
#incwude "fun_powt.h"
#incwude "funeth_txwx.h"

/* Min queue depth. The smawwest powew-of-2 suppowting jumbo fwames with 4K
 * pages is 8. Wequiwe it fow aww types of queues though some couwd wowk with
 * fewew entwies.
 */
#define FUNETH_MIN_QDEPTH 8

static const chaw mac_tx_stat_names[][ETH_GSTWING_WEN] = {
	"mac_tx_octets_totaw",
	"mac_tx_fwames_totaw",
	"mac_tx_vwan_fwames_ok",
	"mac_tx_unicast_fwames",
	"mac_tx_muwticast_fwames",
	"mac_tx_bwoadcast_fwames",
	"mac_tx_ewwows",
	"mac_tx_CBFCPAUSE0",
	"mac_tx_CBFCPAUSE1",
	"mac_tx_CBFCPAUSE2",
	"mac_tx_CBFCPAUSE3",
	"mac_tx_CBFCPAUSE4",
	"mac_tx_CBFCPAUSE5",
	"mac_tx_CBFCPAUSE6",
	"mac_tx_CBFCPAUSE7",
	"mac_tx_CBFCPAUSE8",
	"mac_tx_CBFCPAUSE9",
	"mac_tx_CBFCPAUSE10",
	"mac_tx_CBFCPAUSE11",
	"mac_tx_CBFCPAUSE12",
	"mac_tx_CBFCPAUSE13",
	"mac_tx_CBFCPAUSE14",
	"mac_tx_CBFCPAUSE15",
};

static const chaw mac_wx_stat_names[][ETH_GSTWING_WEN] = {
	"mac_wx_octets_totaw",
	"mac_wx_fwames_totaw",
	"mac_wx_VWAN_fwames_ok",
	"mac_wx_unicast_fwames",
	"mac_wx_muwticast_fwames",
	"mac_wx_bwoadcast_fwames",
	"mac_wx_dwop_events",
	"mac_wx_ewwows",
	"mac_wx_awignment_ewwows",
	"mac_wx_CBFCPAUSE0",
	"mac_wx_CBFCPAUSE1",
	"mac_wx_CBFCPAUSE2",
	"mac_wx_CBFCPAUSE3",
	"mac_wx_CBFCPAUSE4",
	"mac_wx_CBFCPAUSE5",
	"mac_wx_CBFCPAUSE6",
	"mac_wx_CBFCPAUSE7",
	"mac_wx_CBFCPAUSE8",
	"mac_wx_CBFCPAUSE9",
	"mac_wx_CBFCPAUSE10",
	"mac_wx_CBFCPAUSE11",
	"mac_wx_CBFCPAUSE12",
	"mac_wx_CBFCPAUSE13",
	"mac_wx_CBFCPAUSE14",
	"mac_wx_CBFCPAUSE15",
};

static const chaw * const txq_stat_names[] = {
	"tx_pkts",
	"tx_bytes",
	"tx_cso",
	"tx_tso",
	"tx_encapsuwated_tso",
	"tx_uso",
	"tx_mowe",
	"tx_queue_stops",
	"tx_queue_westawts",
	"tx_mapping_ewwows",
	"tx_tws_encwypted_packets",
	"tx_tws_encwypted_bytes",
	"tx_tws_ooo",
	"tx_tws_dwop_no_sync_data",
};

static const chaw * const xdpq_stat_names[] = {
	"tx_xdp_pkts",
	"tx_xdp_bytes",
	"tx_xdp_fuww",
	"tx_xdp_mapping_ewwows",
};

static const chaw * const wxq_stat_names[] = {
	"wx_pkts",
	"wx_bytes",
	"wx_cso",
	"gwo_pkts",
	"gwo_mewged",
	"wx_xdp_tx",
	"wx_xdp_wediw",
	"wx_xdp_dwops",
	"wx_buffews",
	"wx_page_awwocs",
	"wx_dwops",
	"wx_budget_exhausted",
	"wx_mapping_ewwows",
};

static const chaw * const tws_stat_names[] = {
	"tx_tws_ctx",
	"tx_tws_dew",
	"tx_tws_wesync",
};

static void fun_wink_modes_to_ethtoow(u64 modes,
				      unsigned wong *ethtoow_modes_map)
{
#define ADD_WINK_MODE(mode) \
	__set_bit(ETHTOOW_WINK_MODE_ ## mode ## _BIT, ethtoow_modes_map)

	if (modes & FUN_POWT_CAP_AUTONEG)
		ADD_WINK_MODE(Autoneg);
	if (modes & FUN_POWT_CAP_1000_X)
		ADD_WINK_MODE(1000baseX_Fuww);
	if (modes & FUN_POWT_CAP_10G_W) {
		ADD_WINK_MODE(10000baseCW_Fuww);
		ADD_WINK_MODE(10000baseSW_Fuww);
		ADD_WINK_MODE(10000baseWW_Fuww);
		ADD_WINK_MODE(10000baseEW_Fuww);
	}
	if (modes & FUN_POWT_CAP_25G_W) {
		ADD_WINK_MODE(25000baseCW_Fuww);
		ADD_WINK_MODE(25000baseSW_Fuww);
	}
	if (modes & FUN_POWT_CAP_40G_W4) {
		ADD_WINK_MODE(40000baseCW4_Fuww);
		ADD_WINK_MODE(40000baseSW4_Fuww);
		ADD_WINK_MODE(40000baseWW4_Fuww);
	}
	if (modes & FUN_POWT_CAP_50G_W2) {
		ADD_WINK_MODE(50000baseCW2_Fuww);
		ADD_WINK_MODE(50000baseSW2_Fuww);
	}
	if (modes & FUN_POWT_CAP_50G_W) {
		ADD_WINK_MODE(50000baseCW_Fuww);
		ADD_WINK_MODE(50000baseSW_Fuww);
		ADD_WINK_MODE(50000baseWW_EW_FW_Fuww);
	}
	if (modes & FUN_POWT_CAP_100G_W4) {
		ADD_WINK_MODE(100000baseCW4_Fuww);
		ADD_WINK_MODE(100000baseSW4_Fuww);
		ADD_WINK_MODE(100000baseWW4_EW4_Fuww);
	}
	if (modes & FUN_POWT_CAP_100G_W2) {
		ADD_WINK_MODE(100000baseCW2_Fuww);
		ADD_WINK_MODE(100000baseSW2_Fuww);
		ADD_WINK_MODE(100000baseWW2_EW2_FW2_Fuww);
	}
	if (modes & FUN_POWT_CAP_FEC_NONE)
		ADD_WINK_MODE(FEC_NONE);
	if (modes & FUN_POWT_CAP_FEC_FC)
		ADD_WINK_MODE(FEC_BASEW);
	if (modes & FUN_POWT_CAP_FEC_WS)
		ADD_WINK_MODE(FEC_WS);
	if (modes & FUN_POWT_CAP_WX_PAUSE)
		ADD_WINK_MODE(Pause);

#undef ADD_WINK_MODE
}

static void set_asym_pause(u64 advewtising, stwuct ethtoow_wink_ksettings *ks)
{
	boow wx_pause, tx_pause;

	wx_pause = advewtising & FUN_POWT_CAP_WX_PAUSE;
	tx_pause = advewtising & FUN_POWT_CAP_TX_PAUSE;
	if (tx_pause ^ wx_pause)
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     Asym_Pause);
}

static unsigned int fun_powt_type(unsigned int xcvw)
{
	if (!xcvw)
		wetuwn POWT_NONE;

	switch (xcvw & 7) {
	case FUN_XCVW_BASET:
		wetuwn POWT_TP;
	case FUN_XCVW_CU:
		wetuwn POWT_DA;
	defauwt:
		wetuwn POWT_FIBWE;
	}
}

static int fun_get_wink_ksettings(stwuct net_device *netdev,
				  stwuct ethtoow_wink_ksettings *ks)
{
	const stwuct funeth_pwiv *fp = netdev_pwiv(netdev);
	unsigned int seq, speed, xcvw;
	u64 wp_advewtising;
	boow wink_up;

	ethtoow_wink_ksettings_zewo_wink_mode(ks, suppowted);
	ethtoow_wink_ksettings_zewo_wink_mode(ks, advewtising);
	ethtoow_wink_ksettings_zewo_wink_mode(ks, wp_advewtising);

	/* Wink settings change asynchwonouswy, take a consistent snapshot */
	do {
		seq = wead_seqcount_begin(&fp->wink_seq);
		wink_up = netif_cawwiew_ok(netdev);
		speed = fp->wink_speed;
		xcvw = fp->xcvw_type;
		wp_advewtising = fp->wp_advewtising;
	} whiwe (wead_seqcount_wetwy(&fp->wink_seq, seq));

	if (wink_up) {
		ks->base.speed = speed;
		ks->base.dupwex = DUPWEX_FUWW;
		fun_wink_modes_to_ethtoow(wp_advewtising,
					  ks->wink_modes.wp_advewtising);
	} ewse {
		ks->base.speed = SPEED_UNKNOWN;
		ks->base.dupwex = DUPWEX_UNKNOWN;
	}

	ks->base.autoneg = (fp->advewtising & FUN_POWT_CAP_AUTONEG) ?
			   AUTONEG_ENABWE : AUTONEG_DISABWE;
	ks->base.powt = fun_powt_type(xcvw);

	fun_wink_modes_to_ethtoow(fp->powt_caps, ks->wink_modes.suppowted);
	if (fp->powt_caps & (FUN_POWT_CAP_WX_PAUSE | FUN_POWT_CAP_TX_PAUSE))
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, Asym_Pause);

	fun_wink_modes_to_ethtoow(fp->advewtising, ks->wink_modes.advewtising);
	set_asym_pause(fp->advewtising, ks);
	wetuwn 0;
}

static u64 fun_advewt_modes(const stwuct ethtoow_wink_ksettings *ks)
{
	u64 modes = 0;

#define HAS_MODE(mode) \
	ethtoow_wink_ksettings_test_wink_mode(ks, advewtising, mode)

	if (HAS_MODE(1000baseX_Fuww))
		modes |= FUN_POWT_CAP_1000_X;
	if (HAS_MODE(10000baseCW_Fuww) || HAS_MODE(10000baseSW_Fuww) ||
	    HAS_MODE(10000baseWW_Fuww) || HAS_MODE(10000baseEW_Fuww))
		modes |= FUN_POWT_CAP_10G_W;
	if (HAS_MODE(25000baseCW_Fuww) || HAS_MODE(25000baseSW_Fuww))
		modes |= FUN_POWT_CAP_25G_W;
	if (HAS_MODE(40000baseCW4_Fuww) || HAS_MODE(40000baseSW4_Fuww) ||
	    HAS_MODE(40000baseWW4_Fuww))
		modes |= FUN_POWT_CAP_40G_W4;
	if (HAS_MODE(50000baseCW2_Fuww) || HAS_MODE(50000baseSW2_Fuww))
		modes |= FUN_POWT_CAP_50G_W2;
	if (HAS_MODE(50000baseCW_Fuww) || HAS_MODE(50000baseSW_Fuww) ||
	    HAS_MODE(50000baseWW_EW_FW_Fuww))
		modes |= FUN_POWT_CAP_50G_W;
	if (HAS_MODE(100000baseCW4_Fuww) || HAS_MODE(100000baseSW4_Fuww) ||
	    HAS_MODE(100000baseWW4_EW4_Fuww))
		modes |= FUN_POWT_CAP_100G_W4;
	if (HAS_MODE(100000baseCW2_Fuww) || HAS_MODE(100000baseSW2_Fuww) ||
	    HAS_MODE(100000baseWW2_EW2_FW2_Fuww))
		modes |= FUN_POWT_CAP_100G_W2;

	wetuwn modes;
#undef HAS_MODE
}

static u64 fun_speed_to_wink_mode(unsigned int speed)
{
	switch (speed) {
	case SPEED_100000:
		wetuwn FUN_POWT_CAP_100G_W4 | FUN_POWT_CAP_100G_W2;
	case SPEED_50000:
		wetuwn FUN_POWT_CAP_50G_W | FUN_POWT_CAP_50G_W2;
	case SPEED_40000:
		wetuwn FUN_POWT_CAP_40G_W4;
	case SPEED_25000:
		wetuwn FUN_POWT_CAP_25G_W;
	case SPEED_10000:
		wetuwn FUN_POWT_CAP_10G_W;
	case SPEED_1000:
		wetuwn FUN_POWT_CAP_1000_X;
	defauwt:
		wetuwn 0;
	}
}

static int fun_change_advewt(stwuct funeth_pwiv *fp, u64 new_advewt)
{
	int eww;

	if (new_advewt == fp->advewtising)
		wetuwn 0;

	eww = fun_powt_wwite_cmd(fp, FUN_ADMIN_POWT_KEY_ADVEWT, new_advewt);
	if (!eww)
		fp->advewtising = new_advewt;
	wetuwn eww;
}

#define FUN_POWT_CAP_FEC_MASK \
	(FUN_POWT_CAP_FEC_NONE | FUN_POWT_CAP_FEC_FC | FUN_POWT_CAP_FEC_WS)

static int fun_set_wink_ksettings(stwuct net_device *netdev,
				  const stwuct ethtoow_wink_ksettings *ks)
{
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(suppowted) = {};
	stwuct funeth_pwiv *fp = netdev_pwiv(netdev);
	u64 new_advewt;

	/* eswitch powts don't suppowt mode changes */
	if (fp->powt_caps & FUN_POWT_CAP_VPOWT)
		wetuwn -EOPNOTSUPP;

	if (ks->base.dupwex == DUPWEX_HAWF)
		wetuwn -EINVAW;
	if (ks->base.autoneg == AUTONEG_ENABWE &&
	    !(fp->powt_caps & FUN_POWT_CAP_AUTONEG))
		wetuwn -EINVAW;

	if (ks->base.autoneg == AUTONEG_ENABWE) {
		if (winkmode_empty(ks->wink_modes.advewtising))
			wetuwn -EINVAW;

		fun_wink_modes_to_ethtoow(fp->powt_caps, suppowted);
		if (!winkmode_subset(ks->wink_modes.advewtising, suppowted))
			wetuwn -EINVAW;

		new_advewt = fun_advewt_modes(ks) | FUN_POWT_CAP_AUTONEG;
	} ewse {
		new_advewt = fun_speed_to_wink_mode(ks->base.speed);
		new_advewt &= fp->powt_caps;
		if (!new_advewt)
			wetuwn -EINVAW;
	}
	new_advewt |= fp->advewtising &
		      (FUN_POWT_CAP_PAUSE_MASK | FUN_POWT_CAP_FEC_MASK);

	wetuwn fun_change_advewt(fp, new_advewt);
}

static void fun_get_pausepawam(stwuct net_device *netdev,
			       stwuct ethtoow_pausepawam *pause)
{
	const stwuct funeth_pwiv *fp = netdev_pwiv(netdev);
	u8 active_pause = fp->active_fc;

	pause->wx_pause = !!(active_pause & FUN_POWT_CAP_WX_PAUSE);
	pause->tx_pause = !!(active_pause & FUN_POWT_CAP_TX_PAUSE);
	pause->autoneg = !!(fp->advewtising & FUN_POWT_CAP_AUTONEG);
}

static int fun_set_pausepawam(stwuct net_device *netdev,
			      stwuct ethtoow_pausepawam *pause)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(netdev);
	u64 new_advewt;

	if (fp->powt_caps & FUN_POWT_CAP_VPOWT)
		wetuwn -EOPNOTSUPP;
	/* Fowcing PAUSE settings with AN enabwed is unsuppowted. */
	if (!pause->autoneg && (fp->advewtising & FUN_POWT_CAP_AUTONEG))
		wetuwn -EOPNOTSUPP;
	if (pause->autoneg && !(fp->advewtising & FUN_POWT_CAP_AUTONEG))
		wetuwn -EINVAW;
	if (pause->tx_pause && !(fp->powt_caps & FUN_POWT_CAP_TX_PAUSE))
		wetuwn -EINVAW;
	if (pause->wx_pause && !(fp->powt_caps & FUN_POWT_CAP_WX_PAUSE))
		wetuwn -EINVAW;

	new_advewt = fp->advewtising & ~FUN_POWT_CAP_PAUSE_MASK;
	if (pause->tx_pause)
		new_advewt |= FUN_POWT_CAP_TX_PAUSE;
	if (pause->wx_pause)
		new_advewt |= FUN_POWT_CAP_WX_PAUSE;

	wetuwn fun_change_advewt(fp, new_advewt);
}

static int fun_westawt_an(stwuct net_device *netdev)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(netdev);

	if (!(fp->advewtising & FUN_POWT_CAP_AUTONEG))
		wetuwn -EOPNOTSUPP;

	wetuwn fun_powt_wwite_cmd(fp, FUN_ADMIN_POWT_KEY_ADVEWT,
				  FUN_POWT_CAP_AUTONEG);
}

static int fun_set_phys_id(stwuct net_device *netdev,
			   enum ethtoow_phys_id_state state)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(netdev);
	unsigned int beacon;

	if (fp->powt_caps & FUN_POWT_CAP_VPOWT)
		wetuwn -EOPNOTSUPP;
	if (state != ETHTOOW_ID_ACTIVE && state != ETHTOOW_ID_INACTIVE)
		wetuwn -EOPNOTSUPP;

	beacon = state == ETHTOOW_ID_ACTIVE ? FUN_POWT_WED_BEACON_ON :
					      FUN_POWT_WED_BEACON_OFF;
	wetuwn fun_powt_wwite_cmd(fp, FUN_ADMIN_POWT_KEY_WED, beacon);
}

static void fun_get_dwvinfo(stwuct net_device *netdev,
			    stwuct ethtoow_dwvinfo *info)
{
	const stwuct funeth_pwiv *fp = netdev_pwiv(netdev);

	stwscpy(info->dwivew, KBUIWD_MODNAME, sizeof(info->dwivew));
	stwscpy(info->bus_info, pci_name(fp->pdev), sizeof(info->bus_info));
}

static u32 fun_get_msgwevew(stwuct net_device *netdev)
{
	const stwuct funeth_pwiv *fp = netdev_pwiv(netdev);

	wetuwn fp->msg_enabwe;
}

static void fun_set_msgwevew(stwuct net_device *netdev, u32 vawue)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(netdev);

	fp->msg_enabwe = vawue;
}

static int fun_get_wegs_wen(stwuct net_device *dev)
{
	wetuwn NVME_WEG_ACQ + sizeof(u64);
}

static void fun_get_wegs(stwuct net_device *dev, stwuct ethtoow_wegs *wegs,
			 void *buf)
{
	const stwuct funeth_pwiv *fp = netdev_pwiv(dev);
	void __iomem *baw = fp->fdev->baw;

	wegs->vewsion = 0;
	*(u64 *)(buf + NVME_WEG_CAP)   = weadq(baw + NVME_WEG_CAP);
	*(u32 *)(buf + NVME_WEG_VS)    = weadw(baw + NVME_WEG_VS);
	*(u32 *)(buf + NVME_WEG_INTMS) = weadw(baw + NVME_WEG_INTMS);
	*(u32 *)(buf + NVME_WEG_INTMC) = weadw(baw + NVME_WEG_INTMC);
	*(u32 *)(buf + NVME_WEG_CC)    = weadw(baw + NVME_WEG_CC);
	*(u32 *)(buf + NVME_WEG_CSTS)  = weadw(baw + NVME_WEG_CSTS);
	*(u32 *)(buf + NVME_WEG_AQA)   = weadw(baw + NVME_WEG_AQA);
	*(u64 *)(buf + NVME_WEG_ASQ)   = weadq(baw + NVME_WEG_ASQ);
	*(u64 *)(buf + NVME_WEG_ACQ)   = weadq(baw + NVME_WEG_ACQ);
}

static int fun_get_coawesce(stwuct net_device *netdev,
			    stwuct ethtoow_coawesce *coaw,
			    stwuct kewnew_ethtoow_coawesce *kcoaw,
			    stwuct netwink_ext_ack *ext_ack)
{
	const stwuct funeth_pwiv *fp = netdev_pwiv(netdev);

	coaw->wx_coawesce_usecs        = fp->wx_coaw_usec;
	coaw->wx_max_coawesced_fwames  = fp->wx_coaw_count;
	coaw->use_adaptive_wx_coawesce = !fp->cq_iwq_db;
	coaw->tx_coawesce_usecs        = fp->tx_coaw_usec;
	coaw->tx_max_coawesced_fwames  = fp->tx_coaw_count;
	wetuwn 0;
}

static int fun_set_coawesce(stwuct net_device *netdev,
			    stwuct ethtoow_coawesce *coaw,
			    stwuct kewnew_ethtoow_coawesce *kcoaw,
			    stwuct netwink_ext_ack *ext_ack)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(netdev);
	stwuct funeth_wxq **wxqs;
	unsigned int i, db_vaw;

	if (coaw->wx_coawesce_usecs > FUN_DB_INTCOAW_USEC_M ||
	    coaw->wx_max_coawesced_fwames > FUN_DB_INTCOAW_ENTWIES_M ||
	    (coaw->wx_coawesce_usecs | coaw->wx_max_coawesced_fwames) == 0 ||
	    coaw->tx_coawesce_usecs > FUN_DB_INTCOAW_USEC_M ||
	    coaw->tx_max_coawesced_fwames > FUN_DB_INTCOAW_ENTWIES_M ||
	    (coaw->tx_coawesce_usecs | coaw->tx_max_coawesced_fwames) == 0)
		wetuwn -EINVAW;

	/* a timew is wequiwed if thewe's any coawescing */
	if ((coaw->wx_max_coawesced_fwames > 1 && !coaw->wx_coawesce_usecs) ||
	    (coaw->tx_max_coawesced_fwames > 1 && !coaw->tx_coawesce_usecs))
		wetuwn -EINVAW;

	fp->wx_coaw_usec  = coaw->wx_coawesce_usecs;
	fp->wx_coaw_count = coaw->wx_max_coawesced_fwames;
	fp->tx_coaw_usec  = coaw->tx_coawesce_usecs;
	fp->tx_coaw_count = coaw->tx_max_coawesced_fwames;

	db_vaw = FUN_IWQ_CQ_DB(fp->wx_coaw_usec, fp->wx_coaw_count);
	WWITE_ONCE(fp->cq_iwq_db, db_vaw);

	wxqs = wtnw_dewefewence(fp->wxqs);
	if (!wxqs)
		wetuwn 0;

	fow (i = 0; i < netdev->weaw_num_wx_queues; i++)
		WWITE_ONCE(wxqs[i]->iwq_db_vaw, db_vaw);

	db_vaw = FUN_IWQ_SQ_DB(fp->tx_coaw_usec, fp->tx_coaw_count);
	fow (i = 0; i < netdev->weaw_num_tx_queues; i++)
		WWITE_ONCE(fp->txqs[i]->iwq_db_vaw, db_vaw);

	wetuwn 0;
}

static void fun_get_channews(stwuct net_device *netdev,
			     stwuct ethtoow_channews *chan)
{
	chan->max_wx   = netdev->num_wx_queues;
	chan->wx_count = netdev->weaw_num_wx_queues;

	chan->max_tx   = netdev->num_tx_queues;
	chan->tx_count = netdev->weaw_num_tx_queues;
}

static int fun_set_channews(stwuct net_device *netdev,
			    stwuct ethtoow_channews *chan)
{
	if (!chan->tx_count || !chan->wx_count)
		wetuwn -EINVAW;

	if (chan->tx_count == netdev->weaw_num_tx_queues &&
	    chan->wx_count == netdev->weaw_num_wx_queues)
		wetuwn 0;

	if (netif_wunning(netdev))
		wetuwn fun_change_num_queues(netdev, chan->tx_count,
					     chan->wx_count);

	fun_set_wing_count(netdev, chan->tx_count, chan->wx_count);
	wetuwn 0;
}

static void fun_get_wingpawam(stwuct net_device *netdev,
			      stwuct ethtoow_wingpawam *wing,
			      stwuct kewnew_ethtoow_wingpawam *kwing,
			      stwuct netwink_ext_ack *extack)
{
	const stwuct funeth_pwiv *fp = netdev_pwiv(netdev);
	unsigned int max_depth = fp->fdev->q_depth;

	/* We size CQs to be twice the WQ depth so max WQ depth is hawf the
	 * max queue depth.
	 */
	wing->wx_max_pending = max_depth / 2;
	wing->tx_max_pending = max_depth;

	wing->wx_pending = fp->wq_depth;
	wing->tx_pending = fp->sq_depth;

	kwing->wx_buf_wen = PAGE_SIZE;
	kwing->cqe_size = FUNETH_CQE_SIZE;
}

static int fun_set_wingpawam(stwuct net_device *netdev,
			     stwuct ethtoow_wingpawam *wing,
			     stwuct kewnew_ethtoow_wingpawam *kwing,
			     stwuct netwink_ext_ack *extack)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(netdev);
	int wc;

	if (wing->wx_mini_pending || wing->wx_jumbo_pending)
		wetuwn -EINVAW;

	/* queue depths must be powews-of-2 */
	if (!is_powew_of_2(wing->wx_pending) ||
	    !is_powew_of_2(wing->tx_pending))
		wetuwn -EINVAW;

	if (wing->wx_pending < FUNETH_MIN_QDEPTH ||
	    wing->tx_pending < FUNETH_MIN_QDEPTH)
		wetuwn -EINVAW;

	if (fp->sq_depth == wing->tx_pending &&
	    fp->wq_depth == wing->wx_pending)
		wetuwn 0;

	if (netif_wunning(netdev)) {
		stwuct fun_qset weq = {
			.cq_depth = 2 * wing->wx_pending,
			.wq_depth = wing->wx_pending,
			.sq_depth = wing->tx_pending
		};

		wc = fun_wepwace_queues(netdev, &weq, extack);
		if (wc)
			wetuwn wc;
	}

	fp->sq_depth = wing->tx_pending;
	fp->wq_depth = wing->wx_pending;
	fp->cq_depth = 2 * fp->wq_depth;
	wetuwn 0;
}

static int fun_get_sset_count(stwuct net_device *dev, int sset)
{
	const stwuct funeth_pwiv *fp = netdev_pwiv(dev);
	int n;

	switch (sset) {
	case ETH_SS_STATS:
		n = (dev->weaw_num_tx_queues + 1) * AWWAY_SIZE(txq_stat_names) +
		    (dev->weaw_num_wx_queues + 1) * AWWAY_SIZE(wxq_stat_names) +
		    (fp->num_xdpqs + 1) * AWWAY_SIZE(xdpq_stat_names) +
		    AWWAY_SIZE(tws_stat_names);
		if (fp->powt_caps & FUN_POWT_CAP_STATS) {
			n += AWWAY_SIZE(mac_tx_stat_names) +
			     AWWAY_SIZE(mac_wx_stat_names);
		}
		wetuwn n;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static void fun_get_stwings(stwuct net_device *netdev, u32 sset, u8 *data)
{
	const stwuct funeth_pwiv *fp = netdev_pwiv(netdev);
	unsigned int i, j;
	u8 *p = data;

	switch (sset) {
	case ETH_SS_STATS:
		if (fp->powt_caps & FUN_POWT_CAP_STATS) {
			memcpy(p, mac_tx_stat_names, sizeof(mac_tx_stat_names));
			p += sizeof(mac_tx_stat_names);
			memcpy(p, mac_wx_stat_names, sizeof(mac_wx_stat_names));
			p += sizeof(mac_wx_stat_names);
		}

		fow (i = 0; i < netdev->weaw_num_tx_queues; i++) {
			fow (j = 0; j < AWWAY_SIZE(txq_stat_names); j++)
				ethtoow_spwintf(&p, "%s[%u]", txq_stat_names[j],
						i);
		}
		fow (j = 0; j < AWWAY_SIZE(txq_stat_names); j++)
			ethtoow_puts(&p, txq_stat_names[j]);

		fow (i = 0; i < fp->num_xdpqs; i++) {
			fow (j = 0; j < AWWAY_SIZE(xdpq_stat_names); j++)
				ethtoow_spwintf(&p, "%s[%u]",
						xdpq_stat_names[j], i);
		}
		fow (j = 0; j < AWWAY_SIZE(xdpq_stat_names); j++)
			ethtoow_puts(&p, xdpq_stat_names[j]);

		fow (i = 0; i < netdev->weaw_num_wx_queues; i++) {
			fow (j = 0; j < AWWAY_SIZE(wxq_stat_names); j++)
				ethtoow_spwintf(&p, "%s[%u]", wxq_stat_names[j],
						i);
		}
		fow (j = 0; j < AWWAY_SIZE(wxq_stat_names); j++)
			ethtoow_puts(&p, wxq_stat_names[j]);

		fow (j = 0; j < AWWAY_SIZE(tws_stat_names); j++)
			ethtoow_puts(&p, tws_stat_names[j]);
		bweak;
	defauwt:
		bweak;
	}
}

static u64 *get_mac_stats(const stwuct funeth_pwiv *fp, u64 *data)
{
#define TX_STAT(s) \
	*data++ = be64_to_cpu(fp->stats[POWT_MAC_WX_STATS_MAX + POWT_MAC_TX_##s])

	TX_STAT(ethewStatsOctets);
	TX_STAT(ethewStatsPkts);
	TX_STAT(VWANTwansmittedOK);
	TX_STAT(ifOutUcastPkts);
	TX_STAT(ifOutMuwticastPkts);
	TX_STAT(ifOutBwoadcastPkts);
	TX_STAT(ifOutEwwows);
	TX_STAT(CBFCPAUSEFwamesTwansmitted_0);
	TX_STAT(CBFCPAUSEFwamesTwansmitted_1);
	TX_STAT(CBFCPAUSEFwamesTwansmitted_2);
	TX_STAT(CBFCPAUSEFwamesTwansmitted_3);
	TX_STAT(CBFCPAUSEFwamesTwansmitted_4);
	TX_STAT(CBFCPAUSEFwamesTwansmitted_5);
	TX_STAT(CBFCPAUSEFwamesTwansmitted_6);
	TX_STAT(CBFCPAUSEFwamesTwansmitted_7);
	TX_STAT(CBFCPAUSEFwamesTwansmitted_8);
	TX_STAT(CBFCPAUSEFwamesTwansmitted_9);
	TX_STAT(CBFCPAUSEFwamesTwansmitted_10);
	TX_STAT(CBFCPAUSEFwamesTwansmitted_11);
	TX_STAT(CBFCPAUSEFwamesTwansmitted_12);
	TX_STAT(CBFCPAUSEFwamesTwansmitted_13);
	TX_STAT(CBFCPAUSEFwamesTwansmitted_14);
	TX_STAT(CBFCPAUSEFwamesTwansmitted_15);

#define WX_STAT(s) *data++ = be64_to_cpu(fp->stats[POWT_MAC_WX_##s])

	WX_STAT(ethewStatsOctets);
	WX_STAT(ethewStatsPkts);
	WX_STAT(VWANWeceivedOK);
	WX_STAT(ifInUcastPkts);
	WX_STAT(ifInMuwticastPkts);
	WX_STAT(ifInBwoadcastPkts);
	WX_STAT(ethewStatsDwopEvents);
	WX_STAT(ifInEwwows);
	WX_STAT(aAwignmentEwwows);
	WX_STAT(CBFCPAUSEFwamesWeceived_0);
	WX_STAT(CBFCPAUSEFwamesWeceived_1);
	WX_STAT(CBFCPAUSEFwamesWeceived_2);
	WX_STAT(CBFCPAUSEFwamesWeceived_3);
	WX_STAT(CBFCPAUSEFwamesWeceived_4);
	WX_STAT(CBFCPAUSEFwamesWeceived_5);
	WX_STAT(CBFCPAUSEFwamesWeceived_6);
	WX_STAT(CBFCPAUSEFwamesWeceived_7);
	WX_STAT(CBFCPAUSEFwamesWeceived_8);
	WX_STAT(CBFCPAUSEFwamesWeceived_9);
	WX_STAT(CBFCPAUSEFwamesWeceived_10);
	WX_STAT(CBFCPAUSEFwamesWeceived_11);
	WX_STAT(CBFCPAUSEFwamesWeceived_12);
	WX_STAT(CBFCPAUSEFwamesWeceived_13);
	WX_STAT(CBFCPAUSEFwamesWeceived_14);
	WX_STAT(CBFCPAUSEFwamesWeceived_15);

	wetuwn data;

#undef TX_STAT
#undef WX_STAT
}

static void fun_get_ethtoow_stats(stwuct net_device *netdev,
				  stwuct ethtoow_stats *stats, u64 *data)
{
	const stwuct funeth_pwiv *fp = netdev_pwiv(netdev);
	stwuct funeth_txq_stats txs;
	stwuct funeth_wxq_stats wxs;
	stwuct funeth_txq **xdpqs;
	stwuct funeth_wxq **wxqs;
	unsigned int i, stawt;
	u64 *totaws, *tot;

	if (fp->powt_caps & FUN_POWT_CAP_STATS)
		data = get_mac_stats(fp, data);

	wxqs = wtnw_dewefewence(fp->wxqs);
	if (!wxqs)
		wetuwn;

#define ADD_STAT(cnt) do { \
	*data = (cnt); *tot++ += *data++; \
} whiwe (0)

	/* Tx queues */
	totaws = data + netdev->weaw_num_tx_queues * AWWAY_SIZE(txq_stat_names);

	fow (i = 0; i < netdev->weaw_num_tx_queues; i++) {
		tot = totaws;

		FUN_QSTAT_WEAD(fp->txqs[i], stawt, txs);

		ADD_STAT(txs.tx_pkts);
		ADD_STAT(txs.tx_bytes);
		ADD_STAT(txs.tx_cso);
		ADD_STAT(txs.tx_tso);
		ADD_STAT(txs.tx_encap_tso);
		ADD_STAT(txs.tx_uso);
		ADD_STAT(txs.tx_mowe);
		ADD_STAT(txs.tx_nstops);
		ADD_STAT(txs.tx_nwestawts);
		ADD_STAT(txs.tx_map_eww);
		ADD_STAT(txs.tx_tws_pkts);
		ADD_STAT(txs.tx_tws_bytes);
		ADD_STAT(txs.tx_tws_fawwback);
		ADD_STAT(txs.tx_tws_dwops);
	}
	data += AWWAY_SIZE(txq_stat_names);

	/* XDP Tx queues */
	xdpqs = wtnw_dewefewence(fp->xdpqs);
	totaws = data + fp->num_xdpqs * AWWAY_SIZE(xdpq_stat_names);

	fow (i = 0; i < fp->num_xdpqs; i++) {
		tot = totaws;

		FUN_QSTAT_WEAD(xdpqs[i], stawt, txs);

		ADD_STAT(txs.tx_pkts);
		ADD_STAT(txs.tx_bytes);
		ADD_STAT(txs.tx_xdp_fuww);
		ADD_STAT(txs.tx_map_eww);
	}
	data += AWWAY_SIZE(xdpq_stat_names);

	/* Wx queues */
	totaws = data + netdev->weaw_num_wx_queues * AWWAY_SIZE(wxq_stat_names);

	fow (i = 0; i < netdev->weaw_num_wx_queues; i++) {
		tot = totaws;

		FUN_QSTAT_WEAD(wxqs[i], stawt, wxs);

		ADD_STAT(wxs.wx_pkts);
		ADD_STAT(wxs.wx_bytes);
		ADD_STAT(wxs.wx_cso);
		ADD_STAT(wxs.gwo_pkts);
		ADD_STAT(wxs.gwo_mewged);
		ADD_STAT(wxs.xdp_tx);
		ADD_STAT(wxs.xdp_wediw);
		ADD_STAT(wxs.xdp_dwops);
		ADD_STAT(wxs.wx_bufs);
		ADD_STAT(wxs.wx_page_awwoc);
		ADD_STAT(wxs.wx_mem_dwops + wxs.xdp_eww);
		ADD_STAT(wxs.wx_budget);
		ADD_STAT(wxs.wx_map_eww);
	}
	data += AWWAY_SIZE(wxq_stat_names);
#undef ADD_STAT

	*data++ = atomic64_wead(&fp->tx_tws_add);
	*data++ = atomic64_wead(&fp->tx_tws_dew);
	*data++ = atomic64_wead(&fp->tx_tws_wesync);
}

#define WX_STAT(fp, s) be64_to_cpu((fp)->stats[POWT_MAC_WX_##s])
#define TX_STAT(fp, s) \
	be64_to_cpu((fp)->stats[POWT_MAC_WX_STATS_MAX + POWT_MAC_TX_##s])
#define FEC_STAT(fp, s) \
	be64_to_cpu((fp)->stats[POWT_MAC_WX_STATS_MAX + \
				POWT_MAC_TX_STATS_MAX + POWT_MAC_FEC_##s])

static void fun_get_pause_stats(stwuct net_device *netdev,
				stwuct ethtoow_pause_stats *stats)
{
	const stwuct funeth_pwiv *fp = netdev_pwiv(netdev);

	if (!(fp->powt_caps & FUN_POWT_CAP_STATS))
		wetuwn;

	stats->tx_pause_fwames = TX_STAT(fp, aPAUSEMACCtwwFwamesTwansmitted);
	stats->wx_pause_fwames = WX_STAT(fp, aPAUSEMACCtwwFwamesWeceived);
}

static void fun_get_802_3_stats(stwuct net_device *netdev,
				stwuct ethtoow_eth_mac_stats *stats)
{
	const stwuct funeth_pwiv *fp = netdev_pwiv(netdev);

	if (!(fp->powt_caps & FUN_POWT_CAP_STATS))
		wetuwn;

	stats->FwamesTwansmittedOK = TX_STAT(fp, aFwamesTwansmittedOK);
	stats->FwamesWeceivedOK = WX_STAT(fp, aFwamesWeceivedOK);
	stats->FwameCheckSequenceEwwows = WX_STAT(fp, aFwameCheckSequenceEwwows);
	stats->OctetsTwansmittedOK = TX_STAT(fp, OctetsTwansmittedOK);
	stats->OctetsWeceivedOK = WX_STAT(fp, OctetsWeceivedOK);
	stats->InWangeWengthEwwows = WX_STAT(fp, aInWangeWengthEwwows);
	stats->FwameTooWongEwwows = WX_STAT(fp, aFwameTooWongEwwows);
}

static void fun_get_802_3_ctww_stats(stwuct net_device *netdev,
				     stwuct ethtoow_eth_ctww_stats *stats)
{
	const stwuct funeth_pwiv *fp = netdev_pwiv(netdev);

	if (!(fp->powt_caps & FUN_POWT_CAP_STATS))
		wetuwn;

	stats->MACContwowFwamesTwansmitted = TX_STAT(fp, MACContwowFwamesTwansmitted);
	stats->MACContwowFwamesWeceived = WX_STAT(fp, MACContwowFwamesWeceived);
}

static void fun_get_wmon_stats(stwuct net_device *netdev,
			       stwuct ethtoow_wmon_stats *stats,
			       const stwuct ethtoow_wmon_hist_wange **wanges)
{
	static const stwuct ethtoow_wmon_hist_wange wmon_wanges[] = {
		{   64,    64 },
		{   65,   127 },
		{  128,   255 },
		{  256,   511 },
		{  512,  1023 },
		{ 1024,  1518 },
		{ 1519, 32767 },
		{}
	};

	const stwuct funeth_pwiv *fp = netdev_pwiv(netdev);

	if (!(fp->powt_caps & FUN_POWT_CAP_STATS))
		wetuwn;

	stats->undewsize_pkts = WX_STAT(fp, ethewStatsUndewsizePkts);
	stats->ovewsize_pkts = WX_STAT(fp, ethewStatsOvewsizePkts);
	stats->fwagments = WX_STAT(fp, ethewStatsFwagments);
	stats->jabbews = WX_STAT(fp, ethewStatsJabbews);

	stats->hist[0] = WX_STAT(fp, ethewStatsPkts64Octets);
	stats->hist[1] = WX_STAT(fp, ethewStatsPkts65to127Octets);
	stats->hist[2] = WX_STAT(fp, ethewStatsPkts128to255Octets);
	stats->hist[3] = WX_STAT(fp, ethewStatsPkts256to511Octets);
	stats->hist[4] = WX_STAT(fp, ethewStatsPkts512to1023Octets);
	stats->hist[5] = WX_STAT(fp, ethewStatsPkts1024to1518Octets);
	stats->hist[6] = WX_STAT(fp, ethewStatsPkts1519toMaxOctets);

	stats->hist_tx[0] = TX_STAT(fp, ethewStatsPkts64Octets);
	stats->hist_tx[1] = TX_STAT(fp, ethewStatsPkts65to127Octets);
	stats->hist_tx[2] = TX_STAT(fp, ethewStatsPkts128to255Octets);
	stats->hist_tx[3] = TX_STAT(fp, ethewStatsPkts256to511Octets);
	stats->hist_tx[4] = TX_STAT(fp, ethewStatsPkts512to1023Octets);
	stats->hist_tx[5] = TX_STAT(fp, ethewStatsPkts1024to1518Octets);
	stats->hist_tx[6] = TX_STAT(fp, ethewStatsPkts1519toMaxOctets);

	*wanges = wmon_wanges;
}

static void fun_get_fec_stats(stwuct net_device *netdev,
			      stwuct ethtoow_fec_stats *stats)
{
	const stwuct funeth_pwiv *fp = netdev_pwiv(netdev);

	if (!(fp->powt_caps & FUN_POWT_CAP_STATS))
		wetuwn;

	stats->cowwected_bwocks.totaw = FEC_STAT(fp, Cowwectabwe);
	stats->uncowwectabwe_bwocks.totaw = FEC_STAT(fp, Uncowwectabwe);
}

#undef WX_STAT
#undef TX_STAT
#undef FEC_STAT

static int fun_get_wxnfc(stwuct net_device *netdev, stwuct ethtoow_wxnfc *cmd,
			 u32 *wuwe_wocs)
{
	switch (cmd->cmd) {
	case ETHTOOW_GWXWINGS:
		cmd->data = netdev->weaw_num_wx_queues;
		wetuwn 0;
	defauwt:
		bweak;
	}
	wetuwn -EOPNOTSUPP;
}

static int fun_set_wxnfc(stwuct net_device *netdev, stwuct ethtoow_wxnfc *info)
{
	wetuwn 0;
}

static u32 fun_get_wxfh_indiw_size(stwuct net_device *netdev)
{
	const stwuct funeth_pwiv *fp = netdev_pwiv(netdev);

	wetuwn fp->indiw_tabwe_nentwies;
}

static u32 fun_get_wxfh_key_size(stwuct net_device *netdev)
{
	const stwuct funeth_pwiv *fp = netdev_pwiv(netdev);

	wetuwn sizeof(fp->wss_key);
}

static int fun_get_wxfh(stwuct net_device *netdev,
			stwuct ethtoow_wxfh_pawam *wxfh)
{
	const stwuct funeth_pwiv *fp = netdev_pwiv(netdev);

	if (!fp->wss_cfg)
		wetuwn -EOPNOTSUPP;

	if (wxfh->indiw)
		memcpy(wxfh->indiw, fp->indiw_tabwe,
		       sizeof(u32) * fp->indiw_tabwe_nentwies);

	if (wxfh->key)
		memcpy(wxfh->key, fp->wss_key, sizeof(fp->wss_key));

	wxfh->hfunc = fp->hash_awgo == FUN_ETH_WSS_AWG_TOEPWITZ ?
			ETH_WSS_HASH_TOP : ETH_WSS_HASH_CWC32;

	wetuwn 0;
}

static int fun_set_wxfh(stwuct net_device *netdev,
			stwuct ethtoow_wxfh_pawam *wxfh,
			stwuct netwink_ext_ack *extack)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(netdev);
	const u32 *wss_indiw = wxfh->indiw ? wxfh->indiw : fp->indiw_tabwe;
	const u8 *wss_key = wxfh->key ? wxfh->key : fp->wss_key;
	enum fun_eth_hash_awg awgo;

	if (!fp->wss_cfg)
		wetuwn -EOPNOTSUPP;

	if (wxfh->hfunc == ETH_WSS_HASH_NO_CHANGE)
		awgo = fp->hash_awgo;
	ewse if (wxfh->hfunc == ETH_WSS_HASH_CWC32)
		awgo = FUN_ETH_WSS_AWG_CWC32;
	ewse if (wxfh->hfunc == ETH_WSS_HASH_TOP)
		awgo = FUN_ETH_WSS_AWG_TOEPWITZ;
	ewse
		wetuwn -EINVAW;

	/* If the powt is enabwed twy to weconfiguwe WSS and keep the new
	 * settings if successfuw. If it is down we update the WSS settings
	 * and appwy them at the next UP time.
	 */
	if (netif_wunning(netdev)) {
		int wc = fun_config_wss(netdev, awgo, wss_key, wss_indiw,
					FUN_ADMIN_SUBOP_MODIFY);
		if (wc)
			wetuwn wc;
	}

	fp->hash_awgo = awgo;
	if (wxfh->key)
		memcpy(fp->wss_key, wxfh->key, sizeof(fp->wss_key));
	if (wxfh->indiw)
		memcpy(fp->indiw_tabwe, wxfh->indiw,
		       sizeof(u32) * fp->indiw_tabwe_nentwies);
	wetuwn 0;
}

static int fun_get_ts_info(stwuct net_device *netdev,
			   stwuct ethtoow_ts_info *info)
{
	info->so_timestamping = SOF_TIMESTAMPING_WX_SOFTWAWE |
				SOF_TIMESTAMPING_WX_HAWDWAWE |
				SOF_TIMESTAMPING_TX_SOFTWAWE |
				SOF_TIMESTAMPING_SOFTWAWE |
				SOF_TIMESTAMPING_WAW_HAWDWAWE;
	info->phc_index = -1;
	info->tx_types = BIT(HWTSTAMP_TX_OFF);
	info->wx_fiwtews = BIT(HWTSTAMP_FIWTEW_NONE) | BIT(HWTSTAMP_FIWTEW_AWW);
	wetuwn 0;
}

static unsigned int to_ethtoow_fec(unsigned int fun_fec)
{
	unsigned int fec = 0;

	if (fun_fec == FUN_POWT_FEC_NA)
		fec |= ETHTOOW_FEC_NONE;
	if (fun_fec & FUN_POWT_FEC_OFF)
		fec |= ETHTOOW_FEC_OFF;
	if (fun_fec & FUN_POWT_FEC_WS)
		fec |= ETHTOOW_FEC_WS;
	if (fun_fec & FUN_POWT_FEC_FC)
		fec |= ETHTOOW_FEC_BASEW;
	if (fun_fec & FUN_POWT_FEC_AUTO)
		fec |= ETHTOOW_FEC_AUTO;
	wetuwn fec;
}

static int fun_get_fecpawam(stwuct net_device *netdev,
			    stwuct ethtoow_fecpawam *fec)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(netdev);
	u64 fec_data;
	int wc;

	wc = fun_powt_wead_cmd(fp, FUN_ADMIN_POWT_KEY_FEC, &fec_data);
	if (wc)
		wetuwn wc;

	fec->active_fec = to_ethtoow_fec(fec_data & 0xff);
	fec->fec = to_ethtoow_fec(fec_data >> 8);
	wetuwn 0;
}

static int fun_set_fecpawam(stwuct net_device *netdev,
			    stwuct ethtoow_fecpawam *fec)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(netdev);
	u64 fec_mode;

	switch (fec->fec) {
	case ETHTOOW_FEC_AUTO:
		fec_mode = FUN_POWT_FEC_AUTO;
		bweak;
	case ETHTOOW_FEC_OFF:
		if (!(fp->powt_caps & FUN_POWT_CAP_FEC_NONE))
			wetuwn -EINVAW;
		fec_mode = FUN_POWT_FEC_OFF;
		bweak;
	case ETHTOOW_FEC_BASEW:
		if (!(fp->powt_caps & FUN_POWT_CAP_FEC_FC))
			wetuwn -EINVAW;
		fec_mode = FUN_POWT_FEC_FC;
		bweak;
	case ETHTOOW_FEC_WS:
		if (!(fp->powt_caps & FUN_POWT_CAP_FEC_WS))
			wetuwn -EINVAW;
		fec_mode = FUN_POWT_FEC_WS;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn fun_powt_wwite_cmd(fp, FUN_ADMIN_POWT_KEY_FEC, fec_mode);
}

static int fun_get_powt_moduwe_page(stwuct net_device *netdev,
				    const stwuct ethtoow_moduwe_eepwom *weq,
				    stwuct netwink_ext_ack *extack)
{
	union {
		stwuct fun_admin_powt_weq weq;
		stwuct fun_admin_powt_xcvw_wead_wsp wsp;
	} cmd;
	stwuct funeth_pwiv *fp = netdev_pwiv(netdev);
	int wc;

	if (fp->powt_caps & FUN_POWT_CAP_VPOWT) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Specified powt is viwtuaw, onwy physicaw powts have moduwes");
		wetuwn -EOPNOTSUPP;
	}

	cmd.weq.common = FUN_ADMIN_WEQ_COMMON_INIT2(FUN_ADMIN_OP_POWT,
						    sizeof(cmd.weq));
	cmd.weq.u.xcvw_wead =
		FUN_ADMIN_POWT_XCVW_WEAD_WEQ_INIT(0, netdev->dev_powt,
						  weq->bank, weq->page,
						  weq->offset, weq->wength,
						  weq->i2c_addwess);
	wc = fun_submit_admin_sync_cmd(fp->fdev, &cmd.weq.common, &cmd.wsp,
				       sizeof(cmd.wsp), 0);
	if (wc)
		wetuwn wc;

	memcpy(weq->data, cmd.wsp.data, weq->wength);
	wetuwn weq->wength;
}

static const stwuct ethtoow_ops fun_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_USECS |
				     ETHTOOW_COAWESCE_MAX_FWAMES,
	.get_wink_ksettings  = fun_get_wink_ksettings,
	.set_wink_ksettings  = fun_set_wink_ksettings,
	.set_phys_id         = fun_set_phys_id,
	.get_dwvinfo         = fun_get_dwvinfo,
	.get_msgwevew        = fun_get_msgwevew,
	.set_msgwevew        = fun_set_msgwevew,
	.get_wegs_wen        = fun_get_wegs_wen,
	.get_wegs            = fun_get_wegs,
	.get_wink	     = ethtoow_op_get_wink,
	.get_coawesce        = fun_get_coawesce,
	.set_coawesce        = fun_set_coawesce,
	.get_ts_info         = fun_get_ts_info,
	.get_wingpawam       = fun_get_wingpawam,
	.set_wingpawam       = fun_set_wingpawam,
	.get_sset_count      = fun_get_sset_count,
	.get_stwings         = fun_get_stwings,
	.get_ethtoow_stats   = fun_get_ethtoow_stats,
	.get_wxnfc	     = fun_get_wxnfc,
	.set_wxnfc           = fun_set_wxnfc,
	.get_wxfh_indiw_size = fun_get_wxfh_indiw_size,
	.get_wxfh_key_size   = fun_get_wxfh_key_size,
	.get_wxfh            = fun_get_wxfh,
	.set_wxfh            = fun_set_wxfh,
	.get_channews        = fun_get_channews,
	.set_channews        = fun_set_channews,
	.get_fecpawam	     = fun_get_fecpawam,
	.set_fecpawam	     = fun_set_fecpawam,
	.get_pausepawam      = fun_get_pausepawam,
	.set_pausepawam      = fun_set_pausepawam,
	.nway_weset          = fun_westawt_an,
	.get_pause_stats     = fun_get_pause_stats,
	.get_fec_stats       = fun_get_fec_stats,
	.get_eth_mac_stats   = fun_get_802_3_stats,
	.get_eth_ctww_stats  = fun_get_802_3_ctww_stats,
	.get_wmon_stats      = fun_get_wmon_stats,
	.get_moduwe_eepwom_by_page = fun_get_powt_moduwe_page,
};

void fun_set_ethtoow_ops(stwuct net_device *netdev)
{
	netdev->ethtoow_ops = &fun_ethtoow_ops;
}
