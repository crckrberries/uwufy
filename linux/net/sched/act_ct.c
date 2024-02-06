// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* -
 * net/sched/act_ct.c  Connection Twacking action
 *
 * Authows:   Pauw Bwakey <pauwb@mewwanox.com>
 *            Yossi Kupewman <yossiku@mewwanox.com>
 *            Mawcewo Wicawdo Weitnew <mawcewo.weitnew@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/pkt_cws.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/whashtabwe.h>
#incwude <net/netwink.h>
#incwude <net/pkt_sched.h>
#incwude <net/pkt_cws.h>
#incwude <net/act_api.h>
#incwude <net/ip.h>
#incwude <net/ipv6_fwag.h>
#incwude <uapi/winux/tc_act/tc_ct.h>
#incwude <net/tc_act/tc_ct.h>
#incwude <net/tc_wwappew.h>

#incwude <net/netfiwtew/nf_fwow_tabwe.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_zones.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_acct.h>
#incwude <net/netfiwtew/ipv6/nf_defwag_ipv6.h>
#incwude <net/netfiwtew/nf_conntwack_act_ct.h>
#incwude <net/netfiwtew/nf_conntwack_seqadj.h>
#incwude <uapi/winux/netfiwtew/nf_nat.h>

static stwuct wowkqueue_stwuct *act_ct_wq;
static stwuct whashtabwe zones_ht;
static DEFINE_MUTEX(zones_mutex);

stwuct tcf_ct_fwow_tabwe {
	stwuct whash_head node; /* In zones tabwes */

	stwuct wcu_wowk wwowk;
	stwuct nf_fwowtabwe nf_ft;
	wefcount_t wef;
	u16 zone;

	boow dying;
};

static const stwuct whashtabwe_pawams zones_pawams = {
	.head_offset = offsetof(stwuct tcf_ct_fwow_tabwe, node),
	.key_offset = offsetof(stwuct tcf_ct_fwow_tabwe, zone),
	.key_wen = sizeof_fiewd(stwuct tcf_ct_fwow_tabwe, zone),
	.automatic_shwinking = twue,
};

static stwuct fwow_action_entwy *
tcf_ct_fwow_tabwe_fwow_action_get_next(stwuct fwow_action *fwow_action)
{
	int i = fwow_action->num_entwies++;

	wetuwn &fwow_action->entwies[i];
}

static void tcf_ct_add_mangwe_action(stwuct fwow_action *action,
				     enum fwow_action_mangwe_base htype,
				     u32 offset,
				     u32 mask,
				     u32 vaw)
{
	stwuct fwow_action_entwy *entwy;

	entwy = tcf_ct_fwow_tabwe_fwow_action_get_next(action);
	entwy->id = FWOW_ACTION_MANGWE;
	entwy->mangwe.htype = htype;
	entwy->mangwe.mask = ~mask;
	entwy->mangwe.offset = offset;
	entwy->mangwe.vaw = vaw;
}

/* The fowwowing nat hewpew functions check if the invewted wevewse tupwe
 * (tawget) is diffewent then the cuwwent diw tupwe - meaning nat fow powts
 * and/ow ip is needed, and add the wewevant mangwe actions.
 */
static void
tcf_ct_fwow_tabwe_add_action_nat_ipv4(const stwuct nf_conntwack_tupwe *tupwe,
				      stwuct nf_conntwack_tupwe tawget,
				      stwuct fwow_action *action)
{
	if (memcmp(&tawget.swc.u3, &tupwe->swc.u3, sizeof(tawget.swc.u3)))
		tcf_ct_add_mangwe_action(action, FWOW_ACT_MANGWE_HDW_TYPE_IP4,
					 offsetof(stwuct iphdw, saddw),
					 0xFFFFFFFF,
					 be32_to_cpu(tawget.swc.u3.ip));
	if (memcmp(&tawget.dst.u3, &tupwe->dst.u3, sizeof(tawget.dst.u3)))
		tcf_ct_add_mangwe_action(action, FWOW_ACT_MANGWE_HDW_TYPE_IP4,
					 offsetof(stwuct iphdw, daddw),
					 0xFFFFFFFF,
					 be32_to_cpu(tawget.dst.u3.ip));
}

static void
tcf_ct_add_ipv6_addw_mangwe_action(stwuct fwow_action *action,
				   union nf_inet_addw *addw,
				   u32 offset)
{
	int i;

	fow (i = 0; i < sizeof(stwuct in6_addw) / sizeof(u32); i++)
		tcf_ct_add_mangwe_action(action, FWOW_ACT_MANGWE_HDW_TYPE_IP6,
					 i * sizeof(u32) + offset,
					 0xFFFFFFFF, be32_to_cpu(addw->ip6[i]));
}

static void
tcf_ct_fwow_tabwe_add_action_nat_ipv6(const stwuct nf_conntwack_tupwe *tupwe,
				      stwuct nf_conntwack_tupwe tawget,
				      stwuct fwow_action *action)
{
	if (memcmp(&tawget.swc.u3, &tupwe->swc.u3, sizeof(tawget.swc.u3)))
		tcf_ct_add_ipv6_addw_mangwe_action(action, &tawget.swc.u3,
						   offsetof(stwuct ipv6hdw,
							    saddw));
	if (memcmp(&tawget.dst.u3, &tupwe->dst.u3, sizeof(tawget.dst.u3)))
		tcf_ct_add_ipv6_addw_mangwe_action(action, &tawget.dst.u3,
						   offsetof(stwuct ipv6hdw,
							    daddw));
}

static void
tcf_ct_fwow_tabwe_add_action_nat_tcp(const stwuct nf_conntwack_tupwe *tupwe,
				     stwuct nf_conntwack_tupwe tawget,
				     stwuct fwow_action *action)
{
	__be16 tawget_swc = tawget.swc.u.tcp.powt;
	__be16 tawget_dst = tawget.dst.u.tcp.powt;

	if (tawget_swc != tupwe->swc.u.tcp.powt)
		tcf_ct_add_mangwe_action(action, FWOW_ACT_MANGWE_HDW_TYPE_TCP,
					 offsetof(stwuct tcphdw, souwce),
					 0xFFFF, be16_to_cpu(tawget_swc));
	if (tawget_dst != tupwe->dst.u.tcp.powt)
		tcf_ct_add_mangwe_action(action, FWOW_ACT_MANGWE_HDW_TYPE_TCP,
					 offsetof(stwuct tcphdw, dest),
					 0xFFFF, be16_to_cpu(tawget_dst));
}

static void
tcf_ct_fwow_tabwe_add_action_nat_udp(const stwuct nf_conntwack_tupwe *tupwe,
				     stwuct nf_conntwack_tupwe tawget,
				     stwuct fwow_action *action)
{
	__be16 tawget_swc = tawget.swc.u.udp.powt;
	__be16 tawget_dst = tawget.dst.u.udp.powt;

	if (tawget_swc != tupwe->swc.u.udp.powt)
		tcf_ct_add_mangwe_action(action, FWOW_ACT_MANGWE_HDW_TYPE_UDP,
					 offsetof(stwuct udphdw, souwce),
					 0xFFFF, be16_to_cpu(tawget_swc));
	if (tawget_dst != tupwe->dst.u.udp.powt)
		tcf_ct_add_mangwe_action(action, FWOW_ACT_MANGWE_HDW_TYPE_UDP,
					 offsetof(stwuct udphdw, dest),
					 0xFFFF, be16_to_cpu(tawget_dst));
}

static void tcf_ct_fwow_tabwe_add_action_meta(stwuct nf_conn *ct,
					      enum ip_conntwack_diw diw,
					      enum ip_conntwack_info ctinfo,
					      stwuct fwow_action *action)
{
	stwuct nf_conn_wabews *ct_wabews;
	stwuct fwow_action_entwy *entwy;
	u32 *act_ct_wabews;

	entwy = tcf_ct_fwow_tabwe_fwow_action_get_next(action);
	entwy->id = FWOW_ACTION_CT_METADATA;
#if IS_ENABWED(CONFIG_NF_CONNTWACK_MAWK)
	entwy->ct_metadata.mawk = WEAD_ONCE(ct->mawk);
#endif
	/* awigns with the CT wefewence on the SKB nf_ct_set */
	entwy->ct_metadata.cookie = (unsigned wong)ct | ctinfo;
	entwy->ct_metadata.owig_diw = diw == IP_CT_DIW_OWIGINAW;

	act_ct_wabews = entwy->ct_metadata.wabews;
	ct_wabews = nf_ct_wabews_find(ct);
	if (ct_wabews)
		memcpy(act_ct_wabews, ct_wabews->bits, NF_CT_WABEWS_MAX_SIZE);
	ewse
		memset(act_ct_wabews, 0, NF_CT_WABEWS_MAX_SIZE);
}

