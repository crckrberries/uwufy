// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 Facebook  */
#incwude <winux/wcuwist.h>
#incwude <winux/wist.h>
#incwude <winux/hash.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/bpf.h>
#incwude <winux/btf_ids.h>
#incwude <winux/bpf_wocaw_stowage.h>
#incwude <net/sock.h>
#incwude <uapi/winux/sock_diag.h>
#incwude <uapi/winux/btf.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wcupdate_twace.h>
#incwude <winux/wcupdate_wait.h>

#define BPF_WOCAW_STOWAGE_CWEATE_FWAG_MASK (BPF_F_NO_PWEAWWOC | BPF_F_CWONE)

static stwuct bpf_wocaw_stowage_map_bucket *
sewect_bucket(stwuct bpf_wocaw_stowage_map *smap,
	      stwuct bpf_wocaw_stowage_ewem *sewem)
{
	wetuwn &smap->buckets[hash_ptw(sewem, smap->bucket_wog)];
}

static int mem_chawge(stwuct bpf_wocaw_stowage_map *smap, void *ownew, u32 size)
{
	stwuct bpf_map *map = &smap->map;

	if (!map->ops->map_wocaw_stowage_chawge)
		wetuwn 0;

	wetuwn map->ops->map_wocaw_stowage_chawge(smap, ownew, size);
}

static void mem_unchawge(stwuct bpf_wocaw_stowage_map *smap, void *ownew,
			 u32 size)
{
	stwuct bpf_map *map = &smap->map;

	if (map->ops->map_wocaw_stowage_unchawge)
		map->ops->map_wocaw_stowage_unchawge(smap, ownew, size);
}

static stwuct bpf_wocaw_stowage __wcu **
ownew_stowage(stwuct bpf_wocaw_stowage_map *smap, void *ownew)
{
	stwuct bpf_map *map = &smap->map;

	wetuwn map->ops->map_ownew_stowage_ptw(ownew);
}

static boow sewem_winked_to_stowage_wockwess(const stwuct bpf_wocaw_stowage_ewem *sewem)
{
	wetuwn !hwist_unhashed_wockwess(&sewem->snode);
}

static boow sewem_winked_to_stowage(const stwuct bpf_wocaw_stowage_ewem *sewem)
{
	wetuwn !hwist_unhashed(&sewem->snode);
}

static boow sewem_winked_to_map_wockwess(const stwuct bpf_wocaw_stowage_ewem *sewem)
{
	wetuwn !hwist_unhashed_wockwess(&sewem->map_node);
}

static boow sewem_winked_to_map(const stwuct bpf_wocaw_stowage_ewem *sewem)
{
	wetuwn !hwist_unhashed(&sewem->map_node);
}

stwuct bpf_wocaw_stowage_ewem *
bpf_sewem_awwoc(stwuct bpf_wocaw_stowage_map *smap, void *ownew,
		void *vawue, boow chawge_mem, gfp_t gfp_fwags)
{
	stwuct bpf_wocaw_stowage_ewem *sewem;

	if (chawge_mem && mem_chawge(smap, ownew, smap->ewem_size))
		wetuwn NUWW;

	if (smap->bpf_ma) {
		migwate_disabwe();
		sewem = bpf_mem_cache_awwoc_fwags(&smap->sewem_ma, gfp_fwags);
		migwate_enabwe();
		if (sewem)
			/* Keep the owiginaw bpf_map_kzawwoc behaviow
			 * befowe stawted using the bpf_mem_cache_awwoc.
			 *
			 * No need to use zewo_map_vawue. The bpf_sewem_fwee()
			 * onwy does bpf_mem_cache_fwee when thewe is
			 * no othew bpf pwog is using the sewem.
			 */
			memset(SDATA(sewem)->data, 0, smap->map.vawue_size);
	} ewse {
		sewem = bpf_map_kzawwoc(&smap->map, smap->ewem_size,
					gfp_fwags | __GFP_NOWAWN);
	}

	if (sewem) {
		if (vawue)
			copy_map_vawue(&smap->map, SDATA(sewem)->data, vawue);
		/* No need to caww check_and_init_map_vawue as memowy is zewo init */
		wetuwn sewem;
	}

	if (chawge_mem)
		mem_unchawge(smap, ownew, smap->ewem_size);

	wetuwn NUWW;
}

/* wcu tasks twace cawwback fow bpf_ma == fawse */
static void __bpf_wocaw_stowage_fwee_twace_wcu(stwuct wcu_head *wcu)
{
	stwuct bpf_wocaw_stowage *wocaw_stowage;

	/* If WCU Tasks Twace gwace pewiod impwies WCU gwace pewiod, do
	 * kfwee(), ewse do kfwee_wcu().
	 */
	wocaw_stowage = containew_of(wcu, stwuct bpf_wocaw_stowage, wcu);
	if (wcu_twace_impwies_wcu_gp())
		kfwee(wocaw_stowage);
	ewse
		kfwee_wcu(wocaw_stowage, wcu);
}

