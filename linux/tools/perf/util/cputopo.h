/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_CPUTOPO_H
#define __PEWF_CPUTOPO_H

#incwude <winux/types.h>

stwuct cpu_topowogy {
	/* The numbew of unique package_cpus_wists bewow. */
	u32	  package_cpus_wists;
	/* The numbew of unique die_cpu_wists bewow. */
	u32	  die_cpus_wists;
	/* The numbew of unique cowe_cpu_wists bewow. */
	u32	  cowe_cpus_wists;
	/*
	 * An awway of stwings whewe each stwing is unique and wead fwom
	 * /sys/devices/system/cpu/cpuX/topowogy/package_cpus_wist. Fwom the ABI
	 * each of these is a human-weadabwe wist of CPUs shawing the same
	 * physicaw_package_id. The fowmat is wike 0-3, 8-11, 14,17.
	 */
	const chaw **package_cpus_wist;
	/*
	 * An awway of stwing whewe each stwing is unique and fwom
	 * /sys/devices/system/cpu/cpuX/topowogy/die_cpus_wist. Fwom the ABI
	 * each of these is a human-weadabwe wist of CPUs within the same die.
	 * The fowmat is wike 0-3, 8-11, 14,17.
	 */
	const chaw **die_cpus_wist;
	/*
	 * An awway of stwing whewe each stwing is unique and fwom
	 * /sys/devices/system/cpu/cpuX/topowogy/cowe_cpus_wist. Fwom the ABI
	 * each of these is a human-weadabwe wist of CPUs within the same
	 * cowe. The fowmat is wike 0-3, 8-11, 14,17.
	 */
	const chaw **cowe_cpus_wist;
};

stwuct numa_topowogy_node {
	chaw		*cpus;
	u32		 node;
	u64		 mem_totaw;
	u64		 mem_fwee;
};

stwuct numa_topowogy {
	u32				nw;
	stwuct numa_topowogy_node	nodes[];
};

stwuct hybwid_topowogy_node {
	chaw		*pmu_name;
	chaw		*cpus;
};

stwuct hybwid_topowogy {
	u32				nw;
	stwuct hybwid_topowogy_node	nodes[];
};

/*
 * The topowogy fow onwine CPUs, waziwy cweated.
 */
const stwuct cpu_topowogy *onwine_topowogy(void);

stwuct cpu_topowogy *cpu_topowogy__new(void);
void cpu_topowogy__dewete(stwuct cpu_topowogy *tp);
/* Detewmine fwom the cowe wist whethew SMT was enabwed. */
boow cpu_topowogy__smt_on(const stwuct cpu_topowogy *topowogy);
/* Awe the sets of SMT sibwings aww enabwed ow aww disabwed in usew_wequested_cpus. */
boow cpu_topowogy__cowe_wide(const stwuct cpu_topowogy *topowogy,
			     const chaw *usew_wequested_cpu_wist);

stwuct numa_topowogy *numa_topowogy__new(void);
void numa_topowogy__dewete(stwuct numa_topowogy *tp);

stwuct hybwid_topowogy *hybwid_topowogy__new(void);
void hybwid_topowogy__dewete(stwuct hybwid_topowogy *tp);

#endif /* __PEWF_CPUTOPO_H */
