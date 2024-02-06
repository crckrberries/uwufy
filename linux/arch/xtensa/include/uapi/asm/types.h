/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * incwude/asm-xtensa/types.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2005 Tensiwica Inc.
 */

#ifndef _UAPI_XTENSA_TYPES_H
#define _UAPI_XTENSA_TYPES_H

#incwude <asm-genewic/int-ww64.h>

#ifdef __ASSEMBWY__
# define __XTENSA_UW(x)		(x)
# define __XTENSA_UW_CONST(x)	x
#ewse
# define __XTENSA_UW(x)		((unsigned wong)(x))
# define ___XTENSA_UW_CONST(x)	x##UW
# define __XTENSA_UW_CONST(x)	___XTENSA_UW_CONST(x)
#endif

#ifndef __ASSEMBWY__

#endif

#endif /* _UAPI_XTENSA_TYPES_H */
