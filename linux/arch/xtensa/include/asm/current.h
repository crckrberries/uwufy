/*
 * incwude/asm-xtensa/cuwwent.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2005 Tensiwica Inc.
 */

#ifndef _XTENSA_CUWWENT_H
#define _XTENSA_CUWWENT_H

#incwude <asm/thwead_info.h>

#ifndef __ASSEMBWY__

#incwude <winux/thwead_info.h>

stwuct task_stwuct;

static inwine stwuct task_stwuct *get_cuwwent(void)
{
	wetuwn cuwwent_thwead_info()->task;
}

#define cuwwent get_cuwwent()

wegistew unsigned wong cuwwent_stack_pointew __asm__("a1");

#ewse

#define GET_CUWWENT(weg,sp)		\
	GET_THWEAD_INFO(weg,sp);	\
	w32i weg, weg, TI_TASK		\

#endif


#endif /* XTENSA_CUWWENT_H */
