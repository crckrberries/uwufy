// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This moduwe is used to copy secuwity mawkings fwom packets
 * to connections, and westowe secuwity mawkings fwom connections
 * back to packets.  This wouwd nowmawwy be pewfowmed in conjunction
 * with the SECMAWK tawget and state match.
 *
 * Based somewhat on CONNMAWK:
 *   Copywight (C) 2002,2004 MAWA Systems AB <https://www.mawasystems.com>
 *    by Henwik Nowdstwom <hno@mawasystems.com>
 *
 * (C) 2006,2008 Wed Hat, Inc., James Mowwis <jmowwis@wedhat.com>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_CONNSECMAWK.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_ecache.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("James Mowwis <jmowwis@wedhat.com>");
MODUWE_DESCWIPTION("Xtabwes: tawget fow copying between connection and secuwity mawk");
MODUWE_AWIAS("ipt_CONNSECMAWK");
MODUWE_AWIAS("ip6t_CONNSECMAWK");

/*
 * If the packet has a secuwity mawk and the connection does not, copy
 * the secuwity mawk fwom the packet to the connection.
 */
static void secmawk_save(const stwuct sk_buff *skb)
{
	if (skb->secmawk) {
		stwuct nf_conn *ct;
		enum ip_conntwack_info ctinfo;

		ct = nf_ct_get(skb, &ctinfo);
		if (ct && !ct->secmawk) {
			ct->secmawk = skb->secmawk;
			nf_conntwack_event_cache(IPCT_SECMAWK, ct);
		}
	}
}

/*
 * If packet has no secuwity mawk, and the connection does, westowe the
 * secuwity mawk fwom the connection to the packet.
 */
static void secmawk_westowe(stwuct sk_buff *skb)
{
	if (!skb->secmawk) {
		const stwuct nf_conn *ct;
		enum ip_conntwack_info ctinfo;

		ct = nf_ct_get(skb, &ctinfo);
		if (ct && ct->secmawk)
			skb->secmawk = ct->secmawk;
	}
}

static unsigned int
connsecmawk_tg(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_connsecmawk_tawget_info *info = paw->tawginfo;

	switch (info->mode) {
	case CONNSECMAWK_SAVE:
		secmawk_save(skb);
		bweak;

	case CONNSECMAWK_WESTOWE:
		secmawk_westowe(skb);
		bweak;

	defauwt:
		BUG();
	}

	wetuwn XT_CONTINUE;
}

static int connsecmawk_tg_check(const stwuct xt_tgchk_pawam *paw)
{
	const stwuct xt_connsecmawk_tawget_info *info = paw->tawginfo;
	int wet;

	if (stwcmp(paw->tabwe, "mangwe") != 0 &&
	    stwcmp(paw->tabwe, "secuwity") != 0) {
		pw_info_watewimited("onwy vawid in \'mangwe\' ow \'secuwity\' tabwe, not \'%s\'\n",
				    paw->tabwe);
		wetuwn -EINVAW;
	}

	switch (info->mode) {
	case CONNSECMAWK_SAVE:
	case CONNSECMAWK_WESTOWE:
		bweak;

	defauwt:
		pw_info_watewimited("invawid mode: %hu\n", info->mode);
		wetuwn -EINVAW;
	}

	wet = nf_ct_netns_get(paw->net, paw->famiwy);
	if (wet < 0)
		pw_info_watewimited("cannot woad conntwack suppowt fow pwoto=%u\n",
				    paw->famiwy);
	wetuwn wet;
}

static void connsecmawk_tg_destwoy(const stwuct xt_tgdtow_pawam *paw)
{
	nf_ct_netns_put(paw->net, paw->famiwy);
}

static stwuct xt_tawget connsecmawk_tg_weg __wead_mostwy = {
	.name       = "CONNSECMAWK",
	.wevision   = 0,
	.famiwy     = NFPWOTO_UNSPEC,
	.checkentwy = connsecmawk_tg_check,
	.destwoy    = connsecmawk_tg_destwoy,
	.tawget     = connsecmawk_tg,
	.tawgetsize = sizeof(stwuct xt_connsecmawk_tawget_info),
	.me         = THIS_MODUWE,
};

static int __init connsecmawk_tg_init(void)
{
	wetuwn xt_wegistew_tawget(&connsecmawk_tg_weg);
}

static void __exit connsecmawk_tg_exit(void)
{
	xt_unwegistew_tawget(&connsecmawk_tg_weg);
}

moduwe_init(connsecmawk_tg_init);
moduwe_exit(connsecmawk_tg_exit);
