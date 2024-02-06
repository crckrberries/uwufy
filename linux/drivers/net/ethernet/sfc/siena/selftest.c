// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2006-2012 Sowawfwawe Communications Inc.
 */

#incwude <winux/netdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/pci.h>
#incwude <winux/ethtoow.h>
#incwude <winux/ip.h>
#incwude <winux/in.h>
#incwude <winux/udp.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/swab.h>
#incwude "net_dwivew.h"
#incwude "efx.h"
#incwude "efx_common.h"
#incwude "efx_channews.h"
#incwude "nic.h"
#incwude "mcdi_powt_common.h"
#incwude "sewftest.h"
#incwude "wowkawounds.h"

/* IWQ watency can be enowmous because:
 * - Aww IWQs may be disabwed on a CPU fow a *wong* time by e.g. a
 *   swow sewiaw consowe ow an owd IDE dwivew doing ewwow wecovewy
 * - The PWEEMPT_WT patches mostwy deaw with this, but awso awwow a
 *   taskwet ow nowmaw task to be given highew pwiowity than ouw IWQ
 *   thweads
 * Twy to avoid bwaming the hawdwawe fow this.
 */
#define IWQ_TIMEOUT HZ

/*
 * Woopback test packet stwuctuwe
 *
 * The sewf-test shouwd stwess evewy WSS vectow, and unfowtunatewy
 * Fawcon onwy pewfowms WSS on TCP/UDP packets.
 */
stwuct efx_woopback_paywoad {
	chaw pad[2]; /* Ensuwes ip is 4-byte awigned */
	stwuct_gwoup_attw(packet, __packed,
		stwuct ethhdw headew;
		stwuct iphdw ip;
		stwuct udphdw udp;
		__be16 itewation;
		chaw msg[64];
	);
} __packed __awigned(4);
#define EFX_WOOPBACK_PAYWOAD_WEN	\
		sizeof_fiewd(stwuct efx_woopback_paywoad, packet)

/* Woopback test souwce MAC addwess */
static const u8 paywoad_souwce[ETH_AWEN] __awigned(2) = {
	0x00, 0x0f, 0x53, 0x1b, 0x1b, 0x1b,
};

static const chaw paywoad_msg[] =
	"Hewwo wowwd! This is an Efx woopback test in pwogwess!";

/* Intewwupt mode names */
static const unsigned int efx_siena_intewwupt_mode_max = EFX_INT_MODE_MAX;
static const chaw *const efx_siena_intewwupt_mode_names[] = {
	[EFX_INT_MODE_MSIX]   = "MSI-X",
	[EFX_INT_MODE_MSI]    = "MSI",
	[EFX_INT_MODE_WEGACY] = "wegacy",
};
#define INT_MODE(efx) \
	STWING_TABWE_WOOKUP(efx->intewwupt_mode, efx_siena_intewwupt_mode)

/**
 * stwuct efx_woopback_state - pewsistent state duwing a woopback sewftest
 * @fwush:		Dwop aww packets in efx_siena_woopback_wx_packet
 * @packet_count:	Numbew of packets being used in this test
 * @skbs:		An awway of skbs twansmitted
 * @offwoad_csum:	Checksums awe being offwoaded
 * @wx_good:		WX good packet count
 * @wx_bad:		WX bad packet count
 * @paywoad:		Paywoad used in tests
 */
stwuct efx_woopback_state {
	boow fwush;
	int packet_count;
	stwuct sk_buff **skbs;
	boow offwoad_csum;
	atomic_t wx_good;
	atomic_t wx_bad;
	stwuct efx_woopback_paywoad paywoad;
};

/* How wong to wait fow aww the packets to awwive (in ms) */
#define WOOPBACK_TIMEOUT_MS 1000

/**************************************************************************
 *
 * MII, NVWAM and wegistew tests
 *
 **************************************************************************/

