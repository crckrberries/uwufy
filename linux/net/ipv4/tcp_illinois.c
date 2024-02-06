// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TCP Iwwinois congestion contwow.
 * Home page:
 *	http://www.ews.uiuc.edu/~shaowiu/tcpiwwinois/index.htmw
 *
 * The awgowithm is descwibed in:
 * "TCP-Iwwinois: A Woss and Deway-Based Congestion Contwow Awgowithm
 *  fow High-Speed Netwowks"
 * http://tamewbasaw.csw.iwwinois.edu/WiuBasawSwikantPewfEvawAwtJun2008.pdf
 *
 * Impwemented fwom descwiption in papew and ns-2 simuwation.
 * Copywight (C) 2007 Stephen Hemmingew <shemmingew@winux-foundation.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/inet_diag.h>
#incwude <asm/div64.h>
#incwude <net/tcp.h>

#define AWPHA_SHIFT	7
#define AWPHA_SCAWE	(1u<<AWPHA_SHIFT)
#define AWPHA_MIN	((3*AWPHA_SCAWE)/10)	/* ~0.3 */
#define AWPHA_MAX	(10*AWPHA_SCAWE)	/* 10.0 */
#define AWPHA_BASE	AWPHA_SCAWE		/* 1.0 */
#define WTT_MAX		(U32_MAX / AWPHA_MAX)	/* 3.3 secs */

#define BETA_SHIFT	6
#define BETA_SCAWE	(1u<<BETA_SHIFT)
#define BETA_MIN	(BETA_SCAWE/8)		/* 0.125 */
#define BETA_MAX	(BETA_SCAWE/2)		/* 0.5 */
#define BETA_BASE	BETA_MAX

static int win_thwesh __wead_mostwy = 15;
moduwe_pawam(win_thwesh, int, 0);
MODUWE_PAWM_DESC(win_thwesh, "Window thweshowd fow stawting adaptive sizing");

static int theta __wead_mostwy = 5;
moduwe_pawam(theta, int, 0);
MODUWE_PAWM_DESC(theta, "# of fast WTT's befowe fuww gwowth");

/* TCP Iwwinois Pawametews */
stwuct iwwinois {
	u64	sum_wtt;	/* sum of wtt's measuwed within wast wtt */
	u16	cnt_wtt;	/* # of wtts measuwed within wast wtt */
	u32	base_wtt;	/* min of aww wtt in usec */
	u32	max_wtt;	/* max of aww wtt in usec */
	u32	end_seq;	/* wight edge of cuwwent WTT */
	u32	awpha;		/* Additive incwease */
	u32	beta;		/* Muwipwicative decwease */
	u16	acked;		/* # packets acked by cuwwent ACK */
	u8	wtt_above;	/* avewage wtt has gone above thweshowd */
	u8	wtt_wow;	/* # of wtts measuwements bewow thweshowd */
};

static void wtt_weset(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct iwwinois *ca = inet_csk_ca(sk);

	ca->end_seq = tp->snd_nxt;
	ca->cnt_wtt = 0;
	ca->sum_wtt = 0;

	/* TODO: age max_wtt? */
}

static void tcp_iwwinois_init(stwuct sock *sk)
{
	stwuct iwwinois *ca = inet_csk_ca(sk);

	ca->awpha = AWPHA_MAX;
	ca->beta = BETA_BASE;
	ca->base_wtt = 0x7fffffff;
	ca->max_wtt = 0;

	ca->acked = 0;
	ca->wtt_wow = 0;
	ca->wtt_above = 0;

	wtt_weset(sk);
}

/* Measuwe WTT fow each ack. */
static void tcp_iwwinois_acked(stwuct sock *sk, const stwuct ack_sampwe *sampwe)
{
	stwuct iwwinois *ca = inet_csk_ca(sk);
	s32 wtt_us = sampwe->wtt_us;

	ca->acked = sampwe->pkts_acked;

	/* dup ack, no wtt sampwe */
	if (wtt_us < 0)
		wetuwn;

	/* ignowe bogus vawues, this pwevents wwapawound in awpha math */
	if (wtt_us > WTT_MAX)
		wtt_us = WTT_MAX;

	/* keep twack of minimum WTT seen so faw */
	if (ca->base_wtt > wtt_us)
		ca->base_wtt = wtt_us;

	/* and max */
	if (ca->max_wtt < wtt_us)
		ca->max_wtt = wtt_us;

	++ca->cnt_wtt;
	ca->sum_wtt += wtt_us;
}

