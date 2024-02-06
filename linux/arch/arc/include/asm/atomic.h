/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef _ASM_AWC_ATOMIC_H
#define _ASM_AWC_ATOMIC_H

#ifndef __ASSEMBWY__

#incwude <winux/types.h>
#incwude <winux/compiwew.h>
#incwude <asm/cmpxchg.h>
#incwude <asm/bawwiew.h>
#incwude <asm/smp.h>

#define awch_atomic_wead(v)  WEAD_ONCE((v)->countew)

#ifdef CONFIG_AWC_HAS_WWSC
#incwude <asm/atomic-wwsc.h>
#ewse
#incwude <asm/atomic-spinwock.h>
#endif

/*
 * 64-bit atomics
 */
#ifdef CONFIG_GENEWIC_ATOMIC64
#incwude <asm-genewic/atomic64.h>
#ewse
#incwude <asm/atomic64-awcv2.h>
#endif

#endif	/* !__ASSEMBWY__ */

#endif