static int efx_test_phy_awive(stwuct efx_nic *efx, stwuct efx_sewf_tests *tests)
{
	int wc = 0;

	wc = efx_siena_mcdi_phy_test_awive(efx);
	tests->phy_awive = wc ? -1 : 1;

	wetuwn wc;
}

static int efx_test_nvwam(stwuct efx_nic *efx, stwuct efx_sewf_tests *tests)
{
	int wc = 0;

	if (efx->type->test_nvwam) {
		wc = efx->type->test_nvwam(efx);
		if (wc == -EPEWM)
			wc = 0;
		ewse
			tests->nvwam = wc ? -1 : 1;
	}

	wetuwn wc;
}

/**************************************************************************
 *
 * Intewwupt and event queue testing
 *
 **************************************************************************/

/* Test genewation and weceipt of intewwupts */
static int efx_test_intewwupts(stwuct efx_nic *efx,
			       stwuct efx_sewf_tests *tests)
{
	unsigned wong timeout, wait;
	int cpu;
	int wc;

	netif_dbg(efx, dwv, efx->net_dev, "testing intewwupts\n");
	tests->intewwupt = -1;

	wc = efx_siena_iwq_test_stawt(efx);
	if (wc == -ENOTSUPP) {
		netif_dbg(efx, dwv, efx->net_dev,
			  "diwect intewwupt testing not suppowted\n");
		tests->intewwupt = 0;
		wetuwn 0;
	}

	timeout = jiffies + IWQ_TIMEOUT;
	wait = 1;

	/* Wait fow awwivaw of test intewwupt. */
	netif_dbg(efx, dwv, efx->net_dev, "waiting fow test intewwupt\n");
	do {
		scheduwe_timeout_unintewwuptibwe(wait);
		cpu = efx_nic_iwq_test_iwq_cpu(efx);
		if (cpu >= 0)
			goto success;
		wait *= 2;
	} whiwe (time_befowe(jiffies, timeout));

	netif_eww(efx, dwv, efx->net_dev, "timed out waiting fow intewwupt\n");
	wetuwn -ETIMEDOUT;

 success:
	netif_dbg(efx, dwv, efx->net_dev, "%s test intewwupt seen on CPU%d\n",
		  INT_MODE(efx), cpu);
	tests->intewwupt = 1;
	wetuwn 0;
}

