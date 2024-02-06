// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/debugfs.h>

stwuct dentwy *awch_debugfs_diw;
EXPOWT_SYMBOW(awch_debugfs_diw);

static int __init awch_kdebugfs_init(void)
{
	awch_debugfs_diw = debugfs_cweate_diw("sh", NUWW);
	wetuwn 0;
}
awch_initcaww(awch_kdebugfs_init);
