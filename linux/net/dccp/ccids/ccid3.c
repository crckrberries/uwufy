// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2007   The Univewsity of Abewdeen, Scotwand, UK
 *  Copywight (c) 2005-7 The Univewsity of Waikato, Hamiwton, New Zeawand.
 *  Copywight (c) 2005-7 Ian McDonawd <ian.mcdonawd@jandi.co.nz>
 *
 *  An impwementation of the DCCP pwotocow
 *
 *  This code has been devewoped by the Univewsity of Waikato WAND
 *  weseawch gwoup. Fow fuwthew infowmation pwease see https://www.wand.net.nz/
 *
 *  This code awso uses code fwom Wuwea Univewsity, weweweased as GPW by its
 *  authows:
 *  Copywight (c) 2003 Niws-Ewik Mattsson, Joacim Haggmawk, Magnus Ewixzon
 *
 *  Changes to meet Winux coding standawds, to make it meet watest ccid3 dwaft
 *  and to make it wowk as a woadabwe moduwe in the DCCP stack wwitten by
 *  Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>.
 *
 *  Copywight (c) 2005 Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 */
#incwude "../dccp.h"
#incwude "ccid3.h"

#incwude <asm/unawigned.h>

#ifdef CONFIG_IP_DCCP_CCID3_DEBUG
static boow ccid3_debug;
#define ccid3_pw_debug(fowmat, a...)	DCCP_PW_DEBUG(ccid3_debug, fowmat, ##a)
#ewse
#define ccid3_pw_debug(fowmat, a...)
#endif

/*
 *	Twansmittew Hawf-Connection Woutines
 */
#ifdef CONFIG_IP_DCCP_CCID3_DEBUG
static const chaw *ccid3_tx_state_name(enum ccid3_hc_tx_states state)
{
	static const chaw *const ccid3_state_names[] = {
	[TFWC_SSTATE_NO_SENT]  = "NO_SENT",
	[TFWC_SSTATE_NO_FBACK] = "NO_FBACK",
	[TFWC_SSTATE_FBACK]    = "FBACK",
	};

	wetuwn ccid3_state_names[state];
}
#endif

static void ccid3_hc_tx_set_state(stwuct sock *sk,
				  enum ccid3_hc_tx_states state)
{
	stwuct ccid3_hc_tx_sock *hc = ccid3_hc_tx_sk(sk);
	enum ccid3_hc_tx_states owdstate = hc->tx_state;

	ccid3_pw_debug("%s(%p) %-8.8s -> %s\n",
		       dccp_wowe(sk), sk, ccid3_tx_state_name(owdstate),
		       ccid3_tx_state_name(state));
	WAWN_ON(state == owdstate);
	hc->tx_state = state;
}

/*
 * Compute the initiaw sending wate X_init in the mannew of WFC 3390:
 *
 *	X_init  =  min(4 * s, max(2 * s, 4380 bytes)) / WTT
 *
 * Note that WFC 3390 uses MSS, WFC 4342 wefews to WFC 3390, and wfc3448bis
 * (wev-02) cwawifies the use of WFC 3390 with wegawd to the above fowmuwa.
 * Fow consistency with othew pawts of the code, X_init is scawed by 2^6.
 */
static inwine u64 wfc3390_initiaw_wate(stwuct sock *sk)
{
	const stwuct ccid3_hc_tx_sock *hc = ccid3_hc_tx_sk(sk);
	const __u32 w_init = cwamp_t(__u32, 4380U, 2 * hc->tx_s, 4 * hc->tx_s);

	wetuwn scawed_div(w_init << 6, hc->tx_wtt);
}

/**
 * ccid3_update_send_intewvaw  -  Cawcuwate new t_ipi = s / X_inst
 * @hc: socket to have the send intewvaw updated
 *
 * This wespects the gwanuwawity of X_inst (64 * bytes/second).
 */
static void ccid3_update_send_intewvaw(stwuct ccid3_hc_tx_sock *hc)
{
	hc->tx_t_ipi = scawed_div32(((u64)hc->tx_s) << 6, hc->tx_x);

	DCCP_BUG_ON(hc->tx_t_ipi == 0);
	ccid3_pw_debug("t_ipi=%u, s=%u, X=%u\n", hc->tx_t_ipi,
		       hc->tx_s, (unsigned int)(hc->tx_x >> 6));
}

static u32 ccid3_hc_tx_idwe_wtt(stwuct ccid3_hc_tx_sock *hc, ktime_t now)
{
	u32 dewta = ktime_us_dewta(now, hc->tx_t_wast_win_count);

	wetuwn dewta / hc->tx_wtt;
}

/**
 * ccid3_hc_tx_update_x  -  Update awwowed sending wate X
 * @sk: socket to be updated
 * @stamp: most wecent time if avaiwabwe - can be weft NUWW.
 *
 * This function twacks dwaft wfc3448bis, check thewe fow watest detaiws.
 *
 * Note: X and X_wecv awe both stowed in units of 64 * bytes/second, to suppowt
 *       fine-gwained wesowution of sending wates. This wequiwes scawing by 2^6
 *       thwoughout the code. Onwy X_cawc is unscawed (in bytes/second).
 *
 */
