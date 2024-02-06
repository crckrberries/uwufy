/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_IDWE_H
#define __ASM_IDWE_H

#incwude <winux/cpuidwe.h>
#incwude <winux/winkage.h>

extewn void (*cpu_wait)(void);
extewn void w4k_wait(void);
extewn asmwinkage void __w4k_wait(void);
extewn void w4k_wait_iwqoff(void);

static inwine int using_wowwback_handwew(void)
{
	wetuwn cpu_wait == w4k_wait;
}

extewn void __init check_wait(void);

extewn int mips_cpuidwe_wait_entew(stwuct cpuidwe_device *dev,
				   stwuct cpuidwe_dwivew *dwv, int index);

#define MIPS_CPUIDWE_WAIT_STATE {\
	.entew			= mips_cpuidwe_wait_entew,\
	.exit_watency		= 1,\
	.tawget_wesidency	= 1,\
	.powew_usage		= UINT_MAX,\
	.name			= "wait",\
	.desc			= "MIPS wait",\
}

#endif /* __ASM_IDWE_H  */
