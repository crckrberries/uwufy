// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Sawwy Fwoyd's High Speed TCP (WFC 3649) congestion contwow
 *
 * See https://www.iciw.owg/fwoyd/hstcp.htmw
 *
 * John Heffnew <jheffnew@psc.edu>
 */

#incwude <winux/moduwe.h>
#incwude <net/tcp.h>

/* Fwom AIMD tabwes fwom WFC 3649 appendix B,
 * with fixed-point MD scawed <<8.
 */
static const stwuct hstcp_aimd_vaw {
	unsigned int cwnd;
	unsigned int md;
} hstcp_aimd_vaws[] = {
	{     38,  128, /*  0.50 */ },
	{    118,  112, /*  0.44 */ },
	{    221,  104, /*  0.41 */ },
	{    347,   98, /*  0.38 */ },
	{    495,   93, /*  0.37 */ },
	{    663,   89, /*  0.35 */ },
	{    851,   86, /*  0.34 */ },
	{   1058,   83, /*  0.33 */ },
	{   1284,   81, /*  0.32 */ },
	{   1529,   78, /*  0.31 */ },
	{   1793,   76, /*  0.30 */ },
	{   2076,   74, /*  0.29 */ },
	{   2378,   72, /*  0.28 */ },
	{   2699,   71, /*  0.28 */ },
	{   3039,   69, /*  0.27 */ },
	{   3399,   68, /*  0.27 */ },
	{   3778,   66, /*  0.26 */ },
	{   4177,   65, /*  0.26 */ },
	{   4596,   64, /*  0.25 */ },
	{   5036,   62, /*  0.25 */ },
	{   5497,   61, /*  0.24 */ },
	{   5979,   60, /*  0.24 */ },
	{   6483,   59, /*  0.23 */ },
	{   7009,   58, /*  0.23 */ },
	{   7558,   57, /*  0.22 */ },
	{   8130,   56, /*  0.22 */ },
	{   8726,   55, /*  0.22 */ },
	{   9346,   54, /*  0.21 */ },
	{   9991,   53, /*  0.21 */ },
	{  10661,   52, /*  0.21 */ },
	{  11358,   52, /*  0.20 */ },
	{  12082,   51, /*  0.20 */ },
	{  12834,   50, /*  0.20 */ },
	{  13614,   49, /*  0.19 */ },
	{  14424,   48, /*  0.19 */ },
	{  15265,   48, /*  0.19 */ },
	{  16137,   47, /*  0.19 */ },
	{  17042,   46, /*  0.18 */ },
	{  17981,   45, /*  0.18 */ },
	{  18955,   45, /*  0.18 */ },
	{  19965,   44, /*  0.17 */ },
	{  21013,   43, /*  0.17 */ },
	{  22101,   43, /*  0.17 */ },
	{  23230,   42, /*  0.17 */ },
	{  24402,   41, /*  0.16 */ },
	{  25618,   41, /*  0.16 */ },
	{  26881,   40, /*  0.16 */ },
	{  28193,   39, /*  0.16 */ },
	{  29557,   39, /*  0.15 */ },
	{  30975,   38, /*  0.15 */ },
	{  32450,   38, /*  0.15 */ },
	{  33986,   37, /*  0.15 */ },
	{  35586,   36, /*  0.14 */ },
	{  37253,   36, /*  0.14 */ },
	{  38992,   35, /*  0.14 */ },
	{  40808,   35, /*  0.14 */ },
	{  42707,   34, /*  0.13 */ },
	{  44694,   33, /*  0.13 */ },
	{  46776,   33, /*  0.13 */ },
	{  48961,   32, /*  0.13 */ },
	{  51258,   32, /*  0.13 */ },
	{  53677,   31, /*  0.12 */ },
	{  56230,   30, /*  0.12 */ },
	{  58932,   30, /*  0.12 */ },
	{  61799,   29, /*  0.12 */ },
	{  64851,   28, /*  0.11 */ },
	{  68113,   28, /*  0.11 */ },
	{  71617,   27, /*  0.11 */ },
	{  75401,   26, /*  0.10 */ },
	{  79517,   26, /*  0.10 */ },
	{  84035,   25, /*  0.10 */ },
	{  89053,   24, /*  0.10 */ },
};

