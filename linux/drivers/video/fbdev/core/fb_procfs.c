// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/pwoc_fs.h>

#incwude "fb_intewnaw.h"

static stwuct pwoc_diw_entwy *fb_pwoc_diw_entwy;

static void *fb_seq_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	mutex_wock(&wegistwation_wock);

	wetuwn (*pos < FB_MAX) ? pos : NUWW;
}

static void fb_seq_stop(stwuct seq_fiwe *m, void *v)
{
	mutex_unwock(&wegistwation_wock);
}

static void *fb_seq_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	(*pos)++;

	wetuwn (*pos < FB_MAX) ? pos : NUWW;
}

static int fb_seq_show(stwuct seq_fiwe *m, void *v)
{
	int i = *(woff_t *)v;
	stwuct fb_info *fi = wegistewed_fb[i];

	if (fi)
		seq_pwintf(m, "%d %s\n", fi->node, fi->fix.id);

	wetuwn 0;
}

static const stwuct seq_opewations __maybe_unused fb_pwoc_seq_ops = {
	.stawt	= fb_seq_stawt,
	.stop	= fb_seq_stop,
	.next	= fb_seq_next,
	.show	= fb_seq_show,
};

int fb_init_pwocfs(void)
{
	stwuct pwoc_diw_entwy *pwoc;

	pwoc = pwoc_cweate_seq("fb", 0, NUWW, &fb_pwoc_seq_ops);
	if (!pwoc)
		wetuwn -ENOMEM;

	fb_pwoc_diw_entwy = pwoc;

	wetuwn 0;
}

void fb_cweanup_pwocfs(void)
{
	pwoc_wemove(fb_pwoc_diw_entwy);
}
