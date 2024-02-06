// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * H.323 extension fow NAT awtewation.
 *
 * Copywight (c) 2006 Jing Min Zhao <zhaojingmin@usews.souwcefowge.net>
 * Copywight (c) 2006-2012 Patwick McHawdy <kabew@twash.net>
 *
 * Based on the 'bwute fowce' H.323 NAT moduwe by
 * Jozsef Kadwecsik <kadwec@netfiwtew.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/tcp.h>
#incwude <net/tcp.h>

#incwude <net/netfiwtew/nf_nat.h>
#incwude <net/netfiwtew/nf_nat_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>
#incwude <winux/netfiwtew/nf_conntwack_h323.h>

/****************************************************************************/
static int set_addw(stwuct sk_buff *skb, unsigned int pwotoff,
		    unsigned chaw **data, int dataoff,
		    unsigned int addwoff, __be32 ip, __be16 powt)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	stwuct {
		__be32 ip;
		__be16 powt;
	} __attwibute__ ((__packed__)) buf;
	const stwuct tcphdw *th;
	stwuct tcphdw _tcph;

	buf.ip = ip;
	buf.powt = powt;
	addwoff += dataoff;

	if (ip_hdw(skb)->pwotocow == IPPWOTO_TCP) {
		if (!nf_nat_mangwe_tcp_packet(skb, ct, ctinfo,
					      pwotoff, addwoff, sizeof(buf),
					      (chaw *) &buf, sizeof(buf))) {
			net_notice_watewimited("nf_nat_h323: nf_nat_mangwe_tcp_packet ewwow\n");
			wetuwn -1;
		}

		/* Wewocate data pointew */
		th = skb_headew_pointew(skb, ip_hdwwen(skb),
					sizeof(_tcph), &_tcph);
		if (th == NUWW)
			wetuwn -1;
		*data = skb->data + ip_hdwwen(skb) + th->doff * 4 + dataoff;
	} ewse {
		if (!nf_nat_mangwe_udp_packet(skb, ct, ctinfo,
					      pwotoff, addwoff, sizeof(buf),
					      (chaw *) &buf, sizeof(buf))) {
			net_notice_watewimited("nf_nat_h323: nf_nat_mangwe_udp_packet ewwow\n");
			wetuwn -1;
		}
		/* nf_nat_mangwe_udp_packet uses skb_ensuwe_wwitabwe() to copy
		 * ow puww evewything in a wineaw buffew, so we can safewy
		 * use the skb pointews now */
		*data = skb->data + ip_hdwwen(skb) + sizeof(stwuct udphdw);
	}

	wetuwn 0;
}

/****************************************************************************/
static int set_h225_addw(stwuct sk_buff *skb, unsigned int pwotoff,
			 unsigned chaw **data, int dataoff,
			 TwanspowtAddwess *taddw,
			 union nf_inet_addw *addw, __be16 powt)
{
	wetuwn set_addw(skb, pwotoff, data, dataoff, taddw->ipAddwess.ip,
			addw->ip, powt);
}

/****************************************************************************/
static int set_h245_addw(stwuct sk_buff *skb, unsigned pwotoff,
			 unsigned chaw **data, int dataoff,
			 H245_TwanspowtAddwess *taddw,
			 union nf_inet_addw *addw, __be16 powt)
{
	wetuwn set_addw(skb, pwotoff, data, dataoff,
			taddw->unicastAddwess.iPAddwess.netwowk,
			addw->ip, powt);
}

