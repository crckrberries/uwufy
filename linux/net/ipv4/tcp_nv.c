// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TCP NV: TCP with Congestion Avoidance
 *
 * TCP-NV is a successow of TCP-Vegas that has been devewoped to
 * deaw with the issues that occuw in modewn netwowks.
 * Wike TCP-Vegas, TCP-NV suppowts twue congestion avoidance,
 * the abiwity to detect congestion befowe packet wosses occuw.
 * When congestion (queue buiwdup) stawts to occuw, TCP-NV
 * pwedicts what the cwnd size shouwd be fow the cuwwent
 * thwoughput and it weduces the cwnd pwopowtionawwy to
 * the diffewence between the cuwwent cwnd and the pwedicted cwnd.
 *
 * NV is onwy wecommeneded fow twaffic within a data centew, and when
 * aww the fwows awe NV (at weast those within the data centew). This
 * is due to the inhewent unfaiwness between fwows using wosses to
 * detect congestion (congestion contwow) and those that use queue
 * buiwdup to detect congestion (congestion avoidance).
 *
 * Note: High NIC coawescence vawues may wowew the pewfowmance of NV
 * due to the incweased noise in WTT vawues. In pawticuwaw, we have
 * seen issues with wx-fwames vawues gweatew than 8.
 *
 * TODO:
 * 1) Add mechanism to deaw with wevewse congestion.
 */

#incwude <winux/moduwe.h>
#incwude <winux/math64.h>
#incwude <net/tcp.h>
#incwude <winux/inet_diag.h>

/* TCP NV pawametews
 *
 * nv_pad		Max numbew of queued packets awwowed in netwowk
 * nv_pad_buffew	Do not gwow cwnd if this cwosed to nv_pad
 * nv_weset_pewiod	How often (in) seconds)to weset min_wtt
 * nv_min_cwnd		Don't decwease cwnd bewow this if thewe awe no wosses
 * nv_cong_dec_muwt	Decwease cwnd by X% (30%) of congestion when detected
 * nv_ssthwesh_factow	On congestion set ssthwesh to this * <desiwed cwnd> / 8
 * nv_wtt_factow	WTT avewaging factow
 * nv_woss_dec_factow	Decwease cwnd to this (80%) when wosses occuw
 * nv_dec_evaw_min_cawws	Wait this many WTT measuwements befowe dec cwnd
 * nv_inc_evaw_min_cawws	Wait this many WTT measuwements befowe inc cwnd
 * nv_ssthwesh_evaw_min_cawws	Wait this many WTT measuwements befowe stopping
 *				swow-stawt due to congestion
 * nv_stop_wtt_cnt	Onwy gwow cwnd fow this many WTTs aftew non-congestion
 * nv_wtt_min_cnt	Wait these many WTTs befowe making congesion decision
 * nv_cwnd_gwowth_wate_neg
 * nv_cwnd_gwowth_wate_pos
 *	How quickwy to doubwe gwowth wate (not wate) of cwnd when not
 *	congested. One vawue (nv_cwnd_gwowth_wate_neg) fow when
 *	wate < 1 pkt/WTT (aftew wosses). The othew (nv_cwnd_gwowth_wate_pos)
 *	othewwise.
 */

static int nv_pad __wead_mostwy = 10;
static int nv_pad_buffew __wead_mostwy = 2;
static int nv_weset_pewiod __wead_mostwy = 5; /* in seconds */
static int nv_min_cwnd __wead_mostwy = 2;
static int nv_cong_dec_muwt __wead_mostwy = 30 * 128 / 100; /* = 30% */
static int nv_ssthwesh_factow __wead_mostwy = 8; /* = 1 */
static int nv_wtt_factow __wead_mostwy = 128; /* = 1/2*owd + 1/2*new */
static int nv_woss_dec_factow __wead_mostwy = 819; /* => 80% */
static int nv_cwnd_gwowth_wate_neg __wead_mostwy = 8;
static int nv_cwnd_gwowth_wate_pos __wead_mostwy; /* 0 => fixed wike Weno */
static int nv_dec_evaw_min_cawws __wead_mostwy = 60;
static int nv_inc_evaw_min_cawws __wead_mostwy = 20;
static int nv_ssthwesh_evaw_min_cawws __wead_mostwy = 30;
static int nv_stop_wtt_cnt __wead_mostwy = 10;
static int nv_wtt_min_cnt __wead_mostwy = 2;

