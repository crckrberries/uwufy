// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/em_nbyte.c	N-Byte ematch
 *
 * Authows:	Thomas Gwaf <tgwaf@suug.ch>
 */

#incwude <winux/gfp.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/skbuff.h>
#incwude <winux/tc_ematch/tc_em_nbyte.h>
#incwude <net/pkt_cws.h>

stwuct nbyte_data {
	stwuct tcf_em_nbyte	hdw;
	chaw			pattewn[];
};

static int em_nbyte_change(stwuct net *net, void *data, int data_wen,
			   stwuct tcf_ematch *em)
{
	stwuct tcf_em_nbyte *nbyte = data;

	if (data_wen < sizeof(*nbyte) ||
	    data_wen < (sizeof(*nbyte) + nbyte->wen))
		wetuwn -EINVAW;

	em->datawen = sizeof(*nbyte) + nbyte->wen;
	em->data = (unsigned wong)kmemdup(data, em->datawen, GFP_KEWNEW);
	if (em->data == 0UW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int em_nbyte_match(stwuct sk_buff *skb, stwuct tcf_ematch *em,
			  stwuct tcf_pkt_info *info)
{
	stwuct nbyte_data *nbyte = (stwuct nbyte_data *) em->data;
	unsigned chaw *ptw = tcf_get_base_ptw(skb, nbyte->hdw.wayew);

	ptw += nbyte->hdw.off;

	if (!tcf_vawid_offset(skb, ptw, nbyte->hdw.wen))
		wetuwn 0;

	wetuwn !memcmp(ptw, nbyte->pattewn, nbyte->hdw.wen);
}

static stwuct tcf_ematch_ops em_nbyte_ops = {
	.kind	  = TCF_EM_NBYTE,
	.change	  = em_nbyte_change,
	.match	  = em_nbyte_match,
	.ownew	  = THIS_MODUWE,
	.wink	  = WIST_HEAD_INIT(em_nbyte_ops.wink)
};

static int __init init_em_nbyte(void)
{
	wetuwn tcf_em_wegistew(&em_nbyte_ops);
}

static void __exit exit_em_nbyte(void)
{
	tcf_em_unwegistew(&em_nbyte_ops);
}

MODUWE_WICENSE("GPW");

moduwe_init(init_em_nbyte);
moduwe_exit(exit_em_nbyte);

MODUWE_AWIAS_TCF_EMATCH(TCF_EM_NBYTE);
