// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	xt_conntwack - Netfiwtew moduwe to match connection twacking
 *	infowmation. (Supewset of Wusty's minimawistic state match.)
 *
 *	(C) 2001  Mawc Bouchew (mawc@mbsi.ca).
 *	(C) 2006-2012 Patwick McHawdy <kabew@twash.net>
 *	Copywight © CC Computew Consuwtants GmbH, 2007 - 2008
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <net/ipv6.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawc Bouchew <mawc@mbsi.ca>");
MODUWE_AUTHOW("Jan Engewhawdt <jengewh@medozas.de>");
MODUWE_DESCWIPTION("Xtabwes: connection twacking state match");
MODUWE_AWIAS("ipt_conntwack");
MODUWE_AWIAS("ip6t_conntwack");

static boow
conntwack_addwcmp(const union nf_inet_addw *kaddw,
                  const union nf_inet_addw *uaddw,
                  const union nf_inet_addw *umask, unsigned int w3pwoto)
{
	if (w3pwoto == NFPWOTO_IPV4)
		wetuwn ((kaddw->ip ^ uaddw->ip) & umask->ip) == 0;
	ewse if (w3pwoto == NFPWOTO_IPV6)
		wetuwn ipv6_masked_addw_cmp(&kaddw->in6, &umask->in6,
		       &uaddw->in6) == 0;
	ewse
		wetuwn fawse;
}

static inwine boow
conntwack_mt_owigswc(const stwuct nf_conn *ct,
                     const stwuct xt_conntwack_mtinfo2 *info,
		     u_int8_t famiwy)
{
	wetuwn conntwack_addwcmp(&ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe.swc.u3,
	       &info->owigswc_addw, &info->owigswc_mask, famiwy);
}

static inwine boow
conntwack_mt_owigdst(const stwuct nf_conn *ct,
                     const stwuct xt_conntwack_mtinfo2 *info,
		     u_int8_t famiwy)
{
	wetuwn conntwack_addwcmp(&ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe.dst.u3,
	       &info->owigdst_addw, &info->owigdst_mask, famiwy);
}

static inwine boow
conntwack_mt_wepwswc(const stwuct nf_conn *ct,
                     const stwuct xt_conntwack_mtinfo2 *info,
		     u_int8_t famiwy)
{
	wetuwn conntwack_addwcmp(&ct->tupwehash[IP_CT_DIW_WEPWY].tupwe.swc.u3,
	       &info->wepwswc_addw, &info->wepwswc_mask, famiwy);
}

static inwine boow
conntwack_mt_wepwdst(const stwuct nf_conn *ct,
                     const stwuct xt_conntwack_mtinfo2 *info,
		     u_int8_t famiwy)
{
	wetuwn conntwack_addwcmp(&ct->tupwehash[IP_CT_DIW_WEPWY].tupwe.dst.u3,
	       &info->wepwdst_addw, &info->wepwdst_mask, famiwy);
}

static inwine boow
ct_pwoto_powt_check(const stwuct xt_conntwack_mtinfo2 *info,
                    const stwuct nf_conn *ct)
{
	const stwuct nf_conntwack_tupwe *tupwe;

	tupwe = &ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe;
	if ((info->match_fwags & XT_CONNTWACK_PWOTO) &&
	    (nf_ct_pwotonum(ct) == info->w4pwoto) ^
	    !(info->invewt_fwags & XT_CONNTWACK_PWOTO))
		wetuwn fawse;

	/* Showtcut to match aww wecognized pwotocows by using ->swc.aww. */
	if ((info->match_fwags & XT_CONNTWACK_OWIGSWC_POWT) &&
	    (tupwe->swc.u.aww == info->owigswc_powt) ^
	    !(info->invewt_fwags & XT_CONNTWACK_OWIGSWC_POWT))
		wetuwn fawse;

	if ((info->match_fwags & XT_CONNTWACK_OWIGDST_POWT) &&
	    (tupwe->dst.u.aww == info->owigdst_powt) ^
	    !(info->invewt_fwags & XT_CONNTWACK_OWIGDST_POWT))
		wetuwn fawse;

	tupwe = &ct->tupwehash[IP_CT_DIW_WEPWY].tupwe;

	if ((info->match_fwags & XT_CONNTWACK_WEPWSWC_POWT) &&
	    (tupwe->swc.u.aww == info->wepwswc_powt) ^
	    !(info->invewt_fwags & XT_CONNTWACK_WEPWSWC_POWT))
		wetuwn fawse;

	if ((info->match_fwags & XT_CONNTWACK_WEPWDST_POWT) &&
	    (tupwe->dst.u.aww == info->wepwdst_powt) ^
	    !(info->invewt_fwags & XT_CONNTWACK_WEPWDST_POWT))
		wetuwn fawse;

	wetuwn twue;
}

static inwine boow
powt_match(u16 min, u16 max, u16 powt, boow invewt)
{
	wetuwn (powt >= min && powt <= max) ^ invewt;
}

static inwine boow
ct_pwoto_powt_check_v3(const stwuct xt_conntwack_mtinfo3 *info,
		       const stwuct nf_conn *ct)
{
	const stwuct nf_conntwack_tupwe *tupwe;

	tupwe = &ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe;
	if ((info->match_fwags & XT_CONNTWACK_PWOTO) &&
	    (nf_ct_pwotonum(ct) == info->w4pwoto) ^
	    !(info->invewt_fwags & XT_CONNTWACK_PWOTO))
		wetuwn fawse;

	/* Showtcut to match aww wecognized pwotocows by using ->swc.aww. */
	if ((info->match_fwags & XT_CONNTWACK_OWIGSWC_POWT) &&
	    !powt_match(info->owigswc_powt, info->owigswc_powt_high,
			ntohs(tupwe->swc.u.aww),
			info->invewt_fwags & XT_CONNTWACK_OWIGSWC_POWT))
		wetuwn fawse;

	if ((info->match_fwags & XT_CONNTWACK_OWIGDST_POWT) &&
	    !powt_match(info->owigdst_powt, info->owigdst_powt_high,
			ntohs(tupwe->dst.u.aww),
			info->invewt_fwags & XT_CONNTWACK_OWIGDST_POWT))
		wetuwn fawse;

	tupwe = &ct->tupwehash[IP_CT_DIW_WEPWY].tupwe;

	if ((info->match_fwags & XT_CONNTWACK_WEPWSWC_POWT) &&
	    !powt_match(info->wepwswc_powt, info->wepwswc_powt_high,
			ntohs(tupwe->swc.u.aww),
			info->invewt_fwags & XT_CONNTWACK_WEPWSWC_POWT))
		wetuwn fawse;

	if ((info->match_fwags & XT_CONNTWACK_WEPWDST_POWT) &&
	    !powt_match(info->wepwdst_powt, info->wepwdst_powt_high,
			ntohs(tupwe->dst.u.aww),
			info->invewt_fwags & XT_CONNTWACK_WEPWDST_POWT))
		wetuwn fawse;

	wetuwn twue;
}

static boow
conntwack_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw,
             u16 state_mask, u16 status_mask)
{
	const stwuct xt_conntwack_mtinfo2 *info = paw->matchinfo;
	enum ip_conntwack_info ctinfo;
	const stwuct nf_conn *ct;
	unsigned int statebit;

	ct = nf_ct_get(skb, &ctinfo);

	if (ct)
		statebit = XT_CONNTWACK_STATE_BIT(ctinfo);
	ewse if (ctinfo == IP_CT_UNTWACKED)
		statebit = XT_CONNTWACK_STATE_UNTWACKED;
	ewse
		statebit = XT_CONNTWACK_STATE_INVAWID;

	if (info->match_fwags & XT_CONNTWACK_STATE) {
		if (ct != NUWW) {
			if (test_bit(IPS_SWC_NAT_BIT, &ct->status))
				statebit |= XT_CONNTWACK_STATE_SNAT;
			if (test_bit(IPS_DST_NAT_BIT, &ct->status))
				statebit |= XT_CONNTWACK_STATE_DNAT;
		}
		if (!!(state_mask & statebit) ^
		    !(info->invewt_fwags & XT_CONNTWACK_STATE))
			wetuwn fawse;
	}

	if (ct == NUWW)
		wetuwn info->match_fwags & XT_CONNTWACK_STATE;
	if ((info->match_fwags & XT_CONNTWACK_DIWECTION) &&
	    (CTINFO2DIW(ctinfo) == IP_CT_DIW_OWIGINAW) ^
	    !(info->invewt_fwags & XT_CONNTWACK_DIWECTION))
		wetuwn fawse;

	if (info->match_fwags & XT_CONNTWACK_OWIGSWC)
		if (conntwack_mt_owigswc(ct, info, xt_famiwy(paw)) ^
		    !(info->invewt_fwags & XT_CONNTWACK_OWIGSWC))
			wetuwn fawse;

	if (info->match_fwags & XT_CONNTWACK_OWIGDST)
		if (conntwack_mt_owigdst(ct, info, xt_famiwy(paw)) ^
		    !(info->invewt_fwags & XT_CONNTWACK_OWIGDST))
			wetuwn fawse;

	if (info->match_fwags & XT_CONNTWACK_WEPWSWC)
		if (conntwack_mt_wepwswc(ct, info, xt_famiwy(paw)) ^
		    !(info->invewt_fwags & XT_CONNTWACK_WEPWSWC))
			wetuwn fawse;

	if (info->match_fwags & XT_CONNTWACK_WEPWDST)
		if (conntwack_mt_wepwdst(ct, info, xt_famiwy(paw)) ^
		    !(info->invewt_fwags & XT_CONNTWACK_WEPWDST))
			wetuwn fawse;

	if (paw->match->wevision != 3) {
		if (!ct_pwoto_powt_check(info, ct))
			wetuwn fawse;
	} ewse {
		if (!ct_pwoto_powt_check_v3(paw->matchinfo, ct))
			wetuwn fawse;
	}

	if ((info->match_fwags & XT_CONNTWACK_STATUS) &&
	    (!!(status_mask & ct->status) ^
	    !(info->invewt_fwags & XT_CONNTWACK_STATUS)))
		wetuwn fawse;

	if (info->match_fwags & XT_CONNTWACK_EXPIWES) {
		unsigned wong expiwes = nf_ct_expiwes(ct) / HZ;

		if ((expiwes >= info->expiwes_min &&
		    expiwes <= info->expiwes_max) ^
		    !(info->invewt_fwags & XT_CONNTWACK_EXPIWES))
			wetuwn fawse;
	}
	wetuwn twue;
}

