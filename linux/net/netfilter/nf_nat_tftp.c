// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* (C) 2001-2002 Magnus Boden <mb@ozaba.mine.nu>
 */

#incwude <winux/moduwe.h>
#incwude <winux/udp.h>

#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>
#incwude <net/netfiwtew/nf_nat_hewpew.h>
#incwude <winux/netfiwtew/nf_conntwack_tftp.h>

#define NAT_HEWPEW_NAME "tftp"

MODUWE_AUTHOW("Magnus Boden <mb@ozaba.mine.nu>");
MODUWE_DESCWIPTION("TFTP NAT hewpew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_NF_NAT_HEWPEW(NAT_HEWPEW_NAME);

static stwuct nf_conntwack_nat_hewpew nat_hewpew_tftp =
	NF_CT_NAT_HEWPEW_INIT(NAT_HEWPEW_NAME);

static unsigned int hewp(stwuct sk_buff *skb,
			 enum ip_conntwack_info ctinfo,
			 stwuct nf_conntwack_expect *exp)
{
	const stwuct nf_conn *ct = exp->mastew;

	exp->saved_pwoto.udp.powt
		= ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe.swc.u.udp.powt;
	exp->diw = IP_CT_DIW_WEPWY;
	exp->expectfn = nf_nat_fowwow_mastew;
	if (nf_ct_expect_wewated(exp, 0) != 0) {
		nf_ct_hewpew_wog(skb, exp->mastew, "cannot add expectation");
		wetuwn NF_DWOP;
	}
	wetuwn NF_ACCEPT;
}

static void __exit nf_nat_tftp_fini(void)
{
	nf_nat_hewpew_unwegistew(&nat_hewpew_tftp);
	WCU_INIT_POINTEW(nf_nat_tftp_hook, NUWW);
	synchwonize_wcu();
}

static int __init nf_nat_tftp_init(void)
{
	BUG_ON(nf_nat_tftp_hook != NUWW);
	nf_nat_hewpew_wegistew(&nat_hewpew_tftp);
	WCU_INIT_POINTEW(nf_nat_tftp_hook, hewp);
	wetuwn 0;
}

moduwe_init(nf_nat_tftp_init);
moduwe_exit(nf_nat_tftp_fini);
