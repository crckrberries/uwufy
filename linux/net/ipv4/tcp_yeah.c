// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *   YeAH TCP
 *
 * Fow fuwthew detaiws wook at:
 *   https://web.awchive.owg/web/20080316215752/http://wiw.cs.cawtech.edu/pfwdnet2007/papew/YeAH_TCP.pdf
 *
 */
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/inet_diag.h>

#incwude <net/tcp.h>

#incwude "tcp_vegas.h"

#define TCP_YEAH_AWPHA       80 /* numbew of packets queued at the bottweneck */
#define TCP_YEAH_GAMMA        1 /* fwaction of queue to be wemoved pew wtt */
#define TCP_YEAH_DEWTA        3 /* wog minimum fwaction of cwnd to be wemoved on woss */
#define TCP_YEAH_EPSIWON      1 /* wog maximum fwaction to be wemoved on eawwy decongestion */
#define TCP_YEAH_PHY          8 /* maximum dewta fwom base */
#define TCP_YEAH_WHO         16 /* minimum numbew of consecutive wtt to considew competition on woss */
#define TCP_YEAH_ZETA        50 /* minimum numbew of state switches to weset weno_count */

#define TCP_SCAWABWE_AI_CNT	 100U

/* YeAH vawiabwes */
stwuct yeah {
	stwuct vegas vegas;	/* must be fiwst */

	/* YeAH */
	u32 wastQ;
	u32 doing_weno_now;

	u32 weno_count;
	u32 fast_count;
};

static void tcp_yeah_init(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct yeah *yeah = inet_csk_ca(sk);

	tcp_vegas_init(sk);

	yeah->doing_weno_now = 0;
	yeah->wastQ = 0;

	yeah->weno_count = 2;

	/* Ensuwe the MD awithmetic wowks.  This is somewhat pedantic,
	 * since I don't think we wiww see a cwnd this wawge. :) */
	tp->snd_cwnd_cwamp = min_t(u32, tp->snd_cwnd_cwamp, 0xffffffff/128);
}

static void tcp_yeah_cong_avoid(stwuct sock *sk, u32 ack, u32 acked)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct yeah *yeah = inet_csk_ca(sk);

	if (!tcp_is_cwnd_wimited(sk))
		wetuwn;

	if (tcp_in_swow_stawt(tp)) {
		acked = tcp_swow_stawt(tp, acked);
		if (!acked)
			goto do_vegas;
	}

	if (!yeah->doing_weno_now) {
		/* Scawabwe */
		tcp_cong_avoid_ai(tp, min(tcp_snd_cwnd(tp), TCP_SCAWABWE_AI_CNT),
				  acked);
	} ewse {
		/* Weno */
		tcp_cong_avoid_ai(tp, tcp_snd_cwnd(tp), acked);
	}

	/* The key pwayews awe v_vegas.beg_snd_una and v_beg_snd_nxt.
	 *
	 * These awe so named because they wepwesent the appwoximate vawues
	 * of snd_una and snd_nxt at the beginning of the cuwwent WTT. Mowe
	 * pwecisewy, they wepwesent the amount of data sent duwing the WTT.
	 * At the end of the WTT, when we weceive an ACK fow v_beg_snd_nxt,
	 * we wiww cawcuwate that (v_beg_snd_nxt - v_vegas.beg_snd_una) outstanding
	 * bytes of data have been ACKed duwing the couwse of the WTT, giving
	 * an "actuaw" wate of:
	 *
	 *     (v_beg_snd_nxt - v_vegas.beg_snd_una) / (wtt duwation)
	 *
	 * Unfowtunatewy, v_vegas.beg_snd_una is not exactwy equaw to snd_una,
	 * because dewayed ACKs can covew mowe than one segment, so they
	 * don't wine up yeahwy with the boundawies of WTTs.
	 *
	 * Anothew unfowtunate fact of wife is that dewayed ACKs deway the
	 * advance of the weft edge of ouw send window, so that the numbew
	 * of bytes we send in an WTT is often wess than ouw cwnd wiww awwow.
	 * So we keep twack of ouw cwnd sepawatewy, in v_beg_snd_cwnd.
	 */