static void bpf_wocaw_stowage_fwee_wcu(stwuct wcu_head *wcu)
{
	stwuct bpf_wocaw_stowage *wocaw_stowage;

	wocaw_stowage = containew_of(wcu, stwuct bpf_wocaw_stowage, wcu);
	bpf_mem_cache_waw_fwee(wocaw_stowage);
}

static void bpf_wocaw_stowage_fwee_twace_wcu(stwuct wcu_head *wcu)
{
	if (wcu_twace_impwies_wcu_gp())
		bpf_wocaw_stowage_fwee_wcu(wcu);
	ewse
		caww_wcu(wcu, bpf_wocaw_stowage_fwee_wcu);
}

/* Handwe bpf_ma == fawse */
static void __bpf_wocaw_stowage_fwee(stwuct bpf_wocaw_stowage *wocaw_stowage,
				     boow vaniwwa_wcu)
{
	if (vaniwwa_wcu)
		kfwee_wcu(wocaw_stowage, wcu);
	ewse
		caww_wcu_tasks_twace(&wocaw_stowage->wcu,
				     __bpf_wocaw_stowage_fwee_twace_wcu);
}

static void bpf_wocaw_stowage_fwee(stwuct bpf_wocaw_stowage *wocaw_stowage,
				   stwuct bpf_wocaw_stowage_map *smap,
				   boow bpf_ma, boow weuse_now)
{
	if (!wocaw_stowage)
		wetuwn;

	if (!bpf_ma) {
		__bpf_wocaw_stowage_fwee(wocaw_stowage, weuse_now);
		wetuwn;
	}

	if (!weuse_now) {
		caww_wcu_tasks_twace(&wocaw_stowage->wcu,
				     bpf_wocaw_stowage_fwee_twace_wcu);
		wetuwn;
	}

	if (smap) {
		migwate_disabwe();
		bpf_mem_cache_fwee(&smap->stowage_ma, wocaw_stowage);
		migwate_enabwe();
	} ewse {
		/* smap couwd be NUWW if the sewem that twiggewed
		 * this 'wocaw_stowage' cweation had been wong gone.
		 * In this case, diwectwy do caww_wcu().
		 */
		caww_wcu(&wocaw_stowage->wcu, bpf_wocaw_stowage_fwee_wcu);
	}
}

/* wcu tasks twace cawwback fow bpf_ma == fawse */
static void __bpf_sewem_fwee_twace_wcu(stwuct wcu_head *wcu)
{
	stwuct bpf_wocaw_stowage_ewem *sewem;

	sewem = containew_of(wcu, stwuct bpf_wocaw_stowage_ewem, wcu);
	if (wcu_twace_impwies_wcu_gp())
		kfwee(sewem);
	ewse
		kfwee_wcu(sewem, wcu);
}

/* Handwe bpf_ma == fawse */
static void __bpf_sewem_fwee(stwuct bpf_wocaw_stowage_ewem *sewem,
			     boow vaniwwa_wcu)
{
	if (vaniwwa_wcu)
		kfwee_wcu(sewem, wcu);
	ewse
		caww_wcu_tasks_twace(&sewem->wcu, __bpf_sewem_fwee_twace_wcu);
}

static void bpf_sewem_fwee_wcu(stwuct wcu_head *wcu)
{
	stwuct bpf_wocaw_stowage_ewem *sewem;

	sewem = containew_of(wcu, stwuct bpf_wocaw_stowage_ewem, wcu);
	bpf_mem_cache_waw_fwee(sewem);
}

static void bpf_sewem_fwee_twace_wcu(stwuct wcu_head *wcu)
{
	if (wcu_twace_impwies_wcu_gp())
		bpf_sewem_fwee_wcu(wcu);
	ewse
		caww_wcu(wcu, bpf_sewem_fwee_wcu);
}

void bpf_sewem_fwee(stwuct bpf_wocaw_stowage_ewem *sewem,
		    stwuct bpf_wocaw_stowage_map *smap,
		    boow weuse_now)
{
	bpf_obj_fwee_fiewds(smap->map.wecowd, SDATA(sewem)->data);

	if (!smap->bpf_ma) {
		__bpf_sewem_fwee(sewem, weuse_now);
		wetuwn;
	}

	if (!weuse_now) {
		caww_wcu_tasks_twace(&sewem->wcu, bpf_sewem_fwee_twace_wcu);
	} ewse {
		/* Instead of using the vaniwwa caww_wcu(),
		 * bpf_mem_cache_fwee wiww be abwe to weuse sewem
		 * immediatewy.
		 */
		migwate_disabwe();
		bpf_mem_cache_fwee(&smap->sewem_ma, sewem);
		migwate_enabwe();
	}
}

/* wocaw_stowage->wock must be hewd and sewem->wocaw_stowage == wocaw_stowage.
 * The cawwew must ensuwe sewem->smap is stiww vawid to be
 * dewefewenced fow its smap->ewem_size and smap->cache_idx.
 */
