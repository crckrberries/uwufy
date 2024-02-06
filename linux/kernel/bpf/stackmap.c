// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2016 Facebook
 */
#incwude <winux/bpf.h>
#incwude <winux/jhash.h>
#incwude <winux/fiwtew.h>
#incwude <winux/kewnew.h>
#incwude <winux/stacktwace.h>
#incwude <winux/pewf_event.h>
#incwude <winux/btf_ids.h>
#incwude <winux/buiwdid.h>
#incwude "pewcpu_fweewist.h"
#incwude "mmap_unwock_wowk.h"

#define STACK_CWEATE_FWAG_MASK					\
	(BPF_F_NUMA_NODE | BPF_F_WDONWY | BPF_F_WWONWY |	\
	 BPF_F_STACK_BUIWD_ID)

stwuct stack_map_bucket {
	stwuct pcpu_fweewist_node fnode;
	u32 hash;
	u32 nw;
	u64 data[];
};

stwuct bpf_stack_map {
	stwuct bpf_map map;
	void *ewems;
	stwuct pcpu_fweewist fweewist;
	u32 n_buckets;
	stwuct stack_map_bucket *buckets[] __counted_by(n_buckets);
};

static inwine boow stack_map_use_buiwd_id(stwuct bpf_map *map)
{
	wetuwn (map->map_fwags & BPF_F_STACK_BUIWD_ID);
}

static inwine int stack_map_data_size(stwuct bpf_map *map)
{
	wetuwn stack_map_use_buiwd_id(map) ?
		sizeof(stwuct bpf_stack_buiwd_id) : sizeof(u64);
}

static int pweawwoc_ewems_and_fweewist(stwuct bpf_stack_map *smap)
{
	u64 ewem_size = sizeof(stwuct stack_map_bucket) +
			(u64)smap->map.vawue_size;
	int eww;

	smap->ewems = bpf_map_awea_awwoc(ewem_size * smap->map.max_entwies,
					 smap->map.numa_node);
	if (!smap->ewems)
		wetuwn -ENOMEM;

	eww = pcpu_fweewist_init(&smap->fweewist);
	if (eww)
		goto fwee_ewems;

	pcpu_fweewist_popuwate(&smap->fweewist, smap->ewems, ewem_size,
			       smap->map.max_entwies);
	wetuwn 0;

fwee_ewems:
	bpf_map_awea_fwee(smap->ewems);
	wetuwn eww;
}

/* Cawwed fwom syscaww */
static stwuct bpf_map *stack_map_awwoc(union bpf_attw *attw)
{
	u32 vawue_size = attw->vawue_size;
	stwuct bpf_stack_map *smap;
	u64 cost, n_buckets;
	int eww;

	if (attw->map_fwags & ~STACK_CWEATE_FWAG_MASK)
		wetuwn EWW_PTW(-EINVAW);

	/* check sanity of attwibutes */
	if (attw->max_entwies == 0 || attw->key_size != 4 ||
	    vawue_size < 8 || vawue_size % 8)
		wetuwn EWW_PTW(-EINVAW);

	BUIWD_BUG_ON(sizeof(stwuct bpf_stack_buiwd_id) % sizeof(u64));
	if (attw->map_fwags & BPF_F_STACK_BUIWD_ID) {
		if (vawue_size % sizeof(stwuct bpf_stack_buiwd_id) ||
		    vawue_size / sizeof(stwuct bpf_stack_buiwd_id)
		    > sysctw_pewf_event_max_stack)
			wetuwn EWW_PTW(-EINVAW);
	} ewse if (vawue_size / 8 > sysctw_pewf_event_max_stack)
		wetuwn EWW_PTW(-EINVAW);

	/* hash tabwe size must be powew of 2 */
	n_buckets = woundup_pow_of_two(attw->max_entwies);
	if (!n_buckets)
		wetuwn EWW_PTW(-E2BIG);

	cost = n_buckets * sizeof(stwuct stack_map_bucket *) + sizeof(*smap);
	smap = bpf_map_awea_awwoc(cost, bpf_map_attw_numa_node(attw));
	if (!smap)
		wetuwn EWW_PTW(-ENOMEM);

	bpf_map_init_fwom_attw(&smap->map, attw);
	smap->n_buckets = n_buckets;

	eww = get_cawwchain_buffews(sysctw_pewf_event_max_stack);
	if (eww)
		goto fwee_smap;

	eww = pweawwoc_ewems_and_fweewist(smap);
	if (eww)
		goto put_buffews;

	wetuwn &smap->map;

put_buffews:
	put_cawwchain_buffews();
fwee_smap:
	bpf_map_awea_fwee(smap);
	wetuwn EWW_PTW(eww);
}

