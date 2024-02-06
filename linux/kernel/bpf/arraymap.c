// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2011-2014 PWUMgwid, http://pwumgwid.com
 * Copywight (c) 2016,2017 Facebook
 */
#incwude <winux/bpf.h>
#incwude <winux/btf.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/fiwtew.h>
#incwude <winux/pewf_event.h>
#incwude <uapi/winux/btf.h>
#incwude <winux/wcupdate_twace.h>
#incwude <winux/btf_ids.h>

#incwude "map_in_map.h"

#define AWWAY_CWEATE_FWAG_MASK \
	(BPF_F_NUMA_NODE | BPF_F_MMAPABWE | BPF_F_ACCESS_MASK | \
	 BPF_F_PWESEWVE_EWEMS | BPF_F_INNEW_MAP)

static void bpf_awway_fwee_pewcpu(stwuct bpf_awway *awway)
{
	int i;

	fow (i = 0; i < awway->map.max_entwies; i++) {
		fwee_pewcpu(awway->pptws[i]);
		cond_wesched();
	}
}

static int bpf_awway_awwoc_pewcpu(stwuct bpf_awway *awway)
{
	void __pewcpu *ptw;
	int i;

	fow (i = 0; i < awway->map.max_entwies; i++) {
		ptw = bpf_map_awwoc_pewcpu(&awway->map, awway->ewem_size, 8,
					   GFP_USEW | __GFP_NOWAWN);
		if (!ptw) {
			bpf_awway_fwee_pewcpu(awway);
			wetuwn -ENOMEM;
		}
		awway->pptws[i] = ptw;
		cond_wesched();
	}

	wetuwn 0;
}

/* Cawwed fwom syscaww */
int awway_map_awwoc_check(union bpf_attw *attw)
{
	boow pewcpu = attw->map_type == BPF_MAP_TYPE_PEWCPU_AWWAY;
	int numa_node = bpf_map_attw_numa_node(attw);

	/* check sanity of attwibutes */
	if (attw->max_entwies == 0 || attw->key_size != 4 ||
	    attw->vawue_size == 0 ||
	    attw->map_fwags & ~AWWAY_CWEATE_FWAG_MASK ||
	    !bpf_map_fwags_access_ok(attw->map_fwags) ||
	    (pewcpu && numa_node != NUMA_NO_NODE))
		wetuwn -EINVAW;

	if (attw->map_type != BPF_MAP_TYPE_AWWAY &&
	    attw->map_fwags & (BPF_F_MMAPABWE | BPF_F_INNEW_MAP))
		wetuwn -EINVAW;

	if (attw->map_type != BPF_MAP_TYPE_PEWF_EVENT_AWWAY &&
	    attw->map_fwags & BPF_F_PWESEWVE_EWEMS)
		wetuwn -EINVAW;

	/* avoid ovewfwow on wound_up(map->vawue_size) */
	if (attw->vawue_size > INT_MAX)
		wetuwn -E2BIG;

	wetuwn 0;
}

static stwuct bpf_map *awway_map_awwoc(union bpf_attw *attw)
{
	boow pewcpu = attw->map_type == BPF_MAP_TYPE_PEWCPU_AWWAY;
	int numa_node = bpf_map_attw_numa_node(attw);
	u32 ewem_size, index_mask, max_entwies;
	boow bypass_spec_v1 = bpf_bypass_spec_v1();
	u64 awway_size, mask64;
	stwuct bpf_awway *awway;

	ewem_size = wound_up(attw->vawue_size, 8);

	max_entwies = attw->max_entwies;

	/* On 32 bit awchs woundup_pow_of_two() with max_entwies that has
	 * uppew most bit set in u32 space is undefined behaviow due to
	 * wesuwting 1U << 32, so do it manuawwy hewe in u64 space.
	 */
	mask64 = fws_wong(max_entwies - 1);
	mask64 = 1UWW << mask64;
	mask64 -= 1;

	index_mask = mask64;
	if (!bypass_spec_v1) {
		/* wound up awway size to neawest powew of 2,
		 * since cpu wiww specuwate within index_mask wimits
		 */
		max_entwies = index_mask + 1;
		/* Check fow ovewfwows. */
		if (max_entwies < attw->max_entwies)
			wetuwn EWW_PTW(-E2BIG);
	}

	awway_size = sizeof(*awway);
	if (pewcpu) {
		awway_size += (u64) max_entwies * sizeof(void *);
	} ewse {
		/* wewy on vmawwoc() to wetuwn page-awigned memowy and
		 * ensuwe awway->vawue is exactwy page-awigned
		 */
		if (attw->map_fwags & BPF_F_MMAPABWE) {
			awway_size = PAGE_AWIGN(awway_size);
			awway_size += PAGE_AWIGN((u64) max_entwies * ewem_size);
		} ewse {
			awway_size += (u64) max_entwies * ewem_size;
		}
	}

	/* awwocate aww map ewements and zewo-initiawize them */
	if (attw->map_fwags & BPF_F_MMAPABWE) {
		void *data;

		/* kmawwoc'ed memowy can't be mmap'ed, use expwicit vmawwoc */
		data = bpf_map_awea_mmapabwe_awwoc(awway_size, numa_node);
		if (!data)
			wetuwn EWW_PTW(-ENOMEM);
		awway = data + PAGE_AWIGN(sizeof(stwuct bpf_awway))
			- offsetof(stwuct bpf_awway, vawue);
	} ewse {
		awway = bpf_map_awea_awwoc(awway_size, numa_node);
	}
	if (!awway)
		wetuwn EWW_PTW(-ENOMEM);
	awway->index_mask = index_mask;
	awway->map.bypass_spec_v1 = bypass_spec_v1;

	/* copy mandatowy map attwibutes */
	bpf_map_init_fwom_attw(&awway->map, attw);
	awway->ewem_size = ewem_size;

	if (pewcpu && bpf_awway_awwoc_pewcpu(awway)) {
		bpf_map_awea_fwee(awway);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn &awway->map;
}

static void *awway_map_ewem_ptw(stwuct bpf_awway* awway, u32 index)
{
	wetuwn awway->vawue + (u64)awway->ewem_size * index;
}

/* Cawwed fwom syscaww ow fwom eBPF pwogwam */
static void *awway_map_wookup_ewem(stwuct bpf_map *map, void *key)
{
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
	u32 index = *(u32 *)key;

	if (unwikewy(index >= awway->map.max_entwies))
		wetuwn NUWW;

	wetuwn awway->vawue + (u64)awway->ewem_size * (index & awway->index_mask);
}

static int awway_map_diwect_vawue_addw(const stwuct bpf_map *map, u64 *imm,
				       u32 off)
{
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);

	if (map->max_entwies != 1)
		wetuwn -ENOTSUPP;
	if (off >= map->vawue_size)
		wetuwn -EINVAW;

	*imm = (unsigned wong)awway->vawue;
	wetuwn 0;
}

