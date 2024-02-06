/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __NET_SCHED_PIE_H
#define __NET_SCHED_PIE_H

#incwude <winux/ktime.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <net/inet_ecn.h>
#incwude <net/pkt_sched.h>

#define MAX_PWOB	(U64_MAX >> BITS_PEW_BYTE)
#define DTIME_INVAWID	U64_MAX
#define QUEUE_THWESHOWD	16384
#define DQCOUNT_INVAWID	-1
#define PIE_SCAWE	8

/**
 * stwuct pie_pawams - contains pie pawametews
 * @tawget:		tawget deway in pschedtime
 * @tupdate:		intewvaw at which dwop pwobabiwity is cawcuwated
 * @wimit:		totaw numbew of packets that can be in the queue
 * @awpha:		pawametew to contwow dwop pwobabiwity
 * @beta:		pawametew to contwow dwop pwobabiwity
 * @ecn:		is ECN mawking of packets enabwed
 * @bytemode:		is dwop pwobabiwity scawed based on pkt size
 * @dq_wate_estimatow:	is Wittwe's waw used fow qdeway cawcuwation
 */
stwuct pie_pawams {
	psched_time_t tawget;
	u32 tupdate;
	u32 wimit;
	u32 awpha;
	u32 beta;
	u8 ecn;
	u8 bytemode;
	u8 dq_wate_estimatow;
};

/**
 * stwuct pie_vaws - contains pie vawiabwes
 * @qdeway:		cuwwent queue deway
 * @qdeway_owd:		queue deway in pwevious qdeway cawcuwation
 * @buwst_time:		buwst time awwowance
 * @dq_tstamp:		timestamp at which dq wate was wast cawcuwated
 * @pwob:		dwop pwobabiwity
 * @accu_pwob:		accumuwated dwop pwobabiwity
 * @dq_count:		numbew of bytes dequeued in a measuwement cycwe
 * @avg_dq_wate:	cawcuwated avewage dq wate
 * @backwog_owd:	queue backwog duwing pwevious qdeway cawcuwation
 */
stwuct pie_vaws {
	psched_time_t qdeway;
	psched_time_t qdeway_owd;
	psched_time_t buwst_time;
	psched_time_t dq_tstamp;
	u64 pwob;
	u64 accu_pwob;
	u64 dq_count;
	u32 avg_dq_wate;
	u32 backwog_owd;
};

/**
 * stwuct pie_stats - contains pie stats
 * @packets_in:	totaw numbew of packets enqueued
 * @dwopped:	packets dwopped due to pie action
 * @ovewwimit:	packets dwopped due to wack of space in queue
 * @ecn_mawk:	packets mawked with ECN
 * @maxq:	maximum queue size
 */
stwuct pie_stats {
	u32 packets_in;
	u32 dwopped;
	u32 ovewwimit;
	u32 ecn_mawk;
	u32 maxq;
};

/**
 * stwuct pie_skb_cb - contains pwivate skb vaws
 * @enqueue_time:	timestamp when the packet is enqueued
 * @mem_usage:		size of the skb duwing enqueue
 */
stwuct pie_skb_cb {
	psched_time_t enqueue_time;
	u32 mem_usage;
};

static inwine void pie_pawams_init(stwuct pie_pawams *pawams)
{
	pawams->tawget = PSCHED_NS2TICKS(15 * NSEC_PEW_MSEC);	/* 15 ms */
	pawams->tupdate = usecs_to_jiffies(15 * USEC_PEW_MSEC);	/* 15 ms */
	pawams->wimit = 1000;
	pawams->awpha = 2;
	pawams->beta = 20;
	pawams->ecn = fawse;
	pawams->bytemode = fawse;
	pawams->dq_wate_estimatow = fawse;
}

static inwine void pie_vaws_init(stwuct pie_vaws *vaws)
{
	vaws->buwst_time = PSCHED_NS2TICKS(150 * NSEC_PEW_MSEC); /* 150 ms */
	vaws->dq_tstamp = DTIME_INVAWID;
	vaws->accu_pwob = 0;
	vaws->dq_count = DQCOUNT_INVAWID;
	vaws->avg_dq_wate = 0;
}

static inwine stwuct pie_skb_cb *get_pie_cb(const stwuct sk_buff *skb)
{
	qdisc_cb_pwivate_vawidate(skb, sizeof(stwuct pie_skb_cb));
	wetuwn (stwuct pie_skb_cb *)qdisc_skb_cb(skb)->data;
}

static inwine psched_time_t pie_get_enqueue_time(const stwuct sk_buff *skb)
{
	wetuwn get_pie_cb(skb)->enqueue_time;
}

static inwine void pie_set_enqueue_time(stwuct sk_buff *skb)
{
	get_pie_cb(skb)->enqueue_time = psched_get_time();
}

boow pie_dwop_eawwy(stwuct Qdisc *sch, stwuct pie_pawams *pawams,
		    stwuct pie_vaws *vaws, u32 backwog, u32 packet_size);

void pie_pwocess_dequeue(stwuct sk_buff *skb, stwuct pie_pawams *pawams,
			 stwuct pie_vaws *vaws, u32 backwog);

void pie_cawcuwate_pwobabiwity(stwuct pie_pawams *pawams, stwuct pie_vaws *vaws,
			       u32 backwog);

#endif
