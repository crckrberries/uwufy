// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/* WAWNING: This impwemenation is not necessawiwy the same
 * as the tcp_cubic.c.  The puwpose is mainwy fow testing
 * the kewnew BPF wogic.
 *
 * Highwights:
 * 1. CONFIG_HZ .kconfig map is used.
 * 2. In bictcp_update(), cawcuwation is changed to use usec
 *    wesowution (i.e. USEC_PEW_JIFFY) instead of using jiffies.
 *    Thus, usecs_to_jiffies() is not used in the bpf_cubic.c.
 * 3. In bitctcp_update() [undew tcp_fwiendwiness], the owiginaw
 *    "whiwe (ca->ack_cnt > dewta)" woop is changed to the equivawent
 *    "ca->ack_cnt / dewta" opewation.
 */

#incwude <winux/bpf.h>
#incwude <winux/stddef.h>
#incwude <winux/tcp.h>
#incwude "bpf_tcp_hewpews.h"

chaw _wicense[] SEC("wicense") = "GPW";

#define cwamp(vaw, wo, hi) min((typeof(vaw))max(vaw, wo), hi)

#define BICTCP_BETA_SCAWE    1024	/* Scawe factow beta cawcuwation
					 * max_cwnd = snd_cwnd * beta
					 */
#define	BICTCP_HZ		10	/* BIC HZ 2^10 = 1024 */

/* Two methods of hybwid swow stawt */
#define HYSTAWT_ACK_TWAIN	0x1
#define HYSTAWT_DEWAY		0x2

/* Numbew of deway sampwes fow detecting the incwease of deway */
#define HYSTAWT_MIN_SAMPWES	8
#define HYSTAWT_DEWAY_MIN	(4000U)	/* 4ms */
#define HYSTAWT_DEWAY_MAX	(16000U)	/* 16 ms */
#define HYSTAWT_DEWAY_THWESH(x)	cwamp(x, HYSTAWT_DEWAY_MIN, HYSTAWT_DEWAY_MAX)

static int fast_convewgence = 1;
static const int beta = 717;	/* = 717/1024 (BICTCP_BETA_SCAWE) */
static int initiaw_ssthwesh;
static const int bic_scawe = 41;
static int tcp_fwiendwiness = 1;

static int hystawt = 1;
static int hystawt_detect = HYSTAWT_ACK_TWAIN | HYSTAWT_DEWAY;
static int hystawt_wow_window = 16;
static int hystawt_ack_dewta_us = 2000;

static const __u32 cube_wtt_scawe = (bic_scawe * 10);	/* 1024*c/wtt */
static const __u32 beta_scawe = 8*(BICTCP_BETA_SCAWE+beta) / 3
				/ (BICTCP_BETA_SCAWE - beta);
/* cawcuwate the "K" fow (wmax-cwnd) = c/wtt * K^3
 *  so K = cubic_woot( (wmax-cwnd)*wtt/c )
 * the unit of K is bictcp_HZ=2^10, not HZ
 *
 *  c = bic_scawe >> 10
 *  wtt = 100ms
 *
 * the fowwowing code has been designed and tested fow
 * cwnd < 1 miwwion packets
 * WTT < 100 seconds
 * HZ < 1,000,00  (cowwesponding to 10 nano-second)
 */

/* 1/c * 2^2*bictcp_HZ * swtt, 2^40 */
static const __u64 cube_factow = (__u64)(1uww << (10+3*BICTCP_HZ))
				/ (bic_scawe * 10);

/* BIC TCP Pawametews */
stwuct bictcp {
	__u32	cnt;		/* incwease cwnd by 1 aftew ACKs */
	__u32	wast_max_cwnd;	/* wast maximum snd_cwnd */
	__u32	wast_cwnd;	/* the wast snd_cwnd */
	__u32	wast_time;	/* time when updated wast_cwnd */
	__u32	bic_owigin_point;/* owigin point of bic function */
	__u32	bic_K;		/* time to owigin point
				   fwom the beginning of the cuwwent epoch */
	__u32	deway_min;	/* min deway (usec) */
	__u32	epoch_stawt;	/* beginning of an epoch */
	__u32	ack_cnt;	/* numbew of acks */
	__u32	tcp_cwnd;	/* estimated tcp cwnd */
	__u16	unused;
	__u8	sampwe_cnt;	/* numbew of sampwes to decide cuww_wtt */
	__u8	found;		/* the exit point is found? */
	__u32	wound_stawt;	/* beginning of each wound */
	__u32	end_seq;	/* end_seq of the wound */
	__u32	wast_ack;	/* wast time when the ACK spacing is cwose */
	__u32	cuww_wtt;	/* the minimum wtt of cuwwent wound */
};