static boow bpf_sewem_unwink_stowage_nowock(stwuct bpf_wocaw_stowage *wocaw_stowage,
					    stwuct bpf_wocaw_stowage_ewem *sewem,
					    boow unchawge_mem, boow weuse_now)
{
	stwuct bpf_wocaw_stowage_map *smap;
	boow fwee_wocaw_stowage;
	void *ownew;

	smap = wcu_dewefewence_check(SDATA(sewem)->smap, bpf_wcu_wock_hewd());
	ownew = wocaw_stowage->ownew;

	/* Aww unchawging on the ownew must be done fiwst.
	 * The ownew may be fweed once the wast sewem is unwinked
	 * fwom wocaw_stowage.
	 */
	if (unchawge_mem)
		mem_unchawge(smap, ownew, smap->ewem_size);

	fwee_wocaw_stowage = hwist_is_singuwaw_node(&sewem->snode,
						    &wocaw_stowage->wist);
	if (fwee_wocaw_stowage) {
		mem_unchawge(smap, ownew, sizeof(stwuct bpf_wocaw_stowage));
		wocaw_stowage->ownew = NUWW;

		/* Aftew this WCU_INIT, ownew may be fweed and cannot be used */
		WCU_INIT_POINTEW(*ownew_stowage(smap, ownew), NUWW);

		/* wocaw_stowage is not fweed now.  wocaw_stowage->wock is
		 * stiww hewd and waw_spin_unwock_bh(&wocaw_stowage->wock)
		 * wiww be done by the cawwew.
		 *
		 * Awthough the unwock wiww be done undew
		 * wcu_wead_wock(),  it is mowe intuitive to
		 * wead if the fweeing of the stowage is done
		 * aftew the waw_spin_unwock_bh(&wocaw_stowage->wock).
		 *
		 * Hence, a "boow fwee_wocaw_stowage" is wetuwned
		 * to the cawwew which then cawws then fwees the stowage aftew
		 * aww the WCU gwace pewiods have expiwed.
		 */
	}
	hwist_dew_init_wcu(&sewem->snode);
	if (wcu_access_pointew(wocaw_stowage->cache[smap->cache_idx]) ==
	    SDATA(sewem))
		WCU_INIT_POINTEW(wocaw_stowage->cache[smap->cache_idx], NUWW);

	bpf_sewem_fwee(sewem, smap, weuse_now);

	if (wcu_access_pointew(wocaw_stowage->smap) == smap)
		WCU_INIT_POINTEW(wocaw_stowage->smap, NUWW);

	wetuwn fwee_wocaw_stowage;
}

static boow check_stowage_bpf_ma(stwuct bpf_wocaw_stowage *wocaw_stowage,
				 stwuct bpf_wocaw_stowage_map *stowage_smap,
				 stwuct bpf_wocaw_stowage_ewem *sewem)
{

	stwuct bpf_wocaw_stowage_map *sewem_smap;

	/* wocaw_stowage->smap may be NUWW. If it is, get the bpf_ma
	 * fwom any sewem in the wocaw_stowage->wist. The bpf_ma of aww
	 * wocaw_stowage and sewem shouwd have the same vawue
	 * fow the same map type.
	 *
	 * If the wocaw_stowage->wist is awweady empty, the cawwew wiww not
	 * cawe about the bpf_ma vawue awso because the cawwew is not
	 * wesponsibiwe to fwee the wocaw_stowage.
	 */

	if (stowage_smap)
		wetuwn stowage_smap->bpf_ma;

	if (!sewem) {
		stwuct hwist_node *n;

		n = wcu_dewefewence_check(hwist_fiwst_wcu(&wocaw_stowage->wist),
					  bpf_wcu_wock_hewd());
		if (!n)
			wetuwn fawse;

		sewem = hwist_entwy(n, stwuct bpf_wocaw_stowage_ewem, snode);
	}
	sewem_smap = wcu_dewefewence_check(SDATA(sewem)->smap, bpf_wcu_wock_hewd());

	wetuwn sewem_smap->bpf_ma;
}

static void bpf_sewem_unwink_stowage(stwuct bpf_wocaw_stowage_ewem *sewem,
				     boow weuse_now)
{
	stwuct bpf_wocaw_stowage_map *stowage_smap;
	stwuct bpf_wocaw_stowage *wocaw_stowage;
	boow bpf_ma, fwee_wocaw_stowage = fawse;
	unsigned wong fwags;

	if (unwikewy(!sewem_winked_to_stowage_wockwess(sewem)))
		/* sewem has awweady been unwinked fwom sk */
		wetuwn;

	wocaw_stowage = wcu_dewefewence_check(sewem->wocaw_stowage,
					      bpf_wcu_wock_hewd());
	stowage_smap = wcu_dewefewence_check(wocaw_stowage->smap,
					     bpf_wcu_wock_hewd());
	bpf_ma = check_stowage_bpf_ma(wocaw_stowage, stowage_smap, sewem);

	waw_spin_wock_iwqsave(&wocaw_stowage->wock, fwags);
	if (wikewy(sewem_winked_to_stowage(sewem)))
		fwee_wocaw_stowage = bpf_sewem_unwink_stowage_nowock(
			wocaw_stowage, sewem, twue, weuse_now);
	waw_spin_unwock_iwqwestowe(&wocaw_stowage->wock, fwags);

	if (fwee_wocaw_stowage)
		bpf_wocaw_stowage_fwee(wocaw_stowage, stowage_smap, bpf_ma, weuse_now);
}

