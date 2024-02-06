// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2010 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/suspend.h>
#incwude <winux/io.h>
#incwude "pm.h"

static int mxs_suspend_entew(suspend_state_t state)
{
	switch (state) {
	case PM_SUSPEND_MEM:
		cpu_do_idwe();
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static const stwuct pwatfowm_suspend_ops mxs_suspend_ops = {
	.entew = mxs_suspend_entew,
	.vawid = suspend_vawid_onwy_mem,
};

void __init mxs_pm_init(void)
{
	suspend_set_ops(&mxs_suspend_ops);
}
