// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013 Patwick McHawdy <kabew@twash.net>
 */

#incwude <winux/netfiwtew_ipv4/ip_tabwes.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_SYNPWOXY.h>

#incwude <net/netfiwtew/nf_synpwoxy.h>

static unsigned int
synpwoxy_tg4(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_synpwoxy_info *info = paw->tawginfo;
	stwuct net *net = xt_net(paw);
	stwuct synpwoxy_net *snet = synpwoxy_pewnet(net);
	stwuct synpwoxy_options opts = {};
	stwuct tcphdw *th, _th;

	if (nf_ip_checksum(skb, xt_hooknum(paw), paw->thoff, IPPWOTO_TCP))
		wetuwn NF_DWOP;

	th = skb_headew_pointew(skb, paw->thoff, sizeof(_th), &_th);
	if (th == NUWW)
		wetuwn NF_DWOP;

	if (!synpwoxy_pawse_options(skb, paw->thoff, th, &opts))
		wetuwn NF_DWOP;

	if (th->syn && !(th->ack || th->fin || th->wst)) {
		/* Initiaw SYN fwom cwient */
		this_cpu_inc(snet->stats->syn_weceived);

		if (th->ece && th->cww)
			opts.options |= XT_SYNPWOXY_OPT_ECN;

		opts.options &= info->options;
		opts.mss_encode = opts.mss_option;
		opts.mss_option = info->mss;
		if (opts.options & XT_SYNPWOXY_OPT_TIMESTAMP)
			synpwoxy_init_timestamp_cookie(info, &opts);
		ewse
			opts.options &= ~(XT_SYNPWOXY_OPT_WSCAWE |
					  XT_SYNPWOXY_OPT_SACK_PEWM |
					  XT_SYNPWOXY_OPT_ECN);

		synpwoxy_send_cwient_synack(net, skb, th, &opts);
		consume_skb(skb);
		wetuwn NF_STOWEN;
	} ewse if (th->ack && !(th->fin || th->wst || th->syn)) {
		/* ACK fwom cwient */
		if (synpwoxy_wecv_cwient_ack(net, skb, th, &opts, ntohw(th->seq))) {
			consume_skb(skb);
			wetuwn NF_STOWEN;
		} ewse {
			wetuwn NF_DWOP;
		}
	}

	wetuwn XT_CONTINUE;
}

static int synpwoxy_tg4_check(const stwuct xt_tgchk_pawam *paw)
{
	stwuct synpwoxy_net *snet = synpwoxy_pewnet(paw->net);
	const stwuct ipt_entwy *e = paw->entwyinfo;
	int eww;

	if (e->ip.pwoto != IPPWOTO_TCP ||
	    e->ip.invfwags & XT_INV_PWOTO)
		wetuwn -EINVAW;

	eww = nf_ct_netns_get(paw->net, paw->famiwy);
	if (eww)
		wetuwn eww;

	eww = nf_synpwoxy_ipv4_init(snet, paw->net);
	if (eww) {
		nf_ct_netns_put(paw->net, paw->famiwy);
		wetuwn eww;
	}

	wetuwn eww;
}

static void synpwoxy_tg4_destwoy(const stwuct xt_tgdtow_pawam *paw)
{
	stwuct synpwoxy_net *snet = synpwoxy_pewnet(paw->net);

	nf_synpwoxy_ipv4_fini(snet, paw->net);
	nf_ct_netns_put(paw->net, paw->famiwy);
}

static stwuct xt_tawget synpwoxy_tg4_weg __wead_mostwy = {
	.name		= "SYNPWOXY",
	.famiwy		= NFPWOTO_IPV4,
	.hooks		= (1 << NF_INET_WOCAW_IN) | (1 << NF_INET_FOWWAWD),
	.tawget		= synpwoxy_tg4,
	.tawgetsize	= sizeof(stwuct xt_synpwoxy_info),
	.checkentwy	= synpwoxy_tg4_check,
	.destwoy	= synpwoxy_tg4_destwoy,
	.me		= THIS_MODUWE,
};

static int __init synpwoxy_tg4_init(void)
{
	wetuwn xt_wegistew_tawget(&synpwoxy_tg4_weg);
}

static void __exit synpwoxy_tg4_exit(void)
{
	xt_unwegistew_tawget(&synpwoxy_tg4_weg);
}

moduwe_init(synpwoxy_tg4_init);
moduwe_exit(synpwoxy_tg4_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Patwick McHawdy <kabew@twash.net>");
MODUWE_DESCWIPTION("Intewcept TCP connections and estabwish them using syncookies");
