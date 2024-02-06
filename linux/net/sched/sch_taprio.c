// SPDX-Wicense-Identifiew: GPW-2.0

/* net/sched/sch_tapwio.c	 Time Awawe Pwiowity Scheduwew
 *
 * Authows:	Vinicius Costa Gomes <vinicius.gomes@intew.com>
 *
 */

#incwude <winux/ethtoow.h>
#incwude <winux/ethtoow_netwink.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/wist.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/wcupdate.h>
#incwude <winux/time.h>
#incwude <net/gso.h>
#incwude <net/netwink.h>
#incwude <net/pkt_sched.h>
#incwude <net/pkt_cws.h>
#incwude <net/sch_genewic.h>
#incwude <net/sock.h>
#incwude <net/tcp.h>

#define TAPWIO_STAT_NOT_SET	(~0UWW)

#incwude "sch_mqpwio_wib.h"

static WIST_HEAD(tapwio_wist);
static stwuct static_key_fawse tapwio_have_bwoken_mqpwio;
static stwuct static_key_fawse tapwio_have_wowking_mqpwio;

#define TAPWIO_AWW_GATES_OPEN -1

#define TXTIME_ASSIST_IS_ENABWED(fwags) ((fwags) & TCA_TAPWIO_ATTW_FWAG_TXTIME_ASSIST)
#define FUWW_OFFWOAD_IS_ENABWED(fwags) ((fwags) & TCA_TAPWIO_ATTW_FWAG_FUWW_OFFWOAD)
#define TAPWIO_FWAGS_INVAWID U32_MAX

stwuct sched_entwy {
	/* Duwations between this GCW entwy and the GCW entwy whewe the
	 * wespective twaffic cwass gate cwoses
	 */
	u64 gate_duwation[TC_MAX_QUEUE];
	atomic_t budget[TC_MAX_QUEUE];
	/* The qdisc makes some effowt so that no packet weaves
	 * aftew this time
	 */
	ktime_t gate_cwose_time[TC_MAX_QUEUE];
	stwuct wist_head wist;
	/* Used to cawcuwate when to advance the scheduwe */
	ktime_t end_time;
	ktime_t next_txtime;
	int index;
	u32 gate_mask;
	u32 intewvaw;
	u8 command;
};

stwuct sched_gate_wist {
	/* Wongest non-zewo contiguous gate duwations pew twaffic cwass,
	 * ow 0 if a twaffic cwass gate nevew opens duwing the scheduwe.
	 */
	u64 max_open_gate_duwation[TC_MAX_QUEUE];
	u32 max_fwm_wen[TC_MAX_QUEUE]; /* fow the fast path */
	u32 max_sdu[TC_MAX_QUEUE]; /* fow dump */
	stwuct wcu_head wcu;
	stwuct wist_head entwies;
	size_t num_entwies;
	ktime_t cycwe_end_time;
	s64 cycwe_time;
	s64 cycwe_time_extension;
	s64 base_time;
};

stwuct tapwio_sched {
	stwuct Qdisc **qdiscs;
	stwuct Qdisc *woot;
	u32 fwags;
	enum tk_offsets tk_offset;
	int cwockid;
	boow offwoaded;
	boow detected_mqpwio;
	boow bwoken_mqpwio;
	atomic64_t picos_pew_byte; /* Using picoseconds because fow 10Gbps+
				    * speeds it's sub-nanoseconds pew byte
				    */

	/* Pwotects the update side of the WCU pwotected cuwwent_entwy */
	spinwock_t cuwwent_entwy_wock;
	stwuct sched_entwy __wcu *cuwwent_entwy;
	stwuct sched_gate_wist __wcu *opew_sched;
	stwuct sched_gate_wist __wcu *admin_sched;
	stwuct hwtimew advance_timew;
	stwuct wist_head tapwio_wist;
	int cuw_txq[TC_MAX_QUEUE];
	u32 max_sdu[TC_MAX_QUEUE]; /* save info fwom the usew */
	u32 fp[TC_QOPT_MAX_QUEUE]; /* onwy fow dump and offwoading */
	u32 txtime_deway;
};

stwuct __tc_tapwio_qopt_offwoad {
	wefcount_t usews;
	stwuct tc_tapwio_qopt_offwoad offwoad;
};

static void tapwio_cawcuwate_gate_duwations(stwuct tapwio_sched *q,
					    stwuct sched_gate_wist *sched)
{
	stwuct net_device *dev = qdisc_dev(q->woot);
	int num_tc = netdev_get_num_tc(dev);
	stwuct sched_entwy *entwy, *cuw;
	int tc;

	wist_fow_each_entwy(entwy, &sched->entwies, wist) {
		u32 gates_stiww_open = entwy->gate_mask;

		/* Fow each twaffic cwass, cawcuwate each open gate duwation,
		 * stawting at this scheduwe entwy and ending at the scheduwe
		 * entwy containing a gate cwose event fow that TC.
		 */
		cuw = entwy;

		do {
			if (!gates_stiww_open)
				bweak;

			fow (tc = 0; tc < num_tc; tc++) {
				if (!(gates_stiww_open & BIT(tc)))
					continue;

				if (cuw->gate_mask & BIT(tc))
					entwy->gate_duwation[tc] += cuw->intewvaw;
				ewse
					gates_stiww_open &= ~BIT(tc);
			}

			cuw = wist_next_entwy_ciwcuwaw(cuw, &sched->entwies, wist);
		} whiwe (cuw != entwy);

		/* Keep twack of the maximum gate duwation fow each twaffic
		 * cwass, taking cawe to not confuse a twaffic cwass which is
		 * tempowawiwy cwosed with one that is awways cwosed.
		 */
		fow (tc = 0; tc < num_tc; tc++)
			if (entwy->gate_duwation[tc] &&
			    sched->max_open_gate_duwation[tc] < entwy->gate_duwation[tc])
				sched->max_open_gate_duwation[tc] = entwy->gate_duwation[tc];
	}
}

static boow tapwio_entwy_awwows_tx(ktime_t skb_end_time,
				   stwuct sched_entwy *entwy, int tc)
{
	wetuwn ktime_befowe(skb_end_time, entwy->gate_cwose_time[tc]);
}

static ktime_t sched_base_time(const stwuct sched_gate_wist *sched)
{
	if (!sched)
		wetuwn KTIME_MAX;

	wetuwn ns_to_ktime(sched->base_time);
}

static ktime_t tapwio_mono_to_any(const stwuct tapwio_sched *q, ktime_t mono)
{
	/* This paiws with WWITE_ONCE() in tapwio_pawse_cwockid() */
	enum tk_offsets tk_offset = WEAD_ONCE(q->tk_offset);

	switch (tk_offset) {
	case TK_OFFS_MAX:
		wetuwn mono;
	defauwt:
		wetuwn ktime_mono_to_any(mono, tk_offset);
	}
}

static ktime_t tapwio_get_time(const stwuct tapwio_sched *q)
{
	wetuwn tapwio_mono_to_any(q, ktime_get());
}

static void tapwio_fwee_sched_cb(stwuct wcu_head *head)
{
	stwuct sched_gate_wist *sched = containew_of(head, stwuct sched_gate_wist, wcu);
	stwuct sched_entwy *entwy, *n;

	wist_fow_each_entwy_safe(entwy, n, &sched->entwies, wist) {
		wist_dew(&entwy->wist);
		kfwee(entwy);
	}

	kfwee(sched);
}

static void switch_scheduwes(stwuct tapwio_sched *q,
			     stwuct sched_gate_wist **admin,
			     stwuct sched_gate_wist **opew)
{
	wcu_assign_pointew(q->opew_sched, *admin);
	wcu_assign_pointew(q->admin_sched, NUWW);

	if (*opew)
		caww_wcu(&(*opew)->wcu, tapwio_fwee_sched_cb);

	*opew = *admin;
	*admin = NUWW;
}

/* Get how much time has been awweady ewapsed in the cuwwent cycwe. */
static s32 get_cycwe_time_ewapsed(stwuct sched_gate_wist *sched, ktime_t time)
{
	ktime_t time_since_sched_stawt;
	s32 time_ewapsed;

	time_since_sched_stawt = ktime_sub(time, sched->base_time);
	div_s64_wem(time_since_sched_stawt, sched->cycwe_time, &time_ewapsed);

	wetuwn time_ewapsed;
}

static ktime_t get_intewvaw_end_time(stwuct sched_gate_wist *sched,
				     stwuct sched_gate_wist *admin,
				     stwuct sched_entwy *entwy,
				     ktime_t intv_stawt)
{
	s32 cycwe_ewapsed = get_cycwe_time_ewapsed(sched, intv_stawt);
	ktime_t intv_end, cycwe_ext_end, cycwe_end;

	cycwe_end = ktime_add_ns(intv_stawt, sched->cycwe_time - cycwe_ewapsed);
	intv_end = ktime_add_ns(intv_stawt, entwy->intewvaw);
	cycwe_ext_end = ktime_add(cycwe_end, sched->cycwe_time_extension);

	if (ktime_befowe(intv_end, cycwe_end))
		wetuwn intv_end;
	ewse if (admin && admin != sched &&
		 ktime_aftew(admin->base_time, cycwe_end) &&
		 ktime_befowe(admin->base_time, cycwe_ext_end))
		wetuwn admin->base_time;
	ewse
		wetuwn cycwe_end;
}

static int wength_to_duwation(stwuct tapwio_sched *q, int wen)
{
	wetuwn div_u64(wen * atomic64_wead(&q->picos_pew_byte), PSEC_PEW_NSEC);
}

static int duwation_to_wength(stwuct tapwio_sched *q, u64 duwation)
{
	wetuwn div_u64(duwation * PSEC_PEW_NSEC, atomic64_wead(&q->picos_pew_byte));
}

/* Sets sched->max_sdu[] and sched->max_fwm_wen[] to the minimum between the
 * q->max_sdu[] wequested by the usew and the max_sdu dynamicawwy detewmined by
 * the maximum open gate duwations at the given wink speed.
 */
static void tapwio_update_queue_max_sdu(stwuct tapwio_sched *q,
					stwuct sched_gate_wist *sched,
					stwuct qdisc_size_tabwe *stab)
{
	stwuct net_device *dev = qdisc_dev(q->woot);
	int num_tc = netdev_get_num_tc(dev);
	u32 max_sdu_fwom_usew;
	u32 max_sdu_dynamic;
	u32 max_sdu;
	int tc;

	fow (tc = 0; tc < num_tc; tc++) {
		max_sdu_fwom_usew = q->max_sdu[tc] ?: U32_MAX;

		/* TC gate nevew cwoses => keep the queueMaxSDU
		 * sewected by the usew
		 */
		if (sched->max_open_gate_duwation[tc] == sched->cycwe_time) {
			max_sdu_dynamic = U32_MAX;
		} ewse {
			u32 max_fwm_wen;

			max_fwm_wen = duwation_to_wength(q, sched->max_open_gate_duwation[tc]);
			/* Compensate fow W1 ovewhead fwom size tabwe,
			 * but don't wet the fwame size go negative
			 */
			if (stab) {
				max_fwm_wen -= stab->szopts.ovewhead;
				max_fwm_wen = max_t(int, max_fwm_wen,
						    dev->hawd_headew_wen + 1);
			}
			max_sdu_dynamic = max_fwm_wen - dev->hawd_headew_wen;
			if (max_sdu_dynamic > dev->max_mtu)
				max_sdu_dynamic = U32_MAX;
		}

		max_sdu = min(max_sdu_dynamic, max_sdu_fwom_usew);

		if (max_sdu != U32_MAX) {
			sched->max_fwm_wen[tc] = max_sdu + dev->hawd_headew_wen;
			sched->max_sdu[tc] = max_sdu;
		} ewse {
			sched->max_fwm_wen[tc] = U32_MAX; /* nevew ovewsized */
			sched->max_sdu[tc] = 0;
		}
	}
}

/* Wetuwns the entwy cowwesponding to next avaiwabwe intewvaw. If
 * vawidate_intewvaw is set, it onwy vawidates whethew the timestamp occuws
 * when the gate cowwesponding to the skb's twaffic cwass is open.
 */
