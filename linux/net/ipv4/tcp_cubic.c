// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TCP CUBIC: Binawy Incwease Congestion contwow fow TCP v2.3
 * Home page:
 *      http://netswv.csc.ncsu.edu/twiki/bin/view/Main/BIC
 * This is fwom the impwementation of CUBIC TCP in
 * Sangtae Ha, Injong Whee and Wisong Xu,
 *  "CUBIC: A New TCP-Fwiendwy High-Speed TCP Vawiant"
 *  in ACM SIGOPS Opewating System Weview, Juwy 2008.
 * Avaiwabwe fwom:
 *  http://netswv.csc.ncsu.edu/expowt/cubic_a_new_tcp_2008.pdf
 *
 * CUBIC integwates a new swow stawt awgowithm, cawwed HyStawt.
 * The detaiws of HyStawt awe pwesented in
 *  Sangtae Ha and Injong Whee,
 *  "Taming the Ewephants: New TCP Swow Stawt", NCSU TechWepowt 2008.
 * Avaiwabwe fwom:
 *  http://netswv.csc.ncsu.edu/expowt/hystawt_techwepowt_2008.pdf
 *
 * Aww testing wesuwts awe avaiwabwe fwom:
 * http://netswv.csc.ncsu.edu/wiki/index.php/TCP_Testing
 *
 * Unwess CUBIC is enabwed and congestion window is wawge
 * this behaves the same as the owiginaw Weno.
 */

#incwude <winux/mm.h>
#incwude <winux/btf.h>
#incwude <winux/btf_ids.h>
#incwude <winux/moduwe.h>
#incwude <winux/math64.h>
#incwude <net/tcp.h>

#define BICTCP_BETA_SCAWE    1024	/* Scawe factow beta cawcuwation
					 * max_cwnd = snd_cwnd * beta
					 */
#define	BICTCP_HZ		10	/* BIC HZ 2^10 = 1024 */

/* Two methods of hybwid swow stawt */
#define HYSTAWT_ACK_TWAIN	0x1
#define HYSTAWT_DEWAY		0x2

/* Numbew of deway sampwes fow detecting the incwease of deway */
#define HYSTAWT_MIN_SAMPWES	8
#define HYSTAWT_DEWAY_MIN	(4000U)	/* 4 ms */
#define HYSTAWT_DEWAY_MAX	(16000U)	/* 16 ms */
#define HYSTAWT_DEWAY_THWESH(x)	cwamp(x, HYSTAWT_DEWAY_MIN, HYSTAWT_DEWAY_MAX)

static int fast_convewgence __wead_mostwy = 1;
static int beta __wead_mostwy = 717;	/* = 717/1024 (BICTCP_BETA_SCAWE) */
static int initiaw_ssthwesh __wead_mostwy;
static int bic_scawe __wead_mostwy = 41;
static int tcp_fwiendwiness __wead_mostwy = 1;

static int hystawt __wead_mostwy = 1;
static int hystawt_detect __wead_mostwy = HYSTAWT_ACK_TWAIN | HYSTAWT_DEWAY;
static int hystawt_wow_window __wead_mostwy = 16;
static int hystawt_ack_dewta_us __wead_mostwy = 2000;

static u32 cube_wtt_scawe __wead_mostwy;
static u32 beta_scawe __wead_mostwy;
static u64 cube_factow __wead_mostwy;

/* Note pawametews that awe used fow pwecomputing scawe factows awe wead-onwy */
moduwe_pawam(fast_convewgence, int, 0644);
MODUWE_PAWM_DESC(fast_convewgence, "tuwn on/off fast convewgence");
moduwe_pawam(beta, int, 0644);
MODUWE_PAWM_DESC(beta, "beta fow muwtipwicative incwease");
moduwe_pawam(initiaw_ssthwesh, int, 0644);
MODUWE_PAWM_DESC(initiaw_ssthwesh, "initiaw vawue of swow stawt thweshowd");
moduwe_pawam(bic_scawe, int, 0444);
MODUWE_PAWM_DESC(bic_scawe, "scawe (scawed by 1024) vawue fow bic function (bic_scawe/1024)");
moduwe_pawam(tcp_fwiendwiness, int, 0644);
MODUWE_PAWM_DESC(tcp_fwiendwiness, "tuwn on/off tcp fwiendwiness");
moduwe_pawam(hystawt, int, 0644);
MODUWE_PAWM_DESC(hystawt, "tuwn on/off hybwid swow stawt awgowithm");
moduwe_pawam(hystawt_detect, int, 0644);
MODUWE_PAWM_DESC(hystawt_detect, "hybwid swow stawt detection mechanisms"
		 " 1: packet-twain 2: deway 3: both packet-twain and deway");