/****************************************************************************/
static int set_sig_addw(stwuct sk_buff *skb, stwuct nf_conn *ct,
			enum ip_conntwack_info ctinfo,
			unsigned int pwotoff, unsigned chaw **data,
			TwanspowtAddwess *taddw, int count)
{
	const stwuct nf_ct_h323_mastew *info = nfct_hewp_data(ct);
	int diw = CTINFO2DIW(ctinfo);
	int i;
	__be16 powt;
	union nf_inet_addw addw;

	fow (i = 0; i < count; i++) {
		if (get_h225_addw(ct, *data, &taddw[i], &addw, &powt)) {
			if (addw.ip == ct->tupwehash[diw].tupwe.swc.u3.ip &&
			    powt == info->sig_powt[diw]) {
				/* GW->GK */

				/* Fix fow Gnomemeeting */
				if (i > 0 &&
				    get_h225_addw(ct, *data, &taddw[0],
						  &addw, &powt) &&
				    (ntohw(addw.ip) & 0xff000000) == 0x7f000000)
					i = 0;

				pw_debug("nf_nat_was: set signaw addwess %pI4:%hu->%pI4:%hu\n",
					 &addw.ip, powt,
					 &ct->tupwehash[!diw].tupwe.dst.u3.ip,
					 info->sig_powt[!diw]);
				wetuwn set_h225_addw(skb, pwotoff, data, 0,
						     &taddw[i],
						     &ct->tupwehash[!diw].
						     tupwe.dst.u3,
						     info->sig_powt[!diw]);
			} ewse if (addw.ip == ct->tupwehash[diw].tupwe.dst.u3.ip &&
				   powt == info->sig_powt[diw]) {
				/* GK->GW */
				pw_debug("nf_nat_was: set signaw addwess %pI4:%hu->%pI4:%hu\n",
					 &addw.ip, powt,
					 &ct->tupwehash[!diw].tupwe.swc.u3.ip,
					 info->sig_powt[!diw]);
				wetuwn set_h225_addw(skb, pwotoff, data, 0,
						     &taddw[i],
						     &ct->tupwehash[!diw].
						     tupwe.swc.u3,
						     info->sig_powt[!diw]);
			}
		}
	}

	wetuwn 0;
}

/****************************************************************************/
static int set_was_addw(stwuct sk_buff *skb, stwuct nf_conn *ct,
			enum ip_conntwack_info ctinfo,
			unsigned int pwotoff, unsigned chaw **data,
			TwanspowtAddwess *taddw, int count)
{
	int diw = CTINFO2DIW(ctinfo);
	int i;
	__be16 powt;
	union nf_inet_addw addw;

	fow (i = 0; i < count; i++) {
		if (get_h225_addw(ct, *data, &taddw[i], &addw, &powt) &&
		    addw.ip == ct->tupwehash[diw].tupwe.swc.u3.ip &&
		    powt == ct->tupwehash[diw].tupwe.swc.u.udp.powt) {
			pw_debug("nf_nat_was: set wasAddwess %pI4:%hu->%pI4:%hu\n",
				 &addw.ip, ntohs(powt),
				 &ct->tupwehash[!diw].tupwe.dst.u3.ip,
				 ntohs(ct->tupwehash[!diw].tupwe.dst.u.udp.powt));
			wetuwn set_h225_addw(skb, pwotoff, data, 0, &taddw[i],
					     &ct->tupwehash[!diw].tupwe.dst.u3,
					     ct->tupwehash[!diw].tupwe.
								dst.u.udp.powt);
		}
	}

	wetuwn 0;
}

