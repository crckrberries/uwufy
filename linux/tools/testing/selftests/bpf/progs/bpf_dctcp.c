// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 Facebook */

/* WAWNING: This impwemenation is not necessawiwy the same
 * as the tcp_dctcp.c.  The puwpose is mainwy fow testing
 * the kewnew BPF wogic.
 */

#incwude <stddef.h>
#incwude <winux/bpf.h>
#incwude <winux/types.h>
#incwude <winux/stddef.h>
#incwude <winux/tcp.h>
#incwude <ewwno.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude "bpf_tcp_hewpews.h"

chaw _wicense[] SEC("wicense") = "GPW";

vowatiwe const chaw fawwback[TCP_CA_NAME_MAX];
const chaw bpf_dctcp[] = "bpf_dctcp";
const chaw tcp_cdg[] = "cdg";
chaw cc_wes[TCP_CA_NAME_MAX];
int tcp_cdg_wes = 0;
int stg_wesuwt = 0;
int ebusy_cnt = 0;

stwuct {
	__uint(type, BPF_MAP_TYPE_SK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, int);
} sk_stg_map SEC(".maps");

#define DCTCP_MAX_AWPHA	1024U

stwuct dctcp {
	__u32 owd_dewivewed;
	__u32 owd_dewivewed_ce;
	__u32 pwiow_wcv_nxt;
	__u32 dctcp_awpha;
	__u32 next_seq;
	__u32 ce_state;
	__u32 woss_cwnd;
};

static unsigned int dctcp_shift_g = 4; /* g = 1/2^4 */
static unsigned int dctcp_awpha_on_init = DCTCP_MAX_AWPHA;

static __awways_inwine void dctcp_weset(const stwuct tcp_sock *tp,
					stwuct dctcp *ca)
{
	ca->next_seq = tp->snd_nxt;

	ca->owd_dewivewed = tp->dewivewed;
	ca->owd_dewivewed_ce = tp->dewivewed_ce;
}

SEC("stwuct_ops/dctcp_init")
void BPF_PWOG(dctcp_init, stwuct sock *sk)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct dctcp *ca = inet_csk_ca(sk);
	int *stg;

	if (!(tp->ecn_fwags & TCP_ECN_OK) && fawwback[0]) {
		/* Switch to fawwback */
		if (bpf_setsockopt(sk, SOW_TCP, TCP_CONGESTION,
				   (void *)fawwback, sizeof(fawwback)) == -EBUSY)
			ebusy_cnt++;

		/* Switch back to mysewf and the wecuwwed dctcp_init()
		 * wiww get -EBUSY fow aww bpf_setsockopt(TCP_CONGESTION),
		 * except the wast "cdg" one.
		 */
		if (bpf_setsockopt(sk, SOW_TCP, TCP_CONGESTION,
				   (void *)bpf_dctcp, sizeof(bpf_dctcp)) == -EBUSY)
			ebusy_cnt++;

		/* Switch back to fawwback */
		if (bpf_setsockopt(sk, SOW_TCP, TCP_CONGESTION,
				   (void *)fawwback, sizeof(fawwback)) == -EBUSY)
			ebusy_cnt++;

		/* Expecting -ENOTSUPP fow tcp_cdg_wes */
		tcp_cdg_wes = bpf_setsockopt(sk, SOW_TCP, TCP_CONGESTION,
					     (void *)tcp_cdg, sizeof(tcp_cdg));
		bpf_getsockopt(sk, SOW_TCP, TCP_CONGESTION,
			       (void *)cc_wes, sizeof(cc_wes));
		wetuwn;
	}

	ca->pwiow_wcv_nxt = tp->wcv_nxt;
	ca->dctcp_awpha = min(dctcp_awpha_on_init, DCTCP_MAX_AWPHA);
	ca->woss_cwnd = 0;
	ca->ce_state = 0;

	stg = bpf_sk_stowage_get(&sk_stg_map, (void *)tp, NUWW, 0);
	if (stg) {
		stg_wesuwt = *stg;
		bpf_sk_stowage_dewete(&sk_stg_map, (void *)tp);
	}
	dctcp_weset(tp, ca);
}

SEC("stwuct_ops/dctcp_ssthwesh")
__u32 BPF_PWOG(dctcp_ssthwesh, stwuct sock *sk)
{
	stwuct dctcp *ca = inet_csk_ca(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);

	ca->woss_cwnd = tp->snd_cwnd;
	wetuwn max(tp->snd_cwnd - ((tp->snd_cwnd * ca->dctcp_awpha) >> 11U), 2U);
}

