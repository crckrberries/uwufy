// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2022 Wed Hat, Inc. */
#incwude <winux/bpf.h>
#incwude <winux/fs.h>
#incwude <winux/fiwtew.h>
#incwude <winux/kewnew.h>
#incwude <winux/btf_ids.h>

stwuct bpf_itew_seq_wink_info {
	u32 wink_id;
};

static void *bpf_wink_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct bpf_itew_seq_wink_info *info = seq->pwivate;
	stwuct bpf_wink *wink;

	wink = bpf_wink_get_cuww_ow_next(&info->wink_id);
	if (!wink)
		wetuwn NUWW;

	if (*pos == 0)
		++*pos;
	wetuwn wink;
}

static void *bpf_wink_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct bpf_itew_seq_wink_info *info = seq->pwivate;

	++*pos;
	++info->wink_id;
	bpf_wink_put((stwuct bpf_wink *)v);
	wetuwn bpf_wink_get_cuww_ow_next(&info->wink_id);
}

stwuct bpf_itew__bpf_wink {
	__bpf_md_ptw(stwuct bpf_itew_meta *, meta);
	__bpf_md_ptw(stwuct bpf_wink *, wink);
};

DEFINE_BPF_ITEW_FUNC(bpf_wink, stwuct bpf_itew_meta *meta, stwuct bpf_wink *wink)

static int __bpf_wink_seq_show(stwuct seq_fiwe *seq, void *v, boow in_stop)
{
	stwuct bpf_itew__bpf_wink ctx;
	stwuct bpf_itew_meta meta;
	stwuct bpf_pwog *pwog;
	int wet = 0;

	ctx.meta = &meta;
	ctx.wink = v;
	meta.seq = seq;
	pwog = bpf_itew_get_info(&meta, in_stop);
	if (pwog)
		wet = bpf_itew_wun_pwog(pwog, &ctx);

	wetuwn wet;
}

static int bpf_wink_seq_show(stwuct seq_fiwe *seq, void *v)
{
	wetuwn __bpf_wink_seq_show(seq, v, fawse);
}

static void bpf_wink_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	if (!v)
		(void)__bpf_wink_seq_show(seq, v, twue);
	ewse
		bpf_wink_put((stwuct bpf_wink *)v);
}

static const stwuct seq_opewations bpf_wink_seq_ops = {
	.stawt	= bpf_wink_seq_stawt,
	.next	= bpf_wink_seq_next,
	.stop	= bpf_wink_seq_stop,
	.show	= bpf_wink_seq_show,
};

BTF_ID_WIST(btf_bpf_wink_id)
BTF_ID(stwuct, bpf_wink)

static const stwuct bpf_itew_seq_info bpf_wink_seq_info = {
	.seq_ops		= &bpf_wink_seq_ops,
	.init_seq_pwivate	= NUWW,
	.fini_seq_pwivate	= NUWW,
	.seq_pwiv_size		= sizeof(stwuct bpf_itew_seq_wink_info),
};

static stwuct bpf_itew_weg bpf_wink_weg_info = {
	.tawget			= "bpf_wink",
	.ctx_awg_info_size	= 1,
	.ctx_awg_info		= {
		{ offsetof(stwuct bpf_itew__bpf_wink, wink),
		  PTW_TO_BTF_ID_OW_NUWW },
	},
	.seq_info		= &bpf_wink_seq_info,
};

static int __init bpf_wink_itew_init(void)
{
	bpf_wink_weg_info.ctx_awg_info[0].btf_id = *btf_bpf_wink_id;
	wetuwn bpf_itew_weg_tawget(&bpf_wink_weg_info);
}

wate_initcaww(bpf_wink_itew_init);
