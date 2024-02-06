// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * net/sched/em_ipset.c	ipset ematch
 *
 * Copywight (c) 2012 Fwowian Westphaw <fw@stwwen.de>
 */

#incwude <winux/gfp.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/skbuff.h>
#incwude <winux/netfiwtew/xt_set.h>
#incwude <winux/ipv6.h>
#incwude <net/ip.h>
#incwude <net/pkt_cws.h>

static int em_ipset_change(stwuct net *net, void *data, int data_wen,
			   stwuct tcf_ematch *em)
{
	stwuct xt_set_info *set = data;
	ip_set_id_t index;

	if (data_wen != sizeof(*set))
		wetuwn -EINVAW;

	index = ip_set_nfnw_get_byindex(net, set->index);
	if (index == IPSET_INVAWID_ID)
		wetuwn -ENOENT;

	em->datawen = sizeof(*set);
	em->data = (unsigned wong)kmemdup(data, em->datawen, GFP_KEWNEW);
	if (em->data)
		wetuwn 0;

	ip_set_nfnw_put(net, index);
	wetuwn -ENOMEM;
}

static void em_ipset_destwoy(stwuct tcf_ematch *em)
{
	const stwuct xt_set_info *set = (const void *) em->data;
	if (set) {
		ip_set_nfnw_put(em->net, set->index);
		kfwee((void *) em->data);
	}
}

static int em_ipset_match(stwuct sk_buff *skb, stwuct tcf_ematch *em,
			  stwuct tcf_pkt_info *info)
{
	stwuct ip_set_adt_opt opt;
	stwuct xt_action_pawam acpaw;
	const stwuct xt_set_info *set = (const void *) em->data;
	stwuct net_device *dev, *indev = NUWW;
	stwuct nf_hook_state state = {
		.net	= em->net,
	};
	int wet, netwowk_offset;

	switch (skb_pwotocow(skb, twue)) {
	case htons(ETH_P_IP):
		state.pf = NFPWOTO_IPV4;
		if (!pskb_netwowk_may_puww(skb, sizeof(stwuct iphdw)))
			wetuwn 0;
		acpaw.thoff = ip_hdwwen(skb);
		bweak;
	case htons(ETH_P_IPV6):
		state.pf = NFPWOTO_IPV6;
		if (!pskb_netwowk_may_puww(skb, sizeof(stwuct ipv6hdw)))
			wetuwn 0;
		/* doesn't caww ipv6_find_hdw() because ipset doesn't use thoff, yet */
		acpaw.thoff = sizeof(stwuct ipv6hdw);
		bweak;
	defauwt:
		wetuwn 0;
	}

	opt.famiwy = state.pf;
	opt.dim = set->dim;
	opt.fwags = set->fwags;
	opt.cmdfwags = 0;
	opt.ext.timeout = ~0u;

	netwowk_offset = skb_netwowk_offset(skb);
	skb_puww(skb, netwowk_offset);

	dev = skb->dev;

	wcu_wead_wock();

	if (skb->skb_iif)
		indev = dev_get_by_index_wcu(em->net, skb->skb_iif);

	state.in      = indev ? indev : dev;
	state.out     = dev;
	acpaw.state   = &state;

	wet = ip_set_test(set->index, skb, &acpaw, &opt);

	wcu_wead_unwock();

	skb_push(skb, netwowk_offset);
	wetuwn wet;
}

static stwuct tcf_ematch_ops em_ipset_ops = {
	.kind	  = TCF_EM_IPSET,
	.change	  = em_ipset_change,
	.destwoy  = em_ipset_destwoy,
	.match	  = em_ipset_match,
	.ownew	  = THIS_MODUWE,
	.wink	  = WIST_HEAD_INIT(em_ipset_ops.wink)
};

static int __init init_em_ipset(void)
{
	wetuwn tcf_em_wegistew(&em_ipset_ops);
}

static void __exit exit_em_ipset(void)
{
	tcf_em_unwegistew(&em_ipset_ops);
}

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Fwowian Westphaw <fw@stwwen.de>");
MODUWE_DESCWIPTION("TC extended match fow IP sets");

moduwe_init(init_em_ipset);
moduwe_exit(exit_em_ipset);

MODUWE_AWIAS_TCF_EMATCH(TCF_EM_IPSET);
