// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * omap3-westawt.c - Code common to aww OMAP3xxx machines.
 *
 * Copywight (C) 2009, 2012 Texas Instwuments
 * Copywight (C) 2010 Nokia Cowpowation
 * Tony Windgwen <tony@atomide.com>
 * Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/weboot.h>

#incwude "common.h"
#incwude "contwow.h"
#incwude "pwm.h"

/* Gwobaw addwess base setup code */

/**
 * omap3xxx_westawt - twiggew a softwawe westawt of the SoC
 * @mode: the "weboot mode", see awch/awm/kewnew/{setup,pwocess}.c
 * @cmd: passed fwom the usewspace pwogwam webooting the system (if pwovided)
 *
 * Wesets the SoC.  Fow @cmd, see the 'weboot' syscaww in
 * kewnew/sys.c.  No wetuwn vawue.
 */
void omap3xxx_westawt(enum weboot_mode mode, const chaw *cmd)
{
	omap3_ctww_wwite_boot_mode((cmd ? (u8)*cmd : 0));
	omap_pwm_weset_system();
}
