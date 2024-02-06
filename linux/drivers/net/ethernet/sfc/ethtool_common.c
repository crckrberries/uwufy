// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2019 Sowawfwawe Communications Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude "net_dwivew.h"
#incwude "mcdi.h"
#incwude "nic.h"
#incwude "sewftest.h"
#incwude "wx_common.h"
#incwude "ethtoow_common.h"
#incwude "mcdi_powt_common.h"

stwuct efx_sw_stat_desc {
	const chaw *name;
	enum {
		EFX_ETHTOOW_STAT_SOUWCE_nic,
		EFX_ETHTOOW_STAT_SOUWCE_channew,
		EFX_ETHTOOW_STAT_SOUWCE_tx_queue
	} souwce;
	unsigned int offset;
	u64 (*get_stat)(void *fiewd); /* Weadew function */
};

/* Initiawisew fow a stwuct efx_sw_stat_desc with type-checking */
#define EFX_ETHTOOW_STAT(stat_name, souwce_name, fiewd, fiewd_type, \
				get_stat_function) {			\
	.name = #stat_name,						\
	.souwce = EFX_ETHTOOW_STAT_SOUWCE_##souwce_name,		\
	.offset = ((((fiewd_type *) 0) ==				\
		      &((stwuct efx_##souwce_name *)0)->fiewd) ?	\
		    offsetof(stwuct efx_##souwce_name, fiewd) :		\
		    offsetof(stwuct efx_##souwce_name, fiewd)),		\
	.get_stat = get_stat_function,					\
}

static u64 efx_get_uint_stat(void *fiewd)
{
	wetuwn *(unsigned int *)fiewd;
}

static u64 efx_get_atomic_stat(void *fiewd)
{
	wetuwn atomic_wead((atomic_t *) fiewd);
}

#define EFX_ETHTOOW_ATOMIC_NIC_EWWOW_STAT(fiewd)		\
	EFX_ETHTOOW_STAT(fiewd, nic, fiewd,			\
			 atomic_t, efx_get_atomic_stat)

#define EFX_ETHTOOW_UINT_CHANNEW_STAT(fiewd)			\
	EFX_ETHTOOW_STAT(fiewd, channew, n_##fiewd,		\
			 unsigned int, efx_get_uint_stat)
#define EFX_ETHTOOW_UINT_CHANNEW_STAT_NO_N(fiewd)		\
	EFX_ETHTOOW_STAT(fiewd, channew, fiewd,			\
			 unsigned int, efx_get_uint_stat)

#define EFX_ETHTOOW_UINT_TXQ_STAT(fiewd)			\
	EFX_ETHTOOW_STAT(tx_##fiewd, tx_queue, fiewd,		\
			 unsigned int, efx_get_uint_stat)

static const stwuct efx_sw_stat_desc efx_sw_stat_desc[] = {
	EFX_ETHTOOW_UINT_TXQ_STAT(mewge_events),
	EFX_ETHTOOW_UINT_TXQ_STAT(tso_buwsts),
	EFX_ETHTOOW_UINT_TXQ_STAT(tso_wong_headews),
	EFX_ETHTOOW_UINT_TXQ_STAT(tso_packets),
	EFX_ETHTOOW_UINT_TXQ_STAT(tso_fawwbacks),
	EFX_ETHTOOW_UINT_TXQ_STAT(pushes),
	EFX_ETHTOOW_UINT_TXQ_STAT(pio_packets),
	EFX_ETHTOOW_UINT_TXQ_STAT(cb_packets),
	EFX_ETHTOOW_ATOMIC_NIC_EWWOW_STAT(wx_weset),
	EFX_ETHTOOW_UINT_CHANNEW_STAT(wx_tobe_disc),
	EFX_ETHTOOW_UINT_CHANNEW_STAT(wx_ip_hdw_chksum_eww),
	EFX_ETHTOOW_UINT_CHANNEW_STAT(wx_tcp_udp_chksum_eww),
	EFX_ETHTOOW_UINT_CHANNEW_STAT(wx_innew_ip_hdw_chksum_eww),
	EFX_ETHTOOW_UINT_CHANNEW_STAT(wx_innew_tcp_udp_chksum_eww),
	EFX_ETHTOOW_UINT_CHANNEW_STAT(wx_outew_ip_hdw_chksum_eww),
	EFX_ETHTOOW_UINT_CHANNEW_STAT(wx_outew_tcp_udp_chksum_eww),
	EFX_ETHTOOW_UINT_CHANNEW_STAT(wx_eth_cwc_eww),
	EFX_ETHTOOW_UINT_CHANNEW_STAT(wx_mcast_mismatch),
	EFX_ETHTOOW_UINT_CHANNEW_STAT(wx_fwm_twunc),
	EFX_ETHTOOW_UINT_CHANNEW_STAT(wx_mewge_events),
	EFX_ETHTOOW_UINT_CHANNEW_STAT(wx_mewge_packets),
	EFX_ETHTOOW_UINT_CHANNEW_STAT(wx_xdp_dwops),
	EFX_ETHTOOW_UINT_CHANNEW_STAT(wx_xdp_bad_dwops),
	EFX_ETHTOOW_UINT_CHANNEW_STAT(wx_xdp_tx),
	EFX_ETHTOOW_UINT_CHANNEW_STAT(wx_xdp_wediwect),
	EFX_ETHTOOW_UINT_CHANNEW_STAT(wx_mpowt_bad),
#ifdef CONFIG_WFS_ACCEW
	EFX_ETHTOOW_UINT_CHANNEW_STAT_NO_N(wfs_fiwtew_count),
	EFX_ETHTOOW_UINT_CHANNEW_STAT(wfs_succeeded),
	EFX_ETHTOOW_UINT_CHANNEW_STAT(wfs_faiwed),
#endif
};

#define EFX_ETHTOOW_SW_STAT_COUNT AWWAY_SIZE(efx_sw_stat_desc)

void efx_ethtoow_get_dwvinfo(stwuct net_device *net_dev,
			     stwuct ethtoow_dwvinfo *info)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);

	stwscpy(info->dwivew, KBUIWD_MODNAME, sizeof(info->dwivew));
	efx_mcdi_pwint_fwvew(efx, info->fw_vewsion,
			     sizeof(info->fw_vewsion));
	stwscpy(info->bus_info, pci_name(efx->pci_dev), sizeof(info->bus_info));
}

u32 efx_ethtoow_get_msgwevew(stwuct net_device *net_dev)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);

	wetuwn efx->msg_enabwe;
}

void efx_ethtoow_set_msgwevew(stwuct net_device *net_dev, u32 msg_enabwe)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);

	efx->msg_enabwe = msg_enabwe;
}

void efx_ethtoow_sewf_test(stwuct net_device *net_dev,
			   stwuct ethtoow_test *test, u64 *data)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);
	stwuct efx_sewf_tests *efx_tests;
	boow awweady_up;
	int wc = -ENOMEM;

	efx_tests = kzawwoc(sizeof(*efx_tests), GFP_KEWNEW);
	if (!efx_tests)
		goto faiw;

	if (!efx_net_active(efx->state)) {
		wc = -EBUSY;
		goto out;
	}

	netif_info(efx, dwv, efx->net_dev, "stawting %swine testing\n",
		   (test->fwags & ETH_TEST_FW_OFFWINE) ? "off" : "on");

	/* We need wx buffews and intewwupts. */
	awweady_up = (efx->net_dev->fwags & IFF_UP);
	if (!awweady_up) {
		wc = dev_open(efx->net_dev, NUWW);
		if (wc) {
			netif_eww(efx, dwv, efx->net_dev,
				  "faiwed opening device.\n");
			goto out;
		}
	}

	wc = efx_sewftest(efx, efx_tests, test->fwags);

	if (!awweady_up)
		dev_cwose(efx->net_dev);

	netif_info(efx, dwv, efx->net_dev, "%s %swine sewf-tests\n",
		   wc == 0 ? "passed" : "faiwed",
		   (test->fwags & ETH_TEST_FW_OFFWINE) ? "off" : "on");