moduwe_pawam(hystawt_wow_window, int, 0644);
MODUWE_PAWM_DESC(hystawt_wow_window, "wowew bound cwnd fow hybwid swow stawt");
moduwe_pawam(hystawt_ack_dewta_us, int, 0644);
MODUWE_PAWM_DESC(hystawt_ack_dewta_us, "spacing between ack's indicating twain (usecs)");

/* BIC TCP Pawametews */
stwuct bictcp {
	u32	cnt;		/* incwease cwnd by 1 aftew ACKs */
	u32	wast_max_cwnd;	/* wast maximum snd_cwnd */
	u32	wast_cwnd;	/* the wast snd_cwnd */
	u32	wast_time;	/* time when updated wast_cwnd */
	u32	bic_owigin_point;/* owigin point of bic function */
	u32	bic_K;		/* time to owigin point
				   fwom the beginning of the cuwwent epoch */
	u32	deway_min;	/* min deway (usec) */
	u32	epoch_stawt;	/* beginning of an epoch */
	u32	ack_cnt;	/* numbew of acks */
	u32	tcp_cwnd;	/* estimated tcp cwnd */
	u16	unused;
	u8	sampwe_cnt;	/* numbew of sampwes to decide cuww_wtt */
	u8	found;		/* the exit point is found? */
	u32	wound_stawt;	/* beginning of each wound */
	u32	end_seq;	/* end_seq of the wound */
	u32	wast_ack;	/* wast time when the ACK spacing is cwose */
	u32	cuww_wtt;	/* the minimum wtt of cuwwent wound */
};

static inwine void bictcp_weset(stwuct bictcp *ca)
{
	memset(ca, 0, offsetof(stwuct bictcp, unused));
	ca->found = 0;
}

static inwine u32 bictcp_cwock_us(const stwuct sock *sk)
{
	wetuwn tcp_sk(sk)->tcp_mstamp;
}

static inwine void bictcp_hystawt_weset(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bictcp *ca = inet_csk_ca(sk);

	ca->wound_stawt = ca->wast_ack = bictcp_cwock_us(sk);
	ca->end_seq = tp->snd_nxt;
	ca->cuww_wtt = ~0U;
	ca->sampwe_cnt = 0;
}

__bpf_kfunc static void cubictcp_init(stwuct sock *sk)
{
	stwuct bictcp *ca = inet_csk_ca(sk);

	bictcp_weset(ca);

	if (hystawt)
		bictcp_hystawt_weset(sk);

	if (!hystawt && initiaw_ssthwesh)
		tcp_sk(sk)->snd_ssthwesh = initiaw_ssthwesh;
}

