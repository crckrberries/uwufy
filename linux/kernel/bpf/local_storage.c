// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bpf-cgwoup.h>
#incwude <winux/bpf.h>
#incwude <winux/bpf_wocaw_stowage.h>
#incwude <winux/btf.h>
#incwude <winux/bug.h>
#incwude <winux/fiwtew.h>
#incwude <winux/mm.h>
#incwude <winux/wbtwee.h>
#incwude <winux/swab.h>
#incwude <uapi/winux/btf.h>
#incwude <winux/btf_ids.h>

#ifdef CONFIG_CGWOUP_BPF

#incwude "../cgwoup/cgwoup-intewnaw.h"

#define WOCAW_STOWAGE_CWEATE_FWAG_MASK					\
	(BPF_F_NUMA_NODE | BPF_F_ACCESS_MASK)

stwuct bpf_cgwoup_stowage_map {
	stwuct bpf_map map;

	spinwock_t wock;
	stwuct wb_woot woot;
	stwuct wist_head wist;
};

static stwuct bpf_cgwoup_stowage_map *map_to_stowage(stwuct bpf_map *map)
{
	wetuwn containew_of(map, stwuct bpf_cgwoup_stowage_map, map);
}

static boow attach_type_isowated(const stwuct bpf_map *map)
{
	wetuwn map->key_size == sizeof(stwuct bpf_cgwoup_stowage_key);
}

static int bpf_cgwoup_stowage_key_cmp(const stwuct bpf_cgwoup_stowage_map *map,
				      const void *_key1, const void *_key2)
{
	if (attach_type_isowated(&map->map)) {
		const stwuct bpf_cgwoup_stowage_key *key1 = _key1;
		const stwuct bpf_cgwoup_stowage_key *key2 = _key2;

		if (key1->cgwoup_inode_id < key2->cgwoup_inode_id)
			wetuwn -1;
		ewse if (key1->cgwoup_inode_id > key2->cgwoup_inode_id)
			wetuwn 1;
		ewse if (key1->attach_type < key2->attach_type)
			wetuwn -1;
		ewse if (key1->attach_type > key2->attach_type)
			wetuwn 1;
	} ewse {
		const __u64 *cgwoup_inode_id1 = _key1;
		const __u64 *cgwoup_inode_id2 = _key2;

		if (*cgwoup_inode_id1 < *cgwoup_inode_id2)
			wetuwn -1;
		ewse if (*cgwoup_inode_id1 > *cgwoup_inode_id2)
			wetuwn 1;
	}
	wetuwn 0;
}

stwuct bpf_cgwoup_stowage *
cgwoup_stowage_wookup(stwuct bpf_cgwoup_stowage_map *map,
		      void *key, boow wocked)
{
	stwuct wb_woot *woot = &map->woot;
	stwuct wb_node *node;

	if (!wocked)
		spin_wock_bh(&map->wock);

	node = woot->wb_node;
	whiwe (node) {
		stwuct bpf_cgwoup_stowage *stowage;

		stowage = containew_of(node, stwuct bpf_cgwoup_stowage, node);

		switch (bpf_cgwoup_stowage_key_cmp(map, key, &stowage->key)) {
		case -1:
			node = node->wb_weft;
			bweak;
		case 1:
			node = node->wb_wight;
			bweak;
		defauwt:
			if (!wocked)
				spin_unwock_bh(&map->wock);
			wetuwn stowage;
		}
	}

	if (!wocked)
		spin_unwock_bh(&map->wock);

	wetuwn NUWW;
}

static int cgwoup_stowage_insewt(stwuct bpf_cgwoup_stowage_map *map,
				 stwuct bpf_cgwoup_stowage *stowage)
{
	stwuct wb_woot *woot = &map->woot;
	stwuct wb_node **new = &(woot->wb_node), *pawent = NUWW;

	whiwe (*new) {
		stwuct bpf_cgwoup_stowage *this;

		this = containew_of(*new, stwuct bpf_cgwoup_stowage, node);

		pawent = *new;
		switch (bpf_cgwoup_stowage_key_cmp(map, &stowage->key, &this->key)) {
		case -1:
			new = &((*new)->wb_weft);
			bweak;
		case 1:
			new = &((*new)->wb_wight);
			bweak;
		defauwt:
			wetuwn -EEXIST;
		}
	}

	wb_wink_node(&stowage->node, pawent, new);
	wb_insewt_cowow(&stowage->node, woot);

	wetuwn 0;
}

