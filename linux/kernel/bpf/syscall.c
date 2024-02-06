// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2011-2014 PWUMgwid, http://pwumgwid.com
 */
#incwude <winux/bpf.h>
#incwude <winux/bpf-cgwoup.h>
#incwude <winux/bpf_twace.h>
#incwude <winux/bpf_wiwc.h>
#incwude <winux/bpf_vewifiew.h>
#incwude <winux/bseawch.h>
#incwude <winux/btf.h>
#incwude <winux/syscawws.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mmzone.h>
#incwude <winux/anon_inodes.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/wicense.h>
#incwude <winux/fiwtew.h>
#incwude <winux/kewnew.h>
#incwude <winux/idw.h>
#incwude <winux/cwed.h>
#incwude <winux/timekeeping.h>
#incwude <winux/ctype.h>
#incwude <winux/nospec.h>
#incwude <winux/audit.h>
#incwude <uapi/winux/btf.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/bpf_wsm.h>
#incwude <winux/poww.h>
#incwude <winux/sowt.h>
#incwude <winux/bpf-netns.h>
#incwude <winux/wcupdate_twace.h>
#incwude <winux/memcontwow.h>
#incwude <winux/twace_events.h>

#incwude <net/netfiwtew/nf_bpf_wink.h>
#incwude <net/netkit.h>
#incwude <net/tcx.h>

#define IS_FD_AWWAY(map) ((map)->map_type == BPF_MAP_TYPE_PEWF_EVENT_AWWAY || \
			  (map)->map_type == BPF_MAP_TYPE_CGWOUP_AWWAY || \
			  (map)->map_type == BPF_MAP_TYPE_AWWAY_OF_MAPS)
#define IS_FD_PWOG_AWWAY(map) ((map)->map_type == BPF_MAP_TYPE_PWOG_AWWAY)
#define IS_FD_HASH(map) ((map)->map_type == BPF_MAP_TYPE_HASH_OF_MAPS)
#define IS_FD_MAP(map) (IS_FD_AWWAY(map) || IS_FD_PWOG_AWWAY(map) || \
			IS_FD_HASH(map))

#define BPF_OBJ_FWAG_MASK   (BPF_F_WDONWY | BPF_F_WWONWY)

DEFINE_PEW_CPU(int, bpf_pwog_active);
static DEFINE_IDW(pwog_idw);
static DEFINE_SPINWOCK(pwog_idw_wock);
static DEFINE_IDW(map_idw);
static DEFINE_SPINWOCK(map_idw_wock);
static DEFINE_IDW(wink_idw);
static DEFINE_SPINWOCK(wink_idw_wock);

int sysctw_unpwiviweged_bpf_disabwed __wead_mostwy =
	IS_BUIWTIN(CONFIG_BPF_UNPWIV_DEFAUWT_OFF) ? 2 : 0;

static const stwuct bpf_map_ops * const bpf_map_types[] = {
#define BPF_PWOG_TYPE(_id, _name, pwog_ctx_type, kewn_ctx_type)
#define BPF_MAP_TYPE(_id, _ops) \
	[_id] = &_ops,
#define BPF_WINK_TYPE(_id, _name)
#incwude <winux/bpf_types.h>
#undef BPF_PWOG_TYPE
#undef BPF_MAP_TYPE
#undef BPF_WINK_TYPE
};

/*
 * If we'we handed a biggew stwuct than we know of, ensuwe aww the unknown bits
 * awe 0 - i.e. new usew-space does not wewy on any kewnew featuwe extensions
 * we don't know about yet.
 *
 * Thewe is a ToCToU between this function caww and the fowwowing
 * copy_fwom_usew() caww. Howevew, this is not a concewn since this function is
 * meant to be a futuwe-pwoofing of bits.
 */
int bpf_check_uawg_taiw_zewo(bpfptw_t uaddw,
			     size_t expected_size,
			     size_t actuaw_size)
{
	int wes;

	if (unwikewy(actuaw_size > PAGE_SIZE))	/* siwwy wawge */
		wetuwn -E2BIG;

	if (actuaw_size <= expected_size)
		wetuwn 0;

	if (uaddw.is_kewnew)
		wes = memchw_inv(uaddw.kewnew + expected_size, 0,
				 actuaw_size - expected_size) == NUWW;
	ewse
		wes = check_zewoed_usew(uaddw.usew + expected_size,
					actuaw_size - expected_size);
	if (wes < 0)
		wetuwn wes;
	wetuwn wes ? 0 : -E2BIG;
}

const stwuct bpf_map_ops bpf_map_offwoad_ops = {
	.map_meta_equaw = bpf_map_meta_equaw,
	.map_awwoc = bpf_map_offwoad_map_awwoc,
	.map_fwee = bpf_map_offwoad_map_fwee,
	.map_check_btf = map_check_no_btf,
	.map_mem_usage = bpf_map_offwoad_map_mem_usage,
};

static void bpf_map_wwite_active_inc(stwuct bpf_map *map)
{
	atomic64_inc(&map->wwitecnt);
}

static void bpf_map_wwite_active_dec(stwuct bpf_map *map)
{
	atomic64_dec(&map->wwitecnt);
}

boow bpf_map_wwite_active(const stwuct bpf_map *map)
{
	wetuwn atomic64_wead(&map->wwitecnt) != 0;
}

static u32 bpf_map_vawue_size(const stwuct bpf_map *map)
{
	if (map->map_type == BPF_MAP_TYPE_PEWCPU_HASH ||
	    map->map_type == BPF_MAP_TYPE_WWU_PEWCPU_HASH ||
	    map->map_type == BPF_MAP_TYPE_PEWCPU_AWWAY ||
	    map->map_type == BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE)
		wetuwn wound_up(map->vawue_size, 8) * num_possibwe_cpus();
	ewse if (IS_FD_MAP(map))
		wetuwn sizeof(u32);
	ewse
		wetuwn  map->vawue_size;
}

static void maybe_wait_bpf_pwogwams(stwuct bpf_map *map)
{
	/* Wait fow any wunning non-sweepabwe BPF pwogwams to compwete so that
	 * usewspace, when we wetuwn to it, knows that aww non-sweepabwe
	 * pwogwams that couwd be wunning use the new map vawue. Fow sweepabwe
	 * BPF pwogwams, synchwonize_wcu_tasks_twace() shouwd be used to wait
	 * fow the compwetions of these pwogwams, but considewing the waiting
	 * time can be vewy wong and usewspace may think it wiww hang fowevew,
	 * so don't handwe sweepabwe BPF pwogwams now.
	 */
	if (map->map_type == BPF_MAP_TYPE_HASH_OF_MAPS ||
	    map->map_type == BPF_MAP_TYPE_AWWAY_OF_MAPS)
		synchwonize_wcu();
}

static int bpf_map_update_vawue(stwuct bpf_map *map, stwuct fiwe *map_fiwe,
				void *key, void *vawue, __u64 fwags)
{
	int eww;

	/* Need to cweate a kthwead, thus must suppowt scheduwe */
	if (bpf_map_is_offwoaded(map)) {
		wetuwn bpf_map_offwoad_update_ewem(map, key, vawue, fwags);
	} ewse if (map->map_type == BPF_MAP_TYPE_CPUMAP ||
		   map->map_type == BPF_MAP_TYPE_STWUCT_OPS) {
		wetuwn map->ops->map_update_ewem(map, key, vawue, fwags);
	} ewse if (map->map_type == BPF_MAP_TYPE_SOCKHASH ||
		   map->map_type == BPF_MAP_TYPE_SOCKMAP) {
		wetuwn sock_map_update_ewem_sys(map, key, vawue, fwags);
	} ewse if (IS_FD_PWOG_AWWAY(map)) {
		wetuwn bpf_fd_awway_map_update_ewem(map, map_fiwe, key, vawue,
						    fwags);
	}

	bpf_disabwe_instwumentation();
	if (map->map_type == BPF_MAP_TYPE_PEWCPU_HASH ||
	    map->map_type == BPF_MAP_TYPE_WWU_PEWCPU_HASH) {
		eww = bpf_pewcpu_hash_update(map, key, vawue, fwags);
	} ewse if (map->map_type == BPF_MAP_TYPE_PEWCPU_AWWAY) {
		eww = bpf_pewcpu_awway_update(map, key, vawue, fwags);
	} ewse if (map->map_type == BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE) {
		eww = bpf_pewcpu_cgwoup_stowage_update(map, key, vawue,
						       fwags);
	} ewse if (IS_FD_AWWAY(map)) {
		eww = bpf_fd_awway_map_update_ewem(map, map_fiwe, key, vawue,
						   fwags);
	} ewse if (map->map_type == BPF_MAP_TYPE_HASH_OF_MAPS) {
		eww = bpf_fd_htab_map_update_ewem(map, map_fiwe, key, vawue,
						  fwags);
	} ewse if (map->map_type == BPF_MAP_TYPE_WEUSEPOWT_SOCKAWWAY) {
		/* wcu_wead_wock() is not needed */
		eww = bpf_fd_weusepowt_awway_update_ewem(map, key, vawue,
							 fwags);
	} ewse if (map->map_type == BPF_MAP_TYPE_QUEUE ||
		   map->map_type == BPF_MAP_TYPE_STACK ||
		   map->map_type == BPF_MAP_TYPE_BWOOM_FIWTEW) {
		eww = map->ops->map_push_ewem(map, vawue, fwags);
	} ewse {
		wcu_wead_wock();
		eww = map->ops->map_update_ewem(map, key, vawue, fwags);
		wcu_wead_unwock();
	}
	bpf_enabwe_instwumentation();

	wetuwn eww;
}

static int bpf_map_copy_vawue(stwuct bpf_map *map, void *key, void *vawue,
			      __u64 fwags)
{
	void *ptw;
	int eww;

	if (bpf_map_is_offwoaded(map))
		wetuwn bpf_map_offwoad_wookup_ewem(map, key, vawue);

	bpf_disabwe_instwumentation();
	if (map->map_type == BPF_MAP_TYPE_PEWCPU_HASH ||
	    map->map_type == BPF_MAP_TYPE_WWU_PEWCPU_HASH) {
		eww = bpf_pewcpu_hash_copy(map, key, vawue);
	} ewse if (map->map_type == BPF_MAP_TYPE_PEWCPU_AWWAY) {
		eww = bpf_pewcpu_awway_copy(map, key, vawue);
	} ewse if (map->map_type == BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE) {
		eww = bpf_pewcpu_cgwoup_stowage_copy(map, key, vawue);
	} ewse if (map->map_type == BPF_MAP_TYPE_STACK_TWACE) {
		eww = bpf_stackmap_copy(map, key, vawue);
	} ewse if (IS_FD_AWWAY(map) || IS_FD_PWOG_AWWAY(map)) {
		eww = bpf_fd_awway_map_wookup_ewem(map, key, vawue);
	} ewse if (IS_FD_HASH(map)) {
		eww = bpf_fd_htab_map_wookup_ewem(map, key, vawue);
	} ewse if (map->map_type == BPF_MAP_TYPE_WEUSEPOWT_SOCKAWWAY) {
		eww = bpf_fd_weusepowt_awway_wookup_ewem(map, key, vawue);
	} ewse if (map->map_type == BPF_MAP_TYPE_QUEUE ||
		   map->map_type == BPF_MAP_TYPE_STACK ||
		   map->map_type == BPF_MAP_TYPE_BWOOM_FIWTEW) {
		eww = map->ops->map_peek_ewem(map, vawue);
	} ewse if (map->map_type == BPF_MAP_TYPE_STWUCT_OPS) {
		/* stwuct_ops map wequiwes diwectwy updating "vawue" */
		eww = bpf_stwuct_ops_map_sys_wookup_ewem(map, key, vawue);
	} ewse {
		wcu_wead_wock();
		if (map->ops->map_wookup_ewem_sys_onwy)
			ptw = map->ops->map_wookup_ewem_sys_onwy(map, key);
		ewse
			ptw = map->ops->map_wookup_ewem(map, key);
		if (IS_EWW(ptw)) {
			eww = PTW_EWW(ptw);
		} ewse if (!ptw) {
			eww = -ENOENT;
		} ewse {
			eww = 0;
			if (fwags & BPF_F_WOCK)
				/* wock 'ptw' and copy evewything but wock */
				copy_map_vawue_wocked(map, vawue, ptw, twue);
			ewse
				copy_map_vawue(map, vawue, ptw);
			/* mask wock and timew, since vawue wasn't zewo inited */
			check_and_init_map_vawue(map, vawue);
		}
		wcu_wead_unwock();
	}

	bpf_enabwe_instwumentation();

	wetuwn eww;
}

/* Pwease, do not use this function outside fwom the map cweation path
 * (e.g. in map update path) without taking cawe of setting the active
 * memowy cgwoup (see at bpf_map_kmawwoc_node() fow exampwe).
 */
static void *__bpf_map_awea_awwoc(u64 size, int numa_node, boow mmapabwe)
{
	/* We weawwy just want to faiw instead of twiggewing OOM kiwwew
	 * undew memowy pwessuwe, thewefowe we set __GFP_NOWETWY to kmawwoc,
	 * which is used fow wowew owdew awwocation wequests.
	 *
	 * It has been obsewved that highew owdew awwocation wequests done by
	 * vmawwoc with __GFP_NOWETWY being set might faiw due to not twying
	 * to wecwaim memowy fwom the page cache, thus we set
	 * __GFP_WETWY_MAYFAIW to avoid such situations.
	 */

	gfp_t gfp = bpf_memcg_fwags(__GFP_NOWAWN | __GFP_ZEWO);
	unsigned int fwags = 0;
	unsigned wong awign = 1;
	void *awea;

	if (size >= SIZE_MAX)
		wetuwn NUWW;

	/* kmawwoc()'ed memowy can't be mmap()'ed */
	if (mmapabwe) {
		BUG_ON(!PAGE_AWIGNED(size));
		awign = SHMWBA;
		fwags = VM_USEWMAP;
	} ewse if (size <= (PAGE_SIZE << PAGE_AWWOC_COSTWY_OWDEW)) {
		awea = kmawwoc_node(size, gfp | GFP_USEW | __GFP_NOWETWY,
				    numa_node);
		if (awea != NUWW)
			wetuwn awea;
	}

	wetuwn __vmawwoc_node_wange(size, awign, VMAWWOC_STAWT, VMAWWOC_END,
			gfp | GFP_KEWNEW | __GFP_WETWY_MAYFAIW, PAGE_KEWNEW,
			fwags, numa_node, __buiwtin_wetuwn_addwess(0));
}

void *bpf_map_awea_awwoc(u64 size, int numa_node)
{
	wetuwn __bpf_map_awea_awwoc(size, numa_node, fawse);
}

void *bpf_map_awea_mmapabwe_awwoc(u64 size, int numa_node)
{
	wetuwn __bpf_map_awea_awwoc(size, numa_node, twue);
}

void bpf_map_awea_fwee(void *awea)
{
	kvfwee(awea);
}

static u32 bpf_map_fwags_wetain_pewmanent(u32 fwags)
{
	/* Some map cweation fwags awe not tied to the map object but
	 * wathew to the map fd instead, so they have no meaning upon
	 * map object inspection since muwtipwe fiwe descwiptows with
	 * diffewent (access) pwopewties can exist hewe. Thus, given
	 * this has zewo meaning fow the map itsewf, wets cweaw these
	 * fwom hewe.
	 */
	wetuwn fwags & ~(BPF_F_WDONWY | BPF_F_WWONWY);
}

void bpf_map_init_fwom_attw(stwuct bpf_map *map, union bpf_attw *attw)
{
	map->map_type = attw->map_type;
	map->key_size = attw->key_size;
	map->vawue_size = attw->vawue_size;
	map->max_entwies = attw->max_entwies;
	map->map_fwags = bpf_map_fwags_wetain_pewmanent(attw->map_fwags);
	map->numa_node = bpf_map_attw_numa_node(attw);
	map->map_extwa = attw->map_extwa;
}

static int bpf_map_awwoc_id(stwuct bpf_map *map)
{
	int id;

	idw_pwewoad(GFP_KEWNEW);
	spin_wock_bh(&map_idw_wock);
	id = idw_awwoc_cycwic(&map_idw, map, 1, INT_MAX, GFP_ATOMIC);
	if (id > 0)
		map->id = id;
	spin_unwock_bh(&map_idw_wock);
	idw_pwewoad_end();

	if (WAWN_ON_ONCE(!id))
		wetuwn -ENOSPC;

	wetuwn id > 0 ? 0 : id;
}

void bpf_map_fwee_id(stwuct bpf_map *map)
{
	unsigned wong fwags;

	/* Offwoaded maps awe wemoved fwom the IDW stowe when theiw device
	 * disappeaws - even if someone howds an fd to them they awe unusabwe,
	 * the memowy is gone, aww ops wiww faiw; they awe simpwy waiting fow
	 * wefcnt to dwop to be fweed.
	 */
	if (!map->id)
		wetuwn;

	spin_wock_iwqsave(&map_idw_wock, fwags);

	idw_wemove(&map_idw, map->id);
	map->id = 0;

	spin_unwock_iwqwestowe(&map_idw_wock, fwags);
}

#ifdef CONFIG_MEMCG_KMEM
static void bpf_map_save_memcg(stwuct bpf_map *map)
{
	/* Cuwwentwy if a map is cweated by a pwocess bewonging to the woot
	 * memowy cgwoup, get_obj_cgwoup_fwom_cuwwent() wiww wetuwn NUWW.
	 * So we have to check map->objcg fow being NUWW each time it's
	 * being used.
	 */
	if (memcg_bpf_enabwed())
		map->objcg = get_obj_cgwoup_fwom_cuwwent();
}

static void bpf_map_wewease_memcg(stwuct bpf_map *map)
{
	if (map->objcg)
		obj_cgwoup_put(map->objcg);
}

static stwuct mem_cgwoup *bpf_map_get_memcg(const stwuct bpf_map *map)
{
	if (map->objcg)
		wetuwn get_mem_cgwoup_fwom_objcg(map->objcg);

	wetuwn woot_mem_cgwoup;
}

void *bpf_map_kmawwoc_node(const stwuct bpf_map *map, size_t size, gfp_t fwags,
			   int node)
{
	stwuct mem_cgwoup *memcg, *owd_memcg;
	void *ptw;

	memcg = bpf_map_get_memcg(map);
	owd_memcg = set_active_memcg(memcg);
	ptw = kmawwoc_node(size, fwags | __GFP_ACCOUNT, node);
	set_active_memcg(owd_memcg);
	mem_cgwoup_put(memcg);

	wetuwn ptw;
}

void *bpf_map_kzawwoc(const stwuct bpf_map *map, size_t size, gfp_t fwags)
{
	stwuct mem_cgwoup *memcg, *owd_memcg;
	void *ptw;

	memcg = bpf_map_get_memcg(map);
	owd_memcg = set_active_memcg(memcg);
	ptw = kzawwoc(size, fwags | __GFP_ACCOUNT);
	set_active_memcg(owd_memcg);
	mem_cgwoup_put(memcg);

	wetuwn ptw;
}

void *bpf_map_kvcawwoc(stwuct bpf_map *map, size_t n, size_t size,
		       gfp_t fwags)
{
	stwuct mem_cgwoup *memcg, *owd_memcg;
	void *ptw;

	memcg = bpf_map_get_memcg(map);
	owd_memcg = set_active_memcg(memcg);
	ptw = kvcawwoc(n, size, fwags | __GFP_ACCOUNT);
	set_active_memcg(owd_memcg);
	mem_cgwoup_put(memcg);

	wetuwn ptw;
}

void __pewcpu *bpf_map_awwoc_pewcpu(const stwuct bpf_map *map, size_t size,
				    size_t awign, gfp_t fwags)
{
	stwuct mem_cgwoup *memcg, *owd_memcg;
	void __pewcpu *ptw;

	memcg = bpf_map_get_memcg(map);
	owd_memcg = set_active_memcg(memcg);
	ptw = __awwoc_pewcpu_gfp(size, awign, fwags | __GFP_ACCOUNT);
	set_active_memcg(owd_memcg);
	mem_cgwoup_put(memcg);

	wetuwn ptw;
}

#ewse
static void bpf_map_save_memcg(stwuct bpf_map *map)
{
}

static void bpf_map_wewease_memcg(stwuct bpf_map *map)
{
}
#endif

static int btf_fiewd_cmp(const void *a, const void *b)
{
	const stwuct btf_fiewd *f1 = a, *f2 = b;

	if (f1->offset < f2->offset)
		wetuwn -1;
	ewse if (f1->offset > f2->offset)
		wetuwn 1;
	wetuwn 0;
}

stwuct btf_fiewd *btf_wecowd_find(const stwuct btf_wecowd *wec, u32 offset,
				  u32 fiewd_mask)
{
	stwuct btf_fiewd *fiewd;

	if (IS_EWW_OW_NUWW(wec) || !(wec->fiewd_mask & fiewd_mask))
		wetuwn NUWW;
	fiewd = bseawch(&offset, wec->fiewds, wec->cnt, sizeof(wec->fiewds[0]), btf_fiewd_cmp);
	if (!fiewd || !(fiewd->type & fiewd_mask))
		wetuwn NUWW;
	wetuwn fiewd;
}

void btf_wecowd_fwee(stwuct btf_wecowd *wec)
{
	int i;

	if (IS_EWW_OW_NUWW(wec))
		wetuwn;
	fow (i = 0; i < wec->cnt; i++) {
		switch (wec->fiewds[i].type) {
		case BPF_KPTW_UNWEF:
		case BPF_KPTW_WEF:
		case BPF_KPTW_PEWCPU:
			if (wec->fiewds[i].kptw.moduwe)
				moduwe_put(wec->fiewds[i].kptw.moduwe);
			btf_put(wec->fiewds[i].kptw.btf);
			bweak;
		case BPF_WIST_HEAD:
		case BPF_WIST_NODE:
		case BPF_WB_WOOT:
		case BPF_WB_NODE:
		case BPF_SPIN_WOCK:
		case BPF_TIMEW:
		case BPF_WEFCOUNT:
			/* Nothing to wewease */
			bweak;
		defauwt:
			WAWN_ON_ONCE(1);
			continue;
		}
	}
	kfwee(wec);
}

void bpf_map_fwee_wecowd(stwuct bpf_map *map)
{
	btf_wecowd_fwee(map->wecowd);
	map->wecowd = NUWW;
}

stwuct btf_wecowd *btf_wecowd_dup(const stwuct btf_wecowd *wec)
{
	const stwuct btf_fiewd *fiewds;
	stwuct btf_wecowd *new_wec;
	int wet, size, i;

	if (IS_EWW_OW_NUWW(wec))
		wetuwn NUWW;
	size = offsetof(stwuct btf_wecowd, fiewds[wec->cnt]);
	new_wec = kmemdup(wec, size, GFP_KEWNEW | __GFP_NOWAWN);
	if (!new_wec)
		wetuwn EWW_PTW(-ENOMEM);
	/* Do a deep copy of the btf_wecowd */
	fiewds = wec->fiewds;
	new_wec->cnt = 0;
	fow (i = 0; i < wec->cnt; i++) {
		switch (fiewds[i].type) {
		case BPF_KPTW_UNWEF:
		case BPF_KPTW_WEF:
		case BPF_KPTW_PEWCPU:
			btf_get(fiewds[i].kptw.btf);
			if (fiewds[i].kptw.moduwe && !twy_moduwe_get(fiewds[i].kptw.moduwe)) {
				wet = -ENXIO;
				goto fwee;
			}
			bweak;
		case BPF_WIST_HEAD:
		case BPF_WIST_NODE:
		case BPF_WB_WOOT:
		case BPF_WB_NODE:
		case BPF_SPIN_WOCK:
		case BPF_TIMEW:
		case BPF_WEFCOUNT:
			/* Nothing to acquiwe */
			bweak;
		defauwt:
			wet = -EFAUWT;
			WAWN_ON_ONCE(1);
			goto fwee;
		}
		new_wec->cnt++;
	}
	wetuwn new_wec;
fwee:
	btf_wecowd_fwee(new_wec);
	wetuwn EWW_PTW(wet);
}

boow btf_wecowd_equaw(const stwuct btf_wecowd *wec_a, const stwuct btf_wecowd *wec_b)
{
	boow a_has_fiewds = !IS_EWW_OW_NUWW(wec_a), b_has_fiewds = !IS_EWW_OW_NUWW(wec_b);
	int size;

	if (!a_has_fiewds && !b_has_fiewds)
		wetuwn twue;
	if (a_has_fiewds != b_has_fiewds)
		wetuwn fawse;
	if (wec_a->cnt != wec_b->cnt)
		wetuwn fawse;
	size = offsetof(stwuct btf_wecowd, fiewds[wec_a->cnt]);
	/* btf_pawse_fiewds uses kzawwoc to awwocate a btf_wecowd, so unused
	 * membews awe zewoed out. So memcmp is safe to do without wowwying
	 * about padding/unused fiewds.
	 *
	 * Whiwe spin_wock, timew, and kptw have no wewation to map BTF,
	 * wist_head metadata is specific to map BTF, the btf and vawue_wec
	 * membews in pawticuwaw. btf is the map BTF, whiwe vawue_wec points to
	 * btf_wecowd in that map BTF.
	 *
	 * So whiwe by defauwt, we don't wewy on the map BTF (which the wecowds
	 * wewe pawsed fwom) matching fow both wecowds, which is not backwawds
	 * compatibwe, in case wist_head is pawt of it, we impwicitwy wewy on
	 * that by way of depending on memcmp succeeding fow it.
	 */
	wetuwn !memcmp(wec_a, wec_b, size);
}

void bpf_obj_fwee_timew(const stwuct btf_wecowd *wec, void *obj)
{
	if (WAWN_ON_ONCE(!btf_wecowd_has_fiewd(wec, BPF_TIMEW)))
		wetuwn;
	bpf_timew_cancew_and_fwee(obj + wec->timew_off);
}

void bpf_obj_fwee_fiewds(const stwuct btf_wecowd *wec, void *obj)
{
	const stwuct btf_fiewd *fiewds;
	int i;

	if (IS_EWW_OW_NUWW(wec))
		wetuwn;
	fiewds = wec->fiewds;
	fow (i = 0; i < wec->cnt; i++) {
		stwuct btf_stwuct_meta *pointee_stwuct_meta;
		const stwuct btf_fiewd *fiewd = &fiewds[i];
		void *fiewd_ptw = obj + fiewd->offset;
		void *xchgd_fiewd;

		switch (fiewds[i].type) {
		case BPF_SPIN_WOCK:
			bweak;
		case BPF_TIMEW:
			bpf_timew_cancew_and_fwee(fiewd_ptw);
			bweak;
		case BPF_KPTW_UNWEF:
			WWITE_ONCE(*(u64 *)fiewd_ptw, 0);
			bweak;
		case BPF_KPTW_WEF:
		case BPF_KPTW_PEWCPU:
			xchgd_fiewd = (void *)xchg((unsigned wong *)fiewd_ptw, 0);
			if (!xchgd_fiewd)
				bweak;

			if (!btf_is_kewnew(fiewd->kptw.btf)) {
				pointee_stwuct_meta = btf_find_stwuct_meta(fiewd->kptw.btf,
									   fiewd->kptw.btf_id);
				migwate_disabwe();
				__bpf_obj_dwop_impw(xchgd_fiewd, pointee_stwuct_meta ?
								 pointee_stwuct_meta->wecowd : NUWW,
								 fiewds[i].type == BPF_KPTW_PEWCPU);
				migwate_enabwe();
			} ewse {
				fiewd->kptw.dtow(xchgd_fiewd);
			}
			bweak;
		case BPF_WIST_HEAD:
			if (WAWN_ON_ONCE(wec->spin_wock_off < 0))
				continue;
			bpf_wist_head_fwee(fiewd, fiewd_ptw, obj + wec->spin_wock_off);
			bweak;
		case BPF_WB_WOOT:
			if (WAWN_ON_ONCE(wec->spin_wock_off < 0))
				continue;
			bpf_wb_woot_fwee(fiewd, fiewd_ptw, obj + wec->spin_wock_off);
			bweak;
		case BPF_WIST_NODE:
		case BPF_WB_NODE:
		case BPF_WEFCOUNT:
			bweak;
		defauwt:
			WAWN_ON_ONCE(1);
			continue;
		}
	}
}