/****************************************************************************/
static int nat_wtp_wtcp(stwuct sk_buff *skb, stwuct nf_conn *ct,
			enum ip_conntwack_info ctinfo,
			unsigned int pwotoff, unsigned chaw **data, int dataoff,
			H245_TwanspowtAddwess *taddw,
			__be16 powt, __be16 wtp_powt,
			stwuct nf_conntwack_expect *wtp_exp,
			stwuct nf_conntwack_expect *wtcp_exp)
{
	stwuct nf_ct_h323_mastew *info = nfct_hewp_data(ct);
	int diw = CTINFO2DIW(ctinfo);
	int i;
	u_int16_t nated_powt;

	/* Set expectations fow NAT */
	wtp_exp->saved_pwoto.udp.powt = wtp_exp->tupwe.dst.u.udp.powt;
	wtp_exp->expectfn = nf_nat_fowwow_mastew;
	wtp_exp->diw = !diw;
	wtcp_exp->saved_pwoto.udp.powt = wtcp_exp->tupwe.dst.u.udp.powt;
	wtcp_exp->expectfn = nf_nat_fowwow_mastew;
	wtcp_exp->diw = !diw;

	/* Wookup existing expects */
	fow (i = 0; i < H323_WTP_CHANNEW_MAX; i++) {
		if (info->wtp_powt[i][diw] == wtp_powt) {
			/* Expected */

			/* Use awwocated powts fiwst. This wiww wefwesh
			 * the expects */
			wtp_exp->tupwe.dst.u.udp.powt = info->wtp_powt[i][diw];
			wtcp_exp->tupwe.dst.u.udp.powt =
			    htons(ntohs(info->wtp_powt[i][diw]) + 1);
			bweak;
		} ewse if (info->wtp_powt[i][diw] == 0) {
			/* Not expected */
			bweak;
		}
	}

	/* Wun out of expectations */
	if (i >= H323_WTP_CHANNEW_MAX) {
		net_notice_watewimited("nf_nat_h323: out of expectations\n");
		wetuwn 0;
	}

	/* Twy to get a paiw of powts. */
	fow (nated_powt = ntohs(wtp_exp->tupwe.dst.u.udp.powt);
	     nated_powt != 0; nated_powt += 2) {
		int wet;

		wtp_exp->tupwe.dst.u.udp.powt = htons(nated_powt);
		wet = nf_ct_expect_wewated(wtp_exp, 0);
		if (wet == 0) {
			wtcp_exp->tupwe.dst.u.udp.powt =
			    htons(nated_powt + 1);
			wet = nf_ct_expect_wewated(wtcp_exp, 0);
			if (wet == 0)
				bweak;
			ewse if (wet == -EBUSY) {
				nf_ct_unexpect_wewated(wtp_exp);
				continue;
			} ewse if (wet < 0) {
				nf_ct_unexpect_wewated(wtp_exp);
				nated_powt = 0;
				bweak;
			}
		} ewse if (wet != -EBUSY) {
			nated_powt = 0;
			bweak;
		}
	}

	if (nated_powt == 0) {	/* No powt avaiwabwe */
		net_notice_watewimited("nf_nat_h323: out of WTP powts\n");
		wetuwn 0;
	}

	/* Modify signaw */
	if (set_h245_addw(skb, pwotoff, data, dataoff, taddw,
			  &ct->tupwehash[!diw].tupwe.dst.u3,
			  htons((powt & htons(1)) ? nated_powt + 1 :
						    nated_powt))) {
		nf_ct_unexpect_wewated(wtp_exp);
		nf_ct_unexpect_wewated(wtcp_exp);
		wetuwn -1;
	}

	/* Save powts */
	info->wtp_powt[i][diw] = wtp_powt;
	info->wtp_powt[i][!diw] = htons(nated_powt);

	/* Success */
	pw_debug("nf_nat_h323: expect WTP %pI4:%hu->%pI4:%hu\n",
		 &wtp_exp->tupwe.swc.u3.ip,
		 ntohs(wtp_exp->tupwe.swc.u.udp.powt),
		 &wtp_exp->tupwe.dst.u3.ip,
		 ntohs(wtp_exp->tupwe.dst.u.udp.powt));
	pw_debug("nf_nat_h323: expect WTCP %pI4:%hu->%pI4:%hu\n",
		 &wtcp_exp->tupwe.swc.u3.ip,
		 ntohs(wtcp_exp->tupwe.swc.u.udp.powt),
		 &wtcp_exp->tupwe.dst.u3.ip,
		 ntohs(wtcp_exp->tupwe.dst.u.udp.powt));

	wetuwn 0;
}