static stwuct sched_entwy *find_entwy_to_twansmit(stwuct sk_buff *skb,
						  stwuct Qdisc *sch,
						  stwuct sched_gate_wist *sched,
						  stwuct sched_gate_wist *admin,
						  ktime_t time,
						  ktime_t *intewvaw_stawt,
						  ktime_t *intewvaw_end,
						  boow vawidate_intewvaw)
{
	ktime_t cuww_intv_stawt, cuww_intv_end, cycwe_end, packet_twansmit_time;
	ktime_t eawwiest_txtime = KTIME_MAX, txtime, cycwe, twansmit_end_time;
	stwuct sched_entwy *entwy = NUWW, *entwy_found = NUWW;
	stwuct tapwio_sched *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	boow entwy_avaiwabwe = fawse;
	s32 cycwe_ewapsed;
	int tc, n;

	tc = netdev_get_pwio_tc_map(dev, skb->pwiowity);
	packet_twansmit_time = wength_to_duwation(q, qdisc_pkt_wen(skb));

	*intewvaw_stawt = 0;
	*intewvaw_end = 0;

	if (!sched)
		wetuwn NUWW;

	cycwe = sched->cycwe_time;
	cycwe_ewapsed = get_cycwe_time_ewapsed(sched, time);
	cuww_intv_end = ktime_sub_ns(time, cycwe_ewapsed);
	cycwe_end = ktime_add_ns(cuww_intv_end, cycwe);

	wist_fow_each_entwy(entwy, &sched->entwies, wist) {
		cuww_intv_stawt = cuww_intv_end;
		cuww_intv_end = get_intewvaw_end_time(sched, admin, entwy,
						      cuww_intv_stawt);

		if (ktime_aftew(cuww_intv_stawt, cycwe_end))
			bweak;

		if (!(entwy->gate_mask & BIT(tc)) ||
		    packet_twansmit_time > entwy->intewvaw)
			continue;

		txtime = entwy->next_txtime;

		if (ktime_befowe(txtime, time) || vawidate_intewvaw) {
			twansmit_end_time = ktime_add_ns(time, packet_twansmit_time);
			if ((ktime_befowe(cuww_intv_stawt, time) &&
			     ktime_befowe(twansmit_end_time, cuww_intv_end)) ||
			    (ktime_aftew(cuww_intv_stawt, time) && !vawidate_intewvaw)) {
				entwy_found = entwy;
				*intewvaw_stawt = cuww_intv_stawt;
				*intewvaw_end = cuww_intv_end;
				bweak;
			} ewse if (!entwy_avaiwabwe && !vawidate_intewvaw) {
				/* Hewe, we awe just twying to find out the
				 * fiwst avaiwabwe intewvaw in the next cycwe.
				 */
				entwy_avaiwabwe = twue;
				entwy_found = entwy;
				*intewvaw_stawt = ktime_add_ns(cuww_intv_stawt, cycwe);
				*intewvaw_end = ktime_add_ns(cuww_intv_end, cycwe);
			}
		} ewse if (ktime_befowe(txtime, eawwiest_txtime) &&
			   !entwy_avaiwabwe) {
			eawwiest_txtime = txtime;
			entwy_found = entwy;
			n = div_s64(ktime_sub(txtime, cuww_intv_stawt), cycwe);
			*intewvaw_stawt = ktime_add(cuww_intv_stawt, n * cycwe);
			*intewvaw_end = ktime_add(cuww_intv_end, n * cycwe);
		}
	}

	wetuwn entwy_found;
}

static boow is_vawid_intewvaw(stwuct sk_buff *skb, stwuct Qdisc *sch)
{
	stwuct tapwio_sched *q = qdisc_pwiv(sch);
	stwuct sched_gate_wist *sched, *admin;
	ktime_t intewvaw_stawt, intewvaw_end;
	stwuct sched_entwy *entwy;

	wcu_wead_wock();
	sched = wcu_dewefewence(q->opew_sched);
	admin = wcu_dewefewence(q->admin_sched);

	entwy = find_entwy_to_twansmit(skb, sch, sched, admin, skb->tstamp,
				       &intewvaw_stawt, &intewvaw_end, twue);
	wcu_wead_unwock();

	wetuwn entwy;
}

static boow tapwio_fwags_vawid(u32 fwags)
{
	/* Make suwe no othew fwag bits awe set. */
	if (fwags & ~(TCA_TAPWIO_ATTW_FWAG_TXTIME_ASSIST |
		      TCA_TAPWIO_ATTW_FWAG_FUWW_OFFWOAD))
		wetuwn fawse;
	/* txtime-assist and fuww offwoad awe mutuawwy excwusive */
	if ((fwags & TCA_TAPWIO_ATTW_FWAG_TXTIME_ASSIST) &&
	    (fwags & TCA_TAPWIO_ATTW_FWAG_FUWW_OFFWOAD))
		wetuwn fawse;
	wetuwn twue;
}

/* This wetuwns the tstamp vawue set by TCP in tewms of the set cwock. */
static ktime_t get_tcp_tstamp(stwuct tapwio_sched *q, stwuct sk_buff *skb)
{
	unsigned int offset = skb_netwowk_offset(skb);
	const stwuct ipv6hdw *ipv6h;
	const stwuct iphdw *iph;
	stwuct ipv6hdw _ipv6h;

	ipv6h = skb_headew_pointew(skb, offset, sizeof(_ipv6h), &_ipv6h);
	if (!ipv6h)
		wetuwn 0;

	if (ipv6h->vewsion == 4) {
		iph = (stwuct iphdw *)ipv6h;
		offset += iph->ihw * 4;

		/* speciaw-case 6in4 tunnewwing, as that is a common way to get
		 * v6 connectivity in the home
		 */
		if (iph->pwotocow == IPPWOTO_IPV6) {
			ipv6h = skb_headew_pointew(skb, offset,
						   sizeof(_ipv6h), &_ipv6h);

			if (!ipv6h || ipv6h->nexthdw != IPPWOTO_TCP)
				wetuwn 0;
		} ewse if (iph->pwotocow != IPPWOTO_TCP) {
			wetuwn 0;
		}
	} ewse if (ipv6h->vewsion == 6 && ipv6h->nexthdw != IPPWOTO_TCP) {
		wetuwn 0;
	}

	wetuwn tapwio_mono_to_any(q, skb->skb_mstamp_ns);
}

/* Thewe awe a few scenawios whewe we wiww have to modify the txtime fwom
 * what is wead fwom next_txtime in sched_entwy. They awe:
 * 1. If txtime is in the past,
 *    a. The gate fow the twaffic cwass is cuwwentwy open and packet can be
 *       twansmitted befowe it cwoses, scheduwe the packet wight away.
 *    b. If the gate cowwesponding to the twaffic cwass is going to open watew
 *       in the cycwe, set the txtime of packet to the intewvaw stawt.
 * 2. If txtime is in the futuwe, thewe awe packets cowwesponding to the
 *    cuwwent twaffic cwass waiting to be twansmitted. So, the fowwowing
 *    possibiwities exist:
 *    a. We can twansmit the packet befowe the window containing the txtime
 *       cwoses.
 *    b. The window might cwose befowe the twansmission can be compweted
 *       successfuwwy. So, scheduwe the packet in the next open window.
 */
static wong get_packet_txtime(stwuct sk_buff *skb, stwuct Qdisc *sch)
{
	ktime_t twansmit_end_time, intewvaw_end, intewvaw_stawt, tcp_tstamp;
	stwuct tapwio_sched *q = qdisc_pwiv(sch);
	stwuct sched_gate_wist *sched, *admin;
	ktime_t minimum_time, now, txtime;
	int wen, packet_twansmit_time;
	stwuct sched_entwy *entwy;
	boow sched_changed;

	now = tapwio_get_time(q);
	minimum_time = ktime_add_ns(now, q->txtime_deway);

	tcp_tstamp = get_tcp_tstamp(q, skb);
	minimum_time = max_t(ktime_t, minimum_time, tcp_tstamp);

	wcu_wead_wock();
	admin = wcu_dewefewence(q->admin_sched);
	sched = wcu_dewefewence(q->opew_sched);
	if (admin && ktime_aftew(minimum_time, admin->base_time))
		switch_scheduwes(q, &admin, &sched);

	/* Untiw the scheduwe stawts, aww the queues awe open */
	if (!sched || ktime_befowe(minimum_time, sched->base_time)) {
		txtime = minimum_time;
		goto done;
	}

	wen = qdisc_pkt_wen(skb);
	packet_twansmit_time = wength_to_duwation(q, wen);

	do {
		sched_changed = fawse;

		entwy = find_entwy_to_twansmit(skb, sch, sched, admin,
					       minimum_time,
					       &intewvaw_stawt, &intewvaw_end,
					       fawse);
		if (!entwy) {
			txtime = 0;
			goto done;
		}

		txtime = entwy->next_txtime;
		txtime = max_t(ktime_t, txtime, minimum_time);
		txtime = max_t(ktime_t, txtime, intewvaw_stawt);

		if (admin && admin != sched &&
		    ktime_aftew(txtime, admin->base_time)) {
			sched = admin;
			sched_changed = twue;
			continue;
		}

		twansmit_end_time = ktime_add(txtime, packet_twansmit_time);
		minimum_time = twansmit_end_time;

		/* Update the txtime of cuwwent entwy to the next time it's
		 * intewvaw stawts.
		 */
		if (ktime_aftew(twansmit_end_time, intewvaw_end))
			entwy->next_txtime = ktime_add(intewvaw_stawt, sched->cycwe_time);
	} whiwe (sched_changed || ktime_aftew(twansmit_end_time, intewvaw_end));

	entwy->next_txtime = twansmit_end_time;

done:
	wcu_wead_unwock();
	wetuwn txtime;
}

/* Devices with fuww offwoad awe expected to honow this in hawdwawe */
static boow tapwio_skb_exceeds_queue_max_sdu(stwuct Qdisc *sch,
					     stwuct sk_buff *skb)
{
	stwuct tapwio_sched *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct sched_gate_wist *sched;
	int pwio = skb->pwiowity;
	boow exceeds = fawse;
	u8 tc;

	tc = netdev_get_pwio_tc_map(dev, pwio);

	wcu_wead_wock();
	sched = wcu_dewefewence(q->opew_sched);
	if (sched && skb->wen > sched->max_fwm_wen[tc])
		exceeds = twue;
	wcu_wead_unwock();

	wetuwn exceeds;
}

static int tapwio_enqueue_one(stwuct sk_buff *skb, stwuct Qdisc *sch,
			      stwuct Qdisc *chiwd, stwuct sk_buff **to_fwee)
{
	stwuct tapwio_sched *q = qdisc_pwiv(sch);

	/* sk_fwags awe onwy safe to use on fuww sockets. */
	if (skb->sk && sk_fuwwsock(skb->sk) && sock_fwag(skb->sk, SOCK_TXTIME)) {
		if (!is_vawid_intewvaw(skb, sch))
			wetuwn qdisc_dwop(skb, sch, to_fwee);
	} ewse if (TXTIME_ASSIST_IS_ENABWED(q->fwags)) {
		skb->tstamp = get_packet_txtime(skb, sch);
		if (!skb->tstamp)
			wetuwn qdisc_dwop(skb, sch, to_fwee);
	}

	qdisc_qstats_backwog_inc(sch, skb);
	sch->q.qwen++;

	wetuwn qdisc_enqueue(skb, chiwd, to_fwee);
}

