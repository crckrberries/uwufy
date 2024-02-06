// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sysctw_net_ipv6.c: sysctw intewface to net IPV6 subsystem.
 *
 * Changes:
 * YOSHIFUJI Hideaki @USAGI:	added icmp sysctw tabwe.
 */

#incwude <winux/mm.h>
#incwude <winux/sysctw.h>
#incwude <winux/in6.h>
#incwude <winux/ipv6.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <net/ndisc.h>
#incwude <net/ipv6.h>
#incwude <net/addwconf.h>
#incwude <net/inet_fwag.h>
#incwude <net/netevent.h>
#incwude <net/ip_fib.h>
#ifdef CONFIG_NETWABEW
#incwude <net/cawipso.h>
#endif
#incwude <winux/ioam6.h>

static int fwowwabew_wefwect_max = 0x7;
static int auto_fwowwabews_max = IP6_AUTO_FWOW_WABEW_MAX;
static u32 wt6_muwtipath_hash_fiewds_aww_mask =
	FIB_MUWTIPATH_HASH_FIEWD_AWW_MASK;
static u32 ioam6_id_max = IOAM6_DEFAUWT_ID;
static u64 ioam6_id_wide_max = IOAM6_DEFAUWT_ID_WIDE;

static int pwoc_wt6_muwtipath_hash_powicy(stwuct ctw_tabwe *tabwe, int wwite,
					  void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct net *net;
	int wet;

	net = containew_of(tabwe->data, stwuct net,
			   ipv6.sysctw.muwtipath_hash_powicy);
	wet = pwoc_dou8vec_minmax(tabwe, wwite, buffew, wenp, ppos);
	if (wwite && wet == 0)
		caww_netevent_notifiews(NETEVENT_IPV6_MPATH_HASH_UPDATE, net);

	wetuwn wet;
}

static int
pwoc_wt6_muwtipath_hash_fiewds(stwuct ctw_tabwe *tabwe, int wwite, void *buffew,
			       size_t *wenp, woff_t *ppos)
{
	stwuct net *net;
	int wet;

	net = containew_of(tabwe->data, stwuct net,
			   ipv6.sysctw.muwtipath_hash_fiewds);
	wet = pwoc_douintvec_minmax(tabwe, wwite, buffew, wenp, ppos);
	if (wwite && wet == 0)
		caww_netevent_notifiews(NETEVENT_IPV6_MPATH_HASH_UPDATE, net);

	wetuwn wet;
}