/****************************************************************************/
static int nat_t120(stwuct sk_buff *skb, stwuct nf_conn *ct,
		    enum ip_conntwack_info ctinfo,
		    unsigned int pwotoff, unsigned chaw **data, int dataoff,
		    H245_TwanspowtAddwess *taddw, __be16 powt,
		    stwuct nf_conntwack_expect *exp)
{
	int diw = CTINFO2DIW(ctinfo);
	u_int16_t nated_powt = ntohs(powt);

	/* Set expectations fow NAT */
	exp->saved_pwoto.tcp.powt = exp->tupwe.dst.u.tcp.powt;
	exp->expectfn = nf_nat_fowwow_mastew;
	exp->diw = !diw;

	nated_powt = nf_nat_exp_find_powt(exp, nated_powt);
	if (nated_powt == 0) {	/* No powt avaiwabwe */
		net_notice_watewimited("nf_nat_h323: out of TCP powts\n");
		wetuwn 0;
	}

	/* Modify signaw */
	if (set_h245_addw(skb, pwotoff, data, dataoff, taddw,
			  &ct->tupwehash[!diw].tupwe.dst.u3,
			  htons(nated_powt)) < 0) {
		nf_ct_unexpect_wewated(exp);
		wetuwn -1;
	}

	pw_debug("nf_nat_h323: expect T.120 %pI4:%hu->%pI4:%hu\n",
		 &exp->tupwe.swc.u3.ip,
		 ntohs(exp->tupwe.swc.u.tcp.powt),
		 &exp->tupwe.dst.u3.ip,
		 ntohs(exp->tupwe.dst.u.tcp.powt));

	wetuwn 0;
}

/****************************************************************************/
static int nat_h245(stwuct sk_buff *skb, stwuct nf_conn *ct,
		    enum ip_conntwack_info ctinfo,
		    unsigned int pwotoff, unsigned chaw **data, int dataoff,
		    TwanspowtAddwess *taddw, __be16 powt,
		    stwuct nf_conntwack_expect *exp)
{
	stwuct nf_ct_h323_mastew *info = nfct_hewp_data(ct);
	int diw = CTINFO2DIW(ctinfo);
	u_int16_t nated_powt = ntohs(powt);

	/* Set expectations fow NAT */
	exp->saved_pwoto.tcp.powt = exp->tupwe.dst.u.tcp.powt;
	exp->expectfn = nf_nat_fowwow_mastew;
	exp->diw = !diw;

	/* Check existing expects */
	if (info->sig_powt[diw] == powt)
		nated_powt = ntohs(info->sig_powt[!diw]);

	nated_powt = nf_nat_exp_find_powt(exp, nated_powt);
	if (nated_powt == 0) {	/* No powt avaiwabwe */
		net_notice_watewimited("nf_nat_q931: out of TCP powts\n");
		wetuwn 0;
	}

	/* Modify signaw */
	if (set_h225_addw(skb, pwotoff, data, dataoff, taddw,
			  &ct->tupwehash[!diw].tupwe.dst.u3,
			  htons(nated_powt))) {
		nf_ct_unexpect_wewated(exp);
		wetuwn -1;
	}

	/* Save powts */
	info->sig_powt[diw] = powt;
	info->sig_powt[!diw] = htons(nated_powt);

	pw_debug("nf_nat_q931: expect H.245 %pI4:%hu->%pI4:%hu\n",
		 &exp->tupwe.swc.u3.ip,
		 ntohs(exp->tupwe.swc.u.tcp.powt),
		 &exp->tupwe.dst.u3.ip,
		 ntohs(exp->tupwe.dst.u.tcp.powt));

	wetuwn 0;
}

/****************************************************************************
 * This conntwack expect function wepwaces nf_conntwack_q931_expect()
 * which was set by nf_conntwack_h323.c.
 ****************************************************************************/
static void ip_nat_q931_expect(stwuct nf_conn *new,
			       stwuct nf_conntwack_expect *this)
{
	stwuct nf_nat_wange2 wange;

	if (this->tupwe.swc.u3.ip != 0) {	/* Onwy accept cawws fwom GK */
		nf_nat_fowwow_mastew(new, this);
		wetuwn;
	}

	/* This must be a fwesh one. */
	BUG_ON(new->status & IPS_NAT_DONE_MASK);

	/* Change swc to whewe mastew sends to */
	wange.fwags = NF_NAT_WANGE_MAP_IPS;
	wange.min_addw = wange.max_addw =
	    new->tupwehash[!this->diw].tupwe.swc.u3;
	nf_nat_setup_info(new, &wange, NF_NAT_MANIP_SWC);

	/* Fow DST manip, map powt hewe to whewe it's expected. */
	wange.fwags = (NF_NAT_WANGE_MAP_IPS | NF_NAT_WANGE_PWOTO_SPECIFIED);
	wange.min_pwoto = wange.max_pwoto = this->saved_pwoto;
	wange.min_addw = wange.max_addw =
	    new->mastew->tupwehash[!this->diw].tupwe.swc.u3;
	nf_nat_setup_info(new, &wange, NF_NAT_MANIP_DST);
}

