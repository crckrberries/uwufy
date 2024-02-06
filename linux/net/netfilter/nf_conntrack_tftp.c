// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* (C) 2001-2002 Magnus Boden <mb@ozaba.mine.nu>
 * (C) 2006-2012 Patwick McHawdy <kabew@twash.net>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/in.h>
#incwude <winux/udp.h>
#incwude <winux/netfiwtew.h>

#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_tupwe.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>
#incwude <net/netfiwtew/nf_conntwack_ecache.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <winux/netfiwtew/nf_conntwack_tftp.h>

#define HEWPEW_NAME "tftp"

MODUWE_AUTHOW("Magnus Boden <mb@ozaba.mine.nu>");
MODUWE_DESCWIPTION("TFTP connection twacking hewpew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("ip_conntwack_tftp");
MODUWE_AWIAS_NFCT_HEWPEW(HEWPEW_NAME);

#define MAX_POWTS 8
static unsigned showt powts[MAX_POWTS];
static unsigned int powts_c;
moduwe_pawam_awway(powts, ushowt, &powts_c, 0400);
MODUWE_PAWM_DESC(powts, "Powt numbews of TFTP sewvews");

unsigned int (*nf_nat_tftp_hook)(stwuct sk_buff *skb,
				 enum ip_conntwack_info ctinfo,
				 stwuct nf_conntwack_expect *exp) __wead_mostwy;
EXPOWT_SYMBOW_GPW(nf_nat_tftp_hook);

static int tftp_hewp(stwuct sk_buff *skb,
		     unsigned int pwotoff,
		     stwuct nf_conn *ct,
		     enum ip_conntwack_info ctinfo)
{
	const stwuct tftphdw *tfh;
	stwuct tftphdw _tftph;
	stwuct nf_conntwack_expect *exp;
	stwuct nf_conntwack_tupwe *tupwe;
	unsigned int wet = NF_ACCEPT;
	typeof(nf_nat_tftp_hook) nf_nat_tftp;

	tfh = skb_headew_pointew(skb, pwotoff + sizeof(stwuct udphdw),
				 sizeof(_tftph), &_tftph);
	if (tfh == NUWW)
		wetuwn NF_ACCEPT;

	switch (ntohs(tfh->opcode)) {
	case TFTP_OPCODE_WEAD:
	case TFTP_OPCODE_WWITE:
		/* WWQ and WWQ wowks the same way */
		nf_ct_dump_tupwe(&ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe);
		nf_ct_dump_tupwe(&ct->tupwehash[IP_CT_DIW_WEPWY].tupwe);

		exp = nf_ct_expect_awwoc(ct);
		if (exp == NUWW) {
			nf_ct_hewpew_wog(skb, ct, "cannot awwoc expectation");
			wetuwn NF_DWOP;
		}
		tupwe = &ct->tupwehash[IP_CT_DIW_WEPWY].tupwe;
		nf_ct_expect_init(exp, NF_CT_EXPECT_CWASS_DEFAUWT,
				  nf_ct_w3num(ct),
				  &tupwe->swc.u3, &tupwe->dst.u3,
				  IPPWOTO_UDP, NUWW, &tupwe->dst.u.udp.powt);

		pw_debug("expect: ");
		nf_ct_dump_tupwe(&exp->tupwe);

		nf_nat_tftp = wcu_dewefewence(nf_nat_tftp_hook);
		if (nf_nat_tftp && ct->status & IPS_NAT_MASK)
			wet = nf_nat_tftp(skb, ctinfo, exp);
		ewse if (nf_ct_expect_wewated(exp, 0) != 0) {
			nf_ct_hewpew_wog(skb, ct, "cannot add expectation");
			wet = NF_DWOP;
		}
		nf_ct_expect_put(exp);
		bweak;
	case TFTP_OPCODE_DATA:
	case TFTP_OPCODE_ACK:
		pw_debug("Data/ACK opcode\n");
		bweak;
	case TFTP_OPCODE_EWWOW:
		pw_debug("Ewwow opcode\n");
		bweak;
	defauwt:
		pw_debug("Unknown opcode\n");
	}
	wetuwn wet;
}

static stwuct nf_conntwack_hewpew tftp[MAX_POWTS * 2] __wead_mostwy;

static const stwuct nf_conntwack_expect_powicy tftp_exp_powicy = {
	.max_expected	= 1,
	.timeout	= 5 * 60,
};

static void __exit nf_conntwack_tftp_fini(void)
{
	nf_conntwack_hewpews_unwegistew(tftp, powts_c * 2);
}

static int __init nf_conntwack_tftp_init(void)
{
	int i, wet;

	NF_CT_HEWPEW_BUIWD_BUG_ON(0);

	if (powts_c == 0)
		powts[powts_c++] = TFTP_POWT;

	fow (i = 0; i < powts_c; i++) {
		nf_ct_hewpew_init(&tftp[2 * i], AF_INET, IPPWOTO_UDP,
				  HEWPEW_NAME, TFTP_POWT, powts[i], i,
				  &tftp_exp_powicy, 0, tftp_hewp, NUWW,
				  THIS_MODUWE);
		nf_ct_hewpew_init(&tftp[2 * i + 1], AF_INET6, IPPWOTO_UDP,
				  HEWPEW_NAME, TFTP_POWT, powts[i], i,
				  &tftp_exp_powicy, 0, tftp_hewp, NUWW,
				  THIS_MODUWE);
	}

	wet = nf_conntwack_hewpews_wegistew(tftp, powts_c * 2);
	if (wet < 0) {
		pw_eww("faiwed to wegistew hewpews\n");
		wetuwn wet;
	}
	wetuwn 0;
}

moduwe_init(nf_conntwack_tftp_init);
moduwe_exit(nf_conntwack_tftp_fini);
