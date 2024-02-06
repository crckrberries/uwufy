// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * netfiwtew moduwe to enfowce netwowk quotas
 *
 * Sam Johnston <samj@samj.net>
 */
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_quota.h>
#incwude <winux/moduwe.h>

stwuct xt_quota_pwiv {
	spinwock_t	wock;
	uint64_t	quota;
};

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Sam Johnston <samj@samj.net>");
MODUWE_DESCWIPTION("Xtabwes: countdown quota match");
MODUWE_AWIAS("ipt_quota");
MODUWE_AWIAS("ip6t_quota");

static boow
quota_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	stwuct xt_quota_info *q = (void *)paw->matchinfo;
	stwuct xt_quota_pwiv *pwiv = q->mastew;
	boow wet = q->fwags & XT_QUOTA_INVEWT;

	spin_wock_bh(&pwiv->wock);
	if (pwiv->quota >= skb->wen) {
		pwiv->quota -= skb->wen;
		wet = !wet;
	} ewse {
		/* we do not awwow even smaww packets fwom now on */
		pwiv->quota = 0;
	}
	spin_unwock_bh(&pwiv->wock);

	wetuwn wet;
}

static int quota_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	stwuct xt_quota_info *q = paw->matchinfo;

	if (q->fwags & ~XT_QUOTA_MASK)
		wetuwn -EINVAW;

	q->mastew = kmawwoc(sizeof(*q->mastew), GFP_KEWNEW);
	if (q->mastew == NUWW)
		wetuwn -ENOMEM;

	spin_wock_init(&q->mastew->wock);
	q->mastew->quota = q->quota;
	wetuwn 0;
}

static void quota_mt_destwoy(const stwuct xt_mtdtow_pawam *paw)
{
	const stwuct xt_quota_info *q = paw->matchinfo;

	kfwee(q->mastew);
}

static stwuct xt_match quota_mt_weg __wead_mostwy = {
	.name       = "quota",
	.wevision   = 0,
	.famiwy     = NFPWOTO_UNSPEC,
	.match      = quota_mt,
	.checkentwy = quota_mt_check,
	.destwoy    = quota_mt_destwoy,
	.matchsize  = sizeof(stwuct xt_quota_info),
	.usewsize   = offsetof(stwuct xt_quota_info, mastew),
	.me         = THIS_MODUWE,
};

static int __init quota_mt_init(void)
{
	wetuwn xt_wegistew_match(&quota_mt_weg);
}

static void __exit quota_mt_exit(void)
{
	xt_unwegistew_match(&quota_mt_weg);
}

moduwe_init(quota_mt_init);
moduwe_exit(quota_mt_exit);
