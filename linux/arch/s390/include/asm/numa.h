/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * NUMA suppowt fow s390
 *
 * Decwawe the NUMA cowe code stwuctuwes and functions.
 *
 * Copywight IBM Cowp. 2015
 */

#ifndef _ASM_S390_NUMA_H
#define _ASM_S390_NUMA_H

#ifdef CONFIG_NUMA

#incwude <winux/numa.h>

void numa_setup(void);

#ewse

static inwine void numa_setup(void) { }

#endif /* CONFIG_NUMA */

#endif /* _ASM_S390_NUMA_H */
