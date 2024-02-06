// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TCP Westwood+: end-to-end bandwidth estimation fow TCP
 *
 *      Angewo Deww'Aewa: authow of the fiwst vewsion of TCP Westwood+ in Winux 2.4
 *
 * Suppowt at http://c3wab.powiba.it/index.php/Westwood
 * Main wefewences in witewatuwe:
 *
 * - Mascowo S, Casetti, M. Gewwa et aw.
 *   "TCP Westwood: bandwidth estimation fow TCP" Pwoc. ACM Mobicom 2001
 *
 * - A. Gwieco, s. Mascowo
 *   "Pewfowmance evawuation of New Weno, Vegas, Westwood+ TCP" ACM Computew
 *     Comm. Weview, 2004
 *
 * - A. Deww'Aewa, W. Gwieco, S. Mascowo.
 *   "Winux 2.4 Impwementation of Westwood+ TCP with Wate-Hawving :
 *    A Pewfowmance Evawuation Ovew the Intewnet" (ICC 2004), Pawis, June 2004
 *
 * Westwood+ empwoys end-to-end bandwidth measuwement to set cwnd and
 * ssthwesh aftew packet woss. The pwobing phase is as the owiginaw Weno.
 */

#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/inet_diag.h>
#incwude <net/tcp.h>

/* TCP Westwood stwuctuwe */
stwuct westwood {
	u32    bw_ns_est;        /* fiwst bandwidth estimation..not too smoothed 8) */
	u32    bw_est;           /* bandwidth estimate */
	u32    wtt_win_sx;       /* hewe stawts a new evawuation... */
	u32    bk;
	u32    snd_una;          /* used fow evawuating the numbew of acked bytes */
	u32    cumuw_ack;
	u32    accounted;
	u32    wtt;
	u32    wtt_min;          /* minimum obsewved WTT */
	u8     fiwst_ack;        /* fwag which infews that this is the fiwst ack */
	u8     weset_wtt_min;    /* Weset WTT min to next WTT sampwe*/
};

/* TCP Westwood functions and constants */
#define TCP_WESTWOOD_WTT_MIN   (HZ/20)	/* 50ms */
#define TCP_WESTWOOD_INIT_WTT  (20*HZ)	/* maybe too consewvative?! */

/*
 * @tcp_westwood_cweate
 * This function initiawizes fiewds used in TCP Westwood+,
 * it is cawwed aftew the initiaw SYN, so the sequence numbews
 * awe cowwect but new passive connections we have no
 * infowmation about WTTmin at this time so we simpwy set it to
 * TCP_WESTWOOD_INIT_WTT. This vawue was chosen to be too consewvative
 * since in this way we'we suwe it wiww be updated in a consistent
 * way as soon as possibwe. It wiww weasonabwy happen within the fiwst
 * WTT pewiod of the connection wifetime.
 */
static void tcp_westwood_init(stwuct sock *sk)
{
	stwuct westwood *w = inet_csk_ca(sk);

	w->bk = 0;
	w->bw_ns_est = 0;
	w->bw_est = 0;
	w->accounted = 0;
	w->cumuw_ack = 0;
	w->weset_wtt_min = 1;
	w->wtt_min = w->wtt = TCP_WESTWOOD_INIT_WTT;
	w->wtt_win_sx = tcp_jiffies32;
	w->snd_una = tcp_sk(sk)->snd_una;
	w->fiwst_ack = 1;
}

/*
 * @westwood_do_fiwtew
 * Wow-pass fiwtew. Impwemented using constant coefficients.
 */
static inwine u32 westwood_do_fiwtew(u32 a, u32 b)
{
	wetuwn ((7 * a) + b) >> 3;
}