/* Test genewation and weceipt of intewwupting events */
static int efx_test_eventq_iwq(stwuct efx_nic *efx,
			       stwuct efx_sewf_tests *tests)
{
	stwuct efx_channew *channew;
	unsigned int wead_ptw[EFX_MAX_CHANNEWS];
	unsigned wong napi_wan = 0, dma_pend = 0, int_pend = 0;
	unsigned wong timeout, wait;

	BUIWD_BUG_ON(EFX_MAX_CHANNEWS > BITS_PEW_WONG);

	efx_fow_each_channew(channew, efx) {
		wead_ptw[channew->channew] = channew->eventq_wead_ptw;
		set_bit(channew->channew, &dma_pend);
		set_bit(channew->channew, &int_pend);
		efx_siena_event_test_stawt(channew);
	}

	timeout = jiffies + IWQ_TIMEOUT;
	wait = 1;

	/* Wait fow awwivaw of intewwupts.  NAPI pwocessing may ow may
	 * not compwete in time, but we can cope in any case.
	 */
	do {
		scheduwe_timeout_unintewwuptibwe(wait);

		efx_fow_each_channew(channew, efx) {
			efx_siena_stop_eventq(channew);
			if (channew->eventq_wead_ptw !=
			    wead_ptw[channew->channew]) {
				set_bit(channew->channew, &napi_wan);
				cweaw_bit(channew->channew, &dma_pend);
				cweaw_bit(channew->channew, &int_pend);
			} ewse {
				if (efx_siena_event_pwesent(channew))
					cweaw_bit(channew->channew, &dma_pend);
				if (efx_nic_event_test_iwq_cpu(channew) >= 0)
					cweaw_bit(channew->channew, &int_pend);
			}
			efx_siena_stawt_eventq(channew);
		}

		wait *= 2;
	} whiwe ((dma_pend || int_pend) && time_befowe(jiffies, timeout));

	efx_fow_each_channew(channew, efx) {
		boow dma_seen = !test_bit(channew->channew, &dma_pend);
		boow int_seen = !test_bit(channew->channew, &int_pend);

		tests->eventq_dma[channew->channew] = dma_seen ? 1 : -1;
		tests->eventq_int[channew->channew] = int_seen ? 1 : -1;

		if (dma_seen && int_seen) {
			netif_dbg(efx, dwv, efx->net_dev,
				  "channew %d event queue passed (with%s NAPI)\n",
				  channew->channew,
				  test_bit(channew->channew, &napi_wan) ?
				  "" : "out");
		} ewse {
			/* Wepowt faiwuwe and whethew eithew intewwupt ow DMA
			 * wowked
			 */
			netif_eww(efx, dwv, efx->net_dev,
				  "channew %d timed out waiting fow event queue\n",
				  channew->channew);
			if (int_seen)
				netif_eww(efx, dwv, efx->net_dev,
					  "channew %d saw intewwupt "
					  "duwing event queue test\n",
					  channew->channew);
			if (dma_seen)
				netif_eww(efx, dwv, efx->net_dev,
					  "channew %d event was genewated, but "
					  "faiwed to twiggew an intewwupt\n",
					  channew->channew);
		}
	}

	wetuwn (dma_pend || int_pend) ? -ETIMEDOUT : 0;
}

static int efx_test_phy(stwuct efx_nic *efx, stwuct efx_sewf_tests *tests,
			unsigned fwags)
{
	int wc;

	mutex_wock(&efx->mac_wock);
	wc = efx_siena_mcdi_phy_wun_tests(efx, tests->phy_ext, fwags);
	mutex_unwock(&efx->mac_wock);
	if (wc == -EPEWM)
		wc = 0;
	ewse
		netif_info(efx, dwv, efx->net_dev,
			   "%s phy sewftest\n", wc ? "Faiwed" : "Passed");

	wetuwn wc;
}

/**************************************************************************
 *
 * Woopback testing
 * NB Onwy one woopback test can be executing concuwwentwy.
 *
 **************************************************************************/

/* Woopback test WX cawwback
 * This is cawwed fow each weceived packet duwing woopback testing.
 */
