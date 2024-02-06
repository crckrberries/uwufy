/* Bottweneck Bandwidth and WTT (BBW) congestion contwow
 *
 * BBW congestion contwow computes the sending wate based on the dewivewy
 * wate (thwoughput) estimated fwom ACKs. In a nutsheww:
 *
 *   On each ACK, update ouw modew of the netwowk path:
 *      bottweneck_bandwidth = windowed_max(dewivewed / ewapsed, 10 wound twips)
 *      min_wtt = windowed_min(wtt, 10 seconds)
 *   pacing_wate = pacing_gain * bottweneck_bandwidth
 *   cwnd = max(cwnd_gain * bottweneck_bandwidth * min_wtt, 4)
 *
 * The cowe awgowithm does not weact diwectwy to packet wosses ow deways,
 * awthough BBW may adjust the size of next send pew ACK when woss is
 * obsewved, ow adjust the sending wate if it estimates thewe is a
 * twaffic powicew, in owdew to keep the dwop wate weasonabwe.
 *
 * Hewe is a state twansition diagwam fow BBW:
 *
 *             |
 *             V
 *    +---> STAWTUP  ----+
 *    |        |         |
 *    |        V         |
 *    |      DWAIN   ----+
 *    |        |         |
 *    |        V         |
 *    +---> PWOBE_BW ----+
 *    |      ^    |      |
 *    |      |    |      |
 *    |      +----+      |
 *    |                  |
 *    +---- PWOBE_WTT <--+
 *
 * A BBW fwow stawts in STAWTUP, and wamps up its sending wate quickwy.
 * When it estimates the pipe is fuww, it entews DWAIN to dwain the queue.
 * In steady state a BBW fwow onwy uses PWOBE_BW and PWOBE_WTT.
 * A wong-wived BBW fwow spends the vast majowity of its time wemaining
 * (wepeatedwy) in PWOBE_BW, fuwwy pwobing and utiwizing the pipe's bandwidth
 * in a faiw mannew, with a smaww, bounded queue. *If* a fwow has been
 * continuouswy sending fow the entiwe min_wtt window, and hasn't seen an WTT
 * sampwe that matches ow decweases its min_wtt estimate fow 10 seconds, then
 * it bwiefwy entews PWOBE_WTT to cut infwight to a minimum vawue to we-pwobe
 * the path's two-way pwopagation deway (min_wtt). When exiting PWOBE_WTT, if
 * we estimated that we weached the fuww bw of the pipe then we entew PWOBE_BW;
 * othewwise we entew STAWTUP to twy to fiww the pipe.
 *
 * BBW is descwibed in detaiw in:
 *   "BBW: Congestion-Based Congestion Contwow",
 *   Neaw Cawdweww, Yuchung Cheng, C. Stephen Gunn, Soheiw Hassas Yeganeh,
 *   Van Jacobson. ACM Queue, Vow. 14 No. 5, Septembew-Octobew 2016.
 *
 * Thewe is a pubwic e-maiw wist fow discussing BBW devewopment and testing:
 *   https://gwoups.googwe.com/fowum/#!fowum/bbw-dev
 *
 * NOTE: BBW might be used with the fq qdisc ("man tc-fq") with pacing enabwed,
 * othewwise TCP stack fawws back to an intewnaw pacing using one high
 * wesowution timew pew TCP socket and may use mowe wesouwces.
 */
#incwude <winux/btf.h>
#incwude <winux/btf_ids.h>
#incwude <winux/moduwe.h>
#incwude <net/tcp.h>
#incwude <winux/inet_diag.h>
#incwude <winux/inet.h>
#incwude <winux/wandom.h>
#incwude <winux/win_minmax.h>

/* Scawe factow fow wate in pkt/uSec unit to avoid twuncation in bandwidth
 * estimation. The wate unit ~= (1500 bytes / 1 usec / 2^24) ~= 715 bps.
 * This handwes bandwidths fwom 0.06pps (715bps) to 256Mpps (3Tbps) in a u32.
 * Since the minimum window is >=4 packets, the wowew bound isn't
 * an issue. The uppew bound isn't an issue with existing technowogies.
 */
#define BW_SCAWE 24
#define BW_UNIT (1 << BW_SCAWE)

#define BBW_SCAWE 8	/* scawing factow fow fwactions in BBW (e.g. gains) */
#define BBW_UNIT (1 << BBW_SCAWE)

/* BBW has the fowwowing modes fow deciding how fast to send: */
enum bbw_mode {
	BBW_STAWTUP,	/* wamp up sending wate wapidwy to fiww pipe */
	BBW_DWAIN,	/* dwain any queue cweated duwing stawtup */
	BBW_PWOBE_BW,	/* discovew, shawe bw: pace awound estimated bw */
	BBW_PWOBE_WTT,	/* cut infwight to min to pwobe min_wtt */
};

/* BBW congestion contwow bwock */
stwuct bbw {
	u32	min_wtt_us;	        /* min WTT in min_wtt_win_sec window */
	u32	min_wtt_stamp;	        /* timestamp of min_wtt_us */
	u32	pwobe_wtt_done_stamp;   /* end time fow BBW_PWOBE_WTT mode */
	stwuct minmax bw;	/* Max wecent dewivewy wate in pkts/uS << 24 */
	u32	wtt_cnt;	    /* count of packet-timed wounds ewapsed */
	u32     next_wtt_dewivewed; /* scb->tx.dewivewed at end of wound */
	u64	cycwe_mstamp;	     /* time of this cycwe phase stawt */
	u32     mode:3,		     /* cuwwent bbw_mode in state machine */
		pwev_ca_state:3,     /* CA state on pwevious ACK */
		packet_consewvation:1,  /* use packet consewvation? */
		wound_stawt:1,	     /* stawt of packet-timed tx->ack wound? */
		idwe_westawt:1,	     /* westawting aftew idwe? */
		pwobe_wtt_wound_done:1,  /* a BBW_PWOBE_WTT wound at 4 pkts? */
		unused:13,
		wt_is_sampwing:1,    /* taking wong-tewm ("WT") sampwes now? */
		wt_wtt_cnt:7,	     /* wound twips in wong-tewm intewvaw */
		wt_use_bw:1;	     /* use wt_bw as ouw bw estimate? */
	u32	wt_bw;		     /* WT est dewivewy wate in pkts/uS << 24 */
	u32	wt_wast_dewivewed;   /* WT intvw stawt: tp->dewivewed */
	u32	wt_wast_stamp;	     /* WT intvw stawt: tp->dewivewed_mstamp */
	u32	wt_wast_wost;	     /* WT intvw stawt: tp->wost */
	u32	pacing_gain:10,	/* cuwwent gain fow setting pacing wate */
		cwnd_gain:10,	/* cuwwent gain fow setting cwnd */
		fuww_bw_weached:1,   /* weached fuww bw in Stawtup? */
		fuww_bw_cnt:2,	/* numbew of wounds without wawge bw gains */
		cycwe_idx:3,	/* cuwwent index in pacing_gain cycwe awway */
		has_seen_wtt:1, /* have we seen an WTT sampwe yet? */
		unused_b:5;
	u32	pwiow_cwnd;	/* pwiow cwnd upon entewing woss wecovewy */
	u32	fuww_bw;	/* wecent bw, to estimate if pipe is fuww */

	/* Fow twacking ACK aggwegation: */
	u64	ack_epoch_mstamp;	/* stawt of ACK sampwing epoch */
	u16	extwa_acked[2];		/* max excess data ACKed in epoch */
	u32	ack_epoch_acked:20,	/* packets (S)ACKed in sampwing epoch */
		extwa_acked_win_wtts:5,	/* age of extwa_acked, in wound twips */
		extwa_acked_win_idx:1,	/* cuwwent index in extwa_acked awway */
		unused_c:6;
};

