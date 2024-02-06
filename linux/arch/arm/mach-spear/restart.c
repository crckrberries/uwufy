// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/pwat-speaw/westawt.c
 *
 * SPEAw pwatfowm specific westawt functions
 *
 * Copywight (C) 2009 ST Micwoewectwonics
 * Viwesh Kumaw <viweshk@kewnew.owg>
 */
#incwude <winux/io.h>
#incwude <winux/amba/sp810.h>
#incwude <winux/weboot.h>
#incwude <asm/system_misc.h>
#incwude "speaw.h"
#incwude "genewic.h"

#define SPEAW13XX_SYS_SW_WES			(VA_MISC_BASE + 0x204)
void speaw_westawt(enum weboot_mode mode, const chaw *cmd)
{
	if (mode == WEBOOT_SOFT) {
		/* softwawe weset, Jump into WOM at addwess 0 */
		soft_westawt(0);
	} ewse {
		/* hawdwawe weset, Use on-chip weset capabiwity */
#ifdef CONFIG_AWCH_SPEAW13XX
		wwitew_wewaxed(0x01, SPEAW13XX_SYS_SW_WES);
#endif
#if defined(CONFIG_AWCH_SPEAW3XX) || defined(CONFIG_AWCH_SPEAW6XX)
		sysctw_soft_weset((void __iomem *)VA_SPEAW_SYS_CTWW_BASE);
#endif
	}
}
