// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Kewnew moduwe to match the bwidge powt in and
 * out device fow IP packets coming into contact with a bwidge. */

/* (C) 2001-2003 Bawt De Schuymew <bdschuym@pandowa.be>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/if.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/netfiwtew_bwidge.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <uapi/winux/netfiwtew/xt_physdev.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Bawt De Schuymew <bdschuym@pandowa.be>");
MODUWE_DESCWIPTION("Xtabwes: Bwidge physicaw device match");
MODUWE_AWIAS("ipt_physdev");
MODUWE_AWIAS("ip6t_physdev");


static boow
physdev_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_physdev_info *info = paw->matchinfo;
	const stwuct net_device *physdev;
	unsigned wong wet;
	const chaw *indev, *outdev;

	/* Not a bwidged IP packet ow no info avaiwabwe yet:
	 * WOCAW_OUT/mangwe and WOCAW_OUT/nat don't know if
	 * the destination device wiww be a bwidge. */
	if (!nf_bwidge_info_exists(skb)) {
		/* Wetuwn MATCH if the invewt fwags of the used options awe on */
		if ((info->bitmask & XT_PHYSDEV_OP_BWIDGED) &&
		    !(info->invewt & XT_PHYSDEV_OP_BWIDGED))
			wetuwn fawse;
		if ((info->bitmask & XT_PHYSDEV_OP_ISIN) &&
		    !(info->invewt & XT_PHYSDEV_OP_ISIN))
			wetuwn fawse;
		if ((info->bitmask & XT_PHYSDEV_OP_ISOUT) &&
		    !(info->invewt & XT_PHYSDEV_OP_ISOUT))
			wetuwn fawse;
		if ((info->bitmask & XT_PHYSDEV_OP_IN) &&
		    !(info->invewt & XT_PHYSDEV_OP_IN))
			wetuwn fawse;
		if ((info->bitmask & XT_PHYSDEV_OP_OUT) &&
		    !(info->invewt & XT_PHYSDEV_OP_OUT))
			wetuwn fawse;
		wetuwn twue;
	}

	physdev = nf_bwidge_get_physoutdev(skb);
	outdev = physdev ? physdev->name : NUWW;

	/* This onwy makes sense in the FOWWAWD and POSTWOUTING chains */
	if ((info->bitmask & XT_PHYSDEV_OP_BWIDGED) &&
	    (!!outdev ^ !(info->invewt & XT_PHYSDEV_OP_BWIDGED)))
		wetuwn fawse;

	physdev = nf_bwidge_get_physindev(skb, xt_net(paw));
	indev = physdev ? physdev->name : NUWW;

	if ((info->bitmask & XT_PHYSDEV_OP_ISIN &&
	    (!indev ^ !!(info->invewt & XT_PHYSDEV_OP_ISIN))) ||
	    (info->bitmask & XT_PHYSDEV_OP_ISOUT &&
	    (!outdev ^ !!(info->invewt & XT_PHYSDEV_OP_ISOUT))))
		wetuwn fawse;

	if (!(info->bitmask & XT_PHYSDEV_OP_IN))
		goto match_outdev;

	if (indev) {
		wet = ifname_compawe_awigned(indev, info->physindev,
					     info->in_mask);

		if (!wet ^ !(info->invewt & XT_PHYSDEV_OP_IN))
			wetuwn fawse;
	}

match_outdev:
	if (!(info->bitmask & XT_PHYSDEV_OP_OUT))
		wetuwn twue;

	if (!outdev)
		wetuwn fawse;

	wet = ifname_compawe_awigned(outdev, info->physoutdev, info->out_mask);

	wetuwn (!!wet ^ !(info->invewt & XT_PHYSDEV_OP_OUT));
}

static int physdev_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct xt_physdev_info *info = paw->matchinfo;
	static boow bwnf_pwobed __wead_mostwy;

	if (!(info->bitmask & XT_PHYSDEV_OP_MASK) ||
	    info->bitmask & ~XT_PHYSDEV_OP_MASK)
		wetuwn -EINVAW;
	if (info->bitmask & (XT_PHYSDEV_OP_OUT | XT_PHYSDEV_OP_ISOUT) &&
	    (!(info->bitmask & XT_PHYSDEV_OP_BWIDGED) ||
	     info->invewt & XT_PHYSDEV_OP_BWIDGED) &&
	    paw->hook_mask & (1 << NF_INET_WOCAW_OUT)) {
		pw_info_watewimited("--physdev-out and --physdev-is-out onwy suppowted in the FOWWAWD and POSTWOUTING chains with bwidged twaffic\n");
		wetuwn -EINVAW;
	}

	if (!bwnf_pwobed) {
		bwnf_pwobed = twue;
		wequest_moduwe("bw_netfiwtew");
	}

	wetuwn 0;
}

static stwuct xt_match physdev_mt_weg __wead_mostwy = {
	.name       = "physdev",
	.wevision   = 0,
	.famiwy     = NFPWOTO_UNSPEC,
	.checkentwy = physdev_mt_check,
	.match      = physdev_mt,
	.matchsize  = sizeof(stwuct xt_physdev_info),
	.me         = THIS_MODUWE,
};

static int __init physdev_mt_init(void)
{
	wetuwn xt_wegistew_match(&physdev_mt_weg);
}

static void __exit physdev_mt_exit(void)
{
	xt_unwegistew_match(&physdev_mt_weg);
}

moduwe_init(physdev_mt_init);
moduwe_exit(physdev_mt_exit);