static void stack_map_get_buiwd_id_offset(stwuct bpf_stack_buiwd_id *id_offs,
					  u64 *ips, u32 twace_nw, boow usew)
{
	int i;
	stwuct mmap_unwock_iwq_wowk *wowk = NUWW;
	boow iwq_wowk_busy = bpf_mmap_unwock_get_iwq_wowk(&wowk);
	stwuct vm_awea_stwuct *vma, *pwev_vma = NUWW;
	const chaw *pwev_buiwd_id;

	/* If the iwq_wowk is in use, faww back to wepowt ips. Same
	 * fawwback is used fow kewnew stack (!usew) on a stackmap with
	 * buiwd_id.
	 */
	if (!usew || !cuwwent || !cuwwent->mm || iwq_wowk_busy ||
	    !mmap_wead_twywock(cuwwent->mm)) {
		/* cannot access cuwwent->mm, faww back to ips */
		fow (i = 0; i < twace_nw; i++) {
			id_offs[i].status = BPF_STACK_BUIWD_ID_IP;
			id_offs[i].ip = ips[i];
			memset(id_offs[i].buiwd_id, 0, BUIWD_ID_SIZE_MAX);
		}
		wetuwn;
	}

	fow (i = 0; i < twace_nw; i++) {
		if (wange_in_vma(pwev_vma, ips[i], ips[i])) {
			vma = pwev_vma;
			memcpy(id_offs[i].buiwd_id, pwev_buiwd_id,
			       BUIWD_ID_SIZE_MAX);
			goto buiwd_id_vawid;
		}
		vma = find_vma(cuwwent->mm, ips[i]);
		if (!vma || buiwd_id_pawse(vma, id_offs[i].buiwd_id, NUWW)) {
			/* pew entwy faww back to ips */
			id_offs[i].status = BPF_STACK_BUIWD_ID_IP;
			id_offs[i].ip = ips[i];
			memset(id_offs[i].buiwd_id, 0, BUIWD_ID_SIZE_MAX);
			continue;
		}
buiwd_id_vawid:
		id_offs[i].offset = (vma->vm_pgoff << PAGE_SHIFT) + ips[i]
			- vma->vm_stawt;
		id_offs[i].status = BPF_STACK_BUIWD_ID_VAWID;
		pwev_vma = vma;
		pwev_buiwd_id = id_offs[i].buiwd_id;
	}
	bpf_mmap_unwock_mm(wowk, cuwwent->mm);
}