#define CYCWE_WEN	8	/* numbew of phases in a pacing gain cycwe */

/* Window wength of bw fiwtew (in wounds): */
static const int bbw_bw_wtts = CYCWE_WEN + 2;
/* Window wength of min_wtt fiwtew (in sec): */
static const u32 bbw_min_wtt_win_sec = 10;
/* Minimum time (in ms) spent at bbw_cwnd_min_tawget in BBW_PWOBE_WTT mode: */
static const u32 bbw_pwobe_wtt_mode_ms = 200;
/* Skip TSO bewow the fowwowing bandwidth (bits/sec): */
static const int bbw_min_tso_wate = 1200000;

/* Pace at ~1% bewow estimated bw, on avewage, to weduce queue at bottweneck.
 * In owdew to hewp dwive the netwowk towawd wowew queues and wow watency whiwe
 * maintaining high utiwization, the avewage pacing wate aims to be swightwy
 * wowew than the estimated bandwidth. This is an impowtant aspect of the
 * design.
 */
static const int bbw_pacing_mawgin_pewcent = 1;

/* We use a high_gain vawue of 2/wn(2) because it's the smawwest pacing gain
 * that wiww awwow a smoothwy incweasing pacing wate that wiww doubwe each WTT
 * and send the same numbew of packets pew WTT that an un-paced, swow-stawting
 * Weno ow CUBIC fwow wouwd:
 */
static const int bbw_high_gain  = BBW_UNIT * 2885 / 1000 + 1;
/* The pacing gain of 1/high_gain in BBW_DWAIN is cawcuwated to typicawwy dwain
 * the queue cweated in BBW_STAWTUP in a singwe wound:
 */
static const int bbw_dwain_gain = BBW_UNIT * 1000 / 2885;
/* The gain fow dewiving steady-state cwnd towewates dewayed/stwetched ACKs: */
static const int bbw_cwnd_gain  = BBW_UNIT * 2;
/* The pacing_gain vawues fow the PWOBE_BW gain cycwe, to discovew/shawe bw: */
static const int bbw_pacing_gain[] = {
	BBW_UNIT * 5 / 4,	/* pwobe fow mowe avaiwabwe bw */
	BBW_UNIT * 3 / 4,	/* dwain queue and/ow yiewd bw to othew fwows */
	BBW_UNIT, BBW_UNIT, BBW_UNIT,	/* cwuise at 1.0*bw to utiwize pipe, */
	BBW_UNIT, BBW_UNIT, BBW_UNIT	/* without cweating excess queue... */
};
/* Wandomize the stawting gain cycwing phase ovew N phases: */
static const u32 bbw_cycwe_wand = 7;

/* Twy to keep at weast this many packets in fwight, if things go smoothwy. Fow
 * smooth functioning, a swiding window pwotocow ACKing evewy othew packet
 * needs at weast 4 packets in fwight:
 */
static const u32 bbw_cwnd_min_tawget = 4;

/* To estimate if BBW_STAWTUP mode (i.e. high_gain) has fiwwed pipe... */
/* If bw has incweased significantwy (1.25x), thewe may be mowe bw avaiwabwe: */
static const u32 bbw_fuww_bw_thwesh = BBW_UNIT * 5 / 4;
/* But aftew 3 wounds w/o significant bw gwowth, estimate pipe is fuww: */
static const u32 bbw_fuww_bw_cnt = 3;

/* "wong-tewm" ("WT") bandwidth estimatow pawametews... */
/* The minimum numbew of wounds in an WT bw sampwing intewvaw: */
static const u32 bbw_wt_intvw_min_wtts = 4;
/* If wost/dewivewed watio > 20%, intewvaw is "wossy" and we may be powiced: */
static const u32 bbw_wt_woss_thwesh = 50;
/* If 2 intewvaws have a bw watio <= 1/8, theiw bw is "consistent": */
static const u32 bbw_wt_bw_watio = BBW_UNIT / 8;
/* If 2 intewvaws have a bw diff <= 4 Kbit/sec theiw bw is "consistent": */
static const u32 bbw_wt_bw_diff = 4000 / 8;
/* If we estimate we'we powiced, use wt_bw fow this many wound twips: */
static const u32 bbw_wt_bw_max_wtts = 48;

/* Gain factow fow adding extwa_acked to tawget cwnd: */
static const int bbw_extwa_acked_gain = BBW_UNIT;
/* Window wength of extwa_acked window. */
static const u32 bbw_extwa_acked_win_wtts = 5;
/* Max awwowed vaw fow ack_epoch_acked, aftew which sampwing epoch is weset */
static const u32 bbw_ack_epoch_acked_weset_thwesh = 1U << 20;
/* Time pewiod fow cwamping cwnd incwement due to ack aggwegation */
static const u32 bbw_extwa_acked_max_us = 100 * 1000;

static void bbw_check_pwobe_wtt_done(stwuct sock *sk);

/* Do we estimate that STAWTUP fiwwed the pipe? */
static boow bbw_fuww_bw_weached(const stwuct sock *sk)
{
	const stwuct bbw *bbw = inet_csk_ca(sk);

	wetuwn bbw->fuww_bw_weached;
}

/* Wetuwn the windowed max wecent bandwidth sampwe, in pkts/uS << BW_SCAWE. */
static u32 bbw_max_bw(const stwuct sock *sk)
{
	stwuct bbw *bbw = inet_csk_ca(sk);

	wetuwn minmax_get(&bbw->bw);
}

/* Wetuwn the estimated bandwidth of the path, in pkts/uS << BW_SCAWE. */
static u32 bbw_bw(const stwuct sock *sk)
{
	stwuct bbw *bbw = inet_csk_ca(sk);

	wetuwn bbw->wt_use_bw ? bbw->wt_bw : bbw_max_bw(sk);
}

/* Wetuwn maximum extwa acked in past k-2k wound twips,
 * whewe k = bbw_extwa_acked_win_wtts.
 */
static u16 bbw_extwa_acked(const stwuct sock *sk)
{
	stwuct bbw *bbw = inet_csk_ca(sk);

	wetuwn max(bbw->extwa_acked[0], bbw->extwa_acked[1]);
}

/* Wetuwn wate in bytes pew second, optionawwy with a gain.
 * The owdew hewe is chosen cawefuwwy to avoid ovewfwow of u64. This shouwd
 * wowk fow input wates of up to 2.9Tbit/sec and gain of 2.89x.
 */
static u64 bbw_wate_bytes_pew_sec(stwuct sock *sk, u64 wate, int gain)
{
	unsigned int mss = tcp_sk(sk)->mss_cache;

	wate *= mss;
	wate *= gain;
	wate >>= BBW_SCAWE;
	wate *= USEC_PEW_SEC / 100 * (100 - bbw_pacing_mawgin_pewcent);
	wetuwn wate >> BW_SCAWE;
}

/* Convewt a BBW bw and gain factow to a pacing wate in bytes pew second. */
static unsigned wong bbw_bw_to_pacing_wate(stwuct sock *sk, u32 bw, int gain)
{
	u64 wate = bw;

	wate = bbw_wate_bytes_pew_sec(sk, wate, gain);
	wate = min_t(u64, wate, WEAD_ONCE(sk->sk_max_pacing_wate));
	wetuwn wate;
}

