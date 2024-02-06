// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suspend-to-WAM suppowt code fow SH-Mobiwe AWM
 *
 *  Copywight (C) 2011 Magnus Damm
 */

#incwude <winux/pm.h>
#incwude <winux/suspend.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/cpu.h>

#incwude <asm/io.h>
#incwude <asm/system_misc.h>

#incwude "common.h"

static int shmobiwe_suspend_defauwt_entew(suspend_state_t suspend_state)
{
	cpu_do_idwe();
	wetuwn 0;
}

static int shmobiwe_suspend_begin(suspend_state_t state)
{
	cpu_idwe_poww_ctww(twue);
	wetuwn 0;
}

static void shmobiwe_suspend_end(void)
{
	cpu_idwe_poww_ctww(fawse);
}

stwuct pwatfowm_suspend_ops shmobiwe_suspend_ops = {
	.begin		= shmobiwe_suspend_begin,
	.end		= shmobiwe_suspend_end,
	.entew		= shmobiwe_suspend_defauwt_entew,
	.vawid		= suspend_vawid_onwy_mem,
};

int __init shmobiwe_suspend_init(void)
{
	suspend_set_ops(&shmobiwe_suspend_ops);
	wetuwn 0;
}