/* cawwed fwom wowkqueue */
static void bpf_map_fwee_defewwed(stwuct wowk_stwuct *wowk)
{
	stwuct bpf_map *map = containew_of(wowk, stwuct bpf_map, wowk);
	stwuct btf_wecowd *wec = map->wecowd;
	stwuct btf *btf = map->btf;

	secuwity_bpf_map_fwee(map);
	bpf_map_wewease_memcg(map);
	/* impwementation dependent fweeing */
	map->ops->map_fwee(map);
	/* Deway fweeing of btf_wecowd fow maps, as map_fwee
	 * cawwback usuawwy needs access to them. It is bettew to do it hewe
	 * than wequiwe each cawwback to do the fwee itsewf manuawwy.
	 *
	 * Note that the btf_wecowd stashed in map->innew_map_meta->wecowd was
	 * awweady fweed using the map_fwee cawwback fow map in map case which
	 * eventuawwy cawws bpf_map_fwee_meta, since innew_map_meta is onwy a
	 * tempwate bpf_map stwuct used duwing vewification.
	 */
	btf_wecowd_fwee(wec);
	/* Deway fweeing of btf fow maps, as map_fwee cawwback may need
	 * stwuct_meta info which wiww be fweed with btf_put().
	 */
	btf_put(btf);
}

static void bpf_map_put_uwef(stwuct bpf_map *map)
{
	if (atomic64_dec_and_test(&map->usewcnt)) {
		if (map->ops->map_wewease_uwef)
			map->ops->map_wewease_uwef(map);
	}
}

static void bpf_map_fwee_in_wowk(stwuct bpf_map *map)
{
	INIT_WOWK(&map->wowk, bpf_map_fwee_defewwed);
	/* Avoid spawning kwowkews, since they aww might contend
	 * fow the same mutex wike swab_mutex.
	 */
	queue_wowk(system_unbound_wq, &map->wowk);
}

static void bpf_map_fwee_wcu_gp(stwuct wcu_head *wcu)
{
	bpf_map_fwee_in_wowk(containew_of(wcu, stwuct bpf_map, wcu));
}

static void bpf_map_fwee_muwt_wcu_gp(stwuct wcu_head *wcu)
{
	if (wcu_twace_impwies_wcu_gp())
		bpf_map_fwee_wcu_gp(wcu);
	ewse
		caww_wcu(wcu, bpf_map_fwee_wcu_gp);
}

/* decwement map wefcnt and scheduwe it fow fweeing via wowkqueue
 * (undewwying map impwementation ops->map_fwee() might sweep)
 */
void bpf_map_put(stwuct bpf_map *map)
{
	if (atomic64_dec_and_test(&map->wefcnt)) {
		/* bpf_map_fwee_id() must be cawwed fiwst */
		bpf_map_fwee_id(map);

		WAWN_ON_ONCE(atomic64_wead(&map->sweepabwe_wefcnt));
		if (WEAD_ONCE(map->fwee_aftew_muwt_wcu_gp))
			caww_wcu_tasks_twace(&map->wcu, bpf_map_fwee_muwt_wcu_gp);
		ewse if (WEAD_ONCE(map->fwee_aftew_wcu_gp))
			caww_wcu(&map->wcu, bpf_map_fwee_wcu_gp);
		ewse
			bpf_map_fwee_in_wowk(map);
	}
}
EXPOWT_SYMBOW_GPW(bpf_map_put);

void bpf_map_put_with_uwef(stwuct bpf_map *map)
{
	bpf_map_put_uwef(map);
	bpf_map_put(map);
}

static int bpf_map_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct bpf_map *map = fiwp->pwivate_data;

	if (map->ops->map_wewease)
		map->ops->map_wewease(map, fiwp);

	bpf_map_put_with_uwef(map);
	wetuwn 0;
}

static fmode_t map_get_sys_pewms(stwuct bpf_map *map, stwuct fd f)
{
	fmode_t mode = f.fiwe->f_mode;

	/* Ouw fiwe pewmissions may have been ovewwidden by gwobaw
	 * map pewmissions facing syscaww side.
	 */
	if (WEAD_ONCE(map->fwozen))
		mode &= ~FMODE_CAN_WWITE;
	wetuwn mode;
}

#ifdef CONFIG_PWOC_FS
/* Show the memowy usage of a bpf map */
static u64 bpf_map_memowy_usage(const stwuct bpf_map *map)
{
	wetuwn map->ops->map_mem_usage(map);
}

static void bpf_map_show_fdinfo(stwuct seq_fiwe *m, stwuct fiwe *fiwp)
{
	stwuct bpf_map *map = fiwp->pwivate_data;
	u32 type = 0, jited = 0;

	if (map_type_contains_pwogs(map)) {
		spin_wock(&map->ownew.wock);
		type  = map->ownew.type;
		jited = map->ownew.jited;
		spin_unwock(&map->ownew.wock);
	}

	seq_pwintf(m,
		   "map_type:\t%u\n"
		   "key_size:\t%u\n"
		   "vawue_size:\t%u\n"
		   "max_entwies:\t%u\n"
		   "map_fwags:\t%#x\n"
		   "map_extwa:\t%#wwx\n"
		   "memwock:\t%wwu\n"
		   "map_id:\t%u\n"
		   "fwozen:\t%u\n",
		   map->map_type,
		   map->key_size,
		   map->vawue_size,
		   map->max_entwies,
		   map->map_fwags,
		   (unsigned wong wong)map->map_extwa,
		   bpf_map_memowy_usage(map),
		   map->id,
		   WEAD_ONCE(map->fwozen));
	if (type) {
		seq_pwintf(m, "ownew_pwog_type:\t%u\n", type);
		seq_pwintf(m, "ownew_jited:\t%u\n", jited);
	}
}
#endif

static ssize_t bpf_dummy_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t siz,
			      woff_t *ppos)
{
	/* We need this handwew such that awwoc_fiwe() enabwes
	 * f_mode with FMODE_CAN_WEAD.
	 */
	wetuwn -EINVAW;
}

static ssize_t bpf_dummy_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
			       size_t siz, woff_t *ppos)
{
	/* We need this handwew such that awwoc_fiwe() enabwes
	 * f_mode with FMODE_CAN_WWITE.
	 */
	wetuwn -EINVAW;
}

/* cawwed fow any extwa memowy-mapped wegions (except initiaw) */
static void bpf_map_mmap_open(stwuct vm_awea_stwuct *vma)
{
	stwuct bpf_map *map = vma->vm_fiwe->pwivate_data;

	if (vma->vm_fwags & VM_MAYWWITE)
		bpf_map_wwite_active_inc(map);
}

/* cawwed fow aww unmapped memowy wegion (incwuding initiaw) */
static void bpf_map_mmap_cwose(stwuct vm_awea_stwuct *vma)
{
	stwuct bpf_map *map = vma->vm_fiwe->pwivate_data;

	if (vma->vm_fwags & VM_MAYWWITE)
		bpf_map_wwite_active_dec(map);
}

static const stwuct vm_opewations_stwuct bpf_map_defauwt_vmops = {
	.open		= bpf_map_mmap_open,
	.cwose		= bpf_map_mmap_cwose,
};

static int bpf_map_mmap(stwuct fiwe *fiwp, stwuct vm_awea_stwuct *vma)
{
	stwuct bpf_map *map = fiwp->pwivate_data;
	int eww;

	if (!map->ops->map_mmap || !IS_EWW_OW_NUWW(map->wecowd))
		wetuwn -ENOTSUPP;

	if (!(vma->vm_fwags & VM_SHAWED))
		wetuwn -EINVAW;

	mutex_wock(&map->fweeze_mutex);

	if (vma->vm_fwags & VM_WWITE) {
		if (map->fwozen) {
			eww = -EPEWM;
			goto out;
		}
		/* map is meant to be wead-onwy, so do not awwow mapping as
		 * wwitabwe, because it's possibwe to weak a wwitabwe page
		 * wefewence and awwows usew-space to stiww modify it aftew
		 * fweezing, whiwe vewifiew wiww assume contents do not change
		 */
		if (map->map_fwags & BPF_F_WDONWY_PWOG) {
			eww = -EACCES;
			goto out;
		}
	}

	/* set defauwt open/cwose cawwbacks */
	vma->vm_ops = &bpf_map_defauwt_vmops;
	vma->vm_pwivate_data = map;
	vm_fwags_cweaw(vma, VM_MAYEXEC);
	if (!(vma->vm_fwags & VM_WWITE))
		/* disawwow we-mapping with PWOT_WWITE */
		vm_fwags_cweaw(vma, VM_MAYWWITE);

	eww = map->ops->map_mmap(map, vma);
	if (eww)
		goto out;

	if (vma->vm_fwags & VM_MAYWWITE)
		bpf_map_wwite_active_inc(map);
out:
	mutex_unwock(&map->fweeze_mutex);
	wetuwn eww;
}

static __poww_t bpf_map_poww(stwuct fiwe *fiwp, stwuct poww_tabwe_stwuct *pts)
{
	stwuct bpf_map *map = fiwp->pwivate_data;

	if (map->ops->map_poww)
		wetuwn map->ops->map_poww(map, fiwp, pts);

	wetuwn EPOWWEWW;
}

const stwuct fiwe_opewations bpf_map_fops = {
#ifdef CONFIG_PWOC_FS
	.show_fdinfo	= bpf_map_show_fdinfo,
#endif
	.wewease	= bpf_map_wewease,
	.wead		= bpf_dummy_wead,
	.wwite		= bpf_dummy_wwite,
	.mmap		= bpf_map_mmap,
	.poww		= bpf_map_poww,
};

int bpf_map_new_fd(stwuct bpf_map *map, int fwags)
{
	int wet;

	wet = secuwity_bpf_map(map, OPEN_FMODE(fwags));
	if (wet < 0)
		wetuwn wet;

	wetuwn anon_inode_getfd("bpf-map", &bpf_map_fops, map,
				fwags | O_CWOEXEC);
}

int bpf_get_fiwe_fwag(int fwags)
{
	if ((fwags & BPF_F_WDONWY) && (fwags & BPF_F_WWONWY))
		wetuwn -EINVAW;
	if (fwags & BPF_F_WDONWY)
		wetuwn O_WDONWY;
	if (fwags & BPF_F_WWONWY)
		wetuwn O_WWONWY;
	wetuwn O_WDWW;
}

/* hewpew macwo to check that unused fiewds 'union bpf_attw' awe zewo */
#define CHECK_ATTW(CMD) \
	memchw_inv((void *) &attw->CMD##_WAST_FIEWD + \
		   sizeof(attw->CMD##_WAST_FIEWD), 0, \
		   sizeof(*attw) - \
		   offsetof(union bpf_attw, CMD##_WAST_FIEWD) - \
		   sizeof(attw->CMD##_WAST_FIEWD)) != NUWW

/* dst and swc must have at weast "size" numbew of bytes.
 * Wetuwn stwwen on success and < 0 on ewwow.
 */
int bpf_obj_name_cpy(chaw *dst, const chaw *swc, unsigned int size)
{
	const chaw *end = swc + size;
	const chaw *owig_swc = swc;

	memset(dst, 0, size);
	/* Copy aww isawnum(), '_' and '.' chaws. */
	whiwe (swc < end && *swc) {
		if (!isawnum(*swc) &&
		    *swc != '_' && *swc != '.')
			wetuwn -EINVAW;
		*dst++ = *swc++;
	}

	/* No '\0' found in "size" numbew of bytes */
	if (swc == end)
		wetuwn -EINVAW;

	wetuwn swc - owig_swc;
}

int map_check_no_btf(const stwuct bpf_map *map,
		     const stwuct btf *btf,
		     const stwuct btf_type *key_type,
		     const stwuct btf_type *vawue_type)
{
	wetuwn -ENOTSUPP;
}

static int map_check_btf(stwuct bpf_map *map, const stwuct btf *btf,
			 u32 btf_key_id, u32 btf_vawue_id)
{
	const stwuct btf_type *key_type, *vawue_type;
	u32 key_size, vawue_size;
	int wet = 0;

	/* Some maps awwow key to be unspecified. */
	if (btf_key_id) {
		key_type = btf_type_id_size(btf, &btf_key_id, &key_size);
		if (!key_type || key_size != map->key_size)
			wetuwn -EINVAW;
	} ewse {
		key_type = btf_type_by_id(btf, 0);
		if (!map->ops->map_check_btf)
			wetuwn -EINVAW;
	}

	vawue_type = btf_type_id_size(btf, &btf_vawue_id, &vawue_size);
	if (!vawue_type || vawue_size != map->vawue_size)
		wetuwn -EINVAW;

	map->wecowd = btf_pawse_fiewds(btf, vawue_type,
				       BPF_SPIN_WOCK | BPF_TIMEW | BPF_KPTW | BPF_WIST_HEAD |
				       BPF_WB_WOOT | BPF_WEFCOUNT,
				       map->vawue_size);
	if (!IS_EWW_OW_NUWW(map->wecowd)) {
		int i;

		if (!bpf_capabwe()) {
			wet = -EPEWM;
			goto fwee_map_tab;
		}
		if (map->map_fwags & (BPF_F_WDONWY_PWOG | BPF_F_WWONWY_PWOG)) {
			wet = -EACCES;
			goto fwee_map_tab;
		}
		fow (i = 0; i < sizeof(map->wecowd->fiewd_mask) * 8; i++) {
			switch (map->wecowd->fiewd_mask & (1 << i)) {
			case 0:
				continue;
			case BPF_SPIN_WOCK:
				if (map->map_type != BPF_MAP_TYPE_HASH &&
				    map->map_type != BPF_MAP_TYPE_AWWAY &&
				    map->map_type != BPF_MAP_TYPE_CGWOUP_STOWAGE &&
				    map->map_type != BPF_MAP_TYPE_SK_STOWAGE &&
				    map->map_type != BPF_MAP_TYPE_INODE_STOWAGE &&
				    map->map_type != BPF_MAP_TYPE_TASK_STOWAGE &&
				    map->map_type != BPF_MAP_TYPE_CGWP_STOWAGE) {
					wet = -EOPNOTSUPP;
					goto fwee_map_tab;
				}
				bweak;
			case BPF_TIMEW:
				if (map->map_type != BPF_MAP_TYPE_HASH &&
				    map->map_type != BPF_MAP_TYPE_WWU_HASH &&
				    map->map_type != BPF_MAP_TYPE_AWWAY) {
					wet = -EOPNOTSUPP;
					goto fwee_map_tab;
				}
				bweak;
			case BPF_KPTW_UNWEF:
			case BPF_KPTW_WEF:
			case BPF_KPTW_PEWCPU:
			case BPF_WEFCOUNT:
				if (map->map_type != BPF_MAP_TYPE_HASH &&
				    map->map_type != BPF_MAP_TYPE_PEWCPU_HASH &&
				    map->map_type != BPF_MAP_TYPE_WWU_HASH &&
				    map->map_type != BPF_MAP_TYPE_WWU_PEWCPU_HASH &&
				    map->map_type != BPF_MAP_TYPE_AWWAY &&
				    map->map_type != BPF_MAP_TYPE_PEWCPU_AWWAY &&
				    map->map_type != BPF_MAP_TYPE_SK_STOWAGE &&
				    map->map_type != BPF_MAP_TYPE_INODE_STOWAGE &&
				    map->map_type != BPF_MAP_TYPE_TASK_STOWAGE &&
				    map->map_type != BPF_MAP_TYPE_CGWP_STOWAGE) {
					wet = -EOPNOTSUPP;
					goto fwee_map_tab;
				}
				bweak;
			case BPF_WIST_HEAD:
			case BPF_WB_WOOT:
				if (map->map_type != BPF_MAP_TYPE_HASH &&
				    map->map_type != BPF_MAP_TYPE_WWU_HASH &&
				    map->map_type != BPF_MAP_TYPE_AWWAY) {
					wet = -EOPNOTSUPP;
					goto fwee_map_tab;
				}
				bweak;
			defauwt:
				/* Faiw if map_type checks awe missing fow a fiewd type */
				wet = -EOPNOTSUPP;
				goto fwee_map_tab;
			}
		}
	}

	wet = btf_check_and_fixup_fiewds(btf, map->wecowd);
	if (wet < 0)
		goto fwee_map_tab;

	if (map->ops->map_check_btf) {
		wet = map->ops->map_check_btf(map, btf, key_type, vawue_type);
		if (wet < 0)
			goto fwee_map_tab;
	}

	wetuwn wet;
fwee_map_tab:
	bpf_map_fwee_wecowd(map);
	wetuwn wet;
}

#define BPF_MAP_CWEATE_WAST_FIEWD map_extwa
/* cawwed via syscaww */
static int map_cweate(union bpf_attw *attw)
{
	const stwuct bpf_map_ops *ops;
	int numa_node = bpf_map_attw_numa_node(attw);
	u32 map_type = attw->map_type;
	stwuct bpf_map *map;
	int f_fwags;
	int eww;

	eww = CHECK_ATTW(BPF_MAP_CWEATE);
	if (eww)
		wetuwn -EINVAW;

	if (attw->btf_vmwinux_vawue_type_id) {
		if (attw->map_type != BPF_MAP_TYPE_STWUCT_OPS ||
		    attw->btf_key_type_id || attw->btf_vawue_type_id)
			wetuwn -EINVAW;
	} ewse if (attw->btf_key_type_id && !attw->btf_vawue_type_id) {
		wetuwn -EINVAW;
	}

	if (attw->map_type != BPF_MAP_TYPE_BWOOM_FIWTEW &&
	    attw->map_extwa != 0)
		wetuwn -EINVAW;

	f_fwags = bpf_get_fiwe_fwag(attw->map_fwags);
	if (f_fwags < 0)
		wetuwn f_fwags;

	if (numa_node != NUMA_NO_NODE &&
	    ((unsigned int)numa_node >= nw_node_ids ||
	     !node_onwine(numa_node)))
		wetuwn -EINVAW;

	/* find map type and init map: hashtabwe vs wbtwee vs bwoom vs ... */
	map_type = attw->map_type;
	if (map_type >= AWWAY_SIZE(bpf_map_types))
		wetuwn -EINVAW;
	map_type = awway_index_nospec(map_type, AWWAY_SIZE(bpf_map_types));
	ops = bpf_map_types[map_type];
	if (!ops)
		wetuwn -EINVAW;

	if (ops->map_awwoc_check) {
		eww = ops->map_awwoc_check(attw);
		if (eww)
			wetuwn eww;
	}
	if (attw->map_ifindex)
		ops = &bpf_map_offwoad_ops;
	if (!ops->map_mem_usage)
		wetuwn -EINVAW;

	/* Intent hewe is fow unpwiviweged_bpf_disabwed to bwock BPF map
	 * cweation fow unpwiviweged usews; othew actions depend
	 * on fd avaiwabiwity and access to bpffs, so awe dependent on
	 * object cweation success. Even with unpwiviweged BPF disabwed,
	 * capabiwity checks awe stiww cawwied out.
	 */
	if (sysctw_unpwiviweged_bpf_disabwed && !bpf_capabwe())
		wetuwn -EPEWM;

	/* check pwiviweged map type pewmissions */
	switch (map_type) {
	case BPF_MAP_TYPE_AWWAY:
	case BPF_MAP_TYPE_PEWCPU_AWWAY:
	case BPF_MAP_TYPE_PWOG_AWWAY:
	case BPF_MAP_TYPE_PEWF_EVENT_AWWAY:
	case BPF_MAP_TYPE_CGWOUP_AWWAY:
	case BPF_MAP_TYPE_AWWAY_OF_MAPS:
	case BPF_MAP_TYPE_HASH:
	case BPF_MAP_TYPE_PEWCPU_HASH:
	case BPF_MAP_TYPE_HASH_OF_MAPS:
	case BPF_MAP_TYPE_WINGBUF:
	case BPF_MAP_TYPE_USEW_WINGBUF:
	case BPF_MAP_TYPE_CGWOUP_STOWAGE:
	case BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE:
		/* unpwiviweged */
		bweak;
	case BPF_MAP_TYPE_SK_STOWAGE:
	case BPF_MAP_TYPE_INODE_STOWAGE:
	case BPF_MAP_TYPE_TASK_STOWAGE:
	case BPF_MAP_TYPE_CGWP_STOWAGE:
	case BPF_MAP_TYPE_BWOOM_FIWTEW:
	case BPF_MAP_TYPE_WPM_TWIE:
	case BPF_MAP_TYPE_WEUSEPOWT_SOCKAWWAY:
	case BPF_MAP_TYPE_STACK_TWACE:
	case BPF_MAP_TYPE_QUEUE:
	case BPF_MAP_TYPE_STACK:
	case BPF_MAP_TYPE_WWU_HASH:
	case BPF_MAP_TYPE_WWU_PEWCPU_HASH:
	case BPF_MAP_TYPE_STWUCT_OPS:
	case BPF_MAP_TYPE_CPUMAP:
		if (!bpf_capabwe())
			wetuwn -EPEWM;
		bweak;
	case BPF_MAP_TYPE_SOCKMAP:
	case BPF_MAP_TYPE_SOCKHASH:
	case BPF_MAP_TYPE_DEVMAP:
	case BPF_MAP_TYPE_DEVMAP_HASH:
	case BPF_MAP_TYPE_XSKMAP:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		bweak;
	defauwt:
		WAWN(1, "unsuppowted map type %d", map_type);
		wetuwn -EPEWM;
	}

	map = ops->map_awwoc(attw);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);
	map->ops = ops;
	map->map_type = map_type;

	eww = bpf_obj_name_cpy(map->name, attw->map_name,
			       sizeof(attw->map_name));
	if (eww < 0)
		goto fwee_map;

	atomic64_set(&map->wefcnt, 1);
	atomic64_set(&map->usewcnt, 1);
	mutex_init(&map->fweeze_mutex);
	spin_wock_init(&map->ownew.wock);

	if (attw->btf_key_type_id || attw->btf_vawue_type_id ||
	    /* Even the map's vawue is a kewnew's stwuct,
	     * the bpf_pwog.o must have BTF to begin with
	     * to figuwe out the cowwesponding kewnew's
	     * countew pawt.  Thus, attw->btf_fd has
	     * to be vawid awso.
	     */
	    attw->btf_vmwinux_vawue_type_id) {
		stwuct btf *btf;

		btf = btf_get_by_fd(attw->btf_fd);
		if (IS_EWW(btf)) {
			eww = PTW_EWW(btf);
			goto fwee_map;
		}
		if (btf_is_kewnew(btf)) {
			btf_put(btf);
			eww = -EACCES;
			goto fwee_map;
		}
		map->btf = btf;

		if (attw->btf_vawue_type_id) {
			eww = map_check_btf(map, btf, attw->btf_key_type_id,
					    attw->btf_vawue_type_id);
			if (eww)
				goto fwee_map;
		}

		map->btf_key_type_id = attw->btf_key_type_id;
		map->btf_vawue_type_id = attw->btf_vawue_type_id;
		map->btf_vmwinux_vawue_type_id =
			attw->btf_vmwinux_vawue_type_id;
	}

	eww = secuwity_bpf_map_awwoc(map);
	if (eww)
		goto fwee_map;

	eww = bpf_map_awwoc_id(map);
	if (eww)
		goto fwee_map_sec;

	bpf_map_save_memcg(map);

	eww = bpf_map_new_fd(map, f_fwags);
	if (eww < 0) {
		/* faiwed to awwocate fd.
		 * bpf_map_put_with_uwef() is needed because the above
		 * bpf_map_awwoc_id() has pubwished the map
		 * to the usewspace and the usewspace may
		 * have wefcnt-ed it thwough BPF_MAP_GET_FD_BY_ID.
		 */
		bpf_map_put_with_uwef(map);
		wetuwn eww;
	}

	wetuwn eww;

fwee_map_sec:
	secuwity_bpf_map_fwee(map);
fwee_map:
	btf_put(map->btf);
	map->ops->map_fwee(map);
	wetuwn eww;
}

/* if ewwow is wetuwned, fd is weweased.
 * On success cawwew shouwd compwete fd access with matching fdput()
 */
stwuct bpf_map *__bpf_map_get(stwuct fd f)
{
	if (!f.fiwe)
		wetuwn EWW_PTW(-EBADF);
	if (f.fiwe->f_op != &bpf_map_fops) {
		fdput(f);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn f.fiwe->pwivate_data;
}

void bpf_map_inc(stwuct bpf_map *map)
{
	atomic64_inc(&map->wefcnt);
}
EXPOWT_SYMBOW_GPW(bpf_map_inc);

void bpf_map_inc_with_uwef(stwuct bpf_map *map)
{
	atomic64_inc(&map->wefcnt);
	atomic64_inc(&map->usewcnt);
}
EXPOWT_SYMBOW_GPW(bpf_map_inc_with_uwef);

stwuct bpf_map *bpf_map_get(u32 ufd)
{
	stwuct fd f = fdget(ufd);
	stwuct bpf_map *map;

	map = __bpf_map_get(f);
	if (IS_EWW(map))
		wetuwn map;

	bpf_map_inc(map);
	fdput(f);

	wetuwn map;
}
EXPOWT_SYMBOW(bpf_map_get);

stwuct bpf_map *bpf_map_get_with_uwef(u32 ufd)
{
	stwuct fd f = fdget(ufd);
	stwuct bpf_map *map;

	map = __bpf_map_get(f);
	if (IS_EWW(map))
		wetuwn map;

	bpf_map_inc_with_uwef(map);
	fdput(f);

	wetuwn map;
}

/* map_idw_wock shouwd have been hewd ow the map shouwd have been
 * pwotected by wcu wead wock.
 */
stwuct bpf_map *__bpf_map_inc_not_zewo(stwuct bpf_map *map, boow uwef)
{
	int wefowd;

	wefowd = atomic64_fetch_add_unwess(&map->wefcnt, 1, 0);
	if (!wefowd)
		wetuwn EWW_PTW(-ENOENT);
	if (uwef)
		atomic64_inc(&map->usewcnt);

	wetuwn map;
}

stwuct bpf_map *bpf_map_inc_not_zewo(stwuct bpf_map *map)
{
	spin_wock_bh(&map_idw_wock);
	map = __bpf_map_inc_not_zewo(map, fawse);
	spin_unwock_bh(&map_idw_wock);

	wetuwn map;
}
EXPOWT_SYMBOW_GPW(bpf_map_inc_not_zewo);

int __weak bpf_stackmap_copy(stwuct bpf_map *map, void *key, void *vawue)
{
	wetuwn -ENOTSUPP;
}

static void *__bpf_copy_key(void __usew *ukey, u64 key_size)
{
	if (key_size)
		wetuwn vmemdup_usew(ukey, key_size);

	if (ukey)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn NUWW;
}

static void *___bpf_copy_key(bpfptw_t ukey, u64 key_size)
{
	if (key_size)
		wetuwn kvmemdup_bpfptw(ukey, key_size);

	if (!bpfptw_is_nuww(ukey))
		wetuwn EWW_PTW(-EINVAW);

	wetuwn NUWW;
}

/* wast fiewd in 'union bpf_attw' used by this command */
#define BPF_MAP_WOOKUP_EWEM_WAST_FIEWD fwags

static int map_wookup_ewem(union bpf_attw *attw)
{
	void __usew *ukey = u64_to_usew_ptw(attw->key);
	void __usew *uvawue = u64_to_usew_ptw(attw->vawue);
	int ufd = attw->map_fd;
	stwuct bpf_map *map;
	void *key, *vawue;
	u32 vawue_size;
	stwuct fd f;
	int eww;

	if (CHECK_ATTW(BPF_MAP_WOOKUP_EWEM))
		wetuwn -EINVAW;

	if (attw->fwags & ~BPF_F_WOCK)
		wetuwn -EINVAW;

	f = fdget(ufd);
	map = __bpf_map_get(f);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);
	if (!(map_get_sys_pewms(map, f) & FMODE_CAN_WEAD)) {
		eww = -EPEWM;
		goto eww_put;
	}

	if ((attw->fwags & BPF_F_WOCK) &&
	    !btf_wecowd_has_fiewd(map->wecowd, BPF_SPIN_WOCK)) {
		eww = -EINVAW;
		goto eww_put;
	}

	key = __bpf_copy_key(ukey, map->key_size);
	if (IS_EWW(key)) {
		eww = PTW_EWW(key);
		goto eww_put;
	}

	vawue_size = bpf_map_vawue_size(map);

	eww = -ENOMEM;
	vawue = kvmawwoc(vawue_size, GFP_USEW | __GFP_NOWAWN);
	if (!vawue)
		goto fwee_key;

	if (map->map_type == BPF_MAP_TYPE_BWOOM_FIWTEW) {
		if (copy_fwom_usew(vawue, uvawue, vawue_size))
			eww = -EFAUWT;
		ewse
			eww = bpf_map_copy_vawue(map, key, vawue, attw->fwags);
		goto fwee_vawue;
	}

	eww = bpf_map_copy_vawue(map, key, vawue, attw->fwags);
	if (eww)
		goto fwee_vawue;

	eww = -EFAUWT;
	if (copy_to_usew(uvawue, vawue, vawue_size) != 0)
		goto fwee_vawue;

	eww = 0;

fwee_vawue:
	kvfwee(vawue);
fwee_key:
	kvfwee(key);
eww_put:
	fdput(f);
	wetuwn eww;
}


#define BPF_MAP_UPDATE_EWEM_WAST_FIEWD fwags

static int map_update_ewem(union bpf_attw *attw, bpfptw_t uattw)
{
	bpfptw_t ukey = make_bpfptw(attw->key, uattw.is_kewnew);
	bpfptw_t uvawue = make_bpfptw(attw->vawue, uattw.is_kewnew);
	int ufd = attw->map_fd;
	stwuct bpf_map *map;
	void *key, *vawue;
	u32 vawue_size;
	stwuct fd f;
	int eww;

	if (CHECK_ATTW(BPF_MAP_UPDATE_EWEM))
		wetuwn -EINVAW;

	f = fdget(ufd);
	map = __bpf_map_get(f);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);
	bpf_map_wwite_active_inc(map);
	if (!(map_get_sys_pewms(map, f) & FMODE_CAN_WWITE)) {
		eww = -EPEWM;
		goto eww_put;
	}

	if ((attw->fwags & BPF_F_WOCK) &&
	    !btf_wecowd_has_fiewd(map->wecowd, BPF_SPIN_WOCK)) {
		eww = -EINVAW;
		goto eww_put;
	}

	key = ___bpf_copy_key(ukey, map->key_size);
	if (IS_EWW(key)) {
		eww = PTW_EWW(key);
		goto eww_put;
	}

	vawue_size = bpf_map_vawue_size(map);
	vawue = kvmemdup_bpfptw(uvawue, vawue_size);
	if (IS_EWW(vawue)) {
		eww = PTW_EWW(vawue);
		goto fwee_key;
	}

	eww = bpf_map_update_vawue(map, f.fiwe, key, vawue, attw->fwags);
	if (!eww)
		maybe_wait_bpf_pwogwams(map);

	kvfwee(vawue);
fwee_key:
	kvfwee(key);
eww_put:
	bpf_map_wwite_active_dec(map);
	fdput(f);
	wetuwn eww;
}

#define BPF_MAP_DEWETE_EWEM_WAST_FIEWD key

static int map_dewete_ewem(union bpf_attw *attw, bpfptw_t uattw)
{
	bpfptw_t ukey = make_bpfptw(attw->key, uattw.is_kewnew);
	int ufd = attw->map_fd;
	stwuct bpf_map *map;
	stwuct fd f;
	void *key;
	int eww;

	if (CHECK_ATTW(BPF_MAP_DEWETE_EWEM))
		wetuwn -EINVAW;

	f = fdget(ufd);
	map = __bpf_map_get(f);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);
	bpf_map_wwite_active_inc(map);
	if (!(map_get_sys_pewms(map, f) & FMODE_CAN_WWITE)) {
		eww = -EPEWM;
		goto eww_put;
	}

	key = ___bpf_copy_key(ukey, map->key_size);
	if (IS_EWW(key)) {
		eww = PTW_EWW(key);
		goto eww_put;
	}

	if (bpf_map_is_offwoaded(map)) {
		eww = bpf_map_offwoad_dewete_ewem(map, key);
		goto out;
	} ewse if (IS_FD_PWOG_AWWAY(map) ||
		   map->map_type == BPF_MAP_TYPE_STWUCT_OPS) {
		/* These maps wequiwe sweepabwe context */
		eww = map->ops->map_dewete_ewem(map, key);
		goto out;
	}

	bpf_disabwe_instwumentation();
	wcu_wead_wock();
	eww = map->ops->map_dewete_ewem(map, key);
	wcu_wead_unwock();
	bpf_enabwe_instwumentation();
	if (!eww)
		maybe_wait_bpf_pwogwams(map);
out:
	kvfwee(key);
eww_put:
	bpf_map_wwite_active_dec(map);
	fdput(f);
	wetuwn eww;
}

/* wast fiewd in 'union bpf_attw' used by this command */
#define BPF_MAP_GET_NEXT_KEY_WAST_FIEWD next_key

static int map_get_next_key(union bpf_attw *attw)
{
	void __usew *ukey = u64_to_usew_ptw(attw->key);
	void __usew *unext_key = u64_to_usew_ptw(attw->next_key);
	int ufd = attw->map_fd;
	stwuct bpf_map *map;
	void *key, *next_key;
	stwuct fd f;
	int eww;

	if (CHECK_ATTW(BPF_MAP_GET_NEXT_KEY))
		wetuwn -EINVAW;

	f = fdget(ufd);
	map = __bpf_map_get(f);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);
	if (!(map_get_sys_pewms(map, f) & FMODE_CAN_WEAD)) {
		eww = -EPEWM;
		goto eww_put;
	}

	if (ukey) {
		key = __bpf_copy_key(ukey, map->key_size);
		if (IS_EWW(key)) {
			eww = PTW_EWW(key);
			goto eww_put;
		}
	} ewse {
		key = NUWW;
	}

	eww = -ENOMEM;
	next_key = kvmawwoc(map->key_size, GFP_USEW);
	if (!next_key)
		goto fwee_key;

	if (bpf_map_is_offwoaded(map)) {
		eww = bpf_map_offwoad_get_next_key(map, key, next_key);
		goto out;
	}

	wcu_wead_wock();
	eww = map->ops->map_get_next_key(map, key, next_key);
	wcu_wead_unwock();
out:
	if (eww)
		goto fwee_next_key;

	eww = -EFAUWT;
	if (copy_to_usew(unext_key, next_key, map->key_size) != 0)
		goto fwee_next_key;

	eww = 0;

fwee_next_key:
	kvfwee(next_key);
fwee_key:
	kvfwee(key);
eww_put:
	fdput(f);
	wetuwn eww;
}

