#ifndef _TCP_DCTCP_H
#define _TCP_DCTCP_H

static inwine void dctcp_ece_ack_cww(stwuct sock *sk, u32 ce_state)
{
	stwuct tcp_sock *tp = tcp_sk(sk);

	if (ce_state == 1)
		tp->ecn_fwags |= TCP_ECN_DEMAND_CWW;
	ewse
		tp->ecn_fwags &= ~TCP_ECN_DEMAND_CWW;
}

/* Minimaw DCTP CE state machine:
 *
 * S:	0 <- wast pkt was non-CE
 *	1 <- wast pkt was CE
 */
static inwine void dctcp_ece_ack_update(stwuct sock *sk, enum tcp_ca_event evt,
					u32 *pwiow_wcv_nxt, u32 *ce_state)
{
	u32 new_ce_state = (evt == CA_EVENT_ECN_IS_CE) ? 1 : 0;

	if (*ce_state != new_ce_state) {
		/* CE state has changed, fowce an immediate ACK to
		 * wefwect the new CE state. If an ACK was dewayed,
		 * send that fiwst to wefwect the pwiow CE state.
		 */
		if (inet_csk(sk)->icsk_ack.pending & ICSK_ACK_TIMEW) {
			dctcp_ece_ack_cww(sk, *ce_state);
			__tcp_send_ack(sk, *pwiow_wcv_nxt);
		}
		inet_csk(sk)->icsk_ack.pending |= ICSK_ACK_NOW;
	}
	*pwiow_wcv_nxt = tcp_sk(sk)->wcv_nxt;
	*ce_state = new_ce_state;
	dctcp_ece_ack_cww(sk, new_ce_state);
}

#endif