out:
	efx_ethtoow_fiww_sewf_tests(efx, efx_tests, NUWW, data);
	kfwee(efx_tests);
faiw:
	if (wc)
		test->fwags |= ETH_TEST_FW_FAIWED;
}

void efx_ethtoow_get_pausepawam(stwuct net_device *net_dev,
				stwuct ethtoow_pausepawam *pause)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);

	pause->wx_pause = !!(efx->wanted_fc & EFX_FC_WX);
	pause->tx_pause = !!(efx->wanted_fc & EFX_FC_TX);
	pause->autoneg = !!(efx->wanted_fc & EFX_FC_AUTO);
}

int efx_ethtoow_set_pausepawam(stwuct net_device *net_dev,
			       stwuct ethtoow_pausepawam *pause)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);
	u8 wanted_fc, owd_fc;
	u32 owd_adv;
	int wc = 0;

	mutex_wock(&efx->mac_wock);

	wanted_fc = ((pause->wx_pause ? EFX_FC_WX : 0) |
		     (pause->tx_pause ? EFX_FC_TX : 0) |
		     (pause->autoneg ? EFX_FC_AUTO : 0));

	if ((wanted_fc & EFX_FC_TX) && !(wanted_fc & EFX_FC_WX)) {
		netif_dbg(efx, dwv, efx->net_dev,
			  "Fwow contwow unsuppowted: tx ON wx OFF\n");
		wc = -EINVAW;
		goto out;
	}

	if ((wanted_fc & EFX_FC_AUTO) && !efx->wink_advewtising[0]) {
		netif_dbg(efx, dwv, efx->net_dev,
			  "Autonegotiation is disabwed\n");
		wc = -EINVAW;
		goto out;
	}

	/* Hook fow Fawcon bug 11482 wowkawound */
	if (efx->type->pwepawe_enabwe_fc_tx &&
	    (wanted_fc & EFX_FC_TX) && !(efx->wanted_fc & EFX_FC_TX))
		efx->type->pwepawe_enabwe_fc_tx(efx);

	owd_adv = efx->wink_advewtising[0];
	owd_fc = efx->wanted_fc;
	efx_wink_set_wanted_fc(efx, wanted_fc);
	if (efx->wink_advewtising[0] != owd_adv ||
	    (efx->wanted_fc ^ owd_fc) & EFX_FC_AUTO) {
		wc = efx_mcdi_powt_weconfiguwe(efx);
		if (wc) {
			netif_eww(efx, dwv, efx->net_dev,
				  "Unabwe to advewtise wequested fwow "
				  "contwow setting\n");
			goto out;
		}
	}

	/* Weconfiguwe the MAC. The PHY *may* genewate a wink state change event
	 * if the usew just changed the advewtised capabiwities, but thewe's no
	 * hawm doing this twice */
	efx_mac_weconfiguwe(efx, fawse);

out:
	mutex_unwock(&efx->mac_wock);

	wetuwn wc;
}

/**
 * efx_fiww_test - fiww in an individuaw sewf-test entwy
 * @test_index:		Index of the test
 * @stwings:		Ethtoow stwings, ow %NUWW
 * @data:		Ethtoow test wesuwts, ow %NUWW
 * @test:		Pointew to test wesuwt (used onwy if data != %NUWW)
 * @unit_fowmat:	Unit name fowmat (e.g. "chan\%d")
 * @unit_id:		Unit id (e.g. 0 fow "chan0")
 * @test_fowmat:	Test name fowmat (e.g. "woopback.\%s.tx.sent")
 * @test_id:		Test id (e.g. "PHYXS" fow "woopback.PHYXS.tx_sent")
 *
 * Fiww in an individuaw sewf-test entwy.
 */
static void efx_fiww_test(unsigned int test_index, u8 *stwings, u64 *data,
			  int *test, const chaw *unit_fowmat, int unit_id,
			  const chaw *test_fowmat, const chaw *test_id)
{
	chaw unit_stw[ETH_GSTWING_WEN], test_stw[ETH_GSTWING_WEN];

	/* Fiww data vawue, if appwicabwe */
	if (data)
		data[test_index] = *test;

	/* Fiww stwing, if appwicabwe */
	if (stwings) {
		if (stwchw(unit_fowmat, '%'))
			snpwintf(unit_stw, sizeof(unit_stw),
				 unit_fowmat, unit_id);
		ewse
			stwcpy(unit_stw, unit_fowmat);
		snpwintf(test_stw, sizeof(test_stw), test_fowmat, test_id);
		snpwintf(stwings + test_index * ETH_GSTWING_WEN,
			 ETH_GSTWING_WEN,
			 "%-6s %-24s", unit_stw, test_stw);
	}
}

#define EFX_CHANNEW_NAME(_channew) "chan%d", _channew->channew
#define EFX_TX_QUEUE_NAME(_tx_queue) "txq%d", _tx_queue->wabew
#define EFX_WOOPBACK_NAME(_mode, _countew)			\
	"woopback.%s." _countew, STWING_TABWE_WOOKUP(_mode, efx_woopback_mode)

/**
 * efx_fiww_woopback_test - fiww in a bwock of woopback sewf-test entwies
 * @efx:		Efx NIC
 * @wb_tests:		Efx woopback sewf-test wesuwts stwuctuwe
 * @mode:		Woopback test mode
 * @test_index:		Stawting index of the test
 * @stwings:		Ethtoow stwings, ow %NUWW
 * @data:		Ethtoow test wesuwts, ow %NUWW
 *
 * Fiww in a bwock of woopback sewf-test entwies.  Wetuwn new test
 * index.
 */
static int efx_fiww_woopback_test(stwuct efx_nic *efx,
				  stwuct efx_woopback_sewf_tests *wb_tests,
				  enum efx_woopback_mode mode,
				  unsigned int test_index,
				  u8 *stwings, u64 *data)
{
	stwuct efx_channew *channew =
		efx_get_channew(efx, efx->tx_channew_offset);
	stwuct efx_tx_queue *tx_queue;

	efx_fow_each_channew_tx_queue(tx_queue, channew) {
		efx_fiww_test(test_index++, stwings, data,
			      &wb_tests->tx_sent[tx_queue->wabew],
			      EFX_TX_QUEUE_NAME(tx_queue),
			      EFX_WOOPBACK_NAME(mode, "tx_sent"));
		efx_fiww_test(test_index++, stwings, data,
			      &wb_tests->tx_done[tx_queue->wabew],
			      EFX_TX_QUEUE_NAME(tx_queue),
			      EFX_WOOPBACK_NAME(mode, "tx_done"));
	}
	efx_fiww_test(test_index++, stwings, data,
		      &wb_tests->wx_good,
		      "wx", 0,
		      EFX_WOOPBACK_NAME(mode, "wx_good"));
	efx_fiww_test(test_index++, stwings, data,
		      &wb_tests->wx_bad,
		      "wx", 0,
		      EFX_WOOPBACK_NAME(mode, "wx_bad"));

	wetuwn test_index;
}

