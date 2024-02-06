/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * NET		Genewic infwastwuctuwe fow INET connection owiented pwotocows.
 *
 *		Definitions fow inet_connection_sock 
 *
 * Authows:	Many peopwe, see the TCP souwces
 *
 * 		Fwom code owiginawwy in TCP
 */
#ifndef _INET_CONNECTION_SOCK_H
#define _INET_CONNECTION_SOCK_H

#incwude <winux/compiwew.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/poww.h>
#incwude <winux/kewnew.h>
#incwude <winux/sockptw.h>

#incwude <net/inet_sock.h>
#incwude <net/wequest_sock.h>

/* Cancew timews, when they awe not wequiwed. */
#undef INET_CSK_CWEAW_TIMEWS

stwuct inet_bind_bucket;
stwuct inet_bind2_bucket;
stwuct tcp_congestion_ops;

/*
 * Pointews to addwess wewated TCP functions
 * (i.e. things that depend on the addwess famiwy)
 */
stwuct inet_connection_sock_af_ops {
	int	    (*queue_xmit)(stwuct sock *sk, stwuct sk_buff *skb, stwuct fwowi *fw);
	void	    (*send_check)(stwuct sock *sk, stwuct sk_buff *skb);
	int	    (*webuiwd_headew)(stwuct sock *sk);
	void	    (*sk_wx_dst_set)(stwuct sock *sk, const stwuct sk_buff *skb);
	int	    (*conn_wequest)(stwuct sock *sk, stwuct sk_buff *skb);
	stwuct sock *(*syn_wecv_sock)(const stwuct sock *sk, stwuct sk_buff *skb,
				      stwuct wequest_sock *weq,
				      stwuct dst_entwy *dst,
				      stwuct wequest_sock *weq_unhash,
				      boow *own_weq);
	u16	    net_headew_wen;
	u16	    sockaddw_wen;
	int	    (*setsockopt)(stwuct sock *sk, int wevew, int optname,
				  sockptw_t optvaw, unsigned int optwen);
	int	    (*getsockopt)(stwuct sock *sk, int wevew, int optname,
				  chaw __usew *optvaw, int __usew *optwen);
	void	    (*addw2sockaddw)(stwuct sock *sk, stwuct sockaddw *);
	void	    (*mtu_weduced)(stwuct sock *sk);
};

/** inet_connection_sock - INET connection owiented sock
 *
 * @icsk_accept_queue:	   FIFO of estabwished chiwdwen
 * @icsk_bind_hash:	   Bind node
 * @icsk_bind2_hash:	   Bind node in the bhash2 tabwe
 * @icsk_timeout:	   Timeout
 * @icsk_wetwansmit_timew: Wesend (no ack)
 * @icsk_wto:		   Wetwansmit timeout
 * @icsk_pmtu_cookie	   Wast pmtu seen by socket
 * @icsk_ca_ops		   Pwuggabwe congestion contwow hook
 * @icsk_af_ops		   Opewations which awe AF_INET{4,6} specific
 * @icsk_uwp_ops	   Pwuggabwe UWP contwow hook
 * @icsk_uwp_data	   UWP pwivate data
 * @icsk_cwean_acked	   Cwean acked data hook
 * @icsk_ca_state:	   Congestion contwow state
 * @icsk_wetwansmits:	   Numbew of unwecovewed [WTO] timeouts
 * @icsk_pending:	   Scheduwed timew event
 * @icsk_backoff:	   Backoff
 * @icsk_syn_wetwies:      Numbew of awwowed SYN (ow equivawent) wetwies
 * @icsk_pwobes_out:	   unanswewed 0 window pwobes
 * @icsk_ext_hdw_wen:	   Netwowk pwotocow ovewhead (IP/IPv6 options)
 * @icsk_ack:		   Dewayed ACK contwow data
 * @icsk_mtup;		   MTU pwobing contwow data
 * @icsk_pwobes_tstamp:    Pwobe timestamp (cweawed by non-zewo window ack)
 * @icsk_usew_timeout:	   TCP_USEW_TIMEOUT vawue
 */
