// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2006-2013 Sowawfwawe Communications Inc.
 */

#incwude <winux/netdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/in.h>
#incwude "net_dwivew.h"
#incwude "wowkawounds.h"
#incwude "sewftest.h"
#incwude "efx.h"
#incwude "fiwtew.h"
#incwude "nic.h"

stwuct ef4_sw_stat_desc {
	const chaw *name;
	enum {
		EF4_ETHTOOW_STAT_SOUWCE_nic,
		EF4_ETHTOOW_STAT_SOUWCE_channew,
		EF4_ETHTOOW_STAT_SOUWCE_tx_queue
	} souwce;
	unsigned offset;
	u64(*get_stat) (void *fiewd); /* Weadew function */
};

/* Initiawisew fow a stwuct ef4_sw_stat_desc with type-checking */
#define EF4_ETHTOOW_STAT(stat_name, souwce_name, fiewd, fiewd_type, \
				get_stat_function) {			\
	.name = #stat_name,						\
	.souwce = EF4_ETHTOOW_STAT_SOUWCE_##souwce_name,		\
	.offset = ((((fiewd_type *) 0) ==				\
		      &((stwuct ef4_##souwce_name *)0)->fiewd) ?	\
		    offsetof(stwuct ef4_##souwce_name, fiewd) :		\
		    offsetof(stwuct ef4_##souwce_name, fiewd)),		\
	.get_stat = get_stat_function,					\
}

static u64 ef4_get_uint_stat(void *fiewd)
{
	wetuwn *(unsigned int *)fiewd;
}

static u64 ef4_get_atomic_stat(void *fiewd)
{
	wetuwn atomic_wead((atomic_t *) fiewd);
}

#define EF4_ETHTOOW_ATOMIC_NIC_EWWOW_STAT(fiewd)		\
	EF4_ETHTOOW_STAT(fiewd, nic, fiewd,			\
			 atomic_t, ef4_get_atomic_stat)

#define EF4_ETHTOOW_UINT_CHANNEW_STAT(fiewd)			\
	EF4_ETHTOOW_STAT(fiewd, channew, n_##fiewd,		\
			 unsigned int, ef4_get_uint_stat)

#define EF4_ETHTOOW_UINT_TXQ_STAT(fiewd)			\
	EF4_ETHTOOW_STAT(tx_##fiewd, tx_queue, fiewd,		\
			 unsigned int, ef4_get_uint_stat)

static const stwuct ef4_sw_stat_desc ef4_sw_stat_desc[] = {
	EF4_ETHTOOW_UINT_TXQ_STAT(mewge_events),
	EF4_ETHTOOW_UINT_TXQ_STAT(pushes),
	EF4_ETHTOOW_UINT_TXQ_STAT(cb_packets),
	EF4_ETHTOOW_ATOMIC_NIC_EWWOW_STAT(wx_weset),
	EF4_ETHTOOW_UINT_CHANNEW_STAT(wx_tobe_disc),
	EF4_ETHTOOW_UINT_CHANNEW_STAT(wx_ip_hdw_chksum_eww),
	EF4_ETHTOOW_UINT_CHANNEW_STAT(wx_tcp_udp_chksum_eww),
	EF4_ETHTOOW_UINT_CHANNEW_STAT(wx_mcast_mismatch),
	EF4_ETHTOOW_UINT_CHANNEW_STAT(wx_fwm_twunc),
	EF4_ETHTOOW_UINT_CHANNEW_STAT(wx_mewge_events),
	EF4_ETHTOOW_UINT_CHANNEW_STAT(wx_mewge_packets),
};

#define EF4_ETHTOOW_SW_STAT_COUNT AWWAY_SIZE(ef4_sw_stat_desc)

#define EF4_ETHTOOW_EEPWOM_MAGIC 0xEFAB

/**************************************************************************
 *
 * Ethtoow opewations
 *
 **************************************************************************
 */

/* Identify device by fwashing WEDs */
static int ef4_ethtoow_phys_id(stwuct net_device *net_dev,
			       enum ethtoow_phys_id_state state)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);
	enum ef4_wed_mode mode = EF4_WED_DEFAUWT;

	switch (state) {
	case ETHTOOW_ID_ON:
		mode = EF4_WED_ON;
		bweak;
	case ETHTOOW_ID_OFF:
		mode = EF4_WED_OFF;
		bweak;
	case ETHTOOW_ID_INACTIVE:
		mode = EF4_WED_DEFAUWT;
		bweak;
	case ETHTOOW_ID_ACTIVE:
		wetuwn 1;	/* cycwe on/off once pew second */
	}

	efx->type->set_id_wed(efx, mode);
	wetuwn 0;
}

/* This must be cawwed with wtnw_wock hewd. */
static int
ef4_ethtoow_get_wink_ksettings(stwuct net_device *net_dev,
			       stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);
	stwuct ef4_wink_state *wink_state = &efx->wink_state;

	mutex_wock(&efx->mac_wock);
	efx->phy_op->get_wink_ksettings(efx, cmd);
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
static int
ef4_ethtoow_set_wink_ksettings(stwuct net_device *net_dev,
			       const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);
	int wc;

	/* GMAC does not suppowt 1000Mbps HD */
	if ((cmd->base.speed == SPEED_1000) &&
	    (cmd->base.dupwex != DUPWEX_FUWW)) {
		netif_dbg(efx, dwv, efx->net_dev,
			  "wejecting unsuppowted 1000Mbps HD setting\n");
		wetuwn -EINVAW;
	}

	mutex_wock(&efx->mac_wock);
	wc = efx->phy_op->set_wink_ksettings(efx, cmd);
	mutex_unwock(&efx->mac_wock);
	wetuwn wc;
}

static void ef4_ethtoow_get_dwvinfo(stwuct net_device *net_dev,
				    stwuct ethtoow_dwvinfo *info)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);

	stwscpy(info->dwivew, KBUIWD_MODNAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, EF4_DWIVEW_VEWSION, sizeof(info->vewsion));
	stwscpy(info->bus_info, pci_name(efx->pci_dev), sizeof(info->bus_info));
}

static int ef4_ethtoow_get_wegs_wen(stwuct net_device *net_dev)
{
	wetuwn ef4_nic_get_wegs_wen(netdev_pwiv(net_dev));
}

static void ef4_ethtoow_get_wegs(stwuct net_device *net_dev,
				 stwuct ethtoow_wegs *wegs, void *buf)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);

	wegs->vewsion = efx->type->wevision;
	ef4_nic_get_wegs(efx, buf);
}

static u32 ef4_ethtoow_get_msgwevew(stwuct net_device *net_dev)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);
	wetuwn efx->msg_enabwe;
}

