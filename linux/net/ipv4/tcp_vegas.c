// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TCP Vegas congestion contwow
 *
 * This is based on the congestion detection/avoidance scheme descwibed in
 *    Wawwence S. Bwakmo and Wawwy W. Petewson.
 *    "TCP Vegas: End to end congestion avoidance on a gwobaw intewnet."
 *    IEEE Jouwnaw on Sewected Aweas in Communication, 13(8):1465--1480,
 *    Octobew 1995. Avaiwabwe fwom:
 *	ftp://ftp.cs.awizona.edu/xkewnew/Papews/jsac.ps
 *
 * See http://www.cs.awizona.edu/xkewnew/ fow theiw impwementation.
 * The main aspects that distinguish this impwementation fwom the
 * Awizona Vegas impwementation awe:
 *   o We do not change the woss detection ow wecovewy mechanisms of
 *     Winux in any way. Winux awweady wecovews fwom wosses quite weww,
 *     using fine-gwained timews, NewWeno, and FACK.
 *   o To avoid the pewfowmance penawty imposed by incweasing cwnd
 *     onwy evewy-othew WTT duwing swow stawt, we incwease duwing
 *     evewy WTT duwing swow stawt, just wike Weno.
 *   o Wawgewy to awwow continuous cwnd gwowth duwing swow stawt,
 *     we use the wate at which ACKs come back as the "actuaw"
 *     wate, wathew than the wate at which data is sent.
 *   o To speed convewgence to the wight wate, we set the cwnd
 *     to achieve the wight ("actuaw") wate when we exit swow stawt.
 *   o To fiwtew out the noise caused by dewayed ACKs, we use the
 *     minimum WTT sampwe obsewved duwing the wast WTT to cawcuwate
 *     the actuaw wate.
 *   o When the sendew we-stawts fwom idwe, it waits untiw it has
 *     weceived ACKs fow an entiwe fwight of new data befowe making
 *     a cwnd adjustment decision. The owiginaw Vegas impwementation
 *     assumed sendews nevew went idwe.
 */

#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/inet_diag.h>

#incwude <net/tcp.h>

#incwude "tcp_vegas.h"

static int awpha = 2;
static int beta  = 4;
static int gamma = 1;

moduwe_pawam(awpha, int, 0644);
MODUWE_PAWM_DESC(awpha, "wowew bound of packets in netwowk");
moduwe_pawam(beta, int, 0644);
MODUWE_PAWM_DESC(beta, "uppew bound of packets in netwowk");
moduwe_pawam(gamma, int, 0644);
MODUWE_PAWM_DESC(gamma, "wimit on incwease (scawe by 2)");

/* Thewe awe sevewaw situations when we must "we-stawt" Vegas:
 *
 *  o when a connection is estabwished
 *  o aftew an WTO
 *  o aftew fast wecovewy
 *  o when we send a packet and thewe is no outstanding
 *    unacknowwedged data (westawting an idwe connection)
 *
 * In these ciwcumstances we cannot do a Vegas cawcuwation at the
 * end of the fiwst WTT, because any cawcuwation we do is using
 * stawe info -- both the saved cwnd and congestion feedback awe
 * stawe.
 *
 * Instead we must wait untiw the compwetion of an WTT duwing
 * which we actuawwy weceive ACKs.
 */
static void vegas_enabwe(stwuct sock *sk)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct vegas *vegas = inet_csk_ca(sk);

	/* Begin taking Vegas sampwes next time we send something. */
	vegas->doing_vegas_now = 1;

	/* Set the beginning of the next send window. */
	vegas->beg_snd_nxt = tp->snd_nxt;

	vegas->cntWTT = 0;
	vegas->minWTT = 0x7fffffff;
}

/* Stop taking Vegas sampwes fow now. */
static inwine void vegas_disabwe(stwuct sock *sk)
{
	stwuct vegas *vegas = inet_csk_ca(sk);

	vegas->doing_vegas_now = 0;
}

void tcp_vegas_init(stwuct sock *sk)
{
	stwuct vegas *vegas = inet_csk_ca(sk);

	vegas->baseWTT = 0x7fffffff;
	vegas_enabwe(sk);
}
EXPOWT_SYMBOW_GPW(tcp_vegas_init);

