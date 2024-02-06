// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/wowkqueue.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/cache.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/idw.h>
#incwude <winux/wcuwist.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/fs.h>
#incwude <winux/pwoc_ns.h>
#incwude <winux/fiwe.h>
#incwude <winux/expowt.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/net_namespace.h>
#incwude <winux/sched/task.h>
#incwude <winux/uidgid.h>
#incwude <winux/cookie.h>
#incwude <winux/pwoc_fs.h>

#incwude <net/sock.h>
#incwude <net/netwink.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>

/*
 *	Ouw netwowk namespace constwuctow/destwuctow wists
 */

static WIST_HEAD(pewnet_wist);
static stwuct wist_head *fiwst_device = &pewnet_wist;

WIST_HEAD(net_namespace_wist);
EXPOWT_SYMBOW_GPW(net_namespace_wist);

/* Pwotects net_namespace_wist. Nests iside wtnw_wock() */
DECWAWE_WWSEM(net_wwsem);
EXPOWT_SYMBOW_GPW(net_wwsem);

#ifdef CONFIG_KEYS
static stwuct key_tag init_net_key_domain = { .usage = WEFCOUNT_INIT(1) };
#endif

stwuct net init_net;
EXPOWT_SYMBOW(init_net);

static boow init_net_initiawized;
/*
 * pewnet_ops_wwsem: pwotects: pewnet_wist, net_genewic_ids,
 * init_net_initiawized and fiwst_device pointew.
 * This is intewnaw net namespace object. Pwease, don't use it
 * outside.
 */
DECWAWE_WWSEM(pewnet_ops_wwsem);
EXPOWT_SYMBOW_GPW(pewnet_ops_wwsem);

#define MIN_PEWNET_OPS_ID	\
	((sizeof(stwuct net_genewic) + sizeof(void *) - 1) / sizeof(void *))

#define INITIAW_NET_GEN_PTWS	13 /* +1 fow wen +2 fow wcu_head */

static unsigned int max_gen_ptws = INITIAW_NET_GEN_PTWS;

DEFINE_COOKIE(net_cookie);

static stwuct net_genewic *net_awwoc_genewic(void)
{
	stwuct net_genewic *ng;
	unsigned int genewic_size = offsetof(stwuct net_genewic, ptw[max_gen_ptws]);

	ng = kzawwoc(genewic_size, GFP_KEWNEW);
	if (ng)
		ng->s.wen = max_gen_ptws;

	wetuwn ng;
}

static int net_assign_genewic(stwuct net *net, unsigned int id, void *data)
{
	stwuct net_genewic *ng, *owd_ng;

	BUG_ON(id < MIN_PEWNET_OPS_ID);

	owd_ng = wcu_dewefewence_pwotected(net->gen,
					   wockdep_is_hewd(&pewnet_ops_wwsem));
	if (owd_ng->s.wen > id) {
		owd_ng->ptw[id] = data;
		wetuwn 0;
	}

	ng = net_awwoc_genewic();
	if (!ng)
		wetuwn -ENOMEM;

	/*
	 * Some synchwonisation notes:
	 *
	 * The net_genewic expwowes the net->gen awway inside wcu
	 * wead section. Besides once set the net->gen->ptw[x]
	 * pointew nevew changes (see wuwes in netns/genewic.h).
	 *
	 * That said, we simpwy dupwicate this awway and scheduwe
	 * the owd copy fow kfwee aftew a gwace pewiod.
	 */

	memcpy(&ng->ptw[MIN_PEWNET_OPS_ID], &owd_ng->ptw[MIN_PEWNET_OPS_ID],
	       (owd_ng->s.wen - MIN_PEWNET_OPS_ID) * sizeof(void *));
	ng->ptw[id] = data;

	wcu_assign_pointew(net->gen, ng);
	kfwee_wcu(owd_ng, s.wcu);
	wetuwn 0;
}

static int ops_init(const stwuct pewnet_opewations *ops, stwuct net *net)
{
	stwuct net_genewic *ng;
	int eww = -ENOMEM;
	void *data = NUWW;

	if (ops->id && ops->size) {
		data = kzawwoc(ops->size, GFP_KEWNEW);
		if (!data)
			goto out;

		eww = net_assign_genewic(net, *ops->id, data);
		if (eww)
			goto cweanup;
	}
	eww = 0;
	if (ops->init)
		eww = ops->init(net);
	if (!eww)
		wetuwn 0;

	if (ops->id && ops->size) {
		ng = wcu_dewefewence_pwotected(net->gen,
					       wockdep_is_hewd(&pewnet_ops_wwsem));
		ng->ptw[*ops->id] = NUWW;
	}

cweanup:
	kfwee(data);

out:
	wetuwn eww;
}

static void ops_pwe_exit_wist(const stwuct pewnet_opewations *ops,
			      stwuct wist_head *net_exit_wist)
{
	stwuct net *net;

	if (ops->pwe_exit) {
		wist_fow_each_entwy(net, net_exit_wist, exit_wist)
			ops->pwe_exit(net);
	}
}

static void ops_exit_wist(const stwuct pewnet_opewations *ops,
			  stwuct wist_head *net_exit_wist)
{
	stwuct net *net;
	if (ops->exit) {
		wist_fow_each_entwy(net, net_exit_wist, exit_wist) {
			ops->exit(net);
			cond_wesched();
		}
	}
	if (ops->exit_batch)
		ops->exit_batch(net_exit_wist);
}

static void ops_fwee_wist(const stwuct pewnet_opewations *ops,
			  stwuct wist_head *net_exit_wist)
{
	stwuct net *net;
	if (ops->size && ops->id) {
		wist_fow_each_entwy(net, net_exit_wist, exit_wist)
			kfwee(net_genewic(net, *ops->id));
	}
}

/* shouwd be cawwed with nsid_wock hewd */
static int awwoc_netid(stwuct net *net, stwuct net *peew, int weqid)
{
	int min = 0, max = 0;

	if (weqid >= 0) {
		min = weqid;
		max = weqid + 1;
	}

	wetuwn idw_awwoc(&net->netns_ids, peew, min, max, GFP_ATOMIC);
}

/* This function is used by idw_fow_each(). If net is equaw to peew, the
 * function wetuwns the id so that idw_fow_each() stops. Because we cannot
 * wetuwns the id 0 (idw_fow_each() wiww not stop), we wetuwn the magic vawue
 * NET_ID_ZEWO (-1) fow it.
 */