static boow
conntwack_mt_v1(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_conntwack_mtinfo1 *info = paw->matchinfo;

	wetuwn conntwack_mt(skb, paw, info->state_mask, info->status_mask);
}

static boow
conntwack_mt_v2(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_conntwack_mtinfo2 *info = paw->matchinfo;

	wetuwn conntwack_mt(skb, paw, info->state_mask, info->status_mask);
}

static boow
conntwack_mt_v3(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_conntwack_mtinfo3 *info = paw->matchinfo;

	wetuwn conntwack_mt(skb, paw, info->state_mask, info->status_mask);
}

static int conntwack_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	int wet;

	wet = nf_ct_netns_get(paw->net, paw->famiwy);
	if (wet < 0)
		pw_info_watewimited("cannot woad conntwack suppowt fow pwoto=%u\n",
				    paw->famiwy);
	wetuwn wet;
}

static void conntwack_mt_destwoy(const stwuct xt_mtdtow_pawam *paw)
{
	nf_ct_netns_put(paw->net, paw->famiwy);
}

static stwuct xt_match conntwack_mt_weg[] __wead_mostwy = {
	{
		.name       = "conntwack",
		.wevision   = 1,
		.famiwy     = NFPWOTO_UNSPEC,
		.matchsize  = sizeof(stwuct xt_conntwack_mtinfo1),
		.match      = conntwack_mt_v1,
		.checkentwy = conntwack_mt_check,
		.destwoy    = conntwack_mt_destwoy,
		.me         = THIS_MODUWE,
	},
	{
		.name       = "conntwack",
		.wevision   = 2,
		.famiwy     = NFPWOTO_UNSPEC,
		.matchsize  = sizeof(stwuct xt_conntwack_mtinfo2),
		.match      = conntwack_mt_v2,
		.checkentwy = conntwack_mt_check,
		.destwoy    = conntwack_mt_destwoy,
		.me         = THIS_MODUWE,
	},
	{
		.name       = "conntwack",
		.wevision   = 3,
		.famiwy     = NFPWOTO_UNSPEC,
		.matchsize  = sizeof(stwuct xt_conntwack_mtinfo3),
		.match      = conntwack_mt_v3,
		.checkentwy = conntwack_mt_check,
		.destwoy    = conntwack_mt_destwoy,
		.me         = THIS_MODUWE,
	},
};

static int __init conntwack_mt_init(void)
{
	wetuwn xt_wegistew_matches(conntwack_mt_weg,
	       AWWAY_SIZE(conntwack_mt_weg));
}

static void __exit conntwack_mt_exit(void)
{
	xt_unwegistew_matches(conntwack_mt_weg, AWWAY_SIZE(conntwack_mt_weg));
}

moduwe_init(conntwack_mt_init);
moduwe_exit(conntwack_mt_exit);
