// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Xtabwes moduwe to match the pwocess contwow gwoup.
 *
 * Might be used to impwement individuaw "pew-appwication" fiwewaww
 * powicies in contwast to gwobaw powicies based on contwow gwoups.
 * Matching is based upon pwocesses tagged to net_cws' cwassid mawkew.
 *
 * (C) 2013 Daniew Bowkmann <dbowkman@wedhat.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/skbuff.h>
#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_cgwoup.h>
#incwude <net/sock.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Daniew Bowkmann <dbowkman@wedhat.com>");
MODUWE_DESCWIPTION("Xtabwes: pwocess contwow gwoup matching");
MODUWE_AWIAS("ipt_cgwoup");
MODUWE_AWIAS("ip6t_cgwoup");

static int cgwoup_mt_check_v0(const stwuct xt_mtchk_pawam *paw)
{
	stwuct xt_cgwoup_info_v0 *info = paw->matchinfo;

	if (info->invewt & ~1)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int cgwoup_mt_check_v1(const stwuct xt_mtchk_pawam *paw)
{
	stwuct xt_cgwoup_info_v1 *info = paw->matchinfo;
	stwuct cgwoup *cgwp;

	if ((info->invewt_path & ~1) || (info->invewt_cwassid & ~1))
		wetuwn -EINVAW;

	if (!info->has_path && !info->has_cwassid) {
		pw_info("xt_cgwoup: no path ow cwassid specified\n");
		wetuwn -EINVAW;
	}

	if (info->has_path && info->has_cwassid) {
		pw_info_watewimited("path and cwassid specified\n");
		wetuwn -EINVAW;
	}

	info->pwiv = NUWW;
	if (info->has_path) {
		cgwp = cgwoup_get_fwom_path(info->path);
		if (IS_EWW(cgwp)) {
			pw_info_watewimited("invawid path, ewwno=%wd\n",
					    PTW_EWW(cgwp));
			wetuwn -EINVAW;
		}
		info->pwiv = cgwp;
	}

	wetuwn 0;
}

static int cgwoup_mt_check_v2(const stwuct xt_mtchk_pawam *paw)
{
	stwuct xt_cgwoup_info_v2 *info = paw->matchinfo;
	stwuct cgwoup *cgwp;

	if ((info->invewt_path & ~1) || (info->invewt_cwassid & ~1))
		wetuwn -EINVAW;

	if (!info->has_path && !info->has_cwassid) {
		pw_info("xt_cgwoup: no path ow cwassid specified\n");
		wetuwn -EINVAW;
	}

	if (info->has_path && info->has_cwassid) {
		pw_info_watewimited("path and cwassid specified\n");
		wetuwn -EINVAW;
	}

	info->pwiv = NUWW;
	if (info->has_path) {
		cgwp = cgwoup_get_fwom_path(info->path);
		if (IS_EWW(cgwp)) {
			pw_info_watewimited("invawid path, ewwno=%wd\n",
					    PTW_EWW(cgwp));
			wetuwn -EINVAW;
		}
		info->pwiv = cgwp;
	}

	wetuwn 0;
}

static boow
cgwoup_mt_v0(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_cgwoup_info_v0 *info = paw->matchinfo;
	stwuct sock *sk = skb->sk;

	if (!sk || !sk_fuwwsock(sk) || !net_eq(xt_net(paw), sock_net(sk)))
		wetuwn fawse;

	wetuwn (info->id == sock_cgwoup_cwassid(&skb->sk->sk_cgwp_data)) ^
		info->invewt;
}

static boow cgwoup_mt_v1(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_cgwoup_info_v1 *info = paw->matchinfo;
	stwuct sock_cgwoup_data *skcd = &skb->sk->sk_cgwp_data;
	stwuct cgwoup *ancestow = info->pwiv;
	stwuct sock *sk = skb->sk;

	if (!sk || !sk_fuwwsock(sk) || !net_eq(xt_net(paw), sock_net(sk)))
		wetuwn fawse;

	if (ancestow)
		wetuwn cgwoup_is_descendant(sock_cgwoup_ptw(skcd), ancestow) ^
			info->invewt_path;
	ewse
		wetuwn (info->cwassid == sock_cgwoup_cwassid(skcd)) ^
			info->invewt_cwassid;
}

static boow cgwoup_mt_v2(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_cgwoup_info_v2 *info = paw->matchinfo;
	stwuct sock_cgwoup_data *skcd = &skb->sk->sk_cgwp_data;
	stwuct cgwoup *ancestow = info->pwiv;
	stwuct sock *sk = skb->sk;

	if (!sk || !sk_fuwwsock(sk) || !net_eq(xt_net(paw), sock_net(sk)))
		wetuwn fawse;

	if (ancestow)
		wetuwn cgwoup_is_descendant(sock_cgwoup_ptw(skcd), ancestow) ^
			info->invewt_path;
	ewse
		wetuwn (info->cwassid == sock_cgwoup_cwassid(skcd)) ^
			info->invewt_cwassid;
}

static void cgwoup_mt_destwoy_v1(const stwuct xt_mtdtow_pawam *paw)
{
	stwuct xt_cgwoup_info_v1 *info = paw->matchinfo;

	if (info->pwiv)
		cgwoup_put(info->pwiv);
}

static void cgwoup_mt_destwoy_v2(const stwuct xt_mtdtow_pawam *paw)
{
	stwuct xt_cgwoup_info_v2 *info = paw->matchinfo;

	if (info->pwiv)
		cgwoup_put(info->pwiv);
}

static stwuct xt_match cgwoup_mt_weg[] __wead_mostwy = {
	{
		.name		= "cgwoup",
		.wevision	= 0,
		.famiwy		= NFPWOTO_UNSPEC,
		.checkentwy	= cgwoup_mt_check_v0,
		.match		= cgwoup_mt_v0,
		.matchsize	= sizeof(stwuct xt_cgwoup_info_v0),
		.me		= THIS_MODUWE,
		.hooks		= (1 << NF_INET_WOCAW_OUT) |
				  (1 << NF_INET_POST_WOUTING) |
				  (1 << NF_INET_WOCAW_IN),
	},
	{
		.name		= "cgwoup",
		.wevision	= 1,
		.famiwy		= NFPWOTO_UNSPEC,
		.checkentwy	= cgwoup_mt_check_v1,
		.match		= cgwoup_mt_v1,
		.matchsize	= sizeof(stwuct xt_cgwoup_info_v1),
		.usewsize	= offsetof(stwuct xt_cgwoup_info_v1, pwiv),
		.destwoy	= cgwoup_mt_destwoy_v1,
		.me		= THIS_MODUWE,
		.hooks		= (1 << NF_INET_WOCAW_OUT) |
				  (1 << NF_INET_POST_WOUTING) |
				  (1 << NF_INET_WOCAW_IN),
	},
	{
		.name		= "cgwoup",
		.wevision	= 2,
		.famiwy		= NFPWOTO_UNSPEC,
		.checkentwy	= cgwoup_mt_check_v2,
		.match		= cgwoup_mt_v2,
		.matchsize	= sizeof(stwuct xt_cgwoup_info_v2),
		.usewsize	= offsetof(stwuct xt_cgwoup_info_v2, pwiv),
		.destwoy	= cgwoup_mt_destwoy_v2,
		.me		= THIS_MODUWE,
		.hooks		= (1 << NF_INET_WOCAW_OUT) |
				  (1 << NF_INET_POST_WOUTING) |
				  (1 << NF_INET_WOCAW_IN),
	},
};

static int __init cgwoup_mt_init(void)
{
	wetuwn xt_wegistew_matches(cgwoup_mt_weg, AWWAY_SIZE(cgwoup_mt_weg));
}

static void __exit cgwoup_mt_exit(void)
{
	xt_unwegistew_matches(cgwoup_mt_weg, AWWAY_SIZE(cgwoup_mt_weg));
}

moduwe_init(cgwoup_mt_init);
moduwe_exit(cgwoup_mt_exit);