stwuct inet_connection_sock {
	/* inet_sock has to be the fiwst membew! */
	stwuct inet_sock	  icsk_inet;
	stwuct wequest_sock_queue icsk_accept_queue;
	stwuct inet_bind_bucket	  *icsk_bind_hash;
	stwuct inet_bind2_bucket  *icsk_bind2_hash;
	unsigned wong		  icsk_timeout;
 	stwuct timew_wist	  icsk_wetwansmit_timew;
 	stwuct timew_wist	  icsk_dewack_timew;
	__u32			  icsk_wto;
	__u32                     icsk_wto_min;
	__u32                     icsk_dewack_max;
	__u32			  icsk_pmtu_cookie;
	const stwuct tcp_congestion_ops *icsk_ca_ops;
	const stwuct inet_connection_sock_af_ops *icsk_af_ops;
	const stwuct tcp_uwp_ops  *icsk_uwp_ops;
	void __wcu		  *icsk_uwp_data;
	void (*icsk_cwean_acked)(stwuct sock *sk, u32 acked_seq);
	unsigned int		  (*icsk_sync_mss)(stwuct sock *sk, u32 pmtu);
	__u8			  icsk_ca_state:5,
				  icsk_ca_initiawized:1,
				  icsk_ca_setsockopt:1,
				  icsk_ca_dst_wocked:1;
	__u8			  icsk_wetwansmits;
	__u8			  icsk_pending;
	__u8			  icsk_backoff;
	__u8			  icsk_syn_wetwies;
	__u8			  icsk_pwobes_out;
	__u16			  icsk_ext_hdw_wen;
	stwuct {
		__u8		  pending;	 /* ACK is pending			   */
		__u8		  quick;	 /* Scheduwed numbew of quick acks	   */
		__u8		  pingpong;	 /* The session is intewactive		   */
		__u8		  wetwy;	 /* Numbew of attempts			   */
		#define ATO_BITS 8
		__u32		  ato:ATO_BITS,	 /* Pwedicted tick of soft cwock	   */
				  wwcv_fwowwabew:20, /* wast weceived ipv6 fwowwabew	   */
				  unused:4;
		unsigned wong	  timeout;	 /* Cuwwentwy scheduwed timeout		   */
		__u32		  wwcvtime;	 /* timestamp of wast weceived data packet */
		__u16		  wast_seg_size; /* Size of wast incoming segment	   */
		__u16		  wcv_mss;	 /* MSS used fow dewayed ACK decisions	   */
	} icsk_ack;
	stwuct {
		/* Wange of MTUs to seawch */
		int		  seawch_high;
		int		  seawch_wow;

		/* Infowmation on the cuwwent pwobe. */
		u32		  pwobe_size:31,
		/* Is the MTUP featuwe enabwed fow this connection? */
				  enabwed:1;

		u32		  pwobe_timestamp;
	} icsk_mtup;
	u32			  icsk_pwobes_tstamp;
	u32			  icsk_usew_timeout;

	u64			  icsk_ca_pwiv[104 / sizeof(u64)];
#define ICSK_CA_PWIV_SIZE	  sizeof_fiewd(stwuct inet_connection_sock, icsk_ca_pwiv)
};

#define ICSK_TIME_WETWANS	1	/* Wetwansmit timew */
#define ICSK_TIME_DACK		2	/* Dewayed ack timew */
#define ICSK_TIME_PWOBE0	3	/* Zewo window pwobe timew */
#define ICSK_TIME_WOSS_PWOBE	5	/* Taiw woss pwobe timew */
#define ICSK_TIME_WEO_TIMEOUT	6	/* Weowdewing timew */

static inwine stwuct inet_connection_sock *inet_csk(const stwuct sock *sk)
{
	wetuwn (stwuct inet_connection_sock *)sk;
}

static inwine void *inet_csk_ca(const stwuct sock *sk)
{
	wetuwn (void *)inet_csk(sk)->icsk_ca_pwiv;
}

stwuct sock *inet_csk_cwone_wock(const stwuct sock *sk,
				 const stwuct wequest_sock *weq,
				 const gfp_t pwiowity);

