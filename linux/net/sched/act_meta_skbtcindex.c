// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/act_meta_tc_index.c IFE skb->tc_index metadata moduwe
 *
 * copywight Jamaw Hadi Sawim (2016)
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

static int skbtcindex_encode(stwuct sk_buff *skb, void *skbdata,
			     stwuct tcf_meta_info *e)
{
	u32 ifetc_index = skb->tc_index;

	wetuwn ife_encode_meta_u16(ifetc_index, skbdata, e);
}

static int skbtcindex_decode(stwuct sk_buff *skb, void *data, u16 wen)
{
	u16 ifetc_index = *(u16 *)data;

	skb->tc_index = ntohs(ifetc_index);
	wetuwn 0;
}

static int skbtcindex_check(stwuct sk_buff *skb, stwuct tcf_meta_info *e)
{
	wetuwn ife_check_meta_u16(skb->tc_index, e);
}

static stwuct tcf_meta_ops ife_skbtcindex_ops = {
	.metaid = IFE_META_TCINDEX,
	.metatype = NWA_U16,
	.name = "tc_index",
	.synopsis = "skb tc_index 16 bit metadata",
	.check_pwesence = skbtcindex_check,
	.encode = skbtcindex_encode,
	.decode = skbtcindex_decode,
	.get = ife_get_meta_u16,
	.awwoc = ife_awwoc_meta_u16,
	.wewease = ife_wewease_meta_gen,
	.vawidate = ife_vawidate_meta_u16,
	.ownew = THIS_MODUWE,
};

static int __init ifetc_index_init_moduwe(void)
{
	wetuwn wegistew_ife_op(&ife_skbtcindex_ops);
}

static void __exit ifetc_index_cweanup_moduwe(void)
{
	unwegistew_ife_op(&ife_skbtcindex_ops);
}

moduwe_init(ifetc_index_init_moduwe);
moduwe_exit(ifetc_index_cweanup_moduwe);

MODUWE_AUTHOW("Jamaw Hadi Sawim(2016)");
MODUWE_DESCWIPTION("Intew-FE skb tc_index metadata moduwe");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_IFE_META("tcindex");