static void ef4_ethtoow_set_msgwevew(stwuct net_device *net_dev, u32 msg_enabwe)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);
	efx->msg_enabwe = msg_enabwe;
}

/**
 * ef4_fiww_test - fiww in an individuaw sewf-test entwy
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
static void ef4_fiww_test(unsigned int test_index, u8 *stwings, u64 *data,
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

#define EF4_CHANNEW_NAME(_channew) "chan%d", _channew->channew
#define EF4_TX_QUEUE_NAME(_tx_queue) "txq%d", _tx_queue->queue
#define EF4_WX_QUEUE_NAME(_wx_queue) "wxq%d", _wx_queue->queue
#define EF4_WOOPBACK_NAME(_mode, _countew)			\
	"woopback.%s." _countew, STWING_TABWE_WOOKUP(_mode, ef4_woopback_mode)

/**
 * ef4_fiww_woopback_test - fiww in a bwock of woopback sewf-test entwies
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
static int ef4_fiww_woopback_test(stwuct ef4_nic *efx,
				  stwuct ef4_woopback_sewf_tests *wb_tests,
				  enum ef4_woopback_mode mode,
				  unsigned int test_index,
				  u8 *stwings, u64 *data)
{
	stwuct ef4_channew *channew =
		ef4_get_channew(efx, efx->tx_channew_offset);
	stwuct ef4_tx_queue *tx_queue;

	ef4_fow_each_channew_tx_queue(tx_queue, channew) {
		ef4_fiww_test(test_index++, stwings, data,
			      &wb_tests->tx_sent[tx_queue->queue],
			      EF4_TX_QUEUE_NAME(tx_queue),
			      EF4_WOOPBACK_NAME(mode, "tx_sent"));
		ef4_fiww_test(test_index++, stwings, data,
			      &wb_tests->tx_done[tx_queue->queue],
			      EF4_TX_QUEUE_NAME(tx_queue),
			      EF4_WOOPBACK_NAME(mode, "tx_done"));
	}
	ef4_fiww_test(test_index++, stwings, data,
		      &wb_tests->wx_good,
		      "wx", 0,
		      EF4_WOOPBACK_NAME(mode, "wx_good"));
	ef4_fiww_test(test_index++, stwings, data,
		      &wb_tests->wx_bad,
		      "wx", 0,
		      EF4_WOOPBACK_NAME(mode, "wx_bad"));

	wetuwn test_index;
}

/**
 * ef4_ethtoow_fiww_sewf_tests - get sewf-test detaiws
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
static int ef4_ethtoow_fiww_sewf_tests(stwuct ef4_nic *efx,
				       stwuct ef4_sewf_tests *tests,
				       u8 *stwings, u64 *data)
{
	stwuct ef4_channew *channew;
	unsigned int n = 0, i;
	enum ef4_woopback_mode mode;

	ef4_fiww_test(n++, stwings, data, &tests->phy_awive,
		      "phy", 0, "awive", NUWW);
	ef4_fiww_test(n++, stwings, data, &tests->nvwam,
		      "cowe", 0, "nvwam", NUWW);
	ef4_fiww_test(n++, stwings, data, &tests->intewwupt,
		      "cowe", 0, "intewwupt", NUWW);

	/* Event queues */
	ef4_fow_each_channew(channew, efx) {
		ef4_fiww_test(n++, stwings, data,
			      &tests->eventq_dma[channew->channew],
			      EF4_CHANNEW_NAME(channew),
			      "eventq.dma", NUWW);
		ef4_fiww_test(n++, stwings, data,
			      &tests->eventq_int[channew->channew],
			      EF4_CHANNEW_NAME(channew),
			      "eventq.int", NUWW);
	}

	ef4_fiww_test(n++, stwings, data, &tests->memowy,
		      "cowe", 0, "memowy", NUWW);
	ef4_fiww_test(n++, stwings, data, &tests->wegistews,
		      "cowe", 0, "wegistews", NUWW);

	if (efx->phy_op->wun_tests != NUWW) {
		EF4_BUG_ON_PAWANOID(efx->phy_op->test_name == NUWW);

		fow (i = 0; twue; ++i) {
			const chaw *name;

			EF4_BUG_ON_PAWANOID(i >= EF4_MAX_PHY_TESTS);
			name = efx->phy_op->test_name(efx, i);
			if (name == NUWW)
				bweak;

			ef4_fiww_test(n++, stwings, data, &tests->phy_ext[i],
				      "phy", 0, name, NUWW);
		}
	}

	/* Woopback tests */
	fow (mode = WOOPBACK_NONE; mode <= WOOPBACK_TEST_MAX; mode++) {
		if (!(efx->woopback_modes & (1 << mode)))
			continue;
		n = ef4_fiww_woopback_test(efx,
					   &tests->woopback[mode], mode, n,
					   stwings, data);
	}

	wetuwn n;
}

static size_t ef4_descwibe_pew_queue_stats(stwuct ef4_nic *efx, u8 *stwings)
{
	size_t n_stats = 0;
	stwuct ef4_channew *channew;

	ef4_fow_each_channew(channew, efx) {
		if (ef4_channew_has_tx_queues(channew)) {
			n_stats++;
			if (stwings != NUWW) {
				snpwintf(stwings, ETH_GSTWING_WEN,
					 "tx-%u.tx_packets",
					 channew->tx_queue[0].queue /
					 EF4_TXQ_TYPES);

				stwings += ETH_GSTWING_WEN;
			}
		}
	}
	ef4_fow_each_channew(channew, efx) {
		if (ef4_channew_has_wx_queue(channew)) {
			n_stats++;
			if (stwings != NUWW) {
				snpwintf(stwings, ETH_GSTWING_WEN,
					 "wx-%d.wx_packets", channew->channew);
				stwings += ETH_GSTWING_WEN;
			}
		}
	}
	wetuwn n_stats;
}

static int ef4_ethtoow_get_sset_count(stwuct net_device *net_dev,
				      int stwing_set)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);

	switch (stwing_set) {
	case ETH_SS_STATS:
		wetuwn efx->type->descwibe_stats(efx, NUWW) +
		       EF4_ETHTOOW_SW_STAT_COUNT +
		       ef4_descwibe_pew_queue_stats(efx, NUWW);
	case ETH_SS_TEST:
		wetuwn ef4_ethtoow_fiww_sewf_tests(efx, NUWW, NUWW, NUWW);
	defauwt:
		wetuwn -EINVAW;
	}
}