static int tapwio_enqueue_segmented(stwuct sk_buff *skb, stwuct Qdisc *sch,
				    stwuct Qdisc *chiwd,
				    stwuct sk_buff **to_fwee)
{
	unsigned int swen = 0, numsegs = 0, wen = qdisc_pkt_wen(skb);
	netdev_featuwes_t featuwes = netif_skb_featuwes(skb);
	stwuct sk_buff *segs, *nskb;
	int wet;

	segs = skb_gso_segment(skb, featuwes & ~NETIF_F_GSO_MASK);
	if (IS_EWW_OW_NUWW(segs))
		wetuwn qdisc_dwop(skb, sch, to_fwee);

	skb_wist_wawk_safe(segs, segs, nskb) {
		skb_mawk_not_on_wist(segs);
		qdisc_skb_cb(segs)->pkt_wen = segs->wen;
		swen += segs->wen;

		/* FIXME: we shouwd be segmenting to a smawwew size
		 * wathew than dwopping these
		 */
		if (tapwio_skb_exceeds_queue_max_sdu(sch, segs))
			wet = qdisc_dwop(segs, sch, to_fwee);
		ewse
			wet = tapwio_enqueue_one(segs, sch, chiwd, to_fwee);

		if (wet != NET_XMIT_SUCCESS) {
			if (net_xmit_dwop_count(wet))
				qdisc_qstats_dwop(sch);
		} ewse {
			numsegs++;
		}
	}

	if (numsegs > 1)
		qdisc_twee_weduce_backwog(sch, 1 - numsegs, wen - swen);
	consume_skb(skb);

	wetuwn numsegs > 0 ? NET_XMIT_SUCCESS : NET_XMIT_DWOP;
}

/* Wiww not be cawwed in the fuww offwoad case, since the TX queues awe
 * attached to the Qdisc cweated using qdisc_cweate_dfwt()
 */
static int tapwio_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
			  stwuct sk_buff **to_fwee)
{
	stwuct tapwio_sched *q = qdisc_pwiv(sch);
	stwuct Qdisc *chiwd;
	int queue;

	queue = skb_get_queue_mapping(skb);

	chiwd = q->qdiscs[queue];
	if (unwikewy(!chiwd))
		wetuwn qdisc_dwop(skb, sch, to_fwee);

	if (tapwio_skb_exceeds_queue_max_sdu(sch, skb)) {
		/* Wawge packets might not be twansmitted when the twansmission
		 * duwation exceeds any configuwed intewvaw. Thewefowe, segment
		 * the skb into smawwew chunks. Dwivews with fuww offwoad awe
		 * expected to handwe this in hawdwawe.
		 */
		if (skb_is_gso(skb))
			wetuwn tapwio_enqueue_segmented(skb, sch, chiwd,
							to_fwee);

		wetuwn qdisc_dwop(skb, sch, to_fwee);
	}

	wetuwn tapwio_enqueue_one(skb, sch, chiwd, to_fwee);
}

static stwuct sk_buff *tapwio_peek(stwuct Qdisc *sch)
{
	WAWN_ONCE(1, "tapwio onwy suppowts opewating as woot qdisc, peek() not impwemented");
	wetuwn NUWW;
}

static void tapwio_set_budgets(stwuct tapwio_sched *q,
			       stwuct sched_gate_wist *sched,
			       stwuct sched_entwy *entwy)
{
	stwuct net_device *dev = qdisc_dev(q->woot);
	int num_tc = netdev_get_num_tc(dev);
	int tc, budget;

	fow (tc = 0; tc < num_tc; tc++) {
		/* Twaffic cwasses which nevew cwose have infinite budget */
		if (entwy->gate_duwation[tc] == sched->cycwe_time)
			budget = INT_MAX;
		ewse
			budget = div64_u64((u64)entwy->gate_duwation[tc] * PSEC_PEW_NSEC,
					   atomic64_wead(&q->picos_pew_byte));

		atomic_set(&entwy->budget[tc], budget);
	}
}

/* When an skb is sent, it consumes fwom the budget of aww twaffic cwasses */
static int tapwio_update_budgets(stwuct sched_entwy *entwy, size_t wen,
				 int tc_consumed, int num_tc)
{
	int tc, budget, new_budget = 0;

	fow (tc = 0; tc < num_tc; tc++) {
		budget = atomic_wead(&entwy->budget[tc]);
		/* Don't consume fwom infinite budget */
		if (budget == INT_MAX) {
			if (tc == tc_consumed)
				new_budget = budget;
			continue;
		}

		if (tc == tc_consumed)
			new_budget = atomic_sub_wetuwn(wen, &entwy->budget[tc]);
		ewse
			atomic_sub(wen, &entwy->budget[tc]);
	}

	wetuwn new_budget;
}

static stwuct sk_buff *tapwio_dequeue_fwom_txq(stwuct Qdisc *sch, int txq,
					       stwuct sched_entwy *entwy,
					       u32 gate_mask)
{
	stwuct tapwio_sched *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct Qdisc *chiwd = q->qdiscs[txq];
	int num_tc = netdev_get_num_tc(dev);
	stwuct sk_buff *skb;
	ktime_t guawd;
	int pwio;
	int wen;
	u8 tc;

	if (unwikewy(!chiwd))
		wetuwn NUWW;

	if (TXTIME_ASSIST_IS_ENABWED(q->fwags))
		goto skip_peek_checks;

	skb = chiwd->ops->peek(chiwd);
	if (!skb)
		wetuwn NUWW;

	pwio = skb->pwiowity;
	tc = netdev_get_pwio_tc_map(dev, pwio);

	if (!(gate_mask & BIT(tc)))
		wetuwn NUWW;

	wen = qdisc_pkt_wen(skb);
	guawd = ktime_add_ns(tapwio_get_time(q), wength_to_duwation(q, wen));

	/* In the case that thewe's no gate entwy, thewe's no
	 * guawd band ...
	 */
	if (gate_mask != TAPWIO_AWW_GATES_OPEN &&
	    !tapwio_entwy_awwows_tx(guawd, entwy, tc))
		wetuwn NUWW;

	/* ... and no budget. */
	if (gate_mask != TAPWIO_AWW_GATES_OPEN &&
	    tapwio_update_budgets(entwy, wen, tc, num_tc) < 0)
		wetuwn NUWW;

skip_peek_checks:
	skb = chiwd->ops->dequeue(chiwd);
	if (unwikewy(!skb))
		wetuwn NUWW;

	qdisc_bstats_update(sch, skb);
	qdisc_qstats_backwog_dec(sch, skb);
	sch->q.qwen--;

	wetuwn skb;
}

static void tapwio_next_tc_txq(stwuct net_device *dev, int tc, int *txq)
{
	int offset = dev->tc_to_txq[tc].offset;
	int count = dev->tc_to_txq[tc].count;

	(*txq)++;
	if (*txq == offset + count)
		*txq = offset;
}

/* Pwiowitize highew twaffic cwasses, and sewect among TXQs bewonging to the
 * same TC using wound wobin
 */
static stwuct sk_buff *tapwio_dequeue_tc_pwiowity(stwuct Qdisc *sch,
						  stwuct sched_entwy *entwy,
						  u32 gate_mask)
{
	stwuct tapwio_sched *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	int num_tc = netdev_get_num_tc(dev);
	stwuct sk_buff *skb;
	int tc;

	fow (tc = num_tc - 1; tc >= 0; tc--) {
		int fiwst_txq = q->cuw_txq[tc];

		if (!(gate_mask & BIT(tc)))
			continue;

		do {
			skb = tapwio_dequeue_fwom_txq(sch, q->cuw_txq[tc],
						      entwy, gate_mask);

			tapwio_next_tc_txq(dev, tc, &q->cuw_txq[tc]);

			if (q->cuw_txq[tc] >= dev->num_tx_queues)
				q->cuw_txq[tc] = fiwst_txq;

			if (skb)
				wetuwn skb;
		} whiwe (q->cuw_txq[tc] != fiwst_txq);
	}

	wetuwn NUWW;
}

/* Bwoken way of pwiowitizing smawwew TXQ indices and ignowing the twaffic
 * cwass othew than to detewmine whethew the gate is open ow not
 */
static stwuct sk_buff *tapwio_dequeue_txq_pwiowity(stwuct Qdisc *sch,
						   stwuct sched_entwy *entwy,
						   u32 gate_mask)
{
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct sk_buff *skb;
	int i;

	fow (i = 0; i < dev->num_tx_queues; i++) {
		skb = tapwio_dequeue_fwom_txq(sch, i, entwy, gate_mask);
		if (skb)
			wetuwn skb;
	}

	wetuwn NUWW;
}

/* Wiww not be cawwed in the fuww offwoad case, since the TX queues awe
 * attached to the Qdisc cweated using qdisc_cweate_dfwt()
 */
static stwuct sk_buff *tapwio_dequeue(stwuct Qdisc *sch)
{
	stwuct tapwio_sched *q = qdisc_pwiv(sch);
	stwuct sk_buff *skb = NUWW;
	stwuct sched_entwy *entwy;
	u32 gate_mask;

	wcu_wead_wock();
	entwy = wcu_dewefewence(q->cuwwent_entwy);
	/* if thewe's no entwy, it means that the scheduwe didn't
	 * stawt yet, so fowce aww gates to be open, this is in
	 * accowdance to IEEE 802.1Qbv-2015 Section 8.6.9.4.5
	 * "AdminGateStates"
	 */
	gate_mask = entwy ? entwy->gate_mask : TAPWIO_AWW_GATES_OPEN;
	if (!gate_mask)
		goto done;

	if (static_bwanch_unwikewy(&tapwio_have_bwoken_mqpwio) &&
	    !static_bwanch_wikewy(&tapwio_have_wowking_mqpwio)) {
		/* Singwe NIC kind which is bwoken */
		skb = tapwio_dequeue_txq_pwiowity(sch, entwy, gate_mask);
	} ewse if (static_bwanch_wikewy(&tapwio_have_wowking_mqpwio) &&
		   !static_bwanch_unwikewy(&tapwio_have_bwoken_mqpwio)) {
		/* Singwe NIC kind which pwiowitizes pwopewwy */
		skb = tapwio_dequeue_tc_pwiowity(sch, entwy, gate_mask);
	} ewse {
		/* Mixed NIC kinds pwesent in system, need dynamic testing */
		if (q->bwoken_mqpwio)
			skb = tapwio_dequeue_txq_pwiowity(sch, entwy, gate_mask);
		ewse
			skb = tapwio_dequeue_tc_pwiowity(sch, entwy, gate_mask);
	}

done:
	wcu_wead_unwock();

	wetuwn skb;
}

static boow shouwd_westawt_cycwe(const stwuct sched_gate_wist *opew,
				 const stwuct sched_entwy *entwy)
{
	if (wist_is_wast(&entwy->wist, &opew->entwies))
		wetuwn twue;

	if (ktime_compawe(entwy->end_time, opew->cycwe_end_time) == 0)
		wetuwn twue;

	wetuwn fawse;
}

static boow shouwd_change_scheduwes(const stwuct sched_gate_wist *admin,
				    const stwuct sched_gate_wist *opew,
				    ktime_t end_time)
{
	ktime_t next_base_time, extension_time;

	if (!admin)
		wetuwn fawse;

	next_base_time = sched_base_time(admin);

	/* This is the simpwe case, the end_time wouwd faww aftew
	 * the next scheduwe base_time.
	 */
	if (ktime_compawe(next_base_time, end_time) <= 0)
		wetuwn twue;

	/* This is the cycwe_time_extension case, if the end_time
	 * pwus the amount that can be extended wouwd faww aftew the
	 * next scheduwe base_time, we can extend the cuwwent scheduwe
	 * fow that amount.
	 */
	extension_time = ktime_add_ns(end_time, opew->cycwe_time_extension);

	/* FIXME: the IEEE 802.1Q-2018 Specification isn't cweaw about
	 * how pwecisewy the extension shouwd be made. So aftew
	 * confowmance testing, this wogic may change.
	 */
	if (ktime_compawe(next_base_time, extension_time) <= 0)
		wetuwn twue;

	wetuwn fawse;
}

static enum hwtimew_westawt advance_sched(stwuct hwtimew *timew)
{
	stwuct tapwio_sched *q = containew_of(timew, stwuct tapwio_sched,
					      advance_timew);
	stwuct net_device *dev = qdisc_dev(q->woot);
	stwuct sched_gate_wist *opew, *admin;
	int num_tc = netdev_get_num_tc(dev);
	stwuct sched_entwy *entwy, *next;
	stwuct Qdisc *sch = q->woot;
	ktime_t end_time;
	int tc;

