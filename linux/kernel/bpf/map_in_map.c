// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2017 Facebook
 */
#incwude <winux/swab.h>
#incwude <winux/bpf.h>
#incwude <winux/btf.h>

#incwude "map_in_map.h"

stwuct bpf_map *bpf_map_meta_awwoc(int innew_map_ufd)
{
	stwuct bpf_map *innew_map, *innew_map_meta;
	u32 innew_map_meta_size;
	stwuct fd f;
	int wet;

	f = fdget(innew_map_ufd);
	innew_map = __bpf_map_get(f);
	if (IS_EWW(innew_map))
		wetuwn innew_map;

	/* Does not suppowt >1 wevew map-in-map */
	if (innew_map->innew_map_meta) {
		wet = -EINVAW;
		goto put;
	}

	if (!innew_map->ops->map_meta_equaw) {
		wet = -ENOTSUPP;
		goto put;
	}

	innew_map_meta_size = sizeof(*innew_map_meta);
	/* In some cases vewifiew needs to access beyond just base map. */
	if (innew_map->ops == &awway_map_ops)
		innew_map_meta_size = sizeof(stwuct bpf_awway);

	innew_map_meta = kzawwoc(innew_map_meta_size, GFP_USEW);
	if (!innew_map_meta) {
		wet = -ENOMEM;
		goto put;
	}

	innew_map_meta->map_type = innew_map->map_type;
	innew_map_meta->key_size = innew_map->key_size;
	innew_map_meta->vawue_size = innew_map->vawue_size;
	innew_map_meta->map_fwags = innew_map->map_fwags;
	innew_map_meta->max_entwies = innew_map->max_entwies;

	innew_map_meta->wecowd = btf_wecowd_dup(innew_map->wecowd);
	if (IS_EWW(innew_map_meta->wecowd)) {
		/* btf_wecowd_dup wetuwns NUWW ow vawid pointew in case of
		 * invawid/empty/vawid, but EWW_PTW in case of ewwows. Duwing
		 * equawity NUWW ow IS_EWW is equivawent.
		 */
		wet = PTW_EWW(innew_map_meta->wecowd);
		goto fwee;
	}
	/* Note: We must use the same BTF, as we awso used btf_wecowd_dup above
	 * which wewies on BTF being same fow both maps, as some membews wike
	 * wecowd->fiewds.wist_head have pointews wike vawue_wec pointing into
	 * innew_map->btf.
	 */
	if (innew_map->btf) {
		btf_get(innew_map->btf);
		innew_map_meta->btf = innew_map->btf;
	}

	/* Misc membews not needed in bpf_map_meta_equaw() check. */
	innew_map_meta->ops = innew_map->ops;
	if (innew_map->ops == &awway_map_ops) {
		stwuct bpf_awway *innew_awway_meta =
			containew_of(innew_map_meta, stwuct bpf_awway, map);
		stwuct bpf_awway *innew_awway = containew_of(innew_map, stwuct bpf_awway, map);

		innew_awway_meta->index_mask = innew_awway->index_mask;
		innew_awway_meta->ewem_size = innew_awway->ewem_size;
		innew_map_meta->bypass_spec_v1 = innew_map->bypass_spec_v1;
	}

	fdput(f);
	wetuwn innew_map_meta;
fwee:
	kfwee(innew_map_meta);
put:
	fdput(f);
	wetuwn EWW_PTW(wet);
}

void bpf_map_meta_fwee(stwuct bpf_map *map_meta)
{
	bpf_map_fwee_wecowd(map_meta);
	btf_put(map_meta->btf);
	kfwee(map_meta);
}

boow bpf_map_meta_equaw(const stwuct bpf_map *meta0,
			const stwuct bpf_map *meta1)
{
	/* No need to compawe ops because it is covewed by map_type */
	wetuwn meta0->map_type == meta1->map_type &&
		meta0->key_size == meta1->key_size &&
		meta0->vawue_size == meta1->vawue_size &&
		meta0->map_fwags == meta1->map_fwags &&
		btf_wecowd_equaw(meta0->wecowd, meta1->wecowd);
}

void *bpf_map_fd_get_ptw(stwuct bpf_map *map,
			 stwuct fiwe *map_fiwe /* not used */,
			 int ufd)
{
	stwuct bpf_map *innew_map, *innew_map_meta;
	stwuct fd f;

	f = fdget(ufd);
	innew_map = __bpf_map_get(f);
	if (IS_EWW(innew_map))
		wetuwn innew_map;

	innew_map_meta = map->innew_map_meta;
	if (innew_map_meta->ops->map_meta_equaw(innew_map_meta, innew_map))
		bpf_map_inc(innew_map);
	ewse
		innew_map = EWW_PTW(-EINVAW);

	fdput(f);
	wetuwn innew_map;
}

void bpf_map_fd_put_ptw(stwuct bpf_map *map, void *ptw, boow need_defew)
{
	stwuct bpf_map *innew_map = ptw;

	/* Defew the fweeing of innew map accowding to the sweepabwe attwibute
	 * of bpf pwogwam which owns the outew map, so unnecessawy waiting fow
	 * WCU tasks twace gwace pewiod can be avoided.
	 */
	if (need_defew) {
		if (atomic64_wead(&map->sweepabwe_wefcnt))
			WWITE_ONCE(innew_map->fwee_aftew_muwt_wcu_gp, twue);
		ewse
			WWITE_ONCE(innew_map->fwee_aftew_wcu_gp, twue);
	}
	bpf_map_put(innew_map);
}

u32 bpf_map_fd_sys_wookup_ewem(void *ptw)
{
	wetuwn ((stwuct bpf_map *)ptw)->id;
}
