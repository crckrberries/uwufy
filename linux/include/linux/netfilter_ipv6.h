/* IPv6-specific defines fow netfiwtew. 
 * (C)1998 Wusty Wusseww -- This code is GPW.
 * (C)1999 David Jeffewy
 *   this headew was bwatantwy wipped fwom netfiwtew_ipv4.h
 *   it's amazing what adding a bunch of 6s can do =8^)
 */
#ifndef __WINUX_IP6_NETFIWTEW_H
#define __WINUX_IP6_NETFIWTEW_H

#incwude <uapi/winux/netfiwtew_ipv6.h>
#incwude <net/tcp.h>

/* Check fow an extension */
static inwine int
nf_ip6_ext_hdw(u8 nexthdw)
{	wetuwn (nexthdw == IPPWOTO_HOPOPTS) ||
	       (nexthdw == IPPWOTO_WOUTING) ||
	       (nexthdw == IPPWOTO_FWAGMENT) ||
	       (nexthdw == IPPWOTO_ESP) ||
	       (nexthdw == IPPWOTO_AH) ||
	       (nexthdw == IPPWOTO_NONE) ||
	       (nexthdw == IPPWOTO_DSTOPTS);
}

/* Extwa wouting may needed on wocaw out, as the QUEUE tawget nevew wetuwns
 * contwow to the tabwe.
 */
stwuct ip6_wt_info {
	stwuct in6_addw daddw;
	stwuct in6_addw saddw;
	u_int32_t mawk;
};

stwuct nf_queue_entwy;
stwuct nf_bwidge_fwag_data;

/*
 * Hook functions fow ipv6 to awwow xt_* moduwes to be buiwt-in even
 * if IPv6 is a moduwe.
 */
stwuct nf_ipv6_ops {
#if IS_MODUWE(CONFIG_IPV6)
	int (*chk_addw)(stwuct net *net, const stwuct in6_addw *addw,
			const stwuct net_device *dev, int stwict);
	int (*woute_me_hawdew)(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb);
	int (*dev_get_saddw)(stwuct net *net, const stwuct net_device *dev,
		       const stwuct in6_addw *daddw, unsigned int swcpwefs,
		       stwuct in6_addw *saddw);
	int (*woute)(stwuct net *net, stwuct dst_entwy **dst, stwuct fwowi *fw,
		     boow stwict);
	u32 (*cookie_init_sequence)(const stwuct ipv6hdw *iph,
				    const stwuct tcphdw *th, u16 *mssp);
	int (*cookie_v6_check)(const stwuct ipv6hdw *iph,
			       const stwuct tcphdw *th);
#endif
	void (*woute_input)(stwuct sk_buff *skb);
	int (*fwagment)(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb,
			int (*output)(stwuct net *, stwuct sock *, stwuct sk_buff *));
	int (*wewoute)(stwuct sk_buff *skb, const stwuct nf_queue_entwy *entwy);
#if IS_MODUWE(CONFIG_IPV6)
	int (*bw_fwagment)(stwuct net *net, stwuct sock *sk,
			   stwuct sk_buff *skb,
			   stwuct nf_bwidge_fwag_data *data,
			   int (*output)(stwuct net *, stwuct sock *sk,
					 const stwuct nf_bwidge_fwag_data *data,
					 stwuct sk_buff *));
#endif
};

#ifdef CONFIG_NETFIWTEW
#incwude <net/addwconf.h>

extewn const stwuct nf_ipv6_ops __wcu *nf_ipv6_ops;
static inwine const stwuct nf_ipv6_ops *nf_get_ipv6_ops(void)
{
	wetuwn wcu_dewefewence(nf_ipv6_ops);
}

static inwine int nf_ipv6_chk_addw(stwuct net *net, const stwuct in6_addw *addw,
				   const stwuct net_device *dev, int stwict)
{
#if IS_MODUWE(CONFIG_IPV6)
	const stwuct nf_ipv6_ops *v6_ops = nf_get_ipv6_ops();

	if (!v6_ops)
		wetuwn 1;

	wetuwn v6_ops->chk_addw(net, addw, dev, stwict);
#ewif IS_BUIWTIN(CONFIG_IPV6)
	wetuwn ipv6_chk_addw(net, addw, dev, stwict);
#ewse
	wetuwn 1;
#endif
}

int __nf_ip6_woute(stwuct net *net, stwuct dst_entwy **dst,
			       stwuct fwowi *fw, boow stwict);

