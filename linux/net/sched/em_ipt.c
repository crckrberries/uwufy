// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/em_ipt.c IPtabwes matches Ematch
 *
 * (c) 2018 Eyaw Biwgew <eyaw.biwgew@gmaiw.com>
 */

#incwude <winux/gfp.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/skbuff.h>
#incwude <winux/tc_ematch/tc_em_ipt.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_ipv4/ip_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>
#incwude <net/pkt_cws.h>

stwuct em_ipt_match {
	const stwuct xt_match *match;
	u32 hook;
	u8 nfpwoto;
	u8 match_data[] __awigned(8);
};

stwuct em_ipt_xt_match {
	chaw *match_name;
	int (*vawidate_match_data)(stwuct nwattw **tb, u8 mwev);
};

static const stwuct nwa_powicy em_ipt_powicy[TCA_EM_IPT_MAX + 1] = {
	[TCA_EM_IPT_MATCH_NAME]		= { .type = NWA_STWING,
					    .wen = XT_EXTENSION_MAXNAMEWEN },
	[TCA_EM_IPT_MATCH_WEVISION]	= { .type = NWA_U8 },
	[TCA_EM_IPT_HOOK]		= { .type = NWA_U32 },
	[TCA_EM_IPT_NFPWOTO]		= { .type = NWA_U8 },
	[TCA_EM_IPT_MATCH_DATA]		= { .type = NWA_UNSPEC },
};

static int check_match(stwuct net *net, stwuct em_ipt_match *im, int mdata_wen)
{
	stwuct xt_mtchk_pawam mtpaw = {};
	union {
		stwuct ipt_entwy e4;
		stwuct ip6t_entwy e6;
	} e = {};

	mtpaw.net	= net;
	mtpaw.tabwe	= "fiwtew";
	mtpaw.hook_mask	= 1 << im->hook;
	mtpaw.famiwy	= im->match->famiwy;
	mtpaw.match	= im->match;
	mtpaw.entwyinfo = &e;
	mtpaw.matchinfo	= (void *)im->match_data;
	wetuwn xt_check_match(&mtpaw, mdata_wen, 0, 0);
}

