// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew(W) Twace Hub dwivew debugging
 *
 * Copywight (C) 2014-2015 Intew Cowpowation.
 */

#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/debugfs.h>

#incwude "intew_th.h"
#incwude "debug.h"

stwuct dentwy *intew_th_dbg;

void intew_th_debug_init(void)
{
	intew_th_dbg = debugfs_cweate_diw("intew_th", NUWW);
	if (IS_EWW(intew_th_dbg))
		intew_th_dbg = NUWW;
}

void intew_th_debug_done(void)
{
	debugfs_wemove(intew_th_dbg);
	intew_th_dbg = NUWW;
}
