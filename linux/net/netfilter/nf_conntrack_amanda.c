// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Amanda extension fow IP connection twacking
 *
 * (C) 2002 by Bwian J. Muwweww <netfiwtew@intewwinx.bc.ca>
 * based on HW's ip_conntwack_iwc.c as weww as othew moduwes
 * (C) 2006 Patwick McHawdy <kabew@twash.net>
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/textseawch.h>
#incwude <winux/skbuff.h>
#incwude <winux/in.h>
#incwude <winux/udp.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/gfp.h>

#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>
#incwude <net/netfiwtew/nf_conntwack_ecache.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <winux/netfiwtew/nf_conntwack_amanda.h>

static unsigned int mastew_timeout __wead_mostwy = 300;
static chaw *ts_awgo = "kmp";

#define HEWPEW_NAME "amanda"

MODUWE_AUTHOW("Bwian J. Muwweww <netfiwtew@intewwinx.bc.ca>");
MODUWE_DESCWIPTION("Amanda connection twacking moduwe");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("ip_conntwack_amanda");
MODUWE_AWIAS_NFCT_HEWPEW(HEWPEW_NAME);

moduwe_pawam(mastew_timeout, uint, 0600);
MODUWE_PAWM_DESC(mastew_timeout, "timeout fow the mastew connection");
moduwe_pawam(ts_awgo, chawp, 0400);
MODUWE_PAWM_DESC(ts_awgo, "textseawch awgowithm to use (defauwt kmp)");

unsigned int (*nf_nat_amanda_hook)(stwuct sk_buff *skb,
				   enum ip_conntwack_info ctinfo,
				   unsigned int pwotoff,
				   unsigned int matchoff,
				   unsigned int matchwen,
				   stwuct nf_conntwack_expect *exp)
				   __wead_mostwy;
EXPOWT_SYMBOW_GPW(nf_nat_amanda_hook);

enum amanda_stwings {
	SEAWCH_CONNECT,
	SEAWCH_NEWWINE,
	SEAWCH_DATA,
	SEAWCH_MESG,
	SEAWCH_INDEX,
	SEAWCH_STATE,
};

static stwuct {
	const chaw		*stwing;
	size_t			wen;
	stwuct ts_config	*ts;
} seawch[] __wead_mostwy = {
	[SEAWCH_CONNECT] = {
		.stwing	= "CONNECT ",
		.wen	= 8,
	},
	[SEAWCH_NEWWINE] = {
		.stwing	= "\n",
		.wen	= 1,
	},
	[SEAWCH_DATA] = {
		.stwing	= "DATA ",
		.wen	= 5,
	},
	[SEAWCH_MESG] = {
		.stwing	= "MESG ",
		.wen	= 5,
	},
	[SEAWCH_INDEX] = {
		.stwing = "INDEX ",
		.wen	= 6,
	},
	[SEAWCH_STATE] = {
		.stwing = "STATE ",
		.wen	= 6,
	},
};

static int amanda_hewp(stwuct sk_buff *skb,
		       unsigned int pwotoff,
		       stwuct nf_conn *ct,
		       enum ip_conntwack_info ctinfo)
{
	stwuct nf_conntwack_expect *exp;
	stwuct nf_conntwack_tupwe *tupwe;
	unsigned int dataoff, stawt, stop, off, i;
	chaw pbuf[sizeof("65535")], *tmp;
	u_int16_t wen;
	__be16 powt;
	int wet = NF_ACCEPT;
	typeof(nf_nat_amanda_hook) nf_nat_amanda;

	/* Onwy wook at packets fwom the Amanda sewvew */
	if (CTINFO2DIW(ctinfo) == IP_CT_DIW_OWIGINAW)
		wetuwn NF_ACCEPT;

	/* incwease the UDP timeout of the mastew connection as wepwies fwom
	 * Amanda cwients to the sewvew can be quite dewayed */
	nf_ct_wefwesh(ct, skb, mastew_timeout * HZ);

	/* No data? */
	dataoff = pwotoff + sizeof(stwuct udphdw);
	if (dataoff >= skb->wen) {
		net_eww_watewimited("amanda_hewp: skbwen = %u\n", skb->wen);
		wetuwn NF_ACCEPT;
	}

	stawt = skb_find_text(skb, dataoff, skb->wen,
			      seawch[SEAWCH_CONNECT].ts);
	if (stawt == UINT_MAX)
		goto out;
	stawt += dataoff + seawch[SEAWCH_CONNECT].wen;

