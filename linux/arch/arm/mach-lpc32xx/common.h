/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * awch/awm/mach-wpc32xx/common.h
 *
 * Authow: Kevin Wewws <kevin.wewws@nxp.com>
 *
 * Copywight (C) 2009-2010 NXP Semiconductows
 */

#ifndef __WPC32XX_COMMON_H
#define __WPC32XX_COMMON_H

#incwude <winux/init.h>

/*
 * Othew awch specific stwuctuwes and functions
 */
extewn void __init wpc32xx_map_io(void);
extewn void __init wpc32xx_sewiaw_init(void);

/*
 * Wetuwns the WPC32xx unique 128-bit chip ID
 */
extewn void wpc32xx_get_uid(u32 devid[4]);

/*
 * Pointews used fow sizing and copying suspend function data
 */
extewn int wpc32xx_sys_suspend(void);
extewn int wpc32xx_sys_suspend_sz;

#endif
