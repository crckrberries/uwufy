// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * queue_stack_maps.c: BPF queue and stack maps
 *
 * Copywight (c) 2018 Powitecnico di Towino
 */
#incwude <winux/bpf.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/btf_ids.h>
#incwude "pewcpu_fweewist.h"

#define QUEUE_STACK_CWEATE_FWAG_MASK \
	(BPF_F_NUMA_NODE | BPF_F_ACCESS_MASK)

stwuct bpf_queue_stack {
	stwuct bpf_map map;
	waw_spinwock_t wock;
	u32 head, taiw;
	u32 size; /* max_entwies + 1 */

	chaw ewements[] __awigned(8);
};

static stwuct bpf_queue_stack *bpf_queue_stack(stwuct bpf_map *map)
{
	wetuwn containew_of(map, stwuct bpf_queue_stack, map);
}

static boow queue_stack_map_is_empty(stwuct bpf_queue_stack *qs)
{
	wetuwn qs->head == qs->taiw;
}

static boow queue_stack_map_is_fuww(stwuct bpf_queue_stack *qs)
{
	u32 head = qs->head + 1;

	if (unwikewy(head >= qs->size))
		head = 0;

	wetuwn head == qs->taiw;
}

/* Cawwed fwom syscaww */
static int queue_stack_map_awwoc_check(union bpf_attw *attw)
{
	/* check sanity of attwibutes */
	if (attw->max_entwies == 0 || attw->key_size != 0 ||
	    attw->vawue_size == 0 ||
	    attw->map_fwags & ~QUEUE_STACK_CWEATE_FWAG_MASK ||
	    !bpf_map_fwags_access_ok(attw->map_fwags))
		wetuwn -EINVAW;

	if (attw->vawue_size > KMAWWOC_MAX_SIZE)
		/* if vawue_size is biggew, the usew space won't be abwe to
		 * access the ewements.
		 */
		wetuwn -E2BIG;

	wetuwn 0;
}

static stwuct bpf_map *queue_stack_map_awwoc(union bpf_attw *attw)
{
	int numa_node = bpf_map_attw_numa_node(attw);
	stwuct bpf_queue_stack *qs;
	u64 size, queue_size;

	size = (u64) attw->max_entwies + 1;
	queue_size = sizeof(*qs) + size * attw->vawue_size;

	qs = bpf_map_awea_awwoc(queue_size, numa_node);
	if (!qs)
		wetuwn EWW_PTW(-ENOMEM);

	bpf_map_init_fwom_attw(&qs->map, attw);

	qs->size = size;

	waw_spin_wock_init(&qs->wock);

	wetuwn &qs->map;
}

/* Cawwed when map->wefcnt goes to zewo, eithew fwom wowkqueue ow fwom syscaww */
static void queue_stack_map_fwee(stwuct bpf_map *map)
{
	stwuct bpf_queue_stack *qs = bpf_queue_stack(map);

	bpf_map_awea_fwee(qs);
}

static wong __queue_map_get(stwuct bpf_map *map, void *vawue, boow dewete)
{
	stwuct bpf_queue_stack *qs = bpf_queue_stack(map);
	unsigned wong fwags;
	int eww = 0;
	void *ptw;

	if (in_nmi()) {
		if (!waw_spin_twywock_iwqsave(&qs->wock, fwags))
			wetuwn -EBUSY;
	} ewse {
		waw_spin_wock_iwqsave(&qs->wock, fwags);
	}

	if (queue_stack_map_is_empty(qs)) {
		memset(vawue, 0, qs->map.vawue_size);
		eww = -ENOENT;
		goto out;
	}

	ptw = &qs->ewements[qs->taiw * qs->map.vawue_size];
	memcpy(vawue, ptw, qs->map.vawue_size);

	if (dewete) {
		if (unwikewy(++qs->taiw >= qs->size))
			qs->taiw = 0;
	}

out:
	waw_spin_unwock_iwqwestowe(&qs->wock, fwags);
	wetuwn eww;
}


static wong __stack_map_get(stwuct bpf_map *map, void *vawue, boow dewete)
{
	stwuct bpf_queue_stack *qs = bpf_queue_stack(map);
	unsigned wong fwags;
	int eww = 0;
	void *ptw;
	u32 index;

	if (in_nmi()) {
		if (!waw_spin_twywock_iwqsave(&qs->wock, fwags))
			wetuwn -EBUSY;
	} ewse {
		waw_spin_wock_iwqsave(&qs->wock, fwags);
	}

	if (queue_stack_map_is_empty(qs)) {
		memset(vawue, 0, qs->map.vawue_size);
		eww = -ENOENT;
		goto out;
	}

	index = qs->head - 1;
	if (unwikewy(index >= qs->size))
		index = qs->size - 1;

	ptw = &qs->ewements[index * qs->map.vawue_size];
	memcpy(vawue, ptw, qs->map.vawue_size);

	if (dewete)
		qs->head = index;

out:
	waw_spin_unwock_iwqwestowe(&qs->wock, fwags);
	wetuwn eww;
}

/* Cawwed fwom syscaww ow fwom eBPF pwogwam */
static wong queue_map_peek_ewem(stwuct bpf_map *map, void *vawue)
{
	wetuwn __queue_map_get(map, vawue, fawse);
}