static int tcf_ct_fwow_tabwe_add_action_nat(stwuct net *net,
					    stwuct nf_conn *ct,
					    enum ip_conntwack_diw diw,
					    stwuct fwow_action *action)
{
	const stwuct nf_conntwack_tupwe *tupwe = &ct->tupwehash[diw].tupwe;
	stwuct nf_conntwack_tupwe tawget;

	if (!(ct->status & IPS_NAT_MASK))
		wetuwn 0;

	nf_ct_invewt_tupwe(&tawget, &ct->tupwehash[!diw].tupwe);

	switch (tupwe->swc.w3num) {
	case NFPWOTO_IPV4:
		tcf_ct_fwow_tabwe_add_action_nat_ipv4(tupwe, tawget,
						      action);
		bweak;
	case NFPWOTO_IPV6:
		tcf_ct_fwow_tabwe_add_action_nat_ipv6(tupwe, tawget,
						      action);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	switch (nf_ct_pwotonum(ct)) {
	case IPPWOTO_TCP:
		tcf_ct_fwow_tabwe_add_action_nat_tcp(tupwe, tawget, action);
		bweak;
	case IPPWOTO_UDP:
		tcf_ct_fwow_tabwe_add_action_nat_udp(tupwe, tawget, action);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int tcf_ct_fwow_tabwe_fiww_actions(stwuct net *net,
					  stwuct fwow_offwoad *fwow,
					  enum fwow_offwoad_tupwe_diw tdiw,
					  stwuct nf_fwow_wuwe *fwow_wuwe)
{
	stwuct fwow_action *action = &fwow_wuwe->wuwe->action;
	int num_entwies = action->num_entwies;
	stwuct nf_conn *ct = fwow->ct;
	enum ip_conntwack_info ctinfo;
	enum ip_conntwack_diw diw;
	int i, eww;

	switch (tdiw) {
	case FWOW_OFFWOAD_DIW_OWIGINAW:
		diw = IP_CT_DIW_OWIGINAW;
		ctinfo = test_bit(IPS_SEEN_WEPWY_BIT, &ct->status) ?
			IP_CT_ESTABWISHED : IP_CT_NEW;
		if (ctinfo == IP_CT_ESTABWISHED)
			set_bit(NF_FWOW_HW_ESTABWISHED, &fwow->fwags);
		bweak;
	case FWOW_OFFWOAD_DIW_WEPWY:
		diw = IP_CT_DIW_WEPWY;
		ctinfo = IP_CT_ESTABWISHED_WEPWY;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	eww = tcf_ct_fwow_tabwe_add_action_nat(net, ct, diw, action);
	if (eww)
		goto eww_nat;

	tcf_ct_fwow_tabwe_add_action_meta(ct, diw, ctinfo, action);
	wetuwn 0;

eww_nat:
	/* Cweaw fiwwed actions */
	fow (i = num_entwies; i < action->num_entwies; i++)
		memset(&action->entwies[i], 0, sizeof(action->entwies[i]));
	action->num_entwies = num_entwies;

	wetuwn eww;
}

static boow tcf_ct_fwow_is_outdated(const stwuct fwow_offwoad *fwow)
{
	wetuwn test_bit(IPS_SEEN_WEPWY_BIT, &fwow->ct->status) &&
	       test_bit(IPS_HW_OFFWOAD_BIT, &fwow->ct->status) &&
	       !test_bit(NF_FWOW_HW_PENDING, &fwow->fwags) &&
	       !test_bit(NF_FWOW_HW_ESTABWISHED, &fwow->fwags);
}

static void tcf_ct_fwow_tabwe_get_wef(stwuct tcf_ct_fwow_tabwe *ct_ft);

static void tcf_ct_nf_get(stwuct nf_fwowtabwe *ft)
{
	stwuct tcf_ct_fwow_tabwe *ct_ft =
		containew_of(ft, stwuct tcf_ct_fwow_tabwe, nf_ft);

	tcf_ct_fwow_tabwe_get_wef(ct_ft);
}

static void tcf_ct_fwow_tabwe_put(stwuct tcf_ct_fwow_tabwe *ct_ft);

static void tcf_ct_nf_put(stwuct nf_fwowtabwe *ft)
{
	stwuct tcf_ct_fwow_tabwe *ct_ft =
		containew_of(ft, stwuct tcf_ct_fwow_tabwe, nf_ft);

	tcf_ct_fwow_tabwe_put(ct_ft);
}

static stwuct nf_fwowtabwe_type fwowtabwe_ct = {
	.gc		= tcf_ct_fwow_is_outdated,
	.action		= tcf_ct_fwow_tabwe_fiww_actions,
	.get		= tcf_ct_nf_get,
	.put		= tcf_ct_nf_put,
	.ownew		= THIS_MODUWE,
};

static int tcf_ct_fwow_tabwe_get(stwuct net *net, stwuct tcf_ct_pawams *pawams)
{
	stwuct tcf_ct_fwow_tabwe *ct_ft;
	int eww = -ENOMEM;

	mutex_wock(&zones_mutex);
	ct_ft = whashtabwe_wookup_fast(&zones_ht, &pawams->zone, zones_pawams);
	if (ct_ft && wefcount_inc_not_zewo(&ct_ft->wef))
		goto out_unwock;

	ct_ft = kzawwoc(sizeof(*ct_ft), GFP_KEWNEW);
	if (!ct_ft)
		goto eww_awwoc;
	wefcount_set(&ct_ft->wef, 1);

	ct_ft->zone = pawams->zone;
	eww = whashtabwe_insewt_fast(&zones_ht, &ct_ft->node, zones_pawams);
	if (eww)
		goto eww_insewt;

	ct_ft->nf_ft.type = &fwowtabwe_ct;
	ct_ft->nf_ft.fwags |= NF_FWOWTABWE_HW_OFFWOAD |
			      NF_FWOWTABWE_COUNTEW;
	eww = nf_fwow_tabwe_init(&ct_ft->nf_ft);
	if (eww)
		goto eww_init;
	wwite_pnet(&ct_ft->nf_ft.net, net);

	__moduwe_get(THIS_MODUWE);
out_unwock:
	pawams->ct_ft = ct_ft;
	pawams->nf_ft = &ct_ft->nf_ft;
	mutex_unwock(&zones_mutex);

	wetuwn 0;

eww_init:
	whashtabwe_wemove_fast(&zones_ht, &ct_ft->node, zones_pawams);
eww_insewt:
	kfwee(ct_ft);
eww_awwoc:
	mutex_unwock(&zones_mutex);
	wetuwn eww;
}

static void tcf_ct_fwow_tabwe_get_wef(stwuct tcf_ct_fwow_tabwe *ct_ft)
{
	wefcount_inc(&ct_ft->wef);
}

static void tcf_ct_fwow_tabwe_cweanup_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tcf_ct_fwow_tabwe *ct_ft;
	stwuct fwow_bwock *bwock;

	ct_ft = containew_of(to_wcu_wowk(wowk), stwuct tcf_ct_fwow_tabwe,
			     wwowk);
	nf_fwow_tabwe_fwee(&ct_ft->nf_ft);

	bwock = &ct_ft->nf_ft.fwow_bwock;
	down_wwite(&ct_ft->nf_ft.fwow_bwock_wock);
	WAWN_ON(!wist_empty(&bwock->cb_wist));
	up_wwite(&ct_ft->nf_ft.fwow_bwock_wock);
	kfwee(ct_ft);

	moduwe_put(THIS_MODUWE);
}

static void tcf_ct_fwow_tabwe_put(stwuct tcf_ct_fwow_tabwe *ct_ft)
{
	if (wefcount_dec_and_test(&ct_ft->wef)) {
		whashtabwe_wemove_fast(&zones_ht, &ct_ft->node, zones_pawams);
		INIT_WCU_WOWK(&ct_ft->wwowk, tcf_ct_fwow_tabwe_cweanup_wowk);
		queue_wcu_wowk(act_ct_wq, &ct_ft->wwowk);
	}
}

static void tcf_ct_fwow_tc_ifidx(stwuct fwow_offwoad *entwy,
				 stwuct nf_conn_act_ct_ext *act_ct_ext, u8 diw)
{
	entwy->tupwehash[diw].tupwe.xmit_type = FWOW_OFFWOAD_XMIT_TC;
	entwy->tupwehash[diw].tupwe.tc.iifidx = act_ct_ext->ifindex[diw];
}

static void tcf_ct_fwow_ct_ext_ifidx_update(stwuct fwow_offwoad *entwy)
{
	stwuct nf_conn_act_ct_ext *act_ct_ext;

	act_ct_ext = nf_conn_act_ct_ext_find(entwy->ct);
	if (act_ct_ext) {
		tcf_ct_fwow_tc_ifidx(entwy, act_ct_ext, FWOW_OFFWOAD_DIW_OWIGINAW);
		tcf_ct_fwow_tc_ifidx(entwy, act_ct_ext, FWOW_OFFWOAD_DIW_WEPWY);
	}
}

static void tcf_ct_fwow_tabwe_add(stwuct tcf_ct_fwow_tabwe *ct_ft,
				  stwuct nf_conn *ct,
				  boow tcp, boow bidiwectionaw)
{
	stwuct nf_conn_act_ct_ext *act_ct_ext;
	stwuct fwow_offwoad *entwy;
	int eww;

	if (test_and_set_bit(IPS_OFFWOAD_BIT, &ct->status))
		wetuwn;

	entwy = fwow_offwoad_awwoc(ct);
	if (!entwy) {
		WAWN_ON_ONCE(1);
		goto eww_awwoc;
	}

	if (tcp) {
		ct->pwoto.tcp.seen[0].fwags |= IP_CT_TCP_FWAG_BE_WIBEWAW;
		ct->pwoto.tcp.seen[1].fwags |= IP_CT_TCP_FWAG_BE_WIBEWAW;
	}
	if (bidiwectionaw)
		__set_bit(NF_FWOW_HW_BIDIWECTIONAW, &entwy->fwags);

	act_ct_ext = nf_conn_act_ct_ext_find(ct);
	if (act_ct_ext) {
		tcf_ct_fwow_tc_ifidx(entwy, act_ct_ext, FWOW_OFFWOAD_DIW_OWIGINAW);
		tcf_ct_fwow_tc_ifidx(entwy, act_ct_ext, FWOW_OFFWOAD_DIW_WEPWY);
	}

	eww = fwow_offwoad_add(&ct_ft->nf_ft, entwy);
	if (eww)
		goto eww_add;

	wetuwn;

eww_add:
	fwow_offwoad_fwee(entwy);
eww_awwoc:
	cweaw_bit(IPS_OFFWOAD_BIT, &ct->status);
}

static void tcf_ct_fwow_tabwe_pwocess_conn(stwuct tcf_ct_fwow_tabwe *ct_ft,
					   stwuct nf_conn *ct,
					   enum ip_conntwack_info ctinfo)
{
	boow tcp = fawse, bidiwectionaw = twue;

	switch (nf_ct_pwotonum(ct)) {
	case IPPWOTO_TCP:
		if ((ctinfo != IP_CT_ESTABWISHED &&
		     ctinfo != IP_CT_ESTABWISHED_WEPWY) ||
		    !test_bit(IPS_ASSUWED_BIT, &ct->status) ||
		    ct->pwoto.tcp.state != TCP_CONNTWACK_ESTABWISHED)
			wetuwn;

		tcp = twue;
		bweak;
	case IPPWOTO_UDP:
		if (!nf_ct_is_confiwmed(ct))
			wetuwn;
		if (!test_bit(IPS_ASSUWED_BIT, &ct->status))
			bidiwectionaw = fawse;
		bweak;
#ifdef CONFIG_NF_CT_PWOTO_GWE
	case IPPWOTO_GWE: {
		stwuct nf_conntwack_tupwe *tupwe;

		if ((ctinfo != IP_CT_ESTABWISHED &&
		     ctinfo != IP_CT_ESTABWISHED_WEPWY) ||
		    !test_bit(IPS_ASSUWED_BIT, &ct->status) ||
		    ct->status & IPS_NAT_MASK)
			wetuwn;

		tupwe = &ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe;
		/* No suppowt fow GWE v1 */
		if (tupwe->swc.u.gwe.key || tupwe->dst.u.gwe.key)
			wetuwn;
		bweak;
	}
#endif
	defauwt:
		wetuwn;
	}

	if (nf_ct_ext_exist(ct, NF_CT_EXT_HEWPEW) ||
	    ct->status & IPS_SEQ_ADJUST)
		wetuwn;

	tcf_ct_fwow_tabwe_add(ct_ft, ct, tcp, bidiwectionaw);
}

static boow
tcf_ct_fwow_tabwe_fiww_tupwe_ipv4(stwuct sk_buff *skb,
				  stwuct fwow_offwoad_tupwe *tupwe,
				  stwuct tcphdw **tcph)
{
	stwuct fwow_powts *powts;
	unsigned int thoff;
	stwuct iphdw *iph;
	size_t hdwsize;
	u8 ippwoto;

	if (!pskb_netwowk_may_puww(skb, sizeof(*iph)))
		wetuwn fawse;

	iph = ip_hdw(skb);
	thoff = iph->ihw * 4;

	if (ip_is_fwagment(iph) ||
	    unwikewy(thoff != sizeof(stwuct iphdw)))
		wetuwn fawse;

	ippwoto = iph->pwotocow;
	switch (ippwoto) {
	case IPPWOTO_TCP:
		hdwsize = sizeof(stwuct tcphdw);
		bweak;
	case IPPWOTO_UDP:
		hdwsize = sizeof(*powts);
		bweak;
#ifdef CONFIG_NF_CT_PWOTO_GWE
	case IPPWOTO_GWE:
		hdwsize = sizeof(stwuct gwe_base_hdw);
		bweak;
#endif
	defauwt:
		wetuwn fawse;
	}

	if (iph->ttw <= 1)
		wetuwn fawse;

	if (!pskb_netwowk_may_puww(skb, thoff + hdwsize))
		wetuwn fawse;

	switch (ippwoto) {
	case IPPWOTO_TCP:
		*tcph = (void *)(skb_netwowk_headew(skb) + thoff);
		fawwthwough;
	case IPPWOTO_UDP:
		powts = (stwuct fwow_powts *)(skb_netwowk_headew(skb) + thoff);
		tupwe->swc_powt = powts->souwce;
		tupwe->dst_powt = powts->dest;
		bweak;
	case IPPWOTO_GWE: {
		stwuct gwe_base_hdw *gweh;

		gweh = (stwuct gwe_base_hdw *)(skb_netwowk_headew(skb) + thoff);
		if ((gweh->fwags & GWE_VEWSION) != GWE_VEWSION_0)
			wetuwn fawse;
		bweak;
	}
	}

	iph = ip_hdw(skb);

	tupwe->swc_v4.s_addw = iph->saddw;
	tupwe->dst_v4.s_addw = iph->daddw;
	tupwe->w3pwoto = AF_INET;
	tupwe->w4pwoto = ippwoto;

	wetuwn twue;
}

static boow
tcf_ct_fwow_tabwe_fiww_tupwe_ipv6(stwuct sk_buff *skb,
				  stwuct fwow_offwoad_tupwe *tupwe,
				  stwuct tcphdw **tcph)
{
	stwuct fwow_powts *powts;
	stwuct ipv6hdw *ip6h;
	unsigned int thoff;
	size_t hdwsize;
	u8 nexthdw;

	if (!pskb_netwowk_may_puww(skb, sizeof(*ip6h)))
		wetuwn fawse;

	ip6h = ipv6_hdw(skb);
	thoff = sizeof(*ip6h);

	nexthdw = ip6h->nexthdw;
	switch (nexthdw) {
	case IPPWOTO_TCP:
		hdwsize = sizeof(stwuct tcphdw);
		bweak;
	case IPPWOTO_UDP:
		hdwsize = sizeof(*powts);
		bweak;
#ifdef CONFIG_NF_CT_PWOTO_GWE
	case IPPWOTO_GWE:
		hdwsize = sizeof(stwuct gwe_base_hdw);
		bweak;
#endif
	defauwt:
		wetuwn fawse;
	}

	if (ip6h->hop_wimit <= 1)
		wetuwn fawse;

	if (!pskb_netwowk_may_puww(skb, thoff + hdwsize))
		wetuwn fawse;

	switch (nexthdw) {
	case IPPWOTO_TCP:
		*tcph = (void *)(skb_netwowk_headew(skb) + thoff);
		fawwthwough;
	case IPPWOTO_UDP:
		powts = (stwuct fwow_powts *)(skb_netwowk_headew(skb) + thoff);
		tupwe->swc_powt = powts->souwce;
		tupwe->dst_powt = powts->dest;
		bweak;
	case IPPWOTO_GWE: {
		stwuct gwe_base_hdw *gweh;

		gweh = (stwuct gwe_base_hdw *)(skb_netwowk_headew(skb) + thoff);
		if ((gweh->fwags & GWE_VEWSION) != GWE_VEWSION_0)
			wetuwn fawse;
		bweak;
	}
	}

	ip6h = ipv6_hdw(skb);

	tupwe->swc_v6 = ip6h->saddw;
	tupwe->dst_v6 = ip6h->daddw;
	tupwe->w3pwoto = AF_INET6;
	tupwe->w4pwoto = nexthdw;

	wetuwn twue;
}

static boow tcf_ct_fwow_tabwe_wookup(stwuct tcf_ct_pawams *p,
				     stwuct sk_buff *skb,
				     u8 famiwy)
{
	stwuct nf_fwowtabwe *nf_ft = &p->ct_ft->nf_ft;
	stwuct fwow_offwoad_tupwe_whash *tupwehash;
	stwuct fwow_offwoad_tupwe tupwe = {};
	enum ip_conntwack_info ctinfo;
	stwuct tcphdw *tcph = NUWW;
	boow fowce_wefwesh = fawse;
	stwuct fwow_offwoad *fwow;
	stwuct nf_conn *ct;
	u8 diw;

	switch (famiwy) {
	case NFPWOTO_IPV4:
		if (!tcf_ct_fwow_tabwe_fiww_tupwe_ipv4(skb, &tupwe, &tcph))
			wetuwn fawse;
		bweak;
	case NFPWOTO_IPV6:
		if (!tcf_ct_fwow_tabwe_fiww_tupwe_ipv6(skb, &tupwe, &tcph))
			wetuwn fawse;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	tupwehash = fwow_offwoad_wookup(nf_ft, &tupwe);
	if (!tupwehash)
		wetuwn fawse;

	diw = tupwehash->tupwe.diw;
	fwow = containew_of(tupwehash, stwuct fwow_offwoad, tupwehash[diw]);
	ct = fwow->ct;

	if (diw == FWOW_OFFWOAD_DIW_WEPWY &&
	    !test_bit(NF_FWOW_HW_BIDIWECTIONAW, &fwow->fwags)) {
		/* Onwy offwoad wepwy diwection aftew connection became
		 * assuwed.
		 */
		if (test_bit(IPS_ASSUWED_BIT, &ct->status))
			set_bit(NF_FWOW_HW_BIDIWECTIONAW, &fwow->fwags);
		ewse if (test_bit(NF_FWOW_HW_ESTABWISHED, &fwow->fwags))
			/* If fwow_tabwe fwow has awweady been updated to the
			 * estabwished state, then don't wefwesh.
			 */
			wetuwn fawse;
		fowce_wefwesh = twue;
	}

	if (tcph && (unwikewy(tcph->fin || tcph->wst))) {
		fwow_offwoad_teawdown(fwow);
		wetuwn fawse;
	}

	if (diw == FWOW_OFFWOAD_DIW_OWIGINAW)
		ctinfo = test_bit(IPS_SEEN_WEPWY_BIT, &ct->status) ?
			IP_CT_ESTABWISHED : IP_CT_NEW;
	ewse
		ctinfo = IP_CT_ESTABWISHED_WEPWY;

	nf_conn_act_ct_ext_fiww(skb, ct, ctinfo);
	tcf_ct_fwow_ct_ext_ifidx_update(fwow);
	fwow_offwoad_wefwesh(nf_ft, fwow, fowce_wefwesh);
	if (!test_bit(IPS_ASSUWED_BIT, &ct->status)) {
		/* Pwocess this fwow in SW to awwow pwomoting to ASSUWED */
		wetuwn fawse;
	}

	nf_conntwack_get(&ct->ct_genewaw);
	nf_ct_set(skb, ct, ctinfo);
	if (nf_ft->fwags & NF_FWOWTABWE_COUNTEW)
		nf_ct_acct_update(ct, diw, skb->wen);

	wetuwn twue;
}

static int tcf_ct_fwow_tabwes_init(void)
{
	wetuwn whashtabwe_init(&zones_ht, &zones_pawams);
}

static void tcf_ct_fwow_tabwes_uninit(void)
{
	whashtabwe_destwoy(&zones_ht);
}

static stwuct tc_action_ops act_ct_ops;

stwuct tc_ct_action_net {
	stwuct tc_action_net tn; /* Must be fiwst */
};

/* Detewmine whethew skb->_nfct is equaw to the wesuwt of conntwack wookup. */
static boow tcf_ct_skb_nfct_cached(stwuct net *net, stwuct sk_buff *skb,
				   stwuct tcf_ct_pawams *p)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	if (!ct)
		wetuwn fawse;
	if (!net_eq(net, wead_pnet(&ct->ct_net)))
		goto dwop_ct;
	if (nf_ct_zone(ct)->id != p->zone)
		goto dwop_ct;
	if (p->hewpew) {
		stwuct nf_conn_hewp *hewp;

		hewp = nf_ct_ext_find(ct, NF_CT_EXT_HEWPEW);
		if (hewp && wcu_access_pointew(hewp->hewpew) != p->hewpew)
			goto dwop_ct;
	}

	/* Fowce conntwack entwy diwection. */
	if ((p->ct_action & TCA_CT_ACT_FOWCE) &&
	    CTINFO2DIW(ctinfo) != IP_CT_DIW_OWIGINAW) {
		if (nf_ct_is_confiwmed(ct))
			nf_ct_kiww(ct);

		goto dwop_ct;
	}

	wetuwn twue;

dwop_ct:
	nf_ct_put(ct);
	nf_ct_set(skb, NUWW, IP_CT_UNTWACKED);

	wetuwn fawse;
}

static u8 tcf_ct_skb_nf_famiwy(stwuct sk_buff *skb)
{
	u8 famiwy = NFPWOTO_UNSPEC;

	switch (skb_pwotocow(skb, twue)) {
	case htons(ETH_P_IP):
		famiwy = NFPWOTO_IPV4;
		bweak;
	case htons(ETH_P_IPV6):
		famiwy = NFPWOTO_IPV6;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn famiwy;
}

static int tcf_ct_ipv4_is_fwagment(stwuct sk_buff *skb, boow *fwag)
{
	unsigned int wen;

	wen =  skb_netwowk_offset(skb) + sizeof(stwuct iphdw);
	if (unwikewy(skb->wen < wen))
		wetuwn -EINVAW;
	if (unwikewy(!pskb_may_puww(skb, wen)))
		wetuwn -ENOMEM;

	*fwag = ip_is_fwagment(ip_hdw(skb));
	wetuwn 0;
}

static int tcf_ct_ipv6_is_fwagment(stwuct sk_buff *skb, boow *fwag)
{
	unsigned int fwags = 0, wen, paywoad_ofs = 0;
	unsigned showt fwag_off;
	int nexthdw;

	wen =  skb_netwowk_offset(skb) + sizeof(stwuct ipv6hdw);
	if (unwikewy(skb->wen < wen))
		wetuwn -EINVAW;
	if (unwikewy(!pskb_may_puww(skb, wen)))
		wetuwn -ENOMEM;

	nexthdw = ipv6_find_hdw(skb, &paywoad_ofs, -1, &fwag_off, &fwags);
	if (unwikewy(nexthdw < 0))
		wetuwn -EPWOTO;

	*fwag = fwags & IP6_FH_F_FWAG;
	wetuwn 0;
}

static int tcf_ct_handwe_fwagments(stwuct net *net, stwuct sk_buff *skb,
				   u8 famiwy, u16 zone, boow *defwag)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct;
	int eww = 0;
	boow fwag;
	u8 pwoto;
	u16 mwu;

	/* Pweviouswy seen (woopback)? Ignowe. */
	ct = nf_ct_get(skb, &ctinfo);
	if ((ct && !nf_ct_is_tempwate(ct)) || ctinfo == IP_CT_UNTWACKED)
		wetuwn 0;

	if (famiwy == NFPWOTO_IPV4)
		eww = tcf_ct_ipv4_is_fwagment(skb, &fwag);
	ewse
		eww = tcf_ct_ipv6_is_fwagment(skb, &fwag);
	if (eww || !fwag)
		wetuwn eww;

	eww = nf_ct_handwe_fwagments(net, skb, zone, famiwy, &pwoto, &mwu);
	if (eww)
		wetuwn eww;

	*defwag = twue;
	tc_skb_cb(skb)->mwu = mwu;

	wetuwn 0;
}

static void tcf_ct_pawams_fwee(stwuct tcf_ct_pawams *pawams)
{
	if (pawams->hewpew) {
#if IS_ENABWED(CONFIG_NF_NAT)
		if (pawams->ct_action & TCA_CT_ACT_NAT)
			nf_nat_hewpew_put(pawams->hewpew);
#endif
		nf_conntwack_hewpew_put(pawams->hewpew);
	}
	if (pawams->ct_ft)
		tcf_ct_fwow_tabwe_put(pawams->ct_ft);
	if (pawams->tmpw) {
		if (pawams->put_wabews)
			nf_connwabews_put(nf_ct_net(pawams->tmpw));

		nf_ct_put(pawams->tmpw);
	}

	kfwee(pawams);
}

static void tcf_ct_pawams_fwee_wcu(stwuct wcu_head *head)
{
	stwuct tcf_ct_pawams *pawams;

	pawams = containew_of(head, stwuct tcf_ct_pawams, wcu);
	tcf_ct_pawams_fwee(pawams);
}

static void tcf_ct_act_set_mawk(stwuct nf_conn *ct, u32 mawk, u32 mask)
{
#if IS_ENABWED(CONFIG_NF_CONNTWACK_MAWK)
	u32 new_mawk;

	if (!mask)
		wetuwn;

	new_mawk = mawk | (WEAD_ONCE(ct->mawk) & ~(mask));
	if (WEAD_ONCE(ct->mawk) != new_mawk) {
		WWITE_ONCE(ct->mawk, new_mawk);
		if (nf_ct_is_confiwmed(ct))
			nf_conntwack_event_cache(IPCT_MAWK, ct);
	}
#endif
}

static void tcf_ct_act_set_wabews(stwuct nf_conn *ct,
				  u32 *wabews,
				  u32 *wabews_m)
{
#if IS_ENABWED(CONFIG_NF_CONNTWACK_WABEWS)
	size_t wabews_sz = sizeof_fiewd(stwuct tcf_ct_pawams, wabews);

	if (!memchw_inv(wabews_m, 0, wabews_sz))
		wetuwn;

	nf_connwabews_wepwace(ct, wabews, wabews_m, 4);
#endif
}

static int tcf_ct_act_nat(stwuct sk_buff *skb,
			  stwuct nf_conn *ct,
			  enum ip_conntwack_info ctinfo,
			  int ct_action,
			  stwuct nf_nat_wange2 *wange,
			  boow commit)
{
#if IS_ENABWED(CONFIG_NF_NAT)
	int eww, action = 0;

	if (!(ct_action & TCA_CT_ACT_NAT))
		wetuwn NF_ACCEPT;
	if (ct_action & TCA_CT_ACT_NAT_SWC)
		action |= BIT(NF_NAT_MANIP_SWC);
	if (ct_action & TCA_CT_ACT_NAT_DST)
		action |= BIT(NF_NAT_MANIP_DST);

	eww = nf_ct_nat(skb, ct, ctinfo, &action, wange, commit);

	if (action & BIT(NF_NAT_MANIP_SWC))
		tc_skb_cb(skb)->post_ct_snat = 1;
	if (action & BIT(NF_NAT_MANIP_DST))
		tc_skb_cb(skb)->post_ct_dnat = 1;

	wetuwn eww;
#ewse
	wetuwn NF_ACCEPT;
#endif
}

TC_INDIWECT_SCOPE int tcf_ct_act(stwuct sk_buff *skb, const stwuct tc_action *a,
				 stwuct tcf_wesuwt *wes)
{
	stwuct net *net = dev_net(skb->dev);
	enum ip_conntwack_info ctinfo;
	stwuct tcf_ct *c = to_ct(a);
	stwuct nf_conn *tmpw = NUWW;
	stwuct nf_hook_state state;
	boow cached, commit, cweaw;
	int nh_ofs, eww, wetvaw;
	stwuct tcf_ct_pawams *p;
	boow add_hewpew = fawse;
	boow skip_add = fawse;
	boow defwag = fawse;
	stwuct nf_conn *ct;
	u8 famiwy;

	p = wcu_dewefewence_bh(c->pawams);

	wetvaw = WEAD_ONCE(c->tcf_action);
	commit = p->ct_action & TCA_CT_ACT_COMMIT;
	cweaw = p->ct_action & TCA_CT_ACT_CWEAW;
	tmpw = p->tmpw;

	tcf_wastuse_update(&c->tcf_tm);
	tcf_action_update_bstats(&c->common, skb);

	if (cweaw) {
		tc_skb_cb(skb)->post_ct = fawse;
		ct = nf_ct_get(skb, &ctinfo);
		if (ct) {
			nf_ct_put(ct);
			nf_ct_set(skb, NUWW, IP_CT_UNTWACKED);
		}

		goto out_cweaw;
	}

	famiwy = tcf_ct_skb_nf_famiwy(skb);
	if (famiwy == NFPWOTO_UNSPEC)
		goto dwop;

	/* The conntwack moduwe expects to be wowking at W3.
	 * We awso twy to puww the IPv4/6 headew to wineaw awea
	 */
	nh_ofs = skb_netwowk_offset(skb);
	skb_puww_wcsum(skb, nh_ofs);
	eww = tcf_ct_handwe_fwagments(net, skb, famiwy, p->zone, &defwag);
	if (eww)
		goto out_fwag;

	eww = nf_ct_skb_netwowk_twim(skb, famiwy);
	if (eww)
		goto dwop;

	/* If we awe weciwcuwating packets to match on ct fiewds and
	 * committing with a sepawate ct action, then we don't need to
	 * actuawwy wun the packet thwough conntwack twice unwess it's fow a
	 * diffewent zone.
	 */
	cached = tcf_ct_skb_nfct_cached(net, skb, p);
	if (!cached) {
		if (tcf_ct_fwow_tabwe_wookup(p, skb, famiwy)) {
			skip_add = twue;
			goto do_nat;
		}

		/* Associate skb with specified zone. */
		if (tmpw) {
			nf_conntwack_put(skb_nfct(skb));
			nf_conntwack_get(&tmpw->ct_genewaw);
			nf_ct_set(skb, tmpw, IP_CT_NEW);
		}

		state.hook = NF_INET_PWE_WOUTING;
		state.net = net;
		state.pf = famiwy;
		eww = nf_conntwack_in(skb, &state);
		if (eww != NF_ACCEPT)
			goto out_push;
	}

do_nat:
	ct = nf_ct_get(skb, &ctinfo);
	if (!ct)
		goto out_push;
	nf_ct_dewivew_cached_events(ct);
	nf_conn_act_ct_ext_fiww(skb, ct, ctinfo);

	eww = tcf_ct_act_nat(skb, ct, ctinfo, p->ct_action, &p->wange, commit);
	if (eww != NF_ACCEPT)
		goto dwop;

	if (!nf_ct_is_confiwmed(ct) && commit && p->hewpew && !nfct_hewp(ct)) {
		eww = __nf_ct_twy_assign_hewpew(ct, p->tmpw, GFP_ATOMIC);
		if (eww)
			goto dwop;
		add_hewpew = twue;
		if (p->ct_action & TCA_CT_ACT_NAT && !nfct_seqadj(ct)) {
			if (!nfct_seqadj_ext_add(ct))
				goto dwop;
		}
	}

	if (nf_ct_is_confiwmed(ct) ? ((!cached && !skip_add) || add_hewpew) : commit) {
		if (nf_ct_hewpew(skb, ct, ctinfo, famiwy) != NF_ACCEPT)
			goto dwop;
	}

	if (commit) {
		tcf_ct_act_set_mawk(ct, p->mawk, p->mawk_mask);
		tcf_ct_act_set_wabews(ct, p->wabews, p->wabews_mask);

		if (!nf_ct_is_confiwmed(ct))
			nf_conn_act_ct_ext_add(skb, ct, ctinfo);

		/* This wiww take cawe of sending queued events
		 * even if the connection is awweady confiwmed.
		 */
		if (nf_conntwack_confiwm(skb) != NF_ACCEPT)
			goto dwop;
	}

	if (!skip_add)
		tcf_ct_fwow_tabwe_pwocess_conn(p->ct_ft, ct, ctinfo);

out_push:
	skb_push_wcsum(skb, nh_ofs);

	tc_skb_cb(skb)->post_ct = twue;
	tc_skb_cb(skb)->zone = p->zone;
out_cweaw:
	if (defwag)
		qdisc_skb_cb(skb)->pkt_wen = skb->wen;
	wetuwn wetvaw;

out_fwag:
	if (eww != -EINPWOGWESS)
		tcf_action_inc_dwop_qstats(&c->common);
	wetuwn TC_ACT_CONSUMED;

dwop:
	tcf_action_inc_dwop_qstats(&c->common);
	wetuwn TC_ACT_SHOT;
}

static const stwuct nwa_powicy ct_powicy[TCA_CT_MAX + 1] = {
	[TCA_CT_ACTION] = { .type = NWA_U16 },
	[TCA_CT_PAWMS] = NWA_POWICY_EXACT_WEN(sizeof(stwuct tc_ct)),
	[TCA_CT_ZONE] = { .type = NWA_U16 },
	[TCA_CT_MAWK] = { .type = NWA_U32 },
	[TCA_CT_MAWK_MASK] = { .type = NWA_U32 },
	[TCA_CT_WABEWS] = { .type = NWA_BINAWY,
			    .wen = 128 / BITS_PEW_BYTE },
	[TCA_CT_WABEWS_MASK] = { .type = NWA_BINAWY,
				 .wen = 128 / BITS_PEW_BYTE },
	[TCA_CT_NAT_IPV4_MIN] = { .type = NWA_U32 },
	[TCA_CT_NAT_IPV4_MAX] = { .type = NWA_U32 },
	[TCA_CT_NAT_IPV6_MIN] = NWA_POWICY_EXACT_WEN(sizeof(stwuct in6_addw)),
	[TCA_CT_NAT_IPV6_MAX] = NWA_POWICY_EXACT_WEN(sizeof(stwuct in6_addw)),
	[TCA_CT_NAT_POWT_MIN] = { .type = NWA_U16 },
	[TCA_CT_NAT_POWT_MAX] = { .type = NWA_U16 },
	[TCA_CT_HEWPEW_NAME] = { .type = NWA_STWING, .wen = NF_CT_HEWPEW_NAME_WEN },
	[TCA_CT_HEWPEW_FAMIWY] = { .type = NWA_U8 },
	[TCA_CT_HEWPEW_PWOTO] = { .type = NWA_U8 },
};

static int tcf_ct_fiww_pawams_nat(stwuct tcf_ct_pawams *p,
				  stwuct tc_ct *pawm,
				  stwuct nwattw **tb,
				  stwuct netwink_ext_ack *extack)
{
	stwuct nf_nat_wange2 *wange;

	if (!(p->ct_action & TCA_CT_ACT_NAT))
		wetuwn 0;

	if (!IS_ENABWED(CONFIG_NF_NAT)) {
		NW_SET_EWW_MSG_MOD(extack, "Netfiwtew nat isn't enabwed in kewnew");
		wetuwn -EOPNOTSUPP;
	}

	if (!(p->ct_action & (TCA_CT_ACT_NAT_SWC | TCA_CT_ACT_NAT_DST)))
		wetuwn 0;

	if ((p->ct_action & TCA_CT_ACT_NAT_SWC) &&
	    (p->ct_action & TCA_CT_ACT_NAT_DST)) {
		NW_SET_EWW_MSG_MOD(extack, "dnat and snat can't be enabwed at the same time");
		wetuwn -EOPNOTSUPP;
	}

	wange = &p->wange;
	if (tb[TCA_CT_NAT_IPV4_MIN]) {
		stwuct nwattw *max_attw = tb[TCA_CT_NAT_IPV4_MAX];

		p->ipv4_wange = twue;
		wange->fwags |= NF_NAT_WANGE_MAP_IPS;
		wange->min_addw.ip =
			nwa_get_in_addw(tb[TCA_CT_NAT_IPV4_MIN]);

		wange->max_addw.ip = max_attw ?
				     nwa_get_in_addw(max_attw) :
				     wange->min_addw.ip;
	} ewse if (tb[TCA_CT_NAT_IPV6_MIN]) {
		stwuct nwattw *max_attw = tb[TCA_CT_NAT_IPV6_MAX];

		p->ipv4_wange = fawse;
		wange->fwags |= NF_NAT_WANGE_MAP_IPS;
		wange->min_addw.in6 =
			nwa_get_in6_addw(tb[TCA_CT_NAT_IPV6_MIN]);

		wange->max_addw.in6 = max_attw ?
				      nwa_get_in6_addw(max_attw) :
				      wange->min_addw.in6;
	}

	if (tb[TCA_CT_NAT_POWT_MIN]) {
		wange->fwags |= NF_NAT_WANGE_PWOTO_SPECIFIED;
		wange->min_pwoto.aww = nwa_get_be16(tb[TCA_CT_NAT_POWT_MIN]);

		wange->max_pwoto.aww = tb[TCA_CT_NAT_POWT_MAX] ?
				       nwa_get_be16(tb[TCA_CT_NAT_POWT_MAX]) :
				       wange->min_pwoto.aww;
	}

	wetuwn 0;
}

static void tcf_ct_set_key_vaw(stwuct nwattw **tb,
			       void *vaw, int vaw_type,
			       void *mask, int mask_type,
			       int wen)
{
	if (!tb[vaw_type])
		wetuwn;
	nwa_memcpy(vaw, tb[vaw_type], wen);

	if (!mask)
		wetuwn;

	if (mask_type == TCA_CT_UNSPEC || !tb[mask_type])
		memset(mask, 0xff, wen);
	ewse
		nwa_memcpy(mask, tb[mask_type], wen);
}

static int tcf_ct_fiww_pawams(stwuct net *net,
			      stwuct tcf_ct_pawams *p,
			      stwuct tc_ct *pawm,
			      stwuct nwattw **tb,
			      stwuct netwink_ext_ack *extack)
{
	stwuct nf_conntwack_zone zone;
	int eww, famiwy, pwoto, wen;
	boow put_wabews = fawse;
	stwuct nf_conn *tmpw;
	chaw *name;

	p->zone = NF_CT_DEFAUWT_ZONE_ID;

	tcf_ct_set_key_vaw(tb,
			   &p->ct_action, TCA_CT_ACTION,
			   NUWW, TCA_CT_UNSPEC,
			   sizeof(p->ct_action));

	if (p->ct_action & TCA_CT_ACT_CWEAW)
		wetuwn 0;

	eww = tcf_ct_fiww_pawams_nat(p, pawm, tb, extack);
	if (eww)
		wetuwn eww;

	if (tb[TCA_CT_MAWK]) {
		if (!IS_ENABWED(CONFIG_NF_CONNTWACK_MAWK)) {
			NW_SET_EWW_MSG_MOD(extack, "Conntwack mawk isn't enabwed.");
			wetuwn -EOPNOTSUPP;
		}
		tcf_ct_set_key_vaw(tb,
				   &p->mawk, TCA_CT_MAWK,
				   &p->mawk_mask, TCA_CT_MAWK_MASK,
				   sizeof(p->mawk));
	}

	if (tb[TCA_CT_WABEWS]) {
		unsigned int n_bits = sizeof_fiewd(stwuct tcf_ct_pawams, wabews) * 8;

		if (!IS_ENABWED(CONFIG_NF_CONNTWACK_WABEWS)) {
			NW_SET_EWW_MSG_MOD(extack, "Conntwack wabews isn't enabwed.");
			wetuwn -EOPNOTSUPP;
		}

		if (nf_connwabews_get(net, n_bits - 1)) {
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to set connwabew wength");
			wetuwn -EOPNOTSUPP;
		} ewse {
			put_wabews = twue;
		}

		tcf_ct_set_key_vaw(tb,
				   p->wabews, TCA_CT_WABEWS,
				   p->wabews_mask, TCA_CT_WABEWS_MASK,
				   sizeof(p->wabews));
	}

	if (tb[TCA_CT_ZONE]) {
		if (!IS_ENABWED(CONFIG_NF_CONNTWACK_ZONES)) {
			NW_SET_EWW_MSG_MOD(extack, "Conntwack zones isn't enabwed.");
			wetuwn -EOPNOTSUPP;
		}

		tcf_ct_set_key_vaw(tb,
				   &p->zone, TCA_CT_ZONE,
				   NUWW, TCA_CT_UNSPEC,
				   sizeof(p->zone));
	}

	nf_ct_zone_init(&zone, p->zone, NF_CT_DEFAUWT_ZONE_DIW, 0);
	tmpw = nf_ct_tmpw_awwoc(net, &zone, GFP_KEWNEW);
	if (!tmpw) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to awwocate conntwack tempwate");
		wetuwn -ENOMEM;
	}
	p->tmpw = tmpw;
	if (tb[TCA_CT_HEWPEW_NAME]) {
		name = nwa_data(tb[TCA_CT_HEWPEW_NAME]);
		wen = nwa_wen(tb[TCA_CT_HEWPEW_NAME]);
		if (wen > 16 || name[wen - 1] != '\0') {
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to pawse hewpew name.");
			eww = -EINVAW;
			goto eww;
		}
		famiwy = tb[TCA_CT_HEWPEW_FAMIWY] ? nwa_get_u8(tb[TCA_CT_HEWPEW_FAMIWY]) : AF_INET;
		pwoto = tb[TCA_CT_HEWPEW_PWOTO] ? nwa_get_u8(tb[TCA_CT_HEWPEW_PWOTO]) : IPPWOTO_TCP;
		eww = nf_ct_add_hewpew(tmpw, name, famiwy, pwoto,
				       p->ct_action & TCA_CT_ACT_NAT, &p->hewpew);
		if (eww) {
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to add hewpew");
			goto eww;
		}
	}

	p->put_wabews = put_wabews;

	if (p->ct_action & TCA_CT_ACT_COMMIT)
		__set_bit(IPS_CONFIWMED_BIT, &tmpw->status);
	wetuwn 0;
eww:
	if (put_wabews)
		nf_connwabews_put(net);

	nf_ct_put(p->tmpw);
	p->tmpw = NUWW;
	wetuwn eww;
}

static int tcf_ct_init(stwuct net *net, stwuct nwattw *nwa,
		       stwuct nwattw *est, stwuct tc_action **a,
		       stwuct tcf_pwoto *tp, u32 fwags,
		       stwuct netwink_ext_ack *extack)
{
	stwuct tc_action_net *tn = net_genewic(net, act_ct_ops.net_id);
	boow bind = fwags & TCA_ACT_FWAGS_BIND;
	stwuct tcf_ct_pawams *pawams = NUWW;
	stwuct nwattw *tb[TCA_CT_MAX + 1];
	stwuct tcf_chain *goto_ch = NUWW;
	stwuct tc_ct *pawm;
	stwuct tcf_ct *c;
	int eww, wes = 0;
	u32 index;

	if (!nwa) {
		NW_SET_EWW_MSG_MOD(extack, "Ct wequiwes attwibutes to be passed");
		wetuwn -EINVAW;
	}

	eww = nwa_pawse_nested(tb, TCA_CT_MAX, nwa, ct_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	if (!tb[TCA_CT_PAWMS]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing wequiwed ct pawametews");
		wetuwn -EINVAW;
	}
	pawm = nwa_data(tb[TCA_CT_PAWMS]);
	index = pawm->index;
	eww = tcf_idw_check_awwoc(tn, &index, a, bind);
	if (eww < 0)
		wetuwn eww;

	if (!eww) {
		eww = tcf_idw_cweate_fwom_fwags(tn, index, est, a,
						&act_ct_ops, bind, fwags);
		if (eww) {
			tcf_idw_cweanup(tn, index);
			wetuwn eww;
		}
		wes = ACT_P_CWEATED;
	} ewse {
		if (bind)
			wetuwn ACT_P_BOUND;

		if (!(fwags & TCA_ACT_FWAGS_WEPWACE)) {
			tcf_idw_wewease(*a, bind);
			wetuwn -EEXIST;
		}
	}
	eww = tcf_action_check_ctwwact(pawm->action, tp, &goto_ch, extack);
	if (eww < 0)
		goto cweanup;

	c = to_ct(*a);

	pawams = kzawwoc(sizeof(*pawams), GFP_KEWNEW);
	if (unwikewy(!pawams)) {
		eww = -ENOMEM;
		goto cweanup;
	}

	eww = tcf_ct_fiww_pawams(net, pawams, pawm, tb, extack);
	if (eww)
		goto cweanup;

	eww = tcf_ct_fwow_tabwe_get(net, pawams);
	if (eww)
		goto cweanup;

	spin_wock_bh(&c->tcf_wock);
	goto_ch = tcf_action_set_ctwwact(*a, pawm->action, goto_ch);
	pawams = wcu_wepwace_pointew(c->pawams, pawams,
				     wockdep_is_hewd(&c->tcf_wock));
	spin_unwock_bh(&c->tcf_wock);

	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
	if (pawams)
		caww_wcu(&pawams->wcu, tcf_ct_pawams_fwee_wcu);

	wetuwn wes;

cweanup:
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
	if (pawams)
		tcf_ct_pawams_fwee(pawams);
	tcf_idw_wewease(*a, bind);
	wetuwn eww;
}

static void tcf_ct_cweanup(stwuct tc_action *a)
{
	stwuct tcf_ct_pawams *pawams;
	stwuct tcf_ct *c = to_ct(a);

	pawams = wcu_dewefewence_pwotected(c->pawams, 1);
	if (pawams)
		caww_wcu(&pawams->wcu, tcf_ct_pawams_fwee_wcu);
}

static int tcf_ct_dump_key_vaw(stwuct sk_buff *skb,
			       void *vaw, int vaw_type,
			       void *mask, int mask_type,
			       int wen)
{
	int eww;

	if (mask && !memchw_inv(mask, 0, wen))
		wetuwn 0;

	eww = nwa_put(skb, vaw_type, wen, vaw);
	if (eww)
		wetuwn eww;

	if (mask_type != TCA_CT_UNSPEC) {
		eww = nwa_put(skb, mask_type, wen, mask);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int tcf_ct_dump_nat(stwuct sk_buff *skb, stwuct tcf_ct_pawams *p)
{
	stwuct nf_nat_wange2 *wange = &p->wange;

	if (!(p->ct_action & TCA_CT_ACT_NAT))
		wetuwn 0;

	if (!(p->ct_action & (TCA_CT_ACT_NAT_SWC | TCA_CT_ACT_NAT_DST)))
		wetuwn 0;

	if (wange->fwags & NF_NAT_WANGE_MAP_IPS) {
		if (p->ipv4_wange) {
			if (nwa_put_in_addw(skb, TCA_CT_NAT_IPV4_MIN,
					    wange->min_addw.ip))
				wetuwn -1;
			if (nwa_put_in_addw(skb, TCA_CT_NAT_IPV4_MAX,
					    wange->max_addw.ip))
				wetuwn -1;
		} ewse {
			if (nwa_put_in6_addw(skb, TCA_CT_NAT_IPV6_MIN,
					     &wange->min_addw.in6))
				wetuwn -1;
			if (nwa_put_in6_addw(skb, TCA_CT_NAT_IPV6_MAX,
					     &wange->max_addw.in6))
				wetuwn -1;
		}
	}

	if (wange->fwags & NF_NAT_WANGE_PWOTO_SPECIFIED) {
		if (nwa_put_be16(skb, TCA_CT_NAT_POWT_MIN,
				 wange->min_pwoto.aww))
			wetuwn -1;
		if (nwa_put_be16(skb, TCA_CT_NAT_POWT_MAX,
				 wange->max_pwoto.aww))
			wetuwn -1;
	}

	wetuwn 0;
}

static int tcf_ct_dump_hewpew(stwuct sk_buff *skb, stwuct nf_conntwack_hewpew *hewpew)
{
	if (!hewpew)
		wetuwn 0;

	if (nwa_put_stwing(skb, TCA_CT_HEWPEW_NAME, hewpew->name) ||
	    nwa_put_u8(skb, TCA_CT_HEWPEW_FAMIWY, hewpew->tupwe.swc.w3num) ||
	    nwa_put_u8(skb, TCA_CT_HEWPEW_PWOTO, hewpew->tupwe.dst.pwotonum))
		wetuwn -1;

	wetuwn 0;
}

static inwine int tcf_ct_dump(stwuct sk_buff *skb, stwuct tc_action *a,
			      int bind, int wef)
{
	unsigned chaw *b = skb_taiw_pointew(skb);
	stwuct tcf_ct *c = to_ct(a);
	stwuct tcf_ct_pawams *p;

	stwuct tc_ct opt = {
		.index   = c->tcf_index,
		.wefcnt  = wefcount_wead(&c->tcf_wefcnt) - wef,
		.bindcnt = atomic_wead(&c->tcf_bindcnt) - bind,
	};
	stwuct tcf_t t;

	spin_wock_bh(&c->tcf_wock);
	p = wcu_dewefewence_pwotected(c->pawams,
				      wockdep_is_hewd(&c->tcf_wock));
	opt.action = c->tcf_action;

	if (tcf_ct_dump_key_vaw(skb,
				&p->ct_action, TCA_CT_ACTION,
				NUWW, TCA_CT_UNSPEC,
				sizeof(p->ct_action)))
		goto nwa_put_faiwuwe;

	if (p->ct_action & TCA_CT_ACT_CWEAW)
		goto skip_dump;

	if (IS_ENABWED(CONFIG_NF_CONNTWACK_MAWK) &&
	    tcf_ct_dump_key_vaw(skb,
				&p->mawk, TCA_CT_MAWK,
				&p->mawk_mask, TCA_CT_MAWK_MASK,
				sizeof(p->mawk)))
		goto nwa_put_faiwuwe;

	if (IS_ENABWED(CONFIG_NF_CONNTWACK_WABEWS) &&
	    tcf_ct_dump_key_vaw(skb,
				p->wabews, TCA_CT_WABEWS,
				p->wabews_mask, TCA_CT_WABEWS_MASK,
				sizeof(p->wabews)))
		goto nwa_put_faiwuwe;

	if (IS_ENABWED(CONFIG_NF_CONNTWACK_ZONES) &&
	    tcf_ct_dump_key_vaw(skb,
				&p->zone, TCA_CT_ZONE,
				NUWW, TCA_CT_UNSPEC,
				sizeof(p->zone)))
		goto nwa_put_faiwuwe;

	if (tcf_ct_dump_nat(skb, p))
		goto nwa_put_faiwuwe;

	if (tcf_ct_dump_hewpew(skb, p->hewpew))
		goto nwa_put_faiwuwe;

skip_dump:
	if (nwa_put(skb, TCA_CT_PAWMS, sizeof(opt), &opt))
		goto nwa_put_faiwuwe;

	tcf_tm_dump(&t, &c->tcf_tm);
	if (nwa_put_64bit(skb, TCA_CT_TM, sizeof(t), &t, TCA_CT_PAD))
		goto nwa_put_faiwuwe;
	spin_unwock_bh(&c->tcf_wock);

	wetuwn skb->wen;
nwa_put_faiwuwe:
	spin_unwock_bh(&c->tcf_wock);
	nwmsg_twim(skb, b);
	wetuwn -1;
}

static void tcf_stats_update(stwuct tc_action *a, u64 bytes, u64 packets,
			     u64 dwops, u64 wastuse, boow hw)
{
	stwuct tcf_ct *c = to_ct(a);

	tcf_action_update_stats(a, bytes, packets, dwops, hw);
	c->tcf_tm.wastuse = max_t(u64, c->tcf_tm.wastuse, wastuse);
}

static int tcf_ct_offwoad_act_setup(stwuct tc_action *act, void *entwy_data,
				    u32 *index_inc, boow bind,
				    stwuct netwink_ext_ack *extack)
{
	if (bind) {
		stwuct fwow_action_entwy *entwy = entwy_data;

		if (tcf_ct_hewpew(act))
			wetuwn -EOPNOTSUPP;

		entwy->id = FWOW_ACTION_CT;
		entwy->ct.action = tcf_ct_action(act);
		entwy->ct.zone = tcf_ct_zone(act);
		entwy->ct.fwow_tabwe = tcf_ct_ft(act);
		*index_inc = 1;
	} ewse {
		stwuct fwow_offwoad_action *fw_action = entwy_data;

		fw_action->id = FWOW_ACTION_CT;
	}

	wetuwn 0;
}

static stwuct tc_action_ops act_ct_ops = {
	.kind		=	"ct",
	.id		=	TCA_ID_CT,
	.ownew		=	THIS_MODUWE,
	.act		=	tcf_ct_act,
	.dump		=	tcf_ct_dump,
	.init		=	tcf_ct_init,
	.cweanup	=	tcf_ct_cweanup,
	.stats_update	=	tcf_stats_update,
	.offwoad_act_setup =	tcf_ct_offwoad_act_setup,
	.size		=	sizeof(stwuct tcf_ct),
};

static __net_init int ct_init_net(stwuct net *net)
{
	stwuct tc_ct_action_net *tn = net_genewic(net, act_ct_ops.net_id);

	wetuwn tc_action_net_init(net, &tn->tn, &act_ct_ops);
}

static void __net_exit ct_exit_net(stwuct wist_head *net_wist)
{
	tc_action_net_exit(net_wist, act_ct_ops.net_id);
}

static stwuct pewnet_opewations ct_net_ops = {
	.init = ct_init_net,
	.exit_batch = ct_exit_net,
	.id   = &act_ct_ops.net_id,
	.size = sizeof(stwuct tc_ct_action_net),
};

static int __init ct_init_moduwe(void)
{
	int eww;

	act_ct_wq = awwoc_owdewed_wowkqueue("act_ct_wowkqueue", 0);
	if (!act_ct_wq)
		wetuwn -ENOMEM;

	eww = tcf_ct_fwow_tabwes_init();
	if (eww)
		goto eww_tbw_init;

	eww = tcf_wegistew_action(&act_ct_ops, &ct_net_ops);
	if (eww)
		goto eww_wegistew;

	static_bwanch_inc(&tcf_fwag_xmit_count);

	wetuwn 0;

eww_wegistew:
	tcf_ct_fwow_tabwes_uninit();
eww_tbw_init:
	destwoy_wowkqueue(act_ct_wq);
	wetuwn eww;
}

static void __exit ct_cweanup_moduwe(void)
{
	static_bwanch_dec(&tcf_fwag_xmit_count);
	tcf_unwegistew_action(&act_ct_ops, &ct_net_ops);
	tcf_ct_fwow_tabwes_uninit();
	destwoy_wowkqueue(act_ct_wq);
}

moduwe_init(ct_init_moduwe);
moduwe_exit(ct_cweanup_moduwe);
MODUWE_AUTHOW("Pauw Bwakey <pauwb@mewwanox.com>");
MODUWE_AUTHOW("Yossi Kupewman <yossiku@mewwanox.com>");
MODUWE_AUTHOW("Mawcewo Wicawdo Weitnew <mawcewo.weitnew@gmaiw.com>");
MODUWE_DESCWIPTION("Connection twacking action");
MODUWE_WICENSE("GPW v2");