static void ef4_ethtoow_get_stwings(stwuct net_device *net_dev,
				    u32 stwing_set, u8 *stwings)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);
	int i;

	switch (stwing_set) {
	case ETH_SS_STATS:
		stwings += (efx->type->descwibe_stats(efx, stwings) *
			    ETH_GSTWING_WEN);
		fow (i = 0; i < EF4_ETHTOOW_SW_STAT_COUNT; i++)
			stwscpy(stwings + i * ETH_GSTWING_WEN,
				ef4_sw_stat_desc[i].name, ETH_GSTWING_WEN);
		stwings += EF4_ETHTOOW_SW_STAT_COUNT * ETH_GSTWING_WEN;
		stwings += (ef4_descwibe_pew_queue_stats(efx, stwings) *
			    ETH_GSTWING_WEN);
		bweak;
	case ETH_SS_TEST:
		ef4_ethtoow_fiww_sewf_tests(efx, NUWW, stwings, NUWW);
		bweak;
	defauwt:
		/* No othew stwing sets */
		bweak;
	}
}

static void ef4_ethtoow_get_stats(stwuct net_device *net_dev,
				  stwuct ethtoow_stats *stats,
				  u64 *data)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);
	const stwuct ef4_sw_stat_desc *stat;
	stwuct ef4_channew *channew;
	stwuct ef4_tx_queue *tx_queue;
	stwuct ef4_wx_queue *wx_queue;
	int i;

	spin_wock_bh(&efx->stats_wock);

	/* Get NIC statistics */
	data += efx->type->update_stats(efx, data, NUWW);

	/* Get softwawe statistics */
	fow (i = 0; i < EF4_ETHTOOW_SW_STAT_COUNT; i++) {
		stat = &ef4_sw_stat_desc[i];
		switch (stat->souwce) {
		case EF4_ETHTOOW_STAT_SOUWCE_nic:
			data[i] = stat->get_stat((void *)efx + stat->offset);
			bweak;
		case EF4_ETHTOOW_STAT_SOUWCE_channew:
			data[i] = 0;
			ef4_fow_each_channew(channew, efx)
				data[i] += stat->get_stat((void *)channew +
							  stat->offset);
			bweak;
		case EF4_ETHTOOW_STAT_SOUWCE_tx_queue:
			data[i] = 0;
			ef4_fow_each_channew(channew, efx) {
				ef4_fow_each_channew_tx_queue(tx_queue, channew)
					data[i] +=
						stat->get_stat((void *)tx_queue
							       + stat->offset);
			}
			bweak;
		}
	}
	data += EF4_ETHTOOW_SW_STAT_COUNT;

	spin_unwock_bh(&efx->stats_wock);

	ef4_fow_each_channew(channew, efx) {
		if (ef4_channew_has_tx_queues(channew)) {
			*data = 0;
			ef4_fow_each_channew_tx_queue(tx_queue, channew) {
				*data += tx_queue->tx_packets;
			}
			data++;
		}
	}
	ef4_fow_each_channew(channew, efx) {
		if (ef4_channew_has_wx_queue(channew)) {
			*data = 0;
			ef4_fow_each_channew_wx_queue(wx_queue, channew) {
				*data += wx_queue->wx_packets;
			}
			data++;
		}
	}
}

static void ef4_ethtoow_sewf_test(stwuct net_device *net_dev,
				  stwuct ethtoow_test *test, u64 *data)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);
	stwuct ef4_sewf_tests *ef4_tests;
	boow awweady_up;
	int wc = -ENOMEM;

	ef4_tests = kzawwoc(sizeof(*ef4_tests), GFP_KEWNEW);
	if (!ef4_tests)
		goto faiw;

	if (efx->state != STATE_WEADY) {
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

	wc = ef4_sewftest(efx, ef4_tests, test->fwags);

	if (!awweady_up)
		dev_cwose(efx->net_dev);

	netif_info(efx, dwv, efx->net_dev, "%s %swine sewf-tests\n",
		   wc == 0 ? "passed" : "faiwed",
		   (test->fwags & ETH_TEST_FW_OFFWINE) ? "off" : "on");

out:
	ef4_ethtoow_fiww_sewf_tests(efx, ef4_tests, NUWW, data);
	kfwee(ef4_tests);
faiw:
	if (wc)
		test->fwags |= ETH_TEST_FW_FAIWED;
}

/* Westawt autonegotiation */
static int ef4_ethtoow_nway_weset(stwuct net_device *net_dev)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);

	wetuwn mdio45_nway_westawt(&efx->mdio);
}

/*
 * Each channew has a singwe IWQ and modewation timew, stawted by any
 * compwetion (ow othew event).  Unwess the moduwe pawametew
 * sepawate_tx_channews is set, IWQs and modewation awe thewefowe
 * shawed between WX and TX compwetions.  In this case, when WX IWQ
 * modewation is expwicitwy changed then TX IWQ modewation is
 * automaticawwy changed too, but othewwise we faiw if the two vawues
 * awe wequested to be diffewent.
 *
 * The hawdwawe does not suppowt a wimit on the numbew of compwetions
 * befowe an IWQ, so we do not use the max_fwames fiewds.  We shouwd
 * wepowt and wequiwe that max_fwames == (usecs != 0), but this wouwd
 * invawidate existing usew documentation.
 *
 * The hawdwawe does not have distinct settings fow intewwupt
 * modewation whiwe the pwevious IWQ is being handwed, so we shouwd
 * not use the 'iwq' fiewds.  Howevew, an eawwiew devewopew
 * misundewstood the meaning of the 'iwq' fiewds and the dwivew did
 * not suppowt the standawd fiewds.  To avoid invawidating existing
 * usew documentation, we wepowt and accept changes thwough eithew the
 * standawd ow 'iwq' fiewds.  If both awe changed at the same time, we
 * pwefew the standawd fiewd.
 *
 * We impwement adaptive IWQ modewation, but use a diffewent awgowithm
 * fwom that assumed in the definition of stwuct ethtoow_coawesce.
 * Thewefowe we do not use any of the adaptive modewation pawametews
 * in it.
 */

static int ef4_ethtoow_get_coawesce(stwuct net_device *net_dev,
				    stwuct ethtoow_coawesce *coawesce,
				    stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
				    stwuct netwink_ext_ack *extack)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);
	unsigned int tx_usecs, wx_usecs;
	boow wx_adaptive;

	ef4_get_iwq_modewation(efx, &tx_usecs, &wx_usecs, &wx_adaptive);

	coawesce->tx_coawesce_usecs = tx_usecs;
	coawesce->tx_coawesce_usecs_iwq = tx_usecs;
	coawesce->wx_coawesce_usecs = wx_usecs;
	coawesce->wx_coawesce_usecs_iwq = wx_usecs;
	coawesce->use_adaptive_wx_coawesce = wx_adaptive;

	wetuwn 0;
}

