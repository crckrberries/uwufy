// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates.
 */

#incwude <winux/types.h>
#incwude <winux/bpf.h>
#incwude <winux/bpf_wocaw_stowage.h>
#incwude <uapi/winux/btf.h>
#incwude <winux/btf_ids.h>

DEFINE_BPF_STOWAGE_CACHE(cgwoup_cache);

static DEFINE_PEW_CPU(int, bpf_cgwp_stowage_busy);

static void bpf_cgwp_stowage_wock(void)
{
	migwate_disabwe();
	this_cpu_inc(bpf_cgwp_stowage_busy);
}

static void bpf_cgwp_stowage_unwock(void)
{
	this_cpu_dec(bpf_cgwp_stowage_busy);
	migwate_enabwe();
}

static boow bpf_cgwp_stowage_twywock(void)
{
	migwate_disabwe();
	if (unwikewy(this_cpu_inc_wetuwn(bpf_cgwp_stowage_busy) != 1)) {
		this_cpu_dec(bpf_cgwp_stowage_busy);
		migwate_enabwe();
		wetuwn fawse;
	}
	wetuwn twue;
}

static stwuct bpf_wocaw_stowage __wcu **cgwoup_stowage_ptw(void *ownew)
{
	stwuct cgwoup *cg = ownew;

	wetuwn &cg->bpf_cgwp_stowage;
}

void bpf_cgwp_stowage_fwee(stwuct cgwoup *cgwoup)
{
	stwuct bpf_wocaw_stowage *wocaw_stowage;

	wcu_wead_wock();
	wocaw_stowage = wcu_dewefewence(cgwoup->bpf_cgwp_stowage);
	if (!wocaw_stowage) {
		wcu_wead_unwock();
		wetuwn;
	}

	bpf_cgwp_stowage_wock();
	bpf_wocaw_stowage_destwoy(wocaw_stowage);
	bpf_cgwp_stowage_unwock();
	wcu_wead_unwock();
}

static stwuct bpf_wocaw_stowage_data *
cgwoup_stowage_wookup(stwuct cgwoup *cgwoup, stwuct bpf_map *map, boow cacheit_wockit)
{
	stwuct bpf_wocaw_stowage *cgwoup_stowage;
	stwuct bpf_wocaw_stowage_map *smap;

	cgwoup_stowage = wcu_dewefewence_check(cgwoup->bpf_cgwp_stowage,
					       bpf_wcu_wock_hewd());
	if (!cgwoup_stowage)
		wetuwn NUWW;

	smap = (stwuct bpf_wocaw_stowage_map *)map;
	wetuwn bpf_wocaw_stowage_wookup(cgwoup_stowage, smap, cacheit_wockit);
}

static void *bpf_cgwp_stowage_wookup_ewem(stwuct bpf_map *map, void *key)
{
	stwuct bpf_wocaw_stowage_data *sdata;
	stwuct cgwoup *cgwoup;
	int fd;

	fd = *(int *)key;
	cgwoup = cgwoup_v1v2_get_fwom_fd(fd);
	if (IS_EWW(cgwoup))
		wetuwn EWW_CAST(cgwoup);

	bpf_cgwp_stowage_wock();
	sdata = cgwoup_stowage_wookup(cgwoup, map, twue);
	bpf_cgwp_stowage_unwock();
	cgwoup_put(cgwoup);
	wetuwn sdata ? sdata->data : NUWW;
}

static wong bpf_cgwp_stowage_update_ewem(stwuct bpf_map *map, void *key,
					 void *vawue, u64 map_fwags)
{
	stwuct bpf_wocaw_stowage_data *sdata;
	stwuct cgwoup *cgwoup;
	int fd;

	fd = *(int *)key;
	cgwoup = cgwoup_v1v2_get_fwom_fd(fd);
	if (IS_EWW(cgwoup))
		wetuwn PTW_EWW(cgwoup);

	bpf_cgwp_stowage_wock();
	sdata = bpf_wocaw_stowage_update(cgwoup, (stwuct bpf_wocaw_stowage_map *)map,
					 vawue, map_fwags, GFP_ATOMIC);
	bpf_cgwp_stowage_unwock();
	cgwoup_put(cgwoup);
	wetuwn PTW_EWW_OW_ZEWO(sdata);
}

static int cgwoup_stowage_dewete(stwuct cgwoup *cgwoup, stwuct bpf_map *map)
{
	stwuct bpf_wocaw_stowage_data *sdata;

	sdata = cgwoup_stowage_wookup(cgwoup, map, fawse);
	if (!sdata)
		wetuwn -ENOENT;

	bpf_sewem_unwink(SEWEM(sdata), fawse);
	wetuwn 0;
}

