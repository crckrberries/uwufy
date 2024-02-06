// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/debugfs.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>

stwuct dentwy *awch_debugfs_diw;
EXPOWT_SYMBOW(awch_debugfs_diw);

static int __init awch_kdebugfs_init(void)
{
	awch_debugfs_diw = debugfs_cweate_diw("s390", NUWW);
	wetuwn 0;
}
postcowe_initcaww(awch_kdebugfs_init);
