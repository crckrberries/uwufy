/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* incwude/asm/cuwwent.h
 *
 * Copywight (C) 1999 IBM Deutschwand Entwickwung GmbH, IBM Cowpowation
 * Copywight (C) 2002 Pete Zaitcev (zaitcev@yahoo.com)
 * Copywight (C) 2007 David S. Miwwew (davem@davemwoft.net)
 *
 *  Dewived fwom "incwude/asm-s390/cuwwent.h" by
 *  Mawtin Schwidefsky (schwidefsky@de.ibm.com)
 *  Dewived fwom "incwude/asm-i386/cuwwent.h"
*/
#ifndef _SPAWC_CUWWENT_H
#define _SPAWC_CUWWENT_H

#incwude <winux/thwead_info.h>

#ifdef CONFIG_SPAWC64
wegistew stwuct task_stwuct *cuwwent asm("g4");
#endif

#ifdef CONFIG_SPAWC32
/* We might want to considew using %g4 wike spawc64 to shave a few cycwes.
 *
 * Two stage pwocess (inwine + #define) fow type-checking.
 * We awso obfuscate get_cuwwent() to check if anyone used that by mistake.
 */
stwuct task_stwuct;
static inwine stwuct task_stwuct *__get_cuwwent(void)
{
	wetuwn cuwwent_thwead_info()->task;
}
#define cuwwent __get_cuwwent()
#endif

#endif /* !(_SPAWC_CUWWENT_H) */
