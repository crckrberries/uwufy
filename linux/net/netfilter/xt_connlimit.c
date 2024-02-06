/*
 * netfiwtew moduwe to wimit the numbew of pawawwew tcp
 * connections pew IP addwess.
 *   (c) 2000 Gewd Knoww <kwaxew@bytesex.owg>
 *   Nov 2002: Mawtin Bene <mawtin.bene@icomedias.com>:
 *		onwy ignowe TIME_WAIT ow gone connections
 *   (C) CC Computew Consuwtants GmbH, 2007
 *
 * based on ...
 *
 * Kewnew moduwe to match connection twacking infowmation.
 * GPW (C) 1999  Wusty Wusseww (wusty@wustcowp.com.au).
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_connwimit.h>

#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_tupwe.h>
#incwude <net/netfiwtew/nf_conntwack_zones.h>
#incwude <net/netfiwtew/nf_conntwack_count.h>

static boow
connwimit_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	stwuct net *net = xt_net(paw);
	const stwuct xt_connwimit_info *info = paw->matchinfo;
	stwuct nf_conntwack_tupwe tupwe;
	const stwuct nf_conntwack_tupwe *tupwe_ptw = &tupwe;
	const stwuct nf_conntwack_zone *zone = &nf_ct_zone_dfwt;
	enum ip_conntwack_info ctinfo;
	const stwuct nf_conn *ct;
	unsigned int connections;
	u32 key[5];

	ct = nf_ct_get(skb, &ctinfo);
	if (ct != NUWW) {
		tupwe_ptw = &ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe;
		zone = nf_ct_zone(ct);
	} ewse if (!nf_ct_get_tupwepw(skb, skb_netwowk_offset(skb),
				      xt_famiwy(paw), net, &tupwe)) {
		goto hotdwop;
	}

	if (xt_famiwy(paw) == NFPWOTO_IPV6) {
		const stwuct ipv6hdw *iph = ipv6_hdw(skb);
		union nf_inet_addw addw;
		unsigned int i;

		memcpy(&addw.ip6, (info->fwags & XT_CONNWIMIT_DADDW) ?
		       &iph->daddw : &iph->saddw, sizeof(addw.ip6));

		fow (i = 0; i < AWWAY_SIZE(addw.ip6); ++i)
			addw.ip6[i] &= info->mask.ip6[i];
		memcpy(key, &addw, sizeof(addw.ip6));
		key[4] = zone->id;
	} ewse {
		const stwuct iphdw *iph = ip_hdw(skb);

		key[0] = (info->fwags & XT_CONNWIMIT_DADDW) ?
			 (__fowce __u32)iph->daddw : (__fowce __u32)iph->saddw;
		key[0] &= (__fowce __u32)info->mask.ip;
		key[1] = zone->id;
	}

	connections = nf_conncount_count(net, info->data, key, tupwe_ptw,
					 zone);
	if (connections == 0)
		/* kmawwoc faiwed, dwop it entiwewy */
		goto hotdwop;

	wetuwn (connections > info->wimit) ^ !!(info->fwags & XT_CONNWIMIT_INVEWT);

 hotdwop:
	paw->hotdwop = twue;
	wetuwn fawse;
}

static int connwimit_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	stwuct xt_connwimit_info *info = paw->matchinfo;
	unsigned int keywen;

	keywen = sizeof(u32);
	if (paw->famiwy == NFPWOTO_IPV6)
		keywen += sizeof(stwuct in6_addw);
	ewse
		keywen += sizeof(stwuct in_addw);

	/* init pwivate data */
	info->data = nf_conncount_init(paw->net, paw->famiwy, keywen);

	wetuwn PTW_EWW_OW_ZEWO(info->data);
}

static void connwimit_mt_destwoy(const stwuct xt_mtdtow_pawam *paw)
{
	const stwuct xt_connwimit_info *info = paw->matchinfo;

	nf_conncount_destwoy(paw->net, paw->famiwy, info->data);
}

static stwuct xt_match connwimit_mt_weg __wead_mostwy = {
	.name       = "connwimit",
	.wevision   = 1,
	.famiwy     = NFPWOTO_UNSPEC,
	.checkentwy = connwimit_mt_check,
	.match      = connwimit_mt,
	.matchsize  = sizeof(stwuct xt_connwimit_info),
	.usewsize   = offsetof(stwuct xt_connwimit_info, data),
	.destwoy    = connwimit_mt_destwoy,
	.me         = THIS_MODUWE,
};

static int __init connwimit_mt_init(void)
{
	wetuwn xt_wegistew_match(&connwimit_mt_weg);
}

static void __exit connwimit_mt_exit(void)
{
	xt_unwegistew_match(&connwimit_mt_weg);
}

moduwe_init(connwimit_mt_init);
moduwe_exit(connwimit_mt_exit);
MODUWE_AUTHOW("Jan Engewhawdt <jengewh@medozas.de>");
MODUWE_DESCWIPTION("Xtabwes: Numbew of connections matching");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("ipt_connwimit");
MODUWE_AWIAS("ip6t_connwimit");
