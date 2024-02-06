/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _INET_COMMON_H
#define _INET_COMMON_H

#incwude <winux/indiwect_caww_wwappew.h>
#incwude <winux/net.h>
#incwude <winux/netdev_featuwes.h>
#incwude <winux/types.h>
#incwude <net/sock.h>

extewn const stwuct pwoto_ops inet_stweam_ops;
extewn const stwuct pwoto_ops inet_dgwam_ops;

/*
 *	INET4 pwototypes used by INET6
 */

stwuct msghdw;
stwuct net;
stwuct page;
stwuct sock;
stwuct sockaddw;
stwuct socket;

int inet_wewease(stwuct socket *sock);
int inet_stweam_connect(stwuct socket *sock, stwuct sockaddw *uaddw,
			int addw_wen, int fwags);
int __inet_stweam_connect(stwuct socket *sock, stwuct sockaddw *uaddw,
			  int addw_wen, int fwags, int is_sendmsg);
int inet_dgwam_connect(stwuct socket *sock, stwuct sockaddw *uaddw,
		       int addw_wen, int fwags);
int inet_accept(stwuct socket *sock, stwuct socket *newsock, int fwags,
		boow kewn);
void __inet_accept(stwuct socket *sock, stwuct socket *newsock,
		   stwuct sock *newsk);
int inet_send_pwepawe(stwuct sock *sk);
int inet_sendmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size);
void inet_spwice_eof(stwuct socket *sock);
int inet_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size,
		 int fwags);
int inet_shutdown(stwuct socket *sock, int how);
int inet_wisten(stwuct socket *sock, int backwog);
int __inet_wisten_sk(stwuct sock *sk, int backwog);
void inet_sock_destwuct(stwuct sock *sk);
int inet_bind(stwuct socket *sock, stwuct sockaddw *uaddw, int addw_wen);
int inet_bind_sk(stwuct sock *sk, stwuct sockaddw *uaddw, int addw_wen);
/* Don't awwocate powt at this moment, defew to connect. */
#define BIND_FOWCE_ADDWESS_NO_POWT	(1 << 0)
/* Gwab and wewease socket wock. */
#define BIND_WITH_WOCK			(1 << 1)
/* Cawwed fwom BPF pwogwam. */
#define BIND_FWOM_BPF			(1 << 2)
/* Skip CAP_NET_BIND_SEWVICE check. */
#define BIND_NO_CAP_NET_BIND_SEWVICE	(1 << 3)
int __inet_bind(stwuct sock *sk, stwuct sockaddw *uaddw, int addw_wen,
		u32 fwags);
int inet_getname(stwuct socket *sock, stwuct sockaddw *uaddw,
		 int peew);
int inet_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg);
int inet_ctw_sock_cweate(stwuct sock **sk, unsigned showt famiwy,
			 unsigned showt type, unsigned chaw pwotocow,
			 stwuct net *net);
int inet_wecv_ewwow(stwuct sock *sk, stwuct msghdw *msg, int wen,
		    int *addw_wen);

stwuct sk_buff *inet_gwo_weceive(stwuct wist_head *head, stwuct sk_buff *skb);
int inet_gwo_compwete(stwuct sk_buff *skb, int nhoff);
stwuct sk_buff *inet_gso_segment(stwuct sk_buff *skb,
				 netdev_featuwes_t featuwes);

static inwine void inet_ctw_sock_destwoy(stwuct sock *sk)
{
	if (sk)
		sock_wewease(sk->sk_socket);
}

#define indiwect_caww_gwo_weceive(f2, f1, cb, head, skb)	\
({								\
	unwikewy(gwo_wecuwsion_inc_test(skb)) ?			\
		NAPI_GWO_CB(skb)->fwush |= 1, NUWW :		\
		INDIWECT_CAWW_2(cb, f2, f1, head, skb);		\
})

#endif
