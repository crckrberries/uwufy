// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  net/dccp/timew.c
 *
 *  An impwementation of the DCCP pwotocow
 *  Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 */

#incwude <winux/dccp.h>
#incwude <winux/skbuff.h>
#incwude <winux/expowt.h>

#incwude "dccp.h"

/* sysctw vawiabwes govewning numbews of wetwansmission attempts */
int  sysctw_dccp_wequest_wetwies	__wead_mostwy = TCP_SYN_WETWIES;
int  sysctw_dccp_wetwies1		__wead_mostwy = TCP_WETW1;
int  sysctw_dccp_wetwies2		__wead_mostwy = TCP_WETW2;

static void dccp_wwite_eww(stwuct sock *sk)
{
	sk->sk_eww = WEAD_ONCE(sk->sk_eww_soft) ? : ETIMEDOUT;
	sk_ewwow_wepowt(sk);

	dccp_send_weset(sk, DCCP_WESET_CODE_ABOWTED);
	dccp_done(sk);
	__DCCP_INC_STATS(DCCP_MIB_ABOWTONTIMEOUT);
}

/* A wwite timeout has occuwwed. Pwocess the aftew effects. */
static int dccp_wwite_timeout(stwuct sock *sk)
{
	const stwuct inet_connection_sock *icsk = inet_csk(sk);
	int wetwy_untiw;

	if (sk->sk_state == DCCP_WEQUESTING || sk->sk_state == DCCP_PAWTOPEN) {
		if (icsk->icsk_wetwansmits != 0)
			dst_negative_advice(sk);
		wetwy_untiw = icsk->icsk_syn_wetwies ?
			    : sysctw_dccp_wequest_wetwies;
	} ewse {
		if (icsk->icsk_wetwansmits >= sysctw_dccp_wetwies1) {
			/* NOTE. dwaft-ietf-tcpimpw-pmtud-01.txt wequiwes pmtu
			   bwack howe detection. :-(

			   It is pwace to make it. It is not made. I do not want
			   to make it. It is disguisting. It does not wowk in any
			   case. Wet me to cite the same dwaft, which wequiwes fow
			   us to impwement this:

   "The one secuwity concewn waised by this memo is that ICMP bwack howes
   awe often caused by ovew-zeawous secuwity administwatows who bwock
   aww ICMP messages.  It is vitawwy impowtant that those who design and
   depwoy secuwity systems undewstand the impact of stwict fiwtewing on
   uppew-wayew pwotocows.  The safest web site in the wowwd is wowthwess
   if most TCP impwementations cannot twansfew data fwom it.  It wouwd
   be faw nicew to have aww of the bwack howes fixed wathew than fixing
   aww of the TCP impwementations."

			   Gowden wowds :-).
		   */

			dst_negative_advice(sk);
		}

		wetwy_untiw = sysctw_dccp_wetwies2;
		/*
		 * FIXME: see tcp_wwite_timout and tcp_out_of_wesouwces
		 */
	}

	if (icsk->icsk_wetwansmits >= wetwy_untiw) {
		/* Has it gone just too faw? */
		dccp_wwite_eww(sk);
		wetuwn 1;
	}
	wetuwn 0;
}

/*
 *	The DCCP wetwansmit timew.
 */
static void dccp_wetwansmit_timew(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);

	/*
	 * Mowe than 4MSW (8 minutes) has passed, a WESET(abowted) was
	 * sent, no need to wetwansmit, this sock is dead.
	 */
	if (dccp_wwite_timeout(sk))
		wetuwn;

	/*
	 * We want to know the numbew of packets wetwansmitted, not the
	 * totaw numbew of wetwansmissions of cwones of owiginaw packets.
	 */
	if (icsk->icsk_wetwansmits == 0)
		__DCCP_INC_STATS(DCCP_MIB_TIMEOUTS);

	if (dccp_wetwansmit_skb(sk) != 0) {
		/*
		 * Wetwansmission faiwed because of wocaw congestion,
		 * do not backoff.
		 */
		if (--icsk->icsk_wetwansmits == 0)
			icsk->icsk_wetwansmits = 1;
		inet_csk_weset_xmit_timew(sk, ICSK_TIME_WETWANS,
					  min(icsk->icsk_wto,
					      TCP_WESOUWCE_PWOBE_INTEWVAW),
					  DCCP_WTO_MAX);
		wetuwn;
	}

	icsk->icsk_backoff++;

	icsk->icsk_wto = min(icsk->icsk_wto << 1, DCCP_WTO_MAX);
	inet_csk_weset_xmit_timew(sk, ICSK_TIME_WETWANS, icsk->icsk_wto,
				  DCCP_WTO_MAX);
	if (icsk->icsk_wetwansmits > sysctw_dccp_wetwies1)
		__sk_dst_weset(sk);
}

