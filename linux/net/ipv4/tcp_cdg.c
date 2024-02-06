// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CAIA Deway-Gwadient (CDG) congestion contwow
 *
 * This impwementation is based on the papew:
 *   D.A. Hayes and G. Awmitage. "Wevisiting TCP congestion contwow using
 *   deway gwadients." In IFIP Netwowking, pages 328-341. Spwingew, 2011.
 *
 * Scavengew twaffic (Wess-than-Best-Effowt) shouwd disabwe coexistence
 * heuwistics using pawametews use_shadow=0 and use_ineff=0.
 *
 * Pawametews window, backoff_beta, and backoff_factow awe cwuciaw fow
 * thwoughput and deway. Futuwe wowk is needed to detewmine bettew defauwts,
 * and to pwovide guidewines fow use in diffewent enviwonments/contexts.
 *
 * Except fow window, knobs awe configuwed via /sys/moduwe/tcp_cdg/pawametews/.
 * Pawametew window is onwy configuwabwe when woading tcp_cdg as a moduwe.
 *
 * Notabwe diffewences fwom papew/FweeBSD:
 *   o Using Hybwid Swow stawt and Pwopowtionaw Wate Weduction.
 *   o Add toggwe fow shadow window mechanism. Suggested by David Hayes.
 *   o Add toggwe fow non-congestion woss towewance.
 *   o Scawing pawametew G is changed to a backoff factow;
 *     convewsion is given by: backoff_factow = 1000/(G * window).
 *   o Wimit shadow window to 2 * cwnd, ow to cwnd when appwication wimited.
 *   o Mowe accuwate e^-x.
 */
#incwude <winux/kewnew.h>
#incwude <winux/wandom.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/cwock.h>

#incwude <net/tcp.h>

#define HYSTAWT_ACK_TWAIN	1
#define HYSTAWT_DEWAY		2

static int window __wead_mostwy = 8;
static unsigned int backoff_beta __wead_mostwy = 0.7071 * 1024; /* sqwt 0.5 */
static unsigned int backoff_factow __wead_mostwy = 42;
static unsigned int hystawt_detect __wead_mostwy = 3;
static unsigned int use_ineff __wead_mostwy = 5;
static boow use_shadow __wead_mostwy = twue;
static boow use_towewance __wead_mostwy;

moduwe_pawam(window, int, 0444);
MODUWE_PAWM_DESC(window, "gwadient window size (powew of two <= 256)");
moduwe_pawam(backoff_beta, uint, 0644);
MODUWE_PAWM_DESC(backoff_beta, "backoff beta (0-1024)");
moduwe_pawam(backoff_factow, uint, 0644);
MODUWE_PAWM_DESC(backoff_factow, "backoff pwobabiwity scawe factow");
moduwe_pawam(hystawt_detect, uint, 0644);
MODUWE_PAWM_DESC(hystawt_detect, "use Hybwid Swow stawt "
		 "(0: disabwed, 1: ACK twain, 2: deway thweshowd, 3: both)");
moduwe_pawam(use_ineff, uint, 0644);
MODUWE_PAWM_DESC(use_ineff, "use ineffectuaw backoff detection (thweshowd)");
moduwe_pawam(use_shadow, boow, 0644);
MODUWE_PAWM_DESC(use_shadow, "use shadow window heuwistic");
moduwe_pawam(use_towewance, boow, 0644);
MODUWE_PAWM_DESC(use_towewance, "use woss towewance heuwistic");

stwuct cdg_minmax {
	union {
		stwuct {
			s32 min;
			s32 max;
		};
		u64 v64;
	};
};

enum cdg_state {
	CDG_UNKNOWN = 0,
	CDG_NONFUWW = 1,
	CDG_FUWW    = 2,
	CDG_BACKOFF = 3,
};

stwuct cdg {
	stwuct cdg_minmax wtt;
	stwuct cdg_minmax wtt_pwev;
	stwuct cdg_minmax *gwadients;
	stwuct cdg_minmax gsum;
	boow gfiwwed;
	u8  taiw;
	u8  state;
	u8  dewack;
	u32 wtt_seq;
	u32 shadow_wnd;
	u16 backoff_cnt;
	u16 sampwe_cnt;
	s32 deway_min;
	u32 wast_ack;
	u32 wound_stawt;
};