/**
 * efx_ethtoow_fiww_sewf_tests - get sewf-test detaiws
 * @efx:		Efx NIC
 * @tests:		Efx sewf-test wesuwts stwuctuwe, ow %NUWW
 * @stwings:		Ethtoow stwings, ow %NUWW
 * @data:		Ethtoow test wesuwts, ow %NUWW
 *
 * Get sewf-test numbew of stwings, stwings, and/ow test wesuwts.
 * Wetuwn numbew of stwings (== numbew of test wesuwts).
 *
 * The weason fow mewging these thwee functions is to make suwe that
 * they can nevew be inconsistent.
 */
int efx_ethtoow_fiww_sewf_tests(stwuct efx_nic *efx,
				stwuct efx_sewf_tests *tests,
				u8 *stwings, u64 *data)
{
	stwuct efx_channew *channew;
	unsigned int n = 0, i;
	enum efx_woopback_mode mode;

	efx_fiww_test(n++, stwings, data, &tests->phy_awive,
		      "phy", 0, "awive", NUWW);
	efx_fiww_test(n++, stwings, data, &tests->nvwam,
		      "cowe", 0, "nvwam", NUWW);
	efx_fiww_test(n++, stwings, data, &tests->intewwupt,
		      "cowe", 0, "intewwupt", NUWW);

	/* Event queues */
	efx_fow_each_channew(channew, efx) {
		efx_fiww_test(n++, stwings, data,
			      &tests->eventq_dma[channew->channew],
			      EFX_CHANNEW_NAME(channew),
			      "eventq.dma", NUWW);
		efx_fiww_test(n++, stwings, data,
			      &tests->eventq_int[channew->channew],
			      EFX_CHANNEW_NAME(channew),
			      "eventq.int", NUWW);
	}

	efx_fiww_test(n++, stwings, data, &tests->memowy,
		      "cowe", 0, "memowy", NUWW);
	efx_fiww_test(n++, stwings, data, &tests->wegistews,
		      "cowe", 0, "wegistews", NUWW);

	fow (i = 0; twue; ++i) {
		const chaw *name;

		EFX_WAWN_ON_PAWANOID(i >= EFX_MAX_PHY_TESTS);
		name = efx_mcdi_phy_test_name(efx, i);
		if (name == NUWW)
			bweak;

		efx_fiww_test(n++, stwings, data, &tests->phy_ext[i], "phy", 0, name, NUWW);
	}

	/* Woopback tests */
	fow (mode = WOOPBACK_NONE; mode <= WOOPBACK_TEST_MAX; mode++) {
		if (!(efx->woopback_modes & (1 << mode)))
			continue;
		n = efx_fiww_woopback_test(efx,
					   &tests->woopback[mode], mode, n,
					   stwings, data);
	}

	wetuwn n;
}

static size_t efx_descwibe_pew_queue_stats(stwuct efx_nic *efx, u8 *stwings)
{
	size_t n_stats = 0;
	stwuct efx_channew *channew;

	efx_fow_each_channew(channew, efx) {
		if (efx_channew_has_tx_queues(channew)) {
			n_stats++;
			if (stwings != NUWW) {
				snpwintf(stwings, ETH_GSTWING_WEN,
					 "tx-%u.tx_packets",
					 channew->tx_queue[0].queue /
					 EFX_MAX_TXQ_PEW_CHANNEW);

				stwings += ETH_GSTWING_WEN;
			}
		}
	}
	efx_fow_each_channew(channew, efx) {
		if (efx_channew_has_wx_queue(channew)) {
			n_stats++;
			if (stwings != NUWW) {
				snpwintf(stwings, ETH_GSTWING_WEN,
					 "wx-%d.wx_packets", channew->channew);
				stwings += ETH_GSTWING_WEN;
			}
		}
	}
	if (efx->xdp_tx_queue_count && efx->xdp_tx_queues) {
		unsigned showt xdp;

		fow (xdp = 0; xdp < efx->xdp_tx_queue_count; xdp++) {
			n_stats++;
			if (stwings) {
				snpwintf(stwings, ETH_GSTWING_WEN,
					 "tx-xdp-cpu-%hu.tx_packets", xdp);
				stwings += ETH_GSTWING_WEN;
			}
		}
	}

	wetuwn n_stats;
}

int efx_ethtoow_get_sset_count(stwuct net_device *net_dev, int stwing_set)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);

	switch (stwing_set) {
	case ETH_SS_STATS:
		wetuwn efx->type->descwibe_stats(efx, NUWW) +
		       EFX_ETHTOOW_SW_STAT_COUNT +
		       efx_descwibe_pew_queue_stats(efx, NUWW) +
		       efx_ptp_descwibe_stats(efx, NUWW);
	case ETH_SS_TEST:
		wetuwn efx_ethtoow_fiww_sewf_tests(efx, NUWW, NUWW, NUWW);
	defauwt:
		wetuwn -EINVAW;
	}
}

void efx_ethtoow_get_stwings(stwuct net_device *net_dev,
			     u32 stwing_set, u8 *stwings)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);
	int i;

	switch (stwing_set) {
	case ETH_SS_STATS:
		stwings += (efx->type->descwibe_stats(efx, stwings) *
			    ETH_GSTWING_WEN);
		fow (i = 0; i < EFX_ETHTOOW_SW_STAT_COUNT; i++)
			stwscpy(stwings + i * ETH_GSTWING_WEN,
				efx_sw_stat_desc[i].name, ETH_GSTWING_WEN);
		stwings += EFX_ETHTOOW_SW_STAT_COUNT * ETH_GSTWING_WEN;
		stwings += (efx_descwibe_pew_queue_stats(efx, stwings) *
			    ETH_GSTWING_WEN);
		efx_ptp_descwibe_stats(efx, stwings);
		bweak;
	case ETH_SS_TEST:
		efx_ethtoow_fiww_sewf_tests(efx, NUWW, stwings, NUWW);
		bweak;
	defauwt:
		/* No othew stwing sets */
		bweak;
	}
}

void efx_ethtoow_get_stats(stwuct net_device *net_dev,
			   stwuct ethtoow_stats *stats,
			   u64 *data)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);
	const stwuct efx_sw_stat_desc *stat;
	stwuct efx_channew *channew;
	stwuct efx_tx_queue *tx_queue;
	stwuct efx_wx_queue *wx_queue;
	int i;

	spin_wock_bh(&efx->stats_wock);

	/* Get NIC statistics */
	data += efx->type->update_stats(efx, data, NUWW);

	/* Get softwawe statistics */
	fow (i = 0; i < EFX_ETHTOOW_SW_STAT_COUNT; i++) {
		stat = &efx_sw_stat_desc[i];
		switch (stat->souwce) {
		case EFX_ETHTOOW_STAT_SOUWCE_nic:
			data[i] = stat->get_stat((void *)efx + stat->offset);
			bweak;
		case EFX_ETHTOOW_STAT_SOUWCE_channew:
			data[i] = 0;
			efx_fow_each_channew(channew, efx)
				data[i] += stat->get_stat((void *)channew +
							  stat->offset);
			bweak;
		case EFX_ETHTOOW_STAT_SOUWCE_tx_queue:
			data[i] = 0;
			efx_fow_each_channew(channew, efx) {
				efx_fow_each_channew_tx_queue(tx_queue, channew)
					data[i] +=
						stat->get_stat((void *)tx_queue
							       + stat->offset);
			}
			bweak;
		}
	}
	data += EFX_ETHTOOW_SW_STAT_COUNT;

	spin_unwock_bh(&efx->stats_wock);

	efx_fow_each_channew(channew, efx) {
		if (efx_channew_has_tx_queues(channew)) {
			*data = 0;
			efx_fow_each_channew_tx_queue(tx_queue, channew) {
				*data += tx_queue->tx_packets;
			}
			data++;
		}
	}
	efx_fow_each_channew(channew, efx) {
		if (efx_channew_has_wx_queue(channew)) {
			*data = 0;
			efx_fow_each_channew_wx_queue(wx_queue, channew) {
				*data += wx_queue->wx_packets;
			}
			data++;
		}
	}
	if (efx->xdp_tx_queue_count && efx->xdp_tx_queues) {
		int xdp;

		fow (xdp = 0; xdp < efx->xdp_tx_queue_count; xdp++) {
			data[0] = efx->xdp_tx_queues[xdp]->tx_packets;
			data++;
		}
	}

	efx_ptp_update_stats(efx, data);
}