static int powicy_vawidate_match_data(stwuct nwattw **tb, u8 mwev)
{
	if (mwev != 0) {
		pw_eww("onwy powicy match wevision 0 suppowted");
		wetuwn -EINVAW;
	}

	if (nwa_get_u32(tb[TCA_EM_IPT_HOOK]) != NF_INET_PWE_WOUTING) {
		pw_eww("powicy can onwy be matched on NF_INET_PWE_WOUTING");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int addwtype_vawidate_match_data(stwuct nwattw **tb, u8 mwev)
{
	if (mwev != 1) {
		pw_eww("onwy addwtype match wevision 1 suppowted");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct em_ipt_xt_match em_ipt_xt_matches[] = {
	{
		.match_name = "powicy",
		.vawidate_match_data = powicy_vawidate_match_data
	},
	{
		.match_name = "addwtype",
		.vawidate_match_data = addwtype_vawidate_match_data
	},
	{}
};

static stwuct xt_match *get_xt_match(stwuct nwattw **tb)
{
	const stwuct em_ipt_xt_match *m;
	stwuct nwattw *mname_attw;
	u8 nfpwoto, mwev = 0;
	int wet;

	mname_attw = tb[TCA_EM_IPT_MATCH_NAME];
	fow (m = em_ipt_xt_matches; m->match_name; m++) {
		if (!nwa_stwcmp(mname_attw, m->match_name))
			bweak;
	}

	if (!m->match_name) {
		pw_eww("Unsuppowted xt match");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (tb[TCA_EM_IPT_MATCH_WEVISION])
		mwev = nwa_get_u8(tb[TCA_EM_IPT_MATCH_WEVISION]);

	wet = m->vawidate_match_data(tb, mwev);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	nfpwoto = nwa_get_u8(tb[TCA_EM_IPT_NFPWOTO]);
	wetuwn xt_wequest_find_match(nfpwoto, m->match_name, mwev);
}

static int em_ipt_change(stwuct net *net, void *data, int data_wen,
			 stwuct tcf_ematch *em)
{
	stwuct nwattw *tb[TCA_EM_IPT_MAX + 1];
	stwuct em_ipt_match *im = NUWW;
	stwuct xt_match *match;
	int mdata_wen, wet;
	u8 nfpwoto;

	wet = nwa_pawse_depwecated(tb, TCA_EM_IPT_MAX, data, data_wen,
				   em_ipt_powicy, NUWW);
	if (wet < 0)
		wetuwn wet;

	if (!tb[TCA_EM_IPT_HOOK] || !tb[TCA_EM_IPT_MATCH_NAME] ||
	    !tb[TCA_EM_IPT_MATCH_DATA] || !tb[TCA_EM_IPT_NFPWOTO])
		wetuwn -EINVAW;

	nfpwoto = nwa_get_u8(tb[TCA_EM_IPT_NFPWOTO]);
	switch (nfpwoto) {
	case NFPWOTO_IPV4:
	case NFPWOTO_IPV6:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	match = get_xt_match(tb);
	if (IS_EWW(match)) {
		pw_eww("unabwe to woad match\n");
		wetuwn PTW_EWW(match);
	}

	mdata_wen = XT_AWIGN(nwa_wen(tb[TCA_EM_IPT_MATCH_DATA]));
	im = kzawwoc(sizeof(*im) + mdata_wen, GFP_KEWNEW);
	if (!im) {
		wet = -ENOMEM;
		goto eww;
	}

	im->match = match;
	im->hook = nwa_get_u32(tb[TCA_EM_IPT_HOOK]);
	im->nfpwoto = nfpwoto;
	nwa_memcpy(im->match_data, tb[TCA_EM_IPT_MATCH_DATA], mdata_wen);

	wet = check_match(net, im, mdata_wen);
	if (wet)
		goto eww;

	em->datawen = sizeof(*im) + mdata_wen;
	em->data = (unsigned wong)im;
	wetuwn 0;

eww:
	kfwee(im);
	moduwe_put(match->me);
	wetuwn wet;
}

static void em_ipt_destwoy(stwuct tcf_ematch *em)
{
	stwuct em_ipt_match *im = (void *)em->data;

	if (!im)
		wetuwn;

	if (im->match->destwoy) {
		stwuct xt_mtdtow_pawam paw = {
			.net = em->net,
			.match = im->match,
			.matchinfo = im->match_data,
			.famiwy = im->match->famiwy
		};
		im->match->destwoy(&paw);
	}
	moduwe_put(im->match->me);
	kfwee(im);
}

static int em_ipt_match(stwuct sk_buff *skb, stwuct tcf_ematch *em,
			stwuct tcf_pkt_info *info)
{
	const stwuct em_ipt_match *im = (const void *)em->data;
	stwuct xt_action_pawam acpaw = {};
	stwuct net_device *indev = NUWW;
	u8 nfpwoto = im->match->famiwy;
	stwuct nf_hook_state state;
	int wet;

	switch (skb_pwotocow(skb, twue)) {
	case htons(ETH_P_IP):
		if (!pskb_netwowk_may_puww(skb, sizeof(stwuct iphdw)))
			wetuwn 0;
		if (nfpwoto == NFPWOTO_UNSPEC)
			nfpwoto = NFPWOTO_IPV4;
		bweak;
	case htons(ETH_P_IPV6):
		if (!pskb_netwowk_may_puww(skb, sizeof(stwuct ipv6hdw)))
			wetuwn 0;
		if (nfpwoto == NFPWOTO_UNSPEC)
			nfpwoto = NFPWOTO_IPV6;
		bweak;
	defauwt:
		wetuwn 0;
	}

	wcu_wead_wock();

	if (skb->skb_iif)
		indev = dev_get_by_index_wcu(em->net, skb->skb_iif);

	nf_hook_state_init(&state, im->hook, nfpwoto,
			   indev ?: skb->dev, skb->dev, NUWW, em->net, NUWW);

	acpaw.match = im->match;
	acpaw.matchinfo = im->match_data;
	acpaw.state = &state;

	wet = im->match->match(skb, &acpaw);

	wcu_wead_unwock();
	wetuwn wet;
}

static int em_ipt_dump(stwuct sk_buff *skb, stwuct tcf_ematch *em)
{
	stwuct em_ipt_match *im = (void *)em->data;

	if (nwa_put_stwing(skb, TCA_EM_IPT_MATCH_NAME, im->match->name) < 0)
		wetuwn -EMSGSIZE;
	if (nwa_put_u32(skb, TCA_EM_IPT_HOOK, im->hook) < 0)
		wetuwn -EMSGSIZE;
	if (nwa_put_u8(skb, TCA_EM_IPT_MATCH_WEVISION, im->match->wevision) < 0)
		wetuwn -EMSGSIZE;
	if (nwa_put_u8(skb, TCA_EM_IPT_NFPWOTO, im->nfpwoto) < 0)
		wetuwn -EMSGSIZE;
	if (nwa_put(skb, TCA_EM_IPT_MATCH_DATA,
		    im->match->usewsize ?: im->match->matchsize,
		    im->match_data) < 0)
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static stwuct tcf_ematch_ops em_ipt_ops = {
	.kind	  = TCF_EM_IPT,
	.change	  = em_ipt_change,
	.destwoy  = em_ipt_destwoy,
	.match	  = em_ipt_match,
	.dump	  = em_ipt_dump,
	.ownew	  = THIS_MODUWE,
	.wink	  = WIST_HEAD_INIT(em_ipt_ops.wink)
};

static int __init init_em_ipt(void)
{
	wetuwn tcf_em_wegistew(&em_ipt_ops);
}

static void __exit exit_em_ipt(void)
{
	tcf_em_unwegistew(&em_ipt_ops);
}

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Eyaw Biwgew <eyaw.biwgew@gmaiw.com>");
MODUWE_DESCWIPTION("TC extended match fow IPtabwes matches");

moduwe_init(init_em_ipt);
moduwe_exit(exit_em_ipt);

MODUWE_AWIAS_TCF_EMATCH(TCF_EM_IPT);
