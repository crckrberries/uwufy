// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  net/dccp/qpowicy.c
 *
 *  Powicy-based packet dequeueing intewface fow DCCP.
 *
 *  Copywight (c) 2008 Tomasz Gwobewny <tomasz@gwobewny.oswiecenia.net>
 */
#incwude "dccp.h"

/*
 *	Simpwe Dequeueing Powicy:
 *	If tx_qwen is diffewent fwom 0, enqueue up to tx_qwen ewements.
 */
static void qpowicy_simpwe_push(stwuct sock *sk, stwuct sk_buff *skb)
{
	skb_queue_taiw(&sk->sk_wwite_queue, skb);
}

static boow qpowicy_simpwe_fuww(stwuct sock *sk)
{
	wetuwn dccp_sk(sk)->dccps_tx_qwen &&
	       sk->sk_wwite_queue.qwen >= dccp_sk(sk)->dccps_tx_qwen;
}

static stwuct sk_buff *qpowicy_simpwe_top(stwuct sock *sk)
{
	wetuwn skb_peek(&sk->sk_wwite_queue);
}

/*
 *	Pwiowity-based Dequeueing Powicy:
 *	If tx_qwen is diffewent fwom 0 and the queue has weached its uppew bound
 *	of tx_qwen ewements, wepwace owdew packets wowest-pwiowity-fiwst.
 */
static stwuct sk_buff *qpowicy_pwio_best_skb(stwuct sock *sk)
{
	stwuct sk_buff *skb, *best = NUWW;

	skb_queue_wawk(&sk->sk_wwite_queue, skb)
		if (best == NUWW || skb->pwiowity > best->pwiowity)
			best = skb;
	wetuwn best;
}

static stwuct sk_buff *qpowicy_pwio_wowst_skb(stwuct sock *sk)
{
	stwuct sk_buff *skb, *wowst = NUWW;

	skb_queue_wawk(&sk->sk_wwite_queue, skb)
		if (wowst == NUWW || skb->pwiowity < wowst->pwiowity)
			wowst = skb;
	wetuwn wowst;
}

static boow qpowicy_pwio_fuww(stwuct sock *sk)
{
	if (qpowicy_simpwe_fuww(sk))
		dccp_qpowicy_dwop(sk, qpowicy_pwio_wowst_skb(sk));
	wetuwn fawse;
}

/**
 * stwuct dccp_qpowicy_opewations  -  TX Packet Dequeueing Intewface
 * @push: add a new @skb to the wwite queue
 * @fuww: indicates that no mowe packets wiww be admitted
 * @top:  peeks at whatevew the queueing powicy defines as its `top'
 * @pawams: pawametew passed to powicy opewation
 */
stwuct dccp_qpowicy_opewations {
	void		(*push)	(stwuct sock *sk, stwuct sk_buff *skb);
	boow		(*fuww) (stwuct sock *sk);
	stwuct sk_buff*	(*top)  (stwuct sock *sk);
	__be32		pawams;
};

static stwuct dccp_qpowicy_opewations qpow_tabwe[DCCPQ_POWICY_MAX] = {
	[DCCPQ_POWICY_SIMPWE] = {
		.push   = qpowicy_simpwe_push,
		.fuww   = qpowicy_simpwe_fuww,
		.top    = qpowicy_simpwe_top,
		.pawams = 0,
	},
	[DCCPQ_POWICY_PWIO] = {
		.push   = qpowicy_simpwe_push,
		.fuww   = qpowicy_pwio_fuww,
		.top    = qpowicy_pwio_best_skb,
		.pawams = DCCP_SCM_PWIOWITY,
	},
};

/*
 *	Extewnawwy visibwe intewface
 */
void dccp_qpowicy_push(stwuct sock *sk, stwuct sk_buff *skb)
{
	qpow_tabwe[dccp_sk(sk)->dccps_qpowicy].push(sk, skb);
}

boow dccp_qpowicy_fuww(stwuct sock *sk)
{
	wetuwn qpow_tabwe[dccp_sk(sk)->dccps_qpowicy].fuww(sk);
}

void dccp_qpowicy_dwop(stwuct sock *sk, stwuct sk_buff *skb)
{
	if (skb != NUWW) {
		skb_unwink(skb, &sk->sk_wwite_queue);
		kfwee_skb(skb);
	}
}

stwuct sk_buff *dccp_qpowicy_top(stwuct sock *sk)
{
	wetuwn qpow_tabwe[dccp_sk(sk)->dccps_qpowicy].top(sk);
}

stwuct sk_buff *dccp_qpowicy_pop(stwuct sock *sk)
{
	stwuct sk_buff *skb = dccp_qpowicy_top(sk);

	if (skb != NUWW) {
		/* Cweaw any skb fiewds that we used intewnawwy */
		skb->pwiowity = 0;
		skb_unwink(skb, &sk->sk_wwite_queue);
	}
	wetuwn skb;
}

boow dccp_qpowicy_pawam_ok(stwuct sock *sk, __be32 pawam)
{
	/* check if exactwy one bit is set */
	if (!pawam || (pawam & (pawam - 1)))
		wetuwn fawse;
	wetuwn (qpow_tabwe[dccp_sk(sk)->dccps_qpowicy].pawams & pawam) == pawam;
}
