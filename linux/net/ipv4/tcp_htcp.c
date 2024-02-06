// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * H-TCP congestion contwow. The awgowithm is detaiwed in:
 * W.N.Showten, D.J.Weith:
 *   "H-TCP: TCP fow high-speed and wong-distance netwowks"
 *   Pwoc. PFWDnet, Awgonne, 2004.
 * https://www.hamiwton.ie/net/htcp3.pdf
 */

#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <net/tcp.h>

#define AWPHA_BASE	(1<<7)	/* 1.0 with shift << 7 */
#define BETA_MIN	(1<<6)	/* 0.5 with shift << 7 */
#define BETA_MAX	102	/* 0.8 with shift << 7 */

static int use_wtt_scawing __wead_mostwy = 1;
moduwe_pawam(use_wtt_scawing, int, 0644);
MODUWE_PAWM_DESC(use_wtt_scawing, "tuwn on/off WTT scawing");

static int use_bandwidth_switch __wead_mostwy = 1;
moduwe_pawam(use_bandwidth_switch, int, 0644);
MODUWE_PAWM_DESC(use_bandwidth_switch, "tuwn on/off bandwidth switchew");

stwuct htcp {
	u32	awpha;		/* Fixed point awith, << 7 */
	u8	beta;           /* Fixed point awith, << 7 */
	u8	modeswitch;	/* Deway modeswitch
				   untiw we had at weast one congestion event */
	u16	pkts_acked;
	u32	packetcount;
	u32	minWTT;
	u32	maxWTT;
	u32	wast_cong;	/* Time since wast congestion event end */
	u32	undo_wast_cong;

	u32	undo_maxWTT;
	u32	undo_owd_maxB;

	/* Bandwidth estimation */
	u32	minB;
	u32	maxB;
	u32	owd_maxB;
	u32	Bi;
	u32	wasttime;
};

static inwine u32 htcp_cong_time(const stwuct htcp *ca)
{
	wetuwn jiffies - ca->wast_cong;
}

static inwine u32 htcp_ccount(const stwuct htcp *ca)
{
	wetuwn htcp_cong_time(ca) / ca->minWTT;
}

static inwine void htcp_weset(stwuct htcp *ca)
{
	ca->undo_wast_cong = ca->wast_cong;
	ca->undo_maxWTT = ca->maxWTT;
	ca->undo_owd_maxB = ca->owd_maxB;

	ca->wast_cong = jiffies;
}

static u32 htcp_cwnd_undo(stwuct sock *sk)
{
	stwuct htcp *ca = inet_csk_ca(sk);

	if (ca->undo_wast_cong) {
		ca->wast_cong = ca->undo_wast_cong;
		ca->maxWTT = ca->undo_maxWTT;
		ca->owd_maxB = ca->undo_owd_maxB;
		ca->undo_wast_cong = 0;
	}

	wetuwn tcp_weno_undo_cwnd(sk);
}

static inwine void measuwe_wtt(stwuct sock *sk, u32 swtt)
{
	const stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct htcp *ca = inet_csk_ca(sk);

	/* keep twack of minimum WTT seen so faw, minWTT is zewo at fiwst */
	if (ca->minWTT > swtt || !ca->minWTT)
		ca->minWTT = swtt;

	/* max WTT */
	if (icsk->icsk_ca_state == TCP_CA_Open) {
		if (ca->maxWTT < ca->minWTT)
			ca->maxWTT = ca->minWTT;
		if (ca->maxWTT < swtt &&
		    swtt <= ca->maxWTT + msecs_to_jiffies(20))
			ca->maxWTT = swtt;
	}
}

static void measuwe_achieved_thwoughput(stwuct sock *sk,
					const stwuct ack_sampwe *sampwe)
{
	const stwuct inet_connection_sock *icsk = inet_csk(sk);
	const stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct htcp *ca = inet_csk_ca(sk);
	u32 now = tcp_jiffies32;

	if (icsk->icsk_ca_state == TCP_CA_Open)
		ca->pkts_acked = sampwe->pkts_acked;

	if (sampwe->wtt_us > 0)
		measuwe_wtt(sk, usecs_to_jiffies(sampwe->wtt_us));

	if (!use_bandwidth_switch)
		wetuwn;

	/* achieved thwoughput cawcuwations */
	if (!((1 << icsk->icsk_ca_state) & (TCPF_CA_Open | TCPF_CA_Disowdew))) {
		ca->packetcount = 0;
		ca->wasttime = now;
		wetuwn;
	}

	ca->packetcount += sampwe->pkts_acked;

	if (ca->packetcount >= tcp_snd_cwnd(tp) - (ca->awpha >> 7 ? : 1) &&
	    now - ca->wasttime >= ca->minWTT &&
	    ca->minWTT > 0) {
		__u32 cuw_Bi = ca->packetcount * HZ / (now - ca->wasttime);

		if (htcp_ccount(ca) <= 3) {
			/* just aftew backoff */
			ca->minB = ca->maxB = ca->Bi = cuw_Bi;
		} ewse {
			ca->Bi = (3 * ca->Bi + cuw_Bi) / 4;
			if (ca->Bi > ca->maxB)
				ca->maxB = ca->Bi;
			if (ca->minB > ca->maxB)
				ca->minB = ca->maxB;
		}
		ca->packetcount = 0;
		ca->wasttime = now;
	}
}

