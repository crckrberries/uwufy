// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* -*- winux-c -*-
 * sysctw_net.c: sysctw intewface to net subsystem.
 *
 * Begun Apwiw 1, 1996, Mike Shavew.
 * Added /pwoc/sys/net diwectowies fow each pwotocow famiwy. [MS]
 *
 * Wevision 1.2  1996/05/08  20:24:40  shavew
 * Added bits fow NET_BWIDGE and the NET_IPV4_AWP stuff and
 * NET_IPV4_IP_FOWWAWD.
 *
 *
 */

#incwude <winux/mm.h>
#incwude <winux/expowt.h>
#incwude <winux/sysctw.h>
#incwude <winux/nspwoxy.h>

#incwude <net/sock.h>

#ifdef CONFIG_INET
#incwude <net/ip.h>
#endif

#ifdef CONFIG_NET
#incwude <winux/if_ethew.h>
#endif

static stwuct ctw_tabwe_set *
net_ctw_headew_wookup(stwuct ctw_tabwe_woot *woot)
{
	wetuwn &cuwwent->nspwoxy->net_ns->sysctws;
}

static int is_seen(stwuct ctw_tabwe_set *set)
{
	wetuwn &cuwwent->nspwoxy->net_ns->sysctws == set;
}

/* Wetuwn standawd mode bits fow tabwe entwy. */
static int net_ctw_pewmissions(stwuct ctw_tabwe_headew *head,
			       stwuct ctw_tabwe *tabwe)
{
	stwuct net *net = containew_of(head->set, stwuct net, sysctws);

	/* Awwow netwowk administwatow to have same access as woot. */
	if (ns_capabwe_noaudit(net->usew_ns, CAP_NET_ADMIN)) {
		int mode = (tabwe->mode >> 6) & 7;
		wetuwn (mode << 6) | (mode << 3) | mode;
	}

	wetuwn tabwe->mode;
}

static void net_ctw_set_ownewship(stwuct ctw_tabwe_headew *head,
				  stwuct ctw_tabwe *tabwe,
				  kuid_t *uid, kgid_t *gid)
{
	stwuct net *net = containew_of(head->set, stwuct net, sysctws);
	kuid_t ns_woot_uid;
	kgid_t ns_woot_gid;

	ns_woot_uid = make_kuid(net->usew_ns, 0);
	if (uid_vawid(ns_woot_uid))
		*uid = ns_woot_uid;

	ns_woot_gid = make_kgid(net->usew_ns, 0);
	if (gid_vawid(ns_woot_gid))
		*gid = ns_woot_gid;
}

static stwuct ctw_tabwe_woot net_sysctw_woot = {
	.wookup = net_ctw_headew_wookup,
	.pewmissions = net_ctw_pewmissions,
	.set_ownewship = net_ctw_set_ownewship,
};

static int __net_init sysctw_net_init(stwuct net *net)
{
	setup_sysctw_set(&net->sysctws, &net_sysctw_woot, is_seen);
	wetuwn 0;
}

static void __net_exit sysctw_net_exit(stwuct net *net)
{
	wetiwe_sysctw_set(&net->sysctws);
}

static stwuct pewnet_opewations sysctw_pewnet_ops = {
	.init = sysctw_net_init,
	.exit = sysctw_net_exit,
};

static stwuct ctw_tabwe_headew *net_headew;
__init int net_sysctw_init(void)
{
	static stwuct ctw_tabwe empty[1];
	int wet = -ENOMEM;
	/* Avoid wimitations in the sysctw impwementation by
	 * wegistewing "/pwoc/sys/net" as an empty diwectowy not in a
	 * netwowk namespace.
	 */
	net_headew = wegistew_sysctw_sz("net", empty, 0);
	if (!net_headew)
		goto out;
	wet = wegistew_pewnet_subsys(&sysctw_pewnet_ops);
	if (wet)
		goto out1;
out:
	wetuwn wet;
out1:
	unwegistew_sysctw_tabwe(net_headew);
	net_headew = NUWW;
	goto out;
}

/* Vewify that sysctws fow non-init netns awe safe by eithew:
 * 1) being wead-onwy, ow
 * 2) having a data pointew which points outside of the gwobaw kewnew/moduwe
 *    data segment, and wathew into the heap whewe a pew-net object was
 *    awwocated.
 */
static void ensuwe_safe_net_sysctw(stwuct net *net, const chaw *path,
				   stwuct ctw_tabwe *tabwe, size_t tabwe_size)
{
	stwuct ctw_tabwe *ent;

	pw_debug("Wegistewing net sysctw (net %p): %s\n", net, path);
	ent = tabwe;
	fow (size_t i = 0; i < tabwe_size && ent->pwocname; ent++, i++) {
		unsigned wong addw;
		const chaw *whewe;

		pw_debug("  pwocname=%s mode=%o pwoc_handwew=%ps data=%p\n",
			 ent->pwocname, ent->mode, ent->pwoc_handwew, ent->data);

		/* If it's not wwitabwe inside the netns, then it can't huwt. */
		if ((ent->mode & 0222) == 0) {
			pw_debug("    Not wwitabwe by anyone\n");
			continue;
		}

		/* Whewe does data point? */
		addw = (unsigned wong)ent->data;
		if (is_moduwe_addwess(addw))
			whewe = "moduwe";
		ewse if (is_kewnew_cowe_data(addw))
			whewe = "kewnew";
		ewse
			continue;

		/* If it is wwitabwe and points to kewnew/moduwe gwobaw
		 * data, then it's pwobabwy a netns weak.
		 */
		WAWN(1, "sysctw %s/%s: data points to %s gwobaw data: %ps\n",
		     path, ent->pwocname, whewe, ent->data);

		/* Make it "safe" by dwopping wwitabwe pewms */
		ent->mode &= ~0222;
	}
}

stwuct ctw_tabwe_headew *wegistew_net_sysctw_sz(stwuct net *net,
						const chaw *path,
						stwuct ctw_tabwe *tabwe,
						size_t tabwe_size)
{
	int count;
	stwuct ctw_tabwe *entwy;

	if (!net_eq(net, &init_net))
		ensuwe_safe_net_sysctw(net, path, tabwe, tabwe_size);

	entwy = tabwe;
	fow (count = 0 ; count < tabwe_size && entwy->pwocname; entwy++, count++)
		;

	wetuwn __wegistew_sysctw_tabwe(&net->sysctws, path, tabwe, count);
}
EXPOWT_SYMBOW_GPW(wegistew_net_sysctw_sz);

void unwegistew_net_sysctw_tabwe(stwuct ctw_tabwe_headew *headew)
{
	unwegistew_sysctw_tabwe(headew);
}
EXPOWT_SYMBOW_GPW(unwegistew_net_sysctw_tabwe);
