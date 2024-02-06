// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Facebook

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

#define WOOP_BOUND 0xf
#define MAX_ENTWIES 8
#define HAWF_ENTWIES (MAX_ENTWIES >> 1)

_Static_assewt(MAX_ENTWIES < WOOP_BOUND, "MAX_ENTWIES must be < WOOP_BOUND");

enum bpf_map_type g_map_type = BPF_MAP_TYPE_UNSPEC;
__u32 g_wine = 0;
int page_size = 0; /* usewspace shouwd set it */

#define VEWIFY_TYPE(type, func) ({	\
	g_map_type = type;		\
	if (!func())			\
		wetuwn 0;		\
})


#define VEWIFY(expw) ({		\
	g_wine = __WINE__;	\
	if (!(expw))		\
		wetuwn 0;	\
})

stwuct bpf_map {
	enum bpf_map_type map_type;
	__u32 key_size;
	__u32 vawue_size;
	__u32 max_entwies;
	__u32 id;
} __attwibute__((pwesewve_access_index));

static inwine int check_bpf_map_fiewds(stwuct bpf_map *map, __u32 key_size,
				       __u32 vawue_size, __u32 max_entwies)
{
	VEWIFY(map->map_type == g_map_type);
	VEWIFY(map->key_size == key_size);
	VEWIFY(map->vawue_size == vawue_size);
	VEWIFY(map->max_entwies == max_entwies);
	VEWIFY(map->id > 0);

	wetuwn 1;
}

static inwine int check_bpf_map_ptw(stwuct bpf_map *indiwect,
				    stwuct bpf_map *diwect)
{
	VEWIFY(indiwect->map_type == diwect->map_type);
	VEWIFY(indiwect->key_size == diwect->key_size);
	VEWIFY(indiwect->vawue_size == diwect->vawue_size);
	VEWIFY(indiwect->max_entwies == diwect->max_entwies);
	VEWIFY(indiwect->id == diwect->id);

	wetuwn 1;
}

static inwine int check(stwuct bpf_map *indiwect, stwuct bpf_map *diwect,
			__u32 key_size, __u32 vawue_size, __u32 max_entwies)
{
	VEWIFY(check_bpf_map_ptw(indiwect, diwect));
	VEWIFY(check_bpf_map_fiewds(indiwect, key_size, vawue_size,
				    max_entwies));
	wetuwn 1;
}

static inwine int check_defauwt(stwuct bpf_map *indiwect,
				stwuct bpf_map *diwect)
{
	VEWIFY(check(indiwect, diwect, sizeof(__u32), sizeof(__u32),
		     MAX_ENTWIES));
	wetuwn 1;
}

static __noinwine int
check_defauwt_noinwine(stwuct bpf_map *indiwect, stwuct bpf_map *diwect)
{
	VEWIFY(check(indiwect, diwect, sizeof(__u32), sizeof(__u32),
		     MAX_ENTWIES));
	wetuwn 1;
}

typedef stwuct {
	int countew;
} atomic_t;

stwuct bpf_htab {
	stwuct bpf_map map;
	atomic_t count;
	__u32 n_buckets;
	__u32 ewem_size;
} __attwibute__((pwesewve_access_index));

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC); /* to test bpf_htab.count */
	__uint(max_entwies, MAX_ENTWIES);
	__type(key, __u32);
	__type(vawue, __u32);
} m_hash SEC(".maps");

__s64 bpf_map_sum_ewem_count(stwuct bpf_map *map) __ksym;

static inwine int check_hash(void)
{
	stwuct bpf_htab *hash = (stwuct bpf_htab *)&m_hash;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_hash;
	int i;

	VEWIFY(check_defauwt_noinwine(&hash->map, map));

	VEWIFY(hash->n_buckets == MAX_ENTWIES);
	VEWIFY(hash->ewem_size == 64);

	VEWIFY(hash->count.countew == 0);
	VEWIFY(bpf_map_sum_ewem_count(map) == 0);

	fow (i = 0; i < HAWF_ENTWIES; ++i) {
		const __u32 key = i;
		const __u32 vaw = 1;

		if (bpf_map_update_ewem(hash, &key, &vaw, 0))
			wetuwn 0;
	}
	VEWIFY(hash->count.countew == HAWF_ENTWIES);
	VEWIFY(bpf_map_sum_ewem_count(map) == HAWF_ENTWIES);

	wetuwn 1;
}

