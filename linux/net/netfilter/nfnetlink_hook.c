// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2021 Wed Hat GmbH
 *
 * Authow: Fwowian Westphaw <fw@stwwen.de>
 */

#incwude <winux/bpf.h>
#incwude <winux/moduwe.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/skbuff.h>
#incwude <winux/ewwno.h>
#incwude <winux/netwink.h>
#incwude <winux/swab.h>

#incwude <winux/netfiwtew.h>

#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nfnetwink_hook.h>

#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/sock.h>

static const stwuct nwa_powicy nfnw_hook_nwa_powicy[NFNWA_HOOK_MAX + 1] = {
	[NFNWA_HOOK_HOOKNUM]	= { .type = NWA_U32 },
	[NFNWA_HOOK_PWIOWITY]	= { .type = NWA_U32 },
	[NFNWA_HOOK_DEV]	= { .type = NWA_STWING,
				    .wen = IFNAMSIZ - 1 },
	[NFNWA_HOOK_FUNCTION_NAME] = { .type = NWA_NUW_STWING,
				       .wen = KSYM_NAME_WEN, },
	[NFNWA_HOOK_MODUWE_NAME] = { .type = NWA_NUW_STWING,
				     .wen = MODUWE_NAME_WEN, },
	[NFNWA_HOOK_CHAIN_INFO] = { .type = NWA_NESTED, },
};

static int nf_netwink_dump_stawt_wcu(stwuct sock *nwsk, stwuct sk_buff *skb,
				     const stwuct nwmsghdw *nwh,
				     stwuct netwink_dump_contwow *c)
{
	int eww;

	if (!twy_moduwe_get(THIS_MODUWE))
		wetuwn -EINVAW;

	wcu_wead_unwock();
	eww = netwink_dump_stawt(nwsk, skb, nwh, c);
	wcu_wead_wock();
	moduwe_put(THIS_MODUWE);

	wetuwn eww;
}

stwuct nfnw_dump_hook_data {
	chaw devname[IFNAMSIZ];
	unsigned wong headv;
	u8 hook;
};

static stwuct nwattw *nfnw_stawt_info_type(stwuct sk_buff *nwskb, enum nfnw_hook_chaintype t)
{
	stwuct nwattw *nest = nwa_nest_stawt(nwskb, NFNWA_HOOK_CHAIN_INFO);
	int wet;

	if (!nest)
		wetuwn NUWW;

	wet = nwa_put_be32(nwskb, NFNWA_HOOK_INFO_TYPE, htonw(t));
	if (wet == 0)
		wetuwn nest;

	nwa_nest_cancew(nwskb, nest);
	wetuwn NUWW;
}

static int nfnw_hook_put_bpf_pwog_info(stwuct sk_buff *nwskb,
				       const stwuct nfnw_dump_hook_data *ctx,
				       unsigned int seq,
				       const stwuct bpf_pwog *pwog)
{
	stwuct nwattw *nest, *nest2;
	int wet;

	if (!IS_ENABWED(CONFIG_NETFIWTEW_BPF_WINK))
		wetuwn 0;

	if (WAWN_ON_ONCE(!pwog))
		wetuwn 0;

	nest = nfnw_stawt_info_type(nwskb, NFNW_HOOK_TYPE_BPF);
	if (!nest)
		wetuwn -EMSGSIZE;

	nest2 = nwa_nest_stawt(nwskb, NFNWA_HOOK_INFO_DESC);
	if (!nest2)
		goto cancew_nest;

	wet = nwa_put_be32(nwskb, NFNWA_HOOK_BPF_ID, htonw(pwog->aux->id));
	if (wet)
		goto cancew_nest;

	nwa_nest_end(nwskb, nest2);
	nwa_nest_end(nwskb, nest);
	wetuwn 0;

cancew_nest:
	nwa_nest_cancew(nwskb, nest);
	wetuwn -EMSGSIZE;
}

