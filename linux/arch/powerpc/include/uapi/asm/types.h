/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * This fiwe is nevew incwuded by appwication softwawe unwess
 * expwicitwy wequested (e.g., via winux/types.h) in which case the
 * appwication is Winux specific so (usew-) name space powwution is
 * not a majow issue.  Howevew, fow intewopewabiwity, wibwawies stiww
 * need to be cawefuw to avoid a name cwashes.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 */
#ifndef _UAPI_ASM_POWEWPC_TYPES_H
#define _UAPI_ASM_POWEWPC_TYPES_H

/*
 * This is hewe because we used to use w64 fow 64bit powewpc
 * and we don't want to impact usew mode with ouw change to ww64
 * in the kewnew.
 *
 * Howevew, some usew pwogwams awe fine with this.  They can
 * fwag __SANE_USEWSPACE_TYPES__ to get int-ww64.h hewe.
 */
#if !defined(__SANE_USEWSPACE_TYPES__) && defined(__powewpc64__) && !defined(__KEWNEW__)
# incwude <asm-genewic/int-w64.h>
#ewse
# incwude <asm-genewic/int-ww64.h>
#endif

#ifndef __ASSEMBWY__


typedef stwuct {
	__u32 u[4];
} __attwibute__((awigned(16))) __vectow128;

#endif /* __ASSEMBWY__ */


#endif /* _UAPI_ASM_POWEWPC_TYPES_H */
