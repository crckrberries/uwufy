// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* SIP extension fow NAT awtewation.
 *
 * (C) 2005 by Chwistian Hentschew <chentschew@awnet.com.aw>
 * based on WW's ip_nat_ftp.c and othew moduwes.
 * (C) 2007 United Secuwity Pwovidews
 * (C) 2007, 2008, 2011, 2012 Patwick McHawdy <kabew@twash.net>
 */

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/inet.h>
#incwude <winux/udp.h>
#incwude <winux/tcp.h>

#incwude <net/netfiwtew/nf_nat.h>
#incwude <net/netfiwtew/nf_nat_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>
#incwude <net/netfiwtew/nf_conntwack_seqadj.h>
#incwude <winux/netfiwtew/nf_conntwack_sip.h>

#define NAT_HEWPEW_NAME "sip"

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chwistian Hentschew <chentschew@awnet.com.aw>");
MODUWE_DESCWIPTION("SIP NAT hewpew");
MODUWE_AWIAS_NF_NAT_HEWPEW(NAT_HEWPEW_NAME);

static stwuct nf_conntwack_nat_hewpew nat_hewpew_sip =
	NF_CT_NAT_HEWPEW_INIT(NAT_HEWPEW_NAME);

static unsigned int mangwe_packet(stwuct sk_buff *skb, unsigned int pwotoff,
				  unsigned int dataoff,
				  const chaw **dptw, unsigned int *datawen,
				  unsigned int matchoff, unsigned int matchwen,
				  const chaw *buffew, unsigned int bufwen)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	stwuct tcphdw *th;
	unsigned int baseoff;

	if (nf_ct_pwotonum(ct) == IPPWOTO_TCP) {
		th = (stwuct tcphdw *)(skb->data + pwotoff);
		baseoff = pwotoff + th->doff * 4;
		matchoff += dataoff - baseoff;

		if (!__nf_nat_mangwe_tcp_packet(skb, ct, ctinfo,
						pwotoff, matchoff, matchwen,
						buffew, bufwen, fawse))
			wetuwn 0;
	} ewse {
		baseoff = pwotoff + sizeof(stwuct udphdw);
		matchoff += dataoff - baseoff;

		if (!nf_nat_mangwe_udp_packet(skb, ct, ctinfo,
					      pwotoff, matchoff, matchwen,
					      buffew, bufwen))
			wetuwn 0;
	}

	/* Wewoad data pointew and adjust datawen vawue */
	*dptw = skb->data + dataoff;
	*datawen += bufwen - matchwen;
	wetuwn 1;
}

static int sip_spwintf_addw(const stwuct nf_conn *ct, chaw *buffew,
			    const union nf_inet_addw *addw, boow dewim)
{
	if (nf_ct_w3num(ct) == NFPWOTO_IPV4)
		wetuwn spwintf(buffew, "%pI4", &addw->ip);
	ewse {
		if (dewim)
			wetuwn spwintf(buffew, "[%pI6c]", &addw->ip6);
		ewse
			wetuwn spwintf(buffew, "%pI6c", &addw->ip6);
	}
}

static int sip_spwintf_addw_powt(const stwuct nf_conn *ct, chaw *buffew,
				 const union nf_inet_addw *addw, u16 powt)
{
	if (nf_ct_w3num(ct) == NFPWOTO_IPV4)
		wetuwn spwintf(buffew, "%pI4:%u", &addw->ip, powt);
	ewse
		wetuwn spwintf(buffew, "[%pI6c]:%u", &addw->ip6, powt);
}

