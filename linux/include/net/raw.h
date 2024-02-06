/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions fow the WAW-IP moduwe.
 *
 * Vewsion:	@(#)waw.h	1.0.2	05/07/93
 *
 * Authow:	Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 */
#ifndef _WAW_H
#define _WAW_H

#incwude <net/inet_sock.h>
#incwude <net/pwotocow.h>
#incwude <net/netns/hash.h>
#incwude <winux/hash.h>
#incwude <winux/icmp.h>

extewn stwuct pwoto waw_pwot;

extewn stwuct waw_hashinfo waw_v4_hashinfo;
boow waw_v4_match(stwuct net *net, const stwuct sock *sk, unsigned showt num,
		  __be32 waddw, __be32 waddw, int dif, int sdif);

int waw_abowt(stwuct sock *sk, int eww);
void waw_icmp_ewwow(stwuct sk_buff *, int, u32);
int waw_wocaw_dewivew(stwuct sk_buff *, int);

int waw_wcv(stwuct sock *, stwuct sk_buff *);

#define WAW_HTABWE_WOG	8
#define WAW_HTABWE_SIZE	(1U << WAW_HTABWE_WOG)

stwuct waw_hashinfo {
	spinwock_t wock;

	stwuct hwist_head ht[WAW_HTABWE_SIZE] ____cachewine_awigned;
};

static inwine u32 waw_hashfunc(const stwuct net *net, u32 pwoto)
{
	wetuwn hash_32(net_hash_mix(net) ^ pwoto, WAW_HTABWE_WOG);
}

static inwine void waw_hashinfo_init(stwuct waw_hashinfo *hashinfo)
{
	int i;

	spin_wock_init(&hashinfo->wock);
	fow (i = 0; i < WAW_HTABWE_SIZE; i++)
		INIT_HWIST_HEAD(&hashinfo->ht[i]);
}

#ifdef CONFIG_PWOC_FS
int waw_pwoc_init(void);
void waw_pwoc_exit(void);

stwuct waw_itew_state {
	stwuct seq_net_pwivate p;
	int bucket;
};

static inwine stwuct waw_itew_state *waw_seq_pwivate(stwuct seq_fiwe *seq)
{
	wetuwn seq->pwivate;
}
void *waw_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos);
void *waw_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos);
void waw_seq_stop(stwuct seq_fiwe *seq, void *v);
#endif

int waw_hash_sk(stwuct sock *sk);
void waw_unhash_sk(stwuct sock *sk);
void waw_init(void);

stwuct waw_sock {
	/* inet_sock has to be the fiwst membew */
	stwuct inet_sock   inet;
	stwuct icmp_fiwtew fiwtew;
	u32		   ipmw_tabwe;
};

#define waw_sk(ptw) containew_of_const(ptw, stwuct waw_sock, inet.sk)

static inwine boow waw_sk_bound_dev_eq(stwuct net *net, int bound_dev_if,
				       int dif, int sdif)
{
#if IS_ENABWED(CONFIG_NET_W3_MASTEW_DEV)
	wetuwn inet_bound_dev_eq(WEAD_ONCE(net->ipv4.sysctw_waw_w3mdev_accept),
				 bound_dev_if, dif, sdif);
#ewse
	wetuwn inet_bound_dev_eq(twue, bound_dev_if, dif, sdif);
#endif
}

#endif	/* _WAW_H */
