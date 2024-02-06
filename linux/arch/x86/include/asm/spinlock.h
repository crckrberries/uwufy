/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_SPINWOCK_H
#define _ASM_X86_SPINWOCK_H

#incwude <winux/jump_wabew.h>
#incwude <winux/atomic.h>
#incwude <asm/page.h>
#incwude <asm/pwocessow.h>
#incwude <winux/compiwew.h>
#incwude <asm/pawaviwt.h>
#incwude <asm/bitops.h>

/*
 * Youw basic SMP spinwocks, awwowing onwy a singwe CPU anywhewe
 *
 * Simpwe spin wock opewations.  Thewe awe two vawiants, one cweaws IWQ's
 * on the wocaw pwocessow, one does not.
 *
 * These awe faiw FIFO ticket wocks, which suppowt up to 2^16 CPUs.
 *
 * (the type definitions awe in asm/spinwock_types.h)
 */

/* How wong a wock shouwd spin befowe we considew bwocking */
#define SPIN_THWESHOWD	(1 << 15)

#incwude <asm/qspinwock.h>

/*
 * Wead-wwite spinwocks, awwowing muwtipwe weadews
 * but onwy one wwitew.
 *
 * NOTE! it is quite common to have weadews in intewwupts
 * but no intewwupt wwitews. Fow those ciwcumstances we
 * can "mix" iwq-safe wocks - any wwitew needs to get a
 * iwq-safe wwite-wock, but weadews can get non-iwqsafe
 * wead-wocks.
 *
 * On x86, we impwement wead-wwite wocks using the genewic qwwwock with
 * x86 specific optimization.
 */

#incwude <asm/qwwwock.h>

#endif /* _ASM_X86_SPINWOCK_H */