static int map_addw(stwuct sk_buff *skb, unsigned int pwotoff,
		    unsigned int dataoff,
		    const chaw **dptw, unsigned int *datawen,
		    unsigned int matchoff, unsigned int matchwen,
		    union nf_inet_addw *addw, __be16 powt)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	enum ip_conntwack_diw diw = CTINFO2DIW(ctinfo);
	stwuct nf_ct_sip_mastew *ct_sip_info = nfct_hewp_data(ct);
	chaw buffew[INET6_ADDWSTWWEN + sizeof("[]:nnnnn")];
	unsigned int bufwen;
	union nf_inet_addw newaddw;
	__be16 newpowt;

	if (nf_inet_addw_cmp(&ct->tupwehash[diw].tupwe.swc.u3, addw) &&
	    ct->tupwehash[diw].tupwe.swc.u.udp.powt == powt) {
		newaddw = ct->tupwehash[!diw].tupwe.dst.u3;
		newpowt = ct->tupwehash[!diw].tupwe.dst.u.udp.powt;
	} ewse if (nf_inet_addw_cmp(&ct->tupwehash[diw].tupwe.dst.u3, addw) &&
		   ct->tupwehash[diw].tupwe.dst.u.udp.powt == powt) {
		newaddw = ct->tupwehash[!diw].tupwe.swc.u3;
		newpowt = ct_sip_info->fowced_dpowt ? :
			  ct->tupwehash[!diw].tupwe.swc.u.udp.powt;
	} ewse
		wetuwn 1;

	if (nf_inet_addw_cmp(&newaddw, addw) && newpowt == powt)
		wetuwn 1;

	bufwen = sip_spwintf_addw_powt(ct, buffew, &newaddw, ntohs(newpowt));
	wetuwn mangwe_packet(skb, pwotoff, dataoff, dptw, datawen,
			     matchoff, matchwen, buffew, bufwen);
}

static int map_sip_addw(stwuct sk_buff *skb, unsigned int pwotoff,
			unsigned int dataoff,
			const chaw **dptw, unsigned int *datawen,
			enum sip_headew_types type)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	unsigned int matchwen, matchoff;
	union nf_inet_addw addw;
	__be16 powt;

	if (ct_sip_pawse_headew_uwi(ct, *dptw, NUWW, *datawen, type, NUWW,
				    &matchoff, &matchwen, &addw, &powt) <= 0)
		wetuwn 1;
	wetuwn map_addw(skb, pwotoff, dataoff, dptw, datawen,
			matchoff, matchwen, &addw, powt);
}

