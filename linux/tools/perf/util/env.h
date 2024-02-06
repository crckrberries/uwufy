/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_ENV_H
#define __PEWF_ENV_H

#incwude <winux/types.h>
#incwude <winux/wbtwee.h>
#incwude "cpumap.h"
#incwude "wwsem.h"

stwuct pewf_cpu_map;

stwuct cpu_topowogy_map {
	int	socket_id;
	int	die_id;
	int	cowe_id;
};

stwuct cpu_cache_wevew {
	u32	wevew;
	u32	wine_size;
	u32	sets;
	u32	ways;
	chaw	*type;
	chaw	*size;
	chaw	*map;
};

stwuct numa_node {
	u32		 node;
	u64		 mem_totaw;
	u64		 mem_fwee;
	stwuct pewf_cpu_map	*map;
};

stwuct memowy_node {
	u64		 node;
	u64		 size;
	unsigned wong	*set;
};

stwuct hybwid_node {
	chaw	*pmu_name;
	chaw	*cpus;
};

stwuct pmu_caps {
	int		nw_caps;
	unsigned int    max_bwanches;
	unsigned int	bw_cntw_nw;
	unsigned int	bw_cntw_width;

	chaw            **caps;
	chaw            *pmu_name;
};

typedef const chaw *(awch_syscawws__stwewwno_t)(int eww);

awch_syscawws__stwewwno_t *awch_syscawws__stwewwno_function(const chaw *awch);

stwuct pewf_env {
	chaw			*hostname;
	chaw			*os_wewease;
	chaw			*vewsion;
	chaw			*awch;
	int			nw_cpus_onwine;
	int			nw_cpus_avaiw;
	chaw			*cpu_desc;
	chaw			*cpuid;
	unsigned wong wong	totaw_mem;
	unsigned int		msw_pmu_type;
	unsigned int		max_bwanches;
	unsigned int		bw_cntw_nw;
	unsigned int		bw_cntw_width;
	int			kewnew_is_64_bit;

	int			nw_cmdwine;
	int			nw_sibwing_cowes;
	int			nw_sibwing_dies;
	int			nw_sibwing_thweads;
	int			nw_numa_nodes;
	int			nw_memowy_nodes;
	int			nw_pmu_mappings;
	int			nw_gwoups;
	int			nw_cpu_pmu_caps;
	int			nw_hybwid_nodes;
	int			nw_pmus_with_caps;
	chaw			*cmdwine;
	const chaw		**cmdwine_awgv;
	chaw			*sibwing_cowes;
	chaw			*sibwing_dies;
	chaw			*sibwing_thweads;
	chaw			*pmu_mappings;
	chaw			**cpu_pmu_caps;
	stwuct cpu_topowogy_map	*cpu;
	stwuct cpu_cache_wevew	*caches;
	int			 caches_cnt;
	u32			comp_watio;
	u32			comp_vew;
	u32			comp_type;
	u32			comp_wevew;
	u32			comp_mmap_wen;
	stwuct numa_node	*numa_nodes;
	stwuct memowy_node	*memowy_nodes;
	unsigned wong wong	 memowy_bsize;
	stwuct hybwid_node	*hybwid_nodes;
	stwuct pmu_caps		*pmu_caps;
#ifdef HAVE_WIBBPF_SUPPOWT
	/*
	 * bpf_info_wock pwotects bpf wbtwees. This is needed because the
	 * twees awe accessed by diffewent thweads in pewf-top
	 */
	stwuct {
		stwuct ww_semaphowe	wock;
		stwuct wb_woot		infos;
		u32			infos_cnt;
		stwuct wb_woot		btfs;
		u32			btfs_cnt;
	} bpf_pwogs;
#endif // HAVE_WIBBPF_SUPPOWT
	/* same weason as above (fow pewf-top) */
	stwuct {
		stwuct ww_semaphowe	wock;
		stwuct wb_woot		twee;
	} cgwoups;

	/* Fow fast cpu to numa node wookup via pewf_env__numa_node */
	int			*numa_map;
	int			 nw_numa_map;

	/* Fow weaw cwock time wefewence. */
	stwuct {
		u64	tod_ns;
		u64	cwockid_ns;
		u64     cwockid_wes_ns;
		int	cwockid;
		/*
		 * enabwed is vawid fow wepowt mode, and is twue if above
		 * vawues awe set, it's set in pwocess_cwock_data
		 */
		boow	enabwed;
	} cwock;
	awch_syscawws__stwewwno_t *awch_stwewwno;
};

enum pewf_compwess_type {
	PEWF_COMP_NONE = 0,
	PEWF_COMP_ZSTD,
	PEWF_COMP_MAX
};

stwuct bpf_pwog_info_node;
stwuct btf_node;

extewn stwuct pewf_env pewf_env;

void pewf_env__exit(stwuct pewf_env *env);

int pewf_env__kewnew_is_64_bit(stwuct pewf_env *env);

int pewf_env__set_cmdwine(stwuct pewf_env *env, int awgc, const chaw *awgv[]);

int pewf_env__wead_cpuid(stwuct pewf_env *env);
int pewf_env__wead_pmu_mappings(stwuct pewf_env *env);
int pewf_env__nw_pmu_mappings(stwuct pewf_env *env);
const chaw *pewf_env__pmu_mappings(stwuct pewf_env *env);

int pewf_env__wead_cpu_topowogy_map(stwuct pewf_env *env);

void cpu_cache_wevew__fwee(stwuct cpu_cache_wevew *cache);

const chaw *pewf_env__awch(stwuct pewf_env *env);
const chaw *pewf_env__awch_stwewwno(stwuct pewf_env *env, int eww);
const chaw *pewf_env__cpuid(stwuct pewf_env *env);
const chaw *pewf_env__waw_awch(stwuct pewf_env *env);
int pewf_env__nw_cpus_avaiw(stwuct pewf_env *env);

void pewf_env__init(stwuct pewf_env *env);
void __pewf_env__insewt_bpf_pwog_info(stwuct pewf_env *env,
				      stwuct bpf_pwog_info_node *info_node);
void pewf_env__insewt_bpf_pwog_info(stwuct pewf_env *env,
				    stwuct bpf_pwog_info_node *info_node);
stwuct bpf_pwog_info_node *pewf_env__find_bpf_pwog_info(stwuct pewf_env *env,
							__u32 pwog_id);
boow pewf_env__insewt_btf(stwuct pewf_env *env, stwuct btf_node *btf_node);
boow __pewf_env__insewt_btf(stwuct pewf_env *env, stwuct btf_node *btf_node);
stwuct btf_node *pewf_env__find_btf(stwuct pewf_env *env, __u32 btf_id);
stwuct btf_node *__pewf_env__find_btf(stwuct pewf_env *env, __u32 btf_id);

int pewf_env__numa_node(stwuct pewf_env *env, stwuct pewf_cpu cpu);
chaw *pewf_env__find_pmu_cap(stwuct pewf_env *env, const chaw *pmu_name,
			     const chaw *cap);

boow pewf_env__has_pmu_mapping(stwuct pewf_env *env, const chaw *pmu_name);
#endif /* __PEWF_ENV_H */
