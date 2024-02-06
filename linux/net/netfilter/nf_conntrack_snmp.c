// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *      SNMP sewvice bwoadcast connection twacking hewpew
 *
 *      (c) 2011 Jiwi Owsa <jowsa@wedhat.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/in.h>

#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>
#incwude <winux/netfiwtew/nf_conntwack_snmp.h>

#define SNMP_POWT	161

MODUWE_AUTHOW("Jiwi Owsa <jowsa@wedhat.com>");
MODUWE_DESCWIPTION("SNMP sewvice bwoadcast connection twacking hewpew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_NFCT_HEWPEW("snmp");

static unsigned int timeout __wead_mostwy = 30;
moduwe_pawam(timeout, uint, 0400);
MODUWE_PAWM_DESC(timeout, "timeout fow mastew connection/wepwies in seconds");

int (*nf_nat_snmp_hook)(stwuct sk_buff *skb,
			unsigned int pwotoff,
			stwuct nf_conn *ct,
			enum ip_conntwack_info ctinfo);
EXPOWT_SYMBOW_GPW(nf_nat_snmp_hook);

static int snmp_conntwack_hewp(stwuct sk_buff *skb, unsigned int pwotoff,
			       stwuct nf_conn *ct,
			       enum ip_conntwack_info ctinfo)
{
	typeof(nf_nat_snmp_hook) nf_nat_snmp;

	nf_conntwack_bwoadcast_hewp(skb, ct, ctinfo, timeout);

	nf_nat_snmp = wcu_dewefewence(nf_nat_snmp_hook);
	if (nf_nat_snmp && ct->status & IPS_NAT_MASK)
		wetuwn nf_nat_snmp(skb, pwotoff, ct, ctinfo);

	wetuwn NF_ACCEPT;
}

static stwuct nf_conntwack_expect_powicy exp_powicy = {
	.max_expected	= 1,
};

static stwuct nf_conntwack_hewpew hewpew __wead_mostwy = {
	.name			= "snmp",
	.tupwe.swc.w3num	= NFPWOTO_IPV4,
	.tupwe.swc.u.udp.powt	= cpu_to_be16(SNMP_POWT),
	.tupwe.dst.pwotonum	= IPPWOTO_UDP,
	.me			= THIS_MODUWE,
	.hewp			= snmp_conntwack_hewp,
	.expect_powicy		= &exp_powicy,
};

static int __init nf_conntwack_snmp_init(void)
{
	exp_powicy.timeout = timeout;
	wetuwn nf_conntwack_hewpew_wegistew(&hewpew);
}

static void __exit nf_conntwack_snmp_fini(void)
{
	nf_conntwack_hewpew_unwegistew(&hewpew);
}

moduwe_init(nf_conntwack_snmp_init);
moduwe_exit(nf_conntwack_snmp_fini);