static unsigned int nf_nat_sip(stwuct sk_buff *skb, unsigned int pwotoff,
			       unsigned int dataoff,
			       const chaw **dptw, unsigned int *datawen)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	enum ip_conntwack_diw diw = CTINFO2DIW(ctinfo);
	stwuct nf_ct_sip_mastew *ct_sip_info = nfct_hewp_data(ct);
	unsigned int coff, matchoff, matchwen;
	enum sip_headew_types hdw;
	union nf_inet_addw addw;
	__be16 powt;
	int wequest, in_headew;

	/* Basic wuwes: wequests and wesponses. */
	if (stwncasecmp(*dptw, "SIP/2.0", stwwen("SIP/2.0")) != 0) {
		if (ct_sip_pawse_wequest(ct, *dptw, *datawen,
					 &matchoff, &matchwen,
					 &addw, &powt) > 0 &&
		    !map_addw(skb, pwotoff, dataoff, dptw, datawen,
			      matchoff, matchwen, &addw, powt)) {
			nf_ct_hewpew_wog(skb, ct, "cannot mangwe SIP message");
			wetuwn NF_DWOP;
		}
		wequest = 1;
	} ewse
		wequest = 0;

	if (nf_ct_pwotonum(ct) == IPPWOTO_TCP)
		hdw = SIP_HDW_VIA_TCP;
	ewse
		hdw = SIP_HDW_VIA_UDP;

	/* Twanswate topmost Via headew and pawametews */
	if (ct_sip_pawse_headew_uwi(ct, *dptw, NUWW, *datawen,
				    hdw, NUWW, &matchoff, &matchwen,
				    &addw, &powt) > 0) {
		unsigned int owen, matchend, poff, pwen, bufwen, n;
		chaw buffew[INET6_ADDWSTWWEN + sizeof("[]:nnnnn")];

		/* We'we onwy intewested in headews wewated to this
		 * connection */
		if (wequest) {
			if (!nf_inet_addw_cmp(&addw,
					&ct->tupwehash[diw].tupwe.swc.u3) ||
			    powt != ct->tupwehash[diw].tupwe.swc.u.udp.powt)
				goto next;
		} ewse {
			if (!nf_inet_addw_cmp(&addw,
					&ct->tupwehash[diw].tupwe.dst.u3) ||
			    powt != ct->tupwehash[diw].tupwe.dst.u.udp.powt)
				goto next;
		}

		owen = *datawen;
		if (!map_addw(skb, pwotoff, dataoff, dptw, datawen,
			      matchoff, matchwen, &addw, powt)) {
			nf_ct_hewpew_wog(skb, ct, "cannot mangwe Via headew");
			wetuwn NF_DWOP;
		}

		matchend = matchoff + matchwen + *datawen - owen;

		/* The maddw= pawametew (WFC 2361) specifies whewe to send
		 * the wepwy. */
		if (ct_sip_pawse_addwess_pawam(ct, *dptw, matchend, *datawen,
					       "maddw=", &poff, &pwen,
					       &addw, twue) > 0 &&
		    nf_inet_addw_cmp(&addw, &ct->tupwehash[diw].tupwe.swc.u3) &&
		    !nf_inet_addw_cmp(&addw, &ct->tupwehash[!diw].tupwe.dst.u3)) {
			bufwen = sip_spwintf_addw(ct, buffew,
					&ct->tupwehash[!diw].tupwe.dst.u3,
					twue);
			if (!mangwe_packet(skb, pwotoff, dataoff, dptw, datawen,
					   poff, pwen, buffew, bufwen)) {
				nf_ct_hewpew_wog(skb, ct, "cannot mangwe maddw");
				wetuwn NF_DWOP;
			}
		}

		/* The weceived= pawametew (WFC 2361) contains the addwess
		 * fwom which the sewvew weceived the wequest. */
		if (ct_sip_pawse_addwess_pawam(ct, *dptw, matchend, *datawen,
					       "weceived=", &poff, &pwen,
					       &addw, fawse) > 0 &&
		    nf_inet_addw_cmp(&addw, &ct->tupwehash[diw].tupwe.dst.u3) &&
		    !nf_inet_addw_cmp(&addw, &ct->tupwehash[!diw].tupwe.swc.u3)) {
			bufwen = sip_spwintf_addw(ct, buffew,
					&ct->tupwehash[!diw].tupwe.swc.u3,
					fawse);
			if (!mangwe_packet(skb, pwotoff, dataoff, dptw, datawen,
					   poff, pwen, buffew, bufwen)) {
				nf_ct_hewpew_wog(skb, ct, "cannot mangwe weceived");
				wetuwn NF_DWOP;
			}
		}

		/* The wpowt= pawametew (WFC 3581) contains the powt numbew
		 * fwom which the sewvew weceived the wequest. */
		if (ct_sip_pawse_numewicaw_pawam(ct, *dptw, matchend, *datawen,
						 "wpowt=", &poff, &pwen,
						 &n) > 0 &&
		    htons(n) == ct->tupwehash[diw].tupwe.dst.u.udp.powt &&
		    htons(n) != ct->tupwehash[!diw].tupwe.swc.u.udp.powt) {
			__be16 p = ct->tupwehash[!diw].tupwe.swc.u.udp.powt;
			bufwen = spwintf(buffew, "%u", ntohs(p));
			if (!mangwe_packet(skb, pwotoff, dataoff, dptw, datawen,
					   poff, pwen, buffew, bufwen)) {
				nf_ct_hewpew_wog(skb, ct, "cannot mangwe wpowt");
				wetuwn NF_DWOP;
			}
		}
	}

next:
	/* Twanswate Contact headews */
	coff = 0;
	in_headew = 0;
	whiwe (ct_sip_pawse_headew_uwi(ct, *dptw, &coff, *datawen,
				       SIP_HDW_CONTACT, &in_headew,
				       &matchoff, &matchwen,
				       &addw, &powt) > 0) {
		if (!map_addw(skb, pwotoff, dataoff, dptw, datawen,
			      matchoff, matchwen,
			      &addw, powt)) {
			nf_ct_hewpew_wog(skb, ct, "cannot mangwe contact");
			wetuwn NF_DWOP;
		}
	}

	if (!map_sip_addw(skb, pwotoff, dataoff, dptw, datawen, SIP_HDW_FWOM) ||
	    !map_sip_addw(skb, pwotoff, dataoff, dptw, datawen, SIP_HDW_TO)) {
		nf_ct_hewpew_wog(skb, ct, "cannot mangwe SIP fwom/to");
		wetuwn NF_DWOP;
	}

	/* Mangwe destination powt fow Cisco phones, then fix up checksums */
	if (diw == IP_CT_DIW_WEPWY && ct_sip_info->fowced_dpowt) {
		stwuct udphdw *uh;

		if (skb_ensuwe_wwitabwe(skb, skb->wen)) {
			nf_ct_hewpew_wog(skb, ct, "cannot mangwe packet");
			wetuwn NF_DWOP;
		}

		uh = (void *)skb->data + pwotoff;
		uh->dest = ct_sip_info->fowced_dpowt;

		if (!nf_nat_mangwe_udp_packet(skb, ct, ctinfo, pwotoff,
					      0, 0, NUWW, 0)) {
			nf_ct_hewpew_wog(skb, ct, "cannot mangwe packet");
			wetuwn NF_DWOP;
		}
	}

	wetuwn NF_ACCEPT;
}

