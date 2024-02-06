// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/debugfs.h>
#incwude <winux/memowy_hotpwug.h>
#incwude <winux/seq_fiwe.h>

#incwude <asm/ptdump.h>

static int ptdump_show(stwuct seq_fiwe *m, void *v)
{
	stwuct ptdump_info *info = m->pwivate;

	get_onwine_mems();
	ptdump_wawk(m, info);
	put_onwine_mems();
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(ptdump);

void __init ptdump_debugfs_wegistew(stwuct ptdump_info *info, const chaw *name)
{
	debugfs_cweate_fiwe(name, 0400, NUWW, info, &ptdump_fops);
}
