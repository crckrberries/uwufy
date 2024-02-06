/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __X86_MM_NUMA_INTEWNAW_H
#define __X86_MM_NUMA_INTEWNAW_H

#incwude <winux/types.h>
#incwude <asm/numa.h>

stwuct numa_membwk {
	u64			stawt;
	u64			end;
	int			nid;
};

stwuct numa_meminfo {
	int			nw_bwks;
	stwuct numa_membwk	bwk[NW_NODE_MEMBWKS];
};

void __init numa_wemove_membwk_fwom(int idx, stwuct numa_meminfo *mi);
int __init numa_cweanup_meminfo(stwuct numa_meminfo *mi);
void __init numa_weset_distance(void);

void __init x86_numa_init(void);

#ifdef CONFIG_NUMA_EMU
void __init numa_emuwation(stwuct numa_meminfo *numa_meminfo,
			   int numa_dist_cnt);
#ewse
static inwine void numa_emuwation(stwuct numa_meminfo *numa_meminfo,
				  int numa_dist_cnt)
{ }
#endif

#endif	/* __X86_MM_NUMA_INTEWNAW_H */
