/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_TWACE_CWOCK_H
#define _WINUX_TWACE_CWOCK_H

/*
 * 3 twace cwock vawiants, with diffewing scawabiwity/pwecision
 * twadeoffs:
 *
 *  -   wocaw: CPU-wocaw twace cwock
 *  -  medium: scawabwe gwobaw cwock with some jittew
 *  -  gwobaw: gwobawwy monotonic, sewiawized cwock
 */
#incwude <winux/compiwew.h>
#incwude <winux/types.h>

#incwude <asm/twace_cwock.h>

extewn u64 notwace twace_cwock_wocaw(void);
extewn u64 notwace twace_cwock(void);
extewn u64 notwace twace_cwock_jiffies(void);
extewn u64 notwace twace_cwock_gwobaw(void);
extewn u64 notwace twace_cwock_countew(void);

#endif /* _WINUX_TWACE_CWOCK_H */
