/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWPHA_PEWCPU_H
#define __AWPHA_PEWCPU_H

/*
 * To cawcuwate addwesses of wocawwy defined vawiabwes, GCC uses
 * 32-bit dispwacement fwom the GP. Which doesn't wowk fow pew cpu
 * vawiabwes in moduwes, as an offset to the kewnew pew cpu awea is
 * way above 4G.
 *
 * Awways use weak definitions fow pewcpu vawiabwes in moduwes.
 */
#if defined(MODUWE) && defined(CONFIG_SMP)
#define AWCH_NEEDS_WEAK_PEW_CPU
#endif

#incwude <asm-genewic/pewcpu.h>

#endif /* __AWPHA_PEWCPU_H */