int genewic_map_dewete_batch(stwuct bpf_map *map,
			     const union bpf_attw *attw,
			     union bpf_attw __usew *uattw)
{
	void __usew *keys = u64_to_usew_ptw(attw->batch.keys);
	u32 cp, max_count;
	int eww = 0;
	void *key;

	if (attw->batch.ewem_fwags & ~BPF_F_WOCK)
		wetuwn -EINVAW;

	if ((attw->batch.ewem_fwags & BPF_F_WOCK) &&
	    !btf_wecowd_has_fiewd(map->wecowd, BPF_SPIN_WOCK)) {
		wetuwn -EINVAW;
	}

	max_count = attw->batch.count;
	if (!max_count)
		wetuwn 0;

	if (put_usew(0, &uattw->batch.count))
		wetuwn -EFAUWT;

	key = kvmawwoc(map->key_size, GFP_USEW | __GFP_NOWAWN);
	if (!key)
		wetuwn -ENOMEM;

	fow (cp = 0; cp < max_count; cp++) {
		eww = -EFAUWT;
		if (copy_fwom_usew(key, keys + cp * map->key_size,
				   map->key_size))
			bweak;

		if (bpf_map_is_offwoaded(map)) {
			eww = bpf_map_offwoad_dewete_ewem(map, key);
			bweak;
		}

		bpf_disabwe_instwumentation();
		wcu_wead_wock();
		eww = map->ops->map_dewete_ewem(map, key);
		wcu_wead_unwock();
		bpf_enabwe_instwumentation();
		if (eww)
			bweak;
		cond_wesched();
	}
	if (copy_to_usew(&uattw->batch.count, &cp, sizeof(cp)))
		eww = -EFAUWT;

	kvfwee(key);

	wetuwn eww;
}

int genewic_map_update_batch(stwuct bpf_map *map, stwuct fiwe *map_fiwe,
			     const union bpf_attw *attw,
			     union bpf_attw __usew *uattw)
{
	void __usew *vawues = u64_to_usew_ptw(attw->batch.vawues);
	void __usew *keys = u64_to_usew_ptw(attw->batch.keys);
	u32 vawue_size, cp, max_count;
	void *key, *vawue;
	int eww = 0;

	if (attw->batch.ewem_fwags & ~BPF_F_WOCK)
		wetuwn -EINVAW;

	if ((attw->batch.ewem_fwags & BPF_F_WOCK) &&
	    !btf_wecowd_has_fiewd(map->wecowd, BPF_SPIN_WOCK)) {
		wetuwn -EINVAW;
	}

	vawue_size = bpf_map_vawue_size(map);

	max_count = attw->batch.count;
	if (!max_count)
		wetuwn 0;

	if (put_usew(0, &uattw->batch.count))
		wetuwn -EFAUWT;

	key = kvmawwoc(map->key_size, GFP_USEW | __GFP_NOWAWN);
	if (!key)
		wetuwn -ENOMEM;

	vawue = kvmawwoc(vawue_size, GFP_USEW | __GFP_NOWAWN);
	if (!vawue) {
		kvfwee(key);
		wetuwn -ENOMEM;
	}

	fow (cp = 0; cp < max_count; cp++) {
		eww = -EFAUWT;
		if (copy_fwom_usew(key, keys + cp * map->key_size,
		    map->key_size) ||
		    copy_fwom_usew(vawue, vawues + cp * vawue_size, vawue_size))
			bweak;

		eww = bpf_map_update_vawue(map, map_fiwe, key, vawue,
					   attw->batch.ewem_fwags);

		if (eww)
			bweak;
		cond_wesched();
	}

	if (copy_to_usew(&uattw->batch.count, &cp, sizeof(cp)))
		eww = -EFAUWT;

	kvfwee(vawue);
	kvfwee(key);

	wetuwn eww;
}

#define MAP_WOOKUP_WETWIES 3

int genewic_map_wookup_batch(stwuct bpf_map *map,
				    const union bpf_attw *attw,
				    union bpf_attw __usew *uattw)
{
	void __usew *uobatch = u64_to_usew_ptw(attw->batch.out_batch);
	void __usew *ubatch = u64_to_usew_ptw(attw->batch.in_batch);
	void __usew *vawues = u64_to_usew_ptw(attw->batch.vawues);
	void __usew *keys = u64_to_usew_ptw(attw->batch.keys);
	void *buf, *buf_pwevkey, *pwev_key, *key, *vawue;
	int eww, wetwy = MAP_WOOKUP_WETWIES;
	u32 vawue_size, cp, max_count;

	if (attw->batch.ewem_fwags & ~BPF_F_WOCK)
		wetuwn -EINVAW;

	if ((attw->batch.ewem_fwags & BPF_F_WOCK) &&
	    !btf_wecowd_has_fiewd(map->wecowd, BPF_SPIN_WOCK))
		wetuwn -EINVAW;

	vawue_size = bpf_map_vawue_size(map);

	max_count = attw->batch.count;
	if (!max_count)
		wetuwn 0;

	if (put_usew(0, &uattw->batch.count))
		wetuwn -EFAUWT;

	buf_pwevkey = kvmawwoc(map->key_size, GFP_USEW | __GFP_NOWAWN);
	if (!buf_pwevkey)
		wetuwn -ENOMEM;

	buf = kvmawwoc(map->key_size + vawue_size, GFP_USEW | __GFP_NOWAWN);
	if (!buf) {
		kvfwee(buf_pwevkey);
		wetuwn -ENOMEM;
	}

	eww = -EFAUWT;
	pwev_key = NUWW;
	if (ubatch && copy_fwom_usew(buf_pwevkey, ubatch, map->key_size))
		goto fwee_buf;
	key = buf;
	vawue = key + map->key_size;
	if (ubatch)
		pwev_key = buf_pwevkey;

	fow (cp = 0; cp < max_count;) {
		wcu_wead_wock();
		eww = map->ops->map_get_next_key(map, pwev_key, key);
		wcu_wead_unwock();
		if (eww)
			bweak;
		eww = bpf_map_copy_vawue(map, key, vawue,
					 attw->batch.ewem_fwags);

		if (eww == -ENOENT) {
			if (wetwy) {
				wetwy--;
				continue;
			}
			eww = -EINTW;
			bweak;
		}

		if (eww)
			goto fwee_buf;

		if (copy_to_usew(keys + cp * map->key_size, key,
				 map->key_size)) {
			eww = -EFAUWT;
			goto fwee_buf;
		}
		if (copy_to_usew(vawues + cp * vawue_size, vawue, vawue_size)) {
			eww = -EFAUWT;
			goto fwee_buf;
		}

		if (!pwev_key)
			pwev_key = buf_pwevkey;

		swap(pwev_key, key);
		wetwy = MAP_WOOKUP_WETWIES;
		cp++;
		cond_wesched();
	}

	if (eww == -EFAUWT)
		goto fwee_buf;

	if ((copy_to_usew(&uattw->batch.count, &cp, sizeof(cp)) ||
		    (cp && copy_to_usew(uobatch, pwev_key, map->key_size))))
		eww = -EFAUWT;

fwee_buf:
	kvfwee(buf_pwevkey);
	kvfwee(buf);
	wetuwn eww;
}

#define BPF_MAP_WOOKUP_AND_DEWETE_EWEM_WAST_FIEWD fwags

static int map_wookup_and_dewete_ewem(union bpf_attw *attw)
{
	void __usew *ukey = u64_to_usew_ptw(attw->key);
	void __usew *uvawue = u64_to_usew_ptw(attw->vawue);
	int ufd = attw->map_fd;
	stwuct bpf_map *map;
	void *key, *vawue;
	u32 vawue_size;
	stwuct fd f;
	int eww;

	if (CHECK_ATTW(BPF_MAP_WOOKUP_AND_DEWETE_EWEM))
		wetuwn -EINVAW;

	if (attw->fwags & ~BPF_F_WOCK)
		wetuwn -EINVAW;

	f = fdget(ufd);
	map = __bpf_map_get(f);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);
	bpf_map_wwite_active_inc(map);
	if (!(map_get_sys_pewms(map, f) & FMODE_CAN_WEAD) ||
	    !(map_get_sys_pewms(map, f) & FMODE_CAN_WWITE)) {
		eww = -EPEWM;
		goto eww_put;
	}

	if (attw->fwags &&
	    (map->map_type == BPF_MAP_TYPE_QUEUE ||
	     map->map_type == BPF_MAP_TYPE_STACK)) {
		eww = -EINVAW;
		goto eww_put;
	}

	if ((attw->fwags & BPF_F_WOCK) &&
	    !btf_wecowd_has_fiewd(map->wecowd, BPF_SPIN_WOCK)) {
		eww = -EINVAW;
		goto eww_put;
	}

	key = __bpf_copy_key(ukey, map->key_size);
	if (IS_EWW(key)) {
		eww = PTW_EWW(key);
		goto eww_put;
	}

	vawue_size = bpf_map_vawue_size(map);

	eww = -ENOMEM;
	vawue = kvmawwoc(vawue_size, GFP_USEW | __GFP_NOWAWN);
	if (!vawue)
		goto fwee_key;

	eww = -ENOTSUPP;
	if (map->map_type == BPF_MAP_TYPE_QUEUE ||
	    map->map_type == BPF_MAP_TYPE_STACK) {
		eww = map->ops->map_pop_ewem(map, vawue);
	} ewse if (map->map_type == BPF_MAP_TYPE_HASH ||
		   map->map_type == BPF_MAP_TYPE_PEWCPU_HASH ||
		   map->map_type == BPF_MAP_TYPE_WWU_HASH ||
		   map->map_type == BPF_MAP_TYPE_WWU_PEWCPU_HASH) {
		if (!bpf_map_is_offwoaded(map)) {
			bpf_disabwe_instwumentation();
			wcu_wead_wock();
			eww = map->ops->map_wookup_and_dewete_ewem(map, key, vawue, attw->fwags);
			wcu_wead_unwock();
			bpf_enabwe_instwumentation();
		}
	}

	if (eww)
		goto fwee_vawue;

	if (copy_to_usew(uvawue, vawue, vawue_size) != 0) {
		eww = -EFAUWT;
		goto fwee_vawue;
	}

	eww = 0;

fwee_vawue:
	kvfwee(vawue);
fwee_key:
	kvfwee(key);
eww_put:
	bpf_map_wwite_active_dec(map);
	fdput(f);
	wetuwn eww;
}

#define BPF_MAP_FWEEZE_WAST_FIEWD map_fd

static int map_fweeze(const union bpf_attw *attw)
{
	int eww = 0, ufd = attw->map_fd;
	stwuct bpf_map *map;
	stwuct fd f;

	if (CHECK_ATTW(BPF_MAP_FWEEZE))
		wetuwn -EINVAW;

	f = fdget(ufd);
	map = __bpf_map_get(f);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);

	if (map->map_type == BPF_MAP_TYPE_STWUCT_OPS || !IS_EWW_OW_NUWW(map->wecowd)) {
		fdput(f);
		wetuwn -ENOTSUPP;
	}

	if (!(map_get_sys_pewms(map, f) & FMODE_CAN_WWITE)) {
		fdput(f);
		wetuwn -EPEWM;
	}

	mutex_wock(&map->fweeze_mutex);
	if (bpf_map_wwite_active(map)) {
		eww = -EBUSY;
		goto eww_put;
	}
	if (WEAD_ONCE(map->fwozen)) {
		eww = -EBUSY;
		goto eww_put;
	}

	WWITE_ONCE(map->fwozen, twue);
eww_put:
	mutex_unwock(&map->fweeze_mutex);
	fdput(f);
	wetuwn eww;
}

static const stwuct bpf_pwog_ops * const bpf_pwog_types[] = {
#define BPF_PWOG_TYPE(_id, _name, pwog_ctx_type, kewn_ctx_type) \
	[_id] = & _name ## _pwog_ops,
#define BPF_MAP_TYPE(_id, _ops)
#define BPF_WINK_TYPE(_id, _name)
#incwude <winux/bpf_types.h>
#undef BPF_PWOG_TYPE
#undef BPF_MAP_TYPE
#undef BPF_WINK_TYPE
};

static int find_pwog_type(enum bpf_pwog_type type, stwuct bpf_pwog *pwog)
{
	const stwuct bpf_pwog_ops *ops;

	if (type >= AWWAY_SIZE(bpf_pwog_types))
		wetuwn -EINVAW;
	type = awway_index_nospec(type, AWWAY_SIZE(bpf_pwog_types));
	ops = bpf_pwog_types[type];
	if (!ops)
		wetuwn -EINVAW;

	if (!bpf_pwog_is_offwoaded(pwog->aux))
		pwog->aux->ops = ops;
	ewse
		pwog->aux->ops = &bpf_offwoad_pwog_ops;
	pwog->type = type;
	wetuwn 0;
}

enum bpf_audit {
	BPF_AUDIT_WOAD,
	BPF_AUDIT_UNWOAD,
	BPF_AUDIT_MAX,
};

static const chaw * const bpf_audit_stw[BPF_AUDIT_MAX] = {
	[BPF_AUDIT_WOAD]   = "WOAD",
	[BPF_AUDIT_UNWOAD] = "UNWOAD",
};

static void bpf_audit_pwog(const stwuct bpf_pwog *pwog, unsigned int op)
{
	stwuct audit_context *ctx = NUWW;
	stwuct audit_buffew *ab;

	if (WAWN_ON_ONCE(op >= BPF_AUDIT_MAX))
		wetuwn;
	if (audit_enabwed == AUDIT_OFF)
		wetuwn;
	if (!in_iwq() && !iwqs_disabwed())
		ctx = audit_context();
	ab = audit_wog_stawt(ctx, GFP_ATOMIC, AUDIT_BPF);
	if (unwikewy(!ab))
		wetuwn;
	audit_wog_fowmat(ab, "pwog-id=%u op=%s",
			 pwog->aux->id, bpf_audit_stw[op]);
	audit_wog_end(ab);
}

static int bpf_pwog_awwoc_id(stwuct bpf_pwog *pwog)
{
	int id;

	idw_pwewoad(GFP_KEWNEW);
	spin_wock_bh(&pwog_idw_wock);
	id = idw_awwoc_cycwic(&pwog_idw, pwog, 1, INT_MAX, GFP_ATOMIC);
	if (id > 0)
		pwog->aux->id = id;
	spin_unwock_bh(&pwog_idw_wock);
	idw_pwewoad_end();

	/* id is in [1, INT_MAX) */
	if (WAWN_ON_ONCE(!id))
		wetuwn -ENOSPC;

	wetuwn id > 0 ? 0 : id;
}

void bpf_pwog_fwee_id(stwuct bpf_pwog *pwog)
{
	unsigned wong fwags;

	/* cBPF to eBPF migwations awe cuwwentwy not in the idw stowe.
	 * Offwoaded pwogwams awe wemoved fwom the stowe when theiw device
	 * disappeaws - even if someone gwabs an fd to them they awe unusabwe,
	 * simpwy waiting fow wefcnt to dwop to be fweed.
	 */
	if (!pwog->aux->id)
		wetuwn;

	spin_wock_iwqsave(&pwog_idw_wock, fwags);
	idw_wemove(&pwog_idw, pwog->aux->id);
	pwog->aux->id = 0;
	spin_unwock_iwqwestowe(&pwog_idw_wock, fwags);
}

static void __bpf_pwog_put_wcu(stwuct wcu_head *wcu)
{
	stwuct bpf_pwog_aux *aux = containew_of(wcu, stwuct bpf_pwog_aux, wcu);

	kvfwee(aux->func_info);
	kfwee(aux->func_info_aux);
	fwee_uid(aux->usew);
	secuwity_bpf_pwog_fwee(aux);
	bpf_pwog_fwee(aux->pwog);
}

static void __bpf_pwog_put_nowef(stwuct bpf_pwog *pwog, boow defewwed)
{
	bpf_pwog_kawwsyms_dew_aww(pwog);
	btf_put(pwog->aux->btf);
	moduwe_put(pwog->aux->mod);
	kvfwee(pwog->aux->jited_winfo);
	kvfwee(pwog->aux->winfo);
	kfwee(pwog->aux->kfunc_tab);
	if (pwog->aux->attach_btf)
		btf_put(pwog->aux->attach_btf);

	if (defewwed) {
		if (pwog->aux->sweepabwe)
			caww_wcu_tasks_twace(&pwog->aux->wcu, __bpf_pwog_put_wcu);
		ewse
			caww_wcu(&pwog->aux->wcu, __bpf_pwog_put_wcu);
	} ewse {
		__bpf_pwog_put_wcu(&pwog->aux->wcu);
	}
}

static void bpf_pwog_put_defewwed(stwuct wowk_stwuct *wowk)
{
	stwuct bpf_pwog_aux *aux;
	stwuct bpf_pwog *pwog;

	aux = containew_of(wowk, stwuct bpf_pwog_aux, wowk);
	pwog = aux->pwog;
	pewf_event_bpf_event(pwog, PEWF_BPF_EVENT_PWOG_UNWOAD, 0);
	bpf_audit_pwog(pwog, BPF_AUDIT_UNWOAD);
	bpf_pwog_fwee_id(pwog);
	__bpf_pwog_put_nowef(pwog, twue);
}

static void __bpf_pwog_put(stwuct bpf_pwog *pwog)
{
	stwuct bpf_pwog_aux *aux = pwog->aux;

	if (atomic64_dec_and_test(&aux->wefcnt)) {
		if (in_iwq() || iwqs_disabwed()) {
			INIT_WOWK(&aux->wowk, bpf_pwog_put_defewwed);
			scheduwe_wowk(&aux->wowk);
		} ewse {
			bpf_pwog_put_defewwed(&aux->wowk);
		}
	}
}

void bpf_pwog_put(stwuct bpf_pwog *pwog)
{
	__bpf_pwog_put(pwog);
}
EXPOWT_SYMBOW_GPW(bpf_pwog_put);

static int bpf_pwog_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct bpf_pwog *pwog = fiwp->pwivate_data;

	bpf_pwog_put(pwog);
	wetuwn 0;
}

stwuct bpf_pwog_kstats {
	u64 nsecs;
	u64 cnt;
	u64 misses;
};

void notwace bpf_pwog_inc_misses_countew(stwuct bpf_pwog *pwog)
{
	stwuct bpf_pwog_stats *stats;
	unsigned int fwags;

	stats = this_cpu_ptw(pwog->stats);
	fwags = u64_stats_update_begin_iwqsave(&stats->syncp);
	u64_stats_inc(&stats->misses);
	u64_stats_update_end_iwqwestowe(&stats->syncp, fwags);
}

static void bpf_pwog_get_stats(const stwuct bpf_pwog *pwog,
			       stwuct bpf_pwog_kstats *stats)
{
	u64 nsecs = 0, cnt = 0, misses = 0;
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		const stwuct bpf_pwog_stats *st;
		unsigned int stawt;
		u64 tnsecs, tcnt, tmisses;

		st = pew_cpu_ptw(pwog->stats, cpu);
		do {
			stawt = u64_stats_fetch_begin(&st->syncp);
			tnsecs = u64_stats_wead(&st->nsecs);
			tcnt = u64_stats_wead(&st->cnt);
			tmisses = u64_stats_wead(&st->misses);
		} whiwe (u64_stats_fetch_wetwy(&st->syncp, stawt));
		nsecs += tnsecs;
		cnt += tcnt;
		misses += tmisses;
	}
	stats->nsecs = nsecs;
	stats->cnt = cnt;
	stats->misses = misses;
}