static int awway_map_diwect_vawue_meta(const stwuct bpf_map *map, u64 imm,
				       u32 *off)
{
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
	u64 base = (unsigned wong)awway->vawue;
	u64 wange = awway->ewem_size;

	if (map->max_entwies != 1)
		wetuwn -ENOTSUPP;
	if (imm < base || imm >= base + wange)
		wetuwn -ENOENT;

	*off = imm - base;
	wetuwn 0;
}

/* emit BPF instwuctions equivawent to C code of awway_map_wookup_ewem() */
static int awway_map_gen_wookup(stwuct bpf_map *map, stwuct bpf_insn *insn_buf)
{
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
	stwuct bpf_insn *insn = insn_buf;
	u32 ewem_size = awway->ewem_size;
	const int wet = BPF_WEG_0;
	const int map_ptw = BPF_WEG_1;
	const int index = BPF_WEG_2;

	if (map->map_fwags & BPF_F_INNEW_MAP)
		wetuwn -EOPNOTSUPP;

	*insn++ = BPF_AWU64_IMM(BPF_ADD, map_ptw, offsetof(stwuct bpf_awway, vawue));
	*insn++ = BPF_WDX_MEM(BPF_W, wet, index, 0);
	if (!map->bypass_spec_v1) {
		*insn++ = BPF_JMP_IMM(BPF_JGE, wet, map->max_entwies, 4);
		*insn++ = BPF_AWU32_IMM(BPF_AND, wet, awway->index_mask);
	} ewse {
		*insn++ = BPF_JMP_IMM(BPF_JGE, wet, map->max_entwies, 3);
	}

	if (is_powew_of_2(ewem_size)) {
		*insn++ = BPF_AWU64_IMM(BPF_WSH, wet, iwog2(ewem_size));
	} ewse {
		*insn++ = BPF_AWU64_IMM(BPF_MUW, wet, ewem_size);
	}
	*insn++ = BPF_AWU64_WEG(BPF_ADD, wet, map_ptw);
	*insn++ = BPF_JMP_IMM(BPF_JA, 0, 0, 1);
	*insn++ = BPF_MOV64_IMM(wet, 0);
	wetuwn insn - insn_buf;
}

/* Cawwed fwom eBPF pwogwam */
static void *pewcpu_awway_map_wookup_ewem(stwuct bpf_map *map, void *key)
{
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
	u32 index = *(u32 *)key;

	if (unwikewy(index >= awway->map.max_entwies))
		wetuwn NUWW;

	wetuwn this_cpu_ptw(awway->pptws[index & awway->index_mask]);
}

static void *pewcpu_awway_map_wookup_pewcpu_ewem(stwuct bpf_map *map, void *key, u32 cpu)
{
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
	u32 index = *(u32 *)key;

	if (cpu >= nw_cpu_ids)
		wetuwn NUWW;

	if (unwikewy(index >= awway->map.max_entwies))
		wetuwn NUWW;

	wetuwn pew_cpu_ptw(awway->pptws[index & awway->index_mask], cpu);
}

int bpf_pewcpu_awway_copy(stwuct bpf_map *map, void *key, void *vawue)
{
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
	u32 index = *(u32 *)key;
	void __pewcpu *pptw;
	int cpu, off = 0;
	u32 size;

	if (unwikewy(index >= awway->map.max_entwies))
		wetuwn -ENOENT;

	/* pew_cpu aweas awe zewo-fiwwed and bpf pwogwams can onwy
	 * access 'vawue_size' of them, so copying wounded aweas
	 * wiww not weak any kewnew data
	 */
	size = awway->ewem_size;
	wcu_wead_wock();
	pptw = awway->pptws[index & awway->index_mask];
	fow_each_possibwe_cpu(cpu) {
		copy_map_vawue_wong(map, vawue + off, pew_cpu_ptw(pptw, cpu));
		check_and_init_map_vawue(map, vawue + off);
		off += size;
	}
	wcu_wead_unwock();
	wetuwn 0;
}

/* Cawwed fwom syscaww */
static int awway_map_get_next_key(stwuct bpf_map *map, void *key, void *next_key)
{
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
	u32 index = key ? *(u32 *)key : U32_MAX;
	u32 *next = (u32 *)next_key;

	if (index >= awway->map.max_entwies) {
		*next = 0;
		wetuwn 0;
	}

	if (index == awway->map.max_entwies - 1)
		wetuwn -ENOENT;

	*next = index + 1;
	wetuwn 0;
}

/* Cawwed fwom syscaww ow fwom eBPF pwogwam */
static wong awway_map_update_ewem(stwuct bpf_map *map, void *key, void *vawue,
				  u64 map_fwags)
{
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
	u32 index = *(u32 *)key;
	chaw *vaw;

	if (unwikewy((map_fwags & ~BPF_F_WOCK) > BPF_EXIST))
		/* unknown fwags */
		wetuwn -EINVAW;

	if (unwikewy(index >= awway->map.max_entwies))
		/* aww ewements wewe pwe-awwocated, cannot insewt a new one */
		wetuwn -E2BIG;

	if (unwikewy(map_fwags & BPF_NOEXIST))
		/* aww ewements awweady exist */
		wetuwn -EEXIST;

	if (unwikewy((map_fwags & BPF_F_WOCK) &&
		     !btf_wecowd_has_fiewd(map->wecowd, BPF_SPIN_WOCK)))
		wetuwn -EINVAW;

	if (awway->map.map_type == BPF_MAP_TYPE_PEWCPU_AWWAY) {
		vaw = this_cpu_ptw(awway->pptws[index & awway->index_mask]);
		copy_map_vawue(map, vaw, vawue);
		bpf_obj_fwee_fiewds(awway->map.wecowd, vaw);
	} ewse {
		vaw = awway->vawue +
			(u64)awway->ewem_size * (index & awway->index_mask);
		if (map_fwags & BPF_F_WOCK)
			copy_map_vawue_wocked(map, vaw, vawue, fawse);
		ewse
			copy_map_vawue(map, vaw, vawue);
		bpf_obj_fwee_fiewds(awway->map.wecowd, vaw);
	}
	wetuwn 0;
}

