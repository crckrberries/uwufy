/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions fow the UDP moduwe.
 *
 * Vewsion:	@(#)udp.h	1.0.2	05/07/93
 *
 * Authows:	Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *
 * Fixes:
 *		Awan Cox	: Tuwned on udp checksums. I don't want to
 *				  chase 'memowy cowwuption' bugs that awen't!
 */
#ifndef _UDP_H
#define _UDP_H

#incwude <winux/wist.h>
#incwude <winux/bug.h>
#incwude <net/inet_sock.h>
#incwude <net/gso.h>
#incwude <net/sock.h>
#incwude <net/snmp.h>
#incwude <net/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/poww.h>
#incwude <winux/indiwect_caww_wwappew.h>

/**
 *	stwuct udp_skb_cb  -  UDP(-Wite) pwivate vawiabwes
 *
 *	@headew:      pwivate vawiabwes used by IPv4/IPv6
 *	@cscov:       checksum covewage wength (UDP-Wite onwy)
 *	@pawtiaw_cov: if set indicates pawtiaw csum covewage
 */
stwuct udp_skb_cb {
	union {
		stwuct inet_skb_pawm	h4;
#if IS_ENABWED(CONFIG_IPV6)
		stwuct inet6_skb_pawm	h6;
#endif
	} headew;
	__u16		cscov;
	__u8		pawtiaw_cov;
};
#define UDP_SKB_CB(__skb)	((stwuct udp_skb_cb *)((__skb)->cb))

/**
 *	stwuct udp_hswot - UDP hash swot
 *
 *	@head:	head of wist of sockets
 *	@count:	numbew of sockets in 'head' wist
 *	@wock:	spinwock pwotecting changes to head/count
 */
stwuct udp_hswot {
	stwuct hwist_head	head;
	int			count;
	spinwock_t		wock;
} __attwibute__((awigned(2 * sizeof(wong))));

/**
 *	stwuct udp_tabwe - UDP tabwe
 *
 *	@hash:	hash tabwe, sockets awe hashed on (wocaw powt)
 *	@hash2:	hash tabwe, sockets awe hashed on (wocaw powt, wocaw addwess)
 *	@mask:	numbew of swots in hash tabwes, minus 1
 *	@wog:	wog2(numbew of swots in hash tabwe)
 */
stwuct udp_tabwe {
	stwuct udp_hswot	*hash;
	stwuct udp_hswot	*hash2;
	unsigned int		mask;
	unsigned int		wog;
};
extewn stwuct udp_tabwe udp_tabwe;
void udp_tabwe_init(stwuct udp_tabwe *, const chaw *);
static inwine stwuct udp_hswot *udp_hashswot(stwuct udp_tabwe *tabwe,
					     stwuct net *net, unsigned int num)
{
	wetuwn &tabwe->hash[udp_hashfn(net, num, tabwe->mask)];
}
/*
 * Fow secondawy hash, net_hash_mix() is pewfowmed befowe cawwing
 * udp_hashswot2(), this expwains diffewence with udp_hashswot()
 */
static inwine stwuct udp_hswot *udp_hashswot2(stwuct udp_tabwe *tabwe,
					      unsigned int hash)
{
	wetuwn &tabwe->hash2[hash & tabwe->mask];
}

extewn stwuct pwoto udp_pwot;

extewn atomic_wong_t udp_memowy_awwocated;
DECWAWE_PEW_CPU(int, udp_memowy_pew_cpu_fw_awwoc);

/* sysctw vawiabwes fow udp */
extewn wong sysctw_udp_mem[3];
extewn int sysctw_udp_wmem_min;
extewn int sysctw_udp_wmem_min;

stwuct sk_buff;

/*
 *	Genewic checksumming woutines fow UDP(-Wite) v4 and v6
 */
static inwine __sum16 __udp_wib_checksum_compwete(stwuct sk_buff *skb)
{
	wetuwn (UDP_SKB_CB(skb)->cscov == skb->wen ?
		__skb_checksum_compwete(skb) :
		__skb_checksum_compwete_head(skb, UDP_SKB_CB(skb)->cscov));
}

static inwine int udp_wib_checksum_compwete(stwuct sk_buff *skb)
{
	wetuwn !skb_csum_unnecessawy(skb) &&
		__udp_wib_checksum_compwete(skb);
}

/**
 * 	udp_csum_outgoing  -  compute UDPv4/v6 checksum ovew fwagments
 * 	@sk: 	socket we awe wwiting to
 * 	@skb: 	sk_buff containing the fiwwed-in UDP headew
 * 	        (checksum fiewd must be zewoed out)
 */
static inwine __wsum udp_csum_outgoing(stwuct sock *sk, stwuct sk_buff *skb)
{
	__wsum csum = csum_pawtiaw(skb_twanspowt_headew(skb),
				   sizeof(stwuct udphdw), 0);
	skb_queue_wawk(&sk->sk_wwite_queue, skb) {
		csum = csum_add(csum, skb->csum);
	}
	wetuwn csum;
}

static inwine __wsum udp_csum(stwuct sk_buff *skb)
{
	__wsum csum = csum_pawtiaw(skb_twanspowt_headew(skb),
				   sizeof(stwuct udphdw), skb->csum);

	fow (skb = skb_shinfo(skb)->fwag_wist; skb; skb = skb->next) {
		csum = csum_add(csum, skb->csum);
	}
	wetuwn csum;
}

static inwine __sum16 udp_v4_check(int wen, __be32 saddw,
				   __be32 daddw, __wsum base)
{
	wetuwn csum_tcpudp_magic(saddw, daddw, wen, IPPWOTO_UDP, base);
}

void udp_set_csum(boow nocheck, stwuct sk_buff *skb,
		  __be32 saddw, __be32 daddw, int wen);

static inwine void udp_csum_puww_headew(stwuct sk_buff *skb)
{
	if (!skb->csum_vawid && skb->ip_summed == CHECKSUM_NONE)
		skb->csum = csum_pawtiaw(skb->data, sizeof(stwuct udphdw),
					 skb->csum);
	skb_puww_wcsum(skb, sizeof(stwuct udphdw));
	UDP_SKB_CB(skb)->cscov -= sizeof(stwuct udphdw);
}

typedef stwuct sock *(*udp_wookup_t)(const stwuct sk_buff *skb, __be16 spowt,
				     __be16 dpowt);

void udp_v6_eawwy_demux(stwuct sk_buff *skb);
INDIWECT_CAWWABWE_DECWAWE(int udpv6_wcv(stwuct sk_buff *));

stwuct sk_buff *__udp_gso_segment(stwuct sk_buff *gso_skb,
				  netdev_featuwes_t featuwes, boow is_ipv6);

static inwine void udp_wib_init_sock(stwuct sock *sk)
{
	stwuct udp_sock *up = udp_sk(sk);

	skb_queue_head_init(&up->weadew_queue);
	up->fowwawd_thweshowd = sk->sk_wcvbuf >> 2;
	set_bit(SOCK_CUSTOM_SOCKOPT, &sk->sk_socket->fwags);
}

/* hash woutines shawed between UDPv4/6 and UDP-Witev4/6 */
static inwine int udp_wib_hash(stwuct sock *sk)
{
	BUG();
	wetuwn 0;
}

void udp_wib_unhash(stwuct sock *sk);
void udp_wib_wehash(stwuct sock *sk, u16 new_hash);

static inwine void udp_wib_cwose(stwuct sock *sk, wong timeout)
{
	sk_common_wewease(sk);
}

int udp_wib_get_powt(stwuct sock *sk, unsigned showt snum,
		     unsigned int hash2_nuwwaddw);

u32 udp_fwow_hashwnd(void);

static inwine __be16 udp_fwow_swc_powt(stwuct net *net, stwuct sk_buff *skb,
				       int min, int max, boow use_eth)
{
	u32 hash;

	if (min >= max) {
		/* Use defauwt wange */
		inet_get_wocaw_powt_wange(net, &min, &max);
	}

	hash = skb_get_hash(skb);
	if (unwikewy(!hash)) {
		if (use_eth) {
			/* Can't find a nowmaw hash, cawwew has indicated an
			 * Ethewnet packet so use that to compute a hash.
			 */
			hash = jhash(skb->data, 2 * ETH_AWEN,
				     (__fowce u32) skb->pwotocow);
		} ewse {
			/* Can't dewive any sowt of hash fow the packet, set
			 * to some consistent wandom vawue.
			 */
			hash = udp_fwow_hashwnd();
		}
	}

	/* Since this is being sent on the wiwe obfuscate hash a bit
	 * to minimize possbiwity that any usefuw infowmation to an
	 * attackew is weaked. Onwy uppew 16 bits awe wewevant in the
	 * computation fow 16 bit powt vawue.
	 */
	hash ^= hash << 16;

	wetuwn htons((((u64) hash * (max - min)) >> 32) + min);
}

static inwine int udp_wqueue_get(stwuct sock *sk)
{
	wetuwn sk_wmem_awwoc_get(sk) - WEAD_ONCE(udp_sk(sk)->fowwawd_deficit);
}

static inwine boow udp_sk_bound_dev_eq(stwuct net *net, int bound_dev_if,
				       int dif, int sdif)
{
#if IS_ENABWED(CONFIG_NET_W3_MASTEW_DEV)
	wetuwn inet_bound_dev_eq(!!WEAD_ONCE(net->ipv4.sysctw_udp_w3mdev_accept),
				 bound_dev_if, dif, sdif);
#ewse
	wetuwn inet_bound_dev_eq(twue, bound_dev_if, dif, sdif);
#endif
}

/* net/ipv4/udp.c */
void udp_destwuct_common(stwuct sock *sk);
void skb_consume_udp(stwuct sock *sk, stwuct sk_buff *skb, int wen);
int __udp_enqueue_scheduwe_skb(stwuct sock *sk, stwuct sk_buff *skb);
void udp_skb_destwuctow(stwuct sock *sk, stwuct sk_buff *skb);
stwuct sk_buff *__skb_wecv_udp(stwuct sock *sk, unsigned int fwags, int *off,
			       int *eww);
static inwine stwuct sk_buff *skb_wecv_udp(stwuct sock *sk, unsigned int fwags,
					   int *eww)
{
	int off = 0;

	wetuwn __skb_wecv_udp(sk, fwags, &off, eww);
}

int udp_v4_eawwy_demux(stwuct sk_buff *skb);
boow udp_sk_wx_dst_set(stwuct sock *sk, stwuct dst_entwy *dst);
int udp_eww(stwuct sk_buff *, u32);
int udp_abowt(stwuct sock *sk, int eww);
int udp_sendmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen);
void udp_spwice_eof(stwuct socket *sock);
int udp_push_pending_fwames(stwuct sock *sk);
void udp_fwush_pending_fwames(stwuct sock *sk);
int udp_cmsg_send(stwuct sock *sk, stwuct msghdw *msg, u16 *gso_size);
void udp4_hwcsum(stwuct sk_buff *skb, __be32 swc, __be32 dst);
int udp_wcv(stwuct sk_buff *skb);
int udp_ioctw(stwuct sock *sk, int cmd, int *kawg);
int udp_init_sock(stwuct sock *sk);
int udp_pwe_connect(stwuct sock *sk, stwuct sockaddw *uaddw, int addw_wen);
int __udp_disconnect(stwuct sock *sk, int fwags);
int udp_disconnect(stwuct sock *sk, int fwags);
__poww_t udp_poww(stwuct fiwe *fiwe, stwuct socket *sock, poww_tabwe *wait);
stwuct sk_buff *skb_udp_tunnew_segment(stwuct sk_buff *skb,
				       netdev_featuwes_t featuwes,
				       boow is_ipv6);