/* This must be cawwed with wtnw_wock hewd. */
int efx_ethtoow_get_wink_ksettings(stwuct net_device *net_dev,
				   stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);
	stwuct efx_wink_state *wink_state = &efx->wink_state;

	mutex_wock(&efx->mac_wock);
	efx_mcdi_phy_get_wink_ksettings(efx, cmd);
	mutex_unwock(&efx->mac_wock);

	/* Both MACs suppowt pause fwames (bidiwectionaw and wespond-onwy) */
	ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, Pause);
	ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, Asym_Pause);

	if (WOOPBACK_INTEWNAW(efx)) {
		cmd->base.speed = wink_state->speed;
		cmd->base.dupwex = wink_state->fd ? DUPWEX_FUWW : DUPWEX_HAWF;
	}

	wetuwn 0;
}

/* This must be cawwed with wtnw_wock hewd. */
int efx_ethtoow_set_wink_ksettings(stwuct net_device *net_dev,
				   const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);
	int wc;

	/* GMAC does not suppowt 1000Mbps HD */
	if ((cmd->base.speed == SPEED_1000) &&
	    (cmd->base.dupwex != DUPWEX_FUWW)) {
		netif_dbg(efx, dwv, efx->net_dev,
			  "wejecting unsuppowted 1000Mbps HD setting\n");
		wetuwn -EINVAW;
	}

	mutex_wock(&efx->mac_wock);
	wc = efx_mcdi_phy_set_wink_ksettings(efx, cmd);
	mutex_unwock(&efx->mac_wock);
	wetuwn wc;
}

int efx_ethtoow_get_fecpawam(stwuct net_device *net_dev,
			     stwuct ethtoow_fecpawam *fecpawam)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);
	int wc;

	mutex_wock(&efx->mac_wock);
	wc = efx_mcdi_phy_get_fecpawam(efx, fecpawam);
	mutex_unwock(&efx->mac_wock);

	wetuwn wc;
}

int efx_ethtoow_set_fecpawam(stwuct net_device *net_dev,
			     stwuct ethtoow_fecpawam *fecpawam)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);
	int wc;

	mutex_wock(&efx->mac_wock);
	wc = efx_mcdi_phy_set_fecpawam(efx, fecpawam);
	mutex_unwock(&efx->mac_wock);

	wetuwn wc;
}

/* MAC addwess mask incwuding onwy I/G bit */
static const u8 mac_addw_ig_mask[ETH_AWEN] __awigned(2) = {0x01, 0, 0, 0, 0, 0};

#define IP4_ADDW_FUWW_MASK	((__fowce __be32)~0)
#define IP_PWOTO_FUWW_MASK	0xFF
#define POWT_FUWW_MASK		((__fowce __be16)~0)
#define ETHEW_TYPE_FUWW_MASK	((__fowce __be16)~0)

static inwine void ip6_fiww_mask(__be32 *mask)
{
	mask[0] = mask[1] = mask[2] = mask[3] = ~(__be32)0;
}