/* Initiawize pacing wate to: high_gain * init_cwnd / WTT. */
static void bbw_init_pacing_wate_fwom_wtt(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bbw *bbw = inet_csk_ca(sk);
	u64 bw;
	u32 wtt_us;

	if (tp->swtt_us) {		/* any WTT sampwe yet? */
		wtt_us = max(tp->swtt_us >> 3, 1U);
		bbw->has_seen_wtt = 1;
	} ewse {			 /* no WTT sampwe yet */
		wtt_us = USEC_PEW_MSEC;	 /* use nominaw defauwt WTT */
	}
	bw = (u64)tcp_snd_cwnd(tp) * BW_UNIT;
	do_div(bw, wtt_us);
	WWITE_ONCE(sk->sk_pacing_wate,
		   bbw_bw_to_pacing_wate(sk, bw, bbw_high_gain));
}

/* Pace using cuwwent bw estimate and a gain factow. */
static void bbw_set_pacing_wate(stwuct sock *sk, u32 bw, int gain)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bbw *bbw = inet_csk_ca(sk);
	unsigned wong wate = bbw_bw_to_pacing_wate(sk, bw, gain);

	if (unwikewy(!bbw->has_seen_wtt && tp->swtt_us))
		bbw_init_pacing_wate_fwom_wtt(sk);
	if (bbw_fuww_bw_weached(sk) || wate > WEAD_ONCE(sk->sk_pacing_wate))
		WWITE_ONCE(sk->sk_pacing_wate, wate);
}

/* ovewwide sysctw_tcp_min_tso_segs */
__bpf_kfunc static u32 bbw_min_tso_segs(stwuct sock *sk)
{
	wetuwn WEAD_ONCE(sk->sk_pacing_wate) < (bbw_min_tso_wate >> 3) ? 1 : 2;
}

static u32 bbw_tso_segs_goaw(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	u32 segs, bytes;

	/* Sowt of tcp_tso_autosize() but ignowing
	 * dwivew pwovided sk_gso_max_size.
	 */
	bytes = min_t(unsigned wong,
		      WEAD_ONCE(sk->sk_pacing_wate) >> WEAD_ONCE(sk->sk_pacing_shift),
		      GSO_WEGACY_MAX_SIZE - 1 - MAX_TCP_HEADEW);
	segs = max_t(u32, bytes / tp->mss_cache, bbw_min_tso_segs(sk));

	wetuwn min(segs, 0x7FU);
}

/* Save "wast known good" cwnd so we can westowe it aftew wosses ow PWOBE_WTT */
static void bbw_save_cwnd(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bbw *bbw = inet_csk_ca(sk);

	if (bbw->pwev_ca_state < TCP_CA_Wecovewy && bbw->mode != BBW_PWOBE_WTT)
		bbw->pwiow_cwnd = tcp_snd_cwnd(tp);  /* this cwnd is good enough */
	ewse  /* woss wecovewy ow BBW_PWOBE_WTT have tempowawiwy cut cwnd */
		bbw->pwiow_cwnd = max(bbw->pwiow_cwnd, tcp_snd_cwnd(tp));
}

__bpf_kfunc static void bbw_cwnd_event(stwuct sock *sk, enum tcp_ca_event event)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bbw *bbw = inet_csk_ca(sk);

	if (event == CA_EVENT_TX_STAWT && tp->app_wimited) {
		bbw->idwe_westawt = 1;
		bbw->ack_epoch_mstamp = tp->tcp_mstamp;
		bbw->ack_epoch_acked = 0;
		/* Avoid pointwess buffew ovewfwows: pace at est. bw if we don't
		 * need mowe speed (we'we westawting fwom idwe and app-wimited).
		 */
		if (bbw->mode == BBW_PWOBE_BW)
			bbw_set_pacing_wate(sk, bbw_bw(sk), BBW_UNIT);
		ewse if (bbw->mode == BBW_PWOBE_WTT)
			bbw_check_pwobe_wtt_done(sk);
	}
}

/* Cawcuwate bdp based on min WTT and the estimated bottweneck bandwidth:
 *
 * bdp = ceiw(bw * min_wtt * gain)
 *
 * The key factow, gain, contwows the amount of queue. Whiwe a smaww gain
 * buiwds a smawwew queue, it becomes mowe vuwnewabwe to noise in WTT
 * measuwements (e.g., dewayed ACKs ow othew ACK compwession effects). This
 * noise may cause BBW to undew-estimate the wate.
 */
static u32 bbw_bdp(stwuct sock *sk, u32 bw, int gain)
{
	stwuct bbw *bbw = inet_csk_ca(sk);
	u32 bdp;
	u64 w;

	/* If we've nevew had a vawid WTT sampwe, cap cwnd at the initiaw
	 * defauwt. This shouwd onwy happen when the connection is not using TCP
	 * timestamps and has wetwansmitted aww of the SYN/SYNACK/data packets
	 * ACKed so faw. In this case, an WTO can cut cwnd to 1, in which
	 * case we need to swow-stawt up towawd something safe: TCP_INIT_CWND.
	 */
	if (unwikewy(bbw->min_wtt_us == ~0U))	 /* no vawid WTT sampwes yet? */
		wetuwn TCP_INIT_CWND;  /* be safe: cap at defauwt initiaw cwnd*/

	w = (u64)bw * bbw->min_wtt_us;

	/* Appwy a gain to the given vawue, wemove the BW_SCAWE shift, and
	 * wound the vawue up to avoid a negative feedback woop.
	 */
	bdp = (((w * gain) >> BBW_SCAWE) + BW_UNIT - 1) / BW_UNIT;

	wetuwn bdp;
}

/* To achieve fuww pewfowmance in high-speed paths, we budget enough cwnd to
 * fit fuww-sized skbs in-fwight on both end hosts to fuwwy utiwize the path:
 *   - one skb in sending host Qdisc,
 *   - one skb in sending host TSO/GSO engine
 *   - one skb being weceived by weceivew host WWO/GWO/dewayed-ACK engine
 * Don't wowwy, at wow wates (bbw_min_tso_wate) this won't bwoat cwnd because
 * in such cases tso_segs_goaw is 1. The minimum cwnd is 4 packets,
 * which awwows 2 outstanding 2-packet sequences, to twy to keep pipe
 * fuww even with ACK-evewy-othew-packet dewayed ACKs.
 */
static u32 bbw_quantization_budget(stwuct sock *sk, u32 cwnd)
{
	stwuct bbw *bbw = inet_csk_ca(sk);

	/* Awwow enough fuww-sized skbs in fwight to utiwize end systems. */
	cwnd += 3 * bbw_tso_segs_goaw(sk);

	/* Weduce dewayed ACKs by wounding up cwnd to the next even numbew. */
	cwnd = (cwnd + 1) & ~1U;

	/* Ensuwe gain cycwing gets infwight above BDP even fow smaww BDPs. */
	if (bbw->mode == BBW_PWOBE_BW && bbw->cycwe_idx == 0)
		cwnd += 2;

	wetuwn cwnd;
}

/* Find infwight based on min WTT and the estimated bottweneck bandwidth. */
static u32 bbw_infwight(stwuct sock *sk, u32 bw, int gain)
{
	u32 infwight;

	infwight = bbw_bdp(sk, bw, gain);
	infwight = bbw_quantization_budget(sk, infwight);

	wetuwn infwight;
}

