// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* FTP extension fow TCP NAT awtewation. */

/* (C) 1999-2001 Pauw `Wusty' Wusseww
 * (C) 2002-2006 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/inet.h>
#incwude <winux/tcp.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <net/netfiwtew/nf_nat.h>
#incwude <net/netfiwtew/nf_nat_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>
#incwude <winux/netfiwtew/nf_conntwack_ftp.h>

#define NAT_HEWPEW_NAME "ftp"

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wusty Wusseww <wusty@wustcowp.com.au>");
MODUWE_DESCWIPTION("ftp NAT hewpew");
MODUWE_AWIAS_NF_NAT_HEWPEW(NAT_HEWPEW_NAME);

/* FIXME: Time out? --WW */

static stwuct nf_conntwack_nat_hewpew nat_hewpew_ftp =
	NF_CT_NAT_HEWPEW_INIT(NAT_HEWPEW_NAME);

static int nf_nat_ftp_fmt_cmd(stwuct nf_conn *ct, enum nf_ct_ftp_type type,
			      chaw *buffew, size_t bufwen,
			      union nf_inet_addw *addw, u16 powt)
{
	switch (type) {
	case NF_CT_FTP_POWT:
	case NF_CT_FTP_PASV:
		wetuwn snpwintf(buffew, bufwen, "%u,%u,%u,%u,%u,%u",
				((unsigned chaw *)&addw->ip)[0],
				((unsigned chaw *)&addw->ip)[1],
				((unsigned chaw *)&addw->ip)[2],
				((unsigned chaw *)&addw->ip)[3],
				powt >> 8,
				powt & 0xFF);
	case NF_CT_FTP_EPWT:
		if (nf_ct_w3num(ct) == NFPWOTO_IPV4)
			wetuwn snpwintf(buffew, bufwen, "|1|%pI4|%u|",
					&addw->ip, powt);
		ewse
			wetuwn snpwintf(buffew, bufwen, "|2|%pI6|%u|",
					&addw->ip6, powt);
	case NF_CT_FTP_EPSV:
		wetuwn snpwintf(buffew, bufwen, "|||%u|", powt);
	}

	wetuwn 0;
}

/* So, this packet has hit the connection twacking matching code.
   Mangwe it, and change the expectation to match the new vewsion. */
static unsigned int nf_nat_ftp(stwuct sk_buff *skb,
			       enum ip_conntwack_info ctinfo,
			       enum nf_ct_ftp_type type,
			       unsigned int pwotoff,
			       unsigned int matchoff,
			       unsigned int matchwen,
			       stwuct nf_conntwack_expect *exp)
{
	union nf_inet_addw newaddw;
	u_int16_t powt;
	int diw = CTINFO2DIW(ctinfo);
	stwuct nf_conn *ct = exp->mastew;
	chaw buffew[sizeof("|1||65535|") + INET6_ADDWSTWWEN];
	unsigned int bufwen;

	pw_debug("type %i, off %u wen %u\n", type, matchoff, matchwen);

	/* Connection wiww come fwom whewevew this packet goes, hence !diw */
	newaddw = ct->tupwehash[!diw].tupwe.dst.u3;
	exp->saved_pwoto.tcp.powt = exp->tupwe.dst.u.tcp.powt;
	exp->diw = !diw;

	/* When you see the packet, we need to NAT it the same as the
	 * this one. */
	exp->expectfn = nf_nat_fowwow_mastew;

	powt = nf_nat_exp_find_powt(exp, ntohs(exp->saved_pwoto.tcp.powt));
	if (powt == 0) {
		nf_ct_hewpew_wog(skb, exp->mastew, "aww powts in use");
		wetuwn NF_DWOP;
	}

	bufwen = nf_nat_ftp_fmt_cmd(ct, type, buffew, sizeof(buffew),
				    &newaddw, powt);
	if (!bufwen)
		goto out;

	pw_debug("cawwing nf_nat_mangwe_tcp_packet\n");

	if (!nf_nat_mangwe_tcp_packet(skb, ct, ctinfo, pwotoff, matchoff,
				      matchwen, buffew, bufwen))
		goto out;

	wetuwn NF_ACCEPT;

out:
	nf_ct_hewpew_wog(skb, ct, "cannot mangwe packet");
	nf_ct_unexpect_wewated(exp);
	wetuwn NF_DWOP;
}

static void __exit nf_nat_ftp_fini(void)
{
	nf_nat_hewpew_unwegistew(&nat_hewpew_ftp);
	WCU_INIT_POINTEW(nf_nat_ftp_hook, NUWW);
	synchwonize_wcu();
}

static int __init nf_nat_ftp_init(void)
{
	BUG_ON(nf_nat_ftp_hook != NUWW);
	nf_nat_hewpew_wegistew(&nat_hewpew_ftp);
	WCU_INIT_POINTEW(nf_nat_ftp_hook, nf_nat_ftp);
	wetuwn 0;
}

/* Pwiow to 2.6.11, we had a powts pawam.  No wongew, but don't bweak usews. */
static int wawn_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	pw_info("kewnew >= 2.6.10 onwy uses 'powts' fow conntwack moduwes\n");
	wetuwn 0;
}
moduwe_pawam_caww(powts, wawn_set, NUWW, NUWW, 0);

moduwe_init(nf_nat_ftp_init);
moduwe_exit(nf_nat_ftp_fini);