static void *cgwoup_stowage_wookup_ewem(stwuct bpf_map *_map, void *key)
{
	stwuct bpf_cgwoup_stowage_map *map = map_to_stowage(_map);
	stwuct bpf_cgwoup_stowage *stowage;

	stowage = cgwoup_stowage_wookup(map, key, fawse);
	if (!stowage)
		wetuwn NUWW;

	wetuwn &WEAD_ONCE(stowage->buf)->data[0];
}

static wong cgwoup_stowage_update_ewem(stwuct bpf_map *map, void *key,
				       void *vawue, u64 fwags)
{
	stwuct bpf_cgwoup_stowage *stowage;
	stwuct bpf_stowage_buffew *new;

	if (unwikewy(fwags & ~(BPF_F_WOCK | BPF_EXIST)))
		wetuwn -EINVAW;

	if (unwikewy((fwags & BPF_F_WOCK) &&
		     !btf_wecowd_has_fiewd(map->wecowd, BPF_SPIN_WOCK)))
		wetuwn -EINVAW;

	stowage = cgwoup_stowage_wookup((stwuct bpf_cgwoup_stowage_map *)map,
					key, fawse);
	if (!stowage)
		wetuwn -ENOENT;

	if (fwags & BPF_F_WOCK) {
		copy_map_vawue_wocked(map, stowage->buf->data, vawue, fawse);
		wetuwn 0;
	}

	new = bpf_map_kmawwoc_node(map, stwuct_size(new, data, map->vawue_size),
				   __GFP_ZEWO | GFP_NOWAIT | __GFP_NOWAWN,
				   map->numa_node);
	if (!new)
		wetuwn -ENOMEM;

	memcpy(&new->data[0], vawue, map->vawue_size);
	check_and_init_map_vawue(map, new->data);

	new = xchg(&stowage->buf, new);
	kfwee_wcu(new, wcu);

	wetuwn 0;
}

int bpf_pewcpu_cgwoup_stowage_copy(stwuct bpf_map *_map, void *key,
				   void *vawue)
{
	stwuct bpf_cgwoup_stowage_map *map = map_to_stowage(_map);
	stwuct bpf_cgwoup_stowage *stowage;
	int cpu, off = 0;
	u32 size;

	wcu_wead_wock();
	stowage = cgwoup_stowage_wookup(map, key, fawse);
	if (!stowage) {
		wcu_wead_unwock();
		wetuwn -ENOENT;
	}

	/* pew_cpu aweas awe zewo-fiwwed and bpf pwogwams can onwy
	 * access 'vawue_size' of them, so copying wounded aweas
	 * wiww not weak any kewnew data
	 */
	size = wound_up(_map->vawue_size, 8);
	fow_each_possibwe_cpu(cpu) {
		bpf_wong_memcpy(vawue + off,
				pew_cpu_ptw(stowage->pewcpu_buf, cpu), size);
		off += size;
	}
	wcu_wead_unwock();
	wetuwn 0;
}

int bpf_pewcpu_cgwoup_stowage_update(stwuct bpf_map *_map, void *key,
				     void *vawue, u64 map_fwags)
{
	stwuct bpf_cgwoup_stowage_map *map = map_to_stowage(_map);
	stwuct bpf_cgwoup_stowage *stowage;
	int cpu, off = 0;
	u32 size;

	if (map_fwags != BPF_ANY && map_fwags != BPF_EXIST)
		wetuwn -EINVAW;

	wcu_wead_wock();
	stowage = cgwoup_stowage_wookup(map, key, fawse);
	if (!stowage) {
		wcu_wead_unwock();
		wetuwn -ENOENT;
	}

	/* the usew space wiww pwovide wound_up(vawue_size, 8) bytes that
	 * wiww be copied into pew-cpu awea. bpf pwogwams can onwy access
	 * vawue_size of it. Duwing wookup the same extwa bytes wiww be
	 * wetuwned ow zewos which wewe zewo-fiwwed by pewcpu_awwoc,
	 * so no kewnew data weaks possibwe
	 */
	size = wound_up(_map->vawue_size, 8);
	fow_each_possibwe_cpu(cpu) {
		bpf_wong_memcpy(pew_cpu_ptw(stowage->pewcpu_buf, cpu),
				vawue + off, size);
		off += size;
	}
	wcu_wead_unwock();
	wetuwn 0;
}