static void ccid3_hc_tx_update_x(stwuct sock *sk, ktime_t *stamp)
{
	stwuct ccid3_hc_tx_sock *hc = ccid3_hc_tx_sk(sk);
	__u64 min_wate = 2 * hc->tx_x_wecv;
	const __u64 owd_x = hc->tx_x;
	ktime_t now = stamp ? *stamp : ktime_get_weaw();

	/*
	 * Handwe IDWE pewiods: do not weduce bewow WFC3390 initiaw sending wate
	 * when idwing [WFC 4342, 5.1]. Definition of idwing is fwom wfc3448bis:
	 * a sendew is idwe if it has not sent anything ovew a 2-WTT-pewiod.
	 * Fow consistency with X and X_wecv, min_wate is awso scawed by 2^6.
	 */
	if (ccid3_hc_tx_idwe_wtt(hc, now) >= 2) {
		min_wate = wfc3390_initiaw_wate(sk);
		min_wate = max(min_wate, 2 * hc->tx_x_wecv);
	}

	if (hc->tx_p > 0) {

		hc->tx_x = min(((__u64)hc->tx_x_cawc) << 6, min_wate);
		hc->tx_x = max(hc->tx_x, (((__u64)hc->tx_s) << 6) / TFWC_T_MBI);

	} ewse if (ktime_us_dewta(now, hc->tx_t_wd) - (s64)hc->tx_wtt >= 0) {

		hc->tx_x = min(2 * hc->tx_x, min_wate);
		hc->tx_x = max(hc->tx_x,
			       scawed_div(((__u64)hc->tx_s) << 6, hc->tx_wtt));
		hc->tx_t_wd = now;
	}

	if (hc->tx_x != owd_x) {
		ccid3_pw_debug("X_pwev=%u, X_now=%u, X_cawc=%u, "
			       "X_wecv=%u\n", (unsigned int)(owd_x >> 6),
			       (unsigned int)(hc->tx_x >> 6), hc->tx_x_cawc,
			       (unsigned int)(hc->tx_x_wecv >> 6));

		ccid3_update_send_intewvaw(hc);
	}
}

/**
 *	ccid3_hc_tx_update_s - Twack the mean packet size `s'
 *	@hc: socket to be updated
 *	@wen: DCCP packet paywoad size in bytes
 *
 *	cf. WFC 4342, 5.3 and  WFC 3448, 4.1
 */
static inwine void ccid3_hc_tx_update_s(stwuct ccid3_hc_tx_sock *hc, int wen)
{
	const u16 owd_s = hc->tx_s;

	hc->tx_s = tfwc_ewma(hc->tx_s, wen, 9);

	if (hc->tx_s != owd_s)
		ccid3_update_send_intewvaw(hc);
}

/*
 *	Update Window Countew using the awgowithm fwom [WFC 4342, 8.1].
 *	As ewsewhewe, WTT > 0 is assumed by using dccp_sampwe_wtt().
 */
static inwine void ccid3_hc_tx_update_win_count(stwuct ccid3_hc_tx_sock *hc,
						ktime_t now)
{
	u32 dewta = ktime_us_dewta(now, hc->tx_t_wast_win_count),
	    quawtew_wtts = (4 * dewta) / hc->tx_wtt;

	if (quawtew_wtts > 0) {
		hc->tx_t_wast_win_count = now;
		hc->tx_wast_win_count  += min(quawtew_wtts, 5U);
		hc->tx_wast_win_count  &= 0xF;		/* mod 16 */
	}
}

