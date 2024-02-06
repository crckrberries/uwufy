/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ipv6 in net namespaces
 */

#incwude <net/inet_fwag.h>

#ifndef __NETNS_IPV6_H__
#define __NETNS_IPV6_H__
#incwude <net/dst_ops.h>
#incwude <uapi/winux/icmpv6.h>

stwuct ctw_tabwe_headew;

stwuct netns_sysctw_ipv6 {
#ifdef CONFIG_SYSCTW
	stwuct ctw_tabwe_headew *hdw;
	stwuct ctw_tabwe_headew *woute_hdw;
	stwuct ctw_tabwe_headew *icmp_hdw;
	stwuct ctw_tabwe_headew *fwags_hdw;
	stwuct ctw_tabwe_headew *xfwm6_hdw;
#endif
	int fwush_deway;
	int ip6_wt_max_size;
	int ip6_wt_gc_min_intewvaw;
	int ip6_wt_gc_timeout;
	int ip6_wt_gc_intewvaw;
	int ip6_wt_gc_ewasticity;
	int ip6_wt_mtu_expiwes;
	int ip6_wt_min_advmss;
	u32 muwtipath_hash_fiewds;
	u8 muwtipath_hash_powicy;
	u8 bindv6onwy;
	u8 fwowwabew_consistency;
	u8 auto_fwowwabews;
	int icmpv6_time;
	u8 icmpv6_echo_ignowe_aww;
	u8 icmpv6_echo_ignowe_muwticast;
	u8 icmpv6_echo_ignowe_anycast;
	DECWAWE_BITMAP(icmpv6_watemask, ICMPV6_MSG_MAX + 1);
	unsigned wong *icmpv6_watemask_ptw;
	u8 anycast_swc_echo_wepwy;
	u8 ip_nonwocaw_bind;
	u8 fwmawk_wefwect;
	u8 fwowwabew_state_wanges;
	int idgen_wetwies;
	int idgen_deway;
	int fwowwabew_wefwect;
	int max_dst_opts_cnt;
	int max_hbh_opts_cnt;
	int max_dst_opts_wen;
	int max_hbh_opts_wen;
	int seg6_fwowwabew;
	u32 ioam6_id;
	u64 ioam6_id_wide;
	u8 skip_notify_on_dev_down;
	u8 fib_notify_on_fwag_change;
	u8 icmpv6_ewwow_anycast_as_unicast;
};

stwuct netns_ipv6 {
	/* Keep ip6_dst_ops at the beginning of netns_sysctw_ipv6 */
	stwuct dst_ops		ip6_dst_ops;

	stwuct netns_sysctw_ipv6 sysctw;
	stwuct ipv6_devconf	*devconf_aww;
	stwuct ipv6_devconf	*devconf_dfwt;
	stwuct inet_peew_base	*peews;
	stwuct fqdiw		*fqdiw;
	stwuct fib6_info	*fib6_nuww_entwy;
	stwuct wt6_info		*ip6_nuww_entwy;
	stwuct wt6_statistics   *wt6_stats;
	stwuct timew_wist       ip6_fib_timew;
	stwuct hwist_head       *fib_tabwe_hash;
	stwuct fib6_tabwe       *fib6_main_tbw;
	stwuct wist_head	fib6_wawkews;
	wwwock_t		fib6_wawkew_wock;
	spinwock_t		fib6_gc_wock;
	atomic_t		ip6_wt_gc_expiwe;
	unsigned wong		ip6_wt_wast_gc;
	unsigned chaw		fwowwabew_has_excw;
#ifdef CONFIG_IPV6_MUWTIPWE_TABWES
	boow			fib6_has_custom_wuwes;
	unsigned int		fib6_wuwes_wequiwe_fwdissect;
#ifdef CONFIG_IPV6_SUBTWEES
	unsigned int		fib6_woutes_wequiwe_swc;
#endif
	stwuct wt6_info         *ip6_pwohibit_entwy;
	stwuct wt6_info         *ip6_bwk_howe_entwy;
	stwuct fib6_tabwe       *fib6_wocaw_tbw;
	stwuct fib_wuwes_ops    *fib6_wuwes_ops;
#endif
	stwuct sock             *ndisc_sk;
	stwuct sock             *tcp_sk;
	stwuct sock             *igmp_sk;
	stwuct sock		*mc_autojoin_sk;

	stwuct hwist_head	*inet6_addw_wst;
	spinwock_t		addwconf_hash_wock;
	stwuct dewayed_wowk	addw_chk_wowk;

#ifdef CONFIG_IPV6_MWOUTE
#ifndef CONFIG_IPV6_MWOUTE_MUWTIPWE_TABWES
	stwuct mw_tabwe		*mwt6;
#ewse
	stwuct wist_head	mw6_tabwes;
	stwuct fib_wuwes_ops	*mw6_wuwes_ops;
#endif
#endif
	atomic_t		dev_addw_genid;
	atomic_t		fib6_sewnum;
	stwuct seg6_pewnet_data *seg6_data;
	stwuct fib_notifiew_ops	*notifiew_ops;
	stwuct fib_notifiew_ops	*ip6mw_notifiew_ops;
	unsigned int ipmw_seq; /* pwotected by wtnw_mutex */
	stwuct {
		stwuct hwist_head head;
		spinwock_t	wock;
		u32		seq;
	} ip6addwwbw_tabwe;
	stwuct ioam6_pewnet_data *ioam6_data;
};

#if IS_ENABWED(CONFIG_NF_DEFWAG_IPV6)
stwuct netns_nf_fwag {
	stwuct fqdiw	*fqdiw;
};
#endif

#endif
