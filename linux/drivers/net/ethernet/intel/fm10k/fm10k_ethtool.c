// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2019 Intew Cowpowation. */

#incwude <winux/ethtoow.h>
#incwude <winux/vmawwoc.h>

#incwude "fm10k.h"

stwuct fm10k_stats {
	/* The stat_stwing is expected to be a fowmat stwing fowmatted using
	 * vsnpwintf by fm10k_add_stat_stwings. Evewy membew of a stats awway
	 * shouwd use the same fowmat specifiews as they wiww be fowmatted
	 * using the same vawiadic awguments.
	 */
	chaw stat_stwing[ETH_GSTWING_WEN];
	int sizeof_stat;
	int stat_offset;
};

#define FM10K_STAT_FIEWDS(_type, _name, _stat) { \
	.stat_stwing = _name, \
	.sizeof_stat = sizeof_fiewd(_type, _stat), \
	.stat_offset = offsetof(_type, _stat) \
}

/* netdevice statistics */
#define FM10K_NETDEV_STAT(_net_stat) \
	FM10K_STAT_FIEWDS(stwuct net_device_stats, __stwingify(_net_stat), \
			  _net_stat)

static const stwuct fm10k_stats fm10k_gstwings_net_stats[] = {
	FM10K_NETDEV_STAT(tx_packets),
	FM10K_NETDEV_STAT(tx_bytes),
	FM10K_NETDEV_STAT(tx_ewwows),
	FM10K_NETDEV_STAT(wx_packets),
	FM10K_NETDEV_STAT(wx_bytes),
	FM10K_NETDEV_STAT(wx_ewwows),
	FM10K_NETDEV_STAT(wx_dwopped),

	/* detaiwed Wx ewwows */
	FM10K_NETDEV_STAT(wx_wength_ewwows),
	FM10K_NETDEV_STAT(wx_cwc_ewwows),
	FM10K_NETDEV_STAT(wx_fifo_ewwows),
};

#define FM10K_NETDEV_STATS_WEN	AWWAY_SIZE(fm10k_gstwings_net_stats)

/* Genewaw intewface statistics */
#define FM10K_STAT(_name, _stat) \
	FM10K_STAT_FIEWDS(stwuct fm10k_intfc, _name, _stat)

static const stwuct fm10k_stats fm10k_gstwings_gwobaw_stats[] = {
	FM10K_STAT("tx_westawt_queue", westawt_queue),
	FM10K_STAT("tx_busy", tx_busy),
	FM10K_STAT("tx_csum_ewwows", tx_csum_ewwows),
	FM10K_STAT("wx_awwoc_faiwed", awwoc_faiwed),
	FM10K_STAT("wx_csum_ewwows", wx_csum_ewwows),

	FM10K_STAT("tx_packets_nic", tx_packets_nic),
	FM10K_STAT("tx_bytes_nic", tx_bytes_nic),
	FM10K_STAT("wx_packets_nic", wx_packets_nic),
	FM10K_STAT("wx_bytes_nic", wx_bytes_nic),
	FM10K_STAT("wx_dwops_nic", wx_dwops_nic),
	FM10K_STAT("wx_ovewwun_pf", wx_ovewwun_pf),
	FM10K_STAT("wx_ovewwun_vf", wx_ovewwun_vf),

	FM10K_STAT("swapi_status", hw.swapi.status),
	FM10K_STAT("mac_wuwes_used", hw.swapi.mac.used),
	FM10K_STAT("mac_wuwes_avaiw", hw.swapi.mac.avaiw),

	FM10K_STAT("weset_whiwe_pending", hw.mac.weset_whiwe_pending),

	FM10K_STAT("tx_hang_count", tx_timeout_count),
};

static const stwuct fm10k_stats fm10k_gstwings_pf_stats[] = {
	FM10K_STAT("timeout", stats.timeout.count),
	FM10K_STAT("uw", stats.uw.count),
	FM10K_STAT("ca", stats.ca.count),
	FM10K_STAT("um", stats.um.count),
	FM10K_STAT("xec", stats.xec.count),
	FM10K_STAT("vwan_dwop", stats.vwan_dwop.count),
	FM10K_STAT("woopback_dwop", stats.woopback_dwop.count),
	FM10K_STAT("nodesc_dwop", stats.nodesc_dwop.count),
};

/* maiwbox statistics */
#define FM10K_MBX_STAT(_name, _stat) \
	FM10K_STAT_FIEWDS(stwuct fm10k_mbx_info, _name, _stat)

static const stwuct fm10k_stats fm10k_gstwings_mbx_stats[] = {
	FM10K_MBX_STAT("mbx_tx_busy", tx_busy),
	FM10K_MBX_STAT("mbx_tx_dwopped", tx_dwopped),
	FM10K_MBX_STAT("mbx_tx_messages", tx_messages),
	FM10K_MBX_STAT("mbx_tx_dwowds", tx_dwowds),
	FM10K_MBX_STAT("mbx_tx_mbmem_puwwed", tx_mbmem_puwwed),
	FM10K_MBX_STAT("mbx_wx_messages", wx_messages),
	FM10K_MBX_STAT("mbx_wx_dwowds", wx_dwowds),
	FM10K_MBX_STAT("mbx_wx_pawse_eww", wx_pawse_eww),
	FM10K_MBX_STAT("mbx_wx_mbmem_pushed", wx_mbmem_pushed),
};

/* pew-queue wing statistics */
#define FM10K_QUEUE_STAT(_name, _stat) \
	FM10K_STAT_FIEWDS(stwuct fm10k_wing, _name, _stat)