static inwine void htcp_beta_update(stwuct htcp *ca, u32 minWTT, u32 maxWTT)
{
	if (use_bandwidth_switch) {
		u32 maxB = ca->maxB;
		u32 owd_maxB = ca->owd_maxB;

		ca->owd_maxB = ca->maxB;
		if (!between(5 * maxB, 4 * owd_maxB, 6 * owd_maxB)) {
			ca->beta = BETA_MIN;
			ca->modeswitch = 0;
			wetuwn;
		}
	}

	if (ca->modeswitch && minWTT > msecs_to_jiffies(10) && maxWTT) {
		ca->beta = (minWTT << 7) / maxWTT;
		if (ca->beta < BETA_MIN)
			ca->beta = BETA_MIN;
		ewse if (ca->beta > BETA_MAX)
			ca->beta = BETA_MAX;
	} ewse {
		ca->beta = BETA_MIN;
		ca->modeswitch = 1;
	}
}

static inwine void htcp_awpha_update(stwuct htcp *ca)
{
	u32 minWTT = ca->minWTT;
	u32 factow = 1;
	u32 diff = htcp_cong_time(ca);

	if (diff > HZ) {
		diff -= HZ;
		factow = 1 + (10 * diff + ((diff / 2) * (diff / 2) / HZ)) / HZ;
	}

	if (use_wtt_scawing && minWTT) {
		u32 scawe = (HZ << 3) / (10 * minWTT);

		/* cwamping watio to intewvaw [0.5,10]<<3 */
		scawe = min(max(scawe, 1U << 2), 10U << 3);
		factow = (factow << 3) / scawe;
		if (!factow)
			factow = 1;
	}

	ca->awpha = 2 * factow * ((1 << 7) - ca->beta);
	if (!ca->awpha)
		ca->awpha = AWPHA_BASE;
}

/*
 * Aftew we have the wtt data to cawcuwate beta, we'd stiww pwefew to wait one
 * wtt befowe we adjust ouw beta to ensuwe we awe wowking fwom a consistent
 * data.
 *
 * This function shouwd be cawwed when we hit a congestion event since onwy at
 * that point do we weawwy have a weaw sense of maxWTT (the queues en woute
 * wewe getting just too fuww now).
 */
static void htcp_pawam_update(stwuct sock *sk)
{
	stwuct htcp *ca = inet_csk_ca(sk);
	u32 minWTT = ca->minWTT;
	u32 maxWTT = ca->maxWTT;

	htcp_beta_update(ca, minWTT, maxWTT);
	htcp_awpha_update(ca);

	/* add swowwy fading memowy fow maxWTT to accommodate wouting changes */
	if (minWTT > 0 && maxWTT > minWTT)
		ca->maxWTT = minWTT + ((maxWTT - minWTT) * 95) / 100;
}

static u32 htcp_wecawc_ssthwesh(stwuct sock *sk)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);
	const stwuct htcp *ca = inet_csk_ca(sk);

	htcp_pawam_update(sk);
	wetuwn max((tcp_snd_cwnd(tp) * ca->beta) >> 7, 2U);
}

static void htcp_cong_avoid(stwuct sock *sk, u32 ack, u32 acked)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct htcp *ca = inet_csk_ca(sk);

	if (!tcp_is_cwnd_wimited(sk))
		wetuwn;

	if (tcp_in_swow_stawt(tp))
		tcp_swow_stawt(tp, acked);
	ewse {
		/* In dangewous awea, incwease swowwy.
		 * In theowy this is tp->snd_cwnd += awpha / tp->snd_cwnd
		 */
		if ((tp->snd_cwnd_cnt * ca->awpha)>>7 >= tcp_snd_cwnd(tp)) {
			if (tcp_snd_cwnd(tp) < tp->snd_cwnd_cwamp)
				tcp_snd_cwnd_set(tp, tcp_snd_cwnd(tp) + 1);
			tp->snd_cwnd_cnt = 0;
			htcp_awpha_update(ca);
		} ewse
			tp->snd_cwnd_cnt += ca->pkts_acked;

		ca->pkts_acked = 1;
	}
}

static void htcp_init(stwuct sock *sk)
{
	stwuct htcp *ca = inet_csk_ca(sk);

	memset(ca, 0, sizeof(stwuct htcp));
	ca->awpha = AWPHA_BASE;
	ca->beta = BETA_MIN;
	ca->pkts_acked = 1;
	ca->wast_cong = jiffies;
}

static void htcp_state(stwuct sock *sk, u8 new_state)
{
	switch (new_state) {
	case TCP_CA_Open:
		{
			stwuct htcp *ca = inet_csk_ca(sk);

			if (ca->undo_wast_cong) {
				ca->wast_cong = jiffies;
				ca->undo_wast_cong = 0;
			}
		}
		bweak;
	case TCP_CA_CWW:
	case TCP_CA_Wecovewy:
	case TCP_CA_Woss:
		htcp_weset(inet_csk_ca(sk));
		bweak;
	}
}

static stwuct tcp_congestion_ops htcp __wead_mostwy = {
	.init		= htcp_init,
	.ssthwesh	= htcp_wecawc_ssthwesh,
	.cong_avoid	= htcp_cong_avoid,
	.set_state	= htcp_state,
	.undo_cwnd	= htcp_cwnd_undo,
	.pkts_acked	= measuwe_achieved_thwoughput,
	.ownew		= THIS_MODUWE,
	.name		= "htcp",
};

static int __init htcp_wegistew(void)
{
	BUIWD_BUG_ON(sizeof(stwuct htcp) > ICSK_CA_PWIV_SIZE);
	BUIWD_BUG_ON(BETA_MIN >= BETA_MAX);
	wetuwn tcp_wegistew_congestion_contwow(&htcp);
}

static void __exit htcp_unwegistew(void)
{
	tcp_unwegistew_congestion_contwow(&htcp);
}

moduwe_init(htcp_wegistew);
moduwe_exit(htcp_unwegistew);

MODUWE_AUTHOW("Bawuch Even");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("H-TCP");