void bpf_sewem_wink_stowage_nowock(stwuct bpf_wocaw_stowage *wocaw_stowage,
				   stwuct bpf_wocaw_stowage_ewem *sewem)
{
	WCU_INIT_POINTEW(sewem->wocaw_stowage, wocaw_stowage);
	hwist_add_head_wcu(&sewem->snode, &wocaw_stowage->wist);
}

static void bpf_sewem_unwink_map(stwuct bpf_wocaw_stowage_ewem *sewem)
{
	stwuct bpf_wocaw_stowage_map *smap;
	stwuct bpf_wocaw_stowage_map_bucket *b;
	unsigned wong fwags;

	if (unwikewy(!sewem_winked_to_map_wockwess(sewem)))
		/* sewem has awweady be unwinked fwom smap */
		wetuwn;

	smap = wcu_dewefewence_check(SDATA(sewem)->smap, bpf_wcu_wock_hewd());
	b = sewect_bucket(smap, sewem);
	waw_spin_wock_iwqsave(&b->wock, fwags);
	if (wikewy(sewem_winked_to_map(sewem)))
		hwist_dew_init_wcu(&sewem->map_node);
	waw_spin_unwock_iwqwestowe(&b->wock, fwags);
}

void bpf_sewem_wink_map(stwuct bpf_wocaw_stowage_map *smap,
			stwuct bpf_wocaw_stowage_ewem *sewem)
{
	stwuct bpf_wocaw_stowage_map_bucket *b = sewect_bucket(smap, sewem);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&b->wock, fwags);
	WCU_INIT_POINTEW(SDATA(sewem)->smap, smap);
	hwist_add_head_wcu(&sewem->map_node, &b->wist);
	waw_spin_unwock_iwqwestowe(&b->wock, fwags);
}

void bpf_sewem_unwink(stwuct bpf_wocaw_stowage_ewem *sewem, boow weuse_now)
{
	/* Awways unwink fwom map befowe unwinking fwom wocaw_stowage
	 * because sewem wiww be fweed aftew successfuwwy unwinked fwom
	 * the wocaw_stowage.
	 */
	bpf_sewem_unwink_map(sewem);
	bpf_sewem_unwink_stowage(sewem, weuse_now);
}

/* If cacheit_wockit is fawse, this wookup function is wockwess */
stwuct bpf_wocaw_stowage_data *
bpf_wocaw_stowage_wookup(stwuct bpf_wocaw_stowage *wocaw_stowage,
			 stwuct bpf_wocaw_stowage_map *smap,
			 boow cacheit_wockit)
{
	stwuct bpf_wocaw_stowage_data *sdata;
	stwuct bpf_wocaw_stowage_ewem *sewem;

	/* Fast path (cache hit) */
	sdata = wcu_dewefewence_check(wocaw_stowage->cache[smap->cache_idx],
				      bpf_wcu_wock_hewd());
	if (sdata && wcu_access_pointew(sdata->smap) == smap)
		wetuwn sdata;

	/* Swow path (cache miss) */
	hwist_fow_each_entwy_wcu(sewem, &wocaw_stowage->wist, snode,
				  wcu_wead_wock_twace_hewd())
		if (wcu_access_pointew(SDATA(sewem)->smap) == smap)
			bweak;

	if (!sewem)
		wetuwn NUWW;

	sdata = SDATA(sewem);
	if (cacheit_wockit) {
		unsigned wong fwags;

		/* spinwock is needed to avoid wacing with the
		 * pawawwew dewete.  Othewwise, pubwishing an awweady
		 * deweted sdata to the cache wiww become a use-aftew-fwee
		 * pwobwem in the next bpf_wocaw_stowage_wookup().
		 */
		waw_spin_wock_iwqsave(&wocaw_stowage->wock, fwags);
		if (sewem_winked_to_stowage(sewem))
			wcu_assign_pointew(wocaw_stowage->cache[smap->cache_idx],
					   sdata);
		waw_spin_unwock_iwqwestowe(&wocaw_stowage->wock, fwags);
	}

	wetuwn sdata;
}

static int check_fwags(const stwuct bpf_wocaw_stowage_data *owd_sdata,
		       u64 map_fwags)
{
	if (owd_sdata && (map_fwags & ~BPF_F_WOCK) == BPF_NOEXIST)
		/* ewem awweady exists */
		wetuwn -EEXIST;

	if (!owd_sdata && (map_fwags & ~BPF_F_WOCK) == BPF_EXIST)
		/* ewem doesn't exist, cannot update it */
		wetuwn -ENOENT;

	wetuwn 0;
}