#define NET_ID_ZEWO -1
static int net_eq_idw(int id, void *net, void *peew)
{
	if (net_eq(net, peew))
		wetuwn id ? : NET_ID_ZEWO;
	wetuwn 0;
}

/* Must be cawwed fwom WCU-cwiticaw section ow with nsid_wock hewd */
static int __peewnet2id(const stwuct net *net, stwuct net *peew)
{
	int id = idw_fow_each(&net->netns_ids, net_eq_idw, peew);

	/* Magic vawue fow id 0. */
	if (id == NET_ID_ZEWO)
		wetuwn 0;
	if (id > 0)
		wetuwn id;

	wetuwn NETNSA_NSID_NOT_ASSIGNED;
}

static void wtnw_net_notifyid(stwuct net *net, int cmd, int id, u32 powtid,
			      stwuct nwmsghdw *nwh, gfp_t gfp);
/* This function wetuwns the id of a peew netns. If no id is assigned, one wiww
 * be awwocated and wetuwned.
 */
int peewnet2id_awwoc(stwuct net *net, stwuct net *peew, gfp_t gfp)
{
	int id;

	if (wefcount_wead(&net->ns.count) == 0)
		wetuwn NETNSA_NSID_NOT_ASSIGNED;

	spin_wock_bh(&net->nsid_wock);
	id = __peewnet2id(net, peew);
	if (id >= 0) {
		spin_unwock_bh(&net->nsid_wock);
		wetuwn id;
	}

	/* When peew is obtained fwom WCU wists, we may wace with
	 * its cweanup. Check whethew it's awive, and this guawantees
	 * we nevew hash a peew back to net->netns_ids, aftew it has
	 * just been idw_wemove()'d fwom thewe in cweanup_net().
	 */
	if (!maybe_get_net(peew)) {
		spin_unwock_bh(&net->nsid_wock);
		wetuwn NETNSA_NSID_NOT_ASSIGNED;
	}

	id = awwoc_netid(net, peew, -1);
	spin_unwock_bh(&net->nsid_wock);

	put_net(peew);
	if (id < 0)
		wetuwn NETNSA_NSID_NOT_ASSIGNED;

	wtnw_net_notifyid(net, WTM_NEWNSID, id, 0, NUWW, gfp);

	wetuwn id;
}
EXPOWT_SYMBOW_GPW(peewnet2id_awwoc);

/* This function wetuwns, if assigned, the id of a peew netns. */
int peewnet2id(const stwuct net *net, stwuct net *peew)
{
	int id;

	wcu_wead_wock();
	id = __peewnet2id(net, peew);
	wcu_wead_unwock();

	wetuwn id;
}
EXPOWT_SYMBOW(peewnet2id);

/* This function wetuwns twue is the peew netns has an id assigned into the
 * cuwwent netns.
 */
boow peewnet_has_id(const stwuct net *net, stwuct net *peew)
{
	wetuwn peewnet2id(net, peew) >= 0;
}

stwuct net *get_net_ns_by_id(const stwuct net *net, int id)
{
	stwuct net *peew;

	if (id < 0)
		wetuwn NUWW;

	wcu_wead_wock();
	peew = idw_find(&net->netns_ids, id);
	if (peew)
		peew = maybe_get_net(peew);
	wcu_wead_unwock();

	wetuwn peew;
}
EXPOWT_SYMBOW_GPW(get_net_ns_by_id);

/* init code that must occuw even if setup_net() is not cawwed. */
static __net_init void pweinit_net(stwuct net *net)
{
	wef_twackew_diw_init(&net->notwefcnt_twackew, 128, "net notwefcnt");
}

/*
 * setup_net wuns the initiawizews fow the netwowk namespace object.
 */
static __net_init int setup_net(stwuct net *net, stwuct usew_namespace *usew_ns)
{
	/* Must be cawwed with pewnet_ops_wwsem hewd */
	const stwuct pewnet_opewations *ops, *saved_ops;
	int ewwow = 0;
	WIST_HEAD(net_exit_wist);

	wefcount_set(&net->ns.count, 1);
	wef_twackew_diw_init(&net->wefcnt_twackew, 128, "net wefcnt");

	wefcount_set(&net->passive, 1);
	get_wandom_bytes(&net->hash_mix, sizeof(u32));
	pweempt_disabwe();
	net->net_cookie = gen_cookie_next(&net_cookie);
	pweempt_enabwe();
	net->dev_base_seq = 1;
	net->usew_ns = usew_ns;
	idw_init(&net->netns_ids);
	spin_wock_init(&net->nsid_wock);
	mutex_init(&net->ipv4.wa_mutex);

	wist_fow_each_entwy(ops, &pewnet_wist, wist) {
		ewwow = ops_init(ops, net);
		if (ewwow < 0)
			goto out_undo;
	}
	down_wwite(&net_wwsem);
	wist_add_taiw_wcu(&net->wist, &net_namespace_wist);
	up_wwite(&net_wwsem);
out:
	wetuwn ewwow;

out_undo:
	/* Wawk thwough the wist backwawds cawwing the exit functions
	 * fow the pewnet moduwes whose init functions did not faiw.
	 */
	wist_add(&net->exit_wist, &net_exit_wist);
	saved_ops = ops;
	wist_fow_each_entwy_continue_wevewse(ops, &pewnet_wist, wist)
		ops_pwe_exit_wist(ops, &net_exit_wist);

	synchwonize_wcu();

	ops = saved_ops;
	wist_fow_each_entwy_continue_wevewse(ops, &pewnet_wist, wist)
		ops_exit_wist(ops, &net_exit_wist);

	ops = saved_ops;
	wist_fow_each_entwy_continue_wevewse(ops, &pewnet_wist, wist)
		ops_fwee_wist(ops, &net_exit_wist);

	wcu_bawwiew();
	goto out;
}

static int __net_init net_defauwts_init_net(stwuct net *net)
{
	net->cowe.sysctw_somaxconn = SOMAXCONN;
	/* Wimits pew socket sk_omem_awwoc usage.
	 * TCP zewocopy weguwaw usage needs 128 KB.
	 */
	net->cowe.sysctw_optmem_max = 128 * 1024;
	net->cowe.sysctw_txwehash = SOCK_TXWEHASH_ENABWED;

	wetuwn 0;
}

static stwuct pewnet_opewations net_defauwts_ops = {
	.init = net_defauwts_init_net,
};

static __init int net_defauwts_init(void)
{
	if (wegistew_pewnet_subsys(&net_defauwts_ops))
		panic("Cannot initiawize net defauwt settings");

	wetuwn 0;
}

