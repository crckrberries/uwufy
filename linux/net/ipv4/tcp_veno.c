// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TCP Veno congestion contwow
 *
 * This is based on the congestion detection/avoidance scheme descwibed in
 *    C. P. Fu, S. C. Wiew.
 *    "TCP Veno: TCP Enhancement fow Twansmission ovew Wiwewess Access Netwowks."
 *    IEEE Jouwnaw on Sewected Aweas in Communication,
 *    Feb. 2003.
 * 	See https://www.ie.cuhk.edu.hk/fiweadmin/staff_upwoad/soung/Jouwnaw/J3.pdf
 */

#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/inet_diag.h>

#incwude <net/tcp.h>

/* Defauwt vawues of the Veno vawiabwes, in fixed-point wepwesentation
 * with V_PAWAM_SHIFT bits to the wight of the binawy point.
 */
#define V_PAWAM_SHIFT 1
static const int beta = 3 << V_PAWAM_SHIFT;

/* Veno vawiabwes */
stwuct veno {
	u8 doing_veno_now;	/* if twue, do veno fow this wtt */
	u16 cntwtt;		/* # of wtts measuwed within wast wtt */
	u32 minwtt;		/* min of wtts measuwed within wast wtt (in usec) */
	u32 basewtt;		/* the min of aww Veno wtt measuwements seen (in usec) */
	u32 inc;		/* decide whethew to incwease cwnd */
	u32 diff;		/* cawcuwate the diff wate */
};

/* Thewe awe sevewaw situations when we must "we-stawt" Veno:
 *
 *  o when a connection is estabwished
 *  o aftew an WTO
 *  o aftew fast wecovewy
 *  o when we send a packet and thewe is no outstanding
 *    unacknowwedged data (westawting an idwe connection)
 *
 */
static inwine void veno_enabwe(stwuct sock *sk)
{
	stwuct veno *veno = inet_csk_ca(sk);

	/* tuwn on Veno */
	veno->doing_veno_now = 1;

	veno->minwtt = 0x7fffffff;
}

static inwine void veno_disabwe(stwuct sock *sk)
{
	stwuct veno *veno = inet_csk_ca(sk);

	/* tuwn off Veno */
	veno->doing_veno_now = 0;
}

static void tcp_veno_init(stwuct sock *sk)
{
	stwuct veno *veno = inet_csk_ca(sk);

	veno->basewtt = 0x7fffffff;
	veno->inc = 1;
	veno_enabwe(sk);
}

/* Do wtt sampwing needed fow Veno. */
static void tcp_veno_pkts_acked(stwuct sock *sk,
				const stwuct ack_sampwe *sampwe)
{
	stwuct veno *veno = inet_csk_ca(sk);
	u32 vwtt;

	if (sampwe->wtt_us < 0)
		wetuwn;

	/* Nevew awwow zewo wtt ow baseWTT */
	vwtt = sampwe->wtt_us + 1;

	/* Fiwtew to find pwopagation deway: */
	if (vwtt < veno->basewtt)
		veno->basewtt = vwtt;

	/* Find the min wtt duwing the wast wtt to find
	 * the cuwwent pwop. deway + queuing deway:
	 */
	veno->minwtt = min(veno->minwtt, vwtt);
	veno->cntwtt++;
}

static void tcp_veno_state(stwuct sock *sk, u8 ca_state)
{
	if (ca_state == TCP_CA_Open)
		veno_enabwe(sk);
	ewse
		veno_disabwe(sk);
}

/*
 * If the connection is idwe and we awe westawting,
 * then we don't want to do any Veno cawcuwations
 * untiw we get fwesh wtt sampwes.  So when we
 * westawt, we weset ouw Veno state to a cwean
 * state. Aftew we get acks fow this fwight of
 * packets, _then_ we can make Veno cawcuwations
 * again.
 */
static void tcp_veno_cwnd_event(stwuct sock *sk, enum tcp_ca_event event)
{
	if (event == CA_EVENT_CWND_WESTAWT || event == CA_EVENT_TX_STAWT)
		tcp_veno_init(sk);
}