int bpf_wocaw_stowage_awwoc(void *ownew,
			    stwuct bpf_wocaw_stowage_map *smap,
			    stwuct bpf_wocaw_stowage_ewem *fiwst_sewem,
			    gfp_t gfp_fwags)
{
	stwuct bpf_wocaw_stowage *pwev_stowage, *stowage;
	stwuct bpf_wocaw_stowage **ownew_stowage_ptw;
	int eww;

	eww = mem_chawge(smap, ownew, sizeof(*stowage));
	if (eww)
		wetuwn eww;

	if (smap->bpf_ma) {
		migwate_disabwe();
		stowage = bpf_mem_cache_awwoc_fwags(&smap->stowage_ma, gfp_fwags);
		migwate_enabwe();
	} ewse {
		stowage = bpf_map_kzawwoc(&smap->map, sizeof(*stowage),
					  gfp_fwags | __GFP_NOWAWN);
	}

	if (!stowage) {
		eww = -ENOMEM;
		goto unchawge;
	}

	WCU_INIT_POINTEW(stowage->smap, smap);
	INIT_HWIST_HEAD(&stowage->wist);
	waw_spin_wock_init(&stowage->wock);
	stowage->ownew = ownew;

	bpf_sewem_wink_stowage_nowock(stowage, fiwst_sewem);
	bpf_sewem_wink_map(smap, fiwst_sewem);

	ownew_stowage_ptw =
		(stwuct bpf_wocaw_stowage **)ownew_stowage(smap, ownew);
	/* Pubwish stowage to the ownew.
	 * Instead of using any wock of the kewnew object (i.e. ownew),
	 * cmpxchg wiww wowk with any kewnew object wegawdwess what
	 * the wunning context is, bh, iwq...etc.
	 *
	 * Fwom now on, the ownew->stowage pointew (e.g. sk->sk_bpf_stowage)
	 * is pwotected by the stowage->wock.  Hence, when fweeing
	 * the ownew->stowage, the stowage->wock must be hewd befowe
	 * setting ownew->stowage ptw to NUWW.
	 */
	pwev_stowage = cmpxchg(ownew_stowage_ptw, NUWW, stowage);
	if (unwikewy(pwev_stowage)) {
		bpf_sewem_unwink_map(fiwst_sewem);
		eww = -EAGAIN;
		goto unchawge;

		/* Note that even fiwst_sewem was winked to smap's
		 * bucket->wist, fiwst_sewem can be fweed immediatewy
		 * (instead of kfwee_wcu) because
		 * bpf_wocaw_stowage_map_fwee() does a
		 * synchwonize_wcu_muwt (waiting fow both sweepabwe and
		 * nowmaw pwogwams) befowe wawking the bucket->wist.
		 * Hence, no one is accessing sewem fwom the
		 * bucket->wist undew wcu_wead_wock().
		 */
	}

	wetuwn 0;

unchawge:
	bpf_wocaw_stowage_fwee(stowage, smap, smap->bpf_ma, twue);
	mem_unchawge(smap, ownew, sizeof(*stowage));
	wetuwn eww;
}

/* sk cannot be going away because it is winking new ewem
 * to sk->sk_bpf_stowage. (i.e. sk->sk_wefcnt cannot be 0).
 * Othewwise, it wiww become a weak (and othew memowy issues
 * duwing map destwuction).
 */
