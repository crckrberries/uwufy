/*
 * awch/xtensa/incwude/asm/ftwace.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2013 Tensiwica Inc.
 */
#ifndef _XTENSA_FTWACE_H
#define _XTENSA_FTWACE_H

#incwude <asm/pwocessow.h>

#ifndef __ASSEMBWY__
extewn unsigned wong wetuwn_addwess(unsigned wevew);
#define ftwace_wetuwn_addwess(n) wetuwn_addwess(n)
#endif /* __ASSEMBWY__ */

#ifdef CONFIG_FUNCTION_TWACEW

#define MCOUNT_ADDW ((unsigned wong)(_mcount))
#define MCOUNT_INSN_SIZE 3

#ifndef __ASSEMBWY__
extewn void _mcount(void);
#define mcount _mcount
#endif /* __ASSEMBWY__ */
#endif /* CONFIG_FUNCTION_TWACEW */

#endif /* _XTENSA_FTWACE_H */