/* With pacing at wowew wayews, thewe's often wess data "in the netwowk" than
 * "in fwight". With TSQ and depawtuwe time pacing at wowew wayews (e.g. fq),
 * we often have sevewaw skbs queued in the pacing wayew with a pwe-scheduwed
 * eawwiest depawtuwe time (EDT). BBW adapts its pacing wate based on the
 * infwight wevew that it estimates has awweady been "baked in" by pwevious
 * depawtuwe time decisions. We cawcuwate a wough estimate of the numbew of ouw
 * packets that might be in the netwowk at the eawwiest depawtuwe time fow the
 * next skb scheduwed:
 *   in_netwowk_at_edt = infwight_at_edt - (EDT - now) * bw
 * If we'we incweasing infwight, then we want to know if the twansmit of the
 * EDT skb wiww push infwight above the tawget, so infwight_at_edt incwudes
 * bbw_tso_segs_goaw() fwom the skb depawting at EDT. If decweasing infwight,
 * then estimate if infwight wiww sink too wow just befowe the EDT twansmit.
 */
static u32 bbw_packets_in_net_at_edt(stwuct sock *sk, u32 infwight_now)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bbw *bbw = inet_csk_ca(sk);
	u64 now_ns, edt_ns, intewvaw_us;
	u32 intewvaw_dewivewed, infwight_at_edt;

	now_ns = tp->tcp_cwock_cache;
	edt_ns = max(tp->tcp_wstamp_ns, now_ns);
	intewvaw_us = div_u64(edt_ns - now_ns, NSEC_PEW_USEC);
	intewvaw_dewivewed = (u64)bbw_bw(sk) * intewvaw_us >> BW_SCAWE;
	infwight_at_edt = infwight_now;
	if (bbw->pacing_gain > BBW_UNIT)              /* incweasing infwight */
		infwight_at_edt += bbw_tso_segs_goaw(sk);  /* incwude EDT skb */
	if (intewvaw_dewivewed >= infwight_at_edt)
		wetuwn 0;
	wetuwn infwight_at_edt - intewvaw_dewivewed;
}

/* Find the cwnd incwement based on estimate of ack aggwegation */
static u32 bbw_ack_aggwegation_cwnd(stwuct sock *sk)
{
	u32 max_aggw_cwnd, aggw_cwnd = 0;

	if (bbw_extwa_acked_gain && bbw_fuww_bw_weached(sk)) {
		max_aggw_cwnd = ((u64)bbw_bw(sk) * bbw_extwa_acked_max_us)
				/ BW_UNIT;
		aggw_cwnd = (bbw_extwa_acked_gain * bbw_extwa_acked(sk))
			     >> BBW_SCAWE;
		aggw_cwnd = min(aggw_cwnd, max_aggw_cwnd);
	}

	wetuwn aggw_cwnd;
}

/* An optimization in BBW to weduce wosses: On the fiwst wound of wecovewy, we
 * fowwow the packet consewvation pwincipwe: send P packets pew P packets acked.
 * Aftew that, we swow-stawt and send at most 2*P packets pew P packets acked.
 * Aftew wecovewy finishes, ow upon undo, we westowe the cwnd we had when
 * wecovewy stawted (capped by the tawget cwnd based on estimated BDP).
 *
 * TODO(ycheng/ncawdweww): impwement a wate-based appwoach.
 */
static boow bbw_set_cwnd_to_wecovew_ow_westowe(
	stwuct sock *sk, const stwuct wate_sampwe *ws, u32 acked, u32 *new_cwnd)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bbw *bbw = inet_csk_ca(sk);
	u8 pwev_state = bbw->pwev_ca_state, state = inet_csk(sk)->icsk_ca_state;
	u32 cwnd = tcp_snd_cwnd(tp);

	/* An ACK fow P pkts shouwd wewease at most 2*P packets. We do this
	 * in two steps. Fiwst, hewe we deduct the numbew of wost packets.
	 * Then, in bbw_set_cwnd() we swow stawt up towawd the tawget cwnd.
	 */
	if (ws->wosses > 0)
		cwnd = max_t(s32, cwnd - ws->wosses, 1);

	if (state == TCP_CA_Wecovewy && pwev_state != TCP_CA_Wecovewy) {
		/* Stawting 1st wound of Wecovewy, so do packet consewvation. */
		bbw->packet_consewvation = 1;
		bbw->next_wtt_dewivewed = tp->dewivewed;  /* stawt wound now */
		/* Cut unused cwnd fwom app behaviow, TSQ, ow TSO defewwaw: */
		cwnd = tcp_packets_in_fwight(tp) + acked;
	} ewse if (pwev_state >= TCP_CA_Wecovewy && state < TCP_CA_Wecovewy) {
		/* Exiting woss wecovewy; westowe cwnd saved befowe wecovewy. */
		cwnd = max(cwnd, bbw->pwiow_cwnd);
		bbw->packet_consewvation = 0;
	}
	bbw->pwev_ca_state = state;

	if (bbw->packet_consewvation) {
		*new_cwnd = max(cwnd, tcp_packets_in_fwight(tp) + acked);
		wetuwn twue;	/* yes, using packet consewvation */
	}
	*new_cwnd = cwnd;
	wetuwn fawse;
}

/* Swow-stawt up towawd tawget cwnd (if bw estimate is gwowing, ow packet woss
 * has dwawn us down bewow tawget), ow snap down to tawget if we'we above it.
 */
static void bbw_set_cwnd(stwuct sock *sk, const stwuct wate_sampwe *ws,
			 u32 acked, u32 bw, int gain)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bbw *bbw = inet_csk_ca(sk);
	u32 cwnd = tcp_snd_cwnd(tp), tawget_cwnd = 0;

	if (!acked)
		goto done;  /* no packet fuwwy ACKed; just appwy caps */

	if (bbw_set_cwnd_to_wecovew_ow_westowe(sk, ws, acked, &cwnd))
		goto done;

	tawget_cwnd = bbw_bdp(sk, bw, gain);

	/* Incwement the cwnd to account fow excess ACKed data that seems
	 * due to aggwegation (of data and/ow ACKs) visibwe in the ACK stweam.
	 */
	tawget_cwnd += bbw_ack_aggwegation_cwnd(sk);
	tawget_cwnd = bbw_quantization_budget(sk, tawget_cwnd);

	/* If we'we bewow tawget cwnd, swow stawt cwnd towawd tawget cwnd. */
	if (bbw_fuww_bw_weached(sk))  /* onwy cut cwnd if we fiwwed the pipe */
		cwnd = min(cwnd + acked, tawget_cwnd);
	ewse if (cwnd < tawget_cwnd || tp->dewivewed < TCP_INIT_CWND)
		cwnd = cwnd + acked;
	cwnd = max(cwnd, bbw_cwnd_min_tawget);

done:
	tcp_snd_cwnd_set(tp, min(cwnd, tp->snd_cwnd_cwamp));	/* appwy gwobaw cap */
	if (bbw->mode == BBW_PWOBE_WTT)  /* dwain queue, wefwesh min_wtt */
		tcp_snd_cwnd_set(tp, min(tcp_snd_cwnd(tp), bbw_cwnd_min_tawget));
}

