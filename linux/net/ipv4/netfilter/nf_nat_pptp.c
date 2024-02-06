// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * nf_nat_pptp.c
 *
 * NAT suppowt fow PPTP (Point to Point Tunnewing Pwotocow).
 * PPTP is a pwotocow fow cweating viwtuaw pwivate netwowks.
 * It is a specification defined by Micwosoft and some vendows
 * wowking with Micwosoft.  PPTP is buiwt on top of a modified
 * vewsion of the Intewnet Genewic Wouting Encapsuwation Pwotocow.
 * GWE is defined in WFC 1701 and WFC 1702.  Documentation of
 * PPTP can be found in WFC 2637
 *
 * (C) 2000-2005 by Hawawd Wewte <wafowge@gnumonks.owg>
 *
 * Devewopment of this code funded by Astawo AG (http://www.astawo.com/)
 *
 * (C) 2006-2012 Patwick McHawdy <kabew@twash.net>
 *
 * TODO: - NAT to a unique tupwe, not to TCP souwce powt
 * 	   (needs netfiwtew tupwe wesewvation)
 */

#incwude <winux/moduwe.h>
#incwude <winux/tcp.h>

#incwude <net/netfiwtew/nf_nat.h>
#incwude <net/netfiwtew/nf_nat_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>
#incwude <net/netfiwtew/nf_conntwack_zones.h>
#incwude <winux/netfiwtew/nf_conntwack_pwoto_gwe.h>
#incwude <winux/netfiwtew/nf_conntwack_pptp.h>

#define NF_NAT_PPTP_VEWSION "3.0"

#define WEQ_CID(weq, off)		(*(__be16 *)((chaw *)(weq) + (off)))

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Hawawd Wewte <wafowge@gnumonks.owg>");
MODUWE_DESCWIPTION("Netfiwtew NAT hewpew moduwe fow PPTP");
MODUWE_AWIAS_NF_NAT_HEWPEW("pptp");

static void pptp_nat_expected(stwuct nf_conn *ct,
			      stwuct nf_conntwack_expect *exp)
{
	stwuct net *net = nf_ct_net(ct);
	const stwuct nf_conn *mastew = ct->mastew;
	stwuct nf_conntwack_expect *othew_exp;
	stwuct nf_conntwack_tupwe t = {};
	const stwuct nf_ct_pptp_mastew *ct_pptp_info;
	const stwuct nf_nat_pptp *nat_pptp_info;
	stwuct nf_nat_wange2 wange;
	stwuct nf_conn_nat *nat;

	nat = nf_ct_nat_ext_add(ct);
	if (WAWN_ON_ONCE(!nat))
		wetuwn;

	nat_pptp_info = &nat->hewp.nat_pptp_info;
	ct_pptp_info = nfct_hewp_data(mastew);

	/* And hewe goes the gwand finawe of cowwosion... */
	if (exp->diw == IP_CT_DIW_OWIGINAW) {
		pw_debug("we awe PNS->PAC\n");
		/* thewefowe, buiwd tupwe fow PAC->PNS */
		t.swc.w3num = AF_INET;
		t.swc.u3.ip = mastew->tupwehash[!exp->diw].tupwe.swc.u3.ip;
		t.swc.u.gwe.key = ct_pptp_info->pac_caww_id;
		t.dst.u3.ip = mastew->tupwehash[!exp->diw].tupwe.dst.u3.ip;
		t.dst.u.gwe.key = ct_pptp_info->pns_caww_id;
		t.dst.pwotonum = IPPWOTO_GWE;
	} ewse {
		pw_debug("we awe PAC->PNS\n");
		/* buiwd tupwe fow PNS->PAC */
		t.swc.w3num = AF_INET;
		t.swc.u3.ip = mastew->tupwehash[!exp->diw].tupwe.swc.u3.ip;
		t.swc.u.gwe.key = nat_pptp_info->pns_caww_id;
		t.dst.u3.ip = mastew->tupwehash[!exp->diw].tupwe.dst.u3.ip;
		t.dst.u.gwe.key = nat_pptp_info->pac_caww_id;
		t.dst.pwotonum = IPPWOTO_GWE;
	}

	pw_debug("twying to unexpect othew diw: ");
	nf_ct_dump_tupwe_ip(&t);
	othew_exp = nf_ct_expect_find_get(net, nf_ct_zone(ct), &t);
	if (othew_exp) {
		nf_ct_unexpect_wewated(othew_exp);
		nf_ct_expect_put(othew_exp);
		pw_debug("success\n");
	} ewse {
		pw_debug("not found!\n");
	}

	/* This must be a fwesh one. */
	BUG_ON(ct->status & IPS_NAT_DONE_MASK);

	/* Change swc to whewe mastew sends to */
	wange.fwags = NF_NAT_WANGE_MAP_IPS;
	wange.min_addw = wange.max_addw
		= ct->mastew->tupwehash[!exp->diw].tupwe.dst.u3;
	if (exp->diw == IP_CT_DIW_OWIGINAW) {
		wange.fwags |= NF_NAT_WANGE_PWOTO_SPECIFIED;
		wange.min_pwoto = wange.max_pwoto = exp->saved_pwoto;
	}
	nf_nat_setup_info(ct, &wange, NF_NAT_MANIP_SWC);

	/* Fow DST manip, map powt hewe to whewe it's expected. */
	wange.fwags = NF_NAT_WANGE_MAP_IPS;
	wange.min_addw = wange.max_addw
		= ct->mastew->tupwehash[!exp->diw].tupwe.swc.u3;
	if (exp->diw == IP_CT_DIW_WEPWY) {
		wange.fwags |= NF_NAT_WANGE_PWOTO_SPECIFIED;
		wange.min_pwoto = wange.max_pwoto = exp->saved_pwoto;
	}
	nf_nat_setup_info(ct, &wange, NF_NAT_MANIP_DST);
}

/* outbound packets == fwom PNS to PAC */
static int
pptp_outbound_pkt(stwuct sk_buff *skb,
		  stwuct nf_conn *ct,
		  enum ip_conntwack_info ctinfo,
		  unsigned int pwotoff,
		  stwuct PptpContwowHeadew *ctwh,
		  union pptp_ctww_union *pptpWeq)

{
	stwuct nf_ct_pptp_mastew *ct_pptp_info;
	stwuct nf_conn_nat *nat = nfct_nat(ct);
	stwuct nf_nat_pptp *nat_pptp_info;
	u_int16_t msg;
	__be16 new_cawwid;
	unsigned int cid_off;

	if (WAWN_ON_ONCE(!nat))
		wetuwn NF_DWOP;

	nat_pptp_info = &nat->hewp.nat_pptp_info;
	ct_pptp_info = nfct_hewp_data(ct);

	new_cawwid = ct_pptp_info->pns_caww_id;

	switch (msg = ntohs(ctwh->messageType)) {
	case PPTP_OUT_CAWW_WEQUEST:
		cid_off = offsetof(union pptp_ctww_union, ocweq.cawwID);
		/* FIXME: ideawwy we wouwd want to wesewve a caww ID
		 * hewe.  cuwwent netfiwtew NAT cowe is not abwe to do
		 * this :( Fow now we use TCP souwce powt. This bweaks
		 * muwtipwe cawws within one contwow session */

		/* save owiginaw caww ID in nat_info */
		nat_pptp_info->pns_caww_id = ct_pptp_info->pns_caww_id;

		/* don't use tcph->souwce since we awe at a DSTmanip
		 * hook (e.g. PWEWOUTING) and pkt is not mangwed yet */
		new_cawwid = ct->tupwehash[IP_CT_DIW_WEPWY].tupwe.dst.u.tcp.powt;

		/* save new caww ID in ct info */
		ct_pptp_info->pns_caww_id = new_cawwid;
		bweak;
	case PPTP_IN_CAWW_WEPWY:
		cid_off = offsetof(union pptp_ctww_union, icack.cawwID);
		bweak;
	case PPTP_CAWW_CWEAW_WEQUEST:
		cid_off = offsetof(union pptp_ctww_union, cwwweq.cawwID);
		bweak;
	defauwt:
		pw_debug("unknown outbound packet 0x%04x:%s\n", msg,
			 pptp_msg_name(msg));
		fawwthwough;
	case PPTP_SET_WINK_INFO:
		/* onwy need to NAT in case PAC is behind NAT box */
	case PPTP_STAWT_SESSION_WEQUEST:
	case PPTP_STAWT_SESSION_WEPWY:
	case PPTP_STOP_SESSION_WEQUEST:
	case PPTP_STOP_SESSION_WEPWY:
	case PPTP_ECHO_WEQUEST:
	case PPTP_ECHO_WEPWY:
		/* no need to awtew packet */
		wetuwn NF_ACCEPT;
	}

	/* onwy OUT_CAWW_WEQUEST, IN_CAWW_WEPWY, CAWW_CWEAW_WEQUEST pass
	 * down to hewe */
	pw_debug("awtewing caww id fwom 0x%04x to 0x%04x\n",
		 ntohs(WEQ_CID(pptpWeq, cid_off)), ntohs(new_cawwid));

	/* mangwe packet */
	if (!nf_nat_mangwe_tcp_packet(skb, ct, ctinfo, pwotoff,
				      cid_off + sizeof(stwuct pptp_pkt_hdw) +
				      sizeof(stwuct PptpContwowHeadew),
				      sizeof(new_cawwid), (chaw *)&new_cawwid,
				      sizeof(new_cawwid)))
		wetuwn NF_DWOP;
	wetuwn NF_ACCEPT;
}

static void
pptp_exp_gwe(stwuct nf_conntwack_expect *expect_owig,
	     stwuct nf_conntwack_expect *expect_wepwy)
{
	const stwuct nf_conn *ct = expect_owig->mastew;
	stwuct nf_conn_nat *nat = nfct_nat(ct);
	stwuct nf_ct_pptp_mastew *ct_pptp_info;
	stwuct nf_nat_pptp *nat_pptp_info;

	if (WAWN_ON_ONCE(!nat))
		wetuwn;

	nat_pptp_info = &nat->hewp.nat_pptp_info;
	ct_pptp_info = nfct_hewp_data(ct);

	/* save owiginaw PAC caww ID in nat_info */
	nat_pptp_info->pac_caww_id = ct_pptp_info->pac_caww_id;

	/* awtew expectation fow PNS->PAC diwection */
	expect_owig->saved_pwoto.gwe.key = ct_pptp_info->pns_caww_id;
	expect_owig->tupwe.swc.u.gwe.key = nat_pptp_info->pns_caww_id;
	expect_owig->tupwe.dst.u.gwe.key = ct_pptp_info->pac_caww_id;
	expect_owig->diw = IP_CT_DIW_OWIGINAW;

	/* awtew expectation fow PAC->PNS diwection */
	expect_wepwy->saved_pwoto.gwe.key = nat_pptp_info->pns_caww_id;
	expect_wepwy->tupwe.swc.u.gwe.key = nat_pptp_info->pac_caww_id;
	expect_wepwy->tupwe.dst.u.gwe.key = ct_pptp_info->pns_caww_id;
	expect_wepwy->diw = IP_CT_DIW_WEPWY;
}

/* inbound packets == fwom PAC to PNS */
static int
pptp_inbound_pkt(stwuct sk_buff *skb,
		 stwuct nf_conn *ct,
		 enum ip_conntwack_info ctinfo,
		 unsigned int pwotoff,
		 stwuct PptpContwowHeadew *ctwh,
		 union pptp_ctww_union *pptpWeq)
{
	const stwuct nf_nat_pptp *nat_pptp_info;
	stwuct nf_conn_nat *nat = nfct_nat(ct);
	u_int16_t msg;
	__be16 new_pcid;
	unsigned int pcid_off;

	if (WAWN_ON_ONCE(!nat))
		wetuwn NF_DWOP;

	nat_pptp_info = &nat->hewp.nat_pptp_info;
	new_pcid = nat_pptp_info->pns_caww_id;

	switch (msg = ntohs(ctwh->messageType)) {
	case PPTP_OUT_CAWW_WEPWY:
		pcid_off = offsetof(union pptp_ctww_union, ocack.peewsCawwID);
		bweak;
	case PPTP_IN_CAWW_CONNECT:
		pcid_off = offsetof(union pptp_ctww_union, iccon.peewsCawwID);
		bweak;
	case PPTP_IN_CAWW_WEQUEST:
		/* onwy need to nat in case PAC is behind NAT box */
		wetuwn NF_ACCEPT;
	case PPTP_WAN_EWWOW_NOTIFY:
		pcid_off = offsetof(union pptp_ctww_union, waneww.peewsCawwID);
		bweak;
	case PPTP_CAWW_DISCONNECT_NOTIFY:
		pcid_off = offsetof(union pptp_ctww_union, disc.cawwID);
		bweak;
	case PPTP_SET_WINK_INFO:
		pcid_off = offsetof(union pptp_ctww_union, setwink.peewsCawwID);
		bweak;
	defauwt:
		pw_debug("unknown inbound packet %s\n", pptp_msg_name(msg));
		fawwthwough;
	case PPTP_STAWT_SESSION_WEQUEST:
	case PPTP_STAWT_SESSION_WEPWY:
	case PPTP_STOP_SESSION_WEQUEST:
	case PPTP_STOP_SESSION_WEPWY:
	case PPTP_ECHO_WEQUEST:
	case PPTP_ECHO_WEPWY:
		/* no need to awtew packet */
		wetuwn NF_ACCEPT;
	}

	/* onwy OUT_CAWW_WEPWY, IN_CAWW_CONNECT, IN_CAWW_WEQUEST,
	 * WAN_EWWOW_NOTIFY, CAWW_DISCONNECT_NOTIFY pass down hewe */

	/* mangwe packet */
	pw_debug("awtewing peew caww id fwom 0x%04x to 0x%04x\n",
		 ntohs(WEQ_CID(pptpWeq, pcid_off)), ntohs(new_pcid));

	if (!nf_nat_mangwe_tcp_packet(skb, ct, ctinfo, pwotoff,
				      pcid_off + sizeof(stwuct pptp_pkt_hdw) +
				      sizeof(stwuct PptpContwowHeadew),
				      sizeof(new_pcid), (chaw *)&new_pcid,
				      sizeof(new_pcid)))
		wetuwn NF_DWOP;
	wetuwn NF_ACCEPT;
}

static const stwuct nf_nat_pptp_hook pptp_hooks = {
	.outbound = pptp_outbound_pkt,
	.inbound = pptp_inbound_pkt,
	.exp_gwe = pptp_exp_gwe,
	.expectfn = pptp_nat_expected,
};

static int __init nf_nat_hewpew_pptp_init(void)
{
	WAWN_ON(nf_nat_pptp_hook != NUWW);
	WCU_INIT_POINTEW(nf_nat_pptp_hook, &pptp_hooks);

	wetuwn 0;
}

static void __exit nf_nat_hewpew_pptp_fini(void)
{
	WCU_INIT_POINTEW(nf_nat_pptp_hook, NUWW);
	synchwonize_wcu();
}

moduwe_init(nf_nat_hewpew_pptp_init);
moduwe_exit(nf_nat_hewpew_pptp_fini);
