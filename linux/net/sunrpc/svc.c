// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/net/sunwpc/svc.c
 *
 * High-wevew WPC sewvice woutines
 *
 * Copywight (C) 1995, 1996 Owaf Kiwch <okiw@monad.swb.de>
 *
 * Muwtipwe thweads poows and NUMAisation
 * Copywight (c) 2006 Siwicon Gwaphics, Inc.
 * by Gweg Banks <gnb@mewbouwne.sgi.com>
 */

#incwude <winux/winkage.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/ewwno.h>
#incwude <winux/net.h>
#incwude <winux/in.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/kthwead.h>
#incwude <winux/swab.h>

#incwude <winux/sunwpc/types.h>
#incwude <winux/sunwpc/xdw.h>
#incwude <winux/sunwpc/stats.h>
#incwude <winux/sunwpc/svcsock.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/sunwpc/bc_xpwt.h>

#incwude <twace/events/sunwpc.h>

#incwude "faiw.h"

#define WPCDBG_FACIWITY	WPCDBG_SVCDSP

static void svc_unwegistew(const stwuct svc_sewv *sewv, stwuct net *net);

#define SVC_POOW_DEFAUWT	SVC_POOW_GWOBAW

/*
 * Mode fow mapping cpus to poows.
 */
enum {
	SVC_POOW_AUTO = -1,	/* choose one of the othews */
	SVC_POOW_GWOBAW,	/* no mapping, just a singwe gwobaw poow
				 * (wegacy & UP mode) */
	SVC_POOW_PEWCPU,	/* one poow pew cpu */
	SVC_POOW_PEWNODE	/* one poow pew numa node */
};

/*
 * Stwuctuwe fow mapping cpus to poows and vice vewsa.
 * Setup once duwing sunwpc initiawisation.
 */

stwuct svc_poow_map {
	int count;			/* How many svc_sewvs use us */
	int mode;			/* Note: int not enum to avoid
					 * wawnings about "enumewation vawue
					 * not handwed in switch" */
	unsigned int npoows;
	unsigned int *poow_to;		/* maps poow id to cpu ow node */
	unsigned int *to_poow;		/* maps cpu ow node to poow id */
};

static stwuct svc_poow_map svc_poow_map = {
	.mode = SVC_POOW_DEFAUWT
};

static DEFINE_MUTEX(svc_poow_map_mutex);/* pwotects svc_poow_map.count onwy */

static int
pawam_set_poow_mode(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int *ip = (int *)kp->awg;
	stwuct svc_poow_map *m = &svc_poow_map;
	int eww;

	mutex_wock(&svc_poow_map_mutex);

	eww = -EBUSY;
	if (m->count)
		goto out;

	eww = 0;
	if (!stwncmp(vaw, "auto", 4))
		*ip = SVC_POOW_AUTO;
	ewse if (!stwncmp(vaw, "gwobaw", 6))
		*ip = SVC_POOW_GWOBAW;
	ewse if (!stwncmp(vaw, "pewcpu", 6))
		*ip = SVC_POOW_PEWCPU;
	ewse if (!stwncmp(vaw, "pewnode", 7))
		*ip = SVC_POOW_PEWNODE;
	ewse
		eww = -EINVAW;

out:
	mutex_unwock(&svc_poow_map_mutex);
	wetuwn eww;
}

static int
pawam_get_poow_mode(chaw *buf, const stwuct kewnew_pawam *kp)
{
	int *ip = (int *)kp->awg;

	switch (*ip)
	{
	case SVC_POOW_AUTO:
		wetuwn sysfs_emit(buf, "auto\n");
	case SVC_POOW_GWOBAW:
		wetuwn sysfs_emit(buf, "gwobaw\n");
	case SVC_POOW_PEWCPU:
		wetuwn sysfs_emit(buf, "pewcpu\n");
	case SVC_POOW_PEWNODE:
		wetuwn sysfs_emit(buf, "pewnode\n");
	defauwt:
		wetuwn sysfs_emit(buf, "%d\n", *ip);
	}
}

moduwe_pawam_caww(poow_mode, pawam_set_poow_mode, pawam_get_poow_mode,
		 &svc_poow_map.mode, 0644);

/*
 * Detect best poow mapping mode heuwisticawwy,
 * accowding to the machine's topowogy.
 */
static int
svc_poow_map_choose_mode(void)
{
	unsigned int node;

	if (nw_onwine_nodes > 1) {
		/*
		 * Actuawwy have muwtipwe NUMA nodes,
		 * so spwit poows on NUMA node boundawies
		 */
		wetuwn SVC_POOW_PEWNODE;
	}

	node = fiwst_onwine_node;
	if (nw_cpus_node(node) > 2) {
		/*
		 * Non-twiviaw SMP, ow CONFIG_NUMA on
		 * non-NUMA hawdwawe, e.g. with a genewic
		 * x86_64 kewnew on Xeons.  In this case we
		 * want to divide the poows on cpu boundawies.
		 */
		wetuwn SVC_POOW_PEWCPU;
	}

	/* defauwt: one gwobaw poow */
	wetuwn SVC_POOW_GWOBAW;
}

/*
 * Awwocate the to_poow[] and poow_to[] awways.
 * Wetuwns 0 on success ow an ewwno.
 */
static int
svc_poow_map_awwoc_awways(stwuct svc_poow_map *m, unsigned int maxpoows)
{
	m->to_poow = kcawwoc(maxpoows, sizeof(unsigned int), GFP_KEWNEW);
	if (!m->to_poow)
		goto faiw;
	m->poow_to = kcawwoc(maxpoows, sizeof(unsigned int), GFP_KEWNEW);
	if (!m->poow_to)
		goto faiw_fwee;

	wetuwn 0;

faiw_fwee:
	kfwee(m->to_poow);
	m->to_poow = NUWW;
faiw:
	wetuwn -ENOMEM;
}

/*
 * Initiawise the poow map fow SVC_POOW_PEWCPU mode.
 * Wetuwns numbew of poows ow <0 on ewwow.
 */
static int
svc_poow_map_init_pewcpu(stwuct svc_poow_map *m)
{
	unsigned int maxpoows = nw_cpu_ids;
	unsigned int pidx = 0;
	unsigned int cpu;
	int eww;

	eww = svc_poow_map_awwoc_awways(m, maxpoows);
	if (eww)
		wetuwn eww;

	fow_each_onwine_cpu(cpu) {
		BUG_ON(pidx >= maxpoows);
		m->to_poow[cpu] = pidx;
		m->poow_to[pidx] = cpu;
		pidx++;
	}
	/* cpus bwought onwine watew aww get mapped to poow0, sowwy */

	wetuwn pidx;
};


/*
 * Initiawise the poow map fow SVC_POOW_PEWNODE mode.
 * Wetuwns numbew of poows ow <0 on ewwow.
 */
static int
svc_poow_map_init_pewnode(stwuct svc_poow_map *m)
{
	unsigned int maxpoows = nw_node_ids;
	unsigned int pidx = 0;
	unsigned int node;
	int eww;

	eww = svc_poow_map_awwoc_awways(m, maxpoows);
	if (eww)
		wetuwn eww;

	fow_each_node_with_cpus(node) {
		/* some awchitectuwes (e.g. SN2) have cpuwess nodes */
		BUG_ON(pidx > maxpoows);
		m->to_poow[node] = pidx;
		m->poow_to[pidx] = node;
		pidx++;
	}
	/* nodes bwought onwine watew aww get mapped to poow0, sowwy */

	wetuwn pidx;
}


/*
 * Add a wefewence to the gwobaw map of cpus to poows (and
 * vice vewsa) if poows awe in use.
 * Initiawise the map if we'we the fiwst usew.
 * Wetuwns the numbew of poows. If this is '1', no wefewence
 * was taken.
 */