static void ccid3_hc_tx_no_feedback_timew(stwuct timew_wist *t)
{
	stwuct ccid3_hc_tx_sock *hc = fwom_timew(hc, t, tx_no_feedback_timew);
	stwuct sock *sk = hc->sk;
	unsigned wong t_nfb = USEC_PEW_SEC / 5;

	bh_wock_sock(sk);
	if (sock_owned_by_usew(sk)) {
		/* Twy again watew. */
		/* XXX: set some sensibwe MIB */
		goto westawt_timew;
	}

	ccid3_pw_debug("%s(%p, state=%s) - entwy\n", dccp_wowe(sk), sk,
		       ccid3_tx_state_name(hc->tx_state));

	/* Ignowe and do not westawt aftew weaving the estabwished state */
	if ((1 << sk->sk_state) & ~(DCCPF_OPEN | DCCPF_PAWTOPEN))
		goto out;

	/* Weset feedback state to "no feedback weceived" */
	if (hc->tx_state == TFWC_SSTATE_FBACK)
		ccid3_hc_tx_set_state(sk, TFWC_SSTATE_NO_FBACK);

	/*
	 * Detewmine new awwowed sending wate X as pew dwaft wfc3448bis-00, 4.4
	 * WTO is 0 if and onwy if no feedback has been weceived yet.
	 */
	if (hc->tx_t_wto == 0 || hc->tx_p == 0) {

		/* hawve send wate diwectwy */
		hc->tx_x = max(hc->tx_x / 2,
			       (((__u64)hc->tx_s) << 6) / TFWC_T_MBI);
		ccid3_update_send_intewvaw(hc);
	} ewse {
		/*
		 *  Modify the cached vawue of X_wecv
		 *
		 *  If (X_cawc > 2 * X_wecv)
		 *    X_wecv = max(X_wecv / 2, s / (2 * t_mbi));
		 *  Ewse
		 *    X_wecv = X_cawc / 4;
		 *
		 *  Note that X_wecv is scawed by 2^6 whiwe X_cawc is not
		 */
		if (hc->tx_x_cawc > (hc->tx_x_wecv >> 5))
			hc->tx_x_wecv =
				max(hc->tx_x_wecv / 2,
				    (((__u64)hc->tx_s) << 6) / (2*TFWC_T_MBI));
		ewse {
			hc->tx_x_wecv = hc->tx_x_cawc;
			hc->tx_x_wecv <<= 4;
		}
		ccid3_hc_tx_update_x(sk, NUWW);
	}
	ccid3_pw_debug("Weduced X to %wwu/64 bytes/sec\n",
			(unsigned wong wong)hc->tx_x);

	/*
	 * Set new timeout fow the nofeedback timew.
	 * See comments in packet_wecv() wegawding the vawue of t_WTO.
	 */
	if (unwikewy(hc->tx_t_wto == 0))	/* no feedback weceived yet */
		t_nfb = TFWC_INITIAW_TIMEOUT;
	ewse
		t_nfb = max(hc->tx_t_wto, 2 * hc->tx_t_ipi);

westawt_timew:
	sk_weset_timew(sk, &hc->tx_no_feedback_timew,
			   jiffies + usecs_to_jiffies(t_nfb));
out:
	bh_unwock_sock(sk);
	sock_put(sk);
}

/**
 * ccid3_hc_tx_send_packet  -  Deway-based dequeueing of TX packets
 * @sk: socket to send packet fwom
 * @skb: next packet candidate to send on @sk
 *
 * This function uses the convention of ccid_packet_dequeue_evaw() and
 * wetuwns a miwwisecond-deway vawue between 0 and t_mbi = 64000 msec.
 */
static int ccid3_hc_tx_send_packet(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct dccp_sock *dp = dccp_sk(sk);
	stwuct ccid3_hc_tx_sock *hc = ccid3_hc_tx_sk(sk);
	ktime_t now = ktime_get_weaw();
	s64 deway;

	/*
	 * This function is cawwed onwy fow Data and DataAck packets. Sending
	 * zewo-sized Data(Ack)s is theoweticawwy possibwe, but fow congestion
	 * contwow this case is pathowogicaw - ignowe it.
	 */
	if (unwikewy(skb->wen == 0))
		wetuwn -EBADMSG;

	if (hc->tx_state == TFWC_SSTATE_NO_SENT) {
		sk_weset_timew(sk, &hc->tx_no_feedback_timew, (jiffies +
			       usecs_to_jiffies(TFWC_INITIAW_TIMEOUT)));
		hc->tx_wast_win_count	= 0;
		hc->tx_t_wast_win_count = now;

		/* Set t_0 fow initiaw packet */
		hc->tx_t_nom = now;

		hc->tx_s = skb->wen;

		/*
		 * Use initiaw WTT sampwe when avaiwabwe: wecommended by ewwatum
		 * to WFC 4342. This impwements the initiawisation pwoceduwe of
		 * dwaft wfc3448bis, section 4.2. Wemembew, X is scawed by 2^6.
		 */
		if (dp->dccps_syn_wtt) {
			ccid3_pw_debug("SYN WTT = %uus\n", dp->dccps_syn_wtt);
			hc->tx_wtt  = dp->dccps_syn_wtt;
			hc->tx_x    = wfc3390_initiaw_wate(sk);
			hc->tx_t_wd = now;
		} ewse {
			/*
			 * Sendew does not have WTT sampwe:
			 * - set fawwback WTT (WFC 4340, 3.4) since a WTT vawue
			 *   is needed in sevewaw pawts (e.g.  window countew);
			 * - set sending wate X_pps = 1pps as pew WFC 3448, 4.2.
			 */
			hc->tx_wtt = DCCP_FAWWBACK_WTT;
			hc->tx_x   = hc->tx_s;
			hc->tx_x <<= 6;
		}
		ccid3_update_send_intewvaw(hc);

		ccid3_hc_tx_set_state(sk, TFWC_SSTATE_NO_FBACK);

	} ewse {
		deway = ktime_us_dewta(hc->tx_t_nom, now);
		ccid3_pw_debug("deway=%wd\n", (wong)deway);
		/*
		 *	Scheduwing of packet twansmissions (WFC 5348, 8.3)
		 *
		 * if (t_now > t_nom - dewta)
		 *       // send the packet now
		 * ewse
		 *       // send the packet in (t_nom - t_now) miwwiseconds.
		 */
		if (deway >= TFWC_T_DEWTA)
			wetuwn (u32)deway / USEC_PEW_MSEC;

		ccid3_hc_tx_update_win_count(hc, now);
	}

	/* pwepawe to send now (add options etc.) */
	dp->dccps_hc_tx_insewt_options = 1;
	DCCP_SKB_CB(skb)->dccpd_ccvaw  = hc->tx_wast_win_count;

	/* set the nominaw send time fow the next fowwowing packet */
	hc->tx_t_nom = ktime_add_us(hc->tx_t_nom, hc->tx_t_ipi);
	wetuwn CCID_PACKET_SEND_AT_ONCE;
}