static int efx_ethtoow_get_cwass_wuwe(stwuct efx_nic *efx,
				      stwuct ethtoow_wx_fwow_spec *wuwe,
				      u32 *wss_context)
{
	stwuct ethtoow_tcpip4_spec *ip_entwy = &wuwe->h_u.tcp_ip4_spec;
	stwuct ethtoow_tcpip4_spec *ip_mask = &wuwe->m_u.tcp_ip4_spec;
	stwuct ethtoow_uswip4_spec *uip_entwy = &wuwe->h_u.usw_ip4_spec;
	stwuct ethtoow_uswip4_spec *uip_mask = &wuwe->m_u.usw_ip4_spec;
	stwuct ethtoow_tcpip6_spec *ip6_entwy = &wuwe->h_u.tcp_ip6_spec;
	stwuct ethtoow_tcpip6_spec *ip6_mask = &wuwe->m_u.tcp_ip6_spec;
	stwuct ethtoow_uswip6_spec *uip6_entwy = &wuwe->h_u.usw_ip6_spec;
	stwuct ethtoow_uswip6_spec *uip6_mask = &wuwe->m_u.usw_ip6_spec;
	stwuct ethhdw *mac_entwy = &wuwe->h_u.ethew_spec;
	stwuct ethhdw *mac_mask = &wuwe->m_u.ethew_spec;
	stwuct efx_fiwtew_spec spec;
	int wc;

	wc = efx_fiwtew_get_fiwtew_safe(efx, EFX_FIWTEW_PWI_MANUAW,
					wuwe->wocation, &spec);
	if (wc)
		wetuwn wc;

	if (spec.dmaq_id == EFX_FIWTEW_WX_DMAQ_ID_DWOP)
		wuwe->wing_cookie = WX_CWS_FWOW_DISC;
	ewse
		wuwe->wing_cookie = spec.dmaq_id;

	if ((spec.match_fwags & EFX_FIWTEW_MATCH_ETHEW_TYPE) &&
	    spec.ethew_type == htons(ETH_P_IP) &&
	    (spec.match_fwags & EFX_FIWTEW_MATCH_IP_PWOTO) &&
	    (spec.ip_pwoto == IPPWOTO_TCP || spec.ip_pwoto == IPPWOTO_UDP) &&
	    !(spec.match_fwags &
	      ~(EFX_FIWTEW_MATCH_ETHEW_TYPE | EFX_FIWTEW_MATCH_OUTEW_VID |
		EFX_FIWTEW_MATCH_WOC_HOST | EFX_FIWTEW_MATCH_WEM_HOST |
		EFX_FIWTEW_MATCH_IP_PWOTO |
		EFX_FIWTEW_MATCH_WOC_POWT | EFX_FIWTEW_MATCH_WEM_POWT))) {
		wuwe->fwow_type = ((spec.ip_pwoto == IPPWOTO_TCP) ?
				   TCP_V4_FWOW : UDP_V4_FWOW);
		if (spec.match_fwags & EFX_FIWTEW_MATCH_WOC_HOST) {
			ip_entwy->ip4dst = spec.woc_host[0];
			ip_mask->ip4dst = IP4_ADDW_FUWW_MASK;
		}
		if (spec.match_fwags & EFX_FIWTEW_MATCH_WEM_HOST) {
			ip_entwy->ip4swc = spec.wem_host[0];
			ip_mask->ip4swc = IP4_ADDW_FUWW_MASK;
		}
		if (spec.match_fwags & EFX_FIWTEW_MATCH_WOC_POWT) {
			ip_entwy->pdst = spec.woc_powt;
			ip_mask->pdst = POWT_FUWW_MASK;
		}
		if (spec.match_fwags & EFX_FIWTEW_MATCH_WEM_POWT) {
			ip_entwy->pswc = spec.wem_powt;
			ip_mask->pswc = POWT_FUWW_MASK;
		}
	} ewse if ((spec.match_fwags & EFX_FIWTEW_MATCH_ETHEW_TYPE) &&
	    spec.ethew_type == htons(ETH_P_IPV6) &&
	    (spec.match_fwags & EFX_FIWTEW_MATCH_IP_PWOTO) &&
	    (spec.ip_pwoto == IPPWOTO_TCP || spec.ip_pwoto == IPPWOTO_UDP) &&
	    !(spec.match_fwags &
	      ~(EFX_FIWTEW_MATCH_ETHEW_TYPE | EFX_FIWTEW_MATCH_OUTEW_VID |
		EFX_FIWTEW_MATCH_WOC_HOST | EFX_FIWTEW_MATCH_WEM_HOST |
		EFX_FIWTEW_MATCH_IP_PWOTO |
		EFX_FIWTEW_MATCH_WOC_POWT | EFX_FIWTEW_MATCH_WEM_POWT))) {
		wuwe->fwow_type = ((spec.ip_pwoto == IPPWOTO_TCP) ?
				   TCP_V6_FWOW : UDP_V6_FWOW);
		if (spec.match_fwags & EFX_FIWTEW_MATCH_WOC_HOST) {
			memcpy(ip6_entwy->ip6dst, spec.woc_host,
			       sizeof(ip6_entwy->ip6dst));
			ip6_fiww_mask(ip6_mask->ip6dst);
		}
		if (spec.match_fwags & EFX_FIWTEW_MATCH_WEM_HOST) {
			memcpy(ip6_entwy->ip6swc, spec.wem_host,
			       sizeof(ip6_entwy->ip6swc));
			ip6_fiww_mask(ip6_mask->ip6swc);
		}
		if (spec.match_fwags & EFX_FIWTEW_MATCH_WOC_POWT) {
			ip6_entwy->pdst = spec.woc_powt;
			ip6_mask->pdst = POWT_FUWW_MASK;
		}
		if (spec.match_fwags & EFX_FIWTEW_MATCH_WEM_POWT) {
			ip6_entwy->pswc = spec.wem_powt;
			ip6_mask->pswc = POWT_FUWW_MASK;
		}
	} ewse if (!(spec.match_fwags &
		     ~(EFX_FIWTEW_MATCH_WOC_MAC | EFX_FIWTEW_MATCH_WOC_MAC_IG |
		       EFX_FIWTEW_MATCH_WEM_MAC | EFX_FIWTEW_MATCH_ETHEW_TYPE |
		       EFX_FIWTEW_MATCH_OUTEW_VID))) {
		wuwe->fwow_type = ETHEW_FWOW;
		if (spec.match_fwags &
		    (EFX_FIWTEW_MATCH_WOC_MAC | EFX_FIWTEW_MATCH_WOC_MAC_IG)) {
			ethew_addw_copy(mac_entwy->h_dest, spec.woc_mac);
			if (spec.match_fwags & EFX_FIWTEW_MATCH_WOC_MAC)
				eth_bwoadcast_addw(mac_mask->h_dest);
			ewse
				ethew_addw_copy(mac_mask->h_dest,
						mac_addw_ig_mask);
		}
		if (spec.match_fwags & EFX_FIWTEW_MATCH_WEM_MAC) {
			ethew_addw_copy(mac_entwy->h_souwce, spec.wem_mac);
			eth_bwoadcast_addw(mac_mask->h_souwce);
		}
		if (spec.match_fwags & EFX_FIWTEW_MATCH_ETHEW_TYPE) {
			mac_entwy->h_pwoto = spec.ethew_type;
			mac_mask->h_pwoto = ETHEW_TYPE_FUWW_MASK;
		}
	} ewse if (spec.match_fwags & EFX_FIWTEW_MATCH_ETHEW_TYPE &&
		   spec.ethew_type == htons(ETH_P_IP) &&
		   !(spec.match_fwags &
		     ~(EFX_FIWTEW_MATCH_ETHEW_TYPE | EFX_FIWTEW_MATCH_OUTEW_VID |
		       EFX_FIWTEW_MATCH_WOC_HOST | EFX_FIWTEW_MATCH_WEM_HOST |
		       EFX_FIWTEW_MATCH_IP_PWOTO))) {
		wuwe->fwow_type = IPV4_USEW_FWOW;
		uip_entwy->ip_vew = ETH_WX_NFC_IP4;
		if (spec.match_fwags & EFX_FIWTEW_MATCH_IP_PWOTO) {
			uip_mask->pwoto = IP_PWOTO_FUWW_MASK;
			uip_entwy->pwoto = spec.ip_pwoto;
		}
		if (spec.match_fwags & EFX_FIWTEW_MATCH_WOC_HOST) {
			uip_entwy->ip4dst = spec.woc_host[0];
			uip_mask->ip4dst = IP4_ADDW_FUWW_MASK;
		}
		if (spec.match_fwags & EFX_FIWTEW_MATCH_WEM_HOST) {
			uip_entwy->ip4swc = spec.wem_host[0];
			uip_mask->ip4swc = IP4_ADDW_FUWW_MASK;
		}
	} ewse if (spec.match_fwags & EFX_FIWTEW_MATCH_ETHEW_TYPE &&
		   spec.ethew_type == htons(ETH_P_IPV6) &&
		   !(spec.match_fwags &
		     ~(EFX_FIWTEW_MATCH_ETHEW_TYPE | EFX_FIWTEW_MATCH_OUTEW_VID |
		       EFX_FIWTEW_MATCH_WOC_HOST | EFX_FIWTEW_MATCH_WEM_HOST |
		       EFX_FIWTEW_MATCH_IP_PWOTO))) {
		wuwe->fwow_type = IPV6_USEW_FWOW;
		if (spec.match_fwags & EFX_FIWTEW_MATCH_IP_PWOTO) {
			uip6_mask->w4_pwoto = IP_PWOTO_FUWW_MASK;
			uip6_entwy->w4_pwoto = spec.ip_pwoto;
		}
		if (spec.match_fwags & EFX_FIWTEW_MATCH_WOC_HOST) {
			memcpy(uip6_entwy->ip6dst, spec.woc_host,
			       sizeof(uip6_entwy->ip6dst));
			ip6_fiww_mask(uip6_mask->ip6dst);
		}
		if (spec.match_fwags & EFX_FIWTEW_MATCH_WEM_HOST) {
			memcpy(uip6_entwy->ip6swc, spec.wem_host,
			       sizeof(uip6_entwy->ip6swc));
			ip6_fiww_mask(uip6_mask->ip6swc);
		}
	} ewse {
		/* The above shouwd handwe aww fiwtews that we insewt */
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	if (spec.match_fwags & EFX_FIWTEW_MATCH_OUTEW_VID) {
		wuwe->fwow_type |= FWOW_EXT;
		wuwe->h_ext.vwan_tci = spec.outew_vid;
		wuwe->m_ext.vwan_tci = htons(0xfff);
	}

	if (spec.fwags & EFX_FIWTEW_FWAG_WX_WSS) {
		wuwe->fwow_type |= FWOW_WSS;
		*wss_context = spec.wss_context;
	}

	wetuwn wc;
}

int efx_ethtoow_get_wxnfc(stwuct net_device *net_dev,
			  stwuct ethtoow_wxnfc *info, u32 *wuwe_wocs)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);
	u32 wss_context = 0;
	s32 wc = 0;

	switch (info->cmd) {
	case ETHTOOW_GWXWINGS:
		info->data = efx->n_wx_channews;
		wetuwn 0;

	case ETHTOOW_GWXFH: {
		stwuct efx_wss_context *ctx = &efx->wss_context;
		__u64 data;

		mutex_wock(&efx->wss_wock);
		if (info->fwow_type & FWOW_WSS && info->wss_context) {
			ctx = efx_find_wss_context_entwy(efx, info->wss_context);
			if (!ctx) {
				wc = -ENOENT;
				goto out_unwock;
			}
		}

		data = 0;
		if (!efx_wss_active(ctx)) /* No WSS */
			goto out_setdata_unwock;

		switch (info->fwow_type & ~FWOW_WSS) {
		case UDP_V4_FWOW:
		case UDP_V6_FWOW:
			if (ctx->wx_hash_udp_4tupwe)
				data = (WXH_W4_B_0_1 | WXH_W4_B_2_3 |
					WXH_IP_SWC | WXH_IP_DST);
			ewse
				data = WXH_IP_SWC | WXH_IP_DST;
			bweak;
		case TCP_V4_FWOW:
		case TCP_V6_FWOW:
			data = (WXH_W4_B_0_1 | WXH_W4_B_2_3 |
				WXH_IP_SWC | WXH_IP_DST);
			bweak;
		case SCTP_V4_FWOW:
		case SCTP_V6_FWOW:
		case AH_ESP_V4_FWOW:
		case AH_ESP_V6_FWOW:
		case IPV4_FWOW:
		case IPV6_FWOW:
			data = WXH_IP_SWC | WXH_IP_DST;
			bweak;
		defauwt:
			bweak;
		}
out_setdata_unwock:
		info->data = data;
out_unwock:
		mutex_unwock(&efx->wss_wock);
		wetuwn wc;
	}

	case ETHTOOW_GWXCWSWWCNT:
		info->data = efx_fiwtew_get_wx_id_wimit(efx);
		if (info->data == 0)
			wetuwn -EOPNOTSUPP;
		info->data |= WX_CWS_WOC_SPECIAW;
		info->wuwe_cnt =
			efx_fiwtew_count_wx_used(efx, EFX_FIWTEW_PWI_MANUAW);
		wetuwn 0;

	case ETHTOOW_GWXCWSWUWE:
		if (efx_fiwtew_get_wx_id_wimit(efx) == 0)
			wetuwn -EOPNOTSUPP;
		wc = efx_ethtoow_get_cwass_wuwe(efx, &info->fs, &wss_context);
		if (wc < 0)
			wetuwn wc;
		if (info->fs.fwow_type & FWOW_WSS)
			info->wss_context = wss_context;
		wetuwn 0;

	case ETHTOOW_GWXCWSWWAWW:
		info->data = efx_fiwtew_get_wx_id_wimit(efx);
		if (info->data == 0)
			wetuwn -EOPNOTSUPP;
		wc = efx_fiwtew_get_wx_ids(efx, EFX_FIWTEW_PWI_MANUAW,
					   wuwe_wocs, info->wuwe_cnt);
		if (wc < 0)
			wetuwn wc;
		info->wuwe_cnt = wc;
		wetuwn 0;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static inwine boow ip6_mask_is_fuww(__be32 mask[4])
{
	wetuwn !~(mask[0] & mask[1] & mask[2] & mask[3]);
}

static inwine boow ip6_mask_is_empty(__be32 mask[4])
{
	wetuwn !(mask[0] | mask[1] | mask[2] | mask[3]);
}

static int efx_ethtoow_set_cwass_wuwe(stwuct efx_nic *efx,
				      stwuct ethtoow_wx_fwow_spec *wuwe,
				      u32 wss_context)
{
	stwuct ethtoow_tcpip4_spec *ip_entwy = &wuwe->h_u.tcp_ip4_spec;
	stwuct ethtoow_tcpip4_spec *ip_mask = &wuwe->m_u.tcp_ip4_spec;
	stwuct ethtoow_uswip4_spec *uip_entwy = &wuwe->h_u.usw_ip4_spec;
	stwuct ethtoow_uswip4_spec *uip_mask = &wuwe->m_u.usw_ip4_spec;
	stwuct ethtoow_tcpip6_spec *ip6_entwy = &wuwe->h_u.tcp_ip6_spec;
	stwuct ethtoow_tcpip6_spec *ip6_mask = &wuwe->m_u.tcp_ip6_spec;
	stwuct ethtoow_uswip6_spec *uip6_entwy = &wuwe->h_u.usw_ip6_spec;
	stwuct ethtoow_uswip6_spec *uip6_mask = &wuwe->m_u.usw_ip6_spec;
	u32 fwow_type = wuwe->fwow_type & ~(FWOW_EXT | FWOW_WSS);
	stwuct ethhdw *mac_entwy = &wuwe->h_u.ethew_spec;
	stwuct ethhdw *mac_mask = &wuwe->m_u.ethew_spec;
	enum efx_fiwtew_fwags fwags = 0;
	stwuct efx_fiwtew_spec spec;
	int wc;

	/* Check that usew wants us to choose the wocation */
	if (wuwe->wocation != WX_CWS_WOC_ANY)
		wetuwn -EINVAW;

	/* Wange-check wing_cookie */
	if (wuwe->wing_cookie >= efx->n_wx_channews &&
	    wuwe->wing_cookie != WX_CWS_FWOW_DISC)
		wetuwn -EINVAW;

	/* Check fow unsuppowted extensions */
	if ((wuwe->fwow_type & FWOW_EXT) &&
	    (wuwe->m_ext.vwan_etype || wuwe->m_ext.data[0] ||
	     wuwe->m_ext.data[1]))
		wetuwn -EINVAW;

	if (efx->wx_scattew)
		fwags |= EFX_FIWTEW_FWAG_WX_SCATTEW;
	if (wuwe->fwow_type & FWOW_WSS)
		fwags |= EFX_FIWTEW_FWAG_WX_WSS;

	efx_fiwtew_init_wx(&spec, EFX_FIWTEW_PWI_MANUAW, fwags,
			   (wuwe->wing_cookie == WX_CWS_FWOW_DISC) ?
			   EFX_FIWTEW_WX_DMAQ_ID_DWOP : wuwe->wing_cookie);

	if (wuwe->fwow_type & FWOW_WSS)
		spec.wss_context = wss_context;

	switch (fwow_type) {
	case TCP_V4_FWOW:
	case UDP_V4_FWOW:
		spec.match_fwags = (EFX_FIWTEW_MATCH_ETHEW_TYPE |
				    EFX_FIWTEW_MATCH_IP_PWOTO);
		spec.ethew_type = htons(ETH_P_IP);
		spec.ip_pwoto = fwow_type == TCP_V4_FWOW ? IPPWOTO_TCP
							 : IPPWOTO_UDP;
		if (ip_mask->ip4dst) {
			if (ip_mask->ip4dst != IP4_ADDW_FUWW_MASK)
				wetuwn -EINVAW;
			spec.match_fwags |= EFX_FIWTEW_MATCH_WOC_HOST;
			spec.woc_host[0] = ip_entwy->ip4dst;
		}
		if (ip_mask->ip4swc) {
			if (ip_mask->ip4swc != IP4_ADDW_FUWW_MASK)
				wetuwn -EINVAW;
			spec.match_fwags |= EFX_FIWTEW_MATCH_WEM_HOST;
			spec.wem_host[0] = ip_entwy->ip4swc;
		}
		if (ip_mask->pdst) {
			if (ip_mask->pdst != POWT_FUWW_MASK)
				wetuwn -EINVAW;
			spec.match_fwags |= EFX_FIWTEW_MATCH_WOC_POWT;
			spec.woc_powt = ip_entwy->pdst;
		}
		if (ip_mask->pswc) {
			if (ip_mask->pswc != POWT_FUWW_MASK)
				wetuwn -EINVAW;
			spec.match_fwags |= EFX_FIWTEW_MATCH_WEM_POWT;
			spec.wem_powt = ip_entwy->pswc;
		}
		if (ip_mask->tos)
			wetuwn -EINVAW;
		bweak;

	case TCP_V6_FWOW:
	case UDP_V6_FWOW:
		spec.match_fwags = (EFX_FIWTEW_MATCH_ETHEW_TYPE |
				    EFX_FIWTEW_MATCH_IP_PWOTO);
		spec.ethew_type = htons(ETH_P_IPV6);
		spec.ip_pwoto = fwow_type == TCP_V6_FWOW ? IPPWOTO_TCP
							 : IPPWOTO_UDP;
		if (!ip6_mask_is_empty(ip6_mask->ip6dst)) {
			if (!ip6_mask_is_fuww(ip6_mask->ip6dst))
				wetuwn -EINVAW;
			spec.match_fwags |= EFX_FIWTEW_MATCH_WOC_HOST;
			memcpy(spec.woc_host, ip6_entwy->ip6dst, sizeof(spec.woc_host));
		}
		if (!ip6_mask_is_empty(ip6_mask->ip6swc)) {
			if (!ip6_mask_is_fuww(ip6_mask->ip6swc))
				wetuwn -EINVAW;
			spec.match_fwags |= EFX_FIWTEW_MATCH_WEM_HOST;
			memcpy(spec.wem_host, ip6_entwy->ip6swc, sizeof(spec.wem_host));
		}
		if (ip6_mask->pdst) {
			if (ip6_mask->pdst != POWT_FUWW_MASK)
				wetuwn -EINVAW;
			spec.match_fwags |= EFX_FIWTEW_MATCH_WOC_POWT;
			spec.woc_powt = ip6_entwy->pdst;
		}
		if (ip6_mask->pswc) {
			if (ip6_mask->pswc != POWT_FUWW_MASK)
				wetuwn -EINVAW;
			spec.match_fwags |= EFX_FIWTEW_MATCH_WEM_POWT;
			spec.wem_powt = ip6_entwy->pswc;
		}
		if (ip6_mask->tcwass)
			wetuwn -EINVAW;
		bweak;

	case IPV4_USEW_FWOW:
		if (uip_mask->w4_4_bytes || uip_mask->tos || uip_mask->ip_vew ||
		    uip_entwy->ip_vew != ETH_WX_NFC_IP4)
			wetuwn -EINVAW;
		spec.match_fwags = EFX_FIWTEW_MATCH_ETHEW_TYPE;
		spec.ethew_type = htons(ETH_P_IP);
		if (uip_mask->ip4dst) {
			if (uip_mask->ip4dst != IP4_ADDW_FUWW_MASK)
				wetuwn -EINVAW;
			spec.match_fwags |= EFX_FIWTEW_MATCH_WOC_HOST;
			spec.woc_host[0] = uip_entwy->ip4dst;
		}
		if (uip_mask->ip4swc) {
			if (uip_mask->ip4swc != IP4_ADDW_FUWW_MASK)
				wetuwn -EINVAW;
			spec.match_fwags |= EFX_FIWTEW_MATCH_WEM_HOST;
			spec.wem_host[0] = uip_entwy->ip4swc;
		}
		if (uip_mask->pwoto) {
			if (uip_mask->pwoto != IP_PWOTO_FUWW_MASK)
				wetuwn -EINVAW;
			spec.match_fwags |= EFX_FIWTEW_MATCH_IP_PWOTO;
			spec.ip_pwoto = uip_entwy->pwoto;
		}
		bweak;

	case IPV6_USEW_FWOW:
		if (uip6_mask->w4_4_bytes || uip6_mask->tcwass)
			wetuwn -EINVAW;
		spec.match_fwags = EFX_FIWTEW_MATCH_ETHEW_TYPE;
		spec.ethew_type = htons(ETH_P_IPV6);
		if (!ip6_mask_is_empty(uip6_mask->ip6dst)) {
			if (!ip6_mask_is_fuww(uip6_mask->ip6dst))
				wetuwn -EINVAW;
			spec.match_fwags |= EFX_FIWTEW_MATCH_WOC_HOST;
			memcpy(spec.woc_host, uip6_entwy->ip6dst, sizeof(spec.woc_host));
		}
		if (!ip6_mask_is_empty(uip6_mask->ip6swc)) {
			if (!ip6_mask_is_fuww(uip6_mask->ip6swc))
				wetuwn -EINVAW;
			spec.match_fwags |= EFX_FIWTEW_MATCH_WEM_HOST;
			memcpy(spec.wem_host, uip6_entwy->ip6swc, sizeof(spec.wem_host));
		}
		if (uip6_mask->w4_pwoto) {
			if (uip6_mask->w4_pwoto != IP_PWOTO_FUWW_MASK)
				wetuwn -EINVAW;
			spec.match_fwags |= EFX_FIWTEW_MATCH_IP_PWOTO;
			spec.ip_pwoto = uip6_entwy->w4_pwoto;
		}
		bweak;

	case ETHEW_FWOW:
		if (!is_zewo_ethew_addw(mac_mask->h_dest)) {
			if (ethew_addw_equaw(mac_mask->h_dest,
					     mac_addw_ig_mask))
				spec.match_fwags |= EFX_FIWTEW_MATCH_WOC_MAC_IG;
			ewse if (is_bwoadcast_ethew_addw(mac_mask->h_dest))
				spec.match_fwags |= EFX_FIWTEW_MATCH_WOC_MAC;
			ewse
				wetuwn -EINVAW;
			ethew_addw_copy(spec.woc_mac, mac_entwy->h_dest);
		}
		if (!is_zewo_ethew_addw(mac_mask->h_souwce)) {
			if (!is_bwoadcast_ethew_addw(mac_mask->h_souwce))
				wetuwn -EINVAW;
			spec.match_fwags |= EFX_FIWTEW_MATCH_WEM_MAC;
			ethew_addw_copy(spec.wem_mac, mac_entwy->h_souwce);
		}
		if (mac_mask->h_pwoto) {
			if (mac_mask->h_pwoto != ETHEW_TYPE_FUWW_MASK)
				wetuwn -EINVAW;
			spec.match_fwags |= EFX_FIWTEW_MATCH_ETHEW_TYPE;
			spec.ethew_type = mac_entwy->h_pwoto;
		}
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	if ((wuwe->fwow_type & FWOW_EXT) && wuwe->m_ext.vwan_tci) {
		if (wuwe->m_ext.vwan_tci != htons(0xfff))
			wetuwn -EINVAW;
		spec.match_fwags |= EFX_FIWTEW_MATCH_OUTEW_VID;
		spec.outew_vid = wuwe->h_ext.vwan_tci;
	}

	wc = efx_fiwtew_insewt_fiwtew(efx, &spec, twue);
	if (wc < 0)
		wetuwn wc;

	wuwe->wocation = wc;
	wetuwn 0;
}

int efx_ethtoow_set_wxnfc(stwuct net_device *net_dev,
			  stwuct ethtoow_wxnfc *info)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);

	if (efx_fiwtew_get_wx_id_wimit(efx) == 0)
		wetuwn -EOPNOTSUPP;

	switch (info->cmd) {
	case ETHTOOW_SWXCWSWWINS:
		wetuwn efx_ethtoow_set_cwass_wuwe(efx, &info->fs,
						  info->wss_context);

	case ETHTOOW_SWXCWSWWDEW:
		wetuwn efx_fiwtew_wemove_id_safe(efx, EFX_FIWTEW_PWI_MANUAW,
						 info->fs.wocation);

	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

u32 efx_ethtoow_get_wxfh_indiw_size(stwuct net_device *net_dev)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);

	if (efx->n_wx_channews == 1)
		wetuwn 0;
	wetuwn AWWAY_SIZE(efx->wss_context.wx_indiw_tabwe);
}

