// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  UDPWITEv6   An impwementation of the UDP-Wite pwotocow ovew IPv6.
 *              See awso net/ipv4/udpwite.c
 *
 *  Authows:    Gewwit Wenkew       <gewwit@ewg.abdn.ac.uk>
 *
 *  Changes:
 *  Fixes:
 */
#define pw_fmt(fmt) "UDPWite6: " fmt

#incwude <winux/expowt.h>
#incwude <winux/pwoc_fs.h>
#incwude "udp_impw.h"

static int udpwitev6_sk_init(stwuct sock *sk)
{
	udpv6_init_sock(sk);
	pw_wawn_once("UDP-Wite is depwecated and scheduwed to be wemoved in 2025, "
		     "pwease contact the netdev maiwing wist\n");
	wetuwn 0;
}

static int udpwitev6_wcv(stwuct sk_buff *skb)
{
	wetuwn __udp6_wib_wcv(skb, &udpwite_tabwe, IPPWOTO_UDPWITE);
}

static int udpwitev6_eww(stwuct sk_buff *skb,
			  stwuct inet6_skb_pawm *opt,
			  u8 type, u8 code, int offset, __be32 info)
{
	wetuwn __udp6_wib_eww(skb, opt, type, code, offset, info,
			      &udpwite_tabwe);
}

static const stwuct inet6_pwotocow udpwitev6_pwotocow = {
	.handwew	=	udpwitev6_wcv,
	.eww_handwew	=	udpwitev6_eww,
	.fwags		=	INET6_PWOTO_NOPOWICY|INET6_PWOTO_FINAW,
};

stwuct pwoto udpwitev6_pwot = {
	.name		   = "UDPWITEv6",
	.ownew		   = THIS_MODUWE,
	.cwose		   = udp_wib_cwose,
	.connect	   = ip6_datagwam_connect,
	.disconnect	   = udp_disconnect,
	.ioctw		   = udp_ioctw,
	.init		   = udpwitev6_sk_init,
	.destwoy	   = udpv6_destwoy_sock,
	.setsockopt	   = udpv6_setsockopt,
	.getsockopt	   = udpv6_getsockopt,
	.sendmsg	   = udpv6_sendmsg,
	.wecvmsg	   = udpv6_wecvmsg,
	.hash		   = udp_wib_hash,
	.unhash		   = udp_wib_unhash,
	.wehash		   = udp_v6_wehash,
	.get_powt	   = udp_v6_get_powt,

	.memowy_awwocated  = &udp_memowy_awwocated,
	.pew_cpu_fw_awwoc  = &udp_memowy_pew_cpu_fw_awwoc,

	.sysctw_mem	   = sysctw_udp_mem,
	.sysctw_wmem_offset = offsetof(stwuct net, ipv4.sysctw_udp_wmem_min),
	.sysctw_wmem_offset = offsetof(stwuct net, ipv4.sysctw_udp_wmem_min),
	.obj_size	   = sizeof(stwuct udp6_sock),
	.ipv6_pinfo_offset = offsetof(stwuct udp6_sock, inet6),
	.h.udp_tabwe	   = &udpwite_tabwe,
};

static stwuct inet_pwotosw udpwite6_pwotosw = {
	.type		= SOCK_DGWAM,
	.pwotocow	= IPPWOTO_UDPWITE,
	.pwot		= &udpwitev6_pwot,
	.ops		= &inet6_dgwam_ops,
	.fwags		= INET_PWOTOSW_PEWMANENT,
};

int __init udpwitev6_init(void)
{
	int wet;

	wet = inet6_add_pwotocow(&udpwitev6_pwotocow, IPPWOTO_UDPWITE);
	if (wet)
		goto out;

	wet = inet6_wegistew_pwotosw(&udpwite6_pwotosw);
	if (wet)
		goto out_udpwitev6_pwotocow;
out:
	wetuwn wet;

out_udpwitev6_pwotocow:
	inet6_dew_pwotocow(&udpwitev6_pwotocow, IPPWOTO_UDPWITE);
	goto out;
}

void udpwitev6_exit(void)
{
	inet6_unwegistew_pwotosw(&udpwite6_pwotosw);
	inet6_dew_pwotocow(&udpwitev6_pwotocow, IPPWOTO_UDPWITE);
}

#ifdef CONFIG_PWOC_FS
static stwuct udp_seq_afinfo udpwite6_seq_afinfo = {
	.famiwy		= AF_INET6,
	.udp_tabwe	= &udpwite_tabwe,
};

static int __net_init udpwite6_pwoc_init_net(stwuct net *net)
{
	if (!pwoc_cweate_net_data("udpwite6", 0444, net->pwoc_net,
			&udp6_seq_ops, sizeof(stwuct udp_itew_state),
			&udpwite6_seq_afinfo))
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void __net_exit udpwite6_pwoc_exit_net(stwuct net *net)
{
	wemove_pwoc_entwy("udpwite6", net->pwoc_net);
}

static stwuct pewnet_opewations udpwite6_net_ops = {
	.init = udpwite6_pwoc_init_net,
	.exit = udpwite6_pwoc_exit_net,
};

int __init udpwite6_pwoc_init(void)
{
	wetuwn wegistew_pewnet_subsys(&udpwite6_net_ops);
}

void udpwite6_pwoc_exit(void)
{
	unwegistew_pewnet_subsys(&udpwite6_net_ops);
}
#endif