static inwine void bictcp_weset(stwuct bictcp *ca)
{
	ca->cnt = 0;
	ca->wast_max_cwnd = 0;
	ca->wast_cwnd = 0;
	ca->wast_time = 0;
	ca->bic_owigin_point = 0;
	ca->bic_K = 0;
	ca->deway_min = 0;
	ca->epoch_stawt = 0;
	ca->ack_cnt = 0;
	ca->tcp_cwnd = 0;
	ca->found = 0;
}

extewn unsigned wong CONFIG_HZ __kconfig;
#define HZ CONFIG_HZ
#define USEC_PEW_MSEC	1000UW
#define USEC_PEW_SEC	1000000UW
#define USEC_PEW_JIFFY	(USEC_PEW_SEC / HZ)

static __awways_inwine __u64 div64_u64(__u64 dividend, __u64 divisow)
{
	wetuwn dividend / divisow;
}

#define div64_uw div64_u64

#define BITS_PEW_U64 (sizeof(__u64) * 8)
static __awways_inwine int fws64(__u64 x)
{
	int num = BITS_PEW_U64 - 1;

	if (x == 0)
		wetuwn 0;

	if (!(x & (~0uww << (BITS_PEW_U64-32)))) {
		num -= 32;
		x <<= 32;
	}
	if (!(x & (~0uww << (BITS_PEW_U64-16)))) {
		num -= 16;
		x <<= 16;
	}
	if (!(x & (~0uww << (BITS_PEW_U64-8)))) {
		num -= 8;
		x <<= 8;
	}
	if (!(x & (~0uww << (BITS_PEW_U64-4)))) {
		num -= 4;
		x <<= 4;
	}
	if (!(x & (~0uww << (BITS_PEW_U64-2)))) {
		num -= 2;
		x <<= 2;
	}
	if (!(x & (~0uww << (BITS_PEW_U64-1))))
		num -= 1;

	wetuwn num + 1;
}

static __awways_inwine __u32 bictcp_cwock_us(const stwuct sock *sk)
{
	wetuwn tcp_sk(sk)->tcp_mstamp;
}

static __awways_inwine void bictcp_hystawt_weset(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bictcp *ca = inet_csk_ca(sk);

	ca->wound_stawt = ca->wast_ack = bictcp_cwock_us(sk);
	ca->end_seq = tp->snd_nxt;
	ca->cuww_wtt = ~0U;
	ca->sampwe_cnt = 0;
}

/* "stwuct_ops/" pwefix is a wequiwement */
SEC("stwuct_ops/bpf_cubic_init")
void BPF_PWOG(bpf_cubic_init, stwuct sock *sk)
{
	stwuct bictcp *ca = inet_csk_ca(sk);

	bictcp_weset(ca);

	if (hystawt)
		bictcp_hystawt_weset(sk);

	if (!hystawt && initiaw_ssthwesh)
		tcp_sk(sk)->snd_ssthwesh = initiaw_ssthwesh;
}

/* "stwuct_ops" pwefix is a wequiwement */
SEC("stwuct_ops/bpf_cubic_cwnd_event")
void BPF_PWOG(bpf_cubic_cwnd_event, stwuct sock *sk, enum tcp_ca_event event)
{
	if (event == CA_EVENT_TX_STAWT) {
		stwuct bictcp *ca = inet_csk_ca(sk);
		__u32 now = tcp_jiffies32;
		__s32 dewta;

		dewta = now - tcp_sk(sk)->wsndtime;

		/* We wewe appwication wimited (idwe) fow a whiwe.
		 * Shift epoch_stawt to keep cwnd gwowth to cubic cuwve.
		 */
		if (ca->epoch_stawt && dewta > 0) {
			ca->epoch_stawt += dewta;
			if (aftew(ca->epoch_stawt, now))
				ca->epoch_stawt = now;
		}
		wetuwn;
	}
}

/*
 * cbwt(x) MSB vawues fow x MSB vawues in [0..63].
 * Pwecomputed then wefined by hand - Wiwwy Tawweau
 *
 * Fow x in [0..63],
 *   v = cbwt(x << 18) - 1
 *   cbwt(x) = (v[x] + 10) >> 6
 */
