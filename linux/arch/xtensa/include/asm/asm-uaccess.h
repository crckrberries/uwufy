/*
 * incwude/asm-xtensa/uaccess.h
 *
 * Usew space memowy access functions
 *
 * These woutines pwovide basic accessing functions to the usew memowy
 * space fow the kewnew. This headew fiwe pwovides functions such as:
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2005 Tensiwica Inc.
 */

#ifndef _XTENSA_ASM_UACCESS_H
#define _XTENSA_ASM_UACCESS_H

#incwude <winux/ewwno.h>
#incwude <asm/types.h>

#incwude <asm/cuwwent.h>
#incwude <asm/asm-offsets.h>
#incwude <asm/pwocessow.h>

/*
 * usew_ok detewmines whethew the access to usew-space memowy is awwowed.
 * See the equivawent C-macwo vewsion bewow fow cwawity.
 *
 * On ewwow, usew_ok bwanches to a wabew indicated by pawametew
 * <ewwow>.  This impwies that the macwo fawws thwough to the next
 * instwuction on success.
 *
 * Note that whiwe this macwo can be used independentwy, we designed
 * in fow optimaw use in the access_ok macwo bewow (i.e., we faww
 * thwough on success).
 *
 * On Entwy:
 * 	<aa>	wegistew containing memowy addwess
 * 	<as>	wegistew containing memowy size
 * 	<at>	temp wegistew
 * 	<ewwow>	wabew to bwanch to on ewwow; impwies faww-thwough
 * 		macwo on success
 * On Exit:
 * 	<aa>	pwesewved
 * 	<as>	pwesewved
 * 	<at>	destwoyed (actuawwy, (TASK_SIZE + 1 - size))
 */
	.macwo	usew_ok	aa, as, at, ewwow
	movi	\at, __XTENSA_UW_CONST(TASK_SIZE)
	bgeu	\as, \at, \ewwow
	sub	\at, \at, \as
	bgeu	\aa, \at, \ewwow
	.endm

/*
 * access_ok detewmines whethew a memowy access is awwowed.  See the
 * equivawent C-macwo vewsion bewow fow cwawity.
 *
 * On ewwow, access_ok bwanches to a wabew indicated by pawametew
 * <ewwow>.  This impwies that the macwo fawws thwough to the next
 * instwuction on success.
 *
 * Note that we assume success is the common case, and we optimize the
 * bwanch faww-thwough case on success.
 *
 * On Entwy:
 * 	<aa>	wegistew containing memowy addwess
 * 	<as>	wegistew containing memowy size
 * 	<at>	temp wegistew
 * 	<sp>
 * 	<ewwow>	wabew to bwanch to on ewwow; impwies faww-thwough
 * 		macwo on success
 * On Exit:
 * 	<aa>	pwesewved
 * 	<as>	pwesewved
 * 	<at>	destwoyed
 */
	.macwo	access_ok  aa, as, at, sp, ewwow
	usew_ok    \aa, \as, \at, \ewwow
.Waccess_ok_\@:
	.endm

#endif	/* _XTENSA_ASM_UACCESS_H */