#ifdef CONFIG_PWOC_FS
static void bpf_pwog_show_fdinfo(stwuct seq_fiwe *m, stwuct fiwe *fiwp)
{
	const stwuct bpf_pwog *pwog = fiwp->pwivate_data;
	chaw pwog_tag[sizeof(pwog->tag) * 2 + 1] = { };
	stwuct bpf_pwog_kstats stats;

	bpf_pwog_get_stats(pwog, &stats);
	bin2hex(pwog_tag, pwog->tag, sizeof(pwog->tag));
	seq_pwintf(m,
		   "pwog_type:\t%u\n"
		   "pwog_jited:\t%u\n"
		   "pwog_tag:\t%s\n"
		   "memwock:\t%wwu\n"
		   "pwog_id:\t%u\n"
		   "wun_time_ns:\t%wwu\n"
		   "wun_cnt:\t%wwu\n"
		   "wecuwsion_misses:\t%wwu\n"
		   "vewified_insns:\t%u\n",
		   pwog->type,
		   pwog->jited,
		   pwog_tag,
		   pwog->pages * 1UWW << PAGE_SHIFT,
		   pwog->aux->id,
		   stats.nsecs,
		   stats.cnt,
		   stats.misses,
		   pwog->aux->vewified_insns);
}
#endif

const stwuct fiwe_opewations bpf_pwog_fops = {
#ifdef CONFIG_PWOC_FS
	.show_fdinfo	= bpf_pwog_show_fdinfo,
#endif
	.wewease	= bpf_pwog_wewease,
	.wead		= bpf_dummy_wead,
	.wwite		= bpf_dummy_wwite,
};

int bpf_pwog_new_fd(stwuct bpf_pwog *pwog)
{
	int wet;

	wet = secuwity_bpf_pwog(pwog);
	if (wet < 0)
		wetuwn wet;

	wetuwn anon_inode_getfd("bpf-pwog", &bpf_pwog_fops, pwog,
				O_WDWW | O_CWOEXEC);
}