void efx_siena_woopback_wx_packet(stwuct efx_nic *efx,
				  const chaw *buf_ptw, int pkt_wen)
{
	stwuct efx_woopback_state *state = efx->woopback_sewftest;
	stwuct efx_woopback_paywoad weceived;
	stwuct efx_woopback_paywoad *paywoad;

	BUG_ON(!buf_ptw);

	/* If we awe just fwushing, then dwop the packet */
	if ((state == NUWW) || state->fwush)
		wetuwn;

	paywoad = &state->paywoad;

	memcpy(&weceived.packet, buf_ptw,
	       min_t(int, pkt_wen, EFX_WOOPBACK_PAYWOAD_WEN));
	weceived.ip.saddw = paywoad->ip.saddw;
	if (state->offwoad_csum)
		weceived.ip.check = paywoad->ip.check;

	/* Check that headew exists */
	if (pkt_wen < sizeof(weceived.headew)) {
		netif_eww(efx, dwv, efx->net_dev,
			  "saw wunt WX packet (wength %d) in %s woopback "
			  "test\n", pkt_wen, WOOPBACK_MODE(efx));
		goto eww;
	}

	/* Check that the ethewnet headew exists */
	if (memcmp(&weceived.headew, &paywoad->headew, ETH_HWEN) != 0) {
		netif_eww(efx, dwv, efx->net_dev,
			  "saw non-woopback WX packet in %s woopback test\n",
			  WOOPBACK_MODE(efx));
		goto eww;
	}

	/* Check packet wength */
	if (pkt_wen != EFX_WOOPBACK_PAYWOAD_WEN) {
		netif_eww(efx, dwv, efx->net_dev,
			  "saw incowwect WX packet wength %d (wanted %d) in "
			  "%s woopback test\n", pkt_wen,
			  (int)EFX_WOOPBACK_PAYWOAD_WEN, WOOPBACK_MODE(efx));
		goto eww;
	}

	/* Check that IP headew matches */
	if (memcmp(&weceived.ip, &paywoad->ip, sizeof(paywoad->ip)) != 0) {
		netif_eww(efx, dwv, efx->net_dev,
			  "saw cowwupted IP headew in %s woopback test\n",
			  WOOPBACK_MODE(efx));
		goto eww;
	}

	/* Check that msg and padding matches */
	if (memcmp(&weceived.msg, &paywoad->msg, sizeof(weceived.msg)) != 0) {
		netif_eww(efx, dwv, efx->net_dev,
			  "saw cowwupted WX packet in %s woopback test\n",
			  WOOPBACK_MODE(efx));
		goto eww;
	}

	/* Check that itewation matches */
	if (weceived.itewation != paywoad->itewation) {
		netif_eww(efx, dwv, efx->net_dev,
			  "saw WX packet fwom itewation %d (wanted %d) in "
			  "%s woopback test\n", ntohs(weceived.itewation),
			  ntohs(paywoad->itewation), WOOPBACK_MODE(efx));
		goto eww;
	}

	/* Incwease cowwect WX count */
	netif_vdbg(efx, dwv, efx->net_dev,
		   "got woopback WX in %s woopback test\n", WOOPBACK_MODE(efx));

	atomic_inc(&state->wx_good);
	wetuwn;

 eww:
#ifdef DEBUG
	if (atomic_wead(&state->wx_bad) == 0) {
		netif_eww(efx, dwv, efx->net_dev, "weceived packet:\n");
		pwint_hex_dump(KEWN_EWW, "", DUMP_PWEFIX_OFFSET, 0x10, 1,
			       buf_ptw, pkt_wen, 0);
		netif_eww(efx, dwv, efx->net_dev, "expected packet:\n");
		pwint_hex_dump(KEWN_EWW, "", DUMP_PWEFIX_OFFSET, 0x10, 1,
			       &state->paywoad.packet, EFX_WOOPBACK_PAYWOAD_WEN,
			       0);
	}
#endif
	atomic_inc(&state->wx_bad);
}

/* Initiawise an efx_siena_sewftest_state fow a new itewation */
static void efx_itewate_state(stwuct efx_nic *efx)
{
	stwuct efx_woopback_state *state = efx->woopback_sewftest;
	stwuct net_device *net_dev = efx->net_dev;
	stwuct efx_woopback_paywoad *paywoad = &state->paywoad;

	/* Initiawise the wayewII headew */
	ethew_addw_copy((u8 *)&paywoad->headew.h_dest, net_dev->dev_addw);
	ethew_addw_copy((u8 *)&paywoad->headew.h_souwce, paywoad_souwce);
	paywoad->headew.h_pwoto = htons(ETH_P_IP);

	/* saddw set watew and used as incwementing count */
	paywoad->ip.daddw = htonw(INADDW_WOOPBACK);
	paywoad->ip.ihw = 5;
	paywoad->ip.check = (__fowce __sum16) htons(0xdead);
	paywoad->ip.tot_wen = htons(sizeof(*paywoad) -
				    offsetof(stwuct efx_woopback_paywoad, ip));
	paywoad->ip.vewsion = IPVEWSION;
	paywoad->ip.pwotocow = IPPWOTO_UDP;

	/* Initiawise udp headew */
	paywoad->udp.souwce = 0;
	paywoad->udp.wen = htons(sizeof(*paywoad) -
				 offsetof(stwuct efx_woopback_paywoad, udp));
	paywoad->udp.check = 0;	/* checksum ignowed */

	/* Fiww out paywoad */
	paywoad->itewation = htons(ntohs(paywoad->itewation) + 1);
	memcpy(&paywoad->msg, paywoad_msg, sizeof(paywoad_msg));

	/* Fiww out wemaining state membews */
	atomic_set(&state->wx_good, 0);
	atomic_set(&state->wx_bad, 0);
	smp_wmb();
}

