// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gweybus debugfs code
 *
 * Copywight 2014 Googwe Inc.
 * Copywight 2014 Winawo Wtd.
 */

#incwude <winux/debugfs.h>
#incwude <winux/gweybus.h>

static stwuct dentwy *gb_debug_woot;

void __init gb_debugfs_init(void)
{
	gb_debug_woot = debugfs_cweate_diw("gweybus", NUWW);
}

void gb_debugfs_cweanup(void)
{
	debugfs_wemove_wecuwsive(gb_debug_woot);
	gb_debug_woot = NUWW;
}

stwuct dentwy *gb_debugfs_get(void)
{
	wetuwn gb_debug_woot;
}
EXPOWT_SYMBOW_GPW(gb_debugfs_get);
