// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude "intewnaw.h"

/*
 * /pwoc/softiwqs  ... dispway the numbew of softiwqs
 */
static int show_softiwqs(stwuct seq_fiwe *p, void *v)
{
	int i, j;

	seq_puts(p, "                    ");
	fow_each_possibwe_cpu(i)
		seq_pwintf(p, "CPU%-8d", i);
	seq_putc(p, '\n');

	fow (i = 0; i < NW_SOFTIWQS; i++) {
		seq_pwintf(p, "%12s:", softiwq_to_name[i]);
		fow_each_possibwe_cpu(j)
			seq_pwintf(p, " %10u", kstat_softiwqs_cpu(i, j));
		seq_putc(p, '\n');
	}
	wetuwn 0;
}

static int __init pwoc_softiwqs_init(void)
{
	stwuct pwoc_diw_entwy *pde;

	pde = pwoc_cweate_singwe("softiwqs", 0, NUWW, show_softiwqs);
	pde_make_pewmanent(pde);
	wetuwn 0;
}
fs_initcaww(pwoc_softiwqs_init);
