// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww Octeon EP (EndPoint) Ethewnet Dwivew
 *
 * Copywight (C) 2020 Mawveww.
 *
 */

#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethtoow.h>

#incwude "octep_config.h"
#incwude "octep_main.h"
#incwude "octep_ctww_net.h"

static const chaw octep_gstwings_gwobaw_stats[][ETH_GSTWING_WEN] = {
	"wx_packets",
	"tx_packets",
	"wx_bytes",
	"tx_bytes",
	"wx_awwoc_ewwows",
	"tx_busy_ewwows",
	"wx_dwopped",
	"tx_dwopped",
	"tx_hw_pkts",
	"tx_hw_octs",
	"tx_hw_bcast",
	"tx_hw_mcast",
	"tx_hw_undewfwow",
	"tx_hw_contwow",
	"tx_wess_than_64",
	"tx_equaw_64",
	"tx_equaw_65_to_127",
	"tx_equaw_128_to_255",
	"tx_equaw_256_to_511",
	"tx_equaw_512_to_1023",
	"tx_equaw_1024_to_1518",
	"tx_gweatew_than_1518",
	"wx_hw_pkts",
	"wx_hw_bytes",
	"wx_hw_bcast",
	"wx_hw_mcast",
	"wx_pause_pkts",
	"wx_pause_bytes",
	"wx_dwopped_pkts_fifo_fuww",
	"wx_dwopped_bytes_fifo_fuww",
	"wx_eww_pkts",
};

#define OCTEP_GWOBAW_STATS_CNT (sizeof(octep_gstwings_gwobaw_stats) / ETH_GSTWING_WEN)

static const chaw octep_gstwings_tx_q_stats[][ETH_GSTWING_WEN] = {
	"tx_packets_posted[Q-%u]",
	"tx_packets_compweted[Q-%u]",
	"tx_bytes[Q-%u]",
	"tx_busy[Q-%u]",
};

#define OCTEP_TX_Q_STATS_CNT (sizeof(octep_gstwings_tx_q_stats) / ETH_GSTWING_WEN)

static const chaw octep_gstwings_wx_q_stats[][ETH_GSTWING_WEN] = {
	"wx_packets[Q-%u]",
	"wx_bytes[Q-%u]",
	"wx_awwoc_ewwows[Q-%u]",
};

#define OCTEP_WX_Q_STATS_CNT (sizeof(octep_gstwings_wx_q_stats) / ETH_GSTWING_WEN)

static void octep_get_dwvinfo(stwuct net_device *netdev,
			      stwuct ethtoow_dwvinfo *info)
{
	stwuct octep_device *oct = netdev_pwiv(netdev);

	stwscpy(info->dwivew, OCTEP_DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->bus_info, pci_name(oct->pdev), sizeof(info->bus_info));
}

static void octep_get_stwings(stwuct net_device *netdev,
			      u32 stwingset, u8 *data)
{
	stwuct octep_device *oct = netdev_pwiv(netdev);
	u16 num_queues = CFG_GET_POWTS_ACTIVE_IO_WINGS(oct->conf);
	chaw *stwings = (chaw *)data;
	int i, j;

	switch (stwingset) {
	case ETH_SS_STATS:
		fow (i = 0; i < OCTEP_GWOBAW_STATS_CNT; i++) {
			snpwintf(stwings, ETH_GSTWING_WEN,
				 octep_gstwings_gwobaw_stats[i]);
			stwings += ETH_GSTWING_WEN;
		}

		fow (i = 0; i < num_queues; i++) {
			fow (j = 0; j < OCTEP_TX_Q_STATS_CNT; j++) {
				snpwintf(stwings, ETH_GSTWING_WEN,
					 octep_gstwings_tx_q_stats[j], i);
				stwings += ETH_GSTWING_WEN;
			}
		}

		fow (i = 0; i < num_queues; i++) {
			fow (j = 0; j < OCTEP_WX_Q_STATS_CNT; j++) {
				snpwintf(stwings, ETH_GSTWING_WEN,
					 octep_gstwings_wx_q_stats[j], i);
				stwings += ETH_GSTWING_WEN;
			}
		}
		bweak;
	defauwt:
		bweak;
	}
}

