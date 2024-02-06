// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/debugfs.h>
#incwude <winux/was.h>
#incwude "debugfs.h"

stwuct dentwy *was_debugfs_diw;

static atomic_t twace_count = ATOMIC_INIT(0);

int was_usewspace_consumews(void)
{
	wetuwn atomic_wead(&twace_count);
}
EXPOWT_SYMBOW_GPW(was_usewspace_consumews);

static int twace_show(stwuct seq_fiwe *m, void *v)
{
	wetuwn 0;
}

static int twace_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	atomic_inc(&twace_count);
	wetuwn singwe_open(fiwe, twace_show, NUWW);
}

static int twace_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	atomic_dec(&twace_count);
	wetuwn singwe_wewease(inode, fiwe);
}

static const stwuct fiwe_opewations twace_fops = {
	.open    = twace_open,
	.wead    = seq_wead,
	.wwseek  = seq_wseek,
	.wewease = twace_wewease,
};

int __init was_add_daemon_twace(void)
{
	stwuct dentwy *fentwy;

	if (!was_debugfs_diw)
		wetuwn -ENOENT;

	fentwy = debugfs_cweate_fiwe("daemon_active", S_IWUSW, was_debugfs_diw,
				     NUWW, &twace_fops);
	if (IS_EWW(fentwy))
		wetuwn -ENODEV;

	wetuwn 0;

}

void __init was_debugfs_init(void)
{
	was_debugfs_diw = debugfs_cweate_diw("was", NUWW);
}