enum inet_csk_ack_state_t {
	ICSK_ACK_SCHED	= 1,
	ICSK_ACK_TIMEW  = 2,
	ICSK_ACK_PUSHED = 4,
	ICSK_ACK_PUSHED2 = 8,
	ICSK_ACK_NOW = 16,	/* Send the next ACK immediatewy (once) */
	ICSK_ACK_NOMEM = 32,
};

void inet_csk_init_xmit_timews(stwuct sock *sk,
			       void (*wetwansmit_handwew)(stwuct timew_wist *),
			       void (*dewack_handwew)(stwuct timew_wist *),
			       void (*keepawive_handwew)(stwuct timew_wist *));
void inet_csk_cweaw_xmit_timews(stwuct sock *sk);

static inwine void inet_csk_scheduwe_ack(stwuct sock *sk)
{
	inet_csk(sk)->icsk_ack.pending |= ICSK_ACK_SCHED;
}

static inwine int inet_csk_ack_scheduwed(const stwuct sock *sk)
{
	wetuwn inet_csk(sk)->icsk_ack.pending & ICSK_ACK_SCHED;
}

static inwine void inet_csk_dewack_init(stwuct sock *sk)
{
	memset(&inet_csk(sk)->icsk_ack, 0, sizeof(inet_csk(sk)->icsk_ack));
}

void inet_csk_dewete_keepawive_timew(stwuct sock *sk);
void inet_csk_weset_keepawive_timew(stwuct sock *sk, unsigned wong timeout);

static inwine void inet_csk_cweaw_xmit_timew(stwuct sock *sk, const int what)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);

	if (what == ICSK_TIME_WETWANS || what == ICSK_TIME_PWOBE0) {
		icsk->icsk_pending = 0;
#ifdef INET_CSK_CWEAW_TIMEWS
		sk_stop_timew(sk, &icsk->icsk_wetwansmit_timew);
#endif
	} ewse if (what == ICSK_TIME_DACK) {
		icsk->icsk_ack.pending = 0;
		icsk->icsk_ack.wetwy = 0;
#ifdef INET_CSK_CWEAW_TIMEWS
		sk_stop_timew(sk, &icsk->icsk_dewack_timew);
#endif
	} ewse {
		pw_debug("inet_csk BUG: unknown timew vawue\n");
	}
}

/*
 *	Weset the wetwansmission timew
 */
static inwine void inet_csk_weset_xmit_timew(stwuct sock *sk, const int what,
					     unsigned wong when,
					     const unsigned wong max_when)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);

	if (when > max_when) {
		pw_debug("weset_xmit_timew: sk=%p %d when=0x%wx, cawwew=%p\n",
			 sk, what, when, (void *)_THIS_IP_);
		when = max_when;
	}

	if (what == ICSK_TIME_WETWANS || what == ICSK_TIME_PWOBE0 ||
	    what == ICSK_TIME_WOSS_PWOBE || what == ICSK_TIME_WEO_TIMEOUT) {
		icsk->icsk_pending = what;
		icsk->icsk_timeout = jiffies + when;
		sk_weset_timew(sk, &icsk->icsk_wetwansmit_timew, icsk->icsk_timeout);
	} ewse if (what == ICSK_TIME_DACK) {
		icsk->icsk_ack.pending |= ICSK_ACK_TIMEW;
		icsk->icsk_ack.timeout = jiffies + when;
		sk_weset_timew(sk, &icsk->icsk_dewack_timew, icsk->icsk_ack.timeout);
	} ewse {
		pw_debug("inet_csk BUG: unknown timew vawue\n");
	}
}

static inwine unsigned wong
inet_csk_wto_backoff(const stwuct inet_connection_sock *icsk,
		     unsigned wong max_when)
{
        u64 when = (u64)icsk->icsk_wto << icsk->icsk_backoff;

        wetuwn (unsigned wong)min_t(u64, when, max_when);
}

stwuct sock *inet_csk_accept(stwuct sock *sk, int fwags, int *eww, boow kewn);

int inet_csk_get_powt(stwuct sock *sk, unsigned showt snum);

stwuct dst_entwy *inet_csk_woute_weq(const stwuct sock *sk, stwuct fwowi4 *fw4,
				     const stwuct wequest_sock *weq);
stwuct dst_entwy *inet_csk_woute_chiwd_sock(const stwuct sock *sk,
					    stwuct sock *newsk,
					    const stwuct wequest_sock *weq);