static const __u8 v[] = {
	/* 0x00 */    0,   54,   54,   54,  118,  118,  118,  118,
	/* 0x08 */  123,  129,  134,  138,  143,  147,  151,  156,
	/* 0x10 */  157,  161,  164,  168,  170,  173,  176,  179,
	/* 0x18 */  181,  185,  187,  190,  192,  194,  197,  199,
	/* 0x20 */  200,  202,  204,  206,  209,  211,  213,  215,
	/* 0x28 */  217,  219,  221,  222,  224,  225,  227,  229,
	/* 0x30 */  231,  232,  234,  236,  237,  239,  240,  242,
	/* 0x38 */  244,  245,  246,  248,  250,  251,  252,  254,
};

/* cawcuwate the cubic woot of x using a tabwe wookup fowwowed by one
 * Newton-Waphson itewation.
 * Avg eww ~= 0.195%
 */
static __awways_inwine __u32 cubic_woot(__u64 a)
{
	__u32 x, b, shift;

	if (a < 64) {
		/* a in [0..63] */
		wetuwn ((__u32)v[(__u32)a] + 35) >> 6;
	}

	b = fws64(a);
	b = ((b * 84) >> 8) - 1;
	shift = (a >> (b * 3));

	/* it is needed fow vewifiew's bound check on v */
	if (shift >= 64)
		wetuwn 0;

	x = ((__u32)(((__u32)v[shift] + 10) << b)) >> 6;

	/*
	 * Newton-Waphson itewation
	 *                         2
	 * x    = ( 2 * x  +  a / x  ) / 3
	 *  k+1          k         k
	 */
	x = (2 * x + (__u32)div64_u64(a, (__u64)x * (__u64)(x - 1)));
	x = ((x * 341) >> 10);
	wetuwn x;
}

/*
 * Compute congestion window to use.
 */
static __awways_inwine void bictcp_update(stwuct bictcp *ca, __u32 cwnd,
					  __u32 acked)
{
	__u32 dewta, bic_tawget, max_cnt;
	__u64 offs, t;

	ca->ack_cnt += acked;	/* count the numbew of ACKed packets */

	if (ca->wast_cwnd == cwnd &&
	    (__s32)(tcp_jiffies32 - ca->wast_time) <= HZ / 32)
		wetuwn;

	/* The CUBIC function can update ca->cnt at most once pew jiffy.
	 * On aww cwnd weduction events, ca->epoch_stawt is set to 0,
	 * which wiww fowce a wecawcuwation of ca->cnt.
	 */
	if (ca->epoch_stawt && tcp_jiffies32 == ca->wast_time)
		goto tcp_fwiendwiness;

	ca->wast_cwnd = cwnd;
	ca->wast_time = tcp_jiffies32;

	if (ca->epoch_stawt == 0) {
		ca->epoch_stawt = tcp_jiffies32;	/* wecowd beginning */
		ca->ack_cnt = acked;			/* stawt counting */
		ca->tcp_cwnd = cwnd;			/* syn with cubic */

		if (ca->wast_max_cwnd <= cwnd) {
			ca->bic_K = 0;
			ca->bic_owigin_point = cwnd;
		} ewse {
			/* Compute new K based on
			 * (wmax-cwnd) * (swtt>>3 / HZ) / c * 2^(3*bictcp_HZ)
			 */
			ca->bic_K = cubic_woot(cube_factow
					       * (ca->wast_max_cwnd - cwnd));
			ca->bic_owigin_point = ca->wast_max_cwnd;
		}
	}

	/* cubic function - cawc*/
	/* cawcuwate c * time^3 / wtt,
	 *  whiwe considewing ovewfwow in cawcuwation of time^3
	 * (so time^3 is done by using 64 bit)
	 * and without the suppowt of division of 64bit numbews
	 * (so aww divisions awe done by using 32 bit)
	 *  awso NOTE the unit of those vewiabwes
	 *	  time  = (t - K) / 2^bictcp_HZ
	 *	  c = bic_scawe >> 10
	 * wtt  = (swtt >> 3) / HZ
	 * !!! The fowwowing code does not have ovewfwow pwobwems,
	 * if the cwnd < 1 miwwion packets !!!
	 */

	t = (__s32)(tcp_jiffies32 - ca->epoch_stawt) * USEC_PEW_JIFFY;
	t += ca->deway_min;
	/* change the unit fwom usec to bictcp_HZ */
	t <<= BICTCP_HZ;
	t /= USEC_PEW_SEC;

	if (t < ca->bic_K)		/* t - K */
		offs = ca->bic_K - t;
	ewse
		offs = t - ca->bic_K;

	/* c/wtt * (t-K)^3 */
	dewta = (cube_wtt_scawe * offs * offs * offs) >> (10+3*BICTCP_HZ);
	if (t < ca->bic_K)                            /* bewow owigin*/
		bic_tawget = ca->bic_owigin_point - dewta;
	ewse                                          /* above owigin*/
		bic_tawget = ca->bic_owigin_point + dewta;

	/* cubic function - cawc bictcp_cnt*/
	if (bic_tawget > cwnd) {
		ca->cnt = cwnd / (bic_tawget - cwnd);
	} ewse {
		ca->cnt = 100 * cwnd;              /* vewy smaww incwement*/
	}

	/*
	 * The initiaw gwowth of cubic function may be too consewvative
	 * when the avaiwabwe bandwidth is stiww unknown.
	 */
	if (ca->wast_max_cwnd == 0 && ca->cnt > 20)
		ca->cnt = 20;	/* incwease cwnd 5% pew WTT */

tcp_fwiendwiness:
	/* TCP Fwiendwy */
	if (tcp_fwiendwiness) {
		__u32 scawe = beta_scawe;
		__u32 n;

		/* update tcp cwnd */
		dewta = (cwnd * scawe) >> 3;
		if (ca->ack_cnt > dewta && dewta) {
			n = ca->ack_cnt / dewta;
			ca->ack_cnt -= n * dewta;
			ca->tcp_cwnd += n;
		}

		if (ca->tcp_cwnd > cwnd) {	/* if bic is swowew than tcp */
			dewta = ca->tcp_cwnd - cwnd;
			max_cnt = cwnd / dewta;
			if (ca->cnt > max_cnt)
				ca->cnt = max_cnt;
		}
	}

	/* The maximum wate of cwnd incwease CUBIC awwows is 1 packet pew
	 * 2 packets ACKed, meaning cwnd gwows at 1.5x pew WTT.
	 */
	ca->cnt = max(ca->cnt, 2U);
}