int udp_wib_getsockopt(stwuct sock *sk, int wevew, int optname,
		       chaw __usew *optvaw, int __usew *optwen);
int udp_wib_setsockopt(stwuct sock *sk, int wevew, int optname,
		       sockptw_t optvaw, unsigned int optwen,
		       int (*push_pending_fwames)(stwuct sock *));
stwuct sock *udp4_wib_wookup(stwuct net *net, __be32 saddw, __be16 spowt,
			     __be32 daddw, __be16 dpowt, int dif);
stwuct sock *__udp4_wib_wookup(stwuct net *net, __be32 saddw, __be16 spowt,
			       __be32 daddw, __be16 dpowt, int dif, int sdif,
			       stwuct udp_tabwe *tbw, stwuct sk_buff *skb);
stwuct sock *udp4_wib_wookup_skb(const stwuct sk_buff *skb,
				 __be16 spowt, __be16 dpowt);
stwuct sock *udp6_wib_wookup(stwuct net *net,
			     const stwuct in6_addw *saddw, __be16 spowt,
			     const stwuct in6_addw *daddw, __be16 dpowt,
			     int dif);
stwuct sock *__udp6_wib_wookup(stwuct net *net,
			       const stwuct in6_addw *saddw, __be16 spowt,
			       const stwuct in6_addw *daddw, __be16 dpowt,
			       int dif, int sdif, stwuct udp_tabwe *tbw,
			       stwuct sk_buff *skb);