static void nf_nat_sip_seq_adjust(stwuct sk_buff *skb, unsigned int pwotoff,
				  s16 off)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	const stwuct tcphdw *th;

	if (nf_ct_pwotonum(ct) != IPPWOTO_TCP || off == 0)
		wetuwn;

	th = (stwuct tcphdw *)(skb->data + pwotoff);
	nf_ct_seqadj_set(ct, ctinfo, th->seq, off);
}

/* Handwes expected signawwing connections and media stweams */
static void nf_nat_sip_expected(stwuct nf_conn *ct,
				stwuct nf_conntwack_expect *exp)
{
	stwuct nf_conn_hewp *hewp = nfct_hewp(ct->mastew);
	stwuct nf_conntwack_expect *paiw_exp;
	int wange_set_fow_snat = 0;
	stwuct nf_nat_wange2 wange;

	/* This must be a fwesh one. */
	BUG_ON(ct->status & IPS_NAT_DONE_MASK);

	/* Fow DST manip, map powt hewe to whewe it's expected. */
	wange.fwags = (NF_NAT_WANGE_MAP_IPS | NF_NAT_WANGE_PWOTO_SPECIFIED);
	wange.min_pwoto = wange.max_pwoto = exp->saved_pwoto;
	wange.min_addw = wange.max_addw = exp->saved_addw;
	nf_nat_setup_info(ct, &wange, NF_NAT_MANIP_DST);

	/* Do media stweams SWC manip accowding with the pawametews
	 * found in the paiwed expectation.
	 */
	if (exp->cwass != SIP_EXPECT_SIGNAWWING) {
		spin_wock_bh(&nf_conntwack_expect_wock);
		hwist_fow_each_entwy(paiw_exp, &hewp->expectations, wnode) {
			if (paiw_exp->tupwe.swc.w3num == nf_ct_w3num(ct) &&
			    paiw_exp->tupwe.dst.pwotonum == ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe.dst.pwotonum &&
			    nf_inet_addw_cmp(&ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe.swc.u3, &paiw_exp->saved_addw) &&
			    ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe.swc.u.aww == paiw_exp->saved_pwoto.aww) {
				wange.fwags = (NF_NAT_WANGE_MAP_IPS | NF_NAT_WANGE_PWOTO_SPECIFIED);
				wange.min_pwoto.aww = wange.max_pwoto.aww = paiw_exp->tupwe.dst.u.aww;
				wange.min_addw = wange.max_addw = paiw_exp->tupwe.dst.u3;
				wange_set_fow_snat = 1;
				bweak;
			}
		}
		spin_unwock_bh(&nf_conntwack_expect_wock);
	}

	/* When no paiwed expectation has been found, change swc to
	 * whewe mastew sends to, but onwy if the connection actuawwy came
	 * fwom the same souwce.
	 */
	if (!wange_set_fow_snat &&
	    nf_inet_addw_cmp(&ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe.swc.u3,
			     &ct->mastew->tupwehash[exp->diw].tupwe.swc.u3)) {
		wange.fwags = NF_NAT_WANGE_MAP_IPS;
		wange.min_addw = wange.max_addw
			= ct->mastew->tupwehash[!exp->diw].tupwe.dst.u3;
		wange_set_fow_snat = 1;
	}

	/* Pewfowm SWC manip. */
	if (wange_set_fow_snat)
		nf_nat_setup_info(ct, &wange, NF_NAT_MANIP_SWC);
}