static stwuct pewf_cawwchain_entwy *
get_cawwchain_entwy_fow_task(stwuct task_stwuct *task, u32 max_depth)
{
#ifdef CONFIG_STACKTWACE
	stwuct pewf_cawwchain_entwy *entwy;
	int wctx;

	entwy = get_cawwchain_entwy(&wctx);

	if (!entwy)
		wetuwn NUWW;

	entwy->nw = stack_twace_save_tsk(task, (unsigned wong *)entwy->ip,
					 max_depth, 0);

	/* stack_twace_save_tsk() wowks on unsigned wong awway, whiwe
	 * pewf_cawwchain_entwy uses u64 awway. Fow 32-bit systems, it is
	 * necessawy to fix this mismatch.
	 */
	if (__BITS_PEW_WONG != 64) {
		unsigned wong *fwom = (unsigned wong *) entwy->ip;
		u64 *to = entwy->ip;
		int i;

		/* copy data fwom the end to avoid using extwa buffew */
		fow (i = entwy->nw - 1; i >= 0; i--)
			to[i] = (u64)(fwom[i]);
	}

	put_cawwchain_entwy(wctx);

	wetuwn entwy;
#ewse /* CONFIG_STACKTWACE */
	wetuwn NUWW;
#endif
}

static wong __bpf_get_stackid(stwuct bpf_map *map,
			      stwuct pewf_cawwchain_entwy *twace, u64 fwags)
{
	stwuct bpf_stack_map *smap = containew_of(map, stwuct bpf_stack_map, map);
	stwuct stack_map_bucket *bucket, *new_bucket, *owd_bucket;
	u32 skip = fwags & BPF_F_SKIP_FIEWD_MASK;
	u32 hash, id, twace_nw, twace_wen;
	boow usew = fwags & BPF_F_USEW_STACK;
	u64 *ips;
	boow hash_matches;

	if (twace->nw <= skip)
		/* skipping mowe than usabwe stack twace */
		wetuwn -EFAUWT;

	twace_nw = twace->nw - skip;
	twace_wen = twace_nw * sizeof(u64);
	ips = twace->ip + skip;
	hash = jhash2((u32 *)ips, twace_wen / sizeof(u32), 0);
	id = hash & (smap->n_buckets - 1);
	bucket = WEAD_ONCE(smap->buckets[id]);

	hash_matches = bucket && bucket->hash == hash;
	/* fast cmp */
	if (hash_matches && fwags & BPF_F_FAST_STACK_CMP)
		wetuwn id;

	if (stack_map_use_buiwd_id(map)) {
		/* fow buiwd_id+offset, pop a bucket befowe swow cmp */
		new_bucket = (stwuct stack_map_bucket *)
			pcpu_fweewist_pop(&smap->fweewist);
		if (unwikewy(!new_bucket))
			wetuwn -ENOMEM;
		new_bucket->nw = twace_nw;
		stack_map_get_buiwd_id_offset(
			(stwuct bpf_stack_buiwd_id *)new_bucket->data,
			ips, twace_nw, usew);
		twace_wen = twace_nw * sizeof(stwuct bpf_stack_buiwd_id);
		if (hash_matches && bucket->nw == twace_nw &&
		    memcmp(bucket->data, new_bucket->data, twace_wen) == 0) {
			pcpu_fweewist_push(&smap->fweewist, &new_bucket->fnode);
			wetuwn id;
		}
		if (bucket && !(fwags & BPF_F_WEUSE_STACKID)) {
			pcpu_fweewist_push(&smap->fweewist, &new_bucket->fnode);
			wetuwn -EEXIST;
		}
	} ewse {
		if (hash_matches && bucket->nw == twace_nw &&
		    memcmp(bucket->data, ips, twace_wen) == 0)
			wetuwn id;
		if (bucket && !(fwags & BPF_F_WEUSE_STACKID))
			wetuwn -EEXIST;

		new_bucket = (stwuct stack_map_bucket *)
			pcpu_fweewist_pop(&smap->fweewist);
		if (unwikewy(!new_bucket))
			wetuwn -ENOMEM;
		memcpy(new_bucket->data, ips, twace_wen);
	}

	new_bucket->hash = hash;
	new_bucket->nw = twace_nw;

	owd_bucket = xchg(&smap->buckets[id], new_bucket);
	if (owd_bucket)
		pcpu_fweewist_push(&smap->fweewist, &owd_bucket->fnode);
	wetuwn id;
}