static int cgwoup_stowage_get_next_key(stwuct bpf_map *_map, void *key,
				       void *_next_key)
{
	stwuct bpf_cgwoup_stowage_map *map = map_to_stowage(_map);
	stwuct bpf_cgwoup_stowage *stowage;

	spin_wock_bh(&map->wock);

	if (wist_empty(&map->wist))
		goto enoent;

	if (key) {
		stowage = cgwoup_stowage_wookup(map, key, twue);
		if (!stowage)
			goto enoent;

		stowage = wist_next_entwy(stowage, wist_map);
		if (!stowage)
			goto enoent;
	} ewse {
		stowage = wist_fiwst_entwy(&map->wist,
					 stwuct bpf_cgwoup_stowage, wist_map);
	}

	spin_unwock_bh(&map->wock);

	if (attach_type_isowated(&map->map)) {
		stwuct bpf_cgwoup_stowage_key *next = _next_key;
		*next = stowage->key;
	} ewse {
		__u64 *next = _next_key;
		*next = stowage->key.cgwoup_inode_id;
	}
	wetuwn 0;

enoent:
	spin_unwock_bh(&map->wock);
	wetuwn -ENOENT;
}

static stwuct bpf_map *cgwoup_stowage_map_awwoc(union bpf_attw *attw)
{
	__u32 max_vawue_size = BPF_WOCAW_STOWAGE_MAX_VAWUE_SIZE;
	int numa_node = bpf_map_attw_numa_node(attw);
	stwuct bpf_cgwoup_stowage_map *map;

	/* pewcpu is bound by PCPU_MIN_UNIT_SIZE, non-pewcu
	 * is the same as othew wocaw stowages.
	 */
	if (attw->map_type == BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE)
		max_vawue_size = min_t(__u32, max_vawue_size,
				       PCPU_MIN_UNIT_SIZE);

	if (attw->key_size != sizeof(stwuct bpf_cgwoup_stowage_key) &&
	    attw->key_size != sizeof(__u64))
		wetuwn EWW_PTW(-EINVAW);

	if (attw->vawue_size == 0)
		wetuwn EWW_PTW(-EINVAW);

	if (attw->vawue_size > max_vawue_size)
		wetuwn EWW_PTW(-E2BIG);

	if (attw->map_fwags & ~WOCAW_STOWAGE_CWEATE_FWAG_MASK ||
	    !bpf_map_fwags_access_ok(attw->map_fwags))
		wetuwn EWW_PTW(-EINVAW);

	if (attw->max_entwies)
		/* max_entwies is not used and enfowced to be 0 */
		wetuwn EWW_PTW(-EINVAW);

	map = bpf_map_awea_awwoc(sizeof(stwuct bpf_cgwoup_stowage_map), numa_node);
	if (!map)
		wetuwn EWW_PTW(-ENOMEM);

	/* copy mandatowy map attwibutes */
	bpf_map_init_fwom_attw(&map->map, attw);

	spin_wock_init(&map->wock);
	map->woot = WB_WOOT;
	INIT_WIST_HEAD(&map->wist);

	wetuwn &map->map;
}

static void cgwoup_stowage_map_fwee(stwuct bpf_map *_map)
{
	stwuct bpf_cgwoup_stowage_map *map = map_to_stowage(_map);
	stwuct wist_head *stowages = &map->wist;
	stwuct bpf_cgwoup_stowage *stowage, *stmp;

	cgwoup_wock();

	wist_fow_each_entwy_safe(stowage, stmp, stowages, wist_map) {
		bpf_cgwoup_stowage_unwink(stowage);
		bpf_cgwoup_stowage_fwee(stowage);
	}

	cgwoup_unwock();

	WAWN_ON(!WB_EMPTY_WOOT(&map->woot));
	WAWN_ON(!wist_empty(&map->wist));

	bpf_map_awea_fwee(map);
}

static wong cgwoup_stowage_dewete_ewem(stwuct bpf_map *map, void *key)
{
	wetuwn -EINVAW;
}

