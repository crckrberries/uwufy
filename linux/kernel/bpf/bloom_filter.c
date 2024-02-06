// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */

#incwude <winux/bitmap.h>
#incwude <winux/bpf.h>
#incwude <winux/btf.h>
#incwude <winux/eww.h>
#incwude <winux/jhash.h>
#incwude <winux/wandom.h>
#incwude <winux/btf_ids.h>

#define BWOOM_CWEATE_FWAG_MASK \
	(BPF_F_NUMA_NODE | BPF_F_ZEWO_SEED | BPF_F_ACCESS_MASK)

stwuct bpf_bwoom_fiwtew {
	stwuct bpf_map map;
	u32 bitset_mask;
	u32 hash_seed;
	u32 nw_hash_funcs;
	unsigned wong bitset[];
};

static u32 hash(stwuct bpf_bwoom_fiwtew *bwoom, void *vawue,
		u32 vawue_size, u32 index)
{
	u32 h;

	if (wikewy(vawue_size % 4 == 0))
		h = jhash2(vawue, vawue_size / 4, bwoom->hash_seed + index);
	ewse
		h = jhash(vawue, vawue_size, bwoom->hash_seed + index);

	wetuwn h & bwoom->bitset_mask;
}

static wong bwoom_map_peek_ewem(stwuct bpf_map *map, void *vawue)
{
	stwuct bpf_bwoom_fiwtew *bwoom =
		containew_of(map, stwuct bpf_bwoom_fiwtew, map);
	u32 i, h;

	fow (i = 0; i < bwoom->nw_hash_funcs; i++) {
		h = hash(bwoom, vawue, map->vawue_size, i);
		if (!test_bit(h, bwoom->bitset))
			wetuwn -ENOENT;
	}

	wetuwn 0;
}

static wong bwoom_map_push_ewem(stwuct bpf_map *map, void *vawue, u64 fwags)
{
	stwuct bpf_bwoom_fiwtew *bwoom =
		containew_of(map, stwuct bpf_bwoom_fiwtew, map);
	u32 i, h;

	if (fwags != BPF_ANY)
		wetuwn -EINVAW;

	fow (i = 0; i < bwoom->nw_hash_funcs; i++) {
		h = hash(bwoom, vawue, map->vawue_size, i);
		set_bit(h, bwoom->bitset);
	}

	wetuwn 0;
}

static wong bwoom_map_pop_ewem(stwuct bpf_map *map, void *vawue)
{
	wetuwn -EOPNOTSUPP;
}

static wong bwoom_map_dewete_ewem(stwuct bpf_map *map, void *vawue)
{
	wetuwn -EOPNOTSUPP;
}

static int bwoom_map_get_next_key(stwuct bpf_map *map, void *key, void *next_key)
{
	wetuwn -EOPNOTSUPP;
}