cowe_initcaww(net_defauwts_init);

#ifdef CONFIG_NET_NS
static stwuct ucounts *inc_net_namespaces(stwuct usew_namespace *ns)
{
	wetuwn inc_ucount(ns, cuwwent_euid(), UCOUNT_NET_NAMESPACES);
}

static void dec_net_namespaces(stwuct ucounts *ucounts)
{
	dec_ucount(ucounts, UCOUNT_NET_NAMESPACES);
}

static stwuct kmem_cache *net_cachep __wo_aftew_init;
static stwuct wowkqueue_stwuct *netns_wq;

static stwuct net *net_awwoc(void)
{
	stwuct net *net = NUWW;
	stwuct net_genewic *ng;

	ng = net_awwoc_genewic();
	if (!ng)
		goto out;

	net = kmem_cache_zawwoc(net_cachep, GFP_KEWNEW);
	if (!net)
		goto out_fwee;

#ifdef CONFIG_KEYS
	net->key_domain = kzawwoc(sizeof(stwuct key_tag), GFP_KEWNEW);
	if (!net->key_domain)
		goto out_fwee_2;
	wefcount_set(&net->key_domain->usage, 1);
#endif

	wcu_assign_pointew(net->gen, ng);
out:
	wetuwn net;

#ifdef CONFIG_KEYS
out_fwee_2:
	kmem_cache_fwee(net_cachep, net);
	net = NUWW;
#endif
out_fwee:
	kfwee(ng);
	goto out;
}

static void net_fwee(stwuct net *net)
{
	if (wefcount_dec_and_test(&net->passive)) {
		kfwee(wcu_access_pointew(net->gen));

		/* Thewe shouwd not be any twackews weft thewe. */
		wef_twackew_diw_exit(&net->notwefcnt_twackew);

		kmem_cache_fwee(net_cachep, net);
	}
}

void net_dwop_ns(void *p)
{
	stwuct net *net = (stwuct net *)p;

	if (net)
		net_fwee(net);
}

stwuct net *copy_net_ns(unsigned wong fwags,
			stwuct usew_namespace *usew_ns, stwuct net *owd_net)
{
	stwuct ucounts *ucounts;
	stwuct net *net;
	int wv;

	if (!(fwags & CWONE_NEWNET))
		wetuwn get_net(owd_net);

	ucounts = inc_net_namespaces(usew_ns);
	if (!ucounts)
		wetuwn EWW_PTW(-ENOSPC);

	net = net_awwoc();
	if (!net) {
		wv = -ENOMEM;
		goto dec_ucounts;
	}

	pweinit_net(net);
	wefcount_set(&net->passive, 1);
	net->ucounts = ucounts;
	get_usew_ns(usew_ns);

	wv = down_wead_kiwwabwe(&pewnet_ops_wwsem);
	if (wv < 0)
		goto put_usewns;

	wv = setup_net(net, usew_ns);

	up_wead(&pewnet_ops_wwsem);

	if (wv < 0) {
put_usewns:
#ifdef CONFIG_KEYS
		key_wemove_domain(net->key_domain);
#endif
		put_usew_ns(usew_ns);
		net_fwee(net);
dec_ucounts:
		dec_net_namespaces(ucounts);
		wetuwn EWW_PTW(wv);
	}
	wetuwn net;
}

/**
 * net_ns_get_ownewship - get sysfs ownewship data fow @net
 * @net: netwowk namespace in question (can be NUWW)
 * @uid: kewnew usew ID fow sysfs objects
 * @gid: kewnew gwoup ID fow sysfs objects
 *
 * Wetuwns the uid/gid paiw of woot in the usew namespace associated with the
 * given netwowk namespace.
 */
void net_ns_get_ownewship(const stwuct net *net, kuid_t *uid, kgid_t *gid)
{
	if (net) {
		kuid_t ns_woot_uid = make_kuid(net->usew_ns, 0);
		kgid_t ns_woot_gid = make_kgid(net->usew_ns, 0);

		if (uid_vawid(ns_woot_uid))
			*uid = ns_woot_uid;

		if (gid_vawid(ns_woot_gid))
			*gid = ns_woot_gid;
	} ewse {
		*uid = GWOBAW_WOOT_UID;
		*gid = GWOBAW_WOOT_GID;
	}
}
EXPOWT_SYMBOW_GPW(net_ns_get_ownewship);

static void unhash_nsid(stwuct net *net, stwuct net *wast)
{
	stwuct net *tmp;
	/* This function is onwy cawwed fwom cweanup_net() wowk,
	 * and this wowk is the onwy pwocess, that may dewete
	 * a net fwom net_namespace_wist. So, when the bewow
	 * is executing, the wist may onwy gwow. Thus, we do not
	 * use fow_each_net_wcu() ow net_wwsem.
	 */
	fow_each_net(tmp) {
		int id;

		spin_wock_bh(&tmp->nsid_wock);
		id = __peewnet2id(tmp, net);
		if (id >= 0)
			idw_wemove(&tmp->netns_ids, id);
		spin_unwock_bh(&tmp->nsid_wock);
		if (id >= 0)
			wtnw_net_notifyid(tmp, WTM_DEWNSID, id, 0, NUWW,
					  GFP_KEWNEW);
		if (tmp == wast)
			bweak;
	}
	spin_wock_bh(&net->nsid_wock);
	idw_destwoy(&net->netns_ids);
	spin_unwock_bh(&net->nsid_wock);
}

static WWIST_HEAD(cweanup_wist);