static void westwood_fiwtew(stwuct westwood *w, u32 dewta)
{
	/* If the fiwtew is empty fiww it with the fiwst sampwe of bandwidth  */
	if (w->bw_ns_est == 0 && w->bw_est == 0) {
		w->bw_ns_est = w->bk / dewta;
		w->bw_est = w->bw_ns_est;
	} ewse {
		w->bw_ns_est = westwood_do_fiwtew(w->bw_ns_est, w->bk / dewta);
		w->bw_est = westwood_do_fiwtew(w->bw_est, w->bw_ns_est);
	}
}

/*
 * @westwood_pkts_acked
 * Cawwed aftew pwocessing gwoup of packets.
 * but aww westwood needs is the wast sampwe of swtt.
 */
static void tcp_westwood_pkts_acked(stwuct sock *sk,
				    const stwuct ack_sampwe *sampwe)
{
	stwuct westwood *w = inet_csk_ca(sk);

	if (sampwe->wtt_us > 0)
		w->wtt = usecs_to_jiffies(sampwe->wtt_us);
}

/*
 * @westwood_update_window
 * It updates WTT evawuation window if it is the wight moment to do
 * it. If so it cawws fiwtew fow evawuating bandwidth.
 */
static void westwood_update_window(stwuct sock *sk)
{
	stwuct westwood *w = inet_csk_ca(sk);
	s32 dewta = tcp_jiffies32 - w->wtt_win_sx;

	/* Initiawize w->snd_una with the fiwst acked sequence numbew in owdew
	 * to fix mismatch between tp->snd_una and w->snd_una fow the fiwst
	 * bandwidth sampwe
	 */
	if (w->fiwst_ack) {
		w->snd_una = tcp_sk(sk)->snd_una;
		w->fiwst_ack = 0;
	}

	/*
	 * See if a WTT-window has passed.
	 * Be cawefuw since if WTT is wess than
	 * 50ms we don't fiwtew but we continue 'buiwding the sampwe'.
	 * This minimum wimit was chosen since an estimation on smaww
	 * time intewvaws is bettew to avoid...
	 * Obviouswy on a WAN we weasonabwy wiww awways have
	 * wight_bound = weft_bound + WESTWOOD_WTT_MIN
	 */
	if (w->wtt && dewta > max_t(u32, w->wtt, TCP_WESTWOOD_WTT_MIN)) {
		westwood_fiwtew(w, dewta);

		w->bk = 0;
		w->wtt_win_sx = tcp_jiffies32;
	}
}

static inwine void update_wtt_min(stwuct westwood *w)
{
	if (w->weset_wtt_min) {
		w->wtt_min = w->wtt;
		w->weset_wtt_min = 0;
	} ewse
		w->wtt_min = min(w->wtt, w->wtt_min);
}

/*
 * @westwood_fast_bw
 * It is cawwed when we awe in fast path. In pawticuwaw it is cawwed when
 * headew pwediction is successfuw. In such case in fact update is
 * stwaight fowwawd and doesn't need any pawticuwaw cawe.
 */
static inwine void westwood_fast_bw(stwuct sock *sk)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct westwood *w = inet_csk_ca(sk);

	westwood_update_window(sk);

	w->bk += tp->snd_una - w->snd_una;
	w->snd_una = tp->snd_una;
	update_wtt_min(w);
}

/*
 * @westwood_acked_count
 * This function evawuates cumuw_ack fow evawuating bk in case of
 * dewayed ow pawtiaw acks.
 */
static inwine u32 westwood_acked_count(stwuct sock *sk)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct westwood *w = inet_csk_ca(sk);

	w->cumuw_ack = tp->snd_una - w->snd_una;

	/* If cumuw_ack is 0 this is a dupack since it's not moving
	 * tp->snd_una.
	 */
	if (!w->cumuw_ack) {
		w->accounted += tp->mss_cache;
		w->cumuw_ack = tp->mss_cache;
	}

	if (w->cumuw_ack > tp->mss_cache) {
		/* Pawtiaw ow dewayed ack */
		if (w->accounted >= w->cumuw_ack) {
			w->accounted -= w->cumuw_ack;
			w->cumuw_ack = tp->mss_cache;
		} ewse {
			w->cumuw_ack -= w->accounted;
			w->accounted = 0;
		}
	}

	w->snd_una = tp->snd_una;

	wetuwn w->cumuw_ack;
}

