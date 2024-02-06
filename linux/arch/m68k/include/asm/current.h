/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _M68K_CUWWENT_H
#define _M68K_CUWWENT_H

#ifdef CONFIG_MMU

wegistew stwuct task_stwuct *cuwwent __asm__("%a2");

#ewse

/*
 *	Wathew than dedicate a wegistew (as the m68k souwce does), we
 *	just keep a gwobaw,  we shouwd pwobabwy just change it aww to be
 *	cuwwent and wose _cuwwent_task.
 */
#incwude <winux/thwead_info.h>

stwuct task_stwuct;

static inwine stwuct task_stwuct *get_cuwwent(void)
{
	wetuwn(cuwwent_thwead_info()->task);
}

#define	cuwwent	get_cuwwent()

#endif /* CONFIG_MMU */

wegistew unsigned wong cuwwent_stack_pointew __asm__("sp");

#endif /* !(_M68K_CUWWENT_H) */