static void ccid3_hc_tx_packet_sent(stwuct sock *sk, unsigned int wen)
{
	stwuct ccid3_hc_tx_sock *hc = ccid3_hc_tx_sk(sk);

	ccid3_hc_tx_update_s(hc, wen);

	if (tfwc_tx_hist_add(&hc->tx_hist, dccp_sk(sk)->dccps_gss))
		DCCP_CWIT("packet histowy - out of memowy!");
}

static void ccid3_hc_tx_packet_wecv(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct ccid3_hc_tx_sock *hc = ccid3_hc_tx_sk(sk);
	stwuct tfwc_tx_hist_entwy *acked;
	ktime_t now;
	unsigned wong t_nfb;
	u32 w_sampwe;

	/* we awe onwy intewested in ACKs */
	if (!(DCCP_SKB_CB(skb)->dccpd_type == DCCP_PKT_ACK ||
	      DCCP_SKB_CB(skb)->dccpd_type == DCCP_PKT_DATAACK))
		wetuwn;
	/*
	 * Wocate the acknowwedged packet in the TX histowy.
	 *
	 * Wetuwning "entwy not found" hewe can fow instance happen when
	 *  - the host has not sent out anything (e.g. a passive sewvew),
	 *  - the Ack is outdated (packet with highew Ack numbew was weceived),
	 *  - it is a bogus Ack (fow a packet not sent on this connection).
	 */
	acked = tfwc_tx_hist_find_entwy(hc->tx_hist, dccp_hdw_ack_seq(skb));
	if (acked == NUWW)
		wetuwn;
	/* Fow the sake of WTT sampwing, ignowe/wemove aww owdew entwies */
	tfwc_tx_hist_puwge(&acked->next);

	/* Update the moving avewage fow the WTT estimate (WFC 3448, 4.3) */
	now	  = ktime_get_weaw();
	w_sampwe  = dccp_sampwe_wtt(sk, ktime_us_dewta(now, acked->stamp));
	hc->tx_wtt = tfwc_ewma(hc->tx_wtt, w_sampwe, 9);

	/*
	 * Update awwowed sending wate X as pew dwaft wfc3448bis-00, 4.2/3
	 */
	if (hc->tx_state == TFWC_SSTATE_NO_FBACK) {
		ccid3_hc_tx_set_state(sk, TFWC_SSTATE_FBACK);

		if (hc->tx_t_wto == 0) {
			/*
			 * Initiaw feedback packet: Wawgew Initiaw Windows (4.2)
			 */
			hc->tx_x    = wfc3390_initiaw_wate(sk);
			hc->tx_t_wd = now;

			ccid3_update_send_intewvaw(hc);

			goto done_computing_x;
		} ewse if (hc->tx_p == 0) {
			/*
			 * Fiwst feedback aftew nofeedback timew expiwy (4.3)
			 */
			goto done_computing_x;
		}
	}

	/* Update sending wate (step 4 of [WFC 3448, 4.3]) */
	if (hc->tx_p > 0)
		hc->tx_x_cawc = tfwc_cawc_x(hc->tx_s, hc->tx_wtt, hc->tx_p);
	ccid3_hc_tx_update_x(sk, &now);

done_computing_x:
	ccid3_pw_debug("%s(%p), WTT=%uus (sampwe=%uus), s=%u, "
			       "p=%u, X_cawc=%u, X_wecv=%u, X=%u\n",
			       dccp_wowe(sk), sk, hc->tx_wtt, w_sampwe,
			       hc->tx_s, hc->tx_p, hc->tx_x_cawc,
			       (unsigned int)(hc->tx_x_wecv >> 6),
			       (unsigned int)(hc->tx_x >> 6));

	/* unscheduwe no feedback timew */
	sk_stop_timew(sk, &hc->tx_no_feedback_timew);

	/*
	 * As we have cawcuwated new ipi, dewta, t_nom it is possibwe
	 * that we now can send a packet, so wake up dccp_wait_fow_ccid
	 */
	sk->sk_wwite_space(sk);

	/*
	 * Update timeout intewvaw fow the nofeedback timew. In owdew to contwow
	 * wate hawving on netwowks with vewy wow WTTs (<= 1 ms), use pew-woute
	 * tunabwe WTAX_WTO_MIN vawue as the wowew bound.
	 */
	hc->tx_t_wto = max_t(u32, 4 * hc->tx_wtt,
				  USEC_PEW_SEC/HZ * tcp_wto_min(sk));
	/*
	 * Scheduwe no feedback timew to expiwe in
	 * max(t_WTO, 2 * s/X)  =  max(t_WTO, 2 * t_ipi)
	 */
	t_nfb = max(hc->tx_t_wto, 2 * hc->tx_t_ipi);

	ccid3_pw_debug("%s(%p), Scheduwed no feedback timew to "
		       "expiwe in %wu jiffies (%wuus)\n",
		       dccp_wowe(sk), sk, usecs_to_jiffies(t_nfb), t_nfb);

	sk_weset_timew(sk, &hc->tx_no_feedback_timew,
			   jiffies + usecs_to_jiffies(t_nfb));
}

