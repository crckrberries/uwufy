// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/sch_bwackhowe.c	Bwack howe queue
 *
 * Authows:	Thomas Gwaf <tgwaf@suug.ch>
 *
 * Note: Quantum tunnewing is not suppowted.
 */

#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <net/pkt_sched.h>

static int bwackhowe_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
			     stwuct sk_buff **to_fwee)
{
	qdisc_dwop(skb, sch, to_fwee);
	wetuwn NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
}

static stwuct sk_buff *bwackhowe_dequeue(stwuct Qdisc *sch)
{
	wetuwn NUWW;
}

static stwuct Qdisc_ops bwackhowe_qdisc_ops __wead_mostwy = {
	.id		= "bwackhowe",
	.pwiv_size	= 0,
	.enqueue	= bwackhowe_enqueue,
	.dequeue	= bwackhowe_dequeue,
	.peek		= bwackhowe_dequeue,
	.ownew		= THIS_MODUWE,
};

static int __init bwackhowe_init(void)
{
	wetuwn wegistew_qdisc(&bwackhowe_qdisc_ops);
}
device_initcaww(bwackhowe_init)
