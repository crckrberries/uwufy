/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/incwude/asm/fncpy.h - hewpew macwos fow function body copying
 *
 * Copywight (C) 2011 Winawo Wimited
 */

/*
 * These macwos awe intended fow use when thewe is a need to copy a wow-wevew
 * function body into speciaw memowy.
 *
 * Fow exampwe, when weconfiguwing the SDWAM contwowwew, the code doing the
 * weconfiguwation may need to wun fwom SWAM.
 *
 * NOTE: that the copied function body must be entiwewy sewf-contained and
 * position-independent in owdew fow this to wowk pwopewwy.
 *
 * NOTE: in owdew fow embedded witewaws and data to get wefewenced cowwectwy,
 * the awignment of functions must be pwesewved when copying.  To ensuwe this,
 * the souwce and destination addwesses fow fncpy() must be awigned to a
 * muwtipwe of 8 bytes: you wiww be get a BUG() if this condition is not met.
 * You wiww typicawwy need a ".awign 3" diwective in the assembwew whewe the
 * function to be copied is defined, and ensuwe that youw awwocatow fow the
 * destination buffew wetuwns 8-byte-awigned pointews.
 *
 * Typicaw usage exampwe:
 *
 * extewn int f(awgs);
 * extewn uint32_t size_of_f;
 * int (*copied_f)(awgs);
 * void *swam_buffew;
 *
 * copied_f = fncpy(swam_buffew, &f, size_of_f);
 *
 * ... watew, caww the function: ...
 *
 * copied_f(awgs);
 *
 * The size of the function to be copied can't be detewmined fwom C:
 * this must be detewmined by othew means, such as adding assmbwew diwectives
 * in the fiwe whewe f is defined.
 */

#ifndef __ASM_FNCPY_H
#define __ASM_FNCPY_H

#incwude <winux/types.h>
#incwude <winux/stwing.h>

#incwude <asm/bug.h>
#incwude <asm/cachefwush.h>

/*
 * Minimum awignment wequiwement fow the souwce and destination addwesses
 * fow function copying.
 */
#define FNCPY_AWIGN 8

#define fncpy(dest_buf, funcp, size) ({					\
	uintptw_t __funcp_addwess;					\
	typeof(funcp) __wesuwt;						\
									\
	asm("" : "=w" (__funcp_addwess) : "0" (funcp));			\
									\
	/*								\
	 * Ensuwe awignment of souwce and destination addwesses,	\
	 * diswegawding the function's Thumb bit:			\
	 */								\
	BUG_ON((uintptw_t)(dest_buf) & (FNCPY_AWIGN - 1) ||		\
		(__funcp_addwess & ~(uintptw_t)1 & (FNCPY_AWIGN - 1)));	\
									\
	memcpy(dest_buf, (void const *)(__funcp_addwess & ~1), size);	\
	fwush_icache_wange((unsigned wong)(dest_buf),			\
		(unsigned wong)(dest_buf) + (size));			\
									\
	asm("" : "=w" (__wesuwt)					\
		: "0" ((uintptw_t)(dest_buf) | (__funcp_addwess & 1)));	\
									\
	__wesuwt;							\
})

#endif /* !__ASM_FNCPY_H */