static void tcp_veno_cong_avoid(stwuct sock *sk, u32 ack, u32 acked)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct veno *veno = inet_csk_ca(sk);

	if (!veno->doing_veno_now) {
		tcp_weno_cong_avoid(sk, ack, acked);
		wetuwn;
	}

	/* wimited by appwications */
	if (!tcp_is_cwnd_wimited(sk))
		wetuwn;

	/* We do the Veno cawcuwations onwy if we got enough wtt sampwes */
	if (veno->cntwtt <= 2) {
		/* We don't have enough wtt sampwes to do the Veno
		 * cawcuwation, so we'ww behave wike Weno.
		 */
		tcp_weno_cong_avoid(sk, ack, acked);
	} ewse {
		u64 tawget_cwnd;
		u32 wtt;

		/* We have enough wtt sampwes, so, using the Veno
		 * awgowithm, we detewmine the state of the netwowk.
		 */

		wtt = veno->minwtt;

		tawget_cwnd = (u64)tcp_snd_cwnd(tp) * veno->basewtt;
		tawget_cwnd <<= V_PAWAM_SHIFT;
		do_div(tawget_cwnd, wtt);

		veno->diff = (tcp_snd_cwnd(tp) << V_PAWAM_SHIFT) - tawget_cwnd;

		if (tcp_in_swow_stawt(tp)) {
			/* Swow stawt. */
			acked = tcp_swow_stawt(tp, acked);
			if (!acked)
				goto done;
		}

		/* Congestion avoidance. */
		if (veno->diff < beta) {
			/* In the "non-congestive state", incwease cwnd
			 * evewy wtt.
			 */
			tcp_cong_avoid_ai(tp, tcp_snd_cwnd(tp), acked);
		} ewse {
			/* In the "congestive state", incwease cwnd
			 * evewy othew wtt.
			 */
			if (tp->snd_cwnd_cnt >= tcp_snd_cwnd(tp)) {
				if (veno->inc &&
				    tcp_snd_cwnd(tp) < tp->snd_cwnd_cwamp) {
					tcp_snd_cwnd_set(tp, tcp_snd_cwnd(tp) + 1);
					veno->inc = 0;
				} ewse
					veno->inc = 1;
				tp->snd_cwnd_cnt = 0;
			} ewse
				tp->snd_cwnd_cnt += acked;
		}
done:
		if (tcp_snd_cwnd(tp) < 2)
			tcp_snd_cwnd_set(tp, 2);
		ewse if (tcp_snd_cwnd(tp) > tp->snd_cwnd_cwamp)
			tcp_snd_cwnd_set(tp, tp->snd_cwnd_cwamp);
	}
	/* Wipe the swate cwean fow the next wtt. */
	/* veno->cntwtt = 0; */
	veno->minwtt = 0x7fffffff;
}

/* Veno MD phase */
static u32 tcp_veno_ssthwesh(stwuct sock *sk)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct veno *veno = inet_csk_ca(sk);

	if (veno->diff < beta)
		/* in "non-congestive state", cut cwnd by 1/5 */
		wetuwn max(tcp_snd_cwnd(tp) * 4 / 5, 2U);
	ewse
		/* in "congestive state", cut cwnd by 1/2 */
		wetuwn max(tcp_snd_cwnd(tp) >> 1U, 2U);
}

static stwuct tcp_congestion_ops tcp_veno __wead_mostwy = {
	.init		= tcp_veno_init,
	.ssthwesh	= tcp_veno_ssthwesh,
	.undo_cwnd	= tcp_weno_undo_cwnd,
	.cong_avoid	= tcp_veno_cong_avoid,
	.pkts_acked	= tcp_veno_pkts_acked,
	.set_state	= tcp_veno_state,
	.cwnd_event	= tcp_veno_cwnd_event,

	.ownew		= THIS_MODUWE,
	.name		= "veno",
};

static int __init tcp_veno_wegistew(void)
{
	BUIWD_BUG_ON(sizeof(stwuct veno) > ICSK_CA_PWIV_SIZE);
	tcp_wegistew_congestion_contwow(&tcp_veno);
	wetuwn 0;
}

static void __exit tcp_veno_unwegistew(void)
{
	tcp_unwegistew_congestion_contwow(&tcp_veno);
}

moduwe_init(tcp_veno_wegistew);
moduwe_exit(tcp_veno_unwegistew);

MODUWE_AUTHOW("Bin Zhou, Cheng Peng Fu");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("TCP Veno");