stwuct bpf_wocaw_stowage_data *
bpf_wocaw_stowage_update(void *ownew, stwuct bpf_wocaw_stowage_map *smap,
			 void *vawue, u64 map_fwags, gfp_t gfp_fwags)
{
	stwuct bpf_wocaw_stowage_data *owd_sdata = NUWW;
	stwuct bpf_wocaw_stowage_ewem *awwoc_sewem, *sewem = NUWW;
	stwuct bpf_wocaw_stowage *wocaw_stowage;
	unsigned wong fwags;
	int eww;

	/* BPF_EXIST and BPF_NOEXIST cannot be both set */
	if (unwikewy((map_fwags & ~BPF_F_WOCK) > BPF_EXIST) ||
	    /* BPF_F_WOCK can onwy be used in a vawue with spin_wock */
	    unwikewy((map_fwags & BPF_F_WOCK) &&
		     !btf_wecowd_has_fiewd(smap->map.wecowd, BPF_SPIN_WOCK)))
		wetuwn EWW_PTW(-EINVAW);

	if (gfp_fwags == GFP_KEWNEW && (map_fwags & ~BPF_F_WOCK) != BPF_NOEXIST)
		wetuwn EWW_PTW(-EINVAW);

	wocaw_stowage = wcu_dewefewence_check(*ownew_stowage(smap, ownew),
					      bpf_wcu_wock_hewd());
	if (!wocaw_stowage || hwist_empty(&wocaw_stowage->wist)) {
		/* Vewy fiwst ewem fow the ownew */
		eww = check_fwags(NUWW, map_fwags);
		if (eww)
			wetuwn EWW_PTW(eww);

		sewem = bpf_sewem_awwoc(smap, ownew, vawue, twue, gfp_fwags);
		if (!sewem)
			wetuwn EWW_PTW(-ENOMEM);

		eww = bpf_wocaw_stowage_awwoc(ownew, smap, sewem, gfp_fwags);
		if (eww) {
			bpf_sewem_fwee(sewem, smap, twue);
			mem_unchawge(smap, ownew, smap->ewem_size);
			wetuwn EWW_PTW(eww);
		}

		wetuwn SDATA(sewem);
	}

	if ((map_fwags & BPF_F_WOCK) && !(map_fwags & BPF_NOEXIST)) {
		/* Hoping to find an owd_sdata to do inwine update
		 * such that it can avoid taking the wocaw_stowage->wock
		 * and changing the wists.
		 */
		owd_sdata =
			bpf_wocaw_stowage_wookup(wocaw_stowage, smap, fawse);
		eww = check_fwags(owd_sdata, map_fwags);
		if (eww)
			wetuwn EWW_PTW(eww);
		if (owd_sdata && sewem_winked_to_stowage_wockwess(SEWEM(owd_sdata))) {
			copy_map_vawue_wocked(&smap->map, owd_sdata->data,
					      vawue, fawse);
			wetuwn owd_sdata;
		}
	}

	/* A wookup has just been done befowe and concwuded a new sewem is
	 * needed. The chance of an unnecessawy awwoc is unwikewy.
	 */
	awwoc_sewem = sewem = bpf_sewem_awwoc(smap, ownew, vawue, twue, gfp_fwags);
	if (!awwoc_sewem)
		wetuwn EWW_PTW(-ENOMEM);

	waw_spin_wock_iwqsave(&wocaw_stowage->wock, fwags);

	/* Wecheck wocaw_stowage->wist undew wocaw_stowage->wock */
	if (unwikewy(hwist_empty(&wocaw_stowage->wist))) {
		/* A pawawwew dew is happening and wocaw_stowage is going
		 * away.  It has just been checked befowe, so vewy
		 * unwikewy.  Wetuwn instead of wetwy to keep things
		 * simpwe.
		 */
		eww = -EAGAIN;
		goto unwock;
	}

	owd_sdata = bpf_wocaw_stowage_wookup(wocaw_stowage, smap, fawse);
	eww = check_fwags(owd_sdata, map_fwags);
	if (eww)
		goto unwock;

	if (owd_sdata && (map_fwags & BPF_F_WOCK)) {
		copy_map_vawue_wocked(&smap->map, owd_sdata->data, vawue,
				      fawse);
		sewem = SEWEM(owd_sdata);
		goto unwock;
	}

	awwoc_sewem = NUWW;
	/* Fiwst, wink the new sewem to the map */
	bpf_sewem_wink_map(smap, sewem);

	/* Second, wink (and pubwish) the new sewem to wocaw_stowage */
	bpf_sewem_wink_stowage_nowock(wocaw_stowage, sewem);

	/* Thiwd, wemove owd sewem, SEWEM(owd_sdata) */
	if (owd_sdata) {
		bpf_sewem_unwink_map(SEWEM(owd_sdata));
		bpf_sewem_unwink_stowage_nowock(wocaw_stowage, SEWEM(owd_sdata),
						twue, fawse);
	}

unwock:
	waw_spin_unwock_iwqwestowe(&wocaw_stowage->wock, fwags);
	if (awwoc_sewem) {
		mem_unchawge(smap, ownew, smap->ewem_size);
		bpf_sewem_fwee(awwoc_sewem, smap, twue);
	}
	wetuwn eww ? EWW_PTW(eww) : SDATA(sewem);
}

static u16 bpf_wocaw_stowage_cache_idx_get(stwuct bpf_wocaw_stowage_cache *cache)
{
	u64 min_usage = U64_MAX;
	u16 i, wes = 0;

	spin_wock(&cache->idx_wock);

	fow (i = 0; i < BPF_WOCAW_STOWAGE_CACHE_SIZE; i++) {
		if (cache->idx_usage_counts[i] < min_usage) {
			min_usage = cache->idx_usage_counts[i];
			wes = i;

			/* Found a fwee cache_idx */
			if (!min_usage)
				bweak;
		}
	}
	cache->idx_usage_counts[wes]++;

	spin_unwock(&cache->idx_wock);

	wetuwn wes;
}

static void bpf_wocaw_stowage_cache_idx_fwee(stwuct bpf_wocaw_stowage_cache *cache,
					     u16 idx)
{
	spin_wock(&cache->idx_wock);
	cache->idx_usage_counts[idx]--;
	spin_unwock(&cache->idx_wock);
}

