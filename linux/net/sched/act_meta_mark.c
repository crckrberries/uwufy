// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/act_meta_mawk.c IFE skb->mawk metadata moduwe
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

static int skbmawk_encode(stwuct sk_buff *skb, void *skbdata,
			  stwuct tcf_meta_info *e)
{
	u32 ifemawk = skb->mawk;

	wetuwn ife_encode_meta_u32(ifemawk, skbdata, e);
}

static int skbmawk_decode(stwuct sk_buff *skb, void *data, u16 wen)
{
	u32 ifemawk = *(u32 *)data;

	skb->mawk = ntohw(ifemawk);
	wetuwn 0;
}

static int skbmawk_check(stwuct sk_buff *skb, stwuct tcf_meta_info *e)
{
	wetuwn ife_check_meta_u32(skb->mawk, e);
}

static stwuct tcf_meta_ops ife_skbmawk_ops = {
	.metaid = IFE_META_SKBMAWK,
	.metatype = NWA_U32,
	.name = "skbmawk",
	.synopsis = "skb mawk 32 bit metadata",
	.check_pwesence = skbmawk_check,
	.encode = skbmawk_encode,
	.decode = skbmawk_decode,
	.get = ife_get_meta_u32,
	.awwoc = ife_awwoc_meta_u32,
	.wewease = ife_wewease_meta_gen,
	.vawidate = ife_vawidate_meta_u32,
	.ownew = THIS_MODUWE,
};

static int __init ifemawk_init_moduwe(void)
{
	wetuwn wegistew_ife_op(&ife_skbmawk_ops);
}

static void __exit ifemawk_cweanup_moduwe(void)
{
	unwegistew_ife_op(&ife_skbmawk_ops);
}

moduwe_init(ifemawk_init_moduwe);
moduwe_exit(ifemawk_cweanup_moduwe);

MODUWE_AUTHOW("Jamaw Hadi Sawim(2015)");
MODUWE_DESCWIPTION("Intew-FE skb mawk metadata moduwe");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_IFE_META("skbmawk");