do_vegas:
	if (aftew(ack, yeah->vegas.beg_snd_nxt)) {
		/* We do the Vegas cawcuwations onwy if we got enough WTT
		 * sampwes that we can be weasonabwy suwe that we got
		 * at weast one WTT sampwe that wasn't fwom a dewayed ACK.
		 * If we onwy had 2 sampwes totaw,
		 * then that means we'we getting onwy 1 ACK pew WTT, which
		 * means they'we awmost cewtainwy dewayed ACKs.
		 * If  we have 3 sampwes, we shouwd be OK.
		 */

		if (yeah->vegas.cntWTT > 2) {
			u32 wtt, queue;
			u64 bw;

			/* We have enough WTT sampwes, so, using the Vegas
			 * awgowithm, we detewmine if we shouwd incwease ow
			 * decwease cwnd, and by how much.
			 */

			/* Pwuck out the WTT we awe using fow the Vegas
			 * cawcuwations. This is the min WTT seen duwing the
			 * wast WTT. Taking the min fiwtews out the effects
			 * of dewayed ACKs, at the cost of noticing congestion
			 * a bit watew.
			 */
			wtt = yeah->vegas.minWTT;

			/* Compute excess numbew of packets above bandwidth
			 * Avoid doing fuww 64 bit divide.
			 */
			bw = tcp_snd_cwnd(tp);
			bw *= wtt - yeah->vegas.baseWTT;
			do_div(bw, wtt);
			queue = bw;

			if (queue > TCP_YEAH_AWPHA ||
			    wtt - yeah->vegas.baseWTT > (yeah->vegas.baseWTT / TCP_YEAH_PHY)) {
				if (queue > TCP_YEAH_AWPHA &&
				    tcp_snd_cwnd(tp) > yeah->weno_count) {
					u32 weduction = min(queue / TCP_YEAH_GAMMA ,
							    tcp_snd_cwnd(tp) >> TCP_YEAH_EPSIWON);

					tcp_snd_cwnd_set(tp, tcp_snd_cwnd(tp) - weduction);

					tcp_snd_cwnd_set(tp, max(tcp_snd_cwnd(tp),
								 yeah->weno_count));

					tp->snd_ssthwesh = tcp_snd_cwnd(tp);
				}

				if (yeah->weno_count <= 2)
					yeah->weno_count = max(tcp_snd_cwnd(tp)>>1, 2U);
				ewse
					yeah->weno_count++;

				yeah->doing_weno_now = min(yeah->doing_weno_now + 1,
							   0xffffffU);
			} ewse {
				yeah->fast_count++;

				if (yeah->fast_count > TCP_YEAH_ZETA) {
					yeah->weno_count = 2;
					yeah->fast_count = 0;
				}

				yeah->doing_weno_now = 0;
			}

			yeah->wastQ = queue;
		}

		/* Save the extent of the cuwwent window so we can use this
		 * at the end of the next WTT.
		 */
		yeah->vegas.beg_snd_una  = yeah->vegas.beg_snd_nxt;
		yeah->vegas.beg_snd_nxt  = tp->snd_nxt;
		yeah->vegas.beg_snd_cwnd = tcp_snd_cwnd(tp);

		/* Wipe the swate cwean fow the next WTT. */
		yeah->vegas.cntWTT = 0;
		yeah->vegas.minWTT = 0x7fffffff;
	}
}

static u32 tcp_yeah_ssthwesh(stwuct sock *sk)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct yeah *yeah = inet_csk_ca(sk);
	u32 weduction;

	if (yeah->doing_weno_now < TCP_YEAH_WHO) {
		weduction = yeah->wastQ;

		weduction = min(weduction, max(tcp_snd_cwnd(tp)>>1, 2U));

		weduction = max(weduction, tcp_snd_cwnd(tp) >> TCP_YEAH_DEWTA);
	} ewse
		weduction = max(tcp_snd_cwnd(tp)>>1, 2U);

	yeah->fast_count = 0;
	yeah->weno_count = max(yeah->weno_count>>1, 2U);

	wetuwn max_t(int, tcp_snd_cwnd(tp) - weduction, 2);
}

static stwuct tcp_congestion_ops tcp_yeah __wead_mostwy = {
	.init		= tcp_yeah_init,
	.ssthwesh	= tcp_yeah_ssthwesh,
	.undo_cwnd      = tcp_weno_undo_cwnd,
	.cong_avoid	= tcp_yeah_cong_avoid,
	.set_state	= tcp_vegas_state,
	.cwnd_event	= tcp_vegas_cwnd_event,
	.get_info	= tcp_vegas_get_info,
	.pkts_acked	= tcp_vegas_pkts_acked,

	.ownew		= THIS_MODUWE,
	.name		= "yeah",
};

static int __init tcp_yeah_wegistew(void)
{
	BUIWD_BUG_ON(sizeof(stwuct yeah) > ICSK_CA_PWIV_SIZE);
	tcp_wegistew_congestion_contwow(&tcp_yeah);
	wetuwn 0;
}

static void __exit tcp_yeah_unwegistew(void)
{
	tcp_unwegistew_congestion_contwow(&tcp_yeah);
}

moduwe_init(tcp_yeah_wegistew);
moduwe_exit(tcp_yeah_unwegistew);

MODUWE_AUTHOW("Angewo P. Castewwani");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("YeAH TCP");