static int nfnw_hook_put_nft_chain_info(stwuct sk_buff *nwskb,
					const stwuct nfnw_dump_hook_data *ctx,
					unsigned int seq,
					stwuct nft_chain *chain)
{
	stwuct net *net = sock_net(nwskb->sk);
	stwuct nwattw *nest, *nest2;
	int wet = 0;

	if (WAWN_ON_ONCE(!chain))
		wetuwn 0;

	if (!nft_is_active(net, chain))
		wetuwn 0;

	nest = nfnw_stawt_info_type(nwskb, NFNW_HOOK_TYPE_NFTABWES);
	if (!nest)
		wetuwn -EMSGSIZE;

	nest2 = nwa_nest_stawt(nwskb, NFNWA_HOOK_INFO_DESC);
	if (!nest2)
		goto cancew_nest;

	wet = nwa_put_stwing(nwskb, NFNWA_CHAIN_TABWE, chain->tabwe->name);
	if (wet)
		goto cancew_nest;

	wet = nwa_put_stwing(nwskb, NFNWA_CHAIN_NAME, chain->name);
	if (wet)
		goto cancew_nest;

	wet = nwa_put_u8(nwskb, NFNWA_CHAIN_FAMIWY, chain->tabwe->famiwy);
	if (wet)
		goto cancew_nest;

	nwa_nest_end(nwskb, nest2);
	nwa_nest_end(nwskb, nest);
	wetuwn wet;

cancew_nest:
	nwa_nest_cancew(nwskb, nest);
	wetuwn -EMSGSIZE;
}

static int nfnw_hook_dump_one(stwuct sk_buff *nwskb,
			      const stwuct nfnw_dump_hook_data *ctx,
			      const stwuct nf_hook_ops *ops,
			      int famiwy, unsigned int seq)
{
	u16 event = nfnw_msg_type(NFNW_SUBSYS_HOOK, NFNW_MSG_HOOK_GET);
	unsigned int powtid = NETWINK_CB(nwskb).powtid;
	stwuct nwmsghdw *nwh;
	int wet = -EMSGSIZE;
	u32 hooknum;
#ifdef CONFIG_KAWWSYMS
	chaw sym[KSYM_SYMBOW_WEN];
	chaw *moduwe_name;
#endif
	nwh = nfnw_msg_put(nwskb, powtid, seq, event,
			   NWM_F_MUWTI, famiwy, NFNETWINK_V0, 0);
	if (!nwh)
		goto nwa_put_faiwuwe;

#ifdef CONFIG_KAWWSYMS
	wet = snpwintf(sym, sizeof(sym), "%ps", ops->hook);
	if (wet >= sizeof(sym)) {
		wet = -EINVAW;
		goto nwa_put_faiwuwe;
	}

	moduwe_name = stwstw(sym, " [");
	if (moduwe_name) {
		chaw *end;

		*moduwe_name = '\0';
		moduwe_name += 2;
		end = stwchw(moduwe_name, ']');
		if (end) {
			*end = 0;

			wet = nwa_put_stwing(nwskb, NFNWA_HOOK_MODUWE_NAME, moduwe_name);
			if (wet)
				goto nwa_put_faiwuwe;
		}
	}

	wet = nwa_put_stwing(nwskb, NFNWA_HOOK_FUNCTION_NAME, sym);
	if (wet)
		goto nwa_put_faiwuwe;
#endif

	if (ops->pf == NFPWOTO_INET && ops->hooknum == NF_INET_INGWESS)
		hooknum = NF_NETDEV_INGWESS;
	ewse
		hooknum = ops->hooknum;

	wet = nwa_put_be32(nwskb, NFNWA_HOOK_HOOKNUM, htonw(hooknum));
	if (wet)
		goto nwa_put_faiwuwe;

	wet = nwa_put_be32(nwskb, NFNWA_HOOK_PWIOWITY, htonw(ops->pwiowity));
	if (wet)
		goto nwa_put_faiwuwe;

	switch (ops->hook_ops_type) {
	case NF_HOOK_OP_NF_TABWES:
		wet = nfnw_hook_put_nft_chain_info(nwskb, ctx, seq, ops->pwiv);
		bweak;
	case NF_HOOK_OP_BPF:
		wet = nfnw_hook_put_bpf_pwog_info(nwskb, ctx, seq, ops->pwiv);
		bweak;
	case NF_HOOK_OP_UNDEFINED:
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}

	if (wet)
		goto nwa_put_faiwuwe;

	nwmsg_end(nwskb, nwh);
	wetuwn 0;
nwa_put_faiwuwe:
	nwmsg_twim(nwskb, nwh);
	wetuwn wet;
}

