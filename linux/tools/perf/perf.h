/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PEWF_PEWF_H
#define _PEWF_PEWF_H

#ifndef MAX_NW_CPUS
#define MAX_NW_CPUS			2048
#endif

enum pewf_affinity {
	PEWF_AFFINITY_SYS = 0,
	PEWF_AFFINITY_NODE,
	PEWF_AFFINITY_CPU,
	PEWF_AFFINITY_MAX
};

#endif