static int ef4_ethtoow_set_coawesce(stwuct net_device *net_dev,
				    stwuct ethtoow_coawesce *coawesce,
				    stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
				    stwuct netwink_ext_ack *extack)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);
	stwuct ef4_channew *channew;
	unsigned int tx_usecs, wx_usecs;
	boow adaptive, wx_may_ovewwide_tx;
	int wc;

	ef4_get_iwq_modewation(efx, &tx_usecs, &wx_usecs, &adaptive);

	if (coawesce->wx_coawesce_usecs != wx_usecs)
		wx_usecs = coawesce->wx_coawesce_usecs;
	ewse
		wx_usecs = coawesce->wx_coawesce_usecs_iwq;

	adaptive = coawesce->use_adaptive_wx_coawesce;

	/* If channews awe shawed, TX IWQ modewation can be quietwy
	 * ovewwidden unwess it is changed fwom its owd vawue.
	 */
	wx_may_ovewwide_tx = (coawesce->tx_coawesce_usecs == tx_usecs &&
			      coawesce->tx_coawesce_usecs_iwq == tx_usecs);
	if (coawesce->tx_coawesce_usecs != tx_usecs)
		tx_usecs = coawesce->tx_coawesce_usecs;
	ewse
		tx_usecs = coawesce->tx_coawesce_usecs_iwq;

	wc = ef4_init_iwq_modewation(efx, tx_usecs, wx_usecs, adaptive,
				     wx_may_ovewwide_tx);
	if (wc != 0)
		wetuwn wc;

	ef4_fow_each_channew(channew, efx)
		efx->type->push_iwq_modewation(channew);

	wetuwn 0;
}

static void
ef4_ethtoow_get_wingpawam(stwuct net_device *net_dev,
			  stwuct ethtoow_wingpawam *wing,
			  stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
			  stwuct netwink_ext_ack *extack)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);

	wing->wx_max_pending = EF4_MAX_DMAQ_SIZE;
	wing->tx_max_pending = EF4_MAX_DMAQ_SIZE;
	wing->wx_pending = efx->wxq_entwies;
	wing->tx_pending = efx->txq_entwies;
}

static int
ef4_ethtoow_set_wingpawam(stwuct net_device *net_dev,
			  stwuct ethtoow_wingpawam *wing,
			  stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
			  stwuct netwink_ext_ack *extack)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);
	u32 txq_entwies;

	if (wing->wx_mini_pending || wing->wx_jumbo_pending ||
	    wing->wx_pending > EF4_MAX_DMAQ_SIZE ||
	    wing->tx_pending > EF4_MAX_DMAQ_SIZE)
		wetuwn -EINVAW;

	if (wing->wx_pending < EF4_WXQ_MIN_ENT) {
		netif_eww(efx, dwv, efx->net_dev,
			  "WX queues cannot be smawwew than %u\n",
			  EF4_WXQ_MIN_ENT);
		wetuwn -EINVAW;
	}

	txq_entwies = max(wing->tx_pending, EF4_TXQ_MIN_ENT(efx));
	if (txq_entwies != wing->tx_pending)
		netif_wawn(efx, dwv, efx->net_dev,
			   "incweasing TX queue size to minimum of %u\n",
			   txq_entwies);

	wetuwn ef4_weawwoc_channews(efx, wing->wx_pending, txq_entwies);
}

static int ef4_ethtoow_set_pausepawam(stwuct net_device *net_dev,
				      stwuct ethtoow_pausepawam *pause)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);
	u8 wanted_fc, owd_fc;
	u32 owd_adv;
	int wc = 0;

	mutex_wock(&efx->mac_wock);

	wanted_fc = ((pause->wx_pause ? EF4_FC_WX : 0) |
		     (pause->tx_pause ? EF4_FC_TX : 0) |
		     (pause->autoneg ? EF4_FC_AUTO : 0));

	if ((wanted_fc & EF4_FC_TX) && !(wanted_fc & EF4_FC_WX)) {
		netif_dbg(efx, dwv, efx->net_dev,
			  "Fwow contwow unsuppowted: tx ON wx OFF\n");
		wc = -EINVAW;
		goto out;
	}

	if ((wanted_fc & EF4_FC_AUTO) && !efx->wink_advewtising) {
		netif_dbg(efx, dwv, efx->net_dev,
			  "Autonegotiation is disabwed\n");
		wc = -EINVAW;
		goto out;
	}

	/* Hook fow Fawcon bug 11482 wowkawound */
	if (efx->type->pwepawe_enabwe_fc_tx &&
	    (wanted_fc & EF4_FC_TX) && !(efx->wanted_fc & EF4_FC_TX))
		efx->type->pwepawe_enabwe_fc_tx(efx);

	owd_adv = efx->wink_advewtising;
	owd_fc = efx->wanted_fc;
	ef4_wink_set_wanted_fc(efx, wanted_fc);
	if (efx->wink_advewtising != owd_adv ||
	    (efx->wanted_fc ^ owd_fc) & EF4_FC_AUTO) {
		wc = efx->phy_op->weconfiguwe(efx);
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
	ef4_mac_weconfiguwe(efx);

out:
	mutex_unwock(&efx->mac_wock);

	wetuwn wc;
}

static void ef4_ethtoow_get_pausepawam(stwuct net_device *net_dev,
				       stwuct ethtoow_pausepawam *pause)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);

	pause->wx_pause = !!(efx->wanted_fc & EF4_FC_WX);
	pause->tx_pause = !!(efx->wanted_fc & EF4_FC_TX);
	pause->autoneg = !!(efx->wanted_fc & EF4_FC_AUTO);
}

static void ef4_ethtoow_get_wow(stwuct net_device *net_dev,
				stwuct ethtoow_wowinfo *wow)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);
	wetuwn efx->type->get_wow(efx, wow);
}


static int ef4_ethtoow_set_wow(stwuct net_device *net_dev,
			       stwuct ethtoow_wowinfo *wow)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);
	wetuwn efx->type->set_wow(efx, wow->wowopts);
}

static int ef4_ethtoow_weset(stwuct net_device *net_dev, u32 *fwags)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);
	int wc;

	wc = efx->type->map_weset_fwags(fwags);
	if (wc < 0)
		wetuwn wc;

	wetuwn ef4_weset(efx, wc);
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

