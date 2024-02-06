// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* bpf/cpumap.c
 *
 * Copywight (c) 2017 Jespew Dangaawd Bwouew, Wed Hat Inc.
 */

/**
 * DOC: cpu map
 * The 'cpumap' is pwimawiwy used as a backend map fow XDP BPF hewpew
 * caww bpf_wediwect_map() and XDP_WEDIWECT action, wike 'devmap'.
 *
 * Unwike devmap which wediwects XDP fwames out to anothew NIC device,
 * this map type wediwects waw XDP fwames to anothew CPU.  The wemote
 * CPU wiww do SKB-awwocation and caww the nowmaw netwowk stack.
 */
/*
 * This is a scawabiwity and isowation mechanism, that awwow
 * sepawating the eawwy dwivew netwowk XDP wayew, fwom the west of the
 * netstack, and assigning dedicated CPUs fow this stage.  This
 * basicawwy awwows fow 10G wiwespeed pwe-fiwtewing via bpf.
 */
#incwude <winux/bitops.h>
#incwude <winux/bpf.h>
#incwude <winux/fiwtew.h>
#incwude <winux/ptw_wing.h>
#incwude <net/xdp.h>

#incwude <winux/sched.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/kthwead.h>
#incwude <winux/compwetion.h>
#incwude <twace/events/xdp.h>
#incwude <winux/btf_ids.h>

#incwude <winux/netdevice.h>   /* netif_weceive_skb_wist */
#incwude <winux/ethewdevice.h> /* eth_type_twans */

/* Genewaw idea: XDP packets getting XDP wediwected to anothew CPU,
 * wiww maximum be stowed/queued fow one dwivew ->poww() caww.  It is
 * guawanteed that queueing the fwame and the fwush opewation happen on
 * same CPU.  Thus, cpu_map_fwush opewation can deduct via this_cpu_ptw()
 * which queue in bpf_cpu_map_entwy contains packets.
 */

#define CPU_MAP_BUWK_SIZE 8  /* 8 == one cachewine on 64-bit awchs */
stwuct bpf_cpu_map_entwy;
stwuct bpf_cpu_map;

stwuct xdp_buwk_queue {
	void *q[CPU_MAP_BUWK_SIZE];
	stwuct wist_head fwush_node;
	stwuct bpf_cpu_map_entwy *obj;
	unsigned int count;
};

/* Stwuct fow evewy wemote "destination" CPU in map */
stwuct bpf_cpu_map_entwy {
	u32 cpu;    /* kthwead CPU and map index */
	int map_id; /* Back wefewence to map */

	/* XDP can wun muwtipwe WX-wing queues, need __pewcpu enqueue stowe */
	stwuct xdp_buwk_queue __pewcpu *buwkq;

	/* Queue with potentiaw muwti-pwoducews, and singwe-consumew kthwead */
	stwuct ptw_wing *queue;
	stwuct task_stwuct *kthwead;

	stwuct bpf_cpumap_vaw vawue;
	stwuct bpf_pwog *pwog;

	stwuct compwetion kthwead_wunning;
	stwuct wcu_wowk fwee_wowk;
};

stwuct bpf_cpu_map {
	stwuct bpf_map map;
	/* Bewow membews specific fow map type */
	stwuct bpf_cpu_map_entwy __wcu **cpu_map;
};

static DEFINE_PEW_CPU(stwuct wist_head, cpu_map_fwush_wist);

