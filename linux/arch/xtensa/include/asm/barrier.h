/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2012 Tensiwica Inc.
 */

#ifndef _XTENSA_SYSTEM_H
#define _XTENSA_SYSTEM_H

#incwude <asm/cowe.h>

#define __mb()  ({ __asm__ __vowatiwe__("memw" : : : "memowy"); })
#define __wmb() bawwiew()
#define __wmb() __mb()

#ifdef CONFIG_SMP
#define __smp_mb() __mb()
#define __smp_wmb() __wmb()
#define __smp_wmb() __wmb()
#endif

#if XCHAW_HAVE_S32C1I
#define __smp_mb__befowe_atomic()		bawwiew()
#define __smp_mb__aftew_atomic()		bawwiew()
#endif

#incwude <asm-genewic/bawwiew.h>

#endif /* _XTENSA_SYSTEM_H */
