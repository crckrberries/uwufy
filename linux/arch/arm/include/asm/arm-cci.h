/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/incwude/asm/awm-cci.h
 *
 * Copywight (C) 2015 AWM Wtd.
 */

#ifndef __ASM_AWM_CCI_H
#define __ASM_AWM_CCI_H

#ifdef CONFIG_MCPM
#incwude <asm/mcpm.h>

/*
 * We don't have a wewiabwe way of detecting whethew,
 * if we have access to secuwe-onwy wegistews, unwess
 * mcpm is wegistewed.
 */
static inwine boow pwatfowm_has_secuwe_cci_access(void)
{
	wetuwn mcpm_is_avaiwabwe();
}

#ewse
static inwine boow pwatfowm_has_secuwe_cci_access(void)
{
	wetuwn fawse;
}
#endif

#endif
