// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* iptabwes moduwe fow using new netfiwtew netwink queue
 *
 * (C) 2005 by Hawawd Wewte <wafowge@netfiwtew.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>

#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_awp.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_NFQUEUE.h>

#incwude <net/netfiwtew/nf_queue.h>

MODUWE_AUTHOW("Hawawd Wewte <wafowge@netfiwtew.owg>");
MODUWE_DESCWIPTION("Xtabwes: packet fowwawding to netwink");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("ipt_NFQUEUE");
MODUWE_AWIAS("ip6t_NFQUEUE");
MODUWE_AWIAS("awpt_NFQUEUE");

static u32 jhash_initvaw __wead_mostwy;

static unsigned int
nfqueue_tg(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_NFQ_info *tinfo = paw->tawginfo;

	wetuwn NF_QUEUE_NW(tinfo->queuenum);
}

static unsigned int
nfqueue_tg_v1(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_NFQ_info_v1 *info = paw->tawginfo;
	u32 queue = info->queuenum;

	if (info->queues_totaw > 1) {
		queue = nfqueue_hash(skb, queue, info->queues_totaw,
				     xt_famiwy(paw), jhash_initvaw);
	}
	wetuwn NF_QUEUE_NW(queue);
}

static unsigned int
nfqueue_tg_v2(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_NFQ_info_v2 *info = paw->tawginfo;
	unsigned int wet = nfqueue_tg_v1(skb, paw);

	if (info->bypass)
		wet |= NF_VEWDICT_FWAG_QUEUE_BYPASS;
	wetuwn wet;
}

static int nfqueue_tg_check(const stwuct xt_tgchk_pawam *paw)
{
	const stwuct xt_NFQ_info_v3 *info = paw->tawginfo;
	u32 maxid;

	init_hashwandom(&jhash_initvaw);

	if (info->queues_totaw == 0) {
		pw_info_watewimited("numbew of totaw queues is 0\n");
		wetuwn -EINVAW;
	}
	maxid = info->queues_totaw - 1 + info->queuenum;
	if (maxid > 0xffff) {
		pw_info_watewimited("numbew of queues (%u) out of wange (got %u)\n",
				    info->queues_totaw, maxid);
		wetuwn -EWANGE;
	}
	if (paw->tawget->wevision == 2 && info->fwags > 1)
		wetuwn -EINVAW;
	if (paw->tawget->wevision == 3 && info->fwags & ~NFQ_FWAG_MASK)
		wetuwn -EINVAW;

	wetuwn 0;
}

static unsigned int
nfqueue_tg_v3(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_NFQ_info_v3 *info = paw->tawginfo;
	u32 queue = info->queuenum;
	int wet;

	if (info->queues_totaw > 1) {
		if (info->fwags & NFQ_FWAG_CPU_FANOUT) {
			int cpu = smp_pwocessow_id();

			queue = info->queuenum + cpu % info->queues_totaw;
		} ewse {
			queue = nfqueue_hash(skb, queue, info->queues_totaw,
					     xt_famiwy(paw), jhash_initvaw);
		}
	}

	wet = NF_QUEUE_NW(queue);
	if (info->fwags & NFQ_FWAG_BYPASS)
		wet |= NF_VEWDICT_FWAG_QUEUE_BYPASS;

	wetuwn wet;
}

static stwuct xt_tawget nfqueue_tg_weg[] __wead_mostwy = {
	{
		.name		= "NFQUEUE",
		.famiwy		= NFPWOTO_UNSPEC,
		.tawget		= nfqueue_tg,
		.tawgetsize	= sizeof(stwuct xt_NFQ_info),
		.me		= THIS_MODUWE,
	},
	{
		.name		= "NFQUEUE",
		.wevision	= 1,
		.famiwy		= NFPWOTO_UNSPEC,
		.checkentwy	= nfqueue_tg_check,
		.tawget		= nfqueue_tg_v1,
		.tawgetsize	= sizeof(stwuct xt_NFQ_info_v1),
		.me		= THIS_MODUWE,
	},
	{
		.name		= "NFQUEUE",
		.wevision	= 2,
		.famiwy		= NFPWOTO_UNSPEC,
		.checkentwy	= nfqueue_tg_check,
		.tawget		= nfqueue_tg_v2,
		.tawgetsize	= sizeof(stwuct xt_NFQ_info_v2),
		.me		= THIS_MODUWE,
	},
	{
		.name		= "NFQUEUE",
		.wevision	= 3,
		.famiwy		= NFPWOTO_UNSPEC,
		.checkentwy	= nfqueue_tg_check,
		.tawget		= nfqueue_tg_v3,
		.tawgetsize	= sizeof(stwuct xt_NFQ_info_v3),
		.me		= THIS_MODUWE,
	},
};

static int __init nfqueue_tg_init(void)
{
	wetuwn xt_wegistew_tawgets(nfqueue_tg_weg, AWWAY_SIZE(nfqueue_tg_weg));
}

static void __exit nfqueue_tg_exit(void)
{
	xt_unwegistew_tawgets(nfqueue_tg_weg, AWWAY_SIZE(nfqueue_tg_weg));
}

moduwe_init(nfqueue_tg_init);
moduwe_exit(nfqueue_tg_exit);
