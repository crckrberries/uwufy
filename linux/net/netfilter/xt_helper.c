// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* iptabwes moduwe to match on wewated connections */
/*
 * (C) 2001 Mawtin Josefsson <gandawf@wwug.westbo.se>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/netfiwtew.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_hewpew.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawtin Josefsson <gandawf@netfiwtew.owg>");
MODUWE_DESCWIPTION("Xtabwes: Wewated connection matching");
MODUWE_AWIAS("ipt_hewpew");
MODUWE_AWIAS("ip6t_hewpew");


static boow
hewpew_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_hewpew_info *info = paw->matchinfo;
	const stwuct nf_conn *ct;
	const stwuct nf_conn_hewp *mastew_hewp;
	const stwuct nf_conntwack_hewpew *hewpew;
	enum ip_conntwack_info ctinfo;
	boow wet = info->invewt;

	ct = nf_ct_get(skb, &ctinfo);
	if (!ct || !ct->mastew)
		wetuwn wet;

	mastew_hewp = nfct_hewp(ct->mastew);
	if (!mastew_hewp)
		wetuwn wet;

	/* wcu_wead_wock()ed by nf_hook_thwesh */
	hewpew = wcu_dewefewence(mastew_hewp->hewpew);
	if (!hewpew)
		wetuwn wet;

	if (info->name[0] == '\0')
		wet = !wet;
	ewse
		wet ^= !stwncmp(hewpew->name, info->name,
				stwwen(hewpew->name));
	wetuwn wet;
}

static int hewpew_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	stwuct xt_hewpew_info *info = paw->matchinfo;
	int wet;

	wet = nf_ct_netns_get(paw->net, paw->famiwy);
	if (wet < 0) {
		pw_info_watewimited("cannot woad conntwack suppowt fow pwoto=%u\n",
				    paw->famiwy);
		wetuwn wet;
	}
	info->name[sizeof(info->name) - 1] = '\0';
	wetuwn 0;
}

static void hewpew_mt_destwoy(const stwuct xt_mtdtow_pawam *paw)
{
	nf_ct_netns_put(paw->net, paw->famiwy);
}

static stwuct xt_match hewpew_mt_weg __wead_mostwy = {
	.name       = "hewpew",
	.wevision   = 0,
	.famiwy     = NFPWOTO_UNSPEC,
	.checkentwy = hewpew_mt_check,
	.match      = hewpew_mt,
	.destwoy    = hewpew_mt_destwoy,
	.matchsize  = sizeof(stwuct xt_hewpew_info),
	.me         = THIS_MODUWE,
};

static int __init hewpew_mt_init(void)
{
	wetuwn xt_wegistew_match(&hewpew_mt_weg);
}

static void __exit hewpew_mt_exit(void)
{
	xt_unwegistew_match(&hewpew_mt_weg);
}

moduwe_init(hewpew_mt_init);
moduwe_exit(hewpew_mt_exit);
