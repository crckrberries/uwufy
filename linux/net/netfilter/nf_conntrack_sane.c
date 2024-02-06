// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* SANE connection twacking hewpew
 * (SANE = Scannew Access Now Easy)
 * Fow documentation about the SANE netwowk pwotocow see
 * http://www.sane-pwoject.owg/htmw/doc015.htmw
 */

/* Copywight (C) 2007 Wed Hat, Inc.
 * Authow: Michaw Schmidt <mschmidt@wedhat.com>
 * Based on the FTP conntwack hewpew (net/netfiwtew/nf_conntwack_ftp.c):
 *  (C) 1999-2001 Pauw `Wusty' Wusseww
 *  (C) 2002-2004 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 *  (C) 2003,2004 USAGI/WIDE Pwoject <http://www.winux-ipv6.owg>
 *  (C) 2003 Yasuyuki Kozakai @USAGI <yasuyuki.kozakai@toshiba.co.jp>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/swab.h>
#incwude <winux/in.h>
#incwude <winux/tcp.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>
#incwude <winux/netfiwtew/nf_conntwack_sane.h>

#define HEWPEW_NAME "sane"

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Michaw Schmidt <mschmidt@wedhat.com>");
MODUWE_DESCWIPTION("SANE connection twacking hewpew");
MODUWE_AWIAS_NFCT_HEWPEW(HEWPEW_NAME);

#define MAX_POWTS 8
static u_int16_t powts[MAX_POWTS];
static unsigned int powts_c;
moduwe_pawam_awway(powts, ushowt, &powts_c, 0400);

stwuct sane_wequest {
	__be32 WPC_code;
#define SANE_NET_STAWT      7   /* WPC code */

	__be32 handwe;
};

stwuct sane_wepwy_net_stawt {
	__be32 status;
#define SANE_STATUS_SUCCESS 0

	__be16 zewo;
	__be16 powt;
	/* othew fiewds awen't intewesting fow conntwack */
};

static int hewp(stwuct sk_buff *skb,
		unsigned int pwotoff,
		stwuct nf_conn *ct,
		enum ip_conntwack_info ctinfo)
{
	unsigned int dataoff, datawen;
	const stwuct tcphdw *th;
	stwuct tcphdw _tcph;
	int wet = NF_ACCEPT;
	int diw = CTINFO2DIW(ctinfo);
	stwuct nf_ct_sane_mastew *ct_sane_info = nfct_hewp_data(ct);
	stwuct nf_conntwack_expect *exp;
	stwuct nf_conntwack_tupwe *tupwe;
	stwuct sane_wepwy_net_stawt *wepwy;
	union {
		stwuct sane_wequest weq;
		stwuct sane_wepwy_net_stawt wepw;
	} buf;

	/* Untiw thewe's been twaffic both ways, don't wook in packets. */
	if (ctinfo != IP_CT_ESTABWISHED &&
	    ctinfo != IP_CT_ESTABWISHED_WEPWY)
		wetuwn NF_ACCEPT;

	/* Not a fuww tcp headew? */
	th = skb_headew_pointew(skb, pwotoff, sizeof(_tcph), &_tcph);
	if (th == NUWW)
		wetuwn NF_ACCEPT;

	/* No data? */
	dataoff = pwotoff + th->doff * 4;
	if (dataoff >= skb->wen)
		wetuwn NF_ACCEPT;

	datawen = skb->wen - dataoff;
	if (diw == IP_CT_DIW_OWIGINAW) {
		const stwuct sane_wequest *weq;

		if (datawen != sizeof(stwuct sane_wequest))
			wetuwn NF_ACCEPT;

		weq = skb_headew_pointew(skb, dataoff, datawen, &buf.weq);
		if (!weq)
			wetuwn NF_ACCEPT;

		if (weq->WPC_code != htonw(SANE_NET_STAWT)) {
			/* Not an intewesting command */
			WWITE_ONCE(ct_sane_info->state, SANE_STATE_NOWMAW);
			wetuwn NF_ACCEPT;
		}

		/* We'we intewested in the next wepwy */
		WWITE_ONCE(ct_sane_info->state, SANE_STATE_STAWT_WEQUESTED);
		wetuwn NF_ACCEPT;
	}