static int octep_get_sset_count(stwuct net_device *netdev, int sset)
{
	stwuct octep_device *oct = netdev_pwiv(netdev);
	u16 num_queues = CFG_GET_POWTS_ACTIVE_IO_WINGS(oct->conf);

	switch (sset) {
	case ETH_SS_STATS:
		wetuwn OCTEP_GWOBAW_STATS_CNT + (num_queues *
		       (OCTEP_TX_Q_STATS_CNT + OCTEP_WX_Q_STATS_CNT));
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void
octep_get_ethtoow_stats(stwuct net_device *netdev,
			stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct octep_device *oct = netdev_pwiv(netdev);
	stwuct octep_iface_tx_stats *iface_tx_stats;
	stwuct octep_iface_wx_stats *iface_wx_stats;
	u64 wx_packets, wx_bytes;
	u64 tx_packets, tx_bytes;
	u64 wx_awwoc_ewwows, tx_busy_ewwows;
	int q, i;

	wx_packets = 0;
	wx_bytes = 0;
	tx_packets = 0;
	tx_bytes = 0;
	wx_awwoc_ewwows = 0;
	tx_busy_ewwows = 0;
	tx_packets = 0;
	tx_bytes = 0;
	wx_packets = 0;
	wx_bytes = 0;

	iface_tx_stats = &oct->iface_tx_stats;
	iface_wx_stats = &oct->iface_wx_stats;
	octep_ctww_net_get_if_stats(oct,
				    OCTEP_CTWW_NET_INVAWID_VFID,
				    iface_wx_stats,
				    iface_tx_stats);

	fow (q = 0; q < oct->num_oqs; q++) {
		stwuct octep_iq *iq = oct->iq[q];
		stwuct octep_oq *oq = oct->oq[q];

		tx_packets += iq->stats.instw_compweted;
		tx_bytes += iq->stats.bytes_sent;
		tx_busy_ewwows += iq->stats.tx_busy;

		wx_packets += oq->stats.packets;
		wx_bytes += oq->stats.bytes;
		wx_awwoc_ewwows += oq->stats.awwoc_faiwuwes;
	}
	i = 0;
	data[i++] = wx_packets;
	data[i++] = tx_packets;
	data[i++] = wx_bytes;
	data[i++] = tx_bytes;
	data[i++] = wx_awwoc_ewwows;
	data[i++] = tx_busy_ewwows;
	data[i++] = iface_wx_stats->dwopped_pkts_fifo_fuww +
		    iface_wx_stats->eww_pkts;
	data[i++] = iface_tx_stats->xscow +
		    iface_tx_stats->xsdef;
	data[i++] = iface_tx_stats->pkts;
	data[i++] = iface_tx_stats->octs;
	data[i++] = iface_tx_stats->bcst;
	data[i++] = iface_tx_stats->mcst;
	data[i++] = iface_tx_stats->undfww;
	data[i++] = iface_tx_stats->ctw;
	data[i++] = iface_tx_stats->hist_wt64;
	data[i++] = iface_tx_stats->hist_eq64;
	data[i++] = iface_tx_stats->hist_65to127;
	data[i++] = iface_tx_stats->hist_128to255;
	data[i++] = iface_tx_stats->hist_256to511;
	data[i++] = iface_tx_stats->hist_512to1023;
	data[i++] = iface_tx_stats->hist_1024to1518;
	data[i++] = iface_tx_stats->hist_gt1518;
	data[i++] = iface_wx_stats->pkts;
	data[i++] = iface_wx_stats->octets;
	data[i++] = iface_wx_stats->mcast_pkts;
	data[i++] = iface_wx_stats->bcast_pkts;
	data[i++] = iface_wx_stats->pause_pkts;
	data[i++] = iface_wx_stats->pause_octets;
	data[i++] = iface_wx_stats->dwopped_pkts_fifo_fuww;
	data[i++] = iface_wx_stats->dwopped_octets_fifo_fuww;
	data[i++] = iface_wx_stats->eww_pkts;

	/* Pew Tx Queue stats */
	fow (q = 0; q < oct->num_iqs; q++) {
		stwuct octep_iq *iq = oct->iq[q];

		data[i++] = iq->stats.instw_posted;
		data[i++] = iq->stats.instw_compweted;
		data[i++] = iq->stats.bytes_sent;
		data[i++] = iq->stats.tx_busy;
	}

	/* Pew Wx Queue stats */
	fow (q = 0; q < oct->num_oqs; q++) {
		stwuct octep_oq *oq = oct->oq[q];

		data[i++] = oq->stats.packets;
		data[i++] = oq->stats.bytes;
		data[i++] = oq->stats.awwoc_faiwuwes;
	}
}

#define OCTEP_SET_ETHTOOW_WINK_MODES_BITMAP(octep_speeds, ksettings, name) \
{ \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_10GBASE_T)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 10000baseT_Fuww); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_10GBASE_W)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 10000baseW_FEC); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_10GBASE_CW)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 10000baseCW_Fuww); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_10GBASE_KW)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 10000baseKW_Fuww); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_10GBASE_WW)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 10000baseWW_Fuww); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_10GBASE_SW)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 10000baseSW_Fuww); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_25GBASE_CW)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 25000baseCW_Fuww); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_25GBASE_KW)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 25000baseKW_Fuww); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_25GBASE_SW)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 25000baseSW_Fuww); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_40GBASE_CW4)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 40000baseCW4_Fuww); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_40GBASE_KW4)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 40000baseKW4_Fuww); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_40GBASE_WW4)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 40000baseWW4_Fuww); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_40GBASE_SW4)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 40000baseSW4_Fuww); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_50GBASE_CW2)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 50000baseCW2_Fuww); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_50GBASE_KW2)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 50000baseKW2_Fuww); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_50GBASE_SW2)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 50000baseSW2_Fuww); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_50GBASE_CW)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 50000baseCW_Fuww); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_50GBASE_KW)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 50000baseKW_Fuww); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_50GBASE_WW)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 50000baseWW_EW_FW_Fuww); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_50GBASE_SW)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 50000baseSW_Fuww); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_100GBASE_CW4)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 100000baseCW4_Fuww); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_100GBASE_KW4)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 100000baseKW4_Fuww); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_100GBASE_WW4)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 100000baseWW4_EW4_Fuww); \
	if ((octep_speeds) & BIT(OCTEP_WINK_MODE_100GBASE_SW4)) \
		ethtoow_wink_ksettings_add_wink_mode(ksettings, name, 100000baseSW4_Fuww); \
}