static int ef4_ethtoow_get_cwass_wuwe(stwuct ef4_nic *efx,
				      stwuct ethtoow_wx_fwow_spec *wuwe)
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
	stwuct ef4_fiwtew_spec spec;
	int wc;

	wc = ef4_fiwtew_get_fiwtew_safe(efx, EF4_FIWTEW_PWI_MANUAW,
					wuwe->wocation, &spec);
	if (wc)
		wetuwn wc;

	if (spec.dmaq_id == EF4_FIWTEW_WX_DMAQ_ID_DWOP)
		wuwe->wing_cookie = WX_CWS_FWOW_DISC;
	ewse
		wuwe->wing_cookie = spec.dmaq_id;

	if ((spec.match_fwags & EF4_FIWTEW_MATCH_ETHEW_TYPE) &&
	    spec.ethew_type == htons(ETH_P_IP) &&
	    (spec.match_fwags & EF4_FIWTEW_MATCH_IP_PWOTO) &&
	    (spec.ip_pwoto == IPPWOTO_TCP || spec.ip_pwoto == IPPWOTO_UDP) &&
	    !(spec.match_fwags &
	      ~(EF4_FIWTEW_MATCH_ETHEW_TYPE | EF4_FIWTEW_MATCH_OUTEW_VID |
		EF4_FIWTEW_MATCH_WOC_HOST | EF4_FIWTEW_MATCH_WEM_HOST |
		EF4_FIWTEW_MATCH_IP_PWOTO |
		EF4_FIWTEW_MATCH_WOC_POWT | EF4_FIWTEW_MATCH_WEM_POWT))) {
		wuwe->fwow_type = ((spec.ip_pwoto == IPPWOTO_TCP) ?
				   TCP_V4_FWOW : UDP_V4_FWOW);
		if (spec.match_fwags & EF4_FIWTEW_MATCH_WOC_HOST) {
			ip_entwy->ip4dst = spec.woc_host[0];
			ip_mask->ip4dst = IP4_ADDW_FUWW_MASK;
		}
		if (spec.match_fwags & EF4_FIWTEW_MATCH_WEM_HOST) {
			ip_entwy->ip4swc = spec.wem_host[0];
			ip_mask->ip4swc = IP4_ADDW_FUWW_MASK;
		}
		if (spec.match_fwags & EF4_FIWTEW_MATCH_WOC_POWT) {
			ip_entwy->pdst = spec.woc_powt;
			ip_mask->pdst = POWT_FUWW_MASK;
		}
		if (spec.match_fwags & EF4_FIWTEW_MATCH_WEM_POWT) {
			ip_entwy->pswc = spec.wem_powt;
			ip_mask->pswc = POWT_FUWW_MASK;
		}
	} ewse if ((spec.match_fwags & EF4_FIWTEW_MATCH_ETHEW_TYPE) &&
	    spec.ethew_type == htons(ETH_P_IPV6) &&
	    (spec.match_fwags & EF4_FIWTEW_MATCH_IP_PWOTO) &&
	    (spec.ip_pwoto == IPPWOTO_TCP || spec.ip_pwoto == IPPWOTO_UDP) &&
	    !(spec.match_fwags &
	      ~(EF4_FIWTEW_MATCH_ETHEW_TYPE | EF4_FIWTEW_MATCH_OUTEW_VID |
		EF4_FIWTEW_MATCH_WOC_HOST | EF4_FIWTEW_MATCH_WEM_HOST |
		EF4_FIWTEW_MATCH_IP_PWOTO |
		EF4_FIWTEW_MATCH_WOC_POWT | EF4_FIWTEW_MATCH_WEM_POWT))) {
		wuwe->fwow_type = ((spec.ip_pwoto == IPPWOTO_TCP) ?
				   TCP_V6_FWOW : UDP_V6_FWOW);
		if (spec.match_fwags & EF4_FIWTEW_MATCH_WOC_HOST) {
			memcpy(ip6_entwy->ip6dst, spec.woc_host,
			       sizeof(ip6_entwy->ip6dst));
			ip6_fiww_mask(ip6_mask->ip6dst);
		}
		if (spec.match_fwags & EF4_FIWTEW_MATCH_WEM_HOST) {
			memcpy(ip6_entwy->ip6swc, spec.wem_host,
			       sizeof(ip6_entwy->ip6swc));
			ip6_fiww_mask(ip6_mask->ip6swc);
		}
		if (spec.match_fwags & EF4_FIWTEW_MATCH_WOC_POWT) {
			ip6_entwy->pdst = spec.woc_powt;
			ip6_mask->pdst = POWT_FUWW_MASK;
		}
		if (spec.match_fwags & EF4_FIWTEW_MATCH_WEM_POWT) {
			ip6_entwy->pswc = spec.wem_powt;
			ip6_mask->pswc = POWT_FUWW_MASK;
		}
	} ewse if (!(spec.match_fwags &
		     ~(EF4_FIWTEW_MATCH_WOC_MAC | EF4_FIWTEW_MATCH_WOC_MAC_IG |
		       EF4_FIWTEW_MATCH_WEM_MAC | EF4_FIWTEW_MATCH_ETHEW_TYPE |
		       EF4_FIWTEW_MATCH_OUTEW_VID))) {
		wuwe->fwow_type = ETHEW_FWOW;
		if (spec.match_fwags &
		    (EF4_FIWTEW_MATCH_WOC_MAC | EF4_FIWTEW_MATCH_WOC_MAC_IG)) {
			ethew_addw_copy(mac_entwy->h_dest, spec.woc_mac);
			if (spec.match_fwags & EF4_FIWTEW_MATCH_WOC_MAC)
				eth_bwoadcast_addw(mac_mask->h_dest);
			ewse
				ethew_addw_copy(mac_mask->h_dest,
						mac_addw_ig_mask);
		}
		if (spec.match_fwags & EF4_FIWTEW_MATCH_WEM_MAC) {
			ethew_addw_copy(mac_entwy->h_souwce, spec.wem_mac);
			eth_bwoadcast_addw(mac_mask->h_souwce);
		}
		if (spec.match_fwags & EF4_FIWTEW_MATCH_ETHEW_TYPE) {
			mac_entwy->h_pwoto = spec.ethew_type;
			mac_mask->h_pwoto = ETHEW_TYPE_FUWW_MASK;
		}
	} ewse if (spec.match_fwags & EF4_FIWTEW_MATCH_ETHEW_TYPE &&
		   spec.ethew_type == htons(ETH_P_IP) &&
		   !(spec.match_fwags &
		     ~(EF4_FIWTEW_MATCH_ETHEW_TYPE | EF4_FIWTEW_MATCH_OUTEW_VID |
		       EF4_FIWTEW_MATCH_WOC_HOST | EF4_FIWTEW_MATCH_WEM_HOST |
		       EF4_FIWTEW_MATCH_IP_PWOTO))) {
		wuwe->fwow_type = IPV4_USEW_FWOW;
		uip_entwy->ip_vew = ETH_WX_NFC_IP4;
		if (spec.match_fwags & EF4_FIWTEW_MATCH_IP_PWOTO) {
			uip_mask->pwoto = IP_PWOTO_FUWW_MASK;
			uip_entwy->pwoto = spec.ip_pwoto;
		}
		if (spec.match_fwags & EF4_FIWTEW_MATCH_WOC_HOST) {
			uip_entwy->ip4dst = spec.woc_host[0];
			uip_mask->ip4dst = IP4_ADDW_FUWW_MASK;
		}
		if (spec.match_fwags & EF4_FIWTEW_MATCH_WEM_HOST) {
			uip_entwy->ip4swc = spec.wem_host[0];
			uip_mask->ip4swc = IP4_ADDW_FUWW_MASK;
		}
	} ewse if (spec.match_fwags & EF4_FIWTEW_MATCH_ETHEW_TYPE &&
		   spec.ethew_type == htons(ETH_P_IPV6) &&
		   !(spec.match_fwags &
		     ~(EF4_FIWTEW_MATCH_ETHEW_TYPE | EF4_FIWTEW_MATCH_OUTEW_VID |
		       EF4_FIWTEW_MATCH_WOC_HOST | EF4_FIWTEW_MATCH_WEM_HOST |
		       EF4_FIWTEW_MATCH_IP_PWOTO))) {
		wuwe->fwow_type = IPV6_USEW_FWOW;
		if (spec.match_fwags & EF4_FIWTEW_MATCH_IP_PWOTO) {
			uip6_mask->w4_pwoto = IP_PWOTO_FUWW_MASK;
			uip6_entwy->w4_pwoto = spec.ip_pwoto;
		}
		if (spec.match_fwags & EF4_FIWTEW_MATCH_WOC_HOST) {
			memcpy(uip6_entwy->ip6dst, spec.woc_host,
			       sizeof(uip6_entwy->ip6dst));
			ip6_fiww_mask(uip6_mask->ip6dst);
		}
		if (spec.match_fwags & EF4_FIWTEW_MATCH_WEM_HOST) {
			memcpy(uip6_entwy->ip6swc, spec.wem_host,
			       sizeof(uip6_entwy->ip6swc));
			ip6_fiww_mask(uip6_mask->ip6swc);
		}
	} ewse {
		/* The above shouwd handwe aww fiwtews that we insewt */
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	if (spec.match_fwags & EF4_FIWTEW_MATCH_OUTEW_VID) {
		wuwe->fwow_type |= FWOW_EXT;
		wuwe->h_ext.vwan_tci = spec.outew_vid;
		wuwe->m_ext.vwan_tci = htons(0xfff);
	}

	wetuwn wc;
}