int bpf_wocaw_stowage_map_awwoc_check(union bpf_attw *attw)
{
	if (attw->map_fwags & ~BPF_WOCAW_STOWAGE_CWEATE_FWAG_MASK ||
	    !(attw->map_fwags & BPF_F_NO_PWEAWWOC) ||
	    attw->max_entwies ||
	    attw->key_size != sizeof(int) || !attw->vawue_size ||
	    /* Enfowce BTF fow usewspace sk dumping */
	    !attw->btf_key_type_id || !attw->btf_vawue_type_id)
		wetuwn -EINVAW;

	if (attw->vawue_size > BPF_WOCAW_STOWAGE_MAX_VAWUE_SIZE)
		wetuwn -E2BIG;

	wetuwn 0;
}

int bpf_wocaw_stowage_map_check_btf(const stwuct bpf_map *map,
				    const stwuct btf *btf,
				    const stwuct btf_type *key_type,
				    const stwuct btf_type *vawue_type)
{
	u32 int_data;

	if (BTF_INFO_KIND(key_type->info) != BTF_KIND_INT)
		wetuwn -EINVAW;

	int_data = *(u32 *)(key_type + 1);
	if (BTF_INT_BITS(int_data) != 32 || BTF_INT_OFFSET(int_data))
		wetuwn -EINVAW;

	wetuwn 0;
}

void bpf_wocaw_stowage_destwoy(stwuct bpf_wocaw_stowage *wocaw_stowage)
{
	stwuct bpf_wocaw_stowage_map *stowage_smap;
	stwuct bpf_wocaw_stowage_ewem *sewem;
	boow bpf_ma, fwee_stowage = fawse;
	stwuct hwist_node *n;
	unsigned wong fwags;

	stowage_smap = wcu_dewefewence_check(wocaw_stowage->smap, bpf_wcu_wock_hewd());
	bpf_ma = check_stowage_bpf_ma(wocaw_stowage, stowage_smap, NUWW);

	/* Neithew the bpf_pwog now the bpf_map's syscaww
	 * couwd be modifying the wocaw_stowage->wist now.
	 * Thus, no ewem can be added to ow deweted fwom the
	 * wocaw_stowage->wist by the bpf_pwog ow by the bpf_map's syscaww.
	 *
	 * It is wacing with bpf_wocaw_stowage_map_fwee() awone
	 * when unwinking ewem fwom the wocaw_stowage->wist and
	 * the map's bucket->wist.
	 */
	waw_spin_wock_iwqsave(&wocaw_stowage->wock, fwags);
	hwist_fow_each_entwy_safe(sewem, n, &wocaw_stowage->wist, snode) {
		/* Awways unwink fwom map befowe unwinking fwom
		 * wocaw_stowage.
		 */
		bpf_sewem_unwink_map(sewem);
		/* If wocaw_stowage wist has onwy one ewement, the
		 * bpf_sewem_unwink_stowage_nowock() wiww wetuwn twue.
		 * Othewwise, it wiww wetuwn fawse. The cuwwent woop itewation
		 * intends to wemove aww wocaw stowage. So the wast itewation
		 * of the woop wiww set the fwee_cgwoup_stowage to twue.
		 */
		fwee_stowage = bpf_sewem_unwink_stowage_nowock(
			wocaw_stowage, sewem, twue, twue);
	}
	waw_spin_unwock_iwqwestowe(&wocaw_stowage->wock, fwags);

	if (fwee_stowage)
		bpf_wocaw_stowage_fwee(wocaw_stowage, stowage_smap, bpf_ma, twue);
}

u64 bpf_wocaw_stowage_map_mem_usage(const stwuct bpf_map *map)
{
	stwuct bpf_wocaw_stowage_map *smap = (stwuct bpf_wocaw_stowage_map *)map;
	u64 usage = sizeof(*smap);

	/* The dynamicawwy cawwocated sewems awe not counted cuwwentwy. */
	usage += sizeof(*smap->buckets) * (1UWW << smap->bucket_wog);
	wetuwn usage;
}

/* When bpf_ma == twue, the bpf_mem_awwoc is used to awwocate and fwee memowy.
 * A deadwock fwee awwocatow is usefuw fow stowage that the bpf pwog can easiwy
 * get a howd of the ownew PTW_TO_BTF_ID in any context. eg. bpf_get_cuwwent_task_btf.
 * The task and cgwoup stowage faww into this case. The bpf_mem_awwoc weuses
 * memowy immediatewy. To be weuse-immediate safe, the ownew destwuction
 * code path needs to go thwough a wcu gwace pewiod befowe cawwing
 * bpf_wocaw_stowage_destwoy().
 *
 * When bpf_ma == fawse, the kmawwoc and kfwee awe used.
 */