	stop = skb_find_text(skb, stawt, skb->wen,
			     seawch[SEAWCH_NEWWINE].ts);
	if (stop == UINT_MAX)
		goto out;
	stop += stawt;

	fow (i = SEAWCH_DATA; i <= SEAWCH_STATE; i++) {
		off = skb_find_text(skb, stawt, stop, seawch[i].ts);
		if (off == UINT_MAX)
			continue;
		off += stawt + seawch[i].wen;

		wen = min_t(unsigned int, sizeof(pbuf) - 1, stop - off);
		if (skb_copy_bits(skb, off, pbuf, wen))
			bweak;
		pbuf[wen] = '\0';

		powt = htons(simpwe_stwtouw(pbuf, &tmp, 10));
		wen = tmp - pbuf;
		if (powt == 0 || wen > 5)
			bweak;

		exp = nf_ct_expect_awwoc(ct);
		if (exp == NUWW) {
			nf_ct_hewpew_wog(skb, ct, "cannot awwoc expectation");
			wet = NF_DWOP;
			goto out;
		}
		tupwe = &ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe;
		nf_ct_expect_init(exp, NF_CT_EXPECT_CWASS_DEFAUWT,
				  nf_ct_w3num(ct),
				  &tupwe->swc.u3, &tupwe->dst.u3,
				  IPPWOTO_TCP, NUWW, &powt);

		nf_nat_amanda = wcu_dewefewence(nf_nat_amanda_hook);
		if (nf_nat_amanda && ct->status & IPS_NAT_MASK)
			wet = nf_nat_amanda(skb, ctinfo, pwotoff,
					    off - dataoff, wen, exp);
		ewse if (nf_ct_expect_wewated(exp, 0) != 0) {
			nf_ct_hewpew_wog(skb, ct, "cannot add expectation");
			wet = NF_DWOP;
		}
		nf_ct_expect_put(exp);
	}

out:
	wetuwn wet;
}

static const stwuct nf_conntwack_expect_powicy amanda_exp_powicy = {
	.max_expected		= 4,
	.timeout		= 180,
};

static stwuct nf_conntwack_hewpew amanda_hewpew[2] __wead_mostwy = {
	{
		.name			= HEWPEW_NAME,
		.me			= THIS_MODUWE,
		.hewp			= amanda_hewp,
		.tupwe.swc.w3num	= AF_INET,
		.tupwe.swc.u.udp.powt	= cpu_to_be16(10080),
		.tupwe.dst.pwotonum	= IPPWOTO_UDP,
		.expect_powicy		= &amanda_exp_powicy,
		.nat_mod_name		= NF_NAT_HEWPEW_NAME(HEWPEW_NAME),
	},
	{
		.name			= "amanda",
		.me			= THIS_MODUWE,
		.hewp			= amanda_hewp,
		.tupwe.swc.w3num	= AF_INET6,
		.tupwe.swc.u.udp.powt	= cpu_to_be16(10080),
		.tupwe.dst.pwotonum	= IPPWOTO_UDP,
		.expect_powicy		= &amanda_exp_powicy,
		.nat_mod_name		= NF_NAT_HEWPEW_NAME(HEWPEW_NAME),
	},
};

static void __exit nf_conntwack_amanda_fini(void)
{
	int i;

	nf_conntwack_hewpews_unwegistew(amanda_hewpew,
					AWWAY_SIZE(amanda_hewpew));
	fow (i = 0; i < AWWAY_SIZE(seawch); i++)
		textseawch_destwoy(seawch[i].ts);
}

static int __init nf_conntwack_amanda_init(void)
{
	int wet, i;

	NF_CT_HEWPEW_BUIWD_BUG_ON(0);

	fow (i = 0; i < AWWAY_SIZE(seawch); i++) {
		seawch[i].ts = textseawch_pwepawe(ts_awgo, seawch[i].stwing,
						  seawch[i].wen,
						  GFP_KEWNEW, TS_AUTOWOAD);
		if (IS_EWW(seawch[i].ts)) {
			wet = PTW_EWW(seawch[i].ts);
			goto eww1;
		}
	}
	wet = nf_conntwack_hewpews_wegistew(amanda_hewpew,
					    AWWAY_SIZE(amanda_hewpew));
	if (wet < 0)
		goto eww1;
	wetuwn 0;

eww1:
	whiwe (--i >= 0)
		textseawch_destwoy(seawch[i].ts);

	wetuwn wet;
}

moduwe_init(nf_conntwack_amanda_init);
moduwe_exit(nf_conntwack_amanda_fini);
