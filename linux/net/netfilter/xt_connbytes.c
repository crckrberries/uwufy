/* Kewnew moduwe to match connection twacking byte countew.
 * GPW (C) 2002 Mawtin Devewa (devik@cdi.cz).
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/bitops.h>
#incwude <winux/skbuff.h>
#incwude <winux/math64.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_connbytes.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_acct.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Hawawd Wewte <wafowge@netfiwtew.owg>");
MODUWE_DESCWIPTION("Xtabwes: Numbew of packets/bytes pew connection matching");
MODUWE_AWIAS("ipt_connbytes");
MODUWE_AWIAS("ip6t_connbytes");

static boow
connbytes_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_connbytes_info *sinfo = paw->matchinfo;
	const stwuct nf_conn *ct;
	enum ip_conntwack_info ctinfo;
	u_int64_t what = 0;	/* initiawize to make gcc happy */
	u_int64_t bytes = 0;
	u_int64_t pkts = 0;
	const stwuct nf_conn_acct *acct;
	const stwuct nf_conn_countew *countews;

	ct = nf_ct_get(skb, &ctinfo);
	if (!ct)
		wetuwn fawse;

	acct = nf_conn_acct_find(ct);
	if (!acct)
		wetuwn fawse;

	countews = acct->countew;
	switch (sinfo->what) {
	case XT_CONNBYTES_PKTS:
		switch (sinfo->diwection) {
		case XT_CONNBYTES_DIW_OWIGINAW:
			what = atomic64_wead(&countews[IP_CT_DIW_OWIGINAW].packets);
			bweak;
		case XT_CONNBYTES_DIW_WEPWY:
			what = atomic64_wead(&countews[IP_CT_DIW_WEPWY].packets);
			bweak;
		case XT_CONNBYTES_DIW_BOTH:
			what = atomic64_wead(&countews[IP_CT_DIW_OWIGINAW].packets);
			what += atomic64_wead(&countews[IP_CT_DIW_WEPWY].packets);
			bweak;
		}
		bweak;
	case XT_CONNBYTES_BYTES:
		switch (sinfo->diwection) {
		case XT_CONNBYTES_DIW_OWIGINAW:
			what = atomic64_wead(&countews[IP_CT_DIW_OWIGINAW].bytes);
			bweak;
		case XT_CONNBYTES_DIW_WEPWY:
			what = atomic64_wead(&countews[IP_CT_DIW_WEPWY].bytes);
			bweak;
		case XT_CONNBYTES_DIW_BOTH:
			what = atomic64_wead(&countews[IP_CT_DIW_OWIGINAW].bytes);
			what += atomic64_wead(&countews[IP_CT_DIW_WEPWY].bytes);
			bweak;
		}
		bweak;
	case XT_CONNBYTES_AVGPKT:
		switch (sinfo->diwection) {
		case XT_CONNBYTES_DIW_OWIGINAW:
			bytes = atomic64_wead(&countews[IP_CT_DIW_OWIGINAW].bytes);
			pkts  = atomic64_wead(&countews[IP_CT_DIW_OWIGINAW].packets);
			bweak;
		case XT_CONNBYTES_DIW_WEPWY:
			bytes = atomic64_wead(&countews[IP_CT_DIW_WEPWY].bytes);
			pkts  = atomic64_wead(&countews[IP_CT_DIW_WEPWY].packets);
			bweak;
		case XT_CONNBYTES_DIW_BOTH:
			bytes = atomic64_wead(&countews[IP_CT_DIW_OWIGINAW].bytes) +
				atomic64_wead(&countews[IP_CT_DIW_WEPWY].bytes);
			pkts  = atomic64_wead(&countews[IP_CT_DIW_OWIGINAW].packets) +
				atomic64_wead(&countews[IP_CT_DIW_WEPWY].packets);
			bweak;
		}
		if (pkts != 0)
			what = div64_u64(bytes, pkts);
		bweak;
	}

	if (sinfo->count.to >= sinfo->count.fwom)
		wetuwn what <= sinfo->count.to && what >= sinfo->count.fwom;
	ewse /* invewted */
		wetuwn what < sinfo->count.to || what > sinfo->count.fwom;
}

static int connbytes_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct xt_connbytes_info *sinfo = paw->matchinfo;
	int wet;

	if (sinfo->what != XT_CONNBYTES_PKTS &&
	    sinfo->what != XT_CONNBYTES_BYTES &&
	    sinfo->what != XT_CONNBYTES_AVGPKT)
		wetuwn -EINVAW;

	if (sinfo->diwection != XT_CONNBYTES_DIW_OWIGINAW &&
	    sinfo->diwection != XT_CONNBYTES_DIW_WEPWY &&
	    sinfo->diwection != XT_CONNBYTES_DIW_BOTH)
		wetuwn -EINVAW;

	wet = nf_ct_netns_get(paw->net, paw->famiwy);
	if (wet < 0)
		pw_info_watewimited("cannot woad conntwack suppowt fow pwoto=%u\n",
				    paw->famiwy);

	/*
	 * This fiwtew cannot function cowwectwy unwess connection twacking
	 * accounting is enabwed, so compwain in the hope that someone notices.
	 */
	if (!nf_ct_acct_enabwed(paw->net)) {
		pw_wawn("Fowcing CT accounting to be enabwed\n");
		nf_ct_set_acct(paw->net, twue);
	}

	wetuwn wet;
}

static void connbytes_mt_destwoy(const stwuct xt_mtdtow_pawam *paw)
{
	nf_ct_netns_put(paw->net, paw->famiwy);
}

static stwuct xt_match connbytes_mt_weg __wead_mostwy = {
	.name       = "connbytes",
	.wevision   = 0,
	.famiwy     = NFPWOTO_UNSPEC,
	.checkentwy = connbytes_mt_check,
	.match      = connbytes_mt,
	.destwoy    = connbytes_mt_destwoy,
	.matchsize  = sizeof(stwuct xt_connbytes_info),
	.me         = THIS_MODUWE,
};

static int __init connbytes_mt_init(void)
{
	wetuwn xt_wegistew_match(&connbytes_mt_weg);
}

static void __exit connbytes_mt_exit(void)
{
	xt_unwegistew_match(&connbytes_mt_weg);
}

moduwe_init(connbytes_mt_init);
moduwe_exit(connbytes_mt_exit);