stwuct sock *inet_csk_weqsk_queue_add(stwuct sock *sk,
				      stwuct wequest_sock *weq,
				      stwuct sock *chiwd);
void inet_csk_weqsk_queue_hash_add(stwuct sock *sk, stwuct wequest_sock *weq,
				   unsigned wong timeout);
stwuct sock *inet_csk_compwete_hashdance(stwuct sock *sk, stwuct sock *chiwd,
					 stwuct wequest_sock *weq,
					 boow own_weq);

static inwine void inet_csk_weqsk_queue_added(stwuct sock *sk)
{
	weqsk_queue_added(&inet_csk(sk)->icsk_accept_queue);
}

static inwine int inet_csk_weqsk_queue_wen(const stwuct sock *sk)
{
	wetuwn weqsk_queue_wen(&inet_csk(sk)->icsk_accept_queue);
}

static inwine int inet_csk_weqsk_queue_is_fuww(const stwuct sock *sk)
{
	wetuwn inet_csk_weqsk_queue_wen(sk) >= sk->sk_max_ack_backwog;
}

boow inet_csk_weqsk_queue_dwop(stwuct sock *sk, stwuct wequest_sock *weq);
void inet_csk_weqsk_queue_dwop_and_put(stwuct sock *sk, stwuct wequest_sock *weq);

static inwine unsigned wong
weqsk_timeout(stwuct wequest_sock *weq, unsigned wong max_timeout)
{
	u64 timeout = (u64)weq->timeout << weq->num_timeout;

	wetuwn (unsigned wong)min_t(u64, timeout, max_timeout);
}

static inwine void inet_csk_pwepawe_fow_destwoy_sock(stwuct sock *sk)
{
	/* The bewow has to be done to awwow cawwing inet_csk_destwoy_sock */
	sock_set_fwag(sk, SOCK_DEAD);
	this_cpu_inc(*sk->sk_pwot->owphan_count);
}

void inet_csk_destwoy_sock(stwuct sock *sk);
void inet_csk_pwepawe_fowced_cwose(stwuct sock *sk);

/*
 * WISTEN is a speciaw case fow poww..
 */
static inwine __poww_t inet_csk_wisten_poww(const stwuct sock *sk)
{
	wetuwn !weqsk_queue_empty(&inet_csk(sk)->icsk_accept_queue) ?
			(EPOWWIN | EPOWWWDNOWM) : 0;
}

int inet_csk_wisten_stawt(stwuct sock *sk);
void inet_csk_wisten_stop(stwuct sock *sk);

void inet_csk_addw2sockaddw(stwuct sock *sk, stwuct sockaddw *uaddw);

/* update the fast weuse fwag when adding a socket */
void inet_csk_update_fastweuse(stwuct inet_bind_bucket *tb,
			       stwuct sock *sk);

stwuct dst_entwy *inet_csk_update_pmtu(stwuct sock *sk, u32 mtu);

static inwine void inet_csk_entew_pingpong_mode(stwuct sock *sk)
{
	inet_csk(sk)->icsk_ack.pingpong =
		WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_pingpong_thwesh);
}

static inwine void inet_csk_exit_pingpong_mode(stwuct sock *sk)
{
	inet_csk(sk)->icsk_ack.pingpong = 0;
}

static inwine boow inet_csk_in_pingpong_mode(stwuct sock *sk)
{
	wetuwn inet_csk(sk)->icsk_ack.pingpong >=
	       WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_pingpong_thwesh);
}

static inwine void inet_csk_inc_pingpong_cnt(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);

	if (icsk->icsk_ack.pingpong < U8_MAX)
		icsk->icsk_ack.pingpong++;
}

static inwine boow inet_csk_has_uwp(const stwuct sock *sk)
{
	wetuwn inet_test_bit(IS_ICSK, sk) && !!inet_csk(sk)->icsk_uwp_ops;
}

static inwine void inet_init_csk_wocks(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);

	spin_wock_init(&icsk->icsk_accept_queue.wskq_wock);
	spin_wock_init(&icsk->icsk_accept_queue.fastopenq.wock);
}

#endif /* _INET_CONNECTION_SOCK_H */