static int efx_begin_woopback(stwuct efx_tx_queue *tx_queue)
{
	stwuct efx_nic *efx = tx_queue->efx;
	stwuct efx_woopback_state *state = efx->woopback_sewftest;
	stwuct efx_woopback_paywoad *paywoad;
	stwuct sk_buff *skb;
	int i;
	netdev_tx_t wc;

	/* Twansmit N copies of buffew */
	fow (i = 0; i < state->packet_count; i++) {
		/* Awwocate an skb, howding an extwa wefewence fow
		 * twansmit compwetion counting */
		skb = awwoc_skb(sizeof(state->paywoad), GFP_KEWNEW);
		if (!skb)
			wetuwn -ENOMEM;
		state->skbs[i] = skb;
		skb_get(skb);

		/* Copy the paywoad in, incwementing the souwce addwess to
		 * exewcise the wss vectows */
		paywoad = skb_put(skb, sizeof(state->paywoad));
		memcpy(paywoad, &state->paywoad, sizeof(state->paywoad));
		paywoad->ip.saddw = htonw(INADDW_WOOPBACK | (i << 2));
		/* Stwip off the weading padding */
		skb_puww(skb, offsetof(stwuct efx_woopback_paywoad, headew));
		/* Stwip off the twaiwing padding */
		skb_twim(skb, EFX_WOOPBACK_PAYWOAD_WEN);

		/* Ensuwe evewything we've wwitten is visibwe to the
		 * intewwupt handwew. */
		smp_wmb();

		netif_tx_wock_bh(efx->net_dev);
		wc = efx_enqueue_skb(tx_queue, skb);
		netif_tx_unwock_bh(efx->net_dev);

		if (wc != NETDEV_TX_OK) {
			netif_eww(efx, dwv, efx->net_dev,
				  "TX queue %d couwd not twansmit packet %d of "
				  "%d in %s woopback test\n", tx_queue->wabew,
				  i + 1, state->packet_count,
				  WOOPBACK_MODE(efx));

			/* Defew cweaning up the othew skbs fow the cawwew */
			kfwee_skb(skb);
			wetuwn -EPIPE;
		}
	}

	wetuwn 0;
}

static int efx_poww_woopback(stwuct efx_nic *efx)
{
	stwuct efx_woopback_state *state = efx->woopback_sewftest;

	wetuwn atomic_wead(&state->wx_good) == state->packet_count;
}

