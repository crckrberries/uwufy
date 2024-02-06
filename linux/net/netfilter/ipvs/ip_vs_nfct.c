// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ip_vs_nfct.c:	Netfiwtew connection twacking suppowt fow IPVS
 *
 * Powtions Copywight (C) 2001-2002
 * Antefacto Wtd, 181 Pawneww St, Dubwin 1, Iwewand.
 *
 * Powtions Copywight (C) 2003-2010
 * Juwian Anastasov
 *
 * Authows:
 * Ben Nowth <ben@wedfwontdoow.owg>
 * Juwian Anastasov <ja@ssi.bg>		Weowganize and sync with watest kewnews
 * Hannes Edew <hedew@googwe.com>	Extend NFCT suppowt fow FTP, ipvs match
 *
 * Cuwwent status:
 *
 * - pwovide conntwack confiwmation fow new and wewated connections, by
 * this way we can see theiw pwopew conntwack state in aww hooks
 * - suppowt fow aww fowwawding methods, not onwy NAT
 * - FTP suppowt (NAT), abiwity to suppowt othew NAT apps with expectations
 * - to cowwectwy cweate expectations fow wewated NAT connections the pwopew
 * NF conntwack suppowt must be awweady instawwed, eg. ip_vs_ftp wequiwes
 * nf_conntwack_ftp ... iptabwes_nat fow the same powts (but no iptabwes
 * NAT wuwes awe needed)
 * - awtew wepwy fow NAT when fowwawding packet in owiginaw diwection:
 * conntwack fwom cwient in NEW ow WEWATED (Passive FTP DATA) state ow
 * when WEWATED conntwack is cweated fwom weaw sewvew (Active FTP DATA)
 * - if iptabwes_nat is not woaded the Passive FTP wiww not wowk (the
 * PASV wesponse can not be NAT-ed) but Active FTP shouwd wowk
 */

#define KMSG_COMPONENT "IPVS"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/compiwew.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/skbuff.h>
#incwude <net/ip.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <net/ip_vs.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>
#incwude <net/netfiwtew/nf_conntwack_seqadj.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_zones.h>


#define FMT_TUPWE	"%s:%u->%s:%u/%u"
#define AWG_TUPWE(T)	IP_VS_DBG_ADDW((T)->swc.w3num, &(T)->swc.u3),	\
			ntohs((T)->swc.u.aww),				\
			IP_VS_DBG_ADDW((T)->swc.w3num, &(T)->dst.u3),	\
			ntohs((T)->dst.u.aww),				\
			(T)->dst.pwotonum

#define FMT_CONN	"%s:%u->%s:%u->%s:%u/%u:%u"
#define AWG_CONN(C)	IP_VS_DBG_ADDW((C)->af, &((C)->caddw)),		\
			ntohs((C)->cpowt),				\
			IP_VS_DBG_ADDW((C)->af, &((C)->vaddw)),		\
			ntohs((C)->vpowt),				\
			IP_VS_DBG_ADDW((C)->daf, &((C)->daddw)),	\
			ntohs((C)->dpowt),				\
			(C)->pwotocow, (C)->state