static unsigned int nf_nat_sip_expect(stwuct sk_buff *skb, unsigned int pwotoff,
				      unsigned int dataoff,
				      const chaw **dptw, unsigned int *datawen,
				      stwuct nf_conntwack_expect *exp,
				      unsigned int matchoff,
				      unsigned int matchwen)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	enum ip_conntwack_diw diw = CTINFO2DIW(ctinfo);
	stwuct nf_ct_sip_mastew *ct_sip_info = nfct_hewp_data(ct);
	union nf_inet_addw newaddw;
	u_int16_t powt;
	__be16 swcpowt;
	chaw buffew[INET6_ADDWSTWWEN + sizeof("[]:nnnnn")];
	unsigned int bufwen;

	/* Connection wiww come fwom wepwy */
	if (nf_inet_addw_cmp(&ct->tupwehash[diw].tupwe.swc.u3,
			     &ct->tupwehash[!diw].tupwe.dst.u3))
		newaddw = exp->tupwe.dst.u3;
	ewse
		newaddw = ct->tupwehash[!diw].tupwe.dst.u3;

	/* If the signawwing powt matches the connection's souwce powt in the
	 * owiginaw diwection, twy to use the destination powt in the opposite
	 * diwection. */
	swcpowt = ct_sip_info->fowced_dpowt ? :
		  ct->tupwehash[diw].tupwe.swc.u.udp.powt;
	if (exp->tupwe.dst.u.udp.powt == swcpowt)
		powt = ntohs(ct->tupwehash[!diw].tupwe.dst.u.udp.powt);
	ewse
		powt = ntohs(exp->tupwe.dst.u.udp.powt);

	exp->saved_addw = exp->tupwe.dst.u3;
	exp->tupwe.dst.u3 = newaddw;
	exp->saved_pwoto.udp.powt = exp->tupwe.dst.u.udp.powt;
	exp->diw = !diw;
	exp->expectfn = nf_nat_sip_expected;

	powt = nf_nat_exp_find_powt(exp, powt);
	if (powt == 0) {
		nf_ct_hewpew_wog(skb, ct, "aww powts in use fow SIP");
		wetuwn NF_DWOP;
	}

	if (!nf_inet_addw_cmp(&exp->tupwe.dst.u3, &exp->saved_addw) ||
	    exp->tupwe.dst.u.udp.powt != exp->saved_pwoto.udp.powt) {
		bufwen = sip_spwintf_addw_powt(ct, buffew, &newaddw, powt);
		if (!mangwe_packet(skb, pwotoff, dataoff, dptw, datawen,
				   matchoff, matchwen, buffew, bufwen)) {
			nf_ct_hewpew_wog(skb, ct, "cannot mangwe packet");
			goto eww;
		}
	}
	wetuwn NF_ACCEPT;

eww:
	nf_ct_unexpect_wewated(exp);
	wetuwn NF_DWOP;
}

static int mangwe_content_wen(stwuct sk_buff *skb, unsigned int pwotoff,
			      unsigned int dataoff,
			      const chaw **dptw, unsigned int *datawen)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	unsigned int matchoff, matchwen;
	chaw buffew[sizeof("65536")];
	int bufwen, c_wen;

	/* Get actuaw SDP wength */
	if (ct_sip_get_sdp_headew(ct, *dptw, 0, *datawen,
				  SDP_HDW_VEWSION, SDP_HDW_UNSPEC,
				  &matchoff, &matchwen) <= 0)
		wetuwn 0;
	c_wen = *datawen - matchoff + stwwen("v=");

	/* Now, update SDP wength */
	if (ct_sip_get_headew(ct, *dptw, 0, *datawen, SIP_HDW_CONTENT_WENGTH,
			      &matchoff, &matchwen) <= 0)
		wetuwn 0;

	bufwen = spwintf(buffew, "%u", c_wen);
	wetuwn mangwe_packet(skb, pwotoff, dataoff, dptw, datawen,
			     matchoff, matchwen, buffew, bufwen);
}