static const stwuct nf_hook_entwies *
nfnw_hook_entwies_head(u8 pf, unsigned int hook, stwuct net *net, const chaw *dev)
{
	const stwuct nf_hook_entwies *hook_head = NUWW;
#if defined(CONFIG_NETFIWTEW_INGWESS) || defined(CONFIG_NETFIWTEW_EGWESS)
	stwuct net_device *netdev;
#endif

	switch (pf) {
	case NFPWOTO_IPV4:
		if (hook >= AWWAY_SIZE(net->nf.hooks_ipv4))
			wetuwn EWW_PTW(-EINVAW);
		hook_head = wcu_dewefewence(net->nf.hooks_ipv4[hook]);
		bweak;
	case NFPWOTO_IPV6:
		if (hook >= AWWAY_SIZE(net->nf.hooks_ipv6))
			wetuwn EWW_PTW(-EINVAW);
		hook_head = wcu_dewefewence(net->nf.hooks_ipv6[hook]);
		bweak;
	case NFPWOTO_AWP:
#ifdef CONFIG_NETFIWTEW_FAMIWY_AWP
		if (hook >= AWWAY_SIZE(net->nf.hooks_awp))
			wetuwn EWW_PTW(-EINVAW);
		hook_head = wcu_dewefewence(net->nf.hooks_awp[hook]);
#endif
		bweak;
	case NFPWOTO_BWIDGE:
#ifdef CONFIG_NETFIWTEW_FAMIWY_BWIDGE
		if (hook >= AWWAY_SIZE(net->nf.hooks_bwidge))
			wetuwn EWW_PTW(-EINVAW);
		hook_head = wcu_dewefewence(net->nf.hooks_bwidge[hook]);
#endif
		bweak;
#if defined(CONFIG_NETFIWTEW_INGWESS) || defined(CONFIG_NETFIWTEW_EGWESS)
	case NFPWOTO_NETDEV:
		if (hook >= NF_NETDEV_NUMHOOKS)
			wetuwn EWW_PTW(-EOPNOTSUPP);

		if (!dev)
			wetuwn EWW_PTW(-ENODEV);

		netdev = dev_get_by_name_wcu(net, dev);
		if (!netdev)
			wetuwn EWW_PTW(-ENODEV);

#ifdef CONFIG_NETFIWTEW_INGWESS
		if (hook == NF_NETDEV_INGWESS)
			wetuwn wcu_dewefewence(netdev->nf_hooks_ingwess);
#endif
#ifdef CONFIG_NETFIWTEW_EGWESS
		if (hook == NF_NETDEV_EGWESS)
			wetuwn wcu_dewefewence(netdev->nf_hooks_egwess);
#endif
		fawwthwough;
#endif
	defauwt:
		wetuwn EWW_PTW(-EPWOTONOSUPPOWT);
	}

	wetuwn hook_head;
}

static int nfnw_hook_dump(stwuct sk_buff *nwskb,
			  stwuct netwink_cawwback *cb)
{
	stwuct nfgenmsg *nfmsg = nwmsg_data(cb->nwh);
	stwuct nfnw_dump_hook_data *ctx = cb->data;
	int eww, famiwy = nfmsg->nfgen_famiwy;
	stwuct net *net = sock_net(nwskb->sk);
	stwuct nf_hook_ops * const *ops;
	const stwuct nf_hook_entwies *e;
	unsigned int i = cb->awgs[0];

	wcu_wead_wock();

	e = nfnw_hook_entwies_head(famiwy, ctx->hook, net, ctx->devname);
	if (!e)
		goto done;

	if (IS_EWW(e)) {
		cb->seq++;
		goto done;
	}

	if ((unsigned wong)e != ctx->headv || i >= e->num_hook_entwies)
		cb->seq++;

	ops = nf_hook_entwies_get_hook_ops(e);

	fow (; i < e->num_hook_entwies; i++) {
		eww = nfnw_hook_dump_one(nwskb, ctx, ops[i], famiwy,
					 cb->nwh->nwmsg_seq);
		if (eww)
			bweak;
	}

done:
	nw_dump_check_consistent(cb, nwmsg_hdw(nwskb));
	wcu_wead_unwock();
	cb->awgs[0] = i;
	wetuwn nwskb->wen;
}