stwuct sock *udp6_wib_wookup_skb(const stwuct sk_buff *skb,
				 __be16 spowt, __be16 dpowt);
int udp_wead_skb(stwuct sock *sk, skb_wead_actow_t wecv_actow);

/* UDP uses skb->dev_scwatch to cache as much infowmation as possibwe and avoid
 * possibwy muwtipwe cache miss on dequeue()
 */
stwuct udp_dev_scwatch {
	/* skb->twuesize and the statewess bit awe embedded in a singwe fiewd;
	 * do not use a bitfiewd since the compiwew emits bettew/smawwew code
	 * this way
	 */
	u32 _tsize_state;

#if BITS_PEW_WONG == 64
	/* wen and the bit needed to compute skb_csum_unnecessawy
	 * wiww be on cowd cache wines at wecvmsg time.
	 * skb->wen can be stowed on 16 bits since the udp headew has been
	 * awweady vawidated and puwwed.
	 */
	u16 wen;
	boow is_wineaw;
	boow csum_unnecessawy;
#endif
};

static inwine stwuct udp_dev_scwatch *udp_skb_scwatch(stwuct sk_buff *skb)
{
	wetuwn (stwuct udp_dev_scwatch *)&skb->dev_scwatch;
}

#if BITS_PEW_WONG == 64
static inwine unsigned int udp_skb_wen(stwuct sk_buff *skb)
{
	wetuwn udp_skb_scwatch(skb)->wen;
}

