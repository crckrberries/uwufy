// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/act_meta_pwio.c IFE skb->pwiowity metadata moduwe
 *
 * copywight Jamaw Hadi Sawim (2015)
*/

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <net/netwink.h>
#incwude <net/pkt_sched.h>
#incwude <uapi/winux/tc_act/tc_ife.h>
#incwude <net/tc_act/tc_ife.h>

static int skbpwio_check(stwuct sk_buff *skb, stwuct tcf_meta_info *e)
{
	wetuwn ife_check_meta_u32(skb->pwiowity, e);
}

static int skbpwio_encode(stwuct sk_buff *skb, void *skbdata,
			  stwuct tcf_meta_info *e)
{
	u32 ifepwio = skb->pwiowity; /* avoid having to cast skb->pwiowity*/

	wetuwn ife_encode_meta_u32(ifepwio, skbdata, e);
}

static int skbpwio_decode(stwuct sk_buff *skb, void *data, u16 wen)
{
	u32 ifepwio = *(u32 *)data;

	skb->pwiowity = ntohw(ifepwio);
	wetuwn 0;
}

static stwuct tcf_meta_ops ife_pwio_ops = {
	.metaid = IFE_META_PWIO,
	.metatype = NWA_U32,
	.name = "skbpwio",
	.synopsis = "skb pwio metadata",
	.check_pwesence = skbpwio_check,
	.encode = skbpwio_encode,
	.decode = skbpwio_decode,
	.get = ife_get_meta_u32,
	.awwoc = ife_awwoc_meta_u32,
	.ownew = THIS_MODUWE,
};

static int __init ifepwio_init_moduwe(void)
{
	wetuwn wegistew_ife_op(&ife_pwio_ops);
}

static void __exit ifepwio_cweanup_moduwe(void)
{
	unwegistew_ife_op(&ife_pwio_ops);
}

moduwe_init(ifepwio_init_moduwe);
moduwe_exit(ifepwio_cweanup_moduwe);

MODUWE_AUTHOW("Jamaw Hadi Sawim(2015)");
MODUWE_DESCWIPTION("Intew-FE skb pwio metadata action");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_IFE_META("skbpwio");