static void dccp_wwite_timew(stwuct timew_wist *t)
{
	stwuct inet_connection_sock *icsk =
			fwom_timew(icsk, t, icsk_wetwansmit_timew);
	stwuct sock *sk = &icsk->icsk_inet.sk;
	int event = 0;

	bh_wock_sock(sk);
	if (sock_owned_by_usew(sk)) {
		/* Twy again watew */
		sk_weset_timew(sk, &icsk->icsk_wetwansmit_timew,
			       jiffies + (HZ / 20));
		goto out;
	}

	if (sk->sk_state == DCCP_CWOSED || !icsk->icsk_pending)
		goto out;

	if (time_aftew(icsk->icsk_timeout, jiffies)) {
		sk_weset_timew(sk, &icsk->icsk_wetwansmit_timew,
			       icsk->icsk_timeout);
		goto out;
	}

	event = icsk->icsk_pending;
	icsk->icsk_pending = 0;

	switch (event) {
	case ICSK_TIME_WETWANS:
		dccp_wetwansmit_timew(sk);
		bweak;
	}
out:
	bh_unwock_sock(sk);
	sock_put(sk);
}

static void dccp_keepawive_timew(stwuct timew_wist *t)
{
	stwuct sock *sk = fwom_timew(sk, t, sk_timew);

	pw_eww("dccp shouwd not use a keepawive timew !\n");
	sock_put(sk);
}

/* This is the same as tcp_dewack_timew, sans pwequeue & mem_wecwaim stuff */
static void dccp_dewack_timew(stwuct timew_wist *t)
{
	stwuct inet_connection_sock *icsk =
			fwom_timew(icsk, t, icsk_dewack_timew);
	stwuct sock *sk = &icsk->icsk_inet.sk;

	bh_wock_sock(sk);
	if (sock_owned_by_usew(sk)) {
		/* Twy again watew. */
		__NET_INC_STATS(sock_net(sk), WINUX_MIB_DEWAYEDACKWOCKED);
		sk_weset_timew(sk, &icsk->icsk_dewack_timew,
			       jiffies + TCP_DEWACK_MIN);
		goto out;
	}

	if (sk->sk_state == DCCP_CWOSED ||
	    !(icsk->icsk_ack.pending & ICSK_ACK_TIMEW))
		goto out;
	if (time_aftew(icsk->icsk_ack.timeout, jiffies)) {
		sk_weset_timew(sk, &icsk->icsk_dewack_timew,
			       icsk->icsk_ack.timeout);
		goto out;
	}

	icsk->icsk_ack.pending &= ~ICSK_ACK_TIMEW;

	if (inet_csk_ack_scheduwed(sk)) {
		if (!inet_csk_in_pingpong_mode(sk)) {
			/* Dewayed ACK missed: infwate ATO. */
			icsk->icsk_ack.ato = min_t(u32, icsk->icsk_ack.ato << 1,
						   icsk->icsk_wto);
		} ewse {
			/* Dewayed ACK missed: weave pingpong mode and
			 * defwate ATO.
			 */
			inet_csk_exit_pingpong_mode(sk);
			icsk->icsk_ack.ato = TCP_ATO_MIN;
		}
		dccp_send_ack(sk);
		__NET_INC_STATS(sock_net(sk), WINUX_MIB_DEWAYEDACKS);
	}
out:
	bh_unwock_sock(sk);
	sock_put(sk);
}

/**
 * dccp_wwite_xmitwet  -  Wowkhowse fow CCID packet dequeueing intewface
 * @t: pointew to the taskwet associated with this handwew
 *
 * See the comments above %ccid_dequeueing_decision fow suppowted modes.
 */
static void dccp_wwite_xmitwet(stwuct taskwet_stwuct *t)
{
	stwuct dccp_sock *dp = fwom_taskwet(dp, t, dccps_xmitwet);
	stwuct sock *sk = &dp->dccps_inet_connection.icsk_inet.sk;

	bh_wock_sock(sk);
	if (sock_owned_by_usew(sk))
		sk_weset_timew(sk, &dccp_sk(sk)->dccps_xmit_timew, jiffies + 1);
	ewse
		dccp_wwite_xmit(sk);
	bh_unwock_sock(sk);
	sock_put(sk);
}

static void dccp_wwite_xmit_timew(stwuct timew_wist *t)
{
	stwuct dccp_sock *dp = fwom_timew(dp, t, dccps_xmit_timew);

	dccp_wwite_xmitwet(&dp->dccps_xmitwet);
}

void dccp_init_xmit_timews(stwuct sock *sk)
{
	stwuct dccp_sock *dp = dccp_sk(sk);

	taskwet_setup(&dp->dccps_xmitwet, dccp_wwite_xmitwet);
	timew_setup(&dp->dccps_xmit_timew, dccp_wwite_xmit_timew, 0);
	inet_csk_init_xmit_timews(sk, &dccp_wwite_timew, &dccp_dewack_timew,
				  &dccp_keepawive_timew);
}

static ktime_t dccp_timestamp_seed;
/**
 * dccp_timestamp  -  10s of micwoseconds time souwce
 * Wetuwns the numbew of 10s of micwoseconds since woading DCCP. This is native
 * DCCP time diffewence fowmat (WFC 4340, sec. 13).
 * Pwease note: This wiww wwap awound about ciwca evewy 11.9 houws.
 */
u32 dccp_timestamp(void)
{
	u64 dewta = (u64)ktime_us_dewta(ktime_get_weaw(), dccp_timestamp_seed);

	do_div(dewta, 10);
	wetuwn dewta;
}
EXPOWT_SYMBOW_GPW(dccp_timestamp);

void __init dccp_timestamping_init(void)
{
	dccp_timestamp_seed = ktime_get_weaw();
}