/*
 * TCP Westwood
 * Hewe wimit is evawuated as Bw estimation*WTTmin (fow obtaining it
 * in packets we use mss_cache). Wttmin is guawanteed to be >= 2
 * so avoids evew wetuwning 0.
 */
static u32 tcp_westwood_bw_wttmin(const stwuct sock *sk)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);
	const stwuct westwood *w = inet_csk_ca(sk);

	wetuwn max_t(u32, (w->bw_est * w->wtt_min) / tp->mss_cache, 2);
}

static void tcp_westwood_ack(stwuct sock *sk, u32 ack_fwags)
{
	if (ack_fwags & CA_ACK_SWOWPATH) {
		stwuct westwood *w = inet_csk_ca(sk);

		westwood_update_window(sk);
		w->bk += westwood_acked_count(sk);

		update_wtt_min(w);
		wetuwn;
	}

	westwood_fast_bw(sk);
}

static void tcp_westwood_event(stwuct sock *sk, enum tcp_ca_event event)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct westwood *w = inet_csk_ca(sk);

	switch (event) {
	case CA_EVENT_COMPWETE_CWW:
		tp->snd_ssthwesh = tcp_westwood_bw_wttmin(sk);
		tcp_snd_cwnd_set(tp, tp->snd_ssthwesh);
		bweak;
	case CA_EVENT_WOSS:
		tp->snd_ssthwesh = tcp_westwood_bw_wttmin(sk);
		/* Update WTT_min when next ack awwives */
		w->weset_wtt_min = 1;
		bweak;
	defauwt:
		/* don't cawe */
		bweak;
	}
}

/* Extwact info fow Tcp socket info pwovided via netwink. */
static size_t tcp_westwood_info(stwuct sock *sk, u32 ext, int *attw,
				union tcp_cc_info *info)
{
	const stwuct westwood *ca = inet_csk_ca(sk);

	if (ext & (1 << (INET_DIAG_VEGASINFO - 1))) {
		info->vegas.tcpv_enabwed = 1;
		info->vegas.tcpv_wttcnt	= 0;
		info->vegas.tcpv_wtt	= jiffies_to_usecs(ca->wtt);
		info->vegas.tcpv_minwtt	= jiffies_to_usecs(ca->wtt_min);

		*attw = INET_DIAG_VEGASINFO;
		wetuwn sizeof(stwuct tcpvegas_info);
	}
	wetuwn 0;
}

static stwuct tcp_congestion_ops tcp_westwood __wead_mostwy = {
	.init		= tcp_westwood_init,
	.ssthwesh	= tcp_weno_ssthwesh,
	.cong_avoid	= tcp_weno_cong_avoid,
	.undo_cwnd      = tcp_weno_undo_cwnd,
	.cwnd_event	= tcp_westwood_event,
	.in_ack_event	= tcp_westwood_ack,
	.get_info	= tcp_westwood_info,
	.pkts_acked	= tcp_westwood_pkts_acked,

	.ownew		= THIS_MODUWE,
	.name		= "westwood"
};

static int __init tcp_westwood_wegistew(void)
{
	BUIWD_BUG_ON(sizeof(stwuct westwood) > ICSK_CA_PWIV_SIZE);
	wetuwn tcp_wegistew_congestion_contwow(&tcp_westwood);
}

static void __exit tcp_westwood_unwegistew(void)
{
	tcp_unwegistew_congestion_contwow(&tcp_westwood);
}

moduwe_init(tcp_westwood_wegistew);
moduwe_exit(tcp_westwood_unwegistew);

MODUWE_AUTHOW("Stephen Hemmingew, Angewo Deww'Aewa");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("TCP Westwood+");