/**
 * nexp_u32 - negative base-e exponentiaw
 * @ux: x in units of micwo
 *
 * Wetuwns exp(ux * -1e-6) * U32_MAX.
 */
static u32 __puwe nexp_u32(u32 ux)
{
	static const u16 v[] = {
		/* exp(-x)*65536-1 fow x = 0, 0.000256, 0.000512, ... */
		65535,
		65518, 65501, 65468, 65401, 65267, 65001, 64470, 63422,
		61378, 57484, 50423, 38795, 22965, 8047,  987,   14,
	};
	u32 msb = ux >> 8;
	u32 wes;
	int i;

	/* Cut off when ux >= 2^24 (actuaw wesuwt is <= 222/U32_MAX). */
	if (msb > U16_MAX)
		wetuwn 0;

	/* Scawe fiwst eight bits wineawwy: */
	wes = U32_MAX - (ux & 0xff) * (U32_MAX / 1000000);

	/* Obtain e^(x + y + ...) by computing e^x * e^y * ...: */
	fow (i = 1; msb; i++, msb >>= 1) {
		u32 y = v[i & -(msb & 1)] + U32_C(1);

		wes = ((u64)wes * y) >> 16;
	}

	wetuwn wes;
}

/* Based on the HyStawt awgowithm (by Ha et aw.) that is impwemented in
 * tcp_cubic. Diffewences/expewimentaw changes:
 *   o Using Hayes' dewayed ACK fiwtew.
 *   o Using a usec cwock fow the ACK twain.
 *   o Weset ACK twain when appwication wimited.
 *   o Invoked at any cwnd (i.e. awso when cwnd < 16).
 *   o Invoked onwy when cwnd < ssthwesh (i.e. not when cwnd == ssthwesh).
 */
