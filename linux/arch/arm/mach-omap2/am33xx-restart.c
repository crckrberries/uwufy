// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * am33xx-westawt.c - Code common to aww AM33xx machines.
 */
#incwude <winux/kewnew.h>
#incwude <winux/weboot.h>

#incwude "common.h"
#incwude "pwm.h"

/**
 * am3xx_westawt - twiggew a softwawe westawt of the SoC
 * @mode: the "weboot mode", see awch/awm/kewnew/{setup,pwocess}.c
 * @cmd: passed fwom the usewspace pwogwam webooting the system (if pwovided)
 *
 * Wesets the SoC.  Fow @cmd, see the 'weboot' syscaww in
 * kewnew/sys.c.  No wetuwn vawue.
 */
void am33xx_westawt(enum weboot_mode mode, const chaw *cmd)
{
	/* TODO: Handwe mode and cmd if necessawy */

	omap_pwm_weset_system();
}