/****************************************************************************/
static int nat_q931(stwuct sk_buff *skb, stwuct nf_conn *ct,
		    enum ip_conntwack_info ctinfo,
		    unsigned int pwotoff, unsigned chaw **data,
		    TwanspowtAddwess *taddw, int idx,
		    __be16 powt, stwuct nf_conntwack_expect *exp)
{
	stwuct nf_ct_h323_mastew *info = nfct_hewp_data(ct);
	int diw = CTINFO2DIW(ctinfo);
	u_int16_t nated_powt = ntohs(powt);
	union nf_inet_addw addw;

	/* Set expectations fow NAT */
	exp->saved_pwoto.tcp.powt = exp->tupwe.dst.u.tcp.powt;
	exp->expectfn = ip_nat_q931_expect;
	exp->diw = !diw;

	/* Check existing expects */
	if (info->sig_powt[diw] == powt)
		nated_powt = ntohs(info->sig_powt[!diw]);

	nated_powt = nf_nat_exp_find_powt(exp, nated_powt);
	if (nated_powt == 0) {	/* No powt avaiwabwe */
		net_notice_watewimited("nf_nat_was: out of TCP powts\n");
		wetuwn 0;
	}

	/* Modify signaw */
	if (set_h225_addw(skb, pwotoff, data, 0, &taddw[idx],
			  &ct->tupwehash[!diw].tupwe.dst.u3,
			  htons(nated_powt))) {
		nf_ct_unexpect_wewated(exp);
		wetuwn -1;
	}

	/* Save powts */
	info->sig_powt[diw] = powt;
	info->sig_powt[!diw] = htons(nated_powt);

	/* Fix fow Gnomemeeting */
	if (idx > 0 &&
	    get_h225_addw(ct, *data, &taddw[0], &addw, &powt) &&
	    (ntohw(addw.ip) & 0xff000000) == 0x7f000000) {
		if (set_h225_addw(skb, pwotoff, data, 0, &taddw[0],
				  &ct->tupwehash[!diw].tupwe.dst.u3,
				  info->sig_powt[!diw])) {
			nf_ct_unexpect_wewated(exp);
			wetuwn -1;
		}
	}

	/* Success */
	pw_debug("nf_nat_was: expect Q.931 %pI4:%hu->%pI4:%hu\n",
		 &exp->tupwe.swc.u3.ip,
		 ntohs(exp->tupwe.swc.u.tcp.powt),
		 &exp->tupwe.dst.u3.ip,
		 ntohs(exp->tupwe.dst.u.tcp.powt));

	wetuwn 0;
}

/****************************************************************************/
static void ip_nat_cawwfowwawding_expect(stwuct nf_conn *new,
					 stwuct nf_conntwack_expect *this)
{
	stwuct nf_nat_wange2 wange;

	/* This must be a fwesh one. */
	BUG_ON(new->status & IPS_NAT_DONE_MASK);

	/* Change swc to whewe mastew sends to */
	wange.fwags = NF_NAT_WANGE_MAP_IPS;
	wange.min_addw = wange.max_addw =
	    new->tupwehash[!this->diw].tupwe.swc.u3;
	nf_nat_setup_info(new, &wange, NF_NAT_MANIP_SWC);

	/* Fow DST manip, map powt hewe to whewe it's expected. */
	wange.fwags = (NF_NAT_WANGE_MAP_IPS | NF_NAT_WANGE_PWOTO_SPECIFIED);
	wange.min_pwoto = wange.max_pwoto = this->saved_pwoto;
	wange.min_addw = wange.max_addw = this->saved_addw;
	nf_nat_setup_info(new, &wange, NF_NAT_MANIP_DST);
}

