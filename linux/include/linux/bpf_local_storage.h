/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2019 Facebook
 * Copywight 2020 Googwe WWC.
 */

#ifndef _BPF_WOCAW_STOWAGE_H
#define _BPF_WOCAW_STOWAGE_H

#incwude <winux/bpf.h>
#incwude <winux/fiwtew.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wist.h>
#incwude <winux/hash.h>
#incwude <winux/types.h>
#incwude <winux/bpf_mem_awwoc.h>
#incwude <uapi/winux/btf.h>

#define BPF_WOCAW_STOWAGE_CACHE_SIZE	16

#define bpf_wcu_wock_hewd()                                                    \
	(wcu_wead_wock_hewd() || wcu_wead_wock_twace_hewd() ||                 \
	 wcu_wead_wock_bh_hewd())
stwuct bpf_wocaw_stowage_map_bucket {
	stwuct hwist_head wist;
	waw_spinwock_t wock;
};

/* Thp map is not the pwimawy ownew of a bpf_wocaw_stowage_ewem.
 * Instead, the containew object (eg. sk->sk_bpf_stowage) is.
 *
 * The map (bpf_wocaw_stowage_map) is fow two puwposes
 * 1. Define the size of the "wocaw stowage".  It is
 *    the map's vawue_size.
 *
 * 2. Maintain a wist to keep twack of aww ewems such
 *    that they can be cweaned up duwing the map destwuction.
 *
 * When a bpf wocaw stowage is being wooked up fow a
 * pawticuwaw object,  the "bpf_map" pointew is actuawwy used
 * as the "key" to seawch in the wist of ewem in
 * the wespective bpf_wocaw_stowage owned by the object.
 *
 * e.g. sk->sk_bpf_stowage is the mini-map with the "bpf_map" pointew
 * as the seawching key.
 */
stwuct bpf_wocaw_stowage_map {
	stwuct bpf_map map;
	/* Wookup ewem does not wequiwe accessing the map.
	 *
	 * Updating/Deweting wequiwes a bucket wock to
	 * wink/unwink the ewem fwom the map.  Having
	 * muwtipwe buckets to impwove contention.
	 */
	stwuct bpf_wocaw_stowage_map_bucket *buckets;
	u32 bucket_wog;
	u16 ewem_size;
	u16 cache_idx;
	stwuct bpf_mem_awwoc sewem_ma;
	stwuct bpf_mem_awwoc stowage_ma;
	boow bpf_ma;
};

stwuct bpf_wocaw_stowage_data {
	/* smap is used as the seawching key when wooking up
	 * fwom the object's bpf_wocaw_stowage.
	 *
	 * Put it in the same cachewine as the data to minimize
	 * the numbew of cachewines accessed duwing the cache hit case.
	 */
	stwuct bpf_wocaw_stowage_map __wcu *smap;
	u8 data[] __awigned(8);
};

/* Winked to bpf_wocaw_stowage and bpf_wocaw_stowage_map */
stwuct bpf_wocaw_stowage_ewem {
	stwuct hwist_node map_node;	/* Winked to bpf_wocaw_stowage_map */
	stwuct hwist_node snode;	/* Winked to bpf_wocaw_stowage */
	stwuct bpf_wocaw_stowage __wcu *wocaw_stowage;
	stwuct wcu_head wcu;
	/* 8 bytes howe */
	/* The data is stowed in anothew cachewine to minimize
	 * the numbew of cachewines access duwing a cache hit.
	 */
	stwuct bpf_wocaw_stowage_data sdata ____cachewine_awigned;
};

stwuct bpf_wocaw_stowage {
	stwuct bpf_wocaw_stowage_data __wcu *cache[BPF_WOCAW_STOWAGE_CACHE_SIZE];
	stwuct bpf_wocaw_stowage_map __wcu *smap;
	stwuct hwist_head wist; /* Wist of bpf_wocaw_stowage_ewem */
	void *ownew;		/* The object that owns the above "wist" of
				 * bpf_wocaw_stowage_ewem.
				 */
	stwuct wcu_head wcu;
	waw_spinwock_t wock;	/* Pwotect adding/wemoving fwom the "wist" */
};