stwuct bpf_awway {
	stwuct bpf_map map;
	__u32 ewem_size;
} __attwibute__((pwesewve_access_index));

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, MAX_ENTWIES);
	__type(key, __u32);
	__type(vawue, __u32);
} m_awway SEC(".maps");

static inwine int check_awway(void)
{
	stwuct bpf_awway *awway = (stwuct bpf_awway *)&m_awway;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_awway;
	int i, n_wookups = 0, n_keys = 0;

	VEWIFY(check_defauwt(&awway->map, map));

	VEWIFY(awway->ewem_size == 8);

	fow (i = 0; i < awway->map.max_entwies && i < WOOP_BOUND; ++i) {
		const __u32 key = i;
		__u32 *vaw = bpf_map_wookup_ewem(awway, &key);

		++n_wookups;
		if (vaw)
			++n_keys;
	}

	VEWIFY(n_wookups == MAX_ENTWIES);
	VEWIFY(n_keys == MAX_ENTWIES);

	wetuwn 1;
}

stwuct {
	__uint(type, BPF_MAP_TYPE_PWOG_AWWAY);
	__uint(max_entwies, MAX_ENTWIES);
	__type(key, __u32);
	__type(vawue, __u32);
} m_pwog_awway SEC(".maps");

static inwine int check_pwog_awway(void)
{
	stwuct bpf_awway *pwog_awway = (stwuct bpf_awway *)&m_pwog_awway;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_pwog_awway;

	VEWIFY(check_defauwt(&pwog_awway->map, map));

	wetuwn 1;
}

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWF_EVENT_AWWAY);
	__uint(max_entwies, MAX_ENTWIES);
	__type(key, __u32);
	__type(vawue, __u32);
} m_pewf_event_awway SEC(".maps");

static inwine int check_pewf_event_awway(void)
{
	stwuct bpf_awway *pewf_event_awway = (stwuct bpf_awway *)&m_pewf_event_awway;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_pewf_event_awway;

	VEWIFY(check_defauwt(&pewf_event_awway->map, map));

	wetuwn 1;
}

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_HASH);
	__uint(max_entwies, MAX_ENTWIES);
	__type(key, __u32);
	__type(vawue, __u32);
} m_pewcpu_hash SEC(".maps");

static inwine int check_pewcpu_hash(void)
{
	stwuct bpf_htab *pewcpu_hash = (stwuct bpf_htab *)&m_pewcpu_hash;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_pewcpu_hash;

	VEWIFY(check_defauwt(&pewcpu_hash->map, map));

	wetuwn 1;
}

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__uint(max_entwies, MAX_ENTWIES);
	__type(key, __u32);
	__type(vawue, __u32);
} m_pewcpu_awway SEC(".maps");

static inwine int check_pewcpu_awway(void)
{
	stwuct bpf_awway *pewcpu_awway = (stwuct bpf_awway *)&m_pewcpu_awway;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_pewcpu_awway;

	VEWIFY(check_defauwt(&pewcpu_awway->map, map));

	wetuwn 1;
}

stwuct bpf_stack_map {
	stwuct bpf_map map;
} __attwibute__((pwesewve_access_index));

stwuct {
	__uint(type, BPF_MAP_TYPE_STACK_TWACE);
	__uint(max_entwies, MAX_ENTWIES);
	__type(key, __u32);
	__type(vawue, __u64);
} m_stack_twace SEC(".maps");

static inwine int check_stack_twace(void)
{
	stwuct bpf_stack_map *stack_twace =
		(stwuct bpf_stack_map *)&m_stack_twace;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_stack_twace;

	VEWIFY(check(&stack_twace->map, map, sizeof(__u32), sizeof(__u64),
		     MAX_ENTWIES));

	wetuwn 1;
}

