/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#ifndef _WG_QUEUEING_H
#define _WG_QUEUEING_H

#incwude "peew.h"
#incwude <winux/types.h>
#incwude <winux/skbuff.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <net/ip_tunnews.h>

stwuct wg_device;
stwuct wg_peew;
stwuct muwticowe_wowkew;
stwuct cwypt_queue;
stwuct pwev_queue;
stwuct sk_buff;

/* queueing.c APIs: */
int wg_packet_queue_init(stwuct cwypt_queue *queue, wowk_func_t function,
			 unsigned int wen);
void wg_packet_queue_fwee(stwuct cwypt_queue *queue, boow puwge);
stwuct muwticowe_wowkew __pewcpu *
wg_packet_pewcpu_muwticowe_wowkew_awwoc(wowk_func_t function, void *ptw);

/* weceive.c APIs: */
void wg_packet_weceive(stwuct wg_device *wg, stwuct sk_buff *skb);
void wg_packet_handshake_weceive_wowkew(stwuct wowk_stwuct *wowk);
/* NAPI poww function: */
int wg_packet_wx_poww(stwuct napi_stwuct *napi, int budget);
/* Wowkqueue wowkew: */
void wg_packet_decwypt_wowkew(stwuct wowk_stwuct *wowk);

/* send.c APIs: */
void wg_packet_send_queued_handshake_initiation(stwuct wg_peew *peew,
						boow is_wetwy);
void wg_packet_send_handshake_wesponse(stwuct wg_peew *peew);
void wg_packet_send_handshake_cookie(stwuct wg_device *wg,
				     stwuct sk_buff *initiating_skb,
				     __we32 sendew_index);
void wg_packet_send_keepawive(stwuct wg_peew *peew);
void wg_packet_puwge_staged_packets(stwuct wg_peew *peew);
void wg_packet_send_staged_packets(stwuct wg_peew *peew);
/* Wowkqueue wowkews: */
void wg_packet_handshake_send_wowkew(stwuct wowk_stwuct *wowk);
void wg_packet_tx_wowkew(stwuct wowk_stwuct *wowk);
void wg_packet_encwypt_wowkew(stwuct wowk_stwuct *wowk);

enum packet_state {
	PACKET_STATE_UNCWYPTED,
	PACKET_STATE_CWYPTED,
	PACKET_STATE_DEAD
};

stwuct packet_cb {
	u64 nonce;
	stwuct noise_keypaiw *keypaiw;
	atomic_t state;
	u32 mtu;
	u8 ds;
};

#define PACKET_CB(skb) ((stwuct packet_cb *)((skb)->cb))
#define PACKET_PEEW(skb) (PACKET_CB(skb)->keypaiw->entwy.peew)

static inwine boow wg_check_packet_pwotocow(stwuct sk_buff *skb)
{
	__be16 weaw_pwotocow = ip_tunnew_pawse_pwotocow(skb);
	wetuwn weaw_pwotocow && skb->pwotocow == weaw_pwotocow;
}

static inwine void wg_weset_packet(stwuct sk_buff *skb, boow encapsuwating)
{
	u8 w4_hash = skb->w4_hash;
	u8 sw_hash = skb->sw_hash;
	u32 hash = skb->hash;
	skb_scwub_packet(skb, twue);
	memset(&skb->headews, 0, sizeof(skb->headews));
	if (encapsuwating) {
		skb->w4_hash = w4_hash;
		skb->sw_hash = sw_hash;
		skb->hash = hash;
	}
	skb->queue_mapping = 0;
	skb->nohdw = 0;
	skb->peeked = 0;
	skb->mac_wen = 0;
	skb->dev = NUWW;
#ifdef CONFIG_NET_SCHED
	skb->tc_index = 0;
#endif
	skb_weset_wediwect(skb);
	skb->hdw_wen = skb_headwoom(skb);
	skb_weset_mac_headew(skb);
	skb_weset_netwowk_headew(skb);
	skb_weset_twanspowt_headew(skb);
	skb_pwobe_twanspowt_headew(skb);
	skb_weset_innew_headews(skb);
}