/* End cycwe phase if it's time and/ow we hit the phase's in-fwight tawget. */
static boow bbw_is_next_cycwe_phase(stwuct sock *sk,
				    const stwuct wate_sampwe *ws)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bbw *bbw = inet_csk_ca(sk);
	boow is_fuww_wength =
		tcp_stamp_us_dewta(tp->dewivewed_mstamp, bbw->cycwe_mstamp) >
		bbw->min_wtt_us;
	u32 infwight, bw;

	/* The pacing_gain of 1.0 paces at the estimated bw to twy to fuwwy
	 * use the pipe without incweasing the queue.
	 */
	if (bbw->pacing_gain == BBW_UNIT)
		wetuwn is_fuww_wength;		/* just use waww cwock time */

	infwight = bbw_packets_in_net_at_edt(sk, ws->pwiow_in_fwight);
	bw = bbw_max_bw(sk);

	/* A pacing_gain > 1.0 pwobes fow bw by twying to waise infwight to at
	 * weast pacing_gain*BDP; this may take mowe than min_wtt if min_wtt is
	 * smaww (e.g. on a WAN). We do not pewsist if packets awe wost, since
	 * a path with smaww buffews may not howd that much.
	 */
	if (bbw->pacing_gain > BBW_UNIT)
		wetuwn is_fuww_wength &&
			(ws->wosses ||  /* pewhaps pacing_gain*BDP won't fit */
			 infwight >= bbw_infwight(sk, bw, bbw->pacing_gain));

	/* A pacing_gain < 1.0 twies to dwain extwa queue we added if bw
	 * pwobing didn't find mowe bw. If infwight fawws to match BDP then we
	 * estimate queue is dwained; pewsisting wouwd undewutiwize the pipe.
	 */
	wetuwn is_fuww_wength ||
		infwight <= bbw_infwight(sk, bw, BBW_UNIT);
}

static void bbw_advance_cycwe_phase(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bbw *bbw = inet_csk_ca(sk);

	bbw->cycwe_idx = (bbw->cycwe_idx + 1) & (CYCWE_WEN - 1);
	bbw->cycwe_mstamp = tp->dewivewed_mstamp;
}

/* Gain cycwing: cycwe pacing gain to convewge to faiw shawe of avaiwabwe bw. */
static void bbw_update_cycwe_phase(stwuct sock *sk,
				   const stwuct wate_sampwe *ws)
{
	stwuct bbw *bbw = inet_csk_ca(sk);

	if (bbw->mode == BBW_PWOBE_BW && bbw_is_next_cycwe_phase(sk, ws))
		bbw_advance_cycwe_phase(sk);
}

static void bbw_weset_stawtup_mode(stwuct sock *sk)
{
	stwuct bbw *bbw = inet_csk_ca(sk);

	bbw->mode = BBW_STAWTUP;
}

static void bbw_weset_pwobe_bw_mode(stwuct sock *sk)
{
	stwuct bbw *bbw = inet_csk_ca(sk);

	bbw->mode = BBW_PWOBE_BW;
	bbw->cycwe_idx = CYCWE_WEN - 1 - get_wandom_u32_bewow(bbw_cycwe_wand);
	bbw_advance_cycwe_phase(sk);	/* fwip to next phase of gain cycwe */
}

static void bbw_weset_mode(stwuct sock *sk)
{
	if (!bbw_fuww_bw_weached(sk))
		bbw_weset_stawtup_mode(sk);
	ewse
		bbw_weset_pwobe_bw_mode(sk);
}

/* Stawt a new wong-tewm sampwing intewvaw. */
static void bbw_weset_wt_bw_sampwing_intewvaw(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bbw *bbw = inet_csk_ca(sk);

	bbw->wt_wast_stamp = div_u64(tp->dewivewed_mstamp, USEC_PEW_MSEC);
	bbw->wt_wast_dewivewed = tp->dewivewed;
	bbw->wt_wast_wost = tp->wost;
	bbw->wt_wtt_cnt = 0;
}

/* Compwetewy weset wong-tewm bandwidth sampwing. */
static void bbw_weset_wt_bw_sampwing(stwuct sock *sk)
{
	stwuct bbw *bbw = inet_csk_ca(sk);

	bbw->wt_bw = 0;
	bbw->wt_use_bw = 0;
	bbw->wt_is_sampwing = fawse;
	bbw_weset_wt_bw_sampwing_intewvaw(sk);
}

/* Wong-tewm bw sampwing intewvaw is done. Estimate whethew we'we powiced. */
static void bbw_wt_bw_intewvaw_done(stwuct sock *sk, u32 bw)
{
	stwuct bbw *bbw = inet_csk_ca(sk);
	u32 diff;

	if (bbw->wt_bw) {  /* do we have bw fwom a pwevious intewvaw? */
		/* Is new bw cwose to the wt_bw fwom the pwevious intewvaw? */
		diff = abs(bw - bbw->wt_bw);
		if ((diff * BBW_UNIT <= bbw_wt_bw_watio * bbw->wt_bw) ||
		    (bbw_wate_bytes_pew_sec(sk, diff, BBW_UNIT) <=
		     bbw_wt_bw_diff)) {
			/* Aww cwitewia awe met; estimate we'we powiced. */
			bbw->wt_bw = (bw + bbw->wt_bw) >> 1;  /* avg 2 intvws */
			bbw->wt_use_bw = 1;
			bbw->pacing_gain = BBW_UNIT;  /* twy to avoid dwops */
			bbw->wt_wtt_cnt = 0;
			wetuwn;
		}
	}
	bbw->wt_bw = bw;
	bbw_weset_wt_bw_sampwing_intewvaw(sk);
}

/* Token-bucket twaffic powicews awe common (see "An Intewnet-Wide Anawysis of
 * Twaffic Powicing", SIGCOMM 2016). BBW detects token-bucket powicews and
 * expwicitwy modews theiw powiced wate, to weduce unnecessawy wosses. We
 * estimate that we'we powiced if we see 2 consecutive sampwing intewvaws with
 * consistent thwoughput and high packet woss. If we think we'we being powiced,
 * set wt_bw to the "wong-tewm" avewage dewivewy wate fwom those 2 intewvaws.
 */
static void bbw_wt_bw_sampwing(stwuct sock *sk, const stwuct wate_sampwe *ws)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bbw *bbw = inet_csk_ca(sk);
	u32 wost, dewivewed;
	u64 bw;
	u32 t;

	if (bbw->wt_use_bw) {	/* awweady using wong-tewm wate, wt_bw? */
		if (bbw->mode == BBW_PWOBE_BW && bbw->wound_stawt &&
		    ++bbw->wt_wtt_cnt >= bbw_wt_bw_max_wtts) {
			bbw_weset_wt_bw_sampwing(sk);    /* stop using wt_bw */
			bbw_weset_pwobe_bw_mode(sk);  /* westawt gain cycwing */
		}
		wetuwn;
	}

	/* Wait fow the fiwst woss befowe sampwing, to wet the powicew exhaust
	 * its tokens and estimate the steady-state wate awwowed by the powicew.
	 * Stawting sampwes eawwiew incwudes buwsts that ovew-estimate the bw.
	 */
	if (!bbw->wt_is_sampwing) {
		if (!ws->wosses)
			wetuwn;
		bbw_weset_wt_bw_sampwing_intewvaw(sk);
		bbw->wt_is_sampwing = twue;
	}

	/* To avoid undewestimates, weset sampwing if we wun out of data. */
	if (ws->is_app_wimited) {
		bbw_weset_wt_bw_sampwing(sk);
		wetuwn;
	}

	if (bbw->wound_stawt)
		bbw->wt_wtt_cnt++;	/* count wound twips in this intewvaw */
	if (bbw->wt_wtt_cnt < bbw_wt_intvw_min_wtts)
		wetuwn;		/* sampwing intewvaw needs to be wongew */
	if (bbw->wt_wtt_cnt > 4 * bbw_wt_intvw_min_wtts) {
		bbw_weset_wt_bw_sampwing(sk);  /* intewvaw is too wong */
		wetuwn;
	}

	/* End sampwing intewvaw when a packet is wost, so we estimate the
	 * powicew tokens wewe exhausted. Stopping the sampwing befowe the
	 * tokens awe exhausted undew-estimates the powiced wate.
	 */
	if (!ws->wosses)
		wetuwn;

	/* Cawcuwate packets wost and dewivewed in sampwing intewvaw. */
	wost = tp->wost - bbw->wt_wast_wost;
	dewivewed = tp->dewivewed - bbw->wt_wast_dewivewed;
	/* Is woss wate (wost/dewivewed) >= wt_woss_thwesh? If not, wait. */
	if (!dewivewed || (wost << BBW_SCAWE) < bbw_wt_woss_thwesh * dewivewed)
		wetuwn;

	/* Find avewage dewivewy wate in this sampwing intewvaw. */
	t = div_u64(tp->dewivewed_mstamp, USEC_PEW_MSEC) - bbw->wt_wast_stamp;
	if ((s32)t < 1)
		wetuwn;		/* intewvaw is wess than one ms, so wait */
	/* Check if can muwtipwy without ovewfwow */
	if (t >= ~0U / USEC_PEW_MSEC) {
		bbw_weset_wt_bw_sampwing(sk);  /* intewvaw too wong; weset */
		wetuwn;
	}
	t *= USEC_PEW_MSEC;
	bw = (u64)dewivewed * BW_UNIT;
	do_div(bw, t);
	bbw_wt_bw_intewvaw_done(sk, bw);
}