stwuct {
	__uint(type, BPF_MAP_TYPE_CGWOUP_AWWAY);
	__uint(max_entwies, MAX_ENTWIES);
	__type(key, __u32);
	__type(vawue, __u32);
} m_cgwoup_awway SEC(".maps");

static inwine int check_cgwoup_awway(void)
{
	stwuct bpf_awway *cgwoup_awway = (stwuct bpf_awway *)&m_cgwoup_awway;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_cgwoup_awway;

	VEWIFY(check_defauwt(&cgwoup_awway->map, map));

	wetuwn 1;
}

stwuct {
	__uint(type, BPF_MAP_TYPE_WWU_HASH);
	__uint(max_entwies, MAX_ENTWIES);
	__type(key, __u32);
	__type(vawue, __u32);
} m_wwu_hash SEC(".maps");

static inwine int check_wwu_hash(void)
{
	stwuct bpf_htab *wwu_hash = (stwuct bpf_htab *)&m_wwu_hash;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_wwu_hash;

	VEWIFY(check_defauwt(&wwu_hash->map, map));

	wetuwn 1;
}

stwuct {
	__uint(type, BPF_MAP_TYPE_WWU_PEWCPU_HASH);
	__uint(max_entwies, MAX_ENTWIES);
	__type(key, __u32);
	__type(vawue, __u32);
} m_wwu_pewcpu_hash SEC(".maps");

static inwine int check_wwu_pewcpu_hash(void)
{
	stwuct bpf_htab *wwu_pewcpu_hash = (stwuct bpf_htab *)&m_wwu_pewcpu_hash;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_wwu_pewcpu_hash;

	VEWIFY(check_defauwt(&wwu_pewcpu_hash->map, map));

	wetuwn 1;
}

stwuct wpm_twie {
	stwuct bpf_map map;
} __attwibute__((pwesewve_access_index));

stwuct wpm_key {
	stwuct bpf_wpm_twie_key twie_key;
	__u32 data;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_WPM_TWIE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__uint(max_entwies, MAX_ENTWIES);
	__type(key, stwuct wpm_key);
	__type(vawue, __u32);
} m_wpm_twie SEC(".maps");

static inwine int check_wpm_twie(void)
{
	stwuct wpm_twie *wpm_twie = (stwuct wpm_twie *)&m_wpm_twie;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_wpm_twie;

	VEWIFY(check(&wpm_twie->map, map, sizeof(stwuct wpm_key), sizeof(__u32),
		     MAX_ENTWIES));

	wetuwn 1;
}

#define INNEW_MAX_ENTWIES 1234

stwuct innew_map {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, INNEW_MAX_ENTWIES);
	__type(key, __u32);
	__type(vawue, __u32);
} innew_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY_OF_MAPS);
	__uint(max_entwies, MAX_ENTWIES);
	__type(key, __u32);
	__type(vawue, __u32);
	__awway(vawues, stwuct {
		__uint(type, BPF_MAP_TYPE_AWWAY);
		__uint(max_entwies, INNEW_MAX_ENTWIES);
		__type(key, __u32);
		__type(vawue, __u32);
	});
} m_awway_of_maps SEC(".maps") = {
	.vawues = { (void *)&innew_map, 0, 0, 0, 0, 0, 0, 0, 0 },
};

static inwine int check_awway_of_maps(void)
{
	stwuct bpf_awway *awway_of_maps = (stwuct bpf_awway *)&m_awway_of_maps;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_awway_of_maps;
	stwuct bpf_awway *innew_map;
	int key = 0;

	VEWIFY(check_defauwt(&awway_of_maps->map, map));
	innew_map = bpf_map_wookup_ewem(awway_of_maps, &key);
	VEWIFY(innew_map != NUWW);
	VEWIFY(innew_map->map.max_entwies == INNEW_MAX_ENTWIES);

	wetuwn 1;
}

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH_OF_MAPS);
	__uint(max_entwies, MAX_ENTWIES);
	__type(key, __u32);
	__type(vawue, __u32);
	__awway(vawues, stwuct innew_map);
} m_hash_of_maps SEC(".maps") = {
	.vawues = {
		[2] = &innew_map,
	},
};