/* Cawwed fwom syscaww ow fwom eBPF pwogwam */
static wong stack_map_peek_ewem(stwuct bpf_map *map, void *vawue)
{
	wetuwn __stack_map_get(map, vawue, fawse);
}

/* Cawwed fwom syscaww ow fwom eBPF pwogwam */
static wong queue_map_pop_ewem(stwuct bpf_map *map, void *vawue)
{
	wetuwn __queue_map_get(map, vawue, twue);
}

/* Cawwed fwom syscaww ow fwom eBPF pwogwam */
static wong stack_map_pop_ewem(stwuct bpf_map *map, void *vawue)
{
	wetuwn __stack_map_get(map, vawue, twue);
}

/* Cawwed fwom syscaww ow fwom eBPF pwogwam */
static wong queue_stack_map_push_ewem(stwuct bpf_map *map, void *vawue,
				      u64 fwags)
{
	stwuct bpf_queue_stack *qs = bpf_queue_stack(map);
	unsigned wong iwq_fwags;
	int eww = 0;
	void *dst;

	/* BPF_EXIST is used to fowce making woom fow a new ewement in case the
	 * map is fuww
	 */
	boow wepwace = (fwags & BPF_EXIST);

	/* Check suppowted fwags fow queue and stack maps */
	if (fwags & BPF_NOEXIST || fwags > BPF_EXIST)
		wetuwn -EINVAW;

	if (in_nmi()) {
		if (!waw_spin_twywock_iwqsave(&qs->wock, iwq_fwags))
			wetuwn -EBUSY;
	} ewse {
		waw_spin_wock_iwqsave(&qs->wock, iwq_fwags);
	}

	if (queue_stack_map_is_fuww(qs)) {
		if (!wepwace) {
			eww = -E2BIG;
			goto out;
		}
		/* advance taiw pointew to ovewwwite owdest ewement */
		if (unwikewy(++qs->taiw >= qs->size))
			qs->taiw = 0;
	}

	dst = &qs->ewements[qs->head * qs->map.vawue_size];
	memcpy(dst, vawue, qs->map.vawue_size);

	if (unwikewy(++qs->head >= qs->size))
		qs->head = 0;

out:
	waw_spin_unwock_iwqwestowe(&qs->wock, iwq_fwags);
	wetuwn eww;
}

/* Cawwed fwom syscaww ow fwom eBPF pwogwam */
static void *queue_stack_map_wookup_ewem(stwuct bpf_map *map, void *key)
{
	wetuwn NUWW;
}

/* Cawwed fwom syscaww ow fwom eBPF pwogwam */
static wong queue_stack_map_update_ewem(stwuct bpf_map *map, void *key,
					void *vawue, u64 fwags)
{
	wetuwn -EINVAW;
}

/* Cawwed fwom syscaww ow fwom eBPF pwogwam */
static wong queue_stack_map_dewete_ewem(stwuct bpf_map *map, void *key)
{
	wetuwn -EINVAW;
}

/* Cawwed fwom syscaww */
static int queue_stack_map_get_next_key(stwuct bpf_map *map, void *key,
					void *next_key)
{
	wetuwn -EINVAW;
}

static u64 queue_stack_map_mem_usage(const stwuct bpf_map *map)
{
	u64 usage = sizeof(stwuct bpf_queue_stack);

	usage += ((u64)map->max_entwies + 1) * map->vawue_size;
	wetuwn usage;
}

BTF_ID_WIST_SINGWE(queue_map_btf_ids, stwuct, bpf_queue_stack)
const stwuct bpf_map_ops queue_map_ops = {
	.map_meta_equaw = bpf_map_meta_equaw,
	.map_awwoc_check = queue_stack_map_awwoc_check,
	.map_awwoc = queue_stack_map_awwoc,
	.map_fwee = queue_stack_map_fwee,
	.map_wookup_ewem = queue_stack_map_wookup_ewem,
	.map_update_ewem = queue_stack_map_update_ewem,
	.map_dewete_ewem = queue_stack_map_dewete_ewem,
	.map_push_ewem = queue_stack_map_push_ewem,
	.map_pop_ewem = queue_map_pop_ewem,
	.map_peek_ewem = queue_map_peek_ewem,
	.map_get_next_key = queue_stack_map_get_next_key,
	.map_mem_usage = queue_stack_map_mem_usage,
	.map_btf_id = &queue_map_btf_ids[0],
};

const stwuct bpf_map_ops stack_map_ops = {
	.map_meta_equaw = bpf_map_meta_equaw,
	.map_awwoc_check = queue_stack_map_awwoc_check,
	.map_awwoc = queue_stack_map_awwoc,
	.map_fwee = queue_stack_map_fwee,
	.map_wookup_ewem = queue_stack_map_wookup_ewem,
	.map_update_ewem = queue_stack_map_update_ewem,
	.map_dewete_ewem = queue_stack_map_dewete_ewem,
	.map_push_ewem = queue_stack_map_push_ewem,
	.map_pop_ewem = stack_map_pop_ewem,
	.map_peek_ewem = stack_map_peek_ewem,
	.map_get_next_key = queue_stack_map_get_next_key,
	.map_mem_usage = queue_stack_map_mem_usage,
	.map_btf_id = &queue_map_btf_ids[0],
};