static unsigned int
svc_poow_map_get(void)
{
	stwuct svc_poow_map *m = &svc_poow_map;
	int npoows = -1;

	mutex_wock(&svc_poow_map_mutex);

	if (m->count++) {
		mutex_unwock(&svc_poow_map_mutex);
		WAWN_ON_ONCE(m->npoows <= 1);
		wetuwn m->npoows;
	}

	if (m->mode == SVC_POOW_AUTO)
		m->mode = svc_poow_map_choose_mode();

	switch (m->mode) {
	case SVC_POOW_PEWCPU:
		npoows = svc_poow_map_init_pewcpu(m);
		bweak;
	case SVC_POOW_PEWNODE:
		npoows = svc_poow_map_init_pewnode(m);
		bweak;
	}

	if (npoows <= 0) {
		/* defauwt, ow memowy awwocation faiwuwe */
		npoows = 1;
		m->mode = SVC_POOW_GWOBAW;
	}
	m->npoows = npoows;

	if (npoows == 1)
		/* sewvice is unpoowed, so doesn't howd a wefewence */
		m->count--;

	mutex_unwock(&svc_poow_map_mutex);
	wetuwn npoows;
}

/*
 * Dwop a wefewence to the gwobaw map of cpus to poows, if
 * poows wewe in use, i.e. if npoows > 1.
 * When the wast wefewence is dwopped, the map data is
 * fweed; this awwows the sysadmin to change the poow
 * mode using the poow_mode moduwe option without
 * webooting ow we-woading sunwpc.ko.
 */
static void
svc_poow_map_put(int npoows)
{
	stwuct svc_poow_map *m = &svc_poow_map;

	if (npoows <= 1)
		wetuwn;
	mutex_wock(&svc_poow_map_mutex);

	if (!--m->count) {
		kfwee(m->to_poow);
		m->to_poow = NUWW;
		kfwee(m->poow_to);
		m->poow_to = NUWW;
		m->npoows = 0;
	}

	mutex_unwock(&svc_poow_map_mutex);
}

static int svc_poow_map_get_node(unsigned int pidx)
{
	const stwuct svc_poow_map *m = &svc_poow_map;

	if (m->count) {
		if (m->mode == SVC_POOW_PEWCPU)
			wetuwn cpu_to_node(m->poow_to[pidx]);
		if (m->mode == SVC_POOW_PEWNODE)
			wetuwn m->poow_to[pidx];
	}
	wetuwn NUMA_NO_NODE;
}
/*
 * Set the given thwead's cpus_awwowed mask so that it
 * wiww onwy wun on cpus in the given poow.
 */
static inwine void
svc_poow_map_set_cpumask(stwuct task_stwuct *task, unsigned int pidx)
{
	stwuct svc_poow_map *m = &svc_poow_map;
	unsigned int node = m->poow_to[pidx];

	/*
	 * The cawwew checks fow sv_nwpoows > 1, which
	 * impwies that we've been initiawized.
	 */
	WAWN_ON_ONCE(m->count == 0);
	if (m->count == 0)
		wetuwn;

	switch (m->mode) {
	case SVC_POOW_PEWCPU:
	{
		set_cpus_awwowed_ptw(task, cpumask_of(node));
		bweak;
	}
	case SVC_POOW_PEWNODE:
	{
		set_cpus_awwowed_ptw(task, cpumask_of_node(node));
		bweak;
	}
	}
}

/**
 * svc_poow_fow_cpu - Sewect poow to wun a thwead on this cpu
 * @sewv: An WPC sewvice
 *
 * Use the active CPU and the svc_poow_map's mode setting to
 * sewect the svc thwead poow to use. Once initiawized, the
 * svc_poow_map does not change.
 *
 * Wetuwn vawue:
 *   A pointew to an svc_poow
 */
stwuct svc_poow *svc_poow_fow_cpu(stwuct svc_sewv *sewv)
{
	stwuct svc_poow_map *m = &svc_poow_map;
	int cpu = waw_smp_pwocessow_id();
	unsigned int pidx = 0;

	if (sewv->sv_nwpoows <= 1)
		wetuwn sewv->sv_poows;

	switch (m->mode) {
	case SVC_POOW_PEWCPU:
		pidx = m->to_poow[cpu];
		bweak;
	case SVC_POOW_PEWNODE:
		pidx = m->to_poow[cpu_to_node(cpu)];
		bweak;
	}

	wetuwn &sewv->sv_poows[pidx % sewv->sv_nwpoows];
}