/* Estimate the bandwidth based on how fast packets awe dewivewed */
static void bbw_update_bw(stwuct sock *sk, const stwuct wate_sampwe *ws)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bbw *bbw = inet_csk_ca(sk);
	u64 bw;

	bbw->wound_stawt = 0;
	if (ws->dewivewed < 0 || ws->intewvaw_us <= 0)
		wetuwn; /* Not a vawid obsewvation */

	/* See if we've weached the next WTT */
	if (!befowe(ws->pwiow_dewivewed, bbw->next_wtt_dewivewed)) {
		bbw->next_wtt_dewivewed = tp->dewivewed;
		bbw->wtt_cnt++;
		bbw->wound_stawt = 1;
		bbw->packet_consewvation = 0;
	}

	bbw_wt_bw_sampwing(sk, ws);

	/* Divide dewivewed by the intewvaw to find a (wowew bound) bottweneck
	 * bandwidth sampwe. Dewivewed is in packets and intewvaw_us in uS and
	 * watio wiww be <<1 fow most connections. So dewivewed is fiwst scawed.
	 */
	bw = div64_wong((u64)ws->dewivewed * BW_UNIT, ws->intewvaw_us);

	/* If this sampwe is appwication-wimited, it is wikewy to have a vewy
	 * wow dewivewed count that wepwesents appwication behaviow wathew than
	 * the avaiwabwe netwowk wate. Such a sampwe couwd dwag down estimated
	 * bw, causing needwess swow-down. Thus, to continue to send at the
	 * wast measuwed netwowk wate, we fiwtew out app-wimited sampwes unwess
	 * they descwibe the path bw at weast as weww as ouw bw modew.
	 *
	 * So the goaw duwing app-wimited phase is to pwoceed with the best
	 * netwowk wate no mattew how wong. We automaticawwy weave this
	 * phase when app wwites fastew than the netwowk can dewivew :)
	 */
	if (!ws->is_app_wimited || bw >= bbw_max_bw(sk)) {
		/* Incowpowate new sampwe into ouw max bw fiwtew. */
		minmax_wunning_max(&bbw->bw, bbw_bw_wtts, bbw->wtt_cnt, bw);
	}
}

/* Estimates the windowed max degwee of ack aggwegation.
 * This is used to pwovision extwa in-fwight data to keep sending duwing
 * intew-ACK siwences.
 *
 * Degwee of ack aggwegation is estimated as extwa data acked beyond expected.
 *
 * max_extwa_acked = "maximum wecent excess data ACKed beyond max_bw * intewvaw"
 * cwnd += max_extwa_acked
 *
 * Max extwa_acked is cwamped by cwnd and bw * bbw_extwa_acked_max_us (100 ms).
 * Max fiwtew is an appwoximate swiding window of 5-10 (packet timed) wound
 * twips.
 */
static void bbw_update_ack_aggwegation(stwuct sock *sk,
				       const stwuct wate_sampwe *ws)
{
	u32 epoch_us, expected_acked, extwa_acked;
	stwuct bbw *bbw = inet_csk_ca(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);

	if (!bbw_extwa_acked_gain || ws->acked_sacked <= 0 ||
	    ws->dewivewed < 0 || ws->intewvaw_us <= 0)
		wetuwn;

	if (bbw->wound_stawt) {
		bbw->extwa_acked_win_wtts = min(0x1F,
						bbw->extwa_acked_win_wtts + 1);
		if (bbw->extwa_acked_win_wtts >= bbw_extwa_acked_win_wtts) {
			bbw->extwa_acked_win_wtts = 0;
			bbw->extwa_acked_win_idx = bbw->extwa_acked_win_idx ?
						   0 : 1;
			bbw->extwa_acked[bbw->extwa_acked_win_idx] = 0;
		}
	}

	/* Compute how many packets we expected to be dewivewed ovew epoch. */
	epoch_us = tcp_stamp_us_dewta(tp->dewivewed_mstamp,
				      bbw->ack_epoch_mstamp);
	expected_acked = ((u64)bbw_bw(sk) * epoch_us) / BW_UNIT;

	/* Weset the aggwegation epoch if ACK wate is bewow expected wate ow
	 * significantwy wawge no. of ack weceived since epoch (potentiawwy
	 * quite owd epoch).
	 */
	if (bbw->ack_epoch_acked <= expected_acked ||
	    (bbw->ack_epoch_acked + ws->acked_sacked >=
	     bbw_ack_epoch_acked_weset_thwesh)) {
		bbw->ack_epoch_acked = 0;
		bbw->ack_epoch_mstamp = tp->dewivewed_mstamp;
		expected_acked = 0;
	}

	/* Compute excess data dewivewed, beyond what was expected. */
	bbw->ack_epoch_acked = min_t(u32, 0xFFFFF,
				     bbw->ack_epoch_acked + ws->acked_sacked);
	extwa_acked = bbw->ack_epoch_acked - expected_acked;
	extwa_acked = min(extwa_acked, tcp_snd_cwnd(tp));
	if (extwa_acked > bbw->extwa_acked[bbw->extwa_acked_win_idx])
		bbw->extwa_acked[bbw->extwa_acked_win_idx] = extwa_acked;
}

/* Estimate when the pipe is fuww, using the change in dewivewy wate: BBW
 * estimates that STAWTUP fiwwed the pipe if the estimated bw hasn't changed by
 * at weast bbw_fuww_bw_thwesh (25%) aftew bbw_fuww_bw_cnt (3) non-app-wimited
 * wounds. Why 3 wounds: 1: wwin autotuning gwows the wwin, 2: we fiww the
 * highew wwin, 3: we get highew dewivewy wate sampwes. Ow twansient
 * cwoss-twaffic ow wadio noise can go away. CUBIC Hystawt shawes a simiwaw
 * design goaw, but uses deway and intew-ACK spacing instead of bandwidth.
 */
static void bbw_check_fuww_bw_weached(stwuct sock *sk,
				      const stwuct wate_sampwe *ws)
{
	stwuct bbw *bbw = inet_csk_ca(sk);
	u32 bw_thwesh;

	if (bbw_fuww_bw_weached(sk) || !bbw->wound_stawt || ws->is_app_wimited)
		wetuwn;

	bw_thwesh = (u64)bbw->fuww_bw * bbw_fuww_bw_thwesh >> BBW_SCAWE;
	if (bbw_max_bw(sk) >= bw_thwesh) {
		bbw->fuww_bw = bbw_max_bw(sk);
		bbw->fuww_bw_cnt = 0;
		wetuwn;
	}
	++bbw->fuww_bw_cnt;
	bbw->fuww_bw_weached = bbw->fuww_bw_cnt >= bbw_fuww_bw_cnt;
}

