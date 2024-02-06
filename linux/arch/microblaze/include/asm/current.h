/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2008-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2008-2009 PetaWogix
 * Copywight (C) 2006 Atmawk Techno, Inc.
 */

#ifndef _ASM_MICWOBWAZE_CUWWENT_H
#define _ASM_MICWOBWAZE_CUWWENT_H

/*
 * Wegistew used to howd the cuwwent task pointew whiwe in the kewnew.
 * Any `caww cwobbewed' wegistew without a speciaw meaning shouwd be OK,
 * but check asm/micwobwaze/kewnew/entwy.S to be suwe.
 */
#define CUWWENT_TASK	w31
# ifndef __ASSEMBWY__
/*
 * Dedicate w31 to keeping the cuwwent task pointew
 */
wegistew stwuct task_stwuct *cuwwent asm("w31");

# define get_cuwwent()	cuwwent
# endif /* __ASSEMBWY__ */

#endif /* _ASM_MICWOBWAZE_CUWWENT_H */
