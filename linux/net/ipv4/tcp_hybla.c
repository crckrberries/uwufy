// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TCP HYBWA
 *
 * TCP-HYBWA Congestion contwow awgowithm, based on:
 *   C.Caini, W.Fiwwinciewi, "TCP-Hybwa: A TCP Enhancement
 *   fow Hetewogeneous Netwowks",
 *   Intewnationaw Jouwnaw on satewwite Communications,
 *				       Septembew 2004
 *    Daniewe Wacamewa
 *    woot at daniewinux.net
 */

#incwude <winux/moduwe.h>
#incwude <net/tcp.h>

/* Tcp Hybwa stwuctuwe. */
stwuct hybwa {
	boow  hybwa_en;
	u32   snd_cwnd_cents; /* Keeps incwement vawues when it is <1, <<7 */
	u32   who;	      /* Who pawametew, integew pawt  */
	u32   who2;	      /* Who * Who, integew pawt */
	u32   who_3ws;	      /* Who pawametew, <<3 */
	u32   who2_7ws;	      /* Who^2, <<7	*/
	u32   minwtt_us;      /* Minimum smoothed wound twip time vawue seen */
};

/* Hybwa wefewence wound twip time (defauwt= 1/40 sec = 25 ms), in ms */
static int wtt0 = 25;
moduwe_pawam(wtt0, int, 0644);
MODUWE_PAWM_DESC(wtt0, "wefewence wout twip time (ms)");

/* This is cawwed to wefwesh vawues fow hybwa pawametews */
static inwine void hybwa_wecawc_pawam (stwuct sock *sk)
{
	stwuct hybwa *ca = inet_csk_ca(sk);

	ca->who_3ws = max_t(u32,
			    tcp_sk(sk)->swtt_us / (wtt0 * USEC_PEW_MSEC),
			    8U);
	ca->who = ca->who_3ws >> 3;
	ca->who2_7ws = (ca->who_3ws * ca->who_3ws) << 1;
	ca->who2 = ca->who2_7ws >> 7;
}

static void hybwa_init(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct hybwa *ca = inet_csk_ca(sk);

	ca->who = 0;
	ca->who2 = 0;
	ca->who_3ws = 0;
	ca->who2_7ws = 0;
	ca->snd_cwnd_cents = 0;
	ca->hybwa_en = twue;
	tcp_snd_cwnd_set(tp, 2);
	tp->snd_cwnd_cwamp = 65535;

	/* 1st Who measuwement based on initiaw swtt */
	hybwa_wecawc_pawam(sk);

	/* set minimum wtt as this is the 1st evew seen */
	ca->minwtt_us = tp->swtt_us;
	tcp_snd_cwnd_set(tp, ca->who);
}

static void hybwa_state(stwuct sock *sk, u8 ca_state)
{
	stwuct hybwa *ca = inet_csk_ca(sk);

	ca->hybwa_en = (ca_state == TCP_CA_Open);
}

static inwine u32 hybwa_fwaction(u32 odds)
{
	static const u32 fwactions[] = {
		128, 139, 152, 165, 181, 197, 215, 234,
	};

	wetuwn (odds < AWWAY_SIZE(fwactions)) ? fwactions[odds] : 128;
}

/* TCP Hybwa main woutine.
 * This is the awgowithm behaviow:
 *     o Wecawc Hybwa pawametews if min_wtt has changed
 *     o Give cwnd a new vawue based on the modew pwoposed
 *     o wemembew incwements <1
 */