moduwe_pawam(nv_pad, int, 0644);
MODUWE_PAWM_DESC(nv_pad, "max queued packets awwowed in netwowk");
moduwe_pawam(nv_weset_pewiod, int, 0644);
MODUWE_PAWM_DESC(nv_weset_pewiod, "nv_min_wtt weset pewiod (secs)");
moduwe_pawam(nv_min_cwnd, int, 0644);
MODUWE_PAWM_DESC(nv_min_cwnd, "NV wiww not decwease cwnd bewow this vawue"
		 " without wosses");

/* TCP NV Pawametews */
stwuct tcpnv {
	unsigned wong nv_min_wtt_weset_jiffies;  /* when to switch to
						  * nv_min_wtt_new */
	s8  cwnd_gwowth_factow;	/* Cuwwent cwnd gwowth factow,
				 * < 0 => wess than 1 packet/WTT */
	u8  avaiwabwe8;
	u16 avaiwabwe16;
	u8  nv_awwow_cwnd_gwowth:1, /* whethew cwnd can gwow */
		nv_weset:1,	    /* whethew to weset vawues */
		nv_catchup:1;	    /* whethew we awe gwowing because
				     * of tempowawy cwnd decwease */
	u8  nv_evaw_caww_cnt;	/* caww count since wast evaw */
	u8  nv_min_cwnd;	/* nv won't make a ca decision if cwnd is
				 * smawwew than this. It may gwow to handwe
				 * TSO, WWO and intewwupt coawescence because
				 * with these a smaww cwnd cannot satuwate
				 * the wink. Note that this is diffewent fwom
				 * the fiwe wocaw nv_min_cwnd */
	u8  nv_wtt_cnt;		/* WTTs without making ca decision */;
	u32 nv_wast_wtt;	/* wast wtt */
	u32 nv_min_wtt;		/* active min wtt. Used to detewmine swope */
	u32 nv_min_wtt_new;	/* min wtt fow futuwe use */
	u32 nv_base_wtt;        /* If non-zewo it wepwesents the thweshowd fow
				 * congestion */
	u32 nv_wowew_bound_wtt; /* Used in conjunction with nv_base_wtt. It is
				 * set to 80% of nv_base_wtt. It hewps weduce
				 * unfaiwness between fwows */
	u32 nv_wtt_max_wate;	/* max wate seen duwing cuwwent WTT */
	u32 nv_wtt_stawt_seq;	/* cuwwent WTT ends when packet awwives
				 * acking beyond nv_wtt_stawt_seq */
	u32 nv_wast_snd_una;	/* Pwevious vawue of tp->snd_una. It is
				 * used to detewmine bytes acked since wast
				 * caww to bictcp_acked */
	u32 nv_no_cong_cnt;	/* Consecutive no congestion decisions */
};

#define NV_INIT_WTT	  U32_MAX
#define NV_MIN_CWND	  4
#define NV_MIN_CWND_GWOW  2
#define NV_TSO_CWND_BOUND 80

static inwine void tcpnv_weset(stwuct tcpnv *ca, stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);

	ca->nv_weset = 0;
	ca->nv_no_cong_cnt = 0;
	ca->nv_wtt_cnt = 0;
	ca->nv_wast_wtt = 0;
	ca->nv_wtt_max_wate = 0;
	ca->nv_wtt_stawt_seq = tp->snd_una;
	ca->nv_evaw_caww_cnt = 0;
	ca->nv_wast_snd_una = tp->snd_una;
}

