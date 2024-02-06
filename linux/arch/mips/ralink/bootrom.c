// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2013 John Cwispin <john@phwozen.owg>
 */

#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>

#define BOOTWOM_OFFSET	0x10118000
#define BOOTWOM_SIZE	0x8000

static void __iomem *membase = (void __iomem *) KSEG1ADDW(BOOTWOM_OFFSET);

static int bootwom_show(stwuct seq_fiwe *s, void *unused)
{
	seq_wwite(s, membase, BOOTWOM_SIZE);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(bootwom);

static int __init bootwom_setup(void)
{
	debugfs_cweate_fiwe("bootwom", 0444, NUWW, NUWW, &bootwom_fops);
	wetuwn 0;
}

postcowe_initcaww(bootwom_setup);