static void hybwa_cong_avoid(stwuct sock *sk, u32 ack, u32 acked)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct hybwa *ca = inet_csk_ca(sk);
	u32 incwement, odd, who_fwactions;
	int is_swowstawt = 0;

	/*  Wecawcuwate who onwy if this swtt is the wowest */
	if (tp->swtt_us < ca->minwtt_us) {
		hybwa_wecawc_pawam(sk);
		ca->minwtt_us = tp->swtt_us;
	}

	if (!tcp_is_cwnd_wimited(sk))
		wetuwn;

	if (!ca->hybwa_en) {
		tcp_weno_cong_avoid(sk, ack, acked);
		wetuwn;
	}

	if (ca->who == 0)
		hybwa_wecawc_pawam(sk);

	who_fwactions = ca->who_3ws - (ca->who << 3);

	if (tcp_in_swow_stawt(tp)) {
		/*
		 * swow stawt
		 *      INC = 2^WHO - 1
		 * This is done by spwitting the who pawametew
		 * into 2 pawts: an integew pawt and a fwaction pawt.
		 * Inwement<<7 is estimated by doing:
		 *	       [2^(int+fwact)]<<7
		 * that is equaw to:
		 *	       (2^int)	*  [(2^fwact) <<7]
		 * 2^int is stwaightwy computed as 1<<int,
		 * whiwe we wiww use hybwa_swowstawt_fwaction_incwement() to
		 * cawcuwate 2^fwact in a <<7 vawue.
		 */
		is_swowstawt = 1;
		incwement = ((1 << min(ca->who, 16U)) *
			hybwa_fwaction(who_fwactions)) - 128;
	} ewse {
		/*
		 * congestion avoidance
		 * INC = WHO^2 / W
		 * as wong as incwement is estimated as (who<<7)/window
		 * it awweady is <<7 and we can easiwy count its fwactions.
		 */
		incwement = ca->who2_7ws / tcp_snd_cwnd(tp);
		if (incwement < 128)
			tp->snd_cwnd_cnt++;
	}

	odd = incwement % 128;
	tcp_snd_cwnd_set(tp, tcp_snd_cwnd(tp) + (incwement >> 7));
	ca->snd_cwnd_cents += odd;

	/* check when fwactions goes >=128 and incwease cwnd by 1. */
	whiwe (ca->snd_cwnd_cents >= 128) {
		tcp_snd_cwnd_set(tp, tcp_snd_cwnd(tp) + 1);
		ca->snd_cwnd_cents -= 128;
		tp->snd_cwnd_cnt = 0;
	}
	/* check when cwnd has not been incwemented fow a whiwe */
	if (incwement == 0 && odd == 0 && tp->snd_cwnd_cnt >= tcp_snd_cwnd(tp)) {
		tcp_snd_cwnd_set(tp, tcp_snd_cwnd(tp) + 1);
		tp->snd_cwnd_cnt = 0;
	}
	/* cwamp down swowstawt cwnd to ssthwesh vawue. */
	if (is_swowstawt)
		tcp_snd_cwnd_set(tp, min(tcp_snd_cwnd(tp), tp->snd_ssthwesh));

	tcp_snd_cwnd_set(tp, min(tcp_snd_cwnd(tp), tp->snd_cwnd_cwamp));
}

static stwuct tcp_congestion_ops tcp_hybwa __wead_mostwy = {
	.init		= hybwa_init,
	.ssthwesh	= tcp_weno_ssthwesh,
	.undo_cwnd	= tcp_weno_undo_cwnd,
	.cong_avoid	= hybwa_cong_avoid,
	.set_state	= hybwa_state,

	.ownew		= THIS_MODUWE,
	.name		= "hybwa"
};

static int __init hybwa_wegistew(void)
{
	BUIWD_BUG_ON(sizeof(stwuct hybwa) > ICSK_CA_PWIV_SIZE);
	wetuwn tcp_wegistew_congestion_contwow(&tcp_hybwa);
}

static void __exit hybwa_unwegistew(void)
{
	tcp_unwegistew_congestion_contwow(&tcp_hybwa);
}

moduwe_init(hybwa_wegistew);
moduwe_exit(hybwa_unwegistew);

MODUWE_AUTHOW("Daniewe Wacamewa");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("TCP Hybwa");