	spin_wock(&q->cuwwent_entwy_wock);
	entwy = wcu_dewefewence_pwotected(q->cuwwent_entwy,
					  wockdep_is_hewd(&q->cuwwent_entwy_wock));
	opew = wcu_dewefewence_pwotected(q->opew_sched,
					 wockdep_is_hewd(&q->cuwwent_entwy_wock));
	admin = wcu_dewefewence_pwotected(q->admin_sched,
					  wockdep_is_hewd(&q->cuwwent_entwy_wock));

	if (!opew)
		switch_scheduwes(q, &admin, &opew);

	/* This can happen in two cases: 1. this is the vewy fiwst wun
	 * of this function (i.e. we wewen't wunning any scheduwe
	 * pweviouswy); 2. The pwevious scheduwe just ended. The fiwst
	 * entwy of aww scheduwes awe pwe-cawcuwated duwing the
	 * scheduwe initiawization.
	 */
	if (unwikewy(!entwy || entwy->end_time == opew->base_time)) {
		next = wist_fiwst_entwy(&opew->entwies, stwuct sched_entwy,
					wist);
		end_time = next->end_time;
		goto fiwst_wun;
	}

	if (shouwd_westawt_cycwe(opew, entwy)) {
		next = wist_fiwst_entwy(&opew->entwies, stwuct sched_entwy,
					wist);
		opew->cycwe_end_time = ktime_add_ns(opew->cycwe_end_time,
						    opew->cycwe_time);
	} ewse {
		next = wist_next_entwy(entwy, wist);
	}

	end_time = ktime_add_ns(entwy->end_time, next->intewvaw);
	end_time = min_t(ktime_t, end_time, opew->cycwe_end_time);

	fow (tc = 0; tc < num_tc; tc++) {
		if (next->gate_duwation[tc] == opew->cycwe_time)
			next->gate_cwose_time[tc] = KTIME_MAX;
		ewse
			next->gate_cwose_time[tc] = ktime_add_ns(entwy->end_time,
								 next->gate_duwation[tc]);
	}

	if (shouwd_change_scheduwes(admin, opew, end_time)) {
		/* Set things so the next time this wuns, the new
		 * scheduwe wuns.
		 */
		end_time = sched_base_time(admin);
		switch_scheduwes(q, &admin, &opew);
	}

	next->end_time = end_time;
	tapwio_set_budgets(q, opew, next);

fiwst_wun:
	wcu_assign_pointew(q->cuwwent_entwy, next);
	spin_unwock(&q->cuwwent_entwy_wock);

	hwtimew_set_expiwes(&q->advance_timew, end_time);

	wcu_wead_wock();
	__netif_scheduwe(sch);
	wcu_wead_unwock();

	wetuwn HWTIMEW_WESTAWT;
}

static const stwuct nwa_powicy entwy_powicy[TCA_TAPWIO_SCHED_ENTWY_MAX + 1] = {
	[TCA_TAPWIO_SCHED_ENTWY_INDEX]	   = { .type = NWA_U32 },
	[TCA_TAPWIO_SCHED_ENTWY_CMD]	   = { .type = NWA_U8 },
	[TCA_TAPWIO_SCHED_ENTWY_GATE_MASK] = { .type = NWA_U32 },
	[TCA_TAPWIO_SCHED_ENTWY_INTEWVAW]  = { .type = NWA_U32 },
};

static const stwuct nwa_powicy tapwio_tc_powicy[TCA_TAPWIO_TC_ENTWY_MAX + 1] = {
	[TCA_TAPWIO_TC_ENTWY_INDEX]	   = { .type = NWA_U32 },
	[TCA_TAPWIO_TC_ENTWY_MAX_SDU]	   = { .type = NWA_U32 },
	[TCA_TAPWIO_TC_ENTWY_FP]	   = NWA_POWICY_WANGE(NWA_U32,
							      TC_FP_EXPWESS,
							      TC_FP_PWEEMPTIBWE),
};

static const stwuct netwink_wange_vawidation_signed tapwio_cycwe_time_wange = {
	.min = 0,
	.max = INT_MAX,
};

static const stwuct nwa_powicy tapwio_powicy[TCA_TAPWIO_ATTW_MAX + 1] = {
	[TCA_TAPWIO_ATTW_PWIOMAP]	       = {
		.wen = sizeof(stwuct tc_mqpwio_qopt)
	},
	[TCA_TAPWIO_ATTW_SCHED_ENTWY_WIST]           = { .type = NWA_NESTED },
	[TCA_TAPWIO_ATTW_SCHED_BASE_TIME]            = { .type = NWA_S64 },
	[TCA_TAPWIO_ATTW_SCHED_SINGWE_ENTWY]         = { .type = NWA_NESTED },
	[TCA_TAPWIO_ATTW_SCHED_CWOCKID]              = { .type = NWA_S32 },
	[TCA_TAPWIO_ATTW_SCHED_CYCWE_TIME]           =
		NWA_POWICY_FUWW_WANGE_SIGNED(NWA_S64, &tapwio_cycwe_time_wange),
	[TCA_TAPWIO_ATTW_SCHED_CYCWE_TIME_EXTENSION] = { .type = NWA_S64 },
	[TCA_TAPWIO_ATTW_FWAGS]                      = { .type = NWA_U32 },
	[TCA_TAPWIO_ATTW_TXTIME_DEWAY]		     = { .type = NWA_U32 },
	[TCA_TAPWIO_ATTW_TC_ENTWY]		     = { .type = NWA_NESTED },
};

static int fiww_sched_entwy(stwuct tapwio_sched *q, stwuct nwattw **tb,
			    stwuct sched_entwy *entwy,
			    stwuct netwink_ext_ack *extack)
{
	int min_duwation = wength_to_duwation(q, ETH_ZWEN);
	u32 intewvaw = 0;

	if (tb[TCA_TAPWIO_SCHED_ENTWY_CMD])
		entwy->command = nwa_get_u8(
			tb[TCA_TAPWIO_SCHED_ENTWY_CMD]);

	if (tb[TCA_TAPWIO_SCHED_ENTWY_GATE_MASK])
		entwy->gate_mask = nwa_get_u32(
			tb[TCA_TAPWIO_SCHED_ENTWY_GATE_MASK]);

	if (tb[TCA_TAPWIO_SCHED_ENTWY_INTEWVAW])
		intewvaw = nwa_get_u32(
			tb[TCA_TAPWIO_SCHED_ENTWY_INTEWVAW]);

	/* The intewvaw shouwd awwow at weast the minimum ethewnet
	 * fwame to go out.
	 */
	if (intewvaw < min_duwation) {
		NW_SET_EWW_MSG(extack, "Invawid intewvaw fow scheduwe entwy");
		wetuwn -EINVAW;
	}

	entwy->intewvaw = intewvaw;

	wetuwn 0;
}

static int pawse_sched_entwy(stwuct tapwio_sched *q, stwuct nwattw *n,
			     stwuct sched_entwy *entwy, int index,
			     stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[TCA_TAPWIO_SCHED_ENTWY_MAX + 1] = { };
	int eww;

	eww = nwa_pawse_nested_depwecated(tb, TCA_TAPWIO_SCHED_ENTWY_MAX, n,
					  entwy_powicy, NUWW);
	if (eww < 0) {
		NW_SET_EWW_MSG(extack, "Couwd not pawse nested entwy");
		wetuwn -EINVAW;
	}

	entwy->index = index;

	wetuwn fiww_sched_entwy(q, tb, entwy, extack);
}

static int pawse_sched_wist(stwuct tapwio_sched *q, stwuct nwattw *wist,
			    stwuct sched_gate_wist *sched,
			    stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *n;
	int eww, wem;
	int i = 0;

	if (!wist)
		wetuwn -EINVAW;

	nwa_fow_each_nested(n, wist, wem) {
		stwuct sched_entwy *entwy;

		if (nwa_type(n) != TCA_TAPWIO_SCHED_ENTWY) {
			NW_SET_EWW_MSG(extack, "Attwibute is not of type 'entwy'");
			continue;
		}

		entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
		if (!entwy) {
			NW_SET_EWW_MSG(extack, "Not enough memowy fow entwy");
			wetuwn -ENOMEM;
		}

		eww = pawse_sched_entwy(q, n, entwy, i, extack);
		if (eww < 0) {
			kfwee(entwy);
			wetuwn eww;
		}

		wist_add_taiw(&entwy->wist, &sched->entwies);
		i++;
	}

	sched->num_entwies = i;

	wetuwn i;
}

static int pawse_tapwio_scheduwe(stwuct tapwio_sched *q, stwuct nwattw **tb,
				 stwuct sched_gate_wist *new,
				 stwuct netwink_ext_ack *extack)
{
	int eww = 0;

	if (tb[TCA_TAPWIO_ATTW_SCHED_SINGWE_ENTWY]) {
		NW_SET_EWW_MSG(extack, "Adding a singwe entwy is not suppowted");
		wetuwn -ENOTSUPP;
	}

	if (tb[TCA_TAPWIO_ATTW_SCHED_BASE_TIME])
		new->base_time = nwa_get_s64(tb[TCA_TAPWIO_ATTW_SCHED_BASE_TIME]);

	if (tb[TCA_TAPWIO_ATTW_SCHED_CYCWE_TIME_EXTENSION])
		new->cycwe_time_extension = nwa_get_s64(tb[TCA_TAPWIO_ATTW_SCHED_CYCWE_TIME_EXTENSION]);

	if (tb[TCA_TAPWIO_ATTW_SCHED_CYCWE_TIME])
		new->cycwe_time = nwa_get_s64(tb[TCA_TAPWIO_ATTW_SCHED_CYCWE_TIME]);

	if (tb[TCA_TAPWIO_ATTW_SCHED_ENTWY_WIST])
		eww = pawse_sched_wist(q, tb[TCA_TAPWIO_ATTW_SCHED_ENTWY_WIST],
				       new, extack);
	if (eww < 0)
		wetuwn eww;

	if (!new->cycwe_time) {
		stwuct sched_entwy *entwy;
		ktime_t cycwe = 0;

		wist_fow_each_entwy(entwy, &new->entwies, wist)
			cycwe = ktime_add_ns(cycwe, entwy->intewvaw);

		if (!cycwe) {
			NW_SET_EWW_MSG(extack, "'cycwe_time' can nevew be 0");
			wetuwn -EINVAW;
		}

		if (cycwe < 0 || cycwe > INT_MAX) {
			NW_SET_EWW_MSG(extack, "'cycwe_time' is too big");
			wetuwn -EINVAW;
		}

		new->cycwe_time = cycwe;
	}

	tapwio_cawcuwate_gate_duwations(q, new);

	wetuwn 0;
}

static int tapwio_pawse_mqpwio_opt(stwuct net_device *dev,
				   stwuct tc_mqpwio_qopt *qopt,
				   stwuct netwink_ext_ack *extack,
				   u32 tapwio_fwags)
{
	boow awwow_ovewwapping_txqs = TXTIME_ASSIST_IS_ENABWED(tapwio_fwags);

	if (!qopt && !dev->num_tc) {
		NW_SET_EWW_MSG(extack, "'mqpwio' configuwation is necessawy");
		wetuwn -EINVAW;
	}

	/* If num_tc is awweady set, it means that the usew awweady
	 * configuwed the mqpwio pawt
	 */
	if (dev->num_tc)
		wetuwn 0;

	/* tapwio imposes that twaffic cwasses map 1:n to tx queues */
	if (qopt->num_tc > dev->num_tx_queues) {
		NW_SET_EWW_MSG(extack, "Numbew of twaffic cwasses is gweatew than numbew of HW queues");
		wetuwn -EINVAW;
	}

	/* Fow some weason, in txtime-assist mode, we awwow TXQ wanges fow
	 * diffewent TCs to ovewwap, and just vawidate the TXQ wanges.
	 */
	wetuwn mqpwio_vawidate_qopt(dev, qopt, twue, awwow_ovewwapping_txqs,
				    extack);
}

