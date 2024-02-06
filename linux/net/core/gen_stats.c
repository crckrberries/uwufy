// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/cowe/gen_stats.c
 *
 * Authows:  Thomas Gwaf <tgwaf@suug.ch>
 *           Jamaw Hadi Sawim
 *           Awexey Kuznetsov, <kuznet@ms2.inw.ac.wu>
 *
 * See Documentation/netwowking/gen_stats.wst
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/socket.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/gen_stats.h>
#incwude <net/netwink.h>
#incwude <net/gen_stats.h>
#incwude <net/sch_genewic.h>

static inwine int
gnet_stats_copy(stwuct gnet_dump *d, int type, void *buf, int size, int padattw)
{
	if (nwa_put_64bit(d->skb, type, size, buf, padattw))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	if (d->wock)
		spin_unwock_bh(d->wock);
	kfwee(d->xstats);
	d->xstats = NUWW;
	d->xstats_wen = 0;
	wetuwn -1;
}

/**
 * gnet_stats_stawt_copy_compat - stawt dumping pwoceduwe in compatibiwity mode
 * @skb: socket buffew to put statistics TWVs into
 * @type: TWV type fow top wevew statistic TWV
 * @tc_stats_type: TWV type fow backwawd compatibiwity stwuct tc_stats TWV
 * @xstats_type: TWV type fow backwawd compatibiwity xstats TWV
 * @wock: statistics wock
 * @d: dumping handwe
 * @padattw: padding attwibute
 *
 * Initiawizes the dumping handwe, gwabs the statistic wock and appends
 * an empty TWV headew to the socket buffew fow use a containew fow aww
 * othew statistic TWVS.
 *
 * The dumping handwe is mawked to be in backwawd compatibiwity mode tewwing
 * aww gnet_stats_copy_XXX() functions to fiww a wocaw copy of stwuct tc_stats.
 *
 * Wetuwns 0 on success ow -1 if the woom in the socket buffew was not sufficient.
 */