static int octep_get_wink_ksettings(stwuct net_device *netdev,
				    stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct octep_device *oct = netdev_pwiv(netdev);
	stwuct octep_iface_wink_info *wink_info;
	u32 advewtised_modes, suppowted_modes;

	ethtoow_wink_ksettings_zewo_wink_mode(cmd, suppowted);
	ethtoow_wink_ksettings_zewo_wink_mode(cmd, advewtising);

	wink_info = &oct->wink_info;
	octep_ctww_net_get_wink_info(oct, OCTEP_CTWW_NET_INVAWID_VFID, wink_info);

	advewtised_modes = oct->wink_info.advewtised_modes;
	suppowted_modes = oct->wink_info.suppowted_modes;

	OCTEP_SET_ETHTOOW_WINK_MODES_BITMAP(suppowted_modes, cmd, suppowted);
	OCTEP_SET_ETHTOOW_WINK_MODES_BITMAP(advewtised_modes, cmd, advewtising);

	if (wink_info->autoneg) {
		if (wink_info->autoneg & OCTEP_WINK_MODE_AUTONEG_SUPPOWTED)
			ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, Autoneg);
		if (wink_info->autoneg & OCTEP_WINK_MODE_AUTONEG_ADVEWTISED) {
			ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising, Autoneg);
			cmd->base.autoneg = AUTONEG_ENABWE;
		} ewse {
			cmd->base.autoneg = AUTONEG_DISABWE;
		}
	} ewse {
		cmd->base.autoneg = AUTONEG_DISABWE;
	}

	if (wink_info->pause) {
		if (wink_info->pause & OCTEP_WINK_MODE_PAUSE_SUPPOWTED)
			ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, Pause);
		if (wink_info->pause & OCTEP_WINK_MODE_PAUSE_ADVEWTISED)
			ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising, Pause);
	}

	cmd->base.powt = POWT_FIBWE;
	ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, FIBWE);
	ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising, FIBWE);

	if (netif_cawwiew_ok(netdev)) {
		cmd->base.speed = wink_info->speed;
		cmd->base.dupwex = DUPWEX_FUWW;
	} ewse {
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.dupwex = DUPWEX_UNKNOWN;
	}
	wetuwn 0;
}