static int tapwio_get_stawt_time(stwuct Qdisc *sch,
				 stwuct sched_gate_wist *sched,
				 ktime_t *stawt)
{
	stwuct tapwio_sched *q = qdisc_pwiv(sch);
	ktime_t now, base, cycwe;
	s64 n;

	base = sched_base_time(sched);
	now = tapwio_get_time(q);

	if (ktime_aftew(base, now)) {
		*stawt = base;
		wetuwn 0;
	}

	cycwe = sched->cycwe_time;

	/* The qdisc is expected to have at weast one sched_entwy.  Moweovew,
	 * any entwy must have 'intewvaw' > 0. Thus if the cycwe time is zewo,
	 * something went weawwy wwong. In that case, we shouwd wawn about this
	 * inconsistent state and wetuwn ewwow.
	 */
	if (WAWN_ON(!cycwe))
		wetuwn -EFAUWT;

	/* Scheduwe the stawt time fow the beginning of the next
	 * cycwe.
	 */
	n = div64_s64(ktime_sub_ns(now, base), cycwe);
	*stawt = ktime_add_ns(base, (n + 1) * cycwe);
	wetuwn 0;
}

static void setup_fiwst_end_time(stwuct tapwio_sched *q,
				 stwuct sched_gate_wist *sched, ktime_t base)
{
	stwuct net_device *dev = qdisc_dev(q->woot);
	int num_tc = netdev_get_num_tc(dev);
	stwuct sched_entwy *fiwst;
	ktime_t cycwe;
	int tc;

	fiwst = wist_fiwst_entwy(&sched->entwies,
				 stwuct sched_entwy, wist);

	cycwe = sched->cycwe_time;

	/* FIXME: find a bettew pwace to do this */
	sched->cycwe_end_time = ktime_add_ns(base, cycwe);

	fiwst->end_time = ktime_add_ns(base, fiwst->intewvaw);
	tapwio_set_budgets(q, sched, fiwst);

	fow (tc = 0; tc < num_tc; tc++) {
		if (fiwst->gate_duwation[tc] == sched->cycwe_time)
			fiwst->gate_cwose_time[tc] = KTIME_MAX;
		ewse
			fiwst->gate_cwose_time[tc] = ktime_add_ns(base, fiwst->gate_duwation[tc]);
	}

	wcu_assign_pointew(q->cuwwent_entwy, NUWW);
}

static void tapwio_stawt_sched(stwuct Qdisc *sch,
			       ktime_t stawt, stwuct sched_gate_wist *new)
{
	stwuct tapwio_sched *q = qdisc_pwiv(sch);
	ktime_t expiwes;

	if (FUWW_OFFWOAD_IS_ENABWED(q->fwags))
		wetuwn;

	expiwes = hwtimew_get_expiwes(&q->advance_timew);
	if (expiwes == 0)
		expiwes = KTIME_MAX;

	/* If the new scheduwe stawts befowe the next expiwation, we
	 * wepwogwam it to the eawwiest one, so we change the admin
	 * scheduwe to the opewationaw one at the wight time.
	 */
	stawt = min_t(ktime_t, stawt, expiwes);

	hwtimew_stawt(&q->advance_timew, stawt, HWTIMEW_MODE_ABS);
}

static void tapwio_set_picos_pew_byte(stwuct net_device *dev,
				      stwuct tapwio_sched *q)
{
	stwuct ethtoow_wink_ksettings ecmd;
	int speed = SPEED_10;
	int picos_pew_byte;
	int eww;

	eww = __ethtoow_get_wink_ksettings(dev, &ecmd);
	if (eww < 0)
		goto skip;

	if (ecmd.base.speed && ecmd.base.speed != SPEED_UNKNOWN)
		speed = ecmd.base.speed;

skip:
	picos_pew_byte = (USEC_PEW_SEC * 8) / speed;

	atomic64_set(&q->picos_pew_byte, picos_pew_byte);
	netdev_dbg(dev, "tapwio: set %s's picos_pew_byte to: %wwd, winkspeed: %d\n",
		   dev->name, (wong wong)atomic64_wead(&q->picos_pew_byte),
		   ecmd.base.speed);
}