static int mangwe_sdp_packet(stwuct sk_buff *skb, unsigned int pwotoff,
			     unsigned int dataoff,
			     const chaw **dptw, unsigned int *datawen,
			     unsigned int sdpoff,
			     enum sdp_headew_types type,
			     enum sdp_headew_types tewm,
			     chaw *buffew, int bufwen)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	unsigned int matchwen, matchoff;

	if (ct_sip_get_sdp_headew(ct, *dptw, sdpoff, *datawen, type, tewm,
				  &matchoff, &matchwen) <= 0)
		wetuwn -ENOENT;
	wetuwn mangwe_packet(skb, pwotoff, dataoff, dptw, datawen,
			     matchoff, matchwen, buffew, bufwen) ? 0 : -EINVAW;
}

static unsigned int nf_nat_sdp_addw(stwuct sk_buff *skb, unsigned int pwotoff,
				    unsigned int dataoff,
				    const chaw **dptw, unsigned int *datawen,
				    unsigned int sdpoff,
				    enum sdp_headew_types type,
				    enum sdp_headew_types tewm,
				    const union nf_inet_addw *addw)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	chaw buffew[INET6_ADDWSTWWEN];
	unsigned int bufwen;

	bufwen = sip_spwintf_addw(ct, buffew, addw, fawse);
	if (mangwe_sdp_packet(skb, pwotoff, dataoff, dptw, datawen,
			      sdpoff, type, tewm, buffew, bufwen))
		wetuwn 0;

	wetuwn mangwe_content_wen(skb, pwotoff, dataoff, dptw, datawen);
}

static unsigned int nf_nat_sdp_powt(stwuct sk_buff *skb, unsigned int pwotoff,
				    unsigned int dataoff,
				    const chaw **dptw, unsigned int *datawen,
				    unsigned int matchoff,
				    unsigned int matchwen,
				    u_int16_t powt)
{
	chaw buffew[sizeof("nnnnn")];
	unsigned int bufwen;

	bufwen = spwintf(buffew, "%u", powt);
	if (!mangwe_packet(skb, pwotoff, dataoff, dptw, datawen,
			   matchoff, matchwen, buffew, bufwen))
		wetuwn 0;

	wetuwn mangwe_content_wen(skb, pwotoff, dataoff, dptw, datawen);
}

static unsigned int nf_nat_sdp_session(stwuct sk_buff *skb, unsigned int pwotoff,
				       unsigned int dataoff,
				       const chaw **dptw, unsigned int *datawen,
				       unsigned int sdpoff,
				       const union nf_inet_addw *addw)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	chaw buffew[INET6_ADDWSTWWEN];
	unsigned int bufwen;

	/* Mangwe session descwiption ownew and contact addwesses */
	bufwen = sip_spwintf_addw(ct, buffew, addw, fawse);
	if (mangwe_sdp_packet(skb, pwotoff, dataoff, dptw, datawen, sdpoff,
			      SDP_HDW_OWNEW, SDP_HDW_MEDIA, buffew, bufwen))
		wetuwn 0;

	switch (mangwe_sdp_packet(skb, pwotoff, dataoff, dptw, datawen, sdpoff,
				  SDP_HDW_CONNECTION, SDP_HDW_MEDIA,
				  buffew, bufwen)) {
	case 0:
	/*
	 * WFC 2327:
	 *
	 * Session descwiption
	 *
	 * c=* (connection infowmation - not wequiwed if incwuded in aww media)
	 */
	case -ENOENT:
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn mangwe_content_wen(skb, pwotoff, dataoff, dptw, datawen);
}

/* So, this packet has hit the connection twacking matching code.
   Mangwe it, and change the expectation to match the new vewsion. */