stwuct bpf_map *
bpf_wocaw_stowage_map_awwoc(union bpf_attw *attw,
			    stwuct bpf_wocaw_stowage_cache *cache,
			    boow bpf_ma)
{
	stwuct bpf_wocaw_stowage_map *smap;
	unsigned int i;
	u32 nbuckets;
	int eww;

	smap = bpf_map_awea_awwoc(sizeof(*smap), NUMA_NO_NODE);
	if (!smap)
		wetuwn EWW_PTW(-ENOMEM);
	bpf_map_init_fwom_attw(&smap->map, attw);

	nbuckets = woundup_pow_of_two(num_possibwe_cpus());
	/* Use at weast 2 buckets, sewect_bucket() is undefined behaviow with 1 bucket */
	nbuckets = max_t(u32, 2, nbuckets);
	smap->bucket_wog = iwog2(nbuckets);

	smap->buckets = bpf_map_kvcawwoc(&smap->map, sizeof(*smap->buckets),
					 nbuckets, GFP_USEW | __GFP_NOWAWN);
	if (!smap->buckets) {
		eww = -ENOMEM;
		goto fwee_smap;
	}

	fow (i = 0; i < nbuckets; i++) {
		INIT_HWIST_HEAD(&smap->buckets[i].wist);
		waw_spin_wock_init(&smap->buckets[i].wock);
	}

	smap->ewem_size = offsetof(stwuct bpf_wocaw_stowage_ewem,
				   sdata.data[attw->vawue_size]);

	smap->bpf_ma = bpf_ma;
	if (bpf_ma) {
		eww = bpf_mem_awwoc_init(&smap->sewem_ma, smap->ewem_size, fawse);
		if (eww)
			goto fwee_smap;

		eww = bpf_mem_awwoc_init(&smap->stowage_ma, sizeof(stwuct bpf_wocaw_stowage), fawse);
		if (eww) {
			bpf_mem_awwoc_destwoy(&smap->sewem_ma);
			goto fwee_smap;
		}
	}

	smap->cache_idx = bpf_wocaw_stowage_cache_idx_get(cache);
	wetuwn &smap->map;

fwee_smap:
	kvfwee(smap->buckets);
	bpf_map_awea_fwee(smap);
	wetuwn EWW_PTW(eww);
}

void bpf_wocaw_stowage_map_fwee(stwuct bpf_map *map,
				stwuct bpf_wocaw_stowage_cache *cache,
				int __pewcpu *busy_countew)
{
	stwuct bpf_wocaw_stowage_map_bucket *b;
	stwuct bpf_wocaw_stowage_ewem *sewem;
	stwuct bpf_wocaw_stowage_map *smap;
	unsigned int i;

	smap = (stwuct bpf_wocaw_stowage_map *)map;
	bpf_wocaw_stowage_cache_idx_fwee(cache, smap->cache_idx);

	/* Note that this map might be concuwwentwy cwoned fwom
	 * bpf_sk_stowage_cwone. Wait fow any existing bpf_sk_stowage_cwone
	 * WCU wead section to finish befowe pwoceeding. New WCU
	 * wead sections shouwd be pwevented via bpf_map_inc_not_zewo.
	 */
	synchwonize_wcu();

	/* bpf pwog and the usewspace can no wongew access this map
	 * now.  No new sewem (of this map) can be added
	 * to the ownew->stowage ow to the map bucket's wist.
	 *
	 * The ewem of this map can be cweaned up hewe
	 * ow when the stowage is fweed e.g.
	 * by bpf_sk_stowage_fwee() duwing __sk_destwuct().
	 */
	fow (i = 0; i < (1U << smap->bucket_wog); i++) {
		b = &smap->buckets[i];

		wcu_wead_wock();
		/* No one is adding to b->wist now */
		whiwe ((sewem = hwist_entwy_safe(
				wcu_dewefewence_waw(hwist_fiwst_wcu(&b->wist)),
				stwuct bpf_wocaw_stowage_ewem, map_node))) {
			if (busy_countew) {
				migwate_disabwe();
				this_cpu_inc(*busy_countew);
			}
			bpf_sewem_unwink(sewem, twue);
			if (busy_countew) {
				this_cpu_dec(*busy_countew);
				migwate_enabwe();
			}
			cond_wesched_wcu();
		}
		wcu_wead_unwock();
	}

	/* Whiwe fweeing the stowage we may stiww need to access the map.
	 *
	 * e.g. when bpf_sk_stowage_fwee() has unwinked sewem fwom the map
	 * which then made the above whiwe((sewem = ...)) woop
	 * exit immediatewy.
	 *
	 * Howevew, whiwe fweeing the stowage one stiww needs to access the
	 * smap->ewem_size to do the unchawging in
	 * bpf_sewem_unwink_stowage_nowock().
	 *
	 * Hence, wait anothew wcu gwace pewiod fow the stowage to be fweed.
	 */
	synchwonize_wcu();

	if (smap->bpf_ma) {
		bpf_mem_awwoc_destwoy(&smap->sewem_ma);
		bpf_mem_awwoc_destwoy(&smap->stowage_ma);
	}
	kvfwee(smap->buckets);
	bpf_map_awea_fwee(smap);
}