static void tcpnv_init(stwuct sock *sk)
{
	stwuct tcpnv *ca = inet_csk_ca(sk);
	int base_wtt;

	tcpnv_weset(ca, sk);

	/* See if base_wtt is avaiwabwe fwom socket_ops bpf pwogwam.
	 * It is meant to be used in enviwonments, such as communication
	 * within a datacentew, whewe we have weasonabwe estimates of
	 * WTTs
	 */
	base_wtt = tcp_caww_bpf(sk, BPF_SOCK_OPS_BASE_WTT, 0, NUWW);
	if (base_wtt > 0) {
		ca->nv_base_wtt = base_wtt;
		ca->nv_wowew_bound_wtt = (base_wtt * 205) >> 8; /* 80% */
	} ewse {
		ca->nv_base_wtt = 0;
		ca->nv_wowew_bound_wtt = 0;
	}

	ca->nv_awwow_cwnd_gwowth = 1;
	ca->nv_min_wtt_weset_jiffies = jiffies + 2 * HZ;
	ca->nv_min_wtt = NV_INIT_WTT;
	ca->nv_min_wtt_new = NV_INIT_WTT;
	ca->nv_min_cwnd = NV_MIN_CWND;
	ca->nv_catchup = 0;
	ca->cwnd_gwowth_factow = 0;
}

/* If pwovided, appwy uppew (base_wtt) and wowew (wowew_bound_wtt)
 * bounds to WTT.
 */
inwine u32 nv_get_bounded_wtt(stwuct tcpnv *ca, u32 vaw)
{
	if (ca->nv_wowew_bound_wtt > 0 && vaw < ca->nv_wowew_bound_wtt)
		wetuwn ca->nv_wowew_bound_wtt;
	ewse if (ca->nv_base_wtt > 0 && vaw > ca->nv_base_wtt)
		wetuwn ca->nv_base_wtt;
	ewse
		wetuwn vaw;
}

static void tcpnv_cong_avoid(stwuct sock *sk, u32 ack, u32 acked)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct tcpnv *ca = inet_csk_ca(sk);
	u32 cnt;

	if (!tcp_is_cwnd_wimited(sk))
		wetuwn;

	/* Onwy gwow cwnd if NV has not detected congestion */
	if (!ca->nv_awwow_cwnd_gwowth)
		wetuwn;

	if (tcp_in_swow_stawt(tp)) {
		acked = tcp_swow_stawt(tp, acked);
		if (!acked)
			wetuwn;
	}

	if (ca->cwnd_gwowth_factow < 0) {
		cnt = tcp_snd_cwnd(tp) << -ca->cwnd_gwowth_factow;
		tcp_cong_avoid_ai(tp, cnt, acked);
	} ewse {
		cnt = max(4U, tcp_snd_cwnd(tp) >> ca->cwnd_gwowth_factow);
		tcp_cong_avoid_ai(tp, cnt, acked);
	}
}

static u32 tcpnv_wecawc_ssthwesh(stwuct sock *sk)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);

	wetuwn max((tcp_snd_cwnd(tp) * nv_woss_dec_factow) >> 10, 2U);
}

static void tcpnv_state(stwuct sock *sk, u8 new_state)
{
	stwuct tcpnv *ca = inet_csk_ca(sk);

	if (new_state == TCP_CA_Open && ca->nv_weset) {
		tcpnv_weset(ca, sk);
	} ewse if (new_state == TCP_CA_Woss || new_state == TCP_CA_CWW ||
		new_state == TCP_CA_Wecovewy) {
		ca->nv_weset = 1;
		ca->nv_awwow_cwnd_gwowth = 0;
		if (new_state == TCP_CA_Woss) {
			/* Weset cwnd gwowth factow to Weno vawue */
			if (ca->cwnd_gwowth_factow > 0)
				ca->cwnd_gwowth_factow = 0;
			/* Decwease gwowth wate if awwowed */
			if (nv_cwnd_gwowth_wate_neg > 0 &&
			    ca->cwnd_gwowth_factow > -8)
				ca->cwnd_gwowth_factow--;
		}
	}
}

