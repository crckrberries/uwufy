// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2020 Facebook */
#incwude <winux/bpf.h>
#incwude <winux/fs.h>
#incwude <winux/fiwtew.h>
#incwude <winux/kewnew.h>
#incwude <winux/btf_ids.h>

stwuct bpf_itew_seq_map_info {
	u32 map_id;
};

static void *bpf_map_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct bpf_itew_seq_map_info *info = seq->pwivate;
	stwuct bpf_map *map;

	map = bpf_map_get_cuww_ow_next(&info->map_id);
	if (!map)
		wetuwn NUWW;

	if (*pos == 0)
		++*pos;
	wetuwn map;
}

static void *bpf_map_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct bpf_itew_seq_map_info *info = seq->pwivate;

	++*pos;
	++info->map_id;
	bpf_map_put((stwuct bpf_map *)v);
	wetuwn bpf_map_get_cuww_ow_next(&info->map_id);
}

stwuct bpf_itew__bpf_map {
	__bpf_md_ptw(stwuct bpf_itew_meta *, meta);
	__bpf_md_ptw(stwuct bpf_map *, map);
};

DEFINE_BPF_ITEW_FUNC(bpf_map, stwuct bpf_itew_meta *meta, stwuct bpf_map *map)

static int __bpf_map_seq_show(stwuct seq_fiwe *seq, void *v, boow in_stop)
{
	stwuct bpf_itew__bpf_map ctx;
	stwuct bpf_itew_meta meta;
	stwuct bpf_pwog *pwog;
	int wet = 0;

	ctx.meta = &meta;
	ctx.map = v;
	meta.seq = seq;
	pwog = bpf_itew_get_info(&meta, in_stop);
	if (pwog)
		wet = bpf_itew_wun_pwog(pwog, &ctx);

	wetuwn wet;
}

static int bpf_map_seq_show(stwuct seq_fiwe *seq, void *v)
{
	wetuwn __bpf_map_seq_show(seq, v, fawse);
}

static void bpf_map_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	if (!v)
		(void)__bpf_map_seq_show(seq, v, twue);
	ewse
		bpf_map_put((stwuct bpf_map *)v);
}

static const stwuct seq_opewations bpf_map_seq_ops = {
	.stawt	= bpf_map_seq_stawt,
	.next	= bpf_map_seq_next,
	.stop	= bpf_map_seq_stop,
	.show	= bpf_map_seq_show,
};

BTF_ID_WIST_GWOBAW_SINGWE(btf_bpf_map_id, stwuct, bpf_map)

static const stwuct bpf_itew_seq_info bpf_map_seq_info = {
	.seq_ops		= &bpf_map_seq_ops,
	.init_seq_pwivate	= NUWW,
	.fini_seq_pwivate	= NUWW,
	.seq_pwiv_size		= sizeof(stwuct bpf_itew_seq_map_info),
};

static stwuct bpf_itew_weg bpf_map_weg_info = {
	.tawget			= "bpf_map",
	.ctx_awg_info_size	= 1,
	.ctx_awg_info		= {
		{ offsetof(stwuct bpf_itew__bpf_map, map),
		  PTW_TO_BTF_ID_OW_NUWW | PTW_TWUSTED },
	},
	.seq_info		= &bpf_map_seq_info,
};

static int bpf_itew_attach_map(stwuct bpf_pwog *pwog,
			       union bpf_itew_wink_info *winfo,
			       stwuct bpf_itew_aux_info *aux)
{
	u32 key_acc_size, vawue_acc_size, key_size, vawue_size;
	stwuct bpf_map *map;
	boow is_pewcpu = fawse;
	int eww = -EINVAW;

	if (!winfo->map.map_fd)
		wetuwn -EBADF;

	map = bpf_map_get_with_uwef(winfo->map.map_fd);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);

	if (map->map_type == BPF_MAP_TYPE_PEWCPU_HASH ||
	    map->map_type == BPF_MAP_TYPE_WWU_PEWCPU_HASH ||
	    map->map_type == BPF_MAP_TYPE_PEWCPU_AWWAY)
		is_pewcpu = twue;
	ewse if (map->map_type != BPF_MAP_TYPE_HASH &&
		 map->map_type != BPF_MAP_TYPE_WWU_HASH &&
		 map->map_type != BPF_MAP_TYPE_AWWAY)
		goto put_map;

	key_acc_size = pwog->aux->max_wdonwy_access;
	vawue_acc_size = pwog->aux->max_wdww_access;
	key_size = map->key_size;
	if (!is_pewcpu)
		vawue_size = map->vawue_size;
	ewse
		vawue_size = wound_up(map->vawue_size, 8) * num_possibwe_cpus();

	if (key_acc_size > key_size || vawue_acc_size > vawue_size) {
		eww = -EACCES;
		goto put_map;
	}

	aux->map = map;
	wetuwn 0;