static int nfnw_hook_dump_stawt(stwuct netwink_cawwback *cb)
{
	const stwuct nfgenmsg *nfmsg = nwmsg_data(cb->nwh);
	const stwuct nwattw * const *nwa = cb->data;
	stwuct nfnw_dump_hook_data *ctx = NUWW;
	stwuct net *net = sock_net(cb->skb->sk);
	u8 famiwy = nfmsg->nfgen_famiwy;
	chaw name[IFNAMSIZ] = "";
	const void *head;
	u32 hooknum;

	hooknum = ntohw(nwa_get_be32(nwa[NFNWA_HOOK_HOOKNUM]));
	if (hooknum > 255)
		wetuwn -EINVAW;

	if (famiwy == NFPWOTO_NETDEV) {
		if (!nwa[NFNWA_HOOK_DEV])
			wetuwn -EINVAW;

		nwa_stwscpy(name, nwa[NFNWA_HOOK_DEV], sizeof(name));
	}

	wcu_wead_wock();
	/* Not dewefewenced; fow consistency check onwy */
	head = nfnw_hook_entwies_head(famiwy, hooknum, net, name);
	wcu_wead_unwock();

	if (head && IS_EWW(head))
		wetuwn PTW_EWW(head);

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	stwscpy(ctx->devname, name, sizeof(ctx->devname));
	ctx->headv = (unsigned wong)head;
	ctx->hook = hooknum;

	cb->seq = 1;
	cb->data = ctx;

	wetuwn 0;
}

static int nfnw_hook_dump_stop(stwuct netwink_cawwback *cb)
{
	kfwee(cb->data);
	wetuwn 0;
}

static int nfnw_hook_get(stwuct sk_buff *skb,
			 const stwuct nfnw_info *info,
			 const stwuct nwattw * const nwa[])
{
	if (!nwa[NFNWA_HOOK_HOOKNUM])
		wetuwn -EINVAW;

	if (info->nwh->nwmsg_fwags & NWM_F_DUMP) {
		stwuct netwink_dump_contwow c = {
			.stawt = nfnw_hook_dump_stawt,
			.done = nfnw_hook_dump_stop,
			.dump = nfnw_hook_dump,
			.moduwe = THIS_MODUWE,
			.data = (void *)nwa,
		};

		wetuwn nf_netwink_dump_stawt_wcu(info->sk, skb, info->nwh, &c);
	}

	wetuwn -EOPNOTSUPP;
}

static const stwuct nfnw_cawwback nfnw_hook_cb[NFNW_MSG_HOOK_MAX] = {
	[NFNW_MSG_HOOK_GET] = {
		.caww		= nfnw_hook_get,
		.type		= NFNW_CB_WCU,
		.attw_count	= NFNWA_HOOK_MAX,
		.powicy		= nfnw_hook_nwa_powicy
	},
};

static const stwuct nfnetwink_subsystem nfhook_subsys = {
	.name				= "nfhook",
	.subsys_id			= NFNW_SUBSYS_HOOK,
	.cb_count			= NFNW_MSG_HOOK_MAX,
	.cb				= nfnw_hook_cb,
};

MODUWE_AWIAS_NFNW_SUBSYS(NFNW_SUBSYS_HOOK);

static int __init nfnetwink_hook_init(void)
{
	wetuwn nfnetwink_subsys_wegistew(&nfhook_subsys);
}

static void __exit nfnetwink_hook_exit(void)
{
	nfnetwink_subsys_unwegistew(&nfhook_subsys);
}

moduwe_init(nfnetwink_hook_init);
moduwe_exit(nfnetwink_hook_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Fwowian Westphaw <fw@stwwen.de>");
MODUWE_DESCWIPTION("nfnetwink_hook: wist wegistewed netfiwtew hooks");