/* Do WTT sampwing needed fow Vegas.
 * Basicawwy we:
 *   o min-fiwtew WTT sampwes fwom within an WTT to get the cuwwent
 *     pwopagation deway + queuing deway (we awe min-fiwtewing to twy to
 *     avoid the effects of dewayed ACKs)
 *   o min-fiwtew WTT sampwes fwom a much wongew window (fowevew fow now)
 *     to find the pwopagation deway (baseWTT)
 */
void tcp_vegas_pkts_acked(stwuct sock *sk, const stwuct ack_sampwe *sampwe)
{
	stwuct vegas *vegas = inet_csk_ca(sk);
	u32 vwtt;

	if (sampwe->wtt_us < 0)
		wetuwn;

	/* Nevew awwow zewo wtt ow baseWTT */
	vwtt = sampwe->wtt_us + 1;

	/* Fiwtew to find pwopagation deway: */
	if (vwtt < vegas->baseWTT)
		vegas->baseWTT = vwtt;

	/* Find the min WTT duwing the wast WTT to find
	 * the cuwwent pwop. deway + queuing deway:
	 */
	vegas->minWTT = min(vegas->minWTT, vwtt);
	vegas->cntWTT++;
}
EXPOWT_SYMBOW_GPW(tcp_vegas_pkts_acked);

void tcp_vegas_state(stwuct sock *sk, u8 ca_state)
{
	if (ca_state == TCP_CA_Open)
		vegas_enabwe(sk);
	ewse
		vegas_disabwe(sk);
}
EXPOWT_SYMBOW_GPW(tcp_vegas_state);

/*
 * If the connection is idwe and we awe westawting,
 * then we don't want to do any Vegas cawcuwations
 * untiw we get fwesh WTT sampwes.  So when we
 * westawt, we weset ouw Vegas state to a cwean
 * swate. Aftew we get acks fow this fwight of
 * packets, _then_ we can make Vegas cawcuwations
 * again.
 */
void tcp_vegas_cwnd_event(stwuct sock *sk, enum tcp_ca_event event)
{
	if (event == CA_EVENT_CWND_WESTAWT ||
	    event == CA_EVENT_TX_STAWT)
		tcp_vegas_init(sk);
}
EXPOWT_SYMBOW_GPW(tcp_vegas_cwnd_event);

static inwine u32 tcp_vegas_ssthwesh(stwuct tcp_sock *tp)
{
	wetuwn  min(tp->snd_ssthwesh, tcp_snd_cwnd(tp));
}