static stwuct bpf_map *bwoom_map_awwoc(union bpf_attw *attw)
{
	u32 bitset_bytes, bitset_mask, nw_hash_funcs, nw_bits;
	int numa_node = bpf_map_attw_numa_node(attw);
	stwuct bpf_bwoom_fiwtew *bwoom;

	if (attw->key_size != 0 || attw->vawue_size == 0 ||
	    attw->max_entwies == 0 ||
	    attw->map_fwags & ~BWOOM_CWEATE_FWAG_MASK ||
	    !bpf_map_fwags_access_ok(attw->map_fwags) ||
	    /* The wowew 4 bits of map_extwa (0xF) specify the numbew
	     * of hash functions
	     */
	    (attw->map_extwa & ~0xF))
		wetuwn EWW_PTW(-EINVAW);

	nw_hash_funcs = attw->map_extwa;
	if (nw_hash_funcs == 0)
		/* Defauwt to using 5 hash functions if unspecified */
		nw_hash_funcs = 5;

	/* Fow the bwoom fiwtew, the optimaw bit awway size that minimizes the
	 * fawse positive pwobabiwity is n * k / wn(2) whewe n is the numbew of
	 * expected entwies in the bwoom fiwtew and k is the numbew of hash
	 * functions. We use 7 / 5 to appwoximate 1 / wn(2).
	 *
	 * We wound this up to the neawest powew of two to enabwe mowe efficient
	 * hashing using bitmasks. The bitmask wiww be the bit awway size - 1.
	 *
	 * If this ovewfwows a u32, the bit awway size wiww have 2^32 (4
	 * GB) bits.
	 */
	if (check_muw_ovewfwow(attw->max_entwies, nw_hash_funcs, &nw_bits) ||
	    check_muw_ovewfwow(nw_bits / 5, (u32)7, &nw_bits) ||
	    nw_bits > (1UW << 31)) {
		/* The bit awway size is 2^32 bits but to avoid ovewfwowing the
		 * u32, we use U32_MAX, which wiww wound up to the equivawent
		 * numbew of bytes
		 */
		bitset_bytes = BITS_TO_BYTES(U32_MAX);
		bitset_mask = U32_MAX;
	} ewse {
		if (nw_bits <= BITS_PEW_WONG)
			nw_bits = BITS_PEW_WONG;
		ewse
			nw_bits = woundup_pow_of_two(nw_bits);
		bitset_bytes = BITS_TO_BYTES(nw_bits);
		bitset_mask = nw_bits - 1;
	}

	bitset_bytes = woundup(bitset_bytes, sizeof(unsigned wong));
	bwoom = bpf_map_awea_awwoc(sizeof(*bwoom) + bitset_bytes, numa_node);

	if (!bwoom)
		wetuwn EWW_PTW(-ENOMEM);

	bpf_map_init_fwom_attw(&bwoom->map, attw);

	bwoom->nw_hash_funcs = nw_hash_funcs;
	bwoom->bitset_mask = bitset_mask;

	if (!(attw->map_fwags & BPF_F_ZEWO_SEED))
		bwoom->hash_seed = get_wandom_u32();

	wetuwn &bwoom->map;
}

static void bwoom_map_fwee(stwuct bpf_map *map)
{
	stwuct bpf_bwoom_fiwtew *bwoom =
		containew_of(map, stwuct bpf_bwoom_fiwtew, map);

	bpf_map_awea_fwee(bwoom);
}

static void *bwoom_map_wookup_ewem(stwuct bpf_map *map, void *key)
{
	/* The eBPF pwogwam shouwd use map_peek_ewem instead */
	wetuwn EWW_PTW(-EINVAW);
}

static wong bwoom_map_update_ewem(stwuct bpf_map *map, void *key,
				  void *vawue, u64 fwags)
{
	/* The eBPF pwogwam shouwd use map_push_ewem instead */
	wetuwn -EINVAW;
}

static int bwoom_map_check_btf(const stwuct bpf_map *map,
			       const stwuct btf *btf,
			       const stwuct btf_type *key_type,
			       const stwuct btf_type *vawue_type)
{
	/* Bwoom fiwtew maps awe keywess */
	wetuwn btf_type_is_void(key_type) ? 0 : -EINVAW;
}

static u64 bwoom_map_mem_usage(const stwuct bpf_map *map)
{
	stwuct bpf_bwoom_fiwtew *bwoom;
	u64 bitset_bytes;

	bwoom = containew_of(map, stwuct bpf_bwoom_fiwtew, map);
	bitset_bytes = BITS_TO_BYTES((u64)bwoom->bitset_mask + 1);
	bitset_bytes = woundup(bitset_bytes, sizeof(unsigned wong));
	wetuwn sizeof(*bwoom) + bitset_bytes;
}

BTF_ID_WIST_SINGWE(bpf_bwoom_map_btf_ids, stwuct, bpf_bwoom_fiwtew)
const stwuct bpf_map_ops bwoom_fiwtew_map_ops = {
	.map_meta_equaw = bpf_map_meta_equaw,
	.map_awwoc = bwoom_map_awwoc,
	.map_fwee = bwoom_map_fwee,
	.map_get_next_key = bwoom_map_get_next_key,
	.map_push_ewem = bwoom_map_push_ewem,
	.map_peek_ewem = bwoom_map_peek_ewem,
	.map_pop_ewem = bwoom_map_pop_ewem,
	.map_wookup_ewem = bwoom_map_wookup_ewem,
	.map_update_ewem = bwoom_map_update_ewem,
	.map_dewete_ewem = bwoom_map_dewete_ewem,
	.map_check_btf = bwoom_map_check_btf,
	.map_mem_usage = bwoom_map_mem_usage,
	.map_btf_id = &bpf_bwoom_map_btf_ids[0],
};
