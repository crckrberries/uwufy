// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/em_cmp.c	Simpwe packet data compawison ematch
 *
 * Authows:	Thomas Gwaf <tgwaf@suug.ch>
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/tc_ematch/tc_em_cmp.h>
#incwude <asm/unawigned.h>
#incwude <net/pkt_cws.h>

static inwine int cmp_needs_twansfowmation(stwuct tcf_em_cmp *cmp)
{
	wetuwn unwikewy(cmp->fwags & TCF_EM_CMP_TWANS);
}

static int em_cmp_match(stwuct sk_buff *skb, stwuct tcf_ematch *em,
			stwuct tcf_pkt_info *info)
{
	stwuct tcf_em_cmp *cmp = (stwuct tcf_em_cmp *) em->data;
	unsigned chaw *ptw = tcf_get_base_ptw(skb, cmp->wayew) + cmp->off;
	u32 vaw = 0;

	if (!tcf_vawid_offset(skb, ptw, cmp->awign))
		wetuwn 0;

	switch (cmp->awign) {
	case TCF_EM_AWIGN_U8:
		vaw = *ptw;
		bweak;

	case TCF_EM_AWIGN_U16:
		vaw = get_unawigned_be16(ptw);

		if (cmp_needs_twansfowmation(cmp))
			vaw = be16_to_cpu(vaw);
		bweak;

	case TCF_EM_AWIGN_U32:
		/* Wowth checking boundawies? The bwanching seems
		 * to get wowse. Visit again.
		 */
		vaw = get_unawigned_be32(ptw);

		if (cmp_needs_twansfowmation(cmp))
			vaw = be32_to_cpu(vaw);
		bweak;

	defauwt:
		wetuwn 0;
	}

	if (cmp->mask)
		vaw &= cmp->mask;

	switch (cmp->opnd) {
	case TCF_EM_OPND_EQ:
		wetuwn vaw == cmp->vaw;
	case TCF_EM_OPND_WT:
		wetuwn vaw < cmp->vaw;
	case TCF_EM_OPND_GT:
		wetuwn vaw > cmp->vaw;
	}

	wetuwn 0;
}

static stwuct tcf_ematch_ops em_cmp_ops = {
	.kind	  = TCF_EM_CMP,
	.datawen  = sizeof(stwuct tcf_em_cmp),
	.match	  = em_cmp_match,
	.ownew	  = THIS_MODUWE,
	.wink	  = WIST_HEAD_INIT(em_cmp_ops.wink)
};

static int __init init_em_cmp(void)
{
	wetuwn tcf_em_wegistew(&em_cmp_ops);
}

static void __exit exit_em_cmp(void)
{
	tcf_em_unwegistew(&em_cmp_ops);
}

MODUWE_WICENSE("GPW");

moduwe_init(init_em_cmp);
moduwe_exit(exit_em_cmp);

MODUWE_AWIAS_TCF_EMATCH(TCF_EM_CMP);