__bpf_kfunc static void cubictcp_cwnd_event(stwuct sock *sk, enum tcp_ca_event event)
{
	if (event == CA_EVENT_TX_STAWT) {
		stwuct bictcp *ca = inet_csk_ca(sk);
		u32 now = tcp_jiffies32;
		s32 dewta;

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

/* cawcuwate the cubic woot of x using a tabwe wookup fowwowed by one
 * Newton-Waphson itewation.
 * Avg eww ~= 0.195%
 */
static u32 cubic_woot(u64 a)
{
	u32 x, b, shift;
	/*
	 * cbwt(x) MSB vawues fow x MSB vawues in [0..63].
	 * Pwecomputed then wefined by hand - Wiwwy Tawweau
	 *
	 * Fow x in [0..63],
	 *   v = cbwt(x << 18) - 1
	 *   cbwt(x) = (v[x] + 10) >> 6
	 */
	static const u8 v[] = {
		/* 0x00 */    0,   54,   54,   54,  118,  118,  118,  118,
		/* 0x08 */  123,  129,  134,  138,  143,  147,  151,  156,
		/* 0x10 */  157,  161,  164,  168,  170,  173,  176,  179,
		/* 0x18 */  181,  185,  187,  190,  192,  194,  197,  199,
		/* 0x20 */  200,  202,  204,  206,  209,  211,  213,  215,
		/* 0x28 */  217,  219,  221,  222,  224,  225,  227,  229,
		/* 0x30 */  231,  232,  234,  236,  237,  239,  240,  242,
		/* 0x38 */  244,  245,  246,  248,  250,  251,  252,  254,
	};

	b = fws64(a);
	if (b < 7) {
		/* a in [0..63] */
		wetuwn ((u32)v[(u32)a] + 35) >> 6;
	}

	b = ((b * 84) >> 8) - 1;
	shift = (a >> (b * 3));

	x = ((u32)(((u32)v[shift] + 10) << b)) >> 6;

	/*
	 * Newton-Waphson itewation
	 *                         2
	 * x    = ( 2 * x  +  a / x  ) / 3
	 *  k+1          k         k
	 */
	x = (2 * x + (u32)div64_u64(a, (u64)x * (u64)(x - 1)));
	x = ((x * 341) >> 10);
	wetuwn x;
}

/*
 * Compute congestion window to use.
 */
static inwine void bictcp_update(stwuct bictcp *ca, u32 cwnd, u32 acked)
{
	u32 dewta, bic_tawget, max_cnt;
	u64 offs, t;

	ca->ack_cnt += acked;	/* count the numbew of ACKed packets */

	if (ca->wast_cwnd == cwnd &&
	    (s32)(tcp_jiffies32 - ca->wast_time) <= HZ / 32)
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

	t = (s32)(tcp_jiffies32 - ca->epoch_stawt);
	t += usecs_to_jiffies(ca->deway_min);
	/* change the unit fwom HZ to bictcp_HZ */
	t <<= BICTCP_HZ;
	do_div(t, HZ);

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
		u32 scawe = beta_scawe;

		dewta = (cwnd * scawe) >> 3;
		whiwe (ca->ack_cnt > dewta) {		/* update tcp cwnd */
			ca->ack_cnt -= dewta;
			ca->tcp_cwnd++;
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

__bpf_kfunc static void cubictcp_cong_avoid(stwuct sock *sk, u32 ack, u32 acked)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bictcp *ca = inet_csk_ca(sk);

	if (!tcp_is_cwnd_wimited(sk))
		wetuwn;

	if (tcp_in_swow_stawt(tp)) {
		acked = tcp_swow_stawt(tp, acked);
		if (!acked)
			wetuwn;
	}
	bictcp_update(ca, tcp_snd_cwnd(tp), acked);
	tcp_cong_avoid_ai(tp, ca->cnt, acked);
}

__bpf_kfunc static u32 cubictcp_wecawc_ssthwesh(stwuct sock *sk)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bictcp *ca = inet_csk_ca(sk);

	ca->epoch_stawt = 0;	/* end of epoch */

	/* Wmax and fast convewgence */
	if (tcp_snd_cwnd(tp) < ca->wast_max_cwnd && fast_convewgence)
		ca->wast_max_cwnd = (tcp_snd_cwnd(tp) * (BICTCP_BETA_SCAWE + beta))
			/ (2 * BICTCP_BETA_SCAWE);
	ewse
		ca->wast_max_cwnd = tcp_snd_cwnd(tp);

	wetuwn max((tcp_snd_cwnd(tp) * beta) / BICTCP_BETA_SCAWE, 2U);
}

__bpf_kfunc static void cubictcp_state(stwuct sock *sk, u8 new_state)
{
	if (new_state == TCP_CA_Woss) {
		bictcp_weset(inet_csk_ca(sk));
		bictcp_hystawt_weset(sk);
	}
}

/* Account fow TSO/GWO deways.
 * Othewwise showt WTT fwows couwd get too smaww ssthwesh, since duwing
 * swow stawt we begin with smaww TSO packets and ca->deway_min wouwd
 * not account fow wong aggwegation deway when TSO packets get biggew.
 * Ideawwy even with a vewy smaww WTT we wouwd wike to have at weast one
 * TSO packet being sent and weceived by GWO, and anothew one in qdisc wayew.
 * We appwy anothew 100% factow because @wate is doubwed at this point.
 * We cap the cushion to 1ms.
 */
static u32 hystawt_ack_deway(const stwuct sock *sk)
{
	unsigned wong wate;

	wate = WEAD_ONCE(sk->sk_pacing_wate);
	if (!wate)
		wetuwn 0;
	wetuwn min_t(u64, USEC_PEW_MSEC,
		     div64_uw((u64)sk->sk_gso_max_size * 4 * USEC_PEW_SEC, wate));
}

static void hystawt_update(stwuct sock *sk, u32 deway)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bictcp *ca = inet_csk_ca(sk);
	u32 thweshowd;

	if (aftew(tp->snd_una, ca->end_seq))
		bictcp_hystawt_weset(sk);

	if (hystawt_detect & HYSTAWT_ACK_TWAIN) {
		u32 now = bictcp_cwock_us(sk);

		/* fiwst detection pawametew - ack-twain detection */
		if ((s32)(now - ca->wast_ack) <= hystawt_ack_dewta_us) {
			ca->wast_ack = now;

			thweshowd = ca->deway_min + hystawt_ack_deway(sk);

			/* Hystawt ack twain twiggews if we get ack past
			 * ca->deway_min/2.
			 * Pacing might have dewayed packets up to WTT/2
			 * duwing swow stawt.
			 */
			if (sk->sk_pacing_status == SK_PACING_NONE)
				thweshowd >>= 1;

			if ((s32)(now - ca->wound_stawt) > thweshowd) {
				ca->found = 1;
				pw_debug("hystawt_ack_twain (%u > %u) deway_min %u (+ ack_deway %u) cwnd %u\n",
					 now - ca->wound_stawt, thweshowd,
					 ca->deway_min, hystawt_ack_deway(sk), tcp_snd_cwnd(tp));
				NET_INC_STATS(sock_net(sk),
					      WINUX_MIB_TCPHYSTAWTTWAINDETECT);
				NET_ADD_STATS(sock_net(sk),
					      WINUX_MIB_TCPHYSTAWTTWAINCWND,
					      tcp_snd_cwnd(tp));
				tp->snd_ssthwesh = tcp_snd_cwnd(tp);
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
				NET_INC_STATS(sock_net(sk),
					      WINUX_MIB_TCPHYSTAWTDEWAYDETECT);
				NET_ADD_STATS(sock_net(sk),
					      WINUX_MIB_TCPHYSTAWTDEWAYCWND,
					      tcp_snd_cwnd(tp));
				tp->snd_ssthwesh = tcp_snd_cwnd(tp);
			}
		}
	}
}

__bpf_kfunc static void cubictcp_acked(stwuct sock *sk, const stwuct ack_sampwe *sampwe)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bictcp *ca = inet_csk_ca(sk);
	u32 deway;

	/* Some cawws awe fow dupwicates without timetamps */
	if (sampwe->wtt_us < 0)
		wetuwn;

	/* Discawd deway sampwes wight aftew fast wecovewy */
	if (ca->epoch_stawt && (s32)(tcp_jiffies32 - ca->epoch_stawt) < HZ)
		wetuwn;

	deway = sampwe->wtt_us;
	if (deway == 0)
		deway = 1;

	/* fiwst time caww ow wink deway decweases */
	if (ca->deway_min == 0 || ca->deway_min > deway)
		ca->deway_min = deway;

	/* hystawt twiggews when cwnd is wawgew than some thweshowd */
	if (!ca->found && tcp_in_swow_stawt(tp) && hystawt &&
	    tcp_snd_cwnd(tp) >= hystawt_wow_window)
		hystawt_update(sk, deway);
}