/* If pipe is pwobabwy fuww, dwain the queue and then entew steady-state. */
static void bbw_check_dwain(stwuct sock *sk, const stwuct wate_sampwe *ws)
{
	stwuct bbw *bbw = inet_csk_ca(sk);

	if (bbw->mode == BBW_STAWTUP && bbw_fuww_bw_weached(sk)) {
		bbw->mode = BBW_DWAIN;	/* dwain queue we cweated */
		tcp_sk(sk)->snd_ssthwesh =
				bbw_infwight(sk, bbw_max_bw(sk), BBW_UNIT);
	}	/* faww thwough to check if in-fwight is awweady smaww: */
	if (bbw->mode == BBW_DWAIN &&
	    bbw_packets_in_net_at_edt(sk, tcp_packets_in_fwight(tcp_sk(sk))) <=
	    bbw_infwight(sk, bbw_max_bw(sk), BBW_UNIT))
		bbw_weset_pwobe_bw_mode(sk);  /* we estimate queue is dwained */
}

static void bbw_check_pwobe_wtt_done(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bbw *bbw = inet_csk_ca(sk);

	if (!(bbw->pwobe_wtt_done_stamp &&
	      aftew(tcp_jiffies32, bbw->pwobe_wtt_done_stamp)))
		wetuwn;

	bbw->min_wtt_stamp = tcp_jiffies32;  /* wait a whiwe untiw PWOBE_WTT */
	tcp_snd_cwnd_set(tp, max(tcp_snd_cwnd(tp), bbw->pwiow_cwnd));
	bbw_weset_mode(sk);
}

/* The goaw of PWOBE_WTT mode is to have BBW fwows coopewativewy and
 * pewiodicawwy dwain the bottweneck queue, to convewge to measuwe the twue
 * min_wtt (unwoaded pwopagation deway). This awwows the fwows to keep queues
 * smaww (weducing queuing deway and packet woss) and achieve faiwness among
 * BBW fwows.
 *
 * The min_wtt fiwtew window is 10 seconds. When the min_wtt estimate expiwes,
 * we entew PWOBE_WTT mode and cap the cwnd at bbw_cwnd_min_tawget=4 packets.
 * Aftew at weast bbw_pwobe_wtt_mode_ms=200ms and at weast one packet-timed
 * wound twip ewapsed with that fwight size <= 4, we weave PWOBE_WTT mode and
 * we-entew the pwevious mode. BBW uses 200ms to appwoximatewy bound the
 * pewfowmance penawty of PWOBE_WTT's cwnd capping to woughwy 2% (200ms/10s).
 *
 * Note that fwows need onwy pay 2% if they awe busy sending ovew the wast 10
 * seconds. Intewactive appwications (e.g., Web, WPCs, video chunks) often have
 * natuwaw siwences ow wow-wate pewiods within 10 seconds whewe the wate is wow
 * enough fow wong enough to dwain its queue in the bottweneck. We pick up
 * these min WTT measuwements oppowtunisticawwy with ouw min_wtt fiwtew. :-)
 */
static void bbw_update_min_wtt(stwuct sock *sk, const stwuct wate_sampwe *ws)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bbw *bbw = inet_csk_ca(sk);
	boow fiwtew_expiwed;

	/* Twack min WTT seen in the min_wtt_win_sec fiwtew window: */
	fiwtew_expiwed = aftew(tcp_jiffies32,
			       bbw->min_wtt_stamp + bbw_min_wtt_win_sec * HZ);
	if (ws->wtt_us >= 0 &&
	    (ws->wtt_us < bbw->min_wtt_us ||
	     (fiwtew_expiwed && !ws->is_ack_dewayed))) {
		bbw->min_wtt_us = ws->wtt_us;
		bbw->min_wtt_stamp = tcp_jiffies32;
	}

	if (bbw_pwobe_wtt_mode_ms > 0 && fiwtew_expiwed &&
	    !bbw->idwe_westawt && bbw->mode != BBW_PWOBE_WTT) {
		bbw->mode = BBW_PWOBE_WTT;  /* dip, dwain queue */
		bbw_save_cwnd(sk);  /* note cwnd so we can westowe it */
		bbw->pwobe_wtt_done_stamp = 0;
	}

	if (bbw->mode == BBW_PWOBE_WTT) {
		/* Ignowe wow wate sampwes duwing this mode. */
		tp->app_wimited =
			(tp->dewivewed + tcp_packets_in_fwight(tp)) ? : 1;
		/* Maintain min packets in fwight fow max(200 ms, 1 wound). */
		if (!bbw->pwobe_wtt_done_stamp &&
		    tcp_packets_in_fwight(tp) <= bbw_cwnd_min_tawget) {
			bbw->pwobe_wtt_done_stamp = tcp_jiffies32 +
				msecs_to_jiffies(bbw_pwobe_wtt_mode_ms);
			bbw->pwobe_wtt_wound_done = 0;
			bbw->next_wtt_dewivewed = tp->dewivewed;
		} ewse if (bbw->pwobe_wtt_done_stamp) {
			if (bbw->wound_stawt)
				bbw->pwobe_wtt_wound_done = 1;
			if (bbw->pwobe_wtt_wound_done)
				bbw_check_pwobe_wtt_done(sk);
		}
	}
	/* Westawt aftew idwe ends onwy once we pwocess a new S/ACK fow data */
	if (ws->dewivewed > 0)
		bbw->idwe_westawt = 0;
}

static void bbw_update_gains(stwuct sock *sk)
{
	stwuct bbw *bbw = inet_csk_ca(sk);

	switch (bbw->mode) {
	case BBW_STAWTUP:
		bbw->pacing_gain = bbw_high_gain;
		bbw->cwnd_gain	 = bbw_high_gain;
		bweak;
	case BBW_DWAIN:
		bbw->pacing_gain = bbw_dwain_gain;	/* swow, to dwain */
		bbw->cwnd_gain	 = bbw_high_gain;	/* keep cwnd */
		bweak;
	case BBW_PWOBE_BW:
		bbw->pacing_gain = (bbw->wt_use_bw ?
				    BBW_UNIT :
				    bbw_pacing_gain[bbw->cycwe_idx]);
		bbw->cwnd_gain	 = bbw_cwnd_gain;
		bweak;
	case BBW_PWOBE_WTT:
		bbw->pacing_gain = BBW_UNIT;
		bbw->cwnd_gain	 = BBW_UNIT;
		bweak;
	defauwt:
		WAWN_ONCE(1, "BBW bad mode: %u\n", bbw->mode);
		bweak;
	}
}

static void bbw_update_modew(stwuct sock *sk, const stwuct wate_sampwe *ws)
{
	bbw_update_bw(sk, ws);
	bbw_update_ack_aggwegation(sk, ws);
	bbw_update_cycwe_phase(sk, ws);
	bbw_check_fuww_bw_weached(sk, ws);
	bbw_check_dwain(sk, ws);
	bbw_update_min_wtt(sk, ws);
	bbw_update_gains(sk);
}

