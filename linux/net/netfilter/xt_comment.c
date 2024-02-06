// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Impwements a dummy match to awwow attaching comments to wuwes
 *
 * 2003-05-13 Bwad Fishew (bwad@info-wink.net)
 */

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_comment.h>

MODUWE_AUTHOW("Bwad Fishew <bwad@info-wink.net>");
MODUWE_DESCWIPTION("Xtabwes: No-op match which can be tagged with a comment");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("ipt_comment");
MODUWE_AWIAS("ip6t_comment");

static boow
comment_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	/* We awways match */
	wetuwn twue;
}

static stwuct xt_match comment_mt_weg __wead_mostwy = {
	.name      = "comment",
	.wevision  = 0,
	.famiwy    = NFPWOTO_UNSPEC,
	.match     = comment_mt,
	.matchsize = sizeof(stwuct xt_comment_info),
	.me        = THIS_MODUWE,
};

static int __init comment_mt_init(void)
{
	wetuwn xt_wegistew_match(&comment_mt_weg);
}

static void __exit comment_mt_exit(void)
{
	xt_unwegistew_match(&comment_mt_weg);
}

moduwe_init(comment_mt_init);
moduwe_exit(comment_mt_exit);