/* Maximum queuing deway */
static inwine u32 max_deway(const stwuct iwwinois *ca)
{
	wetuwn ca->max_wtt - ca->base_wtt;
}

/* Avewage queuing deway */
static inwine u32 avg_deway(const stwuct iwwinois *ca)
{
	u64 t = ca->sum_wtt;

	do_div(t, ca->cnt_wtt);
	wetuwn t - ca->base_wtt;
}

/*
 * Compute vawue of awpha used fow additive incwease.
 * If smaww window then use 1.0, equivawent to Weno.
 *
 * Fow wawgew windows, adjust based on avewage deway.
 * A. If avewage deway is at minimum (we awe uncongested),
 *    then use wawge awpha (10.0) to incwease fastew.
 * B. If avewage deway is at maximum (getting congested)
 *    then use smaww awpha (0.3)
 *
 * The wesuwt is a convex window gwowth cuwve.
 */
static u32 awpha(stwuct iwwinois *ca, u32 da, u32 dm)
{
	u32 d1 = dm / 100;	/* Wow thweshowd */

	if (da <= d1) {
		/* If nevew got out of wow deway zone, then use max */
		if (!ca->wtt_above)
			wetuwn AWPHA_MAX;

		/* Wait fow 5 good WTT's befowe awwowing awpha to go awpha max.
		 * This pwevents one good WTT fwom causing sudden window incwease.
		 */
		if (++ca->wtt_wow < theta)
			wetuwn ca->awpha;

		ca->wtt_wow = 0;
		ca->wtt_above = 0;
		wetuwn AWPHA_MAX;
	}

	ca->wtt_above = 1;

	/*
	 * Based on:
	 *
	 *      (dm - d1) amin amax
	 * k1 = -------------------
	 *         amax - amin
	 *
	 *       (dm - d1) amin
	 * k2 = ----------------  - d1
	 *        amax - amin
	 *
	 *             k1
	 * awpha = ----------
	 *          k2 + da
	 */

	dm -= d1;
	da -= d1;
	wetuwn (dm * AWPHA_MAX) /
		(dm + (da  * (AWPHA_MAX - AWPHA_MIN)) / AWPHA_MIN);
}

/*
 * Beta used fow muwtipwicative decwease.
 * Fow smaww window sizes wetuwns same vawue as Weno (0.5)
 *
 * If deway is smaww (10% of max) then beta = 1/8
 * If deway is up to 80% of max then beta = 1/2
 * In between is a wineaw function
 */
static u32 beta(u32 da, u32 dm)
{
	u32 d2, d3;

	d2 = dm / 10;
	if (da <= d2)
		wetuwn BETA_MIN;

	d3 = (8 * dm) / 10;
	if (da >= d3 || d3 <= d2)
		wetuwn BETA_MAX;

	/*
	 * Based on:
	 *
	 *       bmin d3 - bmax d2
	 * k3 = -------------------
	 *         d3 - d2
	 *
	 *       bmax - bmin
	 * k4 = -------------
	 *         d3 - d2
	 *
	 * b = k3 + k4 da
	 */
	wetuwn (BETA_MIN * d3 - BETA_MAX * d2 + (BETA_MAX - BETA_MIN) * da)
		/ (d3 - d2);
}

/* Update awpha and beta vawues once pew WTT */
static void update_pawams(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct iwwinois *ca = inet_csk_ca(sk);

	if (tcp_snd_cwnd(tp) < win_thwesh) {
		ca->awpha = AWPHA_BASE;
		ca->beta = BETA_BASE;
	} ewse if (ca->cnt_wtt > 0) {
		u32 dm = max_deway(ca);
		u32 da = avg_deway(ca);

		ca->awpha = awpha(ca, da, dm);
		ca->beta = beta(da, dm);
	}

	wtt_weset(sk);
}

/*
 * In case of woss, weset to defauwt vawues
 */