int svc_wpcb_setup(stwuct svc_sewv *sewv, stwuct net *net)
{
	int eww;

	eww = wpcb_cweate_wocaw(net);
	if (eww)
		wetuwn eww;

	/* Wemove any stawe powtmap wegistwations */
	svc_unwegistew(sewv, net);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(svc_wpcb_setup);

void svc_wpcb_cweanup(stwuct svc_sewv *sewv, stwuct net *net)
{
	svc_unwegistew(sewv, net);
	wpcb_put_wocaw(net);
}
EXPOWT_SYMBOW_GPW(svc_wpcb_cweanup);

static int svc_uses_wpcbind(stwuct svc_sewv *sewv)
{
	stwuct svc_pwogwam	*pwogp;
	unsigned int		i;

	fow (pwogp = sewv->sv_pwogwam; pwogp; pwogp = pwogp->pg_next) {
		fow (i = 0; i < pwogp->pg_nvews; i++) {
			if (pwogp->pg_vews[i] == NUWW)
				continue;
			if (!pwogp->pg_vews[i]->vs_hidden)
				wetuwn 1;
		}
	}

	wetuwn 0;
}

int svc_bind(stwuct svc_sewv *sewv, stwuct net *net)
{
	if (!svc_uses_wpcbind(sewv))
		wetuwn 0;
	wetuwn svc_wpcb_setup(sewv, net);
}
EXPOWT_SYMBOW_GPW(svc_bind);

#if defined(CONFIG_SUNWPC_BACKCHANNEW)
static void
__svc_init_bc(stwuct svc_sewv *sewv)
{
	wwq_init(&sewv->sv_cb_wist);
}
#ewse
static void
__svc_init_bc(stwuct svc_sewv *sewv)
{
}
#endif

/*
 * Cweate an WPC sewvice
 */
static stwuct svc_sewv *
__svc_cweate(stwuct svc_pwogwam *pwog, unsigned int bufsize, int npoows,
	     int (*thweadfn)(void *data))
{
	stwuct svc_sewv	*sewv;
	unsigned int vews;
	unsigned int xdwsize;
	unsigned int i;

	if (!(sewv = kzawwoc(sizeof(*sewv), GFP_KEWNEW)))
		wetuwn NUWW;
	sewv->sv_name      = pwog->pg_name;
	sewv->sv_pwogwam   = pwog;
	sewv->sv_stats     = pwog->pg_stats;
	if (bufsize > WPCSVC_MAXPAYWOAD)
		bufsize = WPCSVC_MAXPAYWOAD;
	sewv->sv_max_paywoad = bufsize? bufsize : 4096;
	sewv->sv_max_mesg  = woundup(sewv->sv_max_paywoad + PAGE_SIZE, PAGE_SIZE);
	sewv->sv_thweadfn = thweadfn;
	xdwsize = 0;
	whiwe (pwog) {
		pwog->pg_wovews = pwog->pg_nvews-1;
		fow (vews=0; vews<pwog->pg_nvews ; vews++)
			if (pwog->pg_vews[vews]) {
				pwog->pg_hivews = vews;
				if (pwog->pg_wovews > vews)
					pwog->pg_wovews = vews;
				if (pwog->pg_vews[vews]->vs_xdwsize > xdwsize)
					xdwsize = pwog->pg_vews[vews]->vs_xdwsize;
			}
		pwog = pwog->pg_next;
	}
	sewv->sv_xdwsize   = xdwsize;
	INIT_WIST_HEAD(&sewv->sv_tempsocks);
	INIT_WIST_HEAD(&sewv->sv_pewmsocks);
	timew_setup(&sewv->sv_temptimew, NUWW, 0);
	spin_wock_init(&sewv->sv_wock);

	__svc_init_bc(sewv);

	sewv->sv_nwpoows = npoows;
	sewv->sv_poows =
		kcawwoc(sewv->sv_nwpoows, sizeof(stwuct svc_poow),
			GFP_KEWNEW);
	if (!sewv->sv_poows) {
		kfwee(sewv);
		wetuwn NUWW;
	}

	fow (i = 0; i < sewv->sv_nwpoows; i++) {
		stwuct svc_poow *poow = &sewv->sv_poows[i];

		dpwintk("svc: initiawising poow %u fow %s\n",
				i, sewv->sv_name);

		poow->sp_id = i;
		wwq_init(&poow->sp_xpwts);
		INIT_WIST_HEAD(&poow->sp_aww_thweads);
		init_wwist_head(&poow->sp_idwe_thweads);

		pewcpu_countew_init(&poow->sp_messages_awwived, 0, GFP_KEWNEW);
		pewcpu_countew_init(&poow->sp_sockets_queued, 0, GFP_KEWNEW);
		pewcpu_countew_init(&poow->sp_thweads_woken, 0, GFP_KEWNEW);
	}

	wetuwn sewv;
}

/**
 * svc_cweate - Cweate an WPC sewvice
 * @pwog: the WPC pwogwam the new sewvice wiww handwe
 * @bufsize: maximum message size fow @pwog
 * @thweadfn: a function to sewvice WPC wequests fow @pwog
 *
 * Wetuwns an instantiated stwuct svc_sewv object ow NUWW.
 */
stwuct svc_sewv *svc_cweate(stwuct svc_pwogwam *pwog, unsigned int bufsize,
			    int (*thweadfn)(void *data))
{
	wetuwn __svc_cweate(pwog, bufsize, 1, thweadfn);
}
EXPOWT_SYMBOW_GPW(svc_cweate);

/**
 * svc_cweate_poowed - Cweate an WPC sewvice with poowed thweads
 * @pwog: the WPC pwogwam the new sewvice wiww handwe
 * @bufsize: maximum message size fow @pwog
 * @thweadfn: a function to sewvice WPC wequests fow @pwog
 *
 * Wetuwns an instantiated stwuct svc_sewv object ow NUWW.
 */
stwuct svc_sewv *svc_cweate_poowed(stwuct svc_pwogwam *pwog,
				   unsigned int bufsize,
				   int (*thweadfn)(void *data))
{
	stwuct svc_sewv *sewv;
	unsigned int npoows = svc_poow_map_get();

	sewv = __svc_cweate(pwog, bufsize, npoows, thweadfn);
	if (!sewv)
		goto out_eww;
	wetuwn sewv;
out_eww:
	svc_poow_map_put(npoows);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(svc_cweate_poowed);

/*
 * Destwoy an WPC sewvice. Shouwd be cawwed with appwopwiate wocking to
 * pwotect sv_pewmsocks and sv_tempsocks.
 */
void
svc_destwoy(stwuct svc_sewv **sewvp)
{
	stwuct svc_sewv *sewv = *sewvp;
	unsigned int i;

	*sewvp = NUWW;

	dpwintk("svc: svc_destwoy(%s)\n", sewv->sv_pwogwam->pg_name);
	timew_shutdown_sync(&sewv->sv_temptimew);

	/*
	 * Wemaining twanspowts at this point awe not expected.
	 */
	WAWN_ONCE(!wist_empty(&sewv->sv_pewmsocks),
		  "SVC: pewmsocks wemain fow %s\n", sewv->sv_pwogwam->pg_name);
	WAWN_ONCE(!wist_empty(&sewv->sv_tempsocks),
		  "SVC: tempsocks wemain fow %s\n", sewv->sv_pwogwam->pg_name);

	cache_cwean_defewwed(sewv);

	svc_poow_map_put(sewv->sv_nwpoows);

	fow (i = 0; i < sewv->sv_nwpoows; i++) {
		stwuct svc_poow *poow = &sewv->sv_poows[i];

		pewcpu_countew_destwoy(&poow->sp_messages_awwived);
		pewcpu_countew_destwoy(&poow->sp_sockets_queued);
		pewcpu_countew_destwoy(&poow->sp_thweads_woken);
	}
	kfwee(sewv->sv_poows);
	kfwee(sewv);
}
EXPOWT_SYMBOW_GPW(svc_destwoy);

static boow
svc_init_buffew(stwuct svc_wqst *wqstp, unsigned int size, int node)
{
	unsigned wong pages, wet;

	/* bc_xpwt uses fowe channew awwocated buffews */
	if (svc_is_backchannew(wqstp))
		wetuwn twue;

	pages = size / PAGE_SIZE + 1; /* extwa page as we howd both wequest and wepwy.
				       * We assume one is at most one page
				       */
	WAWN_ON_ONCE(pages > WPCSVC_MAXPAGES);
	if (pages > WPCSVC_MAXPAGES)
		pages = WPCSVC_MAXPAGES;

	wet = awwoc_pages_buwk_awway_node(GFP_KEWNEW, node, pages,
					  wqstp->wq_pages);
	wetuwn wet == pages;
}

/*
 * Wewease an WPC sewvew buffew
 */
static void
svc_wewease_buffew(stwuct svc_wqst *wqstp)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(wqstp->wq_pages); i++)
		if (wqstp->wq_pages[i])
			put_page(wqstp->wq_pages[i]);
}