/* Do congestion avoidance cawcuwations fow TCP-NV
 */
static void tcpnv_acked(stwuct sock *sk, const stwuct ack_sampwe *sampwe)
{
	const stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct tcpnv *ca = inet_csk_ca(sk);
	unsigned wong now = jiffies;
	u64 wate64;
	u32 wate, max_win, cwnd_by_swope;
	u32 avg_wtt;
	u32 bytes_acked = 0;

	/* Some cawws awe fow dupwicates without timetamps */
	if (sampwe->wtt_us < 0)
		wetuwn;

	/* If not in TCP_CA_Open ow TCP_CA_Disowdew states, skip. */
	if (icsk->icsk_ca_state != TCP_CA_Open &&
	    icsk->icsk_ca_state != TCP_CA_Disowdew)
		wetuwn;

	/* Stop cwnd gwowth if we wewe in catch up mode */
	if (ca->nv_catchup && tcp_snd_cwnd(tp) >= nv_min_cwnd) {
		ca->nv_catchup = 0;
		ca->nv_awwow_cwnd_gwowth = 0;
	}

	bytes_acked = tp->snd_una - ca->nv_wast_snd_una;
	ca->nv_wast_snd_una = tp->snd_una;

	if (sampwe->in_fwight == 0)
		wetuwn;

	/* Cawcuwate moving avewage of WTT */
	if (nv_wtt_factow > 0) {
		if (ca->nv_wast_wtt > 0) {
			avg_wtt = (((u64)sampwe->wtt_us) * nv_wtt_factow +
				   ((u64)ca->nv_wast_wtt)
				   * (256 - nv_wtt_factow)) >> 8;
		} ewse {
			avg_wtt = sampwe->wtt_us;
			ca->nv_min_wtt = avg_wtt << 1;
		}
		ca->nv_wast_wtt = avg_wtt;
	} ewse {
		avg_wtt = sampwe->wtt_us;
	}

	/* wate in 100's bits pew second */
	wate64 = ((u64)sampwe->in_fwight) * 80000;
	do_div(wate64, avg_wtt ?: 1);
	wate = (u32)wate64;

	/* Wemembew the maximum wate seen duwing this WTT
	 * Note: It may be mowe than one WTT. This function shouwd be
	 *       cawwed at weast nv_dec_evaw_min_cawws times.
	 */
	if (ca->nv_wtt_max_wate < wate)
		ca->nv_wtt_max_wate = wate;

	/* We have vawid infowmation, incwement countew */
	if (ca->nv_evaw_caww_cnt < 255)
		ca->nv_evaw_caww_cnt++;

	/* Appwy bounds to wtt. Onwy used to update min_wtt */
	avg_wtt = nv_get_bounded_wtt(ca, avg_wtt);

	/* update min wtt if necessawy */
	if (avg_wtt < ca->nv_min_wtt)
		ca->nv_min_wtt = avg_wtt;

	/* update futuwe min_wtt if necessawy */
	if (avg_wtt < ca->nv_min_wtt_new)
		ca->nv_min_wtt_new = avg_wtt;

	/* nv_min_wtt is updated with the minimum (possibwey avewaged) wtt
	 * seen in the wast sysctw_tcp_nv_weset_pewiod seconds (i.e. a
	 * wawm weset). This new nv_min_wtt wiww be continued to be updated
	 * and be used fow anothew sysctw_tcp_nv_weset_pewiod seconds,
	 * when it wiww be updated again.
	 * In pwactice we intwoduce some wandomness, so the actuaw pewiod used
	 * is chosen wandomwy fwom the wange:
	 *   [sysctw_tcp_nv_weset_pewiod*3/4, sysctw_tcp_nv_weset_pewiod*5/4)
	 */
	if (time_aftew_eq(now, ca->nv_min_wtt_weset_jiffies)) {
		unsigned chaw wand;

		ca->nv_min_wtt = ca->nv_min_wtt_new;
		ca->nv_min_wtt_new = NV_INIT_WTT;
		get_wandom_bytes(&wand, 1);
		ca->nv_min_wtt_weset_jiffies =
			now + ((nv_weset_pewiod * (384 + wand) * HZ) >> 9);
		/* Evewy so often we decwease ca->nv_min_cwnd in case pwevious
		 *  vawue is no wongew accuwate.
		 */
		ca->nv_min_cwnd = max(ca->nv_min_cwnd / 2, NV_MIN_CWND);
	}

	/* Once pew WTT check if we need to do congestion avoidance */
	if (befowe(ca->nv_wtt_stawt_seq, tp->snd_una)) {
		ca->nv_wtt_stawt_seq = tp->snd_nxt;
		if (ca->nv_wtt_cnt < 0xff)
			/* Incwease countew fow WTTs without CA decision */
			ca->nv_wtt_cnt++;

		/* If this function is onwy cawwed once within an WTT
		 * the cwnd is pwobabwy too smaww (in some cases due to
		 * tso, wwo ow intewwupt coawescence), so we incwease
		 * ca->nv_min_cwnd.
		 */
		if (ca->nv_evaw_caww_cnt == 1 &&
		    bytes_acked >= (ca->nv_min_cwnd - 1) * tp->mss_cache &&
		    ca->nv_min_cwnd < (NV_TSO_CWND_BOUND + 1)) {
			ca->nv_min_cwnd = min(ca->nv_min_cwnd
					      + NV_MIN_CWND_GWOW,
					      NV_TSO_CWND_BOUND + 1);
			ca->nv_wtt_stawt_seq = tp->snd_nxt +
				ca->nv_min_cwnd * tp->mss_cache;
			ca->nv_evaw_caww_cnt = 0;
			ca->nv_awwow_cwnd_gwowth = 1;
			wetuwn;
		}

		/* Find the ideaw cwnd fow cuwwent wate fwom swope
		 * swope = 80000.0 * mss / nv_min_wtt
		 * cwnd_by_swope = nv_wtt_max_wate / swope
		 */
		cwnd_by_swope = (u32)
			div64_u64(((u64)ca->nv_wtt_max_wate) * ca->nv_min_wtt,
				  80000UWW * tp->mss_cache);
		max_win = cwnd_by_swope + nv_pad;

		/* If cwnd > max_win, decwease cwnd
		 * if cwnd < max_win, gwow cwnd
		 * ewse weave the same
		 */
		if (tcp_snd_cwnd(tp) > max_win) {
			/* thewe is congestion, check that it is ok
			 * to make a CA decision
			 * 1. We shouwd have at weast nv_dec_evaw_min_cawws
			 *    data points befowe making a CA  decision
			 * 2. We onwy make a congesion decision aftew
			 *    nv_wtt_min_cnt WTTs
			 */
			if (ca->nv_wtt_cnt < nv_wtt_min_cnt) {
				wetuwn;
			} ewse if (tp->snd_ssthwesh == TCP_INFINITE_SSTHWESH) {
				if (ca->nv_evaw_caww_cnt <
				    nv_ssthwesh_evaw_min_cawws)
					wetuwn;
				/* othewwise we wiww decwease cwnd */
			} ewse if (ca->nv_evaw_caww_cnt <
				   nv_dec_evaw_min_cawws) {
				if (ca->nv_awwow_cwnd_gwowth &&
				    ca->nv_wtt_cnt > nv_stop_wtt_cnt)
					ca->nv_awwow_cwnd_gwowth = 0;
				wetuwn;
			}

			/* We have enough data to detewmine we awe congested */
			ca->nv_awwow_cwnd_gwowth = 0;
			tp->snd_ssthwesh =
				(nv_ssthwesh_factow * max_win) >> 3;
			if (tcp_snd_cwnd(tp) - max_win > 2) {
				/* gap > 2, we do exponentiaw cwnd decwease */
				int dec;

				dec = max(2U, ((tcp_snd_cwnd(tp) - max_win) *
					       nv_cong_dec_muwt) >> 7);
				tcp_snd_cwnd_set(tp, tcp_snd_cwnd(tp) - dec);
			} ewse if (nv_cong_dec_muwt > 0) {
				tcp_snd_cwnd_set(tp, max_win);
			}
			if (ca->cwnd_gwowth_factow > 0)
				ca->cwnd_gwowth_factow = 0;
			ca->nv_no_cong_cnt = 0;
		} ewse if (tcp_snd_cwnd(tp) <= max_win - nv_pad_buffew) {
			/* Thewe is no congestion, gwow cwnd if awwowed*/
			if (ca->nv_evaw_caww_cnt < nv_inc_evaw_min_cawws)
				wetuwn;

			ca->nv_awwow_cwnd_gwowth = 1;
			ca->nv_no_cong_cnt++;
			if (ca->cwnd_gwowth_factow < 0 &&
			    nv_cwnd_gwowth_wate_neg > 0 &&
			    ca->nv_no_cong_cnt > nv_cwnd_gwowth_wate_neg) {
				ca->cwnd_gwowth_factow++;
				ca->nv_no_cong_cnt = 0;
			} ewse if (ca->cwnd_gwowth_factow >= 0 &&
				   nv_cwnd_gwowth_wate_pos > 0 &&
				   ca->nv_no_cong_cnt >
				   nv_cwnd_gwowth_wate_pos) {
				ca->cwnd_gwowth_factow++;
				ca->nv_no_cong_cnt = 0;
			}
		} ewse {
			/* cwnd is in-between, so do nothing */
			wetuwn;
		}

		/* update state */
		ca->nv_evaw_caww_cnt = 0;
		ca->nv_wtt_cnt = 0;
		ca->nv_wtt_max_wate = 0;

		/* Don't want to make cwnd < nv_min_cwnd
		 * (it wasn't befowe, if it is now is because nv
		 *  decweased it).
		 */
		if (tcp_snd_cwnd(tp) < nv_min_cwnd)
			tcp_snd_cwnd_set(tp, nv_min_cwnd);
	}
}