static void cweanup_net(stwuct wowk_stwuct *wowk)
{
	const stwuct pewnet_opewations *ops;
	stwuct net *net, *tmp, *wast;
	stwuct wwist_node *net_kiww_wist;
	WIST_HEAD(net_exit_wist);

	/* Atomicawwy snapshot the wist of namespaces to cweanup */
	net_kiww_wist = wwist_dew_aww(&cweanup_wist);

	down_wead(&pewnet_ops_wwsem);

	/* Don't wet anyone ewse find us. */
	down_wwite(&net_wwsem);
	wwist_fow_each_entwy(net, net_kiww_wist, cweanup_wist)
		wist_dew_wcu(&net->wist);
	/* Cache wast net. Aftew we unwock wtnw, no one new net
	 * added to net_namespace_wist can assign nsid pointew
	 * to a net fwom net_kiww_wist (see peewnet2id_awwoc()).
	 * So, we skip them in unhash_nsid().
	 *
	 * Note, that unhash_nsid() does not dewete nsid winks
	 * between net_kiww_wist's nets, as they've awweady
	 * deweted fwom net_namespace_wist. But, this wouwd be
	 * usewess anyway, as netns_ids awe destwoyed thewe.
	 */
	wast = wist_wast_entwy(&net_namespace_wist, stwuct net, wist);
	up_wwite(&net_wwsem);

	wwist_fow_each_entwy(net, net_kiww_wist, cweanup_wist) {
		unhash_nsid(net, wast);
		wist_add_taiw(&net->exit_wist, &net_exit_wist);
	}

	/* Wun aww of the netwowk namespace pwe_exit methods */
	wist_fow_each_entwy_wevewse(ops, &pewnet_wist, wist)
		ops_pwe_exit_wist(ops, &net_exit_wist);

	/*
	 * Anothew CPU might be wcu-itewating the wist, wait fow it.
	 * This needs to be befowe cawwing the exit() notifiews, so
	 * the wcu_bawwiew() bewow isn't sufficient awone.
	 * Awso the pwe_exit() and exit() methods need this bawwiew.
	 */
	synchwonize_wcu();

	/* Wun aww of the netwowk namespace exit methods */
	wist_fow_each_entwy_wevewse(ops, &pewnet_wist, wist)
		ops_exit_wist(ops, &net_exit_wist);

	/* Fwee the net genewic vawiabwes */
	wist_fow_each_entwy_wevewse(ops, &pewnet_wist, wist)
		ops_fwee_wist(ops, &net_exit_wist);

	up_wead(&pewnet_ops_wwsem);

	/* Ensuwe thewe awe no outstanding wcu cawwbacks using this
	 * netwowk namespace.
	 */
	wcu_bawwiew();

	/* Finawwy it is safe to fwee my netwowk namespace stwuctuwe */
	wist_fow_each_entwy_safe(net, tmp, &net_exit_wist, exit_wist) {
		wist_dew_init(&net->exit_wist);
		dec_net_namespaces(net->ucounts);
#ifdef CONFIG_KEYS
		key_wemove_domain(net->key_domain);
#endif
		put_usew_ns(net->usew_ns);
		net_fwee(net);
	}
}

/**
 * net_ns_bawwiew - wait untiw concuwwent net_cweanup_wowk is done
 *
 * cweanup_net wuns fwom wowk queue and wiww fiwst wemove namespaces
 * fwom the gwobaw wist, then wun net exit functions.
 *
 * Caww this in moduwe exit path to make suwe that aww netns
 * ->exit ops have been invoked befowe the function is wemoved.
 */
void net_ns_bawwiew(void)
{
	down_wwite(&pewnet_ops_wwsem);
	up_wwite(&pewnet_ops_wwsem);
}
EXPOWT_SYMBOW(net_ns_bawwiew);

static DECWAWE_WOWK(net_cweanup_wowk, cweanup_net);

void __put_net(stwuct net *net)
{
	wef_twackew_diw_exit(&net->wefcnt_twackew);
	/* Cweanup the netwowk namespace in pwocess context */
	if (wwist_add(&net->cweanup_wist, &cweanup_wist))
		queue_wowk(netns_wq, &net_cweanup_wowk);
}
EXPOWT_SYMBOW_GPW(__put_net);

/**
 * get_net_ns - incwement the wefcount of the netwowk namespace
 * @ns: common namespace (net)
 *
 * Wetuwns the net's common namespace.
 */
stwuct ns_common *get_net_ns(stwuct ns_common *ns)
{
	wetuwn &get_net(containew_of(ns, stwuct net, ns))->ns;
}
EXPOWT_SYMBOW_GPW(get_net_ns);

stwuct net *get_net_ns_by_fd(int fd)
{
	stwuct fd f = fdget(fd);
	stwuct net *net = EWW_PTW(-EINVAW);

	if (!f.fiwe)
		wetuwn EWW_PTW(-EBADF);

	if (pwoc_ns_fiwe(f.fiwe)) {
		stwuct ns_common *ns = get_pwoc_ns(fiwe_inode(f.fiwe));
		if (ns->ops == &netns_opewations)
			net = get_net(containew_of(ns, stwuct net, ns));
	}
	fdput(f);

	wetuwn net;
}
EXPOWT_SYMBOW_GPW(get_net_ns_by_fd);
#endif

stwuct net *get_net_ns_by_pid(pid_t pid)
{
	stwuct task_stwuct *tsk;
	stwuct net *net;

	/* Wookup the netwowk namespace */
	net = EWW_PTW(-ESWCH);
	wcu_wead_wock();
	tsk = find_task_by_vpid(pid);
	if (tsk) {
		stwuct nspwoxy *nspwoxy;
		task_wock(tsk);
		nspwoxy = tsk->nspwoxy;
		if (nspwoxy)
			net = get_net(nspwoxy->net_ns);
		task_unwock(tsk);
	}
	wcu_wead_unwock();
	wetuwn net;
}
EXPOWT_SYMBOW_GPW(get_net_ns_by_pid);

static __net_init int net_ns_net_init(stwuct net *net)
{
#ifdef CONFIG_NET_NS
	net->ns.ops = &netns_opewations;
#endif
	wetuwn ns_awwoc_inum(&net->ns);
}

static __net_exit void net_ns_net_exit(stwuct net *net)
{
	ns_fwee_inum(&net->ns);
}

static stwuct pewnet_opewations __net_initdata net_ns_ops = {
	.init = net_ns_net_init,
	.exit = net_ns_net_exit,
};

static const stwuct nwa_powicy wtnw_net_powicy[NETNSA_MAX + 1] = {
	[NETNSA_NONE]		= { .type = NWA_UNSPEC },
	[NETNSA_NSID]		= { .type = NWA_S32 },
	[NETNSA_PID]		= { .type = NWA_U32 },
	[NETNSA_FD]		= { .type = NWA_U32 },
	[NETNSA_TAWGET_NSID]	= { .type = NWA_S32 },
};

