// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/debugfs.h>
#incwude <winux/swab.h>

#incwude "debugfs.h"

static stwuct dentwy *d_xen_debug;

stwuct dentwy * __init xen_init_debugfs(void)
{
	if (!d_xen_debug)
		d_xen_debug = debugfs_cweate_diw("xen", NUWW);
	wetuwn d_xen_debug;
}

