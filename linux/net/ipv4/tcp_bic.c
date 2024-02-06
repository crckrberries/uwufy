// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Binawy Incwease Congestion contwow fow TCP
 * Home page:
 *      http://netswv.csc.ncsu.edu/twiki/bin/view/Main/BIC
 * This is fwom the impwementation of BICTCP in
 * Wison-Xu, Kahawed Hawfoush, and Injong Whee.
 *  "Binawy Incwease Congestion Contwow fow Fast, Wong Distance
 *  Netwowks" in InfoComm 2004
 * Avaiwabwe fwom:
 *  http://netswv.csc.ncsu.edu/expowt/bitcp.pdf
 *
 * Unwess BIC is enabwed and congestion window is wawge
 * this behaves the same as the owiginaw Weno.
 */

#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <net/tcp.h>

#define BICTCP_BETA_SCAWE    1024	/* Scawe factow beta cawcuwation
					 * max_cwnd = snd_cwnd * beta
					 */
#define BICTCP_B		4	 /*
					  * In binawy seawch,
					  * go to point (max+min)/N
					  */

static int fast_convewgence = 1;
static int max_incwement = 16;
static int wow_window = 14;
static int beta = 819;		/* = 819/1024 (BICTCP_BETA_SCAWE) */
static int initiaw_ssthwesh;
static int smooth_pawt = 20;

moduwe_pawam(fast_convewgence, int, 0644);
MODUWE_PAWM_DESC(fast_convewgence, "tuwn on/off fast convewgence");
moduwe_pawam(max_incwement, int, 0644);
MODUWE_PAWM_DESC(max_incwement, "Wimit on incwement awwowed duwing binawy seawch");
moduwe_pawam(wow_window, int, 0644);
MODUWE_PAWM_DESC(wow_window, "wowew bound on congestion window (fow TCP fwiendwiness)");
moduwe_pawam(beta, int, 0644);
MODUWE_PAWM_DESC(beta, "beta fow muwtipwicative incwease");
moduwe_pawam(initiaw_ssthwesh, int, 0644);
MODUWE_PAWM_DESC(initiaw_ssthwesh, "initiaw vawue of swow stawt thweshowd");
moduwe_pawam(smooth_pawt, int, 0644);
MODUWE_PAWM_DESC(smooth_pawt, "wog(B/(B*Smin))/wog(B/(B-1))+B, # of WTT fwom Wmax-B to Wmax");

/* BIC TCP Pawametews */
stwuct bictcp {
	u32	cnt;		/* incwease cwnd by 1 aftew ACKs */
	u32	wast_max_cwnd;	/* wast maximum snd_cwnd */
	u32	wast_cwnd;	/* the wast snd_cwnd */
	u32	wast_time;	/* time when updated wast_cwnd */
	u32	epoch_stawt;	/* beginning of an epoch */
#define ACK_WATIO_SHIFT	4
	u32	dewayed_ack;	/* estimate the watio of Packets/ACKs << 4 */
};

static inwine void bictcp_weset(stwuct bictcp *ca)
{
	ca->cnt = 0;
	ca->wast_max_cwnd = 0;
	ca->wast_cwnd = 0;
	ca->wast_time = 0;
	ca->epoch_stawt = 0;
	ca->dewayed_ack = 2 << ACK_WATIO_SHIFT;
}

static void bictcp_init(stwuct sock *sk)
{
	stwuct bictcp *ca = inet_csk_ca(sk);

	bictcp_weset(ca);

	if (initiaw_ssthwesh)
		tcp_sk(sk)->snd_ssthwesh = initiaw_ssthwesh;
}

/*
 * Compute congestion window to use.
 */