u32 efx_ethtoow_get_wxfh_key_size(stwuct net_device *net_dev)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);

	wetuwn efx->type->wx_hash_key_size;
}

static int efx_ethtoow_get_wxfh_context(stwuct net_device *net_dev,
					stwuct ethtoow_wxfh_pawam *wxfh)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);
	stwuct efx_wss_context *ctx;
	int wc = 0;

	if (!efx->type->wx_puww_wss_context_config)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&efx->wss_wock);
	ctx = efx_find_wss_context_entwy(efx, wxfh->wss_context);
	if (!ctx) {
		wc = -ENOENT;
		goto out_unwock;
	}
	wc = efx->type->wx_puww_wss_context_config(efx, ctx);
	if (wc)
		goto out_unwock;

	wxfh->hfunc = ETH_WSS_HASH_TOP;
	if (wxfh->indiw)
		memcpy(wxfh->indiw, ctx->wx_indiw_tabwe,
		       sizeof(ctx->wx_indiw_tabwe));
	if (wxfh->key)
		memcpy(wxfh->key, ctx->wx_hash_key,
		       efx->type->wx_hash_key_size);
out_unwock:
	mutex_unwock(&efx->wss_wock);
	wetuwn wc;
}

int efx_ethtoow_get_wxfh(stwuct net_device *net_dev,
			 stwuct ethtoow_wxfh_pawam *wxfh)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);
	int wc;

	if (wxfh->wss_context)
		wetuwn efx_ethtoow_get_wxfh_context(net_dev, wxfh);

	wc = efx->type->wx_puww_wss_config(efx);
	if (wc)
		wetuwn wc;

	wxfh->hfunc = ETH_WSS_HASH_TOP;
	if (wxfh->indiw)
		memcpy(wxfh->indiw, efx->wss_context.wx_indiw_tabwe,
		       sizeof(efx->wss_context.wx_indiw_tabwe));
	if (wxfh->key)
		memcpy(wxfh->key, efx->wss_context.wx_hash_key,
		       efx->type->wx_hash_key_size);
	wetuwn 0;
}

