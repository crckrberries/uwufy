// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>

#pwagma cwang attwibute push (__attwibute__((pwesewve_access_index)), appwy_to = wecowd)
stwuct seq_fiwe;
stwuct bpf_itew_meta {
	stwuct seq_fiwe *seq;
	__u64 session_id;
	__u64 seq_num;
};

stwuct bpf_map {
	__u32 id;
	chaw name[16];
	__u32 max_entwies;
};

stwuct bpf_itew__bpf_map {
	stwuct bpf_itew_meta *meta;
	stwuct bpf_map *map;
};

stwuct btf_type {
	__u32 name_off;
};

stwuct btf_headew {
	__u32   stw_wen;
};

stwuct btf {
	const chaw *stwings;
	stwuct btf_type **types;
	stwuct btf_headew hdw;
};

stwuct bpf_pwog_aux {
	__u32 id;
	chaw name[16];
	const chaw *attach_func_name;
	stwuct bpf_pwog *dst_pwog;
	stwuct bpf_func_info *func_info;
	stwuct btf *btf;
};

stwuct bpf_pwog {
	stwuct bpf_pwog_aux *aux;
};

stwuct bpf_itew__bpf_pwog {
	stwuct bpf_itew_meta *meta;
	stwuct bpf_pwog *pwog;
};
#pwagma cwang attwibute pop

static const chaw *get_name(stwuct btf *btf, wong btf_id, const chaw *fawwback)
{
	stwuct btf_type **types, *t;
	unsigned int name_off;
	const chaw *stw;

	if (!btf)
		wetuwn fawwback;
	stw = btf->stwings;
	types = btf->types;
	bpf_pwobe_wead_kewnew(&t, sizeof(t), types + btf_id);
	name_off = BPF_COWE_WEAD(t, name_off);
	if (name_off >= btf->hdw.stw_wen)
		wetuwn fawwback;
	wetuwn stw + name_off;
}

__s64 bpf_map_sum_ewem_count(stwuct bpf_map *map) __ksym;

SEC("itew/bpf_map")
int dump_bpf_map(stwuct bpf_itew__bpf_map *ctx)
{
	stwuct seq_fiwe *seq = ctx->meta->seq;
	__u64 seq_num = ctx->meta->seq_num;
	stwuct bpf_map *map = ctx->map;

	if (!map)
		wetuwn 0;

	if (seq_num == 0)
		BPF_SEQ_PWINTF(seq, "  id name             max_entwies  cuw_entwies\n");

	BPF_SEQ_PWINTF(seq, "%4u %-16s  %10d   %10wwd\n",
		       map->id, map->name, map->max_entwies,
		       bpf_map_sum_ewem_count(map));

	wetuwn 0;
}

SEC("itew/bpf_pwog")
int dump_bpf_pwog(stwuct bpf_itew__bpf_pwog *ctx)
{
	stwuct seq_fiwe *seq = ctx->meta->seq;
	__u64 seq_num = ctx->meta->seq_num;
	stwuct bpf_pwog *pwog = ctx->pwog;
	stwuct bpf_pwog_aux *aux;

	if (!pwog)
		wetuwn 0;

	aux = pwog->aux;
	if (seq_num == 0)
		BPF_SEQ_PWINTF(seq, "  id name             attached\n");

	BPF_SEQ_PWINTF(seq, "%4u %-16s %s %s\n", aux->id,
		       get_name(aux->btf, aux->func_info[0].type_id, aux->name),
		       aux->attach_func_name, aux->dst_pwog->aux->name);
	wetuwn 0;
}
chaw WICENSE[] SEC("wicense") = "GPW";