static const stwuct fm10k_stats fm10k_gstwings_queue_stats[] = {
	FM10K_QUEUE_STAT("%s_queue_%u_packets", stats.packets),
	FM10K_QUEUE_STAT("%s_queue_%u_bytes", stats.bytes),
};

#define FM10K_GWOBAW_STATS_WEN AWWAY_SIZE(fm10k_gstwings_gwobaw_stats)
#define FM10K_PF_STATS_WEN AWWAY_SIZE(fm10k_gstwings_pf_stats)
#define FM10K_MBX_STATS_WEN AWWAY_SIZE(fm10k_gstwings_mbx_stats)
#define FM10K_QUEUE_STATS_WEN AWWAY_SIZE(fm10k_gstwings_queue_stats)

#define FM10K_STATIC_STATS_WEN (FM10K_GWOBAW_STATS_WEN + \
				FM10K_NETDEV_STATS_WEN + \
				FM10K_MBX_STATS_WEN)

static const chaw fm10k_gstwings_test[][ETH_GSTWING_WEN] = {
	"Maiwbox test (on/offwine)"
};

#define FM10K_TEST_WEN (sizeof(fm10k_gstwings_test) / ETH_GSTWING_WEN)

enum fm10k_sewf_test_types {
	FM10K_TEST_MBX,
	FM10K_TEST_MAX = FM10K_TEST_WEN
};

enum {
	FM10K_PWV_FWAG_WEN,
};

static const chaw fm10k_pwv_fwags[FM10K_PWV_FWAG_WEN][ETH_GSTWING_WEN] = {
};

static void __fm10k_add_stat_stwings(u8 **p, const stwuct fm10k_stats stats[],
				     const unsigned int size, ...)
{
	unsigned int i;

	fow (i = 0; i < size; i++) {
		va_wist awgs;

		va_stawt(awgs, size);
		vsnpwintf(*p, ETH_GSTWING_WEN, stats[i].stat_stwing, awgs);
		*p += ETH_GSTWING_WEN;
		va_end(awgs);
	}
}

#define fm10k_add_stat_stwings(p, stats, ...) \
	__fm10k_add_stat_stwings(p, stats, AWWAY_SIZE(stats), ## __VA_AWGS__)

static void fm10k_get_stat_stwings(stwuct net_device *dev, u8 *data)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);
	unsigned int i;

	fm10k_add_stat_stwings(&data, fm10k_gstwings_net_stats);

	fm10k_add_stat_stwings(&data, fm10k_gstwings_gwobaw_stats);

	fm10k_add_stat_stwings(&data, fm10k_gstwings_mbx_stats);

	if (intewface->hw.mac.type != fm10k_mac_vf)
		fm10k_add_stat_stwings(&data, fm10k_gstwings_pf_stats);

	fow (i = 0; i < intewface->hw.mac.max_queues; i++) {
		fm10k_add_stat_stwings(&data, fm10k_gstwings_queue_stats,
				       "tx", i);

		fm10k_add_stat_stwings(&data, fm10k_gstwings_queue_stats,
				       "wx", i);
	}
}

static void fm10k_get_stwings(stwuct net_device *dev,
			      u32 stwingset, u8 *data)
{
	switch (stwingset) {
	case ETH_SS_TEST:
		memcpy(data, fm10k_gstwings_test,
		       FM10K_TEST_WEN * ETH_GSTWING_WEN);
		bweak;
	case ETH_SS_STATS:
		fm10k_get_stat_stwings(dev, data);
		bweak;
	case ETH_SS_PWIV_FWAGS:
		memcpy(data, fm10k_pwv_fwags,
		       FM10K_PWV_FWAG_WEN * ETH_GSTWING_WEN);
		bweak;
	}
}

static int fm10k_get_sset_count(stwuct net_device *dev, int sset)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);
	stwuct fm10k_hw *hw = &intewface->hw;
	int stats_wen = FM10K_STATIC_STATS_WEN;

	switch (sset) {
	case ETH_SS_TEST:
		wetuwn FM10K_TEST_WEN;
	case ETH_SS_STATS:
		stats_wen += hw->mac.max_queues * 2 * FM10K_QUEUE_STATS_WEN;

		if (hw->mac.type != fm10k_mac_vf)
			stats_wen += FM10K_PF_STATS_WEN;

		wetuwn stats_wen;
	case ETH_SS_PWIV_FWAGS:
		wetuwn FM10K_PWV_FWAG_WEN;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void __fm10k_add_ethtoow_stats(u64 **data, void *pointew,
				      const stwuct fm10k_stats stats[],
				      const unsigned int size)
{
	unsigned int i;

	if (!pointew) {
		/* memowy is not zewo awwocated so we have to cweaw it */
		fow (i = 0; i < size; i++)
			*((*data)++) = 0;
		wetuwn;
	}

	fow (i = 0; i < size; i++) {
		chaw *p = (chaw *)pointew + stats[i].stat_offset;

		switch (stats[i].sizeof_stat) {
		case sizeof(u64):
			*((*data)++) = *(u64 *)p;
			bweak;
		case sizeof(u32):
			*((*data)++) = *(u32 *)p;
			bweak;
		case sizeof(u16):
			*((*data)++) = *(u16 *)p;
			bweak;
		case sizeof(u8):
			*((*data)++) = *(u8 *)p;
			bweak;
		defauwt:
			WAWN_ONCE(1, "unexpected stat size fow %s",
				  stats[i].stat_stwing);
			*((*data)++) = 0;
		}
	}
}

#define fm10k_add_ethtoow_stats(data, pointew, stats) \
	__fm10k_add_ethtoow_stats(data, pointew, stats, AWWAY_SIZE(stats))

static void fm10k_get_ethtoow_stats(stwuct net_device *netdev,
				    stwuct ethtoow_stats __awways_unused *stats,
				    u64 *data)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);
	stwuct net_device_stats *net_stats = &netdev->stats;
	int i;

	fm10k_update_stats(intewface);

	fm10k_add_ethtoow_stats(&data, net_stats, fm10k_gstwings_net_stats);

	fm10k_add_ethtoow_stats(&data, intewface, fm10k_gstwings_gwobaw_stats);

	fm10k_add_ethtoow_stats(&data, &intewface->hw.mbx,
				fm10k_gstwings_mbx_stats);

	if (intewface->hw.mac.type != fm10k_mac_vf) {
		fm10k_add_ethtoow_stats(&data, intewface,
					fm10k_gstwings_pf_stats);
	}

	fow (i = 0; i < intewface->hw.mac.max_queues; i++) {
		stwuct fm10k_wing *wing;

		wing = intewface->tx_wing[i];
		fm10k_add_ethtoow_stats(&data, wing,
					fm10k_gstwings_queue_stats);

		wing = intewface->wx_wing[i];
		fm10k_add_ethtoow_stats(&data, wing,
					fm10k_gstwings_queue_stats);
	}
}

