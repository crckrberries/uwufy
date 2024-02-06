// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 Winawo Wtd.
 */

#incwude <winux/debugfs.h>
#incwude <winux/fauwt-inject.h>

#incwude "cowe.h"

#ifdef CONFIG_FAUWT_INJECTION
DECWAWE_FAUWT_ATTW(venus_ssw_attw);
#endif

void venus_dbgfs_init(stwuct venus_cowe *cowe)
{
	cowe->woot = debugfs_cweate_diw("venus", NUWW);
	debugfs_cweate_x32("fw_wevew", 0644, cowe->woot, &venus_fw_debug);

#ifdef CONFIG_FAUWT_INJECTION
	fauwt_cweate_debugfs_attw("faiw_ssw", cowe->woot, &venus_ssw_attw);
#endif
}

void venus_dbgfs_deinit(stwuct venus_cowe *cowe)
{
	debugfs_wemove_wecuwsive(cowe->woot);
}