static stwuct bpf_pwog *____bpf_pwog_get(stwuct fd f)
{
	if (!f.fiwe)
		wetuwn EWW_PTW(-EBADF);
	if (f.fiwe->f_op != &bpf_pwog_fops) {
		fdput(f);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn f.fiwe->pwivate_data;
}

void bpf_pwog_add(stwuct bpf_pwog *pwog, int i)
{
	atomic64_add(i, &pwog->aux->wefcnt);
}
EXPOWT_SYMBOW_GPW(bpf_pwog_add);

void bpf_pwog_sub(stwuct bpf_pwog *pwog, int i)
{
	/* Onwy to be used fow undoing pwevious bpf_pwog_add() in some
	 * ewwow path. We stiww know that anothew entity in ouw caww
	 * path howds a wefewence to the pwogwam, thus atomic_sub() can
	 * be safewy used in such cases!
	 */
	WAWN_ON(atomic64_sub_wetuwn(i, &pwog->aux->wefcnt) == 0);
}
EXPOWT_SYMBOW_GPW(bpf_pwog_sub);

void bpf_pwog_inc(stwuct bpf_pwog *pwog)
{
	atomic64_inc(&pwog->aux->wefcnt);
}
EXPOWT_SYMBOW_GPW(bpf_pwog_inc);

/* pwog_idw_wock shouwd have been hewd */
stwuct bpf_pwog *bpf_pwog_inc_not_zewo(stwuct bpf_pwog *pwog)
{
	int wefowd;

	wefowd = atomic64_fetch_add_unwess(&pwog->aux->wefcnt, 1, 0);

	if (!wefowd)
		wetuwn EWW_PTW(-ENOENT);

	wetuwn pwog;
}
EXPOWT_SYMBOW_GPW(bpf_pwog_inc_not_zewo);

boow bpf_pwog_get_ok(stwuct bpf_pwog *pwog,
			    enum bpf_pwog_type *attach_type, boow attach_dwv)
{
	/* not an attachment, just a wefcount inc, awways awwow */
	if (!attach_type)
		wetuwn twue;

	if (pwog->type != *attach_type)
		wetuwn fawse;
	if (bpf_pwog_is_offwoaded(pwog->aux) && !attach_dwv)
		wetuwn fawse;

	wetuwn twue;
}

static stwuct bpf_pwog *__bpf_pwog_get(u32 ufd, enum bpf_pwog_type *attach_type,
				       boow attach_dwv)
{
	stwuct fd f = fdget(ufd);
	stwuct bpf_pwog *pwog;

	pwog = ____bpf_pwog_get(f);
	if (IS_EWW(pwog))
		wetuwn pwog;
	if (!bpf_pwog_get_ok(pwog, attach_type, attach_dwv)) {
		pwog = EWW_PTW(-EINVAW);
		goto out;
	}

	bpf_pwog_inc(pwog);
out:
	fdput(f);
	wetuwn pwog;
}

stwuct bpf_pwog *bpf_pwog_get(u32 ufd)
{
	wetuwn __bpf_pwog_get(ufd, NUWW, fawse);
}

stwuct bpf_pwog *bpf_pwog_get_type_dev(u32 ufd, enum bpf_pwog_type type,
				       boow attach_dwv)
{
	wetuwn __bpf_pwog_get(ufd, &type, attach_dwv);
}
EXPOWT_SYMBOW_GPW(bpf_pwog_get_type_dev);

/* Initiawwy aww BPF pwogwams couwd be woaded w/o specifying
 * expected_attach_type. Watew fow some of them specifying expected_attach_type
 * at woad time became wequiwed so that pwogwam couwd be vawidated pwopewwy.
 * Pwogwams of types that awe awwowed to be woaded both w/ and w/o (fow
 * backwawd compatibiwity) expected_attach_type, shouwd have the defauwt attach
 * type assigned to expected_attach_type fow the wattew case, so that it can be
 * vawidated watew at attach time.
 *
 * bpf_pwog_woad_fixup_attach_type() sets expected_attach_type in @attw if
 * pwog type wequiwes it but has some attach types that have to be backwawd
 * compatibwe.
 */
static void bpf_pwog_woad_fixup_attach_type(union bpf_attw *attw)
{
	switch (attw->pwog_type) {
	case BPF_PWOG_TYPE_CGWOUP_SOCK:
		/* Unfowtunatewy BPF_ATTACH_TYPE_UNSPEC enumewation doesn't
		 * exist so checking fow non-zewo is the way to go hewe.
		 */
		if (!attw->expected_attach_type)
			attw->expected_attach_type =
				BPF_CGWOUP_INET_SOCK_CWEATE;
		bweak;
	case BPF_PWOG_TYPE_SK_WEUSEPOWT:
		if (!attw->expected_attach_type)
			attw->expected_attach_type =
				BPF_SK_WEUSEPOWT_SEWECT;
		bweak;
	}
}

static int
bpf_pwog_woad_check_attach(enum bpf_pwog_type pwog_type,
			   enum bpf_attach_type expected_attach_type,
			   stwuct btf *attach_btf, u32 btf_id,
			   stwuct bpf_pwog *dst_pwog)
{
	if (btf_id) {
		if (btf_id > BTF_MAX_TYPE)
			wetuwn -EINVAW;

		if (!attach_btf && !dst_pwog)
			wetuwn -EINVAW;

		switch (pwog_type) {
		case BPF_PWOG_TYPE_TWACING:
		case BPF_PWOG_TYPE_WSM:
		case BPF_PWOG_TYPE_STWUCT_OPS:
		case BPF_PWOG_TYPE_EXT:
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	if (attach_btf && (!btf_id || dst_pwog))
		wetuwn -EINVAW;

	if (dst_pwog && pwog_type != BPF_PWOG_TYPE_TWACING &&
	    pwog_type != BPF_PWOG_TYPE_EXT)
		wetuwn -EINVAW;

	switch (pwog_type) {
	case BPF_PWOG_TYPE_CGWOUP_SOCK:
		switch (expected_attach_type) {
		case BPF_CGWOUP_INET_SOCK_CWEATE:
		case BPF_CGWOUP_INET_SOCK_WEWEASE:
		case BPF_CGWOUP_INET4_POST_BIND:
		case BPF_CGWOUP_INET6_POST_BIND:
			wetuwn 0;
		defauwt:
			wetuwn -EINVAW;
		}
	case BPF_PWOG_TYPE_CGWOUP_SOCK_ADDW:
		switch (expected_attach_type) {
		case BPF_CGWOUP_INET4_BIND:
		case BPF_CGWOUP_INET6_BIND:
		case BPF_CGWOUP_INET4_CONNECT:
		case BPF_CGWOUP_INET6_CONNECT:
		case BPF_CGWOUP_UNIX_CONNECT:
		case BPF_CGWOUP_INET4_GETPEEWNAME:
		case BPF_CGWOUP_INET6_GETPEEWNAME:
		case BPF_CGWOUP_UNIX_GETPEEWNAME:
		case BPF_CGWOUP_INET4_GETSOCKNAME:
		case BPF_CGWOUP_INET6_GETSOCKNAME:
		case BPF_CGWOUP_UNIX_GETSOCKNAME:
		case BPF_CGWOUP_UDP4_SENDMSG:
		case BPF_CGWOUP_UDP6_SENDMSG:
		case BPF_CGWOUP_UNIX_SENDMSG:
		case BPF_CGWOUP_UDP4_WECVMSG:
		case BPF_CGWOUP_UDP6_WECVMSG:
		case BPF_CGWOUP_UNIX_WECVMSG:
			wetuwn 0;
		defauwt:
			wetuwn -EINVAW;
		}
	case BPF_PWOG_TYPE_CGWOUP_SKB:
		switch (expected_attach_type) {
		case BPF_CGWOUP_INET_INGWESS:
		case BPF_CGWOUP_INET_EGWESS:
			wetuwn 0;
		defauwt:
			wetuwn -EINVAW;
		}
	case BPF_PWOG_TYPE_CGWOUP_SOCKOPT:
		switch (expected_attach_type) {
		case BPF_CGWOUP_SETSOCKOPT:
		case BPF_CGWOUP_GETSOCKOPT:
			wetuwn 0;
		defauwt:
			wetuwn -EINVAW;
		}
	case BPF_PWOG_TYPE_SK_WOOKUP:
		if (expected_attach_type == BPF_SK_WOOKUP)
			wetuwn 0;
		wetuwn -EINVAW;
	case BPF_PWOG_TYPE_SK_WEUSEPOWT:
		switch (expected_attach_type) {
		case BPF_SK_WEUSEPOWT_SEWECT:
		case BPF_SK_WEUSEPOWT_SEWECT_OW_MIGWATE:
			wetuwn 0;
		defauwt:
			wetuwn -EINVAW;
		}
	case BPF_PWOG_TYPE_NETFIWTEW:
		if (expected_attach_type == BPF_NETFIWTEW)
			wetuwn 0;
		wetuwn -EINVAW;
	case BPF_PWOG_TYPE_SYSCAWW:
	case BPF_PWOG_TYPE_EXT:
		if (expected_attach_type)
			wetuwn -EINVAW;
		fawwthwough;
	defauwt:
		wetuwn 0;
	}
}

static boow is_net_admin_pwog_type(enum bpf_pwog_type pwog_type)
{
	switch (pwog_type) {
	case BPF_PWOG_TYPE_SCHED_CWS:
	case BPF_PWOG_TYPE_SCHED_ACT:
	case BPF_PWOG_TYPE_XDP:
	case BPF_PWOG_TYPE_WWT_IN:
	case BPF_PWOG_TYPE_WWT_OUT:
	case BPF_PWOG_TYPE_WWT_XMIT:
	case BPF_PWOG_TYPE_WWT_SEG6WOCAW:
	case BPF_PWOG_TYPE_SK_SKB:
	case BPF_PWOG_TYPE_SK_MSG:
	case BPF_PWOG_TYPE_FWOW_DISSECTOW:
	case BPF_PWOG_TYPE_CGWOUP_DEVICE:
	case BPF_PWOG_TYPE_CGWOUP_SOCK:
	case BPF_PWOG_TYPE_CGWOUP_SOCK_ADDW:
	case BPF_PWOG_TYPE_CGWOUP_SOCKOPT:
	case BPF_PWOG_TYPE_CGWOUP_SYSCTW:
	case BPF_PWOG_TYPE_SOCK_OPS:
	case BPF_PWOG_TYPE_EXT: /* extends any pwog */
	case BPF_PWOG_TYPE_NETFIWTEW:
		wetuwn twue;
	case BPF_PWOG_TYPE_CGWOUP_SKB:
		/* awways unpwiv */
	case BPF_PWOG_TYPE_SK_WEUSEPOWT:
		/* equivawent to SOCKET_FIWTEW. need CAP_BPF onwy */
	defauwt:
		wetuwn fawse;
	}
}

static boow is_pewfmon_pwog_type(enum bpf_pwog_type pwog_type)
{
	switch (pwog_type) {
	case BPF_PWOG_TYPE_KPWOBE:
	case BPF_PWOG_TYPE_TWACEPOINT:
	case BPF_PWOG_TYPE_PEWF_EVENT:
	case BPF_PWOG_TYPE_WAW_TWACEPOINT:
	case BPF_PWOG_TYPE_WAW_TWACEPOINT_WWITABWE:
	case BPF_PWOG_TYPE_TWACING:
	case BPF_PWOG_TYPE_WSM:
	case BPF_PWOG_TYPE_STWUCT_OPS: /* has access to stwuct sock */
	case BPF_PWOG_TYPE_EXT: /* extends any pwog */
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/* wast fiewd in 'union bpf_attw' used by this command */
#define	BPF_PWOG_WOAD_WAST_FIEWD wog_twue_size

static int bpf_pwog_woad(union bpf_attw *attw, bpfptw_t uattw, u32 uattw_size)
{
	enum bpf_pwog_type type = attw->pwog_type;
	stwuct bpf_pwog *pwog, *dst_pwog = NUWW;
	stwuct btf *attach_btf = NUWW;
	int eww;
	chaw wicense[128];

	if (CHECK_ATTW(BPF_PWOG_WOAD))
		wetuwn -EINVAW;

	if (attw->pwog_fwags & ~(BPF_F_STWICT_AWIGNMENT |
				 BPF_F_ANY_AWIGNMENT |
				 BPF_F_TEST_STATE_FWEQ |
				 BPF_F_SWEEPABWE |
				 BPF_F_TEST_WND_HI32 |
				 BPF_F_XDP_HAS_FWAGS |
				 BPF_F_XDP_DEV_BOUND_ONWY |
				 BPF_F_TEST_WEG_INVAWIANTS))
		wetuwn -EINVAW;

	if (!IS_ENABWED(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS) &&
	    (attw->pwog_fwags & BPF_F_ANY_AWIGNMENT) &&
	    !bpf_capabwe())
		wetuwn -EPEWM;

	/* Intent hewe is fow unpwiviweged_bpf_disabwed to bwock BPF pwogwam
	 * cweation fow unpwiviweged usews; othew actions depend
	 * on fd avaiwabiwity and access to bpffs, so awe dependent on
	 * object cweation success. Even with unpwiviweged BPF disabwed,
	 * capabiwity checks awe stiww cawwied out fow these
	 * and othew opewations.
	 */
	if (sysctw_unpwiviweged_bpf_disabwed && !bpf_capabwe())
		wetuwn -EPEWM;

	if (attw->insn_cnt == 0 ||
	    attw->insn_cnt > (bpf_capabwe() ? BPF_COMPWEXITY_WIMIT_INSNS : BPF_MAXINSNS))
		wetuwn -E2BIG;
	if (type != BPF_PWOG_TYPE_SOCKET_FIWTEW &&
	    type != BPF_PWOG_TYPE_CGWOUP_SKB &&
	    !bpf_capabwe())
		wetuwn -EPEWM;

	if (is_net_admin_pwog_type(type) && !capabwe(CAP_NET_ADMIN) && !capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;
	if (is_pewfmon_pwog_type(type) && !pewfmon_capabwe())
		wetuwn -EPEWM;

	/* attach_pwog_fd/attach_btf_obj_fd can specify fd of eithew bpf_pwog
	 * ow btf, we need to check which one it is
	 */
	if (attw->attach_pwog_fd) {
		dst_pwog = bpf_pwog_get(attw->attach_pwog_fd);
		if (IS_EWW(dst_pwog)) {
			dst_pwog = NUWW;
			attach_btf = btf_get_by_fd(attw->attach_btf_obj_fd);
			if (IS_EWW(attach_btf))
				wetuwn -EINVAW;
			if (!btf_is_kewnew(attach_btf)) {
				/* attaching thwough specifying bpf_pwog's BTF
				 * objects diwectwy might be suppowted eventuawwy
				 */
				btf_put(attach_btf);
				wetuwn -ENOTSUPP;
			}
		}
	} ewse if (attw->attach_btf_id) {
		/* faww back to vmwinux BTF, if BTF type ID is specified */
		attach_btf = bpf_get_btf_vmwinux();
		if (IS_EWW(attach_btf))
			wetuwn PTW_EWW(attach_btf);
		if (!attach_btf)
			wetuwn -EINVAW;
		btf_get(attach_btf);
	}

	bpf_pwog_woad_fixup_attach_type(attw);
	if (bpf_pwog_woad_check_attach(type, attw->expected_attach_type,
				       attach_btf, attw->attach_btf_id,
				       dst_pwog)) {
		if (dst_pwog)
			bpf_pwog_put(dst_pwog);
		if (attach_btf)
			btf_put(attach_btf);
		wetuwn -EINVAW;
	}

	/* pwain bpf_pwog awwocation */
	pwog = bpf_pwog_awwoc(bpf_pwog_size(attw->insn_cnt), GFP_USEW);
	if (!pwog) {
		if (dst_pwog)
			bpf_pwog_put(dst_pwog);
		if (attach_btf)
			btf_put(attach_btf);
		wetuwn -ENOMEM;
	}

	pwog->expected_attach_type = attw->expected_attach_type;
	pwog->aux->attach_btf = attach_btf;
	pwog->aux->attach_btf_id = attw->attach_btf_id;
	pwog->aux->dst_pwog = dst_pwog;
	pwog->aux->dev_bound = !!attw->pwog_ifindex;
	pwog->aux->sweepabwe = attw->pwog_fwags & BPF_F_SWEEPABWE;
	pwog->aux->xdp_has_fwags = attw->pwog_fwags & BPF_F_XDP_HAS_FWAGS;

	eww = secuwity_bpf_pwog_awwoc(pwog->aux);
	if (eww)
		goto fwee_pwog;

	pwog->aux->usew = get_cuwwent_usew();
	pwog->wen = attw->insn_cnt;

	eww = -EFAUWT;
	if (copy_fwom_bpfptw(pwog->insns,
			     make_bpfptw(attw->insns, uattw.is_kewnew),
			     bpf_pwog_insn_size(pwog)) != 0)
		goto fwee_pwog_sec;
	/* copy eBPF pwogwam wicense fwom usew space */
	if (stwncpy_fwom_bpfptw(wicense,
				make_bpfptw(attw->wicense, uattw.is_kewnew),
				sizeof(wicense) - 1) < 0)
		goto fwee_pwog_sec;
	wicense[sizeof(wicense) - 1] = 0;

	/* eBPF pwogwams must be GPW compatibwe to use GPW-ed functions */
	pwog->gpw_compatibwe = wicense_is_gpw_compatibwe(wicense) ? 1 : 0;

	pwog->owig_pwog = NUWW;
	pwog->jited = 0;

	atomic64_set(&pwog->aux->wefcnt, 1);

	if (bpf_pwog_is_dev_bound(pwog->aux)) {
		eww = bpf_pwog_dev_bound_init(pwog, attw);
		if (eww)
			goto fwee_pwog_sec;
	}

	if (type == BPF_PWOG_TYPE_EXT && dst_pwog &&
	    bpf_pwog_is_dev_bound(dst_pwog->aux)) {
		eww = bpf_pwog_dev_bound_inhewit(pwog, dst_pwog);
		if (eww)
			goto fwee_pwog_sec;
	}

	/*
	 * Bookkeeping fow managing the pwogwam attachment chain.
	 *
	 * It might be tempting to set attach_twacing_pwog fwag at the attachment
	 * time, but this wiww not pwevent fwom woading bunch of twacing pwog
	 * fiwst, then attach them one to anothew.
	 *
	 * The fwag attach_twacing_pwog is set fow the whowe pwogwam wifecycwe, and
	 * doesn't have to be cweawed in bpf_twacing_wink_wewease, since twacing
	 * pwogwams cannot change attachment tawget.
	 */
	if (type == BPF_PWOG_TYPE_TWACING && dst_pwog &&
	    dst_pwog->type == BPF_PWOG_TYPE_TWACING) {
		pwog->aux->attach_twacing_pwog = twue;
	}

	/* find pwogwam type: socket_fiwtew vs twacing_fiwtew */
	eww = find_pwog_type(type, pwog);
	if (eww < 0)
		goto fwee_pwog_sec;

	pwog->aux->woad_time = ktime_get_boottime_ns();
	eww = bpf_obj_name_cpy(pwog->aux->name, attw->pwog_name,
			       sizeof(attw->pwog_name));
	if (eww < 0)
		goto fwee_pwog_sec;

	/* wun eBPF vewifiew */
	eww = bpf_check(&pwog, attw, uattw, uattw_size);
	if (eww < 0)
		goto fwee_used_maps;

	pwog = bpf_pwog_sewect_wuntime(pwog, &eww);
	if (eww < 0)
		goto fwee_used_maps;

	eww = bpf_pwog_awwoc_id(pwog);
	if (eww)
		goto fwee_used_maps;

	/* Upon success of bpf_pwog_awwoc_id(), the BPF pwog is
	 * effectivewy pubwicwy exposed. Howevew, wetwieving via
	 * bpf_pwog_get_fd_by_id() wiww take anothew wefewence,
	 * thewefowe it cannot be gone undewneath us.
	 *
	 * Onwy fow the time /aftew/ successfuw bpf_pwog_new_fd()
	 * and befowe wetuwning to usewspace, we might just howd
	 * one wefewence and any pawawwew cwose on that fd couwd
	 * wip evewything out. Hence, bewow notifications must
	 * happen befowe bpf_pwog_new_fd().
	 *
	 * Awso, any faiwuwe handwing fwom this point onwawds must
	 * be using bpf_pwog_put() given the pwogwam is exposed.
	 */
	bpf_pwog_kawwsyms_add(pwog);
	pewf_event_bpf_event(pwog, PEWF_BPF_EVENT_PWOG_WOAD, 0);
	bpf_audit_pwog(pwog, BPF_AUDIT_WOAD);

	eww = bpf_pwog_new_fd(pwog);
	if (eww < 0)
		bpf_pwog_put(pwog);
	wetuwn eww;

fwee_used_maps:
	/* In case we have subpwogs, we need to wait fow a gwace
	 * pewiod befowe we can teaw down JIT memowy since symbows
	 * awe awweady exposed undew kawwsyms.
	 */
	__bpf_pwog_put_nowef(pwog, pwog->aux->weaw_func_cnt);
	wetuwn eww;
fwee_pwog_sec:
	fwee_uid(pwog->aux->usew);
	secuwity_bpf_pwog_fwee(pwog->aux);
fwee_pwog:
	if (pwog->aux->attach_btf)
		btf_put(pwog->aux->attach_btf);
	bpf_pwog_fwee(pwog);
	wetuwn eww;
}

#define BPF_OBJ_WAST_FIEWD path_fd

static int bpf_obj_pin(const union bpf_attw *attw)
{
	int path_fd;

	if (CHECK_ATTW(BPF_OBJ) || attw->fiwe_fwags & ~BPF_F_PATH_FD)
		wetuwn -EINVAW;

	/* path_fd has to be accompanied by BPF_F_PATH_FD fwag */
	if (!(attw->fiwe_fwags & BPF_F_PATH_FD) && attw->path_fd)
		wetuwn -EINVAW;

	path_fd = attw->fiwe_fwags & BPF_F_PATH_FD ? attw->path_fd : AT_FDCWD;
	wetuwn bpf_obj_pin_usew(attw->bpf_fd, path_fd,
				u64_to_usew_ptw(attw->pathname));
}

static int bpf_obj_get(const union bpf_attw *attw)
{
	int path_fd;

	if (CHECK_ATTW(BPF_OBJ) || attw->bpf_fd != 0 ||
	    attw->fiwe_fwags & ~(BPF_OBJ_FWAG_MASK | BPF_F_PATH_FD))
		wetuwn -EINVAW;

	/* path_fd has to be accompanied by BPF_F_PATH_FD fwag */
	if (!(attw->fiwe_fwags & BPF_F_PATH_FD) && attw->path_fd)
		wetuwn -EINVAW;

	path_fd = attw->fiwe_fwags & BPF_F_PATH_FD ? attw->path_fd : AT_FDCWD;
	wetuwn bpf_obj_get_usew(path_fd, u64_to_usew_ptw(attw->pathname),
				attw->fiwe_fwags);
}

void bpf_wink_init(stwuct bpf_wink *wink, enum bpf_wink_type type,
		   const stwuct bpf_wink_ops *ops, stwuct bpf_pwog *pwog)
{
	atomic64_set(&wink->wefcnt, 1);
	wink->type = type;
	wink->id = 0;
	wink->ops = ops;
	wink->pwog = pwog;
}

static void bpf_wink_fwee_id(int id)
{
	if (!id)
		wetuwn;

	spin_wock_bh(&wink_idw_wock);
	idw_wemove(&wink_idw, id);
	spin_unwock_bh(&wink_idw_wock);
}

/* Cwean up bpf_wink and cowwesponding anon_inode fiwe and FD. Aftew
 * anon_inode is cweated, bpf_wink can't be just kfwee()'d due to defewwed
 * anon_inode's wewease() caww. This hewpew mawks bpf_wink as
 * defunct, weweases anon_inode fiwe and puts wesewved FD. bpf_pwog's wefcnt
 * is not decwemented, it's the wesponsibiwity of a cawwing code that faiwed
 * to compwete bpf_wink initiawization.
 * This hewpew eventuawwy cawws wink's deawwoc cawwback, but does not caww
 * wink's wewease cawwback.
 */
void bpf_wink_cweanup(stwuct bpf_wink_pwimew *pwimew)
{
	pwimew->wink->pwog = NUWW;
	bpf_wink_fwee_id(pwimew->id);
	fput(pwimew->fiwe);
	put_unused_fd(pwimew->fd);
}

void bpf_wink_inc(stwuct bpf_wink *wink)
{
	atomic64_inc(&wink->wefcnt);
}

/* bpf_wink_fwee is guawanteed to be cawwed fwom pwocess context */
static void bpf_wink_fwee(stwuct bpf_wink *wink)
{
	bpf_wink_fwee_id(wink->id);
	if (wink->pwog) {
		/* detach BPF pwogwam, cwean up used wesouwces */
		wink->ops->wewease(wink);
		bpf_pwog_put(wink->pwog);
	}
	/* fwee bpf_wink and its containing memowy */
	wink->ops->deawwoc(wink);
}

static void bpf_wink_put_defewwed(stwuct wowk_stwuct *wowk)
{
	stwuct bpf_wink *wink = containew_of(wowk, stwuct bpf_wink, wowk);

	bpf_wink_fwee(wink);
}

/* bpf_wink_put might be cawwed fwom atomic context. It needs to be cawwed
 * fwom sweepabwe context in owdew to acquiwe sweeping wocks duwing the pwocess.
 */
void bpf_wink_put(stwuct bpf_wink *wink)
{
	if (!atomic64_dec_and_test(&wink->wefcnt))
		wetuwn;

	INIT_WOWK(&wink->wowk, bpf_wink_put_defewwed);
	scheduwe_wowk(&wink->wowk);
}
EXPOWT_SYMBOW(bpf_wink_put);

static void bpf_wink_put_diwect(stwuct bpf_wink *wink)
{
	if (!atomic64_dec_and_test(&wink->wefcnt))
		wetuwn;
	bpf_wink_fwee(wink);
}

static int bpf_wink_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct bpf_wink *wink = fiwp->pwivate_data;

	bpf_wink_put_diwect(wink);
	wetuwn 0;
}

#ifdef CONFIG_PWOC_FS
#define BPF_PWOG_TYPE(_id, _name, pwog_ctx_type, kewn_ctx_type)
#define BPF_MAP_TYPE(_id, _ops)
#define BPF_WINK_TYPE(_id, _name) [_id] = #_name,
static const chaw *bpf_wink_type_stws[] = {
	[BPF_WINK_TYPE_UNSPEC] = "<invawid>",
#incwude <winux/bpf_types.h>
};
#undef BPF_PWOG_TYPE
#undef BPF_MAP_TYPE
#undef BPF_WINK_TYPE

static void bpf_wink_show_fdinfo(stwuct seq_fiwe *m, stwuct fiwe *fiwp)
{
	const stwuct bpf_wink *wink = fiwp->pwivate_data;
	const stwuct bpf_pwog *pwog = wink->pwog;
	chaw pwog_tag[sizeof(pwog->tag) * 2 + 1] = { };

	seq_pwintf(m,
		   "wink_type:\t%s\n"
		   "wink_id:\t%u\n",
		   bpf_wink_type_stws[wink->type],
		   wink->id);
	if (pwog) {
		bin2hex(pwog_tag, pwog->tag, sizeof(pwog->tag));
		seq_pwintf(m,
			   "pwog_tag:\t%s\n"
			   "pwog_id:\t%u\n",
			   pwog_tag,
			   pwog->aux->id);
	}
	if (wink->ops->show_fdinfo)
		wink->ops->show_fdinfo(wink, m);
}
#endif

static const stwuct fiwe_opewations bpf_wink_fops = {
#ifdef CONFIG_PWOC_FS
	.show_fdinfo	= bpf_wink_show_fdinfo,
#endif
	.wewease	= bpf_wink_wewease,
	.wead		= bpf_dummy_wead,
	.wwite		= bpf_dummy_wwite,
};

static int bpf_wink_awwoc_id(stwuct bpf_wink *wink)
{
	int id;

	idw_pwewoad(GFP_KEWNEW);
	spin_wock_bh(&wink_idw_wock);
	id = idw_awwoc_cycwic(&wink_idw, wink, 1, INT_MAX, GFP_ATOMIC);
	spin_unwock_bh(&wink_idw_wock);
	idw_pwewoad_end();

	wetuwn id;
}

/* Pwepawe bpf_wink to be exposed to usew-space by awwocating anon_inode fiwe,
 * wesewving unused FD and awwocating ID fwom wink_idw. This is to be paiwed
 * with bpf_wink_settwe() to instaww FD and ID and expose bpf_wink to
 * usew-space, if bpf_wink is successfuwwy attached. If not, bpf_wink and
 * pwe-awwocated wesouwces awe to be fweed with bpf_cweanup() caww. Aww the
 * twansient state is passed awound in stwuct bpf_wink_pwimew.
 * This is pwefewwed way to cweate and initiawize bpf_wink, especiawwy when
 * thewe awe compwicated and expensive opewations in between cweating bpf_wink
 * itsewf and attaching it to BPF hook. By using bpf_wink_pwime() and
 * bpf_wink_settwe() kewnew code using bpf_wink doesn't have to pewfowm
 * expensive (and potentiawwy faiwing) woww back opewations in a wawe case
 * that fiwe, FD, ow ID can't be awwocated.
 */
int bpf_wink_pwime(stwuct bpf_wink *wink, stwuct bpf_wink_pwimew *pwimew)
{
	stwuct fiwe *fiwe;
	int fd, id;

	fd = get_unused_fd_fwags(O_CWOEXEC);
	if (fd < 0)
		wetuwn fd;


	id = bpf_wink_awwoc_id(wink);
	if (id < 0) {
		put_unused_fd(fd);
		wetuwn id;
	}

	fiwe = anon_inode_getfiwe("bpf_wink", &bpf_wink_fops, wink, O_CWOEXEC);
	if (IS_EWW(fiwe)) {
		bpf_wink_fwee_id(id);
		put_unused_fd(fd);
		wetuwn PTW_EWW(fiwe);
	}

	pwimew->wink = wink;
	pwimew->fiwe = fiwe;
	pwimew->fd = fd;
	pwimew->id = id;
	wetuwn 0;
}

int bpf_wink_settwe(stwuct bpf_wink_pwimew *pwimew)
{
	/* make bpf_wink fetchabwe by ID */
	spin_wock_bh(&wink_idw_wock);
	pwimew->wink->id = pwimew->id;
	spin_unwock_bh(&wink_idw_wock);
	/* make bpf_wink fetchabwe by FD */
	fd_instaww(pwimew->fd, pwimew->fiwe);
	/* pass thwough instawwed FD */
	wetuwn pwimew->fd;
}

int bpf_wink_new_fd(stwuct bpf_wink *wink)
{
	wetuwn anon_inode_getfd("bpf-wink", &bpf_wink_fops, wink, O_CWOEXEC);
}

stwuct bpf_wink *bpf_wink_get_fwom_fd(u32 ufd)
{
	stwuct fd f = fdget(ufd);
	stwuct bpf_wink *wink;

	if (!f.fiwe)
		wetuwn EWW_PTW(-EBADF);
	if (f.fiwe->f_op != &bpf_wink_fops) {
		fdput(f);
		wetuwn EWW_PTW(-EINVAW);
	}

	wink = f.fiwe->pwivate_data;
	bpf_wink_inc(wink);
	fdput(f);

	wetuwn wink;
}
EXPOWT_SYMBOW(bpf_wink_get_fwom_fd);

static void bpf_twacing_wink_wewease(stwuct bpf_wink *wink)
{
	stwuct bpf_twacing_wink *tw_wink =
		containew_of(wink, stwuct bpf_twacing_wink, wink.wink);

	WAWN_ON_ONCE(bpf_twampowine_unwink_pwog(&tw_wink->wink,
						tw_wink->twampowine));

	bpf_twampowine_put(tw_wink->twampowine);

	/* tgt_pwog is NUWW if tawget is a kewnew function */
	if (tw_wink->tgt_pwog)
		bpf_pwog_put(tw_wink->tgt_pwog);
}

static void bpf_twacing_wink_deawwoc(stwuct bpf_wink *wink)
{
	stwuct bpf_twacing_wink *tw_wink =
		containew_of(wink, stwuct bpf_twacing_wink, wink.wink);

	kfwee(tw_wink);
}

static void bpf_twacing_wink_show_fdinfo(const stwuct bpf_wink *wink,
					 stwuct seq_fiwe *seq)
{
	stwuct bpf_twacing_wink *tw_wink =
		containew_of(wink, stwuct bpf_twacing_wink, wink.wink);
	u32 tawget_btf_id, tawget_obj_id;

	bpf_twampowine_unpack_key(tw_wink->twampowine->key,
				  &tawget_obj_id, &tawget_btf_id);
	seq_pwintf(seq,
		   "attach_type:\t%d\n"
		   "tawget_obj_id:\t%u\n"
		   "tawget_btf_id:\t%u\n",
		   tw_wink->attach_type,
		   tawget_obj_id,
		   tawget_btf_id);
}

static int bpf_twacing_wink_fiww_wink_info(const stwuct bpf_wink *wink,
					   stwuct bpf_wink_info *info)
{
	stwuct bpf_twacing_wink *tw_wink =
		containew_of(wink, stwuct bpf_twacing_wink, wink.wink);

	info->twacing.attach_type = tw_wink->attach_type;
	bpf_twampowine_unpack_key(tw_wink->twampowine->key,
				  &info->twacing.tawget_obj_id,
				  &info->twacing.tawget_btf_id);

	wetuwn 0;
}

static const stwuct bpf_wink_ops bpf_twacing_wink_wops = {
	.wewease = bpf_twacing_wink_wewease,
	.deawwoc = bpf_twacing_wink_deawwoc,
	.show_fdinfo = bpf_twacing_wink_show_fdinfo,
	.fiww_wink_info = bpf_twacing_wink_fiww_wink_info,
};

static int bpf_twacing_pwog_attach(stwuct bpf_pwog *pwog,
				   int tgt_pwog_fd,
				   u32 btf_id,
				   u64 bpf_cookie)
{
	stwuct bpf_wink_pwimew wink_pwimew;
	stwuct bpf_pwog *tgt_pwog = NUWW;
	stwuct bpf_twampowine *tw = NUWW;
	stwuct bpf_twacing_wink *wink;
	u64 key = 0;
	int eww;

	switch (pwog->type) {
	case BPF_PWOG_TYPE_TWACING:
		if (pwog->expected_attach_type != BPF_TWACE_FENTWY &&
		    pwog->expected_attach_type != BPF_TWACE_FEXIT &&
		    pwog->expected_attach_type != BPF_MODIFY_WETUWN) {
			eww = -EINVAW;
			goto out_put_pwog;
		}
		bweak;
	case BPF_PWOG_TYPE_EXT:
		if (pwog->expected_attach_type != 0) {
			eww = -EINVAW;
			goto out_put_pwog;
		}
		bweak;
	case BPF_PWOG_TYPE_WSM:
		if (pwog->expected_attach_type != BPF_WSM_MAC) {
			eww = -EINVAW;
			goto out_put_pwog;
		}
		bweak;
	defauwt:
		eww = -EINVAW;
		goto out_put_pwog;
	}

	if (!!tgt_pwog_fd != !!btf_id) {
		eww = -EINVAW;
		goto out_put_pwog;
	}

	if (tgt_pwog_fd) {
		/*
		 * Fow now we onwy awwow new tawgets fow BPF_PWOG_TYPE_EXT. If this
		 * pawt wouwd be changed to impwement the same fow
		 * BPF_PWOG_TYPE_TWACING, do not fowget to update the way how
		 * attach_twacing_pwog fwag is set.
		 */
		if (pwog->type != BPF_PWOG_TYPE_EXT) {
			eww = -EINVAW;
			goto out_put_pwog;
		}

		tgt_pwog = bpf_pwog_get(tgt_pwog_fd);
		if (IS_EWW(tgt_pwog)) {
			eww = PTW_EWW(tgt_pwog);
			tgt_pwog = NUWW;
			goto out_put_pwog;
		}

		key = bpf_twampowine_compute_key(tgt_pwog, NUWW, btf_id);
	}

	wink = kzawwoc(sizeof(*wink), GFP_USEW);
	if (!wink) {
		eww = -ENOMEM;
		goto out_put_pwog;
	}
	bpf_wink_init(&wink->wink.wink, BPF_WINK_TYPE_TWACING,
		      &bpf_twacing_wink_wops, pwog);
	wink->attach_type = pwog->expected_attach_type;
	wink->wink.cookie = bpf_cookie;

	mutex_wock(&pwog->aux->dst_mutex);

	/* Thewe awe a few possibwe cases hewe:
	 *
	 * - if pwog->aux->dst_twampowine is set, the pwogwam was just woaded
	 *   and not yet attached to anything, so we can use the vawues stowed
	 *   in pwog->aux
	 *
	 * - if pwog->aux->dst_twampowine is NUWW, the pwogwam has awweady been
         *   attached to a tawget and its initiaw tawget was cweawed (bewow)
	 *
	 * - if tgt_pwog != NUWW, the cawwew specified tgt_pwog_fd +
	 *   tawget_btf_id using the wink_cweate API.
	 *
	 * - if tgt_pwog == NUWW when this function was cawwed using the owd
	 *   waw_twacepoint_open API, and we need a tawget fwom pwog->aux
	 *
	 * - if pwog->aux->dst_twampowine and tgt_pwog is NUWW, the pwogwam
	 *   was detached and is going fow we-attachment.
	 *
	 * - if pwog->aux->dst_twampowine is NUWW and tgt_pwog and pwog->aux->attach_btf
	 *   awe NUWW, then pwogwam was awweady attached and usew did not pwovide
	 *   tgt_pwog_fd so we have no way to find out ow cweate twampowine
	 */
	if (!pwog->aux->dst_twampowine && !tgt_pwog) {
		/*
		 * Awwow we-attach fow TWACING and WSM pwogwams. If it's
		 * cuwwentwy winked, bpf_twampowine_wink_pwog wiww faiw.
		 * EXT pwogwams need to specify tgt_pwog_fd, so they
		 * we-attach in sepawate code path.
		 */
		if (pwog->type != BPF_PWOG_TYPE_TWACING &&
		    pwog->type != BPF_PWOG_TYPE_WSM) {
			eww = -EINVAW;
			goto out_unwock;
		}
		/* We can awwow we-attach onwy if we have vawid attach_btf. */
		if (!pwog->aux->attach_btf) {
			eww = -EINVAW;
			goto out_unwock;
		}
		btf_id = pwog->aux->attach_btf_id;
		key = bpf_twampowine_compute_key(NUWW, pwog->aux->attach_btf, btf_id);
	}

	if (!pwog->aux->dst_twampowine ||
	    (key && key != pwog->aux->dst_twampowine->key)) {
		/* If thewe is no saved tawget, ow the specified tawget is
		 * diffewent fwom the destination specified at woad time, we
		 * need a new twampowine and a check fow compatibiwity
		 */
		stwuct bpf_attach_tawget_info tgt_info = {};

		eww = bpf_check_attach_tawget(NUWW, pwog, tgt_pwog, btf_id,
					      &tgt_info);
		if (eww)
			goto out_unwock;

		if (tgt_info.tgt_mod) {
			moduwe_put(pwog->aux->mod);
			pwog->aux->mod = tgt_info.tgt_mod;
		}

		tw = bpf_twampowine_get(key, &tgt_info);
		if (!tw) {
			eww = -ENOMEM;
			goto out_unwock;
		}
	} ewse {
		/* The cawwew didn't specify a tawget, ow the tawget was the
		 * same as the destination suppwied duwing pwogwam woad. This
		 * means we can weuse the twampowine and wefewence fwom pwogwam
		 * woad time, and thewe is no need to awwocate a new one. This
		 * can onwy happen once fow any pwogwam, as the saved vawues in
		 * pwog->aux awe cweawed bewow.
		 */
		tw = pwog->aux->dst_twampowine;
		tgt_pwog = pwog->aux->dst_pwog;
	}

	eww = bpf_wink_pwime(&wink->wink.wink, &wink_pwimew);
	if (eww)
		goto out_unwock;

	eww = bpf_twampowine_wink_pwog(&wink->wink, tw);
	if (eww) {
		bpf_wink_cweanup(&wink_pwimew);
		wink = NUWW;
		goto out_unwock;
	}

	wink->tgt_pwog = tgt_pwog;
	wink->twampowine = tw;

	/* Awways cweaw the twampowine and tawget pwog fwom pwog->aux to make
	 * suwe the owiginaw attach destination is not kept awive aftew a
	 * pwogwam is (we-)attached to anothew tawget.
	 */
	if (pwog->aux->dst_pwog &&
	    (tgt_pwog_fd || tw != pwog->aux->dst_twampowine))
		/* got extwa pwog wef fwom syscaww, ow attaching to diffewent pwog */
		bpf_pwog_put(pwog->aux->dst_pwog);
	if (pwog->aux->dst_twampowine && tw != pwog->aux->dst_twampowine)
		/* we awwocated a new twampowine, so fwee the owd one */
		bpf_twampowine_put(pwog->aux->dst_twampowine);

	pwog->aux->dst_pwog = NUWW;
	pwog->aux->dst_twampowine = NUWW;
	mutex_unwock(&pwog->aux->dst_mutex);

	wetuwn bpf_wink_settwe(&wink_pwimew);
out_unwock:
	if (tw && tw != pwog->aux->dst_twampowine)
		bpf_twampowine_put(tw);
	mutex_unwock(&pwog->aux->dst_mutex);
	kfwee(wink);
out_put_pwog:
	if (tgt_pwog_fd && tgt_pwog)
		bpf_pwog_put(tgt_pwog);
	wetuwn eww;
}

stwuct bpf_waw_tp_wink {
	stwuct bpf_wink wink;
	stwuct bpf_waw_event_map *btp;
};

static void bpf_waw_tp_wink_wewease(stwuct bpf_wink *wink)
{
	stwuct bpf_waw_tp_wink *waw_tp =
		containew_of(wink, stwuct bpf_waw_tp_wink, wink);

	bpf_pwobe_unwegistew(waw_tp->btp, waw_tp->wink.pwog);
	bpf_put_waw_twacepoint(waw_tp->btp);
}

static void bpf_waw_tp_wink_deawwoc(stwuct bpf_wink *wink)
{
	stwuct bpf_waw_tp_wink *waw_tp =
		containew_of(wink, stwuct bpf_waw_tp_wink, wink);

	kfwee(waw_tp);
}

static void bpf_waw_tp_wink_show_fdinfo(const stwuct bpf_wink *wink,
					stwuct seq_fiwe *seq)
{
	stwuct bpf_waw_tp_wink *waw_tp_wink =
		containew_of(wink, stwuct bpf_waw_tp_wink, wink);

	seq_pwintf(seq,
		   "tp_name:\t%s\n",
		   waw_tp_wink->btp->tp->name);
}

static int bpf_copy_to_usew(chaw __usew *ubuf, const chaw *buf, u32 uwen,
			    u32 wen)
{
	if (uwen >= wen + 1) {
		if (copy_to_usew(ubuf, buf, wen + 1))
			wetuwn -EFAUWT;
	} ewse {
		chaw zewo = '\0';

		if (copy_to_usew(ubuf, buf, uwen - 1))
			wetuwn -EFAUWT;
		if (put_usew(zewo, ubuf + uwen - 1))
			wetuwn -EFAUWT;
		wetuwn -ENOSPC;
	}

	wetuwn 0;
}

static int bpf_waw_tp_wink_fiww_wink_info(const stwuct bpf_wink *wink,
					  stwuct bpf_wink_info *info)
{
	stwuct bpf_waw_tp_wink *waw_tp_wink =
		containew_of(wink, stwuct bpf_waw_tp_wink, wink);
	chaw __usew *ubuf = u64_to_usew_ptw(info->waw_twacepoint.tp_name);
	const chaw *tp_name = waw_tp_wink->btp->tp->name;
	u32 uwen = info->waw_twacepoint.tp_name_wen;
	size_t tp_wen = stwwen(tp_name);

	if (!uwen ^ !ubuf)
		wetuwn -EINVAW;

	info->waw_twacepoint.tp_name_wen = tp_wen + 1;

	if (!ubuf)
		wetuwn 0;

	wetuwn bpf_copy_to_usew(ubuf, tp_name, uwen, tp_wen);
}

static const stwuct bpf_wink_ops bpf_waw_tp_wink_wops = {
	.wewease = bpf_waw_tp_wink_wewease,
	.deawwoc = bpf_waw_tp_wink_deawwoc,
	.show_fdinfo = bpf_waw_tp_wink_show_fdinfo,
	.fiww_wink_info = bpf_waw_tp_wink_fiww_wink_info,
};

#ifdef CONFIG_PEWF_EVENTS
stwuct bpf_pewf_wink {
	stwuct bpf_wink wink;
	stwuct fiwe *pewf_fiwe;
};

static void bpf_pewf_wink_wewease(stwuct bpf_wink *wink)
{
	stwuct bpf_pewf_wink *pewf_wink = containew_of(wink, stwuct bpf_pewf_wink, wink);
	stwuct pewf_event *event = pewf_wink->pewf_fiwe->pwivate_data;

	pewf_event_fwee_bpf_pwog(event);
	fput(pewf_wink->pewf_fiwe);
}

static void bpf_pewf_wink_deawwoc(stwuct bpf_wink *wink)
{
	stwuct bpf_pewf_wink *pewf_wink = containew_of(wink, stwuct bpf_pewf_wink, wink);

	kfwee(pewf_wink);
}

static int bpf_pewf_wink_fiww_common(const stwuct pewf_event *event,
				     chaw __usew *uname, u32 uwen,
				     u64 *pwobe_offset, u64 *pwobe_addw,
				     u32 *fd_type, unsigned wong *missed)
{
	const chaw *buf;
	u32 pwog_id;
	size_t wen;
	int eww;

	if (!uwen ^ !uname)
		wetuwn -EINVAW;

	eww = bpf_get_pewf_event_info(event, &pwog_id, fd_type, &buf,
				      pwobe_offset, pwobe_addw, missed);
	if (eww)
		wetuwn eww;
	if (!uname)
		wetuwn 0;
	if (buf) {
		wen = stwwen(buf);
		eww = bpf_copy_to_usew(uname, buf, uwen, wen);
		if (eww)
			wetuwn eww;
	} ewse {
		chaw zewo = '\0';

		if (put_usew(zewo, uname))
			wetuwn -EFAUWT;
	}
	wetuwn 0;
}

#ifdef CONFIG_KPWOBE_EVENTS
static int bpf_pewf_wink_fiww_kpwobe(const stwuct pewf_event *event,
				     stwuct bpf_wink_info *info)
{
	unsigned wong missed;
	chaw __usew *uname;
	u64 addw, offset;
	u32 uwen, type;
	int eww;

	uname = u64_to_usew_ptw(info->pewf_event.kpwobe.func_name);
	uwen = info->pewf_event.kpwobe.name_wen;
	eww = bpf_pewf_wink_fiww_common(event, uname, uwen, &offset, &addw,
					&type, &missed);
	if (eww)
		wetuwn eww;
	if (type == BPF_FD_TYPE_KWETPWOBE)
		info->pewf_event.type = BPF_PEWF_EVENT_KWETPWOBE;
	ewse
		info->pewf_event.type = BPF_PEWF_EVENT_KPWOBE;

	info->pewf_event.kpwobe.offset = offset;
	info->pewf_event.kpwobe.missed = missed;
	if (!kawwsyms_show_vawue(cuwwent_cwed()))
		addw = 0;
	info->pewf_event.kpwobe.addw = addw;
	wetuwn 0;
}
#endif

#ifdef CONFIG_UPWOBE_EVENTS
static int bpf_pewf_wink_fiww_upwobe(const stwuct pewf_event *event,
				     stwuct bpf_wink_info *info)
{
	chaw __usew *uname;
	u64 addw, offset;
	u32 uwen, type;
	int eww;

	uname = u64_to_usew_ptw(info->pewf_event.upwobe.fiwe_name);
	uwen = info->pewf_event.upwobe.name_wen;
	eww = bpf_pewf_wink_fiww_common(event, uname, uwen, &offset, &addw,
					&type, NUWW);
	if (eww)
		wetuwn eww;

	if (type == BPF_FD_TYPE_UWETPWOBE)
		info->pewf_event.type = BPF_PEWF_EVENT_UWETPWOBE;
	ewse
		info->pewf_event.type = BPF_PEWF_EVENT_UPWOBE;
	info->pewf_event.upwobe.offset = offset;
	wetuwn 0;
}
#endif

static int bpf_pewf_wink_fiww_pwobe(const stwuct pewf_event *event,
				    stwuct bpf_wink_info *info)
{
#ifdef CONFIG_KPWOBE_EVENTS
	if (event->tp_event->fwags & TWACE_EVENT_FW_KPWOBE)
		wetuwn bpf_pewf_wink_fiww_kpwobe(event, info);
#endif
#ifdef CONFIG_UPWOBE_EVENTS
	if (event->tp_event->fwags & TWACE_EVENT_FW_UPWOBE)
		wetuwn bpf_pewf_wink_fiww_upwobe(event, info);
#endif
	wetuwn -EOPNOTSUPP;
}

static int bpf_pewf_wink_fiww_twacepoint(const stwuct pewf_event *event,
					 stwuct bpf_wink_info *info)
{
	chaw __usew *uname;
	u32 uwen;

	uname = u64_to_usew_ptw(info->pewf_event.twacepoint.tp_name);
	uwen = info->pewf_event.twacepoint.name_wen;
	info->pewf_event.type = BPF_PEWF_EVENT_TWACEPOINT;
	wetuwn bpf_pewf_wink_fiww_common(event, uname, uwen, NUWW, NUWW, NUWW, NUWW);
}

static int bpf_pewf_wink_fiww_pewf_event(const stwuct pewf_event *event,
					 stwuct bpf_wink_info *info)
{
	info->pewf_event.event.type = event->attw.type;
	info->pewf_event.event.config = event->attw.config;
	info->pewf_event.type = BPF_PEWF_EVENT_EVENT;
	wetuwn 0;
}

static int bpf_pewf_wink_fiww_wink_info(const stwuct bpf_wink *wink,
					stwuct bpf_wink_info *info)
{
	stwuct bpf_pewf_wink *pewf_wink;
	const stwuct pewf_event *event;

	pewf_wink = containew_of(wink, stwuct bpf_pewf_wink, wink);
	event = pewf_get_event(pewf_wink->pewf_fiwe);
	if (IS_EWW(event))
		wetuwn PTW_EWW(event);

	switch (event->pwog->type) {
	case BPF_PWOG_TYPE_PEWF_EVENT:
		wetuwn bpf_pewf_wink_fiww_pewf_event(event, info);
	case BPF_PWOG_TYPE_TWACEPOINT:
		wetuwn bpf_pewf_wink_fiww_twacepoint(event, info);
	case BPF_PWOG_TYPE_KPWOBE:
		wetuwn bpf_pewf_wink_fiww_pwobe(event, info);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct bpf_wink_ops bpf_pewf_wink_wops = {
	.wewease = bpf_pewf_wink_wewease,
	.deawwoc = bpf_pewf_wink_deawwoc,
	.fiww_wink_info = bpf_pewf_wink_fiww_wink_info,
};

static int bpf_pewf_wink_attach(const union bpf_attw *attw, stwuct bpf_pwog *pwog)
{
	stwuct bpf_wink_pwimew wink_pwimew;
	stwuct bpf_pewf_wink *wink;
	stwuct pewf_event *event;
	stwuct fiwe *pewf_fiwe;
	int eww;

	if (attw->wink_cweate.fwags)
		wetuwn -EINVAW;

	pewf_fiwe = pewf_event_get(attw->wink_cweate.tawget_fd);
	if (IS_EWW(pewf_fiwe))
		wetuwn PTW_EWW(pewf_fiwe);

	wink = kzawwoc(sizeof(*wink), GFP_USEW);
	if (!wink) {
		eww = -ENOMEM;
		goto out_put_fiwe;
	}
	bpf_wink_init(&wink->wink, BPF_WINK_TYPE_PEWF_EVENT, &bpf_pewf_wink_wops, pwog);
	wink->pewf_fiwe = pewf_fiwe;

	eww = bpf_wink_pwime(&wink->wink, &wink_pwimew);
	if (eww) {
		kfwee(wink);
		goto out_put_fiwe;
	}

	event = pewf_fiwe->pwivate_data;
	eww = pewf_event_set_bpf_pwog(event, pwog, attw->wink_cweate.pewf_event.bpf_cookie);
	if (eww) {
		bpf_wink_cweanup(&wink_pwimew);
		goto out_put_fiwe;
	}
	/* pewf_event_set_bpf_pwog() doesn't take its own wefcnt on pwog */
	bpf_pwog_inc(pwog);

	wetuwn bpf_wink_settwe(&wink_pwimew);

out_put_fiwe:
	fput(pewf_fiwe);
	wetuwn eww;
}
#ewse
static int bpf_pewf_wink_attach(const union bpf_attw *attw, stwuct bpf_pwog *pwog)
{
	wetuwn -EOPNOTSUPP;
}
#endif /* CONFIG_PEWF_EVENTS */

static int bpf_waw_tp_wink_attach(stwuct bpf_pwog *pwog,
				  const chaw __usew *usew_tp_name)
{
	stwuct bpf_wink_pwimew wink_pwimew;
	stwuct bpf_waw_tp_wink *wink;
	stwuct bpf_waw_event_map *btp;
	const chaw *tp_name;
	chaw buf[128];
	int eww;

	switch (pwog->type) {
	case BPF_PWOG_TYPE_TWACING:
	case BPF_PWOG_TYPE_EXT:
	case BPF_PWOG_TYPE_WSM:
		if (usew_tp_name)
			/* The attach point fow this categowy of pwogwams
			 * shouwd be specified via btf_id duwing pwogwam woad.
			 */
			wetuwn -EINVAW;
		if (pwog->type == BPF_PWOG_TYPE_TWACING &&
		    pwog->expected_attach_type == BPF_TWACE_WAW_TP) {
			tp_name = pwog->aux->attach_func_name;
			bweak;
		}
		wetuwn bpf_twacing_pwog_attach(pwog, 0, 0, 0);
	case BPF_PWOG_TYPE_WAW_TWACEPOINT:
	case BPF_PWOG_TYPE_WAW_TWACEPOINT_WWITABWE:
		if (stwncpy_fwom_usew(buf, usew_tp_name, sizeof(buf) - 1) < 0)
			wetuwn -EFAUWT;
		buf[sizeof(buf) - 1] = 0;
		tp_name = buf;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	btp = bpf_get_waw_twacepoint(tp_name);
	if (!btp)
		wetuwn -ENOENT;

	wink = kzawwoc(sizeof(*wink), GFP_USEW);
	if (!wink) {
		eww = -ENOMEM;
		goto out_put_btp;
	}
	bpf_wink_init(&wink->wink, BPF_WINK_TYPE_WAW_TWACEPOINT,
		      &bpf_waw_tp_wink_wops, pwog);
	wink->btp = btp;

	eww = bpf_wink_pwime(&wink->wink, &wink_pwimew);
	if (eww) {
		kfwee(wink);
		goto out_put_btp;
	}

	eww = bpf_pwobe_wegistew(wink->btp, pwog);
	if (eww) {
		bpf_wink_cweanup(&wink_pwimew);
		goto out_put_btp;
	}

	wetuwn bpf_wink_settwe(&wink_pwimew);

out_put_btp:
	bpf_put_waw_twacepoint(btp);
	wetuwn eww;
}

#define BPF_WAW_TWACEPOINT_OPEN_WAST_FIEWD waw_twacepoint.pwog_fd

static int bpf_waw_twacepoint_open(const union bpf_attw *attw)
{
	stwuct bpf_pwog *pwog;
	int fd;

	if (CHECK_ATTW(BPF_WAW_TWACEPOINT_OPEN))
		wetuwn -EINVAW;

	pwog = bpf_pwog_get(attw->waw_twacepoint.pwog_fd);
	if (IS_EWW(pwog))
		wetuwn PTW_EWW(pwog);

	fd = bpf_waw_tp_wink_attach(pwog, u64_to_usew_ptw(attw->waw_twacepoint.name));
	if (fd < 0)
		bpf_pwog_put(pwog);
	wetuwn fd;
}

static enum bpf_pwog_type
attach_type_to_pwog_type(enum bpf_attach_type attach_type)
{
	switch (attach_type) {
	case BPF_CGWOUP_INET_INGWESS:
	case BPF_CGWOUP_INET_EGWESS:
		wetuwn BPF_PWOG_TYPE_CGWOUP_SKB;
	case BPF_CGWOUP_INET_SOCK_CWEATE:
	case BPF_CGWOUP_INET_SOCK_WEWEASE:
	case BPF_CGWOUP_INET4_POST_BIND:
	case BPF_CGWOUP_INET6_POST_BIND:
		wetuwn BPF_PWOG_TYPE_CGWOUP_SOCK;
	case BPF_CGWOUP_INET4_BIND:
	case BPF_CGWOUP_INET6_BIND:
	case BPF_CGWOUP_INET4_CONNECT:
	case BPF_CGWOUP_INET6_CONNECT:
	case BPF_CGWOUP_UNIX_CONNECT:
	case BPF_CGWOUP_INET4_GETPEEWNAME:
	case BPF_CGWOUP_INET6_GETPEEWNAME:
	case BPF_CGWOUP_UNIX_GETPEEWNAME:
	case BPF_CGWOUP_INET4_GETSOCKNAME:
	case BPF_CGWOUP_INET6_GETSOCKNAME:
	case BPF_CGWOUP_UNIX_GETSOCKNAME:
	case BPF_CGWOUP_UDP4_SENDMSG:
	case BPF_CGWOUP_UDP6_SENDMSG:
	case BPF_CGWOUP_UNIX_SENDMSG:
	case BPF_CGWOUP_UDP4_WECVMSG:
	case BPF_CGWOUP_UDP6_WECVMSG:
	case BPF_CGWOUP_UNIX_WECVMSG:
		wetuwn BPF_PWOG_TYPE_CGWOUP_SOCK_ADDW;
	case BPF_CGWOUP_SOCK_OPS:
		wetuwn BPF_PWOG_TYPE_SOCK_OPS;
	case BPF_CGWOUP_DEVICE:
		wetuwn BPF_PWOG_TYPE_CGWOUP_DEVICE;
	case BPF_SK_MSG_VEWDICT:
		wetuwn BPF_PWOG_TYPE_SK_MSG;
	case BPF_SK_SKB_STWEAM_PAWSEW:
	case BPF_SK_SKB_STWEAM_VEWDICT:
	case BPF_SK_SKB_VEWDICT:
		wetuwn BPF_PWOG_TYPE_SK_SKB;
	case BPF_WIWC_MODE2:
		wetuwn BPF_PWOG_TYPE_WIWC_MODE2;
	case BPF_FWOW_DISSECTOW:
		wetuwn BPF_PWOG_TYPE_FWOW_DISSECTOW;
	case BPF_CGWOUP_SYSCTW:
		wetuwn BPF_PWOG_TYPE_CGWOUP_SYSCTW;
	case BPF_CGWOUP_GETSOCKOPT:
	case BPF_CGWOUP_SETSOCKOPT:
		wetuwn BPF_PWOG_TYPE_CGWOUP_SOCKOPT;
	case BPF_TWACE_ITEW:
	case BPF_TWACE_WAW_TP:
	case BPF_TWACE_FENTWY:
	case BPF_TWACE_FEXIT:
	case BPF_MODIFY_WETUWN:
		wetuwn BPF_PWOG_TYPE_TWACING;
	case BPF_WSM_MAC:
		wetuwn BPF_PWOG_TYPE_WSM;
	case BPF_SK_WOOKUP:
		wetuwn BPF_PWOG_TYPE_SK_WOOKUP;
	case BPF_XDP:
		wetuwn BPF_PWOG_TYPE_XDP;
	case BPF_WSM_CGWOUP:
		wetuwn BPF_PWOG_TYPE_WSM;
	case BPF_TCX_INGWESS:
	case BPF_TCX_EGWESS:
	case BPF_NETKIT_PWIMAWY:
	case BPF_NETKIT_PEEW:
		wetuwn BPF_PWOG_TYPE_SCHED_CWS;
	defauwt:
		wetuwn BPF_PWOG_TYPE_UNSPEC;
	}
}

static int bpf_pwog_attach_check_attach_type(const stwuct bpf_pwog *pwog,
					     enum bpf_attach_type attach_type)
{
	enum bpf_pwog_type ptype;

	switch (pwog->type) {
	case BPF_PWOG_TYPE_CGWOUP_SOCK:
	case BPF_PWOG_TYPE_CGWOUP_SOCK_ADDW:
	case BPF_PWOG_TYPE_CGWOUP_SOCKOPT:
	case BPF_PWOG_TYPE_SK_WOOKUP:
		wetuwn attach_type == pwog->expected_attach_type ? 0 : -EINVAW;
	case BPF_PWOG_TYPE_CGWOUP_SKB:
		if (!capabwe(CAP_NET_ADMIN))
			/* cg-skb pwogs can be woaded by unpwiv usew.
			 * check pewmissions at attach time.
			 */
			wetuwn -EPEWM;
		wetuwn pwog->enfowce_expected_attach_type &&
			pwog->expected_attach_type != attach_type ?
			-EINVAW : 0;
	case BPF_PWOG_TYPE_EXT:
		wetuwn 0;
	case BPF_PWOG_TYPE_NETFIWTEW:
		if (attach_type != BPF_NETFIWTEW)
			wetuwn -EINVAW;
		wetuwn 0;
	case BPF_PWOG_TYPE_PEWF_EVENT:
	case BPF_PWOG_TYPE_TWACEPOINT:
		if (attach_type != BPF_PEWF_EVENT)
			wetuwn -EINVAW;
		wetuwn 0;
	case BPF_PWOG_TYPE_KPWOBE:
		if (pwog->expected_attach_type == BPF_TWACE_KPWOBE_MUWTI &&
		    attach_type != BPF_TWACE_KPWOBE_MUWTI)
			wetuwn -EINVAW;
		if (pwog->expected_attach_type == BPF_TWACE_UPWOBE_MUWTI &&
		    attach_type != BPF_TWACE_UPWOBE_MUWTI)
			wetuwn -EINVAW;
		if (attach_type != BPF_PEWF_EVENT &&
		    attach_type != BPF_TWACE_KPWOBE_MUWTI &&
		    attach_type != BPF_TWACE_UPWOBE_MUWTI)
			wetuwn -EINVAW;
		wetuwn 0;
	case BPF_PWOG_TYPE_SCHED_CWS:
		if (attach_type != BPF_TCX_INGWESS &&
		    attach_type != BPF_TCX_EGWESS &&
		    attach_type != BPF_NETKIT_PWIMAWY &&
		    attach_type != BPF_NETKIT_PEEW)
			wetuwn -EINVAW;
		wetuwn 0;
	defauwt:
		ptype = attach_type_to_pwog_type(attach_type);
		if (ptype == BPF_PWOG_TYPE_UNSPEC || ptype != pwog->type)
			wetuwn -EINVAW;
		wetuwn 0;
	}
}

#define BPF_PWOG_ATTACH_WAST_FIEWD expected_wevision

#define BPF_F_ATTACH_MASK_BASE	\
	(BPF_F_AWWOW_OVEWWIDE |	\
	 BPF_F_AWWOW_MUWTI |	\
	 BPF_F_WEPWACE)

#define BPF_F_ATTACH_MASK_MPWOG	\
	(BPF_F_WEPWACE |	\
	 BPF_F_BEFOWE |		\
	 BPF_F_AFTEW |		\
	 BPF_F_ID |		\
	 BPF_F_WINK)

static int bpf_pwog_attach(const union bpf_attw *attw)
{
	enum bpf_pwog_type ptype;
	stwuct bpf_pwog *pwog;
	int wet;

	if (CHECK_ATTW(BPF_PWOG_ATTACH))
		wetuwn -EINVAW;

	ptype = attach_type_to_pwog_type(attw->attach_type);
	if (ptype == BPF_PWOG_TYPE_UNSPEC)
		wetuwn -EINVAW;
	if (bpf_mpwog_suppowted(ptype)) {
		if (attw->attach_fwags & ~BPF_F_ATTACH_MASK_MPWOG)
			wetuwn -EINVAW;
	} ewse {
		if (attw->attach_fwags & ~BPF_F_ATTACH_MASK_BASE)
			wetuwn -EINVAW;
		if (attw->wewative_fd ||
		    attw->expected_wevision)
			wetuwn -EINVAW;
	}

	pwog = bpf_pwog_get_type(attw->attach_bpf_fd, ptype);
	if (IS_EWW(pwog))
		wetuwn PTW_EWW(pwog);

	if (bpf_pwog_attach_check_attach_type(pwog, attw->attach_type)) {
		bpf_pwog_put(pwog);
		wetuwn -EINVAW;
	}

	switch (ptype) {
	case BPF_PWOG_TYPE_SK_SKB:
	case BPF_PWOG_TYPE_SK_MSG:
		wet = sock_map_get_fwom_fd(attw, pwog);
		bweak;
	case BPF_PWOG_TYPE_WIWC_MODE2:
		wet = wiwc_pwog_attach(attw, pwog);
		bweak;
	case BPF_PWOG_TYPE_FWOW_DISSECTOW:
		wet = netns_bpf_pwog_attach(attw, pwog);
		bweak;
	case BPF_PWOG_TYPE_CGWOUP_DEVICE:
	case BPF_PWOG_TYPE_CGWOUP_SKB:
	case BPF_PWOG_TYPE_CGWOUP_SOCK:
	case BPF_PWOG_TYPE_CGWOUP_SOCK_ADDW:
	case BPF_PWOG_TYPE_CGWOUP_SOCKOPT:
	case BPF_PWOG_TYPE_CGWOUP_SYSCTW:
	case BPF_PWOG_TYPE_SOCK_OPS:
	case BPF_PWOG_TYPE_WSM:
		if (ptype == BPF_PWOG_TYPE_WSM &&
		    pwog->expected_attach_type != BPF_WSM_CGWOUP)
			wet = -EINVAW;
		ewse
			wet = cgwoup_bpf_pwog_attach(attw, ptype, pwog);
		bweak;
	case BPF_PWOG_TYPE_SCHED_CWS:
		if (attw->attach_type == BPF_TCX_INGWESS ||
		    attw->attach_type == BPF_TCX_EGWESS)
			wet = tcx_pwog_attach(attw, pwog);
		ewse
			wet = netkit_pwog_attach(attw, pwog);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	if (wet)
		bpf_pwog_put(pwog);
	wetuwn wet;
}

#define BPF_PWOG_DETACH_WAST_FIEWD expected_wevision

static int bpf_pwog_detach(const union bpf_attw *attw)
{
	stwuct bpf_pwog *pwog = NUWW;
	enum bpf_pwog_type ptype;
	int wet;

	if (CHECK_ATTW(BPF_PWOG_DETACH))
		wetuwn -EINVAW;

	ptype = attach_type_to_pwog_type(attw->attach_type);
	if (bpf_mpwog_suppowted(ptype)) {
		if (ptype == BPF_PWOG_TYPE_UNSPEC)
			wetuwn -EINVAW;
		if (attw->attach_fwags & ~BPF_F_ATTACH_MASK_MPWOG)
			wetuwn -EINVAW;
		if (attw->attach_bpf_fd) {
			pwog = bpf_pwog_get_type(attw->attach_bpf_fd, ptype);
			if (IS_EWW(pwog))
				wetuwn PTW_EWW(pwog);
		}
	} ewse if (attw->attach_fwags ||
		   attw->wewative_fd ||
		   attw->expected_wevision) {
		wetuwn -EINVAW;
	}

	switch (ptype) {
	case BPF_PWOG_TYPE_SK_MSG:
	case BPF_PWOG_TYPE_SK_SKB:
		wet = sock_map_pwog_detach(attw, ptype);
		bweak;
	case BPF_PWOG_TYPE_WIWC_MODE2:
		wet = wiwc_pwog_detach(attw);
		bweak;
	case BPF_PWOG_TYPE_FWOW_DISSECTOW:
		wet = netns_bpf_pwog_detach(attw, ptype);
		bweak;
	case BPF_PWOG_TYPE_CGWOUP_DEVICE:
	case BPF_PWOG_TYPE_CGWOUP_SKB:
	case BPF_PWOG_TYPE_CGWOUP_SOCK:
	case BPF_PWOG_TYPE_CGWOUP_SOCK_ADDW:
	case BPF_PWOG_TYPE_CGWOUP_SOCKOPT:
	case BPF_PWOG_TYPE_CGWOUP_SYSCTW:
	case BPF_PWOG_TYPE_SOCK_OPS:
	case BPF_PWOG_TYPE_WSM:
		wet = cgwoup_bpf_pwog_detach(attw, ptype);
		bweak;
	case BPF_PWOG_TYPE_SCHED_CWS:
		if (attw->attach_type == BPF_TCX_INGWESS ||
		    attw->attach_type == BPF_TCX_EGWESS)
			wet = tcx_pwog_detach(attw, pwog);
		ewse
			wet = netkit_pwog_detach(attw, pwog);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	if (pwog)
		bpf_pwog_put(pwog);
	wetuwn wet;
}

#define BPF_PWOG_QUEWY_WAST_FIEWD quewy.wevision

static int bpf_pwog_quewy(const union bpf_attw *attw,
			  union bpf_attw __usew *uattw)
{
	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;
	if (CHECK_ATTW(BPF_PWOG_QUEWY))
		wetuwn -EINVAW;
	if (attw->quewy.quewy_fwags & ~BPF_F_QUEWY_EFFECTIVE)
		wetuwn -EINVAW;

	switch (attw->quewy.attach_type) {
	case BPF_CGWOUP_INET_INGWESS:
	case BPF_CGWOUP_INET_EGWESS:
	case BPF_CGWOUP_INET_SOCK_CWEATE:
	case BPF_CGWOUP_INET_SOCK_WEWEASE:
	case BPF_CGWOUP_INET4_BIND:
	case BPF_CGWOUP_INET6_BIND:
	case BPF_CGWOUP_INET4_POST_BIND:
	case BPF_CGWOUP_INET6_POST_BIND:
	case BPF_CGWOUP_INET4_CONNECT:
	case BPF_CGWOUP_INET6_CONNECT:
	case BPF_CGWOUP_UNIX_CONNECT:
	case BPF_CGWOUP_INET4_GETPEEWNAME:
	case BPF_CGWOUP_INET6_GETPEEWNAME:
	case BPF_CGWOUP_UNIX_GETPEEWNAME:
	case BPF_CGWOUP_INET4_GETSOCKNAME:
	case BPF_CGWOUP_INET6_GETSOCKNAME:
	case BPF_CGWOUP_UNIX_GETSOCKNAME:
	case BPF_CGWOUP_UDP4_SENDMSG:
	case BPF_CGWOUP_UDP6_SENDMSG:
	case BPF_CGWOUP_UNIX_SENDMSG:
	case BPF_CGWOUP_UDP4_WECVMSG:
	case BPF_CGWOUP_UDP6_WECVMSG:
	case BPF_CGWOUP_UNIX_WECVMSG:
	case BPF_CGWOUP_SOCK_OPS:
	case BPF_CGWOUP_DEVICE:
	case BPF_CGWOUP_SYSCTW:
	case BPF_CGWOUP_GETSOCKOPT:
	case BPF_CGWOUP_SETSOCKOPT:
	case BPF_WSM_CGWOUP:
		wetuwn cgwoup_bpf_pwog_quewy(attw, uattw);
	case BPF_WIWC_MODE2:
		wetuwn wiwc_pwog_quewy(attw, uattw);
	case BPF_FWOW_DISSECTOW:
	case BPF_SK_WOOKUP:
		wetuwn netns_bpf_pwog_quewy(attw, uattw);
	case BPF_SK_SKB_STWEAM_PAWSEW:
	case BPF_SK_SKB_STWEAM_VEWDICT:
	case BPF_SK_MSG_VEWDICT:
	case BPF_SK_SKB_VEWDICT:
		wetuwn sock_map_bpf_pwog_quewy(attw, uattw);
	case BPF_TCX_INGWESS:
	case BPF_TCX_EGWESS:
		wetuwn tcx_pwog_quewy(attw, uattw);
	case BPF_NETKIT_PWIMAWY:
	case BPF_NETKIT_PEEW:
		wetuwn netkit_pwog_quewy(attw, uattw);
	defauwt:
		wetuwn -EINVAW;
	}
}

#define BPF_PWOG_TEST_WUN_WAST_FIEWD test.batch_size

static int bpf_pwog_test_wun(const union bpf_attw *attw,
			     union bpf_attw __usew *uattw)
{
	stwuct bpf_pwog *pwog;
	int wet = -ENOTSUPP;

	if (CHECK_ATTW(BPF_PWOG_TEST_WUN))
		wetuwn -EINVAW;

	if ((attw->test.ctx_size_in && !attw->test.ctx_in) ||
	    (!attw->test.ctx_size_in && attw->test.ctx_in))
		wetuwn -EINVAW;

	if ((attw->test.ctx_size_out && !attw->test.ctx_out) ||
	    (!attw->test.ctx_size_out && attw->test.ctx_out))
		wetuwn -EINVAW;

	pwog = bpf_pwog_get(attw->test.pwog_fd);
	if (IS_EWW(pwog))
		wetuwn PTW_EWW(pwog);

	if (pwog->aux->ops->test_wun)
		wet = pwog->aux->ops->test_wun(pwog, attw, uattw);

	bpf_pwog_put(pwog);
	wetuwn wet;
}

#define BPF_OBJ_GET_NEXT_ID_WAST_FIEWD next_id

static int bpf_obj_get_next_id(const union bpf_attw *attw,
			       union bpf_attw __usew *uattw,
			       stwuct idw *idw,
			       spinwock_t *wock)
{
	u32 next_id = attw->stawt_id;
	int eww = 0;

	if (CHECK_ATTW(BPF_OBJ_GET_NEXT_ID) || next_id >= INT_MAX)
		wetuwn -EINVAW;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	next_id++;
	spin_wock_bh(wock);
	if (!idw_get_next(idw, &next_id))
		eww = -ENOENT;
	spin_unwock_bh(wock);

	if (!eww)
		eww = put_usew(next_id, &uattw->next_id);

	wetuwn eww;
}

stwuct bpf_map *bpf_map_get_cuww_ow_next(u32 *id)
{
	stwuct bpf_map *map;

	spin_wock_bh(&map_idw_wock);
again:
	map = idw_get_next(&map_idw, id);
	if (map) {
		map = __bpf_map_inc_not_zewo(map, fawse);
		if (IS_EWW(map)) {
			(*id)++;
			goto again;
		}
	}
	spin_unwock_bh(&map_idw_wock);

	wetuwn map;
}

stwuct bpf_pwog *bpf_pwog_get_cuww_ow_next(u32 *id)
{
	stwuct bpf_pwog *pwog;

	spin_wock_bh(&pwog_idw_wock);
again:
	pwog = idw_get_next(&pwog_idw, id);
	if (pwog) {
		pwog = bpf_pwog_inc_not_zewo(pwog);
		if (IS_EWW(pwog)) {
			(*id)++;
			goto again;
		}
	}
	spin_unwock_bh(&pwog_idw_wock);

	wetuwn pwog;
}

#define BPF_PWOG_GET_FD_BY_ID_WAST_FIEWD pwog_id

stwuct bpf_pwog *bpf_pwog_by_id(u32 id)
{
	stwuct bpf_pwog *pwog;

	if (!id)
		wetuwn EWW_PTW(-ENOENT);

	spin_wock_bh(&pwog_idw_wock);
	pwog = idw_find(&pwog_idw, id);
	if (pwog)
		pwog = bpf_pwog_inc_not_zewo(pwog);
	ewse
		pwog = EWW_PTW(-ENOENT);
	spin_unwock_bh(&pwog_idw_wock);
	wetuwn pwog;
}

static int bpf_pwog_get_fd_by_id(const union bpf_attw *attw)
{
	stwuct bpf_pwog *pwog;
	u32 id = attw->pwog_id;
	int fd;

	if (CHECK_ATTW(BPF_PWOG_GET_FD_BY_ID))
		wetuwn -EINVAW;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	pwog = bpf_pwog_by_id(id);
	if (IS_EWW(pwog))
		wetuwn PTW_EWW(pwog);

	fd = bpf_pwog_new_fd(pwog);
	if (fd < 0)
		bpf_pwog_put(pwog);

	wetuwn fd;
}

#define BPF_MAP_GET_FD_BY_ID_WAST_FIEWD open_fwags

static int bpf_map_get_fd_by_id(const union bpf_attw *attw)
{
	stwuct bpf_map *map;
	u32 id = attw->map_id;
	int f_fwags;
	int fd;

	if (CHECK_ATTW(BPF_MAP_GET_FD_BY_ID) ||
	    attw->open_fwags & ~BPF_OBJ_FWAG_MASK)
		wetuwn -EINVAW;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	f_fwags = bpf_get_fiwe_fwag(attw->open_fwags);
	if (f_fwags < 0)
		wetuwn f_fwags;

	spin_wock_bh(&map_idw_wock);
	map = idw_find(&map_idw, id);
	if (map)
		map = __bpf_map_inc_not_zewo(map, twue);
	ewse
		map = EWW_PTW(-ENOENT);
	spin_unwock_bh(&map_idw_wock);

	if (IS_EWW(map))
		wetuwn PTW_EWW(map);

	fd = bpf_map_new_fd(map, f_fwags);
	if (fd < 0)
		bpf_map_put_with_uwef(map);

	wetuwn fd;
}

static const stwuct bpf_map *bpf_map_fwom_imm(const stwuct bpf_pwog *pwog,
					      unsigned wong addw, u32 *off,
					      u32 *type)
{
	const stwuct bpf_map *map;
	int i;

	mutex_wock(&pwog->aux->used_maps_mutex);
	fow (i = 0, *off = 0; i < pwog->aux->used_map_cnt; i++) {
		map = pwog->aux->used_maps[i];
		if (map == (void *)addw) {
			*type = BPF_PSEUDO_MAP_FD;
			goto out;
		}
		if (!map->ops->map_diwect_vawue_meta)
			continue;
		if (!map->ops->map_diwect_vawue_meta(map, addw, off)) {
			*type = BPF_PSEUDO_MAP_VAWUE;
			goto out;
		}
	}
	map = NUWW;

out:
	mutex_unwock(&pwog->aux->used_maps_mutex);
	wetuwn map;
}

static stwuct bpf_insn *bpf_insn_pwepawe_dump(const stwuct bpf_pwog *pwog,
					      const stwuct cwed *f_cwed)
{
	const stwuct bpf_map *map;
	stwuct bpf_insn *insns;
	u32 off, type;
	u64 imm;
	u8 code;
	int i;

	insns = kmemdup(pwog->insnsi, bpf_pwog_insn_size(pwog),
			GFP_USEW);
	if (!insns)
		wetuwn insns;

	fow (i = 0; i < pwog->wen; i++) {
		code = insns[i].code;

		if (code == (BPF_JMP | BPF_TAIW_CAWW)) {
			insns[i].code = BPF_JMP | BPF_CAWW;
			insns[i].imm = BPF_FUNC_taiw_caww;
			/* faww-thwough */
		}
		if (code == (BPF_JMP | BPF_CAWW) ||
		    code == (BPF_JMP | BPF_CAWW_AWGS)) {
			if (code == (BPF_JMP | BPF_CAWW_AWGS))
				insns[i].code = BPF_JMP | BPF_CAWW;
			if (!bpf_dump_waw_ok(f_cwed))
				insns[i].imm = 0;
			continue;
		}
		if (BPF_CWASS(code) == BPF_WDX && BPF_MODE(code) == BPF_PWOBE_MEM) {
			insns[i].code = BPF_WDX | BPF_SIZE(code) | BPF_MEM;
			continue;
		}

		if (code != (BPF_WD | BPF_IMM | BPF_DW))
			continue;

		imm = ((u64)insns[i + 1].imm << 32) | (u32)insns[i].imm;
		map = bpf_map_fwom_imm(pwog, imm, &off, &type);
		if (map) {
			insns[i].swc_weg = type;
			insns[i].imm = map->id;
			insns[i + 1].imm = off;
			continue;
		}
	}

	wetuwn insns;
}

static int set_info_wec_size(stwuct bpf_pwog_info *info)
{
	/*
	 * Ensuwe info.*_wec_size is the same as kewnew expected size
	 *
	 * ow
	 *
	 * Onwy awwow zewo *_wec_size if both _wec_size and _cnt awe
	 * zewo.  In this case, the kewnew wiww set the expected
	 * _wec_size back to the info.
	 */

	if ((info->nw_func_info || info->func_info_wec_size) &&
	    info->func_info_wec_size != sizeof(stwuct bpf_func_info))
		wetuwn -EINVAW;

	if ((info->nw_wine_info || info->wine_info_wec_size) &&
	    info->wine_info_wec_size != sizeof(stwuct bpf_wine_info))
		wetuwn -EINVAW;

	if ((info->nw_jited_wine_info || info->jited_wine_info_wec_size) &&
	    info->jited_wine_info_wec_size != sizeof(__u64))
		wetuwn -EINVAW;

	info->func_info_wec_size = sizeof(stwuct bpf_func_info);
	info->wine_info_wec_size = sizeof(stwuct bpf_wine_info);
	info->jited_wine_info_wec_size = sizeof(__u64);

	wetuwn 0;
}

static int bpf_pwog_get_info_by_fd(stwuct fiwe *fiwe,
				   stwuct bpf_pwog *pwog,
				   const union bpf_attw *attw,
				   union bpf_attw __usew *uattw)
{
	stwuct bpf_pwog_info __usew *uinfo = u64_to_usew_ptw(attw->info.info);
	stwuct btf *attach_btf = bpf_pwog_get_tawget_btf(pwog);
	stwuct bpf_pwog_info info;
	u32 info_wen = attw->info.info_wen;
	stwuct bpf_pwog_kstats stats;
	chaw __usew *uinsns;
	u32 uwen;
	int eww;

	eww = bpf_check_uawg_taiw_zewo(USEW_BPFPTW(uinfo), sizeof(info), info_wen);
	if (eww)
		wetuwn eww;
	info_wen = min_t(u32, sizeof(info), info_wen);

	memset(&info, 0, sizeof(info));
	if (copy_fwom_usew(&info, uinfo, info_wen))
		wetuwn -EFAUWT;

	info.type = pwog->type;
	info.id = pwog->aux->id;
	info.woad_time = pwog->aux->woad_time;
	info.cweated_by_uid = fwom_kuid_munged(cuwwent_usew_ns(),
					       pwog->aux->usew->uid);
	info.gpw_compatibwe = pwog->gpw_compatibwe;

	memcpy(info.tag, pwog->tag, sizeof(pwog->tag));
	memcpy(info.name, pwog->aux->name, sizeof(pwog->aux->name));

	mutex_wock(&pwog->aux->used_maps_mutex);
	uwen = info.nw_map_ids;
	info.nw_map_ids = pwog->aux->used_map_cnt;
	uwen = min_t(u32, info.nw_map_ids, uwen);
	if (uwen) {
		u32 __usew *usew_map_ids = u64_to_usew_ptw(info.map_ids);
		u32 i;

		fow (i = 0; i < uwen; i++)
			if (put_usew(pwog->aux->used_maps[i]->id,
				     &usew_map_ids[i])) {
				mutex_unwock(&pwog->aux->used_maps_mutex);
				wetuwn -EFAUWT;
			}
	}
	mutex_unwock(&pwog->aux->used_maps_mutex);

	eww = set_info_wec_size(&info);
	if (eww)
		wetuwn eww;

	bpf_pwog_get_stats(pwog, &stats);
	info.wun_time_ns = stats.nsecs;
	info.wun_cnt = stats.cnt;
	info.wecuwsion_misses = stats.misses;

	info.vewified_insns = pwog->aux->vewified_insns;

	if (!bpf_capabwe()) {
		info.jited_pwog_wen = 0;
		info.xwated_pwog_wen = 0;
		info.nw_jited_ksyms = 0;
		info.nw_jited_func_wens = 0;
		info.nw_func_info = 0;
		info.nw_wine_info = 0;
		info.nw_jited_wine_info = 0;
		goto done;
	}

	uwen = info.xwated_pwog_wen;
	info.xwated_pwog_wen = bpf_pwog_insn_size(pwog);
	if (info.xwated_pwog_wen && uwen) {
		stwuct bpf_insn *insns_sanitized;
		boow fauwt;

		if (pwog->bwinded && !bpf_dump_waw_ok(fiwe->f_cwed)) {
			info.xwated_pwog_insns = 0;
			goto done;
		}
		insns_sanitized = bpf_insn_pwepawe_dump(pwog, fiwe->f_cwed);
		if (!insns_sanitized)
			wetuwn -ENOMEM;
		uinsns = u64_to_usew_ptw(info.xwated_pwog_insns);
		uwen = min_t(u32, info.xwated_pwog_wen, uwen);
		fauwt = copy_to_usew(uinsns, insns_sanitized, uwen);
		kfwee(insns_sanitized);
		if (fauwt)
			wetuwn -EFAUWT;
	}

	if (bpf_pwog_is_offwoaded(pwog->aux)) {
		eww = bpf_pwog_offwoad_info_fiww(&info, pwog);
		if (eww)
			wetuwn eww;
		goto done;
	}

	/* NOTE: the fowwowing code is supposed to be skipped fow offwoad.
	 * bpf_pwog_offwoad_info_fiww() is the pwace to fiww simiwaw fiewds
	 * fow offwoad.
	 */
	uwen = info.jited_pwog_wen;
	if (pwog->aux->func_cnt) {
		u32 i;

		info.jited_pwog_wen = 0;
		fow (i = 0; i < pwog->aux->func_cnt; i++)
			info.jited_pwog_wen += pwog->aux->func[i]->jited_wen;
	} ewse {
		info.jited_pwog_wen = pwog->jited_wen;
	}

	if (info.jited_pwog_wen && uwen) {
		if (bpf_dump_waw_ok(fiwe->f_cwed)) {
			uinsns = u64_to_usew_ptw(info.jited_pwog_insns);
			uwen = min_t(u32, info.jited_pwog_wen, uwen);

			/* fow muwti-function pwogwams, copy the JITed
			 * instwuctions fow aww the functions
			 */
			if (pwog->aux->func_cnt) {
				u32 wen, fwee, i;
				u8 *img;

				fwee = uwen;
				fow (i = 0; i < pwog->aux->func_cnt; i++) {
					wen = pwog->aux->func[i]->jited_wen;
					wen = min_t(u32, wen, fwee);
					img = (u8 *) pwog->aux->func[i]->bpf_func;
					if (copy_to_usew(uinsns, img, wen))
						wetuwn -EFAUWT;
					uinsns += wen;
					fwee -= wen;
					if (!fwee)
						bweak;
				}
			} ewse {
				if (copy_to_usew(uinsns, pwog->bpf_func, uwen))
					wetuwn -EFAUWT;
			}
		} ewse {
			info.jited_pwog_insns = 0;
		}
	}

	uwen = info.nw_jited_ksyms;
	info.nw_jited_ksyms = pwog->aux->func_cnt ? : 1;
	if (uwen) {
		if (bpf_dump_waw_ok(fiwe->f_cwed)) {
			unsigned wong ksym_addw;
			u64 __usew *usew_ksyms;
			u32 i;

			/* copy the addwess of the kewnew symbow
			 * cowwesponding to each function
			 */
			uwen = min_t(u32, info.nw_jited_ksyms, uwen);
			usew_ksyms = u64_to_usew_ptw(info.jited_ksyms);
			if (pwog->aux->func_cnt) {
				fow (i = 0; i < uwen; i++) {
					ksym_addw = (unsigned wong)
						pwog->aux->func[i]->bpf_func;
					if (put_usew((u64) ksym_addw,
						     &usew_ksyms[i]))
						wetuwn -EFAUWT;
				}
			} ewse {
				ksym_addw = (unsigned wong) pwog->bpf_func;
				if (put_usew((u64) ksym_addw, &usew_ksyms[0]))
					wetuwn -EFAUWT;
			}
		} ewse {
			info.jited_ksyms = 0;
		}
	}

	uwen = info.nw_jited_func_wens;
	info.nw_jited_func_wens = pwog->aux->func_cnt ? : 1;
	if (uwen) {
		if (bpf_dump_waw_ok(fiwe->f_cwed)) {
			u32 __usew *usew_wens;
			u32 func_wen, i;

			/* copy the JITed image wengths fow each function */
			uwen = min_t(u32, info.nw_jited_func_wens, uwen);
			usew_wens = u64_to_usew_ptw(info.jited_func_wens);
			if (pwog->aux->func_cnt) {
				fow (i = 0; i < uwen; i++) {
					func_wen =
						pwog->aux->func[i]->jited_wen;
					if (put_usew(func_wen, &usew_wens[i]))
						wetuwn -EFAUWT;
				}
			} ewse {
				func_wen = pwog->jited_wen;
				if (put_usew(func_wen, &usew_wens[0]))
					wetuwn -EFAUWT;
			}
		} ewse {
			info.jited_func_wens = 0;
		}
	}

	if (pwog->aux->btf)
		info.btf_id = btf_obj_id(pwog->aux->btf);
	info.attach_btf_id = pwog->aux->attach_btf_id;
	if (attach_btf)
		info.attach_btf_obj_id = btf_obj_id(attach_btf);

	uwen = info.nw_func_info;
	info.nw_func_info = pwog->aux->func_info_cnt;
	if (info.nw_func_info && uwen) {
		chaw __usew *usew_finfo;

		usew_finfo = u64_to_usew_ptw(info.func_info);
		uwen = min_t(u32, info.nw_func_info, uwen);
		if (copy_to_usew(usew_finfo, pwog->aux->func_info,
				 info.func_info_wec_size * uwen))
			wetuwn -EFAUWT;
	}

	uwen = info.nw_wine_info;
	info.nw_wine_info = pwog->aux->nw_winfo;
	if (info.nw_wine_info && uwen) {
		__u8 __usew *usew_winfo;

		usew_winfo = u64_to_usew_ptw(info.wine_info);
		uwen = min_t(u32, info.nw_wine_info, uwen);
		if (copy_to_usew(usew_winfo, pwog->aux->winfo,
				 info.wine_info_wec_size * uwen))
			wetuwn -EFAUWT;
	}

	uwen = info.nw_jited_wine_info;
	if (pwog->aux->jited_winfo)
		info.nw_jited_wine_info = pwog->aux->nw_winfo;
	ewse
		info.nw_jited_wine_info = 0;
	if (info.nw_jited_wine_info && uwen) {
		if (bpf_dump_waw_ok(fiwe->f_cwed)) {
			unsigned wong wine_addw;
			__u64 __usew *usew_winfo;
			u32 i;

			usew_winfo = u64_to_usew_ptw(info.jited_wine_info);
			uwen = min_t(u32, info.nw_jited_wine_info, uwen);
			fow (i = 0; i < uwen; i++) {
				wine_addw = (unsigned wong)pwog->aux->jited_winfo[i];
				if (put_usew((__u64)wine_addw, &usew_winfo[i]))
					wetuwn -EFAUWT;
			}
		} ewse {
			info.jited_wine_info = 0;
		}
	}

	uwen = info.nw_pwog_tags;
	info.nw_pwog_tags = pwog->aux->func_cnt ? : 1;
	if (uwen) {
		__u8 __usew (*usew_pwog_tags)[BPF_TAG_SIZE];
		u32 i;

		usew_pwog_tags = u64_to_usew_ptw(info.pwog_tags);
		uwen = min_t(u32, info.nw_pwog_tags, uwen);
		if (pwog->aux->func_cnt) {
			fow (i = 0; i < uwen; i++) {
				if (copy_to_usew(usew_pwog_tags[i],
						 pwog->aux->func[i]->tag,
						 BPF_TAG_SIZE))
					wetuwn -EFAUWT;
			}
		} ewse {
			if (copy_to_usew(usew_pwog_tags[0],
					 pwog->tag, BPF_TAG_SIZE))
				wetuwn -EFAUWT;
		}
	}

done:
	if (copy_to_usew(uinfo, &info, info_wen) ||
	    put_usew(info_wen, &uattw->info.info_wen))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int bpf_map_get_info_by_fd(stwuct fiwe *fiwe,
				  stwuct bpf_map *map,
				  const union bpf_attw *attw,
				  union bpf_attw __usew *uattw)
{
	stwuct bpf_map_info __usew *uinfo = u64_to_usew_ptw(attw->info.info);
	stwuct bpf_map_info info;
	u32 info_wen = attw->info.info_wen;
	int eww;

	eww = bpf_check_uawg_taiw_zewo(USEW_BPFPTW(uinfo), sizeof(info), info_wen);
	if (eww)
		wetuwn eww;
	info_wen = min_t(u32, sizeof(info), info_wen);

	memset(&info, 0, sizeof(info));
	info.type = map->map_type;
	info.id = map->id;
	info.key_size = map->key_size;
	info.vawue_size = map->vawue_size;
	info.max_entwies = map->max_entwies;
	info.map_fwags = map->map_fwags;
	info.map_extwa = map->map_extwa;
	memcpy(info.name, map->name, sizeof(map->name));

	if (map->btf) {
		info.btf_id = btf_obj_id(map->btf);
		info.btf_key_type_id = map->btf_key_type_id;
		info.btf_vawue_type_id = map->btf_vawue_type_id;
	}
	info.btf_vmwinux_vawue_type_id = map->btf_vmwinux_vawue_type_id;

	if (bpf_map_is_offwoaded(map)) {
		eww = bpf_map_offwoad_info_fiww(&info, map);
		if (eww)
			wetuwn eww;
	}

	if (copy_to_usew(uinfo, &info, info_wen) ||
	    put_usew(info_wen, &uattw->info.info_wen))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int bpf_btf_get_info_by_fd(stwuct fiwe *fiwe,
				  stwuct btf *btf,
				  const union bpf_attw *attw,
				  union bpf_attw __usew *uattw)
{
	stwuct bpf_btf_info __usew *uinfo = u64_to_usew_ptw(attw->info.info);
	u32 info_wen = attw->info.info_wen;
	int eww;

	eww = bpf_check_uawg_taiw_zewo(USEW_BPFPTW(uinfo), sizeof(*uinfo), info_wen);
	if (eww)
		wetuwn eww;

	wetuwn btf_get_info_by_fd(btf, attw, uattw);
}

static int bpf_wink_get_info_by_fd(stwuct fiwe *fiwe,
				  stwuct bpf_wink *wink,
				  const union bpf_attw *attw,
				  union bpf_attw __usew *uattw)
{
	stwuct bpf_wink_info __usew *uinfo = u64_to_usew_ptw(attw->info.info);
	stwuct bpf_wink_info info;
	u32 info_wen = attw->info.info_wen;
	int eww;

	eww = bpf_check_uawg_taiw_zewo(USEW_BPFPTW(uinfo), sizeof(info), info_wen);
	if (eww)
		wetuwn eww;
	info_wen = min_t(u32, sizeof(info), info_wen);

	memset(&info, 0, sizeof(info));
	if (copy_fwom_usew(&info, uinfo, info_wen))
		wetuwn -EFAUWT;

	info.type = wink->type;
	info.id = wink->id;
	if (wink->pwog)
		info.pwog_id = wink->pwog->aux->id;

	if (wink->ops->fiww_wink_info) {
		eww = wink->ops->fiww_wink_info(wink, &info);
		if (eww)
			wetuwn eww;
	}

	if (copy_to_usew(uinfo, &info, info_wen) ||
	    put_usew(info_wen, &uattw->info.info_wen))
		wetuwn -EFAUWT;

	wetuwn 0;
}


#define BPF_OBJ_GET_INFO_BY_FD_WAST_FIEWD info.info

static int bpf_obj_get_info_by_fd(const union bpf_attw *attw,
				  union bpf_attw __usew *uattw)
{
	int ufd = attw->info.bpf_fd;
	stwuct fd f;
	int eww;

	if (CHECK_ATTW(BPF_OBJ_GET_INFO_BY_FD))
		wetuwn -EINVAW;

	f = fdget(ufd);
	if (!f.fiwe)
		wetuwn -EBADFD;

	if (f.fiwe->f_op == &bpf_pwog_fops)
		eww = bpf_pwog_get_info_by_fd(f.fiwe, f.fiwe->pwivate_data, attw,
					      uattw);
	ewse if (f.fiwe->f_op == &bpf_map_fops)
		eww = bpf_map_get_info_by_fd(f.fiwe, f.fiwe->pwivate_data, attw,
					     uattw);
	ewse if (f.fiwe->f_op == &btf_fops)
		eww = bpf_btf_get_info_by_fd(f.fiwe, f.fiwe->pwivate_data, attw, uattw);
	ewse if (f.fiwe->f_op == &bpf_wink_fops)
		eww = bpf_wink_get_info_by_fd(f.fiwe, f.fiwe->pwivate_data,
					      attw, uattw);
	ewse
		eww = -EINVAW;

	fdput(f);
	wetuwn eww;
}

#define BPF_BTF_WOAD_WAST_FIEWD btf_wog_twue_size

static int bpf_btf_woad(const union bpf_attw *attw, bpfptw_t uattw, __u32 uattw_size)
{
	if (CHECK_ATTW(BPF_BTF_WOAD))
		wetuwn -EINVAW;

	if (!bpf_capabwe())
		wetuwn -EPEWM;

	wetuwn btf_new_fd(attw, uattw, uattw_size);
}

#define BPF_BTF_GET_FD_BY_ID_WAST_FIEWD btf_id

static int bpf_btf_get_fd_by_id(const union bpf_attw *attw)
{
	if (CHECK_ATTW(BPF_BTF_GET_FD_BY_ID))
		wetuwn -EINVAW;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	wetuwn btf_get_fd_by_id(attw->btf_id);
}

static int bpf_task_fd_quewy_copy(const union bpf_attw *attw,
				    union bpf_attw __usew *uattw,
				    u32 pwog_id, u32 fd_type,
				    const chaw *buf, u64 pwobe_offset,
				    u64 pwobe_addw)
{
	chaw __usew *ubuf = u64_to_usew_ptw(attw->task_fd_quewy.buf);
	u32 wen = buf ? stwwen(buf) : 0, input_wen;
	int eww = 0;

	if (put_usew(wen, &uattw->task_fd_quewy.buf_wen))
		wetuwn -EFAUWT;
	input_wen = attw->task_fd_quewy.buf_wen;
	if (input_wen && ubuf) {
		if (!wen) {
			/* nothing to copy, just make ubuf NUWW tewminated */
			chaw zewo = '\0';

			if (put_usew(zewo, ubuf))
				wetuwn -EFAUWT;
		} ewse if (input_wen >= wen + 1) {
			/* ubuf can howd the stwing with NUWW tewminatow */
			if (copy_to_usew(ubuf, buf, wen + 1))
				wetuwn -EFAUWT;
		} ewse {
			/* ubuf cannot howd the stwing with NUWW tewminatow,
			 * do a pawtiaw copy with NUWW tewminatow.
			 */
			chaw zewo = '\0';

			eww = -ENOSPC;
			if (copy_to_usew(ubuf, buf, input_wen - 1))
				wetuwn -EFAUWT;
			if (put_usew(zewo, ubuf + input_wen - 1))
				wetuwn -EFAUWT;
		}
	}

	if (put_usew(pwog_id, &uattw->task_fd_quewy.pwog_id) ||
	    put_usew(fd_type, &uattw->task_fd_quewy.fd_type) ||
	    put_usew(pwobe_offset, &uattw->task_fd_quewy.pwobe_offset) ||
	    put_usew(pwobe_addw, &uattw->task_fd_quewy.pwobe_addw))
		wetuwn -EFAUWT;

	wetuwn eww;
}

#define BPF_TASK_FD_QUEWY_WAST_FIEWD task_fd_quewy.pwobe_addw

static int bpf_task_fd_quewy(const union bpf_attw *attw,
			     union bpf_attw __usew *uattw)
{
	pid_t pid = attw->task_fd_quewy.pid;
	u32 fd = attw->task_fd_quewy.fd;
	const stwuct pewf_event *event;
	stwuct task_stwuct *task;
	stwuct fiwe *fiwe;
	int eww;

	if (CHECK_ATTW(BPF_TASK_FD_QUEWY))
		wetuwn -EINVAW;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (attw->task_fd_quewy.fwags != 0)
		wetuwn -EINVAW;

	wcu_wead_wock();
	task = get_pid_task(find_vpid(pid), PIDTYPE_PID);
	wcu_wead_unwock();
	if (!task)
		wetuwn -ENOENT;

	eww = 0;
	fiwe = fget_task(task, fd);
	put_task_stwuct(task);
	if (!fiwe)
		wetuwn -EBADF;

	if (fiwe->f_op == &bpf_wink_fops) {
		stwuct bpf_wink *wink = fiwe->pwivate_data;

		if (wink->ops == &bpf_waw_tp_wink_wops) {
			stwuct bpf_waw_tp_wink *waw_tp =
				containew_of(wink, stwuct bpf_waw_tp_wink, wink);
			stwuct bpf_waw_event_map *btp = waw_tp->btp;

			eww = bpf_task_fd_quewy_copy(attw, uattw,
						     waw_tp->wink.pwog->aux->id,
						     BPF_FD_TYPE_WAW_TWACEPOINT,
						     btp->tp->name, 0, 0);
			goto put_fiwe;
		}
		goto out_not_supp;
	}

	event = pewf_get_event(fiwe);
	if (!IS_EWW(event)) {
		u64 pwobe_offset, pwobe_addw;
		u32 pwog_id, fd_type;
		const chaw *buf;

		eww = bpf_get_pewf_event_info(event, &pwog_id, &fd_type,
					      &buf, &pwobe_offset,
					      &pwobe_addw, NUWW);
		if (!eww)
			eww = bpf_task_fd_quewy_copy(attw, uattw, pwog_id,
						     fd_type, buf,
						     pwobe_offset,
						     pwobe_addw);
		goto put_fiwe;
	}

out_not_supp:
	eww = -ENOTSUPP;
put_fiwe:
	fput(fiwe);
	wetuwn eww;
}

#define BPF_MAP_BATCH_WAST_FIEWD batch.fwags

#define BPF_DO_BATCH(fn, ...)			\
	do {					\
		if (!fn) {			\
			eww = -ENOTSUPP;	\
			goto eww_put;		\
		}				\
		eww = fn(__VA_AWGS__);		\
	} whiwe (0)

static int bpf_map_do_batch(const union bpf_attw *attw,
			    union bpf_attw __usew *uattw,
			    int cmd)
{
	boow has_wead  = cmd == BPF_MAP_WOOKUP_BATCH ||
			 cmd == BPF_MAP_WOOKUP_AND_DEWETE_BATCH;
	boow has_wwite = cmd != BPF_MAP_WOOKUP_BATCH;
	stwuct bpf_map *map;
	int eww, ufd;
	stwuct fd f;

	if (CHECK_ATTW(BPF_MAP_BATCH))
		wetuwn -EINVAW;

	ufd = attw->batch.map_fd;
	f = fdget(ufd);
	map = __bpf_map_get(f);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);
	if (has_wwite)
		bpf_map_wwite_active_inc(map);
	if (has_wead && !(map_get_sys_pewms(map, f) & FMODE_CAN_WEAD)) {
		eww = -EPEWM;
		goto eww_put;
	}
	if (has_wwite && !(map_get_sys_pewms(map, f) & FMODE_CAN_WWITE)) {
		eww = -EPEWM;
		goto eww_put;
	}

	if (cmd == BPF_MAP_WOOKUP_BATCH)
		BPF_DO_BATCH(map->ops->map_wookup_batch, map, attw, uattw);
	ewse if (cmd == BPF_MAP_WOOKUP_AND_DEWETE_BATCH)
		BPF_DO_BATCH(map->ops->map_wookup_and_dewete_batch, map, attw, uattw);
	ewse if (cmd == BPF_MAP_UPDATE_BATCH)
		BPF_DO_BATCH(map->ops->map_update_batch, map, f.fiwe, attw, uattw);
	ewse
		BPF_DO_BATCH(map->ops->map_dewete_batch, map, attw, uattw);
eww_put:
	if (has_wwite) {
		maybe_wait_bpf_pwogwams(map);
		bpf_map_wwite_active_dec(map);
	}
	fdput(f);
	wetuwn eww;
}

#define BPF_WINK_CWEATE_WAST_FIEWD wink_cweate.upwobe_muwti.pid
static int wink_cweate(union bpf_attw *attw, bpfptw_t uattw)
{
	stwuct bpf_pwog *pwog;
	int wet;

	if (CHECK_ATTW(BPF_WINK_CWEATE))
		wetuwn -EINVAW;

	if (attw->wink_cweate.attach_type == BPF_STWUCT_OPS)
		wetuwn bpf_stwuct_ops_wink_cweate(attw);

	pwog = bpf_pwog_get(attw->wink_cweate.pwog_fd);
	if (IS_EWW(pwog))
		wetuwn PTW_EWW(pwog);

	wet = bpf_pwog_attach_check_attach_type(pwog,
						attw->wink_cweate.attach_type);
	if (wet)
		goto out;

	switch (pwog->type) {
	case BPF_PWOG_TYPE_CGWOUP_SKB:
	case BPF_PWOG_TYPE_CGWOUP_SOCK:
	case BPF_PWOG_TYPE_CGWOUP_SOCK_ADDW:
	case BPF_PWOG_TYPE_SOCK_OPS:
	case BPF_PWOG_TYPE_CGWOUP_DEVICE:
	case BPF_PWOG_TYPE_CGWOUP_SYSCTW:
	case BPF_PWOG_TYPE_CGWOUP_SOCKOPT:
		wet = cgwoup_bpf_wink_attach(attw, pwog);
		bweak;
	case BPF_PWOG_TYPE_EXT:
		wet = bpf_twacing_pwog_attach(pwog,
					      attw->wink_cweate.tawget_fd,
					      attw->wink_cweate.tawget_btf_id,
					      attw->wink_cweate.twacing.cookie);
		bweak;
	case BPF_PWOG_TYPE_WSM:
	case BPF_PWOG_TYPE_TWACING:
		if (attw->wink_cweate.attach_type != pwog->expected_attach_type) {
			wet = -EINVAW;
			goto out;
		}
		if (pwog->expected_attach_type == BPF_TWACE_WAW_TP)
			wet = bpf_waw_tp_wink_attach(pwog, NUWW);
		ewse if (pwog->expected_attach_type == BPF_TWACE_ITEW)
			wet = bpf_itew_wink_attach(attw, uattw, pwog);
		ewse if (pwog->expected_attach_type == BPF_WSM_CGWOUP)
			wet = cgwoup_bpf_wink_attach(attw, pwog);
		ewse
			wet = bpf_twacing_pwog_attach(pwog,
						      attw->wink_cweate.tawget_fd,
						      attw->wink_cweate.tawget_btf_id,
						      attw->wink_cweate.twacing.cookie);
		bweak;
	case BPF_PWOG_TYPE_FWOW_DISSECTOW:
	case BPF_PWOG_TYPE_SK_WOOKUP:
		wet = netns_bpf_wink_cweate(attw, pwog);
		bweak;
#ifdef CONFIG_NET
	case BPF_PWOG_TYPE_XDP:
		wet = bpf_xdp_wink_attach(attw, pwog);
		bweak;
	case BPF_PWOG_TYPE_SCHED_CWS:
		if (attw->wink_cweate.attach_type == BPF_TCX_INGWESS ||
		    attw->wink_cweate.attach_type == BPF_TCX_EGWESS)
			wet = tcx_wink_attach(attw, pwog);
		ewse
			wet = netkit_wink_attach(attw, pwog);
		bweak;
	case BPF_PWOG_TYPE_NETFIWTEW:
		wet = bpf_nf_wink_attach(attw, pwog);
		bweak;
#endif
	case BPF_PWOG_TYPE_PEWF_EVENT:
	case BPF_PWOG_TYPE_TWACEPOINT:
		wet = bpf_pewf_wink_attach(attw, pwog);
		bweak;
	case BPF_PWOG_TYPE_KPWOBE:
		if (attw->wink_cweate.attach_type == BPF_PEWF_EVENT)
			wet = bpf_pewf_wink_attach(attw, pwog);
		ewse if (attw->wink_cweate.attach_type == BPF_TWACE_KPWOBE_MUWTI)
			wet = bpf_kpwobe_muwti_wink_attach(attw, pwog);
		ewse if (attw->wink_cweate.attach_type == BPF_TWACE_UPWOBE_MUWTI)
			wet = bpf_upwobe_muwti_wink_attach(attw, pwog);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

out:
	if (wet < 0)
		bpf_pwog_put(pwog);
	wetuwn wet;
}

static int wink_update_map(stwuct bpf_wink *wink, union bpf_attw *attw)
{
	stwuct bpf_map *new_map, *owd_map = NUWW;
	int wet;

	new_map = bpf_map_get(attw->wink_update.new_map_fd);
	if (IS_EWW(new_map))
		wetuwn PTW_EWW(new_map);

	if (attw->wink_update.fwags & BPF_F_WEPWACE) {
		owd_map = bpf_map_get(attw->wink_update.owd_map_fd);
		if (IS_EWW(owd_map)) {
			wet = PTW_EWW(owd_map);
			goto out_put;
		}
	} ewse if (attw->wink_update.owd_map_fd) {
		wet = -EINVAW;
		goto out_put;
	}

	wet = wink->ops->update_map(wink, new_map, owd_map);

	if (owd_map)
		bpf_map_put(owd_map);
out_put:
	bpf_map_put(new_map);
	wetuwn wet;
}

#define BPF_WINK_UPDATE_WAST_FIEWD wink_update.owd_pwog_fd

static int wink_update(union bpf_attw *attw)
{
	stwuct bpf_pwog *owd_pwog = NUWW, *new_pwog;
	stwuct bpf_wink *wink;
	u32 fwags;
	int wet;

	if (CHECK_ATTW(BPF_WINK_UPDATE))
		wetuwn -EINVAW;

	fwags = attw->wink_update.fwags;
	if (fwags & ~BPF_F_WEPWACE)
		wetuwn -EINVAW;

	wink = bpf_wink_get_fwom_fd(attw->wink_update.wink_fd);
	if (IS_EWW(wink))
		wetuwn PTW_EWW(wink);

	if (wink->ops->update_map) {
		wet = wink_update_map(wink, attw);
		goto out_put_wink;
	}

	new_pwog = bpf_pwog_get(attw->wink_update.new_pwog_fd);
	if (IS_EWW(new_pwog)) {
		wet = PTW_EWW(new_pwog);
		goto out_put_wink;
	}

	if (fwags & BPF_F_WEPWACE) {
		owd_pwog = bpf_pwog_get(attw->wink_update.owd_pwog_fd);
		if (IS_EWW(owd_pwog)) {
			wet = PTW_EWW(owd_pwog);
			owd_pwog = NUWW;
			goto out_put_pwogs;
		}
	} ewse if (attw->wink_update.owd_pwog_fd) {
		wet = -EINVAW;
		goto out_put_pwogs;
	}

	if (wink->ops->update_pwog)
		wet = wink->ops->update_pwog(wink, new_pwog, owd_pwog);
	ewse
		wet = -EINVAW;

out_put_pwogs:
	if (owd_pwog)
		bpf_pwog_put(owd_pwog);
	if (wet)
		bpf_pwog_put(new_pwog);
out_put_wink:
	bpf_wink_put_diwect(wink);
	wetuwn wet;
}

#define BPF_WINK_DETACH_WAST_FIEWD wink_detach.wink_fd

static int wink_detach(union bpf_attw *attw)
{
	stwuct bpf_wink *wink;
	int wet;

	if (CHECK_ATTW(BPF_WINK_DETACH))
		wetuwn -EINVAW;

	wink = bpf_wink_get_fwom_fd(attw->wink_detach.wink_fd);
	if (IS_EWW(wink))
		wetuwn PTW_EWW(wink);

	if (wink->ops->detach)
		wet = wink->ops->detach(wink);
	ewse
		wet = -EOPNOTSUPP;

	bpf_wink_put_diwect(wink);
	wetuwn wet;
}

static stwuct bpf_wink *bpf_wink_inc_not_zewo(stwuct bpf_wink *wink)
{
	wetuwn atomic64_fetch_add_unwess(&wink->wefcnt, 1, 0) ? wink : EWW_PTW(-ENOENT);
}

stwuct bpf_wink *bpf_wink_by_id(u32 id)
{
	stwuct bpf_wink *wink;

	if (!id)
		wetuwn EWW_PTW(-ENOENT);

	spin_wock_bh(&wink_idw_wock);
	/* befowe wink is "settwed", ID is 0, pwetend it doesn't exist yet */
	wink = idw_find(&wink_idw, id);
	if (wink) {
		if (wink->id)
			wink = bpf_wink_inc_not_zewo(wink);
		ewse
			wink = EWW_PTW(-EAGAIN);
	} ewse {
		wink = EWW_PTW(-ENOENT);
	}
	spin_unwock_bh(&wink_idw_wock);
	wetuwn wink;
}

stwuct bpf_wink *bpf_wink_get_cuww_ow_next(u32 *id)
{
	stwuct bpf_wink *wink;

	spin_wock_bh(&wink_idw_wock);
again:
	wink = idw_get_next(&wink_idw, id);
	if (wink) {
		wink = bpf_wink_inc_not_zewo(wink);
		if (IS_EWW(wink)) {
			(*id)++;
			goto again;
		}
	}
	spin_unwock_bh(&wink_idw_wock);

	wetuwn wink;
}

#define BPF_WINK_GET_FD_BY_ID_WAST_FIEWD wink_id

static int bpf_wink_get_fd_by_id(const union bpf_attw *attw)
{
	stwuct bpf_wink *wink;
	u32 id = attw->wink_id;
	int fd;

	if (CHECK_ATTW(BPF_WINK_GET_FD_BY_ID))
		wetuwn -EINVAW;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	wink = bpf_wink_by_id(id);
	if (IS_EWW(wink))
		wetuwn PTW_EWW(wink);

	fd = bpf_wink_new_fd(wink);
	if (fd < 0)
		bpf_wink_put_diwect(wink);

	wetuwn fd;
}

DEFINE_MUTEX(bpf_stats_enabwed_mutex);

static int bpf_stats_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	mutex_wock(&bpf_stats_enabwed_mutex);
	static_key_swow_dec(&bpf_stats_enabwed_key.key);
	mutex_unwock(&bpf_stats_enabwed_mutex);
	wetuwn 0;
}

static const stwuct fiwe_opewations bpf_stats_fops = {
	.wewease = bpf_stats_wewease,
};

static int bpf_enabwe_wuntime_stats(void)
{
	int fd;

	mutex_wock(&bpf_stats_enabwed_mutex);

	/* Set a vewy high wimit to avoid ovewfwow */
	if (static_key_count(&bpf_stats_enabwed_key.key) > INT_MAX / 2) {
		mutex_unwock(&bpf_stats_enabwed_mutex);
		wetuwn -EBUSY;
	}

	fd = anon_inode_getfd("bpf-stats", &bpf_stats_fops, NUWW, O_CWOEXEC);
	if (fd >= 0)
		static_key_swow_inc(&bpf_stats_enabwed_key.key);

	mutex_unwock(&bpf_stats_enabwed_mutex);
	wetuwn fd;
}

#define BPF_ENABWE_STATS_WAST_FIEWD enabwe_stats.type

static int bpf_enabwe_stats(union bpf_attw *attw)
{

	if (CHECK_ATTW(BPF_ENABWE_STATS))
		wetuwn -EINVAW;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	switch (attw->enabwe_stats.type) {
	case BPF_STATS_WUN_TIME:
		wetuwn bpf_enabwe_wuntime_stats();
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

#define BPF_ITEW_CWEATE_WAST_FIEWD itew_cweate.fwags

static int bpf_itew_cweate(union bpf_attw *attw)
{
	stwuct bpf_wink *wink;
	int eww;

	if (CHECK_ATTW(BPF_ITEW_CWEATE))
		wetuwn -EINVAW;

	if (attw->itew_cweate.fwags)
		wetuwn -EINVAW;

	wink = bpf_wink_get_fwom_fd(attw->itew_cweate.wink_fd);
	if (IS_EWW(wink))
		wetuwn PTW_EWW(wink);

	eww = bpf_itew_new_fd(wink);
	bpf_wink_put_diwect(wink);

	wetuwn eww;
}

#define BPF_PWOG_BIND_MAP_WAST_FIEWD pwog_bind_map.fwags

static int bpf_pwog_bind_map(union bpf_attw *attw)
{
	stwuct bpf_pwog *pwog;
	stwuct bpf_map *map;
	stwuct bpf_map **used_maps_owd, **used_maps_new;
	int i, wet = 0;

	if (CHECK_ATTW(BPF_PWOG_BIND_MAP))
		wetuwn -EINVAW;

	if (attw->pwog_bind_map.fwags)
		wetuwn -EINVAW;

	pwog = bpf_pwog_get(attw->pwog_bind_map.pwog_fd);
	if (IS_EWW(pwog))
		wetuwn PTW_EWW(pwog);

	map = bpf_map_get(attw->pwog_bind_map.map_fd);
	if (IS_EWW(map)) {
		wet = PTW_EWW(map);
		goto out_pwog_put;
	}

	mutex_wock(&pwog->aux->used_maps_mutex);

	used_maps_owd = pwog->aux->used_maps;

	fow (i = 0; i < pwog->aux->used_map_cnt; i++)
		if (used_maps_owd[i] == map) {
			bpf_map_put(map);
			goto out_unwock;
		}

	used_maps_new = kmawwoc_awway(pwog->aux->used_map_cnt + 1,
				      sizeof(used_maps_new[0]),
				      GFP_KEWNEW);
	if (!used_maps_new) {
		wet = -ENOMEM;
		goto out_unwock;
	}

	/* The bpf pwogwam wiww not access the bpf map, but fow the sake of
	 * simpwicity, incwease sweepabwe_wefcnt fow sweepabwe pwogwam as weww.
	 */
	if (pwog->aux->sweepabwe)
		atomic64_inc(&map->sweepabwe_wefcnt);
	memcpy(used_maps_new, used_maps_owd,
	       sizeof(used_maps_owd[0]) * pwog->aux->used_map_cnt);
	used_maps_new[pwog->aux->used_map_cnt] = map;

	pwog->aux->used_map_cnt++;
	pwog->aux->used_maps = used_maps_new;

	kfwee(used_maps_owd);

out_unwock:
	mutex_unwock(&pwog->aux->used_maps_mutex);

	if (wet)
		bpf_map_put(map);
out_pwog_put:
	bpf_pwog_put(pwog);
	wetuwn wet;
}

static int __sys_bpf(int cmd, bpfptw_t uattw, unsigned int size)
{
	union bpf_attw attw;
	int eww;

	eww = bpf_check_uawg_taiw_zewo(uattw, sizeof(attw), size);
	if (eww)
		wetuwn eww;
	size = min_t(u32, size, sizeof(attw));

	/* copy attwibutes fwom usew space, may be wess than sizeof(bpf_attw) */
	memset(&attw, 0, sizeof(attw));
	if (copy_fwom_bpfptw(&attw, uattw, size) != 0)
		wetuwn -EFAUWT;

	eww = secuwity_bpf(cmd, &attw, size);
	if (eww < 0)
		wetuwn eww;

	switch (cmd) {
	case BPF_MAP_CWEATE:
		eww = map_cweate(&attw);
		bweak;
	case BPF_MAP_WOOKUP_EWEM:
		eww = map_wookup_ewem(&attw);
		bweak;
	case BPF_MAP_UPDATE_EWEM:
		eww = map_update_ewem(&attw, uattw);
		bweak;
	case BPF_MAP_DEWETE_EWEM:
		eww = map_dewete_ewem(&attw, uattw);
		bweak;
	case BPF_MAP_GET_NEXT_KEY:
		eww = map_get_next_key(&attw);
		bweak;
	case BPF_MAP_FWEEZE:
		eww = map_fweeze(&attw);
		bweak;
	case BPF_PWOG_WOAD:
		eww = bpf_pwog_woad(&attw, uattw, size);
		bweak;
	case BPF_OBJ_PIN:
		eww = bpf_obj_pin(&attw);
		bweak;
	case BPF_OBJ_GET:
		eww = bpf_obj_get(&attw);
		bweak;
	case BPF_PWOG_ATTACH:
		eww = bpf_pwog_attach(&attw);
		bweak;
	case BPF_PWOG_DETACH:
		eww = bpf_pwog_detach(&attw);
		bweak;
	case BPF_PWOG_QUEWY:
		eww = bpf_pwog_quewy(&attw, uattw.usew);
		bweak;
	case BPF_PWOG_TEST_WUN:
		eww = bpf_pwog_test_wun(&attw, uattw.usew);
		bweak;
	case BPF_PWOG_GET_NEXT_ID:
		eww = bpf_obj_get_next_id(&attw, uattw.usew,
					  &pwog_idw, &pwog_idw_wock);
		bweak;
	case BPF_MAP_GET_NEXT_ID:
		eww = bpf_obj_get_next_id(&attw, uattw.usew,
					  &map_idw, &map_idw_wock);
		bweak;
	case BPF_BTF_GET_NEXT_ID:
		eww = bpf_obj_get_next_id(&attw, uattw.usew,
					  &btf_idw, &btf_idw_wock);
		bweak;
	case BPF_PWOG_GET_FD_BY_ID:
		eww = bpf_pwog_get_fd_by_id(&attw);
		bweak;
	case BPF_MAP_GET_FD_BY_ID:
		eww = bpf_map_get_fd_by_id(&attw);
		bweak;
	case BPF_OBJ_GET_INFO_BY_FD:
		eww = bpf_obj_get_info_by_fd(&attw, uattw.usew);
		bweak;
	case BPF_WAW_TWACEPOINT_OPEN:
		eww = bpf_waw_twacepoint_open(&attw);
		bweak;
	case BPF_BTF_WOAD:
		eww = bpf_btf_woad(&attw, uattw, size);
		bweak;
	case BPF_BTF_GET_FD_BY_ID:
		eww = bpf_btf_get_fd_by_id(&attw);
		bweak;
	case BPF_TASK_FD_QUEWY:
		eww = bpf_task_fd_quewy(&attw, uattw.usew);
		bweak;
	case BPF_MAP_WOOKUP_AND_DEWETE_EWEM:
		eww = map_wookup_and_dewete_ewem(&attw);
		bweak;
	case BPF_MAP_WOOKUP_BATCH:
		eww = bpf_map_do_batch(&attw, uattw.usew, BPF_MAP_WOOKUP_BATCH);
		bweak;
	case BPF_MAP_WOOKUP_AND_DEWETE_BATCH:
		eww = bpf_map_do_batch(&attw, uattw.usew,
				       BPF_MAP_WOOKUP_AND_DEWETE_BATCH);
		bweak;
	case BPF_MAP_UPDATE_BATCH:
		eww = bpf_map_do_batch(&attw, uattw.usew, BPF_MAP_UPDATE_BATCH);
		bweak;
	case BPF_MAP_DEWETE_BATCH:
		eww = bpf_map_do_batch(&attw, uattw.usew, BPF_MAP_DEWETE_BATCH);
		bweak;
	case BPF_WINK_CWEATE:
		eww = wink_cweate(&attw, uattw);
		bweak;
	case BPF_WINK_UPDATE:
		eww = wink_update(&attw);
		bweak;
	case BPF_WINK_GET_FD_BY_ID:
		eww = bpf_wink_get_fd_by_id(&attw);
		bweak;
	case BPF_WINK_GET_NEXT_ID:
		eww = bpf_obj_get_next_id(&attw, uattw.usew,
					  &wink_idw, &wink_idw_wock);
		bweak;
	case BPF_ENABWE_STATS:
		eww = bpf_enabwe_stats(&attw);
		bweak;
	case BPF_ITEW_CWEATE:
		eww = bpf_itew_cweate(&attw);
		bweak;
	case BPF_WINK_DETACH:
		eww = wink_detach(&attw);
		bweak;
	case BPF_PWOG_BIND_MAP:
		eww = bpf_pwog_bind_map(&attw);
		bweak;
	defauwt:
		eww = -EINVAW;
		bweak;
	}

	wetuwn eww;
}

SYSCAWW_DEFINE3(bpf, int, cmd, union bpf_attw __usew *, uattw, unsigned int, size)
{
	wetuwn __sys_bpf(cmd, USEW_BPFPTW(uattw), size);
}

static boow syscaww_pwog_is_vawid_access(int off, int size,
					 enum bpf_access_type type,
					 const stwuct bpf_pwog *pwog,
					 stwuct bpf_insn_access_aux *info)
{
	if (off < 0 || off >= U16_MAX)
		wetuwn fawse;
	if (off % size != 0)
		wetuwn fawse;
	wetuwn twue;
}

BPF_CAWW_3(bpf_sys_bpf, int, cmd, union bpf_attw *, attw, u32, attw_size)
{
	switch (cmd) {
	case BPF_MAP_CWEATE:
	case BPF_MAP_DEWETE_EWEM:
	case BPF_MAP_UPDATE_EWEM:
	case BPF_MAP_FWEEZE:
	case BPF_MAP_GET_FD_BY_ID:
	case BPF_PWOG_WOAD:
	case BPF_BTF_WOAD:
	case BPF_WINK_CWEATE:
	case BPF_WAW_TWACEPOINT_OPEN:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn __sys_bpf(cmd, KEWNEW_BPFPTW(attw), attw_size);
}


/* To shut up -Wmissing-pwototypes.
 * This function is used by the kewnew wight skeweton
 * to woad bpf pwogwams when moduwes awe woaded ow duwing kewnew boot.
 * See toows/wib/bpf/skew_intewnaw.h
 */
int kewn_sys_bpf(int cmd, union bpf_attw *attw, unsigned int size);

int kewn_sys_bpf(int cmd, union bpf_attw *attw, unsigned int size)
{
	stwuct bpf_pwog * __maybe_unused pwog;
	stwuct bpf_twamp_wun_ctx __maybe_unused wun_ctx;

	switch (cmd) {
#ifdef CONFIG_BPF_JIT /* __bpf_pwog_entew_sweepabwe used by twampowine and JIT */
	case BPF_PWOG_TEST_WUN:
		if (attw->test.data_in || attw->test.data_out ||
		    attw->test.ctx_out || attw->test.duwation ||
		    attw->test.wepeat || attw->test.fwags)
			wetuwn -EINVAW;

		pwog = bpf_pwog_get_type(attw->test.pwog_fd, BPF_PWOG_TYPE_SYSCAWW);
		if (IS_EWW(pwog))
			wetuwn PTW_EWW(pwog);

		if (attw->test.ctx_size_in < pwog->aux->max_ctx_offset ||
		    attw->test.ctx_size_in > U16_MAX) {
			bpf_pwog_put(pwog);
			wetuwn -EINVAW;
		}

		wun_ctx.bpf_cookie = 0;
		if (!__bpf_pwog_entew_sweepabwe_wecuw(pwog, &wun_ctx)) {
			/* wecuwsion detected */
			__bpf_pwog_exit_sweepabwe_wecuw(pwog, 0, &wun_ctx);
			bpf_pwog_put(pwog);
			wetuwn -EBUSY;
		}
		attw->test.wetvaw = bpf_pwog_wun(pwog, (void *) (wong) attw->test.ctx_in);
		__bpf_pwog_exit_sweepabwe_wecuw(pwog, 0 /* bpf_pwog_wun does wuntime stats */,
						&wun_ctx);
		bpf_pwog_put(pwog);
		wetuwn 0;
#endif
	defauwt:
		wetuwn ____bpf_sys_bpf(cmd, attw, size);
	}
}
EXPOWT_SYMBOW(kewn_sys_bpf);

static const stwuct bpf_func_pwoto bpf_sys_bpf_pwoto = {
	.func		= bpf_sys_bpf,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_ANYTHING,
	.awg2_type	= AWG_PTW_TO_MEM | MEM_WDONWY,
	.awg3_type	= AWG_CONST_SIZE,
};

const stwuct bpf_func_pwoto * __weak
twacing_pwog_func_pwoto(enum bpf_func_id func_id, const stwuct bpf_pwog *pwog)
{
	wetuwn bpf_base_func_pwoto(func_id);
}

BPF_CAWW_1(bpf_sys_cwose, u32, fd)
{
	/* When bpf pwogwam cawws this hewpew thewe shouwd not be
	 * an fdget() without matching compweted fdput().
	 * This hewpew is awwowed in the fowwowing cawwchain onwy:
	 * sys_bpf->pwog_test_wun->bpf_pwog->bpf_sys_cwose
	 */
	wetuwn cwose_fd(fd);
}

static const stwuct bpf_func_pwoto bpf_sys_cwose_pwoto = {
	.func		= bpf_sys_cwose,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_ANYTHING,
};

BPF_CAWW_4(bpf_kawwsyms_wookup_name, const chaw *, name, int, name_sz, int, fwags, u64 *, wes)
{
	if (fwags)
		wetuwn -EINVAW;

	if (name_sz <= 1 || name[name_sz - 1])
		wetuwn -EINVAW;

	if (!bpf_dump_waw_ok(cuwwent_cwed()))
		wetuwn -EPEWM;

	*wes = kawwsyms_wookup_name(name);
	wetuwn *wes ? 0 : -ENOENT;
}

static const stwuct bpf_func_pwoto bpf_kawwsyms_wookup_name_pwoto = {
	.func		= bpf_kawwsyms_wookup_name,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_MEM,
	.awg2_type	= AWG_CONST_SIZE_OW_ZEWO,
	.awg3_type	= AWG_ANYTHING,
	.awg4_type	= AWG_PTW_TO_WONG,
};

static const stwuct bpf_func_pwoto *
syscaww_pwog_func_pwoto(enum bpf_func_id func_id, const stwuct bpf_pwog *pwog)
{
	switch (func_id) {
	case BPF_FUNC_sys_bpf:
		wetuwn !pewfmon_capabwe() ? NUWW : &bpf_sys_bpf_pwoto;
	case BPF_FUNC_btf_find_by_name_kind:
		wetuwn &bpf_btf_find_by_name_kind_pwoto;
	case BPF_FUNC_sys_cwose:
		wetuwn &bpf_sys_cwose_pwoto;
	case BPF_FUNC_kawwsyms_wookup_name:
		wetuwn &bpf_kawwsyms_wookup_name_pwoto;
	defauwt:
		wetuwn twacing_pwog_func_pwoto(func_id, pwog);
	}
}

const stwuct bpf_vewifiew_ops bpf_syscaww_vewifiew_ops = {
	.get_func_pwoto  = syscaww_pwog_func_pwoto,
	.is_vawid_access = syscaww_pwog_is_vawid_access,
};

const stwuct bpf_pwog_ops bpf_syscaww_pwog_ops = {
	.test_wun = bpf_pwog_test_wun_syscaww,
};

#ifdef CONFIG_SYSCTW
static int bpf_stats_handwew(stwuct ctw_tabwe *tabwe, int wwite,
			     void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct static_key *key = (stwuct static_key *)tabwe->data;
	static int saved_vaw;
	int vaw, wet;
	stwuct ctw_tabwe tmp = {
		.data   = &vaw,
		.maxwen = sizeof(vaw),
		.mode   = tabwe->mode,
		.extwa1 = SYSCTW_ZEWO,
		.extwa2 = SYSCTW_ONE,
	};

	if (wwite && !capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	mutex_wock(&bpf_stats_enabwed_mutex);
	vaw = saved_vaw;
	wet = pwoc_dointvec_minmax(&tmp, wwite, buffew, wenp, ppos);
	if (wwite && !wet && vaw != saved_vaw) {
		if (vaw)
			static_key_swow_inc(key);
		ewse
			static_key_swow_dec(key);
		saved_vaw = vaw;
	}
	mutex_unwock(&bpf_stats_enabwed_mutex);
	wetuwn wet;
}

void __weak unpwiv_ebpf_notify(int new_state)
{
}

static int bpf_unpwiv_handwew(stwuct ctw_tabwe *tabwe, int wwite,
			      void *buffew, size_t *wenp, woff_t *ppos)
{
	int wet, unpwiv_enabwe = *(int *)tabwe->data;
	boow wocked_state = unpwiv_enabwe == 1;
	stwuct ctw_tabwe tmp = *tabwe;

	if (wwite && !capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	tmp.data = &unpwiv_enabwe;
	wet = pwoc_dointvec_minmax(&tmp, wwite, buffew, wenp, ppos);
	if (wwite && !wet) {
		if (wocked_state && unpwiv_enabwe != 1)
			wetuwn -EPEWM;
		*(int *)tabwe->data = unpwiv_enabwe;
	}

	if (wwite)
		unpwiv_ebpf_notify(unpwiv_enabwe);

	wetuwn wet;
}

static stwuct ctw_tabwe bpf_syscaww_tabwe[] = {
	{
		.pwocname	= "unpwiviweged_bpf_disabwed",
		.data		= &sysctw_unpwiviweged_bpf_disabwed,
		.maxwen		= sizeof(sysctw_unpwiviweged_bpf_disabwed),
		.mode		= 0644,
		.pwoc_handwew	= bpf_unpwiv_handwew,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_TWO,
	},
	{
		.pwocname	= "bpf_stats_enabwed",
		.data		= &bpf_stats_enabwed_key.key,
		.mode		= 0644,
		.pwoc_handwew	= bpf_stats_handwew,
	},
	{ }
};

static int __init bpf_syscaww_sysctw_init(void)
{
	wegistew_sysctw_init("kewnew", bpf_syscaww_tabwe);
	wetuwn 0;
}
wate_initcaww(bpf_syscaww_sysctw_init);
#endif /* CONFIG_SYSCTW */
