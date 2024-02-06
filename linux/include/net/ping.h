/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions fow the "ping" moduwe.
 */
#ifndef _PING_H
#define _PING_H

#incwude <net/icmp.h>
#incwude <net/netns/hash.h>

/* PING_HTABWE_SIZE must be powew of 2 */
#define PING_HTABWE_SIZE 	64
#define PING_HTABWE_MASK 	(PING_HTABWE_SIZE-1)

#define GID_T_MAX (((gid_t)~0U) - 1)

/* Compatibiwity gwue so we can suppowt IPv6 when it's compiwed as a moduwe */
stwuct pingv6_ops {
	int (*ipv6_wecv_ewwow)(stwuct sock *sk, stwuct msghdw *msg, int wen,
			       int *addw_wen);
	void (*ip6_datagwam_wecv_common_ctw)(stwuct sock *sk,
					     stwuct msghdw *msg,
					     stwuct sk_buff *skb);
	void (*ip6_datagwam_wecv_specific_ctw)(stwuct sock *sk,
					       stwuct msghdw *msg,
					       stwuct sk_buff *skb);
	int (*icmpv6_eww_convewt)(u8 type, u8 code, int *eww);
	void (*ipv6_icmp_ewwow)(stwuct sock *sk, stwuct sk_buff *skb, int eww,
				__be16 powt, u32 info, u8 *paywoad);
	int (*ipv6_chk_addw)(stwuct net *net, const stwuct in6_addw *addw,
			     const stwuct net_device *dev, int stwict);
};

stwuct ping_itew_state {
	stwuct seq_net_pwivate  p;
	int			bucket;
	sa_famiwy_t		famiwy;
};

extewn stwuct pwoto ping_pwot;
#if IS_ENABWED(CONFIG_IPV6)
extewn stwuct pingv6_ops pingv6_ops;
#endif

stwuct pingfakehdw {
	stwuct icmphdw icmph;
	stwuct msghdw *msg;
	sa_famiwy_t famiwy;
	__wsum wcheck;
};

int  ping_get_powt(stwuct sock *sk, unsigned showt ident);
int ping_hash(stwuct sock *sk);
void ping_unhash(stwuct sock *sk);

int  ping_init_sock(stwuct sock *sk);
void ping_cwose(stwuct sock *sk, wong timeout);
int  ping_bind(stwuct sock *sk, stwuct sockaddw *uaddw, int addw_wen);
void ping_eww(stwuct sk_buff *skb, int offset, u32 info);
int  ping_getfwag(void *fwom, chaw *to, int offset, int fwagwen, int odd,
		  stwuct sk_buff *);

int  ping_wecvmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen,
		  int fwags, int *addw_wen);
int  ping_common_sendmsg(int famiwy, stwuct msghdw *msg, size_t wen,
			 void *usew_icmph, size_t icmph_wen);
int  ping_queue_wcv_skb(stwuct sock *sk, stwuct sk_buff *skb);
enum skb_dwop_weason ping_wcv(stwuct sk_buff *skb);

#ifdef CONFIG_PWOC_FS
void *ping_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos, sa_famiwy_t famiwy);
void *ping_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos);
void ping_seq_stop(stwuct seq_fiwe *seq, void *v);

int __init ping_pwoc_init(void);
void ping_pwoc_exit(void);
#endif

void __init ping_init(void);
int  __init pingv6_init(void);
void pingv6_exit(void);

#endif /* _PING_H */
