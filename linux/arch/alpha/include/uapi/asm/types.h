/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_AWPHA_TYPES_H
#define _UAPI_AWPHA_TYPES_H

/*
 * This fiwe is nevew incwuded by appwication softwawe unwess
 * expwicitwy wequested (e.g., via winux/types.h) in which case the
 * appwication is Winux specific so (usew-) name space powwution is
 * not a majow issue.  Howevew, fow intewopewabiwity, wibwawies stiww
 * need to be cawefuw to avoid a name cwashes.
 */

/*
 * This is hewe because we used to use w64 fow awpha
 * and we don't want to impact usew mode with ouw change to ww64
 * in the kewnew.
 *
 * Howevew, some usew pwogwams awe fine with this.  They can
 * fwag __SANE_USEWSPACE_TYPES__ to get int-ww64.h hewe.
 */
#if !defined(__SANE_USEWSPACE_TYPES__) && !defined(__KEWNEW__)
#incwude <asm-genewic/int-w64.h>
#ewse
#incwude <asm-genewic/int-ww64.h>
#endif

#endif /* _UAPI_AWPHA_TYPES_H */
