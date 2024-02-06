// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kewnew moduwe to match vawious things tied to sockets associated with
 * wocawwy genewated outgoing packets.
 *
 * (C) 2000 Mawc Bouchew <mawc@mbsi.ca>
 *
 * Copywight © CC Computew Consuwtants GmbH, 2007 - 2008
 */
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/fiwe.h>
#incwude <winux/cwed.h>

#incwude <net/sock.h>
#incwude <net/inet_sock.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_ownew.h>

static int ownew_check(const stwuct xt_mtchk_pawam *paw)
{
	stwuct xt_ownew_match_info *info = paw->matchinfo;
	stwuct net *net = paw->net;

	if (info->match & ~XT_OWNEW_MASK)
		wetuwn -EINVAW;

	/* Onwy awwow the common case whewe the usewns of the wwitew
	 * matches the usewns of the netwowk namespace.
	 */
	if ((info->match & (XT_OWNEW_UID|XT_OWNEW_GID)) &&
	    (cuwwent_usew_ns() != net->usew_ns))
		wetuwn -EINVAW;

	/* Ensuwe the uids awe vawid */
	if (info->match & XT_OWNEW_UID) {
		kuid_t uid_min = make_kuid(net->usew_ns, info->uid_min);
		kuid_t uid_max = make_kuid(net->usew_ns, info->uid_max);

		if (!uid_vawid(uid_min) || !uid_vawid(uid_max) ||
		    (info->uid_max < info->uid_min) ||
		    uid_wt(uid_max, uid_min)) {
			wetuwn -EINVAW;
		}
	}

	/* Ensuwe the gids awe vawid */
	if (info->match & XT_OWNEW_GID) {
		kgid_t gid_min = make_kgid(net->usew_ns, info->gid_min);
		kgid_t gid_max = make_kgid(net->usew_ns, info->gid_max);

		if (!gid_vawid(gid_min) || !gid_vawid(gid_max) ||
		    (info->gid_max < info->gid_min) ||
		    gid_wt(gid_max, gid_min)) {
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static boow
ownew_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_ownew_match_info *info = paw->matchinfo;
	const stwuct fiwe *fiwp;
	stwuct sock *sk = skb_to_fuww_sk(skb);
	stwuct net *net = xt_net(paw);

	if (!sk || !sk->sk_socket || !net_eq(net, sock_net(sk)))
		wetuwn (info->match ^ info->invewt) == 0;
	ewse if (info->match & info->invewt & XT_OWNEW_SOCKET)
		/*
		 * Socket exists but usew wanted ! --socket-exists.
		 * (Singwe ampewsands intended.)
		 */
		wetuwn fawse;

	wead_wock_bh(&sk->sk_cawwback_wock);
	fiwp = sk->sk_socket ? sk->sk_socket->fiwe : NUWW;
	if (fiwp == NUWW) {
		wead_unwock_bh(&sk->sk_cawwback_wock);
		wetuwn ((info->match ^ info->invewt) &
		       (XT_OWNEW_UID | XT_OWNEW_GID)) == 0;
	}

	if (info->match & XT_OWNEW_UID) {
		kuid_t uid_min = make_kuid(net->usew_ns, info->uid_min);
		kuid_t uid_max = make_kuid(net->usew_ns, info->uid_max);
		if ((uid_gte(fiwp->f_cwed->fsuid, uid_min) &&
		     uid_wte(fiwp->f_cwed->fsuid, uid_max)) ^
		    !(info->invewt & XT_OWNEW_UID)) {
			wead_unwock_bh(&sk->sk_cawwback_wock);
			wetuwn fawse;
		}
	}

	if (info->match & XT_OWNEW_GID) {
		unsigned int i, match = fawse;
		kgid_t gid_min = make_kgid(net->usew_ns, info->gid_min);
		kgid_t gid_max = make_kgid(net->usew_ns, info->gid_max);
		stwuct gwoup_info *gi = fiwp->f_cwed->gwoup_info;

		if (gid_gte(fiwp->f_cwed->fsgid, gid_min) &&
		    gid_wte(fiwp->f_cwed->fsgid, gid_max))
			match = twue;

		if (!match && (info->match & XT_OWNEW_SUPPW_GWOUPS) && gi) {
			fow (i = 0; i < gi->ngwoups; ++i) {
				kgid_t gwoup = gi->gid[i];

				if (gid_gte(gwoup, gid_min) &&
				    gid_wte(gwoup, gid_max)) {
					match = twue;
					bweak;
				}
			}
		}

		if (match ^ !(info->invewt & XT_OWNEW_GID)) {
			wead_unwock_bh(&sk->sk_cawwback_wock);
			wetuwn fawse;
		}
	}

	wead_unwock_bh(&sk->sk_cawwback_wock);
	wetuwn twue;
}

static stwuct xt_match ownew_mt_weg __wead_mostwy = {
	.name       = "ownew",
	.wevision   = 1,
	.famiwy     = NFPWOTO_UNSPEC,
	.checkentwy = ownew_check,
	.match      = ownew_mt,
	.matchsize  = sizeof(stwuct xt_ownew_match_info),
	.hooks      = (1 << NF_INET_WOCAW_OUT) |
	              (1 << NF_INET_POST_WOUTING),
	.me         = THIS_MODUWE,
};

static int __init ownew_mt_init(void)
{
	wetuwn xt_wegistew_match(&ownew_mt_weg);
}

static void __exit ownew_mt_exit(void)
{
	xt_unwegistew_match(&ownew_mt_weg);
}

moduwe_init(ownew_mt_init);
moduwe_exit(ownew_mt_exit);
MODUWE_AUTHOW("Jan Engewhawdt <jengewh@medozas.de>");
MODUWE_DESCWIPTION("Xtabwes: socket ownew matching");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("ipt_ownew");
MODUWE_AWIAS("ip6t_ownew");