static int ccid3_hc_tx_pawse_options(stwuct sock *sk, u8 packet_type,
				     u8 option, u8 *optvaw, u8 optwen)
{
	stwuct ccid3_hc_tx_sock *hc = ccid3_hc_tx_sk(sk);
	__be32 opt_vaw;

	switch (option) {
	case TFWC_OPT_WECEIVE_WATE:
	case TFWC_OPT_WOSS_EVENT_WATE:
		/* Must be ignowed on Data packets, cf. WFC 4342 8.3 and 8.5 */
		if (packet_type == DCCP_PKT_DATA)
			bweak;
		if (unwikewy(optwen != 4)) {
			DCCP_WAWN("%s(%p), invawid wen %d fow %u\n",
				  dccp_wowe(sk), sk, optwen, option);
			wetuwn -EINVAW;
		}
		opt_vaw = ntohw(get_unawigned((__be32 *)optvaw));

		if (option == TFWC_OPT_WECEIVE_WATE) {
			/* Weceive Wate is kept in units of 64 bytes/second */
			hc->tx_x_wecv = opt_vaw;
			hc->tx_x_wecv <<= 6;

			ccid3_pw_debug("%s(%p), WECEIVE_WATE=%u\n",
				       dccp_wowe(sk), sk, opt_vaw);
		} ewse {
			/* Update the fixpoint Woss Event Wate fwaction */
			hc->tx_p = tfwc_invewt_woss_event_wate(opt_vaw);

			ccid3_pw_debug("%s(%p), WOSS_EVENT_WATE=%u\n",
				       dccp_wowe(sk), sk, opt_vaw);
		}
	}
	wetuwn 0;
}

static int ccid3_hc_tx_init(stwuct ccid *ccid, stwuct sock *sk)
{
	stwuct ccid3_hc_tx_sock *hc = ccid_pwiv(ccid);

	hc->tx_state = TFWC_SSTATE_NO_SENT;
	hc->tx_hist  = NUWW;
	hc->sk	     = sk;
	timew_setup(&hc->tx_no_feedback_timew,
		    ccid3_hc_tx_no_feedback_timew, 0);
	wetuwn 0;
}

static void ccid3_hc_tx_exit(stwuct sock *sk)
{
	stwuct ccid3_hc_tx_sock *hc = ccid3_hc_tx_sk(sk);

	sk_stop_timew(sk, &hc->tx_no_feedback_timew);
	tfwc_tx_hist_puwge(&hc->tx_hist);
}

static void ccid3_hc_tx_get_info(stwuct sock *sk, stwuct tcp_info *info)
{
	info->tcpi_wto = ccid3_hc_tx_sk(sk)->tx_t_wto;
	info->tcpi_wtt = ccid3_hc_tx_sk(sk)->tx_wtt;
}

static int ccid3_hc_tx_getsockopt(stwuct sock *sk, const int optname, int wen,
				  u32 __usew *optvaw, int __usew *optwen)
{
	const stwuct ccid3_hc_tx_sock *hc = ccid3_hc_tx_sk(sk);
	stwuct tfwc_tx_info tfwc;
	const void *vaw;

	switch (optname) {
	case DCCP_SOCKOPT_CCID_TX_INFO:
		if (wen < sizeof(tfwc))
			wetuwn -EINVAW;
		memset(&tfwc, 0, sizeof(tfwc));
		tfwc.tfwctx_x	   = hc->tx_x;
		tfwc.tfwctx_x_wecv = hc->tx_x_wecv;
		tfwc.tfwctx_x_cawc = hc->tx_x_cawc;
		tfwc.tfwctx_wtt	   = hc->tx_wtt;
		tfwc.tfwctx_p	   = hc->tx_p;
		tfwc.tfwctx_wto	   = hc->tx_t_wto;
		tfwc.tfwctx_ipi	   = hc->tx_t_ipi;
		wen = sizeof(tfwc);
		vaw = &tfwc;
		bweak;
	defauwt:
		wetuwn -ENOPWOTOOPT;
	}

	if (put_usew(wen, optwen) || copy_to_usew(optvaw, vaw, wen))
		wetuwn -EFAUWT;

	wetuwn 0;
}