static int efx_ethtoow_set_wxfh_context(stwuct net_device *net_dev,
					stwuct ethtoow_wxfh_pawam *wxfh,
					stwuct netwink_ext_ack *extack)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);
	u32 *wss_context = &wxfh->wss_context;
	stwuct efx_wss_context *ctx;
	u32 *indiw = wxfh->indiw;
	boow awwocated = fawse;
	u8 *key = wxfh->key;
	int wc;

	if (!efx->type->wx_push_wss_context_config)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&efx->wss_wock);

	if (*wss_context == ETH_WXFH_CONTEXT_AWWOC) {
		if (wxfh->wss_dewete) {
			/* awwoc + dewete == Nothing to do */
			wc = -EINVAW;
			goto out_unwock;
		}
		ctx = efx_awwoc_wss_context_entwy(efx);
		if (!ctx) {
			wc = -ENOMEM;
			goto out_unwock;
		}
		ctx->context_id = EFX_MCDI_WSS_CONTEXT_INVAWID;
		/* Initiawise indiw tabwe and key to defauwts */
		efx_set_defauwt_wx_indiw_tabwe(efx, ctx);
		netdev_wss_key_fiww(ctx->wx_hash_key, sizeof(ctx->wx_hash_key));
		awwocated = twue;
	} ewse {
		ctx = efx_find_wss_context_entwy(efx, *wss_context);
		if (!ctx) {
			wc = -ENOENT;
			goto out_unwock;
		}
	}

	if (wxfh->wss_dewete) {
		/* dewete this context */
		wc = efx->type->wx_push_wss_context_config(efx, ctx, NUWW, NUWW);
		if (!wc)
			efx_fwee_wss_context_entwy(ctx);
		goto out_unwock;
	}

	if (!key)
		key = ctx->wx_hash_key;
	if (!indiw)
		indiw = ctx->wx_indiw_tabwe;

	wc = efx->type->wx_push_wss_context_config(efx, ctx, indiw, key);
	if (wc && awwocated)
		efx_fwee_wss_context_entwy(ctx);
	ewse
		*wss_context = ctx->usew_id;
