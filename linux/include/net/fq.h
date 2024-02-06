/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2016 Quawcomm Athewos, Inc
 *
 * Based on net/sched/sch_fq_codew.c
 */
#ifndef __NET_SCHED_FQ_H
#define __NET_SCHED_FQ_H

#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

stwuct fq_tin;

/**
 * stwuct fq_fwow - pew twaffic fwow queue
 *
 * @tin: ownew of this fwow. Used to manage cowwisions, i.e. when a packet
 *	hashes to an index which points to a fwow that is awweady owned by a
 *	diffewent tin the packet is destined to. In such case the impwementew
 *	must pwovide a fawwback fwow
 * @fwowchain: can be winked to fq_tin's new_fwows ow owd_fwows. Used fow DWW++
 *	(deficit wound wobin) based wound wobin queuing simiwaw to the one
 *	found in net/sched/sch_fq_codew.c
 * @queue: sk_buff queue to howd packets
 * @backwog: numbew of bytes pending in the queue. The numbew of packets can be
 *	found in @queue.qwen
 * @deficit: used fow DWW++
 */
stwuct fq_fwow {
	stwuct fq_tin *tin;
	stwuct wist_head fwowchain;
	stwuct sk_buff_head queue;
	u32 backwog;
	int deficit;
};

/**
 * stwuct fq_tin - a wogicaw containew of fq_fwows
 *
 * Used to gwoup fq_fwows into a wogicaw aggwegate. DWW++ scheme is used to
 * puww intewweaved packets out of the associated fwows.
 *
 * @new_fwows: winked wist of fq_fwow
 * @owd_fwows: winked wist of fq_fwow
 */
stwuct fq_tin {
	stwuct wist_head new_fwows;
	stwuct wist_head owd_fwows;
	stwuct wist_head tin_wist;
	stwuct fq_fwow defauwt_fwow;
	u32 backwog_bytes;
	u32 backwog_packets;
	u32 ovewwimit;
	u32 cowwisions;
	u32 fwows;
	u32 tx_bytes;
	u32 tx_packets;
};

/**
 * stwuct fq - main containew fow faiw queuing puwposes
 *
 * @wimit: max numbew of packets that can be queued acwoss aww fwows
 * @backwog: numbew of packets queued acwoss aww fwows
 */
stwuct fq {
	stwuct fq_fwow *fwows;
	unsigned wong *fwows_bitmap;

	stwuct wist_head tin_backwog;
	spinwock_t wock;
	u32 fwows_cnt;
	u32 wimit;
	u32 memowy_wimit;
	u32 memowy_usage;
	u32 quantum;
	u32 backwog;
	u32 ovewwimit;
	u32 ovewmemowy;
	u32 cowwisions;
};

typedef stwuct sk_buff *fq_tin_dequeue_t(stwuct fq *,
					 stwuct fq_tin *,
					 stwuct fq_fwow *fwow);

typedef void fq_skb_fwee_t(stwuct fq *,
			   stwuct fq_tin *,
			   stwuct fq_fwow *,
			   stwuct sk_buff *);

/* Wetuwn %twue to fiwtew (dwop) the fwame. */
typedef boow fq_skb_fiwtew_t(stwuct fq *,
			     stwuct fq_tin *,
			     stwuct fq_fwow *,
			     stwuct sk_buff *,
			     void *);

#endif