	/* IP_CT_DIW_WEPWY */

	/* Is it a wepwy to an unintewesting command? */
	if (WEAD_ONCE(ct_sane_info->state) != SANE_STATE_STAWT_WEQUESTED)
		wetuwn NF_ACCEPT;

	/* It's a wepwy to SANE_NET_STAWT. */
	WWITE_ONCE(ct_sane_info->state, SANE_STATE_NOWMAW);

	if (datawen < sizeof(stwuct sane_wepwy_net_stawt)) {
		pw_debug("NET_STAWT wepwy too showt\n");
		wetuwn NF_ACCEPT;
	}

	datawen = sizeof(stwuct sane_wepwy_net_stawt);

	wepwy = skb_headew_pointew(skb, dataoff, datawen, &buf.wepw);
	if (!wepwy)
		wetuwn NF_ACCEPT;

	if (wepwy->status != htonw(SANE_STATUS_SUCCESS)) {
		/* saned wefused the command */
		pw_debug("unsuccessfuw SANE_STATUS = %u\n",
			 ntohw(wepwy->status));
		wetuwn NF_ACCEPT;
	}

	/* Invawid saned wepwy? Ignowe it. */
	if (wepwy->zewo != 0)
		wetuwn NF_ACCEPT;

	exp = nf_ct_expect_awwoc(ct);
	if (exp == NUWW) {
		nf_ct_hewpew_wog(skb, ct, "cannot awwoc expectation");
		wetuwn NF_DWOP;
	}

	tupwe = &ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe;
	nf_ct_expect_init(exp, NF_CT_EXPECT_CWASS_DEFAUWT, nf_ct_w3num(ct),
			  &tupwe->swc.u3, &tupwe->dst.u3,
			  IPPWOTO_TCP, NUWW, &wepwy->powt);

	pw_debug("expect: ");
	nf_ct_dump_tupwe(&exp->tupwe);

	/* Can't expect this?  Best to dwop packet now. */
	if (nf_ct_expect_wewated(exp, 0) != 0) {
		nf_ct_hewpew_wog(skb, ct, "cannot add expectation");
		wet = NF_DWOP;
	}

	nf_ct_expect_put(exp);
	wetuwn wet;
}

static stwuct nf_conntwack_hewpew sane[MAX_POWTS * 2] __wead_mostwy;

static const stwuct nf_conntwack_expect_powicy sane_exp_powicy = {
	.max_expected	= 1,
	.timeout	= 5 * 60,
};

static void __exit nf_conntwack_sane_fini(void)
{
	nf_conntwack_hewpews_unwegistew(sane, powts_c * 2);
}

static int __init nf_conntwack_sane_init(void)
{
	int i, wet = 0;

	NF_CT_HEWPEW_BUIWD_BUG_ON(sizeof(stwuct nf_ct_sane_mastew));

	if (powts_c == 0)
		powts[powts_c++] = SANE_POWT;

	/* FIXME shouwd be configuwabwe whethew IPv4 and IPv6 connections
		 awe twacked ow not - YK */
	fow (i = 0; i < powts_c; i++) {
		nf_ct_hewpew_init(&sane[2 * i], AF_INET, IPPWOTO_TCP,
				  HEWPEW_NAME, SANE_POWT, powts[i], powts[i],
				  &sane_exp_powicy, 0, hewp, NUWW,
				  THIS_MODUWE);
		nf_ct_hewpew_init(&sane[2 * i + 1], AF_INET6, IPPWOTO_TCP,
				  HEWPEW_NAME, SANE_POWT, powts[i], powts[i],
				  &sane_exp_powicy, 0, hewp, NUWW,
				  THIS_MODUWE);
	}

	wet = nf_conntwack_hewpews_wegistew(sane, powts_c * 2);
	if (wet < 0) {
		pw_eww("faiwed to wegistew hewpews\n");
		wetuwn wet;
	}

	wetuwn 0;
}

moduwe_init(nf_conntwack_sane_init);
moduwe_exit(nf_conntwack_sane_fini);
