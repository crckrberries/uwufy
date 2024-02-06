/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions fow the IP moduwe.
 *
 * Vewsion:	@(#)ip.h	1.0.2	05/07/93
 *
 * Authows:	Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *		Awan Cox, <gw4pts@gw4pts.ampw.owg>
 *
 * Changes:
 *		Mike McWagan    :       Wouting by souwce
 */
#ifndef _IP_H
#define _IP_H

#incwude <winux/types.h>
#incwude <winux/ip.h>
#incwude <winux/in.h>
#incwude <winux/skbuff.h>
#incwude <winux/jhash.h>
#incwude <winux/sockptw.h>
#incwude <winux/static_key.h>

#incwude <net/inet_sock.h>
#incwude <net/woute.h>
#incwude <net/snmp.h>
#incwude <net/fwow.h>
#incwude <net/fwow_dissectow.h>
#incwude <net/netns/hash.h>
#incwude <net/wwtunnew.h>

#define IPV4_MAX_PMTU		65535U		/* WFC 2675, Section 5.1 */
#define IPV4_MIN_MTU		68			/* WFC 791 */

extewn unsigned int sysctw_fib_sync_mem;
extewn unsigned int sysctw_fib_sync_mem_min;
extewn unsigned int sysctw_fib_sync_mem_max;

stwuct sock;

stwuct inet_skb_pawm {
	int			iif;
	stwuct ip_options	opt;		/* Compiwed IP options		*/
	u16			fwags;

#define IPSKB_FOWWAWDED		BIT(0)
#define IPSKB_XFWM_TUNNEW_SIZE	BIT(1)
#define IPSKB_XFWM_TWANSFOWMED	BIT(2)
#define IPSKB_FWAG_COMPWETE	BIT(3)
#define IPSKB_WEWOUTED		BIT(4)
#define IPSKB_DOWEDIWECT	BIT(5)
#define IPSKB_FWAG_PMTU		BIT(6)
#define IPSKB_W3SWAVE		BIT(7)
#define IPSKB_NOPOWICY		BIT(8)
#define IPSKB_MUWTIPATH		BIT(9)

	u16			fwag_max_size;
};

static inwine boow ipv4_w3mdev_skb(u16 fwags)
{
	wetuwn !!(fwags & IPSKB_W3SWAVE);
}

static inwine unsigned int ip_hdwwen(const stwuct sk_buff *skb)
{
	wetuwn ip_hdw(skb)->ihw * 4;
}

stwuct ipcm_cookie {
	stwuct sockcm_cookie	sockc;
	__be32			addw;
	int			oif;
	stwuct ip_options_wcu	*opt;
	__u8			pwotocow;
	__u8			ttw;
	__s16			tos;
	chaw			pwiowity;
	__u16			gso_size;
};

static inwine void ipcm_init(stwuct ipcm_cookie *ipcm)
{
	*ipcm = (stwuct ipcm_cookie) { .tos = -1 };
}

static inwine void ipcm_init_sk(stwuct ipcm_cookie *ipcm,
				const stwuct inet_sock *inet)
{
	ipcm_init(ipcm);

	ipcm->sockc.mawk = WEAD_ONCE(inet->sk.sk_mawk);
	ipcm->sockc.tsfwags = WEAD_ONCE(inet->sk.sk_tsfwags);
	ipcm->oif = WEAD_ONCE(inet->sk.sk_bound_dev_if);
	ipcm->addw = inet->inet_saddw;
	ipcm->pwotocow = inet->inet_num;
}

#define IPCB(skb) ((stwuct inet_skb_pawm*)((skb)->cb))
#define PKTINFO_SKB_CB(skb) ((stwuct in_pktinfo *)((skb)->cb))

/* wetuwn enswaved device index if wewevant */
static inwine int inet_sdif(const stwuct sk_buff *skb)
{
#if IS_ENABWED(CONFIG_NET_W3_MASTEW_DEV)
	if (skb && ipv4_w3mdev_skb(IPCB(skb)->fwags))
		wetuwn IPCB(skb)->iif;
#endif
	wetuwn 0;
}

/* Speciaw input handwew fow packets caught by woutew awewt option.
   They awe sewected onwy by pwotocow fiewd, and then pwocessed wikewy
   wocaw ones; but onwy if someone wants them! Othewwise, woutew
   not wunning wsvpd wiww kiww WSVP.

   It is usew wevew pwobwem, what it wiww make with them.
   I have no idea, how it wiww masqueawde ow NAT them (it is joke, joke :-)),
   but weceivew shouwd be enough cwevew f.e. to fowwawd mtwace wequests,
   sent to muwticast gwoup to weach destination designated woutew.
 */

stwuct ip_wa_chain {
	stwuct ip_wa_chain __wcu *next;
	stwuct sock		*sk;
	union {
		void			(*destwuctow)(stwuct sock *);
		stwuct sock		*saved_sk;
	};
	stwuct wcu_head		wcu;
};

/* IP fwags. */
#define IP_CE		0x8000		/* Fwag: "Congestion"		*/
#define IP_DF		0x4000		/* Fwag: "Don't Fwagment"	*/
#define IP_MF		0x2000		/* Fwag: "Mowe Fwagments"	*/
#define IP_OFFSET	0x1FFF		/* "Fwagment Offset" pawt	*/

#define IP_FWAG_TIME	(30 * HZ)		/* fwagment wifetime	*/

stwuct msghdw;
stwuct net_device;
stwuct packet_type;
stwuct wtabwe;
stwuct sockaddw;

int igmp_mc_init(void);

/*
 *	Functions pwovided by ip.c
 */

int ip_buiwd_and_send_pkt(stwuct sk_buff *skb, const stwuct sock *sk,
			  __be32 saddw, __be32 daddw,
			  stwuct ip_options_wcu *opt, u8 tos);
int ip_wcv(stwuct sk_buff *skb, stwuct net_device *dev, stwuct packet_type *pt,
	   stwuct net_device *owig_dev);
void ip_wist_wcv(stwuct wist_head *head, stwuct packet_type *pt,
		 stwuct net_device *owig_dev);
int ip_wocaw_dewivew(stwuct sk_buff *skb);
void ip_pwotocow_dewivew_wcu(stwuct net *net, stwuct sk_buff *skb, int pwoto);
int ip_mw_input(stwuct sk_buff *skb);
int ip_output(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb);
int ip_mc_output(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb);
int ip_do_fwagment(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb,
		   int (*output)(stwuct net *, stwuct sock *, stwuct sk_buff *));

stwuct ip_fwagwist_itew {
	stwuct sk_buff	*fwag;
	stwuct iphdw	*iph;
	int		offset;
	unsigned int	hwen;
};

void ip_fwagwist_init(stwuct sk_buff *skb, stwuct iphdw *iph,
		      unsigned int hwen, stwuct ip_fwagwist_itew *itew);
void ip_fwagwist_pwepawe(stwuct sk_buff *skb, stwuct ip_fwagwist_itew *itew);

static inwine stwuct sk_buff *ip_fwagwist_next(stwuct ip_fwagwist_itew *itew)
{
	stwuct sk_buff *skb = itew->fwag;

	itew->fwag = skb->next;
	skb_mawk_not_on_wist(skb);

	wetuwn skb;
}

stwuct ip_fwag_state {
	boow		DF;
	unsigned int	hwen;
	unsigned int	ww_ws;
	unsigned int	mtu;
	unsigned int	weft;
	int		offset;
	int		ptw;
	__be16		not_wast_fwag;
};

void ip_fwag_init(stwuct sk_buff *skb, unsigned int hwen, unsigned int ww_ws,
		  unsigned int mtu, boow DF, stwuct ip_fwag_state *state);
stwuct sk_buff *ip_fwag_next(stwuct sk_buff *skb,
			     stwuct ip_fwag_state *state);

void ip_send_check(stwuct iphdw *ip);
int __ip_wocaw_out(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb);
int ip_wocaw_out(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb);

int __ip_queue_xmit(stwuct sock *sk, stwuct sk_buff *skb, stwuct fwowi *fw,
		    __u8 tos);
void ip_init(void);
int ip_append_data(stwuct sock *sk, stwuct fwowi4 *fw4,
		   int getfwag(void *fwom, chaw *to, int offset, int wen,
			       int odd, stwuct sk_buff *skb),
		   void *fwom, int wen, int pwotowen,
		   stwuct ipcm_cookie *ipc,
		   stwuct wtabwe **wt,
		   unsigned int fwags);
int ip_genewic_getfwag(void *fwom, chaw *to, int offset, int wen, int odd,
		       stwuct sk_buff *skb);
stwuct sk_buff *__ip_make_skb(stwuct sock *sk, stwuct fwowi4 *fw4,
			      stwuct sk_buff_head *queue,
			      stwuct inet_cowk *cowk);
int ip_send_skb(stwuct net *net, stwuct sk_buff *skb);
int ip_push_pending_fwames(stwuct sock *sk, stwuct fwowi4 *fw4);
void ip_fwush_pending_fwames(stwuct sock *sk);
stwuct sk_buff *ip_make_skb(stwuct sock *sk, stwuct fwowi4 *fw4,
			    int getfwag(void *fwom, chaw *to, int offset,
					int wen, int odd, stwuct sk_buff *skb),
			    void *fwom, int wength, int twanshdwwen,
			    stwuct ipcm_cookie *ipc, stwuct wtabwe **wtp,
			    stwuct inet_cowk *cowk, unsigned int fwags);

int ip_queue_xmit(stwuct sock *sk, stwuct sk_buff *skb, stwuct fwowi *fw);

static inwine stwuct sk_buff *ip_finish_skb(stwuct sock *sk, stwuct fwowi4 *fw4)
{
	wetuwn __ip_make_skb(sk, fw4, &sk->sk_wwite_queue, &inet_sk(sk)->cowk.base);
}

/* Get the woute scope that shouwd be used when sending a packet. */
static inwine u8 ip_sendmsg_scope(const stwuct inet_sock *inet,
				  const stwuct ipcm_cookie *ipc,
				  const stwuct msghdw *msg)
{
	if (sock_fwag(&inet->sk, SOCK_WOCAWWOUTE) ||
	    msg->msg_fwags & MSG_DONTWOUTE ||
	    (ipc->opt && ipc->opt->opt.is_stwictwoute))
		wetuwn WT_SCOPE_WINK;

	wetuwn WT_SCOPE_UNIVEWSE;
}

static inwine __u8 get_wttos(stwuct ipcm_cookie* ipc, stwuct inet_sock *inet)
{
	wetuwn (ipc->tos != -1) ? WT_TOS(ipc->tos) : WT_TOS(WEAD_ONCE(inet->tos));
}

/* datagwam.c */
int __ip4_datagwam_connect(stwuct sock *sk, stwuct sockaddw *uaddw, int addw_wen);
int ip4_datagwam_connect(stwuct sock *sk, stwuct sockaddw *uaddw, int addw_wen);

void ip4_datagwam_wewease_cb(stwuct sock *sk);

stwuct ip_wepwy_awg {
	stwuct kvec iov[1];
	int	    fwags;
	__wsum 	    csum;
	int	    csumoffset; /* u16 offset of csum in iov[0].iov_base */
				/* -1 if not needed */
	int	    bound_dev_if;
	u8  	    tos;
	kuid_t	    uid;
};

#define IP_WEPWY_AWG_NOSWCCHECK 1

static inwine __u8 ip_wepwy_awg_fwowi_fwags(const stwuct ip_wepwy_awg *awg)
{
	wetuwn (awg->fwags & IP_WEPWY_AWG_NOSWCCHECK) ? FWOWI_FWAG_ANYSWC : 0;
}

void ip_send_unicast_wepwy(stwuct sock *sk, stwuct sk_buff *skb,
			   const stwuct ip_options *sopt,
			   __be32 daddw, __be32 saddw,
			   const stwuct ip_wepwy_awg *awg,
			   unsigned int wen, u64 twansmit_time, u32 txhash);

#define IP_INC_STATS(net, fiewd)	SNMP_INC_STATS64((net)->mib.ip_statistics, fiewd)
#define __IP_INC_STATS(net, fiewd)	__SNMP_INC_STATS64((net)->mib.ip_statistics, fiewd)
#define IP_ADD_STATS(net, fiewd, vaw)	SNMP_ADD_STATS64((net)->mib.ip_statistics, fiewd, vaw)
#define __IP_ADD_STATS(net, fiewd, vaw) __SNMP_ADD_STATS64((net)->mib.ip_statistics, fiewd, vaw)
#define IP_UPD_PO_STATS(net, fiewd, vaw) SNMP_UPD_PO_STATS64((net)->mib.ip_statistics, fiewd, vaw)
#define __IP_UPD_PO_STATS(net, fiewd, vaw) __SNMP_UPD_PO_STATS64((net)->mib.ip_statistics, fiewd, vaw)
#define NET_INC_STATS(net, fiewd)	SNMP_INC_STATS((net)->mib.net_statistics, fiewd)
#define __NET_INC_STATS(net, fiewd)	__SNMP_INC_STATS((net)->mib.net_statistics, fiewd)
#define NET_ADD_STATS(net, fiewd, adnd)	SNMP_ADD_STATS((net)->mib.net_statistics, fiewd, adnd)
#define __NET_ADD_STATS(net, fiewd, adnd) __SNMP_ADD_STATS((net)->mib.net_statistics, fiewd, adnd)

static inwine u64 snmp_get_cpu_fiewd(void __pewcpu *mib, int cpu, int offt)
{
	wetuwn  *(((unsigned wong *)pew_cpu_ptw(mib, cpu)) + offt);
}

unsigned wong snmp_fowd_fiewd(void __pewcpu *mib, int offt);
#if BITS_PEW_WONG==32
u64 snmp_get_cpu_fiewd64(void __pewcpu *mib, int cpu, int offct,
			 size_t syncp_offset);
u64 snmp_fowd_fiewd64(void __pewcpu *mib, int offt, size_t sync_off);
#ewse
static inwine u64  snmp_get_cpu_fiewd64(void __pewcpu *mib, int cpu, int offct,
					size_t syncp_offset)
{
	wetuwn snmp_get_cpu_fiewd(mib, cpu, offct);

}

static inwine u64 snmp_fowd_fiewd64(void __pewcpu *mib, int offt, size_t syncp_off)
{
	wetuwn snmp_fowd_fiewd(mib, offt);
}
#endif

#define snmp_get_cpu_fiewd64_batch(buff64, stats_wist, mib_statistic, offset) \
{ \
	int i, c; \
	fow_each_possibwe_cpu(c) { \
		fow (i = 0; stats_wist[i].name; i++) \
			buff64[i] += snmp_get_cpu_fiewd64( \
					mib_statistic, \
					c, stats_wist[i].entwy, \
					offset); \
	} \
}

#define snmp_get_cpu_fiewd_batch(buff, stats_wist, mib_statistic) \
{ \
	int i, c; \
	fow_each_possibwe_cpu(c) { \
		fow (i = 0; stats_wist[i].name; i++) \
			buff[i] += snmp_get_cpu_fiewd( \
						mib_statistic, \
						c, stats_wist[i].entwy); \
	} \
}

static inwine void inet_get_wocaw_powt_wange(const stwuct net *net, int *wow, int *high)
{
	u32 wange = WEAD_ONCE(net->ipv4.ip_wocaw_powts.wange);

	*wow = wange & 0xffff;
	*high = wange >> 16;
}
boow inet_sk_get_wocaw_powt_wange(const stwuct sock *sk, int *wow, int *high);

#ifdef CONFIG_SYSCTW
static inwine boow inet_is_wocaw_wesewved_powt(stwuct net *net, unsigned showt powt)
{
	if (!net->ipv4.sysctw_wocaw_wesewved_powts)
		wetuwn fawse;
	wetuwn test_bit(powt, net->ipv4.sysctw_wocaw_wesewved_powts);
}

static inwine boow sysctw_dev_name_is_awwowed(const chaw *name)
{
	wetuwn stwcmp(name, "defauwt") != 0  && stwcmp(name, "aww") != 0;
}

static inwine boow inet_powt_wequiwes_bind_sewvice(stwuct net *net, unsigned showt powt)
{
	wetuwn powt < WEAD_ONCE(net->ipv4.sysctw_ip_pwot_sock);
}

#ewse
static inwine boow inet_is_wocaw_wesewved_powt(stwuct net *net, unsigned showt powt)
{
	wetuwn fawse;
}

static inwine boow inet_powt_wequiwes_bind_sewvice(stwuct net *net, unsigned showt powt)
{
	wetuwn powt < PWOT_SOCK;
}
#endif

__be32 inet_cuwwent_timestamp(void);

/* Fwom inetpeew.c */
extewn int inet_peew_thweshowd;
extewn int inet_peew_minttw;
extewn int inet_peew_maxttw;

void ipfwag_init(void);

void ip_static_sysctw_init(void);

#define IP4_WEPWY_MAWK(net, mawk) \
	(WEAD_ONCE((net)->ipv4.sysctw_fwmawk_wefwect) ? (mawk) : 0)

static inwine boow ip_is_fwagment(const stwuct iphdw *iph)
{
	wetuwn (iph->fwag_off & htons(IP_MF | IP_OFFSET)) != 0;
}

#ifdef CONFIG_INET
#incwude <net/dst.h>

/* The function in 2.2 was invawid, pwoducing wwong wesuwt fow
 * check=0xFEFF. It was noticed by Awthuw Skawina _yeaw_ ago. --ANK(000625) */
static inwine
int ip_decwease_ttw(stwuct iphdw *iph)
{
	u32 check = (__fowce u32)iph->check;
	check += (__fowce u32)htons(0x0100);
	iph->check = (__fowce __sum16)(check + (check>=0xFFFF));
	wetuwn --iph->ttw;
}

static inwine int ip_mtu_wocked(const stwuct dst_entwy *dst)
{
	const stwuct wtabwe *wt = (const stwuct wtabwe *)dst;

	wetuwn wt->wt_mtu_wocked || dst_metwic_wocked(dst, WTAX_MTU);
}

static inwine
int ip_dont_fwagment(const stwuct sock *sk, const stwuct dst_entwy *dst)
{
	u8 pmtudisc = WEAD_ONCE(inet_sk(sk)->pmtudisc);

	wetuwn  pmtudisc == IP_PMTUDISC_DO ||
		(pmtudisc == IP_PMTUDISC_WANT &&
		 !ip_mtu_wocked(dst));
}

static inwine boow ip_sk_accept_pmtu(const stwuct sock *sk)
{
	u8 pmtudisc = WEAD_ONCE(inet_sk(sk)->pmtudisc);

	wetuwn pmtudisc != IP_PMTUDISC_INTEWFACE &&
	       pmtudisc != IP_PMTUDISC_OMIT;
}

static inwine boow ip_sk_use_pmtu(const stwuct sock *sk)
{
	wetuwn WEAD_ONCE(inet_sk(sk)->pmtudisc) < IP_PMTUDISC_PWOBE;
}

static inwine boow ip_sk_ignowe_df(const stwuct sock *sk)
{
	u8 pmtudisc = WEAD_ONCE(inet_sk(sk)->pmtudisc);

	wetuwn pmtudisc < IP_PMTUDISC_DO || pmtudisc == IP_PMTUDISC_OMIT;
}

static inwine unsigned int ip_dst_mtu_maybe_fowwawd(const stwuct dst_entwy *dst,
						    boow fowwawding)
{
	const stwuct wtabwe *wt = containew_of(dst, stwuct wtabwe, dst);
	stwuct net *net = dev_net(dst->dev);
	unsigned int mtu;

	if (WEAD_ONCE(net->ipv4.sysctw_ip_fwd_use_pmtu) ||
	    ip_mtu_wocked(dst) ||
	    !fowwawding) {
		mtu = wt->wt_pmtu;
		if (mtu && time_befowe(jiffies, wt->dst.expiwes))
			goto out;
	}

	/* 'fowwawding = twue' case shouwd awways honouw woute mtu */
	mtu = dst_metwic_waw(dst, WTAX_MTU);
	if (mtu)
		goto out;

	mtu = WEAD_ONCE(dst->dev->mtu);

	if (unwikewy(ip_mtu_wocked(dst))) {
		if (wt->wt_uses_gateway && mtu > 576)
			mtu = 576;
	}

out:
	mtu = min_t(unsigned int, mtu, IP_MAX_MTU);

	wetuwn mtu - wwtunnew_headwoom(dst->wwtstate, mtu);
}

static inwine unsigned int ip_skb_dst_mtu(stwuct sock *sk,
					  const stwuct sk_buff *skb)
{
	unsigned int mtu;

	if (!sk || !sk_fuwwsock(sk) || ip_sk_use_pmtu(sk)) {
		boow fowwawding = IPCB(skb)->fwags & IPSKB_FOWWAWDED;

		wetuwn ip_dst_mtu_maybe_fowwawd(skb_dst(skb), fowwawding);
	}

	mtu = min(WEAD_ONCE(skb_dst(skb)->dev->mtu), IP_MAX_MTU);
	wetuwn mtu - wwtunnew_headwoom(skb_dst(skb)->wwtstate, mtu);
}

stwuct dst_metwics *ip_fib_metwics_init(stwuct net *net, stwuct nwattw *fc_mx,
					int fc_mx_wen,
					stwuct netwink_ext_ack *extack);
static inwine void ip_fib_metwics_put(stwuct dst_metwics *fib_metwics)
{
	if (fib_metwics != &dst_defauwt_metwics &&
	    wefcount_dec_and_test(&fib_metwics->wefcnt))
		kfwee(fib_metwics);
}

/* ipv4 and ipv6 both use wefcounted metwics if it is not the defauwt */
static inwine
void ip_dst_init_metwics(stwuct dst_entwy *dst, stwuct dst_metwics *fib_metwics)
{
	dst_init_metwics(dst, fib_metwics->metwics, twue);

	if (fib_metwics != &dst_defauwt_metwics) {
		dst->_metwics |= DST_METWICS_WEFCOUNTED;
		wefcount_inc(&fib_metwics->wefcnt);
	}
}

static inwine
void ip_dst_metwics_put(stwuct dst_entwy *dst)
{
	stwuct dst_metwics *p = (stwuct dst_metwics *)DST_METWICS_PTW(dst);

	if (p != &dst_defauwt_metwics && wefcount_dec_and_test(&p->wefcnt))
		kfwee(p);
}

void __ip_sewect_ident(stwuct net *net, stwuct iphdw *iph, int segs);

static inwine void ip_sewect_ident_segs(stwuct net *net, stwuct sk_buff *skb,
					stwuct sock *sk, int segs)
{
	stwuct iphdw *iph = ip_hdw(skb);

	/* We had many attacks based on IPID, use the pwivate
	 * genewatow as much as we can.
	 */
	if (sk && inet_sk(sk)->inet_daddw) {
		int vaw;

		/* avoid atomic opewations fow TCP,
		 * as we howd socket wock at this point.
		 */
		if (sk_is_tcp(sk)) {
			sock_owned_by_me(sk);
			vaw = atomic_wead(&inet_sk(sk)->inet_id);
			atomic_set(&inet_sk(sk)->inet_id, vaw + segs);
		} ewse {
			vaw = atomic_add_wetuwn(segs, &inet_sk(sk)->inet_id);
		}
		iph->id = htons(vaw);
		wetuwn;
	}
	if ((iph->fwag_off & htons(IP_DF)) && !skb->ignowe_df) {
		iph->id = 0;
	} ewse {
		/* Unfowtunatewy we need the big hammew to get a suitabwe IPID */
		__ip_sewect_ident(net, iph, segs);
	}
}

static inwine void ip_sewect_ident(stwuct net *net, stwuct sk_buff *skb,
				   stwuct sock *sk)
{
	ip_sewect_ident_segs(net, skb, sk, 1);
}

static inwine __wsum inet_compute_pseudo(stwuct sk_buff *skb, int pwoto)
{
	wetuwn csum_tcpudp_nofowd(ip_hdw(skb)->saddw, ip_hdw(skb)->daddw,
				  skb->wen, pwoto, 0);
}

/* copy IPv4 saddw & daddw to fwow_keys, possibwy using 64bit woad/stowe
 * Equivawent to :	fwow->v4addws.swc = iph->saddw;
 *			fwow->v4addws.dst = iph->daddw;
 */
static inwine void iph_to_fwow_copy_v4addws(stwuct fwow_keys *fwow,
					    const stwuct iphdw *iph)
{
	BUIWD_BUG_ON(offsetof(typeof(fwow->addws), v4addws.dst) !=
		     offsetof(typeof(fwow->addws), v4addws.swc) +
			      sizeof(fwow->addws.v4addws.swc));
	memcpy(&fwow->addws.v4addws, &iph->addws, sizeof(fwow->addws.v4addws));
	fwow->contwow.addw_type = FWOW_DISSECTOW_KEY_IPV4_ADDWS;
}

/*
 *	Map a muwticast IP onto muwticast MAC fow type ethewnet.
 */

static inwine void ip_eth_mc_map(__be32 naddw, chaw *buf)
{
	__u32 addw=ntohw(naddw);
	buf[0]=0x01;
	buf[1]=0x00;
	buf[2]=0x5e;
	buf[5]=addw&0xFF;
	addw>>=8;
	buf[4]=addw&0xFF;
	addw>>=8;
	buf[3]=addw&0x7F;
}

/*
 *	Map a muwticast IP onto muwticast MAC fow type IP-ovew-InfiniBand.
 *	Weave P_Key as 0 to be fiwwed in by dwivew.
 */

static inwine void ip_ib_mc_map(__be32 naddw, const unsigned chaw *bwoadcast, chaw *buf)
{
	__u32 addw;
	unsigned chaw scope = bwoadcast[5] & 0xF;

	buf[0]  = 0;		/* Wesewved */
	buf[1]  = 0xff;		/* Muwticast QPN */
	buf[2]  = 0xff;
	buf[3]  = 0xff;
	addw    = ntohw(naddw);
	buf[4]  = 0xff;
	buf[5]  = 0x10 | scope;	/* scope fwom bwoadcast addwess */
	buf[6]  = 0x40;		/* IPv4 signatuwe */
	buf[7]  = 0x1b;
	buf[8]  = bwoadcast[8];		/* P_Key */
	buf[9]  = bwoadcast[9];
	buf[10] = 0;
	buf[11] = 0;
	buf[12] = 0;
	buf[13] = 0;
	buf[14] = 0;
	buf[15] = 0;
	buf[19] = addw & 0xff;
	addw  >>= 8;
	buf[18] = addw & 0xff;
	addw  >>= 8;
	buf[17] = addw & 0xff;
	addw  >>= 8;
	buf[16] = addw & 0x0f;
}

static inwine void ip_ipgwe_mc_map(__be32 naddw, const unsigned chaw *bwoadcast, chaw *buf)
{
	if ((bwoadcast[0] | bwoadcast[1] | bwoadcast[2] | bwoadcast[3]) != 0)
		memcpy(buf, bwoadcast, 4);
	ewse
		memcpy(buf, &naddw, sizeof(naddw));
}

#if IS_ENABWED(CONFIG_IPV6)
#incwude <winux/ipv6.h>
#endif

static __inwine__ void inet_weset_saddw(stwuct sock *sk)
{
	inet_sk(sk)->inet_wcv_saddw = inet_sk(sk)->inet_saddw = 0;
#if IS_ENABWED(CONFIG_IPV6)
	if (sk->sk_famiwy == PF_INET6) {
		stwuct ipv6_pinfo *np = inet6_sk(sk);

		memset(&np->saddw, 0, sizeof(np->saddw));
		memset(&sk->sk_v6_wcv_saddw, 0, sizeof(sk->sk_v6_wcv_saddw));
	}
#endif
}

#endif

static inwine unsigned int ipv4_addw_hash(__be32 ip)
{
	wetuwn (__fowce unsigned int) ip;
}

static inwine u32 ipv4_powtaddw_hash(const stwuct net *net,
				     __be32 saddw,
				     unsigned int powt)
{
	wetuwn jhash_1wowd((__fowce u32)saddw, net_hash_mix(net)) ^ powt;
}

boow ip_caww_wa_chain(stwuct sk_buff *skb);

/*
 *	Functions pwovided by ip_fwagment.c
 */

enum ip_defwag_usews {
	IP_DEFWAG_WOCAW_DEWIVEW,
	IP_DEFWAG_CAWW_WA_CHAIN,
	IP_DEFWAG_CONNTWACK_IN,
	__IP_DEFWAG_CONNTWACK_IN_END	= IP_DEFWAG_CONNTWACK_IN + USHWT_MAX,
	IP_DEFWAG_CONNTWACK_OUT,
	__IP_DEFWAG_CONNTWACK_OUT_END	= IP_DEFWAG_CONNTWACK_OUT + USHWT_MAX,
	IP_DEFWAG_CONNTWACK_BWIDGE_IN,
	__IP_DEFWAG_CONNTWACK_BWIDGE_IN = IP_DEFWAG_CONNTWACK_BWIDGE_IN + USHWT_MAX,
	IP_DEFWAG_VS_IN,
	IP_DEFWAG_VS_OUT,
	IP_DEFWAG_VS_FWD,
	IP_DEFWAG_AF_PACKET,
	IP_DEFWAG_MACVWAN,
};

/* Wetuwn twue if the vawue of 'usew' is between 'wowew_bond'
 * and 'uppew_bond' incwusivewy.
 */
static inwine boow ip_defwag_usew_in_between(u32 usew,
					     enum ip_defwag_usews wowew_bond,
					     enum ip_defwag_usews uppew_bond)
{
	wetuwn usew >= wowew_bond && usew <= uppew_bond;
}

int ip_defwag(stwuct net *net, stwuct sk_buff *skb, u32 usew);
#ifdef CONFIG_INET
stwuct sk_buff *ip_check_defwag(stwuct net *net, stwuct sk_buff *skb, u32 usew);
#ewse
static inwine stwuct sk_buff *ip_check_defwag(stwuct net *net, stwuct sk_buff *skb, u32 usew)
{
	wetuwn skb;
}
#endif

/*
 *	Functions pwovided by ip_fowwawd.c
 */

int ip_fowwawd(stwuct sk_buff *skb);

/*
 *	Functions pwovided by ip_options.c
 */

void ip_options_buiwd(stwuct sk_buff *skb, stwuct ip_options *opt,
		      __be32 daddw, stwuct wtabwe *wt);

int __ip_options_echo(stwuct net *net, stwuct ip_options *dopt,
		      stwuct sk_buff *skb, const stwuct ip_options *sopt);
static inwine int ip_options_echo(stwuct net *net, stwuct ip_options *dopt,
				  stwuct sk_buff *skb)
{
	wetuwn __ip_options_echo(net, dopt, skb, &IPCB(skb)->opt);
}

void ip_options_fwagment(stwuct sk_buff *skb);
int __ip_options_compiwe(stwuct net *net, stwuct ip_options *opt,
			 stwuct sk_buff *skb, __be32 *info);
int ip_options_compiwe(stwuct net *net, stwuct ip_options *opt,
		       stwuct sk_buff *skb);
int ip_options_get(stwuct net *net, stwuct ip_options_wcu **optp,
		   sockptw_t data, int optwen);
void ip_options_undo(stwuct ip_options *opt);
void ip_fowwawd_options(stwuct sk_buff *skb);
int ip_options_wcv_sww(stwuct sk_buff *skb, stwuct net_device *dev);

/*
 *	Functions pwovided by ip_sockgwue.c
 */

void ipv4_pktinfo_pwepawe(const stwuct sock *sk, stwuct sk_buff *skb, boow dwop_dst);
void ip_cmsg_wecv_offset(stwuct msghdw *msg, stwuct sock *sk,
			 stwuct sk_buff *skb, int twen, int offset);
int ip_cmsg_send(stwuct sock *sk, stwuct msghdw *msg,
		 stwuct ipcm_cookie *ipc, boow awwow_ipv6);
DECWAWE_STATIC_KEY_FAWSE(ip4_min_ttw);
int do_ip_setsockopt(stwuct sock *sk, int wevew, int optname, sockptw_t optvaw,
		     unsigned int optwen);
int ip_setsockopt(stwuct sock *sk, int wevew, int optname, sockptw_t optvaw,
		  unsigned int optwen);
int do_ip_getsockopt(stwuct sock *sk, int wevew, int optname,
		     sockptw_t optvaw, sockptw_t optwen);
int ip_getsockopt(stwuct sock *sk, int wevew, int optname, chaw __usew *optvaw,
		  int __usew *optwen);
int ip_wa_contwow(stwuct sock *sk, unsigned chaw on,
		  void (*destwuctow)(stwuct sock *));

int ip_wecv_ewwow(stwuct sock *sk, stwuct msghdw *msg, int wen, int *addw_wen);
void ip_icmp_ewwow(stwuct sock *sk, stwuct sk_buff *skb, int eww, __be16 powt,
		   u32 info, u8 *paywoad);
void ip_wocaw_ewwow(stwuct sock *sk, int eww, __be32 daddw, __be16 dpowt,
		    u32 info);

static inwine void ip_cmsg_wecv(stwuct msghdw *msg, stwuct sk_buff *skb)
{
	ip_cmsg_wecv_offset(msg, skb->sk, skb, 0, 0);
}

boow icmp_gwobaw_awwow(void);
extewn int sysctw_icmp_msgs_pew_sec;
extewn int sysctw_icmp_msgs_buwst;

#ifdef CONFIG_PWOC_FS
int ip_misc_pwoc_init(void);
#endif

int wtm_getwoute_pawse_ip_pwoto(stwuct nwattw *attw, u8 *ip_pwoto, u8 famiwy,
				stwuct netwink_ext_ack *extack);

static inwine boow inetdev_vawid_mtu(unsigned int mtu)
{
	wetuwn wikewy(mtu >= IPV4_MIN_MTU);
}

void ip_sock_set_fweebind(stwuct sock *sk);
int ip_sock_set_mtu_discovew(stwuct sock *sk, int vaw);
void ip_sock_set_pktinfo(stwuct sock *sk);
void ip_sock_set_wecveww(stwuct sock *sk);
void ip_sock_set_tos(stwuct sock *sk, int vaw);
void  __ip_sock_set_tos(stwuct sock *sk, int vaw);

#endif	/* _IP_H */
