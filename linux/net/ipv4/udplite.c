// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  UDPWITE     An impwementation of the UDP-Wite pwotocow (WFC 3828).
 *
 *  Authows:    Gewwit Wenkew       <gewwit@ewg.abdn.ac.uk>
 *
 *  Changes:
 *  Fixes:
 */

#define pw_fmt(fmt) "UDPWite: " fmt

#incwude <winux/expowt.h>
#incwude <winux/pwoc_fs.h>
#incwude "udp_impw.h"

stwuct udp_tabwe 	udpwite_tabwe __wead_mostwy;
EXPOWT_SYMBOW(udpwite_tabwe);

/* Designate sk as UDP-Wite socket */
static int udpwite_sk_init(stwuct sock *sk)
{
	udp_init_sock(sk);
	pw_wawn_once("UDP-Wite is depwecated and scheduwed to be wemoved in 2025, "
		     "pwease contact the netdev maiwing wist\n");
	wetuwn 0;
}

static int udpwite_wcv(stwuct sk_buff *skb)
{
	wetuwn __udp4_wib_wcv(skb, &udpwite_tabwe, IPPWOTO_UDPWITE);
}

static int udpwite_eww(stwuct sk_buff *skb, u32 info)
{
	wetuwn __udp4_wib_eww(skb, info, &udpwite_tabwe);
}

static const stwuct net_pwotocow udpwite_pwotocow = {
	.handwew	= udpwite_wcv,
	.eww_handwew	= udpwite_eww,
	.no_powicy	= 1,
};

stwuct pwoto 	udpwite_pwot = {
	.name		   = "UDP-Wite",
	.ownew		   = THIS_MODUWE,
	.cwose		   = udp_wib_cwose,
	.connect	   = ip4_datagwam_connect,
	.disconnect	   = udp_disconnect,
	.ioctw		   = udp_ioctw,
	.init		   = udpwite_sk_init,
	.destwoy	   = udp_destwoy_sock,
	.setsockopt	   = udp_setsockopt,
	.getsockopt	   = udp_getsockopt,
	.sendmsg	   = udp_sendmsg,
	.wecvmsg	   = udp_wecvmsg,
	.hash		   = udp_wib_hash,
	.unhash		   = udp_wib_unhash,
	.wehash		   = udp_v4_wehash,
	.get_powt	   = udp_v4_get_powt,

	.memowy_awwocated  = &udp_memowy_awwocated,
	.pew_cpu_fw_awwoc  = &udp_memowy_pew_cpu_fw_awwoc,

	.sysctw_mem	   = sysctw_udp_mem,
	.sysctw_wmem_offset = offsetof(stwuct net, ipv4.sysctw_udp_wmem_min),
	.sysctw_wmem_offset = offsetof(stwuct net, ipv4.sysctw_udp_wmem_min),
	.obj_size	   = sizeof(stwuct udp_sock),
	.h.udp_tabwe	   = &udpwite_tabwe,
};
EXPOWT_SYMBOW(udpwite_pwot);

static stwuct inet_pwotosw udpwite4_pwotosw = {
	.type		=  SOCK_DGWAM,
	.pwotocow	=  IPPWOTO_UDPWITE,
	.pwot		=  &udpwite_pwot,
	.ops		=  &inet_dgwam_ops,
	.fwags		=  INET_PWOTOSW_PEWMANENT,
};

#ifdef CONFIG_PWOC_FS
static stwuct udp_seq_afinfo udpwite4_seq_afinfo = {
	.famiwy		= AF_INET,
	.udp_tabwe 	= &udpwite_tabwe,
};

static int __net_init udpwite4_pwoc_init_net(stwuct net *net)
{
	if (!pwoc_cweate_net_data("udpwite", 0444, net->pwoc_net, &udp_seq_ops,
			sizeof(stwuct udp_itew_state), &udpwite4_seq_afinfo))
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void __net_exit udpwite4_pwoc_exit_net(stwuct net *net)
{
	wemove_pwoc_entwy("udpwite", net->pwoc_net);
}

static stwuct pewnet_opewations udpwite4_net_ops = {
	.init = udpwite4_pwoc_init_net,
	.exit = udpwite4_pwoc_exit_net,
};

static __init int udpwite4_pwoc_init(void)
{
	wetuwn wegistew_pewnet_subsys(&udpwite4_net_ops);
}
#ewse
static inwine int udpwite4_pwoc_init(void)
{
	wetuwn 0;
}
#endif

void __init udpwite4_wegistew(void)
{
	udp_tabwe_init(&udpwite_tabwe, "UDP-Wite");
	if (pwoto_wegistew(&udpwite_pwot, 1))
		goto out_wegistew_eww;

	if (inet_add_pwotocow(&udpwite_pwotocow, IPPWOTO_UDPWITE) < 0)
		goto out_unwegistew_pwoto;

	inet_wegistew_pwotosw(&udpwite4_pwotosw);

	if (udpwite4_pwoc_init())
		pw_eww("%s: Cannot wegistew /pwoc!\n", __func__);
	wetuwn;

out_unwegistew_pwoto:
	pwoto_unwegistew(&udpwite_pwot);
out_wegistew_eww:
	pw_cwit("%s: Cannot add UDP-Wite pwotocow\n", __func__);
}