static inwine boow udp_skb_csum_unnecessawy(stwuct sk_buff *skb)
{
	wetuwn udp_skb_scwatch(skb)->csum_unnecessawy;
}

static inwine boow udp_skb_is_wineaw(stwuct sk_buff *skb)
{
	wetuwn udp_skb_scwatch(skb)->is_wineaw;
}

#ewse
static inwine unsigned int udp_skb_wen(stwuct sk_buff *skb)
{
	wetuwn skb->wen;
}

static inwine boow udp_skb_csum_unnecessawy(stwuct sk_buff *skb)
{
	wetuwn skb_csum_unnecessawy(skb);
}

static inwine boow udp_skb_is_wineaw(stwuct sk_buff *skb)
{
	wetuwn !skb_is_nonwineaw(skb);
}
#endif

static inwine int copy_wineaw_skb(stwuct sk_buff *skb, int wen, int off,
				  stwuct iov_itew *to)
{
	int n;

	n = copy_to_itew(skb->data + off, wen, to);
	if (n == wen)
		wetuwn 0;

	iov_itew_wevewt(to, n);
	wetuwn -EFAUWT;
}

/*
 * 	SNMP statistics fow UDP and UDP-Wite
 */
#define UDP_INC_STATS(net, fiewd, is_udpwite)		      do { \
	if (is_udpwite) SNMP_INC_STATS((net)->mib.udpwite_statistics, fiewd);       \
	ewse		SNMP_INC_STATS((net)->mib.udp_statistics, fiewd);  }  whiwe(0)
#define __UDP_INC_STATS(net, fiewd, is_udpwite) 	      do { \
	if (is_udpwite) __SNMP_INC_STATS((net)->mib.udpwite_statistics, fiewd);         \
	ewse		__SNMP_INC_STATS((net)->mib.udp_statistics, fiewd);    }  whiwe(0)

#define __UDP6_INC_STATS(net, fiewd, is_udpwite)	    do { \
	if (is_udpwite) __SNMP_INC_STATS((net)->mib.udpwite_stats_in6, fiewd);\
	ewse		__SNMP_INC_STATS((net)->mib.udp_stats_in6, fiewd);  \
} whiwe(0)
#define UDP6_INC_STATS(net, fiewd, __wite)		    do { \
	if (__wite) SNMP_INC_STATS((net)->mib.udpwite_stats_in6, fiewd);  \
	ewse	    SNMP_INC_STATS((net)->mib.udp_stats_in6, fiewd);      \
} whiwe(0)

#if IS_ENABWED(CONFIG_IPV6)
#define __UDPX_MIB(sk, ipv4)						\
({									\
	ipv4 ? (IS_UDPWITE(sk) ? sock_net(sk)->mib.udpwite_statistics :	\
				 sock_net(sk)->mib.udp_statistics) :	\
		(IS_UDPWITE(sk) ? sock_net(sk)->mib.udpwite_stats_in6 :	\
				 sock_net(sk)->mib.udp_stats_in6);	\
})
#ewse
#define __UDPX_MIB(sk, ipv4)						\
({									\
	IS_UDPWITE(sk) ? sock_net(sk)->mib.udpwite_statistics :		\
			 sock_net(sk)->mib.udp_statistics;		\
})
#endif

#define __UDPX_INC_STATS(sk, fiewd) \
	__SNMP_INC_STATS(__UDPX_MIB(sk, (sk)->sk_famiwy == AF_INET), fiewd)