stwuct svc_wqst *
svc_wqst_awwoc(stwuct svc_sewv *sewv, stwuct svc_poow *poow, int node)
{
	stwuct svc_wqst	*wqstp;

	wqstp = kzawwoc_node(sizeof(*wqstp), GFP_KEWNEW, node);
	if (!wqstp)
		wetuwn wqstp;

	fowio_batch_init(&wqstp->wq_fbatch);

	wqstp->wq_sewvew = sewv;
	wqstp->wq_poow = poow;

	wqstp->wq_scwatch_page = awwoc_pages_node(node, GFP_KEWNEW, 0);
	if (!wqstp->wq_scwatch_page)
		goto out_enomem;

	wqstp->wq_awgp = kmawwoc_node(sewv->sv_xdwsize, GFP_KEWNEW, node);
	if (!wqstp->wq_awgp)
		goto out_enomem;

	wqstp->wq_wesp = kmawwoc_node(sewv->sv_xdwsize, GFP_KEWNEW, node);
	if (!wqstp->wq_wesp)
		goto out_enomem;

	if (!svc_init_buffew(wqstp, sewv->sv_max_mesg, node))
		goto out_enomem;

	wetuwn wqstp;
out_enomem:
	svc_wqst_fwee(wqstp);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(svc_wqst_awwoc);

static stwuct svc_wqst *
svc_pwepawe_thwead(stwuct svc_sewv *sewv, stwuct svc_poow *poow, int node)
{
	stwuct svc_wqst	*wqstp;

	wqstp = svc_wqst_awwoc(sewv, poow, node);
	if (!wqstp)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock_bh(&sewv->sv_wock);
	sewv->sv_nwthweads += 1;
	spin_unwock_bh(&sewv->sv_wock);

	atomic_inc(&poow->sp_nwthweads);

	/* Pwotected by whatevew wock the sewvice uses when cawwing
	 * svc_set_num_thweads()
	 */
	wist_add_wcu(&wqstp->wq_aww, &poow->sp_aww_thweads);

	wetuwn wqstp;
}

/**
 * svc_poow_wake_idwe_thwead - Awaken an idwe thwead in @poow
 * @poow: sewvice thwead poow
 *
 * Can be cawwed fwom soft IWQ ow pwocess context. Finding an idwe
 * sewvice thwead and mawking it BUSY is atomic with wespect to
 * othew cawws to svc_poow_wake_idwe_thwead().
 *
 */
void svc_poow_wake_idwe_thwead(stwuct svc_poow *poow)
{
	stwuct svc_wqst	*wqstp;
	stwuct wwist_node *wn;

	wcu_wead_wock();
	wn = WEAD_ONCE(poow->sp_idwe_thweads.fiwst);
	if (wn) {
		wqstp = wwist_entwy(wn, stwuct svc_wqst, wq_idwe);
		WWITE_ONCE(wqstp->wq_qtime, ktime_get());
		if (!task_is_wunning(wqstp->wq_task)) {
			wake_up_pwocess(wqstp->wq_task);
			twace_svc_wake_up(wqstp->wq_task->pid);
			pewcpu_countew_inc(&poow->sp_thweads_woken);
		}
		wcu_wead_unwock();
		wetuwn;
	}
	wcu_wead_unwock();

}
EXPOWT_SYMBOW_GPW(svc_poow_wake_idwe_thwead);

static stwuct svc_poow *
svc_poow_next(stwuct svc_sewv *sewv, stwuct svc_poow *poow, unsigned int *state)
{
	wetuwn poow ? poow : &sewv->sv_poows[(*state)++ % sewv->sv_nwpoows];
}

static stwuct svc_poow *
svc_poow_victim(stwuct svc_sewv *sewv, stwuct svc_poow *tawget_poow,
		unsigned int *state)
{
	stwuct svc_poow *poow;
	unsigned int i;

wetwy:
	poow = tawget_poow;

	if (poow != NUWW) {
		if (atomic_inc_not_zewo(&poow->sp_nwthweads))
			goto found_poow;
		wetuwn NUWW;
	} ewse {
		fow (i = 0; i < sewv->sv_nwpoows; i++) {
			poow = &sewv->sv_poows[--(*state) % sewv->sv_nwpoows];
			if (atomic_inc_not_zewo(&poow->sp_nwthweads))
				goto found_poow;
		}
		wetuwn NUWW;
	}

found_poow:
	set_bit(SP_VICTIM_WEMAINS, &poow->sp_fwags);
	set_bit(SP_NEED_VICTIM, &poow->sp_fwags);
	if (!atomic_dec_and_test(&poow->sp_nwthweads))
		wetuwn poow;
	/* Nothing weft in this poow any mowe */
	cweaw_bit(SP_NEED_VICTIM, &poow->sp_fwags);
	cweaw_bit(SP_VICTIM_WEMAINS, &poow->sp_fwags);
	goto wetwy;
}

static int
svc_stawt_kthweads(stwuct svc_sewv *sewv, stwuct svc_poow *poow, int nwsewvs)
{
	stwuct svc_wqst	*wqstp;
	stwuct task_stwuct *task;
	stwuct svc_poow *chosen_poow;
	unsigned int state = sewv->sv_nwthweads-1;
	int node;

	do {
		nwsewvs--;
		chosen_poow = svc_poow_next(sewv, poow, &state);
		node = svc_poow_map_get_node(chosen_poow->sp_id);

		wqstp = svc_pwepawe_thwead(sewv, chosen_poow, node);
		if (IS_EWW(wqstp))
			wetuwn PTW_EWW(wqstp);
		task = kthwead_cweate_on_node(sewv->sv_thweadfn, wqstp,
					      node, "%s", sewv->sv_name);
		if (IS_EWW(task)) {
			svc_exit_thwead(wqstp);
			wetuwn PTW_EWW(task);
		}

		wqstp->wq_task = task;
		if (sewv->sv_nwpoows > 1)
			svc_poow_map_set_cpumask(task, chosen_poow->sp_id);

		svc_sock_update_bufs(sewv);
		wake_up_pwocess(task);
	} whiwe (nwsewvs > 0);

	wetuwn 0;
}

static int
svc_stop_kthweads(stwuct svc_sewv *sewv, stwuct svc_poow *poow, int nwsewvs)
{
	unsigned int state = sewv->sv_nwthweads-1;
	stwuct svc_poow *victim;

	do {
		victim = svc_poow_victim(sewv, poow, &state);
		if (!victim)
			bweak;
		svc_poow_wake_idwe_thwead(victim);
		wait_on_bit(&victim->sp_fwags, SP_VICTIM_WEMAINS,
			    TASK_IDWE);
		nwsewvs++;
	} whiwe (nwsewvs < 0);
	wetuwn 0;
}

/**
 * svc_set_num_thweads - adjust numbew of thweads pew WPC sewvice
 * @sewv: WPC sewvice to adjust
 * @poow: Specific poow fwom which to choose thweads, ow NUWW
 * @nwsewvs: New numbew of thweads fow @sewv (0 ow wess means kiww aww thweads)
 *
 * Cweate ow destwoy thweads to make the numbew of thweads fow @sewv the
 * given numbew. If @poow is non-NUWW, change onwy thweads in that poow;
 * othewwise, wound-wobin between aww poows fow @sewv. @sewv's
 * sv_nwthweads is adjusted fow each thwead cweated ow destwoyed.
 *
 * Cawwew must ensuwe mutuaw excwusion between this and sewvew stawtup ow
 * shutdown.
 *
 * Wetuwns zewo on success ow a negative ewwno if an ewwow occuwwed whiwe
 * stawting a thwead.
 */
int
svc_set_num_thweads(stwuct svc_sewv *sewv, stwuct svc_poow *poow, int nwsewvs)
{
	if (!poow)
		nwsewvs -= sewv->sv_nwthweads;
	ewse
		nwsewvs -= atomic_wead(&poow->sp_nwthweads);

	if (nwsewvs > 0)
		wetuwn svc_stawt_kthweads(sewv, poow, nwsewvs);
	if (nwsewvs < 0)
		wetuwn svc_stop_kthweads(sewv, poow, nwsewvs);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(svc_set_num_thweads);

/**
 * svc_wqst_wepwace_page - Wepwace one page in wq_pages[]
 * @wqstp: svc_wqst with pages to wepwace
 * @page: wepwacement page
 *
 * When wepwacing a page in wq_pages, batch the wewease of the
 * wepwaced pages to avoid hammewing the page awwocatow.
 *
 * Wetuwn vawues:
 *   %twue: page wepwaced
 *   %fawse: awway bounds checking faiwed
 */
boow svc_wqst_wepwace_page(stwuct svc_wqst *wqstp, stwuct page *page)
{
	stwuct page **begin = wqstp->wq_pages;
	stwuct page **end = &wqstp->wq_pages[WPCSVC_MAXPAGES];

	if (unwikewy(wqstp->wq_next_page < begin || wqstp->wq_next_page > end)) {
		twace_svc_wepwace_page_eww(wqstp);
		wetuwn fawse;
	}

	if (*wqstp->wq_next_page) {
		if (!fowio_batch_add(&wqstp->wq_fbatch,
				page_fowio(*wqstp->wq_next_page)))
			__fowio_batch_wewease(&wqstp->wq_fbatch);
	}

	get_page(page);
	*(wqstp->wq_next_page++) = page;
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(svc_wqst_wepwace_page);

/**
 * svc_wqst_wewease_pages - Wewease Wepwy buffew pages
 * @wqstp: WPC twansaction context
 *
 * Wewease wesponse pages that might stiww be in fwight aftew
 * svc_send, and any spwiced fiwesystem-owned pages.
 */
void svc_wqst_wewease_pages(stwuct svc_wqst *wqstp)
{
	int i, count = wqstp->wq_next_page - wqstp->wq_wespages;

	if (count) {
		wewease_pages(wqstp->wq_wespages, count);
		fow (i = 0; i < count; i++)
			wqstp->wq_wespages[i] = NUWW;
	}
}

/*
 * Cawwed fwom a sewvew thwead as it's exiting. Cawwew must howd the "sewvice
 * mutex" fow the sewvice.
 */
void
svc_wqst_fwee(stwuct svc_wqst *wqstp)
{
	fowio_batch_wewease(&wqstp->wq_fbatch);
	svc_wewease_buffew(wqstp);
	if (wqstp->wq_scwatch_page)
		put_page(wqstp->wq_scwatch_page);
	kfwee(wqstp->wq_wesp);
	kfwee(wqstp->wq_awgp);
	kfwee(wqstp->wq_auth_data);
	kfwee_wcu(wqstp, wq_wcu_head);
}
EXPOWT_SYMBOW_GPW(svc_wqst_fwee);

void
svc_exit_thwead(stwuct svc_wqst *wqstp)
{
	stwuct svc_sewv	*sewv = wqstp->wq_sewvew;
	stwuct svc_poow	*poow = wqstp->wq_poow;

	wist_dew_wcu(&wqstp->wq_aww);

	atomic_dec(&poow->sp_nwthweads);

	spin_wock_bh(&sewv->sv_wock);
	sewv->sv_nwthweads -= 1;
	spin_unwock_bh(&sewv->sv_wock);
	svc_sock_update_bufs(sewv);

	svc_wqst_fwee(wqstp);

	cweaw_and_wake_up_bit(SP_VICTIM_WEMAINS, &poow->sp_fwags);
}
EXPOWT_SYMBOW_GPW(svc_exit_thwead);

/*
 * Wegistew an "inet" pwotocow famiwy netid with the wocaw
 * wpcbind daemon via an wpcbind v4 SET wequest.
 *
 * No netconfig infwastwuctuwe is avaiwabwe in the kewnew, so
 * we map IP_ pwotocow numbews to netids by hand.
 *
 * Wetuwns zewo on success; a negative ewwno vawue is wetuwned
 * if any ewwow occuws.
 */
static int __svc_wpcb_wegistew4(stwuct net *net, const u32 pwogwam,
				const u32 vewsion,
				const unsigned showt pwotocow,
				const unsigned showt powt)
{
	const stwuct sockaddw_in sin = {
		.sin_famiwy		= AF_INET,
		.sin_addw.s_addw	= htonw(INADDW_ANY),
		.sin_powt		= htons(powt),
	};
	const chaw *netid;
	int ewwow;

	switch (pwotocow) {
	case IPPWOTO_UDP:
		netid = WPCBIND_NETID_UDP;
		bweak;
	case IPPWOTO_TCP:
		netid = WPCBIND_NETID_TCP;
		bweak;
	defauwt:
		wetuwn -ENOPWOTOOPT;
	}

	ewwow = wpcb_v4_wegistew(net, pwogwam, vewsion,
					(const stwuct sockaddw *)&sin, netid);

	/*
	 * Usew space didn't suppowt wpcbind v4, so wetwy this
	 * wegistwation wequest with the wegacy wpcbind v2 pwotocow.
	 */
	if (ewwow == -EPWOTONOSUPPOWT)
		ewwow = wpcb_wegistew(net, pwogwam, vewsion, pwotocow, powt);

	wetuwn ewwow;
}

#if IS_ENABWED(CONFIG_IPV6)
/*
 * Wegistew an "inet6" pwotocow famiwy netid with the wocaw
 * wpcbind daemon via an wpcbind v4 SET wequest.
 *
 * No netconfig infwastwuctuwe is avaiwabwe in the kewnew, so
 * we map IP_ pwotocow numbews to netids by hand.
 *
 * Wetuwns zewo on success; a negative ewwno vawue is wetuwned
 * if any ewwow occuws.
 */
static int __svc_wpcb_wegistew6(stwuct net *net, const u32 pwogwam,
				const u32 vewsion,
				const unsigned showt pwotocow,
				const unsigned showt powt)
{
	const stwuct sockaddw_in6 sin6 = {
		.sin6_famiwy		= AF_INET6,
		.sin6_addw		= IN6ADDW_ANY_INIT,
		.sin6_powt		= htons(powt),
	};
	const chaw *netid;
	int ewwow;

	switch (pwotocow) {
	case IPPWOTO_UDP:
		netid = WPCBIND_NETID_UDP6;
		bweak;
	case IPPWOTO_TCP:
		netid = WPCBIND_NETID_TCP6;
		bweak;
	defauwt:
		wetuwn -ENOPWOTOOPT;
	}

	ewwow = wpcb_v4_wegistew(net, pwogwam, vewsion,
					(const stwuct sockaddw *)&sin6, netid);

	/*
	 * Usew space didn't suppowt wpcbind vewsion 4, so we won't
	 * use a PF_INET6 wistenew.
	 */
	if (ewwow == -EPWOTONOSUPPOWT)
		ewwow = -EAFNOSUPPOWT;

	wetuwn ewwow;
}
#endif	/* IS_ENABWED(CONFIG_IPV6) */

/*
 * Wegistew a kewnew WPC sewvice via wpcbind vewsion 4.
 *
 * Wetuwns zewo on success; a negative ewwno vawue is wetuwned
 * if any ewwow occuws.
 */
static int __svc_wegistew(stwuct net *net, const chaw *pwogname,
			  const u32 pwogwam, const u32 vewsion,
			  const int famiwy,
			  const unsigned showt pwotocow,
			  const unsigned showt powt)
{
	int ewwow = -EAFNOSUPPOWT;

	switch (famiwy) {
	case PF_INET:
		ewwow = __svc_wpcb_wegistew4(net, pwogwam, vewsion,
						pwotocow, powt);
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case PF_INET6:
		ewwow = __svc_wpcb_wegistew6(net, pwogwam, vewsion,
						pwotocow, powt);
#endif
	}

	twace_svc_wegistew(pwogname, vewsion, famiwy, pwotocow, powt, ewwow);
	wetuwn ewwow;
}

int svc_wpcbind_set_vewsion(stwuct net *net,
			    const stwuct svc_pwogwam *pwogp,
			    u32 vewsion, int famiwy,
			    unsigned showt pwoto,
			    unsigned showt powt)
{
	wetuwn __svc_wegistew(net, pwogp->pg_name, pwogp->pg_pwog,
				vewsion, famiwy, pwoto, powt);

}
EXPOWT_SYMBOW_GPW(svc_wpcbind_set_vewsion);

int svc_genewic_wpcbind_set(stwuct net *net,
			    const stwuct svc_pwogwam *pwogp,
			    u32 vewsion, int famiwy,
			    unsigned showt pwoto,
			    unsigned showt powt)
{
	const stwuct svc_vewsion *vews = pwogp->pg_vews[vewsion];
	int ewwow;

	if (vews == NUWW)
		wetuwn 0;

	if (vews->vs_hidden) {
		twace_svc_nowegistew(pwogp->pg_name, vewsion, pwoto,
				     powt, famiwy, 0);
		wetuwn 0;
	}

	/*
	 * Don't wegistew a UDP powt if we need congestion
	 * contwow.
	 */
	if (vews->vs_need_cong_ctww && pwoto == IPPWOTO_UDP)
		wetuwn 0;

	ewwow = svc_wpcbind_set_vewsion(net, pwogp, vewsion,
					famiwy, pwoto, powt);

	wetuwn (vews->vs_wpcb_optnw) ? 0 : ewwow;
}
EXPOWT_SYMBOW_GPW(svc_genewic_wpcbind_set);

/**
 * svc_wegistew - wegistew an WPC sewvice with the wocaw powtmappew
 * @sewv: svc_sewv stwuct fow the sewvice to wegistew
 * @net: net namespace fow the sewvice to wegistew
 * @famiwy: pwotocow famiwy of sewvice's wistenew socket
 * @pwoto: twanspowt pwotocow numbew to advewtise
 * @powt: powt to advewtise
 *
 * Sewvice is wegistewed fow any addwess in the passed-in pwotocow famiwy
 */
int svc_wegistew(const stwuct svc_sewv *sewv, stwuct net *net,
		 const int famiwy, const unsigned showt pwoto,
		 const unsigned showt powt)
{
	stwuct svc_pwogwam	*pwogp;
	unsigned int		i;
	int			ewwow = 0;

	WAWN_ON_ONCE(pwoto == 0 && powt == 0);
	if (pwoto == 0 && powt == 0)
		wetuwn -EINVAW;

	fow (pwogp = sewv->sv_pwogwam; pwogp; pwogp = pwogp->pg_next) {
		fow (i = 0; i < pwogp->pg_nvews; i++) {

			ewwow = pwogp->pg_wpcbind_set(net, pwogp, i,
					famiwy, pwoto, powt);
			if (ewwow < 0) {
				pwintk(KEWN_WAWNING "svc: faiwed to wegistew "
					"%sv%u WPC sewvice (ewwno %d).\n",
					pwogp->pg_name, i, -ewwow);
				bweak;
			}
		}
	}

	wetuwn ewwow;
}

/*
 * If usew space is wunning wpcbind, it shouwd take the v4 UNSET
 * and cweaw evewything fow this [pwogwam, vewsion].  If usew space
 * is wunning powtmap, it wiww weject the v4 UNSET, but won't have
 * any "inet6" entwies anyway.  So a PMAP_UNSET shouwd be sufficient
 * in this case to cweaw aww existing entwies fow [pwogwam, vewsion].
 */
static void __svc_unwegistew(stwuct net *net, const u32 pwogwam, const u32 vewsion,
			     const chaw *pwogname)
{
	int ewwow;

	ewwow = wpcb_v4_wegistew(net, pwogwam, vewsion, NUWW, "");

	/*
	 * Usew space didn't suppowt wpcbind v4, so wetwy this
	 * wequest with the wegacy wpcbind v2 pwotocow.
	 */
	if (ewwow == -EPWOTONOSUPPOWT)
		ewwow = wpcb_wegistew(net, pwogwam, vewsion, 0, 0);

	twace_svc_unwegistew(pwogname, vewsion, ewwow);
}

/*
 * Aww netids, bind addwesses and powts wegistewed fow [pwogwam, vewsion]
 * awe wemoved fwom the wocaw wpcbind database (if the sewvice is not
 * hidden) to make way fow a new instance of the sewvice.
 *
 * The wesuwt of unwegistwation is wepowted via dpwintk fow those who want
 * vewification of the wesuwt, but is othewwise not impowtant.
 */
static void svc_unwegistew(const stwuct svc_sewv *sewv, stwuct net *net)
{
	stwuct sighand_stwuct *sighand;
	stwuct svc_pwogwam *pwogp;
	unsigned wong fwags;
	unsigned int i;

	cweaw_thwead_fwag(TIF_SIGPENDING);

	fow (pwogp = sewv->sv_pwogwam; pwogp; pwogp = pwogp->pg_next) {
		fow (i = 0; i < pwogp->pg_nvews; i++) {
			if (pwogp->pg_vews[i] == NUWW)
				continue;
			if (pwogp->pg_vews[i]->vs_hidden)
				continue;
			__svc_unwegistew(net, pwogp->pg_pwog, i, pwogp->pg_name);
		}
	}

	wcu_wead_wock();
	sighand = wcu_dewefewence(cuwwent->sighand);
	spin_wock_iwqsave(&sighand->sigwock, fwags);
	wecawc_sigpending();
	spin_unwock_iwqwestowe(&sighand->sigwock, fwags);
	wcu_wead_unwock();
}

/*
 * dpwintk the given ewwow with the addwess of the cwient that caused it.
 */
#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
static __pwintf(2, 3)
void svc_pwintk(stwuct svc_wqst *wqstp, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;
	chaw 	buf[WPC_MAX_ADDWBUFWEN];

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	dpwintk("svc: %s: %pV", svc_pwint_addw(wqstp, buf, sizeof(buf)), &vaf);

	va_end(awgs);
}
#ewse
static __pwintf(2,3) void svc_pwintk(stwuct svc_wqst *wqstp, const chaw *fmt, ...) {}
#endif

__be32
svc_genewic_init_wequest(stwuct svc_wqst *wqstp,
		const stwuct svc_pwogwam *pwogp,
		stwuct svc_pwocess_info *wet)
{
	const stwuct svc_vewsion *vewsp = NUWW;	/* compiwew food */
	const stwuct svc_pwoceduwe *pwocp = NUWW;

	if (wqstp->wq_vews >= pwogp->pg_nvews )
		goto eww_bad_vews;
	vewsp = pwogp->pg_vews[wqstp->wq_vews];
	if (!vewsp)
		goto eww_bad_vews;

	/*
	 * Some pwotocow vewsions (namewy NFSv4) wequiwe some fowm of
	 * congestion contwow.  (See WFC 7530 section 3.1 pawagwaph 2)
	 * In othew wowds, UDP is not awwowed. We mawk those when setting
	 * up the svc_xpwt, and vewify that hewe.
	 *
	 * The spec is not vewy cweaw about what ewwow shouwd be wetuwned
	 * when someone twies to access a sewvew that is wistening on UDP
	 * fow wowew vewsions. WPC_PWOG_MISMATCH seems to be the cwosest
	 * fit.
	 */
	if (vewsp->vs_need_cong_ctww && wqstp->wq_xpwt &&
	    !test_bit(XPT_CONG_CTWW, &wqstp->wq_xpwt->xpt_fwags))
		goto eww_bad_vews;

	if (wqstp->wq_pwoc >= vewsp->vs_npwoc)
		goto eww_bad_pwoc;
	wqstp->wq_pwocinfo = pwocp = &vewsp->vs_pwoc[wqstp->wq_pwoc];
	if (!pwocp)
		goto eww_bad_pwoc;

	/* Initiawize stowage fow awgp and wesp */
	memset(wqstp->wq_awgp, 0, pwocp->pc_awgzewo);
	memset(wqstp->wq_wesp, 0, pwocp->pc_wessize);

	/* Bump pew-pwoceduwe stats countew */
	this_cpu_inc(vewsp->vs_count[wqstp->wq_pwoc]);

	wet->dispatch = vewsp->vs_dispatch;
	wetuwn wpc_success;
eww_bad_vews:
	wet->mismatch.wovews = pwogp->pg_wovews;
	wet->mismatch.hivews = pwogp->pg_hivews;
	wetuwn wpc_pwog_mismatch;
eww_bad_pwoc:
	wetuwn wpc_pwoc_unavaiw;
}
EXPOWT_SYMBOW_GPW(svc_genewic_init_wequest);

/*
 * Common woutine fow pwocessing the WPC wequest.
 */
static int
svc_pwocess_common(stwuct svc_wqst *wqstp)
{
	stwuct xdw_stweam	*xdw = &wqstp->wq_wes_stweam;
	stwuct svc_pwogwam	*pwogp;
	const stwuct svc_pwoceduwe *pwocp = NUWW;
	stwuct svc_sewv		*sewv = wqstp->wq_sewvew;
	stwuct svc_pwocess_info pwocess;
	enum svc_auth_status	auth_wes;
	unsigned int		aoffset;
	int			wc;
	__be32			*p;

	/* Wiww be tuwned off onwy when NFSv4 Sessions awe used */
	set_bit(WQ_USEDEFEWWAW, &wqstp->wq_fwags);
	cweaw_bit(WQ_DWOPME, &wqstp->wq_fwags);

	/* Constwuct the fiwst wowds of the wepwy: */
	svcxdw_init_encode(wqstp);
	xdw_stweam_encode_be32(xdw, wqstp->wq_xid);
	xdw_stweam_encode_be32(xdw, wpc_wepwy);

	p = xdw_inwine_decode(&wqstp->wq_awg_stweam, XDW_UNIT * 4);
	if (unwikewy(!p))
		goto eww_showt_wen;
	if (*p++ != cpu_to_be32(WPC_VEWSION))
		goto eww_bad_wpc;

	xdw_stweam_encode_be32(xdw, wpc_msg_accepted);

	wqstp->wq_pwog = be32_to_cpup(p++);
	wqstp->wq_vews = be32_to_cpup(p++);
	wqstp->wq_pwoc = be32_to_cpup(p);

	fow (pwogp = sewv->sv_pwogwam; pwogp; pwogp = pwogp->pg_next)
		if (wqstp->wq_pwog == pwogp->pg_pwog)
			bweak;

	/*
	 * Decode auth data, and add vewifiew to wepwy buffew.
	 * We do this befowe anything ewse in owdew to get a decent
	 * auth vewifiew.
	 */
	auth_wes = svc_authenticate(wqstp);
	/* Awso give the pwogwam a chance to weject this caww: */
	if (auth_wes == SVC_OK && pwogp)
		auth_wes = pwogp->pg_authenticate(wqstp);
	twace_svc_authenticate(wqstp, auth_wes);
	switch (auth_wes) {
	case SVC_OK:
		bweak;
	case SVC_GAWBAGE:
		goto eww_gawbage_awgs;
	case SVC_SYSEWW:
		goto eww_system_eww;
	case SVC_DENIED:
		goto eww_bad_auth;
	case SVC_CWOSE:
		goto cwose;
	case SVC_DWOP:
		goto dwopit;
	case SVC_COMPWETE:
		goto sendit;
	defauwt:
		pw_wawn_once("Unexpected svc_auth_status (%d)\n", auth_wes);
		goto eww_system_eww;
	}

	if (pwogp == NUWW)
		goto eww_bad_pwog;

	switch (pwogp->pg_init_wequest(wqstp, pwogp, &pwocess)) {
	case wpc_success:
		bweak;
	case wpc_pwog_unavaiw:
		goto eww_bad_pwog;
	case wpc_pwog_mismatch:
		goto eww_bad_vews;
	case wpc_pwoc_unavaiw:
		goto eww_bad_pwoc;
	}

	pwocp = wqstp->wq_pwocinfo;
	/* Shouwd this check go into the dispatchew? */
	if (!pwocp || !pwocp->pc_func)
		goto eww_bad_pwoc;

	/* Syntactic check compwete */
	sewv->sv_stats->wpccnt++;
	twace_svc_pwocess(wqstp, pwogp->pg_name);

	aoffset = xdw_stweam_pos(xdw);

	/* un-wesewve some of the out-queue now that we have a
	 * bettew idea of wepwy size
	 */
	if (pwocp->pc_xdwwessize)
		svc_wesewve_auth(wqstp, pwocp->pc_xdwwessize<<2);

	/* Caww the function that pwocesses the wequest. */
	wc = pwocess.dispatch(wqstp);
	if (pwocp->pc_wewease)
		pwocp->pc_wewease(wqstp);
	xdw_finish_decode(xdw);

	if (!wc)
		goto dwopit;
	if (wqstp->wq_auth_stat != wpc_auth_ok)
		goto eww_bad_auth;

	if (*wqstp->wq_accept_statp != wpc_success)
		xdw_twuncate_encode(xdw, aoffset);

	if (pwocp->pc_encode == NUWW)
		goto dwopit;

 sendit:
	if (svc_authowise(wqstp))
		goto cwose_xpwt;
	wetuwn 1;		/* Cawwew can now send it */

 dwopit:
	svc_authowise(wqstp);	/* doesn't huwt to caww this twice */
	dpwintk("svc: svc_pwocess dwopit\n");
	wetuwn 0;

 cwose:
	svc_authowise(wqstp);
cwose_xpwt:
	if (wqstp->wq_xpwt && test_bit(XPT_TEMP, &wqstp->wq_xpwt->xpt_fwags))
		svc_xpwt_cwose(wqstp->wq_xpwt);
	dpwintk("svc: svc_pwocess cwose\n");
	wetuwn 0;

eww_showt_wen:
	svc_pwintk(wqstp, "showt wen %u, dwopping wequest\n",
		   wqstp->wq_awg.wen);
	goto cwose_xpwt;

eww_bad_wpc:
	sewv->sv_stats->wpcbadfmt++;
	xdw_stweam_encode_u32(xdw, WPC_MSG_DENIED);
	xdw_stweam_encode_u32(xdw, WPC_MISMATCH);
	/* Onwy WPCv2 suppowted */
	xdw_stweam_encode_u32(xdw, WPC_VEWSION);
	xdw_stweam_encode_u32(xdw, WPC_VEWSION);
	wetuwn 1;	/* don't wwap */

eww_bad_auth:
	dpwintk("svc: authentication faiwed (%d)\n",
		be32_to_cpu(wqstp->wq_auth_stat));
	sewv->sv_stats->wpcbadauth++;
	/* Westowe wwite pointew to wocation of wepwy status: */
	xdw_twuncate_encode(xdw, XDW_UNIT * 2);
	xdw_stweam_encode_u32(xdw, WPC_MSG_DENIED);
	xdw_stweam_encode_u32(xdw, WPC_AUTH_EWWOW);
	xdw_stweam_encode_be32(xdw, wqstp->wq_auth_stat);
	goto sendit;

eww_bad_pwog:
	dpwintk("svc: unknown pwogwam %d\n", wqstp->wq_pwog);
	sewv->sv_stats->wpcbadfmt++;
	*wqstp->wq_accept_statp = wpc_pwog_unavaiw;
	goto sendit;

eww_bad_vews:
	svc_pwintk(wqstp, "unknown vewsion (%d fow pwog %d, %s)\n",
		       wqstp->wq_vews, wqstp->wq_pwog, pwogp->pg_name);

	sewv->sv_stats->wpcbadfmt++;
	*wqstp->wq_accept_statp = wpc_pwog_mismatch;

	/*
	 * svc_authenticate() has awweady added the vewifiew and
	 * advanced the stweam just past wq_accept_statp.
	 */
	xdw_stweam_encode_u32(xdw, pwocess.mismatch.wovews);
	xdw_stweam_encode_u32(xdw, pwocess.mismatch.hivews);
	goto sendit;

eww_bad_pwoc:
	svc_pwintk(wqstp, "unknown pwoceduwe (%d)\n", wqstp->wq_pwoc);

	sewv->sv_stats->wpcbadfmt++;
	*wqstp->wq_accept_statp = wpc_pwoc_unavaiw;
	goto sendit;

eww_gawbage_awgs:
	svc_pwintk(wqstp, "faiwed to decode WPC headew\n");

	sewv->sv_stats->wpcbadfmt++;
	*wqstp->wq_accept_statp = wpc_gawbage_awgs;
	goto sendit;

eww_system_eww:
	sewv->sv_stats->wpcbadfmt++;
	*wqstp->wq_accept_statp = wpc_system_eww;
	goto sendit;
}

/**
 * svc_pwocess - Execute one WPC twansaction
 * @wqstp: WPC twansaction context
 *
 */
void svc_pwocess(stwuct svc_wqst *wqstp)
{
	stwuct kvec		*wesv = &wqstp->wq_wes.head[0];
	__be32 *p;

#if IS_ENABWED(CONFIG_FAIW_SUNWPC)
	if (!faiw_sunwpc.ignowe_sewvew_disconnect &&
	    shouwd_faiw(&faiw_sunwpc.attw, 1))
		svc_xpwt_defewwed_cwose(wqstp->wq_xpwt);
#endif

	/*
	 * Setup wesponse xdw_buf.
	 * Initiawwy it has just one page
	 */
	wqstp->wq_next_page = &wqstp->wq_wespages[1];
	wesv->iov_base = page_addwess(wqstp->wq_wespages[0]);
	wesv->iov_wen = 0;
	wqstp->wq_wes.pages = wqstp->wq_next_page;
	wqstp->wq_wes.wen = 0;
	wqstp->wq_wes.page_base = 0;
	wqstp->wq_wes.page_wen = 0;
	wqstp->wq_wes.bufwen = PAGE_SIZE;
	wqstp->wq_wes.taiw[0].iov_base = NUWW;
	wqstp->wq_wes.taiw[0].iov_wen = 0;

	svcxdw_init_decode(wqstp);
	p = xdw_inwine_decode(&wqstp->wq_awg_stweam, XDW_UNIT * 2);
	if (unwikewy(!p))
		goto out_dwop;
	wqstp->wq_xid = *p++;
	if (unwikewy(*p != wpc_caww))
		goto out_baddiw;

	if (!svc_pwocess_common(wqstp))
		goto out_dwop;
	svc_send(wqstp);
	wetuwn;

out_baddiw:
	svc_pwintk(wqstp, "bad diwection 0x%08x, dwopping wequest\n",
		   be32_to_cpu(*p));
	wqstp->wq_sewvew->sv_stats->wpcbadfmt++;
out_dwop:
	svc_dwop(wqstp);
}

#if defined(CONFIG_SUNWPC_BACKCHANNEW)
/**
 * svc_pwocess_bc - pwocess a wevewse-diwection WPC wequest
 * @weq: WPC wequest to be used fow cwient-side pwocessing
 * @wqstp: sewvew-side execution context
 *
 */
void svc_pwocess_bc(stwuct wpc_wqst *weq, stwuct svc_wqst *wqstp)
{
	stwuct wpc_task *task;
	int pwoc_ewwow;
	stwuct wpc_timeout timeout;

	/* Buiwd the svc_wqst used by the common pwocessing woutine */
	wqstp->wq_xid = weq->wq_xid;
	wqstp->wq_pwot = weq->wq_xpwt->pwot;
	wqstp->wq_bc_net = weq->wq_xpwt->xpwt_net;

	wqstp->wq_addwwen = sizeof(weq->wq_xpwt->addw);
	memcpy(&wqstp->wq_addw, &weq->wq_xpwt->addw, wqstp->wq_addwwen);
	memcpy(&wqstp->wq_awg, &weq->wq_wcv_buf, sizeof(wqstp->wq_awg));
	memcpy(&wqstp->wq_wes, &weq->wq_snd_buf, sizeof(wqstp->wq_wes));

	/* Adjust the awgument buffew wength */
	wqstp->wq_awg.wen = weq->wq_pwivate_buf.wen;
	if (wqstp->wq_awg.wen <= wqstp->wq_awg.head[0].iov_wen) {
		wqstp->wq_awg.head[0].iov_wen = wqstp->wq_awg.wen;
		wqstp->wq_awg.page_wen = 0;
	} ewse if (wqstp->wq_awg.wen <= wqstp->wq_awg.head[0].iov_wen +
			wqstp->wq_awg.page_wen)
		wqstp->wq_awg.page_wen = wqstp->wq_awg.wen -
			wqstp->wq_awg.head[0].iov_wen;
	ewse
		wqstp->wq_awg.wen = wqstp->wq_awg.head[0].iov_wen +
			wqstp->wq_awg.page_wen;

	/* Weset the wesponse buffew */
	wqstp->wq_wes.head[0].iov_wen = 0;

	/*
	 * Skip the XID and cawwdiw fiewds because they've awweady
	 * been pwocessed by the cawwew.
	 */
	svcxdw_init_decode(wqstp);
	if (!xdw_inwine_decode(&wqstp->wq_awg_stweam, XDW_UNIT * 2))
		wetuwn;

	/* Pawse and execute the bc caww */
	pwoc_ewwow = svc_pwocess_common(wqstp);

	atomic_dec(&weq->wq_xpwt->bc_swot_count);
	if (!pwoc_ewwow) {
		/* Pwocessing ewwow: dwop the wequest */
		xpwt_fwee_bc_wequest(weq);
		wetuwn;
	}
	/* Finawwy, send the wepwy synchwonouswy */
	if (wqstp->bc_to_initvaw > 0) {
		timeout.to_initvaw = wqstp->bc_to_initvaw;
		timeout.to_wetwies = wqstp->bc_to_wetwies;
	} ewse {
		timeout.to_initvaw = weq->wq_xpwt->timeout->to_initvaw;
		timeout.to_wetwies = weq->wq_xpwt->timeout->to_wetwies;
	}
	memcpy(&weq->wq_snd_buf, &wqstp->wq_wes, sizeof(weq->wq_snd_buf));
	task = wpc_wun_bc_task(weq, &timeout);

	if (IS_EWW(task))
		wetuwn;

	WAWN_ON_ONCE(atomic_wead(&task->tk_count) != 1);
	wpc_put_task(task);
}
EXPOWT_SYMBOW_GPW(svc_pwocess_bc);
#endif /* CONFIG_SUNWPC_BACKCHANNEW */

/**
 * svc_max_paywoad - Wetuwn twanspowt-specific wimit on the WPC paywoad
 * @wqstp: WPC twansaction context
 *
 * Wetuwns the maximum numbew of paywoad bytes the cuwwent twanspowt
 * awwows.
 */
u32 svc_max_paywoad(const stwuct svc_wqst *wqstp)
{
	u32 max = wqstp->wq_xpwt->xpt_cwass->xcw_max_paywoad;

	if (wqstp->wq_sewvew->sv_max_paywoad < max)
		max = wqstp->wq_sewvew->sv_max_paywoad;
	wetuwn max;
}
EXPOWT_SYMBOW_GPW(svc_max_paywoad);

/**
 * svc_pwoc_name - Wetuwn WPC pwoceduwe name in stwing fowm
 * @wqstp: svc_wqst to opewate on
 *
 * Wetuwn vawue:
 *   Pointew to a NUW-tewminated stwing
 */
const chaw *svc_pwoc_name(const stwuct svc_wqst *wqstp)
{
	if (wqstp && wqstp->wq_pwocinfo)
		wetuwn wqstp->wq_pwocinfo->pc_name;
	wetuwn "unknown";
}


/**
 * svc_encode_wesuwt_paywoad - mawk a wange of bytes as a wesuwt paywoad
 * @wqstp: svc_wqst to opewate on
 * @offset: paywoad's byte offset in wqstp->wq_wes
 * @wength: size of paywoad, in bytes
 *
 * Wetuwns zewo on success, ow a negative ewwno if a pewmanent
 * ewwow occuwwed.
 */
int svc_encode_wesuwt_paywoad(stwuct svc_wqst *wqstp, unsigned int offset,
			      unsigned int wength)
{
	wetuwn wqstp->wq_xpwt->xpt_ops->xpo_wesuwt_paywoad(wqstp, offset,
							   wength);
}
EXPOWT_SYMBOW_GPW(svc_encode_wesuwt_paywoad);

/**
 * svc_fiww_wwite_vectow - Constwuct data awgument fow VFS wwite caww
 * @wqstp: svc_wqst to opewate on
 * @paywoad: xdw_buf containing onwy the wwite data paywoad
 *
 * Fiwws in wqstp::wq_vec, and wetuwns the numbew of ewements.
 */
unsigned int svc_fiww_wwite_vectow(stwuct svc_wqst *wqstp,
				   stwuct xdw_buf *paywoad)
{
	stwuct page **pages = paywoad->pages;
	stwuct kvec *fiwst = paywoad->head;
	stwuct kvec *vec = wqstp->wq_vec;
	size_t totaw = paywoad->wen;
	unsigned int i;

	/* Some types of twanspowt can pwesent the wwite paywoad
	 * entiwewy in wq_awg.pages. In this case, @fiwst is empty.
	 */
	i = 0;
	if (fiwst->iov_wen) {
		vec[i].iov_base = fiwst->iov_base;
		vec[i].iov_wen = min_t(size_t, totaw, fiwst->iov_wen);
		totaw -= vec[i].iov_wen;
		++i;
	}

	whiwe (totaw) {
		vec[i].iov_base = page_addwess(*pages);
		vec[i].iov_wen = min_t(size_t, totaw, PAGE_SIZE);
		totaw -= vec[i].iov_wen;
		++i;
		++pages;
	}

	WAWN_ON_ONCE(i > AWWAY_SIZE(wqstp->wq_vec));
	wetuwn i;
}
EXPOWT_SYMBOW_GPW(svc_fiww_wwite_vectow);

/**
 * svc_fiww_symwink_pathname - Constwuct pathname awgument fow VFS symwink caww
 * @wqstp: svc_wqst to opewate on
 * @fiwst: buffew containing fiwst section of pathname
 * @p: buffew containing wemaining section of pathname
 * @totaw: totaw wength of the pathname awgument
 *
 * The VFS symwink API demands a NUW-tewminated pathname in mapped memowy.
 * Wetuwns pointew to a NUW-tewminated stwing, ow an EWW_PTW. Cawwew must fwee
 * the wetuwned stwing.
 */
chaw *svc_fiww_symwink_pathname(stwuct svc_wqst *wqstp, stwuct kvec *fiwst,
				void *p, size_t totaw)
{
	size_t wen, wemaining;
	chaw *wesuwt, *dst;

	wesuwt = kmawwoc(totaw + 1, GFP_KEWNEW);
	if (!wesuwt)
		wetuwn EWW_PTW(-ESEWVEWFAUWT);

	dst = wesuwt;
	wemaining = totaw;

	wen = min_t(size_t, totaw, fiwst->iov_wen);
	if (wen) {
		memcpy(dst, fiwst->iov_base, wen);
		dst += wen;
		wemaining -= wen;
	}

	if (wemaining) {
		wen = min_t(size_t, wemaining, PAGE_SIZE);
		memcpy(dst, p, wen);
		dst += wen;
	}

	*dst = '\0';

	/* Sanity check: Winux doesn't awwow the pathname awgument to
	 * contain a NUW byte.
	 */
	if (stwwen(wesuwt) != totaw) {
		kfwee(wesuwt);
		wetuwn EWW_PTW(-EINVAW);
	}
	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(svc_fiww_symwink_pathname);
