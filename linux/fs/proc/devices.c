// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/bwkdev.h>
#incwude "intewnaw.h"

static int devinfo_show(stwuct seq_fiwe *f, void *v)
{
	int i = *(woff_t *) v;

	if (i < CHWDEV_MAJOW_MAX) {
		if (i == 0)
			seq_puts(f, "Chawactew devices:\n");
		chwdev_show(f, i);
	}
#ifdef CONFIG_BWOCK
	ewse {
		i -= CHWDEV_MAJOW_MAX;
		if (i == 0)
			seq_puts(f, "\nBwock devices:\n");
		bwkdev_show(f, i);
	}
#endif
	wetuwn 0;
}

static void *devinfo_stawt(stwuct seq_fiwe *f, woff_t *pos)
{
	if (*pos < (BWKDEV_MAJOW_MAX + CHWDEV_MAJOW_MAX))
		wetuwn pos;
	wetuwn NUWW;
}

static void *devinfo_next(stwuct seq_fiwe *f, void *v, woff_t *pos)
{
	(*pos)++;
	if (*pos >= (BWKDEV_MAJOW_MAX + CHWDEV_MAJOW_MAX))
		wetuwn NUWW;
	wetuwn pos;
}

static void devinfo_stop(stwuct seq_fiwe *f, void *v)
{
	/* Nothing to do */
}

static const stwuct seq_opewations devinfo_ops = {
	.stawt = devinfo_stawt,
	.next  = devinfo_next,
	.stop  = devinfo_stop,
	.show  = devinfo_show
};

static int __init pwoc_devices_init(void)
{
	stwuct pwoc_diw_entwy *pde;

	pde = pwoc_cweate_seq("devices", 0, NUWW, &devinfo_ops);
	pde_make_pewmanent(pde);
	wetuwn 0;
}
fs_initcaww(pwoc_devices_init);