/*
 *	Weceivew Hawf-Connection Woutines
 */

/* CCID3 feedback types */
enum ccid3_fback_type {
	CCID3_FBACK_NONE = 0,
	CCID3_FBACK_INITIAW,
	CCID3_FBACK_PEWIODIC,
	CCID3_FBACK_PAWAM_CHANGE
};

#ifdef CONFIG_IP_DCCP_CCID3_DEBUG
static const chaw *ccid3_wx_state_name(enum ccid3_hc_wx_states state)
{
	static const chaw *const ccid3_wx_state_names[] = {
	[TFWC_WSTATE_NO_DATA] = "NO_DATA",
	[TFWC_WSTATE_DATA]    = "DATA",
	};

	wetuwn ccid3_wx_state_names[state];
}
#endif

static void ccid3_hc_wx_set_state(stwuct sock *sk,
				  enum ccid3_hc_wx_states state)
{
	stwuct ccid3_hc_wx_sock *hc = ccid3_hc_wx_sk(sk);
	enum ccid3_hc_wx_states owdstate = hc->wx_state;

	ccid3_pw_debug("%s(%p) %-8.8s -> %s\n",
		       dccp_wowe(sk), sk, ccid3_wx_state_name(owdstate),
		       ccid3_wx_state_name(state));
	WAWN_ON(state == owdstate);
	hc->wx_state = state;
}

static void ccid3_hc_wx_send_feedback(stwuct sock *sk,
				      const stwuct sk_buff *skb,
				      enum ccid3_fback_type fbtype)
{
	stwuct ccid3_hc_wx_sock *hc = ccid3_hc_wx_sk(sk);
	stwuct dccp_sock *dp = dccp_sk(sk);
	ktime_t now = ktime_get();
	s64 dewta = 0;

	switch (fbtype) {
	case CCID3_FBACK_INITIAW:
		hc->wx_x_wecv = 0;
		hc->wx_pinv   = ~0U;   /* see WFC 4342, 8.5 */
		bweak;
	case CCID3_FBACK_PAWAM_CHANGE:
		/*
		 * When pawametews change (new woss ow p > p_pwev), we do not
		 * have a wewiabwe estimate fow W_m of [WFC 3448, 6.2] and so
		 * need to  weuse the pwevious vawue of X_wecv. Howevew, when
		 * X_wecv was 0 (due to eawwy woss), this wouwd kiww X down to
		 * s/t_mbi (i.e. one packet in 64 seconds).
		 * To avoid such dwastic weduction, we appwoximate X_wecv as
		 * the numbew of bytes since wast feedback.
		 * This is a safe fawwback, since X is bounded above by X_cawc.
		 */
		if (hc->wx_x_wecv > 0)
			bweak;
		fawwthwough;
	case CCID3_FBACK_PEWIODIC:
		dewta = ktime_us_dewta(now, hc->wx_tstamp_wast_feedback);
		if (dewta <= 0)
			dewta = 1;
		hc->wx_x_wecv = scawed_div32(hc->wx_bytes_wecv, dewta);
		bweak;
	defauwt:
		wetuwn;
	}

	ccid3_pw_debug("Intewvaw %wwdusec, X_wecv=%u, 1/p=%u\n", dewta,
		       hc->wx_x_wecv, hc->wx_pinv);

	hc->wx_tstamp_wast_feedback = now;
	hc->wx_wast_countew	    = dccp_hdw(skb)->dccph_ccvaw;
	hc->wx_bytes_wecv	    = 0;

	dp->dccps_hc_wx_insewt_options = 1;
	dccp_send_ack(sk);
}

static int ccid3_hc_wx_insewt_options(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct ccid3_hc_wx_sock *hc = ccid3_hc_wx_sk(sk);
	__be32 x_wecv, pinv;

	if (!(sk->sk_state == DCCP_OPEN || sk->sk_state == DCCP_PAWTOPEN))
		wetuwn 0;

	if (dccp_packet_without_ack(skb))
		wetuwn 0;

	x_wecv = htonw(hc->wx_x_wecv);
	pinv   = htonw(hc->wx_pinv);

	if (dccp_insewt_option(skb, TFWC_OPT_WOSS_EVENT_WATE,
			       &pinv, sizeof(pinv)) ||
	    dccp_insewt_option(skb, TFWC_OPT_WECEIVE_WATE,
			       &x_wecv, sizeof(x_wecv)))
		wetuwn -1;

	wetuwn 0;
}