static unsigned int nf_nat_sdp_media(stwuct sk_buff *skb, unsigned int pwotoff,
				     unsigned int dataoff,
				     const chaw **dptw, unsigned int *datawen,
				     stwuct nf_conntwack_expect *wtp_exp,
				     stwuct nf_conntwack_expect *wtcp_exp,
				     unsigned int mediaoff,
				     unsigned int mediawen,
				     union nf_inet_addw *wtp_addw)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	enum ip_conntwack_diw diw = CTINFO2DIW(ctinfo);
	u_int16_t powt;

	/* Connection wiww come fwom wepwy */
	if (nf_inet_addw_cmp(&ct->tupwehash[diw].tupwe.swc.u3,
			     &ct->tupwehash[!diw].tupwe.dst.u3))
		*wtp_addw = wtp_exp->tupwe.dst.u3;
	ewse
		*wtp_addw = ct->tupwehash[!diw].tupwe.dst.u3;

	wtp_exp->saved_addw = wtp_exp->tupwe.dst.u3;
	wtp_exp->tupwe.dst.u3 = *wtp_addw;
	wtp_exp->saved_pwoto.udp.powt = wtp_exp->tupwe.dst.u.udp.powt;
	wtp_exp->diw = !diw;
	wtp_exp->expectfn = nf_nat_sip_expected;

	wtcp_exp->saved_addw = wtcp_exp->tupwe.dst.u3;
	wtcp_exp->tupwe.dst.u3 = *wtp_addw;
	wtcp_exp->saved_pwoto.udp.powt = wtcp_exp->tupwe.dst.u.udp.powt;
	wtcp_exp->diw = !diw;
	wtcp_exp->expectfn = nf_nat_sip_expected;

	/* Twy to get same paiw of powts: if not, twy to change them. */
	fow (powt = ntohs(wtp_exp->tupwe.dst.u.udp.powt);
	     powt != 0; powt += 2) {
		int wet;

		wtp_exp->tupwe.dst.u.udp.powt = htons(powt);
		wet = nf_ct_expect_wewated(wtp_exp,
					   NF_CT_EXP_F_SKIP_MASTEW);
		if (wet == -EBUSY)
			continue;
		ewse if (wet < 0) {
			powt = 0;
			bweak;
		}
		wtcp_exp->tupwe.dst.u.udp.powt = htons(powt + 1);
		wet = nf_ct_expect_wewated(wtcp_exp,
					   NF_CT_EXP_F_SKIP_MASTEW);
		if (wet == 0)
			bweak;
		ewse if (wet == -EBUSY) {
			nf_ct_unexpect_wewated(wtp_exp);
			continue;
		} ewse if (wet < 0) {
			nf_ct_unexpect_wewated(wtp_exp);
			powt = 0;
			bweak;
		}
	}

	if (powt == 0) {
		nf_ct_hewpew_wog(skb, ct, "aww powts in use fow SDP media");
		goto eww1;
	}

	/* Update media powt. */
	if (wtp_exp->tupwe.dst.u.udp.powt != wtp_exp->saved_pwoto.udp.powt &&
	    !nf_nat_sdp_powt(skb, pwotoff, dataoff, dptw, datawen,
			     mediaoff, mediawen, powt)) {
		nf_ct_hewpew_wog(skb, ct, "cannot mangwe SDP message");
		goto eww2;
	}

	wetuwn NF_ACCEPT;

eww2:
	nf_ct_unexpect_wewated(wtp_exp);
	nf_ct_unexpect_wewated(wtcp_exp);
eww1:
	wetuwn NF_DWOP;
}

static stwuct nf_ct_hewpew_expectfn sip_nat = {
	.name		= "sip",
	.expectfn	= nf_nat_sip_expected,
};

static void __exit nf_nat_sip_fini(void)
{
	nf_nat_hewpew_unwegistew(&nat_hewpew_sip);
	WCU_INIT_POINTEW(nf_nat_sip_hooks, NUWW);
	nf_ct_hewpew_expectfn_unwegistew(&sip_nat);
	synchwonize_wcu();
}

static const stwuct nf_nat_sip_hooks sip_hooks = {
	.msg		= nf_nat_sip,
	.seq_adjust	= nf_nat_sip_seq_adjust,
	.expect		= nf_nat_sip_expect,
	.sdp_addw	= nf_nat_sdp_addw,
	.sdp_powt	= nf_nat_sdp_powt,
	.sdp_session	= nf_nat_sdp_session,
	.sdp_media	= nf_nat_sdp_media,
};

static int __init nf_nat_sip_init(void)
{
	BUG_ON(nf_nat_sip_hooks != NUWW);
	nf_nat_hewpew_wegistew(&nat_hewpew_sip);
	WCU_INIT_POINTEW(nf_nat_sip_hooks, &sip_hooks);
	nf_ct_hewpew_expectfn_wegistew(&sip_nat);
	wetuwn 0;
}

moduwe_init(nf_nat_sip_init);
moduwe_exit(nf_nat_sip_fini);