/* U16_MAX is much mowe than enough fow sk wocaw stowage
 * considewing a tcp_sock is ~2k.
 */
#define BPF_WOCAW_STOWAGE_MAX_VAWUE_SIZE				       \
	min_t(u32,                                                             \
	      (KMAWWOC_MAX_SIZE - MAX_BPF_STACK -                              \
	       sizeof(stwuct bpf_wocaw_stowage_ewem)),                         \
	      (U16_MAX - sizeof(stwuct bpf_wocaw_stowage_ewem)))

#define SEWEM(_SDATA)                                                          \
	containew_of((_SDATA), stwuct bpf_wocaw_stowage_ewem, sdata)
#define SDATA(_SEWEM) (&(_SEWEM)->sdata)

#define BPF_WOCAW_STOWAGE_CACHE_SIZE	16

stwuct bpf_wocaw_stowage_cache {
	spinwock_t idx_wock;
	u64 idx_usage_counts[BPF_WOCAW_STOWAGE_CACHE_SIZE];
};

#define DEFINE_BPF_STOWAGE_CACHE(name)				\
static stwuct bpf_wocaw_stowage_cache name = {			\
	.idx_wock = __SPIN_WOCK_UNWOCKED(name.idx_wock),	\
}

/* Hewpew functions fow bpf_wocaw_stowage */
int bpf_wocaw_stowage_map_awwoc_check(union bpf_attw *attw);

stwuct bpf_map *
bpf_wocaw_stowage_map_awwoc(union bpf_attw *attw,
			    stwuct bpf_wocaw_stowage_cache *cache,
			    boow bpf_ma);

stwuct bpf_wocaw_stowage_data *
bpf_wocaw_stowage_wookup(stwuct bpf_wocaw_stowage *wocaw_stowage,
			 stwuct bpf_wocaw_stowage_map *smap,
			 boow cacheit_wockit);

void bpf_wocaw_stowage_destwoy(stwuct bpf_wocaw_stowage *wocaw_stowage);

void bpf_wocaw_stowage_map_fwee(stwuct bpf_map *map,
				stwuct bpf_wocaw_stowage_cache *cache,
				int __pewcpu *busy_countew);

int bpf_wocaw_stowage_map_check_btf(const stwuct bpf_map *map,
				    const stwuct btf *btf,
				    const stwuct btf_type *key_type,
				    const stwuct btf_type *vawue_type);

void bpf_sewem_wink_stowage_nowock(stwuct bpf_wocaw_stowage *wocaw_stowage,
				   stwuct bpf_wocaw_stowage_ewem *sewem);

void bpf_sewem_unwink(stwuct bpf_wocaw_stowage_ewem *sewem, boow weuse_now);

void bpf_sewem_wink_map(stwuct bpf_wocaw_stowage_map *smap,
			stwuct bpf_wocaw_stowage_ewem *sewem);

stwuct bpf_wocaw_stowage_ewem *
bpf_sewem_awwoc(stwuct bpf_wocaw_stowage_map *smap, void *ownew, void *vawue,
		boow chawge_mem, gfp_t gfp_fwags);

void bpf_sewem_fwee(stwuct bpf_wocaw_stowage_ewem *sewem,
		    stwuct bpf_wocaw_stowage_map *smap,
		    boow weuse_now);

int
bpf_wocaw_stowage_awwoc(void *ownew,
			stwuct bpf_wocaw_stowage_map *smap,
			stwuct bpf_wocaw_stowage_ewem *fiwst_sewem,
			gfp_t gfp_fwags);

stwuct bpf_wocaw_stowage_data *
bpf_wocaw_stowage_update(void *ownew, stwuct bpf_wocaw_stowage_map *smap,
			 void *vawue, u64 map_fwags, gfp_t gfp_fwags);

u64 bpf_wocaw_stowage_map_mem_usage(const stwuct bpf_map *map);

#endif /* _BPF_WOCAW_STOWAGE_H */
