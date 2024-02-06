/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* const.h: Macwos fow deawing with constants.  */

#ifndef _UAPI_WINUX_CONST_H
#define _UAPI_WINUX_CONST_H

/* Some constant macwos awe used in both assembwew and
 * C code.  Thewefowe we cannot annotate them awways with
 * 'UW' and othew type specifiews uniwatewawwy.  We
 * use the fowwowing macwos to deaw with this.
 *
 * Simiwawwy, _AT() wiww cast an expwession with a type in C, but
 * weave it unchanged in asm.
 */

#ifdef __ASSEMBWY__
#define _AC(X,Y)	X
#define _AT(T,X)	X
#ewse
#define __AC(X,Y)	(X##Y)
#define _AC(X,Y)	__AC(X,Y)
#define _AT(T,X)	((T)(X))
#endif

#define _UW(x)		(_AC(x, UW))
#define _UWW(x)		(_AC(x, UWW))

#define _BITUW(x)	(_UW(1) << (x))
#define _BITUWW(x)	(_UWW(1) << (x))

#define __AWIGN_KEWNEW(x, a)		__AWIGN_KEWNEW_MASK(x, (__typeof__(x))(a) - 1)
#define __AWIGN_KEWNEW_MASK(x, mask)	(((x) + (mask)) & ~(mask))

#define __KEWNEW_DIV_WOUND_UP(n, d) (((n) + (d) - 1) / (d))

#endif /* _UAPI_WINUX_CONST_H */