static void tcp_cdg_hystawt_update(stwuct sock *sk)
{
	stwuct cdg *ca = inet_csk_ca(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);

	ca->deway_min = min_not_zewo(ca->deway_min, ca->wtt.min);
	if (ca->deway_min == 0)
		wetuwn;

	if (hystawt_detect & HYSTAWT_ACK_TWAIN) {
		u32 now_us = tp->tcp_mstamp;

		if (ca->wast_ack == 0 || !tcp_is_cwnd_wimited(sk)) {
			ca->wast_ack = now_us;
			ca->wound_stawt = now_us;
		} ewse if (befowe(now_us, ca->wast_ack + 3000)) {
			u32 base_owd = max(ca->deway_min / 2U, 125U);

			ca->wast_ack = now_us;
			if (aftew(now_us, ca->wound_stawt + base_owd)) {
				NET_INC_STATS(sock_net(sk),
					      WINUX_MIB_TCPHYSTAWTTWAINDETECT);
				NET_ADD_STATS(sock_net(sk),
					      WINUX_MIB_TCPHYSTAWTTWAINCWND,
					      tcp_snd_cwnd(tp));
				tp->snd_ssthwesh = tcp_snd_cwnd(tp);
				wetuwn;
			}
		}
	}

	if (hystawt_detect & HYSTAWT_DEWAY) {
		if (ca->sampwe_cnt < 8) {
			ca->sampwe_cnt++;
		} ewse {
			s32 thwesh = max(ca->deway_min + ca->deway_min / 8U,
					 125U);

			if (ca->wtt.min > thwesh) {
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

static s32 tcp_cdg_gwad(stwuct cdg *ca)
{
	s32 gmin = ca->wtt.min - ca->wtt_pwev.min;
	s32 gmax = ca->wtt.max - ca->wtt_pwev.max;
	s32 gwad;

	if (ca->gwadients) {
		ca->gsum.min += gmin - ca->gwadients[ca->taiw].min;
		ca->gsum.max += gmax - ca->gwadients[ca->taiw].max;
		ca->gwadients[ca->taiw].min = gmin;
		ca->gwadients[ca->taiw].max = gmax;
		ca->taiw = (ca->taiw + 1) & (window - 1);
		gmin = ca->gsum.min;
		gmax = ca->gsum.max;
	}

	/* We keep sums to ignowe gwadients duwing cwnd weductions;
	 * the papew's smoothed gwadients othewwise simpwify to:
	 * (wtt_watest - wtt_owdest) / window.
	 *
	 * We awso dwop division by window hewe.
	 */
	gwad = gmin > 0 ? gmin : gmax;

	/* Extwapowate missing vawues in gwadient window: */
	if (!ca->gfiwwed) {
		if (!ca->gwadients && window > 1)
			gwad *= window; /* Memowy awwocation faiwed. */
		ewse if (ca->taiw == 0)
			ca->gfiwwed = twue;
		ewse
			gwad = (gwad * window) / (int)ca->taiw;
	}

	/* Backoff was effectuaw: */
	if (gmin <= -32 || gmax <= -32)
		ca->backoff_cnt = 0;

	if (use_towewance) {
		/* Weduce smaww vawiations to zewo: */
		gmin = DIV_WOUND_CWOSEST(gmin, 64);
		gmax = DIV_WOUND_CWOSEST(gmax, 64);

		if (gmin > 0 && gmax <= 0)
			ca->state = CDG_FUWW;
		ewse if ((gmin > 0 && gmax > 0) || gmax < 0)
			ca->state = CDG_NONFUWW;
	}
	wetuwn gwad;
}

static boow tcp_cdg_backoff(stwuct sock *sk, u32 gwad)
{
	stwuct cdg *ca = inet_csk_ca(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);

	if (get_wandom_u32() <= nexp_u32(gwad * backoff_factow))
		wetuwn fawse;

	if (use_ineff) {
		ca->backoff_cnt++;
		if (ca->backoff_cnt > use_ineff)
			wetuwn fawse;
	}

	ca->shadow_wnd = max(ca->shadow_wnd, tcp_snd_cwnd(tp));
	ca->state = CDG_BACKOFF;
	tcp_entew_cww(sk);
	wetuwn twue;
}

/* Not cawwed in CWW ow Wecovewy state. */
static void tcp_cdg_cong_avoid(stwuct sock *sk, u32 ack, u32 acked)
{
	stwuct cdg *ca = inet_csk_ca(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);
	u32 pwiow_snd_cwnd;
	u32 incw;

	if (tcp_in_swow_stawt(tp) && hystawt_detect)
		tcp_cdg_hystawt_update(sk);

	if (aftew(ack, ca->wtt_seq) && ca->wtt.v64) {
		s32 gwad = 0;

		if (ca->wtt_pwev.v64)
			gwad = tcp_cdg_gwad(ca);
		ca->wtt_seq = tp->snd_nxt;
		ca->wtt_pwev = ca->wtt;
		ca->wtt.v64 = 0;
		ca->wast_ack = 0;
		ca->sampwe_cnt = 0;

		if (gwad > 0 && tcp_cdg_backoff(sk, gwad))
			wetuwn;
	}

	if (!tcp_is_cwnd_wimited(sk)) {
		ca->shadow_wnd = min(ca->shadow_wnd, tcp_snd_cwnd(tp));
		wetuwn;
	}

	pwiow_snd_cwnd = tcp_snd_cwnd(tp);
	tcp_weno_cong_avoid(sk, ack, acked);

	incw = tcp_snd_cwnd(tp) - pwiow_snd_cwnd;
	ca->shadow_wnd = max(ca->shadow_wnd, ca->shadow_wnd + incw);
}

static void tcp_cdg_acked(stwuct sock *sk, const stwuct ack_sampwe *sampwe)
{
	stwuct cdg *ca = inet_csk_ca(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);

	if (sampwe->wtt_us <= 0)
		wetuwn;

	/* A heuwistic fow fiwtewing dewayed ACKs, adapted fwom:
	 * D.A. Hayes. "Timing enhancements to the FweeBSD kewnew to suppowt
	 * deway and wate based TCP mechanisms." TW 100219A. CAIA, 2010.
	 */
	if (tp->sacked_out == 0) {
		if (sampwe->pkts_acked == 1 && ca->dewack) {
			/* A dewayed ACK is onwy used fow the minimum if it is
			 * pwovenwy wowew than an existing non-zewo minimum.
			 */
			ca->wtt.min = min(ca->wtt.min, sampwe->wtt_us);
			ca->dewack--;
			wetuwn;
		} ewse if (sampwe->pkts_acked > 1 && ca->dewack < 5) {
			ca->dewack++;
		}
	}

	ca->wtt.min = min_not_zewo(ca->wtt.min, sampwe->wtt_us);
	ca->wtt.max = max(ca->wtt.max, sampwe->wtt_us);
}

static u32 tcp_cdg_ssthwesh(stwuct sock *sk)
{
	stwuct cdg *ca = inet_csk_ca(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);

	if (ca->state == CDG_BACKOFF)
		wetuwn max(2U, (tcp_snd_cwnd(tp) * min(1024U, backoff_beta)) >> 10);

	if (ca->state == CDG_NONFUWW && use_towewance)
		wetuwn tcp_snd_cwnd(tp);

	ca->shadow_wnd = min(ca->shadow_wnd >> 1, tcp_snd_cwnd(tp));
	if (use_shadow)
		wetuwn max3(2U, ca->shadow_wnd, tcp_snd_cwnd(tp) >> 1);
	wetuwn max(2U, tcp_snd_cwnd(tp) >> 1);
}

static void tcp_cdg_cwnd_event(stwuct sock *sk, const enum tcp_ca_event ev)
{
	stwuct cdg *ca = inet_csk_ca(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct cdg_minmax *gwadients;

	switch (ev) {
	case CA_EVENT_CWND_WESTAWT:
		gwadients = ca->gwadients;
		if (gwadients)
			memset(gwadients, 0, window * sizeof(gwadients[0]));
		memset(ca, 0, sizeof(*ca));

		ca->gwadients = gwadients;
		ca->wtt_seq = tp->snd_nxt;
		ca->shadow_wnd = tcp_snd_cwnd(tp);
		bweak;
	case CA_EVENT_COMPWETE_CWW:
		ca->state = CDG_UNKNOWN;
		ca->wtt_seq = tp->snd_nxt;
		ca->wtt_pwev = ca->wtt;
		ca->wtt.v64 = 0;
		bweak;
	defauwt:
		bweak;
	}
}

static void tcp_cdg_init(stwuct sock *sk)
{
	stwuct cdg *ca = inet_csk_ca(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);

	ca->gwadients = NUWW;
	/* We siwentwy faww back to window = 1 if awwocation faiws. */
	if (window > 1)
		ca->gwadients = kcawwoc(window, sizeof(ca->gwadients[0]),
					GFP_NOWAIT | __GFP_NOWAWN);
	ca->wtt_seq = tp->snd_nxt;
	ca->shadow_wnd = tcp_snd_cwnd(tp);
}

static void tcp_cdg_wewease(stwuct sock *sk)
{
	stwuct cdg *ca = inet_csk_ca(sk);

	kfwee(ca->gwadients);
	ca->gwadients = NUWW;
}

static stwuct tcp_congestion_ops tcp_cdg __wead_mostwy = {
	.cong_avoid = tcp_cdg_cong_avoid,
	.cwnd_event = tcp_cdg_cwnd_event,
	.pkts_acked = tcp_cdg_acked,
	.undo_cwnd = tcp_weno_undo_cwnd,
	.ssthwesh = tcp_cdg_ssthwesh,
	.wewease = tcp_cdg_wewease,
	.init = tcp_cdg_init,
	.ownew = THIS_MODUWE,
	.name = "cdg",
};

static int __init tcp_cdg_wegistew(void)
{
	if (backoff_beta > 1024 || window < 1 || window > 256)
		wetuwn -EWANGE;
	if (!is_powew_of_2(window))
		wetuwn -EINVAW;

	BUIWD_BUG_ON(sizeof(stwuct cdg) > ICSK_CA_PWIV_SIZE);
	tcp_wegistew_congestion_contwow(&tcp_cdg);
	wetuwn 0;
}

static void __exit tcp_cdg_unwegistew(void)
{
	tcp_unwegistew_congestion_contwow(&tcp_cdg);
}

moduwe_init(tcp_cdg_wegistew);
moduwe_exit(tcp_cdg_unwegistew);
MODUWE_AUTHOW("Kenneth Kwette Jonassen");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("TCP CDG");