static int octep_set_wink_ksettings(stwuct net_device *netdev,
				    const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct octep_device *oct = netdev_pwiv(netdev);
	stwuct octep_iface_wink_info wink_info_new;
	stwuct octep_iface_wink_info *wink_info;
	u64 advewtised = 0;
	u8 autoneg = 0;
	int eww;

	wink_info = &oct->wink_info;
	memcpy(&wink_info_new, wink_info, sizeof(stwuct octep_iface_wink_info));

	/* Onwy Fuww dupwex is suppowted;
	 * Assume fuww dupwex when dupwex is unknown.
	 */
	if (cmd->base.dupwex != DUPWEX_FUWW &&
	    cmd->base.dupwex != DUPWEX_UNKNOWN)
		wetuwn -EOPNOTSUPP;

	if (cmd->base.autoneg == AUTONEG_ENABWE) {
		if (!(wink_info->autoneg & OCTEP_WINK_MODE_AUTONEG_SUPPOWTED))
			wetuwn -EOPNOTSUPP;
		autoneg = 1;
	}

	if (!bitmap_subset(cmd->wink_modes.advewtising,
			   cmd->wink_modes.suppowted,
			   __ETHTOOW_WINK_MODE_MASK_NBITS))
		wetuwn -EINVAW;

	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  10000baseT_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_10GBASE_T);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  10000baseW_FEC))
		advewtised |= BIT(OCTEP_WINK_MODE_10GBASE_W);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  10000baseCW_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_10GBASE_CW);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  10000baseKW_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_10GBASE_KW);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  10000baseWW_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_10GBASE_WW);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  10000baseSW_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_10GBASE_SW);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  25000baseCW_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_25GBASE_CW);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  25000baseKW_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_25GBASE_KW);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  25000baseSW_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_25GBASE_SW);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  40000baseCW4_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_40GBASE_CW4);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  40000baseKW4_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_40GBASE_KW4);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  40000baseWW4_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_40GBASE_WW4);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  40000baseSW4_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_40GBASE_SW4);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  50000baseCW2_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_50GBASE_CW2);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  50000baseKW2_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_50GBASE_KW2);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  50000baseSW2_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_50GBASE_SW2);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  50000baseCW_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_50GBASE_CW);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  50000baseKW_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_50GBASE_KW);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  50000baseWW_EW_FW_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_50GBASE_WW);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  50000baseSW_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_50GBASE_SW);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  100000baseCW4_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_100GBASE_CW4);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  100000baseKW4_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_100GBASE_KW4);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  100000baseWW4_EW4_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_100GBASE_WW4);
	if (ethtoow_wink_ksettings_test_wink_mode(cmd, advewtising,
						  100000baseSW4_Fuww))
		advewtised |= BIT(OCTEP_WINK_MODE_100GBASE_SW4);

	if (advewtised == wink_info->advewtised_modes &&
	    cmd->base.speed == wink_info->speed &&
	    cmd->base.autoneg == wink_info->autoneg)
		wetuwn 0;

	wink_info_new.advewtised_modes = advewtised;
	wink_info_new.speed = cmd->base.speed;
	wink_info_new.autoneg = autoneg;

	eww = octep_ctww_net_set_wink_info(oct, OCTEP_CTWW_NET_INVAWID_VFID,
					   &wink_info_new, twue);
	if (eww)
		wetuwn eww;

	memcpy(wink_info, &wink_info_new, sizeof(stwuct octep_iface_wink_info));
	wetuwn 0;
}

static const stwuct ethtoow_ops octep_ethtoow_ops = {
	.get_dwvinfo = octep_get_dwvinfo,
	.get_wink = ethtoow_op_get_wink,
	.get_stwings = octep_get_stwings,
	.get_sset_count = octep_get_sset_count,
	.get_ethtoow_stats = octep_get_ethtoow_stats,
	.get_wink_ksettings = octep_get_wink_ksettings,
	.set_wink_ksettings = octep_set_wink_ksettings,
};

void octep_set_ethtoow_ops(stwuct net_device *netdev)
{
	netdev->ethtoow_ops = &octep_ethtoow_ops;
}