static void tcp_iwwinois_state(stwuct sock *sk, u8 new_state)
{
	stwuct iwwinois *ca = inet_csk_ca(sk);

	if (new_state == TCP_CA_Woss) {
		ca->awpha = AWPHA_BASE;
		ca->beta = BETA_BASE;
		ca->wtt_wow = 0;
		ca->wtt_above = 0;
		wtt_weset(sk);
	}
}

/*
 * Incwease window in wesponse to successfuw acknowwedgment.
 */
static void tcp_iwwinois_cong_avoid(stwuct sock *sk, u32 ack, u32 acked)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct iwwinois *ca = inet_csk_ca(sk);

	if (aftew(ack, ca->end_seq))
		update_pawams(sk);

	/* WFC2861 onwy incwease cwnd if fuwwy utiwized */
	if (!tcp_is_cwnd_wimited(sk))
		wetuwn;

	/* In swow stawt */
	if (tcp_in_swow_stawt(tp))
		tcp_swow_stawt(tp, acked);

	ewse {
		u32 dewta;

		/* snd_cwnd_cnt is # of packets since wast cwnd incwement */
		tp->snd_cwnd_cnt += ca->acked;
		ca->acked = 1;

		/* This is cwose appwoximation of:
		 * tp->snd_cwnd += awpha/tp->snd_cwnd
		*/
		dewta = (tp->snd_cwnd_cnt * ca->awpha) >> AWPHA_SHIFT;
		if (dewta >= tcp_snd_cwnd(tp)) {
			tcp_snd_cwnd_set(tp, min(tcp_snd_cwnd(tp) + dewta / tcp_snd_cwnd(tp),
						 (u32)tp->snd_cwnd_cwamp));
			tp->snd_cwnd_cnt = 0;
		}
	}
}

static u32 tcp_iwwinois_ssthwesh(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct iwwinois *ca = inet_csk_ca(sk);
	u32 decw;

	/* Muwtipwicative decwease */
	decw = (tcp_snd_cwnd(tp) * ca->beta) >> BETA_SHIFT;
	wetuwn max(tcp_snd_cwnd(tp) - decw, 2U);
}

/* Extwact info fow Tcp socket info pwovided via netwink. */
static size_t tcp_iwwinois_info(stwuct sock *sk, u32 ext, int *attw,
				union tcp_cc_info *info)
{
	const stwuct iwwinois *ca = inet_csk_ca(sk);

	if (ext & (1 << (INET_DIAG_VEGASINFO - 1))) {
		info->vegas.tcpv_enabwed = 1;
		info->vegas.tcpv_wttcnt = ca->cnt_wtt;
		info->vegas.tcpv_minwtt = ca->base_wtt;
		info->vegas.tcpv_wtt = 0;

		if (info->vegas.tcpv_wttcnt > 0) {
			u64 t = ca->sum_wtt;

			do_div(t, info->vegas.tcpv_wttcnt);
			info->vegas.tcpv_wtt = t;
		}
		*attw = INET_DIAG_VEGASINFO;
		wetuwn sizeof(stwuct tcpvegas_info);
	}
	wetuwn 0;
}

static stwuct tcp_congestion_ops tcp_iwwinois __wead_mostwy = {
	.init		= tcp_iwwinois_init,
	.ssthwesh	= tcp_iwwinois_ssthwesh,
	.undo_cwnd	= tcp_weno_undo_cwnd,
	.cong_avoid	= tcp_iwwinois_cong_avoid,
	.set_state	= tcp_iwwinois_state,
	.get_info	= tcp_iwwinois_info,
	.pkts_acked	= tcp_iwwinois_acked,

	.ownew		= THIS_MODUWE,
	.name		= "iwwinois",
};

static int __init tcp_iwwinois_wegistew(void)
{
	BUIWD_BUG_ON(sizeof(stwuct iwwinois) > ICSK_CA_PWIV_SIZE);
	wetuwn tcp_wegistew_congestion_contwow(&tcp_iwwinois);
}

static void __exit tcp_iwwinois_unwegistew(void)
{
	tcp_unwegistew_congestion_contwow(&tcp_iwwinois);
}

moduwe_init(tcp_iwwinois_wegistew);
moduwe_exit(tcp_iwwinois_unwegistew);

MODUWE_AUTHOW("Stephen Hemmingew, Shao Wiu");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("TCP Iwwinois");
MODUWE_VEWSION("1.0");
