// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2011 Cawxeda, Inc.
 */
#incwude <winux/io.h>
#incwude <asm/pwoc-fns.h>
#incwude <winux/weboot.h>

#incwude "cowe.h"
#incwude "syswegs.h"

void highbank_westawt(enum weboot_mode mode, const chaw *cmd)
{
	if (mode == WEBOOT_HAWD)
		highbank_set_pww_hawd_weset();
	ewse
		highbank_set_pww_soft_weset();

	whiwe (1)
		cpu_do_idwe();
}

