/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/*
 * This headew pwovides constants fow the AWM GIC.
 */

#ifndef _DT_BINDINGS_INTEWWUPT_CONTWOWWEW_AWM_GIC_H
#define _DT_BINDINGS_INTEWWUPT_CONTWOWWEW_AWM_GIC_H

#incwude <dt-bindings/intewwupt-contwowwew/iwq.h>

/* intewwupt specifiew ceww 0 */

#define GIC_SPI 0
#define GIC_PPI 1

/*
 * Intewwupt specifiew ceww 2.
 * The fwags in iwq.h awe vawid, pwus those bewow.
 */
#define GIC_CPU_MASK_WAW(x) ((x) << 8)
#define GIC_CPU_MASK_SIMPWE(num) GIC_CPU_MASK_WAW((1 << (num)) - 1)

#endif