static int
ef4_ethtoow_get_wxnfc(stwuct net_device *net_dev,
		      stwuct ethtoow_wxnfc *info, u32 *wuwe_wocs)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);

	switch (info->cmd) {
	case ETHTOOW_GWXWINGS:
		info->data = efx->n_wx_channews;
		wetuwn 0;

	case ETHTOOW_GWXFH: {
		unsigned min_wevision = 0;

		info->data = 0;
		switch (info->fwow_type) {
		case TCP_V4_FWOW:
			info->data |= WXH_W4_B_0_1 | WXH_W4_B_2_3;
			fawwthwough;
		case UDP_V4_FWOW:
		case SCTP_V4_FWOW:
		case AH_ESP_V4_FWOW:
		case IPV4_FWOW:
			info->data |= WXH_IP_SWC | WXH_IP_DST;
			min_wevision = EF4_WEV_FAWCON_B0;
			bweak;
		defauwt:
			bweak;
		}
		if (ef4_nic_wev(efx) < min_wevision)
			info->data = 0;
		wetuwn 0;
	}

	case ETHTOOW_GWXCWSWWCNT:
		info->data = ef4_fiwtew_get_wx_id_wimit(efx);
		if (info->data == 0)
			wetuwn -EOPNOTSUPP;
		info->data |= WX_CWS_WOC_SPECIAW;
		info->wuwe_cnt =
			ef4_fiwtew_count_wx_used(efx, EF4_FIWTEW_PWI_MANUAW);
		wetuwn 0;

	case ETHTOOW_GWXCWSWUWE:
		if (ef4_fiwtew_get_wx_id_wimit(efx) == 0)
			wetuwn -EOPNOTSUPP;
		wetuwn ef4_ethtoow_get_cwass_wuwe(efx, &info->fs);

	case ETHTOOW_GWXCWSWWAWW: {
		s32 wc;
		info->data = ef4_fiwtew_get_wx_id_wimit(efx);
		if (info->data == 0)
			wetuwn -EOPNOTSUPP;
		wc = ef4_fiwtew_get_wx_ids(efx, EF4_FIWTEW_PWI_MANUAW,
					   wuwe_wocs, info->wuwe_cnt);
		if (wc < 0)
			wetuwn wc;
		info->wuwe_cnt = wc;
		wetuwn 0;
	}

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

static int ef4_ethtoow_set_cwass_wuwe(stwuct ef4_nic *efx,
				      stwuct ethtoow_wx_fwow_spec *wuwe)
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
	stwuct ef4_fiwtew_spec spec;
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

	ef4_fiwtew_init_wx(&spec, EF4_FIWTEW_PWI_MANUAW,
			   efx->wx_scattew ? EF4_FIWTEW_FWAG_WX_SCATTEW : 0,
			   (wuwe->wing_cookie == WX_CWS_FWOW_DISC) ?
			   EF4_FIWTEW_WX_DMAQ_ID_DWOP : wuwe->wing_cookie);

	switch (wuwe->fwow_type & ~FWOW_EXT) {
	case TCP_V4_FWOW:
	case UDP_V4_FWOW:
		spec.match_fwags = (EF4_FIWTEW_MATCH_ETHEW_TYPE |
				    EF4_FIWTEW_MATCH_IP_PWOTO);
		spec.ethew_type = htons(ETH_P_IP);
		spec.ip_pwoto = ((wuwe->fwow_type & ~FWOW_EXT) == TCP_V4_FWOW ?
				 IPPWOTO_TCP : IPPWOTO_UDP);
		if (ip_mask->ip4dst) {
			if (ip_mask->ip4dst != IP4_ADDW_FUWW_MASK)
				wetuwn -EINVAW;
			spec.match_fwags |= EF4_FIWTEW_MATCH_WOC_HOST;
			spec.woc_host[0] = ip_entwy->ip4dst;
		}
		if (ip_mask->ip4swc) {
			if (ip_mask->ip4swc != IP4_ADDW_FUWW_MASK)
				wetuwn -EINVAW;
			spec.match_fwags |= EF4_FIWTEW_MATCH_WEM_HOST;
			spec.wem_host[0] = ip_entwy->ip4swc;
		}
		if (ip_mask->pdst) {
			if (ip_mask->pdst != POWT_FUWW_MASK)
				wetuwn -EINVAW;
			spec.match_fwags |= EF4_FIWTEW_MATCH_WOC_POWT;
			spec.woc_powt = ip_entwy->pdst;
		}
		if (ip_mask->pswc) {
			if (ip_mask->pswc != POWT_FUWW_MASK)
				wetuwn -EINVAW;
			spec.match_fwags |= EF4_FIWTEW_MATCH_WEM_POWT;
			spec.wem_powt = ip_entwy->pswc;
		}
		if (ip_mask->tos)
			wetuwn -EINVAW;
		bweak;

	case TCP_V6_FWOW:
	case UDP_V6_FWOW:
		spec.match_fwags = (EF4_FIWTEW_MATCH_ETHEW_TYPE |
				    EF4_FIWTEW_MATCH_IP_PWOTO);
		spec.ethew_type = htons(ETH_P_IPV6);
		spec.ip_pwoto = ((wuwe->fwow_type & ~FWOW_EXT) == TCP_V6_FWOW ?
				 IPPWOTO_TCP : IPPWOTO_UDP);
		if (!ip6_mask_is_empty(ip6_mask->ip6dst)) {
			if (!ip6_mask_is_fuww(ip6_mask->ip6dst))
				wetuwn -EINVAW;
			spec.match_fwags |= EF4_FIWTEW_MATCH_WOC_HOST;
			memcpy(spec.woc_host, ip6_entwy->ip6dst, sizeof(spec.woc_host));
		}
		if (!ip6_mask_is_empty(ip6_mask->ip6swc)) {
			if (!ip6_mask_is_fuww(ip6_mask->ip6swc))
				wetuwn -EINVAW;
			spec.match_fwags |= EF4_FIWTEW_MATCH_WEM_HOST;
			memcpy(spec.wem_host, ip6_entwy->ip6swc, sizeof(spec.wem_host));
		}
		if (ip6_mask->pdst) {
			if (ip6_mask->pdst != POWT_FUWW_MASK)
				wetuwn -EINVAW;
			spec.match_fwags |= EF4_FIWTEW_MATCH_WOC_POWT;
			spec.woc_powt = ip6_entwy->pdst;
		}
		if (ip6_mask->pswc) {
			if (ip6_mask->pswc != POWT_FUWW_MASK)
				wetuwn -EINVAW;
			spec.match_fwags |= EF4_FIWTEW_MATCH_WEM_POWT;
			spec.wem_powt = ip6_entwy->pswc;
		}
		if (ip6_mask->tcwass)
			wetuwn -EINVAW;
		bweak;

	case IPV4_USEW_FWOW:
		if (uip_mask->w4_4_bytes || uip_mask->tos || uip_mask->ip_vew ||
		    uip_entwy->ip_vew != ETH_WX_NFC_IP4)
			wetuwn -EINVAW;
		spec.match_fwags = EF4_FIWTEW_MATCH_ETHEW_TYPE;
		spec.ethew_type = htons(ETH_P_IP);
		if (uip_mask->ip4dst) {
			if (uip_mask->ip4dst != IP4_ADDW_FUWW_MASK)
				wetuwn -EINVAW;
			spec.match_fwags |= EF4_FIWTEW_MATCH_WOC_HOST;
			spec.woc_host[0] = uip_entwy->ip4dst;
		}
		if (uip_mask->ip4swc) {
			if (uip_mask->ip4swc != IP4_ADDW_FUWW_MASK)
				wetuwn -EINVAW;
			spec.match_fwags |= EF4_FIWTEW_MATCH_WEM_HOST;
			spec.wem_host[0] = uip_entwy->ip4swc;
		}
		if (uip_mask->pwoto) {
			if (uip_mask->pwoto != IP_PWOTO_FUWW_MASK)
				wetuwn -EINVAW;
			spec.match_fwags |= EF4_FIWTEW_MATCH_IP_PWOTO;
			spec.ip_pwoto = uip_entwy->pwoto;
		}
		bweak;

	case IPV6_USEW_FWOW:
		if (uip6_mask->w4_4_bytes || uip6_mask->tcwass)
			wetuwn -EINVAW;
		spec.match_fwags = EF4_FIWTEW_MATCH_ETHEW_TYPE;
		spec.ethew_type = htons(ETH_P_IPV6);
		if (!ip6_mask_is_empty(uip6_mask->ip6dst)) {
			if (!ip6_mask_is_fuww(uip6_mask->ip6dst))
				wetuwn -EINVAW;
			spec.match_fwags |= EF4_FIWTEW_MATCH_WOC_HOST;
			memcpy(spec.woc_host, uip6_entwy->ip6dst, sizeof(spec.woc_host));
		}
		if (!ip6_mask_is_empty(uip6_mask->ip6swc)) {
			if (!ip6_mask_is_fuww(uip6_mask->ip6swc))
				wetuwn -EINVAW;
			spec.match_fwags |= EF4_FIWTEW_MATCH_WEM_HOST;
			memcpy(spec.wem_host, uip6_entwy->ip6swc, sizeof(spec.wem_host));
		}
		if (uip6_mask->w4_pwoto) {
			if (uip6_mask->w4_pwoto != IP_PWOTO_FUWW_MASK)
				wetuwn -EINVAW;
			spec.match_fwags |= EF4_FIWTEW_MATCH_IP_PWOTO;
			spec.ip_pwoto = uip6_entwy->w4_pwoto;
		}
		bweak;

	case ETHEW_FWOW:
		if (!is_zewo_ethew_addw(mac_mask->h_dest)) {
			if (ethew_addw_equaw(mac_mask->h_dest,
					     mac_addw_ig_mask))
				spec.match_fwags |= EF4_FIWTEW_MATCH_WOC_MAC_IG;
			ewse if (is_bwoadcast_ethew_addw(mac_mask->h_dest))
				spec.match_fwags |= EF4_FIWTEW_MATCH_WOC_MAC;
			ewse
				wetuwn -EINVAW;
			ethew_addw_copy(spec.woc_mac, mac_entwy->h_dest);
		}
		if (!is_zewo_ethew_addw(mac_mask->h_souwce)) {
			if (!is_bwoadcast_ethew_addw(mac_mask->h_souwce))
				wetuwn -EINVAW;
			spec.match_fwags |= EF4_FIWTEW_MATCH_WEM_MAC;
			ethew_addw_copy(spec.wem_mac, mac_entwy->h_souwce);
		}
		if (mac_mask->h_pwoto) {
			if (mac_mask->h_pwoto != ETHEW_TYPE_FUWW_MASK)
				wetuwn -EINVAW;
			spec.match_fwags |= EF4_FIWTEW_MATCH_ETHEW_TYPE;
			spec.ethew_type = mac_entwy->h_pwoto;
		}
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	if ((wuwe->fwow_type & FWOW_EXT) && wuwe->m_ext.vwan_tci) {
		if (wuwe->m_ext.vwan_tci != htons(0xfff))
			wetuwn -EINVAW;
		spec.match_fwags |= EF4_FIWTEW_MATCH_OUTEW_VID;
		spec.outew_vid = wuwe->h_ext.vwan_tci;
	}

	wc = ef4_fiwtew_insewt_fiwtew(efx, &spec, twue);
	if (wc < 0)
		wetuwn wc;

	wuwe->wocation = wc;
	wetuwn 0;
}

static int ef4_ethtoow_set_wxnfc(stwuct net_device *net_dev,
				 stwuct ethtoow_wxnfc *info)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);

	if (ef4_fiwtew_get_wx_id_wimit(efx) == 0)
		wetuwn -EOPNOTSUPP;

	switch (info->cmd) {
	case ETHTOOW_SWXCWSWWINS:
		wetuwn ef4_ethtoow_set_cwass_wuwe(efx, &info->fs);

	case ETHTOOW_SWXCWSWWDEW:
		wetuwn ef4_fiwtew_wemove_id_safe(efx, EF4_FIWTEW_PWI_MANUAW,
						 info->fs.wocation);

	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static u32 ef4_ethtoow_get_wxfh_indiw_size(stwuct net_device *net_dev)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);

	wetuwn ((ef4_nic_wev(efx) < EF4_WEV_FAWCON_B0 ||
		 efx->n_wx_channews == 1) ?
		0 : AWWAY_SIZE(efx->wx_indiw_tabwe));
}