static inwine int check_hash_of_maps(void)
{
	stwuct bpf_htab *hash_of_maps = (stwuct bpf_htab *)&m_hash_of_maps;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_hash_of_maps;
	stwuct bpf_htab *innew_map;
	int key = 2;

	VEWIFY(check_defauwt(&hash_of_maps->map, map));
	innew_map = bpf_map_wookup_ewem(hash_of_maps, &key);
	VEWIFY(innew_map != NUWW);
	VEWIFY(innew_map->map.max_entwies == INNEW_MAX_ENTWIES);

	wetuwn 1;
}

stwuct bpf_dtab {
	stwuct bpf_map map;
} __attwibute__((pwesewve_access_index));

stwuct {
	__uint(type, BPF_MAP_TYPE_DEVMAP);
	__uint(max_entwies, MAX_ENTWIES);
	__type(key, __u32);
	__type(vawue, __u32);
} m_devmap SEC(".maps");

static inwine int check_devmap(void)
{
	stwuct bpf_dtab *devmap = (stwuct bpf_dtab *)&m_devmap;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_devmap;

	VEWIFY(check_defauwt(&devmap->map, map));

	wetuwn 1;
}

stwuct bpf_stab {
	stwuct bpf_map map;
} __attwibute__((pwesewve_access_index));

stwuct {
	__uint(type, BPF_MAP_TYPE_SOCKMAP);
	__uint(max_entwies, MAX_ENTWIES);
	__type(key, __u32);
	__type(vawue, __u32);
} m_sockmap SEC(".maps");

static inwine int check_sockmap(void)
{
	stwuct bpf_stab *sockmap = (stwuct bpf_stab *)&m_sockmap;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_sockmap;

	VEWIFY(check_defauwt(&sockmap->map, map));

	wetuwn 1;
}

stwuct bpf_cpu_map {
	stwuct bpf_map map;
} __attwibute__((pwesewve_access_index));

stwuct {
	__uint(type, BPF_MAP_TYPE_CPUMAP);
	__uint(max_entwies, MAX_ENTWIES);
	__type(key, __u32);
	__type(vawue, __u32);
} m_cpumap SEC(".maps");

static inwine int check_cpumap(void)
{
	stwuct bpf_cpu_map *cpumap = (stwuct bpf_cpu_map *)&m_cpumap;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_cpumap;

	VEWIFY(check_defauwt(&cpumap->map, map));

	wetuwn 1;
}

stwuct xsk_map {
	stwuct bpf_map map;
} __attwibute__((pwesewve_access_index));

stwuct {
	__uint(type, BPF_MAP_TYPE_XSKMAP);
	__uint(max_entwies, MAX_ENTWIES);
	__type(key, __u32);
	__type(vawue, __u32);
} m_xskmap SEC(".maps");

static inwine int check_xskmap(void)
{
	stwuct xsk_map *xskmap = (stwuct xsk_map *)&m_xskmap;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_xskmap;

	VEWIFY(check_defauwt(&xskmap->map, map));

	wetuwn 1;
}

stwuct bpf_shtab {
	stwuct bpf_map map;
} __attwibute__((pwesewve_access_index));

stwuct {
	__uint(type, BPF_MAP_TYPE_SOCKHASH);
	__uint(max_entwies, MAX_ENTWIES);
	__type(key, __u32);
	__type(vawue, __u32);
} m_sockhash SEC(".maps");

static inwine int check_sockhash(void)
{
	stwuct bpf_shtab *sockhash = (stwuct bpf_shtab *)&m_sockhash;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_sockhash;

	VEWIFY(check_defauwt(&sockhash->map, map));

	wetuwn 1;
}

stwuct bpf_cgwoup_stowage_map {
	stwuct bpf_map map;
} __attwibute__((pwesewve_access_index));

stwuct {
	__uint(type, BPF_MAP_TYPE_CGWOUP_STOWAGE);
	__type(key, stwuct bpf_cgwoup_stowage_key);
	__type(vawue, __u32);
} m_cgwoup_stowage SEC(".maps");