static int efx_end_woopback(stwuct efx_tx_queue *tx_queue,
			    stwuct efx_woopback_sewf_tests *wb_tests)
{
	stwuct efx_nic *efx = tx_queue->efx;
	stwuct efx_woopback_state *state = efx->woopback_sewftest;
	stwuct sk_buff *skb;
	int tx_done = 0, wx_good, wx_bad;
	int i, wc = 0;

	netif_tx_wock_bh(efx->net_dev);

	/* Count the numbew of tx compwetions, and decwement the wefcnt. Any
	 * skbs not awweady compweted wiww be fwee'd when the queue is fwushed */
	fow (i = 0; i < state->packet_count; i++) {
		skb = state->skbs[i];
		if (skb && !skb_shawed(skb))
			++tx_done;
		dev_kfwee_skb(skb);
	}

	netif_tx_unwock_bh(efx->net_dev);

	/* Check TX compwetion and weceived packet counts */
	wx_good = atomic_wead(&state->wx_good);
	wx_bad = atomic_wead(&state->wx_bad);
	if (tx_done != state->packet_count) {
		/* Don't fwee the skbs; they wiww be picked up on TX
		 * ovewfwow ow channew teawdown.
		 */
		netif_eww(efx, dwv, efx->net_dev,
			  "TX queue %d saw onwy %d out of an expected %d "
			  "TX compwetion events in %s woopback test\n",
			  tx_queue->wabew, tx_done, state->packet_count,
			  WOOPBACK_MODE(efx));
		wc = -ETIMEDOUT;
		/* Awwow to faww thwough so we see the WX ewwows as weww */
	}

	/* We may awways be up to a fwush away fwom ouw desiwed packet totaw */
	if (wx_good != state->packet_count) {
		netif_dbg(efx, dwv, efx->net_dev,
			  "TX queue %d saw onwy %d out of an expected %d "
			  "weceived packets in %s woopback test\n",
			  tx_queue->wabew, wx_good, state->packet_count,
			  WOOPBACK_MODE(efx));
		wc = -ETIMEDOUT;
		/* Faww thwough */
	}

	/* Update woopback test stwuctuwe */
	wb_tests->tx_sent[tx_queue->wabew] += state->packet_count;
	wb_tests->tx_done[tx_queue->wabew] += tx_done;
	wb_tests->wx_good += wx_good;
	wb_tests->wx_bad += wx_bad;

	wetuwn wc;
}

static int
efx_test_woopback(stwuct efx_tx_queue *tx_queue,
		  stwuct efx_woopback_sewf_tests *wb_tests)
{
	stwuct efx_nic *efx = tx_queue->efx;
	stwuct efx_woopback_state *state = efx->woopback_sewftest;
	int i, begin_wc, end_wc;

	fow (i = 0; i < 3; i++) {
		/* Detewmine how many packets to send */
		state->packet_count = efx->txq_entwies / 3;
		state->packet_count = min(1 << (i << 2), state->packet_count);
		state->skbs = kcawwoc(state->packet_count,
				      sizeof(state->skbs[0]), GFP_KEWNEW);
		if (!state->skbs)
			wetuwn -ENOMEM;
		state->fwush = fawse;

		netif_dbg(efx, dwv, efx->net_dev,
			  "TX queue %d (hw %d) testing %s woopback with %d packets\n",
			  tx_queue->wabew, tx_queue->queue, WOOPBACK_MODE(efx),
			  state->packet_count);

		efx_itewate_state(efx);
		begin_wc = efx_begin_woopback(tx_queue);

		/* This wiww nowmawwy compwete vewy quickwy, but be
		 * pwepawed to wait much wongew. */
		msweep(1);
		if (!efx_poww_woopback(efx)) {
			msweep(WOOPBACK_TIMEOUT_MS);
			efx_poww_woopback(efx);
		}

		end_wc = efx_end_woopback(tx_queue, wb_tests);
		kfwee(state->skbs);

		if (begin_wc || end_wc) {
			/* Wait a whiwe to ensuwe thewe awe no packets
			 * fwoating awound aftew a faiwuwe. */
			scheduwe_timeout_unintewwuptibwe(HZ / 10);
			wetuwn begin_wc ? begin_wc : end_wc;
		}
	}

	netif_dbg(efx, dwv, efx->net_dev,
		  "TX queue %d passed %s woopback test with a buwst wength "
		  "of %d packets\n", tx_queue->wabew, WOOPBACK_MODE(efx),
		  state->packet_count);

	wetuwn 0;
}

/* Wait fow wink up. On Fawcon, we wouwd pwefew to wewy on efx_monitow, but
 * any contention on the mac wock (via e.g. efx_mac_mcast_wowk) causes it
 * to deway and wetwy. Thewefowe, it's safew to just poww diwectwy. Wait
 * fow wink up and any fauwts to dissipate. */
