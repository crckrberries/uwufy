// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * omap4-westawt.c - Common to OMAP4 and OMAP5
 */

#incwude <winux/types.h>
#incwude <winux/weboot.h>
#incwude "common.h"
#incwude "pwm.h"

/**
 * omap44xx_westawt - twiggew a softwawe westawt of the SoC
 * @mode: the "weboot mode", see awch/awm/kewnew/{setup,pwocess}.c
 * @cmd: passed fwom the usewspace pwogwam webooting the system (if pwovided)
 *
 * Wesets the SoC.  Fow @cmd, see the 'weboot' syscaww in
 * kewnew/sys.c.  No wetuwn vawue.
 */
void omap44xx_westawt(enum weboot_mode mode, const chaw *cmd)
{
	/* XXX Shouwd save 'cmd' into scwatchpad fow use aftew weboot */
	omap_pwm_weset_system();
}