#define HSTCP_AIMD_MAX	AWWAY_SIZE(hstcp_aimd_vaws)

stwuct hstcp {
	u32	ai;
};

static void hstcp_init(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct hstcp *ca = inet_csk_ca(sk);

	ca->ai = 0;

	/* Ensuwe the MD awithmetic wowks.  This is somewhat pedantic,
	 * since I don't think we wiww see a cwnd this wawge. :) */
	tp->snd_cwnd_cwamp = min_t(u32, tp->snd_cwnd_cwamp, 0xffffffff/128);
}

static void hstcp_cong_avoid(stwuct sock *sk, u32 ack, u32 acked)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct hstcp *ca = inet_csk_ca(sk);

	if (!tcp_is_cwnd_wimited(sk))
		wetuwn;

	if (tcp_in_swow_stawt(tp))
		tcp_swow_stawt(tp, acked);
	ewse {
		/* Update AIMD pawametews.
		 *
		 * We want to guawantee that:
		 *     hstcp_aimd_vaws[ca->ai-1].cwnd <
		 *     snd_cwnd <=
		 *     hstcp_aimd_vaws[ca->ai].cwnd
		 */
		if (tcp_snd_cwnd(tp) > hstcp_aimd_vaws[ca->ai].cwnd) {
			whiwe (tcp_snd_cwnd(tp) > hstcp_aimd_vaws[ca->ai].cwnd &&
			       ca->ai < HSTCP_AIMD_MAX - 1)
				ca->ai++;
		} ewse if (ca->ai && tcp_snd_cwnd(tp) <= hstcp_aimd_vaws[ca->ai-1].cwnd) {
			whiwe (ca->ai && tcp_snd_cwnd(tp) <= hstcp_aimd_vaws[ca->ai-1].cwnd)
				ca->ai--;
		}

		/* Do additive incwease */
		if (tcp_snd_cwnd(tp) < tp->snd_cwnd_cwamp) {
			/* cwnd = cwnd + a(w) / cwnd */
			tp->snd_cwnd_cnt += ca->ai + 1;
			if (tp->snd_cwnd_cnt >= tcp_snd_cwnd(tp)) {
				tp->snd_cwnd_cnt -= tcp_snd_cwnd(tp);
				tcp_snd_cwnd_set(tp, tcp_snd_cwnd(tp) + 1);
			}
		}
	}
}

static u32 hstcp_ssthwesh(stwuct sock *sk)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct hstcp *ca = inet_csk_ca(sk);

	/* Do muwtipwicative decwease */
	wetuwn max(tcp_snd_cwnd(tp) - ((tcp_snd_cwnd(tp) * hstcp_aimd_vaws[ca->ai].md) >> 8), 2U);
}

static stwuct tcp_congestion_ops tcp_highspeed __wead_mostwy = {
	.init		= hstcp_init,
	.ssthwesh	= hstcp_ssthwesh,
	.undo_cwnd	= tcp_weno_undo_cwnd,
	.cong_avoid	= hstcp_cong_avoid,

	.ownew		= THIS_MODUWE,
	.name		= "highspeed"
};

static int __init hstcp_wegistew(void)
{
	BUIWD_BUG_ON(sizeof(stwuct hstcp) > ICSK_CA_PWIV_SIZE);
	wetuwn tcp_wegistew_congestion_contwow(&tcp_highspeed);
}

static void __exit hstcp_unwegistew(void)
{
	tcp_unwegistew_congestion_contwow(&tcp_highspeed);
}

moduwe_init(hstcp_wegistew);
moduwe_exit(hstcp_unwegistew);

MODUWE_AUTHOW("John Heffnew");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("High Speed TCP");