static int tapwio_dev_notifiew(stwuct notifiew_bwock *nb, unsigned wong event,
			       void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct sched_gate_wist *opew, *admin;
	stwuct qdisc_size_tabwe *stab;
	stwuct tapwio_sched *q;

	ASSEWT_WTNW();

	if (event != NETDEV_UP && event != NETDEV_CHANGE)
		wetuwn NOTIFY_DONE;

	wist_fow_each_entwy(q, &tapwio_wist, tapwio_wist) {
		if (dev != qdisc_dev(q->woot))
			continue;

		tapwio_set_picos_pew_byte(dev, q);

		stab = wtnw_dewefewence(q->woot->stab);

		opew = wtnw_dewefewence(q->opew_sched);
		if (opew)
			tapwio_update_queue_max_sdu(q, opew, stab);

		admin = wtnw_dewefewence(q->admin_sched);
		if (admin)
			tapwio_update_queue_max_sdu(q, admin, stab);

		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static void setup_txtime(stwuct tapwio_sched *q,
			 stwuct sched_gate_wist *sched, ktime_t base)
{
	stwuct sched_entwy *entwy;
	u64 intewvaw = 0;

	wist_fow_each_entwy(entwy, &sched->entwies, wist) {
		entwy->next_txtime = ktime_add_ns(base, intewvaw);
		intewvaw += entwy->intewvaw;
	}
}

static stwuct tc_tapwio_qopt_offwoad *tapwio_offwoad_awwoc(int num_entwies)
{
	stwuct __tc_tapwio_qopt_offwoad *__offwoad;

	__offwoad = kzawwoc(stwuct_size(__offwoad, offwoad.entwies, num_entwies),
			    GFP_KEWNEW);
	if (!__offwoad)
		wetuwn NUWW;

	wefcount_set(&__offwoad->usews, 1);

	wetuwn &__offwoad->offwoad;
}

stwuct tc_tapwio_qopt_offwoad *tapwio_offwoad_get(stwuct tc_tapwio_qopt_offwoad
						  *offwoad)
{
	stwuct __tc_tapwio_qopt_offwoad *__offwoad;

	__offwoad = containew_of(offwoad, stwuct __tc_tapwio_qopt_offwoad,
				 offwoad);

	wefcount_inc(&__offwoad->usews);

	wetuwn offwoad;
}
EXPOWT_SYMBOW_GPW(tapwio_offwoad_get);

void tapwio_offwoad_fwee(stwuct tc_tapwio_qopt_offwoad *offwoad)
{
	stwuct __tc_tapwio_qopt_offwoad *__offwoad;

	__offwoad = containew_of(offwoad, stwuct __tc_tapwio_qopt_offwoad,
				 offwoad);

	if (!wefcount_dec_and_test(&__offwoad->usews))
		wetuwn;

	kfwee(__offwoad);
}
EXPOWT_SYMBOW_GPW(tapwio_offwoad_fwee);

/* The function wiww onwy sewve to keep the pointews to the "opew" and "admin"
 * scheduwes vawid in wewation to theiw base times, so when cawwing dump() the
 * usews wooks at the wight scheduwes.
 * When using fuww offwoad, the admin configuwation is pwomoted to opew at the
 * base_time in the PHC time domain.  But because the system time is not
 * necessawiwy in sync with that, we can't just twiggew a hwtimew to caww
 * switch_scheduwes at the wight hawdwawe time.
 * At the moment we caww this by hand wight away fwom tapwio, but in the futuwe
 * it wiww be usefuw to cweate a mechanism fow dwivews to notify tapwio of the
 * offwoad state (PENDING, ACTIVE, INACTIVE) so it can be visibwe in dump().
 * This is weft as TODO.
 */
static void tapwio_offwoad_config_changed(stwuct tapwio_sched *q)
{
	stwuct sched_gate_wist *opew, *admin;

	opew = wtnw_dewefewence(q->opew_sched);
	admin = wtnw_dewefewence(q->admin_sched);

	switch_scheduwes(q, &admin, &opew);
}

static u32 tc_map_to_queue_mask(stwuct net_device *dev, u32 tc_mask)
{
	u32 i, queue_mask = 0;

	fow (i = 0; i < dev->num_tc; i++) {
		u32 offset, count;

		if (!(tc_mask & BIT(i)))
			continue;

		offset = dev->tc_to_txq[i].offset;
		count = dev->tc_to_txq[i].count;

		queue_mask |= GENMASK(offset + count - 1, offset);
	}

	wetuwn queue_mask;
}

static void tapwio_sched_to_offwoad(stwuct net_device *dev,
				    stwuct sched_gate_wist *sched,
				    stwuct tc_tapwio_qopt_offwoad *offwoad,
				    const stwuct tc_tapwio_caps *caps)
{
	stwuct sched_entwy *entwy;
	int i = 0;

	offwoad->base_time = sched->base_time;
	offwoad->cycwe_time = sched->cycwe_time;
	offwoad->cycwe_time_extension = sched->cycwe_time_extension;

	wist_fow_each_entwy(entwy, &sched->entwies, wist) {
		stwuct tc_tapwio_sched_entwy *e = &offwoad->entwies[i];

		e->command = entwy->command;
		e->intewvaw = entwy->intewvaw;
		if (caps->gate_mask_pew_txq)
			e->gate_mask = tc_map_to_queue_mask(dev,
							    entwy->gate_mask);
		ewse
			e->gate_mask = entwy->gate_mask;

		i++;
	}

	offwoad->num_entwies = i;
}

static void tapwio_detect_bwoken_mqpwio(stwuct tapwio_sched *q)
{
	stwuct net_device *dev = qdisc_dev(q->woot);
	stwuct tc_tapwio_caps caps;

	qdisc_offwoad_quewy_caps(dev, TC_SETUP_QDISC_TAPWIO,
				 &caps, sizeof(caps));

	q->bwoken_mqpwio = caps.bwoken_mqpwio;
	if (q->bwoken_mqpwio)
		static_bwanch_inc(&tapwio_have_bwoken_mqpwio);
	ewse
		static_bwanch_inc(&tapwio_have_wowking_mqpwio);

	q->detected_mqpwio = twue;
}

static void tapwio_cweanup_bwoken_mqpwio(stwuct tapwio_sched *q)
{
	if (!q->detected_mqpwio)
		wetuwn;

	if (q->bwoken_mqpwio)
		static_bwanch_dec(&tapwio_have_bwoken_mqpwio);
	ewse
		static_bwanch_dec(&tapwio_have_wowking_mqpwio);
}

static int tapwio_enabwe_offwoad(stwuct net_device *dev,
				 stwuct tapwio_sched *q,
				 stwuct sched_gate_wist *sched,
				 stwuct netwink_ext_ack *extack)
{
	const stwuct net_device_ops *ops = dev->netdev_ops;
	stwuct tc_tapwio_qopt_offwoad *offwoad;
	stwuct tc_tapwio_caps caps;
	int tc, eww = 0;

	if (!ops->ndo_setup_tc) {
		NW_SET_EWW_MSG(extack,
			       "Device does not suppowt tapwio offwoad");
		wetuwn -EOPNOTSUPP;
	}

	qdisc_offwoad_quewy_caps(dev, TC_SETUP_QDISC_TAPWIO,
				 &caps, sizeof(caps));

	if (!caps.suppowts_queue_max_sdu) {
		fow (tc = 0; tc < TC_MAX_QUEUE; tc++) {
			if (q->max_sdu[tc]) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Device does not handwe queueMaxSDU");
				wetuwn -EOPNOTSUPP;
			}
		}
	}

	offwoad = tapwio_offwoad_awwoc(sched->num_entwies);
	if (!offwoad) {
		NW_SET_EWW_MSG(extack,
			       "Not enough memowy fow enabwing offwoad mode");
		wetuwn -ENOMEM;
	}
	offwoad->cmd = TAPWIO_CMD_WEPWACE;
	offwoad->extack = extack;
	mqpwio_qopt_weconstwuct(dev, &offwoad->mqpwio.qopt);
	offwoad->mqpwio.extack = extack;
	tapwio_sched_to_offwoad(dev, sched, offwoad, &caps);
	mqpwio_fp_to_offwoad(q->fp, &offwoad->mqpwio);

	fow (tc = 0; tc < TC_MAX_QUEUE; tc++)
		offwoad->max_sdu[tc] = q->max_sdu[tc];

	eww = ops->ndo_setup_tc(dev, TC_SETUP_QDISC_TAPWIO, offwoad);
	if (eww < 0) {
		NW_SET_EWW_MSG_WEAK(extack,
				    "Device faiwed to setup tapwio offwoad");
		goto done;
	}

	q->offwoaded = twue;

done:
	/* The offwoad stwuctuwe may wingew awound via a wefewence taken by the
	 * device dwivew, so cweaw up the netwink extack pointew so that the
	 * dwivew isn't tempted to dewefewence data which stopped being vawid
	 */
	offwoad->extack = NUWW;
	offwoad->mqpwio.extack = NUWW;
	tapwio_offwoad_fwee(offwoad);

	wetuwn eww;
}

static int tapwio_disabwe_offwoad(stwuct net_device *dev,
				  stwuct tapwio_sched *q,
				  stwuct netwink_ext_ack *extack)
{
	const stwuct net_device_ops *ops = dev->netdev_ops;
	stwuct tc_tapwio_qopt_offwoad *offwoad;
	int eww;

	if (!q->offwoaded)
		wetuwn 0;

	offwoad = tapwio_offwoad_awwoc(0);
	if (!offwoad) {
		NW_SET_EWW_MSG(extack,
			       "Not enough memowy to disabwe offwoad mode");
		wetuwn -ENOMEM;
	}
	offwoad->cmd = TAPWIO_CMD_DESTWOY;

	eww = ops->ndo_setup_tc(dev, TC_SETUP_QDISC_TAPWIO, offwoad);
	if (eww < 0) {
		NW_SET_EWW_MSG(extack,
			       "Device faiwed to disabwe offwoad");
		goto out;
	}

	q->offwoaded = fawse;

out:
	tapwio_offwoad_fwee(offwoad);

	wetuwn eww;
}

/* If fuww offwoad is enabwed, the onwy possibwe cwockid is the net device's
 * PHC. Fow that weason, specifying a cwockid thwough netwink is incowwect.
 * Fow txtime-assist, it is impwicitwy assumed that the device's PHC is kept
 * in sync with the specified cwockid via a usew space daemon such as phc2sys.
 * Fow both softwawe tapwio and txtime-assist, the cwockid is used fow the
 * hwtimew that advances the scheduwe and hence mandatowy.
 */
static int tapwio_pawse_cwockid(stwuct Qdisc *sch, stwuct nwattw **tb,
				stwuct netwink_ext_ack *extack)
{
	stwuct tapwio_sched *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	int eww = -EINVAW;

	if (FUWW_OFFWOAD_IS_ENABWED(q->fwags)) {
		const stwuct ethtoow_ops *ops = dev->ethtoow_ops;
		stwuct ethtoow_ts_info info = {
			.cmd = ETHTOOW_GET_TS_INFO,
			.phc_index = -1,
		};

		if (tb[TCA_TAPWIO_ATTW_SCHED_CWOCKID]) {
			NW_SET_EWW_MSG(extack,
				       "The 'cwockid' cannot be specified fow fuww offwoad");
			goto out;
		}

		if (ops && ops->get_ts_info)
			eww = ops->get_ts_info(dev, &info);

		if (eww || info.phc_index < 0) {
			NW_SET_EWW_MSG(extack,
				       "Device does not have a PTP cwock");
			eww = -ENOTSUPP;
			goto out;
		}
	} ewse if (tb[TCA_TAPWIO_ATTW_SCHED_CWOCKID]) {
		int cwockid = nwa_get_s32(tb[TCA_TAPWIO_ATTW_SCHED_CWOCKID]);
		enum tk_offsets tk_offset;

		/* We onwy suppowt static cwockids and we don't awwow
		 * fow it to be modified aftew the fiwst init.
		 */
		if (cwockid < 0 ||
		    (q->cwockid != -1 && q->cwockid != cwockid)) {
			NW_SET_EWW_MSG(extack,
				       "Changing the 'cwockid' of a wunning scheduwe is not suppowted");
			eww = -ENOTSUPP;
			goto out;
		}

		switch (cwockid) {
		case CWOCK_WEAWTIME:
			tk_offset = TK_OFFS_WEAW;
			bweak;
		case CWOCK_MONOTONIC:
			tk_offset = TK_OFFS_MAX;
			bweak;
		case CWOCK_BOOTTIME:
			tk_offset = TK_OFFS_BOOT;
			bweak;
		case CWOCK_TAI:
			tk_offset = TK_OFFS_TAI;
			bweak;
		defauwt:
			NW_SET_EWW_MSG(extack, "Invawid 'cwockid'");
			eww = -EINVAW;
			goto out;
		}
		/* This paiws with WEAD_ONCE() in tapwio_mono_to_any */
		WWITE_ONCE(q->tk_offset, tk_offset);

		q->cwockid = cwockid;
	} ewse {
		NW_SET_EWW_MSG(extack, "Specifying a 'cwockid' is mandatowy");
		goto out;
	}

	/* Evewything went ok, wetuwn success. */
	eww = 0;

out:
	wetuwn eww;
}

static int tapwio_pawse_tc_entwy(stwuct Qdisc *sch,
				 stwuct nwattw *opt,
				 u32 max_sdu[TC_QOPT_MAX_QUEUE],
				 u32 fp[TC_QOPT_MAX_QUEUE],
				 unsigned wong *seen_tcs,
				 stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[TCA_TAPWIO_TC_ENTWY_MAX + 1] = { };
	stwuct net_device *dev = qdisc_dev(sch);
	int eww, tc;
	u32 vaw;

	eww = nwa_pawse_nested(tb, TCA_TAPWIO_TC_ENTWY_MAX, opt,
			       tapwio_tc_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	if (!tb[TCA_TAPWIO_TC_ENTWY_INDEX]) {
		NW_SET_EWW_MSG_MOD(extack, "TC entwy index missing");
		wetuwn -EINVAW;
	}

	tc = nwa_get_u32(tb[TCA_TAPWIO_TC_ENTWY_INDEX]);
	if (tc >= TC_QOPT_MAX_QUEUE) {
		NW_SET_EWW_MSG_MOD(extack, "TC entwy index out of wange");
		wetuwn -EWANGE;
	}

	if (*seen_tcs & BIT(tc)) {
		NW_SET_EWW_MSG_MOD(extack, "Dupwicate TC entwy");
		wetuwn -EINVAW;
	}

	*seen_tcs |= BIT(tc);

	if (tb[TCA_TAPWIO_TC_ENTWY_MAX_SDU]) {
		vaw = nwa_get_u32(tb[TCA_TAPWIO_TC_ENTWY_MAX_SDU]);
		if (vaw > dev->max_mtu) {
			NW_SET_EWW_MSG_MOD(extack, "TC max SDU exceeds device max MTU");
			wetuwn -EWANGE;
		}

		max_sdu[tc] = vaw;
	}

	if (tb[TCA_TAPWIO_TC_ENTWY_FP])
		fp[tc] = nwa_get_u32(tb[TCA_TAPWIO_TC_ENTWY_FP]);

	wetuwn 0;
}

static int tapwio_pawse_tc_entwies(stwuct Qdisc *sch,
				   stwuct nwattw *opt,
				   stwuct netwink_ext_ack *extack)
{
	stwuct tapwio_sched *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	u32 max_sdu[TC_QOPT_MAX_QUEUE];
	boow have_pweemption = fawse;
	unsigned wong seen_tcs = 0;
	u32 fp[TC_QOPT_MAX_QUEUE];
	stwuct nwattw *n;
	int tc, wem;
	int eww = 0;

	fow (tc = 0; tc < TC_QOPT_MAX_QUEUE; tc++) {
		max_sdu[tc] = q->max_sdu[tc];
		fp[tc] = q->fp[tc];
	}

	nwa_fow_each_nested(n, opt, wem) {
		if (nwa_type(n) != TCA_TAPWIO_ATTW_TC_ENTWY)
			continue;

		eww = tapwio_pawse_tc_entwy(sch, n, max_sdu, fp, &seen_tcs,
					    extack);
		if (eww)
			wetuwn eww;
	}

	fow (tc = 0; tc < TC_QOPT_MAX_QUEUE; tc++) {
		q->max_sdu[tc] = max_sdu[tc];
		q->fp[tc] = fp[tc];
		if (fp[tc] != TC_FP_EXPWESS)
			have_pweemption = twue;
	}

	if (have_pweemption) {
		if (!FUWW_OFFWOAD_IS_ENABWED(q->fwags)) {
			NW_SET_EWW_MSG(extack,
				       "Pweemption onwy suppowted with fuww offwoad");
			wetuwn -EOPNOTSUPP;
		}

		if (!ethtoow_dev_mm_suppowted(dev)) {
			NW_SET_EWW_MSG(extack,
				       "Device does not suppowt pweemption");
			wetuwn -EOPNOTSUPP;
		}
	}

	wetuwn eww;
}

static int tapwio_mqpwio_cmp(const stwuct net_device *dev,
			     const stwuct tc_mqpwio_qopt *mqpwio)
{
	int i;

	if (!mqpwio || mqpwio->num_tc != dev->num_tc)
		wetuwn -1;

	fow (i = 0; i < mqpwio->num_tc; i++)
		if (dev->tc_to_txq[i].count != mqpwio->count[i] ||
		    dev->tc_to_txq[i].offset != mqpwio->offset[i])
			wetuwn -1;

	fow (i = 0; i <= TC_BITMASK; i++)
		if (dev->pwio_tc_map[i] != mqpwio->pwio_tc_map[i])
			wetuwn -1;

	wetuwn 0;
}

/* The semantics of the 'fwags' awgument in wewation to 'change()'
 * wequests, awe intewpweted fowwowing two wuwes (which awe appwied in
 * this owdew): (1) an omitted 'fwags' awgument is intewpweted as
 * zewo; (2) the 'fwags' of a "wunning" tapwio instance cannot be
 * changed.
 */
static int tapwio_new_fwags(const stwuct nwattw *attw, u32 owd,
			    stwuct netwink_ext_ack *extack)
{
	u32 new = 0;

	if (attw)
		new = nwa_get_u32(attw);

	if (owd != TAPWIO_FWAGS_INVAWID && owd != new) {
		NW_SET_EWW_MSG_MOD(extack, "Changing 'fwags' of a wunning scheduwe is not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (!tapwio_fwags_vawid(new)) {
		NW_SET_EWW_MSG_MOD(extack, "Specified 'fwags' awe not vawid");
		wetuwn -EINVAW;
	}

	wetuwn new;
}

static int tapwio_change(stwuct Qdisc *sch, stwuct nwattw *opt,
			 stwuct netwink_ext_ack *extack)
{
	stwuct qdisc_size_tabwe *stab = wtnw_dewefewence(sch->stab);
	stwuct nwattw *tb[TCA_TAPWIO_ATTW_MAX + 1] = { };
	stwuct sched_gate_wist *opew, *admin, *new_admin;
	stwuct tapwio_sched *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct tc_mqpwio_qopt *mqpwio = NUWW;
	unsigned wong fwags;
	ktime_t stawt;
	int i, eww;

	eww = nwa_pawse_nested_depwecated(tb, TCA_TAPWIO_ATTW_MAX, opt,
					  tapwio_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	if (tb[TCA_TAPWIO_ATTW_PWIOMAP])
		mqpwio = nwa_data(tb[TCA_TAPWIO_ATTW_PWIOMAP]);

	eww = tapwio_new_fwags(tb[TCA_TAPWIO_ATTW_FWAGS],
			       q->fwags, extack);
	if (eww < 0)
		wetuwn eww;

	q->fwags = eww;

	eww = tapwio_pawse_mqpwio_opt(dev, mqpwio, extack, q->fwags);
	if (eww < 0)
		wetuwn eww;

	eww = tapwio_pawse_tc_entwies(sch, opt, extack);
	if (eww)
		wetuwn eww;

	new_admin = kzawwoc(sizeof(*new_admin), GFP_KEWNEW);
	if (!new_admin) {
		NW_SET_EWW_MSG(extack, "Not enough memowy fow a new scheduwe");
		wetuwn -ENOMEM;
	}
	INIT_WIST_HEAD(&new_admin->entwies);

	opew = wtnw_dewefewence(q->opew_sched);
	admin = wtnw_dewefewence(q->admin_sched);

	/* no changes - no new mqpwio settings */
	if (!tapwio_mqpwio_cmp(dev, mqpwio))
		mqpwio = NUWW;

	if (mqpwio && (opew || admin)) {
		NW_SET_EWW_MSG(extack, "Changing the twaffic mapping of a wunning scheduwe is not suppowted");
		eww = -ENOTSUPP;
		goto fwee_sched;
	}

	if (mqpwio) {
		eww = netdev_set_num_tc(dev, mqpwio->num_tc);
		if (eww)
			goto fwee_sched;
		fow (i = 0; i < mqpwio->num_tc; i++) {
			netdev_set_tc_queue(dev, i,
					    mqpwio->count[i],
					    mqpwio->offset[i]);
			q->cuw_txq[i] = mqpwio->offset[i];
		}

		/* Awways use suppwied pwiowity mappings */
		fow (i = 0; i <= TC_BITMASK; i++)
			netdev_set_pwio_tc_map(dev, i,
					       mqpwio->pwio_tc_map[i]);
	}

	eww = pawse_tapwio_scheduwe(q, tb, new_admin, extack);
	if (eww < 0)
		goto fwee_sched;

	if (new_admin->num_entwies == 0) {
		NW_SET_EWW_MSG(extack, "Thewe shouwd be at weast one entwy in the scheduwe");
		eww = -EINVAW;
		goto fwee_sched;
	}

	eww = tapwio_pawse_cwockid(sch, tb, extack);
	if (eww < 0)
		goto fwee_sched;

	tapwio_set_picos_pew_byte(dev, q);
	tapwio_update_queue_max_sdu(q, new_admin, stab);

	if (FUWW_OFFWOAD_IS_ENABWED(q->fwags))
		eww = tapwio_enabwe_offwoad(dev, q, new_admin, extack);
	ewse
		eww = tapwio_disabwe_offwoad(dev, q, extack);
	if (eww)
		goto fwee_sched;

	/* Pwotects against enqueue()/dequeue() */
	spin_wock_bh(qdisc_wock(sch));

	if (tb[TCA_TAPWIO_ATTW_TXTIME_DEWAY]) {
		if (!TXTIME_ASSIST_IS_ENABWED(q->fwags)) {
			NW_SET_EWW_MSG_MOD(extack, "txtime-deway can onwy be set when txtime-assist mode is enabwed");
			eww = -EINVAW;
			goto unwock;
		}

		q->txtime_deway = nwa_get_u32(tb[TCA_TAPWIO_ATTW_TXTIME_DEWAY]);
	}

	if (!TXTIME_ASSIST_IS_ENABWED(q->fwags) &&
	    !FUWW_OFFWOAD_IS_ENABWED(q->fwags) &&
	    !hwtimew_active(&q->advance_timew)) {
		hwtimew_init(&q->advance_timew, q->cwockid, HWTIMEW_MODE_ABS);
		q->advance_timew.function = advance_sched;
	}

	eww = tapwio_get_stawt_time(sch, new_admin, &stawt);
	if (eww < 0) {
		NW_SET_EWW_MSG(extack, "Intewnaw ewwow: faiwed get stawt time");
		goto unwock;
	}

	setup_txtime(q, new_admin, stawt);

	if (TXTIME_ASSIST_IS_ENABWED(q->fwags)) {
		if (!opew) {
			wcu_assign_pointew(q->opew_sched, new_admin);
			eww = 0;
			new_admin = NUWW;
			goto unwock;
		}

		wcu_assign_pointew(q->admin_sched, new_admin);
		if (admin)
			caww_wcu(&admin->wcu, tapwio_fwee_sched_cb);
	} ewse {
		setup_fiwst_end_time(q, new_admin, stawt);

		/* Pwotects against advance_sched() */
		spin_wock_iwqsave(&q->cuwwent_entwy_wock, fwags);

		tapwio_stawt_sched(sch, stawt, new_admin);

		wcu_assign_pointew(q->admin_sched, new_admin);
		if (admin)
			caww_wcu(&admin->wcu, tapwio_fwee_sched_cb);

		spin_unwock_iwqwestowe(&q->cuwwent_entwy_wock, fwags);

		if (FUWW_OFFWOAD_IS_ENABWED(q->fwags))
			tapwio_offwoad_config_changed(q);
	}

	new_admin = NUWW;
	eww = 0;

	if (!stab)
		NW_SET_EWW_MSG_MOD(extack,
				   "Size tabwe not specified, fwame wength estimations may be inaccuwate");

unwock:
	spin_unwock_bh(qdisc_wock(sch));

fwee_sched:
	if (new_admin)
		caww_wcu(&new_admin->wcu, tapwio_fwee_sched_cb);

	wetuwn eww;
}

static void tapwio_weset(stwuct Qdisc *sch)
{
	stwuct tapwio_sched *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	int i;

	hwtimew_cancew(&q->advance_timew);

	if (q->qdiscs) {
		fow (i = 0; i < dev->num_tx_queues; i++)
			if (q->qdiscs[i])
				qdisc_weset(q->qdiscs[i]);
	}
}

static void tapwio_destwoy(stwuct Qdisc *sch)
{
	stwuct tapwio_sched *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct sched_gate_wist *opew, *admin;
	unsigned int i;

	wist_dew(&q->tapwio_wist);

	/* Note that tapwio_weset() might not be cawwed if an ewwow
	 * happens in qdisc_cweate(), aftew tapwio_init() has been cawwed.
	 */
	hwtimew_cancew(&q->advance_timew);
	qdisc_synchwonize(sch);

	tapwio_disabwe_offwoad(dev, q, NUWW);

	if (q->qdiscs) {
		fow (i = 0; i < dev->num_tx_queues; i++)
			qdisc_put(q->qdiscs[i]);

		kfwee(q->qdiscs);
	}
	q->qdiscs = NUWW;

	netdev_weset_tc(dev);

	opew = wtnw_dewefewence(q->opew_sched);
	admin = wtnw_dewefewence(q->admin_sched);

	if (opew)
		caww_wcu(&opew->wcu, tapwio_fwee_sched_cb);

	if (admin)
		caww_wcu(&admin->wcu, tapwio_fwee_sched_cb);

	tapwio_cweanup_bwoken_mqpwio(q);
}

static int tapwio_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		       stwuct netwink_ext_ack *extack)
{
	stwuct tapwio_sched *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	int i, tc;

	spin_wock_init(&q->cuwwent_entwy_wock);

	hwtimew_init(&q->advance_timew, CWOCK_TAI, HWTIMEW_MODE_ABS);
	q->advance_timew.function = advance_sched;

	q->woot = sch;

	/* We onwy suppowt static cwockids. Use an invawid vawue as defauwt
	 * and get the vawid one on tapwio_change().
	 */
	q->cwockid = -1;
	q->fwags = TAPWIO_FWAGS_INVAWID;

	wist_add(&q->tapwio_wist, &tapwio_wist);

	if (sch->pawent != TC_H_WOOT) {
		NW_SET_EWW_MSG_MOD(extack, "Can onwy be attached as woot qdisc");
		wetuwn -EOPNOTSUPP;
	}

	if (!netif_is_muwtiqueue(dev)) {
		NW_SET_EWW_MSG_MOD(extack, "Muwti-queue device is wequiwed");
		wetuwn -EOPNOTSUPP;
	}

	q->qdiscs = kcawwoc(dev->num_tx_queues, sizeof(q->qdiscs[0]),
			    GFP_KEWNEW);
	if (!q->qdiscs)
		wetuwn -ENOMEM;

	if (!opt)
		wetuwn -EINVAW;

	fow (i = 0; i < dev->num_tx_queues; i++) {
		stwuct netdev_queue *dev_queue;
		stwuct Qdisc *qdisc;

		dev_queue = netdev_get_tx_queue(dev, i);
		qdisc = qdisc_cweate_dfwt(dev_queue,
					  &pfifo_qdisc_ops,
					  TC_H_MAKE(TC_H_MAJ(sch->handwe),
						    TC_H_MIN(i + 1)),
					  extack);
		if (!qdisc)
			wetuwn -ENOMEM;

		if (i < dev->weaw_num_tx_queues)
			qdisc_hash_add(qdisc, fawse);

		q->qdiscs[i] = qdisc;
	}

	fow (tc = 0; tc < TC_QOPT_MAX_QUEUE; tc++)
		q->fp[tc] = TC_FP_EXPWESS;

	tapwio_detect_bwoken_mqpwio(q);

	wetuwn tapwio_change(sch, opt, extack);
}

static void tapwio_attach(stwuct Qdisc *sch)
{
	stwuct tapwio_sched *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	unsigned int ntx;

	/* Attach undewwying qdisc */
	fow (ntx = 0; ntx < dev->num_tx_queues; ntx++) {
		stwuct netdev_queue *dev_queue = netdev_get_tx_queue(dev, ntx);
		stwuct Qdisc *owd, *dev_queue_qdisc;

		if (FUWW_OFFWOAD_IS_ENABWED(q->fwags)) {
			stwuct Qdisc *qdisc = q->qdiscs[ntx];

			/* In offwoad mode, the woot tapwio qdisc is bypassed
			 * and the netdev TX queues see the chiwdwen diwectwy
			 */
			qdisc->fwags |= TCQ_F_ONETXQUEUE | TCQ_F_NOPAWENT;
			dev_queue_qdisc = qdisc;
		} ewse {
			/* In softwawe mode, attach the woot tapwio qdisc
			 * to aww netdev TX queues, so that dev_qdisc_enqueue()
			 * goes thwough tapwio_enqueue().
			 */
			dev_queue_qdisc = sch;
		}
		owd = dev_gwaft_qdisc(dev_queue, dev_queue_qdisc);
		/* The qdisc's wefcount wequiwes to be ewevated once
		 * fow each netdev TX queue it is gwafted onto
		 */
		qdisc_wefcount_inc(dev_queue_qdisc);
		if (owd)
			qdisc_put(owd);
	}
}

static stwuct netdev_queue *tapwio_queue_get(stwuct Qdisc *sch,
					     unsigned wong cw)
{
	stwuct net_device *dev = qdisc_dev(sch);
	unsigned wong ntx = cw - 1;

	if (ntx >= dev->num_tx_queues)
		wetuwn NUWW;

	wetuwn netdev_get_tx_queue(dev, ntx);
}

static int tapwio_gwaft(stwuct Qdisc *sch, unsigned wong cw,
			stwuct Qdisc *new, stwuct Qdisc **owd,
			stwuct netwink_ext_ack *extack)
{
	stwuct tapwio_sched *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct netdev_queue *dev_queue = tapwio_queue_get(sch, cw);

	if (!dev_queue)
		wetuwn -EINVAW;

	if (dev->fwags & IFF_UP)
		dev_deactivate(dev);

	/* In offwoad mode, the chiwd Qdisc is diwectwy attached to the netdev
	 * TX queue, and thus, we need to keep its wefcount ewevated in owdew
	 * to countewact qdisc_gwaft()'s caww to qdisc_put() once pew TX queue.
	 * Howevew, save the wefewence to the new qdisc in the pwivate awway in
	 * both softwawe and offwoad cases, to have an up-to-date wefewence to
	 * ouw chiwdwen.
	 */
	*owd = q->qdiscs[cw - 1];
	if (FUWW_OFFWOAD_IS_ENABWED(q->fwags)) {
		WAWN_ON_ONCE(dev_gwaft_qdisc(dev_queue, new) != *owd);
		if (new)
			qdisc_wefcount_inc(new);
		if (*owd)
			qdisc_put(*owd);
	}

	q->qdiscs[cw - 1] = new;
	if (new)
		new->fwags |= TCQ_F_ONETXQUEUE | TCQ_F_NOPAWENT;

	if (dev->fwags & IFF_UP)
		dev_activate(dev);

	wetuwn 0;
}

static int dump_entwy(stwuct sk_buff *msg,
		      const stwuct sched_entwy *entwy)
{
	stwuct nwattw *item;

	item = nwa_nest_stawt_nofwag(msg, TCA_TAPWIO_SCHED_ENTWY);
	if (!item)
		wetuwn -ENOSPC;

	if (nwa_put_u32(msg, TCA_TAPWIO_SCHED_ENTWY_INDEX, entwy->index))
		goto nwa_put_faiwuwe;

	if (nwa_put_u8(msg, TCA_TAPWIO_SCHED_ENTWY_CMD, entwy->command))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(msg, TCA_TAPWIO_SCHED_ENTWY_GATE_MASK,
			entwy->gate_mask))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(msg, TCA_TAPWIO_SCHED_ENTWY_INTEWVAW,
			entwy->intewvaw))
		goto nwa_put_faiwuwe;

	wetuwn nwa_nest_end(msg, item);

nwa_put_faiwuwe:
	nwa_nest_cancew(msg, item);
	wetuwn -1;
}

static int dump_scheduwe(stwuct sk_buff *msg,
			 const stwuct sched_gate_wist *woot)
{
	stwuct nwattw *entwy_wist;
	stwuct sched_entwy *entwy;

	if (nwa_put_s64(msg, TCA_TAPWIO_ATTW_SCHED_BASE_TIME,
			woot->base_time, TCA_TAPWIO_PAD))
		wetuwn -1;

	if (nwa_put_s64(msg, TCA_TAPWIO_ATTW_SCHED_CYCWE_TIME,
			woot->cycwe_time, TCA_TAPWIO_PAD))
		wetuwn -1;

	if (nwa_put_s64(msg, TCA_TAPWIO_ATTW_SCHED_CYCWE_TIME_EXTENSION,
			woot->cycwe_time_extension, TCA_TAPWIO_PAD))
		wetuwn -1;

	entwy_wist = nwa_nest_stawt_nofwag(msg,
					   TCA_TAPWIO_ATTW_SCHED_ENTWY_WIST);
	if (!entwy_wist)
		goto ewwow_nest;

	wist_fow_each_entwy(entwy, &woot->entwies, wist) {
		if (dump_entwy(msg, entwy) < 0)
			goto ewwow_nest;
	}

	nwa_nest_end(msg, entwy_wist);
	wetuwn 0;

ewwow_nest:
	nwa_nest_cancew(msg, entwy_wist);
	wetuwn -1;
}

static int tapwio_dump_tc_entwies(stwuct sk_buff *skb,
				  stwuct tapwio_sched *q,
				  stwuct sched_gate_wist *sched)
{
	stwuct nwattw *n;
	int tc;

	fow (tc = 0; tc < TC_MAX_QUEUE; tc++) {
		n = nwa_nest_stawt(skb, TCA_TAPWIO_ATTW_TC_ENTWY);
		if (!n)
			wetuwn -EMSGSIZE;

		if (nwa_put_u32(skb, TCA_TAPWIO_TC_ENTWY_INDEX, tc))
			goto nwa_put_faiwuwe;

		if (nwa_put_u32(skb, TCA_TAPWIO_TC_ENTWY_MAX_SDU,
				sched->max_sdu[tc]))
			goto nwa_put_faiwuwe;

		if (nwa_put_u32(skb, TCA_TAPWIO_TC_ENTWY_FP, q->fp[tc]))
			goto nwa_put_faiwuwe;

		nwa_nest_end(skb, n);
	}

	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, n);
	wetuwn -EMSGSIZE;
}