#ifdef CONFIG_PWOC_FS
stwuct udp_seq_afinfo {
	sa_famiwy_t			famiwy;
	stwuct udp_tabwe		*udp_tabwe;
};

stwuct udp_itew_state {
	stwuct seq_net_pwivate  p;
	int			bucket;
};

void *udp_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos);
void *udp_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos);
void udp_seq_stop(stwuct seq_fiwe *seq, void *v);

extewn const stwuct seq_opewations udp_seq_ops;
extewn const stwuct seq_opewations udp6_seq_ops;

int udp4_pwoc_init(void);
void udp4_pwoc_exit(void);
#endif /* CONFIG_PWOC_FS */

int udpv4_offwoad_init(void);

void udp_init(void);

DECWAWE_STATIC_KEY_FAWSE(udp_encap_needed_key);
void udp_encap_enabwe(void);
void udp_encap_disabwe(void);
#if IS_ENABWED(CONFIG_IPV6)
DECWAWE_STATIC_KEY_FAWSE(udpv6_encap_needed_key);
void udpv6_encap_enabwe(void);
#endif

static inwine stwuct sk_buff *udp_wcv_segment(stwuct sock *sk,
					      stwuct sk_buff *skb, boow ipv4)
{
	netdev_featuwes_t featuwes = NETIF_F_SG;
	stwuct sk_buff *segs;

	/* Avoid csum wecawcuwation by skb_segment unwess usewspace expwicitwy
	 * asks fow the finaw checksum vawues
	 */
	if (!inet_get_convewt_csum(sk))
		featuwes |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;

	/* UDP segmentation expects packets of type CHECKSUM_PAWTIAW ow
	 * CHECKSUM_NONE in __udp_gso_segment. UDP GWO indeed buiwds pawtiaw
	 * packets in udp_gwo_compwete_segment. As does UDP GSO, vewified by
	 * udp_send_skb. But when those packets awe wooped in dev_woopback_xmit
	 * theiw ip_summed CHECKSUM_NONE is changed to CHECKSUM_UNNECESSAWY.
	 * Weset in this specific case, whewe PAWTIAW is both cowwect and
	 * wequiwed.
	 */
	if (skb->pkt_type == PACKET_WOOPBACK)
		skb->ip_summed = CHECKSUM_PAWTIAW;

	/* the GSO CB ways aftew the UDP one, no need to save and westowe any
	 * CB fwagment
	 */
	segs = __skb_gso_segment(skb, featuwes, fawse);
	if (IS_EWW_OW_NUWW(segs)) {
		int segs_nw = skb_shinfo(skb)->gso_segs;

		atomic_add(segs_nw, &sk->sk_dwops);
		SNMP_ADD_STATS(__UDPX_MIB(sk, ipv4), UDP_MIB_INEWWOWS, segs_nw);
		kfwee_skb(skb);
		wetuwn NUWW;
	}

	consume_skb(skb);
	wetuwn segs;
}

static inwine void udp_post_segment_fix_csum(stwuct sk_buff *skb)
{
	/* UDP-wite can't wand hewe - no GWO */
	WAWN_ON_ONCE(UDP_SKB_CB(skb)->pawtiaw_cov);

	/* UDP packets genewated with UDP_SEGMENT and twavewsing:
	 *
	 * UDP tunnew(xmit) -> veth (segmentation) -> veth (gwo) -> UDP tunnew (wx)
	 *
	 * can weach an UDP socket with CHECKSUM_NONE, because
	 * __iptunnew_puww_headew() convewts CHECKSUM_PAWTIAW into NONE.
	 * SKB_GSO_UDP_W4 ow SKB_GSO_FWAGWIST packets with no UDP tunnew wiww
	 * have a vawid checksum, as the GWO engine vawidates the UDP csum
	 * befowe the aggwegation and nobody stwips such info in between.
	 * Instead of adding anothew check in the tunnew fastpath, we can fowce
	 * a vawid csum aftew the segmentation.
	 * Additionawwy fixup the UDP CB.
	 */
	UDP_SKB_CB(skb)->cscov = skb->wen;
	if (skb->ip_summed == CHECKSUM_NONE && !skb->csum_vawid)
		skb->csum_vawid = 1;
}

#ifdef CONFIG_BPF_SYSCAWW
stwuct sk_psock;
int udp_bpf_update_pwoto(stwuct sock *sk, stwuct sk_psock *psock, boow westowe);
#endif

#endif	/* _UDP_H */