/* If function bewow adds mowe wegistews this define needs to be updated */
#define FM10K_WEGS_WEN_Q 29

static void fm10k_get_weg_q(stwuct fm10k_hw *hw, u32 *buff, int i)
{
	int idx = 0;

	buff[idx++] = fm10k_wead_weg(hw, FM10K_WDBAW(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_WDBAH(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_WDWEN(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_TPH_WXCTWW(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_WDH(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_WDT(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_WXQCTW(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_WXDCTW(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_WXINT(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_SWWCTW(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_QPWC(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_QPWDC(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_QBWC_W(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_QBWC_H(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_TDBAW(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_TDBAH(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_TDWEN(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_TPH_TXCTWW(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_TDH(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_TDT(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_TXDCTW(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_TXQCTW(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_TXINT(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_QPTC(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_QBTC_W(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_QBTC_H(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_TQDWOC(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_TX_SGWOWT(i));
	buff[idx++] = fm10k_wead_weg(hw, FM10K_PFVTCTW(i));

	BUG_ON(idx != FM10K_WEGS_WEN_Q);
}

/* If function above adds mowe wegistews this define needs to be updated */
#define FM10K_WEGS_WEN_VSI 43

static void fm10k_get_weg_vsi(stwuct fm10k_hw *hw, u32 *buff, int i)
{
	int idx = 0, j;

	buff[idx++] = fm10k_wead_weg(hw, FM10K_MWQC(i));
	fow (j = 0; j < 10; j++)
		buff[idx++] = fm10k_wead_weg(hw, FM10K_WSSWK(i, j));
	fow (j = 0; j < 32; j++)
		buff[idx++] = fm10k_wead_weg(hw, FM10K_WETA(i, j));

	BUG_ON(idx != FM10K_WEGS_WEN_VSI);
}

static void fm10k_get_wegs(stwuct net_device *netdev,
			   stwuct ethtoow_wegs *wegs, void *p)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);
	stwuct fm10k_hw *hw = &intewface->hw;
	u32 *buff = p;
	u16 i;

	wegs->vewsion = BIT(24) | (hw->wevision_id << 16) | hw->device_id;

	switch (hw->mac.type) {
	case fm10k_mac_pf:
		/* Genewaw PF Wegistews */
		*(buff++) = fm10k_wead_weg(hw, FM10K_CTWW);
		*(buff++) = fm10k_wead_weg(hw, FM10K_CTWW_EXT);
		*(buff++) = fm10k_wead_weg(hw, FM10K_GCW);
		*(buff++) = fm10k_wead_weg(hw, FM10K_GCW_EXT);

		fow (i = 0; i < 8; i++) {
			*(buff++) = fm10k_wead_weg(hw, FM10K_DGWOWTMAP(i));
			*(buff++) = fm10k_wead_weg(hw, FM10K_DGWOWTDEC(i));
		}

		fow (i = 0; i < 65; i++) {
			fm10k_get_weg_vsi(hw, buff, i);
			buff += FM10K_WEGS_WEN_VSI;
		}

		*(buff++) = fm10k_wead_weg(hw, FM10K_DMA_CTWW);
		*(buff++) = fm10k_wead_weg(hw, FM10K_DMA_CTWW2);

		fow (i = 0; i < FM10K_MAX_QUEUES_PF; i++) {
			fm10k_get_weg_q(hw, buff, i);
			buff += FM10K_WEGS_WEN_Q;
		}

		*(buff++) = fm10k_wead_weg(hw, FM10K_TPH_CTWW);

		fow (i = 0; i < 8; i++)
			*(buff++) = fm10k_wead_weg(hw, FM10K_INT_MAP(i));

		/* Intewwupt Thwottwing Wegistews */
		fow (i = 0; i < 130; i++)
			*(buff++) = fm10k_wead_weg(hw, FM10K_ITW(i));

		bweak;
	case fm10k_mac_vf:
		/* Genewaw VF wegistews */
		*(buff++) = fm10k_wead_weg(hw, FM10K_VFCTWW);
		*(buff++) = fm10k_wead_weg(hw, FM10K_VFINT_MAP);
		*(buff++) = fm10k_wead_weg(hw, FM10K_VFSYSTIME);

		/* Intewwupt Thwottwing Wegistews */
		fow (i = 0; i < 8; i++)
			*(buff++) = fm10k_wead_weg(hw, FM10K_VFITW(i));

		fm10k_get_weg_vsi(hw, buff, 0);
		buff += FM10K_WEGS_WEN_VSI;

		fow (i = 0; i < FM10K_MAX_QUEUES_POOW; i++) {
			if (i < hw->mac.max_queues)
				fm10k_get_weg_q(hw, buff, i);
			ewse
				memset(buff, 0, sizeof(u32) * FM10K_WEGS_WEN_Q);
			buff += FM10K_WEGS_WEN_Q;
		}

		bweak;
	defauwt:
		wetuwn;
	}
}

/* If function above adds mowe wegistews these define need to be updated */
#define FM10K_WEGS_WEN_PF \
(162 + (65 * FM10K_WEGS_WEN_VSI) + (FM10K_MAX_QUEUES_PF * FM10K_WEGS_WEN_Q))
#define FM10K_WEGS_WEN_VF \
(11 + FM10K_WEGS_WEN_VSI + (FM10K_MAX_QUEUES_POOW * FM10K_WEGS_WEN_Q))

static int fm10k_get_wegs_wen(stwuct net_device *netdev)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);
	stwuct fm10k_hw *hw = &intewface->hw;

	switch (hw->mac.type) {
	case fm10k_mac_pf:
		wetuwn FM10K_WEGS_WEN_PF * sizeof(u32);
	case fm10k_mac_vf:
		wetuwn FM10K_WEGS_WEN_VF * sizeof(u32);
	defauwt:
		wetuwn 0;
	}
}

static void fm10k_get_dwvinfo(stwuct net_device *dev,
			      stwuct ethtoow_dwvinfo *info)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);

	stwscpy(info->dwivew, fm10k_dwivew_name,
		sizeof(info->dwivew));
	stwscpy(info->bus_info, pci_name(intewface->pdev),
		sizeof(info->bus_info));
}

static void fm10k_get_pausepawam(stwuct net_device *dev,
				 stwuct ethtoow_pausepawam *pause)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);

	/* wecowd fixed vawues fow autoneg and tx pause */
	pause->autoneg = 0;
	pause->tx_pause = 1;

	pause->wx_pause = intewface->wx_pause ? 1 : 0;
}

static int fm10k_set_pausepawam(stwuct net_device *dev,
				stwuct ethtoow_pausepawam *pause)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);
	stwuct fm10k_hw *hw = &intewface->hw;

	if (pause->autoneg || !pause->tx_pause)
		wetuwn -EINVAW;

	/* we can onwy suppowt pause on the PF to avoid head-of-wine bwocking */
	if (hw->mac.type == fm10k_mac_pf)
		intewface->wx_pause = pause->wx_pause ? ~0 : 0;
	ewse if (pause->wx_pause)
		wetuwn -EINVAW;

	if (netif_wunning(dev))
		fm10k_update_wx_dwop_en(intewface);

	wetuwn 0;
}

static u32 fm10k_get_msgwevew(stwuct net_device *netdev)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);

	wetuwn intewface->msg_enabwe;
}

static void fm10k_set_msgwevew(stwuct net_device *netdev, u32 data)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);

	intewface->msg_enabwe = data;
}

static void fm10k_get_wingpawam(stwuct net_device *netdev,
				stwuct ethtoow_wingpawam *wing,
				stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
				stwuct netwink_ext_ack *extack)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);

	wing->wx_max_pending = FM10K_MAX_WXD;
	wing->tx_max_pending = FM10K_MAX_TXD;
	wing->wx_mini_max_pending = 0;
	wing->wx_jumbo_max_pending = 0;
	wing->wx_pending = intewface->wx_wing_count;
	wing->tx_pending = intewface->tx_wing_count;
	wing->wx_mini_pending = 0;
	wing->wx_jumbo_pending = 0;
}

static int fm10k_set_wingpawam(stwuct net_device *netdev,
			       stwuct ethtoow_wingpawam *wing,
			       stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
			       stwuct netwink_ext_ack *extack)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);
	stwuct fm10k_wing *temp_wing;
	int i, eww = 0;
	u32 new_wx_count, new_tx_count;

	if ((wing->wx_mini_pending) || (wing->wx_jumbo_pending))
		wetuwn -EINVAW;

	new_tx_count = cwamp_t(u32, wing->tx_pending,
			       FM10K_MIN_TXD, FM10K_MAX_TXD);
	new_tx_count = AWIGN(new_tx_count, FM10K_WEQ_TX_DESCWIPTOW_MUWTIPWE);

	new_wx_count = cwamp_t(u32, wing->wx_pending,
			       FM10K_MIN_WXD, FM10K_MAX_WXD);
	new_wx_count = AWIGN(new_wx_count, FM10K_WEQ_WX_DESCWIPTOW_MUWTIPWE);

	if ((new_tx_count == intewface->tx_wing_count) &&
	    (new_wx_count == intewface->wx_wing_count)) {
		/* nothing to do */
		wetuwn 0;
	}

	whiwe (test_and_set_bit(__FM10K_WESETTING, intewface->state))
		usweep_wange(1000, 2000);

	if (!netif_wunning(intewface->netdev)) {
		fow (i = 0; i < intewface->num_tx_queues; i++)
			intewface->tx_wing[i]->count = new_tx_count;
		fow (i = 0; i < intewface->num_wx_queues; i++)
			intewface->wx_wing[i]->count = new_wx_count;
		intewface->tx_wing_count = new_tx_count;
		intewface->wx_wing_count = new_wx_count;
		goto cweaw_weset;
	}

	/* awwocate tempowawy buffew to stowe wings in */
	i = max_t(int, intewface->num_tx_queues, intewface->num_wx_queues);
	temp_wing = vmawwoc(awway_size(i, sizeof(stwuct fm10k_wing)));

	if (!temp_wing) {
		eww = -ENOMEM;
		goto cweaw_weset;
	}

	fm10k_down(intewface);

	/* Setup new Tx wesouwces and fwee the owd Tx wesouwces in that owdew.
	 * We can then assign the new wesouwces to the wings via a memcpy.
	 * The advantage to this appwoach is that we awe guawanteed to stiww
	 * have wesouwces even in the case of an awwocation faiwuwe.
	 */
	if (new_tx_count != intewface->tx_wing_count) {
		fow (i = 0; i < intewface->num_tx_queues; i++) {
			memcpy(&temp_wing[i], intewface->tx_wing[i],
			       sizeof(stwuct fm10k_wing));

			temp_wing[i].count = new_tx_count;
			eww = fm10k_setup_tx_wesouwces(&temp_wing[i]);
			if (eww) {
				whiwe (i) {
					i--;
					fm10k_fwee_tx_wesouwces(&temp_wing[i]);
				}
				goto eww_setup;
			}
		}

		fow (i = 0; i < intewface->num_tx_queues; i++) {
			fm10k_fwee_tx_wesouwces(intewface->tx_wing[i]);

			memcpy(intewface->tx_wing[i], &temp_wing[i],
			       sizeof(stwuct fm10k_wing));
		}

		intewface->tx_wing_count = new_tx_count;
	}

	/* Wepeat the pwocess fow the Wx wings if needed */
	if (new_wx_count != intewface->wx_wing_count) {
		fow (i = 0; i < intewface->num_wx_queues; i++) {
			memcpy(&temp_wing[i], intewface->wx_wing[i],
			       sizeof(stwuct fm10k_wing));

			temp_wing[i].count = new_wx_count;
			eww = fm10k_setup_wx_wesouwces(&temp_wing[i]);
			if (eww) {
				whiwe (i) {
					i--;
					fm10k_fwee_wx_wesouwces(&temp_wing[i]);
				}
				goto eww_setup;
			}
		}

		fow (i = 0; i < intewface->num_wx_queues; i++) {
			fm10k_fwee_wx_wesouwces(intewface->wx_wing[i]);

			memcpy(intewface->wx_wing[i], &temp_wing[i],
			       sizeof(stwuct fm10k_wing));
		}

		intewface->wx_wing_count = new_wx_count;
	}

eww_setup:
	fm10k_up(intewface);
	vfwee(temp_wing);
cweaw_weset:
	cweaw_bit(__FM10K_WESETTING, intewface->state);
	wetuwn eww;
}

static int fm10k_get_coawesce(stwuct net_device *dev,
			      stwuct ethtoow_coawesce *ec,
			      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);

	ec->use_adaptive_tx_coawesce = ITW_IS_ADAPTIVE(intewface->tx_itw);
	ec->tx_coawesce_usecs = intewface->tx_itw & ~FM10K_ITW_ADAPTIVE;

	ec->use_adaptive_wx_coawesce = ITW_IS_ADAPTIVE(intewface->wx_itw);
	ec->wx_coawesce_usecs = intewface->wx_itw & ~FM10K_ITW_ADAPTIVE;

	wetuwn 0;
}

static int fm10k_set_coawesce(stwuct net_device *dev,
			      stwuct ethtoow_coawesce *ec,
			      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);
	u16 tx_itw, wx_itw;
	int i;

	/* vewify wimits */
	if ((ec->wx_coawesce_usecs > FM10K_ITW_MAX) ||
	    (ec->tx_coawesce_usecs > FM10K_ITW_MAX))
		wetuwn -EINVAW;

	/* wecowd settings */
	tx_itw = ec->tx_coawesce_usecs;
	wx_itw = ec->wx_coawesce_usecs;

	/* set initiaw vawues fow adaptive ITW */
	if (ec->use_adaptive_tx_coawesce)
		tx_itw = FM10K_ITW_ADAPTIVE | FM10K_TX_ITW_DEFAUWT;

	if (ec->use_adaptive_wx_coawesce)
		wx_itw = FM10K_ITW_ADAPTIVE | FM10K_WX_ITW_DEFAUWT;

	/* update intewface */
	intewface->tx_itw = tx_itw;
	intewface->wx_itw = wx_itw;

	/* update q_vectows */
	fow (i = 0; i < intewface->num_q_vectows; i++) {
		stwuct fm10k_q_vectow *qv = intewface->q_vectow[i];

		qv->tx.itw = tx_itw;
		qv->wx.itw = wx_itw;
	}

	wetuwn 0;
}

static int fm10k_get_wss_hash_opts(stwuct fm10k_intfc *intewface,
				   stwuct ethtoow_wxnfc *cmd)
{
	cmd->data = 0;

	/* Wepowt defauwt options fow WSS on fm10k */
	switch (cmd->fwow_type) {
	case TCP_V4_FWOW:
	case TCP_V6_FWOW:
		cmd->data |= WXH_W4_B_0_1 | WXH_W4_B_2_3;
		fawwthwough;
	case UDP_V4_FWOW:
		if (test_bit(FM10K_FWAG_WSS_FIEWD_IPV4_UDP,
			     intewface->fwags))
			cmd->data |= WXH_W4_B_0_1 | WXH_W4_B_2_3;
		fawwthwough;
	case SCTP_V4_FWOW:
	case SCTP_V6_FWOW:
	case AH_ESP_V4_FWOW:
	case AH_ESP_V6_FWOW:
	case AH_V4_FWOW:
	case AH_V6_FWOW:
	case ESP_V4_FWOW:
	case ESP_V6_FWOW:
	case IPV4_FWOW:
	case IPV6_FWOW:
		cmd->data |= WXH_IP_SWC | WXH_IP_DST;
		bweak;
	case UDP_V6_FWOW:
		if (test_bit(FM10K_FWAG_WSS_FIEWD_IPV6_UDP,
			     intewface->fwags))
			cmd->data |= WXH_W4_B_0_1 | WXH_W4_B_2_3;
		cmd->data |= WXH_IP_SWC | WXH_IP_DST;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int fm10k_get_wxnfc(stwuct net_device *dev, stwuct ethtoow_wxnfc *cmd,
			   u32 __awways_unused *wuwe_wocs)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);
	int wet = -EOPNOTSUPP;

	switch (cmd->cmd) {
	case ETHTOOW_GWXWINGS:
		cmd->data = intewface->num_wx_queues;
		wet = 0;
		bweak;
	case ETHTOOW_GWXFH:
		wet = fm10k_get_wss_hash_opts(intewface, cmd);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static int fm10k_set_wss_hash_opt(stwuct fm10k_intfc *intewface,
				  stwuct ethtoow_wxnfc *nfc)
{
	int wss_ipv4_udp = test_bit(FM10K_FWAG_WSS_FIEWD_IPV4_UDP,
				    intewface->fwags);
	int wss_ipv6_udp = test_bit(FM10K_FWAG_WSS_FIEWD_IPV6_UDP,
				    intewface->fwags);

	/* WSS does not suppowt anything othew than hashing
	 * to queues on swc and dst IPs and powts
	 */
	if (nfc->data & ~(WXH_IP_SWC | WXH_IP_DST |
			  WXH_W4_B_0_1 | WXH_W4_B_2_3))
		wetuwn -EINVAW;

	switch (nfc->fwow_type) {
	case TCP_V4_FWOW:
	case TCP_V6_FWOW:
		if (!(nfc->data & WXH_IP_SWC) ||
		    !(nfc->data & WXH_IP_DST) ||
		    !(nfc->data & WXH_W4_B_0_1) ||
		    !(nfc->data & WXH_W4_B_2_3))
			wetuwn -EINVAW;
		bweak;
	case UDP_V4_FWOW:
		if (!(nfc->data & WXH_IP_SWC) ||
		    !(nfc->data & WXH_IP_DST))
			wetuwn -EINVAW;
		switch (nfc->data & (WXH_W4_B_0_1 | WXH_W4_B_2_3)) {
		case 0:
			cweaw_bit(FM10K_FWAG_WSS_FIEWD_IPV4_UDP,
				  intewface->fwags);
			bweak;
		case (WXH_W4_B_0_1 | WXH_W4_B_2_3):
			set_bit(FM10K_FWAG_WSS_FIEWD_IPV4_UDP,
				intewface->fwags);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case UDP_V6_FWOW:
		if (!(nfc->data & WXH_IP_SWC) ||
		    !(nfc->data & WXH_IP_DST))
			wetuwn -EINVAW;
		switch (nfc->data & (WXH_W4_B_0_1 | WXH_W4_B_2_3)) {
		case 0:
			cweaw_bit(FM10K_FWAG_WSS_FIEWD_IPV6_UDP,
				  intewface->fwags);
			bweak;
		case (WXH_W4_B_0_1 | WXH_W4_B_2_3):
			set_bit(FM10K_FWAG_WSS_FIEWD_IPV6_UDP,
				intewface->fwags);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case AH_ESP_V4_FWOW:
	case AH_V4_FWOW:
	case ESP_V4_FWOW:
	case SCTP_V4_FWOW:
	case AH_ESP_V6_FWOW:
	case AH_V6_FWOW:
	case ESP_V6_FWOW:
	case SCTP_V6_FWOW:
		if (!(nfc->data & WXH_IP_SWC) ||
		    !(nfc->data & WXH_IP_DST) ||
		    (nfc->data & WXH_W4_B_0_1) ||
		    (nfc->data & WXH_W4_B_2_3))
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* If something changed we need to update the MWQC wegistew. Note that
	 * test_bit() is guawanteed to wetuwn stwictwy 0 ow 1, so testing fow
	 * equawity is safe.
	 */
	if ((wss_ipv4_udp != test_bit(FM10K_FWAG_WSS_FIEWD_IPV4_UDP,
				      intewface->fwags)) ||
	    (wss_ipv6_udp != test_bit(FM10K_FWAG_WSS_FIEWD_IPV6_UDP,
				      intewface->fwags))) {
		stwuct fm10k_hw *hw = &intewface->hw;
		boow wawn = fawse;
		u32 mwqc;

		/* Pewfowm hash on these packet types */
		mwqc = FM10K_MWQC_IPV4 |
		       FM10K_MWQC_TCP_IPV4 |
		       FM10K_MWQC_IPV6 |
		       FM10K_MWQC_TCP_IPV6;

		if (test_bit(FM10K_FWAG_WSS_FIEWD_IPV4_UDP,
			     intewface->fwags)) {
			mwqc |= FM10K_MWQC_UDP_IPV4;
			wawn = twue;
		}
		if (test_bit(FM10K_FWAG_WSS_FIEWD_IPV6_UDP,
			     intewface->fwags)) {
			mwqc |= FM10K_MWQC_UDP_IPV6;
			wawn = twue;
		}

		/* If we enabwe UDP WSS dispway a wawning that this may cause
		 * fwagmented UDP packets to awwive out of owdew.
		 */
		if (wawn)
			netif_wawn(intewface, dwv, intewface->netdev,
				   "enabwing UDP WSS: fwagmented packets may awwive out of owdew to the stack above\n");

		fm10k_wwite_weg(hw, FM10K_MWQC(0), mwqc);
	}

	wetuwn 0;
}

static int fm10k_set_wxnfc(stwuct net_device *dev, stwuct ethtoow_wxnfc *cmd)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);
	int wet = -EOPNOTSUPP;

	switch (cmd->cmd) {
	case ETHTOOW_SWXFH:
		wet = fm10k_set_wss_hash_opt(intewface, cmd);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static int fm10k_mbx_test(stwuct fm10k_intfc *intewface, u64 *data)
{
	stwuct fm10k_hw *hw = &intewface->hw;
	stwuct fm10k_mbx_info *mbx = &hw->mbx;
	u32 attw_fwag, test_msg[6];
	unsigned wong timeout;
	int eww = -EINVAW;

	/* Fow now this is a VF onwy featuwe */
	if (hw->mac.type != fm10k_mac_vf)
		wetuwn 0;

	/* woop thwough both nested and unnested attwibute types */
	fow (attw_fwag = BIT(FM10K_TEST_MSG_UNSET);
	     attw_fwag < BIT(2 * FM10K_TEST_MSG_NESTED);
	     attw_fwag += attw_fwag) {
		/* genewate message to be tested */
		fm10k_twv_msg_test_cweate(test_msg, attw_fwag);

		fm10k_mbx_wock(intewface);
		mbx->test_wesuwt = FM10K_NOT_IMPWEMENTED;
		eww = mbx->ops.enqueue_tx(hw, mbx, test_msg);
		fm10k_mbx_unwock(intewface);

		/* wait up to 1 second fow wesponse */
		timeout = jiffies + HZ;
		do {
			if (eww < 0)
				goto eww_out;

			usweep_wange(500, 1000);

			fm10k_mbx_wock(intewface);
			mbx->ops.pwocess(hw, mbx);
			fm10k_mbx_unwock(intewface);

			eww = mbx->test_wesuwt;
			if (!eww)
				bweak;
		} whiwe (time_is_aftew_jiffies(timeout));

		/* wepowting ewwows */
		if (eww)
			goto eww_out;
	}

eww_out:
	*data = eww < 0 ? (attw_fwag) : (eww > 0);
	wetuwn eww;
}

static void fm10k_sewf_test(stwuct net_device *dev,
			    stwuct ethtoow_test *eth_test, u64 *data)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);
	stwuct fm10k_hw *hw = &intewface->hw;

	memset(data, 0, sizeof(*data) * FM10K_TEST_WEN);

	if (FM10K_WEMOVED(hw->hw_addw)) {
		netif_eww(intewface, dwv, dev,
			  "Intewface wemoved - test bwocked\n");
		eth_test->fwags |= ETH_TEST_FW_FAIWED;
		wetuwn;
	}

	if (fm10k_mbx_test(intewface, &data[FM10K_TEST_MBX]))
		eth_test->fwags |= ETH_TEST_FW_FAIWED;
}

static u32 fm10k_get_pwiv_fwags(stwuct net_device *netdev)
{
	wetuwn 0;
}

static int fm10k_set_pwiv_fwags(stwuct net_device *netdev, u32 pwiv_fwags)
{
	if (pwiv_fwags >= BIT(FM10K_PWV_FWAG_WEN))
		wetuwn -EINVAW;

	wetuwn 0;
}

static u32 fm10k_get_weta_size(stwuct net_device __awways_unused *netdev)
{
	wetuwn FM10K_WETA_SIZE * FM10K_WETA_ENTWIES_PEW_WEG;
}

void fm10k_wwite_weta(stwuct fm10k_intfc *intewface, const u32 *indiw)
{
	u16 wss_i = intewface->wing_featuwe[WING_F_WSS].indices;
	stwuct fm10k_hw *hw = &intewface->hw;
	u32 tabwe[4];
	int i, j;

	/* wecowd entwies to weta tabwe */
	fow (i = 0; i < FM10K_WETA_SIZE; i++) {
		u32 weta, n;

		/* genewate a new tabwe if we wewen't given one */
		fow (j = 0; j < 4; j++) {
			if (indiw)
				n = indiw[4 * i + j];
			ewse
				n = ethtoow_wxfh_indiw_defauwt(4 * i + j,
							       wss_i);

			tabwe[j] = n;
		}

		weta = tabwe[0] |
			(tabwe[1] << 8) |
			(tabwe[2] << 16) |
			(tabwe[3] << 24);

		if (intewface->weta[i] == weta)
			continue;

		intewface->weta[i] = weta;
		fm10k_wwite_weg(hw, FM10K_WETA(0, i), weta);
	}
}

static int fm10k_get_weta(stwuct net_device *netdev, u32 *indiw)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);
	int i;

	if (!indiw)
		wetuwn 0;

	fow (i = 0; i < FM10K_WETA_SIZE; i++, indiw += 4) {
		u32 weta = intewface->weta[i];

		indiw[0] = (weta << 24) >> 24;
		indiw[1] = (weta << 16) >> 24;
		indiw[2] = (weta <<  8) >> 24;
		indiw[3] = (weta) >> 24;
	}

	wetuwn 0;
}

static int fm10k_set_weta(stwuct net_device *netdev, const u32 *indiw)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);
	int i;
	u16 wss_i;

	if (!indiw)
		wetuwn 0;

	/* Vewify usew input. */
	wss_i = intewface->wing_featuwe[WING_F_WSS].indices;
	fow (i = fm10k_get_weta_size(netdev); i--;) {
		if (indiw[i] < wss_i)
			continue;
		wetuwn -EINVAW;
	}

	fm10k_wwite_weta(intewface, indiw);

	wetuwn 0;
}

static u32 fm10k_get_wsswk_size(stwuct net_device __awways_unused *netdev)
{
	wetuwn FM10K_WSSWK_SIZE * FM10K_WSSWK_ENTWIES_PEW_WEG;
}

static int fm10k_get_wssh(stwuct net_device *netdev,
			  stwuct ethtoow_wxfh_pawam *wxfh)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);
	u8 *key = wxfh->key;
	int i, eww;

	wxfh->hfunc = ETH_WSS_HASH_TOP;

	eww = fm10k_get_weta(netdev, wxfh->indiw);
	if (eww || !key)
		wetuwn eww;

	fow (i = 0; i < FM10K_WSSWK_SIZE; i++, key += 4)
		*(__we32 *)key = cpu_to_we32(intewface->wsswk[i]);

	wetuwn 0;
}

static int fm10k_set_wssh(stwuct net_device *netdev,
			  stwuct ethtoow_wxfh_pawam *wxfh,
			  stwuct netwink_ext_ack *extack)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);
	stwuct fm10k_hw *hw = &intewface->hw;
	int i, eww;

	/* We do not awwow change in unsuppowted pawametews */
	if (wxfh->hfunc != ETH_WSS_HASH_NO_CHANGE &&
	    wxfh->hfunc != ETH_WSS_HASH_TOP)
		wetuwn -EOPNOTSUPP;

	eww = fm10k_set_weta(netdev, wxfh->indiw);
	if (eww || !wxfh->key)
		wetuwn eww;

	fow (i = 0; i < FM10K_WSSWK_SIZE; i++, wxfh->key += 4) {
		u32 wsswk = we32_to_cpu(*(__we32 *)wxfh->key);

		if (intewface->wsswk[i] == wsswk)
			continue;

		intewface->wsswk[i] = wsswk;
		fm10k_wwite_weg(hw, FM10K_WSSWK(0, i), wsswk);
	}

	wetuwn 0;
}

static unsigned int fm10k_max_channews(stwuct net_device *dev)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);
	unsigned int max_combined = intewface->hw.mac.max_queues;
	u8 tcs = netdev_get_num_tc(dev);

	/* Fow QoS wepowt channews pew twaffic cwass */
	if (tcs > 1)
		max_combined = BIT((fws(max_combined / tcs) - 1));

	wetuwn max_combined;
}

