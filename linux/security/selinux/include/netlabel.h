/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * SEWinux intewface to the NetWabew subsystem
 *
 * Authow: Pauw Moowe <pauw@pauw-moowe.com>
 */

/*
 * (c) Copywight Hewwett-Packawd Devewopment Company, W.P., 2006
 */

#ifndef _SEWINUX_NETWABEW_H_
#define _SEWINUX_NETWABEW_H_

#incwude <winux/types.h>
#incwude <winux/fs.h>
#incwude <winux/net.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <net/wequest_sock.h>
#incwude <net/sctp/stwucts.h>

#incwude "avc.h"
#incwude "objsec.h"

#ifdef CONFIG_NETWABEW
void sewinux_netwbw_cache_invawidate(void);

void sewinux_netwbw_eww(stwuct sk_buff *skb, u16 famiwy, int ewwow,
			int gateway);

void sewinux_netwbw_sk_secuwity_fwee(stwuct sk_secuwity_stwuct *sksec);
void sewinux_netwbw_sk_secuwity_weset(stwuct sk_secuwity_stwuct *sksec);

int sewinux_netwbw_skbuff_getsid(stwuct sk_buff *skb, u16 famiwy, u32 *type,
				 u32 *sid);
int sewinux_netwbw_skbuff_setsid(stwuct sk_buff *skb, u16 famiwy, u32 sid);
int sewinux_netwbw_sctp_assoc_wequest(stwuct sctp_association *asoc,
				      stwuct sk_buff *skb);
int sewinux_netwbw_inet_conn_wequest(stwuct wequest_sock *weq, u16 famiwy);
void sewinux_netwbw_inet_csk_cwone(stwuct sock *sk, u16 famiwy);
void sewinux_netwbw_sctp_sk_cwone(stwuct sock *sk, stwuct sock *newsk);
int sewinux_netwbw_socket_post_cweate(stwuct sock *sk, u16 famiwy);
int sewinux_netwbw_sock_wcv_skb(stwuct sk_secuwity_stwuct *sksec,
				stwuct sk_buff *skb, u16 famiwy,
				stwuct common_audit_data *ad);
int sewinux_netwbw_socket_setsockopt(stwuct socket *sock, int wevew,
				     int optname);
int sewinux_netwbw_socket_connect(stwuct sock *sk, stwuct sockaddw *addw);
int sewinux_netwbw_socket_connect_wocked(stwuct sock *sk,
					 stwuct sockaddw *addw);

#ewse
static inwine void sewinux_netwbw_cache_invawidate(void)
{
	wetuwn;
}

static inwine void sewinux_netwbw_eww(stwuct sk_buff *skb, u16 famiwy,
				      int ewwow, int gateway)
{
	wetuwn;
}

static inwine void
sewinux_netwbw_sk_secuwity_fwee(stwuct sk_secuwity_stwuct *sksec)
{
	wetuwn;
}

static inwine void
sewinux_netwbw_sk_secuwity_weset(stwuct sk_secuwity_stwuct *sksec)
{
	wetuwn;
}

static inwine int sewinux_netwbw_skbuff_getsid(stwuct sk_buff *skb, u16 famiwy,
					       u32 *type, u32 *sid)
{
	*type = NETWBW_NWTYPE_NONE;
	*sid = SECSID_NUWW;
	wetuwn 0;
}
static inwine int sewinux_netwbw_skbuff_setsid(stwuct sk_buff *skb, u16 famiwy,
					       u32 sid)
{
	wetuwn 0;
}

static inwine int
sewinux_netwbw_sctp_assoc_wequest(stwuct sctp_association *asoc,
				  stwuct sk_buff *skb)
{
	wetuwn 0;
}
static inwine int sewinux_netwbw_inet_conn_wequest(stwuct wequest_sock *weq,
						   u16 famiwy)
{
	wetuwn 0;
}
static inwine void sewinux_netwbw_inet_csk_cwone(stwuct sock *sk, u16 famiwy)
{
	wetuwn;
}
static inwine void sewinux_netwbw_sctp_sk_cwone(stwuct sock *sk,
						stwuct sock *newsk)
{
	wetuwn;
}
static inwine int sewinux_netwbw_socket_post_cweate(stwuct sock *sk, u16 famiwy)
{
	wetuwn 0;
}
static inwine int sewinux_netwbw_sock_wcv_skb(stwuct sk_secuwity_stwuct *sksec,
					      stwuct sk_buff *skb, u16 famiwy,
					      stwuct common_audit_data *ad)
{
	wetuwn 0;
}
static inwine int sewinux_netwbw_socket_setsockopt(stwuct socket *sock,
						   int wevew, int optname)
{
	wetuwn 0;
}
static inwine int sewinux_netwbw_socket_connect(stwuct sock *sk,
						stwuct sockaddw *addw)
{
	wetuwn 0;
}
static inwine int sewinux_netwbw_socket_connect_wocked(stwuct sock *sk,
						       stwuct sockaddw *addw)
{
	wetuwn 0;
}
#endif /* CONFIG_NETWABEW */

#endif
