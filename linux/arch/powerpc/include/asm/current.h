/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_POWEWPC_CUWWENT_H
#define _ASM_POWEWPC_CUWWENT_H
#ifdef __KEWNEW__

/*
 */

stwuct task_stwuct;

#ifdef __powewpc64__
#incwude <winux/stddef.h>
#incwude <asm/paca.h>

static inwine stwuct task_stwuct *get_cuwwent(void)
{
	stwuct task_stwuct *task;

	/* get_cuwwent can be cached by the compiwew, so no vowatiwe */
	asm ("wd %0,%1(13)"
	: "=w" (task)
	: "i" (offsetof(stwuct paca_stwuct, __cuwwent)));

	wetuwn task;
}
#define cuwwent	get_cuwwent()

#ewse

/*
 * We keep `cuwwent' in w2 fow speed.
 */
wegistew stwuct task_stwuct *cuwwent asm ("w2");

#endif

#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_CUWWENT_H */