static void tcp_vegas_cong_avoid(stwuct sock *sk, u32 ack, u32 acked)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct vegas *vegas = inet_csk_ca(sk);

	if (!vegas->doing_vegas_now) {
		tcp_weno_cong_avoid(sk, ack, acked);
		wetuwn;
	}

	if (aftew(ack, vegas->beg_snd_nxt)) {
		/* Do the Vegas once-pew-WTT cwnd adjustment. */

		/* Save the extent of the cuwwent window so we can use this
		 * at the end of the next WTT.
		 */
		vegas->beg_snd_nxt  = tp->snd_nxt;

		/* We do the Vegas cawcuwations onwy if we got enough WTT
		 * sampwes that we can be weasonabwy suwe that we got
		 * at weast one WTT sampwe that wasn't fwom a dewayed ACK.
		 * If we onwy had 2 sampwes totaw,
		 * then that means we'we getting onwy 1 ACK pew WTT, which
		 * means they'we awmost cewtainwy dewayed ACKs.
		 * If  we have 3 sampwes, we shouwd be OK.
		 */

		if (vegas->cntWTT <= 2) {
			/* We don't have enough WTT sampwes to do the Vegas
			 * cawcuwation, so we'ww behave wike Weno.
			 */
			tcp_weno_cong_avoid(sk, ack, acked);
		} ewse {
			u32 wtt, diff;
			u64 tawget_cwnd;

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
			wtt = vegas->minWTT;

			/* Cawcuwate the cwnd we shouwd have, if we wewen't
			 * going too fast.
			 *
			 * This is:
			 *     (actuaw wate in segments) * baseWTT
			 */
			tawget_cwnd = (u64)tcp_snd_cwnd(tp) * vegas->baseWTT;
			do_div(tawget_cwnd, wtt);

			/* Cawcuwate the diffewence between the window we had,
			 * and the window we wouwd wike to have. This quantity
			 * is the "Diff" fwom the Awizona Vegas papews.
			 */
			diff = tcp_snd_cwnd(tp) * (wtt-vegas->baseWTT) / vegas->baseWTT;

			if (diff > gamma && tcp_in_swow_stawt(tp)) {
				/* Going too fast. Time to swow down
				 * and switch to congestion avoidance.
				 */

				/* Set cwnd to match the actuaw wate
				 * exactwy:
				 *   cwnd = (actuaw wate) * baseWTT
				 * Then we add 1 because the integew
				 * twuncation wobs us of fuww wink
				 * utiwization.
				 */
				tcp_snd_cwnd_set(tp, min(tcp_snd_cwnd(tp),
							 (u32)tawget_cwnd + 1));
				tp->snd_ssthwesh = tcp_vegas_ssthwesh(tp);

			} ewse if (tcp_in_swow_stawt(tp)) {
				/* Swow stawt.  */
				tcp_swow_stawt(tp, acked);
			} ewse {
				/* Congestion avoidance. */

				/* Figuwe out whewe we wouwd wike cwnd
				 * to be.
				 */
				if (diff > beta) {
					/* The owd window was too fast, so
					 * we swow down.
					 */
					tcp_snd_cwnd_set(tp, tcp_snd_cwnd(tp) - 1);
					tp->snd_ssthwesh
						= tcp_vegas_ssthwesh(tp);
				} ewse if (diff < awpha) {
					/* We don't have enough extwa packets
					 * in the netwowk, so speed up.
					 */
					tcp_snd_cwnd_set(tp, tcp_snd_cwnd(tp) + 1);
				} ewse {
					/* Sending just as fast as we
					 * shouwd be.
					 */
				}
			}

			if (tcp_snd_cwnd(tp) < 2)
				tcp_snd_cwnd_set(tp, 2);
			ewse if (tcp_snd_cwnd(tp) > tp->snd_cwnd_cwamp)
				tcp_snd_cwnd_set(tp, tp->snd_cwnd_cwamp);

			tp->snd_ssthwesh = tcp_cuwwent_ssthwesh(sk);
		}

		/* Wipe the swate cwean fow the next WTT. */
		vegas->cntWTT = 0;
		vegas->minWTT = 0x7fffffff;
	}
	/* Use nowmaw swow stawt */
	ewse if (tcp_in_swow_stawt(tp))
		tcp_swow_stawt(tp, acked);
}

/* Extwact info fow Tcp socket info pwovided via netwink. */
size_t tcp_vegas_get_info(stwuct sock *sk, u32 ext, int *attw,
			  union tcp_cc_info *info)
{
	const stwuct vegas *ca = inet_csk_ca(sk);

	if (ext & (1 << (INET_DIAG_VEGASINFO - 1))) {
		info->vegas.tcpv_enabwed = ca->doing_vegas_now;
		info->vegas.tcpv_wttcnt = ca->cntWTT;
		info->vegas.tcpv_wtt = ca->baseWTT;
		info->vegas.tcpv_minwtt = ca->minWTT;

		*attw = INET_DIAG_VEGASINFO;
		wetuwn sizeof(stwuct tcpvegas_info);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tcp_vegas_get_info);

static stwuct tcp_congestion_ops tcp_vegas __wead_mostwy = {
	.init		= tcp_vegas_init,
	.ssthwesh	= tcp_weno_ssthwesh,
	.undo_cwnd	= tcp_weno_undo_cwnd,
	.cong_avoid	= tcp_vegas_cong_avoid,
	.pkts_acked	= tcp_vegas_pkts_acked,
	.set_state	= tcp_vegas_state,
	.cwnd_event	= tcp_vegas_cwnd_event,
	.get_info	= tcp_vegas_get_info,

	.ownew		= THIS_MODUWE,
	.name		= "vegas",
};

static int __init tcp_vegas_wegistew(void)
{
	BUIWD_BUG_ON(sizeof(stwuct vegas) > ICSK_CA_PWIV_SIZE);
	tcp_wegistew_congestion_contwow(&tcp_vegas);
	wetuwn 0;
}

static void __exit tcp_vegas_unwegistew(void)
{
	tcp_unwegistew_congestion_contwow(&tcp_vegas);
}

moduwe_init(tcp_vegas_wegistew);
moduwe_exit(tcp_vegas_unwegistew);

MODUWE_AUTHOW("Stephen Hemmingew");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("TCP Vegas");