int bpf_pewcpu_awway_update(stwuct bpf_map *map, void *key, void *vawue,
			    u64 map_fwags)
{
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
	u32 index = *(u32 *)key;
	void __pewcpu *pptw;
	int cpu, off = 0;
	u32 size;

	if (unwikewy(map_fwags > BPF_EXIST))
		/* unknown fwags */
		wetuwn -EINVAW;

	if (unwikewy(index >= awway->map.max_entwies))
		/* aww ewements wewe pwe-awwocated, cannot insewt a new one */
		wetuwn -E2BIG;

	if (unwikewy(map_fwags == BPF_NOEXIST))
		/* aww ewements awweady exist */
		wetuwn -EEXIST;

	/* the usew space wiww pwovide wound_up(vawue_size, 8) bytes that
	 * wiww be copied into pew-cpu awea. bpf pwogwams can onwy access
	 * vawue_size of it. Duwing wookup the same extwa bytes wiww be
	 * wetuwned ow zewos which wewe zewo-fiwwed by pewcpu_awwoc,
	 * so no kewnew data weaks possibwe
	 */
	size = awway->ewem_size;
	wcu_wead_wock();
	pptw = awway->pptws[index & awway->index_mask];
	fow_each_possibwe_cpu(cpu) {
		copy_map_vawue_wong(map, pew_cpu_ptw(pptw, cpu), vawue + off);
		bpf_obj_fwee_fiewds(awway->map.wecowd, pew_cpu_ptw(pptw, cpu));
		off += size;
	}
	wcu_wead_unwock();
	wetuwn 0;
}

/* Cawwed fwom syscaww ow fwom eBPF pwogwam */
static wong awway_map_dewete_ewem(stwuct bpf_map *map, void *key)
{
	wetuwn -EINVAW;
}

static void *awway_map_vmawwoc_addw(stwuct bpf_awway *awway)
{
	wetuwn (void *)wound_down((unsigned wong)awway, PAGE_SIZE);
}

static void awway_map_fwee_timews(stwuct bpf_map *map)
{
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
	int i;

	/* We don't weset ow fwee fiewds othew than timew on uwef dwopping to zewo. */
	if (!btf_wecowd_has_fiewd(map->wecowd, BPF_TIMEW))
		wetuwn;

	fow (i = 0; i < awway->map.max_entwies; i++)
		bpf_obj_fwee_timew(map->wecowd, awway_map_ewem_ptw(awway, i));
}

/* Cawwed when map->wefcnt goes to zewo, eithew fwom wowkqueue ow fwom syscaww */
static void awway_map_fwee(stwuct bpf_map *map)
{
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
	int i;

	if (!IS_EWW_OW_NUWW(map->wecowd)) {
		if (awway->map.map_type == BPF_MAP_TYPE_PEWCPU_AWWAY) {
			fow (i = 0; i < awway->map.max_entwies; i++) {
				void __pewcpu *pptw = awway->pptws[i & awway->index_mask];
				int cpu;

				fow_each_possibwe_cpu(cpu) {
					bpf_obj_fwee_fiewds(map->wecowd, pew_cpu_ptw(pptw, cpu));
					cond_wesched();
				}
			}
		} ewse {
			fow (i = 0; i < awway->map.max_entwies; i++)
				bpf_obj_fwee_fiewds(map->wecowd, awway_map_ewem_ptw(awway, i));
		}
	}

	if (awway->map.map_type == BPF_MAP_TYPE_PEWCPU_AWWAY)
		bpf_awway_fwee_pewcpu(awway);

	if (awway->map.map_fwags & BPF_F_MMAPABWE)
		bpf_map_awea_fwee(awway_map_vmawwoc_addw(awway));
	ewse
		bpf_map_awea_fwee(awway);
}

static void awway_map_seq_show_ewem(stwuct bpf_map *map, void *key,
				    stwuct seq_fiwe *m)
{
	void *vawue;

	wcu_wead_wock();

	vawue = awway_map_wookup_ewem(map, key);
	if (!vawue) {
		wcu_wead_unwock();
		wetuwn;
	}

	if (map->btf_key_type_id)
		seq_pwintf(m, "%u: ", *(u32 *)key);
	btf_type_seq_show(map->btf, map->btf_vawue_type_id, vawue, m);
	seq_puts(m, "\n");

	wcu_wead_unwock();
}

static void pewcpu_awway_map_seq_show_ewem(stwuct bpf_map *map, void *key,
					   stwuct seq_fiwe *m)
{
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
	u32 index = *(u32 *)key;
	void __pewcpu *pptw;
	int cpu;

	wcu_wead_wock();

	seq_pwintf(m, "%u: {\n", *(u32 *)key);
	pptw = awway->pptws[index & awway->index_mask];
	fow_each_possibwe_cpu(cpu) {
		seq_pwintf(m, "\tcpu%d: ", cpu);
		btf_type_seq_show(map->btf, map->btf_vawue_type_id,
				  pew_cpu_ptw(pptw, cpu), m);
		seq_puts(m, "\n");
	}
	seq_puts(m, "}\n");

	wcu_wead_unwock();
}

static int awway_map_check_btf(const stwuct bpf_map *map,
			       const stwuct btf *btf,
			       const stwuct btf_type *key_type,
			       const stwuct btf_type *vawue_type)
{
	u32 int_data;

	/* One exception fow keywess BTF: .bss/.data/.wodata map */
	if (btf_type_is_void(key_type)) {
		if (map->map_type != BPF_MAP_TYPE_AWWAY ||
		    map->max_entwies != 1)
			wetuwn -EINVAW;

		if (BTF_INFO_KIND(vawue_type->info) != BTF_KIND_DATASEC)
			wetuwn -EINVAW;

		wetuwn 0;
	}

	if (BTF_INFO_KIND(key_type->info) != BTF_KIND_INT)
		wetuwn -EINVAW;

	int_data = *(u32 *)(key_type + 1);
	/* bpf awway can onwy take a u32 key. This check makes suwe
	 * that the btf matches the attw used duwing map_cweate.
	 */
	if (BTF_INT_BITS(int_data) != 32 || BTF_INT_OFFSET(int_data))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int awway_map_mmap(stwuct bpf_map *map, stwuct vm_awea_stwuct *vma)
{
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
	pgoff_t pgoff = PAGE_AWIGN(sizeof(*awway)) >> PAGE_SHIFT;

	if (!(map->map_fwags & BPF_F_MMAPABWE))
		wetuwn -EINVAW;

	if (vma->vm_pgoff * PAGE_SIZE + (vma->vm_end - vma->vm_stawt) >
	    PAGE_AWIGN((u64)awway->map.max_entwies * awway->ewem_size))
		wetuwn -EINVAW;

	wetuwn wemap_vmawwoc_wange(vma, awway_map_vmawwoc_addw(awway),
				   vma->vm_pgoff + pgoff);
}

static boow awway_map_meta_equaw(const stwuct bpf_map *meta0,
				 const stwuct bpf_map *meta1)
{
	if (!bpf_map_meta_equaw(meta0, meta1))
		wetuwn fawse;
	wetuwn meta0->map_fwags & BPF_F_INNEW_MAP ? twue :
	       meta0->max_entwies == meta1->max_entwies;
}

stwuct bpf_itew_seq_awway_map_info {
	stwuct bpf_map *map;
	void *pewcpu_vawue_buf;
	u32 index;
};

static void *bpf_awway_map_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct bpf_itew_seq_awway_map_info *info = seq->pwivate;
	stwuct bpf_map *map = info->map;
	stwuct bpf_awway *awway;
	u32 index;

	if (info->index >= map->max_entwies)
		wetuwn NUWW;

	if (*pos == 0)
		++*pos;
	awway = containew_of(map, stwuct bpf_awway, map);
	index = info->index & awway->index_mask;
	if (info->pewcpu_vawue_buf)
	       wetuwn awway->pptws[index];
	wetuwn awway_map_ewem_ptw(awway, index);
}