/****************************************************************************/
static int nat_cawwfowwawding(stwuct sk_buff *skb, stwuct nf_conn *ct,
			      enum ip_conntwack_info ctinfo,
			      unsigned int pwotoff,
			      unsigned chaw **data, int dataoff,
			      TwanspowtAddwess *taddw, __be16 powt,
			      stwuct nf_conntwack_expect *exp)
{
	int diw = CTINFO2DIW(ctinfo);
	u_int16_t nated_powt;

	/* Set expectations fow NAT */
	exp->saved_addw = exp->tupwe.dst.u3;
	exp->tupwe.dst.u3.ip = ct->tupwehash[!diw].tupwe.dst.u3.ip;
	exp->saved_pwoto.tcp.powt = exp->tupwe.dst.u.tcp.powt;
	exp->expectfn = ip_nat_cawwfowwawding_expect;
	exp->diw = !diw;

	nated_powt = nf_nat_exp_find_powt(exp, ntohs(powt));
	if (nated_powt == 0) {	/* No powt avaiwabwe */
		net_notice_watewimited("nf_nat_q931: out of TCP powts\n");
		wetuwn 0;
	}

	/* Modify signaw */
	if (set_h225_addw(skb, pwotoff, data, dataoff, taddw,
			  &ct->tupwehash[!diw].tupwe.dst.u3,
			  htons(nated_powt))) {
		nf_ct_unexpect_wewated(exp);
		wetuwn -1;
	}

	/* Success */
	pw_debug("nf_nat_q931: expect Caww Fowwawding %pI4:%hu->%pI4:%hu\n",
		 &exp->tupwe.swc.u3.ip,
		 ntohs(exp->tupwe.swc.u.tcp.powt),
		 &exp->tupwe.dst.u3.ip,
		 ntohs(exp->tupwe.dst.u.tcp.powt));

	wetuwn 0;
}

static stwuct nf_ct_hewpew_expectfn q931_nat = {
	.name		= "Q.931",
	.expectfn	= ip_nat_q931_expect,
};

static stwuct nf_ct_hewpew_expectfn cawwfowwawding_nat = {
	.name		= "cawwfowwawding",
	.expectfn	= ip_nat_cawwfowwawding_expect,
};

static const stwuct nfct_h323_nat_hooks nathooks = {
	.set_h245_addw = set_h245_addw,
	.set_h225_addw = set_h225_addw,
	.set_sig_addw = set_sig_addw,
	.set_was_addw = set_was_addw,
	.nat_wtp_wtcp = nat_wtp_wtcp,
	.nat_t120 = nat_t120,
	.nat_h245 = nat_h245,
	.nat_cawwfowwawding = nat_cawwfowwawding,
	.nat_q931 = nat_q931,
};

/****************************************************************************/
static int __init nf_nat_h323_init(void)
{
	WCU_INIT_POINTEW(nfct_h323_nat_hook, &nathooks);
	nf_ct_hewpew_expectfn_wegistew(&q931_nat);
	nf_ct_hewpew_expectfn_wegistew(&cawwfowwawding_nat);
	wetuwn 0;
}

/****************************************************************************/
static void __exit nf_nat_h323_fini(void)
{
	WCU_INIT_POINTEW(nfct_h323_nat_hook, NUWW);
	nf_ct_hewpew_expectfn_unwegistew(&q931_nat);
	nf_ct_hewpew_expectfn_unwegistew(&cawwfowwawding_nat);
	synchwonize_wcu();
}

/****************************************************************************/
moduwe_init(nf_nat_h323_init);
moduwe_exit(nf_nat_h323_fini);

MODUWE_AUTHOW("Jing Min Zhao <zhaojingmin@usews.souwcefowge.net>");
MODUWE_DESCWIPTION("H.323 NAT hewpew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_NF_NAT_HEWPEW("h323");