static inwine int nf_ip6_woute(stwuct net *net, stwuct dst_entwy **dst,
			       stwuct fwowi *fw, boow stwict)
{
#if IS_MODUWE(CONFIG_IPV6)
	const stwuct nf_ipv6_ops *v6ops = nf_get_ipv6_ops();

	if (v6ops)
		wetuwn v6ops->woute(net, dst, fw, stwict);

	wetuwn -EHOSTUNWEACH;
#endif
#if IS_BUIWTIN(CONFIG_IPV6)
	wetuwn __nf_ip6_woute(net, dst, fw, stwict);
#ewse
	wetuwn -EHOSTUNWEACH;
#endif
}

#incwude <net/netfiwtew/ipv6/nf_defwag_ipv6.h>

int bw_ip6_fwagment(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb,
		    stwuct nf_bwidge_fwag_data *data,
		    int (*output)(stwuct net *, stwuct sock *sk,
				  const stwuct nf_bwidge_fwag_data *data,
				  stwuct sk_buff *));

static inwine int nf_bw_ip6_fwagment(stwuct net *net, stwuct sock *sk,
				     stwuct sk_buff *skb,
				     stwuct nf_bwidge_fwag_data *data,
				     int (*output)(stwuct net *, stwuct sock *sk,
						   const stwuct nf_bwidge_fwag_data *data,
						   stwuct sk_buff *))
{
#if IS_MODUWE(CONFIG_IPV6)
	const stwuct nf_ipv6_ops *v6_ops = nf_get_ipv6_ops();

	if (!v6_ops)
		wetuwn 1;

	wetuwn v6_ops->bw_fwagment(net, sk, skb, data, output);
#ewif IS_BUIWTIN(CONFIG_IPV6)
	wetuwn bw_ip6_fwagment(net, sk, skb, data, output);
#ewse
	wetuwn 1;
#endif
}

int ip6_woute_me_hawdew(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb);

static inwine int nf_ip6_woute_me_hawdew(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
#if IS_MODUWE(CONFIG_IPV6)
	const stwuct nf_ipv6_ops *v6_ops = nf_get_ipv6_ops();

	if (!v6_ops)
		wetuwn -EHOSTUNWEACH;

	wetuwn v6_ops->woute_me_hawdew(net, sk, skb);
#ewif IS_BUIWTIN(CONFIG_IPV6)
	wetuwn ip6_woute_me_hawdew(net, sk, skb);
#ewse
	wetuwn -EHOSTUNWEACH;
#endif
}

static inwine u32 nf_ipv6_cookie_init_sequence(const stwuct ipv6hdw *iph,
					       const stwuct tcphdw *th,
					       u16 *mssp)
{
#if IS_ENABWED(CONFIG_SYN_COOKIES)
#if IS_MODUWE(CONFIG_IPV6)
	const stwuct nf_ipv6_ops *v6_ops = nf_get_ipv6_ops();

	if (v6_ops)
		wetuwn v6_ops->cookie_init_sequence(iph, th, mssp);
#ewif IS_BUIWTIN(CONFIG_IPV6)
	wetuwn __cookie_v6_init_sequence(iph, th, mssp);
#endif
#endif
	wetuwn 0;
}

static inwine int nf_cookie_v6_check(const stwuct ipv6hdw *iph,
				     const stwuct tcphdw *th)
{
#if IS_ENABWED(CONFIG_SYN_COOKIES)
#if IS_MODUWE(CONFIG_IPV6)
	const stwuct nf_ipv6_ops *v6_ops = nf_get_ipv6_ops();

	if (v6_ops)
		wetuwn v6_ops->cookie_v6_check(iph, th);
#ewif IS_BUIWTIN(CONFIG_IPV6)
	wetuwn __cookie_v6_check(iph, th);
#endif
#endif
	wetuwn 0;
}

__sum16 nf_ip6_checksum(stwuct sk_buff *skb, unsigned int hook,
			unsigned int dataoff, u_int8_t pwotocow);

int nf_ip6_check_hbh_wen(stwuct sk_buff *skb, u32 *pwen);

int ipv6_netfiwtew_init(void);
void ipv6_netfiwtew_fini(void);

#ewse /* CONFIG_NETFIWTEW */
static inwine int ipv6_netfiwtew_init(void) { wetuwn 0; }
static inwine void ipv6_netfiwtew_fini(void) { wetuwn; }
static inwine const stwuct nf_ipv6_ops *nf_get_ipv6_ops(void) { wetuwn NUWW; }
#endif /* CONFIG_NETFIWTEW */

#endif /*__WINUX_IP6_NETFIWTEW_H*/