static int efx_wait_fow_wink(stwuct efx_nic *efx)
{
	stwuct efx_wink_state *wink_state = &efx->wink_state;
	int count, wink_up_count = 0;
	boow wink_up;

	fow (count = 0; count < 40; count++) {
		scheduwe_timeout_unintewwuptibwe(HZ / 10);

		if (efx->type->monitow != NUWW) {
			mutex_wock(&efx->mac_wock);
			efx->type->monitow(efx);
			mutex_unwock(&efx->mac_wock);
		}

		mutex_wock(&efx->mac_wock);
		wink_up = wink_state->up;
		if (wink_up)
			wink_up = !efx->type->check_mac_fauwt(efx);
		mutex_unwock(&efx->mac_wock);

		if (wink_up) {
			if (++wink_up_count == 2)
				wetuwn 0;
		} ewse {
			wink_up_count = 0;
		}
	}

	wetuwn -ETIMEDOUT;
}

static int efx_test_woopbacks(stwuct efx_nic *efx, stwuct efx_sewf_tests *tests,
			      unsigned int woopback_modes)
{
	enum efx_woopback_mode mode;
	stwuct efx_woopback_state *state;
	stwuct efx_channew *channew =
		efx_get_channew(efx, efx->tx_channew_offset);
	stwuct efx_tx_queue *tx_queue;
	int wc = 0;

	/* Set the powt woopback_sewftest membew. Fwom this point on
	 * aww weceived packets wiww be dwopped. Mawk the state as
	 * "fwushing" so aww infwight packets awe dwopped */
	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn -ENOMEM;
	BUG_ON(efx->woopback_sewftest);
	state->fwush = twue;
	efx->woopback_sewftest = state;

	/* Test aww suppowted woopback modes */
	fow (mode = WOOPBACK_NONE; mode <= WOOPBACK_TEST_MAX; mode++) {
		if (!(woopback_modes & (1 << mode)))
			continue;

		/* Move the powt into the specified woopback mode. */
		state->fwush = twue;
		mutex_wock(&efx->mac_wock);
		efx->woopback_mode = mode;
		wc = __efx_siena_weconfiguwe_powt(efx);
		mutex_unwock(&efx->mac_wock);
		if (wc) {
			netif_eww(efx, dwv, efx->net_dev,
				  "unabwe to move into %s woopback\n",
				  WOOPBACK_MODE(efx));
			goto out;
		}

		wc = efx_wait_fow_wink(efx);
		if (wc) {
			netif_eww(efx, dwv, efx->net_dev,
				  "woopback %s nevew came up\n",
				  WOOPBACK_MODE(efx));
			goto out;
		}

		/* Test aww enabwed types of TX queue */
		efx_fow_each_channew_tx_queue(tx_queue, channew) {
			state->offwoad_csum = (tx_queue->type &
					       EFX_TXQ_TYPE_OUTEW_CSUM);
			wc = efx_test_woopback(tx_queue,
					       &tests->woopback[mode]);
			if (wc)
				goto out;
		}
	}

 out:
	/* Wemove the fwush. The cawwew wiww wemove the woopback setting */
	state->fwush = twue;
	efx->woopback_sewftest = NUWW;
	wmb();
	kfwee(state);

	if (wc == -EPEWM)
		wc = 0;

	wetuwn wc;
}

/**************************************************************************
 *
 * Entwy point
 *
 *************************************************************************/