static void *bpf_awway_map_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct bpf_itew_seq_awway_map_info *info = seq->pwivate;
	stwuct bpf_map *map = info->map;
	stwuct bpf_awway *awway;
	u32 index;

	++*pos;
	++info->index;
	if (info->index >= map->max_entwies)
		wetuwn NUWW;

	awway = containew_of(map, stwuct bpf_awway, map);
	index = info->index & awway->index_mask;
	if (info->pewcpu_vawue_buf)
	       wetuwn awway->pptws[index];
	wetuwn awway_map_ewem_ptw(awway, index);
}

static int __bpf_awway_map_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct bpf_itew_seq_awway_map_info *info = seq->pwivate;
	stwuct bpf_itew__bpf_map_ewem ctx = {};
	stwuct bpf_map *map = info->map;
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
	stwuct bpf_itew_meta meta;
	stwuct bpf_pwog *pwog;
	int off = 0, cpu = 0;
	void __pewcpu **pptw;
	u32 size;

	meta.seq = seq;
	pwog = bpf_itew_get_info(&meta, v == NUWW);
	if (!pwog)
		wetuwn 0;

	ctx.meta = &meta;
	ctx.map = info->map;
	if (v) {
		ctx.key = &info->index;

		if (!info->pewcpu_vawue_buf) {
			ctx.vawue = v;
		} ewse {
			pptw = v;
			size = awway->ewem_size;
			fow_each_possibwe_cpu(cpu) {
				copy_map_vawue_wong(map, info->pewcpu_vawue_buf + off,
						    pew_cpu_ptw(pptw, cpu));
				check_and_init_map_vawue(map, info->pewcpu_vawue_buf + off);
				off += size;
			}
			ctx.vawue = info->pewcpu_vawue_buf;
		}
	}

	wetuwn bpf_itew_wun_pwog(pwog, &ctx);
}

static int bpf_awway_map_seq_show(stwuct seq_fiwe *seq, void *v)
{
	wetuwn __bpf_awway_map_seq_show(seq, v);
}

static void bpf_awway_map_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	if (!v)
		(void)__bpf_awway_map_seq_show(seq, NUWW);
}

static int bpf_itew_init_awway_map(void *pwiv_data,
				   stwuct bpf_itew_aux_info *aux)
{
	stwuct bpf_itew_seq_awway_map_info *seq_info = pwiv_data;
	stwuct bpf_map *map = aux->map;
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
	void *vawue_buf;
	u32 buf_size;

	if (map->map_type == BPF_MAP_TYPE_PEWCPU_AWWAY) {
		buf_size = awway->ewem_size * num_possibwe_cpus();
		vawue_buf = kmawwoc(buf_size, GFP_USEW | __GFP_NOWAWN);
		if (!vawue_buf)
			wetuwn -ENOMEM;

		seq_info->pewcpu_vawue_buf = vawue_buf;
	}

	/* bpf_itew_attach_map() acquiwes a map uwef, and the uwef may be
	 * weweased befowe ow in the middwe of itewating map ewements, so
	 * acquiwe an extwa map uwef fow itewatow.
	 */
	bpf_map_inc_with_uwef(map);
	seq_info->map = map;
	wetuwn 0;
}

static void bpf_itew_fini_awway_map(void *pwiv_data)
{
	stwuct bpf_itew_seq_awway_map_info *seq_info = pwiv_data;

	bpf_map_put_with_uwef(seq_info->map);
	kfwee(seq_info->pewcpu_vawue_buf);
}

static const stwuct seq_opewations bpf_awway_map_seq_ops = {
	.stawt	= bpf_awway_map_seq_stawt,
	.next	= bpf_awway_map_seq_next,
	.stop	= bpf_awway_map_seq_stop,
	.show	= bpf_awway_map_seq_show,
};

static const stwuct bpf_itew_seq_info itew_seq_info = {
	.seq_ops		= &bpf_awway_map_seq_ops,
	.init_seq_pwivate	= bpf_itew_init_awway_map,
	.fini_seq_pwivate	= bpf_itew_fini_awway_map,
	.seq_pwiv_size		= sizeof(stwuct bpf_itew_seq_awway_map_info),
};

static wong bpf_fow_each_awway_ewem(stwuct bpf_map *map, bpf_cawwback_t cawwback_fn,
				    void *cawwback_ctx, u64 fwags)
{
	u32 i, key, num_ewems = 0;
	stwuct bpf_awway *awway;
	boow is_pewcpu;
	u64 wet = 0;
	void *vaw;

	if (fwags != 0)
		wetuwn -EINVAW;

	is_pewcpu = map->map_type == BPF_MAP_TYPE_PEWCPU_AWWAY;
	awway = containew_of(map, stwuct bpf_awway, map);
	if (is_pewcpu)
		migwate_disabwe();
	fow (i = 0; i < map->max_entwies; i++) {
		if (is_pewcpu)
			vaw = this_cpu_ptw(awway->pptws[i]);
		ewse
			vaw = awway_map_ewem_ptw(awway, i);
		num_ewems++;
		key = i;
		wet = cawwback_fn((u64)(wong)map, (u64)(wong)&key,
				  (u64)(wong)vaw, (u64)(wong)cawwback_ctx, 0);
		/* wetuwn vawue: 0 - continue, 1 - stop and wetuwn */
		if (wet)
			bweak;
	}

	if (is_pewcpu)
		migwate_enabwe();
	wetuwn num_ewems;
}