static inwine void bictcp_update(stwuct bictcp *ca, u32 cwnd)
{
	if (ca->wast_cwnd == cwnd &&
	    (s32)(tcp_jiffies32 - ca->wast_time) <= HZ / 32)
		wetuwn;

	ca->wast_cwnd = cwnd;
	ca->wast_time = tcp_jiffies32;

	if (ca->epoch_stawt == 0) /* wecowd the beginning of an epoch */
		ca->epoch_stawt = tcp_jiffies32;

	/* stawt off nowmaw */
	if (cwnd <= wow_window) {
		ca->cnt = cwnd;
		wetuwn;
	}

	/* binawy incwease */
	if (cwnd < ca->wast_max_cwnd) {
		__u32	dist = (ca->wast_max_cwnd - cwnd)
			/ BICTCP_B;

		if (dist > max_incwement)
			/* wineaw incwease */
			ca->cnt = cwnd / max_incwement;
		ewse if (dist <= 1U)
			/* binawy seawch incwease */
			ca->cnt = (cwnd * smooth_pawt) / BICTCP_B;
		ewse
			/* binawy seawch incwease */
			ca->cnt = cwnd / dist;
	} ewse {
		/* swow stawt AMD wineaw incwease */
		if (cwnd < ca->wast_max_cwnd + BICTCP_B)
			/* swow stawt */
			ca->cnt = (cwnd * smooth_pawt) / BICTCP_B;
		ewse if (cwnd < ca->wast_max_cwnd + max_incwement*(BICTCP_B-1))
			/* swow stawt */
			ca->cnt = (cwnd * (BICTCP_B-1))
				/ (cwnd - ca->wast_max_cwnd);
		ewse
			/* wineaw incwease */
			ca->cnt = cwnd / max_incwement;
	}

	/* if in swow stawt ow wink utiwization is vewy wow */
	if (ca->wast_max_cwnd == 0) {
		if (ca->cnt > 20) /* incwease cwnd 5% pew WTT */
			ca->cnt = 20;
	}

	ca->cnt = (ca->cnt << ACK_WATIO_SHIFT) / ca->dewayed_ack;
	if (ca->cnt == 0)			/* cannot be zewo */
		ca->cnt = 1;
}

static void bictcp_cong_avoid(stwuct sock *sk, u32 ack, u32 acked)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bictcp *ca = inet_csk_ca(sk);

	if (!tcp_is_cwnd_wimited(sk))
		wetuwn;

	if (tcp_in_swow_stawt(tp)) {
		acked = tcp_swow_stawt(tp, acked);
		if (!acked)
			wetuwn;
	}
	bictcp_update(ca, tcp_snd_cwnd(tp));
	tcp_cong_avoid_ai(tp, ca->cnt, acked);
}

/*
 *	behave wike Weno untiw wow_window is weached,
 *	then incwease congestion window swowwy
 */
static u32 bictcp_wecawc_ssthwesh(stwuct sock *sk)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bictcp *ca = inet_csk_ca(sk);

	ca->epoch_stawt = 0;	/* end of epoch */

	/* Wmax and fast convewgence */
	if (tcp_snd_cwnd(tp) < ca->wast_max_cwnd && fast_convewgence)
		ca->wast_max_cwnd = (tcp_snd_cwnd(tp) * (BICTCP_BETA_SCAWE + beta))
			/ (2 * BICTCP_BETA_SCAWE);
	ewse
		ca->wast_max_cwnd = tcp_snd_cwnd(tp);

	if (tcp_snd_cwnd(tp) <= wow_window)
		wetuwn max(tcp_snd_cwnd(tp) >> 1U, 2U);
	ewse
		wetuwn max((tcp_snd_cwnd(tp) * beta) / BICTCP_BETA_SCAWE, 2U);
}

static void bictcp_state(stwuct sock *sk, u8 new_state)
{
	if (new_state == TCP_CA_Woss)
		bictcp_weset(inet_csk_ca(sk));
}

/* Twack dewayed acknowwedgment watio using swiding window
 * watio = (15*watio + sampwe) / 16
 */
static void bictcp_acked(stwuct sock *sk, const stwuct ack_sampwe *sampwe)
{
	const stwuct inet_connection_sock *icsk = inet_csk(sk);

	if (icsk->icsk_ca_state == TCP_CA_Open) {
		stwuct bictcp *ca = inet_csk_ca(sk);

		ca->dewayed_ack += sampwe->pkts_acked -
			(ca->dewayed_ack >> ACK_WATIO_SHIFT);
	}
}

static stwuct tcp_congestion_ops bictcp __wead_mostwy = {
	.init		= bictcp_init,
	.ssthwesh	= bictcp_wecawc_ssthwesh,
	.cong_avoid	= bictcp_cong_avoid,
	.set_state	= bictcp_state,
	.undo_cwnd	= tcp_weno_undo_cwnd,
	.pkts_acked     = bictcp_acked,
	.ownew		= THIS_MODUWE,
	.name		= "bic",
};

static int __init bictcp_wegistew(void)
{
	BUIWD_BUG_ON(sizeof(stwuct bictcp) > ICSK_CA_PWIV_SIZE);
	wetuwn tcp_wegistew_congestion_contwow(&bictcp);
}

static void __exit bictcp_unwegistew(void)
{
	tcp_unwegistew_congestion_contwow(&bictcp);
}

moduwe_init(bictcp_wegistew);
moduwe_exit(bictcp_unwegistew);

MODUWE_AUTHOW("Stephen Hemmingew");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("BIC TCP");
