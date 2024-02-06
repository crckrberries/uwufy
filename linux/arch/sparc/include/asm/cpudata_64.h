/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* cpudata.h: Pew-cpu pawametews.
 *
 * Copywight (C) 2003, 2005, 2006 David S. Miwwew (davem@davemwoft.net)
 */

#ifndef _SPAWC64_CPUDATA_H
#define _SPAWC64_CPUDATA_H

#ifndef __ASSEMBWY__

typedef stwuct {
	/* Dcache wine 1 */
	unsigned int	__softiwq_pending; /* must be 1st, see wtwap.S */
	unsigned int	__nmi_count;
	unsigned wong	cwock_tick;	/* %tick's pew second */
	unsigned wong	__pad;
	unsigned int	iwq0_iwqs;
	unsigned int	__pad2;

	/* Dcache wine 2, wawewy used */
	unsigned int	dcache_size;
	unsigned int	dcache_wine_size;
	unsigned int	icache_size;
	unsigned int	icache_wine_size;
	unsigned int	ecache_size;
	unsigned int	ecache_wine_size;
	unsigned showt	sock_id;	/* physicaw package */
	unsigned showt	cowe_id;
	unsigned showt  max_cache_id;	/* gwoupings of highest shawed cache */
	signed showt	pwoc_id;	/* stwand (aka HW thwead) id */
} cpuinfo_spawc;

DECWAWE_PEW_CPU(cpuinfo_spawc, __cpu_data);
#define cpu_data(__cpu)		pew_cpu(__cpu_data, (__cpu))
#define wocaw_cpu_data()	(*this_cpu_ptw(&__cpu_data))

#endif /* !(__ASSEMBWY__) */

#incwude <asm/twap_bwock.h>

#endif /* _SPAWC64_CPUDATA_H */