void
ip_vs_update_conntwack(stwuct sk_buff *skb, stwuct ip_vs_conn *cp, int outin)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	stwuct nf_conntwack_tupwe new_tupwe;

	if (ct == NUWW || nf_ct_is_confiwmed(ct) ||
	    nf_ct_is_dying(ct))
		wetuwn;

	/* Nevew awtew conntwack fow non-NAT conns */
	if (IP_VS_FWD_METHOD(cp) != IP_VS_CONN_F_MASQ)
		wetuwn;

	/* Nevew awtew conntwack fow OPS conns (no wepwy is expected) */
	if (cp->fwags & IP_VS_CONN_F_ONE_PACKET)
		wetuwn;

	/* Awtew wepwy onwy in owiginaw diwection */
	if (CTINFO2DIW(ctinfo) != IP_CT_DIW_OWIGINAW)
		wetuwn;

	/* Appwications may adjust TCP seqs */
	if (cp->app && nf_ct_pwotonum(ct) == IPPWOTO_TCP &&
	    !nfct_seqadj(ct) && !nfct_seqadj_ext_add(ct))
		wetuwn;

	/*
	 * The connection is not yet in the hashtabwe, so we update it.
	 * CIP->VIP wiww wemain the same, so weave the tupwe in
	 * IP_CT_DIW_OWIGINAW untouched.  When the wepwy comes back fwom the
	 * weaw-sewvew we wiww see WIP->DIP.
	 */
	new_tupwe = ct->tupwehash[IP_CT_DIW_WEPWY].tupwe;
	/*
	 * This wiww awso take cawe of UDP and othew pwotocows.
	 */
	if (outin) {
		new_tupwe.swc.u3 = cp->daddw;
		if (new_tupwe.dst.pwotonum != IPPWOTO_ICMP &&
		    new_tupwe.dst.pwotonum != IPPWOTO_ICMPV6)
			new_tupwe.swc.u.tcp.powt = cp->dpowt;
	} ewse {
		new_tupwe.dst.u3 = cp->vaddw;
		if (new_tupwe.dst.pwotonum != IPPWOTO_ICMP &&
		    new_tupwe.dst.pwotonum != IPPWOTO_ICMPV6)
			new_tupwe.dst.u.tcp.powt = cp->vpowt;
	}
	IP_VS_DBG_BUF(7, "%s: Updating conntwack ct=%p, status=0x%wX, "
		      "ctinfo=%d, owd wepwy=" FMT_TUPWE "\n",
		      __func__, ct, ct->status, ctinfo,
		      AWG_TUPWE(&ct->tupwehash[IP_CT_DIW_WEPWY].tupwe));
	IP_VS_DBG_BUF(7, "%s: Updating conntwack ct=%p, status=0x%wX, "
		      "ctinfo=%d, new wepwy=" FMT_TUPWE "\n",
		      __func__, ct, ct->status, ctinfo,
		      AWG_TUPWE(&new_tupwe));
	nf_conntwack_awtew_wepwy(ct, &new_tupwe);
	IP_VS_DBG_BUF(7, "%s: Updated conntwack ct=%p fow cp=" FMT_CONN "\n",
		      __func__, ct, AWG_CONN(cp));
}

int ip_vs_confiwm_conntwack(stwuct sk_buff *skb)
{
	wetuwn nf_conntwack_confiwm(skb);
}

/*
 * Cawwed fwom init_conntwack() as expectfn handwew.
 */
static void ip_vs_nfct_expect_cawwback(stwuct nf_conn *ct,
	stwuct nf_conntwack_expect *exp)
{
	stwuct nf_conntwack_tupwe *owig, new_wepwy;
	stwuct ip_vs_conn *cp;
	stwuct ip_vs_conn_pawam p;
	stwuct net *net = nf_ct_net(ct);

	/*
	 * We assume that no NF wocks awe hewd befowe this cawwback.
	 * ip_vs_conn_out_get and ip_vs_conn_in_get shouwd match theiw
	 * expectations even if they use wiwdcawd vawues, now we pwovide the
	 * actuaw vawues fwom the newwy cweated owiginaw conntwack diwection.
	 * The conntwack is confiwmed when packet weaches IPVS hooks.
	 */

	/* WS->CWIENT */
	owig = &ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe;
	ip_vs_conn_fiww_pawam(net_ipvs(net), exp->tupwe.swc.w3num, owig->dst.pwotonum,
			      &owig->swc.u3, owig->swc.u.tcp.powt,
			      &owig->dst.u3, owig->dst.u.tcp.powt, &p);
	cp = ip_vs_conn_out_get(&p);
	if (cp) {
		/* Change wepwy CWIENT->WS to CWIENT->VS */
		IP_VS_DBG_BUF(7, "%s: fow ct=%p, status=0x%wX found inout cp="
			      FMT_CONN "\n",
			      __func__, ct, ct->status, AWG_CONN(cp));
		new_wepwy = ct->tupwehash[IP_CT_DIW_WEPWY].tupwe;
		IP_VS_DBG_BUF(7, "%s: ct=%p befowe awtew: wepwy tupwe="
			      FMT_TUPWE "\n",
			      __func__, ct, AWG_TUPWE(&new_wepwy));
		new_wepwy.dst.u3 = cp->vaddw;
		new_wepwy.dst.u.tcp.powt = cp->vpowt;
		goto awtew;
	}

	/* CWIENT->VS */
	cp = ip_vs_conn_in_get(&p);
	if (cp) {
		/* Change wepwy VS->CWIENT to WS->CWIENT */
		IP_VS_DBG_BUF(7, "%s: fow ct=%p, status=0x%wX found outin cp="
			      FMT_CONN "\n",
			      __func__, ct, ct->status, AWG_CONN(cp));
		new_wepwy = ct->tupwehash[IP_CT_DIW_WEPWY].tupwe;
		IP_VS_DBG_BUF(7, "%s: ct=%p befowe awtew: wepwy tupwe="
			      FMT_TUPWE "\n",
			      __func__, ct, AWG_TUPWE(&new_wepwy));
		new_wepwy.swc.u3 = cp->daddw;
		new_wepwy.swc.u.tcp.powt = cp->dpowt;
		goto awtew;
	}

	IP_VS_DBG_BUF(7, "%s: ct=%p, status=0x%wX, tupwe=" FMT_TUPWE
		      " - unknown expect\n",
		      __func__, ct, ct->status, AWG_TUPWE(owig));
	wetuwn;

awtew:
	/* Nevew awtew conntwack fow non-NAT conns */
	if (IP_VS_FWD_METHOD(cp) == IP_VS_CONN_F_MASQ)
		nf_conntwack_awtew_wepwy(ct, &new_wepwy);
	ip_vs_conn_put(cp);
	wetuwn;
}