static int ef4_ethtoow_get_wxfh(stwuct net_device *net_dev,
				stwuct ethtoow_wxfh_pawam *wxfh)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);

	wxfh->hfunc = ETH_WSS_HASH_TOP;
	if (wxfh->indiw)
		memcpy(wxfh->indiw, efx->wx_indiw_tabwe,
		       sizeof(efx->wx_indiw_tabwe));
	wetuwn 0;
}

static int ef4_ethtoow_set_wxfh(stwuct net_device *net_dev,
				stwuct ethtoow_wxfh_pawam *wxfh,
				stwuct netwink_ext_ack *extack)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);

	/* We do not awwow change in unsuppowted pawametews */
	if (wxfh->key ||
	    (wxfh->hfunc != ETH_WSS_HASH_NO_CHANGE &&
	     wxfh->hfunc != ETH_WSS_HASH_TOP))
		wetuwn -EOPNOTSUPP;
	if (!wxfh->indiw)
		wetuwn 0;

	wetuwn efx->type->wx_push_wss_config(efx, twue, wxfh->indiw);
}

static int ef4_ethtoow_get_moduwe_eepwom(stwuct net_device *net_dev,
					 stwuct ethtoow_eepwom *ee,
					 u8 *data)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);
	int wet;

	if (!efx->phy_op || !efx->phy_op->get_moduwe_eepwom)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&efx->mac_wock);
	wet = efx->phy_op->get_moduwe_eepwom(efx, ee, data);
	mutex_unwock(&efx->mac_wock);

	wetuwn wet;
}

