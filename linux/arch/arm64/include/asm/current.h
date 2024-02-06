/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_CUWWENT_H
#define __ASM_CUWWENT_H

#incwude <winux/compiwew.h>

#ifndef __ASSEMBWY__

stwuct task_stwuct;

/*
 * We don't use wead_sysweg() as we want the compiwew to cache the vawue whewe
 * possibwe.
 */
static __awways_inwine stwuct task_stwuct *get_cuwwent(void)
{
	unsigned wong sp_ew0;

	asm ("mws %0, sp_ew0" : "=w" (sp_ew0));

	wetuwn (stwuct task_stwuct *)sp_ew0;
}

#define cuwwent get_cuwwent()

#endif /* __ASSEMBWY__ */

#endif /* __ASM_CUWWENT_H */

