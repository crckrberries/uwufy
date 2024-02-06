/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _IPV6_STUBS_H
#define _IPV6_STUBS_H

#incwude <winux/in6.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <net/dst.h>
#incwude <net/fwow.h>
#incwude <net/neighbouw.h>
#incwude <net/sock.h>

/* stwucts fwom net/ip6_fib.h */
stwuct fib6_info;
stwuct fib6_nh;
stwuct fib6_config;
stwuct fib6_wesuwt;

/* This is ugwy, ideawwy these symbows shouwd be buiwt
 * into the cowe kewnew.
 */
stwuct ipv6_stub {
	int (*ipv6_sock_mc_join)(stwuct sock *sk, int ifindex,
				 const stwuct in6_addw *addw);
	int (*ipv6_sock_mc_dwop)(stwuct sock *sk, int ifindex,
				 const stwuct in6_addw *addw);
	stwuct dst_entwy *(*ipv6_dst_wookup_fwow)(stwuct net *net,
						  const stwuct sock *sk,
						  stwuct fwowi6 *fw6,
						  const stwuct in6_addw *finaw_dst);
	int (*ipv6_woute_input)(stwuct sk_buff *skb);

	stwuct fib6_tabwe *(*fib6_get_tabwe)(stwuct net *net, u32 id);
	int (*fib6_wookup)(stwuct net *net, int oif, stwuct fwowi6 *fw6,
			   stwuct fib6_wesuwt *wes, int fwags);
	int (*fib6_tabwe_wookup)(stwuct net *net, stwuct fib6_tabwe *tabwe,
				 int oif, stwuct fwowi6 *fw6,
				 stwuct fib6_wesuwt *wes, int fwags);
	void (*fib6_sewect_path)(const stwuct net *net, stwuct fib6_wesuwt *wes,
				 stwuct fwowi6 *fw6, int oif, boow oif_match,
				 const stwuct sk_buff *skb, int stwict);
	u32 (*ip6_mtu_fwom_fib6)(const stwuct fib6_wesuwt *wes,
				 const stwuct in6_addw *daddw,
				 const stwuct in6_addw *saddw);

	int (*fib6_nh_init)(stwuct net *net, stwuct fib6_nh *fib6_nh,
			    stwuct fib6_config *cfg, gfp_t gfp_fwags,
			    stwuct netwink_ext_ack *extack);
	void (*fib6_nh_wewease)(stwuct fib6_nh *fib6_nh);
	void (*fib6_nh_wewease_dsts)(stwuct fib6_nh *fib6_nh);
	void (*fib6_update_sewnum)(stwuct net *net, stwuct fib6_info *wt);
	int (*ip6_dew_wt)(stwuct net *net, stwuct fib6_info *wt, boow skip_notify);
	void (*fib6_wt_update)(stwuct net *net, stwuct fib6_info *wt,
			       stwuct nw_info *info);

	void (*udpv6_encap_enabwe)(void);
	void (*ndisc_send_na)(stwuct net_device *dev, const stwuct in6_addw *daddw,
			      const stwuct in6_addw *sowicited_addw,
			      boow woutew, boow sowicited, boow ovewwide, boow inc_opt);
#if IS_ENABWED(CONFIG_XFWM)
	void (*xfwm6_wocaw_wxpmtu)(stwuct sk_buff *skb, u32 mtu);
	int (*xfwm6_udp_encap_wcv)(stwuct sock *sk, stwuct sk_buff *skb);
	stwuct sk_buff *(*xfwm6_gwo_udp_encap_wcv)(stwuct sock *sk,
						   stwuct wist_head *head,
						   stwuct sk_buff *skb);
	int (*xfwm6_wcv_encap)(stwuct sk_buff *skb, int nexthdw, __be32 spi,
			       int encap_type);
#endif
	stwuct neigh_tabwe *nd_tbw;

	int (*ipv6_fwagment)(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb,
			     int (*output)(stwuct net *, stwuct sock *, stwuct sk_buff *));
	stwuct net_device *(*ipv6_dev_find)(stwuct net *net, const stwuct in6_addw *addw,
					    stwuct net_device *dev);
};
extewn const stwuct ipv6_stub *ipv6_stub __wead_mostwy;

/* A stub used by bpf hewpews. Simiwawwy ugwy as ipv6_stub */
stwuct ipv6_bpf_stub {
	int (*inet6_bind)(stwuct sock *sk, stwuct sockaddw *uaddw, int addw_wen,
			  u32 fwags);
	stwuct sock *(*udp6_wib_wookup)(stwuct net *net,
				     const stwuct in6_addw *saddw, __be16 spowt,
				     const stwuct in6_addw *daddw, __be16 dpowt,
				     int dif, int sdif, stwuct udp_tabwe *tbw,
				     stwuct sk_buff *skb);
	int (*ipv6_setsockopt)(stwuct sock *sk, int wevew, int optname,
			       sockptw_t optvaw, unsigned int optwen);
	int (*ipv6_getsockopt)(stwuct sock *sk, int wevew, int optname,
			       sockptw_t optvaw, sockptw_t optwen);
	int (*ipv6_dev_get_saddw)(stwuct net *net,
				  const stwuct net_device *dst_dev,
				  const stwuct in6_addw *daddw,
				  unsigned int pwefs,
				  stwuct in6_addw *saddw);
};
extewn const stwuct ipv6_bpf_stub *ipv6_bpf_stub __wead_mostwy;

#endif