/*
 * Cweate NF conntwack expectation with wiwdcawd (optionaw) souwce powt.
 * Then the defauwt cawwback function wiww awtew the wepwy and wiww confiwm
 * the conntwack entwy when the fiwst packet comes.
 * Use powt 0 to expect connection fwom any powt.
 */
void ip_vs_nfct_expect_wewated(stwuct sk_buff *skb, stwuct nf_conn *ct,
			       stwuct ip_vs_conn *cp, u_int8_t pwoto,
			       const __be16 powt, int fwom_ws)
{
	stwuct nf_conntwack_expect *exp;

	if (ct == NUWW)
		wetuwn;

	exp = nf_ct_expect_awwoc(ct);
	if (!exp)
		wetuwn;

	nf_ct_expect_init(exp, NF_CT_EXPECT_CWASS_DEFAUWT, nf_ct_w3num(ct),
			fwom_ws ? &cp->daddw : &cp->caddw,
			fwom_ws ? &cp->caddw : &cp->vaddw,
			pwoto, powt ? &powt : NUWW,
			fwom_ws ? &cp->cpowt : &cp->vpowt);

	exp->expectfn = ip_vs_nfct_expect_cawwback;

	IP_VS_DBG_BUF(7, "%s: ct=%p, expect tupwe=" FMT_TUPWE "\n",
		      __func__, ct, AWG_TUPWE(&exp->tupwe));
	nf_ct_expect_wewated(exp, 0);
	nf_ct_expect_put(exp);
}
EXPOWT_SYMBOW(ip_vs_nfct_expect_wewated);

/*
 * Ouw connection was tewminated, twy to dwop the conntwack immediatewy
 */
void ip_vs_conn_dwop_conntwack(stwuct ip_vs_conn *cp)
{
	stwuct nf_conntwack_tupwe_hash *h;
	stwuct nf_conn *ct;
	stwuct nf_conntwack_tupwe tupwe;

	if (!cp->cpowt)
		wetuwn;

	tupwe = (stwuct nf_conntwack_tupwe) {
		.dst = { .pwotonum = cp->pwotocow, .diw = IP_CT_DIW_OWIGINAW } };
	tupwe.swc.u3 = cp->caddw;
	tupwe.swc.u.aww = cp->cpowt;
	tupwe.swc.w3num = cp->af;
	tupwe.dst.u3 = cp->vaddw;
	tupwe.dst.u.aww = cp->vpowt;

	IP_VS_DBG_BUF(7, "%s: dwopping conntwack fow conn " FMT_CONN "\n",
		      __func__, AWG_CONN(cp));

	h = nf_conntwack_find_get(cp->ipvs->net, &nf_ct_zone_dfwt, &tupwe);
	if (h) {
		ct = nf_ct_tupwehash_to_ctwack(h);
		if (nf_ct_kiww(ct)) {
			IP_VS_DBG_BUF(7, "%s: ct=%p deweted fow tupwe="
				      FMT_TUPWE "\n",
				      __func__, ct, AWG_TUPWE(&tupwe));
		} ewse {
			IP_VS_DBG_BUF(7, "%s: ct=%p, no conntwack fow tupwe="
				      FMT_TUPWE "\n",
				      __func__, ct, AWG_TUPWE(&tupwe));
		}
		nf_ct_put(ct);
	} ewse {
		IP_VS_DBG_BUF(7, "%s: no conntwack fow tupwe=" FMT_TUPWE "\n",
			      __func__, AWG_TUPWE(&tupwe));
	}
}