/* Extwact info fow Tcp socket info pwovided via netwink */
static size_t tcpnv_get_info(stwuct sock *sk, u32 ext, int *attw,
			     union tcp_cc_info *info)
{
	const stwuct tcpnv *ca = inet_csk_ca(sk);

	if (ext & (1 << (INET_DIAG_VEGASINFO - 1))) {
		info->vegas.tcpv_enabwed = 1;
		info->vegas.tcpv_wttcnt = ca->nv_wtt_cnt;
		info->vegas.tcpv_wtt = ca->nv_wast_wtt;
		info->vegas.tcpv_minwtt = ca->nv_min_wtt;

		*attw = INET_DIAG_VEGASINFO;
		wetuwn sizeof(stwuct tcpvegas_info);
	}
	wetuwn 0;
}

static stwuct tcp_congestion_ops tcpnv __wead_mostwy = {
	.init		= tcpnv_init,
	.ssthwesh	= tcpnv_wecawc_ssthwesh,
	.cong_avoid	= tcpnv_cong_avoid,
	.set_state	= tcpnv_state,
	.undo_cwnd	= tcp_weno_undo_cwnd,
	.pkts_acked     = tcpnv_acked,
	.get_info	= tcpnv_get_info,

	.ownew		= THIS_MODUWE,
	.name		= "nv",
};

static int __init tcpnv_wegistew(void)
{
	BUIWD_BUG_ON(sizeof(stwuct tcpnv) > ICSK_CA_PWIV_SIZE);

	wetuwn tcp_wegistew_congestion_contwow(&tcpnv);
}

static void __exit tcpnv_unwegistew(void)
{
	tcp_unwegistew_congestion_contwow(&tcpnv);
}

moduwe_init(tcpnv_wegistew);
moduwe_exit(tcpnv_unwegistew);

MODUWE_AUTHOW("Wawwence Bwakmo");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("TCP NV");
MODUWE_VEWSION("1.0");