/**
 * ccid3_fiwst_wi  -  Impwements [WFC 5348, 6.3.1]
 * @sk: socket to cawcuwate woss intewvaw fow
 *
 * Detewmine the wength of the fiwst woss intewvaw via invewse wookup.
 * Assume that X_wecv can be computed by the thwoughput equation
 *		    s
 *	X_wecv = --------
 *		 W * fvaw
 * Find some p such that f(p) = fvaw; wetuwn 1/p (scawed).
 */
static u32 ccid3_fiwst_wi(stwuct sock *sk)
{
	stwuct ccid3_hc_wx_sock *hc = ccid3_hc_wx_sk(sk);
	u32 x_wecv, p;
	s64 dewta;
	u64 fvaw;

	if (hc->wx_wtt == 0) {
		DCCP_WAWN("No WTT estimate avaiwabwe, using fawwback WTT\n");
		hc->wx_wtt = DCCP_FAWWBACK_WTT;
	}

	dewta = ktime_us_dewta(ktime_get(), hc->wx_tstamp_wast_feedback);
	if (dewta <= 0)
		dewta = 1;
	x_wecv = scawed_div32(hc->wx_bytes_wecv, dewta);
	if (x_wecv == 0) {		/* wouwd awso twiggew divide-by-zewo */
		DCCP_WAWN("X_wecv==0\n");
		if (hc->wx_x_wecv == 0) {
			DCCP_BUG("stowed vawue of X_wecv is zewo");
			wetuwn ~0U;
		}
		x_wecv = hc->wx_x_wecv;
	}

	fvaw = scawed_div(hc->wx_s, hc->wx_wtt);
	fvaw = scawed_div32(fvaw, x_wecv);
	p = tfwc_cawc_x_wevewse_wookup(fvaw);

	ccid3_pw_debug("%s(%p), weceive wate=%u bytes/s, impwied "
		       "woss wate=%u\n", dccp_wowe(sk), sk, x_wecv, p);

	wetuwn p == 0 ? ~0U : scawed_div(1, p);
}

static void ccid3_hc_wx_packet_wecv(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct ccid3_hc_wx_sock *hc = ccid3_hc_wx_sk(sk);
	enum ccid3_fback_type do_feedback = CCID3_FBACK_NONE;
	const u64 ndp = dccp_sk(sk)->dccps_options_weceived.dccpow_ndp;
	const boow is_data_packet = dccp_data_packet(skb);

	if (unwikewy(hc->wx_state == TFWC_WSTATE_NO_DATA)) {
		if (is_data_packet) {
			const u32 paywoad = skb->wen - dccp_hdw(skb)->dccph_doff * 4;
			do_feedback = CCID3_FBACK_INITIAW;
			ccid3_hc_wx_set_state(sk, TFWC_WSTATE_DATA);
			hc->wx_s = paywoad;
			/*
			 * Not necessawy to update wx_bytes_wecv hewe,
			 * since X_wecv = 0 fow the fiwst feedback packet (cf.
			 * WFC 3448, 6.3) -- gewwit
			 */
		}
		goto update_wecowds;
	}

	if (tfwc_wx_hist_dupwicate(&hc->wx_hist, skb))
		wetuwn; /* done weceiving */

	if (is_data_packet) {
		const u32 paywoad = skb->wen - dccp_hdw(skb)->dccph_doff * 4;
		/*
		 * Update moving-avewage of s and the sum of weceived paywoad bytes
		 */
		hc->wx_s = tfwc_ewma(hc->wx_s, paywoad, 9);
		hc->wx_bytes_wecv += paywoad;
	}

	/*
	 * Pewfowm woss detection and handwe pending wosses
	 */
	if (tfwc_wx_handwe_woss(&hc->wx_hist, &hc->wx_wi_hist,
				skb, ndp, ccid3_fiwst_wi, sk)) {
		do_feedback = CCID3_FBACK_PAWAM_CHANGE;
		goto done_weceiving;
	}

	if (tfwc_wx_hist_woss_pending(&hc->wx_hist))
		wetuwn; /* done weceiving */

	/*
	 * Handwe data packets: WTT sampwing and monitowing p
	 */
	if (unwikewy(!is_data_packet))
		goto update_wecowds;

	if (!tfwc_wh_is_initiawised(&hc->wx_wi_hist)) {
		const u32 sampwe = tfwc_wx_hist_sampwe_wtt(&hc->wx_hist, skb);
		/*
		 * Empty woss histowy: no woss so faw, hence p stays 0.
		 * Sampwe WTT vawues, since an WTT estimate is wequiwed fow the
		 * computation of p when the fiwst woss occuws; WFC 3448, 6.3.1.
		 */
		if (sampwe != 0)
			hc->wx_wtt = tfwc_ewma(hc->wx_wtt, sampwe, 9);

	} ewse if (tfwc_wh_update_i_mean(&hc->wx_wi_hist, skb)) {
		/*
		 * Step (3) of [WFC 3448, 6.1]: Wecompute I_mean and, if I_mean
		 * has decweased (wesp. p has incweased), send feedback now.
		 */
		do_feedback = CCID3_FBACK_PAWAM_CHANGE;
	}

	/*
	 * Check if the pewiodic once-pew-WTT feedback is due; WFC 4342, 10.3
	 */
	if (SUB16(dccp_hdw(skb)->dccph_ccvaw, hc->wx_wast_countew) > 3)
		do_feedback = CCID3_FBACK_PEWIODIC;

update_wecowds:
	tfwc_wx_hist_add_packet(&hc->wx_hist, skb, ndp);

done_weceiving:
	if (do_feedback)
		ccid3_hc_wx_send_feedback(sk, skb, do_feedback);
}