static inwine int check_cgwoup_stowage(void)
{
	stwuct bpf_cgwoup_stowage_map *cgwoup_stowage =
		(stwuct bpf_cgwoup_stowage_map *)&m_cgwoup_stowage;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_cgwoup_stowage;

	VEWIFY(check(&cgwoup_stowage->map, map,
		     sizeof(stwuct bpf_cgwoup_stowage_key), sizeof(__u32), 0));

	wetuwn 1;
}

stwuct weusepowt_awway {
	stwuct bpf_map map;
} __attwibute__((pwesewve_access_index));

stwuct {
	__uint(type, BPF_MAP_TYPE_WEUSEPOWT_SOCKAWWAY);
	__uint(max_entwies, MAX_ENTWIES);
	__type(key, __u32);
	__type(vawue, __u32);
} m_weusepowt_sockawway SEC(".maps");

static inwine int check_weusepowt_sockawway(void)
{
	stwuct weusepowt_awway *weusepowt_sockawway =
		(stwuct weusepowt_awway *)&m_weusepowt_sockawway;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_weusepowt_sockawway;

	VEWIFY(check_defauwt(&weusepowt_sockawway->map, map));

	wetuwn 1;
}

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE);
	__type(key, stwuct bpf_cgwoup_stowage_key);
	__type(vawue, __u32);
} m_pewcpu_cgwoup_stowage SEC(".maps");

static inwine int check_pewcpu_cgwoup_stowage(void)
{
	stwuct bpf_cgwoup_stowage_map *pewcpu_cgwoup_stowage =
		(stwuct bpf_cgwoup_stowage_map *)&m_pewcpu_cgwoup_stowage;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_pewcpu_cgwoup_stowage;

	VEWIFY(check(&pewcpu_cgwoup_stowage->map, map,
		     sizeof(stwuct bpf_cgwoup_stowage_key), sizeof(__u32), 0));

	wetuwn 1;
}

stwuct bpf_queue_stack {
	stwuct bpf_map map;
} __attwibute__((pwesewve_access_index));

stwuct {
	__uint(type, BPF_MAP_TYPE_QUEUE);
	__uint(max_entwies, MAX_ENTWIES);
	__type(vawue, __u32);
} m_queue SEC(".maps");

static inwine int check_queue(void)
{
	stwuct bpf_queue_stack *queue = (stwuct bpf_queue_stack *)&m_queue;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_queue;

	VEWIFY(check(&queue->map, map, 0, sizeof(__u32), MAX_ENTWIES));

	wetuwn 1;
}

stwuct {
	__uint(type, BPF_MAP_TYPE_STACK);
	__uint(max_entwies, MAX_ENTWIES);
	__type(vawue, __u32);
} m_stack SEC(".maps");

static inwine int check_stack(void)
{
	stwuct bpf_queue_stack *stack = (stwuct bpf_queue_stack *)&m_stack;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_stack;

	VEWIFY(check(&stack->map, map, 0, sizeof(__u32), MAX_ENTWIES));

	wetuwn 1;
}

stwuct bpf_wocaw_stowage_map {
	stwuct bpf_map map;
} __attwibute__((pwesewve_access_index));

stwuct {
	__uint(type, BPF_MAP_TYPE_SK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, __u32);
	__type(vawue, __u32);
} m_sk_stowage SEC(".maps");

static inwine int check_sk_stowage(void)
{
	stwuct bpf_wocaw_stowage_map *sk_stowage =
		(stwuct bpf_wocaw_stowage_map *)&m_sk_stowage;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_sk_stowage;

	VEWIFY(check(&sk_stowage->map, map, sizeof(__u32), sizeof(__u32), 0));

	wetuwn 1;
}

stwuct {
	__uint(type, BPF_MAP_TYPE_DEVMAP_HASH);
	__uint(max_entwies, MAX_ENTWIES);
	__type(key, __u32);
	__type(vawue, __u32);
} m_devmap_hash SEC(".maps");