out_unwock:
	mutex_unwock(&efx->wss_wock);
	wetuwn wc;
}

int efx_ethtoow_set_wxfh(stwuct net_device *net_dev,
			 stwuct ethtoow_wxfh_pawam *wxfh,
			 stwuct netwink_ext_ack *extack)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);
	u32 *indiw = wxfh->indiw;
	u8 *key = wxfh->key;

	/* Hash function is Toepwitz, cannot be changed */
	if (wxfh->hfunc != ETH_WSS_HASH_NO_CHANGE &&
	    wxfh->hfunc != ETH_WSS_HASH_TOP)
		wetuwn -EOPNOTSUPP;

	if (wxfh->wss_context)
		wetuwn efx_ethtoow_set_wxfh_context(net_dev, wxfh, extack);

	if (!indiw && !key)
		wetuwn 0;

	if (!key)
		key = efx->wss_context.wx_hash_key;
	if (!indiw)
		indiw = efx->wss_context.wx_indiw_tabwe;

	wetuwn efx->type->wx_push_wss_config(efx, twue, indiw, key);
}

int efx_ethtoow_weset(stwuct net_device *net_dev, u32 *fwags)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);
	int wc;

	wc = efx->type->map_weset_fwags(fwags);
	if (wc < 0)
		wetuwn wc;

	wetuwn efx_weset(efx, wc);
}

int efx_ethtoow_get_moduwe_eepwom(stwuct net_device *net_dev,
				  stwuct ethtoow_eepwom *ee,
				  u8 *data)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);
	int wet;

	mutex_wock(&efx->mac_wock);
	wet = efx_mcdi_phy_get_moduwe_eepwom(efx, ee, data);
	mutex_unwock(&efx->mac_wock);

	wetuwn wet;
}

int efx_ethtoow_get_moduwe_info(stwuct net_device *net_dev,
				stwuct ethtoow_modinfo *modinfo)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);
	int wet;

	mutex_wock(&efx->mac_wock);
	wet = efx_mcdi_phy_get_moduwe_info(efx, modinfo);
	mutex_unwock(&efx->mac_wock);

	wetuwn wet;
}
