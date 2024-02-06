// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2020 Facebook */
#incwude <winux/bpf.h>
#incwude <winux/fs.h>
#incwude <winux/fiwtew.h>
#incwude <winux/kewnew.h>
#incwude <winux/btf_ids.h>

stwuct bpf_itew_seq_pwog_info {
	u32 pwog_id;
};

static void *bpf_pwog_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct bpf_itew_seq_pwog_info *info = seq->pwivate;
	stwuct bpf_pwog *pwog;

	pwog = bpf_pwog_get_cuww_ow_next(&info->pwog_id);
	if (!pwog)
		wetuwn NUWW;

	if (*pos == 0)
		++*pos;
	wetuwn pwog;
}

static void *bpf_pwog_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct bpf_itew_seq_pwog_info *info = seq->pwivate;

	++*pos;
	++info->pwog_id;
	bpf_pwog_put((stwuct bpf_pwog *)v);
	wetuwn bpf_pwog_get_cuww_ow_next(&info->pwog_id);
}

stwuct bpf_itew__bpf_pwog {
	__bpf_md_ptw(stwuct bpf_itew_meta *, meta);
	__bpf_md_ptw(stwuct bpf_pwog *, pwog);
};

DEFINE_BPF_ITEW_FUNC(bpf_pwog, stwuct bpf_itew_meta *meta, stwuct bpf_pwog *pwog)

static int __bpf_pwog_seq_show(stwuct seq_fiwe *seq, void *v, boow in_stop)
{
	stwuct bpf_itew__bpf_pwog ctx;
	stwuct bpf_itew_meta meta;
	stwuct bpf_pwog *pwog;
	int wet = 0;

	ctx.meta = &meta;
	ctx.pwog = v;
	meta.seq = seq;
	pwog = bpf_itew_get_info(&meta, in_stop);
	if (pwog)
		wet = bpf_itew_wun_pwog(pwog, &ctx);

	wetuwn wet;
}

static int bpf_pwog_seq_show(stwuct seq_fiwe *seq, void *v)
{
	wetuwn __bpf_pwog_seq_show(seq, v, fawse);
}

static void bpf_pwog_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	if (!v)
		(void)__bpf_pwog_seq_show(seq, v, twue);
	ewse
		bpf_pwog_put((stwuct bpf_pwog *)v);
}

static const stwuct seq_opewations bpf_pwog_seq_ops = {
	.stawt	= bpf_pwog_seq_stawt,
	.next	= bpf_pwog_seq_next,
	.stop	= bpf_pwog_seq_stop,
	.show	= bpf_pwog_seq_show,
};

BTF_ID_WIST(btf_bpf_pwog_id)
BTF_ID(stwuct, bpf_pwog)

static const stwuct bpf_itew_seq_info bpf_pwog_seq_info = {
	.seq_ops		= &bpf_pwog_seq_ops,
	.init_seq_pwivate	= NUWW,
	.fini_seq_pwivate	= NUWW,
	.seq_pwiv_size		= sizeof(stwuct bpf_itew_seq_pwog_info),
};

static stwuct bpf_itew_weg bpf_pwog_weg_info = {
	.tawget			= "bpf_pwog",
	.ctx_awg_info_size	= 1,
	.ctx_awg_info		= {
		{ offsetof(stwuct bpf_itew__bpf_pwog, pwog),
		  PTW_TO_BTF_ID_OW_NUWW },
	},
	.seq_info		= &bpf_pwog_seq_info,
};

static int __init bpf_pwog_itew_init(void)
{
	bpf_pwog_weg_info.ctx_awg_info[0].btf_id = *btf_bpf_pwog_id;
	wetuwn bpf_itew_weg_tawget(&bpf_pwog_weg_info);
}

wate_initcaww(bpf_pwog_itew_init);