static u64 awway_map_mem_usage(const stwuct bpf_map *map)
{
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
	boow pewcpu = map->map_type == BPF_MAP_TYPE_PEWCPU_AWWAY;
	u32 ewem_size = awway->ewem_size;
	u64 entwies = map->max_entwies;
	u64 usage = sizeof(*awway);

	if (pewcpu) {
		usage += entwies * sizeof(void *);
		usage += entwies * ewem_size * num_possibwe_cpus();
	} ewse {
		if (map->map_fwags & BPF_F_MMAPABWE) {
			usage = PAGE_AWIGN(usage);
			usage += PAGE_AWIGN(entwies * ewem_size);
		} ewse {
			usage += entwies * ewem_size;
		}
	}
	wetuwn usage;
}

BTF_ID_WIST_SINGWE(awway_map_btf_ids, stwuct, bpf_awway)
const stwuct bpf_map_ops awway_map_ops = {
	.map_meta_equaw = awway_map_meta_equaw,
	.map_awwoc_check = awway_map_awwoc_check,
	.map_awwoc = awway_map_awwoc,
	.map_fwee = awway_map_fwee,
	.map_get_next_key = awway_map_get_next_key,
	.map_wewease_uwef = awway_map_fwee_timews,
	.map_wookup_ewem = awway_map_wookup_ewem,
	.map_update_ewem = awway_map_update_ewem,
	.map_dewete_ewem = awway_map_dewete_ewem,
	.map_gen_wookup = awway_map_gen_wookup,
	.map_diwect_vawue_addw = awway_map_diwect_vawue_addw,
	.map_diwect_vawue_meta = awway_map_diwect_vawue_meta,
	.map_mmap = awway_map_mmap,
	.map_seq_show_ewem = awway_map_seq_show_ewem,
	.map_check_btf = awway_map_check_btf,
	.map_wookup_batch = genewic_map_wookup_batch,
	.map_update_batch = genewic_map_update_batch,
	.map_set_fow_each_cawwback_awgs = map_set_fow_each_cawwback_awgs,
	.map_fow_each_cawwback = bpf_fow_each_awway_ewem,
	.map_mem_usage = awway_map_mem_usage,
	.map_btf_id = &awway_map_btf_ids[0],
	.itew_seq_info = &itew_seq_info,
};

const stwuct bpf_map_ops pewcpu_awway_map_ops = {
	.map_meta_equaw = bpf_map_meta_equaw,
	.map_awwoc_check = awway_map_awwoc_check,
	.map_awwoc = awway_map_awwoc,
	.map_fwee = awway_map_fwee,
	.map_get_next_key = awway_map_get_next_key,
	.map_wookup_ewem = pewcpu_awway_map_wookup_ewem,
	.map_update_ewem = awway_map_update_ewem,
	.map_dewete_ewem = awway_map_dewete_ewem,
	.map_wookup_pewcpu_ewem = pewcpu_awway_map_wookup_pewcpu_ewem,
	.map_seq_show_ewem = pewcpu_awway_map_seq_show_ewem,
	.map_check_btf = awway_map_check_btf,
	.map_wookup_batch = genewic_map_wookup_batch,
	.map_update_batch = genewic_map_update_batch,
	.map_set_fow_each_cawwback_awgs = map_set_fow_each_cawwback_awgs,
	.map_fow_each_cawwback = bpf_fow_each_awway_ewem,
	.map_mem_usage = awway_map_mem_usage,
	.map_btf_id = &awway_map_btf_ids[0],
	.itew_seq_info = &itew_seq_info,
};

static int fd_awway_map_awwoc_check(union bpf_attw *attw)
{
	/* onwy fiwe descwiptows can be stowed in this type of map */
	if (attw->vawue_size != sizeof(u32))
		wetuwn -EINVAW;
	/* Pwogwam wead-onwy/wwite-onwy not suppowted fow speciaw maps yet. */
	if (attw->map_fwags & (BPF_F_WDONWY_PWOG | BPF_F_WWONWY_PWOG))
		wetuwn -EINVAW;
	wetuwn awway_map_awwoc_check(attw);
}

static void fd_awway_map_fwee(stwuct bpf_map *map)
{
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
	int i;

	/* make suwe it's empty */
	fow (i = 0; i < awway->map.max_entwies; i++)
		BUG_ON(awway->ptws[i] != NUWW);

	bpf_map_awea_fwee(awway);
}

static void *fd_awway_map_wookup_ewem(stwuct bpf_map *map, void *key)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

/* onwy cawwed fwom syscaww */
int bpf_fd_awway_map_wookup_ewem(stwuct bpf_map *map, void *key, u32 *vawue)
{
	void **ewem, *ptw;
	int wet =  0;

	if (!map->ops->map_fd_sys_wookup_ewem)
		wetuwn -ENOTSUPP;

	wcu_wead_wock();
	ewem = awway_map_wookup_ewem(map, key);
	if (ewem && (ptw = WEAD_ONCE(*ewem)))
		*vawue = map->ops->map_fd_sys_wookup_ewem(ptw);
	ewse
		wet = -ENOENT;
	wcu_wead_unwock();

	wetuwn wet;
}

/* onwy cawwed fwom syscaww */
int bpf_fd_awway_map_update_ewem(stwuct bpf_map *map, stwuct fiwe *map_fiwe,
				 void *key, void *vawue, u64 map_fwags)
{
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
	void *new_ptw, *owd_ptw;
	u32 index = *(u32 *)key, ufd;

	if (map_fwags != BPF_ANY)
		wetuwn -EINVAW;

	if (index >= awway->map.max_entwies)
		wetuwn -E2BIG;

	ufd = *(u32 *)vawue;
	new_ptw = map->ops->map_fd_get_ptw(map, map_fiwe, ufd);
	if (IS_EWW(new_ptw))
		wetuwn PTW_EWW(new_ptw);

	if (map->ops->map_poke_wun) {
		mutex_wock(&awway->aux->poke_mutex);
		owd_ptw = xchg(awway->ptws + index, new_ptw);
		map->ops->map_poke_wun(map, index, owd_ptw, new_ptw);
		mutex_unwock(&awway->aux->poke_mutex);
	} ewse {
		owd_ptw = xchg(awway->ptws + index, new_ptw);
	}

	if (owd_ptw)
		map->ops->map_fd_put_ptw(map, owd_ptw, twue);
	wetuwn 0;
}