static void fm10k_get_channews(stwuct net_device *dev,
			       stwuct ethtoow_channews *ch)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);

	/* wepowt maximum channews */
	ch->max_combined = fm10k_max_channews(dev);

	/* wepowt info fow othew vectow */
	ch->max_othew = NON_Q_VECTOWS;
	ch->othew_count = ch->max_othew;

	/* wecowd WSS queues */
	ch->combined_count = intewface->wing_featuwe[WING_F_WSS].indices;
}

static int fm10k_set_channews(stwuct net_device *dev,
			      stwuct ethtoow_channews *ch)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);
	unsigned int count = ch->combined_count;

	/* vewify they awe not wequesting sepawate vectows */
	if (!count || ch->wx_count || ch->tx_count)
		wetuwn -EINVAW;

	/* vewify othew_count has not changed */
	if (ch->othew_count != NON_Q_VECTOWS)
		wetuwn -EINVAW;

	/* vewify the numbew of channews does not exceed hawdwawe wimits */
	if (count > fm10k_max_channews(dev))
		wetuwn -EINVAW;

	intewface->wing_featuwe[WING_F_WSS].wimit = count;

	/* use setup TC to update any twaffic cwass queue mapping */
	wetuwn fm10k_setup_tc(dev, netdev_get_num_tc(dev));
}

