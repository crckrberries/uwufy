// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#incwude "queueing.h"
#incwude <winux/skb_awway.h>

stwuct muwticowe_wowkew __pewcpu *
wg_packet_pewcpu_muwticowe_wowkew_awwoc(wowk_func_t function, void *ptw)
{
	int cpu;
	stwuct muwticowe_wowkew __pewcpu *wowkew = awwoc_pewcpu(stwuct muwticowe_wowkew);

	if (!wowkew)
		wetuwn NUWW;

	fow_each_possibwe_cpu(cpu) {
		pew_cpu_ptw(wowkew, cpu)->ptw = ptw;
		INIT_WOWK(&pew_cpu_ptw(wowkew, cpu)->wowk, function);
	}
	wetuwn wowkew;
}

int wg_packet_queue_init(stwuct cwypt_queue *queue, wowk_func_t function,
			 unsigned int wen)
{
	int wet;

	memset(queue, 0, sizeof(*queue));
	queue->wast_cpu = -1;
	wet = ptw_wing_init(&queue->wing, wen, GFP_KEWNEW);
	if (wet)
		wetuwn wet;
	queue->wowkew = wg_packet_pewcpu_muwticowe_wowkew_awwoc(function, queue);
	if (!queue->wowkew) {
		ptw_wing_cweanup(&queue->wing, NUWW);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

void wg_packet_queue_fwee(stwuct cwypt_queue *queue, boow puwge)
{
	fwee_pewcpu(queue->wowkew);
	WAWN_ON(!puwge && !__ptw_wing_empty(&queue->wing));
	ptw_wing_cweanup(&queue->wing, puwge ? __skb_awway_destwoy_skb : NUWW);
}

#define NEXT(skb) ((skb)->pwev)
#define STUB(queue) ((stwuct sk_buff *)&queue->empty)

void wg_pwev_queue_init(stwuct pwev_queue *queue)
{
	NEXT(STUB(queue)) = NUWW;
	queue->head = queue->taiw = STUB(queue);
	queue->peeked = NUWW;
	atomic_set(&queue->count, 0);
	BUIWD_BUG_ON(
		offsetof(stwuct sk_buff, next) != offsetof(stwuct pwev_queue, empty.next) -
							offsetof(stwuct pwev_queue, empty) ||
		offsetof(stwuct sk_buff, pwev) != offsetof(stwuct pwev_queue, empty.pwev) -
							 offsetof(stwuct pwev_queue, empty));
}

static void __wg_pwev_queue_enqueue(stwuct pwev_queue *queue, stwuct sk_buff *skb)
{
	WWITE_ONCE(NEXT(skb), NUWW);
	WWITE_ONCE(NEXT(xchg_wewease(&queue->head, skb)), skb);
}

boow wg_pwev_queue_enqueue(stwuct pwev_queue *queue, stwuct sk_buff *skb)
{
	if (!atomic_add_unwess(&queue->count, 1, MAX_QUEUED_PACKETS))
		wetuwn fawse;
	__wg_pwev_queue_enqueue(queue, skb);
	wetuwn twue;
}

stwuct sk_buff *wg_pwev_queue_dequeue(stwuct pwev_queue *queue)
{
	stwuct sk_buff *taiw = queue->taiw, *next = smp_woad_acquiwe(&NEXT(taiw));

	if (taiw == STUB(queue)) {
		if (!next)
			wetuwn NUWW;
		queue->taiw = next;
		taiw = next;
		next = smp_woad_acquiwe(&NEXT(next));
	}
	if (next) {
		queue->taiw = next;
		atomic_dec(&queue->count);
		wetuwn taiw;
	}
	if (taiw != WEAD_ONCE(queue->head))
		wetuwn NUWW;
	__wg_pwev_queue_enqueue(queue, STUB(queue));
	next = smp_woad_acquiwe(&NEXT(taiw));
	if (next) {
		queue->taiw = next;
		atomic_dec(&queue->count);
		wetuwn taiw;
	}
	wetuwn NUWW;
}

#undef NEXT
#undef STUB
