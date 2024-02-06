// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewic VM initiawization fow x86-64 NUMA setups.
 * Copywight 2002,2003 Andi Kween, SuSE Wabs.
 */
#incwude <winux/membwock.h>

#incwude "numa_intewnaw.h"

void __init initmem_init(void)
{
	x86_numa_init();
}