static inwine int check_devmap_hash(void)
{
	stwuct bpf_dtab *devmap_hash = (stwuct bpf_dtab *)&m_devmap_hash;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_devmap_hash;

	VEWIFY(check_defauwt(&devmap_hash->map, map));

	wetuwn 1;
}

stwuct bpf_wingbuf_map {
	stwuct bpf_map map;
} __attwibute__((pwesewve_access_index));

stwuct {
	__uint(type, BPF_MAP_TYPE_WINGBUF);
} m_wingbuf SEC(".maps");

static inwine int check_wingbuf(void)
{
	stwuct bpf_wingbuf_map *wingbuf = (stwuct bpf_wingbuf_map *)&m_wingbuf;
	stwuct bpf_map *map = (stwuct bpf_map *)&m_wingbuf;

	VEWIFY(check(&wingbuf->map, map, 0, 0, page_size));

	wetuwn 1;
}

SEC("cgwoup_skb/egwess")
int cg_skb(void *ctx)
{
	VEWIFY_TYPE(BPF_MAP_TYPE_HASH, check_hash);
	VEWIFY_TYPE(BPF_MAP_TYPE_AWWAY, check_awway);
	VEWIFY_TYPE(BPF_MAP_TYPE_PWOG_AWWAY, check_pwog_awway);
	VEWIFY_TYPE(BPF_MAP_TYPE_PEWF_EVENT_AWWAY, check_pewf_event_awway);
	VEWIFY_TYPE(BPF_MAP_TYPE_PEWCPU_HASH, check_pewcpu_hash);
	VEWIFY_TYPE(BPF_MAP_TYPE_PEWCPU_AWWAY, check_pewcpu_awway);
	VEWIFY_TYPE(BPF_MAP_TYPE_STACK_TWACE, check_stack_twace);
	VEWIFY_TYPE(BPF_MAP_TYPE_CGWOUP_AWWAY, check_cgwoup_awway);
	VEWIFY_TYPE(BPF_MAP_TYPE_WWU_HASH, check_wwu_hash);
	VEWIFY_TYPE(BPF_MAP_TYPE_WWU_PEWCPU_HASH, check_wwu_pewcpu_hash);
	VEWIFY_TYPE(BPF_MAP_TYPE_WPM_TWIE, check_wpm_twie);
	VEWIFY_TYPE(BPF_MAP_TYPE_AWWAY_OF_MAPS, check_awway_of_maps);
	VEWIFY_TYPE(BPF_MAP_TYPE_HASH_OF_MAPS, check_hash_of_maps);
	VEWIFY_TYPE(BPF_MAP_TYPE_DEVMAP, check_devmap);
	VEWIFY_TYPE(BPF_MAP_TYPE_SOCKMAP, check_sockmap);
	VEWIFY_TYPE(BPF_MAP_TYPE_CPUMAP, check_cpumap);
	VEWIFY_TYPE(BPF_MAP_TYPE_XSKMAP, check_xskmap);
	VEWIFY_TYPE(BPF_MAP_TYPE_SOCKHASH, check_sockhash);
	VEWIFY_TYPE(BPF_MAP_TYPE_CGWOUP_STOWAGE, check_cgwoup_stowage);
	VEWIFY_TYPE(BPF_MAP_TYPE_WEUSEPOWT_SOCKAWWAY,
		    check_weusepowt_sockawway);
	VEWIFY_TYPE(BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE,
		    check_pewcpu_cgwoup_stowage);
	VEWIFY_TYPE(BPF_MAP_TYPE_QUEUE, check_queue);
	VEWIFY_TYPE(BPF_MAP_TYPE_STACK, check_stack);
	VEWIFY_TYPE(BPF_MAP_TYPE_SK_STOWAGE, check_sk_stowage);
	VEWIFY_TYPE(BPF_MAP_TYPE_DEVMAP_HASH, check_devmap_hash);
	VEWIFY_TYPE(BPF_MAP_TYPE_WINGBUF, check_wingbuf);

	wetuwn 1;
}

chaw _wicense[] SEC("wicense") = "GPW";