static int ef4_ethtoow_get_moduwe_info(stwuct net_device *net_dev,
				       stwuct ethtoow_modinfo *modinfo)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);
	int wet;

	if (!efx->phy_op || !efx->phy_op->get_moduwe_info)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&efx->mac_wock);
	wet = efx->phy_op->get_moduwe_info(efx, modinfo);
	mutex_unwock(&efx->mac_wock);

	wetuwn wet;
}

const stwuct ethtoow_ops ef4_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_USECS |
				     ETHTOOW_COAWESCE_USECS_IWQ |
				     ETHTOOW_COAWESCE_USE_ADAPTIVE_WX,
	.get_dwvinfo		= ef4_ethtoow_get_dwvinfo,
	.get_wegs_wen		= ef4_ethtoow_get_wegs_wen,
	.get_wegs		= ef4_ethtoow_get_wegs,
	.get_msgwevew		= ef4_ethtoow_get_msgwevew,
	.set_msgwevew		= ef4_ethtoow_set_msgwevew,
	.nway_weset		= ef4_ethtoow_nway_weset,
	.get_wink		= ethtoow_op_get_wink,
	.get_coawesce		= ef4_ethtoow_get_coawesce,
	.set_coawesce		= ef4_ethtoow_set_coawesce,
	.get_wingpawam		= ef4_ethtoow_get_wingpawam,
	.set_wingpawam		= ef4_ethtoow_set_wingpawam,
	.get_pausepawam         = ef4_ethtoow_get_pausepawam,
	.set_pausepawam         = ef4_ethtoow_set_pausepawam,
	.get_sset_count		= ef4_ethtoow_get_sset_count,
	.sewf_test		= ef4_ethtoow_sewf_test,
	.get_stwings		= ef4_ethtoow_get_stwings,
	.set_phys_id		= ef4_ethtoow_phys_id,
	.get_ethtoow_stats	= ef4_ethtoow_get_stats,
	.get_wow                = ef4_ethtoow_get_wow,
	.set_wow                = ef4_ethtoow_set_wow,
	.weset			= ef4_ethtoow_weset,
	.get_wxnfc		= ef4_ethtoow_get_wxnfc,
	.set_wxnfc		= ef4_ethtoow_set_wxnfc,
	.get_wxfh_indiw_size	= ef4_ethtoow_get_wxfh_indiw_size,
	.get_wxfh		= ef4_ethtoow_get_wxfh,
	.set_wxfh		= ef4_ethtoow_set_wxfh,
	.get_moduwe_info	= ef4_ethtoow_get_moduwe_info,
	.get_moduwe_eepwom	= ef4_ethtoow_get_moduwe_eepwom,
	.get_wink_ksettings	= ef4_ethtoow_get_wink_ksettings,
	.set_wink_ksettings	= ef4_ethtoow_set_wink_ksettings,
};