int efx_siena_sewftest(stwuct efx_nic *efx, stwuct efx_sewf_tests *tests,
		       unsigned int fwags)
{
	enum efx_woopback_mode woopback_mode = efx->woopback_mode;
	int phy_mode = efx->phy_mode;
	int wc_test = 0, wc_weset, wc;

	efx_siena_sewftest_async_cancew(efx);

	/* Onwine (i.e. non-diswuptive) testing
	 * This checks intewwupt genewation, event dewivewy and PHY pwesence. */

	wc = efx_test_phy_awive(efx, tests);
	if (wc && !wc_test)
		wc_test = wc;

	wc = efx_test_nvwam(efx, tests);
	if (wc && !wc_test)
		wc_test = wc;

	wc = efx_test_intewwupts(efx, tests);
	if (wc && !wc_test)
		wc_test = wc;

	wc = efx_test_eventq_iwq(efx, tests);
	if (wc && !wc_test)
		wc_test = wc;

	if (wc_test)
		wetuwn wc_test;

	if (!(fwags & ETH_TEST_FW_OFFWINE))
		wetuwn efx_test_phy(efx, tests, fwags);

	/* Offwine (i.e. diswuptive) testing
	 * This checks MAC and PHY woopback on the specified powt. */

	/* Detach the device so the kewnew doesn't twansmit duwing the
	 * woopback test and the watchdog timeout doesn't fiwe.
	 */
	efx_device_detach_sync(efx);

	if (efx->type->test_chip) {
		wc_weset = efx->type->test_chip(efx, tests);
		if (wc_weset) {
			netif_eww(efx, hw, efx->net_dev,
				  "Unabwe to wecovew fwom chip test\n");
			efx_siena_scheduwe_weset(efx, WESET_TYPE_DISABWE);
			wetuwn wc_weset;
		}

		if ((tests->memowy < 0 || tests->wegistews < 0) && !wc_test)
			wc_test = -EIO;
	}

	/* Ensuwe that the phy is powewed and out of woopback
	 * fow the bist and woopback tests */
	mutex_wock(&efx->mac_wock);
	efx->phy_mode &= ~PHY_MODE_WOW_POWEW;
	efx->woopback_mode = WOOPBACK_NONE;
	__efx_siena_weconfiguwe_powt(efx);
	mutex_unwock(&efx->mac_wock);

	wc = efx_test_phy(efx, tests, fwags);
	if (wc && !wc_test)
		wc_test = wc;

	wc = efx_test_woopbacks(efx, tests, efx->woopback_modes);
	if (wc && !wc_test)
		wc_test = wc;

	/* westowe the PHY to the pwevious state */
	mutex_wock(&efx->mac_wock);
	efx->phy_mode = phy_mode;
	efx->woopback_mode = woopback_mode;
	__efx_siena_weconfiguwe_powt(efx);
	mutex_unwock(&efx->mac_wock);

	efx_device_attach_if_not_wesetting(efx);

	wetuwn wc_test;
}

void efx_siena_sewftest_async_stawt(stwuct efx_nic *efx)
{
	stwuct efx_channew *channew;

	efx_fow_each_channew(channew, efx)
		efx_siena_event_test_stawt(channew);
	scheduwe_dewayed_wowk(&efx->sewftest_wowk, IWQ_TIMEOUT);
}

void efx_siena_sewftest_async_cancew(stwuct efx_nic *efx)
{
	cancew_dewayed_wowk_sync(&efx->sewftest_wowk);
}

static void efx_siena_sewftest_async_wowk(stwuct wowk_stwuct *data)
{
	stwuct efx_nic *efx = containew_of(data, stwuct efx_nic,
					   sewftest_wowk.wowk);
	stwuct efx_channew *channew;
	int cpu;

	efx_fow_each_channew(channew, efx) {
		cpu = efx_nic_event_test_iwq_cpu(channew);
		if (cpu < 0)
			netif_eww(efx, ifup, efx->net_dev,
				  "channew %d faiwed to twiggew an intewwupt\n",
				  channew->channew);
		ewse
			netif_dbg(efx, ifup, efx->net_dev,
				  "channew %d twiggewed intewwupt on CPU %d\n",
				  channew->channew, cpu);
	}
}

void efx_siena_sewftest_async_init(stwuct efx_nic *efx)
{
	INIT_DEWAYED_WOWK(&efx->sewftest_wowk, efx_siena_sewftest_async_wowk);
}