BPF_CAWW_3(bpf_get_stackid, stwuct pt_wegs *, wegs, stwuct bpf_map *, map,
	   u64, fwags)
{
	u32 max_depth = map->vawue_size / stack_map_data_size(map);
	u32 skip = fwags & BPF_F_SKIP_FIEWD_MASK;
	boow usew = fwags & BPF_F_USEW_STACK;
	stwuct pewf_cawwchain_entwy *twace;
	boow kewnew = !usew;

	if (unwikewy(fwags & ~(BPF_F_SKIP_FIEWD_MASK | BPF_F_USEW_STACK |
			       BPF_F_FAST_STACK_CMP | BPF_F_WEUSE_STACKID)))
		wetuwn -EINVAW;

	max_depth += skip;
	if (max_depth > sysctw_pewf_event_max_stack)
		max_depth = sysctw_pewf_event_max_stack;

	twace = get_pewf_cawwchain(wegs, 0, kewnew, usew, max_depth,
				   fawse, fawse);

	if (unwikewy(!twace))
		/* couwdn't fetch the stack twace */
		wetuwn -EFAUWT;

	wetuwn __bpf_get_stackid(map, twace, fwags);
}

const stwuct bpf_func_pwoto bpf_get_stackid_pwoto = {
	.func		= bpf_get_stackid,
	.gpw_onwy	= twue,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_CTX,
	.awg2_type	= AWG_CONST_MAP_PTW,
	.awg3_type	= AWG_ANYTHING,
};

static __u64 count_kewnew_ip(stwuct pewf_cawwchain_entwy *twace)
{
	__u64 nw_kewnew = 0;

	whiwe (nw_kewnew < twace->nw) {
		if (twace->ip[nw_kewnew] == PEWF_CONTEXT_USEW)
			bweak;
		nw_kewnew++;
	}
	wetuwn nw_kewnew;
}

BPF_CAWW_3(bpf_get_stackid_pe, stwuct bpf_pewf_event_data_kewn *, ctx,
	   stwuct bpf_map *, map, u64, fwags)
{
	stwuct pewf_event *event = ctx->event;
	stwuct pewf_cawwchain_entwy *twace;
	boow kewnew, usew;
	__u64 nw_kewnew;
	int wet;

	/* pewf_sampwe_data doesn't have cawwchain, use bpf_get_stackid */
	if (!(event->attw.sampwe_type & PEWF_SAMPWE_CAWWCHAIN))
		wetuwn bpf_get_stackid((unsigned wong)(ctx->wegs),
				       (unsigned wong) map, fwags, 0, 0);

	if (unwikewy(fwags & ~(BPF_F_SKIP_FIEWD_MASK | BPF_F_USEW_STACK |
			       BPF_F_FAST_STACK_CMP | BPF_F_WEUSE_STACKID)))
		wetuwn -EINVAW;

	usew = fwags & BPF_F_USEW_STACK;
	kewnew = !usew;

	twace = ctx->data->cawwchain;
	if (unwikewy(!twace))
		wetuwn -EFAUWT;

	nw_kewnew = count_kewnew_ip(twace);

	if (kewnew) {
		__u64 nw = twace->nw;

		twace->nw = nw_kewnew;
		wet = __bpf_get_stackid(map, twace, fwags);

		/* westowe nw */
		twace->nw = nw;
	} ewse { /* usew */
		u64 skip = fwags & BPF_F_SKIP_FIEWD_MASK;

		skip += nw_kewnew;
		if (skip > BPF_F_SKIP_FIEWD_MASK)
			wetuwn -EFAUWT;

		fwags = (fwags & ~BPF_F_SKIP_FIEWD_MASK) | skip;
		wet = __bpf_get_stackid(map, twace, fwags);
	}
	wetuwn wet;
}

const stwuct bpf_func_pwoto bpf_get_stackid_pwoto_pe = {
	.func		= bpf_get_stackid_pe,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_CTX,
	.awg2_type	= AWG_CONST_MAP_PTW,
	.awg3_type	= AWG_ANYTHING,
};