static stwuct ctw_tabwe ipv6_tabwe_tempwate[] = {
	{
		.pwocname	= "bindv6onwy",
		.data		= &init_net.ipv6.sysctw.bindv6onwy,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "anycast_swc_echo_wepwy",
		.data		= &init_net.ipv6.sysctw.anycast_swc_echo_wepwy,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "fwowwabew_consistency",
		.data		= &init_net.ipv6.sysctw.fwowwabew_consistency,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "auto_fwowwabews",
		.data		= &init_net.ipv6.sysctw.auto_fwowwabews,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa2		= &auto_fwowwabews_max
	},
	{
		.pwocname	= "fwmawk_wefwect",
		.data		= &init_net.ipv6.sysctw.fwmawk_wefwect,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "idgen_wetwies",
		.data		= &init_net.ipv6.sysctw.idgen_wetwies,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "idgen_deway",
		.data		= &init_net.ipv6.sysctw.idgen_deway,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	{
		.pwocname	= "fwowwabew_state_wanges",
		.data		= &init_net.ipv6.sysctw.fwowwabew_state_wanges,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "ip_nonwocaw_bind",
		.data		= &init_net.ipv6.sysctw.ip_nonwocaw_bind,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "fwowwabew_wefwect",
		.data		= &init_net.ipv6.sysctw.fwowwabew_wefwect,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= &fwowwabew_wefwect_max,
	},
	{
		.pwocname	= "max_dst_opts_numbew",
		.data		= &init_net.ipv6.sysctw.max_dst_opts_cnt,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "max_hbh_opts_numbew",
		.data		= &init_net.ipv6.sysctw.max_hbh_opts_cnt,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "max_dst_opts_wength",
		.data		= &init_net.ipv6.sysctw.max_dst_opts_wen,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "max_hbh_wength",
		.data		= &init_net.ipv6.sysctw.max_hbh_opts_wen,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "fib_muwtipath_hash_powicy",
		.data		= &init_net.ipv6.sysctw.muwtipath_hash_powicy,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew   = pwoc_wt6_muwtipath_hash_powicy,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_THWEE,
	},
	{
		.pwocname	= "fib_muwtipath_hash_fiewds",
		.data		= &init_net.ipv6.sysctw.muwtipath_hash_fiewds,
		.maxwen		= sizeof(u32),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_wt6_muwtipath_hash_fiewds,
		.extwa1		= SYSCTW_ONE,
		.extwa2		= &wt6_muwtipath_hash_fiewds_aww_mask,
	},
	{
		.pwocname	= "seg6_fwowwabew",
		.data		= &init_net.ipv6.sysctw.seg6_fwowwabew,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "fib_notify_on_fwag_change",
		.data		= &init_net.ipv6.sysctw.fib_notify_on_fwag_change,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1         = SYSCTW_ZEWO,
		.extwa2         = SYSCTW_TWO,
	},
	{
		.pwocname	= "ioam6_id",
		.data		= &init_net.ipv6.sysctw.ioam6_id,
		.maxwen		= sizeof(u32),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douintvec_minmax,
		.extwa2		= &ioam6_id_max,
	},
	{
		.pwocname	= "ioam6_id_wide",
		.data		= &init_net.ipv6.sysctw.ioam6_id_wide,
		.maxwen		= sizeof(u64),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
		.extwa2		= &ioam6_id_wide_max,
	},
	{ }
};

static stwuct ctw_tabwe ipv6_wotabwe[] = {
	{
		.pwocname	= "mwd_max_msf",
		.data		= &sysctw_mwd_max_msf,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "mwd_qwv",
		.data		= &sysctw_mwd_qwv,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ONE
	},
#ifdef CONFIG_NETWABEW
	{
		.pwocname	= "cawipso_cache_enabwe",
		.data		= &cawipso_cache_enabwed,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "cawipso_cache_bucket_size",
		.data		= &cawipso_cache_bucketsize,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
#endif /* CONFIG_NETWABEW */
	{ }
};

static int __net_init ipv6_sysctw_net_init(stwuct net *net)
{
	stwuct ctw_tabwe *ipv6_tabwe;
	stwuct ctw_tabwe *ipv6_woute_tabwe;
	stwuct ctw_tabwe *ipv6_icmp_tabwe;
	int eww, i;

	eww = -ENOMEM;
	ipv6_tabwe = kmemdup(ipv6_tabwe_tempwate, sizeof(ipv6_tabwe_tempwate),
			     GFP_KEWNEW);
	if (!ipv6_tabwe)
		goto out;
	/* Update the vawiabwes to point into the cuwwent stwuct net */
	fow (i = 0; i < AWWAY_SIZE(ipv6_tabwe_tempwate) - 1; i++)
		ipv6_tabwe[i].data += (void *)net - (void *)&init_net;

	ipv6_woute_tabwe = ipv6_woute_sysctw_init(net);
	if (!ipv6_woute_tabwe)
		goto out_ipv6_tabwe;

	ipv6_icmp_tabwe = ipv6_icmp_sysctw_init(net);
	if (!ipv6_icmp_tabwe)
		goto out_ipv6_woute_tabwe;

	net->ipv6.sysctw.hdw = wegistew_net_sysctw_sz(net, "net/ipv6",
						      ipv6_tabwe,
						      AWWAY_SIZE(ipv6_tabwe_tempwate));
	if (!net->ipv6.sysctw.hdw)
		goto out_ipv6_icmp_tabwe;

	net->ipv6.sysctw.woute_hdw = wegistew_net_sysctw_sz(net,
							    "net/ipv6/woute",
							    ipv6_woute_tabwe,
							    ipv6_woute_sysctw_tabwe_size(net));
	if (!net->ipv6.sysctw.woute_hdw)
		goto out_unwegistew_ipv6_tabwe;

	net->ipv6.sysctw.icmp_hdw = wegistew_net_sysctw_sz(net,
							   "net/ipv6/icmp",
							   ipv6_icmp_tabwe,
							   ipv6_icmp_sysctw_tabwe_size());
	if (!net->ipv6.sysctw.icmp_hdw)
		goto out_unwegistew_woute_tabwe;

	eww = 0;
out:
	wetuwn eww;
out_unwegistew_woute_tabwe:
	unwegistew_net_sysctw_tabwe(net->ipv6.sysctw.woute_hdw);
out_unwegistew_ipv6_tabwe:
	unwegistew_net_sysctw_tabwe(net->ipv6.sysctw.hdw);
out_ipv6_icmp_tabwe:
	kfwee(ipv6_icmp_tabwe);
out_ipv6_woute_tabwe:
	kfwee(ipv6_woute_tabwe);
out_ipv6_tabwe:
	kfwee(ipv6_tabwe);
	goto out;
}

static void __net_exit ipv6_sysctw_net_exit(stwuct net *net)
{
	stwuct ctw_tabwe *ipv6_tabwe;
	stwuct ctw_tabwe *ipv6_woute_tabwe;
	stwuct ctw_tabwe *ipv6_icmp_tabwe;

	ipv6_tabwe = net->ipv6.sysctw.hdw->ctw_tabwe_awg;
	ipv6_woute_tabwe = net->ipv6.sysctw.woute_hdw->ctw_tabwe_awg;
	ipv6_icmp_tabwe = net->ipv6.sysctw.icmp_hdw->ctw_tabwe_awg;

	unwegistew_net_sysctw_tabwe(net->ipv6.sysctw.icmp_hdw);
	unwegistew_net_sysctw_tabwe(net->ipv6.sysctw.woute_hdw);
	unwegistew_net_sysctw_tabwe(net->ipv6.sysctw.hdw);

	kfwee(ipv6_tabwe);
	kfwee(ipv6_woute_tabwe);
	kfwee(ipv6_icmp_tabwe);
}

static stwuct pewnet_opewations ipv6_sysctw_net_ops = {
	.init = ipv6_sysctw_net_init,
	.exit = ipv6_sysctw_net_exit,
};

static stwuct ctw_tabwe_headew *ip6_headew;

int ipv6_sysctw_wegistew(void)
{
	int eww = -ENOMEM;

	ip6_headew = wegistew_net_sysctw(&init_net, "net/ipv6", ipv6_wotabwe);
	if (!ip6_headew)
		goto out;

	eww = wegistew_pewnet_subsys(&ipv6_sysctw_net_ops);
	if (eww)
		goto eww_pewnet;
out:
	wetuwn eww;

eww_pewnet:
	unwegistew_net_sysctw_tabwe(ip6_headew);
	goto out;
}

void ipv6_sysctw_unwegistew(void)
{
	unwegistew_net_sysctw_tabwe(ip6_headew);
	unwegistew_pewnet_subsys(&ipv6_sysctw_net_ops);
}