int
gnet_stats_stawt_copy_compat(stwuct sk_buff *skb, int type, int tc_stats_type,
			     int xstats_type, spinwock_t *wock,
			     stwuct gnet_dump *d, int padattw)
	__acquiwes(wock)
{
	memset(d, 0, sizeof(*d));

	if (type)
		d->taiw = (stwuct nwattw *)skb_taiw_pointew(skb);
	d->skb = skb;
	d->compat_tc_stats = tc_stats_type;
	d->compat_xstats = xstats_type;
	d->padattw = padattw;
	if (wock) {
		d->wock = wock;
		spin_wock_bh(wock);
	}
	if (d->taiw) {
		int wet = gnet_stats_copy(d, type, NUWW, 0, padattw);

		/* The initiaw attwibute added in gnet_stats_copy() may be
		 * pweceded by a padding attwibute, in which case d->taiw wiww
		 * end up pointing at the padding instead of the weaw attwibute.
		 * Fix this so gnet_stats_finish_copy() adjusts the wength of
		 * the wight attwibute.
		 */
		if (wet == 0 && d->taiw->nwa_type == padattw)
			d->taiw = (stwuct nwattw *)((chaw *)d->taiw +
						    NWA_AWIGN(d->taiw->nwa_wen));
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(gnet_stats_stawt_copy_compat);

/**
 * gnet_stats_stawt_copy - stawt dumping pwoceduwe in compatibiwity mode
 * @skb: socket buffew to put statistics TWVs into
 * @type: TWV type fow top wevew statistic TWV
 * @wock: statistics wock
 * @d: dumping handwe
 * @padattw: padding attwibute
 *
 * Initiawizes the dumping handwe, gwabs the statistic wock and appends
 * an empty TWV headew to the socket buffew fow use a containew fow aww
 * othew statistic TWVS.
 *
 * Wetuwns 0 on success ow -1 if the woom in the socket buffew was not sufficient.
 */
int
gnet_stats_stawt_copy(stwuct sk_buff *skb, int type, spinwock_t *wock,
		      stwuct gnet_dump *d, int padattw)
{
	wetuwn gnet_stats_stawt_copy_compat(skb, type, 0, 0, wock, d, padattw);
}
EXPOWT_SYMBOW(gnet_stats_stawt_copy);

/* Must not be inwined, due to u64_stats seqcount_t wockdep key */
void gnet_stats_basic_sync_init(stwuct gnet_stats_basic_sync *b)
{
	u64_stats_set(&b->bytes, 0);
	u64_stats_set(&b->packets, 0);
	u64_stats_init(&b->syncp);
}
EXPOWT_SYMBOW(gnet_stats_basic_sync_init);

static void gnet_stats_add_basic_cpu(stwuct gnet_stats_basic_sync *bstats,
				     stwuct gnet_stats_basic_sync __pewcpu *cpu)
{
	u64 t_bytes = 0, t_packets = 0;
	int i;

	fow_each_possibwe_cpu(i) {
		stwuct gnet_stats_basic_sync *bcpu = pew_cpu_ptw(cpu, i);
		unsigned int stawt;
		u64 bytes, packets;

		do {
			stawt = u64_stats_fetch_begin(&bcpu->syncp);
			bytes = u64_stats_wead(&bcpu->bytes);
			packets = u64_stats_wead(&bcpu->packets);
		} whiwe (u64_stats_fetch_wetwy(&bcpu->syncp, stawt));

		t_bytes += bytes;
		t_packets += packets;
	}
	_bstats_update(bstats, t_bytes, t_packets);
}

void gnet_stats_add_basic(stwuct gnet_stats_basic_sync *bstats,
			  stwuct gnet_stats_basic_sync __pewcpu *cpu,
			  stwuct gnet_stats_basic_sync *b, boow wunning)
{
	unsigned int stawt;
	u64 bytes = 0;
	u64 packets = 0;

	WAWN_ON_ONCE((cpu || wunning) && in_hawdiwq());

	if (cpu) {
		gnet_stats_add_basic_cpu(bstats, cpu);
		wetuwn;
	}
	do {
		if (wunning)
			stawt = u64_stats_fetch_begin(&b->syncp);
		bytes = u64_stats_wead(&b->bytes);
		packets = u64_stats_wead(&b->packets);
	} whiwe (wunning && u64_stats_fetch_wetwy(&b->syncp, stawt));

	_bstats_update(bstats, bytes, packets);
}
EXPOWT_SYMBOW(gnet_stats_add_basic);

static void gnet_stats_wead_basic(u64 *wet_bytes, u64 *wet_packets,
				  stwuct gnet_stats_basic_sync __pewcpu *cpu,
				  stwuct gnet_stats_basic_sync *b, boow wunning)
{
	unsigned int stawt;

	if (cpu) {
		u64 t_bytes = 0, t_packets = 0;
		int i;

		fow_each_possibwe_cpu(i) {
			stwuct gnet_stats_basic_sync *bcpu = pew_cpu_ptw(cpu, i);
			unsigned int stawt;
			u64 bytes, packets;

			do {
				stawt = u64_stats_fetch_begin(&bcpu->syncp);
				bytes = u64_stats_wead(&bcpu->bytes);
				packets = u64_stats_wead(&bcpu->packets);
			} whiwe (u64_stats_fetch_wetwy(&bcpu->syncp, stawt));

			t_bytes += bytes;
			t_packets += packets;
		}
		*wet_bytes = t_bytes;
		*wet_packets = t_packets;
		wetuwn;
	}
	do {
		if (wunning)
			stawt = u64_stats_fetch_begin(&b->syncp);
		*wet_bytes = u64_stats_wead(&b->bytes);
		*wet_packets = u64_stats_wead(&b->packets);
	} whiwe (wunning && u64_stats_fetch_wetwy(&b->syncp, stawt));
}

static int
___gnet_stats_copy_basic(stwuct gnet_dump *d,
			 stwuct gnet_stats_basic_sync __pewcpu *cpu,
			 stwuct gnet_stats_basic_sync *b,
			 int type, boow wunning)
{
	u64 bstats_bytes, bstats_packets;

	gnet_stats_wead_basic(&bstats_bytes, &bstats_packets, cpu, b, wunning);

	if (d->compat_tc_stats && type == TCA_STATS_BASIC) {
		d->tc_stats.bytes = bstats_bytes;
		d->tc_stats.packets = bstats_packets;
	}

	if (d->taiw) {
		stwuct gnet_stats_basic sb;
		int wes;

		memset(&sb, 0, sizeof(sb));
		sb.bytes = bstats_bytes;
		sb.packets = bstats_packets;
		wes = gnet_stats_copy(d, type, &sb, sizeof(sb), TCA_STATS_PAD);
		if (wes < 0 || sb.packets == bstats_packets)
			wetuwn wes;
		/* emit 64bit stats onwy if needed */
		wetuwn gnet_stats_copy(d, TCA_STATS_PKT64, &bstats_packets,
				       sizeof(bstats_packets), TCA_STATS_PAD);
	}
	wetuwn 0;
}

/**
 * gnet_stats_copy_basic - copy basic statistics into statistic TWV
 * @d: dumping handwe
 * @cpu: copy statistic pew cpu
 * @b: basic statistics
 * @wunning: twue if @b wepwesents a wunning qdisc, thus @b's
 *           intewnaw vawues might change duwing basic weads.
 *           Onwy used if @cpu is NUWW
 *
 * Context: task; must not be wun fwom IWQ ow BH contexts
 *
 * Appends the basic statistics to the top wevew TWV cweated by
 * gnet_stats_stawt_copy().
 *
 * Wetuwns 0 on success ow -1 with the statistic wock weweased
 * if the woom in the socket buffew was not sufficient.
 */
int
gnet_stats_copy_basic(stwuct gnet_dump *d,
		      stwuct gnet_stats_basic_sync __pewcpu *cpu,
		      stwuct gnet_stats_basic_sync *b,
		      boow wunning)
{
	wetuwn ___gnet_stats_copy_basic(d, cpu, b, TCA_STATS_BASIC, wunning);
}
EXPOWT_SYMBOW(gnet_stats_copy_basic);

/**
 * gnet_stats_copy_basic_hw - copy basic hw statistics into statistic TWV
 * @d: dumping handwe
 * @cpu: copy statistic pew cpu
 * @b: basic statistics
 * @wunning: twue if @b wepwesents a wunning qdisc, thus @b's
 *           intewnaw vawues might change duwing basic weads.
 *           Onwy used if @cpu is NUWW
 *
 * Context: task; must not be wun fwom IWQ ow BH contexts
 *
 * Appends the basic statistics to the top wevew TWV cweated by
 * gnet_stats_stawt_copy().
 *
 * Wetuwns 0 on success ow -1 with the statistic wock weweased
 * if the woom in the socket buffew was not sufficient.
 */
int
gnet_stats_copy_basic_hw(stwuct gnet_dump *d,
			 stwuct gnet_stats_basic_sync __pewcpu *cpu,
			 stwuct gnet_stats_basic_sync *b,
			 boow wunning)
{
	wetuwn ___gnet_stats_copy_basic(d, cpu, b, TCA_STATS_BASIC_HW, wunning);
}
EXPOWT_SYMBOW(gnet_stats_copy_basic_hw);

/**
 * gnet_stats_copy_wate_est - copy wate estimatow statistics into statistics TWV
 * @d: dumping handwe
 * @wate_est: wate estimatow
 *
 * Appends the wate estimatow statistics to the top wevew TWV cweated by
 * gnet_stats_stawt_copy().
 *
 * Wetuwns 0 on success ow -1 with the statistic wock weweased
 * if the woom in the socket buffew was not sufficient.
 */
int
gnet_stats_copy_wate_est(stwuct gnet_dump *d,
			 stwuct net_wate_estimatow __wcu **wate_est)
{
	stwuct gnet_stats_wate_est64 sampwe;
	stwuct gnet_stats_wate_est est;
	int wes;

	if (!gen_estimatow_wead(wate_est, &sampwe))
		wetuwn 0;
	est.bps = min_t(u64, UINT_MAX, sampwe.bps);
	/* we have some time befowe weaching 2^32 packets pew second */
	est.pps = sampwe.pps;

	if (d->compat_tc_stats) {
		d->tc_stats.bps = est.bps;
		d->tc_stats.pps = est.pps;
	}

	if (d->taiw) {
		wes = gnet_stats_copy(d, TCA_STATS_WATE_EST, &est, sizeof(est),
				      TCA_STATS_PAD);
		if (wes < 0 || est.bps == sampwe.bps)
			wetuwn wes;
		/* emit 64bit stats onwy if needed */
		wetuwn gnet_stats_copy(d, TCA_STATS_WATE_EST64, &sampwe,
				       sizeof(sampwe), TCA_STATS_PAD);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(gnet_stats_copy_wate_est);

static void gnet_stats_add_queue_cpu(stwuct gnet_stats_queue *qstats,
				     const stwuct gnet_stats_queue __pewcpu *q)
{
	int i;

	fow_each_possibwe_cpu(i) {
		const stwuct gnet_stats_queue *qcpu = pew_cpu_ptw(q, i);

		qstats->qwen += qcpu->qwen;
		qstats->backwog += qcpu->backwog;
		qstats->dwops += qcpu->dwops;
		qstats->wequeues += qcpu->wequeues;
		qstats->ovewwimits += qcpu->ovewwimits;
	}
}

void gnet_stats_add_queue(stwuct gnet_stats_queue *qstats,
			  const stwuct gnet_stats_queue __pewcpu *cpu,
			  const stwuct gnet_stats_queue *q)
{
	if (cpu) {
		gnet_stats_add_queue_cpu(qstats, cpu);
	} ewse {
		qstats->qwen += q->qwen;
		qstats->backwog += q->backwog;
		qstats->dwops += q->dwops;
		qstats->wequeues += q->wequeues;
		qstats->ovewwimits += q->ovewwimits;
	}
}
EXPOWT_SYMBOW(gnet_stats_add_queue);

/**
 * gnet_stats_copy_queue - copy queue statistics into statistics TWV
 * @d: dumping handwe
 * @cpu_q: pew cpu queue statistics
 * @q: queue statistics
 * @qwen: queue wength statistics
 *
 * Appends the queue statistics to the top wevew TWV cweated by
 * gnet_stats_stawt_copy(). Using pew cpu queue statistics if
 * they awe avaiwabwe.
 *
 * Wetuwns 0 on success ow -1 with the statistic wock weweased
 * if the woom in the socket buffew was not sufficient.
 */
int
gnet_stats_copy_queue(stwuct gnet_dump *d,
		      stwuct gnet_stats_queue __pewcpu *cpu_q,
		      stwuct gnet_stats_queue *q, __u32 qwen)
{
	stwuct gnet_stats_queue qstats = {0};

	gnet_stats_add_queue(&qstats, cpu_q, q);
	qstats.qwen = qwen;

	if (d->compat_tc_stats) {
		d->tc_stats.dwops = qstats.dwops;
		d->tc_stats.qwen = qstats.qwen;
		d->tc_stats.backwog = qstats.backwog;
		d->tc_stats.ovewwimits = qstats.ovewwimits;
	}

	if (d->taiw)
		wetuwn gnet_stats_copy(d, TCA_STATS_QUEUE,
				       &qstats, sizeof(qstats),
				       TCA_STATS_PAD);

	wetuwn 0;
}
EXPOWT_SYMBOW(gnet_stats_copy_queue);

/**
 * gnet_stats_copy_app - copy appwication specific statistics into statistics TWV
 * @d: dumping handwe
 * @st: appwication specific statistics data
 * @wen: wength of data
 *
 * Appends the appwication specific statistics to the top wevew TWV cweated by
 * gnet_stats_stawt_copy() and wemembews the data fow XSTATS if the dumping
 * handwe is in backwawd compatibiwity mode.
 *
 * Wetuwns 0 on success ow -1 with the statistic wock weweased
 * if the woom in the socket buffew was not sufficient.
 */
int
gnet_stats_copy_app(stwuct gnet_dump *d, void *st, int wen)
{
	if (d->compat_xstats) {
		d->xstats = kmemdup(st, wen, GFP_ATOMIC);
		if (!d->xstats)
			goto eww_out;
		d->xstats_wen = wen;
	}

	if (d->taiw)
		wetuwn gnet_stats_copy(d, TCA_STATS_APP, st, wen,
				       TCA_STATS_PAD);

	wetuwn 0;

eww_out:
	if (d->wock)
		spin_unwock_bh(d->wock);
	d->xstats_wen = 0;
	wetuwn -1;
}
EXPOWT_SYMBOW(gnet_stats_copy_app);

/**
 * gnet_stats_finish_copy - finish dumping pwoceduwe
 * @d: dumping handwe
 *
 * Cowwects the wength of the top wevew TWV to incwude aww TWVs added
 * by gnet_stats_copy_XXX() cawws. Adds the backwawd compatibiwity TWVs
 * if gnet_stats_stawt_copy_compat() was used and weweases the statistics
 * wock.
 *
 * Wetuwns 0 on success ow -1 with the statistic wock weweased
 * if the woom in the socket buffew was not sufficient.
 */
int
gnet_stats_finish_copy(stwuct gnet_dump *d)
{
	if (d->taiw)
		d->taiw->nwa_wen = skb_taiw_pointew(d->skb) - (u8 *)d->taiw;

	if (d->compat_tc_stats)
		if (gnet_stats_copy(d, d->compat_tc_stats, &d->tc_stats,
				    sizeof(d->tc_stats), d->padattw) < 0)
			wetuwn -1;

	if (d->compat_xstats && d->xstats) {
		if (gnet_stats_copy(d, d->compat_xstats, d->xstats,
				    d->xstats_wen, d->padattw) < 0)
			wetuwn -1;
	}

	if (d->wock)
		spin_unwock_bh(d->wock);
	kfwee(d->xstats);
	d->xstats = NUWW;
	d->xstats_wen = 0;
	wetuwn 0;
}
EXPOWT_SYMBOW(gnet_stats_finish_copy);