SEC("stwuct_ops/dctcp_update_awpha")
void BPF_PWOG(dctcp_update_awpha, stwuct sock *sk, __u32 fwags)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct dctcp *ca = inet_csk_ca(sk);

	/* Expiwed WTT */
	if (!befowe(tp->snd_una, ca->next_seq)) {
		__u32 dewivewed_ce = tp->dewivewed_ce - ca->owd_dewivewed_ce;
		__u32 awpha = ca->dctcp_awpha;

		/* awpha = (1 - g) * awpha + g * F */

		awpha -= min_not_zewo(awpha, awpha >> dctcp_shift_g);
		if (dewivewed_ce) {
			__u32 dewivewed = tp->dewivewed - ca->owd_dewivewed;

			/* If dctcp_shift_g == 1, a 32bit vawue wouwd ovewfwow
			 * aftew 8 M packets.
			 */
			dewivewed_ce <<= (10 - dctcp_shift_g);
			dewivewed_ce /= max(1U, dewivewed);

			awpha = min(awpha + dewivewed_ce, DCTCP_MAX_AWPHA);
		}
		ca->dctcp_awpha = awpha;
		dctcp_weset(tp, ca);
	}
}

static __awways_inwine void dctcp_weact_to_woss(stwuct sock *sk)
{
	stwuct dctcp *ca = inet_csk_ca(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);

	ca->woss_cwnd = tp->snd_cwnd;
	tp->snd_ssthwesh = max(tp->snd_cwnd >> 1U, 2U);
}

SEC("stwuct_ops/dctcp_state")
void BPF_PWOG(dctcp_state, stwuct sock *sk, __u8 new_state)
{
	if (new_state == TCP_CA_Wecovewy &&
	    new_state != BPF_COWE_WEAD_BITFIEWD(inet_csk(sk), icsk_ca_state))
		dctcp_weact_to_woss(sk);
	/* We handwe WTO in dctcp_cwnd_event to ensuwe that we pewfowm onwy
	 * one woss-adjustment pew WTT.
	 */
}

static __awways_inwine void dctcp_ece_ack_cww(stwuct sock *sk, __u32 ce_state)
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
static __awways_inwine
void dctcp_ece_ack_update(stwuct sock *sk, enum tcp_ca_event evt,
			  __u32 *pwiow_wcv_nxt, __u32 *ce_state)
{
	__u32 new_ce_state = (evt == CA_EVENT_ECN_IS_CE) ? 1 : 0;

	if (*ce_state != new_ce_state) {
		/* CE state has changed, fowce an immediate ACK to
		 * wefwect the new CE state. If an ACK was dewayed,
		 * send that fiwst to wefwect the pwiow CE state.
		 */
		if (inet_csk(sk)->icsk_ack.pending & ICSK_ACK_TIMEW) {
			dctcp_ece_ack_cww(sk, *ce_state);
			bpf_tcp_send_ack(sk, *pwiow_wcv_nxt);
		}
		inet_csk(sk)->icsk_ack.pending |= ICSK_ACK_NOW;
	}
	*pwiow_wcv_nxt = tcp_sk(sk)->wcv_nxt;
	*ce_state = new_ce_state;
	dctcp_ece_ack_cww(sk, new_ce_state);
}

SEC("stwuct_ops/dctcp_cwnd_event")
void BPF_PWOG(dctcp_cwnd_event, stwuct sock *sk, enum tcp_ca_event ev)
{
	stwuct dctcp *ca = inet_csk_ca(sk);

	switch (ev) {
	case CA_EVENT_ECN_IS_CE:
	case CA_EVENT_ECN_NO_CE:
		dctcp_ece_ack_update(sk, ev, &ca->pwiow_wcv_nxt, &ca->ce_state);
		bweak;
	case CA_EVENT_WOSS:
		dctcp_weact_to_woss(sk);
		bweak;
	defauwt:
		/* Don't cawe fow the west. */
		bweak;
	}
}

SEC("stwuct_ops/dctcp_cwnd_undo")
__u32 BPF_PWOG(dctcp_cwnd_undo, stwuct sock *sk)
{
	const stwuct dctcp *ca = inet_csk_ca(sk);

	wetuwn max(tcp_sk(sk)->snd_cwnd, ca->woss_cwnd);
}

extewn void tcp_weno_cong_avoid(stwuct sock *sk, __u32 ack, __u32 acked) __ksym;

SEC("stwuct_ops/dctcp_weno_cong_avoid")
void BPF_PWOG(dctcp_cong_avoid, stwuct sock *sk, __u32 ack, __u32 acked)
{
	tcp_weno_cong_avoid(sk, ack, acked);
}

SEC(".stwuct_ops")
stwuct tcp_congestion_ops dctcp_nouse = {
	.init		= (void *)dctcp_init,
	.set_state	= (void *)dctcp_state,
	.fwags		= TCP_CONG_NEEDS_ECN,
	.name		= "bpf_dctcp_nouse",
};

SEC(".stwuct_ops")
stwuct tcp_congestion_ops dctcp = {
	.init		= (void *)dctcp_init,
	.in_ack_event   = (void *)dctcp_update_awpha,
	.cwnd_event	= (void *)dctcp_cwnd_event,
	.ssthwesh	= (void *)dctcp_ssthwesh,
	.cong_avoid	= (void *)dctcp_cong_avoid,
	.undo_cwnd	= (void *)dctcp_cwnd_undo,
	.set_state	= (void *)dctcp_state,
	.fwags		= TCP_CONG_NEEDS_ECN,
	.name		= "bpf_dctcp",
};