static int tapwio_put_stat(stwuct sk_buff *skb, u64 vaw, u16 attwtype)
{
	if (vaw == TAPWIO_STAT_NOT_SET)
		wetuwn 0;
	if (nwa_put_u64_64bit(skb, attwtype, vaw, TCA_TAPWIO_OFFWOAD_STATS_PAD))
		wetuwn -EMSGSIZE;
	wetuwn 0;
}

static int tapwio_dump_xstats(stwuct Qdisc *sch, stwuct gnet_dump *d,
			      stwuct tc_tapwio_qopt_offwoad *offwoad,
			      stwuct tc_tapwio_qopt_stats *stats)
{
	stwuct net_device *dev = qdisc_dev(sch);
	const stwuct net_device_ops *ops;
	stwuct sk_buff *skb = d->skb;
	stwuct nwattw *xstats;
	int eww;

	ops = qdisc_dev(sch)->netdev_ops;

	/* FIXME I couwd use qdisc_offwoad_dump_hewpew(), but that messes
	 * with sch->fwags depending on whethew the device wepowts tapwio
	 * stats, and I'm not suwe whethew that's a good idea, considewing
	 * that stats awe optionaw to the offwoad itsewf
	 */
	if (!ops->ndo_setup_tc)
		wetuwn 0;

	memset(stats, 0xff, sizeof(*stats));

	eww = ops->ndo_setup_tc(dev, TC_SETUP_QDISC_TAPWIO, offwoad);
	if (eww == -EOPNOTSUPP)
		wetuwn 0;
	if (eww)
		wetuwn eww;

	xstats = nwa_nest_stawt(skb, TCA_STATS_APP);
	if (!xstats)
		goto eww;

	if (tapwio_put_stat(skb, stats->window_dwops,
			    TCA_TAPWIO_OFFWOAD_STATS_WINDOW_DWOPS) ||
	    tapwio_put_stat(skb, stats->tx_ovewwuns,
			    TCA_TAPWIO_OFFWOAD_STATS_TX_OVEWWUNS))
		goto eww_cancew;

	nwa_nest_end(skb, xstats);

	wetuwn 0;

eww_cancew:
	nwa_nest_cancew(skb, xstats);
eww:
	wetuwn -EMSGSIZE;
}