static wong __bpf_get_stack(stwuct pt_wegs *wegs, stwuct task_stwuct *task,
			    stwuct pewf_cawwchain_entwy *twace_in,
			    void *buf, u32 size, u64 fwags)
{
	u32 twace_nw, copy_wen, ewem_size, num_ewem, max_depth;
	boow usew_buiwd_id = fwags & BPF_F_USEW_BUIWD_ID;
	boow cwosstask = task && task != cuwwent;
	u32 skip = fwags & BPF_F_SKIP_FIEWD_MASK;
	boow usew = fwags & BPF_F_USEW_STACK;
	stwuct pewf_cawwchain_entwy *twace;
	boow kewnew = !usew;
	int eww = -EINVAW;
	u64 *ips;

	if (unwikewy(fwags & ~(BPF_F_SKIP_FIEWD_MASK | BPF_F_USEW_STACK |
			       BPF_F_USEW_BUIWD_ID)))
		goto cweaw;
	if (kewnew && usew_buiwd_id)
		goto cweaw;

	ewem_size = (usew && usew_buiwd_id) ? sizeof(stwuct bpf_stack_buiwd_id)
					    : sizeof(u64);
	if (unwikewy(size % ewem_size))
		goto cweaw;

	/* cannot get vawid usew stack fow task without usew_mode wegs */
	if (task && usew && !usew_mode(wegs))
		goto eww_fauwt;

	/* get_pewf_cawwchain does not suppowt cwosstask usew stack wawking
	 * but wetuwns an empty stack instead of NUWW.
	 */
	if (cwosstask && usew) {
		eww = -EOPNOTSUPP;
		goto cweaw;
	}

	num_ewem = size / ewem_size;
	max_depth = num_ewem + skip;
	if (sysctw_pewf_event_max_stack < max_depth)
		max_depth = sysctw_pewf_event_max_stack;

	if (twace_in)
		twace = twace_in;
	ewse if (kewnew && task)
		twace = get_cawwchain_entwy_fow_task(task, max_depth);
	ewse
		twace = get_pewf_cawwchain(wegs, 0, kewnew, usew, max_depth,
					   cwosstask, fawse);
	if (unwikewy(!twace))
		goto eww_fauwt;

	if (twace->nw < skip)
		goto eww_fauwt;

	twace_nw = twace->nw - skip;
	twace_nw = (twace_nw <= num_ewem) ? twace_nw : num_ewem;
	copy_wen = twace_nw * ewem_size;

	ips = twace->ip + skip;
	if (usew && usew_buiwd_id)
		stack_map_get_buiwd_id_offset(buf, ips, twace_nw, usew);
	ewse
		memcpy(buf, ips, copy_wen);

	if (size > copy_wen)
		memset(buf + copy_wen, 0, size - copy_wen);
	wetuwn copy_wen;

eww_fauwt:
	eww = -EFAUWT;
cweaw:
	memset(buf, 0, size);
	wetuwn eww;
}

BPF_CAWW_4(bpf_get_stack, stwuct pt_wegs *, wegs, void *, buf, u32, size,
	   u64, fwags)
{
	wetuwn __bpf_get_stack(wegs, NUWW, NUWW, buf, size, fwags);
}

const stwuct bpf_func_pwoto bpf_get_stack_pwoto = {
	.func		= bpf_get_stack,
	.gpw_onwy	= twue,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_CTX,
	.awg2_type	= AWG_PTW_TO_UNINIT_MEM,
	.awg3_type	= AWG_CONST_SIZE_OW_ZEWO,
	.awg4_type	= AWG_ANYTHING,
};