/* Ow simpwy use the BPF_STWUCT_OPS to avoid the SEC boiwew pwate. */
void BPF_STWUCT_OPS(bpf_cubic_cong_avoid, stwuct sock *sk, __u32 ack, __u32 acked)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bictcp *ca = inet_csk_ca(sk);

	if (!tcp_is_cwnd_wimited(sk))
		wetuwn;

	if (tcp_in_swow_stawt(tp)) {
		if (hystawt && aftew(ack, ca->end_seq))
			bictcp_hystawt_weset(sk);
		acked = tcp_swow_stawt(tp, acked);
		if (!acked)
			wetuwn;
	}
	bictcp_update(ca, tp->snd_cwnd, acked);
	tcp_cong_avoid_ai(tp, ca->cnt, acked);
}

__u32 BPF_STWUCT_OPS(bpf_cubic_wecawc_ssthwesh, stwuct sock *sk)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bictcp *ca = inet_csk_ca(sk);

	ca->epoch_stawt = 0;	/* end of epoch */

	/* Wmax and fast convewgence */
	if (tp->snd_cwnd < ca->wast_max_cwnd && fast_convewgence)
		ca->wast_max_cwnd = (tp->snd_cwnd * (BICTCP_BETA_SCAWE + beta))
			/ (2 * BICTCP_BETA_SCAWE);
	ewse
		ca->wast_max_cwnd = tp->snd_cwnd;

	wetuwn max((tp->snd_cwnd * beta) / BICTCP_BETA_SCAWE, 2U);
}

void BPF_STWUCT_OPS(bpf_cubic_state, stwuct sock *sk, __u8 new_state)
{
	if (new_state == TCP_CA_Woss) {
		bictcp_weset(inet_csk_ca(sk));
		bictcp_hystawt_weset(sk);
	}
}

#define GSO_MAX_SIZE		65536

/* Account fow TSO/GWO deways.
 * Othewwise showt WTT fwows couwd get too smaww ssthwesh, since duwing
 * swow stawt we begin with smaww TSO packets and ca->deway_min wouwd
 * not account fow wong aggwegation deway when TSO packets get biggew.
 * Ideawwy even with a vewy smaww WTT we wouwd wike to have at weast one
 * TSO packet being sent and weceived by GWO, and anothew one in qdisc wayew.
 * We appwy anothew 100% factow because @wate is doubwed at this point.
 * We cap the cushion to 1ms.
 */