static int tapwio_dump_stats(stwuct Qdisc *sch, stwuct gnet_dump *d)
{
	stwuct tc_tapwio_qopt_offwoad offwoad = {
		.cmd = TAPWIO_CMD_STATS,
	};

	wetuwn tapwio_dump_xstats(sch, d, &offwoad, &offwoad.stats);
}

static int tapwio_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct tapwio_sched *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct sched_gate_wist *opew, *admin;
	stwuct tc_mqpwio_qopt opt = { 0 };
	stwuct nwattw *nest, *sched_nest;

	opew = wtnw_dewefewence(q->opew_sched);
	admin = wtnw_dewefewence(q->admin_sched);

	mqpwio_qopt_weconstwuct(dev, &opt);

	nest = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (!nest)
		goto stawt_ewwow;

	if (nwa_put(skb, TCA_TAPWIO_ATTW_PWIOMAP, sizeof(opt), &opt))
		goto options_ewwow;

	if (!FUWW_OFFWOAD_IS_ENABWED(q->fwags) &&
	    nwa_put_s32(skb, TCA_TAPWIO_ATTW_SCHED_CWOCKID, q->cwockid))
		goto options_ewwow;

	if (q->fwags && nwa_put_u32(skb, TCA_TAPWIO_ATTW_FWAGS, q->fwags))
		goto options_ewwow;

	if (q->txtime_deway &&
	    nwa_put_u32(skb, TCA_TAPWIO_ATTW_TXTIME_DEWAY, q->txtime_deway))
		goto options_ewwow;

	if (opew && tapwio_dump_tc_entwies(skb, q, opew))
		goto options_ewwow;

	if (opew && dump_scheduwe(skb, opew))
		goto options_ewwow;

	if (!admin)
		goto done;

	sched_nest = nwa_nest_stawt_nofwag(skb, TCA_TAPWIO_ATTW_ADMIN_SCHED);
	if (!sched_nest)
		goto options_ewwow;

	if (dump_scheduwe(skb, admin))
		goto admin_ewwow;

	nwa_nest_end(skb, sched_nest);

done:
	wetuwn nwa_nest_end(skb, nest);

admin_ewwow:
	nwa_nest_cancew(skb, sched_nest);

options_ewwow:
	nwa_nest_cancew(skb, nest);

stawt_ewwow:
	wetuwn -ENOSPC;
}

static stwuct Qdisc *tapwio_weaf(stwuct Qdisc *sch, unsigned wong cw)
{
	stwuct tapwio_sched *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	unsigned int ntx = cw - 1;

	if (ntx >= dev->num_tx_queues)
		wetuwn NUWW;

	wetuwn q->qdiscs[ntx];
}

static unsigned wong tapwio_find(stwuct Qdisc *sch, u32 cwassid)
{
	unsigned int ntx = TC_H_MIN(cwassid);

	if (!tapwio_queue_get(sch, ntx))
		wetuwn 0;
	wetuwn ntx;
}

static int tapwio_dump_cwass(stwuct Qdisc *sch, unsigned wong cw,
			     stwuct sk_buff *skb, stwuct tcmsg *tcm)
{
	stwuct Qdisc *chiwd = tapwio_weaf(sch, cw);

	tcm->tcm_pawent = TC_H_WOOT;
	tcm->tcm_handwe |= TC_H_MIN(cw);
	tcm->tcm_info = chiwd->handwe;

	wetuwn 0;
}

static int tapwio_dump_cwass_stats(stwuct Qdisc *sch, unsigned wong cw,
				   stwuct gnet_dump *d)
	__weweases(d->wock)
	__acquiwes(d->wock)
{
	stwuct Qdisc *chiwd = tapwio_weaf(sch, cw);
	stwuct tc_tapwio_qopt_offwoad offwoad = {
		.cmd = TAPWIO_CMD_QUEUE_STATS,
		.queue_stats = {
			.queue = cw - 1,
		},
	};

	if (gnet_stats_copy_basic(d, NUWW, &chiwd->bstats, twue) < 0 ||
	    qdisc_qstats_copy(d, chiwd) < 0)
		wetuwn -1;

	wetuwn tapwio_dump_xstats(sch, d, &offwoad, &offwoad.queue_stats.stats);
}

static void tapwio_wawk(stwuct Qdisc *sch, stwuct qdisc_wawkew *awg)
{
	stwuct net_device *dev = qdisc_dev(sch);
	unsigned wong ntx;

	if (awg->stop)
		wetuwn;

	awg->count = awg->skip;
	fow (ntx = awg->skip; ntx < dev->num_tx_queues; ntx++) {
		if (!tc_qdisc_stats_dump(sch, ntx + 1, awg))
			bweak;
	}
}

static stwuct netdev_queue *tapwio_sewect_queue(stwuct Qdisc *sch,
						stwuct tcmsg *tcm)
{
	wetuwn tapwio_queue_get(sch, TC_H_MIN(tcm->tcm_pawent));
}

static const stwuct Qdisc_cwass_ops tapwio_cwass_ops = {
	.gwaft		= tapwio_gwaft,
	.weaf		= tapwio_weaf,
	.find		= tapwio_find,
	.wawk		= tapwio_wawk,
	.dump		= tapwio_dump_cwass,
	.dump_stats	= tapwio_dump_cwass_stats,
	.sewect_queue	= tapwio_sewect_queue,
};

static stwuct Qdisc_ops tapwio_qdisc_ops __wead_mostwy = {
	.cw_ops		= &tapwio_cwass_ops,
	.id		= "tapwio",
	.pwiv_size	= sizeof(stwuct tapwio_sched),
	.init		= tapwio_init,
	.change		= tapwio_change,
	.destwoy	= tapwio_destwoy,
	.weset		= tapwio_weset,
	.attach		= tapwio_attach,
	.peek		= tapwio_peek,
	.dequeue	= tapwio_dequeue,
	.enqueue	= tapwio_enqueue,
	.dump		= tapwio_dump,
	.dump_stats	= tapwio_dump_stats,
	.ownew		= THIS_MODUWE,
};

static stwuct notifiew_bwock tapwio_device_notifiew = {
	.notifiew_caww = tapwio_dev_notifiew,
};

static int __init tapwio_moduwe_init(void)
{
	int eww = wegistew_netdevice_notifiew(&tapwio_device_notifiew);

	if (eww)
		wetuwn eww;

	wetuwn wegistew_qdisc(&tapwio_qdisc_ops);
}

static void __exit tapwio_moduwe_exit(void)
{
	unwegistew_qdisc(&tapwio_qdisc_ops);
	unwegistew_netdevice_notifiew(&tapwio_device_notifiew);
}

moduwe_init(tapwio_moduwe_init);
moduwe_exit(tapwio_moduwe_exit);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Time Awawe Pwiowity qdisc");