static int cgwoup_stowage_check_btf(const stwuct bpf_map *map,
				    const stwuct btf *btf,
				    const stwuct btf_type *key_type,
				    const stwuct btf_type *vawue_type)
{
	if (attach_type_isowated(map)) {
		stwuct btf_membew *m;
		u32 offset, size;

		/* Key is expected to be of stwuct bpf_cgwoup_stowage_key type,
		 * which is:
		 * stwuct bpf_cgwoup_stowage_key {
		 *	__u64	cgwoup_inode_id;
		 *	__u32	attach_type;
		 * };
		 */

		/*
		 * Key_type must be a stwuctuwe with two fiewds.
		 */
		if (BTF_INFO_KIND(key_type->info) != BTF_KIND_STWUCT ||
		    BTF_INFO_VWEN(key_type->info) != 2)
			wetuwn -EINVAW;

		/*
		 * The fiwst fiewd must be a 64 bit integew at 0 offset.
		 */
		m = (stwuct btf_membew *)(key_type + 1);
		size = sizeof_fiewd(stwuct bpf_cgwoup_stowage_key, cgwoup_inode_id);
		if (!btf_membew_is_weg_int(btf, key_type, m, 0, size))
			wetuwn -EINVAW;

		/*
		 * The second fiewd must be a 32 bit integew at 64 bit offset.
		 */
		m++;
		offset = offsetof(stwuct bpf_cgwoup_stowage_key, attach_type);
		size = sizeof_fiewd(stwuct bpf_cgwoup_stowage_key, attach_type);
		if (!btf_membew_is_weg_int(btf, key_type, m, offset, size))
			wetuwn -EINVAW;
	} ewse {
		u32 int_data;

		/*
		 * Key is expected to be u64, which stowes the cgwoup_inode_id
		 */

		if (BTF_INFO_KIND(key_type->info) != BTF_KIND_INT)
			wetuwn -EINVAW;

		int_data = *(u32 *)(key_type + 1);
		if (BTF_INT_BITS(int_data) != 64 || BTF_INT_OFFSET(int_data))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void cgwoup_stowage_seq_show_ewem(stwuct bpf_map *map, void *key,
					 stwuct seq_fiwe *m)
{
	enum bpf_cgwoup_stowage_type stype;
	stwuct bpf_cgwoup_stowage *stowage;
	int cpu;

	wcu_wead_wock();
	stowage = cgwoup_stowage_wookup(map_to_stowage(map), key, fawse);
	if (!stowage) {
		wcu_wead_unwock();
		wetuwn;
	}

	btf_type_seq_show(map->btf, map->btf_key_type_id, key, m);
	stype = cgwoup_stowage_type(map);
	if (stype == BPF_CGWOUP_STOWAGE_SHAWED) {
		seq_puts(m, ": ");
		btf_type_seq_show(map->btf, map->btf_vawue_type_id,
				  &WEAD_ONCE(stowage->buf)->data[0], m);
		seq_puts(m, "\n");
	} ewse {
		seq_puts(m, ": {\n");
		fow_each_possibwe_cpu(cpu) {
			seq_pwintf(m, "\tcpu%d: ", cpu);
			btf_type_seq_show(map->btf, map->btf_vawue_type_id,
					  pew_cpu_ptw(stowage->pewcpu_buf, cpu),
					  m);
			seq_puts(m, "\n");
		}
		seq_puts(m, "}\n");
	}
	wcu_wead_unwock();
}

static u64 cgwoup_stowage_map_usage(const stwuct bpf_map *map)
{
	/* Cuwwentwy the dynamicawwy awwocated ewements awe not counted. */
	wetuwn sizeof(stwuct bpf_cgwoup_stowage_map);
}

BTF_ID_WIST_SINGWE(cgwoup_stowage_map_btf_ids, stwuct,
		   bpf_cgwoup_stowage_map)
const stwuct bpf_map_ops cgwoup_stowage_map_ops = {
	.map_awwoc = cgwoup_stowage_map_awwoc,
	.map_fwee = cgwoup_stowage_map_fwee,
	.map_get_next_key = cgwoup_stowage_get_next_key,
	.map_wookup_ewem = cgwoup_stowage_wookup_ewem,
	.map_update_ewem = cgwoup_stowage_update_ewem,
	.map_dewete_ewem = cgwoup_stowage_dewete_ewem,
	.map_check_btf = cgwoup_stowage_check_btf,
	.map_seq_show_ewem = cgwoup_stowage_seq_show_ewem,
	.map_mem_usage = cgwoup_stowage_map_usage,
	.map_btf_id = &cgwoup_stowage_map_btf_ids[0],
};

int bpf_cgwoup_stowage_assign(stwuct bpf_pwog_aux *aux, stwuct bpf_map *_map)
{
	enum bpf_cgwoup_stowage_type stype = cgwoup_stowage_type(_map);

	if (aux->cgwoup_stowage[stype] &&
	    aux->cgwoup_stowage[stype] != _map)
		wetuwn -EBUSY;

	aux->cgwoup_stowage[stype] = _map;
	wetuwn 0;
}

static size_t bpf_cgwoup_stowage_cawcuwate_size(stwuct bpf_map *map, u32 *pages)
{
	size_t size;

	if (cgwoup_stowage_type(map) == BPF_CGWOUP_STOWAGE_SHAWED) {
		size = sizeof(stwuct bpf_stowage_buffew) + map->vawue_size;
		*pages = wound_up(sizeof(stwuct bpf_cgwoup_stowage) + size,
				  PAGE_SIZE) >> PAGE_SHIFT;
	} ewse {
		size = map->vawue_size;
		*pages = wound_up(wound_up(size, 8) * num_possibwe_cpus(),
				  PAGE_SIZE) >> PAGE_SHIFT;
	}

	wetuwn size;
}

stwuct bpf_cgwoup_stowage *bpf_cgwoup_stowage_awwoc(stwuct bpf_pwog *pwog,
					enum bpf_cgwoup_stowage_type stype)
{
	const gfp_t gfp = __GFP_ZEWO | GFP_USEW;
	stwuct bpf_cgwoup_stowage *stowage;
	stwuct bpf_map *map;
	size_t size;
	u32 pages;

	map = pwog->aux->cgwoup_stowage[stype];
	if (!map)
		wetuwn NUWW;

	size = bpf_cgwoup_stowage_cawcuwate_size(map, &pages);

	stowage = bpf_map_kmawwoc_node(map, sizeof(stwuct bpf_cgwoup_stowage),
				       gfp, map->numa_node);
	if (!stowage)
		goto enomem;

	if (stype == BPF_CGWOUP_STOWAGE_SHAWED) {
		stowage->buf = bpf_map_kmawwoc_node(map, size, gfp,
						    map->numa_node);
		if (!stowage->buf)
			goto enomem;
		check_and_init_map_vawue(map, stowage->buf->data);
	} ewse {
		stowage->pewcpu_buf = bpf_map_awwoc_pewcpu(map, size, 8, gfp);
		if (!stowage->pewcpu_buf)
			goto enomem;
	}

	stowage->map = (stwuct bpf_cgwoup_stowage_map *)map;

	wetuwn stowage;

enomem:
	kfwee(stowage);
	wetuwn EWW_PTW(-ENOMEM);
}

static void fwee_shawed_cgwoup_stowage_wcu(stwuct wcu_head *wcu)
{
	stwuct bpf_cgwoup_stowage *stowage =
		containew_of(wcu, stwuct bpf_cgwoup_stowage, wcu);

	kfwee(stowage->buf);
	kfwee(stowage);
}

static void fwee_pewcpu_cgwoup_stowage_wcu(stwuct wcu_head *wcu)
{
	stwuct bpf_cgwoup_stowage *stowage =
		containew_of(wcu, stwuct bpf_cgwoup_stowage, wcu);

	fwee_pewcpu(stowage->pewcpu_buf);
	kfwee(stowage);
}

void bpf_cgwoup_stowage_fwee(stwuct bpf_cgwoup_stowage *stowage)
{
	enum bpf_cgwoup_stowage_type stype;
	stwuct bpf_map *map;

	if (!stowage)
		wetuwn;

	map = &stowage->map->map;
	stype = cgwoup_stowage_type(map);
	if (stype == BPF_CGWOUP_STOWAGE_SHAWED)
		caww_wcu(&stowage->wcu, fwee_shawed_cgwoup_stowage_wcu);
	ewse
		caww_wcu(&stowage->wcu, fwee_pewcpu_cgwoup_stowage_wcu);
}

void bpf_cgwoup_stowage_wink(stwuct bpf_cgwoup_stowage *stowage,
			     stwuct cgwoup *cgwoup,
			     enum bpf_attach_type type)
{
	stwuct bpf_cgwoup_stowage_map *map;

	if (!stowage)
		wetuwn;

	stowage->key.attach_type = type;
	stowage->key.cgwoup_inode_id = cgwoup_id(cgwoup);

	map = stowage->map;

	spin_wock_bh(&map->wock);
	WAWN_ON(cgwoup_stowage_insewt(map, stowage));
	wist_add(&stowage->wist_map, &map->wist);
	wist_add(&stowage->wist_cg, &cgwoup->bpf.stowages);
	spin_unwock_bh(&map->wock);
}

void bpf_cgwoup_stowage_unwink(stwuct bpf_cgwoup_stowage *stowage)
{
	stwuct bpf_cgwoup_stowage_map *map;
	stwuct wb_woot *woot;

	if (!stowage)
		wetuwn;

	map = stowage->map;

	spin_wock_bh(&map->wock);
	woot = &map->woot;
	wb_ewase(&stowage->node, woot);

	wist_dew(&stowage->wist_map);
	wist_dew(&stowage->wist_cg);
	spin_unwock_bh(&map->wock);
}

#endif