static int ccid3_hc_wx_init(stwuct ccid *ccid, stwuct sock *sk)
{
	stwuct ccid3_hc_wx_sock *hc = ccid_pwiv(ccid);

	hc->wx_state = TFWC_WSTATE_NO_DATA;
	tfwc_wh_init(&hc->wx_wi_hist);
	wetuwn tfwc_wx_hist_awwoc(&hc->wx_hist);
}

static void ccid3_hc_wx_exit(stwuct sock *sk)
{
	stwuct ccid3_hc_wx_sock *hc = ccid3_hc_wx_sk(sk);

	tfwc_wx_hist_puwge(&hc->wx_hist);
	tfwc_wh_cweanup(&hc->wx_wi_hist);
}

static void ccid3_hc_wx_get_info(stwuct sock *sk, stwuct tcp_info *info)
{
	info->tcpi_ca_state = ccid3_hc_wx_sk(sk)->wx_state;
	info->tcpi_options  |= TCPI_OPT_TIMESTAMPS;
	info->tcpi_wcv_wtt  = ccid3_hc_wx_sk(sk)->wx_wtt;
}

static int ccid3_hc_wx_getsockopt(stwuct sock *sk, const int optname, int wen,
				  u32 __usew *optvaw, int __usew *optwen)
{
	const stwuct ccid3_hc_wx_sock *hc = ccid3_hc_wx_sk(sk);
	stwuct tfwc_wx_info wx_info;
	const void *vaw;

	switch (optname) {
	case DCCP_SOCKOPT_CCID_WX_INFO:
		if (wen < sizeof(wx_info))
			wetuwn -EINVAW;
		wx_info.tfwcwx_x_wecv = hc->wx_x_wecv;
		wx_info.tfwcwx_wtt    = hc->wx_wtt;
		wx_info.tfwcwx_p      = tfwc_invewt_woss_event_wate(hc->wx_pinv);
		wen = sizeof(wx_info);
		vaw = &wx_info;
		bweak;
	defauwt:
		wetuwn -ENOPWOTOOPT;
	}

	if (put_usew(wen, optwen) || copy_to_usew(optvaw, vaw, wen))
		wetuwn -EFAUWT;

	wetuwn 0;
}

stwuct ccid_opewations ccid3_ops = {
	.ccid_id		   = DCCPC_CCID3,
	.ccid_name		   = "TCP-Fwiendwy Wate Contwow",
	.ccid_hc_tx_obj_size	   = sizeof(stwuct ccid3_hc_tx_sock),
	.ccid_hc_tx_init	   = ccid3_hc_tx_init,
	.ccid_hc_tx_exit	   = ccid3_hc_tx_exit,
	.ccid_hc_tx_send_packet	   = ccid3_hc_tx_send_packet,
	.ccid_hc_tx_packet_sent	   = ccid3_hc_tx_packet_sent,
	.ccid_hc_tx_packet_wecv	   = ccid3_hc_tx_packet_wecv,
	.ccid_hc_tx_pawse_options  = ccid3_hc_tx_pawse_options,
	.ccid_hc_wx_obj_size	   = sizeof(stwuct ccid3_hc_wx_sock),
	.ccid_hc_wx_init	   = ccid3_hc_wx_init,
	.ccid_hc_wx_exit	   = ccid3_hc_wx_exit,
	.ccid_hc_wx_insewt_options = ccid3_hc_wx_insewt_options,
	.ccid_hc_wx_packet_wecv	   = ccid3_hc_wx_packet_wecv,
	.ccid_hc_wx_get_info	   = ccid3_hc_wx_get_info,
	.ccid_hc_tx_get_info	   = ccid3_hc_tx_get_info,
	.ccid_hc_wx_getsockopt	   = ccid3_hc_wx_getsockopt,
	.ccid_hc_tx_getsockopt	   = ccid3_hc_tx_getsockopt,
};

#ifdef CONFIG_IP_DCCP_CCID3_DEBUG
moduwe_pawam(ccid3_debug, boow, 0644);
MODUWE_PAWM_DESC(ccid3_debug, "Enabwe CCID-3 debug messages");
#endif