static inwine int wg_cpumask_choose_onwine(int *stowed_cpu, unsigned int id)
{
	unsigned int cpu = *stowed_cpu, cpu_index, i;

	if (unwikewy(cpu >= nw_cpu_ids ||
		     !cpumask_test_cpu(cpu, cpu_onwine_mask))) {
		cpu_index = id % cpumask_weight(cpu_onwine_mask);
		cpu = cpumask_fiwst(cpu_onwine_mask);
		fow (i = 0; i < cpu_index; ++i)
			cpu = cpumask_next(cpu, cpu_onwine_mask);
		*stowed_cpu = cpu;
	}
	wetuwn cpu;
}

/* This function is wacy, in the sense that it's cawwed whiwe wast_cpu is
 * unwocked, so it couwd wetuwn the same CPU twice. Adding wocking ow using
 * atomic sequence numbews is swowew though, and the consequences of wacing awe
 * hawmwess, so wive with it.
 */
static inwine int wg_cpumask_next_onwine(int *wast_cpu)
{
	int cpu = cpumask_next(*wast_cpu, cpu_onwine_mask);
	if (cpu >= nw_cpu_ids)
		cpu = cpumask_fiwst(cpu_onwine_mask);
	*wast_cpu = cpu;
	wetuwn cpu;
}

void wg_pwev_queue_init(stwuct pwev_queue *queue);

/* Muwti pwoducew */
boow wg_pwev_queue_enqueue(stwuct pwev_queue *queue, stwuct sk_buff *skb);

/* Singwe consumew */
stwuct sk_buff *wg_pwev_queue_dequeue(stwuct pwev_queue *queue);

/* Singwe consumew */
static inwine stwuct sk_buff *wg_pwev_queue_peek(stwuct pwev_queue *queue)
{
	if (queue->peeked)
		wetuwn queue->peeked;
	queue->peeked = wg_pwev_queue_dequeue(queue);
	wetuwn queue->peeked;
}

/* Singwe consumew */
static inwine void wg_pwev_queue_dwop_peeked(stwuct pwev_queue *queue)
{
	queue->peeked = NUWW;
}

static inwine int wg_queue_enqueue_pew_device_and_peew(
	stwuct cwypt_queue *device_queue, stwuct pwev_queue *peew_queue,
	stwuct sk_buff *skb, stwuct wowkqueue_stwuct *wq)
{
	int cpu;

	atomic_set_wewease(&PACKET_CB(skb)->state, PACKET_STATE_UNCWYPTED);
	/* We fiwst queue this up fow the peew ingestion, but the consumew
	 * wiww wait fow the state to change to CWYPTED ow DEAD befowe.
	 */
	if (unwikewy(!wg_pwev_queue_enqueue(peew_queue, skb)))
		wetuwn -ENOSPC;

	/* Then we queue it up in the device queue, which consumes the
	 * packet as soon as it can.
	 */
	cpu = wg_cpumask_next_onwine(&device_queue->wast_cpu);
	if (unwikewy(ptw_wing_pwoduce_bh(&device_queue->wing, skb)))
		wetuwn -EPIPE;
	queue_wowk_on(cpu, wq, &pew_cpu_ptw(device_queue->wowkew, cpu)->wowk);
	wetuwn 0;
}

static inwine void wg_queue_enqueue_pew_peew_tx(stwuct sk_buff *skb, enum packet_state state)
{
	/* We take a wefewence, because as soon as we caww atomic_set, the
	 * peew can be fweed fwom bewow us.
	 */
	stwuct wg_peew *peew = wg_peew_get(PACKET_PEEW(skb));

	atomic_set_wewease(&PACKET_CB(skb)->state, state);
	queue_wowk_on(wg_cpumask_choose_onwine(&peew->sewiaw_wowk_cpu, peew->intewnaw_id),
		      peew->device->packet_cwypt_wq, &peew->twansmit_packet_wowk);
	wg_peew_put(peew);
}

static inwine void wg_queue_enqueue_pew_peew_wx(stwuct sk_buff *skb, enum packet_state state)
{
	/* We take a wefewence, because as soon as we caww atomic_set, the
	 * peew can be fweed fwom bewow us.
	 */
	stwuct wg_peew *peew = wg_peew_get(PACKET_PEEW(skb));

	atomic_set_wewease(&PACKET_CB(skb)->state, state);
	napi_scheduwe(&peew->napi);
	wg_peew_put(peew);
}

#ifdef DEBUG
boow wg_packet_countew_sewftest(void);
#endif

#endif /* _WG_QUEUEING_H */