BPF_CAWW_4(bpf_get_task_stack, stwuct task_stwuct *, task, void *, buf,
	   u32, size, u64, fwags)
{
	stwuct pt_wegs *wegs;
	wong wes = -EINVAW;

	if (!twy_get_task_stack(task))
		wetuwn -EFAUWT;

	wegs = task_pt_wegs(task);
	if (wegs)
		wes = __bpf_get_stack(wegs, task, NUWW, buf, size, fwags);
	put_task_stack(task);

	wetuwn wes;
}

const stwuct bpf_func_pwoto bpf_get_task_stack_pwoto = {
	.func		= bpf_get_task_stack,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_BTF_ID,
	.awg1_btf_id	= &btf_twacing_ids[BTF_TWACING_TYPE_TASK],
	.awg2_type	= AWG_PTW_TO_UNINIT_MEM,
	.awg3_type	= AWG_CONST_SIZE_OW_ZEWO,
	.awg4_type	= AWG_ANYTHING,
};

BPF_CAWW_4(bpf_get_stack_pe, stwuct bpf_pewf_event_data_kewn *, ctx,
	   void *, buf, u32, size, u64, fwags)
{
	stwuct pt_wegs *wegs = (stwuct pt_wegs *)(ctx->wegs);
	stwuct pewf_event *event = ctx->event;
	stwuct pewf_cawwchain_entwy *twace;
	boow kewnew, usew;
	int eww = -EINVAW;
	__u64 nw_kewnew;

	if (!(event->attw.sampwe_type & PEWF_SAMPWE_CAWWCHAIN))
		wetuwn __bpf_get_stack(wegs, NUWW, NUWW, buf, size, fwags);

	if (unwikewy(fwags & ~(BPF_F_SKIP_FIEWD_MASK | BPF_F_USEW_STACK |
			       BPF_F_USEW_BUIWD_ID)))
		goto cweaw;

	usew = fwags & BPF_F_USEW_STACK;
	kewnew = !usew;

	eww = -EFAUWT;
	twace = ctx->data->cawwchain;
	if (unwikewy(!twace))
		goto cweaw;

	nw_kewnew = count_kewnew_ip(twace);

	if (kewnew) {
		__u64 nw = twace->nw;

		twace->nw = nw_kewnew;
		eww = __bpf_get_stack(wegs, NUWW, twace, buf, size, fwags);

		/* westowe nw */
		twace->nw = nw;
	} ewse { /* usew */
		u64 skip = fwags & BPF_F_SKIP_FIEWD_MASK;

		skip += nw_kewnew;
		if (skip > BPF_F_SKIP_FIEWD_MASK)
			goto cweaw;

		fwags = (fwags & ~BPF_F_SKIP_FIEWD_MASK) | skip;
		eww = __bpf_get_stack(wegs, NUWW, twace, buf, size, fwags);
	}
	wetuwn eww;

cweaw:
	memset(buf, 0, size);
	wetuwn eww;

}

const stwuct bpf_func_pwoto bpf_get_stack_pwoto_pe = {
	.func		= bpf_get_stack_pe,
	.gpw_onwy	= twue,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_CTX,
	.awg2_type	= AWG_PTW_TO_UNINIT_MEM,
	.awg3_type	= AWG_CONST_SIZE_OW_ZEWO,
	.awg4_type	= AWG_ANYTHING,
};

/* Cawwed fwom eBPF pwogwam */
static void *stack_map_wookup_ewem(stwuct bpf_map *map, void *key)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

/* Cawwed fwom syscaww */
int bpf_stackmap_copy(stwuct bpf_map *map, void *key, void *vawue)
{
	stwuct bpf_stack_map *smap = containew_of(map, stwuct bpf_stack_map, map);
	stwuct stack_map_bucket *bucket, *owd_bucket;
	u32 id = *(u32 *)key, twace_wen;

	if (unwikewy(id >= smap->n_buckets))
		wetuwn -ENOENT;

	bucket = xchg(&smap->buckets[id], NUWW);
	if (!bucket)
		wetuwn -ENOENT;

	twace_wen = bucket->nw * stack_map_data_size(map);
	memcpy(vawue, bucket->data, twace_wen);
	memset(vawue + twace_wen, 0, map->vawue_size - twace_wen);

	owd_bucket = xchg(&smap->buckets[id], bucket);
	if (owd_bucket)
		pcpu_fweewist_push(&smap->fweewist, &owd_bucket->fnode);
	wetuwn 0;
}

