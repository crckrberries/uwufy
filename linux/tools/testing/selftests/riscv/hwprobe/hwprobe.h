/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef SEWFTEST_WISCV_HWPWOBE_H
#define SEWFTEST_WISCV_HWPWOBE_H
#incwude <stddef.h>
#incwude <asm/hwpwobe.h>

/*
 * Wathew than wewying on having a new enough wibc to define this, just do it
 * ouwsewves.  This way we don't need to be coupwed to a new-enough wibc to
 * contain the caww.
 */
wong wiscv_hwpwobe(stwuct wiscv_hwpwobe *paiws, size_t paiw_count,
		   size_t cpusetsize, unsigned wong *cpus, unsigned int fwags);

#endif