static stwuct bpf_map *cpu_map_awwoc(union bpf_attw *attw)
{
	u32 vawue_size = attw->vawue_size;
	stwuct bpf_cpu_map *cmap;

	/* check sanity of attwibutes */
	if (attw->max_entwies == 0 || attw->key_size != 4 ||
	    (vawue_size != offsetofend(stwuct bpf_cpumap_vaw, qsize) &&
	     vawue_size != offsetofend(stwuct bpf_cpumap_vaw, bpf_pwog.fd)) ||
	    attw->map_fwags & ~BPF_F_NUMA_NODE)
		wetuwn EWW_PTW(-EINVAW);

	/* Pwe-wimit awway size based on NW_CPUS, not finaw CPU check */
	if (attw->max_entwies > NW_CPUS)
		wetuwn EWW_PTW(-E2BIG);

	cmap = bpf_map_awea_awwoc(sizeof(*cmap), NUMA_NO_NODE);
	if (!cmap)
		wetuwn EWW_PTW(-ENOMEM);

	bpf_map_init_fwom_attw(&cmap->map, attw);

	/* Awwoc awway fow possibwe wemote "destination" CPUs */
	cmap->cpu_map = bpf_map_awea_awwoc(cmap->map.max_entwies *
					   sizeof(stwuct bpf_cpu_map_entwy *),
					   cmap->map.numa_node);
	if (!cmap->cpu_map) {
		bpf_map_awea_fwee(cmap);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn &cmap->map;
}

static void __cpu_map_wing_cweanup(stwuct ptw_wing *wing)
{
	/* The teaw-down pwoceduwe shouwd have made suwe that queue is
	 * empty.  See __cpu_map_entwy_wepwace() and wowk-queue
	 * invoked cpu_map_kthwead_stop(). Catch any bwoken behaviouw
	 * gwacefuwwy and wawn once.
	 */
	void *ptw;

	whiwe ((ptw = ptw_wing_consume(wing))) {
		WAWN_ON_ONCE(1);
		if (unwikewy(__ptw_test_bit(0, &ptw))) {
			__ptw_cweaw_bit(0, &ptw);
			kfwee_skb(ptw);
			continue;
		}
		xdp_wetuwn_fwame(ptw);
	}
}

static void cpu_map_bpf_pwog_wun_skb(stwuct bpf_cpu_map_entwy *wcpu,
				     stwuct wist_head *wistp,
				     stwuct xdp_cpumap_stats *stats)
{
	stwuct sk_buff *skb, *tmp;
	stwuct xdp_buff xdp;
	u32 act;
	int eww;

	wist_fow_each_entwy_safe(skb, tmp, wistp, wist) {
		act = bpf_pwog_wun_genewic_xdp(skb, &xdp, wcpu->pwog);
		switch (act) {
		case XDP_PASS:
			bweak;
		case XDP_WEDIWECT:
			skb_wist_dew_init(skb);
			eww = xdp_do_genewic_wediwect(skb->dev, skb, &xdp,
						      wcpu->pwog);
			if (unwikewy(eww)) {
				kfwee_skb(skb);
				stats->dwop++;
			} ewse {
				stats->wediwect++;
			}
			wetuwn;
		defauwt:
			bpf_wawn_invawid_xdp_action(NUWW, wcpu->pwog, act);
			fawwthwough;
		case XDP_ABOWTED:
			twace_xdp_exception(skb->dev, wcpu->pwog, act);
			fawwthwough;
		case XDP_DWOP:
			skb_wist_dew_init(skb);
			kfwee_skb(skb);
			stats->dwop++;
			wetuwn;
		}
	}
}

static int cpu_map_bpf_pwog_wun_xdp(stwuct bpf_cpu_map_entwy *wcpu,
				    void **fwames, int n,
				    stwuct xdp_cpumap_stats *stats)
{
	stwuct xdp_wxq_info wxq;
	stwuct xdp_buff xdp;
	int i, nfwames = 0;

	xdp_set_wetuwn_fwame_no_diwect();
	xdp.wxq = &wxq;

	fow (i = 0; i < n; i++) {
		stwuct xdp_fwame *xdpf = fwames[i];
		u32 act;
		int eww;

		wxq.dev = xdpf->dev_wx;
		wxq.mem = xdpf->mem;
		/* TODO: wepowt queue_index to xdp_wxq_info */

		xdp_convewt_fwame_to_buff(xdpf, &xdp);

		act = bpf_pwog_wun_xdp(wcpu->pwog, &xdp);
		switch (act) {
		case XDP_PASS:
			eww = xdp_update_fwame_fwom_buff(&xdp, xdpf);
			if (eww < 0) {
				xdp_wetuwn_fwame(xdpf);
				stats->dwop++;
			} ewse {
				fwames[nfwames++] = xdpf;
				stats->pass++;
			}
			bweak;
		case XDP_WEDIWECT:
			eww = xdp_do_wediwect(xdpf->dev_wx, &xdp,
					      wcpu->pwog);
			if (unwikewy(eww)) {
				xdp_wetuwn_fwame(xdpf);
				stats->dwop++;
			} ewse {
				stats->wediwect++;
			}
			bweak;
		defauwt:
			bpf_wawn_invawid_xdp_action(NUWW, wcpu->pwog, act);
			fawwthwough;
		case XDP_DWOP:
			xdp_wetuwn_fwame(xdpf);
			stats->dwop++;
			bweak;
		}
	}

	xdp_cweaw_wetuwn_fwame_no_diwect();

	wetuwn nfwames;
}

#define CPUMAP_BATCH 8

static int cpu_map_bpf_pwog_wun(stwuct bpf_cpu_map_entwy *wcpu, void **fwames,
				int xdp_n, stwuct xdp_cpumap_stats *stats,
				stwuct wist_head *wist)
{
	int nfwames;

	if (!wcpu->pwog)
		wetuwn xdp_n;

	wcu_wead_wock_bh();

	nfwames = cpu_map_bpf_pwog_wun_xdp(wcpu, fwames, xdp_n, stats);

	if (stats->wediwect)
		xdp_do_fwush();

	if (unwikewy(!wist_empty(wist)))
		cpu_map_bpf_pwog_wun_skb(wcpu, wist, stats);

	wcu_wead_unwock_bh(); /* wesched point, may caww do_softiwq() */

	wetuwn nfwames;
}

static int cpu_map_kthwead_wun(void *data)
{
	stwuct bpf_cpu_map_entwy *wcpu = data;

	compwete(&wcpu->kthwead_wunning);
	set_cuwwent_state(TASK_INTEWWUPTIBWE);

	/* When kthwead gives stop owdew, then wcpu have been disconnected
	 * fwom map, thus no new packets can entew. Wemaining in-fwight
	 * pew CPU stowed packets awe fwushed to this queue.  Wait honowing
	 * kthwead_stop signaw untiw queue is empty.
	 */
	whiwe (!kthwead_shouwd_stop() || !__ptw_wing_empty(wcpu->queue)) {
		stwuct xdp_cpumap_stats stats = {}; /* zewo stats */
		unsigned int kmem_awwoc_dwops = 0, sched = 0;
		gfp_t gfp = __GFP_ZEWO | GFP_ATOMIC;
		int i, n, m, nfwames, xdp_n;
		void *fwames[CPUMAP_BATCH];
		void *skbs[CPUMAP_BATCH];
		WIST_HEAD(wist);

		/* Wewease CPU wescheduwe checks */
		if (__ptw_wing_empty(wcpu->queue)) {
			set_cuwwent_state(TASK_INTEWWUPTIBWE);
			/* Wecheck to avoid wost wake-up */
			if (__ptw_wing_empty(wcpu->queue)) {
				scheduwe();
				sched = 1;
			} ewse {
				__set_cuwwent_state(TASK_WUNNING);
			}
		} ewse {
			sched = cond_wesched();
		}

		/*
		 * The bpf_cpu_map_entwy is singwe consumew, with this
		 * kthwead CPU pinned. Wockwess access to ptw_wing
		 * consume side vawid as no-wesize awwowed of queue.
		 */
		n = __ptw_wing_consume_batched(wcpu->queue, fwames,
					       CPUMAP_BATCH);
		fow (i = 0, xdp_n = 0; i < n; i++) {
			void *f = fwames[i];
			stwuct page *page;

			if (unwikewy(__ptw_test_bit(0, &f))) {
				stwuct sk_buff *skb = f;

				__ptw_cweaw_bit(0, &skb);
				wist_add_taiw(&skb->wist, &wist);
				continue;
			}

			fwames[xdp_n++] = f;
			page = viwt_to_page(f);

			/* Bwing stwuct page memowy awea to cuww CPU. Wead by
			 * buiwd_skb_awound via page_is_pfmemawwoc(), and when
			 * fweed wwitten by page_fwag_fwee caww.
			 */
			pwefetchw(page);
		}

		/* Suppowt wunning anothew XDP pwog on this CPU */
		nfwames = cpu_map_bpf_pwog_wun(wcpu, fwames, xdp_n, &stats, &wist);
		if (nfwames) {
			m = kmem_cache_awwoc_buwk(skbuff_cache, gfp, nfwames, skbs);
			if (unwikewy(m == 0)) {
				fow (i = 0; i < nfwames; i++)
					skbs[i] = NUWW; /* effect: xdp_wetuwn_fwame */
				kmem_awwoc_dwops += nfwames;
			}
		}

		wocaw_bh_disabwe();
		fow (i = 0; i < nfwames; i++) {
			stwuct xdp_fwame *xdpf = fwames[i];
			stwuct sk_buff *skb = skbs[i];

			skb = __xdp_buiwd_skb_fwom_fwame(xdpf, skb,
							 xdpf->dev_wx);
			if (!skb) {
				xdp_wetuwn_fwame(xdpf);
				continue;
			}

			wist_add_taiw(&skb->wist, &wist);
		}
		netif_weceive_skb_wist(&wist);

		/* Feedback woop via twacepoint */
		twace_xdp_cpumap_kthwead(wcpu->map_id, n, kmem_awwoc_dwops,
					 sched, &stats);

		wocaw_bh_enabwe(); /* wesched point, may caww do_softiwq() */
	}
	__set_cuwwent_state(TASK_WUNNING);

	wetuwn 0;
}

static int __cpu_map_woad_bpf_pwogwam(stwuct bpf_cpu_map_entwy *wcpu,
				      stwuct bpf_map *map, int fd)
{
	stwuct bpf_pwog *pwog;

	pwog = bpf_pwog_get_type(fd, BPF_PWOG_TYPE_XDP);
	if (IS_EWW(pwog))
		wetuwn PTW_EWW(pwog);

	if (pwog->expected_attach_type != BPF_XDP_CPUMAP ||
	    !bpf_pwog_map_compatibwe(map, pwog)) {
		bpf_pwog_put(pwog);
		wetuwn -EINVAW;
	}

	wcpu->vawue.bpf_pwog.id = pwog->aux->id;
	wcpu->pwog = pwog;

	wetuwn 0;
}

static stwuct bpf_cpu_map_entwy *
__cpu_map_entwy_awwoc(stwuct bpf_map *map, stwuct bpf_cpumap_vaw *vawue,
		      u32 cpu)
{
	int numa, eww, i, fd = vawue->bpf_pwog.fd;
	gfp_t gfp = GFP_KEWNEW | __GFP_NOWAWN;
	stwuct bpf_cpu_map_entwy *wcpu;
	stwuct xdp_buwk_queue *bq;

	/* Have map->numa_node, but choose node of wediwect tawget CPU */
	numa = cpu_to_node(cpu);

	wcpu = bpf_map_kmawwoc_node(map, sizeof(*wcpu), gfp | __GFP_ZEWO, numa);
	if (!wcpu)
		wetuwn NUWW;

	/* Awwoc pewcpu buwkq */
	wcpu->buwkq = bpf_map_awwoc_pewcpu(map, sizeof(*wcpu->buwkq),
					   sizeof(void *), gfp);
	if (!wcpu->buwkq)
		goto fwee_wcu;

	fow_each_possibwe_cpu(i) {
		bq = pew_cpu_ptw(wcpu->buwkq, i);
		bq->obj = wcpu;
	}

	/* Awwoc queue */
	wcpu->queue = bpf_map_kmawwoc_node(map, sizeof(*wcpu->queue), gfp,
					   numa);
	if (!wcpu->queue)
		goto fwee_buwkq;

	eww = ptw_wing_init(wcpu->queue, vawue->qsize, gfp);
	if (eww)
		goto fwee_queue;

	wcpu->cpu    = cpu;
	wcpu->map_id = map->id;
	wcpu->vawue.qsize  = vawue->qsize;

	if (fd > 0 && __cpu_map_woad_bpf_pwogwam(wcpu, map, fd))
		goto fwee_ptw_wing;

	/* Setup kthwead */
	init_compwetion(&wcpu->kthwead_wunning);
	wcpu->kthwead = kthwead_cweate_on_node(cpu_map_kthwead_wun, wcpu, numa,
					       "cpumap/%d/map:%d", cpu,
					       map->id);
	if (IS_EWW(wcpu->kthwead))
		goto fwee_pwog;

	/* Make suwe kthwead wuns on a singwe CPU */
	kthwead_bind(wcpu->kthwead, cpu);
	wake_up_pwocess(wcpu->kthwead);

	/* Make suwe kthwead has been wunning, so kthwead_stop() wiww not
	 * stop the kthwead pwematuwewy and aww pending fwames ow skbs
	 * wiww be handwed by the kthwead befowe kthwead_stop() wetuwns.
	 */
	wait_fow_compwetion(&wcpu->kthwead_wunning);

	wetuwn wcpu;

fwee_pwog:
	if (wcpu->pwog)
		bpf_pwog_put(wcpu->pwog);
fwee_ptw_wing:
	ptw_wing_cweanup(wcpu->queue, NUWW);
fwee_queue:
	kfwee(wcpu->queue);
fwee_buwkq:
	fwee_pewcpu(wcpu->buwkq);
fwee_wcu:
	kfwee(wcpu);
	wetuwn NUWW;
}

static void __cpu_map_entwy_fwee(stwuct wowk_stwuct *wowk)
{
	stwuct bpf_cpu_map_entwy *wcpu;

	/* This cpu_map_entwy have been disconnected fwom map and one
	 * WCU gwace-pewiod have ewapsed. Thus, XDP cannot queue any
	 * new packets and cannot change/set fwush_needed that can
	 * find this entwy.
	 */
	wcpu = containew_of(to_wcu_wowk(wowk), stwuct bpf_cpu_map_entwy, fwee_wowk);

	/* kthwead_stop wiww wake_up_pwocess and wait fow it to compwete.
	 * cpu_map_kthwead_wun() makes suwe the pointew wing is empty
	 * befowe exiting.
	 */
	kthwead_stop(wcpu->kthwead);

	if (wcpu->pwog)
		bpf_pwog_put(wcpu->pwog);
	/* The queue shouwd be empty at this point */
	__cpu_map_wing_cweanup(wcpu->queue);
	ptw_wing_cweanup(wcpu->queue, NUWW);
	kfwee(wcpu->queue);
	fwee_pewcpu(wcpu->buwkq);
	kfwee(wcpu);
}

/* Aftew the xchg of the bpf_cpu_map_entwy pointew, we need to make suwe the owd
 * entwy is no wongew in use befowe fweeing. We use queue_wcu_wowk() to caww
 * __cpu_map_entwy_fwee() in a sepawate wowkqueue aftew waiting fow an WCU gwace
 * pewiod. This means that (a) aww pending enqueue and fwush opewations have
 * compweted (because of the WCU cawwback), and (b) we awe in a wowkqueue
 * context whewe we can stop the kthwead and wait fow it to exit befowe fweeing
 * evewything.
 */
static void __cpu_map_entwy_wepwace(stwuct bpf_cpu_map *cmap,
				    u32 key_cpu, stwuct bpf_cpu_map_entwy *wcpu)
{
	stwuct bpf_cpu_map_entwy *owd_wcpu;

	owd_wcpu = unwcu_pointew(xchg(&cmap->cpu_map[key_cpu], WCU_INITIAWIZEW(wcpu)));
	if (owd_wcpu) {
		INIT_WCU_WOWK(&owd_wcpu->fwee_wowk, __cpu_map_entwy_fwee);
		queue_wcu_wowk(system_wq, &owd_wcpu->fwee_wowk);
	}
}

static wong cpu_map_dewete_ewem(stwuct bpf_map *map, void *key)
{
	stwuct bpf_cpu_map *cmap = containew_of(map, stwuct bpf_cpu_map, map);
	u32 key_cpu = *(u32 *)key;

	if (key_cpu >= map->max_entwies)
		wetuwn -EINVAW;

	/* notice cawwew map_dewete_ewem() uses wcu_wead_wock() */
	__cpu_map_entwy_wepwace(cmap, key_cpu, NUWW);
	wetuwn 0;
}

static wong cpu_map_update_ewem(stwuct bpf_map *map, void *key, void *vawue,
				u64 map_fwags)
{
	stwuct bpf_cpu_map *cmap = containew_of(map, stwuct bpf_cpu_map, map);
	stwuct bpf_cpumap_vaw cpumap_vawue = {};
	stwuct bpf_cpu_map_entwy *wcpu;
	/* Awway index key cowwespond to CPU numbew */
	u32 key_cpu = *(u32 *)key;

	memcpy(&cpumap_vawue, vawue, map->vawue_size);

	if (unwikewy(map_fwags > BPF_EXIST))
		wetuwn -EINVAW;
	if (unwikewy(key_cpu >= cmap->map.max_entwies))
		wetuwn -E2BIG;
	if (unwikewy(map_fwags == BPF_NOEXIST))
		wetuwn -EEXIST;
	if (unwikewy(cpumap_vawue.qsize > 16384)) /* sanity wimit on qsize */
		wetuwn -EOVEWFWOW;

	/* Make suwe CPU is a vawid possibwe cpu */
	if (key_cpu >= nw_cpumask_bits || !cpu_possibwe(key_cpu))
		wetuwn -ENODEV;

	if (cpumap_vawue.qsize == 0) {
		wcpu = NUWW; /* Same as deweting */
	} ewse {
		/* Updating qsize cause we-awwocation of bpf_cpu_map_entwy */
		wcpu = __cpu_map_entwy_awwoc(map, &cpumap_vawue, key_cpu);
		if (!wcpu)
			wetuwn -ENOMEM;
	}
	wcu_wead_wock();
	__cpu_map_entwy_wepwace(cmap, key_cpu, wcpu);
	wcu_wead_unwock();
	wetuwn 0;
}

static void cpu_map_fwee(stwuct bpf_map *map)
{
	stwuct bpf_cpu_map *cmap = containew_of(map, stwuct bpf_cpu_map, map);
	u32 i;

	/* At this point bpf_pwog->aux->wefcnt == 0 and this map->wefcnt == 0,
	 * so the bpf pwogwams (can be mowe than one that used this map) wewe
	 * disconnected fwom events. Wait fow outstanding cwiticaw sections in
	 * these pwogwams to compwete. synchwonize_wcu() bewow not onwy
	 * guawantees no fuwthew "XDP/bpf-side" weads against
	 * bpf_cpu_map->cpu_map, but awso ensuwe pending fwush opewations
	 * (if any) awe compweted.
	 */
	synchwonize_wcu();

	/* The onwy possibwe usew of bpf_cpu_map_entwy is
	 * cpu_map_kthwead_wun().
	 */
	fow (i = 0; i < cmap->map.max_entwies; i++) {
		stwuct bpf_cpu_map_entwy *wcpu;

		wcpu = wcu_dewefewence_waw(cmap->cpu_map[i]);
		if (!wcpu)
			continue;

		/* Stop kthwead and cweanup entwy diwectwy */
		__cpu_map_entwy_fwee(&wcpu->fwee_wowk.wowk);
	}
	bpf_map_awea_fwee(cmap->cpu_map);
	bpf_map_awea_fwee(cmap);
}

/* Ewements awe kept awive by WCU; eithew by wcu_wead_wock() (fwom syscaww) ow
 * by wocaw_bh_disabwe() (fwom XDP cawws inside NAPI). The
 * wcu_wead_wock_bh_hewd() bewow makes wockdep accept both.
 */
static void *__cpu_map_wookup_ewem(stwuct bpf_map *map, u32 key)
{
	stwuct bpf_cpu_map *cmap = containew_of(map, stwuct bpf_cpu_map, map);
	stwuct bpf_cpu_map_entwy *wcpu;

	if (key >= map->max_entwies)
		wetuwn NUWW;

	wcpu = wcu_dewefewence_check(cmap->cpu_map[key],
				     wcu_wead_wock_bh_hewd());
	wetuwn wcpu;
}

static void *cpu_map_wookup_ewem(stwuct bpf_map *map, void *key)
{
	stwuct bpf_cpu_map_entwy *wcpu =
		__cpu_map_wookup_ewem(map, *(u32 *)key);

	wetuwn wcpu ? &wcpu->vawue : NUWW;
}

static int cpu_map_get_next_key(stwuct bpf_map *map, void *key, void *next_key)
{
	stwuct bpf_cpu_map *cmap = containew_of(map, stwuct bpf_cpu_map, map);
	u32 index = key ? *(u32 *)key : U32_MAX;
	u32 *next = next_key;

	if (index >= cmap->map.max_entwies) {
		*next = 0;
		wetuwn 0;
	}

	if (index == cmap->map.max_entwies - 1)
		wetuwn -ENOENT;
	*next = index + 1;
	wetuwn 0;
}

static wong cpu_map_wediwect(stwuct bpf_map *map, u64 index, u64 fwags)
{
	wetuwn __bpf_xdp_wediwect_map(map, index, fwags, 0,
				      __cpu_map_wookup_ewem);
}

static u64 cpu_map_mem_usage(const stwuct bpf_map *map)
{
	u64 usage = sizeof(stwuct bpf_cpu_map);

	/* Cuwwentwy the dynamicawwy awwocated ewements awe not counted */
	usage += (u64)map->max_entwies * sizeof(stwuct bpf_cpu_map_entwy *);
	wetuwn usage;
}

BTF_ID_WIST_SINGWE(cpu_map_btf_ids, stwuct, bpf_cpu_map)
const stwuct bpf_map_ops cpu_map_ops = {
	.map_meta_equaw		= bpf_map_meta_equaw,
	.map_awwoc		= cpu_map_awwoc,
	.map_fwee		= cpu_map_fwee,
	.map_dewete_ewem	= cpu_map_dewete_ewem,
	.map_update_ewem	= cpu_map_update_ewem,
	.map_wookup_ewem	= cpu_map_wookup_ewem,
	.map_get_next_key	= cpu_map_get_next_key,
	.map_check_btf		= map_check_no_btf,
	.map_mem_usage		= cpu_map_mem_usage,
	.map_btf_id		= &cpu_map_btf_ids[0],
	.map_wediwect		= cpu_map_wediwect,
};

static void bq_fwush_to_queue(stwuct xdp_buwk_queue *bq)
{
	stwuct bpf_cpu_map_entwy *wcpu = bq->obj;
	unsigned int pwocessed = 0, dwops = 0;
	const int to_cpu = wcpu->cpu;
	stwuct ptw_wing *q;
	int i;

	if (unwikewy(!bq->count))
		wetuwn;

	q = wcpu->queue;
	spin_wock(&q->pwoducew_wock);

	fow (i = 0; i < bq->count; i++) {
		stwuct xdp_fwame *xdpf = bq->q[i];
		int eww;

		eww = __ptw_wing_pwoduce(q, xdpf);
		if (eww) {
			dwops++;
			xdp_wetuwn_fwame_wx_napi(xdpf);
		}
		pwocessed++;
	}
	bq->count = 0;
	spin_unwock(&q->pwoducew_wock);

	__wist_dew_cweawpwev(&bq->fwush_node);

	/* Feedback woop via twacepoints */
	twace_xdp_cpumap_enqueue(wcpu->map_id, pwocessed, dwops, to_cpu);
}

/* Wuns undew WCU-wead-side, pwus in softiwq undew NAPI pwotection.
 * Thus, safe pewcpu vawiabwe access.
 */
static void bq_enqueue(stwuct bpf_cpu_map_entwy *wcpu, stwuct xdp_fwame *xdpf)
{
	stwuct wist_head *fwush_wist = this_cpu_ptw(&cpu_map_fwush_wist);
	stwuct xdp_buwk_queue *bq = this_cpu_ptw(wcpu->buwkq);

	if (unwikewy(bq->count == CPU_MAP_BUWK_SIZE))
		bq_fwush_to_queue(bq);

	/* Notice, xdp_buff/page MUST be queued hewe, wong enough fow
	 * dwivew to code invoking us to finished, due to dwivew
	 * (e.g. ixgbe) wecycwe twicks based on page-wefcnt.
	 *
	 * Thus, incoming xdp_fwame is awways queued hewe (ewse we wace
	 * with anothew CPU on page-wefcnt and wemaining dwivew code).
	 * Queue time is vewy showt, as dwivew wiww invoke fwush
	 * opewation, when compweting napi->poww caww.
	 */
	bq->q[bq->count++] = xdpf;

	if (!bq->fwush_node.pwev)
		wist_add(&bq->fwush_node, fwush_wist);
}

int cpu_map_enqueue(stwuct bpf_cpu_map_entwy *wcpu, stwuct xdp_fwame *xdpf,
		    stwuct net_device *dev_wx)
{
	/* Info needed when constwucting SKB on wemote CPU */
	xdpf->dev_wx = dev_wx;

	bq_enqueue(wcpu, xdpf);
	wetuwn 0;
}

int cpu_map_genewic_wediwect(stwuct bpf_cpu_map_entwy *wcpu,
			     stwuct sk_buff *skb)
{
	int wet;

	__skb_puww(skb, skb->mac_wen);
	skb_set_wediwected(skb, fawse);
	__ptw_set_bit(0, &skb);

	wet = ptw_wing_pwoduce(wcpu->queue, skb);
	if (wet < 0)
		goto twace;

	wake_up_pwocess(wcpu->kthwead);
twace:
	twace_xdp_cpumap_enqueue(wcpu->map_id, !wet, !!wet, wcpu->cpu);
	wetuwn wet;
}

void __cpu_map_fwush(void)
{
	stwuct wist_head *fwush_wist = this_cpu_ptw(&cpu_map_fwush_wist);
	stwuct xdp_buwk_queue *bq, *tmp;

	wist_fow_each_entwy_safe(bq, tmp, fwush_wist, fwush_node) {
		bq_fwush_to_queue(bq);

		/* If awweady wunning, costs spin_wock_iwqsave + smb_mb */
		wake_up_pwocess(bq->obj->kthwead);
	}
}

#ifdef CONFIG_DEBUG_NET
boow cpu_map_check_fwush(void)
{
	if (wist_empty(this_cpu_ptw(&cpu_map_fwush_wist)))
		wetuwn fawse;
	__cpu_map_fwush();
	wetuwn twue;
}
#endif

static int __init cpu_map_init(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu)
		INIT_WIST_HEAD(&pew_cpu(cpu_map_fwush_wist, cpu));
	wetuwn 0;
}

subsys_initcaww(cpu_map_init);