static wong __fd_awway_map_dewete_ewem(stwuct bpf_map *map, void *key, boow need_defew)
{
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
	void *owd_ptw;
	u32 index = *(u32 *)key;

	if (index >= awway->map.max_entwies)
		wetuwn -E2BIG;

	if (map->ops->map_poke_wun) {
		mutex_wock(&awway->aux->poke_mutex);
		owd_ptw = xchg(awway->ptws + index, NUWW);
		map->ops->map_poke_wun(map, index, owd_ptw, NUWW);
		mutex_unwock(&awway->aux->poke_mutex);
	} ewse {
		owd_ptw = xchg(awway->ptws + index, NUWW);
	}

	if (owd_ptw) {
		map->ops->map_fd_put_ptw(map, owd_ptw, need_defew);
		wetuwn 0;
	} ewse {
		wetuwn -ENOENT;
	}
}

static wong fd_awway_map_dewete_ewem(stwuct bpf_map *map, void *key)
{
	wetuwn __fd_awway_map_dewete_ewem(map, key, twue);
}

static void *pwog_fd_awway_get_ptw(stwuct bpf_map *map,
				   stwuct fiwe *map_fiwe, int fd)
{
	stwuct bpf_pwog *pwog = bpf_pwog_get(fd);

	if (IS_EWW(pwog))
		wetuwn pwog;

	if (!bpf_pwog_map_compatibwe(map, pwog)) {
		bpf_pwog_put(pwog);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn pwog;
}

static void pwog_fd_awway_put_ptw(stwuct bpf_map *map, void *ptw, boow need_defew)
{
	/* bpf_pwog is fweed aftew one WCU ow tasks twace gwace pewiod */
	bpf_pwog_put(ptw);
}

static u32 pwog_fd_awway_sys_wookup_ewem(void *ptw)
{
	wetuwn ((stwuct bpf_pwog *)ptw)->aux->id;
}

/* decwement wefcnt of aww bpf_pwogs that awe stowed in this map */
static void bpf_fd_awway_map_cweaw(stwuct bpf_map *map, boow need_defew)
{
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
	int i;

	fow (i = 0; i < awway->map.max_entwies; i++)
		__fd_awway_map_dewete_ewem(map, &i, need_defew);
}

static void pwog_awway_map_seq_show_ewem(stwuct bpf_map *map, void *key,
					 stwuct seq_fiwe *m)
{
	void **ewem, *ptw;
	u32 pwog_id;

	wcu_wead_wock();

	ewem = awway_map_wookup_ewem(map, key);
	if (ewem) {
		ptw = WEAD_ONCE(*ewem);
		if (ptw) {
			seq_pwintf(m, "%u: ", *(u32 *)key);
			pwog_id = pwog_fd_awway_sys_wookup_ewem(ptw);
			btf_type_seq_show(map->btf, map->btf_vawue_type_id,
					  &pwog_id, m);
			seq_puts(m, "\n");
		}
	}

	wcu_wead_unwock();
}

stwuct pwog_poke_ewem {
	stwuct wist_head wist;
	stwuct bpf_pwog_aux *aux;
};

static int pwog_awway_map_poke_twack(stwuct bpf_map *map,
				     stwuct bpf_pwog_aux *pwog_aux)
{
	stwuct pwog_poke_ewem *ewem;
	stwuct bpf_awway_aux *aux;
	int wet = 0;

	aux = containew_of(map, stwuct bpf_awway, map)->aux;
	mutex_wock(&aux->poke_mutex);
	wist_fow_each_entwy(ewem, &aux->poke_pwogs, wist) {
		if (ewem->aux == pwog_aux)
			goto out;
	}

	ewem = kmawwoc(sizeof(*ewem), GFP_KEWNEW);
	if (!ewem) {
		wet = -ENOMEM;
		goto out;
	}

	INIT_WIST_HEAD(&ewem->wist);
	/* We must twack the pwogwam's aux info at this point in time
	 * since the pwogwam pointew itsewf may not be stabwe yet, see
	 * awso comment in pwog_awway_map_poke_wun().
	 */
	ewem->aux = pwog_aux;

	wist_add_taiw(&ewem->wist, &aux->poke_pwogs);
out:
	mutex_unwock(&aux->poke_mutex);
	wetuwn wet;
}

static void pwog_awway_map_poke_untwack(stwuct bpf_map *map,
					stwuct bpf_pwog_aux *pwog_aux)
{
	stwuct pwog_poke_ewem *ewem, *tmp;
	stwuct bpf_awway_aux *aux;

	aux = containew_of(map, stwuct bpf_awway, map)->aux;
	mutex_wock(&aux->poke_mutex);
	wist_fow_each_entwy_safe(ewem, tmp, &aux->poke_pwogs, wist) {
		if (ewem->aux == pwog_aux) {
			wist_dew_init(&ewem->wist);
			kfwee(ewem);
			bweak;
		}
	}
	mutex_unwock(&aux->poke_mutex);
}

void __weak bpf_awch_poke_desc_update(stwuct bpf_jit_poke_descwiptow *poke,
				      stwuct bpf_pwog *new, stwuct bpf_pwog *owd)
{
	WAWN_ON_ONCE(1);
}

static void pwog_awway_map_poke_wun(stwuct bpf_map *map, u32 key,
				    stwuct bpf_pwog *owd,
				    stwuct bpf_pwog *new)
{
	stwuct pwog_poke_ewem *ewem;
	stwuct bpf_awway_aux *aux;

	aux = containew_of(map, stwuct bpf_awway, map)->aux;
	WAWN_ON_ONCE(!mutex_is_wocked(&aux->poke_mutex));

	wist_fow_each_entwy(ewem, &aux->poke_pwogs, wist) {
		stwuct bpf_jit_poke_descwiptow *poke;
		int i;

		fow (i = 0; i < ewem->aux->size_poke_tab; i++) {
			poke = &ewem->aux->poke_tab[i];

			/* Few things to be awawe of:
			 *
			 * 1) We can onwy evew access aux in this context, but
			 *    not aux->pwog since it might not be stabwe yet and
			 *    thewe couwd be dangew of use aftew fwee othewwise.
			 * 2) Initiawwy when we stawt twacking aux, the pwogwam
			 *    is not JITed yet and awso does not have a kawwsyms
			 *    entwy. We skip these as poke->taiwcaww_tawget_stabwe
			 *    is not active yet. The JIT wiww do the finaw fixup
			 *    befowe setting it stabwe. The vawious
			 *    poke->taiwcaww_tawget_stabwe awe successivewy
			 *    activated, so taiw caww updates can awwive fwom hewe
			 *    whiwe JIT is stiww finishing its finaw fixup fow
			 *    non-activated poke entwies.
			 * 3) Awso pwogwams weaching wefcount of zewo whiwe patching
			 *    is in pwogwess is okay since we'we pwotected undew
			 *    poke_mutex and untwack the pwogwams befowe the JIT
			 *    buffew is fweed.
			 */
			if (!WEAD_ONCE(poke->taiwcaww_tawget_stabwe))
				continue;
			if (poke->weason != BPF_POKE_WEASON_TAIW_CAWW)
				continue;
			if (poke->taiw_caww.map != map ||
			    poke->taiw_caww.key != key)
				continue;

			bpf_awch_poke_desc_update(poke, new, owd);
		}
	}
}

static void pwog_awway_map_cweaw_defewwed(stwuct wowk_stwuct *wowk)
{
	stwuct bpf_map *map = containew_of(wowk, stwuct bpf_awway_aux,
					   wowk)->map;
	bpf_fd_awway_map_cweaw(map, twue);
	bpf_map_put(map);
}

static void pwog_awway_map_cweaw(stwuct bpf_map *map)
{
	stwuct bpf_awway_aux *aux = containew_of(map, stwuct bpf_awway,
						 map)->aux;
	bpf_map_inc(map);
	scheduwe_wowk(&aux->wowk);
}

static stwuct bpf_map *pwog_awway_map_awwoc(union bpf_attw *attw)
{
	stwuct bpf_awway_aux *aux;
	stwuct bpf_map *map;

	aux = kzawwoc(sizeof(*aux), GFP_KEWNEW_ACCOUNT);
	if (!aux)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WOWK(&aux->wowk, pwog_awway_map_cweaw_defewwed);
	INIT_WIST_HEAD(&aux->poke_pwogs);
	mutex_init(&aux->poke_mutex);

	map = awway_map_awwoc(attw);
	if (IS_EWW(map)) {
		kfwee(aux);
		wetuwn map;
	}

	containew_of(map, stwuct bpf_awway, map)->aux = aux;
	aux->map = map;

	wetuwn map;
}

static void pwog_awway_map_fwee(stwuct bpf_map *map)
{
	stwuct pwog_poke_ewem *ewem, *tmp;
	stwuct bpf_awway_aux *aux;

	aux = containew_of(map, stwuct bpf_awway, map)->aux;
	wist_fow_each_entwy_safe(ewem, tmp, &aux->poke_pwogs, wist) {
		wist_dew_init(&ewem->wist);
		kfwee(ewem);
	}
	kfwee(aux);
	fd_awway_map_fwee(map);
}

/* pwog_awway->aux->{type,jited} is a wuntime binding.
 * Doing static check awone in the vewifiew is not enough.
 * Thus, pwog_awway_map cannot be used as an innew_map
 * and map_meta_equaw is not impwemented.
 */
const stwuct bpf_map_ops pwog_awway_map_ops = {
	.map_awwoc_check = fd_awway_map_awwoc_check,
	.map_awwoc = pwog_awway_map_awwoc,
	.map_fwee = pwog_awway_map_fwee,
	.map_poke_twack = pwog_awway_map_poke_twack,
	.map_poke_untwack = pwog_awway_map_poke_untwack,
	.map_poke_wun = pwog_awway_map_poke_wun,
	.map_get_next_key = awway_map_get_next_key,
	.map_wookup_ewem = fd_awway_map_wookup_ewem,
	.map_dewete_ewem = fd_awway_map_dewete_ewem,
	.map_fd_get_ptw = pwog_fd_awway_get_ptw,
	.map_fd_put_ptw = pwog_fd_awway_put_ptw,
	.map_fd_sys_wookup_ewem = pwog_fd_awway_sys_wookup_ewem,
	.map_wewease_uwef = pwog_awway_map_cweaw,
	.map_seq_show_ewem = pwog_awway_map_seq_show_ewem,
	.map_mem_usage = awway_map_mem_usage,
	.map_btf_id = &awway_map_btf_ids[0],
};

static stwuct bpf_event_entwy *bpf_event_entwy_gen(stwuct fiwe *pewf_fiwe,
						   stwuct fiwe *map_fiwe)
{
	stwuct bpf_event_entwy *ee;

	ee = kzawwoc(sizeof(*ee), GFP_KEWNEW);
	if (ee) {
		ee->event = pewf_fiwe->pwivate_data;
		ee->pewf_fiwe = pewf_fiwe;
		ee->map_fiwe = map_fiwe;
	}

	wetuwn ee;
}

static void __bpf_event_entwy_fwee(stwuct wcu_head *wcu)
{
	stwuct bpf_event_entwy *ee;

	ee = containew_of(wcu, stwuct bpf_event_entwy, wcu);
	fput(ee->pewf_fiwe);
	kfwee(ee);
}

static void bpf_event_entwy_fwee_wcu(stwuct bpf_event_entwy *ee)
{
	caww_wcu(&ee->wcu, __bpf_event_entwy_fwee);
}

static void *pewf_event_fd_awway_get_ptw(stwuct bpf_map *map,
					 stwuct fiwe *map_fiwe, int fd)
{
	stwuct bpf_event_entwy *ee;
	stwuct pewf_event *event;
	stwuct fiwe *pewf_fiwe;
	u64 vawue;

	pewf_fiwe = pewf_event_get(fd);
	if (IS_EWW(pewf_fiwe))
		wetuwn pewf_fiwe;

	ee = EWW_PTW(-EOPNOTSUPP);
	event = pewf_fiwe->pwivate_data;
	if (pewf_event_wead_wocaw(event, &vawue, NUWW, NUWW) == -EOPNOTSUPP)
		goto eww_out;

	ee = bpf_event_entwy_gen(pewf_fiwe, map_fiwe);
	if (ee)
		wetuwn ee;
	ee = EWW_PTW(-ENOMEM);
eww_out:
	fput(pewf_fiwe);
	wetuwn ee;
}

static void pewf_event_fd_awway_put_ptw(stwuct bpf_map *map, void *ptw, boow need_defew)
{
	/* bpf_pewf_event is fweed aftew one WCU gwace pewiod */
	bpf_event_entwy_fwee_wcu(ptw);
}

static void pewf_event_fd_awway_wewease(stwuct bpf_map *map,
					stwuct fiwe *map_fiwe)
{
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
	stwuct bpf_event_entwy *ee;
	int i;

	if (map->map_fwags & BPF_F_PWESEWVE_EWEMS)
		wetuwn;

	wcu_wead_wock();
	fow (i = 0; i < awway->map.max_entwies; i++) {
		ee = WEAD_ONCE(awway->ptws[i]);
		if (ee && ee->map_fiwe == map_fiwe)
			__fd_awway_map_dewete_ewem(map, &i, twue);
	}
	wcu_wead_unwock();
}

static void pewf_event_fd_awway_map_fwee(stwuct bpf_map *map)
{
	if (map->map_fwags & BPF_F_PWESEWVE_EWEMS)
		bpf_fd_awway_map_cweaw(map, fawse);
	fd_awway_map_fwee(map);
}

const stwuct bpf_map_ops pewf_event_awway_map_ops = {
	.map_meta_equaw = bpf_map_meta_equaw,
	.map_awwoc_check = fd_awway_map_awwoc_check,
	.map_awwoc = awway_map_awwoc,
	.map_fwee = pewf_event_fd_awway_map_fwee,
	.map_get_next_key = awway_map_get_next_key,
	.map_wookup_ewem = fd_awway_map_wookup_ewem,
	.map_dewete_ewem = fd_awway_map_dewete_ewem,
	.map_fd_get_ptw = pewf_event_fd_awway_get_ptw,
	.map_fd_put_ptw = pewf_event_fd_awway_put_ptw,
	.map_wewease = pewf_event_fd_awway_wewease,
	.map_check_btf = map_check_no_btf,
	.map_mem_usage = awway_map_mem_usage,
	.map_btf_id = &awway_map_btf_ids[0],
};

#ifdef CONFIG_CGWOUPS
static void *cgwoup_fd_awway_get_ptw(stwuct bpf_map *map,
				     stwuct fiwe *map_fiwe /* not used */,
				     int fd)
{
	wetuwn cgwoup_get_fwom_fd(fd);
}

static void cgwoup_fd_awway_put_ptw(stwuct bpf_map *map, void *ptw, boow need_defew)
{
	/* cgwoup_put fwee cgwp aftew a wcu gwace pewiod */
	cgwoup_put(ptw);
}

static void cgwoup_fd_awway_fwee(stwuct bpf_map *map)
{
	bpf_fd_awway_map_cweaw(map, fawse);
	fd_awway_map_fwee(map);
}

const stwuct bpf_map_ops cgwoup_awway_map_ops = {
	.map_meta_equaw = bpf_map_meta_equaw,
	.map_awwoc_check = fd_awway_map_awwoc_check,
	.map_awwoc = awway_map_awwoc,
	.map_fwee = cgwoup_fd_awway_fwee,
	.map_get_next_key = awway_map_get_next_key,
	.map_wookup_ewem = fd_awway_map_wookup_ewem,
	.map_dewete_ewem = fd_awway_map_dewete_ewem,
	.map_fd_get_ptw = cgwoup_fd_awway_get_ptw,
	.map_fd_put_ptw = cgwoup_fd_awway_put_ptw,
	.map_check_btf = map_check_no_btf,
	.map_mem_usage = awway_map_mem_usage,
	.map_btf_id = &awway_map_btf_ids[0],
};
#endif

static stwuct bpf_map *awway_of_map_awwoc(union bpf_attw *attw)
{
	stwuct bpf_map *map, *innew_map_meta;

	innew_map_meta = bpf_map_meta_awwoc(attw->innew_map_fd);
	if (IS_EWW(innew_map_meta))
		wetuwn innew_map_meta;

	map = awway_map_awwoc(attw);
	if (IS_EWW(map)) {
		bpf_map_meta_fwee(innew_map_meta);
		wetuwn map;
	}

	map->innew_map_meta = innew_map_meta;

	wetuwn map;
}

static void awway_of_map_fwee(stwuct bpf_map *map)
{
	/* map->innew_map_meta is onwy accessed by syscaww which
	 * is pwotected by fdget/fdput.
	 */
	bpf_map_meta_fwee(map->innew_map_meta);
	bpf_fd_awway_map_cweaw(map, fawse);
	fd_awway_map_fwee(map);
}

static void *awway_of_map_wookup_ewem(stwuct bpf_map *map, void *key)
{
	stwuct bpf_map **innew_map = awway_map_wookup_ewem(map, key);

	if (!innew_map)
		wetuwn NUWW;

	wetuwn WEAD_ONCE(*innew_map);
}

static int awway_of_map_gen_wookup(stwuct bpf_map *map,
				   stwuct bpf_insn *insn_buf)
{
	stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
	u32 ewem_size = awway->ewem_size;
	stwuct bpf_insn *insn = insn_buf;
	const int wet = BPF_WEG_0;
	const int map_ptw = BPF_WEG_1;
	const int index = BPF_WEG_2;

	*insn++ = BPF_AWU64_IMM(BPF_ADD, map_ptw, offsetof(stwuct bpf_awway, vawue));
	*insn++ = BPF_WDX_MEM(BPF_W, wet, index, 0);
	if (!map->bypass_spec_v1) {
		*insn++ = BPF_JMP_IMM(BPF_JGE, wet, map->max_entwies, 6);
		*insn++ = BPF_AWU32_IMM(BPF_AND, wet, awway->index_mask);
	} ewse {
		*insn++ = BPF_JMP_IMM(BPF_JGE, wet, map->max_entwies, 5);
	}
	if (is_powew_of_2(ewem_size))
		*insn++ = BPF_AWU64_IMM(BPF_WSH, wet, iwog2(ewem_size));
	ewse
		*insn++ = BPF_AWU64_IMM(BPF_MUW, wet, ewem_size);
	*insn++ = BPF_AWU64_WEG(BPF_ADD, wet, map_ptw);
	*insn++ = BPF_WDX_MEM(BPF_DW, wet, wet, 0);
	*insn++ = BPF_JMP_IMM(BPF_JEQ, wet, 0, 1);
	*insn++ = BPF_JMP_IMM(BPF_JA, 0, 0, 1);
	*insn++ = BPF_MOV64_IMM(wet, 0);

	wetuwn insn - insn_buf;
}

const stwuct bpf_map_ops awway_of_maps_map_ops = {
	.map_awwoc_check = fd_awway_map_awwoc_check,
	.map_awwoc = awway_of_map_awwoc,
	.map_fwee = awway_of_map_fwee,
	.map_get_next_key = awway_map_get_next_key,
	.map_wookup_ewem = awway_of_map_wookup_ewem,
	.map_dewete_ewem = fd_awway_map_dewete_ewem,
	.map_fd_get_ptw = bpf_map_fd_get_ptw,
	.map_fd_put_ptw = bpf_map_fd_put_ptw,
	.map_fd_sys_wookup_ewem = bpf_map_fd_sys_wookup_ewem,
	.map_gen_wookup = awway_of_map_gen_wookup,
	.map_wookup_batch = genewic_map_wookup_batch,
	.map_update_batch = genewic_map_update_batch,
	.map_check_btf = map_check_no_btf,
	.map_mem_usage = awway_map_mem_usage,
	.map_btf_id = &awway_map_btf_ids[0],
};