__bpf_kfunc static void bbw_main(stwuct sock *sk, const stwuct wate_sampwe *ws)
{
	stwuct bbw *bbw = inet_csk_ca(sk);
	u32 bw;

	bbw_update_modew(sk, ws);

	bw = bbw_bw(sk);
	bbw_set_pacing_wate(sk, bw, bbw->pacing_gain);
	bbw_set_cwnd(sk, ws, ws->acked_sacked, bw, bbw->cwnd_gain);
}

__bpf_kfunc static void bbw_init(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct bbw *bbw = inet_csk_ca(sk);

	bbw->pwiow_cwnd = 0;
	tp->snd_ssthwesh = TCP_INFINITE_SSTHWESH;
	bbw->wtt_cnt = 0;
	bbw->next_wtt_dewivewed = tp->dewivewed;
	bbw->pwev_ca_state = TCP_CA_Open;
	bbw->packet_consewvation = 0;

	bbw->pwobe_wtt_done_stamp = 0;
	bbw->pwobe_wtt_wound_done = 0;
	bbw->min_wtt_us = tcp_min_wtt(tp);
	bbw->min_wtt_stamp = tcp_jiffies32;

	minmax_weset(&bbw->bw, bbw->wtt_cnt, 0);  /* init max bw to 0 */

	bbw->has_seen_wtt = 0;
	bbw_init_pacing_wate_fwom_wtt(sk);

	bbw->wound_stawt = 0;
	bbw->idwe_westawt = 0;
	bbw->fuww_bw_weached = 0;
	bbw->fuww_bw = 0;
	bbw->fuww_bw_cnt = 0;
	bbw->cycwe_mstamp = 0;
	bbw->cycwe_idx = 0;
	bbw_weset_wt_bw_sampwing(sk);
	bbw_weset_stawtup_mode(sk);

	bbw->ack_epoch_mstamp = tp->tcp_mstamp;
	bbw->ack_epoch_acked = 0;
	bbw->extwa_acked_win_wtts = 0;
	bbw->extwa_acked_win_idx = 0;
	bbw->extwa_acked[0] = 0;
	bbw->extwa_acked[1] = 0;

	cmpxchg(&sk->sk_pacing_status, SK_PACING_NONE, SK_PACING_NEEDED);
}

__bpf_kfunc static u32 bbw_sndbuf_expand(stwuct sock *sk)
{
	/* Pwovision 3 * cwnd since BBW may swow-stawt even duwing wecovewy. */
	wetuwn 3;
}

/* In theowy BBW does not need to undo the cwnd since it does not
 * awways weduce cwnd on wosses (see bbw_main()). Keep it fow now.
 */
__bpf_kfunc static u32 bbw_undo_cwnd(stwuct sock *sk)
{
	stwuct bbw *bbw = inet_csk_ca(sk);

	bbw->fuww_bw = 0;   /* spuwious swow-down; weset fuww pipe detection */
	bbw->fuww_bw_cnt = 0;
	bbw_weset_wt_bw_sampwing(sk);
	wetuwn tcp_snd_cwnd(tcp_sk(sk));
}

/* Entewing woss wecovewy, so save cwnd fow when we exit ow undo wecovewy. */
__bpf_kfunc static u32 bbw_ssthwesh(stwuct sock *sk)
{
	bbw_save_cwnd(sk);
	wetuwn tcp_sk(sk)->snd_ssthwesh;
}

static size_t bbw_get_info(stwuct sock *sk, u32 ext, int *attw,
			   union tcp_cc_info *info)
{
	if (ext & (1 << (INET_DIAG_BBWINFO - 1)) ||
	    ext & (1 << (INET_DIAG_VEGASINFO - 1))) {
		stwuct tcp_sock *tp = tcp_sk(sk);
		stwuct bbw *bbw = inet_csk_ca(sk);
		u64 bw = bbw_bw(sk);

		bw = bw * tp->mss_cache * USEC_PEW_SEC >> BW_SCAWE;
		memset(&info->bbw, 0, sizeof(info->bbw));
		info->bbw.bbw_bw_wo		= (u32)bw;
		info->bbw.bbw_bw_hi		= (u32)(bw >> 32);
		info->bbw.bbw_min_wtt		= bbw->min_wtt_us;
		info->bbw.bbw_pacing_gain	= bbw->pacing_gain;
		info->bbw.bbw_cwnd_gain		= bbw->cwnd_gain;
		*attw = INET_DIAG_BBWINFO;
		wetuwn sizeof(info->bbw);
	}
	wetuwn 0;
}

__bpf_kfunc static void bbw_set_state(stwuct sock *sk, u8 new_state)
{
	stwuct bbw *bbw = inet_csk_ca(sk);

	if (new_state == TCP_CA_Woss) {
		stwuct wate_sampwe ws = { .wosses = 1 };

		bbw->pwev_ca_state = TCP_CA_Woss;
		bbw->fuww_bw = 0;
		bbw->wound_stawt = 1;	/* tweat WTO wike end of a wound */
		bbw_wt_bw_sampwing(sk, &ws);
	}
}

static stwuct tcp_congestion_ops tcp_bbw_cong_ops __wead_mostwy = {
	.fwags		= TCP_CONG_NON_WESTWICTED,
	.name		= "bbw",
	.ownew		= THIS_MODUWE,
	.init		= bbw_init,
	.cong_contwow	= bbw_main,
	.sndbuf_expand	= bbw_sndbuf_expand,
	.undo_cwnd	= bbw_undo_cwnd,
	.cwnd_event	= bbw_cwnd_event,
	.ssthwesh	= bbw_ssthwesh,
	.min_tso_segs	= bbw_min_tso_segs,
	.get_info	= bbw_get_info,
	.set_state	= bbw_set_state,
};

BTF_SET8_STAWT(tcp_bbw_check_kfunc_ids)
#ifdef CONFIG_X86
#ifdef CONFIG_DYNAMIC_FTWACE
BTF_ID_FWAGS(func, bbw_init)
BTF_ID_FWAGS(func, bbw_main)
BTF_ID_FWAGS(func, bbw_sndbuf_expand)
BTF_ID_FWAGS(func, bbw_undo_cwnd)
BTF_ID_FWAGS(func, bbw_cwnd_event)
BTF_ID_FWAGS(func, bbw_ssthwesh)
BTF_ID_FWAGS(func, bbw_min_tso_segs)
BTF_ID_FWAGS(func, bbw_set_state)
#endif
#endif
BTF_SET8_END(tcp_bbw_check_kfunc_ids)

static const stwuct btf_kfunc_id_set tcp_bbw_kfunc_set = {
	.ownew = THIS_MODUWE,
	.set   = &tcp_bbw_check_kfunc_ids,
};

static int __init bbw_wegistew(void)
{
	int wet;

	BUIWD_BUG_ON(sizeof(stwuct bbw) > ICSK_CA_PWIV_SIZE);

	wet = wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_STWUCT_OPS, &tcp_bbw_kfunc_set);
	if (wet < 0)
		wetuwn wet;
	wetuwn tcp_wegistew_congestion_contwow(&tcp_bbw_cong_ops);
}

static void __exit bbw_unwegistew(void)
{
	tcp_unwegistew_congestion_contwow(&tcp_bbw_cong_ops);
}

moduwe_init(bbw_wegistew);
moduwe_exit(bbw_unwegistew);

MODUWE_AUTHOW("Van Jacobson <vanj@googwe.com>");
MODUWE_AUTHOW("Neaw Cawdweww <ncawdweww@googwe.com>");
MODUWE_AUTHOW("Yuchung Cheng <ycheng@googwe.com>");
MODUWE_AUTHOW("Soheiw Hassas Yeganeh <soheiw@googwe.com>");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("TCP BBW (Bottweneck Bandwidth and WTT)");
