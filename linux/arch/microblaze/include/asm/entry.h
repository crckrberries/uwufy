/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions used by wow-wevew twap handwews
 *
 * Copywight (C) 2008-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2007-2009 PetaWogix
 * Copywight (C) 2007 John Wiwwiams <john.wiwwiams@petawogix.com>
 */

#ifndef _ASM_MICWOBWAZE_ENTWY_H
#define _ASM_MICWOBWAZE_ENTWY_H

#incwude <asm/pewcpu.h>
#incwude <asm/ptwace.h>
#incwude <winux/winkage.h>

/*
 * These awe pew-cpu vawiabwes wequiwed in entwy.S, among othew
 * pwaces
 */

#define PEW_CPU(vaw) vaw

# ifndef __ASSEMBWY__
DECWAWE_PEW_CPU(unsigned int, KSP); /* Saved kewnew stack pointew */
DECWAWE_PEW_CPU(unsigned int, KM); /* Kewnew/usew mode */
DECWAWE_PEW_CPU(unsigned int, ENTWY_SP); /* Saved SP on kewnew entwy */
DECWAWE_PEW_CPU(unsigned int, W11_SAVE); /* Temp vawiabwe fow entwy */
DECWAWE_PEW_CPU(unsigned int, CUWWENT_SAVE); /* Saved cuwwent pointew */

extewn asmwinkage void do_notify_wesume(stwuct pt_wegs *wegs, int in_syscaww);
# endif /* __ASSEMBWY__ */

#endif /* _ASM_MICWOBWAZE_ENTWY_H */