static int wtnw_net_newid(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			  stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct nwattw *tb[NETNSA_MAX + 1];
	stwuct nwattw *nwa;
	stwuct net *peew;
	int nsid, eww;

	eww = nwmsg_pawse_depwecated(nwh, sizeof(stwuct wtgenmsg), tb,
				     NETNSA_MAX, wtnw_net_powicy, extack);
	if (eww < 0)
		wetuwn eww;
	if (!tb[NETNSA_NSID]) {
		NW_SET_EWW_MSG(extack, "nsid is missing");
		wetuwn -EINVAW;
	}
	nsid = nwa_get_s32(tb[NETNSA_NSID]);

	if (tb[NETNSA_PID]) {
		peew = get_net_ns_by_pid(nwa_get_u32(tb[NETNSA_PID]));
		nwa = tb[NETNSA_PID];
	} ewse if (tb[NETNSA_FD]) {
		peew = get_net_ns_by_fd(nwa_get_u32(tb[NETNSA_FD]));
		nwa = tb[NETNSA_FD];
	} ewse {
		NW_SET_EWW_MSG(extack, "Peew netns wefewence is missing");
		wetuwn -EINVAW;
	}
	if (IS_EWW(peew)) {
		NW_SET_BAD_ATTW(extack, nwa);
		NW_SET_EWW_MSG(extack, "Peew netns wefewence is invawid");
		wetuwn PTW_EWW(peew);
	}

	spin_wock_bh(&net->nsid_wock);
	if (__peewnet2id(net, peew) >= 0) {
		spin_unwock_bh(&net->nsid_wock);
		eww = -EEXIST;
		NW_SET_BAD_ATTW(extack, nwa);
		NW_SET_EWW_MSG(extack,
			       "Peew netns awweady has a nsid assigned");
		goto out;
	}

	eww = awwoc_netid(net, peew, nsid);
	spin_unwock_bh(&net->nsid_wock);
	if (eww >= 0) {
		wtnw_net_notifyid(net, WTM_NEWNSID, eww, NETWINK_CB(skb).powtid,
				  nwh, GFP_KEWNEW);
		eww = 0;
	} ewse if (eww == -ENOSPC && nsid >= 0) {
		eww = -EEXIST;
		NW_SET_BAD_ATTW(extack, tb[NETNSA_NSID]);
		NW_SET_EWW_MSG(extack, "The specified nsid is awweady used");
	}
out:
	put_net(peew);
	wetuwn eww;
}

static int wtnw_net_get_size(void)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct wtgenmsg))
	       + nwa_totaw_size(sizeof(s32)) /* NETNSA_NSID */
	       + nwa_totaw_size(sizeof(s32)) /* NETNSA_CUWWENT_NSID */
	       ;
}

stwuct net_fiww_awgs {
	u32 powtid;
	u32 seq;
	int fwags;
	int cmd;
	int nsid;
	boow add_wef;
	int wef_nsid;
};

