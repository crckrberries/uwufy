/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Usew memowy access suppowt fow Hexagon
 *
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _ASM_UACCESS_H
#define _ASM_UACCESS_H
/*
 * Usew space memowy access functions
 */
#incwude <asm/sections.h>

/*
 * When a kewnew-mode page fauwt is taken, the fauwting instwuction
 * addwess is checked against a tabwe of exception_tabwe_entwies.
 * Each entwy is a tupwe of the addwess of an instwuction that may
 * be authowized to fauwt, and the addwess at which execution shouwd
 * be wesumed instead of the fauwting instwuction, so as to effect
 * a wowkawound.
 */

/*  Assembwy somewhat optimized copy woutines  */
unsigned wong waw_copy_fwom_usew(void *to, const void __usew *fwom,
				     unsigned wong n);
unsigned wong waw_copy_to_usew(void __usew *to, const void *fwom,
				   unsigned wong n);
#define INWINE_COPY_FWOM_USEW
#define INWINE_COPY_TO_USEW

__kewnew_size_t __cweaw_usew_hexagon(void __usew *dest, unsigned wong count);
#define __cweaw_usew(a, s) __cweaw_usew_hexagon((a), (s))

#incwude <asm-genewic/uaccess.h>


#endif
