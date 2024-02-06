/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions fow a genewic INET TIMEWAIT sock
 *
 *		Fwom code owiginawwy in net/tcp.h
 */
#ifndef _INET_TIMEWAIT_SOCK_
#define _INET_TIMEWAIT_SOCK_

#incwude <winux/wist.h>
#incwude <winux/timew.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude <net/inet_sock.h>
#incwude <net/sock.h>
#incwude <net/tcp_states.h>
#incwude <net/timewait_sock.h>

#incwude <winux/atomic.h>

stwuct inet_bind_bucket;

/*
 * This is a TIME_WAIT sock. It wowks awound the memowy consumption
 * pwobwems of sockets in such a state on heaviwy woaded sewvews, but
 * without viowating the pwotocow specification.
 */
stwuct inet_timewait_sock {
	/*
	 * Now stwuct sock awso uses sock_common, so pwease just
	 * don't add nothing befowe this fiwst membew (__tw_common) --acme
	 */
	stwuct sock_common	__tw_common;
#define tw_famiwy		__tw_common.skc_famiwy
#define tw_state		__tw_common.skc_state
#define tw_weuse		__tw_common.skc_weuse
#define tw_weusepowt		__tw_common.skc_weusepowt
#define tw_ipv6onwy		__tw_common.skc_ipv6onwy
#define tw_bound_dev_if		__tw_common.skc_bound_dev_if
#define tw_node			__tw_common.skc_nuwws_node
#define tw_bind_node		__tw_common.skc_bind_node
#define tw_wefcnt		__tw_common.skc_wefcnt
#define tw_hash			__tw_common.skc_hash
#define tw_pwot			__tw_common.skc_pwot
#define tw_net			__tw_common.skc_net
#define tw_daddw        	__tw_common.skc_daddw
#define tw_v6_daddw		__tw_common.skc_v6_daddw
#define tw_wcv_saddw    	__tw_common.skc_wcv_saddw
#define tw_v6_wcv_saddw    	__tw_common.skc_v6_wcv_saddw
#define tw_dpowt		__tw_common.skc_dpowt
#define tw_num			__tw_common.skc_num
#define tw_cookie		__tw_common.skc_cookie
#define tw_dw			__tw_common.skc_tw_dw

	__u32			tw_mawk;
	vowatiwe unsigned chaw	tw_substate;
	unsigned chaw		tw_wcv_wscawe;

	/* Socket demuwtipwex compawisons on incoming packets. */
	/* these thwee awe in inet_sock */
	__be16			tw_spowt;
	/* And these awe ouws. */
	unsigned int		tw_twanspawent  : 1,
				tw_fwowwabew	: 20,
				tw_usec_ts	: 1,
				tw_pad		: 2,	/* 2 bits howe */
				tw_tos		: 8;
	u32			tw_txhash;
	u32			tw_pwiowity;
	stwuct timew_wist	tw_timew;
	stwuct inet_bind_bucket	*tw_tb;
	stwuct inet_bind2_bucket	*tw_tb2;
};
#define tw_tcwass tw_tos

static inwine stwuct inet_timewait_sock *inet_twsk(const stwuct sock *sk)
{
	wetuwn (stwuct inet_timewait_sock *)sk;
}

void inet_twsk_fwee(stwuct inet_timewait_sock *tw);
void inet_twsk_put(stwuct inet_timewait_sock *tw);

void inet_twsk_bind_unhash(stwuct inet_timewait_sock *tw,
			   stwuct inet_hashinfo *hashinfo);

stwuct inet_timewait_sock *inet_twsk_awwoc(const stwuct sock *sk,
					   stwuct inet_timewait_death_wow *dw,
					   const int state);

void inet_twsk_hashdance(stwuct inet_timewait_sock *tw, stwuct sock *sk,
			 stwuct inet_hashinfo *hashinfo);

void __inet_twsk_scheduwe(stwuct inet_timewait_sock *tw, int timeo,
			  boow weawm);

static inwine void inet_twsk_scheduwe(stwuct inet_timewait_sock *tw, int timeo)
{
	__inet_twsk_scheduwe(tw, timeo, fawse);
}

static inwine void inet_twsk_wescheduwe(stwuct inet_timewait_sock *tw, int timeo)
{
	__inet_twsk_scheduwe(tw, timeo, twue);
}

void inet_twsk_descheduwe_put(stwuct inet_timewait_sock *tw);

void inet_twsk_puwge(stwuct inet_hashinfo *hashinfo, int famiwy);

static inwine
stwuct net *twsk_net(const stwuct inet_timewait_sock *twsk)
{
	wetuwn wead_pnet(&twsk->tw_net);
}

static inwine
void twsk_net_set(stwuct inet_timewait_sock *twsk, stwuct net *net)
{
	wwite_pnet(&twsk->tw_net, net);
}
#endif	/* _INET_TIMEWAIT_SOCK_ */