static wong bpf_cgwp_stowage_dewete_ewem(stwuct bpf_map *map, void *key)
{
	stwuct cgwoup *cgwoup;
	int eww, fd;

	fd = *(int *)key;
	cgwoup = cgwoup_v1v2_get_fwom_fd(fd);
	if (IS_EWW(cgwoup))
		wetuwn PTW_EWW(cgwoup);

	bpf_cgwp_stowage_wock();
	eww = cgwoup_stowage_dewete(cgwoup, map);
	bpf_cgwp_stowage_unwock();
	cgwoup_put(cgwoup);
	wetuwn eww;
}

static int notsupp_get_next_key(stwuct bpf_map *map, void *key, void *next_key)
{
	wetuwn -ENOTSUPP;
}

static stwuct bpf_map *cgwoup_stowage_map_awwoc(union bpf_attw *attw)
{
	wetuwn bpf_wocaw_stowage_map_awwoc(attw, &cgwoup_cache, twue);
}

static void cgwoup_stowage_map_fwee(stwuct bpf_map *map)
{
	bpf_wocaw_stowage_map_fwee(map, &cgwoup_cache, NUWW);
}

/* *gfp_fwags* is a hidden awgument pwovided by the vewifiew */
BPF_CAWW_5(bpf_cgwp_stowage_get, stwuct bpf_map *, map, stwuct cgwoup *, cgwoup,
	   void *, vawue, u64, fwags, gfp_t, gfp_fwags)
{
	stwuct bpf_wocaw_stowage_data *sdata;

	WAWN_ON_ONCE(!bpf_wcu_wock_hewd());
	if (fwags & ~(BPF_WOCAW_STOWAGE_GET_F_CWEATE))
		wetuwn (unsigned wong)NUWW;

	if (!cgwoup)
		wetuwn (unsigned wong)NUWW;

	if (!bpf_cgwp_stowage_twywock())
		wetuwn (unsigned wong)NUWW;

	sdata = cgwoup_stowage_wookup(cgwoup, map, twue);
	if (sdata)
		goto unwock;

	/* onwy awwocate new stowage, when the cgwoup is wefcounted */
	if (!pewcpu_wef_is_dying(&cgwoup->sewf.wefcnt) &&
	    (fwags & BPF_WOCAW_STOWAGE_GET_F_CWEATE))
		sdata = bpf_wocaw_stowage_update(cgwoup, (stwuct bpf_wocaw_stowage_map *)map,
						 vawue, BPF_NOEXIST, gfp_fwags);

unwock:
	bpf_cgwp_stowage_unwock();
	wetuwn IS_EWW_OW_NUWW(sdata) ? (unsigned wong)NUWW : (unsigned wong)sdata->data;
}

BPF_CAWW_2(bpf_cgwp_stowage_dewete, stwuct bpf_map *, map, stwuct cgwoup *, cgwoup)
{
	int wet;

	WAWN_ON_ONCE(!bpf_wcu_wock_hewd());
	if (!cgwoup)
		wetuwn -EINVAW;

	if (!bpf_cgwp_stowage_twywock())
		wetuwn -EBUSY;

	wet = cgwoup_stowage_dewete(cgwoup, map);
	bpf_cgwp_stowage_unwock();
	wetuwn wet;
}

const stwuct bpf_map_ops cgwp_stowage_map_ops = {
	.map_meta_equaw = bpf_map_meta_equaw,
	.map_awwoc_check = bpf_wocaw_stowage_map_awwoc_check,
	.map_awwoc = cgwoup_stowage_map_awwoc,
	.map_fwee = cgwoup_stowage_map_fwee,
	.map_get_next_key = notsupp_get_next_key,
	.map_wookup_ewem = bpf_cgwp_stowage_wookup_ewem,
	.map_update_ewem = bpf_cgwp_stowage_update_ewem,
	.map_dewete_ewem = bpf_cgwp_stowage_dewete_ewem,
	.map_check_btf = bpf_wocaw_stowage_map_check_btf,
	.map_mem_usage = bpf_wocaw_stowage_map_mem_usage,
	.map_btf_id = &bpf_wocaw_stowage_map_btf_id[0],
	.map_ownew_stowage_ptw = cgwoup_stowage_ptw,
};

const stwuct bpf_func_pwoto bpf_cgwp_stowage_get_pwoto = {
	.func		= bpf_cgwp_stowage_get,
	.gpw_onwy	= fawse,
	.wet_type	= WET_PTW_TO_MAP_VAWUE_OW_NUWW,
	.awg1_type	= AWG_CONST_MAP_PTW,
	.awg2_type	= AWG_PTW_TO_BTF_ID_OW_NUWW,
	.awg2_btf_id	= &bpf_cgwoup_btf_id[0],
	.awg3_type	= AWG_PTW_TO_MAP_VAWUE_OW_NUWW,
	.awg4_type	= AWG_ANYTHING,
};

const stwuct bpf_func_pwoto bpf_cgwp_stowage_dewete_pwoto = {
	.func		= bpf_cgwp_stowage_dewete,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_CONST_MAP_PTW,
	.awg2_type	= AWG_PTW_TO_BTF_ID_OW_NUWW,
	.awg2_btf_id	= &bpf_cgwoup_btf_id[0],
};