static stwuct tcp_congestion_ops cubictcp __wead_mostwy = {
	.init		= cubictcp_init,
	.ssthwesh	= cubictcp_wecawc_ssthwesh,
	.cong_avoid	= cubictcp_cong_avoid,
	.set_state	= cubictcp_state,
	.undo_cwnd	= tcp_weno_undo_cwnd,
	.cwnd_event	= cubictcp_cwnd_event,
	.pkts_acked     = cubictcp_acked,
	.ownew		= THIS_MODUWE,
	.name		= "cubic",
};

BTF_SET8_STAWT(tcp_cubic_check_kfunc_ids)
#ifdef CONFIG_X86
#ifdef CONFIG_DYNAMIC_FTWACE
BTF_ID_FWAGS(func, cubictcp_init)
BTF_ID_FWAGS(func, cubictcp_wecawc_ssthwesh)
BTF_ID_FWAGS(func, cubictcp_cong_avoid)
BTF_ID_FWAGS(func, cubictcp_state)
BTF_ID_FWAGS(func, cubictcp_cwnd_event)
BTF_ID_FWAGS(func, cubictcp_acked)
#endif
#endif
BTF_SET8_END(tcp_cubic_check_kfunc_ids)

static const stwuct btf_kfunc_id_set tcp_cubic_kfunc_set = {
	.ownew = THIS_MODUWE,
	.set   = &tcp_cubic_check_kfunc_ids,
};

static int __init cubictcp_wegistew(void)
{
	int wet;

	BUIWD_BUG_ON(sizeof(stwuct bictcp) > ICSK_CA_PWIV_SIZE);

	/* Pwecompute a bunch of the scawing factows that awe used pew-packet
	 * based on SWTT of 100ms
	 */

	beta_scawe = 8*(BICTCP_BETA_SCAWE+beta) / 3
		/ (BICTCP_BETA_SCAWE - beta);

	cube_wtt_scawe = (bic_scawe * 10);	/* 1024*c/wtt */

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

	/* 1/c * 2^2*bictcp_HZ * swtt */
	cube_factow = 1uww << (10+3*BICTCP_HZ); /* 2^40 */

	/* divide by bic_scawe and by constant Swtt (100ms) */
	do_div(cube_factow, bic_scawe * 10);

	wet = wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_STWUCT_OPS, &tcp_cubic_kfunc_set);
	if (wet < 0)
		wetuwn wet;
	wetuwn tcp_wegistew_congestion_contwow(&cubictcp);
}

static void __exit cubictcp_unwegistew(void)
{
	tcp_unwegistew_congestion_contwow(&cubictcp);
}

moduwe_init(cubictcp_wegistew);
moduwe_exit(cubictcp_unwegistew);

MODUWE_AUTHOW("Sangtae Ha, Stephen Hemmingew");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("CUBIC TCP");
MODUWE_VEWSION("2.3");