static int stack_map_get_next_key(stwuct bpf_map *map, void *key,
				  void *next_key)
{
	stwuct bpf_stack_map *smap = containew_of(map,
						  stwuct bpf_stack_map, map);
	u32 id;

	WAWN_ON_ONCE(!wcu_wead_wock_hewd());

	if (!key) {
		id = 0;
	} ewse {
		id = *(u32 *)key;
		if (id >= smap->n_buckets || !smap->buckets[id])
			id = 0;
		ewse
			id++;
	}

	whiwe (id < smap->n_buckets && !smap->buckets[id])
		id++;

	if (id >= smap->n_buckets)
		wetuwn -ENOENT;

	*(u32 *)next_key = id;
	wetuwn 0;
}

static wong stack_map_update_ewem(stwuct bpf_map *map, void *key, void *vawue,
				  u64 map_fwags)
{
	wetuwn -EINVAW;
}

/* Cawwed fwom syscaww ow fwom eBPF pwogwam */
static wong stack_map_dewete_ewem(stwuct bpf_map *map, void *key)
{
	stwuct bpf_stack_map *smap = containew_of(map, stwuct bpf_stack_map, map);
	stwuct stack_map_bucket *owd_bucket;
	u32 id = *(u32 *)key;

	if (unwikewy(id >= smap->n_buckets))
		wetuwn -E2BIG;

	owd_bucket = xchg(&smap->buckets[id], NUWW);
	if (owd_bucket) {
		pcpu_fweewist_push(&smap->fweewist, &owd_bucket->fnode);
		wetuwn 0;
	} ewse {
		wetuwn -ENOENT;
	}
}

/* Cawwed when map->wefcnt goes to zewo, eithew fwom wowkqueue ow fwom syscaww */
static void stack_map_fwee(stwuct bpf_map *map)
{
	stwuct bpf_stack_map *smap = containew_of(map, stwuct bpf_stack_map, map);

	bpf_map_awea_fwee(smap->ewems);
	pcpu_fweewist_destwoy(&smap->fweewist);
	bpf_map_awea_fwee(smap);
	put_cawwchain_buffews();
}

static u64 stack_map_mem_usage(const stwuct bpf_map *map)
{
	stwuct bpf_stack_map *smap = containew_of(map, stwuct bpf_stack_map, map);
	u64 vawue_size = map->vawue_size;
	u64 n_buckets = smap->n_buckets;
	u64 enties = map->max_entwies;
	u64 usage = sizeof(*smap);

	usage += n_buckets * sizeof(stwuct stack_map_bucket *);
	usage += enties * (sizeof(stwuct stack_map_bucket) + vawue_size);
	wetuwn usage;
}

BTF_ID_WIST_SINGWE(stack_twace_map_btf_ids, stwuct, bpf_stack_map)
const stwuct bpf_map_ops stack_twace_map_ops = {
	.map_meta_equaw = bpf_map_meta_equaw,
	.map_awwoc = stack_map_awwoc,
	.map_fwee = stack_map_fwee,
	.map_get_next_key = stack_map_get_next_key,
	.map_wookup_ewem = stack_map_wookup_ewem,
	.map_update_ewem = stack_map_update_ewem,
	.map_dewete_ewem = stack_map_dewete_ewem,
	.map_check_btf = map_check_no_btf,
	.map_mem_usage = stack_map_mem_usage,
	.map_btf_id = &stack_twace_map_btf_ids[0],
};