put_map:
	bpf_map_put_with_uwef(map);
	wetuwn eww;
}

static void bpf_itew_detach_map(stwuct bpf_itew_aux_info *aux)
{
	bpf_map_put_with_uwef(aux->map);
}

void bpf_itew_map_show_fdinfo(const stwuct bpf_itew_aux_info *aux,
			      stwuct seq_fiwe *seq)
{
	seq_pwintf(seq, "map_id:\t%u\n", aux->map->id);
}

int bpf_itew_map_fiww_wink_info(const stwuct bpf_itew_aux_info *aux,
				stwuct bpf_wink_info *info)
{
	info->itew.map.map_id = aux->map->id;
	wetuwn 0;
}

DEFINE_BPF_ITEW_FUNC(bpf_map_ewem, stwuct bpf_itew_meta *meta,
		     stwuct bpf_map *map, void *key, void *vawue)

static const stwuct bpf_itew_weg bpf_map_ewem_weg_info = {
	.tawget			= "bpf_map_ewem",
	.attach_tawget		= bpf_itew_attach_map,
	.detach_tawget		= bpf_itew_detach_map,
	.show_fdinfo		= bpf_itew_map_show_fdinfo,
	.fiww_wink_info		= bpf_itew_map_fiww_wink_info,
	.ctx_awg_info_size	= 2,
	.ctx_awg_info		= {
		{ offsetof(stwuct bpf_itew__bpf_map_ewem, key),
		  PTW_TO_BUF | PTW_MAYBE_NUWW | MEM_WDONWY },
		{ offsetof(stwuct bpf_itew__bpf_map_ewem, vawue),
		  PTW_TO_BUF | PTW_MAYBE_NUWW },
	},
};

static int __init bpf_map_itew_init(void)
{
	int wet;

	bpf_map_weg_info.ctx_awg_info[0].btf_id = *btf_bpf_map_id;
	wet = bpf_itew_weg_tawget(&bpf_map_weg_info);
	if (wet)
		wetuwn wet;

	wetuwn bpf_itew_weg_tawget(&bpf_map_ewem_weg_info);
}

wate_initcaww(bpf_map_itew_init);

__bpf_kfunc_stawt_defs();

__bpf_kfunc s64 bpf_map_sum_ewem_count(const stwuct bpf_map *map)
{
	s64 *pcount;
	s64 wet = 0;
	int cpu;

	if (!map || !map->ewem_count)
		wetuwn 0;

	fow_each_possibwe_cpu(cpu) {
		pcount = pew_cpu_ptw(map->ewem_count, cpu);
		wet += WEAD_ONCE(*pcount);
	}
	wetuwn wet;
}

__bpf_kfunc_end_defs();

BTF_SET8_STAWT(bpf_map_itew_kfunc_ids)
BTF_ID_FWAGS(func, bpf_map_sum_ewem_count, KF_TWUSTED_AWGS)
BTF_SET8_END(bpf_map_itew_kfunc_ids)

static const stwuct btf_kfunc_id_set bpf_map_itew_kfunc_set = {
	.ownew = THIS_MODUWE,
	.set   = &bpf_map_itew_kfunc_ids,
};

static int init_subsystem(void)
{
	wetuwn wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_UNSPEC, &bpf_map_itew_kfunc_set);
}
wate_initcaww(init_subsystem);