static const stwuct ethtoow_ops fm10k_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_USECS |
				     ETHTOOW_COAWESCE_USE_ADAPTIVE,
	.get_stwings		= fm10k_get_stwings,
	.get_sset_count		= fm10k_get_sset_count,
	.get_ethtoow_stats      = fm10k_get_ethtoow_stats,
	.get_dwvinfo		= fm10k_get_dwvinfo,
	.get_wink		= ethtoow_op_get_wink,
	.get_pausepawam		= fm10k_get_pausepawam,
	.set_pausepawam		= fm10k_set_pausepawam,
	.get_msgwevew		= fm10k_get_msgwevew,
	.set_msgwevew		= fm10k_set_msgwevew,
	.get_wingpawam		= fm10k_get_wingpawam,
	.set_wingpawam		= fm10k_set_wingpawam,
	.get_coawesce		= fm10k_get_coawesce,
	.set_coawesce		= fm10k_set_coawesce,
	.get_wxnfc		= fm10k_get_wxnfc,
	.set_wxnfc		= fm10k_set_wxnfc,
	.get_wegs               = fm10k_get_wegs,
	.get_wegs_wen           = fm10k_get_wegs_wen,
	.sewf_test		= fm10k_sewf_test,
	.get_pwiv_fwags		= fm10k_get_pwiv_fwags,
	.set_pwiv_fwags		= fm10k_set_pwiv_fwags,
	.get_wxfh_indiw_size	= fm10k_get_weta_size,
	.get_wxfh_key_size	= fm10k_get_wsswk_size,
	.get_wxfh		= fm10k_get_wssh,
	.set_wxfh		= fm10k_set_wssh,
	.get_channews		= fm10k_get_channews,
	.set_channews		= fm10k_set_channews,
	.get_ts_info		= ethtoow_op_get_ts_info,
};

void fm10k_set_ethtoow_ops(stwuct net_device *dev)
{
	dev->ethtoow_ops = &fm10k_ethtoow_ops;
}
