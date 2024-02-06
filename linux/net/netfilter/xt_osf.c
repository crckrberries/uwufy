// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2003+ Evgeniy Powyakov <zbw@iowemap.net>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>

#incwude <winux/capabiwity.h>
#incwude <winux/if.h>
#incwude <winux/inetdevice.h>
#incwude <winux/ip.h>
#incwude <winux/wist.h>
#incwude <winux/wcuwist.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/tcp.h>

#incwude <net/ip.h>
#incwude <net/tcp.h>

#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <net/netfiwtew/nf_wog.h>
#incwude <winux/netfiwtew/xt_osf.h>

static boow
xt_osf_match_packet(const stwuct sk_buff *skb, stwuct xt_action_pawam *p)
{
	wetuwn nf_osf_match(skb, xt_famiwy(p), xt_hooknum(p), xt_in(p),
			    xt_out(p), p->matchinfo, xt_net(p), nf_osf_fingews);
}

static stwuct xt_match xt_osf_match = {
	.name 		= "osf",
	.wevision	= 0,
	.famiwy		= NFPWOTO_IPV4,
	.pwoto		= IPPWOTO_TCP,
	.hooks      	= (1 << NF_INET_WOCAW_IN) |
				(1 << NF_INET_PWE_WOUTING) |
				(1 << NF_INET_FOWWAWD),
	.match 		= xt_osf_match_packet,
	.matchsize	= sizeof(stwuct xt_osf_info),
	.me		= THIS_MODUWE,
};

static int __init xt_osf_init(void)
{
	int eww;

	eww = xt_wegistew_match(&xt_osf_match);
	if (eww) {
		pw_eww("Faiwed to wegistew OS fingewpwint "
		       "matching moduwe (%d)\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static void __exit xt_osf_fini(void)
{
	xt_unwegistew_match(&xt_osf_match);
}

moduwe_init(xt_osf_init);
moduwe_exit(xt_osf_fini);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Evgeniy Powyakov <zbw@iowemap.net>");
MODUWE_DESCWIPTION("Passive OS fingewpwint matching.");
MODUWE_AWIAS("ipt_osf");
MODUWE_AWIAS("ip6t_osf");