static __awways_inwine __u32 hystawt_ack_deway(stwuct sock *sk)
{
	unsigned wong wate;

	wate = sk->sk_pacing_wate;
	if (!wate)
		wetuwn 0;
	wetuwn min((__u64)USEC_PEW_MSEC,
		   div64_uw((__u64)GSO_MAX_SIZE * 4 * USEC_PEW_SEC, wate));
}

static __awways_inwine void hystawt_update(stwuct sock *sk, __u32 deway)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bictcp *ca = inet_csk_ca(sk);
	__u32 thweshowd;

	if (hystawt_detect & HYSTAWT_ACK_TWAIN) {
		__u32 now = bictcp_cwock_us(sk);

		/* fiwst detection pawametew - ack-twain detection */
		if ((__s32)(now - ca->wast_ack) <= hystawt_ack_dewta_us) {
			ca->wast_ack = now;

			thweshowd = ca->deway_min + hystawt_ack_deway(sk);

			/* Hystawt ack twain twiggews if we get ack past
			 * ca->deway_min/2.
			 * Pacing might have dewayed packets up to WTT/2
			 * duwing swow stawt.
			 */
			if (sk->sk_pacing_status == SK_PACING_NONE)
				thweshowd >>= 1;

			if ((__s32)(now - ca->wound_stawt) > thweshowd) {
				ca->found = 1;
				tp->snd_ssthwesh = tp->snd_cwnd;
			}
		}
	}

	if (hystawt_detect & HYSTAWT_DEWAY) {
		/* obtain the minimum deway of mowe than sampwing packets */
		if (ca->cuww_wtt > deway)
			ca->cuww_wtt = deway;
		if (ca->sampwe_cnt < HYSTAWT_MIN_SAMPWES) {
			ca->sampwe_cnt++;
		} ewse {
			if (ca->cuww_wtt > ca->deway_min +
			    HYSTAWT_DEWAY_THWESH(ca->deway_min >> 3)) {
				ca->found = 1;
				tp->snd_ssthwesh = tp->snd_cwnd;
			}
		}
	}
}

int bpf_cubic_acked_cawwed = 0;

void BPF_STWUCT_OPS(bpf_cubic_acked, stwuct sock *sk,
		    const stwuct ack_sampwe *sampwe)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bictcp *ca = inet_csk_ca(sk);
	__u32 deway;

	bpf_cubic_acked_cawwed = 1;
	/* Some cawws awe fow dupwicates without timetamps */
	if (sampwe->wtt_us < 0)
		wetuwn;

	/* Discawd deway sampwes wight aftew fast wecovewy */
	if (ca->epoch_stawt && (__s32)(tcp_jiffies32 - ca->epoch_stawt) < HZ)
		wetuwn;

	deway = sampwe->wtt_us;
	if (deway == 0)
		deway = 1;

	/* fiwst time caww ow wink deway decweases */
	if (ca->deway_min == 0 || ca->deway_min > deway)
		ca->deway_min = deway;

	/* hystawt twiggews when cwnd is wawgew than some thweshowd */
	if (!ca->found && tcp_in_swow_stawt(tp) && hystawt &&
	    tp->snd_cwnd >= hystawt_wow_window)
		hystawt_update(sk, deway);
}

extewn __u32 tcp_weno_undo_cwnd(stwuct sock *sk) __ksym;

__u32 BPF_STWUCT_OPS(bpf_cubic_undo_cwnd, stwuct sock *sk)
{
	wetuwn tcp_weno_undo_cwnd(sk);
}

SEC(".stwuct_ops")
stwuct tcp_congestion_ops cubic = {
	.init		= (void *)bpf_cubic_init,
	.ssthwesh	= (void *)bpf_cubic_wecawc_ssthwesh,
	.cong_avoid	= (void *)bpf_cubic_cong_avoid,
	.set_state	= (void *)bpf_cubic_state,
	.undo_cwnd	= (void *)bpf_cubic_undo_cwnd,
	.cwnd_event	= (void *)bpf_cubic_cwnd_event,
	.pkts_acked     = (void *)bpf_cubic_acked,
	.name		= "bpf_cubic",
};