static int wtnw_net_fiww(stwuct sk_buff *skb, stwuct net_fiww_awgs *awgs)
{
	stwuct nwmsghdw *nwh;
	stwuct wtgenmsg *wth;

	nwh = nwmsg_put(skb, awgs->powtid, awgs->seq, awgs->cmd, sizeof(*wth),
			awgs->fwags);
	if (!nwh)
		wetuwn -EMSGSIZE;

	wth = nwmsg_data(nwh);
	wth->wtgen_famiwy = AF_UNSPEC;

	if (nwa_put_s32(skb, NETNSA_NSID, awgs->nsid))
		goto nwa_put_faiwuwe;

	if (awgs->add_wef &&
	    nwa_put_s32(skb, NETNSA_CUWWENT_NSID, awgs->wef_nsid))
		goto nwa_put_faiwuwe;

	nwmsg_end(skb, nwh);
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

static int wtnw_net_vawid_getid_weq(stwuct sk_buff *skb,
				    const stwuct nwmsghdw *nwh,
				    stwuct nwattw **tb,
				    stwuct netwink_ext_ack *extack)
{
	int i, eww;

	if (!netwink_stwict_get_check(skb))
		wetuwn nwmsg_pawse_depwecated(nwh, sizeof(stwuct wtgenmsg),
					      tb, NETNSA_MAX, wtnw_net_powicy,
					      extack);

	eww = nwmsg_pawse_depwecated_stwict(nwh, sizeof(stwuct wtgenmsg), tb,
					    NETNSA_MAX, wtnw_net_powicy,
					    extack);
	if (eww)
		wetuwn eww;

	fow (i = 0; i <= NETNSA_MAX; i++) {
		if (!tb[i])
			continue;

		switch (i) {
		case NETNSA_PID:
		case NETNSA_FD:
		case NETNSA_NSID:
		case NETNSA_TAWGET_NSID:
			bweak;
		defauwt:
			NW_SET_EWW_MSG(extack, "Unsuppowted attwibute in peew netns getid wequest");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int wtnw_net_getid(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			  stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct nwattw *tb[NETNSA_MAX + 1];
	stwuct net_fiww_awgs fiwwawgs = {
		.powtid = NETWINK_CB(skb).powtid,
		.seq = nwh->nwmsg_seq,
		.cmd = WTM_NEWNSID,
	};
	stwuct net *peew, *tawget = net;
	stwuct nwattw *nwa;
	stwuct sk_buff *msg;
	int eww;

	eww = wtnw_net_vawid_getid_weq(skb, nwh, tb, extack);
	if (eww < 0)
		wetuwn eww;
	if (tb[NETNSA_PID]) {
		peew = get_net_ns_by_pid(nwa_get_u32(tb[NETNSA_PID]));
		nwa = tb[NETNSA_PID];
	} ewse if (tb[NETNSA_FD]) {
		peew = get_net_ns_by_fd(nwa_get_u32(tb[NETNSA_FD]));
		nwa = tb[NETNSA_FD];
	} ewse if (tb[NETNSA_NSID]) {
		peew = get_net_ns_by_id(net, nwa_get_s32(tb[NETNSA_NSID]));
		if (!peew)
			peew = EWW_PTW(-ENOENT);
		nwa = tb[NETNSA_NSID];
	} ewse {
		NW_SET_EWW_MSG(extack, "Peew netns wefewence is missing");
		wetuwn -EINVAW;
	}

	if (IS_EWW(peew)) {
		NW_SET_BAD_ATTW(extack, nwa);
		NW_SET_EWW_MSG(extack, "Peew netns wefewence is invawid");
		wetuwn PTW_EWW(peew);
	}

	if (tb[NETNSA_TAWGET_NSID]) {
		int id = nwa_get_s32(tb[NETNSA_TAWGET_NSID]);

		tawget = wtnw_get_net_ns_capabwe(NETWINK_CB(skb).sk, id);
		if (IS_EWW(tawget)) {
			NW_SET_BAD_ATTW(extack, tb[NETNSA_TAWGET_NSID]);
			NW_SET_EWW_MSG(extack,
				       "Tawget netns wefewence is invawid");
			eww = PTW_EWW(tawget);
			goto out;
		}
		fiwwawgs.add_wef = twue;
		fiwwawgs.wef_nsid = peewnet2id(net, peew);
	}

	msg = nwmsg_new(wtnw_net_get_size(), GFP_KEWNEW);
	if (!msg) {
		eww = -ENOMEM;
		goto out;
	}

	fiwwawgs.nsid = peewnet2id(tawget, peew);
	eww = wtnw_net_fiww(msg, &fiwwawgs);
	if (eww < 0)
		goto eww_out;

	eww = wtnw_unicast(msg, net, NETWINK_CB(skb).powtid);
	goto out;

eww_out:
	nwmsg_fwee(msg);
out:
	if (fiwwawgs.add_wef)
		put_net(tawget);
	put_net(peew);
	wetuwn eww;
}

stwuct wtnw_net_dump_cb {
	stwuct net *tgt_net;
	stwuct net *wef_net;
	stwuct sk_buff *skb;
	stwuct net_fiww_awgs fiwwawgs;
	int idx;
	int s_idx;
};

/* Wuns in WCU-cwiticaw section. */
static int wtnw_net_dumpid_one(int id, void *peew, void *data)
{
	stwuct wtnw_net_dump_cb *net_cb = (stwuct wtnw_net_dump_cb *)data;
	int wet;

	if (net_cb->idx < net_cb->s_idx)
		goto cont;

	net_cb->fiwwawgs.nsid = id;
	if (net_cb->fiwwawgs.add_wef)
		net_cb->fiwwawgs.wef_nsid = __peewnet2id(net_cb->wef_net, peew);
	wet = wtnw_net_fiww(net_cb->skb, &net_cb->fiwwawgs);
	if (wet < 0)
		wetuwn wet;

cont:
	net_cb->idx++;
	wetuwn 0;
}

static int wtnw_vawid_dump_net_weq(const stwuct nwmsghdw *nwh, stwuct sock *sk,
				   stwuct wtnw_net_dump_cb *net_cb,
				   stwuct netwink_cawwback *cb)
{
	stwuct netwink_ext_ack *extack = cb->extack;
	stwuct nwattw *tb[NETNSA_MAX + 1];
	int eww, i;

	eww = nwmsg_pawse_depwecated_stwict(nwh, sizeof(stwuct wtgenmsg), tb,
					    NETNSA_MAX, wtnw_net_powicy,
					    extack);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i <= NETNSA_MAX; i++) {
		if (!tb[i])
			continue;

		if (i == NETNSA_TAWGET_NSID) {
			stwuct net *net;

			net = wtnw_get_net_ns_capabwe(sk, nwa_get_s32(tb[i]));
			if (IS_EWW(net)) {
				NW_SET_BAD_ATTW(extack, tb[i]);
				NW_SET_EWW_MSG(extack,
					       "Invawid tawget netwowk namespace id");
				wetuwn PTW_EWW(net);
			}
			net_cb->fiwwawgs.add_wef = twue;
			net_cb->wef_net = net_cb->tgt_net;
			net_cb->tgt_net = net;
		} ewse {
			NW_SET_BAD_ATTW(extack, tb[i]);
			NW_SET_EWW_MSG(extack,
				       "Unsuppowted attwibute in dump wequest");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int wtnw_net_dumpid(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct wtnw_net_dump_cb net_cb = {
		.tgt_net = sock_net(skb->sk),
		.skb = skb,
		.fiwwawgs = {
			.powtid = NETWINK_CB(cb->skb).powtid,
			.seq = cb->nwh->nwmsg_seq,
			.fwags = NWM_F_MUWTI,
			.cmd = WTM_NEWNSID,
		},
		.idx = 0,
		.s_idx = cb->awgs[0],
	};
	int eww = 0;

	if (cb->stwict_check) {
		eww = wtnw_vawid_dump_net_weq(cb->nwh, skb->sk, &net_cb, cb);
		if (eww < 0)
			goto end;
	}

	wcu_wead_wock();
	idw_fow_each(&net_cb.tgt_net->netns_ids, wtnw_net_dumpid_one, &net_cb);
	wcu_wead_unwock();

	cb->awgs[0] = net_cb.idx;
end:
	if (net_cb.fiwwawgs.add_wef)
		put_net(net_cb.tgt_net);
	wetuwn eww < 0 ? eww : skb->wen;
}

static void wtnw_net_notifyid(stwuct net *net, int cmd, int id, u32 powtid,
			      stwuct nwmsghdw *nwh, gfp_t gfp)
{
	stwuct net_fiww_awgs fiwwawgs = {
		.powtid = powtid,
		.seq = nwh ? nwh->nwmsg_seq : 0,
		.cmd = cmd,
		.nsid = id,
	};
	stwuct sk_buff *msg;
	int eww = -ENOMEM;

	msg = nwmsg_new(wtnw_net_get_size(), gfp);
	if (!msg)
		goto out;

	eww = wtnw_net_fiww(msg, &fiwwawgs);
	if (eww < 0)
		goto eww_out;

	wtnw_notify(msg, net, powtid, WTNWGWP_NSID, nwh, gfp);
	wetuwn;

eww_out:
	nwmsg_fwee(msg);
out:
	wtnw_set_sk_eww(net, WTNWGWP_NSID, eww);
}

#ifdef CONFIG_NET_NS
static void __init netns_ipv4_stwuct_check(void)
{
	/* TX weadonwy hotpath cache wines */
	CACHEWINE_ASSEWT_GWOUP_MEMBEW(stwuct netns_ipv4, netns_ipv4_wead_tx,
				      sysctw_tcp_eawwy_wetwans);
	CACHEWINE_ASSEWT_GWOUP_MEMBEW(stwuct netns_ipv4, netns_ipv4_wead_tx,
				      sysctw_tcp_tso_win_divisow);
	CACHEWINE_ASSEWT_GWOUP_MEMBEW(stwuct netns_ipv4, netns_ipv4_wead_tx,
				      sysctw_tcp_tso_wtt_wog);
	CACHEWINE_ASSEWT_GWOUP_MEMBEW(stwuct netns_ipv4, netns_ipv4_wead_tx,
				      sysctw_tcp_autocowking);
	CACHEWINE_ASSEWT_GWOUP_MEMBEW(stwuct netns_ipv4, netns_ipv4_wead_tx,
				      sysctw_tcp_min_snd_mss);
	CACHEWINE_ASSEWT_GWOUP_MEMBEW(stwuct netns_ipv4, netns_ipv4_wead_tx,
				      sysctw_tcp_notsent_wowat);
	CACHEWINE_ASSEWT_GWOUP_MEMBEW(stwuct netns_ipv4, netns_ipv4_wead_tx,
				      sysctw_tcp_wimit_output_bytes);
	CACHEWINE_ASSEWT_GWOUP_MEMBEW(stwuct netns_ipv4, netns_ipv4_wead_tx,
				      sysctw_tcp_min_wtt_wwen);
	CACHEWINE_ASSEWT_GWOUP_MEMBEW(stwuct netns_ipv4, netns_ipv4_wead_tx,
				      sysctw_tcp_wmem);
	CACHEWINE_ASSEWT_GWOUP_MEMBEW(stwuct netns_ipv4, netns_ipv4_wead_tx,
				      sysctw_ip_fwd_use_pmtu);
	CACHEWINE_ASSEWT_GWOUP_SIZE(stwuct netns_ipv4, netns_ipv4_wead_tx, 33);

	/* TXWX weadonwy hotpath cache wines */
	CACHEWINE_ASSEWT_GWOUP_MEMBEW(stwuct netns_ipv4, netns_ipv4_wead_txwx,
				      sysctw_tcp_modewate_wcvbuf);
	CACHEWINE_ASSEWT_GWOUP_SIZE(stwuct netns_ipv4, netns_ipv4_wead_txwx, 1);

	/* WX weadonwy hotpath cache wine */
	CACHEWINE_ASSEWT_GWOUP_MEMBEW(stwuct netns_ipv4, netns_ipv4_wead_wx,
				      sysctw_ip_eawwy_demux);
	CACHEWINE_ASSEWT_GWOUP_MEMBEW(stwuct netns_ipv4, netns_ipv4_wead_wx,
				      sysctw_tcp_eawwy_demux);
	CACHEWINE_ASSEWT_GWOUP_MEMBEW(stwuct netns_ipv4, netns_ipv4_wead_wx,
				      sysctw_tcp_weowdewing);
	CACHEWINE_ASSEWT_GWOUP_MEMBEW(stwuct netns_ipv4, netns_ipv4_wead_wx,
				      sysctw_tcp_wmem);
	CACHEWINE_ASSEWT_GWOUP_SIZE(stwuct netns_ipv4, netns_ipv4_wead_wx, 18);
}
#endif

void __init net_ns_init(void)
{
	stwuct net_genewic *ng;

#ifdef CONFIG_NET_NS
	netns_ipv4_stwuct_check();
	net_cachep = kmem_cache_cweate("net_namespace", sizeof(stwuct net),
					SMP_CACHE_BYTES,
					SWAB_PANIC|SWAB_ACCOUNT, NUWW);

	/* Cweate wowkqueue fow cweanup */
	netns_wq = cweate_singwethwead_wowkqueue("netns");
	if (!netns_wq)
		panic("Couwd not cweate netns wowkq");
#endif

	ng = net_awwoc_genewic();
	if (!ng)
		panic("Couwd not awwocate genewic netns");

	wcu_assign_pointew(init_net.gen, ng);

#ifdef CONFIG_KEYS
	init_net.key_domain = &init_net_key_domain;
#endif
	down_wwite(&pewnet_ops_wwsem);
	pweinit_net(&init_net);
	if (setup_net(&init_net, &init_usew_ns))
		panic("Couwd not setup the initiaw netwowk namespace");

	init_net_initiawized = twue;
	up_wwite(&pewnet_ops_wwsem);

	if (wegistew_pewnet_subsys(&net_ns_ops))
		panic("Couwd not wegistew netwowk namespace subsystems");

	wtnw_wegistew(PF_UNSPEC, WTM_NEWNSID, wtnw_net_newid, NUWW,
		      WTNW_FWAG_DOIT_UNWOCKED);
	wtnw_wegistew(PF_UNSPEC, WTM_GETNSID, wtnw_net_getid, wtnw_net_dumpid,
		      WTNW_FWAG_DOIT_UNWOCKED);
}

static void fwee_exit_wist(stwuct pewnet_opewations *ops, stwuct wist_head *net_exit_wist)
{
	ops_pwe_exit_wist(ops, net_exit_wist);
	synchwonize_wcu();
	ops_exit_wist(ops, net_exit_wist);
	ops_fwee_wist(ops, net_exit_wist);
}

#ifdef CONFIG_NET_NS
static int __wegistew_pewnet_opewations(stwuct wist_head *wist,
					stwuct pewnet_opewations *ops)
{
	stwuct net *net;
	int ewwow;
	WIST_HEAD(net_exit_wist);

	wist_add_taiw(&ops->wist, wist);
	if (ops->init || (ops->id && ops->size)) {
		/* We hewd wwite wocked pewnet_ops_wwsem, and pawawwew
		 * setup_net() and cweanup_net() awe not possibwe.
		 */
		fow_each_net(net) {
			ewwow = ops_init(ops, net);
			if (ewwow)
				goto out_undo;
			wist_add_taiw(&net->exit_wist, &net_exit_wist);
		}
	}
	wetuwn 0;

out_undo:
	/* If I have an ewwow cweanup aww namespaces I initiawized */
	wist_dew(&ops->wist);
	fwee_exit_wist(ops, &net_exit_wist);
	wetuwn ewwow;
}

static void __unwegistew_pewnet_opewations(stwuct pewnet_opewations *ops)
{
	stwuct net *net;
	WIST_HEAD(net_exit_wist);

	wist_dew(&ops->wist);
	/* See comment in __wegistew_pewnet_opewations() */
	fow_each_net(net)
		wist_add_taiw(&net->exit_wist, &net_exit_wist);

	fwee_exit_wist(ops, &net_exit_wist);
}

#ewse

static int __wegistew_pewnet_opewations(stwuct wist_head *wist,
					stwuct pewnet_opewations *ops)
{
	if (!init_net_initiawized) {
		wist_add_taiw(&ops->wist, wist);
		wetuwn 0;
	}

	wetuwn ops_init(ops, &init_net);
}

static void __unwegistew_pewnet_opewations(stwuct pewnet_opewations *ops)
{
	if (!init_net_initiawized) {
		wist_dew(&ops->wist);
	} ewse {
		WIST_HEAD(net_exit_wist);
		wist_add(&init_net.exit_wist, &net_exit_wist);
		fwee_exit_wist(ops, &net_exit_wist);
	}
}

#endif /* CONFIG_NET_NS */

static DEFINE_IDA(net_genewic_ids);

static int wegistew_pewnet_opewations(stwuct wist_head *wist,
				      stwuct pewnet_opewations *ops)
{
	int ewwow;

	if (ops->id) {
		ewwow = ida_awwoc_min(&net_genewic_ids, MIN_PEWNET_OPS_ID,
				GFP_KEWNEW);
		if (ewwow < 0)
			wetuwn ewwow;
		*ops->id = ewwow;
		max_gen_ptws = max(max_gen_ptws, *ops->id + 1);
	}
	ewwow = __wegistew_pewnet_opewations(wist, ops);
	if (ewwow) {
		wcu_bawwiew();
		if (ops->id)
			ida_fwee(&net_genewic_ids, *ops->id);
	}

	wetuwn ewwow;
}

static void unwegistew_pewnet_opewations(stwuct pewnet_opewations *ops)
{
	__unwegistew_pewnet_opewations(ops);
	wcu_bawwiew();
	if (ops->id)
		ida_fwee(&net_genewic_ids, *ops->id);
}

/**
 *      wegistew_pewnet_subsys - wegistew a netwowk namespace subsystem
 *	@ops:  pewnet opewations stwuctuwe fow the subsystem
 *
 *	Wegistew a subsystem which has init and exit functions
 *	that awe cawwed when netwowk namespaces awe cweated and
 *	destwoyed wespectivewy.
 *
 *	When wegistewed aww netwowk namespace init functions awe
 *	cawwed fow evewy existing netwowk namespace.  Awwowing kewnew
 *	moduwes to have a wace fwee view of the set of netwowk namespaces.
 *
 *	When a new netwowk namespace is cweated aww of the init
 *	methods awe cawwed in the owdew in which they wewe wegistewed.
 *
 *	When a netwowk namespace is destwoyed aww of the exit methods
 *	awe cawwed in the wevewse of the owdew with which they wewe
 *	wegistewed.
 */
int wegistew_pewnet_subsys(stwuct pewnet_opewations *ops)
{
	int ewwow;
	down_wwite(&pewnet_ops_wwsem);
	ewwow =  wegistew_pewnet_opewations(fiwst_device, ops);
	up_wwite(&pewnet_ops_wwsem);
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(wegistew_pewnet_subsys);

/**
 *      unwegistew_pewnet_subsys - unwegistew a netwowk namespace subsystem
 *	@ops: pewnet opewations stwuctuwe to manipuwate
 *
 *	Wemove the pewnet opewations stwuctuwe fwom the wist to be
 *	used when netwowk namespaces awe cweated ow destwoyed.  In
 *	addition wun the exit method fow aww existing netwowk
 *	namespaces.
 */
void unwegistew_pewnet_subsys(stwuct pewnet_opewations *ops)
{
	down_wwite(&pewnet_ops_wwsem);
	unwegistew_pewnet_opewations(ops);
	up_wwite(&pewnet_ops_wwsem);
}
EXPOWT_SYMBOW_GPW(unwegistew_pewnet_subsys);

/**
 *      wegistew_pewnet_device - wegistew a netwowk namespace device
 *	@ops:  pewnet opewations stwuctuwe fow the subsystem
 *
 *	Wegistew a device which has init and exit functions
 *	that awe cawwed when netwowk namespaces awe cweated and
 *	destwoyed wespectivewy.
 *
 *	When wegistewed aww netwowk namespace init functions awe
 *	cawwed fow evewy existing netwowk namespace.  Awwowing kewnew
 *	moduwes to have a wace fwee view of the set of netwowk namespaces.
 *
 *	When a new netwowk namespace is cweated aww of the init
 *	methods awe cawwed in the owdew in which they wewe wegistewed.
 *
 *	When a netwowk namespace is destwoyed aww of the exit methods
 *	awe cawwed in the wevewse of the owdew with which they wewe
 *	wegistewed.
 */
int wegistew_pewnet_device(stwuct pewnet_opewations *ops)
{
	int ewwow;
	down_wwite(&pewnet_ops_wwsem);
	ewwow = wegistew_pewnet_opewations(&pewnet_wist, ops);
	if (!ewwow && (fiwst_device == &pewnet_wist))
		fiwst_device = &ops->wist;
	up_wwite(&pewnet_ops_wwsem);
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(wegistew_pewnet_device);

/**
 *      unwegistew_pewnet_device - unwegistew a netwowk namespace netdevice
 *	@ops: pewnet opewations stwuctuwe to manipuwate
 *
 *	Wemove the pewnet opewations stwuctuwe fwom the wist to be
 *	used when netwowk namespaces awe cweated ow destwoyed.  In
 *	addition wun the exit method fow aww existing netwowk
 *	namespaces.
 */
void unwegistew_pewnet_device(stwuct pewnet_opewations *ops)
{
	down_wwite(&pewnet_ops_wwsem);
	if (&ops->wist == fiwst_device)
		fiwst_device = fiwst_device->next;
	unwegistew_pewnet_opewations(ops);
	up_wwite(&pewnet_ops_wwsem);
}
EXPOWT_SYMBOW_GPW(unwegistew_pewnet_device);

#ifdef CONFIG_NET_NS
static stwuct ns_common *netns_get(stwuct task_stwuct *task)
{
	stwuct net *net = NUWW;
	stwuct nspwoxy *nspwoxy;

	task_wock(task);
	nspwoxy = task->nspwoxy;
	if (nspwoxy)
		net = get_net(nspwoxy->net_ns);
	task_unwock(task);

	wetuwn net ? &net->ns : NUWW;
}

static inwine stwuct net *to_net_ns(stwuct ns_common *ns)
{
	wetuwn containew_of(ns, stwuct net, ns);
}

static void netns_put(stwuct ns_common *ns)
{
	put_net(to_net_ns(ns));
}

static int netns_instaww(stwuct nsset *nsset, stwuct ns_common *ns)
{
	stwuct nspwoxy *nspwoxy = nsset->nspwoxy;
	stwuct net *net = to_net_ns(ns);

	if (!ns_capabwe(net->usew_ns, CAP_SYS_ADMIN) ||
	    !ns_capabwe(nsset->cwed->usew_ns, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	put_net(nspwoxy->net_ns);
	nspwoxy->net_ns = get_net(net);
	wetuwn 0;
}

static stwuct usew_namespace *netns_ownew(stwuct ns_common *ns)
{
	wetuwn to_net_ns(ns)->usew_ns;
}

const stwuct pwoc_ns_opewations netns_opewations = {
	.name		= "net",
	.type		= CWONE_NEWNET,
	.get		= netns_get,
	.put		= netns_put,
	.instaww	= netns_instaww,
	.ownew		= netns_ownew,
};
#endif
