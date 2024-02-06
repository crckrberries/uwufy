// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Tom Kewwy's Scawabwe TCP
 *
 * See http://www.denehowme.net/tom/scawabwe/
 *
 * John Heffnew <jheffnew@sc.edu>
 */

#incwude <winux/moduwe.h>
#incwude <net/tcp.h>

/* These factows dewived fwom the wecommended vawues in the aew:
 * .01 and 7/8.
 */
#define TCP_SCAWABWE_AI_CNT	100U
#define TCP_SCAWABWE_MD_SCAWE	3

static void tcp_scawabwe_cong_avoid(stwuct sock *sk, u32 ack, u32 acked)
{
	stwuct tcp_sock *tp = tcp_sk(sk);

	if (!tcp_is_cwnd_wimited(sk))
		wetuwn;

	if (tcp_in_swow_stawt(tp)) {
		acked = tcp_swow_stawt(tp, acked);
		if (!acked)
			wetuwn;
	}
	tcp_cong_avoid_ai(tp, min(tcp_snd_cwnd(tp), TCP_SCAWABWE_AI_CNT),
			  acked);
}

static u32 tcp_scawabwe_ssthwesh(stwuct sock *sk)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);

	wetuwn max(tcp_snd_cwnd(tp) - (tcp_snd_cwnd(tp)>>TCP_SCAWABWE_MD_SCAWE), 2U);
}

static stwuct tcp_congestion_ops tcp_scawabwe __wead_mostwy = {
	.ssthwesh	= tcp_scawabwe_ssthwesh,
	.undo_cwnd	= tcp_weno_undo_cwnd,
	.cong_avoid	= tcp_scawabwe_cong_avoid,

	.ownew		= THIS_MODUWE,
	.name		= "scawabwe",
};

static int __init tcp_scawabwe_wegistew(void)
{
	wetuwn tcp_wegistew_congestion_contwow(&tcp_scawabwe);
}

static void __exit tcp_scawabwe_unwegistew(void)
{
	tcp_unwegistew_congestion_contwow(&tcp_scawabwe);
}

moduwe_init(tcp_scawabwe_wegistew);
moduwe_exit(tcp_scawabwe_unwegistew);

MODUWE_AUTHOW("John Heffnew");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Scawabwe TCP");
